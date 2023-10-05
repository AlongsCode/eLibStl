#include"EcontrolHelp.h"
#include<string>
typedef struct _ColumnInfo//字段信息
{
	const char* Name;
	int Type;
	int StrDataLenth;
} *lpColumInfo;
#pragma once

#ifndef KRNLNDATABSE
#define KRNLNDATABSE
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<filesystem>
#include <map>
#include <unordered_set>
#include<cstring>
#include<functional>
namespace elibstl {
#pragma pack(1)//边界对齐
#ifdef _MSC_VER 
#pragma warning(disable:4996)
#endif 

	enum class ColumnDataType {
		BYTE = 1,         // 字节型
		SHORT_INT,    // 短整数型
		INT,          // 整数型
		LONG_INT,     // 长整数型
		FLOAT,        // 小数型
		DOUBLE,       // 双精度小数型
		BOOLEAN,      // 逻辑型
		DATE_TIME,    // 日期时间型
		PTR,		  // 指针型，文件数据库不会用到
		TEXT,         // 文本型
		BYTE_ARRAY,   // 字节集型
		REMARK,		  // 备注型
		PRIMARY_KEY	  // 主键
	};


	/*验证宏*/


	/*失败宏*/
	constexpr int EDB_ERROR_SUCCESS = 0;
	constexpr int EDB_ERROR_INVALID_COLUMN_NAME = -1;//字段名称错误
	constexpr int EDB_ERROR_INVALID_COLUMN_TYPE = -2;//数据类型错误
	constexpr int EDB_ERROR_INVALID_COLUMN_SIZE = -3;//数据长度为0
	constexpr int EDB_ERROR_DUPLICATE_COLUMN_NAME = -4;//字段名重复
	constexpr int EDB_ERROR_CREATE_EDBS = -5;//创建EDB失败
	constexpr int EDB_ERROR_CREATE_EDT = -6;//创建EDT失败
	constexpr int EDB_ERROR_INVALID_EDBSFILE = -7;//无效edb文件
	constexpr int EDB_ERROR_NOOPEN_EDBS = -8;//没打开文件
	constexpr int EDB_ERROR_INVALID_INDEX = -9;//无效的字段或记录索引
	constexpr int EDB_ERROR_INVALID_DATA_SIZE = -10;//写入错误的数据长度
	constexpr int EDB_ERROR_INVALID_DATA_TYPE = -11;//写入错误的数据类型
	constexpr int EDB_ERROR_TRANSACTION_OPENED = -12; //事务已开启
	constexpr int EDB_ERROR_TRANSACTION_NOT_OPENED = -13;//事务未开启
	constexpr int EDB_ERROR_INVALID_COLUMN_NUM = -14;//插入数据数量不匹配
	constexpr int EDB_ERROR_HASBEEN_OPEN_EDBS = -15; // 已经打开一个了
	constexpr int EDB_ERROR_INVALID_ROWS_NUM = -16;//加入无效数量的记录
	constexpr int EDB_ERROR_CANTOPEN_DAT = -17;//无法打开对应EDT文件
	constexpr int EDB_ERROR_HAS_DEL_OR_INVALID = -18;//主键无效或已经打上删除标记
	constexpr int EDB_ERROR_HAS_NO_DEL_OR_INVALID = -18;//主键无效或已经还未打上删除标记




	struct ColumnInfo {
		std::string m_name;
		ColumnDataType m_dataType = ColumnDataType::TEXT;
		unsigned int m_strDataLength = 20;
		ColumnInfo() = default;
		ColumnInfo(const std::string& n, ColumnDataType t = ColumnDataType::TEXT, int l = 20) : m_name(n), m_dataType(t), m_strDataLength(l) {}
	};



#ifndef _WIN32
#include <unistd.h>

#else
#include<windows.h>
#include <SHLWAPI.h>
#pragma comment(lib,"SHLWAPI.lib") 

#endif // !_WIN32

	class edb_file
	{
		class edt_file
		{

			struct edt_header//EDT创建数据
			{
				edt_header() {
					m_createTime = 0;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
					m_recordNum = 1;
					m_un_using_count = 0;
					m_nop_index = 0;
					std::fill(m_data, m_data + sizeof(m_data), 0);
				}
				double  m_createTime;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
				int m_recordNum;//未使用绑定外键1;
				int m_un_using_count;//未使用数量
				int m_nop_index;//最后腾出的数据索引;
				unsigned char m_data[484];
			};
			struct edt_data {
				int m_previous;//前一条空数据索引
				int m_next;//后一条数据索引,再次被使用时会将指向索引改为此数据,如果为空表示没有后续数据或者没有空余数据
				int m_data_size;//数据长度
				unsigned char m_pbuffer[500];
				edt_data() {
					std::memset(this, 0, sizeof(*this));
				}
			};
			static constexpr int BUFFER_SIZE = 500;/*块大小*/
			static constexpr char CHECK_EDT[] = { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 };
		private://成员
			std::fstream  m_file_edt;  // EDT文件
			std::string m_filename;
			edt_header m_edb_inf;
		private://私有函数
			bool __check_close_file() {
				if (!m_file_edt) {
					m_file_edt.close();
					return false;
				}
				return true;
			}
			bool __is_edt_file() {
				m_file_edt.seekg(0, std::ios::end);
				if (m_file_edt.tellg() < sizeof(edt_data)) {
					return false;
				}

				m_file_edt.seekg(0, std::ios::beg);

				char rfile_flag[sizeof(CHECK_EDT)];
				m_file_edt.read(rfile_flag, sizeof(CHECK_EDT));

				if (std::memcmp(rfile_flag, CHECK_EDT, sizeof(CHECK_EDT)) != 0) {
					return false;
				}
				m_file_edt.seekg(0, std::ios::beg);
				return true;
			}
		private://成员

			inline static std::string __rename_file_ext(const std::string& fname, const std::string& extname) {
				if (extname.empty()) {
					return fname;
				}
				std::filesystem::path filepath(fname);
				std::string suffix = extname;
				if (extname[0] != '.') {
					suffix = "." + suffix;
				}
				filepath.replace_extension(suffix);
				return filepath.string();
			}
		public://全局函数
			static bool create(const std::string& nfilename, double time) {
				std::string edtFileName = __rename_file_ext(nfilename, ".EDT");
				// 文件操作放在额外的作用域中，保证文件正确关闭
				{
					std::ofstream edtFile(edtFileName, std::ios::binary);
					if (!static_cast<const std::ios&>(edtFile)) {
						// 创建EDT文件失败
						return false;
					}
					// 写入EDT文件头部信息
					edt_header edtHeader;
					edtHeader.m_createTime = time;
					edtFile.write(CHECK_EDT, sizeof(CHECK_EDT));
					edtFile.write(reinterpret_cast<char*>(&edtHeader), sizeof(edt_header));
				}
				return true;
			}
		public://成员函数
			bool is_open() const {
				return m_file_edt.is_open();
			}
			bool open(const std::string& filename, double n_time) {
				if (m_file_edt.is_open()) {
					return false;
				}

				m_file_edt.open(filename, std::ios::binary | std::ios::out | std::ios::in);
				if (!__check_close_file()) {
					return false;
				}
				if (!__is_edt_file()) {
					return false;
				}
				static constexpr auto edt_check_size = sizeof(CHECK_EDT);
				m_file_edt.seekg(edt_check_size);
				m_file_edt.read(reinterpret_cast<char*>(&m_edb_inf), sizeof(edt_header));
				if (!__check_close_file() || m_edb_inf.m_recordNum <= 0) {
					return false;
				}

				m_file_edt.seekg(0, std::ios::end);
				auto fileSize = m_file_edt.tellg();
				if (!__check_close_file() || fileSize < static_cast<decltype(fileSize)>(sizeof(edt_data)) * m_edb_inf.m_recordNum) {
					return false;
				}
				/*if (n_time != m_edb_inf.m_createTime) {
					return false;
				}*/
				m_filename = filename;
				return true;
			}
			void read(int n_index, std::vector<unsigned char>& n_pData) {
				n_pData.clear();
				if (!m_file_edt.is_open() || n_index < 0 || n_index >= m_edb_inf.m_recordNum) {
					return;
				}

				m_file_edt.seekg(n_index * sizeof(edt_data), std::ios::beg);
				while (true) {
					edt_data temp_data;

					m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(temp_data));
					if (temp_data.m_data_size == 0 || m_file_edt.fail() || m_file_edt.bad()) {
						return;
					}

					n_pData.insert(n_pData.end(), temp_data.m_pbuffer, temp_data.m_pbuffer + temp_data.m_data_size);
					if (temp_data.m_next == 0) {
						return;
					}

					m_file_edt.clear();
					m_file_edt.seekg(temp_data.m_next * sizeof(edt_data), std::ios::beg);
				}
			}
			int write(const std::vector<unsigned char>& n_pData) {
				if (!m_file_edt.is_open() || n_pData.empty()) {
					return 0;
				}

				int data_len = static_cast<int>(n_pData.size());
				int last_segment_size = data_len % BUFFER_SIZE;
				int segment_num = data_len / BUFFER_SIZE + (last_segment_size > 0 ? 1 : 0);
				int s_last_index = 0;
				int ret = 0;

				for (int i = 0; i < segment_num; ++i) {
					edt_data temp_data;
					int i_index;
					if (m_edb_inf.m_un_using_count > 0) {
						i_index = m_edb_inf.m_nop_index;
						m_file_edt.seekg(i_index * sizeof(edt_data), std::ios::beg);
						m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);
						m_edb_inf.m_un_using_count--;
						m_edb_inf.m_nop_index = temp_data.m_next;
					}
					else {
						i_index = m_edb_inf.m_recordNum++;
					}

					auto i_next = m_edb_inf.m_un_using_count > 0 ? m_edb_inf.m_nop_index : m_edb_inf.m_recordNum;
					auto data_size = i == segment_num - 1 ? last_segment_size : BUFFER_SIZE;
					std::memcpy(temp_data.m_pbuffer, n_pData.data() + static_cast<size_t>(i) * static_cast<size_t>(BUFFER_SIZE), data_size);
					temp_data.m_data_size = data_size;

					if (i == 0) {
						ret = i_index;
						temp_data.m_previous = 0;
						temp_data.m_next = segment_num == 1 ? 0 : i_next;
					}
					else if (i == segment_num - 1) {
						temp_data.m_previous = s_last_index;
						temp_data.m_next = 0;
					}
					else {
						temp_data.m_previous = s_last_index;
						temp_data.m_next = i_next;
					}

					s_last_index = i_index;
					m_file_edt.seekp(i_index * sizeof(edt_data), std::ios::beg);
					m_file_edt.write(reinterpret_cast<const char*>(&temp_data), sizeof(temp_data));
				}

				return ret;
			}
			void del(int n_index) {
				if (!m_file_edt.is_open() || n_index < 0 || n_index >= m_edb_inf.m_recordNum) {
					return;
				}

				edt_data temp_data;
				m_file_edt.seekg(n_index * sizeof(edt_data), std::ios::beg);
				m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);

				if (temp_data.m_next != 0) {
					del(temp_data.m_next);
				}

				m_file_edt.seekp(n_index * sizeof(edt_data), std::ios::beg);
				temp_data.m_next = m_edb_inf.m_nop_index;
				m_edb_inf.m_nop_index = n_index;
				m_edb_inf.m_un_using_count++;
				m_file_edt.write(reinterpret_cast<const char*>(&temp_data), sizeof(int) * 2);
			}
			int change(int n_index, const std::vector<unsigned char>& n_pData) {
				del(n_index);
				if (n_pData.empty()) {
					return 0;
				}
				int new_index = write(n_pData);
				return new_index;
			}
			bool clean() {
				if (!is_open())
				{
					return false;
				}
				close(); // Reuse close() method
				if (!create(m_filename.c_str(), m_edb_inf.m_createTime))
					return false;
				if (!open(m_filename.c_str(), m_edb_inf.m_createTime))
					return false;;
				return true;
			}
			void close() {
				if (m_file_edt.is_open()) {
					m_file_edt.close();
				}
				m_filename.clear(); // Use clear() method instead of assigning a new empty string
				m_edb_inf = edt_header(); // This is already optimal
			}
			void updata() {
				if (!m_file_edt.is_open()) {
					return;
				}
				/*更新文件头*/
				m_file_edt.seekp(sizeof(CHECK_EDT), std::ios::beg);
				m_file_edt.write(reinterpret_cast<char*>(&m_edb_inf), sizeof(m_edb_inf));
				m_file_edt.flush(); // This is already optimal
			};

		};
		std::map<ColumnDataType, int> type_lengths = {
			{ColumnDataType::BYTE, 1},
			{ColumnDataType::SHORT_INT, 2},
			{ColumnDataType::INT, 4},
			{ColumnDataType::LONG_INT, 8},
			{ColumnDataType::FLOAT, 4},
			{ColumnDataType::DOUBLE, 8},
			{ColumnDataType::BOOLEAN, 1},
			{ColumnDataType::DATE_TIME, 8},
			{ColumnDataType::PTR, 4},
			{ColumnDataType::BYTE_ARRAY, 4},
			{ColumnDataType::REMARK, 4},
			{ColumnDataType::PRIMARY_KEY, 4} // 主键型默认长度为4
		};

		struct edb_header {

			double m_createTime = 0;//OLE时间
			int m_recordNum = 0;//当前记录数量
			int m_unusedPrimaryKey = 1;//目前可使用的主键,每次插入空数据会自增1,不可重复,仅自增
			int  m_totalLength = 0;;//所有字段所需的长度,单位字节
			unsigned char  m_blankBYTE[84]{ 0 };//预留空间
			int m_validColumnNum = 0;;//有效字段数
		};
		struct colimn_data
		{
			char m_ColumnName[16]{ 0 };  // 名称最大16字节,
			int m_delimiter = 0;    // 分隔符
			ColumnDataType m_ColumnType = ColumnDataType::TEXT;       // 起始偏移位置
			int m_offset = 0;           // 非文本型需求数据长度;
			int m_strlenth = 0;         // 如为文本类型则需要长度;
			unsigned char m_Table[40]{ 0 };
		};
		static constexpr char CHECK_EDB[] = { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 };
	public:/*全局静态函数*/
		static
			int
			create_edbs(const std::string& nfilename, const std::vector< ColumnInfo>& columns) {

			static  std::map<ColumnDataType, int> stype_lengths = {
			{ColumnDataType::BYTE, 1},
			{ColumnDataType::SHORT_INT, 2},
			{ColumnDataType::INT, 4},
			{ColumnDataType::LONG_INT, 8},
			{ColumnDataType::FLOAT, 4},
			{ColumnDataType::DOUBLE, 8},
			{ColumnDataType::BOOLEAN, 1},
			{ColumnDataType::DATE_TIME, 8},
			{ColumnDataType::PTR, 4},
			{ColumnDataType::BYTE_ARRAY, 4},
			{ColumnDataType::REMARK, 4},
			{ColumnDataType::PRIMARY_KEY, 4} // 主键型默认长度为4
			};
			/*对于字段的有效性验证和数据提取*/
			std::unordered_set<std::string> columnNames;

			std::vector<colimn_data> wFileCoumns;

			//默认要对数据库进行一个主键大小,同时也是偏移和拓展出去的长度
			std::uint32_t all_columns_datasize = stype_lengths[ColumnDataType::PRIMARY_KEY];
			//有效字段数量
			std::uint32_t valid_column_num = 0;

			bool bIsHaveBigData = false;
			if (columns.empty()) {
				return EDB_ERROR_INVALID_COLUMN_NAME;  // 没有有效列信息
			}
			for (ColumnInfo column : columns)
			{

				// 判断字段名是否已经出现过
				if (columnNames.count(column.m_name) > 0)
				{
					return EDB_ERROR_DUPLICATE_COLUMN_NAME;
				}
				columnNames.insert(column.m_name);


				if (!__is_vaild_name(column.m_name))
				{

					return  EDB_ERROR_INVALID_COLUMN_NAME;
				}


				if (column.m_dataType< ColumnDataType::BYTE || column.m_dataType > ColumnDataType::REMARK)
				{
					return EDB_ERROR_INVALID_COLUMN_TYPE;
				}



				//准备将其写入文件中的字段数据
				colimn_data TempwFileCoumns;
				TempwFileCoumns.m_ColumnType = column.m_dataType;

				std::strcpy(TempwFileCoumns.m_ColumnName, column.m_name.c_str());
				TempwFileCoumns.m_ColumnName[15] = '\0';
				if (std::strlen(TempwFileCoumns.m_ColumnName) < 15)
				{
					std::memset(&TempwFileCoumns.m_ColumnName[strlen(TempwFileCoumns.m_ColumnName)], 0, 15 - strlen(TempwFileCoumns.m_ColumnName));
				}

				//通过名称和类型判断则进行长度验证
				//首先是判断是否为文本型
				std::uint32_t TempColumnSize = 0;
				//EDBS不对文本型最大长度进行限制
				if (column.m_dataType == ColumnDataType::TEXT)
				{
					//验证
					TempColumnSize = column.m_strDataLength;
					//准备写入二进制数据
					TempwFileCoumns.m_strlenth = column.m_strDataLength;
				}
				else
				{
					TempColumnSize = stype_lengths[column.m_dataType];
				}

				if (TempColumnSize == 0)
				{
					return EDB_ERROR_INVALID_COLUMN_SIZE;
				}

				if (column.m_dataType == ColumnDataType::REMARK || column.m_dataType == ColumnDataType::BYTE_ARRAY)
				{
					bIsHaveBigData = true;
				}
				TempwFileCoumns.m_offset = all_columns_datasize;
				wFileCoumns.push_back(TempwFileCoumns);
				all_columns_datasize += TempColumnSize;
				valid_column_num++;
			}

			auto filename = nfilename;// __rename_file_ext(nfilename, ".edbs");

			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open())
			{
				// 创建EDT文件失败
				return EDB_ERROR_CREATE_EDBS;
			}
			edb_header EDB;
			auto time = __get_nowtm_to_oletm();
			EDB.m_createTime = time;
			EDB.m_validColumnNum = valid_column_num;
			EDB.m_totalLength = all_columns_datasize;
			file.write(CHECK_EDB, sizeof(CHECK_EDB));
			file.write(reinterpret_cast<char*>(&EDB), sizeof(edb_header));
			// 然后写入字段数据
			for (auto& column : wFileCoumns)
			{
				file.write(reinterpret_cast<char*>(&column), sizeof(colimn_data));
			}
			file.close();

			if (bIsHaveBigData)
			{
				edt_file::create(nfilename, time);
			}
			return EDB_ERROR_SUCCESS;
		}
	private:/*全局辅助函数*/
		//获取时间并转化为OLE时间,此代码为兼容EDB原版
		inline static
			double
			__get_nowtm_to_oletm() {
			auto now = std::chrono::system_clock::now();
			auto time_t_now = std::chrono::system_clock::to_time_t(now);
			auto  t = static_cast<time_t>(time_t_now);
			return static_cast<double>(25569 + t / 86400.0 + 8.0 / 24.0);

		}
		/*EDBS并不会进行过多限制，但会进行严格的规则审查，不满足则不允许创建*/
		inline static
			bool
			__is_vaild_name(const std::string& text) {
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
		inline static
			std::string
			__rename_file_ext(const std::string& fname, const std::string& extname) {
			if (extname.empty()) {
				return fname;
			}
			std::filesystem::path filepath(fname);
			std::string suffix = extname;
			if (extname[0] != '.') {
				suffix = "." + suffix;
			}
			filepath.replace_extension(suffix);
			return filepath.string();
		}
	public:
		inline
			edb_file() = default;
		inline
			edb_file(const std::string& filename) :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {
			// 已经打开就不再打开
			if (m_file.is_open()) {
				m_errorCode = EDB_ERROR_HASBEEN_OPEN_EDBS;
				return;
			}

			m_file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}

			if (!__is_edbs_file()) {
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}

			// 获取EDB信息
			m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(edb_header));

			// 无有效字段
			if (m_edbInf.m_validColumnNum <= 0) {
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}

			auto allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(colimn_data);
			auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;

			// 再次验证文件大小
			m_file.seekg(0, std::ios::end);
			size_t fileSize = m_file.tellg();

			if (fileSize < sizeof(edb_header) + sizeof(CHECK_EDB) + allCoLimnsize + allRowsize) {
				// 文件太小，不可能读取所有列信息和足够的数据
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}

			m_file.seekg(sizeof(edb_header) + sizeof(CHECK_EDB));
			m_allCoLimns.resize(m_edbInf.m_validColumnNum);
			m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
			m_dataOffset = static_cast<int>(m_file.tellg());

			if (__has_big_data()) {
				// 打开对应EDT文件
				if (!m_edt_file.open(__rename_file_ext(filename, ".EDT"), m_edbInf.m_createTime)) {
					m_file.close();
					// 文件无法打开
					m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
					return;
				}
			}

			/*处理初始化数据*/
			if (m_edbInf.m_recordNum > 0) {
				m_cur_off = 1;
			}

			m_fileName = filename;
			return;
		}
		inline
			bool
			open(const std::string& filename) {
			// 已经打开就不再打开
			if (m_file.is_open()) {
				m_errorCode = EDB_ERROR_HASBEEN_OPEN_EDBS;
				return false;
			}

			m_file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}

			if (!__is_edbs_file()) {
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}

			// 获取EDB信息
			m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(edb_header));

			// 无有效字段
			if (m_edbInf.m_validColumnNum <= 0) {
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}

			auto allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(colimn_data);
			auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;

			// 再次验证文件大小
			m_file.seekg(0, std::ios::end);
			size_t fileSize = m_file.tellg();

			if (fileSize < sizeof(edb_header) + sizeof(CHECK_EDB) + allCoLimnsize + allRowsize) {
				// 文件太小，不可能读取所有列信息和足够的数据
				m_file.close();
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}

			m_file.seekg(sizeof(edb_header) + sizeof(CHECK_EDB));
			m_allCoLimns.resize(m_edbInf.m_validColumnNum);
			m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
			m_dataOffset = static_cast<int>(m_file.tellg());

			if (__has_big_data()) {
				// 打开对应EDT文件
				if (!m_edt_file.open(__rename_file_ext(filename, ".EDT"), m_edbInf.m_createTime)) {
					m_file.close();
					// 文件无法打开
					m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
					return false;
				}
			}

			/*处理初始化数据*/
			if (m_edbInf.m_recordNum > 0) {
				m_cur_off = 1;
			}

			m_fileName = filename;
			return true;
		}
		inline
			void clean() {
			if (!m_file.is_open())
			{
				debug_put(m_file.is_open());
				return;
			}
			/*关闭*/
			if (m_edt_file.is_open())
			{
				m_edt_file.close();
				//	m_edt_file.clean();
			}
	
			
			

			std::vector<ColumnInfo> _ColumnInfo;
			/*重建*/
			debug_put(m_allCoLimns.size());
			for (const auto& temp : m_allCoLimns)
			{
				ColumnInfo i_ColumnInfo;
				i_ColumnInfo.m_dataType = temp.m_ColumnType;
				i_ColumnInfo.m_name = temp.m_ColumnName;
				
				i_ColumnInfo.m_strDataLength = temp.m_strlenth;
				_ColumnInfo.push_back(i_ColumnInfo);
			}

			m_file.clear();
			m_file.close();
			char edt_file_name[MAX_PATH]{ 0 };
			strcpy_s(edt_file_name, m_fileName.c_str());
			PathRenameExtensionA(edt_file_name, "EDT");
			std::remove(m_fileName.c_str());
			std::remove(edt_file_name);

			m_errorCode = create_edbs(m_fileName, _ColumnInfo);
			debug_put(m_errorCode);
			/*打开*/
			open(m_fileName);
	
		}
		inline
			void
			close() {
			if (m_edt_file.is_open())
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
		template<typename T>
		inline
			void
			read(int nIndex_column, int nIndex_row, T& pData) {
			std::memset(&pData, 0, sizeof(T));
			std::vector<unsigned char> vpData;
			read(nIndex_column, nIndex_row, vpData);
			if (vpData.size() < sizeof(T))
				return;
			pData = *reinterpret_cast<T*>(vpData.data());
		}
		inline
			void
			read(int nIndex_column, int nIndex_row, std::vector<unsigned char>& pData) {
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
			if (m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::TEXT)
			{	//否则默认长度
				needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
			}

			if (m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::REMARK)
			{
				pData.resize(needsize, 0);
				m_file.read(reinterpret_cast<char*>(pData.data()), pData.size());
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
					m_edt_file.read(index, pData);
				}

			}


		};
		/*索引从0,0开始*/
		inline
			bool
			write(int nIndex_column, int nIndex_row, const std::vector<unsigned char>& data) {
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}
			if (m_edbInf.m_recordNum <= 0 || nIndex_row < 0)
			{
				m_errorCode = EDB_ERROR_INVALID_INDEX;
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
			if (m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::TEXT)
			{	//否则默认长度
				needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
			}

			if (m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != ColumnDataType::REMARK)
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
						auto padData = new char[needsize - data.size()] { 0 };
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

		inline
			bool
			del(int nIndex_row) {
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}
			if (m_edbInf.m_recordNum<=0)
			{
				m_errorCode = EDB_ERROR_INVALID_INDEX;
				return false;
			}
			if (nIndex_row <= 0)
				nIndex_row = m_cur_off-1 ;
			//debug_put(nIndex_row);
			if (nIndex_row <= 0) {
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}
			
			if (nIndex_row + 1 > m_edbInf.m_recordNum)
			{
				m_errorCode = EDB_ERROR_INVALID_INDEX;
				return false;
			}

			
			m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength);
			int primary_key = 0;
			m_file.read(reinterpret_cast<char*>(&primary_key), sizeof(int));
			if (primary_key <= 0) {
				m_errorCode = EDB_ERROR_HAS_DEL_OR_INVALID;
				return false;
			}

			m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength);
			primary_key = ~primary_key + 1;
			m_file.write(reinterpret_cast<char*>(&primary_key), sizeof(int));

			/*处理字节集和备注型*/

			if (!m_isTransactionOpened)
				m_file.flush();

			return  true;
		}
		inline
			bool
			cancel_del(int nIndex_row) {
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}
			if (m_edbInf.m_recordNum <= 0)
			{
				m_errorCode = EDB_ERROR_INVALID_INDEX;
				return false;
			}
			if (nIndex_row <= 0)
				nIndex_row = m_cur_off - 1;
			//debug_put(nIndex_row);
			if (nIndex_row <= 0) {
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}

			if (nIndex_row + 1 > m_edbInf.m_recordNum)
			{
				m_errorCode = EDB_ERROR_INVALID_INDEX;
				return false;
			}

			m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength);
			int primary_key = 0;
			m_file.read(reinterpret_cast<char*>(&primary_key), sizeof(int));
			if (primary_key > 0) {
				m_errorCode = EDB_ERROR_HAS_DEL_OR_INVALID;
				return false;
			}

			m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength);
			primary_key = ~primary_key + 1;
			m_file.write(reinterpret_cast<char*>(&primary_key), sizeof(int));

			/*处理字节集和备注型*/

			if (!m_isTransactionOpened)
				m_file.flush();

			return  true;
		}
		inline
			std::string
			get_column_name(int nIndex_column)const {
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
		inline
			void
			set_column_name(int nIndex_column, const std::string& name) {
			if (!m_file.is_open()) {
				// 文件无法打开
				return;
			}
			if (nIndex_column < 0 || nIndex_column >= m_allCoLimns.size())
			{
				return;
			}
			//COLIMNDATA TempwFileCoumns = m_allCoLimns[nIndex_column];
			std::strcpy(m_allCoLimns[nIndex_column].m_ColumnName, name.c_str());
			m_allCoLimns[nIndex_column].m_ColumnName[15] = '\0';
			if (std::strlen(m_allCoLimns[nIndex_column].m_ColumnName) < 15)
			{
				std::memset(&m_allCoLimns[nIndex_column].m_ColumnName[strlen(m_allCoLimns[nIndex_column].m_ColumnName)], 0, 15 - strlen(m_allCoLimns[nIndex_column].m_ColumnName));
			}
			__updata_heade();
			;
		}
		inline
			bool
			append_blank(int nCount) {
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
			__updata_heade();
			to_end();
			return  true;
		}
		inline
			void
			to_end() {
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return;
			}
			m_cur_off = m_edbInf.m_recordNum;
		};
		inline
			bool pop() {
			/*遍历寻找打上删除标记的行*/
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return false;
			}

			//size_t i = 0;
			//while (i< m_edbInf.m_recordNum)
			//{
			//	m_file.seekg(m_dataOffset + i * m_edbInf.m_totalLength, std::ios::beg);
			//	int primary_key = 0;
			//	m_file.read(reinterpret_cast<char*>(&primary_key), sizeof(int));
			//	if (primary_key < 0) {
			//		m_edbInf.m_recordNum--;
			//		__updata_heade();
			//		/*删除时一定会强制刷盘*/
			//		std::vector<std::pair<std::streampos, std::streampos>> segments;
			//		segments.push_back({ m_dataOffset + i * m_edbInf.m_totalLength ,m_dataOffset + (i + 1) * m_edbInf.m_totalLength });
			//		__delete_segments(segments);
			//		m_file.flush();
			//	}
			//	i++;
			//}

			
			std::vector<std::pair<std::streampos, std::streampos>> segments;
			auto recordNu = m_edbInf.m_recordNum;
			for (int i = 0; i < recordNu; i++)
			{
				m_file.seekg(m_dataOffset + i * m_edbInf.m_totalLength, std::ios::beg);
				int primary_key = 0;
				m_file.read(reinterpret_cast<char*>(&primary_key), sizeof(int));
				debug_put(primary_key);
				if (primary_key < 0) {
					segments.push_back({ m_dataOffset + i * m_edbInf.m_totalLength ,m_dataOffset + (i + 1) * m_edbInf.m_totalLength });
					m_edbInf.m_recordNum--;
				}
			}
			__updata_heade();
			/*删除时一定会强制刷盘*/
			m_file.flush();
			
			__delete_segments(segments);

			return true;;
		}

		inline
			int
			get_error_code() const {
			return m_errorCode;
		}
		inline
			int
			get_column_num()const {
			if (!m_file.is_open()) {
				// 文件无法打开
				return 0;
			}
			return m_edbInf.m_validColumnNum;
		}
		using ReadCallback = std::function<void(int, const std::vector<uint8_t>&)>;
		/*异步读取*/
		inline
			//	void async_read(int column, int row, ReadCallback callback) {
			//	// 在新线程中执行读操作并通过回调返回
			//	std::thread([=]() {
			//		std::vector<uint8_t> data;
			//		read(column, row, data);
			//		callback(column, data);
			//		}).detach();
			//}
			inline
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
		inline
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
		inline
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
		inline
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
		inline
			int get_current() const {
			return m_cur_off;
		}
		inline
			int
			get_row_num()const {
			if (!m_file.is_open()) {
				// 文件无法打开
				return 0;
			}
			return m_edbInf.m_recordNum;
		}
		/*此同易,从1-1开始*/
		inline
			auto read(int nIndex_column) {
			std::vector<unsigned char> p_get_data;
			read(nIndex_column - 1, m_cur_off - 1, p_get_data);
			return p_get_data;
		}
		/*此同易,从1-1开始*/
		inline
			bool write(int nIndex_column, const std::vector<unsigned char>& pData) {
			return write(nIndex_column - 1, m_cur_off - 1, pData);
		}
		/*禁止io*/
		inline
			void
			cant_be_io() {
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
		//刷盘
		inline
			void
			commit_io() {
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

	private:
		inline
			void __delete_segments(const std::vector<std::pair<std::streampos, std::streampos>>& segments) {
			std::string tempFileName = __get_temp_file("");
			std::ofstream tempFile(tempFileName, std::ios::binary);

			// 获取文件大小
			m_file.seekg(0, std::ios::end);
			std::streampos fileSize = m_file.tellg();
			m_file.seekg(0, std::ios::beg);

			std::streampos currentPosition = 0;

			for (const auto& segment : segments) {
				std::streampos start = segment.first;
				std::streampos end = segment.second;

				// 将数据段之前的数据写入临时文件
				std::vector<char> buffer(start - currentPosition);
				m_file.read(buffer.data(), start - currentPosition);
				tempFile.write(buffer.data(), start - currentPosition);

				// 跳过要删除的数据段
				m_file.seekg(end, std::ios::beg);
				currentPosition = end;
			}

			// 将剩余的数据写入临时文件
			std::vector<char> buffer(fileSize - currentPosition);
			m_file.read(buffer.data(), fileSize - currentPosition);
			tempFile.write(buffer.data(), fileSize - currentPosition);

			// 关闭文件
			m_file.close();
			tempFile.close();

			// 删除原始文件
			std::remove(m_fileName.c_str());

			// 重命名临时文件为原始文件名
			std::rename(tempFileName.c_str(), m_fileName.c_str());
		}
		//处理文件头部,每次增减记录时需要操作
		inline
			void
			__updata_heade() {
			if (!m_file.is_open()) {
				// 文件无法打开
				m_errorCode = EDB_ERROR_NOOPEN_EDBS;
				return;
			}
			//记录现在位置
			auto now = m_file.tellp();
			//移到文件头,不包括文件标识位置+
			m_file.seekp(sizeof(CHECK_EDB), std::ios::beg);
			m_file.write(reinterpret_cast<const char*>(&m_edbInf), sizeof(m_edbInf));
			//移动回之前的位置
			m_file.seekp(now, std::ios::beg);

			if (!m_isTransactionOpened)
			{
				m_file.flush();
			}
		}
		inline
			bool
			__has_big_data() const {
			if (m_allCoLimns.empty()) {
				return true;
			}

			for (const auto& temp : m_allCoLimns) {
				if (temp.m_ColumnType == ColumnDataType::REMARK || temp.m_ColumnType == ColumnDataType::BYTE_ARRAY) {
					return true;
				}
			}

			return false;
		}
#ifndef _WIN32
		inline static std::string
			__get_temp_file(const std::string& dir)
		{
			std::string tempFileName = dir + "/tempXXXXXX";  // 文件名模板，"XXXXXX"会被替换为随机字符串

			char* tempFilePath = new char[tempFileName.size() + 1];
			std::strcpy(tempFilePath, tempFileName.c_str());

			int fileDescriptor = mkstemp(tempFilePath);  // 创建临时文件

			if (fileDescriptor == -1)
			{
				std::cerr << "无法创建临时文件" << std::endl;
				delete[] tempFilePath;
				return "";
			}

			close(fileDescriptor);  // 关闭文件描述符

			std::string result(tempFilePath);
			delete[] tempFilePath;

			return result;
		}
#else
		inline static std::string
			__get_temp_file(const std::string& dir) {
			std::string DirName;
			DirName.resize(MAX_PATH);

			if (dir.empty()) {
				if (GetTempPathA(MAX_PATH, DirName.data()) == FALSE)
					DirName.clear();
			}
			else {
				DirName = dir;
			}

			char TempFileName[MAX_PATH];
			std::size_t nLen = DirName.length();

			if (!DirName.empty() && DirName[nLen - 1] != '\\') {
				DirName += '\\';
			}

			do {
				std::sprintf(TempFileName, "%s%x.tmp", DirName.c_str(), GetTickCount());
			} while (PathFileExistsA(TempFileName));

			std::string pText(TempFileName);
			return pText;
		}
#endif
		inline bool
			__is_edbs_file() {
			// 确认文件大小
			m_file.seekg(0, std::ios::end);
			if (m_file.tellg() < sizeof(edb_header) + sizeof(CHECK_EDB)) {
				// 文件太小，不可能是有效的EDBS文件
				return false;
			}

			m_file.seekg(0, std::ios::beg);
			char rfile_flag[sizeof(CHECK_EDB)]{ 0 };
			m_file.read(rfile_flag, sizeof(CHECK_EDB));

			if (std::memcmp(rfile_flag, CHECK_EDB, sizeof(CHECK_EDB)) != 0) {
				// 文件不是EDBS文件
				return false;
			}

			return true;
		}


	private:
		int m_cur_off{ 0 };                      // 当前行
		edt_file m_edt_file;                // EDT文件对象
		std::string m_fileName;             // 文件名
		std::fstream m_file;                // 文件流
		int m_dataOffset{ 0 };                   // 数据开始位置
		int m_errorCode{ EDB_ERROR_SUCCESS };                    // 错误码
		edb_header m_edbInf;                 // 数据表信息
		std::vector<colimn_data> m_allCoLimns;// 字段信息
		bool m_isTransactionOpened{ false };         // 是否开启事务
	};




}
#endif




static ARG_INFO Args[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ ("创建易语言数据库文件,此创建的有可能不兼容原版命令，但是原版创建的一定兼容新版命令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "字段信息",
		/*explain*/ ("创建易语言数据库文件,此创建的有可能不兼容原版命令，但是原版创建的一定兼容新版命令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::KRNLN_EDB,
		/*default*/ 0,
		/*state*/   ArgMark::AS_RECEIVE_ARRAY_DATA,
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
	std::vector<elibstl::ColumnInfo> InAryData;
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
				elibstl::ColumnInfo Temp;
				Temp.m_name = pAryDataBegin[i]->Name == nullptr ? "" : pAryDataBegin[i]->Name;
				Temp.m_strDataLength = pAryDataBegin[i]->StrDataLenth;
				Temp.m_dataType = static_cast<elibstl::ColumnDataType> (pAryDataBegin[i]->Type);
				InAryData.push_back(Temp);
			}


		}

	}//memcppy
	BOOL ret = elibstl::edb_file::create_edbs(filename, InAryData) == 0;

	pRetData->m_bool = ret;
}

FucInfo e_lib_CreateEbds = { {
		/*ccname*/  ("创建易数据库"),
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	self = new elibstl::edb_file;
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	auto rht = static_cast<elibstl::edb_file*>(*pArgInf[1].m_ppCompoundData);
	put_errmsg(L"数据库文件读写是唯一的,不应在不同位置创建多个对象读写同一易数据库文件,此会引发超级无敌的异常,编译版本下同样会崩溃!");
	exit(0);
	//*self = *rht;
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	if (self)
	{
		self->~edb_file();
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
		/*state*/   ArgMark::AS_NONE,
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_int = self->get_row_num();
}




EXTERN_C void fn_edbs_ex_addpendnop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_bool = self->append_blank(pArgInf[1].m_int);
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
		/*state*/   ArgMark::AS_NONE,
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






//跳到
EXTERN_C void fn_edbs_set_current(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);

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
		/*state*/   ArgMark::AS_NONE,
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	auto temp = self->read(pArgInf[1].m_int);
	pRetData->m_pBin = elibstl::clone_bin(temp.data(), temp.size());
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
		/*state*/   ArgMark::AS_NONE,
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
		/*state*/   ArgMark::AS_NONE,
	},{
		/*name*/    "数据",
		/*explain*/ ("对应字段的数据，不足会填充0，超出会截断"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	self->cant_be_io();
}

FucInfo	edbs_begin = { {
		/*ccname*/  "禁止IO",
		/*egname*/  "cant_be_io",
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	self->commit_io();
}

FucInfo	edbs_commit = { {
		/*ccname*/  "允许IO",
		/*egname*/  "",
		/*explain*/ "刷盘,将所有更新写入磁盘",
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_pText = elibstl::clone_text(self->get_column_name(pArgInf[1].m_int));
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
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
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	self->set_column_name(pArgInf[1].m_int, std::string(elibstl::args_to_sdata(pArgInf, 2)));
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
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "欲修改为的字段名",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
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






EXTERN_C void fn_edbs_del(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_bool = self->del(pArgInf[1].m_int - 1);
}
static ARG_INFO fn_edbs_del_Args[] =
{
	{
		/*name*/    "字段索引",
		/*explain*/ ("小于等于0则默认为当前位置"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ -1,
		/*state*/   ArgMark::AS_HAS_DEFAULT_VALUE,
	}
};
FucInfo	edbs_del = { {
		/*ccname*/  "删除",
		/*egname*/  "",
		/*explain*/ "打上删除标记",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  fn_edbs_del_Args,
	} ,fn_edbs_del ,"fn_edbs_del" };


EXTERN_C void fn_edbs_pop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_bool = self->pop();
}

FucInfo	edbs_pop = { {
		/*ccname*/  "彻底删除",
		/*egname*/  "pop",
		/*explain*/ "删除带有标记的记录",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ 0,
	} ,fn_edbs_pop ,"fn_edbs_pop" };


EXTERN_C void fn_edbs_cancel_del(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::edb_file>(pArgInf);
	pRetData->m_bool = self->cancel_del(pArgInf[1].m_int - 1);
}
static ARG_INFO fn_edbs_cancel_del_Args[] =
{
	{
		/*name*/    "字段索引",
		/*explain*/ ("小于等于0则默认为当前位置"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ -1,
		/*state*/   ArgMark::AS_HAS_DEFAULT_VALUE,
	}
};
FucInfo	edbs_cancel_del = { {
		/*ccname*/  "取消删除",
		/*egname*/  "",
		/*explain*/ "取消已经打上的删除标记",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  fn_edbs_cancel_del_Args,
	} ,fn_edbs_cancel_del ,"fn_edbs_cancel_del" };




static INT s_dtCmdIndexcommobj_edbs_ex[] = { 132,133,134,135 ,136,137,138 ,139 ,140 ,141,142,143,144,145,146,147,148,149,150,300,301,302 };
namespace elibstl {


	LIB_DATA_TYPE_INFO edbs_ex =
	{
		"易数据库",
		"EDBS",
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