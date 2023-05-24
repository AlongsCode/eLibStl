//#include"ElibHelp.h"
//#include<unordered_map>
//static std::unordered_map<HWND, WNDPROC> g_hwndOldWndProcMap;
//
//
//static LRESULT CALLBACK OldWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//	switch (msg) {
//		// ����WM_NCDESTROY��Ϣ���ָ����ڹ��̺���
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
//		// ת�����ڹ��̺���
//		WNDPROC lpfnOldWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
//		SetWindowLongPtr(hwndNew, GWLP_WNDPROC, (LONG_PTR)OldWndProc);
//		// ���¾ɴ��ڵ�ӳ���ϵ���浽ӳ�����
//		g_hwndOldWndProcMap[hwndNew] = lpfnOldWndProc;
//		// ��lpCreateParamsָ��ɴ��ڵĴ��ڹ��̵�ַ
//		CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//		pCreateStruct->lpCreateParams = (LPVOID)hwndNew;
//		// ���´��ڵľ�����ݸ��ɴ��ڵĸ�����
//		SetParent(hwndNew, hwndParent);
//		ShowWindow(hwndNew, SW_SHOW);
//		// ���´��ڵľ�����浽�ɴ��ڵĶ��ⴰ���ڴ���
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
//		/*name*/    "���ھ��",
//		/*explain*/ (""),
//		/*bmp inx*/ 0,
//		/*bmp num*/ 0,
//		/*type*/    DATA_TYPE::SDT_INT,
//		/*default*/ 0,
//		/*state*/   0,
//	}
//};
//FucInfo ansiwindow_to_unicodewindow = { {
//		/*ccname*/  ("����תW��"),
//		/*egname*/  ("AW2WW"),
//		/*explain*/ ("������ת��ΪW�洰��"),
//		/*category*/10,
//		/*state*/   NULL,
//		/*ret*/     DATA_TYPE::SDT_BOOL,
//		/*reserved*/NULL,
//		/*level*/   LVL_HIGH,
//		/*bmp inx*/ 0,
//		/*bmp num*/ 0,
//		/*ArgCount*/1,
//		/*arg lp*/  Args,
//	} ,Fn_ansiwindow_to_unicodewindow ,"Fn_ansiwindow_to_unicodewindow" };
