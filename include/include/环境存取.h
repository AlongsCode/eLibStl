#pragma once
#ifdef _WIN32
vector<wstring> 枚举注册表项(HKEY 根类, const wstring& 父路径);
vector<string> 枚举注册表项(HKEY 根类, const string& 父路径);
std::vector<std::wstring> 取命令行W();
std::vector<std::string> 取命令行A();

size_t 取命令行W(std::vector<std::wstring>& saryArgs);
size_t 取命令行A(std::vector<std::string>& saryArgs);
#ifdef _UNICODE
#define  取命令行  取命令行W
#else
#define  取命令行  取命令行A
#endif


#endif
#ifdef _UNICODE
#define 取运行目录 取运行目录W
#define 取执行文件名 取执行文件名W
#else
#define 取运行目录 取运行目录A
#define 取执行文件名 取执行文件名A
#endif


string 取执行文件名A();
wstring 取执行文件名W();

string 读环境变量(const string& 环境变量名称);
wstring 读环境变量(const wstring& 环境变量名称);



//将目录中所有的"/"转为"\",所有的大写转小写
string 规范化路径(const string& 路径);
//将目录中所有的"/"转为"\",所有的大写转小写
wstring 规范化路径(const wstring& 路径);
wstring 取运行目录W();
string 取运行目录A();

bool 写环境变量(const string& 环境变量名称, const string& 欲写入内容);
bool 写环境变量(const wstring& 环境变量名称, const wstring& 欲写入内容);




/*目录为空则取当前路径*/
string 合并路径(const string& 文件名, const string& 目录 = "");
/*目录为空则取当前路径*/
wstring get_complete_path(const wstring& 文件名, const wstring& 目录 = L"");