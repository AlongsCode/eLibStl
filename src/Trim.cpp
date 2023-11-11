#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲删除空格的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_LTrimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = elibstl::arg_to_wstring(pArgInf, 0);
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(0, text.find_first_not_of(L" "));
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo ltrim_w = { {
		/*ccname*/  ("删首空W"),
		/*egname*/  ("LTrimW"),
		/*explain*/ ("返回一个文本，其中包含被删除了首部全角或半角空格的指定文本."),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_LTrimW ,"Fn_LTrimW" };



EXTERN_C void Fn_RTrimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(text.find_last_not_of(L" ") + 1);
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo rtrim_w = { {
		/*ccname*/  ("删尾空W"),
		/*egname*/  ("RTrimW"),
		/*explain*/ (" 返回一个文本，其中包含被删除了尾部全角或半角空格的指定文本。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_RTrimW ,"Fn_RTrimW" };

EXTERN_C void Fn_trimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(0, text.find_first_not_of(L" "));
	text.erase(text.find_last_not_of(L" ") + 1);
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo trim_w = { {
		/*ccname*/  ("删首尾空W"),
		/*egname*/  ("trimW"),
		/*explain*/ ("返回一个文本，其中包含被删除了首部及尾部全角或半角空格的指定文本。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_trimW ,"Fn_trimW" };

EXTERN_C void Fn_TrimAllW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	std::wstring mark = L" ";
	size_t nSize = mark.size();
	if (text.empty() || text == L"") {
		return;
	}
	while (1)
	{
		size_t pos = text.find(mark);    //  尤其是这里
		if (pos == std::wstring::npos)
		{
			pRetData->m_pBin = elibstl::clone_textw(text);
			return;
		}
		text.erase(pos, nSize);
	}
}
FucInfo trim_all_w = { {
		/*ccname*/  ("删全部空W"),
		/*egname*/  ("TrimAllW"),
		/*explain*/ ("返回一个文本，其中包含被删除了所有全角或半角空格的指定文本。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_TrimAllW ,"Fn_TrimAllW" };

