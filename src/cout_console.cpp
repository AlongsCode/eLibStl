#include"ElibHelp.h"
#include<iostream>
#pragma warning(disable:4018)
static ARG_INFO Args[] =
{
	{
		/*name*/    "输出方向",
		/*explain*/ ("本参数提供内容所输出到的设备，可以为以下常量值之一： 1、#标准输出设备； 2、#标准错误设备。如果省略本参数，默认为“#标准输出设备”"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "输出文本",
		/*explain*/ ("本参数只能为unicode字节集。如果内容为文本且包含多行，可在各行之间用回车符 (即“字符W (13)”)、换行符 (即“字符W (10)”) 或回车换行符的组合 (即：“字符W (13) + 字符W (10)"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_coutW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto direction = elibstl::args_to_data<INT>(pArgInf, 0);
	int directionin = 1;
	if (direction.has_value() && direction.value() == 2)
	{
		directionin = 2;
	}

	// 输出内容是宽字符，使用 std::wcout 输出
	for (size_t i = 1; i < nArgCount; i++)
	{
		std::wstring_view text = elibstl::args_to_wsdata(pArgInf, i);
		if (directionin == 2) {
			std::wcerr << std::wstring(text);
		}
		else {
			std::wcout << std::wstring(text);
		}
	}
}

FucInfo cout_w = { {
		/*ccname*/  ("标准输出W"),
		/*egname*/  ("coutW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_coutW ,"Fn_coutW" };
