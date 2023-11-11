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

    // 记录所有组件申请的内存, 键名为窗口句柄
    static std::unordered_map<HWND, PCONTROL_STRUCT_BASE> m_map;

    // 需要释放的数据, 一个组件对应一个结构
    static std::vector<PCONTROL_STRUCT_BASE> s_free_ptr;

    HUNIT WINAPI ECreate(LPBYTE pAllData, INT cbData, DWORD dwStyle, HWND hParent, UINT nID, \
                                HMENU hMenu, INT x, INT y, INT cx, INT cy, DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL bInDesignMode
    );
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText);
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit);
    BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);
    BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);
    INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2);

    LRESULT CALLBACK OnNotify(HWND hWnd, LPNMHDR hdr, LPVOID lpParam);



}
EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_HexView(INT nInterfaceNO)
{
    switch ( nInterfaceNO )
    {
    case ITF_CREATE_UNIT:               // 创建组件
        return (PFN_INTERFACE)elibstl::hexview::ECreate;
    case ITF_NOTIFY_PROPERTY_CHANGED:   // 通知某属性数据被用户修改
        return (PFN_INTERFACE)elibstl::hexview::EChange;
    case ITF_GET_ALL_PROPERTY_DATA:     // 取全部属性数据
        return (PFN_INTERFACE)elibstl::hexview::EGetAlldata;
    case ITF_GET_PROPERTY_DATA:         // 取某属性数据
        return (PFN_INTERFACE)elibstl::hexview::EGetData;
    case ITF_DLG_INIT_CUSTOMIZE_DATA:   // 使用对话框设置自定义数据
        return (PFN_INTERFACE)elibstl::hexview::EInputW;
    case ITF_GET_NOTIFY_RECEIVER:       // 取组件的附加通知接收者(PFN_ON_NOTIFY_UNIT)
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
            // 不是重新创建的窗口才初始化属性信息, 已经创建的窗口属性都有记录了
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
            memcpy(lf.lfFaceName, L"宋体", 6);
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

    // 解析属性, 如果返回假那就需要设置默认值, 返回真表示有属性
    static bool ParsePropData(PHEXVIEW_PROPERTY pData, LPBYTE pAllPropertyData, INT nAllPropertyDataSize)
    {
        LPBYTE pBuf = pAllPropertyData;
        HEXVIEW_PROPERTY& prop = *pData;
        if ( !pBuf )
            return false;   // 没有处理属性, 返回假, 外部给默认值
        prop.version        = read_int32(pBuf);     // 版本号, 这个不会显示到属性里, 内部使用, 用来判断数据结构的
        prop.border         = read_int32(pBuf);     // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
        prop.TextColor      = read_int32(pBuf);     // 文本颜色
        prop.TextBackColor  = read_int32(pBuf);     // 文本背景颜色
        prop.BackColor      = read_int32(pBuf);     // 背景颜色
        prop.Editable       = read_int32(pBuf);     // 允许编辑, 本属性指定是否允许编辑

        prop.fontSize = read_font(pBuf, prop.font);      // 1. 读取字体, 写入的是A版结构, 以后都使用这个结构, 字体一般用不上W版
        Ctl_SetFontData(prop.font, prop.fontSize, pData->hFont, prop.fontSize ? &prop.font : 0);

        size_t nReadSize = (LPBYTE)pBuf - pAllPropertyData;
        if ( nReadSize == (size_t)nAllPropertyDataSize )
            return true; // 已经解析到尾巴了

        // 为后续版本准备

        return false;
    }
    // 创建组件
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
        //    // 不是重新创建的窗口才初始化属性信息, 已经创建的窗口属性都有记录了
        //    s_free_ptr.push_back(pData);
        //}


        PHEXVIEW_PROPERTY pData = new HEXVIEW_PROPERTY;
        memset(pData, 0, sizeof(HEXVIEW_PROPERTY));

        if ( !ParsePropData(pData, pAllData, cbData) )
        {
            HEXVIEW_PROPERTY& prop = *pData;
            prop.BackColor = RGB(255, 255, 255);
            prop.TextColor = RGB(0, 0, 0);
            prop.Editable = false;
            //prop.TextBackColor = 

            // 默认配色按照下面的颜色值设置
            //HexView->clrTextSel = RGB(255, 255, 255);
            //HexView->clrText1 = RGB(0, 0, 128);
            //HexView->clrText2 = RGB(0, 0, 255);
            //HexView->clrTextSel1 = RGB(255, 255, 127);
            //HexView->clrTextSel2 = RGB(255, 255, 0);
            //HexView->clrTextAddress = RGB(0, 0, 0);
            //HexView->clrLine = RGB(204, 206, 219);
            //HexView->clrTextBackground = RGB(255, 255, 255);
            //HexView->clrSelTextBack = RGB(8, 36, 107);
            //HexView->clrModifiedText = RGB(255, 0, 0);
            //HexView->clrModifiedTextSel = RGB(0, 255, 255);
        }
        pData->hDesignWnd = hDesignWnd;
        pData->hWndParent = hParent;
        pData->id = nID;
        pData->dwWinFormID = dwWinFormID;
        pData->dwUnitID = dwUnitID;
        pData->blInDesignMode = bInDesignMode;
        pData->style = dwStyle;
        pData->styleCtl = 0;
        pData->styleEx = 0;
        pData->hUnit = 0;
        pData->data = new std::vector<BYTE>;
        pData->modi = new std::vector<BYTE>;
        pData->hWnd = CreateHexView(0, dwStyle | WS_VISIBLE | WS_CHILD,
                                      x, y, cx, cy, hParent, nID, pData);
        
        SetWindowLongPtrW(pData->hWnd, 0, (LONG_PTR)pData);
        HexView_BindNotify(pData->hWnd, OnNotify, pData);
        return elibstl::make_cwnd(pData->hWnd);
    }


    // 通知某属性数据被用户修改
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
    {
        return false;
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hHexView, 0);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        switch ( nPropertyIndex )
        {
        case HEXVIEW_PROP_BORDER:       // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
            prop.border = min(max(0, pPropertyVaule->m_int), 5);
            elibstl::ChangeBorder(pData->hWnd, prop.border);
            break;
        case HEXVIEW_PROP_TEXTCOLOR:    // 文本颜色
            prop.TextColor = pPropertyVaule->m_int;
            InvalidateRect(pData->hWnd, 0, 0);
            break;
        case HEXVIEW_PROP_TEXTBACKCOLOR:// 文本背景颜色
            prop.TextBackColor = pPropertyVaule->m_int;
            InvalidateRect(pData->hWnd, 0, 0);
            break;
        case HEXVIEW_PROP_BACKCOLOR:    // 背景颜色
            prop.BackColor = pPropertyVaule->m_int;
            InvalidateRect(pData->hWnd, 0, 0);
            break;
        case HEXVIEW_PROP_FONT:         // 字体属性
        {
            Ctl_SetFontData(prop.font, prop.fontSize, pData->hFont, (LPLOGFONTA)pPropertyVaule->m_data.m_pData);
            SendMessageW(pData->hWnd, WM_SETFONT, (WPARAM)pData->hFont, 1);
            //InvalidateRect(pData->hWnd, 0, 0);
            break;
        }
        case HEXVIEW_PROP_EDITABLE:     // 允许编辑, 本属性指定是否允许编辑
            prop.Editable = pPropertyVaule->m_int;
            break;
        default:
            break;
        }
        return 0;
    }

    // 取全部属性数据
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
    {
        return 0;
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hHexView, 0);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        std::vector<BYTE> buffer;
        buffer.reserve(0x1000);
        buffer.clear();
        int size = 0;                // 实际写入缓冲区的字节数

        size += write_int32(buffer, HEXVIEW_VERSION     );  // 版本号, 每次写入的都是最新版的版本号
        size += write_int32(buffer, prop.border         );  // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
        size += write_int32(buffer, prop.TextColor      );  // 文本颜色
        size += write_int32(buffer, prop.TextBackColor  );  // 文本背景颜色
        size += write_int32(buffer, prop.BackColor      );  // 背景颜色
        size += write_int32(buffer, prop.Editable       );  // 允许编辑, 本属性指定是否允许编辑

        size += write_font(buffer, &prop.font, prop.fontSize);  // 写入字体, 写入的是A版结构, 以后都使用这个结构, 字体一般用不上W版


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

    // 取某属性数据
    BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
    {
        // 取某属性数据到pPropertyValue中, 成功返回真, 否则返回假
        // 注意：如果在设计时(由调用PFN_CREATE_UNIT时的blInDesignMode参数决定)
        // pPropertyValue必须返回所存储的值。如果在运行时(blInDesignMode为假)
        // 必须返回实际的当前实时值
        // 比如说, 编辑框窗口单元的"内容"属性, 设计时必须返回内部所保存的值
        // 而运行时就必须调用 GetWindowText 去实时获取

        return false;
        HWND hHexView = elibstl::get_hwnd_from_hunit(hUnit);
        if ( !hHexView ) return 0;
        PHEXVIEW_PROPERTY pData = (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hHexView, 0);
        if ( !pData ) return 0;
        HEXVIEW_PROPERTY& prop = *pData;

        switch ( nPropertyIndex )
        {
        case HEXVIEW_PROP_BORDER:       // 边框, 0=无边框, 1=凹入式, 2=凸出式, 3=浅凹入式, 4=镜框式, 5=单线边框式
            pPropertyVaule->m_int = prop.border;
            break;
        case HEXVIEW_PROP_TEXTCOLOR:    // 文本颜色
            pPropertyVaule->m_int = prop.TextColor;
            break;
        case HEXVIEW_PROP_TEXTBACKCOLOR:// 文本背景颜色
            pPropertyVaule->m_int = prop.TextBackColor;
            break;
        case HEXVIEW_PROP_BACKCOLOR:    // 背景颜色
            pPropertyVaule->m_int = prop.BackColor;
            break;
        case HEXVIEW_PROP_FONT:         // 字体属性
        {
            if ( prop.fontSize > 0 )
            {
                pPropertyVaule->m_data.m_pData = (LPBYTE)&prop.font;
                pPropertyVaule->m_data.m_nDataSize = sizeof(prop.font);
            }
            break;
        }
        case HEXVIEW_PROP_EDITABLE:     // 允许编辑, 本属性指定是否允许编辑
            pPropertyVaule->m_int = prop.Editable;
            break;
        default:
            break;
        }
        return 0;
    }

    // 弹出对话框方法
    BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
    {
        // 用作设置类型为UD_CUSTOMIZE的单元属性
        // 如果需要重新创建该单元才能修改单元外形, 请返回真
        // pblModified 不为NULL, 请在其中返回是否被用户真正修改(便于易语言IDE建立UNDO记录)

        return 0;
    }

    // 取组件的附加通知接收者(PFN_ON_NOTIFY_UNIT)
    INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
    {
        switch ( nMsg )
        {
        case NU_GET_CREATE_SIZE_IN_DESIGNER:
        {
            // 取设计时组件被单击放置到窗体上时的默认创建尺寸
            // dwParam1: 类型: INT*, 返回宽度(单位像素)
            // dwParam2: 类型: INT*, 返回高度(单位像素)
            // 成功返回1,失败返回0.
            *( (int*)dwParam1 ) = 200; // 组件拖放到ide上就使用这个默认宽度
            *( (int*)dwParam2 ) = 100; // 组件拖放到ide上就使用这个默认高度
            return 1; // 使用修改后的宽高, 自己根据需要修改
            break;
        }
        default:
            return 0;
        }
        return 0;
    }

    LRESULT CALLBACK OnNotify(HWND hWnd, LPNMHDR hdr, LPVOID lpParam)
    {
        PHEXVIEW_PROPERTY pData = (PHEXVIEW_PROPERTY)lpParam;

        switch ( hdr->code )
        {
        case HVN_SEARCH:    // 搜索项目
            //return _search_bin((PNMHEXSEARCH)lParam, mem);
        case HVN_GETDISPINFO:
        {
            PNMHVDISPINFO DispInfo = (PNMHVDISPINFO)hdr;
            const SIZE_T index = DispInfo->Item.NumberOfItem;
            std::vector<BYTE>& data = *pData->data;
            std::vector<BYTE>& modi = *pData->modi;
            if ( index >= data.size() )
                break;  // 越界了

            LPBYTE pBase = (LPBYTE)( &data[index] );
            if ( DispInfo->Item.Mask & HVIF_ADDRESS )
            {
                DispInfo->Item.Address = (ULONG64)pData->pAddress + index;
            }
            if ( DispInfo->Item.Mask & HVIF_BYTE )
            {
                DispInfo->Item.Value = *pBase;
                DispInfo->Item.State = ( modi[index] ) ? HVIS_MODIFIED : 0;
            }
            break;
        }
        case HVN_ITEMCHANGING:
        {
            PNMHEXVIEW HexView = (PNMHEXVIEW)hdr;
            const SIZE_T index = HexView->Item.NumberOfItem;
            std::vector<BYTE>& data = *pData->data;
            std::vector<BYTE>& modi = *pData->modi;
            if ( index >= data.size() )
                break;  // 越界了
            LPBYTE pBase = (LPBYTE)( &data[index] );
            *pBase = HexView->Item.Value;
            modi[index] = true;    // 记录这个成员已经修改
            break;
        }
        case HVN_COPYDATA:
        {
            PNMHEXCOPYDATA arg = (PNMHEXCOPYDATA)hdr;
            std::vector<BYTE>& data = *pData->data;
            size_t size = data.size();
            if ( arg->nSize > size )
                arg->nSize = size;
            arg->Address = (ULONG64)pData->pAddress;
            memcpy(arg->pBuf, &data[0], arg->nSize);
            return 1;
        }
        default:
            return 0;
        }
        return 0;
    }


}


namespace elibstl
{

    // 命令索引, 在HexView_CmdDef.cpp里定义
    static INT s_dtCmdIndexcommobj_HexView[] = { 325 };

    // 事件
    static EVENT_INFO2 s_Event_HexView[] =
    {
        /*000*/ {"事件待编辑", "等待加这个功能", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
        
    };

    // 属性
    static UNIT_PROPERTY s_Member_HexView[] =
    {
        //FIXED_WIN_UNIT_PROPERTY,
        /*000*/ {"左边", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*001*/ {"顶边", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*002*/ {"宽度", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*003*/ {"高度", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
        /*004*/ {"标记", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
        /*005*/ {"可视", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
        /*006*/ {"禁止", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
        /*007*/ {"鼠标指针", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},

        // 以上属性是易语言需要的默认属性, 每个组件都必须有, 但是可以手动隐藏
        // 以下属性是组件自身带的, 这些不是强制需要的
        // 这些属性在易语言的回调里是从0开始的, 所以, 这些序号也从0开始
         
    //    //1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束
    

        /*000*/ {"边框", "border", NULL, UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
        
        /*001*/ {"文本颜色1", "TextColor1", "文本颜色, 第一个格子的颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL },
        /*002*/ {"文本颜色2", "TextColor2", "文本颜色, 第二个格子的颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL },
        /*003*/ {"文本选中颜色1", "TextColorSel1", "文本选中颜色, 第一个格子的颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL },
        /*004*/ {"文本选中颜色2", "TextColorSel2", "文本选中颜色, 第二个格子的颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL },
        
        /*005*/ {"背景颜色", "BackColor", "背景颜色", UD_COLOR_BACK, _PROP_OS(__OS_WIN), NULL },
        /*006*/ {"文本选中背景色", "TextBackColorSel", "选中文本背景颜色", UD_COLOR_BACK, _PROP_OS(__OS_WIN), NULL },
        
        /*007*/ {"文本颜色_文本区", "clrText_text", "右边字符用", UD_COLOR, _PROP_OS(__OS_WIN), NULL },
        /*008*/ {"文本地址颜色", "TextColorAddress", "左边地址的文本颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL},

        /*009*/ {"已修改文本颜色", "clrModifiedText", "修改过的文本颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
        /*010*/ {"已修改文本选中颜色", "clrModifiedTextSel", "修改过的文本颜色, 选中的颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
        /*011*/ {"线条颜色", "clrLine", "线条颜色", UD_COLOR, _PROP_OS(__OS_WIN), NULL},
        
        /*012*/ {"字体", "font", "非等宽字体会显示异常, 请选择等宽字体", UD_FONT, _PROP_OS(__OS_WIN), NULL },
        /*013*/ {"允许编辑", "Editable", "是否允许编辑, 默认不可编辑", UD_BOOL, _PROP_OS(__OS_WIN), NULL},

    //COLORREF    clrTextSel;         // 文本颜色, 选中的文本颜色, 右边字符用
    //COLORREF    clrTextAddress;     // 文本颜色, 左边地址的颜色
    //COLORREF    clrText1;           // 文本颜色, 第一个格子的颜色
    //COLORREF    clrText2;           // 文本颜色, 第二个格子的颜色
    //COLORREF    clrTextSel1;        // 选中文本颜色, 第一个格子的颜色
    //COLORREF    clrTextSel2;        // 选中文本颜色, 第二个格子的颜色
    //COLORREF    clrTextBackground;  // 文本背景颜色
    //COLORREF    clrSelTextBack;     // 选中文本背景颜色
    //COLORREF    clrModifiedText;    // 修改过的文本颜色
    //COLORREF    clrModifiedTextSel; // 修改过的文本颜色, 选中的颜色
    //COLORREF    clrLine;            // 线条颜色, 包括边框色
        
    };
    //1=中文名字,2=英文名字,3=详细解释,4=命令数量,5=索引值,6=标志 LDT_
    //类型为窗口或菜单组件时有效 7=资源ID,8=事件数量,9=组件事件数组,10=属性数  11=属性数组 12=组件交互子程序
    //不为窗口、菜单组件或为枚举数据类型时才有效 13=成员数量,14=成员数据数组
    LIB_DATA_TYPE_INFO HexView_control =
    {
        "十六进制编辑框",
        "HexView",
        "16进制编辑器",
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