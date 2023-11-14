#include"ElibHelp.h"
#include"EplPinYin.h"/*拼音字典*/
#include <unordered_map>
#include <sstream>
#include <mutex>







static ARG_INFO Args1[] =
{
	{
		"欲取其拼音编码的汉字",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个成员数目为 0 的空文本数组",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	}
};
EXTERN_C void efn_get_all_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	if (data.empty())
	{
		pRetData->m_pAryData = elibstl::empty_array();
		return;
	}
	pRetData->m_pAryData = elibstl::eplpinyin::GetAllPinyinW(*data.data());
}

FucInfo g_get_all_py = { {
		/*ccname*/  ("取所有发音W"),
		/*egname*/  ("get_all_py"),
		/*explain*/ ("返回包含指定汉字所有拼音编码的文本数组（支持多音字）。返回的数组结果可以用“复制数组”命令保存到同类型数组变量。本命令为初级命令。"),
		/*category*/16,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args1) / sizeof(Args1[0]),
		/*arg lp*/  Args1,
	} ,efn_get_all_py ,"efn_get_all_py" };



static ARG_INFO Args2[] =
{
	{
		"欲取其拼音的汉",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个成员数目为 0 的空文本数组",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	}
};
EXTERN_C void efn_get_py_count(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	if (data.empty())
	{
		pRetData->m_int = 0;
		return;
	}
	std::uint8_t count = 0;
	elibstl::eplpinyin::GetPinyinStruct(*data.data(), count);
	pRetData->m_int = static_cast<INT>(count);
}

FucInfo g_get_py_count = { {
		/*ccname*/  ("取发音数目W"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("返回指定汉字的发音数目。"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args2) / sizeof(Args2[0]),
		/*arg lp*/  Args2,
	} ,efn_get_py_count ,"efn_get_py_count" };


static ARG_INFO Args3[] =
{
	{
		"欲取其拼音编码的汉字",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个空文本。",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	},
	{
		"欲取拼音编码的索引",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个空文本。",
		0,
		0,
		SDT_INT,
		1,
		ArgMark::AS_HAS_DEFAULT_VALUE,
	}
};
EXTERN_C void efn_get_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	if (data.empty())
	{
		pRetData->m_pBin = nullptr;
		return;
	}
	pRetData->m_pBin = elibstl::eplpinyin::GetPinyinW(*data.data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1));
}

FucInfo g_get_py = { {
		/*ccname*/  ("取拼音W"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("返回包含指定汉字的指定拼音编码的文本。如果该指定拼音编码不存在，将返回空文本。目前仅支持国标汉字。多音字的第一个发音为常用音。同易完全相同"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/    SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py ,"efn_get_py" };



EXTERN_C void efn_get_py_sm(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	if (data.empty())
	{
		pRetData->m_pBin = nullptr;
		return;
	}
	pRetData->m_pBin = elibstl::clone_textw(elibstl::eplpinyin::GetSm(*data.data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1)));
}

FucInfo g_get_py_sm = { {
		/*ccname*/  ("取声母W"),
		/*egname*/  ("get_py_sm"),
		/*explain*/ ("返回包含指定汉字的指定拼音编码的文本。如果该指定拼音编码不存在，将返回空文本。目前仅支持国标汉字。多音字的第一个发音为常用音。同易完全相同"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py_sm ,"efn_get_py_sm" };



EXTERN_C void efn_get_py_ym(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	if (data.empty())
	{
		pRetData->m_pBin = nullptr;
		return;
	}
	pRetData->m_pBin = elibstl::clone_textw(elibstl::eplpinyin::GetYm(*data.data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1)));
}

FucInfo g_get_py_ym = { {
		/*ccname*/  ("取韵母W"),
		/*egname*/  ("get_py_ym"),
		/*explain*/ ("返回包含指定汉字指定拼音编码的韵母部分文本。如果指定拼音编码不存在或该汉字此发音无声母，将返回空文本。"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py_ym ,"efn_get_py_ym" };

#include <algorithm>

inline auto __PyToLow(const std::wstring_view& text)
{
	std::wstring ret(text);
	std::transform(text.begin(), text.end(), ret.begin(), tolower);
	return ret;
}
inline auto& __PyRemoveTrim(std::wstring& text) {
	std::wstring mark = L" ";
	size_t nSize = mark.size();
	if (text.empty() || text == L"") {
		return text;
	}
	while (1)
	{
		size_t pos = text.find(mark);    //  尤其是这里
		if (pos == std::wstring::npos)
		{
			return text;
		}
		text.erase(pos, nSize);
	}
}
EXTERN_C void efn_comp_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = FALSE;

	auto IsFuzzy = elibstl::args_to_data<BOOL>(pArgInf, 2).value_or(FALSE);
	if (IsFuzzy)
	{
		auto str1 = elibstl::eplpinyin::GetStrPinyinFirst(elibstl::args_to_wsdata(pArgInf, 0));
		auto str2 = elibstl::eplpinyin::GetStrPinyinFirst(elibstl::args_to_wsdata(pArgInf, 1));
		if (__PyToLow(str1) == __PyToLow(str2))
			pRetData->m_bool = TRUE;
	}
	else {
		auto str1 = elibstl::eplpinyin::GetStrPinyinNoNop(elibstl::args_to_wsdata(pArgInf, 0));
		auto str2 = elibstl::eplpinyin::GetStrPinyinNoNop(elibstl::args_to_wsdata(pArgInf, 1));
		if (__PyToLow(str1) == __PyToLow(str2))
			pRetData->m_bool = TRUE;
	}
}
static ARG_INFO Args4[] =
{
	{
		"待比较文本一",
		"",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	},{
		"待比较文本二",
		"",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	},
	{
		"是否为模糊比较",
		"本参数为真时，当待比较文本一的发音在待比较文本二的首部被包容时即认为比较通过。如果被省略，默认值为假。",
		0,
		0,
		SDT_BOOL,
		0,
		ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo Fn_comp_py = { {
		/*ccname*/  ("发音比较W"),
		/*egname*/  ("comp_py"),
		/*explain*/ ("比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非国标汉字部分，将仅进行简单的值比较。"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args4) / sizeof(Args4[0]),
		/*arg lp*/  Args4,
	} ,efn_comp_py ,"efn_comp_py" };





EXTERN_C void efn_comp_py_code(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = FALSE;
	auto s = elibstl::args_to_wsdata(pArgInf, 0);
	auto IsFuzzy = elibstl::eplpinyin::IsAllSpelled(s);

	if (IsFuzzy)
	{
		auto str1 = elibstl::eplpinyin::GetStrPinyinNoNop(elibstl::args_to_wsdata(pArgInf, 0));
		auto str2 = elibstl::eplpinyin::GetStrPinyinNoNop(elibstl::args_to_wsdata(pArgInf, 1));
		auto py1 = __PyToLow(str1), py2 = __PyToLow(str2);
		if (__PyRemoveTrim(py1) == __PyRemoveTrim(py2))
			pRetData->m_bool = TRUE;
	}
	else {
		auto str1 = elibstl::eplpinyin::GetStrPinyinFirst(elibstl::args_to_wsdata(pArgInf, 0));
		auto str2 = elibstl::eplpinyin::GetStrPinyinFirst(elibstl::args_to_wsdata(pArgInf, 1));
		auto py1 = __PyToLow(str1), py2 = __PyToLow(str2);
		if (__PyRemoveTrim(py1) == __PyRemoveTrim(py2))
			pRetData->m_bool = TRUE;
	
	}
	
}
static ARG_INFO Args5[] =
{
	{
		"待比较拼音输入字",
		R"(
系统自动判别该输入字具体是首拼方式还是全拼方式,非拼音部分按照英文大小写同音,全角数字；
如：
“jsjA”可以匹配“计算机a”
“计算机A”,“jsj”可以匹配“计算机”
“jisuanji”也可以匹配“计算机”
“j算j1”也可以匹配“计算机1”
“jsj1”匹配“计算机1”。
)",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	},{
		"待比较普通文本",
		"",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	}
};
FucInfo Fn_comp_py_code = { {
		/*ccname*/  ("输入字比较W"),
		/*egname*/  ("comp_py_code"),
		/*explain*/ ("比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非国标汉字部分，将仅进行简单的值比较。"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args5) / sizeof(Args5[0]),
		/*arg lp*/  Args5,
	} ,efn_comp_py_code ,"efn_comp_py_code" };



static ARG_INFO Args99[] =
{
	{
		"欲获取拼音的字符串",
		"会将可转换为拼音则字符串转为拼音",
		0,
		0,
		SDT_BIN,
		0,
		ArgMark::AS_NONE,
	},{
		"是否增加空格",
		"会为每个字符增加空格例如此项为真时“你好”会变为“ni hao”否则为“nihao”,默认为真",
		0,
		0,
		SDT_BOOL,
		0,
		ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		"是否保留无拼音字符",
		"为真时保留,例如“你好A吗”,会变为“ni hao A ma”，反之为“ni hao ma”",
		0,
		0,
		SDT_BOOL,
		0,
		ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
EXTERN_C void efn_get_str_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = nullptr;
	auto data = elibstl::args_to_wsdata(pArgInf, 0);
	auto IsNop = elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE);
	auto IsRetain = elibstl::args_to_data<BOOL>(pArgInf, 2).value_or(TRUE);
	if (data.empty())
		return;
	
	if (IsNop)
		pRetData->m_pBin = elibstl::clone_textw(elibstl::eplpinyin::GetStrPinyin(data.data(), IsRetain == TRUE));
	
	else
		pRetData->m_pBin = elibstl::clone_textw(elibstl::eplpinyin::GetStrPinyinNoNop(data.data(), IsRetain == TRUE));
	
	
}

FucInfo Fn_get_str_py = { {
		/*ccname*/  ("取文本拼音W"),
		/*egname*/  ("get_str_py"),
		/*explain*/ ("获取字符串文本的常用拼音,例如“我爱我的祖国”,会变成“wo ai wo de zu guo”,不存在拼音的则会返回原数据"),
		/*category*/16,
		/*state*/	NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args99) / sizeof(Args99[0]),
		/*arg lp*/  Args99,
	} ,ESTLFNAME(efn_get_str_py)};