#include"ElibHelp.h"
#include<iostream>
#include<conio.h>

static ARG_INFO Args[] =
{
	{
		/*name*/    "�Ƿ����",
		/*explain*/ ("Ϊ�������Ϊ�첽����,Ϊ�ٻ�����ַ���ȡ"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�����ʽ",
		/*explain*/ ("�����õĿ���̨�����ʽ����\"chs\",Ĭ��Ϊ��ǰ����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_readconsoleW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::string_view
		category = elibstl::args_to_sdata(pArgInf, 1);
	auto echo = elibstl::args_to_data<BOOL>(pArgInf, 0);
	std::wcin.imbue(std::locale(category.empty() ? std::wcin.getloc().name() : std::string(category)));
	std::wstring result;
	if ((!echo.has_value()) || (echo.has_value() && echo.value())) {
		// ʹ�� std::getline �ӱ�׼��������ȡһ���ַ���
		std::getline(std::wcin, result);
	}
	else {
		wchar_t c;
		while ((c = (wchar_t)_getch()) != L'\r' && c != L'\0' && c != L'\n') {
			result.push_back(c);
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}

FucInfo read_console_w = { {
		/*ccname*/  ("��׼����W"),
		/*egname*/  ("readconsoleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_readconsoleW ,"Fn_readconsoleW" };
