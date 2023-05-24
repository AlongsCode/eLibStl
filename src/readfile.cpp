#include <fstream>  
#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "��������ļ�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_readfileA(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::string_view& filename = elibstl::args_to_sdata(pArgInf, 0);
	std::ifstream file(std::string(filename), std::ios::binary);
	LPBYTE data;
	// ����ļ��򿪳ɹ�
	if (file) {
		// ��ȡ�ļ�����
		file.seekg(0, std::ios::end);
		size_t length = static_cast<size_t>(file.tellg());
		// �����ļ�ָ�뵽�ļ���ͷ
		file.seekg(0, std::ios::beg);
		data = new BYTE[length];
		file.read(reinterpret_cast<char*>(data), length);
		if (data && length > 0)
		{
			pRetData->m_pBin = elibstl::clone_bin(data, length);
			delete[]data;
		}

	}
	// �ر��ļ�
	file.close();

}

FucInfo read_file_a = { {
		/*ccname*/  ("�����ļ�A"),
		/*egname*/  (""),
		/*explain*/ ("���ļ��Զ����Ʒ�ʽ�����ڴ�"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_readfileA ,"Fn_readfileA" };











static ARG_INFO WArgs[] =
{
	{
		/*name*/    "��������ļ�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_readfileW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::wstring_view& filename = elibstl::args_to_wsdata(pArgInf, 0);
	std::ifstream file(std::wstring(filename), std::ios::binary);
	LPBYTE data;

	// ����ļ��򿪳ɹ�
	if (file) {
		// ��ȡ�ļ�����
		file.seekg(0, std::ios::end);
		size_t length = static_cast<size_t>(file.tellg());
		// �����ļ�ָ�뵽�ļ���ͷ
		file.seekg(0, std::ios::beg);
		// ��ȡ�����ļ��������ֽڵ� vector<unsigned char>
		data = new BYTE[length];
		file.read(reinterpret_cast<char*>(data), length);
		if (data && length > 0)
		{
			pRetData->m_pBin = elibstl::clone_bin(data, length);
			delete[]data;
		}

	}
	// �ر��ļ�
	file.close();

}

FucInfo read_file_w = { {
		/*ccname*/  ("�����ļ�W"),
		/*egname*/  (""),
		/*explain*/ ("���ļ��Զ����Ʒ�ʽ�����ڴ�"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,Fn_readfileW ,"Fn_readfileW" };
