#pragma once
#include<string>
#include<vector>
#include<optional>
#include<ctime>
#if  __cplusplus > 202004L
import STL;
#endif


#ifndef UseKrnln  //防止重复引用，C++23可以尝试重构为模块
#define UseKrnln
//中文函数我就不加命名空间了，一般不会冲突
/******************************************************************************
如果为MSVC则使用全中文模块--开始（MSVC版本没做定义，如果你还在用VC6自行修改吧）
*******************************************************************************/
#ifdef _MSC_VER 
//使用vcide环境下定义默认为win环境，并使用中文代码。
#pragma region 
#define 使用中文代码
#include<windows.h>
using namespace std;
#pragma endregion
#include"Edefcn.h"//定义函数
//#include"模板打包.h"
#include"文本转换.h"//辅助类函数
#include"数组.h"
/*--函数头文件，将易核心库和常用支持库的常用命令囊括在内，落后的命令和有问题的命令都进行了修改以及删除，修改的内容也会在命令注释中体现。*/
#include"流程控制.h"
#include"算术运算.h"
#include"逻辑比较.h"
#include"位运算.h"
#include"环境存取.h"
#include"字节集操作.h"
#include"文本操作.h"
#include"时间操作.h"
#include"数值转换.h"
#include"磁盘操作.h"
#include"数据操作.h"
/*此文件中会包含操作系统独占函数*/
#include"操作系统.h"
#include"系统处理.h"
#include"线程操作.h"
#include"网络通信.h"
#include"程序进程.h"

//#include"图片处理.h"
//#include"其他.h"

//#include"窗口操作.h"
#include"控制台操作.h"
//#include"COM变体型.h"

#include"文件读写.h"
//#include"Sqlite数据库.h"
//#include"通用易类.h"
//*****************************DEBUG时请自行添加调试宏|重载使用方便************************
#pragma region 调试输出
#ifdef 调试版


template <class Ty>
static void pt(wstring& str, Ty v)
{

	str.append(std::to_wstring(v) + L" | ");
}
template <class Ty>
static void pt(wstring& str, vector<Ty> v)
{
	if (v.empty())
	{
		str.append(L" 数组:(空) |");
		return;
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i == 0) {
			str.append(L" 数组 :" + to_wstring(v.size()) + L" {");
		}
		str.append(to_wstring(v[i]));
		str.append(L",");
	}
	str.pop_back();
	str.append(L"} | ");
}
static void pt(wstring& str, const wchar_t* s) //这个是 L""
{

	str.append(L"\"");
	if (!s)
	{
		str.append(L"(空)");
		str.append(L"\" | ");
		return;
	}

	str.append(s);

	str.append(L"\" | ");
}
static void pt(wstring& str, const char* s) //这个是 L""
{
	str.append(L"\"");
	if (!s)
	{
		str.append(L"(空)");
		str.append(L"\" | ");
		return;
	}
	str.append(L"\"");

	str.append(文本到宽文本(s));

	str.append(L"\" | ");
}
static void pt(wstring& str, std::string s)
{
	str.append(L"\"");

	str.append(文本到宽文本(s));

	str.append(L"\" | ");
}
static void pt(wstring& str, std::wstring s)
{
	str.append(L"\"");
	str.append(s);
	str.append(L"\" | ");
}
static void pt(wstring& str, vector<unsigned char> s)
{
	if (s.empty())
	{
		str.append(L" 字节集:(空) |");
		return;
	}
	for (size_t i = 0; i < s.size(); i++)
	{
		if (i == 0) {
			str.append(L" 字节集 :" + to_wstring(s.size()) + L" {");
		}
		str.append(to_wstring((int)s.data()[i]));
		str.append(L",");
	}
	str.pop_back();
	str.append(L"} | ");

};
static void pt(wstring& str, char* s)
{

	str.append(到文本W(string(s)) + L" | ");

};
static void pt(wstring& str, std::tm s)
{

	str.append(到文本W(s) + L" | ");

};
//调试输出 支持 无限参数!  任意类型!  (没有的可以重载方法自定义)
template <class... T>
static void 调试输出(T... args)
{
	std::wstring str = L"";
	std::initializer_list<INT>{(pt(str, std::forward<T>(args)), 0)...};

	str.pop_back();
	str.pop_back();
	str.append(L"\r\n");
	OutputDebugStringW(str.c_str());
};

#else
#define 调试输出(...)
#endif

#pragma endregion
#endif 



/*****************************************************************************
					  如果为非MSVC则使用使用英文模块
******************************************************************************/
#ifdef __GNUC__

#include"Edef.h"
#endif
#ifdef __BORLANDC__
#include"Edef.h"
#endif
#else
#endif 