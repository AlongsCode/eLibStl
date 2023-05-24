#include"ElibHelp.h"
#include <algorithm>
#pragma warning(disable:4018)

static ARG_INFO WArgs[] =
{
	{
		/*name*/    "欲取其字符的字符代码",
		/*explain*/ ("欲获取字符的代码"),
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
		/*ccname*/  ("字符W"),
		/*egname*/  ("GetCharacterW"),
		/*explain*/ ("返回一个文本，其中包含有与指定字符代码相关的字符。"),
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
		/*name*/    "欲取字符代码的文本",
		/*explain*/ ("欲取字符代码的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲取其代码的字符位置",
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
		/*ccname*/  ("取代码W"),
		/*egname*/  ("GetCharCodeW"),
		/*explain*/ ("返回文本中指定位置处字符的代码。如果指定位置超出文本长度，返回0。"),
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



