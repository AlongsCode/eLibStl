#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "�ļ���",
		/*explain*/ ("���жϵ��ļ�"),
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
		/*ccname*/  ("�ļ��Ƿ����W"),
		/*egname*/  ("IsFileExistW"),
		/*explain*/ (" �ж�ָ���Ĵ����ļ��Ƿ���ʵ���ڡ�����ڷ����棬���򷵻ؼ١�"),
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

