#include"EcontrolHelp.h"

#include <unordered_map>

#pragma warning(disable:4996)

#define SCID_PUSHBTN		20230425'01u
#define SCID_PUSHBTNPARENT	20230425'02u
#define SCID_CHECKBTN		20230425'03u
#define SCID_CHECKBTNPARENT	20230425'04u
#define SCID_CMDLINK		20230425'05u
#define SCID_CMDLINKPARENT	20230425'06u


// 基础数据
/*
* 版本1数据布局：
* EBUTTONDATA结构
* 图片
* 文本
*/
#define DATA_VER_BTN_1	1
struct EBUTTONDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int algH;				// 横向对齐
	int algV;				// 纵向对齐
	BOOL bShowTextAndImage;	// 是否同时显示图片和文本
	LOGFONTA Font;			// 字体
	int cchText;			// 文本长度，仅用于保存信息
	PSTR pszTextA;			// 标题A
	PWSTR pszTextW;			// 标题W
	int cbPic;				// 图片字节流长度
	void* pPicData;			// 图片数据
};

// 普通按钮
/*
* 版本1数据布局：
* EBUTTONDATA_PUSHBTN结构
*/
#define DATA_VER_BTN_PUSHBTN_1	1
struct EBUTTONDATA_PUSHBTN
{
	int iVer;				// 版本
	DWORD dwReserved;		// 保留

	int iType;				// 类型
	int iDef;				// 是否默认
};

// 选择框（单选、复选、三态复选）
/*
* 版本1数据布局：
* EBUTTONDATA_CHECKBTN结构
*/
#define DATA_VER_BTN_CHECKBTN_1	1
struct EBUTTONDATA_CHECKBTN
{
	int iVer;				// 版本
	DWORD dwReserved;		// 保留

	int iType;				// 类型
	int iCheckState;		// 选择状态，0 未选中  1 选中  2 半选中（仅用于三态复选）
};

// 命令链接
/*
* 版本1数据布局：
* EBUTTONDATA_CMDLINK结构
* 注释文本
*/
#define DATA_VER_BTN_CMDLINK_1	1
struct EBUTTONDATA_CMDLINK
{
	int iVer;				// 版本
	DWORD dwReserved;		// 保留

	int cchNote;			// 注释文本长度
	PWSTR pszNote;			// 注释文本
};


/// <summary>
/// 按钮基类。
/// 请勿直接实例化此类
/// </summary>
class CButton
{
protected:
	// 易系统相关
	DWORD m_dwWinFormID = 0;
	DWORD m_dwUnitID = 0;
	BOOL m_blInDesignMode = FALSE;
	// 窗口句柄
	HWND m_hWnd = NULL;
	// 位图句柄
	HBITMAP m_hBitmap = NULL;
	// 字体句柄
	HFONT m_hFont = NULL;
	// 信息
	EBUTTONDATA m_Info{};

	SIZE_T InitBase(STD_ECTRL_CREATE_ARGS)
	{
		m_blInDesignMode = blInDesignMode;
		m_dwWinFormID = dwWinFormID;
		m_dwUnitID = dwUnitID;

		if (pAllData)
		{
			memcpy(&m_Info, pAllData, sizeof(EBUTTONDATA));
			BYTE* p = (BYTE*)pAllData + sizeof(EBUTTONDATA) + m_Info.cbPic;

			m_Info.pszTextW = NULL;
			if (m_Info.cchText)
				elibstl::DupStringForNewDeleteW(m_Info.pszTextW, (PCWSTR)p, m_Info.cchText);
			else
				elibstl::DupStringForNewDeleteW(m_Info.pszTextW, L"按钮W");
		}
		else
		{

			m_Info.pszTextW = NULL;
			elibstl::DupStringForNewDeleteW(m_Info.pszTextW, L"按钮W");
		}
		m_Info.pPicData = NULL;
		m_Info.pszTextA = elibstl::W2A(m_Info.pszTextW);

		m_Info.iVer = DATA_VER_BTN_1;

		return sizeof(EBUTTONDATA) + m_Info.cbPic + m_Info.cchText * sizeof(WCHAR);
	}

	void InitBase(PCVOID pAllData)
	{
		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);

		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + sizeof(EBUTTONDATA);
			SetPic(p, m_Info.cbPic);

			SetAlign(TRUE, m_Info.algH);
			SetAlign(FALSE, m_Info.algV);
			SetTextImageShowing(m_Info.bShowTextAndImage);
		}
		else
		{
			m_Info.Font = elibstl::GetEDefLOGFONT(m_hWnd);
			m_Info.algH = 1;
			m_Info.algV = 1;
		}

		SetFont(&m_Info.Font);

		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
	}

	eStlInline void Redraw()
	{
		InvalidateRect(m_hWnd, NULL, TRUE);
		UpdateWindow(m_hWnd);
	}
public:
	CButton()
	{

	}

	virtual ~CButton()
	{
		DeleteObject(m_hFont);
		DeleteObject(m_hBitmap);
		delete[] m_Info.pszTextA;
		delete[] m_Info.pszTextW;
		delete[] m_Info.pPicData;
	}

	/// <summary>
	/// 置标题A
	/// </summary>
	/// <param name="pszText">文本指针</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetTextA(PCSTR pszText)
	{
		if (m_blInDesignMode)
		{
			elibstl::DupStringForNewDeleteA(m_Info.pszTextA, pszText);
			delete[] m_Info.pszTextW;
			m_Info.pszTextW = elibstl::A2W(pszText);
		}
		return SetWindowTextA(m_hWnd, pszText);
	}

	/// <summary>
	/// 置标题W
	/// </summary>
	/// <param name="pszText">文本指针</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetTextW(PCWSTR pszText)
	{
		if (m_blInDesignMode)
		{
			elibstl::DupStringForNewDeleteW(m_Info.pszTextW, pszText);
			delete[] m_Info.pszTextA;
			m_Info.pszTextA = elibstl::W2A(pszText);
		}
		return SetWindowTextW(m_hWnd, pszText);
	}

	/// <summary>
	/// 置图片
	/// </summary>
	/// <param name="pPic">图片数据</param>
	/// <param name="cbSize">图片数据长度</param>
	void SetPic(void* pPic, int cbSize)
	{
		m_Info.cbPic = cbSize;
		delete[] m_Info.pPicData;
		if (m_hBitmap)
			DeleteObject(m_hBitmap);
		if (cbSize)
		{
			if (m_Info.bShowTextAndImage)
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
			else
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			m_Info.pPicData = new BYTE[cbSize];
			memcpy(m_Info.pPicData, pPic, cbSize);
			m_hBitmap = elibstl::make_hbit((BYTE*)pPic, cbSize);
			SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
		}
		else
		{
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
			m_Info.pPicData = NULL;
			m_hBitmap = NULL;
			SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, NULL);
		}
	}

	/// <summary>
	/// 取图片。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <param name="pcb">指向接收图片数据长度变量的指针</param>
	/// <returns>图片数据指针</returns>
	eStlInline BYTE* GetPic(int* pcb) const
	{
		*pcb = m_Info.cbPic;
		return (BYTE*)m_Info.pPicData;
	}

	/// <summary>
	/// 取文本W。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <returns>文本指针</returns>
	PWSTR GetTextW()
	{
		if (m_blInDesignMode)
		{
			int cch = GetWindowTextLengthW(m_hWnd);
			if (cch)
			{
				delete[] m_Info.pszTextW;
				m_Info.pszTextW = new WCHAR[cch + 1];
				GetWindowTextW(m_hWnd, m_Info.pszTextW, cch + 1);
			}
		}

		return m_Info.pszTextW;
	}

	/// <summary>
	/// 取文本A。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <returns>文本指针</returns>
	PCSTR GetTextA()
	{
		if (m_blInDesignMode)
		{
			int cch = GetWindowTextLengthA(m_hWnd);
			if (cch)
			{
				delete[] m_Info.pszTextA;
				m_Info.pszTextA = new CHAR[cch + 1];
				GetWindowTextA(m_hWnd, m_Info.pszTextA, cch + 1);
			}
		}

		return m_Info.pszTextA;
	}

	/// <summary>
	/// 置字体
	/// </summary>
	/// <param name="plf">LOGFONTA指针</param>
	eStlInline void SetFont(LOGFONTA* plf)
	{
		if (m_hFont)
			DeleteObject(m_hFont);

		m_Info.Font = *plf;
		m_hFont = CreateFontIndirectA(plf);
		SendMessageW(m_hWnd, WM_SETFONT, (WPARAM)m_hFont, TRUE);
	}

	/// <summary>
	/// 取字体
	/// </summary>
	/// <returns>LOGFONTA指针，为迎合易语言回调参数类型而设为BYTE*，不要释放。</returns>
	eStlInline BYTE* GetFont() const
	{
		return (BYTE*)&m_Info.Font;
	}

	/// <summary>
	/// 置图片文本同时显示
	/// </summary>
	/// <param name="bShowTextAndImage">是否同时显示</param>
	void SetTextImageShowing(BOOL bShowTextAndImage)
	{
		m_Info.bShowTextAndImage = bShowTextAndImage;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
		if (bShowTextAndImage)
			dwStyle &= (~(BS_BITMAP));
		else
			dwStyle |= BS_BITMAP;
		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
	}

	/// <summary>
	/// 取图片文本同时显示
	/// </summary>
	/// <returns>是否同时显示</returns>
	eStlInline BOOL GetTextImageShowing() const
	{
		return m_Info.bShowTextAndImage;
	}

	/// <summary>
	/// 置对齐
	/// </summary>
	/// <param name="bHAlign">是否水平对齐</param>
	/// <param name="iAlign">对齐，参见属性定义</param>
	void SetAlign(BOOL bHAlign, int iAlign)
	{
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
		if (bHAlign)
		{
			dwStyle &= (~(BS_LEFT | BS_CENTER | BS_RIGHT));
			m_Info.algH = iAlign;
			switch (iAlign)
			{
			case 0: dwStyle |= BS_LEFT; break;
			case 1: dwStyle |= BS_CENTER; break;
			case 2: dwStyle |= BS_RIGHT; break;
			}
		}
		else
		{
			dwStyle &= (~(BS_TOP | BS_VCENTER | BS_BOTTOM));
			m_Info.algV = iAlign;
			switch (iAlign)
			{
			case 0: dwStyle |= BS_TOP; break;
			case 1: dwStyle |= BS_VCENTER; break;
			case 2: dwStyle |= BS_BOTTOM; break;
			}
		}
		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		Redraw();
	}

	/// <summary>
	/// 取对齐
	/// </summary>
	/// <param name="bHAlign">是否水平对齐</param>
	/// <returns>对齐，参见属性定义</returns>
	eStlInline int GetAlign(BOOL bHAlign) const
	{
		if (bHAlign)
			return m_Info.algH;
		else
			return m_Info.algV;
	}

	/// <summary>
	/// 平面化基类数据。
	/// 扩展数据应在其后附加
	/// </summary>
	/// <returns></returns>
	eStlInline HGLOBAL FlattenInfoBase(SIZE_T cbExtra = 0u, SIZE_T* pcbBaseData = NULL)
	{
		BYTE* p;
		auto pszText = GetTextW();
		m_Info.cchText = wcslen(pszText);
		int cbText = m_Info.cchText * sizeof(WCHAR);
		SIZE_T cbMem = sizeof(EBUTTONDATA) + m_Info.cbPic + cbText;
		if (pcbBaseData)
			*pcbBaseData = cbMem;
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cbMem + cbExtra);
		if (!hGlobal)
			goto FailAlloc;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto FailLock;
		// 结构
		memcpy(p, &m_Info, sizeof(EBUTTONDATA));
		// 图片
		p += sizeof(EBUTTONDATA);
		memcpy(p, m_Info.pPicData, m_Info.cbPic);
		//// 文本
		p += m_Info.cbPic;
		memcpy(p, pszText, cbText);
		// 
		GlobalUnlock(hGlobal);
		return hGlobal;
	FailLock:
		GlobalFree(hGlobal);
	FailAlloc:
		return NULL;
	}

	/// <summary>
	/// 平面化数据。
	/// 用于向易语言返回所有属性。
	/// 内存布局参见文件首部数据版本定义处
	/// </summary>
	/// <returns></returns>
	virtual HGLOBAL FlattenInfo() { assert(FALSE); return NULL; }

	/// <summary>
	/// 取窗口句柄
	/// </summary>
	/// <returns>窗口句柄</returns>
	eStlInline HWND GetHWND() const
	{
		return m_hWnd;
	}
};


class CPushButton :public CButton
{
	SUBCLASS_MGR_DECL(CPushButton)
private:
	EBUTTONDATA_PUSHBTN m_InfoEx{};

	/// <summary>
	/// 被单击
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	/// <summary>
	/// 下拉箭头被单击
	/// </summary>
	eStlInline void OnDropDownClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 1);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	/// <summary>
	/// 父窗口子类化过程
	/// </summary>
	SUBCLASS_PARENT_FNHEAD
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (m_CtrlSCInfo.count((HWND)lParam))
				m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_NOTIFY:
		{
			auto p = (NMHDR*)lParam;
			if (p->code == BCN_DROPDOWN)
				if (m_CtrlSCInfo.count(p->hwndFrom))
					m_CtrlSCInfo[p->hwndFrom]->OnDropDownClick();
		}
		break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		SUBCLASS_RET_DEFPROC;
	}

	/// <summary>
	/// 按钮窗口子类化过程
	/// </summary>
	SUBCLASS_CTRL_FNHEAD
	{
		auto p = (CPushButton*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			SUBCLASS_RET_DEFPROC;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		SUBCLASS_RET_DEFPROC;
	}

public:
	CPushButton(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(STD_ECTRL_CREATE_REAL_ARGS);

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_PUSHBTN));
		m_InfoEx.iVer = DATA_VER_BTN_PUSHBTN_1;

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_Info.pszTextW, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | BS_PUSHBUTTON,
			x, y, cx, cy, hParent, (HMENU)nId, GetModuleHandleW(NULL), NULL);

		InitBase(pAllData);
		SetDef(m_InfoEx.iDef);

		m_SM.OnCtrlCreate(this);
	}

	/// <summary>
	/// 置类型
	/// </summary>
	/// <param name="iType">类型，参见属性定义</param>
	void SetType(int iType)
	{
		m_InfoEx.iType = iType;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_PUSHBUTTON | BS_SPLITBUTTON | BS_DEFPUSHBUTTON | BS_DEFSPLITBUTTON));

		switch (iType)
		{
		case 0:
			dwStyle |= (m_InfoEx.iDef ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON);
			break;
		case 1:
			dwStyle |= (m_InfoEx.iDef ? BS_DEFSPLITBUTTON : BS_SPLITBUTTON);
			break;
		}

		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		Redraw();
	}

	/// <summary>
	/// 取类型
	/// </summary>
	/// <returns>类型，参见属性定义</returns>
	eStlInline int GetType() const
	{
		return m_InfoEx.iType;
	}

	/// <summary>
	/// 置是否默认
	/// </summary>
	/// <param name="iDef">是否默认，参见属性定义</param>
	void SetDef(int iDef)
	{
		m_InfoEx.iDef = iDef;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_DEFPUSHBUTTON | BS_DEFSPLITBUTTON | BS_PUSHBUTTON | BS_SPLITBUTTON));
		if (iDef)
			if (m_InfoEx.iType)
				dwStyle |= BS_DEFSPLITBUTTON;
			else
				dwStyle |= BS_DEFPUSHBUTTON;
		else
			if (m_InfoEx.iType)
				dwStyle |= BS_SPLITBUTTON;
			else
				dwStyle |= BS_PUSHBUTTON;

		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
	}

	/// <summary>
	/// 取是否默认
	/// </summary>
	/// <returns>是否默认，参见属性定义</returns>
	eStlInline int GetDef() const
	{
		return m_InfoEx.iDef;
	}

	/// <summary>
	/// 平面化数据。
	/// 用于向易语言获取所有属性提供数据。
	/// 内存布局参见文件首部数据版本定义处
	/// </summary>
	/// <returns></returns>
	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase(sizeof(EBUTTONDATA_PUSHBTN), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_InfoEx, sizeof(EBUTTONDATA_PUSHBTN));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}


	static HUNIT WINAPI ECreate(LPBYTE pAllPropertyData, INT nAllPropertyDataSize, DWORD dwStyle, HWND hParentWnd, UINT uID, HMENU hMenu,
		INT x, INT y, INT cx, INT cy, DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL blInDesignMode
	)
	{
		auto pButton = new CPushButton(pAllPropertyData, nAllPropertyDataSize, dwStyle, x, y, cx, cy,
			hParentWnd, uID, blInDesignMode, dwWinFormID, dwUnitID);
		return elibstl::make_cwnd(pButton->GetHWND());
	}


	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 图片
			p->SetPic(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;

		case 1:// 是否同时显示图片和文本
			p->SetTextImageShowing(pPropertyVaule->m_bool);
			break;

		case 2:// 标题
			p->SetTextA(pPropertyVaule->m_szText);
			break;

		case 3:// 标题W
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;

		case 4:// 横向对齐
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;

		case 5:// 纵向对齐
			p->SetAlign(FALSE, pPropertyVaule->m_int);
			break;

		case 6:// 字体
			p->SetFont((LOGFONTA*)pPropertyVaule->m_int);
			break;

		case 7:// 默认
			p->SetDef(pPropertyVaule->m_int);
			break;

		case 8:// 类型
			p->SetType(pPropertyVaule->m_int);
			break;
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
		case 0:// 图片
			pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize);
			break;

		case 1:// 是否同时显示图片和文本
			pPropertyVaule->m_bool = p->GetTextImageShowing();
			break;

		case 2:// 标题
			pPropertyVaule->m_szText = p->GetTextA();
			break;

		case 3:// 标题W
			if (pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW())
				pPropertyVaule->m_data.m_nDataSize = wcslen((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;

		case 4:// 横向对齐
			pPropertyVaule->m_int = p->GetAlign(TRUE);
			break;

		case 5:// 纵向对齐
			pPropertyVaule->m_int = p->GetAlign(FALSE);
			break;

		case 6:// 字体
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;

		case 7:// 默认
			pPropertyVaule->m_int = p->GetDef();
			break;

		case 8:// 类型
			pPropertyVaule->m_int = p->GetType();
			break;
		}

		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		if (nPropertyIndex == 3)
		{
			auto psz = p->GetTextW();
			std::wstring ws(psz);
			p->SetTextW(elibstl::MyInputBox(ws).c_str());
			*pblModified = TRUE;
		}
		else
			*pblModified = FALSE;

		return FALSE;
	}

	static PFN_INTERFACE WINAPI EGetInterface(INT nInterfaceNO)
	{
		switch (nInterfaceNO)
		{
		case ITF_CREATE_UNIT:
			// 创建组件
			return (PFN_INTERFACE)ECreate;
		case ITF_NOTIFY_PROPERTY_CHANGED:
			// 通知某属性数据被用户修改
			return (PFN_INTERFACE)EChange;
		case ITF_GET_ALL_PROPERTY_DATA:
			// 取全部属性数据
			return (PFN_INTERFACE)EGetAlldata;
		case ITF_GET_PROPERTY_DATA:
			// 取某属性数据
			return (PFN_INTERFACE)EGetData;
		case ITF_DLG_INIT_CUSTOMIZE_DATA:
			return (PFN_INTERFACE)EInputW;
		}
		return NULL;
	}
};

SUBCLASS_MGR_INIT(CPushButton, SCID_PUSHBTNPARENT, SCID_PUSHBTN)


class CCheckButton :public CButton
{
	SUBCLASS_MGR_DECL(CCheckButton)
private:
	EBUTTONDATA_CHECKBTN m_InfoEx{};

	SUBCLASS_PARENT_FNHEAD
	{

		SUBCLASS_RET_DEFPROC;
	}

	SUBCLASS_CTRL_FNHEAD
	{



		SUBCLASS_RET_DEFPROC;
	}
};

SUBCLASS_MGR_INIT(CCheckButton, SCID_CHECKBTNPARENT, SCID_CHECKBTN)

class CCommandLink :public CButton
{
	SUBCLASS_MGR_DECL(CCommandLink)
private:
	EBUTTONDATA_CMDLINK m_InfoEx{};

	SUBCLASS_PARENT_FNHEAD
	{

		SUBCLASS_RET_DEFPROC;
	}

		SUBCLASS_CTRL_FNHEAD
	{



		SUBCLASS_RET_DEFPROC;
	}
};

SUBCLASS_MGR_INIT(CCommandLink, SCID_CMDLINKPARENT, SCID_CMDLINK)

//////////////////////////////////////////////////////////////////////
/////////////////////////////普通按钮//////////////////////////////////
//////////////////////////////////////////////////////////////////////
static EVENT_INFO2 s_Event_PushBtn[] =
{
	/*000*/ {"按钮被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"下拉箭头被单击", "当下拉箭头被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_PushBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*001*/ {"是否同时显示图片和文本", "IsShowPicAndText", "无法预览，需要通用组件库6.0", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*002*/ {"标题", "Text", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_TEXT, _PROP_OS(__OS_WIN), NULL},
	/*003*/ {"标题W", "TextW", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*004*/ {"横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0"},
	/*005*/ {"纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""居中\0""下边\0""\0"},
	/*006*/ {"字体", "Font", "用作在运行时提供浏览器的当前标题文本", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*007*/ {"默认", "Def", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "通常\0""默认\0""\0"},
	/*008*/ {"类型", "Type", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "普通按钮\0""拆分按钮\0""\0"},
};
//////////////////////////////////////////////////////////////////////
///////////////////////////////选择框//////////////////////////////////
//////////////////////////////////////////////////////////////////////
static EVENT_INFO2 s_Event_CheckBtn[] =
{
	/*000*/ {"按钮被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"下拉箭头被单击", "当下拉箭头被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_CheckBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*001*/ {"是否同时显示图片和文本", "IsShowPicAndText", "无法预览，需要通用组件库6.0", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*002*/ {"标题", "Text", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_TEXT, _PROP_OS(__OS_WIN), NULL},
	/*003*/ {"标题W", "TextW", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*004*/ {"横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0"},
	/*005*/ {"纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""居中\0""下边\0""\0"},
	/*006*/ {"字体", "Font", "用作在运行时提供浏览器的当前标题文本", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*007*/ {"默认", "Def", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "通常\0""默认\0""\0"},
	/*008*/ {"类型", "Type", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "普通按钮\0""拆分按钮\0""\0"},
};
//////////////////////////////////////////////////////////////////////
/////////////////////////////命令链接//////////////////////////////////
//////////////////////////////////////////////////////////////////////
static EVENT_INFO2 s_Event_CmdLink[] =
{
	/*000*/ {"按钮被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"下拉箭头被单击", "当下拉箭头被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_CmdLink[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*001*/ {"是否同时显示图片和文本", "IsShowPicAndText", "无法预览，需要通用组件库6.0", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*002*/ {"标题", "Text", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_TEXT, _PROP_OS(__OS_WIN), NULL},
	/*003*/ {"标题W", "TextW", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*004*/ {"横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0"},
	/*005*/ {"纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""居中\0""下边\0""\0"},
	/*006*/ {"字体", "Font", "用作在运行时提供浏览器的当前标题文本", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*007*/ {"默认", "Def", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "通常\0""默认\0""\0"},
	/*008*/ {"类型", "Type", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "普通按钮\0""拆分按钮\0""\0"},
};

ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtButtonW =
{
	"按钮W",				//中文名称
	"ButtonW",			//英文名称
	"Unicode按钮",		//说明
	0,					//命令数量
	0,					//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	103,				//资源ID
	sizeof(s_Event_PushBtn) / sizeof(s_Event_PushBtn[0]),
	s_Event_PushBtn,
	sizeof(s_Member_PushBtn) / sizeof(s_Member_PushBtn[0]),
	s_Member_PushBtn,
	CPushButton::EGetInterface,
	0,					//成员数量
	NULL				//成员数据数组
};

LIB_DATA_TYPE_INFO CtCheckButtonW =
{
	"选择框W",			//中文名称
	"CheckButtonW",		//英文名称
	"Unicode选择框（单选、复选、三态复选）",//说明
	0,					//命令数量
	0,					//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	103,				//资源ID
	sizeof(s_Event_CheckBtn) / sizeof(s_Event_CheckBtn[0]),
	s_Event_CheckBtn,
	sizeof(s_Member_CheckBtn) / sizeof(s_Member_CheckBtn[0]),
	s_Member_CheckBtn,
	CPushButton::EGetInterface,
	0,					//成员数量
	NULL				//成员数据数组
};

LIB_DATA_TYPE_INFO CtCommandLink =
{
	"命令链接按钮",		//中文名称
	"CommandLink",		//英文名称
	"命令链接按钮",		//说明
	0,					//命令数量
	0,					//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	103,				//资源ID
	sizeof(s_Event_CmdLink) / sizeof(s_Event_CmdLink[0]),
	s_Event_CmdLink,
	sizeof(s_Member_CmdLink) / sizeof(s_Member_CmdLink[0]),
	s_Member_CmdLink,
	CPushButton::EGetInterface,
	0,					//成员数量
	NULL				//成员数据数组
};
ESTL_NAMESPACE_END