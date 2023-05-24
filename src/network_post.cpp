#include"ElibHelp.h"
#include<wininet.h>
#include <algorithm>
#include<sstream>
static ARG_INFO Args[] =
{
	{
		/*name*/    "��ҳ",
		/*explain*/ ("��������ҳ��ַ���������http://����https://��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "���ʷ�ʽ",
		/*explain*/ ("��ֵ������0��GET����1��POST����2��HEAD����3��PUT����4��OPTIONS����5��DELETE����6��TRACE����7��CONNECT����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�ύ��Ϣ",
		/*explain*/ ("���ڷ��ʷ�ʽΪPOSTʱ��Ч��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�ύCookies",
		/*explain*/ ("�ύ��Cookie��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "����Cookies",
		/*explain*/ ("���淵�ص�Cookie��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR,
	},
	{
		/*name*/    " ����Э��ͷ",
		/*explain*/ ("һЩ���ӵ�Э��ͷ��Ϣ��һ��һ�����Ի��з�������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "����Э��ͷ",
		/*explain*/ ("���淵�ص�Э��ͷ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR,
	},{
		/*name*/    "��ֹ�ض���",
		/*explain*/ ("�Ƿ��ֹ��ҳ�ض���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},{
		/*name*/    "�ֽڼ��ύ",
		/*explain*/ ("�ύ�Ķ���������,ָ���˲���ʱ���ȼ������������ύ��Ϣ����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�����ַ",
		/*explain*/ ("�����ַ����ʽΪip:port������8.8.8.8:88��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�Ƿ�ȫ��ҪЭ��ͷ",
		/*explain*/ ("������Э��ͷΪ��ʱ�Զ���ӱ�Ҫ��UAЭ��ͷ Ĭ��Ϊ�棬�ٽ�������ӷǴ���Э��ͷ"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},
	{
		/*name*/    "�Ƿ���Э��ͷ��Сд",
		/*explain*/ ("��Э��ͷ�еļ�������ĸ����Ϊ��д"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},
	{
		/*name*/    "�Ƿ�ʹ��socks4����",
		/*explain*/ ("��Ϊhttp(s)������Ϊsocks4����Ĭ��Ϊ�١�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	}
};





/**
 * @brief ʹ��WinInet API��ʽ������ҳ
 *
 * @param ��ַ [in] ��������ҳ��ַ���������http://����https://��
 * @param ���ʷ�ʽ [in] һ�������͵Ĳ�������ֵ������0��GET����1��POST����2��HEAD����3��PUT����4��OPTIONS����5��DELETE����6��TRACE����7��CONNECT����
 * @param �ύ��Ϣ [in] һ���ı��͵Ĳ��������ڷ��ʷ�ʽΪPOSTʱ��Ч��
 * @param �ύCookies [in] һ���ı��͵Ĳ�������ʾ�ύʱ��cookie��
 * @param ����Cookies [out] һ���ı��͵Ĳ�������ʾ���ص�Cookie��
 * @param ����Э��ͷ [in] һ���ı��͵Ĳ�������ʾһЩ���ӵ�Э��ͷ��Ϣ��һ��һ�����Ի��з�������
 * @param ����Э��ͷ [out] һ���ı��͵Ĳ�������ʾ���ص�Э��ͷ��
 * @param ��ֹ�ض��� [in] һ���߼��͵Ĳ�������ʾ�Ƿ��ֹ��ҳ�ض���
 * @param �ֽڼ��ύ [in] һ���ֽڼ��Ĳ�������ʾ�ύ�ֽڼ����ݡ�
 * @param �����ַ [in] һ���ı��͵Ĳ�������ʾ�����ַ����ʽΪip:port������8.8.8.8:88��
 * @param �Ƿ�ȫ��ҪЭ��ͷ [in] ������Э��ͷΪ��ʱ�Զ���ӱ�Ҫ��UAЭ��ͷ Ĭ��Ϊ�棬�ٽ�������ӷǴ���Э��ͷ
 * @param �Ƿ���Э��ͷ��Сд [in] ��Э��ͷ�еļ�������ĸ����Ϊ��д
 * @param �Ƿ�ʹ��socks4���� [in] ���ô������ͣ���Ϊhttp(s)������Ϊsocks4����
 *
 * @return std::vector<unsigned char> ��������ҳ�����ݶ���������������
 */
static LPBYTE
web_visit(
	std::string_view  n_url,//0
	int  n_access_method,//1
	std::string_view  n_post_data,//2
	std::string_view n_post_Cookies,//3
	LPSTR* pRetCookies,//4
	std::string_view  n_add_itional_header,//5
	LPSTR* pRetHead,//6
	std::optional<BOOL>  n_no_redirect,//7
	std::vector<unsigned char>  n_post_data_pBuffer,//8
	std::string_view  n_pox_addr,//9
	std::optional<BOOL>  n_is_completion_head,//10
	std::optional<BOOL>  n_is_make_head_up,//11
	std::optional<BOOL>  n_is_socks4//12
) {

	bool no_redirect = n_no_redirect.value_or(false);
	bool  isCompleteRequiredHeader = n_is_completion_head.value_or(true);;
	bool is_make_head_up = n_is_make_head_up.value_or(true);
	std::string add_itional_header = n_add_itional_header.data() ? n_add_itional_header.data() : "";
	if (is_make_head_up)
	{
		std::vector<std::string> lines;
		std::stringstream ss(add_itional_header);
		std::string line;
		while (std::getline(ss, line, '\n')) {
			lines.push_back(line);
		}
		std::string result_header;
		int colon_pos;
		std::string key, value;
		for (const auto& line : lines) {
			colon_pos = line.find(":");
			if (colon_pos == std::string::npos) {
				continue;
			}
			key = line.substr(0, colon_pos);
			value = line.substr(colon_pos + 1);
			if (value[0] == ' ') {
				value = value.substr(1);
			}
			key[0] = std::toupper(key[0]);
			result_header += key + ":" + value + "\n";
		}
		add_itional_header = result_header.substr(0, result_header.size() - 1);
	}
	bool  is_socks4 = n_is_socks4.value_or(false);;

	std::string access_method;
	switch (n_access_method)
	{
	case 1:access_method = "POST"; break;
	case 2:access_method = "HEAD"; break;
	case 3:access_method = "PUT"; break;
	case 4:access_method = "OPTIONS"; break;
	case 5:access_method = "DELETE"; break;
	case 6:access_method = "TRACE"; break;
	case 7:access_method = "CONNECT"; break;
	default:access_method = "GET"; break;//Ĭ��
	}
	bool is_https = false;
	std::string lower_url = std::string(n_url);
	std::transform(lower_url.begin(), lower_url.end(), lower_url.begin(), tolower);
	if (lower_url.substr(0, 8) == "https://") {
		is_https = true;
	}
	//�����뻻һ�£���Щ���ˣ�����������xp�Ļ��ͻ����Ϳ��ԣ����״���xpӦ��Ҳ�ò��˰�
	std::string l_user_agent = "Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1)";
	std::string l_lower_additional_header(add_itional_header);
	std::transform(add_itional_header.begin(), add_itional_header.end(), l_lower_additional_header.begin(), tolower);

	// ����ҵ��� "user-agent:"��������ȡ�м��������Ϊ User-Agent
	size_t pos = l_lower_additional_header.find("user-agent:");
	if (pos != std::string::npos)
	{
		std::string middle_text;
		size_t before_pos = pos + 11;
		size_t after_pos = add_itional_header.find("\r\n", before_pos);
		if (after_pos != std::string::npos)
		{
			middle_text = add_itional_header.substr(before_pos, after_pos - before_pos);
			auto first = middle_text.find_first_not_of(" ");
			auto last = middle_text.find_last_not_of(" ") + 1;
			l_user_agent = middle_text.substr(first, last - first);
		}
	}

	// ����Internet���
	HINTERNET l_HInternet = NULL;

	// �жϴ����ַ�Ƿ�Ϊ��
	if (n_pox_addr.empty()) {
		// ��ʹ�ô�����ʼ��Internet���
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
	}
	else if (is_socks4) {
		// ʹ��socks4������ʼ��Internet���
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, ("SOCKS=" + std::string(n_pox_addr)).c_str(), nullptr, 0);
	}
	else if (is_https) {
		// ���win7��httpsЭ�������Ч���⣬��ʼ��Internet���
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, n_pox_addr.data(), nullptr, 0);
	}
	else {
		// ʹ��http������ʼ��Internet���
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, ("http=" + std::string(n_pox_addr)).c_str(), nullptr, 0);
	}

	// �ж�Internet����Ƿ��ʼ���ɹ�
	if (l_HInternet == NULL) {
		return {};
	}

	std::string domain; // �洢����
	std::string temp_port; // ��ʱ�洢�˿ں�
	std::string url = n_url.data();// �������URL�ַ�������url
	constexpr auto c_https_size = sizeof("https://") - sizeof('\0');
	constexpr auto c_http_size = sizeof("http://") - sizeof('\0');
	// ��url�е��ַ�ȫ��ת��ΪСд���������Ա�
	std::transform(url.begin(), url.end(), url.begin(), ::tolower);
	if (!url.empty() && url.back() != '/') {
		url += '/';
	}

	if (url.find("https://") == 0) {//https:
		temp_port = url.substr(c_https_size);
		domain = url.substr(c_https_size, url.find("/", c_https_size) - c_https_size);
		temp_port = temp_port.substr(domain.length());
	}
	else if (url.find("http://") == 0) {//http:
		temp_port = url.substr(c_http_size);
		domain = url.substr(c_http_size, url.find("/", c_http_size) - c_http_size);
		temp_port = temp_port.substr(domain.length());
	}
	else {//��û�о����http://
		url = "http://" + url;
		temp_port = url.substr(7);
		domain = url.substr(7, url.find("/", c_http_size) - c_http_size);
		temp_port = temp_port.substr(domain.length());
	}

	int port;
	size_t port_pos = temp_port.rfind(":");
	if (port_pos != std::string::npos) {
		port = atoi(temp_port.substr(port_pos + 1).c_str());
	}
	else if (n_url.substr(0, 5) == "https") {
		//ʹ�ð�ȫ���ı�����Э���Ĭ�϶˿� (HTTPS) ������ (�˿� 443) ��
		port = INTERNET_DEFAULT_HTTPS_PORT;
	}
	else {
		//ʹ�� HTTP ��������Ĭ�϶˿� (�˿� 80) ��
		port = INTERNET_DEFAULT_HTTP_PORT;
	}
	HINTERNET l_HInternetCom = InternetConnectA(l_HInternet, domain.c_str(), port, nullptr, nullptr, 3, 0, 0);
	if (l_HInternetCom == NULL)
	{
		InternetCloseHandle(l_HInternet);
		return {};
	}

	//Ĭ�������־
	DWORD l_flag = INTERNET_FLAG_RELOAD | INTERNET_COOKIE_THIRD_PARTY;
	//���'�ύCookies'Ϊ�գ��뽫��־����Ϊ������cookie
	if (n_post_Cookies.empty())
	{
		l_flag = l_flag | INTERNET_FLAG_NO_COOKIES;
	}
	//��ֹ�ض���
	if (no_redirect)
	{
		l_flag = l_flag | INTERNET_FLAG_NO_AUTO_REDIRECT;
	}

	//��_HTTPS,����ʹ�ð�ȫ���ӱ�־����������ض���HTTPS
	if (is_https)
	{
		l_flag = l_flag | INTERNET_FLAG_SECURE;
	}
	else {
		l_flag = l_flag | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS;
	}

	std::string temp_url;
	auto urlpos = n_url.find("://");
	if (urlpos != std::string::npos) {
		temp_url = n_url.substr(urlpos + 3);
	}
	else {
		temp_url = n_url;
	}
	urlpos = temp_url.find('/');
	if (urlpos != std::string::npos) {
		temp_url = temp_url.substr(urlpos);
	}
	else {
		temp_url = "/";
	}

	HINTERNET l_Hhttpre = HttpOpenRequestA(l_HInternetCom, access_method.c_str(), temp_url.c_str(), "HTTP/1.1", nullptr, nullptr, l_flag, 0);

	if (!l_Hhttpre)
	{

		InternetCloseHandle(l_HInternetCom);
		InternetCloseHandle(l_HInternet);
		return {};
	}


	char pBuffer[4]{ 0 };
	InternetSetOptionA(l_Hhttpre, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)pBuffer, 4);
	std::string additionalHeaderLower = add_itional_header;
	std::transform(add_itional_header.begin(), add_itional_header.end(), additionalHeaderLower.begin(), ::toupper);

	if (isCompleteRequiredHeader) {
		if (add_itional_header == "") {
			add_itional_header = "Accept: */*";
		}
		if (additionalHeaderLower.find("accept:") == std::string::npos) {
			add_itional_header = add_itional_header + "\r\n" + "Accept: */*";
		}
		if (additionalHeaderLower.find("referer:") == std::string::npos) {
			add_itional_header = add_itional_header + "\r\n" + "Referer: " + url.data();
		}
		if (additionalHeaderLower.find("accept-language:") == std::string::npos) {
			add_itional_header = add_itional_header + "\r\n" + "Accept-Language: zh-cn";
		}
		if (n_access_method == 1) {
			if (additionalHeaderLower.find("content-type:") == std::string::npos) {
				add_itional_header = add_itional_header + "\r\n" + "Content-Type: application/x-www-form-urlencoded";
			}
		}
	}
	if (!n_post_Cookies.empty()) {
		if (n_post_Cookies.find("Cookie:") == std::string::npos) {
			add_itional_header = add_itional_header + "\r\n" + "Cookie: " + n_post_Cookies.data();
		}
		else {
			add_itional_header = add_itional_header + "\r\n" + n_post_Cookies.data();
		}
	}




	if (n_access_method == 0) {
		HttpSendRequestA(l_Hhttpre, add_itional_header.c_str(), add_itional_header.size(), 0, 0);
	}
	else {
		if (!n_post_data.empty()) {
			n_post_data_pBuffer.resize(n_post_data.size());
			std::memcpy(n_post_data_pBuffer.data(), n_post_data.data(), n_post_data.size());
		}
		HttpSendRequestA(l_Hhttpre, add_itional_header.c_str(), add_itional_header.size(), n_post_data_pBuffer.data(), n_post_data_pBuffer.size());
	}

	//��ȡ����
	DWORD byteCount = 0;
	std::vector<unsigned char> buffer(1024);
	std::vector<unsigned char> pageContent;
	do {
		InternetReadFile(l_Hhttpre, buffer.data(), 1024, &byteCount);
		pageContent.insert(pageContent.end(), buffer.begin(), buffer.begin() + byteCount);
	} while (byteCount);

	//����Э��ͷ
	std::string ret_header;
	DWORD headerLength = 0;
	HttpQueryInfoA(l_Hhttpre, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr, &headerLength, nullptr);
	if (headerLength > 0) {
		char* buffer = new char[headerLength + 1]{ 0 };//�����ǲ������������ģ���ǰ����
		HttpQueryInfoA(l_Hhttpre, HTTP_QUERY_RAW_HEADERS_CRLF, buffer, &headerLength, nullptr);
		ret_header = std::string(buffer);
		delete[]buffer;
	}

	InternetCloseHandle(l_Hhttpre);
	InternetCloseHandle(l_HInternetCom);
	InternetCloseHandle(l_HInternet);

	if (pRetHead)
	{
		elibstl::efree(*pRetHead);
		*pRetHead = elibstl::clone_text(ret_header);

	}
	if (pRetCookies)
	{
		constexpr auto cookie_prefix = "Set-Cookie:";
		constexpr auto cookie_prefix_size = sizeof("Set-Cookie:") - sizeof('\0');
		std::vector<std::string> ret_headers;
		std::stringstream text(ret_header);
		std::string line;

		while (std::getline(text, line)) {
			ret_headers.push_back(line);
		}
		std::string temp_cookies;
		for (const auto& header : ret_headers) {
			if (header.find(cookie_prefix) == 0) {
				auto temp = header.substr(header.find(cookie_prefix) + cookie_prefix_size);
				auto semi_colon_pos = temp.find(";");
				if (semi_colon_pos != std::string::npos) {
					temp.erase(semi_colon_pos);
				}
				temp_cookies += temp + "; ";
			}
		}
		temp_cookies = temp_cookies.substr(0, temp_cookies.size() - 2);
		elibstl::efree(*pRetCookies);
		*pRetCookies = elibstl::clone_text(temp_cookies);
	}
	return elibstl::clone_bin(pageContent.data(), pageContent.size());
}

EXTERN_C void Fn_estl_network_post(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto url = elibstl::args_to_sdata(pArgInf, 0);
	if (url.empty())
	{
		return;
	}
	pRetData->m_pBin = web_visit(url, elibstl::args_to_data<INT>(pArgInf, 1).value_or(0),
		elibstl::args_to_sdata(pArgInf, 2),
		elibstl::args_to_sdata(pArgInf, 3),
		pArgInf[4].m_ppText,
		elibstl::args_to_sdata(pArgInf, 5),
		pArgInf[6].m_ppText,
		elibstl::args_to_data<BOOL>(pArgInf, 7),
		elibstl::arg_to_vdata(pArgInf, 8),
		elibstl::args_to_sdata(pArgInf, 9),
		elibstl::args_to_data<BOOL>(pArgInf, 10),
		elibstl::args_to_data<BOOL>(pArgInf, 11),
		elibstl::args_to_data<BOOL>(pArgInf, 12)
	);
}

FucInfo network_post = { {
		/*ccname*/  ("��ҳ����"),
		/*egname*/  ("web_visit"),
		/*explain*/ ("ʹ��WinInet API��ʽ������ҳ,������������ҳ�������ֽڼ�����"),
		/*category*/7,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/12,
		/*arg lp*/  &Args[0],
	} ,Fn_estl_network_post ,"Fn_estl_network_post" };




