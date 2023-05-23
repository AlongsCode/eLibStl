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

ESTL_NAMESPACE_END