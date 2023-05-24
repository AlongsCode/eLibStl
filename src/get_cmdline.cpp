#include"ElibHelp.h"

std::vector<LPBYTE> get_cmdline()
{
	std::vector<LPBYTE> saryArgs;
	// Initialize the output vector.
	saryArgs = {};

	// Get the command-line arguments.
	const wchar_t* conmline = GetCommandLineW();
	if (!conmline)
	{
		return saryArgs;
	}

	// Inline the SkipSpaces function.
	const wchar_t* ps = conmline;
	while (*ps != L'\0')
	{
		if (!iswspace(*ps))
			break;
		ps++;
	}

	// Set psCommand to the value of conmline.
	// This will ensure that the first command-line argument is not skipped.
	const wchar_t* psCommand = ps;

	// Skip the program name.
	wchar_t ch = L' ';
	if (*psCommand == L'\"')
	{
		ch = L'\"';
		psCommand++;
	}
	while (*psCommand != ch && *psCommand != L'\0')
		psCommand++;

	if (*psCommand != L'\0')
		psCommand++;

	// Do not skip the first space.
	// This will ensure that the first command-line argument is not skipped.
	// if (ch != L' ' && *psCommand == L' ')
	//     psCommand++;    // Skip the first space.

	// Extract the command-line arguments.
	while (*psCommand != L'\0')
	{
		if (*psCommand == L'\"')
		{
			psCommand++;

			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && *ps != L'\"')
				ps++;

			saryArgs.push_back(elibstl::clone_textw(std::wstring(psCommand, ps - psCommand)));

			psCommand = ps;
			if (*psCommand != L'\0')
				psCommand++;
		}
		else if (!iswspace(*psCommand))
		{
			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && !iswspace(*ps))
				ps++;

			saryArgs.push_back(elibstl::clone_textw(std::wstring(psCommand, ps - psCommand)));
			psCommand = ps;
		}
		else
		{
			psCommand++;
		}
	}

	return saryArgs;
}




EXTERN_C void Fn_get_cmdline_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::vector<LPBYTE> ret = get_cmdline();
	pRetData->m_pAryData = elibstl::create_array<LPBYTE>(ret.data(), ret.size());
}

FucInfo get_cmdline_W = { {
		/*ccname*/  ("取命令行W"),
		/*egname*/  ("GetCmdLineW"),
		/*explain*/ ("本命令可以取出在启动易程序时附加在其可执行文件名后面的所有以空格分隔的命令行文本段。"),
		/*category*/8,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_cmdline_W ,"Fn_get_cmdline_W" };

