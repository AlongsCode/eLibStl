#include"ElibHelp.h"
#include <random>
#undef max
static ARG_INFO Args[] =
{
	{
		/*name*/    "欲转换的弧度值",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_DOUBLE,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_rtoa(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = (double)pArgInf->m_double * 180 / 3.1415926535;
}

FucInfo rtoa = { {
		/*ccname*/  ("弧度到角度"),
		/*egname*/  (""),
		/*explain*/ ("弧度制到角度制"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     SDT_DOUBLE,
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
		/*name*/    "欲转换的角度值",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_DOUBLE,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_ator(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = (double)pArgInf->m_double * 3.1415926535 / 180;
}

FucInfo ator = { {
		/*ccname*/  ("角度到弧度"),
		/*egname*/  (""),
		/*explain*/ ("角度制到弧度制"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     SDT_DOUBLE,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args2[0],
	} ,Fn_ator ,"Fn_ator" };

