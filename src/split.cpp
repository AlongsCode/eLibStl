#include"ElibHelp.h"
#include <algorithm>


static  std::vector<LPBYTE> split_text(const std::wstring& text, const  std::wstring& str, size_t count) {
	std::vector<LPBYTE> ret;
	if (str.empty() || text == L"")
	{
		ret.push_back(elibkrnln::clone_textw(text));
		return ret;
	}
	size_t start = 0, index = text.find_first_of(str, 0);
	while (index != text.npos)
	{
		if (start != index)
			ret.push_back(elibkrnln::clone_textw(text.substr(start, index - start)));
		start = index + 1;
		index = text.find_first_of(str, start);
	}
	if (text.substr(start) != L"")
	{
		ret.push_back(elibkrnln::clone_textw(text.substr(start)));
	}
	if (count != -1 && count <= ret.size())
	{
		ret.resize(count);
	}
	return ret;
}


static ARG_INFO WArgs[] =
{
	{
		/*name*/    "待分割文本",
		/*explain*/ ("如果参数值是一个长度为零的文本，则返回一个空数组，即没有任何成员的数组"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "参数值用于标识子文本边界。如果被省略，则默认使用半角逗号字符作为分隔符。如果是一个长度为零的文本，则返回的数组仅包含一个成员，即完整的“待分割文本”",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "要返回的子文本数目",
		/*explain*/ ("如果被省略，则默认返回所有的子文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_splitW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibkrnln::args_to_wsdata(pArgInf, 0),
		search = elibkrnln::args_to_wsdata(pArgInf, 1);
	std::optional<INT> count = elibkrnln::args_to_data<INT>(pArgInf, 2);
	std::wstring s = L",";
	if (!search.empty()) {
		s = std::wstring(search);
	}
	std::vector<LPBYTE> ret = split_text(std::wstring(text), s, count.has_value() && count.value() > 0 ? count.value() : -1);
	pRetData->m_pAryData = elibkrnln::create_array<LPBYTE>(ret.data(), ret.size());

}

FucInfo split_w = { {
		/*ccname*/  ("分割文本W"),
		/*egname*/  ("splitW"),
		/*explain*/ ("将指定文本进行分割，返回分割后的一维文本数组。"),
		/*category*/2,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  &WArgs[0],
	} ,Fn_splitW ,"Fn_splitW" };



