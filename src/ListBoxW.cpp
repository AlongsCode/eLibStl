/*
* 2023.6.1
* TODO：列表框取整高度需要修复
*/
#include "EcontrolHelp.h"

#include <algorithm>

#include <Uxtheme.h>
#include <vsstyle.h>

#define SCID_LISTBOX		20230521'01u
#define SCID_LISTBOXPARENT	20230521'02u

ESTL_NAMESPACE_BEGIN

struct LBITEMCOMMINFO
{
	int idxImage;			// 图像索引
	int iReserved;			// 未用
	COLORREF crText;		// 文本颜色
	COLORREF crBK;			// 背景颜色
	COLORREF crSelText;		// 选中文本颜色
	COLORREF crSelBK;		// 选中背景颜色
	LPARAM lParam;			// 表项数值
	BITBOOL bChecked : 1;	// 是否检查
	BITBOOL bDisabled : 1;	// 是否禁止
};

#pragma warning (push)
#pragma warning (disable:26495)// “未初始化变量”
// 只用于运行时保存信息
struct LBITEMINFO
{
	CSimpleRefStrW rsCaption;	// 标题
	CSimpleRefStrW rsTip;		// 提示文本
	HBRUSH hbrBK;				// 背景画刷
	HBRUSH hbrSelBK;			// 选中背景画刷
	LBITEMCOMMINFO Info;		// 通用信息
};
#pragma warning (pop)

// 只用于设计对话框
struct LBITEMINFO_DESIGN
{
	PWSTR pszTip;			// 提示文本
	LBITEMCOMMINFO Info;	// 通用信息
};
/*
* 版本1数据布局：
* LBITEMSDATAHEADER_MEM结构
* {
*	LBITEMHEADER_MEM结构
*	标题
*	提示文本
* }
*/
#define DATA_VER_LBITEMS_1 1
// 项目数据头，只用于保存数据
struct LBITEMSDATAHEADER_MEM
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int cItems;				// 项目数
};
// 项目属性头，标题与提示文本紧随其后（都附带结尾NULL，便于初始化时插入项目），只用于保存数据
struct LBITEMHEADER_MEM
{
	int cchCaption;			// 标题字符数，包含结尾NULL
	int cchTip;				// 提示字符数，包含结尾NULL
	LBITEMCOMMINFO Info;	// 通用信息
};

struct EDLGCTX_LISTBOXITEMS :public EzDlg::EDLGCTX_BASE
{
	BYTE** ppItemsData;		// 返回数据
	SIZE_T* pcbItems;		// 返回数据长度
	BYTE* pInitData;		// 初始数据
	HIMAGELIST hImageList;	// 图像列表
};

#define WCN_LISTBOXDESIGN L"eLibStl.WndClass.ListBoxItemsDesign"

static ATOM s_atomListBoxItemsDesign = 0;

#define IDC_LB_ITEMS		101
#define IDC_BT_OK			201
#define IDC_BT_CANCEL		202
#define IDC_BT_INSERTF		203
#define IDC_BT_INSERTB		204
#define IDC_BT_DEL			205
#define IDC_BT_SELIMAGE		206
#define IDC_ED_CAPTION		301
#define IDC_ED_TIP			302
#define IDC_ED_IMAGEIDX		303
#define IDC_ED_ITEMDATA		304
#define IDC_CB_CHECKED		401
#define IDC_CB_DISABLE		402
#define IDC_CLP_TEXT		501
#define IDC_CLP_BK			502
#define IDC_CLP_SELTEXT		503
#define IDC_CLP_SELBK		504

#define CWM_CLRPICKERNOTIFY	WM_USER + 2

static LRESULT CALLBACK WndProc_ListBoxDesign(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto p = (EDLGCTX_LISTBOXITEMS*)GetWindowLongPtrW(hWnd, 0);
	switch (uMsg)
	{
	case CWM_CLRPICKERNOTIFY:
	{
		HWND hLB = GetDlgItem(hWnd, IDC_LB_ITEMS);
		int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
		if (iCurrSel == LB_ERR)
			return 0;
		auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
		switch (wParam)
		{
		case IDC_CLP_BK:
			pItem->Info.crBK = lParam;
			break;
		case IDC_CLP_SELBK:
			pItem->Info.crSelBK = lParam;
			break;
		case IDC_CLP_TEXT:
			pItem->Info.crText = lParam;
			break;
		case IDC_CLP_SELTEXT:
			pItem->Info.crSelText = lParam;
			break;
		}
	}
	return 0;

	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
		{
			HWND hLB = GetDlgItem(hWnd, IDC_LB_ITEMS);
			int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
			switch (LOWORD(wParam))
			{
			case IDC_BT_INSERTF:
			case IDC_BT_INSERTB:
			{
				auto pItem = new LBITEMINFO_DESIGN;
				ZeroMemory(pItem, sizeof(LBITEMINFO_DESIGN));
				pItem->Info.idxImage = -1;
				pItem->Info.crBK = pItem->Info.crSelBK = pItem->Info.crText = pItem->Info.crSelText = CLR_DEFAULT;
				int idx = SendMessageW(hLB, LB_INSERTSTRING,
					(LOWORD(wParam) == IDC_BT_INSERTF) ? iCurrSel : iCurrSel + 1, (LPARAM)L"");
				SendMessageW(hLB, LB_SETITEMDATA, idx, (LPARAM)pItem);
				SendMessageW(hLB, LB_SETCURSEL, idx, 0);
				SendMessageW(hWnd, WM_COMMAND, MAKEWPARAM(IDC_LB_ITEMS, LBN_SELCHANGE), (LPARAM)GetDlgItem(hWnd, IDC_LB_ITEMS));
				SetFocus(GetDlgItem(hWnd, IDC_ED_CAPTION));
			}
			return 0;

			case IDC_BT_DEL:
			{
				if (iCurrSel != LB_ERR)
				{
					auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
					delete[] pItem->pszTip;
					delete pItem;
					SendMessageW(hLB, LB_DELETESTRING, iCurrSel, 0);
				}
			}
			return 0;

			case IDC_CB_CHECKED:
			{
				if (iCurrSel == LB_ERR)
					break;
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				pItem->Info.bChecked = (SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);
			}
			return 0;

			case IDC_CB_DISABLE:
			{
				if (iCurrSel == LB_ERR)
					break;
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				pItem->Info.bDisabled = (SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);
			}
			return 0;

			case IDC_BT_OK:
			{
				int cItems = SendMessageW(hLB, LB_GETCOUNT, 0, 0);
				if (cItems <= 0)
				{
					*p->ppItemsData = NULL;
					p->bOK = TRUE;
					EzDlg::EIDEDlgEnd(p);
					return 0;
				}

				int* pcchCaption = new int[cItems];
				int* pcchTip = new int[cItems];

				int iTemp;
				int cchTotal = 0;
				LBITEMINFO_DESIGN* pItem;
				for (int i = 0; i < cItems; ++i)
				{
					iTemp = SendMessageW(hLB, LB_GETTEXTLEN, i, 0) + 1;
					pcchCaption[i] = iTemp;
					cchTotal += iTemp;

					pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);
					if (pItem->pszTip)
						iTemp = wcslen(pItem->pszTip) + 1;
					else
						iTemp = 1;
					pcchTip[i] = iTemp;
					cchTotal += iTemp;
				}

				SIZE_T cbTotal =
					sizeof(LBITEMSDATAHEADER_MEM) +
					sizeof(LBITEMHEADER_MEM) * cItems +
					cchTotal * sizeof(WCHAR);
				BYTE* pData = new BYTE[cbTotal];
				*p->pcbItems = cbTotal;
				*p->ppItemsData = pData;
				auto pHeader = (LBITEMSDATAHEADER_MEM*)pData;
				pHeader->iVer = DATA_VER_LBITEMS_1;
				pHeader->dwReserved = 0;
				pHeader->cItems = cItems;

				pData += sizeof(LBITEMSDATAHEADER_MEM);
				LBITEMHEADER_MEM* pItemHeader;
				for (int i = 0; i < cItems; ++i)
				{
					pItemHeader = (LBITEMHEADER_MEM*)pData;
					pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);

					pItemHeader->cchCaption = pcchCaption[i];
					pItemHeader->cchTip = pcchTip[i];
					pItemHeader->Info = pItem->Info;

					pData += sizeof(LBITEMHEADER_MEM);

					SendMessageW(hLB, LB_GETTEXT, i, (LPARAM)pData);
					pData += (pcchCaption[i] * sizeof(WCHAR));

					if (pItem->pszTip)
						wcscpy((PWSTR)pData, pItem->pszTip);
					else
						*(PWSTR)pData = L'\0';
					pData += (pcchTip[i] * sizeof(WCHAR));
				}

				delete[] pcchCaption;
				delete[] pcchTip;

				p->bOK = TRUE;
				EzDlg::EIDEDlgEnd(p);
			}
			return 0;

			case IDC_BT_CANCEL:
			{
				p->bOK = FALSE;
				EzDlg::EIDEDlgEnd(p);
			}
			return 0;

			case IDC_BT_SELIMAGE:
			{
				if (iCurrSel == LB_ERR)
					break;
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				int idxRet;
				if (ImageListSelectDlg(p->hImageList, pItem->Info.idxImage, &idxRet, hWnd))
				{
					pItem->Info.idxImage = idxRet;
					WCHAR szText[32];
					swprintf(szText, L"%d", idxRet);
					SetDlgItemTextW(hWnd, IDC_ED_IMAGEIDX, szText);
				}
			}
			return 0;
			}
		}
		return 0;

		case EN_CHANGE:
		{
			HWND hLB = GetDlgItem(hWnd, IDC_LB_ITEMS);
			int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
			if (iCurrSel == LB_ERR)
				break;
			switch (LOWORD(wParam))
			{
			case IDC_ED_CAPTION:
			{
				QuickGetWindowTextW(pszText, (HWND)lParam);
				SendMessageW(hLB, WM_SETREDRAW, FALSE, 0);
				SetLBText(hLB, iCurrSel, pszText);
				SendMessageW(hLB, WM_SETREDRAW, TRUE, 0);
				QuickGetWindowTextWFree(pszText);
			}
			break;

			case IDC_ED_TIP:
			{
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				int cch = GetWindowTextLengthW((HWND)lParam);
				delete[] pItem->pszTip;
				if (cch)
				{
					pItem->pszTip = new WCHAR[cch + 1];
					GetWindowTextW((HWND)lParam, pItem->pszTip, cch + 1);
				}
				else
					pItem->pszTip = NULL;
			}
			break;

			case IDC_ED_IMAGEIDX:
			{
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				QuickGetWindowTextW(pszText, (HWND)lParam);
				if (pszText)
					pItem->Info.idxImage = _wtoi(pszText);
				else
					pItem->Info.idxImage = -1;
				QuickGetWindowTextWFree(pszText);
			}
			break;

			case IDC_ED_ITEMDATA:
			{
				auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
				QuickGetWindowTextW(pszText, (HWND)lParam);
				if (pszText)
					pItem->Info.lParam = _wtoi(pszText);
				else
					pItem->Info.lParam = 0;
				QuickGetWindowTextWFree(pszText);
			}
			break;
			}

		}
		return 0;

		case LBN_SELCHANGE:
		{
			if (LOWORD(wParam) != IDC_LB_ITEMS)
				break;
			HWND hLB = (HWND)lParam;
			int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
			if (iCurrSel == LB_ERR)
				break;
			// 标题
			int cch = SendMessageW(hLB, LB_GETTEXTLEN, iCurrSel, 0);
			PWSTR pszText;
			if (cch)
			{
				pszText = (PWSTR)_malloca((cch + 1) * sizeof(WCHAR));
				SendMessageW(hLB, LB_GETTEXT, iCurrSel, (LPARAM)pszText);
			}
			else
				pszText = NULL;
#pragma warning (push)
#pragma warning (disable:6387)// “可能为NULL，不符合函数规范”
			SetDlgItemTextW(hWnd, IDC_ED_CAPTION, pszText);
			_freea(pszText);
			// 提示文本
			auto pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
			SetDlgItemTextW(hWnd, IDC_ED_TIP, pItem->pszTip);
			// 图像索引
			WCHAR szText[48]{};
			swprintf(szText, L"%d", pItem->Info.idxImage);
			SetDlgItemTextW(hWnd, IDC_ED_IMAGEIDX, szText);
			// 表项数值
			swprintf(szText, L"%d", pItem->Info.lParam);
			SetDlgItemTextW(hWnd, IDC_ED_ITEMDATA, szText);
			// 选中
			CheckDlgButton(hWnd, IDC_CB_CHECKED, pItem->Info.bChecked ? BST_CHECKED : BST_UNCHECKED);
			// 禁止
			CheckDlgButton(hWnd, IDC_CB_DISABLE, pItem->Info.bDisabled ? BST_CHECKED : BST_UNCHECKED);
			// 颜色
			ClrPicker::SetColor(GetDlgItem(hWnd, IDC_CLP_BK), pItem->Info.crBK);
			ClrPicker::SetColor(GetDlgItem(hWnd, IDC_CLP_TEXT), pItem->Info.crText);
			ClrPicker::SetColor(GetDlgItem(hWnd, IDC_CLP_SELBK), pItem->Info.crSelBK);
			ClrPicker::SetColor(GetDlgItem(hWnd, IDC_CLP_SELTEXT), pItem->Info.crSelText);
#pragma warning (pop)
		}
		return 0;
		}
	}
	break;

	case WM_CREATE:
	{
#pragma region 创建控件
		constexpr int DlgPadding = 8;
		constexpr int cxLB = 240;
		constexpr int cyLB = 240;
		constexpr int xStatic = 256;
		constexpr int xStatic2 = 400;
		constexpr int cxStatic = 70;
		constexpr int cxStatic2 = 95;
		constexpr int cyStatic = 26;
		constexpr int StaticLineStep = 40;
		constexpr int xEdit = 329;
		constexpr int cxEdit1 = 256;
		constexpr int cxEdit2 = 60;
		constexpr int xBTOK = 384;
		constexpr int cxBT = 96;
		constexpr int cxBTSelImage = 14;
		constexpr int cyBT = 32;
		constexpr int yBT = DlgPadding * 2 + cyLB;
		constexpr int xTip = 361;
		constexpr int yTip = 167;
		constexpr int cxTip = 216;
		constexpr int cyTip = 80;
		constexpr int xClrPicker = 495;
		constexpr int cxClrPicker = 90;
		constexpr int cyClrPicker = 300;

		p = (EDLGCTX_LISTBOXITEMS*)((CREATESTRUCTW*)lParam)->lpCreateParams;
		SetWindowLongPtrW(hWnd, 0, (LONG_PTR)p);
		p->hFont = EzFont(L"微软雅黑", 10);

		HWND hCtrl;
		HWND hLB = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
			DlgPadding, DlgPadding, cxLB, cyLB, hWnd, (HMENU)IDC_LB_ITEMS, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"标题：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"提示文本：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"图像索引：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 2, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"项目数值：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 3, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"文本颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 2, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"背景颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 3, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"选中文本颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 4, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"选中背景颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 5, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_CAPTION, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding + StaticLineStep, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_TIP, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding + StaticLineStep * 2, cxEdit2 - cxBTSelImage, cyStatic, hWnd, (HMENU)IDC_ED_IMAGEIDX, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding + StaticLineStep * 3, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_ITEMDATA, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 2, cxClrPicker, cyClrPicker,
			WS_TABSTOP | WS_GROUP, 0, IDC_CLP_TEXT, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 3, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_BK, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 4, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_SELTEXT, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 5, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_SELBK, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"O", WS_CHILD | WS_TABSTOP | WS_GROUP | WS_VISIBLE,
			xEdit + cxEdit2 - cxBTSelImage, DlgPadding + StaticLineStep * 2, cxBTSelImage, cyStatic, hWnd, (HMENU)IDC_BT_SELIMAGE, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"选中", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | BS_AUTOCHECKBOX,
			xStatic, DlgPadding + StaticLineStep * 4, cxEdit2, cyStatic, hWnd, (HMENU)IDC_CB_CHECKED, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"禁止", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX,
			xEdit, DlgPadding + StaticLineStep * 4, cxEdit2, cyStatic, hWnd, (HMENU)IDC_CB_DISABLE, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"向前插入(&F)", WS_CHILD | WS_TABSTOP | WS_GROUP | WS_VISIBLE,
			DlgPadding, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTF, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"向后插入(&B)", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
			DlgPadding * 2 + cxBT, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_INSERTB, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"删除(&D)", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
			DlgPadding * 3 + cxBT * 2, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_DEL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"确定(&O)", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			xBTOK, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_OK, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"取消(&C)", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
			xBTOK + DlgPadding + cxBT, yBT, cxBT, cyBT, hWnd, (HMENU)IDC_BT_CANCEL, NULL, NULL);

		EzDlg::SetFontForWndAndCtrl(hWnd, p->hFont);
#pragma endregion 创建控件
		BYTE* pData = p->pInitData;
		if (!pData)
			return 0;

		auto pHeader = (LBITEMSDATAHEADER_MEM*)pData;

		int cItems = pHeader->cItems;
		if (cItems <= 0)
			return 0;

		SendMessageW(hLB, WM_SETREDRAW, FALSE, 0);
		SendMessageW(hLB, LB_INITSTORAGE, cItems, 48);

		int cchTotal = 0;
		LBITEMINFO_DESIGN* pItem;
		pData += sizeof(LBITEMSDATAHEADER_MEM);
		LBITEMHEADER_MEM* pItemHeader;
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (LBITEMHEADER_MEM*)pData;
			pData += sizeof(LBITEMHEADER_MEM);
			// 项目头
			pItem = new LBITEMINFO_DESIGN;
			ZeroMemory(pItem, sizeof(LBITEMINFO_DESIGN));
			pItem->Info = pItemHeader->Info;
			// 文本
			int idx = SendMessageW(hLB, LB_ADDSTRING, 0, (LPARAM)pData);
			SendMessageW(hLB, LB_SETITEMDATA, idx, (LPARAM)pItem);
			// 提示文本
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));
			DupStringForNewDeleteW(pItem->pszTip, (PCWSTR)pData);
			pData += (pItemHeader->cchTip * sizeof(WCHAR));
		}
		SendMessageW(hLB, LB_SETCURSEL, 0, 0);
		SendMessageW(hWnd, WM_COMMAND, MAKEWPARAM(IDC_LB_ITEMS, LBN_SELCHANGE), (LPARAM)GetDlgItem(hWnd, IDC_LB_ITEMS));
		SetFocus(GetDlgItem(hWnd, IDC_ED_CAPTION));

		SendMessageW(hLB, WM_SETREDRAW, TRUE, 0);
	}
	return 0;

	case WM_CLOSE:
	{
		p->bOK = FALSE;
		EzDlg::EIDEDlgEnd(p);
	}
	return 0;

	case WM_DESTROY:
	{
		HWND hLB = GetDlgItem(hWnd, IDC_LB_ITEMS);
		LBITEMINFO_DESIGN* pItem;
		for (int i = SendMessageW(hLB, LB_GETCOUNT, 0, 0) - 1; i >= 0; --i)
		{
			pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);
			delete[] pItem->pszTip;
			delete pItem;
		}
		DeleteObject(p->hFont);
		EzDlg::EIDEDlgOnDestroy(p);
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

BOOL ShowListBoxDesignDlg(BYTE** ppItemsData, SIZE_T* pcbItems, BYTE* pInitData, HIMAGELIST hImageList)
{
	auto pCtx = EzDlg::EIDEDlgPreShow<EDLGCTX_LISTBOXITEMS>(&s_atomListBoxItemsDesign, WCN_LISTBOXDESIGN, WndProc_ListBoxDesign);
	if (ppItemsData)
		*ppItemsData = NULL;
	if (pcbItems)
		*pcbItems = 0u;
	pCtx->pInitData = pInitData;
	pCtx->ppItemsData = ppItemsData;
	pCtx->pcbItems = pcbItems;
	pCtx->hImageList = hImageList;

	EzDlg::EIDEDlgShow(WCN_LISTBOXDESIGN, L"列表框项目设置", CW_USEDEFAULT, 0, 600, 325,
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_POPUP, pCtx);

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
	SIZE_T cbItems;			// 表项数据长度，全程维护此值
	SIZE_T cbImageList;		// 图片组长度，仅在保存信息时有效
	int cchDir;				// 目录字符数，全程维护此值
	int cchFilePattern;		// 文件过滤器字符数，全程维护此值
	int iCheckBoxMode;		// 选择列表框模式
	BITBOOL bAutoSort : 1;			// 自动排序
	BITBOOL bMultiSel : 1;			// 鼠标多选
	BITBOOL bExtSel : 1;			// 按键多选
	BITBOOL bToolTip : 1;			// 工具提示
	BITBOOL bIntegralHeight : 1;	// 取整控件高度
	BITBOOL bDisableNoScroll : 1;	// 显示禁止的滚动条
	BITBOOL bEllipsis : 1;			// 省略号
	BITBOOL bBalloonToolTip : 1;	// 气球工具提示
	BITBOOL bDragList : 1;			// 表项可拖动
};

constexpr int c_LBPadding = 3;
#define TTID_LBITEM		20230526'01u

class CListBox :public CCtrlBase
{
	SUBCLASS_MGR_DECL(CListBox)
public:
	ELISTBOXDATA m_Info{};
	//////////图像列表相关
	BOOL m_bImageListNeedDel = FALSE;		// 图像列表句柄是否需要被释放
	HIMAGELIST m_hImageList = NULL;			// 图像列表句柄
	std::vector<BYTE> m_ILData{};			// 图片组数据
	int m_cxImage = 0, m_cyImage = 0;		// 图像列表尺寸
	//////////文件框相关
	PWSTR m_pszDir = NULL;					// 目录
	PWSTR m_pszFilePattern = NULL;			// 过滤器
	//////////通用信息
	HBRUSH m_hbrBK = NULL;					// 通用表项背景画刷
	HBRUSH m_hbrSelBK = NULL;				// 通用选择表项背景画刷
	int m_idxChecked = -1;					// 选中的项目，仅单选模式有效
	BYTE* m_pItems = NULL;					// 项目数据，非设计模式下总为NULL
	HTHEME m_hTheme = NULL;					// 主题句柄，绘制选择框时用
	int m_cxCheckBox = 0;					// 选择框尺寸
	std::vector<LBITEMINFO> m_ItemsInfo{};	// 所有项目
	HWND m_hToolTip = NULL;					// 工具提示窗口句柄
	TTTOOLINFOW m_ti{ sizeof(TTTOOLINFOW),TTF_ABSOLUTE | TTF_TRACK,NULL,TTID_LBITEM };// 工具提示信息
	//////////拖动列表框
	int m_idxDraggingBegin = -1;			// 拖放起始索引
	static UINT m_uMsgDragList;				// 拖动列表框消息
private:
	void UpdateThemeInfo()
	{
		CloseThemeData(m_hTheme);
		m_hTheme = OpenThemeData(m_hWnd, L"Button");
		HDC hDC = GetDC(m_hWnd);
		SIZE size;
		GetThemePartSize(m_hTheme, hDC, BP_CHECKBOX, CBS_CHECKEDNORMAL, NULL, TS_DRAW, &size);
		m_cxCheckBox = size.cx;
		ReleaseDC(m_hWnd, hDC);
	}

	void AddFile()
	{
		if (!m_Info.cchDir)
			return;
		LBDeleteString(-1);

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

			LBITEMCOMMINFO CommInfo{};
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
						LBAddString(wfd.cFileName, NULL, CommInfo);
					else if (wfd.ftCreationTime > m_Info.ftMinTime && wfd.ftCreationTime < m_Info.ftMaxTime)
						LBAddString(wfd.cFileName, NULL, CommInfo);
				}
			} while (FindNextFileW(hFind, &wfd));
			FindClose(hFind);
			if (!pszDivPos)
				break;
		}

		_freea(pszPath);
	}

	int HitTestCheckBox(POINT pt, int* pidxItem = NULL)
	{
		POINT ptScr = pt;
		ClientToScreen(m_hWnd, &ptScr);
		int idx = LBItemFromPt(m_hWnd, ptScr, FALSE);
		if (pidxItem)
			*pidxItem = idx;
		if (idx < 0)
			return -1;

		RECT rcItem;
		if (SendMessageW(m_hWnd, LB_GETITEMRECT, idx, (LPARAM)&rcItem) == LB_ERR)
			return -1;
		rcItem.left += c_LBPadding;
		rcItem.right = rcItem.left + m_cxCheckBox;
		if (PtInRect(&rcItem, pt))
			return idx;
		else
			return -1;
	}

	eStlInline void OnSelChange()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);

		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline BOOL OnBeginDrag(POINT pt)
	{
		m_idxDraggingBegin = LBItemFromPt(m_hWnd, pt, FALSE);
		if (m_idxDraggingBegin >= 0)
		{
			if (m_ItemsInfo[m_idxDraggingBegin].Info.bDisabled)
				return FALSE;
		}

		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 1);
		evt.m_nArgCount = 3;
		ScreenToClient(m_hWnd, &pt);
		evt.m_arg[0].m_inf.m_int = pt.x;
		evt.m_arg[1].m_inf.m_int = pt.y;

		evt.m_arg[2].m_inf.m_int = m_idxDraggingBegin;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
		if (evt.m_blHasRetVal)
			return evt.m_infRetData.m_bool;
		else
			return TRUE;
	}

	eStlInline void OnCancelDrag(POINT pt)
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 2);
		evt.m_nArgCount = 2;
		ScreenToClient(m_hWnd, &pt);
		evt.m_arg[0].m_inf.m_int = pt.x;
		evt.m_arg[1].m_inf.m_int = pt.y;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline int OnDragging(POINT pt)
	{
		int idx = LBItemFromPt(m_hWnd, pt, TRUE);

		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 3);
		evt.m_nArgCount = 4;
		ScreenToClient(m_hWnd, &pt);
		evt.m_arg[0].m_inf.m_int = pt.x;
		evt.m_arg[1].m_inf.m_int = pt.y;

		DrawInsert(m_hParent, m_hWnd, idx);
		evt.m_arg[2].m_inf.m_int = idx;

		evt.m_arg[3].m_inf.m_int = m_idxDraggingBegin;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
		if (evt.m_blHasRetVal)
			return evt.m_infRetData.m_int;
		else
			return 0;
	}

	eStlInline void OnDropped(POINT pt)
	{
		int idx = LBItemFromPt(m_hWnd, pt, FALSE);
		DrawInsert(m_hParent, m_hWnd, -1);

		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 4);
		evt.m_nArgCount = 4;
		ScreenToClient(m_hWnd, &pt);
		evt.m_arg[0].m_inf.m_int = pt.x;
		evt.m_arg[1].m_inf.m_int = pt.y;

		evt.m_arg[2].m_inf.m_int = idx;
		evt.m_arg[3].m_inf.m_int = m_idxDraggingBegin;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);

		BOOL bSwapItem = (evt.m_blHasRetVal ? evt.m_infRetData.m_bool : TRUE);
		if (!bSwapItem || m_idxDraggingBegin < 0 || idx < 0 || m_idxDraggingBegin == idx)
			return;

		LBMoveItem(m_idxDraggingBegin, idx);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		if (uMsg == m_uMsgDragList)
		{
			auto pdli = (DRAGLISTINFO*)lParam;
			if (!m_CtrlSCInfo.count(pdli->hWnd))
				return DefSubclassProc(hWnd, uMsg, wParam, lParam);
			auto p = m_CtrlSCInfo[pdli->hWnd];
			switch (pdli->uNotification)
			{
			case DL_BEGINDRAG:
			{
				auto pdli = (DRAGLISTINFO*)lParam;
				if (!m_CtrlSCInfo.count(pdli->hWnd))
					break;
				auto p = m_CtrlSCInfo[pdli->hWnd];
				return p->OnBeginDrag(pdli->ptCursor);
			}

			case DL_CANCELDRAG:
			{
				auto pdli = (DRAGLISTINFO*)lParam;
				if (!m_CtrlSCInfo.count(pdli->hWnd))
					break;
				auto p = m_CtrlSCInfo[pdli->hWnd];
				p->OnCancelDrag(pdli->ptCursor);
			}
			return 0;// 不使用返回值

			case DL_DRAGGING:
			{
				auto pdli = (DRAGLISTINFO*)lParam;
				if (!m_CtrlSCInfo.count(pdli->hWnd))
					break;
				auto p = m_CtrlSCInfo[pdli->hWnd];
				return p->OnDragging(pdli->ptCursor);
			}

			case DL_DROPPED:
			{
				auto pdli = (DRAGLISTINFO*)lParam;
				if (!m_CtrlSCInfo.count(pdli->hWnd))
					break;
				auto p = m_CtrlSCInfo[pdli->hWnd];
				p->OnDropped(pdli->ptCursor);
			}
			return 0;// 不使用返回值
			}
		}

		switch (uMsg)
		{
		case WM_MEASUREITEM:
		{
			HWND hCtrl = GetDlgItem(hWnd, wParam);
			if (!m_CtrlSCInfo.count(hCtrl))
				break;
			auto pmis = (MEASUREITEMSTRUCT*)lParam;
			auto p = m_CtrlSCInfo[hCtrl];
			pmis->itemHeight = p->m_Info.cyItem;
			return TRUE;
		}
		break;

		case WM_DRAWITEM:
		{
			auto pdis = (DRAWITEMSTRUCT*)lParam;
			if (!m_CtrlSCInfo.count(pdis->hwndItem))
				break;
			auto p = m_CtrlSCInfo[pdis->hwndItem];
			if (pdis->itemID == -1)
				break;
			auto& Item = p->m_ItemsInfo[pdis->itemID];

			HDC hDC = pdis->hDC;
			// 画背景
			if (IsBitExist(pdis->itemState, ODS_SELECTED) && !Item.Info.bDisabled)
			{
				if (Item.hbrSelBK)
					FillRect(hDC, &pdis->rcItem, Item.hbrSelBK);
				else
					FillRect(hDC, &pdis->rcItem, p->m_hbrSelBK);

				if (Item.Info.crSelText != CLR_DEFAULT)
					SetTextColor(hDC, Item.Info.crSelText);
				else if (p->m_Info.crSelText != CLR_DEFAULT)
					SetTextColor(hDC, p->m_Info.crSelText);
				else
					SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			}
			else
			{
				if (Item.hbrBK)
					FillRect(hDC, &pdis->rcItem, Item.hbrBK);
				else
					FillRect(hDC, &pdis->rcItem, p->m_hbrBK);

				if (Item.Info.bDisabled)
					SetTextColor(hDC, GetSysColor(COLOR_GRAYTEXT));
				else if (Item.Info.crText != CLR_DEFAULT)
					SetTextColor(hDC, Item.Info.crText);
				else if (p->m_Info.crText != CLR_DEFAULT)
					SetTextColor(hDC, p->m_Info.crText);
				else
					SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
			}
			// 画选择框
			RECT rc = pdis->rcItem;
			if (p->m_Info.iCheckBoxMode)
			{
				rc.left += c_LBPadding;
				rc.right = rc.left + p->m_cxCheckBox;

				int iPartID;
				int iStateID;
				if (p->m_Info.iCheckBoxMode == 1)
				{
					iPartID = BP_RADIOBUTTON;
					if (p->m_idxChecked == pdis->itemID)
						iStateID = Item.Info.bDisabled ? RBS_CHECKEDDISABLED : RBS_CHECKEDNORMAL;
					else
						iStateID = Item.Info.bDisabled ? RBS_UNCHECKEDDISABLED : RBS_UNCHECKEDNORMAL;
				}
				else
				{
					iPartID = BP_CHECKBOX;
					if (Item.Info.bChecked)
						iStateID = Item.Info.bDisabled ? CBS_CHECKEDDISABLED : CBS_CHECKEDNORMAL;
					else
						iStateID = Item.Info.bDisabled ? CBS_UNCHECKEDDISABLED : CBS_UNCHECKEDNORMAL;
				}
				DrawThemeBackground(p->m_hTheme, hDC, iPartID, iStateID, &rc, NULL);
				rc.right += c_LBPadding;
				rc.left = rc.right;
			}
			else
			{
				rc.left += c_LBPadding;
				rc.right = rc.left;
			}
			// 画图片
			if (p->m_cxImage)
			{
				if (p->m_hImageList && Item.Info.idxImage >= 0)
				{
					ImageList_Draw(p->m_hImageList, Item.Info.idxImage, hDC,
						rc.right,
						rc.top + ((rc.bottom - rc.top) - p->m_cyImage) / 2,
						ILD_NORMAL | (IsBitExist(pdis->itemState, ODS_SELECTED) ? ILD_SELECTED : 0));
				}
				rc.left += (p->m_cxImage + c_LBPadding);
			}
			rc.right = pdis->rcItem.right;
			// 画文本
			UINT uDTFlags = DT_NOCLIP | DT_SINGLELINE |
				MultiSelect<UINT>(p->m_Info.iAlignH, DT_LEFT, DT_CENTER, DT_VCENTER) |
				MultiSelect<UINT>(p->m_Info.iAlignV, DT_TOP, DT_VCENTER, DT_BOTTOM) |
				(p->m_Info.bEllipsis ? DT_END_ELLIPSIS : 0);
			SetBkMode(hDC, TRANSPARENT);
			DrawTextW(hDC, Item.rsCaption, -1, &rc, uDTFlags);
			return TRUE;
		}
		break;

		case WM_NOTIFY:
		{

			if (!m_CtrlSCInfo.count(((NMHDR*)lParam)->hwndFrom))
				break;
			auto p = m_CtrlSCInfo[((NMHDR*)lParam)->hwndFrom];
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				p->OnSelChange();
				return 0;// 不使用返回值
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
		case WM_LBUTTONDOWN:// 更新检查框
		{
			if (!p->m_Info.iCheckBoxMode)
				break;

			POINT pt{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			int idxItem;
			int idx = p->HitTestCheckBox(pt, &idxItem);
			if (idxItem < 0)
				break;
			if (!p->m_ItemsInfo[idxItem].Info.bDisabled && idx >= 0)
				if (p->m_Info.iCheckBoxMode == 1)
				{
					if (p->m_idxChecked != idx)
					{
						if (p->m_idxChecked >= 0)
							p->RedrawItem(p->m_idxChecked);
						p->m_idxChecked = idx;
					}
				}
				else
				{
					BOOLNOT(p->m_ItemsInfo[idx].Info.bChecked);
					p->RedrawItem(idx);
				}
		}
		break;

		case WM_LBUTTONDBLCLK:// 连击修复
		{
			POINT pt{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			int idx = p->HitTestCheckBox(pt);
			if (idx >= 0)
				PostMessageW(hWnd, WM_LBUTTONDOWN, wParam, lParam);
		}
		break;

		case WM_MOUSEMOVE:
		{
			if (!p->m_Info.bToolTip)
				break;
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = 400;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);
		}
		break;

		case WM_MOUSEHOVER:
		{
			if (!p->m_Info.bToolTip)
				break;
			SendMessageW(p->m_hToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)&p->m_ti);
			POINT ptScr{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			ClientToScreen(hWnd, &ptScr);
			int idx = LBItemFromPt(hWnd, ptScr, FALSE);
			if (idx < 0)
				break;
			SendMessageW(p->m_hToolTip, TTM_GETTOOLINFOW, 0, (LPARAM)&p->m_ti);
			p->m_ti.lpszText = p->m_ItemsInfo[idx].rsTip;
			SendMessageW(p->m_hToolTip, TTM_SETTOOLINFOW, 0, (LPARAM)&p->m_ti);
			SendMessageW(p->m_hToolTip, TTM_TRACKPOSITION, 0, MAKELPARAM(ptScr.x, ptScr.y));
			SendMessageW(p->m_hToolTip, TTM_TRACKACTIVATE, TRUE, (LPARAM)&p->m_ti);
		}
		break;

		case WM_MOUSELEAVE:
			if (!p->m_Info.bToolTip)
				break;
			SendMessageW(p->m_hToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)&p->m_ti);
			break;

		case WM_THEMECHANGED:
			p->UpdateThemeInfo();
			break;

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;

		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);
		}

		SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CListBox() = delete;
	CListBox(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);

		BYTE* pILData = NULL;
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			// 结构
			memcpy(&m_Info, p, sizeof(ELISTBOXDATA));
			p += sizeof(ELISTBOXDATA);
			// 项目
			DupStreamForNewDelete(m_pItems, p, m_Info.cbItems);
			p += m_Info.cbItems;
			// 图像列表
			pILData = p;
			p += m_Info.cbImageList;
			// 目录
			DupStringForNewDeleteW(m_pszDir, (PCWSTR)p, m_Info.cchDir);
			p += m_Info.cchDir * sizeof(WCHAR);
			// 过滤器
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
			m_Info.cyItem = 16;
			m_Info.idxCurrSel = -1;
			m_Info.iAlignV = 1;
		}
		m_Info.iVer = DATA_VER_LISTBOX_1;

		if (!m_uMsgDragList)
			m_uMsgDragList = RegisterWindowMessageW(DRAGLISTMSGSTRING);

		DWORD dwLBStyle = LBS_OWNERDRAWFIXED | LBS_NODATA | LBS_NOTIFY;
		if (m_Info.bMultiSel)
			dwLBStyle |= LBS_MULTIPLESEL;
		if (m_Info.bExtSel)
			dwLBStyle |= LBS_EXTENDEDSEL;
		//if (!m_Info.bIntegralHeight)
		dwLBStyle |= LBS_NOINTEGRALHEIGHT;
		if (m_Info.bDisableNoScroll)
			dwLBStyle |= LBS_DISABLENOSCROLL;
		if (!m_Info.bIntegralHeight)
			dwLBStyle |= LBS_NOINTEGRALHEIGHT;

		m_hToolTip = CreateWindowExW(0, TOOLTIPS_CLASSW, NULL,
			WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | (m_Info.bBalloonToolTip ? TTS_BALLOON : 0),
			0, 0, 0, 0, NULL, NULL, NULL, NULL);
		m_hWnd = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_VSCROLL | WS_CHILD | WS_CLIPSIBLINGS | dwLBStyle | dwStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		if (m_Info.bDragList)
			SetDragList(m_Info.bDragList);// 必须在子类化之前
		m_SM.OnCtrlCreate(this);
		UpdateThemeInfo();

		m_ti.hwnd = m_hWnd;
		SendMessageW(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&m_ti);

		SetRedraw(FALSE);
		// 设置图像列表
		if (pILData)
			SetImageList(pILData, m_Info.cbImageList);
		// 插入表项
		if (m_pszDir)
			AddFile();
		else
			SetItems(m_pItems, m_Info.cbItems, TRUE);
		// 
		SetClr(1, m_Info.crBK);
		SetSelClr(1, m_Info.crSelBK);
		SetCurrSel(m_Info.idxCurrSel);

		InitBase0(pAllData);
		if (m_Info.cyItem)// 必须在InitBase0之后
			SetItemHeight(m_Info.cyItem);
		SetRedraw(TRUE);
	}

	~CListBox()
	{
		delete[] m_pItems;
		for (auto& x : m_ItemsInfo)
		{
			DeleteObject(x.hbrBK);
			DeleteObject(x.hbrSelBK);
		}

		DeleteObject(m_hbrBK);
		DeleteObject(m_hbrSelBK);

		delete[] m_pszDir;
		delete[] m_pszFilePattern;

		if (m_bImageListNeedDel)
			ImageList_Destroy(m_hImageList);

		CloseThemeData(m_hTheme);

		DestroyWindow(m_hToolTip);
	}

	int LBInsertString(PCWSTR pszString, PCWSTR pszTip, const LBITEMCOMMINFO& CommInfo, int iPos = -1)
	{
		int idx = SendMessageW(m_hWnd, LB_INSERTSTRING, iPos, (LPARAM)L"");
		if (idx == LB_ERR)
			return -1;
		LBITEMINFO Item{ pszString,pszTip,NULL,NULL,CommInfo };
		if (CommInfo.crBK != CLR_DEFAULT)
			Item.hbrBK = CreateSolidBrush(CommInfo.crBK);
		if (CommInfo.crSelBK != CLR_DEFAULT)
			Item.hbrSelBK = CreateSolidBrush(CommInfo.crSelBK);
		if (!m_Info.bAutoSort)
			if (iPos < 0)
				m_ItemsInfo.push_back(std::move(Item));
			else
				m_ItemsInfo.insert(m_ItemsInfo.begin() + idx, std::move(Item));
		else
		{
			for (int i = 0; i < (int)m_ItemsInfo.size(); ++i)
			{
				if (wcscmp(m_ItemsInfo[i].rsCaption, pszString) > 0)
				{
					m_ItemsInfo.insert(m_ItemsInfo.begin() + i, std::move(Item));
					goto Ret;
				}
			}
			m_ItemsInfo.push_back(std::move(Item));
		}
	Ret:
		return idx;
	}

	int LBAddString(PCWSTR pszString, PCWSTR pszTip, const LBITEMCOMMINFO& CommInfo)
	{
		int idx = SendMessageW(m_hWnd, LB_ADDSTRING, 0, (LPARAM)L"");
		if (idx == LB_ERR)
			return -1;
		LBITEMINFO Item{ pszString,pszTip,NULL,NULL,CommInfo };
		if (CommInfo.crBK != CLR_DEFAULT)
			Item.hbrBK = CreateSolidBrush(CommInfo.crBK);
		if (CommInfo.crSelBK != CLR_DEFAULT)
			Item.hbrSelBK = CreateSolidBrush(CommInfo.crSelBK);
		if (!m_Info.bAutoSort)
			m_ItemsInfo.push_back(std::move(Item));
		else
		{
			for (int i = 0; i < (int)m_ItemsInfo.size(); ++i)
			{
				if (wcscmp(m_ItemsInfo[i].rsCaption, pszString) > 0)
				{
					m_ItemsInfo.insert(m_ItemsInfo.begin() + i, std::move(Item));
					goto Ret;
				}
			}
			m_ItemsInfo.push_back(std::move(Item));
		}
	Ret:
		return idx;
	}

	void LBSetItem(int idx, PCWSTR pszString, PCWSTR pszTip, const LBITEMCOMMINFO& CommInfo)
	{
		LBITEMINFO& Item = m_ItemsInfo[idx];
		Item = { pszString,pszTip,NULL,NULL,CommInfo };
		if (CommInfo.crBK != CLR_DEFAULT)
			Item.hbrBK = CreateSolidBrush(CommInfo.crBK);
		if (CommInfo.crSelBK != CLR_DEFAULT)
			Item.hbrSelBK = CreateSolidBrush(CommInfo.crSelBK);
	}

	BOOL LBDeleteString(int iPos)
	{
		if (iPos < 0)
		{
			SendMessageW(m_hWnd, LB_RESETCONTENT, 0, 0);
			for (auto& x : m_ItemsInfo)
			{
				DeleteObject(x.hbrBK);
				DeleteObject(x.hbrSelBK);
			}
			m_ItemsInfo.resize(0u);
		}
		else if (iPos >= 0 && iPos < (int)m_ItemsInfo.size())
		{
			if (SendMessageW(m_hWnd, LB_DELETESTRING, iPos, 0) == LB_ERR)
				return FALSE;
			auto& Item = m_ItemsInfo[iPos];
			DeleteObject(Item.hbrBK);
			DeleteObject(Item.hbrSelBK);
			m_ItemsInfo.erase(m_ItemsInfo.begin() + iPos);
		}
		Redraw();
		return TRUE;
	}

	BOOL LBInitStorage(int cItems)
	{
		if (SendMessageW(m_hWnd, LB_INITSTORAGE, cItems, 0) == LB_ERRSPACE)
			return FALSE;
		m_ItemsInfo.reserve(cItems);
		return TRUE;
	}

	eStlInline void LBSwapItem(int idx1, int idx2)
	{
		std::swap(m_ItemsInfo[idx1], m_ItemsInfo[idx2]);
		Redraw();
	}

	void LBMoveItem(int idxSrc, int idxDst)
	{
		LBITEMINFO Info = std::move(m_ItemsInfo[idxSrc]);
		if (idxSrc < idxDst)
		{
			m_ItemsInfo.insert(m_ItemsInfo.begin() + idxDst, std::move(Info));
			m_ItemsInfo.erase(m_ItemsInfo.begin() + idxSrc);
		}
		else
		{
			m_ItemsInfo.erase(m_ItemsInfo.begin() + idxSrc);
			m_ItemsInfo.insert(m_ItemsInfo.begin() + idxDst, std::move(Info));
		}
		Redraw();
	}

	eStlInline void RedrawItem(int idx)
	{
		RECT rcItem;
		if (SendMessageW(m_hWnd, LB_GETITEMRECT, idx, (LPARAM)&rcItem) == LB_ERR)
			return;

		InvalidateRect(m_hWnd, &rcItem, TRUE);
	}

	void SetItems(BYTE* pItems, SIZE_T cbItems, BOOL bNoCopy)
	{
		SetRedraw(FALSE);
		LBDeleteString(-1);
		if (!pItems || !cbItems)
		{
			if (m_bInDesignMode)
			{
				delete[] m_pItems;
				m_pItems = NULL;
				m_Info.cbItems = 0u;
			}
			SetRedraw(TRUE);
			return;
		}

		BYTE* pData = pItems;
		LBITEMSDATAHEADER_MEM* pHeader;
		LBITEMHEADER_MEM* pItemHeader;
		PCWSTR pszCaption;
		PCWSTR pszTip;
		if (bNoCopy)
		{
			if (m_pItems != pItems)
				delete[] m_pItems;
			m_pItems = pItems;
			m_Info.cbItems = cbItems;
		}
		else if (m_bInDesignMode)
			m_Info.cbItems = DupStreamForNewDelete(m_pItems, pItems, cbItems);

		pHeader = (LBITEMSDATAHEADER_MEM*)pData;
		pData += sizeof(LBITEMSDATAHEADER_MEM);
		int cItems = pHeader->cItems;
		LBInitStorage(cItems);
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (LBITEMHEADER_MEM*)pData;
			pData += sizeof(LBITEMHEADER_MEM);

			pszCaption = (PCWSTR)pData;
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));
			pszTip = (PCWSTR)pData;
			pData += (pItemHeader->cchTip * sizeof(WCHAR));

			LBAddString(pszCaption, pszTip, pItemHeader->Info);
		}

		SetRedraw(TRUE);
		Redraw();
	}

	BYTE* GetItems()
	{
		if (m_bInDesignMode)
			return m_pItems;

		delete[] m_pItems;
		m_Info.cbItems = 0u;
		int cItems = m_ItemsInfo.size();
		if (!cItems)
			return NULL;

		int cchTotal = 0;
		for (auto& x : m_ItemsInfo)
		{
			cchTotal += (x.rsCaption.m_cchText + 1);
			cchTotal += (x.rsTip.m_cchText + 1);
		}

		SIZE_T cbTotal =
			sizeof(LBITEMSDATAHEADER_MEM) +
			sizeof(LBITEMHEADER_MEM) * cItems +
			cchTotal * sizeof(WCHAR);
		m_Info.cbItems = cbTotal;
		BYTE* pData = new BYTE[cbTotal];
		m_pItems = pData;

		auto pHeader = (LBITEMSDATAHEADER_MEM*)pData;
		pHeader->iVer = DATA_VER_LBITEMS_1;
		pHeader->dwReserved = 0;
		pHeader->cItems = cItems;

		pData += sizeof(LBITEMSDATAHEADER_MEM);
		LBITEMHEADER_MEM* pItemHeader;
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (LBITEMHEADER_MEM*)pData;

			pItemHeader->cchCaption = m_ItemsInfo[i].rsCaption.m_cchText;
			pItemHeader->cchTip = m_ItemsInfo[i].rsTip.m_cchText;
			pItemHeader->Info = m_ItemsInfo[i].Info;

			pData += sizeof(LBITEMHEADER_MEM);

			m_ItemsInfo[i].rsCaption.CopyTo((PWSTR)pData);
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));

			m_ItemsInfo[i].rsTip.CopyTo((PWSTR)pData);
			pData += (pItemHeader->cchTip * sizeof(WCHAR));
		}

		return m_pItems;
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
		{
			int idx = SendMessageW(m_hWnd, LB_GETCURSEL, 0, 0);
			if (idx == LB_ERR)
				return -1;

			if (m_ItemsInfo[idx].Info.bDisabled)
				return -1;
			else
				return idx;
		}
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

	void SetClr(int idx, COLORREF cr)
	{
		if (idx)
		{
			m_Info.crBK = cr;
			DeleteObject(m_hbrBK);
			if (cr != CLR_DEFAULT)
				m_hbrBK = CreateSolidBrush(cr);
			else
				m_hbrBK = GetSysColorBrush(COLOR_WINDOW);
		}
		else
			m_Info.crText = cr;
		Redraw();
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
		if (bAutoSort && m_ItemsInfo.size())
		{
			std::sort(m_ItemsInfo.begin(), m_ItemsInfo.end(),
				[](LBITEMINFO& i1, LBITEMINFO& i2) -> bool
			{
				return wcscmp(i1.rsCaption, i2.rsCaption) < 0;
			});
			Redraw();
		}
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

	void SetImageList(BYTE* pData, SIZE_T cb)
	{
		// 啥乱吴涛真有你的哈，几千几万的字节集到处拷，不留头上那8字节身上难受？
		if (m_hImageList && m_bImageListNeedDel)
			ImageList_Destroy(m_hImageList);

		m_hImageList = NULL;
		m_bImageListNeedDel = FALSE;
		if (!pData || cb <= 8u)
		{
			m_ILData.resize(0u);
			return;
		}

		m_ILData.resize(cb);
		for (SIZE_T i = 0; i < cb; ++i)
			m_ILData[i] = pData[i];

		HGLOBAL hGlobal;
		hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb - 8);
		if (!hGlobal)
			return;

		void* p;
		if (p = GlobalLock(hGlobal))
		{
			memcpy(p, pData + 8, cb - 8);
			GlobalUnlock(hGlobal);
		}

		IStream* pIStream;
		if (SUCCEEDED(CreateStreamOnHGlobal(hGlobal, FALSE, &pIStream)))
		{
			m_hImageList = ImageList_Read(pIStream);
			m_bImageListNeedDel = TRUE;
			pIStream->Release();
			ImageList_GetIconSize(m_hImageList, &m_cxImage, &m_cyImage);
		}
		GlobalFree(hGlobal);
		Redraw();
	}

	BYTE* GetImageList(int* pcb)
	{
		SIZE_T cb = m_ILData.size();
		if (m_bInDesignMode)
		{
			if (cb)
			{
				if (pcb)
					*pcb = cb;
				return m_ILData.data();
			}
			else
			{
				if (pcb)
					*pcb = 0;
				return NULL;
			}
		}

		if (!m_hImageList)
		{
			if (pcb)
				*pcb = 0;
			return NULL;
		}

		HGLOBAL hGlobal;
		hGlobal = GlobalAlloc(GMEM_MOVEABLE, 4);
		if (!hGlobal)
		{
			if (pcb)
				*pcb = 0;
			return NULL;
		}

		IStream* pIStream;
		if (SUCCEEDED(CreateStreamOnHGlobal(hGlobal, FALSE, &pIStream)))
		{
			ImageList_Write(m_hImageList, pIStream);
			pIStream->Release();
		}

		cb = GlobalSize(hGlobal) + 8;

		COLORREF crDef = CLR_DEFAULT;
		BYTE* pData, * pcr;
		if (m_bImageListNeedDel)
			pcr = m_ILData.data() + 4;
		else
			pcr = (BYTE*)&crDef;

		if (pData = (BYTE*)GlobalLock(hGlobal))
		{
			m_ILData.resize(cb);
			m_ILData[0] = 'M';
			m_ILData[1] = 'I';
			m_ILData[2] = 'T';
			m_ILData[3] = 'L';
			m_ILData[4] = pcr[0];
			m_ILData[5] = pcr[1];
			m_ILData[6] = pcr[2];
			m_ILData[7] = pcr[3];
			for (SIZE_T i = 7; i < cb; ++i)
				m_ILData[i] = pData[i];

			GlobalUnlock(hGlobal);
		}
		GlobalFree(hGlobal);

		if (pcb)
			*pcb = cb;
		return m_ILData.data();
	}

	void SetImageList(HIMAGELIST hImageList)
	{
		if (m_hImageList && m_bImageListNeedDel)
			ImageList_Destroy(m_hImageList);

		m_hImageList = NULL;
		m_bImageListNeedDel = FALSE;
		m_ILData.resize(0u);

		m_hImageList = hImageList;
		Redraw();
	}

	eStlInline HIMAGELIST GetImageList(BOOL bRetIntIL)
	{
		if (m_bImageListNeedDel)
			if (bRetIntIL)
				return m_hImageList;
			else
				return NULL;
		else
			return m_hImageList;
	}

	void SetSelClr(int idx, COLORREF cr)
	{
		if (idx)
		{
			m_Info.crSelBK = cr;
			DeleteObject(m_hbrSelBK);
			if (cr != CLR_DEFAULT)
				m_hbrSelBK = CreateSolidBrush(cr);
			else
				m_hbrSelBK = GetSysColorBrush(COLOR_HIGHLIGHT);// 可以删除系统颜色画刷
		}
		else
			m_Info.crSelText = cr;
		Redraw();
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

	eStlInline void SetCheckBoxMode(int iCheckBoxMode)
	{
		m_Info.iCheckBoxMode = iCheckBoxMode;
		Redraw();
	}

	eStlInline int GetCheckBoxMode()
	{
		return m_Info.iCheckBoxMode;
	}

	eStlInline void SetBalloonToolTip(BOOL bBalloonToolTip)
	{
		m_Info.bBalloonToolTip = bBalloonToolTip;
		ModifyWindowStyle(m_hToolTip, bBalloonToolTip ? TTS_BALLOON : 0, TTS_BALLOON);
	}

	eStlInline BOOL GetBalloonToolTip()
	{
		return m_Info.bBalloonToolTip;
	}

	eStlInline void SetDragList(BOOL bDragList)
	{
		m_Info.bDragList = bDragList;
		MakeDragList(m_hWnd);
	}

	eStlInline BOOL GetDragList()
	{
		return m_Info.bDragList;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		GetItems();
		GetImageList(NULL);
		m_Info.cbImageList = m_ILData.size();
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
		memcpy(p, m_pItems, m_Info.cbItems);
		p += m_Info.cbItems;
		// 图像列表
		memcpy(p, m_ILData.data(), m_Info.cbImageList);
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
			p->SetItems(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize, FALSE);
			break;
		case 1:// 现行选中项
			p->SetCurrSel(pPropertyVaule->m_int);
			break;
		case 2:// 行高
			p->SetItemHeight(pPropertyVaule->m_int);
			break;
		case 3:// 文本颜色
		case 4:// 背景颜色
			p->SetClr(nPropertyIndex - 3, pPropertyVaule->m_clr);
			break;
		case 5:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 6:// 自动排序
			p->SetAutoSort(pPropertyVaule->m_bool);
			break;
		case 7:// 鼠标多选
			p->SetMultiSel(pPropertyVaule->m_bool);
			return TRUE;
		case 8:// 按键多选
			p->SetExtSel(pPropertyVaule->m_bool);
			return TRUE;
		case 9:// 工具提示
			p->SetToolTip(pPropertyVaule->m_bool);
			break;
		case 10:// 取整控件高度
			p->SetIntegralHeight(pPropertyVaule->m_bool);
			return TRUE;
		case 11:// 显示禁止滚动条
			p->SetDisableNoScroll(pPropertyVaule->m_bool);
			return TRUE;
		case 12:// 目录
			p->SetDir((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 13:// 文件过滤器
			p->SetFilePattern((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 14:// 文件过滤属性
			p->SetFileAttr(pPropertyVaule->m_int);
			break;
		case 15:// 文件最小日期
			p->SetFileTime(FALSE, pPropertyVaule->m_dtDateTime);
			break;
		case 16:// 文件最大日期
			p->SetFileTime(TRUE, pPropertyVaule->m_dtDateTime);
			break;
		case 17:// 图片组
			p->SetImageList(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 18:// 选中文本颜色
		case 19:// 选中背景颜色
			p->SetSelClr(nPropertyIndex - 18, pPropertyVaule->m_clr);
			break;
		case 20:// 省略号裁剪
			p->SetEllipsis(pPropertyVaule->m_bool);
			break;
		case 21:// 横向对齐
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;
		case 22:// 纵向对齐
			p->SetAlign(FALSE, pPropertyVaule->m_int);
			break;
		case 23:// 选择列表框
			p->SetCheckBoxMode(pPropertyVaule->m_int);
			break;
		case 24:// 字体
			p->SetFont((LOGFONTA*)pPropertyVaule->m_data.m_pData);
			break;
		case 25:// 气球工具提示
			p->SetBalloonToolTip(pPropertyVaule->m_bool);
			break;
		case 26:// 可拖放
			p->SetDragList(pPropertyVaule->m_bool);
			return TRUE;
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
		case 2:// 行高
			pPropertyVaule->m_int = p->GetItemHeight();
			break;
		case 3:// 文本颜色
		case 4:// 背景颜色
			pPropertyVaule->m_clr = p->GetClr(nPropertyIndex - 3);
			break;
		case 5:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 6:// 自动排序
			pPropertyVaule->m_bool = p->GetAutoSort();
			break;
		case 7:// 鼠标多选
			pPropertyVaule->m_bool = p->GetMultiSel();
			break;
		case 8:// 按键多选
			pPropertyVaule->m_bool = p->GetExtSel();
			break;
		case 9:// 工具提示
			pPropertyVaule->m_bool = p->GetToolTip();
			break;
		case 10:// 取整控件高度
			pPropertyVaule->m_bool = p->GetIntegralHeight();
			break;
		case 11:// 显示禁止滚动条
			pPropertyVaule->m_bool = p->GetDisableNoScroll();
			break;
		case 12:// 目录
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetDir(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 13:// 文件过滤器
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetFilePattern(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 14:// 文件过滤属性
			pPropertyVaule->m_int = p->GetFileAttr();
			break;
		case 15:// 文件最小日期
			pPropertyVaule->m_dtDateTime = p->GetFileTime(FALSE);
			break;
		case 16:// 文件最大日期
			pPropertyVaule->m_dtDateTime = p->GetFileTime(TRUE);
			break;
		case 17:// 图片组
			pPropertyVaule->m_data.m_pData = p->GetImageList(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 18:// 选中文本颜色
		case 19:// 选中背景颜色
			pPropertyVaule->m_clr = p->GetSelClr(nPropertyIndex - 18);
			break;
		case 20:// 省略号裁剪
			pPropertyVaule->m_bool = p->GetEllipsis();
			break;
		case 21:// 横向对齐
			pPropertyVaule->m_int = p->GetAlign(TRUE);
			break;
		case 22:// 纵向对齐
			pPropertyVaule->m_int = p->GetAlign(FALSE);
			break;
		case 23:// 选择列表框
			pPropertyVaule->m_int = p->GetCheckBoxMode();
			break;
		case 24:// 字体
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;
		case 25:// 气球工具提示
			pPropertyVaule->m_bool = p->GetBalloonToolTip();
			break;
		case 26:// 表项可拖动
			pPropertyVaule->m_bool = p->GetDragList();
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
		case 0:// 表项
		{
			BYTE* pItems;
			SIZE_T cb;
			BOOL bOK = ShowListBoxDesignDlg(&pItems, &cb, p->GetItems(), p->m_hImageList);
			if (bOK)
				p->SetItems(pItems, cb, TRUE);
			*pblModified = bOK;
		}
		break;

		case 14:// 目录
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
				p->AddFile();
				*pblModified = TRUE;
			}
		}
		break;

		case 15:// 过滤器
		{
			PWSTR psz;
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
SUBCLASS_MGR_INIT(CListBox, SCID_LISTBOXPARENT, SCID_LISTBOX)
UINT CListBox::m_uMsgDragList = 0u;
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
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CListBox::ENotify;
	}
	return NULL;
}
static EVENT_ARG_INFO2 s_EventArgs_LB[] =
{
	{"横向位置","相对客户区",0,SDT_INT},
	{"纵向位置","相对客户区",0,SDT_INT},
	{"光标所在项目索引","",0,SDT_INT},
	{"拖放起始项目索引","",0,SDT_INT},
};
static EVENT_INFO2 s_Event_ListBox[] =
{
	/*000*/ {"选中项被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, NULL, _SDT_NULL},
	/*001*/ {"开始拖放", "返回真允许拖动，返回假禁止拖动，默认返回真", _EVENT_OS(OS_ALL) | EV_IS_VER2, 3, s_EventArgs_LB, SDT_BOOL},
	/*002*/ {"取消拖放", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 2, s_EventArgs_LB, _SDT_NULL},
	/*003*/ {"拖放悬停", "返回值指示光标样式：0 - 常规  1 - 禁止  2 - 复制  3 - 移动，默认返回0", _EVENT_OS(OS_ALL) | EV_IS_VER2, 4, s_EventArgs_LB, SDT_INT},
	/*004*/ {"拖放落下", "返回真则支持库内部自动交换开始项目和结束项目，返回假无动作，默认返回真", _EVENT_OS(OS_ALL) | EV_IS_VER2, 4, s_EventArgs_LB, SDT_BOOL},
};

static UNIT_PROPERTY s_Member_ListBox[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"表项", "Items", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*001*/  {"现行选中项", "CurrSel", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*002*/  {"行高", "ItemHeight", "", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*003*/  {"文本颜色", "TextClr", "", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
	/*004*/  {"背景颜色", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN),NULL},
	/*005*/  {"边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*006*/  {"自动排序", "AutoSort", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*007*/  {"鼠标多选", "MultiSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*008*/  {"按键多选", "ExtSel", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*009*/  {"工具提示", "ToolTip", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*010*/  {"取整控件高度", "IntegralHeight", "是否将控件高度对齐到项目高度的整数倍", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*011*/  {"显示禁止滚动条", "DisableNoScroll", "滚动条不可用时显示禁止的滚动条而不是隐藏滚动条", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*012*/  {"目录", "Dir", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*013*/  {"文件过滤器", "FilePattern", "如“*.mp3”，多个过滤器之间用竖线“|”分隔", UD_CUSTOMIZE, _PROP_OS(__OS_WIN),  NULL},
	/*014*/  {"文件过滤属性", "FileAttr", "以下值的位或组合：1 - 只读  2 - 隐藏  4 - 系统  16 - 目录  32 - 存档  128 - 通常", UD_INT, _PROP_OS(__OS_WIN),  NULL},
	/*015*/  {"文件最小日期", "FileDateMin", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*016*/  {"文件最大日期", "FileDataMax", "", UD_DATE_TIME, _PROP_OS(__OS_WIN),  NULL},
	/*017*/  {"图片组", "ImageList", "", UD_IMAGE_LIST, _PROP_OS(__OS_WIN),  NULL},
	/*018*/  {"选中文本颜色", "SelTextClr", "", UD_COLOR, _PROP_OS(__OS_WIN),NULL},
	/*019*/  {"选中背景颜色", "SelBKClr", "", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
	/*020*/	 {"省略号裁剪", "Ellipsis", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*021*/  {"横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0"},
	/*022*/  {"纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN),"上边\0""居中\0""下边\0""\0"},
	/*023*/  {"选择列表框", "CheckBoxMode", "", UD_PICK_INT, _PROP_OS(__OS_WIN),"无\0""单选列表框\0""复选列表框\0""\0"},
	/*024*/  {"字体", "Font", "", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*025*/	 {"气球式工具提示", "BalloonToolTip", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*026*/	 {"表项可拖动", "DragDrop", "本属性为真时可启用四个额外的拖放事件", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
};

EXTERN_C void libstl_ListBoxW_AddString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	elibstl::LBITEMCOMMINFO CommInfo{};
	CommInfo.crBK = CommInfo.crSelBK = CommInfo.crText = CommInfo.crSelText = CLR_DEFAULT;
	CommInfo.idxImage = -1;
	pRetData->m_int = p->LBAddString(
		elibstl::args_to_pszw(pArgInf, 1),
		elibstl::args_to_pszw(pArgInf, 2),
		CommInfo);
}
static ARG_INFO s_ArgsAddString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL },
	{ "提示文本","",0,0,SDT_BIN,0,AS_DEFAULT_VALUE_IS_EMPTY }
};
FucInfo Fn_ListBoxWAddString = { {
		/*ccname*/  "加入表项",
		/*egname*/  "AddString",
		/*explain*/ "返回表项索引，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsAddString),
		/*arg lp*/  s_ArgsAddString,
	} , ESTLFNAME(libstl_ListBoxW_AddString) };

EXTERN_C void libstl_ListBoxW_InsertString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	elibstl::LBITEMCOMMINFO CommInfo{};
	CommInfo.crBK = CommInfo.crSelBK = CommInfo.crText = CommInfo.crSelText = CLR_DEFAULT;
	CommInfo.idxImage = -1;
	pRetData->m_int = p->LBInsertString(
		elibstl::args_to_pszw(pArgInf, 1),
		elibstl::args_to_pszw(pArgInf, 2),
		CommInfo,
		pArgInf[3].m_int);
}
static ARG_INFO s_ArgsInsertString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL },
	{ "提示文本","",0,0,SDT_BIN,0,AS_DEFAULT_VALUE_IS_EMPTY },
	{ "插入位置","",0,0,SDT_INT,-1,AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ListBoxWInsertString = { {
		/*ccname*/  "插入表项",
		/*egname*/  "InsertString",
		/*explain*/ "返回表项索引，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsInsertString),
		/*arg lp*/  s_ArgsInsertString,
	} , ESTLFNAME(libstl_ListBoxW_InsertString) };

EXTERN_C void libstl_ListBoxW_DelString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	pRetData->m_bool = p->LBDeleteString(pArgInf[1].m_int);
}
static ARG_INFO s_ArgsDelString[] =
{
	{ "删除位置","若为-1则删除所有项目",0,0,SDT_INT,0,0 },
};
FucInfo Fn_ListBoxWDelString = { {
		/*ccname*/  "删除表项",
		/*egname*/  "DelString",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsDelString),
		/*arg lp*/  s_ArgsDelString,
	} , ESTLFNAME(libstl_ListBoxW_DelString) };

EXTERN_C void libstl_ListBoxW_GetItemCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, LB_GETCOUNT, 0, 0);
}
FucInfo Fn_ListBoxWGetItemCount = { {
		/*ccname*/  "取表项数",
		/*egname*/  "GetItemCount",
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
	} , ESTLFNAME(libstl_ListBoxW_GetItemCount) };

EXTERN_C void libstl_ListBoxW_GetTopIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, LB_GETTOPINDEX, 0, 0);
}
FucInfo Fn_ListBoxWGetTopIndex = { {
		/*ccname*/  "取第一可见项",
		/*egname*/  "GetTopIndex",
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
	} , ESTLFNAME(libstl_ListBoxW_GetTopIndex) };

EXTERN_C void libstl_ListBoxW_SetTopIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = (SendMessageW(hWnd, LB_SETTOPINDEX, pArgInf[1].m_int, 0) != LB_ERR);
}
static ARG_INFO s_ArgsSetTopIndex[] =
{
	{ "位置","",0,0,SDT_INT,0,NULL }
};
FucInfo Fn_ListBoxWSetTopIndex = { {
		/*ccname*/  "置第一可见项",
		/*egname*/  "SetTopIndex",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetTopIndex),
		/*arg lp*/  s_ArgsSetTopIndex,
	} , ESTLFNAME(libstl_ListBoxW_SetTopIndex) };

EXTERN_C void libstl_ListBoxW_GetItemlParam(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_int = 0;
		return;
	}

	pRetData->m_int = p->m_ItemsInfo[idx].Info.lParam;
}
static ARG_INFO s_ArgsGetItemlParam[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL }
};
FucInfo Fn_ListBoxWGetItemlParam = { {
		/*ccname*/  "取表项数值",
		/*egname*/  "GetItemlParam",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemlParam),
		/*arg lp*/  s_ArgsGetItemlParam,
	} , ESTLFNAME(libstl_ListBoxW_GetItemlParam) };

EXTERN_C void libstl_ListBoxW_SetItemlParam(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_int = 0;
		return;
	}

	p->m_ItemsInfo[idx].Info.lParam = pArgInf[2].m_int;
}
static ARG_INFO s_ArgsSetItemlParam[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "表项数值","",0,0,SDT_INT,0,NULL }
};
FucInfo Fn_ListBoxWSetItemlParam = { {
		/*ccname*/  "置表项数值",
		/*egname*/  "SetItemlParam",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemlParam),
		/*arg lp*/  s_ArgsSetItemlParam,
	} , ESTLFNAME(libstl_ListBoxW_SetItemlParam) };

EXTERN_C void libstl_ListBoxW_GetItemString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_pBin = NULL;
		return;
	}

	auto& rsCaption = p->m_ItemsInfo[idx].rsCaption;
	if (!rsCaption.m_cchText)
	{
		pRetData->m_pBin = NULL;
		return;
	}

	pRetData->m_pBin = elibstl::malloc_array<BYTE>(rsCaption.m_cchText + 1);
	rsCaption.CopyTo((PWSTR)(pRetData->m_pBin + 8));
}
static ARG_INFO s_ArgsGetItemString[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWGetItemString = { {
		/*ccname*/  "取表项文本",
		/*egname*/  "GetItemString",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemString),
		/*arg lp*/  s_ArgsGetItemString,
	} , ESTLFNAME(libstl_ListBoxW_GetItemString) };

EXTERN_C void libstl_ListBoxW_SetItemString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->m_ItemsInfo[idx].rsCaption = elibstl::args_to_pszw(pArgInf, 2);
	p->Redraw();
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemString[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemString = { {
		/*ccname*/  "置表项文本",
		/*egname*/  "SetItemString",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemString),
		/*arg lp*/  s_ArgsSetItemString,
	} , ESTLFNAME(libstl_ListBoxW_SetItemString) };

EXTERN_C void libstl_ListBoxW_GetSelectedItemCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int cSeledItems = 0;
	for (int i = 0; i < (int)p->m_ItemsInfo.size(); ++i)
	{
		if (SendMessageW(hWnd, LB_GETSEL, i, 0) > 0 && !p->m_ItemsInfo[i].Info.bDisabled)
			++cSeledItems;
	}
	pRetData->m_int = cSeledItems;
}
FucInfo Fn_ListBoxWGetSelectedItemCount = { {
		/*ccname*/  "取选中表项数",
		/*egname*/  "GetSelectedItemCount",
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
	} , ESTLFNAME(libstl_ListBoxW_GetSelectedItemCount) };

EXTERN_C void libstl_ListBoxW_GetSelectedItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int cSeledItems = SendMessageW(hWnd, LB_GETSELCOUNT, 0, 0);
	if (cSeledItems <= 0)
	{
		pRetData->m_pAryData = NULL;
		return;
	}

	int* pArray = (int*)_malloca(cSeledItems * sizeof(int));
	if (!pArray)
	{
		pRetData->m_pAryData = NULL;
		return;
	}
	cSeledItems = 0;
	for (int i = 0; i < (int)p->m_ItemsInfo.size(); ++i)
	{
		if (SendMessageW(hWnd, LB_GETSEL, i, 0) > 0 && !p->m_ItemsInfo[i].Info.bDisabled)
		{
			pArray[cSeledItems] = i;
			++cSeledItems;
		}
	}
	pRetData->m_pAryData = elibstl::malloc_array<int>(cSeledItems);
	memcpy((BYTE*)pRetData->m_pAryData + 8, pArray, cSeledItems * sizeof(int));
	_freea(pArray);
}
FucInfo Fn_ListBoxWGetSelectedItem = { {
		/*ccname*/  "取选中表项",
		/*egname*/  "GetSelectedItem",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} , ESTLFNAME(libstl_ListBoxW_GetSelectedItem) };

EXTERN_C void libstl_ListBoxW_IsItemSelected(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	pRetData->m_bool = ((SendMessageW(hWnd, LB_GETSEL, idx, 0) > 0) && (!p->m_ItemsInfo[idx].Info.bDisabled));
}
static ARG_INFO s_ArgsIsItemSelected[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWIsItemSelected = { {
		/*ccname*/  "表项是否选中 ",
		/*egname*/  "IsItemSelected",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsIsItemSelected),
		/*arg lp*/  s_ArgsIsItemSelected,
	} , ESTLFNAME(libstl_ListBoxW_IsItemSelected) };

EXTERN_C void libstl_ListBoxW_GetItemCheckState(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	if (p->m_Info.iCheckBoxMode == 1)
		pRetData->m_bool = (p->m_idxChecked == idx);
	else
		pRetData->m_bool = p->m_ItemsInfo[idx].Info.bChecked;
}
static ARG_INFO s_ArgsGetItemCheckState[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWGetItemCheckState = { {
		/*ccname*/  "取表项检查状态",
		/*egname*/  "GetItemCheckState",
		/*explain*/ "返回0为选中，返回1选中",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemCheckState),
		/*arg lp*/  s_ArgsGetItemCheckState,
	} , ESTLFNAME(libstl_ListBoxW_GetItemCheckState) };

EXTERN_C void libstl_ListBoxW_SetItemCheckState(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	if (p->m_Info.iCheckBoxMode == 1)
		if (pArgInf[2].m_int == 1)
			p->m_idxChecked = idx;
		else
			p->m_idxChecked = -1;
	else
		if (pArgInf[2].m_int == 1)
			p->m_ItemsInfo[idx].Info.bChecked = TRUE;
		else
			p->m_ItemsInfo[idx].Info.bChecked = FALSE;
	p->RedrawItem(idx);
}
static ARG_INFO s_ArgsSetItemCheckState[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "检查状态","0 - 未选中  1 - 选中",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWSetItemCheckState = { {
		/*ccname*/  "置表项检查状态",
		/*egname*/  "SetItemCheckState",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemCheckState),
		/*arg lp*/  s_ArgsSetItemCheckState,
	} , ESTLFNAME(libstl_ListBoxW_SetItemCheckState) };

EXTERN_C void libstl_ListBoxW_SelectItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	DWORD dwStyle = GetWindowLongPtrW(hWnd, GWL_STYLE);
	if (elibstl::IsBitExist(dwStyle, LBS_MULTIPLESEL) || elibstl::IsBitExist(dwStyle, LBS_EXTENDEDSEL))
		pRetData->m_bool = (SendMessageW(hWnd, LB_SETSEL, pArgInf[2].m_bool, pArgInf[1].m_int) != LB_ERR);
	else
		pRetData->m_bool = (SendMessageW(hWnd, LB_SETCURSEL, 0, pArgInf[2].m_bool ? pArgInf[1].m_int : -1) != LB_ERR);
}
static ARG_INFO s_ArgsSelectItem[] =
{
	{ "索引","若为多选模式，则传递-1会操作所有项",0,0,SDT_INT,0,NULL },
	{ "是否选择","",0,0,SDT_BOOL,0,NULL },
};
FucInfo Fn_ListBoxWSelectItem = { {
		/*ccname*/  "选中表项",
		/*egname*/  "SelectItem",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSelectItem),
		/*arg lp*/  s_ArgsSelectItem,
	} , ESTLFNAME(libstl_ListBoxW_SelectItem) };

EXTERN_C void libstl_ListBoxW_FindString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[2].m_int;
	int cItems = p->m_ItemsInfo.size();
	if (idx < 0 || idx > cItems)
	{
		pRetData->m_int = -1;
		return;
	}

	PCWSTR pszSub = elibstl::args_to_pszw(pArgInf, 1);
	if (!pszSub)
	{
		pRetData->m_int = -1;
		return;
	}
	int cchSub = wcslen(pszSub);

	switch (pArgInf[3].m_int)
	{
	case 0:
		for (int i = idx; i < cItems; ++i)
		{
			if (std::wstring_view(p->m_ItemsInfo[i].rsCaption).find(pszSub) != std::wstring_view::npos)
			{
				pRetData->m_int = i;
				return;
			}
		}
		break;

	case 1:
		for (int i = idx; i < cItems; ++i)
		{
			if (std::wstring_view(p->m_ItemsInfo[i].rsCaption).find(pszSub) == 0)
			{
				pRetData->m_int = i;
				return;
			}
		}
		break;

	case 2:
		for (int i = idx; i < cItems; ++i)
		{
			if (std::wstring_view(p->m_ItemsInfo[i].rsCaption).rfind(pszSub) == p->m_ItemsInfo[i].rsCaption.m_cchText - cchSub)
			{
				pRetData->m_int = i;
				return;
			}
		}
		break;

	case 3:
		for (int i = idx; i < cItems; ++i)
		{
			if (p->m_ItemsInfo[i].rsCaption.m_cchText == cchSub)
			{
				if (p->m_ItemsInfo[i].rsCaption == pszSub)
				{
					pRetData->m_int = i;
					return;
				}
			}
		}
		break;
	}
	pRetData->m_int = -1;
	return;
}
static ARG_INFO s_ArgsFindString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL },
	{ "起始搜寻索引","",0,0,SDT_INT,0,AS_HAS_DEFAULT_VALUE },
	{ "匹配模式","0 - 包含  1 - 头部  2 - 尾部  3 - 相同",0,0,SDT_INT,0,AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ListBoxWFindString = { {
		/*ccname*/  "寻找表项",
		/*egname*/  "FindString",
		/*explain*/ "成功返回找到的表项索引，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsFindString),
		/*arg lp*/  s_ArgsFindString,
	} , ESTLFNAME(libstl_ListBoxW_FindString) };

EXTERN_C void libstl_ListBoxW_GetItemColor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_int = 0;
		return;
	}

	switch (pArgInf[2].m_int)
	{
	case 0:pRetData->m_int = p->m_ItemsInfo[idx].Info.crBK; break;
	case 1:pRetData->m_int = p->m_ItemsInfo[idx].Info.crSelBK; break;
	case 2:pRetData->m_int = p->m_ItemsInfo[idx].Info.crText; break;
	case 3:pRetData->m_int = p->m_ItemsInfo[idx].Info.crSelText; break;
	default:pRetData->m_int = 0; break;
	}
}
static ARG_INFO s_ArgsGetItemColor[] =
{
	{ "索引","",0,0,SDT_INT,0,0 },
	{ "类型","0 - 背景  1 - 选中背景  2 - 文本  3 - 选中文本",0,0,SDT_INT,0,0 },
};
FucInfo Fn_ListBoxWGetItemColor = { {
		/*ccname*/  "取表项颜色",
		/*egname*/  "GetItemColor",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemColor),
		/*arg lp*/  s_ArgsGetItemColor,
	} , ESTLFNAME(libstl_ListBoxW_GetItemColor) };

EXTERN_C void libstl_ListBoxW_SetItemColor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}
	COLORREF cr = pArgInf[3].m_int;

	elibstl::LBITEMINFO& Item = p->m_ItemsInfo[idx];
	switch (pArgInf[2].m_int)
	{
	case 0:
		DeleteObject(Item.hbrBK);
		if (cr == CLR_DEFAULT)
			Item.hbrBK = NULL;
		else
			Item.hbrBK = CreateSolidBrush(cr);
		Item.Info.crBK = cr;
		break;
	case 1:
		DeleteObject(Item.hbrSelBK);
		if (cr == CLR_DEFAULT)
			Item.hbrSelBK = NULL;
		else
			Item.hbrSelBK = CreateSolidBrush(cr);
		Item.Info.crSelBK = cr;
		break;
	case 2:
		Item.Info.crText = cr;
		break;
	case 3:
		Item.Info.crSelText = cr;
		break;
	default:
		pRetData->m_bool = FALSE;
		return;
	}
	p->RedrawItem(idx);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemColor[] =
{
	{ "索引","",0,0,SDT_INT,0,0 },
	{ "类型","0 - 背景  1 - 选中背景  2 - 文本  3 - 选中文本",0,0,SDT_INT,0,0 },
	{ "颜色","若要保持缺省，传递 #默认色 常量",0,0,SDT_INT,0,0 },
};
FucInfo Fn_ListBoxWSetItemColor = { {
		/*ccname*/  "置表项颜色",
		/*egname*/  "SetItemColor",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemColor),
		/*arg lp*/  s_ArgsSetItemColor,
	} , ESTLFNAME(libstl_ListBoxW_SetItemColor) };

EXTERN_C void libstl_ListBoxW_GetItemTip(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_pBin = NULL;
		return;
	}

	auto& rsTip = p->m_ItemsInfo[idx].rsTip;
	if (!rsTip.m_cchText)
	{
		pRetData->m_pBin = NULL;
		return;
	}

	pRetData->m_pBin = elibstl::malloc_array<BYTE>(rsTip.m_cchText + 1);
	rsTip.CopyTo((PWSTR)(pRetData->m_pBin + 8));
}
static ARG_INFO s_ArgsGetItemTip[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWGetItemTip = { {
		/*ccname*/  "取表项提示文本",
		/*egname*/  "GetItemTip",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemTip),
		/*arg lp*/  s_ArgsGetItemTip,
	} , ESTLFNAME(libstl_ListBoxW_GetItemTip) };

EXTERN_C void libstl_ListBoxW_SetItemTip(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->m_ItemsInfo[idx].rsTip = elibstl::args_to_pszw(pArgInf, 2);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemTip[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemTip = { {
		/*ccname*/  "置表项提示文本",
		/*egname*/  "SetItemTip",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemTip),
		/*arg lp*/  s_ArgsSetItemTip,
	} , ESTLFNAME(libstl_ListBoxW_SetItemTip) };

EXTERN_C void libstl_ListBoxW_GetItemImageIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_int = -1;
		return;
	}

	pRetData->m_int = p->m_ItemsInfo[idx].Info.idxImage;
}
static ARG_INFO s_ArgsGetItemImageIndex[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWGetItemImageIndex = { {
		/*ccname*/  "取表项图片索引",
		/*egname*/  "GetItemImageIndex",
		/*explain*/ "失败或无图片返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemImageIndex),
		/*arg lp*/  s_ArgsGetItemImageIndex,
	} , ESTLFNAME(libstl_ListBoxW_GetItemImageIndex) };

EXTERN_C void libstl_ListBoxW_SetItemImageIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->m_ItemsInfo[idx].Info.idxImage = pArgInf[2].m_int;
	p->RedrawItem(idx);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemImageIndex[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "图片索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWSetItemImageIndex = { {
		/*ccname*/  "置表项图片索引",
		/*egname*/  "SetItemImageIndex",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetItemImageIndex),
		/*arg lp*/  s_ArgsSetItemImageIndex,
	} , ESTLFNAME(libstl_ListBoxW_SetItemImageIndex) };

EXTERN_C void libstl_ListBoxW_InitStorage(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	if (pArgInf[1].m_int <= 0)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	pRetData->m_bool = p->LBInitStorage(pArgInf[1].m_int);
}
static ARG_INFO s_ArgsInitStorage[] =
{
	{ "项目数","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWInitStorage = { {
		/*ccname*/  "保留内存",
		/*egname*/  "InitStorage",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsInitStorage),
		/*arg lp*/  s_ArgsInitStorage,
	} , ESTLFNAME(libstl_ListBoxW_InitStorage) };

EXTERN_C void libstl_ListBoxW_GetImageList(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	pRetData->m_int = (int)p->GetImageList(pArgInf[1].m_bool);
}
static ARG_INFO s_ArgsGetImageList[] =
{
	{ "是否返回非外部图像列表","若本参数为真则返回值可能是控件内部维护的图像列表，绝对不能在外部删除或修改该图像列表",0,0,SDT_BOOL,FALSE,AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ListBoxWGetImageList = { {
		/*ccname*/  "取图像列表句柄",
		/*egname*/  "GetImageList",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetImageList),
		/*arg lp*/  s_ArgsGetImageList,
	} , ESTLFNAME(libstl_ListBoxW_GetImageList) };

EXTERN_C void libstl_ListBoxW_SetImageList(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	p->SetImageList((HIMAGELIST)pArgInf[1].m_int);
}
static ARG_INFO s_ArgsSetImageList[] =
{
	{ "图像列表句柄","改图像列表由调用者维护，控件不会修改或删除它",0,0,SDT_INT,0,0 },
};
FucInfo Fn_ListBoxWSetImageList = { {
		/*ccname*/  "置图像列表句柄",
		/*egname*/  "SetImageList",
		/*explain*/ "易语言的字节集图片组太过闹弹，于是本方法应运而生，杜绝啥乱贵物字节集从我做起",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetImageList),
		/*arg lp*/  s_ArgsSetImageList,
	} , ESTLFNAME(libstl_ListBoxW_SetImageList) };

EXTERN_C void libstl_ListBoxW_GetItemRect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

	RECT rc;
	if (SendMessageW(hWnd, LB_GETITEMRECT, pArgInf[1].m_int, (LPARAM)&rc) == LB_ERR)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	if (pArgInf[2].m_dtDataType != _SDT_NULL)
		*pArgInf[2].m_pInt = rc.left;
	if (pArgInf[3].m_dtDataType != _SDT_NULL)
		*pArgInf[3].m_pInt = rc.top;
	if (pArgInf[4].m_dtDataType != _SDT_NULL)
		*pArgInf[4].m_pInt = rc.right;
	if (pArgInf[5].m_dtDataType != _SDT_NULL)
		*pArgInf[5].m_pInt = rc.bottom;
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsGetItemRect[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "接收左边变量","",0,0,SDT_INT,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
	{ "接收顶边变量","",0,0,SDT_INT,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
	{ "接收右边变量","",0,0,SDT_INT,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
	{ "接收底边变量","",0,0,SDT_INT,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
};
FucInfo Fn_ListBoxWGetItemRect = { {
		/*ccname*/  "取表项矩形",
		/*egname*/  "GetItemRect",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemRect),
		/*arg lp*/  s_ArgsGetItemRect,
	} , ESTLFNAME(libstl_ListBoxW_GetItemRect) };

EXTERN_C void libstl_ListBoxW_HitTest(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	POINT pt{ pArgInf[1].m_int,pArgInf[2].m_int };
	int idx = LBItemFromPt(hWnd, pt, FALSE);
	pRetData->m_int = idx;
	if (idx < 0)
	{
		if (pArgInf[3].m_dtDataType != _SDT_NULL)
			*pArgInf[3].m_pBool = FALSE;
		if (pArgInf[4].m_dtDataType != _SDT_NULL)
			*pArgInf[4].m_pBool = FALSE;
		return;
	}

	if (pArgInf[3].m_dtDataType == _SDT_NULL && pArgInf[4].m_dtDataType == _SDT_NULL)
		return;

	RECT rcItem, rc;
	SendMessageW(hWnd, LB_GETITEMRECT, idx, (LPARAM)&rcItem);

	BOOL bHitCheckBox = FALSE, bHitImage = FALSE;
	if (p->m_Info.iCheckBoxMode)
	{
		rc = rcItem;
		rc.left += elibstl::c_LBPadding;
		rc.right = p->m_cxCheckBox;

		bHitCheckBox = PtInRect(&rc, pt);
	}

	if (p->m_cxImage)
	{
		rc.left = p->m_cxCheckBox + elibstl::c_LBPadding * 2;
		rc.right = rc.left + p->m_cxImage;
		rc.top = rcItem.top + (rcItem.bottom - rcItem.top - p->m_cyImage) / 2;
		rc.bottom = rc.top + p->m_cyImage;

		bHitCheckBox = PtInRect(&rc, pt);
	}

	if (pArgInf[3].m_dtDataType != _SDT_NULL)
		*pArgInf[3].m_pBool = bHitCheckBox;
	if (pArgInf[4].m_dtDataType != _SDT_NULL)
		*pArgInf[4].m_pBool = bHitImage;
}
static ARG_INFO s_ArgsHitTest[] =
{
	{ "横向位置","相对客户区",0,0,SDT_INT,0,NULL },
	{ "纵向位置","相对客户区",0,0,SDT_INT,0,NULL },
	{ "是否命中检查框","",0,0,SDT_BOOL,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
	{ "是否命中图片","",0,0,SDT_BOOL,0,AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY },
};
FucInfo Fn_ListBoxWHitTest = { {
		/*ccname*/  "命中测试",
		/*egname*/  "HitTest",
		/*explain*/ "返回命中的表项索引，未命中则返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsHitTest),
		/*arg lp*/  s_ArgsHitTest,
	} , ESTLFNAME(libstl_ListBoxW_HitTest) };

EXTERN_C void libstl_ListBoxW_GetItemStringLength(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_int = 0;
		return;
	}

	pRetData->m_int = p->m_ItemsInfo[idx].rsCaption.m_cchText;
}
static ARG_INFO s_ArgsGetItemStringLength[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWGetItemStringLength = { {
		/*ccname*/  "取表项文本长度",
		/*egname*/  "GetItemStringLength",
		/*explain*/ "失败或无文本返回0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetItemStringLength),
		/*arg lp*/  s_ArgsGetItemStringLength,
	} , ESTLFNAME(libstl_ListBoxW_GetItemStringLength) };

EXTERN_C void libstl_ListBoxW_Sort(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	if (pArgInf[1].m_int == 0)
		std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
			[](elibstl::LBITEMINFO& i1, elibstl::LBITEMINFO& i2) -> bool
	{
		return wcscmp(i1.rsCaption, i2.rsCaption) < 0;
	});
	else
		std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
			[](elibstl::LBITEMINFO& i1, elibstl::LBITEMINFO& i2) -> bool
	{
		return wcscmp(i1.rsCaption, i2.rsCaption) > 0;
	});
	p->Redraw();
}
static ARG_INFO s_ArgsSort[] =
{
	{ "排序方式","0 - 升序  1 - 降序",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWSort = { {
		/*ccname*/  "排序",
		/*egname*/  "Sort",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSort),
		/*arg lp*/  s_ArgsSort,
	} , ESTLFNAME(libstl_ListBoxW_Sort) };

typedef BOOL(__stdcall* LBSORTPROC)(LPARAM lParam1, LPARAM lParam2);
EXTERN_C void libstl_ListBoxW_Sort2(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	LBSORTPROC pProc;
	if (pArgInf[1].m_dtDataType == SDT_INT)
		pProc = (LBSORTPROC)pArgInf[1].m_int;
	else if (pArgInf[1].m_dtDataType == SDT_SUB_PTR)
		pProc = (LBSORTPROC)pArgInf[1].m_dwSubCodeAdr;
	else
	{
		pRetData->m_bool = FALSE;
		return;
	}

	std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
		[pProc = pProc](elibstl::LBITEMINFO& i1, elibstl::LBITEMINFO& i2) -> bool
	{
		return pProc(i1.Info.lParam, i2.Info.lParam);
	});
	p->Redraw();
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSort2[] =
{
	{ "排序子程序","返回值类型为逻辑型，有两个整数型参数，传入两表项的自定义数值，若第一个参数代表的表项数据大于第二个，则返回真，否则返回假",0,0,_SDT_ALL,0,NULL },
};
FucInfo Fn_ListBoxWSort2 = { {
		/*ccname*/  "自定义排序",
		/*egname*/  "Sort2",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSort2),
		/*arg lp*/  s_ArgsSort2,
	} , ESTLFNAME(libstl_ListBoxW_Sort2) };

EXTERN_C void libstl_ListBoxW_SwapItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx1 = pArgInf[1].m_int;
	int idx2 = pArgInf[2].m_int;
	int cItems = p->m_ItemsInfo.size();
	if (idx1 < 0 || idx1 > cItems || idx2 < 0 || idx2 > cItems || idx1 == idx2)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->LBSwapItem(idx1, idx2);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSwapItem[] =
{
	{ "索引1","",0,0,SDT_INT,0,NULL },
	{ "索引2","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWSwapItem = { {
		/*ccname*/  "交换表项",
		/*egname*/  "SwapItem",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSwapItem),
		/*arg lp*/  s_ArgsSwapItem,
	} , ESTLFNAME(libstl_ListBoxW_SwapItem) };

EXTERN_C void libstl_ListBoxW_MoveItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CListBox::m_CtrlSCInfo[hWnd];

	int idx1 = pArgInf[1].m_int;
	int idx2 = pArgInf[2].m_int;
	int cItems = p->m_ItemsInfo.size();
	if (idx1 < 0 || idx1 > cItems || idx2 < 0 || idx2 > cItems || idx1 == idx2)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->LBMoveItem(idx1, idx2);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsMoveItem[] =
{
	{ "索引1","",0,0,SDT_INT,0,NULL },
	{ "索引2","",0,0,SDT_INT,0,NULL },
};
FucInfo Fn_ListBoxWMoveItem = { {
		/*ccname*/  "移动表项",
		/*egname*/  "MoveItem",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsMoveItem),
		/*arg lp*/  s_ArgsMoveItem,
	} , ESTLFNAME(libstl_ListBoxW_MoveItem) };

static INT s_Cmd_ListBox[] = { 237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,
								259,260,261,262,263,264,265,266,267,268,269 };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtListBoxW = {
	"列表框W",//中文名称
	"ListBoxW",//英文名称
	"Unicode列表框、文件框、选择列表框三合一。注意：支持库创建一个无数据列表框，然后处理它的项目管理与绘制工作，外部绝对不能使用LB_ADDSTRING等消息。",//说明
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