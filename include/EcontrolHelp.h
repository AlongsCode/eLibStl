//组件库需用通用函数引入此头文件
#include"ElibHelp.h"
#include <CommCtrl.h>
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")


std::vector<unsigned char> GetDataFromHBIT(HBITMAP hBitmap);
std::wstring MyInputBox(std::wstring  title);
//转发消息给子窗口
bool ForwardMessageToComponent(HWND componentHandle, HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//子类化窗口操作，保存旧回调确并保父窗口不会重复子类化
WNDPROC SubclassParent(HWND hwnd, WNDPROC newProc);

typedef struct CONTROL_STRUCT_BASE
{
	WNDPROC             oldProc;        // 窗口原过程, 一般情况下自己创建的组件都需要子类化, 这里记录组件子类化的原过程
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

// 组件统一处理消息函数, 会记录组件的一些基础信息, 返回组件base结构指针


struct EFONTDATA
{
	HFONT m_hFont;
	LOGFONTA m_data;
	EFONTDATA()
	{
		memset(this, 0, sizeof(EFONTDATA));
	}
};