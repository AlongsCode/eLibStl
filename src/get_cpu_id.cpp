#include"intrin.h"
#include"ElibHelp.h"

/*可以使用内联汇编，这里是从代码里扣的为了兼容x64*/

EXTERN_C void Fn_get_cpu_id(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int cpuid[4] = {};
	char cpuid_buf[17] = {};
	__cpuid(cpuid, 1);
	sprintf_s(cpuid_buf, "%08X%08X", cpuid[3], cpuid[0]);
	pRetData->m_pText = elibstl::clone_text(cpuid_buf);
}


FucInfo get_cpu_id = { {
		/*ccname*/  ("取CPU序列号"),
		/*egname*/  ("get_cpu_id"),
		/*explain*/ ("获取CPU序列号"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_TEXT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_cpu_id ,"Fn_get_cpu_id" };