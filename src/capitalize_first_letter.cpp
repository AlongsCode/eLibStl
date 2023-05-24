#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "Ӣ���ı�",
		/*explain*/ ("��ת����Unicode�ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
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
		/*ccname*/  ("����ĸ��дW"),
		/*egname*/  ("capitalize_first_letter"),
		/*explain*/ ("��Ӣ���ַ�����ĸ��д����Ӣ���ַ�������������κβ���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_capitalize_first_letter ,"Fn_capitalize_first_letter" };
