#include"EcontrolHelp.h"

#include"etcp\etcpapi.h"


#define CLINETEX L"my_e_clinet_ex"
static INT s_clinet_cmd[] = { 46,47,48,49 };

static HBITMAP g_hbmp_clinet = NULL;

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
	g_hbmp_clinet = (HBITMAP)LoadImageW(g_elibstl_hModule, MAKEINTRESOURCEW(IDB_CLINET_EX), IMAGE_BITMAP, 0, 0, 0);
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

//�ɹ�����
static void clinet_callback_con(eClinet* pClinet) {

	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 1);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
//���ݵ���
static void clinet_callback_get_data(eClinet* pClinet) {

	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 0);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
//�Ͽ�����
static void clinet_callback_out(eClinet* pClinet) {
	pClinet->backoff();
	EVENT_NOTIFY2 event(pClinet->m_dwWinFormID, pClinet->m_dwUnitID, 2);
	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
}
HUNIT WINAPI Create_clinetWindow(
	LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ��������������, �ɱ����ڵ�Ԫ��ITF_GET_PROPERTY_DATA�ӿڲ���, ���û��������ΪNULL
	INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ�, ���û����Ϊ0
	DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
	HWND hParentWnd,                    //   �����ھ��
	UINT uID,                           //   �ڸ������е�ID
	HMENU hMenu,                        //   δʹ��
	INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ�
	DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ
	HWND hDesignWnd,                    //   ���blInDesignModeΪ��, ��hDesignWnd�ṩ����ƴ��ڵĴ��ھ��
	BOOL blInDesignMode                 //   ˵���Ƿ�������IDE�����Խ��п��ӻ����, ����ʱΪ��
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
	return elibstl::make_cwnd(hWnd);
}
BOOL WINAPI NotifyPropertyChanged_clinetApp(HUNIT hUnit, INT nPropertyIndex,
	PUNIT_PROPERTY_VALUE pValue, LPTSTR* ppszTipText)    //Ŀǰ��δʹ��
{
	return FALSE;//�������´���
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
extern "C" PFN_INTERFACE WINAPI libstl_GetInterface_clinetex(INT nInterfaceNO)
{

	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)Create_clinetWindow :
		nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged_clinetApp :
		nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData_clinetApp :
		nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData_clinetApp :
		NULL;
}










EVENT_INFO2 s_clinet_event[] =
{
	/*000*/ {"���ݵ���", "���������˽����ݷ��͹����󣬻�������¼����ڱ��¼��Ĵ����ӳ����е��á�ȡ�����ݡ���������ȡ�ر������յ������ݡ�", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
	/*001*/ {"���ӳɹ�", "�����ӷ������˳ɹ��󣬻�������¼���", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
	/*002*/ {"���ӶϿ�", "�����ӱ��������˶Ͽ��󣬻�������¼���", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
};


static UNIT_PROPERTY s_clinet_member[] =
{
	// FIXED_WIN_UNIT_PROPERTY,    // ������ϴ˺�, ����ֱ��չ��, �����չ��
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	/*000*/ {"���", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*001*/ {"����", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*002*/ {"���", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*003*/ {"�߶�", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*004*/ {"���", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
	/*005*/ {"����", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*006*/ {"��ֹ", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*007*/ {"���ָ��", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},
};

namespace elibstl {
	LIB_DATA_TYPE_INFO clinetex = {
		/*m_szName*/			"�ͻ���Ex",
		/*m_szEgName*/			"clinetex",
		/*m_szExplain*/			"����ETCP�������������ݽ����Ŀͻ����������������һ���ķ�����������������ݡ��������ӵ����ݽ�����һ�ֿɿ��ġ���������������������ݽ�����ʽ��",
		/*m_nCmdCount*/			sizeof(s_clinet_cmd) / sizeof(s_clinet_cmd[0]),
		/*m_pnCmdsIndex*/		s_clinet_cmd,
		/*m_dwState*/			_DT_OS(__OS_WIN) | LDT_WIN_UNIT | LDT_IS_FUNCTION_PROVIDER ,
		/*m_dwUnitBmpID*/		IDB_CLINET_EX,
		/*m_nEventCount*/		3,
		/*m_pEventBegin*/		s_clinet_event,
		/*m_nPropertyCount*/	sizeof(s_clinet_member) / sizeof(s_clinet_member[0]),
		/*m_pPropertyBegin*/	s_clinet_member,
		/*m_pfnGetInterface*/	 libstl_GetInterface_clinetex,
		/*m_nElementCount*/		0,
		/*m_pElementBegin*/		NULL,
	};
}






#pragma region clinetcmd
static ARG_INFO connectArgs[] =
{
	{
		/*name*/    "������ip��ַ",
		/*explain*/ ("��������ip��ַ"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�������˿ں�",
		/*explain*/ ("��������Ӧ�˿ں�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
inline string get_ip_this_a() {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return "";
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
	std::string localIP;
	localIP.assign(inet_ntoa(addr));
	WSACleanup();
	return localIP;
}
EXTERN_C void Fn_Clinet_connect(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	string ip = string(elibstl::args_to_sdata(pArgInf, 1));
	if (ip.empty())
	{
		return;
	}

	pRetData->m_bool = pClinet->connect(ip, pArgInf[2].m_short);
}

FucInfo Clinet_connect = { {
		/*ccname*/  ("����"),
		/*egname*/  ("connect"),
		/*explain*/ ("���ӵ�ָ�������ϵ�ָ���˿ڣ��������ϵĸö˿ڱ����Ѿ���ĳһ����������������ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(connectArgs) / sizeof(connectArgs[0]),
		/*arg lp*/  connectArgs,
	} ,Fn_Clinet_connect ,"Fn_Clinet_connect" };
EXTERN_C void Fn_Clinet_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	pRetData->m_bool = pClinet->backoff();
}

FucInfo Clinet_close = { {
		/*ccname*/  ("�Ͽ�"),
		/*egname*/  ("close"),
		/*explain*/ (" �Ͽ�����������������ӡ�"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_Clinet_close ,"Fn_Clinet_close" };



EXTERN_C void Fn_Clinet_GetData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	size_t size = 0;
	auto tempdata = pClinet->get_data(&size);
	pRetData->m_pBin = elibstl::clone_bin(tempdata, size);
}

FucInfo Clinet_GetData = { {
		/*ccname*/  ("ȡ������"),
		/*egname*/  ("GetData"),
		/*explain*/ ("ȡ�������յ������ݡ�����������ڡ����ݵ���¼��Ĵ����ӳ�����ʹ�á�"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
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
		/*name*/    "��������",
		/*explain*/ ("�����͵�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�Ƿ񷵻�",
		/*explain*/ ("�Ƿ񷵻أ�Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_Clinet_Send(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eClinet* pClinet = (eClinet*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
	auto bnow = elibstl::args_to_data<BOOL>(pArgInf, 2);

	pRetData->m_bool = pClinet->send(elibstl::arg_to_vdata(pArgInf[1].m_pBin), bnow.has_value() ? bnow.value() : FALSE);
}

FucInfo  Clinet_Send = { {
		/*ccname*/  ("��������"),
		/*egname*/  ("send"),
		/*explain*/ ("��ָ���Ѿ����ӽ����Ŀͻ��������ݡ��ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_Clinet_Send ,"Fn_Clinet_Send" };


#pragma endregion
