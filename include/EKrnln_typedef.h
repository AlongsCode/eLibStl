#pragma once
#include <windows.h>

typedef BOOL(CALLBACK* PFN_ProcessNotifyLib)( INT nMsg, DWORD dwParam1, DWORD dwParam2, INT* pRet );
typedef BOOL(CALLBACK* PFN_ProcessNotify)( INT nMsg, DWORD dwParam1, DWORD dwParam2 );

// 界面库一接口类, 由支持库调用, 这里调用的是dll里的命令
class CEKrnln_interface
{
public:
    virtual int Release() = 0;
    virtual void* GetNewInf(PFN_ProcessNotify pfn, bool* isStatic) = 0;
    virtual int NotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2) = 0;
    virtual void CallFun(int index, PVOID pRetData, INT nArgCount, PVOID pArgInf) = 0;
    virtual PVOID GetInterface_TransLabel(INT nInterfaceNO) = 0;
    virtual PVOID GetInterface_ListView(INT nInterfaceNO) = 0;
    virtual PVOID GetInterface_StatusBar(INT nInterfaceNO) = 0;
    virtual PVOID GetInterface_ToolBar(INT nInterfaceNO) = 0;
    virtual PVOID GetInterface_TreeBox(INT nInterfaceNO) = 0;


};

typedef CEKrnln_interface* IEKrnln;

