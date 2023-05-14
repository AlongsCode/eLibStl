#include "EcontrolHelp.h"

#define WCN_LABELW			L"eLibStl.WndClass.LabelW"

ESTL_NAMESPACE_BEGIN
// 标签
/*
* 版本1数据布局
* ELABELDATA结构
* 底图
*/
#define DATA_VER_LABEL_1	1
struct ELABELDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	SIZE_T cbBKPic;			// 底图大小
	int iBKPicMode;			// 底图模式
	int iAlignH;			// 横向对齐
	int iAlignV;			// 纵向对齐
	BOOL bAutoWrap;			// 自动折行
	COLORREF crText;		// 文本颜色
	COLORREF crTextBK;		// 文本背景颜色
	COLORREF crBK;			// 背景颜色
	int iGradientMode;		// 渐变背景模式
	COLORREF crGradient[3];	// 渐变背景颜色
	int iEllipsisMode;		// 省略号模式
	int iPrefixMode;		// 前缀模式
	BOOL bFullWndPic;		// 底图尽量充满控件
	BOOL bTransparent;		// 透明标签
	int iMousePassingThrough;// 鼠标穿透
};

// 标签
// 为了支持WM_SETTEXT消息，本控件类不使用基类设置标题的方法（SetTextW,SetTextA等）
class CLabel :public elibstl::CCtrlBase
{
	SUBCLASS_SMP_MGR_DECL(CLabel)
private:
	ELABELDATA m_Info{};

	int m_cxClient = 0, m_cyClient = 0;// 客户区大小
	HDC m_hCDC = NULL;// 后台兼容DC
	HDC m_hcdcHelper = NULL;// 画位图使用的辅助DC
	HBITMAP m_hBitmap = NULL;// 后台兼容位图
	HGDIOBJ m_hOld1 = NULL/*后台DC旧位图句柄*/, m_hOld2 = NULL/*辅助DC旧位图句柄*/;

	BYTE* m_pBKPicData = NULL;// 底图数据
	HBITMAP m_hbmBK = NULL;// 底图
	int m_cxBKPic = 0, m_cyBKPic = 0;// 底图大小

	int m_cxPic = 0, m_cyPic = 0;// 图片大小
	RECT m_rcPartPic{};
	RECT m_rcPartText{};

	BOOL m_bAllowRedraw = TRUE;

	static ATOM m_atomLabel;// 标签类原子

	void Paint(HDC hDC)
	{
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;
		//
		// 画背景
		//

		// 画纯色背景
		RECT rc{ 0,0,m_cxClient,m_cyClient };
		if (!m_Info.bTransparent)
			FillRect(hDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
		else
			IntersectClipRect(hDC, 0, 0, m_cxClient, m_cyClient);
		// 类样式带CS_PARENTDC速度会快一点，并且按理来说应该手动剪辑子窗口，但是为什么不剪辑也没事。。。反正这里就这么写了吧，按规定来
		
		// 画渐变背景或底图
		if (m_Info.iGradientMode != 0)
		{
			if (m_Info.iGradientMode <= 4 && m_Info.iGradientMode >= 1)
			{
				TRIVERTEX tv[4];
				COLORREF cr1, cr2, cr3;
				ULONG uMode;
				switch (m_Info.iGradientMode)
				{
				case 1:// 从上到下
				case 2:// 从下到上
					cr2 = m_Info.crGradient[1];
					tv[0].x = 0;
					tv[0].y = 0;
					tv[1].x = m_cxClient;
					tv[1].y = m_cyClient / 2;
					tv[2].x = 0;
					tv[2].y = m_cyClient / 2;
					tv[3].x = m_cxClient;
					tv[3].y = m_cyClient;
					uMode = GRADIENT_FILL_RECT_V;
					if (m_Info.iGradientMode == 1)
					{
						cr1 = m_Info.crGradient[0];
						cr3 = m_Info.crGradient[2];
					}
					else
					{
						cr1 = m_Info.crGradient[2];
						cr3 = m_Info.crGradient[0];
					}
					break;
				case 3:// 从左到右
				case 4:// 从右到左
					cr2 = m_Info.crGradient[1];
					tv[0].x = 0;
					tv[0].y = 0;
					tv[1].x = m_cxClient / 2;
					tv[1].y = m_cyClient;
					tv[2].x = m_cxClient / 2;
					tv[2].y = 0;
					tv[3].x = m_cxClient;
					tv[3].y = m_cyClient;
					uMode = GRADIENT_FILL_RECT_H;
					if (m_Info.iGradientMode == 3)
					{
						cr1 = m_Info.crGradient[0];
						cr3 = m_Info.crGradient[2];
					}
					else
					{
						cr1 = m_Info.crGradient[2];
						cr3 = m_Info.crGradient[0];
					}
					break;
				}

				tv[0].Red = GetRValue(cr1) << 8;
				tv[0].Green = GetGValue(cr1) << 8;
				tv[0].Blue = GetBValue(cr1) << 8;
				tv[0].Alpha = 0xFF << 8;

				tv[1].Red = GetRValue(cr2) << 8;
				tv[1].Green = GetGValue(cr2) << 8;
				tv[1].Blue = GetBValue(cr2) << 8;
				tv[1].Alpha = 0xFF << 8;

				tv[2].Red = tv[1].Red;
				tv[2].Green = tv[1].Green;
				tv[2].Blue = tv[1].Blue;
				tv[2].Alpha = 0xFF << 8;

				tv[3].Red = GetRValue(cr3) << 8;
				tv[3].Green = GetGValue(cr3) << 8;
				tv[3].Blue = GetBValue(cr3) << 8;
				tv[3].Alpha = 0xFF << 8;

				GRADIENT_RECT gr[2];
				gr[0].UpperLeft = 0;
				gr[0].LowerRight = 1;
				gr[1].UpperLeft = 2;
				gr[1].LowerRight = 3;
				GdiGradientFill(hDC, tv, ARRAYSIZE(tv), &gr, ARRAYSIZE(gr), uMode);
			}
			else
			{
				TRIVERTEX tv[4];
				// 左上
				tv[0].x = 0;
				tv[0].y = 0;
				// 左下
				tv[1].x = 0;
				tv[1].y = m_cyClient;
				// 右上
				tv[2].x = m_cxClient;
				tv[2].y = 0;
				// 右下
				tv[3].x = m_cxClient;
				tv[3].y = m_cyClient;
				COLORREF cr1, cr2, cr3;

				GRADIENT_TRIANGLE gt[2];
				switch (m_Info.iGradientMode)
				{
				case 5:// 左上到右下↘
				case 6:// 右下到左上↖
					gt[0].Vertex1 = 0;
					gt[0].Vertex2 = 1;
					gt[0].Vertex3 = 2;
					gt[1].Vertex1 = 3;
					gt[1].Vertex2 = 1;
					gt[1].Vertex3 = 2;
					cr2 = m_Info.crGradient[1];
					if (m_Info.iGradientMode == 5)
					{
						cr1 = m_Info.crGradient[0];
						cr3 = m_Info.crGradient[2];
					}
					else
					{
						cr1 = m_Info.crGradient[2];
						cr3 = m_Info.crGradient[0];
					}

					tv[0].Red = GetRValue(cr1) << 8;
					tv[0].Green = GetGValue(cr1) << 8;
					tv[0].Blue = GetBValue(cr1) << 8;
					tv[0].Alpha = 0xFF << 8;

					tv[1].Red = GetRValue(cr2) << 8;
					tv[1].Green = GetGValue(cr2) << 8;
					tv[1].Blue = GetBValue(cr2) << 8;
					tv[1].Alpha = 0xFF << 8;

					tv[2].Red = tv[1].Red;
					tv[2].Green = tv[1].Green;
					tv[2].Blue = tv[1].Blue;
					tv[2].Alpha = 0xFF << 8;

					tv[3].Red = GetRValue(cr3) << 8;
					tv[3].Green = GetGValue(cr3) << 8;
					tv[3].Blue = GetBValue(cr3) << 8;
					tv[3].Alpha = 0xFF << 8;
					break;
				case 7:// 左下到右上↗
				case 8:// 右上到左下↙
					gt[0].Vertex1 = 1;
					gt[0].Vertex2 = 0;
					gt[0].Vertex3 = 3;
					gt[1].Vertex1 = 2;
					gt[1].Vertex2 = 0;
					gt[1].Vertex3 = 3;
					cr2 = m_Info.crGradient[1];
					if (m_Info.iGradientMode == 7)
					{
						cr1 = m_Info.crGradient[0];
						cr3 = m_Info.crGradient[2];
					}
					else
					{
						cr1 = m_Info.crGradient[2];
						cr3 = m_Info.crGradient[0];
					}

					tv[0].Red = GetRValue(cr2) << 8;
					tv[0].Green = GetGValue(cr2) << 8;
					tv[0].Blue = GetBValue(cr2) << 8;
					tv[0].Alpha = 0xFF << 8;

					tv[1].Red = GetRValue(cr1) << 8;
					tv[1].Green = GetGValue(cr1) << 8;
					tv[1].Blue = GetBValue(cr1) << 8;
					tv[1].Alpha = 0xFF << 8;

					tv[3].Red = tv[0].Red;
					tv[3].Green = tv[0].Green;
					tv[3].Blue = tv[0].Blue;
					tv[3].Alpha = 0xFF << 8;

					tv[2].Red = GetRValue(cr3) << 8;
					tv[2].Green = GetGValue(cr3) << 8;
					tv[2].Blue = GetBValue(cr3) << 8;
					tv[2].Alpha = 0xFF << 8;
					break;
				}

				GdiGradientFill(hDC, tv, ARRAYSIZE(tv), gt, ARRAYSIZE(gt), GRADIENT_FILL_TRIANGLE);
			}
		}
		else if (m_hbmBK)
		{
			SelectObject(m_hcdcHelper, m_hbmBK);
			switch (m_Info.iBKPicMode)
			{
			case 0:// 居左上
				if (m_Info.bFullWndPic)
				{
					if (!m_cyBKPic || !m_cxBKPic)
						break;
					int cxRgn, cyRgn;

					cxRgn = m_cyClient * m_cxBKPic / m_cyBKPic;
					if (cxRgn < m_cxClient)// 先尝试y对齐，看x方向是否充满窗口
					{
						cxRgn = m_cxClient;
						cyRgn = m_cxClient * m_cyBKPic / m_cxBKPic;
					}
					else
						cyRgn = m_cyClient;

					GdiAlphaBlend(hDC, 0, 0, cxRgn, cyRgn, m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				}
				else
					GdiAlphaBlend(hDC, 0, 0, m_cxBKPic, m_cyBKPic, m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				break;
			case 1:// 平铺
				for (int i = 0; i < (m_cxClient - 1) / m_cxBKPic + 1; ++i)
					for (int j = 0; j < (m_cyClient - 1) / m_cyBKPic + 1; ++j)
						GdiAlphaBlend(hDC, i * m_cxBKPic, j * m_cyBKPic, m_cxBKPic, m_cyBKPic,
							m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				break;
			case 2:// 居中
				if (m_Info.bFullWndPic)
				{
					if (!m_cyBKPic || !m_cxBKPic)
						break;
					int cxRgn, cyRgn;
					int x, y;

					cxRgn = m_cyClient * m_cxBKPic / m_cyBKPic;
					if (cxRgn < m_cxClient)// 先尝试y对齐，看x方向是否充满窗口
					{
						cxRgn = m_cxClient;
						cyRgn = m_cxClient * m_cyBKPic / m_cxBKPic;
						x = 0;
						y = (m_cyClient - cyRgn) / 2;
					}
					else
					{
						cyRgn = m_cyClient;
						x = (m_cxClient - cxRgn) / 2;
						y = 0;
					}

					GdiAlphaBlend(hDC, x, y, cxRgn, cyRgn, m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				}
				else
					GdiAlphaBlend(hDC, (m_cxClient - m_cxBKPic) / 2, (m_cyClient - m_cyBKPic) / 2, m_cxBKPic, m_cyBKPic,
						m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				break;
			case 3:// 缩放
				GdiAlphaBlend(hDC, 0, 0, m_cxClient, m_cyClient, m_hcdcHelper, 0, 0, m_cxBKPic, m_cyBKPic, bf);
				break;
			}
		}
		//
		// 画文本
		//
		UINT uDTFlags = DT_NOCLIP |
			(m_Info.bAutoWrap ? DT_WORDBREAK : DT_SINGLELINE) |
			elibstl::MultiSelect<UINT>(m_Info.iEllipsisMode, 0, DT_END_ELLIPSIS, DT_PATH_ELLIPSIS, DT_WORD_ELLIPSIS) |
			elibstl::MultiSelect<UINT>(m_Info.iPrefixMode, 0, DT_NOPREFIX, DT_HIDEPREFIX, DT_PREFIXONLY);

		SelectObject(m_hcdcHelper, m_hbmPic);
		GdiAlphaBlend(hDC, m_rcPartPic.left, m_rcPartPic.top, m_cxPic, m_cyPic, m_hcdcHelper, 0, 0, m_cxPic, m_cyPic, bf);
		rc = m_rcPartText;
		DrawTextW(hDC, m_pszTextW, -1, &rc, uDTFlags);
	}

	void CalcPartsRect()
	{
		RECT rc{ 0,0,m_cxClient-m_cxPic,m_cyClient };
		UINT uDTFlags = DT_NOCLIP | DT_CALCRECT |
			elibstl::MultiSelect<UINT>(m_Info.iEllipsisMode, 0, DT_END_ELLIPSIS, DT_PATH_ELLIPSIS, DT_WORD_ELLIPSIS) |
			elibstl::MultiSelect<UINT>(m_Info.iPrefixMode, 0, DT_NOPREFIX, DT_HIDEPREFIX, DT_PREFIXONLY);
		int xPic, yPic;

		if (m_Info.bAutoWrap)
		{
			uDTFlags |= DT_WORDBREAK;
			DrawTextW(m_hCDC, m_pszTextW, -1, &rc, uDTFlags);

			int cyText = rc.bottom - rc.top;
			switch (m_Info.iAlignV)
			{
			case 0:// 上边
				rc.top = 0;
				rc.bottom = rc.top + cyText;
				yPic = rc.top;
				break;
			case 1:// 中间
				rc.top = (m_cyClient - cyText) / 2;
				rc.bottom = rc.top + cyText;
				yPic = (m_cyClient - m_cyPic) / 2;
				break;
			case 2:// 下边
				rc.bottom = m_cyClient;
				rc.top = rc.bottom - cyText;
				yPic = m_cyClient - m_cyPic;
				break;
			default:
				assert(FALSE);
			}
		}
		else
		{
			uDTFlags |= DT_SINGLELINE;
			DrawTextW(m_hCDC, m_pszTextW, -1, &rc, uDTFlags);

			int cyText = rc.bottom - rc.top;
			switch (m_Info.iAlignV)
			{
			case 0:// 上边
				rc.top = 0;
				rc.bottom = rc.top + cyText;
				yPic = rc.top;
				break;
			case 1:// 中间
				rc.top = (m_cyClient - cyText) / 2;
				rc.bottom = rc.top + cyText;
				yPic = (m_cyClient - m_cyPic) / 2;
				break;
			case 2:// 下边
				rc.bottom = m_cyClient;
				rc.top = rc.bottom - cyText;
				yPic = m_cyClient - m_cyPic;
				break;
			default:
				assert(FALSE);
			}
		}
		uDTFlags &= (~DT_CALCRECT);
		int cxText = rc.right - rc.left;
		int cxTotal = cxText + m_cxPic;
		switch (m_Info.iAlignH)
		{
		case 0:// 左边
			uDTFlags |= DT_LEFT;
			rc.left = m_cxPic;
			rc.right = rc.left + cxText;
			xPic = 0;
			break;
		case 1:// 中间
			rc.left = (m_cxClient - cxTotal) / 2 + m_cxPic;
			rc.right = rc.left + cxText;
			xPic = rc.left - m_cxPic;
			break;
		case 2:// 右边
			uDTFlags |= DT_RIGHT;
			rc.right = m_cxClient - m_cxPic;
			rc.left = rc.right - cxText;
			xPic = rc.right;
			break;
		default:
			assert(FALSE);
		}

		m_rcPartPic.left = xPic;
		m_rcPartPic.top = yPic;
		m_rcPartPic.right = m_rcPartPic.left + m_cxPic;
		m_rcPartPic.bottom = m_rcPartPic.top + m_cyPic;

		m_rcPartText = rc;
	}

	void SetDCAttr(HDC hDC)
	{
		SaveDC(hDC);
		///////////
		SelectObject(hDC, m_hFont);
		///////////
		SetTextColor(hDC, m_Info.crText);
		///////////
		if (m_Info.crBK == CLR_DEFAULT)
			m_Info.crBK = GetSysColor(COLOR_BTNFACE);
		SetDCBrushColor(hDC, m_Info.crBK);
		///////////
		if (m_Info.crTextBK == CLR_DEFAULT)
			SetBkMode(hDC, TRANSPARENT);
		else
		{
			SetBkMode(hDC, OPAQUE);
			SetBkColor(hDC, m_Info.crTextBK);
		}
	}

	// 未用
	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) { return 0; }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto p = (CLabel*)GetWindowLongPtrW(hWnd, 0);

		switch (uMsg)
		{
		case WM_NCHITTEST:
		{
			if (p->m_Info.bTransparent)
				switch (p->m_Info.iMousePassingThrough)
				{
				case 0:// 无
					break;
				case 1:// 穿透空白区域
				{
					POINT pt{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
					ScreenToClient(hWnd, &pt);
					if (!PtInRect(&p->m_rcPartPic, pt) && !PtInRect(&p->m_rcPartText, pt))
						return HTTRANSPARENT;
				}
				break;
				case 2:// 穿透整个控件
					return HTTRANSPARENT;
				}
		}
		break;

		case WM_WINDOWPOSCHANGED:
		{
			LRESULT lResult = DefWindowProcW(hWnd, uMsg, wParam, lParam);
			if (p->m_Info.bTransparent)
				p->RedrawLabel();
			return lResult;
		}

		case WM_SIZE:
		{
			p->m_cxClient = LOWORD(lParam);
			p->m_cyClient = HIWORD(lParam);
			SelectObject(p->m_hCDC, p->m_hOld1);
			DeleteObject(p->m_hBitmap);
			HDC hDC = GetDC(hWnd);
			p->m_hBitmap = CreateCompatibleBitmap(hDC, p->m_cxClient, p->m_cyClient);
			SelectObject(p->m_hCDC, p->m_hBitmap);
			ReleaseDC(hWnd, hDC);
			p->CalcPartsRect();
			if (!p->m_Info.bTransparent)
				p->RedrawLabel();
		}
		return 0;

		case WM_NCCREATE:
			SetWindowLongPtrW(hWnd, 0, (LONG_PTR)((CREATESTRUCTW*)lParam)->lpCreateParams);
			return TRUE;

		case WM_CREATE:
		{
			HDC hDC = GetDC(hWnd);
			p->m_hCDC = CreateCompatibleDC(hDC);
			p->m_hcdcHelper = CreateCompatibleDC(hDC);
			ReleaseDC(hWnd, hDC);
			p->m_hOld1 = GetCurrentObject(p->m_hCDC, OBJ_BITMAP);
			p->m_hOld2 = GetCurrentObject(p->m_hcdcHelper, OBJ_BITMAP);
			SetDCBrushColor(p->m_hCDC, GetSysColor(COLOR_BTNFACE));
		}
		return 0;

		case WM_DESTROY:
		{
			m_SM.OnCtrlDestroy(p);
			SelectObject(p->m_hCDC, p->m_hOld1);
			SelectObject(p->m_hcdcHelper, p->m_hOld2);
			DeleteDC(p->m_hCDC);
			DeleteDC(p->m_hcdcHelper);
			DeleteObject(p->m_hBitmap);
			delete p;
		}
		return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			if (p->m_Info.bTransparent)
			{
				p->SetDCAttr(ps.hdc);
				p->Paint(ps.hdc);
				RestoreDC(ps.hdc, -1);
			}
			else
			{
				p->Paint(p->m_hCDC);
				BitBlt(ps.hdc,
					ps.rcPaint.left,
					ps.rcPaint.top,
					ps.rcPaint.right - ps.rcPaint.left,
					ps.rcPaint.bottom - ps.rcPaint.top,
					p->m_hCDC,
					ps.rcPaint.left,
					ps.rcPaint.top,
					SRCCOPY);
			}
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_SETFONT:
		{
			SelectObject(p->m_hCDC, (HFONT)wParam);
			p->CalcPartsRect();
			p->RedrawLabel();
		}
		break;

		case WM_SETTEXT:
		{
			LRESULT lResult = DefWindowProcW(hWnd, uMsg, wParam, lParam);
			auto pszText = (PCWSTR)lParam;

			elibstl::DupStringForNewDeleteW(p->m_pszTextW, pszText);
			if (p->m_bInDesignMode)
			{
				delete[] p->m_pszTextA;
				if (pszText)
					p->m_pszTextA = elibstl::W2A(pszText);
				else
					p->m_pszTextA = NULL;
			}

			p->CalcPartsRect();
			p->RedrawLabel();
			return lResult;
		}

		case WM_ERASEBKGND:
			return TRUE;

		case WM_SETREDRAW:
			p->m_bAllowRedraw = wParam;
			break;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
public:
	CLabel() = delete;
	CLabel(STD_ECTRL_CREATE_ARGS)
	{
		if (!m_atomLabel)
		{
			WNDCLASSW wc{};
			wc.cbWndExtra = sizeof(void*);
			wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
			wc.hInstance = g_elibstl_hModule;
			wc.lpfnWndProc = WndProc;
			wc.lpszClassName = WCN_LABELW;
			wc.style = CS_DBLCLKS | CS_PARENTDC;
			m_atomLabel = RegisterClassW(&wc);
			if (!m_atomLabel)
			{
				assert(FALSE);
				return;
			}
		}

		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ELABELDATA));

			p += sizeof(ELABELDATA);
			SetBKPic(p, m_Info.cbBKPic);
		}
		else
		{
			m_Info.iAlignV = 1;
			m_Info.crBK = GetSysColor(COLOR_BTNFACE);
			m_Info.crTextBK = CLR_DEFAULT;
			m_Info.crGradient[0] = 0x808080;
			m_Info.crGradient[1] = 0xFFFFFF;
			m_Info.crGradient[2] = 0x808080;
		}
		m_Info.iVer = DATA_VER_LABEL_1;

		if (!m_pszTextW)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"标签W");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}

		m_hWnd = CreateWindowExW(m_Info.bTransparent ? WS_EX_TRANSPARENT : 0, WCN_LABELW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS,
			x, y, cx, cy, hParent, (HMENU)nID, g_elibstl_hModule, this);
		m_hParent = hParent;
		m_SM.OnCtrlCreate2(this);

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		SetClr(0, m_Info.crText);
		SetClr(1, m_Info.crBK);
		SetClr(2, m_Info.crTextBK);

		InitBase0(pAllData);

		BITMAP bitmap;
		if (m_hbmBK)
		{
			GetObjectW(m_hbmBK, sizeof(bitmap), &bitmap);
			m_cxBKPic = bitmap.bmWidth;
			m_cyBKPic = bitmap.bmHeight;
		}

		if (m_hbmPic)
		{
			GetObjectW(m_hbmPic, sizeof(bitmap), &bitmap);
			m_cxPic = bitmap.bmWidth;
			m_cyPic = bitmap.bmHeight;
		}
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		CalcPartsRect();
		RedrawLabel();
	}

	~CLabel()
	{
		delete[] m_pBKPicData;
		DeleteObject(m_hbmBK);
	}

	void RedrawLabel()
	{
		if (m_Info.bTransparent)
		{
			RECT rc{ 0,0,m_cxClient,m_cyClient };
			HWND hParent = GetParent(m_hWnd);
			MapWindowPoints(m_hWnd, hParent, (POINT*)&rc, 2);
			RedrawWindow(hParent, &rc, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_UPDATENOW);
		}
		else
		{
			InvalidateRect(m_hWnd, NULL, FALSE);
			UpdateWindow(m_hWnd);
		}
	}

	void SetBKPic(BYTE* pPic, SIZE_T cbSize)
	{
		m_Info.cbBKPic = cbSize;
		if (m_hbmBK)
			DeleteObject(m_hbmBK);

		if (cbSize && pPic)
		{
			if (m_bInDesignMode)
			{
				delete[] m_pBKPicData;
				m_pBKPicData = new BYTE[cbSize];
				memcpy(m_pBKPicData, pPic, cbSize);
			}
			m_hbmBK = elibstl::make_hbm_gp((BYTE*)pPic, cbSize);
			BITMAP bitmap;
			GetObjectW(m_hbmBK, sizeof(bitmap), &bitmap);
			m_cxBKPic = bitmap.bmWidth;
			m_cyBKPic = bitmap.bmHeight;
		}
		else
		{
			if (m_bInDesignMode)
			{
				delete[] m_pBKPicData;
				m_pBKPicData = NULL;
			}
			m_hbmBK = NULL;
		}
		RedrawLabel();
	}

	eStlInline BYTE* GetBKPic(int* pcbPic) const
	{
		if (pcbPic)
			*pcbPic = m_Info.cbBKPic;
		return m_pBKPicData;
	}

	eStlInline void SetPicLabel(BYTE* pPic, SIZE_T cbSize)
	{
		SetPic(pPic, cbSize);
		if (m_hbmPic)
		{
			BITMAP bitmap;
			GetObjectW(m_hbmPic, sizeof(bitmap), &bitmap);
			m_cxPic = bitmap.bmWidth;
			m_cyPic = bitmap.bmHeight;
		}
		else
		{
			m_cxPic = 0;
			m_cyPic = 0;
		}
		CalcPartsRect();
		RedrawLabel();
	}

	eStlInline void SetBKPicMode(int iBKPicMode)
	{
		m_Info.iBKPicMode = iBKPicMode;
		RedrawLabel();
	}

	eStlInline int GetBKPicMode() const
	{
		return m_Info.iBKPicMode;
	}

	eStlInline void SetAlign(BOOL bHAlign, int iAlign)
	{
		if (bHAlign)
			m_Info.iAlignH = iAlign;
		else
			m_Info.iAlignV = iAlign;
		CalcPartsRect();
		RedrawLabel();
	}

	eStlInline int GetAlign(BOOL bHAlign) const
	{
		if (bHAlign)
			return m_Info.iAlignH;
		else
			return m_Info.iAlignV;
	}

	eStlInline void SetAutoWrap(BOOL bAutoWrap)
	{
		m_Info.bAutoWrap = bAutoWrap;
		CalcPartsRect();
		RedrawLabel();
	}

	eStlInline BOOL GetAutoWrap() const
	{
		return m_Info.bAutoWrap;
	}

	void SetClr(int idx, COLORREF cr)
	{
		switch (idx)
		{
		case 0:
			m_Info.crText = cr;
			SetTextColor(m_hCDC, cr);
			break;
		case 1:
			m_Info.crBK = cr;
			if (cr == CLR_DEFAULT)
				cr = GetSysColor(COLOR_BTNFACE);
			SetDCBrushColor(m_hCDC, cr);
			break;
		case 2:
			m_Info.crTextBK = cr;
			if (cr == CLR_DEFAULT)
				SetBkMode(m_hCDC, TRANSPARENT);
			else
			{
				SetBkMode(m_hCDC, OPAQUE);
				SetBkColor(m_hCDC, cr);
			}
		}

		RedrawLabel();
	}

	eStlInline COLORREF GetClr(int idx) const
	{
		switch (idx)
		{
		case 0:return m_Info.crText;
		case 1:return m_Info.crBK;
		case 2:return m_Info.crTextBK;
		}
		assert(FALSE);
		return 0;
	}

	eStlInline void SetGradientMode(int iGradientMode)
	{
		m_Info.iGradientMode = iGradientMode;
		RedrawLabel();
	}

	eStlInline int GetGradientMode() const
	{
		return m_Info.iGradientMode;
	}

	eStlInline void SetGradientClr(int idx, COLORREF cr)
	{
		m_Info.crGradient[idx] = cr;
		RedrawLabel();
	}

	eStlInline COLORREF GetGradientClr(int idx) const
	{
		return m_Info.crGradient[idx];
	}

	eStlInline void SetEllipsisMode(int iEllipsisMode)
	{
		m_Info.iEllipsisMode = iEllipsisMode;
		CalcPartsRect();
		RedrawLabel();
	}

	eStlInline int GetEllipsisMode() const
	{
		return m_Info.iEllipsisMode;
	}

	eStlInline void SetPrefixMode(int iPrefixMode)
	{
		m_Info.iPrefixMode = iPrefixMode;
		CalcPartsRect();
		RedrawLabel();
	}

	eStlInline int GetPrefixMode() const
	{
		return m_Info.iPrefixMode;
	}

	eStlInline void SetFullWndPic(BOOL bFullWndPic)
	{
		m_Info.bFullWndPic = bFullWndPic;
		RedrawLabel();
	}

	eStlInline BOOL GetFullWndPic() const
	{
		return m_Info.bFullWndPic;
	}

	eStlInline void SetTransparent(BOOL bTransparent)
	{
		m_Info.bTransparent = bTransparent;
		elibstl::ModifyWindowStyle(m_hWnd, bTransparent ? WS_EX_TRANSPARENT : 0, WS_EX_TRANSPARENT, GWL_EXSTYLE);
		RedrawLabel();
	}

	eStlInline BOOL GetTransparent() const
	{
		return m_Info.bTransparent;
	}

	eStlInline void SetMousePassingThrough(int iMousePassingThrough)
	{
		m_Info.iMousePassingThrough = iMousePassingThrough;
		RedrawLabel();
	}

	eStlInline int GetMousePassingThrough() const
	{
		return m_Info.iMousePassingThrough;
	}

	HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(ELABELDATA) + m_Info.cbBKPic, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ELABELDATA));
		// 底图
		p += sizeof(ELABELDATA);
		memcpy(p, m_pBKPicData, m_Info.cbBKPic);
		// 
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto pButton = new CLabel(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(pButton->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 标题
			SetWindowTextA(p->m_hWnd, pPropertyVaule->m_szText);
			break;
		case 1:// 标题W
			SetWindowTextW(p->m_hWnd, (PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 2:// 图片
			p->SetPicLabel(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// 底图
			p->SetBKPic(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 4:// 底图方式
			p->SetBKPicMode(pPropertyVaule->m_int);
			break;
		case 5:// 字体
			p->SetFont((LOGFONTA*)pPropertyVaule->m_int);
			break;
		case 6:// 横向对齐
			p->SetAlign(TRUE, pPropertyVaule->m_int);
			break;
		case 7:// 纵向对齐
			p->SetAlign(FALSE, pPropertyVaule->m_int);
			break;
		case 8:// 自动折行
			p->SetAutoWrap(pPropertyVaule->m_bool);
			break;
		case 9:// 文本颜色
		case 10:// 背景颜色
		case 11:// 文本背景颜色
			p->SetClr(nPropertyIndex - 9, pPropertyVaule->m_clr);
			break;
		case 12:// 渐变背景方式
			p->SetGradientMode(pPropertyVaule->m_int);
			break;
		case 13:// 渐变背景颜色1
		case 14:// 渐变背景颜色2
		case 15:// 渐变背景颜色3
			p->SetGradientClr(nPropertyIndex - 13, pPropertyVaule->m_clr);
			break;
		case 16:// 省略号方式
			p->SetEllipsisMode(pPropertyVaule->m_bool);
			break;
		case 17:// 前缀字符解释方式
			p->SetPrefixMode(pPropertyVaule->m_int);
			break;
		case 18:// 底图尽量充满窗口
			p->SetFullWndPic(pPropertyVaule->m_bool);
			break;
		case 19:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 20:// 透明标签
			p->SetTransparent(pPropertyVaule->m_bool);
			break;
		case 21:// 透过鼠标
			p->SetMousePassingThrough(pPropertyVaule->m_int);
			break;
		}

		return FALSE;
	}

	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 标题
			pPropertyVaule->m_szText = p->GetTextA();
			break;
		case 1:// 标题W
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 2:// 图片
			pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// 底图
			pPropertyVaule->m_data.m_pData = p->GetBKPic(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 4:// 底图方式
			pPropertyVaule->m_int = p->GetBKPicMode();
			break;
		case 5:// 字体
			pPropertyVaule->m_data.m_pData = p->GetFont();
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
			break;
		case 6:// 横向对齐
			pPropertyVaule->m_int = p->GetAlign(TRUE);
			break;
		case 7:// 纵向对齐
			pPropertyVaule->m_int = p->GetAlign(FALSE);
			break;
		case 8:// 自动折行
			pPropertyVaule->m_bool = p->GetAutoWrap();
			break;
		case 9:// 文本颜色
		case 10:// 背景颜色
		case 11:// 文本背景颜色
			pPropertyVaule->m_clr = p->GetClr(nPropertyIndex - 9);
			break;
		case 12:// 渐变背景方式
			pPropertyVaule->m_int = p->GetGradientMode();
			break;
		case 13:// 渐变背景颜色1
		case 14:// 渐变背景颜色2
		case 15:// 渐变背景颜色3
			pPropertyVaule->m_clr = p->GetGradientClr(nPropertyIndex - 13);
			break;
		case 16:// 省略号方式
			pPropertyVaule->m_int = p->GetEllipsisMode();
			break;
		case 17:// 前缀字符解释方式
			pPropertyVaule->m_int = p->GetPrefixMode();
			break;
		case 18:// 底图尽量充满窗口
			pPropertyVaule->m_bool = p->GetFullWndPic();
			break;
		case 19:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 20:// 透明标签
			pPropertyVaule->m_bool = p->GetTransparent();
			break;
		case 21:// 透过鼠标
			pPropertyVaule->m_int = p->GetMousePassingThrough();
			break;
		}

		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		if (nPropertyIndex == 1)
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				SetWindowTextW(p->m_hWnd, psz);
				delete[] psz;
				*pblModified = TRUE;
			}
		}
		return FALSE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 80;
			*((int*)dwParam2) = 32;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_SMP_MGR_INIT(CLabel, 0)
ATOM CLabel::m_atomLabel = 0;
ESTL_NAMESPACE_END

static UNIT_PROPERTY s_Member_LabelW[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/{ "标题", "Text", "", UD_TEXT, _PROP_OS(__OS_WIN), NULL },
	/*001*/{ "标题W", "TextW", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL },
	/*002*/{ "图片", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*003*/{ "底图", "BKPicture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*004*/		{ "底图方式", "BKPicAlign", "", UD_PICK_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, "居左上\0""平铺\0""居中\0""缩放\0""\0" },
	/*005*/{ "字体", "Font", "", UD_FONT, _PROP_OS(__OS_WIN) , NULL },
	/*006*/{ "横向对齐方式", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""居中\0""右边\0""\0" },
	/*007*/{ "纵向对齐方式", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""居中\0""下边\0""\0" },
	/*008*/{ "是否自动折行", "AutoWrap", "", UD_BOOL, _PROP_OS(__OS_WIN) , NULL },
	/*009*/{ "文本颜色", "TextClr", "", UD_COLOR, _PROP_OS(__OS_WIN) , NULL },
	/*010*/{ "背景颜色", "BKClr", "", UD_COLOR_BACK, _PROP_OS(__OS_WIN) , NULL },
	/*011*/{ "文本背景颜色", "BKClr", "", UD_COLOR_TRANS, _PROP_OS(__OS_WIN) , NULL },
	/*012*/{ "渐变背景方式", "GradientMode", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无\0""从上到下\0""从下到上\0""从左到右\0""从右到左\0""从左上到右下\0""从右下到左上\0""从左下到右上\0""从右上到左下\0""\0" },
	/*013*/		{ "渐变背景颜色1", "GradientClr1", "", UD_COLOR_TRANS, _PROP_OS(__OS_WIN) | UW_HAS_INDENT , NULL },
	/*014*/		{ "渐变背景颜色2", "GradientClr2", "", UD_COLOR_TRANS, _PROP_OS(__OS_WIN) | UW_HAS_INDENT , NULL },
	/*015*/		{ "渐变背景颜色3", "GradientClr3", "", UD_COLOR_TRANS, _PROP_OS(__OS_WIN) | UW_HAS_INDENT , NULL },
	/*016*/{ "省略号方式", "EllipsisMode", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无省略\0""末尾省略\0""中间省略\0""省略单词\0""\0" },
	/*017*/{ "前缀字符解释方式", "PrefixMode", "", UD_PICK_INT, _PROP_OS(__OS_WIN) , "常规\0""不解释前缀\0""隐藏下划线\0""只显示下划线\0""\0" },
	/*018*/{ "底图尽量充满控件", "FullWndPic", "", UD_BOOL, _PROP_OS(__OS_WIN) , NULL },
	/*019*/{ "边框", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*020*/{ "透明标签", "Transparent", "使标签背景透明，达到类似扩展界面支持库一中透明标签的效果。设置本模式后将忽略背景颜色属性，但渐变背景和底图依然有效。注意：频繁更新透明标签会影响程序的性能，若标签还设置了图片，则会有较明显的闪烁，应避免这种情况。", UD_BOOL, _PROP_OS(__OS_WIN) , NULL },
	/*021*/{ "鼠标穿透方式", "MousePassingThroughMode", "", UD_PICK_INT, _PROP_OS(__OS_WIN) , "无\0""穿透空白区域\0""穿透整个控件\0""\0" },
};

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_LabelW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CLabel::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CLabel::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CLabel::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CLabel::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CLabel::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CLabel::ENotify;
	}
	return NULL;
}

ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtLabelW =
{
	"标签W",		//中文名称
	"LabelW",	//英文名称
	"",			//说明
	0,			//命令数量
	0,			//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	IDB_COMLINKBUTTON_W,//资源ID
	0,
	NULL,
	ARRAYSIZE(s_Member_LabelW),
	s_Member_LabelW,
	libstl_GetInterface_LabelW,
	0,			//成员数量
	NULL		//成员数据数组
};
ESTL_NAMESPACE_END