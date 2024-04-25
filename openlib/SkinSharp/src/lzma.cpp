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
/// <param name="skinSize">Ƥ������</param>
/// <param name="pBegin">Ƥ��ʵ����ʼλ��,�������Ȳ���</param>
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
		pBegin + 4, //�������Ȳ���
		LZMA_PROPS_SIZE, LZMA_FINISH_ANY, (ELzmaStatus*)&pBegin, &g_Alloc);

}


/*�ļ�ͷΪ.SHE,������ľ��ǳ���ָ��*/
size_t __cdecl getdecsize(BYTE* pBegin)
{
	return *reinterpret_cast<size_t*>(pBegin);
}