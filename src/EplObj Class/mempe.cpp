#include"EcontrolHelp.h"
#include <algorithm>
//#include"memload\MemoryModule.h"

#pragma comment (lib, "winmm.lib")
#pragma warning(disable:28159)
using namespace std;
//using namespace eMemoryModule;


namespace {
typedef int (APIENTRY* DLLMAIN)(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
typedef int (APIENTRY* WINMAIN)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
typedef DWORD(WINAPI* FRCALLBACK)(LPCSTR pModuleName, LPCSTR pProcName, DWORD pFR_lParam);

//
//	内部函数
//
LPVOID VirAlloc(LPVOID LpAddress, SIZE_T DwSize);
BOOL VirFree(LPVOID LpAddress);
UINT GetAlignedSize(UINT Origin, UINT Alignment);
VOID DoRelocation(DWORD NewBase);
BOOL FillRavAddress(DWORD ImageBase, FRCALLBACK pFR_CallBack, DWORD pFR_lParam);


//
//	导出函数
//
LPBYTE WINAPI _LoadLibrary(LPCBYTE LpLibData, FRCALLBACK pFR_CallBack, DWORD pFR_lParam);
BOOL WINAPI _FreeLibrary(LPBYTE hLibModule);
FARPROC WINAPI _GetProcAddress(LPBYTE hLibModule, LPCSTR lpProcName);
DWORD WINAPI _GetEntryPoint(LPBYTE hLibModule);







LPBYTE WINAPI _LoadLibrary(LPCBYTE LpLibData, FRCALLBACK pFR_CallBack, DWORD pFR_lParam)
{
	if (!LpLibData)
		return NULL;

	PIMAGE_DOS_HEADER LpDosHeader = (PIMAGE_DOS_HEADER)LpLibData;
	PIMAGE_NT_HEADERS LpNtHeader = (PIMAGE_NT_HEADERS)(LpLibData + LpDosHeader->e_lfanew);

	//
	//	检查有效性
	//
	if (LpDosHeader->e_magic != IMAGE_DOS_SIGNATURE)	//	MZ
		return NULL;

	if (LpNtHeader->Signature != IMAGE_NT_SIGNATURE)	//	PE
		return NULL;

	if (!(LpNtHeader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE))	//	可执行
		return NULL;

	//
	//	计算映像大小
	//
	PIMAGE_SECTION_HEADER SectionHeader;
	DWORD SizeOfImage = LpNtHeader->OptionalHeader.SizeOfImage;

	for (int i = 0; i < LpNtHeader->FileHeader.NumberOfSections; i++)
	{
		SectionHeader = (PIMAGE_SECTION_HEADER)(LpLibData
			+ LpDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS)
			+ i * sizeof(IMAGE_SECTION_HEADER));

		SizeOfImage = max(SizeOfImage, GetAlignedSize(
			SectionHeader->VirtualAddress + max(SectionHeader->SizeOfRawData,
				SectionHeader->Misc.VirtualSize), LpNtHeader->OptionalHeader.SectionAlignment));
	}
	if (!SizeOfImage)
		return NULL;

	//
	//	分配内存, 拷贝数据
	//
	LPBYTE hLibModule = (LPBYTE)VirAlloc((LPVOID)LpNtHeader->OptionalHeader.ImageBase, SizeOfImage);
	if (!hLibModule)
		return NULL;

	memcpy(hLibModule, LpLibData, LpDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS)
		+ LpNtHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER));

	for (int i = 0; i < LpNtHeader->FileHeader.NumberOfSections; i++)
	{
		SectionHeader = (PIMAGE_SECTION_HEADER)(LpLibData + LpDosHeader->e_lfanew
			+ sizeof(IMAGE_NT_HEADERS) + i * sizeof(IMAGE_SECTION_HEADER));

		if (SectionHeader->SizeOfRawData && SectionHeader->VirtualAddress)
			memcpy(hLibModule + SectionHeader->VirtualAddress, LpLibData
				+ SectionHeader->PointerToRawData, SectionHeader->SizeOfRawData);
	}

	//
	//	重定位
	//
	if (LpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size)
		DoRelocation((DWORD)hLibModule);

	//
	//	填充导入表
	//
	if (LpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
	{
		if (!FillRavAddress((DWORD)hLibModule, pFR_CallBack, pFR_lParam))
		{
			VirFree(hLibModule);
			return NULL;
		}
	}

	//
	//	执行入口代码
	//
	if (LpNtHeader->FileHeader.Characteristics & IMAGE_FILE_DLL)	//	是否为 DLL
	{
		DLLMAIN _DllMain = (DLLMAIN)(hLibModule + LpNtHeader->OptionalHeader.AddressOfEntryPoint);
		if (!_DllMain(NULL, DLL_PROCESS_ATTACH, NULL))
		{
			_DllMain(NULL, DLL_PROCESS_DETACH, NULL);
			VirFree(hLibModule);
			return NULL;
		}
	}

	return hLibModule;
}

BOOL WINAPI _FreeLibrary(LPBYTE hLibModule)
{
	if (!hLibModule)
		return false;

	PIMAGE_DOS_HEADER LpDosHeader = (PIMAGE_DOS_HEADER)hLibModule;
	PIMAGE_NT_HEADERS LpNtHeader = (PIMAGE_NT_HEADERS)(hLibModule + LpDosHeader->e_lfanew);

	//
	//	执行入口代码
	//
	if (LpNtHeader->FileHeader.Characteristics & IMAGE_FILE_DLL)	//	是否为 DLL
	{
		DLLMAIN _DllMain = (DLLMAIN)(hLibModule + LpNtHeader->OptionalHeader.AddressOfEntryPoint);
		_DllMain(0, DLL_PROCESS_DETACH, 0);
	}

	return VirFree(hLibModule);
}

FARPROC WINAPI _GetProcAddress(LPBYTE hLibModule, LPCSTR lpProcName)
{
	if (!hLibModule || !lpProcName)
		return NULL;

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hLibModule;
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(hLibModule + pDosHeader->e_lfanew);

	if (!pNtHeader->OptionalHeader.
		DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size)	//	是否存在导出表
		return NULL;

	PIMAGE_EXPORT_DIRECTORY pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)(hLibModule
		+ pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	PDWORD AddressOfNames = (PDWORD)(hLibModule + pExportDirectory->AddressOfNames);
	PDWORD AddressOfFunctions = (PDWORD)(hLibModule + pExportDirectory->AddressOfFunctions);
	PWORD AddressOfNameOrdinals = (PWORD)(hLibModule + pExportDirectory->AddressOfNameOrdinals);
	LPSTR pProcName;
	DWORD Ordinals = (DWORD)lpProcName - pExportDirectory->Base;

	//
	//	寻找指定函数
	//

	if (Ordinals >= 0 && Ordinals <= pExportDirectory->NumberOfFunctions)	//	是否为序号
	{
		return (FARPROC)(hLibModule + AddressOfFunctions[Ordinals]);
	}
	else	//	以名称导出的函数
	{
		Ordinals = 0;
		for (DWORD i = 0; i < pExportDirectory->NumberOfNames; i++)
		{
			pProcName = (LPSTR)(hLibModule + AddressOfNames[i]);
			Ordinals = AddressOfNameOrdinals[i];

			if (Ordinals >= 0 && Ordinals <= pExportDirectory->NumberOfFunctions)
			{
				if (!strcmp(lpProcName, pProcName))
				{
					return (FARPROC)(hLibModule + AddressOfFunctions[Ordinals]);
				}
			}
		}
	}

	return NULL;
}



DWORD WINAPI _GetEntryPoint(LPBYTE hLibModule)
{
	return (DWORD)(hLibModule + ((PIMAGE_NT_HEADERS)(hLibModule
		+ ((PIMAGE_DOS_HEADER)hLibModule)->e_lfanew))->OptionalHeader.AddressOfEntryPoint);
}


LPVOID VirAlloc(LPVOID LpAddress, SIZE_T DwSize)
{
	LPVOID pMem;

	//
	//	分配内存
	//
	pMem = VirtualAlloc(LpAddress, DwSize,	//	指定基址
		MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pMem)
		pMem = VirtualAlloc(NULL, DwSize,	//	随机基址
			MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	return pMem;
}

BOOL VirFree(LPVOID LpAddress)
{
	//
	//	释放内存
	//
	return VirtualFree(LpAddress, NULL, MEM_RELEASE);
}

UINT GetAlignedSize(UINT Origin, UINT Alignment)
{
	//
	//	计算对齐后大小
	//
	return (Origin + Alignment - 1) / Alignment * Alignment;
}

VOID DoRelocation(DWORD NewBase)
{
	PIMAGE_DOS_HEADER LpDosHeader = (PIMAGE_DOS_HEADER)NewBase;
	PIMAGE_NT_HEADERS LpNtHeader = (PIMAGE_NT_HEADERS)(NewBase + LpDosHeader->e_lfanew);
	DWORD Delta = NewBase - LpNtHeader->OptionalHeader.ImageBase;
	DWORD Offset = LpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	PIMAGE_BASE_RELOCATION LpBaseRelocation = (PIMAGE_BASE_RELOCATION)(NewBase + Offset);
	short LocData;
	DWORD Address;

	//
	//	重定位
	//
	do
	{
		for (DWORD i = 0; i < (LpBaseRelocation->SizeOfBlock - 8) / 2; i++)
		{
			LocData = *((PWORD)(NewBase + Offset + 8 + i * 2));
			if ((LocData & 61440) == 12288)
			{
				Address = NewBase + LpBaseRelocation->VirtualAddress + (LocData & 4095);
				*((PDWORD)Address) = *((PDWORD)Address) + Delta;
			}
		}
		Offset += LpBaseRelocation->SizeOfBlock;
		LpBaseRelocation = (PIMAGE_BASE_RELOCATION)(NewBase + Offset);
	} while (LpBaseRelocation->VirtualAddress);
}

BOOL FillRavAddress(DWORD ImageBase, FRCALLBACK pFR_CallBack, DWORD pFR_lParam)
{
	PIMAGE_DOS_HEADER LpDosHeader = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS LpNtHeader = (PIMAGE_NT_HEADERS)(ImageBase + LpDosHeader->e_lfanew);
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(ImageBase + LpNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	DWORD dwRealIAT;
	HMODULE hModule;
	LPCSTR pModuleName;
	int i, j = 0;
	DWORD dwProcName;
	LPCSTR pProcName;
	DWORD dwFunction;
	char pStr[64 + 1];
	BOOL bRet = TRUE;

	//
	//	填充导入表
	//

	while (ImportDescriptor[j].FirstThunk)
	{
		pModuleName = (LPCSTR)(ImageBase	//	模块名
			+ ImportDescriptor[j].Name);
		hModule = LoadLibraryA(pModuleName);

		i = 0;
		while (((PDWORD)(ImageBase + ImportDescriptor[j].FirstThunk))[i])
		{
			if (((PDWORD)(ImageBase + ImportDescriptor[j].OriginalFirstThunk))[i])
				dwRealIAT = ((PDWORD)(ImageBase + ImportDescriptor[j].OriginalFirstThunk))[i];
			else
				dwRealIAT = ((PDWORD)(ImageBase + ImportDescriptor[j].FirstThunk))[i];

			if (dwRealIAT & IMAGE_ORDINAL_FLAG32)	//	是否为序号
			{
				dwProcName = dwRealIAT & 65535;
				wsprintfA(pStr, "%d", dwProcName);
				pProcName = pStr;
			}
			else	//	符号
				pProcName =		//	函数名
				(LPCSTR)(dwProcName = ImageBase + dwRealIAT + 2);

			if (pFR_CallBack)	//	是否需要询问 ( 回调 )
				dwFunction = pFR_CallBack(pModuleName, pProcName, pFR_lParam);
			else
				dwFunction = 0;

			if (!dwFunction)	//	函数地址是否为 0
				dwFunction = (DWORD)GetProcAddress(hModule, (LPCSTR)dwProcName);
			if (!dwFunction)
			{
				return FALSE;
			}

			((PDWORD)(ImageBase + ImportDescriptor[j].FirstThunk))[i] = dwFunction;

			i++;
		}
		j++;
	}

	return TRUE;
}

}
namespace {

	class MemoryModule
	{
	public:
		MemoryModule() = default;
		~MemoryModule() {
			if (hMode)
				_FreeLibrary(hMode);
			
		};
		auto MemoryLoadLibrary(const elibstl::ebin* pData) {
			if (hMode)
				_FreeLibrary(hMode);
		
			hMode = ::_LoadLibrary(pData->m_data, nullptr, 0);

			return hMode != NULL;
		}
		auto MemoryGetProcAddress(const char* fun)-> FARPROC {
			if (!hMode || !fun)
				return nullptr;
			return ::_GetProcAddress(hMode, fun);
		}
		auto MemoryCallEntryPoint() {
			if (!hMode)
				return DWORD{};
			return ::_GetEntryPoint(hMode);
		}

	private:
		LPBYTE hMode{ nullptr };
	};


}






static INT s_dtCmdIndexcommobj_MemoryModule_play[] = { 351,352,353,354,355,356 };



//构造
EXTERN_C void fn_MemoryModule_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<MemoryModule>(pArgInf);
	self = new MemoryModule;
}
//构造
FucInfo Fn_MemoryModule_structure = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/  _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_CONSTURCT_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,ESTLFNAME(fn_MemoryModule_structure) };
static ARG_INFO s_CopyArgs[] =
{
	{
		/*name*/    "拷贝",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   DATA_TYPE(6),
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
//复制
EXTERN_C void fn_MemoryModule_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	debug_put("内存Dll,具有唯一性,该次复制并不生效");
}
FucInfo Fn_MemoryModule_copy = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_COPY_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		ESTLARG(s_CopyArgs)
	},ESTLFNAME(fn_MemoryModule_copy)};

//析构
EXTERN_C void fn_MemoryModule_destruct(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<MemoryModule>(pArgInf);
	if (self)
	{
		self->~MemoryModule();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo Fn_MemoryModule_destruct = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_FREE_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,ESTLFNAME(fn_MemoryModule_destruct) };

static ARG_INFO m_MemoryModule_arg[] =
{
	{
		/*name*/    "模块",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}

};
EXTERN_C void fn_MemoryModule_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<MemoryModule>(pArgInf);

	pRetData->m_bool = self->MemoryLoadLibrary(elibstl::args_to_ebin(pArgInf, 1));
}

FucInfo Fn_MemoryModule_LoadLibrary = { {
		/*ccname*/  ("加载模块"),
		/*egname*/  ("LoadLibrary"),
		/*explain*/ R"(从内存加载具有指定大小的EXE/DLL文件.
注意: 如果加载的EXE完成运行,本进程也将终止)",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
	ESTLARG(m_MemoryModule_arg)
	} ,ESTLFNAME(fn_MemoryModule_open) };

static ARG_INFO m_MemoryModule_arg2[] =
{
	{
		/*name*/    "函数名称",
		/*explain*/ "函数导出时的名称",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};

EXTERN_C void fn_MemoryModule_GetProcAddress(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<MemoryModule>(pArgInf);
	pRetData->m_pAryData = self->MemoryGetProcAddress(elibstl::args_to_sdata(pArgInf,1).data());
}
FucInfo Fn_MemoryModule_GetProcAddress = { {
		"取函数指针", "GetProcAddress", "判从模块句柄中获取函数调用对象", -1, _CMD_OS(__OS_WIN), SDT_SUB_PTR, 0, LVL_SIMPLE, 0, 0, 
		ESTLARG(m_MemoryModule_arg2)
	} ,ESTLFNAME(fn_MemoryModule_GetProcAddress)};


EXTERN_C void fn_MemoryModule_CallEntryPoint(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<MemoryModule>(pArgInf);
	pRetData->m_int = self->MemoryCallEntryPoint();
}
FucInfo Fn_MemoryModule_CallEntryPoint = { {
		"取入口地址", "CallEntryPoint", R"(获取入口点(仅限EXE).只有当EXE已加载到正确的基址或可以重新定位时(即链接器未剥离重新定位信息),才能执行入口点.
重要提示:调用入口地址不会返回,即一旦执行的EXE完成运行,进程将终止.)", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0
} ,ESTLFNAME(fn_MemoryModule_CallEntryPoint) };

namespace elibstl {


	LIB_DATA_TYPE_INFO Obj_MemoryModule =
	{
		"内存模块类",
		"MemoryModule",
		R"(内存模块类是一个可用于完全从内存加载 DLL \ COM \EXE 等PE文件的类，无需先存储在磁盘上。)",
		ESTLARG(s_dtCmdIndexcommobj_MemoryModule_play),
		_DT_OS(__OS_WIN),
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		0
	};
}