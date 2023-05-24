#include"ElibHelp.h"
#include <algorithm>


inline size_t count_occurrences(const std::wstring_view& str, const std::wstring_view& text) {
	size_t count = 0;
	size_t pos = str.find(text, 0);
	while (pos != std::string::npos) {
		count++;
		pos = str.find(text, pos + text.length());
	}
	return count;
}

static ARG_INFO WArgs[] =
{
	{
		/*name*/    "�ַ���",
		/*explain*/ ("����ȡ���ִ������ַ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "ָ���ı�",
		/*explain*/ ("Ѱ�Ҵ�����ָ���ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/    NULL,
	}
};

EXTERN_C void efn_count_occurrences(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		str = elibstl::args_to_wsdata(pArgInf, 0),
		text = elibstl::args_to_wsdata(pArgInf, 1);
	pRetData->m_int = 0;
	if (!str.empty() && !text.empty()) {
		pRetData->m_int = count_occurrences(str, text);
	}
}

FucInfo g_count_occurrences = { {
		/*ccname*/  ("ȡ�ı����ִ���W"),
		/*egname*/  ("extract_shortest_matching_text"),
		/*explain*/ ("��ȡָ���ı����ַ����г��ֵĴ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &WArgs[0],
	} ,efn_count_occurrences ,"efn_count_occurrences" };



