//组件库需用通用函数引入此头文件
#include "ElibHelp.h"
#include "GdiplusFlatDef.h"
#include <CommCtrl.h>
#include <unordered_map>
#include <Shlwapi.h>
#include <windowsx.h>
#include <commoncontrols.h>
/*易定义的标签反馈事件*/
#define WM_EFEEDBACK  32885


ESTL_NAMESPACE_BEGIN
eStlInline void SetLBText(HWND hLB, int idx, PCWSTR pszText)
{
	int iCurrSel = SendMessageW(hLB, LB_GETCURSEL, 0, 0);
	auto lParam = SendMessageW(hLB, LB_GETITEMDATA, idx, 0);
	SendMessageW(hLB, LB_DELETESTRING, idx, 0);
	SendMessageW(hLB, LB_INSERTSTRING, idx, (LPARAM)(pszText ? pszText : L""));
	SendMessageW(hLB, LB_SETITEMDATA, idx, lParam);
	SendMessageW(hLB, LB_SETCURSEL, iCurrSel, 0);
}

void GetDataFromHBIT(HBITMAP hBitmap, std::vector<unsigned char>& pData);

/// <summary>
/// 创建字体。
/// easy font
/// （CreateFont wrapper）
/// </summary>
/// <param name="pszFontName">字体名</param>
/// <param name="nPoint">点数</param>
/// <param name="nWeight">粗细，1~1000</param>
/// <param name="IsItalic">是否倾斜</param>
/// <param name="IsUnderline">是否下划线</param>
/// <param name="IsStrikeOut">是否删除线</param>
/// <returns>成功返回字体句柄，失败返回NULL</returns>
HFONT EzFont(PCWSTR pszFontName, int iPoint = 9, int iWeight = 400, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);

#define ESTL_EZDLG_NAMESPACE_BEGIN namespace EzDlg {
#define ESTL_EZDLG_NAMESPACE_END }

ESTL_EZDLG_NAMESPACE_BEGIN
/// <summary>
/// 设置窗口字体。
/// 函数枚举窗口的所有子窗口并悉数设置字体
/// </summary>
/// <param name="hWnd">窗口句柄</param>
/// <param name="hFont">字体句柄</param>
/// <param name="bRedraw">是否重画</param>
eStlInline void SetFontForWndAndCtrl(HWND hWnd, HFONT hFont, BOOL bRedraw = FALSE)
{
	EnumChildWindows(hWnd,
		[](HWND hWnd, LPARAM lParam)->BOOL
		{
			SendMessageW(hWnd, WM_SETFONT, lParam, FALSE);
			return TRUE;
		}, (LPARAM)hFont);
	if (bRedraw)
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_UPDATENOW);
}

/// <summary>
/// 模态对话框预处理。
/// 此函数供模拟模态对话框使用。
/// 禁用父窗口
/// </summary>
/// <param name="hParent">父窗口</param>
/// <returns>返回父窗口在调用函数前是否启用，调用DlgEndModel时传递此值</returns>
eStlInline BOOL DlgPreModel(HWND hParent)
{
	BOOL bEnabled = IsWindowEnabled(hParent);
	if (bEnabled)
		EnableWindow(hParent, FALSE);
	return bEnabled;
}

/// <summary>
/// 模态对话框结束。
/// 此函数供模拟模态对话框使用，而不应直接使用DestroyWindow。
/// 启用父窗口并使其获得焦点。注意：设置父窗口焦点是必要的，否则其他窗口将被设置焦点从而导致错乱
/// </summary>
/// <param name="hWnd">对话框窗口</param>
/// <param name="hParent">父窗口</param>
/// <param name="bParentShouldBeEnabled">DlgPreModel的返回值</param>
eStlInline void DlgEndModel(HWND hWnd, HWND hParent, BOOL bParentShouldBeEnabled)
{
	if (bParentShouldBeEnabled)
		EnableWindow(hParent, TRUE);
	SetFocus(hParent);
	DestroyWindow(hWnd);
}

/// <summary>
/// 模态对话框将被销毁。
/// 此函数供模拟模态对话框使用。
/// 主要为了防止一些意外情况，使未通过DlgEndModel销毁的对话框的父窗口也能被解禁
/// </summary>
/// <param name="hWnd">对话框窗口</param>
/// <param name="hParent">父窗口</param>
/// <param name="bParentShouldBeEnabled">DlgPreModel的返回值</param>
/// <returns>对话框未通过DlgEndModel销毁时返回TRUE，否则返回FALSE</returns>
eStlInline BOOL DlgModelOnDestroy(HWND hWnd, HWND hParent, BOOL bParentShouldBeEnabled)
{
	if (bParentShouldBeEnabled && !IsWindowEnabled(hParent))// 防止一些意外情况。。
	{
		EnableWindow(hParent, TRUE);
		return TRUE;
	}
	else
		return FALSE;
}

// IDE对话框上下文基础数据，所有上下文必须由此派生
struct EDLGCTX_BASE
{
	HWND hDlg;
	HWND hParent;
	BOOL bParentEnabled;
	HFONT hFont;
	BOOL bOK;
};

/// <summary>
/// 准备显示易IDE对话框。
/// 函数注册窗口类并为上下文结构分配内存。
/// 模板参数：上下文结构类型
/// </summary>
/// <param name="pAtom">类原子静态变量指针</param>
/// <param name="pszWndClass">窗口类名</param>
/// <param name="pfnWndProc">窗口过程</param>
/// <returns>返回上下文指针</returns>
template<class T>
T* EIDEDlgPreShow(ATOM* pAtom, PCWSTR pszWndClass, WNDPROC pfnWndProc)
{
	if (!*pAtom)
	{
		WNDCLASSW wc{};
		wc.lpszClassName = pszWndClass;
		wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wc.hIcon = (HICON)GetClassLongPtrW((HWND)NotifySys(NES_GET_MAIN_HWND, 0, 0), GCLP_HICON);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.hInstance = g_elibstl_hModule;
		wc.lpfnWndProc = pfnWndProc;
		wc.cbWndExtra = sizeof(void*);
		*pAtom = RegisterClassW(&wc);
	}

	auto pCtx = new T;
	ZeroMemory(pCtx, sizeof(T));
	return pCtx;
}

/// <summary>
/// 显示易IDE对话框。
/// 函数禁用IDE主窗口，然后创建窗口并启动模态消息循环。
/// 注意：消息循环调用IsDialogMessageW以支持导航键，
/// 它会向窗口发送DM_GETDEFID和DM_SETDEFID，
/// 分别定义为WM_USER和WM_USER+1，
/// 应避免使用这两个值来定义自定义消息。
/// </summary>
/// <param name="pszWndClass">窗口类</param>
/// <param name="pszCaption">标题</param>
/// <param name="x">x，若为CW_USEDEFAULT则显示在IDE窗口中央</param>
/// <param name="y">y</param>
/// <param name="cx">宽度</param>
/// <param name="cy">高度</param>
/// <param name="dwStyle">窗口样式，若为0则使用WS_OVERLAPPEDWINDOW | WS_VISIBLE</param>
/// <param name="pCtx">上下文</param>
void EIDEDlgShow(PCWSTR pszWndClass, PCWSTR pszCaption, int x, int y, int cx, int cy, 
	DWORD dwStyle, EDLGCTX_BASE* pCtx, HWND hParent = NULL);

eStlInline void EIDEDlgEnd(EDLGCTX_BASE* pCtx)
{
	EzDlg::DlgEndModel(pCtx->hDlg, pCtx->hParent, pCtx->bParentEnabled);
}

eStlInline void EIDEDlgOnDestroy(EDLGCTX_BASE* pCtx)
{
	DeleteObject(pCtx->hFont);
	pCtx->hFont = NULL;
	EzDlg::DlgModelOnDestroy(pCtx->hDlg, pCtx->hParent, pCtx->bParentEnabled);
}

LRESULT CALLBACK SubclassProc_TabRepair(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

#define SCID_TABREPAIR 20230524'02u
/// <summary>
/// Tab键焦点移动修复
/// </summary>
/// <param name="hWnd">控件句柄</param>
/// <returns>成功返回TRUE</returns>
eStlInline BOOL TabRepairInstall(HWND hWnd)
{
	return SetWindowSubclass(hWnd, SubclassProc_TabRepair, SCID_TABREPAIR, 0);
}

/// <summary>
/// 取消Tab键焦点移动修复
/// </summary>
/// <param name="hWnd">控件句柄</param>
/// <returns>成功返回TRUE</returns>
eStlInline BOOL TabRepairUnInstall(HWND hWnd)
{
	return RemoveWindowSubclass(hWnd, SubclassProc_TabRepair, SCID_TABREPAIR);
}
#undef SCID_TABREPAIR
ESTL_EZDLG_NAMESPACE_END

/// <summary>
/// 发送通用事件。
/// 向易语言通知控件通用事件的产生
/// </summary>
bool SendToParentsHwnd(DWORD m_dwWinFormID, DWORD m_dwUnitID, INT uMsg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// 克隆Unicode字符串。
/// 内存分配释放由new/delete[]进行
/// </summary>
/// <param name="pszDst">目标字符串，如果不为NULL则函数会将其释放</param>
/// <param name="pszSrc">源字符串</param>
/// <param name="cchSrc">字符数</param>
/// <returns>复制的字符数</returns>
int DupStringForNewDeleteW(PWSTR& pszDst, PCWSTR pszSrc, int cchSrc = -1);

/// <summary>
/// 克隆ANSI字符串。
/// 内存分配释放由new/delete[]进行
/// </summary>
/// <param name="pszDst">目标字符串，如果不为NULL则函数会将其释放</param>
/// <param name="pszSrc">源字符串</param>
/// <param name="cchSrc">字符数</param>
/// <returns>复制的字符数</returns>
int DupStringForNewDeleteA(PSTR& pszDst, PCSTR pszSrc, int cchSrc = -1);

SIZE_T DupStreamForNewDelete(BYTE*& pDst, PCBYTE pSrc, SIZE_T cbSrc);

/// <summary>
/// 取默认字体
/// </summary>
/// <param name="hWnd">控件窗口句柄</param>
/// <returns>默认字体LOGFONTA结构</returns>
eStlInline LOGFONTA GetEDefLOGFONT(HWND hWnd)
{
	LOGFONTA lf{};
	HDC hDC = GetDC(hWnd);
	lf.lfHeight = -MulDiv(9, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	lf.lfWeight = 400;// 权重设默认，不然选字体的时候可能会直接转移到细体上
	strcpy(lf.lfFaceName, "宋体");
	lf.lfCharSet = GB2312_CHARSET;
	ReleaseDC(hWnd, hDC);
	return lf;
}
 
/// <summary>
/// 输入框
/// </summary>
/// <param name="ppszInput">接收输入内容指针，需使用delete[]释放</param>
/// <param name="pszInitContent">编辑框初始内容</param>
/// <param name="pszCaption">标题</param>
/// <returns>成功返回TRUE，失败返回FALSE</returns>
BOOL IntputBox(PWSTR* ppszInput, PCWSTR pszInitContent = NULL, PCWSTR pszCaption = L"请输入文本：");

BOOL ImageListSelectDlg(HIMAGELIST hImageList, int idxInit, int* pidxSel, HWND hParent = NULL);

/// <summary>
/// 控件实用类：子类化管理器
/// </summary>
/// <typeparam name="TC">控件类，必须实现GetHWND()方法，返回控件窗口句柄</typeparam>
template<class TC>
class CSubclassMgr
{
private:
	using TCtrlInfo = std::unordered_map<HWND, TC*>;
	using TParentInfo = std::unordered_map<HWND, int>;

	TParentInfo& m_ParentInfo;
	TCtrlInfo& m_CtrlInfo;
	SUBCLASSPROC m_pfnParentSubclass;
	SUBCLASSPROC m_pfnCtrlSubclass;
	UINT_PTR m_uIDParent;
	UINT_PTR m_uIDCtrl;
public:
	CSubclassMgr() = delete;

	/// <summary>
	/// 构造
	/// </summary>
	/// <param name="ParentInfo">父窗口引用计数哈希表</param>
	/// <param name="CtrlInfo">控件到控件类哈希表</param>
	/// <param name="pfnParentSubclass">父窗口子类化过程</param>
	/// <param name="pfnCtrlSubclass">控件子类化过程</param>
	/// <param name="uIDParent">父窗口子类化ID</param>
	/// <param name="uIDCtrl">控件子类化ID</param>
	CSubclassMgr(TParentInfo& ParentInfo, TCtrlInfo& CtrlInfo,
		SUBCLASSPROC pfnParentSubclass, SUBCLASSPROC pfnCtrlSubclass, UINT_PTR uIDParent, UINT_PTR uIDCtrl) :
		m_ParentInfo(ParentInfo), m_CtrlInfo(CtrlInfo),
		m_pfnParentSubclass(pfnParentSubclass), m_pfnCtrlSubclass(pfnCtrlSubclass), m_uIDParent(uIDParent), m_uIDCtrl(uIDCtrl) {}

	~CSubclassMgr() = default;

	/// <summary>
	/// 控件已创建
	/// </summary>
	/// <param name="pClass">控件类</param>
	eStlInline void OnCtrlCreate(TC* pClass)
	{
		OnCtrlCreate2(pClass);
		SetWindowSubclass(pClass->GetHWND(), m_pfnCtrlSubclass, m_uIDCtrl, (DWORD_PTR)pClass);
	}

	/// <summary>
	/// 控件已创建。
	/// 此方法不对控件进行子类化，可用于非标准控件
	/// </summary>
	/// <param name="pClass">控件类</param>
	void OnCtrlCreate2(TC* pClass)
	{
		HWND hWnd = pClass->GetHWND();
		HWND hParent = GetParent(hWnd);
		m_CtrlInfo[hWnd] = pClass;

		if (!m_ParentInfo.count(hParent))
		{
			SetWindowSubclass(hParent, m_pfnParentSubclass, m_uIDParent, 0);
			m_ParentInfo[hParent] = 1;
		}
		else
			m_ParentInfo[hParent]++;
	}

	/// <summary>
	/// 控件的父窗口已被改变。
	/// 原先的父窗口引用不能去掉，因为WM_NOTIFY总是发给创建时的父窗口，WM_COMMAND总是发给直接父窗口
	/// </summary>
	/// <param name="pClass">控件类</param>
	void OnParentChanged(TC* pClass)
	{
		HWND hParent = GetParent(pClass->GetHWND());
		if (!m_ParentInfo.count(hParent))
		{
			SetWindowSubclass(hParent, m_pfnParentSubclass, m_uIDParent, 0);
			m_ParentInfo[hParent] = 1;
		}
		else
			m_ParentInfo[hParent]++;
	}

	/// <summary>
	/// 控件将被销毁
	/// </summary>
	/// <param name="pClass">控件类</param>
	void OnCtrlDestroy(TC* pClass)
	{
		HWND hWnd = pClass->GetHWND();
		HWND hParent = GetParent(hWnd);

		if (m_ParentInfo.count(hParent))
		{
			auto& v = m_ParentInfo[hParent];
			v--;
			if (v <= 0)
			{
				RemoveWindowSubclass(hParent, m_pfnParentSubclass, m_uIDParent);
				m_ParentInfo.erase(hParent);
			}
		}

		HWND hParent2 = pClass->GetHParent();
		if (hParent != hParent2)
			if (m_ParentInfo.count(hParent2))
			{
				auto& v = m_ParentInfo[hParent2];
				v--;
				if (v <= 0)
				{
					RemoveWindowSubclass(hParent2, m_pfnParentSubclass, m_uIDParent);
					m_ParentInfo.erase(hParent2);
				}
			}

		if (m_CtrlInfo.count(hWnd))
			m_CtrlInfo.erase(hWnd);
	}

	/// <summary>
	/// 父窗口将被销毁
	/// </summary>
	/// <param name="hParent"></param>
	void OnParentDestroy(HWND hParent)
	{
		RemoveWindowSubclass(hParent, m_pfnParentSubclass, m_uIDParent);
		if (m_ParentInfo.count(hParent))
			m_ParentInfo.erase(hParent);
	}
};

/// <summary>
/// 控件实用类：子类化管理器。
/// 本类不执行父窗口子类化操作
/// </summary>
/// <typeparam name="TC">控件类，必须实现GetHWND()方法，返回控件窗口句柄</typeparam>
template<class TC>
class CSubclassMgrSimple
{
private:
	using TCtrlInfo = std::unordered_map<HWND, TC*>;

	TCtrlInfo& m_CtrlInfo;
	SUBCLASSPROC m_pfnCtrlSubclass;
	UINT_PTR m_uIDCtrl;
public:
	CSubclassMgrSimple() = delete;
	/// <summary>
	/// 构造
	/// </summary>
	/// <param name="CtrlInfo">控件到控件类哈希表</param>
	/// <param name="pfnCtrlSubclass">控件子类化过程</param>
	/// <param name="uIDCtrl">控件子类化ID</param>
	CSubclassMgrSimple(TCtrlInfo& CtrlInfo, SUBCLASSPROC pfnCtrlSubclass, UINT_PTR uIDCtrl) :
		m_CtrlInfo(CtrlInfo), m_pfnCtrlSubclass(pfnCtrlSubclass), m_uIDCtrl(uIDCtrl) {}

	~CSubclassMgrSimple() = default;

	/// <summary>
	/// 控件已创建
	/// </summary>
	/// <param name="pClass">控件类</param>
	eStlInline void OnCtrlCreate(TC* pClass)
	{
		OnCtrlCreate2(pClass);
		SetWindowSubclass(pClass->GetHWND(), m_pfnCtrlSubclass, m_uIDCtrl, (DWORD_PTR)pClass);
	}

	/// <summary>
	/// 控件已创建。
	/// 此方法不对控件进行子类化，可用于非标准控件
	/// </summary>
	/// <param name="pClass">控件类</param>
	eStlInline void OnCtrlCreate2(TC* pClass)
	{
		HWND hWnd = pClass->GetHWND();
		m_CtrlInfo[hWnd] = pClass;
	}

	/// <summary>
	/// 控件将被销毁
	/// </summary>
	/// <param name="pClass">控件类</param>
	eStlInline void OnCtrlDestroy(TC* pClass)
	{
		HWND hWnd = pClass->GetHWND();
		if (m_CtrlInfo.count(hWnd))
			m_CtrlInfo.erase(hWnd);
	}
};

eStlInline DWORD ModifyWindowStyle(HWND hWnd, DWORD dwNew, DWORD dwMask = 0u, int idx = GWL_STYLE, BOOL bAutoMaskNew = FALSE)
{
	if (bAutoMaskNew)
		dwMask |= dwNew;
	DWORD dwStyle = GetWindowLongPtrW(hWnd, idx);
	dwStyle &= ~dwMask;
	dwStyle |= dwNew;
	SetWindowLongPtrW(hWnd, idx, dwStyle);
	return dwStyle;
}

eStlInline int ESTLPRIV_MultiSelectWndStyle___(HWND hWnd, int idx, int cStyle, ...)
{
	va_list Args;
	va_start(Args, cStyle);
	for (int i = 0; i < cStyle; ++i)
	{
		if (IsBitExist(GetWindowLongPtrW(hWnd, idx), va_arg_idx(Args, i, DWORD)))
		{
			va_end(Args);
			return i;
		}
	}
	va_end(Args);
	return -1;
}
#define MultiSelectWndStyle(hWnd, ...) elibstl::ESTLPRIV_MultiSelectWndStyle___(hWnd, GWL_STYLE, ESTLVAL(__VA_ARGS__))
#define MultiSelectWndExStyle(hWnd, ...) elibstl::ESTLPRIV_MultiSelectWndStyle___(hWnd, GWL_EXSTYLE, ESTLVAL(__VA_ARGS__))

template<class T>
eStlInline int ESTLPRIV_MultiSelectEqual___(T ii, int cItem, ...)
{
	va_list Args;
	va_start(Args, cItem);
	for (int i = 0; i < cItem; ++i)
	{
		if (ii == va_arg_idx(Args, i, T))
		{
			va_end(Args);
			return i;
		}
	}
	va_end(Args);
	return -1;
}
#define MultiSelectEqual(i, ...) elibstl::ESTLPRIV_MultiSelectEqual___(i, ESTLVAL(__VA_ARGS__))

void SetFrameType(HWND hWnd, int iFrame);
int GetFrameType(HWND hWnd);

/// <summary>
/// 字节流到位图句柄。
/// NAS_GET_HBITMAP有点问题，半透明像素都有色差，也没去细研究。。。。不知道吴涛在原版控件里是怎么写的
/// </summary>
/// <param name="pData">字节流</param>
/// <param name="cbPic">长度</param>
/// <returns>成功返回位图句柄，失败返回NULL</returns>
HBITMAP make_hbm_gp(BYTE* pData, SIZE_T cbPic);

#define ESTL_CLRPICKER_NAMESPACE_BEGIN namespace ClrPicker {
#define ESTL_CLRPICKER_NAMESPACE_END }

ESTL_CLRPICKER_NAMESPACE_BEGIN
HWND Create(int x, int y, int cx, int cy, DWORD dwStyle, DWORD dwExStyle, UINT uID, HWND hParent, UINT uNotifyMsg);
eStlInline void SelColor(HWND hWnd, int idx)
{
	SendMessageW(hWnd, CB_SETCURSEL, idx, 0);
}
COLORREF GetColor(HWND hWnd);
BOOL SetColor(HWND hWnd, COLORREF cr);
ESTL_CLRPICKER_NAMESPACE_END

class CCtrlWnd
{
protected:
	HWND m_hWnd = NULL;
	HWND m_hParent = NULL;
	BOOL m_bParentChanged = FALSE;

public:
	CCtrlWnd() = default;
	virtual ~CCtrlWnd() {}

	/// <summary>
	/// 重画
	/// </summary>
	eStlInline void Redraw()
	{
		InvalidateRect(m_hWnd, NULL, TRUE);
		UpdateWindow(m_hWnd);
	}

	/// <summary>
	/// 强制重新核算非客户区
	/// </summary>
	eStlInline void FrameChanged()
	{
		SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	}

	/// <summary>
	/// 取窗口句柄
	/// </summary>
	/// <returns>窗口句柄</returns>
	eStlInline HWND GetHWND() const
	{
		return m_hWnd;
	}

	/// <summary>
	/// 取首次创建父窗口
	/// </summary>
	eStlInline HWND GetHParent() const
	{
		return m_hParent;
	}

	eStlInline void SetRedraw(BOOL bRedraw)
	{
		SendMessageW(m_hWnd, WM_SETREDRAW, bRedraw, 0);
	}
};

// 控件基础数据
/*
* 版本1数据布局：
* ECTRLINFO结构
* 图片
* 文本
*/
#define DATA_VER_BASE_1	1
struct ECTRLINFO
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	LOGFONTA Font;			// 字体
	int cchText;			// 文本长度，仅用于保存信息
	SIZE_T cbPic;			// 图片字节流长度
	int iFrame;				// 边框
};
// 控件基类
// 请勿直接实例化此类
class CCtrlBase :public CCtrlWnd
{
protected:
	// 易系统相关
	DWORD m_dwWinFormID = 0;
	DWORD m_dwUnitID = 0;
	BOOL m_bInDesignMode = FALSE;
	UINT m_uID = 0;

	BOOL m_bGpDecodePicInDesignMode = FALSE;// 设计模式下是否用GDI+解码图片

	HBITMAP m_hbmPic = NULL;// 位图句柄
	HFONT m_hFont = NULL;// 字体句柄
	ECTRLINFO m_Info0{};// 信息

	PSTR m_pszTextA = NULL;// 标题A
	PWSTR m_pszTextW = NULL;// 标题W
	void* m_pPicData = NULL;// 图片数据

	SIZE_T InitBase0(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID, UINT uID, HWND hParent);

	void InitBase0(PCVOID pAllData);
public:
	CCtrlBase() = default;
	~CCtrlBase()
	{
		DeleteObject(m_hFont);
		DeleteObject(m_hbmPic);
		delete[] m_pszTextA;
		delete[] m_pszTextW;
		delete[] m_pPicData;
	}

	/// <summary>
	/// 置标题A
	/// </summary>
	/// <param name="pszText">文本指针</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetTextA(PCSTR pszText)
	{
		if (m_bInDesignMode)
		{
			DupStringForNewDeleteA(m_pszTextA, pszText);
			delete[] m_pszTextW;
			if (pszText)
				m_pszTextW = A2W(pszText);
			else
				m_pszTextW = NULL;
		}
		return SetWindowTextA(m_hWnd, pszText);
	}

	/// <summary>
	/// 置标题W
	/// </summary>
	/// <param name="pszText">文本指针</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetTextW(PCWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			DupStringForNewDeleteW(m_pszTextW, pszText);
			delete[] m_pszTextA;
			if (pszText)
				m_pszTextA = W2A(pszText);
			else
				m_pszTextA = NULL;
		}
		return SetWindowTextW(m_hWnd, pszText);
	}

	/// <summary>
	/// 置标题W。
	/// 此函数不复制字符串
	/// </summary>
	/// <param name="pszText">文本指针，此指针在函数调用结束后归控件对象所有</param>
	/// <returns>成功返回TRUE，失败返回FALSE</returns>
	eStlInline BOOL SetTextNoCopyW(PWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			delete[] m_pszTextW;
			m_pszTextW = pszText;
			delete[] m_pszTextA;
			if (pszText)
				m_pszTextA = W2A(pszText);
			else
				m_pszTextA = NULL;
		}
		return SetWindowTextW(m_hWnd, pszText);
	}

	/// <summary>
	/// 取文本W。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <returns>文本指针</returns>
	PWSTR GetTextW(SIZE_T* pcb = NULL);

	/// <summary>
	/// 取文本A。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <returns>文本指针</returns>
	eStlInline PCSTR GetTextA()
	{
		if (!m_bInDesignMode)
		{
			int cch = GetWindowTextLengthA(m_hWnd);
			if (cch)
			{
				delete[] m_pszTextA;
				m_pszTextA = new CHAR[cch + 1];
				GetWindowTextA(m_hWnd, m_pszTextA, cch + 1);
			}
		}

		return m_pszTextA;
	}

	/// <summary>
	/// 置图片
	/// </summary>
	/// <param name="pPic">图片数据</param>
	/// <param name="cbSize">图片数据长度</param>
	void SetPic(void* pPic, int cbSize);

	/// <summary>
	/// 取图片。
	/// 返回的文本为对象内部所有，不可释放
	/// </summary>
	/// <param name="pcb">指向接收图片数据长度变量的指针</param>
	/// <returns>图片数据指针</returns>
	BYTE* GetPic(int* pcb);

	/// <summary>
	/// 置字体
	/// </summary>
	/// <param name="plf">LOGFONTA指针</param>
	eStlInline void SetFont(LOGFONTA* plf)
	{
		if (m_hFont)
			DeleteObject(m_hFont);

		m_Info0.Font = *plf;
		m_hFont = CreateFontIndirectA(plf);
		SendMessageW(m_hWnd, WM_SETFONT, (WPARAM)m_hFont, TRUE);
	}

	/// <summary>
	/// 取字体
	/// </summary>
	/// <returns>LOGFONTA指针，为迎合易语言回调参数类型而设为BYTE*，不要释放。</returns>
	eStlInline BYTE* GetFont()
	{
		if (!m_bInDesignMode)
		{
			HFONT hFont = (HFONT)SendMessageW(m_hWnd, WM_GETFONT, 0, 0);
			GetObjectA(hFont, sizeof(m_Info0.Font), &m_Info0.Font);
		}
		return (BYTE*)&m_Info0.Font;
	}

	/// <summary>
	/// 置边框
	/// </summary>
	/// <param name="iFrame">边框</param>
	eStlInline void SetFrame(int iFrame)
	{
		m_Info0.iFrame = iFrame;
		SetFrameType(m_hWnd, iFrame);
		FrameChanged();
	}

	/// <summary>
	/// 取边框
	/// </summary>
	/// <returns>边框</returns>
	eStlInline int GetFrame() const
	{
		if (m_bInDesignMode)
			return m_Info0.iFrame;
		else
			return GetFrameType(m_hWnd);
	}

	/// <summary>
	/// 平面化基类数据。
	/// 扩展数据应在其后附加
	/// </summary>
	/// <returns></returns>
	HGLOBAL FlattenInfoBase0(SIZE_T cbExtra = 0u, SIZE_T* pcbBaseData = NULL);

	/// <summary>
	/// 平面化数据。
	/// 用于向易语言返回所有属性。
	/// 内存布局参见文件首部数据版本定义处
	/// </summary>
	/// <returns></returns>
	virtual HGLOBAL FlattenInfo() { assert(FALSE); return NULL; }
};

// 简单控件基础数据
/*
* 版本1数据布局：
* ECTRLINFOSMP结构
*/
#define DATA_VER_BASE_SIMPLE_1	1
struct ECTRLINFOSMP
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int iFrame;				// 边框
};
// 简单控件基类
// 请勿直接实例化此类
class CCtrlBaseSimple :public CCtrlWnd
{
protected:
	// 易系统相关
	DWORD m_dwWinFormID = 0;
	DWORD m_dwUnitID = 0;
	BOOL m_bInDesignMode = FALSE;
	UINT m_uID = 0;

	ECTRLINFOSMP m_Info0{};// 信息

	CCtrlBaseSimple() = default;
	~CCtrlBaseSimple() = default;

	SIZE_T InitBase0(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID, UINT uID, HWND hParent);

	/// <summary>
	/// 平面化基类数据。
	/// 扩展数据应在其后附加
	/// </summary>
	/// <returns></returns>
	HGLOBAL FlattenInfoBase0(SIZE_T cbExtra = 0u, SIZE_T* pcbBaseData = NULL);

	/// <summary>
	/// 置边框
	/// </summary>
	/// <param name="iFrame">边框</param>
	eStlInline void SetFrame(int iFrame)
	{
		m_Info0.iFrame = iFrame;
		SetFrameType(m_hWnd, iFrame);
		FrameChanged();
	}

	/// <summary>
	/// 取边框
	/// </summary>
	/// <returns>边框</returns>
	eStlInline int GetFrame() const
	{
		if (m_bInDesignMode)
			return m_Info0.iFrame;
		else
			return GetFrameType(m_hWnd);
	}

	/// <summary>
	/// 平面化数据。
	/// 用于向易语言返回所有属性。
	/// 内存布局参见文件首部数据版本定义处
	/// </summary>
	/// <returns></returns>
	virtual HGLOBAL FlattenInfo() { assert(FALSE); return NULL; }
};
ESTL_NAMESPACE_END

// 创建控件接口参数定义
#define STD_ECTRL_CREATE_ARGS \
	LPVOID pAllData, int cbData, DWORD dwStyle, int x, int y, int cx, int cy, \
	HWND hParent, UINT nID, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID
// 创建控件接口参数
#define STD_ECTRL_CREATE_REAL_ARGS \
	pAllData, cbData, dwStyle, x, y, cx, cy, \
	hParent, nID, bInDesignMode, dwWinFormID, dwUnitID
// 易语言创建控件接口参数定义，跟上面的略有不同
#define STD_EINTF_CREATE_ARGS \
	LPBYTE pAllData, INT cbData, DWORD dwStyle, HWND hParent, UINT nID, \
	HMENU hMenu, INT x, INT y, INT cx, INT cy, DWORD dwWinFormID, DWORD dwUnitID, HWND hDesignWnd, BOOL bInDesignMode
// 声明子类化管理器所需成员
#define SUBCLASS_MGR_DECL(Class) \
	public: \
		static ::std::unordered_map<HWND, Class*> m_CtrlSCInfo; \
		static ::std::unordered_map<HWND, int> m_ParentSCInfo; \
	private: \
		static ::elibstl::CSubclassMgr<Class> m_SM;
// 初始化子类化管理器所需成员
#define SUBCLASS_MGR_INIT(Class, uIDParent, uIDCtrl) \
	::std::unordered_map<HWND, Class*> Class::m_CtrlSCInfo{}; \
	::std::unordered_map<HWND, int> Class::m_ParentSCInfo{}; \
	::elibstl::CSubclassMgr<Class> Class::m_SM{ m_ParentSCInfo,m_CtrlSCInfo,ParentSubclassProc,CtrlSubclassProc,uIDParent,uIDCtrl };
// 声明简单子类化管理器所需成员
#define SUBCLASS_SMP_MGR_DECL(Class) \
	public: \
		static ::std::unordered_map<HWND, Class*> m_CtrlSCInfo; \
	private: \
		static ::elibstl::CSubclassMgrSimple<Class> m_SM;
// 初始化简单子类化管理器所需成员
#define SUBCLASS_SMP_MGR_INIT(Class, uIDCtrl) \
	::std::unordered_map<HWND, Class*> Class::m_CtrlSCInfo{}; \
	::elibstl::CSubclassMgrSimple<Class> Class::m_SM{ m_CtrlSCInfo,CtrlSubclassProc,uIDCtrl };
// 检查父窗口是否改变，放在WM_SHOWWINDOW下，控件在容器中时，创建参数中的父窗口句柄实际上是顶级窗口句柄，WM_SHOWWINDOW前会被改为容器窗口
#define CHECK_PARENT_CHANGE \
	if (!p->m_bParentChanged) \
		if (GetParent(hWnd) != p->m_hParent) \
		{ \
			m_SM.OnParentChanged(p); \
			p->m_bParentChanged = TRUE; \
		}

#define QuickGetWindowTextW(VarName, hWnd) \
			PWSTR VarName; \
			int ESTLPRIV_cch_##VarName##___ = GetWindowTextLengthW((hWnd)); \
			if (ESTLPRIV_cch_##VarName##___) \
			{ \
				VarName = (PWSTR)_malloca((ESTLPRIV_cch_##VarName##___ + 1)*sizeof(WCHAR)); \
				assert(VarName);/*消除警告*/ \
				GetWindowTextW((hWnd), VarName, ESTLPRIV_cch_##VarName##___ + 1); \
			} \
			else \
				VarName = NULL;

#define QuickGetWindowTextWFree(VarName) _freea(VarName)

#define QuickDupStringW(VarName, pszSrc, cchSrc) \
			PWSTR VarName; \
			if (!pszSrc || !cchSrc) \
			{ \
				VarName = NULL; \
			} \
			else \
			{ \
				int ESTLPRIV_QDS_cch_##VarName##___; \
				if (cchSrc < 0) \
					ESTLPRIV_QDS_cch_##VarName##___ = wcslen(pszSrc); \
				else \
					ESTLPRIV_QDS_cch_##VarName##___ = cchSrc; \
				VarName = (PWSTR)_malloca((cchSrc + 1) * sizeof(WCHAR)); \
				assert(VarName);/*消除警告*/ \
				wcsncpy(VarName, pszSrc, cchSrc); \
				*(VarName + cchSrc) = L'\0'; \
			} \

#define QuickDupStringFree(VarName) _freea(VarName)