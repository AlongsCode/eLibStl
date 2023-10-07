#include "EcontrolHelp.h"

#include <algorithm>

#pragma warning(disable:4996)

#define SCID_COMBOBOX			20230930'01u
#define SCID_COMBOBOXPARENT		20230930'02u

#define ED_CUEBANNER_MAXLEN		260

ESTL_NAMESPACE_BEGIN
// 编辑框
/*
* 版本1数据布局：
* ECOMBOBOXDATA结构
* 提示文本
*/
#define DATA_VER_COMBOBOX_1	1
struct ECOMBOBOXDATA
{
	int iVer;				// 版本号

	int idxCurrSel;			// 现行选中
	int cyItem;				// 行高
	COLORREF crText;		// 文本颜色
	COLORREF crBK;			// 背景颜色
	COLORREF crSelText;		// 选中文本颜色
	COLORREF crSelBK;		// 选择背景颜色
	int iAlignH;			// 横向对齐
	int iAlignV;			// 纵向对齐
	SIZE_T cbItems;			// 表项数据长度，全程维护此值
	SIZE_T cbImageList;		// 图片组长度，仅在保存信息时有效
	int iMaxLen;			// 最大允许长度
	int iSelPos;			// 起始选择位置
	int iSelNum;			// 被选择字符数
	int cchCueBanner;		// 提示文本长度，仅保存信息时有效
	int cyComboBox;			// 组合框高度
	BYTE iType;				// 0 - 简单组合框   1 - 可编辑下拉组合框   2 - 不可编辑下拉组合框
	BITBOOL bAutoSort : 1;			// 自动排序
	BITBOOL bIntegralHeight : 1;	// 取整控件高度
	BITBOOL bDisableNoScroll : 1;	// 显示禁止的滚动条
	BITBOOL bEllipsis : 1;			// 省略号
};

struct CBITEMCOMMINFO
{
	int idxImage;			// 图像索引
	COLORREF crText;		// 文本颜色
	COLORREF crBK;			// 背景颜色
	COLORREF crSelText;		// 选中文本颜色
	COLORREF crSelBK;		// 选中背景颜色
	LPARAM lParam;			// 表项数值
};

/*
* 版本1数据布局：
* CBITEMSDATAHEADER_MEM结构
* {
*	CBITEMHEADER_MEM结构
*	标题
* }
*/
#define DATA_VER_CBITEMS_1 1
// 只用于运行时保存信息
struct CBITEMINFO
{
	CSimpleRefStrW rsCaption;	// 标题
	HBRUSH hbrBK;				// 背景画刷
	HBRUSH hbrSelBK;			// 选中背景画刷
	CBITEMCOMMINFO Info;		// 通用信息
};

// 只用于设计对话框
struct CBITEMINFO_DESIGN
{
	PWSTR pszTip;			// 提示文本
	CBITEMCOMMINFO Info;	// 通用信息
};

struct CBITEMSDATAHEADER_MEM
{
	int iVer;				// 版本号

	int cItems;				// 项目数
};
// 项目属性头，标题紧随其后（附带结尾NULL，便于初始化时插入项目），只用于保存数据
struct CBITEMHEADER_MEM
{
	int cchCaption;			// 标题字符数，包含结尾NULL
	CBITEMCOMMINFO Info;	// 通用信息
};


struct EDLGCTX_COMBOBOXITEMS :public EzDlg::EDLGCTX_BASE
{
	BYTE** ppItemsData;		// 返回数据
	SIZE_T* pcbItems;		// 返回数据长度
	BYTE* pInitData;		// 初始数据
	HIMAGELIST hImageList;	// 图像列表
};

#define WCN_LISTBOXDESIGN L"eLibStl.WndClass.ComboBoxItemsDesign"

static ATOM s_atomListBoxItemsDesign = 0;

#define IDC_LB_ITEMS		101
#define IDC_BT_OK			201
#define IDC_BT_CANCEL		202
#define IDC_BT_INSERTF		203
#define IDC_BT_INSERTB		204
#define IDC_BT_DEL			205
#define IDC_BT_SELIMAGE		206
#define IDC_ED_CAPTION		301
#define IDC_ED_IMAGEIDX		303
#define IDC_ED_ITEMDATA		304
#define IDC_CLP_TEXT		501
#define IDC_CLP_BK			502
#define IDC_CLP_SELTEXT		503
#define IDC_CLP_SELBK		504

#define CWM_CLRPICKERNOTIFY	WM_USER + 2

static LRESULT CALLBACK WndProc_ComboBoxBoxDesign(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto p = (EDLGCTX_COMBOBOXITEMS*)GetWindowLongPtrW(hWnd, 0);
	switch (uMsg)
	{
	case CWM_CLRPICKERNOTIFY:
	{
		HWND hLB = GetDlgItem(hWnd, IDC_LB_ITEMS);
		int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
		if (iCurrSel == LB_ERR)
			return 0;
		auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
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
				auto pItem = new CBITEMINFO_DESIGN;
				ZeroMemory(pItem, sizeof(CBITEMINFO_DESIGN));
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
					auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
					delete[] pItem->pszTip;
					delete pItem;
					SendMessageW(hLB, LB_DELETESTRING, iCurrSel, 0);
				}
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
				CBITEMINFO_DESIGN* pItem;
				for (int i = 0; i < cItems; ++i)
				{
					iTemp = SendMessageW(hLB, LB_GETTEXTLEN, i, 0) + 1;
					pcchCaption[i] = iTemp;
					cchTotal += iTemp;

					pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);
					if (pItem->pszTip)
						iTemp = wcslen(pItem->pszTip) + 1;
					else
						iTemp = 1;
					pcchTip[i] = iTemp;
					cchTotal += iTemp;
				}

				SIZE_T cbTotal =
					sizeof(CBITEMSDATAHEADER_MEM) +
					sizeof(CBITEMHEADER_MEM) * cItems +
					cchTotal * sizeof(WCHAR);
				BYTE* pData = new BYTE[cbTotal];
				*p->pcbItems = cbTotal;
				*p->ppItemsData = pData;
				auto pHeader = (CBITEMSDATAHEADER_MEM*)pData;
				pHeader->iVer = DATA_VER_CBITEMS_1;
				pHeader->cItems = cItems;

				pData += sizeof(CBITEMSDATAHEADER_MEM);
				CBITEMHEADER_MEM* pItemHeader;
				for (int i = 0; i < cItems; ++i)
				{
					pItemHeader = (CBITEMHEADER_MEM*)pData;
					pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);

					pItemHeader->cchCaption = pcchCaption[i];
					pItemHeader->Info = pItem->Info;

					pData += sizeof(CBITEMHEADER_MEM);

					SendMessageW(hLB, LB_GETTEXT, i, (LPARAM)pData);
					pData += (pcchCaption[i] * sizeof(WCHAR));
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
				auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
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

			case IDC_ED_IMAGEIDX:
			{
				auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
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
				auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
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
			auto pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, iCurrSel, 0);
			// 图像索引
			WCHAR szText[48]{};
			swprintf(szText, L"%d", pItem->Info.idxImage);
			SetDlgItemTextW(hWnd, IDC_ED_IMAGEIDX, szText);
			// 表项数值
			swprintf(szText, L"%d", pItem->Info.lParam);
			SetDlgItemTextW(hWnd, IDC_ED_ITEMDATA, szText);
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
		constexpr int xClrPicker = 495;
		constexpr int cxClrPicker = 90;
		constexpr int cyClrPicker = 300;

		p = (EDLGCTX_COMBOBOXITEMS*)((CREATESTRUCTW*)lParam)->lpCreateParams;
		SetWindowLongPtrW(hWnd, 0, (LONG_PTR)p);
		p->hFont = EzFont(L"微软雅黑", 10);

		HWND hCtrl;
		HWND hLB = CreateWindowExW(0, WC_LISTBOXW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | WS_VSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
			DlgPadding, DlgPadding, cxLB, cyLB, hWnd, (HMENU)IDC_LB_ITEMS, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"标题：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"图像索引：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 1, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"项目数值：", WS_CHILD | WS_VISIBLE,
			xStatic, DlgPadding + StaticLineStep * 2, cxStatic, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"文本颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 1, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"背景颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 2, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"选中文本颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 3, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(0, WC_STATICW, L"选中背景颜色：", WS_CHILD | WS_VISIBLE,
			xStatic2, DlgPadding + StaticLineStep * 4, cxStatic2, cyStatic, hWnd, NULL, NULL, NULL);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding, cxEdit1, cyStatic, hWnd, (HMENU)IDC_ED_CAPTION, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding + StaticLineStep * 1, cxEdit2 - cxBTSelImage, cyStatic, hWnd, (HMENU)IDC_ED_IMAGEIDX, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_MULTILINE,
			xEdit, DlgPadding + StaticLineStep * 2, cxEdit2, cyStatic, hWnd, (HMENU)IDC_ED_ITEMDATA, NULL, NULL);
		EzDlg::TabRepairInstall(hCtrl);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 1, cxClrPicker, cyClrPicker,
			WS_TABSTOP | WS_GROUP, 0, IDC_CLP_TEXT, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 2, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_BK, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 3, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_SELTEXT, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = ClrPicker::Create(xClrPicker, DlgPadding + StaticLineStep * 4, cxClrPicker, cyClrPicker,
			WS_TABSTOP, 0, IDC_CLP_SELBK, hWnd, CWM_CLRPICKERNOTIFY);

		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"O", WS_CHILD | WS_TABSTOP | WS_GROUP | WS_VISIBLE,
			xEdit + cxEdit2 - cxBTSelImage, DlgPadding + StaticLineStep * 1, cxBTSelImage, cyStatic, hWnd, (HMENU)IDC_BT_SELIMAGE, NULL, NULL);

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

		auto pHeader = (CBITEMSDATAHEADER_MEM*)pData;

		int cItems = pHeader->cItems;
		if (cItems <= 0)
			return 0;

		SendMessageW(hLB, WM_SETREDRAW, FALSE, 0);
		SendMessageW(hLB, LB_INITSTORAGE, cItems, 48);

		int cchTotal = 0;
		CBITEMINFO_DESIGN* pItem;
		pData += sizeof(CBITEMSDATAHEADER_MEM);
		CBITEMHEADER_MEM* pItemHeader;
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (CBITEMHEADER_MEM*)pData;
			pData += sizeof(CBITEMHEADER_MEM);
			// 项目头
			pItem = new CBITEMINFO_DESIGN;
			ZeroMemory(pItem, sizeof(CBITEMINFO_DESIGN));
			pItem->Info = pItemHeader->Info;
			// 文本
			int idx = SendMessageW(hLB, LB_ADDSTRING, 0, (LPARAM)pData);
			SendMessageW(hLB, LB_SETITEMDATA, idx, (LPARAM)pItem);
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));
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
		CBITEMINFO_DESIGN* pItem;
		for (int i = SendMessageW(hLB, LB_GETCOUNT, 0, 0) - 1; i >= 0; --i)
		{
			pItem = (CBITEMINFO_DESIGN*)SendMessageW(hLB, LB_GETITEMDATA, i, 0);
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

BOOL ShowComboBoxDesignDlg(BYTE** ppItemsData, SIZE_T* pcbItems, BYTE* pInitData, HIMAGELIST hImageList)
{
	auto pCtx = EzDlg::EIDEDlgPreShow<EDLGCTX_COMBOBOXITEMS>(&s_atomListBoxItemsDesign, WCN_LISTBOXDESIGN, WndProc_ComboBoxBoxDesign);
	if (ppItemsData)
		*ppItemsData = NULL;
	if (pcbItems)
		*pcbItems = 0u;
	pCtx->pInitData = pInitData;
	pCtx->ppItemsData = ppItemsData;
	pCtx->pcbItems = pcbItems;
	pCtx->hImageList = hImageList;

	EzDlg::EIDEDlgShow(WCN_LISTBOXDESIGN, L"组合框项目设置", CW_USEDEFAULT, 0, 600, 325,
		WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_POPUP, pCtx);

	BOOL bOK = pCtx->bOK;
	delete pCtx;
	return bOK;
}



constexpr int c_CBPadding = 3;

#define CB_CUEBANNER_MAXLEN 260

class CComboBox :public elibstl::CCtrlBase
{
	SUBCLASS_MGR_DECL(CComboBox)
public:
	ECOMBOBOXDATA m_Info{};
	//////////图像列表相关
	BOOL m_bImageListNeedDel = FALSE;		// 图像列表句柄是否需要被释放
	HIMAGELIST m_hImageList = NULL;			// 图像列表句柄
	std::vector<BYTE> m_ILData{};			// 图片组数据
	int m_cxImage = 0, m_cyImage = 0;		// 图像列表尺寸
	//////////通用信息
	HBRUSH m_hbrBK = NULL;					// 通用表项背景画刷
	HBRUSH m_hbrSelBK = NULL;				// 通用选择表项背景画刷
	BYTE* m_pItems = NULL;					// 项目数据
	std::vector<CBITEMINFO> m_ItemsInfo{};	// 所有项目
	//////////
	PWSTR m_pszSelText = NULL;
	PWSTR m_pszCueBanner = new WCHAR[CB_CUEBANNER_MAXLEN];
private:
	HWND GetEditControl()
	{
		COMBOBOXINFO cbi;
		cbi.cbSize = sizeof(COMBOBOXINFO);
		SendMessageW(m_hWnd, CB_GETCOMBOBOXINFO, 0, (LPARAM)&cbi);
		return cbi.hwndItem;
	}

	eStlInline void OnSelChange()
	{
		if(m_Info.iType!=2)
		{
			int idxCurr = GetCurrSel();
			if (idxCurr >= 0)
				SetTextW(m_ItemsInfo[idxCurr].rsCaption);
		}
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline void OnEditChange()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 1);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline void OnDropDown()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 2);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline void OnCloseUp()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 3);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	eStlInline void OnDBLClk()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 4);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		//case WM_MEASUREITEM:
		//{
		//	HWND hCtrl = GetDlgItem(hWnd, wParam);
		//	auto it = m_CtrlSCInfo.find(hCtrl);
		//	if (it == m_CtrlSCInfo.end())
		//		break;
		//	auto pmis = (MEASUREITEMSTRUCT*)lParam;
		//	auto p = it->second;
		//	if (pmis->itemID == -1)
		//	{
		//		if (p->m_Info.cyComboBox >= 0)
		//			pmis->itemHeight = p->m_Info.cyComboBox;
		//	}
		//	else
		//	{
		//		if (p->m_Info.cyItem >= 0)
		//			pmis->itemHeight = p->m_Info.cyItem;
		//	}

		//	return TRUE;
		//}
		//break;

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
			
			// 画图片
			RECT rc = pdis->rcItem;
			if (p->m_cxImage)
			{
				if (p->m_hImageList && Item.Info.idxImage >= 0)
				{
					rc.left += c_CBPadding;
					ImageList_Draw(p->m_hImageList, Item.Info.idxImage, hDC,
						rc.left,
						rc.top + ((rc.bottom - rc.top) - p->m_cyImage) / 2,
						ILD_NORMAL | (IsBitExist(pdis->itemState, ODS_SELECTED) ? ILD_SELECTED : 0));
				}
				rc.left += (p->m_cxImage + c_CBPadding);
			}
			else
				rc.left += c_CBPadding;
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

		case WM_COMMAND:
		{
			if (!m_CtrlSCInfo.count((HWND)lParam))
				break;
			auto p = m_CtrlSCInfo[(HWND)lParam];
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				p->OnSelChange();
				return 0;// 不使用返回值
			case CBN_EDITCHANGE:
				p->OnEditChange();
				return 0;// 不使用返回值
			case CBN_DROPDOWN:
				p->OnDropDown();
				return 0;// 不使用返回值
			case CBN_CLOSEUP:
				p->OnCloseUp();
				return 0;// 不使用返回值
			case CBN_DBLCLK:
				p->OnDBLClk();
				return 0;// 不使用返回值
			}
		}
		break;

		case WM_CTLCOLORSTATIC:
		{
			HWND hCB = WindowFromDC((HDC)wParam);
			auto it = m_CtrlSCInfo.find(hCB);
			if (it != m_CtrlSCInfo.end())
			{
				auto p = it->second;
				SetTextColor((HDC)wParam, p->m_Info.crText);
				return (LRESULT)p->m_hbrBK;
			}
		}
		break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CComboBox*)dwRefData;
		switch (uMsg)
		{
		case CB_SETCURSEL:
		{
			if (p->m_Info.iType != 2)
			{
				if (wParam >= 0 && wParam < p->m_ItemsInfo.size())
					p->SetTextW(p->m_ItemsInfo[wParam].rsCaption);
				else
					p->SetTextW(NULL);
			}
		}
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
	CComboBox() = delete;
	CComboBox(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);
		*m_pszCueBanner = L'\0';
		BYTE* pILData = NULL;
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			// 结构
			memcpy(&m_Info, p, sizeof(ECOMBOBOXDATA));
			p += sizeof(ECOMBOBOXDATA);
			// 项目
			DupStreamForNewDelete(m_pItems, p, m_Info.cbItems);
			p += m_Info.cbItems;
			// 图像列表
			pILData = p;
			p += m_Info.cbImageList;
			// 提示文本
			if (m_Info.cchCueBanner)
			{
				memcpy(m_pszCueBanner, p, m_Info.cchCueBanner * sizeof(WCHAR));
				*(m_pszCueBanner + m_Info.cchCueBanner) = L'\0';
			}
		}
		else
		{
			m_Info.iType = 1;
			m_Info.crBK = CLR_DEFAULT;
			m_Info.crSelBK = CLR_DEFAULT;
			m_Info.crSelBK = CLR_DEFAULT;
			m_Info.crSelText = CLR_DEFAULT;
			m_Info.cyItem = -1;
			m_Info.idxCurrSel = -1;
			m_Info.iAlignV = 1;
			m_Info.cyComboBox = -1;
		}

		m_Info.iVer = DATA_VER_COMBOBOX_1;
		DWORD dwCBStyle = CBS_OWNERDRAWFIXED | WS_VSCROLL | CBS_AUTOHSCROLL;
		switch (m_Info.iType)
		{
		case 0:dwCBStyle |= CBS_SIMPLE; break;
		case 1:dwCBStyle |= CBS_DROPDOWN; break;
		case 2:dwCBStyle |= CBS_DROPDOWNLIST; break;
		}
		if (!m_Info.bIntegralHeight)
			dwCBStyle |= CBS_NOINTEGRALHEIGHT;
		if (m_Info.bDisableNoScroll)
			dwCBStyle |= CBS_DISABLENOSCROLL;

		if (cy < 400 && m_Info.iType != 0)
			cy = 400;

		m_hWnd = CreateWindowExW(0, WC_COMBOBOXW, NULL, WS_CHILD | WS_CLIPSIBLINGS | dwStyle | dwCBStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;
		if (!pAllData)
		{
			RECT rc;
			GetClientRect(m_hWnd, &rc);
			m_Info.cyComboBox = rc.bottom;
		}

		SetRedraw(FALSE);
		// 设置图像列表
		if (pILData)
			SetImageList(pILData, m_Info.cbImageList);
		// 插入表项
		SetItems(m_pItems, m_Info.cbItems, TRUE);
		// 
		SetClr(1, m_Info.crBK);
		SetSelClr(1, m_Info.crSelBK);
		SetCurrSel(m_Info.idxCurrSel);
		if (m_Info.cchCueBanner && m_Info.iType != 2)
			SetCueBannerNoCopy(m_pszCueBanner);

		InitBase0(pAllData);
		if (m_Info.cyItem)// 必须在InitBase0之后
			SetItemHeight(m_Info.cyItem);
		SetRedraw(TRUE);

		SetComboBoxHeight(m_Info.cyComboBox);
		SendMessageW(m_hWnd, CB_SETMINVISIBLE, 30, 0);
	}

	~CComboBox()
	{
		delete[] m_pszCueBanner;
		delete[] m_pszSelText;
		delete[] m_pItems;
		for (auto& x : m_ItemsInfo)
		{
			DeleteObject(x.hbrBK);
			DeleteObject(x.hbrSelBK);
		}

		DeleteObject(m_hbrBK);
		DeleteObject(m_hbrSelBK);

		if (m_bImageListNeedDel)
			ImageList_Destroy(m_hImageList);
	}

	int CBInsertString(PCWSTR pszString, const CBITEMCOMMINFO& CommInfo, int iPos = -1)
	{
		int idx = SendMessageW(m_hWnd, CB_INSERTSTRING, iPos, (LPARAM)L"");
		if (idx == LB_ERR)
			return -1;
		CBITEMINFO Item{ pszString,NULL,NULL,CommInfo };
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

	void CBSetItem(int idx, PCWSTR pszString, const CBITEMCOMMINFO& CommInfo)
	{
		CBITEMINFO& Item = m_ItemsInfo[idx];
		Item = { pszString,NULL,NULL,CommInfo };
		if (CommInfo.crBK != CLR_DEFAULT)
			Item.hbrBK = CreateSolidBrush(CommInfo.crBK);
		if (CommInfo.crSelBK != CLR_DEFAULT)
			Item.hbrSelBK = CreateSolidBrush(CommInfo.crSelBK);
	}

	BOOL CBDeleteString(int iPos)
	{
		if (iPos < 0)
		{
			SendMessageW(m_hWnd, CB_RESETCONTENT, 0, 0);
			for (auto& x : m_ItemsInfo)
			{
				DeleteObject(x.hbrBK);
				DeleteObject(x.hbrSelBK);
			}
			m_ItemsInfo.clear();
			Redraw();
			return TRUE;
		}
		else if (iPos >= 0 && iPos < (int)m_ItemsInfo.size())
		{
			if (SendMessageW(m_hWnd, CB_DELETESTRING, iPos, 0) == CB_ERR)
				return FALSE;
			auto& Item = m_ItemsInfo[iPos];
			DeleteObject(Item.hbrBK);
			DeleteObject(Item.hbrSelBK);
			m_ItemsInfo.erase(m_ItemsInfo.begin() + iPos);
			Redraw();
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL CBInitStorage(int cItems)
	{
		if (SendMessageW(m_hWnd, CB_INITSTORAGE, cItems, 0) == CB_ERRSPACE)
			return FALSE;
		m_ItemsInfo.reserve(cItems);
		return TRUE;
	}

	eStlInline void CBSwapItem(int idx1, int idx2)
	{
		std::swap(m_ItemsInfo[idx1], m_ItemsInfo[idx2]);
		Redraw();
	}

	void CBMoveItem(int idxSrc, int idxDst)
	{
		CBITEMINFO Info = std::move(m_ItemsInfo[idxSrc]);
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

	void SetImageList(BYTE* pData, SIZE_T cb)
	{
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

	void SetItems(BYTE* pItems, SIZE_T cbItems, BOOL bNoCopy)
	{
		SetRedraw(FALSE);
		CBDeleteString(-1);
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
		CBITEMSDATAHEADER_MEM* pHeader;
		CBITEMHEADER_MEM* pItemHeader;
		PCWSTR pszCaption;
		if (bNoCopy)
		{
			if (m_pItems != pItems)
				delete[] m_pItems;
			m_pItems = pItems;
			m_Info.cbItems = cbItems;
		}
		else if (m_bInDesignMode)
			m_Info.cbItems = DupStreamForNewDelete(m_pItems, pItems, cbItems);

		pHeader = (CBITEMSDATAHEADER_MEM*)pData;
		pData += sizeof(CBITEMSDATAHEADER_MEM);
		int cItems = pHeader->cItems;
		CBInitStorage(cItems);
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (CBITEMHEADER_MEM*)pData;
			pData += sizeof(CBITEMHEADER_MEM);

			pszCaption = (PCWSTR)pData;
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));

			CBInsertString(pszCaption, pItemHeader->Info);
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
		}

		SIZE_T cbTotal =
			sizeof(CBITEMSDATAHEADER_MEM) +
			sizeof(CBITEMHEADER_MEM) * cItems +
			cchTotal * sizeof(WCHAR);
		m_Info.cbItems = cbTotal;
		BYTE* pData = new BYTE[cbTotal];
		m_pItems = pData;

		auto pHeader = (CBITEMSDATAHEADER_MEM*)pData;
		pHeader->iVer = DATA_VER_CBITEMS_1;
		pHeader->cItems = cItems;

		pData += sizeof(CBITEMSDATAHEADER_MEM);
		CBITEMHEADER_MEM* pItemHeader;
		for (int i = 0; i < cItems; ++i)
		{
			pItemHeader = (CBITEMHEADER_MEM*)pData;

			pItemHeader->cchCaption = m_ItemsInfo[i].rsCaption.m_cchText;
			pItemHeader->Info = m_ItemsInfo[i].Info;

			pData += sizeof(CBITEMHEADER_MEM);

			m_ItemsInfo[i].rsCaption.CopyTo((PWSTR)pData);
			pData += (pItemHeader->cchCaption * sizeof(WCHAR));
		}

		return m_pItems;
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

	eStlInline void SetType(int i)
	{
		m_Info.iType = i;
	}

	eStlInline int GetType()
	{
		return m_Info.iType;
	}

	eStlInline void SetCurrSel(int idx)
	{
		m_Info.idxCurrSel = idx;
		SendMessageW(m_hWnd, CB_SETCURSEL, idx, 0);
	}

	eStlInline int GetCurrSel()
	{
		if (m_bInDesignMode)
			return m_Info.idxCurrSel;
		else
			return (int)SendMessageW(m_hWnd, CB_GETCURSEL, 0, 0);
	}

	eStlInline void SetItemHeight(int cy)
	{
		m_Info.cyItem = cy;
		SendMessageW(m_hWnd, CB_SETITEMHEIGHT, 0, cy);
	}

	eStlInline int GetItemHeight()
	{
		if (m_bInDesignMode)
			return m_Info.cyItem;
		else
			return SendMessageW(m_hWnd, CB_GETITEMHEIGHT, 0, 0);
	}

	eStlInline void SetAutoSort(BOOL bAutoSort)
	{
		if (bAutoSort && !m_Info.bAutoSort && m_ItemsInfo.size())
		{
			std::sort(m_ItemsInfo.begin(), m_ItemsInfo.end(),
				[](CBITEMINFO& i1, CBITEMINFO& i2) -> bool
				{
					return wcscmp(i1.rsCaption, i2.rsCaption) < 0;
				});
			Redraw();
		}
		m_Info.bAutoSort = bAutoSort;
	}

	eStlInline BOOL GetAutoSort()
	{
		return m_Info.bAutoSort;
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

	eStlInline void SetEllipsis(BOOL bEllipsis)
	{
		m_Info.bEllipsis = bEllipsis;
		Redraw();
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

	eStlInline void SetIntegralHeight(BOOL bIntegralHeight)
	{
		m_Info.bIntegralHeight = bIntegralHeight;
	}

	eStlInline BOOL GetIntegralHeight()
	{
		if (m_bInDesignMode)
			return m_Info.bIntegralHeight;
		else
			return !IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), CBS_NOINTEGRALHEIGHT);
	}

	void SetSelPos(int iSelPos)
	{
		m_Info.iSelPos = iSelPos;
		DWORD dwStart, dwEnd;
		SendMessageW(m_hWnd, CB_GETEDITSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		DWORD dwLen;
		if (dwStart > dwEnd)
			dwLen = dwStart - dwEnd;
		else
			dwLen = dwEnd - dwStart;
		SendMessageW(m_hWnd, CB_SETEDITSEL, iSelPos, iSelPos + dwLen);
	}

	eStlInline int GetSelPos()
	{
		if (m_bInDesignMode)
			return m_Info.iSelPos;
		else
		{
			DWORD dwStart;
			SendMessageW(m_hWnd, CB_GETEDITSEL, (WPARAM)&dwStart, NULL);
			return dwStart;
		}
	}

	eStlInline void SetSelNum(int iSelNum)
	{
		m_Info.iSelNum = iSelNum;
		DWORD dwStart;
		SendMessageW(m_hWnd, CB_GETEDITSEL, (WPARAM)&dwStart, NULL);
		SendMessageW(m_hWnd, CB_SETEDITSEL, dwStart, dwStart + iSelNum);
	}

	int GetSelNum()
	{
		if (m_bInDesignMode)
			return m_Info.iSelNum;
		else
		{
			DWORD dwStart, dwEnd;
			SendMessageW(m_hWnd, CB_GETEDITSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
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
		SendMessageW(GetEditControl(), EM_REPLACESEL, TRUE, (LPARAM)pszText);
	}

	PWSTR GetSelText(int* pcb = NULL)
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
		m_pszSelText = new WCHAR[dwEnd + 1];
		GetWindowTextW(m_hWnd, m_pszSelText, (int)dwEnd + 1);
		if (pcb)
			*pcb = (dwLen + 1) * sizeof(WCHAR);
		return m_pszSelText + dwStart;
	}

	eStlInline void SetMaxLen(int iMaxLen)
	{
		m_Info.iMaxLen = iMaxLen;
		SendMessageW(GetEditControl(), EM_SETLIMITTEXT, iMaxLen, 0);
	}

	eStlInline int GetMaxLen()
	{
		if (m_bInDesignMode)
			return m_Info.iMaxLen;
		else
			return SendMessageW(GetEditControl(), EM_GETLIMITTEXT, 0, 0);
	}

	eStlInline void SetCueBannerNoCopy(PCWSTR psz)
	{
		if (!m_bInDesignMode)
			SendMessageW(GetEditControl(), EM_SETCUEBANNER, FALSE, (LPARAM)psz);
	}

	void SetCueBanner(PCWSTR psz)
	{
		if (!psz)
		{
			*m_pszCueBanner = L'\0';
			SetCueBannerNoCopy(NULL);
			return;
		}

		wcsncpy(m_pszCueBanner, psz, CB_CUEBANNER_MAXLEN - 1);
		*(m_pszCueBanner + CB_CUEBANNER_MAXLEN - 1) = L'\0';
		SetCueBannerNoCopy(m_pszCueBanner);
	}

	eStlInline PCWSTR GetCueBanner(SIZE_T* pcb = NULL)
	{
		if (!m_bInDesignMode)
			SendMessageW(GetEditControl(), EM_GETCUEBANNER, (WPARAM)m_pszCueBanner, CB_CUEBANNER_MAXLEN);
		if (pcb)
			*pcb = wcslen(m_pszCueBanner);
		return m_pszCueBanner;
	}

	void SetComboBoxHeight(int cy)
	{
		m_Info.cyComboBox = cy;
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		int iOffset = rc.bottom - (int)SendMessageW(m_hWnd, CB_GETITEMHEIGHT, -1, 0);
		SendMessageW(m_hWnd, CB_SETITEMHEIGHT, -1, cy - iOffset);
	}

	eStlInline int GetComboBoxHeight()
	{
		return m_Info.cyComboBox;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		m_Info.cbImageList = m_ILData.size();
		m_Info.cchCueBanner = wcslen(m_pszCueBanner);
		const SIZE_T cbCueBanner = (m_Info.cchCueBanner + 1) * sizeof(WCHAR);
		auto hGlobal = FlattenInfoBase0(sizeof(ECOMBOBOXDATA) + m_Info.cbItems + m_Info.cbImageList + cbCueBanner, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ECOMBOBOXDATA));
		p += sizeof(ECOMBOBOXDATA);
		// 项目
		memcpy(p, m_pItems, m_Info.cbItems);
		p += m_Info.cbItems;
		// 图像列表
		memcpy(p, m_ILData.data(), m_Info.cbImageList);
		p += m_Info.cbImageList;
		// 提示文本
		memcpy(p, m_pszCueBanner, cbCueBanner);
		p += cbCueBanner;
		// 
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CComboBox(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:
			p->SetItems(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize, FALSE);
			break;
		case 1:
			p->SetType(pPropertyVaule->m_int);
			return TRUE;
		case 2:
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 3:
			p->SetMaxLen(pPropertyVaule->m_int);
			break;
		case 4:
			p->SetSelPos(pPropertyVaule->m_int);
			break;
		case 5:
			p->SetSelNum(pPropertyVaule->m_int);
			break;
		case 6:
			p->SetSelText((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 7:
			p->SetCueBanner((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 8:
			p->SetCurrSel(pPropertyVaule->m_int);
			break;
		case 9:
			p->SetItemHeight(pPropertyVaule->m_int);
			break;
		case 10:
			p->SetClr(0, pPropertyVaule->m_clr);
			break;
		case 11:
			p->SetClr(1, pPropertyVaule->m_clr);
			break;
		case 12:
			p->SetSelClr(0, pPropertyVaule->m_clr);
			break;
		case 13:
			p->SetSelClr(1, pPropertyVaule->m_clr);
			break;
		case 14:
			p->SetAutoSort(pPropertyVaule->m_bool);
			break;
		case 15:
			p->SetIntegralHeight(pPropertyVaule->m_bool);
			break;
		case 16:
			p->SetDisableNoScroll(pPropertyVaule->m_bool);
			break;
		case 17:
			p->SetImageList(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 18:
			p->SetEllipsis(pPropertyVaule->m_bool);
			break;
		case 19:
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;
		case 20:
			p->SetAlign(FALSE, pPropertyVaule->m_int);
			break;
		case 21:
			p->SetFont((LOGFONTA*)pPropertyVaule->m_data.m_pData);
			break;
		case 22:
			p->SetComboBoxHeight(pPropertyVaule->m_int);
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
		case 0:
			pPropertyVaule->m_data.m_pData = p->GetItems();
			pPropertyVaule->m_data.m_nDataSize = p->m_Info.cbItems;
			break;
		case 1:
			pPropertyVaule->m_int = p->GetType();
			break;
		case 2:
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:
			pPropertyVaule->m_int = p->GetMaxLen();
			break;
		case 4:
			pPropertyVaule->m_int = p->GetSelPos();
			break;
		case 5:
			pPropertyVaule->m_int = p->GetSelNum();
			break;
		case 6:
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetSelText(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 7:
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetCueBanner((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 8:
			pPropertyVaule->m_int = p->GetCurrSel();
			break;
		case 9:
			pPropertyVaule->m_int = p->GetItemHeight();
			break;
		case 10:
			pPropertyVaule->m_clr = p->GetClr(0);
			break;
		case 11:
			pPropertyVaule->m_clr = p->GetClr(1);
			break;
		case 12:
			pPropertyVaule->m_clr = p->GetSelClr(0);
			break;
		case 13:
			pPropertyVaule->m_clr = p->GetSelClr(1);
			break;
		case 14:
			pPropertyVaule->m_bool = p->GetAutoSort();
			break;
		case 15:
			pPropertyVaule->m_bool = p->GetIntegralHeight();
			break;
		case 16:
			pPropertyVaule->m_bool = p->GetDisableNoScroll();
			break;
		case 17:
			pPropertyVaule->m_data.m_pData = p->GetImageList(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 18:
			pPropertyVaule->m_bool = p->GetEllipsis();
			break;
		case 19:
			pPropertyVaule->m_bool = p->GetAlign(TRUE);
			break;
		case 20:
			pPropertyVaule->m_bool = p->GetAlign(FALSE);
			break;
		case 21:
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;
		case 22:
			pPropertyVaule->m_int = p->GetComboBoxHeight();
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
		{
			BYTE* pItems;
			SIZE_T cb;
			BOOL bOK = ShowComboBoxDesignDlg(&pItems, &cb, p->GetItems(), p->m_hImageList);
			if (bOK)
				p->SetItems(pItems, cb, TRUE);
			*pblModified = bOK;
		}
		break;
		case 2:// 内容
		{
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		break;
		case 7:// 提示文本
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
		if (nPropertyIndex >= 2 && nPropertyIndex <= 7)
			return p->GetType() != 2;

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
SUBCLASS_MGR_INIT(CComboBox, SCID_COMBOBOXPARENT, SCID_COMBOBOX)
ESTL_NAMESPACE_END

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_ComboBoxW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CComboBox::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CComboBox::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CComboBox::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CComboBox::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CComboBox::EInputW;
	case ITF_PROPERTY_UPDATE_UI:
		return (PFN_INTERFACE)elibstl::CComboBox::EPropUpdateUI;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CComboBox::ENotify;
	}
	return NULL;
}

static EVENT_INFO2 s_Event_ComboBox[] =
{
	/*000*/ {"列表项被选择", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"编辑内容被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*002*/ {"将弹出列表", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*003*/ {"列表被关闭", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*004*/ {"双击选择", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};
static UNIT_PROPERTY s_Member_ComboBox[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"项目", "Items", "", UD_CUSTOMIZE, UW_OS_WIN, NULL},
	/*001*/  {"类型", "Type", "", UD_PICK_INT, UW_OS_WIN, "简单组合框\0可编辑下拉组合框\0不可编辑下拉组合框\0\0"},
	/*002*/		{"内容", "Text", "", UD_CUSTOMIZE, UW_OS_WIN | UW_HAS_INDENT },
	/*003*/		{"最大文本长度", "MaxLen", "", UD_INT, UW_OS_WIN | UW_HAS_INDENT },
	/*004*/		{"起始选择位置", "SelStart", "", UD_INT, UW_OS_WIN | UW_HAS_INDENT },
	/*005*/		{"被选择字符数", "SelNum", "", UD_INT, UW_OS_WIN | UW_HAS_INDENT },
	/*006*/		{"被选择文本", "SelText", "", UD_CUSTOMIZE, UW_OS_WIN | UW_HAS_INDENT | UW_CANNOT_INIT },
	/*007*/		{"提示文本", "CueBanner", "", UD_CUSTOMIZE, UW_OS_WIN | UW_HAS_INDENT },
	/*008*/  {"现行选中项", "CurrSel", "", UD_INT, UW_OS_WIN, NULL},
	/*009*/  {"行高", "ItemHeight", "", UD_INT, UW_OS_WIN, NULL},
	/*010*/  {"文本颜色", "TextClr", "", UD_COLOR_BACK, UW_OS_WIN, NULL},
	/*011*/  {"背景颜色", "BKClr", "", UD_COLOR_BACK, UW_OS_WIN,NULL},
	/*012*/  {"选中文本颜色", "SelTextClr", "", UD_COLOR_BACK, UW_OS_WIN,NULL},
	/*013*/  {"选中背景颜色", "SelBKClr", "", UD_COLOR_BACK, UW_OS_WIN, NULL},
	/*014*/  {"自动排序", "AutoSort", "", UD_BOOL, UW_OS_WIN,  NULL},
	/*015*/  {"取整控件高度", "IntegralHeight", "是否将控件高度对齐到项目高度的整数倍", UD_BOOL, UW_OS_WIN, NULL},
	/*016*/  {"显示禁止滚动条", "DisableNoScroll", "滚动条不可用时显示禁止的滚动条而不是隐藏滚动条", UD_BOOL, UW_OS_WIN, NULL},
	/*017*/  {"图片组", "ImageList", "", UD_IMAGE_LIST, UW_OS_WIN,  NULL},
	/*018*/	 {"省略号裁剪", "Ellipsis", "", UD_BOOL, UW_OS_WIN,  NULL},
	/*019*/  {"横向对齐方式", "AlignH", "", UD_PICK_INT, UW_OS_WIN, "左边\0""居中\0""右边\0""\0"},
	/*020*/  {"纵向对齐方式", "AlignV", "", UD_PICK_INT, UW_OS_WIN,"上边\0""居中\0""下边\0""\0"},
	/*021*/  {"字体", "Font", "", UD_FONT, UW_OS_WIN , NULL},
	/*022*/  {"组合框高度", "ComboBoxHeight", "", UD_INT, UW_OS_WIN, NULL},
};
///////////////////////////////////方法
EXTERN_C void libstl_ComboBoxW_InsertString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	elibstl::CBITEMCOMMINFO CommInfo{};
	CommInfo.crBK = CommInfo.crSelBK = CommInfo.crText = CommInfo.crSelText = CLR_DEFAULT;
	CommInfo.idxImage = -1;
	pRetData->m_int = p->CBInsertString(
		elibstl::args_to_pszw(pArgInf, 1),
		CommInfo,
		pArgInf[2].m_int);
}
static ARG_INFO s_ArgsInsertString[] =
{
	{ "文本","",0,0,SDT_BIN,0,ArgMark::AS_NONE },
	{ "插入位置","",0,0,SDT_INT,-1,ArgMark::AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ComboBoxWInsertString = { {
		/*ccname*/  "插入项目",
		/*egname*/  "InsertString",
		/*explain*/ "返回项目索引，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsInsertString),
		/*arg lp*/  s_ArgsInsertString,
	} , ESTLFNAME(libstl_ComboBoxW_InsertString) };

EXTERN_C void libstl_ComboBoxW_DelString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	pRetData->m_bool = p->CBDeleteString(pArgInf[1].m_int);
}
static ARG_INFO s_ArgsDelString[] =
{
	{ "删除位置","若为-1则删除所有项目",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWDelString = { {
		/*ccname*/  "删除项目",
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
	} , ESTLFNAME(libstl_ComboBoxW_DelString) };

EXTERN_C void libstl_ComboBoxW_GetItemCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, CB_GETCOUNT, 0, 0);
}
FucInfo Fn_ComboBoxWGetItemCount = { {
		/*ccname*/  "取项目数",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemCount) };

EXTERN_C void libstl_ComboBoxW_GetTopIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_int = SendMessageW(hWnd, CB_GETTOPINDEX, 0, 0);
}
FucInfo Fn_ComboBoxWGetTopIndex = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_GetTopIndex) };

EXTERN_C void libstl_ComboBoxW_SetTopIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	pRetData->m_bool = (SendMessageW(hWnd, CB_SETTOPINDEX, pArgInf[1].m_int, 0) != CB_ERR);
}
static ARG_INFO s_ArgsSetTopIndex[] =
{
	{ "位置","",0,0,SDT_INT,0,ArgMark::AS_NONE }
};
FucInfo Fn_ComboBoxWSetTopIndex = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_SetTopIndex) };

EXTERN_C void libstl_ComboBoxW_GetItemlParam(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE}
};
FucInfo Fn_ComboBoxWGetItemlParam = { {
		/*ccname*/  "取项目数值",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemlParam) };

EXTERN_C void libstl_ComboBoxW_SetItemlParam(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "项目数值","",0,0,SDT_INT,0,ArgMark::AS_NONE }
};
FucInfo Fn_ComboBoxWSetItemlParam = { {
		/*ccname*/  "置项目数值",
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
	} , ESTLFNAME(libstl_ComboBoxW_SetItemlParam) };

EXTERN_C void libstl_ComboBoxW_GetItemString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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

	pRetData->m_pBin = elibstl::malloc_wstring(rsCaption.m_cchText);
	rsCaption.CopyTo((PWSTR)(pRetData->m_pBin + 8));
}
static ARG_INFO s_ArgsGetItemString[] =
{
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWGetItemString = { {
		/*ccname*/  "取项目文本",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemString) };

EXTERN_C void libstl_ComboBoxW_SetItemString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "文本","",0,0,SDT_BIN,0,ArgMark::AS_NONE }
};
FucInfo Fn_ComboBoxWSetItemString = { {
		/*ccname*/  "置项目文本",
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
	} , ESTLFNAME(libstl_ComboBoxW_SetItemString) };

EXTERN_C void libstl_ComboBoxW_FindString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "文本","",0,0,SDT_BIN,0,ArgMark::AS_NONE },
	{ "起始搜寻索引","",0,0,SDT_INT,0,ArgMark::AS_HAS_DEFAULT_VALUE },
	{ "匹配模式","0 - 包含  1 - 头部  2 - 尾部  3 - 相同",0,0,SDT_INT,0,ArgMark::AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ComboBoxWFindString = { {
		/*ccname*/  "寻找项目",
		/*egname*/  "FindString",
		/*explain*/ "成功返回找到的项目索引，失败返回-1",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsFindString),
		/*arg lp*/  s_ArgsFindString,
	} , ESTLFNAME(libstl_ComboBoxW_FindString) };

EXTERN_C void libstl_ComboBoxW_GetItemColor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "类型","0 - 背景  1 - 选中背景  2 - 文本  3 - 选中文本",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWGetItemColor = { {
		/*ccname*/  "取项目颜色",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemColor) };

EXTERN_C void libstl_ComboBoxW_SetItemColor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}
	COLORREF cr = pArgInf[3].m_int;

	elibstl::CBITEMINFO& Item = p->m_ItemsInfo[idx];
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
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemColor[] =
{
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "类型","0 - 背景  1 - 选中背景  2 - 文本  3 - 选中文本",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "颜色","若要保持缺省，传递 #默认色 常量",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSetItemColor = { {
		/*ccname*/  "置项目颜色",
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
	} , ESTLFNAME(libstl_ComboBoxW_SetItemColor) };

EXTERN_C void libstl_ComboBoxW_GetItemImageIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWGetItemImageIndex = { {
		/*ccname*/  "取项目图片索引",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemImageIndex) };

EXTERN_C void libstl_ComboBoxW_SetItemImageIndex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	int idx = pArgInf[1].m_int;
	if (idx < 0 || idx >(int)p->m_ItemsInfo.size())
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->m_ItemsInfo[idx].Info.idxImage = pArgInf[2].m_int;
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSetItemImageIndex[] =
{
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "图片索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSetItemImageIndex = { {
		/*ccname*/  "置项目图片索引",
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
	} , ESTLFNAME(libstl_ComboBoxW_SetItemImageIndex) };

EXTERN_C void libstl_ComboBoxW_InitStorage(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	if (pArgInf[1].m_int <= 0)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	pRetData->m_bool = p->CBInitStorage(pArgInf[1].m_int);
}
static ARG_INFO s_ArgsInitStorage[] =
{
	{ "项目数","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWInitStorage = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_InitStorage) };

EXTERN_C void libstl_ComboBoxW_GetImageList(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	pRetData->m_int = (int)p->GetImageList(pArgInf[1].m_bool);
}
static ARG_INFO s_ArgsGetImageList[] =
{
	{ "是否返回非外部图像列表","若本参数为真则返回值可能是控件内部维护的图像列表，绝对不能在外部删除或修改该图像列表",0,0,SDT_BOOL,FALSE,ArgMark::AS_HAS_DEFAULT_VALUE },
};
FucInfo Fn_ComboBoxWGetImageList = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_GetImageList) };

EXTERN_C void libstl_ComboBoxW_SetImageList(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	p->SetImageList((HIMAGELIST)pArgInf[1].m_int);
}
static ARG_INFO s_ArgsSetImageList[] =
{
	{ "图像列表句柄","该图像列表由调用者维护，控件不会修改或删除",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSetImageList = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_SetImageList) };

EXTERN_C void libstl_ComboBoxW_GetItemStringLength(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

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
	{ "索引","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWGetItemStringLength = { {
		/*ccname*/  "取项目文本长度",
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
	} , ESTLFNAME(libstl_ComboBoxW_GetItemStringLength) };

EXTERN_C void libstl_ComboBoxW_Sort(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	if (pArgInf[1].m_int == 0)
		std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
			[](elibstl::CBITEMINFO& i1, elibstl::CBITEMINFO& i2) -> bool
			{
				return wcscmp(i1.rsCaption, i2.rsCaption) < 0;
			});
	else
		std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
			[](elibstl::CBITEMINFO& i1, elibstl::CBITEMINFO& i2) -> bool
			{
				return wcscmp(i1.rsCaption, i2.rsCaption) > 0;
			});
	p->Redraw();
}
static ARG_INFO s_ArgsSort[] =
{
	{ "排序方式","0 - 升序  1 - 降序",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSort = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_Sort) };

typedef BOOL(__stdcall* CBSORTPROC)(LPARAM lParam1, LPARAM lParam2);
EXTERN_C void libstl_ComboBoxW_Sort2(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	CBSORTPROC pProc;
	if (pArgInf[1].m_dtDataType == SDT_INT)
		pProc = (CBSORTPROC)pArgInf[1].m_int;
	else if (pArgInf[1].m_dtDataType == SDT_SUB_PTR)
		pProc = (CBSORTPROC)pArgInf[1].m_dwSubCodeAdr;
	else
	{
		pRetData->m_bool = FALSE;
		return;
	}

	std::sort(p->m_ItemsInfo.begin(), p->m_ItemsInfo.end(),
		[pProc = pProc](elibstl::CBITEMINFO& i1, elibstl::CBITEMINFO& i2) -> bool
		{
			return pProc(i1.Info.lParam, i2.Info.lParam);
		});
	p->Redraw();
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSort2[] =
{
	{ "排序子程序","返回值类型为逻辑型，有两个整数型参数，传入两项目的自定义数值，若第一个参数代表的项目数据大于第二个，则返回真，否则返回假",0,0,_SDT_ALL,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSort2 = { {
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
	} , ESTLFNAME(libstl_ComboBoxW_Sort2) };

EXTERN_C void libstl_ComboBoxW_SwapItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	int idx1 = pArgInf[1].m_int;
	int idx2 = pArgInf[2].m_int;
	int cItems = p->m_ItemsInfo.size();
	if (idx1 < 0 || idx1 > cItems || idx2 < 0 || idx2 > cItems || idx1 == idx2)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->CBSwapItem(idx1, idx2);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsSwapItem[] =
{
	{ "索引1","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "索引2","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWSwapItem = { {
		/*ccname*/  "交换项目",
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
	} , ESTLFNAME(libstl_ComboBoxW_SwapItem) };

EXTERN_C void libstl_ComboBoxW_MoveItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	auto p = elibstl::CComboBox::m_CtrlSCInfo[hWnd];

	int idx1 = pArgInf[1].m_int;
	int idx2 = pArgInf[2].m_int;
	int cItems = p->m_ItemsInfo.size();
	if (idx1 < 0 || idx1 > cItems || idx2 < 0 || idx2 > cItems || idx1 == idx2)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	p->CBMoveItem(idx1, idx2);
	pRetData->m_bool = TRUE;
}
static ARG_INFO s_ArgsMoveItem[] =
{
	{ "索引1","",0,0,SDT_INT,0,ArgMark::AS_NONE },
	{ "索引2","",0,0,SDT_INT,0,ArgMark::AS_NONE },
};
FucInfo Fn_ComboBoxWMoveItem = { {
		/*ccname*/  "移动项目",
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
	} , ESTLFNAME(libstl_ComboBoxW_MoveItem) };


static INT s_Cmd_ComboBox[] = { 276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297 };

ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtComboBox = {
	"组合框W",//中文名称
	"ComboBoxW",//英文名称
	"Unicode组合框",//说明
	ARRAYSIZE(s_Cmd_ComboBox),//命令数量
	s_Cmd_ComboBox,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_COMBOBOX_W ,//资源ID
	ARRAYSIZE(s_Event_ComboBox),
	s_Event_ComboBox,
	ARRAYSIZE(s_Member_ComboBox),//属性数
	s_Member_ComboBox,//属性指针
	libstl_GetInterface_ComboBoxW,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END