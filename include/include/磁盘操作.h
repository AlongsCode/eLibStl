#pragma once
/*比较重要的平台特定函数依然存在核心库之中*/
#ifdef _WIN32
/*在文件资源管理器中显示并选中指定文件,编辑模式为真则选中时设为重命名模式*/
bool 定位文件(const std::wstring& 文件路径, bool 编辑模式 = false);
bool 定位文件(const std::string& 文件路径, bool 编辑模式 = false);

long long 取磁盘剩余空间(char 磁盘驱动器字符);
long long 取磁盘剩余空间(wchar_t 磁盘驱动器字符);
long long 取磁盘剩余空间(const wstring& 磁盘驱动器字符 = L"");
long long 取磁盘剩余空间(const string& 磁盘驱动器字符);

bool 置磁盘卷标(const string& 磁盘驱动器字符, const string& 欲置入的卷标文本 = "");
bool 置磁盘卷标(const wstring& 磁盘驱动器字符 = L"", const wstring& 欲置入的卷标文本 = L"");
bool 置磁盘卷标(char 磁盘驱动器字符, const string& 欲置入的卷标文本 = "");
bool 置磁盘卷标(wchar_t 磁盘驱动器字符, const wstring& 欲置入的卷标文本 = L"");

string 取磁盘卷标A(char 磁盘驱动器字符);
wstring 取磁盘卷标W(wchar_t 磁盘驱动器字符);
string 取磁盘卷标A(const string& 磁盘驱动器字符 = "");
wstring 取磁盘卷标W(const wstring& 磁盘驱动器字符 = L"");


long long 取磁盘总空间(wchar_t 磁盘驱动器字符);
long long 取磁盘总空间(char 磁盘驱动器字符);
long long 取磁盘总空间(const wstring& 磁盘驱动器字符 = L"");
long long 取磁盘总空间(const string& 磁盘驱动器字符);

/*磁盘操作 - 置文件属性
	调用格式： 〈逻辑型〉 置文件属性 （文本型 欲设置其属性的文件名称，整数型 欲设置为的属性值） - 系统核心支持库->磁盘操作
	英文名称：SetAttr
	为一个文件设置属性信息。成功返回真，失败返回假。本命令为初级命令。
	参数<1>的名称为“欲设置其属性的文件名称”，类型为“文本型（text）”。
	参数<2>的名称为“欲设置为的属性值”，类型为“整数型（int）”。参数值可以为以下常量值或其和： 1、#只读文件； 2、#隐藏文件； 4、#系统文件； 32、#存档文件 。通过将这些常量值加起来可以一次设置多个文件属性。
*/
bool 置文件属性(const wstring& 欲设置其属性的文件名称, int 欲设置为的属性值);
/*磁盘操作 - 置文件属性
	调用格式： 〈逻辑型〉 置文件属性 （文本型 欲设置其属性的文件名称，整数型 欲设置为的属性值） - 系统核心支持库->磁盘操作
	英文名称：SetAttr
	为一个文件设置属性信息。成功返回真，失败返回假。本命令为初级命令。
	参数<1>的名称为“欲设置其属性的文件名称”，类型为“文本型（text）”。
	参数<2>的名称为“欲设置为的属性值”，类型为“整数型（int）”。参数值可以为以下常量值或其和： 1、#只读文件； 2、#隐藏文件； 4、#系统文件； 32、#存档文件 。通过将这些常量值加起来可以一次设置多个文件属性。
*/
bool 置文件属性(const string& 欲设置其属性的文件名称, int 欲设置为的属性值);
#pragma region 取磁盘卷标

#ifdef _UNICODE
#define 取磁盘卷标() 取磁盘卷标A()
#else
#define 取磁盘卷标() 取磁盘卷标W()
#endif

#else
#endif



/*全平台通用函数*/
bool 改变驱动器(const string& 欲改变到的驱动器);
bool 改变驱动器(const wstring& 欲改变到的驱动器);
bool 改变驱动器(char 欲改变到的驱动器);
bool 改变驱动器(wchar_t 欲改变到的驱动器);

bool 改变目录(const string& 欲改变到的目录);
bool 改变目录(const wstring& 欲改变到的目录);

/*强制创建会将不存在父目录的目录中创建文件*/
bool create_dir(const string& 欲创建的目录名称, bool 强制创建 = false);
/*强制创建会将不存在父目录的目录中创建文件*/
bool 创建目录(const wstring& 欲创建的目录名称, bool 强制创建 = false);


bool 删除目录(const string& 欲删除的目录名称);
bool 删除目录(const wstring& 欲删除的目录名称);

bool 复制文件(const string& 被复制的文件名, const string& 复制到的文件名);
bool 复制文件(const wstring& 被复制的文件名, const wstring& 复制到的文件名);

bool 移动文件(const wstring& 被移动的文件, const wstring& 移动到的位置);
bool 移动文件(const string& 被移动的文件, const string& 移动到的位置);

bool 删除文件(const wstring& 欲删除的文件名);
bool 删除文件(const string& 欲删除的文件名);

bool 文件更名(const wstring& 欲更名的原文件或目录名, const wstring& 欲更改为的现文件或目录名);
bool 文件更名(const string& 欲更名的原文件或目录名, const string& 欲更改为的现文件或目录名);

bool 文件是否存在(const string& 欲测试的文件名称);
bool 文件是否存在(const wstring& 欲测试的文件名称);
//如果不想带着你的寻找文件进行一整个程序生命周期的内存，请不用时及时释放;
string 寻找文件(string 欲寻找的文件或目录名称 = "", int 欲寻找文件的属性 = 0);
wstring 寻找文件(const wstring& 欲寻找的文件或目录名称 = L"", int 欲寻找文件的属性 = 0);

std::tm 取文件时间(const string& 文件名);
std::tm 取文件时间(const wstring& 文件名);

int 取文件属性(const string& 文件名);
int 取文件属性(const wstring& 文件名);

long long 取文件尺寸(const wstring& 文件名);
long long 取文件尺寸(const string& 文件名);
#define 取文件大小(文件名) 取文件尺寸(文件名);




//默认清空所有目录，类型可以指定为任意文件类型，如"txt"
bool 清空目录(const std::string& 要删除文件的目录, const std::string& 文件类型 = "", bool 删除文件夹 = true);
//默认清空所有目录，类型可以指定为任意文件类型，如"txt"
bool 清空目录(const std::wstring& 要删除文件的目录, const std::wstring& 文件类型 = L"", bool 删除文件夹 = true);
string 取临时文件名A(const string& 目录名 = "");
wstring 取临时文件名W(const wstring& 目录名 = L"");
#pragma region 取临时文件名
std::string 取父路径(const std::string& 欲取父路径的目录或文件);
std::wstring 取父路径(const std::wstring& 欲取父路径的目录或文件);
#ifdef _UNICODE
#define 取临时文件名() 取临时文件名A()
#else
#define 取临时文件名() 取临时文件名W()
#endif

#pragma endregion

vector<unsigned char> 读入文件(const string& 文件名);
vector<unsigned char> 读入文件(const wstring& 文件名);


bool 写到文件(const string& 文件名, vector<unsigned char>  欲写入文件的数据);
bool 写到文件(const wstring& 文件名, vector<unsigned char>  欲写入文件的数据);


#pragma region 取当前目录

string 取当前目录A();
wstring 取当前目录W();
#ifdef _UNICODE
#define 取当前目录() 取当前目录A()
#else
#define 取当前目录() 取当前目录W()
#endif

#pragma endregion