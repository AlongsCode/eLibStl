// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "elib/lib2.h"

#if _MSC_VER < 1201

#else

#endif



static IEKrnln g_call;


inline void init_call_dll()
{
    if ( g_call ) return;
    g_call = IextEntry();
}
#ifndef __E_STATIC_LIB
#define IEXT_DEF_STR(_index, _name, _remarks) (INT) ______E_FNENAME(IEXT_NAME(_index, _name)),
static INT s_names[] =
{
    2
};
#endif


// 这个是为了静态库有这么一个函数, 功能全部给dll处理
// 静态库会调用这个函数, 这个函数把消息都转到dll里
EXTERN_C INT WINAPI iext_ProcessNotifyLib_iext(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    switch ( nMsg )
    {
#ifndef __E_STATIC_LIB
    // 返回所有命令实现函数的的函数名称数组(char*[]), 支持静态编译的动态库必须处理
    case NL_GET_CMD_FUNC_NAMES:
    {
        g_call->NotifyLib(nMsg, (DWORD)"QQ121007124__Group_20752843", (DWORD)s_names);
        return (INT)s_names;
    }
    // 返回处理系统通知的函数名称(PFN_NOTIFY_LIB函数名称), 支持静态编译的动态库必须处理
    case NL_GET_NOTIFY_LIB_FUNC_NAME:
    {
        return (INT)"iext_ProcessNotifyLib_iext";
    }
    // 返回静态库所依赖的其它静态库文件名列表(格式为\0分隔的文本,结尾两个\0), 支持静态编译的动态库必须处理
    // kernel32.lib user32.lib gdi32.lib 等常用的系统库不需要放在此列表中
    // 返回NULL或NR_ERR表示不指定依赖文件
    case NL_GET_DEPENDENT_LIBS:
    {
        return (INT)"\0\0";
    }
#endif

    // 告知库通知系统用的函数指针,在装载支持库前通知,可能有多次,后通知的值应该覆盖前面所通知的值,忽略返回值
    // 库可将此函数指针记录下来以便在需要时使用它通知信息到系统
    // dwParam1: (PFN_NOTIFY_SYS)
    case NL_SYS_NOTIFY_FUNCTION:
    {
        init_call_dll();
        break;
    }
    default:
        break;
    }
    return g_call->NotifyLib(nMsg, dwParam1, dwParam2);
    return 0;
}



inline static void iext_CallDllFun_iext(int index, PVOID pRetData, INT nArgCount, PVOID pArgInf)
{
    //g_call->CallFun(index, pRetData, nArgCount, pArgInf);
}

#define IEXT_DEF_CALL(_index, _name, _remarks) \
    extern "C" void IEXT_NAME(_index, _name)(PVOID pRetData, INT nArgCount, PVOID pArgInf)\
    {\
        iext_CallDllFun_iext(_index, pRetData, nArgCount, pArgInf);\
    }
#define IEXT_DEF_INTERFACE(_name) extern "C" PVOID __stdcall iext_GetInterface_##_name(INT nInterfaceNO) { return g_call->GetInterface_##_name(nInterfaceNO); }


//! 这个文件主要是让静态库有导出命令, 这些命令都是调用dll实现
//! 在dll里会把这些函数名数组返回给易语言
//IEXT_DEF(IEXT_DEF_CALL)             // 所有的命令, 都是调用dll来实现, 把函数索引和参数传递到dll里, 由dll处理
//IEXT_DEF_INTERFACE(TreeBox)         // 树型框的组件接口函数
//IEXT_DEF_INTERFACE(StatusBar)       // 状态条的组件接口函数
//IEXT_DEF_INTERFACE(ToolBar)         // 工具条的组件接口函数
//IEXT_DEF_INTERFACE(ListView)        // 超列的组件接口函数
//IEXT_DEF_INTERFACE(TransLabel)      // 透明标签的组件接口函数

#ifndef __E_STATIC_LIB

//计算Offset
inline ULONG RvaToOffset(PIMAGE_NT_HEADERS pNtHeader, ULONG Rva)
{
    //PE节
    PIMAGE_SECTION_HEADER pSection = (PIMAGE_SECTION_HEADER)( pNtHeader + 1 );

    ULONG sNum, i;
    //取得节表项数目
    sNum = pNtHeader->FileHeader.NumberOfSections;
    for ( i = 0; i < sNum; i++ )
    {
        //printf("PE 节名称: %s\n",p_section_header->Name);
        if ( ( pSection->VirtualAddress <= Rva ) && Rva < ( pSection->VirtualAddress + pSection->SizeOfRawData ) )
        {
            return Rva - pSection->VirtualAddress + pSection->PointerToRawData;
        }
        pSection++;
    }
    return 0;
}

// 获取这个地址是当前进程哪个模块里的地址, 用来调试注册消息/事件堆栈错误的问题
inline const char* GetDllNameFromAddress(LPCVOID pAddress)
{
    if ( !pAddress )
        return 0;
    MEMORY_BASIC_INFORMATION mem;
    BOOL isOk = VirtualQuery(pAddress, &mem, sizeof(MEMORY_BASIC_INFORMATION));
    LPBYTE pCmp = (LPBYTE)mem.AllocationBase;
    if ( !isOk ) return 0;

    static char runFile[260];
    runFile[0] = 0;
    const int fileBuffer = sizeof(runFile) / sizeof(runFile[0]);
    GetModuleFileNameA((HMODULE)pCmp, runFile, fileBuffer);   // 先获取到程序运行路径
    if ( runFile[0] )
    {
        char* pos = strrchr(runFile, '\\');
        if ( pos )
        {
            *pos++ = 0;
            return pos;
        }
        return runFile;
    }

    if ( pCmp[0] != 'M' || pCmp[1] != 'Z' )
        return 0;

    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)pCmp;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)( pCmp + dosHeader->e_lfanew );

    ULONG offsetExportTable = RvaToOffset(nt, nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);    // 导出表偏移
    PIMAGE_EXPORT_DIRECTORY pExportTable = (PIMAGE_EXPORT_DIRECTORY)( pCmp + offsetExportTable );   // 导出表
    if ( !offsetExportTable ) return 0;

    char* dllName = (char*)( pCmp + RvaToOffset(nt, pExportTable->Name) );
    return dllName;
}

EXTERN_C void* WINAPI GetNewInf()
{
    //! 静态编译不会走这里, 所以这个不怕取到exe的文件名
    LPCSTR name = GetDllNameFromAddress(GetNewInf);
    //if ( stricmp(name, "iext.fne") != 0 && stricmp(name, "iext.fnr") != 0 )
    //{
    //    MessageBoxW(0, L"检测到支持库文件名已被修改, 本次不会加载支持库\r\n本支持库只允许文件名为 iext.fne", L"扩展界面支持库一Ex", MB_ICONERROR);
    //    return 0;
    //}
    init_call_dll();
    if ( !g_call )return 0;
#define IEXT_INTERFACE_NAME(_name) (int)iext_GetInterface_##_name
#ifdef __E_STATIC_LIB
    static bool isStatic = true;
#else
    static bool isStatic = false;
#endif

    //PLIB_INFO info = (PLIB_INFO)g_call->GetNewInf(iext_ProcessNotifyLib_iext, &isStatic);


    //int fn[5][2] =
    //{
    //    { IEXT_INTERFACE_NAME(TreeBox),    IDICON_TREEVIEW },
    //    { IEXT_INTERFACE_NAME(StatusBar),  IDICON_STATUSBAR },
    //    { IEXT_INTERFACE_NAME(ToolBar),    IDICON_TOOLBAR },
    //    { IEXT_INTERFACE_NAME(ListView),   IDICON_LISTVIEW },
    //    { IEXT_INTERFACE_NAME(TransLabel), IDICON_TRANSPARENTSTATIC },
    //};

    //// 修改组件通知回调和组件图标索引
    //// 因为易语言加载的是这个支持库, 所以需要返回这个支持库的资源ID
    //for ( int i = 0; i < 5; i++ )
    //{
    //    info->m_pDataType[i].m_pfnGetInterface = (PFN_GET_INTERFACE)fn[i][0];
    //    info->m_pDataType[i].m_dwUnitBmpID = fn[i][1];
    //}

    //return info;
    return 0;
}

#endif

