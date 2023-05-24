#include"ElibHelp.h"

#ifdef _WIN32
#undef UNICODE
#include <windows.h>
#include<tlhelp32.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif



inline bool kill_process_w(const std::wstring& process_name_or_window_title) {
	// ���ڴ洢���� ID �ı���
	unsigned int process_id = 0;

#ifdef _WIN32
	// �� Windows ϵͳ��ʹ�� FindWindow �������Ҵ��ھ��
	HWND window_handle = FindWindowW(0, process_name_or_window_title.c_str());
	if (window_handle) {
		GetWindowThreadProcessId(window_handle, (LPDWORD)&process_id);
	}

	// ����ҵ��˴��ھ�����Ͳ���Ҫ��ö�ٽ�����
	if (process_id == 0) {
		// ö��ϵͳ�е����н���
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE) {
			return false;
		}

		PROCESSENTRY32W process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32W);

		// ����ÿһ������
		if (Process32FirstW(snapshot_handle, &process_entry)) {
			do {
				// ƥ���������
				if (process_name_or_window_title == std::wstring(process_entry.szExeFile)) {
					process_id = process_entry.th32ProcessID;
					break;
				}
			} while (Process32NextW(snapshot_handle, &process_entry));
		}
		CloseHandle(snapshot_handle);
	}


#else
	// �� Linux ϵͳ��ʹ�� ps ������ҽ��� ID
	std::wstring command = L"ps -e -o pid,comm | grep " + process_name_or_window_title;
	std::FILE* process_id_file = _wpopen(command.c_str(), L"r");
	if (process_id_file) {
		std::fscanf(process_id_file, "%d", &process_id);
		_pclose(process_id_file);
	}
#endif
	// ���û���ҵ����� ID������ false
	if (process_id == 0) {
		return false;
	}

	// �� Windows ϵͳ��ʹ�� TerminateProcess ������ֹ����
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	int kill_result = _wsystem((L"kill " + std::to_wstring(process_id)).c_str());
	// ��� kill ����� 0����ʾ�ɹ���ֹ����
	return kill_result == 0;
#endif
}
inline bool kill_process_w(const std::string& process_name_or_window_title) {
	// ���ڴ洢���� ID �ı���
	unsigned int process_id = 0;

#ifdef _WIN32
	// �� Windows ϵͳ��ʹ�� FindWindow �������Ҵ��ھ��
	HWND window_handle = FindWindowA(0, process_name_or_window_title.c_str());
	if (window_handle) {
		GetWindowThreadProcessId(window_handle, (LPDWORD)&process_id);
	}

	// ����ҵ��˴��ھ�����Ͳ���Ҫ��ö�ٽ�����
	if (process_id == 0) {
		// ö��ϵͳ�е����н���
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot_handle == INVALID_HANDLE_VALUE) {
			return false;
		}

		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32W);

		// ����ÿһ������
		if (Process32First(snapshot_handle, &process_entry)) {
			do {
				// ƥ���������
				if (process_name_or_window_title == std::string(process_entry.szExeFile)) {
					process_id = process_entry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot_handle, &process_entry));
		}
		CloseHandle(snapshot_handle);
	}


#else
	// �� Linux ϵͳ��ʹ�� ps ������ҽ��� ID
	std::string command = "ps -e -o pid,comm | grep " + process_name_or_window_title;
	std::FILE* process_id_file = _popen(command.c_str(), "r");
	if (process_id_file) {
		std::fscanf(process_id_file, "%d", &process_id);
		_pclose(process_id_file);
	}
#endif
	// ���û���ҵ����� ID������ false
	if (process_id == 0) {
		return false;
	}

	// �� Windows ϵͳ��ʹ�� TerminateProcess ������ֹ����
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	int kill_result = std::system(("kill " + std::to_string(process_id)).c_str());
	// ��� kill ����� 0����ʾ�ɹ���ֹ����
	return kill_result == 0;
#endif
}
inline bool kill_process_w(unsigned int process_id) {
	if (process_id == 0)
	{
		return 0;
	}
	// �� Windows ϵͳ��ʹ�� TerminateProcess ������ֹ����
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	// ������ƽ̨��ʹ�� kill ������ֹ����
	int kill_result = std::system(("kill " + std::to_string(process_id)).c_str());
	// ��� kill ����� 0����ʾ�ɹ���ֹ����
	return kill_result == 0;
#endif
}


static ARG_INFO Args[] =
{
	{
		/*name*/    "�������Ľ���",
		/*explain*/ ("Ҫ��ֹ���̵Ľ���ID���������ƻ򴰿ڱ�����ı��ͻ���ı���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_kill_process_w(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BOOL ret = FALSE;
	if (pArgInf->m_dtDataType == DATA_TYPE::SDT_BIN)
	{
		ret = kill_process_w(std::wstring(elibstl::args_to_wsdata(pArgInf, 0)));
	}
	else if (pArgInf->m_dtDataType == DATA_TYPE::SDT_TEXT)
	{
		ret = kill_process_w(std::string(elibstl::args_to_sdata(pArgInf, 0)));
	}
	else if (pArgInf->m_dtDataType == DATA_TYPE::SDT_INT)
	{
		ret = kill_process_w(pArgInf[0].m_int);
	}
	pRetData->m_int = ret;
}

FucInfo kill_process = { {
		/*ccname*/  ("��������"),
		/*egname*/  (""),
		/*explain*/ ("ǿ�ƽ���ĳһָ������"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_kill_process_w ,"Fn_kill_process_w" };
