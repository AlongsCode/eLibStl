#pragma region 命令添加到这
#define ALL_E_LIB_CMD /*头部不要添加东西，保持命令索引=行号-3*/ \
/*000*/ rnd_ex,/*取随机数Ex*/\
/*001*/ L,/*unicode_base*/\
/*002*/ fint_text_a,/*寻找文本A*/\
/*003*/ find_text_w,/*寻找文本W*/\
/*004*/ strlen_a,/*取文本长度A*/\
/*005*/ wcslen_w,/*取文本长度W*/\
/*006*/ ator,/*弧度到角度*/\
/*007*/ rtoa,/*角度到弧度*/\
/*008*/ prime,/*是否素数*/\
/*009*/ message_box_w,/*延迟信息框W*/\
/*010*/ read_file_a,/*读入文件A*/\
/*011*/ read_file_w,/*读入文件W*/\
/*012*/ write_file_a,/*写到文件A*/\
/*013*/ write_file_w,/*写到文件W*/\
/*014*/ task_dialog_w,/*高级信息框W*/\
/*015*/ set_clip_board_text_w,/*置剪辑板文本W*/\
/*016*/ get_clip_board_text_w,/*取剪辑板文本W*/\
/*017*/ to_upper_w,/*到大写W*/\
/*018*/ to_lower_w,/*到小写W*/\
/*019*/ to_full_w,/*到全角W*/\
/*020*/ to_half_w,/*到半角W*/\
/*021*/ in_str_rev_w,/*倒找文本W*/\
/*022*/ Fn_split_w,/*分割文本W*/\
/*023*/ get_character_w,/*字符W*/\
/*024*/ get_char_code_w,/*取代码W*/\
/*025*/ ltrim_w,/*删收空W*/\
/*026*/ rtrim_w,/*删尾空W*/\
/*027*/ trim_w,/*删首尾空W*/\
/*028*/ trim_all_w,/*删全部空W*/\
/*029*/ left_text_t,/*取文本左边W*/\
/*030*/ right_text_w,/*取文本右边W*/\
/*031*/ mid_text_w,/*取文本中间W*/\
/*032*/ open_console,/*打开控制台*/\
/*033*/ set_console_title,/*置控制台标题W*/\
/*034*/ read_console_w,/*标准输入W*/\
/*035*/ cout_w,/*标准输出W*/\
/*036*/ get_console_locale,/*取控制台编码*/\
/*037*/ set_console_locale,/*置控制台编码*/\
/*038*/ get_net_work_types_w,/*枚举网络类型W*/\
/*039*/ Server_GetData,/*取回数据*/\
/*040*/ Server_GetCline,/*取回客户*/\
/*041*/ Server_CloseClient,/*断开客户*/\
/*042*/ Server_start,/*启动*/\
/*043*/ Server_close,/*关闭*/\
/*044*/ Server_is_open,/*是否已启动*/\
/*045*/ Server_Send,/*发送数据*/\
/*046*/ Clinet_connect,/*连接*/\
/*047*/ Clinet_close,/*关闭*/\
/*048*/ Clinet_GetData,/*取回数据*/\
/*049*/ Clinet_Send,/*发送数据*/\
/*050*/ Fn_EditAddText,/*编辑框.加入文本*/\
/*051*/ clear_folder_W,/*磁盘操作→清空目录*/\
/*052*/ create_dir_W,/*创建目录W*/\
/*053*/ remove_dir_W,/*删除目录W*/\
/*054*/ remove_file_W,/*删除文件W*/\
/*055*/ current_path_W,/*取运行目录W*/\
/*056*/ get_complete_path_W,/*取完整路径W*/\
/*057*/ normalization_path_W,/*规范化路径W*/\
/*058*/ get_exe_name_W,/*取执行文件名W*/\
/*059*/ get_cmdline_W,/*取命令行W*/\
/*060*/ get_env_W,/*读环境变量W*/\
/*061*/ set_env_W,/*写环境变量W*/\
/*062*/ get_special_folder_path_W,/*取特定目录W*/\
/*063*/ prevent_duplicate_execution_W,/*禁止程序重复运行W*/\
/*064*/ atomic_increment,/*原子递增*/\
/*065*/ atomic_exchange,/*原子赋值*/\
/*066*/ atomic_decrement,/*原子递减*/\
/*067*/ atomic_addition,/*原子运算*/\
/*068*/ create_coroutine,/*创建协程*/\
/*069*/ switch_coroutine,/*切换协程*/\
/*070*/ is_valid_hCoprocess,/*协程句柄是否有效*/\
/*071*/ delete_coroutine,/*销毁协程*/\
/*072*/ get_h_coroutine,/*取当前函数所在协程*/\
/*073*/ free_console,/*分离控制台*/\
/*074*/ get_ip_this,/*取本机ip*/\
/*075*/ kill_process,/*结束进程*/\
/*076*/ is_64_bit,/*是否位64位系统*/\
/*077*/ Media_structure,/*媒体播放构造*/\
/*078*/ Media_copy,/*媒体播放复制*/\
/*079*/ Media_destruct,/*媒体播放析构*/\
/*080*/ Media_open,/*媒体播放打开*/\
/*081*/ Media_IsVideo,/*是否为视频*/\
/*082*/ Media_GetHwnd,/*取句柄*/\
/*083*/ Media_SetHwnd,/*置句柄*/\
/*084*/ Media_GetMode,/*取状态*/\
/*085*/ Media_GetLength,/*取长度*/\
/*086*/ Media_GetPosition,/*取位置*/\
/*087*/ Media_GetTotalSec,/*取总时间*/\
/*088*/ Media_GetFrameRate,/*取比率*/\
/*089*/ Media_Play,/*播放*/\
/*090*/ Media_Pause,/*暂停*/\
/*091*/ Media_Stop,/*停止*/\
/*092*/ Media_GetMCIAlias,/*取别名*/\
/*093*/ Media_Close,/*关闭*/\
/*094*/ Media_SetVolume,/*置音量*/\
/*095*/ Media_GetVolume,/*取音量*/\
/*096*/ Media_continue,/*继续*/\
/*097*/ Media_GetChannel,/*取媒体声道*/\
/*098*/ Media_SetChannel,/*置媒体声道*/\
/*099*/ Media_GetFrames,/*取帧数*/\
/*100*/ Media_GetMediaVolume,/*取媒体音量*/\
/*101*/ Media_SetMediaVolume,/*置媒体音量*/\
/*102*/ Media_SetPlaySpeed,/*置播放速度*/\
/*103*/ Media_GetPlaySpeed,/*取播放速度*/\
/*104*/ Media_SetPos,/*置位置*/\
/*105*/ Media_SetFrame,/*跳到指定帧*/\
/*106*/ Media_IsOpen,/*是否已打开*/\
/*107*/ is_connect_to_internet,/*是否已联网*/\
/*108*/ check_port,/*端口是否可用*/\
/*109*/ send_net_msg,/*发送网络消息*/\
/*110*/ Fn_EditCharFromPos,/*编辑框.取坐标处字符*/\
/*111*/ e_coroutine_close,/*释放协程调度器*/\
/*112*/ e_coroutine_open,/*创建协程调度器*/\
/*113*/ e_hCoi2h,/*指针到调度器*/\
/*114*/ analog_press,/*模拟按下*/\
/*115*/ analog_up,/*模拟弹起*/\
/*116*/ replace_substring_w,/*取CPU当前使用率*/\
/*117*/ get_cpu_id,/*获取CPU序列号*/\
/*118*/ network_post/*网页访问*/\
/*119*/ ,capitalize_first_letter/*首字母大写*/\
/*120*/ ,Fn_BtnGetIdealSize/*按钮.取理想尺寸*/\
/*121*/ ,Fn_UpDownSetAccel/*调节器.置加速度*/\
/*122*/ ,e_debugput/*调试*/\
/*123*/ ,e_CallEfun/*执行函数*/\
/*124*/ ,_e_delay/*延迟Ex*/\
/*125*/ ,e_GetTickCount_ex/*取启动时间Ex*/\
/*126*/ ,e_eLibCallEfun/*调用易库函数*/\
/*127*/ ,e_Open_File_Dialog_A/*文件选择夹*/\
/*128*/ ,e_Open_File_Dialog_W/*文件选择夹W*/\
/*129*/ ,e_BrowseForFolder_W/*文件浏览夹W*/\
/*130*/ ,e_BrowseForFolder_A/*文件浏览夹*/\
/*131*/ ,e_lib_CreateEbds/*文件浏览夹*/\
/*132*/ ,edbs_ex_structure/*EDBS构造*/\
/*133*/ ,edbs_ex_copy/*EDB复制*/\
/*134*/ ,edbs_ex_destruct/*析构*/\
/*135*/ ,edbs_ex_open/*打开*/\
/*136*/ ,edbs_get_row_num/*取记录数*/\
/*137*/ ,edbs_ex_addpendnop/*加空记录*/\
/*138*/ ,edbs_set_current/*跳到*/\
/*139*/ ,edbs_read/*读*/\
/*140*/ ,edbs_write/*写*/\
/*141*/ ,edbs_close/*关闭*/\
/*142*/ ,edbs_next/*EDB.下一行*/\
/*143*/ ,edbs_previous/*EDB.上一行*/\
/*144*/ ,edbs_clean/*EDB.清空*/\
/*145*/ ,edbs_begin/*EDB.开启事务*/\
/*146*/ ,edbs_commit/*EDB.提交事务*/\
/*147*/ ,edbs_get_current/*EDB.当前行*/\
/*148*/ ,edbs_get_column_name/*EDB.字段名*/\
/*149*/ ,edbs_get_column_num/*EDB.字段数*/\
/*150*/ ,edbs_set_column_name/*EDB.置字段名*/\
/*151*/ ,Fn_EditCanUndo/*编辑框.是否可撤销*/\
/*152*/ ,Fn_EditEmptyUndoBuf/*编辑框.清空撤销队列*/\
/*153*/ ,Fn_EditGetFirstLine/*编辑框.取第一可见行*/\
/*154*/ ,Fn_EditGetLineCount/*编辑框.取行数*/\
/*155*/ ,Fn_EditGetModify/*编辑框.取修改标志*/\
/*156*/ ,Fn_EditHideBallloonTip/*编辑框.隐藏气球提示*/\
/*157*/ ,Fn_EditLineLength/*编辑框.取某行长度*/\
/*158*/ ,Fn_EditGetLine/*编辑框.取行文本*/\
/*159*/ ,Fn_EditGetMargins/*编辑框.取边距*/\
/*160*/ ,Fn_EditGetRect/*编辑框.取显示矩形*/\
/*161*/ ,Fn_EditLineFromChar/*编辑框.字符位置到行数*/\
/*162*/ ,Fn_EditLineIndex/*编辑框.取某行第一字符位置*/\
/*163*/ ,Fn_EditScroll/*编辑框.滚动*/\
/*164*/ ,Fn_EditLineScroll/*编辑框.滚动行*/\
/*165*/ ,Fn_EditPosFromChar/*编辑框.取字符坐标*/\
/*166*/ ,Fn_EditReplaceSel/*编辑框.替换选中文本*/\
/*167*/ ,Fn_EditSetMargins/*编辑框.置边距*/\
/*168*/ ,Fn_EditSetModify/*编辑框.置修改标志*/\
/*169*/ ,Fn_EditSetRect/*编辑框.置显示矩形*/\
/*170*/ ,Fn_EditSetTabStop/*编辑框.置制表位*/\
/*171*/ ,Fn_EditSetBallloonTip/*编辑框.弹出气球提示*/\
/*172*/ ,Fn_EditUndo/*编辑框.撤销*/\
/*173*/ ,Fn_EditPaste/*编辑框.粘贴*/\
/*174*/ ,Fn_EditCopy/*编辑框.复制*/\
/*175*/ ,Fn_EditSelAll/*编辑框.全选*/\
/*176*/ ,eto_wstring/*到文本W*/\
/*177*/ ,e_malloc/*内存申请*/\
/*178*/ ,e_free/*内存释放*/\
/*179*/ ,clearConsole/*清空控制台*/\
/*180*/ ,e_WriteMem/*写入内存*/\
/*181*/ ,Fn_UpDownGetAccel/*调节器.取加速度*/\
/*182*/ ,g_trim_leading_zeros/*删文本左侧无效零*/\
/*183*/ ,g_extract_shortest_matching_text/*取中间文本*/\
/*184*/ ,g_byte_array_to_string/*字节集到十进制文本A*/\
/*185*/ ,g_byte_array_to_wstring/*字节集到十进制文本W*/\
/*186*/ ,g_concatenate_wstrings/*拼接文本W*/\
/*187*/ ,g_is_inside_virtual_machine/*是否运行在虚拟机*/\
/*188*/ ,g_get_all_py/*取所有发音W*/\
/*189*/ ,g_get_py_count/*取发音数量W*/\
/*190*/ ,g_get_py/*取拼音W*/\
/*191*/ ,g_get_py_sm/*取声母W*/\
/*192*/ ,g_get_py_ym/*取韵母W*/\
/*193*/ ,Fn_SendLabelMsg/*调用标签反馈事件*/\
/*194*/ ,e_debugput_img/*调试图片*/\
/*195*/ ,e_debugput_w/*调试宽字符*/\
/*196*/ ,Fn_MenuConstructor/*菜单.构造*/\
/*197*/ ,Fn_MenuDestructor/*菜单.析构*/\
/*198*/ ,Fn_MenuCopy/*菜单.复制*/\
/*199*/ ,Fn_MenuAttach/*菜单.依附句柄*/\
/*200*/ ,Fn_MenuInsertItem/*菜单.插入项目*/\
/*201*/ ,Fn_MenuDetach/*菜单.拆离句柄*/\
/*202*/ ,Fn_MenuSetDelFlag/*菜单.置回收标志*/\
/*203*/ ,Fn_MenuCreatePopupMenu/*菜单.创建弹出式菜单*/\
/*204*/ ,Fn_MenuGetCurrentMenu/*菜单.取当前菜单*/\
/*205*/ ,Fn_MenuDeleteItem/*菜单.删除项目*/\
/*206*/ ,Fn_MenuGetCount/*菜单.取项目数*/\
/*207*/ ,Fn_MenuGetCaption/*菜单.取标题*/\
/*208*/ ,Fn_MenuSetCheck/*菜单.置选中状态*/\
/*209*/ ,Fn_MenuGetCheck/*菜单.取选中状态*/\
/*210*/ ,Fn_MenuSetRadioCheck/*菜单.置单选状态*/\
/*211*/ ,Fn_MenuGetRadioCheck/*菜单.取单选状态*/\
/*212*/ ,Fn_MenuSetDefault/*菜单.置默认状态*/\
/*213*/ ,Fn_MenuGetDefault/*菜单.取默认状态*/\
/*214*/ ,Fn_MenuSetDisable/*菜单.置禁止状态*/\
/*215*/ ,Fn_MenuGetDisable/*菜单.取禁止状态*/\
/*216*/ ,Fn_MenuSetHilite/*菜单.置高亮状态*/\
/*217*/ ,Fn_MenuGetHilite/*菜单.取高亮状态*/\
/*218*/ ,Fn_MenuTrackPopupMenu/*菜单.弹出跟踪式菜单*/\
/*219*/ ,Fn_MenuSetCaption/*菜单.置标题*/\
/*220*/ ,Fn_MenuCreateMenu/*菜单.创建水平菜单*/\
/*221*/ ,Fn_MenuSetMenu/*菜单.置窗口菜单*/\
/*222*/ ,Fn_MenuGetMenu/*菜单.取窗口菜单*/\
/*223*/ ,Fn_MenuReset/*菜单.重置*/\
/*224*/ ,Fn_MenuSetEventReceiver/*菜单.置事件接收器*/\
/*225*/ ,Fn_InputBox/*输入框*/\
/*226*/ ,Fn_memfile_structure/*内存文件.构造*/\
/*227*/ ,Fn_memfile_copy/*内存文件.复制*/\
/*228*/ ,Fn_memfile_destruct/*内存文件.析构*/\
/*229*/ ,Fn_memfile_get_size/*内存文件.取长度*/\
/*230*/ ,Fn_memfile_seek_begin/*内存文件.移到文件首*/\
/*231*/ ,Fn_memfile_seek_end/*内存文件.移到文件尾*/\
/*232*/ ,Fn_memfile_write/*内存文件.写*/\
/*233*/ ,Fn_memfile_read/*内存文件.读*/\
/*234*/ ,Fn_memfile_write_mem/*内存文件.写入字节集*/\
/*235*/ ,Fn_memfile_seek/*内存文件.移动读写位置*/\
/*236*/ ,Fn_memfile_get_off_set/*内存文件.取读写位置*/\
/*237*/ ,Fn_ListBoxWAddString/*列表框.加入表项*/\
/*238*/ ,Fn_ListBoxWInsertString/*列表框.插入表项*/\
/*239*/ ,Fn_ListBoxWDelString/*列表框.删除表项*/\
/*240*/ ,Fn_ListBoxWGetItemCount/*列表框.取表项数*/\
/*241*/ ,Fn_ListBoxWGetTopIndex/*列表框.取第一可见项*/\
/*242*/ ,Fn_ListBoxWSetTopIndex/*列表框.置第一可见项*/\
/*243*/ ,Fn_ListBoxWGetItemlParam/*列表框.取表项数值*/\
/*244*/ ,Fn_ListBoxWSetItemlParam/*列表框.置表项数值*/\
/*245*/ ,Fn_ListBoxWGetItemString/*列表框.取表项文本*/\
/*246*/ ,Fn_ListBoxWSetItemString/*列表框.置表项文本*/\
/*247*/ ,Fn_ListBoxWGetSelectedItemCount/*列表框.取选中表项数*/\
/*248*/ ,Fn_ListBoxWGetSelectedItem/*列表框.取选中表项*/\
/*249*/ ,Fn_ListBoxWIsItemSelected/*列表框.表项是否选中*/\
/*250*/ ,Fn_ListBoxWGetItemCheckState/*列表框.取表项检查状态*/\
/*251*/ ,Fn_ListBoxWSetItemCheckState/*列表框.置表项检查状态*/\
/*252*/ ,Fn_ListBoxWSelectItem/*列表框.选中表项*/\
/*253*/ ,Fn_ListBoxWFindString/*列表框.寻找表项*/\
/*254*/ ,Fn_ListBoxWGetItemColor/*列表框.取表项颜色*/\
/*255*/ ,Fn_ListBoxWSetItemColor/*列表框.置表项颜色*/\
/*256*/ ,Fn_ListBoxWGetItemTip/*列表框.取表项提示文本*/\
/*257*/ ,Fn_ListBoxWSetItemTip/*列表框.置表项提示文本*/\
/*258*/ ,Fn_ListBoxWGetItemImageIndex/*列表框.取表项图片索引*/\
/*259*/ ,Fn_ListBoxWSetItemImageIndex/*列表框.置表项图片索引*/\
/*260*/ ,Fn_ListBoxWInitStorage/*列表框.保留内存*/\
/*261*/ ,Fn_ListBoxWGetImageList/*列表框.取图像列表句柄*/\
/*262*/ ,Fn_ListBoxWSetImageList/*列表框.置图像列表句柄*/\
/*263*/ ,Fn_ListBoxWGetItemRect/*列表框.取表项矩形*/\
/*264*/ ,Fn_ListBoxWHitTest/*列表框.命中测试*/\
/*265*/ ,Fn_ListBoxWGetItemStringLength/*列表框.取表项文本长度*/\
/*266*/ ,Fn_ListBoxWSort/*列表框.排序*/\
/*267*/ ,Fn_ListBoxWSort2/*列表框.自定义排序*/\
/*268*/ ,Fn_ListBoxWSwapItem/*列表框.交换表项*/\
/*269*/ ,Fn_ListBoxWMoveItem/*列表框.移动表项*/\
/*270*/ ,Fn_DirBoxGetCurrentItem/*目录框.取当前选中表项*/\
/*271*/ ,Fn_DirBoxExtend/*目录框.展开到*/\
/*272*/ ,Fn_DirBoxGetCheckedItems/*目录框.取所有检查项目*/\
/*273*/ ,Fn_DirBoxRefresh/*目录框.刷新*/\
/*274*/ ,e_memcpy/*内存复制*/\
/*275*/ ,Fn_EditCut/*编辑框.剪切*/\
/*276*/ ,Fn_ComboBoxWInsertString/*组合框.插入项目*/\
/*277*/ ,Fn_ComboBoxWDelString/*组合框.删除项目*/\
/*278*/ ,Fn_ComboBoxWGetItemCount/*组合框.取项目数*/\
/*279*/ ,Fn_ComboBoxWGetTopIndex/*组合框.取第一可见项*/\
/*280*/ ,Fn_ComboBoxWSetTopIndex/*组合框.置第一可见项*/\
/*281*/ ,Fn_ComboBoxWGetItemlParam/*组合框.取项目数值*/\
/*282*/ ,Fn_ComboBoxWSetItemlParam/*组合框.置项目数值*/\
/*283*/ ,Fn_ComboBoxWGetItemString/*组合框.取项目文本*/\
/*284*/ ,Fn_ComboBoxWSetItemString/*组合框.置项目文本*/\
/*285*/ ,Fn_ComboBoxWFindString/*组合框.寻找项目*/\
/*286*/ ,Fn_ComboBoxWGetItemColor/*组合框.取项目颜色*/\
/*287*/ ,Fn_ComboBoxWSetItemColor/*组合框.置项目颜色*/\
/*288*/ ,Fn_ComboBoxWGetItemImageIndex/*组合框.取项目图片索引*/\
/*289*/ ,Fn_ComboBoxWSetItemImageIndex/*组合框.置项目图片索引*/\
/*290*/ ,Fn_ComboBoxWInitStorage/*组合框.保留内存*/\
/*291*/ ,Fn_ComboBoxWGetImageList/*组合框.取图像列表句柄*/\
/*292*/ ,Fn_ComboBoxWSetImageList/*组合框.置图像列表句柄*/\
/*293*/ ,Fn_ComboBoxWGetItemStringLength/*组合框.取项目文本长度*/\
/*294*/ ,Fn_ComboBoxWSort/*组合框.排序*/\
/*295*/ ,Fn_ComboBoxWSort2/*组合框.自定义排序*/\
/*296*/ ,Fn_ComboBoxWSwapItem/*组合框.交换表项*/\
/*297*/ ,Fn_ComboBoxWMoveItem/*组合框.移动表项*/\
/*298*/ ,Fn_ListBoxWGetItemDisableState/*列表框.取表项禁止状态*/\
/*299*/ ,Fn_ListBoxWSetItemDisableState/*列表框.置表项禁止状态*/\
/*300*/ ,edbs_del/*易数据库.删除*/\
/*301*/ ,edbs_pop/*易数据库.彻底删除*/\
/*302*/ ,edbs_cancel_del/*易数据库.取消删除*/\
/*303*/ ,e_load_windows/*载入窗口*/\
/*304*/ ,EplVar_structure/*变量.构造*/\
/*305*/ ,EplVar_copy/*变量.复制*/\
/*306*/ ,EplVar_destruct/*变量.析构*/\
/*307*/ ,Fn_Var_Set/*变量.置*/\
/*308*/ ,Fn_Var_Get/*变量.取*/\
/*309*/ ,Fn_Var_Type/*变量.类型*/\
/*310*/ ,Fn_Var_Size/*变量.长度*/\
/*311*/ ,Fn_Var_TypeName/*变量.类型名*/\
/*312*/ ,Fn_Var_Data/*变量.指针*/\
/*313*/ ,Fn_Var_ToBin/*变量.到字节集*/\
/*314*/ ,Fn_Ceil/*向上取整*/\
/*315*/ ,Fn_Floor/*向下取整*/\
/*316*/ ,Fn_GetVarPtr/*取变量指针*/\
/*317*/ ,Fn_GetVarDataPtr/*取变量数据指针*/\
/*318*/ ,Fn_CFile_structure/*文件读写.构造*/\
/*319*/ ,Fn_CFile_copy/*文件读写.复制*/\
/*320*/ ,Fn_CFile_destruct/*文件读写.拷贝*/\
/*321*/ ,Fn_CFile_Open/*文件读写.打开*/\
/*322*/ ,Fn_CFile_Close/*文件读写.关闭*/\
/*323*/ ,Fn_CFile_Lock/*文件读写.锁住*/\
/*324*/ ,Fn_CFile_UnLock/*文件读写.解锁*/\
/*325*/ ,Fn_hexview_setdata/*进制框.置数据*/\
/*326*/ ,Fn_CFile_FSeek/*文件读写.移动读写位置*/\
/*327*/ ,Fn_CFile_SeekToBegin/*文件读写.移到文件首*/\
/*328*/ ,Fn_CFile_SeekToEnd/*文件读写.移到文件尾*/\
/*329*/ ,Fn_CFile_ReadBin/*文件读写.读入字节集*/\
/*330*/ ,Fn_CFile_ReadBin/*文件读写.写出字节集*/\
/*331*/ ,Fn_CFile_ReadText/*文件读写.读入文本W*/\
/*332*/ ,Fn_CFile_WriteText/*文件读写.写出文本W*/\
/*333*/ ,Fn_CFile_ReadLine/*文件读写.读入一行*/\
/*334*/ ,Fn_CFile_WriteLine/*文件读写.写出一行*/\
/*335*/ ,Fn_CFile_isOpen/*文件读写.是否已打开*/\
/*336*/ ,Fn_CFile_GetCurrent/*文件读写.取当前读写位置*/\
/*337*/ ,Fn_CFile_GetSize/*文件读写.取文件大小*/\
/*338*/ ,Fn_CFile_RemoveData/*文件读写.删除数据*/\
/*339*/ ,Fn_CFile_InsertStr/*文件读写.插入文本*/\
/*340*/ ,Fn_comp_py_code/*输入字比较W*/\
/*341*/ ,Fn_comp_py/*发音比较W*/\
/*342*/ ,Fn_get_str_py/*取文本拼音W*/\
/*343*/ ,Fn_is_matching_brackets/*括号否匹配*/\
/*344*/ ,Fn_throw_ception/*抛出异常*/\
/*345*/ ,Fn_catch_ception/*注册异常函数*/\
/*346*/ , Fn_process_messages_improved/*取CPU核心数*/\
/*347*/ ,Fn_get_win_pic/*截图*/\
/*348*/ ,Fn_get_pixel/*取坐标颜色*/\
/*349*/ , Fn_QRcode_encodeString/*生成文本二维码*/\
/*350*/ ,Fn_QRcode_encodeData/*生成数据二维码*/\
/*351*/ ,Fn_MemoryModule_structure/*构造*/\
/*352*/ ,Fn_MemoryModule_copy/*复制*/\
/*353*/ ,Fn_MemoryModule_destruct/*析构*/\
/*354*/ ,Fn_MemoryModule_LoadLibrary/*载入*/\
/*355*/ ,Fn_MemoryModule_GetProcAddress/*取函数地址*/\
/*356*/ ,Fn_MemoryModule_CallEntryPoint/*运行*/\


#pragma endregion





#pragma region 对象添加到这
#define ALL_E_LIB_CLASS \
CtButtonW,/*按钮W*/\
CtEdit,/*编辑框W*/\
severex,/*服务器Ex*/\
clinetex,/*客户端Ex*/\
hCoprocessD,/*协程句柄*/\
media_play_ex,/*媒体播放*/\
TaskDialog_Button_Type,/*高级信息框按钮*/\
UpDown,/*调节器*/\
hCoroutine,/*协程调度器*/\
edbs_ex,/*edbs*/\
CtCheckButtonW,/*选择框*/\
CtCommandLink/*命令链接*/\
,CtLabelW/*标签W*/\
,ClMenu/*菜单*/\
,CtListBoxW/*列表框*/\
,Obj_EMemFile/*内存文件*/\
/*,CtScintilla无法通过静态编译，暂时移除*/\
,CtDirBoxW/*目录框*/\
,CtRichEdit/*富文本框*/\
,CtComboBox/**/\
,epl_class_Var/*强类型动态数组*/\
,Obj_DiskFile/*文件读写类*/\
,Enum_CoRuningType/*协程运行状态*/\
,HexView_control/*进制框*/\
,Obj_MemoryModule/*内存模块类*/

#pragma endregion





#pragma region 插件添加到这
#define ALL_E_LIB_PLUG \
Plug_UnicodeBase/*unicode预编译*/

#pragma endregion