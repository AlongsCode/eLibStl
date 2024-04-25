#include "fnshare.h"



extern "C" {
	int APIENTRY Scintilla_DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved);
	int APIENTRY SkinH_Init(HINSTANCE hInstance);
	int APIENTRY SkinH_Free();
}

namespace elibstl
{
	static PFN_NOTIFY_SYS s_pfnNotifySys = 0;
	static PFN_NOTIFY_SYS s_pfnuserNotifySys = 0;    // 由函数 SetUserSysNotify() 设置, 
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
			/*防止编译静态库时抽取此页代码*/
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
			//应返回所有命令和方法实现函数的函数名称数组, 
			//此数组必须与命令和方法定义数组一一对应, 
			//数组各成员均为对应函数的函数名称文本指针(char*)；

			break;
		case NL_GET_NOTIFY_LIB_FUNC_NAME:
			//应返回“处理系统通知的函数”(即自身函数)的函数名称(char*)；

			break;
		case NL_GET_DEPENDENT_LIBS:
			//应返回“依赖的第三方静态库文件列表”, 格式为\0分隔的文本, 结尾两个\0。

			break;
		default:
			nRet = NR_ERR;
			break;
		}

		//调用用户代码
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