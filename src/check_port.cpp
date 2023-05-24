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
		/*name*/    "�˿ں�",
		/*explain*/ ("�����Ķ˿ں�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
		},
		{
			/*name*/    "ip��ַ",
			/*explain*/ ("������ip��ַ��Ϊ����Ϊ����ip"),
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
		/*ccname*/  ("�˿��Ƿ����"),
		/*egname*/  ("is_connect_to_internet"),
		/*explain*/ ("�ж�ָ��ip��ָ���˿ں��Ƿ񿪷Ż���ã�һ��ϵͳ��Ĭ��ռ��һЩ�˿�,�˴���᳢������ָ��IP��ָ���˿ڣ����ӳɹ����Ͽ������أ������ô˴����ڿͻ����������ǰ�Ƚ����жϡ���ֹ��Ч���ӡ�"),
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
