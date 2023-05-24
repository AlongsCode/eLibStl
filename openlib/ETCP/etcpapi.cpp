
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
*
*        etcp的上层抽象封装
*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#pragma region 环境依赖和函数声明

#include"winsock2.h"
#include"windows.h"
#include"string"
#include"vector"

using namespace std;
#pragma warning(disable:4018)

typedef unsigned char byte;
namespace etcpkrnln {
	void* myetcp_sever_create(u_short u_port, bool mod, const char* IP);
	bool myetcp_init(void* _servercallback, void* _clinetcallback, int _inbuffer = 0);
	bool  myetcp_server_send(void* pS, SOCKET  pC, vector<unsigned char>  data, bool  is_ret = false);
	bool  myetcp_server_close(SOCKET  pC, bool  is_now = false);
	bool  myetcp_server_over(void* pS);
	char* myetcp_server_getclinet(void* pS, SOCKET  pC);
	u_short  myetcp_server_get_port(void* pS);
	void* clinet_con_f(const char* ip, u_short  uport, int  timedout = 10, bool  mod = false, int  type = 0, const char* proxyip = "", u_short  proxyport = 0, const char* name = "", const char* password = "");
	bool  clinet_send_f(void* pC, vector<unsigned char>  data, bool  is_ret = false, vector<unsigned char>* ret_data = NULL, int delay_ret = 2);
	bool  clinet_leave_f(void* pC);
	SOCKET  get_clinet_soket(void* pC);
	string get_ip_this_a();
	SOCKET  get_server_soket(void* pS);
}
using namespace etcpkrnln;
template<typename Type>
intptr_t  arry_delete_member(std::vector<Type>& to_delete, intptr_t numof, intptr_t count = 1) {
	if (numof <  0 || count > to_delete.size()) {
		return 0;
	}
	intptr_t num = 0;
	for (intptr_t i = 1; i <= count; i++)
	{
		to_delete.erase(to_delete.begin() + numof);
		if (to_delete.size() < numof - 1) {
			break;
		}
		num = i;
	}
	return num;
};
static std::string wcs2cs(std::wstring wcs)
{
	int asciisize = ::WideCharToMultiByte(CP_ACP, 0, wcs.c_str(), -1, NULL, 0, NULL, NULL);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	char* resultstring = new char[asciisize];

	int convresult = ::WideCharToMultiByte(CP_ACP, 0, wcs.c_str(), -1, resultstring, asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	std::string Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
static std::wstring cs2wcs(std::string cs)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, cs.c_str(), -1, NULL, 0);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	wchar_t* resultstring = new wchar_t[widesize];

	int convresult = MultiByteToWideChar(CP_ACP, 0, cs.c_str(), -1, resultstring, widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	std::wstring wstrReturn(resultstring);
	delete[] resultstring;
	return wstrReturn;
}

#pragma endregion


/*******************************************************************
*
*        共同变量
*
********************************************************************/
#pragma region 共同变量
static bool s_is_etcp_init = false;
static u_short s_default_port = 23461;
#pragma endregion
static void destroy_pBind(void* pTCP);
static void* get_pBind(void* pTCP);
static void CALLBACK server_callback(HANDLE  pS, SOCKET  pC, int  eventype, char* ip, int  size, int  conut);
static void CALLBACK clinet_callback(HANDLE   pC, SOCKET  pS, int  eventype, char* ip, int  size);
#define ETCP_ERROR_INIT  3001;
#define ETCP_ERROR_SERVER_CREATE  3002;
#define ETCP_ERROR_CLINET_CREATE  3003


#pragma region 服务器类
struct POINTERBIND
{
	void* pTcp = NULL;
	void* pControl = NULL;
};

static vector<POINTERBIND> g_bind_control;
class eServer
{
public:
	SOCKET m_temp_clinet = NULL;
	unsigned char* temp_data;
	size_t temp_size;
	DWORD m_dwWinFormID = 0;
	DWORD m_dwUnitID = 0;
	u_short m_port_num = 0;
	void* m_clinet_enter = NULL;
	void* m_data_get = NULL;
	void* m_clinet_leave = NULL;
	eServer(u_short uport, void* clinet_enter = NULL, void* data_get = NULL, void* clinet_leave = NULL);
	eServer();
	~eServer();
	bool start();
	//本函数仅可在回调函数 ##数据到达 中使用;
	unsigned char* get_data(size_t* nSize);
	bool is_create();
	void set_ip(string IP);
	void set_ip(wstring IP);
	char* get_ip();
	bool breakoff(SOCKET pC, bool is_now = false);
	string get_clinet_ip(SOCKET pC);
	wstring get_clinet_ip_w(SOCKET pC);
	bool send(SOCKET pClinet, const vector<unsigned char>& data, bool is_ret = false);
	//本函数仅可在回调函数 ##客户进入##数据到达##客户离开 中使用;
	SOCKET get_clinet();
	//bool 断开(客户端 要断开的客户端, bool 立即断开 = false);
	bool close();
	SOCKET get_socket();
private:
	void pointer_synchronization();
	void* m_sever_num = NULL;
	int m_error_code = 0;
	char m_defalt_ip[16] = "";

};
bool eServer::is_create() {
	return m_sever_num != NULL;
}

SOCKET eServer::get_clinet() {
	return m_temp_clinet;
}
unsigned char* eServer::get_data(size_t* nSize) {
	*nSize = temp_size;
	return temp_data;
}

eServer::eServer(u_short arg_port, void* c_en_cb, void* data_get_cb, void* c_leav_cb) {
	m_port_num = arg_port;
	if (c_leav_cb)
	{
		m_clinet_leave = c_leav_cb;
	}
	if (data_get_cb)
	{
		m_data_get = data_get_cb;
	}
	if (c_en_cb)
	{
		m_clinet_enter = c_en_cb;
	}
	if (*m_defalt_ip == '\0')
	{
		strcpy_s(m_defalt_ip, "127.0.0.1");
		if (*m_defalt_ip == '\0')
		{
			strcpy_s(m_defalt_ip, "0.0.0.0");
		}
	}
	if (!s_is_etcp_init)
	{
		s_is_etcp_init = myetcp_init(&server_callback, &clinet_callback, 8192);
		if (!s_is_etcp_init)
		{
			m_error_code = ETCP_ERROR_INIT;
			return;
		}
	}
}

void eServer::pointer_synchronization() {
	POINTERBIND temp;
	temp.pTcp = m_sever_num;
	temp.pControl = this;
	g_bind_control.push_back(temp);
}
char* eServer::get_ip() {
	return m_defalt_ip;
};
eServer::eServer()
{
	m_port_num = s_default_port;
	s_default_port++;
	if (*m_defalt_ip == '\0')
	{
		strcpy_s(m_defalt_ip, "127.0.0.1");
		if (*m_defalt_ip == '\0')
		{
			strcpy_s(m_defalt_ip, "0.0.0.0");
		}
	}
	if (!s_is_etcp_init)
	{
		s_is_etcp_init = myetcp_init(&server_callback, &clinet_callback, 8192);
		if (!s_is_etcp_init)
		{
			m_error_code = ETCP_ERROR_INIT;
			return;
		}
	}

}

bool eServer::start() {
	if (m_sever_num)
	{
		return false;
	}
	m_sever_num = myetcp_sever_create(m_port_num, false, m_defalt_ip);
	if (!m_sever_num)
	{
		m_error_code = ETCP_ERROR_SERVER_CREATE;
		return false;
	}
	pointer_synchronization();
	return true;
}
eServer::~eServer()
{
	close();
}
#pragma endregion

static void server_call(void* pFunc, eServer* pSever)
{
	typedef void (*func)(eServer*);
	func Fun = (func)pFunc;
	Fun(pSever);
}

void CALLBACK server_callback(HANDLE  pS, SOCKET  pC, int  event_type, char* ip_f, int  size_f, int  sever_count)//多线程回调，例如在回调函数体内使用ADO请自己初始化：CoInitialize(0)
{
	eServer* pServer_temp = (eServer*)get_pBind(pS);
	if (!pServer_temp)
	{
		return;
	}
	pServer_temp->m_temp_clinet = pC;
	switch (event_type)
	{
	case 1://客户进入或连接成功
		if (pServer_temp->m_clinet_enter)
		{
			server_call(pServer_temp->m_clinet_enter, pServer_temp);
		}
		break;
	case 2://数据到达
		if (pServer_temp->m_data_get)
		{
			pServer_temp->temp_data = (unsigned char*)ip_f;
			pServer_temp->temp_size = size_f;
			server_call(pServer_temp->m_data_get, pServer_temp);
			pServer_temp->temp_data = nullptr;
			pServer_temp->temp_size = 0;
		}
		break;
	case 3://客户离开
		if (pServer_temp->m_clinet_leave)
		{
			server_call(pServer_temp->m_clinet_leave, pServer_temp);
		}
		break;
	default:
		break;
	}
	pServer_temp->m_temp_clinet = NULL;
}

void eServer::set_ip(string IP) {
	strcpy_s(m_defalt_ip, IP.c_str());
};
void eServer::set_ip(wstring IP) {

	strcpy_s(m_defalt_ip, wcs2cs(IP).c_str());

};
bool eServer::breakoff(SOCKET pSvever, bool is_now) {
	return myetcp_server_close(pSvever, is_now);
}
bool eServer::close() {

	if (m_sever_num)
	{
		bool Ret = myetcp_server_over(m_sever_num);

		if (Ret)
		{
			destroy_pBind(m_sever_num);
			m_sever_num = NULL;
		}
		return Ret;

	}
	return true;
}
SOCKET eServer::get_socket() {
	if (m_sever_num)
	{
		return get_server_soket(m_sever_num);

	}
	return 0;
}


string eServer::get_clinet_ip(SOCKET pClinet) {

	if (m_sever_num)
	{
		char* Ret = myetcp_server_getclinet(m_sever_num, pClinet);
		if (Ret)
		{
			return Ret;
		}

	}
	return "";
};
wstring eServer::get_clinet_ip_w(SOCKET pClinet) {

	if (m_sever_num)
	{
		char* Ret = myetcp_server_getclinet(m_sever_num, pClinet);
		if (Ret)
		{
			return cs2wcs(string(Ret));
		}

	}
	return L"";
};
bool  eServer::send(SOCKET pClinet, const vector<unsigned char>& data, bool  is_ret)//发送成功返回true
{
	if (m_sever_num)
	{
		return myetcp_server_send(m_sever_num, pClinet, data, is_ret);
	}
	return false;
}
static void* get_pBind(void* pTcp) {

	if (g_bind_control.size() >= 1)
	{
		for (size_t i = 0; i < g_bind_control.size(); i++)
		{
			if (g_bind_control[i].pTcp == pTcp) {
				return g_bind_control[i].pControl;
			}

		}
	}
	return 0;
}
static void destroy_pBind(void* pTcp) {

	if (g_bind_control.size() >= 1)
	{
		for (size_t i = 0; i < g_bind_control.size(); i++)
		{
			if (g_bind_control[i].pTcp == pTcp) {
				arry_delete_member(g_bind_control, i, 1);
				break;
			}

		}
	}
}



class eClinet
{
public:
	//内部使用
	unsigned char* m_temp_data = nullptr;
	size_t m_temp_size = 0;
	SOCKET m_temp_server = NULL;
	DWORD m_dwWinFormID = 0;
	DWORD m_dwUnitID = 0;

	void* m_connect_cb = NULL;
	void* m_data_get_cb = NULL;
	void* m_backoff_cb = NULL;
	~eClinet();
	eClinet(void* clinet_connect_cb = NULL, void* data_get_cb = NULL, void* clinet_backoff_cb = NULL);
	bool connect(string ip, u_short  port, int  timeout = 10, bool  mod = false, int  type = 0, string pxoryip = "", u_short  proxy_port = 0, string name = "", string password = "");
	bool connect(wstring ip, u_short  port, int  timeout = 10, bool  mod = false, int  type = 0, wstring pxoryip = L"", u_short  proxy_port = 0, wstring name = L"", wstring password = L"");
	bool  send(const vector<unsigned char>& data, bool is_ret = false, vector<unsigned char>* ret_data = NULL, int delay_ret = 2);
	bool backoff();
	SOCKET get_socket();
	//本函数仅在##数据到达##函数中使用;
	unsigned char* get_data(size_t* nSize);

	//本函数仅在##回调函数##中使用;
	SOCKET get_server_socket();
private:
	void pointer_synchronization();
	void* m_clinet_num = NULL;
	int m_error_code = 0;
};

void eClinet::pointer_synchronization() {
	POINTERBIND temp;
	temp.pTcp = m_clinet_num;
	temp.pControl = this;
	g_bind_control.push_back(temp);
}
bool eClinet::connect(string ip, u_short  uport, int  timeout, bool  mode, int  proxy_type, string proxy_ip, u_short  proxy_port, string proxy_name, string proxy_password) {
	if (m_clinet_num)
	{
		return false;
	}
	m_clinet_num = clinet_con_f(ip.c_str(), uport, timeout, mode, proxy_type, proxy_ip.c_str(), proxy_port, proxy_name.c_str(), proxy_password.c_str());
	if (!m_clinet_num)
	{
		m_error_code = ETCP_ERROR_CLINET_CREATE;
		return false;
	}
	pointer_synchronization();
	return true;
};
bool eClinet::connect(wstring ip, u_short  port, int  timeout, bool  mode, int  proxy_type, wstring proxy_ip, u_short  proxy_port, wstring proxy_name, wstring proxy_password) {
	if (m_clinet_num)
	{
		return false;
	}
	m_clinet_num = clinet_con_f(wcs2cs(ip).c_str(), port, timeout, mode, proxy_type, wcs2cs(proxy_ip).c_str(), proxy_port, wcs2cs(proxy_name).c_str(), wcs2cs(proxy_password).c_str());
	if (!m_clinet_num)
	{
		m_error_code = ETCP_ERROR_CLINET_CREATE;
		return false;
	}
	pointer_synchronization();
	return true;
};

bool  eClinet::send(const vector<unsigned char>& data, bool is_ret, vector<unsigned char>* pRet_Data, int delay_ret) {

	if (m_clinet_num)
	{
		return clinet_send_f(m_clinet_num, data, is_ret, pRet_Data, delay_ret);
	}
	return false;


};

bool eClinet::backoff() {
	if (m_clinet_num)
	{
		bool Ret = clinet_leave_f(m_clinet_num);
		if (Ret)
		{
			destroy_pBind(m_clinet_num);
			m_temp_server = NULL;
			m_clinet_num = NULL;
		}
		return Ret;
	}
	return false;
}

SOCKET eClinet::get_socket() {
	if (m_clinet_num)
	{
		return get_clinet_soket(m_clinet_num);
	}
	return 0;
};

SOCKET eClinet::get_server_socket() {
	return m_temp_server;

}
eClinet::eClinet(void* cb_connect, void* cb_get_data, void* cb_backoff) {

	if (cb_connect)
	{
		m_connect_cb = cb_connect;
	}
	if (cb_get_data)
	{
		m_data_get_cb = cb_get_data;
	}
	if (cb_backoff)
	{
		m_backoff_cb = cb_backoff;
	}
	if (!s_is_etcp_init)
	{
		s_is_etcp_init = myetcp_init(&server_callback, &clinet_callback, 8192);
		if (!s_is_etcp_init)
		{
			m_error_code = ETCP_ERROR_INIT;
			return;
		}
	}
}


eClinet::~eClinet() {
	backoff();
}

unsigned char* eClinet::get_data(size_t* nSize) {
	*nSize = m_temp_size;
	return m_temp_data;
}

static void ClinetCall(void* pfun, eClinet* pSever)
{
	typedef void (*Func)(eClinet*);
	Func pFunc = (Func)pfun;
	pFunc(pSever);
}
static void CALLBACK  clinet_callback(HANDLE   pClient, SOCKET  pS, int  msg, char* ip_f, int  size_f)//多线程回调，例如在回调函数体内使用ADO请自己初始化：CoInitialize(0)
{

	eClinet* pClinet_temp = (eClinet*)get_pBind(pClient);
	if (pClinet_temp == nullptr)
	{
		return;
	}
	pClinet_temp->m_temp_server = pS;
	switch (msg)
	{
	case 1://连接成功

		if (pClinet_temp->m_connect_cb)
		{
			ClinetCall(pClinet_temp->m_connect_cb, pClinet_temp);
		}
		break;
	case 2://数据到达
		if (pClinet_temp->m_data_get_cb)
		{
			pClinet_temp->m_temp_data = (unsigned char*)ip_f;
			pClinet_temp->m_temp_size = size_f;
			ClinetCall(pClinet_temp->m_data_get_cb, pClinet_temp);
			pClinet_temp->m_temp_data = nullptr;
			pClinet_temp->m_temp_size = 0;;
		}
		break;
	case 3://连接断开
		if (pClinet_temp->m_backoff_cb)
		{
			ClinetCall(pClinet_temp->m_backoff_cb, pClinet_temp);
		}
		break;
	default:
		break;
	}
	pClinet_temp->m_temp_server = NULL;
}