#include"ElibHelp.h"
#include <random>
#undef max
static ARG_INFO Args[] =
{
	{
		/*name*/    "��ת���Ļ���ֵ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_DOUBLE,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_rtoa(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = (double)pArgInf->m_double * 180 / 3.1415926535;
}

FucInfo rtoa = { {
		/*ccname*/  ("���ȵ��Ƕ�"),
		/*egname*/  (""),
		/*explain*/ ("�����Ƶ��Ƕ���"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_DOUBLE,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_rtoa ,"Fn_rtoa" };
static ARG_INFO Args2[] =
{
	{
		/*name*/    "��ת���ĽǶ�ֵ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_DOUBLE,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_ator(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = (double)pArgInf->m_double * 3.1415926535 / 180;
}

FucInfo ator = { {
		/*ccname*/  ("�Ƕȵ�����"),
		/*egname*/  (""),
		/*explain*/ ("�Ƕ��Ƶ�������"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_DOUBLE,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args2[0],
	} ,Fn_ator ,"Fn_ator" };

