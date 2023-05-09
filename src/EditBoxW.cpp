/*
* 2023.5.7
* FIXME：输入模式中的输入日期时间未实现
*/
#include "EcontrolHelp.h"

#pragma warning(disable:4996)

#define SCID_EDIT		20230501'01u
#define SCID_EDITPARENT	20230501'02u

#define ED_CUEBANNER_MAXLEN 260

// 编辑框
/*
* 版本1数据布局：
* EEDITDATA结构
* 提示文本
*/
#define DATA_VER_EDIT_1	1
struct EEDITDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	COLORREF crText;		// 文本颜色
	COLORREF crTextBK;		// 文本背景色
	COLORREF crBK;			// 编辑框背景色
	BOOL bHideSel;			// 隐藏选择
	int iMaxLen;			// 最大允许长度
	BOOL bMultiLine;		// 多行
	int iScrollBar;			// 滚动条
	int iAlign;				// 对齐
	int iInputMode;			// 输入方式
	union
	{
		WCHAR chMask;		// 密码遮盖字符
		int PRIV_ALIGN___;
	};
	int iTransformMode;		// 转换方式
	int iSelPos;			// 起始选择位置
	int iSelNum;			// 被选择字符数
	int cchCueBanner;		// 提示文本长度，仅保存信息时有效
	BOOL bCueBannerShowAlways;// 总是显示提示文本，即使编辑框具有焦点
	BOOL bNoAutoSetRect;	// 是否禁止控件内部设置格式矩形（单行时）
	BOOL bAutoWrap;			// 自动换行
};

class CEdit :public elibstl::CCtrlBase
{
	SUBCLASS_MGR_DECL(CEdit)
private:
	EEDITDATA m_Info{};

	HBRUSH m_hbrEditBK = NULL;
	PWSTR m_pszSelText = NULL;

	int m_cyText = 0;// 文本高度
	RECT m_rcMargins{};// 四边框尺寸

	PWSTR m_pszCueBanner = NULL;// 提示文本，没有获取长度的接口，这里就固定为260个字符（含终止NULL）

	void UpdateTextInfo()
	{
		HFONT hFont = (HFONT)SendMessageW(m_hWnd, WM_GETFONT, 0, 0);
		HDC hDC = GetDC(m_hWnd);
		SelectObject(hDC, hFont);
		TEXTMETRICW tm;
		GetTextMetricsW(hDC, &tm);
		m_cyText = tm.tmHeight;
		ReleaseDC(m_hWnd, hDC);
	}

	eStlInline void OnChange()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_CTLCOLOREDIT:
		{
			if (m_CtrlSCInfo.count((HWND)lParam))
			{
				auto p = m_CtrlSCInfo[(HWND)lParam];
				HBRUSH hbr;
				if (p->m_hbrEditBK)
					hbr = p->m_hbrEditBK;
				else
					hbr = (HBRUSH)DefSubclassProc(hWnd, uMsg, wParam, lParam);
				SetTextColor((HDC)wParam, p->m_Info.crText);
				SetBkColor((HDC)wParam, p->m_Info.crTextBK);
				return (LRESULT)hbr;
			}
		}
		break;

		case WM_COMMAND:
		{
			if (HIWORD(wParam) == EN_CHANGE)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnChange();
		}
		break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CEdit*)dwRefData;
		switch (uMsg)
		{
		case WM_CHAR:
		{
			elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
			if (p->m_Info.iInputMode > 2)
			{
				if (GetKeyState(VK_CONTROL) & 0x8000 || GetKeyState(VK_MENU) & 0x8000)
					break;

				if (wParam == VK_BACK ||
					wParam == VK_RETURN)
					break;
			}

			switch (p->m_Info.iInputMode)
			{
			case 3:// 整数文本
			case 6:// 输入短整数
			case 7:// 输入整数
			case 8:// 输入长整数
				if ((wParam >= L'0' && wParam <= L'9') ||
					wParam == L'-')
					break;
				else
					return 0;
			case 4:// 小数文本
			case 9:// 输入小数
			case 10:// 输入双精度小数
				if ((wParam >= L'0' && wParam <= L'9') ||
					wParam == L'-' ||
					wParam == L'.' ||
					wParam == L'e' ||
					wParam == L'E')
					break;
				else
					return 0;
			case 5:// 输入字节
				if ((wParam >= L'0' && wParam <= L'9'))
					break;
				else
					return 0;
			}
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_KILLFOCUS:
		{
#define BUFSIZE_EDITVALUE 36
			WCHAR szValue[BUFSIZE_EDITVALUE]{};
			LONGLONG llValue;
			double lfValue;

			PWSTR pszText;
			int cchText;

			PCWSTR pszCorrectValue = NULL;
			switch (p->m_Info.iInputMode)
			{
			case 5:// 输入字节
				GetWindowTextW(hWnd, szValue, BUFSIZE_EDITVALUE);
				llValue = _wtoi64(szValue);
				if (llValue < 0ll)
					pszCorrectValue = L"0";
				else if (llValue > 255ll)
					pszCorrectValue = L"255";
				else
					SetWindowTextW(hWnd, std::to_wstring(llValue).c_str());
				break;
			case 6:// 输入短整数
				GetWindowTextW(hWnd, szValue, BUFSIZE_EDITVALUE);
				llValue = _wtoi64(szValue);
				if (llValue < -32768ll)
					pszCorrectValue = L"-32768";
				else if (llValue > 32767ll)
					pszCorrectValue = L"32767";
				else
					SetWindowTextW(hWnd, std::to_wstring(llValue).c_str());
				break;
			case 7:// 输入整数
				GetWindowTextW(hWnd, szValue, BUFSIZE_EDITVALUE);
				llValue = _wtoi64(szValue);
				if (llValue < -2147483648ll)
					pszCorrectValue = L"-2147483648";
				else if (llValue > 2147483647ll)
					pszCorrectValue = L"2147483647";
				else
					SetWindowTextW(hWnd, std::to_wstring(llValue).c_str());
				break;
			case 8:// 输入长整数
				GetWindowTextW(hWnd, szValue, BUFSIZE_EDITVALUE);
				llValue = _wtoi64(szValue);
				if (errno == ERANGE)
				{
					if (llValue == _I64_MIN)
						pszCorrectValue = L"-9223372036854775808";
					else if (llValue == _I64_MAX)
						pszCorrectValue = L"9223372036854775807";
				}
				else
					SetWindowTextW(hWnd, std::to_wstring(llValue).c_str());
				break;
			case 9:// 输入小数
			{
				cchText = GetWindowTextLengthW(hWnd);
				if (!cchText)
					break;
				pszText = new WCHAR[cchText + 1];
				GetWindowTextW(hWnd, pszText, cchText + 1);
				lfValue = _wtof(pszText);
				if (lfValue < -3.402823466e38)// 实际上正负值中间是有空隙的，不做判断了。。。
					SetWindowTextW(hWnd, L"-3.402823466e38");
				else if (lfValue < 3.402823466e38)
					SetWindowTextW(hWnd, L"3.402823466e38");
				else
					SetWindowTextW(hWnd, std::to_wstring(lfValue).c_str());
				delete[] pszText;
			}
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

			case 10:// 输入双精度小数
			{
				cchText = GetWindowTextLengthW(hWnd);
				if (!cchText)
					break;
				pszText = new WCHAR[cchText + 1];
				GetWindowTextW(hWnd, pszText, cchText + 1);
				lfValue = _wtof(pszText);
				if (*(ULONGLONG*)&lfValue == 0xFFF0000000000000)
					SetWindowTextW(hWnd, L"-1.79769313486231570E+308");
				else if (*(ULONGLONG*)&lfValue == 0x7FF0000000000000)
					SetWindowTextW(hWnd, L"1.79769313486231570E+308");
				else
					SetWindowTextW(hWnd, std::to_wstring(lfValue).c_str());
				delete[] pszText;
			}
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

			case 11:// 输入日期时间
				break;
			}

			if (pszCorrectValue)
				SetWindowTextW(hWnd, pszCorrectValue);
#undef BUFSIZE_EDITVALUE
		}
		break;

		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;

		case WM_NCCALCSIZE:
		{
			if (!p->GetMultiLine())
			{
				LRESULT lResult;
				if (wParam)
				{
					auto pnccsp = (NCCALCSIZE_PARAMS*)lParam;
					p->m_rcMargins = pnccsp->rgrc[0];// 保存非客户区尺寸
					lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);// call默认过程，计算标准边框尺寸
					// 保存边框尺寸
					p->m_rcMargins.left = pnccsp->rgrc[0].left - p->m_rcMargins.left;
					p->m_rcMargins.top = pnccsp->rgrc[0].top - p->m_rcMargins.top;
					p->m_rcMargins.right -= pnccsp->rgrc[0].right;
					p->m_rcMargins.bottom -= pnccsp->rgrc[0].bottom;
					// 上下留空
					pnccsp->rgrc[0].top += ((pnccsp->rgrc[0].bottom - pnccsp->rgrc[0].top - p->m_cyText) / 2);
					pnccsp->rgrc[0].bottom = pnccsp->rgrc[0].top + p->m_cyText;
				}
				else
				{
					auto prc = (RECT*)lParam;
					p->m_rcMargins = *prc;// 保存非客户区尺寸
					lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);// call默认过程，计算标准边框尺寸
					// 保存边框尺寸
					p->m_rcMargins.left = prc->left - p->m_rcMargins.left;
					p->m_rcMargins.top = prc->top - p->m_rcMargins.top;
					p->m_rcMargins.right -= prc->right;
					p->m_rcMargins.bottom -= prc->bottom;
					// 上下留空
					prc->top += ((prc->bottom - prc->top - p->m_cyText) / 2);
					prc->bottom = prc->top + p->m_cyText;
				}
				return lResult;
			}
		}
		break;

		case WM_NCPAINT:
		{
			DefSubclassProc(hWnd, uMsg, wParam, lParam);// 画默认边框
			if (p->GetMultiLine())
				return 0;

			RECT rcWnd, rcText;
			HDC hDC = GetWindowDC(hWnd);
			// 取非客户区矩形
			GetWindowRect(hWnd, &rcWnd);
			rcWnd.right -= rcWnd.left;
			rcWnd.bottom -= rcWnd.top;
			rcWnd.left = 0;
			rcWnd.top = 0;
			// 制文本矩形
			rcText.left = 0;
			rcText.top = (rcWnd.bottom - p->m_cyText) / 2;
			rcText.right = rcWnd.right;
			rcText.bottom = rcText.top + p->m_cyText;
			// 非客户区矩形减掉边框
			rcWnd.left += p->m_rcMargins.left;
			rcWnd.top += p->m_rcMargins.top;
			rcWnd.right -= p->m_rcMargins.right;
			rcWnd.bottom -= p->m_rcMargins.bottom;
			// 异或合并，剪辑
			HRGN hRgnBK = CreateRectRgnIndirect(&rcWnd);
			HRGN hRgnText = CreateRectRgnIndirect(&rcText);
			CombineRgn(hRgnBK, hRgnBK, hRgnText, RGN_XOR);
			SelectClipRgn(hDC, hRgnBK);
			DeleteObject(hRgnBK);
			DeleteObject(hRgnText);
			// 填充背景
			FillRect(hDC, &rcWnd, p->m_hbrEditBK);
			ReleaseDC(hWnd, hDC);
		}
		return 0;

		case WM_SETFONT:
		{
			auto lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);
			if (!p->GetMultiLine())
			{
				p->UpdateTextInfo();
				p->FrameChanged();
			}
			return lResult;
		}

		case WM_NCHITTEST:
		{
			auto lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);
			if (!p->GetMultiLine())
			{
				if (lResult == HTNOWHERE)// 修复一下NC命中测试，不然设计器里点到边上的时候选不上控件
					lResult = HTBORDER;
			}
			return lResult;
		}
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CEdit() = delete;
	CEdit(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);

		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(EEDITDATA));

			m_pszCueBanner = new WCHAR[ED_CUEBANNER_MAXLEN];
			*m_pszCueBanner = L'\0';

			p += sizeof(EEDITDATA);
			if (m_Info.cchCueBanner)
			{
				memcpy(m_pszCueBanner, p, m_Info.cchCueBanner * sizeof(WCHAR));
				*(m_pszCueBanner + m_Info.cchCueBanner) = L'\0';
			}
		}
		else
		{
			m_Info0.iFrame = 1;
			m_pszCueBanner = new WCHAR[ED_CUEBANNER_MAXLEN];
			*m_pszCueBanner = L'\0';
			m_Info.crTextBK = 0x00FFFFFF;
			m_Info.crBK = 0x00FFFFFF;
			m_Info.bHideSel = TRUE;
		}

		m_Info.iVer = DATA_VER_EDIT_1;

		DWORD dwEDStyle;
		if (m_Info.bMultiLine)
			dwEDStyle = ES_MULTILINE | ES_AUTOVSCROLL | (m_Info.bAutoWrap ? ES_AUTOHSCROLL : 0);
		else
			dwEDStyle = ES_AUTOHSCROLL;

		m_hWnd = CreateWindowExW(0, WC_EDITW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS | dwEDStyle,
			x, y, cx, cy, hParent, (HMENU)nID, GetModuleHandleW(NULL), NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		InitBase0(pAllData);
		SetClr(0, m_Info.crText);
		SetClr(1, m_Info.crTextBK);
		SetClr(2, m_Info.crBK);
		SetHideSel(m_Info.bHideSel);
		SetMaxLen(m_Info.iMaxLen);
		// SetMultiLine(m_Info.bMultiLine);// 这个函数仅仅在必要时重新核算非客户区，没有做其他实质性工作
		SetScrollBar(m_Info.iScrollBar);
		SetAlign(m_Info.iAlign);
		SetInputMode(m_Info.iInputMode);
		if (m_Info.chMask)
			SetMaskChar(m_Info.chMask);
		SetTransformMode(m_Info.iTransformMode);
		SetSelPos(m_Info.iSelPos);
		SetSelNum(m_Info.iSelNum);
		SetCueBannerNoCopy(m_pszCueBanner);
		UpdateTextInfo();
		FrameChanged();
	}

	~CEdit()
	{
		DeleteObject(m_hbrEditBK);
		delete[] m_pszSelText;
		delete[] m_pszCueBanner;
	}

	eStlInline void SetClr(int iType, COLORREF cr)
	{
		switch (iType)
		{
		case 0:m_Info.crText = cr; break;
		case 1:m_Info.crTextBK = cr; break;
		case 2:
			if (m_hbrEditBK)
				DeleteObject(m_hbrEditBK);
			m_hbrEditBK = CreateSolidBrush(cr);
			m_Info.crBK = cr;
			SendMessageW(m_hWnd, WM_NCPAINT, 0, 0);
			break;
		}
		Redraw();
	}

	eStlInline COLORREF GetClr(int iType)
	{
		return elibstl::MultiSelect<COLORREF>(iType, m_Info.crText, m_Info.crTextBK, m_Info.crBK);
	}

	eStlInline void SetHideSel(BOOL bHideSel)
	{
		m_Info.bHideSel = bHideSel;
		elibstl::ModifyWindowStyle(m_hWnd, (bHideSel ? 0 : ES_NOHIDESEL), ES_NOHIDESEL);
	}

	eStlInline BOOL GetHideSel()
	{
		if (m_bInDesignMode)
			return m_Info.bHideSel;
		else
			return !(!!(GetWindowLongPtrW(m_hWnd, GWL_STYLE) & ES_NOHIDESEL));
	}

	eStlInline void SetMaxLen(int iMaxLen)
	{
		m_Info.iMaxLen = iMaxLen;
		SendMessageW(m_hWnd, EM_SETLIMITTEXT, iMaxLen, 0);
	}

	eStlInline int GetMaxLen()
	{
		if (m_bInDesignMode)
			return m_Info.iMaxLen;
		else
			return SendMessageW(m_hWnd, EM_GETLIMITTEXT, 0, 0);
	}

	eStlInline void SetMultiLine(BOOL bMultiLine)
	{
		BOOL bOld = m_Info.bMultiLine;
		m_Info.bMultiLine = bMultiLine;// 不需要修改风格，因为控件要重新创建
		if (!bOld && bMultiLine)
			FrameChanged();
	}

	eStlInline BOOL GetMultiLine()
	{
		if (m_bInDesignMode)
			return m_Info.bMultiLine;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), ES_MULTILINE);
	}

	void SetScrollBar(int i)
	{
		m_Info.iScrollBar = i;
		switch (i)
		{
		case 0:
			ShowScrollBar(m_hWnd, SB_VERT, FALSE);
			ShowScrollBar(m_hWnd, SB_HORZ, FALSE);
			break;
		case 1:
			ShowScrollBar(m_hWnd, SB_VERT, FALSE);
			ShowScrollBar(m_hWnd, SB_HORZ, TRUE);
			break;
		case 2:
			ShowScrollBar(m_hWnd, SB_VERT, TRUE);
			ShowScrollBar(m_hWnd, SB_HORZ, FALSE);
			break;
		case 3:
			ShowScrollBar(m_hWnd, SB_VERT, TRUE);
			ShowScrollBar(m_hWnd, SB_HORZ, TRUE);
			break;
		}
	}

	int GetScrollBar()
	{
		if (m_bInDesignMode)
			return m_Info.iScrollBar;
		else
		{
			BOOL bVSB = elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), WS_VSCROLL);
			BOOL bHSB = elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), WS_HSCROLL);
			if (bVSB)
				if (bHSB)
					return 3;
				else
					return 2;
			if (bHSB)
				return 1;

			return 0;
		}
	}

	eStlInline void SetAlign(int iAlign)
	{
		m_Info.iAlign = iAlign;
		elibstl::ModifyWindowStyle(m_hWnd,
			elibstl::MultiSelect<DWORD>(iAlign, ES_LEFT, ES_CENTER, ES_RIGHT),
			ES_LEFT | ES_CENTER | ES_RIGHT);
	}

	eStlInline int GetAlign()
	{
		if (m_bInDesignMode)
			return m_Info.iAlign;
		else
			return MultiSelectWndStyle(m_hWnd, ES_LEFT, ES_CENTER, ES_RIGHT);
	}

	eStlInline void SetInputMode(int iInputMode)
	{
		m_Info.iInputMode = iInputMode;

		elibstl::ModifyWindowStyle(m_hWnd, ((iInputMode == 1) ? ES_READONLY : 0), ES_READONLY);

		if (iInputMode == 2)// 密码输入
			SendMessageW(m_hWnd, EM_SETPASSWORDCHAR, L'*', 0);
		else
			SendMessageW(m_hWnd, EM_SETPASSWORDCHAR, 0, 0);
	}

	eStlInline int GetInputMode()
	{
		return m_Info.iInputMode;
	}

	eStlInline void SetMaskChar(WCHAR chMask)
	{
		if (!chMask)
			chMask = L'*';
		m_Info.chMask = chMask;
		SendMessageW(m_hWnd, EM_SETPASSWORDCHAR, chMask, 0);
	}

	eStlInline WCHAR GetMaskChar()
	{
		if (m_bInDesignMode)
			return m_Info.chMask;
		else
			return (WCHAR)SendMessageW(m_hWnd, EM_GETPASSWORDCHAR, 0, 0);
	}

	void SetTransformMode(int iTransformMode)
	{
		m_Info.iTransformMode = iTransformMode;
		elibstl::ModifyWindowStyle(m_hWnd,
			elibstl::MultiSelect<DWORD>(iTransformMode, 0, ES_LOWERCASE, ES_UPPERCASE),
			ES_LOWERCASE | ES_UPPERCASE);
	}

	int GetTransformMode()
	{
		if (m_bInDesignMode)
			return m_Info.iTransformMode;
		else
		{
			DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
			if (dwStyle & ES_LOWERCASE)
				return 1;
			else if (dwStyle & ES_UPPERCASE)
				return 2;
			else
				return 0;
		}
	}

	void SetSelPos(int iSelPos)
	{
		m_Info.iSelPos = iSelPos;
		DWORD dwStart, dwEnd;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		DWORD dwLen;
		if (dwStart > dwEnd)
			dwLen = dwStart - dwEnd;
		else
			dwLen = dwEnd - dwStart;
		SendMessageW(m_hWnd, EM_SETSEL, iSelPos, iSelPos + dwLen);
	}

	eStlInline int GetSelPos()
	{
		if (m_bInDesignMode)
			return m_Info.iSelPos;
		else
		{
			DWORD dwStart;
			SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, NULL);
			return dwStart;
		}
	}

	eStlInline void SetSelNum(int iSelNum)
	{
		m_Info.iSelNum = iSelNum;
		DWORD dwStart;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, NULL);
		SendMessageW(m_hWnd, EM_SETSEL, dwStart, dwStart + iSelNum);
	}

	int GetSelNum()
	{
		if (m_bInDesignMode)
			return m_Info.iSelNum;
		else
		{
			DWORD dwStart, dwEnd;
			SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
			DWORD dwLen;
			if (dwStart > dwEnd)
				dwLen = dwStart - dwEnd;
			else
				dwLen = dwEnd - dwStart;
			return (int)dwLen;
		}
	}

	eStlInline void SetSelText(PCWSTR pszText)
	{
		SendMessageW(m_hWnd, EM_REPLACESEL, TRUE, (LPARAM)pszText);
	}

	PWSTR GetSelText(SIZE_T* pcb = NULL)
	{
		delete[] m_pszSelText;
		m_pszSelText = NULL;
		if (pcb)
			*pcb = 0u;
		int cch = GetWindowTextLengthW(m_hWnd);
		if (!cch)
			return NULL;

		DWORD dwStart, dwEnd;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		DWORD dwLen;
		if (dwStart > dwEnd)
			dwLen = dwStart - dwEnd;
		else
			dwLen = dwEnd - dwStart;
		if (!dwLen)
			return NULL;
		m_pszSelText = new WCHAR[dwEnd + 1];// UTF-16是变长的，这里按说还要多一步解析，先这样吧。。
		GetWindowTextW(m_hWnd, m_pszSelText, (int)dwEnd + 1);
		if (pcb)
			*pcb = (dwEnd + 1) * sizeof(WCHAR);
		return m_pszSelText;
	}

	eStlInline void SetCueBannerNoCopy(PCWSTR psz)
	{
		if (!m_bInDesignMode)
			SendMessageW(m_hWnd, EM_SETCUEBANNER, m_Info.bCueBannerShowAlways, (LPARAM)psz);
	}

	void SetCueBanner(PCWSTR psz)
	{
		if (!psz)
		{
			*m_pszCueBanner = L'\0';
			SetCueBannerNoCopy(NULL);
			return;
		}

		wcsncpy(m_pszCueBanner, psz, ED_CUEBANNER_MAXLEN - 1);
		*(m_pszCueBanner + ED_CUEBANNER_MAXLEN - 1) = L'\0';
		SetCueBannerNoCopy(m_pszCueBanner);
	}

	eStlInline PCWSTR GetCueBanner(SIZE_T* pcb = NULL)
	{
		if (!m_bInDesignMode)
			SendMessageW(m_hWnd, EM_GETCUEBANNER, (WPARAM)m_pszCueBanner, ED_CUEBANNER_MAXLEN);
		if (pcb)
			*pcb = wcslen(m_pszCueBanner);
		return m_pszCueBanner;
	}

	void SetCueBannerShowAlways(BOOL b)
	{
		m_Info.bCueBannerShowAlways = b;
		SetCueBannerNoCopy(m_pszCueBanner);
	}

	eStlInline BOOL GetCueBannerShowAlways()
	{
		return m_Info.bCueBannerShowAlways;
	}

	BOOL SetAutoWrap(BOOL bAutoWrap)
	{
		m_Info.bAutoWrap = bAutoWrap;
		return GetMultiLine();
	}

	eStlInline BOOL GetAutoWrap()
	{
		return m_Info.bAutoWrap;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		SIZE_T cbCueBanner;
		auto pszCueBanner = GetCueBanner();
		if (pszCueBanner)
		{
			m_Info.cchCueBanner = wcslen(pszCueBanner);
			cbCueBanner = (m_Info.cchCueBanner + 1) * sizeof(WCHAR);
		}
		else
		{
			m_Info.cchCueBanner = 0;
			cbCueBanner = 0u;
		}

		auto hGlobal = FlattenInfoBase0(sizeof(EEDITDATA) + cbCueBanner, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(EEDITDATA));
		// 提示文本
		p += sizeof(EEDITDATA);
		memcpy(p, m_pszCueBanner, cbCueBanner);
		// 
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto pButton = new CEdit(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(pButton->GetHWND());
	}
	
	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 内容
			p->SetTextA(pPropertyVaule->m_szText);
			break;
		case 1:// 内容W
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 2:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 3:// 文本颜色
		case 4:// 文本背景颜色
		case 5:// 编辑框背景颜色
			p->SetClr(nPropertyIndex - 3, pPropertyVaule->m_clr);
			break;
		case 6:// 字体
			p->SetFont((LOGFONTA*)pPropertyVaule->m_data.m_pData);
			break;
		case 7:// 隐藏选择
			p->SetHideSel(pPropertyVaule->m_bool);
			break;
		case 8:// 最大允许长度
			p->SetMaxLen(pPropertyVaule->m_int);
			break;
		case 9:// 是否允许多行
			p->SetMultiLine(pPropertyVaule->m_bool);
			return TRUE;
		case 10:// 滚动条
			p->SetScrollBar(pPropertyVaule->m_int);
			break;
		case 11:// 对齐方式
			p->SetAlign(pPropertyVaule->m_int);
			break;
		case 12:// 输入方式
			p->SetInputMode(pPropertyVaule->m_int);
			break;
		case 13:// 密码遮盖字符
			if (pPropertyVaule->m_data.m_nDataSize)
				p->SetMaskChar(*(PWSTR)pPropertyVaule->m_data.m_pData);
			else
				p->SetMaskChar(L'*');
			break;
		case 14:// 转换方式
			p->SetTransformMode(pPropertyVaule->m_int);
			break;
		case 15:// 起始选择位置
			p->SetSelPos(pPropertyVaule->m_int);
			break;
		case 16:// 被选择字符数
			p->SetSelNum(pPropertyVaule->m_int);
			break;
		case 17:// 被选择文本
			p->SetSelText((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 18:// 提示文本
			p->SetCueBanner((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 19:// 总是显示提示文本
			p->SetCueBannerShowAlways(pPropertyVaule->m_bool);
			break;
		case 20:// 自动换行
			return p->SetAutoWrap(pPropertyVaule->m_bool);
		}

		return FALSE;
	}

	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 内容
			pPropertyVaule->m_szText = p->GetTextA();
			break;
		case 1:// 内容W
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 2:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 3:// 文本颜色
		case 4:// 文本背景颜色
		case 5:// 编辑框背景颜色
			pPropertyVaule->m_clr = p->GetClr(nPropertyIndex - 3);
			break;
		case 6:// 字体
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;
		case 7:// 隐藏选择
			pPropertyVaule->m_bool = p->GetHideSel();
			break;
		case 8:// 最大允许长度
			pPropertyVaule->m_int = p->GetMaxLen();
			break;
		case 9:// 是否允许多行
			pPropertyVaule->m_bool = p->GetMultiLine();
			break;
		case 10:// 滚动条
			pPropertyVaule->m_int = p->GetScrollBar();
			break;
		case 11:// 对齐方式
			pPropertyVaule->m_int = p->GetAlign();
			break;
		case 12:// 输入方式
			pPropertyVaule->m_int = p->GetInputMode();
			break;
		case 13:// 密码遮盖字符
			pPropertyVaule->m_data.m_pData = (BYTE*)&p->m_Info.chMask;
			pPropertyVaule->m_data.m_nDataSize = 1;
			break;
		case 14:// 转换方式
			pPropertyVaule->m_int = p->GetTransformMode();
			break;
		case 15:// 起始选择位置
			pPropertyVaule->m_int = p->GetSelPos();
			break;
		case 16:// 被选择字符数
			pPropertyVaule->m_int = p->GetSelNum();
			break;
		case 17:// 被选择文本
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetSelText((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 18:// 提示文本
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetCueBanner((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 19:// 总是显示提示文本
			pPropertyVaule->m_bool = p->GetCueBannerShowAlways();
			break;
		case 20:// 自动换行
			pPropertyVaule->m_bool = p->GetAutoWrap();
			break;
		}

		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		PWSTR psz;
		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 1:// 内容W
		{
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		break;

		case 13:// 密码遮盖字符W
		{
			WCHAR sz[2]{ p->GetMaskChar(),L'\0' };
			if (elibstl::IntputBox(&psz, sz, L"请输入密码遮盖字符，仅第一个字符有效："))
			{
				p->SetMaskChar(*psz);
				delete psz;
				*pblModified = TRUE;
			}
		}
		break;

		case 18:// 提示文本
		{
			if (elibstl::IntputBox(&psz, p->GetCueBanner()))
			{
				p->SetCueBanner(psz);
				*pblModified = TRUE;
				delete psz;
			}
		}
		break;
		}
		return FALSE;
	}

	static BOOL WINAPI EPropUpdateUI(HUNIT hUnit, INT nPropertyIndex)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		switch (nPropertyIndex)
		{
		case 13:// 密码遮盖字符
			return p->m_Info.iInputMode == 2;
		case 20:// 自动换行
			return p->GetMultiLine();
		}

		return TRUE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 80;
			*((int*)dwParam2) = 20;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CEdit, SCID_EDITPARENT, SCID_EDIT)

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_EditW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)CEdit::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)CEdit::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)CEdit::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)CEdit::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)CEdit::EInputW;
	case ITF_PROPERTY_UPDATE_UI:
		return (PFN_INTERFACE)CEdit::EPropUpdateUI;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)CEdit::ENotify;
	}
	return NULL;
}

static EVENT_INFO2 s_Event_Edit[] =
{
	/*000*/ {"内容被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_Edit[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"内容", "Text", "", UD_TEXT, _PROP_OS(__OS_WIN), NULL},
	/*001*/  {"内容W", "TextW", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*002*/	 {"边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*003*/  {"文本颜色", "TextClr", "", UD_COLOR, _PROP_OS(__OS_WIN),  NULL},
	/*004*/  {"文本背景颜色", "TextBKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),  NULL},
	/*005*/  {"编辑框背景颜色", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),  NULL},
	/*006*/  {"字体", "Font", "", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*007*/  {"隐藏选择", "", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*008*/  {"最大允许长度", "", "0为不限制", UD_INT, _PROP_OS(__OS_WIN),  NULL},
	/*009*/  {"是否允许多行", "", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*010*/  {"滚动条", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无\0""横向滚动条\0""纵向滚动条\0""横向及纵向滚动条\0""\0"},
	/*011*/  {"对齐方式", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左对齐\0""居中\0""右对齐\0""\0"},
	/*012*/  {"输入方式", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN),
					"通常\0""只读\0""密码\0""整数文本\0""小数文本\0""输入字节\0""输入短整数\0""输入整数\0""输入长整数\0""输入小数\0"
					"输入双精度小数\0""输入日期时间\0""\0"},
	/*013*/		{"密码遮盖字符W", "", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,  NULL},
	/*014*/  {"转换方式", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无\0""大写到小写\0""小写到大写\0""\0"},
	/*015*/  {"起始选择位置", "", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*016*/  {"被选择字符数", "", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*017*/  {"被选择文本W", "", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL},
	/*018*/  {"提示文本W", "", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*019*/  {"总是显示提示文本", "", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*020*/  {"自动换行", "", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
};
///////////////////////////////////方法
static INT s_Cmd_Edit[] = { 50,110,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175 };

EXTERN_C void libstl_Edit_AddText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	for (int i = 1; i <= nArgCount - 1; ++i)
	{
		SendMessageW(hWnd, EM_SETSEL, -2, -1);
		SendMessageW(hWnd, EM_REPLACESEL, FALSE, (LPARAM)pArgInf[i].m_pBin + 8);
	}
}
static ARG_INFO s_ArgsAddText[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲加入的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo Fn_EditAddText = { {
		/*ccname*/  ("加入文本"),
		/*egname*/  ("AddTextW"),
		/*explain*/ ("将指定文本加入到编辑框内容的尾部"),
		/*category*/-1,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsAddText),
		/*arg lp*/  s_ArgsAddText,
	} , libstl_Edit_AddText ,"libstl_Edit_AddText" };
///////////////////////////////////
EXTERN_C void libstl_Edit_CharFromPos(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwRet = SendMessageW(hWnd, EM_CHARFROMPOS, 0, MAKELPARAM(pArgInf[1].m_int, pArgInf[2].m_int));
	USHORT usPos = LOWORD(dwRet);
	if (usPos == 65535)
		pRetData->m_int = -1;
	else
		pRetData->m_int = usPos;
	if (pArgInf[3].m_pInt)
	{
		usPos = HIWORD(dwRet);
		if (usPos == 65535)
			*pArgInf[3].m_pInt = -1;
		else
			*pArgInf[3].m_pInt = usPos;
	}
}
static ARG_INFO s_ArgsCharFromPos[] =
{
	{
		/*name*/    "横向位置",
		/*explain*/ "相对客户区",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "纵向位置",
		/*explain*/ "相对客户区",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "行中位置",
		/*explain*/ "接收字符行中位置的变量，若函数失败，则改变量的值为-1",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditCharFromPos = { {
		/*ccname*/  "取坐标处字符",
		/*egname*/  "CharFromPos",
		/*explain*/ "返回字符位置，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsCharFromPos),
		/*arg lp*/  s_ArgsCharFromPos,
	} , libstl_Edit_CharFromPos ,"libstl_Edit_CharFromPos" };
///////////////////////////////////
EXTERN_C void libstl_Edit_CanUndo(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = SendMessageW(hWnd, EM_CANUNDO, 0, 0);

}
FucInfo Fn_EditCanUndo = { {
		/*ccname*/  "是否可撤销",
		/*egname*/  "CanUndo",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_CanUndo ,"libstl_Edit_CanUndo" };
///////////////////////////////////
EXTERN_C void libstl_Edit_EmptyUndoBuf(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	SendMessageW(hWnd, EM_EMPTYUNDOBUFFER, 0, 0);
}
FucInfo Fn_EditEmptyUndoBuf = { {
		/*ccname*/  "清空撤销队列",
		/*egname*/  "EmptyUndoBuf",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_EmptyUndoBuf ,"libstl_Edit_EmptyUndoBuf" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetFirstLine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
}
FucInfo Fn_EditGetFirstLine = { {
		/*ccname*/  "取第一可见行",
		/*egname*/  "GetFirstLine",
		/*explain*/ "返回行索引",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_GetFirstLine ,"libstl_Edit_GetFirstLine" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetLineCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_GETLINECOUNT, 0, 0);
}
FucInfo Fn_EditGetLineCount = { {
		/*ccname*/  "取行数",
		/*egname*/  "GetLineCount",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_GetLineCount ,"libstl_Edit_GetLineCount" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetModify(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_GETMODIFY, 0, 0);
}
FucInfo Fn_EditGetModify = { {
		/*ccname*/  "取修改标志",
		/*egname*/  "GetModify",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_GetModify ,"libstl_Edit_GetModify" };
///////////////////////////////////
EXTERN_C void libstl_Edit_HideBallloonTip(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = SendMessageW(hWnd, EM_HIDEBALLOONTIP, 0, 0);
}
FucInfo Fn_EditHideBallloonTip = { {
		/*ccname*/  "隐藏气球提示",
		/*egname*/  "HideBallloonTip",
		/*explain*/ "该函数需要在清单中指定Comctl6.0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_HideBallloonTip ,"libstl_Edit_HideBallloonTip" };
///////////////////////////////////
EXTERN_C void libstl_Edit_LineLength(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_LINELENGTH, pArgInf[1].m_int, 0);
}
static ARG_INFO s_ArgsLineLength[] =
{
	{
		/*name*/    "行中的字符索引",
		/*explain*/ "若此参数设为-1，则返回选区所在各行的未选定字符数",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo Fn_EditLineLength = { {
		/*ccname*/  "取某行长度",
		/*egname*/  "LineLength",
		/*explain*/ "返回某一行字符的长度，若编辑框为单行模式，则返回全部文本的长度，失败返回0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsLineLength),
		/*arg lp*/  s_ArgsLineLength,
	} , libstl_Edit_LineLength ,"libstl_Edit_LineLength" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetLine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	int cch = SendMessageW(hWnd, EM_LINELENGTH, SendMessageW(hWnd, EM_LINEINDEX, pArgInf[1].m_int, 0), 0);
	if (cch)
	{
		BYTE* pBuf = elibstl::malloc_array<BYTE>((cch + 1) * sizeof(WCHAR));
		*(WORD*)(pBuf + 8) = cch;// 发送消息前将第一个WORD设置为缓冲区大小
		SendMessageW(hWnd, EM_GETLINE, pArgInf[1].m_int, (LPARAM)(pBuf + 8));
		*(((PWSTR)(pBuf + 8)) + cch) = L'\0';// 复制完成后不会添加结尾NULL
		pRetData->m_pBin = pBuf;
	}
	else
		pRetData->m_pBin = NULL;
}
static ARG_INFO s_ArgsGetLine[] =
{
	{
		/*name*/    "行索引",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo Fn_EditGetLine = { {
		/*ccname*/  "取行文本",
		/*egname*/  "GetLine",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetLine),
		/*arg lp*/  s_ArgsGetLine,
	} , libstl_Edit_GetLine ,"libstl_Edit_GetLine" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetMargins(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwRet = SendMessageW(hWnd, EM_GETMARGINS, 0, 0);
	if (pArgInf[1].m_pInt)
		*pArgInf[1].m_pInt = LOWORD(dwRet);
	if (pArgInf[2].m_pInt)
		*pArgInf[2].m_pInt = HIWORD(dwRet);
}
static ARG_INFO s_ArgsGetMargins[] =
{
	{
		/*name*/    "接收左边距变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收右边距变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditGetMargins = { {
		/*ccname*/  "取边距",
		/*egname*/  "GetMargins",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetMargins),
		/*arg lp*/  s_ArgsGetMargins,
	} , libstl_Edit_GetMargins ,"libstl_Edit_GetMargins" };
///////////////////////////////////
EXTERN_C void libstl_Edit_GetRect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	RECT rc;
	DWORD dwRet = SendMessageW(hWnd, EM_GETRECT, 0, (LPARAM)&rc);
	if (pArgInf[1].m_pInt)
		*pArgInf[1].m_pInt = rc.left;
	if (pArgInf[2].m_pInt)
		*pArgInf[2].m_pInt = rc.top;
	if (pArgInf[3].m_pInt)
		*pArgInf[3].m_pInt = rc.right - rc.left;
	if (pArgInf[4].m_pInt)
		*pArgInf[4].m_pInt = rc.bottom - rc.top;
}
static ARG_INFO s_ArgsGetRect[] =
{
	{
		/*name*/    "接收横向位置变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收纵向位置变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收宽度变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收高度变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditGetRect = { {
		/*ccname*/  "取显示矩形",
		/*egname*/  "GetRect",
		/*explain*/ "返回字符位置，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetRect),
		/*arg lp*/  s_ArgsGetRect,
	} , libstl_Edit_GetRect ,"libstl_Edit_GetRect" };
///////////////////////////////////
EXTERN_C void libstl_Edit_LineFromChar(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_LINEFROMCHAR, pArgInf[1].m_int, 0);
}
static ARG_INFO s_ArgsLineFromChar[] =
{
	{
		/*name*/    "字符索引",
		/*explain*/ "若该参数设为-1，则返回当前光标所在行，或者返回选定内容所在行（如果有）",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};
FucInfo Fn_EditLineFromChar = { {
		/*ccname*/  "字符位置到行数",
		/*egname*/  "LineFromChar",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsLineFromChar),
		/*arg lp*/  s_ArgsLineFromChar,
	} , libstl_Edit_LineFromChar ,"libstl_Edit_LineFromChar" };
///////////////////////////////////
EXTERN_C void libstl_Edit_LineIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, EM_LINEINDEX, pArgInf[1].m_int, 0);
}
static ARG_INFO s_ArgsLineIndex[] =
{
	{
		/*name*/    "行索引",
		/*explain*/ "若该参数设为-1，则指定当前光标所在行",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};
FucInfo Fn_EditLineIndex = { {
		/*ccname*/  "取某行第一字符位置",
		/*egname*/  "LineIndex",
		/*explain*/ "失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsLineIndex),
		/*arg lp*/  s_ArgsLineIndex,
	} , libstl_Edit_LineIndex ,"libstl_Edit_LineIndex" };
///////////////////////////////////
EXTERN_C void libstl_Edit_Scroll(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = HIWORD(SendMessageW(hWnd, EM_SCROLL, pArgInf[1].m_int, 0));
}
static ARG_INFO s_ArgsScroll[] =
{
	{
		/*name*/    "滚动操作",
		/*explain*/ "0 - 向上一行   1 - 向下一行   2 - 向上一页   3 - 向下一页",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};
FucInfo Fn_EditScroll = { {
		/*ccname*/  "滚动",
		/*egname*/  "Scroll",
		/*explain*/ "失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsScroll),
		/*arg lp*/  s_ArgsScroll,
	} , libstl_Edit_Scroll ,"libstl_Edit_Scroll" };
///////////////////////////////////
EXTERN_C void libstl_Edit_LineScroll(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = HIWORD(SendMessageW(hWnd, EM_LINESCROLL, pArgInf[1].m_int, pArgInf[2].m_int));
}
static ARG_INFO s_ArgsLineScroll[] =
{
	{
		/*name*/    "水平滚动字符数",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "垂直滚动行数",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditLineScroll = { {
		/*ccname*/  "滚动行",
		/*egname*/  "LineScroll",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsLineScroll),
		/*arg lp*/  s_ArgsLineScroll,
	} , libstl_Edit_LineScroll ,"libstl_Edit_LineScroll" };
///////////////////////////////////
EXTERN_C void libstl_Edit_PosFromChar(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwRet = SendMessageW(hWnd, EM_LINESCROLL, pArgInf[1].m_int, 0);
	if (pArgInf[2].m_pInt)
		*pArgInf[2].m_pInt = LOWORD(dwRet);
	if (pArgInf[3].m_pInt)
		*pArgInf[3].m_pInt = HIWORD(dwRet);
}
static ARG_INFO s_ArgsPosFromChar[] =
{
	{
		/*name*/    "字符索引",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	},
	{
		/*name*/    "接收横向位置变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收纵向位置变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditPosFromChar = { {
		/*ccname*/  "取字符坐标",
		/*egname*/  "PosFromChar",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsPosFromChar),
		/*arg lp*/  s_ArgsPosFromChar,
	} , libstl_Edit_PosFromChar ,"libstl_Edit_PosFromChar" };
///////////////////////////////////
EXTERN_C void libstl_Edit_ReplaceSel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwRet = SendMessageW(hWnd, EM_REPLACESEL, pArgInf[2].m_int, (LPARAM)(pArgInf[1].m_pBin + 8));
}
static ARG_INFO s_ArgsReplaceSel[] =
{
	{
		/*name*/    "用作替换的文本",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	},
	{
		/*name*/    "能否撤销",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ FALSE,
		/*state*/   AS_HAS_DEFAULT_VALUE,
	}
};
FucInfo Fn_EditReplaceSel = { {
		/*ccname*/  "替换选中文本",
		/*egname*/  "ReplaceSel",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsReplaceSel),
		/*arg lp*/  s_ArgsReplaceSel,
	} , libstl_Edit_ReplaceSel ,"libstl_Edit_ReplaceSel" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SetMargins(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwMask = 0u;
	if (pArgInf[1].m_dtDataType != _SDT_NULL)
	{
		if (pArgInf[1].m_int < 0)
			pArgInf[1].m_int = EC_USEFONTINFO;
		dwMask |= EC_LEFTMARGIN;
	}

	if (pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		if (pArgInf[2].m_int < 0)
			pArgInf[2].m_int = EC_USEFONTINFO;
		dwMask |= EC_RIGHTMARGIN;
	}

	SendMessageW(hWnd, EM_SETMARGINS, pArgInf[1].m_int, MAKELPARAM(pArgInf[1].m_int, pArgInf[2].m_int));
}
static ARG_INFO s_ArgsSetMargins[] =
{
	{
		/*name*/    "左边距",
		/*explain*/ "空为不设置，-1为设为默认",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "右边距",
		/*explain*/ "空为不设置，-1为设为默认",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditSetMargins = { {
		/*ccname*/  "置边距",
		/*egname*/  "SetMargins",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetMargins),
		/*arg lp*/  s_ArgsSetMargins,
	} , libstl_Edit_SetMargins ,"libstl_Edit_SetMargins" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SetModify(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	SendMessageW(hWnd, EM_SETMODIFY, pArgInf[1].m_bool, 0);
}
static ARG_INFO s_ArgsSetModify[] =
{
	{
		/*name*/    "是否已修改",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   0,
	}
};
FucInfo Fn_EditSetModify = { {
		/*ccname*/  "置修改标志",
		/*egname*/  "SetModify",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetModify),
		/*arg lp*/  s_ArgsSetModify,
	} , libstl_Edit_SetModify ,"libstl_Edit_SetModify" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SetRect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	if (pArgInf[1].m_dtDataType == _SDT_NULL && pArgInf[2].m_dtDataType == _SDT_NULL &&
		pArgInf[3].m_dtDataType == _SDT_NULL && pArgInf[4].m_dtDataType == _SDT_NULL)
	{
		SendMessageW(hWnd, EM_SETRECT, 0, NULL);
		return;
	}
	RECT rc{ pArgInf[1].m_int,  pArgInf[2].m_int,  pArgInf[3].m_int,  pArgInf[4].m_int };
	SendMessageW(hWnd, EM_SETRECT, 0, (LPARAM)&rc);
}
static ARG_INFO s_ArgsSetRect[] =
{
	{
		/*name*/    "左边",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "右边",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "宽度",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "高度",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditSetRect = { {
		/*ccname*/  "置显示矩形",
		/*egname*/  "SetRect",
		/*explain*/ "若四个参数全为空，则将显示矩形置回默认",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetRect),
		/*arg lp*/  s_ArgsSetRect,
	} , libstl_Edit_SetRect ,"libstl_Edit_SetRect" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SetTabStop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

	if (pArgInf[1].m_dtDataType == _SDT_NULL)
	{
		SendMessageW(hWnd, EM_SETTABSTOPS, 0, 0);
		return;
	}
	int cAry = elibstl::get_array_count(pArgInf[1].m_pAryData);
	if (!cAry)
	{
		SendMessageW(hWnd, EM_SETTABSTOPS, 0, 0);
		return;
	}
	else if (cAry == 1)
	{
		SendMessageW(hWnd, EM_SETTABSTOPS, 1, *(int*)((BYTE*)pArgInf[1].m_pAryData + 8));
		return;
	}
	else
	{
		SendMessageW(hWnd, EM_SETTABSTOPS, cAry, (LPARAM)((BYTE*)pArgInf[1].m_pAryData + 8));
		return;
	}
}
static ARG_INFO s_ArgsSetTabStop[] =
{
	{
		/*name*/    "制表位数组",
		/*explain*/ "以对话框单位表示的制表位数组，若此参数设为空，则将制表位置回默认",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA | AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_EditSetTabStop = { {
		/*ccname*/  "置制表位",
		/*egname*/  "SetTabStop",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetTabStop),
		/*arg lp*/  s_ArgsSetTabStop,
	} , libstl_Edit_SetTabStop ,"libstl_Edit_SetTabStop" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SetBallloonTip(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	EDITBALLOONTIP ebt;
	ebt.cbStruct = sizeof(EDITBALLOONTIP);

	if (pArgInf[1].m_dtDataType == _SDT_NULL)
		ebt.pszTitle = NULL;
	else if (!elibstl::get_array_count(pArgInf[1].m_pBin))
		ebt.pszTitle = NULL;
	else
		ebt.pszTitle = (PCWSTR)(pArgInf[1].m_pBin + 8);

	if (pArgInf[2].m_dtDataType == _SDT_NULL)
		ebt.pszText = NULL;
	else if (!elibstl::get_array_count(pArgInf[2].m_pBin))
		ebt.pszText = NULL;
	else
		ebt.pszText = (PCWSTR)(pArgInf[2].m_pBin + 8);

	ebt.ttiIcon = pArgInf[3].m_int;

	pRetData->m_bool = SendMessageW(hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM)&ebt);
}
static ARG_INFO s_ArgsSetBallloonTip[] =
{
	{
		/*name*/    "标题",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "内容",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "图标类型",
		/*explain*/ "0 - 无图标   1 - 信息图标   2 - 警告图标   3 - 错误图标   4 - 大信息图标   5 - 大警告图标   6 - 大错误图标，默认0",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_HAS_DEFAULT_VALUE,
	}
};
FucInfo Fn_EditSetBallloonTip = { {
		/*ccname*/  "弹出气球提示",
		/*egname*/  "SetBallloonTip",
		/*explain*/ "该函数需要在清单中指定Comctl6.0，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetBallloonTip),
		/*arg lp*/  s_ArgsSetBallloonTip,
	} , libstl_Edit_SetBallloonTip ,"libstl_Edit_SetBallloonTip" };
///////////////////////////////////
EXTERN_C void libstl_Edit_Undo(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = SendMessageW(hWnd, WM_UNDO, 0, 0);

}
FucInfo Fn_EditUndo = { {
		/*ccname*/  "撤销",
		/*egname*/  "Undo",
		/*explain*/ "失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_Undo ,"libstl_Edit_Undo" };
///////////////////////////////////
EXTERN_C void libstl_Edit_Paste(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	SendMessageW(hWnd, WM_PASTE, 0, 0);
}
FucInfo Fn_EditPaste = { {
		/*ccname*/  "粘贴",
		/*egname*/  "Paste",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_Paste ,"libstl_Edit_Paste" };
///////////////////////////////////
EXTERN_C void libstl_Edit_Copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	SendMessageW(hWnd, WM_COPY, 0, 0);
}
FucInfo Fn_EditCopy = { {
		/*ccname*/  "复制",
		/*egname*/  "Copy",
		/*explain*/ "失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_Copy ,"libstl_Edit_Copy" };
///////////////////////////////////
EXTERN_C void libstl_Edit_SelAll(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	SendMessageW(hWnd, EM_SETSEL, 0, -1);
}
FucInfo Fn_EditSelAll = { {
		/*ccname*/  "全选",
		/*egname*/  "SelAll",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_Edit_SelAll ,"libstl_Edit_SelAll" };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtEdit = {
	"编辑框W",//中文名称
	"EditW",//英文名称
	"Unicode编辑框",//说明
	ARRAYSIZE(s_Cmd_Edit),//命令数量
	s_Cmd_Edit,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	104,//资源ID
	ARRAYSIZE(s_Event_Edit),
	s_Event_Edit,
	ARRAYSIZE(s_Member_Edit),//属性数
	s_Member_Edit,//属性指针
	libstl_GetInterface_EditW,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END