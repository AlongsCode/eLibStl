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

// ��ȡ����, ���ض�ȡ��ĵ�ַ
inline LPBYTE read_data(LPBYTE& buf, LPVOID pData, int size)
{
    BYTE ret = ((BYTE*)buf)[0];
    memcpy(pData, buf, size);
    buf += size;
    return buf;
}
// ��ȡ�ṹ, ���ض�ȡ��ĵ�ַ
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
#define _DBG_BREAK_MSG(_s) { MessageBoxA(0, "����: " _DBG_BREAK_TOSTR2(__LINE__) "\r\n�ļ�: " __FILE__ \
                                "\r\n��������Ϣ�����ͼ��������\r\n\r\n���ȷ������򽫴����쳣, ���û�е�����, ���������"\
                                , _s, 0); __debugbreak(); }


template<typename T>
inline void AddPtr(T& pInt, int size)
{
    pInt = (T)( ( (LPBYTE)pInt ) + size );
}


// ������д�뻺����, �ڲ����ж��Ƿ�Խ��, Խ������·����ڴ�
// д���, pBuffer������nSize���ֽ�, ����д����ֽ���
inline int write_data(std::vector<BYTE>& buffer, LPCVOID pData, int nSize)
{
    if ( nSize == 0 )
        return 0;
#ifdef _DEBUG
    if ( nSize < 0 )
        _DBG_BREAK_MSG("д������, ���ݳߴ�С��0");
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
// д������
inline int write_int32(std::vector<BYTE>& buffer, int number)
{
    return write_data(buffer, &number, sizeof(number));
}
// д������64
inline int write_int64(std::vector<BYTE>& buffer, ULONG64 number)
{
    return write_data(buffer, &number, sizeof(number));
}


// ����������д��, ������ָ��, �������ӵ��ֽ���, ���ٻ�д��4���ֽ�
inline int write_font(std::vector<BYTE>& buffer, LPLOGFONTA lf, int fontSize)
{
    int size = 4;
    write_int32(buffer, fontSize);    // ����ռ���ֽ���
    if ( fontSize > 0 )
    {
        write_data(buffer, lf, fontSize);   // д����������
        size += fontSize;
    }
    return size;
}

// ���ַ���д�뻺����, ���ѵ�ַ����, �������ӵ��ֽ���
inline int write_str_A(std::vector<BYTE>& buffer, LPCSTR pstr, size_t strLen = 0)
{
    if ( strLen == 0 )
        strLen = strlen(pstr);
    size_t len = strLen;  // �������������ֽ�

    write_data(buffer, pstr, len);   // ������ַ���д��, ������������־
    buffer.push_back(0);    // д�������־, 1���ֽ�0
    len++;
    return len;
}
// ���ַ���д�뻺����, ���ѵ�ַ����, �������ӵ��ֽ���
inline int write_str_W(std::vector<BYTE>& buffer, LPCWSTR pstr, size_t strLen = 0)
{
    if ( !pstr )pstr = L"";
    if ( strLen == 0 )
        strLen = wcslen(pstr);
    size_t len = strLen * sizeof(wchar_t);  // �������������ֽ�

    write_data(buffer, pstr, len);   // ������ַ���д��, ������������־
    buffer.push_back(0);    // д�������־, �����ֽ�, ����0
    buffer.push_back(0);

    len += sizeof(wchar_t);
    return len;
}


// ��������, ��������ռ���ֽ���
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
        _DBG_BREAK_MSG("д������, �������ݳߴ粻����LOGFONTA");
#endif

    return size;
}


// ��ȡ�ַ���, �����ַ�����ַ, ͬʱ��ַ����, retSize���յ�ַ���Ӷ��ٸ��ֽ�
inline LPCSTR read_str_A(LPBYTE& buf, int* retSize = 0)
{
    LPCSTR str = (LPCSTR)buf;
    size_t len = strlen(str) + 1;
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}
// ��ȡ�ַ���, �����ַ�����ַ, ͬʱ��ַ����, retSize���յ�ַ���Ӷ��ٸ��ֽ�
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