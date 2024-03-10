#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "HexView_Function.h"
#include <vector>
#include <string>

#define WC_HEXVIEWA              "扩大福QQ121007124"
#define WC_HEXVIEWW              L"扩大福QQ121007124"

#ifdef UNICODE
#define WC_HEXVIEW              WC_HEXVIEWW
#else
#define WC_HEXVIEW              WC_HEXVIEWA
#endif

#define HVM_FIRST               0x3C00

#define HVM_SETCLRBK                (HVM_FIRST + 0)     // 设置背景颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRBK                (HVM_FIRST + 1)     // 获取背景颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRBK_SEL            (HVM_FIRST + 2)     // 设置选中区域的背景颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRBK_SEL            (HVM_FIRST + 3)     // 获取选中区域的背景颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRLINE              (HVM_FIRST + 4)     // 设置线条颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRLINE              (HVM_FIRST + 5)     // 获取线条颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRMODIFYTEXT        (HVM_FIRST + 6)     // 设置已修改文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRMODIFYTEXT        (HVM_FIRST + 7)     // 获取已修改文本颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRMODIFYTEXT_SEL    (HVM_FIRST + 8)     // 设置选中区域已修改文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRMODIFYTEXT_SEL    (HVM_FIRST + 9)     // 获取选中区域已修改文本颜色, 忽略 wParam和lParam, 返回对应颜色

#define HVM_SETCLRTEXTADDR          (HVM_FIRST + 10)     // 设置左边地址和右边字符的文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXTADDR          (HVM_FIRST + 11)     // 获取左边地址和右边字符的文本颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRTEXTSELCHAR       (HVM_FIRST + 12)     // 设置右边选中时字符的文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXTSELCHAR       (HVM_FIRST + 13)     // 获取右边选中时字符的文本颜色, 忽略 wParam和lParam, 返回对应颜色

#define HVM_SETCLRTEXT1             (HVM_FIRST + 14)     // 设置第一个格子文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXT1             (HVM_FIRST + 15)     // 获取第一个格子文本颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRTEXT2             (HVM_FIRST + 16)     // 设置第二个格子文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXT2             (HVM_FIRST + 17)     // 获取第二个格子文本颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRTEXT1_SEL         (HVM_FIRST + 18)     // 设置第一个格子选中文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXT1_SEL         (HVM_FIRST + 19)     // 获取第一个格子选中文本颜色, 忽略 wParam和lParam, 返回对应颜色
#define HVM_SETCLRTEXT2_SEL         (HVM_FIRST + 20)     // 设置第二个格子选中文本颜色, wParam = 是否重画, lParam = 要设置的颜色, 返回设置前的颜色
#define HVM_GETCLRTEXT2_SEL         (HVM_FIRST + 21)     // 获取第二个格子选中文本颜色, 忽略 wParam和lParam, 返回对应颜色

#define HVM_SETDARKMODE             (HVM_FIRST + 30)     // 设置深色模式, wParam = 是否重画, lParam = 是否设置深色模式
#define HVM_GETDARKMODE             (HVM_FIRST + 31)     // 获取当前视图是否为深色模式

#define HVM_GETCOLOR                (HVM_FIRST + 40)     // 获取当前配色信息, wParam未使用, lParam = HEXVIEW_COLOR 结构指针
#define HVM_SETCOLOR                (HVM_FIRST + 41)     // 设置当前配色信息, wParam是否重画, lParam = HEXVIEW_COLOR 结构指针





#define HVM_SETEXTENDEDSTYLE    (HVM_FIRST + 50)    // 设置组件扩展样式, wParam = 是否重画, lParam = 组件扩展样式, 返回设置前的样式
#define HVM_GETEXTENDEDSTYLE    (HVM_FIRST + 51)    // 获取组件扩展样式, 忽略 wParam和lParam, 返回组件扩展样式
#define HVM_SETITEMCOUNT        (HVM_FIRST + 52)    // 设置项目数, wParam = 是否重画, lParam = 项目数, 返回是否成功
#define HVM_GETITEMCOUNT        (HVM_FIRST + 53)    // 获取项目数, 忽略 wParam和lParam, 返回项目数
#define HVM_SETSEL              (HVM_FIRST + 54)    // 设置选中区域, wParam = 是否重画, lParam = BYTERANGE结构, 返回是否成功
#define HVM_GETSEL              (HVM_FIRST + 55)    // 获取选中区域, 忽略 wParam, lParam = BYTERANGE结构, 接收结果, 返回是否成功
#define HVM_SETCOLUMNCOUNT      (HVM_FIRST + 56)    // 设置列数, wParam = 是否重画, lParam = 列数, 返回是否成功
#define HVM_GETCOLUMNCOUNT      (HVM_FIRST + 57)    // 获取列数, 忽略 wParam和lParam, 返回列数


#define HVN_GETDISPINFO         (WMN_FIRST - 0)     // 获取数据, NMHVDISPINFO 结构
#define HVN_ITEMCHANGING        (WMN_FIRST - 1)     // 数据被改变, NMHEXVIEW 结构
#define HVN_ITEMSEL             (WMN_FIRST - 2)     // 选中数据, NMHEXSEL 结构
#define HVN_SEARCH              (WMN_FIRST - 3)     // 搜索数据, NMHEXSEARCH 结构
#define HVN_COPYDATA            (WMN_FIRST - 4)     // 拷贝数据, NMHEXCOPYDATA 结构
#define HVN_POPUPMENU           (WMN_FIRST - 5)     // 弹出菜单, NMMENUPOPUP 结构, 返回是否拦截
#define HVN_MENUSELING          (WMN_FIRST - 6)     // 菜单项即将被选择, NMMENUSEL 结构, 返回是否拦截
#define HVN_MENUSELED           (WMN_FIRST - 7)     // 菜单项已经被选择, NMMENUSEL 结构


//
// Mask of an item
//

#define HVIF_ADDRESS            0x0001
#define HVIF_BYTE               0x0002

//
// State of an item
//

#define HVIS_MODIFIED           0x0001

//
// Extended styles
//

#define HVS_ADDRESS64           0x0001  // 64位地址
#define HVS_READONLY            0x0002  // 只读模式
#define HVS_DARMMODE            0x0004  // 深色模式

//
// States of the control
//

#define HVF_FONTCREATED         0x0001
#define HVF_CARETVISIBLE        0x0002
#define HVF_SELECTED            0x0004

#define HVCPY_DEF               0x0000  // 默认复制, 只复制中间的文本, 复制16进制
#define HVCPY_ADDRESS           0x0001  // 复制左边的地址
#define HVCPY_CHAR              0x0002  // 复制右边的字符
#define HVCPY_HEX10             0x0004  // 复制10进制
#define HVCPY_ALL               HVCPY_ADDRESS | HVCPY_CHAR  // 复制16进制 + 地址 + 字符

#define HVCPY_HEX_1             0x0100  // 复制16进制, 不用空格分隔
#define HVCPY_HEX_C             0x0200  // 复制16进制, 用C语言的格式, 0xFF, 
#define HVCPY_HEX_ASM           0x0300  // 复制16进制, 用汇编的格式, 0FFh, 
#define HVCPY_HEX10_1           0x0400  // 复制10进制, 字节没有字符分隔


enum Column {
    COLUMN_DATA = 1,
    COLUMN_VALUE
};

typedef struct _HEXVIEW_COLOR
{
    COLORREF    clrBack;            // 文本背景颜色
    COLORREF    clrBackSel;         // 选中背景颜色
    COLORREF    clrLine;            // 线条颜色, 包括边框色
    COLORREF    clrModifyText;      // 修改过的文本颜色
    COLORREF    clrModifyTextSel;   // 修改过的文本颜色, 选中的颜色

    COLORREF    clrTextAddress;     // 文本颜色, 左边地址的颜色
    COLORREF    clrTextSelChar;     // 文本颜色, 选中的文本颜色, 右边字符用

    COLORREF    clrText1;           // 文本颜色, 第一个格子的颜色
    COLORREF    clrText2;           // 文本颜色, 第二个格子的颜色
    COLORREF    clrTextSel1;        // 选中文本颜色, 第一个格子的颜色
    COLORREF    clrTextSel2;        // 选中文本颜色, 第二个格子的颜色

}HEXVIEW_COLOR, *PHEXVIEW_COLOR, *LPHEXVIEW_COLOR;

typedef struct _HEXVIEW {
    int         Line1;              // Start of the COLUMN_DATA
    int         Line2;              // Start of the COLUMN_VALUE

    int         VisibleLines;       //
    LONG_PTR    TotalLines;         //
    int         VisibleChars;       //
    int         LongestLine;        //

    LONG_PTR    VscrollPos;         //
    LONG_PTR    VscrollMax;         //
    int         HscrollPos;         //
    int         HscrollMax;         //

    int         HeightChar;         //
    int         WidthChar;          //
    int         HeightView;         //
    int         WidthView;          //

    int         ColumnCount;        // 显示多少列, 默认设置16
    int         ColumnSecond;       // 右边列的位置, 这个影响右边字符的位置

    HWND        hAsm;               // 汇编窗口句柄, 如果已经打开就不再打开第二次
    int         asm_ShowMode;       // 汇编显示语法模式, 0=MASM, 0x100=GoAsm, 0x200=Nasm, 0x400=AT, 0x800=IntrinsicMem
    WNDPROC     pfnNotify;          // 通知函数, 不需要子类化父窗口就可以接收WM_NOTIFY通知, 处理方式和处理WM_NOTIFY消息一样

    int         ActiveColumn;       // COLUMN_DATA or COLUMN_VALUE

    SIZE_T      TotalItems;         //
    SIZE_T      NumberOfItem;       //
    UINT        PositionInItem;     // 0 = HINIBBLE; 1 = LONIBBLE

    SIZE_T      SelectionStart;     //
    SIZE_T      SelectionEnd;       //

    DWORD       Flags;              // 
    DWORD       ExStyle;            // 扩展风格

    HFONT       hFont;              // 组件使用的字体

    HEXVIEW_COLOR clr;              // 配色信息


    LPVOID      pBoxData;           // 对话框的结构指针
} HEXVIEW, *PHEXVIEW;

typedef struct _HVITEM {
    UINT Mask;
    UINT State;
    ULONG64 Address;
    SIZE_T NumberOfItem;
    BYTE Value;
} HVITEM, *PHVITEM;

typedef struct _NMHVDISPINFO {
    NMHDR NmHdr;
    HVITEM Item;
} NMHVDISPINFO, *PNMHVDISPINFO;

typedef struct _NMHEXVIEW {
    NMHDR NmHdr;
    HVITEM Item;
} NMHEXVIEW, * PNMHEXVIEW;

typedef struct _NMMENUPOPUP {
    NMHDR NmHdr;
    HMENU hMenu;
    POINT pt;
} NMMENUPOPUP, * PNMMENUPOPUP;

typedef struct _NMMENUSEL {
    NMHDR NmHdr;
    LONG_PTR id;
} NMMENUSEL, * PNMMENUSEL;

typedef struct _NMHEXSEL
{
    NMHDR  NmHdr;
    SIZE_T Min;
    SIZE_T Max;
    int    isSel;
} NMHEXSEL, * PNMHEXSEL;
typedef struct _NMHEXSEARCH
{
    NMHDR   NmHdr;
    LPBYTE  pSearch;    // 要搜索的数据
    SIZE_T  nSize;      // 搜索的数据大小
    SIZE_T  start;      // 开始搜索的位置
    SIZE_T  end;        // 结束搜索的位置, 倒序搜索则为0
    SIZE_T  pos;        // 查找到的位置, 接收通知的地方填写
} NMHEXSEARCH, * PNMHEXSEARCH;
typedef struct _NMHEXCOPYDATA
{
    NMHDR   NmHdr;
    LPVOID  pBuf;       // 缓冲区地址
    SIZE_T  nSize;      // 缓冲区尺寸
    ULONG64 Address;    // 接收数据起始地址, 显示汇编使用这个地址
} NMHEXCOPYDATA, * PNMHEXCOPYDATA;

typedef struct _BYTERANGE {
    SIZE_T Min;
    SIZE_T Max;
} BYTERANGE, *PBYTERANGE;

HWND CreateHexView(DWORD dwExStyle, DWORD dwStyle,
                   int x, int y, int nWidth, int nHeight, HWND hWndParent, LONG_PTR id = 0, LPVOID lpParam = 0);

BOOLEAN HexView_BindNotify(HWND hWnd, WNDPROC pfn);

