/*
* 2023.5.7
* FIXME：按钮的图像列表相关功能没有封装
*/
#include"EcontrolHelp.h"

#pragma warning(disable:4996)

#define SCID_PUSHBTN		20230425'01u
#define SCID_PUSHBTNPARENT	20230425'02u
#define SCID_CHECKBTN		20230425'03u
#define SCID_CHECKBTNPARENT	20230425'04u
#define SCID_CMDLINK		20230425'05u
#define SCID_CMDLINKPARENT	20230425'06u

#define BTN_COMM_PROP \
	/*000*/{ "图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL}, \
	/*001*/{ "是否同时显示图片和文本", "IsShowPicAndText", "无法预览，需要通用组件库6.0", UD_BOOL, _PROP_OS(__OS_WIN), NULL }, \
	/*002*/{ "标题", "Text", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_TEXT, _PROP_OS(__OS_WIN), NULL }, \
	/*003*/{ "标题W", "TextW", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL }, \
	/*004*/{ "横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0" }, \
	/*005*/{ "纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""居中\0""下边\0""\0" }, \
	/*006*/{ "字体", "Font", "", UD_FONT, _PROP_OS(__OS_WIN) , NULL }

#define BTN_COMM_GETPROP \
	case 0:/*图片*/ \
		pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 1:/*是否同时显示图片和文本*/ \
		pPropertyVaule->m_bool = p->GetTextImageShowing(); \
		break; \
	case 2:/*标题*/ \
		pPropertyVaule->m_szText = p->GetTextA(); \
		break; \
	case 3:/*标题W*/ \
		pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 4:/*横向对齐*/ \
		pPropertyVaule->m_int = p->GetAlign(TRUE); \
		break; \
	case 5:/*纵向对齐*/ \
		pPropertyVaule->m_int = p->GetAlign(FALSE); \
		break; \
	case 6:/*字体*/ \
		pPropertyVaule->m_data.m_pData = p->GetFont(); \
		pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA); \
		break;

#define BTN_COMM_SETPROP \
	case 0:/*图片*/ \
		p->SetPicBtn(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 1:/*是否同时显示图片和文本*/ \
		p->SetTextImageShowing(pPropertyVaule->m_bool); \
		break; \
	case 2:/*标题*/ \
		p->SetTextA(pPropertyVaule->m_szText); \
		break; \
	case 3:/*标题W*/ \
		p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData); \
		break; \
	case 4:/*横向对齐*/ \
		p->SetAlign(TRUE, pPropertyVaule->m_int); \
		break; \
	case 5:/*纵向对齐*/ \
		p->SetAlign(FALSE, pPropertyVaule->m_int); \
		break; \
	case 6:/*字体*/ \
		p->SetFont((LOGFONTA*)pPropertyVaule->m_int); \
		break;

ESTL_NAMESPACE_BEGIN
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

	int iType;				// 类型
	int iCheckState;		// 选择状态
	BOOL bPushLike;			// 按钮形式
	BOOL bFlat;				// 平面
	BOOL bLeftText;			// 标题居左
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

	int cchNote;			// 注释文本长度，仅用于保存信息
	BOOL bShieldIcon;		// 是否盾牌图标
	int iDef;				// 默认
};

// 按钮基类。
// 请勿直接实例化此类
class CButton :public elibstl::CCtrlBase
{
protected:
	EBUTTONDATA m_Info{};

	eStlInline SIZE_T InitBase(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID, UINT uID, HWND hParent)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, uID, hParent);
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(EBUTTONDATA));
		}

		m_Info.iVer = DATA_VER_BTN_1;

		if (pAllData)
			return sizeof(EBUTTONDATA) + cbBaseData;
		else
			return 0;
	}

	eStlInline void InitBase(PCVOID pAllData)
	{
		InitBase0(pAllData);
		if (pAllData)
		{
			SetAlign(TRUE, m_Info.algH);
			SetAlign(FALSE, m_Info.algV);
			SetTextImageShowing(m_Info.bShowTextAndImage);
		}
		else
		{
			m_Info.algH = 1;
			m_Info.algV = 1;
		}

		if (m_hbmPic)
		{
			if (!m_bInDesignMode)
				if (m_Info.bShowTextAndImage)
					SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
				else
					SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			else
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hbmPic);
		}
		else
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
	}
public:
	CButton() {}

	virtual ~CButton() {}

	/// <summary>
	/// 置图片文本同时显示
	/// </summary>
	/// <param name="bShowTextAndImage">是否同时显示</param>
	void SetTextImageShowing(BOOL bShowTextAndImage)
	{
		m_Info.bShowTextAndImage = bShowTextAndImage;
		if (!m_bInDesignMode)
		{
			DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
			if (bShowTextAndImage)
				dwStyle &= (~(BS_BITMAP));
			else if (m_pPicData && m_Info0.cbPic)
				dwStyle |= BS_BITMAP;
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		}
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
		if (m_bInDesignMode)
			if (bHAlign)
				return m_Info.algH;
			else
				return m_Info.algV;
		else
			if (bHAlign)
				return MultiSelectWndStyle(m_hWnd, BS_LEFT, BS_CENTER, BS_RIGHT);
			else
				return MultiSelectWndStyle(m_hWnd, BS_TOP, BS_VCENTER, BS_BOTTOM);
	}

	/// <summary>
	/// 置图片。
	/// 特定于按钮，不应使用基类方法
	/// </summary>
	/// <param name="pPic">图片字节流指针</param>
	/// <param name="cbSize">字节流长度</param>
	/// <returns></returns>
	eStlInline void SetPicBtn(void* pPic, int cbSize)
	{
		if (cbSize)
			if (m_Info.bShowTextAndImage)
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
			else
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
		else
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));

		SetPic(pPic, cbSize);
		SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hbmPic);
	}

	/// <summary>
	/// 平面化基类数据。
	/// 扩展数据应在其后附加
	/// </summary>
	/// <returns></returns>
	eStlInline HGLOBAL FlattenInfoBase(SIZE_T cbExtra = 0u, SIZE_T* pcbBaseData = NULL)
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(EBUTTONDATA) + cbExtra, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_Info, sizeof(EBUTTONDATA));
		GlobalUnlock(hGlobal);
		*pcbBaseData = cbBaseData + sizeof(EBUTTONDATA);
		return hGlobal;
	Fail:
		*pcbBaseData = 0;
		return hGlobal;
	}
};

// 普通按钮
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

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_NOTIFY:
		{
			auto p = (NMHDR*)lParam;
#pragma warning(push)
#pragma warning(disable:26454)// 算术溢出
			if (p->code == BCN_DROPDOWN)
				if (m_CtrlSCInfo.count(p->hwndFrom))
					m_CtrlSCInfo[p->hwndFrom]->OnDropDownClick();
#pragma warning(pop)
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
		auto p = (CPushButton*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CPushButton() = delete;
	CPushButton(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_PUSHBTN));
		else
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"按钮W");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}
		m_InfoEx.iVer = DATA_VER_BTN_PUSHBTN_1;

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetDef(m_InfoEx.iDef);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
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
			if (!m_bInDesignMode)
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

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CPushButton(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
			BTN_COMM_SETPROP

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
			BTN_COMM_GETPROP

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

		*pblModified = FALSE;
		if (nPropertyIndex == 3)
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
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
			*((int*)dwParam2) = 32;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CPushButton, SCID_PUSHBTNPARENT, SCID_PUSHBTN)

// 选择框
class CCheckButton :public CButton
{
	SUBCLASS_MGR_DECL(CCheckButton)
private:
	EBUTTONDATA_CHECKBTN m_InfoEx{};

	/// <summary>
	/// 被单击
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CCheckButton*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_NCCALCSIZE:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CCheckButton() = delete;
	CCheckButton(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);
		if (!m_pszTextW)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"选择框W");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_CHECKBTN));
		else
			m_Info.algH = 0;
		m_InfoEx.iVer = DATA_VER_BTN_CHECKBTN_1;

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetType(m_InfoEx.iType);
		SetCheckState(m_InfoEx.iCheckState);
		SetPushLike(m_InfoEx.bPushLike);
		SetFlat(m_InfoEx.bFlat);
		SetLeftText(m_InfoEx.bLeftText);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
	}

	/// <summary>
	/// 置类型
	/// </summary>
	/// <param name="iType">类型</param>
	void SetType(int iType)
	{
		m_InfoEx.iType = iType;
		elibstl::ModifyWindowStyle(
			m_hWnd,
			elibstl::MultiSelect<DWORD>(iType, BS_AUTORADIOBUTTON, BS_AUTOCHECKBOX, BS_AUTO3STATE),
			BS_AUTORADIOBUTTON | BS_AUTOCHECKBOX | BS_AUTO3STATE);
		Redraw();
	}

	/// <summary>
	/// 取类型
	/// </summary>
	int GetType()
	{
		if (m_bInDesignMode)
			return m_InfoEx.iType;
		else
		{
			auto i = MultiSelectWndStyle(m_hWnd,
				BS_AUTORADIOBUTTON | BS_RADIOBUTTON, BS_AUTOCHECKBOX | BS_CHECKBOX, BS_AUTO3STATE | BS_3STATE);
			if (i < 0)
				i = 0;
			return i;
		}
	}

	/// <summary>
	/// 置检查框状态
	/// </summary>
	/// <param name="iState">状态</param>
	eStlInline void SetCheckState(int iState)
	{
		m_InfoEx.iCheckState = iState;
		SendMessageW(m_hWnd, BM_SETCHECK, elibstl::MultiSelect<DWORD>(iState, BST_UNCHECKED, BST_CHECKED, BST_INDETERMINATE), 0);
	}

	/// <summary>
	/// 取检查框状态
	/// </summary>
	int GetCheckState()
	{
		if (m_bInDesignMode)
			return m_InfoEx.iCheckState;
		else
		{
			int i = MultiSelectEqual(SendMessageW(m_hWnd, BM_GETCHECK, 0, 0), BST_UNCHECKED, BST_CHECKED, BST_INDETERMINATE);
			if (i < 0)
				i = 0;
			return i;
		}
	}

	/// <summary>
	/// 置按钮形式
	/// </summary>
	/// <param name="bPushLike">是否为按钮形式</param>
	eStlInline void SetPushLike(BOOL bPushLike)
	{
		m_InfoEx.bPushLike = bPushLike;
		elibstl::ModifyWindowStyle(m_hWnd, bPushLike ? BS_PUSHLIKE : 0, BS_PUSHLIKE);
		Redraw();
	}

	/// <summary>
	/// 取按钮形式
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetPushLike()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bPushLike;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_PUSHLIKE);
	}

	/// <summary>
	/// 置平面形式
	/// </summary>
	/// <param name="bFlat">是否为平面形式</param>
	eStlInline void SetFlat(BOOL bFlat)
	{
		m_InfoEx.bFlat = bFlat;
		elibstl::ModifyWindowStyle(m_hWnd, bFlat ? BS_FLAT : 0, BS_FLAT);
		Redraw();
	}

	/// <summary>
	/// 取平面形式
	/// </summary>
	eStlInline BOOL GetFlat()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bFlat;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_FLAT);
	}

	/// <summary>
	/// 置文本居左
	/// </summary>
	/// <param name="bLeftText">是否文本居左</param>
	eStlInline void SetLeftText(BOOL bLeftText)
	{
		m_InfoEx.bLeftText = bLeftText;
		elibstl::ModifyWindowStyle(m_hWnd, bLeftText ? BS_LEFTTEXT : 0, BS_LEFTTEXT);
		Redraw();
	}

	/// <summary>
	/// 取文本居左
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetLeftText()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bLeftText;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_LEFTTEXT);
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase(sizeof(EBUTTONDATA_CHECKBTN), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_InfoEx, sizeof(EBUTTONDATA_CHECKBTN));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CCheckButton(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
			BTN_COMM_SETPROP

		case 7:// 类型
			p->SetType(pPropertyVaule->m_int);
			break;

		case 8:// 选中
			p->SetCheckState(pPropertyVaule->m_int);
			break;

		case 9:// 按钮形式
			p->SetPushLike(pPropertyVaule->m_bool);
			break;

		case 10:// 平面
			p->SetFlat(pPropertyVaule->m_bool);
			break;

		case 11:// 标题居左
			p->SetLeftText(pPropertyVaule->m_bool);
			break;

		case 12:// 边框
			p->SetFrame(pPropertyVaule->m_int);
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
			BTN_COMM_GETPROP

		case 7:// 类型
			pPropertyVaule->m_int = p->GetType();
			break;

		case 8:// 选中
			pPropertyVaule->m_int = p->GetCheckState();
			break;

		case 9:// 按钮形式
			pPropertyVaule->m_bool = p->GetPushLike();
			break;

		case 10:// 平面
			pPropertyVaule->m_bool = p->GetFlat();
			break;

		case 11:// 标题居左
			pPropertyVaule->m_bool = p->GetLeftText();
			break;

		case 12:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		}
		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		if (nPropertyIndex == 3)
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
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
			*((int*)dwParam2) = 24;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CCheckButton, SCID_CHECKBTNPARENT, SCID_CHECKBTN)

// 命令链接
class CCommandLink :public CButton
{
	SUBCLASS_MGR_DECL(CCommandLink)
private:
	EBUTTONDATA_CMDLINK m_InfoEx{};
	PWSTR m_pszNote;// 注释文本

	/// <summary>
	/// 被单击
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CCommandLink*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CCommandLink() = delete;
	CCommandLink(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);
		if (!m_pszTextW)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"命令链接");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_CMDLINK));
		m_InfoEx.iVer = DATA_VER_BTN_CHECKBTN_1;
		m_pszNote = NULL;
		if (m_InfoEx.cchNote)
		{
			elibstl::DupStringForNewDeleteW(m_pszNote,
				(PCWSTR)((BYTE*)pAllData + cbBaseData + sizeof(EBUTTONDATA_CMDLINK)), m_InfoEx.cchNote);
		}

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS |
			(m_bInDesignMode ? BS_PUSHBUTTON : BS_COMMANDLINK),
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetShieldIcon(m_InfoEx.bShieldIcon);
		SetNote(m_pszNote);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
	}

	~CCommandLink()
	{
		delete[] m_pszNote;
	}

	/// <summary>
	/// 置注释文本
	/// </summary>
	/// <param name="pszText">文本指针</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetNote(PCWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			if (pszText)
				elibstl::DupStringForNewDeleteW(m_pszNote, pszText);
			else
			{
				delete[] m_pszNote;
				m_pszNote = NULL;
			}
			return TRUE;
		}
		else
			return SendMessageW(m_hWnd, BCM_SETNOTE, 0, (LPARAM)pszText);
	}

	/// <summary>
	/// 置注释文本。
	/// 本方法不复制内存
	/// </summary>
	/// <param name="pszText">文本指针，必须由new/delete[]管理</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetNoteNoCopy(PWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			delete[] m_pszNote;
			m_pszNote = pszText;
			return TRUE;
		}
		else
			return SendMessageW(m_hWnd, BCM_SETNOTE, 0, (LPARAM)pszText);
	}

	/// <summary>
	/// 取注释文本。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <returns>文本指针</returns>
	PWSTR GetNote()
	{
		if (!m_bInDesignMode)
		{
			int cch = SendMessageW(m_hWnd, BCM_GETNOTELENGTH, 0, 0);
			delete[] m_pszNote;
			if (cch)
			{
				m_pszNote = new WCHAR[cch + 1];
				SendMessageW(m_hWnd, BCM_GETNOTE, cch + 1, (LPARAM)m_pszNote);
			}
			else
				m_pszNote = NULL;
		}

		return m_pszNote;
	}

	/// <summary>
	/// 置盾牌图标
	/// </summary>
	/// <param name="bShieldIcon">是否为盾牌图标</param>
	eStlInline void SetShieldIcon(BOOL bShieldIcon)
	{
		m_InfoEx.bShieldIcon = bShieldIcon;
		SendMessageW(m_hWnd, BCM_SETSHIELD, 0, bShieldIcon);
	}

	/// <summary>
	/// 取盾牌图标
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetShieldIcon()
	{
		return m_InfoEx.bShieldIcon;// 这个东西只能置不能取.....把记录的值返回回去吧
	}

	/// <summary>
	/// 置是否默认
	/// </summary>
	/// <param name="iDef">是否默认，参见属性定义</param>
	void SetDef(int iDef)
	{
		m_InfoEx.iDef = iDef;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_DEFCOMMANDLINK | BS_COMMANDLINK));
		if (iDef)
			dwStyle |= (m_bInDesignMode ? BS_DEFPUSHBUTTON : BS_DEFCOMMANDLINK);
		else
			dwStyle |= (m_bInDesignMode ? BS_PUSHBUTTON : BS_COMMANDLINK);

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

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		SIZE_T cbData = sizeof(EBUTTONDATA_CMDLINK);
		if (GetNote())
		{
			m_InfoEx.cchNote = wcslen(m_pszNote);
			cbData += (m_InfoEx.cchNote * sizeof(WCHAR));
		}
		else
			m_InfoEx.cchNote = 0;
		auto hGlobal = FlattenInfoBase(cbData, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_InfoEx, sizeof(EBUTTONDATA_CMDLINK));
		// 注释文本
		p += sizeof(EBUTTONDATA_CMDLINK);
		if (m_pszNote)
			memcpy(p, m_pszNote, m_InfoEx.cchNote * sizeof(WCHAR));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CCommandLink(STD_ECTRL_CREATE_REAL_ARGS);
		if (p->GetHWND())
			return elibstl::make_cwnd(p->GetHWND());
		else
		{
			delete p;
			return NULL;
		}
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:/*图片*/
			p->SetPicBtn(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 1:/*标题*/
			p->SetTextA(pPropertyVaule->m_szText);
			break;
		case 2:/*标题W*/
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 3:// 注释文本
			p->SetNote((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 4:// 是否盾牌图标
			p->SetShieldIcon(pPropertyVaule->m_bool);
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
		case 0:/*图片*/
			pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 1:/*标题*/
			pPropertyVaule->m_szText = p->GetTextA();
			break;
		case 2:/*标题W*/
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// 注释文本
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetNote();
			break;
		case 4:// 是否盾牌图标
			pPropertyVaule->m_bool = p->GetShieldIcon();
			break;
		}
		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 2:// 标题W
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;

		case 3:// 注释文本
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetNote()))
			{
				p->SetNoteNoCopy(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;
		}
		return FALSE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 80;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CCommandLink, SCID_CMDLINKPARENT, SCID_CMDLINK)
ESTL_NAMESPACE_END
/////////////////////////////普通按钮
static EVENT_INFO2 s_Event_PushBtn[] =
{
	/*000*/ {"按钮被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"下拉箭头被单击", "当下拉箭头被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_PushBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	BTN_COMM_PROP,
	/*007*/ {"默认", "Def", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "通常\0""默认\0""\0"},
	/*008*/ {"类型", "Type", "无法预览。该属性需要在清单中指定Comctl6.0", UD_PICK_INT, _PROP_OS(__OS_WIN), "普通按钮\0""拆分按钮\0""\0"},
};
///////////////////////////////选择框
static EVENT_INFO2 s_Event_CheckBtn[] =
{
	/*000*/ {"被单击", "当选择框被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_CheckBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	BTN_COMM_PROP,
	/*007*/ {"类型", "Type", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "单选框\0""复选框\0""三态复选框\0""\0"},
	/*008*/ {"选中", "CheckState", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "未选中\0""选中\0""半选中\0""\0"},
	/*009*/ {"按钮形式", "IsBtnLike", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*010*/ {"平面", "IsFlat", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*011*/ {"标题居左", "IsTextLeft", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*012*/ {"边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
};
/////////////////////////////命令链接
static EVENT_INFO2 s_Event_CmdLink[] =
{
	/*000*/ {"被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_CmdLink[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*001*/ {"标题","Text","",UD_TEXT,_PROP_OS(__OS_WIN),NULL },
	/*002*/ {"标题W","TextW","",UD_CUSTOMIZE,_PROP_OS(__OS_WIN),NULL },
	/*003*/ {"注释文本","Note","",UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*004*/ {"是否为盾牌图标", "IsShieldIcon", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL },
};
/////////////////////////////方法
static int s_Cmd_PushBtn[] = { 120 };

EXTERN_C void libstl_Button_GetIdealSize(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SIZE size{ *pArgInf[1].m_pInt,0 };
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	if (!hWnd)
		goto Fail;
	if (!SendMessageW(hWnd, BCM_GETIDEALSIZE, 0, (LPARAM)&size))
		goto Fail;
	*pArgInf[1].m_pInt = size.cx;
	*pArgInf[2].m_pInt = size.cy;
	pRetData->m_bool = TRUE;
	return;
Fail:
	pRetData->m_bool = FALSE;
	return;
}

static ARG_INFO s_Args_GetIdealSize[] =
{
	{
		/*name*/    "宽度",
		/*explain*/ "接受宽度的变量，若调用前变量不为0，则变量的值指定为按钮的宽度，将以此值为基准计算理想高度",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	},
	{
		/*name*/    "高度",
		/*explain*/ "接受高度的变量",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	}
};

FucInfo Fn_BtnGetIdealSize = { {
		/*ccname*/  ("取理想尺寸"),
		/*egname*/  ("GetIdealSize"),
		/*explain*/ ("取按钮理想尺寸。本命令需要在清单中指定Comctl6.0"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetIdealSize),
		/*arg lp*/  s_Args_GetIdealSize,
	} ,libstl_Button_GetIdealSize ,"libstl_Button_GetIdealSize" };
/////////////////////////////取接口
EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_ButtonW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CPushButton::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CPushButton::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CPushButton::ENotify;
	}
	return NULL;
}

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_CheckButtonW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CCheckButton::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CCheckButton::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CCheckButton::ENotify;
	}
	return NULL;
}

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_CommandLink(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CCommandLink::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CCommandLink::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CCommandLink::ENotify;
	}
	return NULL;
}
/////////////////////////////类型定义
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtButtonW =
{
	"按钮W",				//中文名称
	"ButtonW",			//英文名称
	"Unicode按钮",		//说明
	ARRAYSIZE(s_Cmd_PushBtn),
	s_Cmd_PushBtn,
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	IDB_BUTTON_W,				//资源ID
	ARRAYSIZE(s_Event_PushBtn),
	s_Event_PushBtn,
	ARRAYSIZE(s_Member_PushBtn),
	s_Member_PushBtn,
	libstl_GetInterface_ButtonW,
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
	IDB_CHECKBUTTON_W,				//资源ID
	ARRAYSIZE(s_Event_CheckBtn),
	s_Event_CheckBtn,
	ARRAYSIZE(s_Member_CheckBtn),
	s_Member_CheckBtn,
	libstl_GetInterface_CheckButtonW,
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
	IDB_COMLINKBUTTON_W,				//资源ID
	ARRAYSIZE(s_Event_CmdLink),
	s_Event_CmdLink,
	ARRAYSIZE(s_Member_CmdLink),
	s_Member_CmdLink,
	libstl_GetInterface_CommandLink,
	0,					//成员数量
	NULL				//成员数据数组
};
ESTL_NAMESPACE_END