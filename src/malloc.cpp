#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"���볤��",
		"",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		NULL,
	},
	{
		"�Ƿ��ʼ��Ϊ��",
		"",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}

};

EXTERN_C void Fn_e_malloc(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = 0;
	auto p = std::malloc(pArgInf[0].m_int);
	if (!p)
	{
		return;
	}
	if (pArgInf[1].m_dtDataType != DATA_TYPE::_SDT_NULL && pArgInf[1].m_bool)
	{
		std::memset(p, 0, pArgInf[0].m_int);
	}
	pRetData->m_int = reinterpret_cast<size_t>(p);
}

FucInfo e_malloc = { {
		/*ccname*/  ("�ڴ�����"),
		/*egname*/  ("malloc"),
		/*explain*/ ("�˴��������ڴ治����������ide�����ü���,��ȫ�ɳ���Ա����,�������ͷš�"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_e_malloc ,"Fn_e_malloc" };
