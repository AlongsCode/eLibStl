#include "HexView_Jmp.h"
#include <stdio.h>


#define IDC_CBB_INPUT       1000    // 输入文本组合框

#define IDC_RADIO_START     2000    // 文件开始
#define IDC_RADIO_NOW       2001    // 现在位置
#define IDC_RADIO_NOW2      2002    // 现在位置往上
#define IDC_RADIO_END       2003    // 文件结束

#define IDC_RADIO_10        3000    // 10进制
#define IDC_RADIO_16        3001    // 16进制


typedef struct HEXJMP_DATA
{
    HWND        hWnd;       // 对话框句柄
    PHEXJMP     pArg;       // 传递给对话框的参数
    BOOLEAN     isOk;       // 是否点击了确定按钮
    SIZE_T      start;      // 跳转对话框用
    HWND        hStart;
    HWND        hNow;
    HWND        hNow2;
    HWND        hEnd;
    HWND        h10;
    HWND        h16;
    HWND        hCbb;
}*PHEXJMP_DATA;

HWND HexView_Jmp_CreateControl(LPCWSTR szClass, LPCWSTR title, DWORD styleEx, DWORD style, int x, int y, int cx, int cy, HWND hParent, INT_PTR id, LPCWSTR lpszTips = 0);
INT_PTR CALLBACK HexView_Jmp_DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



// 返回是否输入了值
int HexView_Jmp_Dialog(PHEXJMP arg)
{
    struct __DLGTEMPLATE : DLGTEMPLATE
    {
        WORD menuid;
        WORD cls;
        wchar_t caption[1024];
    };

    __DLGTEMPLATE dlg;
    memset(&dlg, 0, sizeof(dlg));
    dlg.style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_VISIBLE;
    dlg.dwExtendedStyle = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
    dlg.cdit = 0;
    wcscpy_s(dlg.caption, arg->szCaption);

    HEXJMP_DATA data = { 0 };
    data.pArg = arg;

    INT_PTR bRet = DialogBoxIndirectParamW(GetModuleHandleW(0), &dlg, data.pArg->hParent, HexView_Jmp_DlgProc, (LPARAM)&data);

    return data.isOk;
}

// 释放搜索返回的数据
void HexView_Jmp_Free(LPVOID ptr)
{
    if ( ptr )
        free(ptr);
}

HWND HexView_Jmp_CreateControl(LPCWSTR szClass, LPCWSTR title, DWORD styleEx, DWORD style, int x, int y, int cx, int cy, HWND hParent, INT_PTR id, LPCWSTR lpszTips)
{
    HWND hWnd = CreateWindowExW(styleEx, szClass, title, style, x, y, cx, cy, hParent, (HMENU)(LONG_PTR)id, GetModuleHandleW(0), 0);

    static HFONT hFont;
    if ( !hFont )
    {
        LOGFONTW lf = { 0 };
        SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
        lf.lfHeight     = -12;
        lf.lfWeight     = FW_NORMAL;
        lf.lfItalic     = false; // 斜体
        lf.lfUnderline  = false; // 下划线
        lf.lfStrikeOut  = false; // 删除线
        lf.lfCharSet    = GB2312_CHARSET;
        wcscpy_s(lf.lfFaceName, L"微软雅黑");
        hFont = CreateFontIndirectW(&lf);
    }
    SendMessageW(hWnd, WM_SETFONT, (WPARAM)hFont, 0);
    return hWnd;
}

// 添加一个字符串到下拉框, 并且把参数设置进去
inline int HexView_Combobox_AddString(HWND hWnd, LPCWSTR lpsz, LPARAM param = 0, int index = -1)
{
    int ret = ( (int)(DWORD)SendMessageW(hWnd, CB_INSERTSTRING, (WPARAM)(int)index, (LPARAM)lpsz) );
    if ( ret >= 0 && param )
    {
        SendMessageW(hWnd, CB_SETITEMDATA, ret, param);
    }
    return ret;
}

INT_PTR CALLBACK HexView_Jmp_DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    if ( message == WM_INITDIALOG )   // 对话框初始化, 把指针设置进窗口里
        SetWindowLongPtrW(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);

    PHEXJMP_DATA pData = (PHEXJMP_DATA)GetWindowLongPtrW(hDlg, GWLP_USERDATA);  // 每个消息都要获取这个指针
    if ( !pData ) return false;
    INT_PTR ret = 0;
    switch ( message )
    {
    case WM_INITDIALOG:
    {
        pData->hWnd = hDlg;
        RECT rc = { 0 };
        GetWindowRect(pData->pArg->hParent, &rc);
        if ( rc.right - rc.left <= 0 || rc.bottom - rc.top <= 0 )
        {
            rc.left = 0;
            rc.top = 0;
            rc.right = GetSystemMetrics(SM_CXSCREEN);
            //rc.bottom = GetSystemMetrics(SM_CYSCREEN);
            rc.bottom = GetSystemMetrics(SM_CYMAXIMIZED);
        }

        const int margin = 11;  // 边距
        const int editWidth = 460;
        const int cbkWidth = 140;
        const int btnWidth = 140;
        const int inputWidth = editWidth + margin * 2 + 16;
        const int inputHeight = 218;
        const int width = rc.right - rc.left;
        const int height = rc.bottom - rc.top;
        const int inputLeft = rc.left + ( width - inputWidth ) / 2;
        const int inputTop = rc.top + ( height - inputHeight ) / 2;
        const int height_cbb = 200;
        const int width_cbb = editWidth - 55;
        const int static_height = 20;
        const int right = margin + 55 + width_cbb;

        MoveWindow(hDlg, inputLeft, inputTop, inputWidth, inputHeight, true);

        int top = margin;

        const DWORD styleStatic = WS_GROUP | WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE;
        DWORD style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
        DWORD styleEx = WS_EX_NOPARENTNOTIFY;

        pData->hCbb = HexView_Jmp_CreateControl(L"ComboBox", 0, styleEx, style, margin + 55, top, width_cbb, height_cbb, hDlg, IDC_CBB_INPUT);
        GetWindowRect(pData->hCbb, &rc);
        const int cbbHeight = rc.bottom - rc.top;
        HexView_Jmp_CreateControl(L"static", L"跳转位置", styleEx, styleStatic, margin, top, 55, cbbHeight, hDlg, 0);
        top += cbbHeight + 5;


        PHEX_NODE node = pData->pArg->listText;

        int count = 0;
        while ( node )
        {
            HexView_Combobox_AddString(pData->hCbb, node->text);
            count++;
            node = node->next;
            if ( count >= 20 )
                break;  // 最多显示20个
        }

        if ( count > 0 )
            SendMessageW(pData->hCbb, CB_SETCURSEL, 0, 0);


        HexView_Jmp_CreateControl(L"static", L"相对于...", styleEx, styleStatic, margin, top, width_cbb, static_height, hDlg, 0);
        top += static_height + 5;

        const int styleBtn = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
        style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON;
        const int radioWidth = 120;
        int saveTop = top;
        int left = margin + 20;

        LPCWSTR pszRadio1 = L"文件开始(&B)";
        LPCWSTR pszRadio2 = L"现在位置";
        LPCWSTR pszRadio3 = L"现在位置往上";
        LPCWSTR pszRadio4 = L"文件结尾(&E)";
        if ( pData->pArg->isAsm )
        {
            pszRadio1 = L"第一个表项(&B)";
            pszRadio2 = L"现在位置";
            pszRadio3 = L"现在位置往上";
            pszRadio4 = L"最后一个表项(&E)";
        }

        pData->hStart = HexView_Jmp_CreateControl(L"button", pszRadio1, styleEx, style | WS_GROUP, left, top, radioWidth, static_height, hDlg, IDC_RADIO_START);
        top += static_height + 5;
        pData->hNow = HexView_Jmp_CreateControl(L"button", pszRadio2, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_NOW);
        top += static_height + 5;
        pData->hNow2 = HexView_Jmp_CreateControl(L"button", pszRadio3, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_NOW2);
        top += static_height + 5;
        pData->hEnd = HexView_Jmp_CreateControl(L"button", pszRadio4, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_END);


        top = saveTop - 5 - (static_height / 2);
        const int btnHeight = static_height * 2 + 5 + ( static_height / 2);
        left = right - btnWidth;
        HexView_Jmp_CreateControl(L"button", L"跳转", styleEx, styleBtn | BS_DEFPUSHBUTTON, left, top, btnWidth, btnHeight, hDlg, IDOK);
        top += btnHeight + 5;
        HexView_Jmp_CreateControl(L"button", L"取消", styleEx, styleBtn, left, top, btnWidth, btnHeight, hDlg, IDCANCEL);


        left -= 80;
        top = saveTop;
        top += static_height + 5;
        top += static_height + 5;
        pData->h10 = HexView_Jmp_CreateControl(L"button", L"10进制", styleEx, style | WS_GROUP, left, top, 70, static_height, hDlg, IDC_RADIO_10);
        top += static_height + 5;
        pData->h16 = HexView_Jmp_CreateControl(L"button", L"16进制", styleEx, style, left, top, 70, static_height, hDlg, IDC_RADIO_16);

        HWND hRadio = HIWORD(pData->pArg->nMode) ? pData->h16 : pData->h10;
        int mode = LOWORD(pData->pArg->nMode);
        SendMessageW(hRadio, BM_SETCHECK, BST_CHECKED, 0);

        hRadio = pData->hStart;
        if ( mode == 0 )
            hRadio = pData->hStart;
        else if ( mode == 1 )
            hRadio = pData->hNow;
        else if ( mode == 2 )
            hRadio = pData->hNow2;
        else if ( mode == 3 )
            hRadio = pData->hEnd;
        SendMessageW(hRadio, BM_SETCHECK, BST_CHECKED, 0);

        SetFocus(pData->hCbb);
        return false;
        break;
    }
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        switch ( id )
        {
        case IDOK:
        {
            //pData->pArg->nMode = (int)(DWORD)SendMessageW(hWndMode, CB_GETCURSEL, 0, 0);
            int isHex = 0;
            int mode = 0;

            isHex = SendMessageW(pData->h16, BM_GETCHECK, 0, 0) == BST_CHECKED;

            if ( SendMessageW(pData->hNow, BM_GETCHECK, 0, 0) == BST_CHECKED )
                mode = 1;
            else if ( SendMessageW(pData->hNow2, BM_GETCHECK, 0, 0) == BST_CHECKED )
                mode = 2;
            else if( SendMessageW(pData->hEnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
                mode = 3;
            else
                mode = 0;


            int len = GetWindowTextLengthW(pData->hCbb) + 1;
            int size = len * sizeof(wchar_t);

            pData->pArg->pRet = (LPWSTR)HexViewAlloc(size);
            len = GetWindowTextW(pData->hCbb, pData->pArg->pRet, len);
            pData->isOk = TRUE;
            LPCWSTR pStr = pData->pArg->pRet;
            if ( len > 1 && _wcsnicmp(pStr, L"0x", 2) == 0 )
            {
                isHex = 1;
                pStr += 2;
            }

            INT64 num = 0;
            if ( isHex )
            {
                swscanf_s(pStr, L"%016llX", &num);
            }
            else
            {
                num = _wtoll(pData->pArg->pRet);
            }


            pData->pArg->nMode = MAKELONG(mode, isHex);
            pData->pArg->pos = num;

            EndDialog(hDlg, 1);
            break;
        }
        case IDCANCEL:
        {
            EndDialog(hDlg, 0);
            break;
        }
        default:
            return (INT_PTR)false;
        }
        break;
    }
    case WM_CTLCOLORMSGBOX:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORLISTBOX:
    case WM_CTLCOLORBTN:
    case WM_CTLCOLORDLG:
    case WM_CTLCOLORSCROLLBAR:
    case WM_CTLCOLORSTATIC:
        return (INT_PTR)GetStockObject(WHITE_BRUSH);
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps = { 0 };
        BeginPaint(hDlg, &ps);
        RECT rc = { 0 };
        GetClientRect(hDlg, &rc);
        FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
        EndPaint(hDlg, &ps);
        break;
    }
    default:
        return (INT_PTR)false;
    }
    return (INT_PTR)true;
}

