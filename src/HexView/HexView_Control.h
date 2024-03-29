#include "HexView.h"
#include <vector>

// 版本号, 两个字节记录主版本和次版本号, 两个字节记录日期
#define HEXVIEW_VERSION MAKELONG(MAKEWORD(1, 0), MAKEWORD(10, 15))

#define HEXVIEW_PROP_BORDER                 0   // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
#define HEXVIEW_PROP_EDITABLE               1   // 允许编辑, 本属性指定是否允许编辑
#define HEXVIEW_PROP_COLUMNCOUNT            2   // 列数
#define HEXVIEW_PROP_IS64ADDR               3   // 是否使用64位地址显示
#define HEXVIEW_PROP_ADDRESS                4   // 显示在左边的地址
#define HEXVIEW_PROP_ISDARK                 5   // 是否使用深色模式
#define HEXVIEW_PROP_COLOR                  6   // 配色信息
#define HEXVIEW_PROP_FONT                   7   // 字体属性
#define HEXVIEW_PROP_ITEMCOUNT              8   // 项目数
#define HEXVIEW_PROP_OWNERDATA              9   // 纯虚项目


#define HEXVIEW_EVENT_ITEMCHANGED           0   // 项目被修改, 3个参数,项目索引,修改后,修改前, 返回是否允许修改, 虚项目有特别处理
#define HEXVIEW_EVENT_SHOWINFO              1   // 即将显示, 4个参数, 项目索引,&项目值,&是否被修改,&显示的地址
#define HEXVIEW_EVENT_SEARCH                2   // 搜索项目, 5个参数, 起始位置, 结束位置,被搜索数据指针,被搜索数据尺寸,&找到位置
#define HEXVIEW_EVENT_POPUPMENU             3   // 即将弹出菜单, 1个参数, 菜单句柄, 返回是否允许弹出菜单
#define HEXVIEW_EVENT_MENUSELING            4   // 菜单即将选择, 1个参数, 菜单id, 返回是否继续执行
#define HEXVIEW_EVENT_MENUSELED             5   // 菜单被选择, 1个参数, 菜单id


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
    BOOL            Editable;               // 允许编辑, 本属性指定是否允许编辑
    LONG            columnCount;            // 列数
    BOOL            is64Address;            // 是否使用64位地址显示
    ULONG64         pAddress;               // 显示的地址
    BOOL            isDark;                 // 是否是深色模式
    BOOL            bOwnerData;             // 纯虚项目
    LONG            size;                   // 项目数
    LONG            clrSize;                // 配色占用的尺寸, 如果有新增颜色信息, 可以根据这个成员判断版本
    HEXVIEW_COLOR   clr;

    LONG            fontSize;               // 字体属性尺寸, 为0则不写出数据
    LOGFONTA        font;                   // 字体属性
    char            addr_buf[50];           // 显示的地址文本, 给易语言属性那显示用的
    std::vector<BYTE>* data;                // 显示的数据
    std::vector<bool>* modi;                // 指定字节是否被修改
}HEXVIEW_PROPERTY, * PHEXVIEW_PROPERTY, * LPHEXVIEW_PROPERTY;

inline PHEXVIEW_PROPERTY GetHexViewData(HWND hWnd)
{
    return (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
}
inline PHEXVIEW_PROPERTY SetHexViewData(HWND hWnd, PHEXVIEW_PROPERTY pData)
{
    return (PHEXVIEW_PROPERTY)SetWindowLongPtrW(hWnd, GWLP_USERDATA, (ULONG_PTR)pData);
}

bool HexView_Dialog_Color(PHEXVIEW_PROPERTY pData);


HEXVIEW_NAMESPACE_END