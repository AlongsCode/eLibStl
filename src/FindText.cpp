#include"ElibHelp.h"
#include <algorithm>
//#include"include\krnln.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "����Ѱ���ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��Ѱ�ҵ��ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ʼ��Ѱλ��",
		/*explain*/ ("λ��ֵ�� 1 ��ʼ�������������ʡ�ԣ�Ĭ��Ϊ 1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�Ƿ����ִ�Сд",
		/*explain*/ ("Ϊ�治���ִ�Сд��Ϊ�����֡�Ĭ��Ϊ���١���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

static intptr_t find_text(const std::string_view& text, const std::string_view& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		//��Ҫת����Сд�ٿ���
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
		/*ccname*/  ("Ѱ���ı�A"),
		/*egname*/  ("InStrA"),
		/*explain*/ ("����һ������ֵ��ָ��һ�ı�����һ�ı������ȳ��ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ�������-1��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
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
		/*name*/    "����Ѱ���ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��Ѱ�ҵ��ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ʼ��Ѱλ��",
		/*explain*/ ("λ��ֵ�� 1 ��ʼ�������������ʡ�ԣ�Ĭ��Ϊ 1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�Ƿ����ִ�Сд",
		/*explain*/ ("Ϊ�治���ִ�Сд��Ϊ�����֡�Ĭ��Ϊ���١���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

static intptr_t find_text(const std::wstring_view& text, const std::wstring_view& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		//��Ҫת����Сд�ٿ���
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
	//��Ϊ�ֽڼ����ݿ��ַ������ǰ���win2�ֽ�linux3�ֽڹ̶������������ֽ��������Դ�λ���ٴ�ʹ��wstring������ʽ��һ��,���ǿ϶���Ӱ��Ч�ʣ�����΢����΢.
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
		/*ccname*/  ("Ѱ���ı�W"),
		/*egname*/  ("InStrW"),
		/*explain*/ ("����һ������ֵ��ָ��һ�ı�����һ�ı������ȳ��ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ�������-1��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,Fn_InStrW ,"Fn_InStrW" };



