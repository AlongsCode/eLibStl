#pragma once

#include "CDialog.h"

// ��תģʽ
enum JUMPBOX_MODE : int
{
    JUMPBOX_MODE_START      = 0x0000,     // ���ļ���ʼ
    JUMPBOX_MODE_NOW        = 0x0001,     // ��ǰλ��
    JUMPBOX_MODE_NOW_PREV   = 0x0002,     // ��ǰλ������
    JUMPBOX_MODE_END        = 0x0003,     // ���ļ�����

    JUMPBOX_MODE_HEX        = 0x10000,    // �Ƿ���16����, û�������־�Ļ�, �Ի�����ʾ����ѡ��10���Ƶĵ�ѡ��

};


// ��ת�Ի���
class CJumpBox : private CDialog
{
    static constexpr auto IDC_CBB_INPUT     { static_cast<UINT>(1000) };    // �����ı���Ͽ�

    static constexpr auto IDC_RADIO_START   { static_cast<UINT>(2000) };   // �ļ���ʼ
    static constexpr auto IDC_RADIO_NOW     { static_cast<UINT>(2001) };   // ����λ��
    static constexpr auto IDC_RADIO_NOW2    { static_cast<UINT>(2002) };   // ����λ������
    static constexpr auto IDC_RADIO_END     { static_cast<UINT>(2003) };   // �ļ�����

    static constexpr auto IDC_RADIO_10      { static_cast<UINT>(3000) };   // 10����
    static constexpr auto IDC_RADIO_16      { static_cast<UINT>(3001) };   // 16����

    typedef struct JUMPBOX_STRUCT
    {
        HWND            hParent;    // �Ի��򸸴���
        int             nMode;      // ��תģʽ, 0=���ļ���ʼ, 1=��ǰλ��, 2����λ������, 3=���ļ�����, ��λ = �Ƿ���16����, ͬʱ��������ʱѡ�е�ģʽ
        int             nTextCount; // ����Ԫ�ظ���

        std::wstring    pszCaption; // �Ի������
        std::wstring    pResult;    // �����������ת�ı�
        INT64           pos;        // �������ת�ı�ת�ɵ���ֵ

        BOOL            isOk;       // �Ƿ�����ȷ����ť

        HWND            hStart;     // ���½ǵ�һ����ѡ��, ��0��ʼ��ת
        HWND            hNow;       // ���½ǵڶ�����ѡ��, �ӵ�ǰλ�ÿ�ʼ������ת
        HWND            hNow2;      // ���½ǵ�������ѡ��, �ӵ�ǰλ����ǰ��ת
        HWND            hEnd;       // ���½����һ����ѡ��, ��ת�����
        HWND            h10;        // 10���Ƶ�ѡ��
        HWND            h16;        // 16���Ƶ�ѡ��
        HWND            hCbb;       // �����ı�����Ͽ�, �����Ҫ�������Ͽ��ȡ�ı�����

        std::wstring    pszRadio1;  // ���½ǵ�һ����ѡ����ı�, ��0��ʼ��ת
        std::wstring    pszRadio2;  // ���½ǵڶ�����ѡ����ı�, �ӵ�ǰλ�ÿ�ʼ������ת
        std::wstring    pszRadio3;  // ���½ǵ�������ѡ����ı�, �ӵ�ǰλ����ǰ��ת
        std::wstring    pszRadio4;  // ���½����һ����ѡ����ı�, ��ת�����

        PFN_DLGPROC     lpDialogFunc;   // ��������Ϣ�ص�����, ����true�����ڲ�����, ����false�ڲ�Ĭ�ϴ���, pRet�Ƿ���trueʱ�ڲ����ص�ֵ
        LPARAM          dwInitParam;    // ���Ӳ���, �ᴫ�ݵ� WM_INITDIALOG ��Ϣ�µ� lParam ����

        JUMPBOX_STRUCT()
        {
            clear();
        }
        inline void clear()
        {
            hParent         = 0;
            nMode           = 0;
            nTextCount      = 0;
            pos             = 0;
            isOk            = 0;
            hStart          = 0;
            hNow            = 0;
            hNow2           = 0;
            hEnd            = 0;
            h10             = 0;
            h16             = 0;
            hCbb            = 0;
            lpDialogFunc    = 0;
            dwInitParam     = 0;


            pszCaption.clear();
            pResult.clear();
            pszRadio1.clear();
            pszRadio2.clear();
            pszRadio3.clear();
            pszRadio4.clear();
        }
    }*PJUMPBOX_STRUCT;

    JUMPBOX_STRUCT m_data;
    std::vector<std::wstring>   m_arr_text; // ��ʷ�����ı�, ����һ�μ�¼һ��, ÿ�����붼����뵽�������

private:

public:
    CJumpBox() : CDialog()
    {
        m_data.clear();
    }
    ~CJumpBox()
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
public:
    // ��ʾ��ת�Ի���, ����������ı�, ����û������ȡ����ť, ����0
    // ʹ�õĲ����Ƕ�Ӧ�������õĲ���
    inline LPCWSTR Show(HWND hWndParent = 0)
    {
        const DWORD style = WS_SYSMENU | WS_CAPTION | WS_CLIPSIBLINGS | WS_VISIBLE;
        const DWORD dwExtendedStyle = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;

        LPCWSTR pszCaption = GetCaption();
        m_data.isOk = FALSE;
        m_data.hParent = hWndParent;
        popup(hWndParent, 498, 218, style, dwExtendedStyle, pszCaption);
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
    // �Ƿ�ѡ��16���Ƶĵ�ѡ��, ��������ǰ��ֵ
    inline bool SetSelHex(bool isHex)
    {
        const bool ret = (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;
        if (isHex)
            m_data.nMode |= JUMPBOX_MODE_HEX;
        else
            m_data.nMode &= ~JUMPBOX_MODE_HEX;
        return ret;
    }
    // ������תģʽ, ��������ǰ��ֵ, JUMPBOX_MODE_ ��ͷ����, ���½�4����ѡ��, Ĭ��ѡ���ĸ�
    inline int SetMode(JUMPBOX_MODE mode)
    {
        const bool isHex = (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;
        int ret = LOWORD(m_data.nMode);
        m_data.nMode = MAKELONG(mode, isHex);
        return ret;
    }
    // ����������Ĭ���ı��б�, ��Ҫ���÷���֤���ݽ������ı�ָ�����������, �Ի�����ʾ֮ǰ���ܱ�����
    // pText = �ı�����, count = ����Ԫ�ظ���
    inline bool SetDefaultText(LPCWSTR* pText, int count)
    {
        m_arr_text.clear();
        if (count <= 0)
            return true;
        for (int i = 0; i < count; i++)
        {
            LPCWSTR text = pText[i];
            if (text && *text)
                m_arr_text.push_back(text);
        }
        return true;
    }
    // �������½ǵ�ѡ����ı�, ���� nRadio �����������ĸ���ѡ����ı�
    inline bool SetRadioText(JUMPBOX_MODE nRadio, LPCWSTR pszText)
    {
#define _copy_free_str(_s) _s = pszText
        switch (nRadio)
        {
        case JUMPBOX_MODE_START:
            _copy_free_str(m_data.pszRadio1);
            break;
        case JUMPBOX_MODE_NOW:
            _copy_free_str(m_data.pszRadio2);
            break;
        case JUMPBOX_MODE_NOW_PREV:
            _copy_free_str(m_data.pszRadio3);
            break;
        case JUMPBOX_MODE_END:
            _copy_free_str(m_data.pszRadio4);
            break;
        default:
            return false;
        }
#undef _copy_free_str
        return true;
    }

public:
    // ��ȡ��ת��������ı�, ���û�������򷵻ؿ��ı�, ���᷵��0
    inline LPCWSTR GetResult() const
    {
        return !m_data.pResult.empty() ? m_data.pResult.c_str() : L"";
    }
    // ��ȡ��ת��������ı�ת���ɵ���ֵ, ���û�������򷵻�0
    inline INT64 GetResultNumber() const
    {
        return m_data.pos;
    }
    // ������ת��������ı�, ���ú��ٴλ�ȡ�᷵�ؿ��ı�
    inline void ResetResult()
    {
        m_data.pResult.clear();
        m_data.pos = 0;
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
        return !m_data.pszCaption.empty() ? m_data.pszCaption.c_str() : L"��ת��...";
    }
    // ��ȡʮ������ѡ�������ģʽ, SEARCH_HEXMODE_ ��ͷö�ٳ���
    inline bool GetSelHex() const
    {
        return (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;;
    }
    // ��ȡ��תģʽ, ���÷�Ӧ�ø��ݷ��ص�ģʽ�����������ת
    inline JUMPBOX_MODE GetMode() const
    {
        int ret = LOWORD(m_data.nMode);
        return (JUMPBOX_MODE)ret;
    }
    // ��ȡ���½ǵ�ѡ����ı�, ���� nRadio ��������ȡ�ĸ���ѡ����ı�
    inline LPCWSTR GetRadioText(JUMPBOX_MODE nRadio) const
    {
#define _retuen_str(_s, _r) return !_s.empty() ? _s.c_str() : _r
        switch (nRadio)
        {
        case JUMPBOX_MODE_START:
            _retuen_str(m_data.pszRadio1, L"�ļ���ʼ(&B)");
        case JUMPBOX_MODE_NOW:
            _retuen_str(m_data.pszRadio2, L"����λ��");
        case JUMPBOX_MODE_NOW_PREV:
            _retuen_str(m_data.pszRadio3, L"����λ������");
        case JUMPBOX_MODE_END:
            _retuen_str(m_data.pszRadio4, L"�ļ���β(&E)");
        default:
            return L"";
        }
#undef _retuen_str
        return L"";
    }


private:

    inline virtual INT_PTR InitDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        INT_PTR ret = CDialog::InitDialog(hDlg, message, wParam, lParam);

        const int margin = 11;  // �߾�
        const int editWidth = 460;
        const int cbkWidth = 140;
        const int btnWidth = 140;
        const int height_cbb = 200;
        const int width_cbb = editWidth - 55;
        const int static_height = 20;
        const int right = margin + 55 + width_cbb;


        int top = margin;

        const DWORD styleStatic = WS_GROUP | WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE;
        DWORD style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
        DWORD styleEx = WS_EX_NOPARENTNOTIFY;

        PJUMPBOX_STRUCT pData = &m_data;
        pData->hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 55, top, width_cbb, height_cbb, hDlg, IDC_CBB_INPUT);
        //CDrawComboBox::InitCombobox(pData->hCbb, m_clr);
        RECT rc;
        GetWindowRect(pData->hCbb, &rc);
        const int cbbHeight = rc.bottom - rc.top;
        CreateControl(L"static", L"��תλ��", styleEx, styleStatic, margin, top, 55, cbbHeight, hDlg, 0);
        top += cbbHeight + 5;


        int count = 0;
        for (auto it = m_arr_text.rbegin(); it != m_arr_text.rend(); ++it)
        {
            LPCWSTR text = it->c_str();
            if (text && *text)
            {
                Combobox_AddString(pData->hCbb, text);
                count++;
                //if (count >= 20)
                //    break;  // �����ʾ20��
            }
        }

        if (count > 0)
            SendMessageW(pData->hCbb, CB_SETCURSEL, 0, 0);


        CreateControl(L"static", L"�����...", styleEx, styleStatic, margin, top, width_cbb, static_height, hDlg, 0);
        top += static_height + 5;

        const int styleBtn = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
        style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON;
        const int radioWidth = 120;
        int saveTop = top;
        int left = margin + 20;

        LPCWSTR pszRadio1 = GetRadioText(JUMPBOX_MODE_START);
        LPCWSTR pszRadio2 = GetRadioText(JUMPBOX_MODE_NOW);
        LPCWSTR pszRadio3 = GetRadioText(JUMPBOX_MODE_NOW_PREV);
        LPCWSTR pszRadio4 = GetRadioText(JUMPBOX_MODE_END);

        if (0)  // ����Ļ�Ӧ����ʾ����������ļ���ʼ
        {
            pszRadio1 = L"��һ������(&B)";
            pszRadio2 = L"����λ��";
            pszRadio3 = L"����λ������";
            pszRadio4 = L"���һ������(&E)";
        }

        pData->hStart = CreateControl(L"button", pszRadio1, styleEx, style | WS_GROUP, left, top, radioWidth, static_height, hDlg, IDC_RADIO_START);
        top += static_height + 5;
        pData->hNow = CreateControl(L"button", pszRadio2, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_NOW);
        top += static_height + 5;
        pData->hNow2 = CreateControl(L"button", pszRadio3, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_NOW2);
        top += static_height + 5;
        pData->hEnd = CreateControl(L"button", pszRadio4, styleEx, style, left, top, radioWidth, static_height, hDlg, IDC_RADIO_END);


        top = saveTop - 5 - (static_height / 2);
        const int btnHeight = static_height * 2 + 5 + (static_height / 2);
        left = right - btnWidth;
        CreateControl(L"button", L"��ת", styleEx, styleBtn | BS_DEFPUSHBUTTON, left, top, btnWidth, btnHeight, hDlg, IDOK);
        top += btnHeight + 5;
        CreateControl(L"button", L"ȡ��", styleEx, styleBtn, left, top, btnWidth, btnHeight, hDlg, IDCANCEL);


        left -= 80;
        top = saveTop;
        top += static_height + 5;
        top += static_height + 5;
        pData->h10 = CreateControl(L"button", L"10����", styleEx, style | WS_GROUP, left, top, 70, static_height, hDlg, IDC_RADIO_10);
        top += static_height + 5;
        pData->h16 = CreateControl(L"button", L"16����", styleEx, style, left, top, 70, static_height, hDlg, IDC_RADIO_16);

        HWND hRadio = HIWORD(pData->nMode) ? pData->h16 : pData->h10;
        int mode = LOWORD(pData->nMode);
        SendMessageW(hRadio, BM_SETCHECK, BST_CHECKED, 0);

        hRadio = pData->hStart;
        if (mode == 0)
            hRadio = pData->hStart;
        else if (mode == 1)
            hRadio = pData->hNow;
        else if (mode == 2)
            hRadio = pData->hNow2;
        else if (mode == 3)
            hRadio = pData->hEnd;
        SendMessageW(hRadio, BM_SETCHECK, BST_CHECKED, 0);

        SetFocus(pData->hCbb);
        return ret;
    }
    inline virtual INT_PTR OnCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PJUMPBOX_STRUCT pData = &m_data;
        const int id = LOWORD(wParam);
        const int code = HIWORD(wParam);
        switch (id)
        {
        case IDOK:
        {
            int isHex = 0;
            int mode = 0;

            isHex = btn_isCheck(pData->h16);

            if (btn_isCheck(pData->hNow))
                mode = JUMPBOX_MODE_NOW;
            else if (btn_isCheck(pData->hNow2))
                mode = JUMPBOX_MODE_NOW_PREV;
            else if (btn_isCheck(pData->hEnd))
                mode = JUMPBOX_MODE_END;
            else
                mode = JUMPBOX_MODE_START;


            pData->pResult = GetWndText(pData->hCbb);
            push_back(m_arr_text, pData->pResult);
            LPCWSTR pStr = pData->pResult.c_str();
            size_t len = pData->pResult.size();
            if (len > 1 && _wcsnicmp(pStr, L"0x", 2) == 0)
            {
                isHex = 1;
                pStr += 2;
            }

            INT64 num = 0;
            if (isHex)
            {
                swscanf_s(pStr, L"%016llX", &num);
            }
            else
            {
                num = _wtoll(pData->pResult.c_str());
            }

            pData->nMode = MAKELONG(mode, isHex);
            pData->pos = num;
            pData->isOk = TRUE;
            EndDialog(hDlg, 1);
            break;
        }
        case IDCANCEL:
        {
            EndDialog(hDlg, 0);
            break;
        }
        case IDC_CBB_INPUT:
            return OnCommandCombobox(hDlg, message, wParam, lParam);
        case IDC_RADIO_START:   // �ļ���ʼ
            pData->nMode = MAKELONG(JUMPBOX_MODE_START, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_NOW:     // ����λ��
            pData->nMode = MAKELONG(JUMPBOX_MODE_NOW, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_NOW2:    // ����λ������
            pData->nMode = MAKELONG(JUMPBOX_MODE_NOW_PREV, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_END:     // �ļ�����
            pData->nMode = MAKELONG(JUMPBOX_MODE_END, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_10:      // 10����
            pData->nMode &= ~JUMPBOX_MODE_HEX;
            break;
        case IDC_RADIO_16:      // 16����
            pData->nMode |= JUMPBOX_MODE_HEX;
            break;
        default:
            return (INT_PTR)false;
        }
        return (INT_PTR)true;
    }
    inline INT_PTR OnCommandCombobox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        const int code = HIWORD(wParam);
        switch (code)
        {
        case CBN_EDITCHANGE:
            ComboboxEditChange();
            break;
        default:
            return (INT_PTR)false;
        }
        return (INT_PTR)true;
    }
    //inline virtual INT_PTR OnNotify(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    //{
    //    LPNMHDR hdr = (LPNMHDR)lParam;
    //    if (hdr->code != NM_CUSTOMDRAW)
    //        return false;

    //    if (hdr->idFrom != IDC_RADIO_START
    //        && hdr->idFrom != IDC_RADIO_NOW
    //        && hdr->idFrom != IDC_RADIO_NOW2
    //        && hdr->idFrom != IDC_RADIO_END
    //        && hdr->idFrom != IDC_RADIO_10
    //        && hdr->idFrom != IDC_RADIO_16
    //        )
    //        return false;
    //    return OnNotify_Button(hDlg, message, wParam, lParam, m_clr);
    //}
    inline void ComboboxEditChange()
    {
        // �����ı��ı���, 300�������������ǲ���16���Ƶ�0x��ͷ, Ȼ���Զ�ѡ��10���ƻ���16���Ƶĵ�ѡ��
        PJUMPBOX_STRUCT pData = &m_data;
        SetTimer(pData->hCbb, (UINT_PTR)pData, 300, [](HWND hWnd, UINT message, UINT_PTR timerId, DWORD dwTimer)
        {
            PJUMPBOX_STRUCT pData = (PJUMPBOX_STRUCT)timerId;
            KillTimer(hWnd, timerId);

            wchar_t buffer[4] = { 0 };
            int len = GetWindowTextLengthW(pData->hCbb);
            auto pfn_set_check = [pData]()
            {
                bool isHex = ((pData->nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX);
                btn_Check(pData->h16, isHex);
                btn_Check(pData->h10, !isHex);
            };
            if (len < 2)
            {
                // �϶�����0x��ͷ, �ж�һ��Ĭ��ѡ���ǲ���10���Ƶĵ�ѡ��, �ǵĻ�������Ϊѡ��
                pfn_set_check();
                return;
            }

            // �������0x, �Ǿ�ѡ��16���Ƶĵ�ѡ��
            GetWindowTextW(pData->hCbb, buffer, 3);
            if (_wcsnicmp(buffer, L"0x", 2) == 0)
            {
                btn_Check(pData->h16, true);
                btn_Check(pData->h10, false);
            }
            else
            {
                pfn_set_check();
            }
            bool isHex = (_wcsnicmp(buffer, L"0x", 2) == 0);

        });
    }
};