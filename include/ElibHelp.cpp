#include"ElibHelp.h"
#include"elib/lang.h"
namespace elibstl {

	//调用易语言支持库函数
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

}