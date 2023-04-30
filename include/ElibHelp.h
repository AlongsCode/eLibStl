#pragma once
#include"elib/lib2.h"
#include"elib/fnshare.h"
#include<vector>
#include<string>
#include <tuple>
#include"..\resource.h"

#include"Tace.hpp"

#define ESTL_NAMESPACE_BEGIN namespace elibstl {
#define ESTL_NAMESPACE_END }

#ifdef _MSC_VER
#define eStlInline __forceinline
#else
#define eStlInline inline
#endif

#define MAKEINTATOMW(i)  (PWSTR)((ULONG_PTR)((WORD)(i)))

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
bool CallElibFunc(const char* elib_name, const char* def_name, PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);

template<class T>
eStlInline const T& ESTLPRIV_MultiSelectHelp___(int i, const T& Item)
{
	return Item;
}

template<class T, class...Args>
eStlInline const T& ESTLPRIV_MultiSelectHelp___(int i, const T& Item, const Args&...Items)
{
	if (i > 0)
	{
		i--;
		return ESTLPRIV_MultiSelectHelp___(i, Items...);
	}
	else
		return Item;
}

/// <summary>
/// 多项选择。
/// 第一个参数指示从0开始的索引。
/// </summary>
template<class...T>
eStlInline const auto& MultiSelect(int i, const T&...Items)
{
	assert(i >= 0 || i < sizeof...(Items));
	return ESTLPRIV_MultiSelectHelp___(i, Items...);
}
ESTL_NAMESPACE_END