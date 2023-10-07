#include"EcontrolHelp.h"
#include<cmath>

/*向下取整*/
static ARG_INFO s_CopyArgs[] =
{
	{
		/*name*/    "欲取整的小数",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/	SDT_DOUBLE,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
EXTERN_C void Fn_Epl_Floor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = static_cast<int>(::std::floor(pArgInf->m_double));
}



FucInfo Fn_Floor = { {
		/*ccname*/  "向下取整",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ 1,
		/*state*/   _CMD_OS(__OS_WIN),
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_CopyArgs,
	} ,Fn_Epl_Floor ,"Fn_Epl_Floor" };

EXTERN_C void Fn_Epl_Ceil(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = static_cast<int>(::std::ceil(pArgInf->m_double));
}


FucInfo Fn_Ceil = { {
		/*ccname*/  "向上取整",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ 1,
		/*state*/   _CMD_OS(__OS_WIN),
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_CopyArgs,
	} ,Fn_Epl_Ceil ,"Fn_Epl_Ceil" };