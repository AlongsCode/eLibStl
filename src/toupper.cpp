#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换大写的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_toupperW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	std::wstring ret(text);
	std::transform(text.begin(), text.end(), ret.begin(), toupper);
	pRetData->m_pBin = elibstl::clone_textw(ret);
}
FucInfo to_upper_w = { {
		/*ccname*/  ("到大写W"),
		/*egname*/  ("toupperW"),
		/*explain*/ ("转换指定文本为大写。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_toupperW ,"Fn_toupperW" };

