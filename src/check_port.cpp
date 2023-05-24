#pragma warning(disable:4996)
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
static bool check_port_(unsigned short port, const char* ip_address)
{
	bool result = false;
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0)
	{
		addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* addr_result;
		if (getaddrinfo(ip_address, std::to_string(port).c_str(), &hints, &addr_result) == 0)
		{
			SOCKET sock = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);
			if (sock != INVALID_SOCKET)
			{
				if (connect(sock, addr_result->ai_addr, (int)addr_result->ai_addrlen) != SOCKET_ERROR)
				{
					result = true;
				}
				closesocket(sock);
			}
			freeaddrinfo(addr_result);
		}
		WSACleanup();
	}
	return result;
}

static std::string get_ip_this_a() {
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


#include"ElibHelp.h"

static ARG_INFO Args[] =
{
		{
		/*name*/    "端口号",
		/*explain*/ ("欲检测的端口号"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
		},
		{
			/*name*/    "ip地址",
			/*explain*/ ("欲检测的ip地址，为空则为本地ip"),
			/*bmp inx*/ 0,
			/*bmp num*/ 0,
			/*type*/    DATA_TYPE::SDT_TEXT,
			/*default*/ 0,
			/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
		}

};
EXTERN_C void Fn_check_port(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto ip = elibstl::args_to_sdata(pArgInf, 1);
	pRetData->m_bool = check_port_(pArgInf->m_short, ip.empty() ? get_ip_this_a().c_str() : ip.data());
}

FucInfo check_port = { {
		/*ccname*/  ("端口是否可用"),
		/*egname*/  ("is_connect_to_internet"),
		/*explain*/ ("判断指定ip的指定端口号是否开放或可用，一般系统会默认占用一些端口,此代码会尝试连接指定IP的指定端口，连接成功即断开并返回，可以用此代码在客户端组件连接前先进行判断。防止无效连接。"),
		/*category*/7,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_check_port ,"Fn_check_port" };
