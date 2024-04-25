#include "EcontrolHelp.h"
#include<Richedit.h>
#pragma comment (lib,"Crypt32.lib")



#define SCID_RICHEDIT		20230527'01u
#define SCID_RICHEDITPARENT	20230527'02u
#define DATA_VER_RICHEDIT_1	1
struct ERICHEDITDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留



	int m_nContentType;				//内容格式
	COLORREF m_clrBackColor;			// 编辑框背景色
	BOOL m_blMutiLine;		// 是否允许多行
	BOOL m_blAutoNextLine;			// 自动换行
	BOOL m_blReadOnly;			//是否只读
	BOOL m_blHideSelection;          //隐藏选择
	BOOL iScrollBar;		// 滚动条
	BOOL bAutoDetectURL;	// 自动检测链接
	INT RevocationTimes;    //撤销次数
	INT iMaxLen;			// 最大允许长度
	INT iSelPos;			// 起始选择位置
	INT iSelNum;			// 被选择字符数

	//wchar_t hMem[0];			// 内容,全局变量
};
ESTL_NAMESPACE_BEGIN


class CRichEdit :public CCtrlBase
{
	SUBCLASS_MGR_DECL(CRichEdit)
public:
	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CRichEdit(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}
	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0://内容格式
			if (pPropertyVaule->m_int < 0 || pPropertyVaule->m_int>1)
			{
				TaskDialog(GetActiveWindow(), NULL, L"警告", L"不看参数解释，你带脑子了吗？", L"你是傻逼吗？", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
				return FALSE;
			}
			p->m_Info.m_nContentType = pPropertyVaule->m_int;
			break;
		case 1:// 内容
			p->SetContent((PCWSTR)pPropertyVaule->m_data.m_pData, false);
			break;
		case 2:
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 3:// 编辑框背景颜色
			p->SetCorlor(pPropertyVaule->m_clr);
			break;
		case 4:// 是否允许多行
			p->SetMultiLine(pPropertyVaule->m_bool);
			return TRUE;
		case 5:// 自动换行
			p->SetAutoWrap(pPropertyVaule->m_bool);
			return TRUE;
		case 6://只读
			p->SetOnlyRead(pPropertyVaule->m_bool);
			return TRUE;
		case 7:// 隐藏选择
			p->SetHideSel(pPropertyVaule->m_bool);
			return TRUE;
		case 8:// 滚动条
			p->SetScrollBar(pPropertyVaule->m_int);
			return TRUE;
		case 9:// 边框
			p->SetFrame(pPropertyVaule->m_int);
			break;
		case 10:// 撤销次数
			p->SetUndoLimit(pPropertyVaule->m_int);
			break;
		case 11:// 最大允许长度
			p->SetMaxLen(pPropertyVaule->m_int);
			break;
		case 12:// 自动检测链接
			p->SetAutoDetectURL(pPropertyVaule->m_bool);
			return TRUE;/*重画*/
		case 13:// 起始选择位置
			p->SetSelPos(pPropertyVaule->m_int);
			break;
		case 14:// 被选择字符数
			p->SetSelNum(pPropertyVaule->m_int);
			break;
		case 15:// 被选择文本
			p->SetContent((PCWSTR)pPropertyVaule->m_data.m_pData, TRUE);
			break;
		case 16://是否已更改
			p->SetModify(pPropertyVaule->m_bool);
			break;


		case 17://字体名称
		case 18://字体大小
		case 19://文本颜色
		case 20://文本底色
		case 21://粗体
		case 22://斜体
		case 23://下划线
		case 24://删除线
		case 25://上标
		case 26://下标
		case 27://纵向偏移
		case 28://字体簇
		case 29://字符集
		{
			CHARFORMAT2W cf{ 0 };
			p->GetSelectionCharacterFormat(cf);
			switch (nPropertyIndex)
			{
			case 17://字体名称
				p->SetSelectionCharacterFormat(cf, (PCWSTR)pPropertyVaule->m_data.m_pData);
				return FALSE;
			case 18://字体大小
				if (pPropertyVaule->m_int <= 0)
					TaskDialog(GetActiveWindow(), NULL, L"警告", L"字体大小可以小于0？", L"你是傻逼吗？", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
				else
					cf.yHeight = pPropertyVaule->m_int;
				break;
			case 19://文本颜色
				if (pPropertyVaule->m_int != CLR_INVALID)
				{
					cf.crTextColor = pPropertyVaule->m_int;
				}
				break;
			case 20://文本底色
				if (pPropertyVaule->m_int != CLR_INVALID)
					cf.crBackColor = pPropertyVaule->m_int;

				break;
			case 21://粗体
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_BOLD;
				else
					cf.dwEffects &= ~CFE_BOLD;
				break;
			case 22://斜体
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_ITALIC;
				else
					cf.dwEffects &= ~CFE_ITALIC;
				break;
			case 23://下划线
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_UNDERLINE;
				else
					cf.dwEffects &= ~CFE_UNDERLINE;
				break;
			case 24://删除线
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_STRIKEOUT;
				else
					cf.dwEffects &= ~CFE_STRIKEOUT;
				break;
			case 25://上标
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_SUPERSCRIPT;
				else
					cf.dwEffects &= ~CFE_SUPERSCRIPT;

				break;
			case 26://下标
				if (pPropertyVaule->m_bool)
					cf.dwEffects |= CFE_SUBSCRIPT;
				else
					cf.dwEffects &= ~CFE_SUBSCRIPT;
				break;
			case 27://纵向偏移
				cf.yOffset = pPropertyVaule->m_int;
				break;
			case 28://字体簇
				cf.bPitchAndFamily = pPropertyVaule->m_int;
				break;
			case 29://字符集
				cf.bCharSet = pPropertyVaule->m_int;
				break;
			default:
				break;
			}
			p->SetSelectionCharacterFormat(cf);
		}break;
		case 30://对齐方式
		case 31://首行缩进
		case 32://右边缩进
		case 33://非首行缩进
		case 34://制表符位宽度
		case 35://段前间距
		case 36://段后间距
		case 37://行间距
		case 38://段落符号
		case 39://行间距类型
		{
			PARAFORMAT2 pf{ 0 };
			p->GetSelectionParagraphFormat(pf);
			switch (nPropertyIndex)
			{
			case 30://对齐方式
				pf.wAlignment = pPropertyVaule->m_int;;
				break;
			case 31://首行缩进
				pf.dxStartIndent = pPropertyVaule->m_int;;
				break;
			case 32://右边缩进
				pf.dxRightIndent = pPropertyVaule->m_int;;
				break;
			case 33://非首行缩进
				pf.dxOffset = pPropertyVaule->m_int;
				break;
			case 34://制表符位宽度
				pf.cTabCount = 1;
				pf.rgxTabs[0] = pPropertyVaule->m_int * 1440; // 将制表符位宽度转换为 twips 单位
				break;
			case 35://段前间距
				pf.dySpaceBefore = pPropertyVaule->m_int;
				break;
			case 36://段后间距
				pf.dySpaceAfter = pPropertyVaule->m_int;
				break;
			case 37://行间距
				pf.dyLineSpacing = pPropertyVaule->m_int;
				break;
			case 38://段落符号
				if (pPropertyVaule->m_int < 1 || pPropertyVaule->m_int > 6)
				{
					TaskDialog(GetActiveWindow(), NULL, L"警告", L"不看参数解释，你带脑子了吗？", L"你是傻逼吗？", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
					return FALSE;
				}
				pf.wNumbering = pPropertyVaule->m_int;
				break;
			case 39://行间距类型
				if (pPropertyVaule->m_int < 0 || pPropertyVaule->m_int > 5)
				{
					TaskDialog(GetActiveWindow(), NULL, L"警告", L"不看参数解释，你带脑子了吗？", L"你是傻逼吗？", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
					return FALSE;
				}
				pf.bLineSpacingRule = pPropertyVaule->m_int;
				break;
			}
			p->SetSelectionParagraphFormat(pf);
		}break;

		}

		return FALSE;
	}
	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0://内容格式
			pPropertyVaule->m_int = p->m_Info.m_nContentType;
			break;
		case 1:// 内容
			pPropertyVaule->m_data.m_pData = p->GetContent((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize, false);
			break;
		case 2:
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// 编辑框背景颜色
			pPropertyVaule->m_clr = p->GetCorlor();
			break;
		case 4:// 是否允许多行
			pPropertyVaule->m_bool = p->GetMultiLine();
			break;
		case 5:// 自动换行
			pPropertyVaule->m_bool = p->GetAutoWrap();
			break;
		case 6://只读
			pPropertyVaule->m_bool = p->GetOnlyRead();
			break;
		case 7:// 隐藏选择
			pPropertyVaule->m_bool = p->GetHideSel();
			break;
		case 8:// 滚动条
			pPropertyVaule->m_int = p->GetScrollBar();
			break;
		case 9:// 边框
			pPropertyVaule->m_int = p->GetFrame();
			break;
		case 10:// 撤销次数
			pPropertyVaule->m_int = p->GetUndoLimit();
			break;
		case 11:// 最大允许长度
			pPropertyVaule->m_int = p->GetMaxLen();
			break;
		case 12:// 自动检测链接
			pPropertyVaule->m_bool = p->GetAutoDetectURL();
			break;
		case 13:// 起始选择位置
			pPropertyVaule->m_int = p->GetSelPos();
			break;
		case 14:// 被选择字符数
			pPropertyVaule->m_int = p->GetSelNum();
			break;
		case 15:// 被选择文本
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetContent((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize, TRUE);
			break;
		case 16://是否被改变
			pPropertyVaule->m_bool = p->GetModify();
			break;

		case 17://字体名称
		case 18://字体大小
		case 19://文本颜色
		case 20://文本底色
		case 21://粗体
		case 22://斜体
		case 23://下划线
		case 24://删除线
		case 25://上标
		case 26://下标
		case 27://纵向偏移
		case 28://字体簇
		case 29://字符集
		{
			CHARFORMAT2W cf{ 0 };
			p->GetSelectionCharacterFormat(cf);
			switch (nPropertyIndex)
			{
			case 17://字体名称
				pPropertyVaule->m_data.m_nDataSize = (wcslen(cf.szFaceName) + 1) * sizeof(wchar_t);
				pPropertyVaule->m_data.m_pData = (LPBYTE)cf.szFaceName;
				break;
			case 18://字体大小
				pPropertyVaule->m_int = cf.yHeight;
				break;
			case 19://文本颜色
				pPropertyVaule->m_int = cf.crTextColor;
				break;
			case 20://文本底色
				if (pPropertyVaule->m_int != CLR_INVALID)
					pPropertyVaule->m_int = cf.crBackColor;

				break;
			case 21://粗体
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_BOLD);
				break;
			case 22://斜体
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_ITALIC);
				break;
			case 23://下划线
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_UNDERLINE);
				break;
			case 24://删除线
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_STRIKEOUT);
				break;
			case 25://上标
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_SUPERSCRIPT);
				break;
			case 26://下标
				pPropertyVaule->m_bool = elibstl::IsBitExist(cf.dwEffects, CFE_SUBSCRIPT);
				break;
			case 27://纵向偏移
				pPropertyVaule->m_int = cf.yOffset;
				break;
			case 28://字体簇
				pPropertyVaule->m_int = cf.bPitchAndFamily;
				break;
			case 29://字符集
				pPropertyVaule->m_int = cf.bCharSet;
				break;
			default:
				break;
			}
		}break;
		case 30://对齐方式
		case 31://首行缩进
		case 32://右边缩进
		case 33://非首行缩进
		case 34://制表符位宽度
		case 35://段前间距
		case 36://段后间距
		case 37://行间距
		case 38://段落符号
		case 39://行间距类型
		{
			PARAFORMAT2 pf{ 0 };
			p->GetSelectionParagraphFormat(pf);
			switch (nPropertyIndex)
			{
			case 30://对齐方式
				pPropertyVaule->m_int = pf.wAlignment;;
				break;
			case 31://首行缩进
				pPropertyVaule->m_int = pf.dxStartIndent;;
				break;
			case 32://右边缩进
				pPropertyVaule->m_int = pf.dxRightIndent;;
				break;
			case 33://非首行缩进
				pPropertyVaule->m_int = pf.dxOffset;
				break;
			case 34://制表符位宽度
				pPropertyVaule->m_int = pf.rgxTabs[0] / 1440; // 将制表符位宽度转换为 twips 单位
				break;
			case 35://段前间距
				pPropertyVaule->m_int = pf.dySpaceBefore;
				break;
			case 36://段后间距
				pPropertyVaule->m_int = pf.dySpaceAfter;
				break;
			case 37://行间距
				pPropertyVaule->m_int = pf.dyLineSpacing;
				break;
			case 38://段落符号
				pPropertyVaule->m_int = pf.wNumbering;
				break;
			case 39://行间距类型
				pPropertyVaule->m_int = pf.bLineSpacingRule;
				break;
			}
		}break;
		case 40:/*可否撤销*/
			pPropertyVaule->m_bool = p->CanUnDo();
			break;
		case 41:/*可否重做*/
			pPropertyVaule->m_bool = p->CanReDo();
			break;
		case 42:/*可否粘贴*/
			pPropertyVaule->m_bool = p->CanPaste();
			break;
		case 43:/*行数*/
			pPropertyVaule->m_bool = p->GetLineCount();
			break;
		case 44:/*文本长度*/
			pPropertyVaule->m_int = p->GetTextLength();
			break;
		}

		return TRUE;
	}
	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}
	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		PWSTR psz;
		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 1:// 内容W
		{
			SIZE_T a;
			p->GetContent(&a, FALSE);
			if (elibstl::IntputBox(&psz, p->m_editData.to_string<wchar_t>().c_str()))
			{
				if (psz == nullptr)
					p->SetContent(L"", false);
				else {
					p->SetContent(psz, false);
					delete[]psz;
				}
				*pblModified = TRUE;
			}
		}break;
		case 2:// 内容W
		{
			SIZE_T a;
			p->GetContent(&a, FALSE);
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}break;
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
			*((int*)dwParam2) = 20;
		}
		return TRUE;
		}
		return FALSE;
	}
public:
	static  DWORD CALLBACK sEditStreamOutCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
	{
		((epldatatype::MemBin*)dwCookie)->append(pbBuff, cb);
		*pcb = cb;
		return 0;
	}
	long StreamOut(_In_ int nFormat, EDITSTREAM& es)
	{
		return (long)::SendMessage(m_hWnd, EM_STREAMOUT, nFormat, (LPARAM)&es);
	}
	long StreamIn(_In_ int nFormat, EDITSTREAM& es)
	{
		return (long)::SendMessage(m_hWnd, EM_STREAMIN, nFormat, (LPARAM)&es);
	}
	static DWORD CALLBACK sEditStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
	{
		epldatatype::MemBin* pMem = (epldatatype::MemBin*)dwCookie;
		if (cb > pMem->size())
			cb = (LONG)pMem->size();
		if (cb > 0)
		{
			memcpy(pbBuff, pMem->data(), cb);
			pMem->remove(0, cb);
		}
		*pcb = cb;
		return 0;
	}
	//内容
	eStlInline LPBYTE GetContent(SIZE_T* size, BOOL blOnlySelection)
	{
		INT nFormat = (m_Info.m_nContentType == 0 ? (SF_TEXT | SF_UNICODE) : SF_RTF);
		if (blOnlySelection)
			nFormat |= SFF_SELECTION;

		m_editData.clean();
		EDITSTREAM inf;
		inf.dwCookie = (DWORD_PTR)&m_editData;
		inf.dwError = 0;
		inf.pfnCallback = sEditStreamOutCallback;
		StreamOut(nFormat, inf);
		m_editData.append(0);
		if (m_editData.empty())
		{
			*size = 0;
			return nullptr;
		}
		if (m_Info.m_nContentType == 0)
		{
			*size = m_editData.size();
			return m_editData.data();
		}
		else
		{
			epldatatype::MemBin memBuf;
			epldatatype::GetWideText((const CHAR*)m_editData.data(), memBuf, NULL);
			m_editData = memBuf;
			*size = m_editData.size();
			return m_editData.data();
		}
	}
	//内容
	eStlInline void SetContent(const std::wstring_view& szContent, BOOL blOnlySelection)
	{
		INT nFormat = (m_Info.m_nContentType == 0 ? (SF_TEXT | SF_UNICODE) : SF_RTF);
		if (blOnlySelection)
			nFormat |= SFF_SELECTION;

		m_editData.clean();
		if (m_Info.m_nContentType == 0)
		{
			m_editData.append_str(szContent);
		}
		else
		{
			epldatatype::MemBin memBuf;
			size_t npTextLength;
			const CHAR* ps = GetMbsText(szContent.data(), memBuf, &npTextLength);

			m_editData.append(ps, npTextLength * sizeof(CHAR));
		}

		EDITSTREAM inf;
		inf.dwCookie = (DWORD_PTR)&m_editData;
		inf.dwError = 0;
		inf.pfnCallback = sEditStreamInCallback;

		StreamIn(nFormat, inf);
	}

public:

	/*回调函数*/
	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_NOTIFY:
		{
			NMHDR* nm = (NMHDR*)lParam;
			if (nm->code == EN_SELCHANGE) {
				SELCHANGE* slc = (SELCHANGE*)lParam;

				if (m_CtrlSCInfo.count(slc->nmhdr.hwndFrom))
					m_CtrlSCInfo[slc->nmhdr.hwndFrom]->OnSelChange(slc->chrg.cpMin, slc->chrg.cpMax, slc->seltyp);
			}
			else if (nm->code == EN_LINK)
			{
				ENLINK* el = (ENLINK*)lParam;
				if (el->msg == WM_LBUTTONDOWN)
				{
					if (m_CtrlSCInfo.count(el->nmhdr.hwndFrom))
						m_CtrlSCInfo[el->nmhdr.hwndFrom]->OnLinkClick(el->chrg.cpMin, el->chrg.cpMax);
				}
			}

		}break;
		case WM_COMMAND: {

			if (HIWORD(wParam) == EN_CHANGE)
			{
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnChange();
			}
		}
					   break;
		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

public:
	CRichEdit(STD_ECTRL_CREATE_ARGS)
	{
		static	HMODULE hRichEditDLL = NULL;
		if (!hRichEditDLL)
		{

			hRichEditDLL = LoadLibraryW(L"MSFTEDIT.DLL");
			if (!hRichEditDLL)
			{
				TaskDialog(GetActiveWindow(), NULL, L"警告", L"该系统并不支持!", L"B老旧系统跑啥富文本框", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
				return;
			}
		}

		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);

		std::wstring str = L"";
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ERICHEDITDATA));

			if (cbData > sizeof(ERICHEDITDATA) + cbBaseData)//存在内容
			{
				p += sizeof(ERICHEDITDATA);
				str = (const wchar_t*)p;
			}
		}
		else
		{
			m_Info0.iFrame = 1;
			m_Info.RevocationTimes = 1;
			m_Info.m_blAutoNextLine = TRUE;
			m_Info.m_blMutiLine = TRUE;
			m_Info.bAutoDetectURL = TRUE;
			m_Info.m_clrBackColor = CLR_DEFAULT;
		}
		m_Info.iVer = DATA_VER_RICHEDIT_1;

		if (m_Info.m_blMutiLine)
		{
			dwStyle |= (ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | WS_VSCROLL);

			if (m_Info.m_blAutoNextLine == FALSE)
				dwStyle |= (ES_AUTOHSCROLL | WS_HSCROLL);
		}
		else
			dwStyle |= ES_AUTOHSCROLL;
		if (m_Info.m_blReadOnly)
			dwStyle |= ES_READONLY;
		if (m_Info.m_blHideSelection == FALSE)
			dwStyle |= ES_NOHIDESEL;


		// 创建 RichEdit 控件
		m_hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, nullptr, dwStyle | WS_CHILDWINDOW | WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPSIBLINGS | EM_PASTESPECIAL,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);

		if (!m_hWnd)
		{
			TaskDialog(GetActiveWindow(), NULL, L"警告", L"创建窗口失败", L"B老旧系统跑啥富文本框", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			return;
		}
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;



		InitBase0(pAllData);
		SetContent(str, FALSE);
		SetScrollBar(m_Info.iScrollBar);/*滚动条*/
		SetHideSel(m_Info.m_blHideSelection);/*隐藏选择*/
		SetCorlor(m_Info.m_clrBackColor);
		SetMaxLen(m_Info.iMaxLen);/*最大长度*/
		SetAutoDetectURL(m_Info.bAutoDetectURL);/*超链接*/
		SetUndoLimit(m_Info.RevocationTimes);/*最大撤销次数*/




		DWORD make = ::SendMessageW(m_hWnd, EM_GETEVENTMASK, 0, 0);

		::SendMessageW(m_hWnd, EM_SETEVENTMASK, 0, make | ENM_CHANGE | ENM_SELCHANGE | ENM_LINK);
	//	::SendMessageW(m_hWnd, EM_SETOPTIONS, ECOOP_OR, ECO_AUTOWORDSELECTION);
		FrameChanged();
	}

	~CRichEdit()
	{
		delete[] m_pszSelText;
	}
	/*是否可撤销*/
	eStlInline BOOL CanUnDo() {
		return SendMessageW(m_hWnd, EM_CANUNDO, 0, 0) != 0;
	}
	eStlInline void OnSelChange(int begin, int end,int type) {
	
	
		EVENT_ARG_VALUE Arg1{}, Arg2{}, Arg3{};
		Arg1.m_inf.m_int = begin;
		Arg1.m_inf.m_dtDataType = SDT_INT;
		Arg2.m_inf.m_int = end;
		Arg2.m_inf.m_dtDataType = SDT_INT;
		Arg3.m_inf.m_int = type;
		Arg3.m_inf.m_dtDataType = SDT_INT;


		EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 1);
		event.m_nArgCount = 3;
		event.m_arg[0] = Arg1;
		event.m_arg[1] = Arg2;
		event.m_arg[2] = Arg3;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&event, 0);

	}
	eStlInline void OnLinkClick(int begin, int end) {


		EVENT_ARG_VALUE Arg1{}, Arg2{}, Arg3{};
		Arg1.m_inf.m_int = begin;
		Arg1.m_inf.m_dtDataType = SDT_INT;
		Arg2.m_inf.m_int = end;
		Arg2.m_inf.m_dtDataType = SDT_INT;



		EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 2);
		event.m_nArgCount = 2;
		event.m_arg[0] = Arg1;
		event.m_arg[1] = Arg2;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);

	}
	eStlInline void OnChange()
	{

		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}
	/*是否可重做*/
	eStlInline BOOL CanReDo() {
		return SendMessageW(m_hWnd, EM_CANREDO, 0, 0) != 0;
	}
	/*可否粘贴*/
	eStlInline BOOL CanPaste() {
		return SendMessageW(m_hWnd, EM_CANPASTE, 0, 0) != 0;
	}

	BOOL  GetModify() {
		return SendMessageW(m_hWnd, EM_GETMODIFY, 0, 0) != 0;
	};
	void SetModify(BOOL Modify) {
		SendMessageW(m_hWnd, EM_SETMODIFY, Modify, 0);
	}

	eStlInline void SetUndoLimit(int limit)
	{
		m_Info.RevocationTimes = limit;
		m_Info.RevocationTimes = SendMessageW(m_hWnd, EM_SETUNDOLIMIT, m_Info.RevocationTimes, 0);
	}
	eStlInline int GetUndoLimit() const
	{
		return m_Info.RevocationTimes;
	}

	void SetScrollBar(int i)
	{
		m_Info.iScrollBar = i;
		switch (i)
		{
		case 0:
			ShowScrollBar(m_hWnd, SB_VERT, FALSE);
			ShowScrollBar(m_hWnd, SB_HORZ, FALSE);
			break;
		case 1:
			ShowScrollBar(m_hWnd, SB_VERT, FALSE);
			ShowScrollBar(m_hWnd, SB_HORZ, TRUE);
			break;
		case 2:
			ShowScrollBar(m_hWnd, SB_VERT, TRUE);
			ShowScrollBar(m_hWnd, SB_HORZ, FALSE);
			break;
		case 3:
			ShowScrollBar(m_hWnd, SB_VERT, TRUE);
			ShowScrollBar(m_hWnd, SB_HORZ, TRUE);
			break;
		}
	}
	int GetLineCount() {
		return (int)::SendMessage(m_hWnd, EM_GETLINECOUNT, 0, 0);
	}
	int GetTextLength() {
		return (long)::SendMessage(m_hWnd, WM_GETTEXTLENGTH, NULL, NULL);
	}
	int GetScrollBar()
	{
		if (m_bInDesignMode)
			return m_Info.iScrollBar;
		else
		{
			BOOL bVSB = elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), WS_VSCROLL);
			BOOL bHSB = elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), WS_HSCROLL);
			if (bVSB)
				if (bHSB)
					return 3;
				else
					return 2;
			if (bHSB)
				return 1;

			return 0;
		}
	}
	void SetSelPos(int iSelPos)
	{
		m_Info.iSelPos = iSelPos;
		DWORD dwStart, dwEnd;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		DWORD dwLen;
		if (dwStart > dwEnd)
			dwLen = dwStart - dwEnd;
		else
			dwLen = dwEnd - dwStart;
		SendMessageW(m_hWnd, EM_SETSEL, iSelPos, iSelPos + dwLen);
	}

	eStlInline int GetSelPos()
	{
		if (m_bInDesignMode)
			return m_Info.iSelPos;
		else
		{
			DWORD dwStart;
			SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, NULL);
			return dwStart;
		}
	}
	eStlInline void SetAutoDetectURL(BOOL bAutoDetect)
	{
		m_Info.bAutoDetectURL = bAutoDetect;
		SendMessageW(m_hWnd, EM_AUTOURLDETECT, m_Info.bAutoDetectURL, NULL);
	}
	eStlInline BOOL GetAutoDetectURL()
	{
		m_Info.bAutoDetectURL = SendMessageW(m_hWnd, EM_GETAUTOURLDETECT, 0, 0);
		return m_Info.bAutoDetectURL;
	}


	eStlInline void SetMaxLen(int iMaxLen)
	{
		m_Info.iMaxLen = iMaxLen;
		SendMessageW(m_hWnd, EM_SETLIMITTEXT, iMaxLen, 0);
	}

	eStlInline int GetMaxLen()
	{
		if (m_bInDesignMode)
			return m_Info.iMaxLen;
		else
			return SendMessageW(m_hWnd, EM_GETLIMITTEXT, 0, 0);
	}

	eStlInline void SetMultiLine(BOOL bMultiLine)
	{
		BOOL bOld = m_Info.m_blMutiLine;
		m_Info.m_blMutiLine = bMultiLine;// 不需要修改风格，因为控件要重新创建
	}

	eStlInline BOOL GetMultiLine()
	{
		if (m_bInDesignMode)
			return m_Info.m_blMutiLine;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), ES_MULTILINE);
	}
	eStlInline void SetHideSel(BOOL bHideSel)
	{
		m_Info.m_blHideSelection = bHideSel;
		::SendMessage(m_hWnd, EM_HIDESELECTION, m_Info.m_blHideSelection, TRUE);
	}

	eStlInline BOOL GetHideSel()
	{
		if (m_bInDesignMode)
			return m_Info.m_blHideSelection;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), ES_NOHIDESEL) && m_Info.m_blHideSelection;
	}
	void SetAutoWrap(BOOL bAutoWrap)
	{
		m_Info.m_blAutoNextLine = bAutoWrap;
	}

	eStlInline BOOL GetAutoWrap()
	{
		return m_Info.m_blAutoNextLine;
	}
	eStlInline void SetCorlor(COLORREF cr)
	{
		m_Info.m_clrBackColor = cr;
		if (m_Info.m_clrBackColor == CLR_DEFAULT)
		{
			::SendMessage(m_hWnd, EM_SETBKGNDCOLOR, TRUE, RGB(255, 255, 255));
		}
		else
		{
			::SendMessage(m_hWnd, EM_SETBKGNDCOLOR, FALSE, m_Info.m_clrBackColor);
		}
		Redraw();
	}
	eStlInline COLORREF GetCorlor() {
		return m_Info.m_clrBackColor;
	}
	eStlInline void SetSelNum(int iSelNum)
	{
		m_Info.iSelNum = iSelNum;
		DWORD dwStart;
		SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, NULL);
		SendMessageW(m_hWnd, EM_SETSEL, dwStart, dwStart + iSelNum);
	}
	BOOL GetOnlyRead() {
		if (m_bInDesignMode)
			return m_Info.m_blReadOnly;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), ES_READONLY);
	}
	void SetOnlyRead(BOOL ReadOnly) {
		m_Info.m_blReadOnly = ReadOnly;
		SendMessage(m_hWnd, EM_SETREADONLY, m_Info.m_blReadOnly, 0);

	}
	int GetSelNum()
	{
		if (m_bInDesignMode)
			return m_Info.iSelNum;
		else
		{
			DWORD dwStart, dwEnd;
			SendMessageW(m_hWnd, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
			DWORD dwLen;
			if (dwStart > dwEnd)
				dwLen = dwStart - dwEnd;
			else
				dwLen = dwEnd - dwStart;
			return (int)dwLen;
		}
	}
	///*追加文本*/
	//void AppendText(const wchar_t* text) const
	//{
	//	int length = GetWindowTextLengthW(m_hWnd);
	//	SendMessageW(m_hWnd, EM_SETSEL, length, length);
	//	SendMessageW(m_hWnd, EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(text));
	//}
	///*添加图片*/
	//void AppendImage()
	//{
	//	if (!m_isInit || m_hWnd == NULL)
	//		return;
	//	// 在富文本框中插入剪贴板中的图像
	//	SendMessageW(m_hWnd, WM_PASTE, 0, 0);

	//}


private:

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;

		SIZE_T textsize = 0;
		const auto str = GetContent(&textsize, FALSE);;


		auto hGlobal = FlattenInfoBase0(sizeof(ERICHEDITDATA) + textsize + sizeof(wchar_t), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ERICHEDITDATA));

		p += sizeof(ERICHEDITDATA);
		memset(p, 0, textsize + 1);
		memcpy(p, str, textsize);
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}
	/*获取选中区域字符格式*/
	bool GetSelectionCharacterFormat(CHARFORMAT2W& format) const
	{

		format.cbSize = sizeof(CHARFORMAT2W);
		return SendMessageW(m_hWnd, EM_GETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&format)) != 0;
	}

	/*置选中区域字符格式*/
	bool SetSelectionCharacterFormat(const CHARFORMAT2W& format, const std::wstring_view& format_name)   const
	{
		CHARFORMAT2W cf;
		cf.cbSize = sizeof(CHARFORMAT2W);
		cf.dwMask = CFM_FACE | CFM_EFFECTS | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET;

		if (format_name.empty())
		{
			auto len = lstrlenW(format.szFaceName);
			if (len > LF_FACESIZE - 1)
			{
				len = LF_FACESIZE - 1;
			}
			wcsncpy_s(cf.szFaceName, format.szFaceName, len);
			cf.szFaceName[len] = L'\0';
		}
		else
		{
			auto len = format_name.size();
			if (len > LF_FACESIZE - 1)
			{
				len = LF_FACESIZE - 1;
			}
			wcsncpy_s(cf.szFaceName, format_name.data(), len);
			cf.szFaceName[len] = L'\0';
		}

		cf.dwEffects = format.dwEffects & ~CFE_AUTOCOLOR;
		cf.yHeight = format.yHeight;
		cf.yOffset = format.yOffset;
		cf.crTextColor = format.crTextColor;
		cf.bCharSet = format.bCharSet;
		cf.bPitchAndFamily = format.bPitchAndFamily;
		return SendMessageW(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&cf)) != 0;
	}
	bool SetSelectionCharacterFormat(const CHARFORMAT2W& format)   const
	{
		CHARFORMAT2W cf;
		cf.cbSize = sizeof(CHARFORMAT2W);
		cf.dwMask = CFM_FACE | CFM_EFFECTS | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET;


		auto len = lstrlenW(format.szFaceName);
		if (len > LF_FACESIZE - 1)
		{
			len = LF_FACESIZE - 1;
		}
		wcsncpy_s(cf.szFaceName, format.szFaceName, len);
		cf.szFaceName[len] = L'\0';


		cf.dwEffects = format.dwEffects & ~CFE_AUTOCOLOR;
		cf.yHeight = format.yHeight;
		cf.yOffset = format.yOffset;
		cf.crTextColor = format.crTextColor;
		cf.bCharSet = format.bCharSet;
		cf.bPitchAndFamily = format.bPitchAndFamily;
		return SendMessageW(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&cf)) != 0;
	}
	/*段落格式*/
	bool GetSelectionParagraphFormat(PARAFORMAT2& format) const
	{
		format.cbSize = sizeof(PARAFORMAT2);
		return SendMessageW(m_hWnd, EM_GETPARAFORMAT, 0, reinterpret_cast<LPARAM>(&format)) != 0;
	}
	bool SetSelectionParagraphFormat(PARAFORMAT2& format) const
	{

		format.cbSize = sizeof(PARAFORMAT2);
		format.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_RIGHTINDENT | PFM_OFFSET | PFM_ALIGNMENT | PFM_LINESPACING | PFM_SPACEAFTER | PFM_SPACEBEFORE;


		if (format.wAlignment == 0) {
			format.wAlignment = PFA_LEFT;
		}
		return SendMessageW(m_hWnd, EM_SETPARAFORMAT, 0, reinterpret_cast<LPARAM>(&format)) != 0;
	}

	/*置选中区域*/
	bool SetSelection(int startPosition, int endPosition)   const
	{
		CHARRANGE range;
		range.cpMin = startPosition;
		range.cpMax = endPosition;
		return SendMessageW(m_hWnd, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&range)) != 0;
	}
	ERICHEDITDATA m_Info{ 0 };
	epldatatype::MemBin m_editData;/*设计器不可能创建出,所以无需担心设计器传递过来的格式*/
	PWSTR m_pszSelText = NULL;

};


SUBCLASS_MGR_INIT(CRichEdit, SCID_RICHEDITPARENT, SCID_RICHEDIT)
ESTL_NAMESPACE_END



EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_RichEdit(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CRichEdit::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CRichEdit::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CRichEdit::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CRichEdit::ENotify;
	}
	return NULL;
}


ESTL_NAMESPACE_BEGIN


static UNIT_PROPERTY s_Member_RichEdit[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个
	//空串结束

	/*0*/{"内容格式","TextFormat","本属性指定对文本框的内容进行读写时所使用的文本格式。具体格式的组合看开发文档。",UD_PICK_INT,_PROP_OS(OS_ALL),"纯文本\0""RTF丰富文本\0""\0"},
	/*1*/{"内容", "Text", "本属性所使用的文本格式由“内容格式”属性决定,纯文本为标准utf16字符,RTF对象为对象数据", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},

	/*2*/{"文本", "TextW", "标准utf16字符", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*3*/{"背景颜色","BackColor","文本框的背景颜色",UD_COLOR_BACK,_PROP_OS(OS_ALL),NULL},
	/*4*/{"是否允许多行","AllowMultiLines","本属性设置文本框是否允许输入多行文本",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*5*/{"自动换行","WrapMode","本属性设置文本框是否支持自动换行",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*6*/{"只读","ReadOnly","本属性设置编辑框是否只能读取而不能写入",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*7*/{"隐藏选择","HideSel","本属性指定失去输入焦点后是否还显示当前被选择的区域",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*8*/{"滚动条", "ScrollBar", "横向滚动条与自动换行互斥", UD_PICK_INT, _PROP_OS(__OS_WIN), "无\0""横向滚动条\0""纵向滚动条\0""横向及纵向滚动条\0""\0"},
	/*9*/{"边框","Style","",UD_PICK_INT,_PROP_OS(OS_ALL),"无边框\0""凹入式\0""凸出式\0""浅凹入式\0""镜框式\0""单线边框式\0""\0"},
	/*10*/{"最大允许撤消次数","MultileveUndo","返回或设置可以撤消的次数。占用系统资源，不可设置太多",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*11*/{"最大允许长度","MaxAllowLength","本属性设置最大允许输入到文本框中的字符数目，如为0则输入字符数目不受限制",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*12*/{"自动检测链接","AutoURLDetect","自动检测文档里的URL链接，例如：HTTP:\\、ftp:\\和mailto:开头的关键字",UD_BOOL,_PROP_OS(OS_ALL),NULL},
	/*13*/{"起始选择位置","SelStart","返回或设置所选择文本的起始点；0 为位置 1 ，1 为位置 2，如此类推。如果没有文本被选中， 则提供当前光标位置。如果设置位置时使用值 -1，则将当前光标位置移动到文本尾部",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*14*/{"被选择字符数","SelLength","返回或设置所选择的字符数。如果设置字符数时使用值 -1，则选择编辑框内的所有字符",UD_INT,_PROP_OS(OS_ALL),NULL},
	/*15*/{"被选择文本","SelText","返回或替换当前所选择的文本，文本格式由“内容格式”属性决定",UD_CUSTOMIZE,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*16*/{"是否已改变","CanUnDo","运行时可控制，被改变则返回真，否则为假。",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},

	/*17*/{"字体名称","FontName","在编辑时，设置和取得被选择文本的字体名称。如果字体混合选中,则取得光标位置的字体名称",UD_CUSTOMIZE,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*18*/{"字体大小","FontSize","在编辑时，设置和取得被选择文本的字体大小。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*19*/{"文本颜色","ForeColor","在编辑时，设置和取得被选择文本的颜色值。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*20*/{"文本底色","FontBackColor","在编辑时，设置和取得被选择文本的背景颜色值。如果字体混合选中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*21*/{"粗体","Bold","在编辑时，被选择文本是否为粗体。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*22*/{"斜体","Italic","在编辑时，被选择文本是否为斜体。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*23*/{"下划线","Underline","在编辑时，被选择文本是否为下划线。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*24*/{"删除线","StrikeThrough","在编辑时，被选择文本是否为删除线。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*25*/{"上标","Superscript","在编辑时，被选择文本是否为上标。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*26*/{"下标","Subscript","在编辑时，被选择文本是否为下标。如果字体混合选中,则为真",UD_BOOL,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*27*/{"纵向偏移","YOffset","在编辑时，设置和取得被选择文本块的纵向位置，正值变上标，负值变下标，单位为像素。如果混合选 中，取光标处的",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*28*/{"字体蔟","PitchAndFamily","LOGFONT结构的lfPitchAndFamily成员",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*29*/{"字符集","CharSet","LOGFONT结构的lfCharSet成员",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*30*/{"对齐方式","Alignment","选区的对齐方式，可以为以下常量值之一： 1、#文本居左；2、#文本居右；3、#文本居中。",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*31*/{"首行缩进","StartIndent","段落相对于文本框左边框的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*32*/{"右边缩进","RightIndent","段落右边相对于文本框右边框的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*33*/{"非首行缩进","Indent","指定段落中所有非首行相对于首行的缩进量，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*34*/{"制表位宽度","TopStops","TAB键的制表位宽度，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*35*/{"段前间距","SpaceBefore","段落的上面间距，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*36*/{"段后间距","SpaceAfter","段落的下面间距，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},
	/*37*/{"行间距","LineSpacing","行与行之间的距离，单位为点像素",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},


	/*38*/{"段落符号","LineSpacing","\
	#0.无段落符号\
	#1.圆点\
	#2.阿拉伯数字\
	#3.小写字母\
	#4.大写字母\
	#5.小写罗马字母	\
	#6.大写罗马字母\
	",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},


	/*39*/{"行间距类型","LineSpacingRule","\
	#0.单一（“行间距”成员被忽略）\n\
	#1.一半（“行间距”成员被忽略） \n\
	#2.两倍（“行间距”成员被忽略）\n\
	#3.不小于单一(“行间距”成员指定一行到下一行的间距，单位：缇(1/1440英寸)，如果小于 单一 间距，则无效)\n\
	#4.精确控制（“行间距”成员指定一行到下一行的间距，单位：缇(1/1440英寸)）\n\
	#5.倍数20(“行间距”设置20 为单一间距，40为双倍，60为三倍...)	\
	",UD_INT,UW_CANNOT_INIT | _PROP_OS(OS_ALL),NULL},

	/*40*/{"可否撤销","CanUnDo","返回真可撤消，假不可。",UD_BOOL,UW_ONLY_READ | _PROP_OS(OS_ALL),NULL},
	/*41*/{"可否重做","CanUnDo","返回真可，假不可。",UD_BOOL,UW_ONLY_READ | _PROP_OS(OS_ALL),NULL},
	/*42*/{"可否粘贴","CanUnDo","返回真可，假不可。",UD_BOOL,UW_ONLY_READ | _PROP_OS(OS_ALL),NULL},
	/*43*/{"行数","","",UD_INT,UW_ONLY_READ | _PROP_OS(OS_ALL),NULL},
	/*44*/{"文本长度","","",UD_INT,UW_ONLY_READ | _PROP_OS(OS_ALL),NULL},


};
static EVENT_ARG_INFO2 s_EventArgInfo_RichEdit_Feedback[] =
{
	 {"起始位置", "", 0, SDT_INT},
	 {"结束位置", "", 0, SDT_INT},
	 {"选择类型", "#0：空(SEL_EMPTY)  #1:文本（SEL_TEXT） #2：对象 （SEL_OBJECT）#3：多个字符（SEL_MULTICHAR）#4：多个对象（SEL_MULTIOBJECT）", 0, SDT_INT},
};
static EVENT_INFO2 s_Event_RichEdit[] =
{
	/*000*/ {"内容被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
	/*001*/ {"选择被改变", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, ARRAYSIZE(s_EventArgInfo_RichEdit_Feedback), s_EventArgInfo_RichEdit_Feedback, _SDT_NULL},
	/*002*/ {"超连接被单击", NULL, _EVENT_OS(OS_ALL) | EV_IS_VER2, 2, s_EventArgInfo_RichEdit_Feedback, _SDT_NULL},

};
LIB_DATA_TYPE_INFO CtRichEdit = {
	"富文本框",//中文名称
	"RichEdit",//英文名称
	"",//说明
	0,//命令数量
	0,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_RICHEDIT,//资源ID
	ARRAYSIZE(s_Event_RichEdit),
	s_Event_RichEdit,//事件
	ARRAYSIZE(s_Member_RichEdit),//属性数
	s_Member_RichEdit,//属性指针
	libstl_GetInterface_RichEdit,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END