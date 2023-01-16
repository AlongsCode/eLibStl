#include"ElibHelp.h"
#include <algorithm>

#pragma comment(lib,"Mpr.lib")
static std::vector<LPBYTE> GetNetworkTypes()
{
	std::vector<LPBYTE> result;
	DWORD dwResultEnum, cbBuffer = 16384, cEntries = -1;
	HANDLE hEnum;
	LPNETRESOURCEW lpnrLocal;
	if (!WNetOpenEnumW(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, 0, &hEnum))
	{
		lpnrLocal = (LPNETRESOURCEW)new char[cbBuffer];
		if (lpnrLocal != NULL) {
			do {
				ZeroMemory(lpnrLocal, cbBuffer);
				dwResultEnum = WNetEnumResourceW(hEnum, &cEntries, lpnrLocal, &cbBuffer);
				if (dwResultEnum == NO_ERROR) {
					for (DWORD i = 0; i < cEntries; i++) {
						if (lpnrLocal[i].lpRemoteName)
						{
							result.push_back(elibkrnln::clone_textw(lpnrLocal[i].lpRemoteName));
						}
						else if (lpnrLocal[i].lpProvider)
						{
							result.push_back(elibkrnln::clone_textw(lpnrLocal[i].lpProvider));
						}
					}
				}
				else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
					DWORD errCode = GetLastError();
					// handle error according to errCode
					break;
				}
			} while (dwResultEnum != ERROR_NO_MORE_ITEMS);
			delete[] lpnrLocal;
		}
		WNetCloseEnum(hEnum);
	}
	return result;
}


EXTERN_C void Fn_GetNetworkTypesW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::vector<LPBYTE> ret = GetNetworkTypes();
	pRetData->m_pAryData = elibkrnln::create_array<LPBYTE>(ret.data(), ret.size());

}

FucInfo get_net_work_types_w = { {
		/*ccname*/  ("枚举网络类型W"),
		/*egname*/  ("GetNetworkTypesW"),
		/*explain*/ ("枚举所有的网络类型。"),
		/*category*/7,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_GetNetworkTypesW ,"Fn_GetNetworkTypesW" };



