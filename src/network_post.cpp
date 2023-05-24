#include"ElibHelp.h"
#include<wininet.h>
#include <algorithm>
#include<sstream>
static ARG_INFO Args[] =
{
	{
		/*name*/    "网页",
		/*explain*/ ("完整的网页地址，必须包含http://或者https://。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "访问方式",
		/*explain*/ ("其值可以是0（GET），1（POST），2（HEAD），3（PUT），4（OPTIONS），5（DELETE），6（TRACE）或7（CONNECT）。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "提交信息",
		/*explain*/ ("仅在访问方式为POST时有效。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "提交Cookies",
		/*explain*/ ("提交的Cookie。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "返回Cookies",
		/*explain*/ ("储存返回的Cookie。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR,
	},
	{
		/*name*/    " 附加协议头",
		/*explain*/ ("一些附加的协议头信息，一行一个，以换行符隔开。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "返回协议头",
		/*explain*/ ("储存返回的协议头。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_VAR,
	},{
		/*name*/    "禁止重定向",
		/*explain*/ ("是否禁止网页重定向。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},{
		/*name*/    "字节集提交",
		/*explain*/ ("提交的二进制数据,指定此参数时优先级超过参数“提交信息”。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "代理地址",
		/*explain*/ ("代理地址，格式为ip:port，例如8.8.8.8:88。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "是否补全必要协议头",
		/*explain*/ ("当附件协议头为空时自动添加必要的UA协议头 默认为真，假将不再添加非传入协议头"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},
	{
		/*name*/    "是否处理协议头大小写",
		/*explain*/ ("将协议头中的键名首字母处理为大写"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	},
	{
		/*name*/    "是否使用socks4代理",
		/*explain*/ ("假为http(s)代理，真为socks4代理。默认为假。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,

	}
};





/**
 * @brief 使用WinInet API方式访问网页
 *
 * @param 网址 [in] 完整的网页地址，必须包含http://或者https://。
 * @param 访问方式 [in] 一个整数型的参数，其值可以是0（GET），1（POST），2（HEAD），3（PUT），4（OPTIONS），5（DELETE），6（TRACE）或7（CONNECT）。
 * @param 提交信息 [in] 一个文本型的参数，仅在访问方式为POST时有效。
 * @param 提交Cookies [in] 一个文本型的参数，表示提交时的cookie。
 * @param 返回Cookies [out] 一个文本型的参数，表示返回的Cookie。
 * @param 附加协议头 [in] 一个文本型的参数，表示一些附加的协议头信息，一行一个，以换行符隔开。
 * @param 返回协议头 [out] 一个文本型的参数，表示返回的协议头。
 * @param 禁止重定向 [in] 一个逻辑型的参数，表示是否禁止网页重定向。
 * @param 字节集提交 [in] 一个字节集的参数，表示提交字节集数据。
 * @param 代理地址 [in] 一个文本型的参数，表示代理地址，格式为ip:port，例如8.8.8.8:88。
 * @param 是否补全必要协议头 [in] 当附件协议头为空时自动添加必要的UA协议头 默认为真，假将不再添加非传入协议头
 * @param 是否处理协议头大小写 [in] 将协议头中的键名首字母处理为大写
 * @param 是否使用socks4代理 [in] 设置代理类型，假为http(s)代理，真为socks4代理
 *
 * @return std::vector<unsigned char> 所访问网页的内容二进制数据容器。
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
	default:access_method = "GET"; break;//默认
	}
	bool is_https = false;
	std::string lower_url = std::string(n_url);
	std::transform(lower_url.begin(), lower_url.end(), lower_url.begin(), tolower);
	if (lower_url.substr(0, 8) == "https://") {
		is_https = true;
	}
	//这里想换一下，有些旧了，如果不相兼容xp的话就换掉就可以，这套代码xp应该也用不了吧
	std::string l_user_agent = "Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1)";
	std::string l_lower_additional_header(add_itional_header);
	std::transform(add_itional_header.begin(), add_itional_header.end(), l_lower_additional_header.begin(), tolower);

	// 如果找到了 "user-agent:"，则尝试提取中间的内容作为 User-Agent
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

	// 定义Internet句柄
	HINTERNET l_HInternet = NULL;

	// 判断代理地址是否为空
	if (n_pox_addr.empty()) {
		// 不使用代理，初始化Internet句柄
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
	}
	else if (is_socks4) {
		// 使用socks4代理，初始化Internet句柄
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, ("SOCKS=" + std::string(n_pox_addr)).c_str(), nullptr, 0);
	}
	else if (is_https) {
		// 解决win7下https协议代理无效问题，初始化Internet句柄
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, n_pox_addr.data(), nullptr, 0);
	}
	else {
		// 使用http代理，初始化Internet句柄
		l_HInternet = InternetOpenA(l_user_agent.c_str(), INTERNET_OPEN_TYPE_PROXY, ("http=" + std::string(n_pox_addr)).c_str(), nullptr, 0);
	}

	// 判断Internet句柄是否初始化成功
	if (l_HInternet == NULL) {
		return {};
	}

	std::string domain; // 存储域名
	std::string temp_port; // 临时存储端口号
	std::string url = n_url.data();// 将输入的URL字符串赋给url
	constexpr auto c_https_size = sizeof("https://") - sizeof('\0');
	constexpr auto c_http_size = sizeof("http://") - sizeof('\0');
	// 将url中的字符全部转换为小写，方便后面对比
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
	else {//都没有就添加http://
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
		//使用安全超文本传输协议的默认端口 (HTTPS) 服务器 (端口 443) 。
		port = INTERNET_DEFAULT_HTTPS_PORT;
	}
	else {
		//使用 HTTP 服务器的默认端口 (端口 80) 。
		port = INTERNET_DEFAULT_HTTP_PORT;
	}
	HINTERNET l_HInternetCom = InternetConnectA(l_HInternet, domain.c_str(), port, nullptr, nullptr, 3, 0, 0);
	if (l_HInternetCom == NULL)
	{
		InternetCloseHandle(l_HInternet);
		return {};
	}

	//默认请求标志
	DWORD l_flag = INTERNET_FLAG_RELOAD | INTERNET_COOKIE_THIRD_PARTY;
	//如果'提交Cookies'为空，请将标志设置为不发送cookie
	if (n_post_Cookies.empty())
	{
		l_flag = l_flag | INTERNET_FLAG_NO_COOKIES;
	}
	//禁止重定向
	if (no_redirect)
	{
		l_flag = l_flag | INTERNET_FLAG_NO_AUTO_REDIRECT;
	}

	//局_HTTPS,增加使用安全连接标志，否则忽略重定向到HTTPS
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

	//读取数据
	DWORD byteCount = 0;
	std::vector<unsigned char> buffer(1024);
	std::vector<unsigned char> pageContent;
	do {
		InternetReadFile(l_Hhttpre, buffer.data(), 1024, &byteCount);
		pageContent.insert(pageContent.end(), buffer.begin(), buffer.begin() + byteCount);
	} while (byteCount);

	//处理协议头
	std::string ret_header;
	DWORD headerLength = 0;
	HttpQueryInfoA(l_Hhttpre, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr, &headerLength, nullptr);
	if (headerLength > 0) {
		char* buffer = new char[headerLength + 1]{ 0 };//长度是不包含结束符的，提前申请
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
		/*ccname*/  ("网页访问"),
		/*egname*/  ("web_visit"),
		/*explain*/ ("使用WinInet API方式访问网页,返回所访问网页的内容字节集数据"),
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




