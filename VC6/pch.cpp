// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include "LoadTempLibrary.h"
#include <EKrnln_Version.h>

//#define __MEM_LOAD_DLL__    // 需要编译成内存调用就打开这个宏
#define _DBG_LOCAL          // 本地调用, 一般调试时使用, 直接调用本地的dll



// 当使用预编译的头时，需要使用此源文件，编译才能成功。
typedef IEKrnln( WINAPI* PFN_CreateEKrnlnInterface)( HMODULE hCurDllModule );

#ifdef __MEM_LOAD_DLL__
#define IEXT_SPACENAME  iext_space_mmloaddll
#define IEXT_SPACENAME_BEGIN  namespace IEXT_SPACENAME {
#define IEXT_SPACENAME_END  }

IEXT_SPACENAME_BEGIN

//************************************
// 函数名:  LoadLibrary
// 返回类型:   LPVOID
// 功能: 模拟LoadLibrary加载内存文件到进程中
// 参数1: LPVOID lpData    文件基址
// 参数2: BOOL IsExe    文件属性标志，TRUE表示exe文件，FALSE表示dll文件
//************************************
HMODULE MmLoadLibrary(LPCVOID lpData);

// 模拟GetProcAddress获取内存DLL的导出函数
// lpBaseAddress: 内存DLL文件加载到进程中的加载基址
// lpszFuncName: 导出函数的名字
// 返回值: 返回导出函数的的地址
FARPROC MmGetProcAddress(HMODULE lpBaseAddress, LPCSTR lpszFuncName);

// 释放从内存加载的DLL到进程内存的空间
// lpBaseAddress: 内存DLL数据按SectionAlignment大小对齐映射到进程内存中的内存基址
// 返回值: 成功返回TRUE，否则返回FALSE
BOOL MmFreeLibrary(HMODULE lpBaseAddress);

IEXT_SPACENAME_END

#endif


static inline LPCVOID GetELibStlDllData(int* size)
{

    static LPBYTE dll;
    static int retSize;
    if ( dll )
    {
        if ( size )
            *size = retSize;
        return dll;
    }

#if defined(__COMPILE_FNR) || defined(__E_STATIC_LIB)
    dll = GetELibStlFnrDllData(&retSize);
#else
    dll = GetELibStlFneDllData(&retSize);
#endif
    if ( size )*size = retSize;
    return dll;
}

static CLoadTempLibrary s_dll;


static inline PFN_CreateEKrnlnInterface GetEKrnlnEntry(HMODULE hModule, LPCVOID pData, int size, LPCWSTR dllFile)
{
    if ( !hModule )
    {
        std::string caption, text;
        char fmtText[1024];
        sprintf_s(fmtText, "改造扩展界面库一 %d.%d.%d", EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION);
        s_dll.chech_import((LPBYTE)pData, size, GetLastError(), text, dllFile);
        MessageBoxA(0, text.c_str(), caption.c_str(), MB_ICONERROR);
        exit(0);
        TerminateProcess(GetCurrentProcess(), 0);
        return 0;
    }
    PFN_CreateEKrnlnInterface pfn = (PFN_CreateEKrnlnInterface)GetProcAddress(hModule, "CreateIextInterface");
    if ( !pfn )
    {
        std::wstring caption;
        wchar_t fmtText[1024];

        swprintf_s(fmtText, L"改造扩展界面库一 %d.%d.%d", EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION);
        caption = fmtText;
        MessageBoxW(0, L"加载改造扩展界面库一Ex失败, 获取支持库信息失败\r\n"
                    L"请确认支持库文件是否被修改\r\n"
                    L"本支持库不支持xp, server2003, 以及以下版本的系统", caption.c_str(), MB_ICONERROR);
        exit(0);
        TerminateProcess(GetCurrentProcess(), 0);
        return 0;
    }
    return pfn;
}


#if defined(_DBG_LOCAL)
// 读入文件, 不支持超过4G的文件
inline int readFile(LPCWSTR file, std::string& data)
{
    FILE* f;
    errno_t err = _wfopen_s(&f, file, L"rb+");
    if (!f)
        return 0;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    data.resize(size);
    size = (long)fread_s(&data[0], size, 1, size, f);

    fclose(f);
    return size;
}

// 读入文件, 不支持超过4G的文件
inline int writeFile(LPCWSTR file, LPCVOID pData, int size)
{
    FILE* f;
    errno_t err = _wfopen_s(&f, file, L"wb+");
    if (!f)
        return 0;

    fseek(f, 0, SEEK_SET);
    int ret = (int)fwrite(pData, size, 1, f);
    fclose(f);
    return ret;
}

#endif

IEKrnln IextEntry()
{
#if defined(__COMPILE_FNR) || defined(__E_STATIC_LIB)
    s_dll.init(GetIextDllData, L"iext1.fnr.bbs.125.la");
#else
    s_dll.init(GetELibStlDllData, L"iext1.fne.bbs.125.la");
#endif

    int size = 0;
    PFN_CreateEKrnlnInterface pfn = 0;
    HMODULE hModule = 0;
    LPCVOID dll = 0;
    GetELibStlDllData(0);


#if defined(_DBG_LOCAL)
    const LPCWSTR _dll_file = L"I:\\cpp\\_git_works\\iext\\测试易语言源码\\iext_fne.dll";
    //const LPCWSTR _dll_file = L"C:\\Users\\n\\Desktop\\666\\iext_fne.dll";
    std::string _dll_data;
    readFile(_dll_file, _dll_data);
    hModule = LoadLibraryW(_dll_file);
    //hModule = LoadLibraryW(L"c:\\iext_fne.dll");
    pfn = GetEKrnlnEntry(hModule, _dll_data.c_str(), (int)_dll_data.size(), _dll_file);
#elif defined(__MEM_LOAD_DLL__)
    dll = GetIextDllData(&size);
    hModule = IEXT_SPACENAME::MmLoadLibrary(dll);
    if ( !hModule )
    {
        _str caption, text;
        caption.Format("改造扩展界面库一 %d.%d.%d", IEXT_MAJORVERSION, IEXT_MINORVERSION, IEXT_BUILDVERSION);
        s_dll.chech_import((LPBYTE)dll, size, GetLastError(), text, 0);
        MessageBoxA(0, text.c_str(), caption.c_str(), MB_ICONERROR);
        exit(0);
        TerminateProcess(GetCurrentProcess(), 0);
        return 0;
    }

    pfn = (PFN_CreateIextInterface)IEXT_SPACENAME::MmGetProcAddress(hModule, "CreateIextInterface");

    if ( !pfn )
    {
        // 加载失败就释放到临时目录, 然后正常加载
        hModule = s_dll.GetModule(&dll, &size);
        pfn = GetIextEntry(hModule, dll, size, s_dll.GetDllFile());
        if ( !pfn )
            return 0;
    }

    if ( !pfn )
    {
        wstr caption;
        caption.Format(L"改造扩展界面库一 %d.%d.%d", IEXT_MAJORVERSION, IEXT_MINORVERSION, IEXT_BUILDVERSION);
        MessageBoxW(0, L"加载改造扩展界面库一Ex失败, 获取支持库信息失败\r\n"
                    L"请确认支持库文件是否被修改\r\n"
                    L"本支持库不支持xp, server2003, 以及以下版本的系统", caption.c_str(), MB_ICONERROR);
        exit(0);
        TerminateProcess(GetCurrentProcess(), 0);
        return 0;
    }
#else
    //dll = GetIextDllData(&size);

    //hModule = (HMODULE)MemoryLoadLibrary(dll);
    //if(hModule )
    //    pfn = (PFN_GetNewInf)MemoryGetProcAddress(hModule, "CreateIextInterface");

    //if ( !pfn )
    //{
    //    hModule = MmLoadLibrary(dll);
    //    if ( hModule )  // 先内存加载
    //        pfn = (PFN_GetNewInf)MmGetProcAddress(hModule, "CreateIextInterface");
    //}
    if ( !pfn )
    {
        // 加载失败就释放到临时目录, 然后正常加载
        hModule = s_dll.GetModule(&dll, &size);
        LPCWSTR _dll_file = s_dll.GetDllFile();
        pfn = GetIextEntry(hModule, dll, size, _dll_file);
    }
#endif

    if ( !pfn )
        return 0;

    

    HMODULE hBase = 0;
    MEMORY_BASIC_INFORMATION mem = { 0 };
    if ( VirtualQuery(IextEntry, &mem, sizeof(mem)) )
    {
        hBase = (HMODULE)mem.AllocationBase;
    }
    if ( !hBase )
        hBase = GetModuleHandleW(0);

    return pfn(hBase);
}


#ifdef __MEM_LOAD_DLL__


IEXT_SPACENAME_BEGIN

#if 0
#define MSGBOX_SHOW(_0, _1, _2, _3) MessageBoxW(_0, _1, _2, _3)
#else
#define MSGBOX_SHOW(_0, _1, _2, _3) 
#endif

DWORD GetSizeOfImage(LPCVOID lpData);
BOOL MmMapFile(LPCVOID lpData, LPVOID lpBaseAddress);
BOOL DoRelocationTable(LPVOID lpBaseAddress);
BOOL DoImportTable(LPVOID lpBaseAddress);
BOOL SetImageBase(LPVOID lpBaseAddress);
BOOL CallDllMain(LPCVOID lpBaseAddress, BOOL IsExe);



//************************************
// 函数名:  LoadLibrary
// 返回类型:   LPVOID
// 功能: 模拟LoadLibrary加载内存文件到进程中
// 参数1: LPVOID lpData    文件基址
// 参数2: BOOL IsExe    文件属性标志，TRUE表示exe文件，FALSE表示dll文件
//************************************
HMODULE MmLoadLibrary(LPCVOID lpData)
{

    HMODULE lpBaseAddress = NULL;
    // 获取映像大小
    DWORD dwSizeOfImage = GetSizeOfImage(lpData);
    // 在进程中申请一个可读、可写、可执行的内存块
    lpBaseAddress = (HMODULE)VirtualAlloc((LPVOID)0, dwSizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if ( NULL == lpBaseAddress )
    {
        MSGBOX_SHOW(0, L"申请空间失败！", 0, 0);
        return NULL;
    }
    // 将申请的空间的数据全部置0
    RtlZeroMemory(lpBaseAddress, dwSizeOfImage);
    // 将内存DLL数据按映像对齐大小（SectionAlignment）映射到刚刚申请的内存中
    if ( FALSE == MmMapFile(lpData, lpBaseAddress) )
    {
        MSGBOX_SHOW(0, L"区段映射到内存失败!", 0, 0);
        return NULL;
    }


    // 修改PE文件的重定位表信息
    if ( FALSE == DoRelocationTable(lpBaseAddress) )
    {
        MSGBOX_SHOW(0, L"修复重定位失败!", 0, 0);
        return NULL;
    }


    // 填写PE文件的导入表信息
    if ( FALSE == DoImportTable(lpBaseAddress) )
    {
        MSGBOX_SHOW(0, L"导入表填写失败!", 0, 0);
        return NULL;
    }
    // 修改PE文件的加载基址IMAGE_NT_HEADERS.OptionalHeader.ImageBase
    if ( FALSE == SetImageBase(lpBaseAddress) )
    {
        MSGBOX_SHOW(0, L"修改加载机制失败!", 0, 0);
        return NULL;
    }
    // 调用DLL的入口函数DllMain,函数地址即为PE文件的入口点AddressOfEntryPoint
    if ( FALSE == CallDllMain(lpBaseAddress, false) )
    {
        MSGBOX_SHOW(0, L"调用入口函数失败!", 0, 0);
        return NULL;
    }
    return (HMODULE)lpBaseAddress;
}


// 模拟GetProcAddress获取内存DLL的导出函数
// lpBaseAddress: 内存DLL文件加载到进程中的加载基址
// lpszFuncName: 导出函数的名字
// 返回值: 返回导出函数的的地址
FARPROC MmGetProcAddress(HMODULE lpBaseAddress, LPCSTR lpszFuncName)
{
    FARPROC lpFunc = NULL;
    // 获取导出表
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)( (ULONG32)pDosHeader + pDosHeader->e_lfanew );
    PIMAGE_EXPORT_DIRECTORY pExportTable = (PIMAGE_EXPORT_DIRECTORY)( (DWORD)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress );
    // 获取导出表的数据
    PDWORD lpAddressOfNamesArray = (PDWORD)( (DWORD)pDosHeader + pExportTable->AddressOfNames );
    PCHAR lpFuncName = NULL;
    PWORD lpAddressOfNameOrdinalsArray = (PWORD)( (DWORD)pDosHeader + pExportTable->AddressOfNameOrdinals );
    WORD wHint = 0;
    PDWORD lpAddressOfFunctionsArray = (PDWORD)( (DWORD)pDosHeader + pExportTable->AddressOfFunctions );
    DWORD dwNumberOfNames = pExportTable->NumberOfNames;
    DWORD i = 0;
    // 遍历导出表的导出函数的名称, 并进行匹配
    for ( i = 0; i < dwNumberOfNames; i++ )
    {
        lpFuncName = (PCHAR)( (DWORD)pDosHeader + lpAddressOfNamesArray[i] );
        if ( 0 == ::_stricmp(lpFuncName, lpszFuncName) )
        {
            // 获取导出函数地址
            wHint = lpAddressOfNameOrdinalsArray[i];
            lpFunc = (FARPROC)( (DWORD)pDosHeader + lpAddressOfFunctionsArray[wHint] );
            break;
        }
    }
    return lpFunc;
}

// 释放从内存加载的DLL到进程内存的空间
// lpBaseAddress: 内存DLL数据按SectionAlignment大小对齐映射到进程内存中的内存基址
// 返回值: 成功返回TRUE，否则返回FALSE
BOOL MmFreeLibrary(HMODULE lpBaseAddress)
{
    BOOL bRet = FALSE;
    if ( NULL == lpBaseAddress )
        return bRet;
    bRet = ::VirtualFree(lpBaseAddress, 0, MEM_RELEASE);
    lpBaseAddress = NULL;
    return bRet;
}



//************************************
// 函数名:  GetSizeOfImage
// 返回类型:   DWORD
// 功能: 获取文件映像大小
// 参数1: LPVOID lpData    文件基址
//************************************
DWORD GetSizeOfImage(LPCVOID lpData)
{
    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpData;
    //判断是否是有效的PE文件        0x5A4D
    if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE )
    {
        MSGBOX_SHOW(0, L"这不是一个PE文件!", 0, 0);
        return 0;
    }

    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );
    //判断是否是有效的PE文件        0x00004550
    if ( pNtHeader->Signature != IMAGE_NT_SIGNATURE )
    {
        MSGBOX_SHOW(0, L"这不是一个PE文件!", 0, 0);
        return 0;
    }

    //获取文件映像大小
    return pNtHeader->OptionalHeader.SizeOfImage;
}



//************************************
// 函数名:  MmMapFile
// 返回类型:   BOOL
// 功能: 将内存DLL数据按映像对齐大小（SectionAlignment）映射到刚刚申请的内存中
// 参数1: LPVOID lpData    文件基址
// 参数2: LPVOID lpBaseAddress    申请的内存的首地址
//************************************
BOOL MmMapFile(LPCVOID lpData, LPVOID lpBaseAddress)
{
    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpData;
    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );
    //获取所有头部+区段表的大小
    DWORD dwSizeOfHeaders = pNtHeader->OptionalHeader.SizeOfHeaders;
    //获取区段数量
    WORD wNumberOfSections = pNtHeader->FileHeader.NumberOfSections;
    //获取区段表数组的首元素
    PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
    //将头部（包括区段表）拷贝到内存
    RtlCopyMemory(lpBaseAddress, lpData, dwSizeOfHeaders);
    LPVOID lpSrcMem = NULL;
    LPVOID lpDestMem = NULL;
    DWORD dwSizeOfRawData = 0;
    const  int asdas = offsetof(IMAGE_SECTION_HEADER, Characteristics);
    //循环加载所有区段
    for ( WORD i = 0; i < wNumberOfSections; i++ )
    {
        //过滤掉无效区段
        if ( 0 == pSectionHeader->VirtualAddress || 0 == pSectionHeader->SizeOfRawData )
        {
            pSectionHeader++;
            continue;
        }
        //获取区段在文件中的位置
        lpSrcMem = (LPVOID)( (DWORD)lpData + pSectionHeader->PointerToRawData );
        //获取区段映射到内存中的位置
        lpDestMem = (LPVOID)( (DWORD)lpBaseAddress + pSectionHeader->VirtualAddress );
        //获取区段在文件中的大小
        dwSizeOfRawData = pSectionHeader->SizeOfRawData;
        //将区段数据拷贝到内存中
        RtlCopyMemory(lpDestMem, lpSrcMem, dwSizeOfRawData);
        //获取下一个区段头（属性）
        pSectionHeader++;
    }
    return TRUE;
}


//************************************
// 函数名:  DoRelocationTable
// 返回类型:   BOOL
// 功能: 修改PE文件的重定位表信息
// 参数1: LPVOID lpBaseAddress    映像对齐后的文件基址
//************************************
BOOL DoRelocationTable(LPVOID lpBaseAddress)
{
    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );
    //获取重定位表的地址
    PIMAGE_BASE_RELOCATION pReloc = (PIMAGE_BASE_RELOCATION)( (DWORD)pDosHeader +
                                                             pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress );

    //注意重定位表的位置可能和硬盘文件中的偏移地址不同，应该使用加载后的地址

    //判断是否有重定位表
    if ( (PVOID)pReloc == (PVOID)pDosHeader )
    {
        //没有重定位表
        return TRUE;
    }

    int nNumberOfReloc = 0;
    WORD* pRelocData = NULL;
    DWORD* pAddress = NULL;
    //开始修复重定位
    while ( pReloc->VirtualAddress != 0 && pReloc->SizeOfBlock != 0 )
    {
        //计算本区域（每一个描述了4KB大小的区域的重定位信息）需要修正的重定位项的数量
        nNumberOfReloc = ( pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION) ) / sizeof(WORD);

        for ( int i = 0; i < nNumberOfReloc; i++ )
        {
            //获取IMAGE_BASE_RELOCATION结构后面的数据的地址
            pRelocData = (WORD*)( (DWORD)pReloc + sizeof(IMAGE_BASE_RELOCATION) );

            //每个WORD由两部分组成，高4位指出了重定位的类型，WINNT.H中的一系列IMAGE_REL_BASED_xxx定义了重定位类型的取值。
            //大部分重定位属性值都是0x3
            //低12位是相对于IMAGE_BASE_RELOCATION中第一个元素VirtualAddress描述位置的偏移
            //找出需要修正的地址
            if ( (WORD)( pRelocData[i] & 0xF000 ) == 0x3000 )
            {
                //获取需要修正数据的地址,    按位与计算优先级比加减乘除低
                int offset = (int)pDosHeader - (int)pNtHeader->OptionalHeader.ImageBase;
                DWORD addrOffset = pReloc->VirtualAddress + ( pRelocData[i] & 0x0FFF );
                pAddress = (DWORD*)( (DWORD)pDosHeader + addrOffset );
                //进行修改
                *pAddress += (DWORD)offset;
            }

        }
        //下一个重定位块
        pReloc = (PIMAGE_BASE_RELOCATION)( (DWORD)pReloc + pReloc->SizeOfBlock );
    }
    return TRUE;
}



//************************************
// 函数名:  DoImportTable
// 返回类型:   BOOL
// 功能: 填写PE文件的导入表信息
// 参数1: LPVOID lpBaseAddress    映像对齐后的文件基址
//************************************
BOOL DoImportTable(LPVOID lpBaseAddress)
{
    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );
    //获取导入表地址
    PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)( (DWORD)pDosHeader +
                                                                  pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress );

    char* pDllName = 0;
    HMODULE hDll = NULL;
    PIMAGE_THUNK_DATA pIat = NULL;
    FARPROC pFuncAddress = NULL;
    PIMAGE_IMPORT_BY_NAME pImportByName = NULL;

    //循环遍历导入表
    while ( pImport->Name )
    {
        //获取导入表中的Dll名称
        pDllName = (char*)( (DWORD)pDosHeader + pImport->Name );
        //检索Dll模块获取模块句柄
        hDll = GetModuleHandleA(pDllName);
        //获取失败
        if ( NULL == hDll )
        {
            //加载Dll模块获取模块句柄
            hDll = LoadLibraryA(pDllName);
            //加载失败
            if ( NULL == hDll )
            {
                pImport++;
                continue;
            }
        }

        //获取IAT
        pIat = (PIMAGE_THUNK_DATA)( (DWORD)pDosHeader + pImport->FirstThunk );

        //遍历IAT中函数
        while ( pIat->u1.Ordinal )
        {
            //判断导入的函数是名称导入还是序号导入
            //判断最高位是否为1，如果是1那么是序号导入
            if ( pIat->u1.Ordinal & 0x80000000 )
            {
                //获取函数地址
                pFuncAddress = GetProcAddress(hDll, (LPCSTR)( pIat->u1.Ordinal & 0x7FFFFFFF ));

            }
            //名称导入
            else
            {
                //获取IMAGE_IMPORT_BY_NAME结构
                pImportByName = (PIMAGE_IMPORT_BY_NAME)( (DWORD)pDosHeader + pIat->u1.AddressOfData );
                //获取函数地址
                pFuncAddress = GetProcAddress(hDll, (LPCSTR)pImportByName->Name);
            }
            //将函数地址填入到IAT中
            pIat->u1.Function = (DWORD)pFuncAddress;
            pIat++;
        }
        pImport++;
    }

    return TRUE;
}




//************************************
// 函数名:  SetImageBase
// 返回类型:   BOOL
// 功能: 修改PE文件的加载基址IMAGE_NT_HEADERS.OptionalHeader.ImageBase
// 参数1: LPVOID lpBaseAddress    映像对齐后的文件基址
//************************************
BOOL SetImageBase(LPVOID lpBaseAddress)
{
    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );
    //修改默认加载基址
    pNtHeader->OptionalHeader.ImageBase = (DWORD)lpBaseAddress;
    return TRUE;
}



//************************************
// 函数名:  CallDllMain
// 返回类型:   BOOL
// 功能: 调用PE文件的入口函数
// 参数1: LPVOID lpBaseAddress    映像对齐后的文件基址
// 参数2: BOOL IsExe    文件属性标志，TRUE表示exe文件，FALSE表示dll文件
//************************************
BOOL CallDllMain(LPCVOID lpBaseAddress, BOOL IsExe)
{
    typedef BOOL(APIENTRY* typedef_DllMain)( HMODULE hModule,
                                            DWORD  ul_reason_for_call,
                                            LPVOID lpReserved
                                            );
    //定义函数指针变量
    typedef_DllMain DllMain = NULL;
    //typedef_wWinMain MyWinMain = NULL;

    //获取Dos头
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
    //获取NT头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)( (DWORD)pDosHeader + pDosHeader->e_lfanew );

    BOOL bRet = TRUE;
    //如果是exe文件
    if ( IsExe )
    {
        //MSGBOX_SHOW(0, L"有问题，待解决", 0, 0);
        //MyWinMain = (typedef_wWinMain)((DWORD)pDosHeader + pNtHeader->OptionalHeader.AddressOfEntryPoint+0xF8D);
        //bRet = MyWinMain((HINSTANCE)lpBaseAddress, NULL, NULL, SW_SHOWNORMAL);
    }
    //dll 文件
    else
    {
        DllMain = (typedef_DllMain)( (DWORD)pDosHeader + pNtHeader->OptionalHeader.AddressOfEntryPoint );
        //调用入口函数，附加进程DLL_PROCESS_ATTACH
        bRet = DllMain((HINSTANCE)lpBaseAddress, DLL_PROCESS_ATTACH, NULL);
    }
    return bRet;
}

IEXT_SPACENAME_END

#endif