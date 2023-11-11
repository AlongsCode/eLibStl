//#include"EcontrolHelp.h"
//namespace elibstl {
//	/*目录监视类*/
//	class FolderMonitor {
//		// 定义回调监视事件的数据类型
//		using DirectoryChangeCallback = void(__stdcall*)(int eventType, const char* oldFileName, const char* newFileName);
//		// 示例用法
//		static void DirectoryChangeEventHandler(int eventType, const char* oldFileName, const char* newFileName) {
//			// 在这里处理回调事件
//			// eventType 表示事件类型 (1: 创建, 2: 删除, 3: 修改, 4: 重命名)
//			// oldFileName 是原文件名，newFileName 是现文件名
//		}
//		static  DWORD CALLBACK
//			Monitoring_Thread(LPVOID m_hDir) {
//			for (size_t i = 0; i < 1024; i++)
//			{
//				if (m_hDir == INVALID_HANDLE_VALUE || m_hDir == NULL) {
//					return 0;
//				}
//				ReadDirectoryChangesW(目录句柄, _保存监视信息[i], 1024, 真, #FILE_NOTIFY_CHANGE_FILE_NAME ＋ #FILE_NOTIFY_CHANGE_DIR_NAME ＋ #FILE_NOTIFY_CHANGE_ATTRIBUTES ＋ #FILE_NOTIFY_CHANGE_SIZE ＋ #FILE_NOTIFY_CHANGE_LAST_WRITE ＋ #FILE_NOTIFY_CHANGE_LAST_ACCESS ＋ #FILE_NOTIFY_CHANGE_CREATION ＋ #FILE_NOTIFY_CHANGE_SECURITY, 0, _重叠操作, 0)
//			}
//		}
//		HANDLE m_hDir{ INVALID_HANDLE_VALUE };
//		std::string m_dir;
//	public:
//		FolderMonitor() = default;
//		~FolderMonitor() = default;
//		
//		auto Over() {
//		
//		}
//		auto StartMonitoring(std::string_view dir) {
//			Over();//撤消目录监视
//			if (dir.empty())
//			{
//				return false;
//			}
//			m_dir = dir;
//			if (dir.back() != '\\') {
//				m_dir += '\\';
//			}
//
//			m_hDir = CreateFileA(m_dir.data(), GENERIC_READ| GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
//			if (m_hDir == INVALID_HANDLE_VALUE)
//			{
//				return false;
//			}
//			CloseHandle(CreateThread(0, 0, &Monitoring_Thread, m_hDir, 0, 0));
//		}
//	};
//}
//
//static HBITMAP g_hbmp_FolderMonitor = NULL;
//
//static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//
//	switch (uMsg)
//	{
//#ifndef __E_STATIC_LIB
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		BeginPaint(hWnd, &ps);
//		HDC hCDC = CreateCompatibleDC(ps.hdc);
//		SelectObject(hCDC, g_hbmp_FolderMonitor);
//		RECT rc;
//		GetClientRect(hWnd, &rc);
//		FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
//		FrameRect(ps.hdc, &rc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
//		BitBlt(ps.hdc, (rc.right - 24) / 2, (rc.bottom - 24) / 2, 24, 24, hCDC, 0, 0, SRCCOPY);
//		DeleteDC(hCDC);
//		EndPaint(hWnd, &ps);
//		break;
//	}
//#endif
//	}
//
//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
//}
//
//////文件被创建
////static void clinet_callback_con(const char* newFileName) {
////
////	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 1);
////	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
////}
//////数据到达
////static void clinet_callback_get_data(eClinet* pClinet) {
////
////	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 0);
////	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
////}
//////断开连接
////static void clinet_callback_out(eClinet* pClinet) {
////	pClinet->backoff();
////	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 2);
////	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
////}
//static HUNIT WINAPI CreateEplWindow(
//	LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据, 由本窗口单元的ITF_GET_PROPERTY_DATA接口产生, 如果没有数据则为NULL
//	INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸, 如果没有则为0
//	DWORD dwStyle,                      //   预先设置的窗口风格
//	HWND hParentWnd,                    //   父窗口句柄
//	UINT uID,                           //   在父窗口中的ID
//	HMENU hMenu,                        //   未使用
//	INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸
//	DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID, 用作通知到系统
//	HWND hDesignWnd,                    //   如果blInDesignMode为真, 则hDesignWnd提供所设计窗口的窗口句柄
//	BOOL blInDesignMode                 //   说明是否被易语言IDE调用以进行可视化设计, 运行时为假
//)
//{
//#define FOLDERMONITOR L"my_e_FolderMonitor"
//	static INT s_FolderMonitor_cmd[] = { 46,47,48,49 };
//
//
//	static ATOM g_atom_FolderMonitor = NULL;
//	auto Clinet_RegWndClass = []()
//		{
//#ifndef __E_STATIC_LIB
//			g_hbmp_FolderMonitor = (HBITMAP)LoadImageW(g_elibstl_hModule, MAKEINTRESOURCEW(IDB_CLINET_EX), IMAGE_BITMAP, 0, 0, 0);
//#endif
//			WNDCLASSW wc = { sizeof(WNDCLASSW) };
//			wc.lpszClassName = FOLDERMONITOR;
//			wc.hCursor = LoadCursorW(NULL, (PWSTR)IDC_ARROW);
//			wc.lpfnWndProc = WndProc;
//			wc.style = CS_HREDRAW | CS_VREDRAW;
//			wc.cbWndExtra = sizeof(void*);
//			g_atom_FolderMonitor = RegisterClassW(&wc);
//		};
//
//
//
//
//	if (!g_atom_FolderMonitor)
//	{
//		Clinet_RegWndClass();
//	}
//
//	if (!blInDesignMode)
//		dwStyle &= (~WS_VISIBLE);
//	HWND hWnd = CreateWindowExW(
//		0,
//		FOLDERMONITOR,
//		NULL,
//		dwStyle | WS_CHILD | WS_CLIPSIBLINGS,
//		x,
//		y,
//		cx,
//		cy,
//		hParentWnd,
//		hMenu,
//		NULL,
//		NULL
//	);
//	if (!hWnd)
//	{
//		return NULL;
//	}
//
//	//eClinet* pClinet = new eClinet;
//	//pClinet->m_connect_cb = clinet_callback_con;
//	//pClinet->m_backoff_cb = clinet_callback_out;
//	//pClinet->m_data_get_cb = clinet_callback_get_data;
//	/*SetWindowLongPtrW(hWnd, GWL_USERDATA, (LONG_PTR)pClinet);
//	pClinet->m_dwUnitID = dwUnitID;
//	pClinet->m_dwWinFormID = dwWinFormID;*/
//	return elibstl::make_cwnd(hWnd);
//}
//static  BOOL WINAPI NotifyPropertyChanged(HUNIT hUnit, INT nPropertyIndex,
//	PUNIT_PROPERTY_VALUE pValue, PSTR* ppszTipText)    //目前尚未使用
//{
//	return FALSE;//不用重新创建
//}
//static  HGLOBAL WINAPI GetAllPropertyData(HUNIT hUnit)
//{
//
//	return nullptr;
//}
//static  BOOL WINAPI GetPropertyData(HUNIT hUnit, INT nPropertyIndex,
//	PUNIT_PROPERTY_VALUE pValue)
//{
//	return FALSE;
//}
//extern "C" PFN_INTERFACE WINAPI libstl_GetInterface_FolderMonitor(INT nInterfaceNO)
//{
//
//	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)CreateEplWindow :
//		nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged :
//		nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData :
//		nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData :
//		NULL;
//}
//
//
//
//
//
//
//
//
//
///*事件*/
//static
//EVENT_INFO2 s_event[] =
//{
//	/*000*/ {"数据到达", "当服务器端将数据发送过来后，会产生本事件。在本事件的处理子程序中调用“取回数据”方法即可取回本次所收到的数据。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
//	/*001*/ {"连接成功", "当连接服务器端成功后，会产生本事件。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
//	/*002*/ {"连接断开", "当连接被服务器端断开后，会产生本事件。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
//};
//
///*属性*/
//static
//UNIT_PROPERTY s_member[] =
//{
//	// FIXED_WIN_UNIT_PROPERTY,    // 必须加上此宏, 或者直接展开, 这里就展开
//	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束
//
//	/*000*/ {"左边", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
//	/*001*/ {"顶边", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
//	/*002*/ {"宽度", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
//	/*003*/ {"高度", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
//	/*004*/ {"标记", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
//	/*005*/ {"可视", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
//	/*006*/ {"禁止", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
//	/*007*/ {"鼠标指针", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},
//};
//
//namespace elibstl {
//	LIB_DATA_TYPE_INFO Obj_FolderMonitor = {
//		/*m_szName*/			"目录监视",
//		/*m_szEgName*/			"FolderMonitor",
//		/*m_szExplain*/			"监视指定目录以及它的子目录中所有文件的创建修改删除等操作.",
//		/*m_nCmdCount*/			sizeof(s_cmd) / sizeof(s_cmd[0]),
//		/*m_pnCmdsIndex*/		s_cmd,
//		/*m_dwState*/			_DT_OS(__OS_WIN) | LDT_WIN_UNIT | LDT_IS_FUNCTION_PROVIDER ,
//		/*m_dwUnitBmpID*/		IDB_CLINET_EX,
//		/*m_nEventCount*/		3,
//		/*m_pEventBegin*/		s_event,
//		/*m_nPropertyCount*/	sizeof(s_member) / sizeof(s_member[0]),
//		/*m_pPropertyBegin*/	s_member,
//		/*m_pfnGetInterface*/	 libstl_GetInterface_FolderMonitor,
//		/*m_nElementCount*/		0,
//		/*m_pElementBegin*/		NULL,
//	};
//}
//
//
//
//
//
//
////#pragma region clinetcmd
////static ARG_INFO connectArgs[] =
////{
////	{
////		/*name*/    "服务器ip地址",
////		/*explain*/ ("服务器的ip地址"),
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*type*/    SDT_TEXT,
////		/*default*/ 0,
////		/*state*/  ArgMark::AS_NONE,
////	},
////	{
////		/*name*/    "服务器端口号",
////		/*explain*/ ("服务器对应端口号"),
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*type*/    SDT_SHORT,
////		/*default*/ 0,
////		/*state*/   ArgMark::AS_NONE,
////	}
////};
////inline string get_ip_this_a() {
////	WORD wVersionRequested = MAKEWORD(2, 2);
////	WSADATA wsaData;
////	if (WSAStartup(wVersionRequested, &wsaData) != 0)
////		return "";
////	char local[255] = { 0 };
////	gethostname(local, sizeof(local));
////	hostent* ph = gethostbyname(local);
////	if (ph == NULL)
////		return "";
////	in_addr addr;
////	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
////	std::string localIP;
////	localIP.assign(inet_ntoa(addr));
////	WSACleanup();
////	return localIP;
////}
////EXTERN_C void Fn_Clinet_connect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
////{
////	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
////	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
////	string ip = string(elibstl::args_to_sdata(pArgInf, 1));
////	if (ip.empty())
////	{
////		return;
////	}
////
////	pRetData->m_bool = pClinet->connect(ip, pArgInf[2].m_short);
////}
////
////FucInfo Clinet_connect = { {
////		/*ccname*/  ("连接"),
////		/*egname*/  ("connect"),
////		/*explain*/ ("连接到指定主机上的指定端口，该主机上的该端口必须已经被某一服务器组件监听。成功返回真，失败返回假。"),
////		/*category*/-1,
////		/*state*/   NULL,
////		/*ret*/     SDT_BOOL,
////		/*reserved*/NULL,
////		/*level*/   LVL_HIGH,
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*ArgCount*/2,
////		/*arg lp*/  connectArgs,
////	} ,Fn_Clinet_connect ,"Fn_Clinet_connect" };
////EXTERN_C void Fn_Clinet_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
////{
////	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
////	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
////	pRetData->m_bool = pClinet->backoff();
////}
////
////FucInfo Clinet_close = { {
////		/*ccname*/  ("断开"),
////		/*egname*/  ("close"),
////		/*explain*/ (" 断开与服务器的已有连接。"),
////		/*category*/-1,
////		/*state*/   NULL,
////		/*ret*/     SDT_BOOL,
////		/*reserved*/NULL,
////		/*level*/   LVL_HIGH,
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*ArgCount*/0,
////		/*arg lp*/  0,
////	} ,Fn_Clinet_close ,"Fn_Clinet_close" };
////
////
////
////EXTERN_C void Fn_Clinet_GetData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
////{
////	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
////	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
////	size_t size = 0;
////	auto tempdata = pClinet->get_data(&size);
////	pRetData->m_pBin = elibstl::clone_bin(tempdata, size);
////}
////
////FucInfo Clinet_GetData = { {
////		/*ccname*/  ("取回数据"),
////		/*egname*/  ("GetData"),
////		/*explain*/ ("取回所接收到的数据。本命令必须在“数据到达”事件的处理子程序中使用。"),
////		/*category*/-1,
////		/*state*/   NULL,
////		/*ret*/     SDT_BIN,
////		/*reserved*/NULL,
////		/*level*/   LVL_HIGH,
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*ArgCount*/0,
////		/*arg lp*/  0,
////	} ,Fn_Clinet_GetData ,"Fn_Clinet_GetData" };
////
////static ARG_INFO Args[] =
////{
////
////	{
////		/*name*/    "发送数据",
////		/*explain*/ ("欲发送的数据"),
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*type*/    SDT_BIN,
////		/*default*/ 0,
////		/*state*/  ArgMark::AS_NONE,
////	},
////	{
////		/*name*/    "是否返回",
////		/*explain*/ ("是否返回，默认为假"),
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*type*/    SDT_BOOL,
////		/*default*/ 0,
////		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
////	}
////};
////
////EXTERN_C void Fn_Clinet_Send(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
////{
////	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
////	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
////	auto bnow = elibstl::args_to_data<BOOL>(pArgInf, 2);
////
////	pRetData->m_bool = pClinet->send(elibstl::arg_to_vdata(pArgInf[1].m_pBin), bnow.has_value() ? bnow.value() : FALSE);
////}
////
////FucInfo  Clinet_Send = { {
////		/*ccname*/  ("发送数据"),
////		/*egname*/  ("send"),
////		/*explain*/ ("向指定已经连接进来的客户发送数据。成功返回真，失败返回假。"),
////		/*category*/-1,
////		/*state*/   NULL,
////		/*ret*/     SDT_BOOL,
////		/*reserved*/NULL,
////		/*level*/   LVL_HIGH,
////		/*bmp inx*/ 0,
////		/*bmp num*/ 0,
////		/*ArgCount*/2,
////		/*arg lp*/  Args,
////	} ,Fn_Clinet_Send ,"Fn_Clinet_Send" };
////
////
////#pragma endregion
