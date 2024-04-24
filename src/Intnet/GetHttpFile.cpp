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
		CString m_strURL;//������ַ
		CString m_strDomain;//����
		CString m_strFile;//�ļ���ַ(����������)	
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
		LPCWSTR lpszProxy = NULL;//�����ַ
		LPCWSTR lpszProxyBypass = NULL;//����Ĳ���
		DWORD dwFlags = 0;
		if (strProxy != _T("")) {//���ݹ����Ĵ����ַ
			dwAccessType = INTERNET_OPEN_TYPE_PROXY;
			lpszProxy = strProxy;
		}

		m_hInternetOpen = InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
		if (m_hInternetOpen) {
			DWORD dwMilliseconds = 90 * 1000; //��ʱֵ
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
		// ����Э��ͷ-------
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
			// ������Ϣ��������----		
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

						//		// �ȴ�1��
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

		//ȡHTTP״̬
		QueryInfo(HTTP_QUERY_STATUS_CODE, m_nHttpStatus);
		//ȡ���ݳ���
		QueryInfo(HTTP_QUERY_CONTENT_LENGTH, m_lContentLength);
		//ȡ�ļ���
		QueryInfo(HTTP_QUERY_LOCATION, m_strLocation);
		//ȡ�������ش�ȫ��Э��ͷ
		QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, m_strRequest);
		//ȡ�ر����ʽ,�Ƿ�UTF-8
		QueryInfo(HTTP_QUERY_CONTENT_TYPE, m_strContentType);
		//ȡ�ط�����ʱ��
		QueryInfo(HTTP_QUERY_DATE, m_strDate);
		//AfxMessageBox(m_strRequest);

		//�жϱ����ʽ,�Ƿ�GZIP
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
		//ȡ��Cookie
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
		CString strURL;//������ַ
		CString strVerb;//���ʷ�ʽ
		CString strProxy;//�����ַ
		CString strHeader;//����Э��ͷ
		LPVOID lpPostBuff;//POST�ύ��Ϣ,�ύ���������ı���Ϣ
		DWORD dwPostLength;//POST���ݳ���
		BOOL	bGzip;//����GZIPѹ��
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
		DWORD dwMilliseconds = 90 * 1000; //��ʱֵ
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
		pInfo->strURL = elibstl::arg_to_wstring(pArgInf, 0).c_str();//������ַ
		pInfo->strVerb = elibstl::arg_to_wstring(pArgInf, 1).c_str();//���ʷ�ʽ
		pInfo->strProxy = elibstl::arg_to_wstring(pArgInf, 2).c_str();//�����ַ
		pInfo->strHeader = elibstl::arg_to_wstring(pArgInf, 3).c_str();//����Э��ͷ
		//pInfo->strPostBody	=(pArgInf[4].m_pText);//�ύ��Ϣ,�ύ���������ı���Ϣ
		pInfo->bGzip = pArgInf[5].m_bool;
		pInfo->dwFlag = pArgInf[6].m_int | dwFlag;
		pInfo->bReadFile = bReadFile;

		//POST�ύ��Ϣ,�ύ���������ı���Ϣ========================
		if (pArgInf[4].m_dtDataType == SDT_TEXT) {		//�����ı��Ͳ���
			pInfo->lpPostBuff = pArgInf[4].m_pText;
			pInfo->dwPostLength = strlen(pArgInf[4].m_pText);
		}
		else if (pArgInf[4].m_dtDataType == SDT_BIN) {//�����ֽڼ�����
			if (pArgInf[4].m_pBin) {
				LPBYTE pData = pArgInf[4].m_pBin + sizeof(INT) * 2;
				INT nDataSize = *(LPINT)(pData - sizeof(INT));
				if (nDataSize > 0) {
					pInfo->lpPostBuff = pData;
					pInfo->dwPostLength = nDataSize;
				}
			}
		}

		// ����<1>������Ϊ��������ַ��������Ϊ���ı��ͣ�text��������������ҳ��ַ,����http://www.it608.com��
		// ����<2>������Ϊ�����ʷ�ʽ��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ���GET���� ��POST��,Ϊ��Ĭ�ϡ�GET����
		// ����<3>������Ϊ�������ַ��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ���ʽ��HTTP=HTTP://proxyserver:port��FTP=FTP://proxyserver:port��GOPHER=HTTP://proxyserver:port��SOCKS=proxyserver:port��
		// ����<4>������Ϊ������Э��ͷ��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ��Զ���Э��ͷ��
		// ����<5>������Ϊ���ύ��Ϣ��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�POSTר��,�ύ���������ı���Ϣ��
		// ����<6>������Ϊ������GZIPѹ����������Ϊ���߼��ͣ�bool��������ʼֵΪ���١�������GZIPѹ����������紫���ٶ�,�����ص����ݿ�����GZIPѹ�����,���ַ���������ǿ�ƿ���.
		// ����<7>������Ϊ�����ӱ�ǡ�������Ϊ�������ͣ�int��������ʼֵΪ��0��������ʹ�� #HTTP���.��ֹ���桢#HTTP���.��ֹ�Զ�����Cookie .. �ȳ���,���������ʹ��λ��
		// ����<8>������Ϊ������Cookie��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԣ��ṩ��������ʱֻ���ṩ���������ط��������ص�Э��ͷ��
		// ����<9>������Ϊ��������ҳͷ��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԣ��ṩ��������ʱֻ���ṩ���������ط��������ص�Э��ͷ��
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
		DWORD dwMilliseconds = 90 * 1000; //��ʱֵ
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
	//�ͷ���Դ
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
		/*name*/	("������ַ"),
		/*explain*/	("��������ҳ��ַ,����https://github.com/AlongsCode/eLibStl�������·��������Ҫ�ʺ�����ķ�����:http://admin:admin@192.168.1.1"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=1
	/*name*/	("���ʷ�ʽ"),
	/*explain*/	("��GET���� ��POST������HEAD��,Ϊ��Ĭ�ϡ�GET��"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=2
	/*name*/	("�����ַ"),
	/*explain*/	("��ʽ��HTTP=HTTP://proxyserver:port��FTP=FTP://proxyserver:port��GOPHER=HTTP://proxyserver:port��SOCKS=proxyserver:port"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=3
	/*name*/	("����Э��ͷ"),
	/*explain*/	("�Զ���Э��ͷ,����һЩ�Զ����HTTPͷ,���硰Referer: www.baidu.com������cookie: Test Cookie��;������Cookie���Ҳ�ϣ��ϵͳ�Զ����Cookie,�����ڡ����ӱ�ǡ������á�#HTTP���.��ֹ�Զ�����COOKIE��"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=4
	/*name*/	("�ύ��Ϣ"),
	/*explain*/	("POSTר��,�ύ���������ı���Ϣ,���Դ����ı��ͻ����ֽڼ�"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=5
	/*name*/	("GZIPѹ��"),
	/*explain*/	("����GZIPѹ����������紫���ٶ�,�����ص����ݿ�����GZIPѹ�����,���ַ���������ǿ�ƿ���.Ĭ��Ϊ��"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_BOOL,
	/*default*/	FALSE,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=6
	/*name*/	("���ӱ��"),
	/*explain*/	("����ʹ�� #HTTP���.��ֹ���桢#HTTP���.��ֹ�Զ�����COOKIE .. �ȳ���,���������ʹ��λ��,Ĭ��Ϊ0"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_INT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
}, {	//-- nIndex=7
	/*name*/	("����Cookie"),
	/*explain*/	("ȡ�ط��������ص�Cookie"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
}, {	//-- nIndex=8
	/*name*/	("������ҳͷ"),
	/*explain*/	("ȡ�ط��������ص�Э��ͷ"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
}
};

FucInfo Fn_GetHttpFile = { {
		/*ccname*/  ("HTTP���ļ�W"),
		/*egname*/  ("GetHttpFileW"),
		/*explain*/ ("��ȡ��������ָ��HTTP��ַ������ҳ�������ļ��������ļ������ֽڼ�"),
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
		/*name*/	("������ַ"),
		/*explain*/	("��������ҳ��ַ,����https://github.com/AlongsCode/eLibStl�������·��������Ҫ�ʺ�����ķ�����:http://admin:admin@192.168.1.1"),
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=0
	/*name*/	("�����ļ���·��"),
	/*explain*/	("�������ļ���·��,����ļ��������򴴽�,��Ҫȷ����·������"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	_SDT_ALL,
	/*default*/	0,
	/*state*/	ArgMark::AS_NONE
}, {	//-- nIndex=0
	/*name*/	("�ص�����"),
	/*explain*/	(R"(
ԭ��:UserAction(CALLBACK*)(DownloadStatus, unsigned long long, unsigned long long, double, unsigned long long);

����ֵ ����  
˵��: #0:Ĭ�Ϸ���ֵ,#1:�����������߳�,#2:��ͣ���߳�,#3:�������߳�

����1: �߳�״̬  ������ ˵���� #0:��ʼ֪ͨ,#1:������,#2:��ͣ��,#3:����֪ͨ
����1: �ܳ���   ��������
����3: �����ٶ� ��������
����4: ʣ���С ��������
����5: ���ؽ��� ˫����С����
����6: ������ʱ ��������
����6: �û����� ������
)"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_SUB_PTR,
/*default*/	0,
/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
},{	//-- nIndex=0
	/*name*/	("�û����Ӳ���"),
	/*explain*/	(R"(���ݵ���㺯�����û����ӵĲ���)"),
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_INT,
	/*default*/	0,
	/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
	},
};
FucInfo Fn_DowndLoadFile = { {
		/*ccname*/  ("HTTP��������W"),
		/*egname*/  ("DowndLoadFileW"),
		/*explain*/ ("��ȡ��������ָ��HTTP��ַ������ҳ�������ļ��������ļ������ֽڼ�"),
		/*category*/7,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ESTLARG(Args2),
	} ,ESTLFNAME(elibstl_fn_DowndLoadFile) };