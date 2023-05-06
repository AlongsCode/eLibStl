#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include"ElibHelp.h"
#include"elib/lang.h"
#include"DefCmd.h"
#pragma comment(lib, "legacy_stdio_definitions.lib") 
//以下代码无需关注，添加命令自建cpp,命令和对象添加到DefCmd
#ifndef  __E_STATIC_LIB
//我怕vc2017linker链接不上,静态库用宏屏蔽掉吧，也不影响动态库的编译
#include<algorithm>
#include<iterator>

EXTERN_C INT WINAPI LibStl_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);

#pragma region 暴露接口
extern FucInfo
ALL_E_LIB_CMD;
//防止符号污染


ESTL_NAMESPACE_BEGIN

extern LIB_DATA_TYPE_INFO
ALL_E_LIB_CLASS;

//所有命令,此下用于动态添加,只需要将每个obj暴漏的接口添加到下方就好
std::vector<FucInfo> g_all_cmd = { ALL_E_LIB_CMD };

//所有对象,此下用于动态添加,只需要将每个obj暴漏的接口添加到下方就好
static LIB_DATA_TYPE_INFO g_DataType[] = { ALL_E_LIB_CLASS };

//所有命令的信息
std::vector<CMD_INFO> g_all_cmd_info;

//所有命令的指针
std::vector<PFN_EXECUTE_CMD> g_all_pcmd;

//所有类的名字#用于静态编译
std::vector<const char*> g_cmd_name;

static LIB_INFO s_LibInfo =
{
	/*m_dwLibFormatVer*/        LIB_FORMAT_VER, // 库格式号, 应该等于LIB_FORMAT_VER
	/*m_szGuid*/                "9E98DDB731D5421890CAD9CC6C999442", // 对应于本库的唯一GUID串, 不能为NULL或空, 库的所有版本此串都应相同
	/*m_nMajorVersion*/         1, // 本库的主版本号, 必须大于0
	/*m_nMinorVersion*/         1, // 本库的次版本号
	/*m_nBuildNumber*/          1, // 构建版本号, 无需对此版本号作任何处理

	/*m_nRqSysMajorVer*/        3, // 所需要的易语言系统的主版本号
	/*m_nRqSysMinorVer*/        0, // 所需要的易语言系统的次版本号
	/*m_nRqSysKrnlLibMajorVer*/ 3, // 所需要的系统核心支持库的主版本号
	/*m_nRqSysKrnlLibMinorVer*/ 0, // 所需要的系统核心支持库的次版本号

	/*m_szName*/                "标准模板库", // 库名, 不能为NULL或空
	/*m_nLanguage*/             __GBK_LANG_VER, // 库所支持的语言
	/*m_szExplain*/             "易语言核心库拓展", // 库详细解释
	/*m_dwState*/               _LIB_OS(OS_ALL), // _LIB_OS() | LBS_ 开头常量, 如果是插件,必须包含 LBS_IDE_PLUGIN

	/*m_szAuthor*/              "阿龙、福仔、QingKong", // 作者
	/*m_szZipCode*/             "", // 邮编
	/*m_szAddress*/             "", // 地址
	/*m_szPhoto*/               "", // 联系电话
	/*m_szFax*/                 "", // 传真
	/*m_szEmail*/               "", // 邮箱
	/*m_szHomePage*/            "", // 主页
	/*m_szOther*/               "", // 其他信息

	/*m_nDataTypeCount*/       sizeof(g_DataType) / sizeof(g_DataType[0]), // 本库中自定义数据类型的数目
	/*g_DataType_web*/         g_DataType, // 本库中所有的自定义数据类型

	/*m_nCategoryCount*/        15, // 全局命令类别数目, 可为0
	/*m_szzCategory*/
	"0000算术运算\0"
	"0000文本操作\0"
	"0000操作系统\0"
	"0000磁盘操作\0"
	"0000控制台程序\0"
	"0000系统处理\0"
	"0000网络通信\0"
	"0000环境存取\0"
	"0000进程线程协程\0"
	"0000窗口操作\0"
	"0000代码调试\0"
	"0000其他\0"
	"0000常用对话框\0"
	"0000数据库\0"
	"0000内存操作\0"
	"\0",

	/*m_nCmdCount*/             0, // 本库中提供的所有命令(全局命令及对象命令)的数目, 可为0
	/*m_pBeginCmdInfo*/			0, // 本库中提供的所有命令
	/*m_pCmdsFunc*/				0, // 指向每个命令的实现代码首地址, 可为NULL

	/*m_pfnRunAddInFn*/         NULL,
	NULL, // 功能详细介绍(仅限一行60字符), 最后由两个空串结束

	/*m_pfnNotify*/             LibStl_ProcessNotifyLib, // 不能为NULL,和易语言通讯的子程序

	/*m_pfnSuperTemplate*/      NULL, // 模板 可为NULL
	//  有关SuperTemplate的说明, 两个字符串说明一个SuperTemplate。
	//  第一个为SuperTemplate名称(仅限一行30字符), 第二个为详细介绍(不限), 
	//  最后由两个空串结束。
	/*m_szzSuperTemplateInfo*/  NULL, // 模板 可为NULL
	/*m_nLibConstCount*/        0, // 本库预先定义的所有常量数量
	/*m_pLibConst*/             0, // 本库预先定义的所有常量
	/*m_szzDependFiles*/        NULL // 可为NULL, 本库正常运行所需要依赖的其他支持文件
};
ESTL_NAMESPACE_END

extern "C" _declspec(dllexport) PLIB_INFO GetNewInf()
{
	using namespace elibstl;
	//没初始化的话先初始化
	if (s_LibInfo.m_nCmdCount != g_all_cmd.size())
	{
		std::transform(g_all_cmd.begin(), g_all_cmd.end(), std::back_inserter(g_all_cmd_info), [](const auto& elem) { return elem.FucDef; });
		std::transform(g_all_cmd.begin(), g_all_cmd.end(), std::back_inserter(g_all_pcmd), [](const auto& elem) { return elem.pFuc; });
		s_LibInfo.m_pBeginCmdInfo = g_all_cmd_info.data();
		s_LibInfo.m_pCmdsFunc = g_all_pcmd.data();
		s_LibInfo.m_nCmdCount = g_all_cmd.size();
	}
	return  &s_LibInfo;
};
#pragma endregion 暴露接口
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		g_elibstl_hModule = hModule;
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

#endif  // !__E_STATIC_LIB
EXTERN_C INT WINAPI LibStl_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	using namespace elibstl;
#ifndef __E_STATIC_LIB
	switch (nMsg)
	{
	case NL_GET_CMD_FUNC_NAMES:
		if (g_cmd_name.empty())
		{
			std::transform(g_all_cmd.begin(), g_all_cmd.end(), std::back_inserter(g_cmd_name), [](const auto& elem) { return elem.FucName; });
		}
		return (INT)g_cmd_name.data();
	case NL_GET_NOTIFY_LIB_FUNC_NAME:
		return (INT)"LibStl_ProcessNotifyLib";
	case NL_GET_DEPENDENT_LIBS:
		return (INT)NULL;
	}
#endif // !__E_STATIC_LIB
	return elibstl::ProcessNotifyLib(nMsg, dwParam1, dwParam2);
}