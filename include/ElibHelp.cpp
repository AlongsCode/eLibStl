#include"ElibHelp.h"
#include"elib/lang.h"
ESTL_NAMESPACE_BEGIN
bool CallElibFunc(const char* elib_name, const char* def_name, PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	PFN_EXECUTE_CMD pEdef = nullptr;
	HMODULE hModule = ::LoadLibraryA(elib_name);
	if (hModule == NULL) {
		HKEY hKey = nullptr;
		LSTATUS status = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\FlySky\\E\\Install", 0, KEY_EXECUTE, &hKey);
		if (status != ERROR_SUCCESS)
			return false;

		DWORD dataSize = MAX_PATH;
		char buffer[MAX_PATH] = { 0 };
		status = RegQueryValueExA(hKey, "Path", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &dataSize);
		RegCloseKey(hKey);
		if (status != ERROR_SUCCESS)
			return false;
		std::string krnlnPath = buffer;
		if (krnlnPath.back() != '\\')
			krnlnPath.push_back('\\');
		krnlnPath += elib_name;
		hModule = ::LoadLibraryA(krnlnPath.c_str());
	}
	if (hModule == NULL)return false;
	PFN_GET_LIB_INFO pfn_GetNewInfo = reinterpret_cast<PFN_GET_LIB_INFO>(::GetProcAddress(hModule, "GetNewInf"));
	if (pfn_GetNewInfo == nullptr) {
		::FreeLibrary(hModule); return false;
	}

	PLIB_INFO pLibInfo = pfn_GetNewInfo();
	if (pLibInfo == nullptr) {
		::FreeLibrary(hModule); return false;
	}

	int nCmdCount = pLibInfo->m_nCmdCount;
	PCMD_INFO pCmdsInfo = pLibInfo->m_pBeginCmdInfo;
	PFN_EXECUTE_CMD* pCmdsFun = pLibInfo->m_pCmdsFunc;
	for (int i = 0; i < nCmdCount; i++)
	{
		if (!pCmdsInfo[i].m_szName || !pCmdsInfo[i].m_szName[0])
			continue;
		if (strcmp(pCmdsInfo[i].m_szName, def_name) == 0)
		{
			pEdef = pCmdsFun[i];
			break;
		}
	}
	if (!pEdef)
	{
		::FreeLibrary(hModule);
		return false;
	}
	pEdef(pRetData, nArgCount, pArgInf);
	::FreeLibrary(hModule);
	return true;

}

PSTR W2A(PCWSTR pszW)
{
	int iBufSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pszW, -1, NULL, 0, NULL, NULL);
	PSTR pszA = new CHAR[iBufSize + 1];
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pszW, -1, pszA, iBufSize, NULL, NULL);
	return pszA;
}

PWSTR A2W(PCSTR pszA)
{
	int iBufSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszA, -1, NULL, 0);
	PWSTR pszW = new WCHAR[iBufSize + 1];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszA, -1, pszW, iBufSize);
	return pszW;
}

PSTR W2UTF8(const std::wstring_view& text)
{
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.length()), nullptr, 0, nullptr, nullptr);
	PSTR pszW = new CHAR[utf8Length + 1];
	WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.length()), pszW, utf8Length, nullptr, nullptr);
	pszW[utf8Length] = '\0';
	return pszW;
}

LPSTR A2UTF8(const std::string_view& text)
{
	int wideLength = MultiByteToWideChar(CP_ACP, 0, text.data(), static_cast<int>(text.length()), nullptr, 0);
	std::wstring wideText(wideLength, L'\0');
	MultiByteToWideChar(CP_ACP, 0, text.data(), static_cast<int>(text.length()), &wideText[0], wideLength);

	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, nullptr, 0, nullptr, nullptr);
	LPSTR pszUTF8 = new CHAR[utf8Length + 1];
	WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, pszUTF8, utf8Length, nullptr, nullptr);
	pszUTF8[utf8Length] = '\0';
	return pszUTF8;
}

int CSimpleRefStrW::DupString(PCWSTR pszSrc, int cchSrc)
{
	if (!pszSrc || !cchSrc)
	{
	NullStr:
		m_cchText = 0;
		if (m_pszText)
			*m_pszText = L'\0';
		return 0;
	}

	if (cchSrc < 0)
		cchSrc = wcslen(pszSrc);
	if (!cchSrc)
		goto NullStr;
	if (m_cchCapacity < cchSrc + 1)
	{
		m_cchCapacity = SRSMakeCapacity(cchSrc + 1);
		if (m_pszText)
			m_pszText = SRSReAllocW(m_pszText, m_cchCapacity);
		else
			m_pszText = SRSAllocW(m_cchCapacity);
	}
	m_cchText = cchSrc;
	wcsncpy(m_pszText, pszSrc, cchSrc);
	*(m_pszText + cchSrc) = L'\0';
}

PWSTR CSimpleRefStrW::Attach(PWSTR psz, int cchCapacity, int cchText)
{
	auto pTemp = m_pszText;
	if (!psz)
	{
		m_cchCapacity = 0;
		m_cchText = 0;
		m_pszText = NULL;
		return pTemp;
	}
	m_cchCapacity = cchCapacity;
	if (cchText < 0)
		m_cchText = wcslen(psz);
	else
		m_cchText = cchText;
	m_pszText = psz;
	return pTemp;
}

int CSimpleRefStrW::PushBack(PCWSTR pszSrc, int cchSrc)
{
	if (!pszSrc || !cchSrc)
		return 0;
	if (cchSrc < 0)
		cchSrc = wcslen(pszSrc);
	if (!cchSrc)
		return 0;
	if (m_cchCapacity < m_cchText + cchSrc + 1)
	{
		m_cchCapacity = SRSMakeCapacity(m_cchText + cchSrc + 1);
		m_pszText = SRSReAllocW(m_pszText, m_cchCapacity);
	}
	wcsncpy(m_pszText + m_cchText, pszSrc, cchSrc);
	m_cchText += cchSrc;
	*(m_pszText + m_cchText) = L'\0';
}

ESTL_NAMESPACE_END