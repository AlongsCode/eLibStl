#include "HexView_Help.h"
#ifdef _DEBUG
#include <assert.h>
#else
#   ifndef assert
#       define assert(_s) 
#   endif
#endif

namespace elibstl::hexview
{
    using namespace HEXVIEW_NAMESPACE;

    // ��¼�������������ڴ�, ����Ϊ���ھ��
    static std::unordered_map<HWND, PCONTROL_STRUCT_BASE> m_map;

    // ��Ҫ�ͷŵ�����, һ�������Ӧһ���ṹ
    static std::vector<PCONTROL_STRUCT_BASE> s_free_ptr;

    HUNIT WINAPI ECreate(LPBYTE pAllData, INT cbData, DWORD dwStyle, HWND hParent, UINT nID, \
                                HMENU hMenu, INT x, INT y, INT cx, INT cy, DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL bInDesignMode
    );
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText);
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit);
    BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);
    BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);
    INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2);

    LRESULT CALLBACK OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static char m_pszDefText[] =
        "elibstl:        "
        "       761463364"
        "QQ: 121007124   "
        "Groud: 20752843 ";
    const int m_nDefTextSize = sizeof(m_pszDefText) - 1;

}
EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_HexView(INT nInterfaceNO)
{
    switch ( nInterfaceNO )
    {
    case ITF_CREATE_UNIT:               // �������
        return (PFN_INTERFACE)elibstl::hexview::ECreate;
    case ITF_NOTIFY_PROPERTY_CHANGED:   // ֪ͨĳ�������ݱ��û��޸�
        return (PFN_INTERFACE)elibstl::hexview::EChange;
    case ITF_GET_ALL_PROPERTY_DATA:     // ȡȫ����������
        return (PFN_INTERFACE)elibstl::hexview::EGetAlldata;
    case ITF_GET_PROPERTY_DATA:         // ȡĳ��������
        return (PFN_INTERFACE)elibstl::hexview::EGetData;
    case ITF_DLG_INIT_CUSTOMIZE_DATA:   // ʹ�öԻ��������Զ�������
        return (PFN_INTERFACE)elibstl::hexview::EInputW;
    case ITF_GET_NOTIFY_RECEIVER:       // ȡ����ĸ���֪ͨ������(PFN_ON_NOTIFY_UNIT)
        return (PFN_INTERFACE)elibstl::hexview::ENotify;
    }
    return NULL;
}



namespace elibstl::hexview
{
#define PROP_WNDUNIT L"{949F3071-FD14-4C66-84D5-A92E0641EFFE}"
    inline void SetWndUnit(PCONTROL_STRUCT_BASE data, bool isClose)
    {
        ::SetPropW(data->hWnd, PROP_WNDUNIT, (HANDLE)data->hUnit);
        if ( isClose )
            PostMessageW(data->hWnd, WM_CLOSE, 0, 0);
    }
    inline HUNIT GetWndUnit(HWND hWnd)
    {
        //return (HUNIT)GetPropW(hWnd, PROP_WNDUNIT);
        return (HUNIT)RemovePropW(hWnd, PROP_WNDUNIT);
    }

    inline static bool InitDataEx(PHEXVIEW_PROPERTY& data, bool blInDesignMode)
    {
        if ( !data )
        {
            // �������´����Ĵ��ڲų�ʼ��������Ϣ, �Ѿ������Ĵ������Զ��м�¼��
            data = new HEXVIEW_PROPERTY;
            data->blInDesignMode = blInDesignMode;
            return true;
        }

        if ( data->hUnit )
        {
            //HWND hWndOld = (HWND)NotifySys(NAS_DETACH_CWND_OBJECT, (DWORD)data->hUnit, 0);
            SetWndUnit(data, true);
            //data->pCtl->Destroy();
        }

        m_map.erase(data->hWnd);
        return false;
    }

    inline HFONT Ctl_SetFontData(LOGFONTA& font, LONG& fontSize, HFONT& hFont, LPLOGFONTA lfA)
    {
        if ( hFont )
            DeleteObject(hFont);

        if ( !lfA )
        {
            LOGFONTW lf = { 0 };
            SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
            lf.lfHeight = -12;
            lf.lfWeight = FW_NORMAL;
            lf.lfItalic = 0;
            lf.lfUnderline = 0;
            lf.lfStrikeOut = 0;
            lf.lfCharSet = GB2312_CHARSET;
            memcpy(lf.lfFaceName, L"����", 6);
            hFont = CreateFontIndirectW(&lf);
            GetObjectA(hFont, sizeof(LOGFONTA), &font);
            fontSize = 0;
        }
        else
        {
            fontSize = sizeof(font);
            memcpy(&font, lfA, fontSize);
            hFont = CreateFontIndirectA(&font);
        }
        return hFont;
    }

    // ��������, ������ؼ��Ǿ���Ҫ����Ĭ��ֵ, �������ʾ������
    static bool ParsePropData(PHEXVIEW_PROPERTY pData, LPBYTE pAllPropertyData, INT nAllPropertyDataSize)
    {
        LPBYTE pBuf = pAllPropertyData;
        HEXVIEW_PROPERTY& prop = *pData;
        if ( !pBuf )
            return false;   // û�д�������, ���ؼ�, �ⲿ��Ĭ��ֵ
        prop.version        = read_int32(pBuf);     // �汾��, ���������ʾ��������, �ڲ�ʹ��, �����ж����ݽṹ��
        prop.border         = read_int32(pBuf);     // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
        prop.Editable       = read_int32(pBuf);     // ����༭, ������ָ���Ƿ�����༭
        prop.columnCount    = read_int32(pBuf);     // ����
        prop.is64Address    = read_int32(pBuf);     // �Ƿ�ʹ��64λ��ַ��ʾ
        prop.pAddress       = read_int64(pBuf);     // ��ʾ�ĵ�ַ
        prop.isDark         = read_int32(pBuf);     // �Ƿ�����ɫģʽ
        prop.size           = read_int32(pBuf);     // ��Ŀ��
        prop.bOwnerData     = read_int32(pBuf);     // ������Ŀ

        prop.clrSize        = read_int32(pBuf);     // ��ɫռ�õĳߴ�
        read_struct(pBuf, prop.clr);                // ��ɫ��Ϣ

        prop.fontSize = read_font(pBuf, prop.font);      // 1. ��ȡ����, д�����A��ṹ, �Ժ�ʹ������ṹ, ����һ���ò���W��
        Ctl_SetFontData(prop.font, prop.fontSize, pData->hFont, prop.fontSize ? &prop.font : 0);

        size_t nReadSize = (LPBYTE)pBuf - pAllPropertyData;
        if ( nReadSize == (size_t)nAllPropertyDataSize )
            return true; // �Ѿ�������β����

        // Ϊ�����汾׼��

        return false;
    }

    // �������
    HUNIT WINAPI ECreate(LPBYTE pAllData, INT cbData, DWORD dwStyle,
                         HWND hParent, UINT nID, HMENU hMenu,
                         INT x, INT y, INT cx, INT cy,
                         DWORD dwWinFormID, DWORD dwUnitID,
                         HWND hDesignWnd, BOOL bInDesignMode)
    {

        //PHEXVIEW_PROPERTY pData = 0;
        //HUNIT hUnit = GethUnitFromId(dwWinFormID, dwUnitID, (PVOID*)&pData);

        //if ( InitDataEx(pData, bInDesignMode) )
        //{
        //    // �������´����Ĵ��ڲų�ʼ��������Ϣ, �Ѿ������Ĵ������Զ��м�¼��
        //    s_free_ptr.push_back(pData);
        //}


        PHEXVIEW_PROPERTY pData = new HEXVIEW_PROPERTY;
        memset(pData, 0, sizeof(HEXVIEW_PROPERTY));

        bool isGetDefColor = false;
        DWORD styleCtl = 0;
        if ( !ParsePropData(pData, pAllData, cbData) )
        {
            isGetDefColor = true;   // ��Ҫ��ȡĬ����ɫ, �����������Ϻ�����
            HEXVIEW_PROPERTY& prop = *pData;
            prop.version = HEXVIEW_VERSION;
            prop.Editable = false;
            prop.columnCount = 16;
            prop.is64Address = false;
            prop.pAddress = 0;
            prop.clrSize = sizeof(prop.clr);
            prop.border = 5;
            //prop.TextBackColor = 
        }
        DWORD dwExStyle = 0;
        switch (pData->border)
        {
            //case 0:        // �ޱ߿�
            //    dwExStyle = WS_EX_CLIENTEDGE;
            //    break;
        case 1:        // ����ʽ
            dwExStyle = WS_EX_CLIENTEDGE;
            break;
        case 2:        // ͹��ʽ
            dwExStyle = WS_EX_DLGMODALFRAME;
            break;
        case 3:        // ǳ����ʽ
            dwExStyle = WS_EX_STATICEDGE;
            break;
        case 4:        // ����ʽ
            dwExStyle = WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME;
            break;
        case 5:
            dwStyle |= WS_BORDER;
            break;
        }

        styleCtl = (pData->Editable ? 0 : HVS_READONLY);
        styleCtl |= (pData->is64Address ? HVS_ADDRESS64 : 0);
        styleCtl |= (pData->isDark ? HVS_DARMMODE : 0);

        pData->hDesignWnd = hDesignWnd;
        pData->hWndParent = hParent;
        pData->id = nID;
        pData->dwWinFormID = dwWinFormID;
        pData->dwUnitID = dwUnitID;
        pData->blInDesignMode = bInDesignMode;
        pData->style = dwStyle;
        pData->styleCtl = styleCtl;
        pData->styleEx = dwExStyle;
        pData->hUnit = 0;
        if (!pData->bOwnerData)
        {
            // ��������Ŀ��������Ŀ������
            pData->data = new std::vector<BYTE>;
            pData->modi = new std::vector<bool>;
        }

        LPCSTR fmt = pData->is64Address ? "0x%016llX" : "0x%08X";
        sprintf_s(pData->addr_buf, fmt, pData->pAddress);

        pData->hWnd = CreateHexView(dwExStyle, dwStyle | WS_VISIBLE | WS_CHILD,
                                      x, y, cx, cy, hParent, nID, pData);
        SendMessageW(pData->hWnd, HVM_SETEXTENDEDSTYLE, 0, pData->styleCtl);

        if (isGetDefColor)
            SendMessageW(pData->hWnd, HVM_GETCOLOR, 0, (LPARAM)&pData->clr);
        else if (!pData->isDark)
            SendMessageW(pData->hWnd, HVM_SETCOLOR, 0, (LPARAM)&pData->clr);
        if(pData->columnCount != 16)
            SendMessageW(pData->hWnd, HVM_SETCOLUMNCOUNT, 0, (LPARAM)pData->columnCount);

        SetHexViewData(pData->hWnd, pData);
        HexView_BindNotify(pData->hWnd, OnNotify);
        if (pData->blInDesignMode)
        {
            // ����ģʽ, ����һ��Ĭ�ϵ�ֵ
            SendMessageW(pData->hWnd, HVM_SETITEMCOUNT, 1, (LPARAM)m_nDefTextSize);
        }
        pData->hUnit = elibstl::make_cwnd(pData->hWnd);
        return pData->hUnit;
    }


    // ֪ͨĳ�������ݱ��û��޸�
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
    {
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        switch ( nPropertyIndex )
        {
        case HEXVIEW_PROP_BORDER:       // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
            prop.border = min(max(0, pPropertyVaule->m_int), 5);
            elibstl::ChangeBorder(pData->hWnd, prop.border);
            break;
        case HEXVIEW_PROP_EDITABLE:     // ����༭, ������ָ���Ƿ�����༭
        {
            prop.Editable = pPropertyVaule->m_int;
            DWORD styleCtl = (DWORD)SendMessageW(hHexView, HVM_GETEXTENDEDSTYLE, 0, 0);
            prop.styleCtl = styleCtl;
            if (prop.Editable)
                styleCtl &= ~HVS_READONLY;
            else
                styleCtl |= HVS_READONLY;
            if (prop.styleCtl != styleCtl)
            {
                prop.styleCtl = styleCtl;
                SendMessageW(hHexView, HVM_SETEXTENDEDSTYLE, 1, prop.styleCtl);
            }
            break;
        }
        case HEXVIEW_PROP_COLUMNCOUNT:  // ����
            SendMessageW(hHexView, HVM_SETCOLUMNCOUNT, 1, pPropertyVaule->m_int);
            prop.columnCount = SendMessageW(hHexView, HVM_GETCOLUMNCOUNT, 0, 0);
            break;
        case HEXVIEW_PROP_IS64ADDR:     // ��ʹ��64λ��ַ��ʾ
        {
            prop.is64Address = pPropertyVaule->m_int;
            DWORD styleCtl = (DWORD)SendMessageW(hHexView, HVM_GETEXTENDEDSTYLE, 0, 0);
            prop.styleCtl = styleCtl;
            if (prop.is64Address)
                styleCtl |= HVS_ADDRESS64;
            else
                styleCtl &= ~HVS_ADDRESS64;

            LPCSTR fmt = prop.is64Address ? "0x%016llX" : "0x%08X";
            sprintf_s(prop.addr_buf, fmt, prop.pAddress);

            if (prop.styleCtl != styleCtl)
            {
                prop.styleCtl = styleCtl;
                SendMessageW(hHexView, HVM_SETEXTENDEDSTYLE, 1, prop.styleCtl);
            }
            break;
        }
        case HEXVIEW_PROP_ADDRESS:      // ��ʾ����ߵĵ�ַ
        {
            LPCSTR str = pPropertyVaule->m_szText;
            if (!str || !*str)
            {
                prop.pAddress = 0;
            }
            else
            {
                if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))  // 0x��ͷ, ��16����
                    sscanf_s(str, "0x%016llX", &prop.pAddress);
                else
                    prop.pAddress = (ULONG64)atoll(str);
            }
            LPCSTR fmt = prop.is64Address ? "0x%016llX" : "0x%08X";
            sprintf_s(prop.addr_buf, fmt, prop.pAddress);
            InvalidateRect(hHexView, 0, 0);
            break;
        }
        case HEXVIEW_PROP_ISDARK:       // �Ƿ�ʹ����ɫģʽ
            prop.isDark = pPropertyVaule->m_int;
            SendMessageW(hHexView, HVM_SETDARKMODE, 1, prop.isDark);
            break;
        case HEXVIEW_PROP_COLOR:        // ��ɫ
        {
            int copySize = pPropertyVaule->m_data.m_nDataSize;
            if (copySize > sizeof(prop.clr))
                copySize = sizeof(prop.clr);

            memcpy(&prop.clr, pPropertyVaule->m_data.m_pData, copySize);
            SendMessageW(hHexView, HVM_SETCOLOR, 1, (LPARAM)&prop.clr);
            break;
        }
        case HEXVIEW_PROP_FONT:         // ��������
        {
            Ctl_SetFontData(prop.font, prop.fontSize, pData->hFont, (LPLOGFONTA)pPropertyVaule->m_data.m_pData);
            SendMessageW(pData->hWnd, WM_SETFONT, (WPARAM)pData->hFont, 1);
            break;
        }
        case HEXVIEW_PROP_ITEMCOUNT:    // ��Ŀ��
        {
            //TODO ��Ҫ������Ŀ��, �����Ƿ�������Ŀ����
            //prop.size = pPropertyVaule->m_int;
            break;
        }
        case HEXVIEW_PROP_OWNERDATA:    // ������Ŀ
        {
            prop.bOwnerData = pPropertyVaule->m_int;
            if (!prop.blInDesignMode)
            {
                // ���ǵ���״̬, �Ǿ������Ŀ��Ϣ
                if (prop.bOwnerData)
                {
                    if (prop.data) delete prop.data;
                    if (prop.modi) delete prop.modi;
                    prop.data = 0;
                    prop.modi = 0;
                }
                else
                {
                    if (!prop.data) prop.data = new std::vector<BYTE>;
                    if (!prop.modi) prop.modi = new std::vector<bool>;
                    prop.data->clear();
                    prop.modi->clear();
                    prop.data->resize(prop.size);
                    prop.modi->resize(prop.size);
                }
            }
            break;
        }
        default:
            break;
        }
        return 0;
    }

    // ȡȫ����������
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
    {
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        std::vector<BYTE> buffer;
        buffer.reserve(0x1000);
        buffer.clear();
        int size = 0;                // ʵ��д�뻺�������ֽ���

        size += write_int32(buffer, HEXVIEW_VERSION     );  // �汾��, ÿ��д��Ķ������°�İ汾��
        size += write_int32(buffer, prop.border         );  // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
        size += write_int32(buffer, prop.Editable       );  // ����༭, ������ָ���Ƿ�����༭
        size += write_int32(buffer, prop.columnCount    );  // ����
        size += write_int32(buffer, prop.is64Address    );  // �Ƿ�ʹ��64λ��ַ��ʾ
        size += write_int64(buffer, prop.pAddress       );  // ��ʾ�ĵ�ַ
        size += write_int32(buffer, prop.isDark         );  // �Ƿ�����ɫģʽ
        size += write_int32(buffer, prop.size           );  // ��Ŀ��
        size += write_int32(buffer, prop.bOwnerData     );  // ������Ŀ

        size += write_int32(buffer, prop.clrSize        );  // ��ɫռ�õĳߴ�
        size += write_data(buffer, &prop.clr, sizeof(prop.clr));  // ��ɫ��Ϣ

        size += write_font(buffer, &prop.font, prop.fontSize);  // д������, д�����A��ṹ, �Ժ�ʹ������ṹ, ����һ���ò���W��


        HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
        if ( hGlobal )
        {
            PVOID pGlobal = ::GlobalLock(hGlobal);
            if ( pGlobal && size > 0 )
            {
                LPCVOID pBuffer = &buffer[0];
                memcpy(pGlobal, pBuffer, size);
                ::GlobalUnlock(hGlobal);
            }

        }

        assert(size == (int)buffer.size());

        return hGlobal;
    }

    // ȡĳ��������
    BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
    {
        // ȡĳ�������ݵ�pPropertyValue��, �ɹ�������, ���򷵻ؼ�
        // ע�⣺��������ʱ(�ɵ���PFN_CREATE_UNITʱ��blInDesignMode��������)
        // pPropertyValue���뷵�����洢��ֵ�����������ʱ(blInDesignModeΪ��)
        // ���뷵��ʵ�ʵĵ�ǰʵʱֵ
        // ����˵, �༭�򴰿ڵ�Ԫ��"����"����, ���ʱ���뷵���ڲ��������ֵ
        // ������ʱ�ͱ������ GetWindowText ȥʵʱ��ȡ

        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        switch ( nPropertyIndex )
        {
        case HEXVIEW_PROP_BORDER:       // �߿�, 0=�ޱ߿�, 1=����ʽ, 2=͹��ʽ, 3=ǳ����ʽ, 4=����ʽ, 5=���߱߿�ʽ
            pPropertyVaule->m_int = prop.border;
            break;
        case HEXVIEW_PROP_EDITABLE:     // ����༭, ������ָ���Ƿ�����༭
        {
            if (prop.blInDesignMode)
            {
                pPropertyVaule->m_int = prop.Editable;
            }
            else
            {
                prop.styleCtl = (DWORD)SendMessageW(hHexView, HVM_GETEXTENDEDSTYLE, 0, 0);
                const bool isReadOnly = (prop.styleCtl & HVS_READONLY) == HVS_READONLY;
                prop.Editable = isReadOnly == false;
            }
            break;
        }
        case HEXVIEW_PROP_COLUMNCOUNT:  // ����
        {
            if (!prop.blInDesignMode)
                prop.columnCount = SendMessageW(hHexView, HVM_GETCOLUMNCOUNT, 0, 0);
            
            pPropertyVaule->m_int = prop.columnCount;
            break;
        }
        case HEXVIEW_PROP_IS64ADDR:     // ��ʹ��64λ��ַ��ʾ
        {
            if (!prop.blInDesignMode)
            {
                prop.styleCtl = (DWORD)SendMessageW(hHexView, HVM_GETEXTENDEDSTYLE, 0, 0);
                prop.is64Address = (prop.styleCtl & HVS_ADDRESS64) == HVS_ADDRESS64;
            }
            pPropertyVaule->m_int = prop.is64Address;
            break;
        }
        case HEXVIEW_PROP_ADDRESS:      // ��ʾ����ߵĵ�ַ
        {
            pPropertyVaule->m_szText = prop.addr_buf;
            break;
        }
        case HEXVIEW_PROP_ISDARK:       // �Ƿ�ʹ����ɫģʽ
        {
            if (!prop.blInDesignMode)
                prop.isDark = (BOOL)SendMessageW(hHexView, HVM_GETDARKMODE, 0, 0);
            pPropertyVaule->m_int = prop.isDark;
            break;
        }
        case HEXVIEW_PROP_COLOR:        // ��ɫ
        {
            pPropertyVaule->m_data.m_nDataSize = sizeof(prop.clr);
            pPropertyVaule->m_data.m_pData = (LPBYTE)&prop.clr;
            break;
        }
        case HEXVIEW_PROP_FONT:         // ��������
        {
            if ( prop.fontSize > 0 )
            {
                pPropertyVaule->m_data.m_pData = (LPBYTE)&prop.font;
                pPropertyVaule->m_data.m_nDataSize = sizeof(prop.font);
            }
            break;
        }
        case HEXVIEW_PROP_ITEMCOUNT:    // ��Ŀ��
            pPropertyVaule->m_int = prop.size;
            break;
        case HEXVIEW_PROP_OWNERDATA:    // ������Ŀ
            pPropertyVaule->m_int = prop.bOwnerData;
            break;

        default:
            break;
        }
        return 0;
    }

    // �����Ի��򷽷�
    BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
    {
        // ������������ΪUD_CUSTOMIZE�ĵ�Ԫ����
        // �����Ҫ���´����õ�Ԫ�����޸ĵ�Ԫ����, �뷵����
        // pblModified ��ΪNULL, �������з����Ƿ��û������޸�(����������IDE����UNDO��¼)
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if (!hHexView) return 0;
        PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);
        if (!pData) return 0;
        HEXVIEW_PROPERTY& prop = *pData;
        switch (nPropertyIndex)
        {
        case HEXVIEW_PROP_COLOR:    // ��ɫ��Ϣ, ������ɫ����
        {
            *pblModified = HexView_Dialog_Color(pData);
            if (*pblModified)
                SendMessageW(hHexView, HVM_SETCOLOR, 1, (LPARAM)&pData->clr);
            
            return false;
            break;
        }
        default:
            return false;
        }
        return 0;
    }

    // ȡ����ĸ���֪ͨ������(PFN_ON_NOTIFY_UNIT)
    INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
    {
        switch ( nMsg )
        {
        case NU_GET_CREATE_SIZE_IN_DESIGNER:
        {
            // ȡ���ʱ������������õ�������ʱ��Ĭ�ϴ����ߴ�
            // dwParam1: ����: INT*, ���ؿ��(��λ����)
            // dwParam2: ����: INT*, ���ظ߶�(��λ����)
            // �ɹ�����1,ʧ�ܷ���0.
            *( (int*)dwParam1 ) = 200; // ����Ϸŵ�ide�Ͼ�ʹ�����Ĭ�Ͽ��
            *( (int*)dwParam2 ) = 100; // ����Ϸŵ�ide�Ͼ�ʹ�����Ĭ�ϸ߶�
            return 1; // ʹ���޸ĺ�Ŀ��, �Լ�������Ҫ�޸�
            break;
        }
        default:
            return 0;
        }
        return 0;
    }

    // ��������
    inline static BOOL _search_bin(PNMHEXSEARCH search, PHEXVIEW_PROPERTY pData)
    {
        SIZE_T index = search->start;
        std::vector<BYTE>& data = *pData->data;
        if (index >= data.size())
            return FALSE;   // Խ����

        LPBYTE pBase = (LPBYTE)(&data[0]);
        LPBYTE pEnd = pBase + data.size();
        LPBYTE pStart = pBase + index;
        int size = (int)(DWORD)search->nSize;
        LPBYTE pFind = search->pSearch;

        if (search->end == 0)
        {
            // ��������
            if (pStart + size > pEnd)
                pStart = pEnd - size;
            while (pStart >= pBase)
            {
                if (memcmp(pStart, pFind, size) == 0)
                {
                    search->pos = pStart - pBase;
                    return TRUE;
                }
                pStart--;
            }
            return FALSE;
        }

        // ��������
        while (pStart + size <= pEnd)
        {
            if (memcmp(pStart, pFind, size) == 0)
            {
                search->pos = pStart - pBase;
                return TRUE;
            }
            pStart++;
        }

        return FALSE;
    }


    LRESULT CALLBACK OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LPNMHDR hdr = (LPNMHDR)lParam;
        HWND hHexView = hdr->hwndFrom;
        PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);

        switch ( hdr->code )
        {
        case HVN_SEARCH:    // ������Ŀ
        {
            PNMHEXSEARCH search = (PNMHEXSEARCH)lParam;
            int deal = 0;
            int start = (int)search->start;
            int end = (int)search->end;
            int size = (int)search->nSize;
            int ret = CallEEvent(pData, deal, HEXVIEW_EVENT_SEARCH, 5, start, end, search->pSearch, size, &search->pos);
            if (!__query(ret, E_EVENT_DEAL_RET))
                ret = -1;   // �û�û�з���, �Ǿ�����Ϊ֧�ֿ��ڲ�����

            if (ret >= 0)
                return ret; // ���ڵ���0���������¼��Ѿ������������

            return _search_bin(search, pData);
        }
        case HVN_GETDISPINFO:
        {
            PNMHVDISPINFO DispInfo = (PNMHVDISPINFO)hdr;
            const SIZE_T index = DispInfo->Item.NumberOfItem;
            if (DispInfo->Item.Mask & HVIF_ADDRESS)
            {
                DispInfo->Item.Address = (ULONG64)pData->pAddress + index;
            }

            if (pData->blInDesignMode && pData->size == 0)
            {
                if (index >= m_nDefTextSize)
                    break;  // Խ����
                DispInfo->Item.Value = m_pszDefText[index];
                DispInfo->Item.State = 0;
                break;
            }
            if (!pData->bOwnerData)
            {
                // ��������Ŀ, �ڲ�����
                if (index >= pData->size || !pData->data || !pData->modi)
                    break;  // Խ����

                std::vector<BYTE>& data = *pData->data;
                std::vector<bool>& modi = *pData->modi;

                LPBYTE pBase = (LPBYTE)(&data[index]);
                if (DispInfo->Item.Mask & HVIF_BYTE)
                {
                    DispInfo->Item.Value = *pBase;
                    DispInfo->Item.State = (modi[index]) ? HVIS_MODIFIED : 0;
                }
            }
            int deal = 0;
            int value = (int)DispInfo->Item.Value;
            int isChange = __query(DispInfo->Item.State, HVIS_MODIFIED);

            EVENT_NOTIFY2 eventInfo(pData->dwWinFormID, pData->dwUnitID, HEXVIEW_EVENT_SHOWINFO);
            eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
            eventInfo.m_arg[0].m_inf.m_int = index;

            eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
            eventInfo.m_arg[1].m_inf.m_pInt = &value;

            eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_INT;
            eventInfo.m_arg[2].m_inf.m_pInt = &isChange;

            eventInfo.m_arg[3].m_inf.m_dtDataType = SDT_INT64;
            eventInfo.m_arg[3].m_inf.m_pInt64 = (INT64*)&DispInfo->Item.Address;
            eventInfo.m_nArgCount = 4;

            int ret = elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
            if (eventInfo.m_blHasRetVal)
            {
                // �û������˷���ֵ, ����û�д�����ֵ
            }
            DispInfo->Item.Value = (BYTE)value;
            if (isChange)
                DispInfo->Item.State |= HVIS_MODIFIED;
            else
                DispInfo->Item.State &= ~HVIS_MODIFIED;

            break;
        }
        case HVN_ITEMCHANGING:
        {
            if (pData->blInDesignMode)
                break;
            PNMHEXVIEW HexView = (PNMHEXVIEW)hdr;
            const int index = (int)HexView->Item.NumberOfItem;
            const int value = (int)HexView->Item.Value;
            int deal = 0;
            LPBYTE pBase = 0;
            int value_old = 0;
            if (!pData->bOwnerData)
            {
                // ��������Ŀ, ���ڲ��������ȡ����
                if (index >= pData->size || !pData->data || !pData->modi)
                    break;  // Խ����
                std::vector<BYTE>& data = *pData->data;
                pBase = (LPBYTE)(&data[index]);
                value_old = *pBase;
            }

            int ret = CallEEvent(pData, deal, HEXVIEW_EVENT_ITEMCHANGED, 3, index, value, value_old);
            if (ret == 0 && __query(deal, E_EVENT_DEAL_RET))
            {
                // �û��з�������, �����Ƿ�����0, ������
                break;
            }
            if (pBase)
            {
                // ��������Ŀ, �ڲ���¼����
                *pBase = HexView->Item.Value;
                std::vector<bool>& modi = *pData->modi;
                modi[index] = true;
            }
            break;
        }
        //case HVN_COPYDATA:  // �����ʹ��, �����ݿ��������ݽ����Ļ�������, ����û��ʹ�õ�
        //{
        //    PNMHEXCOPYDATA arg = (PNMHEXCOPYDATA)hdr;
        //    std::vector<BYTE>& data = *pData->data;
        //    size_t size = data.size();
        //    if ( arg->nSize > size )
        //        arg->nSize = size;
        //    arg->Address = (ULONG64)pData->pAddress;
        //    memcpy(arg->pBuf, &data[0], arg->nSize);
        //    return 1;
        //}
        case HVN_POPUPMENU:       // ���������˵�, NMMENUPOPUP �ṹ, �����Ƿ�����
        {
            PNMMENUPOPUP info = (PNMMENUPOPUP)lParam;
            int deal = 0;
            int ret = CallEEvent(pData, deal, HEXVIEW_EVENT_POPUPMENU, 3, info->hMenu, &info->pt.x, &info->pt.y);
            if (__query(ret, E_EVENT_DEAL_RET) && ret == 0)
                return 1;   // �û�����������, ���ﷵ��1, ����֪ͨ
            break;
        }
        case HVN_MENUSELING:      // �˵�����ѡ��, NMMENUSEL �ṹ, �����Ƿ�����
        case HVN_MENUSELED:       // �˵���ѡ��, NMMENUSEL �ṹ
        {
            PNMMENUSEL info = (PNMMENUSEL)lParam;
            const int iEvent = hdr->code == HEXVIEW_EVENT_MENUSELING ? HEXVIEW_EVENT_MENUSELING : HEXVIEW_EVENT_MENUSELED;
            int deal = 0;
            int ret = CallEEvent(pData, deal, iEvent, 1, info->id);
            if (iEvent == HEXVIEW_EVENT_MENUSELING && __query(ret, E_EVENT_DEAL_RET) && ret == 0)
                return 1;   // �û�����������, ���ﷵ��1, ����֪ͨ
            break;
        }
        default:
            return 0;
        }
        return 0;
    }


}


namespace elibstl
{

    // ��������, ��HexView_CmdDef.cpp�ﶨ��
    static INT s_dtCmdIndexcommobj_HexView[] = { 325 };
    // �¼�����, �����¼�������д������, ʹ�õ�ʱ�� ������ + ƫ�ƾ�����
    static EVENT_ARG_INFO2 s_eventArgInfo_HexView[] =
    {
        //1=��������,2=��������,3=�Ƿ�ο�,4=��������SDT_    

        /*000*/ {"��Ŀ����", "������0��ʼ", 0, SDT_INT},
        /*001*/ {"�޸ĺ��ֵ", "�޸ĺ��ֵ", 0, SDT_INT},
        /*002*/ {"�޸�ǰ��ֵ", "�޸�ǰ��ֵ, \"����Ŀ\" ����Ϊ��ʱ, ���ֵ��ԶΪ0", 0, SDT_INT},

        /*003*/ {"��Ŀ����", "������0��ʼ", 0, SDT_INT},
        /*004*/ {"��Ŀֵ", "��Ҫ��ʾ��ֵ, ����޸����ֵ, ��������ʾ�ľ������ֵ", EAS_BY_REF, SDT_INT},
        /*005*/ {"�Ƿ��޸�", "Ϊ�������ֵ��ʾʱʹ�� �޸Ĺ����ı���ɫ ����ʾ", EAS_BY_REF, SDT_BOOL},
        /*006*/ {"��ʾ�ĵ�ַ", "�����ʾ�ĵ�ַ", EAS_BY_REF, SDT_INT64},

        /*007*/ {"��ʼλ��", "�����Ctrl+F���ǵ�ǰ���������Ŀ, F3�ǵ�ǰ��Ŀ+1, Shift+F3�ǵ�ǰ��Ŀ-1", 0, SDT_INT},
        /*008*/ {"����λ��", "����λ��", 0, SDT_INT},
        /*009*/ {"������������ָ��", "ָ�뵽�ֽڼ�/ָ�뵽xxx ���Եõ�����, ����������ʲô����", 0, SDT_INT},
        /*010*/ {"�����������ݳߴ�", "������������ָ�� �����ݴ�С, ָ�뵽�ֽڼ�(������������ָ��, �����������ݳߴ�) ���Ǳ�����������", 0, SDT_INT},
        /*011*/ {"�ҵ�λ��", "����ҵ���λ����Ҫ���ҵ���λ�ø�ֵ���������", EAS_BY_REF, SDT_INT},

        /*012*/ {"�˵����", "�˵����", 0, SDT_INT},
        /*013*/ {"x", "�˵�����λ��", EAS_BY_REF, SDT_INT},
        /*014*/ {"y", "�˵�����λ��", EAS_BY_REF, SDT_INT},
        /*015*/ {"�˵�ID", "�˵�ID", 0, SDT_INT},

    };

    // �¼�
    static EVENT_INFO2 s_Event_HexView[] =
    {
        //1=�¼�����,2=�¼���ϸ����,3=����ֵ����,EV_RETURN_ ���Բ��ܶ���ɷ����ı����ֽڼ����������͵���Ҫ�ռ��ͷŴ������������
        //4=�¼��Ĳ�����Ŀ,5=�¼�����,6=����ֵ����
        /*000*/ {"��Ŀ���޸�", "����ֻ��Ϊ��ʱ, �������ݺ�ᴥ������¼�\r\n"
                    "    \"����Ŀ\" ����Ϊ��ʱ����ֵ������, Ϊ��ʱ����0�������޸�, ���ط�0�����޸�", _EVENT_OS(OS_ALL) | EV_IS_VER2, 3, s_eventArgInfo_HexView + 0, SDT_INT},
        /*001*/ {"��Ŀ������ʾ", "��Ҫ��ȡ����Ŀ��ʱ��ᴥ������¼�, ���¼�����Ƶ�ʺܸ�, ������������¼�����̫���ӵĲ���\r\n"
                    "    Ŀǰ����ֵ������, �����������汾ʹ��", _EVENT_OS(OS_ALL) | EV_IS_VER2, 4, s_eventArgInfo_HexView + 3, SDT_INT},
        /*002*/ {"������Ŀ", "�����¼�, ����ʼ/����λ�úͱ����������ݴ��ݵ��¼���, ���¼��ڷ����Ƿ�����������\r\n"
            "    ����0���ʾû������������, ������������ʾ�Ѿ��ҵ�, ��Ҫ��λ�ø�ֵ�� �ҵ�λ�� ����, ���ظ�������ʾ��֧�ֿ��ڲ�����, ��������֧�ֿ��ڲ�����", _EVENT_OS(OS_ALL) | EV_IS_VER2, 5, s_eventArgInfo_HexView + 7, SDT_INT},
        /*003*/ {"���������˵�", "���������˵�ʱ�����¼�, �������Ӳ˵���, ������ɾ���˵���, �����Ƿ��������˵�", _EVENT_OS(OS_ALL) | EV_IS_VER2, 3, s_eventArgInfo_HexView + 12, SDT_BOOL},
        /*004*/ {"�˵�����ѡ��", "���в˵�������ѡ�񶼴�������¼�, ʮ�����ƿ��ڲ�ʹ�õĲ˵�ID��ο� #ʮ�����ƿ�˵�_ ��ͷ�ĳ���\r\n"
                    "    ���������ڲ�����������, ���ؼٻ���û�з���ֵ���ڲ���������", _EVENT_OS(OS_ALL) | EV_IS_VER2, 1, s_eventArgInfo_HexView + 15, SDT_BOOL},
        /*005*/ {"�˵���ѡ��", "���в˵���ѡ�񶼴�������¼�, ʮ�����ƿ��ڲ�ʹ�õĲ˵�ID��ο��±�\r\n"
                    "        1000 = ֱ�Ӹ���, Ctrl+C �Ľ�� \r\n"
                    "        1001 = ����16���� \r\n"
                    "        1002 = ����16����, ���ÿո���� \r\n"
                    "        1003 = ����16����, ��C���Եĸ�ʽ, 0xFF,  \r\n"
                    "        1004 = ����16����, �û��ĸ�ʽ, 0FFh,  \r\n"
                    "        1005 = ����10���� \r\n"
                    "        1006 = ����10����, �м�û���ַ��ָ� \r\n"
                    "        1100 = ֱ�Ӹ���, Ctrl+C �Ľ�� \r\n"
                    "        1101 = ����16���� \r\n"
                    "        1102 = ����16����, ���ÿո���� \r\n"
                    "        1103 = ����16����, ��C���Եĸ�ʽ, 0xFF,  \r\n"
                    "        1104 = ����16����, �û��ĸ�ʽ, 0FFh,  \r\n"
                    "        1105 = ����10���� \r\n"
                    "        1106 = ����10����, �м�û���ַ��ָ� \r\n"
                    "        1200 = ȫѡ Ctrl+A \r\n"
                    "        1201 = ���� Ctrl+F \r\n"
                    "        1202 = ������һ�� N \r\n"
                    "        1203 = ������һ�� P \r\n"
                    "        1300 = ��ת Ctrl+G \r\n"
        , _EVENT_OS(OS_ALL) | EV_IS_VER2, 1, s_eventArgInfo_HexView + 15, _SDT_NULL},

    };

    // ����
    static UNIT_PROPERTY s_Member_HexView[] =
    {
        //FIXED_WIN_UNIT_PROPERTY,
        /*000*/ {"���", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*001*/ {"����", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*002*/ {"���", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*003*/ {"�߶�", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*004*/ {"���", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
        /*005*/ {"����", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
        /*006*/ {"��ֹ", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
        /*007*/ {"���ָ��", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},

        // ������������������Ҫ��Ĭ������, ÿ�������������, ���ǿ����ֶ�����
        // ��������������������, ��Щ����ǿ����Ҫ��
        // ��Щ�����������ԵĻص����Ǵ�0��ʼ��, ����, ��Щ���Ҳ��0��ʼ
         
    //    //1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����
    

        /*000*/ {"�߿�", "border", NULL, UD_PICK_INT, _PROP_OS(__OS_WIN), "�ޱ߿�\0""����ʽ\0""͹��ʽ\0""ǳ����ʽ\0""����ʽ\0""���߱߿�ʽ\0""\0"},
        /*001*/ {"����༭", "Editable", "�Ƿ�����༭, Ĭ�ϲ��ɱ༭", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
        /*002*/ {"����", "columnCount", "ÿ����ʾ���ٸ�16����ֵ", UD_INT, _PROP_OS(__OS_WIN), "16\0""32\0""64\0"},
        /*003*/ {"��ʾ����ַ", "is64Address", "�Ƿ�ʹ��64λ��ַ��ʾ", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
        /*004*/ {"��ʾ��ַ", "Address", "��ʾ����ߵĵ�ַ, 10���Ʊ���0x��ͷ", UD_TEXT, _PROP_OS(__OS_WIN), NULL},

        /*005*/ {"��ɫģʽ", "isDark", "�Ƿ�ʹ����ɫģʽ", UD_BOOL, _PROP_OS(__OS_WIN), NULL },
        /*006*/ {"��ɫ", "color", "�������ɫ��Ϣ", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL },


        /*007*/ {"����", "font", "�ǵȿ��������ʾ�쳣, ��ѡ��ȿ�����", UD_FONT, _PROP_OS(__OS_WIN) | UW_IS_HIDED, NULL },
        /*008*/ {"��Ŀ��", "nItemCount", "��Ҫ��ʾ���ٸ�16����", UD_INT, _PROP_OS(__OS_WIN) | UW_IS_HIDED, NULL },
        /*009*/ {"����Ŀ", "OwnerData", "������ʾ����Ŀ���������, ����ڲ��������κ�����, �����һ��, �ı��㹻���Ժ�ԭ�����ݽ����", UD_INT, _PROP_OS(__OS_WIN) | UW_IS_HIDED, NULL },
        
    };
    //1=��������,2=Ӣ������,3=��ϸ����,4=��������,5=����ֵ,6=��־ LDT_
    //����Ϊ���ڻ�˵����ʱ��Ч 7=��ԴID,8=�¼�����,9=����¼�����,10=������  11=�������� 12=��������ӳ���
    //��Ϊ���ڡ��˵������Ϊö����������ʱ����Ч 13=��Ա����,14=��Ա��������
    LIB_DATA_TYPE_INFO HexView_control =
    {
        "ʮ�����Ʊ༭��",
        "HexView",
        "16���Ʊ༭��",
        sizeof(s_dtCmdIndexcommobj_HexView) / sizeof(s_dtCmdIndexcommobj_HexView[0]),
         s_dtCmdIndexcommobj_HexView,
        _DT_OS(__OS_WIN) | LDT_WIN_UNIT,// | LDT_IS_HIDED,
        IDB_BUTTON_W,
        ARRAYSIZE(s_Event_HexView),
        s_Event_HexView,
        ARRAYSIZE(s_Member_HexView),
        s_Member_HexView,
        libstl_GetInterface_HexView,
        0,
        0
    };

}