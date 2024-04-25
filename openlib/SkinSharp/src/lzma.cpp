#include "LzmaDec.h"

extern "C" {

	
	void* SzAlloc(void* p, size_t size) { p = p; return malloc(size); }
	void SzFree(void* p, void* address) { p = p; free(address); }
	
	static ISzAlloc g_Alloc = { SzAlloc, SzFree };
	
}
/// <summary>
/// 
/// </summary>
/// <param name="pbuffer"></param>
/// <param name="skinSize">皮肤长度</param>
/// <param name="pBegin">皮肤实际起始位置,包含长度部分</param>
/// <param name="prosize"></param>
/// <returns></returns>
int __cdecl dec(BYTE* pbuffer, size_t* skinSize, BYTE* pBegin, unsigned int prosize)
{
	prosize -= 9;
	return LzmaDecode(
		pbuffer, 
		skinSize,
		pBegin + 9,//
		&prosize, 
		pBegin + 4, //跳过长度部分
		LZMA_PROPS_SIZE, LZMA_FINISH_ANY, (ELzmaStatus*)&pBegin, &g_Alloc);

}


/*文件头为.SHE,其后跟随的就是长度指针*/
size_t __cdecl getdecsize(BYTE* pBegin)
{
	return *reinterpret_cast<size_t*>(pBegin);
}