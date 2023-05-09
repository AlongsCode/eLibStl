#include"ElibHelp.h"

EXTERN_C void Fn_to_string(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_dtDataType == SDT_BIN) {
		pRetData->m_pBin = pArgInf->m_pBin;
		return;
	}
	pRetData->m_pBin = elibstl::clone_textw(elibstl::arg_to_wstring(*pArgInf)), static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE));
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "欲转换的数据",
		/*explain*/ ("欲转换的数据"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA,
	},{
		/*name*/    "是否包含结束符",
		/*explain*/ ("默认包含结束符"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

FucInfo   eto_wstring = { {
		/*ccname*/  ("到文本W"),
		/*egname*/  ("to_wstring"),
		/*explain*/ ("转换指定数据为文本。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} , Fn_to_string ,"Fn_to_string" };

