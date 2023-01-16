#pragma once
#ifndef KRNLNCONSOLE
#define KRNLNCONSOLE
#include<iostream>

void 标准输出(int 输出方向);
template<typename T, typename... Args>
void 标准输出(int 输出方向, T 输出内容, Args... args) {
	// 判断输出内容的类型是否为宽字符
	if constexpr (std::is_same<T, wchar_t>::value
		|| std::is_same<T, wchar_t*>::value
		|| std::is_same<T, const wchar_t*>::value
		|| std::is_same<T, std::wstring>::value
		|| std::is_same<T, const std::wstring>::value) {
		// 输出内容是宽字符，使用 std::wcout 输出
		if (输出方向 == 2) {
			std::wcerr << 输出内容;
		}
		else {
			std::wcout << 输出内容;
		}
	}
	else {
		// 输出内容不是宽字符，使用 std::cout 输出
		if (输出方向 == 2) {
			std::cerr << 输出内容;
		}
		else {
			std::cout << 输出内容;
		}
	}

	// 继续处理其余的参数
	标准输出(输出方向, args...);
}

std::string 标准输入A(bool 是否回显 = 1);
std::wstring 标准输入W(bool 是否回显 = 1, std::string 编码格式 = std::wcin.getloc().name());
#ifdef _UNICODE
#define 标准输入(是否回显) 标准输入W(是否回显)
#else
#define 标准输入(是否回显) 标准输入A(是否回显)
#endif



template <typename Stream>
void 置控制台编码(const wstring& 编码类型, Stream& 流 = std::wcin) {
	流.imbue(std::locale(编码类型));
}
template <typename Stream>
void 置控制台编码(const string& 编码类型, Stream& 流 = std::wcin) {
	流.imbue(std::locale(编码类型));
}
template <typename Stream>
std::locale 取控制台编码(Stream& 流 = std::wcin) {

	return 流.getloc();
}

#endif // !KRNLNCONSOLE

