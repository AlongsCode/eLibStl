#include"EcontrolHelp.h"

inline auto get_arg_runtime_type(PMDATA_INF pArgInf, size_t index) {
	return pArgInf[index].m_dtDataType;;
}
inline auto get_arg_runtime_type(MDATA_INF pArgInf) {
	return pArgInf.m_dtDataType;;
}
namespace elibstl {
	struct EplVar
	{
		enum DTT
		{
			DTT_IS_NULL_DATA_TYPE = 0,
			DTT_IS_SYS_DATA_TYPE = 1,
			DTT_IS_USER_DATA_TYPE = 2,
			DTT_IS_LIB_DATA_TYPE = 3,

		};
		DTT m_dtt{ DTT_IS_NULL_DATA_TYPE };
		void* m_pData{ nullptr };
		DATA_TYPE m_DataType{ DATA_TYPE::_SDT_NULL };
		size_t m_DataSize{ 0 };
	public:
		//EplVar() = default;
		//EplVar(MDATA_INF pArgInf) {
		//	if (m_bCreate)
		//		return;
		//	if (!pArgInf.is_dt_flag())
		//		return;
		//}
		//~EplVar()
		//{
		//	/*释放指针*/
		//	if (m_pData)
		//	{
		//		operator delete (m_pData);
		//		m_pData = nullptr;
		//	}

		DTT GetDataTypeType(const DATA_TYPE& dtDataType)
		{
			if (dtDataType == _SDT_NULL)
				return DTT_IS_NULL_DATA_TYPE;

			DWORD dw = dtDataType & 0xC0000000;
			return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
				dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
				DTT_IS_LIB_DATA_TYPE;
		}

		bool empty() const{
			return m_pData ? false : true;
		}
		void clean() {
			if (m_pData) {
				operator delete  (m_pData);
				m_pData = nullptr;
				m_DataType = DATA_TYPE::_SDT_NULL;
				m_DataSize = 0; 
				m_dtt = DTT_IS_NULL_DATA_TYPE;
			}
		}
		auto make_sys_data(const MDATA_INF& pArgInf) {
			m_DataType = pArgInf.m_dtDataType;
			debug_put("此位置");
			if (m_DataType == SDT_TEXT)
			{
				m_DataSize = strlen(pArgInf.m_pText);
				m_pData = operator new(m_DataSize + 1);
				memcpy(m_pData, pArgInf.m_pText, m_DataSize + 1);
			}
			else if (m_DataType == SDT_BIN)
			{
				m_DataSize = reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin)[1];
				m_pData = operator new(m_DataSize);
				memcpy(m_pData, reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin) + 2, m_DataSize);
			}
			else {
		/*		static  const std::map<DATA_TYPE, size_t> dataSizes = {
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
				auto iter = dataSizes.find(pArgInf.m_dtDataType);
				if (iter != dataSizes.end()) {
					m_DataSize = iter->second;
				}
				if (m_DataSize == 0)
					put_errmsg(L"出现重大错误,运行时通用变量无法获取长度");*/
				m_pData = operator new(sizeof(INT64));
				memcpy(m_pData, &pArgInf.m_int64, sizeof(INT64));
			}
	
		}
		auto get_sys_data(PMDATA_INF& pArgInf) {
			if (empty())
				return;
			
			pArgInf->m_dtDataType = m_DataType;
			if (m_DataType == SDT_TEXT)/*文本型*/
				pArgInf->m_pText = elibstl::clone_text(reinterpret_cast<char*>(m_pData));
			else if (m_DataType == SDT_BIN)/*字节集型*/
			{
				pArgInf->m_pBin = elibstl::clone_bin(reinterpret_cast<unsigned char*>(m_pData), m_DataSize);
			}
			else {/*数值型*/
				auto val = *reinterpret_cast<INT64*>(m_pData);
				pArgInf->m_int64 = val;
			}
		}
		void set(const MDATA_INF &pArgInf) {
			/*先释放*/
			if (m_pData) {
				operator delete  (m_pData);
				m_pData = nullptr;
				m_DataType = DATA_TYPE::_SDT_NULL;
				m_DataSize = 0;
			}

			m_dtt = GetDataTypeType(pArgInf.m_dtDataType);
			debug_put(m_dtt);
			if (m_dtt== DTT_IS_SYS_DATA_TYPE)
			{
				make_sys_data(pArgInf);
			}
			else if (m_dtt == DTT_IS_LIB_DATA_TYPE)
			{
				///*获取库定义信息*/
				//auto info= reinterpret_cast<LIB_DATA_TYPE_INFO*>(elibstl::NotifySys(NAS_GET_LIB_DATA_TYPE_INFO, pArgInf.m_dtDataType, 0));
				///*如果为对象,则调用其构造以及析构函数处理*/
				//if (info.)
				//{
				//	info->m_pnCmdsIndex
				//}
			}

			//m_DataSize = get_arg_runtime_type(pArgInf);

			/*易语言的数据类型*/
		/*	static  const std::map<DATA_TYPE, size_t> dataSizes = {
			{SDT_BYTE, sizeof(BYTE)},
			{SDT_SHORT, sizeof(SHORT)},
			{SDT_BOOL, sizeof(BOOL)},
			{SDT_INT, sizeof(INT)},
			{SDT_FLOAT, sizeof(FLOAT)},
			{SDT_SUB_PTR, sizeof(DWORD)},
			{SDT_TEXT, sizeof(DWORD)},
			{SDT_BIN, sizeof(DWORD)},
			{SDT_INT64, sizeof(INT64)},
			{SDT_DOUBLE, sizeof(DOUBLE)},
			{SDT_DATE_TIME, sizeof(DATE)}
			};
			auto iter = dataSizes.find(pArgInf.m_dtDataType);
			if (iter != dataSizes.end()) {
				 iter->second;
			}*/
			//LocalSize();
		}
		void get(PMDATA_INF& pArgInf) {
			if (!pArgInf->m_dtDataType == m_DataType) {
				put_errmsg(L"变量中储存的数据和欲接受的数据类型不同!"); 
				return;
			}
			if (m_dtt == DTT_IS_SYS_DATA_TYPE)
			{
				get_sys_data(pArgInf);
			}
		}


	};
}


//构造
EXTERN_C void Fn_EplVar_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
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

//复制
EXTERN_C void Fn_EplVar_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	auto rht = static_cast<elibstl::EplVar*>(*pArgInf[1].m_ppCompoundData);
	*self = *rht;
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
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,Fn_EplVar_copy ,"Fn_EplVar_copy" };

//析构
EXTERN_C void Fn_EplVar_des(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	if (self)
	{
		self->~EplVar();
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
	self->set(pArgInf[0]);
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
		/*arg lp*/  s_Args_set },ESTLFNAME(libstl_Var_Set) };
EXTERN_C void libstl_Var_Get(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<elibstl::EplVar>(pArgInf);
	self->get(pRetData);
}

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
		/*ArgCount*/0,
		/*arg lp*/  0 },ESTLFNAME(libstl_Var_Get) };
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