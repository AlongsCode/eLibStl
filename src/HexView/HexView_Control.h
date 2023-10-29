#include "HexView.h"
#include <vector>

// 版本号, 两个字节记录主版本和次版本号, 两个字节记录日期
#define HEXVIEW_VERSION MAKELONG(MAKEWORD(1, 0), MAKEWORD(10, 15))

#define HEXVIEW_PROP_BORDER                 0   // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
#define HEXVIEW_PROP_TEXTCOLOR              1   // 文本颜色
#define HEXVIEW_PROP_TEXTBACKCOLOR          2   // 文本背景颜色
#define HEXVIEW_PROP_BACKCOLOR              3   // 背景颜色
#define HEXVIEW_PROP_FONT                   4   // 字体属性
#define HEXVIEW_PROP_EDITABLE               5  // 允许编辑, 本属性指定是否允许编辑


#define HEXVIEW_NAMESPACE _hexview
#define HEXVIEW_NAMESPACE_BEGIN namespace HEXVIEW_NAMESPACE {
#define HEXVIEW_NAMESPACE_END }

HEXVIEW_NAMESPACE_BEGIN
typedef struct CONTROL_STRUCT_BASE
{
    LONG                controlType;    // 组件类型, 绑定数据都是一样的操作, 就根据这个确定是什么组件了, CONTROLTYPE_ 开头常量
    WNDPROC             oldProc;        // 窗口原过程
    HFONT               hFont;          // 字体
    HWND                hDesignWnd;     // 如果blInDesignMode为真, 则hDesignWnd是设计窗口的窗口句柄, 否则为0
    HWND                hWndParent;     // 组件父窗口句柄
    HWND                hWnd;           // 组件句柄
    DWORD               hUnit;          // 易语言返回的一个CWnd类指针
    UINT                id;             // 组件的ID
    DWORD               dwWinFormID;    // 本窗口单元所在窗口及本身的ID, 用作通知到系统
    DWORD               dwUnitID;       // 本窗口单元所在窗口及本身的ID, 用作通知到系统。
    BOOL                blInDesignMode; // 是否被易语言IDE调用以进行可视化设计, 运行时为假
    LONG                flags;          // 组件的一些标志, 自己组件自己定义
    DWORD               style;          // 组件的样式, 在 WM_STYLECHANGED 里修改
    DWORD               styleEx;        // 组件的扩展样式, 在 WM_STYLECHANGED 里修改
    DWORD               styleCtl;       // 组件专属扩展样式

}*PCONTROL_STRUCT_BASE;

// 
typedef struct _HEXVIEW_PROPERTY : CONTROL_STRUCT_BASE
{
    LONG            version;                // 确定版本号的一个标志
    LONG            border;                 // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
    LONG            TextColor;              // 文本颜色
    LONG            TextBackColor;          // 文本背景颜色
    LONG            BackColor;              // 背景颜色
    BOOL            Editable;               // 允许编辑, 本属性指定是否允许编辑
    LONG            fontSize;               // 字体属性尺寸, 为0则不写出数据
    LOGFONTA        font;                   // 字体属性
    ULONG64         pAddress;               // 显示的地址
    std::vector<BYTE>* data;                // 显示的数据
    std::vector<BYTE>* modi;                // 指定字节是否被修改
}HEXVIEW_PROPERTY, * PHEXVIEW_PROPERTY, * LPHEXVIEW_PROPERTY;



HEXVIEW_NAMESPACE_END