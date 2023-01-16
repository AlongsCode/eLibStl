#include"ElibHelp.h"

#ifdef _WIN32
#undef UNICODE
#include <windows.h>
#include<tlhelp32.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif



bool kill_process_w(const std::wstring& process_name_or_window_title) {
	// 用于存储进程 ID 的变量
	unsigned int process_id = 0;

#ifdef _WIN32
	// 在 Windows 系统上使用 FindWindow 函数查找窗口句柄
	HWND window_handle = FindWindowW(0, process_name_or_window_title.c_str());
	if (window_handle) {
		GetWindowThreadProcessId(window_handle, (LPDWORD)&process_id);
	}

	// 如果找到了窗口句柄，就不需要再枚举进程了
	if (process_id == 0) {
		// 枚举系统中的所有进程
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE) {
			return false;
		}

		PROCESSENTRY32W process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32W);

		// 遍历每一个进程
		if (Process32FirstW(snapshot_handle, &process_entry)) {
			do {
				// 匹配进程名称
				if (process_name_or_window_title == std::wstring(process_entry.szExeFile)) {
					process_id = process_entry.th32ProcessID;
					break;
				}
			} while (Process32NextW(snapshot_handle, &process_entry));
		}
		CloseHandle(snapshot_handle);
	}


#else
	// 在 Linux 系统上使用 ps 命令查找进程 ID
	std::wstring command = L"ps -e -o pid,comm | grep " + process_name_or_window_title;
	std::FILE* process_id_file = _wpopen(command.c_str(), L"r");
	if (process_id_file) {
		std::fscanf(process_id_file, "%d", &process_id);
		_pclose(process_id_file);
	}
#endif
	// 如果没有找到进程 ID，返回 false
	if (process_id == 0) {
		return false;
	}

	// 在 Windows 系统上使用 TerminateProcess 函数终止进程
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	int kill_result = _wsystem((L"kill " + std::to_wstring(process_id)).c_str());
	// 如果 kill 命令返回 0，表示成功终止进程
	return kill_result == 0;
#endif
}
bool kill_process_w(const std::string& process_name_or_window_title) {
	// 用于存储进程 ID 的变量
	unsigned int process_id = 0;

#ifdef _WIN32
	// 在 Windows 系统上使用 FindWindow 函数查找窗口句柄
	HWND window_handle = FindWindowA(0, process_name_or_window_title.c_str());
	if (window_handle) {
		GetWindowThreadProcessId(window_handle, (LPDWORD)&process_id);
	}

	// 如果找到了窗口句柄，就不需要再枚举进程了
	if (process_id == 0) {
		// 枚举系统中的所有进程
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE) {
			return false;
		}

		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32W);

		// 遍历每一个进程
		if (Process32First(snapshot_handle, &process_entry)) {
			do {
				// 匹配进程名称
				if (process_name_or_window_title == std::string(process_entry.szExeFile)) {
					process_id = process_entry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot_handle, &process_entry));
		}
		CloseHandle(snapshot_handle);
	}


#else
	// 在 Linux 系统上使用 ps 命令查找进程 ID
	std::string command = "ps -e -o pid,comm | grep " + process_name_or_window_title;
	std::FILE* process_id_file = _popen(command.c_str(), "r");
	if (process_id_file) {
		std::fscanf(process_id_file, "%d", &process_id);
		_pclose(process_id_file);
	}
#endif
	// 如果没有找到进程 ID，返回 false
	if (process_id == 0) {
		return false;
	}

	// 在 Windows 系统上使用 TerminateProcess 函数终止进程
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	int kill_result = std::system(("kill " + std::to_string(process_id)).c_str());
	// 如果 kill 命令返回 0，表示成功终止进程
	return kill_result == 0;
#endif
}
bool kill_process_w(unsigned int process_id) {
	if (process_id == 0)
	{
		return 0;
	}
	// 在 Windows 系统上使用 TerminateProcess 函数终止进程
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	// 在其他平台上使用 kill 命令终止进程
	int kill_result = std::system(("kill " + std::to_string(process_id)).c_str());
	// 如果 kill 命令返回 0，表示成功终止进程
	return kill_result == 0;
#endif
}


static ARG_INFO Args[] =
{
	{
		/*name*/    "欲结束的进程",
		/*explain*/ ("要终止进程的进程ID、进程名称或窗口标题的文本型或宽文本型"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_kill_process_w(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BOOL ret = FALSE;
	if (pArgInf->m_dtDataType == SDT_BIN)
	{
		ret = kill_process_w(std::wstring(elibkrnln::args_to_wsdata(pArgInf, 0)));
	}
	else if (pArgInf->m_dtDataType == SDT_TEXT)
	{
		ret = kill_process_w(std::string(elibkrnln::args_to_sdata(pArgInf, 0)));
	}
	else if (pArgInf->m_dtDataType == SDT_INT)
	{
		ret = kill_process_w(pArgInf[0].m_int);
	}
	pRetData->m_int = ret;
}

FucInfo kill_process = { {
		/*ccname*/  ("结束进程"),
		/*egname*/  (""),
		/*explain*/ ("强制结束某一指定进程"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_kill_process_w ,"Fn_kill_process_w" };
