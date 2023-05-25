#include "EcontrolHelp.h"
#include <Uxtheme.h>
#include <vsstyle.h>

#define SCID_LISTBOX		20230521'01u
#define SCID_LISTBOXPARENT	20230521'02u

ESTL_NAMESPACE_BEGIN

struct LBITEMCOMMINFO
{
	int idxImage;
	int cyItem;
	COLORREF crText;
	COLORREF crBK;
	COLORREF crSelText;
	COLORREF crSelBK;
	LPARAM lParam;
	BITBOOL bChecked : 1;
	BITBOOL bDisabled : 1;
};

#pragma warning (push)
#pragma warning (disable:26495)// “未初始化变量”
// 只用于运行时保存信息
struct LBITEMINFO
{
	CSimpleRefStrW rsCaption;
	CSimpleRefStrW rsTip;
	HBRUSH hbrBK;
	HBRUSH hbrSelBK;
	LBITEMCOMMINFO Info;
};
#pragma warning (pop)

// 只用于设计对话框
struct LBITEMINFO_DESIGN
{
	PWSTR pszTip;
	LBITEMCOMMINFO Info;
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
	LBITEMCOMMINFO Info;
};

struct EDLGCTX_LISTBOXITEMS :public EzDlg::EDLGCTX_BASE
{
	BYTE** ppItemsData;
	SIZE_T* pcbItems;
	BYTE* pInitData;
};

#define WCN_LISTBOXDESIGN L"eLibStl.WndClass.ListBoxItemsDesign"

static ATOM s_atomListBoxItemsDesign = 0;

#define IDC_LB_ITEMS		101
#define IDC_BT_OK			201
#define IDC_BT_CANCEL		202
#define IDC_BT_INSERTF		203
#define IDC_BT_INSERTB		204
#define IDC_BT_DEL			205
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
					EzDlg::DlgEndModel(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
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

					pItem = (LBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
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
				EzDlg::DlgEndModel(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
			}
			return 0;

			case IDC_BT_CANCEL:
			{
				p->bOK = FALSE;
				EzDlg::DlgEndModel(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
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
			WCHAR szText[32]{};
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
			xEdit, DlgPadding + StaticLineStep * 2, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_IMAGEIDX, NULL, NULL);
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
			int idx = SendMessageW(hLB, LB_ADDSTRING,0, (LPARAM)pData);
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
		EzDlg::DlgEndModel(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
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
		EzDlg::DlgModelOnDestroy(hWnd, p->hwndEMain, p->bEMainWndInitEnabled);
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

BOOL ShowListBoxDesignDlg(BYTE** ppItemsData, SIZE_T* pcbItems, BYTE* pInitData)
{
	auto pCtx = EzDlg::EIDEDlgPreShow<EDLGCTX_LISTBOXITEMS>(&s_atomListBoxItemsDesign, WCN_LISTBOXDESIGN, WndProc_ListBoxDesign);
	if (ppItemsData)
		*ppItemsData = NULL;
	if (pcbItems)
		*pcbItems = 0u;
	pCtx->pInitData = pInitData;
	pCtx->ppItemsData = ppItemsData;
	pCtx->pcbItems = pcbItems;

	EzDlg::EIDEDlgShow(WCN_LISTBOXDESIGN, L"列表框项目设置", 500,500, 600, 325, 
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
	BITBOOL bAutoSort : 1;		// 自动排序
	BITBOOL bMultiSel : 1;		// 鼠标多选
	BITBOOL bExtSel : 1;		// 按键多选
	BITBOOL bToolTip : 1;		// 工具提示
	BITBOOL bIntegralHeight: 1;	// 取整控件高度
	BITBOOL bDisableNoScroll: 1;// 显示禁止的滚动条
	BITBOOL bEllipsis: 1;		// 省略号
};

constexpr int c_LBPadding = 3;

class CListBox :public CCtrlBase
{
	SUBCLASS_MGR_DECL(CListBox)
private:
	ELISTBOXDATA m_Info{};
public:
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

	int HitTestCheckBox(POINT pt)
	{
		POINT ptScr = pt;
		ClientToScreen(m_hWnd, &ptScr);
		int idx = LBItemFromPt(m_hWnd, ptScr, FALSE);
		if (idx < 0)
			return -1;

		RECT rcItem;
		if (SendMessageW(m_hWnd, LB_GETITEMRECT, idx, (LPARAM)&rcItem) == LB_ERR)
			return -1;

		rcItem.right = rcItem.left + m_cxCheckBox;
		if (PtInRect(&rcItem, pt))
			return idx;
		else
			return -1;
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
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
			if (IsBitExist(pdis->itemState, ODS_SELECTED))
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

				if (Item.Info.crText != CLR_DEFAULT)
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
						iStateID = RBS_CHECKEDNORMAL;
					else
						iStateID = RBS_UNCHECKEDNORMAL;
				}
				else
				{
					iPartID = BP_CHECKBOX;
					if (Item.Info.bChecked)
						iStateID = CBS_CHECKEDNORMAL;
					else
						iStateID = CBS_UNCHECKEDNORMAL;
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
			RECT rcItem;
			int idx = p->HitTestCheckBox(pt);
			if (idx < 0)
				break;
			if (p->m_Info.iCheckBoxMode == 1)
			{
				if (p->m_idxChecked != idx)
				{
					if (p->m_idxChecked >= 0)
					{
						DefSubclassProc(hWnd, LB_GETITEMRECT, p->m_idxChecked, (LPARAM)&rcItem);
						InvalidateRect(hWnd, &rcItem, FALSE);
					}
					p->m_idxChecked = idx;
				}
			}
			else
			{
				BOOLNOT(p->m_ItemsInfo[idx].Info.bChecked);
				DefSubclassProc(hWnd, LB_GETITEMRECT, idx, (LPARAM)&rcItem);
				InvalidateRect(hWnd, &rcItem, FALSE);
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

		case WM_THEMECHANGED:
			p->UpdateThemeInfo();
			break;

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;

		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			break;
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

		DWORD dwLBStyle = LBS_OWNERDRAWFIXED | LBS_NODATA;
		if (m_Info.bMultiSel)
			dwLBStyle |= LBS_MULTIPLESEL;
		if (m_Info.bExtSel)
			dwLBStyle |= LBS_EXTENDEDSEL;
		if (!m_Info.bIntegralHeight)
			dwLBStyle |= LBS_NOINTEGRALHEIGHT;
		if (m_Info.bDisableNoScroll)
			dwLBStyle |= LBS_DISABLENOSCROLL;

		m_hWnd = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_VSCROLL | WS_CHILD | WS_CLIPSIBLINGS | dwLBStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;
		UpdateThemeInfo();

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
		if (m_Info.cyItem)// 必须在InitBase0后面
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
		if (iPos < 0)
			m_ItemsInfo.push_back(std::move(Item));
		else
			m_ItemsInfo.insert(m_ItemsInfo.begin() + idx, std::move(Item));
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
		m_ItemsInfo.push_back(std::move(Item));
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

	void LBSetCount(int cItems)
	{
		SendMessageW(m_hWnd, LB_SETCOUNT, cItems, 0);
		m_ItemsInfo.resize(cItems);
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
			auto Item = m_ItemsInfo[iPos];
			DeleteObject(Item.hbrBK);
			DeleteObject(Item.hbrSelBK);
			m_ItemsInfo.erase(m_ItemsInfo.begin() + iPos);
		}
		Redraw();
		return TRUE;
	}

	void LBInitStorage(int cItems)
	{
		m_ItemsInfo.reserve(cItems);
		SendMessageW(m_hWnd, LB_INITSTORAGE, cItems, 0);
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
		LBSetCount(cItems);
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (LBITEMHEADER_MEM*)pData;
			pData += sizeof(LBITEMHEADER_MEM);

			pszCaption = (PCWSTR)pData;
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));
			pszTip = (PCWSTR)pData;
			pData += (pItemHeader->cchTip * sizeof(WCHAR));

			LBSetItem(i, pszCaption, pszTip, pItemHeader->Info);
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
			return SendMessageW(m_hWnd, LB_GETCURSEL, 0, 0);
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
		BYTE* pData, *pcr;
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

	eStlInline HGLOBAL FlattenInfo() override
	{
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
			BOOL bOK = ShowListBoxDesignDlg(&pItems, &cb, p->GetItems());
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
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 400;
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
	pRetData->m_int - SendMessageW(hWnd, LB_GETCOUNT, 0, 0);
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
	pRetData->m_int == SendMessageW(hWnd, LB_GETTOPINDEX, 0, 0);
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
		/*ccname*/  "加入表项",
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
	if (idx < 0 || idx > p->m_ItemsInfo.size())
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
	if (idx < 0 || idx > p->m_ItemsInfo.size())
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
	if (idx < 0 || idx > p->m_ItemsInfo.size())
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
	if (idx < 0 || idx > p->m_ItemsInfo.size())
	{
		pRetData->m_pBin = NULL;
		return;
	}

	auto& rsCaption = p->m_ItemsInfo[idx].rsCaption;
	rsCaption = elibstl::args_to_pszw(pArgInf, 2);
	p->Redraw();
}
static ARG_INFO s_ArgsSetItemString[] =
{
	{ "索引","",0,0,SDT_INT,0,NULL },
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemString = { {
		/*ccname*/  "置表项文本",
		/*egname*/  "SetItemString",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

	pRetData->m_int = SendMessageW(hWnd, LB_GETSELCOUNT, 0, 0);
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

	int cSeledItems = SendMessageW(hWnd, LB_GETSELCOUNT, 0, 0);
	if (cSeledItems <= 0)
	{
		pRetData->m_pAryData = NULL;
		return;
	}

	pRetData->m_pAryData = elibstl::malloc_array<int>(cSeledItems);
	SendMessageW(hWnd, LB_GETSELITEMS, cSeledItems, (LPARAM)((BYTE*)pRetData->m_pAryData + 8));
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

}
static ARG_INFO s_ArgsIsItemSelected[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWIsItemSelected = { {
		/*ccname*/  "表项是否选中 ",
		/*egname*/  "IsItemSelected",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsGetItemCheckState[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWGetItemCheckState = { {
		/*ccname*/  "取表项检查状态",
		/*egname*/  "GetItemCheckState",
		/*explain*/ "",
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

}
static ARG_INFO s_ArgsSetItemCheckState[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemCheckState = { {
		/*ccname*/  "置表项检查状态",
		/*egname*/  "SetItemCheckState",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsSelectItem[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSelectItem = { {
		/*ccname*/  "选中表项",
		/*egname*/  "SelectItem",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsFindString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWFindString = { {
		/*ccname*/  "寻找表项",
		/*egname*/  "FindString",
		/*explain*/ "",
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

}
static ARG_INFO s_ArgsGetItemColor[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
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

}
static ARG_INFO s_ArgsSetItemColor[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemColor = { {
		/*ccname*/  "置表项颜色",
		/*egname*/  "SetItemColor",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsGetItemTip[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWGetItemTip = { {
		/*ccname*/  "取表项提示文本",
		/*egname*/  "GetItemTip",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsSetItemTip[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemTip = { {
		/*ccname*/  "置表项提示文本",
		/*egname*/  "SetItemTip",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsGetItemImageIndex[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWGetItemImageIndex = { {
		/*ccname*/  "取表项图片索引",
		/*egname*/  "GetItemImageIndex",
		/*explain*/ "",
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

}
static ARG_INFO s_ArgsSetItemImageIndex[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWSetItemImageIndex = { {
		/*ccname*/  "置表项图片索引",
		/*egname*/  "SetItemImageIndex",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsInitStorage[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWInitStorage = { {
		/*ccname*/  "保留内存",
		/*egname*/  "InitStorage",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsInitStorage),
		/*arg lp*/  s_ArgsInitStorage,
	} , ESTLFNAME(libstl_ListBoxW_InitStorage) };

EXTERN_C void libstl_ListBoxW_InsertMultiString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

}
static ARG_INFO s_ArgsInsertMultiString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWInsertMultiString = { {
		/*ccname*/  "插入多个项目",
		/*egname*/  "InsertMultiString",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsInsertMultiString),
		/*arg lp*/  s_ArgsInsertMultiString,
	} , ESTLFNAME(libstl_ListBoxW_InsertMultiString) };

EXTERN_C void libstl_ListBoxW_AddMultiString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

}
static ARG_INFO s_ArgsAddMultiString[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWAddMultiString = { {
		/*ccname*/  "加入多个项目",
		/*egname*/  "AddMultiString",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsAddMultiString),
		/*arg lp*/  s_ArgsAddMultiString,
	} , ESTLFNAME(libstl_ListBoxW_AddMultiString) };

EXTERN_C void libstl_ListBoxW_GetItemRect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);

}
static ARG_INFO s_ArgsGetItemRect[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWGetItemRect = { {
		/*ccname*/  "取项目矩形",
		/*egname*/  "GetItemRect",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
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

}
static ARG_INFO s_ArgsHitTest[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWHitTest = { {
		/*ccname*/  "命中测试",
		/*egname*/  "HitTest",
		/*explain*/ "",
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

}
static ARG_INFO s_ArgsGetItemStringLength[] =
{
	{ "文本","",0,0,SDT_BIN,0,NULL }
};
FucInfo Fn_ListBoxWGetItemStringLength = { {
		/*ccname*/  "取项目文本长度",
		/*egname*/  "GetItemStringLength",
		/*explain*/ "",
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






static INT s_Cmd_ListBox[] = { 237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,
								259,260,261,262,263,264,265};
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtListBoxW = {
	"列表框W",//中文名称
	"ListBoxW",//英文名称
	"Unicode列表框、文件框、选择列表框三合一。注意：支持库创建一个无数据列表框，然后处理它的项目管理与绘制工作，因此不能使用LB_ADDSTRING等消息。",//说明
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