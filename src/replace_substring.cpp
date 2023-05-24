#include"ElibHelp.h"
#include <algorithm>





static ARG_INFO WArgs[] =
{
	{
		/*name*/    "�����滻���ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�����滻�����ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�����滻�����ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�����滻����ʼλ��",
		/*explain*/ ("����ֵָ�����滻���ı�����ʼ����λ�á����ʡ�ԣ�Ĭ�ϴ� 1 ��ʼ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�����滻�Ĵ���",
		/*explain*/ ("����ֵָ�������ı������滻�Ĵ��������ʡ�ԣ�Ĭ�Ͻ������п��ܵ��滻��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�Ƿ����ִ�Сд",
		/*explain*/ ("Ϊ�����ִ�Сд��Ϊ�ٲ�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
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
	//��Ϊ�ֽڼ����ݿ��ַ������ǰ���win2�ֽ�linux3�ֽڹ̶������������ֽ��������Դ�λ���ٴ�ʹ��wstring������ʽ��һ��,���ǿ϶���Ӱ��Ч�ʣ�����΢����΢.
	pRetData->m_pBin = replace_substring(std::wstring(text), std::wstring(to_replace), std::wstring(replace_with), start_pos, replace_count, case_sensitive);
}

FucInfo replace_substring_w = { {
		/*ccname*/  ("���ı��滻W"),
		/*egname*/  ("replace_substringW"),
		/*explain*/ ("����һ���ı������ı���ָ�������ı��ѱ��滻����һ���ı��������滻�����Ĵ���Ҳ�Ǳ�ָ����"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/6,
		/*arg lp*/  &WArgs[0],
	} ,Fn_replace_substringW ,"Fn_replace_substringW" };



