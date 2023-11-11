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
		/*无标记*/
		

		// anydata中使用
		
		/*数据管理*/
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

		DTT m_dtt{ DTT_IS_NULL_DATA_TYPE };/*定义操作类型1.系统数据类型/2.数据类型/3.库定义类型/*/
		DATA_TYPE m_DataType{ DATA_TYPE::_SDT_NULL };/*记录储存的数据类型*/
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
			debug_put(L"标准模板库调试:", dataType);
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
				return 0; // 默认值，如果传入的dataType不匹配任何已知的数据类型
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
				return static_cast<int>(pArgInf.m_dtDataType);/*无返回值类型*/
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
				return static_cast<int>(m_DataType);/*无返回值类型*/
				break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				return 0;
				break;
			default:
				return 0;
				break;
			}
		}
		/*储存系统类型*/
		auto make_sys_data(const MDATA_INF& pArgInf) {
			if (m_DataType == SDT_TEXT)
				m_data.set(pArgInf.m_pText, (strlen(pArgInf.m_pText) + 1) * sizeof(char));
			else if (m_DataType == SDT_BIN && pArgInf.m_pBin) {
		
				auto pbin=elibstl::classhelp::eplarg::get_bin(pArgInf);
				m_data.set(pbin.data(), pbin.size());

			}
			else {
				/*易语言的数据类型*/
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
		/*返回系统类型*/
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
		
		/*储存用户自定义类型*/
		auto make_user_data(const MDATA_INF& pArgInf) {
			/*自定义数据类型基本全部为易语言申请的内存,对于非文本数据会进行拷贝*/
			/*所以可以获取到申请大小*/
			auto IsPointer = [](int ptrValue) {
				return IsBadReadPtr((void*)ptrValue, 1) == FALSE;
				};
			auto size=LocalSize(pArgInf.m_pCompoundData);
			auto end = size / sizeof(std::uintptr_t);
			if (size % sizeof(std::uintptr_t) != 0)
				put_errmsg(L"该自定义变量不遵循4字节对其?");
			
			
			/*自定义类型皆为4字节对其*/
			auto pPrt = reinterpret_cast<std::uintptr_t>(pArgInf.m_pCompoundData);
			m_data.set(pArgInf.m_pCompoundData, size);
		}
		/*返回用户自定义类型*/
				/*返回系统类型*/
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
				put_errmsg(L"暂不支持库定义数据结构!");
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
				put_errmsg(L"暂不支持库定义数据结构!");
				break;
			default:
				put_errmsg(L"该变量为空变量");
				break;
			}
		}

	};

};



//构造
EXTERN_C void Fn_EplVar_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::EplVar>(pArgInf);
	self = new elibstl::EplVar;
}
//构造
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
		/*name*/    "拷贝",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   DTP_VAR,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

//复制
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

//析构
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
	{"欲置入的值", "支持任意类型,自定义数据类型中指针类型如文本型、自定义数据类型、字节集型都应注意避免超出作用域失效或悬浮指针访问引起的问题,", 0, 0, _SDT_ALL, 0, ArgMark::AS_NONE},
};
FucInfo Fn_Var_Set = { {
		/*ccname*/  "置",
		/*egname*/  "Set",
		/*explain*/ "将任意非变量数据置入",
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
			err << L"\n该类型运行时数据类型应为:" 
				<< static_cast<std::uint32_t>(self->get_data_type()) 
				<< L"\n但是目前接受类型为:" 
				<< pArgInf[1].m_dtDataType;
			put_errmsg(err.str());
			return;
		}
		elibstl::efree(*pArgInf[1].m_ppCompoundData);/*先释放*/
		self->get(pArgInf[1]);
	}
		
	
}
static ARG_INFO s_Args_get[] =
{
	{
		"欲获取的值", 
		"系统类型可直接使用返回值,复合结构应使用", 0, 0, 
		_SDT_ALL, 0,
		ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR
	},
};
FucInfo Fn_Var_Get = { {
		/*ccname*/  "取",
		/*egname*/  "Get",
		/*explain*/ "该参数不应和返回值一起使用，因为其为同一片指针而非拷贝,仅用于无法将通用型赋值的数据代码使用",
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
		/*ccname*/  "类型",
		/*egname*/  "Type",
		/*explain*/ "将返回对应数据类型值, 0、#空类型 1、#字节型； 2、#短整数型； 3、#整数型； "
			  "4、#长整数型； 5、#小数型； 6、#双精度小数型； 7、#逻辑型； 8、#日期时间型； "
			  "9、#子程序指针型； 10、#文本型。；11、#字节集型。；!!自定义数据类型请使用 \"取运行时数据类型()\"函数返回值",
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
		/*ccname*/  "长度",
		/*egname*/  "Size",
		/*explain*/ "将返回对应数据所需求的长度",
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
	{0, "空类型"},
	{1, "字节型"},
	{2, "短整数型"},
	{3, "整数型"},
	{4, "长整数型"},
	{5, "小数型"},
	{6, "双精度小数型"},
	{7, "逻辑型"},
	{8, "日期时间型"},
	{9, "子程序指针型"},
	{10, "文本型"},
	{11, "字节集型"}
	};
	auto iter = dataTypeToString.find(value);
	std::string dataTypeString = "自定义数据类型";
	if (iter != dataTypeToString.end()) {
		dataTypeString = iter->second;
	}
	pRetData->m_pText = elibstl::clone_text(dataTypeString);
}

FucInfo Fn_Var_TypeName = { {
		/*ccname*/  "类型名",
		/*egname*/  "TypeName",
		/*explain*/ "将返回对应数据类型名称",
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
		/*ccname*/  "指针",
		/*egname*/  "TypeName",
		/*explain*/ "此指针尽量只读,配合长度可进行内存操作,但是内部是由智能指针控制,请不要随意尝试扩容释放等",
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
		/*ccname*/  "到字节集",
		/*egname*/  "change",
		/*explain*/ "该参数不应和返回值一起使用，因为其为同一片指针而非拷贝,仅用于无法将通用型赋值的数据代码使用",
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
		"变量",
		"Var",
		"动态类型通用变量",
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


