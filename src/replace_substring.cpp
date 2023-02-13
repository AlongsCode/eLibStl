#include"ElibHelp.h"
#include <algorithm>





static ARG_INFO WArgs[] =
{
	{
		/*name*/    "欲被替换的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲被替换的子文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "用作替换的子文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "进行替换的起始位置",
		/*explain*/ ("参数值指定被替换子文本的起始搜索位置。如果省略，默认从 1 开始。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "进行替换的次数",
		/*explain*/ ("参数值指定对子文本进行替换的次数。如果省略，默认进行所有可能的替换。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "是否区分大小写",
		/*explain*/ ("为真区分大小写，为假不区分"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

static LPBYTE
replace_substring(std::wstring text,
	std::wstring to_replace,
	const  std::wstring& replace_with,
	std::optional<size_t> start_pos,
	std::optional<size_t> replace_count,
	std::optional<BOOL> case_sensitive) {
	size_t search_start = start_pos.value_or(0);
	search_start -= 1;
	if (search_start < 0)
	{
		search_start = 0;
	}
#undef max
	size_t count = replace_count.value_or(std::numeric_limits<size_t>::max());
	bool sensitive = case_sensitive.value_or(true);
	std::wstring replace = replace_with.empty() ? L"" : replace_with;
	if (!sensitive) {
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		std::transform(to_replace.begin(), to_replace.end(), to_replace.begin(), ::tolower);
	}
	size_t pos = text.find(to_replace, search_start);
	while (pos != std::string::npos && count > 0) {
		text.replace(pos, to_replace.length(), replace);
		pos = text.find(to_replace, pos + replace.length());
		--count;
	}
	return elibstl::clone_textw(text);
}



EXTERN_C void Fn_replace_substringW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0),
		to_replace = elibstl::args_to_wsdata(pArgInf, 1),
		replace_with = elibstl::args_to_wsdata(pArgInf, 2);
	std::optional<INT> start_pos = elibstl::args_to_data<INT>(pArgInf, 3);
	std::optional<INT> replace_count = elibstl::args_to_data<INT>(pArgInf, 4);
	std::optional<BOOL> case_sensitive = elibstl::args_to_data<BOOL>(pArgInf, 5);
	//因为字节集传递宽字符并不是按照win2字节linux3字节固定，而是任意字节数，所以此位置再次使用wstring拷贝格式化一下,但是肯定会影响效率，不过微乎其微.
	pRetData->m_pBin = replace_substring(std::wstring(text), std::wstring(to_replace), std::wstring(replace_with), start_pos, replace_count, case_sensitive);
}

FucInfo replace_substring_w = { {
		/*ccname*/  ("子文本替换W"),
		/*egname*/  ("replace_substringW"),
		/*explain*/ ("返回一个文本，该文本中指定的子文本已被替换成另一子文本，并且替换发生的次数也是被指定的"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/6,
		/*arg lp*/  &WArgs[0],
	} ,Fn_replace_substringW ,"Fn_replace_substringW" };



