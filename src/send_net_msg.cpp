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

/*此页代码调试不好了，服了*/
static bool Ipv6_send_net_msg(const std::string& serverIP, u_short port, LPBYTE msg, size_t len) {
	//初始化
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	// 创建 socket
	SOCKET sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);


	//判断是否是IPv4

	if (inet_pton(AF_INET, serverIP.data(), &server.sin_addr) == 1) {
		//IPV4不做特殊处理
	}
	else {
		sockaddr_in6 server6;
		server6.sin6_family = AF_INET6;
		server6.sin6_port = htons(port);
		//判断是否是IPv6
		if (InetPtonA(AF_INET6, serverIP.data(), &server6.sin6_addr) == 1) {
			server = reinterpret_cast<sockaddr_in&>(server6);
		}
		else {
			closesocket(sock);
			WSACleanup();
			return false;
		}
	}

	// 连接
	if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 发送
	int iSendResult = send(sock, (char*)msg, len, 0);
	if (iSendResult == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return false;
	}

	// 释放资源
	closesocket(sock);
	WSACleanup();
	return true;
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "ip地址",
		/*explain*/ ("欲发送服务器的ip地址,默认为本地ip"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "端口号",
		/*explain*/ ("欲发送服务器的端口号"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "发送数据",
		/*explain*/ ("欲发送的数据"),
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
		/*ccname*/  ("发送网络消息"),
		/*egname*/  ("send_net_msg"),
		/*explain*/ ("自动判断IPV4,IPV6,然后连接并向指定服务器发送消息，相对于客户端组件来说使用更加方便，类似UDP，但是实际上是进行握手连接之后的TCP通信，能够触发服务器的连接监听。用户只需关注参数的传递，而不需要关注内部实现，方便易语言使用户使用"),
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
