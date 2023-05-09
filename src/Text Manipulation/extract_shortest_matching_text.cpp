#include"ElibHelp.h"
#include <algorithm>


inline void extract_shortest_matching_text(std::vector<LPBYTE>& aryText, const std::wstring& wanna, const std::wstring& left_str, const std::wstring& right_str)
{

	size_t start_place = 0;

	if (left_str.empty() || right_str.empty()) {
		return; // 如果左边或右边的字符串为空，则直接返回空的结果
	}

	while (start_place != std::wstring::npos) {

		start_place = wanna.find(left_str, start_place);
		if (start_place == std::wstring::npos) {
			break; // 如果找不到左边的字符串，则结束循环
		}

		start_place += left_str.length();
		size_t end_place = wanna.find(right_str, start_place);

		if (end_place != std::wstring::npos) {

			aryText.push_back(elibstl::clone_textw(wanna.substr(start_place, end_place - start_place)));
			start_place = end_place + right_str.length();
		}
	}
};

inline void  extract_shortest_matching_text(std::vector<LPBYTE>& aryText, const std::wstring& wanna, const std::wstring& left_str, const std::wstring& right_str, const size_t& count)
{

	size_t start_place = 0;

	if (left_str.empty() || right_str.empty()) {
		return; // 如果左边或右边的字符串为空，则直接返回空的结果
	}

	while (start_place != std::wstring::npos) {
		if (aryText.size() >= count) {
			break;
		}

		start_place = wanna.find(left_str, start_place);
		if (start_place == std::wstring::npos) {
			break; // 如果找不到左边的字符串，则结束循环
		}

		start_place += left_str.length();
		size_t end_place = wanna.find(right_str, start_place);

		if (end_place != std::wstring::npos) {
			aryText.push_back(elibstl::clone_textw(wanna.substr(start_place, end_place - start_place)));
			start_place = end_place + right_str.length();
		}
	}
}

static ARG_INFO WArgs[] =
{
	{
		/*name*/    "欲取的文本",
		/*explain*/ ("如果参数值是一个长度为零的文本，则返回一个空数组，即没有任何成员的数组"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "左边文本",
		/*explain*/ ("条件1:左边匹配的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/    NULL,
	},
	{
		/*name*/    "右边文本",
		/*explain*/ ("条件2:右边匹配的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "最大获取数量",
		/*explain*/ ("-1或为空时不限制"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void efn_extract_shortest_matching_text(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = elibstl::args_to_wsdata(pArgInf, 0).data(),
		left = elibstl::args_to_wsdata(pArgInf, 1).data(),
		right = elibstl::args_to_wsdata(pArgInf, 2).data();
	size_t size = static_cast<size_t>(elibstl::args_to_data<int>(pArgInf, 3).value_or(-1));
	std::vector<LPBYTE> ret;

	if (size == static_cast<size_t>(-1))
	{

		extract_shortest_matching_text(ret, text, left, right);
	}
	else
	{
		extract_shortest_matching_text(ret, text, left, right, size);
	}


	pRetData->m_pAryData = elibstl::create_array<LPBYTE>(ret.data(), ret.size());

}

FucInfo g_extract_shortest_matching_text = { {
		/*ccname*/  ("取中间文本W"),
		/*egname*/  ("extract_shortest_matching_text"),
		/*explain*/ ("和取文本中间有很大区别,通过前后(左右)文本，取出所有最短匹配要求的中间文本。类似精易模块的\"文本_取中间\""),
		/*category*/2,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,efn_extract_shortest_matching_text ,"efn_extract_shortest_matching_text" };



