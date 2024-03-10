#include "HexView_Control.h"
#include "../../include/ElibHelp.h"

#define HEXVIEW_ESTLFNAME(_n) HEXVIEW_NAMESPACE::_n, #_n

using namespace HEXVIEW_NAMESPACE;
//HEXVIEW_NAMESPACE_BEGIN

// ������������ݲ����׵�ַ����Ա��Ŀ�� ���صĵ�ַ����Ҫ�����ͷ�
inline LPBYTE GetAryElementInf_HexView(void* pAryData, LPINT pnElementCount)
{
	if (pnElementCount)*pnElementCount = 0;
	if (!pAryData)return 0;
	LPINT pnData = (LPINT)pAryData;
	INT nArys = *pnData++;  // ȡ��ά����
	// �����Ա��Ŀ��
	INT nElementCount = 1;
	while (nArys > 0)
	{
		nElementCount *= *pnData++;
		nArys--;
	}

	if (pnElementCount)
		*pnElementCount = nElementCount;
	return (LPBYTE)pnData;
}
//HEXVIEW_NAMESPACE_END

// ��������, һ���ֽڼ�����
EXTERN_C void fn_hexview_setdata(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hHexView = elibstl::get_hwnd_from_arg(pArgInf);
	if (!hHexView)
		return;
    PHEXVIEW_PROPERTY pData = GetHexViewData(hHexView);
	if (!pData)
		return;

	//SendMessageW(pData->hWnd, HVM_SETEXTENDEDSTYLE, 0, HVS_READONLY);

	int size = 0;
	LPBYTE pBin = GetAryElementInf_HexView(pArgInf[1].m_pBin, &size);
	pData->size = size;

	if (!pData->bOwnerData)
	{
		std::vector<BYTE>& data = *pData->data;
		std::vector<bool>& modi = *pData->modi;

		data.clear();
		modi.clear();

		if (size > 0)
		{
			data.resize(size);
			modi.assign(size, 0);
			memcpy(&data[0], pBin, size);
		}
	}
	SendMessageW(pData->hWnd, HVM_SETITEMCOUNT, 1, (LPARAM)size);
	//InvalidateRect(hHexView, 0, 0);
}



// �����ݲ���
static ARG_INFO Fn_hexview_setdata_args[] =
{
	{
		/*name*/    "����",
		/*explain*/ "��ʾ������, ���ֽڼ�Ϊ���",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo	Fn_hexview_setdata = { {
		/*ccname*/  "������",
		/*egname*/  "SetData",
		/*explain*/ "������Ҫ��ʾ������",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Fn_hexview_setdata_args,
	} ,ESTLFNAME(fn_hexview_setdata) };