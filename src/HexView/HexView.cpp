#include "HexView.h"
#include "HexView_Search.h"
#include "HexView_Jmp.h"
#include "HexView_Function.h"

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

#define ID_HEX_COPY             1000    // 直接复制, Ctrl+C 的结果
#define ID_HEX_COPY_16          1001    // 复制16进制
#define ID_HEX_COPY_16_1        1002    // 复制16进制, 不用空格隔开
#define ID_HEX_COPY_16_C        1003    // 复制16进制, 用C语言的格式, 0xFF, 
#define ID_HEX_COPY_16_ASM      1004    // 复制16进制, 用汇编的格式, 0FFh, 
#define ID_HEX_COPY_10          1005    // 复制10进制
#define ID_HEX_COPY_10_1        1006    // 复制10进制, 中间没有字符分隔

#define ID_HEX_COPY2            1100    // 直接复制, Ctrl+C 的结果
#define ID_HEX_COPY2_16         1101    // 复制16进制
#define ID_HEX_COPY2_16_1       1102    // 复制16进制, 不用空格隔开
#define ID_HEX_COPY2_16_C       1103    // 复制16进制, 用C语言的格式, 0xFF, 
#define ID_HEX_COPY2_16_ASM     1104    // 复制16进制, 用汇编的格式, 0FFh, 
#define ID_HEX_COPY2_10         1105    // 复制10进制
#define ID_HEX_COPY2_10_1       1106    // 复制10进制, 中间没有字符分隔

#define ID_HEX_SELALL           1200    // 全选 Ctrl+A
#define ID_HEX_SEARCH           1201    // 搜索 Ctrl+F
#define ID_HEX_NEXT             1202    // 搜索下一个 N
#define ID_HEX_PREV             1203    // 搜索上一个 P

#define ID_HEX_JMP              1300    // 跳转 Ctrl+G
#define ID_HEX_ASM              1301    // 跳转到汇编窗口 Ctrl+Q

#define NUMBEROF_CHARS_IN_FIRST_COLUMN_64BIT    1 + 18 + 2  // 这个影响左边地址的距离, 18表示18个字符
#define NUMBEROF_CHARS_IN_FIRST_COLUMN_32BIT    1 + 10 + 2  // 这个是32位地址, 10个字符


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
//void HexView_Asm(PHEXVIEW HexView, HWND hWnd);


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

LRESULT HexView_SetTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetSelBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_SetModifiedColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);


LRESULT HexView_GetTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetSelBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT HexView_GetModifiedColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam);


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
    NmHdr->hwndFrom = hWnd;
    NmHdr->code = Code;
    PHEXVIEW HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if ( !HexView )
        return 0;
    if ( HexView->pfnNotify )
        return HexView->pfnNotify(hWnd, NmHdr, HexView->lpParamNotify);
    return SendMessageW(HexView->hWndParent, WM_NOTIFY, 0, (LPARAM)NmHdr);
}


// 获取选中文本, 返回拷贝到缓冲区的尺寸
// HexView = 组件数据
// buf = 缓冲区, 为0则返回缓冲区需要的尺寸
// bufSize = 缓冲区尺寸, 为0则返回缓冲区需要的尺寸
// flags = 复制的标志, HVCPY_ 开头的常量
int HexView_GetSelText(PHEXVIEW HexView, HWND hWnd, LPWSTR buf, int bufSize, int flags)
{
    NMHVDISPINFO DispInfo = { 0 };
    const BOOLEAN isHex = (flags & HVCPY_HEX10) == 0;
    const BOOLEAN isAddress = (flags & HVCPY_ADDRESS ) == HVCPY_ADDRESS;
    const BOOLEAN isChar = (flags & HVCPY_CHAR ) == HVCPY_CHAR;
    const BOOLEAN isAddress64 = ( HexView->ExStyle & HVS_ADDRESS64 ) == HVS_ADDRESS64;
    const int copyMode = ( flags & 0xFF00 );

    // 是否有换行, 为真的话就是需要加换行符, 为假的话就是不需要分隔符, 也不需要换行符
    // 拷贝模式不是10/16进制不分隔, 或者有拷贝地址或者字符, 都算有换行
    const BOOLEAN isWrap = (copyMode != HVCPY_HEX_1 && copyMode != HVCPY_HEX10_1) || (isAddress || isChar);

    BYTERANGE sel = { 0 };
    HexView_GetSel(HexView, hWnd, 0, (LPARAM)&sel);
    int selCount = (int)(sel.Max - sel.Min);
    if ( selCount <= 0 )
        return 0;   // 没有选中任何内容, 没有选中就不需要缓冲区, 不写入任何字节

    int allocSize = 0;  // 总共需要的尺寸
    int hexSize = 0;    // 16进制部分需要的尺寸
    int addrSize = 0;   // 地址需要的尺寸
    int charSize = 0;   // 右边字符需要的尺寸

    const int first_line = (int)( sel.Min ) / HexView->ColumnCount;
    const int final_line = (int)( sel.Max ) / HexView->ColumnCount - ( sel.Max % HexView->ColumnCount == 0 ? 1 : 0 );
    const int lineCount = final_line - first_line + 1;  // 一共多少行

    
    LPCWSTR fmt_kg = L"  ";
    switch ( copyMode )
    {
    case HVCPY_HEX_1:   // 复制16进制, 不用空格分隔
        // 行数 * (每行的字符数 * 每个字节占用尺寸) 每个字节占用尺寸 = 2
        hexSize = lineCount * ( HexView->ColumnCount * 2 );
        break;
    case HVCPY_HEX_C:   // 复制16进制, 用C语言的格式, 0xFF, 
        // 一个字节变成4个字符, 加上逗号和空格, 0xff 变成 "0xFF, "
        // 行数 * (每行的字符数 * 每个字节占用尺寸) 每个字节占用尺寸 = 6
        hexSize = lineCount * ( HexView->ColumnCount * 6 );
        fmt_kg = L"      ";
        break;
    case HVCPY_HEX_ASM: // 复制16进制, 用汇编的格式, 0FFh, 
        // 一个字节变成4个字符, 加上逗号和空格, 0xff 变成 "0FFh, "
        // 行数 * (每行的字符数 * 每个字节占用尺寸) 每个字节占用尺寸 = 6
        hexSize = lineCount * ( HexView->ColumnCount * 6 );
        fmt_kg = L"      ";
        break;
    case HVCPY_HEX10_1: // 复制10进制, 字节没有字符分隔
        // 一个字节变成3个字符, 没有逗号没有空格, 一个字节最长就3个字符, 按最长的算
        // 行数 * (每行的字符数 * 每个字节占用尺寸) 每个字节占用尺寸 = 3
        hexSize = lineCount * ( HexView->ColumnCount * 3 );
        fmt_kg = L" ";
        break;
    default:
        // 没有指定格式, 就按16/10进制计算
        // 16进制部分需要的尺寸, 16进制每个字节占用3个字符, 10进制占用4个字符
        // 16进制最大 ff, 10进制最大 255, 加上空格就是3/4个字符
        // 行数 * (每行的字符数 * 每个字节占用尺寸)
        hexSize = lineCount * ( HexView->ColumnCount * ( isHex ? 3 : 4 ) );
        fmt_kg = isHex ? L"   " : L"    ";
        break;
    }

    if ( isAddress )
    {
        // 地址部分需要的尺寸, 64位地址占用18个字符, 32位地址占用10个字符, 加上两个空格
        // 行数 * (每行的字符数 * 每个字节占用尺寸)
        addrSize = lineCount * ( isAddress64 ? 20 : 12 );
    }

    if ( isChar )
    {
        // 字符部分需要的尺寸, 多少列就占用多少个字符, 再加一个空格
        // 行数 * (列数 + 空格)
        charSize = lineCount * ( HexView->ColumnCount + 1 );
    }

    // 总尺寸 = 地址尺寸 + 16进制尺寸 + 字符尺寸 + 每行的换行符
    allocSize = addrSize + hexSize + charSize + (lineCount * 2);

    if ( !buf || bufSize <= 0 )
        return allocSize + 1;   // 加一个结束标志


    WORD* buf_value = 0;    // 每列的值, 有多少列缓冲区就有多大
    int index_value = 0;    // 每次循环都从0开始, 循环次数是列数
    if ( charSize )
    {
        buf_value = (WORD*)malloc(HexView->ColumnCount * sizeof(WORD));
        memset(buf_value, 0, HexView->ColumnCount * sizeof(WORD));
    }

    // 获取进制值, 每一行循环去取
    const LPCWSTR fmt_addr = isAddress64 ? L"0x%016llX  " : L"0x%08X  ";
    const LPCWSTR fmt_hex = isHex ? L"%02X " : L"% 3d ";
    int offset_hex = 0;
    wchar_t buffer[32];

    auto pfn_append = [&](LPCWSTR vl, int len)
    {
        if ( len < 0 )
            return; // 长度为0就不需要复制

        // 缓冲区长度 - 已经写入的长度 = 剩余长度
        int len1 = bufSize - offset_hex;

        if ( len > len1 )
        {
            // 剩余长度不够了, 只写入一部分
            int writeLen = len1 - len - 1;
            if ( writeLen > 0 )
            {
                wmemcpy(&buf[offset_hex], vl, writeLen);
                offset_hex += writeLen;
                buf[offset_hex] = L'\0';
            }
            throw 1;
        }

        // 走到这里就是缓冲区足够写入

        wmemcpy(&buf[offset_hex], vl, len);
        offset_hex += len;
        buf[offset_hex] = L'\0';
    };
    auto pfn_push_back = [&](wchar_t ch)
    {
        if( offset_hex + 1 >= bufSize )
            throw 2; // 缓冲区已满, 不再写入
        buf[offset_hex++] = ch;
        buf[offset_hex] = L'\0';
    };

    // 返回内存是否已满, 满了就应该退出循环
    auto pfn_add_format = [&](LPCWSTR fmt, ULONG64 vl)
    {
        int len = swprintf_s(buffer, fmt, vl);
        pfn_append(buffer, len);
    };

    auto pfn_address = [&](int i)
    {
        if ( !addrSize ) return;
        
        // 写入地址
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
                // 这部分填充空格
                if ( isWrap )   // 如果是复制不分隔的就不需要加空格
                    pfn_add_format(fmt_kg, 0);
                if ( buf_value )
                    buf_value[index_value++] = 0xffff;
            }
            else
            {
                // 选择的内容, 需要转换成对应进制
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
                case HVCPY_HEX_1:   // 复制16进制, 不用空格分隔
                    pfn_add_format(L"%02X", DispInfo.Item.Value);       // 按这个格式加入, "FF"
                    break;
                case HVCPY_HEX_C:   // 复制16进制, 用C语言的格式, 0xFF, 
                    // 一个字节变成4个字符, 加上逗号和空格, 0xff 变成 "0xFF, "
                    pfn_add_format(L"0x%02X, ", DispInfo.Item.Value);   // 按这个格式加入, "0xFF, "
                    break;
                case HVCPY_HEX_ASM: // 复制16进制, 用汇编的格式, 0FFh, 
                    // 一个字节变成4个字符, 加上逗号和空格, 0xff 变成 "0FFh, "
                    pfn_add_format(L"0%02Xh, ", DispInfo.Item.Value);   // 按这个格式加入, "0FFh, "
                    break;
                case HVCPY_HEX10_1: // 复制10进制, 字节没有字符分隔
                    pfn_add_format(L"%u", DispInfo.Item.Value);         // 按这个格式加入, 直接加, 不用空格分隔
                    break;
                default:
                {
                    if ( isHex )
                    {
                        pfn_add_format(fmt_hex, DispInfo.Item.Value);
                    }
                    else
                    {
                        // 10进制需要自己转一下
                        len = swprintf_s(buffer, L"%u", DispInfo.Item.Value);
                        for ( int i = 0; i < 3 - len; i++ )
                            pfn_push_back(L' ');    // 不足3位的补空格

                        pfn_append(buffer, len);    // 空格加上这个值肯定是3位
                        pfn_push_back(L' ');        // 后面再补个空格
                    }
                    break;
                }
                }


            }
        }

    };
    auto pfn_char = [&]()
    {
        // buf_value 有值就表示要写入右边的字符, 没有值就不需要
        // 进制值右边有一个空格, 如果不需要写右边的字符, 那就把左边的空格去掉
        if ( !buf_value  )
        {
            if ( isWrap )
                buf[--offset_hex] = L'\0';  // 去掉最后一个空格
            return;
        }
        
        index_value = 0;
        // 先加一个空格, 和左边的值隔开两个空格, 值末尾有一个空格, 这里再加一个
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
            pfn_address(i);     // 写入左边的地址, 如果不需要就不写入

            pfn_hex(i);         // 写入中间的16进制值

            pfn_char();         // 写入右边的字符值

            // 一行写完了, 加上换行, 不加分隔的就不加换行符
            if ( isWrap )
            {
                pfn_push_back(L'\r');
                pfn_push_back(L'\n');
            }
        }

    }
    catch (...)
    {
        // 走到这里就是内存写满了, 可以收尾返回了
        //__debugbreak();
    }

    if ( buf_value )
        free(buf_value);

    return offset_hex;
}

// 绘画左边的地址
void HexView_DrawAddress(HDC hdc, PHEXVIEW HexView, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[32]; // 把字节转成字符用的缓冲区
    SetTextColor(hdc, HexView->clrTextAddress);

    const LPCWSTR fmt = ( HexView->ExStyle & HVS_ADDRESS64 ) ? L"0x%016I64X" : L"0x%08X";
    StringCchPrintfW(Buffer, _countof(Buffer), fmt, DispInfo->Item.Address);

    int ShiftPosX = -( HexView->WidthChar * HexView->HscrollPos ) + HexView->WidthChar;
    TextOutW(hdc, ShiftPosX, top, (PCWSTR)Buffer, (int)wcslen(Buffer));
}

// 绘画中间的16进制值, 这里根据样式决定绘画什么格式, 1/2/4/8 字节, 浮点, 双浮点, 有符号无符号等格式
void HexView_DrawHexValue(HDC hdc, PHEXVIEW HexView, int Position1, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[100];    // 转换数值的缓冲区, 100个字节足够了, 就算是双精度浮点都够存放了

    StringCchPrintfW(Buffer, _countof(Buffer), L"%02X", DispInfo->Item.Value);
    TextOutW(hdc, Position1, top, (PCWSTR)Buffer, 2);

}

// 绘画右边的字符
void HexView_DrawCharValue(HDC hdc, PHEXVIEW HexView, int Position2, NMHVDISPINFO* DispInfo, int top)
{
    wchar_t Buffer[32]; // 把字节转成字符用的缓冲区
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

    // 绘画左边的地址
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
            SetBkColor(hdcMem, HexView->clrSelTextBack);

            if (i != SelectionEnd && i != NumberOfItem + ( HexView->ColumnCount - 1))
            {
                // 这里是填充两个16进制值之间的那一小段空白

                rc.top = 0;
                rc.bottom = HexView->HeightView;
                rc.left = Position1 + HexView->WidthChar * 2;
                rc.right = rc.left + HexView->WidthChar;
                ExtTextOutW(hdcMem, 0, top, ETO_OPAQUE, &rc, NULL, 0, NULL);
            }
            // 选中使用其他文本颜色
            const COLORREF clrText = ( DispInfo.Item.State & HVIS_MODIFIED ) ? HexView->clrModifiedTextSel :
                ( ( i % 2 == 0 ) ? HexView->clrTextSel1 : HexView->clrTextSel2 );
            SetTextColor(hdcMem, clrText);
        }
        else
        {
            SetBkColor(hdcMem, HexView->clrTextBackground);
            const COLORREF clrText = ( DispInfo.Item.State & HVIS_MODIFIED ) ? HexView->clrModifiedText :
                ( ( i % 2 == 0 ) ? HexView->clrText1 : HexView->clrText2 );
            SetTextColor(hdcMem, clrText);
        }

        // 绘画中间的16进制值, 需要改成有符号/无符号, 多少个字节显示, 都在这里改
        HexView_DrawHexValue(hdcMem, HexView, Position1, &DispInfo, top);

        // 绘画右边的字符
        SetTextColor(hdcMem, isSel ? HexView->clrTextSel : HexView->clrTextAddress);
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

    hPen = CreatePen(PS_SOLID, 1, HexView->clrLine);
    hOld = SelectObject(hdcMem, hbmMem);
    hOldPen = SelectObject(hdcMem, hPen);
    hOldFont = SelectObject(hdcMem, HexView->hFont);

    clrBk = SetBkColor(hdcMem, HexView->clrTextBackground);
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

        // 十六进制左边位置, 小于这个位置就是地址
        const int left1 = HexView->Line1 - HexView->WidthChar * 2;
        const int ritgt1 = HexView->Line1 + ( ( ((int)NumberOfItemsInLine) * 3 ) - 1 ) * HexView->WidthChar;

        // 这个判断是判断鼠标在十六进制中, 这里改成在地址中也可以选中
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

    SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)HexView);

    HexView->ActiveColumn = COLUMN_DATA;
    HexView->ColumnCount = 16;
    HexView->ColumnSecond = HexView->ColumnCount * 3 + 1;
    HexView->hWndParent = GetParent(hWnd);

    HexView->clrTextSel         = RGB(255, 255, 255);
    HexView->clrText1           = RGB(0, 0, 128);
    HexView->clrText2           = RGB(0, 0, 255);
    HexView->clrTextSel1        = RGB(255, 255, 127);
    HexView->clrTextSel2        = RGB(255, 255, 0);
    HexView->clrTextAddress     = RGB(0, 0, 0);
    HexView->clrLine            = RGB(204, 206, 219);
    HexView->clrTextBackground  = RGB(255, 255, 255);
    HexView->clrSelTextBack     = RGB(8, 36, 107);
    HexView->clrModifiedText    = RGB(255, 0, 0);
    HexView->clrModifiedTextSel = RGB(0, 255, 255);

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
        wcscpy_s(LogFont.lfFaceName, _countof(LogFont.lfFaceName), L"黑体");

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
    case ID_HEX_COPY:           // 直接复制, Ctrl+C 的结果
    case ID_HEX_COPY_16:        // 复制16进制
        HexView_Copy(HexView, hWnd, HVCPY_DEF);
        break;
    case ID_HEX_COPY_16_1:      // 复制16进制, 不用空格隔开
        HexView_Copy(HexView, hWnd, HVCPY_HEX_1);
        break;
    case ID_HEX_COPY_16_C:      // 复制16进制, 用C语言的格式, 0xFF, 
        HexView_Copy(HexView, hWnd, HVCPY_HEX_C);
        break;
    case ID_HEX_COPY_16_ASM:    // 复制16进制, 用汇编的格式, 0FFh, 
        HexView_Copy(HexView, hWnd, HVCPY_HEX_ASM);
        break;
    case ID_HEX_COPY_10:        // 复制10进制
        HexView_Copy(HexView, hWnd, HVCPY_HEX10);
        break;
    case ID_HEX_COPY_10_1:      // 复制10进制, 中间没有字符分隔
        HexView_Copy(HexView, hWnd, HVCPY_HEX10_1);
        break;
    case ID_HEX_COPY2:          // 直接复制, Ctrl+C 的结果
    case ID_HEX_COPY2_16:       // 复制16进制
        HexView_Copy(HexView, hWnd, HVCPY_ALL);
        break;
    case ID_HEX_COPY2_16_1:     // 复制16进制, 不用空格隔开
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_1);
        break;
    case ID_HEX_COPY2_16_C:     // 复制16进制, 用C语言的格式, 0xFF, 
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_C);
        break;
    case ID_HEX_COPY2_16_ASM:   // 复制16进制, 用汇编的格式, 0FFh, 
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX_ASM);
        break;
    case ID_HEX_COPY2_10:       // 复制10进制
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX10);
        break;
    case ID_HEX_COPY2_10_1:     // 复制10进制, 中间没有字符分隔
        HexView_Copy(HexView, hWnd, HVCPY_ALL | HVCPY_HEX10_1);
        break;
    case ID_HEX_SELALL:         // 全选 Ctrl+A
        HexView_SelAll(HexView, hWnd);
        break;
    case ID_HEX_SEARCH:         // 搜索 Ctrl+F
        HexView_Search(HexView, hWnd);
        break;
    case ID_HEX_NEXT:           // 搜索下一个 N
        HexView_Search_Next(HexView, hWnd);
        break;
    case ID_HEX_PREV:           // 搜索上一个 P
        HexView_Search_Prev(HexView, hWnd);
        break;
    case ID_HEX_JMP:            // 跳转 Ctrl+G
        HexView_Jmp(HexView, hWnd);
        break;
    //case ID_HEX_ASM:            // 跳转到汇编窗口 Ctrl+Q
    //    HexView_Asm(HexView, hWnd);
    //    break;
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
    case 'F':   // 搜索
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_Search(HexView, hWnd);
        break;
    }
    case VK_F3: // 搜索上/下一个
    {
        if ( IsCtrlKeyDown )
            break;
        if ( IsShiftKeyDown )
            HexView_Search_Prev(HexView, hWnd);
        else
            HexView_Search_Next(HexView, hWnd);
        return 0;
    }
    case 'G':   // 跳转
    {
        if ( !IsCtrlKeyDown )
            break;
        HexView_Jmp(HexView, hWnd);
        break;
    }
    //case 'Q':   // 跳转到汇编窗口
    //{
    //    if ( !IsCtrlKeyDown )
    //        break;
    //    HexView_Asm(HexView, hWnd);
    //    break;
    //}
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
    HPEN hPen = CreatePen(PS_SOLID, 1, HexView->clrLine);

    HGDIOBJ hOldPen = SelectObject(hdc, hPen);
    HGDIOBJ hOldBrush = SelectObject(hdc, GetStockBrush(NULL_BRUSH));

    Rectangle(hdc, 0, 0, cxScreen, cyScreen);   // 直接画到窗口DC上

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
        HexView_FreeList(HexView->pNode);
        HexView_FreeList(HexView->pNodeJmp);
        HeapFree(GetProcessHeap(), 0, HexView);
    }
    return 0;
}


// 发送消息过来让组件处理, 都在这个命名空间内处理

LRESULT HexView_SetExtendStyle(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    DWORD ret = HexView->ExStyle;
    HexView->ExStyle = (DWORD)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
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
        return 0;   // 列数不能小于1

    HexView->ColumnCount = columnCount;
    HexView->ColumnSecond = HexView->ColumnCount * 3 + 1;

    HexView_SetItemCount(HexView, hWnd, wParam, HexView->TotalItems);
    return 1;
}
LRESULT HexView_GetColumnCount(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return HexView->ColumnCount;
}


LRESULT HexView_SetTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clrText1;
    HexView->clrText1 = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_SetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clrTextBackground;
    HexView->clrTextBackground = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_SetSelBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clrSelTextBack;
    HexView->clrSelTextBack = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}
LRESULT HexView_SetModifiedColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COLORREF ret = HexView->clrModifiedText;
    HexView->clrModifiedText = (COLORREF)lParam;
    HexView_Wparam_InvalidateRect(HexView, hWnd, wParam, lParam);
    return ret;
}


LRESULT HexView_GetTextColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return (LRESULT)HexView->clrText1;
}
LRESULT HexView_GetBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return (LRESULT)HexView->clrTextBackground;
}
LRESULT HexView_GetSelBkColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return (LRESULT)HexView->clrSelTextBack;
}
LRESULT HexView_GetModifiedColor(PHEXVIEW HexView, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    return (LRESULT)HexView->clrModifiedText;
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
    HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, GWLP_USERDATA);

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
    case HVM_SETTEXTCOLOR:
        return HexView_SetTextColor(HexView, hWnd, wParam, lParam);
    case HVM_SETBKCOLOR:
        return HexView_SetBkColor(HexView, hWnd, wParam, lParam);
    case HVM_SETSELBKCOLOR:
        return HexView_SetSelBkColor(HexView, hWnd, wParam, lParam);
    case HVM_SETMODIFIEDCOLOR:
        return HexView_SetModifiedColor(HexView, hWnd, wParam, lParam);
    case HVM_GETTEXTCOLOR:
        return HexView_GetTextColor(HexView, hWnd, wParam, lParam);
    case HVM_GETBKCOLOR:
        return HexView_GetBkColor(HexView, hWnd, wParam, lParam);
    case HVM_GETSELBKCOLOR:
        return HexView_GetSelBkColor(HexView, hWnd, wParam, lParam);
    case HVM_GETMODIFIEDCOLOR:
        return HexView_GetModifiedColor(HexView, hWnd, wParam, lParam);

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
    wcex.cbWndExtra     = 20;

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

BOOLEAN HexView_BindNotify(HWND hWnd, PFN_HEXVIEW_NOTIFY pfn, LPVOID lpParam)
{
    PHEXVIEW HexView = (PHEXVIEW)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if ( !HexView )
        return FALSE;
    HexView->lpParamNotify = lpParam;
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
    // 没有选择区域的话, 复制功能都禁用
    const SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    const SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);

    const BOOLEAN isSel = ( HexView->Flags & HVF_SELECTED ) != 0;
    const BOOLEAN isSelAll = start == 0 && end == HexView->TotalItems;
    const int disabled = isSel ? MF_STRING : MF_DISABLED;
    const int flag_search = ( HexView->pSearchData && HexView->nSearchSize ) ? MF_STRING : MF_DISABLED;
    const int sel_all = isSelAll ? MF_DISABLED : MF_STRING;
    const int asm_flag = IsWindow(HexView->hAsm) ? MF_DISABLED : MF_STRING;;

    HMENU hMenu = CreatePopupMenu();
    HMENU hCopy1 = CreatePopupMenu();
    HMENU hCopy2 = CreatePopupMenu();
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY, L"&C.复制");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16, L"Hex格式 (FF FF FF FF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_1, L"Hex格式 (FFFFFFFF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_C, L"C格式 (0xFF, 0xFF, 0xFF 0xFF)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_16_ASM, L"汇编格式 (0FFh, 0FFh, 0FFh, 0FFh)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_10, L"10进制 (255 255 255 255)");
    AppendMenuW(hCopy1, MF_STRING, ID_HEX_COPY_10_1, L"10进制 (255255255255)");

    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2, L"&C.复制");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16, L"Hex格式 (FF FF FF FF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_1, L"Hex格式 (FFFFFFFF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_C, L"C格式 (0xFF, 0xFF, 0xFF 0xFF)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_16_ASM, L"汇编格式 (0FFh, 0FFh, 0FFh, 0FFh)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_10, L"10进制 (255 255 255 255)");
    AppendMenuW(hCopy2, MF_STRING, ID_HEX_COPY2_10_1, L"10进制 (255255255255)");


    AppendMenuW(hMenu, disabled, ID_HEX_COPY, L"&C.复制\tCtrl + C");
    AppendMenuW(hMenu, MF_POPUP | disabled, (UINT_PTR)hCopy1, L"按格式复制");
    AppendMenuW(hMenu, MF_POPUP | disabled, (UINT_PTR)hCopy2, L"按格式复制全部");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, L"");

    AppendMenuW(hMenu, sel_all, ID_HEX_SELALL, L"&A.全选\tCtrl + A");
    AppendMenuW(hMenu, MF_STRING, ID_HEX_SEARCH, L"&F.搜索\tCtrl + F");
    AppendMenuW(hMenu, flag_search, ID_HEX_NEXT, L"&N.搜索下一个\tF3");
    AppendMenuW(hMenu, flag_search, ID_HEX_PREV, L"&P.搜索上\tShift + F3");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, L"");
    AppendMenuW(hMenu, MF_STRING, ID_HEX_JMP, L"&G.跳转\tCtrl + G");
    //AppendMenuW(hMenu, asm_flag, ID_HEX_ASM, L"&H.跳转到汇编窗口\tCtrl + Q");

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

// 重新调整搜索数据缓冲区
inline LPBYTE HexView_Search_Resize(PHEXVIEW HexView, size_t newSize)
{
    if ( HexView->nSearchBufSize >= (int)newSize )
        return HexView->pSearchData;    // 缓冲区还足够, 不需要重新分配

    // 缓冲区不够, 重新分配
    if ( HexView->pSearchData )
        HexViewFree(HexView->pSearchData);
    if ( newSize < 100 )
        newSize = 100;
    HexView->pSearchData = (LPBYTE)HexViewAlloc(newSize, true);
    HexView->nSearchBufSize = (int)(DWORD)newSize;
    return HexView->pSearchData;
}

// 16进制文本转换成字节数据, 每两个字符转成一个字节, 直接写入到结构里, 会释放旧数据
inline void HexView_Search_HexToBin(PHEXVIEW HexView)
{
    LPCWSTR pStr = HexView->pSearchText;
    size_t len = wcslen(pStr);
    HexView_Search_Resize(HexView, len);
    LPBYTE p = HexView->pSearchData;

    HexView->nSearchSize = 0;
    auto pfn_isHex = [](wchar_t ch)
    {
        // a-f, A-F, 0-9 是这些字符就返回真
        return ( ( ch >= 'a' && ch <= 'f' || ch >= 'A' && ch <= 'F' ) || ch >= '0' && ch <= '9' );
    };
    wchar_t buf[4] = { 0 };
    while ( *pStr )
    {
        buf[0] = *pStr++;
        if ( !pfn_isHex(buf[0]) )
            continue;   // 不是16进制字符, 跳过
        wchar_t ch = *pStr++;
        if ( pfn_isHex(ch) )
        {
            // 下一个字符也是16进制, 那就凑两个字符
            buf[1] = ch;
        }
        else
        {
            // 下一个字符不是16进制, 那就把第一个字符当成16进制的后面这个字符, 前面是0
            buf[2] = buf[0];
            buf[0] = '0';
            buf[1] = buf[2];
        }
        buf[2] = 0;

        DWORD num = 0;
        swscanf_s(buf, L"%02X", &num);
        p[HexView->nSearchSize++] = (BYTE)num;
        if ( ch == 0 )
            break;
    }
}
// 转换到ansi编码
inline void HexView_Search_ToAnsi(PHEXVIEW HexView)
{
    LPCWSTR unicode = HexView->pSearchText;
    size_t len = wcslen(unicode);
    int aLen = WideCharToMultiByte(936, 0, unicode, (int)len, 0, 0, 0, 0) + 1;
    LPBYTE szStr = HexView_Search_Resize(HexView, aLen);

    WideCharToMultiByte(936, 0, unicode, (int)len, (LPSTR)szStr, aLen, 0, 0);
    
    HexView->nSearchSize = aLen - 1;
}
// 把10进制的数转换成字节
inline void HexView_Search_10ToBin(PHEXVIEW HexView)
{
    LONG64 ret = _wtoll(HexView->pSearchText);
    LPBYTE ptr = HexView_Search_Resize(HexView, sizeof(ret));
    int* arr = (int*)( &ret );
    HexView->nSearchSize = 4;
    if ( arr[1] )
    {
        // 高位有值, 那就是64位数值, 8个字节
        HexView->nSearchSize = 8;
    }
    memcpy(ptr, arr, HexView->nSearchSize);
}
// 把浮点数转成字节
inline void HexView_Search_FloatToBin(PHEXVIEW HexView)
{
    wchar_t* _Eptr;
    float f = (float)wcstod(HexView->pSearchText, &_Eptr);
    LPBYTE ptr = HexView_Search_Resize(HexView, sizeof(f));
    memcpy(ptr, &f, sizeof(f));
    HexView->nSearchSize = sizeof(f);
}
// 把双浮点数转成字节
inline void HexView_Search_DoubleToBin(PHEXVIEW HexView)
{
    wchar_t* _Eptr;
    double f = wcstod(HexView->pSearchText, &_Eptr);
    LPBYTE ptr = HexView_Search_Resize(HexView, sizeof(f));
    memcpy(ptr, &f, sizeof(f));
    HexView->nSearchSize = sizeof(f);
}
// 转换到unicode编码, 本来就是Unicode, 这里拷贝一份
inline void HexView_Search_ToUnicode(PHEXVIEW HexView)
{
    LPCWSTR unicode = HexView->pSearchText;
    size_t len = wcslen(unicode) * sizeof(wchar_t); // 不分配结束标志
    LPBYTE szStr = HexView_Search_Resize(HexView, len);

    memcpy(szStr, unicode, len);
    HexView->nSearchSize = (int)(DWORD)len;
}

inline BOOLEAN _search_find(PHEXVIEW HexView, HWND hWnd, SIZE_T start, SIZE_T end, LPCWSTR text)
{
    NMHEXSEARCH search = { 0 };
    search.nSize    = HexView->nSearchSize;
    search.pSearch  = HexView->pSearchData;
    search.start    = start;
    search.end      = end;
    BOOLEAN isSearch = (BOOLEAN)HexView_SendNotify(hWnd, HVN_SEARCH, (LPNMHDR)&search);
    if ( isSearch )
    {
        HexView_Jmp_pos(HexView, hWnd, search.pos, search.pos + HexView->nSearchSize);
    }
    else
    {
        // 没有搜索到数据
        _search_msgbox(HexView, hWnd, text, start);
    }
    return isSearch;
}

void HexView_Search(PHEXVIEW HexView, HWND hWnd)
{
    HEXSEARCH arg = { 0 };
    arg.hParent = hWnd;
    arg.szCaption = L"搜索";
    arg.szTips = L"";
    arg.listText = HexView->pNode;
    arg.nMode = HexView->nSearchMode;
    arg.windowType = HEXSEARCH_WINDOWTYPE_HEX;

    int ret = HexView_Search_Dialog(&arg);

    if ( !ret || !arg.pRet ) return; // 对话框取消了搜索

    // 走到这就是搜索框输入了搜索的数据

    // 先枚举一下链表, 看看有没有重复项, 有的话把重复项拿出来放到第一个位置
    if ( !HexView_AdjustListOrder(&HexView->pNode, arg.pRet) )
    {
        // 链表里没有重复项, 那就新建一个节点
        // 没有相同的数据, 那就把这个数据放到第一个节点
        HexView->pNode = HexView_NewNode(arg.pRet, HexView->pNode);
    }

    HexView->pSearchText = arg.pRet;
    HexView->nSearchMode = arg.nMode;
    // 把文本转换成需要搜索的数据
    switch ( arg.nMode )
    {
    case 0: // 十六进制
        HexView_Search_HexToBin(HexView);
        break;
    case 1: // ansi字符串
        HexView_Search_ToAnsi(HexView);
        break;
    case 2: // 10进制
        HexView_Search_10ToBin(HexView);
        break;
    case 3: // Unicode字符串
        HexView_Search_ToUnicode(HexView);
        break;
    case 4: // 单精度浮点数
        HexView_Search_FloatToBin(HexView);
        break;
    case 5: // 双精度浮点数
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
    // 没有搜索到数据

    LPCWSTR mode = L"";

    switch ( HexView->nSearchMode)
    {
    case 1: // ansi字符串
        mode = L"ANSI 字符串";
        break;
    case 2: // 10进制
        mode = L"10进制";
        break;
    case 3: // Unicode字符串
        mode = L"Unicode字符串";
        break;
    case 4: // 单精度浮点数
        mode = L"单精度浮点数";
        break;
    case 5: // 双精度浮点数
        mode = L"双精度浮点数";
        break;
    default:
        mode = L"十六进制";
        break;
    }

    NMHVDISPINFO DispInfo = { 0 };
    DispInfo.Item.Mask = HVIF_ADDRESS;
    DispInfo.Item.NumberOfItem = start;
    HexView_SendNotify(hWnd, HVN_GETDISPINFO, (LPNMHDR)&DispInfo);

    size_t len = wcslen(HexView->pSearchText) + 260;
    LPWSTR dbg = (LPWSTR)HexViewAlloc(len * sizeof(wchar_t));
    swprintf_s(dbg, len,
               L"搜索模式: %s\r\n"
               L"搜索文本: \"%s\"\r\n"
               L"从 0x%016llX 开始%s搜索\r\n\r\n"
               L"未搜索到匹配数据", mode, HexView->pSearchText, DispInfo.Item.Address, text);
    MessageBoxW(hWnd, dbg, L"没有搜索到数据", 0);
    HexViewFree(dbg);
}
void HexView_Search_Next(PHEXVIEW HexView, HWND hWnd)
{
    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);
    start += 1;
    if ( start > HexView->TotalItems )
        start = 0;


    _search_find(HexView, hWnd, start, HexView->TotalItems, L"向下");
}
void HexView_Search_Prev(PHEXVIEW HexView, HWND hWnd)
{
    SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
    SIZE_T end = max(HexView->SelectionStart, HexView->SelectionEnd);

    start -= 1;
    if ( start > HexView->TotalItems )
        start = HexView->TotalItems - 1;

    _search_find(HexView, hWnd, start, 0, L"向上");
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
    HEXJMP arg      = { 0 };
    arg.hParent     = hWnd;
    arg.szCaption   = L"跳转到...";
    arg.listText    = HexView->pNodeJmp;
    arg.nMode       = HexView->nJmpMode;
    arg.pos         = start;
    arg.isAsm       = false;

    int ret = HexView_Jmp_Dialog(&arg);

    if ( !ret || !arg.pRet ) return; // 对话框取消了搜索

    // 走到这就是搜索框输入了搜索的数据

    // 先枚举一下链表, 看看有没有重复项, 有的话把重复项拿出来放到第一个位置
    if ( !HexView_AdjustListOrder(&HexView->pNodeJmp, arg.pRet) )
    {
        // 链表里没有重复项, 那就新建一个节点
        // 没有相同的数据, 那就把这个数据放到第一个节点
        HexView->pNodeJmp = HexView_NewNode(arg.pRet, HexView->pNodeJmp);
    }

    int mode = LOWORD(arg.nMode);
    SIZE_T retPos = (SIZE_T)arg.pos;
    SIZE_T pos = 0;
    if ( mode == 0 )    // 文件开始
    {
        pos = retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0 ) ? HexView->TotalItems - 1 : 0;
    }
    else if ( mode == 1 )   // 当前位置
    {
        pos = start + retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0) ? HexView->TotalItems - 1 : 0;

    }
    else if ( mode == 2 )   // 当前位置往上
    {
        pos = start - retPos;
        if ( pos >= HexView->TotalItems )
            pos = ( retPos > 0 ) ? 0 : HexView->TotalItems - 1;
    }
    else if ( mode == 3 )   // 文件结束
    {
        pos = HexView->TotalItems - retPos;
        if ( pos > HexView->TotalItems )
            pos = ( retPos > 0 ) ? 0 : HexView->TotalItems - 1;
    }

    HexView->nJmpMode = arg.nMode;
    HexView_Jmp_pos(HexView, hWnd, pos, pos + 1);
}
//
//void HexView_Asm(PHEXVIEW HexView, HWND hWnd)
//{
//    if ( IsWindow(HexView->hAsm) )
//        return;
//    NMHEXCOPYDATA arg = { 0 };
//    arg.nSize = HexView->TotalItems;
//    arg.pBuf = HexViewAlloc(arg.nSize, true);
//    if ( HexView_SendNotify(hWnd, HVN_COPYDATA, (LPNMHDR)&arg) )
//    {
//        SIZE_T start = min(HexView->SelectionStart, HexView->SelectionEnd);
//        ASMVIEW_LOAD asm_arg = { 0 };
//        asm_arg.hParent = hWnd;
//        asm_arg.szCaption = L"汇编查看器";
//        asm_arg.pData = arg.pBuf;
//        asm_arg.nSize = arg.nSize;
//        asm_arg.address = arg.Address;
//        asm_arg.offset = start;
//        asm_arg.pShowMode = &HexView->asm_ShowMode;
//        asm_arg.hFont = HexView->hFont;
//
//        HexView->hAsm = AsmView_Load(&asm_arg);
//        if ( !HexView->hAsm )
//        {
//            MessageBoxW(hWnd, L"打开汇编查看器失败", L"错误", 0);
//        }
//    }
//    else
//    {
//        MessageBoxW(hWnd, L"获取数据失败, 无法查看汇编", L"错误", 0);
//    }
//    HexViewFree(arg.pBuf);
//}

