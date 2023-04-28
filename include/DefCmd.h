#pragma region 命令添加到这
#define CMD_START_LINE __LINE__
#define ALL_E_LIB_CMD \
rnd_ex,/*取随机数Ex*/\
L,/*unicode_base*/\
fint_text_a,/*寻找文本A*/\
find_text_w,/*寻找文本W*/\
strlen_a,/*取文本长度A*/\
wcslen_w,/*取文本长度W*/\
ator,/*弧度到角度*/\
rtoa,/*角度到弧度*/\
prime,/*是否素数*/\
message_box_w,/*延迟信息框W*/\
read_file_a,/*读入文件A*/\
read_file_w,/*读入文件W*/\
write_file_a,/*写到文件A*/\
write_file_w,/*写到文件W*/\
task_dialog_w,/*高级信息框W*/\
set_clip_board_text_w,/*置剪辑板文本W*/\
get_clip_board_text_w,/*取剪辑板文本W*/\
to_upper_w,/*到大写W*/\
to_lower_w,/*到小写W*/\
to_full_w,/*到全角W*/\
to_half_w,/*到半角W*/\
in_str_rev_w,/*倒找文本W*/\
split_w,/*分割文本W*/\
get_character_w,/*字符W*/\
get_char_code_w,/*取代码W*/\
ltrim_w,/*删收空W*/\
rtrim_w,/*删尾空W*/\
trim_w,/*删首尾空W*/\
trim_all_w,/*删全部空W*/\
left_text_t,/*取文本左边W*/\
right_text_w,/*取文本右边W*/\
mid_text_w,/*取文本中间W*/\
open_console,/*打开控制台*/\
set_console_title,/*置控制台标题W*/\
read_console_w,/*标准输入W*/\
cout_w,/*标准输出W*/\
get_console_locale,/*取控制台编码*/\
set_console_locale,/*置控制台编码*/\
get_net_work_types_w,/*枚举网络类型W*/\
Server_GetData,/*取回数据*/\
Server_GetCline,/*取回客户*/\
Server_CloseClient,/*断开客户*/\
Server_start,/*启动*/\
Server_close,/*关闭*/\
Server_is_open,/*是否已启动*/\
Server_Send,/*发送数据*/\
Clinet_connect,/*连接*/\
Clinet_close,/*关闭*/\
Clinet_GetData,/*取回数据*/\
Clinet_Send,/*发送数据*/\
EditBoxW_AddText,/*编辑框.加入文本*/\
clear_folder_W,/*磁盘操作→清空目录*/\
create_dir_W,/*创建目录W*/\
remove_dir_W,/*删除目录W*/\
remove_file_W,/*删除文件W*/\
current_path_W,/*取运行目录W*/\
get_complete_path_W,/*取完整路径W*/\
normalization_path_W,/*规范化路径W*/\
get_exe_name_W,/*取执行文件名W*/\
get_cmdline_W,/*取命令行W*/\
get_env_W,/*读环境变量W*/\
set_env_W,/*写环境变量W*/\
get_special_folder_path_W,/*取特定目录W*/\
prevent_duplicate_execution_W,/*禁止程序重复运行W*/\
atomic_increment,/*原子递增*/\
atomic_exchange,/*原子赋值*/\
atomic_decrement,/*原子递减*/\
atomic_addition,/*原子运算*/\
create_coroutine,/*创建协程*/\
switch_coroutine,/*切换协程*/\
is_valid_hCoprocess,/*协程句柄是否有效*/\
delete_coroutine,/*销毁协程*/\
get_h_coroutine,/*取当前函数所在协程*/\
free_console,/*分离控制台*/\
get_ip_this,/*取本机ip*/\
kill_process,/*结束进程*/\
is_64_bit,/*是否位64位系统*/\
Media_structure,/*媒体播放构造*/\
Media_copy,/*媒体播放复制*/\
Media_destruct,/*媒体播放析构*/\
Media_open,/*媒体播放打开*/\
Media_IsVideo,/*是否为视频*/\
Media_GetHwnd,/*取句柄*/\
Media_SetHwnd,/*置句柄*/\
Media_GetMode,/*取状态*/\
Media_GetLength,/*取长度*/\
Media_GetPosition,/*取位置*/\
Media_GetTotalSec,/*取总时间*/\
Media_GetFrameRate,/*取比率*/\
Media_Play,/*播放*/\
Media_Pause,/*暂停*/\
Media_Stop,/*停止*/\
Media_GetMCIAlias,/*取别名*/\
Media_Close,/*关闭*/\
Media_SetVolume,/*置音量*/\
Media_GetVolume,/*取音量*/\
Media_continue,/*继续*/\
Media_GetChannel,/*取媒体声道*/\
Media_SetChannel,/*置媒体声道*/\
Media_GetFrames,/*取帧数*/\
Media_GetMediaVolume,/*取媒体音量*/\
Media_SetMediaVolume,/*置媒体音量*/\
Media_SetPlaySpeed,/*置播放速度*/\
Media_GetPlaySpeed,/*取播放速度*/\
Media_SetPos,/*置位置*/\
Media_SetFrame,/*跳到指定帧*/\
Media_IsOpen,/*是否已打开*/\
is_connect_to_internet,/*是否已联网*/\
check_port,/*端口是否可用*/\
send_net_msg,/*发送网络消息*/\
EditBoxW_GetHwnd,/*编辑框取编辑框句柄*/\
e_coroutine_close,/*释放协程调度器*/\
e_coroutine_open,/*创建协程调度器*/\
e_hCoi2h,/*指针到调度器*/\
analog_press,/*模拟按下*/\
analog_up,/*模拟弹起*/\
replace_substring_w,/*取CPU当前使用率*/\
get_cpu_id,/*获取CPU序列号*/\
network_post/*网页访问*/\
,capitalize_first_letter/*首字母大写*/\
,capitalize_first_letter/*按钮取组件句柄*/\
,EUpDown_GetHwnd/*调节器取组件句柄*/\
,e_debugput/*调试*/\
,e_CallEfun/*执行函数*/\
,_e_delay/*延迟Ex*/\
,e_GetTickCount_ex/*取启动时间Ex*/\
,e_eLibCallEfun/*调用易库函数*/\
,e_Open_File_Dialog_A/*文件选择夹*/\
,e_Open_File_Dialog_W/*文件选择夹W*/\
,e_BrowseForFolder_W/*文件浏览夹W*/\
,e_BrowseForFolder_A/*文件浏览夹*/\
,e_lib_CreateEbds/*文件浏览夹*/\
,edbs_ex_structure/*EDBS构造*/\
,edbs_ex_copy/*EDB复制*/\
,edbs_ex_destruct/*析构*/\
,edbs_ex_open/*打开*/\
,edbs_get_row_num/*取记录数*/\
,edbs_ex_addpendnop/*加空记录*/\
,edbs_set_current/*跳到*/\
,edbs_read/*读*/\
,edbs_write/*写*/\
, edbs_close/*关闭*/\
,edbs_next\
,edbs_previous\
,edbs_clean\
,edbs_begin\
,edbs_commit\
,edbs_get_current\
,edbs_get_column_name\
,edbs_get_column_num\
,edbs_set_column_name\



//,ansiwindow_to_unicodewindow/*窗口unicode支持*/



#pragma endregion





#pragma region 对象添加到这
#define ALL_E_LIB_CLASS \
CtButtonW,/*按钮W*/\
editboxw,/*编辑框W*/\
severex,/*服务器Ex*/\
clinetex,/*客户端Ex*/\
hCoprocessD,/*协程句柄*/\
media_play_ex,/*媒体播放*/\
TaskDialog_Button_Type,/*高级信息框按钮*/\
UpDown,/*调节器*/\
hCoroutine,/*协程调度器*/\
edbs_ex/*edbs*/\
CtCheckButtonW/*选择框*/\
CtCommandLink/*命令链接*/\

#pragma endregion

