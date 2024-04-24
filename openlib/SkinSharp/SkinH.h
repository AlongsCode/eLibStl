/*��Stdafx.h�ļ��м����������
#include "SkinH.h"
#pragma comment(lib, "Detours.lib")
#pragma comment(lib, "SkinH_ST.lib")

**************** ���ݱ���ѡ��������ѡ�������������� ***********
�±���ʾ����Ҫʹ�õ�����ʱ��Ӧ���ԵĿ⡣
��Ҫʹ�õ�һ������ʱ��    ����Ե�2�е���Щ�� 
���߳� (libc.lib) 
libcmt.lib��msvcrt.lib��libcd.lib��libcmtd.lib��msvcrtd.lib
���߳� (libcmt.lib) 
libc.lib��msvcrt.lib��libcd.lib��libcmtd.lib��msvcrtd.lib
ʹ�� DLL �Ķ��߳� (msvcrt.lib) 
libc.lib��libcmt.lib��libcd.lib��libcmtd.lib��msvcrtd.lib
���Ե��߳� (libcd.lib) 
libc.lib��libcmt.lib��msvcrt.lib��libcmtd.lib��msvcrtd.lib
���Զ��߳� (libcmtd.lib) 
libc.lib��libcmt.lib��msvcrt.lib��libcd.lib��msvcrtd.lib
ʹ�� DLL �ĵ��Զ��߳� (msvcrtd.lib) 
libc.lib��libcmt.lib��msvcrt.lib��libcd.lib��libcmtd.lib
**************************************************************/
#ifndef SKIN_H
#define SKIN_H

///ERROR CODE//////////////////////// 
#define		SRET_OK					0
#define		SRET_ERROR				1
#define		SRET_ERROR_FILE			2
#define		SRET_ERROR_PARAM		3
#define		SRET_ERROR_CREATE		4
#define		SRET_ERROR_FORMAT		5
#define		SRET_ERROR_VERSION		6
#define		SRET_ERROR_PASSWORD		7
#define		SRET_ERROR_INVALID		8
//////////////////////////////////////

//�ӿ��б�
extern "C"
{
	 /*
		����:	��̬���ʼ��
		����ֵ:	�ɹ�����0, ʧ�ܷ��ط�0
	 */
	int __stdcall SkinH_Init(HINSTANCE hInstance);


	/*
		����:	��̬��ж��
		����ֵ:	�ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_Free();


	/*
	 	����:	���س���ǰĿ¼�µ��ļ���skinh.sheƤ�����л���
	 	����ֵ:	�ɹ�����0, ʧ�ܷ��ط�0
	 */
	int __stdcall SkinH_Attach();
	

	/*
		����:	����ָ��·����Ƥ�����л���
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_AttachEx(
						LPCTSTR strSkinFile,	//Ƥ���ļ�·��
						LPCTSTR strPassword		//Ƥ����Կ
						);

	/*
		����:	����ָ��·����Ƥ�����л�����ָ����Ӧ��ɫ�������Ͷȣ�����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_AttachExt(
						LPCTSTR strSkinFile,	//Ƥ���ļ�·��
						LPCTSTR strPassword,	//Ƥ����Կ
						int nHue,				//ɫ����	ȡֵ��Χ0-360, Ĭ��ֵ0
						int nSat,				//���Ͷȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						int nBri				//���ȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						);
	
	/*
		����:	����ָ����Դ���л�����ָ����Ӧ��ɫ�������Ͷȣ�����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_AttachRes(
						LPBYTE	pShe,			//��ԴƤ������ָ��
						DWORD	dwSize,			//��ԴƤ�����ݳ���
						LPCTSTR strPassword,	//Ƥ����Կ
						int nHue,				//ɫ����	ȡֵ��Χ0-360, Ĭ��ֵ0
						int nSat,				//���Ͷȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						int nBri				//���ȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						);

	/*
		����:	����ָ��Ƥ����Դ���л�����ָ����Ӧ��ɫ�������Ͷȣ�����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_AttachResEx(
						LPCTSTR lpName,			//��Դ��
						LPCTSTR lpType,			//��Դ����
						LPCTSTR strPassword,	//Ƥ����Կ
						int nHue,				//ɫ����	ȡֵ��Χ0-360, Ĭ��ֵ0
						int nSat,				//���Ͷȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						int nBri				//���ȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						);

	/*
		����:	ж�ػ���	
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_Detach();

	/*
		����:	ж��ָ������Ĵ�����߿ؼ���Ƥ��	
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_DetachEx(
						HWND hWnd				//ָ��ж��Ƥ���Ĵ����ؼ��ľ��
						);
	
	/*
		����:	����ָ�������͸����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetWindowAlpha(
						HWND hWnd,				//����ľ�� 
						int nAlpha				//͸����
						);

	/*
		����:	������ǰƤ����ɫ�������Ͷȣ�����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_AdjustHSV(
						int nHue,				//ɫ����	ȡֵ��Χ0-360, Ĭ��ֵ0
						int nSat,				//���Ͷȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						int nBri				//���ȣ�	ȡֵ��Χ0-256, Ĭ��ֵ0
						);
	
	/*
		����:	��ȡָ�����ڻ�ؼ���nX,nY������ɫֵ 
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_GetColor(
						HWND hWnd,				//ָ�������ؼ��ľ��
						int nX,					//������
						int nY					//������
						);
	
	/*
		����:	ָ������Ϳؼ��Ļ�������
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_Map(
						HWND hWnd,				//ָ�������ؼ��ľ�� 
						int nType				//��������
						);

	//��������
	#define TYPE_UNKNOWN				0		//δ֪����
	#define TYPE_ANIMATE				1001	//�����ؼ� 
	#define TYPE_CHECKBOX				1002	//��ѡ��
	#define TYPE_COMBOBOX				1003	//��Ͽ�
	#define TYPE_COMBOLBOX				1004	//���������
	#define TYPE_CONTROLBAR				1005	//�ؼ���
	#define TYPE_DATETIME				1006	//���ڿؼ�
	#define TYPE_EDITBOX				1007	//�ı���
	#define TYPE_GROUPBOX				1008	//�����
	#define TYPE_HEADERCTRL				1009	//��ͷ�ؼ�
	#define TYPE_HOTKEY					1010	//�ȼ��ؼ�
	#define TYPE_IPADDRESS				1011	//IP��ַ�ؼ�
	#define TYPE_LABEL					1012	//��ǩ�ؼ�
	#define TYPE_LISTBOX				1013	//�б��
	#define TYPE_LISTVIEW				1014	//�б���ͼ
	#define TYPE_MDICLIENT				1015	//MDI�ͻ���
	#define TYPE_MENU					1016	//�˵�
	#define TYPE_MONTHCAL				1017	//�����ؼ�
	#define TYPE_PICTURE				1018	//ͼƬ��
	#define TYPE_PROGRESS				1019	//������
	#define TYPE_PUSHBUTTON				1020	//��ͨ��ť
	#define TYPE_RADIOBUTTON			1021	//��ѡ��
	#define TYPE_REBAR					1022	//������
	#define TYPE_RICHEDIT				1023	//���ı���
	#define TYPE_SCROLLBAR				1024	//������
	#define TYPE_SCROLLCTRL				1025	//���ù������Ŀؼ�
	#define TYPE_SPINCTRL				1026	//������
	#define TYPE_STATUSBAR				1027	//״̬��
	#define TYPE_TABCTRL				1028	//ѡ���
	#define TYPE_TOOLBAR				1029	//������
	#define TYPE_TOOLBARWND				1030	//MFC����������
	#define TYPE_TRACKBAR				1031	//�����ؼ�
	#define TYPE_TREEVIEW				1032	//������ͼ
	#define TYPE_WINDOW					1034	//��׼����
	#define TYPE_COMCTRL				1036	//ͨ�û���
	#define TYPE_PAINTCTRL				1037	//ͨ�û���

	/*
		����:	����Aero��Ч
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetAero(
						int bAero				//1Ϊ������Ч,0Ϊ�ر���Ч 
						);
	

	/*
		����:	����Aero��Ч����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_AdjustAero(
						int nAlpha,				//͸����,   0-255, Ĭ��ֵ0
						int nShwDark,			//����,     0-255, Ĭ��ֵ0
						int nShwSharp,			//���,	    0-255, Ĭ��ֵ0 
						int nShwSize,			//��Ӱ��С, 2-19,  Ĭ��ֵ2
						int nX,					//ˮƽƫ��, 0-25,  Ĭ��ֵ0 (Ŀǰ��֧��)
						int nY,					//��ֱƫ��, 0-25,  Ĭ��ֵ0 (Ŀǰ��֧��)
						int nRed,				//��ɫ����, 0-255, Ĭ��ֵ -1
						int nGreen,				//��ɫ����, 0-255, Ĭ��ֵ -1 
						int nBlue				//��ɫ����, 0-255, Ĭ��ֵ -1 
						);
	
	/*
		����:	���ô����Ƿ�����ƶ�
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetWindowMovable(
						HWND hWnd,				//���ھ�� 
						BOOL bMovable			//0Ϊ�����ƶ�, 1Ϊ���ƶ�
						);
	
	/*
		����:	���ÿؼ��ı���ɫ(Ŀǰ���Ե�ѡ��, ��ѡ��, �������Ч)
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetBackColor(
						HWND hWnd,				//�ؼ����
						int nRed,				//��ɫ����
						int nGreen,				//��ɫ����
						int nBlue				//��ɫ����
						);
	
	/*
		����:	���ÿؼ����ı���ɫɫ(Ŀǰ���Ե�ѡ��,��ѡ��,�������Ч)
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetForeColor(
						HWND hWnd,				//�ؼ����
						int nRed,				//��ɫ����
						int nGreen,				//��ɫ����
						int nBlue				//��ɫ����
						);

	/*
		����:	�������������б�ؼ�����ʱ���ظ�����Ӱ��ִ��Ч������
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_LockUpdate(
						HWND hWnd,				//ָ�������ؼ��ľ�� 
						int bUpdate				//1Ϊ�������ƣ�0Ϊ�������� 
						);
	
	/*
		����:	���ò˵�͸����
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetMenuAlpha(
						int nAlpha				//�˵�͸���ȣ�ȡֵ��Χ 0 - 255
						);

	/*
		����:	����ָ���豸�����ĵ�Ԫ��
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_NineBlt(
						HDC hDtDC,				//Ŀ���豸������
						int left,				//���Ͻ�ˮƽ����
						int top,				//���ϽǴ�ֱ����
						int right,				//���½�ˮƽ����
						int bottom,				//���½Ǵ�ֱ����
						int nMRect				//Ԫ��id
						);

	/*
		����:	���ñ���˵���
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0	
	*/
	int __stdcall SkinH_SetTitleMenuBar(
						HWND hWnd, 	//���ھ��
						BOOL bEnable,	//�Ƿ����� 1Ϊ���ã� 0 Ϊȡ�� 
						int nTMenuY, 	//�˵����߶�
						int nTopOffs, 	//����ƫ��
						int nRightOffs 	//�Ҳ�ƫ��
						);

	
	/*
		����:	���ÿؼ�������
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_SetFont(
						HWND hWnd,		//�ؼ��ľ��
						HFONT hFont		//������
						);
		
		
	/*
		����:	���ÿؼ�������
		����ֵ: �ɹ�����0, ʧ�ܷ��ط�0
	*/
	int __stdcall SkinH_SetFontEx(
						HWND hWnd,		//�ؼ��ľ��
						LPCTSTR szFace,	//��������
						int nHeight,	//����߶�
						int nWidth,		//������
						int nWeight,	//�������
						int nItalic,	//�Ƿ�б��
						int nUnderline,	//�Ƿ��»���
						int nStrikeOut	//�Ƿ�ɾ����
						);

}
#endif