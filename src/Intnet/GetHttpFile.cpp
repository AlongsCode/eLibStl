#include <win32++\wxx_cstring.h>
#include <win32++\wxx_file.h>
#include"ElibHelp.h"
#include <Wininet.h>
#include <thread>
#include <chrono>
#include <atomic>

enum class UserAction :int {
	Normal,
	End,
	Pause,
	Continue,
};
enum class DownloadStatus :int {
	Begin,
	Normal,
	Paused,
	Finished,
};
using DownloadCallback = UserAction(CALLBACK*)(DownloadStatus, unsigned long long all, unsigned long long, unsigned long long, double, unsigned long long, INT userData);
















namespace {

#define AFX_INET_SERVICE_FTP        INTERNET_SERVICE_FTP
#define AFX_INET_SERVICE_HTTP       INTERNET_SERVICE_HTTP
#define AFX_INET_SERVICE_GOPHER     INTERNET_SERVICE_GOPHER

	// these are types that MFC parsing functions understand

#define AFX_INET_SERVICE_UNK        0x1000
#define AFX_INET_SERVICE_FILE       (AFX_INET_SERVICE_UNK+1)
#define AFX_INET_SERVICE_MAILTO     (AFX_INET_SERVICE_UNK+2)
#define AFX_INET_SERVICE_MID        (AFX_INET_SERVICE_UNK+3)
#define AFX_INET_SERVICE_CID        (AFX_INET_SERVICE_UNK+4)
#define AFX_INET_SERVICE_NEWS       (AFX_INET_SERVICE_UNK+5)
#define AFX_INET_SERVICE_NNTP       (AFX_INET_SERVICE_UNK+6)
#define AFX_INET_SERVICE_PROSPERO   (AFX_INET_SERVICE_UNK+7)
#define AFX_INET_SERVICE_TELNET     (AFX_INET_SERVICE_UNK+8)
#define AFX_INET_SERVICE_WAIS       (AFX_INET_SERVICE_UNK+9)
#define AFX_INET_SERVICE_AFS        (AFX_INET_SERVICE_UNK+10)
#define AFX_INET_SERVICE_HTTPS      (AFX_INET_SERVICE_UNK+11)

	inline int AtlStrLen(_In_opt_z_ const wchar_t* str)
	{
		if (str == NULL)
			return 0;
		return static_cast<int>(::wcslen(str));
	}

	BOOL  _AfxParseURLWorker(LPCTSTR pstrURL,
		LPURL_COMPONENTS lpComponents, DWORD& dwServiceType,
		INTERNET_PORT& nPort, DWORD dwFlags)
	{
		// this function will return bogus stuff if lpComponents
		// isn't set up to copy the components

		LPTSTR pstrCanonicalizedURL;
		TCHAR szCanonicalizedURL[INTERNET_MAX_URL_LENGTH];
		DWORD dwNeededLength = INTERNET_MAX_URL_LENGTH;
		BOOL bRetVal;
		BOOL bMustFree = FALSE;

		// Decoding is done in InternetCrackUrl/UrlUnescape
		// so we don't need the ICU_DECODE flag here.

		DWORD dwCanonicalizeFlags = dwFlags &
			(ICU_NO_ENCODE | ICU_NO_META |
				ICU_ENCODE_SPACES_ONLY | ICU_BROWSER_MODE);

		DWORD dwCrackFlags = 0;

		BOOL bUnescape = FALSE;

		if ((dwFlags & (ICU_ESCAPE | ICU_DECODE)) && (lpComponents->dwUrlPathLength != 0))
		{

			// We use only the ICU_ESCAPE flag for decoding even if
			// ICU_DECODE is passed.

			// Also, if ICU_BROWSER_MODE is passed we do the unescaping
			// manually because InternetCrackUrl doesn't do
			// Browser mode unescaping

			if (dwFlags & ICU_BROWSER_MODE)
				bUnescape = TRUE;
			else
				dwCrackFlags |= ICU_ESCAPE;
		}

		bRetVal = InternetCanonicalizeUrl(pstrURL, szCanonicalizedURL,
			&dwNeededLength, dwCanonicalizeFlags);

		if (!bRetVal)
		{
			if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
				return FALSE;

			pstrCanonicalizedURL = new TCHAR[dwNeededLength];
			if (pstrCanonicalizedURL == NULL)
				return FALSE;

			bMustFree = TRUE;
			bRetVal = InternetCanonicalizeUrl(pstrURL, pstrCanonicalizedURL,
				&dwNeededLength, dwCanonicalizeFlags);
			if (!bRetVal)
			{
				delete[] pstrCanonicalizedURL;
				return FALSE;
			}
		}
		else
		{
			pstrCanonicalizedURL = szCanonicalizedURL;
		}

		// now that it's safely canonicalized, crack it

		bRetVal = InternetCrackUrl(pstrCanonicalizedURL, 0,
			dwCrackFlags, lpComponents);

		if (bUnescape)
		{
			// Length of buffer passed to UrlUnescape cannot be larger than INTERNET_MAX_URL_LENGTH characters.
			if (AtlStrLen(lpComponents->lpszUrlPath) >= INTERNET_MAX_URL_LENGTH ||
				FAILED(UrlUnescape(lpComponents->lpszUrlPath, NULL, NULL, URL_UNESCAPE_INPLACE | URL_DONT_UNESCAPE_EXTRA_INFO)))
			{
				if (bMustFree)
					delete[] pstrCanonicalizedURL;

				return FALSE;
			}

			lpComponents->dwUrlPathLength = static_cast<DWORD>(AtlStrLen(lpComponents->lpszUrlPath));
		}

		if (bMustFree)
		{
			delete[] pstrCanonicalizedURL;
		}

		// convert to MFC-style service ID

		if (!bRetVal)
		{
			dwServiceType = AFX_INET_SERVICE_UNK;
		}
		else
		{
			nPort = lpComponents->nPort;
			switch (lpComponents->nScheme)
			{
			case INTERNET_SCHEME_FTP:
				dwServiceType = AFX_INET_SERVICE_FTP;
				break;

			case INTERNET_SCHEME_GOPHER:
				dwServiceType = AFX_INET_SERVICE_GOPHER;
				break;

			case INTERNET_SCHEME_HTTP:
				dwServiceType = AFX_INET_SERVICE_HTTP;
				break;

			case INTERNET_SCHEME_HTTPS:
				dwServiceType = AFX_INET_SERVICE_HTTPS;
				break;

			case INTERNET_SCHEME_FILE:
				dwServiceType = AFX_INET_SERVICE_FILE;
				break;

			case INTERNET_SCHEME_NEWS:
				dwServiceType = AFX_INET_SERVICE_NNTP;
				break;

			case INTERNET_SCHEME_MAILTO:
				dwServiceType = AFX_INET_SERVICE_MAILTO;
				break;

			default:
				dwServiceType = AFX_INET_SERVICE_UNK;
			}
		}

		return bRetVal;
	}

	BOOL AfxParseURLEx(LPCTSTR pstrURL, DWORD& dwServiceType,
		CString& strServer, CString& strObject, INTERNET_PORT& nPort,
		CString& strUsername, CString& strPassword, DWORD dwFlags/* = 0*/)
	{
		dwServiceType = AFX_INET_SERVICE_UNK;

		if (pstrURL == NULL)
			return FALSE;

		URL_COMPONENTS urlComponents;
		memset(&urlComponents, 0, sizeof(URL_COMPONENTS));
		urlComponents.dwStructSize = sizeof(URL_COMPONENTS);

		urlComponents.dwHostNameLength = INTERNET_MAX_HOST_NAME_LENGTH;
		urlComponents.lpszHostName = strServer.GetBuffer(INTERNET_MAX_HOST_NAME_LENGTH + 1);
		urlComponents.dwUrlPathLength = INTERNET_MAX_PATH_LENGTH;
		urlComponents.lpszUrlPath = strObject.GetBuffer(INTERNET_MAX_PATH_LENGTH + 1);
		urlComponents.dwUserNameLength = INTERNET_MAX_USER_NAME_LENGTH;
		urlComponents.lpszUserName = strUsername.GetBuffer(INTERNET_MAX_USER_NAME_LENGTH + 1);
		urlComponents.dwPasswordLength = INTERNET_MAX_PASSWORD_LENGTH;
		urlComponents.lpszPassword = strPassword.GetBuffer(INTERNET_MAX_PASSWORD_LENGTH + 1);

		BOOL bRetVal = _AfxParseURLWorker(pstrURL, &urlComponents,
			dwServiceType, nPort, dwFlags);

		strServer.ReleaseBuffer();
		strObject.ReleaseBuffer();
		strUsername.ReleaseBuffer();
		strPassword.ReleaseBuffer();
		return bRetVal;
	}




	class CCometHttp
	{
	public:
		CCometHttp(void);
		~CCometHttp(void);
	public:
		HINTERNET m_hInternetOpen;
		HINTERNET m_hInternetConnect;
		HINTERNET m_hInternetRequest;
		LPBYTE	m_lpResponseByte;
		DWORD m_ResponseLength;
		CString m_strRequest;
		CString m_strContentType;
		CString m_strCookie;
		CString m_strLocation;
		CString m_strDate;
		int m_nContentEncoding;
		int m_nHttpStatus;
		INT64 m_lContentLength;
	private:
		CString m_strURL;//完整网址
		CString m_strDomain;//域名
		CString m_strFile;//文件地址(不包括域名)	
		CString m_strVerb;
	public:

		BOOL Open(CString strProxy = _T(""));
		BOOL OpenURL(CString strURL, CString strVerb = _T(""), DWORD dwFlag = 0);
		BOOL SendRequest(CString strHeaders = _T(""), BOOL bGzip = FALSE, LPVOID lpPostBuff = NULL, DWORD dwPostLength = 0);
		BOOL ReadFile();
		void Close();
		ULONGLONG GetLength() const
		{

			return m_lContentLength;
		}


		bool DownloadFile(const std::wstring& path, DownloadCallback callback, INT userData);


	private:
		void QueryInfo();
		void QueryInfo(DWORD dwInfoLevel, CString& strValue);
		void QueryInfo(DWORD dwInfoLevel, int& nValue);
		void QueryInfo(DWORD dwInfoLevel, INT64& nValue);
	};


#define HttpEncoding_NULL		0
#define HttpEncoding_GZIP		1
#define HttpEncoding_DEFLATE	2

	CCometHttp::CCometHttp(void)
	{
		m_hInternetOpen = m_hInternetConnect = m_hInternetRequest = NULL;
		m_lpResponseByte = NULL;
		m_ResponseLength = 0;
		m_nContentEncoding = HttpEncoding_NULL;
		m_nHttpStatus = 0;
		m_lContentLength = 0;
	}
	CCometHttp::~CCometHttp(void)
	{
		Close();
		if (m_lpResponseByte) {
			free(m_lpResponseByte);
			m_lpResponseByte = NULL;

		}
		m_ResponseLength = 0;
	}
	BOOL CCometHttp::Open(CString strProxy)
	{
		Close();
		LPCWSTR lpszAgent = NULL;
		DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG;
		LPCWSTR lpszProxy = NULL;//代理地址
		LPCWSTR lpszProxyBypass = NULL;//代理的参数
		DWORD dwFlags = 0;
		if (strProxy != _T("")) {//传递过来的代理地址
			dwAccessType = INTERNET_OPEN_TYPE_PROXY;
			lpszProxy = strProxy;
		}

		m_hInternetOpen = InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
		if (m_hInternetOpen) {
			DWORD dwMilliseconds = 90 * 1000; //超时值
			InternetSetOptionW(m_hInternetOpen, INTERNET_OPTION_CONNECT_TIMEOUT, &dwMilliseconds, sizeof(DWORD));
			InternetSetOptionW(m_hInternetOpen, INTERNET_OPTION_SEND_TIMEOUT, &dwMilliseconds, sizeof(DWORD));
			InternetSetOptionW(m_hInternetOpen, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwMilliseconds, sizeof(DWORD));
		}

		return m_hInternetOpen != NULL;
	}

	BOOL CCometHttp::OpenURL(CString strURL, CString strVerb, DWORD dwFlag)
	{
		if (!m_hInternetOpen)return FALSE;
		strURL.TrimLeft();
		m_strURL = strURL;
		DWORD dwServiceType = 0;
		CString strServer;
		CString strObject;
		INTERNET_PORT nPort = 0;
		CString strUsername = _T("");
		CString strPassword = _T("");

		AfxParseURLEx(strURL, dwServiceType, strServer, strObject, nPort, strUsername, strPassword, 0);
		m_strDomain = strServer;
		m_strFile = strObject;
		//AfxMessageBox(m_strDomain);
		//AfxMessageBox(m_strFile);
		//------------	
		DWORD dwFlags = dwFlag;
		if (dwServiceType == AFX_INET_SERVICE_HTTP) {
			dwServiceType = INTERNET_SERVICE_HTTP;
		}
		else if (dwServiceType == AFX_INET_SERVICE_HTTPS) {
			dwServiceType = INTERNET_SERVICE_HTTP;
			dwFlags |= INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_SECURE;
		}
		else {
			dwServiceType = INTERNET_SERVICE_HTTP;
		}
		//------------
		LPCTSTR lpszUserName = NULL;
		LPCTSTR lpszPassword = NULL;
		if (strUsername != _T("")) {
			lpszUserName = strUsername;
		}
		if (strPassword != _T("")) {
			lpszPassword = strPassword;
		}
		//------------
		m_hInternetConnect = InternetConnectW(m_hInternetOpen, m_strDomain, nPort, lpszUserName, lpszPassword, dwServiceType, NULL, NULL);
		if (!m_hInternetConnect) {
			//AfxMessageBox("InternetConnect=FALSE");
			return FALSE;
		}
		//------------	
		dwFlags |= INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS;
		//------------
		if (strVerb == _T(""))strVerb = _T("GET");
		m_strVerb = strVerb;
		m_strVerb.MakeUpper();
		m_hInternetRequest = HttpOpenRequestW(m_hInternetConnect, m_strVerb, m_strFile, _T("HTTP/1.1"), NULL, NULL, dwFlags, 0);
		if (!m_hInternetRequest) {
			//AfxMessageBox("HttpOpenRequest=FALSE");
			return FALSE;
		}

		return m_hInternetRequest != NULL;
	}
	BOOL CCometHttp::SendRequest(CString strHeaders, BOOL bGzip, LPVOID lpPostBuff, DWORD dwPostLength)
	{
		if (!m_hInternetRequest)return FALSE;
		// 补充协议头-------
		if (strHeaders != L"" && strHeaders.Right(2) != L"\r\n")
			strHeaders += L"\r\n";
		if (strHeaders.Find(L"User-Agent: ") == -1)
			strHeaders += L"User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727) CometHTTP\r\n";
		if (strHeaders.Find(L"Accept: ") == -1)
			strHeaders += L"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*\r\n";
		if (strHeaders.Find(L"Referer: ") == -1)
			strHeaders += L"Referer: " + m_strURL + "\r\n";
		if (strHeaders.Find(L"Accept-Language: ") == -1)
			strHeaders += L"Accept-Language: zh-cn\r\n";
		if (bGzip && strHeaders.Find(L"Accept-Encoding: ") == -1)
			strHeaders += L"Accept-Encoding: gzip, deflate\r\n";

		//AfxMessageBox(strHeaders);
		BOOL bRet = FALSE;
		try {
			// 附带信息发送请求----		
			if (m_strVerb == L"GET") {
				DWORD dwHeadersLength = strHeaders.GetLength();
				bRet = HttpSendRequestW(m_hInternetRequest, strHeaders, dwHeadersLength, NULL, NULL);
			}
			else if (m_strVerb == L"POST") {
				if (strHeaders.Find(L"Content-Type: ") == -1)
					strHeaders += L"Content-Type: application/x-www-form-urlencoded\r\n";
				DWORD dwHeadersLength = strHeaders.GetLength();
				bRet = HttpSendRequestW(m_hInternetRequest, strHeaders, dwHeadersLength, lpPostBuff, dwPostLength);
			}
			else {
				DWORD dwHeadersLength = strHeaders.GetLength();
				bRet = HttpSendRequestW(m_hInternetRequest, strHeaders, dwHeadersLength, NULL, NULL);
			}
		}
		catch (...) {
			//AfxMessageBox("HttpSendRequest=FALSE");
		}
		QueryInfo();
		return bRet;
	}
	bool CCometHttp::DownloadFile(const std::wstring& path, DownloadCallback callback, INT userData) {
		std::atomic<UserAction> m_user = UserAction::Normal;
		std::atomic<DownloadStatus> m_status = DownloadStatus::Normal;
		std::atomic<UINT64> m_downloadedLength = 0;
		BYTE buffer[4096] = { 0 };
		DWORD bytesRead = 1;
		const UINT64 totalLength = GetLength();
		bool success = false;
		std::atomic<bool> bOver = false;
		if (totalLength <= 0)
			return false;

		if (callback) {
			m_user = callback(DownloadStatus::Begin, totalLength, 0, 0, 0, 0, userData);
			if (m_user == UserAction::End) {
				return false;
			}
			else if (m_user == UserAction::Pause) {
				m_status = DownloadStatus::Paused;
			}

			auto lambda = [&]() {
				unsigned long long startTime = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch()).count();
				unsigned long long speed = 0;
				unsigned long long remainingSize = 0;
				double progress = 0;
				unsigned long long elapsedTime = 0;
				unsigned long long currentTime = 0;

				while (!bOver) {
					currentTime = std::chrono::duration_cast<std::chrono::seconds>(
						std::chrono::system_clock::now().time_since_epoch()).count();
					elapsedTime = currentTime - startTime;
					if (elapsedTime > 0) {
						const auto now = m_downloadedLength.load();
						speed = now / elapsedTime;
						remainingSize = totalLength - now;
						progress = now * 100 / totalLength;

						m_user = callback(m_status, totalLength, speed, remainingSize, progress, elapsedTime, userData);
						switch (m_user)
						{
						case UserAction::End:
							m_status.store(DownloadStatus::Finished);
							bOver = true;
							break;
						case UserAction::Pause:
							m_status.store(DownloadStatus::Paused);
							break;
						case UserAction::Continue:
							m_status.store(DownloadStatus::Normal);
							break;
						default:
							break;
						};

						//		// 等待1秒
						std::this_thread::sleep_for(std::chrono::seconds(1));
					}

				}
				m_user = callback(DownloadStatus::Finished, totalLength, speed, remainingSize, progress, elapsedTime, userData);
				};
			std::thread thread(lambda);
			HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (fileHandle == INVALID_HANDLE_VALUE) {
				goto ove1;
			}
			while (bytesRead && m_status.load() != DownloadStatus::Finished) {
				while (m_status.load() == DownloadStatus::Paused) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				BOOL readSuccess = InternetReadFile(m_hInternetRequest, buffer, 4096, &bytesRead);
				if (readSuccess && bytesRead > 0) {
					if (!WriteFile(fileHandle, buffer, bytesRead, nullptr, nullptr)) {
						goto ove1;
					}
					m_downloadedLength.fetch_add(bytesRead);
				}
			}
		ove1:
			bOver = true;
			thread.join();
			CloseHandle(fileHandle);
			success = m_downloadedLength.load() == totalLength;
			return success;
		}
		else
		{
			HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (fileHandle == INVALID_HANDLE_VALUE) {
				goto over;
			}
			while (bytesRead && m_status.load() != DownloadStatus::Finished) {
				while (m_status.load() == DownloadStatus::Paused) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				BOOL readSuccess = InternetReadFile(m_hInternetRequest, buffer, 4096, &bytesRead);
				if (readSuccess && bytesRead > 0) {
					if (!WriteFile(fileHandle, buffer, bytesRead, nullptr, nullptr)) {
						goto over;
					}
					m_downloadedLength.fetch_add(bytesRead);
				}
			}
		over:
			bOver = true;
			CloseHandle(fileHandle);
			success = m_downloadedLength.load() == totalLength;
			return success;
		}

	}
	void CCometHttp::QueryInfo()
	{

		//取HTTP状态
		QueryInfo(HTTP_QUERY_STATUS_CODE, m_nHttpStatus);
		//取内容长度
		QueryInfo(HTTP_QUERY_CONTENT_LENGTH, m_lContentLength);
		//取文件名
		QueryInfo(HTTP_QUERY_LOCATION, m_strLocation);
		//取服务器回传全部协议头
		QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, m_strRequest);
		//取回编码格式,是否UTF-8
		QueryInfo(HTTP_QUERY_CONTENT_TYPE, m_strContentType);
		//取回服务器时间
		QueryInfo(HTTP_QUERY_DATE, m_strDate);
		//AfxMessageBox(m_strRequest);

		//判断编码格式,是否GZIP
		m_nContentEncoding = HttpEncoding_NULL;
		DWORD dwBufferLength = 0;
		HttpQueryInfoW(m_hInternetRequest, HTTP_QUERY_CONTENT_ENCODING, NULL, &dwBufferLength, NULL);
		if (dwBufferLength > 0) {
			wchar_t* lpBuffer = new wchar_t[dwBufferLength] {};
			HttpQueryInfoW(m_hInternetRequest, HTTP_QUERY_CONTENT_ENCODING, lpBuffer, &dwBufferLength, NULL);
			if (lstrcmpW(lpBuffer, L"gzip") == 0) {
				m_nContentEncoding = HttpEncoding_GZIP;
			}
			else if (lstrcmpW(lpBuffer, L"deflate") == 0) {
				m_nContentEncoding = HttpEncoding_DEFLATE;
			}
			delete[]lpBuffer;
		}
		//取回Cookie
		m_strCookie = L"";
		std::string utf8str;
		DWORD dwIndex = 0;
		while (TRUE) {
			char* lpBuffer = NULL;
			dwBufferLength = 0;
			HttpQueryInfoW(m_hInternetRequest, HTTP_QUERY_SET_COOKIE, NULL, &dwBufferLength, &dwIndex);
			if (dwBufferLength < 1)break;
			lpBuffer = new char[dwBufferLength] {};
			HttpQueryInfoW(m_hInternetRequest, HTTP_QUERY_SET_COOKIE, lpBuffer, &dwBufferLength, &dwIndex);
			if (dwIndex > 1) {
				utf8str += "\r\n";
				utf8str.append(lpBuffer, dwBufferLength);
			}
			delete[] lpBuffer;
		}
		if (!utf8str.empty())
		{
			m_strCookie = elibstl::utf82utf16(utf8str.c_str()).data();
		}



		//AfxMessageBox(m_strRequest);
	}
	void CCometHttp::QueryInfo(DWORD dwInfoLevel, CString& strValue)
	{
		try {
			DWORD dwBufferLength = 0;
			HttpQueryInfoW(m_hInternetRequest, dwInfoLevel, NULL, &dwBufferLength, NULL);
			if (dwBufferLength > 0) {
				HttpQueryInfoW(m_hInternetRequest, dwInfoLevel, strValue.GetBuffer(dwBufferLength), &dwBufferLength, NULL);
				strValue.ReleaseBuffer();
			}
			else {
				strValue = _T("");
			}
		}
		catch (...) {

		}
	}
	void CCometHttp::QueryInfo(DWORD dwInfoLevel, int& nValue)
	{
		try {
			CString strValue;
			QueryInfo(dwInfoLevel, strValue);
			if (strValue == _T("")) {
				nValue = 0;
			}
			else {
				nValue = _wtoi(strValue);
			}
		}
		catch (...) {

		}
	}
	void CCometHttp::QueryInfo(DWORD dwInfoLevel, INT64& nValue)
	{
		CString strValue;
		QueryInfo(dwInfoLevel, strValue);
		if (strValue == _T("")) {
			nValue = 0;
		}
		else {
			nValue = _wtoi(strValue);
		}
	}


	BOOL CCometHttp::ReadFile()
	{
		if (m_lpResponseByte) {
			free(m_lpResponseByte);
			m_lpResponseByte = nullptr;
		}
		m_ResponseLength = 0;

		std::vector<unsigned char> MemFile;
		BYTE szBuff[1024] = { 0 };
		DWORD dwNumber = 1;

		while (dwNumber) {
			BOOL bRet = InternetReadFile(m_hInternetRequest, szBuff, 1024, &dwNumber);
			if (bRet && dwNumber > 0)
				MemFile.insert(MemFile.end(), szBuff, szBuff + dwNumber);
		}

		size_t dwLength = MemFile.size();
		if (dwLength > 0) {
			m_lpResponseByte = MemFile.data();
			m_ResponseLength = dwLength;
		}

		return dwLength > 0;
	}









	void CCometHttp::Close()
	{
		if (m_hInternetRequest)
			InternetCloseHandle(m_hInternetRequest);
		if (m_hInternetConnect)
			InternetCloseHandle(m_hInternetConnect);
		if (m_hInternetRequest)
			InternetCloseHandle(m_hInternetRequest);
		m_hInternetOpen = m_hInternetConnect = m_hInternetRequest = NULL;
	}
	typedef struct {
		CString strURL;//完整网址
		CString strVerb;//访问方式
		CString strProxy;//代理地址
		CString strHeader;//附加协议头
		LPVOID lpPostBuff;//POST提交信息,提交到服务器的表单信息
		DWORD dwPostLength;//POST数据长度
		BOOL	bGzip;//开启GZIP压缩
		DWORD	dwFlag;
		LPBYTE	lpByte;
		DWORD length;
		CString strRequest;
		CString strContentType;
		CString strCookie;
		CString strLocation;
		CString strDate;
		int nContentEncoding;
		INT64 lContentLength;
		int nHttpStatus;
		BOOL bReadFile;
		HANDLE hThread;
		DWORD dwThreadID;
	}CometHttp_Info, * LPCometHttp_Info;

	DWORD _stdcall GetHttpFile_Thread(LPVOID arg)
	{
		CometHttp_Info* pInfo = (CometHttp_Info*)arg;
		pInfo->nContentEncoding = 0;
		pInfo->lContentLength = 0;
		pInfo->nHttpStatus = 0;
		pInfo->strCookie = L"";
		pInfo->strRequest = L"";
		pInfo->strContentType = L"";
		pInfo->strLocation = L"";
		pInfo->hThread = GetCurrentThread();
		pInfo->dwThreadID = GetCurrentThreadId();
		//------------------
		CCometHttp http;

		if (!http.Open(pInfo->strProxy))return 0;

		if (!http.OpenURL(pInfo->strURL, pInfo->strVerb, pInfo->dwFlag))return 0;
		//------------------
		if (http.SendRequest(pInfo->strHeader, pInfo->bGzip, pInfo->lpPostBuff, pInfo->dwPostLength)) {
			pInfo->strCookie = http.m_strCookie;
			pInfo->strRequest = http.m_strRequest;
			pInfo->strContentType = http.m_strContentType;
			pInfo->strLocation = http.m_strLocation;
			pInfo->strDate = http.m_strDate;
			pInfo->nContentEncoding = http.m_nContentEncoding;
			pInfo->lContentLength = http.m_lContentLength;
			pInfo->nHttpStatus = http.m_nHttpStatus;
		}
		else {
			return 0;
		}
		//------------------
		if (pInfo->bReadFile)
		{
			if (http.ReadFile())
			{
				if (http.m_lpResponseByte != NULL && http.m_ResponseLength > 0) {
					pInfo->lpByte = http.m_lpResponseByte;
					pInfo->length = http.m_ResponseLength;
					http.m_lpResponseByte = NULL;
					http.m_ResponseLength = 0;
				}
			}
		}
		//------------------
		return 0;
	}


	void GetHttpFile(CometHttp_Info* pInfo)
	{
		pInfo->lpByte = NULL;
		pInfo->length = 0;
		pInfo->hThread = NULL;
		pInfo->dwThreadID = 0;
		HANDLE hProcess = GetCurrentProcess();
		HANDLE hThread = NULL;

		auto H = CreateThread(NULL, 0, GetHttpFile_Thread, pInfo, 0, NULL);
		if (H == nullptr)
			return;
		BOOL bRet = DuplicateHandle(hProcess, H, hProcess, &hThread, DUPLICATE_SAME_ACCESS,
			true, DUPLICATE_SAME_ACCESS);
		CloseHandle(H);
		DWORD dwMilliseconds = 90 * 1000; //超时值
		while (hThread) {
			DWORD dwRet = MsgWaitForMultipleObjects(1, &hThread, FALSE, dwMilliseconds, 1215);
			if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_TIMEOUT)
				break;
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				DispatchMessage(&msg);
				TranslateMessage(&msg);
			}
			Sleep(10);
		}
		if (hThread)
		{
			CloseHandle(hThread);
			hThread = NULL;
		}
	}
	void GetHttpFile(PMDATA_INF pArgInf, CometHttp_Info* pInfo, BOOL bReadFile, DWORD dwFlag)
	{

		pInfo->bGzip = FALSE;
		pInfo->dwFlag = 0;
		pInfo->lpPostBuff = NULL;
		pInfo->dwPostLength = 0;
		pInfo->strURL = elibstl::arg_to_wstring(pArgInf, 0).c_str();//完整网址
		pInfo->strVerb = elibstl::arg_to_wstring(pArgInf, 1).c_str();//访问方式
		pInfo->strProxy = elibstl::arg_to_wstring(pArgInf, 2).c_str();//代理地址
		pInfo->strHeader = elibstl::arg_to_wstring(pArgInf, 3).c_str();//附加协议头
		//pInfo->strPostBody	=(pArgInf[4].m_pText);//提交信息,提交到服务器的表单信息
		pInfo->bGzip = pArgInf[5].m_bool;
		pInfo->dwFlag = pArgInf[6].m_int | dwFlag;
		pInfo->bReadFile = bReadFile;

		//POST提交信息,提交到服务器的表单信息========================
		if (pArgInf[4].m_dtDataType == SDT_TEXT) {		//传递文本型参数
			pInfo->lpPostBuff = pArgInf[4].m_pText;
			pInfo->dwPostLength = strlen(pArgInf[4].m_pText);
		}
		else if (pArgInf[4].m_dtDataType == SDT_BIN) {//传递字节集参数
			if (pArgInf[4].m_pBin) {
				LPBYTE pData = pArgInf[4].m_pBin + sizeof(INT) * 2;
				INT nDataSize = *(LPINT)(pData - sizeof(INT));
				if (nDataSize > 0) {
					pInfo->lpPostBuff = pData;
					pInfo->dwPostLength = nDataSize;
				}
			}
		}

		// 参数<1>的名称为“完整网址”，类型为“文本型（text）”。完整的网页地址,比如http://www.it608.com。
		// 参数<2>的名称为“访问方式”，类型为“文本型（text）”，可以被省略。“GET”或 “POST”,为空默认“GET”。
		// 参数<3>的名称为“代理地址”，类型为“文本型（text）”，可以被省略。格式：HTTP=HTTP://proxyserver:port；FTP=FTP://proxyserver:port；GOPHER=HTTP://proxyserver:port；SOCKS=proxyserver:port。
		// 参数<4>的名称为“附加协议头”，类型为“文本型（text）”，可以被省略。自定义协议头。
		// 参数<5>的名称为“提交信息”，类型为“文本型（text）”，可以被省略。POST专用,提交到服务器的表单信息。
		// 参数<6>的名称为“开启GZIP压缩”，类型为“逻辑型（bool）”，初始值为“假”。开启GZIP压缩能提高网络传输速度,但返回的数据可能是GZIP压缩后的,部分服务器必须强制开启.
		// 参数<7>的名称为“附加标记”，类型为“整数型（int）”，初始值为“0”。可以使用 #HTTP标记.禁止缓存、#HTTP标记.禁止自动管理Cookie .. 等常量,多个常量请使用位或。
		// 参数<8>的名称为“返回Cookie”，类型为“文本型（text）”，可以被省略，提供参数数据时只能提供变量。返回服务器返回的协议头。
		// 参数<9>的名称为“返回网页头”，类型为“文本型（text）”，可以被省略，提供参数数据时只能提供变量。返回服务器返回的协议头。
		//--------------------------------
		GetHttpFile(pInfo);

	}
	struct Downld
	{
		std::wstring Url;
		std::wstring Path;
		BOOL bRet = FALSE;
		INT User;
		DownloadCallback p{ nullptr };
	};

	DWORD _stdcall DowndLoadFile_Thread(LPVOID arg)
	{
		Downld* S = (Downld*)arg;
		//------------------
		CCometHttp http;
		S->bRet = FALSE;
		if (!http.Open())
			return 0;

		if (!http.OpenURL(S->Url.data()))
			return 0;
		if (!http.SendRequest())
			return 0;

		S->bRet = http.DownloadFile(S->Path, S->p, S->User);
		return 0;
	}

	BOOL DowndLoadFile(const std::wstring& Url, const std::wstring& Path, DownloadCallback p, int userData)
	{
		Downld s;
		s.p = p;
		s.Path = Path;
		s.Url = Url;
		s.User = userData;

		HANDLE hProcess = GetCurrentProcess();
		HANDLE hThread = NULL;
		auto H = CreateThread(NULL, 0, DowndLoadFile_Thread, &s, 0, NULL);
		if (H == nullptr)
			return FALSE;
		BOOL bRet = DuplicateHandle(hProcess, H, hProcess, &hThread, DUPLICATE_SAME_ACCESS,
			true, DUPLICATE_SAME_ACCESS);
		CloseHandle(H);
		DWORD dwMilliseconds = 90 * 1000; //超时值
		while (hThread) {
			DWORD dwRet = MsgWaitForMultipleObjects(1, &hThread, FALSE, dwMilliseconds, 1215);
			if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_TIMEOUT)
				break;
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				DispatchMessage(&msg);
				TranslateMessage(&msg);
			}
			Sleep(10);
		}
		if (hThread)
		{
			CloseHandle(hThread);
			hThread = NULL;
		}
		return s.bRet;
	}


}




//////////////////////////////////////////////
//============================================  
extern "C" void elibstl_fn_GetHttpFile(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)	//0
{

	CometHttp_Info HttpInfo;
	GetHttpFile(pArgInf, &HttpInfo, TRUE, NULL);
	pRetData->m_pBin = elibstl::clone_bin(HttpInfo.lpByte, HttpInfo.length);
	elibstl::set_textw(pArgInf + 7, HttpInfo.strCookie);
	elibstl::set_textw(pArgInf + 8, HttpInfo.strRequest);
	//释放资源
	if (HttpInfo.lpByte)
	{
		free(HttpInfo.lpByte);
		HttpInfo.lpByte = NULL;
	}

}

extern "C" void elibstl_fn_DowndLoadFile(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)	//0
{
	pRetData->m_bool = DowndLoadFile(elibstl::arg_to_wstring(pArgInf, 0), elibstl::arg_to_wstring(pArgInf, 1), (DownloadCallback)elibstl::args_to_data<void*>(pArgInf, 2).value_or(nullptr), elibstl::args_to_data<int>(pArgInf, 3).value_or(0));
}


static ARG_INFO Args[] = {
{	//-- nIndex=0
		/*name*/	("完整网址"),
		/*explain*/	("完整的网页地址,比如https://github.com/AlongsCode/eLibStl；如果是路由器等需要帐号密码的服务器:http://admin:admin@192.168.1.1"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=1
	/*name*/	("访问方式"),
	/*explain*/	("“GET”或 “POST”、“HEAD”,为空默认“GET”"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=2
	/*name*/	("代理地址"),
	/*explain*/	("格式：HTTP=HTTP://proxyserver:port；FTP=FTP://proxyserver:port；GOPHER=HTTP://proxyserver:port；SOCKS=proxyserver:port"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=3
	/*name*/	("附加协议头"),
	/*explain*/	("自定义协议头,设置一些自定义的HTTP头,比如“Referer: www.baidu.com”、“cookie: Test Cookie”;设置了Cookie并且不希望系统自动添加Cookie,可以在“附加标记”里设置“#HTTP标记.禁止自动设置COOKIE”"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=4
	/*name*/	("提交信息"),
	/*explain*/	("POST专用,提交到服务器的表单信息,可以传递文本型或者字节集"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=5
	/*name*/	("GZIP压缩"),
	/*explain*/	("开启GZIP压缩能提高网络传输速度,但返回的数据可能是GZIP压缩后的,部分服务器必须强制开启.默认为假"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_BOOL,
	/*default*/	FALSE,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=6
	/*name*/	("附加标记"),
	/*explain*/	("可以使用 #HTTP标记.禁止缓存、#HTTP标记.禁止自动设置COOKIE .. 等常量,多个常量请使用位或,默认为0"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_INT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=7
	/*name*/	("返回Cookie"),
	/*explain*/	("取回服务器返回的Cookie"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
}, {	//-- nIndex=8
	/*name*/	("返回网页头"),
	/*explain*/	("取回服务器返回的协议头"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
}
};

FucInfo Fn_GetHttpFile = { {
		/*ccname*/  ("HTTP读文件W"),
		/*egname*/  ("GetHttpFileW"),
		/*explain*/ ("获取互联网上指定HTTP地址处的网页或数据文件，返回文件内容字节集"),
		/*category*/7,
		/*state*/   0,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ESTLARG(Args),
	} ,ESTLFNAME(elibstl_fn_GetHttpFile) };



static ARG_INFO Args2[] = {
{	//-- nIndex=0
		/*name*/	("完整网址"),
		/*explain*/	("完整的网页地址,比如https://github.com/AlongsCode/eLibStl；如果是路由器等需要帐号密码的服务器:http://admin:admin@192.168.1.1"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=0
	/*name*/	("保存文件的路径"),
	/*explain*/	("欲保存文件的路径,如果文件不存在则创建,但要确保父路径存在"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=0
	/*name*/	("回调函数"),
	/*explain*/	(R"(
原型:UserAction(CALLBACK*)(DownloadStatus, unsigned long long, unsigned long long, double, unsigned long long);

返回值 整数  
说明: #0:默认返回值,#1:结束该下载线程,#2:暂停该线程,#3:继续该线程

参数1: 线程状态  整数型 说明： #0:开始通知,#1:下载中,#2:暂停中,#3:结束通知
参数1: 总长度   长整数型
参数3: 下载速度 长整数型
参数4: 剩余大小 长整数型
参数5: 下载进度 双精度小数型
参数6: 下载用时 长整数型
参数6: 用户定义 整数型
)"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_SUB_PTR,
/*default*/	0,
/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
},{	//-- nIndex=0
	/*name*/	("用户附加参数"),
	/*explain*/	(R"(传递到会点函数中用户附加的参数)"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_INT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
	},
};
FucInfo Fn_DowndLoadFile = { {
		/*ccname*/  ("HTTP进度下载W"),
		/*egname*/  ("DowndLoadFileW"),
		/*explain*/ ("获取互联网上指定HTTP地址处的网页或数据文件，返回文件内容字节集"),
		/*category*/7,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ESTLARG(Args2),
	} ,ESTLFNAME(elibstl_fn_DowndLoadFile) };