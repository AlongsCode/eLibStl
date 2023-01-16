#include"ElibHelp.h"


EXTERN_C void Fn_is_64_bit(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	pRetData->m_bool = (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64);
}

FucInfo is_64_bit = { {
		/*ccname*/  ("是否为64位系统"),
		/*egname*/  ("Is64Bit"),
		/*explain*/ ("判断当前运行操作系统是否为64位架构"),
		/*category*/3,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_is_64_bit ,"Fn_is_64_bit" };
