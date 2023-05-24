#include"ElibHelp.h"


EXTERN_C void Fn_is_64_bit(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	pRetData->m_bool = (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64);
}

FucInfo is_64_bit = { {
		/*ccname*/  ("�Ƿ�Ϊ64λϵͳ"),
		/*egname*/  ("Is64Bit"),
		/*explain*/ ("�жϵ�ǰ���в���ϵͳ�Ƿ�Ϊ64λ�ܹ�"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_is_64_bit ,"Fn_is_64_bit" };
