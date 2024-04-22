
#include"ElibHelp.h"

namespace {
	class MD5
	{
		static constexpr unsigned int s11 = 7;
		static constexpr unsigned int s12 = 12;
		static constexpr unsigned int s13 = 17;
		static constexpr unsigned int s14 = 22;
		static constexpr unsigned int s21 = 5;
		static constexpr unsigned int s22 = 9;
		static constexpr unsigned int s23 = 14;
		static constexpr unsigned int s24 = 20;
		static constexpr unsigned int s31 = 4;
		static constexpr unsigned int s32 = 11;
		static constexpr unsigned int s33 = 16;
		static constexpr unsigned int s34 = 23;
		static constexpr unsigned int s41 = 6;
		static constexpr unsigned int s42 = 10;
		static constexpr unsigned int s43 = 15;
		static constexpr unsigned int s44 = 21;

		inline constexpr auto FF(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, const unsigned int& s, const unsigned int& ac)
		{
			(a) += (((b) & (c)) | ((~b) & (d))) + (x)+ac;
			(a) = (((a) << (s)) | ((a) >> (32 - (s))));
			(a) += (b);
		}
		inline void GG(unsigned int& a, const unsigned int& b, const unsigned int& c, const unsigned int& d, const unsigned int& x, const unsigned int& s, const unsigned int& ac)
		{
			(a) += (((b) & (d)) | ((c) & (~d))) + (x)+ac;
			(a) = (((a) << (s)) | ((a) >> (32 - (s))));
			(a) += (b);
		}
		inline void HH(unsigned int& a, const unsigned int& b, unsigned int& c, unsigned int& d, unsigned int& x, const unsigned int& s, const unsigned int& ac)
		{
			(a) += ((b) ^ (c) ^ (d)) + (x)+ac;
			(a) = (((a) << (s)) | ((a) >> (32 - (s))));
			(a) += (b);
		}
		inline void II(unsigned int& a, const unsigned int& b, const unsigned int& c, const unsigned int& d, const unsigned int& x, const unsigned int& s, const unsigned int& ac)
		{
			(a) += ((c) ^ ((b) | (~d))) + (x)+ac;
			(a) = (((a) << (s)) | ((a) >> (32 - (s))));
			(a) += (b);
		}

	public:
		template <typename CharType>
		MD5(const std::basic_string<CharType>& message)
		{
			init(reinterpret_cast<const unsigned char*>(message.c_str()), message.length() * sizeof(CharType));
		};
		template <typename T>
		MD5(const T& data)
		{
			/*if constexpr (__is_container_v<T>())
			{
				init(reinterpret_cast<const unsigned char*>(data.data()), data.size() * sizeof(data.back()));
			}
			else {*/
			init(reinterpret_cast<const unsigned char*>(&data), sizeof(T));
			//}
		};
		MD5(const unsigned char* data, const size_t size)
		{
			init(data, size);
		}
		MD5(const std::vector<unsigned char>& data)
		{

			init(data.data(), data.size());
		}
		const unsigned char* GetMd5()
		{
			if (!finished)
			{
				finished = true;

				unsigned char bits[8];
				unsigned int oldState[4];
				unsigned int oldCount[2];
				unsigned int index, padLen;

				/* Save current state and count. */
				memcpy(oldState, state, 16);
				memcpy(oldCount, count, 8);

				/* Save number of bits */
				encode(count, bits, 8);

				/* Pad out to 56 mod 64. */
				index = (unsigned int)((count[0] >> 3) & 0x3f);
				padLen = (index < 56) ? (56 - index) : (120 - index);
				init(PADDING, padLen);

				/* Append length (before padding) */
				init(bits, 8);

				/* Store state in digest */
				encode(state, digest, 16);

				/* Restore current state and count. */
				memcpy(state, oldState, 16);
				memcpy(count, oldCount, 8);
			}
			return digest;
		}
		template <typename CharType>
		std::basic_string<CharType> GetMd5Str()
		{
			const auto digest_ = GetMd5();
			std::basic_string<CharType> str;
			str.reserve(16 << 1);
			for (size_t i = 0; i < 16; ++i)
			{
				int t = digest_[i];
				int a = t / 16;
				int b = t % 16;
				str.append(1, CharType(HEX_NUMBERS[a]));
				str.append(1, CharType(HEX_NUMBERS[b]));
			}
			return str;
		};

	private:
		void init(const unsigned char* input, size_t len)
		{

			unsigned int i, index, partLen;

			finished = false;

			/* Compute number of unsigned chars mod 64 */
			index = (unsigned int)((count[0] >> 3) & 0x3f);

			/* update number of bits */
			if ((count[0] += ((unsigned int)len << 3)) < ((unsigned int)len << 3))
			{
				++count[1];
			}
			count[1] += ((unsigned int)len >> 29);

			partLen = 64 - index;

			/* transform as many times as possible. */
			if (len >= partLen)
			{

				memcpy(&buffer[index], input, partLen);
				transform(buffer);

				for (i = partLen; i + 63 < len; i += 64)
				{
					transform(&input[i]);
				}
				index = 0;
			}
			else
			{
				i = 0;
			}

			/* Buffer remaining input */
			memcpy(&buffer[index], &input[i], len - i);
		};
		void transform(const unsigned char block[64])
		{

			unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];

			decode(block, x, 64);

			/* Round 1 */
			FF(a, b, c, d, x[0], s11, 0xd76aa478);
			FF(d, a, b, c, x[1], s12, 0xe8c7b756);
			FF(c, d, a, b, x[2], s13, 0x242070db);
			FF(b, c, d, a, x[3], s14, 0xc1bdceee);
			FF(a, b, c, d, x[4], s11, 0xf57c0faf);
			FF(d, a, b, c, x[5], s12, 0x4787c62a);
			FF(c, d, a, b, x[6], s13, 0xa8304613);
			FF(b, c, d, a, x[7], s14, 0xfd469501);
			FF(a, b, c, d, x[8], s11, 0x698098d8);
			FF(d, a, b, c, x[9], s12, 0x8b44f7af);
			FF(c, d, a, b, x[10], s13, 0xffff5bb1);
			FF(b, c, d, a, x[11], s14, 0x895cd7be);
			FF(a, b, c, d, x[12], s11, 0x6b901122);
			FF(d, a, b, c, x[13], s12, 0xfd987193);
			FF(c, d, a, b, x[14], s13, 0xa679438e);
			FF(b, c, d, a, x[15], s14, 0x49b40821);

			/* Round 2 */
			GG(a, b, c, d, x[1], s21, 0xf61e2562);
			GG(d, a, b, c, x[6], s22, 0xc040b340);
			GG(c, d, a, b, x[11], s23, 0x265e5a51);
			GG(b, c, d, a, x[0], s24, 0xe9b6c7aa);
			GG(a, b, c, d, x[5], s21, 0xd62f105d);
			GG(d, a, b, c, x[10], s22, 0x2441453);
			GG(c, d, a, b, x[15], s23, 0xd8a1e681);
			GG(b, c, d, a, x[4], s24, 0xe7d3fbc8);
			GG(a, b, c, d, x[9], s21, 0x21e1cde6);
			GG(d, a, b, c, x[14], s22, 0xc33707d6);
			GG(c, d, a, b, x[3], s23, 0xf4d50d87);
			GG(b, c, d, a, x[8], s24, 0x455a14ed);
			GG(a, b, c, d, x[13], s21, 0xa9e3e905);
			GG(d, a, b, c, x[2], s22, 0xfcefa3f8);
			GG(c, d, a, b, x[7], s23, 0x676f02d9);
			GG(b, c, d, a, x[12], s24, 0x8d2a4c8a);

			/* Round 3 */
			HH(a, b, c, d, x[5], s31, 0xfffa3942);
			HH(d, a, b, c, x[8], s32, 0x8771f681);
			HH(c, d, a, b, x[11], s33, 0x6d9d6122);
			HH(b, c, d, a, x[14], s34, 0xfde5380c);
			HH(a, b, c, d, x[1], s31, 0xa4beea44);
			HH(d, a, b, c, x[4], s32, 0x4bdecfa9);
			HH(c, d, a, b, x[7], s33, 0xf6bb4b60);
			HH(b, c, d, a, x[10], s34, 0xbebfbc70);
			HH(a, b, c, d, x[13], s31, 0x289b7ec6);
			HH(d, a, b, c, x[0], s32, 0xeaa127fa);
			HH(c, d, a, b, x[3], s33, 0xd4ef3085);
			HH(b, c, d, a, x[6], s34, 0x4881d05);
			HH(a, b, c, d, x[9], s31, 0xd9d4d039);
			HH(d, a, b, c, x[12], s32, 0xe6db99e5);
			HH(c, d, a, b, x[15], s33, 0x1fa27cf8);
			HH(b, c, d, a, x[2], s34, 0xc4ac5665);

			/* Round 4 */
			II(a, b, c, d, x[0], s41, 0xf4292244);
			II(d, a, b, c, x[7], s42, 0x432aff97);
			II(c, d, a, b, x[14], s43, 0xab9423a7);
			II(b, c, d, a, x[5], s44, 0xfc93a039);
			II(a, b, c, d, x[12], s41, 0x655b59c3);
			II(d, a, b, c, x[3], s42, 0x8f0ccc92);
			II(c, d, a, b, x[10], s43, 0xffeff47d);
			II(b, c, d, a, x[1], s44, 0x85845dd1);
			II(a, b, c, d, x[8], s41, 0x6fa87e4f);
			II(d, a, b, c, x[15], s42, 0xfe2ce6e0);
			II(c, d, a, b, x[6], s43, 0xa3014314);
			II(b, c, d, a, x[13], s44, 0x4e0811a1);
			II(a, b, c, d, x[4], s41, 0xf7537e82);
			II(d, a, b, c, x[11], s42, 0xbd3af235);
			II(c, d, a, b, x[2], s43, 0x2ad7d2bb);
			II(b, c, d, a, x[9], s44, 0xeb86d391);

			state[0] += a;
			state[1] += b;
			state[2] += c;
			state[3] += d;
		};
		void encode(const unsigned int* input, unsigned char* output, size_t length)
		{

			for (size_t i = 0, j = 0; j < length; ++i, j += 4)
			{
				output[j] = (unsigned char)(input[i] & 0xff);
				output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
				output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
				output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
			}
		};
		void decode(const unsigned char* input, unsigned int* output, size_t length)
		{
			for (size_t i = 0, j = 0; j < length; ++i, j += 4)
			{
				output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j + 1]) << 8) |
					(((unsigned int)input[j + 2]) << 16) | (((unsigned int)input[j + 3]) << 24);
			}
		};

	private:
		bool finished{ false };
		unsigned int state[4]{
			0x67452301,
			0xefcdab89,
			0x98badcfe,
			0x10325476,
		};
		unsigned int count[2]{ 0 };
		unsigned char buffer[64];
		unsigned char digest[16];
		static constexpr unsigned char PADDING[64]{ 0x80 };
		static constexpr char
			HEX_NUMBERS[16]{
				'0', '1', '2', '3',
				'4', '5', '6', '7',
				'8', '9', 'a', 'b',
				'c', 'd', 'e', 'f' };
	};
	/*易语言加密文件Md5加密方式*/
	std::string NewGetMD5(const unsigned char* pBuf, size_t nLength) {
		// 获取MD5哈希
		std::string md5Hash = MD5(pBuf, nLength).GetMd5Str<char>();
		for (size_t i = 0; i < md5Hash.size(); i += 2) {
			std::swap(md5Hash[i], md5Hash[i + 1]);
		}
		std::reverse(md5Hash.begin(), md5Hash.end());
		return md5Hash;
	}
}


EXTERN_C void fn_eStl_GetMd5(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_ebin(pArgInf, 0);
	MD5 ret(data->m_data, data->m_size);
	pRetData->m_pText = elibstl::clone_text(ret.GetMd5Str<char>());
}
EXTERN_C void fn_eStl_GetMd5W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto data = elibstl::args_to_ebin(pArgInf, 0);
	MD5 ret(data->m_data, data->m_size);
	pRetData->m_pBin = elibstl::clone_textw(ret.GetMd5Str<wchar_t>());
}

static ARG_INFO Args[] =
{
	{
		/*name*/    "数据",
		/*explain*/ ("欲获取MD5的数据"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE
	}
};
FucInfo Fn_eStl_GetMd5W = { {
		/*ccname*/  ("取数据摘要W"),
		/*egname*/  ("get_md5_str"),
		/*explain*/ ("返回一段字节集数据的MD5数据摘要编码文本。不同数据的MD5码都不一样，因此本命令可以用作保证重要数据不会被篡改。"),
		/*category*/17,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
	ESTLARG(Args)
	} ,ESTLFNAME(fn_eStl_GetMd5W)};

FucInfo Fn_eStl_GetMd5A = { {
		/*ccname*/  ("取数据摘要A"),
		/*egname*/  ("get_md5_str"),
		/*explain*/ ("返回一段字节集数据的MD5数据摘要编码文本。不同数据的MD5码都不一样，因此本命令可以用作保证重要数据不会被篡改。"),
		/*category*/17,
		/*state*/	CT_IS_HIDED,
		/*ret*/     DATA_TYPE::SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
	ESTLARG(Args)
	} ,ESTLFNAME(fn_eStl_GetMd5) };

