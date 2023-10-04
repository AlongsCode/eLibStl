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
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "编码格式",
		/*explain*/ ("欲设置的控制台编码格式,默认为\"chs\""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_setconsolelocale(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto type = elibstl::args_to_data<INT>(pArgInf, 0);
	auto loacl = elibstl::args_to_sdata(pArgInf, 1);
	std::string local_in = loacl.empty() ? "chs" : std::string(loacl);
	if (type.has_value() && type.value() >= 1 && type.value() <= 4)
	{
		switch (type.value())
		{
		case 2:
			std::wcin.imbue(std::locale(local_in));;
			return;
		case 3:
			std::cout.imbue(std::locale(local_in));;
			return;
		case 4:
			std::cin.imbue(std::locale(local_in));;
			return;
		default:
			std::wcout.imbue(std::locale(local_in));;
			return;
		}
	}
	std::wcout.imbue(std::locale(local_in));;
}

FucInfo set_console_locale = { {
		/*ccname*/  ("置控制台编码"),
		/*egname*/  ("setconsolelocaleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_setconsolelocale ,"Fn_setconsolelocale" };
