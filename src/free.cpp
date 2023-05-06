#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
			"内存指针",
			"",
			0,
			0,
			SDT_INT,
			0,
			NULL,
		}

};
EXTERN_C void Fn_e_free(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::free(reinterpret_cast<void*>(pArgInf[0].m_int));
}

FucInfo e_free = { {
		/*ccname*/  ("内存释放"),
		/*egname*/  ("free"),
		/*explain*/ ("释放所申请的内存。"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_e_free ,"Fn_e_free" };
