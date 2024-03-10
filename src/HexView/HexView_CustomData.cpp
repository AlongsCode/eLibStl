#include "HexView_Help.h"
#include <windowsx.h>
#include <strsafe.h>
#include <CDialog.h>

HEXVIEW_NAMESPACE_BEGIN

typedef struct _HEXVIEW_COLOR_HWND
{
    HWND    clrBack;            // �ı�������ɫ
    HWND    clrBackSel;         // ѡ�б�����ɫ
    HWND    clrLine;            // ������ɫ, �����߿�ɫ
    HWND    clrModifyText;      // �޸Ĺ����ı���ɫ
    HWND    clrModifyTextSel;   // �޸Ĺ����ı���ɫ, ѡ�е���ɫ
    HWND    clrTextAddress;     // �ı���ɫ, ��ߵ�ַ����ɫ
    HWND    clrTextSelChar;     // �ı���ɫ, ѡ�е��ı���ɫ, �ұ��ַ���
    HWND    clrText1;           // �ı���ɫ, ��һ�����ӵ���ɫ
    HWND    clrText2;           // �ı���ɫ, �ڶ������ӵ���ɫ
    HWND    clrTextSel1;        // ѡ���ı���ɫ, ��һ�����ӵ���ɫ
    HWND    clrTextSel2;        // ѡ���ı���ɫ, �ڶ������ӵ���ɫ

}HEXVIEW_COLOR_HWND, * PHEXVIEW_COLOR_HWND;

typedef struct HEXVIEW_DIALOG_STRUCT
{
    PHEXVIEW_PROPERTY pData;    // �������Ϣ
    HEXVIEW_COLOR_HWND wnd;     // �Ի���ľ����Ϣ
    HEXVIEW_COLOR clr;          // �Ի������ɫ, ���ȷ���������ṹ�������������ɫ��
    HWND hParent;               // �����ھ��, �����������������
    HWND hWnd;                  // �Ի��򴰿�
    HWND hDraw;                 // �滭�Ĵ���, �����Ԥ��
    HWND hEdit;                 // ����ʱ��ʱ�Ĵ���, ���б�ǩ���ʱ��¼�ľ��
    WNDPROC oldProc;            // �滭���ڵ�ԭ�ص�����
    bool isOk;                  // �Ƿ�����ȷ��
}*PHEXVIEW_DIALOG_STRUCT;

INT_PTR CALLBACK HexView_Dialog_Color_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool HexView_Dialog_Command(HWND hWnd, int id, int code, HWND hChild);
LRESULT CALLBACK HexView_Dialog_Draw_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND HexView_Dialog_CreateControl(LPCWSTR szClass, LPCWSTR title, DWORD styleEx, DWORD style, HWND hParent, INT_PTR id, int x, int y, int cx, int cy);

// Ĭ��Ϊ΢���ź�, �����С -12, û����ʽ
// lfWeight = ����,  lfItalic = б��,  lfUnderline = �»���, lfStrikeOut = ɾ����
HFONT HexView_CreateFontW(const wchar_t* name = L"΢���ź�", int size = -12, BOOL lfWeight = false, BOOL lfItalic = false, BOOL lfUnderline = false, BOOL lfStrikeOut = false);
void HexView_MoveDialog(HWND hWnd, HWND hParent, int width, int height);
bool HexView_IsRgbLight(COLORREF clr);


bool HexView_Dialog_Color(PHEXVIEW_PROPERTY pData)
{
    struct __DLGTEMPLATE : DLGTEMPLATE
    {
        WORD menuid;
        WORD cls;
        wchar_t caption[1024];
    };

    __DLGTEMPLATE dlg;
    memset(&dlg, 0, sizeof(dlg));
    dlg.style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
    dlg.dwExtendedStyle = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
    dlg.cdit = 0;
    wcscpy_s(dlg.caption, L"ʮ�����ƿ���ɫ����");
    HWND hParent = (HWND)elibstl::NotifySys(NES_GET_MAIN_HWND, 0, 0);
    HEXVIEW_DIALOG_STRUCT arg = { 0 };
    arg.pData = pData;
    arg.hParent = hParent;
    arg.wnd = { 0 };
    arg.clr = pData->clr;
    arg.isOk = false;
    DialogBoxIndirectParamW(GetModuleHandleW(0), &dlg, hParent, HexView_Dialog_Color_Proc, (LPARAM)&arg);
    return arg.isOk;
}
static void HexView_Dialog_SetStaticColor(PHEXVIEW_DIALOG_STRUCT pArg, HWND hStatic, COLORREF clr)
{
    const bool isLight = HexView_IsRgbLight(clr);
    COLORREF clrText = isLight ? RGB(0, 0, 0) : RGB(255, 255, 255);
    SetPropW(hStatic, L"clrBack", (LPVOID)(LONG_PTR)clr);
    SetPropW(hStatic, L"clrText", (LPVOID)(LONG_PTR)clrText);
    InvalidateRect(hStatic, 0, 0);
    COLORREF* pClr = (COLORREF*)GetPropW(hStatic, L"pClr");
    if (pClr)
        *pClr = clr;
    if (pArg->hDraw)
        InvalidateRect(pArg->hDraw, 0, 0);
}
// ����11��������ɫ�ı༭��, ����Ǳ�ǩ��ʾʲô��ɫ, �м���������ɫ�ı༭��, �ұ���һ����ť����󵯳���ɫѡ����
static int HexView_Dialog_Create_Color_edit(PHEXVIEW_DIALOG_STRUCT pArg)
{
    const DWORD dwStyle = WS_TABSTOP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL;
    const DWORD dwStyleEx = WS_EX_CLIENTEDGE | WS_EX_CONTROLPARENT;
    const DWORD dwStyleStatic = WS_TABSTOP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_CENTERIMAGE | SS_CENTER;
    const int height = 20;
    const int left_static = 8;
    const int width_static = 150;
    const int left_edit = left_static + width_static + 5;
    const int width_edit = 80;
    const int right = left_edit + width_edit;
    int top = 8;

    int id_static = 8000;
    int id_edit = 9000;
    wchar_t buf[50];


    // ����������ɫ�ı༭��, ����Ǳ�ǩ��ʾʲô��ɫ, �ұ���������ɫ�ı༭��
    auto pfn_create_edit = [&](COLORREF& clr, LPCWSTR pszTitle) -> HWND
    {
        swprintf_s(buf, L"%u", clr);
        HWND hStatic = HexView_Dialog_CreateControl(WC_STATICW, pszTitle, 0, dwStyleStatic, pArg->hWnd, id_static++, left_static, top, width_static, height);
        HWND hEdit = HexView_Dialog_CreateControl(WC_EDIT, buf, dwStyleEx, dwStyle, pArg->hWnd, id_edit++, left_edit, top, width_edit, height);
        SetPropW(hEdit, L"control", hStatic);
        SetPropW(hStatic, L"control", hEdit);
        SetPropW(hStatic, L"pClr", &clr);

        HexView_Dialog_SetStaticColor(pArg, hStatic, clr);

        top += height + 5;
        return hEdit;
    };

#define _CREATE_EDIT_(_name, _s) pArg->wnd._name = pfn_create_edit(pArg->clr._name, _s)

    _CREATE_EDIT_(clrBack         ,  L"�ı�������ɫ"                         );
    _CREATE_EDIT_(clrBackSel      ,  L"ѡ�б�����ɫ"                         );
    _CREATE_EDIT_(clrLine         ,  L"������ɫ"                            );
    _CREATE_EDIT_(clrModifyText   ,  L"�޸Ĺ����ı���ɫ"                     );
    _CREATE_EDIT_(clrModifyTextSel,  L"�޸Ĺ���ѡ���ı���ɫ"                  );
    _CREATE_EDIT_(clrTextAddress  ,  L"��ߵ�ַ����ɫ"                       );
    _CREATE_EDIT_(clrTextSelChar  ,  L"ѡ�е��ı���ɫ"                       );
    _CREATE_EDIT_(clrText1        ,  L"��һ�����ӵ��ı���ɫ"                  );
    _CREATE_EDIT_(clrText2        ,  L"�ڶ������ӵ��ı���ɫ"                  );
    _CREATE_EDIT_(clrTextSel1     ,  L"��һ�����ӵ�ѡ���ı���ɫ"               );
    _CREATE_EDIT_(clrTextSel2     ,  L"�ڶ������ӵ�ѡ���ı���ɫ"               );

    return top - 10;
}

INT_PTR CALLBACK HexView_Dialog_Color_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)lParam);
        PHEXVIEW_DIALOG_STRUCT pArg = (PHEXVIEW_DIALOG_STRUCT)lParam;
        pArg->hWnd = hWnd;

        // �����ﴴ�����
        DWORD dwStyleEx = 0, dwStyle = 0;
        HWND hChild = 0;

        const int bottom = HexView_Dialog_Create_Color_edit(pArg);
        const int width_dialog = 880;
        const int height_dialog = bottom + 58 + 90;
        const int left = 248;

        pArg->hDraw = HexView_Dialog_CreateControl(L"#32770", 0, dwStyleEx, dwStyle, hWnd, 3000, left, 8, 620, 375);
        SetPropW(pArg->hDraw, L"proc", pArg);
        pArg->oldProc = (WNDPROC)SetWindowLongPtrW(pArg->hDraw, GWLP_WNDPROC, (LONG_PTR)HexView_Dialog_Draw_Proc);

        int mid = left / 2;
        const int width_button = 80;
        const int height_button = 32;
        const int top = height_dialog - height_button - 48;
        int left_ok = mid - width_button - 5;
        int left_cancel = mid + 5;
        HexView_Dialog_CreateControl(WC_BUTTONW, L"&O.ȷ��", dwStyleEx, dwStyle, hWnd, IDOK, left_ok, top, width_button, height_button);
        HexView_Dialog_CreateControl(WC_BUTTONW, L"&C.ȡ��", dwStyleEx, dwStyle, hWnd, IDCANCEL, left_cancel, top, width_button, height_button);

        HexView_MoveDialog(hWnd, pArg->hParent, width_dialog, height_dialog);
        break;
    }
    case WM_CTLCOLOR:
    case WM_CTLCOLORMSGBOX:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORLISTBOX:
    case WM_CTLCOLORBTN:
    case WM_CTLCOLORDLG:
    case WM_CTLCOLORSCROLLBAR:
    case WM_CTLCOLORSTATIC:
    {
        HWND hChild = (HWND)lParam;
        int id = GetDlgCtrlID(hChild);
        if (id >= 8000 && id < 9000)
        {
            HDC hdc = (HDC)wParam;
            COLORREF clrBack = (COLORREF)GetPropW(hChild, L"clrBack");
            COLORREF clrText = (COLORREF)GetPropW(hChild, L"clrText");
            SetTextColor(hdc, clrText);
            SetBkColor(hdc, clrBack);
            HBRUSH hbr = CDialog::GetBrush(clrBack);
            return (LRESULT)hbr;
        }
        return (LRESULT)GetStockBrush(WHITE_BRUSH);
    }
    case WM_COMMAND:
    {
        const int id = LOWORD(wParam);
        const int code = HIWORD(wParam);
        return (INT_PTR)HexView_Dialog_Command(hWnd, id, code, (HWND)lParam);
    }
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
        break;
    }
    default:
        return (INT_PTR)false;
    }
    return (INT_PTR)true;
}

bool HexView_Dialog_Command2(HWND hWnd, int id, int code, HWND hChild, PHEXVIEW_DIALOG_STRUCT pArg)
{
    switch (code)
    {
    case EN_CHANGE:     // �༭�����ݸı�, Ū��ʱ�Ӹı��ǩ��ɫ
    {
        pArg->hEdit = hChild;
        SetTimer(pArg->hWnd, (UINT_PTR)pArg, 100, [](HWND hWnd, UINT message, UINT_PTR id, DWORD timer) -> void
        {
            KillTimer(hWnd, id);
            PHEXVIEW_DIALOG_STRUCT pArg = (PHEXVIEW_DIALOG_STRUCT)id;
            int size = GetWindowTextLengthW(pArg->hEdit) + 1;
            std::vector<wchar_t> buf(size);
            GetWindowTextW(pArg->hEdit, &buf[0], size);
            int clr = _wtoi(&buf[0]);
            HWND hStatic = (HWND)GetPropW(pArg->hEdit, L"control");
            HexView_Dialog_SetStaticColor(pArg, hStatic, clr);
        });
        break;
    }
    case STN_CLICKED:   // ��ǩ������, ������ɫѡ��Ի���
    {
        HWND hStatic = hChild;
        pArg->hEdit = (HWND)GetPropW(hStatic, L"control");
        COLORREF clrBack = (COLORREF)GetPropW(hStatic, L"clrBack");
        static COLORREF crDef[16] =
        {
            RGB(255, 255, 255), RGB(192, 192, 192), RGB(128, 128, 128), RGB(0, 0, 0),
            RGB(255, 0, 0),     RGB(128, 0, 0),     RGB(255, 255, 0),   RGB(128, 128, 0),
            RGB(0, 255, 0),     RGB(0, 128, 0),     RGB(0, 255, 255),   RGB(0, 128, 128),
            RGB(0, 0, 255),     RGB(0, 0, 128),     RGB(255, 0, 255),   RGB(128, 0, 128),
        };

        CHOOSECOLORW cc = { 0 };
        cc.lStructSize = sizeof(cc);
        cc.hwndOwner = pArg->hWnd;
        cc.rgbResult = clrBack;
        cc.lpCustColors = crDef;
        cc.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
        if (!ChooseColorW(&cc))
            break;
        HexView_Dialog_SetStaticColor(pArg, hStatic, cc.rgbResult);
        wchar_t buf[50];
        swprintf_s(buf, L"%u", cc.rgbResult);
        SetWindowTextW(pArg->hEdit, buf);
        break;
    }
    default:
        return false;
    }
    return true;
}
bool HexView_Dialog_Command(HWND hWnd, int id, int code, HWND hChild)
{
    PHEXVIEW_DIALOG_STRUCT pArg = (PHEXVIEW_DIALOG_STRUCT)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
    {
        if (id == IDOK)
            pArg->pData->clr = pArg->clr;
        pArg->isOk = id == IDOK ? 1 : 0;
        EndDialog(hWnd, pArg->isOk);
        //DestroyWindow(hWnd);
        break;
    }
    default:
        return HexView_Dialog_Command2(hWnd, id, code, hChild, pArg);
    }
    return true;
}

static void CALLBACK HexView_Dialog_Draw_OnPaint_DrawLine(HDC hdc, int cyClient, int left)
{
    MoveToEx(hdc, left, 0, 0);
    LineTo(hdc, left, cyClient);
}
// �滭�м��16����ֵ, ���������ʽ�����滭ʲô��ʽ, 1/2/4/8 �ֽ�, ����, ˫����, �з����޷��ŵȸ�ʽ
void HexView_Dialog_Draw_OnPaint_DrawDrawHexValue(HDC hdc, int Position1, int vl, int top)
{
    wchar_t Buffer[100];    // ת����ֵ�Ļ�����, 100���ֽ��㹻��, ������˫���ȸ��㶼�������

    StringCchPrintfW(Buffer, _countof(Buffer), L"%02X", vl);
    TextOutW(hdc, Position1, top, (PCWSTR)Buffer, 2);

}

// �滭�ұߵ��ַ�
void HexView_Dialog_Draw_OnPaint_DrawCharValue(HDC hdc, int Position2, int vl, int top)
{
    wchar_t Buffer[32]; // ���ֽ�ת���ַ��õĻ�����
    if (isprint(vl))
    {
        StringCchPrintfW(Buffer, _countof(Buffer), L"%c", vl);
    }
    else
    {
        wcscpy_s(Buffer, _countof(Buffer), L".");
    }

    TextOutW(hdc, Position2, top, (PCWSTR)Buffer, 1);
}



static void CALLBACK HexView_Dialog_Draw_OnPaint_Draw(HDC hdc, PHEXVIEW_DIALOG_STRUCT pArg, int cxClient, int cyClient)
{
    RECT rcText = { 0 };
    HEXVIEW_COLOR& clr = pArg->clr;
    DrawTextW(hdc, L"FF", 2, &rcText, DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);
    const int width_hex_char = rcText.right - rcText.left;  // һ��16����ռ�õĿ��
    const int nSpace = 8;
    const int count = 16;   // �滭���ٸ�16����

    DrawTextW(hdc, L"0x00401000", 10, &rcText, DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);
    const int right_addr = rcText.right - rcText.left + 5;
    const int height = rcText.bottom - rcText.top;
    const int left_hex = right_addr + 9;
    const int left_line1 = right_addr + 4;
    const int left_line2 = left_hex + (count * width_hex_char) + (count * nSpace - nSpace / 2);
    const int left_char = left_line2 + 9;
    int top = 2;
    RECT rc = { 0, 0, cxClient, height };


    TEXTMETRICW TextMetric;
    GetTextMetricsW(hdc, &TextMetric);
    int WidthChar = TextMetric.tmAveCharWidth;
    int HeightChar = TextMetric.tmHeight;

    HexView_Dialog_Draw_OnPaint_DrawLine(hdc, cyClient, left_line1);
    HexView_Dialog_Draw_OnPaint_DrawLine(hdc, cyClient, left_line2);

    int Position1 = left_hex;
    int Position2 = left_char;
    BYTE psz[] =
        "elibstl:        "
        "       761463364"
        "QQ: 121007124   "
        "Groud: 20752843 "
        "                "
        " \0 \0 \0 \0 \0 \0 \0 \0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
        "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
        "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"
        "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F"
        "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F"
        "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F"
        "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F"
        "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"
        "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"
        "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
        "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
        "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
        "\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
        "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
        "\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF"
        ;
    const int str_len = sizeof(psz) - 1;
    //for (char& ch : psz)
    //{
    //    if (ch == ' ')
    //        ch = 0;
    //}



    auto pfn_draw_text = [&](int start, int end, bool isSel, bool isModify)
    {
        SetBkColor(hdc, isSel ? clr.clrBackSel : clr.clrBack);
        COLORREF clrText1 = isSel ? clr.clrTextSel1 : clr.clrText1;
        COLORREF clrText2 = isSel ? clr.clrTextSel2 : clr.clrText2;
        COLORREF clrChar = isSel ? clr.clrTextSelChar : clr.clrTextAddress;
        for (int i = start; i < end && i < str_len; i++)
        {
            const COLORREF clrText = isModify ? clr.clrModifyText : ((i % 2 == 0) ? clrText1 : clrText2);
            if (isSel && i + 1 < end)
            {
                // �������������16����ֵ֮�����һС�οհ�
                rc.top = top;
                rc.bottom = top + HeightChar;
                rc.left = Position1 + WidthChar * 2;
                rc.right = rc.left + WidthChar;
                ExtTextOutW(hdc, 0, top, ETO_OPAQUE, &rc, NULL, 0, NULL);
            }

            SetTextColor(hdc, clrText);
            HexView_Dialog_Draw_OnPaint_DrawDrawHexValue(hdc, Position1, psz[i], top);

            SetTextColor(hdc, clrChar);
            HexView_Dialog_Draw_OnPaint_DrawCharValue(hdc, Position2, psz[i], top);

            Position1 = Position1 + WidthChar * 3;
            Position2 = Position2 + WidthChar;
        }
    };

    LONG addr = 0x00401000;
    wchar_t buf_addr[50];
    struct DRAW_INFO
    {
        int start;
        int end;
        bool isModify;
    };
    const DRAW_INFO draw_info[23] =
    {
        // ѡ����ʼλ��, ѡ�н���λ��, �Ƿ��޸�
        {0, 8,  false}, // elibstl:
        {7, 16, true }, // 761463364
        {2, 6,  false}, // QQ
        {4, 9,  false}, // Groud
        {0, 0,  false}, // 16�ո�
        {0, 16, false}, // �ո�+�ض��ַ�
        {0, 0 , true},  // 16�ض��ַ�
        {0, 16, true},  // 00-0F
        {0, 0, false},  // 10-1F
        {0, 0, false},  // 20-2F
        {0, 16, false}, // 30-3F
        {0, 0, false},  // 40-4F
        {0, 16, true},  // 50-5F
        {0, 0, false},  // 60-6F
        {0, 0, false},  // 70-7F
        {0, 0, false},  // 80-8F
        {0, 0, true},   // 90-9F
        {0, 0, false},  // A0-AF
        {0, 0, false},  // B0-BF
        {3, 12, false}, // C0-CF
        {0, 0, false},  // D0-DF
        {0, 0, false},  // E0-EF
        {0, 0, false},  // F0-FF
    };
    int nCharStart = 0;
    for (const DRAW_INFO& info : draw_info)
    {
        Position1 = left_hex;
        Position2 = left_char;

        swprintf_s(buf_addr, L"0x%08X", addr);
        rcText = { 5, top, right_addr, top + HeightChar };
        SetBkColor(hdc, clr.clrBack);
        SetTextColor(hdc, clr.clrTextAddress);
        DrawTextW(hdc, buf_addr, 10, &rcText, DT_VCENTER | DT_SINGLELINE);

        int start = 0;
        int end = info.start - start;
        if (end - start > 0)    // �Ȼ滭ѡ����߲���
            pfn_draw_text(start + nCharStart, end + nCharStart, false, info.isModify);

        start = info.start;
        end = info.end;
        if (end - start > 0)    // �ٻ滭ѡ�в���
            pfn_draw_text(start + nCharStart, end + nCharStart, true, info.isModify);

        start = info.end;
        end = 0x10;
        if (end - start > 0)    // �ٻ滭���沿��
            pfn_draw_text(start + nCharStart, end + nCharStart, false, info.isModify);

        top += HeightChar;
        addr += 0x10;
        nCharStart += 0x10;
    }
}
static LRESULT CALLBACK HexView_Dialog_Draw_OnPaint(HWND hWnd, PHEXVIEW_DIALOG_STRUCT pArg)
{
    RECT rc;
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    GetClientRect(hWnd, &rc);
    const int cxClient = rc.right - rc.left;
    const int cyClient = rc.bottom - rc.top;
    HEXVIEW_COLOR& clr = pArg->clr;
    static HFONT hFont = HexView_CreateFontW(L"����", -16);

    HDC hdcMem = CreateCompatibleDC(ps.hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(ps.hdc, cxClient, cyClient);

    HPEN hPen = CreatePen(PS_SOLID, 1, clr.clrLine);
    HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
    HGDIOBJ hOldPen = SelectObject(hdcMem, hPen);
    HGDIOBJ hOldFont = SelectObject(hdcMem, hFont);

    COLORREF clrBk = SetBkColor(hdcMem, clr.clrBack);
    HBRUSH hbr = CreateSolidBrush(clr.clrBack);
    HGDIOBJ hOldBrush = SelectObject(hdcMem, hbr);
    Rectangle(hdcMem, 0, 0, cxClient, cyClient);
    //FillRect(hdcMem, &rc, hbr);


    HexView_Dialog_Draw_OnPaint_Draw(hdcMem, pArg, cxClient, cyClient);
    BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0, SRCCOPY);

    SetBkColor(hdcMem, clrBk);

    SelectObject(hdcMem, hOldFont);
    SelectObject(hdcMem, hOldPen);
    SelectObject(hdcMem, hOld);
    SelectObject(hdcMem, hOldBrush);

    DeleteObject(hbr);
    DeleteObject(hPen);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

    EndPaint(hWnd, &ps);
    return 0;
}

LRESULT CALLBACK HexView_Dialog_Draw_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PHEXVIEW_DIALOG_STRUCT pArg = (PHEXVIEW_DIALOG_STRUCT)GetPropW(hWnd, L"proc");
    if (!pArg)
        return DefWindowProcW(hWnd, message, wParam, lParam);

    WNDPROC oldProc = pArg->oldProc;
    switch (message)
    {
    case WM_PAINT:
        return HexView_Dialog_Draw_OnPaint(hWnd, pArg);
    case WM_DESTROY:
         SetWindowLongPtrW(pArg->hDraw, GWLP_USERDATA, (LONG_PTR)pArg->oldProc);
         return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
    default:
        return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
    }
    return 0;
}
HWND HexView_Dialog_CreateControl(LPCWSTR szClass, LPCWSTR title, DWORD styleEx, DWORD style, HWND hParent, INT_PTR id, int x, int y, int cx, int cy)
{
    HWND hWnd = CreateWindowExW(styleEx, szClass, title, style | WS_VISIBLE | WS_CHILD,
                                x, y, cx, cy, hParent, (HMENU)(LONG_PTR)id, 0, 0);

    static HFONT hFont = HexView_CreateFontW();
    SendMessageW(hWnd, WM_SETFONT, (WPARAM)hFont, 0);
    return hWnd;
}

// Ĭ��Ϊ΢���ź�, �����С -12, û����ʽ
// lfWeight = ����,  lfItalic = б��,  lfUnderline = �»���, lfStrikeOut = ɾ����
HFONT HexView_CreateFontW(const wchar_t* name, int size, BOOL lfWeight, BOOL lfItalic, BOOL lfUnderline, BOOL lfStrikeOut)
{
    LOGFONTW lf = { 0 };
    SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
    lf.lfHeight = size;
    if (lfWeight)
        lf.lfWeight = FW_BOLD;
    lf.lfItalic = lfItalic;
    lf.lfUnderline = lfUnderline;
    lf.lfStrikeOut = lfStrikeOut;
    lf.lfCharSet = GB2312_CHARSET;
    if (!name) name = L"΢���ź�";
    size_t len = wcslen(name) + 1;
    memcpy(lf.lfFaceName, name, len * sizeof(wchar_t));
    return CreateFontIndirectW(&lf);
}

// �ѶԻ�����е���������
void HexView_MoveDialog(HWND hWnd, HWND hParent, int width, int height)
{
    RECT rcParent;
    GetWindowRect(hParent, &rcParent);
    RECT rc;
    rc.left = rcParent.left + (rcParent.right - rcParent.left - width) / 2;
    rc.top = rcParent.top + (rcParent.bottom - rcParent.top - height) / 2;
    rc.right = rc.left + width;
    rc.bottom = rc.top + height;
    MoveWindow(hWnd, rc.left, rc.top, width, height, true);
}

// ����RGB��ɫ�Ƿ�����ɫ, �������true, ����Ӧ�ð���ɫ�ĳ���ɫ
bool HexView_IsRgbLight(COLORREF clr)
{
    BYTE r = GetRValue(clr);
    BYTE g = GetGValue(clr);
    BYTE b = GetBValue(clr);
    return (((5 * g) + (2 * r) + b) > (8 * 128));
};

HEXVIEW_NAMESPACE_END
