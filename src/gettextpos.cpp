#include"ElibHelp.h"
#pragma warning(disable:4018)

static ARG_INFO Args[] =
{
	{
		/*name*/    "��ȡ�䲿�ֵ��ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ȡ���ַ�����Ŀ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_leftW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_pBin = elibstl::clone_textw(std::wstring(text.substr(0, pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1)));
}
FucInfo left_text_t = { {
		/*ccname*/  ("ȡ�ı����W"),
		/*egname*/  ("leftW"),
		/*explain*/ ("����һ���ı������а���ָ���ı��д��������ָ���������ַ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_leftW ,"Fn_leftW" };



EXTERN_C void Fn_rightW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	if (text.empty()) {
		return;
	}
	int num = pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1;
	if (num >= text.size()) {

		pRetData->m_pBin = elibstl::clone_textw(std::wstring(text));
		return;
	}
	pRetData->m_pBin = elibstl::clone_textw(std::wstring(text.substr(text.length() - num)));
}
FucInfo right_text_w = { {
		/*ccname*/  ("ȡ�ı��ұ�W"),
		/*egname*/  ("rightW"),
		/*explain*/ ("����һ���ı������а���ָ���ı��д��ұ�����ָ���������ַ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} , Fn_rightW ,"Fn_rightW" };


static ARG_INFO wArgs[] =
{
	{
		/*name*/    "��ȡ�䲿�ֵ��ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ʼȡ��λ��",
		/*explain*/ ("1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ȡ���ַ�����Ŀ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_midW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibstl::args_to_wsdata(pArgInf, 0));

	pRetData->m_pBin = elibstl::clone_textw(std::wstring((text.substr((pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1) - 1, pArgInf[2].m_int > 0 ? pArgInf[2].m_int : 1))));
}
FucInfo mid_text_w = { {
		/*ccname*/  ("ȡ�ı��м�W"),
		/*egname*/  ("midW"),
		/*explain*/ ("����һ���ı������а���ָ���ı��д�ָ��λ������ָ���������ַ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  &wArgs[0],
	} , Fn_midW ,"Fn_midW" };

