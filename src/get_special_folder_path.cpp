#include <shlobj.h>
#include"ElibHelp.h"

// ��ȡ�ļ���·��
/*�˲�����ʾҪ��ȡ�������ļ��е����͡�
ֵΪ1ʱ��ʾ��ȡ�ҵ��ĵ��ļ���·����
ֵΪ2ʱ��ʾ��ȡ�ҵ��ղؼ�·����
ֵΪ3ʱ��ʾ��ȡ�����ļ���·����
ֵΪ4ʱ��ʾ��ȡ�����ļ���·����
ֵΪ5ʱ��ʾ��ȡ��ʼ�˵��ļ���·����
ֵΪ6ʱ��ʾ��ȡ�����ļ���·����
ֵΪ7ʱ��ʾ��ȡ�����ļ���·����
ֵΪ8ʱ��ʾ��ȡӦ�ó��������ļ���·����
ֵΪ9ʱ��ʾ��ȡWindows�ļ���·����
ֵΪ10ʱ��ʾ��ȡϵͳ�ļ���·����
ֵΪ11ʱ��ʾ��ȡ��ʱ�ļ���·����*/
static LPBYTE GetSpecialFolderPath(DWORD Type) {
	wchar_t path[MAX_PATH + 1] = { 0 };
	BOOL IsSucceeded = FALSE;
	if (Type >= 1 && Type <= 8) {
		IsSucceeded = SHGetSpecialFolderPathW(NULL, path, (Type == 1 ? CSIDL_PERSONAL : Type == 2 ? CSIDL_FAVORITES : Type == 3 ? CSIDL_DESKTOPDIRECTORY :
			Type == 4 ? CSIDL_FONTS : Type == 5 ? CSIDL_STARTMENU : Type == 6 ? CSIDL_PROGRAMS : Type == 7 ? CSIDL_STARTUP : CSIDL_APPDATA), FALSE);
	}
	else if (Type == 9) {
		IsSucceeded = (GetWindowsDirectoryW(path, MAX_PATH) > 0);
	}
	else if (Type == 10) {
		IsSucceeded = (GetSystemDirectoryW(path, MAX_PATH) > 0);
	}
	else {
		if (Type != 11) {
			return 0;
		}
		IsSucceeded = (GetTempPathW(MAX_PATH, path) > 0);
	}
	LPBYTE Ret = nullptr;
	if (IsSucceeded) {
		size_t lenth = wcslen(path);
		if (lenth > 0 && path[lenth - 1] != L'\\') {
			path[lenth] = L'\\';
			path[lenth + 1] = L'\0';
		}
		Ret = elibstl::clone_textw(path);
	}
	return Ret;
};

EXTERN_C void shell_get_special_folder_path_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	//�����ز�Ϊ��
	pRetData->m_pBin = GetSpecialFolderPath(pArgInf->m_int);
}


static ARG_INFO Args[] =
{

	{
		/*name*/    "����ȡĿ¼����",
		/*explain*/ ("��������ָ������ȡĿ¼�����ͣ�����Ϊ���³���ֵ֮һ�� 1: #�ҵ��ĵ�;  2: #�ҵ��ղؼ�;  3: #ϵͳ����;  4: #ϵͳ����;  5: #��ʼ�˵���;  6: #����˵���;  7: #�����˵���;  8: #��������Ŀ¼;  9: #Windows��װĿ¼;  10: #WindowsϵͳĿ¼;  11: #��ʱ�ļ�Ŀ¼��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

FucInfo get_special_folder_path_W = { {
		/*ccname*/  ("ȡ�ض�Ŀ¼W"),
		/*egname*/  ("GetSpecialFolderPathW"),
		/*explain*/ ("�������ָ����Windowsϵͳ�ض�Ŀ¼��������Ŀ¼���ԡ�\\�����Ž�������ʧ�ܷ��ؿ��ı���"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,shell_get_special_folder_path_W ,"shell_get_special_folder_path_W" };