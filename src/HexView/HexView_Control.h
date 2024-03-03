#include "HexView.h"
#include <vector>

// �汾��, �����ֽڼ�¼���汾�ʹΰ汾��, �����ֽڼ�¼����
#define HEXVIEW_VERSION MAKELONG(MAKEWORD(1, 0), MAKEWORD(10, 15))

#define HEXVIEW_PROP_BORDER                 0   // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
#define HEXVIEW_PROP_EDITABLE               1   // ����༭, ������ָ���Ƿ�����༭
#define HEXVIEW_PROP_COLUMNCOUNT            2   // ����
#define HEXVIEW_PROP_IS64ADDR               3   // �Ƿ�ʹ��64λ��ַ��ʾ
#define HEXVIEW_PROP_ADDRESS                4   // ��ʾ����ߵĵ�ַ
#define HEXVIEW_PROP_ISDARK                 5   // �Ƿ�ʹ����ɫģʽ
#define HEXVIEW_PROP_COLOR                  6   // ��ɫ��Ϣ
#define HEXVIEW_PROP_FONT                   7   // ��������
#define HEXVIEW_PROP_ITEMCOUNT              8   // ��Ŀ��
#define HEXVIEW_PROP_OWNERDATA              9   // ������Ŀ


#define HEXVIEW_NAMESPACE _hexview
#define HEXVIEW_NAMESPACE_BEGIN namespace HEXVIEW_NAMESPACE {
#define HEXVIEW_NAMESPACE_END }

HEXVIEW_NAMESPACE_BEGIN
typedef struct CONTROL_STRUCT_BASE
{
    LONG                controlType;    // �������, �����ݶ���һ���Ĳ���, �͸������ȷ����ʲô�����, CONTROLTYPE_ ��ͷ����
    WNDPROC             oldProc;        // ����ԭ����
    HFONT               hFont;          // ����
    HWND                hDesignWnd;     // ���blInDesignModeΪ��, ��hDesignWnd����ƴ��ڵĴ��ھ��, ����Ϊ0
    HWND                hWndParent;     // ��������ھ��
    HWND                hWnd;           // ������
    DWORD               hUnit;          // �����Է��ص�һ��CWnd��ָ��
    UINT                id;             // �����ID
    DWORD               dwWinFormID;    // �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ
    DWORD               dwUnitID;       // �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ��
    BOOL                blInDesignMode; // �Ƿ�������IDE�����Խ��п��ӻ����, ����ʱΪ��
    LONG                flags;          // �����һЩ��־, �Լ�����Լ�����
    DWORD               style;          // �������ʽ, �� WM_STYLECHANGED ���޸�
    DWORD               styleEx;        // �������չ��ʽ, �� WM_STYLECHANGED ���޸�
    DWORD               styleCtl;       // ���ר����չ��ʽ

}*PCONTROL_STRUCT_BASE;

// 
typedef struct _HEXVIEW_PROPERTY : CONTROL_STRUCT_BASE
{
    LONG            version;                // ȷ���汾�ŵ�һ����־
    LONG            border;                 // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
    BOOL            Editable;               // ����༭, ������ָ���Ƿ�����༭
    LONG            columnCount;            // ����
    BOOL            is64Address;            // �Ƿ�ʹ��64λ��ַ��ʾ
    ULONG64         pAddress;               // ��ʾ�ĵ�ַ
    BOOL            isDark;                 // �Ƿ�����ɫģʽ
    BOOL            bOwnerData;             // ������Ŀ
    LONG            size;                   // ��Ŀ��
    LONG            clrSize;                // ��ɫռ�õĳߴ�, �����������ɫ��Ϣ, ���Ը��������Ա�жϰ汾
    HEXVIEW_COLOR   clr;

    LONG            fontSize;               // �������Գߴ�, Ϊ0��д������
    LOGFONTA        font;                   // ��������
    char            addr_buf[50];           // ��ʾ�ĵ�ַ�ı�, ����������������ʾ�õ�
    std::vector<BYTE>* data;                // ��ʾ������
    std::vector<bool>* modi;                // ָ���ֽ��Ƿ��޸�
}HEXVIEW_PROPERTY, * PHEXVIEW_PROPERTY, * LPHEXVIEW_PROPERTY;

inline PHEXVIEW_PROPERTY GetHexViewData(HWND hWnd)
{
    return (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
}
inline PHEXVIEW_PROPERTY SetHexViewData(HWND hWnd, PHEXVIEW_PROPERTY pData)
{
    return (PHEXVIEW_PROPERTY)SetWindowLongPtrW(hWnd, GWLP_USERDATA, (ULONG_PTR)pData);
}

bool HexView_Dialog_Color(PHEXVIEW_PROPERTY pData);


HEXVIEW_NAMESPACE_END