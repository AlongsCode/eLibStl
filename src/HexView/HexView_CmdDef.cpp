#include "HexView_Control.h"
#include "../../include/ElibHelp.h"

#define HEXVIEW_ESTLFNAME(_n) HEXVIEW_NAMESPACE::_n, #_n

using namespace HEXVIEW_NAMESPACE;
//HEXVIEW_NAMESPACE_BEGIN

// 返回数组的数据部分首地址及成员数目。 返回的地址不需要额外释放
inline LPBYTE GetAryElementInf_HexView(void* pAryData, LPINT pnElementCount)
{
	if ( pnElementCount )*pnElementCount = 0;
	if ( !pAryData )return 0;
	LPINT pnData = (LPINT)pAryData;
	INT nArys = *pnData++;  // 取得维数。
	// 计算成员数目。
	INT nElementCount = 1;
	while ( nArys > 0 )
	{
		nElementCount *= *pnData++;
		nArys--;
	}

	if ( pnElementCount )
		*pnElementCount = nElementCount;
	return (LPBYTE)pnData;
}
//HEXVIEW_NAMESPACE_END

// 设置数据, 一个字节集参数
EXTERN_C void fn_hexview_setdata(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hHexView = elibstl::get_hwnd_from_arg(pArgInf);
	if ( !hHexView )
		return;
	PHEXVIEW_PROPERTY pData = (PHEXVIEW_PROPERTY)GetWindowLongPtrW(hHexView, 0);
	if ( !pData )
		return;

	//SendMessageW(pData->hWnd, HVM_SETEXTENDEDSTYLE, 0, HVS_READONLY);

	int size = 0;
	LPBYTE pBin = GetAryElementInf_HexView(pArgInf[1].m_pBin, &size);
	std::vector<BYTE>& data = *pData->data;
	std::vector<BYTE>& modi = *pData->modi;

	data.clear();
	modi.clear();

	if ( size > 0 )
	{
		data.resize(size);
		modi.assign(size, 0);
		memcpy(&data[0], pBin, size);
	}
	SendMessageW(pData->hWnd, HVM_SETITEMCOUNT, 1, (LPARAM)size);
	//InvalidateRect(hHexView, 0, 0);
}



// 置数据参数
static ARG_INFO Fn_hexview_setdata_args[] =
{
	{
		/*name*/    "数据",
		/*explain*/ "显示的数据, 空字节集为清除",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo	Fn_hexview_setdata = { {
		/*ccname*/  "置数据",
		/*egname*/  "SetData",
		/*explain*/ "设置需要显示的数据",
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