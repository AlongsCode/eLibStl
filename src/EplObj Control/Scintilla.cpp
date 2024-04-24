#include"EcontrolHelp.h"
#include "Scintilla\Scintilla.h"
#include "Scintilla\SciLexer.h"
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"msimg32.lib")


inline std::string WStrToUtf8(const std::wstring& pwsText)
{
	size_t npLength = pwsText.size();
	std::string memBuf;
	if (npLength > 0)
	{
		auto npBufLen = ::WideCharToMultiByte(CP_UTF8, 0, pwsText.c_str(), (INT)npLength, NULL, 0, NULL, NULL);
		memBuf.resize(npBufLen + 1);
		CHAR* psBuf = memBuf.data();
		npBufLen = ::WideCharToMultiByte(CP_UTF8, 0, pwsText.c_str(), (INT)npLength, psBuf, (INT)npBufLen, NULL, NULL);

		if (npBufLen > 0)  // 转换成功?
		{
			psBuf[npBufLen] = '\0';
			return psBuf;
		}
	}
	return "";
}


#pragma warning(disable:4996)

#define SCID_SCINTILLA		20230523'01u
#define SCID_SCINTILLAPARENT	20230523'02u

#define ED_CUEBANNER_MAXLEN 260

ESTL_NAMESPACE_BEGIN
/*火花编辑框*/
#define DATA_VER_SCINTILLA_1	1
struct ESCINTILLADATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	COLORREF m_BackColour;//背景色
	COLORREF m_ForeColour;//前景色
	bool m_bSelectionBackColour;		// 是否被选择背景色
	COLORREF m_SelectionBackColour;		// 被选择背景色
	bool m_bSelectionForeColour;		// 是否被选择背景色
	COLORREF m_SelectionForeColour;		// 被选择前景色
	int  m_ScrollbarMode;//滚动条风格
	int  m_ScrollbarWigtht;//滚动条长度
	bool m_onlyread;//只读
	int m_lexer;//词法分析器;
};
#pragma region Help
inline void show_warning_dialog(HWND parentWnd, LPCWSTR title, LPCWSTR content) {
	TASKDIALOGCONFIG config = { 0 };
	config.cbSize = sizeof(config);
	config.hwndParent = parentWnd;
	config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_USE_HICON_MAIN;
	config.pszWindowTitle = title;
	config.pszMainIcon = TD_WARNING_ICON;
	config.pszContent = content;
	config.pszMainInstruction = L"警告";

	TaskDialogIndirect(&config, NULL, NULL, NULL);
}

static std::string ansi_to_utf8(const char* text)
{
	if (text == nullptr || *text == '\0')
		return "";
	int utf8Length = MultiByteToWideChar(CP_ACP, 0, text, -1, nullptr, 0);
	std::wstring wideText(utf8Length, L'\0');
	MultiByteToWideChar(CP_ACP, 0, text, -1, &wideText[0], utf8Length);
	int utf8Length2 = WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string utf8Text(utf8Length2, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, &utf8Text[0], utf8Length2, nullptr, nullptr);
	return utf8Text;
}
static std::string utf8_to_ansi(const char* text)
{
	if (text == nullptr || *text == '\0')
		return "";
	int wideLength = MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
	std::wstring wideText(wideLength, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, text, -1, &wideText[0], wideLength);

	int ansiLength = WideCharToMultiByte(CP_ACP, 0, wideText.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string ansiText(ansiLength, '\0');
	WideCharToMultiByte(CP_ACP, 0, wideText.c_str(), -1, &ansiText[0], ansiLength, nullptr, nullptr);
	return ansiText;
}
static std::string unicode_to_utf8(const wchar_t* text)
{
	if (text == nullptr || *text == L'\0')
		return "";
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, text, -1, nullptr, 0, nullptr, nullptr);
	std::string utf8Text(utf8Length + 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, text, -1, &utf8Text[0], utf8Length, nullptr, nullptr);
	return utf8Text;
}
std::wstring utf8_to_unicode(const char* utf8Text)
{
	if (utf8Text == nullptr || *utf8Text == L'\0')
		return L"";
	int unicodeLength = MultiByteToWideChar(CP_UTF8, 0, utf8Text, -1, nullptr, 0);
	std::wstring unicodeText(unicodeLength, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, utf8Text, -1, &unicodeText[0], unicodeLength);

	return unicodeText;
}
static PSTR unicode_to_utf8_p(const wchar_t* text)
{
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, text, -1, nullptr, 0, nullptr, nullptr);
	char* utf8Text = new char[utf8Length + 1];
	WideCharToMultiByte(CP_UTF8, 0, text, -1, utf8Text, utf8Length, nullptr, nullptr);
	utf8Text[utf8Length] = '\0';
	return utf8Text;
}

#pragma endregion
/*文本传递方式为utf-8，和基类文本储存方式区别较大*/
class CScintillaEditor :public elibstl::CCtrlBase
{

	SUBCLASS_MGR_DECL(CScintillaEditor)
private:
	ESCINTILLADATA m_Info{ 0 };
	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CScintillaEditor*)dwRefData;
		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public: /*C中使用,utf-8*/
	void set_text(const char* text) {

		auto u8str = ansi_to_utf8(text);
		SendEditor(SCI_SETTEXT, 0, (sptr_t)u8str.data());
	}
	void set_text(const wchar_t* text) {

		auto u8str = unicode_to_utf8(text);
		SendEditor(SCI_SETTEXT, 0, (sptr_t)u8str.data());
	}
	unsigned char get_selalpha() {
		return static_cast<unsigned char>(::SendMessage(m_hWnd, SCI_GETSELALPHA, 0, 0));
	}
	CHAR* get_text() {
		int length = SendMessage(m_hWnd, SCI_GETLENGTH, 0, 0);
		std::string text(length, '\0');
		SendMessage(m_hWnd, SCI_GETTEXT, length + 1, (LPARAM)text.data());
		m_ansiStr = utf8_to_ansi(text.c_str());
		return m_ansiStr.data();
	}
	LPBYTE get_textW(size_t* size) {
		int length = SendMessage(m_hWnd, SCI_GETLENGTH, 0, 0);
		std::string text(length, '\0');
		SendMessage(m_hWnd, SCI_GETTEXT, length + 1, (LPARAM)text.data());
		m_wstr = utf8_to_unicode(text.c_str());
		*size = (m_wstr.size() + 1) * sizeof(wchar_t);
		return (LPBYTE)m_wstr.data();
	}
	/*置滚动条模式*/
	void set_scrollbar_mode(int mode) {
		m_Info.m_ScrollbarMode = mode;
		switch (m_Info.m_ScrollbarMode)
		{
		case 0:

			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 0, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 0, 0);
			break;
		case 1:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 0, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 1, 0);
			break;
		case 2:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 1, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 0, 0);
			break;
		case 3:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 1, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 1, 0);
			break;
		}
	}
	/*获取滚动条*/
	int get_scrollbar_mode() {
		int vertical = static_cast<int>(::SendMessage(m_hWnd, SCI_GETVSCROLLBAR, 0, 0));
		int horizontal = static_cast<int>(::SendMessage(m_hWnd, SCI_GETHSCROLLBAR, 0, 0));

		if (vertical && horizontal) {
			m_Info.m_ScrollbarMode = 3;  // 显示垂直和水平滚动条
		}
		else if (vertical) {
			m_Info.m_ScrollbarMode = 2;  // 显示垂直滚动条
		}
		else if (horizontal) {
			m_Info.m_ScrollbarMode = 1;  // 显示水平滚动条
		}
		else {
			m_Info.m_ScrollbarMode = 0;  // 隐藏滚动条
		}
		return m_Info.m_ScrollbarMode;
	}


	/*置风格背景色*/
	void set_background_color(COLORREF color) {
		m_Info.m_BackColour = color;
		SendEditor(SCI_STYLESETBACK, (uptr_t)STYLE_DEFAULT, (sptr_t)color);
		debug_put((INT)SendEditor(SCI_STYLEGETBACK, (uptr_t)STYLE_DEFAULT, (sptr_t)color));
	}
	/*取风格背景色*/
	COLORREF get_background_color() {
		if (m_bInDesignMode)
			return m_Info.m_BackColour;
		return SendEditor(SCI_STYLEGETBACK, (uptr_t)STYLE_DEFAULT);
	}
	/*置风格前景色*/
	void set_foreground_color(COLORREF color) {
		m_Info.m_ForeColour = color;
		SendEditor(SCI_STYLESETFORE, STYLE_DEFAULT, m_Info.m_ForeColour);
	}
	/*取风格前景色*/
	COLORREF get_foreground_color() {
		if (m_bInDesignMode)
			return m_Info.m_ForeColour;
		return static_cast<COLORREF>(SendEditor(SCI_STYLEGETFORE, STYLE_DEFAULT, 0));
	}
	/*是否启用选中背景色*/
	void set_bselbackclor(bool bselbackclor) {
		m_Info.m_bSelectionBackColour = bselbackclor;
		::SendMessage(m_hWnd, SCI_SETSELBACK, m_Info.m_bSelectionBackColour, m_Info.m_SelectionBackColour);
	}
	/*是否启用选中背景色*/
	bool get_bselbackclor() const {
		return m_Info.m_bSelectionBackColour;
	}
	/*置选中背景色*/
	void set_selbackclor(COLORREF selbackclor) {
		m_Info.m_SelectionBackColour = selbackclor;
		::SendMessage(m_hWnd, SCI_SETSELBACK, m_Info.m_bSelectionBackColour, m_Info.m_SelectionBackColour);
	}
	/*是否启用选中前景色*/
	void set_bselforeclor(bool bselforeclor) {
		m_Info.m_bSelectionForeColour = bselforeclor;
		::SendMessage(m_hWnd, SCI_SETSELFORE, m_Info.m_bSelectionForeColour, m_Info.m_SelectionForeColour);
	}
	bool get_bselforeclor() const {
		return m_Info.m_bSelectionForeColour;
	}
	/*置选中前景色*/
	void set_selforeclor(COLORREF selbackclor) {
		m_Info.m_SelectionForeColour = selbackclor;
		::SendMessage(m_hWnd, SCI_SETSELFORE, m_Info.m_bSelectionForeColour, m_Info.m_SelectionForeColour);
	}
	/*置滚动条宽度*/
	void set_scrollbar_wigth(int wigth) {
		if (wigth <= 0)
		{
			if (m_bInDesignMode)
			{
				TaskDialog(GetActiveWindow(), NULL, L"警告", L"请设置大于1的宽度", L"非设计模式不在提示，但会失效", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			}
			return;
		}
		m_Info.m_ScrollbarWigtht = wigth;
		::SendMessage(m_hWnd, SCI_SETSCROLLWIDTH, m_Info.m_ScrollbarWigtht, 0);
	}
	/*取滚动条宽度*/
	int get_scrollbar_wigth() {
		m_Info.m_ScrollbarWigtht = ::SendMessage(m_hWnd, SCI_GETSCROLLWIDTH, 0, 0);
		return m_Info.m_ScrollbarWigtht;
	}
	bool onlyread() {
		m_Info.m_onlyread = static_cast<bool>(SendEditor(SCI_GETREADONLY));
		return m_Info.m_onlyread;
	}
	void onlyread(bool open) {
		m_Info.m_onlyread = open;

		SendEditor(SCI_SETREADONLY, (uptr_t)m_Info.m_onlyread);
	}
	int get_lexer() {
		m_Info.m_lexer = SendEditor(SCI_GETLEXER);
		return m_Info.m_lexer;
	}
	void set_lexer_name(LPCWSTR str) {
		SendEditor(SCI_SETLEXERLANGUAGE, 0, (sptr_t)unicode_to_utf8(str).c_str());
	}
	LPBYTE get_lexer_name(INT* size) {
		sptr_t len = SendEditor(SCI_GETLEXERLANGUAGE) + 1;
		std::string str(len, 0);
		m_lexname.clear();
		if (SendEditor(SCI_GETLEXERLANGUAGE, 0, (sptr_t)str.data()) > 0) {
			m_lexname = utf8_to_unicode(str.c_str());
			*size = (m_lexname.size() + 1) * sizeof(wchar_t);
		}
		return (LPBYTE)m_lexname.data();
	}
	void set_lexer(int lexer) {
		if (lexer < 0 || lexer>130 || lexer == 29 || lexer == 30)
		{
			if (m_bInDesignMode)
			{
				TaskDialog(GetActiveWindow(), NULL, L"警告", L"请设置有效词法分析器", L"非设计模式不在提示，但会失效", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			}
			return;
		}
		m_Info.m_lexer = lexer;
		SendEditor(SCI_SETLEXER, (uptr_t)m_Info.m_lexer);
	}
public:
	std::wstring m_wstr,m_lexname;
	std::string m_ansiStr;
	SciFnDirect m_fnDirect;
	sptr_t m_ptrDirect;
	sptr_t SendEditor(unsigned int iMessage, uptr_t wParam = 0, sptr_t lParam = 0)
	{
		return m_fnDirect(m_ptrDirect, iMessage, wParam, lParam);
	}
	CScintillaEditor(STD_ECTRL_CREATE_ARGS)
	{

		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);
		m_Info.iVer = DATA_VER_SCINTILLA_1;
		Scintilla_RegisterClasses(g_elibstl_hModule);
		m_hWnd = CreateWindowExW(0, L"Scintilla", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
			x, y, cx, cy, hParent, (HMENU)nID, g_elibstl_hModule, NULL);
		SendMessage(m_hWnd, SCI_STYLESETFONT, 0, (LPARAM)"Consolas");

		m_fnDirect = (SciFnDirect)SendMessage(m_hWnd, SCI_GETDIRECTFUNCTION, 0, 0);
		m_ptrDirect = (sptr_t)SendMessage(m_hWnd, SCI_GETDIRECTPOINTER, 0, 0);
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ESCINTILLADATA));
		}
		else
		{
			/*无滚动条*/
			m_Info.m_BackColour = 16777215;
			m_Info.m_ScrollbarWigtht = get_scrollbar_wigth();
			m_Info.m_ScrollbarMode = get_scrollbar_mode();
		}



		set_background_color(m_Info.m_BackColour);
		set_foreground_color(m_Info.m_ForeColour);
		set_selbackclor(m_Info.m_SelectionBackColour);
		set_selforeclor(m_Info.m_SelectionForeColour);
		set_scrollbar_mode(m_Info.m_ScrollbarMode);
		set_scrollbar_wigth(m_Info.m_ScrollbarWigtht);
		onlyread(m_Info.m_onlyread);
		set_lexer(m_Info.m_lexer);

		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		InitBase0(pAllData);
		FrameChanged();
	}




public:

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CScintillaEditor(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(ESCINTILLADATA), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ESCINTILLADATA));

		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}
	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 内容
			p->set_text(pPropertyVaule->m_szText);
			break;
		case 1:// 内容W
			p->set_text((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 2://背景颜色
			p->set_background_color(pPropertyVaule->m_clr);
			break;
		case 3://前景颜色
			p->set_foreground_color(pPropertyVaule->m_clr);
			break;
		case 4://是否启用选择背景颜色
			p->set_bselbackclor(pPropertyVaule->m_bool);
			break;
		case 5://选择背景颜色
			p->set_selbackclor(pPropertyVaule->m_clr);
			break;
		case 6://是否启用选择前景颜色
			p->set_bselforeclor(pPropertyVaule->m_bool);
			break;
		case 7://选择前景颜色
			p->set_selforeclor(pPropertyVaule->m_clr);
			break;
		case 8://滚动条模式
			p->set_scrollbar_mode(pPropertyVaule->m_int);
			break;
		case 9://滚动条宽度
			p->set_scrollbar_wigth(pPropertyVaule->m_int);
			break;
		case 10:/*只读*/
			p->onlyread(pPropertyVaule->m_bool);
			break;
		case 11:/*词法分析器*/
			p->set_lexer(pPropertyVaule->m_int);
			break;
		case 12:/*词法分析器*/
			p->set_lexer_name((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		}

		return FALSE;
	}
	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 内容
			//p->GetTextA();
			pPropertyVaule->m_szText = p->get_text();
			break;
		case 1:// 内容W
		{
			pPropertyVaule->m_data.m_pData = p->get_textW((size_t*) & pPropertyVaule->m_data.m_nDataSize);

		}break;
		case 2://背景颜色
			pPropertyVaule->m_clr = p->get_background_color();
			break;
		case 3://前景颜色
			pPropertyVaule->m_clr = p->get_foreground_color();
			break;
		case 4://是否启用选择背景颜色
			pPropertyVaule->m_bool = p->get_bselbackclor();
			break;
		case 5://选择背景颜色
			pPropertyVaule->m_clr = p->m_Info.m_SelectionBackColour;
			break;
		case 6://是否启用选择前景颜色
			pPropertyVaule->m_bool = p->get_bselforeclor();
			break;
		case 7://是否启用选择前景颜色
			pPropertyVaule->m_clr = p->m_Info.m_SelectionForeColour;
			break;
		case 8://滚动条模式
			pPropertyVaule->m_int = p->get_scrollbar_mode();
			break;
		case 9://滚动条宽度
			pPropertyVaule->m_int = p->get_scrollbar_wigth();
			break;
		case 10:/*只读*/
			pPropertyVaule->m_bool = p->onlyread();
			break;
		case 11:/*词法*/
			pPropertyVaule->m_int = p->get_lexer();
			break;
		case 12:/*词法名称*/
			pPropertyVaule->m_data.m_pData = p->get_lexer_name(&pPropertyVaule->m_data.m_nDataSize);
			break;
		}


		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		//PWSTR psz;
		*pblModified = FALSE;
		//switch (nPropertyIndex)
		//{
		//case 1:// 内容W
		//{
		//	if (elibstl::IntputBox(&psz, p->GetTextW()))
		//	{
		//		p->Set_TextW(psz);
		//		delete[] psz;
		//		*pblModified = TRUE;
		//	}
		//}
		//break;
		//}
		return FALSE;
	}
	static BOOL WINAPI EPropUpdateUI(HUNIT hUnit, INT nPropertyIndex)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		switch (nPropertyIndex)
		{
		case 5:// 背景颜色
			return p->m_Info.m_bSelectionBackColour;
		case 7:// 背景颜色
			return p->m_Info.m_bSelectionForeColour;
		case 9:// 滚动条最大值
			return p->m_Info.m_ScrollbarMode != 0;
		}

		return TRUE;
	}
	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 50;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CScintillaEditor, SCID_SCINTILLAPARENT, SCID_SCINTILLA)
ESTL_NAMESPACE_END





EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_Scintilla(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EInputW;
	case ITF_PROPERTY_UPDATE_UI:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EPropUpdateUI;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::ENotify;
	}
	return NULL;
}






static UNIT_PROPERTY s_Member_Scintilla[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"内容", "Text", "", UD_TEXT, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL},
	/*001*/  {"内容W", "TextW", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL},
	/*002*/	 {"默认背景颜色", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) ,  NULL},
	/*003*/	 {"默认前景颜色", "FKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) | UW_GROUP_LINE,  NULL},
	/*004*/	 {"启用被选中背景色", "Frame", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*005*/	 {"被选中背景色", "SelBKClr", "设置当前编辑框中选择内容文本的背景色", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT| UW_GROUP_LINE ,  NULL},
	/*006*/	 {"启用被选中前景色", "Frame", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*007*/	 {"被选中前景色", "SelBKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT | UW_GROUP_LINE ,  NULL},
	/*008*/  { "滚动条", "Scroll", "设置滚动条模式", UD_PICK_INT, _PROP_OS(OS_ALL), "无\0""横向滚动条\0""纵向滚动条\0""横向及纵向滚动条\0""\0" },
	/*009*/  {"滚动条最大值", "TextBKClr", "越大则滚动块越小，每次移动跨越幅度越大", UD_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, NULL},
	/*010*/  { "只读模式", "ReadOnly", "只读模式为“真”是代码风格编辑框只能读，不可以编辑。为“假”时可以编辑", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	/*011*/  { "词法分析器", "SETLEXER", "设置词法分析器，设置词法分析器后系统会对输入的文本进行语法加亮的处理", UD_PICK_INT, _PROP_OS(__OS_WIN) ,
	"容器\0"
	"无\0"               // SCLEX_CONTAINER - 0
"Python\0"          // SCLEX_HTML - 1
"C++\0"             // SCLEX_PYTHON - 2
"HTML\0"            // SCLEX_CPP - 3
"XML\0"             // SCLEX_HTML - 4
"Perl\0"            // SCLEX_XML - 5
"SQL\0"             // SCLEX_PERL - 6
"VB\0"              // SCLEX_SQL - 7
"Properties\0"      // SCLEX_VB - 8
"ErrorList\0"       // SCLEX_PROPERTIES - 9
"Makefile\0"        // SCLEX_ERRORLIST - 10
"Batch\0"           // SCLEX_MAKEFILE - 11
"Xcode\0"           // SCLEX_BATCH - 12
"LaTeX\0"           // SCLEX_XCODE - 13
"Lua\0"             // SCLEX_LATEX - 14
"Diff\0"            // SCLEX_LUA - 15
"Conf\0"            // SCLEX_DIFF - 16
"Pascal\0"          // SCLEX_CONF - 17
"Ave\0"             // SCLEX_PASCAL - 18
"Ada\0"             // SCLEX_AVE - 19
"Lisp\0"            // SCLEX_ADA - 20
"Ruby\0"            // SCLEX_LISP - 21
"Eiffel\0"          // SCLEX_RUBY - 22
"EiffelKW\0"        // SCLEX_EIFFEL - 23
"Tcl\0"             // SCLEX_EIFFELKW - 24
"NNCRontab\0"       // SCLEX_TCL - 25
"Bullant\0"         // SCLEX_NNCRONTAB - 26
"VBScript\0"        // SCLEX_BULLANT - 27
"Baan\0"            // SCLEX_VBSCRIPT - 28
"无效\0"//29
"无效\0"//30
"Matlab\0"          // SCLEX_BAAN - 31
"Scriptol\0"        // SCLEX_MATLAB - 32
"ASM\0"             // SCLEX_SCRIPTOL - 33
"CPPNoCase\0"       // SCLEX_ASM - 34
"Fortran\0"         // SCLEX_CPPNOCASE - 35
"F77\0"             // SCLEX_FORTRAN - 36
"CSS\0"             // SCLEX_F77 - 37
"POV\0"             // SCLEX_CSS - 38
"LOUT\0"            // SCLEX_POV - 39
"EScript\0"         // SCLEX_LOUT - 40
"PS\0"              // SCLEX_ESCRIPT - 41
"NSIS\0"            // SCLEX_PS - 42
"MMIXAL\0"          // SCLEX_NSIS - 43
"CLW\0"             // SCLEX_MMIXAL - 44
"CLWNoCase\0"       // SCLEX_CLW - 45
"LOT\0"             // SCLEX_CLWNOCASE - 46
"YAML\0"            // SCLEX_LOT - 47
"TeX\0"             // SCLEX_YAML - 48
"MetaPost\0"        // SCLEX_TEX - 49
"PowerBASIC\0"      // SCLEX_METAPOST - 50
"Forth\0"           // SCLEX_POWERBASIC - 51
"Erlang\0"          // SCLEX_FORTH - 52
"Octave\0"          // SCLEX_ERLANG - 53
"MSSQL\0"           // SCLEX_OCTAVE - 54
"Verilog\0"         // SCLEX_MSSQL - 55
"Kix\0"             // SCLEX_VERILOG - 56
"Gui4Cli\0"         // SCLEX_KIX - 57
"Specman\0"         // SCLEX_GUI4CLI - 58
"AutoIt\0"          // SCLEX_SPECMAN - 59
"APDL\0"            // SCLEX_AU3 - 60
"Bash\0"            // SCLEX_APDL - 61
"ASN.1\0"           // SCLEX_BASH - 62
"VHDL\0"            // SCLEX_ASN1 - 63
"CAML\0"            // SCLEX_VHDL - 64
"BlitzBasic\0"      // SCLEX_CAML - 65
"PureBasic\0"       // SCLEX_BLITZBASIC - 66
"Haskell\0"         // SCLEX_PUREBASIC - 67
"PHPScript\0"       // SCLEX_HASKELL - 68
"TADS3\0"           // SCLEX_PHPSCRIPT - 69
"Rebol\0"           // SCLEX_TADS3 - 70
"Smalltalk\0"       // SCLEX_REBOL - 71
"Flagship\0"        // SCLEX_SMALLTALK - 72
"Csound\0"          // SCLEX_FLAGSHIP - 73
"FreeBASIC\0"       // SCLEX_CSOUND - 74
"InnoSetup\0"       // SCLEX_FREEBASIC - 75
"Opal\0"            // SCLEX_INNOSETUP - 76
"Spice\0"           // SCLEX_OPAL - 77
"D\0"               // SCLEX_SPICE - 78
"CMake\0"           // SCLEX_D - 79
"GAP\0"             // SCLEX_CMAKE - 80
"PL/M\0"            // SCLEX_GAP - 81
"Progress\0"        // SCLEX_PLM - 82
"Abaqus\0"          // SCLEX_PROGRESS - 83
"Asymptote\0"       // SCLEX_ABAQUS - 84
"R\0"               // SCLEX_ASYMPTOTE - 85
"Magik\0"           // SCLEX_R - 86
"PowerShell\0"      // SCLEX_MAGIK - 87
"MySQL\0"           // SCLEX_POWERSHELL - 88
"PO\0"              // SCLEX_MYSQL - 89
"TAL\0"             // SCLEX_PO - 90
"COBOL\0"           // SCLEX_TAL - 91
"TACL\0"            // SCLEX_COBOL - 92
"Sorcus\0"          // SCLEX_TACL - 93
"PowerPro\0"        // SCLEX_SORCUS - 94
"Nimrod\0"          // SCLEX_POWERPRO - 95
"SML\0"             // SCLEX_NIMROD - 96
"Markdown\0"        // SCLEX_SML - 97
"Txt2Tags\0"        // SCLEX_MARKDOWN - 98
"A68K\0"            // SCLEX_TXT2TAGS - 99
"Modula\0"          // SCLEX_A68K - 100
"CoffeeScript\0"    // SCLEX_MODULA - 101
"TCMD\0"            // SCLEX_COFFEESCRIPT - 102
"AVS\0"             // SCLEX_TCMD - 103
"ECL\0"             // SCLEX_AVS - 104
"OScript\0"         // SCLEX_ECL - 105
"VisualProlog\0"    // SCLEX_OSCRIPT - 106
"LiterateHaskell\0" // SCLEX_VISUALPROLOG - 107
"sttxt\0"           // SCLEX_LITERATEHASKELL - 108
"KVIrc\0"           // SCLEX_STTXT - 109
"Rust\0"            // SCLEX_KVIRC - 110
"DMAP\0"            // SCLEX_RUST - 111
"AS\0"              // SCLEX_DMAP - 112
"DMIS\0"            // SCLEX_AS - 113
"Registry\0"        // SCLEX_DMIS - 114
"BibTeX\0"          // SCLEX_REGISTRY - 115
"SREC\0"            // SCLEX_BIBTEX - 116
"IHEX\0"            // SCLEX_SREC - 117
"TEHEX\0"           // SCLEX_IHEX - 118
"JSON\0"            // SCLEX_TEHEX - 119
"EDIFACT\0"         // SCLEX_JSON - 120
"Indent\0"          // SCLEX_EDIFACT - 121
"Maxima\0"          // SCLEX_INDENT - 122
"Stata\0"           // SCLEX_MAXIMA - 123
"SAS\0"             // SCLEX_STATA - 124
"Nim\0"             // SCLEX_SAS - 125
"CIL\0"             // SCLEX_NIM - 126
"X12\0"             // SCLEX_CIL - 127
"DataFlex\0"        // SCLEX_X12 - 128
"Hollywood\0"       // SCLEX_DATAFLEX - 129
"Raku\0"            // SCLEX_HOLLYWOOD - 130
	"\0" },
	/*012*/	 { "词法分析器名称", "Text", R"(设置当前所欲使用的内置词法分析器类型,与"词法分析器"属性不同的是本属性使用词法分析器的文本名称来选择)", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL },
	



	///*002*/{ "空白区域填充模式", "WhiteSpace", "设置空白区域填充模式，空白区域指输入的空格字符或是Tab字符所造成的无可视字符区域，使用点填充空格字符，使用尖头填充Tab字符", UD_PICK_INT, _PROP_OS(OS_ALL), "无\0""总是填充\0""首字符使用后填充\0""\0" },
	///*003*/{ "空白区域前景颜色", "WhiteSpaceFore", "设置空白区域前景颜色", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*004*/{ "空白区域背景颜色", "WhiteSpaceBack", "设置空白区域前景颜色", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*005*/{ "光标类型", "CursorType", "光标类型", UD_PICK_INT, _PROP_OS(OS_ALL), "普通\0""忙\0""\0" },
	///*006*/{ "行结束标志", "EolMode", "设置行结束标志，注：Mac使用\\r，Unix使用\\n，DOS，WINDOWS使用\\r\\n", UD_PICK_INT, _PROP_OS(OS_ALL), "CRLF模式\0""CR模式\0""LF模式\0""\0" },
	///*007*/{ "显示行结束标志", "ViewEol", "显示行结束标志", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*008*/{ "选择文本前景色", "SelForeColor", "选择文本后，文本的前景色", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*009*/{ "选择文本背景色", "SelBackColor", "选择文本后，文本的背景色", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*010*/{ "光标颜色", "CaretForeColor", "光标的颜色", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*011*/{ "光标所在行颜色模式", "CaretLineVisible", "是否使用光标所在行的背景颜色", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*012*/{ "光标所在行背景颜色", "CaretLineBackColor", "光标所在行背景颜色，“光标所在行颜色模式”为真时有效", UD_COLOR, _PROP_OS(OS_ALL) | UW_HAS_INDENT, NULL },
	///*013*/{ "光标闪烁间隔", "CaretPeriod", "光标闪烁的间隔周期", UD_INT, _PROP_OS(OS_ALL), NULL },
	///*014*/{ "光标宽度", "CaretWidth", "光标的宽度，单位为像素", UD_PICK_INT, _PROP_OS(OS_ALL), " 0像素\0"" 1像素\0"" 2像素\0"" 3像素\0""\0" },
	///*015*/{ "编码", "SetCodePage", "设置字符编码", UD_PICK_INT, _PROP_OS(OS_ALL), "ANSI\0""UNICODE\0""\0" },
	///*016*/{ "显示缩进向导", "SetIndentationGuides", "显示缩进向导，缩进向导是缩进边缘的一条虚线", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*017*/{ "自动换行", "SetWrapMode", "自动换行", UD_BOOL, _PROP_OS(OS_ALL), NULL },

};



ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtScintilla = {
	"火花编辑框",//中文名称
	"Scintilla",//英文名称
	"本控件有诸多属性改变后需要重新创建控件，应尽量在设计时确定属性值",//说明
	0,//命令数量
	0,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_SCINTILLA,//资源ID
	0,
	0,//事件
	ARRAYSIZE(s_Member_Scintilla),//属性数
	s_Member_Scintilla,//属性指针
	libstl_GetInterface_Scintilla,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END

