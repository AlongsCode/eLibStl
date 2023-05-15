#include<windows.h>
#include<CommCtrl.h>
namespace elibstl {
	HWND g_hDebugEdit = NULL;/*原版调试框*/
	HWND g_hDebugEditW = NULL;/*调试框*/
	HWND g_hPTab = NULL;/*调试框选择夹*/
	WNDPROC g_Old_WndTab = nullptr;/*选择夹原回调*/
	WNDPROC g_Old_WndEdit = nullptr;/*选择夹原回调*/
	/*获取当前进程的易语言窗口句柄*/

	/*BOOL CALLBACK EnumWindowsProc_ENewFrame(HWND hwnd, LPARAM lParam) {
		struct EFINDWND
		{
			DWORD m_hProcessID;
			HWND m_RetWnd;
		};
		EFINDWND* data = reinterpret_cast<EFINDWND*>(lParam);
		DWORD dwProcessID = NULL;
		GetWindowThreadProcessId(hwnd, &dwProcessID);
		WCHAR szClassName[MAX_PATH + 1]{ 0 };
		GetClassNameW(hwnd, szClassName, MAX_PATH);

		if (dwProcessID == data->m_hProcessID && wcscmp(szClassName, L"ENewFrame") == 0) {
			data->m_RetWnd = hwnd;
			return false;
		}
		else
			return true;
	}*/

	static HWND GetThisWindow()
	{
		HWND hMainWnd = GetForegroundWindow(); // 获取当前前台窗口的句柄
		DWORD dwCurrentProcessId = GetCurrentProcessId(); // 获取当前进程ID
		DWORD dwWindowProcessId;
		do {
			dwWindowProcessId = 0;
			GetWindowThreadProcessId(hMainWnd, &dwWindowProcessId);
			if (dwWindowProcessId == dwCurrentProcessId) {
				// 找到当前进程的主窗口顶级窗口
				break;
			}
			hMainWnd = GetParent(hMainWnd); // 获取父窗口
		} while (hMainWnd != NULL);
		return hMainWnd;

		/*auto hProcessID = GetCurrentProcessId();
		if (hProcessID == NULL)
			return NULL;
		struct EFINDWND
		{
			DWORD m_hProcessID;
			HWND m_RetWnd;
			EFINDWND(DWORD hProcessID, HWND RetWnd) {
				m_hProcessID = hProcessID;
				m_RetWnd = RetWnd;
			}
		};
		EFINDWND eFindWindow(hProcessID, NULL);
		if (EnumWindows(&EnumWindowsProc_ENewFrame, reinterpret_cast<LPARAM> (&eFindWindow))) {
			return NULL;
		}
		else
		{
			return eFindWindow.m_RetWnd;
		}*/
	}

	static HWND GetEdebugEdit() {
		auto hEWND = GetThisWindow();
		if (hEWND == NULL)
		{
			return NULL;
		}
		auto hWnd = FindWindowExW(hEWND, 0, L"AfxControlBar42s", L"状态夹");
		if (hWnd == NULL)
		{
			return NULL;
		}
		hWnd = GetDlgItem(hWnd, 130);
		if (hWnd == NULL)
		{
			return NULL;
		}
		hWnd = FindWindowExW(hWnd, 0, L"#32770", NULL);
		if (hWnd == NULL)
		{
			return NULL;
		}
		hWnd = FindWindowExW(hWnd, 0, L"SysTabControl32", NULL);
		if (hWnd == NULL)
		{
			return NULL;
		}
		return GetDlgItem(hWnd, 1011);
	}
	//HHOOK g_hookHandle = NULL;  // 全局钩子句柄

	//LRESULT CALLBACK EditHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	//	if (nCode >= 0) {
	//		// 解析钩子消息
	//		MSG* pMsg = reinterpret_cast<MSG*>(lParam);
	//		if (pMsg->message == WM_KEYDOWN) {
	//			// 处理键盘按键消息
	//			if (pMsg->wParam == VK_RETURN) {
	//				// 用户按下回车键
	//			}
	//		}
	//	}
	//	// 继续传递钩子消息给下一个钩子或目标窗口
	//	return CallNextHookEx(g_hookHandle, nCode, wParam, lParam);
	//}
	///*Hook调试框*/
	//void SetEditHook(HWND hWndEdit) {
	//	// 卸载之前的钩子
	//	UnhookWindowsHookEx(g_hookHandle);
	//	// 设置新的钩子
	//	DWORD dwThreadId = GetWindowThreadProcessId(hWndEdit, NULL);
	//	g_hookHandle = SetWindowsHookEx(WH_GETMESSAGE, EditHookProc, NULL, dwThreadId);
	//	if (g_hookHandle == NULL) {
	//	}
	//}
	///*UnHook调试框*/
	//void UnsetEditHook() {
	//	// 卸载钩子
	//	if (g_hookHandle != NULL) {
	//		UnhookWindowsHookEx(g_hookHandle);
	//		g_hookHandle = NULL;
	//	}
	//}


	/*选择夹回调*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
		if (Msg == WM_NOTIFY) {
			HWND hwndFrom = reinterpret_cast<LPNMHDR>(lParam)->hwndFrom;
			/*如果来源对象为调试框的选项卡*/
			if (hwndFrom == g_hPTab) {
				UINT code = reinterpret_cast<LPNMHDR>(lParam)->code;
				if (code == TCN_SELCHANGE) {
					auto currentTab = SendMessageW(hwndFrom, TCM_GETCURSEL, 0, 0);
					if (currentTab != 1) {

					}
					else {

					}
				}
			}
		}
		/*任何情况下都不允许原版调试框显示*/
		ShowWindow(g_hDebugEdit, SW_HIDE);
		return CallWindowProcA(g_Old_WndTab, hWnd, Msg, wParam, lParam);

	}

	static LRESULT CALLBACK WndEditProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
		/*转发给调试框W*/
		SendMessageW(g_hDebugEditW, Msg, wParam, lParam);
		return CallWindowProcA(g_Old_WndTab, hWnd, Msg, wParam, lParam);

	}
	void MakeDebugEdit() {
		g_hDebugEdit = GetEdebugEdit();
		if (g_hDebugEdit == NULL)
		{
			//MessageBoxW(0, L"无法获取调试编辑框句柄，Unicode调试框初始化失败！", L"标准模板库提示:", MB_ICONERROR);
			return;
		}
		// 获取原版编辑框的文本长度
		int textLength = GetWindowTextLengthW(g_hDebugEdit);
		if (textLength == 0) {
			return;
		}
		// 获取原版编辑框的文本内容
		wchar_t* buffer = new wchar_t[textLength + 1];
		GetWindowTextW(g_hDebugEdit, buffer, textLength + 1);
		// 获取原版编辑框的位置和大小
		RECT rect;
		if (!GetWindowRect(g_hDebugEdit, &rect)) {
			return;
		}

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int x = rect.left;
		int y = rect.top;

		// 获取原版编辑框的风格
		LONG_PTR style = GetWindowLongPtrW(g_hDebugEdit, GWL_STYLE);
		DWORD dwStyle = static_cast<DWORD>(style);

		//获取原版选项卡的句柄
		auto hParent = GetParent(g_hDebugEdit);

		/*选择夹子类化*/
		if (!g_Old_WndTab)
		{

			g_Old_WndTab = (WNDPROC)SetWindowLongPtrW(GetParent(hParent), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));
			if (g_Old_WndTab)
			{
				/*成功则将选项卡保存置全局变量*/
				g_hPTab = hParent;
			}

		}

		/*子类化原调试框*/
		if (!g_Old_WndEdit)
		{
			g_Old_WndEdit = (WNDPROC)SetWindowLongPtrW(g_hDebugEdit, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndEditProc));

		}

		// 创建新的Unicode编辑框
		HWND hUnicodeEdit = CreateWindowExW(0, L"EDIT", buffer, dwStyle, x, y, width, height, hParent, NULL, NULL, NULL);
		if (hUnicodeEdit == NULL) {
			delete[] buffer;
			return;
		}
		ShowWindow(g_hDebugEdit, SW_HIDE);

		delete[] buffer;

		return;
	}
}