#include"ElibHelp.h"
#pragma warning(disable:4018)

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲取其部分的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲取出字符的数目",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_leftW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibkrnln::args_to_wsdata(pArgInf, 0);
	pRetData->m_pBin = elibkrnln::clone_textw(std::wstring(text.substr(0, pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1)));
}
FucInfo left_text_t = { {
		/*ccname*/  ("取文本左边W"),
		/*egname*/  ("leftW"),
		/*explain*/ ("返回一个文本，其中包含指定文本中从左边算起指定数量的字符。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
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
		text = elibkrnln::args_to_wsdata(pArgInf, 0);
	if (text.empty()) {
		return;
	}
	int num = pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1;
	if (num >= text.size()) {

		pRetData->m_pBin = elibkrnln::clone_textw(std::wstring(text));
		return;
	}
	pRetData->m_pBin = elibkrnln::clone_textw(std::wstring(text.substr(text.length() - num)));
}
FucInfo right_text_w = { {
		/*ccname*/  ("取文本右边W"),
		/*egname*/  ("rightW"),
		/*explain*/ ("返回一个文本，其中包含指定文本中从右边算起指定数量的字符。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
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
		/*name*/    "欲取其部分的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "起始取出位置",
		/*explain*/ ("1为首位置，2为第2个位置，如此类推。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲取出字符的数目",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_midW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = std::wstring(elibkrnln::args_to_wsdata(pArgInf, 0));

	pRetData->m_pBin = elibkrnln::clone_textw(std::wstring((text.substr((pArgInf[1].m_int > 0 ? pArgInf[1].m_int : 1) - 1, pArgInf[2].m_int > 0 ? pArgInf[2].m_int : 1))));
}
FucInfo mid_text_w = { {
		/*ccname*/  ("取文本中间W"),
		/*egname*/  ("midW"),
		/*explain*/ ("返回一个文本，其中包含指定文本中从指定位置算起指定数量的字符。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  &wArgs[0],
	} , Fn_midW ,"Fn_midW" };

