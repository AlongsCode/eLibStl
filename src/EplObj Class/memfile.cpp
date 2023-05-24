#include<string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include"EcontrolHelp.h"



enum  class file_off_set_direction
{
	front = 0,
	back = 1,
};
enum class file_off_set
{
	begin = 1,
	end,
	current
};



class  EMemFile
{
private:
	std::vector<unsigned char> m_pData; // �����ļ�����
	size_t m_offset; // ��ǰ��дλ��
	size_t m_filesize; // �ļ�����
	// �ı仺��������
	void change_pbuffer_size(size_t newlenth);

public:
	// ��ʼ���ڴ��ļ�������ָ�� vector �ĳ�ʼ����
	EMemFile(size_t grow_bytes = 1024);

	~EMemFile();
	//
	void close();
	void read(size_t conut, std::vector<unsigned char>& ret);

	//д������

	void write(const unsigned char* data, const size_t size);


	//��������
	bool insert(std::vector<unsigned char> data);

	// �ƶ���дλ��
	bool seek(long offset, file_off_set origin = file_off_set::current);

	// �ƶ����ļ���ͷ
	void seek_begin();

	// �ƶ����ļ�ĩβ
	void seek_end();

	// �����ļ�����
	void set_file_size(size_t �³���);
	// ��ȡ�ļ�����
	size_t get_size() const;

	// ��ȡ��ǰ��дλ��
	size_t get_off_set() const;


};





EMemFile::EMemFile(size_t grow_bytes) : m_pData(grow_bytes), m_offset(0), m_filesize(0) {}
void EMemFile::change_pbuffer_size(size_t new_lenth)
{
	if (new_lenth > m_pData.size())
	{
		m_pData.resize(new_lenth);
	}
}
// ��ʼ���ڴ��ļ�������ָ�� vector �ĳ�ʼ����

EMemFile::~EMemFile() { close(); }
//
void EMemFile::close()
{

	m_pData.resize(0);
	m_offset = 0;
	m_filesize = 0;

}
// ��ȡ����
void EMemFile::read(size_t wanna_lenth, std::vector<unsigned char>& ret_data)
{
	ret_data.clear();
	// ������볤��Ϊ0���򷵻�һ���յ� vector
	if (wanna_lenth == 0)
	{
		return;
	}
	// �����ǰλ���Ѿ������ļ����ȣ��򷵻�һ���յ� vector
	if (m_offset > m_filesize)
	{
		return;
	}

	// ����ʵ�ʶ�����ֽ���
	size_t real_size;
	if (m_offset + wanna_lenth > m_filesize)
	{
		real_size = m_filesize - m_offset;
	}
	else
	{
		real_size = wanna_lenth;
	}
	// ����������ȡ����Ҫ��������ݣ�������ǰλ���ƶ�������λ�õĺ���
	ret_data.insert(ret_data.end(), m_pData.begin() + m_offset, m_pData.begin() + m_offset + real_size);
	m_offset += real_size;
}

void EMemFile::write(const unsigned char* data, const size_t size)
{

	// ��� data Ϊ�գ���ʲôҲ����
	if (!data || size == 0)
	{
		return;
	}
	// ����������ĳ��Ȳ�������ı仺�����ĳ���
	if (m_offset + size > m_pData.size())
	{
		change_pbuffer_size(m_offset + size);
	}

	// �� data ��������������
	std::copy(data, data + size, m_pData.begin() + m_offset);
	m_offset += size;

	// �����ļ���С
	if (m_offset > m_filesize)
	{
		m_filesize = m_offset;
	}
}


//��������
bool EMemFile::insert(std::vector<unsigned char> data)
{
	// ���Ҫ���������Ϊ�գ��򷵻� false
	if (data.empty())
	{
		return false;
	}

	// �ڵ�ǰλ�ò�������
	m_pData.insert(m_pData.begin() + m_offset, data.begin(), data.end());
	// ����ǰλ���ƶ���������λ��
	m_offset += data.size();
	// �����ļ���С
	if (m_offset > m_filesize)
	{
		m_filesize = m_offset;
	}

	return true;
}

// �ƶ���дλ��
bool EMemFile::seek(long offset, file_off_set origin)
{
	bool success = false;
	size_t new_off_set;
	switch (origin)
	{
	case file_off_set::begin:
		new_off_set = offset;
		break;
	case file_off_set::current:
		new_off_set = m_offset + offset;
		break;
	case file_off_set::end:
		new_off_set = m_filesize + offset;
		break;
	default:
		return success;
	}
	if (new_off_set > m_filesize)
	{

		new_off_set = m_filesize;
	}
	else if (new_off_set < 0)
	{
		new_off_set = 0;
	}
	m_offset = new_off_set;
	success = true;
	return success;
}

// �ƶ����ļ���ͷ
void EMemFile::seek_begin()
{
	m_offset = 0;
}

// �ƶ����ļ�ĩβ
void EMemFile::seek_end()
{
	m_offset = m_filesize;
}

// �����ļ�����
void EMemFile::set_file_size(size_t new_lenth)
{
	if (new_lenth > m_pData.size())
	{//���ݻ�����
		m_pData.resize(new_lenth);
	}
	m_filesize = new_lenth;
	if (m_offset > m_filesize)
	{
		m_offset = m_filesize;
	}
}
// ��ȡ�ļ�����
size_t EMemFile::get_size() const
{
	return m_filesize;
}

// ��ȡ��ǰ��дλ��
size_t EMemFile::get_off_set() const
{

	return m_offset;
}










//����
EXTERN_C void elibstl_memfile_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	self = new EMemFile;
}
//����
FucInfo Fn_memfile_structure = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/  _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_CONSTURCT_CMD,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	}  ,ESTLFNAME(elibstl_memfile_structure) };

//����
EXTERN_C void fn_memfile_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	auto rht = static_cast<EMemFile*>(*pArgInf[1].m_ppCompoundData);
	*self = *rht;
}
FucInfo Fn_memfile_copy = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_COPY_CMD,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,ESTLFNAME(fn_memfile_copy) };

//����
EXTERN_C void fn_memfile_des(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	if (self)
	{
		self->~EMemFile();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo Fn_memfile_destruct = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_FREE_CMD,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	}  ,ESTLFNAME(fn_memfile_des) };



EXTERN_C void fn_memfile_get_size(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	pRetData->m_int = self->get_size();
}

FucInfo Fn_memfile_get_size = { {
		/*ccname*/  "ȡ����",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,ESTLFNAME(fn_memfile_get_size) };


EXTERN_C void elibstl_memfile_seek_begin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	self->seek_begin();
}

FucInfo Fn_memfile_seek_begin = { {
		/*ccname*/  "�Ƶ��ļ���",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,ESTLFNAME(elibstl_memfile_seek_begin) };

EXTERN_C void elibstl_memfile_seek_end(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	self->seek_end();
}

FucInfo Fn_memfile_seek_end = { {
		/*ccname*/  "�Ƶ��ļ�β",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,ESTLFNAME(elibstl_memfile_seek_end) };
static ARG_INFO Args[] =
{
		{
		/*name*/	"��д��ֵ",
		/*explain*/	"���ڷǡ��ı��͡����������Զ�ת��Ϊ�ı����������ɽ�������������ͣ��������������Լ��Զ����������͡�",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::_SDT_ALL,
		/*default*/	0,
		/*state*/	AS_RECEIVE_ALL_TYPE_DATA,
			}
};
EXTERN_C void elibstl_memfile_write(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pMemFile = elibstl::args_to_obj<EMemFile>(pArgInf);
	for (INT i = 1; i < nArgCount; i++)
	{

		if (pArgInf[i].is_dt_flag())//������
		{
			pArgInf[i].remove_dt_flag(); //ȥ�������־
			if (pArgInf[i].m_dtDataType == DATA_TYPE::SDT_TEXT)
			{
				size_t dwSize;
				LPSTR* pAryData = elibstl::get_array_element_inf<LPSTR*>(pArgInf[i].m_pAryData, &dwSize); ;
				INT nData = 0;
				for (UINT n = 0; n < dwSize; n++)
				{
					INT nLen;
					void* pData;
					if (pAryData[n] == NULL)
					{
						nLen = 1;
						pData = &nData;
					}
					else
					{
						nLen = strlen(pAryData[n]) + 1;
						pData = pAryData[n];
					}
					pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

				}


			}
			else if (pArgInf[i].m_dtDataType == DATA_TYPE::SDT_BIN)/*���ı�*/
			{
				size_t dwSize;
				LPBYTE* pAryData = elibstl::get_array_element_inf<LPBYTE*>(pArgInf[i].m_pAryData, &dwSize);
				INT nData = 0;
				for (UINT n = 0; n < dwSize; n++)
				{
					void* pData;
					INT nLen;
					if (pAryData[n] == NULL)
					{
						pData = &nData;
						nLen = sizeof(INT);
					}
					else
					{
						nLen = (wcslen((WCHAR*)(pAryData[n] + sizeof(int) * 2)) + 1) * sizeof(wchar_t);
						pData = pAryData[n];
					}
					pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

				}

			}
			else {

				INT nLen = elibstl::get_esys_datatype_size(pArgInf[i].m_dtDataType);
				if (nLen == 0)//��֧�ֵ���������
					continue;
				size_t dwSize;
				void* pData = elibstl::get_array_element_inf<void*>(pArgInf[i].m_pAryData, &dwSize);
				nLen *= dwSize;
				pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

			}
		}
		else
		{//������
			INT nLen;
			void* pData;
			INT nData = 0;
			if (pArgInf[i].m_dtDataType == DATA_TYPE::SDT_TEXT)
			{
				if (pArgInf[i].m_pText == NULL)
				{
					nLen = 1;
					pData = &nData;

				}
				else
				{
					nLen = strlen(pArgInf[i].m_pText) + 1;
					pData = pArgInf[i].m_pText;
				}

			}
			else if (pArgInf[i].m_dtDataType == DATA_TYPE::SDT_BIN)
			{
				if (pArgInf[i].m_pBin == NULL)
				{
					nLen = sizeof(INT);
					pData = &nData;
				}
				else
				{
					auto data = elibstl::args_to_wsdata(pArgInf, i);
					nLen = (data.size() + 1) * sizeof(wchar_t);
					pData = const_cast<wchar_t*>(data.data());
				}

			}
			else {

				nLen = elibstl::get_esys_datatype_size(pArgInf[i].m_dtDataType);
				if (nLen == 0)//��֧�ֵ���������
					continue;
				pData = &pArgInf[i].m_int;
			}
			pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

		}
	}



}




FucInfo Fn_memfile_write = { {
		/*ccname*/  "д",
		/*egname*/  NULL,
		/*explain*/ "�˴���Ὣ�ֽڼ���Ϊ���ı����봫�ݱ�׼�����������Ŀ��ı�������д���ֽڼ���ʹ��д���ֽڼ�",
		/*category*/ -1,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(Args),
		/*arg lp*/  Args,
	} ,ESTLFNAME(elibstl_memfile_write) };

static ARG_INFO Args_mem[] =
{
		{
		/*name*/	"��д��Ķ���������",
		/*explain*/	"",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_BIN,
		/*default*/	0,
		/*state*/	0,
			}
};
EXTERN_C void elibstl_memfile_write_mem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pMemFile = elibstl::args_to_obj<EMemFile>(pArgInf);
	for (INT i = 1; i < nArgCount; i++)
	{
		auto& pData = elibstl::args_to_ebin(pArgInf, i);
		pMemFile->write(pData.m_data, pData.m_size);
	}
}




FucInfo Fn_memfile_write_mem = { {
		/*ccname*/  "д���ֽڼ�",
		/*egname*/  NULL,
		/*explain*/ "�˴���Ὣ��������������׼ȷд��",
		/*category*/ -1,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(Args_mem),
		/*arg lp*/  Args_mem,
	} ,ESTLFNAME(elibstl_memfile_write_mem) };

static ARG_INFO args_read[] =
{
		{
		/*name*/	"�����볤��",
		/*explain*/	"ʵ�ʳ��ȵ���ȡ�����ļ����ȡ�",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_INT,
		/*default*/	0,
		/*state*/	NULL,
			}
};
EXTERN_C void elibstl_memfile_read(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pMemFile = elibstl::args_to_obj<EMemFile>(pArgInf);
	std::vector<unsigned char> pData;
	pMemFile->read(pArgInf->m_int, pData);
	pRetData->m_pBin = elibstl::clone_bin(pData.data(), pData.size());
}

FucInfo Fn_memfile_read = { {
		/*ccname*/  "��",
		/*egname*/ NULL,
		/*explain*/  "�������ȡ���ȴ����ļ��������ض�",
		/*category*/ -1,
		/*state*/     _CMD_OS(__OS_WIN) ,
		/*ret*/DATA_TYPE::SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(args_read),
		/*arg lp*/  args_read,
	} ,ESTLFNAME(elibstl_memfile_read) };




static ARG_INFO args_seek[] =
{
		{
		/*name*/	"��ʼ�ƶ�λ��",
		/*explain*/	"1��#�ļ��ף� 2��#�ļ�β�� 3��#����λ�á�",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_INT,
		/*default*/	3,
		/*state*/	AS_HAS_DEFAULT_VALUE,
			},{
				/*name*/	"�ƶ�����",
				/*explain*/	"ʵ�ʳ��ȵ���ȡ�����ļ����ȡ�",
				/*bmp inx*/	0,
				/*bmp num*/	0,
				/*type*/	DATA_TYPE::SDT_INT,
				/*default*/	0,
				/*state*/	NULL,
					}
};
EXTERN_C void elibstl_memfile_seek(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pMemFile = elibstl::args_to_obj<EMemFile>(pArgInf);
	if (pArgInf[1].m_int < 1 || pArgInf[1].m_int > 3)
	{
		pArgInf[1].m_int = 3;
	}
	pRetData->m_bool = pMemFile->seek(pArgInf[2].m_int, static_cast<file_off_set>(pArgInf[1].m_int));
}

FucInfo Fn_memfile_seek = { {
		/*ccname*/  "�ƶ���дλ��",
		/*egname*/ NULL,
		/*explain*/  " �ڱ��򿪵��ļ��У�������һ������д������λ��",
		/*category*/ -1,
		/*state*/     _CMD_OS(__OS_WIN) ,
		/*ret*/DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(args_seek),
		/*arg lp*/  args_seek,
	} ,ESTLFNAME(elibstl_memfile_seek) };

EXTERN_C void elibstl_memfile_get_off_set(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pMemFile = elibstl::args_to_obj<EMemFile>(pArgInf);
	pRetData->m_int = pMemFile->get_off_set();
}

FucInfo Fn_memfile_get_off_set = { {
		/*ccname*/  "ȡ��дλ��",
		/*egname*/ NULL,
		/*explain*/  " �ڱ��򿪵��ļ��У�������һ������д������λ��",
		/*category*/ -1,
		/*state*/     _CMD_OS(__OS_WIN) ,
		/*ret*/DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,ESTLFNAME(elibstl_memfile_get_off_set) };
static INT s_dtCmdIndexcommobj_memfile_ex[] = { 226,227,228,229 ,230,231,232 ,233 ,234 ,235 ,236 };
namespace elibstl {


	LIB_DATA_TYPE_INFO Obj_EMemFile =
	{
		"�ڴ��ļ�",
		"MemFile",
		"�ڴ��ļ�",
		sizeof(s_dtCmdIndexcommobj_memfile_ex) / sizeof(s_dtCmdIndexcommobj_memfile_ex[0]),
		 s_dtCmdIndexcommobj_memfile_ex,
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