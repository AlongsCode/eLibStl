#include"ElibHelp.h"
#include <algorithm>

inline std::wstring touper(const std::wstring& text) {
	std::wstring ret(text);
	transform(text.begin(), text.end(), ret.begin(), toupper);
	return ret;
}

static intptr_t rfind_text(std::wstring text, std::wstring wanna, intptr_t pos, bool ignore_case) {
	size_t  Ret = 0;
	if (ignore_case)
	{
		//大小写转换是必须要拷贝的，速度优化我这边不做这么细了
		text = touper(text);
		wanna = touper(text);
	}
	if (pos == -1)
	{
		Ret = text.rfind(wanna.data());
	}
	else
	{
		Ret = text.rfind(wanna.data(), pos - 2);
	}
	if (Ret == text.npos)
	{
		return -1;
	}
	return Ret + 1;
}


static intptr_t rfind_text(const std::wstring_view& text, const std::wstring_view& wanna, intptr_t pos) {
	size_t  Ret = 0;

	if (pos == -1)
	{
		Ret = text.rfind(wanna.data());
	}
	else
	{
		Ret = text.rfind(wanna.data(), pos - 2);
	}
	if (Ret == text.npos)
	{
		return -1;
	}
	return Ret + 1;
}

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

EXTERN_C void Fn_InStrRevW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0),
		search = elibstl::args_to_wsdata(pArgInf, 1);
	std::optional<INT> pos = elibstl::args_to_data<INT>(pArgInf, 2);
	std::optional<BOOL> ignore_case = elibstl::args_to_data<BOOL>(pArgInf, 3);
	//因为字节集传递宽字符并不是按照win2字节linux3字节固定，而是任意字节数，所以此位置再次使用wstring拷贝格式化一下,但是肯定会影响效率，不过微乎其微.
	if (ignore_case.has_value() && ignore_case.value() == TRUE)
	{
		pRetData->m_bool = rfind_text(std::wstring(text), std::wstring(search), pos.has_value() && pos.value() > 1 ? pos.value() : -1, true);
	}
	else
	{

		pRetData->m_bool = rfind_text(text, search, pos.has_value() && pos.value() > 1 ? pos.value() : -1);
	}
}

FucInfo in_str_rev_w = { {
		/*ccname*/  ("倒找文本W"),
		/*egname*/  ("InStrRevW"),
		/*explain*/ ("返回一个整数值，指定一文本在另一文本中最后出现的位置，位置值从 1 开始。如果未找到，返回-1。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,Fn_InStrRevW ,"Fn_InStrRevW" };



