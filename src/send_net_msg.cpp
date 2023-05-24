#pragma warning(disable:4996)
#include <WS2tcpip.h>
#include<string>
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

/*��ҳ������Բ����ˣ�����*/
static bool Ipv6_send_net_msg(const std::string& serverIP, u_short port, LPBYTE msg, size_t len) {
	//��ʼ��
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	// ���� socket
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	//�ж��Ƿ���IPv4

	if (inet_pton(AF_INET, serverIP.data(), &server.sin_addr) == 1) {
		//IPV4�������⴦��
	}
	else {
		sockaddr_in6 server6;
		server6.sin6_family = AF_INET6;
		server6.sin6_port = htons(port);
		//�ж��Ƿ���IPv6
		if (InetPtonA(AF_INET6, serverIP.data(), &server6.sin6_addr) == 1) {
			server = reinterpret_cast<sockaddr_in&>(server6);
		}
		else {
			closesocket(sock);
			WSACleanup();
			return false;
		}
	}

	// ����
	if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// ����
	int iSendResult = send(sock, (char*)msg, len, 0);
	if (iSendResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// �ͷ���Դ
	closesocket(sock);
	WSACleanup();
	return true;
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "ip��ַ",
		/*explain*/ ("�����ͷ�������ip��ַ,Ĭ��Ϊ����ip"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�˿ں�",
		/*explain*/ ("�����ͷ������Ķ˿ں�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��������",
		/*explain*/ ("�����͵�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},

};

EXTERN_C void Fn_send_net_msg(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto ip = elibstl::args_to_sdata(pArgInf, 0);
	LPBYTE data = reinterpret_cast<LPBYTE>(pArgInf[2].m_pBin + sizeof(std::uint32_t) * 2);
	auto datalent = *reinterpret_cast<std::uint32_t*>(pArgInf[2].m_pBin + sizeof(std::uint32_t));
	if (datalent > 0 && data)
	{
		pRetData->m_bool = Ipv6_send_net_msg(ip.empty() ? get_ip_this_a() : std::string(ip), pArgInf[1].m_short, data, datalent);
		return;
	}
	pRetData->m_bool = false;
}

FucInfo send_net_msg = { {
		/*ccname*/  ("����������Ϣ"),
		/*egname*/  ("send_net_msg"),
		/*explain*/ ("�Զ��ж�IPV4,IPV6,Ȼ�����Ӳ���ָ��������������Ϣ������ڿͻ��������˵ʹ�ø��ӷ��㣬����UDP������ʵ�����ǽ�����������֮���TCPͨ�ţ��ܹ����������������Ӽ������û�ֻ���ע�����Ĵ��ݣ�������Ҫ��ע�ڲ�ʵ�֣�����������ʹ�û�ʹ��"),
		/*category*/7,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/   Args,
	} ,Fn_send_net_msg ,"Fn_send_net_msg" };
