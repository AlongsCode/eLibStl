#include "EcontrolHelp.h"

#define SCID_DIRBOX			20230527'03u
#define SCID_DIRBOXPARENT	20230527'04u

ESTL_NAMESPACE_BEGIN
// 目录框
/*
* 版本1数据布局：
* EDIRBOXDATA结构
*/
#define DATA_VER_DIRBOX_1	1
struct EDIRBOXDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	COLORREF crBKClr;		// 背景颜色
	int cchDir;				// 目录字符数，全程维护此值
	BITBOOL bHasButton : 1;			// 加减号
	BITBOOL bHasLine : 1;			// 连线
	BITBOOL bFullRowSel : 1;		// 整行选择
	BITBOOL bFadeInOutExpandos : 1;	// 淡入淡出加减号
	BITBOOL bCheckBox : 1;			// 复选框
	BITBOOL bFile : 1;				// 显示文件
	BITBOOL bNoCache : 1;			// 禁止缓存内容
	BITBOOL bTrackSelect : 1;		// 热点跟踪
};

#define DBITEMFLAG_HASCHILDPATH 1
#define DBITEMFLAG_ISHIDEITEM 1

class CDirBox :public elibstl::CCtrlBase
{
	SUBCLASS_MGR_DECL(CDirBox)
private:
	EDIRBOXDATA m_Info{};

	PWSTR m_pszDir = NULL;
	IImageList* m_pIImageList = NULL;

	int m_cyImage = 0;
public:
	std::wstring m_sCurrPath{};

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_NOTIFY:
		{
			if (!m_CtrlSCInfo.count(((NMHDR*)lParam)->hwndFrom))
				break;
			auto p = m_CtrlSCInfo[((NMHDR*)lParam)->hwndFrom];
			auto pnmtv = (NMTREEVIEWW*)lParam;
			HWND hTV = ((NMHDR*)lParam)->hwndFrom;
			TVITEMEXW tvi;
			switch (((NMHDR*)lParam)->code)
			{
			case TVN_ITEMEXPANDEDA:// 一定要是A版
			{
				if (pnmtv->action == TVE_EXPAND)
				{
					p->SetRedraw(FALSE);
					std::wstring sPath{};
					WCHAR szBuf[MAX_PATH];
					int cch;
					HTREEITEM hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)pnmtv->itemNew.hItem);
					if (!hItem)
						break;
					tvi.mask = TVIF_PARAM | TVIF_TEXT;
					tvi.hItem = hItem;
					tvi.cchTextMax = MAX_PATH - 1;
					tvi.pszText = szBuf;
					SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)&tvi);

					if (tvi.lParam == DBITEMFLAG_ISHIDEITEM)
					{
						tvi.mask = TVIF_TEXT;
						tvi.cchTextMax = MAX_PATH - 1;
						tvi.pszText = szBuf;
						tvi.hItem = pnmtv->itemNew.hItem;
						SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)&tvi);
						sPath = tvi.pszText;
						SendMessageW(hTV, TVM_DELETEITEM, 0, (LPARAM)hItem);
						hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)pnmtv->itemNew.hItem);
						while (hItem)
						{
							tvi.hItem = hItem;
							tvi.cchTextMax = MAX_PATH - 1;
							SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)&tvi);
							cch = wcslen(tvi.pszText);

							if (*(tvi.pszText + cch - 1) == L'\\')
								sPath = std::wstring(tvi.pszText) + sPath;
							else
								sPath = std::wstring(tvi.pszText) + L"\\" + sPath;
							hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem);
						}
						p->EnumFile(sPath.c_str(), pnmtv->itemNew.hItem);
					}
					p->SetRedraw(TRUE);
				}
				else if (pnmtv->action == TVE_COLLAPSE)
				{
					if (!p->m_Info.bNoCache)
						break;
					HTREEITEM hItemTemp;
					HTREEITEM hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)pnmtv->itemNew.hItem);
					if (!hItem)
						break;

					p->SetRedraw(FALSE);
					tvi.mask = TVIF_PARAM;
					tvi.hItem = hItem;
					tvi.lParam = DBITEMFLAG_ISHIDEITEM;
					SendMessageW(hTV, TVM_SETITEMW, 0, (LPARAM)&tvi);

					hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
					while (hItem)
					{
						hItemTemp = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
						SendMessageW(hTV, TVM_DELETEITEM, 0, (LPARAM)hItem);
						hItem = hItemTemp;
					}
					p->SetRedraw(TRUE);
				}
			}
			break;

			case TVN_SELCHANGEDA:
			{
				std::wstring sPath{};
				WCHAR szBuf[MAX_PATH];
				int cch;
				HTREEITEM hItem;

				tvi.mask = TVIF_TEXT;
				tvi.cchTextMax = MAX_PATH - 1;
				tvi.pszText = szBuf;
				tvi.hItem = pnmtv->itemNew.hItem;
				SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)&tvi);
				sPath = tvi.pszText;
				hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)pnmtv->itemNew.hItem);
				while (hItem)
				{
					tvi.hItem = hItem;
					tvi.cchTextMax = MAX_PATH - 1;
					SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)&tvi);
					cch = wcslen(tvi.pszText);

					if (*(tvi.pszText + cch - 1) == L'\\')
						sPath = std::wstring(tvi.pszText) + sPath;
					else
						sPath = std::wstring(tvi.pszText) + L"\\" + sPath;
					hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem);
				}

				p->m_sCurrPath = std::move(sPath);
			}
			break;
			}
		}
		break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CDirBox*)dwRefData;
		switch (uMsg)
		{
		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;

		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_SETFONT:
		{
			LOGFONTA lf;
			GetObjectA((HFONT)wParam, sizeof(lf), &lf);
			int cy = max(p->m_cyImage, lf.lfHeight);
			if (cy < 16)
				cy = -1;
			else
				cy += 4;
			DefSubclassProc(hWnd, TVM_SETITEMHEIGHT, cy, lParam);
		}
		break;
		}

		//SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CDirBox() = delete;
	CDirBox(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);

		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData+ cbBaseData;
			memcpy(&m_Info, p, sizeof(EDIRBOXDATA));
			p += sizeof(EDIRBOXDATA);
			DupStringForNewDeleteW(m_pszDir, (PCWSTR)p, m_Info.cchDir);
		}
		else
		{
			m_Info0.iFrame = 2;
			m_Info.bHasButton = TRUE;
		}
		m_Info.iVer = DATA_VER_DIRBOX_1;

		DWORD dwTVStyle = TVS_SHOWSELALWAYS;
		if (m_Info.bHasButton)
			dwTVStyle |= TVS_HASBUTTONS;
		if (m_Info.bHasLine)
			dwTVStyle |= TVS_HASLINES;
		if (m_Info.bFullRowSel)
			dwTVStyle |= TVS_FULLROWSELECT;
		if (m_Info.bCheckBox)
			dwTVStyle |= TVS_CHECKBOXES;
		if (m_Info.bTrackSelect)
			dwTVStyle |= TVS_TRACKSELECT;
		
		m_hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, WC_TREEVIEWW, NULL, WS_CHILD | WS_CLIPSIBLINGS | dwTVStyle | dwStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);

		UINT uExTVStyle = TVS_EX_DOUBLEBUFFER;
		SendMessageW(m_hWnd, TVM_SETEXTENDEDSTYLE, uExTVStyle, uExTVStyle);

		int cxImage;
		SHGetImageList(SHIL_SMALL, IID_PPV_ARGS(&m_pIImageList));
		SendMessageW(m_hWnd, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)m_pIImageList);
		m_pIImageList->GetIconSize(&cxImage, &m_cyImage);

		SetFadeInOutExpandos(m_Info.bFadeInOutExpandos);
		InitBase0(pAllData);

		FillCtrl();
	}

	HTREEITEM InsertItem(PCWSTR pszText, PWSTR pszNextLevelPath, int cchNextLevelPath,
		HTREEITEM hParentItem, HTREEITEM hItemAfter, BOOL* pbHasChildPath = NULL)
	{
		if (pbHasChildPath)
			*pbHasChildPath = FALSE;
		PWSTR pTemp = pszNextLevelPath + cchNextLevelPath;

		TVINSERTSTRUCTW tis;
		SHFILEINFOW sfi{};
		WIN32_FIND_DATAW wfd;
		HANDLE hFind;
		HTREEITEM hNewItem = NULL;

		if (!SHGetFileInfoW(pszNextLevelPath, 0, &sfi, sizeof(SHFILEINFOW), SHGFI_SYSICONINDEX | SHGFI_SMALLICON))
			return NULL;
		tis.hParent = hParentItem;
		tis.hInsertAfter = hItemAfter;
		tis.itemex.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		tis.itemex.iSelectedImage = tis.itemex.iImage = sfi.iIcon;
		tis.itemex.pszText = (PWSTR)pszText;
		hNewItem = (HTREEITEM)SendMessageW(m_hWnd, TVM_INSERTITEMW, 0, (LPARAM)&tis);

		wcscat(pTemp, L"\\*");
		hFind = FindFirstFileW(pszNextLevelPath, &wfd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (memcmp(wfd.cFileName, L".", 2 * sizeof(WCHAR)) == 0 ||
					memcmp(wfd.cFileName, L"..", 3 * sizeof(WCHAR)) == 0)
					continue;

				tis.hParent = hNewItem;
				tis.hInsertAfter = TVI_FIRST;
				tis.itemex.mask = TVIF_TEXT | TVIF_PARAM;
				tis.itemex.pszText = (PWSTR)L"0";
				tis.itemex.lParam = DBITEMFLAG_ISHIDEITEM;
				SendMessageW(m_hWnd, TVM_INSERTITEMW, 0, (LPARAM)&tis);

				if (pbHasChildPath)
					*pbHasChildPath = TRUE;
				break;
			} while (FindNextFileW(hFind, &wfd));
			FindClose(hFind);
		}

		return hNewItem;
	}

	void EnumFile(PCWSTR pszFile, HTREEITEM hParentItem)
	{
		int cchFile = wcslen(pszFile);
		if (!cchFile)
			return;
		WCHAR pszPath[MAX_PATH];
		wcscpy(pszPath, pszFile);
		PWSTR pszPathTemp = pszPath + cchFile;
		if (*(pszPathTemp - 1) != L'\\')
		{
			wcscpy(pszPathTemp, L"\\*");
			++cchFile;
		}
		else
			wcscpy(pszPathTemp, L"*");

		WCHAR pszNextLevelPath[MAX_PATH];
		PWSTR pszTemp = pszNextLevelPath + cchFile;
		wcscpy(pszNextLevelPath, pszPath);
		*pszTemp = L'\0';

		WIN32_FIND_DATAW wfd;
		HANDLE hFind;
		HTREEITEM hNewItem = NULL, hItemAfterDir = TVI_FIRST, hItemAfterFile = TVI_LAST;

		hFind = FindFirstFileW(pszPath, &wfd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (memcmp(wfd.cFileName, L".", 2 * sizeof(WCHAR)) == 0 ||
					memcmp(wfd.cFileName, L"..", 3 * sizeof(WCHAR)) == 0)
					continue;
				wcscpy(pszTemp, wfd.cFileName);
				if (IsBitExist(wfd.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY))
					hItemAfterDir = InsertItem(wfd.cFileName, pszNextLevelPath, cchFile, hParentItem, hItemAfterDir);
				else if (m_Info.bFile)
					hItemAfterFile = InsertItem(wfd.cFileName, pszNextLevelPath, cchFile, hParentItem, hItemAfterFile);
			} while (FindNextFileW(hFind, &wfd));
			FindClose(hFind);
		}
	}

	void FillCtrl()
	{
		SetRedraw(FALSE);
		SendMessageW(m_hWnd, TVM_DELETEITEM, 0, NULL);
		if (!PathFileExistsW(m_pszDir))
		{
			SetRedraw(TRUE);
			return;
		}

		int cchFile = m_Info.cchDir;
		WCHAR pszPath[MAX_PATH];
		wcscpy(pszPath, m_pszDir);
		if (*(pszPath + cchFile - 1) == L'\\')
			*(pszPath + cchFile - 1) = L'\0';

		WCHAR pszNextLevelPath[MAX_PATH];
		PWSTR pszTemp = pszNextLevelPath + cchFile;
		wcscpy(pszNextLevelPath, m_pszDir);
		if (*(pszTemp - 1) != L'\\')
		{
			wcscpy(pszTemp, L"\\");
			++cchFile;
		}

		BOOL bHasChildPath;
		auto hNewItem = InsertItem(pszPath, pszNextLevelPath, cchFile, TVI_ROOT, TVI_LAST, &bHasChildPath);
		if (bHasChildPath)
		{
			SendMessageW(m_hWnd, TVM_DELETEITEM, 0, SendMessageW(m_hWnd, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hNewItem));
			EnumFile(m_pszDir, hNewItem);
		}
		SendMessageW(m_hWnd, TVM_EXPAND, TVE_EXPAND, (LPARAM)hNewItem);
		SetRedraw(TRUE);
	}

	eStlInline void SetDir(PCWSTR pszDir)
	{
		m_Info.cchDir = DupStringForNewDeleteW(m_pszDir, pszDir);
		FillCtrl();
	}

	eStlInline PCWSTR GetDir(int* pcb)
	{
		if (pcb)
			if (m_pszDir)
				*pcb = (m_Info.cchDir + 1) * sizeof(WCHAR);
			else
				*pcb = 0;
		return m_pszDir;
	}

	eStlInline void SetBKClr(COLORREF cr)
	{
		m_Info.crBKClr = cr;
		Redraw();
	}

	eStlInline COLORREF GetBKClr()
	{
		return m_Info.crBKClr;
	}

	eStlInline void SetHasButton(BOOL bHasButton)
	{
		m_Info.bHasButton = bHasButton;
		ModifyWindowStyle(m_hWnd, bHasButton ? TVS_HASBUTTONS : 0, TVS_HASBUTTONS);
	}

	eStlInline BOOL GetHasButton()
	{
		if (m_bInDesignMode)
			return m_Info.bHasButton;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), TVS_HASBUTTONS);
	}

	eStlInline	void SetHasLine(BOOL bHasLine)
	{
		m_Info.bHasLine = bHasLine;
		ModifyWindowStyle(m_hWnd, bHasLine ? TVS_HASLINES : 0, TVS_HASLINES);
	}

	eStlInline BOOL GetHasLine()
	{
		if (m_bInDesignMode)
			return m_Info.bHasLine;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), TVS_HASLINES);
	}

	eStlInline void SetFullRowSel(BOOL bFullRowSel)
	{
		m_Info.bFullRowSel = bFullRowSel;
		ModifyWindowStyle(m_hWnd, bFullRowSel ? TVS_FULLROWSELECT : 0, TVS_FULLROWSELECT);
	}

	eStlInline BOOL GetFullRowSel()
	{
		if (m_bInDesignMode)
			return m_Info.bFullRowSel;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), TVS_FULLROWSELECT);
	}

	eStlInline void SetFadeInOutExpandos(BOOL bFadeInOutExpandos)
	{
		m_Info.bFadeInOutExpandos = bFadeInOutExpandos;
		SendMessageW(m_hWnd, TVM_SETEXTENDEDSTYLE, TVS_EX_FADEINOUTEXPANDOS, bFadeInOutExpandos ? TVS_EX_FADEINOUTEXPANDOS : 0);
	}

	eStlInline BOOL GetFadeInOutExpandos()
	{
		if (m_bInDesignMode)
			return m_Info.bFadeInOutExpandos;
		else
			return IsBitExist(SendMessageW(m_hWnd, TVM_GETEXTENDEDSTYLE, 0, 0), TVS_EX_FADEINOUTEXPANDOS);
	}

	eStlInline void SetCheckBox(BOOL bCheckBox)
	{
		m_Info.bCheckBox = bCheckBox;
		ModifyWindowStyle(m_hWnd, bCheckBox ? TVS_CHECKBOXES : 0, TVS_CHECKBOXES);
	}

	eStlInline BOOL GetCheckBox()
	{
		if (m_bInDesignMode)
			return m_Info.bCheckBox;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), TVS_CHECKBOXES);
	}

	eStlInline void SetFileShowing(BOOL bFileShowing)
	{
		if (m_Info.bFile != bFileShowing)
		{
			m_Info.bFile = bFileShowing;
			FillCtrl();
		}
	}

	eStlInline BOOL GetFileShowing()
	{
		return m_Info.bFile;
	}

	eStlInline void SetNoCache(BOOL bNoCache)
	{
		m_Info.bNoCache = bNoCache;
	}

	eStlInline BOOL GetNoCache()
	{
		return m_Info.bNoCache;
	}

	eStlInline void SetTrackSel(BOOL bTrackSel)
	{
		m_Info.bTrackSelect = bTrackSel;
		ModifyWindowStyle(m_hWnd, bTrackSel ? TVS_TRACKSELECT : 0, TVS_TRACKSELECT);
	}

	eStlInline BOOL GetTrackSel()
	{
		if (m_bInDesignMode)
			return m_Info.bTrackSelect;
		else
			return IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), TVS_TRACKSELECT);
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;

		auto hGlobal = FlattenInfoBase0(sizeof(EDIRBOXDATA) + m_Info.cchDir * sizeof(WCHAR), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(EDIRBOXDATA));
		p += sizeof(EDIRBOXDATA);
		// 目录
		memcpy(p, m_pszDir, m_Info.cchDir * sizeof(WCHAR));
		// 
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CDirBox(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 目录
			p->SetDir((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 1:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 2:// 背景颜色
			p->SetBKClr(pPropertyVaule->m_clr);
			break;
		case 3:// 加减号
			p->SetHasButton(pPropertyVaule->m_bool);
			break;
		case 4:// 连线
			p->SetHasLine(pPropertyVaule->m_bool);
			break;
		case 5:// 整行选择
			p->SetFullRowSel(pPropertyVaule->m_bool);
			break;
		case 6:// 加减号淡入淡出
			p->SetFadeInOutExpandos(pPropertyVaule->m_bool);
			break;
		case 7:// 复选框
			p->SetCheckBox(pPropertyVaule->m_bool);
			return TRUE;
		case 8:// 显示方式
			p->SetFileShowing(pPropertyVaule->m_bool);
			break;
		case 9:// 字体
			p->SetFont((LOGFONTA*)pPropertyVaule->m_data.m_pData);
			break;
		case 10:// 禁止缓存内容
			p->SetNoCache(pPropertyVaule->m_bool);
			break;
		case 11:// 热点跟踪
			p->SetTrackSel(pPropertyVaule->m_bool);
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
		case 0:// 目录
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetDir(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 1:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 2:// 背景颜色
			pPropertyVaule->m_clr = p->GetBKClr();
			break;
		case 3:// 加减号
			pPropertyVaule->m_bool = p->GetHasButton();
			break;
		case 4:// 连线
			pPropertyVaule->m_bool = p->GetHasLine();
			break;
		case 5:// 整行选择
			pPropertyVaule->m_bool = p->GetFullRowSel();
			break;
		case 6:// 加减号淡入淡出
			pPropertyVaule->m_bool = p->GetFadeInOutExpandos();
			break;
		case 7:// 复选框
			pPropertyVaule->m_bool = p->GetCheckBox();
			break;
		case 8:// 显示方式
			pPropertyVaule->m_bool = p->GetFileShowing();
			break;
		case 9:// 字体
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;
		case 10:// 禁止缓存内容
			pPropertyVaule->m_bool = p->GetNoCache();
			break;
		case 11:// 热点跟踪
			pPropertyVaule->m_bool = p->GetTrackSel();
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
		case 0:// 目录
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetDir(NULL)))
			{
				delete[] p->m_pszDir;
				p->m_pszDir = psz;
				if (psz)
					p->m_Info.cchDir = wcslen(psz);
				else
					p->m_Info.cchDir = 0;
				p->FillCtrl();
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
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 400;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CDirBox, SCID_DIRBOXPARENT, SCID_DIRBOX)
ESTL_NAMESPACE_END

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_DirBoxW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CDirBox::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CDirBox::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CDirBox::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CDirBox::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CDirBox::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CDirBox::ENotify;
	}
	return NULL;
}

static EVENT_INFO2 s_Event_DirBox[] =
{
	/*000*/ {"当前选中项被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_DirBox[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"目录", "Dir", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*001*/	 {"边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*002*/  {"背景颜色", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),  NULL},
	/*003*/  {"加减号", "HasButton", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*004*/  {"连线", "HasLine", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*005*/  {"整行选择", "FullRowSel", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*006*/  {"加减号淡入淡出", "FadeInOutExpandos", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*007*/  {"复选框", "CheckBox", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*008*/	 {"包含文件", "ShowFile", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*009*/	 {"字体", "Font", "", UD_FONT, _PROP_OS(__OS_WIN), NULL},
	/*010*/  {"禁止缓存内容", "DisableContentCache", "本属性为真时每次收缩展开目录都会重新获取子目录", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*011*/  {"热点跟踪", "TrackSel", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
};


EXTERN_C void libstl_DirBox_GetCurrentItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CDirBox::m_CtrlSCInfo[hWnd];

	int cch = p->m_sCurrPath.size();
	pRetData->m_pBin = elibstl::malloc_wstring(cch);
	wcsncpy((PWSTR)(pRetData->m_pBin + 8), p->m_sCurrPath.c_str(), cch);
	*((PWSTR)(pRetData->m_pBin + 8) + cch) = L'\0';
}
FucInfo Fn_DirBoxGetCurrentItem = { {
		/*ccname*/  "取当前选中项",
		/*egname*/  "GetCurrentItem",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_DirBox_GetCurrentItem ,"libstl_DirBox_GetCurrentItem" };

EXTERN_C void libstl_DirBox_Extend(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

	PCWSTR pszPath = elibstl::args_to_pszw(pArgInf, 1);
	if (!pszPath)
		return;
	std::wstring_view svPath(pszPath), svSubStr;
	TVITEMEXW tvi;
	WCHAR szBuf[MAX_PATH];

	HTREEITEM hTopItem = (HTREEITEM)SendMessageW(hWnd, TVM_GETNEXTITEM, TVGN_ROOT, NULL);
	HTREEITEM hItem;
	BOOL bExpand;
	size_t uPos = svPath.find(L"\\");
	size_t uOldPos = 0u;
	SendMessageW(hWnd, WM_SETREDRAW, FALSE, 0);
	while (uPos != std::wstring_view::npos && hTopItem)
	{
		svSubStr = svPath.substr(uOldPos, uPos - uOldPos);
		hItem = hTopItem;
		bExpand = FALSE;
		do
		{
			tvi.mask = TVIF_TEXT;
			tvi.cchTextMax = MAX_PATH - 1;
			tvi.pszText = szBuf;
			tvi.hItem = hItem;
			SendMessageW(hWnd, TVM_GETITEMW, 0, (LPARAM)&tvi);
			if (_wcsnicmp(svSubStr.data(), szBuf, svSubStr.size()) == 0)
			{
				bExpand = TRUE;
				SendMessageW(hWnd, TVM_EXPAND, TVE_EXPAND, (LPARAM)hItem);
				break;
			}
			else
			{
				hItem = (HTREEITEM)SendMessageW(hWnd, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
			}
		} while (hItem);

		if (!bExpand)
			break;
		uOldPos = uPos + 1;
		hTopItem = (HTREEITEM)SendMessageW(hWnd, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);
		uPos = svPath.find(L"\\", uOldPos);
		if (uPos == std::wstring_view::npos && uOldPos < svPath.size())
			uPos = svPath.size();
	}
	SendMessageW(hWnd, WM_SETREDRAW, TRUE, 0);
}
static ARG_INFO s_ArgsExtend[] =
{
	{ "文件或目录","",0,0,SDT_BIN,0,ArgMark::AS_NONE },
};
FucInfo Fn_DirBoxExtend = { {
		/*ccname*/  "展开到",
		/*egname*/  "Extend",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsExtend),
		/*arg lp*/  s_ArgsExtend,
	} , libstl_DirBox_Extend ,"libstl_DirBox_Extend" };

void GetCheckedItemsHelper(HWND hTV, std::vector<BYTE*>& aText, HTREEITEM hParentItem, TVITEMEXW* ptvi)
{
	HTREEITEM hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hParentItem);
	BYTE* pMem;
	while (hItem)
	{
		if ((SendMessageW(hTV, TVM_GETITEMSTATE, (WPARAM)hItem, TVIS_STATEIMAGEMASK) >> 12) == 2)
		{
			ptvi->hItem = hItem;
			ptvi->cchTextMax = MAX_PATH - 1;
			SendMessageW(hTV, TVM_GETITEMW, 0, (LPARAM)ptvi);
			if (ptvi->lParam != DBITEMFLAG_ISHIDEITEM)
			{
				pMem = elibstl::malloc_wstring(wcslen(ptvi->pszText));
				wcscpy((PWSTR)(pMem + 8), ptvi->pszText);
				aText.push_back(pMem);
			}
		}
		GetCheckedItemsHelper(hTV, aText, hItem, ptvi);
		hItem = (HTREEITEM)SendMessageW(hTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
	}
}
EXTERN_C void libstl_DirBox_GetCheckedItems(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

	WCHAR szBuf[MAX_PATH];
	TVITEMEXW tvi;
	tvi.mask = TVIF_TEXT | TVIF_PARAM;
	tvi.pszText = szBuf;
	std::vector<BYTE*> aText{};

	GetCheckedItemsHelper(hWnd, aText, (HTREEITEM)SendMessageW(hWnd, TVM_GETNEXTITEM, TVGN_ROOT, NULL), &tvi);
	size_t c = aText.size();
	if (!c)
	{
		pRetData->m_pAryData = elibstl::malloc_array<BYTE*>(0);// 不能返回NULL
		return;
	}
	pRetData->m_pAryData = elibstl::malloc_array<BYTE*>(c);
	memcpy((BYTE*)pRetData->m_pAryData + 8, aText.data(), c * sizeof(BYTE*));
}
FucInfo Fn_DirBoxGetCheckedItems = { {
		/*ccname*/  "取所有检查项目",
		/*egname*/  "GetCheckedItems",
		/*explain*/ "",
		/*category*/-1,                
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , libstl_DirBox_GetCheckedItems ,"libstl_DirBox_GetCheckedItems" };

EXTERN_C void libstl_DirBox_Refresh(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CDirBox::m_CtrlSCInfo[hWnd];

	p->FillCtrl();
}
FucInfo Fn_DirBoxRefresh = { {
		/*ccname*/  "刷新",
		/*egname*/  "Refresh",
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
	} , libstl_DirBox_Refresh ,"libstl_DirBox_Refresh" };

static INT s_Cmd_DirBox[] = { 270,271,272,273 };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtDirBoxW = {
	"目录框W",//中文名称
	"DirBoxW",//英文名称
	"",//说明
	ARRAYSIZE(s_Cmd_DirBox),//命令数量
	s_Cmd_DirBox,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_DIRBOX_W ,//资源ID
	ARRAYSIZE(s_Event_DirBox),
	s_Event_DirBox,
	ARRAYSIZE(s_Member_DirBox),//属性数
	s_Member_DirBox,//属性指针
	libstl_GetInterface_DirBoxW,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END