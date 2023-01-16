#pragma once
#pragma region 到数值

double 到数值(const string& 待转换的文本或数值);
double 到数值(const wstring& 待转换的文本或数值);

#pragma endregion 
#pragma region 数值转换类(WA)及其宏
string 数值到大写A(double 欲转换形式的数值, bool 是否转换为简体 = false);
string 数值到金额A(double 欲转换形式的数值, bool 是否转换为简体 = false);
string 数值到格式文本A(double 欲转换为文本的数值, int 小数保留位数 = 1, bool 是否进行千分位分隔 = false);
string 取十六进制文本A(int 欲取进制文本的数值);
string 取八进制文本A(int 欲取进制文本的数值);

wstring 数值到大写W(double 欲转换形式的数值, bool 是否转换为简体 = false);
wstring 数值到金额W(double 欲转换形式的数值, bool 是否转换为简体 = false);
wstring 数值到格式文本W(double 欲转换为文本的数值, int 小数保留位数 = 1, bool 是否进行千分位分隔 = false);
wstring 取十六进制文本W(int 欲取进制文本的数值);
wstring 取八进制文本W(int 欲取进制文本的数值);

#ifdef _UNICODE
#define 数值到大写 数值到大写W
#define 数值到金额 数值到金额W
#define 数值到格式文本 数值到格式文本W
#define 取十六进制文本 取十六进制文本W
#define 取八进制文本 取八进制文本W
#else
#define 数值到大写 数值到大写A
#define 数值到金额 数值到金额A
#define 数值到格式文本 数值到格式文本A
#define 取十六进制文本 取十六进制文本A
#define 取八进制文本 取八进制文本A
#endif 

#pragma endregion
#pragma region 到字节
unsigned char 到字节(const string& 待转换的文本或数值);
unsigned char 到字节(const wstring& 待转换的文本或数值);

#pragma endregion

#pragma region 到短整数

short 到短整数(const string& 待转换的文本或数值);
short 到短整数(const wstring& 待转换的文本或数值);
#pragma endregion 

#pragma region 到整数

int 到整数(const string& 待转换的文本或数值);
int 到整数(const wstring& 待转换的文本或数值);
#pragma endregion 

#pragma region 到长整数

long long 到长整数(const string& 待转换的文本或数值);
long long 到长整数(const wstring& 待转换的文本或数值);

#pragma endregion

#pragma region 到小数
float 到小数(const wstring& 待转换的文本或数值);
float 到小数(const string& 待转换的文本或数值);

#pragma endregion

long 十六进制(const wstring& 十六进制文本常量);
long 十六进制(const string& 十六进制文本常量);
long 二进制(const string& 二进制文本常量);
long 二进制(const wstring& 二进制文本常量);
int 反转整数字节序(int 待反转的整数值);