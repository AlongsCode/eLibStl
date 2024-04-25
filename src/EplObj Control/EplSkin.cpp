#include "mfcfiledlg.h"
#include <mbstring.h>
int  __eplinlinestl___() {
	unsigned char* pp;
	auto c = _mbsstr(pp, pp);
	auto c1 = _mbscmp(pp, pp);
	return 0;
}

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:msvcrt.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")
#pragma comment(linker, "/nodefaultlib:libcmtd.lib")
#pragma comment(linker, "/nodefaultlib:msvcrtd.lib")

//#include"fstream"
#include"EplugHelp.h"
#include"EcontrolHelp.h"
#include<string>
#include"etcp\etcpapi.h"
#include"SkinSharp\SkinH.h"
#include "skinres.inl"
//#pragma comment(lib, "SkinSharp\\Detours.lib")
//#pragma comment(lib, "SkinSharp\\SkinH_ST.lib")

//�������ݼ�Ϊȫ��
#define SKINSHARP L"epl_skinsharp"
static INT s_server_cmd[] = { 39 , 40 , 41 , 42 , 43 , 44 ,45 };
static HBITMAP g_hbmp_epl_skinsharp = NULL;
static bool s_bSkinSharp = false;
static bool  g_blInDesignMode = false;
static bool g_mustcreate = false;
static std::vector<unsigned char> pSkindata;

namespace {

	BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
		std::vector<HWND>* windowHandles = reinterpret_cast<std::vector<HWND>*>(lParam);
		windowHandles->push_back(hwnd);
		return TRUE; 
	}

	std::vector<HWND> EnumerateChildWindows(HWND parentWnd) {
		std::vector<HWND> windowHandles;
		EnumChildWindows(parentWnd, EnumChildProc, reinterpret_cast<LPARAM>(&windowHandles));
		return windowHandles;
	}
	std::wstring GetClassStr(HWND hwnd) {
		constexpr DWORD MAX_CLASS_NAME = 256;
		WCHAR className[MAX_CLASS_NAME]{};
		GetClassNameW(hwnd, className, MAX_CLASS_NAME);
		return className;
	}
	BOOL CALLBACK EnumChildProcW(HWND hwnd, LPARAM lParam) {
		constexpr DWORD MAX_CLASS_NAME = 256;
		WCHAR className[MAX_CLASS_NAME]{};
		GetClassNameW(hwnd, className, MAX_CLASS_NAME);
		if (wcscmp(className, L"WTWindow") == 0) {
			std::vector<HWND>* windowHandles = reinterpret_cast<std::vector<HWND>*>(lParam);
			windowHandles->push_back(hwnd);
		}
		return TRUE;
	}
	std::vector<HWND> EnumerateChildWindowsWt(HWND parentWnd) {
		std::vector<HWND> windowHandles;
		EnumChildWindows(parentWnd, EnumChildProcW, reinterpret_cast<LPARAM>(&windowHandles));
		return windowHandles;
	}
	void EnumDetach(HWND parentWnd) {
		const auto a = EnumerateChildWindows(parentWnd);
		const auto c = EnumerateChildWindowsWt(parentWnd);
		for (const auto& ac:a)
		{
			if (GetClassStr(ac) == L"WTWindow")
				continue;
			for (const auto& cc : c)
			{
				if (IsChild(cc, ac)==FALSE)//����ÿؼ������������Դ���
					SkinH_DetachEx(ac);
			}
		}
		SkinH_DetachEx(parentWnd);
	
	}
}
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CREATE:
	{

		s_bSkinSharp = true;
		SkinH_AttachRes((LPBYTE)pSkindata.data(), pSkindata.size(), 0, 0, 0, 0);
		/*���Ϊ���ģʽ,��ֹװ��������ide*/
		if (g_blInDesignMode)
		{
			EnumDetach(elibstl::ideplug::idefunc::get_main_wnd());
		}
		break;
	}
	case WM_DESTROY:
	{

		if (!g_mustcreate)
		{
			SkinH_Detach();
			s_bSkinSharp = false;
		}
		else
		{
			g_mustcreate = false;
		}
		
		break;
	}
#ifndef __E_STATIC_LIB
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		HDC hCDC = CreateCompatibleDC(ps.hdc);
		SelectObject(hCDC, g_hbmp_epl_skinsharp);
		RECT rc;
		GetClientRect(hWnd, &rc);
		FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		FrameRect(ps.hdc, &rc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
		BitBlt(ps.hdc, (rc.right - 24) / 2, (rc.bottom - 24) / 2, 24, 24, hCDC, 0, 0, SRCCOPY);
		DeleteDC(hCDC);
		EndPaint(hWnd, &ps);
		break;
	}
#endif
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
static ATOM g_atom_epl_skinsharpex = NULL;
static void Skinsharp_RegWndClass()
{
#ifndef __E_STATIC_LIB
	g_hbmp_epl_skinsharp = (HBITMAP)LoadImageW(g_elibstl_hModule, MAKEINTRESOURCEW(IDB_SKIN), IMAGE_BITMAP, 0, 0, 0);
#endif

	WNDCLASSW wc = { sizeof(WNDCLASSW) };
	wc.lpszClassName = SKINSHARP;
	wc.hCursor = LoadCursorW(NULL, (PWSTR)IDC_ARROW);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbWndExtra = sizeof(void*);
	g_atom_epl_skinsharpex = RegisterClassW(&wc);
}



//static void server_callback_incline(eServer* pServer) {
//
//	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 1);
//	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
//}
//static void server_callback_get_data(eServer* pServer) {
//
//	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 0);
//	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
//}
//static void server_callback_outcline(eServer* pServer) {
//	EVENT_NOTIFY2 event(pServer->m_dwWinFormID, pServer->m_dwUnitID, 2);
//	elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
//}
namespace {

	HUNIT WINAPI Create_SeverWindow(
		LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ��������������, �ɱ����ڵ�Ԫ��ITF_GET_PROPERTY_DATA�ӿڲ���, ���û��������ΪNULL
		INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ�, ���û����Ϊ0
		DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
		HWND hParentWnd,                    //   �����ھ��
		UINT uID,                           //   �ڸ������е�ID
		HMENU hMenu,                        //   δʹ��
		INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ�
		DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ
		HWND hDesignWnd,                    //   ���blInDesignModeΪ��, ��hDesignWnd�ṩ����ƴ��ڵĴ��ھ��
		BOOL blInDesignMode                 //   ˵���Ƿ�������IDE�����Խ��п��ӻ����, ����ʱΪ��
	)
	{
		if (pAllPropertyData)
		{
			pSkindata = std::vector<unsigned char>(pAllPropertyData, pAllPropertyData + nAllPropertyDataSize);
		}
		else {
			pSkindata = std::vector<unsigned char>(defskin, defskin + skinsize);
		}
		if (!g_atom_epl_skinsharpex)
		{
			Skinsharp_RegWndClass();
		}
		if (s_bSkinSharp == true)
		{
			if (!g_mustcreate)//���������
			{
				put_errmsg(L"���Ѿ����������ع�Ƥ����������!");
				return 0;
			}

		}
		g_blInDesignMode = blInDesignMode;
		if (!blInDesignMode)
			dwStyle &= (~WS_VISIBLE);
		HWND hWnd = CreateWindowExW(
			0,
			SKINSHARP,
			NULL,
			dwStyle | WS_CHILD | WS_CLIPSIBLINGS,
			x,
			y,
			cx,
			cy,
			hParentWnd,
			hMenu,
			NULL,
			NULL
		);
		if (!hWnd)
		{
			return NULL;
		}


		return elibstl::make_cwnd(hWnd);
	}
	BOOL WINAPI NotifyPropertyChanged_ServerApp(HUNIT hUnit, INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pValue, PSTR* ppszTipText)    //Ŀǰ��δʹ��
	{
		HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
		switch (nPropertyIndex)
		{
		case 0://����Ƥ��
			pSkindata = std::vector<unsigned char>(pValue->m_data.m_pData, pValue->m_data.m_pData + pValue->m_data.m_nDataSize);
		}
		return true;//�������´���
	}
	HGLOBAL WINAPI GetAllPropertyData_ServerApp(HUNIT hUnit)
	{
		HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, pSkindata.size());
		if (hGlobal)
		{
			void* pGlobal = GlobalLock(hGlobal);
			if (pGlobal)
			{
				memcpy(pGlobal, pSkindata.data(), pSkindata.size());
				GlobalUnlock(hGlobal);
			}
		}
		return hGlobal;
	}
	BOOL WINAPI GetPropertyData_ServerApp(HUNIT hUnit, INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pValue)
	{
		HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
		switch (nPropertyIndex)
		{
		case 0:
			pValue->m_data.m_nDataSize = pSkindata.size();
			pValue->m_data.m_pData = (LPBYTE)pSkindata.data();
			return FALSE;
		}
		return FALSE;
	}


	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = elibstl::get_hwnd_from_hunit(hUnit);
		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 0:
		{
			
			CFileDlg dlg;
			dlg.m_bFileMustExist = true;
			dlg.m_SelectedFiles = true;
			dlg.m_strDefext = L"she";
			auto path = elibstl::A2W(elibstl::ideplug::idefunc::get_currcet_dir().c_str());
			dlg.m_strDefdir = path;
			delete[] path;
			dlg.m_fileNamae = L"";
			dlg.m_strFilter = L"�ı��ļ���*.she��| *.she";
			dlg.noChangeDir = true;
			dlg.m_bPathMustExist = true;
			dlg.m_title = L"��ѡ��Ƥ���ļ�";
			dlg.Open(elibstl::ideplug::idefunc::get_main_wnd());
			auto s = dlg.GetFullName();
			if (s.empty())
				return FALSE;
			g_mustcreate = true;
			pSkindata.clear();
			*pblModified = TRUE;
			HANDLE hFile = CreateFileW(s.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_ARCHIVE,
				0);
			if (hFile != INVALID_HANDLE_VALUE)
			{

				DWORD dwNumOfByteRead;
				INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
				pSkindata.resize(nLen);
				INT nRet = ReadFile(hFile, pSkindata.data(), nLen, &dwNumOfByteRead, 0);
				CloseHandle(hFile);
			}
			return TRUE;
		}
		break;
		}
		return FALSE;
	}







	static EVENT_INFO2 s_sever_event[] =
	{
		/*000*/ {"���ݵ���", "�յ�����ʱִ��", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
		/*001*/ {"�ͻ�����", "�пͻ�������ʱִ��", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
		/*002*/ {"�ͻ��뿪", "�пͻ��˶Ͽ�ʱִ��", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	};


	static UNIT_PROPERTY s_SkinSharp[] =
	{
		// FIXED_WIN_UNIT_PROPERTY,    // ������ϴ˺�, ����ֱ��չ��, �����չ��
		//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

		/*000*/ {"���", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
		/*001*/ {"����", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
		/*002*/ {"���", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
		/*003*/ {"�߶�", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
		/*004*/ {"���", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
		/*005*/ {"����", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
		/*006*/ {"��ֹ", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
		/*007*/ {"���ָ��", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},
		/*000*/ {"Ƥ��", "", "�������Ƥ��", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	};
}


extern "C" PFN_INTERFACE WINAPI libstl_GetInterface_SkinSharp(INT nInterfaceNO)
{


	
	return nInterfaceNO == ITF_CREATE_UNIT ? (PFN_INTERFACE)Create_SeverWindow :
		nInterfaceNO == ITF_NOTIFY_PROPERTY_CHANGED ? (PFN_INTERFACE)NotifyPropertyChanged_ServerApp :
		nInterfaceNO == ITF_GET_ALL_PROPERTY_DATA ? (PFN_INTERFACE)GetAllPropertyData_ServerApp :
		nInterfaceNO == ITF_GET_PROPERTY_DATA ? (PFN_INTERFACE)GetPropertyData_ServerApp :
		nInterfaceNO == ITF_DLG_INIT_CUSTOMIZE_DATA ? (PFN_INTERFACE)EInputW :

		NULL;
}

namespace elibstl {
	LIB_DATA_TYPE_INFO Obj_SkinSharp = {
		/*m_szName*/			"SkinSharpƤ��",
		/*m_szEgName*/			"SkinSharp",
		/*m_szExplain*/			"ansi�汾��Ƥ��������,��unicode��ͻ,Ŀǰunicode�汾��֧�־�̬����",
		/*m_nCmdCount*/			0,
		/*m_pnCmdsIndex*/		0,
		/*m_dwState*/			_DT_OS(__OS_WIN) | LDT_WIN_UNIT | LDT_IS_FUNCTION_PROVIDER ,
		/*m_dwUnitBmpID*/		IDB_SKIN,
		/*m_nEventCount*/		0,
		/*m_pEventBegin*/		0,
		/*m_nPropertyCount*/	sizeof(s_SkinSharp) / sizeof(s_SkinSharp[0]),
		/*m_pPropertyBegin*/	s_SkinSharp,
		/*m_pfnGetInterface*/	 libstl_GetInterface_SkinSharp,
		/*m_nElementCount*/		0,
		/*m_pElementBegin*/		NULL,
	};
}






