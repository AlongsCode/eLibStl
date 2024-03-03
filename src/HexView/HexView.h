#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "HexView_Function.h"
#include <vector>
#include <string>

#define WC_HEXVIEWA              "����QQ121007124"
#define WC_HEXVIEWW              L"����QQ121007124"

#ifdef UNICODE
#define WC_HEXVIEW              WC_HEXVIEWW
#else
#define WC_HEXVIEW              WC_HEXVIEWA
#endif

#define HVM_FIRST               0x3C00

#define HVM_SETCLRBK                (HVM_FIRST + 0)     // ���ñ�����ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRBK                (HVM_FIRST + 1)     // ��ȡ������ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRBK_SEL            (HVM_FIRST + 2)     // ����ѡ������ı�����ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRBK_SEL            (HVM_FIRST + 3)     // ��ȡѡ������ı�����ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRLINE              (HVM_FIRST + 4)     // ����������ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRLINE              (HVM_FIRST + 5)     // ��ȡ������ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRMODIFYTEXT        (HVM_FIRST + 6)     // �������޸��ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRMODIFYTEXT        (HVM_FIRST + 7)     // ��ȡ���޸��ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRMODIFYTEXT_SEL    (HVM_FIRST + 8)     // ����ѡ���������޸��ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRMODIFYTEXT_SEL    (HVM_FIRST + 9)     // ��ȡѡ���������޸��ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ

#define HVM_SETCLRTEXTADDR          (HVM_FIRST + 10)     // ������ߵ�ַ���ұ��ַ����ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXTADDR          (HVM_FIRST + 11)     // ��ȡ��ߵ�ַ���ұ��ַ����ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRTEXTSELCHAR       (HVM_FIRST + 12)     // �����ұ�ѡ��ʱ�ַ����ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXTSELCHAR       (HVM_FIRST + 13)     // ��ȡ�ұ�ѡ��ʱ�ַ����ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ

#define HVM_SETCLRTEXT1             (HVM_FIRST + 14)     // ���õ�һ�������ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXT1             (HVM_FIRST + 15)     // ��ȡ��һ�������ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRTEXT2             (HVM_FIRST + 16)     // ���õڶ��������ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXT2             (HVM_FIRST + 17)     // ��ȡ�ڶ��������ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRTEXT1_SEL         (HVM_FIRST + 18)     // ���õ�һ������ѡ���ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXT1_SEL         (HVM_FIRST + 19)     // ��ȡ��һ������ѡ���ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ
#define HVM_SETCLRTEXT2_SEL         (HVM_FIRST + 20)     // ���õڶ�������ѡ���ı���ɫ, wParam = �Ƿ��ػ�, lParam = Ҫ���õ���ɫ, ��������ǰ����ɫ
#define HVM_GETCLRTEXT2_SEL         (HVM_FIRST + 21)     // ��ȡ�ڶ�������ѡ���ı���ɫ, ���� wParam��lParam, ���ض�Ӧ��ɫ

#define HVM_SETDARKMODE             (HVM_FIRST + 30)     // ������ɫģʽ, wParam = �Ƿ��ػ�, lParam = �Ƿ�������ɫģʽ
#define HVM_GETDARKMODE             (HVM_FIRST + 31)     // ��ȡ��ǰ��ͼ�Ƿ�Ϊ��ɫģʽ

#define HVM_GETCOLOR                (HVM_FIRST + 40)     // ��ȡ��ǰ��ɫ��Ϣ, wParamδʹ��, lParam = HEXVIEW_COLOR �ṹָ��
#define HVM_SETCOLOR                (HVM_FIRST + 41)     // ���õ�ǰ��ɫ��Ϣ, wParam�Ƿ��ػ�, lParam = HEXVIEW_COLOR �ṹָ��





#define HVM_SETEXTENDEDSTYLE    (HVM_FIRST + 50)    // ���������չ��ʽ, wParam = �Ƿ��ػ�, lParam = �����չ��ʽ, ��������ǰ����ʽ
#define HVM_GETEXTENDEDSTYLE    (HVM_FIRST + 51)    // ��ȡ�����չ��ʽ, ���� wParam��lParam, ���������չ��ʽ
#define HVM_SETITEMCOUNT        (HVM_FIRST + 52)    // ������Ŀ��, wParam = �Ƿ��ػ�, lParam = ��Ŀ��, �����Ƿ�ɹ�
#define HVM_GETITEMCOUNT        (HVM_FIRST + 53)    // ��ȡ��Ŀ��, ���� wParam��lParam, ������Ŀ��
#define HVM_SETSEL              (HVM_FIRST + 54)    // ����ѡ������, wParam = �Ƿ��ػ�, lParam = BYTERANGE�ṹ, �����Ƿ�ɹ�
#define HVM_GETSEL              (HVM_FIRST + 55)    // ��ȡѡ������, ���� wParam, lParam = BYTERANGE�ṹ, ���ս��, �����Ƿ�ɹ�
#define HVM_SETCOLUMNCOUNT      (HVM_FIRST + 56)    // ��������, wParam = �Ƿ��ػ�, lParam = ����, �����Ƿ�ɹ�
#define HVM_GETCOLUMNCOUNT      (HVM_FIRST + 57)    // ��ȡ����, ���� wParam��lParam, ��������


#define HVN_GETDISPINFO         (WMN_FIRST - 0)     // ��ȡ����, NMHVDISPINFO �ṹ
#define HVN_ITEMCHANGING        (WMN_FIRST - 1)     // ���ݱ��ı�, NMHEXVIEW �ṹ
#define HVN_ITEMSEL             (WMN_FIRST - 2)     // ѡ������, NMHEXSEL �ṹ
#define HVN_SEARCH              (WMN_FIRST - 3)     // ��������, NMHEXSEARCH �ṹ
#define HVN_COPYDATA            (WMN_FIRST - 4)     // ��������, NMHEXCOPYDATA �ṹ
#define HVN_POPUPMENU           (WMN_FIRST - 5)     // �����˵�, NMMENUPOPUP �ṹ, �����Ƿ�����
#define HVN_MENUSELING          (WMN_FIRST - 6)     // �˵������ѡ��, NMMENUSEL �ṹ, �����Ƿ�����
#define HVN_MENUSELED           (WMN_FIRST - 7)     // �˵����Ѿ���ѡ��, NMMENUSEL �ṹ


//
// Mask of an item
//

#define HVIF_ADDRESS            0x0001
#define HVIF_BYTE               0x0002

//
// State of an item
//

#define HVIS_MODIFIED           0x0001

//
// Extended styles
//

#define HVS_ADDRESS64           0x0001  // 64λ��ַ
#define HVS_READONLY            0x0002  // ֻ��ģʽ
#define HVS_DARMMODE            0x0004  // ��ɫģʽ

//
// States of the control
//

#define HVF_FONTCREATED         0x0001
#define HVF_CARETVISIBLE        0x0002
#define HVF_SELECTED            0x0004

#define HVCPY_DEF               0x0000  // Ĭ�ϸ���, ֻ�����м���ı�, ����16����
#define HVCPY_ADDRESS           0x0001  // ������ߵĵ�ַ
#define HVCPY_CHAR              0x0002  // �����ұߵ��ַ�
#define HVCPY_HEX10             0x0004  // ����10����
#define HVCPY_ALL               HVCPY_ADDRESS | HVCPY_CHAR  // ����16���� + ��ַ + �ַ�

#define HVCPY_HEX_1             0x0100  // ����16����, ���ÿո�ָ�
#define HVCPY_HEX_C             0x0200  // ����16����, ��C���Եĸ�ʽ, 0xFF, 
#define HVCPY_HEX_ASM           0x0300  // ����16����, �û��ĸ�ʽ, 0FFh, 
#define HVCPY_HEX10_1           0x0400  // ����10����, �ֽ�û���ַ��ָ�


enum Column {
    COLUMN_DATA = 1,
    COLUMN_VALUE
};

typedef struct _HEXVIEW_COLOR
{
    COLORREF    clrBack;            // �ı�������ɫ
    COLORREF    clrBackSel;         // ѡ�б�����ɫ
    COLORREF    clrLine;            // ������ɫ, �����߿�ɫ
    COLORREF    clrModifyText;      // �޸Ĺ����ı���ɫ
    COLORREF    clrModifyTextSel;   // �޸Ĺ����ı���ɫ, ѡ�е���ɫ

    COLORREF    clrTextAddress;     // �ı���ɫ, ��ߵ�ַ����ɫ
    COLORREF    clrTextSelChar;     // �ı���ɫ, ѡ�е��ı���ɫ, �ұ��ַ���

    COLORREF    clrText1;           // �ı���ɫ, ��һ�����ӵ���ɫ
    COLORREF    clrText2;           // �ı���ɫ, �ڶ������ӵ���ɫ
    COLORREF    clrTextSel1;        // ѡ���ı���ɫ, ��һ�����ӵ���ɫ
    COLORREF    clrTextSel2;        // ѡ���ı���ɫ, �ڶ������ӵ���ɫ

}HEXVIEW_COLOR, *PHEXVIEW_COLOR, *LPHEXVIEW_COLOR;

typedef struct _HEXVIEW {
    int         Line1;              // Start of the COLUMN_DATA
    int         Line2;              // Start of the COLUMN_VALUE

    int         VisibleLines;       //
    LONG_PTR    TotalLines;         //
    int         VisibleChars;       //
    int         LongestLine;        //

    LONG_PTR    VscrollPos;         //
    LONG_PTR    VscrollMax;         //
    int         HscrollPos;         //
    int         HscrollMax;         //

    int         HeightChar;         //
    int         WidthChar;          //
    int         HeightView;         //
    int         WidthView;          //

    int         ColumnCount;        // ��ʾ������, Ĭ������16
    int         ColumnSecond;       // �ұ��е�λ��, ���Ӱ���ұ��ַ���λ��

    HWND        hAsm;               // ��ര�ھ��, ����Ѿ��򿪾Ͳ��ٴ򿪵ڶ���
    int         asm_ShowMode;       // �����ʾ�﷨ģʽ, 0=MASM, 0x100=GoAsm, 0x200=Nasm, 0x400=AT, 0x800=IntrinsicMem
    WNDPROC     pfnNotify;          // ֪ͨ����, ����Ҫ���໯�����ھͿ��Խ���WM_NOTIFY֪ͨ, ����ʽ�ʹ���WM_NOTIFY��Ϣһ��

    int         ActiveColumn;       // COLUMN_DATA or COLUMN_VALUE

    SIZE_T      TotalItems;         //
    SIZE_T      NumberOfItem;       //
    UINT        PositionInItem;     // 0 = HINIBBLE; 1 = LONIBBLE

    SIZE_T      SelectionStart;     //
    SIZE_T      SelectionEnd;       //

    DWORD       Flags;              // 
    DWORD       ExStyle;            // ��չ���

    HFONT       hFont;              // ���ʹ�õ�����

    HEXVIEW_COLOR clr;              // ��ɫ��Ϣ


    LPVOID      pBoxData;           // �Ի���Ľṹָ��
} HEXVIEW, *PHEXVIEW;

typedef struct _HVITEM {
    UINT Mask;
    UINT State;
    ULONG64 Address;
    SIZE_T NumberOfItem;
    BYTE Value;
} HVITEM, *PHVITEM;

typedef struct _NMHVDISPINFO {
    NMHDR NmHdr;
    HVITEM Item;
} NMHVDISPINFO, *PNMHVDISPINFO;

typedef struct _NMHEXVIEW {
    NMHDR NmHdr;
    HVITEM Item;
} NMHEXVIEW, * PNMHEXVIEW;

typedef struct _NMMENUPOPUP {
    NMHDR NmHdr;
    HMENU hMenu;
    POINT pt;
} NMMENUPOPUP, * PNMMENUPOPUP;

typedef struct _NMMENUSEL {
    NMHDR NmHdr;
    LONG_PTR id;
} NMMENUSEL, * PNMMENUSEL;

typedef struct _NMHEXSEL
{
    NMHDR  NmHdr;
    SIZE_T Min;
    SIZE_T Max;
    int    isSel;
} NMHEXSEL, * PNMHEXSEL;
typedef struct _NMHEXSEARCH
{
    NMHDR   NmHdr;
    LPBYTE  pSearch;    // Ҫ����������
    SIZE_T  nSize;      // ���������ݴ�С
    SIZE_T  start;      // ��ʼ������λ��
    SIZE_T  end;        // ����������λ��, ����������Ϊ0
    SIZE_T  pos;        // ���ҵ���λ��, ����֪ͨ�ĵط���д
} NMHEXSEARCH, * PNMHEXSEARCH;
typedef struct _NMHEXCOPYDATA
{
    NMHDR   NmHdr;
    LPVOID  pBuf;       // ��������ַ
    SIZE_T  nSize;      // �������ߴ�
    ULONG64 Address;    // ����������ʼ��ַ, ��ʾ���ʹ�������ַ
} NMHEXCOPYDATA, * PNMHEXCOPYDATA;

typedef struct _BYTERANGE {
    SIZE_T Min;
    SIZE_T Max;
} BYTERANGE, *PBYTERANGE;

HWND CreateHexView(DWORD dwExStyle, DWORD dwStyle,
                   int x, int y, int nWidth, int nHeight, HWND hWndParent, LONG_PTR id = 0, LPVOID lpParam = 0);

BOOLEAN HexView_BindNotify(HWND hWnd, WNDPROC pfn);

