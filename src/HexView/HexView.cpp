#include "HexView.h"
#include <CJumpBox.h>
#include <CSearchBox.h>
//#include "AsmView.h"

#include <WindowsX.h>
#include <CommDlg.h>
#include <shellapi.h>
#include <crtdbg.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>

#define IDT_TIMER     1

#define ID_HEX_COPY             1000    // ֱ�Ӹ���, Ctrl+C �Ľ��
#define ID_HEX_COPY_16          1001    // ����16����
#define ID_HEX_COPY_16_1        1002    // ����16����, ���ÿո����
#define ID_HEX_COPY_16_C        1003    // ����16����, ��C���Եĸ�ʽ, 0xFF, 
#define ID_HEX_COPY_16_ASM      1004    // ����16����, �û��ĸ�ʽ, 0FFh, 
#define ID_HEX_COPY_10          1005    // ����10����
#define ID_HEX_COPY_10_1        1006    // ����10����, �м�û���ַ��ָ�

#define ID_HEX_COPY2            1100    // ֱ�Ӹ���, Ctrl+C �Ľ��
#define ID_HEX_COPY2_16         1101    // ����16����
#define ID_HEX_COPY2_16_1       1102    // ����16����, ���ÿո����
#define ID_HEX_COPY2_16_C       1103    // ����16����, ��C���Եĸ�ʽ, 0xFF, 
#define ID_HEX_COPY2_16_ASM     1104    // ����16����, �û��ĸ�ʽ, 0FFh, 
#define ID_HEX_COPY2_10         1105    // ����10����
#define ID_HEX_COPY2_10_1       1106    // ����10����, �м�û���ַ��ָ�

#define ID_HEX_SELALL           1200    // ȫѡ Ctrl+A
#define ID_HEX_SEARCH           1201    // ���� Ctrl+F
#define ID_HEX_NEXT             1202    // ������һ�� N
#define ID_HEX_PREV             1203    // ������һ�� P

#define ID_HEX_JMP              1300    // ��ת Ctrl+G
#define ID_HEX_ASM              1301    // ��ת����ര�� Ctrl+Q

#define NUMBEROF_CHARS_IN_FIRST_COLUMN_64BIT    1 + 18 + 2  // ���Ӱ����ߵ�ַ�ľ���, 18��ʾ18���ַ�
#define NUMBEROF_CHARS_IN_FIRST_COLUMN_32BIT    1 + 10 + 2  // �����32λ��ַ, 10���ַ�


BOOLEAN HexView_SelChanged(PHEXVIEW HexView, HWND hWnd);
void HexView_PopupMenu(PHEXVIEW HexView, HWND hWnd);
void HexView_SelAll(PHEXVIEW HexView, HWND hWnd);
BOOLEAN HexView_Copy(PHEXVIEW HexView, HWND hWnd, int fmt);
void HexView_Search(PHEXVIEW HexView, HWND hWnd);
void _search_msgbox(PHEXVIEW HexView, HWND hWnd, LPCWSTR text, SIZE_T start);
void HexView_Search_Next(PHEXVIEW HexView, HWND hWnd);
void HexView_Search_Prev(PHEXVIEW HexView, HWND hWnd);
void HexView_Jmp_pos(PHEXVIEW HexView, HWND hWnd, SIZE_T start, SIZE_T end);
void HexView_Jmp(PHEXVIEW HexView, HWND hWnd);
void HexView_Asm(PHEXVIEW HexView, HWND hWnd);


typedef struct HEXVIEW_DATA_STRUCT
{
    CSearchBox  search;
    CJumpBox    jmp;
    std::vector<BYTE> arr;
    HEXVIEW_DATA_STRUCT()
    {
        search.SetSearchMode(SEARCH_MODE_HEX);
        search.SetCaption(L"����");
        search.SetTips(L"");

        jmp.SetCaption(L"��ת��...");
        const LPCWSTR pszRadio1 = L"�ļ���ʼ(&B)";
        const LPCWSTR pszRadio2 = L"����λ��";
        const LPCWSTR pszRadio3 = L"����λ������";
        const LPCWSTR pszRadio4 = L"�ļ���β(&E)";
        jmp.SetRadioText(JUMPBOX_MODE_START, pszRadio1);
        jmp.SetRadioText(JUMPBOX_MODE_NOW, pszRadio2);
        jmp.SetRadioText(JUMPBOX_MODE_NOW_PREV, pszRadio3);
        jmp.SetRadioText(JUMPBOX_MODE_END, pszRadio4);
    }
    ~HEXVIEW_DATA_STRUCT()
    {

    }


    inline void Release()
    {

    }

}*PHEXVIEW_DATA_STRUCT;


inline LRESULT HexView_Wparam_InvalidateRect(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( wParam )
        InvalidateRect(hWnd, NULL, FALSE);
    return 0;
}


LRESULT HexView_SetExtendStyle(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetExtendStyle(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetItemCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetItemCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetColumnCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetColumnCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);




LRESULT HexView_SetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetBkColor(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetBkColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetBkColorSel(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetLineColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetLineColor(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetModifyTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetModifyTextColor(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetModifyTextColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetModifyTextColorSel(PHEXVIEW HexView, HWND hWnd);

LRESULT HexView_SetAddrTextColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetAddrTextColorSel(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetCharTextSelColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetCharTextSelColor(PHEXVIEW HexView, HWND hWnd);

LRESULT HexView_SetColorText1(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetColorText1(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetColorText2(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetColorText2(PHEXVIEW HexView, HWND hWnd);

LRESULT HexView_SetColorTextSel1(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetColorTextSel1(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_SetColorTextSel2(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetColorTextSel2(PHEXVIEW HexView, HWND hWnd);

LRESULT HexView_SetDarkMode(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetDarkMode(PHEXVIEW HexView, HWND hWnd);
LRESULT HexView_GetColor(PHEXVIEW HexView, PHEXVIEW_COLOR pClr);
LRESULT HexView_SetColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, PHEXVIEW_COLOR pClr);

void HexView_SwitchDarkMode(PHEXVIEW HexView, HWND hWnd, BOOL isDraw);


LRESULT HexView_OnCreate(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnSetFont(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnTimer(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnCommand(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnRButtonDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnLButtonDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnLButtonUp(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnMouseMove(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnChar(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnKeyDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);

LRESULT HexView_OnNcPaint(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnPaint(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnSetFocus(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnKillFocus(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnVScroll(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnHScroll(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnSize(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnMouseWheel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_OnDestroy(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);



LRESULT
HexView_SendNotify(
    _In_ HWND hWnd,
    _In_ UINT Code,
    _In_ LPNMHDR NmHdr
    )
{
    PHEXVIEW HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, 0);
    NmHdr->hwndFrom = hWnd;
    NmHdr->code = Code;
    NmHdr->idFrom = (UINT_PTR)GetWindowLongPtrW(hWnd, GWLP_ID);
    HWND HParent = GetParent(hWnd);

    if (HexView && HexView->pfnNotify)
        return HexView->pfnNotify(HParent, WM_NOTIFY, (WPARAM)NmHdr->idFrom, (LPARAM)NmHdr);

    return SendMessageW(HParent, WM_NOTIFY, (WPARAM)NmHdr->idFrom, (LPARAM)NmHdr);
}


// ��ȡѡ���ı�, ���ؿ������������ĳߴ�
// HexView = �������
// buf = ������, Ϊ0�򷵻ػ�������Ҫ�ĳߴ�
// bufSize = �������ߴ�, Ϊ0�򷵻ػ�������Ҫ�ĳߴ�
// flags = ���Ƶı�־, HVCPY_ ��ͷ�ĳ���
int HexView_GetSelText(PHEXVIEW HexView, HWND hWnd, LPWSTR buf, int bufSize, int flags)
{
    NMHVDISPINFO DispInfo = { 0 };
    const BOOLEAN isHex = (flags & HVCPY_HEX10) == 0;
    const BOOLEAN isAddress = (flags & HVCPY_ADDRESS ) == HVCPY_ADDRESS;
    const BOOLEAN isChar = (flags & HVCPY_CHAR ) == HVCPY_CHAR;
    const BOOLEAN isAddress64 = ( HexView->ExStyle & HVS_ADDRESS64 ) == HVS_ADDRESS64;
    const int copyMode = ( flags & 0xFF00 );

    // �Ƿ��л���, Ϊ��Ļ�������Ҫ�ӻ��з�, Ϊ�ٵĻ����ǲ���Ҫ�ָ���, Ҳ����Ҫ���з�
    // ����ģʽ����10/16���Ʋ��ָ�, �����п�����ַ�����ַ�, �����л���
    const BOOLEAN isWrap = (copyMode != HVCPY_HEX_1 && copyMode != HVCPY_HEX10_1) || (isAddress || isChar);

    BYTERANGE sel = { 0 };
    HexView_GetSel(HexView, hWnd, 0, (LPARAM)&sel);
    int selCount = (int)(sel.Max - sel.Min);
    if ( selCount <= 0 )
        return 0;   // û��ѡ���κ�����, û��ѡ�оͲ���Ҫ������, ��д���κ��ֽ�

    int allocSize = 0;  // �ܹ���Ҫ�ĳߴ�
    int hexSize = 0;    // 16���Ʋ�����Ҫ�ĳߴ�
    int addrSize = 0;   // ��ַ��Ҫ�ĳߴ�
    int charSize = 0;   // �ұ��ַ���Ҫ�ĳߴ�

    const int first_line = (int)( sel.Min ) / HexView->ColumnCount;
    const int final_line = (int)( sel.Max ) / HexView->ColumnCount - ( sel.Max % HexView->ColumnCount == 0 ? 1 : 0 );
    const int lineCount = final_line - first_line + 1;  // һ��������

    
    LPCWSTR fmt_kg = L"  ";
    switch ( copyMode )
    {
    case HVCPY_HEX_1:   // ����16����, ���ÿո�ָ�
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�) ÿ���ֽ�ռ�óߴ� = 2
        hexSize = lineCount * ( HexView->ColumnCount * 2 );
        break;
    case HVCPY_HEX_C:   // ����16����, ��C���Եĸ�ʽ, 0xFF, 
        // һ���ֽڱ��4���ַ�, ���϶��źͿո�, 0xff ��� "0xFF, "
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�) ÿ���ֽ�ռ�óߴ� = 6
        hexSize = lineCount * ( HexView->ColumnCount * 6 );
        fmt_kg = L"      ";
        break;
    case HVCPY_HEX_ASM: // ����16����, �û��ĸ�ʽ, 0FFh, 
        // һ���ֽڱ��4���ַ�, ���϶��źͿո�, 0xff ��� "0FFh, "
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�) ÿ���ֽ�ռ�óߴ� = 6
        hexSize = lineCount * ( HexView->ColumnCount * 6 );
        fmt_kg = L"      ";
        break;
    case HVCPY_HEX10_1: // ����10����, �ֽ�û���ַ��ָ�
        // һ���ֽڱ��3���ַ�, û�ж���û�пո�, һ���ֽ����3���ַ�, �������
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�) ÿ���ֽ�ռ�óߴ� = 3
        hexSize = lineCount * ( HexView->ColumnCount * 3 );
        fmt_kg = L" ";
        break;
    default:
        // û��ָ����ʽ, �Ͱ�16/10���Ƽ���
        // 16���Ʋ�����Ҫ�ĳߴ�, 16����ÿ���ֽ�ռ��3���ַ�, 10����ռ��4���ַ�
        // 16������� ff, 10������� 255, ���Ͽո����3/4���ַ�
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�)
        hexSize = lineCount * ( HexView->ColumnCount * ( isHex ? 3 : 4 ) );
        fmt_kg = isHex ? L"   " : L"    ";
        break;
    }

    if ( isAddress )
    {
        // ��ַ������Ҫ�ĳߴ�, 64λ��ַռ��18���ַ�, 32λ��ַռ��10���ַ�, ���������ո�
        // ���� * (ÿ�е��ַ��� * ÿ���ֽ�ռ�óߴ�)
        addrSize = lineCount * ( isAddress64 ? 20 : 12 );
    }

    if ( isChar )
    {
        // �ַ�������Ҫ�ĳߴ�, �����о�ռ�ö��ٸ��ַ�, �ټ�һ���ո�
        // ���� * (���� + �ո�)
        charSize = lineCount * ( HexView->ColumnCount + 1 );
    }

    // �ܳߴ� = ��ַ�ߴ� + 16���Ƴߴ� + �ַ��ߴ� + ÿ�еĻ��з�
    allocSize = addrSize + hexSize + charSize + (lineCount * 2);

    if ( !buf || bufSize <= 0 )
        return allocSize + 1;   // ��һ��������־


    WORD* buf_value = 0;    // ÿ�е�ֵ, �ж����л��������ж��
    int index_value = 0;    // ÿ��ѭ������0��ʼ, ѭ������������
    if ( charSize )
    {
        buf_value = (WORD*)malloc(HexView->ColumnCount * sizeof(WORD));
        memset(buf_value, 0, HexView->ColumnCount * sizeof(WORD));
    }

    // ��ȡ����ֵ, ÿһ��ѭ��ȥȡ
    const LPCWSTR fmt_addr = isAddress64 ? L"0x%016llX  " : L"0x%08X  ";
    const LPCWSTR fmt_hex = isHex ? L"%02X " : L"% 3d ";
    int offset_hex = 0;
    wchar_t buffer[32];

    auto pfn_append = [&](LPCWSTR vl, int len)
    {
        if ( len < 0 )
            return; // ����Ϊ0�Ͳ���Ҫ����

        // ���������� - �Ѿ�д��ĳ��� = ʣ�೤��
        int len1 = bufSize - offset_hex;

        if ( len > len1 )
        {
            // ʣ�೤�Ȳ�����, ֻд��һ����
            int writeLen = len1 - len - 1;
            if ( writeLen > 0 )
            {
                wmemcpy(&buf[offset_hex], vl, writeLen);
                offset_hex += writeLen;
                buf[offset_hex] = L'\0';
            }
            throw 1;
        }

        // �ߵ�������ǻ������㹻д��

        wmemcpy(&buf[offset_hex], vl, len);
        offset_hex += len;
        buf[offset_hex] = L'\0';
    };
    auto pfn_push_back = [&](wchar_t ch)
    {
        if( offset_hex + 1 >= bufSize )
            throw 2; // ����������, ����д��
        buf[offset_hex++] = ch;
        buf[offset_hex] = L'\0';
    };

    // �����ڴ��Ƿ�����, ���˾�Ӧ���˳�ѭ��
    auto pfn_add_format = [&](LPCWSTR fmt, ULONG64 vl)
    {
        int len = swprintf_s(buffer, fmt, vl);
        pfn_append(buffer, len);
    };

    auto pfn_address = [&](int i)
    {
        if ( !addrSize ) return;
        
        // д���ַ
        DispInfo.Item.Mask = HVIF_ADDRESS;
        DispInfo.Item.NumberOfItem = (SIZE_T)( i * HexView->ColumnCount );
        HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);

        pfn_add_format(fmt_addr, DispInfo.Item.Address);
    };

    auto pfn_hex = [&](int i)
    {
        index_value = 0;
        for ( int n = 0; n < HexView->ColumnCount; n++ )
        {
            const int index = i * HexView->ColumnCount + n;
            if ( index < (int)(DWORD)sel.Min || index >= (int)(DWORD)sel.Max )
            {
                // �ⲿ�����ո�
                if ( isWrap )   // ����Ǹ��Ʋ��ָ��ľͲ���Ҫ�ӿո�
                    pfn_add_format(fmt_kg, 0);
                if ( buf_value )
                    buf_value[index_value++] = 0xffff;
            }
            else
            {
                // ѡ�������, ��Ҫת���ɶ�Ӧ����
                DispInfo.Item.Mask = HVIF_BYTE;
                DispInfo.Item.State = 0;
                DispInfo.Item.NumberOfItem = index;
                DispInfo.Item.Address = 0;
                DispInfo.Item.Value = 0;
                HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);
                if ( buf_value )
                    buf_value[index_value++] = DispInfo.Item.Value;

                int len = 0;
                switch ( copyMode )
                {
                case HVCPY_HEX_1:   // ����16����, ���ÿո�ָ�
                    pfn_add_format(L"%02X", DispInfo.Item.Value);       // �������ʽ����, "FF"
                    break;
                case HVCPY_HEX_C:   // ����16����, ��C���Եĸ�ʽ, 0xFF, 
                    // һ���ֽڱ��4���ַ�, ���϶��źͿո�, 0xff ��� "0xFF, "
                    pfn_add_format(L"0x%02X, ", DispInfo.Item.Value);   // �������ʽ����, "0xFF, "
                    break;
                case HVCPY_HEX_ASM: // ����16����, �û��ĸ�ʽ, 0FFh, 
                    // һ���ֽڱ��4���ַ�, ���϶��źͿո�, 0xff ��� "0FFh, "
                    pfn_add_format(L"0%02Xh, ", DispInfo.Item.Value);   // �������ʽ����, "0FFh, "
                    break;
                case HVCPY_HEX10_1: // ����10����, �ֽ�û���ַ��ָ�
                    pfn_add_format(L"%u", DispInfo.Item.Value);         // �������ʽ����, ֱ�Ӽ�, ���ÿո�ָ�
                    break;
                default:
                {
                    if ( isHex )
                    {
                        pfn_add_format(fmt_hex, DispInfo.Item.Value);
                    }
                    else
                    {
                        // 10������Ҫ�Լ�תһ��
                        len = swprintf_s(buffer, L"%u", DispInfo.Item.Value);
                        for ( int i = 0; i < 3 - len; i++ )
                            pfn_push_back(L' ');    // ����3λ�Ĳ��ո�

                        pfn_append(buffer, len);    // �ո�������ֵ�϶���3λ
                        pfn_push_back(L' ');        // �����ٲ����ո�
                    }
                    break;
                }
                }


            }
        }

    };
    auto pfn_char = [&]()
    {
        // buf_value ��ֵ�ͱ�ʾҪд���ұߵ��ַ�, û��ֵ�Ͳ���Ҫ
        // ����ֵ�ұ���һ���ո�, �������Ҫд�ұߵ��ַ�, �ǾͰ���ߵĿո�ȥ��
        if ( !buf_value  )
        {
            if ( isWrap )
                buf[--offset_hex] = L'\0';  // ȥ�����һ���ո�
            return;
        }
        
        index_value = 0;
        // �ȼ�һ���ո�, ����ߵ�ֵ���������ո�, ֵĩβ��һ���ո�, �����ټ�һ��
        pfn_push_back(L' ');

        for ( index_value = 0; index_value < HexView->ColumnCount; index_value++ )
        {
            int vl = buf_value[index_value];

            if ( vl == 0xffff )
            {
                pfn_push_back(L' ');
            }
            else if ( isprint(vl) )
            {
                pfn_add_format(L"%c", vl);
            }
            else
            {
                pfn_push_back(L'.');
            }

        }

    };

    try
    {
        for ( int i = first_line; i <= final_line; i++ )
        {
            pfn_address(i);     // д����ߵĵ�ַ, �������Ҫ�Ͳ�д��

            pfn_hex(i);         // д���м��16����ֵ

            pfn_char();         // д���ұߵ��ַ�ֵ

            // һ��д����, ���ϻ���, ���ӷָ��ľͲ��ӻ��з�
            if ( isWrap )
            {
                pfn_push_back(L'\r');
                pfn_push_back(L'\n');
            }
        }

    }
    catch (...)
    {
        // �ߵ���������ڴ�д����, ������β������
        //__debugbreak();
    }

    if ( buf_value )
        free(buf_value);

    return offset_hex;
}

// �滭��ߵĵ�ַ
void HexView_DrawAddress(HDC hdc, PHEXVIEW HexView, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[32]; // ���ֽ�ת���ַ��õĻ�����
    SetTextColor(hdc, HexView->clr.clrTextAddress);

    const LPCWSTR fmt = ( HexView->ExStyle & HVS_ADDRESS64 ) ? L"0x%016I64X" : L"0x%08X";
    StringCchPrintfW(Buffer, _countof(Buffer), fmt, DispInfo->Item.Address);

    int ShiftPosX = -( HexView->WidthChar * HexView->HscrollPos ) + HexView->WidthChar;
    TextOutW(hdc, ShiftPosX, top, (PCWSTR)Buffer, (int)wcslen(Buffer));
}

// �滭�м��16����ֵ, ���������ʽ�����滭ʲô��ʽ, 1/2/4/8 �ֽ�, ����, ˫����, �з����޷��ŵȸ�ʽ
void HexView_DrawHexValue(HDC hdc, PHEXVIEW HexView, int Position1, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[100];    // ת����ֵ�Ļ�����, 100���ֽ��㹻��, ������˫���ȸ��㶼�������

    StringCchPrintfW(Buffer, _countof(Buffer), L"%02X", DispInfo->Item.Value);
    TextOutW(hdc, Position1, top, (PCWSTR)Buffer, 2);

}

// �滭�ұߵ��ַ�
void HexView_DrawCharValue(HDC hdc, PHEXVIEW HexView, int Position2, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[32]; // ���ֽ�ת���ַ��õĻ�����
    if ( isprint(DispInfo->Item.Value) )
    {
        StringCchPrintfW(Buffer, _countof(Buffer), L"%c", DispInfo->Item.Value);
    }
    else
    {
        wcscpy_s(Buffer, _countof(Buffer), L".");
    }

    TextOutW(hdc, Position2, top, (PCWSTR)Buffer, 1);
}

VOID
HexView_DrawLine(
    _In_ HWND hWnd,
    _In_ HDC hdcMem,
    _In_ PHEXVIEW HexView,
    _In_ int NumberOfLine,
    int top
    )
{
    RECT rc = {0};

    //
    // Clean hdcMem
    //

    rc.right = HexView->WidthView;
    rc.bottom = HexView->HeightChar;
    ExtTextOutW(hdcMem, 0, top, ETO_OPAQUE, &rc, NULL, 0, NULL);

    if ( ( HexView->VscrollPos + NumberOfLine ) >= HexView->TotalLines )
        return;
    

    NMHVDISPINFO DispInfo = {0};
    wchar_t Buffer[32] = { 0 };
    int Position1, Position2;
    SIZE_T SelectionStart, SelectionEnd;
    SIZE_T i, NumberOfItem;
    COLORREF clrBk = GetBkColor(hdcMem);

    //
    // Address column
    //


    NumberOfItem = (HexView->VscrollPos + NumberOfLine) * HexView->ColumnCount;

    DispInfo.Item.Mask = HVIF_ADDRESS;
    DispInfo.Item.NumberOfItem = NumberOfItem;
    HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);


    MoveToEx(hdcMem, HexView->Line1 - HexView->WidthChar, 0, 0);
    LineTo(hdcMem, HexView->Line1 - HexView->WidthChar, HexView->HeightChar);

    MoveToEx(hdcMem, HexView->Line2 - HexView->WidthChar, 0, 0);
    LineTo(hdcMem, HexView->Line2 - HexView->WidthChar, HexView->HeightChar);

    // �滭��ߵĵ�ַ
    HexView_DrawAddress(hdcMem, HexView, &DispInfo, top);

    //
    // DATA and VALUE columns
    //

    Position1 = HexView->Line1;
    Position2 = HexView->Line2;

    SelectionStart = min(HexView->SelectionStart, HexView->SelectionEnd);
    SelectionEnd = max(HexView->SelectionStart, HexView->SelectionEnd);

    for (i = NumberOfItem; i < NumberOfItem + HexView->ColumnCount && i < HexView->TotalItems; i++)
    {

        DispInfo.Item.Mask = HVIF_BYTE;
        DispInfo.Item.State = 0;
        DispInfo.Item.NumberOfItem = i;
        DispInfo.Item.Address = 0;
        DispInfo.Item.Value = 0;
        HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);

        BOOLEAN isSel = ( HexView->Flags & HVF_SELECTED ) && ( i >= SelectionStart && i <= SelectionEnd );
        if ( isSel )
        {
            SetBkColor(hdcMem, HexView->clr.clrBackSel);

            if (i != SelectionEnd && i != NumberOfItem + ( HexView->ColumnCount - 1))
            {
                // �������������16����ֵ֮�����һС�οհ�

                rc.top = 0;
                rc.bottom = HexView->HeightView;
                rc.left = Position1 + HexView->WidthChar * 2;
                rc.right = rc.left + HexView->WidthChar;
                ExtTextOutW(hdcMem, 0, top, ETO_OPAQUE, &rc, NULL, 0, NULL);
            }
            // ѡ��ʹ�������ı���ɫ
            const COLORREF clrText = ( DispInfo.Item.State & HVIS_MODIFIED ) ? HexView->clr.clrModifyTextSel :
                ( ( i % 2 == 0 ) ? HexView->clr.clrTextSel1 : HexView->clr.clrTextSel2 );
            SetTextColor(hdcMem, clrText);
        }
        else
        {
            SetBkColor(hdcMem, HexView->clr.clrBack);
            const COLORREF clrText = ( DispInfo.Item.State & HVIS_MODIFIED ) ? HexView->clr.clrModifyText :
                ( ( i % 2 == 0 ) ? HexView->clr.clrText1 : HexView->clr.clrText2 );
            SetTextColor(hdcMem, clrText);
        }

        // �滭�м��16����ֵ, ��Ҫ�ĳ��з���/�޷���, ���ٸ��ֽ���ʾ, ���������
        HexView_DrawHexValue(hdcMem, HexView, Position1, &DispInfo, top);

        // �滭�ұߵ��ַ�
        SetTextColor(hdcMem, isSel ? HexView->clr.clrTextSelChar : HexView->clr.clrTextAddress);
        HexView_DrawCharValue(hdcMem, HexView, Position2, &DispInfo, top);


        SetBkColor(hdcMem, clrBk);

        Position1 = Position1 + HexView->WidthChar * 3;
        Position2 = Position2 + HexView->WidthChar;
    }
}


VOID
HexView_Paint(
    _In_ HWND hWnd,
    _In_ HDC hdc,
    _In_ PHEXVIEW HexView
    )
{
    HDC hdcMem;
    HBITMAP hbmMem;
    HANDLE hOld;
    HANDLE hOldFont;
    HANDLE hOldPen;
    COLORREF clrBk;
    int NumberOfLine;
    HPEN hPen;


    hdcMem = CreateCompatibleDC(hdc);
    hbmMem = CreateCompatibleBitmap(hdc, HexView->WidthView, HexView->HeightChar);

    hPen = CreatePen(PS_SOLID, 1, HexView->clr.clrLine);
    hOld = SelectObject(hdcMem, hbmMem);
    hOldPen = SelectObject(hdcMem, hPen);
    hOldFont = SelectObject(hdcMem, HexView->hFont);

    clrBk = SetBkColor(hdcMem, HexView->clr.clrBack);
    int top = 0;

    for (NumberOfLine = 0; NumberOfLine <= HexView->VisibleLines; NumberOfLine++)
    {
        HexView_DrawLine(hWnd, hdcMem, HexView, NumberOfLine, top);
        //top += HexView->HeightChar;
        BitBlt(hdc, 0, HexView->HeightChar * NumberOfLine, HexView->WidthView, HexView->HeightChar, hdcMem, 0, 0, SRCCOPY);
    }




    SetBkColor(hdcMem, clrBk);

    SelectObject(hdcMem, hOldFont);
    SelectObject(hdcMem, hOldPen);
    SelectObject(hdcMem, hOld);

    DeleteObject(hPen);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}

_Check_return_
BOOL
HexView_PinToBottom(
    _Inout_ PHEXVIEW HexView
    )
{
    BOOL IsOk = FALSE;
    LONG_PTR VisibleLines;
    int VisibleChars;

    VisibleLines = min(HexView->VisibleLines, HexView->TotalLines);
    VisibleChars = min(HexView->VisibleChars, HexView->LongestLine);

    if (HexView->VscrollPos + VisibleLines > HexView->TotalLines) {

        HexView->VscrollPos = HexView->TotalLines - VisibleLines;

        IsOk = TRUE;
    }

    if (HexView->HscrollPos + VisibleChars > HexView->LongestLine) {

        int HscrollPos = HexView->LongestLine - VisibleChars;

        HexView->Line1 -= HexView->WidthChar * (HscrollPos - HexView->HscrollPos);
        HexView->Line2 -= HexView->WidthChar * (HscrollPos - HexView->HscrollPos);

        HexView->HscrollPos = HscrollPos;

        IsOk = TRUE;
    }

    return IsOk;
}

_Check_return_
LONG_PTR
HexView_GetTrackPos(
    _In_ HWND hWnd,
    _In_ PHEXVIEW HexView,
    _In_ int nBar
    )
{
    SCROLLINFO si = {0};

    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_TRACKPOS | SIF_PAGE;

    GetScrollInfo(hWnd, nBar, &si);

    if (nBar == SB_VERT) {

        if (HexView->VscrollMax > MAXLONG) {

            if (si.nTrackPos == (int)(MAXSHORT - si.nPage + 1)) {

                return HexView->VscrollMax - si.nPage + 1;
            }

            return (HexView->VscrollMax / MAXSHORT) * si.nTrackPos;
        }
    }

    return si.nTrackPos;
}

VOID
HexView_SetScrollInfo(
    _In_ HWND hWnd,
    _In_ PHEXVIEW HexView
    )
{
    SCROLLINFO si = {0};

    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_POS | SIF_PAGE | SIF_RANGE;

    if (HexView->VscrollMax <= MAXLONG) {

        si.nPos  = (int)HexView->VscrollPos;
        si.nPage = (UINT)HexView->VisibleLines;
        si.nMin  = 0;
        si.nMax  = (int)HexView->VscrollMax;
    }
    else {

        si.nPos  = (int)(HexView->VscrollPos / (HexView->VscrollMax / MAXSHORT));
        si.nPage = (UINT)HexView->VisibleLines;
        si.nMin  = 0;
        si.nMax  = MAXSHORT;
    }

    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

    si.nPos  = HexView->HscrollPos;
    si.nPage = (UINT)HexView->VisibleChars;
    si.nMin  = 0;
    si.nMax  = HexView->HscrollMax;

    SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
}

VOID
HexView_SetCaret(
    _In_ HWND hWnd,
    _Inout_ PHEXVIEW HexView
    )

/*++

Note:

    Hiding is cumulative.
    If your application calls HideCaret five times in a row,
    it must also call ShowCaret five times before the caret is displayed.
    So we need IsCaretVisible in order to hide the caret only once.

--*/

{
    LONG_PTR NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
    int NumberOfItemInLine = (int)(HexView->NumberOfItem % HexView->ColumnCount );

    if (HexView->TotalItems &&
        NumberOfLine >= HexView->VscrollPos &&
        NumberOfLine <= HexView->VscrollPos + HexView->VisibleLines)
    {
        switch (HexView->ActiveColumn)
        {
        case COLUMN_DATA:

            SetCaretPos(HexView->Line1 + (HexView->WidthChar * ((NumberOfItemInLine * 3) + HexView->PositionInItem)),
                        (int)(NumberOfLine - HexView->VscrollPos) * HexView->HeightChar);
            break;

        case COLUMN_VALUE:

            SetCaretPos(HexView->Line2 + (HexView->WidthChar * NumberOfItemInLine),
                        (int)(NumberOfLine - HexView->VscrollPos) * HexView->HeightChar);
            break;
        }

        ShowCaret(hWnd);
        HexView->Flags |= HVF_CARETVISIBLE;
    }
    else if (HexView->Flags & HVF_CARETVISIBLE) {

        HideCaret(hWnd);
        HexView->Flags &= ~HVF_CARETVISIBLE;
    }


}

VOID
HexView_SetPositionOfColumns(
    _Inout_ PHEXVIEW HexView
    )
{
    if (HexView->ExStyle & HVS_ADDRESS64)
    {

        HexView->Line1 = HexView->WidthChar * (NUMBEROF_CHARS_IN_FIRST_COLUMN_64BIT - HexView->HscrollPos);
        HexView->Line2 = HexView->WidthChar * ((NUMBEROF_CHARS_IN_FIRST_COLUMN_64BIT + HexView->ColumnSecond ) - HexView->HscrollPos);
    }
    else
    {

        HexView->Line1 = HexView->WidthChar * (NUMBEROF_CHARS_IN_FIRST_COLUMN_32BIT - HexView->HscrollPos);
        HexView->Line2 = HexView->WidthChar * ((NUMBEROF_CHARS_IN_FIRST_COLUMN_32BIT + HexView->ColumnSecond ) - HexView->HscrollPos);
    }
}

_Check_return_
BOOL
HexView_SetNumberOfItem(
    _Inout_ PHEXVIEW HexView,
    _In_ int xPos,
    _In_ int yPos
    )
{
    LONG_PTR NumberOfLine;

    _ASSERTE(yPos >= 0);

    NumberOfLine = yPos / HexView->HeightChar;

    if (NumberOfLine == HexView->VisibleLines) {
        NumberOfLine--;
    }

    NumberOfLine += HexView->VscrollPos;

    if (NumberOfLine >= 0 && NumberOfLine < HexView->TotalLines) {

        SIZE_T NumberOfItem = NumberOfLine * HexView->ColumnCount;
        LONG_PTR NumberOfItemsInLine = HexView->TotalItems - NumberOfItem;

        if (NumberOfItemsInLine > HexView->ColumnCount) {
            NumberOfItemsInLine = HexView->ColumnCount;
        }

        // ʮ���������λ��, С�����λ�þ��ǵ�ַ
        const int left1 = HexView->Line1 - HexView->WidthChar * 2;
        const int ritgt1 = HexView->Line1 + ( ( ((int)NumberOfItemsInLine) * 3 ) - 1 ) * HexView->WidthChar;

        // ����ж����ж������ʮ��������, ����ĳ��ڵ�ַ��Ҳ����ѡ��
        //if ((xPos > left1 ) && (xPos < (HexView->Line1 + ((NumberOfItemsInLine * 3) - 1) * HexView->WidthChar)))
        if ( xPos < ritgt1 )
        {
            if( xPos < left1 )
                xPos = left1 + HexView->WidthChar;

            xPos = (xPos - HexView->Line1) / HexView->WidthChar;

            HexView->NumberOfItem = NumberOfItem + ((xPos + 1) / 3);
            HexView->PositionInItem = ((xPos + 1) % 3) >> 1;
            HexView->ActiveColumn = COLUMN_DATA;
        }
        else if ((xPos > HexView->Line2 - HexView->WidthChar) )
                 //&& (xPos < (HexView->Line2 + NumberOfItemsInLine * HexView->WidthChar)))
        {
            //xPos = ( xPos - HexView->Line2 ) / HexView->WidthChar;
            const int max_right2 = HexView->Line2 + ((int)(NumberOfItemsInLine)) * HexView->WidthChar;

            if ( xPos > max_right2 )
                xPos = max_right2 - 1;

            xPos = ( xPos - HexView->Line2 ) / HexView->WidthChar;


            HexView->NumberOfItem = NumberOfItem + xPos;
            HexView->PositionInItem = 0;
            HexView->ActiveColumn = COLUMN_VALUE;
        }

        return TRUE;
    }

    return FALSE;
}


LRESULT HexView_OnCreate(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HexView = (PHEXVIEW)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(HEXVIEW));
    if ( !HexView )
    {
        return -1;
    }
    HexView->pBoxData = new HEXVIEW_DATA_STRUCT;
    SetWindowLongPtrW(hWnd, 0, (LONG_PTR)HexView);

    HexView->ActiveColumn = COLUMN_DATA;
    HexView->ColumnCount = 16;
    HexView->ColumnSecond = HexView->ColumnCount * 3 + 1;

    HexView_SwitchDarkMode(HexView, hWnd, false);

    SendMessageW(hWnd, WM_SETFONT, 0, 0);
    return 0;
}
LRESULT HexView_OnSetFont(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    TEXTMETRICW TextMetric;
    HANDLE hOldFont;

    if ( ( HexView->Flags & HVF_FONTCREATED ) && HexView->hFont )
    {
        DeleteObject(HexView->hFont);
        HexView->Flags &= ~HVF_FONTCREATED;
    }

    HexView->hFont = (HFONT)wParam;
    hdc = GetDC(hWnd);

    if ( !HexView->hFont )
    {
        LOGFONTW LogFont;
        //HFONT hFontCurDC = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
        //GetObjectW(hFontCurDC, sizeof(LOGFONTW), &LogFont);

        //LogFont.lfHeight = -13;
        LogFont.lfHeight = -15;
        LogFont.lfWidth = 0;
        LogFont.lfEscapement = 0;
        LogFont.lfOrientation = 0;
        //LogFont.lfWeight = FW_BOLD;
        LogFont.lfWeight = FW_NORMAL;
        LogFont.lfItalic = FALSE;
        LogFont.lfUnderline = FALSE;
        LogFont.lfStrikeOut = FALSE;
        LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
        LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        LogFont.lfQuality = DEFAULT_QUALITY;
        LogFont.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
        LogFont.lfCharSet = ANSI_CHARSET;

        //wcscpy_s(LogFont.lfFaceName, _countof(LogFont.lfFaceName), L"Courier New");
        wcscpy_s(LogFont.lfFaceName, _countof(LogFont.lfFaceName), L"����");

        HexView->hFont = CreateFontIndirectW(&LogFont);

        if ( HexView->hFont )
        {
            HexView->Flags |= HVF_FONTCREATED;
        }
        else
        {
            HexView->hFont = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);
        }
    }


    hOldFont = SelectObject(hdc, HexView->hFont);
    GetTextMetricsW(hdc, &TextMetric);
    SelectObject(hdc, hOldFont);

    ReleaseDC(hWnd, hdc);

    HexView->WidthChar = TextMetric.tmAveCharWidth;
    HexView->HeightChar = TextMetric.tmHeight;

    HexView->VisibleLines = HexView->HeightView / HexView->HeightChar;
    HexView->VisibleChars = HexView->WidthView / HexView->WidthChar;

    if ( hWnd == GetFocus() )
    {

        CreateCaret(hWnd, NULL, 1, HexView->HeightChar);
    }

    HexView_SetPositionOfColumns(HexView);

    HexView_SetScrollInfo(hWnd, HexView);
    HexView_SetCaret(hWnd, HexView);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
}
LRESULT HexView_OnTimer(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch ( wParam )
    {
    case IDT_TIMER:
    {
        if ( hWnd == GetCapture() )
        {

            RECT rc;
            POINT Point;
            LONG Position;

            GetClientRect(hWnd, &rc);
            GetCursorPos(&Point);
            ScreenToClient(hWnd, &Point);

            if ( Point.y < rc.top )
            {

                SendMessageW(hWnd, WM_VSCROLL, SB_LINEUP, -1);

                Position = MAKELPARAM(Point.x, 0);
                SendMessageW(hWnd, WM_MOUSEMOVE, 0, Position);
            }
            else if ( Point.y > rc.bottom )
            {

                SendMessageW(hWnd, WM_VSCROLL, SB_LINEDOWN, -1);

                Position = MAKELPARAM(Point.x, rc.bottom - HexView->WidthChar);
                SendMessageW(hWnd, WM_MOUSEMOVE, 0, Position);
            }
        }
        break;
    }
    default:
        break;
    }

    return 0;
}
LRESULT HexView_OnCommand(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    const int id = LOWORD(wParam);
    const int code = HIWORD(wParam);
    HWND hChild = (HWND)lParam;
    switch ( id )
    {
    case ID_HEX_COPY:           // ֱ�Ӹ���, Ctrl+C �Ľ��
    case ID_HEX_COPY_16:        // ����16����
        HexView_Copy(HexView, hWnd, HVCPY_DEF);
        break;
    case ID_HEX_COPY_16_1:      // ����16����, ���ÿո����
        HexView_Copy(HexView, hWnd, HVCPY_HEX_1);
        break;
    case ID_HEX_COPY_16_C:      // ����16����, ��C���Եĸ�ʽ, 0xFF, 
        HexView_Copy(HexView, hWnd, HVCPY_HEX_C);
        break;
    case ID_HEX_COPY_16_ASM:    // ����16����, �û��ĸ�ʽ, 0FFh, 
        HexView_Copy(HexView, hWnd, HVCPY_HEX_ASM);
        break;
    case ID_HEX_COPY_10:        // ����10����
        HexView_Copy(HexView, hWnd, HVCPY_HEX10);
        break;
    case ID_HEX_COPY_10_1:      // ����10����, �м�û���ַ��ָ�
        HexView_Copy(HexView, hWnd, HVCPY_HEX10_1);
        break;
    case ID_HEX_COPY2:          // ֱ�Ӹ���, Ctrl+C �Ľ��
    case ID_HEX_COPY2_16:       // ����16����
        HexView_Copy(HexView, hWnd, HVCPY_ALL);
        break;
    case ID_HEX_COPY2_16_1:     // ����16����, ���ÿո����
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_1);
        break;
    case ID_HEX_COPY2_16_C:     // ����16����, ��C���Եĸ�ʽ, 0xFF, 
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_C);
        break;
    case ID_HEX_COPY2_16_ASM:   // ����16����, �û��ĸ�ʽ, 0FFh, 
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_ASM);
        break;
    case ID_HEX_COPY2_10:       // ����10����
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX10);
        break;
    case ID_HEX_COPY2_10_1:     // ����10����, �м�û���ַ��ָ�
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX10_1);
        break;
    case ID_HEX_SELALL:         // ȫѡ Ctrl+A
        HexView_SelAll(HexView, hWnd);
        break;
    case ID_HEX_SEARCH:         // ���� Ctrl+F
        HexView_Search(HexView, hWnd);
        break;
    case ID_HEX_NEXT:           // ������һ�� N
        HexView_Search_Next(HexView, hWnd);
        break;
    case ID_HEX_PREV:           // ������һ�� P
        HexView_Search_Prev(HexView, hWnd);
        break;
    case ID_HEX_JMP:            // ��ת Ctrl+G
        HexView_Jmp(HexView, hWnd);
        break;
    case ID_HEX_ASM:            // ��ת����ര�� Ctrl+Q
        HexView_Asm(HexView, hWnd);
        break;
    default:
        break;
    }
    return 0;
}

LRESULT HexView_OnRButtonDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( HexView->TotalItems )
    {
        NMHDR NmHdr = { 0 };
        SendMessageW(hWnd, WM_SETFOCUS, 0, 0);
        LRESULT ret = HexView_SendNotify(hWnd, NM_RCLICK, &NmHdr);
        if ( ret ) return ret;

        HexView_PopupMenu(HexView, hWnd);
    }
    return 0;
}
LRESULT HexView_OnLButtonDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    if ( HexView_SetNumberOfItem(HexView, xPos, yPos) )
    {
        SIZE_T start = HexView->SelectionStart;
        SIZE_T end = HexView->SelectionEnd;
        HexView->SelectionStart = HexView->SelectionEnd = HexView->NumberOfItem;
        
        if ( HexView->Flags & HVF_SELECTED )
        {
            HexView->Flags &= ~HVF_SELECTED;
            HexView_SelChanged(HexView, hWnd);
            InvalidateRect(hWnd, NULL, FALSE);
        }


        HexView_SetCaret(hWnd, HexView);
        SetFocus(hWnd);

        SetCapture(hWnd);
        SetTimer(hWnd, IDT_TIMER, USER_TIMER_MINIMUM, (TIMERPROC)NULL);
    }

    return 0;
}
LRESULT HexView_OnLButtonUp(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( hWnd == GetCapture() )
    {
        KillTimer(hWnd, IDT_TIMER);
        ReleaseCapture();
    }

    return 0;
}
LRESULT HexView_OnMouseMove(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    GetClientRect(hWnd, &rc);

    if ( yPos < rc.top || yPos > rc.bottom )
    {
        return 0;
    }

    if ( hWnd == GetCapture() )
    {
        //xPos -= HexView->WidthChar;
        //if ( xPos < 0 )xPos = 0;
        if ( HexView_SetNumberOfItem(HexView, xPos, yPos) )
        {
            HexView->SelectionEnd = HexView->NumberOfItem;
            HexView->Flags |= HVF_SELECTED;
            HexView_SelChanged(HexView, hWnd);

            HexView_SetCaret(hWnd, HexView);
            InvalidateRect(hWnd, NULL, FALSE);
        }
    }

    return 0;
}
LRESULT HexView_OnChar(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( HexView->TotalItems && !( HexView->ExStyle & HVS_READONLY ) )
    {

        switch ( HexView->ActiveColumn )
        {

        case COLUMN_DATA:
        {
            if ( _istxdigit((wint_t)wParam) )
            {

                NMHVDISPINFO DispInfo = { 0 };
                NMHEXVIEW NmHexView = { 0 };
                TCHAR Buffer[4] = { 0 };
                BYTE Value;

                DispInfo.Item.Mask = HVIF_BYTE;
                DispInfo.Item.NumberOfItem = HexView->NumberOfItem;
                HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);

                Buffer[0] = (TCHAR)wParam;
                Value = (BYTE)wcstoul((PCWSTR)Buffer, 0, 16);

                if ( HexView->PositionInItem )
                {

                    DispInfo.Item.Value &= 0xf0;
                    DispInfo.Item.Value |= Value;
                }
                else
                {

                    DispInfo.Item.Value &= 0x0f;
                    DispInfo.Item.Value |= ( Value << 4 );
                }

                NmHexView.Item.NumberOfItem = HexView->NumberOfItem;
                NmHexView.Item.Value = DispInfo.Item.Value;
                HexView_SendNotify(hWnd, HVN_ITEMCHANGING, (LPNMHDR)&NmHexView);

                SendMessageW(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
            }
            break;
        }
        case COLUMN_VALUE:
        {
            if ( iswprint((wint_t)wParam) && wParam != VK_TAB )
            {

                NMHEXVIEW NmHexView = { 0 };

                NmHexView.Item.NumberOfItem = HexView->NumberOfItem;
                NmHexView.Item.Value = (BYTE)wParam;
                HexView_SendNotify(hWnd, HVN_ITEMCHANGING, (LPNMHDR)&NmHexView);

                SendMessageW(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
            }
            break;
        }
        }
    }

    return 0;
}



LRESULT HexView_OnKeyDown(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( HexView->TotalItems == 0 )
        return 0;
        
    BOOLEAN IsCtrlKeyDown = (GetKeyState(VK_CONTROL) & 0x8000) ? TRUE : FALSE;
    BOOLEAN IsShiftKeyDown = (GetKeyState(VK_SHIFT) & 0x8000) ? TRUE : FALSE;
    switch (wParam)
    {
    case 'C':
    {
        if ( !IsCtrlKeyDown )
            break;
        const int fmt = HVCPY_DEF;
        HexView_Copy(HexView, hWnd, fmt);
        break;
    }
    case 'A':
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_SelAll(HexView, hWnd);
        break;
    }
    case 'F':   // ����
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_Search(HexView, hWnd);
        break;
    }
    case VK_F3: // ������/��һ��
    {
        if ( IsCtrlKeyDown )
            break;
        if ( IsShiftKeyDown )
            HexView_Search_Prev(HexView, hWnd);
        else
            HexView_Search_Next(HexView, hWnd);
        return 0;
    }
    case 'G':   // ��ת
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_Jmp(HexView, hWnd);
        break;
    }
    case 'Q':   // ��ת����ര��
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_Asm(HexView, hWnd);
        break;
    }
    case VK_TAB:
    {
        switch (HexView->ActiveColumn)
        {
        case COLUMN_DATA:
            HexView->ActiveColumn = COLUMN_VALUE;
            break;
        case COLUMN_VALUE:
            HexView->ActiveColumn = COLUMN_DATA;
            break;
        }
        HexView->PositionInItem = 0;
        break;
    }
    case VK_LEFT:
    {
        if (IsCtrlKeyDown)
        {

            SendMessageW(hWnd, WM_HSCROLL, SB_LINELEFT, 0);
            break;
        }

        switch (HexView->ActiveColumn)
        {
        case COLUMN_DATA:
        {
            switch (HexView->PositionInItem)
            {
            case 0:
            {
                if (HexView->NumberOfItem != 0)
                {
                    LONG_PTR NumberOfLine;

                    HexView->PositionInItem = 1;
                    HexView->NumberOfItem--;

                    NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
                    if (NumberOfLine == HexView->VscrollPos - 1)
                    {
                        SendMessageW(hWnd, WM_VSCROLL, SB_LINEUP, 0);
                    }
                }
                break;
            }
            case 1:
            {
                HexView->PositionInItem = 0;
                break;
            }
            }
            break;
        }
        case COLUMN_VALUE:
        {
            if (HexView->NumberOfItem != 0)
            {
                LONG_PTR NumberOfLine;
                HexView->NumberOfItem--;

                NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
                if (NumberOfLine == HexView->VscrollPos - 1)
                {
                    SendMessageW(hWnd, WM_VSCROLL, SB_LINEUP, 0);
                }
            }
            break;
        }
        }
        break;
    }
    case VK_RIGHT:
    {
        if (IsCtrlKeyDown)
        {
            SendMessageW(hWnd, WM_HSCROLL, SB_LINERIGHT, 0);
            break;
        }

        switch (HexView->ActiveColumn)
        {
        case COLUMN_DATA:
        {
            switch (HexView->PositionInItem)
            {
            case 0:
            {
                HexView->PositionInItem = 1;
                break;
            }
            case 1:
            {
                if (HexView->NumberOfItem < HexView->TotalItems - 1)
                {
                    LONG_PTR NumberOfLine;

                    HexView->PositionInItem = 0;
                    HexView->NumberOfItem++;

                    NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
                    if (NumberOfLine == HexView->VscrollPos + HexView->VisibleLines)
                    {
                        SendMessageW(hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
                    }
                }
                break;
            }
            }
            break;
        }
        case COLUMN_VALUE:
        {
            if (HexView->NumberOfItem < HexView->TotalItems - 1)
            {
                LONG_PTR NumberOfLine;

                HexView->NumberOfItem++;
                NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;

                if (NumberOfLine == HexView->VscrollPos + HexView->VisibleLines)
                {
                    SendMessageW(hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
                }
            }
            break;
        }
        }
        break;
    }
    case VK_UP:
    {
        if (IsCtrlKeyDown)
        {
            SendMessageW(hWnd, WM_VSCROLL, SB_LINEUP, 0);
        }

        if (HexView->NumberOfItem >= (SIZE_T)HexView->ColumnCount )
        {
            LONG_PTR NumberOfLine;
            HexView->NumberOfItem -= HexView->ColumnCount;

            NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
            if (NumberOfLine == HexView->VscrollPos - 1)
            {
                SendMessageW(hWnd, WM_VSCROLL, SB_LINEUP, 0);
            }
        }
        break;
    }
    case VK_DOWN:
    {
        if (IsCtrlKeyDown)
        {
            SendMessageW(hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
        }

        if ((HexView->NumberOfItem + HexView->ColumnCount ) < HexView->TotalItems)
        {
            LONG_PTR NumberOfLine;
            HexView->NumberOfItem += HexView->ColumnCount;

            NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;
            if (NumberOfLine == HexView->VscrollPos + HexView->VisibleLines)
            {
                SendMessageW(hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
            }
        }
        break;
    }
    case VK_PRIOR:
    {
        if ((HexView->NumberOfItem - HexView->ColumnCount * HexView->VisibleLines) >= 0)
        {
            HexView->NumberOfItem -= HexView->ColumnCount * HexView->VisibleLines;
        }
        else
        {
            SIZE_T NumberOfLines = HexView->NumberOfItem / HexView->ColumnCount;
            HexView->NumberOfItem -= HexView->ColumnCount * NumberOfLines;
        }
        SendMessageW(hWnd, WM_VSCROLL, SB_PAGEUP, 0);
        break;
    }
    case VK_NEXT:
    {
        if ((HexView->NumberOfItem + HexView->ColumnCount * HexView->VisibleLines) < HexView->TotalItems)
        {
            HexView->NumberOfItem += HexView->ColumnCount * HexView->VisibleLines;
        }
        else
        {
            SIZE_T NumberOfItems = HexView->TotalItems - HexView->NumberOfItem - 1;
            SIZE_T NumberOfLines = NumberOfItems / HexView->ColumnCount;

            HexView->NumberOfItem += HexView->ColumnCount * NumberOfLines;
        }

        SendMessageW(hWnd, WM_VSCROLL, SB_PAGEDOWN, 0);
        break;
    }
    case VK_HOME:
    {
        if (IsCtrlKeyDown)
        {
            HexView->NumberOfItem = 0;
            HexView->PositionInItem = 0;

            SendMessageW(hWnd, WM_VSCROLL, SB_TOP, 0);
        }
        else
        {
            HexView->NumberOfItem &= ~0xf;
            HexView->PositionInItem = 0;

            if (HexView->ActiveColumn == COLUMN_DATA)
            {
                SendMessageW(hWnd, WM_HSCROLL, SB_LEFT, 0);
            }
        }
        break;
    }
    case VK_END:
    {
        if (IsCtrlKeyDown)
        {
            HexView->NumberOfItem = HexView->TotalItems - 1;
            HexView->PositionInItem = 0;

            SendMessageW(hWnd, WM_VSCROLL, SB_BOTTOM, 0);
        }
        else
        {
            HexView->NumberOfItem = (HexView->NumberOfItem & ~0xf) + 15;
            HexView->PositionInItem = 0;

            if (HexView->NumberOfItem >= HexView->TotalItems)
            {
                HexView->NumberOfItem = HexView->TotalItems - 1;
            }

            SendMessageW(hWnd, WM_HSCROLL, SB_RIGHT, 0);
        }
        break;
    }
    }

    //
    // if lParam == 0 then WM_KEYDOWN came from WM_CHAR
    // and we don't need to select text.
    //

    if ( IsShiftKeyDown && lParam)
    {

        if (HexView->PositionInItem || (HexView->SelectionStart != HexView->NumberOfItem))
        {
            HexView->SelectionEnd = HexView->NumberOfItem;
            HexView->Flags |= HVF_SELECTED;
            HexView_SelChanged(HexView, hWnd);
        }
        else
        {
            HexView->Flags &= ~HVF_SELECTED;
            HexView_SelChanged(HexView, hWnd);
        }
    }
    else if (!IsCtrlKeyDown && !(GetKeyState(VK_APPS) & 0x8000))
    {
        HexView->SelectionStart = HexView->SelectionEnd = HexView->NumberOfItem;
        HexView->Flags &= ~HVF_SELECTED;
        HexView_SelChanged(HexView, hWnd);
    }

    if (!(HexView->Flags & HVF_CARETVISIBLE))
    {
        LONG_PTR NumberOfLine = HexView->NumberOfItem / HexView->ColumnCount;

        if (NumberOfLine > HexView->TotalLines - HexView->VisibleLines)
        {
            HexView->VscrollPos = HexView->TotalLines - HexView->VisibleLines;
        }
        else
        {
            HexView->VscrollPos = NumberOfLine;
        }

        HexView_SetScrollInfo(hWnd, HexView);
    }

    HexView_SetCaret(hWnd, HexView);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
}
LRESULT HexView_OnNcPaint(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret = DefWindowProcW(hWnd, WM_NCPAINT, wParam, lParam);
    RECT rc;
    GetWindowRect(hWnd, &rc);
    const int cxScreen = rc.right - rc.left;
    const int cyScreen = rc.bottom - rc.top;
    HDC hdc = GetWindowDC(hWnd);
    HPEN hPen = CreatePen(PS_SOLID, 1, HexView->clr.clrLine);

    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, GetStockBrush(NULL_BRUSH));

    Rectangle(hdc, 0, 0, cxScreen, cyScreen);   // ֱ�ӻ�������DC��

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    ReleaseDC(hWnd, hdc);
    return ret;
}
LRESULT HexView_OnPaint(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    hdc = BeginPaint(hWnd, &ps);
    HexView_Paint(hWnd, hdc, HexView);
    EndPaint(hWnd, &ps);
    return 0;
}
LRESULT HexView_OnSetFocus(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    CreateCaret(hWnd, NULL, 1, HexView->HeightChar);

    if ( HexView->Flags & HVF_CARETVISIBLE )
    {
        NMHDR NmHdr = { 0 };

        HexView_SetCaret(hWnd, HexView);
        ShowCaret(hWnd);

        HexView_SendNotify(hWnd, NM_SETFOCUS, &NmHdr);
    }
    return 0;
}
LRESULT HexView_OnKillFocus(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( HexView->Flags & HVF_CARETVISIBLE )
    {
        HideCaret(hWnd);
    }

    DestroyCaret();
    return 0;
}
LRESULT HexView_OnVScroll(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LONG_PTR OldPos = HexView->VscrollPos;

    switch ( LOWORD(wParam) )
    {
    case SB_TOP:

        HexView->VscrollPos = 0;
        break;

    case SB_BOTTOM:

        HexView->VscrollPos = max(0, HexView->VscrollMax - HexView->VisibleLines + 1);
        break;

    case SB_LINEUP:

        HexView->VscrollPos = max(0, HexView->VscrollPos - 1);
        break;

    case SB_LINEDOWN:

        HexView->VscrollPos = min(HexView->VscrollPos + 1, max(0, HexView->VscrollMax - HexView->VisibleLines + 1));
        break;

    case SB_PAGEUP:

        HexView->VscrollPos = max(0, HexView->VscrollPos - HexView->VisibleLines);
        break;

    case SB_PAGEDOWN:

        HexView->VscrollPos = min(HexView->VscrollPos + HexView->VisibleLines, max(0, HexView->VscrollMax - HexView->VisibleLines + 1));
        break;

    case SB_THUMBTRACK:

        HexView->VscrollPos = HexView_GetTrackPos(hWnd, HexView, SB_VERT);
        break;
    }

    if ( OldPos != HexView->VscrollPos )
    {
        HexView_SetScrollInfo(hWnd, HexView);

        //
        // If lParam == -1 then WM_VSCROLL came from WM_TIMER
        // and we don't need to set the caret because it will be set in WM_MOUSEMOVE.
        //

        if ( -1 != lParam )
        {

            HexView_SetCaret(hWnd, HexView);
        }

        InvalidateRect(hWnd, NULL, FALSE);
    }

    return 0;
}
LRESULT HexView_OnHScroll(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int OldPos = HexView->HscrollPos;

    switch ( LOWORD(wParam) )
    {
    case SB_LEFT:

        HexView->HscrollPos = 0;
        break;

    case SB_RIGHT:

        HexView->HscrollPos = max(0, HexView->HscrollMax - HexView->VisibleChars + 1);
        break;

    case SB_LINELEFT:
    case SB_PAGELEFT:

        HexView->HscrollPos = max(0, HexView->HscrollPos - 1);
        break;

    case SB_LINERIGHT:
    case SB_PAGERIGHT:

        HexView->HscrollPos = min(HexView->HscrollPos + 1, max(0, HexView->HscrollMax - HexView->VisibleChars + 1));
        break;

    case SB_THUMBTRACK:

        HexView->HscrollPos = (int)HexView_GetTrackPos(hWnd, HexView, SB_HORZ);
        break;
    }

    if ( OldPos != HexView->HscrollPos )
    {
        HexView_SetPositionOfColumns(HexView);

        HexView_SetScrollInfo(hWnd, HexView);
        HexView_SetCaret(hWnd, HexView);

        InvalidateRect(hWnd, NULL, FALSE);
    }

    return 0;
}
LRESULT HexView_OnSize(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HexView->WidthView = LOWORD(lParam);
    HexView->HeightView = HIWORD(lParam);

    HexView->VisibleLines = HexView->HeightView / HexView->HeightChar;
    HexView->VisibleChars = HexView->WidthView / HexView->WidthChar;

    if ( HexView_PinToBottom(HexView) )
    {
        HexView_SetCaret(hWnd, HexView);

        InvalidateRect(hWnd, NULL, FALSE);
    }

    HexView_SetScrollInfo(hWnd, HexView);
    return 0;
}
LRESULT HexView_OnMouseWheel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    INT ScrollLines = 0;
    SHORT Delta;

    Delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

    SystemParametersInfoW(SPI_GETWHEELSCROLLLINES, 0, &ScrollLines, 0);

    if ( Delta > 0 )
    {
        HexView->VscrollPos = max(0, HexView->VscrollPos - ( Delta * ScrollLines ));
    }
    else if ( Delta < 0 )
    {
        HexView->VscrollPos = min(HexView->VscrollPos + ( -Delta * ScrollLines ), max(0, HexView->VscrollMax - HexView->VisibleLines + 1));
    }

    HexView_SetScrollInfo(hWnd, HexView);
    HexView_SetCaret(hWnd, HexView);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
}
LRESULT HexView_OnDestroy(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( HexView )
    {
        if ( HexView->Flags & HVF_FONTCREATED )
        {
            DeleteObject(HexView->hFont);
        }

        PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
        delete pBox;
        HeapFree(GetProcessHeap(), 0, HexView);
    }
    return 0;
}


// ������Ϣ�������������, ������������ռ��ڴ���

LRESULT HexView_SetExtendStyle(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    DWORD styleNew = (DWORD)lParam;
    DWORD oldStyle = HexView->ExStyle;
    BOOL isDarkModeOld = (oldStyle & HVS_DARMMODE) == HVS_DARMMODE;
    BOOL isDarkModeNew = (styleNew & HVS_DARMMODE) == HVS_DARMMODE;

    BOOL isOld64Addr = (oldStyle & HVS_ADDRESS64) == HVS_ADDRESS64;
    BOOL isNew64Addr = (styleNew & HVS_ADDRESS64) == HVS_ADDRESS64;
    HexView->ExStyle = styleNew;
    if (isDarkModeOld != isDarkModeNew)
        HexView_SwitchDarkMode(HexView, hWnd, false);
    if (isNew64Addr != isOld64Addr)
        HexView_SetPositionOfColumns(HexView);

    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);

    return oldStyle;
}
LRESULT HexView_GetExtendStyle(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return HexView->ExStyle;
}
LRESULT HexView_SetItemCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HexView->TotalItems = 0;
    HexView->TotalLines = 0;
    HexView->LongestLine = 0;

    if ( lParam )
    {
        HexView->TotalItems = (SIZE_T)lParam;
        HexView->TotalLines = HexView->TotalItems / HexView->ColumnCount;
        if ( HexView->TotalItems % HexView->ColumnCount )
        {
            HexView->TotalLines += 1;
        }

        const DWORD tmp = ( ( HexView->ExStyle & HVS_ADDRESS64 ) ? NUMBEROF_CHARS_IN_FIRST_COLUMN_64BIT : NUMBEROF_CHARS_IN_FIRST_COLUMN_32BIT );
        HexView->LongestLine = tmp + HexView->ColumnSecond + HexView->ColumnCount;
    }

    HexView->NumberOfItem = 0;
    HexView->PositionInItem = 0;

    HexView->SelectionStart = 0;
    HexView->SelectionEnd = 0;
    HexView->Flags &= ~HVF_SELECTED;
    HexView_SelChanged(HexView, hWnd);

    HexView->ActiveColumn = COLUMN_DATA;

    HexView->VscrollPos = 0;
    HexView->VscrollMax = max(HexView->TotalLines - 1, 0);
    HexView->HscrollPos = 0;
    HexView->HscrollMax = max(HexView->LongestLine - 1, 0);

    HexView_SetPositionOfColumns(HexView);

    HexView_SetScrollInfo(hWnd, HexView);
    HexView_SetCaret(hWnd, HexView);

    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return 1;
}
LRESULT HexView_GetItemCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return (LRESULT)HexView->TotalItems;
}
LRESULT HexView_SetSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( !lParam ) return 0;

    PBYTERANGE ByteRange = (PBYTERANGE)lParam;
    if ( ( ByteRange->Min >= 0 && ByteRange->Min < HexView->TotalItems ) &&
        ( ByteRange->Max >= 0 && ByteRange->Max <= HexView->TotalItems ) )
    {

        HexView->SelectionStart = ByteRange->Min;
        HexView->SelectionEnd = ByteRange->Max;

        if ( ByteRange->Min != ByteRange->Max )
        {
            HexView->SelectionEnd -= 1;
            HexView->Flags |= HVF_SELECTED;
        }
        else
        {
            HexView->Flags &= ~HVF_SELECTED;
        }
        HexView_SelChanged(HexView, hWnd);

        HexView->NumberOfItem = HexView->SelectionStart;
        HexView->PositionInItem = 0;

        HexView->VscrollPos = min((LONG_PTR)( HexView->NumberOfItem / HexView->ColumnCount ), max(0, HexView->VscrollMax - HexView->VisibleLines + 1));

        HexView_SetScrollInfo(hWnd, HexView);
        HexView_SetCaret(hWnd, HexView);

        HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
        return 1;
    }
    return 0;
}
LRESULT HexView_GetSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ( !lParam ) return 0;

    PBYTERANGE ByteRange = (PBYTERANGE)lParam;
    ByteRange->Min = min(HexView->SelectionStart, HexView->SelectionEnd);
    ByteRange->Max = max(HexView->SelectionStart, HexView->SelectionEnd);

    if ( HexView->Flags & HVF_SELECTED )
    {
        ByteRange->Max += 1;
    }
    return 1;
}
LRESULT HexView_SetColumnCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    const int columnCount = (int)lParam;
    if ( HexView->ColumnCount == columnCount )
        return 1;

    if ( columnCount < 1 )
        return 0;   // ��������С��1

    HexView->ColumnCount = columnCount;
    HexView->ColumnSecond = HexView->ColumnCount * 3 + 1;

    HexView_SetItemCount(HexView, hWnd, wParam, HexView->TotalItems);
    return 1;
}
LRESULT HexView_GetColumnCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return HexView->ColumnCount;
}



LRESULT HexView_SetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrBack;
    HexView->clr.clrBack = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetBkColor(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrBack;
}

LRESULT HexView_SetBkColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrBackSel;
    HexView->clr.clrBackSel = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetBkColorSel(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrBackSel;
}

LRESULT HexView_SetLineColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrLine;
    HexView->clr.clrLine = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetLineColor(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrLine;
}

LRESULT HexView_SetModifyTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrModifyText;
    HexView->clr.clrModifyText = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetModifyTextColor(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrModifyText;
}

LRESULT HexView_SetModifyTextColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrModifyTextSel;
    HexView->clr.clrModifyTextSel = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetModifyTextColorSel(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrModifyTextSel;
}

LRESULT HexView_SetAddrTextColorSel(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrTextAddress;
    HexView->clr.clrTextAddress = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetAddrTextColorSel(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrTextAddress;
}

LRESULT HexView_SetCharTextSelColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrTextSelChar;
    HexView->clr.clrTextSelChar = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetCharTextSelColor(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrTextSelChar;
}

LRESULT HexView_SetColorText1(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrText1;
    HexView->clr.clrText1 = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetColorText1(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrText1;
}

LRESULT HexView_SetColorText2(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrText2;
    HexView->clr.clrText2 = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetColorText2(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrText2;
}



LRESULT HexView_SetColorTextSel1(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrTextSel1;
    HexView->clr.clrTextSel1 = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetColorTextSel1(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrTextSel1;
}

LRESULT HexView_SetColorTextSel2(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clr.clrTextSel2;
    HexView->clr.clrTextSel2 = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_GetColorTextSel2(PHEXVIEW HexView, HWND hWnd)
{
    return (LRESULT)HexView->clr.clrTextSel2;
}

LRESULT HexView_SetDarkMode(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    DWORD oldStyle = HexView->ExStyle;
    BOOL isDarkMode = (HexView->ExStyle & HVS_DARMMODE) == HVS_DARMMODE;
    if (lParam)
        HexView->ExStyle |= HVS_DARMMODE;
    else
        HexView->ExStyle &= ~HVS_DARMMODE;

    HexView_SwitchDarkMode(HexView, hWnd, false);

    if (oldStyle != HexView->ExStyle)   // ������ʽ��ȾͲ��ػ�
        HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return isDarkMode;
}
LRESULT HexView_GetDarkMode(PHEXVIEW HexView, HWND hWnd)
{
    BOOL isDarkMode = (HexView->ExStyle & HVS_DARMMODE) == HVS_DARMMODE;
    return isDarkMode;
}
LRESULT HexView_GetColor(PHEXVIEW HexView, PHEXVIEW_COLOR pClr)
{
    if (!pClr)
        return 0;
    memcpy(pClr, &HexView->clr, sizeof(HexView->clr));
    return true;
}
LRESULT HexView_SetColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, PHEXVIEW_COLOR pClr)
{
    if (!pClr)
        return 0;
    memcpy(&HexView->clr, pClr, sizeof(HexView->clr));
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, 0);
    return true;
}


static void HexView_GetDefColor(HEXVIEW_COLOR* pClr, bool isDark)
{
    if (isDark)
    {
        pClr->clrTextSelChar     = RGB(255, 255, 255);
        pClr->clrText1           = RGB(202, 207, 221);
        pClr->clrText2           = RGB(215, 210, 196);
        pClr->clrTextSel1        = RGB(255, 255, 127);
        pClr->clrTextSel2        = RGB(255, 255, 0);
        pClr->clrTextAddress     = RGB(222, 222, 222);
        pClr->clrLine            = RGB(63, 63, 70);
        pClr->clrBack            = RGB(31, 31, 31);
        pClr->clrBackSel         = RGB(39, 80, 121);
        pClr->clrModifyText      = RGB(255, 0, 0);
        pClr->clrModifyTextSel   = RGB(0, 255, 255);
    }
    else
    {
        pClr->clrTextSelChar     = RGB(255, 255, 255);
        pClr->clrText1           = RGB(0, 0, 128);
        pClr->clrText2           = RGB(0, 0, 255);
        pClr->clrTextSel1        = RGB(255, 255, 127);
        pClr->clrTextSel2        = RGB(255, 255, 0);
        pClr->clrTextAddress     = RGB(0, 0, 0);
        pClr->clrLine            = RGB(204, 206, 219);
        pClr->clrBack            = RGB(255, 255, 255);
        pClr->clrBackSel         = RGB(8, 36, 107);
        pClr->clrModifyText      = RGB(255, 0, 0);
        pClr->clrModifyTextSel   = RGB(0, 255, 255);
    }
}

void HexView_SwitchDarkMode(PHEXVIEW HexView, HWND hWnd, BOOL isDraw)
{
    BOOL isDarkMode = (HexView->ExStyle & HVS_DARMMODE) == HVS_DARMMODE;

    HexView_GetDefColor(&HexView->clr, isDarkMode);

    if (isDraw)
        InvalidateRect(hWnd, NULL, FALSE);

}







LRESULT
CALLBACK
HexViewProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    PHEXVIEW HexView;
    HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, 0);

    switch (message)
    {
    case WM_CREATE:
        return HexView_OnCreate(HexView, hWnd, wParam, lParam);
    case WM_SETFONT:
        return HexView_OnSetFont(HexView, hWnd, wParam, lParam);
    case WM_TIMER:
        return HexView_OnTimer(HexView, hWnd, wParam, lParam);
    case WM_COMMAND:
        return HexView_OnCommand(HexView, hWnd, wParam, lParam);

    case WM_RBUTTONDOWN:
        return HexView_OnRButtonDown(HexView, hWnd, wParam, lParam);
    case WM_LBUTTONDOWN:
        return HexView_OnLButtonDown(HexView, hWnd, wParam, lParam);
    case WM_LBUTTONUP:
        return HexView_OnLButtonUp(HexView, hWnd, wParam, lParam);
    case WM_MOUSEMOVE:
        return HexView_OnMouseMove(HexView, hWnd, wParam, lParam);
    case WM_CHAR:
        return HexView_OnChar(HexView, hWnd, wParam, lParam);
    case WM_KEYDOWN:
        return HexView_OnKeyDown(HexView, hWnd, wParam, lParam);
    case WM_NCPAINT:
        return HexView_OnNcPaint(HexView, hWnd, wParam, lParam);
    case WM_PAINT:
        return HexView_OnPaint(HexView, hWnd, wParam, lParam);
    case WM_SETFOCUS:
        return HexView_OnSetFocus(HexView, hWnd, wParam, lParam);
    case WM_KILLFOCUS:
        return HexView_OnKillFocus(HexView, hWnd, wParam, lParam);
    case WM_VSCROLL:
        return HexView_OnVScroll(HexView, hWnd, wParam, lParam);
    case WM_HSCROLL:
        return HexView_OnHScroll(HexView, hWnd, wParam, lParam);
    case WM_SIZE:
        return HexView_OnSize(HexView, hWnd, wParam, lParam);
    case WM_MOUSEWHEEL:
        return HexView_OnMouseWheel(HexView, hWnd, wParam, lParam);
    case WM_DESTROY:
        return HexView_OnDestroy(HexView, hWnd, wParam, lParam);


    case HVM_SETEXTENDEDSTYLE:
        return HexView_SetExtendStyle(HexView, hWnd, wParam, lParam);
    case HVM_GETEXTENDEDSTYLE:
        return HexView_GetExtendStyle(HexView, hWnd, wParam, lParam);
    case HVM_SETITEMCOUNT:
        return HexView_SetItemCount(HexView, hWnd, wParam, lParam);
    case HVM_GETITEMCOUNT:
        return HexView_GetItemCount(HexView, hWnd, wParam, lParam);
    case HVM_SETSEL:
        return HexView_SetSel(HexView, hWnd, wParam, lParam);
    case HVM_GETSEL:
        return HexView_GetSel(HexView, hWnd, wParam, lParam);
    case HVM_SETCOLUMNCOUNT:
        return HexView_SetColumnCount(HexView, hWnd, wParam, lParam);
    case HVM_GETCOLUMNCOUNT:
        return HexView_GetColumnCount(HexView, hWnd, wParam, lParam);


        //////////////////////////////////////////////////////////////////////////
        // ���濪ʼ������/��ȡ��ɫ

    case HVM_SETCLRBK:              // ���ñ�����ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetBkColor(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRBK:              // ��ȡ������ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetBkColor(HexView, hWnd);
    case HVM_SETCLRBK_SEL:          // ����ѡ������ı�����ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetBkColorSel(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRBK_SEL:          // ��ȡѡ������ı�����ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetBkColorSel(HexView, hWnd);
    case HVM_SETCLRLINE:            // ����������ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetLineColor(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRLINE:            // ��ȡ������ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetLineColor(HexView, hWnd);
    case HVM_SETCLRMODIFYTEXT:      // �������޸��ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetModifyTextColor(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRMODIFYTEXT:      // ��ȡ���޸��ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetModifyTextColor(HexView, hWnd);
    case HVM_SETCLRMODIFYTEXT_SEL:  // ����ѡ���������޸��ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetModifyTextColorSel(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRMODIFYTEXT_SEL:  // ��ȡѡ���������޸��ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetModifyTextColorSel(HexView, hWnd);

    case HVM_SETCLRTEXTADDR:        // ������ߵ�ַ���ұ��ַ����ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetAddrTextColorSel(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXTADDR:        // ��ȡ��ߵ�ַ���ұ��ַ����ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetAddrTextColorSel(HexView, hWnd);
    case HVM_SETCLRTEXTSELCHAR:     // �����ұ�ѡ��ʱ�ַ����ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetCharTextSelColor(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXTSELCHAR:     // ��ȡ�ұ�ѡ��ʱ�ַ����ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetCharTextSelColor(HexView, hWnd);

    case HVM_SETCLRTEXT1:           // ���õ�һ�������ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetColorText1(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXT1:           // ��ȡ��һ�������ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetColorText1(HexView, hWnd);
    case HVM_SETCLRTEXT2:           // ���õڶ��������ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetColorText2(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXT2:           // ��ȡ�ڶ��������ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetColorText2(HexView, hWnd);
    case HVM_SETCLRTEXT1_SEL:       // ���õ�һ������ѡ���ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetColorTextSel1(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXT1_SEL:       // ��ȡ��һ������ѡ���ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetColorTextSel1(HexView, hWnd);
    case HVM_SETCLRTEXT2_SEL:       // ���õڶ�������ѡ���ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
        return HexView_SetColorTextSel2(HexView, hWnd, wParam, lParam);
    case HVM_GETCLRTEXT2_SEL:       // ��ȡ�ڶ�������ѡ���ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
        return HexView_GetColorTextSel2(HexView, hWnd);

        //////////////////////////////////////////////////////////////////////////

    case HVM_SETDARKMODE:           // ������ɫģʽ, wParam = �Ƿ��ػ�, lParam = �Ƿ�������ɫģʽ
        return HexView_SetDarkMode(HexView, hWnd, wParam, lParam);
    case HVM_GETDARKMODE:           // ��ȡ��ǰ��ͼ�Ƿ�Ϊ��ɫģʽ
        return HexView_GetDarkMode(HexView, hWnd);
    case HVM_GETCOLOR:              // ��ȡ��ǰ��ɫ��Ϣ, wParamδʹ��, lParam = HEXVIEW_COLOR �ṹָ��
        return HexView_GetColor(HexView, (PHEXVIEW_COLOR)lParam);
    case HVM_SETCOLOR:              // ���õ�ǰ��ɫ��Ϣ, wParam�Ƿ��ػ�, lParam = HEXVIEW_COLOR �ṹָ��
        return HexView_SetColor(HexView, hWnd, wParam, (PHEXVIEW_COLOR)lParam);

    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void RegisterClassHexView()
{
    static ATOM atom;
    if ( atom )
        return;
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize         = sizeof(WNDCLASSEXW);
    wcex.lpfnWndProc    = HexViewProc;
    wcex.hInstance      = GetModuleHandleW(NULL);
    wcex.hCursor        = LoadCursor(NULL, IDC_IBEAM);
    wcex.lpszClassName  = WC_HEXVIEWW;
    wcex.cbWndExtra     = 16;   // ��Ŷ���Ľṹ�õ�

    atom = RegisterClassExW(&wcex);
}

HWND CreateHexView(DWORD dwExStyle, DWORD dwStyle,
                   int x, int y, int nWidth, int nHeight, HWND hWndParent, LONG_PTR id, LPVOID lpParam)
{
    RegisterClassHexView();

    HWND hWnd;
    hWnd = CreateWindowExW(dwExStyle,
                           WC_HEXVIEWW,
                           NULL,
                           dwStyle,
                           x, y, nWidth, nHeight,
                           hWndParent,
                           (HMENU)(LONG_PTR)id,
                           GetModuleHandleW(NULL),
                           lpParam);

    return hWnd;
}

BOOLEAN HexView_BindNotify(HWND hWnd, WNDPROC pfn)
{
    PHEXVIEW HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, 0);
    if (!HexView)
        return FALSE;
    HexView->pfnNotify = pfn;
    return TRUE;
}

BOOLEAN HexView_SelChanged(PHEXVIEW HexView, HWND hWnd)
{
    NMHEXSEL NmHexSel = { 0 };
    NmHexSel.Min = min(HexView->SelectionStart, HexView->SelectionEnd);
    NmHexSel.Max = max(HexView->SelectionStart, HexView->SelectionEnd);
    NmHexSel.isSel = ( HexView->Flags & HVF_SELECTED ) == HVF_SELECTED;
    return (BOOLEAN)(DWORD)HexView_SendNotify(hWnd, HVN_ITEMSEL, (LPNMHDR)&NmHexSel);
}

void HexView_PopupMenu(PHEXVIEW HexView, HWND hWnd)
{
    // û��ѡ������Ļ�, ���ƹ��ܶ�����
    const SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    const SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);

    const BOOLEAN isSel = ( HexView->Flags & HVF_SELECTED ) != 0;
    const BOOLEAN isSelAll = start == 0 && end == HexView->TotalItems;
    const int disabled = isSel ? MF_STRING : MF_DISABLED;

    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    LPCWSTR pSearchData = pBox->search.GetResult();
    const int flag_search = ( pSearchData && *pSearchData) ? MF_STRING : MF_DISABLED;
    const int sel_all = isSelAll ? MF_DISABLED : MF_STRING;
    const int asm_flag = IsWindow(HexView->hAsm) ? MF_DISABLED : MF_STRING;;

    HMENU hMenu = CreatePopupMenu();
    HMENU hCopy1 = CreatePopupMenu();
    HMENU hCopy2 = CreatePopupMenu();
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY, L"&C.����");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16, L"Hex��ʽ (FF FF FF FF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_1, L"Hex��ʽ (FFFFFFFF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_C, L"C��ʽ (0xFF, 0xFF, 0xFF 0xFF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_ASM, L"����ʽ (0FFh, 0FFh, 0FFh, 0FFh)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_10, L"10���� (255 255 255 255)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_10_1, L"10���� (255255255255)");

    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2, L"&C.����");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16, L"Hex��ʽ (FF FF FF FF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_1, L"Hex��ʽ (FFFFFFFF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_C, L"C��ʽ (0xFF, 0xFF, 0xFF 0xFF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_ASM, L"����ʽ (0FFh, 0FFh, 0FFh, 0FFh)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_10, L"10���� (255 255 255 255)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_10_1, L"10���� (255255255255)");


    AppendMenuW(hMenu, disabled, ID_HEX_COPY, L"&C.����\tCtrl + C");
    AppendMenuW(hMenu, MF_POPUP | disabled, (UINT_PTR)hCopy1, L"����ʽ����");
    AppendMenuW(hMenu, MF_POPUP | disabled, (UINT_PTR)hCopy2, L"����ʽ����ȫ��");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, L"");

    AppendMenuW(hMenu, sel_all, ID_HEX_SELALL, L"&A.ȫѡ\tCtrl + A");
    AppendMenuW(hMenu, MF_STRING, ID_HEX_SEARCH, L"&F.����\tCtrl + F");
    AppendMenuW(hMenu, flag_search, ID_HEX_NEXT, L"&N.������һ��\tF3");
    AppendMenuW(hMenu, flag_search, ID_HEX_PREV, L"&P.������һ��\tShift + F3");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, L"");
    AppendMenuW(hMenu, MF_STRING, ID_HEX_JMP, L"&G.��ת\tCtrl + G");
    //AppendMenuW(hMenu, asm_flag, ID_HEX_ASM, L"&H.��ת����ര��\tCtrl + Q");

    POINT pt;
    GetCursorPos(&pt);
    TrackPopupMenu(hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, 0);
    DestroyMenu(hMenu);

}


void HexView_SelAll(PHEXVIEW HexView, HWND hWnd)
{
    HexView->SelectionStart = 0;
    HexView->SelectionEnd = HexView->TotalItems;
    HexView->Flags |= HVF_SELECTED;
    HexView_SelChanged(HexView, hWnd);
    InvalidateRect(hWnd, 0, 0);
}

BOOLEAN HexView_Copy(PHEXVIEW HexView, HWND hWnd, int fmt)
{
    BYTERANGE sel = { 0 };
    HexView_GetSel(HexView, hWnd, 0, (LPARAM)&sel);
    if ( sel.Max - sel.Min <= 0 )
        return FALSE;

    int size = HexView_GetSelText(HexView, hWnd, 0, 0, fmt);
    if ( size <= 0 )
        return FALSE;

    LPWSTR text = (LPWSTR)malloc(size * sizeof(wchar_t));
    if ( !text ) return FALSE;

    int size2 = HexView_GetSelText(HexView, hWnd, text, size, fmt);
    BOOL ret = HexView_SetClipboard(text, size2);
    free(text);
    return ret;
}

// ����ʱ������16���ƾ��ߵ�����, ��Ҫ�������16����ת�����ֽ�Ȼ��浽�ڴ���
// ������һ������һ����ʱ���ʹ�õ�
// 16�����ı�ת�����ֽ�����, ÿ�����ַ�ת��һ���ֽ�, ֱ��д�뵽�ṹ��, ���ͷž�����
inline void HexView_Search_HexToBin(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();
    if (_wcsnicmp(pStr, L"0x", 2) == 0)
        pStr += 2;
    size_t len = wcslen(pStr);

    auto pfn_isHex = [](wchar_t ch)
    {
        // a-f, A-F, 0-9 ����Щ�ַ��ͷ�����
        return ( ( ch >= 'a' && ch <= 'f' || ch >= 'A' && ch <= 'F' ) || ch >= '0' && ch <= '9' );
    };
    wchar_t buf[4] = { 0 };
    while ( *pStr )
    {
        buf[0] = *pStr++;
        if ( !pfn_isHex(buf[0]) )
            continue;   // ����16�����ַ�, ����
        wchar_t ch = *pStr++;
        if ( pfn_isHex(ch) )
        {
            // ��һ���ַ�Ҳ��16����, �Ǿʹ������ַ�
            buf[1] = ch;
        }
        else
        {
            // ��һ���ַ�����16����, �ǾͰѵ�һ���ַ�����16���Ƶĺ�������ַ�, ǰ����0
            buf[2] = buf[0];
            buf[0] = '0';
            buf[1] = buf[2];
        }
        buf[2] = 0;

        DWORD num = 0;
        swscanf_s(buf, L"%02X", &num);
        arr.push_back((BYTE)num);
        if ( ch == 0 )
            break;
    }

}

// ת����ansi����, �����ǵ����ȷ��, Ȼ���ߵ�����
inline void HexView_Search_ToAnsi(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();
    size_t len = wcslen(pStr);
    int aLen = WideCharToMultiByte(936, 0, pStr, (int)len, 0, 0, 0, 0) + 1;

    arr.resize(aLen);
    LPBYTE szStr = &arr[0];
    WideCharToMultiByte(936, 0, pStr, (int)len, (LPSTR)szStr, aLen, 0, 0);

}
// ��10���Ƶ���ת�����ֽ�, ����ȷ�Ϻ��ߵ�������
inline void HexView_Search_10ToBin(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();

    LONG64 ret = _wtoll(pStr);
    int* pInt = (int*)( &ret );
    int size = sizeof(LONG32);
    if (pInt[1])
    {
        // ��λ��ֵ, �Ǿ���64λ��ֵ, 8���ֽ�
        size = sizeof(LONG64);
    }
    arr.resize(size);
    memcpy(&arr[0], pInt, size);
}
// �Ѹ�����ת���ֽ�
inline void HexView_Search_FloatToBin(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();

    wchar_t* _Eptr;
    float f = (float)wcstod(pStr, &_Eptr);
    const int size = sizeof(float);
    arr.resize(size);
    memcpy(&arr[0], &f, size);
}
// ��˫������ת���ֽ�
inline void HexView_Search_DoubleToBin(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();

    wchar_t* _Eptr;
    double f = (double)wcstod(pStr, &_Eptr);
    const int size = sizeof(double);
    arr.resize(size);
    memcpy(&arr[0], &f, size);

}
// ת����unicode����, ��������Unicode, ������һ��
inline void HexView_Search_ToUnicode(PHEXVIEW HexView)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    arr.clear();

    LPCWSTR pStr = pBox->search.GetResult();
    size_t len = wcslen(pStr) * sizeof(wchar_t); // �����������־
    arr.resize(len);

    memcpy(&arr[0], pStr, len);
}

inline BOOLEAN _search_find(PHEXVIEW HexView, HWND hWnd, SIZE_T start, SIZE_T end, LPCWSTR text)
{
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    std::vector<BYTE>& arr = pBox->arr;
    int nSearchSize = (int)arr.size();
    if (!nSearchSize)
        return FALSE;
    LPBYTE pSearchData = nSearchSize > 0 ? &arr[0] : 0;
    NMHEXSEARCH search = { 0 };
    search.nSize    = nSearchSize;
    search.pSearch  = pSearchData;
    search.start    = start;
    search.end      = end;
    BOOLEAN isSearch = (BOOLEAN)HexView_SendNotify(hWnd, HVN_SEARCH, (LPNMHDR)&search);
    if ( isSearch )
    {
        HexView_Jmp_pos(HexView, hWnd, search.pos, search.pos + nSearchSize);
    }
    else
    {
        // û������������
        _search_msgbox(HexView, hWnd, text, start);
    }
    return isSearch;
}

void HexView_Search(PHEXVIEW HexView, HWND hWnd)
{
    PHEXVIEW_DATA_STRUCT box = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    CSearchBox& search = box->search;

    if ( !search.Show(hWnd)) return; // �Ի���ȡ��������

    int nMode = search.GetHexMode();
    // ���ı�ת������Ҫ����������
    switch (nMode)
    {
    case SEARCH_HEXMODE_HEX: // ʮ������
        HexView_Search_HexToBin(HexView);
        break;
    case SEARCH_HEXMODE_ANSI: // ansi�ַ���
        HexView_Search_ToAnsi(HexView);
        break;
    case SEARCH_HEXMODE_DEC: // 10����
        HexView_Search_10ToBin(HexView);
        break;
    case SEARCH_HEXMODE_UNICODE: // Unicode�ַ���
        HexView_Search_ToUnicode(HexView);
        break;
    case SEARCH_HEXMODE_FLOAT: // �����ȸ�����
        HexView_Search_FloatToBin(HexView);
        break;
    case SEARCH_HEXMODE_DOUBLE: // ˫���ȸ�����
        HexView_Search_DoubleToBin(HexView);
        break;
    default:
        break;
    }

    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    _search_find(HexView, hWnd, start, HexView->TotalItems, L"");

}

void _search_msgbox(PHEXVIEW HexView, HWND hWnd, LPCWSTR text, SIZE_T start)
{
    // û������������
    PHEXVIEW_DATA_STRUCT pBox = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    int nMode = pBox->search.GetHexMode();
    LPCWSTR mode = L"";
    switch (nMode)
    {
    case SEARCH_HEXMODE_ANSI: // ansi�ַ���
        mode = L"ANSI �ַ���";
        break;
    case SEARCH_HEXMODE_DEC: // 10����
        mode = L"10����";
        break;
    case SEARCH_HEXMODE_UNICODE: // Unicode�ַ���
        mode = L"Unicode�ַ���";
        break;
    case SEARCH_HEXMODE_FLOAT: // �����ȸ�����
        mode = L"�����ȸ�����";
        break;
    case SEARCH_HEXMODE_DOUBLE: // ˫���ȸ�����
        mode = L"˫���ȸ�����";
        break;
    default:
        mode = L"ʮ������";
        break;
    }

    NMHVDISPINFO DispInfo = { 0 };
    DispInfo.Item.Mask = HVIF_ADDRESS;
    DispInfo.Item.NumberOfItem = start;
    HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);
    LPCWSTR pSearchText = pBox->search.GetResult();
    size_t len = wcslen(pSearchText) + 260;
    LPWSTR dbg = (LPWSTR)HexViewAlloc(len * sizeof(wchar_t));
    swprintf_s(dbg, len,
               L"����ģʽ: %s\r\n"
               L"�����ı�: \"%s\"\r\n"
               L"�� 0x%016llX ��ʼ%s����\r\n\r\n"
               L"δ������ƥ������", mode, pSearchText, DispInfo.Item.Address, text);
    MessageBoxW(hWnd, dbg, L"û������������", 0);
    HexViewFree(dbg);
}
void HexView_Search_Next(PHEXVIEW HexView, HWND hWnd)
{
    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);
    start += 1;
    if ( start > HexView->TotalItems )
        start = 0;


    _search_find(HexView, hWnd, start, HexView->TotalItems, L"����");
}
void HexView_Search_Prev(PHEXVIEW HexView, HWND hWnd)
{
    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);

    start -= 1;
    if ( start > HexView->TotalItems )
        start = HexView->TotalItems - 1;

    _search_find(HexView, hWnd, start, 0, L"����");
}
void HexView_Jmp_pos(PHEXVIEW HexView, HWND hWnd, SIZE_T start, SIZE_T end)
{
    BYTERANGE sel = { 0 };
    sel.Min = start;
    sel.Max = end;
    HexView_SetSel(HexView, hWnd, 1, (LPARAM)&sel);
}



void HexView_Jmp(PHEXVIEW HexView, HWND hWnd)
{
    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);

    PHEXVIEW_DATA_STRUCT box = (PHEXVIEW_DATA_STRUCT)HexView->pBoxData;
    CJumpBox& jmp = box->jmp;
    
    if (!jmp.Show())
        return; // ȡ���˲���

    int mode = jmp.GetMode();
    SIZE_T retPos = (SIZE_T)jmp.GetResultNumber();
    SIZE_T pos = 0;
    if ( mode == 0 )    // �ļ���ʼ
    {
        pos = retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0 ) ? HexView->TotalItems - 1 : 0;
    }
    else if ( mode == 1 )   // ��ǰλ��
    {
        pos = start + retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0) ? HexView->TotalItems - 1 : 0;

    }
    else if ( mode == 2 )   // ��ǰλ������
    {
        pos = start - retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0 ) ? 0 : HexView->TotalItems - 1;
    }
    else if ( mode == 3 )   // �ļ�����
    {
        pos = HexView->TotalItems - retPos;
        if ( pos > HexView->TotalItems )
            pos = ( retPos > 0 ) ? 0 : HexView->TotalItems - 1;
    }

    HexView_Jmp_pos(HexView, hWnd, pos, pos + 1);
}


void HexView_Asm(PHEXVIEW HexView, HWND hWnd)
{
    //if ( IsWindow(HexView->hAsm) )
    //    return;
    //NMHEXCOPYDATA arg = { 0 };
    //arg.nSize = HexView->TotalItems;
    //arg.pBuf = HexViewAlloc(arg.nSize, true);
    //if ( HexView_SendNotify(hWnd, HVN_COPYDATA, (LPNMHDR)&arg) )
    //{
    //    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    //    ASMVIEW_LOAD asm_arg = { 0 };
    //    asm_arg.hParent = hWnd;
    //    asm_arg.szCaption = L"���鿴��";
    //    asm_arg.pData = arg.pBuf;
    //    asm_arg.nSize = arg.nSize;
    //    asm_arg.address = arg.Address;
    //    asm_arg.offset = start;
    //    asm_arg.nShowMode = HexView->asm_ShowMode;
    //    asm_arg.hFont = HexView->hFont;
    //    HexView->hAsm = AsmView_Load(&asm_arg);
    //    if ( !HexView->hAsm )
    //    {
    //        MessageBoxW(hWnd, L"�򿪻��鿴��ʧ��", L"����", 0);
    //    }
    //}
    //else
    //{
    //    MessageBoxW(hWnd, L"��ȡ����ʧ��, �޷��鿴���", L"����", 0);
    //}
    //HexViewFree(arg.pBuf);
}
