#include"EcontrolHelp.h"







namespace elibstl {
	inline auto get_arg_runtime_type(PMDATA_INF pArgInf, size_t index) {
		return pArgInf[index].m_dtDataType;;
	}
	inline auto get_arg_runtime_type(MDATA_INF pArgInf) {
		return pArgInf.m_dtDataType;;
	}
	struct EplVar
	{


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



		DTT get_data_type_form(DATA_TYPE dtDataType)
		{
			if (dtDataType == _SDT_NULL)
				return DTT_IS_NULL_DATA_TYPE;

			DWORD dw = dtDataType & 0xC0000000;
			return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
				dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
				DTT_IS_LIB_DATA_TYPE;
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
				m_data.set(&pArgInf.m_int64, sizeof(INT64));
			}

		}
		/*返回系统类型*/
		auto ret_sys_data(MDATA_INF& pArgInf) {
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
				memcpy(&pArgInf.m_int64, p.data(), sizeof(pArgInf.m_int64));
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
		auto ret_user_data(MDATA_INF& pArgInf) {
			pArgInf.m_dtDataType = m_DataType;
			auto p = m_data.get();
			pArgInf.m_pCompoundData = elibstl::ealloc(p.size());
			memcpy(pArgInf.m_pCompoundData, p.data(), p.size());
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
				break;
			default:
				put_errmsg(L"");
				break;
			}
		}

		void get(MDATA_INF& pArgInf) {
			switch (m_dtt)
			{
			case elibstl::EplVar::DTT_IS_SYS_DATA_TYPE:
				ret_sys_data(pArgInf);
				break;
			case elibstl::EplVar::DTT_IS_USER_DATA_TYPE:
				ret_sys_data(pArgInf);
				break;
			case elibstl::EplVar::DTT_IS_LIB_DATA_TYPE:
				break;
			default:
				put_errmsg(L"该变量为空变量");
				break;
			}
		}
	};

};



//namespace elibstl {
//	struct EplVar
//	{
//		enum DTT
//		{
//			DTT_IS_NULL_DATA_TYPE = 0,
//			DTT_IS_SYS_DATA_TYPE = 1,
//			DTT_IS_USER_DATA_TYPE = 2,
//			DTT_IS_LIB_DATA_TYPE = 3,
//
//		};
//		DTT m_dtt{ DTT_IS_NULL_DATA_TYPE };
//		void* m_pData{ nullptr };
//		DATA_TYPE m_DataType{ DATA_TYPE::_SDT_NULL };
//		size_t m_DataSize{ 0 };
//	public:
//		//EplVar() = default;
//		//EplVar(MDATA_INF pArgInf) {
//		//	if (m_bCreate)
//		//		return;
//		//	if (!pArgInf.is_dt_flag())
//		//		return;
//		//}
//		//~EplVar()
//		//{
//		//	/*释放指针*/
//		//	if (m_pData)
//		//	{
//		//		operator delete (m_pData);
//		//		m_pData = nullptr;
//		//	}
//
//		DTT GetDataTypeType(const DATA_TYPE& dtDataType)
//		{
//			if (dtDataType == _SDT_NULL)
//				return DTT_IS_NULL_DATA_TYPE;
//			auto flag = static_cast<unsigned int>(dtDataType);
//			if (FlagCheck<unsigned int>(flag, DTM_SYS_DATA_TYPE_MASK))
//				return DTT_IS_SYS_DATA_TYPE;
//			else if (FlagCheck<unsigned int>(flag, DTM_USER_DATA_TYPE_MASK))
//				return DTT_IS_USER_DATA_TYPE;
//			else
//			
//
//		//	DWORD dw = dtDataType & 0xC0000000;
//			return DTT_IS_LIB_DATA_TYPE;
//				
//		}
//
//		bool empty() const{
//			return m_pData ? false : true;
//		}
//		void clean() {
//			if (m_pData) {
//				operator delete  (m_pData);
//				m_pData = nullptr;
//				m_DataType = DATA_TYPE::_SDT_NULL;
//				m_DataSize = 0; 
//				m_dtt = DTT_IS_NULL_DATA_TYPE;
//			}
//		}
//		auto make_sys_data(const MDATA_INF& pArgInf) {
//			m_DataType = pArgInf.m_dtDataType;
//			debug_put("此位置");
//			if (m_DataType == SDT_TEXT)
//			{
//				m_DataSize = strlen(pArgInf.m_pText);
//				m_pData = operator new(m_DataSize + 1);
//				memcpy(m_pData, pArgInf.m_pText, m_DataSize + 1);
//			}
//			else if (m_DataType == SDT_BIN)
//			{
//				m_DataSize = reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin)[1];
//				m_pData = operator new(m_DataSize);
//				memcpy(m_pData, reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin) + 2, m_DataSize);
//			}
//			else {
//		/*		static  const std::map<DATA_TYPE, size_t> dataSizes = {
//										{SDT_BYTE, sizeof(BYTE)},
//										{SDT_SHORT, sizeof(SHORT)},
//										{SDT_BOOL, sizeof(BOOL)},
//										{SDT_INT, sizeof(INT)},
//										{SDT_FLOAT, sizeof(FLOAT)},
//										{SDT_SUB_PTR, sizeof(DWORD)},
//											{SDT_INT64, sizeof(INT64)},
//											{SDT_DOUBLE, sizeof(DOUBLE)},
//											{SDT_DATE_TIME, sizeof(DATE)}
//				};
//				auto iter = dataSizes.find(pArgInf.m_dtDataType);
//				if (iter != dataSizes.end()) {
//					m_DataSize = iter->second;
//				}
//				if (m_DataSize == 0)
//					put_errmsg(L"出现重大错误,运行时通用变量无法获取长度");*/
//				m_pData = operator new(sizeof(INT64));
//				memcpy(m_pData, &pArgInf.m_int64, sizeof(INT64));
//			}
//	
//		}
//		auto get_sys_data(PMDATA_INF& pArgInf) {
//			if (empty())
//				return;
//			
//			pArgInf->m_dtDataType = m_DataType;
//			if (m_DataType == SDT_TEXT)/*文本型*/
//				pArgInf->m_pText = elibstl::clone_text(reinterpret_cast<char*>(m_pData));
//			else if (m_DataType == SDT_BIN)/*字节集型*/
//			{
//				pArgInf->m_pBin = elibstl::clone_bin(reinterpret_cast<unsigned char*>(m_pData), m_DataSize);
//			}
//			else {/*数值型*/
//				auto val = *reinterpret_cast<INT64*>(m_pData);
//				pArgInf->m_int64 = val;
//			}
//		}
//		void set(const MDATA_INF &pArgInf) {
//			/*先释放*/
//			if (m_pData) {
//				operator delete  (m_pData);
//				m_pData = nullptr;
//				m_DataType = DATA_TYPE::_SDT_NULL;
//				m_DataSize = 0;
//			}
//
//			m_dtt = GetDataTypeType(pArgInf.m_dtDataType);
//			debug_put(m_dtt);
//			if (m_dtt== DTT_IS_SYS_DATA_TYPE)
//			{
//				make_sys_data(pArgInf);
//			}
//			else if (m_dtt == DTT_IS_LIB_DATA_TYPE)
//			{
//				///*获取库定义信息*/
//				//auto info= reinterpret_cast<LIB_DATA_TYPE_INFO*>(elibstl::NotifySys(NAS_GET_LIB_DATA_TYPE_INFO, pArgInf.m_dtDataType, 0));
//				///*如果为对象,则调用其构造以及析构函数处理*/
//				//if (info.)
//				//{
//				//	info->m_pnCmdsIndex
//				//}
//			}
//
//			//m_DataSize = get_arg_runtime_type(pArgInf);
//
//			/*易语言的数据类型*/
//		/*	static  const std::map<DATA_TYPE, size_t> dataSizes = {
//			{SDT_BYTE, sizeof(BYTE)},
//			{SDT_SHORT, sizeof(SHORT)},
//			{SDT_BOOL, sizeof(BOOL)},
//			{SDT_INT, sizeof(INT)},
//			{SDT_FLOAT, sizeof(FLOAT)},
//			{SDT_SUB_PTR, sizeof(DWORD)},
//			{SDT_TEXT, sizeof(DWORD)},
//			{SDT_BIN, sizeof(DWORD)},
//			{SDT_INT64, sizeof(INT64)},
//			{SDT_DOUBLE, sizeof(DOUBLE)},
//			{SDT_DATE_TIME, sizeof(DATE)}
//			};
//			auto iter = dataSizes.find(pArgInf.m_dtDataType);
//			if (iter != dataSizes.end()) {
//				 iter->second;
//			}*/
//			//LocalSize();
//		}
//		void get(PMDATA_INF& pArgInf) {
//			if (!pArgInf->m_dtDataType == m_DataType) {
//				put_errmsg(L"变量中储存的数据和欲接受的数据类型不同!"); 
//				return;
//			}
//			if (m_dtt == DTT_IS_SYS_DATA_TYPE)
//			{
//				get_sys_data(pArgInf);
//			}
//		}
//
//
//	};
//}


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
	{"欲置入的值", "支持任意类型", 0, 0, _SDT_ALL, 0, ArgMark::AS_NONE},
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
	self->get(pRetData[0]);
	if (pArgInf[1].m_dtDataType!=_SDT_NULL)
		pArgInf[1] = pRetData[0];
	
}
static ARG_INFO s_Args_get[] =
{
	{"欲获取的值", "和返回值同为一个指针,系统类型可直接使用返回值", 0, 0, _SDT_ALL, 0, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY| ArgMark::AS_RECEIVE_VAR},
};
FucInfo Fn_Var_Get = { {
		/*ccname*/  "取",
		/*egname*/  "Get",
		/*explain*/ "取置",
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     _SDT_ALL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  s_Args_get },ESTLFNAME(libstl_Var_Get) };
static INT s_dtCmdIndexcommobj_edbs_ex[] = { 304,305,306 ,307,308};
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



//static ARG_INFO s_ArgInfo[] =
//{
//	/*name*/     "欲转换为字节集的数据",
//	/*explain*/  "参数值只能为基本数据类型数据或字节数组",
//	/*bmp inx*/  0,
//	/*bmp num*/  0,
//	/*type*/     _SDT_ALL,
//	/*default*/  0,
//	/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA,
//};
//
//static CMD_INFO s_CmdInfo =
//{
//	/*ccname*/    "到字节集WWW",
//	/*egname*/    "ToBin",
//	/*explain*/   "将指定数据转换为字节集后返回转换结果",
//	/*category*/  10,
//	/*state*/     NULL,
//	/*ret*/       SDT_BIN,
//	/*reserved*/  0,
//	/*level*/     LVL_SIMPLE,
//	/*bmp inx*/   0,
//	/*bmp num*/   0,
//	/*ArgCount*/  1,
//	/*arg lp*/    s_ArgInfo
//};
//
//
//
//
//// 辅助函数
//LPBYTE GetMDataPtr(PMDATA_INF pInf, LPINT pnDataSize)
//{
//	
//	auto c=GetDataTypeType(pInf->m_dtDataType) == DTT_IS_SYS_DATA_TYPE;
//
//	switch (pInf->m_dtDataType)
//	{
//	case SDT_BYTE:
//		*pnDataSize = sizeof(BYTE);
//		return (LPBYTE)&pInf->m_byte;
//	case SDT_SHORT:
//		*pnDataSize = sizeof(SHORT);
//		return (LPBYTE)&pInf->m_short;
//	case SDT_INT:
//		*pnDataSize = sizeof(INT);
//		return (LPBYTE)&pInf->m_int;
//	case SDT_INT64:
//		*pnDataSize = sizeof(INT64);
//		return (LPBYTE)&pInf->m_int64;
//	case SDT_FLOAT:
//		*pnDataSize = sizeof(FLOAT);
//		return (LPBYTE)&pInf->m_float;
//	case SDT_DOUBLE:
//		*pnDataSize = sizeof(DOUBLE);
//		return (LPBYTE)&pInf->m_double;
//	case SDT_BOOL:
//		*pnDataSize = sizeof(BOOL);
//		return (LPBYTE)&pInf->m_bool;
//	case SDT_DATE_TIME:
//		*pnDataSize = sizeof(DATE);
//		return (LPBYTE)&pInf->m_date;
//	case SDT_SUB_PTR:
//		*pnDataSize = sizeof(DWORD);
//		return (LPBYTE)&pInf->m_dwSubCodeAdr;
//	case SDT_TEXT:
//		*pnDataSize = strlen(pInf->m_pText) + 1;
//		return (LPBYTE)pInf->m_pText;
//	case SDT_BIN: {
//		LPBYTE pBinData = pInf->m_pBin + sizeof(INT) * 2;
//		*pnDataSize = *(LPINT)(pBinData - sizeof(INT));
//		return pBinData; }
//	default:
//		return NULL;
//	}
//}
//
//// 命令实现函数
//void fnCnvToBin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
//{
//	//!!! 对于具有 AS_RECEIVE_VAR_OR_ARRAY 或 AS_RECEIVE_ALL_TYPE_DATA 标志的参数，
//	// 其数据类型中可能带有DT_IS_ARY数组标志，必须以以下方式分离出其数据类型和数组标志。
//	
//	
//	BOOL blIsAry = pArgInf->is_dt_flag(); 
//	pArgInf->remove_dt_flag();
//	auto dtDataType = pArgInf->m_dtDataType;
//
//
//	LPBYTE pData;
//	INT nDataSize;
//	auto c = GetDataTypeType(dtDataType);
//	debug_put(c);
//	if (dtDataType == SDT_BYTE && blIsAry == TRUE)
//	{
//		pData = (LPBYTE)pArgInf[0].m_pAryData + sizeof(INT) * 2;
//		nDataSize = *(LPINT)(pData - sizeof(INT));
//	}
//	else if (blIsAry == TRUE || c != DTT_IS_SYS_DATA_TYPE)
//	{
//		debug_put(c);
//		pRetData->m_pBin = NULL;
//		return;
//	}
//	else if (dtDataType == SDT_TEXT)
//	{
//		pData = (LPBYTE)pArgInf->m_pText;
//		nDataSize = strlen(pArgInf->m_pText);
//	}
//	else
//		pData = GetMDataPtr(pArgInf, &nDataSize);
//
//	pRetData->m_pBin = elibstl::clone_bin(pData, nDataSize);
//}
//
//
//FucInfo TESTEST = { s_CmdInfo,ESTLFNAME(fnCnvToBin) };