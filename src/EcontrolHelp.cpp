#include "EcontrolHelp.h"
#pragma comment(lib, "comctl32.lib")


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

static BOOL CALLBACK MyInputBoxDlgProcW(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
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
				wchar_t* Editstr = new wchar_t[nLen + 1] { 0 };
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
			wchar_t* Editstr = new wchar_t[nLen + 1] { 0 };
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
	if (!cchSrc)
		cchSrc = strlen(pszSrc);
	pszDst = new CHAR[cchSrc + 1];
	strncpy(pszDst, pszSrc, cchSrc);
	*(pszDst + cchSrc) = '\0';
	return cchSrc;
}
ESTL_NAMESPACE_END