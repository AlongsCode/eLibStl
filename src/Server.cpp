#include"EcontrolHelp.h"
#include<string>
#include"etcp\etcpapi.h"


#define SERVEREX L"my_e_sever_ex"
static INT s_server_cmd[] = { 39 , 40 , 41 , 42 , 43 , 44 ,45 };

static HBITMAP g_hbmp_server = NULL;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
#ifndef __E_STATIC_LIB
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		HDC hCDC = CreateCompatibleDC(ps.hdc);
		SelectObject(hCDC, g_hbmp_server);
		RECT rc;
		GetClientRect(hWnd, &rc);
		FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		FrameRect(ps.hdc, &rc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
		BitBlt(ps.hdc, (rc.right - 24) / 2, (rc.bottom - 24) / 2, 24, 24, hCDC, 0, 0, SRCCOPY);
		DeleteDC(hCDC);
		EndPaint(hWnd, &ps);
		break;
	}
#endif
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
static ATOM g_atom_clinet_ex = NULL;
static void Sever_RegWndClass()
{
#ifndef __E_STATIC_LIB
	g_hbmp_server = (HBITMAP)LoadImageW(g_elibstl_hModule, MAKEINTRESOURCEW(IDB_SERVER_EX), IMAGE_BITMAP, 0, 0, 0);
#endif
	WNDCLASSW wc = { sizeof(WNDCLASSW) };
	wc.lpszClassName = SERVEREX;
	wc.hCursor = LoadCursorW(NULL, (PWSTR)IDC_ARROW);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbWndExtra = sizeof(void*);
	g_atom_clinet_ex = RegisterClassW(&wc);
}

//struct _ESERVERDATA
//{
//	u_short m_prot;
//	char m_ip[16];
//	_ESERVERDATA() {
//		memset(this, 0, sizeof(this));
//	}
//}ESERVERDATA, * PESERVERDATA;


static void server_callback_incline(eServer* pServer) {

	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 1);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
static void server_callback_get_data(eServer* pServer) {

	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 0);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
static void server_callback_outcline(eServer* pServer) {
	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 2);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
HUNIT WINAPI Create_SeverWindow(
	LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据, 由本窗口单元的ITF_GET_PROPERTY_DATA接口产生, 如果没有数据则为NULL
	INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸, 如果没有则为0
	DWORD dwStyle,                      //   预先设置的窗口风格
	HWND hParentWnd,                    //   父窗口句柄
	UINT uID,                           //   在父窗口中的ID
	HMENU hMenu,                        //   未使用
	INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸
	DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID, 用作通知到系统
	HWND hDesignWnd,                    //   如果blInDesignMode为真, 则hDesignWnd提供所设计窗口的窗口句柄
	BOOL blInDesignMode                 //   说明是否被易语言IDE调用以进行可视化设计, 运行时为假
)
{
	if (!g_atom_clinet_ex)
	{
		Sever_RegWndClass();
	}

	if (!blInDesignMode)
		dwStyle &= (~WS_VISIBLE);
	HWND hWnd = CreateWindowExW(
		0,
		SERVEREX,
		NULL,
		dwStyle | WS_CHILD | WS_CLIPSIBLINGS,
		x,
		y,
		cx,
		cy,
		hParentWnd,
		hMenu,
		NULL,
		NULL
	);
	if (!hWnd)
	{
		return NULL;
	}

	eServer* server = new eServer;
	if (pAllPropertyData && nAllPropertyDataSize == sizeof(u_short))
	{
		server->m_port_num = *reinterpret_cast<u_short*>(pAllPropertyData);
		server->set_ip(string(reinterpret_cast<char*>(pAllPropertyData) + sizeof(u_short)));
	}
	server->m_clinet_enter = server_callback_incline;
	server->m_clinet_leave = server_callback_outcline;
	server->m_data_get = server_callback_get_data;

	SetWindowLongPtrW(hWnd, GWL_USERDATA, (LONG_PTR)server);
	if (!blInDesignMode)
	{
		server->start();
	}
	server->m_dwUnitID = dwUnitID;
	server->m_dwWinFormID = dwWinFormID;
	return elibstl::make_cwnd(hWnd);
}
BOOL WINAPI NotifyPropertyChanged_ServerApp(HUNIT hUnit, INT nPropertyIndex,
	PUNIT_PROPERTY_VALUE pValue, LPTSTR* ppszTipText)    //目前尚未使用
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	switch (nPropertyIndex)
	{
	case 0:
		pServer->m_port_num = pValue->m_int;
		return FALSE;
	case 1:
		//不然用户操作了，容易乱填
		pServer->set_ip(pValue->m_szText);
		return FALSE;
	default:break;
	}
	return FALSE;//不用重新创建
}
HGLOBAL WINAPI GetAllPropertyData_ServerApp(HUNIT hUnit)
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, sizeof(u_short) + 16);
	if (hGlobal)
	{
		void* pGlobal = GlobalLock(hGlobal);
		if (pGlobal)
		{
			memcpy(pGlobal, &pServer->m_port_num, sizeof(u_short));
			memcpy(reinterpret_cast<unsigned char*>(pGlobal) + sizeof(u_short), pServer->get_ip(), 16);
			GlobalUnlock(hGlobal);
		}
	}
	return hGlobal;
}
BOOL WINAPI GetPropertyData_ServerApp(HUNIT hUnit, INT nPropertyIndex,
	PUNIT_PROPERTY_VALUE pValue)
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	switch (nPropertyIndex)
	{
	case 0:
		pValue->m_int = pServer->m_port_num;
		return FALSE;
	case 1: {

		//是否为拷贝构造？先用临时变量试一下;
		pValue->m_szText = pServer->get_ip();
		return FALSE;
	}
	default:break;
	}
	return FALSE;
}
extern "C" PFN_INTERFACE WINAPI libstl_GetInterface_serverex(INT nInterfaceNO)
{

	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)Create_SeverWindow :
		nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged_ServerApp :
		nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData_ServerApp :
		nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData_ServerApp :
		NULL;
}










static EVENT_INFO2 s_sever_event[] =
{
	/*000*/ {"数据到达", "收到数据时执行", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"客户进入", "有客户端连接时执行", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*002*/ {"客户离开", "有客户端断开时执行", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};


static UNIT_PROPERTY s_server_member[] =
{
	// FIXED_WIN_UNIT_PROPERTY,    // 必须加上此宏, 或者直接展开, 这里就展开
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"左边", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*001*/ {"顶边", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*002*/ {"宽度", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*003*/ {"高度", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*004*/ {"标记", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
	/*005*/ {"可视", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*006*/ {"禁止", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*007*/ {"鼠标指针", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},



	/*000*/ {"端口号", "port", "可以是大于 0 小于 32767 的任何自定数值", UD_INT, _PROP_OS(__OS_WIN), NULL},
	/*000*/ {"默认ip", "ip", "默认为本机ip", UD_TEXT,  _PROP_OS(__OS_WIN), NULL},
};

namespace elibstl {
	LIB_DATA_TYPE_INFO severex = {
		/*m_szName*/			"服务器Ex",
		/*m_szEgName*/			"serverex",
		/*m_szExplain*/			"基于ETCP的连接的网络数据交换的服务方组件，用作在指定端口监视来自客户方的数据。",
		/*m_nCmdCount*/			sizeof(s_server_cmd) / sizeof(s_server_cmd[0]),
		/*m_pnCmdsIndex*/		s_server_cmd,
		/*m_dwState*/			_DT_OS(__OS_WIN) | LDT_WIN_UNIT | LDT_IS_FUNCTION_PROVIDER ,
		/*m_dwUnitBmpID*/		IDB_SERVER_EX,
		/*m_nEventCount*/		3,
		/*m_pEventBegin*/		s_sever_event,
		/*m_nPropertyCount*/	sizeof(s_server_member) / sizeof(s_server_member[0]),
		/*m_pPropertyBegin*/	s_server_member,
		/*m_pfnGetInterface*/	 libstl_GetInterface_serverex,
		/*m_nElementCount*/		0,
		/*m_pElementBegin*/		NULL,
	};
}





#pragma region servercmd
EXTERN_C void Fn_Server_start(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pServer->start();
}

FucInfo Server_start = { {
		/*ccname*/  ("启动"),
		/*egname*/  ("start"),
		/*explain*/ ("启动服务器，默认是启动状态"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Server_start ,"Fn_Server_start" };
EXTERN_C void Fn_Server_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pServer->close();
}

FucInfo Server_close = { {
		/*ccname*/  ("关闭"),
		/*egname*/  ("close"),
		/*explain*/ ("关闭服务器"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Server_close ,"Fn_Server_close" };

EXTERN_C void Fn_Server_is_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pServer->is_create();
}

FucInfo Server_is_open = { {
		/*ccname*/  ("是否已启动"),
		/*egname*/  ("is_open"),
		/*explain*/ ("判断是否已经开启服务器"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Server_is_open,"Fn_Server_is_open" };



EXTERN_C void Fn_Server_GetData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	size_t size = 0;
	auto tempdata = pServer->get_data(&size);
	pRetData->m_pBin = elibstl::clone_bin(tempdata, size);
}

FucInfo Server_GetData = { {
		/*ccname*/  ("取回数据"),
		/*egname*/  ("GetData"),
		/*explain*/ (""),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Server_GetData ,"Fn_Server_GetData" };


EXTERN_C void Fn_Server_GetCline(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_int = pServer->get_clinet();
}

FucInfo Server_GetCline = { {
		/*ccname*/  ("取回客户"),
		/*egname*/  ("GetCline"),
		/*explain*/ ("取回客户的SOCKET，可以理解为唯一标识符,后期可通过此标识控制客户"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Server_GetCline ,"Fn_Server_GetCline" };

static ARG_INFO Args[] =
{
	{
		/*name*/    "客户SOCKET",
		/*explain*/ ("通过取回客户获取的SOKET"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "立即断开",
		/*explain*/ ("是否立即断开,默认为假"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_Server_CloseClient(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	auto bnow = elibstl::args_to_data<BOOL>(pArgInf, 2);
	pRetData->m_bool = pServer->breakoff(pArgInf[1].m_int, bnow.has_value() ? bnow.value() : FALSE);
}

FucInfo Server_CloseClient = { {
		/*ccname*/  ("断开客户"),
		/*egname*/  ("CloseClinet"),
		/*explain*/ ("取回客户的SOCKET，可以理解为唯一标识符,后期可通过此标识控制客户"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_Server_CloseClient ,"Fn_Server_CloseClient" };

static ARG_INFO Args2[] =
{
	{
		/*name*/    "客户SOCKET",
		/*explain*/ ("通过取回客户获取的SOKET"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "发送数据",
		/*explain*/ ("欲发送的数据"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "是否返回",
		/*explain*/ ("是否返回，默认为假"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_Server_Send(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eServer* pServer = (eServer*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	auto bnow = elibstl::args_to_data<BOOL>(pArgInf, 3);
	pRetData->m_bool = pServer->send(pArgInf[1].m_int, elibstl::arg_to_vdata(pArgInf[2].m_pBin), bnow.has_value() ? bnow.value() : FALSE);
}

FucInfo Server_Send = { {
		/*ccname*/  ("发送数据"),
		/*egname*/  ("send"),
		/*explain*/ ("向指定已经连接进来的客户发送数据。成功返回真，失败返回假。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  Args2,
	} ,Fn_Server_Send ,"Fn_Server_Send" };


#pragma endregion
