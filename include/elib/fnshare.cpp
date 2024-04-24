#include "fnshare.h"



extern "C" {
	int APIENTRY Scintilla_DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved);
	int APIENTRY SkinH_Init(HINSTANCE hInstance);
	int APIENTRY SkinH_Free();
}

namespace elibstl
{
	static PFN_NOTIFY_SYS s_pfnNotifySys = 0;
	static PFN_NOTIFY_SYS s_pfnuserNotifySys = 0;    // �ɺ��� SetUserSysNotify() ����, 
	INT WINAPI NotifySys(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		INT ret = 0;
		if (s_pfnNotifySys != NULL)
			ret = s_pfnNotifySys(nMsg, dwParam1, dwParam2);
		return ret;
	}
#ifndef __E_STATIC_LIB
	void e_debugbox_init();
#endif
	INT WINAPI ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		INT nRet = NR_OK;
		switch (nMsg)
		{
		case NL_SYS_NOTIFY_FUNCTION:
		{
#ifndef __E_STATIC_LIB
			/*��ֹ���뾲̬��ʱ��ȡ��ҳ����*/
			e_debugbox_init();
#endif
			s_pfnNotifySys = (PFN_NOTIFY_SYS)dwParam1;
#ifdef __E_STATIC_LIB
			SkinH_Init(GetModuleHandleA(nullptr));
#endif

			break;
		}
		case NL_FREE_LIB_DATA:
#ifdef __E_STATIC_LIB
			SkinH_Free();
#endif
			break;
		case NL_GET_CMD_FUNC_NAMES:
			//Ӧ������������ͷ���ʵ�ֺ����ĺ�����������, 
			//���������������ͷ�����������һһ��Ӧ, 
			//�������Ա��Ϊ��Ӧ�����ĺ��������ı�ָ��(char*)��

			break;
		case NL_GET_NOTIFY_LIB_FUNC_NAME:
			//Ӧ���ء�����ϵͳ֪ͨ�ĺ�����(��������)�ĺ�������(char*)��

			break;
		case NL_GET_DEPENDENT_LIBS:
			//Ӧ���ء������ĵ�������̬���ļ��б�, ��ʽΪ\0�ָ����ı�, ��β����\0��

			break;
		default:
			nRet = NR_ERR;
			break;
		}

		//�����û�����
		if (s_pfnuserNotifySys)
			nRet = s_pfnuserNotifySys(nMsg, dwParam1, dwParam2);

		return nRet;
	}

	PFN_NOTIFY_SYS __stdcall SetUserSysNotify(PFN_NOTIFY_SYS pfn)
	{
		s_pfnuserNotifySys = pfn;
		return ProcessNotifyLib;
	}
}