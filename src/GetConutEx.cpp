#include"ElibHelp.h"
typedef struct _SYSTEM_TIME_INFORMATION {
	LARGE_INTEGER BootTime;
	LARGE_INTEGER CurrentTime;
	LARGE_INTEGER TimeZoneBias;
	ULONG TimeZoneId;
	ULONG Reserved;
	ULONGLONG BootTimeBias;
	ULONGLONG SleepTimeBias;
} SYSTEM_TIME_INFORMATION, * PSYSTEM_TIME_INFORMATION;
typedef NTSTATUS(WINAPI* PROCNTQSI)(
	UINT,
	SYSTEM_TIME_INFORMATION*,
	ULONG,
	PULONG
	);


EXTERN_C void Fn_e_GetTickCount_ex(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SYSTEM_TIME_INFORMATION sysTimeInfo{ 0 };
	ULONG ret;

	HMODULE hNtDll = LoadLibraryA("ntdll.dll");
	if (!hNtDll) {
		pRetData->m_int64 = -1;
		return;
	}

	PROCNTQSI NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(hNtDll, "NtQuerySystemInformation");
	if (!NtQuerySystemInformation) {
		FreeLibrary(hNtDll);
		pRetData->m_int64 = -1;
		return;
	}

	if (NtQuerySystemInformation(3, &sysTimeInfo, sizeof(sysTimeInfo), &ret) != 0) {
		FreeLibrary(hNtDll);
		pRetData->m_int64 = -1;
		return;
	}

	ULONGLONG bootTime = sysTimeInfo.BootTime.QuadPart;
	ULONGLONG currentTime = sysTimeInfo.CurrentTime.QuadPart;
	pRetData->m_int64 = currentTime - bootTime;

}


FucInfo e_GetTickCount_ex = { {
		/*ccname*/  ("取启动时间Ex"),
		/*egname*/  ("GetTickCount"),
		/*explain*/ ("高精度获取启动时间,单位100纳秒,需获取毫秒的话请乘以10000"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT64 ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_e_GetTickCount_ex ,"Fn_e_GetTickCount_ex" };