#include"ElibHelp.h"
#include <intrin.h>
inline  bool IsInsideVirtualMachine()
{
	bool rc = false;

	// ����ǲ���������VirtualPC
	ULONG size = 0;
	PVOID buffer = nullptr;
	DWORD result = GetSystemFirmwareTable('VPC3', 0, buffer, size);
	if (result == ERROR_INSUFFICIENT_BUFFER) {
		buffer = new BYTE[size];
		result = GetSystemFirmwareTable('VPC3', 0, buffer, size);
	}
	if (buffer) {
		delete[] buffer;
		rc = true;
	}

	// �ټ���ǲ���������VMware
	int cpuinfo[4] = { 0 };
	__cpuid(cpuinfo, 0);
	if (cpuinfo[0] >= 1) {
		__cpuid(cpuinfo, 1);
		if ((cpuinfo[2] & 0x80000000) && (strcmp((const char*)&cpuinfo[3], "VMwareVMware") == 0)) {
			rc = true;
		}
	}

	return rc;
}
EXTERN_C void Fn_IsInsideVirtualMachine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = IsInsideVirtualMachine();
}
FucInfo g_is_inside_virtual_machine = { {
		/*ccname*/  ("�Ƿ������������"),
		/*egname*/  (""),
		/*explain*/ ("����Ƿ�������VirtualPC��VMware��"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_IsInsideVirtualMachine ,"Fn_IsInsideVirtualMachine" };