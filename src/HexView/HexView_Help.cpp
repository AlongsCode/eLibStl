#include "HexView_Help.h"


HEXVIEW_NAMESPACE_BEGIN

struct HEXVIEW_CONTROL_ID
{
    DWORD dwWinFormID;
    DWORD dwUnitID;
    HUNIT hUnit;
    HWND  hWnd;
    PVOID pData;
};

// TODO 某些命令可能会在线程内调用, 有必要处理一下线程安全的问题, 先记录
static std::vector<HEXVIEW_CONTROL_ID> s_arr_id;


HUNIT GethUnitFromId(DWORD dwWinFormID, DWORD dwUnitID, PVOID* pRet)
{
    if ( pRet ) *pRet = 0;
    for ( std::vector<HEXVIEW_CONTROL_ID>::iterator it = s_arr_id.begin(); it != s_arr_id.end(); ++it )
    {
        HEXVIEW_CONTROL_ID& id = *it;
        if ( dwWinFormID == id.dwWinFormID && dwUnitID == id.dwUnitID )
        {
            if ( pRet ) *pRet = id.pData;
            return id.hUnit;
        }
    }
    return 0;
}
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID* pRet)
{
    return GethUnitFromId(pInf->m_unit.m_dwFormID, pInf->m_unit.m_dwUnitID, pRet);
}

PVOID GetDataFromHunit(HUNIT hUnit)
{
    for ( std::vector<HEXVIEW_CONTROL_ID>::iterator it = s_arr_id.begin(); it != s_arr_id.end(); ++it )
    {
        HEXVIEW_CONTROL_ID& id = *it;
        if ( hUnit == id.hUnit )
        {
            return id.pData;
        }
    }
    return 0;
}



PVOID UpdateDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, HWND hWnd, PVOID pData)
{
    for ( std::vector<HEXVIEW_CONTROL_ID>::iterator it = s_arr_id.begin(); it != s_arr_id.end(); ++it )
    {
        HEXVIEW_CONTROL_ID& id = *it;
        if ( dwWinFormID == id.dwWinFormID && dwUnitID == id.dwUnitID )
        {
            PVOID ret = id.pData;
            id.hUnit = hUnit;
            id.pData = pData;
            id.hWnd = hWnd;
            return ret;
        }
    }
    return 0;
}
PVOID SetDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, HWND hWnd, PVOID pData)
{
    for ( std::vector<HEXVIEW_CONTROL_ID>::iterator it = s_arr_id.begin(); it != s_arr_id.end(); ++it )
    {
        HEXVIEW_CONTROL_ID& id = *it;
        if ( dwWinFormID == id.dwWinFormID && dwUnitID == id.dwUnitID )
        {
            PVOID ret = id.pData;
            id.hUnit = hUnit;
            id.pData = pData;
            id.hWnd = hWnd;
            return ret;
        }
    }

    HEXVIEW_CONTROL_ID id = { 0 };
    id.dwUnitID = dwUnitID;
    id.dwWinFormID = dwWinFormID;
    id.hUnit = hUnit;
    id.pData = pData;
    id.hWnd = hWnd;
    s_arr_id.push_back(id);
    return 0;
}

// 调用易语言的事件, 返回易语言返回的结果
// data = 要对哪个组件投递事件
// nDeal = 处理结果, 参考返回易语言是否处理了这个事件, E_EVENT_DEAL 枚举常量
// iEvent = 事件索引, EVENT_INFO2 这个数组的索引, 数组是所有事件, 索引对应事件
int CallEEvent(PCONTROL_STRUCT_BASE data, int& nDeal, int iEvent, int nArgCount, ...)
{
    HWND hWnd = (HWND)elibstl::NotifySys(NAS_GET_HWND_OF_CWND_OBJECT, data->hUnit, 0);
    if (!hWnd || !IsWindow(hWnd))
        return 0;   // 检测窗口是否正常, 如果窗口已经失效, 则不能继续投递事件
    if (nArgCount > 12)
    {
#ifdef _DEBUG
        _DBG_BREAK_MSG("事件参数数量超过12个");
#endif
        return 0;
    }
    EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, iEvent);
    eventInfo.m_nArgCount = nArgCount;

    va_list list;
    va_start(list, nArgCount);
    for (int i = 0; i < nArgCount; i++)
    {
        eventInfo.m_arg[i].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[i].m_inf.m_int = va_arg(list, int);
    }
    va_end(list);
    INT ret = elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    nDeal = E_EVENT_DEAL_NONE;
    if (ret != 0)
        nDeal = E_EVENT_DEAL_DEAL;
    if (eventInfo.m_blHasRetVal)
        nDeal |= E_EVENT_DEAL_RET;

    return eventInfo.m_infRetData.m_int;
}

HEXVIEW_NAMESPACE_END

