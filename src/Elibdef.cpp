#include"ElibHelp.h"
#include"elib/lang.h"



#ifndef  __E_STATIC_LIB

EXTERN_C INT WINAPI LibKrnln_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);
#pragma region 暴露接口_函数
extern FucInfo
L,//unicode
fint_text_a,//寻找文本A
find_text_w,//寻找文本W
strlen_a,//取文本长度A
wcslen_w,//取文本长度W
rnd_ex,//取随机数Ex
ator,//弧度到角度
rtoa,//角度到弧度
prime,//是否素数
message_box_w,//延迟信息框W
read_file_a,//读入文件A
read_file_w,//读入文件W
write_file_a,//写到文件A
write_file_w,//写到文件W
task_dialog_w,//高级信息框W
set_clip_board_text_w,//置剪辑板文本W
get_clip_board_text_w,//取剪辑板文本W
to_upper_w,//到大写W
to_lower_w,//到小写W
to_full_w,//到全角W
to_half_w,//到半角W
in_str_rev_w,//倒找文本W
split_w,//分割文本W
get_character_w,//字符W
get_char_code_w,//取代码W
ltrim_w,//删收空W
rtrim_w,//删尾空W
trim_w,//删首尾空W
trim_all_w,//删全部空W
left_text_t,//取文本左边W
right_text_w,//取文本右边W
mid_text_w,//取文本中间W
open_console,//打开控制台
set_console_title,//置控制台标题W
read_console_w,//标准输入W
cout_w,//标准输出W
get_console_locale,//取控制台编码
set_console_locale,//置控制台编码
get_net_work_types_w,//枚举网络类型W
Server_GetData,//取回数据
Server_GetCline,//取回客户
Server_CloseClient,//断开客户
Server_start,//启动
Server_close,//关闭
Server_is_open,//是否已启动
Server_Send,//发送数据
Clinet_connect,//连接
Clinet_close,//关闭
Clinet_GetData,//取回数据
Clinet_Send,//发送数据
EditBoxW_AddText,//编辑框.加入文本
clear_folder_W,//磁盘操作→清空目录
create_dir_W,//创建目录W
remove_dir_W,//删除目录W
remove_file_W,//删除文件W
current_path_W,//取运行目录W
get_complete_path_W,//取完整路径W
normalization_path_W,//规范化路径W
get_exe_name_W,//取执行文件名W
get_cmdline_W,//取命令行W
get_env_W,//读环境变量W
set_env_W,//写环境变量W
get_special_folder_path_W,//取特定目录W
prevent_duplicate_execution_W,//禁止程序重复运行W
atomic_increment,//原子递增
atomic_exchange,//原子赋值
atomic_decrement,//原子递减
atomic_addition,//原子运算
create_coroutine,//创建协程
switch_coroutine,//切换协程
is_valid_hCoprocess,//协程句柄是否有效
delete_coroutine,//销毁协程
get_h_coroutine,//取当前函数所在协程
free_console,//分离控制台
get_ip_this,//取本机ip
kill_process,//结束进程
is_64_bit,//是否位64位系统
Media_structure,//媒体播放构造
Media_copy,//媒体播放复制
Media_destruct,//媒体播放析构
Media_open,//媒体播放打开
Media_IsVideo,//是否为视频
Media_GetHwnd,//取句柄
Media_SetHwnd,//置句柄
Media_GetMode,//取状态
Media_GetLength,//取长度
Media_GetPosition,//取位置
Media_GetTotalSec,//取总时间
Media_GetFrameRate,//取比率
Media_Play,//播放
Media_Pause,//暂停
Media_Stop,//停止
Media_GetMCIAlias,//取别名
Media_Close,//关闭
Media_SetVolume,//置音量
Media_GetVolume,//取音量
Media_continue,//继续
Media_GetChannel,//取媒体声道
Media_SetChannel,//置媒体声道
Media_GetFrames,//取帧数
Media_GetMediaVolume,//取媒体音量
Media_SetMediaVolume,//置媒体音量
Media_SetPlaySpeed,//置播放速度
Media_GetPlaySpeed,//取播放速度
Media_SetPos,//置位置
Media_SetFrame//跳到指定帧
;

extern LIB_DATA_TYPE_INFO
buttonw,//按钮W
editboxw,//编辑框W
severex,//服务器Ex
clinetex,//客户端Ex
hCoprocessD,//协程句柄
media_play_ex//媒体播放
;
#pragma endregion

static const char* g_cmdname[] =
{
	rnd_ex.FucName,
	L.FucName,
	fint_text_a.FucName,
	find_text_w.FucName,
	strlen_a.FucName,
	wcslen_w.FucName,
	ator.FucName,
	rtoa.FucName,
	prime.FucName,
	message_box_w.FucName,
	read_file_a.FucName,
	read_file_w.FucName,
	write_file_a.FucName,
	write_file_w.FucName,
	task_dialog_w.FucName,
	set_clip_board_text_w.FucName,
	get_clip_board_text_w.FucName,
	to_upper_w.FucName,
	to_lower_w.FucName,
	to_full_w.FucName,
	to_half_w.FucName,
	in_str_rev_w.FucName,
	split_w.FucName,
	get_character_w.FucName,
	get_char_code_w.FucName,
	ltrim_w.FucName,
	rtrim_w.FucName,
	trim_w.FucName,
	trim_all_w.FucName,
	left_text_t.FucName,
	right_text_w.FucName,
	mid_text_w.FucName,
	open_console.FucName,
	set_console_title.FucName,
	read_console_w.FucName,
	cout_w.FucName,
	get_console_locale.FucName,
	set_console_locale.FucName,
	get_net_work_types_w.FucName,
	Server_GetData.FucName,
	Server_GetCline.FucName,
	Server_CloseClient.FucName,
	Server_start.FucName,
	Server_close.FucName,
	Server_is_open.FucName,
	Server_Send.FucName,
	Clinet_connect.FucName,
	Clinet_close.FucName,
	Clinet_GetData.FucName,
	Clinet_Send.FucName,
	EditBoxW_AddText.FucName,
	clear_folder_W.FucName,
	create_dir_W.FucName,
	remove_dir_W.FucName,
	remove_file_W.FucName,
	current_path_W.FucName,
	get_complete_path_W.FucName,
	normalization_path_W.FucName,
	get_exe_name_W.FucName,
	get_cmdline_W.FucName,
	get_env_W.FucName,
	set_env_W.FucName,
	get_special_folder_path_W.FucName,
	prevent_duplicate_execution_W.FucName,
	atomic_increment.FucName,
	atomic_exchange.FucName,
	atomic_decrement.FucName,
	atomic_addition.FucName,
	create_coroutine.FucName,
	switch_coroutine.FucName,
	is_valid_hCoprocess.FucName,
	delete_coroutine.FucName,
	get_h_coroutine.FucName,
	free_console.FucName,
	get_ip_this.FucName,
	kill_process.FucName,
	is_64_bit.FucName,
	Media_structure.FucName,
	Media_copy.FucName,
	Media_destruct.FucName,
	Media_open.FucName,
	Media_IsVideo.FucName,
	Media_GetHwnd.FucName,
	Media_SetHwnd.FucName,
	Media_GetMode.FucName,
	Media_GetLength.FucName,
	Media_GetPosition.FucName,
	Media_GetTotalSec.FucName,
	Media_GetFrameRate.FucName,
	Media_Play.FucName,
	Media_Pause.FucName,
	Media_Stop.FucName,
	Media_GetMCIAlias.FucName,
	Media_Close.FucName,
	Media_SetVolume.FucName,
	Media_GetVolume.FucName,
	Media_continue.FucName,
	Media_GetChannel.FucName,
	Media_SetChannel.FucName,
	Media_GetFrames.FucName,
	Media_GetMediaVolume.FucName,
	Media_SetMediaVolume.FucName,
	Media_SetPlaySpeed.FucName,
	Media_GetPlaySpeed.FucName,
	Media_SetPos.FucName,
	Media_SetFrame.FucName,
};
static CMD_INFO g_cmdInfo[] =
{
	rnd_ex.FucDef,
	L.FucDef,
	fint_text_a.FucDef,
	find_text_w.FucDef,
	strlen_a.FucDef,
	wcslen_w.FucDef,
	ator.FucDef,
	rtoa.FucDef,
	prime.FucDef,
	message_box_w.FucDef,
	read_file_a.FucDef,
	read_file_w.FucDef,
	write_file_a.FucDef,
	write_file_w.FucDef,
	task_dialog_w.FucDef,
	set_clip_board_text_w.FucDef,
	get_clip_board_text_w.FucDef,
	to_upper_w.FucDef,
	to_lower_w.FucDef,
	to_full_w.FucDef,
	to_half_w.FucDef,
	in_str_rev_w.FucDef,
	split_w.FucDef,
	get_character_w.FucDef,
	get_char_code_w.FucDef,
	ltrim_w.FucDef,
	rtrim_w.FucDef,
	trim_w.FucDef,
	trim_all_w.FucDef,
	left_text_t.FucDef,
	right_text_w.FucDef,
	mid_text_w.FucDef,
	open_console.FucDef,
	set_console_title.FucDef,
	read_console_w.FucDef,
	cout_w.FucDef,
	get_console_locale.FucDef,
	set_console_locale.FucDef,
	get_net_work_types_w.FucDef,
	Server_GetData.FucDef,
	Server_GetCline.FucDef,
	Server_CloseClient.FucDef,
	Server_start.FucDef,
	Server_close.FucDef,
	Server_is_open.FucDef,
	Server_Send.FucDef,
	Clinet_connect.FucDef,
	Clinet_close.FucDef,
	Clinet_GetData.FucDef,
	Clinet_Send.FucDef,
	EditBoxW_AddText.FucDef,
	clear_folder_W.FucDef,
	create_dir_W.FucDef,
	remove_dir_W.FucDef,
	remove_file_W.FucDef,
	current_path_W.FucDef,
	get_complete_path_W.FucDef,
	normalization_path_W.FucDef,
	get_exe_name_W.FucDef,
	get_cmdline_W.FucDef,
	get_env_W.FucDef,
	set_env_W.FucDef,
	get_special_folder_path_W.FucDef,
	prevent_duplicate_execution_W.FucDef,
	atomic_increment.FucDef,
	atomic_exchange.FucDef,
	atomic_decrement.FucDef,
	atomic_addition.FucDef,
	create_coroutine.FucDef,
	switch_coroutine.FucDef,
	is_valid_hCoprocess.FucDef,
	delete_coroutine.FucDef,
	get_h_coroutine.FucDef,
	free_console.FucDef,
	get_ip_this.FucDef,
	kill_process.FucDef,
	is_64_bit.FucDef,
	Media_structure.FucDef,
	Media_copy.FucDef,
	Media_destruct.FucDef,
	Media_open.FucDef,
	Media_IsVideo.FucDef,
	Media_GetHwnd.FucDef,
	Media_SetHwnd.FucDef,
	Media_GetMode.FucDef,
	Media_GetLength.FucDef,
	Media_GetPosition.FucDef,
	Media_GetTotalSec.FucDef,
	Media_GetFrameRate.FucDef,
	Media_Play.FucDef,
	Media_Pause.FucDef,
	Media_Stop.FucDef,
	Media_GetMCIAlias.FucDef,
	Media_Close.FucDef,
	Media_SetVolume.FucDef,
	Media_GetVolume.FucDef,
	Media_continue.FucDef,
	Media_GetChannel.FucDef,
	Media_SetChannel.FucDef,
	Media_GetFrames.FucDef,
	Media_GetMediaVolume.FucDef,
	Media_SetMediaVolume.FucDef,
	Media_SetPlaySpeed.FucDef,
	Media_GetPlaySpeed.FucDef,
	Media_SetPos.FucDef,
	Media_SetFrame.FucDef,
};
static PFN_EXECUTE_CMD g_pcmd[] =
{
	rnd_ex.pFuc,
	L.pFuc,
	fint_text_a.pFuc,
	find_text_w.pFuc,
	strlen_a.pFuc,
	wcslen_w.pFuc,
	ator.pFuc,
	rtoa.pFuc,
	prime.pFuc,
	message_box_w.pFuc,
	read_file_a.pFuc,
	read_file_w.pFuc,
	write_file_a.pFuc,
	write_file_w.pFuc,
	task_dialog_w.pFuc,
	set_clip_board_text_w.pFuc,
	get_clip_board_text_w.pFuc,
	to_upper_w.pFuc,
	to_lower_w.pFuc,
	to_full_w.pFuc,
	to_half_w.pFuc,
	in_str_rev_w.pFuc,
	split_w.pFuc,
	get_character_w.pFuc,
	get_char_code_w.pFuc,
	ltrim_w.pFuc,
	rtrim_w.pFuc,
	trim_w.pFuc,
	trim_all_w.pFuc,
	left_text_t.pFuc,
	right_text_w.pFuc,
	mid_text_w.pFuc,
	open_console.pFuc,
	set_console_title.pFuc,
	read_console_w.pFuc,
	cout_w.pFuc,
	get_console_locale.pFuc,
	set_console_locale.pFuc,
	get_net_work_types_w.pFuc,
	Server_GetData.pFuc,
	Server_GetCline.pFuc,
	Server_CloseClient.pFuc,
	Server_start.pFuc,
	Server_close.pFuc,
	Server_is_open.pFuc,
	Server_Send.pFuc,
	Clinet_connect.pFuc,
	Clinet_close.pFuc,
	Clinet_GetData.pFuc,
	Clinet_Send.pFuc,
	EditBoxW_AddText.pFuc,
	clear_folder_W.pFuc,
	create_dir_W.pFuc,
	remove_dir_W.pFuc,
	remove_file_W.pFuc,
	current_path_W.pFuc,
	get_complete_path_W.pFuc,
	normalization_path_W.pFuc,
	get_exe_name_W.pFuc,
	get_cmdline_W.pFuc,
	get_env_W.pFuc,
	set_env_W.pFuc,
	get_special_folder_path_W.pFuc,
	prevent_duplicate_execution_W.pFuc,
	atomic_increment.pFuc,
	atomic_exchange.pFuc,
	atomic_decrement.pFuc,
	atomic_addition.pFuc,
	create_coroutine.pFuc,
	switch_coroutine.pFuc,
	is_valid_hCoprocess.pFuc,
	delete_coroutine.pFuc,
	get_h_coroutine.pFuc,
	free_console.pFuc,
	get_ip_this.pFuc,
	kill_process.pFuc,
	is_64_bit.pFuc,
	Media_structure.pFuc,
	Media_copy.pFuc,
	Media_destruct.pFuc,
	Media_open.pFuc,
	Media_IsVideo.pFuc,
	Media_GetHwnd.pFuc,
	Media_SetHwnd.pFuc,
	Media_GetMode.pFuc,
	Media_GetLength.pFuc,
	Media_GetPosition.pFuc,
	Media_GetTotalSec.pFuc,
	Media_GetFrameRate.pFuc,
	Media_Play.pFuc,
	Media_Pause.pFuc,
	Media_Stop.pFuc,
	Media_GetMCIAlias.pFuc,
	Media_Close.pFuc,
	Media_SetVolume.pFuc,
	Media_GetVolume.pFuc,
	Media_continue.pFuc,
	Media_GetChannel.pFuc,
	Media_SetChannel.pFuc,
	Media_GetFrames.pFuc,
	Media_GetMediaVolume.pFuc,
	Media_SetMediaVolume.pFuc,
	Media_SetPlaySpeed.pFuc,
	Media_GetPlaySpeed.pFuc,
	Media_SetPos.pFuc,
	Media_SetFrame.pFuc,
};
static LIB_DATA_TYPE_INFO g_DataType[] = {
	buttonw,
	editboxw,
	severex,
	clinetex,
	hCoprocessD,
	media_play_ex
};
static LIB_INFO s_LibInfo =
{
	/*m_dwLibFormatVer*/        LIB_FORMAT_VER, // 库格式号, 应该等于LIB_FORMAT_VER
	/*m_szGuid*/                "9E98DDB731D5421890CAD9CC6C999442", // 对应于本库的唯一GUID串, 不能为NULL或空, 库的所有版本此串都应相同
	/*m_nMajorVersion*/         2, // 本库的主版本号, 必须大于0
	/*m_nMinorVersion*/         2, // 本库的次版本号
	/*m_nBuildNumber*/          1, // 构建版本号, 无需对此版本号作任何处理

	/*m_nRqSysMajorVer*/        3, // 所需要的易语言系统的主版本号
	/*m_nRqSysMinorVer*/        0, // 所需要的易语言系统的次版本号
	/*m_nRqSysKrnlLibMajorVer*/ 3, // 所需要的系统核心支持库的主版本号
	/*m_nRqSysKrnlLibMinorVer*/ 0, // 所需要的系统核心支持库的次版本号

	/*m_szName*/                "LibKrnln", // 库名, 不能为NULL或空
	/*m_nLanguage*/             __GBK_LANG_VER, // 库所支持的语言
	/*m_szExplain*/             "", // 库详细解释
	/*m_dwState*/               _LIB_OS(OS_ALL), // _LIB_OS() | LBS_ 开头常量, 如果是插件,必须包含 LBS_IDE_PLUGIN

	/*m_szAuthor*/              "阿龙", // 作者
	/*m_szZipCode*/             "", // 邮编
	/*m_szAddress*/             "", // 地址
	/*m_szPhoto*/               "", // 联系电话
	/*m_szFax*/                 "", // 传真
	/*m_szEmail*/               "", // 邮箱
	/*m_szHomePage*/            "", // 主页
	/*m_szOther*/               "", // 其他信息

	/*m_nDataTypeCount*/       sizeof(g_DataType) / sizeof(g_DataType[0]), // 本库中自定义数据类型的数目
	/*g_DataType_web*/        g_DataType, // 本库中所有的自定义数据类型

	/*m_nCategoryCount*/        9, // 全局命令类别数目, 可为0
	/*m_szzCategory*/           "0000算术运算\0" "0000文本操作\0""0000操作系统\0""0000磁盘操作\0""0000控制台程序\0""0000系统处理\0""0000网络通信\0""0000环境存取\0""0000进程线程协程\0""\0", // 全局命令类别数目, 可为0

	/*m_nCmdCount*/             sizeof(g_cmdInfo) / sizeof(g_cmdInfo[0]), // 本库中提供的所有命令(全局命令及对象命令)的数目, 可为0
	/*m_pBeginCmdInfo*/        g_cmdInfo, // 本库中提供的所有命令
	/*m_pCmdsFunc*/            g_pcmd, // 指向每个命令的实现代码首地址, 可为NULL

	/*m_pfnRunAddInFn*/         NULL,
	NULL, // 功能详细介绍(仅限一行60字符), 最后由两个空串结束

	/*m_pfnNotify*/             LibKrnln_ProcessNotifyLib, // 不能为NULL,和易语言通讯的子程序

	/*m_pfnSuperTemplate*/      NULL, // 模板 可为NULL
  //  有关SuperTemplate的说明, 两个字符串说明一个SuperTemplate。
 //  第一个为SuperTemplate名称(仅限一行30字符), 第二个为详细介绍(不限), 
  //  最后由两个空串结束。
  /*m_szzSuperTemplateInfo*/  NULL, // 模板 可为NULL
  /*m_nLibConstCount*/        0, // 本库预先定义的所有常量数量
  /*m_pLibConst*/             0, // 本库预先定义的所有常量
  /*m_szzDependFiles*/        NULL // 可为NULL, 本库正常运行所需要依赖的其他支持文件
};

extern "C" _declspec(dllexport)  PLIB_INFO  GetNewInf()
{

	return  &s_LibInfo;

};
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

#endif 
EXTERN_C INT WINAPI LibKrnln_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{

#ifndef __E_STATIC_LIB

	if (nMsg == NL_GET_CMD_FUNC_NAMES)

		return (INT)g_cmdname;

	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME)

		return (INT)"LibKrnln_ProcessNotifyLib";

	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;


#endif

	return elibkrnln::ProcessNotifyLib(nMsg, dwParam1, dwParam2);

}