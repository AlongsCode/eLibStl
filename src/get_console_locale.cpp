#include"ElibHelp.h"
#include<iostream>

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲获取编码类型的流",
		/*explain*/ ("1.unicode输出流,2.unicode输入流,3.ansi输出流,4.ansi输入流,默认为1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_getconsolelocale(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto type = elibstl::args_to_data<INT>(pArgInf, 0);
	if (type.has_value() && type.value() >= 1 && type.value() <= 4)
	{
		switch (type.value())
		{
		case 2:
			pRetData->m_pText = elibstl::clone_text(std::wcin.getloc().name());
			return;
		case 3:
			pRetData->m_pText = elibstl::clone_text(std::cout.getloc().name());
			return;
		case 4:
			pRetData->m_pText = elibstl::clone_text(std::cin.getloc().name());
			return;
		default:
			pRetData->m_pText = elibstl::clone_text(std::wcout.getloc().name());
			return;
		}
	}
	pRetData->m_pText = elibstl::clone_text(std::wcout.getloc().name());
}

FucInfo get_console_locale = { {
		/*ccname*/  ("取控制台编码"),
		/*egname*/  ("getconsolelocaleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_getconsolelocale ,"Fn_getconsolelocale" };
