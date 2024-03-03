#pragma once
#include "CDialog.h"
#include <algorithm>

//#include <windows.h>


enum SEARCH_MODE
{
    SEARCH_MODE_NORMAL      = 0x0000,   // ��ͨ����, һ����ǩһ���༭��������ť
    SEARCH_MODE_HEX         = 0x0001,   // ʮ����������, һ����ǩһ����Ͽ�������ť
    SEARCH_MODE_ADDR        = 0x0002,   // �����ڴ��ַ�ͳߴ�Ĵ���
    SEARCH_MODE_CHECKBOX    = 0x0003,   // ����ͨ�����������һЩѡ���/��ѡ��
};

enum SEARCH_HEXMODE
{
    SEARCH_HEXMODE_HEX      = 0x0000,   // ʮ������
    SEARCH_HEXMODE_ANSI     = 0x0001,   // ansi�ַ���
    SEARCH_HEXMODE_DEC      = 0x0002,   // 10����
    SEARCH_HEXMODE_UNICODE  = 0x0003,   // Unicode�ַ���
    SEARCH_HEXMODE_FLOAT    = 0x0004,   // �����ȸ�����
    SEARCH_HEXMODE_DOUBLE   = 0x0005,   // ˫���ȸ�����
};


// �Ի�����
class CSearchBox : private CDialog
{
private:
    static constexpr auto IDC_CBB_MODE     { static_cast<UINT>(1000) };    // ����ģʽ��Ͽ�
    static constexpr auto IDC_CBB_INPUT    { static_cast<UINT>(1001) };    // �����ı���Ͽ�
    static constexpr auto IDC_CBB_ADDR     { static_cast<UINT>(1000) };    // �ڴ��ַ��Ͽ�
    static constexpr auto IDC_CBB_ADDRSI   { static_cast<UINT>(1001) };    // �ڴ�ߴ���Ͽ�

    static constexpr LPCWSTR PROP_OLDPROC   = L"{6E53D287-D4CE-4827-8D9D-5BBECA09E69C}";
    static constexpr LPCWSTR PROP_ARR_RADIO = L"{ADF73C81-40CE-4E4B-A26B-83480BAD6332}";

    struct RADIOBOX_STRUCT
    {
        HWND            hWnd;           // ��ѡ����
        int             vk;             // ����ʲô��ʱѡ��������
        int             id;             // �����ID, ���Ի�ȡ������ĸ���ѡ��
        int             nWidth;         // ��ť������Ŀ��
        BOOL            isWrap;         // �Ƿ���, Ϊ���ʱ�򴴽�������ͻỻ����һ�д���
        std::wstring    text;           // ����
        RADIOBOX_STRUCT()
        {
            hWnd = 0;
            vk = 0;
            id = 0;
            nWidth = 0;
            isWrap = FALSE;
        }
    };
    typedef struct _SEARCH_STRUCT
    {
        HWND            hParent;        // �Ի��򸸴���

        std::wstring    pszCaption;     // �Ի������
        std::wstring    pszTips;        // ��ʾ�ı�
        std::wstring    pszOkButton;    // ������ȷ�ϰ�ť�ı���
        std::wstring    pszCancelButton;// ������ȡ����ť�ı���
        PFN_DLGPROC     lpDialogFunc;   // ��������Ϣ�ص�����, ����true�����ڲ�����, ����false�ڲ�Ĭ�ϴ���, pRet�Ƿ���trueʱ�ڲ����ص�ֵ
        LPARAM          dwInitParam;    // ���Ӳ���, �ᴫ�ݵ� WM_INITDIALOG ��Ϣ�µ� lParam ����

        std::wstring    pResult;        // ��������������ı�
        LONG64          pResult2;       // ��������������ı�2, Ŀǰ�������ڴ�������, ���ڷ�������ĳߴ�ߴ�

        int             nHexMode;       // ʮ����������ģʽ, 0=ʮ������, 1=ansi�ַ���, 2=10����, 3=Unicode�ַ���, 4=�����ȸ�����, 5=˫���ȸ�����, ͬʱ��������ʱѡ�е�ģʽ
        int             nSearchMode;    // ����ģʽ, SEARCH_MODE ö�ٳ���
        int             nTipsHeight;    // ��ʾ�ı��Ĵ��ڸ߶�
        int             nRadioHeight;   // ��ѡ��һ��ռ�õĴ��ڸ߶�, ���е�ѡ���������, ��ѡ���ȳ������ڿ�Ȼ��Զ�����
        BOOLEAN         isOk;           // �Ƿ�����ȷ����ť
        int             nRadioId;       // ����ѡ�е����ĸ���ѡ��

        _SEARCH_STRUCT()
        {
            clear();
        }
        inline void clear()
        {
            pszCaption.clear();
            pszTips.clear();
            pszOkButton.clear();
            pszCancelButton.clear();
            pResult.clear();
            pResult2     = 0;
            hParent      = 0;
            lpDialogFunc = 0;
            dwInitParam  = 0;
            nHexMode     = 0;
            nSearchMode  = 0;
            nTipsHeight  = 0;
            nRadioHeight = 0;
            isOk         = 0;
            pResult2     = 0;
            nRadioId     = 0;
        }

    }SEARCH_STRUCT, * PSEARCH_STRUCT, * LPSEARCH_STRUCT;


    SEARCH_STRUCT m_data;
    std::vector<std::wstring>   m_arr_text; // ��ʷ�����ı�, ����һ�μ�¼һ��, ÿ�����붼����뵽�������
    std::vector<LONG64>         m_arr_size; // ��ʷ�����ı�, �ڴ���ҵ�ģʽʹ��, �ڴ��������������ֵ, ������Ҫ��¼����
    std::vector<RADIOBOX_STRUCT> m_radio;   // ��ѡ������, ģʽΪ SEARCH_MODECHECKBOX ʱʹ��
public:
    CSearchBox() : CDialog()
    {
        m_data.clear();
    }
    ~CSearchBox()
    {
        reset();
    }

    // ���ö���, ������в�������Ϊ��, ���չ���Ķ���һ��, �������Զ������������
    inline void reset()
    {
        m_data.clear();
    }
    // ����Ĭ���ı�����, ���Ի�ȡ��ȥд������, �´δ���������
    inline const std::vector<std::wstring>& GetDefaultText()
    {
        return m_arr_text;
    }
    // ����Ĭ�ϳߴ�����, ���Ի�ȡ��ȥд������, �´δ���������
    inline const std::vector<LONG64>& GetDefaultSize()
    {
        return m_arr_size;
    }
public:
    // ʹ��ָ�������������Ի���, ���в���������ʹ��Ĭ�ϲ���
    // ��������������ı�, ����û������ȡ����ť, ����0
    inline LPCWSTR open(HWND hParent = 0,
                        LPCWSTR pszCaption = L"����",
                        LPCWSTR pszTips = L"��������������",
                        LPCWSTR pszOkBtn = L"����",
                        LPCWSTR pszCancelBtn = L"ȡ��",
                        SEARCH_MODE nSearchMode = SEARCH_MODE_NORMAL)
    {
        SetCaption(pszCaption);
        SetTips(pszTips);
        SetOkButtonLabel(pszOkBtn);
        SetCancelButtonLabel(pszCancelBtn);
        SetSearchMode(nSearchMode);
        return Show(hParent);
    }

    // ��ʾ�����Ի���, ��������������ı�, ����û������ȡ����ť, ����0
    // ʹ�õĲ����Ƕ�Ӧ�������õĲ���
    inline LPCWSTR Show(HWND hWndParent = 0)
    {
        const DWORD style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_VISIBLE;
        const DWORD dwExtendedStyle = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;

        m_data.isOk = FALSE;
        m_data.nRadioId = 0;
        LPCWSTR pszCaption = GetCaption();
        LPCWSTR psTips = GetTips();
        int height = 24;
        m_data.nRadioHeight = 0;
        int mode = GetSearchMode();
        if (mode == SEARCH_MODE_NORMAL || mode == SEARCH_MODE_CHECKBOX)
        {
            RECT rcText = { 0, 0, 450, 500 };
            CalcTextWidth(rcText, psTips);
            height = rcText.bottom - rcText.top;
            if (height < 24) height = 24;
            else if (height > 500) height = 500;
        }

        if (mode == SEARCH_MODE_CHECKBOX)
        {
            const int box_width = 20;   // �ı���߿�Ŀ��
            const int maxWidth = 460;   // �������ֵ����Ҫ����
            int nWidth = 0, nHeight = 29;
            for (RADIOBOX_STRUCT& item : m_radio)
            {
                // ��Ŀ�� + �ı���� + 10���ؼ��

                RECT rcText = { 0, 0, 500, 24 };
                CalcTextWidth(rcText, item.text.c_str());
                int width_text = rcText.right - rcText.left;

                item.nWidth = box_width + width_text;
                const int nowWidth = (item.nWidth + 10);
                nWidth += nowWidth;

                if (nWidth > maxWidth)
                {
                    // ������
                    nHeight += 29;   // �߶���24, �м����5
                    nWidth = 0;
                    item.isWrap = TRUE;
                }
            }
            m_data.nRadioHeight = nHeight;
        }

        m_data.nTipsHeight = height;
        height = m_data.nTipsHeight + m_data.nRadioHeight;
        create(hWndParent, 498, 126 + height, style, dwExtendedStyle, pszCaption);
        if (!m_data.isOk)
            return 0;
        return m_data.pResult.c_str();
    }

public:
    // ���öԻ�����̵�ַ, ��������ǰ��ֵ, ���ú�Ի�������Ϣ������������, ��չ�Ի�����ʹ��
    // ��������ֵΪ �Ƿ������ڲ�����, �������true, �ڲ����ᴦ�������Ϣ, ����false, �ڲ��ᴦ�������Ϣ
    // ����������������Լ���������ʹ����¼�, Ҳ���Բ�����, �����ڲ�����
    // �������յ� WM_INITDIALOG ��Ϣʱ, Ĭ������Ѿ��������
    inline bool SetDialogFunc(PFN_DLGPROC pfn)
    {
        m_data.lpDialogFunc = pfn;
        return true;
    }
    // ���öԻ��򸽼Ӳ���, ��������ǰ��ֵ
    // ���ݵ� WM_INITDIALOG ��Ϣ�µ� lParam ����, ֻ���� WM_INITDIALOG ��Ϣ�²Żᴫ���������
    inline LPARAM SetDialogParam(LPARAM param)
    {
        LPARAM ret = m_data.dwInitParam;
        m_data.dwInitParam = param;
        return ret;
    }
    // �����������
    inline bool SetCaption(LPCWSTR text)
    {
        m_data.pszCaption = text;
        return true;
    }
    // ����������������ڴ�ߴ�, �������뵽�ߴ���������һ����Ա��, ����������Ѿ�����, ����������һ����Ա
    inline bool SetMemorySize(LONG64 size)
    {
        for (auto it = m_arr_size.begin(); it != m_arr_size.end(); ++it)
        {
            if (*it == size)
            {
                m_arr_size.erase(it);
                break;
            }
        }
        m_arr_size.push_back(size);
        return true;
    }
    // ����������ʾ�ı�
    inline bool SetTips(LPCWSTR text)
    {
        m_data.pszTips = text;
        return true;
    }
    // ��������ť�ı�
    inline bool SetOkButtonLabel(LPCWSTR text)
    {
        m_data.pszOkButton = text;
        return true;
    }
    // ��ȡ����ť�ı�
    inline bool SetCancelButtonLabel(LPCWSTR text)
    {
        m_data.pszCancelButton = text;
        return true;
    }
    // ����������Ĭ���ı��б�, ��Ա��Ϊ0��������Ϊ0����պ�ѡ�����ı�, ���һ����Ա��ʾ�ڵ�һ����ѡλ��
    // pText = �ı�����, ����Կ��ı���Ա
    // count = ����Ԫ�ظ���
    inline bool SetDefaultText(LPCWSTR* pText, int count)
    {
        m_arr_text.clear();
        if (count <= 0)
            return true;
        for (int i = 0; i < count; i++)
        {
            LPCWSTR text = pText[i];
            if (text && *text)
                push_back(m_arr_text, std::wstring(text));
        }
        return true;
    }

    // ����������Ĭ���ı��б�
    inline bool PushBackDefaultText(LPCWSTR pText)
    {
        push_back(m_arr_text, std::wstring(pText));
        return true;
    }
    // ��������������ڴ淽ʽ��Ĭ�ϳߴ��ı��б�
    // ��Ա��Ϊ0��������Ϊ0������ı�, ���һ����Ա��ʾ�ڵ�һ����ѡλ��
    // ÿ�ε�������󶼻��¼��������
    // pText = �ı�����, ����Կ��ı���Ա
    // count = ����Ԫ�ظ���
    inline bool SetDefaultTextSize(LONG64* pText, int count)
    {
        m_arr_size.clear();
        if (count <= 0)
            return true;
        for (int i = 0; i < count; i++)
        {
            LONG64 num = pText[i];
            m_arr_size.push_back(num);
        }
        return true;
    }
    // ������ģʽ
    inline bool SetSearchMode(SEARCH_MODE mode)
    {
        m_data.nSearchMode = mode;
        return true;
    }
    // ����ʮ������ѡ�������ģʽ, ֻ������ģʽ��16���Ƶ�ʱ�����Ч, SEARCH_HEXMODE_ ��ͷö�ٳ���, ��������ǰ��ֵ
    inline int SetHexMode(SEARCH_HEXMODE mode)
    {
        int ret = m_data.nHexMode;
        m_data.nHexMode = mode;
        return ret;
    }

    // ����һ����ѡ��, �������ⰴ��, ���ص�ǰ��ѡ������, ����ָ��������ʱ���Ӧ�ĵ�ѡ��ͻᱻѡ��
    // id = ��ѡ���id, ���ȷ������Ե��� GetRadioCheck ��ȷ��ѡ�����ĸ���ѡ��
    // vk = ���ⰴ������, VK_ ��ͷ����, ���Ϊ0, ��Ĭ�ϻ�ѡ�����, ���Ϊ0��ѡ�е�һ��Ϊ0�ĵ�ѡ��
    //      һ��������ռ��һ���ֽ�, vk֧��4�����������, ÿ���ֽ�Ϊһ��������
    // pszTitle = ��ѡ��ı���
    inline int InsertRadio(int id, int vk, LPCWSTR pszTitle)
    {
        m_radio.emplace_back();
        RADIOBOX_STRUCT& data = m_radio.back();
        data.text = pszTitle;
        data.vk = vk;
        data.id = id + ((int)(LONG64)this);
        return (int)m_radio.size();
    }
    // ��ȡ���ĸ���ѡ��ѡ����, ����ѡ�еĵ�ѡ��ID, ���û��ѡ���򷵻�0
    inline int GetRadioCheck() const
    {
        return m_data.nRadioId - ((int)(LONG64)this);
    }


public:
    // ��ȡ������������ı�, ���û�������򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetResult() const
    {
        return !m_data.pResult.empty() ? m_data.pResult.c_str() : L"";
    }
    // ��ȡ������������ڴ�ߴ�, ���û�������򷵻�0
    inline LONG64 GetResultMemorySize() const
    {
        return m_data.pResult2;
    }
    // ����������������ı�, ���ú��ٴλ�ȡ�᷵�ؿ��ı�
    inline void ResetResult()
    {
        m_data.pResult.clear();
    }
    // ����������������ڴ�ߴ�, ���ú��ٴλ�ȡ�᷵��0
    inline void ResetResultMemorySize()
    {
        m_data.pResult2 = 0;
    }
    // ��ȡ���õĶԻ�����̵�ַ, ���û�������򷵻�0
    inline PFN_DLGPROC GetDialogFunc() const
    {
        return m_data.lpDialogFunc;
    }
    // ��ȡ���õĶԻ��򸽼Ӳ���, ���û�������򷵻�0
    inline LPARAM GetDialogParam() const
    {
        return m_data.dwInitParam;
    }
    // ��ȡ���������, ���û���򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetCaption() const
    {
        return !m_data.pszCaption.empty() ? m_data.pszCaption.c_str() : L"����";
    }
    // ��ȡ��������ʾ�ı�, ���û���򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetTips() const
    {
        return !m_data.pszTips.empty() ? m_data.pszTips.c_str() : L"��������������";
    }
    // ��ȡ������ť�ı�, ���û���򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetOkButtonLabel() const
    {
        return !m_data.pszOkButton.empty() ? m_data.pszOkButton.c_str() : L"����";
    }
    // ��ȡȡ����ť�ı�, ���û���򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetCancelButtonLabel() const
    {
        return !m_data.pszCancelButton.empty() ? m_data.pszCancelButton.c_str() : L"ȡ��";
    }
    // ��ȡ����ģʽ
    inline SEARCH_MODE GetSearchMode() const
    {
        return (SEARCH_MODE)m_data.nSearchMode;
    }
    // ��ȡʮ������ѡ�������ģʽ, SEARCH_HEXMODE_ ��ͷö�ٳ���
    inline SEARCH_HEXMODE GetHexMode() const
    {
        return (SEARCH_HEXMODE)m_data.nHexMode;
    }

private:
    inline INT_PTR InitDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        INT_PTR ret = CDialog::InitDialog(hDlg, message, wParam, lParam);
        PSEARCH_STRUCT pData = &m_data;
        RECT rc = { 0 };
        GetWindowRect(pData->hParent, &rc);
        if (rc.right == 0 || rc.bottom == 0)
        {
            rc.left = 0;
            rc.top = 0;
            rc.right = GetSystemMetrics(SM_CXSCREEN);
            //rc.bottom = GetSystemMetrics(SM_CYSCREEN);
            rc.bottom = GetSystemMetrics(SM_CYMAXIMIZED);
        }

        const int margin = 11;  // �߾�
        const int editWidth = 460;
        const int cbkWidth = 140;
        const int btnWidth = 90;
        const int height_cbb = 200;
        const int dialogWidth = editWidth + margin * 2 + 16;


        int top = margin;
        const DWORD styleStatic = WS_GROUP | WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE;
        DWORD style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS;
        DWORD styleEx = WS_EX_NOPARENTNOTIFY;


        HWND hCbb = 0;
        LPCWSTR pszCaption  = GetCaption();
        LPCWSTR pszTips     = GetTips();
        LPCWSTR pszOk       = GetOkButtonLabel();
        LPCWSTR pszCancel   = GetCancelButtonLabel();

        auto pfn_subclass = [this, pData](HWND hWnd)
        {
            if (pData->nSearchMode != SEARCH_MODE_CHECKBOX)
                return;
            WNDPROC oldProc = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc_KeyDown);
            SetPropW(hWnd, PROP_OLDPROC, oldProc);
            SetPropW(hWnd, PROP_ARR_RADIO, &m_radio);
        };
        HWND hCbbFocus = 0;
        // ����Ԥ�輸��������ʽ, ��ͬ��������ʽ������ͬ�����
        switch (pData->nSearchMode)
        {
        case SEARCH_MODE_CHECKBOX: // ����ͨ�����������һЩѡ���/��ѡ��
        case SEARCH_MODE_NORMAL: // ��ͨ����, һ����ǩ, һ����������Ͽ�, ������ť
        {
            //CreateControl(L"static", pszTips, styleEx, styleStatic | SS_OWNERDRAW, margin, top, editWidth, m_data.nTipsHeight, hDlg, 0, L"");
            DWORD _edit_style = ES_MULTILINE | ES_READONLY | WS_CHILD | WS_VISIBLE;
            if (m_data.nTipsHeight >= 500)
                _edit_style |= WS_VSCROLL;
            HWND hChild = CreateControl(L"edit", pszTips, styleEx, _edit_style, margin, top, editWidth, m_data.nTipsHeight, hDlg, 0, L"");
            top += m_data.nTipsHeight + 5;
            pfn_subclass(hChild);

            style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 40, top, editWidth - 40, height_cbb, hDlg, IDC_CBB_INPUT, 0);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);

            hChild = GetWindow(hCbb, GW_CHILD);
            pfn_subclass(hCbb);
            while (hChild)
            {
                pfn_subclass(hChild);
                hChild = GetWindow(hChild, GW_HWNDNEXT);
            }
            
            GetWindowRect(hCbb, &rc);
            const int cbbHeight = rc.bottom - rc.top;

            hCbbFocus = hCbb;
            CreateControl(L"static", L"����", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0, 0);
            top += cbbHeight + 5;

            if (pData->nSearchMode == SEARCH_MODE_CHECKBOX)
            {
                int left = margin;
                const int radio_height = 24;
                bool isFirst = true;
                for (RADIOBOX_STRUCT& item : m_radio)
                {
                    const int radio_style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | BS_RADIOBUTTON | WS_VISIBLE | WS_CHILD;
                    const int radio_styleEx = 0;
                    const int radio_width = item.nWidth;

                    if (item.isWrap)
                    {
                        left = margin;
                        top += radio_height + 5;
                    }

                    item.hWnd = CreateControl(L"button", item.text.c_str(), radio_styleEx, radio_style, left, top, radio_width, radio_height, hDlg, item.id);
                    // ���໯����һЩ�¼�
                    pfn_subclass(item.hWnd);

                    if (isFirst && item.vk == 0)
                        isFirst = false, btn_Check(item.hWnd, true);
                    left += radio_width + 10;

                }
                top += radio_height + 5;
            }
            break;
        }
        case SEARCH_MODE_HEX: // ʮ�����ƴ���
        {
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 40, top, editWidth - 40, height_cbb, hDlg, IDC_CBB_MODE);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            GetWindowRect(hCbb, &rc);
            const int cbbHeight = rc.bottom - rc.top;
            CreateControl(L"static", L"����", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0);
            top += cbbHeight + 5;

            Combobox_AddString(hCbb, L"ʮ������");
            Combobox_AddString(hCbb, L"ANSI �ַ���");
            Combobox_AddString(hCbb, L"ʮ����");
            Combobox_AddString(hCbb, L"Unicode �ַ���");
            Combobox_AddString(hCbb, L"�����ȸ�����");
            Combobox_AddString(hCbb, L"˫���ȸ�����");

            int cbbIndex = pData->nHexMode;
            if (cbbIndex < 0 || cbbIndex > 5)
                cbbIndex = 0;
            SendMessageW(hCbb, CB_SETCURSEL, cbbIndex, 0);

            style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
            CreateControl(L"static", L"����", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0);
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 40, top, editWidth - 40, height_cbb, hDlg, IDC_CBB_INPUT);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            top += cbbHeight + 5;
            hCbbFocus = hCbb;
            break;
        }
        case SEARCH_MODE_ADDR: // �����ڴ��ַ�ͳߴ�Ĵ���
        {
            // ����һ����ʾ�ڴ��ַ, ������ʾ�ڴ�ߴ�
            const int staticWidth = 60;
            style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + staticWidth, top, editWidth - staticWidth, height_cbb, hDlg, IDC_CBB_ADDR);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            GetWindowRect(hCbb, &rc);
            const int cbbHeight = rc.bottom - rc.top;
            CreateControl(L"static", L"�ڴ��ַ", styleEx, styleStatic, margin, top, staticWidth, cbbHeight, hDlg, 0);
            top += cbbHeight + 5;

            HWND hCbb2 = CreateControl(L"ComboBox", 0, styleEx, style, margin + staticWidth, top, editWidth - staticWidth, height_cbb, hDlg, IDC_CBB_ADDRSI);
            //CDrawComboBox::InitCombobox(hCbb2, m_clr);
            CreateControl(L"static", L"�ڴ�ߴ�", styleEx, styleStatic, margin, top, staticWidth, cbbHeight, hDlg, 0);

            hCbbFocus = hCbb2;
            pszOk = L"�鿴�ڴ�";
            top += cbbHeight + 5;

            int count = 0;
            wchar_t buf[50];
            for (auto it = m_arr_size.rbegin(); it != m_arr_size.rend(); ++it)
            {
                LONG64 size = *it;
                swprintf_s(buf, L"%lld", size);
                Combobox_AddString(hCbb2, buf);
                count++;
            }
            if (hCbb2 && count > 0)
                SendMessageW(hCbb2, CB_SETCURSEL, 0, 0);
            break;
        }
        default:
            break;
        }


        int count = 0;
        for (auto it = m_arr_text.rbegin(); it != m_arr_text.rend(); ++it)
        {
            LPCWSTR text = it->c_str();
            if (text && *text)
            {
                Combobox_AddString(hCbb, text);
                count++;
                //if (count >= 20)
                //    break;  // �����ʾ20��
            }
        }

        if (hCbb && count > 0)
            SendMessageW(hCbb, CB_SETCURSEL, 0, 0);

        style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;
        styleEx = WS_EX_NOPARENTNOTIFY;
        int left = dialogWidth / 2;
        HWND hChild = CreateControl(L"button", pszOk, styleEx, style, left - btnWidth - 5, top, btnWidth, 31, hDlg, IDOK);
        pfn_subclass(hChild);


        style = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
        hChild = CreateControl(L"button", pszCancel, styleEx, style, left + 5, top, btnWidth, 31, hDlg, IDCANCEL);
        pfn_subclass(hChild);

        SetWindowTextW(hDlg, pszCaption);
        SetFocus(hCbbFocus);

        if (pData->lpDialogFunc && pData->lpDialogFunc(hDlg, message, wParam, pData->dwInitParam, &ret))
            return ret;

        return 0;
    }


    inline INT_PTR OnCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        int id = LOWORD(wParam);
        HWND hChild = (HWND)lParam;
        if (m_data.nSearchMode == SEARCH_MODE_CHECKBOX)
        {
            for (RADIOBOX_STRUCT& item : m_radio)
            {
                if (item.hWnd == hChild)
                    return false;
            }
        }
        PSEARCH_STRUCT pData = &m_data;

        switch (id)
        {
        case IDOK:
        {
            HWND hWndTop = 0, hWndBottom = 0;
            switch (pData->nSearchMode)
            {
            case SEARCH_MODE_NORMAL:    // ��ͨ��������
            case SEARCH_MODE_HEX:       // ʮ�����ƴ���
            case SEARCH_MODE_CHECKBOX:  // ����ͨ�����������һ��ѡ���
            {
                hWndTop = GetDlgItem(hDlg, IDC_CBB_MODE);
                hWndBottom = GetDlgItem(hDlg, IDC_CBB_INPUT);
                if (pData->nSearchMode == SEARCH_MODE_HEX)
                    pData->nHexMode = (int)(DWORD)SendMessageW(hWndTop, CB_GETCURSEL, 0, 0);

                pData->pResult = GetWndText(hWndBottom);
                push_back(m_arr_text, pData->pResult);

                if (pData->nSearchMode == SEARCH_MODE_CHECKBOX)
                {
                    for (RADIOBOX_STRUCT& item : m_radio)
                    {
                        if (btn_isCheck(item.hWnd))
                        {
                            m_data.nRadioId = item.id;
                            break;
                        }
                    }
                }
                break;
            }
            case SEARCH_MODE_ADDR:   // �����ڴ��ַ�ͳߴ�Ĵ���
            {
                hWndTop = GetDlgItem(hDlg, IDC_CBB_ADDR);       // �ڴ��ַ
                hWndBottom = GetDlgItem(hDlg, IDC_CBB_ADDRSI);  // �ڴ�ߴ�

                pData->pResult = GetWndText(hWndTop);
                std::wstring size = GetWndText(hWndBottom);
                pData->pResult2 = _wtoll(size.c_str());

                push_back(m_arr_text, pData->pResult);
                push_back(m_arr_size, pData->pResult2);
                break;
            }
            default:
                EndDialog(hDlg, 1);
                return 0;
                break;
            }
            pData->isOk = TRUE;
            EndDialog(hDlg, 1);
            break;
        }
        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;
        default:
            return (INT_PTR)false;
        }
        return (INT_PTR)true;
    }

    inline virtual INT_PTR OnDrawItem(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LPDRAWITEMSTRUCT draw = (LPDRAWITEMSTRUCT)lParam;
        if (draw->CtlType != ODT_STATIC)//|| draw->CtlID != 0)
            return false;

        HWND hStatic = draw->hwndItem;
        HDC hdc = draw->hDC;
        RECT& rcItem = draw->rcItem;
        LPCWSTR pszText = GetTips();

        DrawTextW(hdc, pszText, -1, &rcItem, DT_NOPREFIX | DT_WORDBREAK | DT_END_ELLIPSIS);

        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 1);
        return true;
    }

    //inline virtual INT_PTR OnNotify(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    //{
    //    LPNMHDR hdr = (LPNMHDR)lParam;
    //    if (hdr->code != NM_CUSTOMDRAW)
    //        return false;
    //    bool isDraw = false;
    //    for (RADIOBOX_STRUCT& item : m_radio)
    //    {
    //        if (item.hWnd == hdr->hwndFrom)
    //        {
    //            isDraw = true;
    //            break;
    //        }
    //    }
    //    if (isDraw)
    //        return OnNotify_Button(hDlg, message, wParam, lParam, m_clr);
    //    return false;
    //}

private:

    static bool _key_down(HWND hWnd, int key)
    {
        std::vector<RADIOBOX_STRUCT>* pArr =(std::vector<RADIOBOX_STRUCT>*)GetPropW(hWnd, PROP_ARR_RADIO);
        if (!pArr)
            return false;

        std::vector<RADIOBOX_STRUCT> arr(*pArr);


        std::sort(arr.begin(), arr.end(), [](const RADIOBOX_STRUCT& left, const RADIOBOX_STRUCT& right)
        {
            return left.vk > right.vk;
        });

        auto pfn_check = [&arr](HWND hWnd)
        {
            for (RADIOBOX_STRUCT& it : arr)
                btn_Check(it.hWnd, false);
            btn_Check(hWnd, true);
        };

        HWND hFirst0 = 0;   // ��һ��vk��0�Ĵ���
        for (RADIOBOX_STRUCT& item : arr)
        {
            if (item.vk == 0)
            {
                if (hFirst0 == 0)
                    hFirst0 = item.hWnd;
                continue;
            }
            LPBYTE pKey = (LPBYTE)&item.vk;
            bool isCheck = pKey[0] ? ((GetAsyncKeyState(pKey[0]) & 0x8000) != 0) : false;
            for (int i = 1; i < 4; i++)
            {
                // һ����4����ϼ�, 4���ֽ�, ÿ���ֽڴ��һ��������
                if (pKey[i])
                    isCheck = ((GetAsyncKeyState(pKey[i]) & 0x8000) != 0);
            }

            if (isCheck)
            {
                pfn_check(item.hWnd);
                return true;
            }
        }
        if (hFirst0)
            pfn_check(hFirst0);
        return false;
    }
    inline virtual INT_PTR DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            if (_key_down(hDlg, (int)wParam))
                return true;
            break;
        }
        default:
            break;
        }
        return CDialog::DialogProc(hDlg, message, wParam, lParam);
    }

    static LRESULT CALLBACK WndProc_KeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WNDPROC oldProc = (WNDPROC)GetPropW(hWnd, PROP_OLDPROC);
        switch (message)
        {
        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            if (_key_down(hWnd, (int)wParam))
                return 0;
            return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
        }
        default:
            if (!oldProc)
                return 0;
            return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
        }
        return 0;
    }

private:

};