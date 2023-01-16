#include"ElibHelp.h"
#include"elib/lang.h"


std::vector<unsigned char> ebin2v(LPBYTE bin) {
	if (!bin)
	{
		return {};
	}
	DWORD lenth = *(DWORD*)(bin + sizeof(int));
	LPBYTE pbuffer = (bin + sizeof(int) * 2);
	if (lenth)
	{
		return std::vector<unsigned char>(pbuffer, pbuffer + lenth);
	}
	return {};
}

