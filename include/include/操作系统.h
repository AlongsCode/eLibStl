//此位置为平台系统级常用处理函数,不同平台的提供的代码并不相同，注意区分
#ifdef _WIN32//win环境下的系统处理
#include<windows.h>

#pragma region 注册表操作
enum class 注册表根目录
{
	根类 = 1,
	现行设置,
	现行用户,
	本地机器,
	所有用户
};
bool 注册项是否存在(注册表根目录 根目录, const std::string& 注册项名称);
bool 注册项是否存在(注册表根目录 根目录, const std::wstring& 注册项名称);
bool 写注册项(注册表根目录 rootDirectory, const std::string& fullPathKeyName, const std::string& value);
bool 写注册项(注册表根目录 rootDirectory, const std::string& fullPathKeyName, const std::vector<unsigned char>& value);
bool 写注册项(注册表根目录 rootDirectory, const std::wstring& fullPathKeyName, const std::wstring& value);
bool 写注册项(注册表根目录 rootDirectory, const std::wstring& fullPathKeyName, const std::vector<unsigned char>& value);

#pragma endregion



BOOL  安装字体(const std::string& 字体文件);
/*当安装字体为内存资源时为临时安装，生命周期跟随进程，并且为进程独占，其他进程须发共享已安装的字体资源*/
HANDLE  安装字体(const vector<unsigned char>& FontData);
BOOL  安装字体(const std::wstring& 字体文件);
BOOL 卸载字体(const std::string& 字体文件);
BOOL 卸载字体(const std::wstring& 字体文件);
BOOL 卸载字体(HANDLE 字体句柄);
BOOL 延迟(INT64 millisecond);
BOOL  播放音乐(const vector<unsigned char>& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);
BOOL  播放音乐(const string& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);
BOOL  播放音乐(const wstring& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);
BOOL  停止播放();
#pragma region 非暴漏接口
namespace KrnlnMidInside {
	struct MIDIFILEDATAINFO
	{
		unsigned char* pData;
		size_t	dwSize;
	};
	//字符串0，宽字符串1，数据指针2;
	struct MIDMUSIC
	{

		string name;
		wstring wname;
		MIDIFILEDATAINFO data;

		int datatype;
	};
	void PackMid(vector<MIDMUSIC>& MidStruct, string MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, wstring MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, vector<unsigned char> MemData);
	void PlayMid(int times, int interval, vector<MIDMUSIC> wannaplay);
}
#pragma endregion

template <class... T>
void 播放MID(int 播放次数, int 间隔时间, T... 欲播放MID)
{
	vector<KrnlnMidInside::MIDMUSIC> Data;
	std::initializer_list<INT>{(PackMid(Data, std::forward<T>(欲播放MID)), 0)...};
	KrnlnMidInside::PlayMid(播放次数, 间隔时间, Data);
};




/*
	调用格式： 〈整数型〉 信息框 （通用型 提示信息，整数型 按钮，［文本型 窗口标题］） - 系统核心支持库->系统处理
	英文名称：MsgBox
	在对话框中显示信息，等待用户单击按钮，并返回一个整数告诉用户单击哪一个按钮。该整数为以下常量值之一： 0、#确认钮； 1、#取消钮； 2、#放弃钮； 3、#重试钮； 4、#忽略钮； 5、#是钮； 6、#否钮。如果对话框有“取消”按钮，则按下 ESC 键与单击“取消”按钮的效果相同。本命令为初级命令。
	参数<1>的名称为“提示信息”，类型为“通用型（all）”。提示信息只能为文本、数值、逻辑值或日期时间。如果提示信息为文本且包含多行，可在各行之间用回车符 (即“字符 (13)”)、换行符 (即“字符 (10)”) 或回车换行符的组合 (即：“字符 (13) + 字符 (10)”) 来分隔。
	参数<2>的名称为“按钮”，类型为“整数型（int）”，初始值为“0”。参数值由以下几组常量值组成，在将这些常量值相加以生成参数值时，每组值只能取用一个数字（第五组除外）：
  第一组（描述对话框中显示按钮的类型与数目）：
	0、#确认钮； 1、#确认取消钮； 2、#放弃重试忽略钮； 3、#取消是否钮；     4、#是否钮； 5、#重试取消钮
  第二组（描述图标的样式）：
	16、#错误图标； 32、#询问图标； 48、#警告图标； 64、#信息图标
  第三组（说明哪一个按钮是缺省默认值）：
	0、#默认按钮一； 256、#默认按钮二； 512、#默认按钮三； 768、#默认按钮四
  第四组（决定如何等待消息框结束）：
	0、#程序等待； 4096、#系统等待
  第五组（其它）：
	65536、#位于前台； 524288、#文本右对齐

	参数<3>的名称为“窗口标题”，类型为“文本型（text）”，可以被省略。参数值指定显示在对话框标题栏中的文本。如果省略，默认为文本“信息：”。
*/
int 信息框(const string& 提示信息, int 按钮 = 0, const  string& 窗口标题 = "信息", HWND 父窗口 = NULL);
/*
	调用格式： 〈整数型〉 信息框 （通用型 提示信息，整数型 按钮，［文本型 窗口标题］） - 系统核心支持库->系统处理
	英文名称：MsgBox
	在对话框中显示信息，等待用户单击按钮，并返回一个整数告诉用户单击哪一个按钮。该整数为以下常量值之一： 0、#确认钮； 1、#取消钮； 2、#放弃钮； 3、#重试钮； 4、#忽略钮； 5、#是钮； 6、#否钮。如果对话框有“取消”按钮，则按下 ESC 键与单击“取消”按钮的效果相同。本命令为初级命令。
	参数<1>的名称为“提示信息”，类型为“通用型（all）”。提示信息只能为文本、数值、逻辑值或日期时间。如果提示信息为文本且包含多行，可在各行之间用回车符 (即“字符 (13)”)、换行符 (即“字符 (10)”) 或回车换行符的组合 (即：“字符 (13) + 字符 (10)”) 来分隔。
	参数<2>的名称为“按钮”，类型为“整数型（int）”，初始值为“0”。参数值由以下几组常量值组成，在将这些常量值相加以生成参数值时，每组值只能取用一个数字（第五组除外）：
  第一组（描述对话框中显示按钮的类型与数目）：
	0、#确认钮； 1、#确认取消钮； 2、#放弃重试忽略钮； 3、#取消是否钮；     4、#是否钮； 5、#重试取消钮
  第二组（描述图标的样式）：
	16、#错误图标； 32、#询问图标； 48、#警告图标； 64、#信息图标
  第三组（说明哪一个按钮是缺省默认值）：
	0、#默认按钮一； 256、#默认按钮二； 512、#默认按钮三； 768、#默认按钮四
  第四组（决定如何等待消息框结束）：
	0、#程序等待； 4096、#系统等待
  第五组（其它）：
	65536、#位于前台； 524288、#文本右对齐

	参数<3>的名称为“窗口标题”，类型为“文本型（text）”，可以被省略。参数值指定显示在对话框标题栏中的文本。如果省略，默认为文本“信息：”。
*/
int 信息框(const wstring& 提示信息, int 按钮 = 0, const wstring& 窗口标题 = L"信息", HWND 父窗口 = NULL);

#else//Linux POSIX 环境下的系统处理macos用苹果的编程语言比较多，不再单独列出



#endif 

