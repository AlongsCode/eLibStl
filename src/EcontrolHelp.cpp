#include "EcontrolHelp.h"
#pragma comment(lib, "comctl32.lib")

#define WCN_INTPUTBOX L"eLibStl.WndClass.InputBox"

#define IDC_ED_INPUT	101
#define IDC_BT_READIN	201
#define IDC_BT_OK		202
#define IDC_BT_CANCEL	203

#define DEF_SIZE(height,width) static INT WINAPI DefSize(INT nMsg, DWORD dwParam1, DWORD dwParam2){switch (nMsg){case NU_GET_CREATE_SIZE_IN_DESIGNER:{*((intptr_t*)dwParam1) = height;*((intptr_t*)dwParam2) = width;}return TRUE;}return FALSE;}



//有写地方需要使用到，所以先定义
HMODULE g_elibstl_hModule = NULL;

ESTL_NAMESPACE_BEGIN
std::vector<unsigned char> GetDataFromHBIT(HBITMAP hBitmap)
{
	HDC hdc;			//设备描述表
	int ibits;
	WORD wbitcount;     //当前显示分辨率下每个像素所占字节数

	//位图中每个像素所占字节数，定义调色板大小，位图中像素字节大小，位图文件大小 ，写入文件字节数
	DWORD dwpalettesize = 0, dwbmbitssize, dwdibsize;

	BITMAP bitmap;				//位图属性结构
	BITMAPFILEHEADER bmfhdr;	//位图文件头结构
	BITMAPINFOHEADER bi;		//位图信息头结构
	LPBITMAPINFOHEADER lpbi;	//指向位图信息头结构

	//定义文件，分配内存句柄，调色板句柄
	HANDLE hdib, hpal, holdpal = NULL;

	//计算位图文件每个像素所占字节数
	hdc = CreateDCW(L"display", NULL, NULL, NULL);
	ibits = GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES);
	DeleteDC(hdc);

	if (ibits <= 1)
		wbitcount = 1;
	else if (ibits <= 4)
		wbitcount = 4;
	else if (ibits <= 8)
		wbitcount = 8;
	else if (ibits <= 16)
		wbitcount = 16;
	else if (ibits <= 24)
		wbitcount = 24;
	else
		wbitcount = 32;

	//计算调色板大小
	if (wbitcount <= 8)
		dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//设置位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wbitcount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwbmbitssize = ((bitmap.bmWidth * wbitcount + 31) / 32) * 4 * bitmap.bmHeight;
	//为位图内容分配内存
	hdib = GlobalAlloc(GHND, dwbmbitssize + dwpalettesize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
	*lpbi = bi;

	// 处理调色板 
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
		RealizePalette(hdc);
	}

	// 获取该调色板下新的像素值
	GetDIBits(hdc, hBitmap, 0, (UINT)bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwpalettesize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	//恢复调色板 
	if (holdpal)
	{
		SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
		::ReleaseDC(NULL, hdc);
	}

	// 设置位图文件头
	bmfhdr.bfType = 0x4d42; // "bm"
	dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		dwpalettesize + dwbmbitssize;
	bmfhdr.bfSize = dwdibsize;
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		(DWORD)sizeof(BITMAPINFOHEADER) + dwpalettesize;
	std::vector<unsigned char> head((unsigned char*)&bmfhdr, (unsigned char*)&bmfhdr + sizeof(BITMAPFILEHEADER));
	std::vector<unsigned char> body((unsigned char*)lpbi, (unsigned char*)lpbi + dwdibsize);

	//清除 
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	std::vector<unsigned char> result;
	result.reserve(head.size() + body.size());
	result.insert(result.end(), head.begin(), head.end());
	result.insert(result.end(), body.begin(), body.end());
	return result;
}

HFONT EzFont(PCWSTR pszFontName, int iPoint, int iWeight, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
{
	HDC hDC = GetDC(NULL);
	int iSize;
	iSize = -MulDiv(iPoint, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	ReleaseDC(NULL, hDC);
	return CreateFontW(iSize, 0, 0, 0, iWeight, bItalic, bUnderline, bStrikeOut, 0, 0, 0, 0, 0, pszFontName);
}

struct ESTLPRIV_INPUTBOXCTX
{
	PCWSTR pszInitContent;
	PWSTR* ppszInput;
	HFONT hFont;
	BOOL bOK;
};
static ATOM s_atomInputBox = 0;
static BOOL CALLBACK MyInputBoxDlgProcW(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndEDIT = GetDlgItem(hwndDlg, 1001);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		::SetWindowTextW(hwndDlg, L"请输入所需文本:");
		::SetWindowLongPtrW(hwndDlg, GWLP_USERDATA, 0);
		::SetWindowTextW(hwndEDIT, (LPCWSTR)lParam);
	}

	break;
	case WM_COMMAND:
	{
		INT nID = wParam & 0xffff;
		if (nID == IDCANCEL)
			DestroyWindow(hwndDlg);
		else if (nID == IDOK) {


			size_t nLen = ::GetWindowTextLengthW(hwndEDIT);
			if (nLen > 0)
			{
				wchar_t* Editstr = new wchar_t[nLen + 1]{ 0 };
				GetWindowTextW(hwndEDIT, Editstr, nLen + 1);
				std::wstring* result = (std::wstring*)::GetWindowLongPtrW(hwndDlg, GWLP_USERDATA);
				*result = std::wstring(Editstr);
				delete[]Editstr;
			}
			DestroyWindow(hwndDlg);
		}
	}
	break;
	case WM_CLOSE: {
		size_t nLen = ::GetWindowTextLengthW(hwndEDIT);
		if (nLen > 0)
		{
			wchar_t* Editstr = new wchar_t[nLen + 1]{ 0 };
			GetWindowTextW(hwndEDIT, Editstr, nLen + 1);
			std::wstring* result = (std::wstring*)::GetWindowLongPtrW(hwndDlg, GWLP_USERDATA);
			*result = std::wstring(Editstr);
			delete[]Editstr;
		}
		DestroyWindow(hwndDlg);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
static LRESULT CALLBACK WndProc_InputBox(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int cyBtn = 36, cxBtn1 = 110, cxBtn2 = 90, sizePadding = 10;
	switch (uMsg)
	{
	case WM_SIZE:
	{
		int cxClient = LOWORD(lParam), cyClient = HIWORD(lParam);
		SetWindowPos(GetDlgItem(hWnd, IDC_ED_INPUT), NULL, 0, 0,
			cxClient - sizePadding * 2,
			cyClient - cyBtn - sizePadding * 3,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		int yBtn = cyClient - cyBtn - sizePadding;
		SetWindowPos(GetDlgItem(hWnd, IDC_BT_READIN), NULL,
			sizePadding,
			yBtn,
			0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

		SetWindowPos(GetDlgItem(hWnd, IDC_BT_OK), NULL,
			cxClient - cxBtn2 * 2 - sizePadding * 2,
			yBtn,
			0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

		SetWindowPos(GetDlgItem(hWnd, IDC_BT_CANCEL), NULL,
			cxClient - cxBtn2 - sizePadding,
			yBtn,
			0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	return 0;

	case WM_COMMAND:
	{
		if (HIWORD(wParam) != BN_CLICKED)
			break;
		if (!lParam)
			break;
		switch (LOWORD(wParam))
		{
		case IDC_BT_READIN:
		{
			WCHAR szPath[MAX_PATH]{};
			OPENFILENAMEW ofn{};
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szPath;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (!GetOpenFileNameW(&ofn))
				return 0;
			HANDLE hFile = CreateFileW(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				wsprintfW(szPath, L"打开文件失败！\n错误码：0x%08X", GetLastError());
				MessageBoxW(hWnd, szPath, L"错误", MB_ICONERROR);
				return 0;
			}

			ULONGLONG ullSize;
			GetFileSizeEx(hFile, (LARGE_INTEGER*)&ullSize);
			if (ullSize >> 32)
			{
				MessageBoxW(hWnd, L"文件过大！", L"错误", MB_ICONERROR);
				CloseHandle(hFile);
				return 0;
			}
			DWORD dwSize = (DWORD)ullSize;
			if (!dwSize)
			{
				CloseHandle(hFile);
				return 0;
			}

			PWSTR p;
			ULONG uExceptionCode;
			__try
			{
				p = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, dwSize + sizeof(WCHAR));
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				uExceptionCode = GetExceptionCode();
				CloseHandle(hFile);
				wsprintfW(szPath, L"分配%u字节内存失败！\n异常代码：0x%08X", dwSize + sizeof(WCHAR), uExceptionCode);
				MessageBoxW(hWnd, szPath, L"错误", MB_ICONERROR);
				return 0;
			}
			assert(p);// 消掉下面那个警告
			DWORD dwRead;
			ReadFile(hFile, p, dwSize, &dwRead, NULL);
			CloseHandle(hFile);
			*(p + dwSize / sizeof(WCHAR)) = L'\0';
			SetWindowTextW(GetDlgItem(hWnd, IDC_ED_INPUT), p);
			HeapFree(GetProcessHeap(), 0, p);
		}
		return 0;

		case IDC_BT_OK:
		{
			auto p = (ESTLPRIV_INPUTBOXCTX*)GetWindowLongPtrW(hWnd, 0);
			p->bOK = TRUE;
			HWND hED = GetDlgItem(hWnd, IDC_ED_INPUT);
			int cch = GetWindowTextLengthW(hED);
			if (cch)
			{
				PWSTR psz = new WCHAR[cch + 1];
				GetWindowTextW(hED, psz, cch + 1);
				*(p->ppszInput) = psz;
			}
			else
				*(p->ppszInput) = NULL;

			DestroyWindow(hWnd);
		}
		return 0;

		case IDC_BT_CANCEL:
		{
			auto p = (ESTLPRIV_INPUTBOXCTX*)GetWindowLongPtrW(hWnd, 0);
			p->bOK = FALSE;
			*(p->ppszInput) = NULL;
			DestroyWindow(hWnd);
		}
		return 0;
		}
	}
	break;

	case WM_CLOSE:
	{
		auto p = (ESTLPRIV_INPUTBOXCTX*)GetWindowLongPtrW(hWnd, 0);
		p->bOK = FALSE;
		*(p->ppszInput) = NULL;
		DestroyWindow(hWnd);
	}
	return 0;

	case WM_CREATE:
	{
		auto p = (ESTLPRIV_INPUTBOXCTX*)((CREATESTRUCTW*)lParam)->lpCreateParams;
		SetWindowLongPtrW(hWnd, 0, (LONG_PTR)p);
		p->hFont = EzFont(L"微软雅黑", 10);
		SendMessageW(hWnd, WM_SETFONT, (WPARAM)p->hFont, FALSE);
		HWND hCtrl;
		hCtrl = CreateWindowExW(WS_EX_CLIENTEDGE, WC_EDITW, p->pszInitContent, WS_CHILD | WS_VISIBLE | ES_MULTILINE,
			sizePadding, sizePadding, 0, 0, hWnd, (HMENU)IDC_ED_INPUT, g_elibstl_hModule, NULL);
		ShowScrollBar(hCtrl, SB_VERT, TRUE);
		SendMessageW(hCtrl, WM_SETFONT, (WPARAM)p->hFont, FALSE);
		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"导入文本(&I)", WS_CHILD | WS_VISIBLE,
			0, 0, cxBtn1, cyBtn, hWnd, (HMENU)IDC_BT_READIN, g_elibstl_hModule, NULL);
		SendMessageW(hCtrl, WM_SETFONT, (WPARAM)p->hFont, FALSE);
		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"确定(&O)", WS_CHILD | WS_VISIBLE,
			0, 0, cxBtn2, cyBtn, hWnd, (HMENU)IDC_BT_OK, g_elibstl_hModule, NULL);
		SendMessageW(hCtrl, WM_SETFONT, (WPARAM)p->hFont, FALSE);
		hCtrl = CreateWindowExW(0, WC_BUTTONW, L"取消(&C)", WS_CHILD | WS_VISIBLE,
			0, 0, cxBtn2, cyBtn, hWnd, (HMENU)IDC_BT_CANCEL, g_elibstl_hModule, NULL);
		SendMessageW(hCtrl, WM_SETFONT, (WPARAM)p->hFont, FALSE);
	}
	return 0;

	case WM_DESTROY:
	{
		auto p = (ESTLPRIV_INPUTBOXCTX*)GetWindowLongPtrW(hWnd, 0);
		DeleteObject(p->hFont);
		PostQuitMessage(0);
	}
	return 0;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

BOOL IntputBox(PWSTR* ppszInput, PCWSTR pszInitContent, PCWSTR pszCaption)
{
	if (!s_atomInputBox)
	{
		WNDCLASSW wc{};
		wc.lpszClassName = WCN_INTPUTBOX;
		wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wc.hIcon = LoadIconW(NULL, IDI_APPLICATION);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hInstance = g_elibstl_hModule;
		wc.lpfnWndProc = WndProc_InputBox;
		wc.cbWndExtra = sizeof(void*);
		s_atomInputBox = RegisterClassW(&wc);
	}

	auto pCtx = new ESTLPRIV_INPUTBOXCTX;
	ZeroMemory(pCtx, sizeof(ESTLPRIV_INPUTBOXCTX));
	pCtx->pszInitContent = pszInitContent;
	pCtx->ppszInput = ppszInput;

	const int cxInit = 560, cyInit = 500;
	HWND hWnd = CreateWindowExW(0, MAKEINTATOMW(s_atomInputBox), pszCaption, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, SW_SHOW, cxInit, cyInit, NULL, NULL, g_elibstl_hModule, pCtx);
	assert(hWnd);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	BOOL bOK = pCtx->bOK;
	delete pCtx;
	return bOK;
}

std::wstring MyInputBox(const std::wstring& title)
{
	//对话框二进制模板，方便脱离MFC
	const  BYTE MyInputBoxDialogTemplateData[] = {
	0x01,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x08,0xC8,0x80,
	0x03,0x00,0x00,0x00,0x00,0x00,0x5F,0x01,0xE2,0x00,0x00,0x00,0x00,0x00,0xF7,0x8B,
	0x93,0x8F,0x65,0x51,0x1A,0xFF,0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x8B,0x5B,
	0x53,0x4F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x84,0x00,0x81,0x50,
	0x05,0x00,0x03,0x00,0x53,0x01,0xC0,0x00,0xE9,0x03,0x00,0x00,0xFF,0xFF,0x81,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x50,
	0x63,0x00,0xC7,0x00,0x37,0x00,0x13,0x00,0x01,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,
	0x6E,0x78,0xA4,0x8B,0x93,0x8F,0x65,0x51,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x50,0xBB,0x00,0xC7,0x00,0x37,0x00,0x13,0x00,
	0x02,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,0x05,0x6E,0x7A,0x7A,0x00,0x00,0x00,0x00
	};
	std::wstring result;
	HWND hDlg = CreateDialogIndirectParamW(::GetModuleHandleW(NULL), (LPCDLGTEMPLATE)MyInputBoxDialogTemplateData, 0, (DLGPROC)MyInputBoxDlgProcW, (LPARAM)title.c_str());
	::SetWindowLongPtrW(hDlg, GWLP_USERDATA, (LONG_PTR)&result);
	//result = temp;
	if (hDlg) {
		ShowWindow(hDlg, SW_SHOW);
		UpdateWindow(hDlg);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return result;
}

int DupStringForNewDeleteW(PWSTR& pszDst, PCWSTR pszSrc, int cchSrc)
{
	delete[] pszDst;
	if (!pszSrc)
	{
		pszDst = NULL;
		return 0;
	}
	if (!cchSrc)
		cchSrc = wcslen(pszSrc);
	pszDst = new WCHAR[cchSrc + 1];
	wcsncpy(pszDst, pszSrc, cchSrc);
	*(pszDst + cchSrc) = L'\0';
	return cchSrc;
}

int DupStringForNewDeleteA(PSTR& pszDst, PCSTR pszSrc, int cchSrc)
{
	delete[] pszDst;
	if (!pszSrc)
	{
		pszDst = NULL;
		return 0;
	}
	if (!cchSrc)
		cchSrc = strlen(pszSrc);
	pszDst = new CHAR[cchSrc + 1];
	strncpy(pszDst, pszSrc, cchSrc);
	*(pszDst + cchSrc) = '\0';
	return cchSrc;
}

void SetFrameType(HWND hWnd, int iFrame)
{
	DWORD dwStyle = GetWindowLongPtrW(hWnd, GWL_STYLE) & (~WS_BORDER);
	DWORD dwExStyle = GetWindowLongPtrW(hWnd, GWL_EXSTYLE)
		& (~(WS_EX_WINDOWEDGE | WS_EX_STATICEDGE | WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE));

	switch (iFrame)
	{
	case 0: break;// 无边框
	case 1: dwExStyle |= WS_EX_CLIENTEDGE; break;// 凹入式
	case 2: dwExStyle |= (WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME); break;// 凸出式
	case 3: dwExStyle |= WS_EX_STATICEDGE; break;// 浅凹入式
	case 4: dwExStyle |= (WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE); break;// 镜框式
	case 5: dwStyle |= WS_BORDER; break;// 单线边框式
	}

	SetWindowLongPtrW(hWnd, GWL_STYLE, dwStyle);
	SetWindowLongPtrW(hWnd, GWL_EXSTYLE, dwExStyle);
}

int GetFrameType(HWND hWnd)
{
	DWORD dwStyle = GetWindowLongPtrW(hWnd, GWL_STYLE);
	DWORD dwExStyle = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
	if (dwExStyle & WS_EX_DLGMODALFRAME)
	{
		if (dwExStyle & WS_EX_WINDOWEDGE)
			return 2;// 凸出式
		if (dwExStyle & WS_EX_CLIENTEDGE)
			return 4;// 镜框式
	}

	if (dwExStyle & WS_EX_CLIENTEDGE)
		return 1;// 凹入式
	if (dwExStyle & WS_EX_STATICEDGE)
		return 3;// 浅凹入式
	if (dwStyle & WS_BORDER)
		return 5;// 单线边框式

	return 0;// 无边框
}


SIZE_T CCtrlBase::InitBase0(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID)
{
	m_bInDesignMode = bInDesignMode;
	m_dwWinFormID = dwWinFormID;
	m_dwUnitID = dwUnitID;

	if (pAllData)
	{
		memcpy(&m_Info0, pAllData, sizeof(ECTRLINFO));
		BYTE* p = (BYTE*)pAllData + sizeof(ECTRLINFO) + m_Info0.cbPic;

		m_pszTextW = NULL;
		if (m_Info0.cchText)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, (PCWSTR)p, m_Info0.cchText);
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}
		else
			m_pszTextA = NULL;
	}
	else
	{
		m_pszTextW = NULL;
		m_pszTextA = NULL;
	}

	m_pPicData = NULL;
	m_Info0.iVer = DATA_VER_BASE_1;

	if (pAllData)
		return sizeof(ECTRLINFO) + m_Info0.cbPic + m_Info0.cchText * sizeof(WCHAR);
	else
		return 0;
}

void CCtrlBase::InitBase0(PCVOID pAllData)
{
	if (pAllData)
	{
		BYTE* p = (BYTE*)pAllData + sizeof(ECTRLINFO);
		SetPic(p, m_Info0.cbPic);
	}
	else
		m_Info0.Font = elibstl::GetEDefLOGFONT(m_hWnd);

	SetFrame(m_Info0.iFrame);
	SetFont(&m_Info0.Font);
}

void CCtrlBase::SetPic(void* pPic, int cbSize)
{
	m_Info0.cbPic = cbSize;
	if (m_hBitmap)
		DeleteObject(m_hBitmap);

	if (cbSize)
	{
		if (m_bInDesignMode)
		{
			delete[] m_pPicData;
			m_pPicData = new BYTE[cbSize];
			memcpy(m_pPicData, pPic, cbSize);
		}
		m_hBitmap = elibstl::make_hbit((BYTE*)pPic, cbSize);
		SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
	}
	else
	{
		if (m_bInDesignMode)
		{
			delete[] m_pPicData;
			m_pPicData = NULL;
		}
		m_hBitmap = NULL;
		SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, NULL);
	}
}

HGLOBAL CCtrlBase::FlattenInfoBase0(SIZE_T cbExtra, SIZE_T* pcbBaseData)
{
	BYTE* p;
	auto pszText = GetTextW();
	if (pszText)
		m_Info0.cchText = wcslen(pszText);
	else
		m_Info0.cchText = 0;
	int cbText = m_Info0.cchText * sizeof(WCHAR);
	SIZE_T cbMem = sizeof(ECTRLINFO) + m_Info0.cbPic + cbText;
	if (pcbBaseData)
		*pcbBaseData = cbMem;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cbMem + cbExtra);
	if (!hGlobal)
		goto FailAlloc;
	p = (BYTE*)GlobalLock(hGlobal);
	if (!p)
		goto FailLock;
	// 结构
	memcpy(p, &m_Info0, sizeof(ECTRLINFO));
	// 图片
	p += sizeof(ECTRLINFO);
	memcpy(p, m_pPicData, m_Info0.cbPic);
	// 文本
	p += m_Info0.cbPic;
	memcpy(p, pszText, cbText);
	// 
	GlobalUnlock(hGlobal);
	return hGlobal;
FailLock:
	GlobalFree(hGlobal);
FailAlloc:
	return NULL;
}
ESTL_NAMESPACE_END