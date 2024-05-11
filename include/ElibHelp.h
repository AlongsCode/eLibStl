#pragma once
#include"elib/lib2.h"
#include"elib/fnshare.h"
#include<vector>
#include<string>
#include <tuple>
#include"..\resource.h"
#include<assert.h>
#include <CommCtrl.h>
#include"Tace.hpp"
#include <cctype>
#include"Membin.hpp"


#define ESTL_NAMESPACE_BEGIN namespace elibstl {
#define ESTL_NAMESPACE_END }

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#define eStlInline __forceinline
#else
#define eStlInline inline
#endif

#define MAKEINTATOMW(i)  (PWSTR)((ULONG_PTR)((WORD)(i)))
#define va_arg_idx(ap, idx, t) (*(t*)((ap)+_INTSIZEOF(t)*(idx)))
#define BOOLNOT(x) (x) = !(x)

struct FucInfo
{
	CMD_INFO FucDef;
	PFN_EXECUTE_CMD pFuc;
	const char* FucName;
};

struct PlugInfo
{
	void (*Plugfunc)() {nullptr}; /*���ʱ����������*/
	const char* PlugDefStr{ "\0" }; /*�����Ϣ*/
	size_t PlugSizeStr{ sizeof("\0")}; /*����ַ�����С*/
};
#define ESTLFNAME(s) s,#s
#define ESTLARG(s) std::size(s),s

extern HMODULE g_elibstl_hModule;

ESTL_NAMESPACE_BEGIN

typedef LPCVOID PCVOID;
typedef LPCBYTE PCBYTE;
typedef UINT BITBOOL;

template<class... Args>
eStlInline int ArgsNum(Args&&... args)
{
	return sizeof...(args);
}

#define ESTLVAL(...) ArgsNum(__VA_ARGS__), __VA_ARGS__

eStlInline bool isUnicode(const unsigned char* data, size_t length) {
	// ����ֽ����� (BOM)
	if (length >= 2 && data[0] == 0xFF && data[1] == 0xFE) {
		// UTF-16LE �ֽ��򣬵�λ�ֽ���ǰ
		return true;
	}
	else if (length >= 2 && data[0] == 0xFE && data[1] == 0xFF) {
		// UTF-16BE �ֽ��򣬸�λ�ֽ���ǰ
		return true;
	}

	// ����ַ���Ӧ���ֽ�����
	for (size_t i = 0; i < length; i += 2) {
		unsigned char highByte = data[i];
		unsigned char lowByte = data[i + 1];

		if ((highByte >= 0xD8 && highByte <= 0xDB) && (lowByte >= 0xDC && lowByte <= 0xDF)) {
			// �ߴ�����͵ʹ������ֽڣ��Ϸ��� UTF-16 ����
			continue;
		}

		if ((highByte >= 0xD8 && highByte <= 0xDB) || (lowByte >= 0xDC && lowByte <= 0xDF)) {
			// �ߴ������ʹ������ֽڵ������֣��Ƿ��� UTF-16 ����
			return false;
		}
	}

	return true;
}

PLIB_CONST_INFO LibStl_GetConstInfo();
int LibStl_GetConstSize();

/// <summary>
/// Unicode��ANSI��ʹ��Ĭ�ϴ���ҳ
/// </summary>
/// <param name="pszW">Unicode�ַ���ָ��</param>
/// <returns>ANSI�ַ���ָ�룬Ӧʹ��delete[]�ͷ�</returns>
PSTR W2A(PCWSTR pszW);


PSTR W2UTF8(const std::wstring_view& text);

PSTR W2UTF8(const std::wstring_view& text);

/// <summary>
/// ANSI��Unicode��ʹ��Ĭ�ϴ���ҳ
/// </summary>
/// <param name="pszA">ANSI�ַ���ָ��</param>
/// <returns>Unicode�ַ���ָ�룬Ӧʹ��delete[]�ͷ�</returns>
PWSTR A2W(PCSTR pszA);

/// <summary>
/// ����������֧�ֿ⺯��
/// </summary>
bool CallElibFunc(const char* elib_name, const char* def_name, PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);

/// <summary>
/// ����ѡ��
/// ��һ������ָʾ��0��ʼ��������
/// </summary>
template <class T>
eStlInline T MultiSelect(int n, ...)
{
	assert(n >= 0);
	va_list Args;
	va_start(Args, n);
	T Ret = va_arg_idx(Args, n, T);
	va_end(Args);
	return Ret;
}

eStlInline BOOL IsFILETIMEZero(const FILETIME* pft)
{
	// ���ܽ�FILETIME*ת��ΪULONGLONG*����Ϊ�����ж������
	ULARGE_INTEGER ull;
	ull.HighPart = pft->dwHighDateTime;
	ull.LowPart = pft->dwLowDateTime;
	return ull.QuadPart == 0;
}

eStlInline BOOL operator==(const FILETIME& ft1, const FILETIME& ft2)
{
	return CompareFileTime(&ft1, &ft2) == 0;
}
eStlInline BOOL operator>(const FILETIME& ft1, const FILETIME& ft2)
{
	return CompareFileTime(&ft1, &ft2) == 1;
}
eStlInline BOOL operator<(const FILETIME& ft1, const FILETIME& ft2)
{
	return CompareFileTime(&ft1, &ft2) == -1;
}

eStlInline BOOL IsBitExist(DWORD dw1, DWORD dw2)
{
	return ((dw1 & dw2) == dw2);
}

#define SRSAllocW(cch) (PWSTR)HeapAlloc(GetProcessHeap(), 0, cch * sizeof(WCHAR))
#define SRSReAllocW(psz, cch) (PWSTR)HeapReAlloc(GetProcessHeap(), 0, psz, cch * sizeof(WCHAR))
#define SRSFree(psz) HeapFree(GetProcessHeap(), 0, psz)
#define SRSMakeCapacity(cch) (cch * 2)

// ���ַ������ṩ͸������������
class CSimpleRefStrW
{
public:
	PWSTR m_pszText = NULL;
	int m_cchText = 0;
	int m_cchCapacity = 0;

	CSimpleRefStrW() = default;

	CSimpleRefStrW(int cchInit)
	{
		m_cchCapacity = cchInit + 1;
		m_pszText = SRSAllocW(cchInit + 1);
	}

	CSimpleRefStrW(PCWSTR psz, int cchText = -1)
	{
		if (!psz || !cchText)
			return;
		if (cchText < 0)
			cchText = wcslen(psz);
		if (!cchText)
			return;
		m_cchText = cchText;
		m_cchCapacity = SRSMakeCapacity(cchText + 1);
		m_pszText = SRSAllocW(m_cchCapacity);
		if (m_pszText)
			wcscpy(m_pszText, psz);
	}

	CSimpleRefStrW(const CSimpleRefStrW& x)
	{
		m_cchText = x.m_cchText;
		m_cchCapacity = SRSMakeCapacity(m_cchText + 1);
		m_pszText = SRSAllocW(m_cchCapacity);
		if (x.m_pszText)
			wcscpy(m_pszText, x.m_pszText);
	}

	CSimpleRefStrW(CSimpleRefStrW&& x) noexcept
	{
		SRSFree(m_pszText);
		m_cchText = x.m_cchText;
		m_cchCapacity = x.m_cchCapacity;
		m_pszText = x.m_pszText;
		x.m_pszText = NULL;
		x.m_cchText = 0;
		x.m_cchCapacity = 0;
	}

	~CSimpleRefStrW()
	{
		SRSFree(m_pszText);
	}

	CSimpleRefStrW& operator=(PCWSTR pszSrc)
	{
		DupString(pszSrc);
		return *this;
	}

	CSimpleRefStrW& operator=(CSimpleRefStrW& x)
	{
		DupString(x.m_pszText, x.m_cchText);
		return *this;
	}

	CSimpleRefStrW& operator=(CSimpleRefStrW&& x) noexcept
	{
		SRSFree(m_pszText);
		m_cchText = x.m_cchText;
		m_cchCapacity = x.m_cchCapacity;
		m_pszText = x.m_pszText;
		x.m_pszText = NULL;
		x.m_cchText = 0;
		x.m_cchCapacity = 0;
		return *this;
	}

	BOOL operator==(PCWSTR psz)
	{
		if (!m_pszText && !psz)
			return TRUE;
		else if (!m_pszText || !psz)
			return FALSE;
		else
			return wcscmp(m_pszText, psz) == 0;
	}

	operator PWSTR()
	{
		return m_pszText;
	}

	int DupString(PCWSTR pszSrc, int cchSrc = -1);

	PWSTR Attach(PWSTR psz, int cchCapacity, int cchText = -1);

	eStlInline PWSTR Dettach()
	{
		auto pTemp = m_pszText;
		m_cchCapacity = 0;
		m_cchText = 0;
		m_pszText = NULL;
		return pTemp;
	}

	int PushBack(PCWSTR pszSrc, int cchSrc = -1);

	eStlInline void CopyTo(PWSTR pszDst, int cch = -1)
	{
		if (cch < 0)
			cch = m_cchText;
		if (!cch || !m_pszText || !pszDst)
			return;
		wcsncpy(pszDst, m_pszText, cch);
		*(pszDst + cch) = L'\0';
	}
};

eStlInline bool operator<(const CSimpleRefStrW& x1, PCWSTR x2)
{
	if (!x1.m_pszText)
		return !!(x2);
	else if (!x2)
		return false;
	else
		return wcscmp(x1.m_pszText, x2) < 0;
}

eStlInline bool operator<(const CSimpleRefStrW& x1, const CSimpleRefStrW& x2)
{
	return operator<(x1, x2.m_pszText);
}

eStlInline bool operator>(const CSimpleRefStrW& x1, PCWSTR x2)
{
	if (!x2)
		return !!(x1.m_pszText);
	else if (!x1.m_pszText)
		return false;
	else
		return wcscmp(x1.m_pszText, x2) > 0;
}

eStlInline bool operator>(const CSimpleRefStrW& x1, const CSimpleRefStrW& x2)
{
	return operator>(x1, x2.m_pszText);
}


#define CFBitMapmax(a,b)            (((a) > (b)) ? (a) : (b))
#define CFBitMapmin(a,b)            (((a) < (b)) ? (a) : (b))
/*��ǿλͼ-��������*/
class CFBitMap
{
public:
	inline CFBitMap()
	{
		m_nBitmapSize = 0;
		m_pBitmap = NULL;
		m_pBitsData = NULL;
		m_pBmpFileHeader = NULL;
		m_pBmpInfoHeader = NULL;
		m_BytesPerLine = NULL;
	}
	inline CFBitMap(const CFBitMap& o)
	{
		CreateFromMem(o.m_pBitmap, o.m_nBitmapSize);
	}

	inline ~CFBitMap()
	{
		Destory();
	}

	void Destory()
	{
		if (m_pBitmap)
			delete[] m_pBitmap;
		m_pBitmap = NULL;
	}

	BOOL CreateBitmap(int nWidth, int nHeight, int nColorBitCount)
	{
		if (nColorBitCount == 24)
			return CreateBitmap24(nWidth, nHeight);
		else
			return CreateBitmap32(nWidth, nHeight);
	}

	BOOL CreateBitmap24(int nWidth, int nHeight)
	{
		Destory();

		//ֻ֧��24λλͼ
		m_BytesPerLine = CalcBytesPerLine(nWidth, 24);

		int nBitmapSize = 0;
		nBitmapSize = sizeof(BITMAPFILEHEADER);
		nBitmapSize = nBitmapSize + sizeof(BITMAPINFOHEADER);
		nBitmapSize = nBitmapSize + nHeight * m_BytesPerLine;
		m_pBitmap = new byte[nBitmapSize];

		//��ʼ����λͼ
		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader = (BITMAPFILEHEADER*)pData;
		pBmpFileHeader->bfType = 0x4d42;
		pBmpFileHeader->bfSize = (DWORD)nBitmapSize;
		pBmpFileHeader->bfReserved1 = 0;
		pBmpFileHeader->bfReserved2 = 0;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)(pData + sizeof(BITMAPFILEHEADER));
		memset(pBmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
		pBmpInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
		pBmpFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		pBmpInfoHeader->biWidth = nWidth;
		pBmpInfoHeader->biHeight = nHeight;
		pBmpInfoHeader->biBitCount = 24;
		pBmpInfoHeader->biPlanes = 1;
		pBmpInfoHeader->biXPelsPerMeter = 2834;
		pBmpInfoHeader->biYPelsPerMeter = 2834;

		pBmpInfoHeader->biSizeImage = m_BytesPerLine * pBmpInfoHeader->biHeight;

		m_nBitmapSize = nBitmapSize;
		m_pBitsData = pData + pBmpFileHeader->bfOffBits;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;

		return TRUE;

	}
	BOOL CreateBitmap32(int nWidth, int nHeight)
	{
		Destory();

		m_BytesPerLine = CalcBytesPerLine(nWidth, 32);

		int nBitmapSize = 0;
		nBitmapSize = sizeof(BITMAPFILEHEADER);
		nBitmapSize = nBitmapSize + sizeof(BITMAPINFOHEADER);
		nBitmapSize = nBitmapSize + nHeight * m_BytesPerLine;
		m_pBitmap = new byte[nBitmapSize];

		//��ʼ����λͼ
		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader = (BITMAPFILEHEADER*)pData;
		pBmpFileHeader->bfType = 0x4d42;
		pBmpFileHeader->bfSize = (DWORD)nBitmapSize;
		pBmpFileHeader->bfReserved1 = 0;
		pBmpFileHeader->bfReserved2 = 0;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)(pData + sizeof(BITMAPFILEHEADER));
		memset(pBmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
		pBmpInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
		pBmpFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		pBmpInfoHeader->biWidth = nWidth;
		pBmpInfoHeader->biHeight = nHeight;
		pBmpInfoHeader->biBitCount = 32;
		pBmpInfoHeader->biPlanes = 1;
		pBmpInfoHeader->biXPelsPerMeter = 2834;
		pBmpInfoHeader->biYPelsPerMeter = 2834;
		pBmpInfoHeader->biSizeImage = m_BytesPerLine * pBmpInfoHeader->biHeight;

		m_nBitmapSize = nBitmapSize;
		m_pBitsData = pData + pBmpFileHeader->bfOffBits;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;

		return TRUE;
	}
	BOOL CreateFromMem(void* pBitMapData, int nSize)
	{
		if (pBitMapData == NULL || nSize == 0)
			return FALSE;

		byte* pData = (byte*)pBitMapData;
		BITMAPFILEHEADER* pBmpFileHeader = (BITMAPFILEHEADER*)pData;
		if (pBmpFileHeader->bfType != 0x4d42)
			return FALSE;

		if (pBmpFileHeader->bfSize != (DWORD)nSize)
			return FALSE;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)(pData + sizeof(BITMAPFILEHEADER));
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;

		if (pBmpInfoHeader->biBitCount == 32)
			return CreateFromBitmap32(pBitMapData, nSize);
		else if (pBmpInfoHeader->biBitCount == 24)
			return CreateFromBitmap24(pBitMapData, nSize);
		return FALSE;
	}
	BOOL CreateFromBitmap24(void* pBitMapData, int nSize)
	{
		Destory();
		m_pBitmap = new byte[nSize];
		if (m_pBitmap == NULL)
			return FALSE;

		memcpy(m_pBitmap, pBitMapData, nSize);

		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader = (BITMAPFILEHEADER*)pData;
		if (pBmpFileHeader->bfType != 0x4d42)
			return FALSE;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)(pData + sizeof(BITMAPFILEHEADER));
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;
		//λͼ����
		byte* pBmpdata = pData + pBmpFileHeader->bfOffBits;
		//һ��ռ���ٸ��ֽ�
		int bytesPerLine = CalcBytesPerLine(pBmpInfoHeader->biWidth, pBmpInfoHeader->biBitCount);

		m_nBitmapSize = pBmpFileHeader->bfSize;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		m_pBitsData = pBmpdata;
		m_BytesPerLine = bytesPerLine;

		if (m_pBmpInfoHeader->biSizeImage == 0)
		{
			int nHeight = pBmpInfoHeader->biHeight;
			if (nHeight < 0)
				nHeight = 0 - nHeight;
			m_pBmpInfoHeader->biSizeImage = m_BytesPerLine * nHeight;
		}

		return TRUE;
	}
	BOOL CreateFromBitmap32(void* pBitMapData, int nSize)
	{
		Destory();
		m_pBitmap = new byte[nSize];
		if (m_pBitmap == NULL)
			return FALSE;

		memcpy(m_pBitmap, pBitMapData, nSize);

		byte* pData = (byte*)m_pBitmap;
		BITMAPFILEHEADER* pBmpFileHeader = (BITMAPFILEHEADER*)pData;
		if (pBmpFileHeader->bfType != 0x4d42)
			return FALSE;

		BITMAPINFOHEADER* pBmpInfoHeader = (BITMAPINFOHEADER*)(pData + sizeof(BITMAPFILEHEADER));
		if (pBmpInfoHeader->biSize != sizeof(BITMAPINFOHEADER))
			return FALSE;
		//λͼ����
		byte* pBmpdata = pData + pBmpFileHeader->bfOffBits;

		//һ��ռ���ٸ��ֽ�
		//32λλͼ��һ������ռ��4���ֽڣ�����ֱ���ÿ��*4 ����
		int bytesPerLine = CalcBytesPerLine(pBmpInfoHeader->biWidth, pBmpInfoHeader->biBitCount);

		m_nBitmapSize = pBmpFileHeader->bfSize;
		m_pBmpFileHeader = pBmpFileHeader;
		m_pBmpInfoHeader = pBmpInfoHeader;
		m_pBitsData = pBmpdata;
		m_BytesPerLine = bytesPerLine;

		if (m_pBmpInfoHeader->biSizeImage == 0)
		{
			int nHeight = pBmpInfoHeader->biHeight;
			if (nHeight < 0)
				nHeight = 0 - nHeight;
			m_pBmpInfoHeader->biSizeImage = m_BytesPerLine * nHeight;
		}

		return TRUE;
	}

	int  GetColorBitCount()
	{
		return m_pBmpInfoHeader->biBitCount;
	}
	BOOL IsValid()
	{
		return m_pBitmap ? TRUE : FALSE;
	}
	int CalcBytesPerLine(int nWidth, int nBitCount)
	{
		return (nWidth * nBitCount + 31) / 32 * 4;
	}
	int GetWidth()
	{
		return m_pBmpInfoHeader->biWidth < 0 ? 0 - m_pBmpInfoHeader->biWidth : m_pBmpInfoHeader->biWidth;
	}
	int GetHeight()
	{
		return m_pBmpInfoHeader->biHeight < 0 ? 0 - m_pBmpInfoHeader->biHeight : m_pBmpInfoHeader->biHeight;
	}
	VOID* GetBitsData()
	{
		return m_pBitsData;
	}
	int GetBitsCount()
	{
		return m_pBmpInfoHeader->biSizeImage;
	}
	int GetPixOffset(int x, int y)
	{
		int nReturn = 0;

		if (m_pBmpInfoHeader->biHeight < 0)
		{
			//Ҫ���Ŷ�ȡ
			if (GetColorBitCount() == 24)
			{
				//24λλͼ
				nReturn = y * m_BytesPerLine + x * 3;
			}
			else
			{
				//32λλͼ
				nReturn = y * m_BytesPerLine + x * 4;
			}

		}
		else
		{
			//Ҫ���Ŷ�ȡ
			if (GetColorBitCount() == 24)
			{
				//24λλͼ
				nReturn = (GetHeight() - y - 1) * m_BytesPerLine + x * 3;
			}
			else
			{
				//32λλͼ
				nReturn = (GetHeight() - y - 1) * m_BytesPerLine + x * 4;
			}
		}

		return nReturn;
	}
	BYTE GetR(int x, int y)
	{
		return m_pBitsData[GetPixOffset(x, y) + 2];
	}
	BYTE GetG(int x, int y)
	{
		return m_pBitsData[GetPixOffset(x, y) + 1];
	}
	BYTE GetB(int x, int y)
	{
		return m_pBitsData[GetPixOffset(x, y)];
	}
	BYTE GetAlpha(int x, int y)
	{
		if (GetColorBitCount() == 32)
			return m_pBitsData[GetPixOffset(x, y) + 3];
		return 0;
	}
	void SetR(int x, int y, BYTE v)
	{
		m_pBitsData[GetPixOffset(x, y) + 2] = v;
	}
	void SetG(int x, int y, BYTE v)
	{
		m_pBitsData[GetPixOffset(x, y) + 1] = v;
	}
	void SetB(int x, int y, BYTE v)
	{
		m_pBitsData[GetPixOffset(x, y)] = v;
	}
	void SetAlpha(int x, int y, BYTE v)
	{
		if (GetColorBitCount() == 32)
			m_pBitsData[GetPixOffset(x, y) + 3] = v;
	}

	BYTE GetR(int index)
	{
		return m_pBitsData[index + 2];
	}
	BYTE GetG(int index)
	{
		return m_pBitsData[index + 1];
	}
	BYTE GetB(int index)
	{
		return m_pBitsData[index];
	}
	BYTE GetAlpha(int index)
	{
		if (GetColorBitCount() == 32)
			return m_pBitsData[index + 3];
		return 0;
	}
	void SetR(int index, BYTE v)
	{
		m_pBitsData[index + 2] = v;
	}
	void SetG(int index, BYTE v)
	{
		m_pBitsData[index + 1] = v;
	}
	void SetB(int index, BYTE v)
	{
		m_pBitsData[index] = v;
	}
	void SetAlpha(int index, BYTE v)
	{
		if (GetColorBitCount() == 32)
			m_pBitsData[index + 3] = v;
	}

	int GetPixel(int nIndex)
	{
		DWORD color = 0;
		BYTE* pPix = &m_pBitsData[nIndex];

		BYTE* pDes = (BYTE*)&color;
		pDes[0] = pPix[2];  //R
		pDes[1] = pPix[1];  //G
		pDes[2] = pPix[0];  //B

		return color;
	}
	int GetPixel(int x, int y)
	{
		DWORD color = 0;
		BYTE* pPix = &m_pBitsData[GetPixOffset(x, y)];

		BYTE* pDes = (BYTE*)&color;
		pDes[0] = pPix[2];  //R
		pDes[1] = pPix[1];  //G
		pDes[2] = pPix[0];  //B

		return color;
	}
	VOID SetPixel(int nIndex, int color)
	{
		BYTE* pPix = &m_pBitsData[nIndex];

		BYTE* pSrc = (BYTE*)&color;

		if (GetColorBitCount() == 32)
			pPix[3] = pSrc[3]; //R
		pPix[0] = pSrc[2]; //B
		pPix[1] = pSrc[1]; //G
		pPix[2] = pSrc[0]; //R
	}

	VOID SetPixel(int x, int y, int color)
	{
		BYTE* pPix = &m_pBitsData[GetPixOffset(x, y)];

		BYTE* pSrc = (BYTE*)&color;

		if (GetColorBitCount() == 32)
			pPix[3] = pSrc[3]; //R
		pPix[0] = pSrc[2]; //B
		pPix[1] = pSrc[1]; //G
		pPix[2] = pSrc[0]; //R
	}

	// flase ��ɫ
	// ture  ��ɫ
	void FillBG(int nColor)
	{
		BYTE* pData = (BYTE*)m_pBitmap;
		for (int nRow = 0; nRow < GetHeight(); nRow++)
		{
			for (int nCol = 0; nCol < GetWidth(); nCol++)
				SetPixel(nCol, nRow, nColor);
		}
	}

	//��������
	void SetBrightness(int nLight)
	{

		int _brightness = CFBitMapmax(-255, CFBitMapmin(255, nLight));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol, dwRow);
				BYTE bPixG = GetG(dwCol, dwRow);
				BYTE bPixR = GetR(dwCol, dwRow);

				bPixR = (BYTE)CFBitMapmax(0, CFBitMapmin(bPixR + _brightness, 255));
				bPixG = (BYTE)CFBitMapmax(0, CFBitMapmin(bPixG + _brightness, 255));
				bPixB = (BYTE)CFBitMapmax(0, CFBitMapmin(bPixB + _brightness, 255));

				SetR(dwCol, dwRow, bPixR);
				SetG(dwCol, dwRow, bPixG);
				SetB(dwCol, dwRow, bPixB);
			}
		}
	}

	void GetRedChannel(int channel[256])
	{
		memset(channel, 0, 256 * sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetR(dwCol, dwRow);
				channel[bPixR]++;
			}
		}
	}
	void GetGreenChannel(int channel[256])
	{
		memset(channel, 0, 256 * sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetG(dwCol, dwRow);
				channel[bPixR]++;
			}
		}
	}

	void GetBlueChannel(int channel[256])
	{
		memset(channel, 0, 256 * sizeof(int));

		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixR = GetG(dwCol, dwRow);
				channel[bPixR]++;
			}
		}
	}

	void BlackAndWhite(int threshold)
	{
		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol, dwRow);
				BYTE bPixG = GetG(dwCol, dwRow);
				BYTE bPixR = GetR(dwCol, dwRow);

				double v = bPixR * 0.299 + bPixG * 0.587 + bPixB * 0.114;
				if (v > threshold)
					SetPixel(dwCol, dwRow, RGB(255, 255, 255));
				else
					SetPixel(dwCol, dwRow, 0);
			}
		}
	}
	void Gray()
	{
		for (LONG dwRow = 0; dwRow < GetHeight(); dwRow++)
		{
			for (LONG dwCol = 0; dwCol < GetWidth(); dwCol++)
			{
				BYTE bPixB = GetB(dwCol, dwRow);
				BYTE bPixG = GetG(dwCol, dwRow);
				BYTE bPixR = GetR(dwCol, dwRow);
				BYTE v = (BYTE)(bPixR * 0.299 + bPixG * 0.587 + bPixB * 0.114);
				SetR(dwCol, dwRow, v);
				SetG(dwCol, dwRow, v);
				SetB(dwCol, dwRow, v);
			}
		}
	}

	void xuanzhuan(int angle, CFBitMap& NewBitmap)
	{
		//ժ�� https://blog.csdn.net/qq_36752072/article/details/78151770
		int width = GetWidth();
		int height = GetHeight();

		if (angle % 360 == 270)
			angle++;
		double thelta = (double)(angle * 3.141592653 / 180);
		int newWidth = abs((int)((double)width * cos(thelta) + (double)height * sin(thelta)));
		int newHeight = abs((int)((double)width * sin(thelta) + (double)height * cos(thelta)));

		int rotateX = width / 2;
		int rotateY = height / 2;
		//��ת���ĵ�
		int write_rotateX = newWidth / 2;
		int write_rotateY = newHeight / 2;

		int l_width = GetBytesPerLine();

		NewBitmap.CreateBitmap(newWidth, newHeight, GetColorBitCount());
		// step 3 : ��ɽ�ͼ����Ϣ��Ǩ��
		for (int hnum = 0; hnum < newHeight; ++hnum) {
			for (int wnum = 0; wnum < newWidth; ++wnum) {
				// �����ݵ��±�Ϊindex
				int index = NewBitmap.GetPixOffset(wnum, hnum);
				// ���ù�ʽ�������ԭ���ĵ�ĵط�
				double d_original_img_hnum = (wnum - write_rotateX) * sin(thelta) + (hnum - write_rotateY) * cos(thelta) + rotateY;
				double d_original_img_wnum = (wnum - write_rotateX) * cos(thelta) - (hnum - write_rotateY) * sin(thelta) + rotateX;

				if (d_original_img_hnum < 0 || d_original_img_hnum > height || d_original_img_wnum < 0 || d_original_img_wnum > width) {
					NewBitmap.SetPixel(index, 0);
					continue;
				}
				else {
					// ����������ʹ��˫���Բ�ֵ������ɶ�Ӧ
					int i_original_img_hnum = (int)d_original_img_hnum;
					int i_original_img_wnum = (int)d_original_img_wnum;
					double distance_to_a_X = d_original_img_wnum - i_original_img_wnum;
					double distance_to_a_Y = d_original_img_hnum - i_original_img_hnum;

					int original_point_A = GetPixOffset(i_original_img_wnum, i_original_img_hnum);
					int original_point_B = GetPixOffset(i_original_img_wnum + 1, i_original_img_hnum);
					int original_point_C = GetPixOffset(i_original_img_wnum, i_original_img_hnum + 1);
					int original_point_D = GetPixOffset(i_original_img_wnum + 1, i_original_img_hnum + 1);

					if (i_original_img_wnum == width - 1) {
						original_point_A = original_point_B;
						original_point_C = original_point_D;
					}
					if (i_original_img_hnum == height - 1) {
						original_point_C = original_point_A;
						original_point_D = original_point_B;
					}

					double pixelB = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetB(original_point_A)
						+ (1 - distance_to_a_X) * distance_to_a_Y * GetB(original_point_B)
						+ distance_to_a_X * (1 - distance_to_a_Y) * GetB(original_point_C)
						+ distance_to_a_X * distance_to_a_Y * GetB(original_point_D);

					double pixelG = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetG(original_point_A)
						+ (1 - distance_to_a_X) * distance_to_a_Y * GetG(original_point_B)
						+ distance_to_a_X * (1 - distance_to_a_Y) * GetG(original_point_C)
						+ distance_to_a_X * distance_to_a_Y * GetG(original_point_D);

					double pixelR = (1 - distance_to_a_X) * (1 - distance_to_a_Y) * GetR(original_point_A)
						+ (1 - distance_to_a_X) * distance_to_a_Y * GetR(original_point_B)
						+ distance_to_a_X * (1 - distance_to_a_Y) * GetR(original_point_C)
						+ distance_to_a_X * distance_to_a_Y * GetR(original_point_D);
					NewBitmap.SetB(index, (BYTE)pixelB);
					NewBitmap.SetG(index, (BYTE)pixelG);
					NewBitmap.SetR(index, (BYTE)pixelR);
				}
			}
		}
	}
	void Zoom(int MYDRAW_WIDTH, int MYDRAW_HEIGHT, CFBitMap& NewBitmap)
	{
		int height = GetHeight();
		int width = GetWidth();
		NewBitmap.CreateBitmap(MYDRAW_WIDTH, MYDRAW_HEIGHT, GetColorBitCount());
		int l_width = GetBytesPerLine();

		for (int hnum = 0; hnum < MYDRAW_HEIGHT; hnum++)
			for (int wnum = 0; wnum < MYDRAW_WIDTH; wnum++)
			{
				double d_original_img_hnum = hnum * height / (double)MYDRAW_HEIGHT;
				double d_original_img_wnum = wnum * width / (double)MYDRAW_WIDTH;
				int i_original_img_hnum = (int)d_original_img_hnum;
				int i_original_img_wnum = (int)d_original_img_wnum;
				double distance_to_a_x = d_original_img_wnum - i_original_img_wnum;//��ԭͼ������a���ˮƽ����  
				double distance_to_a_y = d_original_img_hnum - i_original_img_hnum;//��ԭͼ������a��Ĵ�ֱ����  

				int original_point_a = GetPixOffset(i_original_img_wnum, i_original_img_hnum);
				int original_point_b = GetPixOffset(i_original_img_wnum + 1, i_original_img_hnum);
				int original_point_c = GetPixOffset(i_original_img_wnum, i_original_img_hnum + 1);
				int original_point_d = GetPixOffset(i_original_img_wnum + 1, i_original_img_hnum + 1);

				//if (i_original_img_hnum +1 == MYDRAW_HEIGHT - 1)
				if (i_original_img_hnum + 1 >= height)
				{
					original_point_c = original_point_a;
					original_point_d = original_point_b;
				}
				if (i_original_img_wnum + 1 >= width)
				{
					original_point_b = original_point_a;
					original_point_d = original_point_c;
				}

				int pixel_point = NewBitmap.GetPixOffset(wnum, hnum);

				double pixelB =
					GetB(original_point_a) * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
					GetB(original_point_b) * distance_to_a_x * (1 - distance_to_a_y) +
					GetB(original_point_c) * distance_to_a_y * (1 - distance_to_a_x) +
					GetB(original_point_d) * distance_to_a_y * distance_to_a_x;
				double pixelG =
					GetG(original_point_a) * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
					GetG(original_point_b) * distance_to_a_x * (1 - distance_to_a_y) +
					GetG(original_point_c) * distance_to_a_y * (1 - distance_to_a_x) +
					GetG(original_point_d) * distance_to_a_y * distance_to_a_x;
				double pixelR =
					GetR(original_point_a) * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
					GetR(original_point_b) * distance_to_a_x * (1 - distance_to_a_y) +
					GetR(original_point_c) * distance_to_a_y * (1 - distance_to_a_x) +
					GetR(original_point_d) * distance_to_a_y * distance_to_a_x;

				NewBitmap.SetB(pixel_point, (BYTE)pixelB);
				NewBitmap.SetG(pixel_point, (BYTE)pixelG);
				NewBitmap.SetR(pixel_point, (BYTE)pixelR);
			}
	}
	int GetBytesPerLine()
	{
		return m_BytesPerLine;
	}
	template<typename T> 
	T* GetBitmap()
	{
		return static_cast<T*>(m_pBitmap);
	}
	int GetBitmapSize()
	{
		return m_nBitmapSize;
	}

protected:
	void* m_pBitmap;
	int   m_nBitmapSize;
	byte* m_pBitsData;
	BITMAPFILEHEADER* m_pBmpFileHeader;
	BITMAPINFOHEADER* m_pBmpInfoHeader;
	int m_BytesPerLine;
};
#undef CFBitMapmax
#undef CFBitMapmin


ESTL_NAMESPACE_END