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
//�ҵ�ý�岥����
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
	//��ȡ��ǰ�Ĳ���״̬��Ϊ���³���ֵ֮һ��0��#δ֪״̬��1��#����״̬��2��#ֹͣ״̬��3��#��ͣ״̬��������Ϊ���������Ա���* | **| *
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
	//��λ����
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
	//����Ϊ0-100
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
	//����Ϊ0-100
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
	//���س�������"����_"��ͷ�ĳ���ֵ��ʧ�ܷ���0
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
	//����λ�ñ���С��ý�峤�ȣ�������ܻ��������ʧ�ܡ���λ������
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
	//��������ý�嶼֧���ٶȵ���,1��2000֮���������ԭʼ�ٶ�Ϊ1000��2000Ϊԭʼ�ٶȵ�2����500Ϊԭʼ�ٶȵ�һ�롣����:�������ٶȽ�����ý�忴�����Ѿ�ֹͣ��
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
	//ִ�гɹ�����0�����򷵻ط����������˵����ִ�к��ʵ��������������2�����������õ���ϵͳ������ֵ
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
	/*000*/ {DATA_TYPE::SDT_INT, 0, "������", "AUDIO_CHANNEL_LEFT", NULL, LES_HAS_DEFAULT_VALUE, (INT)1},
	/*001*/ {DATA_TYPE::SDT_INT, 0, "������", "AUDIO_CHANNEL_RIGHT", NULL, LES_HAS_DEFAULT_VALUE, (INT)2},
	/*002*/ {DATA_TYPE::SDT_INT, 0, "������", "AUDIO_CHANNEL_STEREO", NULL, LES_HAS_DEFAULT_VALUE, (INT)3},
	/*003*/ {DATA_TYPE::SDT_INT, 0, "����", "AUDIO_CHANNEL_AVERAGE", NULL, LES_HAS_DEFAULT_VALUE, (INT)4},
};



//����
EXTERN_C void Fn_media_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	self = new eMideaPlay;
}
//����
FucInfo Media_structure = { {
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
	} ,Fn_media_structure ,"Fn_media_structure" };

//����
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
		/*ret*/ DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,fn_media_copy ,"fn_media_copy" };

//����
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
		/*ret*/ DATA_TYPE::_SDT_NULL,
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
		/*name*/    "�ļ���",
		/*explain*/ ("�ò���ΪҪ�򿪵�ý���ļ��������Ƕ���������."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "���ھ��",
		/*explain*/ ("������Ƶ�ļ����贰�ڣ�Ĭ��Ϊ��ǰ����ڣ������������Ϊ��Ƶʱ��ָ�����ھ�����ܻᵼ��ʧ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{"���ھ��", "Ҫ���õĴ��ھ��", 0, 0, DATA_TYPE::SDT_INT, 0, NULL},
	{"����λ��", "�ò���Ϊ����λ�ã��Ժ���Ϊ��λ��Ĭ��Ϊ-1����ʾ�ӵ�ǰ������", 0, 0, DATA_TYPE::SDT_INT, -1, AS_HAS_DEFAULT_VALUE},
	{"����������", "��ΧΪ0-100��0Ϊ������100Ϊ��������������������ʡ�Ի򳬳���Χ�����޸Ĵ�����������", 0, 0, DATA_TYPE::SDT_SHORT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"����������", "��ΧΪ0-100��0Ϊ������100Ϊ��������������������ʡ�Ի򳬳���Χ�����޸Ĵ�����������", 0, 0, DATA_TYPE::SDT_SHORT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"����������", "�ṩ��������ʱֻ���ṩ��������ΧΪ0-100��0Ϊ������100Ϊ��������������������ʡ�ԣ��򲻷��ش�����������", 0, 0, DATA_TYPE::SDT_SHORT, 0, AS_RECEIVE_VAR},
	{"����������", "�ṩ��������ʱֻ���ṩ��������ΧΪ0-100��0Ϊ������100Ϊ��������������������ʡ�ԣ��򲻷��ش�����������", 0, 0, DATA_TYPE::SDT_SHORT, 0, AS_RECEIVE_VAR},
	{"��������", "�������ͳ���1.������,2.������3.������4.����", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"ý������", "������ý�������Ĵ�С", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�����ٶ�", "��������ý�嶼֧���ٶȵ���,1��2000֮���������ԭʼ�ٶ�Ϊ1000��2000Ϊԭʼ�ٶȵ�2����500Ϊԭʼ�ٶȵ�һ�롣����:�������ٶȽ�����ý�忴�����Ѿ�ֹͣ��", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�Ƿ���������", "Ĭ��Ϊ��", 0, 0, DATA_TYPE::SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};
EXTERN_C void Fn_media_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto hWnd = elibstl::args_to_data<INT>(pArgInf, 2);
	pRetData->m_bool = self->Open(wstring(elibstl::args_to_wsdata(pArgInf, 1)), hWnd.has_value() ? IsWindow(reinterpret_cast<HWND>(hWnd.value())) ? reinterpret_cast<HWND>(hWnd.value()) : GetActiveWindow() : GetActiveWindow());
}

FucInfo Media_open = { {
		/*ccname*/  ("��"),
		/*egname*/  ("open"),
		/*explain*/ ("��ָ��ý���ļ����ɹ������棬ʧ�ܷ��ؼ١�����Ѿ�����ֱ�ӷ����棬��Ҫ���´��ļ�,��ر��Ժ��ٴδ����ļ���"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
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
		"�Ƿ���Ƶ", "IsVideo", "�жϵ�ǰ���ŵ������Ƿ�����Ƶ������Ƿ����棬���򷵻ؼ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0
	} ,Fn_media_IsVideo ,"Fn_media_IsVideo" };


EXTERN_C void Fn_media_GetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = reinterpret_cast<int>(self->GetHwnd());
}
FucInfo Media_GetHwnd = { {
		"ȡ���", "GetHwnd", "��ȡ��ǰ��Ƶ���Ŵ��ڵ�Windows ���ھ��", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0
} ,Fn_media_GetHwnd ,"Fn_media_GetHwnd" };


EXTERN_C void Fn_media_SetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetHwnd(reinterpret_cast<HWND>(pArgInf[1].m_int));
}
FucInfo Media_SetHwnd = { {
		"�þ��", "SetHwnd", "���õ�ǰ��Ƶ���Ŵ��ڵ�Windows ���ھ�����ɹ������棬ʧ�ܷ��ؼ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 2} ,
		Fn_media_SetHwnd ,
		"Fn_media_SetHwnd" };
EXTERN_C void Fn_media_GetMode(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetMode();
}
FucInfo Media_GetMode = { {
		 "ȡ״̬", "GetMode", "��ȡ��ǰ�Ĳ���״̬��Ϊ���³���ֵ֮һ��0��#δ֪״̬��1��#����״̬��2��#ֹͣ״̬��3��#��ͣ״̬", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMode ,
		"Fn_media_GetMode" };

EXTERN_C void Fn_media_GetLength(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetLength();
}
FucInfo Media_GetLength = { {
		"ȡ����", "GetLength", "��ȡ��ǰý���ļ��ĳ���", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetLength ,
		"Fn_media_GetLength" };

EXTERN_C void Fn_media_GetPosition(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int64 = self->GetPosition();
}
FucInfo Media_GetPosition = { {
		"ȡλ��","GetPosition", "��ȡ��ǰ�Ĳ���λ��", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetPosition ,
		"Fn_media_GetPosition" };

EXTERN_C void Fn_media_GetTotalSec(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetTotalSec();
}
FucInfo Media_GetTotalSec = { {
		"ȡ��ʱ��", "GetTotalSec", "����Ϊ��λ��ȡ�ܲ���ʱ��", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_GetTotalSec ,
		"Fn_media_GetTotalSec" };

EXTERN_C void Fn_media_GetFrameRate(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetFrameRate();
}
FucInfo Media_GetFrameRate = { {
		 "ȡ����", "GetFrameRate", "��ȡÿһ֡�ı���", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetFrameRate ,
		"Fn_media_GetFrameRate" };

EXTERN_C void Fn_media_Play(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto pos = elibstl::args_to_data<INT>(pArgInf, 1);
	pRetData->m_int = self->Play(pos.has_value() ? pos.value() : -1);
}
FucInfo Media_Play = { {
		"����", "Play", "��ָ��λ�ÿ�ʼ���š��ɹ������棬ʧ�ܷ��ؼ�,���Ŵ���Ϊ�򿪻����þ����ָ���Ĵ���", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 3}
		,Fn_media_Play,
		"Fn_media_Play" };


EXTERN_C void Fn_media_Pause(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->Pause();
}
FucInfo Media_Pause = { {
		"��ͣ", "Pause", "��ͣ���š��ɹ������棬ʧ�ܷ��ؼ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_Pause,
		"Fn_media_Pause" };


EXTERN_C void Fn_media_Stop(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->Stop();
}
FucInfo Media_Stop = { {
		"ֹͣ","Stop", "ֹͣ���š��ɹ������棬ʧ�ܷ��ؼ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_Stop,
		"Fn_media_Stop" };

EXTERN_C void Fn_media_GetMCIAlias(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_pBin = elibstl::clone_textw(self->GetMCIAlias());
}
FucInfo Media_GetMCIAlias = { {
		"ȡ����", "GetMCIAlias", "��ȡ��ǰ����ʹ�õ�MCI����", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BIN, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMCIAlias,
		"Fn_media_GetMCIAlias" };


EXTERN_C void Fn_media_Close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->Close();
}
FucInfo Media_Close = { {
		"�ر�", "Close", "�رյ�ǰ���ŵ�ý�塣�رպ��޷��ٶ�������κβ���,�ɹ������棬ʧ�ܷ��ؼ١�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
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
		"������", "SetVolume", " ���õ�ǰ����ý�����������Ӱ��ϵͳ����������������ֻҪ��һ������ʧ�ܣ��ͻ᷵�ؼ١�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, m_media_arg + 4},
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
		"ȡ����", "GetVolume", "��ȡ��ǰ������������ϵͳ������������������ֻҪ��һ����ȡʧ�ܣ��ͻ᷵�ؼ١�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, m_media_arg + 6},
		Fn_media_GetVolume,
		"Fn_media_GetVolume" };


EXTERN_C void Fn_media_continue(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->Continue();
}
FucInfo Media_continue = { {
		"����", "continue", "��������ͣλ�ò���", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_continue,
		"Fn_media_continue" };


EXTERN_C void Fn_media_GetChannel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->GetChannel();
}
FucInfo Media_GetChannel = { {
		"ȡý������", "GetChannel", "���س����е��������͡�ʧ�ܷ���0", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetChannel,
		"Fn_media_GetChannel" };


EXTERN_C void Fn_media_SetChannel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetChannel(pArgInf[1].m_int);
}
FucInfo Media_SetChannel = { {
		"��ý������", "SetChannel", "����ý����������", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, m_media_arg + 8},
		Fn_media_SetChannel,
		"Fn_media_SetChannel" };


EXTERN_C void Fn_media_GetFrames(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetFrames();
}
FucInfo Media_GetFrames = { {
		"ȡ֡��", "GetFrames", "ȡý���ļ���֡��", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetFrames,
		"Fn_media_GetFrames" };


EXTERN_C void Fn_media_GetMediaVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetMediaVolume();
}
FucInfo Media_GetMediaVolume = { {
		"ȡý������", "GetMediaVolume", "ȡ�򿪵�ý���ļ�������", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0},
		Fn_media_GetMediaVolume,
		"Fn_media_GetMediaVolume" };


EXTERN_C void Fn_media_SetMediaVolume(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetMediaVolume(pArgInf[1].m_int);
}
FucInfo Media_SetMediaVolume = { {
		"��ý������", "SetMediaVolume", "ִ�к��ʵ��������������2�����������õ���ϵͳ������ֵ", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1,m_media_arg + 9},
		Fn_media_SetMediaVolume,
		"Fn_media_SetMediaVolume" };

EXTERN_C void Fn_media_SetPlaySpeed(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->SetPlaySpeed(pArgInf[1].m_int);
}
FucInfo Media_SetPlaySpeed = { {
		"�ò����ٶ�", "SetPlaySpeed", "���õ�ǰý��Ĳ����ٶȡ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1,m_media_arg + 10},
		Fn_media_SetPlaySpeed,
		"Fn_media_SetPlaySpeed" };


EXTERN_C void Fn_media_GetPlaySpeed(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_int = self->GetPlaySpeed();
}
FucInfo Media_GetPlaySpeed = { {
		"ȡ�����ٶ�", "GetPlaySpeed", "��ȡ��ǰý��Ĳ����ٶȡ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_INT, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_GetPlaySpeed,
		"Fn_media_GetPlaySpeed" };

EXTERN_C void Fn_media_SetPos(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto is_now = elibstl::args_to_data<SHORT*>(pArgInf, 2);
	pRetData->m_bool = self->SetPos(pArgInf[1].m_int, is_now.has_value() ? is_now.value() : false);
}
FucInfo Media_SetPos = { {
		"��λ��", "SetPos", "����ý�嵱ǰ���ŵ�λ��", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2,m_media_arg + 11},
		Fn_media_SetPos,
		"Fn_media_SetPos" };

EXTERN_C void Fn_media_SetFrame(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	auto is_now = elibstl::args_to_data<SHORT*>(pArgInf, 2);
	pRetData->m_bool = self->SetFrame(pArgInf[1].m_int, is_now.has_value() ? is_now.value() : false);
}
FucInfo Media_SetFrame = { {
		"����ָ��֡", "SetFrame", "����ָ��֡", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2,m_media_arg + 11},
		Fn_media_SetFrame,
		"Fn_media_SetFrame" };

EXTERN_C void Fn_media_IsOpen(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::args_to_obj<eMideaPlay>(pArgInf);
	pRetData->m_bool = self->IsOpen();
}
FucInfo Media_IsOpen = { {
		"�Ƿ��Ѵ�", "IsOpen", "�ж��Ƿ��Ѵ�", -1, _CMD_OS(__OS_WIN), DATA_TYPE::SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0,0},
		Fn_media_IsOpen,
		"Fn_media_IsOpen" };


namespace elibstl {


	LIB_DATA_TYPE_INFO media_play_ex =
	{
		"ý�岥��Ex",
		"MediaPlayEx",
		"�������ṩ��ý�岥�ŵ�֧�֣�ע�⣺�������Ǽܹ���Windows MCI����֮�ϵģ��������ṩ��\"ȡ����\"������������ͨ���÷������õ��ı���ͨ��Windows API mciSendString������ͱ�����һ�����MCI���š������ý���ļ����ܲ��ţ��밲װ��Ӧ��������",
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