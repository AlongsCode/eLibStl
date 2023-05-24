#include"EcontrolHelp.h"
#include<string>
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4018)
#pragma warning(disable:26451)
#pragma once
#pragma region ���ö��
enum class DataType {
	BYTE = 1,         // �ֽ���
	SHORT_INT,    // ��������
	INT,          // ������
	LONG_INT,     // ��������
	FLOAT,        // С����
	DOUBLE,       // ˫����С����
	BOOLEAN,      // �߼���
	DATE_TIME,    // ����ʱ����
	PTR,		  // ָ���ͣ����ݿⲻ���õ�
	TEXT,         // �ı���
	BYTE_ARRAY,   // �ֽڼ���
	REMARK,		  // ��ע��
	PRIMARY_KEY	  // ����
};


/*��֤��*/


/*ʧ�ܺ�*/
#define EDB_ERROR_SUCCESS 0
#define EDB_ERROR_INVALID_COLUMN_NAME -1 //�ֶ����ƴ���
#define EDB_ERROR_INVALID_COLUMN_TYPE -2 //�������ʹ���
#define EDB_ERROR_INVALID_COLUMN_SIZE -3 //���ݳ���Ϊ0
#define EDB_ERROR_DUPLICATE_COLUMN_NAME -4//�ֶ����ظ�
#define EDB_ERROR_CREATE_EDBS -5//����EDBʧ��
#define EDB_ERROR_CREATE_EDT -6//����EDTʧ��
#define EDB_ERROR_INVALID_EDBSFILE -7//��Чedb�ļ�
#define EDB_ERROR_NOOPEN_EDBS -8//û���ļ�
#define EDB_ERROR_INVALID_INDEX -9//��Ч���ֶλ��¼����
#define EDB_ERROR_INVALID_DATA_SIZE -10 //д���������ݳ���
#define EDB_ERROR_INVALID_DATA_TYPE -11 //д��������������
#define EDB_ERROR_TRANSACTION_OPENED -12 //�����ѿ���
#define EDB_ERROR_TRANSACTION_NOT_OPENED -13 //����δ����
#define EDB_ERROR_INVALID_COLUMN_NUM -14 //��������������ƥ��
#define EDB_ERROR_HASBEEN_OPEN_EDBS -15//�Ѿ���һ����
#define EDB_ERROR_INVALID_ROWS_NUM -16//������Ч�����ļ�¼
#define EDB_ERROR_CANTOPEN_DAT -17//�޷��򿪶�ӦEDT�ļ�
#pragma endregion




struct ColumnInfo {
	std::string m_name;
	DataType m_dataType;
	unsigned int m_strDataLength = 20;

	ColumnInfo() : m_dataType(DataType::TEXT), m_strDataLength(0) {};
	ColumnInfo(const std::string& n, DataType t, int l = 20) : m_name(n), m_dataType(t), m_strDataLength(l) {}
};


typedef struct _ColumnInfo//�ֶ���Ϣ
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
#pragma pack(1)//�߽����





#pragma region �ڲ���


#define EDBCHECK { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 }
#define EDTCHECK { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 }
static const char pCheckSizeNeverUse[] = EDBCHECK;
#define EDBCHECKSIZE sizeof(pCheckSizeNeverUse)
#define EDTCHECKSIZE EDBCHECKSIZE
#define EDTDATASIZE 512


#pragma endregion


#pragma region �ṹ��

struct EDBHEADER {

	double m_createTime;//OLEʱ��
	int m_recordNum;//��ǰ��¼����
	int m_unusedPrimaryKey;//��ʹ�õ�����,ÿ�β�������ݻ�����1,�ò��ظ�
	int  m_totalLength;//�����ֶ�����ĳ���,��λ�ֽ�
	unsigned char  m_blankBYTE[84];//Ԥ���ռ�
	int m_validColumnNum;//��Ч�ֶ�����
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
	char m_ColumnName[16];  // �������16�ֽ�,
	int m_delimiter;    // �ָ���
	DataType m_ColumnType;       // ��ʼƫ��λ��
	int m_offset;           // ���ı����������ݳ���;
	int m_strlenth;         // ��Ϊ�ı���������Ҫ����;
	unsigned char m_Table[40];
	COLIMNDATA() {

		memset(this, 0, sizeof(*this));
	}
};
#pragma endregion


#pragma region ӳ��


/*ӳ���ֶγ���,�ı��Ϳ���������*/
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
	{DataType::PRIMARY_KEY, 4} // ������Ĭ�ϳ���Ϊ4
};
#pragma endregion








#pragma region help
//��ȡʱ�䲢ת��ΪOLEʱ��,�˴���Ϊ����EDBԭ��
inline double get_nowtm_to_oletm() {
	auto now = std::chrono::system_clock::now();
	auto time_t_now = std::chrono::system_clock::to_time_t(now);
	auto  t = static_cast<__time64_t>(time_t_now);
	return static_cast<double>(25569 + t / 86400.0 + 8.0 / 24.0);

}




/*EDBS��������й������ƣ���������ϸ�Ĺ�����飬��������������*/
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
		// �ļ���û����չ��
		return filename + extensionname;
	}
	else {
		// ʹ�� substr() �������ļ�������ȡ��չ��
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
///*�������ò����ļ�ϵͳ,����winƽ̨ȷʵwinapi����һ��*/
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


//����ȡ�ļ���
//std::string get_file_name_unext(const std::string& file_path) {
//	std::filesystem::path file(file_path);
//	std::string file_name = file.stem().string();
//	return file_name;
//}

/*�޸��ļ���չ��*/
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
	struct EDTHEADER//EDT��������
	{
		EDTHEADER() {
			m_createTime = 0;//COleDateTime::GetTickCount()��ÿ�δ򿪻�ˢ�£�����ԭ��EDB;;
			m_recordNum = 1;
			m_un_using_count = 0;
			m_nop_index = 0;
			memset(m_data, 0, sizeof(m_data));
		}
		double  m_createTime;//COleDateTime::GetTickCount()��ÿ�δ򿪻�ˢ�£�����ԭ��EDB;;
		int m_recordNum;//δʹ�ð����1;
		int m_un_using_count;//δʹ������
		int m_nop_index;//����ڳ�����������;
		unsigned char m_data[484];
	};
	struct EDTDATA {
		int m_previous;//ǰһ������������
		int m_next;//��һ����������,�ٴα�ʹ��ʱ�Ὣָ��������Ϊ������,���Ϊ�ձ�ʾû�к������ݻ���û�п�������
		int m_data_size;//���ݳ���
		unsigned char m_pbuffer[500];
		EDTDATA() {
			memset(this, 0, sizeof(*this));
		}
	};
	//help,��󲻻ᱩ©��ͷ�ļ��ӿ���
	bool is_edt_file() {

		// ȷ���ļ���С
		m_file_edt.seekg(0, std::ios::end);
		const char edb_flag[] = { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 };
		if (m_file_edt.tellg() < sizeof(EDTDATA)) {
			// �ļ�̫С������������Ч�� edbs �ļ�
			return false;
		}

		m_file_edt.seekg(0, std::ios::beg);
		char rfile_flag[sizeof(edb_flag)]{ 0 };
		m_file_edt.read(rfile_flag, sizeof(edb_flag));

		if (std::memcmp(rfile_flag, edb_flag, sizeof(edb_flag)) != 0) {
			// �ļ����� edbs �ļ�
			return false;
		}
		//�����edbs�ļ���Ҫ�Ƶ��ļ��׼�������Ϊ����������Ҫ������������ù�������ʱ���Զ��ر�
		m_file_edt.seekg(0, std::ios::beg);
		return true;
	}


public:
	~Edt() {
		close();
	}
	static bool create(const std::string& nfilename, double time) {
		// ����EDT�ļ�
		std::string edtFileName = rename_file_ext(nfilename, ".EDT");
		std::ofstream edtFile(edtFileName, std::ios::binary);
		if (!edtFile)
		{
			// ����EDT�ļ�ʧ��
			return false;
		}
		// д��EDT�ļ�ͷ����Ϣ
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
		//�Ѿ��򿪾Ͳ��ڴ�
		if (m_file_edt.is_open()) {
			return false;
		}


		m_file_edt.open(filename, std::ios::binary | std::ios::out | std::ios::in);
		if (!m_file_edt.is_open()) {
			// �ļ��޷���
			return false;
		}
		if (!is_edt_file())
		{
			m_file_edt.close();
			return false;
		}
		//��ȡEDB��Ϣ
		m_file_edt.seekg(EDBCHECKSIZE);
		m_file_edt.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDTHEADER));
		//����Ч�ֶ�
		if (m_edbInf.m_recordNum <= 0)
		{
			m_file_edt.close();
			return false;;
		}

		//�ٴ���֤�ļ���С
		m_file_edt.seekg(0, std::ios::end);
		auto fileSize = m_file_edt.tellg();


		if (fileSize < sizeof(EDTDATA) * m_edbInf.m_recordNum)
		{
			// �ļ�̫С�������ܶ�ȡ��������Ϣ�͵�ǰ�㹻����Ϣ����
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
	/*��*/
	void read(std::vector<unsigned char>* n_pData, int n_index) {
		n_pData->clear();
		if (!m_file_edt.is_open())
		{
			/*�ļ�û�д�*/
			return;
		}
		/*��֤������Ч��*/
		if (n_index<0 || n_index>m_edbInf.m_recordNum)
		{
			/*����ʧЧ*/
			return;
		}
		m_file_edt.seekg(n_index * sizeof(EDTDATA), std::ios::beg);
		while (true) {
			EDTDATA temp_data;

			m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(temp_data));
			if (temp_data.m_data_size == 0)
			{
				/*��������*/
				return;
			}
			n_pData->insert(n_pData->end(), temp_data.m_pbuffer, temp_data.m_pbuffer + temp_data.m_data_size);
			if (temp_data.m_next == 0)
			{
				/*����һ����*/
				return;
			}
			auto off = temp_data.m_next * sizeof(EDTDATA);
			m_file_edt.clear();
			m_file_edt.seekg(off, std::ios::beg);
			if (m_file_edt.fail() || m_file_edt.bad()) {
				/* ��λʧ�� */
				return;
			}
		}

	}
	/*��*/
	int write(const std::vector<unsigned char>& n_pData)
	{

		int ret = 0;
		if (!m_file_edt.is_open())
		{
			/*�ļ�û�д�*/
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
					/*��������Ϊ����������*/
					i_index = m_edbInf.m_nop_index;
					/*��ȡ����ָ������*/
					m_file_edt.seekg(i_index * sizeof(EDTDATA), std::ios::beg);
					m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);
					/*�����ļ�ͷ*/

					m_edbInf.m_un_using_count--;
					/*��ͷΪ�յ�ָ����£�ȷ����ʽ��ȷ��*/
					m_edbInf.m_nop_index = temp_data.m_next;
				}
				else
				{
					i_index = m_edbInf.m_recordNum;
					m_edbInf.m_recordNum++;
				}
				int i_next = m_edbInf.m_un_using_count > 0 ? m_edbInf.m_nop_index : m_edbInf.m_recordNum;
				/*д�����ݶ�*/
				int data_size = i == segment_num - 1 ? last_segment_size : 500;
				std::memcpy(temp_data.m_pbuffer, n_pData.data() + i * 500, data_size);
				temp_data.m_data_size = data_size;

				if (i == 0)
				{
					/*�����ݶα�ʾ��ʼ��*/
					ret = i_index;
					/*�����һ�����ݶ�*/
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
					/*�������һ�����ݶ�*/
					temp_data.m_previous = s_last_index;
					temp_data.m_next = 0;
				}
				else
				{
					/*�����м�����ݶ�*/
					temp_data.m_previous = s_last_index;
					temp_data.m_next = i_next;
				}
				s_last_index = i_index;

				/*д������*/
				m_file_edt.clear();
				m_file_edt.seekp(i_index * sizeof(EDTDATA), std::ios::beg);
				m_file_edt.write(reinterpret_cast<char*>(&temp_data), sizeof(EDTDATA));
			}
		}
		else
		{
			/*����С�ڵ���500�ֽڣ�д�뵥�����ݿ�*/
			int i_index;
			EDTDATA temp_data;
			if (m_edbInf.m_un_using_count > 0)
			{
				/*��������Ϊ����������*/
				i_index = m_edbInf.m_nop_index;
				/*��ȡ����ָ������*/
				m_file_edt.seekg(i_index * sizeof(EDTDATA), std::ios::beg);
				m_file_edt.read(reinterpret_cast<char*>(&temp_data), sizeof(int) * 2);
				/*�����ļ�ͷ*/

				m_edbInf.m_un_using_count--;
				/*β��Ϊ�յ�ָ����£�ȷ����ʽ��ȷ��*/
				m_edbInf.m_nop_index = temp_data.m_next;
			}
			else
			{
				i_index = m_edbInf.m_recordNum;
				m_edbInf.m_recordNum++;
			}
			ret = i_index;
			/*д������*/
			std::memcpy(temp_data.m_pbuffer, n_pData.data(), data_len);
			temp_data.m_data_size = data_len;
			temp_data.m_previous = 0;
			temp_data.m_next = 0;
			m_file_edt.seekp(i_index * sizeof(EDTDATA), std::ios::beg);
			m_file_edt.write(reinterpret_cast<char*>(&temp_data), sizeof(EDTDATA));
		}
		return ret;
	}
	/*ɾ*/
	void del(int n_index) {
		/*��֤������Ч��*/
		if (n_index < 0 || n_index > m_edbInf.m_recordNum)
		{
			/*����ʧЧ*/
			return;
		}

		m_edbInf.m_nop_index = n_index;
		do
		{
			m_file_edt.seekg(n_index * sizeof(EDTDATA), std::ios::beg);
			EDTDATA  p;
			m_file_edt.read(reinterpret_cast<char*>(&p), sizeof(p));
			m_edbInf.m_un_using_count++;
			p.m_previous = m_edbInf.m_nop_index;//�νӱ�
			if (p.m_next == 0)
			{
				break;
			}
			n_index = p.m_next;

		} while (true);
		if (m_edbInf.m_recordNum == m_edbInf.m_un_using_count + 1)
		{
			/*ɾ���ؽ�*/
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
		//�Ѿ��򿪾Ͳ��ڴ�
		if (!m_file_edt.is_open()) {
			return;
		}
		/*�����ļ�ͷ*/
		m_file_edt.seekp(EDBCHECKSIZE, std::ios::beg);
		m_file_edt.write(reinterpret_cast<char*>(&m_edbInf), sizeof(m_edbInf));
		m_file_edt.flush();
	};
private:
	std::fstream  m_file_edt;/*EDT�ļ�*/
	std::string m_filename;
	EDTHEADER m_edbInf;
};





class Edbs
{
public:
	Edbs& operator = (const Edbs& n_copy) {
#ifdef _WIN32
		MessageBoxW(0, L"��ֹ��EDB������", 0, 0);
#else
		std::cout << "Prohibit copying EDB objects" << std::endl;
#endif // _WIN32
		std::abort();
		/*��Ҫ����*/
		if (this != &n_copy) {
			// �ȹرյ�ǰ�ļ�����ֹ��Դй©
			if (m_file.is_open()) m_file.close();
			// ���ƴ������ƫ��������Ϣ
			m_errorCode = n_copy.m_errorCode;
			m_fileName = n_copy.m_fileName;
			m_dataOffset = n_copy.m_dataOffset;
			m_cur_off = n_copy.m_cur_off;
			m_isTransactionOpened = n_copy.m_isTransactionOpened;
			// ��������Ϣ
			m_allCoLimns = n_copy.m_allCoLimns;
			// ���� EDB ͷ��Ϣ
			m_edbInf = n_copy.m_edbInf;
			// ���ļ�
			m_file.open(n_copy.m_fileName);
			if (!m_file.is_open()) {
				// �ļ��޷���
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			}
			//m_edt_file.open(get_file_name_unext(n_copy.m_fileName) + ".edt");
			//if (!m_file_edt.is_open()) {
			//	// �ļ��޷���
			//	m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			//}
		}
		return *this;
	}
	Edbs() :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {};
	Edbs(const std::string& filename) :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {

		m_file.open(filename, std::ios::binary | std::ios::out | std::ios::in | std::fstream::trunc);
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		if (!is_edbs_file())
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		//��ȡEDB��Ϣ
		m_file.seekg(EDBCHECKSIZE);
		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
		//����Ч�ֶ�
		if (m_edbInf.m_validColumnNum <= 0)
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return;
		}
		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		//�ٴ���֤�ļ���С
		m_file.seekg(0, std::ios::end);
		auto fileSize = m_file.tellg();


		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
		{
			// �ļ�̫С�������ܶ�ȡ��������Ϣ�͵�ǰ�㹻����Ϣ����
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
			//�򿪶�ӦEDT�ļ�
			;
			if (!m_edt_file.open(filename, m_edbInf.m_createTime)) {
				m_file.close();
				// �ļ��޷���
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return;
			}
		}

		/*�����ʼ������*/
		m_cur_off = 1;
		m_fileName = filename;
	};
	~Edbs() { close(); };
public:
	static int create_edbs(const std::string& nfilename, const std::vector< ColumnInfo>& columns) {

		/*�����ֶε���Ч����֤��������ȡ*/
		std::unordered_set<std::string> columnNames;

		std::vector<COLIMNDATA> wFileCoumns;

		//Ĭ��Ҫ�����ݿ����һ��������С,ͬʱҲ��ƫ�ƺ���չ��ȥ�ĳ���
		std::uint32_t all_columns_datasize = type_lengths[DataType::PRIMARY_KEY];
		//��Ч�ֶ�����
		std::uint32_t valid_column_num = 0;

		bool bIsHaveBigData = false;

		for (ColumnInfo column : columns)
		{

			// �ж��ֶ����Ƿ��Ѿ����ֹ�
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



			//׼������д���ļ��е��ֶ�����
			COLIMNDATA TempwFileCoumns;
			TempwFileCoumns.m_ColumnType = column.m_dataType;

			strcpy_s(TempwFileCoumns.m_ColumnName, column.m_name.c_str());
			TempwFileCoumns.m_ColumnName[15] = '\0';
			if (strlen(TempwFileCoumns.m_ColumnName) < 15)
			{
				memset(&TempwFileCoumns.m_ColumnName[strlen(TempwFileCoumns.m_ColumnName)], 0, 15 - strlen(TempwFileCoumns.m_ColumnName));
			}

			//ͨ�����ƺ������ж�����г�����֤
			//�������ж��Ƿ�Ϊ�ı���
			std::uint32_t TempColumnSize = 0;
			//EDBS�����ı�����󳤶Ƚ�������
			if (column.m_dataType == DataType::TEXT)
			{
				//��֤
				TempColumnSize = column.m_strDataLength;
				//׼��д�����������
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
			// ����EDT�ļ�ʧ��
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
		// Ȼ��д���ֶ�����
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
		//�Ѿ��򿪾Ͳ��ڴ�
		if (m_file.is_open()) {
			m_errorCode = EDB_ERROR_HASBEEN_OPEN_EDBS;
			return false;
		}


		m_file.open(filename, std::ios::binary | std::ios::out | std::ios::in);
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;
		}
		if (!is_edbs_file())
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;
		}
		//��ȡEDB��Ϣ
		m_file.seekg(EDBCHECKSIZE);
		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
		//����Ч�ֶ�
		if (m_edbInf.m_validColumnNum <= 0)
		{
			m_file.close();
			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
			return false;;
		}
		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		//�ٴ���֤�ļ���С
		m_file.seekg(0, std::ios::end);
		auto fileSize = m_file.tellg();


		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
		{
			// �ļ�̫С�������ܶ�ȡ��������Ϣ�͵�ǰ�㹻����Ϣ����
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
			//�򿪶�ӦEDT�ļ�
			if (!m_edt_file.open(rename_file_ext(filename, ".EDT"), m_edbInf.m_createTime)) {
				m_file.close();
				// �ļ��޷���
				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
				return false;
			}
		}

		/*�����ʼ������*/
		if (m_edbInf.m_recordNum > 0)
		{
			m_cur_off = 1;
		}

		m_fileName = filename;
		return true;;

	}
	//��֤��������������㣬��Ϊ�����ã���Ҫ����������������֤�û��������ɵ�Ʋ���
	void Read(int nIndex_column, int nIndex_row, std::vector<unsigned char>* pData) {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if ((nIndex_row >= 0 && nIndex_row + 1 > m_edbInf.m_recordNum) || (nIndex_column + 1 > m_edbInf.m_validColumnNum && nIndex_column >= 0))
		{
			m_errorCode = EDB_ERROR_INVALID_INDEX;
			return;
		}
		m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);

		//�ı��ͳ��������⴦��
		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
		{	//����Ĭ�ϳ���
			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
		}

		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
		{
			pData->resize(needsize, 0);
			m_file.read(reinterpret_cast<char*>(pData->data()), pData->size());
		}
		else
		{
			/*�����ֽڼ��ͱ�ע��*/
			/*��������*/
			int index = 0;
			m_file.read(reinterpret_cast<char*>(&index), sizeof(index));
			if (index > 0)
			{
				/*��ָ��EDT�ļ���Ѱ������*/
				m_edt_file.read(pData, index);
			}

		}


	};
	bool Write(int nIndex_column, int nIndex_row, const std::vector<unsigned char>& data) {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (nIndex_row + 1 > m_edbInf.m_recordNum || nIndex_column + 1 > m_edbInf.m_validColumnNum)
		{
			m_errorCode = EDB_ERROR_INVALID_INDEX;
			return false;
		}
		m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
		//�ı��ͳ��������⴦��
		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
		{	//����Ĭ�ϳ���
			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
		}

		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
		{
			/*���ֽڼ��ͱ�ע��*/
			if (data.size() >= needsize) {
				// ���ȳ�����ض�
				m_file.write(reinterpret_cast<const char*>(data.data()), needsize);
			}
			else {
				// ���Ȳ�������
				m_file.write(reinterpret_cast<const char*>(data.data()), data.size());
				if (data.size() < needsize) {
					// ���ʣ��ռ�
					//std::vector<unsigned char> padData(needsize - data.size(), 0);
					auto padData = new char[needsize - data.size()]{ 0 };
					m_file.write(padData, needsize - data.size());
					delete[]padData;
				}
			}
		}
		else
		{
			/*�����ֽڼ��ͱ�ע��*/
			/*��������*/
			m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
			int index = 0;
			m_file.read(reinterpret_cast<char*>(&index), sizeof(index));
			if (index > 0)
			{
				/*��ָ��EDT�ļ��д�������*/
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
				/*������*/
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

			/*�����ֽڼ��ͱ�ע��*/
		}
		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}

		return  true;
	}
	bool Insert(const std::vector<std::vector<unsigned char>>& data) {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (data.empty()) {
			// ������Ҫ����
			return true;
		}
		if (data.front().size() != m_edbInf.m_validColumnNum) {
			// �����ݵ�������ƥ��
			m_errorCode = EDB_ERROR_INVALID_COLUMN_NUM;
			return false;
		}
		if (m_isTransactionOpened) {
			// �ѿ������񣬲��ܲ���
			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
			return false;
		}
		auto totalRowSize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
		// ����������к��ļ����ܴ�С
		auto newFileSize = sizeof(EDBHEADER) + EDBCHECKSIZE + m_allCoLimns.size() * sizeof(COLIMNDATA) +
			(m_edbInf.m_recordNum + data.size()) * m_edbInf.m_totalLength;
		// �����ļ���С
		m_file.seekp(newFileSize - 1);
		m_file.write("", 1);
		// ��ȡ�ļ�β�������ݣ��Ա㽫���ƶ����µ�λ��
		auto tailSize = static_cast<int> (m_file.tellg()) - (m_dataOffset + totalRowSize);
		std::vector<unsigned char> tailData(tailSize);
		m_file.seekg(m_dataOffset + totalRowSize);
		m_file.read(reinterpret_cast<char*>(tailData.data()), tailSize);
		// ��β�������ƶ����µ�λ��
		m_file.seekp(newFileSize - tailSize);
		m_file.write(reinterpret_cast<char*>(tailData.data()), tailSize);
		// ��������д���ļ�
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
						// ���ݳ��Ȳ��㣬����
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
					/*�����ֽڼ��ͱ�ע��*/
				}



			}
		}
		// ���¼�¼�����ļ���С��Ϣ
		m_edbInf.m_recordNum++;
		updata_heade();
		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
	}
	bool AppendBlank(int nCount) {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return false;
		}
		if (nCount <= 0)
		{
			m_errorCode = EDB_ERROR_INVALID_ROWS_NUM;
			return false;
		}
		//�ļ�ͷ����
		m_edbInf.m_recordNum += nCount;
		m_file.seekp(0, std::ios::end);
		//�ı��ͳ��������⴦��


		std::vector<char> pData_nop(nCount * m_edbInf.m_totalLength, 0);
		for (size_t i = 0; i < nCount; i++)
		{

			*reinterpret_cast<int*>(&pData_nop[m_edbInf.m_totalLength * i]) = m_edbInf.m_unusedPrimaryKey++;

		}
		// ���ȳ�����ض�
		m_file.write(reinterpret_cast<const char*>(pData_nop.data()), pData_nop.size());

		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
		updata_heade();
		to_end();
		return  true;
	}

	//��������
	void begin() {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (m_isTransactionOpened) {
			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
			return;
		}
		m_isTransactionOpened = true;
	}
	//�ύ����
	void commit() {
		if (!m_file.is_open()) {
			// �ļ��޷���
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
			// �ļ��޷���
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
			// �ļ��޷���
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
	std::fstream m_file;  //�ļ���
	int m_dataOffset;//���ݿ�ʼλ��
	int m_errorCode;//������
	EDBHEADER m_edbInf;//���ݱ���Ϣ
	std::vector<COLIMNDATA> m_allCoLimns;//�ֶ���Ϣ
	bool m_isTransactionOpened;//�Ƿ�������
	//�·�Ϊ��װ����
public:
	void clean() {
		/*�ر�*/
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
		/*�ؽ�*/
		for (const auto& temp : m_allCoLimns)
		{
			ColumnInfo i_ColumnInfo;
			i_ColumnInfo.m_dataType = temp.m_ColumnType;
			i_ColumnInfo.m_name = temp.m_ColumnName;
			i_ColumnInfo.m_strDataLength = temp.m_strlenth;
			_ColumnInfo.push_back(i_ColumnInfo);
		}
		m_errorCode = create_edbs(m_fileName, _ColumnInfo);
		/*��*/
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
			// �ļ��޷���
			return 0;
		}
		return m_edbInf.m_validColumnNum;
	}
	char* get_column_name(int nIndex_column) const {
		return elibstl::clone_text(Get_column_name(nIndex_column - 1));
	}
	int get_row_num()const {
		if (!m_file.is_open()) {
			// �ļ��޷���
			return 0;
		}
		return m_edbInf.m_recordNum;
	}
	void set_current(int cur_off) {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		if (cur_off < 0)cur_off = m_edbInf.m_recordNum > 0 ? 1 : 0;
		else if (cur_off > m_edbInf.m_recordNum)cur_off = m_edbInf.m_recordNum;
		m_cur_off = cur_off;
	};
	void to_end() {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		m_cur_off = m_edbInf.m_recordNum;
	};
	void to_begin() {
		if (!m_file.is_open()) {
			// �ļ��޷���
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
			// �ļ��޷���
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
			// �ļ��޷���
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
	//�����ļ�ͷ��,ÿ��������¼ʱ��Ҫ����
	inline void updata_heade() {
		if (!m_file.is_open()) {
			// �ļ��޷���
			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
			return;
		}
		//��¼����λ��
		auto now = m_file.tellp();
		//�Ƶ��ļ�ͷ,�������ļ���ʶλ��+
		m_file.seekp(EDBCHECKSIZE, std::ios::beg);
		m_file.write(reinterpret_cast<const char*>(&m_edbInf), sizeof(EDBHEADER));
		//�ƶ���֮ǰ��λ��
		m_file.seekp(now, std::ios::beg);

		if (!m_isTransactionOpened)
		{
			m_file.flush();
		}
	}
	//help,��󲻻ᱩ©��ͷ�ļ��ӿ���
	inline  bool is_edbs_file() {

		// ȷ���ļ���С
		m_file.seekg(0, std::ios::end);
		const char edb_flag[] = { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 };
		if (m_file.tellg() < sizeof(EDBHEADER) + EDBCHECKSIZE) {
			// �ļ�̫С������������Ч�� edbs �ļ�

			return false;
		}

		m_file.seekg(0, std::ios::beg);
		char rfile_flag[EDBCHECKSIZE]{ 0 };
		m_file.read(rfile_flag, EDBCHECKSIZE);

		if (std::memcmp(rfile_flag, edb_flag, EDBCHECKSIZE) != 0) {
			// �ļ����� edbs �ļ�
			return false;
		}
		//�����edbs�ļ���Ҫ�Ƶ��ļ��׼�������Ϊ����������Ҫ������������ù�������ʱ���Զ��ر�
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
		/*name*/    "�ļ���",
		/*explain*/ ("�������������ݿ��ļ�,�˴������п��ܲ�����ԭ���������ԭ�洴����һ�������°�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�ֶ���Ϣ",
		/*explain*/ ("�������������ݿ��ļ�,�˴������п��ܲ�����ԭ���������ԭ�洴����һ�������°�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/	DATA_TYPE::KRNLN_EDB,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
		},
};



EXTERN_C void Fn_CreateEbds(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{



	if (pArgInf[0].m_dtDataType != DATA_TYPE::SDT_TEXT)
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

	if (nElementCount < 1) {//�������涨����Ϊ����
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
		/*ccname*/  ("����EDBS"),
		/*egname*/  ("create_edbs"),
		/*explain*/ ("�������������ݿ��ļ�,�˴������п��ܲ�����ԭ���������ԭ�洴����һ�������°�����"),
		/*category*/14,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_CreateEbds ,"Fn_CreateEbds" };


//����
EXTERN_C void Fn_edbs_ex_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	self = new Edbs;
}
//����
FucInfo edbs_ex_structure = { {
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
	} ,Fn_edbs_ex_structure ,"Fn_edbs_ex_structure" };

//����
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
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,fn_edbs_ex_copy ,"fn_edbs_ex_copy" };

//����
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
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,fn_edbs_ex_des ,"fn_edbs_ex_des" };


//��
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
		/*name*/    "�ļ�·��",
		/*explain*/ ("edbs/edb���ݿ��ļ�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo edbs_ex_open = { {
		/*ccname*/  "��",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_ex_open_Args,
	} ,fn_edbs_ex_open ,"fn_edbs_ex_open" };


//ȡ��¼��
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
		/*name*/    "����",
		/*explain*/ ("����������ݵ�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_ex_addpendnop = { {
		/*ccname*/  "�ӿռ�¼",
		/*egname*/  "",
		/*explain*/ "�������ڵ�ǰ���ݿ��β�����һ���ռ�¼��������ǰ��¼ָ���ƶ������ļ�¼�ϡ��ɹ������棬ʧ�ܷ��ؼ١�",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_ex_addpendnop_Args,
	} ,fn_edbs_ex_addpendnop ,"fn_edbs_ex_addpendnop" };

FucInfo edbs_get_row_num = { {
		/*ccname*/  "ȡ��¼��",
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
	} ,fn_edbs_get_row_num ,"fn_edbs_get_row_num" };

static INT s_dtCmdIndexcommobj_edbs_ex[] = { 132,133,134,135 ,136,137,138 ,139 ,140 ,141,142,143,144,145,146,147,148,149,150 };
namespace elibstl {


	LIB_DATA_TYPE_INFO edbs_ex =
	{
		"EBDS",
		"EBDS",
		"���������ݿ�Ķ������",
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




//����
EXTERN_C void fn_edbs_set_current(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);

	self->set_current(pArgInf[1].m_int);
}
static ARG_INFO edbs_set_current_Args[] =
{
	{
		/*name*/    "λ��",
		/*explain*/ ("��������λ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_set_current = { {
		/*ccname*/  "����",
		/*egname*/  "",
		/*explain*/ "���õ�ǰλ��,���ڼ�¼�����������޷�����0�ģ������ڵ�����һֱΪ0",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  edbs_set_current_Args,
	} ,fn_edbs_set_current ,"fn_edbs_set_current" };



//��
EXTERN_C void fn_edbs_read(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<Edbs>(pArgInf);
	pRetData->m_pBin = self->read(pArgInf[1].m_int);
}
static ARG_INFO fn_edbs_read_Args[] =
{
	{
		/*name*/    "�ֶλ��ֶ�����",
		/*explain*/ ("����ȡ���ֶ�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_read = { {
		/*ccname*/  "��",
		/*egname*/  "��ȡ��ǰ�е�ָ���ֶ�����",
		/*explain*/ "�������ڵ�ǰ���ݿ��β�����һ���ռ�¼��������ǰ��¼ָ���ƶ������ļ�¼�ϡ��ɹ������棬ʧ�ܷ��ؼ١�",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_BIN,
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
		/*name*/    "�ֶλ��ֶ�����",
		/*explain*/ ("����ȡ���ֶ�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},{
		/*name*/    "����",
		/*explain*/ ("��Ӧ�ֶε����ݣ���������0��������ض�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_write = { {
		/*ccname*/  "д",
		/*egname*/  "",
		/*explain*/ " ������д�뵽��ǰ���ݿ��е�ǰ��¼����ָ���ֶ��ڡ��ɹ�������",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_BOOL,
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
		/*ccname*/  "�ر�",
		/*egname*/  "",
		/*explain*/ " ������ر��Ѿ����ݿ�",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "��һ��",
		/*egname*/  "",
		/*explain*/ "�ƶ�����һ��",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "��һ��",
		/*egname*/  "",
		/*explain*/ " �ƶ�����һ��",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "���",
		/*egname*/  "",
		/*explain*/ "������ݿ�",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "��������",
		/*egname*/  "",
		/*explain*/ "��Ϊ��ֹIO,ֱ���ύ����֮ǰ����д�붼����ʵʱ���µ��ļ�",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "�ύ����",
		/*egname*/  "",
		/*explain*/ "�����и���д�����",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*ccname*/  "ȡ��ǰλ��",
		/*egname*/  "",
		/*explain*/ "��ȡ��ǰ��¼ָ����λ��",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_INT,
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
		/*ccname*/  "ȡ�ֶ���",
		/*egname*/  "",
		/*explain*/ "��ȡָ���ֶ��������ֶ���",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_TEXT,
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
		/*ccname*/  "ȡ�ֶ���",
		/*egname*/  "",
		/*explain*/ "��ȡ���ݿ���ֶ���Ŀ",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::SDT_INT,
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
		/*name*/    "�ֶ�����",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "���޸�Ϊ���ֶ���",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
FucInfo	edbs_set_column_name = { {
		/*ccname*/  "���ֶ���",
		/*egname*/  "",
		/*explain*/ "����ָ���ֶ��������ֶ���",
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) ,
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  fn_edbs_set_column_name_Args,
	} ,fn_edbs_set_column_name ,"fn_edbs_set_column_name" };
