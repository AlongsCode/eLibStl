#include"ElibHelp.h"
namespace {
	static ARG_INFO Arg[] =
	{
		  { "配置文件名", "指定配置文件的名称，通常以.ini作为文件名后缀。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "节名称", "包含欲写入配置项所处节的名称。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "配置项名称", "参数值指定欲写入配置项在其节中的名称。如果参数值被省略，则删除指定节及其下的所有配置项。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },
		  { "欲写入值", "参数值指定欲写入到指定配置项中的文本。如果参数值被省略，则删除所指定配置项。",0 , 0,  _SDT_ALL, NULL,  ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },
	};
}

EXTERN_C void fn_SetKeyTextW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool= WritePrivateProfileStringW(elibstl::arg_to_wstring(pArgInf, 1).data(), elibstl::arg_to_wstring(pArgInf, 2).data(), elibstl::arg_to_wstring(pArgInf, 3).data(), elibstl::arg_to_wstring(pArgInf, 0).data());
}


FucInfo Fn_SetKeyTextW = { {
		/*ccname*/  ("写配置项W"),
		/*egname*/  ("SetKeyTextW"),
		/*explain*/ (" 将指定文本内容写入指定配置项中或者删除指定的配置项或节，如果指定配置文件不存在，将会自动创建。成功返回真，失败返回假。"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Arg),
		/*arg lp*/  Arg,
	} ,fn_SetKeyTextW ,"fn_SetKeyTextW" };








//系统处理 - 读配置项
/*
	调用格式： 〈文本型〉 读配置项 （文本型 配置文件名，文本型 节名称，文本型 配置项名称，［文本型 默认文本］） - 系统核心支持库->系统处理
	英文名称：GetKeyText
	读取指定配置文件中指定项目的文本内容。本命令为初级命令。
	参数<1>的名称为“配置文件名”，类型为“文本型（text）”。指定配置文件的名称，通常以.ini作为文件名后缀。
	参数<2>的名称为“节名称”，类型为“文本型（text）”。包含欲读入配置项所处节的名称。
	参数<3>的名称为“配置项名称”，类型为“文本型（text）”。参数值指定欲读入配置项在其节中的名称。
	参数<4>的名称为“默认文本”，类型为“文本型（text）”，可以被省略。如果指定配置项不存在，将返回此默认文本。如果指定配置项不存在且本参数被省略，将返回空文本。
*/
namespace {
	static ARG_INFO Arg2[] =
	{ 
		  { "配置文件名", "指定配置文件的名称，通常以.ini作为文件名后缀。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "节名称", "包含欲写入配置项所处节的名称。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "配置项名称", "参数值指定欲写入配置项在其节中的名称。如果参数值被省略，则删除指定节及其下的所有配置项。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "默认文本", "如果指定配置项不存在，将返回此默认文本。如果指定配置项不存在且本参数被省略，将返回空文本。",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },

	};
}
EXTERN_C void fn_GetKeyText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	LPWSTR pBuff = NULL;
	INT nLen = 1024;
	do
	{
		pBuff = new wchar_t[nLen] {};
		INT nRet = GetPrivateProfileStringW(elibstl::arg_to_wstring(pArgInf, 1).data(), elibstl::arg_to_wstring(pArgInf, 2).data(), elibstl::arg_to_wstring(pArgInf, 3).data(), pBuff, nLen, elibstl::arg_to_wstring(pArgInf, 0).data());
		if (nRet < nLen - 1)
			break;
		nLen = nRet + 1024;
		delete[] pBuff;
	} while (1);

	LPBYTE pText = NULL;
	nLen = wcslen(pBuff);
	if (nLen)
	{
		pText = elibstl::clone_textw(pBuff);
	}
	delete[] pBuff;
	pRetData->m_pBin = pText;
}




FucInfo Fn_GetKeyTextW = { {
		/*ccname*/  ("读配置项W"),
		/*egname*/  ("GetKeyTextW"),
		/*explain*/ ("读取指定配置文件中指定项目的文本内容。"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Arg2),
		/*arg lp*/  Arg2,
	} ,fn_GetKeyText ,"fn_GetKeyText" };