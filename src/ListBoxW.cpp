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
		p->hFont = EzFont(L"΢���ź�", 10);

		HWND hCtrl;
		hCtrl = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOINTEGRALHEIGHT,
			DlgPadding, DlgPadding, cxLB, cyLB, hWnd, (HMENU)IDC_LB_ITEMS, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"���⣺", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"��ʾ�ı���", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"ͼ��������", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 2, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"��Ŀ��ֵ��", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 3, cxStatic, cyStatic, hWnd, NULL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_CAPTION, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_TIP, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep * 2, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_IMAGEIDX, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE,
			xEdit, DlgPadding + StaticLineStep * 3, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_ITEMDATA, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"��ǰ����", WS_CHILD | WS_VISIBLE,
			DlgPadding, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTF, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"������", WS_CHILD | WS_VISIBLE,
			DlgPadding * 2 + cxBT, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTB, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"ɾ��", WS_CHILD | WS_VISIBLE,
			DlgPadding * 3 + cxBT * 2, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_DEL, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"ȷ��", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			xBTOK, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_OK, g_elibstl_hModule, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"ȡ��", WS_CHILD | WS_VISIBLE,
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

	EIDEDlgShow(WCN_LISTBOXDESIGN, L"�б����Ŀ����", 600, 325, WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_POPUP, pCtx);

	BOOL bOK = pCtx->bOK;
	delete pCtx;
	return bOK;
}

// �б��
/*
* �汾1���ݲ��֣�
* ELISTBOXDATA�ṹ
* ��Ŀ����
* ͼƬ��
* Ŀ¼��������βNULL��
* �ļ���������������βNULL��
*/
#define DATA_VER_LISTBOX_1	1
struct ELISTBOXDATA
{
	int iVer;				// �汾��
	DWORD dwReserved;		// ����

	int idxCurrSel;			// ����ѡ��
	int cyItem;				// �и�
	COLORREF crText;		// �ı���ɫ
	COLORREF crBK;			// ������ɫ
	COLORREF crSelText;		// ѡ���ı���ɫ
	COLORREF crSelBK;		// ѡ�񱳾���ɫ
	int iAlignH;			// �������
	int iAlignV;			// �������
	UINT uFileAttr;			// �ļ���������
	FILETIME ftMinTime;		// �ļ���Сʱ�䣬����Э������ʱ
	FILETIME ftMaxTime;		// �ļ����ʱ�䣬����Э������ʱ
	SIZE_T cbItems;			// �������ݳ���
	SIZE_T cbImageList;		// ͼƬ�鳤��
	int cchDir;				// Ŀ¼�ַ���
	int cchFilePattern;		// �ļ��������ַ���
	BITBOOL bMultiColumn : 1;	// ������չ
	BITBOOL bAutoSort : 1;	// �Զ�����
	BITBOOL bMultiSel : 1;	// ����ѡ
	BITBOOL bExtSel : 1;	// ������ѡ
	BITBOOL bToolTip : 1;	// ������ʾ
	BITBOOL bUseTabStop : 1;	// �����Ʊ��
	BITBOOL bIntegralHeight : 1;	// ȡ���ؼ��߶�
	BITBOOL bDisableNoScroll : 1;// ��ʾ��ֹ�Ĺ�����
	BITBOOL bLibOwnerDraw : 1;	// ֧�ֿ��Ի�
	BITBOOL bEllipsis : 1;	// ʡ�Ժ�
};

#define DATA_VER_LBITEMS_1 1
// ��Ŀ����ͷ
struct LBITEMSDATAHEADER
{
	int iVer;				// �汾��
	DWORD dwReserved;		// ����

	int cItems;				// ��Ŀ��
};
// ��Ŀ����ͷ����������ʾ�ı��������
struct LBITEMHEADER
{
	int cchCaption;			// �����ַ���
	int cchTip;				// ��ʾ�ַ���
	int idxImage;			// ͼ������
	LPARAM lParam;			// ������ֵ
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
	BYTE* m_pISData = NULL;// �����ͷ�
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
			5/*һ����б�ܣ�����*.*��ͨ���Ϊ��ʱ�ã���һ����βNULL*/) * sizeof(WCHAR));
		assert(pszPath);// ��������
		wcscpy(pszPath, m_pszDir);
		PWSTR pszTemp = pszPath + m_Info.cchDir;// ָ��ָ��Ŀ¼�ĺ��棬�����滻ͨ���

		PWSTR pszFilePattern;
		if (m_Info.cchFilePattern && m_pszFilePattern)
			pszFilePattern = m_pszFilePattern;
		else
		{
#pragma warning(push)
#pragma warning(disable:6255)// ���þ��棺���Ǹ���_malloca
			pszFilePattern = (PWSTR)_alloca(4 * sizeof(WCHAR));
#pragma warning(pop)
			assert(pszFilePattern);// ��������
			wcscpy(pszFilePattern, L"*.*");
		}

		WIN32_FIND_DATAW wfd;
		HANDLE hFind;
		PWSTR pszDivPos, pszOld = pszFilePattern;
		while (TRUE)
		{
			pszDivPos = wcsstr(pszFilePattern, L"|");
			if (pszDivPos != pszOld && pszDivPos)// �������
			{
				int cch = pszDivPos - pszOld - 1;
				wcscpy(pszTemp, L"\\");
				wcsncat(pszTemp, pszOld, cch);
				*(pszTemp + cch + 1) = L'\0';
			}
			else if (!pszDivPos)// �Ҳ�����һ���ָ���
			{
				wcscpy(pszTemp, L"\\");
				wcscat(pszTemp, pszOld);
			}
			else// β����pszDivPos==pszOld��
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

		m_hWnd = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_VSCROLL | WS_CHILD | WS_CLIPSIBLINGS | dwLBStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		// �������
		AddFile();
		SetCurrSel(m_Info.idxCurrSel);
		InitBase0(pAllData);
		if (m_Info.cyItem)// ������InitBase0����
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
		// ������OLE��ʵ�֣�Shellʵ��û����ԭʼ�ڴ�
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
		// �ṹ
		memcpy(p, &m_Info, sizeof(ELISTBOXDATA));
		p += sizeof(ELISTBOXDATA);
		// ��Ŀ

		p += m_Info.cbItems;
		// ͼ���б�

		p += m_Info.cbImageList;
		// Ŀ¼
		memcpy(p, m_pszDir, cbDir);
		p += cbDir;
		// �ļ�������
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
		case 0:// ����
			p->SetItems(pPropertyVaule->m_data.m_pData);
			break;
		case 1:// ����ѡ����
			p->SetCurrSel(pPropertyVaule->m_int);
			break;
		case 2:// ������չ
			p->SetMultiColumn(pPropertyVaule->m_bool);
			return TRUE;
		case 3:// �и�
			p->SetItemHeight(pPropertyVaule->m_int);
			break;
		case 4:// �ı���ɫ
		case 5:// ������ɫ
			p->SetClr(nPropertyIndex - 4, pPropertyVaule->m_clr);
			break;
		case 6:// �߿�
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 7:// �Զ�����
			p->SetAutoSort(pPropertyVaule->m_bool);
			return TRUE;
		case 8:// ����ѡ
			p->SetMultiSel(pPropertyVaule->m_bool);
			return TRUE;
		case 9:// ������ѡ
			p->SetExtSel(pPropertyVaule->m_bool);
			return TRUE;
		case 10:// ������ʾ
			p->SetToolTip(pPropertyVaule->m_bool);
			break;
		case 11:// �����Ʊ��
			p->SetUseTabStop(pPropertyVaule->m_bool);
			return TRUE;
		case 12:// ȡ���ؼ��߶�
			p->SetIntegralHeight(pPropertyVaule->m_bool);
			return TRUE;
		case 13:// ��ʾ��ֹ������
			p->SetDisableNoScroll(pPropertyVaule->m_bool);
			return TRUE;
		case 14:// Ŀ¼
			p->SetDir((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 15:// �ļ�������
			p->SetFilePattern((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 16:// �ļ���������
			p->SetFileAttr(pPropertyVaule->m_int);
			break;
		case 17:// �ļ���С����
			p->SetFileTime(FALSE, pPropertyVaule->m_dtDateTime);
			break;
		case 18:// �ļ��������
			p->SetFileTime(TRUE, pPropertyVaule->m_dtDateTime);
			break;
		case 19:// ֧�ֿ��Ի�
			p->SetLibOwnerDraw(pPropertyVaule->m_bool);
			return TRUE;
		case 20:// ͼƬ��
			p->SetImageList(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 21:// ѡ���ı���ɫ
		case 22:// ѡ�б�����ɫ
			p->SetSelClr(nPropertyIndex - 21, pPropertyVaule->m_clr);
			break;
		case 23:// ʡ�ԺŲü�
			p->SetEllipsis(pPropertyVaule->m_bool);
			break;
		case 24:// �������
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;
		case 25:// �������
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
		case 0:// ����
			pPropertyVaule->m_data.m_pData = p->GetItems();
			break;
		case 1:// ����ѡ����
			pPropertyVaule->m_int = p->GetCurrSel();
			break;
		case 2:// ������չ
			pPropertyVaule->m_bool = p->GetMultiColumn();
			break;
		case 3:// �и�
			pPropertyVaule->m_int = p->GetItemHeight();
			break;
		case 4:// �ı���ɫ
		case 5:// ������ɫ
			pPropertyVaule->m_clr = p->GetClr(nPropertyIndex - 4);
			break;
		case 6:// �߿�
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 7:// �Զ�����
			pPropertyVaule->m_bool = p->GetAutoSort();
			break;
		case 8:// ����ѡ
			pPropertyVaule->m_bool = p->GetMultiSel();
			break;
		case 9:// ������ѡ
			pPropertyVaule->m_bool = p->GetExtSel();
			break;
		case 10:// ������ʾ
			pPropertyVaule->m_bool = p->GetToolTip();
			break;
		case 11:// �����Ʊ��
			pPropertyVaule->m_bool = p->GetUseTabStop();
			break;
		case 12:// ȡ���ؼ��߶�
			pPropertyVaule->m_bool = p->GetIntegralHeight();
			break;
		case 13:// ��ʾ��ֹ������
			pPropertyVaule->m_bool = p->GetDisableNoScroll();
			break;
		case 14:// Ŀ¼
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetDir(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 15:// �ļ�������
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetFilePattern(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 16:// �ļ���������
			pPropertyVaule->m_int = p->GetFileAttr();
			break;
		case 17:// �ļ���С����
			pPropertyVaule->m_dtDateTime = p->GetFileTime(FALSE);
			break;
		case 18:// �ļ��������
			pPropertyVaule->m_dtDateTime = p->GetFileTime(TRUE);
			break;
		case 19:// ֧�ֿ��Ի�
			pPropertyVaule->m_bool = p->GetLibOwnerDraw();
			break;
		case 20:// ͼƬ��
			pPropertyVaule->m_data.m_pData = p->GetImageList(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 21:// ѡ���ı���ɫ
		case 22:// ѡ�б�����ɫ
			pPropertyVaule->m_clr = p->GetSelClr(nPropertyIndex - 21);
			break;
		case 23:// ʡ�ԺŲü�
			pPropertyVaule->m_bool = p->GetEllipsis();
			break;
		case 24:// �������
			pPropertyVaule->m_int = p->GetAlign(TRUE);
			break;
		case 25:// �������
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
		case 0:// ����
			ShowListBoxDesignDlg(NULL, NULL);
			*pblModified = TRUE;
			break;
		case 14:// Ŀ¼
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
		case 15:// ������
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
	/*000*/ {"���ݱ��ı�", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
};

static UNIT_PROPERTY s_Member_ListBox[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	/*000*/  {"����", "Items", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*001*/  {"����ѡ����", "CurrSel", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*002*/	 {"������չ", "MultiColumn", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*003*/  {"�и�", "ItemHeight", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*004*/  {"�ı���ɫ", "TextClr", "", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
	/*005*/  {"������ɫ", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),NULL},
	/*006*/  {"�߿�", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "�ޱ߿�\0""����ʽ\0""͹��ʽ\0""ǳ����ʽ\0""����ʽ\0""���߱߿�ʽ\0""\0"},
	/*007*/  {"�Զ�����", "AutoSort", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*008*/  {"����ѡ", "MultiSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*009*/  {"������ѡ", "ExtSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*010*/  {"������ʾ", "ToolTip", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*011*/  {"�����Ʊ��", "UseTabStop", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*012*/  {"ȡ���ؼ��߶�", "IntegralHeight", "�Ƿ񽫿ؼ��߶ȶ��뵽��Ŀ�߶ȵ�������", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*013*/  {"��ʾ��ֹ������", "DisableNoScroll", "������������ʱ��ʾ��ֹ�Ĺ��������������ع�����", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*014*/  {"Ŀ¼", "Dir", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*015*/  {"�ļ�������", "FilePattern", "�硰*.mp3�������������֮�������ߡ�|���ָ�", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*016*/  {"�ļ���������", "FileAttr", "����ֵ��λ����ϣ�1 - ֻ��  2 - ����  4 - ϵͳ  16 - Ŀ¼  32 - �浵  128 - ͨ��", UD_INT, _PROP_OS(__OS_WIN),  NULL},
	/*017*/  {"�ļ���С����", "FileDateMin", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*018*/  {"�ļ��������", "FileDataMax", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*019*/  {"֧�ֿ��Ի�", "LibProcOwnerDraw", "֧�ֿ��ڲ���������Ϊ�����߻��ƣ����Զ�������Ʋ�����������Ϊ��ʱ��ʹ�ö�����Զ�������/����", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*020*/  {"ͼƬ��", "ImageList", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_IMAGE_LIST, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,  NULL},
	/*021*/  {"ѡ���ı���ɫ", "SelTextClr", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,NULL},
	/*022*/  {"ѡ�б�����ɫ", "SelBKClr", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, NULL},
	/*023*/	 {"ʡ�ԺŲü�", "Ellipsis", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_BOOL, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,  NULL},
	/*024*/  {"������뷽ʽ", "AlignH", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_PICK_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, "���\0""����\0""�ұ�\0""\0"},
	/*025*/  {"������뷽ʽ", "AlignV", "��֧�ֿ��Ի�������Ϊ��ʱ��ʹ�ñ�����", UD_PICK_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT,"�ϱ�\0""����\0""�±�\0""\0"},
};

static INT s_Cmd_ListBox[] = { 0 };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtListBoxW = {
	"�б��W",//��������
	"ListBoxW",//Ӣ������
	"Unicode�б�򣬼����ļ���Ĺ���",//˵��
	ARRAYSIZE(s_Cmd_ListBox),//��������
	s_Cmd_ListBox,//��ȫ�ֺ����ж�Ӧ������
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//��־
	104,//��ԴID
	ARRAYSIZE(s_Event_ListBox),
	s_Event_ListBox,
	ARRAYSIZE(s_Member_ListBox),//������
	s_Member_ListBox,//����ָ��
	libstl_GetInterface_ListBoxW,//��������ӳ���
	NULL,//��Ա����
	NULL//��Ա��������
};
ESTL_NAMESPACE_END