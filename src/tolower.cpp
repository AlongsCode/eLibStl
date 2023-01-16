#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换小写的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_tolowerW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	std::wstring ret(text);
	std::transform(text.begin(), text.end(), ret.begin(), tolower);
	pRetData->m_pBin = elibstl::clone_textw(ret);
}
FucInfo  to_lower_w = { {
		/*ccname*/  ("到小写W"),
		/*egname*/  ("tolowerW"),
		/*explain*/ ("转换指定文本为夏小写。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_tolowerW ,"Fn_tolowerW" };

