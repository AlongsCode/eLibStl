#ifndef _HEXVIEW_HELP_H
#define _HEXVIEW_HELP_H

#include "HexView_Control.h"
#include <unordered_map>
#include <unordered_set>
#include "../../include/ElibHelp.h"

HEXVIEW_NAMESPACE_BEGIN

HUNIT GethUnitFromId(DWORD dwWinFormID, DWORD dwUnitID, PVOID* pRet);
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID* pRet);
PVOID GetDataFromHunit(HUNIT hUnit);
PVOID UpdateDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, HWND hWnd, PVOID pData);
PVOID SetDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, HWND hWnd, PVOID pData);

// 读取数据, 返回读取后的地址
inline LPBYTE read_data(LPBYTE& buf, LPVOID pData, int size)
{
    BYTE ret = ((BYTE*)buf)[0];
    memcpy(pData, buf, size);
    buf += size;
    return buf;
}
// 读取结构, 返回读取后的地址
template<typename T> inline LPBYTE read_struct(LPBYTE& buf, T& data)
{
    return read_data(buf, &data, sizeof(data));
}
inline BYTE read_int08(LPBYTE& buf)
{
    BYTE ret = ((BYTE*)buf)[0];
    buf += sizeof(BYTE);
    return ret;
}
inline WORD read_int16(LPBYTE& buf)
{
    WORD ret = ( (WORD*)buf )[0];
    buf += sizeof(WORD);
    return ret;
}
inline int read_int32(LPBYTE& buf)
{
    int ret = ( (LPINT)buf )[0];
    buf += sizeof(int);
    return ret;
}
inline UINT64 read_int64(LPBYTE& buf)
{
    UINT64 ret = ( (UINT64*)buf )[0];
    buf += sizeof(UINT64);
    return ret;
}

#define _DBG_BREAK_TOSTR1(_num) #_num
#define _DBG_BREAK_TOSTR2(_num) _DBG_BREAK_TOSTR1(_num)
#define _DBG_BREAK_MSG(_s) { MessageBoxA(0, "行数: " _DBG_BREAK_TOSTR2(__LINE__) "\r\n文件: " __FILE__ \
                                "\r\n看到此信息框请截图发给福仔\r\n\r\n点击确定后程序将触发异常, 如果没有调试器, 则程序会崩溃"\
                                , _s, 0); __debugbreak(); }


template<typename T>
inline void AddPtr(T& pInt, int size)
{
    pInt = (T)( ( (LPBYTE)pInt ) + size );
}


// 把数据写入缓冲区, 内部会判断是否越界, 越界后重新分配内存
// 写入后, pBuffer会增加nSize个字节, 返回写入的字节数
inline int write_data(std::vector<BYTE>& buffer, LPCVOID pData, int nSize)
{
    if ( nSize == 0 )
        return 0;
#ifdef _DEBUG
    if ( nSize < 0 )
        _DBG_BREAK_MSG("写入数据, 数据尺寸小于0");
#endif
    size_t size = buffer.size();
    buffer.resize(size + nSize);
    LPBYTE ptr = ( &buffer[0] ) + size;
    memcpy(ptr, pData, nSize);
    return nSize;
}

inline int write_int08(std::vector<BYTE>& buffer, BYTE number)
{
    return write_data(buffer, &number, sizeof(number));
}

inline int write_int16(std::vector<BYTE>& buffer, WORD number)
{
    return write_data(buffer, &number, sizeof(number));
}
// 写入整数
inline int write_int32(std::vector<BYTE>& buffer, int number)
{
    return write_data(buffer, &number, sizeof(number));
}
// 写入整数64
inline int write_int64(std::vector<BYTE>& buffer, ULONG64 number)
{
    return write_data(buffer, &number, sizeof(number));
}


// 把字体数据写出, 并调整指针, 返回增加的字节数, 最少会写入4个字节
inline int write_font(std::vector<BYTE>& buffer, LPLOGFONTA lf, int fontSize)
{
    int size = 4;
    write_int32(buffer, fontSize);    // 字体占用字节数
    if ( fontSize > 0 )
    {
        write_data(buffer, lf, fontSize);   // 写入字体数据
        size += fontSize;
    }
    return size;
}

// 把字符串写入缓冲区, 并把地址增加, 返回增加的字节数
inline int write_str_A(std::vector<BYTE>& buffer, LPCSTR pstr, size_t strLen = 0)
{
    if ( strLen == 0 )
        strLen = strlen(pstr);
    size_t len = strLen;  // 不包含结束的字节

    write_data(buffer, pstr, len);   // 这里把字符串写入, 不包含结束标志
    buffer.push_back(0);    // 写入结束标志, 1个字节0
    len++;
    return len;
}
// 把字符串写入缓冲区, 并把地址增加, 返回增加的字节数
inline int write_str_W(std::vector<BYTE>& buffer, LPCWSTR pstr, size_t strLen = 0)
{
    if ( !pstr )pstr = L"";
    if ( strLen == 0 )
        strLen = wcslen(pstr);
    size_t len = strLen * sizeof(wchar_t);  // 不包含结束的字节

    write_data(buffer, pstr, len);   // 这里把字符串写入, 不包含结束标志
    buffer.push_back(0);    // 写入结束标志, 两个字节, 都是0
    buffer.push_back(0);

    len += sizeof(wchar_t);
    return len;
}


// 读入字体, 返回字体占用字节数
inline int read_font(LPBYTE& buf, LOGFONTA& lf)
{
    int size = read_int32(buf);
    const int lfSize = sizeof(LOGFONTA);
    if ( size == 0 )
    {
        memset(&lf, 0, lfSize);
        return 0;
    }

    if ( size == lfSize )
    {
        memcpy(&lf, buf, lfSize);
        AddPtr(buf, size);
    }

#ifdef _DEBUG
    if ( size < 0 || size != lfSize )
        _DBG_BREAK_MSG("写入字体, 字体数据尺寸不等于LOGFONTA");
#endif

    return size;
}


// 读取字符串, 返回字符串地址, 同时地址增加, retSize接收地址增加多少个字节
inline LPCSTR read_str_A(LPBYTE& buf, int* retSize = 0)
{
    LPCSTR str = (LPCSTR)buf;
    size_t len = strlen(str) + 1;
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}
// 读取字符串, 返回字符串地址, 同时地址增加, retSize接收地址增加多少个字节
inline LPCWSTR read_str_W(LPBYTE& buf, int* retSize = 0)
{
    LPCWSTR str = (LPCWSTR)buf;
    size_t len = wcslen(str) * sizeof(wchar_t) + sizeof(wchar_t);
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}


HEXVIEW_NAMESPACE_END


#endif