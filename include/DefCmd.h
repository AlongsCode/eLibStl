#pragma region ������ӵ���
#define ALL_E_LIB_CMD /*ͷ����Ҫ��Ӷ�����������������=�к�-3*/ \
/*000*/ rnd_ex,/*ȡ�����Ex*/\
/*001*/ L,/*unicode_base*/\
/*002*/ fint_text_a,/*Ѱ���ı�A*/\
/*003*/ find_text_w,/*Ѱ���ı�W*/\
/*004*/ strlen_a,/*ȡ�ı�����A*/\
/*005*/ wcslen_w,/*ȡ�ı�����W*/\
/*006*/ ator,/*���ȵ��Ƕ�*/\
/*007*/ rtoa,/*�Ƕȵ�����*/\
/*008*/ prime,/*�Ƿ�����*/\
/*009*/ message_box_w,/*�ӳ���Ϣ��W*/\
/*010*/ read_file_a,/*�����ļ�A*/\
/*011*/ read_file_w,/*�����ļ�W*/\
/*012*/ write_file_a,/*д���ļ�A*/\
/*013*/ write_file_w,/*д���ļ�W*/\
/*014*/ task_dialog_w,/*�߼���Ϣ��W*/\
/*015*/ set_clip_board_text_w,/*�ü������ı�W*/\
/*016*/ get_clip_board_text_w,/*ȡ�������ı�W*/\
/*017*/ to_upper_w,/*����дW*/\
/*018*/ to_lower_w,/*��СдW*/\
/*019*/ to_full_w,/*��ȫ��W*/\
/*020*/ to_half_w,/*�����W*/\
/*021*/ in_str_rev_w,/*�����ı�W*/\
/*022*/ Fn_split_w,/*�ָ��ı�W*/\
/*023*/ get_character_w,/*�ַ�W*/\
/*024*/ get_char_code_w,/*ȡ����W*/\
/*025*/ ltrim_w,/*ɾ�տ�W*/\
/*026*/ rtrim_w,/*ɾβ��W*/\
/*027*/ trim_w,/*ɾ��β��W*/\
/*028*/ trim_all_w,/*ɾȫ����W*/\
/*029*/ left_text_t,/*ȡ�ı����W*/\
/*030*/ right_text_w,/*ȡ�ı��ұ�W*/\
/*031*/ mid_text_w,/*ȡ�ı��м�W*/\
/*032*/ open_console,/*�򿪿���̨*/\
/*033*/ set_console_title,/*�ÿ���̨����W*/\
/*034*/ read_console_w,/*��׼����W*/\
/*035*/ cout_w,/*��׼���W*/\
/*036*/ get_console_locale,/*ȡ����̨����*/\
/*037*/ set_console_locale,/*�ÿ���̨����*/\
/*038*/ get_net_work_types_w,/*ö����������W*/\
/*039*/ Server_GetData,/*ȡ������*/\
/*040*/ Server_GetCline,/*ȡ�ؿͻ�*/\
/*041*/ Server_CloseClient,/*�Ͽ��ͻ�*/\
/*042*/ Server_start,/*����*/\
/*043*/ Server_close,/*�ر�*/\
/*044*/ Server_is_open,/*�Ƿ�������*/\
/*045*/ Server_Send,/*��������*/\
/*046*/ Clinet_connect,/*����*/\
/*047*/ Clinet_close,/*�ر�*/\
/*048*/ Clinet_GetData,/*ȡ������*/\
/*049*/ Clinet_Send,/*��������*/\
/*050*/ Fn_EditAddText,/*�༭��.�����ı�*/\
/*051*/ clear_folder_W,/*���̲��������Ŀ¼*/\
/*052*/ create_dir_W,/*����Ŀ¼W*/\
/*053*/ remove_dir_W,/*ɾ��Ŀ¼W*/\
/*054*/ remove_file_W,/*ɾ���ļ�W*/\
/*055*/ current_path_W,/*ȡ����Ŀ¼W*/\
/*056*/ get_complete_path_W,/*ȡ����·��W*/\
/*057*/ normalization_path_W,/*�淶��·��W*/\
/*058*/ get_exe_name_W,/*ȡִ���ļ���W*/\
/*059*/ get_cmdline_W,/*ȡ������W*/\
/*060*/ get_env_W,/*����������W*/\
/*061*/ set_env_W,/*д��������W*/\
/*062*/ get_special_folder_path_W,/*ȡ�ض�Ŀ¼W*/\
/*063*/ prevent_duplicate_execution_W,/*��ֹ�����ظ�����W*/\
/*064*/ atomic_increment,/*ԭ�ӵ���*/\
/*065*/ atomic_exchange,/*ԭ�Ӹ�ֵ*/\
/*066*/ atomic_decrement,/*ԭ�ӵݼ�*/\
/*067*/ atomic_addition,/*ԭ������*/\
/*068*/ create_coroutine,/*����Э��*/\
/*069*/ switch_coroutine,/*�л�Э��*/\
/*070*/ is_valid_hCoprocess,/*Э�̾���Ƿ���Ч*/\
/*071*/ delete_coroutine,/*����Э��*/\
/*072*/ get_h_coroutine,/*ȡ��ǰ��������Э��*/\
/*073*/ free_console,/*�������̨*/\
/*074*/ get_ip_this,/*ȡ����ip*/\
/*075*/ kill_process,/*��������*/\
/*076*/ is_64_bit,/*�Ƿ�λ64λϵͳ*/\
/*077*/ Media_structure,/*ý�岥�Ź���*/\
/*078*/ Media_copy,/*ý�岥�Ÿ���*/\
/*079*/ Media_destruct,/*ý�岥������*/\
/*080*/ Media_open,/*ý�岥�Ŵ�*/\
/*081*/ Media_IsVideo,/*�Ƿ�Ϊ��Ƶ*/\
/*082*/ Media_GetHwnd,/*ȡ���*/\
/*083*/ Media_SetHwnd,/*�þ��*/\
/*084*/ Media_GetMode,/*ȡ״̬*/\
/*085*/ Media_GetLength,/*ȡ����*/\
/*086*/ Media_GetPosition,/*ȡλ��*/\
/*087*/ Media_GetTotalSec,/*ȡ��ʱ��*/\
/*088*/ Media_GetFrameRate,/*ȡ����*/\
/*089*/ Media_Play,/*����*/\
/*090*/ Media_Pause,/*��ͣ*/\
/*091*/ Media_Stop,/*ֹͣ*/\
/*092*/ Media_GetMCIAlias,/*ȡ����*/\
/*093*/ Media_Close,/*�ر�*/\
/*094*/ Media_SetVolume,/*������*/\
/*095*/ Media_GetVolume,/*ȡ����*/\
/*096*/ Media_continue,/*����*/\
/*097*/ Media_GetChannel,/*ȡý������*/\
/*098*/ Media_SetChannel,/*��ý������*/\
/*099*/ Media_GetFrames,/*ȡ֡��*/\
/*100*/ Media_GetMediaVolume,/*ȡý������*/\
/*101*/ Media_SetMediaVolume,/*��ý������*/\
/*102*/ Media_SetPlaySpeed,/*�ò����ٶ�*/\
/*103*/ Media_GetPlaySpeed,/*ȡ�����ٶ�*/\
/*104*/ Media_SetPos,/*��λ��*/\
/*105*/ Media_SetFrame,/*����ָ��֡*/\
/*106*/ Media_IsOpen,/*�Ƿ��Ѵ�*/\
/*107*/ is_connect_to_internet,/*�Ƿ�������*/\
/*108*/ check_port,/*�˿��Ƿ����*/\
/*109*/ send_net_msg,/*����������Ϣ*/\
/*110*/ Fn_EditCharFromPos,/*�༭��.ȡ���괦�ַ�*/\
/*111*/ e_coroutine_close,/*�ͷ�Э�̵�����*/\
/*112*/ e_coroutine_open,/*����Э�̵�����*/\
/*113*/ e_hCoi2h,/*ָ�뵽������*/\
/*114*/ analog_press,/*ģ�ⰴ��*/\
/*115*/ analog_up,/*ģ�ⵯ��*/\
/*116*/ replace_substring_w,/*ȡCPU��ǰʹ����*/\
/*117*/ get_cpu_id,/*��ȡCPU���к�*/\
/*118*/ network_post/*��ҳ����*/\
/*119*/ ,capitalize_first_letter/*����ĸ��д*/\
/*120*/ ,Fn_BtnGetIdealSize/*��ť.ȡ����ߴ�*/\
/*121*/ ,Fn_UpDownSetAccel/*������.�ü��ٶ�*/\
/*122*/ ,e_debugput/*����*/\
/*123*/ ,e_CallEfun/*ִ�к���*/\
/*124*/ ,_e_delay/*�ӳ�Ex*/\
/*125*/ ,e_GetTickCount_ex/*ȡ����ʱ��Ex*/\
/*126*/ ,e_eLibCallEfun/*�����׿⺯��*/\
/*127*/ ,e_Open_File_Dialog_A/*�ļ�ѡ���*/\
/*128*/ ,e_Open_File_Dialog_W/*�ļ�ѡ���W*/\
/*129*/ ,e_BrowseForFolder_W/*�ļ������W*/\
/*130*/ ,e_BrowseForFolder_A/*�ļ������*/\
/*131*/ ,e_lib_CreateEbds/*�ļ������*/\
/*132*/ ,edbs_ex_structure/*EDBS����*/\
/*133*/ ,edbs_ex_copy/*EDB����*/\
/*134*/ ,edbs_ex_destruct/*����*/\
/*135*/ ,edbs_ex_open/*��*/\
/*136*/ ,edbs_get_row_num/*ȡ��¼��*/\
/*137*/ ,edbs_ex_addpendnop/*�ӿռ�¼*/\
/*138*/ ,edbs_set_current/*����*/\
/*139*/ ,edbs_read/*��*/\
/*140*/ ,edbs_write/*д*/\
/*141*/ ,edbs_close/*�ر�*/\
/*142*/ ,edbs_next/*EDB.��һ��*/\
/*143*/ ,edbs_previous/*EDB.��һ��*/\
/*144*/ ,edbs_clean/*EDB.���*/\
/*145*/ ,edbs_begin/*EDB.��������*/\
/*146*/ ,edbs_commit/*EDB.�ύ����*/\
/*147*/ ,edbs_get_current/*EDB.��ǰ��*/\
/*148*/ ,edbs_get_column_name/*EDB.�ֶ���*/\
/*149*/ ,edbs_get_column_num/*EDB.�ֶ���*/\
/*150*/ ,edbs_set_column_name/*EDB.���ֶ���*/\
/*151*/ ,Fn_EditCanUndo/*�༭��.�Ƿ�ɳ���*/\
/*152*/ ,Fn_EditEmptyUndoBuf/*�༭��.��ճ�������*/\
/*153*/ ,Fn_EditGetFirstLine/*�༭��.ȡ��һ�ɼ���*/\
/*154*/ ,Fn_EditGetLineCount/*�༭��.ȡ����*/\
/*155*/ ,Fn_EditGetModify/*�༭��.ȡ�޸ı�־*/\
/*156*/ ,Fn_EditHideBallloonTip/*�༭��.����������ʾ*/\
/*157*/ ,Fn_EditLineLength/*�༭��.ȡĳ�г���*/\
/*158*/ ,Fn_EditGetLine/*�༭��.ȡ���ı�*/\
/*159*/ ,Fn_EditGetMargins/*�༭��.ȡ�߾�*/\
/*160*/ ,Fn_EditGetRect/*�༭��.ȡ��ʾ����*/\
/*161*/ ,Fn_EditLineFromChar/*�༭��.�ַ�λ�õ�����*/\
/*162*/ ,Fn_EditLineIndex/*�༭��.ȡĳ�е�һ�ַ�λ��*/\
/*163*/ ,Fn_EditScroll/*�༭��.����*/\
/*164*/ ,Fn_EditLineScroll/*�༭��.������*/\
/*165*/ ,Fn_EditPosFromChar/*�༭��.ȡ�ַ�����*/\
/*166*/ ,Fn_EditReplaceSel/*�༭��.�滻ѡ���ı�*/\
/*167*/ ,Fn_EditSetMargins/*�༭��.�ñ߾�*/\
/*168*/ ,Fn_EditSetModify/*�༭��.���޸ı�־*/\
/*169*/ ,Fn_EditSetRect/*�༭��.����ʾ����*/\
/*170*/ ,Fn_EditSetTabStop/*�༭��.���Ʊ�λ*/\
/*171*/ ,Fn_EditSetBallloonTip/*�༭��.����������ʾ*/\
/*172*/ ,Fn_EditUndo/*�༭��.����*/\
/*173*/ ,Fn_EditPaste/*�༭��.ճ��*/\
/*174*/ ,Fn_EditCopy/*�༭��.����*/\
/*175*/ ,Fn_EditSelAll/*�༭��.ȫѡ*/\
/*176*/ ,eto_wstring/*���ı�W*/\
/*177*/ ,e_malloc/*�ڴ�����*/\
/*178*/ ,e_free/*�ڴ��ͷ�*/\
/*179*/ ,clearConsole/*��տ���̨*/\
/*180*/ ,e_WriteMem/*д���ڴ�*/\
/*181*/ ,Fn_UpDownGetAccel/*������.ȡ���ٶ�*/\
/*182*/ ,g_trim_leading_zeros/*ɾ�ı������Ч��*/\
/*183*/ ,g_extract_shortest_matching_text/*ȡ�м��ı�*/\
/*184*/ ,g_byte_array_to_string/*�ֽڼ���ʮ�����ı�A*/\
/*185*/ ,g_byte_array_to_wstring/*�ֽڼ���ʮ�����ı�W*/\
/*186*/ ,g_concatenate_wstrings/*ƴ���ı�W*/\
/*187*/ ,g_is_inside_virtual_machine/*�Ƿ������������*/\
/*188*/ ,g_get_all_py/*ȡ���з���W*/\
/*189*/ ,g_get_py_count/*ȡ��������W*/\
/*190*/ ,g_get_py/*ȡƴ��W*/\
/*191*/ ,g_get_py_sm/*ȡ��ĸW*/\
/*192*/ ,g_get_py_ym/*ȡ��ĸW*/\
/*193*/ ,Fn_SendLabelMsg/*���ñ�ǩ�����¼�*/\
/*194*/ ,e_debugput_img/*����ͼƬ*/\
/*195*/ ,e_debugput_w/*���Կ��ַ�*/\
/*196*/ ,Fn_MenuConstructor/*�˵�.����*/\
/*197*/ ,Fn_MenuDestructor/*�˵�.����*/\
/*198*/ ,Fn_MenuCopy/*�˵�.����*/\
/*199*/ ,Fn_MenuAttach/*�˵�.�������*/\
/*200*/ ,Fn_MenuInsertItem/*�˵�.������Ŀ*/\
/*201*/ ,Fn_MenuDetach/*�˵�.������*/\
/*202*/ ,Fn_MenuSetDelFlag/*�˵�.�û��ձ�־*/\
/*203*/ ,Fn_MenuCreatePopupMenu/*�˵�.��������ʽ�˵�*/\
/*204*/ ,Fn_MenuGetCurrentMenu/*�˵�.ȡ��ǰ�˵�*/\
/*205*/ ,Fn_MenuDeleteItem/*�˵�.ɾ����Ŀ*/\
/*206*/ ,Fn_MenuGetCount/*�˵�.ȡ��Ŀ��*/\
/*207*/ ,Fn_MenuGetCaption/*�˵�.ȡ����*/\
/*208*/ ,Fn_MenuSetCheck/*�˵�.��ѡ��״̬*/\
/*209*/ ,Fn_MenuGetCheck/*�˵�.ȡѡ��״̬*/\
/*210*/ ,Fn_MenuSetRadioCheck/*�˵�.�õ�ѡ״̬*/\
/*211*/ ,Fn_MenuGetRadioCheck/*�˵�.ȡ��ѡ״̬*/\
/*212*/ ,Fn_MenuSetDefault/*�˵�.��Ĭ��״̬*/\
/*213*/ ,Fn_MenuGetDefault/*�˵�.ȡĬ��״̬*/\
/*214*/ ,Fn_MenuSetDisable/*�˵�.�ý�ֹ״̬*/\
/*215*/ ,Fn_MenuGetDisable/*�˵�.ȡ��ֹ״̬*/\
/*216*/ ,Fn_MenuSetHilite/*�˵�.�ø���״̬*/\
/*217*/ ,Fn_MenuGetHilite/*�˵�.ȡ����״̬*/\
/*218*/ ,Fn_MenuTrackPopupMenu/*�˵�.��������ʽ�˵�*/\
/*219*/ ,Fn_MenuSetCaption/*�˵�.�ñ���*/\
/*220*/ ,Fn_MenuCreateMenu/*�˵�.����ˮƽ�˵�*/\
/*221*/ ,Fn_MenuSetMenu/*�˵�.�ô��ڲ˵�*/\
/*222*/ ,Fn_MenuGetMenu/*�˵�.ȡ���ڲ˵�*/\
/*223*/ ,Fn_MenuReset/*�˵�.����*/\
/*224*/ ,Fn_MenuSetEventReceiver/*�˵�.���¼�������*/\
/*225*/ ,Fn_InputBox/*�����*/\
/*226*/ ,Fn_memfile_structure/*�ڴ��ļ�.����*/\
/*227*/ ,Fn_memfile_copy/*�ڴ��ļ�.����*/\
/*228*/ ,Fn_memfile_destruct/*�ڴ��ļ�.����*/\
/*229*/ ,Fn_memfile_get_size/*�ڴ��ļ�.ȡ����*/\
/*230*/ ,Fn_memfile_seek_begin/*�ڴ��ļ�.�Ƶ��ļ���*/\
/*231*/ ,Fn_memfile_seek_end/*�ڴ��ļ�.�Ƶ��ļ�β*/\
/*232*/ ,Fn_memfile_write/*�ڴ��ļ�.д*/\
/*233*/ ,Fn_memfile_read/*�ڴ��ļ�.��*/\
/*234*/ ,Fn_memfile_write_mem/*�ڴ��ļ�.д���ֽڼ�*/\
/*235*/ ,Fn_memfile_seek/*�ڴ��ļ�.�ƶ���дλ��*/\
/*236*/ ,Fn_memfile_get_off_set/*�ڴ��ļ�.ȡ��дλ��*/\
/*237*/ ,Fn_ListBoxWAddString/*�б��.�������*/\
/*238*/ ,Fn_ListBoxWInsertString/*�б��.�������*/\
/*239*/ ,Fn_ListBoxWDelString/*�б��.ɾ������*/\
/*240*/ ,Fn_ListBoxWGetItemCount/*�б��.ȡ������*/\
/*241*/ ,Fn_ListBoxWGetTopIndex/*�б��.ȡ��һ�ɼ���*/\
/*242*/ ,Fn_ListBoxWSetTopIndex/*�б��.�õ�һ�ɼ���*/\
/*243*/ ,Fn_ListBoxWGetItemlParam/*�б��.ȡ������ֵ*/\
/*244*/ ,Fn_ListBoxWSetItemlParam/*�б��.�ñ�����ֵ*/\
/*245*/ ,Fn_ListBoxWGetItemString/*�б��.ȡ�����ı�*/\
/*246*/ ,Fn_ListBoxWSetItemString/*�б��.�ñ����ı�*/\
/*247*/ ,Fn_ListBoxWGetSelectedItemCount/*�б��.ȡѡ�б�����*/\
/*248*/ ,Fn_ListBoxWGetSelectedItem/*�б��.ȡѡ�б���*/\
/*249*/ ,Fn_ListBoxWIsItemSelected/*�б��.�����Ƿ�ѡ��*/\
/*250*/ ,Fn_ListBoxWGetItemCheckState/*�б��.ȡ������״̬*/\
/*251*/ ,Fn_ListBoxWSetItemCheckState/*�б��.�ñ�����״̬*/\
/*252*/ ,Fn_ListBoxWSelectItem/*�б��.ѡ�б���*/\
/*253*/ ,Fn_ListBoxWFindString/*�б��.Ѱ�ұ���*/\
/*254*/ ,Fn_ListBoxWGetItemColor/*�б��.ȡ������ɫ*/\
/*255*/ ,Fn_ListBoxWSetItemColor/*�б��.�ñ�����ɫ*/\
/*256*/ ,Fn_ListBoxWGetItemTip/*�б��.ȡ������ʾ�ı�*/\
/*257*/ ,Fn_ListBoxWSetItemTip/*�б��.�ñ�����ʾ�ı�*/\
/*258*/ ,Fn_ListBoxWGetItemImageIndex/*�б��.ȡ����ͼƬ����*/\
/*259*/ ,Fn_ListBoxWSetItemImageIndex/*�б��.�ñ���ͼƬ����*/\
/*260*/ ,Fn_ListBoxWInitStorage/*�б��.�����ڴ�*/\
/*261*/ ,Fn_ListBoxWGetImageList/*�б��.ȡͼ���б���*/\
/*262*/ ,Fn_ListBoxWSetImageList/*�б��.��ͼ���б���*/\
/*263*/ ,Fn_ListBoxWGetItemRect/*�б��.ȡ�������*/\
/*264*/ ,Fn_ListBoxWHitTest/*�б��.���в���*/\
/*265*/ ,Fn_ListBoxWGetItemStringLength/*�б��.ȡ�����ı�����*/\
/*266*/ ,Fn_ListBoxWSort/*�б��.����*/\
/*267*/ ,Fn_ListBoxWSort2/*�б��.�Զ�������*/\
/*268*/ ,Fn_ListBoxWSwapItem/*�б��.��������*/\
/*269*/ ,Fn_ListBoxWMoveItem/*�б��.�ƶ�����*/\
/*270*/ ,Fn_DirBoxGetCurrentItem/*Ŀ¼��.ȡ��ǰѡ�б���*/\
/*271*/ ,Fn_DirBoxExtend/*Ŀ¼��.չ����*/\
/*272*/ ,Fn_DirBoxGetCheckedItems/*Ŀ¼��.ȡ���м����Ŀ*/\
/*273*/ ,Fn_DirBoxRefresh/*Ŀ¼��.ˢ��*/\
/*274*/ ,e_memcpy/*�ڴ渴��*/\
/*275*/ ,Fn_EditCut/*�༭��.����*/\
/*276*/ ,Fn_ComboBoxWInsertString/*��Ͽ�.������Ŀ*/\
/*277*/ ,Fn_ComboBoxWDelString/*��Ͽ�.ɾ����Ŀ*/\
/*278*/ ,Fn_ComboBoxWGetItemCount/*��Ͽ�.ȡ��Ŀ��*/\
/*279*/ ,Fn_ComboBoxWGetTopIndex/*��Ͽ�.ȡ��һ�ɼ���*/\
/*280*/ ,Fn_ComboBoxWSetTopIndex/*��Ͽ�.�õ�һ�ɼ���*/\
/*281*/ ,Fn_ComboBoxWGetItemlParam/*��Ͽ�.ȡ��Ŀ��ֵ*/\
/*282*/ ,Fn_ComboBoxWSetItemlParam/*��Ͽ�.����Ŀ��ֵ*/\
/*283*/ ,Fn_ComboBoxWGetItemString/*��Ͽ�.ȡ��Ŀ�ı�*/\
/*284*/ ,Fn_ComboBoxWSetItemString/*��Ͽ�.����Ŀ�ı�*/\
/*285*/ ,Fn_ComboBoxWFindString/*��Ͽ�.Ѱ����Ŀ*/\
/*286*/ ,Fn_ComboBoxWGetItemColor/*��Ͽ�.ȡ��Ŀ��ɫ*/\
/*287*/ ,Fn_ComboBoxWSetItemColor/*��Ͽ�.����Ŀ��ɫ*/\
/*288*/ ,Fn_ComboBoxWGetItemImageIndex/*��Ͽ�.ȡ��ĿͼƬ����*/\
/*289*/ ,Fn_ComboBoxWSetItemImageIndex/*��Ͽ�.����ĿͼƬ����*/\
/*290*/ ,Fn_ComboBoxWInitStorage/*��Ͽ�.�����ڴ�*/\
/*291*/ ,Fn_ComboBoxWGetImageList/*��Ͽ�.ȡͼ���б���*/\
/*292*/ ,Fn_ComboBoxWSetImageList/*��Ͽ�.��ͼ���б���*/\
/*293*/ ,Fn_ComboBoxWGetItemStringLength/*��Ͽ�.ȡ��Ŀ�ı�����*/\
/*294*/ ,Fn_ComboBoxWSort/*��Ͽ�.����*/\
/*295*/ ,Fn_ComboBoxWSort2/*��Ͽ�.�Զ�������*/\
/*296*/ ,Fn_ComboBoxWSwapItem/*��Ͽ�.��������*/\
/*297*/ ,Fn_ComboBoxWMoveItem/*��Ͽ�.�ƶ�����*/\
/*298*/ ,Fn_ListBoxWGetItemDisableState/*�б��.ȡ�����ֹ״̬*/\
/*299*/ ,Fn_ListBoxWSetItemDisableState/*�б��.�ñ����ֹ״̬*/\
/*300*/ ,edbs_del/*�����ݿ�.ɾ��*/\
/*301*/ ,edbs_pop/*�����ݿ�.����ɾ��*/\
/*302*/ ,edbs_cancel_del/*�����ݿ�.ȡ��ɾ��*/\
/*303*/ ,e_load_windows/*���봰��*/\
/*304*/ ,EplVar_structure/*����.����*/\
/*305*/ ,EplVar_copy/*����.����*/\
/*306*/ ,EplVar_destruct/*����.����*/\
/*307*/ ,Fn_Var_Set/*����.��*/\
/*308*/ ,Fn_Var_Get/*����.ȡ*/\
/*309*/ ,Fn_Var_Type/*����.����*/\
/*310*/ ,Fn_Var_Size/*����.����*/\
/*311*/ ,Fn_Var_TypeName/*����.������*/\
/*312*/ ,Fn_Var_Data/*����.ָ��*/\
/*313*/ ,Fn_Var_ToBin/*����.���ֽڼ�*/\
/*314*/ ,Fn_Ceil/*����ȡ��*/\
/*315*/ ,Fn_Floor/*����ȡ��*/\
/*316*/ ,Fn_GetVarPtr/*ȡ����ָ��*/\
/*317*/ ,Fn_GetVarDataPtr/*ȡ��������ָ��*/\
/*318*/ ,Fn_CFile_structure/*�ļ���д.����*/\
/*319*/ ,Fn_CFile_copy/*�ļ���д.����*/\
/*320*/ ,Fn_CFile_destruct/*�ļ���д.����*/\
/*321*/ ,Fn_CFile_Open/*�ļ���д.��*/\
/*322*/ ,Fn_CFile_Close/*�ļ���д.�ر�*/\
/*323*/ ,Fn_CFile_Lock/*�ļ���д.��ס*/\
/*324*/ ,Fn_CFile_UnLock/*�ļ���д.����*/\
/*325*/ ,Fn_hexview_setdata/*���ƿ�.������*/\
/*326*/ ,Fn_CFile_FSeek/*�ļ���д.�ƶ���дλ��*/\
/*327*/ ,Fn_CFile_SeekToBegin/*�ļ���д.�Ƶ��ļ���*/\
/*328*/ ,Fn_CFile_SeekToEnd/*�ļ���д.�Ƶ��ļ�β*/\
/*329*/ ,Fn_CFile_ReadBin/*�ļ���д.�����ֽڼ�*/\
/*330*/ ,Fn_CFile_ReadBin/*�ļ���д.д���ֽڼ�*/\
/*331*/ ,Fn_CFile_ReadText/*�ļ���д.�����ı�W*/\
/*332*/ ,Fn_CFile_WriteText/*�ļ���д.д���ı�W*/\
/*333*/ ,Fn_CFile_ReadLine/*�ļ���д.����һ��*/\
/*334*/ ,Fn_CFile_WriteLine/*�ļ���д.д��һ��*/\
/*335*/ ,Fn_CFile_isOpen/*�ļ���д.�Ƿ��Ѵ�*/\
/*336*/ ,Fn_CFile_GetCurrent/*�ļ���д.ȡ��ǰ��дλ��*/\
/*337*/ ,Fn_CFile_GetSize/*�ļ���д.ȡ�ļ���С*/\
/*338*/ ,Fn_CFile_RemoveData/*�ļ���д.ɾ������*/\
/*339*/ ,Fn_CFile_InsertStr/*�ļ���д.�����ı�*/\
/*340*/ ,Fn_comp_py_code/*�����ֱȽ�W*/\
/*341*/ ,Fn_comp_py/*�����Ƚ�W*/\
/*342*/ ,Fn_get_str_py/*ȡ�ı�ƴ��W*/\
/*343*/ ,Fn_is_matching_brackets/*���ŷ�ƥ��*/\
/*344*/ ,Fn_throw_ception/*�׳��쳣*/\
/*345*/ ,Fn_catch_ception/*ע���쳣����*/\
/*346*/ , Fn_process_messages_improved/*ȡCPU������*/\
/*347*/ ,Fn_get_win_pic/*��ͼ*/\
/*348*/ ,Fn_get_pixel/*ȡ������ɫ*/\
/*349*/ , Fn_QRcode_encodeString/*�����ı���ά��*/\
/*350*/ ,Fn_QRcode_encodeData/*�������ݶ�ά��*/\
/*351*/ ,Fn_MemoryModule_structure/*����*/\
/*352*/ ,Fn_MemoryModule_copy/*����*/\
/*353*/ ,Fn_MemoryModule_destruct/*����*/\
/*354*/ ,Fn_MemoryModule_LoadLibrary/*����*/\
/*355*/ ,Fn_MemoryModule_GetProcAddress/*ȡ������ַ*/\
/*356*/ ,Fn_MemoryModule_CallEntryPoint/*����*/\
/*357*/ ,Fn_eStl_GetMd5W/*ȡ����ժҪ*/\
/*358*/ ,Fn_eStl_GetMd5A/*ȡ����ժҪA*/\
/*359*/ ,Fn_eStl_FileManyDialogW/*���ļ��Ի���*/

#pragma endregion





#pragma region ������ӵ���
#define ALL_E_LIB_CLASS \
CtButtonW,/*��ťW*/\
CtEdit,/*�༭��W*/\
severex,/*������Ex*/\
clinetex,/*�ͻ���Ex*/\
hCoprocessD,/*Э�̾��*/\
media_play_ex,/*ý�岥��*/\
TaskDialog_Button_Type,/*�߼���Ϣ��ť*/\
UpDown,/*������*/\
hCoroutine,/*Э�̵�����*/\
edbs_ex,/*edbs*/\
CtCheckButtonW,/*ѡ���*/\
CtCommandLink/*��������*/\
,CtLabelW/*��ǩW*/\
,ClMenu/*�˵�*/\
,CtListBoxW/*�б��*/\
,Obj_EMemFile/*�ڴ��ļ�*/\
/*,CtScintilla�޷�ͨ����̬���룬��ʱ�Ƴ�*/\
,CtDirBoxW/*Ŀ¼��*/\
,CtRichEdit/*���ı���*/\
,CtComboBox/**/\
,epl_class_Var/*ǿ���Ͷ�̬����*/\
,Obj_DiskFile/*�ļ���д��*/\
,Enum_CoRuningType/*Э������״̬*/\
,HexView_control/*���ƿ�*/\
,Obj_MemoryModule/*�ڴ�ģ����*/

#pragma endregion





#pragma region �����ӵ���
#define ALL_E_LIB_PLUG \
Plug_UnicodeBase/*unicodeԤ����*/

#pragma endregion