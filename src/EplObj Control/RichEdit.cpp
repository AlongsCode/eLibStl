#include "EcontrolHelp.h"
#include<Richedit.h>
#pragma comment (lib,"Crypt32.lib")

#define SCID_RICHEDIT		20230527'01u
#define SCID_RICHEDITPARENT	20230527'02u
#define DATA_VER_RICHEDIT_1	1
struct ERICHEDITDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留
	COLORREF crBK;			// 编辑框背景色
	BOOL bMultiLine;		// 是否允许多行
	BOOL bAutoWrap;			// 自动换行
	BOOL bOnlyRead;			//是否只读
	BOOL bHideSel;          //隐藏选择
	BOOL iScrollBar;		// 滚动条
	BOOL bAutoDetectURL;	// 自动检测链接
	INT RevocationTimes;    //撤销次数
	INT iMaxLen;			// 最大允许长度
	INT iSelPos;			// 起始选择位置
	INT iSelNum;			// 被选择字符数
};
ESTL_NAMESPACE_BEGIN
class CRichEdit :public CCtrlBase
{
	SUBCLASS_MGR_DECL(CRichEdit)
public:
	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CRichEdit(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}
	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0://内容格式
			break;
		case 1:// 内容
			p->SetTextA(pPropertyVaule->m_szText);
			break;
		case 2:// 内容W
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 3:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 4:// 编辑框背景颜色
			break;
		case 5:// 是否允许多行
			p->SetMultiLine(pPropertyVaule->m_bool);
			return TRUE;
		case 6:// 自动换行
			return p->SetAutoWrap(pPropertyVaule->m_bool);
		case 7://只读
			p->SetOnlyRead(pPropertyVaule->m_bool);
			break;
		case 8:// 隐藏选择
			p->SetHideSel(pPropertyVaule->m_bool);
			break;
		case 9:// 滚动条
			p->SetScrollBar(pPropertyVaule->m_int);
			break;
		case 10:// 自动检测链接
			p->SetAutoDetectURL(pPropertyVaule->m_bool);
			break;
		case 11:// 撤销次数
			p->SetUndoLimit(pPropertyVaule->m_int);
			break;

		case 12:// 最大允许长度
			p->SetMaxLen(pPropertyVaule->m_int);
			break;
		case 13:// 起始选择位置
			p->SetSelPos(pPropertyVaule->m_int);
			break;
		case 14:// 被选择字符数
			p->SetSelNum(pPropertyVaule->m_int);
			break;
		case 15:// 被选择文本
			p->SetSelText((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		}

		return FALSE;
	}
	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0://内容格式
			break;
		case 1:// 内容
			pPropertyVaule->m_szText = p->GetTextA();
			break;
		case 2:// 内容W
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 4:// 编辑框背景颜色
			break;
		case 5:// 是否允许多行
			pPropertyVaule->m_bool = p->GetMultiLine();
			break;
		case 6:// 自动换行
			pPropertyVaule->m_bool = p->GetAutoWrap();
			break;
		case 7://只读
			pPropertyVaule->m_bool = p->GetOnlyRead();
			break;
		case 8:// 隐藏选择
			pPropertyVaule->m_bool = p->GetHideSel();
			break;
		case 9:// 滚动条
			pPropertyVaule->m_int = p->GetScrollBar();
			break;
		case 10:// 自动检测链接
			pPropertyVaule->m_bool = p->GetAutoDetectURL();
			break;
		case 11:// 撤销次数
			pPropertyVaule->m_int = p->GetUndoLimit();
			break;
		case 12:// 是否允许多行
			pPropertyVaule->m_int = p->GetMaxLen();
			break;
		case 13:// 起始选择位置
			pPropertyVaule->m_int = p->GetSelPos();
			break;
		case 14:// 被选择字符数
			pPropertyVaule->m_int = p->GetSelNum();
			break;
		case 15:// 被选择文本
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetSelText((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		}

		return TRUE;
	}
	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		PWSTR psz;
		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 2:// 内容W
		{
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		break;
		}
		return FALSE;
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

public:

	/*回调函数*/
	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = reinterpret_cast <CRichEdit*>(dwRefData);
		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

public:
	CRichEdit(STD_ECTRL_CREATE_ARGS)
	{
		static	HMODULE hRichEditDLL = NULL;
		if (!hRichEditDLL)
		{
			hRichEditDLL = LoadLibraryW(L"MSFTEDIT.DLL");
			if (!hRichEditDLL)
			{
				TaskDialog(GetActiveWindow(), NULL, L"警告", L"该系统并不支持!", L"B老旧系统跑啥富文本框", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
				return;
			}
		}

		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);


		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ERICHEDITDATA));
		}
		else
		{
			m_Info0.iFrame = 1;
			m_Info.RevocationTimes = 1;
			m_Info.bAutoWrap = TRUE;
			m_Info.bMultiLine = TRUE;
			m_Info.bAutoDetectURL = TRUE;
		}
		m_Info.iVer = DATA_VER_RICHEDIT_1;

		DWORD dwEDStyle;
		if (m_Info.bMultiLine)
			dwEDStyle = ES_MULTILINE | ES_AUTOVSCROLL | (m_Info.bAutoWrap ? ES_AUTOHSCROLL : 0);
		else
			dwEDStyle = ES_AUTOHSCROLL;

		dwStyle |= dwEDStyle;
		// 创建 RichEdit 控件
		m_hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, m_pszTextW, dwStyle | WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | EM_PASTESPECIAL,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);

		if (!m_hWnd)
		{
			TaskDialog(GetActiveWindow(), NULL, L"警告", L"创建窗口失败", L"B老旧系统跑啥富文本框", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			return;
		}

		m_SM.OnCtrlCreate(this);
		InitBase0(pAllData);
		SetScrollBar(m_Info.iScrollBar);/*滚动条*/
		SetHideSel(m_Info.bHideSel);/*隐藏选择*/
		SetAutoDetectURL(m_Info.bAutoDetectURL);/*超链接*/
		SetAutoWrap(m_Info.bAutoWrap);/*自定换行*/
		SetMultiLine(m_Info.bMultiLine);/*是否允许多行*/
		SetMaxLen(m_Info.iMaxLen);/*最大长度*/
		SetOnlyRead(m_Info.bOnlyRead);/*只读*/
		SetUndoLimit(m_Info.RevocationTimes);/*最大撤销次数*/
		FrameChanged();
	}

	~CRichEdit()
	{
		delete[] m_pszSelText;
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
	eStlInline void SetUndoLimit(int limit)
	{
		m_Info.RevocationTimes = limit;
		m_Info.RevocationTimes = SendMessageW(m_hWnd, EM_SETUNDOLIMIT, m_Info.RevocationTimes, 0);
	}
	eStlInline int GetUndoLimit() const
	{
		return m_Info.RevocationTimes;
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
	eStlInline void SetAutoDetectURL(BOOL bAutoDetect)
	{
		m_Info.bAutoDetectURL = bAutoDetect;
		SendMessageW(m_hWnd, EM_AUTOURLDETECT, m_Info.bAutoDetectURL, NULL);
	}
	eStlInline BOOL GetAutoDetectURL()
	{
		m_Info.bAutoDetectURL = SendMessageW(m_hWnd, EM_GETAUTOURLDETECT, 0, 0);
		return m_Info.bAutoDetectURL;
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
	}

	eStlInline BOOL GetMultiLine()
	{
		if (m_bInDesignMode)
			return m_Info.bMultiLine;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), ES_MULTILINE);
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
	BOOL SetAutoWrap(BOOL bAutoWrap)
	{
		m_Info.bAutoWrap = bAutoWrap;
		return GetMultiLine();
	}

	eStlInline BOOL GetAutoWrap()
	{
		return m_Info.bAutoWrap;
	}
	eStlInline void SetSelNum(int iSelNum)
	{
		m_Info.iSelNum = iSelNum;
		DWORD dwStart;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, NULL);
		SendMessageW(m_hWnd, EM_SETSEL, dwStart, dwStart + iSelNum);
	}
	BOOL GetOnlyRead() {
		return m_Info.bOnlyRead;
	}
	void SetOnlyRead(BOOL ReadOnly) {
		m_Info.bOnlyRead = ReadOnly;
		SendMessage(m_hWnd, EM_SETREADONLY, m_Info.bOnlyRead, 0);

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
	///*追加文本*/
	//void AppendText(const wchar_t* text) const
	//{
	//	int length = GetWindowTextLengthW(m_hWnd);
	//	SendMessageW(m_hWnd, EM_SETSEL, length, length);
	//	SendMessageW(m_hWnd, EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(text));
	//}
	///*添加图片*/
	//void AppendImage()
	//{
	//	if (!m_isInit || m_hWnd == NULL)
	//		return;
	//	// 在富文本框中插入剪贴板中的图像
	//	SendMessageW(m_hWnd, WM_PASTE, 0, 0);

	//}


private:

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(ERICHEDITDATA), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ERICHEDITDATA));

		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	///*置选中区域格式*/
	//bool SetSelectionCharacterFormat(const CHARFORMAT2W& format)   const
	//{
	//	CHARFORMAT2W cf;
	//	cf.cbSize = sizeof(CHARFORMAT2W);
	//	cf.dwMask = CFM_FACE | CFM_EFFECTS | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET;
	//	auto len = lstrlenW(format.szFaceName);
	//	if (len > LF_FACESIZE - 1)
	//	{
	//		len = LF_FACESIZE - 1;
	//	}
	//	wcsncpy_s(cf.szFaceName, format.szFaceName, len);
	//	cf.szFaceName[len] = L'\0';
	//	cf.dwEffects = format.dwEffects & ~CFE_AUTOCOLOR;
	//	cf.yHeight = format.yHeight;
	//	cf.yOffset = format.yOffset;
	//	cf.crTextColor = format.crTextColor;
	//	cf.bCharSet = format.bCharSet;
	//	cf.bPitchAndFamily = format.bPitchAndFamily;
	//	return SendMessageW(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&cf)) != 0;
	//}
	///*置选中区域*/
	//bool SetSelection(int startPosition, int endPosition)   const
	//{
	//	CHARRANGE range;
	//	range.cpMin = startPosition;
	//	range.cpMax = endPosition;
	//	return SendMessageW(m_hWnd, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&range)) != 0;
	//}
	ERICHEDITDATA m_Info{ 0 };
	PWSTR m_pszSelText = NULL;
};


SUBCLASS_MGR_INIT(CRichEdit, SCID_RICHEDITPARENT, SCID_RICHEDIT)
ESTL_NAMESPACE_END



EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_RichEdit(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CRichEdit::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CRichEdit::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CRichEdit::ENotify;
	}
	return NULL;
}


ESTL_NAMESPACE_BEGIN


static UNIT_PROPERTY s_Member_RichEdit[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*0*/{"内容格式","TextFormat","本属性指定对文本框的内容进行读写时所使用的文本格式。具体格式的组合看开发文档。",UD_PICK_INT,_PROP_OS(OS_ALL),"纯文本\0""RTF丰富文本\0""无对象RTF丰富文本\0""\0"},
	/*1*/{"内容","Text","本属性所使用的文本格式由“内容格式”属性决定",UD_TEXT,_PROP_OS(OS_ALL),NULL},
	/*2*/{"内容W", "TextW", "本属性所使用的文本格式由“内容格式”属性决定", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*3*/{"边框","Style","",UD_PICK_INT,_PROP_OS(OS_ALL),"无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*4*/{"背景颜色","BackColor","文本框的背景颜色",UD_COLOR_BACK,_PROP_OS(OS_ALL),NULL},
	/*5*/{"是否允许多行","AllowMultiLines","本属性设置文本框是否允许输入多行文本",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*6*/{"自动换行","WrapMode","本属性设置文本框是否支持自动换行",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*7*/{"只读","ReadOnly","本属性设置编辑框是否只能读取而不能写入",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*8*/{"隐藏选择","HideSel","本属性指定失去输入焦点后是否还显示当前被选择的区域",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*9*/{"滚动条", "ScrollBar", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无\0""横向滚动条\0""纵向滚动条\0""横向及纵向滚动条\0""\0"},
	/*10*/{"自动检测链接","AutoURLDetect","自动检测文档里的URL链接，例如：HTTP:\\、ftp:\\和mailto:开头的关键字",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*11*/{"最大允许撤消次数","MultileveUndo","返回或设置可以撤消的次数。占用系统资源，不可设置太多",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*12*/{"最大允许长度","MaxAllowLength","本属性设置最大允许输入到文本框中的字符数目，如为0则输入字符数目不受限制",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*13*/{"起始选择位置","SelStart","返回或设置所选择文本的起始点；0 为位置 1 ，1 为位置 2，如此类推。如果没有文本被选中， 则提供当前光标位置。如果设置位置时使用值 -1，则将当前光标位置移动到文本尾部",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*14*/{"被选择字符数","SelLength","返回或设置所选择的字符数。如果设置字符数时使用值 -1，则选择编辑框内的所有字符",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*15*/{"被选择文本","SelText","返回或替换当前所选择的文本，文本格式由“内容格式”属性决定",UD_CUSTOMIZE,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*16*/{"是否已更改","Modified","读取本属性可获知文本框的内容是否已被用户手工更改，运行时写入本属性可以设置其值",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*17*/{"字体名称","FontName","在编辑时，设置和取得被选择文本的字体名称。如果字体混合选中,则取得光标位置的字体名称",UD_TEXT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*18*/{"字体大小","FontSize","在编辑时，设置和取得被选择文本的字体大小。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*19*/{"文本颜色","ForeColor","在编辑时，设置和取得被选择文本的颜色值。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*20*/{"文本底色","FontBackColor","在编辑时，设置和取得被选择文本的背景颜色值。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*21*/{"粗体","Bold","在编辑时，被选择文本是否为粗体。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*22*/{"斜体","Italic","在编辑时，被选择文本是否为斜体。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*23*/{"下划线","Underline","在编辑时，被选择文本是否为下划线。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*24*/{"删除线","StrikeThrough","在编辑时，被选择文本是否为删除线。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*25*/{"上标","Superscript","在编辑时，被选择文本是否为上标。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*26*/{"下标","Subscript","在编辑时，被选择文本是否为下标。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*27*/{"纵向偏移","YOffset","在编辑时，设置和取得被选择文本块的纵向位置，正值变上标，负值变下标，单位为像素。如果混合选 中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*28*/{"字体蔟","PitchAndFamily","LOGFONT结构的lfPitchAndFamily成员",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*29*/{"字符集","CharSet","LOGFONT结构的lfCharSet成员",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*30*/{"对齐方式","Alignment","选区的对齐方式，可以为以下常量值之一： 1、#文本居左；2、#文本居右；3、#文本居中。",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*31*/{"首行缩进","StartIndent","段落相对于文本框左边框的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*32*/{"右边缩进","RightIndent","段落右边相对于文本框右边框的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*33*/{"非首行缩进","Indent","指定段落中所有非首行相对于首行的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*34*/{"制表位宽度","TopStops","TAB键的制表位宽度，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*35*/{"段前间距","SpaceBefore","段落的上面间距，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*36*/{"段后间距","SpaceAfter","段落的下面间距，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*37*/{"行间距","LineSpacing","行与行之间的距离，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*38*/{"背景图片","BackImage","背景图片数据，支持BMP、JPG和GIF等格式的图片",UD_PIC,UW_IS_HIDED | _PROP_OS(OS_ALL),NULL},
	/*39*/{"显示方式","ShowStyle","如果设定了图片，本属性指定背景图片的显示方式",UD_PICK_INT,UW_HAS_INDENT | UW_IS_HIDED | _PROP_OS(OS_ALL),"图片居上\0""图片缩放\0""图片居中\0""图片平铺\0""\0"},
	/*40*/{"透明度","Alpha","如果设定了图片，本属性指定背景图片的透明度，底色为背景颜色属性设置,0~255的值，0为全透明，255为 不透明",UD_INT,UW_HAS_INDENT | UW_IS_HIDED | _PROP_OS(OS_ALL),NULL},
	/*41*/{"背景透明","BgTransparent","将文本框的背景设置为透明，可以看见底下组件的外表，如果是窗口的可设置底图，或是画板或 是图片框上的图片，都可以做为文本框的编辑底图。",UD_BOOL,_PROP_OS(OS_ALL),NULL} };

LIB_DATA_TYPE_INFO CtRichEdit = {
	"富文本框",//中文名称
	"RichEdit",//英文名称
	"",//说明
	0,//命令数量
	0,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_UPDOWN_EX,//资源ID
	0,
	0,//事件
	ARRAYSIZE(s_Member_RichEdit),//属性数
	s_Member_RichEdit,//属性指针
	libstl_GetInterface_RichEdit,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END