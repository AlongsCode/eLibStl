#include"ElibHelp.h"
#include <algorithm>


static  void split_text(const std::wstring_view& text, const  std::wstring_view& str, size_t count, std::vector<LPBYTE>& ret) {

	if (str.empty() || text == L"")
	{
		ret.push_back(elibstl::clone_textw(text));
		return;
	}
	size_t start = 0, index = text.find_first_of(str, 0);
	while (index != text.npos)
	{
		if (start != index)
			ret.push_back(elibstl::clone_textw(text.substr(start, index - start)));
		start = index + 1;
		index = text.find_first_of(str, start);
	}
	if (text.substr(start) != L"")
	{
		ret.push_back(elibstl::clone_textw(text.substr(start)));
	}
	if (count != -1 && count <= ret.size())
	{
		ret.resize(count);
	}
	return;
}


static ARG_INFO WArgs[] =
{
	{
		/*name*/    "���ָ��ı�",
		/*explain*/ ("�������ֵ��һ������Ϊ����ı����򷵻�һ�������飬��û���κγ�Ա������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "����ֵ���ڱ�ʶ���ı��߽硣",
		/*explain*/ ("�����ʡ�ԣ���Ĭ��ʹ�ð�Ƕ����ַ���Ϊ�ָ����������һ������Ϊ����ı����򷵻ص����������һ����Ա���������ġ����ָ��ı���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "Ҫ���ص����ı���Ŀ",
		/*explain*/ ("�����ʡ�ԣ���Ĭ�Ϸ������е����ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_splitW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0),
		search = elibstl::args_to_wsdata(pArgInf, 1);
	std::optional<INT> count = elibstl::args_to_data<INT>(pArgInf, 2);

	if (search.empty())
		search = L",";
	std::vector<LPBYTE> ret;
	split_text(text, search, count.has_value() && count.value() > 0 ? count.value() : -1, ret);
	pRetData->m_pAryData = elibstl::create_array<LPBYTE>(ret.data(), ret.size());

}

FucInfo Fn_split_w = { {
		/*ccname*/  ("�ָ��ı�W"),
		/*egname*/  ("splitW"),
		/*explain*/ ("��ָ���ı����зָ���طָ���һά�ı����顣"),
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



