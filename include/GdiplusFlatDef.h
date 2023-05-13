/*
* GdiplusFlatDef.h ： 平面GDI+定义
*/
#pragma once
#include <Windows.h>

#define DECLFAKEGDIPOBJ(type) struct type{int unused;}
#define DECLFAKEGDIPOBJINHERIT(type,base) struct type:public base{int unused;}
#define WINGDIPAPI WINAPI
#define GDIPCONST const

typedef void* DrawImageAbort;
typedef float REAL;
typedef DWORD ARGB;

enum GpStatus
{
	Ok,
	GenericError,
	InvalidParameter,
	OutOfMemory,
	ObjectBusy,
	InsufficientBuffer,
	NotImplemented,
	Win32Error,
	WrongState,
	Aborted,
	FileNotFound,
	ValueOverflow,
	AccessDenied,
	UnknownImageFormat,
	FontFamilyNotFound,
	FontStyleNotFound,
	NotTrueTypeFont,
	UnsupportedGdiplusVersion,
	GdiplusNotInitialized,
	PropertyNotFound,
	PropertyNotSupported,
	ProfileNotFound
};
enum SmoothingMode
{
	SmoothingModeDefault,
	SmoothingModeHighSpeed,
	SmoothingModeHighQuality,
	SmoothingModeNone,
};
enum TextRenderingHint
{
	TextRenderingHintSystemDefault,
	TextRenderingHintSingleBitPerPixelGridFit,
	TextRenderingHintSingleBitPerPixel,
	TextRenderingHintAntiAliasGridFit,
	TextRenderingHintAntiAlias,
	TextRenderingHintClearTypeGridFit
};
enum FillMode
{
	FillModeAlternate,
	FillModeWinding
};
enum WrapMode
{
	WrapModeTile,
	WrapModeTileFlipX,
	WrapModeTileFlipY,
	WrapModeTileFlipXY,
	WrapModeClamp
};
enum FontStyle
{
	FontStyleRegular,
	FontStyleBold,
	FontStyleItalic,
	FontStyleBoldItalic,
	FontStyleUnderline,
	FontStyleStrikeout
};
enum StringAlignment
{
	StringAlignmentNear,
	StringAlignmentCenter,
	StringAlignmentFar
};
enum Unit
{
	UnitWorld,
	UnitDisplay,
	UnitPixel,
	UnitPoint,
	UnitInch,
	UnitDocument,
	UnitMillimeter
};
enum StringFormatFlags
{
	StringFormatFlagsDirectionRightToLeft = 0x00000001,
	StringFormatFlagsDirectionVertical = 0x00000002,
	StringFormatFlagsNoFitBlackBox = 0x00000004,
	StringFormatFlagsDisplayFormatControl = 0x00000020,
	StringFormatFlagsNoFontFallback = 0x00000400,
	StringFormatFlagsMeasureTrailingSpaces = 0x00000800,
	StringFormatFlagsNoWrap = 0x00001000,
	StringFormatFlagsLineLimit = 0x00002000,
	StringFormatFlagsNoClip = 0x00004000,
	StringFormatFlagsBypassGDI = 0x80000000
};
enum PixelFormat
{
	PixelFormatIndexed = 0x00010000,
	PixelFormatGDI = 0x00020000,
	PixelFormatAlpha = 0x00040000,
	PixelFormatPAlpha = 0x00080000,
	PixelFormatExtended = 0x00100000,
	PixelFormatCanonical = 0x00200000,

	PixelFormatUndefined = 0,
	PixelFormatDontCare = 0,

	PixelFormat1bppIndexed = (1 | (1 << 8) | PixelFormatIndexed | PixelFormatGDI),
	PixelFormat4bppIndexed = (2 | (4 << 8) | PixelFormatIndexed | PixelFormatGDI),
	PixelFormat8bppIndexed = (3 | (8 << 8) | PixelFormatIndexed | PixelFormatGDI),
	PixelFormat16bppGrayScale = (4 | (16 << 8) | PixelFormatExtended),
	PixelFormat16bppRGB555 = (5 | (16 << 8) | PixelFormatGDI),
	PixelFormat16bppRGB565 = (6 | (16 << 8) | PixelFormatGDI),
	PixelFormat16bppARGB1555 = (7 | (16 << 8) | PixelFormatAlpha | PixelFormatGDI),
	PixelFormat24bppRGB = (8 | (24 << 8) | PixelFormatGDI),
	PixelFormat32bppRGB = (9 | (32 << 8) | PixelFormatGDI),
	PixelFormat32bppARGB = (10 | (32 << 8) | PixelFormatAlpha | PixelFormatGDI | PixelFormatCanonical),
	PixelFormat32bppPARGB = (11 | (32 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatGDI),
	PixelFormat48bppRGB = (12 | (48 << 8) | PixelFormatExtended),
	PixelFormat64bppARGB = (13 | (64 << 8) | PixelFormatAlpha | PixelFormatCanonical | PixelFormatExtended),
	PixelFormat64bppPARGB = (14 | (64 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatExtended),
	PixelFormat32bppCMYK = (15 | (32 << 8)),
	PixelFormatMax = 16
};

struct GdiplusStartupInput
{
	UINT32 GdiplusVersion;
	void* DebugEventCallback;
	BOOL SuppressBackgroundThread;
	BOOL SuppressExternalCodecs;
};
struct RectF
{
	REAL Left;
	REAL Top;
	REAL Width;
	REAL Height;
};
struct PointF
{
	REAL x;
	REAL y;
};
struct BlurParams
{
	REAL radius;
	BOOL  expandEdge;
};

DECLFAKEGDIPOBJ(GpGraphics);
DECLFAKEGDIPOBJ(GpFontCollection);
DECLFAKEGDIPOBJ(GpFontFamily);
DECLFAKEGDIPOBJ(GpFont);
DECLFAKEGDIPOBJ(GpStringFormat);
DECLFAKEGDIPOBJ(GpPen);
DECLFAKEGDIPOBJ(GpPath);
DECLFAKEGDIPOBJ(GpBrush);
DECLFAKEGDIPOBJINHERIT(GpSolidFill, GpBrush);
DECLFAKEGDIPOBJ(GpLineGradient);
DECLFAKEGDIPOBJ(GpImage);
DECLFAKEGDIPOBJ(GpImageAttributes);
DECLFAKEGDIPOBJ(GpEffect);
DECLFAKEGDIPOBJINHERIT(GpBitmap, GpImage);

EXTERN_C_START
GpStatus WINGDIPAPI	GdiplusStartup(ULONG_PTR* token, const GdiplusStartupInput* input, void* output);
void	 WINGDIPAPI	GdiplusShutdown(ULONG_PTR token);
GpStatus WINGDIPAPI	GdipCreateFromHDC(HDC hdc, GpGraphics** graphics);
GpStatus WINGDIPAPI	GdipSetSmoothingMode(GpGraphics* graphics, SmoothingMode smoothingMode);
GpStatus WINGDIPAPI GdipSetTextRenderingHint(GpGraphics* graphics, TextRenderingHint mode);
GpStatus WINGDIPAPI	GdipCreateFontFamilyFromName(GDIPCONST WCHAR* name, GpFontCollection* fontCollection, GpFontFamily** FontFamily);
GpStatus WINGDIPAPI GdipCreateFont(GDIPCONST GpFontFamily* fontFamily, REAL emSize, FontStyle style, Unit unit, GpFont** font);
GpStatus WINGDIPAPI GdipCreateStringFormat(StringFormatFlags formatAttributes, LANGID language, GpStringFormat** format);
GpStatus WINGDIPAPI GdipSetStringFormatAlign(GpStringFormat* format, StringAlignment align);
GpStatus WINGDIPAPI GdipCreatePen1(ARGB color, REAL width, Unit unit, GpPen** pen);
GpStatus WINGDIPAPI GdipMeasureString(GpGraphics* graphics, GDIPCONST WCHAR* string, INT length, GDIPCONST GpFont* font,
	GDIPCONST RectF* layoutRect, GDIPCONST GpStringFormat* stringFormat, RectF* boundingBox, INT* codepointsFitted, INT* linesFilled);
GpStatus WINGDIPAPI GdipCreatePath(FillMode brushMode, GpPath** path);
GpStatus WINGDIPAPI GdipAddPathString(GpPath* path, GDIPCONST WCHAR* string, INT length, GDIPCONST GpFontFamily* family,
	FontStyle style, REAL emSize, GDIPCONST RectF* layoutRect, GDIPCONST GpStringFormat* format);
GpStatus WINGDIPAPI GdipCreateSolidFill(ARGB color, GpSolidFill** brush);
GpStatus WINGDIPAPI GdipFillPath(GpGraphics* graphics, GpBrush* brush, GpPath* path);
GpStatus WINGDIPAPI GdipDrawPath(GpGraphics* graphics, GpPen* pen, GpPath* path);
GpStatus WINGDIPAPI GdipCreateLineBrush(GDIPCONST PointF* point1, GDIPCONST PointF* point2, ARGB color1, ARGB color2,
	WrapMode wrapMode, GpLineGradient** lineGradient);
GpStatus WINGDIPAPI GdipFillRectangle(GpGraphics* graphics, GpBrush* brush, REAL x, REAL y, REAL width, REAL height);
GpStatus WINGDIPAPI GdipGraphicsClear(GpGraphics* graphics, ARGB color);
GpStatus WINGDIPAPI GdipDrawRectangle(GpGraphics* graphics, GpPen* pen, REAL x, REAL y, REAL width, REAL height);
GpStatus WINGDIPAPI GdipResetPath(GpPath* path);
GpStatus WINGDIPAPI GdipLoadImageFromStream(IStream* stream, GpImage** image);
GpStatus WINGDIPAPI GdipGetImageHeight(GpImage* image, UINT* height);
GpStatus WINGDIPAPI GdipGetImageWidth(GpImage* image, UINT* width);
GpStatus WINGDIPAPI GdipDrawImageRectRect(GpGraphics* graphics, GpImage* image, REAL dstx, REAL dsty, REAL dstwidth, REAL dstheight,
	REAL srcx, REAL srcy, REAL srcwidth, REAL srcheight, Unit srcUnit, GDIPCONST GpImageAttributes* imageAttributes,
	DrawImageAbort callback, VOID* callbackData);
GpStatus WINGDIPAPI GdipDisposeImage(GpImage* image);
GpStatus WINGDIPAPI GdipDeletePath(GpPath* path);
GpStatus WINGDIPAPI GdipDeletePen(GpPen* pen);
GpStatus WINGDIPAPI GdipDeleteBrush(GpBrush* brush);
GpStatus WINGDIPAPI GdipDeleteGraphics(GpGraphics* graphics);
GpStatus WINGDIPAPI GdipDeleteFont(GpFont* font);
GpStatus WINGDIPAPI GdipDeleteStringFormat(GpStringFormat* format);
GpStatus WINGDIPAPI GdipDeleteFontFamily(GpFontFamily* fontFamily);
GpStatus WINGDIPAPI GdipCreateEffect(const GUID guid, GpEffect** effect);
GpStatus WINGDIPAPI GdipDeleteEffect(GpEffect* effect);
GpStatus WINGDIPAPI GdipCreateBitmapFromHBITMAP(HBITMAP hbm, HPALETTE hpal, GpBitmap** bitmap);
GpStatus WINGDIPAPI GdipSetEffectParameters(GpEffect* effect, const VOID* params, const UINT size);
GpStatus WINGDIPAPI GdipCreateBitmapFromGraphics(INT width, INT height, GpGraphics* target, GpBitmap** bitmap);
GpStatus WINGDIPAPI GdipBitmapApplyEffect(GpBitmap* bitmap, GpEffect* effect, RECT* roi, BOOL useAuxData, VOID** auxData, INT* auxDataSize);
GpStatus WINGDIPAPI GdipCreateBitmapFromStream(IStream* stream, GpBitmap** bitmap);
GpStatus WINGDIPAPI GdipCloneBitmapArea(REAL x, REAL y, REAL width, REAL height, PixelFormat format, GpBitmap* srcBitmap, GpBitmap** dstBitmap);
GpStatus WINGDIPAPI GdipGetImageGraphicsContext(GpImage* image, GpGraphics** graphics);
GpStatus WINGDIPAPI GdipCreateBitmapFromScan0(INT width, INT height, INT stride, PixelFormat format, BYTE* scan0, GpBitmap** bitmap);
GpStatus WINGDIPAPI GdipDrawRectangle(GpGraphics* graphics, GpPen* pen, REAL x, REAL y, REAL width, REAL height);
GpStatus WINGDIPAPI GdipLoadImageFromFile(GDIPCONST WCHAR* filename, GpImage** image);
GpStatus WINGDIPAPI GdipCreateHBITMAPFromBitmap(GpBitmap* bitmap, HBITMAP* hbmReturn, ARGB background);
GpStatus WINGDIPAPI GdipDrawImage(GpGraphics* graphics, GpImage* image, REAL x, REAL y);
GpStatus WINGDIPAPI GdipCreateHICONFromBitmap(GpBitmap* bitmap, HICON* hbmReturn);
GpStatus WINGDIPAPI GdipCreateBitmapFromHICON(HICON hicon, GpBitmap** bitmap);
GpStatus WINGDIPAPI GdipStringFormatGetGenericDefault(GpStringFormat** format);
GpStatus WINGDIPAPI GdipDrawString(GpGraphics* graphics, GDIPCONST WCHAR* string, INT length, GDIPCONST GpFont* font,
	GDIPCONST RectF* layoutRect, GDIPCONST GpStringFormat* stringFormat, GDIPCONST GpBrush* brush);
GpStatus WINGDIPAPI GdipSetStringFormatLineAlign(GpStringFormat* format, StringAlignment align);
EXTERN_C_END