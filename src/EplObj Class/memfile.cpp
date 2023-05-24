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
	std::vector<unsigned char> m_pData; // 储存文件数据
	size_t m_offset; // 当前读写位置
	size_t m_filesize; // 文件长度
	// 改变缓冲区长度
	void change_pbuffer_size(size_t newlenth);

public:
	// 初始化内存文件，可以指定 vector 的初始容量
	EMemFile(size_t grow_bytes = 1024);

	~EMemFile();
	//
	void close();
	void read(size_t conut, std::vector<unsigned char>& ret);

	//写入数据

	void write(const unsigned char* data, const size_t size);


	//插入数据
	bool insert(std::vector<unsigned char> data);

	// 移动读写位置
	bool seek(long offset, file_off_set origin = file_off_set::current);

	// 移动到文件开头
	void seek_begin();

	// 移动到文件末尾
	void seek_end();

	// 设置文件长度
	void set_file_size(size_t 新长度);
	// 获取文件长度
	size_t get_size() const;

	// 获取当前读写位置
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
// 初始化内存文件，可以指定 vector 的初始容量

EMemFile::~EMemFile() { close(); }
//
void EMemFile::close()
{

	m_pData.resize(0);
	m_offset = 0;
	m_filesize = 0;

}
// 读取数据
void EMemFile::read(size_t wanna_lenth, std::vector<unsigned char>& ret_data)
{
	ret_data.clear();
	// 如果读入长度为0，则返回一个空的 vector
	if (wanna_lenth == 0)
	{
		return;
	}
	// 如果当前位置已经超出文件长度，则返回一个空的 vector
	if (m_offset > m_filesize)
	{
		return;
	}

	// 计算实际读入的字节数
	size_t real_size;
	if (m_offset + wanna_lenth > m_filesize)
	{
		real_size = m_filesize - m_offset;
	}
	else
	{
		real_size = wanna_lenth;
	}
	// 从数据中提取出需要读入的数据，并将当前位置移动到读入位置的后面
	ret_data.insert(ret_data.end(), m_pData.begin() + m_offset, m_pData.begin() + m_offset + real_size);
	m_offset += real_size;
}

void EMemFile::write(const unsigned char* data, const size_t size)
{

	// 如果 data 为空，则什么也不做
	if (!data || size == 0)
	{
		return;
	}
	// 如果缓冲区的长度不够，则改变缓冲区的长度
	if (m_offset + size > m_pData.size())
	{
		change_pbuffer_size(m_offset + size);
	}

	// 将 data 拷贝到缓冲区中
	std::copy(data, data + size, m_pData.begin() + m_offset);
	m_offset += size;

	// 更新文件大小
	if (m_offset > m_filesize)
	{
		m_filesize = m_offset;
	}
}


//插入数据
bool EMemFile::insert(std::vector<unsigned char> data)
{
	// 如果要插入的数据为空，则返回 false
	if (data.empty())
	{
		return false;
	}

	// 在当前位置插入数据
	m_pData.insert(m_pData.begin() + m_offset, data.begin(), data.end());
	// 将当前位置移动到插入后的位置
	m_offset += data.size();
	// 更新文件大小
	if (m_offset > m_filesize)
	{
		m_filesize = m_offset;
	}

	return true;
}

// 移动读写位置
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

// 移动到文件开头
void EMemFile::seek_begin()
{
	m_offset = 0;
}

// 移动到文件末尾
void EMemFile::seek_end()
{
	m_offset = m_filesize;
}

// 设置文件长度
void EMemFile::set_file_size(size_t new_lenth)
{
	if (new_lenth > m_pData.size())
	{//扩容缓冲区
		m_pData.resize(new_lenth);
	}
	m_filesize = new_lenth;
	if (m_offset > m_filesize)
	{
		m_offset = m_filesize;
	}
}
// 获取文件长度
size_t EMemFile::get_size() const
{
	return m_filesize;
}

// 获取当前读写位置
size_t EMemFile::get_off_set() const
{

	return m_offset;
}










//构造
EXTERN_C void elibstl_memfile_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<EMemFile>(pArgInf);
	self = new EMemFile;
}
//构造
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

//复制
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

//析构
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
		/*ccname*/  "取长度",
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
		/*ccname*/  "移到文件首",
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
		/*ccname*/  "移到文件尾",
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
		/*name*/	"欲写入值",
		/*explain*/	"对于非“文本型”参数，将自动转换为文本。本参数可接受任意基本类型，但不接受数组以及自定义数据类型。",
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

		if (pArgInf[i].is_dt_flag())//是数组
		{
			pArgInf[i].remove_dt_flag(); //去除数组标志
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
			else if (pArgInf[i].m_dtDataType == DATA_TYPE::SDT_BIN)/*宽文本*/
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
				if (nLen == 0)//不支持的数据类型
					continue;
				size_t dwSize;
				void* pData = elibstl::get_array_element_inf<void*>(pArgInf[i].m_pAryData, &dwSize);
				nLen *= dwSize;
				pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

			}
		}
		else
		{//非数组
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
				if (nLen == 0)//不支持的数据类型
					continue;
				pData = &pArgInf[i].m_int;
			}
			pMemFile->write(reinterpret_cast<unsigned char*>(pData), nLen);

		}
	}



}




FucInfo Fn_memfile_write = { {
		/*ccname*/  "写",
		/*egname*/  NULL,
		/*explain*/ "此代码会将字节集视为宽文本，请传递标准附带结束符的宽文本，如需写入字节集请使用写入字节集",
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
		/*name*/	"欲写入的二进制数据",
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
		/*ccname*/  "写入字节集",
		/*egname*/  NULL,
		/*explain*/ "此代码会将二进制数据完整准确写入",
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
		/*name*/	"欲读入长度",
		/*explain*/	"实际长度等于取决于文件长度。",
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
		/*ccname*/  "读",
		/*egname*/ NULL,
		/*explain*/  "如果所读取长度大于文件长度则会截断",
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
		/*name*/	"起始移动位置",
		/*explain*/	"1、#文件首； 2、#文件尾； 3、#现行位置。",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_INT,
		/*default*/	3,
		/*state*/	AS_HAS_DEFAULT_VALUE,
			},{
				/*name*/	"移动距离",
				/*explain*/	"实际长度等于取决于文件长度。",
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
		/*ccname*/  "移动读写位置",
		/*egname*/ NULL,
		/*explain*/  " 在被打开的文件中，设置下一个读或写操作的位置",
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
		/*ccname*/  "取读写位置",
		/*egname*/ NULL,
		/*explain*/  " 在被打开的文件中，设置下一个读或写操作的位置",
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
		"内存文件",
		"MemFile",
		"内存文件",
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