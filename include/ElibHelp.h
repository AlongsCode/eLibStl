#pragma once
#include"elib/lib2.h"
#include"elib/fnshare.h"
#include<vector>
#include<string>
#include"..\resource.h"

#include"Tace.hpp"

#define ESTL_NAMESPACE_BEGIN namespace elibstl {
#define ESTL_NAMESPACE_END }

#ifdef _MSC_VER
#define eStlInline __forceinline
#else
#define eStlInline inline
#endif

typedef LPCVOID PCVOID;

struct FucInfo
{
	CMD_INFO FucDef;
	PFN_EXECUTE_CMD pFuc;
	const char* FucName;
};

extern HMODULE g_elibstl_hModule;

ESTL_NAMESPACE_BEGIN
/// <summary>
/// Unicode到ANSI，使用默认代码页
/// </summary>
/// <param name="pszW">Unicode字符串指针</param>
/// <returns>ANSI字符串指针，应使用delete[]释放</returns>
PSTR W2A(PCWSTR pszW);

/// <summary>
/// ANSI到Unicode，使用默认代码页
/// </summary>
/// <param name="pszA">ANSI字符串指针</param>
/// <returns>Unicode字符串指针，应使用delete[]释放</returns>
PWSTR A2W(PCSTR pszA);

/// <summary>
/// 调用易语言支持库函数
/// </summary>
/// <param name="elib_name"></param>
/// <param name="def_name"></param>
/// <param name="pRetData"></param>
/// <param name="nArgCount"></param>
/// <param name="pArgInf"></param>
/// <returns></returns>
bool CallElibFunc(const char* elib_name, const char* def_name, PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);
ESTL_NAMESPACE_END