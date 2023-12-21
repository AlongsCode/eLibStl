#define NOMINMAX 
#include"ElibHelp.h"
#include"qrencode\qrencode.h"




namespace {

	void QRcode2Bmp(const QRcode* qrCode, elibstl::CFBitMap& bmp, INT backgroundColor, INT pixelColor, INT nZoom)
	{

		if (!qrCode) return;
		nZoom = std::max(1, nZoom);
		const INT qrWidth = (qrCode->width > 0 ? qrCode->width : 1);
		bmp.CreateBitmap(qrWidth * nZoom, qrWidth * nZoom, 24);
		bmp.FillBG(backgroundColor);    //白色底图
		for (int y = 0; y < qrWidth; y++)
		{
			for (int x = 0; x < qrWidth; x++)
			{
				unsigned char b = qrCode->data[y * qrWidth + x];
				if (b & 0x01)    //深色,反之留底色
				{
					for (int x2 = 0; x2 < nZoom; x2++)
						for (int y2 = 0; y2 < nZoom; y2++)
							bmp.SetPixel(x * nZoom + x2, y * nZoom + y2, pixelColor);
				}
			}
		}
	}


}




static ARG_INFO Args[] =
{
		{
			"内容",
			"二维码所包含的文本内容.会自动将宽字符识别为字节集",
			0,
			0,
			_SDT_ALL,
			0,
			ArgMark::AS_NONE,
		},
		{
				"等级",
				"提供所欲使用的生成等级,1-40之间,值越大像素点越多,能表示的内容越多",
				0,
				0,
				SDT_INT,
				10,
				ArgMark::AS_HAS_DEFAULT_VALUE ,
		},{
			"容错",
			"提供所生成二维码的容错等级,0-3之间.",
			0,
			0,
			SDT_INT,
			3,
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"底色",
			"提供所生成二维码图像的底图颜色,默认为白色",
			0,
			0,
			SDT_INT,
			RGB(255,255,255),
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"码颜色",
			"提供所生成二维码图像的二维码像素点颜色.",
			0,
			0,
			SDT_INT,
			RGB(0,0,0),
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"放大倍数",
			"提供所生成二维码图像的放大倍数",
			0,
			0,
			SDT_INT,
			1,
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}
};

static ARG_INFO Args2[] =
{
		{
			"数据内容",
			"二维码所包含的数据.",
			0,
			0,
			SDT_BIN,
			0,
			ArgMark::AS_NONE,
		},
		{
				"等级",
				"提供所欲使用的生成等级,1-40之间,值越大像素点越多,能表示的内容越多",
				0,
				0,
				SDT_INT,
				10,
				ArgMark::AS_HAS_DEFAULT_VALUE ,
		},{
			"容错",
			"提供所生成二维码的容错等级,0-3之间.",
			0,
			0,
			SDT_INT,
			3,
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"底色",
			"提供所生成二维码图像的底图颜色,默认为白色",
			0,
			0,
			SDT_INT,
			RGB(255,255,255),
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"码颜色",
			"提供所生成二维码图像的二维码像素点颜色.",
			0,
			0,
			SDT_INT,
			RGB(0,0,0),
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}, {
			"放大倍数",
			"提供所生成二维码图像的放大倍数",
			0,
			0,
			SDT_INT,
			1,
			ArgMark::AS_HAS_DEFAULT_VALUE,
		}
};


EXTERN_C void fn_QRcode_encodeString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
	elibstl::CFBitMap bmp;
	
	auto inData = elibstl::arg_to_wstring(pArgInf, 0);
	auto u8str= elibstl::W2UTF8(inData);
	QRcode* qrCode = QRcode_encodeString(u8str, pArgInf[1].m_int, static_cast<QRecLevel> (pArgInf[2].m_int), QR_MODE_8, 1);
	QRcode2Bmp(qrCode, bmp, pArgInf[3].m_int, pArgInf[4].m_int, pArgInf[5].m_int);
	QRcode_free(qrCode);
	pRetData->m_pBin = elibstl::clone_bin(bmp.GetBitmap<unsigned char>(), bmp.GetBitmapSize());
	delete[]u8str;

}

EXTERN_C void fn_QRcode_encodeData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
	elibstl::CFBitMap bmp;

	auto inData = elibstl::args_to_ebin(pArgInf, 0);
	QRcode* qrCode = QRcode_encodeData(inData->m_size, inData->m_data, pArgInf[1].m_int, static_cast<QRecLevel> (pArgInf[2].m_int));
	QRcode2Bmp(qrCode, bmp, pArgInf[3].m_int, pArgInf[4].m_int, pArgInf[5].m_int);
	QRcode_free(qrCode);
	pRetData->m_pBin = elibstl::clone_bin(bmp.GetBitmap<unsigned char>(), bmp.GetBitmapSize());

}




FucInfo Fn_QRcode_encodeString = { {
		/*ccname*/  ("生成文本二维码"),
		/*egname*/  ("QRcode_encodeString"),
		/*explain*/ ("以指定文本内容生成二维码图像."),
		/*category*/12,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
	ESTLARG(Args)
	} ,ESTLFNAME(fn_QRcode_encodeString)};

FucInfo Fn_QRcode_encodeData = { {
		/*ccname*/  ("生成数据二维码"),
		/*egname*/  ("QRcode_encodeData"),
		/*explain*/ ("以指定数据内容生成二维码图像.."),
		/*category*/12,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
	ESTLARG(Args2)
	} ,ESTLFNAME(fn_QRcode_encodeData) };
