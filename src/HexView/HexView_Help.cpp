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

// TODO ĳЩ������ܻ����߳��ڵ���, �б�Ҫ����һ���̰߳�ȫ������, �ȼ�¼
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

// ���������Ե��¼�, ���������Է��صĽ��
// data = Ҫ���ĸ����Ͷ���¼�
// nDeal = ������, �ο������������Ƿ���������¼�, E_EVENT_DEAL ö�ٳ���
// iEvent = �¼�����, EVENT_INFO2 ������������, �����������¼�, ������Ӧ�¼�
int CallEEvent(PCONTROL_STRUCT_BASE data, int& nDeal, int iEvent, int nArgCount, ...)
{
    HWND hWnd = (HWND)elibstl::NotifySys(NAS_GET_HWND_OF_CWND_OBJECT, data->hUnit, 0);
    if (!hWnd || !IsWindow(hWnd))
        return 0;   // ��ⴰ���Ƿ�����, ��������Ѿ�ʧЧ, ���ܼ���Ͷ���¼�
    if (nArgCount > 12)
    {
#ifdef _DEBUG
        _DBG_BREAK_MSG("�¼�������������12��");
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

