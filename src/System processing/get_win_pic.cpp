#define NOMINMAX 
#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"

namespace {
	HBITMAP sCatchBitmap(HWND hWnd, HDC hDCSrc, const SIZE sizeSrc, INT cx, INT cy)
	{
		if (hDCSrc == nullptr)
			return nullptr;

		cx = (cx == 0 ? sizeSrc.cx : cx < 0 ? MulDiv(sizeSrc.cx, std::max(10, -cx), 100) : cx);
		cy = (cy == 0 ? sizeSrc.cy : cy < 0 ? MulDiv(sizeSrc.cy, std::max(10, -cy), 100) : cy);

		if (cx <= 0 || cy <= 0)
		{
			::ReleaseDC(hWnd, hDCSrc);
			return nullptr;
		}

		const auto hBitmap = ::CreateCompatibleBitmap(hDCSrc, cx, cy);

		const auto hDCDest = CreateCompatibleDC(hDCSrc);
		const auto hOldBitmapDest = static_cast<HBITMAP>(::SelectObject(hDCDest, hBitmap));

		auto StretchMode = COLORONCOLOR;
		DEVMODE dm{};
		if (EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &dm))
		{
			if (dm.dmBitsPerPel > 16)
				StretchMode = HALFTONE;
		}
		::SetStretchBltMode(hDCDest, StretchMode);
		::StretchBlt(hDCDest, 0, 0, cx, cy, hDCSrc, 0, 0, sizeSrc.cx, sizeSrc.cy, SRCCOPY);

		::SelectObject(hDCDest, hOldBitmapDest);
		::DeleteDC(hDCDest);

		::ReleaseDC(hWnd, hDCSrc);
		return hBitmap;
	}
	HANDLE sDDBToDIB(HBITMAP hBitmap, DWORD dwCompression, HPALETTE hPal)
	{
		// The function has no arg for bitfields
		if (hBitmap == NULL || dwCompression == BI_BITFIELDS)
			return NULL;

		// Get bitmap information
		BITMAP bm;
		if (::GetObject(hBitmap, sizeof(bm), &bm) == 0)
			return NULL;

		// If a palette has not been supplied use defaul palette
		if (hPal == NULL)
			hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
		constexpr int BitsPerPixel = 24;
		// Initialize the bitmapinfoheader
		BITMAPINFOHEADER bi;
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bm.bmWidth;
		bi.biHeight = bm.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = BitsPerPixel;
		bi.biCompression = dwCompression;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		// Compute the size of the infoheader and the color table
		int nColors = 0 /*(1 << bi.biBitCount)*/;
		// if (nColors > 256)
		//     nColors = 0;
		DWORD dwLen = bi.biSize + nColors * sizeof(RGBQUAD);

		// We need a device context to get the DIB from
		const HDC hDC = ::GetDC(NULL);
		hPal = SelectPalette(hDC, hPal, FALSE);
		RealizePalette(hDC);

		// Allocate enough memory to hold bitmapinfoheader and color table
		HANDLE hDIB = GlobalAlloc(GMEM_MOVEABLE, dwLen);
		if (hDIB == NULL)
		{
			SelectPalette(hDC, hPal, FALSE);
			::ReleaseDC(NULL, hDC);
			return NULL;
		}

		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
		*lpbi = bi;

		// Call GetDIBits with a NULL lpBits param, so the device driver
		// will calculate the biSizeImage field
		GetDIBits(hDC, hBitmap, 0, (DWORD)bi.biHeight, NULL, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
		bi = *lpbi;

		// If the driver did not fill in the biSizeImage field, then compute it
		// Each scan line of the image is aligned on a DWORD (32bit) boundary
		if (bi.biSizeImage == 0)
		{
			bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;

			// If a compression scheme is used the result may infact be larger
			// Increase the size to account for this.
			if (dwCompression != BI_RGB)
				bi.biSizeImage = (bi.biSizeImage * 3) / 2;
		}

		GlobalUnlock(hDIB);

		// Realloc the buffer so that it can hold all the bits
		dwLen += bi.biSizeImage;
		HANDLE handle;
		if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		{
			hDIB = handle;
		}
		else
		{
			GlobalFree(hDIB);

			SelectPalette(hDC, hPal, FALSE);  // Reselect the original palette
			::ReleaseDC(NULL, hDC);
			return NULL;
		}

		// Get the bitmap bits
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

		// FINALLY get the DIB
		const BOOL blpGotBits = GetDIBits(hDC, hBitmap, 0, (DWORD)bi.biHeight,
			(LPBYTE)lpbi + (bi.biSize + nColors * sizeof(RGBQUAD)), (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

		SelectPalette(hDC, hPal, FALSE);
		::ReleaseDC(NULL, hDC);
		GlobalUnlock(hDIB);

		if (blpGotBits == FALSE)
		{
			GlobalFree(hDIB);
			return NULL;
		}

		return hDIB;
	}
	auto sWriteDIB(HANDLE hDIB)
	{
		std::vector<std::byte> mem;
		if (hDIB != NULL)
		{
			LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
			int nColors = 1 << lpbi->biBitCount;
			if (nColors > 256)
				nColors = 0;
			BITMAPFILEHEADER hdr;
			hdr.bfType = ((WORD)('M' << 8) | 'B');
			hdr.bfSize = (DWORD)(GlobalSize(hDIB) + sizeof(hdr));
			hdr.bfReserved1 = 0;
			hdr.bfReserved2 = 0;
			hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));
			auto m = reinterpret_cast<std::byte*>(&hdr);
			mem.insert(mem.end(), m, m + sizeof(hdr));
			m = reinterpret_cast<std::byte*>(lpbi);
			mem.insert(mem.end(), m, m + GlobalSize(hDIB));
			GlobalUnlock(hDIB);
			return mem;
		}

		return mem;
	}
	auto WriteBitmap(HBITMAP hBitmap) -> std::vector<std::byte>

	{
		std::vector<std::byte> mem;

		if (hBitmap == NULL)
			return mem;

		BITMAP bm{};
		if (::GetObjectW(hBitmap, sizeof(bm), &bm) == 0)
			return mem;

		SIZE size{
			bm.bmWidth ,
			 bm.bmHeight };


		if (size.cx <= 0 || size.cy <= 0)
			return mem;

		const HDC hDC = ::GetDC(NULL);

		// 如果设备支持调色板，创建调色板
		HPALETTE hPal;
		if ((::GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE) != 0)
		{
			LOGPALETTE* pLP = (LOGPALETTE*)new BYTE[sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256];
			pLP->palVersion = 0x300;
			pLP->palNumEntries = GetSystemPaletteEntries(hDC, 0, 255, pLP->palPalEntry);
			hPal = ::CreatePalette(pLP);  // Create the palette
			delete[] pLP;
		}
		else
			hPal = NULL;

		HANDLE hDIB;
		if (size.cx != bm.bmWidth || size.cy != bm.bmHeight)
		{
			const HDC hDCSrc = ::CreateCompatibleDC(hDC);
			const HBITMAP hOldBitmapSrc = (HBITMAP)::SelectObject(hDCSrc, hBitmap);

			const HBITMAP hNewBitmap = ::CreateCompatibleBitmap(hDC, size.cx, size.cy);

			const HDC hDCDest = CreateCompatibleDC(hDC);
			const HBITMAP hOldBitmapDest = (HBITMAP)::SelectObject(hDCDest, hNewBitmap);

			auto StretchMode = COLORONCOLOR;
			DEVMODE dm{};
			if (EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &dm))
			{
				if (dm.dmBitsPerPel > 16)
					StretchMode = HALFTONE;
			}
			::SetStretchBltMode(hDCDest, StretchMode);
			::StretchBlt(hDCDest, 0, 0, size.cx, size.cy, hDCSrc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			::SelectObject(hDCSrc, hOldBitmapSrc);
			::SelectObject(hDCDest, hOldBitmapDest);
			::DeleteDC(hDCSrc);
			::DeleteDC(hDCDest);

			hDIB = sDDBToDIB(hNewBitmap, BI_RGB, hPal);
			::DeleteObject(hNewBitmap);
		}
		else
		{
			hDIB = sDDBToDIB(hBitmap, BI_RGB, hPal);
		}

		if (hDIB != NULL)
		{
			mem = sWriteDIB(hDIB);
			GlobalFree(hDIB);  // Free the memory allocated by sDDBToDIB for the DIB
		}

		if (hPal != NULL)
			::DeleteObject(hPal);
		::ReleaseDC(NULL, hDC);

		return mem;
	}
	auto CatchWindowBitmap(HWND hWnd, INT cx, INT cy)
	{
		if (hWnd == nullptr)
			return WriteBitmap(sCatchBitmap(nullptr, ::GetDC(nullptr), { GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN) }, cx, cy));
		RECT rect{};
		::GetWindowRect(hWnd, &rect);
		return WriteBitmap(sCatchBitmap(hWnd, ::GetWindowDC(hWnd), { rect.right - rect.left, rect.bottom - rect.top }, cx, cy));
	}


};



static ARG_INFO Args[] 
{
		{
		/*name*/	"窗口句柄",
		/*explain*/	"提供欲捕获其显示内容的窗口句柄,如果为0则为捕获屏幕显示内容.",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
		},
		{
		/*name*/	"输出宽度",
		/*explain*/	R"(指定图片的输出宽度. 如果小于0,参数值指定的是最终图片输出宽度相对于
所取得图片宽度的百分比(最小为10%); 如果等于0,则按图片原宽度输出; 如
果大于0,指定输出图片的绝对宽度.)",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
		},
		{
		/*name*/	"输出高度",
		/*explain*/	R"(指定图片的输出高度. 如果小于0,参数值指定的是最终图片输出高度相对于
所取得图片高度的百分比(最小为10%); 如果等于0,则按图片原高度输出; 如
果大于0,指定输出图片的绝对高度.)",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
		}
};





EXTERN_C void fn_get_win_pic(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p=CatchWindowBitmap(reinterpret_cast<HWND>( pArgInf[0].m_int), pArgInf[1].m_int, pArgInf[2].m_int);
	pRetData->m_pBin = elibstl::clone_bin(reinterpret_cast<unsigned char*>(p.data()), p.size());
}


FucInfo Fn_get_win_pic = { {
		/*ccname*/  ("截图"),
		/*egname*/  ("get_win_pic"),
		/*explain*/ ("同易语言快照,修复一些情况下截图问题"),
		/*category*/6,
		/*state*/    NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Args),
		/*arg lp*/  Args,
	} ,ESTLFNAME(fn_get_win_pic) };