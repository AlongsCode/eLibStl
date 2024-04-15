#include "EcontrolHelp.h"
#include <iostream>
#include <fstream>
#include <sstream>


namespace elibstl {
	inline auto get_arg_runtime_type(PMDATA_INF pArgInf, size_t index) {
		return pArgInf[index].m_dtDataType;;
	}
	inline auto get_arg_runtime_type(MDATA_INF pArgInf) {
		return pArgInf.m_dtDataType;;
	}

	struct EplVar
	{
		/*�ޱ��*/
		

		// anydata��ʹ��
		
		/*���ݹ���*/
		struct anydata {
			std::unique_ptr<void, void(*)(void*)> m_data{ nullptr, [](void* p) { operator delete(p); } };
			size_t m_data_size{ 0 };
			anydata(const anydata& other) {
				if (this != &other) {
					set(other.m_data.get(), other.m_data_size);
				}
			}
			void set(const void* data, size_t data_size) {
				if (!data || data_size == 0) {
					clear();
					return;
				}

				if (data_size != m_data_size) {
					m_data.reset(operator new(data_size));
					m_data_size = data_size;
				}

				std::memcpy(m_data.get(), data, data_size);
			}
			elibstl::classhelp::span<unsigned char> get() const{
				return { static_cast<unsigned char*>(m_data.get()), m_data_size };
			};
			void clear() {
				m_data.reset(nullptr);
				m_data_size = 0;
			}
			anydata() = default;
			~anydata() {
				clear();
			}

		};

		enum class REF :char {
			Ret,
			Arg,
		};
		enum DTT
		{
			DTT_IS_NULL_DATA_TYPE = 0,
			DTT_IS_SYS_DATA_TYPE = 1,
			DTT_IS_USER_DATA_TYPE = 2,
			DTT_IS_LIB_DATA_TYPE = 3,

		};

		DTT m_dtt{ DTT_IS_NULL_DATA_TYPE };/*�����������1.ϵͳ��������/2.��������/3.�ⶨ������/*/
		DATA_TYPE m_DataType{ DATA_TYPE::_SDT_NULL };/*��¼�������������*/
		anydata m_data;	



		static DTT get_data_type_form(DATA_TYPE dtDataType)
		{
			if (dtDataType == _SDT_NULL)
				return DTT_IS_NULL_DATA_TYPE;

			DWORD dw = dtDataType & 0xC0000000;
			return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
				dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
				DTT_IS_LIB_DATA_TYPE;
		}


		auto get_data_type() const{
			return m_DataType;
		}
		static int get_sys_type_value(DATA_TYPE dataType) {
			switch (dataType) {
			case SDT_BYTE:
				return 1;
			case SDT_SHORT:
				return 2;
			case SDT_INT:
				return 3;
			case SDT_INT64:
				return 4;
			case SDT_FLOAT:
				return 5;
			case SDT_DOUBLE:
				return 6;
			case SDT_BOOL:
				return 7;
			case SDT_DATE_TIME:
				return 8;
			case SDT_SUB_PTR:
				return 9;
			case SDT_TEXT:
				return 10;
			case SDT_BIN:
				return 11;
			default:
				return 0; // Ĭ��ֵ����������dataType��ƥ���κ���֪����������
			}
		}

		static  auto get_type_value(const MDATA_INF& pArgInf) {
			BOOL blIsAry = pArgInf.is_dt_flag();
			auto m_dtt = get_data_type_form(pArgInf.ret_type_noflag());
			switch (m_dtt)
			{
			case elibstl::EplVar::DTT_IS_NULL_DATA_TYPE:
				return 0;
			case elibstl::EplVar::DTT_IS_SYS_DATA_TYPE:
				return get_sys_type_value(pArgInf.ret_type_noflag());
			case elibstl::EplVar::DTT_IS_USER_DATA_TYPE:
				return static_cast<int>(pArgInf.m_dtDataType);/*�޷���ֵ����*/
				break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				break;
			default:

				break;
			}
		}
		auto get_type_value() {

			switch (m_dtt)
			{
			case elibstl::EplVar::DTT_IS_SYS_DATA_TYPE:
				return get_sys_type_value(m_DataType);
			case elibstl::EplVar::DTT_IS_USER_DATA_TYPE:
				return static_cast<int>(m_DataType);/*�޷���ֵ����*/
				break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				return 0;
				break;
			default:
				return 0;
				break;
			}
		}
		/*����ϵͳ����*/
		auto make_sys_data(const MDATA_INF& pArgInf) {
			if (m_DataType == SDT_TEXT)
				m_data.set(pArgInf.m_pText, (strlen(pArgInf.m_pText) + 1) * sizeof(char));
			else if (m_DataType == SDT_BIN && pArgInf.m_pBin) {
		
				auto pbin=elibstl::classhelp::eplarg::get_bin(pArgInf);
				m_data.set(pbin.data(), pbin.size());

			}
			else {
				/*�����Ե���������*/
				static  const std::map<DATA_TYPE, size_t> dataSizes = {
				{SDT_BYTE, sizeof(BYTE)},
				{SDT_SHORT, sizeof(SHORT)},
				{SDT_BOOL, sizeof(BOOL)},
				{SDT_INT, sizeof(INT)},
				{SDT_FLOAT, sizeof(FLOAT)},
				{SDT_SUB_PTR, sizeof(DWORD)},
				{SDT_INT64, sizeof(INT64)},
				{SDT_DOUBLE, sizeof(DOUBLE)},
				{SDT_DATE_TIME, sizeof(DATE)}
				};
				size_t size = sizeof(INT64);
				auto iter = dataSizes.find(pArgInf.m_dtDataType);
				if (iter != dataSizes.end()) {
					size = iter->second;
				}
				m_data.set(&pArgInf.m_int64, size);
			}

		}
		/*����ϵͳ����*/
		template<REF Tv>
		auto ret_sys_data(MDATA_INF& pArgInf) {
			if constexpr (Tv == REF::Ret) {
				pArgInf.m_dtDataType = m_DataType;
				if (m_DataType == SDT_TEXT) {
					auto p = m_data.get();
					pArgInf.m_pText = elibstl::clone_text(reinterpret_cast<char*>(p.data()));
				}
				else if (m_DataType == SDT_BIN) {
					auto p = m_data.get();
					pArgInf.m_pBin = elibstl::clone_bin(p.data(), p.size());
				}
				else {
					auto p = m_data.get();
					memcpy(&pArgInf.m_int64, p.data(), p.size());
				}
			}
			else
			{
				if (m_DataType == SDT_TEXT) {
					auto p = m_data.get();
					*pArgInf.m_ppText = elibstl::clone_text(reinterpret_cast<char*>(p.data()));
				}
				else if (m_DataType == SDT_BIN) {
					auto p = m_data.get();
					*pArgInf.m_ppBin = elibstl::clone_bin(p.data(), p.size());
				}
				else {
					auto p = m_data.get();
					memcpy(pArgInf.m_pInt64, p.data(), p.size());
					//memcpy(pArgInf.m_pInt64, p.data(), sizeof(pArgInf.m_int64));
				}
			}

		}
		
		/*�����û��Զ�������*/
		auto make_user_data(const MDATA_INF& pArgInf) {
			/*�Զ����������ͻ���ȫ��Ϊ������������ڴ�,���ڷ��ı����ݻ���п���*/
			/*���Կ��Ի�ȡ�������С*/
			auto IsPointer = [](int ptrValue) {
				return IsBadReadPtr((void*)ptrValue, 1) == FALSE;
				};
			auto size=LocalSize(pArgInf.m_pCompoundData);
			auto end = size / sizeof(std::uintptr_t);
			if (size % sizeof(std::uintptr_t) != 0)
				put_errmsg(L"���Զ����������ѭ4�ֽڶ���?");
			
			
			/*�Զ������ͽ�Ϊ4�ֽڶ���*/
			auto pPrt = reinterpret_cast<std::uintptr_t>(pArgInf.m_pCompoundData);
			m_data.set(pArgInf.m_pCompoundData, size);
		}
		/*�����û��Զ�������*/
				/*����ϵͳ����*/
		template<REF Tv>
		auto ret_user_data(MDATA_INF& pArgInf) {
			if constexpr (Tv == REF::Ret) {
				pArgInf.m_dtDataType = m_DataType;
				auto p = m_data.get();
				pArgInf.m_pCompoundData = elibstl::ealloc(p.size());
				memcpy(pArgInf.m_pCompoundData, p.data(), p.size());
			}
			else
			{
				pArgInf.m_dtDataType = m_DataType;
				auto p = m_data.get();
				*pArgInf.m_ppCompoundData = elibstl::ealloc(p.size());
				memcpy(*pArgInf.m_ppCompoundData, p.data(), p.size());
			}
		}
		void set(const MDATA_INF& pArgInf) {
			BOOL blIsAry = pArgInf.is_dt_flag();
			m_dtt = get_data_type_form(pArgInf.ret_type_noflag());
			switch (m_dtt)
			{
			case elibstl::EplVar::DTT_IS_SYS_DATA_TYPE:
				m_DataType = pArgInf.ret_type_noflag();
				make_sys_data(pArgInf);
				break;
			case elibstl::EplVar::DTT_IS_USER_DATA_TYPE:
				m_DataType = pArgInf.m_dtDataType;;
				make_user_data(pArgInf);
				break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				put_errmsg(L"�ݲ�֧�ֿⶨ�����ݽṹ!");
				break;
			default:
				put_errmsg(L"");
				break;
			}
		}

		void get(MDATA_INF& pArgInf,const bool ret=false) {
			switch (m_dtt)
			{
			case elibstl::EplVar::DTT_IS_SYS_DATA_TYPE: {
				if (ret)
					ret_sys_data<REF::Ret>(pArgInf);
				else
					ret_sys_data<REF::Arg>(pArgInf);
			}break;
			case elibstl::EplVar::DTT_IS_USER_DATA_TYPE: {
				if (ret)
					ret_user_data<REF::Ret>(pArgInf);
				else
					ret_user_data<REF::Arg>(pArgInf);
			}break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				put_errmsg(L"�ݲ�֧�ֿⶨ�����ݽṹ!");
				break;
			default:
				put_errmsg(L"�ñ���Ϊ�ձ���");
				break;
			}
		}

	};

};



//����
EXTERN_C void Fn_EplVar_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::EplVar>(pArgInf);
	self = new elibstl::EplVar;
}
//����
FucInfo EplVar_structure = { {
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
	} ,Fn_EplVar_structure ,"Fn_EplVar_structure" };


static ARG_INFO s_CopyArgs[] =
{
	{
		/*name*/    "����",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   DTP_VAR,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

//����
EXTERN_C void Fn_EplVar_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::EplVar>(pArgInf);
	const auto& rht = elibstl::classhelp::get_other<elibstl::EplVar>(pArgInf);
	self = new elibstl::EplVar{ *rht };
}
FucInfo EplVar_copy = { {
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
		/*ArgCount*/1,
		/*arg lp*/ s_CopyArgs,
	} ,Fn_EplVar_copy ,"Fn_EplVar_copy" };











//����
EXTERN_C void Fn_EplVar_des(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::EplVar>(pArgInf);
	if (self)
	{
		self->elibstl::EplVar::~EplVar();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo EplVar_destruct = { {
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
	} ,Fn_EplVar_des ,"Fn_EplVar_des" };

EXTERN_C void libstl_Var_Set(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	self->set(pArgInf[1]);
}
static ARG_INFO s_Args_set[] =
{
	{"�������ֵ", "֧����������,�Զ�������������ָ���������ı��͡��Զ����������͡��ֽڼ��Ͷ�Ӧע����ⳬ��������ʧЧ������ָ��������������,", 0, 0, _SDT_ALL, 0, ArgMark::AS_NONE},
};
FucInfo Fn_Var_Set = { {
		/*ccname*/  "��",
		/*egname*/  "Set",
		/*explain*/ "������Ǳ�����������",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_set),
		/*arg lp*/   s_Args_set },ESTLFNAME(libstl_Var_Set) };
EXTERN_C void libstl_Var_Get(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	self->get(pRetData[0],true);
	
	if (pArgInf[1].m_dtDataType != _SDT_NULL ) {
		if (pArgInf[1].m_dtDataType != self->get_data_type())
		{
			std::wstringstream err{ };
			err << L"\n����������ʱ��������ӦΪ:" 
				<< static_cast<std::uint32_t>(self->get_data_type()) 
				<< L"\n����Ŀǰ��������Ϊ:" 
				<< pArgInf[1].m_dtDataType;
			put_errmsg(err.str());
			return;
		}
		elibstl::efree(*pArgInf[1].m_ppCompoundData);/*���ͷ�*/
		self->get(pArgInf[1]);
	}
		
	
}
static ARG_INFO s_Args_get[] =
{
	{
		"����ȡ��ֵ", 
		"ϵͳ���Ϳ�ֱ��ʹ�÷���ֵ,���ϽṹӦʹ��", 0, 0, 
		_SDT_ALL, 0,
		ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
	},
};
FucInfo Fn_Var_Get = { {
		/*ccname*/  "ȡ",
		/*egname*/  "Get",
		/*explain*/ "�ò�����Ӧ�ͷ���ֵһ��ʹ�ã���Ϊ��ΪͬһƬָ����ǿ���,�������޷���ͨ���͸�ֵ�����ݴ���ʹ��",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     _SDT_ALL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  s_Args_get },ESTLFNAME(libstl_Var_Get) };


EXTERN_C void libstl_Var_Type(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	pRetData->m_int = self->get_type_value();
}

FucInfo Fn_Var_Type = { {
		/*ccname*/  "����",
		/*egname*/  "Type",
		/*explain*/ "�����ض�Ӧ��������ֵ, 0��#������ 1��#�ֽ��ͣ� 2��#�������ͣ� 3��#�����ͣ� "
			  "4��#�������ͣ� 5��#С���ͣ� 6��#˫����С���ͣ� 7��#�߼��ͣ� 8��#����ʱ���ͣ� "
			  "9��#�ӳ���ָ���ͣ� 10��#�ı��͡���11��#�ֽڼ��͡���!!�Զ�������������ʹ�� \"ȡ����ʱ��������()\"��������ֵ",
	/*category*/-1,
	/*state*/   NULL,
	/*ret*/     SDT_INT,
	/*reserved*/NULL,
	/*level*/   LVL_SIMPLE,
	/*bmp inx*/ 0,
	/*bmp num*/ 0,
	/*ArgCount*/0,
	/*arg lp*/   0 },ESTLFNAME(libstl_Var_Type) };
EXTERN_C void libstl_Var_Size(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	pRetData->m_int = self->m_data.m_data_size;
}

FucInfo Fn_Var_Size = { {
		/*ccname*/  "����",
		/*egname*/  "Size",
		/*explain*/ "�����ض�Ӧ����������ĳ���",
	/*category*/-1,
	/*state*/   NULL,
	/*ret*/     SDT_INT,
	/*reserved*/NULL,
	/*level*/   LVL_SIMPLE,
	/*bmp inx*/ 0,
	/*bmp num*/ 0,
	/*ArgCount*/0,
	/*arg lp*/   0 },ESTLFNAME(libstl_Var_Size) };


EXTERN_C void libstl_Var_TypeName(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
 auto value = self->get_type_value();
	std::map<int, std::string> dataTypeToString = {
	{0, "������"},
	{1, "�ֽ���"},
	{2, "��������"},
	{3, "������"},
	{4, "��������"},
	{5, "С����"},
	{6, "˫����С����"},
	{7, "�߼���"},
	{8, "����ʱ����"},
	{9, "�ӳ���ָ����"},
	{10, "�ı���"},
	{11, "�ֽڼ���"}
	};
	auto iter = dataTypeToString.find(value);
	std::string dataTypeString = "�Զ�����������";
	if (iter != dataTypeToString.end()) {
		dataTypeString = iter->second;
	}
	pRetData->m_pText = elibstl::clone_text(dataTypeString);
}

FucInfo Fn_Var_TypeName = { {
		/*ccname*/  "������",
		/*egname*/  "TypeName",
		/*explain*/ "�����ض�Ӧ������������",
	/*category*/-1,
	/*state*/   NULL,
	/*ret*/     SDT_TEXT,
	/*reserved*/NULL,
	/*level*/   LVL_SIMPLE,
	/*bmp inx*/ 0,
	/*bmp num*/ 0,
	/*ArgCount*/0,
	/*arg lp*/   0 },ESTLFNAME(libstl_Var_TypeName) };

EXTERN_C void libstl_Var_Data(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	pRetData->m_int = reinterpret_cast<std::ptrdiff_t>(self->m_data.m_data.get());
}

FucInfo Fn_Var_Data = { {
		/*ccname*/  "ָ��",
		/*egname*/  "TypeName",
		/*explain*/ "��ָ�뾡��ֻ��,��ϳ��ȿɽ����ڴ����,�����ڲ���������ָ�����,�벻Ҫ���Ⳣ�������ͷŵ�",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/   0 },ESTLFNAME(libstl_Var_Data) };

EXTERN_C void libstl_Var_ToBin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	auto data = self->m_data.get();
	pRetData->m_pBin = elibstl::clone_bin(data.data(), data.size());
}


FucInfo Fn_Var_ToBin = { {
		/*ccname*/  "���ֽڼ�",
		/*egname*/  "change",
		/*explain*/ "�ò�����Ӧ�ͷ���ֵһ��ʹ�ã���Ϊ��ΪͬһƬָ����ǿ���,�������޷���ͨ���͸�ֵ�����ݴ���ʹ��",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0 },ESTLFNAME(libstl_Var_ToBin) };
static INT s_dtCmdIndexcommobj_edbs_ex[] = { 304,305,306 ,307,308,309 ,310,311,312,313};
namespace elibstl {


	LIB_DATA_TYPE_INFO epl_class_Var =
	{
		"����",
		"Var",
		"��̬����ͨ�ñ���",
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


