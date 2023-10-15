#include "HexView_Control.h"
#include <unordered_map>
#include "../../include/ElibHelp.h"


namespace elibstl::hexview
{
    using namespace HEXVIEW_NAMESPACE;

    std::unordered_map<HWND, WNDPROC> m_map_subclass_hexview;
    std::unordered_map<HWND, PHEXVIEW_PROPERTY> m_map_hexview;
    HUNIT WINAPI ECreate(LPBYTE pAllData, INT cbData, DWORD dwStyle, HWND hParent, UINT nID, \
                                HMENU hMenu, INT x, INT y, INT cx, INT cy, DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL bInDesignMode
    );
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText);
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit);
    BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);
    BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);
    INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2);

    LRESULT CALLBACK WndProc_Parent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
    // 创建组件
    HUNIT WINAPI ECreate(LPBYTE pAllData, INT cbData, DWORD dwStyle,
                         HWND hParent, UINT nID, HMENU hMenu,
                         INT x, INT y, INT cx, INT cy,
                         DWORD dwWinFormID, DWORD dwUnitID,
                         HWND hDesignWnd, BOOL bInDesignMode)
    {
        PHEXVIEW_PROPERTY pData = new HEXVIEW_PROPERTY;
        memset(pData, 0, sizeof(HEXVIEW_PROPERTY));
        pData->hDesignWnd       = hDesignWnd;
        pData->hWndParent       = hParent;
        pData->id               = nID;
        pData->dwWinFormID      = dwWinFormID;   
        pData->dwUnitID         = dwUnitID;      
        pData->blInDesignMode   = bInDesignMode;
        pData->style            = dwStyle;       
        pData->styleCtl         = 0;             
        pData->styleEx          = 0;             
        pData->hUnit            = 0;
        pData->data = new std::vector<BYTE>;
        pData->modi = new std::vector<BYTE>;
        pData->hWnd = CreateHexView(0, dwStyle | WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      x, y, cx, cy, hParent, nID, pData);
        
        m_map_hexview[hParent] = pData;
        m_map_hexview[pData->hWnd] = pData;

        SetWindowLongPtrW(pData->hWnd, 0, (LONG_PTR)pData);
        auto it = m_map_subclass_hexview.find(hParent);
        if ( it == m_map_subclass_hexview.end() )
        {
           WNDPROC oldProc = (WNDPROC)SetWindowLongPtrA(hParent, GWLP_WNDPROC, (LONG_PTR)WndProc_Parent);
           pData->oldProc = oldProc;
        }
        return elibstl::make_cwnd(pData->hWnd);
    }

    // 通知某属性数据被用户修改
    BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
    {
        switch ( nPropertyIndex )
        {
        case 0:
            break;
        default:
            break;
        }
        return 0;
    }

    // 取全部属性数据
    HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
    {
        // TODO 这里需要获取全部属性保存起来
        std::vector<BYTE> buffer;
        const size_t size = buffer.size();
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
        switch ( nPropertyIndex )
        {
        case 0:
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

    LRESULT CALLBACK OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, PHEXVIEW_PROPERTY pData, bool& isDeal)
    {
        LPNMHDR hdr = (LPNMHDR)lParam;
        if ( hdr->hwndFrom != pData->hWnd )
            return DefWindowProcW(hWnd, message, wParam, lParam);

        isDeal = true;
        switch ( hdr->code )
        {
        case HVN_SEARCH:    // 搜索项目
            //return _search_bin((PNMHEXSEARCH)lParam, mem);
        case HVN_GETDISPINFO:
        {
            PNMHVDISPINFO DispInfo = (PNMHVDISPINFO)lParam;
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
            PNMHEXVIEW HexView = (PNMHEXVIEW)lParam;
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
            PNMHEXCOPYDATA arg = (PNMHEXCOPYDATA)lParam;
            std::vector<BYTE>& data = *pData->data;
            size_t size = data.size();
            if ( arg->nSize > size )
                arg->nSize = size;
            arg->Address = (ULONG64)pData->pAddress;
            memcpy(arg->pBuf, &data[0], arg->nSize);
            return 1;
        }
        default:
            isDeal = false;
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
        return 0;
    }


    LRESULT CALLBACK WndProc_Parent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PHEXVIEW_PROPERTY pData = m_map_hexview[hWnd];
        if ( !pData )
            return DefWindowProcA(hWnd, message, wParam, lParam);
        switch ( message )
        {
        case WM_NOTIFY:
        {
            bool isDeal = false;
            LRESULT ret = OnNotify(hWnd, message, wParam, lParam, pData, isDeal);
            return ret;
            return isDeal;
        }
        default:
            break;
        }
        return CallWindowProcA(pData->oldProc, hWnd, message, wParam, lParam);
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
        FIXED_WIN_UNIT_PROPERTY,
        //1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

        /*000*/ {"待增加", "Def", "等增加", UD_INT, _PROP_OS(__OS_WIN), ""},
        
    };
    //1=中文名字,2=英文名字,3=详细解释,4=命令数量,5=索引值,6=标志 LDT_
    //类型为窗口或菜单组件时有效 7=资源ID,8=事件数量,9=组件事件数组,10=属性数  11=属性数组 12=组件交互子程序
    //不为窗口、菜单组件或为枚举数据类型时才有效 13=成员数量,14=成员数据数组
    LIB_DATA_TYPE_INFO HexView_control =
    {
        "进制框",
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