#include"ElibHelp.h"
static ARG_INFO WArgs[] =
{
	{
		/*name*/    "��ƴ�ӵ��ı�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

/*�ַ�����ƴ��һ����Ҫ���µ�Ч��,��Cд��Ȼ��Ȼ���ص��ǿ������󣬲���ֱ�����ö���ָ����������Ƕ������������˵�׼�ʹ���ݲο���Ȼ��Ҫ�ͷ�������*/
EXTERN_C void efn_concatenate_wstrings(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	size_t totalLength = 0;

	// ���������ַ������ܳ���
	for (int i = 0; i < nArgCount; i++)
	{
		if (pArgInf[i].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t)) > 2)
		{
			totalLength += wcslen(reinterpret_cast<wchar_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t) * 2));// *reinterpret_cast<std::uint32_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t) - 1;
		}

	}
	if (totalLength == 0)
	{
		return;
	}
	// �����㹻���ڴ�ռ�
	wchar_t* result = new wchar_t[totalLength + 1]{ 0 };

	// �����ַ���
	size_t currentPosition = 0;
	for (int i = 0; i < nArgCount; ++i)
	{
		if (pArgInf[i].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t)) > 2)
		{
			size_t length = wcslen(reinterpret_cast<wchar_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t) * 2));
			if (length > 0)
			{
				std::memcpy(result + currentPosition, reinterpret_cast<wchar_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t) * 2), length * sizeof(wchar_t));
				currentPosition += length;
			}
		}

	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}
FucInfo g_concatenate_wstrings = { {
		/*ccname*/  ("ƴ���ı�W"),
		/*egname*/  ("concatenate_wstrings"),
		/*explain*/ ("��ȷ��ƴ�ӵ��ַ�Ϊ���������ı�׼unicode�ı�,������Ϊ��ҪЧ��,���Բ���ȡ�ж�,�������������ֱ�������������صġ�+��ƴ���ֽڼ��Ϳ���"),
		/*category*/2,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,efn_concatenate_wstrings ,"efn_concatenate_wstrings" };