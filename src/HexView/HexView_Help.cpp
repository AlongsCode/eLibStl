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

HEXVIEW_NAMESPACE_END

