#pragma warning(disable: 4996) 
#pragma once
#include <windows.h>

typedef enum WIN_VER_DETAIL
{

    WINDOWS_VERSION_NONE,               // 不确定的版本
    WINDOWS_VERSION_SERVER_2022,        // 10.0, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2019,        // 10.0, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2016,        // 10.0, wProductType != VER_NT_WORKSTATION
    WINDOWS_VERSION_11,                 // 10.0, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_10,                 // 10.0, wProductType == VER_NT_WORKSTATION

    WINDOWS_VERSION_8_1,                // 6.3, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2012_R2,     // 6.3, wProductType != VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2012,        // 6.2, wProductType != VER_NT_WORKSTATION
    WINDOWS_VERSION_8,                  // 6.2, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2008_R2,     // 6.1, wProductType != VER_NT_WORKSTATION
    WINDOWS_VERSION_7,                  // 6.1, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_SERVER_2008,        // 6.0, wProductType != VER_NT_WORKSTATION
    WINDOWS_VERSION_VISTA,              // 6.0, wProductType == VER_NT_WORKSTATION

    WINDOWS_VERSION_SERVER_2003,        // 5.2
    WINDOWS_VERSION_HOMESERVER,         // 5.2, wSuiteMask == VER_SUITE_WH_SERVER
    WINDOWS_VERSION_2003,               // 5.2
    WINDOWS_VERSION_2003_SP1_SP2,       // 5.2
    WINDOWS_VERSION_XP_X64,             // 5.2, wProductType == VER_NT_WORKSTATION
    WINDOWS_VERSION_XP,                 // 5.1
    WINDOWS_VERSION_2000,               // 5.0

    WINDOWS_VERSION_7_7600_UP,
    WINDOWS_VERSION_7_7000,
    WINDOWS_VERSION_10_15063,/* win10 1703 */
    WINDOWS_VERSION_10_16299,/* win10 1709 */
    WINDOWS_VERSION_10_17134,/* win10 1803 */
    WINDOWS_VERSION_10_17763,/* win10 1809 */
    WINDOWS_VERSION_10_18362,/* win10 1903 */
    WINDOWS_VERSION_10_18363,/* win10 1909 */
    WINDOWS_VERSION_10_19041_UP/* win10 大于等于2004版本 */

} WIN_VER_DETAIL;




typedef LONG(NTAPI* PFN_RtlGetVersion)( PRTL_OSVERSIONINFOW lpVersionInformation );
// 系统版本输出缓冲区
typedef struct _tagDRIVER_GETVERSION_STRUCT
{
    ULONG           dwMajorVersion;     // 系统主版本号
    ULONG           dwMinorVersion;     // 系统次版本号
    ULONG           dwBuildNumber;      // 系统编译版本号
    ULONG           wProductType;       // 
    ULONG           version;            // 版本
}DRIVER_GETVERSION_STRUCT, * PDRIVER_GETVERSION_STRUCT;


#define _GET_VERSION_STRING_CONST_(_type, _L, _name)\
inline _type _name(WIN_VER_DETAIL ver)\
{\
    _type verName = _L##"";\
    switch ( ver )\
    {\
    case WINDOWS_VERSION_SERVER_2022:\
        verName = _L##"Server2022";\
        break;\
    case WINDOWS_VERSION_SERVER_2019:\
        verName = _L##"Server2019";\
        break;\
    case WINDOWS_VERSION_SERVER_2016:\
        verName = _L##"Server2016";\
        break;\
    case WINDOWS_VERSION_11:\
        verName = _L##"Windows 11";\
        break;\
    case WINDOWS_VERSION_10:\
        verName = _L##"Windows 10";\
        break;\
    case WINDOWS_VERSION_8_1:\
        verName = _L##"Windows 8.1";\
        break;\
    case WINDOWS_VERSION_SERVER_2012_R2:\
        verName = _L##"Server2012 R2";\
        break;\
    case WINDOWS_VERSION_SERVER_2012:\
        verName = _L##"Server2012";\
        break;\
    case WINDOWS_VERSION_8:\
        verName = _L##"Windows 8";\
        break;\
    case WINDOWS_VERSION_SERVER_2008_R2:\
        verName = _L##"Server2008 R2";\
        break;\
    case WINDOWS_VERSION_7:\
        verName = _L##"Windows 7";\
        break;\
    case WINDOWS_VERSION_SERVER_2008:\
        verName = _L##"Server2008";\
        break;\
    case WINDOWS_VERSION_VISTA:\
        verName = _L##"Windows Vista";\
        break;\
    case WINDOWS_VERSION_SERVER_2003:\
        verName = _L##"Server2003";\
        break;\
    case WINDOWS_VERSION_HOMESERVER:\
        verName = _L##"Windows Home Server";\
        break;\
    case WINDOWS_VERSION_2003:\
        verName = _L##"Windows 2003";\
        break;\
    case WINDOWS_VERSION_2003_SP1_SP2:\
        verName = _L##"Windows 2003 SP1 SP2";\
        break;\
    case WINDOWS_VERSION_XP_X64:\
        verName = _L##"Windows XP64";\
        break;\
    case WINDOWS_VERSION_XP:\
        verName = _L##"Windows XP";\
        break;\
    case WINDOWS_VERSION_2000:\
        verName = _L##"Windows 2000";\
        break;\
    case WINDOWS_VERSION_7_7600_UP:\
        verName = _L##"Windows 7 7600";\
        break;\
    case WINDOWS_VERSION_7_7000:\
        verName = _L##"Windows 7 7000";\
        break;\
    case WINDOWS_VERSION_10_15063:\
        verName = _L##"Windows 10 15063";\
        break;\
    case WINDOWS_VERSION_10_16299:\
        verName = _L##"Windows 10 16299";\
        break;\
    case WINDOWS_VERSION_10_17134:\
        verName = _L##"Windows 10 17134";\
        break;\
    case WINDOWS_VERSION_10_17763:\
        verName = _L##"Windows 10 17763";\
        break;\
    case WINDOWS_VERSION_10_18362:\
        verName = _L##"Windows 10 18362";\
        break;\
    case WINDOWS_VERSION_10_18363:\
        verName = _L##"Windows 10 18363";\
        break;\
    case WINDOWS_VERSION_10_19041_UP:\
        verName = _L##"Windows 10 19041";\
        break;\
    default:\
        verName = _L##"未知版本";\
        break;\
    }\
    return verName;\
}

_GET_VERSION_STRING_CONST_(LPCSTR, IN, GetVersionStringA)
_GET_VERSION_STRING_CONST_(LPCWSTR, L, GetVersionStringW)



inline LPCWSTR GetVersionString(WIN_VER_DETAIL ver)
{
    LPCWSTR verName = L"";
    switch ( ver )
    {
    case WINDOWS_VERSION_SERVER_2022:
        verName = L"Server2022";
        break;
    case WINDOWS_VERSION_SERVER_2019:
        verName = L"Server2019";
        break;
    case WINDOWS_VERSION_SERVER_2016:
        verName = L"Server2016";
        break;
    case WINDOWS_VERSION_11:
        verName = L"Windows 11";
        break;
    case WINDOWS_VERSION_10:
        verName = L"Windows 10";
        break;
    case WINDOWS_VERSION_8_1:
        verName = L"Windows 8.1";
        break;
    case WINDOWS_VERSION_SERVER_2012_R2:
        verName = L"Server2012 R2";
        break;
    case WINDOWS_VERSION_SERVER_2012:
        verName = L"Server2012";
        break;
    case WINDOWS_VERSION_8:
        verName = L"Windows 8";
        break;
    case WINDOWS_VERSION_SERVER_2008_R2:
        verName = L"Server2008 R2";
        break;
    case WINDOWS_VERSION_7:
        verName = L"Windows 7";
        break;
    case WINDOWS_VERSION_SERVER_2008:
        verName = L"Server2008";
        break;
    case WINDOWS_VERSION_VISTA:
        verName = L"Windows Vista";
        break;
    case WINDOWS_VERSION_SERVER_2003:
        verName = L"Server2003";
        break;
    case WINDOWS_VERSION_HOMESERVER:
        verName = L"Windows Home Server";
        break;
    case WINDOWS_VERSION_2003:
        verName = L"Windows 2003";
        break;
    case WINDOWS_VERSION_2003_SP1_SP2:
        verName = L"Windows 2003 SP1 SP2";
        break;
    case WINDOWS_VERSION_XP_X64:
        verName = L"Windows XP64";
        break;
    case WINDOWS_VERSION_XP:
        verName = L"Windows XP";
        break;
    case WINDOWS_VERSION_2000:
        verName = L"Windows 2000";
        break;
    case WINDOWS_VERSION_7_7600_UP:
        verName = L"Windows 7 7600";
        break;
    case WINDOWS_VERSION_7_7000:
        verName = L"Windows 7 7000";
        break;
    case WINDOWS_VERSION_10_15063:
        verName = L"Windows 10 15063";
        break;
    case WINDOWS_VERSION_10_16299:
        verName = L"Windows 10 16299";
        break;
    case WINDOWS_VERSION_10_17134:
        verName = L"Windows 10 17134";
        break;
    case WINDOWS_VERSION_10_17763:
        verName = L"Windows 10 17763";
        break;
    case WINDOWS_VERSION_10_18362:
        verName = L"Windows 10 18362";
        break;
    case WINDOWS_VERSION_10_18363:
        verName = L"Windows 10 18363";
        break;
    case WINDOWS_VERSION_10_19041_UP:
        verName = L"Windows 10 19041";
        break;
    default:
        verName = L"未知版本";
        break;
    }
    return verName;
}


inline WIN_VER_DETAIL GetWindowsVersion(PDRIVER_GETVERSION_STRUCT ver)
{
    static HMODULE hNt;
    if ( !hNt ) hNt = GetModuleHandleW(L"ntdll.dll");
    if ( !hNt )
    {
        MessageBoxW(0, L"出现致命错误", L"获取ntdll句柄失败", 0);
        return WINDOWS_VERSION_NONE;
    }

    RTL_OSVERSIONINFOEXW osverinfo = { sizeof(osverinfo) };
    typedef LONG(NTAPI* PFN_RtlGetVersion)( PRTL_OSVERSIONINFOW );
    PFN_RtlGetVersion pfnRtlGetVersion = (PFN_RtlGetVersion)GetProcAddress(hNt, "RtlGetVersion");
    if ( pfnRtlGetVersion )
    {
        pfnRtlGetVersion((PRTL_OSVERSIONINFOW)&osverinfo);
    }
    else
    {
        OSVERSIONINFOEXW osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if ( !GetVersionExW((OSVERSIONINFOW*)&osvi) )
            return WINDOWS_VERSION_NONE;

        typedef void( *RtlGetNtVersionNumbersType )( DWORD*, DWORD*, DWORD* );
        RtlGetNtVersionNumbersType RtlGetNtVersionNumbers = (RtlGetNtVersionNumbersType)GetProcAddress(hNt, "RtlGetNtVersionNumbers");
        RtlGetNtVersionNumbers(&osvi.dwMajorVersion, &osvi.dwMinorVersion, &osvi.dwBuildNumber);
        osverinfo.dwMajorVersion = osvi.dwMajorVersion;
        osverinfo.dwMinorVersion = osvi.dwMinorVersion;
        osverinfo.dwBuildNumber = osvi.dwBuildNumber;
        osverinfo.wProductType = osvi.wProductType;
    }

    if ( ver )
    {
        ver->dwMajorVersion = osverinfo.dwMajorVersion;
        ver->dwMinorVersion = osverinfo.dwMinorVersion;
        ver->dwBuildNumber = osverinfo.dwBuildNumber;
        ver->wProductType = osverinfo.wProductType;
    }

    //根据获得的版本号情况，返回结果
    if ( osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 0 )
    {
        return WINDOWS_VERSION_2000;
    }
    else if ( osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 1 )
    {
        return WINDOWS_VERSION_XP;
    }
    else if ( osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 2 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_XP_X64;
#if _MSC_VER < 1201
#define VER_SUITE_WH_SERVER 0x00008000
#endif
        if ( osverinfo.wSuiteMask == VER_SUITE_WH_SERVER )
            return WINDOWS_VERSION_HOMESERVER;
        if ( osverinfo.wServicePackMajor == 0 )
            return WINDOWS_VERSION_2003;
        return WINDOWS_VERSION_2003_SP1_SP2;
    }
    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 0 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_VISTA;
        if ( osverinfo.wProductType != VER_NT_WORKSTATION )
            return WINDOWS_VERSION_SERVER_2008;
    }
    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 1 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_7;
        if ( osverinfo.wProductType != VER_NT_WORKSTATION )
            return WINDOWS_VERSION_SERVER_2008_R2;
    }
    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 2 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_8;
        if ( osverinfo.wProductType != VER_NT_WORKSTATION )
            return WINDOWS_VERSION_SERVER_2012;
    }
    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 3 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_8_1;
        if ( osverinfo.wProductType != VER_NT_WORKSTATION )
            return WINDOWS_VERSION_SERVER_2012_R2;
    }
    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 )
    {
        if ( osverinfo.wProductType == VER_NT_WORKSTATION )
            return WINDOWS_VERSION_10;
        if ( osverinfo.wProductType != VER_NT_WORKSTATION )
            return WINDOWS_VERSION_SERVER_2016;
    }
    return WINDOWS_VERSION_NONE;


}

//
///* 获取系统版本 */
//WIN_VER_DETAIL GetWindowsVersion1()
//{
//    RTL_OSVERSIONINFOEXW    osverinfo;
//    WIN_VER_DETAIL WinVersion = WINDOWS_VERSION_NONE;
//
//    memset(&osverinfo, 0, sizeof(RTL_OSVERSIONINFOEXW));
//    osverinfo.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);
//
//    if ( RtlGetVersion((RTL_OSVERSIONINFOW*)&osverinfo) != STATUS_SUCCESS )
//    {
//        return WINDOWS_VERSION_NONE;
//    }
//    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 1 && osverinfo.dwBuildNumber == 7000 )
//    {
//        WinVersion = WINDOWS_VERSION_7_7000;
//    }
//    else if ( osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 1 && osverinfo.dwBuildNumber >= 7600 )
//    {
//        WinVersion = WINDOWS_VERSION_7_7600_UP;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 15063 )
//    {
//        WinVersion = WINDOWS_VERSION_10_15063;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 16299 )
//    {
//        WinVersion = WINDOWS_VERSION_10_16299;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 17134 )
//    {
//        WinVersion = WINDOWS_VERSION_10_17134;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 17763 )
//    {
//        WinVersion = WINDOWS_VERSION_10_17763;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 18362 )
//    {
//        WinVersion = WINDOWS_VERSION_10_18362;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber == 18363 )
//    {
//        WinVersion = WINDOWS_VERSION_10_18363;
//    }
//    else if ( osverinfo.dwMajorVersion == 10 && osverinfo.dwMinorVersion == 0 && osverinfo.dwBuildNumber >= 19041 )
//    {
//        WinVersion = WINDOWS_VERSION_10_19041_UP;
//    }
//    //kprintf("WinVersion: dwMajorVersion=%d; dwMinorVersion=%d; dwBuildNumber=%d;\n", osverinfo.dwMajorVersion, osverinfo.dwMinorVersion, osverinfo.dwBuildNumber);
//    return WinVersion;
//}



