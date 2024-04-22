#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_lenA(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::string_view
		text = elibstl::args_to_sdata(pArgInf, 0);
	pRetData->m_int = text.length();
}
FucInfo strlen_a = { {
		/*ccname*/  ("ȡ�ı�����A"),
		/*egname*/  ("lenA"),
		/*explain*/ ("ȡ�ı������ݵĳ��ȣ�����������0��"),
		/*category*/2,
		/*state*/   CT_IS_HIDED,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_lenA ,"Fn_lenA" };


static ARG_INFO WArgs[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_lenW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_int = text.length();
}
FucInfo wcslen_w = { {
		/*ccname*/  ("ȡ�ı�����W"),
		/*egname*/  ("lenW"),
		/*explain*/ ("ȡ�ı������ݵĳ��ȣ�����������0��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,Fn_lenW ,"Fn_lenW" };