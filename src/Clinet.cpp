#include"EcontrolHelp.h"

#include"etcp\etcpapi.h"


#define CLINETEX L"my_e_clinet_ex"
static INT s_clinet_cmd[] = { 46,47,48,49 };

HBITMAP g_hbmp_clinet = NULL;

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
		SelectObject(hCDC, g_hbmp_clinet);
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
static void Clinet_RegWndClass()
{
#ifndef __E_STATIC_LIB
	g_hbmp_clinet = (HBITMAP)LoadImageW(g_hModule, MAKEINTRESOURCEW(IDB_CLINET_EX), IMAGE_BITMAP, 0, 0, 0);
#endif
	WNDCLASSW wc = { sizeof(WNDCLASSW) };
	wc.lpszClassName = CLINETEX;
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

//成功连接
static void clinet_callback_con(eClinet* pClinet) {

	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 1);
	elibkrnln::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
//数据到达
static void clinet_callback_get_data(eClinet* pClinet) {

	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 0);
	elibkrnln::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
//断开连接
static void clinet_callback_out(eClinet* pClinet) {
	pClinet->backoff();
	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 2);
	elibkrnln::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
HUNIT WINAPI Create_clinetWindow(
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
		Clinet_RegWndClass();
	}

	if (!blInDesignMode)
		dwStyle &= (~WS_VISIBLE);
	HWND hWnd = CreateWindowExW(
		0,
		CLINETEX,
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

	eClinet* pClinet = new eClinet;
	pClinet->m_connect_cb = clinet_callback_con;
	pClinet->m_backoff_cb = clinet_callback_out;
	pClinet->m_data_get_cb = clinet_callback_get_data;
	SetWindowLongPtrW(hWnd, GWL_USERDATA, (LONG_PTR)pClinet);
	pClinet->m_dwUnitID = dwUnitID;
	pClinet->m_dwWinFormID = dwWinFormID;
	return elibkrnln::make_cwnd(hWnd);
}
BOOL WINAPI NotifyPropertyChanged_clinetApp(HUNIT hUnit, INT nPropertyIndex,
	PUNIT_PROPERTY_VALUE pValue, LPTSTR* ppszTipText)    //目前尚未使用
{
	return FALSE;//不用重新创建
}
HGLOBAL WINAPI GetAllPropertyData_clinetApp(HUNIT hUnit)
{

	return nullptr;
}
BOOL WINAPI GetPropertyData_clinetApp(HUNIT hUnit, INT nPropertyIndex,
	PUNIT_PROPERTY_VALUE pValue)
{
	return FALSE;
}
extern "C" PFN_INTERFACE WINAPI libkrnln_GetInterface_clinetex(INT nInterfaceNO)
{

	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)Create_clinetWindow :
		nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged_clinetApp :
		nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData_clinetApp :
		nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData_clinetApp :
		NULL;
}










EVENT_INFO2 s_clinet_event[] =
{
	/*000*/ {"数据到达", "当服务器端将数据发送过来后，会产生本事件。在本事件的处理子程序中调用“取回数据”方法即可取回本次所收到的数据。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"连接成功", "当连接服务器端成功后，会产生本事件。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*002*/ {"连接断开", "当连接被服务器端断开后，会产生本事件。", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
};


static UNIT_PROPERTY s_clinet_member[] =
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
};

namespace libkrnln {
	LIB_DATA_TYPE_INFO clinetex = {
		/*m_szName*/			"客户端Ex",
		/*m_szEgName*/			"clinetex",
		/*m_szExplain*/			"基于ETCP的连接网络数据交换的客户方组件，用作向另一方的服务器端组件发送数据。基于连接的数据交换是一种可靠的、允许大数据量的网络数据交互方式。",
		/*m_nCmdCount*/			sizeof(s_clinet_cmd) / sizeof(s_clinet_cmd[0]),
		/*m_pnCmdsIndex*/		s_clinet_cmd,
		/*m_dwState*/			_DT_OS(__OS_WIN) | LDT_WIN_UNIT | LDT_IS_FUNCTION_PROVIDER ,
		/*m_dwUnitBmpID*/		IDB_CLINET_EX,
		/*m_nEventCount*/		3,
		/*m_pEventBegin*/		s_clinet_event,
		/*m_nPropertyCount*/	sizeof(s_clinet_member) / sizeof(s_clinet_member[0]),
		/*m_pPropertyBegin*/	s_clinet_member,
		/*m_pfnGetInterface*/	 libkrnln_GetInterface_clinetex,
		/*m_nElementCount*/		0,
		/*m_pElementBegin*/		NULL,
	};
}






#pragma region clinetcmd
static ARG_INFO connectArgs[] =
{
	{
		/*name*/    "服务器ip地址",
		/*explain*/ ("服务器的ip地址"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "服务器端口号",
		/*explain*/ ("服务器对应端口号"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_Clinet_connect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibkrnln::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pClinet->connect(string(elibkrnln::args_to_sdata(pArgInf, 1)), pArgInf[2].m_short);
}

FucInfo Clinet_connect = { {
		/*ccname*/  ("连接"),
		/*egname*/  ("connect"),
		/*explain*/ ("连接到指定主机上的指定端口，该主机上的该端口必须已经被某一服务器组件监听。成功返回真，失败返回假。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(connectArgs) / sizeof(connectArgs[0]),
		/*arg lp*/  connectArgs,
	} ,Fn_Clinet_connect ,"Fn_Clinet_connect" };
EXTERN_C void Fn_Clinet_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibkrnln::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pClinet->backoff();
}

FucInfo Clinet_close = { {
		/*ccname*/  ("断开"),
		/*egname*/  ("close"),
		/*explain*/ (" 断开与服务器的已有连接。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Clinet_close ,"Fn_Clinet_close" };



EXTERN_C void Fn_Clinet_GetData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibkrnln::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	vector<unsigned char> tempdata = pClinet->get_data();
	pRetData->m_pBin = elibkrnln::clone_bin(tempdata.data(), tempdata.size());
}

FucInfo Clinet_GetData = { {
		/*ccname*/  ("取回数据"),
		/*egname*/  ("GetData"),
		/*explain*/ ("取回所接收到的数据。本命令必须在“数据到达”事件的处理子程序中使用。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Clinet_GetData ,"Fn_Clinet_GetData" };

static ARG_INFO Args[] =
{

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

EXTERN_C void Fn_Clinet_Send(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibkrnln::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	auto bnow = elibkrnln::args_to_data<BOOL>(pArgInf, 2);

	pRetData->m_bool = pClinet->send(ebin2v(pArgInf[1].m_pBin), bnow.has_value() ? bnow.value() : FALSE);
}

FucInfo  Clinet_Send = { {
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
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_Clinet_Send ,"Fn_Clinet_Send" };


#pragma endregion
