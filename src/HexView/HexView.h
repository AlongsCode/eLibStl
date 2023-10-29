#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "HexView_Function.h"

#define WC_HEXVIEWA              "扩大福QQ121007124"
#define WC_HEXVIEWW              L"扩大福QQ121007124"

#ifdef UNICODE
#define WC_HEXVIEW              WC_HEXVIEWW
#else
#define WC_HEXVIEW              WC_HEXVIEWA
#endif

#define HVM_FIRST               0x3C00

#define HVM_SETTEXTCOLOR        (HVM_FIRST + 0)     // 设置文本颜色, wParam = 是否重画, lParam = 文本颜色, 返回设置前的颜色
#define HVM_GETTEXTCOLOR        (HVM_FIRST + 1)     // 获取文本颜色, 忽略 wParam和lParam, 返回文本颜色
#define HVM_SETBKCOLOR          (HVM_FIRST + 2)     // 设置背景颜色, wParam = 是否重画, lParam = 背景颜色, 返回设置前的颜色
#define HVM_GETBKCOLOR          (HVM_FIRST + 3)     // 获取背景颜色, 忽略 wParam和lParam, 返回背景颜色
#define HVM_SETSELBKCOLOR       (HVM_FIRST + 4)     // 设置选中背景颜色, wParam = 是否重画, lParam = 选中背景颜色, 返回设置前的颜色
#define HVM_GETSELBKCOLOR       (HVM_FIRST + 5)     // 获取选中背景颜色, 忽略 wParam和lParam, 返回选中背景颜色
#define HVM_SETMODIFIEDCOLOR    (HVM_FIRST + 6)     // 设置已修改文本颜色, wParam = 是否重画, lParam = 已修改文本颜色, 返回设置前的颜色
#define HVM_GETMODIFIEDCOLOR    (HVM_FIRST + 7)     // 获取已修改文本颜色, 忽略 wParam和lParam, 返回已修改文本颜色

#define HVM_SETEXTENDEDSTYLE    (HVM_FIRST + 20)    // 设置组件扩展样式, wParam = 是否重画, lParam = 组件扩展样式, 返回设置前的样式
#define HVM_GETEXTENDEDSTYLE    (HVM_FIRST + 21)    // 获取组件扩展样式, 忽略 wParam和lParam, 返回组件扩展样式
#define HVM_SETITEMCOUNT        (HVM_FIRST + 22)    // 设置项目数, wParam = 是否重画, lParam = 项目数, 返回是否成功
#define HVM_GETITEMCOUNT        (HVM_FIRST + 23)    // 获取项目数, 忽略 wParam和lParam, 返回项目数
#define HVM_SETSEL              (HVM_FIRST + 24)    // 设置选中区域, wParam = 是否重画, lParam = BYTERANGE结构, 返回是否成功
#define HVM_GETSEL              (HVM_FIRST + 25)    // 获取选中区域, 忽略 wParam, lParam = BYTERANGE结构, 接收结果, 返回是否成功
#define HVM_SETCOLUMNCOUNT      (HVM_FIRST + 26)    // 设置列数, wParam = 是否重画, lParam = 列数, 返回是否成功
#define HVM_GETCOLUMNCOUNT      (HVM_FIRST + 27)    // 获取列数, 忽略 wParam和lParam, 返回列数


#define HVN_GETDISPINFO         (WMN_FIRST - 0)     // 获取数据, NMHVDISPINFO 结构
#define HVN_ITEMCHANGING        (WMN_FIRST - 1)     // 数据被改变, NMHEXVIEW 结构
#define HVN_ITEMSEL             (WMN_FIRST - 2)     // 选中数据, NMHEXSEL 结构
#define HVN_SEARCH              (WMN_FIRST - 3)     // 搜索数据, NMHEXSEARCH 结构
#define HVN_COPYDATA            (WMN_FIRST - 4)     // 拷贝数据, NMHEXCOPYDATA 结构


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

#define HVS_ADDRESS64           0x0001
#define HVS_READONLY            0x0002

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

typedef LRESULT(CALLBACK* PFN_HEXVIEW_NOTIFY)(HWND, LPNMHDR, LPVOID);

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
    LPBYTE      pSearchData;        // 搜索的数据
    int         nSearchSize;        // 搜索的数据大小
    int         nSearchBufSize;     // 搜索的数据缓冲区大小 大于等于 nSearchSize
    LPWSTR      pSearchText;        // 搜索的文本
    int         nSearchMode;        // 搜索模式, 0=十六进制, 1=ansi字符串, 2=10进制, 3=Unicode字符串, 4=单精度浮点数, 5=双精度浮点数
    PHEX_NODE   pNode;              // 历史搜索的文本链表
    PHEX_NODE   pNodeJmp;           // 跳转历史搜索的文本链表
    int         nJmpMode;           // 跳转模式, 0=从文件开始, 1=当前位置, 2现在位置往上, 3=从文件结束, 高位 = 是否是16进制, 同时接收搜索时选中的模式
    HWND        hAsm;               // 汇编窗口句柄, 如果已经打开就不再打开第二次
    int         asm_ShowMode;       // 汇编显示语法模式, 0=MASM, 0x100=GoAsm, 0x200=Nasm, 0x400=AT, 0x800=IntrinsicMem

    HWND        hWndParent;         // 创建窗口时的父窗口, 不管父窗口怎么改, 都向这个窗口通知消息
    PFN_HEXVIEW_NOTIFY pfnNotify;   // 通知事件, 使用这种方式就不用向父窗口投递通知, 可以省去子类化父窗口的操作
    LPVOID      lpParamNotify;      // 通知事件附加参数

    int         ActiveColumn;       // COLUMN_DATA or COLUMN_VALUE

    SIZE_T      TotalItems;         //
    SIZE_T      NumberOfItem;       //
    UINT        PositionInItem;     // 0 = HINIBBLE; 1 = LONIBBLE

    SIZE_T      SelectionStart;     //
    SIZE_T      SelectionEnd;       //

    DWORD       Flags;              // 
    DWORD       ExStyle;            // 扩展风格

    HFONT       hFont;              // 组件使用的字体

    COLORREF    clrTextSel;         // 文本颜色, 选中的文本颜色, 右边字符用
    COLORREF    clrTextAddress;     // 文本颜色, 左边地址的颜色
    COLORREF    clrText1;           // 文本颜色, 第一个格子的颜色
    COLORREF    clrText2;           // 文本颜色, 第二个格子的颜色
    COLORREF    clrTextSel1;        // 选中文本颜色, 第一个格子的颜色
    COLORREF    clrTextSel2;        // 选中文本颜色, 第二个格子的颜色
    COLORREF    clrTextBackground;  // 文本背景颜色
    COLORREF    clrSelTextBack;     // 选中文本背景颜色
    COLORREF    clrModifiedText;    // 修改过的文本颜色
    COLORREF    clrModifiedTextSel; // 修改过的文本颜色, 选中的颜色
    COLORREF    clrLine;            // 线条颜色, 包括边框色
} HEXVIEW, * PHEXVIEW;

typedef struct _HVITEM {
    UINT Mask;
    UINT State;
    ULONG64 Address;
    SIZE_T NumberOfItem;
    BYTE Value;
} HVITEM, * PHVITEM;

typedef struct _NMHVDISPINFO {
    NMHDR NmHdr;
    HVITEM Item;
} NMHVDISPINFO, * PNMHVDISPINFO;

typedef struct _NMHEXVIEW {
    NMHDR NmHdr;
    HVITEM Item;
} NMHEXVIEW, * PNMHEXVIEW;

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
} BYTERANGE, * PBYTERANGE;


HWND CreateHexView(DWORD dwExStyle, DWORD dwStyle,
    int x, int y, int nWidth, int nHeight, HWND hWndParent, LONG_PTR id = 0, LPVOID lpParam = 0);

BOOLEAN HexView_BindNotify(HWND hWnd, PFN_HEXVIEW_NOTIFY pfn, LPVOID lpParam);

