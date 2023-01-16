#include"ElibHelp.h"

static std::wstring get_ip_this_w() {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		return L"";
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return L"";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr));
	std::string localIP;
	localIP.assign(inet_ntoa(addr));
	WSACleanup();
	int widesize = MultiByteToWideChar(CP_ACP, 0, localIP.c_str(), -1, NULL, 0);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	wchar_t* resultstring = new wchar_t[widesize];

	int convresult = MultiByteToWideChar(CP_ACP, 0, localIP.c_str(), -1, resultstring, widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	std::wstring wstrReturn(resultstring);
	delete[] resultstring;
	return wstrReturn;
}
EXTERN_C void Fn_get_ip_this_w(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = elibstl::clone_textw(get_ip_this_w());
}

FucInfo get_ip_this = { {
		/*ccname*/  ("取本机IPW"),
		/*egname*/  ("get_ip_this_w"),
		/*explain*/ ("获取本机计算机ip地址"),
		/*category*/7,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_ip_this_w ,"Fn_get_ip_this_w" };
