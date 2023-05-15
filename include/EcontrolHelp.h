//组件库需用通用函数引入此头文件
#include "ElibHelp.h"
#include "GdiplusFlatDef.h"
#include <CommCtrl.h>
#include <unordered_map>
#include <Shlwapi.h>
#include <windowsx.h>
/*易定义的标签反馈事件*/
#define WM_EFEEDBACK  32885


ESTL_NAMESPACE_BEGIN

std::vector<unsigned char> GetDataFromHBIT(HBITMAP hBitmap);

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

/// <summary>
/// 发送通用事件。
/// 向易语言通知控件通用事件的产生
/// </summary>
eStlInline bool SendToParentsHwnd(DWORD m_dwWinFormID, DWORD m_dwUnitID, INT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_SETFOCUS || uMsg == WM_KILLFOCUS || uMsg == WM_MOUSELAST || uMsg >= WM_MOUSEMOVE
		&& uMsg <= WM_RBUTTONUP || uMsg >= WM_KEYDOWN && uMsg <= WM_CHAR)
	{
		//这几个事件全部转发给父组件
		EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 0);
		INT control_type = 0;
		if (uMsg != WM_CHAR && uMsg != WM_SETFOCUS && uMsg != WM_KILLFOCUS)
		{
			if ((GetKeyState(VK_CONTROL) & 16384) != 0)
				control_type = 1;
			if ((GetKeyState(VK_SHIFT) & 16384) != 0)
				control_type = control_type | 2;
			if ((GetKeyState(VK_MENU) & 16384) != 0)
				control_type = control_type | 4;
		}

		if (uMsg >= WM_MOUSEMOVE && uMsg <= WM_RBUTTONUP)
		{
			if (uMsg == WM_MOUSEMOVE)
				event.m_nEventIndex = -6;
			else
				event.m_nEventIndex = 512 - uMsg;
			event.m_nArgCount = 3;
			event.m_arg[0].m_inf.m_int = lParam & 65535;
			event.m_arg[1].m_inf.m_int = lParam >> 16;
			event.m_arg[2].m_inf.m_int = control_type;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			return true;
		}

		switch (uMsg)
		{
		case WM_SETFOCUS: {
			event.m_nEventIndex = -uMsg;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}
		case WM_KILLFOCUS: {
			event.m_nEventIndex = -uMsg;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}
		case WM_KEYDOWN: {
			event.m_nEventIndex = (247 - uMsg);
			event.m_nArgCount = 2;
			event.m_arg[0].m_inf.m_int = wParam;
			event.m_arg[1].m_inf.m_int = control_type;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}
		case WM_KEYUP: {
			event.m_nEventIndex = (247 - uMsg);
			event.m_nArgCount = 2;
			event.m_arg[0].m_inf.m_int = wParam;
			event.m_arg[1].m_inf.m_int = control_type;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}
		case WM_CHAR: {
			event.m_nEventIndex = -11;
			event.m_nArgCount = 1;
			event.m_arg[0].m_inf.m_int = wParam;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}case WM_MOUSELAST: {
			event.m_nEventIndex = 12;
			event.m_nArgCount = 2;
			event.m_arg[0].m_inf.m_int = (wParam >> 16) > 0 ? 1 : -1;
			event.m_arg[1].m_inf.m_int = control_type;
			elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
			break;
		}
		default:
			break;
		}
	}

	return true;
}

/// <summary>
/// 克隆Unicode字符串。
/// 内存分配释放由new/delete[]进行
/// </summary>
/// <param name="pszDst">目标字符串，如果不为NULL则函数会将其释放</param>
/// <param name="pszSrc">源字符串</param>
/// <param name="cchSrc">字符数</param>
/// <returns>复制的字符数</returns>
int DupStringForNewDeleteW(PWSTR& pszDst, PCWSTR pszSrc, int cchSrc = 0);

/// <summary>
/// 克隆ANSI字符串。
/// 内存分配释放由new/delete[]进行
/// </summary>
/// <param name="pszDst">目标字符串，如果不为NULL则函数会将其释放</param>
/// <param name="pszSrc">源字符串</param>
/// <param name="cchSrc">字符数</param>
/// <returns>复制的字符数</returns>
int DupStringForNewDeleteA(PSTR& pszDst, PCSTR pszSrc, int cchSrc = 0);

/// <summary>
/// 取默认字体
/// </summary>
/// <param name="hWnd">控件窗口句柄</param>
/// <returns>默认字体LOGFONTA结构</returns>
eStlInline LOGFONTA GetEDefLOGFONT(HWND hWnd)
{
	LOGFONTA lf{};
	HDC hDC = GetDC(hWnd);
	lf.lfHeight = -MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
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

eStlInline BOOL IsBitExist(DWORD dw1, DWORD dw2)
{
	return ((dw1 & dw2) == dw2);
}

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
	int cbPic;				// 图片字节流长度
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

	HBITMAP m_hbmPic = NULL;// 位图句柄
	HFONT m_hFont = NULL;// 字体句柄
	ECTRLINFO m_Info0{};// 信息

	PSTR m_pszTextA = NULL;// 标题A
	PWSTR m_pszTextW = NULL;// 标题W
	void* m_pPicData = NULL;// 图片数据

	SIZE_T InitBase0(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID);

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
			elibstl::DupStringForNewDeleteA(m_pszTextA, pszText);
			delete[] m_pszTextW;
			if (pszText)
				m_pszTextW = elibstl::A2W(pszText);
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
			elibstl::DupStringForNewDeleteW(m_pszTextW, pszText);
			delete[] m_pszTextA;
			if (pszText)
				m_pszTextA = elibstl::W2A(pszText);
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
				m_pszTextA = elibstl::W2A(pszText);
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
	eStlInline PWSTR GetTextW(SIZE_T* pcb = NULL)
	{
		if (!m_bInDesignMode)
		{
			int cch = GetWindowTextLengthW(m_hWnd);
			if (cch)
			{
				delete[] m_pszTextW;
				m_pszTextW = new WCHAR[cch + 1];
				GetWindowTextW(m_hWnd, m_pszTextW, cch + 1);
				if (pcb)
					*pcb = (cch + 1) * sizeof(WCHAR);
			}
			else
				if (pcb)
					*pcb = 0u;

		}
		else
			if (pcb)
			{
				if (!m_pszTextW)
					*pcb = 0u;
				else
					*pcb = (wcslen(m_pszTextW) + 1) * sizeof(WCHAR);
			}



		return m_pszTextW;
	}

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
	eStlInline BYTE* GetPic(int* pcb)
	{
		if (!m_bInDesignMode)
		{
			auto&& x = elibstl::GetDataFromHBIT(m_hbmPic);
			delete[] m_pPicData;
			m_Info0.cbPic = x.size();
			m_pPicData = new BYTE[m_Info0.cbPic];
			memcpy(m_pPicData, x.data(), m_Info0.cbPic);
		}

		*pcb = m_Info0.cbPic;
		return (BYTE*)m_pPicData;
	}

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
		elibstl::SetFrameType(m_hWnd, iFrame);
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
			return elibstl::GetFrameType(m_hWnd);
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

	ECTRLINFOSMP m_Info0{};// 信息

	CCtrlBaseSimple() = default;
	~CCtrlBaseSimple() = default;

	SIZE_T InitBase0(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID);

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
		elibstl::SetFrameType(m_hWnd, iFrame);
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
			return elibstl::GetFrameType(m_hWnd);
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
		static std::unordered_map<HWND, Class*> m_CtrlSCInfo; \
		static std::unordered_map<HWND, int> m_ParentSCInfo; \
	private: \
		static elibstl::CSubclassMgr<Class> m_SM;
// 初始化子类化管理器所需成员
#define SUBCLASS_MGR_INIT(Class, uIDParent, uIDCtrl) \
	std::unordered_map<HWND, Class*> Class::m_CtrlSCInfo{}; \
	std::unordered_map<HWND, int> Class::m_ParentSCInfo{}; \
	elibstl::CSubclassMgr<Class> Class::m_SM{ m_ParentSCInfo,m_CtrlSCInfo,ParentSubclassProc,CtrlSubclassProc,uIDParent,uIDCtrl };
// 声明简单子类化管理器所需成员
#define SUBCLASS_SMP_MGR_DECL(Class) \
	public: \
		static std::unordered_map<HWND, Class*> m_CtrlSCInfo; \
	private: \
		static elibstl::CSubclassMgrSimple<Class> m_SM;
// 初始化简单子类化管理器所需成员
#define SUBCLASS_SMP_MGR_INIT(Class, uIDCtrl) \
	std::unordered_map<HWND, Class*> Class::m_CtrlSCInfo{}; \
	elibstl::CSubclassMgrSimple<Class> Class::m_SM{ m_CtrlSCInfo,CtrlSubclassProc,uIDCtrl };
// 检查父窗口是否改变，放在WM_SHOWWINDOW下，控件在容器中时，创建参数中的父窗口句柄实际上是顶级窗口句柄，WM_SHOWWINDOW前会被改为容器窗口
#define CHECK_PARENT_CHANGE \
	if (!p->m_bParentChanged) \
		if (GetParent(hWnd) != p->m_hParent) \
		{ \
			m_SM.OnParentChanged(p); \
			p->m_bParentChanged = TRUE; \
		}