#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ ("欲判断的文件"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void _Fn_IsFileExistW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_bool = PathFileExistsW(elibstl::arg_to_wstring(pArgInf, 0).c_str());
}

FucInfo Fn_IsFileExistW = { {
		/*ccname*/  ("文件是否存在W"),
		/*egname*/  ("IsFileExistW"),
		/*explain*/ (" 判断指定的磁盘文件是否真实存在。如存在返回真，否则返回假。"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,_Fn_IsFileExistW ,"_Fn_IsFileExistW" };

