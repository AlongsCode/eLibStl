#pragma once
#include <vector>
#include <string>
#include <unordered_map>

// �Ի�����ʹ�õ�����ڵ�, ��������, �����ı�ָ��
typedef struct _DIALOG_LIST_NODE
{
    LPWSTR text;
    struct _DIALOG_LIST_NODE* next;
}DIALOG_LIST_NODE, *PDIALOG_LIST_NODE, *LPDIALOG_LIST_NODE;

typedef bool(__stdcall* PFN_DLGPROC)(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, INT_PTR* pRet);


// �Ի�����, ����һ��Ĭ�ϵĶԻ���
class CDialog
{
private:
    typedef struct _DIALOG_STRUCT
    {
        HWND            hParent;        // �Ի��򸸴���
        int             width;          // �Ի�����, ��λΪ����
        int             height;         // �Ի���߶�, ��λΪ����
    }DIALOG_STRUCT, * PDIALOG_STRUCT, * LDIALOG_STRUCT;

    HWND m_hWnd;
    DIALOG_STRUCT m_arg;

    template<typename T>
    struct DIALOG_DELETEOBJECT
    {
        inline void operator()(const T& value)
        {
            if (value)
                DeleteObject(value);
        }
    };
    template<typename T, typename R, typename _FUN = DIALOG_DELETEOBJECT<R>, typename _OBJ = std::unordered_map<T, R>>
    class UNMAP : public _OBJ
    {
    public:
        UNMAP() : _OBJ()
        {

        }
        ~UNMAP()
        {
            _OBJ& map = *this;
            for (auto& item : map)
            {
                R hbr = item.second;
                if (hbr)
                    DeleteObject(hbr);
            }
        }
    };
    inline static UNMAP<COLORREF, HBRUSH>& GetMap()
    {
        static UNMAP<COLORREF, HBRUSH> s_map;
        return s_map;
    }
protected:
    //PTHEMECOLOR_STRUCT m_clr;

public:
    CDialog() : m_hWnd(0),  m_arg{ 0 }//, m_clr(0)
    {
        
    }
    ~CDialog()
    {
        //if (m_clr)
        //    delete m_clr;
    }

public:

    // ����һ����ģ̬�Ի���ؼ�, ���÷���Ҫ���ݻص������Լ�������Ϣ, ������ֻ���𴴽�һ���Ի���
    // �Ի�����и�����, ���ƶԻ�������Ļ��
    inline HWND create(HWND hWndParent,
                         int width = 400,
                         int height = 300,
                         DWORD style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_VISIBLE,
                         DWORD styleEx = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,
                         LPCWSTR pszCaption = L"�Ի���"
    )
    {
        return (HWND)_create_or_popup_dialog(true, hWndParent, width, height, style, styleEx, pszCaption);
    }

    // ����һ��ģ̬�Ի���ؼ�, ���÷���Ҫ���ݻص������Լ�������Ϣ, ������ֻ���𴴽�һ���Ի���
    // �Ի�����и�����, ���ƶԻ�������Ļ��
    inline INT_PTR popup(HWND hWndParent,
                          int width = 400,
                          int height = 300,
                          DWORD style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_VISIBLE,
                          DWORD styleEx = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,
                          LPCWSTR pszCaption = L"�Ի���"
    )
    {
        return _create_or_popup_dialog(false, hWndParent, width, height, style, styleEx, pszCaption);
    }

    static HBRUSH GetBrush(COLORREF clr)
    {
        static UNMAP<COLORREF, HBRUSH> map;
        auto it = map.find(clr);
        if (it != map.end())
            return it->second;
        HBRUSH hbr = CreateSolidBrush(clr);
        map[clr] = hbr;
        return hbr;
    }
private:
    inline INT_PTR _create_or_popup_dialog(bool isCreate, HWND hWndParent, int width, int height, DWORD style, DWORD styleEx, LPCWSTR pszCaption)
    {
        if (IsWindow(m_hWnd))
            return 0;

        struct __DLGTEMPLATE : DLGTEMPLATE
        {
            WORD menuid;
            WORD cls;
            wchar_t caption[1024];
        };


        m_arg.hParent = hWndParent;
        m_arg.width = width;
        m_arg.height = height;

        __DLGTEMPLATE dlg;
        memset(&dlg, 0, sizeof(dlg));
        dlg.style = style;
        dlg.dwExtendedStyle = styleEx;
        dlg.cdit = 0;
        if (pszCaption && *pszCaption)
            wcscpy_s(dlg.caption, pszCaption);

        //THEMECOLOR_STRUCT clr = { 0 };
        //if (GetThemeColorFromMap(&clr))
        //{
        //    if (!m_clr)
        //        m_clr = new THEMECOLOR_STRUCT;
        //    memcpy(m_clr, &clr, sizeof(clr));
        //}
        return DialogBoxIndirectParamW(GetModuleHandleW(0), &dlg, m_arg.hParent, DialogBoxProc, (LPARAM)this);
    }
    inline static INT_PTR CALLBACK DialogBoxProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);
        if (message == WM_INITDIALOG)
            SetWindowLongPtrW(hDlg, GWLP_USERDATA, lParam);
        CDialog* pObj = (CDialog*)GetWindowLongPtrW(hDlg, GWLP_USERDATA);  // ÿ����Ϣ��Ҫ��ȡ���ָ��
        if (!pObj) return false;
        return pObj->DialogProc(hDlg, message, wParam, lParam);
    }

protected:
    inline virtual INT_PTR DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_INITDIALOG:
            return InitDialog(hDlg, message, wParam, lParam);
        case WM_COMMAND:
            return OnCommand(hDlg, message, wParam, lParam);
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
            return OnCtlColor(hDlg, message, wParam, lParam);
        case WM_CLOSE:
            return OnClose(hDlg, message, wParam, lParam);
        case WM_PAINT:
            return OnPaint(hDlg, message, wParam, lParam);
        //case WM_THEMECOLORCHANGED:  // ������ɫ���ı�, wParam = �Ƿ�����ɫģʽ, lParam = THEMECOLOR_STRUCT
        //    return OnThemeColorChanged(hDlg, message, wParam, lParam);
        case WM_NOTIFY:
            return OnNotify(hDlg, message, wParam, lParam);
        case WM_DRAWITEM:
            return OnDrawItem(hDlg, message, wParam, lParam);

        default:
            return (INT_PTR)false;
        }
        return (INT_PTR)true;
    }
    inline virtual INT_PTR InitDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        m_hWnd = hDlg;
        RECT rc = { 0 };
        GetWindowRect(m_arg.hParent, &rc);
        if (rc.right == 0 || rc.bottom == 0)
        {
            rc.left = 0;
            rc.top = 0;
            rc.right = GetSystemMetrics(SM_CXSCREEN);
            //rc.bottom = GetSystemMetrics(SM_CYSCREEN);
            rc.bottom = GetSystemMetrics(SM_CYMAXIMIZED);
        }


        const int dialogWidth = m_arg.width;
        const int dialogHeight = m_arg.height;
        const int width = rc.right - rc.left;
        const int height = rc.bottom - rc.top;
        const int dialogLeft = rc.left + (width - dialogWidth) / 2;
        const int dialogTop = rc.top + (height - dialogHeight) / 2;

        rc = { dialogLeft, dialogTop, dialogLeft + dialogWidth, dialogTop + dialogHeight };

        // ���ƶԻ�������Ļ��
        HMONITOR hMonitor = MonitorFromWindow(m_arg.hParent, MONITOR_DEFAULTTONEAREST);
        if (hMonitor)
        {
            MONITORINFO mi = { 0 };
            mi.cbSize = sizeof(MONITORINFO);
            if (GetMonitorInfoW(hMonitor, &mi))
            {
                RECT& rcWork = mi.rcWork;
                if (rc.left < rcWork.left)
                    rc.left = rcWork.left + 10, rc.right = rc.left + dialogWidth;
                if (rc.top < rcWork.top)
                    rc.top = rcWork.top + 10, rc.bottom = rc.top + dialogHeight;
                if (rc.right > rcWork.right)
                    rc.right = rcWork.right - 10, rc.left = rc.right - dialogWidth;
                if (rc.bottom > rcWork.bottom)
                    rc.bottom = rcWork.bottom - 10, rc.top = rc.bottom - dialogHeight;
            }

        }
        MoveWindow(hDlg, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, false);
        return 1;
    }
    inline virtual INT_PTR OnCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return 0;
    }
    inline virtual INT_PTR OnClose(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        EndDialog(hDlg, 0);
        DestroyWindow(hDlg);
        return 1;
    }
    inline virtual INT_PTR OnPaint(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps = { 0 };
        BeginPaint(hDlg, &ps);
        RECT rc = { 0 };
        GetClientRect(hDlg, &rc);

        //HBRUSH hbrBack = m_clr ? CThemeColor::GetBrush(m_clr->crBack) : (HBRUSH)GetStockObject(WHITE_BRUSH);
        HBRUSH hbrBack = (HBRUSH)GetStockObject(WHITE_BRUSH);
        
        FillRect(ps.hdc, &rc, hbrBack);
        EndPaint(hDlg, &ps);
        return (INT_PTR)true;
    }
    inline virtual INT_PTR OnCtlColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return (INT_PTR)GetStockObject(WHITE_BRUSH);
    }

    inline virtual INT_PTR OnNotify(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return false;
    }
    inline virtual INT_PTR OnDrawItem(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return false;
    }
protected:
    // �����ڴ�, ����ʧ�ܻᵯ��һ���Ի���, �����׳��쳣, �ͷ��ڴ�ʹ�� Free() ����
    inline static LPVOID Alloc(size_t size, bool isClear = false)
    {
        LPVOID p = ::malloc(size);
        if (!p)
        {
            MessageBoxW(NULL, L"�����ڴ�ʧ��, �޷�����", L"�����ڴ�ʧ��", MB_ICONERROR);
            throw;
        }
        if (isClear)
            memset(p, 0, size);
        return p;
    }

    template<typename T>
    inline static void Free(T*& p)
    {
        if (p)
            ::free(p);
        p = 0;
    }
    inline static std::wstring GetWndText(HWND hWnd)
    {
        int len = GetWindowTextLengthW(hWnd) + 1;
        std::wstring ret;
        ret.resize(len);
        len = GetWindowTextW(hWnd, &ret[0], len);
        ret.resize(len);
        return ret;
    }
    // �����ı�, ���ظ��ƺ���ı�ָ��, ʧ�ܷ���ָ����ַ�����ָ��
    inline static LPWSTR CopyString(LPCWSTR pszText, size_t size = -1)
    {
        if (!pszText)
            pszText = L"";

        const size_t strLen = wcslen(pszText);
        if (size > strLen)
            size = strLen;
        const size_t allocSize = size * sizeof(wchar_t) + sizeof(wchar_t);

        LPWSTR ptr = (LPWSTR)Alloc(allocSize, true);
        memcpy(ptr, pszText, allocSize);
        return ptr;
    }

    static HFONT DefautlFont()
    {
        static HFONT hFont;
        if (!hFont)
        {
            LOGFONTW lf = { 0 };
            SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
            lf.lfHeight = -12;
            lf.lfWeight = FW_NORMAL;
            lf.lfItalic = false; // б��
            lf.lfUnderline = false; // �»���
            lf.lfStrikeOut = false; // ɾ����
            lf.lfCharSet = GB2312_CHARSET;
            wcscpy_s(lf.lfFaceName, L"΢���ź�");
            hFont = CreateFontIndirectW(&lf);
        }
        return hFont;
    }

    // �����ı�����Ŀ��, �Ǹ��ݴ��ݽ����ľ����������, ͬʱҲ�����ı��ߴ�
    static int CalcTextWidth(RECT& rcText, LPCWSTR pszText)
    {
        if (!pszText || !*pszText)
            return 0;
        static HDC hdc;
        if (!hdc)
        {
            hdc = CreateCompatibleDC(0);
            SelectObject(hdc, DefautlFont());
        }
        
        return DrawTextW(hdc, pszText, -1, &rcText, DT_CALCRECT | DT_NOPREFIX | DT_WORDBREAK);
    }

    // ����һ�����, ʹ��΢���ź�����, ��������ΪĬ������
    static HWND CreateControl(LPCWSTR szClass, LPCWSTR title,
                              DWORD styleEx, DWORD style,
                              int x, int y, int cx, int cy,
                              HWND hParent, INT_PTR id = 0, LPCWSTR lpszTips = L"")
    {
        HWND hWnd = CreateWindowExW(styleEx, szClass, title, style, x, y, cx, cy, hParent, (HMENU)(LONG_PTR)id, GetModuleHandleW(0), 0);
        SendMessageW(hWnd, WM_SETFONT, (WPARAM)DefautlFont(), 0);
        return hWnd;
    }

    // ��Ͽ����һ���ַ���, �������ø��Ӳ���
    // hWnd = ��Ͽ���
    // pszText = ��ӽ�ȥ���ַ���
    // param = ��Ŀ��ֵ
    // index = �����λ��, -1��ʾ���뵽���
    static int Combobox_AddString(HWND hWnd, LPCWSTR pszText, LPARAM param = 0, int index = -1)
    {
        int ret = ((int)(DWORD)SendMessageW(hWnd, CB_INSERTSTRING, (WPARAM)(int)index, (LPARAM)pszText));
        if (ret >= 0 && param)
        {
            SendMessageW(hWnd, CB_SETITEMDATA, ret, param);
        }
        return ret;
    };

    //static bool GetThemeColorFromMap(PTHEMECOLOR_STRUCT ret)
    //{
    //    HANDLE hMap = CThemeColor::GetColorMap();
    //    if (!hMap)
    //        return false;
    //    PTHEMECOLOR_STRUCT pClr = (PTHEMECOLOR_STRUCT)MapViewOfFile(hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    //    if (pClr)
    //    {
    //        memcpy(ret, pClr, sizeof(THEMECOLOR_STRUCT));
    //        UnmapViewOfFile(pClr);
    //    }
    //    CloseHandle(hMap);
    //    return pClr != 0;
    //}

    static void MoveComboboxEdit(HWND hWnd)
    {
        RECT rc;
        GetWindowRect(hWnd, &rc);
        const int cxClient = rc.right - rc.left;
        const int cyClient = rc.bottom - rc.top;

        HWND hChild = GetWindow(hWnd, GW_CHILD);
        wchar_t cls[260] = { 0 };
        while (hChild)
        {
            GetClassNameW(hChild, cls, 260);
            if (_wcsicmp(cls, L"edit") == 0)
                break;
            hChild = GetWindow(hChild, GW_HWNDNEXT);
        }
        if (hChild)
        {
            // ������Ҫ�Ա༭�����������д���, ����Ҫ���໯�Լ�Ū�ǿͻ�����������
            DWORD style = (DWORD)GetWindowLongPtrW(hChild, GWL_STYLE);
            const DWORD addStyle = WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | ES_NOHIDESEL;
            DWORD newStyle = style | addStyle;
            newStyle &= ~(ES_AUTOVSCROLL | ES_WANTRETURN);
            if (newStyle != style)
                SetWindowLongPtrW(hChild, GWL_STYLE, style | addStyle);
            //SetWindowLongPtrW(hChild, GWL_STYLE, addStyle);

            //SendMessageW(hChild, EM_SETMARGINS, EC_LEFTMARGIN, )
            RECT rc = { 3, 3, cxClient - 19, cyClient - 2 };
            auto a1 = SendMessageW(hChild, EM_SETRECTNP, 0, (LPARAM)&rc);
            //RECT rc1;
            //auto a2 = SendMessageW(hChild, EM_GETRECT, 0, (LPARAM)&rc1);
            //auto a3 = SendMessageW(hChild, EM_SETMARGINS, EC_LEFTMARGIN, 3);
            MoveWindow(hChild, 1, 1, cxClient - 18, cyClient - 2, TRUE);
        }

    }

    static void InitCombobox(HWND hWnd)
    {
        MoveComboboxEdit(hWnd);

        static WNDPROC HexView_ComboboxProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT
        {
            WNDPROC oldProc = (WNDPROC)GetPropW(hWnd, L"{005E7DF6-C920-4146-B4C6-AD15417DE176}");
            switch (message)
            {
            case WM_SIZE:
                MoveComboboxEdit(hWnd);
                break;
            case WM_DESTROY:
                SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)oldProc);
                break;
            default:
                break;
            }
            return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
        };
        WNDPROC oldProc = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)HexView_ComboboxProc);
        SetPropW(hWnd, L"{005E7DF6-C920-4146-B4C6-AD15417DE176}", oldProc);
    }

    //static INT_PTR OnNotify_Button(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, PTHEMECOLOR_STRUCT pClr)
    //{
    //    LPNMHDR hdr = (LPNMHDR)lParam;
    //    if (hdr->code != NM_CUSTOMDRAW || !pClr)
    //        return 0;

    //    LPNMCUSTOMDRAW lpNMCustomDraw = (LPNMCUSTOMDRAW)lParam;
    //    HWND hBtn = hdr->hwndFrom;
    //    switch (lpNMCustomDraw->dwDrawStage)
    //    {
    //    case CDDS_PREPAINT:
    //        //    SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, CDRF_NOTIFYPOSTPAINT);
    //        //    return 1;
    //        //case CDDS_PREERASE:
    //    {
    //        THEMECOLOR_STRUCT& clr = *pClr;
    //        HDC hdc = lpNMCustomDraw->hdc;
    //        RECT rc = lpNMCustomDraw->rc;
    //        rc.left += 16;
    //        int len = GetWindowTextLengthW(hBtn) + 1;
    //        LPWSTR text = new wchar_t[len];
    //        GetWindowTextW(hBtn, text, len);
    //        const BOOL isEnabled = IsWindowEnabled(hBtn);
    //        COLORREF clrOld = SetTextColor(hdc, isEnabled ? clr.crText : clr.crTextBan);
    //        HBRUSH hbr = CThemeColor::GetBrush(clr.crBack);
    //        FillRect(hdc, &rc, hbr);
    //        DrawTextW(hdc, text, len - 1, &rc, DT_VCENTER | DT_SINGLELINE);
    //        delete[] text;
    //        SetTextColor(hdc, clrOld);
    //        //*pRet = CDRF_SKIPDEFAULT;
    //        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, CDRF_SKIPDEFAULT);
    //        return 1;
    //    }
    //    default:
    //        return false;
    //    }
    //    return 0;
    //}

    // ɾ���������ظ��ĳ�Ա, Ȼ��ѳ�Ա���뵽�������
    // ��һ��ֵ���뵽�������һ����Ա��, ��������Ѿ��������ֵ, �ǻ�ɾ�������Ա
    template<typename T>
    static void push_back(std::vector<T>& arr, const T& value)
    {
        for (auto it = arr.begin(); it != arr.end(); ++it)
        {
            const T& vl = *it;
            if (vl == value)
            {
                arr.erase(it);
                break;
            }
        }
        arr.push_back(value);
    }

    static bool btn_isCheck(HWND hBtn)
    {
        return SendMessageW(hBtn, BM_GETCHECK, 0, 0) == BST_CHECKED;
    }
    static void btn_Check(HWND hBtn, bool isCheck)
    {
        SendMessageW(hBtn, BM_SETCHECK, isCheck ? BST_CHECKED : BST_UNCHECKED, 0);
    }


};


