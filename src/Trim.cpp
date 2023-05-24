#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "��ɾ���ո���ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_LTrimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(0, text.find_first_not_of(L" "));
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo ltrim_w = { {
		/*ccname*/  ("ɾ�׿�W"),
		/*egname*/  ("LTrimW"),
		/*explain*/ ("����һ���ı������а�����ɾ�����ײ�ȫ�ǻ��ǿո��ָ���ı�."),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_LTrimW ,"Fn_LTrimW" };



EXTERN_C void Fn_RTrimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(text.find_last_not_of(L" ") + 1);
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo rtrim_w = { {
		/*ccname*/  ("ɾβ��W"),
		/*egname*/  ("RTrimW"),
		/*explain*/ (" ����һ���ı������а�����ɾ����β��ȫ�ǻ��ǿո��ָ���ı���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_RTrimW ,"Fn_RTrimW" };

EXTERN_C void Fn_trimW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	if (text.empty())
	{
		pRetData->m_pBin = elibstl::clone_textw(text);
		return;
	}
	text.erase(0, text.find_first_not_of(L" "));
	text.erase(text.find_last_not_of(L" ") + 1);
	pRetData->m_pBin = elibstl::clone_textw(text);
}
FucInfo trim_w = { {
		/*ccname*/  ("ɾ��β��W"),
		/*egname*/  ("trimW"),
		/*explain*/ ("����һ���ı������а�����ɾ�����ײ���β��ȫ�ǻ��ǿո��ָ���ı���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_trimW ,"Fn_trimW" };

EXTERN_C void Fn_TrimAllW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));
	std::wstring mark = L" ";
	size_t nSize = mark.size();
	if (text.empty() || text == L"") {
		return;
	}
	while (1)
	{
		size_t pos = text.find(mark);    //  ����������
		if (pos == std::wstring::npos)
		{
			pRetData->m_pBin = elibstl::clone_textw(text);
			return;
		}
		text.erase(pos, nSize);
	}
}
FucInfo trim_all_w = { {
		/*ccname*/  ("ɾȫ����W"),
		/*egname*/  ("TrimAllW"),
		/*explain*/ ("����һ���ı������а�����ɾ��������ȫ�ǻ��ǿո��ָ���ı���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_TrimAllW ,"Fn_TrimAllW" };

