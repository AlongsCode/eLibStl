#include"ElibHelp.h"
#include<iostream>

static ARG_INFO Args[] =
{
	{
		/*name*/    "����ȡ�������͵���",
		/*explain*/ ("1.unicode�����,2.unicode������,3.ansi�����,4.ansi������,Ĭ��Ϊ1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�����ʽ",
		/*explain*/ ("�����õĿ���̨�����ʽ,Ĭ��Ϊ\"chs\""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
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
		/*ccname*/  ("�ÿ���̨����"),
		/*egname*/  ("setconsolelocaleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_setconsolelocale ,"Fn_setconsolelocale" };
