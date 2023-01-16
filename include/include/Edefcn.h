#pragma once
#ifndef UseEdefcn
#define UseEdefcn
#include<string>
#include<ctime>
//兼容unicode ansi
#ifdef _UNICODE
typedef std::wstring lstring;
typedef wchar_t lchar;
#define _l(X) L##X
#else
typedef std::string lstring;
typedef char lchar;
#define  _l(X) X
#endif


#ifdef 使用中文代码

//宏定义的数据类型尽量不要使用，微软默认32为编译器，如果文件过大预编译过程容易卡死
//本库中并不会使用除std::tm以外的任何定义函数
/******************************************************************************
*                               易基本数据类型                              *
*******************************************************************************/
#define 整数型 int
#define 长整数型 long
#define 字节型 unsigned char
#define 小数型 float
#define 双精度小数型 double
#define 逻辑型 bool

typedef vector<unsigned char> 字节集类;
#define 文本型 lstring
#define 子程序指针 void*
#define 字节集 字节集类
/******************************************************************************
*                                拓展类型                                     *
*******************************************************************************/
//兼容unicode ansi x86 x64
#define 字符型 char
#define 宽字符型 wchar_t
#ifdef _WIN64
#define 变整数 long long
#else
#define 变整数 int
#endif
struct 字体 {
	const wchar_t* 字体名称;
	BOOL 加粗 = false;
	BOOL 倾斜 = false;
	BOOL 下划线 = false;
	BOOL 删除线 = false;
	//点(1/72英寸）为单位
	ULONG 字体大小 = 9;
};
struct 尺寸
{
	LONG 宽;
	LONG 高;
};
struct 矩形
{
	LONG    左边;
	LONG    顶边;
	LONG    右边;
	LONG    底边;
};
struct 矩形F
{
	float    左边;
	float    顶边;
	float    宽度;
	float    高度;
};

struct 坐标F
{
	float  x;
	float  y;
};
struct 坐标
{
	LONG  x;
	LONG  y;
};





#else
//低版本MSVC或其他C++主流编译器
#endif 


#endif // !UseEdefcn


