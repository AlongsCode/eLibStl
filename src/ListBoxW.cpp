#include "EcontrolHelp.h"

#define SCID_LISTBOX		20230521'01u
#define SCID_LISTBOXPARENT	20230521'02u

ESTL_NAMESPACE_BEGIN

struct EDLGCTX_LISTBOXITEMS :public EDLGCTX_BASE
{
	BYTE** ppItemsData;
	BYTE* pInitData;

};

#define WCN_LISTBOXDESIGN L"eLibStl.WndClass.ListBoxItemsDesign"

static ATOM s_atomListBoxItemsDesign = 0;

#define IDC_LB_ITEMS	101
#define IDC_BT_OK		201
#define IDC_BT_CANCEL	202
#define IDC_BT_INSERTF	203
#define IDC_BT_INSERTB	204
#define IDC_BT_DEL		205
#define IDC_ED_CAPTION	301
#define IDC_ED_TIP		302
#define IDC_ED_IMAGEIDX	303
#define IDC_ED_ITEMDATA	304

static LRESULT CALLBACK WndProc_ListBoxDesign(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto p = (EDLGCTX_LISTBOXITEMS*)GetWindowLongPtrW(hWnd, 0);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		constexpr int DlgPadding = 8;
		constexpr int cxLB = 240;
		constexpr int cyLB = 240;
		constexpr int xStatic = 256;
		constexpr int cxStatic = 70;
		constexpr int cyStatic = 26;
		constexpr int StaticLineStep = 40;
		constexpr int xEdit = 329;
		constexpr int cxEdit1 = 256;
		constexpr int cxEdit2 = 60;
		constexpr int xBTOK = 384;
		constexpr int cxBT = 96;
		constexpr int cyBT = 32;
		constexpr int yBT = DlgPadding * 2 + cyLB;

		p = (EDLGCTX_LISTBOXITEMS*)((CREATESTRUCTW*)lParam)->lpCreateParams;
		SetWindowLongPtrW(hWnd, 0, (LONG_PTR)p);
		p->hFont = EzFont(L"微软雅黑", 10);

		HWND hCtrl;
		hCtrl = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOINTEGRALHEIGHT,
			DlgPadding, DlgPadding, cxLB, cyLB, hWnd, (HMENU)IDC_LB_ITEMS, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"标题：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"提示文本：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"图像索引：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 2, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"项目数值：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 3, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_CAPTION, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_TIP, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep * 2, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_IMAGEIDX, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep * 3, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_ITEMDATA, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"向前插入", WS_CHILD | WS_VISIBLE,
			DlgPadding, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTF, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"向后插入", WS_CHILD | WS_VISIBLE,
			DlgPadding * 2 + cxBT, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTB, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"删除", WS_CHILD | WS_VISIBLE,
			DlgPadding * 3 + cxBT * 2, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_DEL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"确定", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			xBTOK, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_OK, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"取消", WS_CHILD | WS_VISIBLE,
			xBTOK + DlgPadding + cxBT, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_CANCEL, g_elibstl_hModule, NULL);

		SetFontForWndAndCtrl(hWnd, p->hFont);
	}
	return 0;

	case WM_CLOSE:
	{
		p->bOK = FALSE;
		DlgEndModel(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
	}
	return 0;

	case WM_DESTROY:
	{
		DeleteObject(p->hFont);
		p->bOK = FALSE;
		DlgModelOnDestroy(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

BOOL ShowListBoxDesignDlg(BYTE** ppItemsData, BYTE* pInitData)
{
	auto pCtx = EIDEDlgPreShow<EDLGCTX_LISTBOXITEMS>(&s_atomListBoxItemsDesign, WCN_LISTBOXDESIGN, WndProc_ListBoxDesign);
	pCtx->pInitData = pInitData;
	pCtx->ppItemsData = ppItemsData;

	EIDEDlgShow(WCN_LISTBOXDESIGN, L"列表框项目设置", 600, 325, WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_POPUP, pCtx);

	BOOL bOK = pCtx->bOK;
	delete pCtx;
	return bOK;
}

// 列表框
/*
* 版本1数据布局：
* ELISTBOXDATA结构
* 项目数据
* 图片组
* 目录（不带结尾NULL）
* 文件过滤器（不带结尾NULL）
*/
#define DATA_VER_LISTBOX_1	1
struct ELISTBOXDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int idxCurrSel;			// 现行选中
	int cyItem;				// 行高
	COLORREF crText;		// 文本颜色
	COLORREF crBK;			// 背景颜色
	COLORREF crSelText;		// 选中文本颜色
	COLORREF crSelBK;		// 选择背景颜色
	int iAlignH;			// 横向对齐
	int iAlignV;			// 纵向对齐
	UINT uFileAttr;			// 文件过滤属性
	FILETIME ftMinTime;		// 文件最小时间，基于协调世界时
	FILETIME ftMaxTime;		// 文件最大时间，基于协调世界时
	SIZE_T cbItems;			// 表项数据长度
	SIZE_T cbImageList;		// 图片组长度
	int cchDir;				// 目录字符数
	int cchFilePattern;		// 文件过滤器字符数
	BITBOOL bMultiColumn : 1;	// 横向扩展
	BITBOOL bAutoSort : 1;	// 自动排序
	BITBOOL bMultiSel : 1;	// 鼠标多选
	BITBOOL bExtSel : 1;	// 按键多选
	BITBOOL bToolTip : 1;	// 工具提示
	BITBOOL bUseTabStop: 1;	// 解析制表符
	BITBOOL bIntegralHeight: 1;	// 取整控件高度
	BITBOOL bDisableNoScroll: 1;// 显示禁止的滚动条
	BITBOOL bLibOwnerDraw: 1;	// 支持库自画
	BITBOOL bEllipsis: 1;	// 省略号
};

#define DATA_VER_LBITEMS_1 1
// 项目数据头
struct LBITEMSDATAHEADER
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int cItems;				// 项目数
};
// 项目属性头，标题与提示文本紧随其后
struct LBITEMHEADER
{
	int cchCaption;			// 标题字符数
	int cchTip;				// 提示字符数
	int idxImage;			// 图像索引
	LPARAM lParam;			// 表项数值
};

class CListBox :public CCtrlBase
{
	SUBCLASS_MGR_DECL(CListBox)
private:
	ELISTBOXDATA m_Info{};
	BYTE* m_pItems = NULL;
	HIMAGELIST m_hImageList = NULL;
	//BYTE* m_pImageListData = NULL;
	IStream* m_pISImageList = NULL;
	BYTE* m_pISData = NULL;// 无需释放
	PWSTR m_pszDir = NULL;
	PWSTR m_pszFilePattern = NULL;

	HBRUSH m_hbrBK = NULL;
	HBRUSH m_hbrSelBK = NULL;

	void AddFile()
	{
		SendMessageW(m_hWnd, LB_RESETCONTENT, 0, 0);
		SendMessageW(m_hWnd, LB_INITSTORAGE, 30, 30);
		if (!m_Info.cchDir)
			return;

		PWSTR pszPath = (PWSTR)_malloca((
			m_Info.cchDir +
			m_Info.cchFilePattern +
			5/*一个反斜杠，三个*.*（通配符为空时用），一个结尾NULL*/) * sizeof(WCHAR));
		assert(pszPath);// 消除警告
		wcscpy(pszPath, m_pszDir);
		PWSTR pszTemp = pszPath + m_Info.cchDir;// 指针指到目录的后面，方便替换通配符

		PWSTR pszFilePattern;
		if (m_Info.cchFilePattern && m_pszFilePattern)
			pszFilePattern = m_pszFilePattern;
		else
		{
#pragma warning(push)
#pragma warning(disable:6255)// 禁用警告：考虑改用_malloca
			pszFilePattern = (PWSTR)_alloca(4 * sizeof(WCHAR));
#pragma warning(pop)
			assert(pszFilePattern);// 消除警告
			wcscpy(pszFilePattern, L"*.*");
		}

		WIN32_FIND_DATAW wfd;
		HANDLE hFind;
		PWSTR pszDivPos, pszOld = pszFilePattern;
		while (TRUE)
		{
			pszDivPos = wcsstr(pszFilePattern, L"|");
			if (pszDivPos != pszOld && pszDivPos)// 常规情况
			{
				int cch = pszDivPos - pszOld - 1;
				wcscpy(pszTemp, L"\\");
				wcsncat(pszTemp, pszOld, cch);
				*(pszTemp + cch + 1) = L'\0';
			}
			else if (!pszDivPos)// 找不到下一个分隔符
			{
				wcscpy(pszTemp, L"\\");
				wcscat(pszTemp, pszOld);
			}
			else// 尾部（pszDivPos==pszOld）
				break;

			pszOld = pszDivPos + 1;
			hFind = FindFirstFileW(pszPath, &wfd);
			if (hFind == INVALID_HANDLE_VALUE)
				if (!pszDivPos)
					break;
				else
					continue;
			do
			{
				if (memcmp(wfd.cFileName, L".", 2 * sizeof(WCHAR)) == 0 ||
					memcmp(wfd.cFileName, L"..", 3 * sizeof(WCHAR)) == 0)
					continue;
				if (!m_Info.uFileAttr || wfd.dwFileAttributes & m_Info.uFileAttr)
				{
					if (m_Info.ftMaxTime == m_Info.ftMinTime || IsFILETIMEZero(&m_Info.ftMaxTime))
						SendMessageW(m_hWnd, LB_ADDSTRING, 0, (LPARAM)wfd.cFileName);
					else if (wfd.ftCreationTime > m_Info.ftMinTime && wfd.ftCreationTime < m_Info.ftMaxTime)
						SendMessageW(m_hWnd, LB_ADDSTRING, 0, (LPARAM)wfd.cFileName);
				}
			} while (FindNextFileW(hFind, &wfd));
			FindClose(hFind);
			if (!pszDivPos)
				break;
		}

		_freea(pszPath);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_CTLCOLORLISTBOX:
		{
			if (m_CtrlSCInfo.count((HWND)lParam))
			{
				auto p = m_CtrlSCInfo[(HWND)lParam];
				LRESULT lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);
				if (p->m_Info.crText != CLR_DEFAULT)
					SetTextColor((HDC)wParam, p->m_Info.crText);
				if (p->m_Info.crBK != CLR_DEFAULT)
					return (LRESULT)p->m_hbrBK;
				else
					return lResult;
			}
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
		auto p = (CListBox*)dwRefData;
		switch (uMsg)
		{
		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			break;
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CListBox() = delete;
	CListBox(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);

		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ELISTBOXDATA));
			if (m_Info.crBK != CLR_DEFAULT)
				m_hbrBK = CreateSolidBrush(m_Info.crBK);
			if (m_Info.crSelBK != CLR_DEFAULT)
				m_hbrSelBK = CreateSolidBrush(m_Info.crSelBK);
			p += sizeof(ELISTBOXDATA);

			p += m_Info.cbItems;

			p += m_Info.cbImageList;

			DupStringForNewDeleteW(m_pszDir, (PCWSTR)p, m_Info.cchDir);
			p += m_Info.cchDir * sizeof(WCHAR);

			DupStringForNewDeleteW(m_pszFilePattern, (PCWSTR)p, m_Info.cchFilePattern);
			p += m_Info.cchFilePattern * sizeof(WCHAR);
		}
		else
		{
			m_Info0.iFrame = 1;
			m_Info.crBK = CLR_DEFAULT;
			m_Info.crSelBK = CLR_DEFAULT;
			m_Info.crSelBK = CLR_DEFAULT;
			m_Info.crSelText = CLR_DEFAULT;
		}
		m_Info.iVer = DATA_VER_LISTBOX_1;

		DWORD dwLBStyle = 0;
		if (m_Info.bMultiColumn)
			dwLBStyle |= LBS_MULTICOLUMN;
		if (m_Info.bAutoSort)
			dwLBStyle |= LBS_SORT;
		if (m_Info.bMultiSel)
			dwLBStyle |= LBS_MULTIPLESEL;
		if (m_Info.bExtSel)
			dwLBStyle |= LBS_EXTENDEDSEL;
		if (m_Info.bUseTabStop)
			dwLBStyle |= LBS_USETABSTOPS;
		if (!m_Info.bIntegralHeight)
			dwLBStyle |= LBS_NOINTEGRALHEIGHT;
		if (m_Info.bDisableNoScroll)
			dwLBStyle |= LBS_DISABLENOSCROLL;
		if (m_Info.bLibOwnerDraw)
			dwLBStyle |= LBS_OWNERDRAWVARIABLE;

		m_hWnd = CreateWindowExW(0, WC_LISTBOXW, NULL,WS_VSCROLL| WS_CHILD | WS_CLIPSIBLINGS | dwLBStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		// 插入表项
		AddFile();
		SetCurrSel(m_Info.idxCurrSel);
		InitBase0(pAllData);
		if (m_Info.cyItem)// 必须在InitBase0后面
			SetItemHeight(m_Info.cyItem);
	}

	void SetItems(BYTE* pData)
	{

	}

	BYTE* GetItems()
	{
		return NULL;
	}

	eStlInline void SetCurrSel(int idx)
	{
		m_Info.idxCurrSel = idx;
		SendMessageW(m_hWnd, LB_SETCURSEL, idx, 0);
	}

	eStlInline int GetCurrSel()
	{
		if (m_bInDesignMode)
			return m_Info.idxCurrSel;
		else
			return SendMessageW(m_hWnd, LB_GETCURSEL, 0, 0);
	}

	eStlInline void SetMultiColumn(BOOL bMultiColumn)
	{
		m_Info.bMultiColumn = bMultiColumn;
	}

	eStlInline BOOL GetMultiColumn()
	{
		if (m_bInDesignMode)
			return m_Info.bMultiColumn;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_MULTICOLUMN);
	}

	eStlInline void SetItemHeight(int cy)
	{
		m_Info.cyItem = cy;
		SendMessageW(m_hWnd, LB_SETITEMHEIGHT, 0, cy);
	}

	eStlInline int GetItemHeight()
	{
		if (m_bInDesignMode)
			return m_Info.cyItem;
		else
			return SendMessageW(m_hWnd, LB_GETITEMHEIGHT, 0, 0);
	}

	eStlInline void SetClr(int idx, COLORREF cr)
	{
		if (idx)
			m_Info.crBK = cr;
		else
			m_Info.crText = cr;
		InvalidateRect(m_hWnd, NULL, FALSE);
	}

	eStlInline int GetClr(int idx)
	{
		if (idx)
			return m_Info.crBK;
		else
			return m_Info.crText;
	}

	eStlInline void SetAutoSort(BOOL bAutoSort)
	{
		m_Info.bAutoSort = bAutoSort;
	}

	eStlInline BOOL GetAutoSort()
	{
		if (m_bInDesignMode)
			return m_Info.bAutoSort;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_SORT);
	}

	eStlInline void SetMultiSel(BOOL bMultiSel)
	{
		m_Info.bMultiSel = bMultiSel;
	}

	eStlInline BOOL GetMultiSel()
	{
		if (m_bInDesignMode)
			return m_Info.bMultiSel;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_MULTIPLESEL);
	}

	eStlInline void SetExtSel(BOOL bExtSel)
	{
		m_Info.bExtSel = bExtSel;
	}

	eStlInline BOOL GetExtSel()
	{
		if (m_bInDesignMode)
			return m_Info.bExtSel;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_EXTENDEDSEL);
	}

	eStlInline void SetToolTip(BOOL bToolTip)
	{
		m_Info.bToolTip = bToolTip;
	}

	eStlInline BOOL GetToolTip()
	{
		return m_Info.bToolTip;
	}

	eStlInline void SetUseTabStop(BOOL bUseTabStop)
	{
		m_Info.bUseTabStop = bUseTabStop;
	}

	eStlInline BOOL GetUseTabStop()
	{
		if (m_bInDesignMode)
			return m_Info.bUseTabStop;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_USETABSTOPS);
	}

	eStlInline void SetIntegralHeight(BOOL bIntegralHeight)
	{
		m_Info.bIntegralHeight = bIntegralHeight;
	}

	eStlInline BOOL GetIntegralHeight()
	{
		if (m_bInDesignMode)
			return m_Info.bIntegralHeight;
		else
			return !IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_NOINTEGRALHEIGHT);
	}

	eStlInline void SetDisableNoScroll(BOOL bDisableNoScroll)
	{
		m_Info.bDisableNoScroll = bDisableNoScroll;
	}

	eStlInline BOOL GetDisableNoScroll()
	{
		if (m_bInDesignMode)
			return m_Info.bDisableNoScroll;
		else
			return !IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), LBS_DISABLENOSCROLL);
	}

	eStlInline void SetDir(PCWSTR pszDir)
	{
		m_Info.cchDir = DupStringForNewDeleteW(m_pszDir, pszDir);
		AddFile();
	}

	eStlInline PCWSTR GetDir(int* pcb)
	{
		if (pcb)
			*pcb = (m_Info.cchDir + 1) * sizeof(WCHAR);
		return m_pszDir;
	}

	eStlInline void SetFilePattern(PCWSTR pszFilePattern)
	{
		m_Info.cchFilePattern = DupStringForNewDeleteW(m_pszFilePattern, pszFilePattern);
		AddFile();
	}

	eStlInline PCWSTR GetFilePattern(int* pcb)
	{
		if (pcb)
			*pcb = (m_Info.cchFilePattern + 1) * sizeof(WCHAR);
		return m_pszFilePattern;
	}

	void SetFileAttr(UINT uAttr)
	{
		m_Info.uFileAttr = uAttr;
		AddFile();
	}

	UINT GetFileAttr()
	{
		return m_Info.uFileAttr;
	}

	void SetFileTime(BOOL bMaxTime, DATE date)
	{
		SYSTEMTIME st;
		FILETIME ft;
		VariantTimeToSystemTime(date, &st);
		SystemTimeToFileTime(&st, &ft);
		if (bMaxTime)
			LocalFileTimeToFileTime(&ft, &m_Info.ftMaxTime);
		else
			LocalFileTimeToFileTime(&ft, &m_Info.ftMinTime);
	}

	DATE GetFileTime(BOOL bMaxTime)
	{
		SYSTEMTIME st;
		FILETIME ft;
		DATE date;
		if (bMaxTime)
			FileTimeToLocalFileTime(&m_Info.ftMaxTime, &ft);
		else
			FileTimeToLocalFileTime(&m_Info.ftMinTime, &ft);
		FileTimeToSystemTime(&ft, &st);
		SystemTimeToVariantTime(&st, &date);
		return date;
	}

	eStlInline void SetLibOwnerDraw(BOOL bLibOwnerDraw)
	{
		m_Info.bLibOwnerDraw = bLibOwnerDraw;
	}

	eStlInline BOOL GetLibOwnerDraw()
	{
		return m_Info.bLibOwnerDraw;
	}

	void SetImageList(BYTE* pData, SIZE_T cb)
	{
		HGLOBAL hGlobal;
		if (m_pISImageList)
		{
			GetHGlobalFromStream(m_pISImageList, &hGlobal);
			GlobalUnlock(hGlobal);
			m_pISImageList->Release();
		}
		if (m_hImageList)
			ImageList_Destroy(m_hImageList);
		m_pISImageList = NULL;
		m_hImageList = NULL;
		if (!pData || !cb)
			return;

		hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);
		if (!hGlobal)
			return;
		void* p;
		if (p = GlobalLock(hGlobal))
		{
			memcpy(p, pData, cb);
			GlobalUnlock(hGlobal);
		}
		// 这里用OLE的实现，Shell实现没法拿原始内存
		CreateStreamOnHGlobal(hGlobal, TRUE, &m_pISImageList);
		if (m_pISImageList)
			m_hImageList = ImageList_Read(m_pISImageList);
		else
			GlobalFree(hGlobal);
		m_pISData = (BYTE*)GlobalLock(hGlobal);
	}

	BYTE* GetImageList(int* pcb)
	{
		return NULL;
		//ImageList_Write()
		//return m_pISData;
	}

	eStlInline void SetSelClr(int idx, COLORREF cr)
	{
		if (idx)
			m_Info.crSelBK = cr;
		else
			m_Info.crSelText = cr;
	}

	eStlInline COLORREF GetSelClr(int idx)
	{
		if (idx)
			return m_Info.crSelBK;
		else
			return m_Info.crSelText;
	}

	eStlInline void SetEllipsis(BOOL bEllipsis)
	{
		m_Info.bEllipsis = bEllipsis;
	}

	eStlInline BOOL GetEllipsis()
	{
		return m_Info.bEllipsis;
	}

	eStlInline void SetAlign(BOOL bHAlign, int iAlign)
	{
		if (bHAlign)
			m_Info.iAlignH = iAlign;
		else
			m_Info.iAlignV = iAlign;
	}

	eStlInline int GetAlign(BOOL bHAlign)
	{
		if (bHAlign)
			return m_Info.iAlignH;
		else
			return m_Info.iAlignV;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		SIZE_T cbDir = m_Info.cchDir * sizeof(WCHAR), 
			cbFilePattern = m_Info.cchFilePattern * sizeof(WCHAR);
		auto hGlobal = FlattenInfoBase0(
			sizeof(ELISTBOXDATA) +
			m_Info.cbItems +
			m_Info.cbImageList +
			cbDir +
			cbFilePattern, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		p += cbBaseData;
		// 结构
		memcpy(p, &m_Info, sizeof(ELISTBOXDATA));
		p += sizeof(ELISTBOXDATA);
		// 项目
		
		p += m_Info.cbItems;
		// 图像列表

		p += m_Info.cbImageList;
		// 目录
		memcpy(p, m_pszDir, cbDir);
		p += cbDir;
		// 文件过滤器
		memcpy(p, m_pszFilePattern, cbFilePattern);
		// 
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CListBox(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 表项
			p->SetItems(pPropertyVaule->m_data.m_pData);
			break;
		case 1:// 现行选中项
			p->SetCurrSel(pPropertyVaule->m_int);
			break;
		case 2:// 横向扩展
			p->SetMultiColumn(pPropertyVaule->m_bool);
			return TRUE;
		case 3:// 行高
			p->SetItemHeight(pPropertyVaule->m_int);
			break;
		case 4:// 文本颜色
		case 5:// 背景颜色
			p->SetClr(nPropertyIndex - 4, pPropertyVaule->m_clr);
			break;
		case 6:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 7:// 自动排序
			p->SetAutoSort(pPropertyVaule->m_bool);
			return TRUE;
		case 8:// 鼠标多选
			p->SetMultiSel(pPropertyVaule->m_bool);
			return TRUE;
		case 9:// 按键多选
			p->SetExtSel(pPropertyVaule->m_bool);
			return TRUE;
		case 10:// 工具提示
			p->SetToolTip(pPropertyVaule->m_bool);
			break;
		case 11:// 解析制表符
			p->SetUseTabStop(pPropertyVaule->m_bool);
			return TRUE;
		case 12:// 取整控件高度
			p->SetIntegralHeight(pPropertyVaule->m_bool);
			return TRUE;
		case 13:// 显示禁止滚动条
			p->SetDisableNoScroll(pPropertyVaule->m_bool);
			return TRUE;
		case 14:// 目录
			p->SetDir((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 15:// 文件过滤器
			p->SetFilePattern((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 16:// 文件过滤属性
			p->SetFileAttr(pPropertyVaule->m_int);
			break;
		case 17:// 文件最小日期
			p->SetFileTime(FALSE, pPropertyVaule->m_dtDateTime);
			break;
		case 18:// 文件最大日期
			p->SetFileTime(TRUE, pPropertyVaule->m_dtDateTime);
			break;
		case 19:// 支持库自画
			p->SetLibOwnerDraw(pPropertyVaule->m_bool);
			return TRUE;
		case 20:// 图片组
			p->SetImageList(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 21:// 选中文本颜色
		case 22:// 选中背景颜色
			p->SetSelClr(nPropertyIndex - 21, pPropertyVaule->m_clr);
			break;
		case 23:// 省略号裁剪
			p->SetEllipsis(pPropertyVaule->m_bool);
			break;
		case 24:// 横向对齐
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;
		case 25:// 纵向对齐
			p->SetAlign(FALSE, pPropertyVaule->m_int);
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
		case 0:// 表项
			pPropertyVaule->m_data.m_pData = p->GetItems();
			break;
		case 1:// 现行选中项
			pPropertyVaule->m_int = p->GetCurrSel();
			break;
		case 2:// 横向扩展
			pPropertyVaule->m_bool = p->GetMultiColumn();
			break;
		case 3:// 行高
			pPropertyVaule->m_int = p->GetItemHeight();
			break;
		case 4:// 文本颜色
		case 5:// 背景颜色
			pPropertyVaule->m_clr = p->GetClr(nPropertyIndex - 4);
			break;
		case 6:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 7:// 自动排序
			pPropertyVaule->m_bool = p->GetAutoSort();
			break;
		case 8:// 鼠标多选
			pPropertyVaule->m_bool = p->GetMultiSel();
			break;
		case 9:// 按键多选
			pPropertyVaule->m_bool = p->GetExtSel();
			break;
		case 10:// 工具提示
			pPropertyVaule->m_bool = p->GetToolTip();
			break;
		case 11:// 解析制表符
			pPropertyVaule->m_bool = p->GetUseTabStop();
			break;
		case 12:// 取整控件高度
			pPropertyVaule->m_bool = p->GetIntegralHeight();
			break;
		case 13:// 显示禁止滚动条
			pPropertyVaule->m_bool = p->GetDisableNoScroll();
			break;
		case 14:// 目录
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetDir(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 15:// 文件过滤器
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetFilePattern(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 16:// 文件过滤属性
			pPropertyVaule->m_int = p->GetFileAttr();
			break;
		case 17:// 文件最小日期
			pPropertyVaule->m_dtDateTime = p->GetFileTime(FALSE);
			break;
		case 18:// 文件最大日期
			pPropertyVaule->m_dtDateTime = p->GetFileTime(TRUE);
			break;
		case 19:// 支持库自画
			pPropertyVaule->m_bool = p->GetLibOwnerDraw();
			break;
		case 20:// 图片组
			pPropertyVaule->m_data.m_pData = p->GetImageList(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 21:// 选中文本颜色
		case 22:// 选中背景颜色
			pPropertyVaule->m_clr = p->GetSelClr(nPropertyIndex - 21);
			break;
		case 23:// 省略号裁剪
			pPropertyVaule->m_bool = p->GetEllipsis();
			break;
		case 24:// 横向对齐
			pPropertyVaule->m_int = p->GetAlign(TRUE);
			break;
		case 25:// 纵向对齐
			pPropertyVaule->m_int = p->GetAlign(FALSE);
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
		case 0:// 表项
			ShowListBoxDesignDlg(NULL, NULL);
			*pblModified = TRUE;
			break;
		case 14:// 目录
			if (elibstl::IntputBox(&psz, p->GetDir(NULL)))
			{
				delete[] p->m_pszDir;
				p->m_pszDir = psz;
				if (psz)
					p->m_Info.cchDir = wcslen(psz);
				else
					p->m_Info.cchDir = 0;
				p->AddFile();
				*pblModified = TRUE;
			}
			break;
		case 15:// 过滤器
			if (elibstl::IntputBox(&psz, p->GetFilePattern(NULL)))
			{
				delete[] p->m_pszFilePattern;
				p->m_pszFilePattern = psz;
				if (psz)
					p->m_Info.cchFilePattern = wcslen(psz);
				else
					p->m_Info.cchFilePattern = 0;
				p->AddFile();
				*pblModified = TRUE;
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
SUBCLASS_MGR_INIT(CListBox, SCID_LISTBOXPARENT, SCID_LISTBOX)
ESTL_NAMESPACE_END

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_ListBoxW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CListBox::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CListBox::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CListBox::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CListBox::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CListBox::EInputW;
	case ITF_PROPERTY_UPDATE_UI:
		return (PFN_INTERFACE)elibstl::CListBox::EPropUpdateUI;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CListBox::ENotify;
	}
	return NULL;
}

static EVENT_INFO2 s_Event_ListBox[] =
{
	/*000*/ {"内容被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};

static UNIT_PROPERTY s_Member_ListBox[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"表项", "Items", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*001*/  {"现行选中项", "CurrSel", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*002*/	 {"横向扩展", "MultiColumn", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*003*/  {"行高", "ItemHeight", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*004*/  {"文本颜色", "TextClr", "", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
	/*005*/  {"背景颜色", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),NULL},
	/*006*/  {"边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*007*/  {"自动排序", "AutoSort", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*008*/  {"鼠标多选", "MultiSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*009*/  {"按键多选", "ExtSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*010*/  {"工具提示", "ToolTip", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*011*/  {"解析制表符", "UseTabStop", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*012*/  {"取整控件高度", "IntegralHeight", "是否将控件高度对齐到项目高度的整数倍", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*013*/  {"显示禁止滚动条", "DisableNoScroll", "滚动条不可用时显示禁止的滚动条而不是隐藏滚动条", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*014*/  {"目录", "Dir", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*015*/  {"文件过滤器", "FilePattern", "如“*.mp3”，多个过滤器之间用竖线“|”分隔", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*016*/  {"文件过滤属性", "FileAttr", "以下值的位或组合：1 - 只读  2 - 隐藏  4 - 系统  16 - 目录  32 - 存档  128 - 通常", UD_INT, _PROP_OS(__OS_WIN),  NULL},
	/*017*/  {"文件最小日期", "FileDateMin", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*018*/  {"文件最大日期", "FileDataMax", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*019*/  {"支持库自画", "LibProcOwnerDraw", "支持库内部将其设置为所有者绘制，并自动处理绘制操作，该属性为真时可使用额外的自定义属性/命令", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*020*/  {"图片组", "ImageList", "“支持库自画”属性为真时可使用本属性", UD_IMAGE_LIST, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,  NULL},
	/*021*/  {"选中文本颜色", "SelTextClr", "“支持库自画”属性为真时可使用本属性", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,NULL},
	/*022*/  {"选中背景颜色", "SelBKClr", "“支持库自画”属性为真时可使用本属性", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, NULL},
	/*023*/	 {"省略号裁剪", "Ellipsis", "“支持库自画”属性为真时可使用本属性", UD_BOOL, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,  NULL},
	/*024*/  {"横向对齐方式", "AlignH", "“支持库自画”属性为真时可使用本属性", UD_PICK_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, "左边\0""居中\0""右边\0""\0"},
	/*025*/  {"纵向对齐方式", "AlignV", "“支持库自画”属性为真时可使用本属性", UD_PICK_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,"上边\0""居中\0""下边\0""\0"},
};

static INT s_Cmd_ListBox[] = { 0 };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtListBoxW = {
	"列表框W",//中文名称
	"ListBoxW",//英文名称
	"Unicode列表框，兼有文件框的功能",//说明
	ARRAYSIZE(s_Cmd_ListBox),//命令数量
	s_Cmd_ListBox,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	104,//资源ID
	ARRAYSIZE(s_Event_ListBox),
	s_Event_ListBox,
	ARRAYSIZE(s_Member_ListBox),//属性数
	s_Member_ListBox,//属性指针
	libstl_GetInterface_ListBoxW,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END