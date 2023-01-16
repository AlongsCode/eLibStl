#include"EcontrolHelp.h"
#include <CommCtrl.h>
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")


vector<unsigned char> GetDataFromHBIT(HBITMAP hBitmap)
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
	vector<unsigned char> head((unsigned char*)&bmfhdr, (unsigned char*)&bmfhdr + sizeof(BITMAPFILEHEADER));
	vector<unsigned char> body((unsigned char*)lpbi, (unsigned char*)lpbi + dwdibsize);

	//清除 
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	std::vector<unsigned char> result;
	result.reserve(head.size() + body.size());
	result.insert(result.end(), head.begin(), head.end());
	result.insert(result.end(), body.begin(), body.end());
	return result;
}




PCONTROL_STRUCT_BASE DefControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LPCWSTR propName, WNDPROC& oldProc)
{
	// 如果是自己存放数据的话, 这里改成获取自己的数据
	PCONTROL_STRUCT_BASE pBase = (PCONTROL_STRUCT_BASE)GetPropW(hWnd, propName);
	if (!pBase) return 0;
	oldProc = pBase->oldProc;
	switch (message)
	{
	case WM_STYLECHANGED:
	{
		// 记录窗口的样式
		LPSTYLESTRUCT ss = (LPSTYLESTRUCT)lParam;
		if (wParam == GWL_STYLE)
			pBase->style = ss->styleNew;
		else
			pBase->styleEx = ss->styleNew;
		break;
	}
	case WM_DESTROY:
	{
		// 如果是自己存放数据的话, 这里改成删除自己的数据
		RemovePropW(hWnd, propName);
		// 取消子类化, 不取消的话关闭窗口会崩溃
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)pBase->oldProc);
		delete pBase;
		pBase = 0;
		break;
	}
	// 这里可以处理更多通用的消息, 比如 WM_WINDOWPOSCHANGED 把窗口位置记录起来
	// 有或者 WM_SETFOCUS/WM_KILLFOCUS, 把窗口是否有焦点记录起来
	// 更多的通用消息自行扩展
	default:
		break;
	}
	return pBase;
}




static BOOL CALLBACK MyInputBoxDlgProcW(HWND hwndDlg,  // handle to dialog box 
	UINT uMsg,     // message 
	WPARAM wParam, // first message parameter 
	LPARAM lParam  // second message parameter 
)
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
				wstring* result = (wstring*)::GetWindowLongPtrW(hwndDlg, GWLP_USERDATA);
				*result = wstring(Editstr);
				delete[]Editstr;
			}
			DestroyWindow(hwndDlg);
		}
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
void EnableNewCommonControls()
{
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);
}
wstring MyInputBox(wstring  title)
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
	0x02,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,0xD6,0x53,0x88,0x6D,0x00,0x00,0x00,0x00
	}
	;
	wstring result;
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
