#pragma once
//因为核心库中部分W和A所以unicode与ansi转换很有必要
//库中复用性较强，使用内联减少栈开辟消耗
std::wstring 文本到宽文本(const std::string& 文本);
std::string 宽文本到文本(const std::wstring& 宽文本);
std::wstring UTF8到宽文本(const char* lpcszString);
std::wstring UTF8到宽文本(const std::string& utf8string);
std::string 宽文本到UTF8(const std::wstring& widestring);
std::string 文本到UTF8(const std::string& 文本);
