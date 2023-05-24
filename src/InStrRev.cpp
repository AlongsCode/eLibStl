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
		//��Сдת���Ǳ���Ҫ�����ģ��ٶ��Ż�����߲�����ôϸ��
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

EXTERN_C void Fn_InStrRevW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0),
		search = elibstl::args_to_wsdata(pArgInf, 1);
	std::optional<INT> pos = elibstl::args_to_data<INT>(pArgInf, 2);
	std::optional<BOOL> ignore_case = elibstl::args_to_data<BOOL>(pArgInf, 3);
	//��Ϊ�ֽڼ����ݿ��ַ������ǰ���win2�ֽ�linux3�ֽڹ̶������������ֽ��������Դ�λ���ٴ�ʹ��wstring������ʽ��һ��,���ǿ϶���Ӱ��Ч�ʣ�����΢����΢.
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
		/*ccname*/  ("�����ı�W"),
		/*egname*/  ("InStrRevW"),
		/*explain*/ ("����һ������ֵ��ָ��һ�ı�����һ�ı��������ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ�������-1��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,Fn_InStrRevW ,"Fn_InStrRevW" };



