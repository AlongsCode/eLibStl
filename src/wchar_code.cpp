#include"ElibHelp.h"
#include <algorithm>
#pragma warning(disable:4018)

static ARG_INFO WArgs[] =
{
	{
		/*name*/    "��ȡ���ַ����ַ�����",
		/*explain*/ ("����ȡ�ַ��Ĵ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SHORT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_GetCharacterW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	wchar_t code = *reinterpret_cast<wchar_t*>(&pArgInf->m_short);
	if (code == 0)
		return;
	pRetData->m_pBin = elibstl::clone_textw(std::wstring(1, code));
}

FucInfo get_character_w = { {
		/*ccname*/  ("�ַ�W"),
		/*egname*/  ("GetCharacterW"),
		/*explain*/ ("����һ���ı������а�������ָ���ַ�������ص��ַ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,Fn_GetCharacterW ,"Fn_GetCharacterW" };



static ARG_INFO WArgs2[] =
{
	{
		/*name*/    "��ȡ�ַ�������ı�",
		/*explain*/ ("��ȡ�ַ�������ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��ȡ�������ַ�λ��",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_GetCharCodeW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view text = elibstl::args_to_wsdata(pArgInf, 0);
	auto idx_ = elibstl::args_to_data<INT>(pArgInf, 1);
	int idx = idx_.has_value() ? idx_.value() : 1;
	if (text.empty()) {
		pRetData->m_short = 0;
		return;
	}
	if (idx < 1) {
		idx = 1;
	}
	if (idx > text.size()) {
		pRetData->m_short = 0;
		return;
	}
	pRetData->m_short = text.at(idx - 1);
}

FucInfo get_char_code_w = { {
		/*ccname*/  ("ȡ����W"),
		/*egname*/  ("GetCharCodeW"),
		/*explain*/ ("�����ı���ָ��λ�ô��ַ��Ĵ��롣���ָ��λ�ó����ı����ȣ�����0��"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_SHORT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &WArgs2[0],
	} ,Fn_GetCharCodeW ,"Fn_GetCharCodeW" };



