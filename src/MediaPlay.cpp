#include"EcontrolHelp.h"
#include <algorithm>
#pragma comment (lib, "winmm.lib")
#pragma warning(disable:28159)
using namespace std;
#define  MCI_RETURN_STRING_SIZE 256
#define AUDIO_CHANNEL_LEFT 1
#define AUDIO_CHANNEL_RIGHT 2
#define AUDIO_CHANNEL_STEREO 3
#define AUDIO_CHANNEL_AVERAGE 4
//我的媒体播放类
class eMideaPlay
{
	HWND  m_winHwnd;
	bool m_isVideo;
	wstring m_MediaAlias;
public:
	eMideaPlay() :
		m_winHwnd(NULL),
		m_isVideo(false),
		m_MediaAlias({})
	{

	};
	~eMideaPlay() {
		Close();
	}
	bool Open(const wstring& fileName, HWND hWnd = 0) {
		if (!m_MediaAlias.empty())
		{
			return false;
		}
		m_MediaAlias = L"Media" + to_wstring(GetTickCount());
		int dotIndex = fileName.rfind(L'.') + 1;
		wstring ileExtension = fileName.substr(dotIndex, 3);
		for (wchar_t& c : ileExtension) {
			c = towlower(c);
		}
		const wchar_t* mediaType = L"MPEGvideo";
		if (ileExtension == L"avi") {
			mediaType = L"avivideo";
		}
		else if (ileExtension == L"wav") {
			mediaType = L"waveaudio";
		}
		else if (ileExtension == L"cda") {
			mediaType = L"cdaudio";
		}
		else if (ileExtension == L"rm" || ileExtension == L"ra" || ileExtension == L"mp" || ileExtension == L"ram" || ileExtension == L"rmvb") {
			mediaType = L"MPEGvideo";
		}
		else if (ileExtension == L"mid" || ileExtension == L"rmi" || ileExtension == L"idi") {
			mediaType = L"Sequencer";
		}
		else if (ileExtension == L"asf" || ileExtension == L"wma" || ileExtension == L"asx" || ileExtension == L"ivf" || ileExtension == L"lsf" || ileExtension == L"lsx" || ileExtension == L"p2v" || ileExtension == L"wax" || ileExtension == L"wvx" || ileExtension == L"wmx" || ileExtension == L"wmp") {
			mediaType = L"MPEGvideo2";
		}
		MCIERROR errorCode = mciSendStringW((L"open \"" + fileName + L"\" type " + mediaType + L" alias " + m_MediaAlias + L" style child").c_str(), NULL, 0, hWnd);
		m_isVideo = (ileExtension != L"mp3") && (ileExtension != L"wav") && (ileExtension != L"cda") && (ileExtension != L"mid");
		if (m_isVideo && hWnd) {
			wchar_t buf[64];
			swprintf_s(buf, L"window %s handle %p", m_MediaAlias.c_str(), hWnd);
			if (mciSendStringW(buf, NULL, 0, hWnd) == 0) {
				m_winHwnd = hWnd;
			};
		}
		if (errorCode != 0) {
			m_MediaAlias.clear();
			return false;
		}
		return true;
	}
	bool IsOpen() {
		return !m_MediaAlias.empty();
	}

	bool Play(int position = -1)
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		bool error = true;
		wstring command;
		wstring internalCommand;
		if (IsWindow(m_winHwnd))
		{
			command = L"window " + m_MediaAlias + L" handle " + to_wstring((size_t)m_winHwnd);
			error = mciSendStringW(command.c_str(), NULL, 0, NULL) == 0;
		}
		if (position == -1)
		{
			internalCommand = L"play " + m_MediaAlias + L" ";
		}
		else
		{
			internalCommand = L"play " + m_MediaAlias + L" from " + to_wstring(position) + L" ";
		}
		bool Ret = !mciSendStringW(internalCommand.c_str(), NULL, 0, NULL) && error;
		return Ret;
	}

	bool IsVideo() {
		return GetHwnd() != 0;
	};
	HWND GetHwnd()
	{
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		std::wstring lpstrCommand;
		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		lpstrCommand = L"status " + m_MediaAlias + L" window handle";
		mciSendStringW(lpstrCommand.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
		long long ret = _wtoll(strReturnString);
		return reinterpret_cast<HWND>(ret);
	}

	bool SetHwnd(HWND handle)
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		if (IsWindow(handle))
		{
			m_winHwnd = handle;
			std::wstring command = L"window " + m_MediaAlias + L" handle " + std::to_wstring((long long)handle);
			MCIERROR ret = mciSendStringW(command.c_str(), 0, 0, 0);
			return ret == 0;
		}
		return false;
	};
	//获取当前的播放状态，为以下常量值之一：0、#未知状态；1、#播放状态；2、#停止状态；3、#暂停状态。本命令为初级对象成员命令。* | **| *
	int GetMode()
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		mciSendStringW((L"status " + m_MediaAlias + L" mode").c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
		if (wcscmp(strReturnString, L"playing") == 0) {
			return 1;
		}
		else if (wcscmp(strReturnString, L"stopped") == 0) {
			return 2;
		}
		else if (wcscmp(strReturnString, L"paused") == 0) {
			return 3;
		}
		else {
			return 0;
		}
	};
	//单位毫秒
	size_t GetLength() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		wstring Command;
		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		size_t Ret = 0;
		if (IsVideo()) {
			Command = L"set " + m_MediaAlias + L" time format milliseconds";
		}
		else {
			Command = L"set " + m_MediaAlias + L" time format milliseconds";
		}
		mciSendStringW(Command.c_str(), 0, 0, 0);
		Command = L"status " + m_MediaAlias + L" length";
		if (mciSendStringW(Command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0))
		{
			return 0;
		}
		else
		{
			Ret = _wtoi(strReturnString);
		}
		return  Ret;
	};
	long long GetPosition() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		std::wstring command;
		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		long long Ret = 0;
		command = L"status " + m_MediaAlias + L" position";
		if (mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0))
		{
			Ret = -1;
		}
		else
		{
			Ret = _wtoi(strReturnString);
		}
		return  Ret;
	};
	size_t GetFrameRate() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		std::wstring command;
		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		size_t Ret = 0;

		if (IsVideo())
		{
			command = L"capability " + m_MediaAlias + L" has video" + L" status " + m_MediaAlias + L" frame rate";
			mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
			Ret = _wtoi(strReturnString) / 1000;
		}
		return Ret;
	};
	size_t GetFrames() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		std::wstring command = L"set " + m_MediaAlias + L" time format frames";
		mciSendStringW(command.c_str(), nullptr, 0, nullptr);
		command = L"status " + m_MediaAlias + L" length";

		wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
		if (mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, nullptr))
		{
			return 0;
		}
		else
		{
			return _wtoi(strReturnString);
		}
	};
	bool Pause() {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		std::wstring command = L"pause " + m_MediaAlias;
		return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
	};
	bool Continue() {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		std::wstring command = L"resume " + m_MediaAlias;
		return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
	};
	bool Stop() {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		std::wstring command = L"stop " + m_MediaAlias;
		if (mciSendStringW(command.c_str(), nullptr, 0, nullptr) != 0) {
			return false;
		}
		command = L"seek " + m_MediaAlias + L" to start";
		return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
	};
	wstring GetMCIAlias() {
		return m_MediaAlias;
	};
	size_t GetTotalSec() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		return GetLength() / 1000;
	};
	bool Close() {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		std::wstring command = L"close " + m_MediaAlias;
		if (mciSendStringW(command.c_str(), 0, 0, 0))
		{
			return  false;
		}
		m_winHwnd = NULL;
		m_isVideo = false;
		m_MediaAlias.clear();
		return true;
	};
	//音量为0-100
	bool SetVolume(short leftChannelVolume = -1, short rightChannelVolume = -1) {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		MCIERROR leftChannelError = 0;
		MCIERROR rightChannelError = 0;
		bool result = false;
		std::wstring command;
		leftChannelVolume = 10 * leftChannelVolume;
		rightChannelVolume = rightChannelVolume * 10;
		if (leftChannelVolume >= 0 && leftChannelVolume <= 1000) {
			command = L"setaudio " + m_MediaAlias + L" left volume to " + std::to_wstring(leftChannelVolume);
			leftChannelError = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
		}
		if (rightChannelVolume >= 0 && rightChannelVolume <= 1000)
		{
			command = L"setaudio " + m_MediaAlias + L" right volume to " + std::to_wstring(rightChannelVolume);
			rightChannelError = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
			leftChannelError = leftChannelError && !rightChannelError;
		}
		return leftChannelError;
	};
	//音量为0-100
	bool GetVolume(short* leftChannelVolume, short* rightChannelVolume) {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		wchar_t strReturnString[33] = {};
		std::wstring command;
		bool leftChannelSuccess = false;
		bool rightChannelSuccess = false;
		bool Ret = false;
		if (leftChannelVolume)
		{
			command = L"status " + m_MediaAlias + L" left volume";
			leftChannelSuccess = mciSendStringW(command.c_str(), strReturnString, 32, 0) == 0;
			if (leftChannelSuccess)
			{
				*leftChannelVolume = _wtoi(strReturnString) / 10;
			}

		}
		if (rightChannelVolume)
		{
			command = L"status " + m_MediaAlias + L" right volume";
			rightChannelSuccess = mciSendStringW(command.c_str(), strReturnString, 32, 0);
			if (rightChannelSuccess)
			{
				*rightChannelVolume = _wtoi(strReturnString) / 10;
			}
			leftChannelSuccess = leftChannelSuccess && !rightChannelSuccess;
		}
		return leftChannelSuccess;
	};
	//返回常量中以"声道_"开头的常量值。失败返回0
	int GetChannel() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		int result = 0;
		WCHAR channelName[MCI_RETURN_STRING_SIZE] = {};
		std::wstring channelNameLower;
		result = mciSendStringW((L"Status " + m_MediaAlias + L" audio source").c_str(), channelName, MCI_RETURN_STRING_SIZE, 0);
		if (result != 0) {
			return 0;
		}
		channelNameLower = toLower(channelName);
		if (channelNameLower == L"left") {
			result = AUDIO_CHANNEL_LEFT;
		}
		else if (channelNameLower == L"right") {
			result = AUDIO_CHANNEL_RIGHT;
		}
		else if (channelNameLower == L"stereo") {
			result = AUDIO_CHANNEL_STEREO;
		}
		else if (channelNameLower == L"average") {
			result = AUDIO_CHANNEL_AVERAGE;
		}
		return result;
	};
	std::wstring toLower(const std::wstring& str) {
		wstring Ret(str);
		std::transform(str.begin(), str.end(), Ret.begin(), tolower);
		return  Ret;
	}
	bool SetChannel(int type) {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		wstring AUDIO;
		if (type == AUDIO_CHANNEL_LEFT) {
			AUDIO = L"left";
		}
		else if (type == AUDIO_CHANNEL_RIGHT) {
			AUDIO = L"right";
		}
		else if (type == AUDIO_CHANNEL_STEREO) {
			AUDIO = L"stereo";
		}
		else if (type == AUDIO_CHANNEL_AVERAGE) {
			AUDIO = L"average";
		}
		else {
		}
		return mciSendStringW((L"setaudio " + m_MediaAlias + L" source to " + AUDIO).c_str(), 0, 0, 0) == 0;
	};

	bool SetFrame(size_t framePos, bool playImmediately = false)
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		MCIERROR result = 0;
		wstring command = L"set " + m_MediaAlias + L" time format frames";
		result = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
		if (result != 0)
		{
			return false;
		}
		command = L"seek " + m_MediaAlias + L" to " + std::to_wstring(framePos);
		result = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
		if (result != 0)
		{
			return false;
		}
		if (playImmediately)
		{
			Play();
		}
		return result == 0;
	};
	//播放位置必须小于媒体长度，否则可能会造成命令失败。单位：毫秒
	bool SetPos(size_t playPosition, bool playImmediately = false)
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		MCIERROR result = 0;
		result = mciSendStringW((L"set " + m_MediaAlias + L" time format milliseconds").c_str(), nullptr, 0, nullptr);
		if (result != 0)
			return false;
		result = mciSendStringW((L"seek " + m_MediaAlias + L" to " + std::to_wstring(playPosition)).c_str(), nullptr, 0, nullptr);
		if (result != 0)
			return false;
		if (playImmediately)
			Play();
		return result == 0;
	}
	//并非所有媒体都支持速度调整,1到2000之间的整数。原始速度为1000。2000为原始速度的2倍，500为原始速度的一半。警告:过慢的速度将导致媒体看起来已经停止了
	bool SetPlaySpeed(int speed)
	{
		if (m_MediaAlias.empty())
		{
			return false;
		}
		if (speed < 1 || speed>2000) {
			return false;
		}
		return mciSendStringW((L"set " + m_MediaAlias + L" speed " + to_wstring(speed)).c_str(), 0, 0, 0) == 0;
	}

	int GetPlaySpeed() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		wchar_t speedStr[MCI_RETURN_STRING_SIZE] = {};
		mciSendStringW((L"status " + m_MediaAlias + L" speed").c_str(), speedStr, MCI_RETURN_STRING_SIZE, 0);
		return _wtoi(speedStr);
	};
	//执行成功返回0，否则返回非零的整数。说明：执行后的实际音量可能最多±2的误差，这里设置的是系统的音量值
	bool SetMediaVolume(int  mediaVolume) {
		if (m_MediaAlias.empty())
		{
			return false;
		}
		if (mediaVolume < 0 || mediaVolume>100) {
			return false;
		}
		std::wstring command = L"setaudio " + m_MediaAlias + L" volume to " + std::to_wstring(mediaVolume * 10);
		return  mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
	};

	int GetMediaVolume() {
		if (m_MediaAlias.empty())
		{
			return 0;
		}
		wchar_t volume[MCI_RETURN_STRING_SIZE];
		bool result = mciSendStringW((L"status " + m_MediaAlias + L" volume").c_str(), volume, MCI_RETURN_STRING_SIZE, 0);
		if (result == 0) {
			return _wtoi(volume) / 10;
		}
		else {
			return -1;
		}

	};



};
static INT s_dtCmdIndexcommobj_media_play[] = { 77,78,79,80,81,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106 };
static LIB_DATA_TYPE_ELEMENT s_dt_const_media_play[] =
{
	/*000*/ {SDT_INT, 0, "左声道", "AUDIO_CHANNEL_LEFT", NULL, LES_HAS_DEFAULT_VALUE, (INT)1},
	/*001*/ {SDT_INT, 0, "右声道", "AUDIO_CHANNEL_RIGHT", NULL, LES_HAS_DEFAULT_VALUE, (INT)2},
	/*002*/ {SDT_INT, 0, "立体声", "AUDIO_CHANNEL_STEREO", NULL, LES_HAS_DEFAULT_VALUE, (INT)3},
	/*003*/ {SDT_INT, 0, "均衡", "AUDIO_CHANNEL_AVERAGE", NULL, LES_HAS_DEFAULT_VALUE, (INT)4},
};



//构造
EXTERN_C void Fn_media_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	self = new eMideaPlay;
}
//构造
FucInfo Media_structure = { {
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
	} ,Fn_media_structure ,"Fn_media_structure" };

//复制
EXTERN_C void fn_media_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	const auto rht = static_cast<eMideaPlay*>(*pArgInf[1].m_ppCompoundData);
	*self = *rht;
}
FucInfo Media_copy = { {
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
	} ,fn_media_copy ,"fn_media_copy" };

//析构
EXTERN_C void fn_media_destruct(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	if (self)
	{
		self->~eMideaPlay();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo Media_destruct = { {
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
	} ,fn_media_destruct ,"fn_media_destruct" };

static ARG_INFO m_media_arg[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ ("该参数为要打开的媒体文件名，而非二进制数据."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "窗口句柄",
		/*explain*/ ("播放视频文件所需窗口，默认为当前活动窗口，如果播放类型为视频时不指定窗口句柄可能会导致失败"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{"窗口句柄", "要设置的窗口句柄", 0, 0, SDT_INT, 0, NULL},
	{"播放位置", "该参数为播放位置，以毫秒为单位。默认为-1，表示从当前处播放", 0, 0, SDT_INT, -1, AS_HAS_DEFAULT_VALUE},
	{"左声道音量", "范围为0-100，0为静音，100为最大音量。如果本参数被省略或超出范围，则不修改此声道音量。", 0, 0, SDT_SHORT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"右声道音量", "范围为0-100，0为静音，100为最大音量。如果本参数被省略或超出范围，则不修改此声道音量。", 0, 0, SDT_SHORT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"左声道音量", "提供参数数据时只能提供变量。范围为0-100，0为静音，100为最大音量。如果本参数被省略，则不返回此声道音量。", 0, 0, SDT_SHORT, 0, AS_RECEIVE_VAR},
	{"右声道音量", "提供参数数据时只能提供变量。范围为0-100，0为静音，100为最大音量。如果本参数被省略，则不返回此声道音量。", 0, 0, SDT_SHORT, 0, AS_RECEIVE_VAR},
	{"声道类型", "声道类型常量1.左声道,2.右声道3.立体声4.均衡", 0, 0, SDT_INT, 0, 0},
	{"媒体音量", "需设置媒体音量的大小", 0, 0, SDT_INT, 0, 0},
	{"播放速度", "并非所有媒体都支持速度调整,1到2000之间的整数。原始速度为1000。2000为原始速度的2倍，500为原始速度的一半。警告:过慢的速度将导致媒体看起来已经停止了", 0, 0, SDT_INT, 0, 0},
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"是否立即播放", "默认为假", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};
EXTERN_C void Fn_media_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto hWnd = elibstl::args_to_data<INT>(pArgInf, 2);
	pRetData->m_bool = self->Open(wstring(elibstl::args_to_wsdata(pArgInf, 1)), hWnd.has_value() ? IsWindow(reinterpret_cast<HWND>(hWnd.value())) ? reinterpret_cast<HWND>(hWnd.value()) : GetActiveWindow() : GetActiveWindow());
}

FucInfo Media_open = { {
		/*ccname*/  ("打开"),
		/*egname*/  ("open"),
		/*explain*/ ("打开指定媒体文件。成功返回真，失败返回假。如果已经打开则直接返回真，想要重新打开文件,请关闭以后再次打开新文件。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/   &m_media_arg[0],
	} ,Fn_media_open ,"Fn_media_open" };

EXTERN_C void Fn_media_IsVideo(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->IsVideo();
}
FucInfo Media_IsVideo = { {
		"是否视频", "IsVideo", "判断当前播放的内容是否是视频。如果是返回真，否则返回假", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0
	} ,Fn_media_IsVideo ,"Fn_media_IsVideo" };


EXTERN_C void Fn_media_GetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = reinterpret_cast<int>(self->GetHwnd());
}
FucInfo Media_GetHwnd = { {
		"取句柄", "GetHwnd", "获取当前视频播放窗口的Windows 窗口句柄", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0
} ,Fn_media_GetHwnd ,"Fn_media_GetHwnd" };


EXTERN_C void Fn_media_SetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetHwnd(reinterpret_cast<HWND>(pArgInf[1].m_int));
}
FucInfo Media_SetHwnd = { {
		"置句柄", "SetHwnd", "设置当前视频播放窗口的Windows 窗口句柄，成功返回真，失败返回假", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 2} ,
		Fn_media_SetHwnd ,
		"Fn_media_SetHwnd" };
EXTERN_C void Fn_media_GetMode(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetMode();
}
FucInfo Media_GetMode = { {
		 "取状态", "GetMode", "获取当前的播放状态，为以下常量值之一：0、#未知状态；1、#播放状态；2、#停止状态；3、#暂停状态", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMode ,
		"Fn_media_GetMode" };

EXTERN_C void Fn_media_GetLength(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetLength();
}
FucInfo Media_GetLength = { {
		"取长度", "GetLength", "获取当前媒体文件的长度", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetLength ,
		"Fn_media_GetLength" };

EXTERN_C void Fn_media_GetPosition(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int64 = self->GetPosition();
}
FucInfo Media_GetPosition = { {
		"取位置","GetPosition", "获取当前的播放位置", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetPosition ,
		"Fn_media_GetPosition" };

EXTERN_C void Fn_media_GetTotalSec(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetTotalSec();
}
FucInfo Media_GetTotalSec = { {
		"取总时间", "GetTotalSec", "以秒为单位获取总播放时间", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_GetTotalSec ,
		"Fn_media_GetTotalSec" };

EXTERN_C void Fn_media_GetFrameRate(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetFrameRate();
}
FucInfo Media_GetFrameRate = { {
		 "取比率", "GetFrameRate", "获取每一帧的比率", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetFrameRate ,
		"Fn_media_GetFrameRate" };

EXTERN_C void Fn_media_Play(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto pos = elibstl::args_to_data<INT>(pArgInf, 1);
	pRetData->m_int = self->Play(pos.has_value() ? pos.value() : -1);
}
FucInfo Media_Play = { {
		"播放", "Play", "从指定位置开始播放。成功返回真，失败返回假,播放窗口为打开或者置句柄的指定的窗口", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 3}
		,Fn_media_Play,
		"Fn_media_Play" };


EXTERN_C void Fn_media_Pause(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->Pause();
}
FucInfo Media_Pause = { {
		"暂停", "Pause", "暂停播放。成功返回真，失败返回假", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_Pause,
		"Fn_media_Pause" };


EXTERN_C void Fn_media_Stop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->Stop();
}
FucInfo Media_Stop = { {
		"停止","Stop", "停止播放。成功返回真，失败返回假", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_Stop,
		"Fn_media_Stop" };

EXTERN_C void Fn_media_GetMCIAlias(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_pBin = elibstl::clone_textw(self->GetMCIAlias());
}
FucInfo Media_GetMCIAlias = { {
		"取别名", "GetMCIAlias", "获取当前对象使用的MCI别名", -1, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMCIAlias,
		"Fn_media_GetMCIAlias" };


EXTERN_C void Fn_media_Close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->Close();
}
FucInfo Media_Close = { {
		"关闭", "Close", "关闭当前播放的媒体。关闭后无法再对其进行任何操作,成功返回真，失败返回假。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_Close,
		"Fn_media_Close" };


EXTERN_C void Fn_media_SetVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto left = elibstl::args_to_data<SHORT>(pArgInf, 1);
	auto right = elibstl::args_to_data<SHORT>(pArgInf, 2);
	pRetData->m_bool = self->SetVolume(left.has_value() ? left.value() : -1, right.has_value() ? right.value() : -1);
}
FucInfo Media_SetVolume = { {
		"置音量", "SetVolume", " 设置当前播放媒体的音量，不影响系统音量。左右声道中只要有一个设置失败，就会返回假。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, m_media_arg + 4},
		Fn_media_SetVolume,
		"Fn_media_SetVolume" };


EXTERN_C void Fn_media_GetVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto left = elibstl::args_to_data<SHORT*>(pArgInf, 1);
	auto right = elibstl::args_to_data<SHORT*>(pArgInf, 2);
	pRetData->m_bool = self->GetVolume(left.has_value() ? left.value() : 0, right.has_value() ? right.value() : 0);
}
FucInfo Media_GetVolume = { {
		"取音量", "GetVolume", "获取当前播放音量（非系统音量）。左右声道中只要有一个获取失败，就会返回假。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, m_media_arg + 6},
		Fn_media_GetVolume,
		"Fn_media_GetVolume" };


EXTERN_C void Fn_media_continue(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->Continue();
}
FucInfo Media_continue = { {
		"继续", "continue", "继续从暂停位置播放", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_continue,
		"Fn_media_continue" };


EXTERN_C void Fn_media_GetChannel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->GetChannel();
}
FucInfo Media_GetChannel = { {
		"取媒体声道", "GetChannel", "返回常量中的声道类型。失败返回0", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetChannel,
		"Fn_media_GetChannel" };


EXTERN_C void Fn_media_SetChannel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetChannel(pArgInf[1].m_int);
}
FucInfo Media_SetChannel = { {
		"置媒体声道", "SetChannel", "设置媒体声道类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 8},
		Fn_media_SetChannel,
		"Fn_media_SetChannel" };


EXTERN_C void Fn_media_GetFrames(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetFrames();
}
FucInfo Media_GetFrames = { {
		"取帧数", "GetFrames", "取媒体文件的帧数", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetFrames,
		"Fn_media_GetFrames" };


EXTERN_C void Fn_media_GetMediaVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetMediaVolume();
}
FucInfo Media_GetMediaVolume = { {
		"取媒体音量", "GetMediaVolume", "取打开的媒体文件的音量", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMediaVolume,
		"Fn_media_GetMediaVolume" };


EXTERN_C void Fn_media_SetMediaVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetMediaVolume(pArgInf[1].m_int);
}
FucInfo Media_SetMediaVolume = { {
		"置媒体音量", "SetMediaVolume", "执行后的实际音量可能最多±2的误差，这里设置的是系统的音量值", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1,m_media_arg + 9},
		Fn_media_SetMediaVolume,
		"Fn_media_SetMediaVolume" };

EXTERN_C void Fn_media_SetPlaySpeed(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetPlaySpeed(pArgInf[1].m_int);
}
FucInfo Media_SetPlaySpeed = { {
		"置播放速度", "SetPlaySpeed", "设置当前媒体的播放速度。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1,m_media_arg + 10},
		Fn_media_SetPlaySpeed,
		"Fn_media_SetPlaySpeed" };


EXTERN_C void Fn_media_GetPlaySpeed(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetPlaySpeed();
}
FucInfo Media_GetPlaySpeed = { {
		"取播放速度", "GetPlaySpeed", "获取当前媒体的播放速度。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_GetPlaySpeed,
		"Fn_media_GetPlaySpeed" };

EXTERN_C void Fn_media_SetPos(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto is_now = elibstl::args_to_data<SHORT*>(pArgInf, 2);
	pRetData->m_bool = self->SetPos(pArgInf[1].m_int, is_now.has_value() ? is_now.value() : false);
}
FucInfo Media_SetPos = { {
		"置位置", "SetPos", "设置媒体当前播放的位置", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2,m_media_arg + 11},
		Fn_media_SetPos,
		"Fn_media_SetPos" };

EXTERN_C void Fn_media_SetFrame(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto is_now = elibstl::args_to_data<SHORT*>(pArgInf, 2);
	pRetData->m_bool = self->SetFrame(pArgInf[1].m_int, is_now.has_value() ? is_now.value() : false);
}
FucInfo Media_SetFrame = { {
		"跳到指定帧", "SetFrame", "跳到指定帧", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2,m_media_arg + 11},
		Fn_media_SetFrame,
		"Fn_media_SetFrame" };

EXTERN_C void Fn_media_IsOpen(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->IsOpen();
}
FucInfo Media_IsOpen = { {
		"是否已打开", "IsOpen", "判断是否已打开", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_IsOpen,
		"Fn_media_IsOpen" };


namespace elibstl {


	LIB_DATA_TYPE_INFO media_play_ex =
	{
		"媒体播放Ex",
		"MediaPlayEx",
		"本对象提供对媒体播放的支持，注意：本对象是架构在Windows MCI基础之上的，本对象提供了\"取别名\"方法，您可以通过该方法所得的文本，通过Windows API mciSendString等命令和本对象一起控制MCI播放。如果有媒体文件不能播放，请安装相应解码器。",
		sizeof(s_dtCmdIndexcommobj_media_play) / sizeof(s_dtCmdIndexcommobj_media_play[0]),
		s_dtCmdIndexcommobj_media_play,
		_DT_OS(__OS_WIN),
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		sizeof(s_dt_const_media_play) / sizeof(s_dt_const_media_play[0]),
		s_dt_const_media_play
	};
}