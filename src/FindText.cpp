#include"ElibHelp.h"
#include <algorithm>
//#include"include\krnln.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "被搜寻的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲寻找的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "起始搜寻位置",
		/*explain*/ ("位置值从 1 开始。如果本参数被省略，默认为 1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "是否不区分大小写",
		/*explain*/ ("为真不区分大小写，为假区分。默认为“假”。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

static intptr_t find_text(const std::string_view& text, const std::string_view& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		//需要转换大小写再拷贝
		std::string formatted_text = text.data();
		std::string formatted_search = search.data();
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos - 1);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.data(), start_pos - 1);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
}

static intptr_t find_text(const std::string_view& text, const std::string_view& search, size_t start_pos)
{


	intptr_t ret = text.find(search.data(), start_pos - 1);
	if (ret != text.npos) {
		return ret + 1;
	}
	return -1;

}

EXTERN_C void Fn_InStrA(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::string_view
		text = elibstl::args_to_sdata(pArgInf, 0),
		search = elibstl::args_to_sdata(pArgInf, 1);
	std::optional<INT> pos = elibstl::args_to_data<INT>(pArgInf, 2);
	std::optional<BOOL> ignore_case = elibstl::args_to_data<BOOL>(pArgInf, 3);
	if (ignore_case.has_value() && ignore_case.value() == TRUE)
	{
		pRetData->m_bool = find_text(text, search, pos.has_value() && pos.value() > 0 ? pos.value() : 1, ignore_case.has_value() ? ignore_case.value() : true);
	}
	else
	{

		pRetData->m_bool = find_text(text, search, pos.has_value() && pos.value() > 0 ? pos.value() : 1);
	}

}

FucInfo fint_text_a = { {
		/*ccname*/  ("寻找文本A"),
		/*egname*/  ("InStrA"),
		/*explain*/ ("返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 1 开始。如果未找到，返回-1。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &Args[0],
	} ,Fn_InStrA ,"Fn_InStrA" };





static ARG_INFO WArgs[] =
{
	{
		/*name*/    "被搜寻的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲寻找的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "起始搜寻位置",
		/*explain*/ ("位置值从 1 开始。如果本参数被省略，默认为 1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "是否不区分大小写",
		/*explain*/ ("为真不区分大小写，为假区分。默认为“假”。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

static intptr_t find_text(const std::wstring_view& text, const std::wstring_view& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		//需要转换大小写再拷贝
		std::wstring formatted_text = text.data();
		std::wstring formatted_search = search.data();
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos - 1);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.data(), start_pos - 1);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
}
static intptr_t find_text(const std::wstring_view& text, const std::wstring_view& search, size_t start_pos)
{

	intptr_t ret = text.find(search.data(), start_pos - 1);
	if (ret != text.npos) {
		return ret + 1;
	}
	return -1;

}


EXTERN_C void Fn_InStrW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0),
		search = elibstl::args_to_wsdata(pArgInf, 1);
	std::optional<INT> pos = elibstl::args_to_data<INT>(pArgInf, 2);
	std::optional<BOOL> ignore_case = elibstl::args_to_data<BOOL>(pArgInf, 3);
	//因为字节集传递宽字符并不是按照win2字节linux3字节固定，而是任意字节数，所以此位置再次使用wstring拷贝格式化一下,但是肯定会影响效率，不过微乎其微.
	if (ignore_case.has_value() && ignore_case.value() == TRUE)
	{
		pRetData->m_bool = find_text(text, search, pos.has_value() && pos.value() > 0 ? pos.value() : 1, ignore_case.has_value() ? ignore_case.value() : true);
	}
	else
	{
		pRetData->m_bool = find_text(text, search, pos.has_value() && pos.value() > 0 ? pos.value() : 1);
	}
}

FucInfo find_text_w = { {
		/*ccname*/  ("寻找文本W"),
		/*egname*/  ("InStrW"),
		/*explain*/ ("返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 1 开始。如果未找到，返回-1。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,Fn_InStrW ,"Fn_InStrW" };



