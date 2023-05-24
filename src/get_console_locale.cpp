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
		/*ccname*/  ("ȡ����̨����"),
		/*egname*/  ("getconsolelocaleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_getconsolelocale ,"Fn_getconsolelocale" };
