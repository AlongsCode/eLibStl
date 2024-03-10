#pragma once
#include "CDialog.h"
#include <algorithm>

//#include <windows.h>


enum SEARCH_MODE
{
    SEARCH_MODE_NORMAL      = 0x0000,   // 普通搜索, 一个标签一个编辑框两个按钮
    SEARCH_MODE_HEX         = 0x0001,   // 十六进制搜索, 一个标签一个组合框两个按钮
    SEARCH_MODE_ADDR        = 0x0002,   // 输入内存地址和尺寸的窗口
    SEARCH_MODE_CHECKBOX    = 0x0003,   // 比普通搜索下面多了一些选择框/单选框
};

enum SEARCH_HEXMODE
{
    SEARCH_HEXMODE_HEX      = 0x0000,   // 十六进制
    SEARCH_HEXMODE_ANSI     = 0x0001,   // ansi字符串
    SEARCH_HEXMODE_DEC      = 0x0002,   // 10进制
    SEARCH_HEXMODE_UNICODE  = 0x0003,   // Unicode字符串
    SEARCH_HEXMODE_FLOAT    = 0x0004,   // 单精度浮点数
    SEARCH_HEXMODE_DOUBLE   = 0x0005,   // 双精度浮点数
};


// 对话框类
class CSearchBox : private CDialog
{
private:
    static constexpr auto IDC_CBB_MODE     { static_cast<UINT>(1000) };    // 搜索模式组合框
    static constexpr auto IDC_CBB_INPUT    { static_cast<UINT>(1001) };    // 输入文本组合框
    static constexpr auto IDC_CBB_ADDR     { static_cast<UINT>(1000) };    // 内存地址组合框
    static constexpr auto IDC_CBB_ADDRSI   { static_cast<UINT>(1001) };    // 内存尺寸组合框

    static constexpr LPCWSTR PROP_OLDPROC   = L"{6E53D287-D4CE-4827-8D9D-5BBECA09E69C}";
    static constexpr LPCWSTR PROP_ARR_RADIO = L"{ADF73C81-40CE-4E4B-A26B-83480BAD6332}";

    struct RADIOBOX_STRUCT
    {
        HWND            hWnd;           // 单选框句柄
        int             vk;             // 按下什么键时选中这个组件
        int             id;             // 组件的ID, 可以获取点击了哪个单选框
        int             nWidth;         // 按钮计算出的宽度
        BOOL            isWrap;         // 是否换行, 为真的时候创建的组件就会换到下一行创建
        std::wstring    text;           // 标题
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
        HWND            hParent;        // 对话框父窗口

        std::wstring    pszCaption;     // 对话框标题
        std::wstring    pszTips;        // 提示文本
        std::wstring    pszOkButton;    // 搜索框确认按钮的标题
        std::wstring    pszCancelButton;// 搜索框取消按钮的标题
        PFN_DLGPROC     lpDialogFunc;   // 搜索框消息回调函数, 返回true拦截内部处理, 返回false内部默认处理, pRet是返回true时内部返回的值
        LPARAM          dwInitParam;    // 附加参数, 会传递到 WM_INITDIALOG 消息下的 lParam 参数

        std::wstring    pResult;        // 返回输入的搜索文本
        LONG64          pResult2;       // 返回输入的搜索文本2, 目前是用于内存搜索的, 用于返回输入的尺寸尺寸

        int             nHexMode;       // 十六进制搜索模式, 0=十六进制, 1=ansi字符串, 2=10进制, 3=Unicode字符串, 4=单精度浮点数, 5=双精度浮点数, 同时接收搜索时选中的模式
        int             nSearchMode;    // 搜索模式, SEARCH_MODE 枚举常量
        int             nTipsHeight;    // 提示文本的窗口高度
        int             nRadioHeight;   // 单选框一共占用的窗口高度, 所有单选框组合起来, 单选框宽度超过窗口宽度会自动换行
        BOOLEAN         isOk;           // 是否点击了确定按钮
        int             nRadioId;       // 最终选中的是哪个单选框

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
    std::vector<std::wstring>   m_arr_text; // 历史输入文本, 输入一次记录一次, 每次输入都会加入到数组最后
    std::vector<LONG64>         m_arr_size; // 历史输入文本, 内存查找的模式使用, 内存查找有输入两个值, 所以需要记录两次
    std::vector<RADIOBOX_STRUCT> m_radio;   // 单选框数组, 模式为 SEARCH_MODECHECKBOX 时使用
public:
    CSearchBox() : CDialog()
    {
        m_data.clear();
    }
    ~CSearchBox()
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
    // 返回默认尺寸数组, 可以获取回去写出配置, 下次打开重新设置
    inline const std::vector<LONG64>& GetDefaultSize()
    {
        return m_arr_size;
    }
public:
    // 使用指定参数打开搜索对话框, 所有参数留空则使用默认参数
    // 返回输入的搜索文本, 如果用户点击了取消按钮, 返回0
    inline LPCWSTR open(HWND hParent = 0,
                        LPCWSTR pszCaption = L"搜索",
                        LPCWSTR pszTips = L"请输入搜索内容",
                        LPCWSTR pszOkBtn = L"搜索",
                        LPCWSTR pszCancelBtn = L"取消",
                        SEARCH_MODE nSearchMode = SEARCH_MODE_NORMAL)
    {
        SetCaption(pszCaption);
        SetTips(pszTips);
        SetOkButtonLabel(pszOkBtn);
        SetCancelButtonLabel(pszCancelBtn);
        SetSearchMode(nSearchMode);
        return Show(hParent);
    }

    // 显示搜索对话框, 返回输入的搜索文本, 如果用户点击了取消按钮, 返回0
    // 使用的参数是对应方法设置的参数
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
            const int box_width = 20;   // 文本左边框的宽度
            const int maxWidth = 460;   // 超过这个值就需要换行
            int nWidth = 0, nHeight = 29;
            for (RADIOBOX_STRUCT& item : m_radio)
            {
                // 框的宽度 + 文本宽度 + 10像素间隔

                RECT rcText = { 0, 0, 500, 24 };
                CalcTextWidth(rcText, item.text.c_str());
                int width_text = rcText.right - rcText.left;

                item.nWidth = box_width + width_text;
                const int nowWidth = (item.nWidth + 10);
                nWidth += nowWidth;

                if (nWidth > maxWidth)
                {
                    // 换行了
                    nHeight += 29;   // 高度是24, 行间隔是5
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
    // 设置搜索框输入的内存尺寸, 这个会加入到尺寸数组的最后一个成员里, 如果数组里已经存在, 则调整到最后一个成员
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
    // 置搜索框提示文本
    inline bool SetTips(LPCWSTR text)
    {
        m_data.pszTips = text;
        return true;
    }
    // 置搜索按钮文本
    inline bool SetOkButtonLabel(LPCWSTR text)
    {
        m_data.pszOkButton = text;
        return true;
    }
    // 置取消按钮文本
    inline bool SetCancelButtonLabel(LPCWSTR text)
    {
        m_data.pszCancelButton = text;
        return true;
    }
    // 设置输入框的默认文本列表, 成员数为0或者数组为0则清空候选搜索文本, 最后一个成员显示在第一个候选位置
    // pText = 文本数组, 会忽略空文本成员
    // count = 数组元素个数
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

    // 加入输入框的默认文本列表
    inline bool PushBackDefaultText(LPCWSTR pText)
    {
        push_back(m_arr_text, std::wstring(pText));
        return true;
    }
    // 设置输入框搜索内存方式的默认尺寸文本列表
    // 成员数为0或者数组为0则清空文本, 最后一个成员显示在第一个候选位置
    // 每次点击搜索后都会记录到数组里
    // pText = 文本数组, 会忽略空文本成员
    // count = 数组元素个数
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
    // 置搜索模式
    inline bool SetSearchMode(SEARCH_MODE mode)
    {
        m_data.nSearchMode = mode;
        return true;
    }
    // 设置十六进制选择的搜索模式, 只有搜索模式是16进制的时候才有效, SEARCH_HEXMODE_ 开头枚举常量, 返回设置前的值
    inline int SetHexMode(SEARCH_HEXMODE mode)
    {
        int ret = m_data.nHexMode;
        m_data.nHexMode = mode;
        return ret;
    }

    // 插入一个单选框, 并绑定虚拟按键, 返回当前单选框数量, 按下指定按键的时候对应的单选框就会被选中
    // id = 单选框的id, 点击确定后可以调用 GetRadioCheck 来确定选择了哪个单选框
    // vk = 虚拟按键代码, VK_ 开头常量, 如果为0, 则默认会选中这个, 多个为0则选中第一关为0的单选框
    //      一个键代码占用一个字节, vk支持4个按键的组合, 每个字节为一个键代码
    // pszTitle = 单选框的标题
    inline int InsertRadio(int id, int vk, LPCWSTR pszTitle)
    {
        m_radio.emplace_back();
        RADIOBOX_STRUCT& data = m_radio.back();
        data.text = pszTitle;
        data.vk = vk;
        data.id = id + ((int)(LONG64)this);
        return (int)m_radio.size();
    }
    // 获取是哪个单选框被选中了, 返回选中的单选框ID, 如果没有选中则返回0
    inline int GetRadioCheck() const
    {
        return m_data.nRadioId - ((int)(LONG64)this);
    }


public:
    // 获取搜索框输入的文本, 如果没有输入则返回空文本, 不会返回0
    inline LPCWSTR GetResult() const
    {
        return !m_data.pResult.empty() ? m_data.pResult.c_str() : L"";
    }
    // 获取搜索框输入的内存尺寸, 如果没有输入则返回0
    inline LONG64 GetResultMemorySize() const
    {
        return m_data.pResult2;
    }
    // 重置搜索框输入的文本, 重置后再次获取会返回空文本
    inline void ResetResult()
    {
        m_data.pResult.clear();
    }
    // 重置搜索框输入的内存尺寸, 重置后再次获取会返回0
    inline void ResetResultMemorySize()
    {
        m_data.pResult2 = 0;
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
        return !m_data.pszCaption.empty() ? m_data.pszCaption.c_str() : L"搜索";
    }
    // 获取搜索框提示文本, 如果没有则返回空文本, 不会返回0
    inline LPCWSTR GetTips() const
    {
        return !m_data.pszTips.empty() ? m_data.pszTips.c_str() : L"请输入搜索内容";
    }
    // 获取搜索按钮文本, 如果没有则返回空文本, 不会返回0
    inline LPCWSTR GetOkButtonLabel() const
    {
        return !m_data.pszOkButton.empty() ? m_data.pszOkButton.c_str() : L"搜索";
    }
    // 获取取消按钮文本, 如果没有则返回空文本, 不会返回0
    inline LPCWSTR GetCancelButtonLabel() const
    {
        return !m_data.pszCancelButton.empty() ? m_data.pszCancelButton.c_str() : L"取消";
    }
    // 获取搜索模式
    inline SEARCH_MODE GetSearchMode() const
    {
        return (SEARCH_MODE)m_data.nSearchMode;
    }
    // 获取十六进制选择的搜索模式, SEARCH_HEXMODE_ 开头枚举常量
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

        const int margin = 11;  // 边距
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
        // 可以预设几种搜索方式, 不同的搜索方式创建不同的组件
        switch (pData->nSearchMode)
        {
        case SEARCH_MODE_CHECKBOX: // 比普通搜索下面多了一些选择框/单选框
        case SEARCH_MODE_NORMAL: // 普通搜索, 一个标签, 一个可输入组合框, 两个按钮
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
            CreateControl(L"static", L"搜索", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0, 0);
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
                    // 子类化处理一些事件
                    pfn_subclass(item.hWnd);

                    if (isFirst && item.vk == 0)
                        isFirst = false, btn_Check(item.hWnd, true);
                    left += radio_width + 10;

                }
                top += radio_height + 5;
            }
            break;
        }
        case SEARCH_MODE_HEX: // 十六进制窗口
        {
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 40, top, editWidth - 40, height_cbb, hDlg, IDC_CBB_MODE);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            GetWindowRect(hCbb, &rc);
            const int cbbHeight = rc.bottom - rc.top;
            CreateControl(L"static", L"类型", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0);
            top += cbbHeight + 5;

            Combobox_AddString(hCbb, L"十六进制");
            Combobox_AddString(hCbb, L"ANSI 字符串");
            Combobox_AddString(hCbb, L"十进制");
            Combobox_AddString(hCbb, L"Unicode 字符串");
            Combobox_AddString(hCbb, L"单精度浮点数");
            Combobox_AddString(hCbb, L"双精度浮点数");

            int cbbIndex = pData->nHexMode;
            if (cbbIndex < 0 || cbbIndex > 5)
                cbbIndex = 0;
            SendMessageW(hCbb, CB_SETCURSEL, cbbIndex, 0);

            style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
            CreateControl(L"static", L"搜索", styleEx, styleStatic, margin, top, 40, cbbHeight, hDlg, 0);
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + 40, top, editWidth - 40, height_cbb, hDlg, IDC_CBB_INPUT);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            top += cbbHeight + 5;
            hCbbFocus = hCbb;
            break;
        }
        case SEARCH_MODE_ADDR: // 输入内存地址和尺寸的窗口
        {
            // 上面一个显示内存地址, 下面显示内存尺寸
            const int staticWidth = 60;
            style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
            hCbb = CreateControl(L"ComboBox", 0, styleEx, style, margin + staticWidth, top, editWidth - staticWidth, height_cbb, hDlg, IDC_CBB_ADDR);
            //CDrawComboBox::InitCombobox(hCbb, m_clr);
            GetWindowRect(hCbb, &rc);
            const int cbbHeight = rc.bottom - rc.top;
            CreateControl(L"static", L"内存地址", styleEx, styleStatic, margin, top, staticWidth, cbbHeight, hDlg, 0);
            top += cbbHeight + 5;

            HWND hCbb2 = CreateControl(L"ComboBox", 0, styleEx, style, margin + staticWidth, top, editWidth - staticWidth, height_cbb, hDlg, IDC_CBB_ADDRSI);
            //CDrawComboBox::InitCombobox(hCbb2, m_clr);
            CreateControl(L"static", L"内存尺寸", styleEx, styleStatic, margin, top, staticWidth, cbbHeight, hDlg, 0);

            hCbbFocus = hCbb2;
            pszOk = L"查看内存";
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
                //    break;  // 最多显示20个
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
            case SEARCH_MODE_NORMAL:    // 普通搜索窗口
            case SEARCH_MODE_HEX:       // 十六进制窗口
            case SEARCH_MODE_CHECKBOX:  // 比普通搜索下面多了一组选择框
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
            case SEARCH_MODE_ADDR:   // 输入内存地址和尺寸的窗口
            {
                hWndTop = GetDlgItem(hDlg, IDC_CBB_ADDR);       // 内存地址
                hWndBottom = GetDlgItem(hDlg, IDC_CBB_ADDRSI);  // 内存尺寸

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

        HWND hFirst0 = 0;   // 第一个vk是0的窗口
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
                // 一共有4个组合键, 4个字节, 每个字节存放一个键代码
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