#pragma once

#include "CDialog.h"

// 跳转模式
enum JUMPBOX_MODE : int
{
    JUMPBOX_MODE_START      = 0x0000,     // 从文件开始
    JUMPBOX_MODE_NOW        = 0x0001,     // 当前位置
    JUMPBOX_MODE_NOW_PREV   = 0x0002,     // 当前位置往上
    JUMPBOX_MODE_END        = 0x0003,     // 从文件结束

    JUMPBOX_MODE_HEX        = 0x10000,    // 是否是16进制, 没有这个标志的话, 对话框显示后是选中10进制的单选框

};


// 跳转对话框
class CJumpBox : private CDialog
{
    static constexpr auto IDC_CBB_INPUT     { static_cast<UINT>(1000) };    // 输入文本组合框

    static constexpr auto IDC_RADIO_START   { static_cast<UINT>(2000) };   // 文件开始
    static constexpr auto IDC_RADIO_NOW     { static_cast<UINT>(2001) };   // 现在位置
    static constexpr auto IDC_RADIO_NOW2    { static_cast<UINT>(2002) };   // 现在位置往上
    static constexpr auto IDC_RADIO_END     { static_cast<UINT>(2003) };   // 文件结束

    static constexpr auto IDC_RADIO_10      { static_cast<UINT>(3000) };   // 10进制
    static constexpr auto IDC_RADIO_16      { static_cast<UINT>(3001) };   // 16进制

    typedef struct JUMPBOX_STRUCT
    {
        HWND            hParent;    // 对话框父窗口
        int             nMode;      // 跳转模式, 0=从文件开始, 1=当前位置, 2现在位置往上, 3=从文件结束, 高位 = 是否是16进制, 同时接收搜索时选中的模式
        int             nTextCount; // 数组元素个数

        std::wstring    pszCaption; // 对话框标题
        std::wstring    pResult;    // 返回输入的跳转文本
        INT64           pos;        // 输入的跳转文本转成的数值

        BOOL            isOk;       // 是否点击了确定按钮

        HWND            hStart;     // 左下角第一个单选框, 从0开始跳转
        HWND            hNow;       // 左下角第二个单选框, 从当前位置开始往后跳转
        HWND            hNow2;      // 左下角第三个单选框, 从当前位置往前跳转
        HWND            hEnd;       // 左下角最后一个单选框, 跳转到最后
        HWND            h10;        // 10进制单选框
        HWND            h16;        // 16进制单选框
        HWND            hCbb;       // 输入文本的组合框, 最后需要从这个组合框获取文本返回

        std::wstring    pszRadio1;  // 左下角第一个单选框的文本, 从0开始跳转
        std::wstring    pszRadio2;  // 左下角第二个单选框的文本, 从当前位置开始往后跳转
        std::wstring    pszRadio3;  // 左下角第三个单选框的文本, 从当前位置往前跳转
        std::wstring    pszRadio4;  // 左下角最后一个单选框的文本, 跳转到最后

        PFN_DLGPROC     lpDialogFunc;   // 搜索框消息回调函数, 返回true拦截内部处理, 返回false内部默认处理, pRet是返回true时内部返回的值
        LPARAM          dwInitParam;    // 附加参数, 会传递到 WM_INITDIALOG 消息下的 lParam 参数

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
    std::vector<std::wstring>   m_arr_text; // 历史输入文本, 输入一次记录一次, 每次输入都会加入到数组最后

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
    // 重置对象, 会把所有参数设置为空, 跟刚构造的对象一样, 析构会自动调用这个方法
    inline void reset()
    {
        m_data.clear();
    }

    // 返回默认文本数组, 可以获取回去写出配置, 下次打开重新设置
    inline const std::vector<std::wstring>& GetDefaultText()
    {
        return m_arr_text;
    }
public:
    // 显示跳转对话框, 返回输入的文本, 如果用户点击了取消按钮, 返回0
    // 使用的参数是对应方法设置的参数
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
    // 设置对话框过程地址, 返回设置前的值, 设置后对话框有消息会调用这个函数, 扩展对话框功能使用
    // 函数返回值为 是否拦截内部处理, 如果返回true, 内部不会处理这个消息, 返回false, 内部会处理这个消息
    // 可以在这个函数内自己创建组件和处理事件, 也可以不处理, 交给内部处理
    // 当窗口收到 WM_INITDIALOG 消息时, 默认组件已经创建完毕
    inline bool SetDialogFunc(PFN_DLGPROC pfn)
    {
        m_data.lpDialogFunc = pfn;
        return true;
    }
    // 设置对话框附加参数, 返回设置前的值
    // 传递到 WM_INITDIALOG 消息下的 lParam 参数, 只有在 WM_INITDIALOG 消息下才会传递这个参数
    inline LPARAM SetDialogParam(LPARAM param)
    {
        LPARAM ret = m_data.dwInitParam;
        m_data.dwInitParam = param;
        return ret;
    }
    // 置搜索框标题
    inline bool SetCaption(LPCWSTR text)
    {
        m_data.pszCaption = text;
        return true;
    }
    // 是否选中16进制的单选框, 返回设置前的值
    inline bool SetSelHex(bool isHex)
    {
        const bool ret = (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;
        if (isHex)
            m_data.nMode |= JUMPBOX_MODE_HEX;
        else
            m_data.nMode &= ~JUMPBOX_MODE_HEX;
        return ret;
    }
    // 设置跳转模式, 返回设置前的值, JUMPBOX_MODE_ 开头常量, 左下角4个单选框, 默认选中哪个
    inline int SetMode(JUMPBOX_MODE mode)
    {
        const bool isHex = (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;
        int ret = LOWORD(m_data.nMode);
        m_data.nMode = MAKELONG(mode, isHex);
        return ret;
    }
    // 设置输入框的默认文本列表, 需要调用方保证传递进来的文本指针的生命周期, 对话框显示之前不能被销毁
    // pText = 文本数组, count = 数组元素个数
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
    // 设置左下角单选框的文本, 根据 nRadio 来决定设置哪个单选框的文本
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
    // 获取跳转框输入的文本, 如果没有输入则返回空文本, 不会返回0
    inline LPCWSTR GetResult() const
    {
        return !m_data.pResult.empty() ? m_data.pResult.c_str() : L"";
    }
    // 获取跳转框输入的文本转换成的数值, 如果没有输入则返回0
    inline INT64 GetResultNumber() const
    {
        return m_data.pos;
    }
    // 重置跳转框输入的文本, 重置后再次获取会返回空文本
    inline void ResetResult()
    {
        m_data.pResult.clear();
        m_data.pos = 0;
    }

    // 获取设置的对话框过程地址, 如果没有设置则返回0
    inline PFN_DLGPROC GetDialogFunc() const
    {
        return m_data.lpDialogFunc;
    }
    // 获取设置的对话框附加参数, 如果没有设置则返回0
    inline LPARAM GetDialogParam() const
    {
        return m_data.dwInitParam;
    }
    // 获取搜索框标题, 如果没有则返回空文本, 不会返回0
    inline LPCWSTR GetCaption() const
    {
        return !m_data.pszCaption.empty() ? m_data.pszCaption.c_str() : L"跳转到...";
    }
    // 获取十六进制选择的搜索模式, SEARCH_HEXMODE_ 开头枚举常量
    inline bool GetSelHex() const
    {
        return (m_data.nMode & JUMPBOX_MODE_HEX) == JUMPBOX_MODE_HEX;;
    }
    // 获取跳转模式, 调用方应该根据返回的模式来决定如何跳转
    inline JUMPBOX_MODE GetMode() const
    {
        int ret = LOWORD(m_data.nMode);
        return (JUMPBOX_MODE)ret;
    }
    // 获取左下角单选框的文本, 根据 nRadio 来决定获取哪个单选框的文本
    inline LPCWSTR GetRadioText(JUMPBOX_MODE nRadio) const
    {
#define _retuen_str(_s, _r) return !_s.empty() ? _s.c_str() : _r
        switch (nRadio)
        {
        case JUMPBOX_MODE_START:
            _retuen_str(m_data.pszRadio1, L"文件开始(&B)");
        case JUMPBOX_MODE_NOW:
            _retuen_str(m_data.pszRadio2, L"现在位置");
        case JUMPBOX_MODE_NOW_PREV:
            _retuen_str(m_data.pszRadio3, L"现在位置往上");
        case JUMPBOX_MODE_END:
            _retuen_str(m_data.pszRadio4, L"文件结尾(&E)");
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

        const int margin = 11;  // 边距
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
        CreateControl(L"static", L"跳转位置", styleEx, styleStatic, margin, top, 55, cbbHeight, hDlg, 0);
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
                //    break;  // 最多显示20个
            }
        }

        if (count > 0)
            SendMessageW(pData->hCbb, CB_SETCURSEL, 0, 0);


        CreateControl(L"static", L"相对于...", styleEx, styleStatic, margin, top, width_cbb, static_height, hDlg, 0);
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

        if (0)  // 表项的话应该显示表项而不是文件开始
        {
            pszRadio1 = L"第一个表项(&B)";
            pszRadio2 = L"现在位置";
            pszRadio3 = L"现在位置往上";
            pszRadio4 = L"最后一个表项(&E)";
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
        CreateControl(L"button", L"跳转", styleEx, styleBtn | BS_DEFPUSHBUTTON, left, top, btnWidth, btnHeight, hDlg, IDOK);
        top += btnHeight + 5;
        CreateControl(L"button", L"取消", styleEx, styleBtn, left, top, btnWidth, btnHeight, hDlg, IDCANCEL);


        left -= 80;
        top = saveTop;
        top += static_height + 5;
        top += static_height + 5;
        pData->h10 = CreateControl(L"button", L"10进制", styleEx, style | WS_GROUP, left, top, 70, static_height, hDlg, IDC_RADIO_10);
        top += static_height + 5;
        pData->h16 = CreateControl(L"button", L"16进制", styleEx, style, left, top, 70, static_height, hDlg, IDC_RADIO_16);

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
        case IDC_RADIO_START:   // 文件开始
            pData->nMode = MAKELONG(JUMPBOX_MODE_START, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_NOW:     // 现在位置
            pData->nMode = MAKELONG(JUMPBOX_MODE_NOW, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_NOW2:    // 现在位置往上
            pData->nMode = MAKELONG(JUMPBOX_MODE_NOW_PREV, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_END:     // 文件结束
            pData->nMode = MAKELONG(JUMPBOX_MODE_END, pData->nMode & JUMPBOX_MODE_HEX);
            break;
        case IDC_RADIO_10:      // 10进制
            pData->nMode &= ~JUMPBOX_MODE_HEX;
            break;
        case IDC_RADIO_16:      // 16进制
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
        // 输入文本改变了, 300毫秒后检测输入的是不是16进制的0x开头, 然后自动选中10进制或者16进制的单选框
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
                // 肯定不是0x开头, 判断一下默认选中是不是10进制的单选框, 是的话就设置为选中
                pfn_set_check();
                return;
            }

            // 输入的是0x, 那就选中16进制的单选框
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