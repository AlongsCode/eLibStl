#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"�ڴ�ָ��",
		"",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		NULL,
	}
};
EXTERN_C void Fn_e_free(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::free(reinterpret_cast<void*>(pArgInf[0].m_int));
}

FucInfo e_free = { {
		/*ccname*/  ("�ڴ��ͷ�"),
		/*egname*/  ("free"),
		/*explain*/ ("�ͷ���������ڴ档"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_e_free ,"Fn_e_free" };
