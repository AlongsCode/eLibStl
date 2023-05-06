#include"EcontrolHelp.h"
#include<string>
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4018)
#pragma warning(disable:26451)
#pragma once
#pragma region 宏和枚举
enum class DataType {
	BYTE = 1,         // 字节型
	SHORT_INT,    // 短整数型
	INT,          // 整数型
	LONG_INT,     // 长整数型
	FLOAT,        // 小数型
	DOUBLE,       // 双精度小数型
	BOOLEAN,      // 逻辑型
	DATE_TIME,    // 日期时间型
	PTR,		  // 指针型，数据库不会用到
	TEXT,         // 文本型
	BYTE_ARRAY,   // 字节集型
	REMARK,		  // 备注型
	PRIMARY_KEY	  // 主键
};


/*验证宏*/


/*失败宏*/
#define EDB_ERROR_SUCCESS 0
#define EDB_ERROR_INVALID_COLUMN_NAME -1 //字段名称错误
#define EDB_ERROR_INVALID_COLUMN_TYPE -2 //数据类型错误
#define EDB_ERROR_INVALID_COLUMN_SIZE -3 //数据长度为0
#define EDB_ERROR_DUPLICATE_COLUMN_NAME -4//字段名重复
#define EDB_ERROR_CREATE_EDBS -5//创建EDB失败
#define EDB_ERROR_CREATE_EDT -6//创建EDT失败
#define EDB_ERROR_INVALID_EDBSFILE -7//无效edb文件
#define EDB_ERROR_NOOPEN_EDBS -8//没打开文件
#define EDB_ERROR_INVALID_INDEX -9//无效的字段或记录索引
#define EDB_ERROR_INVALID_DATA_SIZE -10 //写入错误的数据长度
#define EDB_ERROR_INVALID_DATA_TYPE -11 //写入错误的数据类型
#define EDB_ERROR_TRANSACTION_OPENED -12 //事务已开启
#define EDB_ERROR_TRANSACTION_NOT_OPENED -13 //事务未开启
#define EDB_ERROR_INVALID_COLUMN_NUM -14 //插入数据数量不匹配
#define EDB_ERROR_HASBEEN_OPEN_EDBS -15//已经打开一个了
#define EDB_ERROR_INVALID_ROWS_NUM -16//加入无效数量的记录
#define EDB_ERROR_CANTOPEN_DAT -17//无法打开对应EDT文件
#pragma endregion




struct ColumnInfo {
	std::string m_name;
	DataType m_dataType;
	unsigned int m_strDataLength = 20;

	ColumnInfo() : m_dataType(DataType::TEXT), m_strDataLength(0) {};
	ColumnInfo(const std::string& n, DataType t, int l = 20) : m_name(n), m_dataType(t), m_strDataLength(l) {}
};


typedef struct _ColumnInfo//字段信息
{
	const char* Name;
	int Type;
	int StrDataLenth;
} *lpColumInfo;

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <ctime>
#include <set>
//#include <filesystem>
#include <map>
#include <unordered_set>
#pragma pack(1)//边界对齐





#pragma region 内部宏


#define EDBCHECK { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 }
#define EDTCHECK { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 }
static const char pCheckSizeNeverUse[] = EDBCHECK;
#define EDBCHECKSIZE sizeof(pCheckSizeNeverUse)
#define EDTCHECKSIZE EDBCHECKSIZE
#define EDTDATASIZE 512


#pragma endregion


#pragma region 结构体

struct EDBHEADER {

	double m_createTime;//OLE时间
	int m_recordNum;//当前记录数量
	int m_unusedPrimaryKey;//可使用的主键,每次插入空数据会自增1,用不重复
	int  m_totalLength;//所有字段所需的长度,单位字节
	unsigned char  m_blankBYTE[84];//预留空间
	int m_validColumnNum;//有效字段数了
	EDBHEADER() {
		m_createTime = 0;
		m_recordNum = 0;
		m_unusedPrimaryKey = 1;
		m_totalLength = 0;
		memset(m_blankBYTE, 0, sizeof(m_blankBYTE));
		m_validColumnNum = 0;
	}
};
struct COLIMNDATA
{
	char m_ColumnName[16];  // 名称最大16字节,
	int m_delimiter;    // 分隔符
	DataType m_ColumnType;       // 起始偏移位置
	int m_offset;           // 非文本型需求数据长度;
	int m_strlenth;         // 如为文本类型则需要长度;
	unsigned char m_Table[40];
	COLIMNDATA() {

		memset(this, 0, sizeof(*this));
	}
};
#pragma endregion


#pragma region 映射


/*映射字段长度,文本型可自行设置*/
std::map<DataType, int> type_lengths = {
	{DataType::BYTE, 1},
	{DataType::SHORT_INT, 2},
	{DataType::INT, 4},
	{DataType::LONG_INT, 8},
	{DataType::FLOAT, 4},
	{DataType::DOUBLE, 8},
	{DataType::BOOLEAN, 1},
	{DataType::DATE_TIME, 4},
	{DataType::PTR, 4},
	{DataType::BYTE_ARRAY, 4},
	{DataType::REMARK, 4},
	{DataType::PRIMARY_KEY, 4} // 主键型默认长度为4
};
#pragma endregion








#pragma region help
//获取时间并转化为OLE时间,此代码为兼容EDB原版
inline double get_nowtm_to_oletm() {
	auto now = std::chrono::system_clock::now();
	auto time_t_now = std::chrono::system_clock::to_time_t(now);
	auto  t = static_cast<__time64_t>(time_t_now);
	return static_cast<double>(25569 + t / 86400.0 + 8.0 / 24.0);

}




/*EDBS并不会进行过多限制，但会进行严格的规则审查，不满足则不允许创建*/
bool is_vaild_name(const std::string& text) {
	if (text.empty()
		|| text.size() > 16
		|| text.find(" ") != std::string::npos
		)
	{
		return false;
	}
	if ((text[0] >= '0' && text[0] <= '9') || text[0] == '.') {
		return false;
	}
	return true;
}




std::string rename_file_ext(const std::string& filename, const std::string& extensionname) {
	std::string::size_type dot_pos = filename.find_last_of('.');

	if (dot_pos == std::string::npos) {
		// 文件名没有扩展名
		return filename + extensionname;
	}
	else {
		// 使用 substr() 函数从文件名中提取扩展名
		std::string base = filename.substr(0, dot_pos);
		return base + extensionname;
	}
}
//#ifdef _WIN32
//#include"shlwapi.h"
//#pragma comment(lib,"shlwapi.lib") 
//std::string refilename(const std::string& Filename, const std::string& extensionname) {
//	char NewPath[MAX_PATH]{ 0 };
//	strcpy(NewPath, Filename.c_str());
//	std::string suffix = PathFindExtensionA(extensionname.c_str());
//	if (suffix.size() > 1)
//	{
//		if (PathRenameExtensionA(NewPath, suffix.c_str())) {
//			return NewPath;
//		};
//		return NewPath;
//	}
//	return NewPath;
//}
//#else
///*易语言用不了文件系统,而且win平台确实winapi更快一点*/
//std::string rename_file_ext(const std::string& filename, const std::string& extensionname) {
//
//	std::filesystem::path filepath(filename);
//	std::string suffix = extensionname;
//	if (extensionname[0] != '.') {
//		suffix = "." + suffix;
//	}
//	filepath.replace_extension(suffix);
//	return filepath.string();
//}
//#endif // _WIN32


//仅获取文件名
//std::string get_file_name_unext(const std::string& file_path) {
//	std::filesystem::path file(file_path);
//	std::string file_name = file.stem().string();
//	return file_name;
//}

/*修改文件拓展名*/
//std::string rename_file_ext(const std::string& filename, const std::string& extensionname) {
//
//	std::filesystem::path filepath(filename);
//	std::string suffix = extensionname;
//	if (extensionname[0] != '.') {
//		suffix = "." + suffix;
//	}
//	filepath.replace_extension(suffix);
//	return filepath.string();
//}
#pragma endregion












class Edt
{
	struct EDTHEADER//EDT创建数据
	{
		EDTHEADER() {
			m_createTime = 0;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
			m_recordNum = 1;
			m_un_using_count = 0;
			m_nop_index = 0;
			memset(m_data, 0, sizeof(m_data));
		}
		double  m_createTime;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
		int m_recordNum;//未使用绑定外键1;
		int m_un_using_count;//未使用数量
		int m_nop_index;//最后腾出的数据索引;
		unsigned char m_data[484];
	};
	struct EDTDATA {
		int m_previous;//前一条空数据索引
		int m_next;//后一条数据索引,再次被使用时会将指向索引改为此数据,如果为空表示没有后续数据或者没有空余数据
		int m_data_size;//数据长度
		unsigned char m_pbuffer[500];
		EDTDATA() {
			memset(this, 0, sizeof(*this));
		}
	};
	//help,最后不会暴漏在头文件接口中
	bool is_edt_file() {

		// 确认文件大小
		m_file_edt.seekg(0, std::ios::end);
		const char edb_flag[] = { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 };
		if (m_file_edt.tellg() < sizeof(EDTDATA)) {
			// 文件太小，不可能是有效的 edbs 文件
			return false;
		}

		m_file_edt.seekg(0, std::ios::beg);
		char rfile_flag[sizeof(edb_flag)]{ 0 };
		m_file_edt.read(rfile_flag, sizeof(edb_flag));

		if (std::memcmp(rfile_flag, edb_flag, sizeof(edb_flag)) != 0) {
			// 文件不是 edbs 文件
			return false;
		}
		//如果是edbs文件需要移到文件首继续，因为后续操作需要，如果不是则不用管理，返回时会自动关闭
		m_file_edt.seekg(0, std::ios::beg);
		return true;
	}


public:
	~Edt() {
		close();
	}
	static bool create(const std::string& nfilename, double time) {
		// 创建EDT文件
		std::string edtFileName = rename_file_ext(nfilename, ".EDT");
		std::ofstream edtFile(edtFileName, std::ios::binary);
		if (!edtFile)
		{
			// 创建EDT文件失败
			return false;
		}
		// 写入EDT文件头部信息
		EDTHEADER edtHeader;
		char check_edt[] = { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 };
		edtHeader.m_createTime = time;
		edtFile.write(check_edt, sizeof(check_edt));
		edtFile.write(reinterpret_cast<char*>(&edtHeader), sizeof(EDTHEADER));
		edtFile.close();
		return true;
	}
	bool isopen() const {
		return m_file_edt.is_open();
	}
	bool open(const std::string& filename, double n_time) {
		//已经打开就不在打开
		if (m_file_edt.is_open()) {
			return false;
		}


		m_file_edt.open(filename, std::ios::binary | std::ios::out | std::ios::in);
		if (!m_file_edt.is_open()) {
			// 文件无法打开
			return false;
		}
		if (!is_edt_file())
		{
			m_file_edt.close();
			return false;
		}
		//获取EDB信息
		m_file_edt.seekg(EDBCHECKSIZE);
		m_file_edt.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDTHEADER));
		//无有效字段
		if (m_edbInf.m_recordNum <= 0)
		{
			m_file_edt.close();
			return false;;
		}

		//再次验证文件大小
		m_file_edt.seekg(0, std::ios::end);
		auto fileSize = m_file_edt.tellg();


		if (fileSize < sizeof(EDTDATA) * m_edbInf.m_recordNum)
		{
			// 文件太小，不可能读取所有列信息和当前足够的信息数据
			m_file_edt.close();
			return false;;
		}
		if (n_time != m_edbInf.m_createTime)
		{
			return false;;
		}
		m_filename = filename;
		return true;;

	}
	/*查*/
	void read(std::vector<unsigned char>* n_pData, int n_index) {
		n_pData->clear();
		if (!m_file_edt.is_open())
		{
			/*文件没有打开*/
			return;
		}
		/*验证索引有效性*/
		if (n_index<0 || n_index>m_edbInf.m_recordNum)
		{
			/*索引失效*/
			return;
		}
		m_file_edt.seekg(n_index * sizeof(EDTDATA), std::ios::beg);
		while (true) {
			EDTDATA temp_data;

			m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(temp_data));
			if (temp_data.m_data_size == 0)
			{
				/*无数据了*/
				return;
			}
			n_pData->insert(n_pData->end(), temp_data.m_pbuffer, temp_data.m_pbuffer + temp_data.m_data_size);
			if (temp_data.m_next == 0)
			{
				/*无下一段了*/
				return;
			}
			auto off = temp_data.m_next * sizeof(EDTDATA);
			m_file_edt.clear();
			m_file_edt.seekg(off, std::ios::beg);
			if (m_file_edt.fail() || m_file_edt.bad()) {
				/* 定位失败 */
				return;
			}
		}

	}
	/*增*/
	int write(const std::vector<unsigned char>& n_pData)
	{

		int ret = 0;
		if (!m_file_edt.is_open())
		{
			/*文件没有打开*/
			return  ret;
		}
		if (n_pData.empty())
		{
			return ret;
		}
		int data_len = n_pData.size();
		int s_last_index = 0;
		if (data_len > 500)
		{

			int segment_num = data_len / 500 + 1;
			//std::vector<EDTDATA> data_segments(segment_num);
			int last_segment_size = data_len % 500;
			for (int i = 0; i < segment_num; ++i)
			{
				EDTDATA temp_data;
				int i_index;
				if (m_edbInf.m_un_using_count > 0)
				{
					/*本次索引为最后空闲索引*/
					i_index = m_edbInf.m_nop_index;
					/*获取空闲指针数据*/
					m_file_edt.seekg(i_index * sizeof(EDTDATA), std::ios::beg);
					m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);
					/*更新文件头*/

					m_edbInf.m_un_using_count--;
					/*链头为空的指针更新，确保链式正确性*/
					m_edbInf.m_nop_index = temp_data.m_next;
				}
				else
				{
					i_index = m_edbInf.m_recordNum;
					m_edbInf.m_recordNum++;
				}
				int i_next = m_edbInf.m_un_using_count > 0 ? m_edbInf.m_nop_index : m_edbInf.m_recordNum;
				/*写入数据段*/
				int data_size = i == segment_num - 1 ? last_segment_size : 500;
				std::memcpy(temp_data.m_pbuffer, n_pData.data() + i * 500, data_size);
				temp_data.m_data_size = data_size;

				if (i == 0)
				{
					/*首数据段表示开始块*/
					ret = i_index;
					/*处理第一个数据段*/
					temp_data.m_previous = 0;
					if (segment_num == 1)
					{
						temp_data.m_next = 0;

					}
					else
					{
						temp_data.m_next = i_next;
					}
				}
				else if (i == segment_num - 1)
				{
					/*处理最后一个数据段*/
					temp_data.m_previous = s_last_index;
					temp_data.m_next = 0;
				}
				else
				{
					/*处理中间的数据段*/
					temp_data.m_previous = s_last_index;
					temp_data.m_next = i_next;
				}
				s_last_index = i_index;

				/*写入数据*/
				m_file_edt.clear();
				m_file_edt.seekp(i_index * sizeof(EDTDATA), std::ios::beg);
				m_file_edt.write(reinterpret_cast<char*>(&temp_data), sizeof(EDTDATA));
			}
		}
		else
		{
			/*数据小于等于500字节，写入单个数据块*/
			int i_index;
			EDTDATA temp_data;
			if (m_edbInf.m_un_using_count > 0)
			{
				/*本次索引为最后空闲索引*/
				i_index = m_edbInf.m_nop_index;
				/*获取空闲指针数据*/
				m_file_edt.seekg(i_index * sizeof(EDTDATA), std::ios::beg);
				m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);
				/*更新文件头*/

				m_edbInf.m_un_using_count--;
				/*尾部为空的指针更新，确保链式正确性*/
				m_edbInf.m_nop_index = temp_data.m_next;
			}
			else
			{
				i_index = m_edbInf.m_recordNum;
				m_edbInf.m_recordNum++;
			}
			ret = i_index;
			/*写入数据*/
			std::memcpy(temp_data.m_pbuffer, n_pData.data(), data_len);
			temp_data.m_data_size = data_len;
			temp_data.m_previous = 0;
			temp_data.m_next = 0;
			m_file_edt.seekp(i_index * sizeof(EDTDATA), std::ios::beg);
			m_file_edt.write(reinterpret_cast<char*>(&temp_data), sizeof(EDTDATA));
		}
		return ret;
	}
	/*删*/
	void del(int n_index) {
		/*验证索引有效性*/
		if (n_index < 0 || n_index > m_edbInf.m_recordNum)
		{
			/*索引失效*/
			return;
		}

		m_edbInf.m_nop_index = n_index;
		do
		{
			m_file_edt.seekg(n_index * sizeof(EDTDATA), std::ios::beg);
			EDTDATA  p;
			m_file_edt.read(reinterpret_cast<char*>(&p), sizeof(p));
			m_edbInf.m_un_using_count++;
			p.m_previous = m_edbInf.m_nop_index;//衔接表
			if (p.m_next == 0)
			{
				break;
			}
			n_index = p.m_next;

		} while (true);
		if (m_edbInf.m_recordNum == m_edbInf.m_un_using_count + 1)
		{
			/*删除重建*/
			m_file_edt.close();
			remove(m_filename.c_str());
			create(m_filename.c_str(), m_edbInf.m_createTime);
			open(m_filename.c_str(), m_edbInf.m_createTime);
		}
	}
	int change(int n_index, const std::vector<unsigned char>& n_pData) {
		del(n_index);
		if (n_pData.empty())
		{
			return 0;
		}
		return write(n_pData);
	}
	void clean() {
		m_file_edt.close();
		remove(m_filename.c_str());
		create(m_filename.c_str(), m_edbInf.m_createTime);
		open(m_filename.c_str(), m_edbInf.m_createTime);
	}
	void close() {
		if (m_file_edt.is_open()) {
			m_file_edt.close();
		}
		m_filename = std::string();
		m_edbInf = EDTHEADER();
	}
	void updata() {
		//已经打开就不在打开
		if (!m_file_edt.is_open()) {
			return;
		}
		/*更新文件头*/
		m_file_edt.seekp(EDBCHECKSIZE, std::ios::beg);
		m_file_edt.write(reinterpret_cast<char*>(&m_edbInf), sizeof(m_edbInf));
		m_file_edt.flush();
	};
private:
	std::fstream  m_file_edt;/*EDT文件*/
	std::string m_filename;
	EDTHEADER m_edbInf;
};





class Edbs
{
public:
	Edbs& operator = (const Edbs& n_copy) {
#ifdef _WIN32
		MessageBoxW(0, L"禁止将EDB对象复制", 0, 0);
#else
		std::cout << "Prohibit copying EDB objects" << std::endl;
#endif // _WIN32
		std::abort();
		/*不要复制*/
		if (this != &n_copy) {
			// 先关闭当前文件，防止资源泄漏
			if (m_file.is_open()) m_file.close();
			// 复制错误码和偏移量等信息
			m_errorCode = n_copy.m_errorCode;
			m_fileName = n_copy.m_fileName;
			m_dataOffset = n_copy.m_dataOffset;
			m_cur_off = n_copy.m_cur_off;
			m_isTransactionOpened = n_copy.m_isTransactionOpened;
			// 复制列信息
			m_allCoLimns = n_copy.m_allCoLimns;
			// 复制 EDB 头信息
			m_edbInf = n_copy.m_edbInf;
			// 打开文件
			m_file.open(n_copy.m_fileName);
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			}
			//m_edt_file.open(get_file_name_unext(n_copy.m_fileName) + ".edt");
			//if (!m_file_edt.is_open()) {
			//	// 文件无法打开
			//	m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			//}
		}
		return *this;
	}
	Edbs() :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {};
	Edbs(const std::string& filename) :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {

		m_file.open(filename, std::ios::binary | std::ios::out | std::ios::in | std::fstream::trunc);
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		if (!is_edbs_file())
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		//获取EDB信息
		m_file.seekg(EDBCHECKSIZE);
		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
		//无有效字段
		if (m_edbInf.m_validColumnNum <= 0)
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		//再次验证文件大小
		m_file.seekg(0, std::ios::end);
		auto fileSize = m_file.tellg();


		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
		{
			// 文件太小，不可能读取所有列信息和当前足够的信息数据
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		m_file.seekg(sizeof(EDBHEADER) + EDBCHECKSIZE);
		m_allCoLimns.resize(m_edbInf.m_validColumnNum);
		m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
		m_dataOffset = m_file.tellg();
		if (has_big_data())
		{
			//打开对应EDT文件
			;
			if (!m_edt_file.open(filename, m_edbInf.m_createTime)) {
				m_file.close();
				// 文件无法打开
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}
		}

		/*处理初始化数据*/
		m_cur_off = 1;
		m_fileName = filename;
	};
	~Edbs() { close(); };
public:
	static int create_edbs(const std::string& nfilename, const std::vector< ColumnInfo>& columns) {

		/*对于字段的有效性验证和数据提取*/
		std::unordered_set<std::string> columnNames;

		std::vector<COLIMNDATA> wFileCoumns;

		//默认要对数据库进行一个主键大小,同时也是偏移和拓展出去的长度
		std::uint32_t all_columns_datasize = type_lengths[DataType::PRIMARY_KEY];
		//有效字段数量
		std::uint32_t valid_column_num = 0;

		bool bIsHaveBigData = false;

		for (ColumnInfo column : columns)
		{

			// 判断字段名是否已经出现过
			if (columnNames.count(column.m_name) > 0)
			{
				return EDB_ERROR_DUPLICATE_COLUMN_NAME;
			}
			columnNames.insert(column.m_name);


			if (!is_vaild_name(column.m_name))
			{

				return  EDB_ERROR_INVALID_COLUMN_NAME;
			}


			if (column.m_dataType< DataType::BYTE || column.m_dataType > DataType::REMARK)
			{
				return EDB_ERROR_INVALID_COLUMN_TYPE;
			}



			//准备将其写入文件中的字段数据
			COLIMNDATA TempwFileCoumns;
			TempwFileCoumns.m_ColumnType = column.m_dataType;

			strcpy_s(TempwFileCoumns.m_ColumnName, column.m_name.c_str());
			TempwFileCoumns.m_ColumnName[15] = '\0';
			if (strlen(TempwFileCoumns.m_ColumnName) < 15)
			{
				memset(&TempwFileCoumns.m_ColumnName[strlen(TempwFileCoumns.m_ColumnName)], 0, 15 - strlen(TempwFileCoumns.m_ColumnName));
			}

			//通过名称和类型判断则进行长度验证
			//首先是判断是否为文本型
			std::uint32_t TempColumnSize = 0;
			//EDBS不对文本型最大长度进行限制
			if (column.m_dataType == DataType::TEXT)
			{
				//验证
				TempColumnSize = column.m_strDataLength;
				//准备写入二进制数据
				TempwFileCoumns.m_strlenth = column.m_strDataLength;
			}
			else
			{
				TempColumnSize = type_lengths[column.m_dataType];
			}

			if (TempColumnSize == 0)
			{
				return EDB_ERROR_INVALID_COLUMN_SIZE;
			}

			if (column.m_dataType == DataType::REMARK || column.m_dataType == DataType::BYTE_ARRAY)
			{
				bIsHaveBigData = true;
			}
			TempwFileCoumns.m_offset = all_columns_datasize;
			wFileCoumns.push_back(TempwFileCoumns);
			all_columns_datasize += TempColumnSize;
			valid_column_num++;
		}

		auto filename = rename_file_ext(nfilename, ".edbs");

		std::ofstream file(filename, std::ios::binary);
		if (!file.is_open())
		{
			// 创建EDT文件失败
			return EDB_ERROR_CREATE_EDBS;
		}
		EDBHEADER EDB;
		auto time = get_nowtm_to_oletm();
		EDB.m_createTime = time;
		EDB.m_validColumnNum = valid_column_num;
		EDB.m_totalLength = all_columns_datasize;
		char check_edb[] = EDBCHECK;
		file.write(check_edb, sizeof(check_edb));
		file.write(reinterpret_cast<char*>(&EDB), sizeof(EDBHEADER));
		// 然后写入字段数据
		for (auto& column : wFileCoumns)
		{
			file.write(reinterpret_cast<char*>(&column), sizeof(COLIMNDATA));
		}
		file.close();

		if (bIsHaveBigData)
		{
			Edt::create(nfilename, time);
		}
		return EDB_ERROR_SUCCESS;
	}

	;
	bool open(const std::string& filename) {
		//已经打开就不在打开
		if (m_file.is_open()) {
			m_errorCode = EDB_ERROR_HASBEEN_OPEN_EDBS;
			return false;
		}


		m_file.open(filename, std::ios::binary | std::ios::out | std::ios::in);
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;
		}
		if (!is_edbs_file())
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;
		}
		//获取EDB信息
		m_file.seekg(EDBCHECKSIZE);
		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
		//无有效字段
		if (m_edbInf.m_validColumnNum <= 0)
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;;
		}
		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		//再次验证文件大小
		m_file.seekg(0, std::ios::end);
		auto fileSize = m_file.tellg();


		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
		{
			// 文件太小，不可能读取所有列信息和当前足够的信息数据
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;;
		}
		m_file.seekg(sizeof(EDBHEADER) + EDBCHECKSIZE);
		m_allCoLimns.resize(m_edbInf.m_validColumnNum);
		m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
		m_dataOffset = m_file.tellg();
		if (has_big_data())
		{
			//打开对应EDT文件
			if (!m_edt_file.open(rename_file_ext(filename, ".EDT"), m_edbInf.m_createTime)) {
				m_file.close();
				// 文件无法打开
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}
		}

		/*处理初始化数据*/
		if (m_edbInf.m_recordNum > 0)
		{
			m_cur_off = 1;
		}

		m_fileName = filename;
		return true;;

	}
	//保证不会出现容量不足，因为给易用，需要牺牲部分性能来保证用户不会进行傻逼操作
	void Read(int nIndex_column, int nIndex_row, std::vector<unsigned char>* pData) {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if ((nIndex_row >= 0 && nIndex_row + 1 > m_edbInf.m_recordNum) || (nIndex_column + 1 > m_edbInf.m_validColumnNum && nIndex_column >= 0))
		{
			m_errorCode = EDB_ERROR_INVALID_INDEX;
			return;
		}
		m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);

		//文本型长度需特殊处理
		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
		{	//否则默认长度
			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
		}

		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
		{
			pData->resize(needsize, 0);
			m_file.read(reinterpret_cast<char*>(pData->data()), pData->size());
		}
		else
		{
			/*处理字节集和备注型*/
			/*读入索引*/
			int index = 0;
			m_file.read(reinterpret_cast<char*>(&index), sizeof(index));
			if (index > 0)
			{
				/*在指定EDT文件中寻找数据*/
				m_edt_file.read(pData, index);
			}

		}


	};
	bool Write(int nIndex_column, int nIndex_row, const std::vector<unsigned char>& data) {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (nIndex_row + 1 > m_edbInf.m_recordNum || nIndex_column + 1 > m_edbInf.m_validColumnNum)
		{
			m_errorCode = EDB_ERROR_INVALID_INDEX;
			return false;
		}
		m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
		//文本型长度需特殊处理
		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
		{	//否则默认长度
			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
		}

		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
		{
			/*非字节集和备注型*/
			if (data.size() >= needsize) {
				// 长度超过会截断
				m_file.write(reinterpret_cast<const char*>(data.data()), needsize);
			}
			else {
				// 长度不足会填充
				m_file.write(reinterpret_cast<const char*>(data.data()), data.size());
				if (data.size() < needsize) {
					// 填充剩余空间
					//std::vector<unsigned char> padData(needsize - data.size(), 0);
					auto padData = new char[needsize - data.size()]{ 0 };
					m_file.write(padData, needsize - data.size());
					delete[]padData;
				}
			}
		}
		else
		{
			/*处理字节集和备注型*/
			/*读入索引*/
			m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
			int index = 0;
			m_file.read(reinterpret_cast<char*>(&index), sizeof(index));
			if (index > 0)
			{
				/*在指定EDT文件中存在数据*/
				if (data.empty())
				{
					m_edt_file.del(index);
					index = 0;
				}
				else
				{
					index = m_edt_file.change(index, data);
				}
			}
			else
			{
				/*不存在*/
				if (data.empty())
				{
					return true;
				}
				else
				{
					index = m_edt_file.write(data);

				}
			}
			m_edt_file.updata();//IO
			debug_put(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
			m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
			m_file.write(reinterpret_cast<const char*>(&index), sizeof(int));

			/*处理字节集和备注型*/
		}
		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}

		return  true;
	}
	bool Insert(const std::vector<std::vector<unsigned char>>& data) {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (data.empty()) {
			// 无数据要插入
			return true;
		}
		if (data.front().size() != m_edbInf.m_validColumnNum) {
			// 新数据的列数不匹配
			m_errorCode = EDB_ERROR_INVALID_COLUMN_NUM;
			return false;
		}
		if (m_isTransactionOpened) {
			// 已开启事务，不能插入
			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
			return false;
		}
		auto totalRowSize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		// 计算插入新行后文件的总大小
		auto newFileSize = sizeof(EDBHEADER) + EDBCHECKSIZE + m_allCoLimns.size() * sizeof(COLIMNDATA) +
			(m_edbInf.m_recordNum + data.size()) * m_edbInf.m_totalLength;
		// 调整文件大小
		m_file.seekp(newFileSize - 1);
		m_file.write("", 1);
		// 读取文件尾部的数据，以便将其移动到新的位置
		auto tailSize = static_cast<int> (m_file.tellg()) - (m_dataOffset + totalRowSize);
		std::vector<unsigned char> tailData(tailSize);
		m_file.seekg(m_dataOffset + totalRowSize);
		m_file.read(reinterpret_cast<char*>(tailData.data()), tailSize);
		// 将尾部数据移动到新的位置
		m_file.seekp(newFileSize - tailSize);
		m_file.write(reinterpret_cast<char*>(tailData.data()), tailSize);
		// 将新数据写入文件
		m_file.seekp(m_dataOffset + m_edbInf.m_recordNum * m_edbInf.m_totalLength);
		for (const auto& row : data) {
			for (int i = 0; i < m_allCoLimns.size(); ++i) {
				const auto& col = row;
				const auto& colInfo = m_allCoLimns[i];
				int needsize = colInfo.m_strlenth;
				if (colInfo.m_ColumnType != DataType::TEXT) {
					needsize = type_lengths[colInfo.m_ColumnType];
				}

				if (colInfo.m_ColumnType != DataType::BYTE_ARRAY && colInfo.m_ColumnType != DataType::REMARK)
				{
					if (col.size() < needsize) {
						// 数据长度不足，补零
						std::vector<unsigned char> paddedData(needsize, 0);
						std::copy(col.begin(), col.end(), paddedData.begin());
						m_file.write(reinterpret_cast<char*>(paddedData.data()), needsize);
					}
					else {
						m_file.write(reinterpret_cast<const char*>(col.data()), needsize);
					}
				}
				else
				{
					/*处理字节集和备注型*/
				}



			}
		}
		// 更新记录数和文件大小信息
		m_edbInf.m_recordNum++;
		updata_heade();
		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
	}
	bool AppendBlank(int nCount) {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (nCount <= 0)
		{
			m_errorCode = EDB_ERROR_INVALID_ROWS_NUM;
			return false;
		}
		//文件头处理
		m_edbInf.m_recordNum += nCount;
		m_file.seekp(0, std::ios::end);
		//文本型长度需特殊处理


		std::vector<char> pData_nop(nCount * m_edbInf.m_totalLength, 0);
		for (size_t i = 0; i < nCount; i++)
		{

			*reinterpret_cast<int*>(&pData_nop[m_edbInf.m_totalLength * i]) = m_edbInf.m_unusedPrimaryKey++;

		}
		// 长度超过会截断
		m_file.write(reinterpret_cast<const char*>(pData_nop.data()), pData_nop.size());

		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
		updata_heade();
		to_end();
		return  true;
	}

	//开启事务
	void begin() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (m_isTransactionOpened) {
			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
			return;
		}
		m_isTransactionOpened = true;
	}
	//提交事务
	void commit() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (!m_isTransactionOpened) {
			m_errorCode = EDB_ERROR_TRANSACTION_NOT_OPENED;
			return;
		}
		m_file.flush();
	}
	std::string Get_column_name(int nIndex_column)const {
		if (!m_file.is_open()) {
			// 文件无法打开
			return std::string();
		}
		if (nIndex_column < 0 || nIndex_column >= m_allCoLimns.size())
		{
			return std::string();
		}
		return m_allCoLimns[nIndex_column].m_ColumnName;
	}
	void Set_column_name(int nIndex_column, const std::string& name) {
		if (!m_file.is_open()) {
			// 文件无法打开
			return;
		}
		if (nIndex_column < 0 || nIndex_column >= m_allCoLimns.size())
		{
			return;
		}
		//COLIMNDATA TempwFileCoumns = m_allCoLimns[nIndex_column];
		strcpy_s(m_allCoLimns[nIndex_column].m_ColumnName, name.c_str());
		m_allCoLimns[nIndex_column].m_ColumnName[15] = '\0';
		if (strlen(m_allCoLimns[nIndex_column].m_ColumnName) < 15)
		{
			memset(&m_allCoLimns[nIndex_column].m_ColumnName[strlen(m_allCoLimns[nIndex_column].m_ColumnName)], 0, 15 - strlen(m_allCoLimns[nIndex_column].m_ColumnName));
		}
		updata_heade();
		;
	}
private:
	Edt m_edt_file;
	std::string m_fileName;
	std::fstream m_file;  //文件流
	int m_dataOffset;//数据开始位置
	int m_errorCode;//错误码
	EDBHEADER m_edbInf;//数据表信息
	std::vector<COLIMNDATA> m_allCoLimns;//字段信息
	bool m_isTransactionOpened;//是否开启事务
	//下方为包装操作
public:
	void clean() {
		/*关闭*/
		if (m_edt_file.isopen())
		{
			m_edt_file.close();
		}
		if (m_file.is_open())
		{
			m_file.clear();
			m_file.close();
		}
		std::vector<ColumnInfo> _ColumnInfo;
		/*重建*/
		for (const auto& temp : m_allCoLimns)
		{
			ColumnInfo i_ColumnInfo;
			i_ColumnInfo.m_dataType = temp.m_ColumnType;
			i_ColumnInfo.m_name = temp.m_ColumnName;
			i_ColumnInfo.m_strDataLength = temp.m_strlenth;
			_ColumnInfo.push_back(i_ColumnInfo);
		}
		m_errorCode = create_edbs(m_fileName, _ColumnInfo);
		/*打开*/
		open(m_fileName);
	}
	void close() {
		if (m_edt_file.isopen())
		{
			m_edt_file.close();
		}
		m_fileName = {};
		if (m_file.is_open())
		{
			m_file.clear();
			m_file.close();
		}
		m_dataOffset = 0;
		m_errorCode = EDB_ERROR_SUCCESS;
		m_edbInf = {};
		m_allCoLimns = {};
		m_isTransactionOpened = false;
	}
	int get_error_code() const {
		return m_errorCode;
	}
	int get_column_num()const {
		if (!m_file.is_open()) {
			// 文件无法打开
			return 0;
		}
		return m_edbInf.m_validColumnNum;
	}
	char* get_column_name(int nIndex_column) const {
		return elibstl::clone_text(Get_column_name(nIndex_column - 1));
	}
	int get_row_num()const {
		if (!m_file.is_open()) {
			// 文件无法打开
			return 0;
		}
		return m_edbInf.m_recordNum;
	}
	void set_current(int cur_off) {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (cur_off < 0)cur_off = m_edbInf.m_recordNum > 0 ? 1 : 0;
		else if (cur_off > m_edbInf.m_recordNum)cur_off = m_edbInf.m_recordNum;
		m_cur_off = cur_off;
	};
	void to_end() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		m_cur_off = m_edbInf.m_recordNum;
	};
	void to_begin() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (m_edbInf.m_recordNum > 0)
		{
			m_cur_off = 1;
		}
		m_cur_off = 0;
	};
	void next() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}

		if (m_cur_off + 1 > m_edbInf.m_recordNum)
		{
			return;
		}
		m_cur_off++;
	}
	void previous() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (m_cur_off - 1 <= 0)
		{
			return;
		}
		m_cur_off--;
	}
	int get_current() const {
		return m_cur_off;
	}


	LPBYTE read(int nIndex_column) {
		std::vector<unsigned char> p_get_data;
		Read(nIndex_column - 1, m_cur_off - 1, &p_get_data);
		return elibstl::clone_bin(p_get_data.data(), p_get_data.size());
	}
	bool write(int nIndex_column, const std::vector<unsigned char>& pData) {
		return Write(nIndex_column - 1, m_cur_off - 1, pData);
	}
private:
	int m_cur_off = 0;
private:
	//处理文件头部,每次增减记录时需要操作
	inline void updata_heade() {
		if (!m_file.is_open()) {
			// 文件无法打开
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		//记录现在位置
		auto now = m_file.tellp();
		//移到文件头,不包括文件标识位置+
		m_file.seekp(EDBCHECKSIZE, std::ios::beg);
		m_file.write(reinterpret_cast<const char*>(&m_edbInf), sizeof(EDBHEADER));
		//移动回之前的位置
		m_file.seekp(now, std::ios::beg);

		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
	}
	//help,最后不会暴漏在头文件接口中
	inline  bool is_edbs_file() {

		// 确认文件大小
		m_file.seekg(0, std::ios::end);
		const char edb_flag[] = { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 };
		if (m_file.tellg() < sizeof(EDBHEADER) + EDBCHECKSIZE) {
			// 文件太小，不可能是有效的 edbs 文件

			return false;
		}

		m_file.seekg(0, std::ios::beg);
		char rfile_flag[EDBCHECKSIZE]{ 0 };
		m_file.read(rfile_flag, EDBCHECKSIZE);

		if (std::memcmp(rfile_flag, edb_flag, EDBCHECKSIZE) != 0) {
			// 文件不是 edbs 文件
			return false;
		}
		//如果是edbs文件需要移到文件首继续，因为后续操作需要，如果不是则不用管理，返回时会自动关闭
		m_file.seekg(0, std::ios::beg);
		return true;
	}
	inline bool has_big_data() {
		if (m_allCoLimns.empty())
			return true;
		for (const auto& temp : m_allCoLimns) {
			if (temp.m_ColumnType == DataType::REMARK || temp.m_ColumnType == DataType::BYTE_ARRAY)
			{
				return true;
			}
		}
		return false;
	}

};



static ARG_INFO Args[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ ("创建易语言数据库文件,此创建的有可能不兼容原版命令，但是原版创建的一定兼容新版命令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "字段信息",
		/*explain*/ ("创建易语言数据库文件,此创建的有可能不兼容原版命令，但是原版创建的一定兼容新版命令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    MAKELONG(34, 1),
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
		},
};



EXTERN_C void Fn_CreateEbds(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{



	if (pArgInf[0].m_dtDataType != SDT_TEXT)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	const char* filename = pArgInf[0].m_pText;


	if (nArgCount != 2)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	int nElementCount;

	lpColumInfo* pAryDataBegin = elibstl::get_array_element_inf<lpColumInfo*>(pArgInf[1].m_pAryData, &nElementCount);

	if (nElementCount < 1) {//参数二规定必须为数组
		pRetData->m_bool = FALSE;
		return;
	}
	std::vector<ColumnInfo> InAryData;
	if (!pAryDataBegin || nElementCount <= 0)
	{
		pRetData->m_bool = FALSE;
		return;
	}

	if (nElementCount > 0)
	{
		for (DWORD i = 0; i < nElementCount; i++) {
			if (pAryDataBegin[i])
			{
				ColumnInfo Temp;
				Temp.m_name = pAryDataBegin[i]->Name == nullptr ? "" : pAryDataBegin[i]->Name;
				Temp.m_strDataLength = pAryDataBegin[i]->StrDataLenth;
				Temp.m_dataType = (DataType)pAryDataBegin[i]->Type;
				InAryData.push_back(Temp);
			}


		}

	}//memcppy
	BOOL ret = Edbs::create_edbs(filename, InAryData) == 0;

	pRetData->m_bool = ret;
}

FucInfo e_lib_CreateEbds = { {
		/*ccname*/  ("创建EDBS"),
		/*egname*/  ("create_edbs"),
		/*explain*/ ("创建易语言数据库文件,此创建的有可能不兼容原版命令，但是原版创建的一定兼容新版命令"),
		/*category*/14,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_CreateEbds ,"Fn_CreateEbds" };


//构造
EXTERN_C void Fn_edbs_ex_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self = new Edbs;
}
//构造
FucInfo edbs_ex_structure = { {
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
	} ,Fn_edbs_ex_structure ,"Fn_edbs_ex_structure" };

//复制
EXTERN_C void fn_edbs_ex_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	auto rht = static_cast<Edbs*>(*pArgInf[1].m_ppCompoundData);

	*self = *rht;
}
FucInfo edbs_ex_copy = { {
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
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,fn_edbs_ex_copy ,"fn_edbs_ex_copy" };

//析构
EXTERN_C void fn_edbs_ex_des(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	if (self)
	{
		self->~Edbs();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo edbs_ex_destruct = { {
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
	} ,fn_edbs_ex_des ,"fn_edbs_ex_des" };


//打开
EXTERN_C void fn_edbs_ex_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	if (!pArgInf[1].m_pText)
	{
		pRetData->m_bool = false;
		return;
	}
	pRetData->m_bool = self->open(pArgInf[1].m_pText);
}
static ARG_INFO edbs_ex_open_Args[] =
{
	{
		/*name*/    "文件路径",
		/*explain*/ ("edbs/edb数据库文件"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo edbs_ex_open = { {
		/*ccname*/  "打开",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_ex_open_Args,
	} ,fn_edbs_ex_open ,"fn_edbs_ex_open" };


//取记录数
EXTERN_C void fn_edbs_get_row_num(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_int = self->get_row_num();
}




EXTERN_C void fn_edbs_ex_addpendnop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_bool = self->AppendBlank(pArgInf[1].m_int);
}
static ARG_INFO edbs_ex_addpendnop_Args[] =
{
	{
		/*name*/    "数量",
		/*explain*/ ("欲加入空数据的数量"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_ex_addpendnop = { {
		/*ccname*/  "加空记录",
		/*egname*/  "",
		/*explain*/ "本命令在当前数据库的尾部添加一条空记录，并将当前记录指针移动到最后的记录上。成功返回真，失败返回假。",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_ex_addpendnop_Args,
	} ,fn_edbs_ex_addpendnop ,"fn_edbs_ex_addpendnop" };

FucInfo edbs_get_row_num = { {
		/*ccname*/  "取记录数",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_get_row_num ,"fn_edbs_get_row_num" };

static INT s_dtCmdIndexcommobj_edbs_ex[] = { 132,133,134,135 ,136,137,138 ,139 ,140 ,141,142,143,144,145,146,147,148,149,150 };
namespace elibstl {


	LIB_DATA_TYPE_INFO edbs_ex =
	{
		"EBDS",
		"EBDS",
		"易语言数据库的对象操作",
		sizeof(s_dtCmdIndexcommobj_edbs_ex) / sizeof(s_dtCmdIndexcommobj_edbs_ex[0]),
		 s_dtCmdIndexcommobj_edbs_ex,
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




//跳到
EXTERN_C void fn_edbs_set_current(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);

	self->set_current(pArgInf[1].m_int);
}
static ARG_INFO edbs_set_current_Args[] =
{
	{
		/*name*/    "位置",
		/*explain*/ ("欲跳到的位置"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_set_current = { {
		/*ccname*/  "跳到",
		/*egname*/  "",
		/*explain*/ "设置当前位置,存在记录的数据你是无法跳到0的，不存在的数据一直为0",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_set_current_Args,
	} ,fn_edbs_set_current ,"fn_edbs_set_current" };



//读
EXTERN_C void fn_edbs_read(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_pBin = self->read(pArgInf[1].m_int);
}
static ARG_INFO fn_edbs_read_Args[] =
{
	{
		/*name*/    "字段或字段索引",
		/*explain*/ ("欲读取的字段"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_read = { {
		/*ccname*/  "读",
		/*egname*/  "读取当前行的指定字段数据",
		/*explain*/ "本命令在当前数据库的尾部添加一条空记录，并将当前记录指针移动到最后的记录上。成功返回真，失败返回假。",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  fn_edbs_read_Args,
	} ,fn_edbs_read ,"fn_edbs_read" };


EXTERN_C void fn_edbs_write(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_bool = self->write(pArgInf[1].m_int, elibstl::arg_to_vdata(pArgInf, 2));
}
static ARG_INFO fn_edbs_write_Args[] =
{
	{
		/*name*/    "字段或字段索引",
		/*explain*/ ("欲读取的字段"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},{
		/*name*/    "数据",
		/*explain*/ ("对应字段的数据，不足会填充0，超出会截断"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_write = { {
		/*ccname*/  "写",
		/*egname*/  "",
		/*explain*/ " 将数据写入到当前数据库中当前记录处的指定字段内。成功返回真",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  fn_edbs_write_Args,
	} ,fn_edbs_write ,"fn_edbs_write" };




EXTERN_C void fn_edbs_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->close();
}

FucInfo	edbs_close = { {
		/*ccname*/  "关闭",
		/*egname*/  "",
		/*explain*/ " 本命令关闭已经数据库",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_close ,"fn_edbs_close" };

EXTERN_C void fn_edbs_next(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->next();
}

FucInfo	edbs_next = { {
		/*ccname*/  "下一行",
		/*egname*/  "",
		/*explain*/ "移动至下一行",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_next ,"fn_edbs_next" };

EXTERN_C void fn_edbs_previous(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->previous();
}

FucInfo	edbs_previous = { {
		/*ccname*/  "上一行",
		/*egname*/  "",
		/*explain*/ " 移动至上一行",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_previous ,"fn_edbs_previous" };


EXTERN_C void fn_edbs_clean(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->clean();
}

FucInfo	edbs_clean = { {
		/*ccname*/  "清空",
		/*egname*/  "",
		/*explain*/ "清空数据库",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_clean ,"fn_edbs_clean" };

EXTERN_C void fn_edbs_begin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->begin();
}

FucInfo	edbs_begin = { {
		/*ccname*/  "开启事务",
		/*egname*/  "",
		/*explain*/ "仅为禁止IO,直至提交事务之前所有写入都不会实时更新到文件",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_begin ,"fn_edbs_begin" };

EXTERN_C void fn_edbs_commit(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->commit();
}

FucInfo	edbs_commit = { {
		/*ccname*/  "提交事务",
		/*egname*/  "",
		/*explain*/ "将所有更新写入磁盘",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_commit ,"fn_edbs_commit" };

EXTERN_C void fn_edbs_get_current(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_int = self->get_current();
}

FucInfo	edbs_get_current = { {
		/*ccname*/  "取当前位置",
		/*egname*/  "",
		/*explain*/ "获取当前记录指针行位置",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_get_current ,"fn_edbs_get_current" };


EXTERN_C void fn_edbs_get_column_name(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_pText = self->get_column_name(pArgInf[1].m_int);
}

FucInfo	edbs_get_column_name = { {
		/*ccname*/  "取字段名",
		/*egname*/  "",
		/*explain*/ "获取指定字段索引的字段名",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_TEXT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  fn_edbs_read_Args,
	} ,fn_edbs_get_column_name ,"fn_edbs_get_column_name" };


EXTERN_C void fn_edbs_get_column_num(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_int = self->get_column_num();
}

FucInfo	edbs_get_column_num = { {
		/*ccname*/  "取字段数",
		/*egname*/  "",
		/*explain*/ "获取数据库的字段数目",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,fn_edbs_get_column_num ,"fn_edbs_get_column_num" };


EXTERN_C void fn_edbs_set_column_name(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self->Set_column_name(pArgInf[1].m_int, std::string(elibstl::args_to_sdata(pArgInf, 2)));
}
static ARG_INFO fn_edbs_set_column_name_Args[] =
{
	{
		/*name*/    "字段索引",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲修改为的字段名",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_set_column_name = { {
		/*ccname*/  "置字段名",
		/*egname*/  "",
		/*explain*/ "设置指定字段索引的字段名",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  fn_edbs_set_column_name_Args,
	} ,fn_edbs_set_column_name ,"fn_edbs_set_column_name" };
