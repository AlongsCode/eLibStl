//#include"ElibHelp.h"
//#include<unordered_map>
//static std::unordered_map<HWND, WNDPROC> g_hwndOldWndProcMap;
//
//
//static LRESULT CALLBACK OldWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//	switch (msg) {
//		// 处理WM_NCDESTROY消息，恢复窗口过程函数
//	case WM_NCDESTROY: {
//		HWND hwndNew = (HWND)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//		WNDPROC lpfnOldWndProc = g_hwndOldWndProcMap[hwndNew];
//		SetWindowLongPtr(hwndNew, GWLP_WNDPROC, (LONG_PTR)lpfnOldWndProc);
//		g_hwndOldWndProcMap.erase(hwndNew);
//		break;
//	}
//	}
//	return CallWindowProc(g_hwndOldWndProcMap[hwnd], hwnd, msg, wParam, lParam);
//}
//
//static bool Windows2UnicodeWindow(HWND hwnd) {
//	HWND hwndParent = GetParent(hwnd);
//	WCHAR szClassName[MAX_PATH];
//	GetClassNameW(hwnd, szClassName, MAX_PATH);
//	WCHAR szWindowText[MAX_PATH];
//	GetWindowTextW(hwnd, szWindowText, MAX_PATH);
//	HWND hwndNew = CreateWindowW(szClassName, szWindowText, WS_VISIBLE, 0, 0, 0, 0, hwndParent, NULL, NULL, NULL);
//	if (hwndNew != NULL) {
//		// 转换窗口过程函数
//		WNDPROC lpfnOldWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
//		SetWindowLongPtr(hwndNew, GWLP_WNDPROC, (LONG_PTR)OldWndProc);
//		// 将新旧窗口的映射关系保存到映射表中
//		g_hwndOldWndProcMap[hwndNew] = lpfnOldWndProc;
//		// 将lpCreateParams指向旧窗口的窗口过程地址
//		CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//		pCreateStruct->lpCreateParams = (LPVOID)hwndNew;
//		// 将新窗口的句柄传递给旧窗口的父窗口
//		SetParent(hwndNew, hwndParent);
//		ShowWindow(hwndNew, SW_SHOW);
//		// 将新窗口的句柄保存到旧窗口的额外窗口内存中
//		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pCreateStruct);
//		return true;
//	}
//	return false;
//}
//
//EXTERN_C void Fn_ansiwindow_to_unicodewindow(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
//{
//
//	pRetData->m_bool = Windows2UnicodeWindow(reinterpret_cast<HWND>(pArgInf->m_int));
//}
//
//static ARG_INFO Args[] =
//{
//	{
//		/*name*/    "窗口句柄",
//		/*explain*/ (""),
//		/*bmp inx*/ 0,
//		/*bmp num*/ 0,
//		/*type*/    SDT_INT,
//		/*default*/ 0,
//		/*state*/   0,
//	}
//};
//FucInfo ansiwindow_to_unicodewindow = { {
//		/*ccname*/  ("窗口转W版"),
//		/*egname*/  ("AW2WW"),
//		/*explain*/ ("将窗口转换为W版窗口"),
//		/*category*/10,
//		/*state*/   NULL,
//		/*ret*/     SDT_BOOL,
//		/*reserved*/NULL,
//		/*level*/   LVL_HIGH,
//		/*bmp inx*/ 0,
//		/*bmp num*/ 0,
//		/*ArgCount*/1,
//		/*arg lp*/  Args,
//	} ,Fn_ansiwindow_to_unicodewindow ,"Fn_ansiwindow_to_unicodewindow" };
