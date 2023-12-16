#include "version_winos.h"
#include <string>
#include <vector>
#include <wincrypt.h>
#include <time.h>


// 加载临时目录dll类, 支持库使用, 功能写在dll里, 支持库加载dll, 这个文件是vc6使用, 需要兼容vc6
typedef LPCVOID(__cdecl* PFN_GetDllData)( int* size );
class CLoadTempLibrary
{
#define __ADD_L____1(s) L ## s
#define __ADD_L____2(s) __ADD_L____1(s)
#define __FILE__W__ __ADD_L____2(__FILE__)

private:
    HMODULE         hModule;        // 加载的模块句柄
    std::wstring    dllFile;        // 模块路径, 析构时会删除这个文件, 只删除, 不管是否删除成功
    PFN_GetDllData  pfn_GetDllData; // 获取dll数据的函数
    LPCWSTR         dllName;        // 写出的dll名字, 临时目录 + dll名字
public:
    CLoadTempLibrary() :hModule(0), pfn_GetDllData(0), dllName(0) { ; }
    void init(PFN_GetDllData pfn, LPCWSTR name)
    {
        dllName = name;
        pfn_GetDllData = pfn;
        if ( !dllName || !dllName[0] || !pfn_GetDllData )
            throw;  // 不支持传递空名字和空函数
    }
    inline LPCWSTR GetDllFile()
    {
        return dllFile.c_str();
    }
    ~CLoadTempLibrary()
    {
        if ( !hModule )return;
        FreeLibrary(hModule);
        hModule = 0;
        DeleteFileW(dllFile.c_str());   // 删除文件, 不管删除是否成功, 其他文件如果有使用, 那会删除失败
    }
    
    
    
    inline HMODULE GetModule(LPCVOID* pDll = 0, int* pSize = 0)
    {
        if (hModule)return hModule;
        wchar_t tempFile[260];
        dllFile.resize(260);
        GetTempPathW(260, tempFile);
        dllFile.assign(tempFile).append(dllName);

        bool reLoad = true;
        int size = 0;
        LPCVOID dll = pfn_GetDllData(&size);
        if ( pDll  ) *pDll = dll;
        if ( pSize ) *pSize = size;
        


        if ( fnPathFileExistsW(dllFile.c_str()) )
        {
            //TODO 这里需要判断临时目录的DLL是否能使用, 看是获取程序段数据还是加载dll获取版本, 判断MD5是最简单的方法
            
            // 读入
            const DWORD dwDesiredAccess = GENERIC_READ;
            const DWORD dwCreationDisposition = OPEN_EXISTING;
            const DWORD dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
            HANDLE hFile = CreateFileW(dllFile.c_str(),
                dwDesiredAccess,
                dwShareMode,
                0,
                dwCreationDisposition,
                FILE_ATTRIBUTE_NORMAL,
                0);

            if (hFile != INVALID_HANDLE_VALUE)
            {
                int oldSize = GetFileSize(hFile, NULL);
                if ( oldSize > 0 )
                {
                    LPBYTE pOldData = new BYTE[oldSize];
                    wchar_t newMd5[65], oldMd5[65];
                    DWORD dwNumOfByteRead = 0;
                    if (ReadFile(hFile, pOldData, size, &dwNumOfByteRead, 0))
                    {
                        _GetMd5(dll, size, newMd5);
                        _GetMd5(pOldData, oldSize, oldMd5);
                        if ( memcmp(newMd5, oldMd5, 16) == 0 )
                            reLoad = false;
                    }
                    delete[] pOldData;
                }
                CloseHandle(hFile);
            }
            // 否则条件这里不写, 如果打开文件失败, 那下面会创建一个随机名字, 再次写出

        }

        if ( reLoad )
        {
            // 重写
            const DWORD dwDesiredAccess = GENERIC_WRITE;
            const DWORD dwCreationDisposition = CREATE_ALWAYS;
            const DWORD dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

            HANDLE hFile = CreateFileW(dllFile.c_str(),
                dwDesiredAccess,
                dwShareMode,
                0,
                dwCreationDisposition,
                FILE_ATTRIBUTE_NORMAL,
                0);

            if ( hFile == INVALID_HANDLE_VALUE)
            {
                // 打开失败, 弄一个新的随机文件名, 然后再次打开
                srand((unsigned int)time(0));
                dllFile.append(randStr(20));
                hFile = CreateFileW(dllFile.c_str(),
                    dwDesiredAccess,
                    dwShareMode,
                    0,
                    dwCreationDisposition,
                    FILE_ATTRIBUTE_NORMAL,
                    0);
            }

            // 利用 或 条件的特性, 第一个条件成立就不会走第二个条件, 打开失败就不会执行写入, 打开成功就判断写入是否成功
            DWORD h = 0;
            if (hFile == INVALID_HANDLE_VALUE || WriteFile(hFile, dll, size, &h, NULL) == FALSE)
            {
                // 都失败, 那就不继续运行了
                int err = GetLastError();
                CloseHandle(hFile);
                wchar_t str[260];
                const wchar_t* const fmtStr = L"没有临时目录读写权限, 写出文件失败\n运行本程序需要临时目录读写权限, 请尝试以管理员权限打开本程序\n错误码 = %d";
                swprintf(str, fmtStr, err);
                MessageBoxW(0, str, L"程序出现致命错误", 0);
                TerminateProcess(GetCurrentProcess(), 0);
                exit(0);
                return 0;
            }

            CloseHandle(hFile);
        }
        hModule = LoadLibraryW(dllFile.c_str());
        return hModule;
    }


    // 从动态库里获取函数地址
    inline void* GetAddrProc(LPCSTR name)
    {
        if (!GetModule()) return 0;
        return GetProcAddress(hModule, name);
    }

private:

    inline static BOOL _GetMd5(LPCVOID pData, int size, wchar_t MD5[33])
    {
        MD5[0] = 0;
        if ( !pData || !size ) return false;
        HCRYPTPROV hProv = NULL;
        HCRYPTPROV hHash = NULL;
        BOOL retVl = false;

        do
        {
            if ( !CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) )
                break;       //获得CSP中一个密钥容器的句柄

            //初始化对数据流的hash, 创建并返回一个与CSP的hash对象相关的句柄。这个句柄接下来将被    CryptHashData调用。

            if ( !CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) )
                break;

            if ( !CryptHashData(hHash, (LPBYTE)pData, size, 0) )
                break;      //hash文件  


            unsigned char* pbHash;
            DWORD dwHashLen = sizeof(DWORD);
            if ( !CryptGetHashParam(hHash, HP_HASHVAL, NULL, &dwHashLen, 0) )
                break; //我也不知道为什么要先这样调用CryptGetHashParam, 这块是参照的msdn       

            pbHash = (unsigned char*)malloc(dwHashLen);
            if ( !pbHash )
                break;
            
            retVl = CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0);    //获得md5值 
            if ( retVl )
            {
                if ( dwHashLen >= 16 )
                {
                    memcpy(MD5, pbHash, 16);
                }
                else
                {
                    memcpy(MD5, pbHash, dwHashLen);
                    for ( DWORD i = dwHashLen; i < 16; i++ )
                        MD5[i] = 0;
                }
                MD5[16] = 0;
            }
            free(pbHash);
        } while ( false );

        //善后工作
        if ( hHash )
            CryptDestroyHash(hHash);
        if ( hProv )
            CryptReleaseContext(hProv, 0);

        return retVl;
    }
    
    inline bool check_dos_nt(LPBYTE pData)
    {
        if ( !pData ) return false;
        LPBYTE base = pData;
        PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)pData;
        if ( dos->e_magic != IMAGE_DOS_SIGNATURE )
            return false;
        PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)( base + dos->e_lfanew );
        if ( nt->Signature != IMAGE_NT_SIGNATURE || ( nt->FileHeader.Machine & IMAGE_FILE_MACHINE_I386 ) == 0 )
            return false;
        return true;
    }

    inline LPBYTE MmMapFile(LPCVOID lpData, std::string& dllData)
    {
        LPBYTE base = (LPBYTE)lpData;
        if ( !check_dos_nt(base) )
            return 0;

        PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
        PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)( base + dos->e_lfanew );

        DWORD dwSizeOfHeaders = nt->OptionalHeader.SizeOfHeaders;   // 获取所有头部+区段表的大小
        WORD wNumberOfSections = nt->FileHeader.NumberOfSections;   // 获取区段数量
        PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(nt);   // 获取区段表数组的首元素
        dllData.resize(nt->OptionalHeader.SizeOfImage);
        LPBYTE lpBaseAddress = (LPBYTE)dllData.data();


        memcpy(lpBaseAddress, lpData, dwSizeOfHeaders); // 将头部, 包括区段表, 拷贝到内存
        LPVOID lpSrcMem = NULL;
        LPVOID lpDestMem = NULL;

        //循环加载所有区段
        for ( WORD i = 0; i < wNumberOfSections; i++ )
        {
            //过滤掉无效区段
            if ( 0 == pSection->VirtualAddress || 0 == pSection->SizeOfRawData )
            {
                pSection++;
                continue;
            }

            lpSrcMem = (LPVOID)( (DWORD)lpData + pSection->PointerToRawData );          // 获取区段在文件中的位置
            lpDestMem = (LPVOID)( (DWORD)lpBaseAddress + pSection->VirtualAddress );    // 获取区段映射到内存中的位置

            memcpy(lpDestMem, lpSrcMem, pSection->SizeOfRawData);   // 将区段数据拷贝到内存中

            pSection++; // 获取下一个区段头
        }
        return lpBaseAddress;
    }

public:
    inline void chech_import(LPBYTE pData, int size, int err, std::string& dbgText, LPCWSTR dllFile)
    {
        std::string dllData;
        dbgText.reserve(0x1000);
        dbgText.clear();
        char fmtBuffer[1024];
        DRIVER_GETVERSION_STRUCT ver = { 0 };
        WIN_VER_DETAIL type = GetWindowsVersion(&ver);
        if ( type != WINDOWS_VERSION_NONE )
        {
            LPCSTR fmt = "加载\"%s\"失败\r\n错误码 = %d\r\n"
                "系统版本: MajorVersion = %d, MinorVersion = %d, BuildNumber = %d, ProductType = %d\r\n"
                "操作系统名称为: %s\r\n详细失败信息如下:\r\n\r\n";
            if ( !dllFile || !dllFile[0] )
            {
                fmt = "加载DLL失败\r\n"
                    "系统版本: MajorVersion = %d, MinorVersion = %d, BuildNumber = %d, ProductType = %d\r\n"
                    "操作系统名称为: %s\r\n详细失败信息如下:\r\n\r\n";
                sprintf_s(fmtBuffer, fmt, ver.dwMajorVersion, ver.dwMinorVersion, ver.dwBuildNumber, ver.wProductType, GetVersionStringA(type));
 
            }
            else
            {
                std::string a = __W2A(dllFile);
                sprintf_s(fmtBuffer, fmt, a.c_str(), err,
                                     ver.dwMajorVersion, ver.dwMinorVersion, ver.dwBuildNumber, ver.wProductType, GetVersionStringA(type));
            }
            dbgText.append(fmtBuffer);

        }
        else if ( dllFile )
        {
            std::string a = __W2A(dllFile);
            sprintf_s(fmtBuffer,
                "加载\"%s\"失败\r\n错误码 = %d, 详细失败信息如下:\r\n\r\n",
                a.c_str(), err);
        }

        dbgText.append("该支持库不支持此系统, 缺少以下dll或者dll中的函数\r\n");
        LPBYTE base = MmMapFile(pData, dllData);
        if ( !base )
            return;

        PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
        PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)( base + dos->e_lfanew );
        PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)( base + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress );
        bool isFree = false;
        std::vector<std::string> arr;
        arr.reserve(100);
        arr.resize(0);

        while ( pImport->Name )
        {
            LPCSTR pDllName = (LPCSTR)( base + pImport->Name );
            if ( *pDllName == 0 )
            {
                pImport++;
                continue;
            }
            isFree = false;
            HMODULE hModule = GetModuleHandleA(pDllName);
            if ( !hModule )
            {
                hModule = LoadLibraryA(pDllName);
                isFree = hModule != 0;
            }


            arr.resize(0);
            PIMAGE_THUNK_DATA pIat = (PIMAGE_THUNK_DATA)( base + pImport->FirstThunk );
            //IAT表个数不确定，最后一项以全为0结尾
            while ( pIat->u1.Ordinal )
            {
                // 判断是否名称导出还是序号导出
                // 通过最高位是否为1, 如果为1, 那么序号导出
                // 如果为0, 名称导出
                LPCSTR pszFunName = 0;
                if ( pIat->u1.Ordinal & 0x80000000 )
                {
                    // 最高位为1, 序号导入
                    pszFunName = (LPCSTR)( pIat->u1.Ordinal & 0xFFFF );
                }
                else
                {
                    //最高位位0, 名称导入
                    //显示序号, 和名称
                    PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)( base + pIat->u1.AddressOfData );
                    pszFunName = (LPCSTR)&pName->Name[0];
                }

                if ( !hModule || GetProcAddress(hModule, pszFunName) == 0 )
                {
                    // 获取这个函数失败, 缺少这个函数, 缺少的才加入到数组里
                    const LPCSTR fmt = ( (DWORD)pszFunName <= 0xffff ? "函数索引: %d" : "%s" );
                    sprintf_s(fmtBuffer, fmt, pszFunName);
                    arr.push_back(fmtBuffer);
                }

                pIat++;
            }

            int count = arr.size();
            if ( count > 0 )
            {
                if ( !hModule )
                {
                    dbgText.append("缺少dll: ").append(pDllName).append("\r\n");
                }
                else
                {
                    dbgText.append("缺少 ").append(pDllName).append(" 中的以下函数:\r\n");

                    for ( int i = 0; i < count; i++ )
                    {
                        dbgText.append("        ").append(arr[i]).append("\r\n");
                    }
                }
                dbgText.append("\r\n");
                arr.resize(0);
            }

            pImport++;
        }

    }

private:
    inline static BOOL fnPathFileExistsW(LPCWSTR file)
    {
        typedef BOOL(WINAPI* PFN_PathFileExistsW)(LPCWSTR pszPath);
        static PFN_PathFileExistsW pFun;
        if (!pFun)
        {
            HMODULE hModule = LoadLibraryW(L"Shlwapi.dll");
            if (!hModule)
                return false;
            pFun = (PFN_PathFileExistsW)GetProcAddress(hModule, "PathFileExistsW");
            if (!pFun)
                return false;
        }
        return pFun(file);
    }

    // 取指定数量的随机字符
    static std::wstring randStr(const size_t _count)
    {
        std::wstring str;
        str.resize(_count);
        LPWSTR p = &str[0];

        const int bufferSize = 62;
        const LPCWSTR buffer = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (size_t i = 0; i < _count; i++)
        {
            int r = __rand(0, bufferSize);
            p[i] = buffer[r];
        }
        return str;
    }
    inline static int __rand(int min, int max)
    {
        return (::rand() % (max - min + 1)) + min;
    }
    inline static std::string __W2A(LPCWSTR str, int len = 0, int cp = 936)
    {
        if (!str)return std::string();
        if (len <= 0)len = (int)wcslen(str);
        if (len <= 0)return std::string();
        int aLen = WideCharToMultiByte(cp, 0, str, (int)len, 0, 0, 0, 0) + 1;
        if (aLen < 1) return std::string();

        std::string ret;
        ret.resize(aLen);
        LPSTR szStr = &ret[0];
        memset(szStr, 0, aLen);
        aLen = WideCharToMultiByte(cp, 0, str, (int)len, szStr, aLen, 0, 0);
        ret.resize(aLen);
        return ret;
    }
};

