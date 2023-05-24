#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ ("��ת����д���ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
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
		/*ccname*/  ("����дW"),
		/*egname*/  ("toupperW"),
		/*explain*/ ("ת��ָ���ı�Ϊ��д��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_toupperW ,"Fn_toupperW" };

