#pragma once
#pragma region 
#ifdef _DEBUG
#include<windows.h>
#include<string>
#include<sstream>
#include<vector>
namespace elibstl_debug {
	inline std::wstring to_wstring(const std::string& str)
	{
		int widesize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		wchar_t* resultstring = new wchar_t[widesize];

		int convresult = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, resultstring, widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		std::wstring wstrReturn(resultstring);
		delete[] resultstring;
		return wstrReturn;
	}

	template <class Ty>
	static void pt(std::wstring& str, Ty v)
	{

		str.append(std::to_wstring(v) + L" | ");
	}
	template <class Ty>
	static void pt(std::wstring& str, std::vector<Ty> v)
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
	static void pt(std::wstring& str, const wchar_t* s) //这个是 L""
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
	static void pt(std::wstring& str, const char* s) //这个是 L""
	{
		str.append(L"\"");
		if (!s)
		{
			str.append(L"(空)");
			str.append(L"\" | ");
			return;
		}
		str.append(L"\"");

		str.append(to_wstring(s));

		str.append(L"\" | ");
	}
	static void pt(std::wstring& str, std::string s)
	{
		str.append(L"\"");

		str.append(to_wstring(s));

		str.append(L"\" | ");
	}
	static void pt(std::wstring& str, std::wstring s)
	{
		str.append(L"\"");
		str.append(s);
		str.append(L"\" | ");
	}
	static void pt(std::wstring& str, const std::vector<unsigned char>& s)
	{
		if (s.empty())
		{
			str.append(L" 字节集:(空) |");
			return;
		}
		for (size_t i = 0; i < s.size(); i++)
		{
			if (i == 0) {
				str.append(L" 字节集 :" + std::to_wstring((int)s.size()) + L" {");
			}
			str.append(std::to_wstring((int)s.data()[i]));
			str.append(L",");
		}
		str.pop_back();
		str.append(L"} | ");

	};
	static void pt(std::wstring& str, char* s)
	{

		str.append(to_wstring(std::string(s)) + L" | ");

	};
	static void pt(std::wstring& str, void* s)
	{

		str.append(std::to_wstring((int)s) + L" | ");

	};
	//调试输出 支持 无限参数!  任意类型!  (没有的可以重载方法自定义)
	template <class... T>
	static void debug_put_elibstl(const std::wstring&file, const int line, T... args)
	{
		std::wstringstream msg;
		msg << L"* \r\n【************此代码来自标准模板库的调试************】\r\n调试代码页:" << file << L"\r\n所在行:" << line<<L"\r\n";
		std::wstring str{ msg.str() };

		std::initializer_list<INT>{(pt(str, std::forward<T>(args)), 0)...};

		str.pop_back();
		str.pop_back();
		str.append(L"\r\n【***************来自支持库的调试结束***************】\r\n");
		
		OutputDebugStringW(str.c_str());
	};
}
#define debug_put( ...) elibstl_debug::debug_put_elibstl(__FILEW__,__LINE__, __VA_ARGS__) 

#else
#define debug_put(...)
#endif
#pragma endregion