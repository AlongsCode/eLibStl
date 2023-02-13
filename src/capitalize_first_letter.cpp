#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "英文文本",
		/*explain*/ ("欲转换的Unicode文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};



EXTERN_C void Fn_capitalize_first_letter(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto text = elibstl::args_to_wsdata(pArgInf, 0);
	if (text.empty() || !std::isalpha(text[0])) {
		pRetData->m_pBin = elibstl::clone_textw(text.data());
		return;
	}
	std::wstring result;
	result.push_back(std::toupper(text[0]));
	result += text.substr(1);
	pRetData->m_pBin = elibstl::clone_textw(result);
}

FucInfo capitalize_first_letter = { {
		/*ccname*/  ("首字母大写W"),
		/*egname*/  ("capitalize_first_letter"),
		/*explain*/ ("将英文字符首字母大写，非英文字符串并不会进行任何操作"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_capitalize_first_letter ,"Fn_capitalize_first_letter" };
