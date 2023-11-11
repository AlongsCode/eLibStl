#ifndef ELIBSTL_PINYIN
#define ELIBSTL_PINYIN
#include <iostream>
#include <string>
namespace elibstl::eplpinyin{
constexpr auto MIN_CN_CHAR_UNICODE_VALUE = 0x4E00;// 最小处理汉字Unicode编码
constexpr auto MAX_CN_CHAR_UNICODE_VALUE = 0x9FA5;// 最大处理汉字Unicode编码
/*声母枚举值*/
enum class pysm :std::uint8_t
{
	nop,
	b,
	c,
	d,
	f,
	g,
	h,
	j,
	k,
	l,
	m,
	n,
	p,
	q,
	r,
	s,
	t,
	w,
	x,
	y,
	z,
	ch,
	sh,
	zh
};
/*韵母枚举值*/
enum class pyym :std::uint8_t {
	nop,
	a,
	ai,
	an,
	ang,
	ao,
	e,
	ei,
	en,
	eng,
	er,
	g,
	i,
	ia,
	ian,
	iang,
	iao,
	ie,
	in,
	ing,
	iong,
	iu,
	m,
	n,
	ng,
	o,
	ong,
	ou,
	u,
	ua,
	uai,
	uan,
	uang,
	ue,
	ui,
	un,
	uo,
	v,
	ve,
	ê
};
/*拼音结构体*/
struct PinYin
{
	pysm sm;/*声母*/
	pyym ym;/*韵母*/
};
/*汉字拼音数据*/
struct HanZiInfo
{
	uint8_t MultiCount;/*多音字数量最大为11*/
	uint16_t MultiIndex;/*多音字表中索引*/
	PinYin MultiTone;
};
/*圣母表对照*/
constexpr static const wchar_t* PinYinSm[] = {
		L"",L"b",L"c",L"d",L"f",L"g",L"h",L"j",L"k",L"l",L"m",L"n",L"p",L"q",L"r",L"s",L"t",L"w",L"x",L"y",L"z",L"ch",L"sh",L"zh"
};
constexpr inline static const auto&	GetPinyinSm(pysm sm) {
	return PinYinSm[static_cast<std::uint8_t>(sm)];
}
/*韵母表对照*/
constexpr static const wchar_t* PinYinYm[] = {
	L"",	L"a",	L"ai",	L"an",	L"ang",	L"ao",	L"e",	L"ei",	L"en",	L"eng",	L"er",	L"g",	L"i",	L"ia",	L"ian",	L"iang",	L"iao",	L"ie",	L"in",	L"ing",	L"iong",	L"iu",L"m",L"n",	L"ng",	L"o",	L"ong",	L"ou",	L"u",	L"ua",	L"uai",	L"uan",	L"uang",	L"ue",	L"ui",	L"un",	L"uo",	L"v",	L"ve",	L"ê"
};
constexpr inline static const auto& GetPinyinYm(pyym ym) {
	return PinYinYm[static_cast<std::uint8_t>(ym)];
}

using PinYin2 = PinYin[2];
using PinYin3 = PinYin[3];
using PinYin4 = PinYin[4];
using PinYin5 = PinYin[5];
using PinYin6 = PinYin[6];
using PinYin7 = PinYin[7];
using PinYin8 = PinYin[8];
using PinYin9 = PinYin[9];

/****************************************
以下为码表,想要压缩可以使用位域,为了可读性
*****************************************/
constexpr static HanZiInfo all_pinyin[] = { 
{1,0,{pysm::y,pyym::i}},//一 yi
{2,0,{pysm::nop,pyym::nop}},//丁 ding
{3,0,{pysm::nop,pyym::nop}},//丂 kao
{1,0,{pysm::q,pyym::i}},//七 qi
{1,0,{pysm::sh,pyym::ang}},//丄 shang
{1,0,{pysm::x,pyym::ia}},//丅 xia
{1,0,{pysm::h,pyym::an}},//丆 han
{2,1,{pysm::nop,pyym::nop}},//万 wan
{1,0,{pysm::zh,pyym::ang}},//丈 zhang
{1,0,{pysm::s,pyym::an}},//三 san
{1,0,{pysm::sh,pyym::ang}},//上 shang
{1,0,{pysm::x,pyym::ia}},//下 xia
{2,2,{pysm::nop,pyym::nop}},//丌 ji
{3,1,{pysm::nop,pyym::nop}},//不 bu
{1,0,{pysm::y,pyym::u}},//与 yu
{1,0,{pysm::m,pyym::ian}},//丏 mian
{1,0,{pysm::g,pyym::ai}},//丐 gai
{1,0,{pysm::ch,pyym::ou}},//丑 chou
{1,0,{pysm::ch,pyym::ou}},//丒 chou
{1,0,{pysm::zh,pyym::uan}},//专 zhuan
{3,2,{pysm::nop,pyym::nop}},//且 qie
{1,0,{pysm::p,pyym::i}},//丕 pi
{1,0,{pysm::sh,pyym::i}},//世 shi
{1,0,{pysm::sh,pyym::i}},//丗 shi
{1,0,{pysm::q,pyym::iu}},//丘 qiu
{1,0,{pysm::b,pyym::ing}},//丙 bing
{1,0,{pysm::y,pyym::e}},//业 ye
{1,0,{pysm::c,pyym::ong}},//丛 cong
{1,0,{pysm::d,pyym::ong}},//东 dong
{1,0,{pysm::s,pyym::i}},//丝 si
{3,3,{pysm::nop,pyym::nop}},//丞 cheng
{1,0,{pysm::d,pyym::iu}},//丟 diu
{1,0,{pysm::q,pyym::iu}},//丠 qiu
{1,0,{pysm::l,pyym::iang}},//両 liang
{1,0,{pysm::d,pyym::iu}},//丢 diu
{1,0,{pysm::y,pyym::ou}},//丣 you
{1,0,{pysm::l,pyym::iang}},//两 liang
{1,0,{pysm::y,pyym::an}},//严 yan
{3,4,{pysm::nop,pyym::nop}},//並 bing
{1,0,{pysm::s,pyym::ang}},//丧 sang
{1,0,{pysm::g,pyym::un}},//丨 gun
{1,0,{pysm::j,pyym::iu}},//丩 jiu
{2,3,{pysm::nop,pyym::nop}},//个 ge
{1,0,{pysm::y,pyym::a}},//丫 ya
{1,0,{pysm::q,pyym::iang}},//丬 qiang
{1,0,{pysm::zh,pyym::ong}},//中 zhong
{1,0,{pysm::j,pyym::i}},//丮 ji
{1,0,{pysm::j,pyym::ie}},//丯 jie
{1,0,{pysm::f,pyym::eng}},//丰 feng
{2,4,{pysm::nop,pyym::nop}},//丱 guan
{3,5,{pysm::nop,pyym::nop}},//串 chuan
{2,5,{pysm::nop,pyym::nop}},//丳 chan
{1,0,{pysm::l,pyym::in}},//临 lin
{1,0,{pysm::zh,pyym::uo}},//丵 zhuo
{1,0,{pysm::zh,pyym::u}},//丶 zhu
{1,0,{pysm::b,pyym::a}},//丷 ba
{1,0,{pysm::w,pyym::an}},//丸 wan
{1,0,{pysm::d,pyym::an}},//丹 dan
{1,0,{pysm::w,pyym::ei}},//为 wei
{1,0,{pysm::zh,pyym::u}},//主 zhu
{2,6,{pysm::nop,pyym::nop}},//丼 jing
{1,0,{pysm::l,pyym::i}},//丽 li
{1,0,{pysm::j,pyym::u}},//举 ju
{2,7,{pysm::nop,pyym::nop}},//丿 pie
{1,0,{pysm::f,pyym::u}},//乀 fu
{2,8,{pysm::nop,pyym::nop}},//乁 yi
{2,9,{pysm::nop,pyym::nop}},//乂 yi
{2,10,{pysm::nop,pyym::nop}},//乃 nai
{1,0,{pysm::w,pyym::u}},//乄 wu
{1,0,{pysm::j,pyym::iu}},//久 jiu
{1,0,{pysm::j,pyym::iu}},//乆 jiu
{2,11,{pysm::nop,pyym::nop}},//乇 tuo
{4,0,{pysm::nop,pyym::nop}},//么 me
{1,0,{pysm::y,pyym::i}},//义 yi
{1,0,{pysm::y,pyym::i}},//乊 yi
{2,12,{pysm::nop,pyym::nop}},//之 zhi
{1,0,{pysm::w,pyym::u}},//乌 wu
{2,13,{pysm::nop,pyym::nop}},//乍 zha
{1,0,{pysm::h,pyym::u}},//乎 hu
{1,0,{pysm::f,pyym::a}},//乏 fa
{2,14,{pysm::nop,pyym::nop}},//乐 le
{3,6,{pysm::nop,pyym::nop}},//乑 yin
{1,0,{pysm::p,pyym::ing}},//乒 ping
{1,0,{pysm::p,pyym::ang}},//乓 pang
{1,0,{pysm::q,pyym::iao}},//乔 qiao
{1,0,{pysm::h,pyym::u}},//乕 hu
{1,0,{pysm::g,pyym::uai}},//乖 guai
{1,0,{pysm::ch,pyym::eng}},//乗 cheng
{2,15,{pysm::nop,pyym::nop}},//乘 cheng
{2,16,{pysm::nop,pyym::nop}},//乙 yi
{1,0,{pysm::y,pyym::in}},//乚 yin
{1,0,{pysm::y,pyym::a}},//乛 ya
{2,17,{pysm::nop,pyym::nop}},//乜 mie
{1,0,{pysm::j,pyym::iu}},//九 jiu
{1,0,{pysm::q,pyym::i}},//乞 qi
{2,18,{pysm::nop,pyym::nop}},//也 ye
{1,0,{pysm::x,pyym::i}},//习 xi
{1,0,{pysm::x,pyym::iang}},//乡 xiang
{1,0,{pysm::g,pyym::ai}},//乢 gai
{1,0,{pysm::j,pyym::iu}},//乣 jiu
{1,0,{pysm::x,pyym::ia}},//乤 xia
{1,0,{pysm::h,pyym::u}},//乥 hu
{1,0,{pysm::sh,pyym::u}},//书 shu
{1,0,{pysm::d,pyym::ou}},//乧 dou
{1,0,{pysm::sh,pyym::i}},//乨 shi
{1,0,{pysm::j,pyym::i}},//乩 ji
{1,0,{pysm::n,pyym::ang}},//乪 nang
{1,0,{pysm::j,pyym::ia}},//乫 jia
{1,0,{pysm::j,pyym::u}},//乬 ju
{1,0,{pysm::sh,pyym::i}},//乭 shi
{1,0,{pysm::m,pyym::ao}},//乮 mao
{1,0,{pysm::h,pyym::u}},//乯 hu
{1,0,{pysm::m,pyym::ai}},//买 mai
{1,0,{pysm::l,pyym::uan}},//乱 luan
{1,0,{pysm::z,pyym::i}},//乲 zi
{1,0,{pysm::r,pyym::u}},//乳 ru
{1,0,{pysm::x,pyym::ue}},//乴 xue
{1,0,{pysm::y,pyym::an}},//乵 yan
{1,0,{pysm::f,pyym::u}},//乶 fu
{1,0,{pysm::sh,pyym::a}},//乷 sha
{1,0,{pysm::n,pyym::a}},//乸 na
{1,0,{pysm::g,pyym::an}},//乹 gan
{1,0,{pysm::s,pyym::uo}},//乺 suo
{1,0,{pysm::y,pyym::u}},//乻 yu
{1,0,{pysm::c,pyym::ui}},//乼 cui
{1,0,{pysm::zh,pyym::e}},//乽 zhe
{2,19,{pysm::nop,pyym::nop}},//乾 qian
{2,20,{pysm::nop,pyym::nop}},//乿 zhi
{1,0,{pysm::g,pyym::ui}},//亀 gui
{1,0,{pysm::g,pyym::an}},//亁 gan
{1,0,{pysm::l,pyym::uan}},//亂 luan
{1,0,{pysm::l,pyym::in}},//亃 lin
{1,0,{pysm::y,pyym::i}},//亄 yi
{1,0,{pysm::j,pyym::ue}},//亅 jue
{2,21,{pysm::nop,pyym::nop}},//了 le
{1,0,{pysm::m,pyym::a}},//亇 ma
{2,22,{pysm::nop,pyym::nop}},//予 yu
{1,0,{pysm::zh,pyym::eng}},//争 zheng
{1,0,{pysm::sh,pyym::i}},//亊 shi
{2,23,{pysm::nop,pyym::nop}},//事 shi
{1,0,{pysm::nop,pyym::er}},//二 er
{1,0,{pysm::ch,pyym::u}},//亍 chu
{3,7,{pysm::nop,pyym::nop}},//于 yu
{2,24,{pysm::nop,pyym::nop}},//亏 kui
{1,0,{pysm::y,pyym::u}},//亐 yu
{1,0,{pysm::y,pyym::un}},//云 yun
{1,0,{pysm::h,pyym::u}},//互 hu
{1,0,{pysm::q,pyym::i}},//亓 qi
{1,0,{pysm::w,pyym::u}},//五 wu
{1,0,{pysm::j,pyym::ing}},//井 jing
{1,0,{pysm::s,pyym::i}},//亖 si
{1,0,{pysm::s,pyym::ui}},//亗 sui
{3,8,{pysm::nop,pyym::nop}},//亘 gen
{2,25,{pysm::nop,pyym::nop}},//亙 gen
{1,0,{pysm::y,pyym::a}},//亚 ya
{2,26,{pysm::nop,pyym::nop}},//些 xie
{1,0,{pysm::y,pyym::a}},//亜 ya
{2,27,{pysm::nop,pyym::nop}},//亝 qi
{2,28,{pysm::nop,pyym::nop}},//亞 ya
{2,29,{pysm::nop,pyym::nop}},//亟 ji
{1,0,{pysm::t,pyym::ou}},//亠 tou
{2,30,{pysm::nop,pyym::nop}},//亡 wang
{3,9,{pysm::nop,pyym::nop}},//亢 kang
{1,0,{pysm::d,pyym::a}},//亣 da
{1,0,{pysm::j,pyym::iao}},//交 jiao
{2,31,{pysm::nop,pyym::nop}},//亥 hai
{1,0,{pysm::y,pyym::i}},//亦 yi
{1,0,{pysm::ch,pyym::an}},//产 chan
{3,10,{pysm::nop,pyym::nop}},//亨 heng
{1,0,{pysm::m,pyym::u}},//亩 mu
{1,0,{pysm::y,pyym::e}},//亪 ye
{1,0,{pysm::x,pyym::iang}},//享 xiang
{1,0,{pysm::j,pyym::ing}},//京 jing
{1,0,{pysm::t,pyym::ing}},//亭 ting
{1,0,{pysm::l,pyym::iang}},//亮 liang
{1,0,{pysm::x,pyym::iang}},//亯 xiang
{1,0,{pysm::j,pyym::ing}},//亰 jing
{1,0,{pysm::y,pyym::e}},//亱 ye
{2,32,{pysm::nop,pyym::nop}},//亲 qin
{1,0,{pysm::b,pyym::o}},//亳 bo
{1,0,{pysm::y,pyym::ou}},//亴 you
{1,0,{pysm::x,pyym::ie}},//亵 xie
{3,11,{pysm::nop,pyym::nop}},//亶 dan
{1,0,{pysm::l,pyym::ian}},//亷 lian
{1,0,{pysm::d,pyym::uo}},//亸 duo
{2,33,{pysm::nop,pyym::nop}},//亹 wei
{1,0,{pysm::r,pyym::en}},//人 ren
{1,0,{pysm::r,pyym::en}},//亻 ren
{1,0,{pysm::j,pyym::i}},//亼 ji
{1,0,{pysm::j,pyym::i}},//亽 ji
{1,0,{pysm::w,pyym::ang}},//亾 wang
{1,0,{pysm::y,pyym::i}},//亿 yi
{2,34,{pysm::nop,pyym::nop}},//什 shen
{1,0,{pysm::r,pyym::en}},//仁 ren
{2,35,{pysm::nop,pyym::nop}},//仂 le
{1,0,{pysm::d,pyym::ing}},//仃 ding
{1,0,{pysm::z,pyym::e}},//仄 ze
{3,12,{pysm::nop,pyym::nop}},//仅 jin
{1,0,{pysm::p,pyym::u}},//仆 pu
{3,13,{pysm::nop,pyym::nop}},//仇 chou
{1,0,{pysm::b,pyym::a}},//仈 ba
{1,0,{pysm::zh,pyym::ang}},//仉 zhang
{1,0,{pysm::j,pyym::in}},//今 jin
{2,36,{pysm::nop,pyym::nop}},//介 jie
{1,0,{pysm::b,pyym::ing}},//仌 bing
{1,0,{pysm::r,pyym::eng}},//仍 reng
{2,37,{pysm::nop,pyym::nop}},//从 cong
{1,0,{pysm::f,pyym::o}},//仏 fo
{1,0,{pysm::s,pyym::an}},//仐 san
{1,0,{pysm::l,pyym::un}},//仑 lun
{1,0,{pysm::b,pyym::ing}},//仒 bing
{1,0,{pysm::c,pyym::ang}},//仓 cang
{2,38,{pysm::nop,pyym::nop}},//仔 zai
{1,0,{pysm::sh,pyym::i}},//仕 shi
{2,39,{pysm::nop,pyym::nop}},//他 ta
{1,0,{pysm::zh,pyym::ang}},//仗 zhang
{1,0,{pysm::f,pyym::u}},//付 fu
{1,0,{pysm::x,pyym::ian}},//仙 xian
{1,0,{pysm::x,pyym::ian}},//仚 xian
{4,1,{pysm::nop,pyym::nop}},//仛 tuo
{1,0,{pysm::h,pyym::ong}},//仜 hong
{1,0,{pysm::t,pyym::ong}},//仝 tong
{1,0,{pysm::r,pyym::en}},//仞 ren
{1,0,{pysm::q,pyym::ian}},//仟 qian
{2,40,{pysm::nop,pyym::nop}},//仠 gan
{3,14,{pysm::nop,pyym::nop}},//仡 ge
{1,0,{pysm::b,pyym::o}},//仢 bo
{1,0,{pysm::d,pyym::ai}},//代 dai
{2,41,{pysm::nop,pyym::nop}},//令 ling
{2,42,{pysm::nop,pyym::nop}},//以 yi
{1,0,{pysm::ch,pyym::ao}},//仦 chao
{1,0,{pysm::ch,pyym::ang}},//仧 chang
{1,0,{pysm::s,pyym::a}},//仨 sa
{1,0,{pysm::ch,pyym::ang}},//仩 chang
{1,0,{pysm::y,pyym::i}},//仪 yi
{1,0,{pysm::m,pyym::u}},//仫 mu
{1,0,{pysm::m,pyym::en}},//们 men
{1,0,{pysm::r,pyym::en}},//仭 ren
{1,0,{pysm::f,pyym::an}},//仮 fan
{2,43,{pysm::nop,pyym::nop}},//仯 chao
{2,44,{pysm::nop,pyym::nop}},//仰 yang
{2,45,{pysm::nop,pyym::nop}},//仱 qian
{1,0,{pysm::zh,pyym::ong}},//仲 zhong
{2,46,{pysm::nop,pyym::nop}},//仳 pi
{1,0,{pysm::w,pyym::o}},//仴 wo
{1,0,{pysm::w,pyym::u}},//仵 wu
{2,47,{pysm::nop,pyym::nop}},//件 jian
{2,48,{pysm::nop,pyym::nop}},//价 jia
{2,49,{pysm::nop,pyym::nop}},//仸 yao
{1,0,{pysm::f,pyym::eng}},//仹 feng
{1,0,{pysm::c,pyym::ang}},//仺 cang
{2,50,{pysm::nop,pyym::nop}},//任 ren
{1,0,{pysm::w,pyym::ang}},//仼 wang
{2,51,{pysm::nop,pyym::nop}},//份 fen
{1,0,{pysm::d,pyym::i}},//仾 di
{2,52,{pysm::nop,pyym::nop}},//仿 fang
{1,0,{pysm::zh,pyym::ong}},//伀 zhong
{1,0,{pysm::q,pyym::i}},//企 qi
{1,0,{pysm::p,pyym::ei}},//伂 pei
{2,53,{pysm::nop,pyym::nop}},//伃 yu
{1,0,{pysm::d,pyym::iao}},//伄 diao
{1,0,{pysm::d,pyym::un}},//伅 dun
{1,0,{pysm::w,pyym::u}},//伆 wu
{1,0,{pysm::y,pyym::i}},//伇 yi
{2,54,{pysm::nop,pyym::nop}},//伈 xin
{2,55,{pysm::nop,pyym::nop}},//伉 kang
{1,0,{pysm::y,pyym::i}},//伊 yi
{2,56,{pysm::nop,pyym::nop}},//伋 ji
{1,0,{pysm::nop,pyym::ai}},//伌 ai
{1,0,{pysm::w,pyym::u}},//伍 wu
{3,15,{pysm::nop,pyym::nop}},//伎 ji
{1,0,{pysm::f,pyym::u}},//伏 fu
{1,0,{pysm::f,pyym::a}},//伐 fa
{2,57,{pysm::nop,pyym::nop}},//休 xiu
{2,58,{pysm::nop,pyym::nop}},//伒 jin
{1,0,{pysm::p,pyym::i}},//伓 pi
{1,0,{pysm::d,pyym::an}},//伔 dan
{1,0,{pysm::f,pyym::u}},//伕 fu
{1,0,{pysm::t,pyym::ang}},//伖 tang
{2,59,{pysm::nop,pyym::nop}},//众 zhong
{1,0,{pysm::y,pyym::ou}},//优 you
{1,0,{pysm::h,pyym::uo}},//伙 huo
{2,60,{pysm::nop,pyym::nop}},//会 hui
{1,0,{pysm::y,pyym::u}},//伛 yu
{1,0,{pysm::c,pyym::ui}},//伜 cui
{1,0,{pysm::y,pyym::un}},//伝 yun
{1,0,{pysm::s,pyym::an}},//伞 san
{1,0,{pysm::w,pyym::ei}},//伟 wei
{2,61,{pysm::nop,pyym::nop}},//传 chuan
{1,0,{pysm::ch,pyym::e}},//伡 che
{1,0,{pysm::y,pyym::a}},//伢 ya
{2,62,{pysm::nop,pyym::nop}},//伣 qian
{1,0,{pysm::sh,pyym::ang}},//伤 shang
{1,0,{pysm::ch,pyym::ang}},//伥 chang
{1,0,{pysm::l,pyym::un}},//伦 lun
{2,63,{pysm::nop,pyym::nop}},//伧 cang
{1,0,{pysm::x,pyym::un}},//伨 xun
{1,0,{pysm::x,pyym::in}},//伩 xin
{1,0,{pysm::w,pyym::ei}},//伪 wei
{1,0,{pysm::zh,pyym::u}},//伫 zhu
{1,0,{pysm::z,pyym::e}},//伬 ze
{1,0,{pysm::x,pyym::ian}},//伭 xian
{1,0,{pysm::n,pyym::u}},//伮 nu
{4,2,{pysm::nop,pyym::nop}},//伯 bo
{1,0,{pysm::g,pyym::u}},//估 gu
{1,0,{pysm::n,pyym::i}},//伱 ni
{1,0,{pysm::n,pyym::i}},//伲 ni
{1,0,{pysm::x,pyym::ie}},//伳 xie
{2,64,{pysm::nop,pyym::nop}},//伴 ban
{1,0,{pysm::x,pyym::u}},//伵 xu
{1,0,{pysm::l,pyym::ing}},//伶 ling
{1,0,{pysm::zh,pyym::ou}},//伷 zhou
{1,0,{pysm::sh,pyym::en}},//伸 shen
{2,65,{pysm::nop,pyym::nop}},//伹 qu
{2,66,{pysm::nop,pyym::nop}},//伺 ci
{1,0,{pysm::b,pyym::eng}},//伻 beng
{2,67,{pysm::nop,pyym::nop}},//似 shi
{3,16,{pysm::nop,pyym::nop}},//伽 ga
{1,0,{pysm::p,pyym::i}},//伾 pi
{1,0,{pysm::y,pyym::i}},//伿 yi
{1,0,{pysm::s,pyym::i}},//佀 si
{4,3,{pysm::nop,pyym::nop}},//佁 yi
{1,0,{pysm::zh,pyym::eng}},//佂 zheng
{2,68,{pysm::nop,pyym::nop}},//佃 dian
{2,69,{pysm::nop,pyym::nop}},//佄 han
{1,0,{pysm::m,pyym::ai}},//佅 mai
{3,17,{pysm::nop,pyym::nop}},//但 dan
{1,0,{pysm::zh,pyym::u}},//佇 zhu
{1,0,{pysm::b,pyym::u}},//佈 bu
{2,70,{pysm::nop,pyym::nop}},//佉 qu
{1,0,{pysm::b,pyym::i}},//佊 bi
{2,71,{pysm::nop,pyym::nop}},//佋 zhao
{1,0,{pysm::c,pyym::i}},//佌 ci
{2,72,{pysm::nop,pyym::nop}},//位 wei
{1,0,{pysm::d,pyym::i}},//低 di
{1,0,{pysm::zh,pyym::u}},//住 zhu
{1,0,{pysm::z,pyym::uo}},//佐 zuo
{1,0,{pysm::y,pyym::ou}},//佑 you
{1,0,{pysm::y,pyym::ang}},//佒 yang
{3,18,{pysm::nop,pyym::nop}},//体 ti
{3,19,{pysm::nop,pyym::nop}},//佔 zhan
{1,0,{pysm::h,pyym::e}},//何 he
{1,0,{pysm::b,pyym::i}},//佖 bi
{2,73,{pysm::nop,pyym::nop}},//佗 tuo
{1,0,{pysm::sh,pyym::e}},//佘 she
{3,20,{pysm::nop,pyym::nop}},//余 yu
{2,74,{pysm::nop,pyym::nop}},//佚 yi
{4,4,{pysm::nop,pyym::nop}},//佛 fu
{1,0,{pysm::z,pyym::uo}},//作 zuo
{3,21,{pysm::nop,pyym::nop}},//佝 gou
{1,0,{pysm::n,pyym::ing}},//佞 ning
{1,0,{pysm::t,pyym::ong}},//佟 tong
{1,0,{pysm::n,pyym::i}},//你 ni
{1,0,{pysm::x,pyym::ian}},//佡 xian
{1,0,{pysm::q,pyym::u}},//佢 qu
{1,0,{pysm::y,pyym::ong}},//佣 yong
{1,0,{pysm::w,pyym::a}},//佤 wa
{1,0,{pysm::q,pyym::ian}},//佥 qian
{1,0,{pysm::sh,pyym::i}},//佦 shi
{1,0,{pysm::k,pyym::a}},//佧 ka
{1,0,{pysm::b,pyym::ao}},//佨 bao
{1,0,{pysm::p,pyym::ei}},//佩 pei
{2,75,{pysm::nop,pyym::nop}},//佪 hui
{2,76,{pysm::nop,pyym::nop}},//佫 he
{2,77,{pysm::nop,pyym::nop}},//佬 lao
{1,0,{pysm::x,pyym::iang}},//佭 xiang
{2,78,{pysm::nop,pyym::nop}},//佮 ge
{1,0,{pysm::y,pyym::ang}},//佯 yang
{2,79,{pysm::nop,pyym::nop}},//佰 bai
{1,0,{pysm::f,pyym::a}},//佱 fa
{1,0,{pysm::m,pyym::ing}},//佲 ming
{1,0,{pysm::j,pyym::ia}},//佳 jia
{2,80,{pysm::nop,pyym::nop}},//佴 er
{1,0,{pysm::b,pyym::ing}},//併 bing
{1,0,{pysm::j,pyym::i}},//佶 ji
{2,81,{pysm::nop,pyym::nop}},//佷 hen
{1,0,{pysm::h,pyym::uo}},//佸 huo
{1,0,{pysm::g,pyym::ui}},//佹 gui
{1,0,{pysm::q,pyym::uan}},//佺 quan
{5,0,{pysm::nop,pyym::nop}},//佻 tiao
{2,82,{pysm::nop,pyym::nop}},//佼 jiao
{1,0,{pysm::c,pyym::i}},//佽 ci
{1,0,{pysm::y,pyym::i}},//佾 yi
{1,0,{pysm::sh,pyym::i}},//使 shi
{1,0,{pysm::x,pyym::ing}},//侀 xing
{1,0,{pysm::sh,pyym::en}},//侁 shen
{1,0,{pysm::t,pyym::uo}},//侂 tuo
{1,0,{pysm::k,pyym::an}},//侃 kan
{1,0,{pysm::zh,pyym::i}},//侄 zhi
{2,83,{pysm::nop,pyym::nop}},//侅 gai
{1,0,{pysm::l,pyym::ai}},//來 lai
{1,0,{pysm::y,pyym::i}},//侇 yi
{1,0,{pysm::ch,pyym::i}},//侈 chi
{4,5,{pysm::nop,pyym::nop}},//侉 kua
{1,0,{pysm::g,pyym::uang}},//侊 guang
{2,84,{pysm::nop,pyym::nop}},//例 li
{1,0,{pysm::y,pyym::in}},//侌 yin
{1,0,{pysm::sh,pyym::i}},//侍 shi
{1,0,{pysm::m,pyym::i}},//侎 mi
{2,85,{pysm::nop,pyym::nop}},//侏 zhu
{1,0,{pysm::x,pyym::u}},//侐 xu
{1,0,{pysm::y,pyym::ou}},//侑 you
{1,0,{pysm::nop,pyym::an}},//侒 an
{1,0,{pysm::l,pyym::u}},//侓 lu
{2,86,{pysm::nop,pyym::nop}},//侔 mou
{1,0,{pysm::nop,pyym::er}},//侕 er
{1,0,{pysm::l,pyym::un}},//侖 lun
{2,87,{pysm::nop,pyym::nop}},//侗 dong
{1,0,{pysm::ch,pyym::a}},//侘 cha
{1,0,{pysm::ch,pyym::i}},//侙 chi
{1,0,{pysm::x,pyym::un}},//侚 xun
{1,0,{pysm::g,pyym::ong}},//供 gong
{1,0,{pysm::zh,pyym::ou}},//侜 zhou
{1,0,{pysm::y,pyym::i}},//依 yi
{1,0,{pysm::r,pyym::u}},//侞 ru
{2,88,{pysm::nop,pyym::nop}},//侟 cun
{1,0,{pysm::x,pyym::ia}},//侠 xia
{1,0,{pysm::s,pyym::i}},//価 si
{1,0,{pysm::d,pyym::ai}},//侢 dai
{1,0,{pysm::l,pyym::v}},//侣 lü
{1,0,{pysm::t,pyym::a}},//侤 ta
{2,89,{pysm::nop,pyym::nop}},//侥 jiao
{1,0,{pysm::zh,pyym::en}},//侦 zhen
{3,22,{pysm::nop,pyym::nop}},//侧 ce
{1,0,{pysm::q,pyym::iao}},//侨 qiao
{1,0,{pysm::k,pyym::uai}},//侩 kuai
{1,0,{pysm::ch,pyym::ai}},//侪 chai
{1,0,{pysm::n,pyym::ing}},//侫 ning
{1,0,{pysm::n,pyym::ong}},//侬 nong
{1,0,{pysm::j,pyym::in}},//侭 jin
{1,0,{pysm::w,pyym::u}},//侮 wu
{1,0,{pysm::h,pyym::ou}},//侯 hou
{1,0,{pysm::j,pyym::iong}},//侰 jiong
{2,90,{pysm::nop,pyym::nop}},//侱 cheng
{2,91,{pysm::nop,pyym::nop}},//侲 zhen
{1,0,{pysm::z,pyym::uo}},//侳 zuo
{1,0,{pysm::ch,pyym::ou}},//侴 chou
{1,0,{pysm::q,pyym::in}},//侵 qin
{1,0,{pysm::l,pyym::v}},//侶 lü
{1,0,{pysm::j,pyym::u}},//侷 ju
{2,92,{pysm::nop,pyym::nop}},//侸 shu
{1,0,{pysm::t,pyym::ing}},//侹 ting
{1,0,{pysm::sh,pyym::en}},//侺 shen
{2,93,{pysm::nop,pyym::nop}},//侻 tui
{1,0,{pysm::b,pyym::o}},//侼 bo
{1,0,{pysm::n,pyym::an}},//侽 nan
{1,0,{pysm::x,pyym::iao}},//侾 xiao
{2,94,{pysm::nop,pyym::nop}},//便 bian
{1,0,{pysm::t,pyym::ui}},//俀 tui
{1,0,{pysm::y,pyym::u}},//俁 yu
{1,0,{pysm::x,pyym::i}},//係 xi
{2,95,{pysm::nop,pyym::nop}},//促 cu
{1,0,{pysm::nop,pyym::e}},//俄 e
{1,0,{pysm::q,pyym::iu}},//俅 qiu
{2,96,{pysm::nop,pyym::nop}},//俆 xu
{1,0,{pysm::g,pyym::uang}},//俇 guang
{1,0,{pysm::k,pyym::u}},//俈 ku
{1,0,{pysm::w,pyym::u}},//俉 wu
{3,23,{pysm::nop,pyym::nop}},//俊 jun
{1,0,{pysm::y,pyym::i}},//俋 yi
{1,0,{pysm::f,pyym::u}},//俌 fu
{2,97,{pysm::nop,pyym::nop}},//俍 liang
{1,0,{pysm::z,pyym::u}},//俎 zu
{2,98,{pysm::nop,pyym::nop}},//俏 qiao
{1,0,{pysm::l,pyym::i}},//俐 li
{1,0,{pysm::y,pyym::ong}},//俑 yong
{1,0,{pysm::h,pyym::un}},//俒 hun
{2,99,{pysm::nop,pyym::nop}},//俓 jing
{2,100,{pysm::nop,pyym::nop}},//俔 qian
{1,0,{pysm::s,pyym::an}},//俕 san
{1,0,{pysm::p,pyym::ei}},//俖 pei
{1,0,{pysm::s,pyym::u}},//俗 su
{1,0,{pysm::f,pyym::u}},//俘 fu
{1,0,{pysm::x,pyym::i}},//俙 xi
{1,0,{pysm::l,pyym::i}},//俚 li
{2,101,{pysm::nop,pyym::nop}},//俛 fu
{1,0,{pysm::p,pyym::ing}},//俜 ping
{1,0,{pysm::b,pyym::ao}},//保 bao
{2,102,{pysm::nop,pyym::nop}},//俞 yu
{2,103,{pysm::nop,pyym::nop}},//俟 qi
{1,0,{pysm::x,pyym::ia}},//俠 xia
{2,104,{pysm::nop,pyym::nop}},//信 xin
{1,0,{pysm::x,pyym::iu}},//俢 xiu
{1,0,{pysm::y,pyym::u}},//俣 yu
{1,0,{pysm::d,pyym::i}},//俤 di
{2,105,{pysm::nop,pyym::nop}},//俥 che
{1,0,{pysm::ch,pyym::ou}},//俦 chou
{1,0,{pysm::zh,pyym::i}},//俧 zhi
{1,0,{pysm::y,pyym::an}},//俨 yan
{2,106,{pysm::nop,pyym::nop}},//俩 lia
{1,0,{pysm::l,pyym::i}},//俪 li
{1,0,{pysm::l,pyym::ai}},//俫 lai
{1,0,{pysm::s,pyym::i}},//俬 si
{1,0,{pysm::j,pyym::ian}},//俭 jian
{1,0,{pysm::x,pyym::iu}},//修 xiu
{1,0,{pysm::f,pyym::u}},//俯 fu
{1,0,{pysm::h,pyym::uo}},//俰 huo
{1,0,{pysm::j,pyym::u}},//俱 ju
{1,0,{pysm::x,pyym::iao}},//俲 xiao
{1,0,{pysm::p,pyym::ai}},//俳 pai
{1,0,{pysm::j,pyym::ian}},//俴 jian
{1,0,{pysm::b,pyym::iao}},//俵 biao
{3,24,{pysm::nop,pyym::nop}},//俶 chu
{1,0,{pysm::f,pyym::ei}},//俷 fei
{2,107,{pysm::nop,pyym::nop}},//俸 feng
{1,0,{pysm::y,pyym::a}},//俹 ya
{2,108,{pysm::nop,pyym::nop}},//俺 an
{1,0,{pysm::b,pyym::ei}},//俻 bei
{1,0,{pysm::y,pyym::u}},//俼 yu
{1,0,{pysm::x,pyym::in}},//俽 xin
{3,25,{pysm::nop,pyym::nop}},//俾 bi
{2,109,{pysm::nop,pyym::nop}},//俿 hu
{3,26,{pysm::nop,pyym::nop}},//倀 chang
{1,0,{pysm::zh,pyym::i}},//倁 zhi
{1,0,{pysm::b,pyym::ing}},//倂 bing
{1,0,{pysm::j,pyym::iu}},//倃 jiu
{1,0,{pysm::y,pyym::ao}},//倄 yao
{2,110,{pysm::nop,pyym::nop}},//倅 cui
{2,111,{pysm::nop,pyym::nop}},//倆 lia
{1,0,{pysm::w,pyym::an}},//倇 wan
{2,112,{pysm::nop,pyym::nop}},//倈 lai
{2,113,{pysm::nop,pyym::nop}},//倉 cang
{1,0,{pysm::z,pyym::ong}},//倊 zong
{1,0,{pysm::g,pyym::e}},//個 ge
{1,0,{pysm::g,pyym::uan}},//倌 guan
{2,114,{pysm::nop,pyym::nop}},//倍 bei
{1,0,{pysm::t,pyym::ian}},//倎 tian
{1,0,{pysm::sh,pyym::u}},//倏 shu
{1,0,{pysm::sh,pyym::u}},//倐 shu
{1,0,{pysm::m,pyym::en}},//們 men
{1,0,{pysm::d,pyym::ao}},//倒 dao
{2,115,{pysm::nop,pyym::nop}},//倓 tan
{1,0,{pysm::j,pyym::ue}},//倔 jue
{2,116,{pysm::nop,pyym::nop}},//倕 chui
{1,0,{pysm::x,pyym::ing}},//倖 xing
{2,117,{pysm::nop,pyym::nop}},//倗 peng
{2,118,{pysm::nop,pyym::nop}},//倘 tang
{1,0,{pysm::h,pyym::ou}},//候 hou
{2,119,{pysm::nop,pyym::nop}},//倚 yi
{1,0,{pysm::q,pyym::i}},//倛 qi
{3,27,{pysm::nop,pyym::nop}},//倜 ti
{1,0,{pysm::g,pyym::an}},//倝 gan
{2,120,{pysm::nop,pyym::nop}},//倞 jing
{1,0,{pysm::j,pyym::ie}},//借 jie
{1,0,{pysm::s,pyym::ui}},//倠 sui
{1,0,{pysm::ch,pyym::ang}},//倡 chang
{2,121,{pysm::nop,pyym::nop}},//倢 jie
{1,0,{pysm::f,pyym::ang}},//倣 fang
{1,0,{pysm::zh,pyym::i}},//値 zhi
{1,0,{pysm::k,pyym::ong}},//倥 kong
{1,0,{pysm::j,pyym::uan}},//倦 juan
{1,0,{pysm::z,pyym::ong}},//倧 zong
{1,0,{pysm::j,pyym::u}},//倨 ju
{2,122,{pysm::nop,pyym::nop}},//倩 qian
{2,123,{pysm::nop,pyym::nop}},//倪 ni
{1,0,{pysm::l,pyym::un}},//倫 lun
{1,0,{pysm::zh,pyym::uo}},//倬 zhuo
{2,124,{pysm::nop,pyym::nop}},//倭 wo
{1,0,{pysm::l,pyym::uo}},//倮 luo
{1,0,{pysm::s,pyym::ong}},//倯 song
{2,125,{pysm::nop,pyym::nop}},//倰 leng
{1,0,{pysm::h,pyym::un}},//倱 hun
{1,0,{pysm::d,pyym::ong}},//倲 dong
{1,0,{pysm::z,pyym::i}},//倳 zi
{1,0,{pysm::b,pyym::en}},//倴 ben
{1,0,{pysm::w,pyym::u}},//倵 wu
{1,0,{pysm::j,pyym::u}},//倶 ju
{1,0,{pysm::n,pyym::ai}},//倷 nai
{1,0,{pysm::c,pyym::ai}},//倸 cai
{1,0,{pysm::j,pyym::ian}},//倹 jian
{1,0,{pysm::zh,pyym::ai}},//债 zhai
{1,0,{pysm::y,pyym::e}},//倻 ye
{1,0,{pysm::zh,pyym::i}},//值 zhi
{1,0,{pysm::sh,pyym::a}},//倽 sha
{1,0,{pysm::q,pyym::ing}},//倾 qing
{1,0,{pysm::n,pyym::ing}},//倿 ning
{1,0,{pysm::y,pyym::ing}},//偀 ying
{1,0,{pysm::ch,pyym::eng}},//偁 cheng
{1,0,{pysm::q,pyym::ian}},//偂 qian
{1,0,{pysm::y,pyym::an}},//偃 yan
{2,126,{pysm::nop,pyym::nop}},//偄 ruan
{3,28,{pysm::nop,pyym::nop}},//偅 zhong
{1,0,{pysm::ch,pyym::un}},//偆 chun
{4,6,{pysm::nop,pyym::nop}},//假 jia
{3,29,{pysm::nop,pyym::nop}},//偈 ji
{1,0,{pysm::w,pyym::ei}},//偉 wei
{1,0,{pysm::y,pyym::u}},//偊 yu
{1,0,{pysm::b,pyym::ing}},//偋 bing
{2,127,{pysm::nop,pyym::nop}},//偌 ruo
{1,0,{pysm::t,pyym::i}},//偍 ti
{1,0,{pysm::w,pyym::ei}},//偎 wei
{1,0,{pysm::p,pyym::ian}},//偏 pian
{1,0,{pysm::y,pyym::an}},//偐 yan
{1,0,{pysm::f,pyym::eng}},//偑 feng
{2,128,{pysm::nop,pyym::nop}},//偒 tang
{1,0,{pysm::w,pyym::o}},//偓 wo
{1,0,{pysm::nop,pyym::e}},//偔 e
{2,129,{pysm::nop,pyym::nop}},//偕 xie
{1,0,{pysm::ch,pyym::e}},//偖 che
{1,0,{pysm::sh,pyym::eng}},//偗 sheng
{1,0,{pysm::k,pyym::an}},//偘 kan
{1,0,{pysm::d,pyym::i}},//偙 di
{1,0,{pysm::z,pyym::uo}},//做 zuo
{1,0,{pysm::ch,pyym::a}},//偛 cha
{1,0,{pysm::t,pyym::ing}},//停 ting
{1,0,{pysm::b,pyym::ei}},//偝 bei
{3,30,{pysm::nop,pyym::nop}},//偞 xie
{1,0,{pysm::h,pyym::uang}},//偟 huang
{1,0,{pysm::y,pyym::ao}},//偠 yao
{1,0,{pysm::zh,pyym::an}},//偡 zhan
{3,31,{pysm::nop,pyym::nop}},//偢 chou
{1,0,{pysm::y,pyym::an}},//偣 yan
{1,0,{pysm::y,pyym::ou}},//偤 you
{1,0,{pysm::j,pyym::ian}},//健 jian
{1,0,{pysm::x,pyym::u}},//偦 xu
{1,0,{pysm::zh,pyym::a}},//偧 zha
{1,0,{pysm::c,pyym::i}},//偨 ci
{1,0,{pysm::f,pyym::u}},//偩 fu
{2,130,{pysm::nop,pyym::nop}},//偪 bi
{1,0,{pysm::zh,pyym::i}},//偫 zhi
{2,131,{pysm::nop,pyym::nop}},//偬 zong
{1,0,{pysm::m,pyym::ian}},//偭 mian
{1,0,{pysm::j,pyym::i}},//偮 ji
{1,0,{pysm::y,pyym::i}},//偯 yi
{1,0,{pysm::x,pyym::ie}},//偰 xie
{1,0,{pysm::x,pyym::un}},//偱 xun
{2,132,{pysm::nop,pyym::nop}},//偲 cai
{1,0,{pysm::d,pyym::uan}},//偳 duan
{3,32,{pysm::nop,pyym::nop}},//側 ce
{2,133,{pysm::nop,pyym::nop}},//偵 zhen
{1,0,{pysm::nop,pyym::ou}},//偶 ou
{1,0,{pysm::t,pyym::ou}},//偷 tou
{1,0,{pysm::t,pyym::ou}},//偸 tou
{1,0,{pysm::b,pyym::ei}},//偹 bei
{2,134,{pysm::nop,pyym::nop}},//偺 za
{2,135,{pysm::nop,pyym::nop}},//偻 lou
{1,0,{pysm::j,pyym::ie}},//偼 jie
{3,33,{pysm::nop,pyym::nop}},//偽 wei
{1,0,{pysm::f,pyym::en}},//偾 fen
{1,0,{pysm::ch,pyym::ang}},//偿 chang
{3,34,{pysm::nop,pyym::nop}},//傀 gui
{1,0,{pysm::s,pyym::ou}},//傁 sou
{2,136,{pysm::nop,pyym::nop}},//傂 zhi
{1,0,{pysm::s,pyym::u}},//傃 su
{1,0,{pysm::x,pyym::ia}},//傄 xia
{1,0,{pysm::f,pyym::u}},//傅 fu
{1,0,{pysm::y,pyym::uan}},//傆 yuan
{1,0,{pysm::r,pyym::ong}},//傇 rong
{1,0,{pysm::l,pyym::i}},//傈 li
{1,0,{pysm::n,pyym::u}},//傉 nu
{1,0,{pysm::y,pyym::un}},//傊 yun
{2,137,{pysm::nop,pyym::nop}},//傋 jiang
{1,0,{pysm::m,pyym::a}},//傌 ma
{4,7,{pysm::nop,pyym::nop}},//傍 bang
{1,0,{pysm::d,pyym::ian}},//傎 dian
{1,0,{pysm::t,pyym::ang}},//傏 tang
{1,0,{pysm::h,pyym::ao}},//傐 hao
{1,0,{pysm::j,pyym::ie}},//傑 jie
{1,0,{pysm::x,pyym::i}},//傒 xi
{1,0,{pysm::sh,pyym::an}},//傓 shan
{2,138,{pysm::nop,pyym::nop}},//傔 qian
{2,139,{pysm::nop,pyym::nop}},//傕 jue
{3,35,{pysm::nop,pyym::nop}},//傖 cang
{1,0,{pysm::ch,pyym::u}},//傗 chu
{1,0,{pysm::s,pyym::an}},//傘 san
{1,0,{pysm::b,pyym::ei}},//備 bei
{1,0,{pysm::x,pyym::iao}},//傚 xiao
{2,140,{pysm::nop,pyym::nop}},//傛 yong
{1,0,{pysm::y,pyym::ao}},//傜 yao
{2,141,{pysm::nop,pyym::nop}},//傝 tan
{1,0,{pysm::s,pyym::uo}},//傞 suo
{1,0,{pysm::y,pyym::ang}},//傟 yang
{1,0,{pysm::f,pyym::a}},//傠 fa
{1,0,{pysm::b,pyym::ing}},//傡 bing
{2,142,{pysm::nop,pyym::nop}},//傢 jia
{1,0,{pysm::d,pyym::ai}},//傣 dai
{1,0,{pysm::z,pyym::ai}},//傤 zai
{1,0,{pysm::t,pyym::ang}},//傥 tang
{1,0,{pysm::g,pyym::u}},//傦 gu
{1,0,{pysm::b,pyym::in}},//傧 bin
{1,0,{pysm::ch,pyym::u}},//储 chu
{1,0,{pysm::n,pyym::uo}},//傩 nuo
{4,8,{pysm::nop,pyym::nop}},//傪 can
{1,0,{pysm::l,pyym::ei}},//傫 lei
{1,0,{pysm::c,pyym::ui}},//催 cui
{2,143,{pysm::nop,pyym::nop}},//傭 yong
{2,144,{pysm::nop,pyym::nop}},//傮 zao
{1,0,{pysm::z,pyym::ong}},//傯 zong
{2,145,{pysm::nop,pyym::nop}},//傰 beng
{2,146,{pysm::nop,pyym::nop}},//傱 song
{1,0,{pysm::nop,pyym::ao}},//傲 ao
{2,147,{pysm::nop,pyym::nop}},//傳 chuan
{1,0,{pysm::y,pyym::u}},//傴 yu
{1,0,{pysm::zh,pyym::ai}},//債 zhai
{2,148,{pysm::nop,pyym::nop}},//傶 zu
{1,0,{pysm::sh,pyym::ang}},//傷 shang
{1,0,{pysm::ch,pyym::uang}},//傸 chuang
{1,0,{pysm::j,pyym::ing}},//傹 jing
{1,0,{pysm::ch,pyym::i}},//傺 chi
{1,0,{pysm::sh,pyym::a}},//傻 sha
{1,0,{pysm::h,pyym::an}},//傼 han
{1,0,{pysm::zh,pyym::ang}},//傽 zhang
{1,0,{pysm::q,pyym::ing}},//傾 qing
{2,149,{pysm::nop,pyym::nop}},//傿 yan
{1,0,{pysm::d,pyym::i}},//僀 di
{2,150,{pysm::nop,pyym::nop}},//僁 xie
{3,36,{pysm::nop,pyym::nop}},//僂 lou
{1,0,{pysm::b,pyym::ei}},//僃 bei
{2,151,{pysm::nop,pyym::nop}},//僄 piao
{1,0,{pysm::j,pyym::in}},//僅 jin
{1,0,{pysm::l,pyym::ian}},//僆 lian
{2,152,{pysm::nop,pyym::nop}},//僇 lu
{1,0,{pysm::m,pyym::an}},//僈 man
{1,0,{pysm::q,pyym::ian}},//僉 qian
{1,0,{pysm::x,pyym::ian}},//僊 xian
{2,153,{pysm::nop,pyym::nop}},//僋 tan
{1,0,{pysm::y,pyym::ing}},//僌 ying
{1,0,{pysm::d,pyym::ong}},//働 dong
{2,154,{pysm::nop,pyym::nop}},//僎 zhuan
{1,0,{pysm::x,pyym::iang}},//像 xiang
{1,0,{pysm::sh,pyym::an}},//僐 shan
{2,155,{pysm::nop,pyym::nop}},//僑 qiao
{1,0,{pysm::j,pyym::iong}},//僒 jiong
{1,0,{pysm::t,pyym::ui}},//僓 tui
{2,156,{pysm::nop,pyym::nop}},//僔 zun
{2,157,{pysm::nop,pyym::nop}},//僕 pu
{1,0,{pysm::x,pyym::i}},//僖 xi
{1,0,{pysm::l,pyym::ao}},//僗 lao
{1,0,{pysm::ch,pyym::ang}},//僘 chang
{1,0,{pysm::g,pyym::uang}},//僙 guang
{2,158,{pysm::nop,pyym::nop}},//僚 liao
{1,0,{pysm::q,pyym::i}},//僛 qi
{3,37,{pysm::nop,pyym::nop}},//僜 cheng
{2,159,{pysm::nop,pyym::nop}},//僝 chan
{1,0,{pysm::w,pyym::ei}},//僞 wei
{1,0,{pysm::j,pyym::i}},//僟 ji
{1,0,{pysm::b,pyym::o}},//僠 bo
{1,0,{pysm::h,pyym::ui}},//僡 hui
{2,160,{pysm::nop,pyym::nop}},//僢 chuan
{2,161,{pysm::nop,pyym::nop}},//僣 tie
{4,9,{pysm::nop,pyym::nop}},//僤 dan
{2,162,{pysm::nop,pyym::nop}},//僥 jiao
{1,0,{pysm::j,pyym::iu}},//僦 jiu
{2,163,{pysm::nop,pyym::nop}},//僧 seng
{1,0,{pysm::f,pyym::en}},//僨 fen
{1,0,{pysm::x,pyym::ian}},//僩 xian
{2,164,{pysm::nop,pyym::nop}},//僪 ju
{1,0,{pysm::nop,pyym::e}},//僫 e
{1,0,{pysm::j,pyym::iao}},//僬 jiao
{2,165,{pysm::nop,pyym::nop}},//僭 jian
{3,38,{pysm::nop,pyym::nop}},//僮 tong
{1,0,{pysm::l,pyym::in}},//僯 lin
{1,0,{pysm::b,pyym::o}},//僰 bo
{1,0,{pysm::g,pyym::u}},//僱 gu
{1,0,{pysm::x,pyym::ian}},//僲 xian
{1,0,{pysm::s,pyym::u}},//僳 su
{1,0,{pysm::x,pyym::ian}},//僴 xian
{1,0,{pysm::j,pyym::iang}},//僵 jiang
{1,0,{pysm::m,pyym::in}},//僶 min
{1,0,{pysm::y,pyym::e}},//僷 ye
{1,0,{pysm::j,pyym::in}},//僸 jin
{3,39,{pysm::nop,pyym::nop}},//價 jia
{1,0,{pysm::q,pyym::iao}},//僺 qiao
{1,0,{pysm::p,pyym::i}},//僻 pi
{1,0,{pysm::f,pyym::eng}},//僼 feng
{1,0,{pysm::zh,pyym::ou}},//僽 zhou
{1,0,{pysm::nop,pyym::ai}},//僾 ai
{1,0,{pysm::s,pyym::ai}},//僿 sai
{1,0,{pysm::y,pyym::i}},//儀 yi
{1,0,{pysm::j,pyym::un}},//儁 jun
{1,0,{pysm::n,pyym::ong}},//儂 nong
{5,1,{pysm::nop,pyym::nop}},//儃 chan
{1,0,{pysm::y,pyym::i}},//億 yi
{1,0,{pysm::d,pyym::ang}},//儅 dang
{1,0,{pysm::j,pyym::ing}},//儆 jing
{1,0,{pysm::x,pyym::uan}},//儇 xuan
{1,0,{pysm::k,pyym::uai}},//儈 kuai
{1,0,{pysm::j,pyym::ian}},//儉 jian
{1,0,{pysm::ch,pyym::u}},//儊 chu
{2,166,{pysm::nop,pyym::nop}},//儋 dan
{1,0,{pysm::j,pyym::iao}},//儌 jiao
{1,0,{pysm::sh,pyym::a}},//儍 sha
{1,0,{pysm::z,pyym::ai}},//儎 zai
{1,0,{pysm::c,pyym::an}},//儏 can
{1,0,{pysm::b,pyym::in}},//儐 bin
{1,0,{pysm::nop,pyym::an}},//儑 an
{1,0,{pysm::r,pyym::u}},//儒 ru
{1,0,{pysm::t,pyym::ai}},//儓 tai
{2,167,{pysm::nop,pyym::nop}},//儔 chou
{1,0,{pysm::ch,pyym::ai}},//儕 chai
{1,0,{pysm::l,pyym::an}},//儖 lan
{3,40,{pysm::nop,pyym::nop}},//儗 ni
{1,0,{pysm::j,pyym::in}},//儘 jin
{1,0,{pysm::q,pyym::ian}},//儙 qian
{1,0,{pysm::m,pyym::eng}},//儚 meng
{1,0,{pysm::w,pyym::u}},//儛 wu
{1,0,{pysm::n,pyym::ing}},//儜 ning
{1,0,{pysm::q,pyym::iong}},//儝 qiong
{1,0,{pysm::n,pyym::i}},//儞 ni
{1,0,{pysm::ch,pyym::ang}},//償 chang
{2,168,{pysm::nop,pyym::nop}},//儠 lie
{1,0,{pysm::l,pyym::ei}},//儡 lei
{1,0,{pysm::l,pyym::v}},//儢 lü
{1,0,{pysm::k,pyym::uang}},//儣 kuang
{1,0,{pysm::b,pyym::ao}},//儤 bao
{3,41,{pysm::nop,pyym::nop}},//儥 yu
{1,0,{pysm::b,pyym::iao}},//儦 biao
{1,0,{pysm::z,pyym::an}},//儧 zan
{1,0,{pysm::zh,pyym::i}},//儨 zhi
{1,0,{pysm::s,pyym::i}},//儩 si
{1,0,{pysm::y,pyym::ou}},//優 you
{1,0,{pysm::h,pyym::ao}},//儫 hao
{1,0,{pysm::q,pyym::ing}},//儬 qing
{2,169,{pysm::nop,pyym::nop}},//儭 chen
{1,0,{pysm::l,pyym::i}},//儮 li
{1,0,{pysm::t,pyym::eng}},//儯 teng
{1,0,{pysm::w,pyym::ei}},//儰 wei
{1,0,{pysm::l,pyym::ong}},//儱 long
{1,0,{pysm::ch,pyym::u}},//儲 chu
{1,0,{pysm::ch,pyym::an}},//儳 chan
{2,170,{pysm::nop,pyym::nop}},//儴 rang
{2,171,{pysm::nop,pyym::nop}},//儵 shu
{2,172,{pysm::nop,pyym::nop}},//儶 hui
{1,0,{pysm::l,pyym::i}},//儷 li
{1,0,{pysm::l,pyym::uo}},//儸 luo
{1,0,{pysm::z,pyym::an}},//儹 zan
{1,0,{pysm::n,pyym::uo}},//儺 nuo
{2,173,{pysm::nop,pyym::nop}},//儻 tang
{1,0,{pysm::y,pyym::an}},//儼 yan
{2,174,{pysm::nop,pyym::nop}},//儽 lei
{1,0,{pysm::n,pyym::ang}},//儾 nang
{2,175,{pysm::nop,pyym::nop}},//儿 er
{1,0,{pysm::w,pyym::u}},//兀 wu
{2,176,{pysm::nop,pyym::nop}},//允 yun
{1,0,{pysm::z,pyym::an}},//兂 zan
{1,0,{pysm::y,pyym::uan}},//元 yuan
{2,177,{pysm::nop,pyym::nop}},//兄 xiong
{1,0,{pysm::ch,pyym::ong}},//充 chong
{1,0,{pysm::zh,pyym::ao}},//兆 zhao
{1,0,{pysm::x,pyym::iong}},//兇 xiong
{1,0,{pysm::x,pyym::ian}},//先 xian
{1,0,{pysm::g,pyym::uang}},//光 guang
{1,0,{pysm::d,pyym::ui}},//兊 dui
{1,0,{pysm::k,pyym::e}},//克 ke
{1,0,{pysm::d,pyym::ui}},//兌 dui
{3,42,{pysm::nop,pyym::nop}},//免 mian
{1,0,{pysm::t,pyym::u}},//兎 tu
{1,0,{pysm::ch,pyym::ang}},//兏 chang
{1,0,{pysm::nop,pyym::er}},//児 er
{3,43,{pysm::nop,pyym::nop}},//兑 dui
{2,178,{pysm::nop,pyym::nop}},//兒 er
{2,179,{pysm::nop,pyym::nop}},//兓 jin
{2,180,{pysm::nop,pyym::nop}},//兔 tu
{1,0,{pysm::s,pyym::i}},//兕 si
{1,0,{pysm::y,pyym::an}},//兖 yan
{1,0,{pysm::y,pyym::an}},//兗 yan
{1,0,{pysm::sh,pyym::i}},//兘 shi
{0,0,{pysm::nop,pyym::nop}},//兙 兙
{1,0,{pysm::d,pyym::ang}},//党 dang
{1,0,{pysm::q,pyym::ian}},//兛 qian
{1,0,{pysm::d,pyym::ou}},//兜 dou
{1,0,{pysm::f,pyym::en}},//兝 fen
{1,0,{pysm::m,pyym::ao}},//兞 mao
{1,0,{pysm::sh,pyym::en}},//兟 shen
{1,0,{pysm::d,pyym::ou}},//兠 dou
{0,0,{pysm::nop,pyym::nop}},//兡 兡
{1,0,{pysm::j,pyym::ing}},//兢 jing
{1,0,{pysm::l,pyym::i}},//兣 li
{1,0,{pysm::h,pyym::uang}},//兤 huang
{1,0,{pysm::r,pyym::u}},//入 ru
{1,0,{pysm::w,pyym::ang}},//兦 wang
{1,0,{pysm::n,pyym::ei}},//內 nei
{1,0,{pysm::q,pyym::uan}},//全 quan
{1,0,{pysm::l,pyym::iang}},//兩 liang
{3,44,{pysm::nop,pyym::nop}},//兪 yu
{1,0,{pysm::b,pyym::a}},//八 ba
{1,0,{pysm::g,pyym::ong}},//公 gong
{2,181,{pysm::nop,pyym::nop}},//六 liu
{1,0,{pysm::x,pyym::i}},//兮 xi
{1,0,{pysm::h,pyym::an}},//兯 han
{1,0,{pysm::l,pyym::an}},//兰 lan
{2,182,{pysm::nop,pyym::nop}},//共 gong
{1,0,{pysm::t,pyym::ian}},//兲 tian
{1,0,{pysm::g,pyym::uan}},//关 guan
{1,0,{pysm::x,pyym::ing}},//兴 xing
{1,0,{pysm::b,pyym::ing}},//兵 bing
{2,183,{pysm::nop,pyym::nop}},//其 qi
{1,0,{pysm::j,pyym::u}},//具 ju
{2,184,{pysm::nop,pyym::nop}},//典 dian
{2,185,{pysm::nop,pyym::nop}},//兹 zi
{1,0,{pysm::f,pyym::en}},//兺 fen
{1,0,{pysm::y,pyym::ang}},//养 yang
{1,0,{pysm::j,pyym::ian}},//兼 jian
{1,0,{pysm::sh,pyym::ou}},//兽 shou
{1,0,{pysm::j,pyym::i}},//兾 ji
{1,0,{pysm::y,pyym::i}},//兿 yi
{1,0,{pysm::j,pyym::i}},//冀 ji
{1,0,{pysm::ch,pyym::an}},//冁 chan
{1,0,{pysm::j,pyym::iong}},//冂 jiong
{1,0,{pysm::m,pyym::ao}},//冃 mao
{1,0,{pysm::r,pyym::an}},//冄 ran
{3,45,{pysm::nop,pyym::nop}},//内 nei
{1,0,{pysm::y,pyym::uan}},//円 yuan
{1,0,{pysm::m,pyym::ao}},//冇 mao
{1,0,{pysm::g,pyym::ang}},//冈 gang
{3,46,{pysm::nop,pyym::nop}},//冉 ran
{1,0,{pysm::c,pyym::e}},//冊 ce
{1,0,{pysm::j,pyym::iong}},//冋 jiong
{2,186,{pysm::nop,pyym::nop}},//册 ce
{1,0,{pysm::z,pyym::ai}},//再 zai
{1,0,{pysm::g,pyym::ua}},//冎 gua
{1,0,{pysm::j,pyym::iong}},//冏 jiong
{1,0,{pysm::m,pyym::ao}},//冐 mao
{1,0,{pysm::zh,pyym::ou}},//冑 zhou
{2,187,{pysm::nop,pyym::nop}},//冒 mao
{1,0,{pysm::g,pyym::ou}},//冓 gou
{1,0,{pysm::x,pyym::u}},//冔 xu
{1,0,{pysm::m,pyym::ian}},//冕 mian
{1,0,{pysm::m,pyym::i}},//冖 mi
{1,0,{pysm::r,pyym::ong}},//冗 rong
{2,188,{pysm::nop,pyym::nop}},//冘 yin
{1,0,{pysm::x,pyym::ie}},//写 xie
{1,0,{pysm::k,pyym::an}},//冚 kan
{1,0,{pysm::j,pyym::un}},//军 jun
{1,0,{pysm::n,pyym::ong}},//农 nong
{1,0,{pysm::y,pyym::i}},//冝 yi
{1,0,{pysm::m,pyym::i}},//冞 mi
{1,0,{pysm::sh,pyym::i}},//冟 shi
{1,0,{pysm::g,pyym::uan}},//冠 guan
{1,0,{pysm::m,pyym::eng}},//冡 meng
{1,0,{pysm::zh,pyym::ong}},//冢 zhong
{1,0,{pysm::j,pyym::u}},//冣 ju
{1,0,{pysm::y,pyym::uan}},//冤 yuan
{2,189,{pysm::nop,pyym::nop}},//冥 ming
{1,0,{pysm::k,pyym::ou}},//冦 kou
{1,0,{pysm::l,pyym::in}},//冧 lin
{1,0,{pysm::f,pyym::u}},//冨 fu
{1,0,{pysm::x,pyym::ie}},//冩 xie
{1,0,{pysm::m,pyym::i}},//冪 mi
{1,0,{pysm::b,pyym::ing}},//冫 bing
{1,0,{pysm::d,pyym::ong}},//冬 dong
{1,0,{pysm::t,pyym::ai}},//冭 tai
{1,0,{pysm::g,pyym::ang}},//冮 gang
{2,190,{pysm::nop,pyym::nop}},//冯 feng
{2,191,{pysm::nop,pyym::nop}},//冰 bing
{1,0,{pysm::h,pyym::u}},//冱 hu
{1,0,{pysm::ch,pyym::ong}},//冲 chong
{1,0,{pysm::j,pyym::ue}},//决 jue
{1,0,{pysm::h,pyym::u}},//冴 hu
{1,0,{pysm::k,pyym::uang}},//况 kuang
{1,0,{pysm::y,pyym::e}},//冶 ye
{2,192,{pysm::nop,pyym::nop}},//冷 leng
{1,0,{pysm::p,pyym::an}},//冸 pan
{1,0,{pysm::f,pyym::u}},//冹 fu
{1,0,{pysm::m,pyym::in}},//冺 min
{1,0,{pysm::d,pyym::ong}},//冻 dong
{2,193,{pysm::nop,pyym::nop}},//冼 xian
{1,0,{pysm::l,pyym::ie}},//冽 lie
{1,0,{pysm::q,pyym::ia}},//冾 qia
{1,0,{pysm::j,pyym::ian}},//冿 jian
{2,194,{pysm::nop,pyym::nop}},//净 jing
{1,0,{pysm::s,pyym::ou}},//凁 sou
{1,0,{pysm::m,pyym::ei}},//凂 mei
{1,0,{pysm::t,pyym::u}},//凃 tu
{1,0,{pysm::q,pyym::i}},//凄 qi
{1,0,{pysm::g,pyym::u}},//凅 gu
{1,0,{pysm::zh,pyym::un}},//准 zhun
{1,0,{pysm::s,pyym::ong}},//凇 song
{1,0,{pysm::j,pyym::ing}},//凈 jing
{1,0,{pysm::l,pyym::iang}},//凉 liang
{1,0,{pysm::q,pyym::ing}},//凊 qing
{1,0,{pysm::d,pyym::iao}},//凋 diao
{1,0,{pysm::l,pyym::ing}},//凌 ling
{1,0,{pysm::d,pyym::ong}},//凍 dong
{1,0,{pysm::g,pyym::an}},//凎 gan
{1,0,{pysm::j,pyym::ian}},//减 jian
{1,0,{pysm::y,pyym::in}},//凐 yin
{1,0,{pysm::c,pyym::ou}},//凑 cou
{1,0,{pysm::nop,pyym::ai}},//凒 ai
{1,0,{pysm::l,pyym::i}},//凓 li
{2,195,{pysm::nop,pyym::nop}},//凔 chuang
{1,0,{pysm::m,pyym::ing}},//凕 ming
{1,0,{pysm::zh,pyym::un}},//凖 zhun
{1,0,{pysm::c,pyym::ui}},//凗 cui
{1,0,{pysm::s,pyym::i}},//凘 si
{1,0,{pysm::d,pyym::uo}},//凙 duo
{1,0,{pysm::j,pyym::in}},//凚 jin
{1,0,{pysm::l,pyym::in}},//凛 lin
{1,0,{pysm::l,pyym::in}},//凜 lin
{1,0,{pysm::n,pyym::ing}},//凝 ning
{1,0,{pysm::x,pyym::i}},//凞 xi
{1,0,{pysm::d,pyym::u}},//凟 du
{1,0,{pysm::j,pyym::i}},//几 ji
{1,0,{pysm::f,pyym::an}},//凡 fan
{1,0,{pysm::f,pyym::an}},//凢 fan
{1,0,{pysm::f,pyym::an}},//凣 fan
{1,0,{pysm::f,pyym::eng}},//凤 feng
{1,0,{pysm::j,pyym::u}},//凥 ju
{1,0,{pysm::ch,pyym::u}},//処 chu
{1,0,{pysm::zh,pyym::eng}},//凧 zheng
{1,0,{pysm::f,pyym::eng}},//凨 feng
{1,0,{pysm::m,pyym::u}},//凩 mu
{1,0,{pysm::zh,pyym::i}},//凪 zhi
{1,0,{pysm::f,pyym::u}},//凫 fu
{1,0,{pysm::f,pyym::eng}},//凬 feng
{1,0,{pysm::p,pyym::ing}},//凭 ping
{1,0,{pysm::f,pyym::eng}},//凮 feng
{1,0,{pysm::k,pyym::ai}},//凯 kai
{1,0,{pysm::h,pyym::uang}},//凰 huang
{1,0,{pysm::k,pyym::ai}},//凱 kai
{1,0,{pysm::g,pyym::an}},//凲 gan
{1,0,{pysm::d,pyym::eng}},//凳 deng
{1,0,{pysm::p,pyym::ing}},//凴 ping
{2,196,{pysm::nop,pyym::nop}},//凵 qian
{1,0,{pysm::x,pyym::iong}},//凶 xiong
{1,0,{pysm::k,pyym::uai}},//凷 kuai
{1,0,{pysm::t,pyym::u}},//凸 tu
{2,197,{pysm::nop,pyym::nop}},//凹 ao
{1,0,{pysm::ch,pyym::u}},//出 chu
{1,0,{pysm::j,pyym::i}},//击 ji
{1,0,{pysm::d,pyym::ang}},//凼 dang
{1,0,{pysm::h,pyym::an}},//函 han
{1,0,{pysm::h,pyym::an}},//凾 han
{2,198,{pysm::nop,pyym::nop}},//凿 zao
{2,199,{pysm::nop,pyym::nop}},//刀 dao
{1,0,{pysm::d,pyym::iao}},//刁 diao
{1,0,{pysm::d,pyym::ao}},//刂 dao
{1,0,{pysm::r,pyym::en}},//刃 ren
{1,0,{pysm::r,pyym::en}},//刄 ren
{1,0,{pysm::ch,pyym::uang}},//刅 chuang
{1,0,{pysm::f,pyym::en}},//分 fen
{2,200,{pysm::nop,pyym::nop}},//切 qie
{1,0,{pysm::y,pyym::i}},//刈 yi
{1,0,{pysm::j,pyym::i}},//刉 ji
{1,0,{pysm::k,pyym::an}},//刊 kan
{1,0,{pysm::q,pyym::ian}},//刋 qian
{1,0,{pysm::c,pyym::un}},//刌 cun
{1,0,{pysm::ch,pyym::u}},//刍 chu
{1,0,{pysm::w,pyym::en}},//刎 wen
{1,0,{pysm::j,pyym::i}},//刏 ji
{1,0,{pysm::d,pyym::an}},//刐 dan
{1,0,{pysm::x,pyym::ing}},//刑 xing
{3,47,{pysm::nop,pyym::nop}},//划 hua
{1,0,{pysm::w,pyym::an}},//刓 wan
{1,0,{pysm::j,pyym::ue}},//刔 jue
{1,0,{pysm::l,pyym::i}},//刕 li
{1,0,{pysm::y,pyym::ue}},//刖 yue
{2,201,{pysm::nop,pyym::nop}},//列 lie
{1,0,{pysm::l,pyym::iu}},//刘 liu
{1,0,{pysm::z,pyym::e}},//则 ze
{1,0,{pysm::g,pyym::ang}},//刚 gang
{1,0,{pysm::ch,pyym::uang}},//创 chuang
{1,0,{pysm::f,pyym::u}},//刜 fu
{1,0,{pysm::ch,pyym::u}},//初 chu
{1,0,{pysm::q,pyym::u}},//刞 qu
{1,0,{pysm::d,pyym::iao}},//刟 diao
{1,0,{pysm::sh,pyym::an}},//删 shan
{1,0,{pysm::m,pyym::in}},//刡 min
{1,0,{pysm::l,pyym::ing}},//刢 ling
{1,0,{pysm::zh,pyym::ong}},//刣 zhong
{1,0,{pysm::p,pyym::an}},//判 pan
{1,0,{pysm::b,pyym::ie}},//別 bie
{1,0,{pysm::j,pyym::ie}},//刦 jie
{1,0,{pysm::j,pyym::ie}},//刧 jie
{2,202,{pysm::nop,pyym::nop}},//刨 pao
{1,0,{pysm::l,pyym::i}},//利 li
{1,0,{pysm::sh,pyym::an}},//刪 shan
{1,0,{pysm::b,pyym::ie}},//别 bie
{1,0,{pysm::ch,pyym::an}},//刬 chan
{1,0,{pysm::j,pyym::ing}},//刭 jing
{1,0,{pysm::g,pyym::ua}},//刮 gua
{1,0,{pysm::g,pyym::eng}},//刯 geng
{1,0,{pysm::d,pyym::ao}},//到 dao
{1,0,{pysm::ch,pyym::uang}},//刱 chuang
{1,0,{pysm::k,pyym::ui}},//刲 kui
{2,203,{pysm::nop,pyym::nop}},//刳 ku
{1,0,{pysm::d,pyym::uo}},//刴 duo
{1,0,{pysm::nop,pyym::er}},//刵 er
{1,0,{pysm::zh,pyym::i}},//制 zhi
{1,0,{pysm::sh,pyym::ua}},//刷 shua
{2,204,{pysm::nop,pyym::nop}},//券 quan
{2,205,{pysm::nop,pyym::nop}},//刹 sha
{2,206,{pysm::nop,pyym::nop}},//刺 ci
{2,207,{pysm::nop,pyym::nop}},//刻 ke
{1,0,{pysm::j,pyym::ie}},//刼 jie
{1,0,{pysm::g,pyym::ui}},//刽 gui
{1,0,{pysm::c,pyym::i}},//刾 ci
{1,0,{pysm::g,pyym::ui}},//刿 gui
{1,0,{pysm::k,pyym::ai}},//剀 kai
{1,0,{pysm::d,pyym::uo}},//剁 duo
{1,0,{pysm::j,pyym::i}},//剂 ji
{1,0,{pysm::t,pyym::i}},//剃 ti
{1,0,{pysm::j,pyym::ing}},//剄 jing
{2,208,{pysm::nop,pyym::nop}},//剅 lou
{1,0,{pysm::l,pyym::uo}},//剆 luo
{1,0,{pysm::z,pyym::e}},//則 ze
{1,0,{pysm::y,pyym::uan}},//剈 yuan
{1,0,{pysm::c,pyym::uo}},//剉 cuo
{4,10,{pysm::nop,pyym::nop}},//削 xue
{2,209,{pysm::nop,pyym::nop}},//剋 ke
{1,0,{pysm::l,pyym::a}},//剌 la
{2,210,{pysm::nop,pyym::nop}},//前 qian
{1,0,{pysm::sh,pyym::a}},//剎 sha
{1,0,{pysm::ch,pyym::uang}},//剏 chuang
{1,0,{pysm::g,pyym::ua}},//剐 gua
{1,0,{pysm::j,pyym::ian}},//剑 jian
{1,0,{pysm::c,pyym::uo}},//剒 cuo
{1,0,{pysm::l,pyym::i}},//剓 li
{1,0,{pysm::t,pyym::i}},//剔 ti
{1,0,{pysm::f,pyym::ei}},//剕 fei
{2,211,{pysm::nop,pyym::nop}},//剖 pou
{1,0,{pysm::ch,pyym::an}},//剗 chan
{1,0,{pysm::q,pyym::i}},//剘 qi
{1,0,{pysm::ch,pyym::uang}},//剙 chuang
{1,0,{pysm::z,pyym::i}},//剚 zi
{1,0,{pysm::g,pyym::ang}},//剛 gang
{1,0,{pysm::w,pyym::an}},//剜 wan
{1,0,{pysm::b,pyym::o}},//剝 bo
{1,0,{pysm::j,pyym::i}},//剞 ji
{2,212,{pysm::nop,pyym::nop}},//剟 duo
{2,213,{pysm::nop,pyym::nop}},//剠 qing
{2,214,{pysm::nop,pyym::nop}},//剡 shan
{2,215,{pysm::nop,pyym::nop}},//剢 du
{1,0,{pysm::j,pyym::ian}},//剣 jian
{1,0,{pysm::j,pyym::i}},//剤 ji
{3,48,{pysm::nop,pyym::nop}},//剥 bo
{1,0,{pysm::y,pyym::an}},//剦 yan
{1,0,{pysm::j,pyym::u}},//剧 ju
{1,0,{pysm::h,pyym::uo}},//剨 huo
{1,0,{pysm::sh,pyym::eng}},//剩 sheng
{1,0,{pysm::j,pyym::ian}},//剪 jian
{2,216,{pysm::nop,pyym::nop}},//剫 duo
{3,49,{pysm::nop,pyym::nop}},//剬 duan
{1,0,{pysm::w,pyym::u}},//剭 wu
{1,0,{pysm::g,pyym::ua}},//剮 gua
{2,217,{pysm::nop,pyym::nop}},//副 fu
{1,0,{pysm::sh,pyym::eng}},//剰 sheng
{1,0,{pysm::j,pyym::ian}},//剱 jian
{1,0,{pysm::g,pyym::e}},//割 ge
{2,218,{pysm::nop,pyym::nop}},//剳 da
{2,219,{pysm::nop,pyym::nop}},//剴 kai
{2,220,{pysm::nop,pyym::nop}},//創 chuang
{1,0,{pysm::ch,pyym::uan}},//剶 chuan
{1,0,{pysm::ch,pyym::an}},//剷 chan
{2,221,{pysm::nop,pyym::nop}},//剸 tuan
{2,222,{pysm::nop,pyym::nop}},//剹 lu
{1,0,{pysm::l,pyym::i}},//剺 li
{1,0,{pysm::p,pyym::eng}},//剻 peng
{1,0,{pysm::sh,pyym::an}},//剼 shan
{2,223,{pysm::nop,pyym::nop}},//剽 piao
{1,0,{pysm::k,pyym::ou}},//剾 kou
{2,224,{pysm::nop,pyym::nop}},//剿 jiao
{1,0,{pysm::g,pyym::ua}},//劀 gua
{1,0,{pysm::q,pyym::iao}},//劁 qiao
{1,0,{pysm::j,pyym::ue}},//劂 jue
{2,225,{pysm::nop,pyym::nop}},//劃 hua
{1,0,{pysm::zh,pyym::a}},//劄 zha
{1,0,{pysm::zh,pyym::uo}},//劅 zhuo
{1,0,{pysm::l,pyym::ian}},//劆 lian
{1,0,{pysm::j,pyym::u}},//劇 ju
{1,0,{pysm::p,pyym::i}},//劈 pi
{1,0,{pysm::l,pyym::iu}},//劉 liu
{1,0,{pysm::g,pyym::ui}},//劊 gui
{2,226,{pysm::nop,pyym::nop}},//劋 jiao
{1,0,{pysm::g,pyym::ui}},//劌 gui
{1,0,{pysm::j,pyym::ian}},//劍 jian
{1,0,{pysm::j,pyym::ian}},//劎 jian
{1,0,{pysm::t,pyym::ang}},//劏 tang
{2,227,{pysm::nop,pyym::nop}},//劐 huo
{1,0,{pysm::j,pyym::i}},//劑 ji
{1,0,{pysm::j,pyym::ian}},//劒 jian
{1,0,{pysm::y,pyym::i}},//劓 yi
{1,0,{pysm::j,pyym::ian}},//劔 jian
{1,0,{pysm::zh,pyym::i}},//劕 zhi
{1,0,{pysm::ch,pyym::an}},//劖 chan
{2,228,{pysm::nop,pyym::nop}},//劗 jian
{2,229,{pysm::nop,pyym::nop}},//劘 mo
{1,0,{pysm::l,pyym::i}},//劙 li
{1,0,{pysm::zh,pyym::u}},//劚 zhu
{1,0,{pysm::l,pyym::i}},//力 li
{1,0,{pysm::y,pyym::a}},//劜 ya
{1,0,{pysm::q,pyym::uan}},//劝 quan
{1,0,{pysm::b,pyym::an}},//办 ban
{1,0,{pysm::g,pyym::ong}},//功 gong
{1,0,{pysm::j,pyym::ia}},//加 jia
{1,0,{pysm::w,pyym::u}},//务 wu
{1,0,{pysm::m,pyym::ai}},//劢 mai
{1,0,{pysm::l,pyym::ie}},//劣 lie
{1,0,{pysm::j,pyym::in}},//劤 jin
{1,0,{pysm::k,pyym::eng}},//劥 keng
{2,230,{pysm::nop,pyym::nop}},//劦 xie
{1,0,{pysm::zh,pyym::i}},//劧 zhi
{1,0,{pysm::d,pyym::ong}},//动 dong
{2,231,{pysm::nop,pyym::nop}},//助 zhu
{1,0,{pysm::n,pyym::u}},//努 nu
{1,0,{pysm::j,pyym::ie}},//劫 jie
{1,0,{pysm::q,pyym::u}},//劬 qu
{1,0,{pysm::sh,pyym::ao}},//劭 shao
{1,0,{pysm::y,pyym::i}},//劮 yi
{1,0,{pysm::zh,pyym::u}},//劯 zhu
{1,0,{pysm::m,pyym::o}},//劰 mo
{1,0,{pysm::l,pyym::i}},//励 li
{2,232,{pysm::nop,pyym::nop}},//劲 jin
{1,0,{pysm::l,pyym::ao}},//劳 lao
{1,0,{pysm::l,pyym::ao}},//労 lao
{1,0,{pysm::j,pyym::uan}},//劵 juan
{1,0,{pysm::k,pyym::ou}},//劶 kou
{1,0,{pysm::y,pyym::ang}},//劷 yang
{1,0,{pysm::w,pyym::a}},//劸 wa
{1,0,{pysm::x,pyym::iao}},//効 xiao
{1,0,{pysm::m,pyym::ou}},//劺 mou
{1,0,{pysm::k,pyym::uang}},//劻 kuang
{1,0,{pysm::j,pyym::ie}},//劼 jie
{1,0,{pysm::l,pyym::ie}},//劽 lie
{2,233,{pysm::nop,pyym::nop}},//劾 he
{1,0,{pysm::sh,pyym::i}},//势 shi
{1,0,{pysm::k,pyym::e}},//勀 ke
{2,234,{pysm::nop,pyym::nop}},//勁 jin
{1,0,{pysm::g,pyym::ao}},//勂 gao
{1,0,{pysm::b,pyym::o}},//勃 bo
{1,0,{pysm::m,pyym::in}},//勄 min
{1,0,{pysm::ch,pyym::i}},//勅 chi
{1,0,{pysm::l,pyym::ang}},//勆 lang
{1,0,{pysm::y,pyym::ong}},//勇 yong
{1,0,{pysm::y,pyym::ong}},//勈 yong
{1,0,{pysm::m,pyym::ian}},//勉 mian
{1,0,{pysm::k,pyym::e}},//勊 ke
{1,0,{pysm::x,pyym::un}},//勋 xun
{1,0,{pysm::j,pyym::uan}},//勌 juan
{1,0,{pysm::q,pyym::ing}},//勍 qing
{1,0,{pysm::l,pyym::u}},//勎 lu
{1,0,{pysm::b,pyym::u}},//勏 bu
{1,0,{pysm::m,pyym::eng}},//勐 meng
{2,235,{pysm::nop,pyym::nop}},//勑 chi
{2,236,{pysm::nop,pyym::nop}},//勒 lei
{1,0,{pysm::k,pyym::ai}},//勓 kai
{1,0,{pysm::m,pyym::ian}},//勔 mian
{1,0,{pysm::d,pyym::ong}},//動 dong
{2,237,{pysm::nop,pyym::nop}},//勖 xu
{1,0,{pysm::x,pyym::u}},//勗 xu
{1,0,{pysm::k,pyym::an}},//勘 kan
{2,238,{pysm::nop,pyym::nop}},//務 wu
{1,0,{pysm::y,pyym::i}},//勚 yi
{1,0,{pysm::x,pyym::un}},//勛 xun
{2,239,{pysm::nop,pyym::nop}},//勜 weng
{1,0,{pysm::sh,pyym::eng}},//勝 sheng
{2,240,{pysm::nop,pyym::nop}},//勞 lao
{2,241,{pysm::nop,pyym::nop}},//募 mu
{1,0,{pysm::l,pyym::u}},//勠 lu
{1,0,{pysm::p,pyym::iao}},//勡 piao
{1,0,{pysm::sh,pyym::i}},//勢 shi
{1,0,{pysm::j,pyym::i}},//勣 ji
{2,242,{pysm::nop,pyym::nop}},//勤 qin
{2,243,{pysm::nop,pyym::nop}},//勥 jiang
{2,244,{pysm::nop,pyym::nop}},//勦 chao
{1,0,{pysm::q,pyym::uan}},//勧 quan
{1,0,{pysm::x,pyym::iang}},//勨 xiang
{1,0,{pysm::y,pyym::i}},//勩 yi
{1,0,{pysm::j,pyym::ue}},//勪 jue
{1,0,{pysm::f,pyym::an}},//勫 fan
{1,0,{pysm::j,pyym::uan}},//勬 juan
{2,245,{pysm::nop,pyym::nop}},//勭 tong
{1,0,{pysm::j,pyym::u}},//勮 ju
{1,0,{pysm::d,pyym::an}},//勯 dan
{1,0,{pysm::x,pyym::ie}},//勰 xie
{1,0,{pysm::m,pyym::ai}},//勱 mai
{1,0,{pysm::x,pyym::un}},//勲 xun
{1,0,{pysm::x,pyym::un}},//勳 xun
{1,0,{pysm::l,pyym::v}},//勴 lü
{1,0,{pysm::l,pyym::i}},//勵 li
{1,0,{pysm::ch,pyym::e}},//勶 che
{2,246,{pysm::nop,pyym::nop}},//勷 rang
{1,0,{pysm::q,pyym::uan}},//勸 quan
{1,0,{pysm::b,pyym::ao}},//勹 bao
{4,11,{pysm::nop,pyym::nop}},//勺 shao
{1,0,{pysm::y,pyym::un}},//勻 yun
{1,0,{pysm::j,pyym::iu}},//勼 jiu
{1,0,{pysm::b,pyym::ao}},//勽 bao
{1,0,{pysm::g,pyym::ou}},//勾 gou
{2,247,{pysm::nop,pyym::nop}},//勿 wu
{2,248,{pysm::nop,pyym::nop}},//匀 yun
{1,0,{pysm::w,pyym::en}},//匁 wen
{1,0,{pysm::x,pyym::iong}},//匂 xiong
{1,0,{pysm::g,pyym::ai}},//匃 gai
{1,0,{pysm::g,pyym::ai}},//匄 gai
{3,50,{pysm::nop,pyym::nop}},//包 bao
{1,0,{pysm::c,pyym::ong}},//匆 cong
{1,0,{pysm::y,pyym::i}},//匇 yi
{1,0,{pysm::x,pyym::iong}},//匈 xiong
{1,0,{pysm::p,pyym::eng}},//匉 peng
{1,0,{pysm::j,pyym::u}},//匊 ju
{2,249,{pysm::nop,pyym::nop}},//匋 tao
{1,0,{pysm::g,pyym::e}},//匌 ge
{1,0,{pysm::p,pyym::u}},//匍 pu
{1,0,{pysm::nop,pyym::e}},//匎 e
{1,0,{pysm::p,pyym::ao}},//匏 pao
{1,0,{pysm::f,pyym::u}},//匐 fu
{1,0,{pysm::g,pyym::ong}},//匑 gong
{1,0,{pysm::d,pyym::a}},//匒 da
{1,0,{pysm::j,pyym::iu}},//匓 jiu
{1,0,{pysm::g,pyym::ong}},//匔 gong
{2,250,{pysm::nop,pyym::nop}},//匕 bi
{2,251,{pysm::nop,pyym::nop}},//化 hua
{1,0,{pysm::b,pyym::ei}},//北 bei
{1,0,{pysm::n,pyym::ao}},//匘 nao
{2,252,{pysm::nop,pyym::nop}},//匙 shi
{1,0,{pysm::f,pyym::ang}},//匚 fang
{1,0,{pysm::j,pyym::iu}},//匛 jiu
{1,0,{pysm::y,pyym::i}},//匜 yi
{1,0,{pysm::z,pyym::a}},//匝 za
{1,0,{pysm::j,pyym::iang}},//匞 jiang
{1,0,{pysm::k,pyym::ang}},//匟 kang
{1,0,{pysm::j,pyym::iang}},//匠 jiang
{2,253,{pysm::nop,pyym::nop}},//匡 kuang
{1,0,{pysm::h,pyym::u}},//匢 hu
{1,0,{pysm::x,pyym::ia}},//匣 xia
{1,0,{pysm::q,pyym::u}},//匤 qu
{1,0,{pysm::f,pyym::an}},//匥 fan
{1,0,{pysm::g,pyym::ui}},//匦 gui
{1,0,{pysm::q,pyym::ie}},//匧 qie
{2,254,{pysm::nop,pyym::nop}},//匨 zang
{1,0,{pysm::k,pyym::uang}},//匩 kuang
{2,255,{pysm::nop,pyym::nop}},//匪 fei
{1,0,{pysm::h,pyym::u}},//匫 hu
{1,0,{pysm::y,pyym::u}},//匬 yu
{1,0,{pysm::g,pyym::ui}},//匭 gui
{2,256,{pysm::nop,pyym::nop}},//匮 kui
{1,0,{pysm::h,pyym::ui}},//匯 hui
{1,0,{pysm::d,pyym::an}},//匰 dan
{2,257,{pysm::nop,pyym::nop}},//匱 gui
{1,0,{pysm::l,pyym::ian}},//匲 lian
{1,0,{pysm::l,pyym::ian}},//匳 lian
{1,0,{pysm::s,pyym::uan}},//匴 suan
{1,0,{pysm::d,pyym::u}},//匵 du
{1,0,{pysm::j,pyym::iu}},//匶 jiu
{1,0,{pysm::j,pyym::ue}},//匷 jue
{1,0,{pysm::x,pyym::i}},//匸 xi
{1,0,{pysm::p,pyym::i}},//匹 pi
{2,258,{pysm::nop,pyym::nop}},//区 qu
{1,0,{pysm::y,pyym::i}},//医 yi
{3,51,{pysm::nop,pyym::nop}},//匼 ke
{1,0,{pysm::y,pyym::an}},//匽 yan
{1,0,{pysm::b,pyym::ian}},//匾 bian
{2,259,{pysm::nop,pyym::nop}},//匿 ni
{5,2,{pysm::nop,pyym::nop}},//區 qu
{1,0,{pysm::sh,pyym::i}},//十 shi
{1,0,{pysm::x,pyym::un}},//卂 xun
{1,0,{pysm::q,pyym::ian}},//千 qian
{1,0,{pysm::n,pyym::ian}},//卄 nian
{1,0,{pysm::s,pyym::a}},//卅 sa
{1,0,{pysm::z,pyym::u}},//卆 zu
{1,0,{pysm::sh,pyym::eng}},//升 sheng
{1,0,{pysm::w,pyym::u}},//午 wu
{1,0,{pysm::h,pyym::ui}},//卉 hui
{2,260,{pysm::nop,pyym::nop}},//半 ban
{1,0,{pysm::sh,pyym::i}},//卋 shi
{1,0,{pysm::x,pyym::i}},//卌 xi
{1,0,{pysm::w,pyym::an}},//卍 wan
{1,0,{pysm::h,pyym::ua}},//华 hua
{1,0,{pysm::x,pyym::ie}},//协 xie
{1,0,{pysm::w,pyym::an}},//卐 wan
{4,12,{pysm::nop,pyym::nop}},//卑 bei
{3,52,{pysm::nop,pyym::nop}},//卒 zu
{1,0,{pysm::zh,pyym::uo}},//卓 zhuo
{1,0,{pysm::x,pyym::ie}},//協 xie
{3,53,{pysm::nop,pyym::nop}},//单 dan
{1,0,{pysm::m,pyym::ai}},//卖 mai
{2,261,{pysm::nop,pyym::nop}},//南 nan
{1,0,{pysm::d,pyym::an}},//単 dan
{2,262,{pysm::nop,pyym::nop}},//卙 ji
{1,0,{pysm::b,pyym::o}},//博 bo
{1,0,{pysm::sh,pyym::uai}},//卛 shuai
{3,54,{pysm::nop,pyym::nop}},//卜 bo
{2,263,{pysm::nop,pyym::nop}},//卝 kuang
{2,264,{pysm::nop,pyym::nop}},//卞 bian
{2,265,{pysm::nop,pyym::nop}},//卟 bu
{2,266,{pysm::nop,pyym::nop}},//占 zhan
{2,267,{pysm::nop,pyym::nop}},//卡 ka
{1,0,{pysm::l,pyym::u}},//卢 lu
{1,0,{pysm::y,pyym::ou}},//卣 you
{2,268,{pysm::nop,pyym::nop}},//卤 lu
{1,0,{pysm::x,pyym::i}},//卥 xi
{1,0,{pysm::g,pyym::ua}},//卦 gua
{1,0,{pysm::w,pyym::o}},//卧 wo
{1,0,{pysm::x,pyym::ie}},//卨 xie
{1,0,{pysm::j,pyym::ie}},//卩 jie
{1,0,{pysm::j,pyym::ie}},//卪 jie
{1,0,{pysm::w,pyym::ei}},//卫 wei
{2,269,{pysm::nop,pyym::nop}},//卬 ang
{1,0,{pysm::q,pyym::iong}},//卭 qiong
{1,0,{pysm::zh,pyym::i}},//卮 zhi
{1,0,{pysm::m,pyym::ao}},//卯 mao
{2,270,{pysm::nop,pyym::nop}},//印 yin
{1,0,{pysm::w,pyym::ei}},//危 wei
{1,0,{pysm::sh,pyym::ao}},//卲 shao
{1,0,{pysm::j,pyym::i}},//即 ji
{1,0,{pysm::q,pyym::ue}},//却 que
{2,271,{pysm::nop,pyym::nop}},//卵 luan
{1,0,{pysm::ch,pyym::i}},//卶 chi
{4,13,{pysm::nop,pyym::nop}},//卷 juan
{1,0,{pysm::x,pyym::ie}},//卸 xie
{2,272,{pysm::nop,pyym::nop}},//卹 xu
{1,0,{pysm::j,pyym::in}},//卺 jin
{3,55,{pysm::nop,pyym::nop}},//卻 que
{1,0,{pysm::w,pyym::u}},//卼 wu
{1,0,{pysm::j,pyym::i}},//卽 ji
{1,0,{pysm::nop,pyym::e}},//卾 e
{1,0,{pysm::q,pyym::ing}},//卿 qing
{1,0,{pysm::x,pyym::i}},//厀 xi
{1,0,{pysm::s,pyym::an}},//厁 san
{4,14,{pysm::nop,pyym::nop}},//厂 chang
{2,273,{pysm::nop,pyym::nop}},//厃 wei
{1,0,{pysm::nop,pyym::e}},//厄 e
{1,0,{pysm::t,pyym::ing}},//厅 ting
{1,0,{pysm::l,pyym::i}},//历 li
{2,274,{pysm::nop,pyym::nop}},//厇 zhe
{2,275,{pysm::nop,pyym::nop}},//厈 han
{1,0,{pysm::l,pyym::i}},//厉 li
{1,0,{pysm::y,pyym::a}},//厊 ya
{1,0,{pysm::y,pyym::a}},//压 ya
{1,0,{pysm::y,pyym::an}},//厌 yan
{1,0,{pysm::sh,pyym::e}},//厍 she
{2,276,{pysm::nop,pyym::nop}},//厎 di
{2,277,{pysm::nop,pyym::nop}},//厏 zha
{1,0,{pysm::p,pyym::ang}},//厐 pang
{1,0,{pysm::y,pyym::a}},//厑 ya
{1,0,{pysm::q,pyym::ie}},//厒 qie
{2,278,{pysm::nop,pyym::nop}},//厓 ya
{2,279,{pysm::nop,pyym::nop}},//厔 zhi
{2,280,{pysm::nop,pyym::nop}},//厕 ce
{2,281,{pysm::nop,pyym::nop}},//厖 pang
{1,0,{pysm::t,pyym::i}},//厗 ti
{2,282,{pysm::nop,pyym::nop}},//厘 li
{1,0,{pysm::sh,pyym::e}},//厙 she
{1,0,{pysm::h,pyym::ou}},//厚 hou
{1,0,{pysm::t,pyym::ing}},//厛 ting
{1,0,{pysm::z,pyym::ui}},//厜 zui
{2,283,{pysm::nop,pyym::nop}},//厝 cuo
{1,0,{pysm::f,pyym::ei}},//厞 fei
{1,0,{pysm::y,pyym::uan}},//原 yuan
{1,0,{pysm::c,pyym::e}},//厠 ce
{1,0,{pysm::y,pyym::uan}},//厡 yuan
{1,0,{pysm::x,pyym::iang}},//厢 xiang
{1,0,{pysm::y,pyym::an}},//厣 yan
{1,0,{pysm::l,pyym::i}},//厤 li
{1,0,{pysm::j,pyym::ue}},//厥 jue
{2,284,{pysm::nop,pyym::nop}},//厦 sha
{1,0,{pysm::d,pyym::ian}},//厧 dian
{1,0,{pysm::ch,pyym::u}},//厨 chu
{1,0,{pysm::j,pyym::iu}},//厩 jiu
{1,0,{pysm::j,pyym::in}},//厪 jin
{1,0,{pysm::nop,pyym::ao}},//厫 ao
{1,0,{pysm::g,pyym::ui}},//厬 gui
{3,56,{pysm::nop,pyym::nop}},//厭 yan
{1,0,{pysm::s,pyym::i}},//厮 si
{1,0,{pysm::l,pyym::i}},//厯 li
{1,0,{pysm::ch,pyym::ang}},//厰 chang
{2,285,{pysm::nop,pyym::nop}},//厱 lan
{2,286,{pysm::nop,pyym::nop}},//厲 li
{1,0,{pysm::y,pyym::an}},//厳 yan
{1,0,{pysm::y,pyym::an}},//厴 yan
{1,0,{pysm::y,pyym::uan}},//厵 yuan
{2,287,{pysm::nop,pyym::nop}},//厶 si
{2,288,{pysm::nop,pyym::nop}},//厷 gong
{2,289,{pysm::nop,pyym::nop}},//厸 lin
{2,290,{pysm::nop,pyym::nop}},//厹 rou
{1,0,{pysm::q,pyym::u}},//厺 qu
{1,0,{pysm::q,pyym::u}},//去 qu
{1,0,{pysm::nop,pyym::er}},//厼 er
{1,0,{pysm::l,pyym::ei}},//厽 lei
{1,0,{pysm::d,pyym::u}},//厾 du
{1,0,{pysm::x,pyym::ian}},//县 xian
{2,291,{pysm::nop,pyym::nop}},//叀 zhuan
{1,0,{pysm::s,pyym::an}},//叁 san
{3,57,{pysm::nop,pyym::nop}},//参 can
{4,15,{pysm::nop,pyym::nop}},//參 can
{1,0,{pysm::c,pyym::an}},//叄 can
{1,0,{pysm::c,pyym::an}},//叅 can
{1,0,{pysm::nop,pyym::ai}},//叆 ai
{1,0,{pysm::d,pyym::ai}},//叇 dai
{1,0,{pysm::y,pyym::ou}},//又 you
{1,0,{pysm::ch,pyym::a}},//叉 cha
{1,0,{pysm::j,pyym::i}},//及 ji
{1,0,{pysm::y,pyym::ou}},//友 you
{1,0,{pysm::sh,pyym::uang}},//双 shuang
{1,0,{pysm::f,pyym::an}},//反 fan
{1,0,{pysm::sh,pyym::ou}},//収 shou
{1,0,{pysm::g,pyym::uai}},//叏 guai
{1,0,{pysm::b,pyym::a}},//叐 ba
{1,0,{pysm::f,pyym::a}},//发 fa
{1,0,{pysm::r,pyym::uo}},//叒 ruo
{2,292,{pysm::nop,pyym::nop}},//叓 shi
{1,0,{pysm::sh,pyym::u}},//叔 shu
{4,16,{pysm::nop,pyym::nop}},//叕 zhuo
{1,0,{pysm::q,pyym::u}},//取 qu
{2,293,{pysm::nop,pyym::nop}},//受 shou
{1,0,{pysm::b,pyym::ian}},//变 bian
{1,0,{pysm::x,pyym::u}},//叙 xu
{2,294,{pysm::nop,pyym::nop}},//叚 jia
{1,0,{pysm::p,pyym::an}},//叛 pan
{1,0,{pysm::s,pyym::ou}},//叜 sou
{1,0,{pysm::j,pyym::i}},//叝 ji
{1,0,{pysm::w,pyym::ei}},//叞 wei
{2,295,{pysm::nop,pyym::nop}},//叟 sou
{1,0,{pysm::d,pyym::ie}},//叠 die
{1,0,{pysm::r,pyym::ui}},//叡 rui
{1,0,{pysm::c,pyym::ong}},//叢 cong
{1,0,{pysm::k,pyym::ou}},//口 kou
{2,296,{pysm::nop,pyym::nop}},//古 gu
{3,58,{pysm::nop,pyym::nop}},//句 ju
{1,0,{pysm::l,pyym::ing}},//另 ling
{1,0,{pysm::g,pyym::ua}},//叧 gua
{2,297,{pysm::nop,pyym::nop}},//叨 dao
{1,0,{pysm::k,pyym::ou}},//叩 kou
{1,0,{pysm::zh,pyym::i}},//只 zhi
{1,0,{pysm::j,pyym::iao}},//叫 jiao
{2,298,{pysm::nop,pyym::nop}},//召 zhao
{2,299,{pysm::nop,pyym::nop}},//叭 ba
{1,0,{pysm::d,pyym::ing}},//叮 ding
{2,300,{pysm::nop,pyym::nop}},//可 ke
{3,59,{pysm::nop,pyym::nop}},//台 tai
{3,60,{pysm::nop,pyym::nop}},//叱 chi
{1,0,{pysm::sh,pyym::i}},//史 shi
{1,0,{pysm::y,pyym::ou}},//右 you
{1,0,{pysm::q,pyym::iu}},//叴 qiu
{1,0,{pysm::p,pyym::o}},//叵 po
{2,301,{pysm::nop,pyym::nop}},//叶 ye
{2,302,{pysm::nop,pyym::nop}},//号 hao
{2,303,{pysm::nop,pyym::nop}},//司 si
{3,61,{pysm::nop,pyym::nop}},//叹 tan
{1,0,{pysm::ch,pyym::i}},//叺 chi
{2,304,{pysm::nop,pyym::nop}},//叻 le
{1,0,{pysm::d,pyym::iao}},//叼 diao
{2,305,{pysm::nop,pyym::nop}},//叽 ji
{1,0,{pysm::l,pyym::iao}},//叾 liao
{1,0,{pysm::h,pyym::ong}},//叿 hong
{1,0,{pysm::m,pyym::ie}},//吀 mie
{2,306,{pysm::nop,pyym::nop}},//吁 xu
{1,0,{pysm::m,pyym::ang}},//吂 mang
{2,307,{pysm::nop,pyym::nop}},//吃 chi
{1,0,{pysm::g,pyym::e}},//各 ge
{2,308,{pysm::nop,pyym::nop}},//吅 xuan
{1,0,{pysm::y,pyym::ao}},//吆 yao
{2,309,{pysm::nop,pyym::nop}},//吇 zi
{2,310,{pysm::nop,pyym::nop}},//合 he
{1,0,{pysm::j,pyym::i}},//吉 ji
{1,0,{pysm::d,pyym::iao}},//吊 diao
{3,62,{pysm::nop,pyym::nop}},//吋 cun
{1,0,{pysm::t,pyym::ong}},//同 tong
{1,0,{pysm::m,pyym::ing}},//名 ming
{1,0,{pysm::h,pyym::ou}},//后 hou
{1,0,{pysm::l,pyym::i}},//吏 li
{1,0,{pysm::t,pyym::u}},//吐 tu
{1,0,{pysm::x,pyym::iang}},//向 xiang
{1,0,{pysm::zh,pyym::a}},//吒 zha
{3,63,{pysm::nop,pyym::nop}},//吓 xia
{1,0,{pysm::y,pyym::e}},//吔 ye
{1,0,{pysm::l,pyym::v}},//吕 lü
{2,311,{pysm::nop,pyym::nop}},//吖 ya
{1,0,{pysm::m,pyym::a}},//吗 ma
{1,0,{pysm::nop,pyym::ou}},//吘 ou
{1,0,{pysm::h,pyym::uo}},//吙 huo
{2,312,{pysm::nop,pyym::nop}},//吚 yi
{1,0,{pysm::j,pyym::un}},//君 jun
{1,0,{pysm::ch,pyym::ou}},//吜 chou
{1,0,{pysm::l,pyym::in}},//吝 lin
{2,313,{pysm::nop,pyym::nop}},//吞 tun
{2,314,{pysm::nop,pyym::nop}},//吟 yin
{1,0,{pysm::f,pyym::ei}},//吠 fei
{2,315,{pysm::nop,pyym::nop}},//吡 bi
{1,0,{pysm::q,pyym::in}},//吢 qin
{1,0,{pysm::q,pyym::in}},//吣 qin
{3,64,{pysm::nop,pyym::nop}},//吤 jie
{2,316,{pysm::nop,pyym::nop}},//吥 bu
{2,317,{pysm::nop,pyym::nop}},//否 fou
{2,318,{pysm::nop,pyym::nop}},//吧 ba
{2,319,{pysm::nop,pyym::nop}},//吨 dun
{2,320,{pysm::nop,pyym::nop}},//吩 fen
{2,321,{pysm::nop,pyym::nop}},//吪 e
{1,0,{pysm::h,pyym::an}},//含 han
{3,65,{pysm::nop,pyym::nop}},//听 ting
{2,322,{pysm::nop,pyym::nop}},//吭 keng
{1,0,{pysm::sh,pyym::un}},//吮 shun
{1,0,{pysm::q,pyym::i}},//启 qi
{1,0,{pysm::h,pyym::ong}},//吰 hong
{3,66,{pysm::nop,pyym::nop}},//吱 zhi
{2,323,{pysm::nop,pyym::nop}},//吲 yin
{2,324,{pysm::nop,pyym::nop}},//吳 wu
{2,325,{pysm::nop,pyym::nop}},//吴 wu
{2,326,{pysm::nop,pyym::nop}},//吵 chao
{1,0,{pysm::n,pyym::a}},//吶 na
{3,67,{pysm::nop,pyym::nop}},//吷 xue
{1,0,{pysm::x,pyym::i}},//吸 xi
{1,0,{pysm::ch,pyym::ui}},//吹 chui
{2,327,{pysm::nop,pyym::nop}},//吺 dou
{1,0,{pysm::w,pyym::en}},//吻 wen
{1,0,{pysm::h,pyym::ou}},//吼 hou
{3,68,{pysm::nop,pyym::nop}},//吽 hong
{3,69,{pysm::nop,pyym::nop}},//吾 wu
{1,0,{pysm::g,pyym::ao}},//吿 gao
{2,328,{pysm::nop,pyym::nop}},//呀 ya
{1,0,{pysm::j,pyym::un}},//呁 jun
{1,0,{pysm::l,pyym::v}},//呂 lü
{2,329,{pysm::nop,pyym::nop}},//呃 e
{1,0,{pysm::g,pyym::e}},//呄 ge
{2,330,{pysm::nop,pyym::nop}},//呅 mei
{3,70,{pysm::nop,pyym::nop}},//呆 dai
{2,331,{pysm::nop,pyym::nop}},//呇 qi
{2,332,{pysm::nop,pyym::nop}},//呈 cheng
{1,0,{pysm::w,pyym::u}},//呉 wu
{3,71,{pysm::nop,pyym::nop}},//告 gao
{1,0,{pysm::f,pyym::u}},//呋 fu
{1,0,{pysm::j,pyym::iao}},//呌 jiao
{1,0,{pysm::h,pyym::ong}},//呍 hong
{2,333,{pysm::nop,pyym::nop}},//呎 chi
{1,0,{pysm::sh,pyym::eng}},//呏 sheng
{3,72,{pysm::nop,pyym::nop}},//呐 na
{1,0,{pysm::t,pyym::un}},//呑 tun
{2,334,{pysm::nop,pyym::nop}},//呒 wu
{1,0,{pysm::y,pyym::i}},//呓 yi
{2,335,{pysm::nop,pyym::nop}},//呔 dai
{1,0,{pysm::nop,pyym::ou}},//呕 ou
{1,0,{pysm::l,pyym::i}},//呖 li
{2,336,{pysm::nop,pyym::nop}},//呗 bei
{2,337,{pysm::nop,pyym::nop}},//员 yuan
{1,0,{pysm::g,pyym::uo}},//呙 guo
{1,0,{pysm::w,pyym::en}},//呚 wen
{1,0,{pysm::q,pyym::iang}},//呛 qiang
{1,0,{pysm::w,pyym::u}},//呜 wu
{1,0,{pysm::nop,pyym::e}},//呝 e
{1,0,{pysm::sh,pyym::i}},//呞 shi
{1,0,{pysm::j,pyym::uan}},//呟 juan
{1,0,{pysm::p,pyym::en}},//呠 pen
{2,338,{pysm::nop,pyym::nop}},//呡 wen
{2,339,{pysm::nop,pyym::nop}},//呢 ne
{2,340,{pysm::nop,pyym::nop}},//呣 m
{1,0,{pysm::l,pyym::ing}},//呤 ling
{1,0,{pysm::r,pyym::an}},//呥 ran
{1,0,{pysm::y,pyym::ou}},//呦 you
{1,0,{pysm::d,pyym::i}},//呧 di
{1,0,{pysm::zh,pyym::ou}},//周 zhou
{1,0,{pysm::sh,pyym::i}},//呩 shi
{1,0,{pysm::zh,pyym::ou}},//呪 zhou
{2,341,{pysm::nop,pyym::nop}},//呫 tie
{2,342,{pysm::nop,pyym::nop}},//呬 xi
{1,0,{pysm::y,pyym::i}},//呭 yi
{2,343,{pysm::nop,pyym::nop}},//呮 qi
{1,0,{pysm::p,pyym::ing}},//呯 ping
{4,17,{pysm::nop,pyym::nop}},//呰 zi
{2,344,{pysm::nop,pyym::nop}},//呱 gu
{2,345,{pysm::nop,pyym::nop}},//呲 ci
{2,346,{pysm::nop,pyym::nop}},//味 wei
{4,18,{pysm::nop,pyym::nop}},//呴 xu
{5,3,{pysm::nop,pyym::nop}},//呵 he
{3,73,{pysm::nop,pyym::nop}},//呶 nao
{3,74,{pysm::nop,pyym::nop}},//呷 ga
{1,0,{pysm::p,pyym::ei}},//呸 pei
{2,347,{pysm::nop,pyym::nop}},//呹 yi
{2,348,{pysm::nop,pyym::nop}},//呺 xiao
{1,0,{pysm::sh,pyym::en}},//呻 shen
{5,4,{pysm::nop,pyym::nop}},//呼 hu
{1,0,{pysm::m,pyym::ing}},//命 ming
{4,19,{pysm::nop,pyym::nop}},//呾 da
{2,349,{pysm::nop,pyym::nop}},//呿 qu
{2,350,{pysm::nop,pyym::nop}},//咀 ju
{3,75,{pysm::nop,pyym::nop}},//咁 gan
{1,0,{pysm::z,pyym::a}},//咂 za
{1,0,{pysm::t,pyym::uo}},//咃 tuo
{1,0,{pysm::d,pyym::uo}},//咄 duo
{1,0,{pysm::p,pyym::ou}},//咅 pou
{1,0,{pysm::p,pyym::ao}},//咆 pao
{2,351,{pysm::nop,pyym::nop}},//咇 bie
{1,0,{pysm::f,pyym::u}},//咈 fu
{1,0,{pysm::y,pyym::ang}},//咉 yang
{1,0,{pysm::h,pyym::e}},//咊 he
{3,76,{pysm::nop,pyym::nop}},//咋 za
{3,77,{pysm::nop,pyym::nop}},//和 he
{2,352,{pysm::nop,pyym::nop}},//咍 hai
{2,353,{pysm::nop,pyym::nop}},//咎 jiu
{1,0,{pysm::y,pyym::ong}},//咏 yong
{1,0,{pysm::f,pyym::u}},//咐 fu
{1,0,{pysm::d,pyym::a}},//咑 da
{1,0,{pysm::zh,pyym::ou}},//咒 zhou
{1,0,{pysm::w,pyym::a}},//咓 wa
{2,354,{pysm::nop,pyym::nop}},//咔 ka
{1,0,{pysm::g,pyym::u}},//咕 gu
{3,78,{pysm::nop,pyym::nop}},//咖 ka
{1,0,{pysm::z,pyym::uo}},//咗 zuo
{1,0,{pysm::b,pyym::u}},//咘 bu
{1,0,{pysm::l,pyym::ong}},//咙 long
{1,0,{pysm::d,pyym::ong}},//咚 dong
{1,0,{pysm::n,pyym::ing}},//咛 ning
{1,0,{pysm::t,pyym::a}},//咜 ta
{1,0,{pysm::s,pyym::i}},//咝 si
{1,0,{pysm::x,pyym::ian}},//咞 xian
{1,0,{pysm::h,pyym::uo}},//咟 huo
{1,0,{pysm::q,pyym::i}},//咠 qi
{1,0,{pysm::nop,pyym::er}},//咡 er
{1,0,{pysm::nop,pyym::e}},//咢 e
{2,355,{pysm::nop,pyym::nop}},//咣 guang
{1,0,{pysm::zh,pyym::a}},//咤 zha
{3,79,{pysm::nop,pyym::nop}},//咥 xi
{2,356,{pysm::nop,pyym::nop}},//咦 yi
{1,0,{pysm::l,pyym::ie}},//咧 lie
{1,0,{pysm::z,pyym::i}},//咨 zi
{1,0,{pysm::m,pyym::ie}},//咩 mie
{3,80,{pysm::nop,pyym::nop}},//咪 mi
{1,0,{pysm::zh,pyym::i}},//咫 zhi
{2,357,{pysm::nop,pyym::nop}},//咬 yao
{3,81,{pysm::nop,pyym::nop}},//咭 ji
{3,82,{pysm::nop,pyym::nop}},//咮 zhou
{4,20,{pysm::nop,pyym::nop}},//咯 ge
{2,358,{pysm::nop,pyym::nop}},//咰 shu
{2,359,{pysm::nop,pyym::nop}},//咱 zan
{1,0,{pysm::x,pyym::iao}},//咲 xiao
{3,83,{pysm::nop,pyym::nop}},//咳 ke
{2,360,{pysm::nop,pyym::nop}},//咴 hui
{1,0,{pysm::k,pyym::ua}},//咵 kua
{5,5,{pysm::nop,pyym::nop}},//咶 huai
{2,361,{pysm::nop,pyym::nop}},//咷 tao
{2,362,{pysm::nop,pyym::nop}},//咸 xian
{3,84,{pysm::nop,pyym::nop}},//咹 e
{1,0,{pysm::x,pyym::uan}},//咺 xuan
{3,85,{pysm::nop,pyym::nop}},//咻 xiu
{5,6,{pysm::nop,pyym::nop}},//咼 guo
{3,86,{pysm::nop,pyym::nop}},//咽 yan
{1,0,{pysm::l,pyym::ao}},//咾 lao
{1,0,{pysm::y,pyym::i}},//咿 yi
{1,0,{pysm::nop,pyym::ai}},//哀 ai
{1,0,{pysm::p,pyym::in}},//品 pin
{1,0,{pysm::sh,pyym::en}},//哂 shen
{1,0,{pysm::t,pyym::ong}},//哃 tong
{1,0,{pysm::h,pyym::ong}},//哄 hong
{2,363,{pysm::nop,pyym::nop}},//哅 xiong
{4,21,{pysm::nop,pyym::nop}},//哆 duo
{3,87,{pysm::nop,pyym::nop}},//哇 wa
{4,22,{pysm::nop,pyym::nop}},//哈 ha
{1,0,{pysm::z,pyym::ai}},//哉 zai
{1,0,{pysm::y,pyym::ou}},//哊 you
{2,364,{pysm::nop,pyym::nop}},//哋 die
{2,365,{pysm::nop,pyym::nop}},//哌 pai
{1,0,{pysm::x,pyym::iang}},//响 xiang
{1,0,{pysm::nop,pyym::ai}},//哎 ai
{3,88,{pysm::nop,pyym::nop}},//哏 gen
{2,366,{pysm::nop,pyym::nop}},//哐 kuang
{1,0,{pysm::y,pyym::a}},//哑 ya
{1,0,{pysm::d,pyym::a}},//哒 da
{1,0,{pysm::x,pyym::iao}},//哓 xiao
{1,0,{pysm::b,pyym::i}},//哔 bi
{2,367,{pysm::nop,pyym::nop}},//哕 hui
{1,0,{pysm::n,pyym::ian}},//哖 nian
{1,0,{pysm::h,pyym::ua}},//哗 hua
{1,0,{pysm::x,pyym::ing}},//哘 xing
{1,0,{pysm::k,pyym::uai}},//哙 kuai
{1,0,{pysm::d,pyym::uo}},//哚 duo
{1,0,{pysm::f,pyym::en}},//哛 fen
{1,0,{pysm::j,pyym::i}},//哜 ji
{1,0,{pysm::n,pyym::ong}},//哝 nong
{1,0,{pysm::m,pyym::ou}},//哞 mou
{1,0,{pysm::y,pyym::o}},//哟 yo
{1,0,{pysm::h,pyym::ao}},//哠 hao
{2,368,{pysm::nop,pyym::nop}},//員 yuan
{1,0,{pysm::l,pyym::ong}},//哢 long
{1,0,{pysm::p,pyym::ou}},//哣 pou
{1,0,{pysm::m,pyym::ang}},//哤 mang
{1,0,{pysm::g,pyym::e}},//哥 ge
{2,369,{pysm::nop,pyym::nop}},//哦 o
{3,89,{pysm::nop,pyym::nop}},//哧 chi
{3,90,{pysm::nop,pyym::nop}},//哨 shao
{3,91,{pysm::nop,pyym::nop}},//哩 li
{6,0,{pysm::nop,pyym::nop}},//哪 na
{1,0,{pysm::z,pyym::u}},//哫 zu
{1,0,{pysm::h,pyym::e}},//哬 he
{1,0,{pysm::k,pyym::u}},//哭 ku
{2,370,{pysm::nop,pyym::nop}},//哮 xiao
{1,0,{pysm::x,pyym::ian}},//哯 xian
{1,0,{pysm::l,pyym::ao}},//哰 lao
{4,23,{pysm::nop,pyym::nop}},//哱 bo
{1,0,{pysm::zh,pyym::e}},//哲 zhe
{1,0,{pysm::zh,pyym::a}},//哳 zha
{2,371,{pysm::nop,pyym::nop}},//哴 liang
{1,0,{pysm::b,pyym::a}},//哵 ba
{1,0,{pysm::m,pyym::ie}},//哶 mie
{2,372,{pysm::nop,pyym::nop}},//哷 lie
{1,0,{pysm::s,pyym::ui}},//哸 sui
{1,0,{pysm::f,pyym::u}},//哹 fu
{2,373,{pysm::nop,pyym::nop}},//哺 bu
{1,0,{pysm::h,pyym::an}},//哻 han
{2,374,{pysm::nop,pyym::nop}},//哼 heng
{4,24,{pysm::nop,pyym::nop}},//哽 geng
{2,375,{pysm::nop,pyym::nop}},//哾 shuo
{1,0,{pysm::g,pyym::e}},//哿 ge
{1,0,{pysm::y,pyym::ou}},//唀 you
{1,0,{pysm::y,pyym::an}},//唁 yan
{1,0,{pysm::g,pyym::u}},//唂 gu
{1,0,{pysm::g,pyym::u}},//唃 gu
{2,376,{pysm::nop,pyym::nop}},//唄 bei
{1,0,{pysm::h,pyym::an}},//唅 han
{2,377,{pysm::nop,pyym::nop}},//唆 suo
{2,378,{pysm::nop,pyym::nop}},//唇 chun
{1,0,{pysm::y,pyym::i}},//唈 yi
{1,0,{pysm::nop,pyym::ai}},//唉 ai
{2,379,{pysm::nop,pyym::nop}},//唊 jia
{1,0,{pysm::t,pyym::u}},//唋 tu
{3,92,{pysm::nop,pyym::nop}},//唌 xian
{1,0,{pysm::w,pyym::an}},//唍 wan
{1,0,{pysm::l,pyym::i}},//唎 li
{2,380,{pysm::nop,pyym::nop}},//唏 xi
{1,0,{pysm::t,pyym::ang}},//唐 tang
{2,381,{pysm::nop,pyym::nop}},//唑 zuo
{1,0,{pysm::q,pyym::iu}},//唒 qiu
{1,0,{pysm::ch,pyym::e}},//唓 che
{4,25,{pysm::nop,pyym::nop}},//唔 wu
{1,0,{pysm::z,pyym::ao}},//唕 zao
{1,0,{pysm::y,pyym::a}},//唖 ya
{1,0,{pysm::d,pyym::ou}},//唗 dou
{1,0,{pysm::q,pyym::i}},//唘 qi
{1,0,{pysm::d,pyym::i}},//唙 di
{1,0,{pysm::q,pyym::in}},//唚 qin
{2,382,{pysm::nop,pyym::nop}},//唛 ma
{1,0,{pysm::m,pyym::o}},//唜 mo
{2,383,{pysm::nop,pyym::nop}},//唝 gong
{1,0,{pysm::d,pyym::ou}},//唞 dou
{1,0,{pysm::q,pyym::u}},//唟 qu
{1,0,{pysm::l,pyym::ao}},//唠 lao
{2,384,{pysm::nop,pyym::nop}},//唡 liang
{1,0,{pysm::s,pyym::uo}},//唢 suo
{1,0,{pysm::z,pyym::ao}},//唣 zao
{1,0,{pysm::h,pyym::uan}},//唤 huan
{1,0,{pysm::l,pyym::ang}},//唥 lang
{1,0,{pysm::sh,pyym::a}},//唦 sha
{2,385,{pysm::nop,pyym::nop}},//唧 ji
{1,0,{pysm::z,pyym::u}},//唨 zu
{2,386,{pysm::nop,pyym::nop}},//唩 wo
{2,387,{pysm::nop,pyym::nop}},//唪 feng
{2,388,{pysm::nop,pyym::nop}},//唫 jin
{5,7,{pysm::nop,pyym::nop}},//唬 hu
{1,0,{pysm::q,pyym::i}},//唭 qi
{2,389,{pysm::nop,pyym::nop}},//售 shou
{1,0,{pysm::w,pyym::ei}},//唯 wei
{1,0,{pysm::sh,pyym::ua}},//唰 shua
{1,0,{pysm::ch,pyym::ang}},//唱 chang
{2,390,{pysm::nop,pyym::nop}},//唲 er
{1,0,{pysm::l,pyym::i}},//唳 li
{1,0,{pysm::q,pyym::iang}},//唴 qiang
{3,93,{pysm::nop,pyym::nop}},//唵 an
{2,391,{pysm::nop,pyym::nop}},//唶 ze
{2,392,{pysm::nop,pyym::nop}},//唷 yo
{2,393,{pysm::nop,pyym::nop}},//唸 nian
{1,0,{pysm::y,pyym::u}},//唹 yu
{1,0,{pysm::t,pyym::ian}},//唺 tian
{1,0,{pysm::l,pyym::ai}},//唻 lai
{2,394,{pysm::nop,pyym::nop}},//唼 sha
{1,0,{pysm::x,pyym::i}},//唽 xi
{1,0,{pysm::t,pyym::uo}},//唾 tuo
{1,0,{pysm::h,pyym::u}},//唿 hu
{1,0,{pysm::nop,pyym::ai}},//啀 ai
{5,8,{pysm::nop,pyym::nop}},//啁 zhao
{1,0,{pysm::n,pyym::ou}},//啂 nou
{1,0,{pysm::k,pyym::en}},//啃 ken
{2,395,{pysm::nop,pyym::nop}},//啄 zhuo
{2,396,{pysm::nop,pyym::nop}},//啅 zhuo
{1,0,{pysm::sh,pyym::ang}},//商 shang
{3,94,{pysm::nop,pyym::nop}},//啇 di
{3,95,{pysm::nop,pyym::nop}},//啈 heng
{3,96,{pysm::nop,pyym::nop}},//啉 lin
{2,397,{pysm::nop,pyym::nop}},//啊 a
{2,398,{pysm::nop,pyym::nop}},//啋 cai
{2,399,{pysm::nop,pyym::nop}},//啌 xiang
{5,9,{pysm::nop,pyym::nop}},//啍 tun
{1,0,{pysm::w,pyym::u}},//啎 wu
{1,0,{pysm::w,pyym::en}},//問 wen
{5,10,{pysm::nop,pyym::nop}},//啐 cui
{5,11,{pysm::nop,pyym::nop}},//啑 sha
{1,0,{pysm::g,pyym::u}},//啒 gu
{1,0,{pysm::q,pyym::i}},//啓 qi
{1,0,{pysm::q,pyym::i}},//啔 qi
{1,0,{pysm::t,pyym::ao}},//啕 tao
{1,0,{pysm::d,pyym::an}},//啖 dan
{1,0,{pysm::d,pyym::an}},//啗 dan
{2,400,{pysm::nop,pyym::nop}},//啘 ye
{2,401,{pysm::nop,pyym::nop}},//啙 zi
{2,402,{pysm::nop,pyym::nop}},//啚 bi
{1,0,{pysm::c,pyym::ui}},//啛 cui
{3,97,{pysm::nop,pyym::nop}},//啜 chuai
{1,0,{pysm::h,pyym::e}},//啝 he
{2,403,{pysm::nop,pyym::nop}},//啞 ya
{1,0,{pysm::q,pyym::i}},//啟 qi
{1,0,{pysm::zh,pyym::e}},//啠 zhe
{4,26,{pysm::nop,pyym::nop}},//啡 fei
{2,404,{pysm::nop,pyym::nop}},//啢 liang
{1,0,{pysm::x,pyym::ian}},//啣 xian
{1,0,{pysm::p,pyym::i}},//啤 pi
{1,0,{pysm::sh,pyym::a}},//啥 sha
{1,0,{pysm::l,pyym::a}},//啦 la
{1,0,{pysm::z,pyym::e}},//啧 ze
{2,405,{pysm::nop,pyym::nop}},//啨 ying
{1,0,{pysm::g,pyym::ua}},//啩 gua
{1,0,{pysm::p,pyym::a}},//啪 pa
{1,0,{pysm::zh,pyym::e}},//啫 zhe
{1,0,{pysm::s,pyym::e}},//啬 se
{1,0,{pysm::zh,pyym::uan}},//啭 zhuan
{1,0,{pysm::n,pyym::ie}},//啮 nie
{1,0,{pysm::g,pyym::uo}},//啯 guo
{1,0,{pysm::l,pyym::uo}},//啰 luo
{1,0,{pysm::y,pyym::an}},//啱 yan
{1,0,{pysm::d,pyym::i}},//啲 di
{2,406,{pysm::nop,pyym::nop}},//啳 quan
{2,407,{pysm::nop,pyym::nop}},//啴 chan
{1,0,{pysm::b,pyym::o}},//啵 bo
{1,0,{pysm::d,pyym::ing}},//啶 ding
{1,0,{pysm::l,pyym::ang}},//啷 lang
{1,0,{pysm::x,pyym::iao}},//啸 xiao
{1,0,{pysm::j,pyym::u}},//啹 ju
{1,0,{pysm::t,pyym::ang}},//啺 tang
{2,408,{pysm::nop,pyym::nop}},//啻 chi
{1,0,{pysm::t,pyym::i}},//啼 ti
{1,0,{pysm::nop,pyym::an}},//啽 an
{1,0,{pysm::j,pyym::iu}},//啾 jiu
{1,0,{pysm::d,pyym::an}},//啿 dan
{2,409,{pysm::nop,pyym::nop}},//喀 ka
{2,410,{pysm::nop,pyym::nop}},//喁 yong
{1,0,{pysm::w,pyym::ei}},//喂 wei
{1,0,{pysm::n,pyym::an}},//喃 nan
{1,0,{pysm::sh,pyym::an}},//善 shan
{1,0,{pysm::y,pyym::u}},//喅 yu
{1,0,{pysm::zh,pyym::e}},//喆 zhe
{1,0,{pysm::l,pyym::a}},//喇 la
{2,411,{pysm::nop,pyym::nop}},//喈 jie
{1,0,{pysm::h,pyym::ou}},//喉 hou
{3,98,{pysm::nop,pyym::nop}},//喊 han
{3,99,{pysm::nop,pyym::nop}},//喋 die
{1,0,{pysm::zh,pyym::ou}},//喌 zhou
{1,0,{pysm::ch,pyym::ai}},//喍 chai
{1,0,{pysm::w,pyym::ai}},//喎 wai
{2,412,{pysm::nop,pyym::nop}},//喏 nuo
{1,0,{pysm::y,pyym::u}},//喐 yu
{1,0,{pysm::y,pyym::in}},//喑 yin
{2,413,{pysm::nop,pyym::nop}},//喒 za
{1,0,{pysm::y,pyym::ao}},//喓 yao
{3,100,{pysm::nop,pyym::nop}},//喔 o
{1,0,{pysm::m,pyym::ian}},//喕 mian
{1,0,{pysm::h,pyym::u}},//喖 hu
{1,0,{pysm::y,pyym::un}},//喗 yun
{1,0,{pysm::ch,pyym::uan}},//喘 chuan
{2,414,{pysm::nop,pyym::nop}},//喙 hui
{1,0,{pysm::h,pyym::uan}},//喚 huan
{4,27,{pysm::nop,pyym::nop}},//喛 huan
{2,415,{pysm::nop,pyym::nop}},//喜 xi
{3,101,{pysm::nop,pyym::nop}},//喝 he
{1,0,{pysm::j,pyym::i}},//喞 ji
{2,416,{pysm::nop,pyym::nop}},//喟 kui
{2,417,{pysm::nop,pyym::nop}},//喠 zhong
{1,0,{pysm::w,pyym::ei}},//喡 wei
{2,418,{pysm::nop,pyym::nop}},//喢 sha
{1,0,{pysm::x,pyym::u}},//喣 xu
{1,0,{pysm::h,pyym::uang}},//喤 huang
{2,419,{pysm::nop,pyym::nop}},//喥 duo
{2,420,{pysm::nop,pyym::nop}},//喦 nie
{1,0,{pysm::x,pyym::uan}},//喧 xuan
{1,0,{pysm::l,pyym::iang}},//喨 liang
{1,0,{pysm::y,pyym::u}},//喩 yu
{1,0,{pysm::s,pyym::ang}},//喪 sang
{2,421,{pysm::nop,pyym::nop}},//喫 chi
{2,422,{pysm::nop,pyym::nop}},//喬 qiao
{1,0,{pysm::y,pyym::an}},//喭 yan
{5,12,{pysm::nop,pyym::nop}},//單 dan
{2,423,{pysm::nop,pyym::nop}},//喯 pen
{3,102,{pysm::nop,pyym::nop}},//喰 can
{1,0,{pysm::l,pyym::i}},//喱 li
{1,0,{pysm::y,pyym::o}},//喲 yo
{2,424,{pysm::nop,pyym::nop}},//喳 zha
{1,0,{pysm::w,pyym::ei}},//喴 wei
{1,0,{pysm::m,pyym::iao}},//喵 miao
{1,0,{pysm::y,pyym::ing}},//営 ying
{1,0,{pysm::p,pyym::en}},//喷 pen
{1,0,{pysm::b,pyym::u}},//喸 bu
{1,0,{pysm::k,pyym::ui}},//喹 kui
{1,0,{pysm::x,pyym::i}},//喺 xi
{1,0,{pysm::y,pyym::u}},//喻 yu
{1,0,{pysm::j,pyym::ie}},//喼 jie
{1,0,{pysm::l,pyym::ou}},//喽 lou
{1,0,{pysm::k,pyym::u}},//喾 ku
{2,425,{pysm::nop,pyym::nop}},//喿 zao
{1,0,{pysm::h,pyym::u}},//嗀 hu
{1,0,{pysm::t,pyym::i}},//嗁 ti
{1,0,{pysm::y,pyym::ao}},//嗂 yao
{3,103,{pysm::nop,pyym::nop}},//嗃 he
{3,104,{pysm::nop,pyym::nop}},//嗄 a
{1,0,{pysm::x,pyym::iu}},//嗅 xiu
{2,426,{pysm::nop,pyym::nop}},//嗆 qiang
{1,0,{pysm::s,pyym::e}},//嗇 se
{1,0,{pysm::y,pyym::ong}},//嗈 yong
{1,0,{pysm::s,pyym::u}},//嗉 su
{2,427,{pysm::nop,pyym::nop}},//嗊 hong
{1,0,{pysm::x,pyym::ie}},//嗋 xie
{3,105,{pysm::nop,pyym::nop}},//嗌 ai
{2,428,{pysm::nop,pyym::nop}},//嗍 suo
{1,0,{pysm::m,pyym::a}},//嗎 ma
{1,0,{pysm::ch,pyym::a}},//嗏 cha
{1,0,{pysm::h,pyym::ai}},//嗐 hai
{3,106,{pysm::nop,pyym::nop}},//嗑 ke
{2,429,{pysm::nop,pyym::nop}},//嗒 da
{1,0,{pysm::s,pyym::ang}},//嗓 sang
{2,430,{pysm::nop,pyym::nop}},//嗔 chen
{1,0,{pysm::r,pyym::u}},//嗕 ru
{2,431,{pysm::nop,pyym::nop}},//嗖 sou
{2,432,{pysm::nop,pyym::nop}},//嗗 wa
{1,0,{pysm::j,pyym::i}},//嗘 ji
{3,107,{pysm::nop,pyym::nop}},//嗙 pang
{1,0,{pysm::w,pyym::u}},//嗚 wu
{3,108,{pysm::nop,pyym::nop}},//嗛 qian
{1,0,{pysm::sh,pyym::i}},//嗜 shi
{1,0,{pysm::g,pyym::e}},//嗝 ge
{1,0,{pysm::z,pyym::i}},//嗞 zi
{2,433,{pysm::nop,pyym::nop}},//嗟 jie
{1,0,{pysm::l,pyym::ao}},//嗠 lao
{1,0,{pysm::w,pyym::eng}},//嗡 weng
{1,0,{pysm::w,pyym::a}},//嗢 wa
{1,0,{pysm::s,pyym::i}},//嗣 si
{1,0,{pysm::ch,pyym::i}},//嗤 chi
{1,0,{pysm::h,pyym::ao}},//嗥 hao
{1,0,{pysm::s,pyym::uo}},//嗦 suo
{0,0,{pysm::nop,pyym::nop}},//嗧 嗧
{2,434,{pysm::nop,pyym::nop}},//嗨 hai
{1,0,{pysm::s,pyym::uo}},//嗩 suo
{1,0,{pysm::q,pyym::in}},//嗪 qin
{1,0,{pysm::n,pyym::ie}},//嗫 nie
{1,0,{pysm::h,pyym::e}},//嗬 he
{1,0,{pysm::zh,pyym::i}},//嗭 zhi
{1,0,{pysm::s,pyym::ai}},//嗮 sai
{2,435,{pysm::nop,pyym::nop}},//嗯 n
{1,0,{pysm::g,pyym::e}},//嗰 ge
{1,0,{pysm::n,pyym::a}},//嗱 na
{2,436,{pysm::nop,pyym::nop}},//嗲 die
{1,0,{pysm::nop,pyym::ai}},//嗳 ai
{1,0,{pysm::q,pyym::iang}},//嗴 qiang
{1,0,{pysm::t,pyym::ong}},//嗵 tong
{1,0,{pysm::b,pyym::i}},//嗶 bi
{1,0,{pysm::nop,pyym::ao}},//嗷 ao
{1,0,{pysm::nop,pyym::ao}},//嗸 ao
{1,0,{pysm::l,pyym::ian}},//嗹 lian
{2,437,{pysm::nop,pyym::nop}},//嗺 zui
{2,438,{pysm::nop,pyym::nop}},//嗻 zhe
{1,0,{pysm::m,pyym::o}},//嗼 mo
{3,109,{pysm::nop,pyym::nop}},//嗽 sou
{1,0,{pysm::s,pyym::ou}},//嗾 sou
{1,0,{pysm::t,pyym::an}},//嗿 tan
{2,439,{pysm::nop,pyym::nop}},//嘀 di
{3,110,{pysm::nop,pyym::nop}},//嘁 qi
{1,0,{pysm::j,pyym::iao}},//嘂 jiao
{1,0,{pysm::ch,pyym::ong}},//嘃 chong
{2,440,{pysm::nop,pyym::nop}},//嘄 jiao
{2,441,{pysm::nop,pyym::nop}},//嘅 kai
{1,0,{pysm::t,pyym::an}},//嘆 tan
{3,111,{pysm::nop,pyym::nop}},//嘇 shan
{1,0,{pysm::c,pyym::ao}},//嘈 cao
{1,0,{pysm::j,pyym::ia}},//嘉 jia
{1,0,{pysm::nop,pyym::ai}},//嘊 ai
{1,0,{pysm::x,pyym::iao}},//嘋 xiao
{1,0,{pysm::p,pyym::iao}},//嘌 piao
{1,0,{pysm::l,pyym::ou}},//嘍 lou
{1,0,{pysm::g,pyym::a}},//嘎 ga
{2,442,{pysm::nop,pyym::nop}},//嘏 gu
{5,13,{pysm::nop,pyym::nop}},//嘐 xiao
{1,0,{pysm::h,pyym::u}},//嘑 hu
{1,0,{pysm::h,pyym::ui}},//嘒 hui
{1,0,{pysm::g,pyym::uo}},//嘓 guo
{3,112,{pysm::nop,pyym::nop}},//嘔 ou
{1,0,{pysm::x,pyym::ian}},//嘕 xian
{1,0,{pysm::z,pyym::e}},//嘖 ze
{1,0,{pysm::ch,pyym::ang}},//嘗 chang
{2,443,{pysm::nop,pyym::nop}},//嘘 xu
{1,0,{pysm::p,pyym::o}},//嘙 po
{3,113,{pysm::nop,pyym::nop}},//嘚 de
{1,0,{pysm::m,pyym::a}},//嘛 ma
{1,0,{pysm::m,pyym::a}},//嘜 ma
{1,0,{pysm::h,pyym::u}},//嘝 hu
{2,444,{pysm::nop,pyym::nop}},//嘞 lei
{1,0,{pysm::d,pyym::u}},//嘟 du
{1,0,{pysm::g,pyym::a}},//嘠 ga
{1,0,{pysm::t,pyym::ang}},//嘡 tang
{1,0,{pysm::y,pyym::e}},//嘢 ye
{1,0,{pysm::b,pyym::eng}},//嘣 beng
{1,0,{pysm::y,pyym::ing}},//嘤 ying
{1,0,{pysm::s,pyym::ai}},//嘥 sai
{1,0,{pysm::j,pyym::iao}},//嘦 jiao
{1,0,{pysm::m,pyym::i}},//嘧 mi
{1,0,{pysm::x,pyym::iao}},//嘨 xiao
{1,0,{pysm::h,pyym::ua}},//嘩 hua
{1,0,{pysm::m,pyym::ai}},//嘪 mai
{1,0,{pysm::r,pyym::an}},//嘫 ran
{2,445,{pysm::nop,pyym::nop}},//嘬 chuai
{1,0,{pysm::p,pyym::eng}},//嘭 peng
{3,114,{pysm::nop,pyym::nop}},//嘮 lao
{2,446,{pysm::nop,pyym::nop}},//嘯 xiao
{1,0,{pysm::j,pyym::i}},//嘰 ji
{1,0,{pysm::zh,pyym::u}},//嘱 zhu
{2,447,{pysm::nop,pyym::nop}},//嘲 chao
{1,0,{pysm::k,pyym::ui}},//嘳 kui
{1,0,{pysm::z,pyym::ui}},//嘴 zui
{1,0,{pysm::x,pyym::iao}},//嘵 xiao
{1,0,{pysm::s,pyym::i}},//嘶 si
{1,0,{pysm::h,pyym::ao}},//嘷 hao
{3,115,{pysm::nop,pyym::nop}},//嘸 fu
{1,0,{pysm::l,pyym::iao}},//嘹 liao
{1,0,{pysm::q,pyym::iao}},//嘺 qiao
{1,0,{pysm::x,pyym::i}},//嘻 xi
{3,116,{pysm::nop,pyym::nop}},//嘼 chu
{4,28,{pysm::nop,pyym::nop}},//嘽 chan
{2,448,{pysm::nop,pyym::nop}},//嘾 dan
{3,117,{pysm::nop,pyym::nop}},//嘿 hei
{1,0,{pysm::x,pyym::un}},//噀 xun
{3,118,{pysm::nop,pyym::nop}},//噁 e
{1,0,{pysm::z,pyym::un}},//噂 zun
{2,449,{pysm::nop,pyym::nop}},//噃 fan
{1,0,{pysm::ch,pyym::i}},//噄 chi
{1,0,{pysm::h,pyym::ui}},//噅 hui
{2,450,{pysm::nop,pyym::nop}},//噆 zan
{1,0,{pysm::ch,pyym::uang}},//噇 chuang
{3,119,{pysm::nop,pyym::nop}},//噈 cu
{1,0,{pysm::d,pyym::an}},//噉 dan
{1,0,{pysm::y,pyym::u}},//噊 yu
{2,451,{pysm::nop,pyym::nop}},//噋 tun
{2,452,{pysm::nop,pyym::nop}},//噌 ceng
{2,453,{pysm::nop,pyym::nop}},//噍 jiao
{3,120,{pysm::nop,pyym::nop}},//噎 ye
{1,0,{pysm::x,pyym::i}},//噏 xi
{1,0,{pysm::q,pyym::i}},//噐 qi
{1,0,{pysm::h,pyym::ao}},//噑 hao
{1,0,{pysm::l,pyym::ian}},//噒 lian
{1,0,{pysm::x,pyym::u}},//噓 xu
{1,0,{pysm::d,pyym::eng}},//噔 deng
{1,0,{pysm::h,pyym::ui}},//噕 hui
{1,0,{pysm::y,pyym::in}},//噖 yin
{1,0,{pysm::p,pyym::u}},//噗 pu
{1,0,{pysm::j,pyym::ue}},//噘 jue
{1,0,{pysm::q,pyym::in}},//噙 qin
{1,0,{pysm::x,pyym::un}},//噚 xun
{1,0,{pysm::n,pyym::ie}},//噛 nie
{1,0,{pysm::l,pyym::u}},//噜 lu
{1,0,{pysm::s,pyym::i}},//噝 si
{1,0,{pysm::y,pyym::an}},//噞 yan
{1,0,{pysm::y,pyym::ing}},//噟 ying
{1,0,{pysm::d,pyym::a}},//噠 da
{2,454,{pysm::nop,pyym::nop}},//噡 zhan
{3,121,{pysm::nop,pyym::nop}},//噢 o
{4,29,{pysm::nop,pyym::nop}},//噣 zhou
{1,0,{pysm::j,pyym::in}},//噤 jin
{2,455,{pysm::nop,pyym::nop}},//噥 nong
{2,456,{pysm::nop,pyym::nop}},//噦 yue
{1,0,{pysm::x,pyym::ie}},//噧 xie
{1,0,{pysm::q,pyym::i}},//器 qi
{1,0,{pysm::nop,pyym::e}},//噩 e
{1,0,{pysm::z,pyym::ao}},//噪 zao
{2,457,{pysm::nop,pyym::nop}},//噫 yi
{1,0,{pysm::sh,pyym::i}},//噬 shi
{3,122,{pysm::nop,pyym::nop}},//噭 jiao
{1,0,{pysm::y,pyym::uan}},//噮 yuan
{1,0,{pysm::nop,pyym::ai}},//噯 ai
{1,0,{pysm::y,pyym::ong}},//噰 yong
{2,458,{pysm::nop,pyym::nop}},//噱 jue
{4,30,{pysm::nop,pyym::nop}},//噲 kuai
{1,0,{pysm::y,pyym::u}},//噳 yu
{2,459,{pysm::nop,pyym::nop}},//噴 pen
{1,0,{pysm::d,pyym::ao}},//噵 dao
{2,460,{pysm::nop,pyym::nop}},//噶 ga
{3,123,{pysm::nop,pyym::nop}},//噷 hm
{1,0,{pysm::d,pyym::un}},//噸 dun
{1,0,{pysm::d,pyym::ang}},//噹 dang
{1,0,{pysm::x,pyym::in}},//噺 xin
{1,0,{pysm::s,pyym::ai}},//噻 sai
{1,0,{pysm::p,pyym::i}},//噼 pi
{1,0,{pysm::p,pyym::i}},//噽 pi
{1,0,{pysm::y,pyym::in}},//噾 yin
{1,0,{pysm::z,pyym::ui}},//噿 zui
{1,0,{pysm::n,pyym::ing}},//嚀 ning
{1,0,{pysm::d,pyym::i}},//嚁 di
{2,461,{pysm::nop,pyym::nop}},//嚂 lan
{1,0,{pysm::t,pyym::a}},//嚃 ta
{3,124,{pysm::nop,pyym::nop}},//嚄 huo
{1,0,{pysm::r,pyym::u}},//嚅 ru
{1,0,{pysm::h,pyym::ao}},//嚆 hao
{2,462,{pysm::nop,pyym::nop}},//嚇 xia
{1,0,{pysm::y,pyym::e}},//嚈 ye
{1,0,{pysm::d,pyym::uo}},//嚉 duo
{3,125,{pysm::nop,pyym::nop}},//嚊 pi
{2,463,{pysm::nop,pyym::nop}},//嚋 chou
{3,126,{pysm::nop,pyym::nop}},//嚌 ji
{1,0,{pysm::j,pyym::in}},//嚍 jin
{1,0,{pysm::h,pyym::ao}},//嚎 hao
{1,0,{pysm::t,pyym::i}},//嚏 ti
{1,0,{pysm::ch,pyym::ang}},//嚐 chang
{1,0,{pysm::x,pyym::un}},//嚑 xun
{1,0,{pysm::m,pyym::e}},//嚒 me
{2,464,{pysm::nop,pyym::nop}},//嚓 ca
{2,465,{pysm::nop,pyym::nop}},//嚔 ti
{1,0,{pysm::l,pyym::u}},//嚕 lu
{1,0,{pysm::h,pyym::ui}},//嚖 hui
{3,127,{pysm::nop,pyym::nop}},//嚗 bo
{1,0,{pysm::y,pyym::ou}},//嚘 you
{2,466,{pysm::nop,pyym::nop}},//嚙 nie
{1,0,{pysm::y,pyym::in}},//嚚 yin
{2,467,{pysm::nop,pyym::nop}},//嚛 hu
{3,128,{pysm::nop,pyym::nop}},//嚜 me
{1,0,{pysm::h,pyym::ong}},//嚝 hong
{1,0,{pysm::zh,pyym::e}},//嚞 zhe
{1,0,{pysm::l,pyym::i}},//嚟 li
{1,0,{pysm::l,pyym::iu}},//嚠 liu
{1,0,{pysm::h,pyym::ai}},//嚡 hai
{1,0,{pysm::n,pyym::ang}},//嚢 nang
{2,468,{pysm::nop,pyym::nop}},//嚣 xiao
{1,0,{pysm::m,pyym::o}},//嚤 mo
{1,0,{pysm::y,pyym::an}},//嚥 yan
{1,0,{pysm::l,pyym::i}},//嚦 li
{1,0,{pysm::l,pyym::u}},//嚧 lu
{1,0,{pysm::l,pyym::ong}},//嚨 long
{1,0,{pysm::m,pyym::o}},//嚩 mo
{1,0,{pysm::d,pyym::an}},//嚪 dan
{1,0,{pysm::ch,pyym::en}},//嚫 chen
{1,0,{pysm::p,pyym::in}},//嚬 pin
{1,0,{pysm::p,pyym::i}},//嚭 pi
{1,0,{pysm::x,pyym::iang}},//嚮 xiang
{2,469,{pysm::nop,pyym::nop}},//嚯 huo
{1,0,{pysm::m,pyym::o}},//嚰 mo
{1,0,{pysm::x,pyym::i}},//嚱 xi
{1,0,{pysm::d,pyym::uo}},//嚲 duo
{1,0,{pysm::k,pyym::u}},//嚳 ku
{1,0,{pysm::y,pyym::an}},//嚴 yan
{1,0,{pysm::ch,pyym::an}},//嚵 chan
{1,0,{pysm::y,pyym::ing}},//嚶 ying
{1,0,{pysm::r,pyym::ang}},//嚷 rang
{1,0,{pysm::d,pyym::ian}},//嚸 dian
{1,0,{pysm::l,pyym::a}},//嚹 la
{1,0,{pysm::t,pyym::a}},//嚺 ta
{1,0,{pysm::x,pyym::iao}},//嚻 xiao
{2,470,{pysm::nop,pyym::nop}},//嚼 jue
{1,0,{pysm::ch,pyym::uo}},//嚽 chuo
{1,0,{pysm::h,pyym::uan}},//嚾 huan
{1,0,{pysm::h,pyym::uo}},//嚿 huo
{1,0,{pysm::zh,pyym::uan}},//囀 zhuan
{2,471,{pysm::nop,pyym::nop}},//囁 nie
{2,472,{pysm::nop,pyym::nop}},//囂 xiao
{3,129,{pysm::nop,pyym::nop}},//囃 ca
{1,0,{pysm::l,pyym::i}},//囄 li
{1,0,{pysm::ch,pyym::an}},//囅 chan
{1,0,{pysm::ch,pyym::ai}},//囆 chai
{1,0,{pysm::l,pyym::i}},//囇 li
{1,0,{pysm::y,pyym::i}},//囈 yi
{1,0,{pysm::l,pyym::uo}},//囉 luo
{1,0,{pysm::n,pyym::ang}},//囊 nang
{3,130,{pysm::nop,pyym::nop}},//囋 za
{1,0,{pysm::s,pyym::u}},//囌 su
{1,0,{pysm::x,pyym::i}},//囍 xi
{1,0,{pysm::z,pyym::en}},//囎 zen
{1,0,{pysm::j,pyym::ian}},//囏 jian
{4,31,{pysm::nop,pyym::nop}},//囐 za
{1,0,{pysm::zh,pyym::u}},//囑 zhu
{1,0,{pysm::l,pyym::an}},//囒 lan
{1,0,{pysm::n,pyym::ie}},//囓 nie
{1,0,{pysm::n,pyym::ang}},//囔 nang
{1,0,{pysm::l,pyym::an}},//囕 lan
{1,0,{pysm::l,pyym::o}},//囖 lo
{2,473,{pysm::nop,pyym::nop}},//囗 wei
{1,0,{pysm::h,pyym::ui}},//囘 hui
{1,0,{pysm::y,pyym::in}},//囙 yin
{1,0,{pysm::q,pyym::iu}},//囚 qiu
{1,0,{pysm::s,pyym::i}},//四 si
{1,0,{pysm::n,pyym::in}},//囜 nin
{3,131,{pysm::nop,pyym::nop}},//囝 jian
{1,0,{pysm::h,pyym::ui}},//回 hui
{1,0,{pysm::x,pyym::in}},//囟 xin
{1,0,{pysm::y,pyym::in}},//因 yin
{2,474,{pysm::nop,pyym::nop}},//囡 nan
{2,475,{pysm::nop,pyym::nop}},//团 tuan
{1,0,{pysm::t,pyym::uan}},//団 tuan
{2,476,{pysm::nop,pyym::nop}},//囤 dun
{1,0,{pysm::k,pyym::ang}},//囥 kang
{1,0,{pysm::y,pyym::uan}},//囦 yuan
{1,0,{pysm::j,pyym::iong}},//囧 jiong
{1,0,{pysm::p,pyym::ian}},//囨 pian
{1,0,{pysm::y,pyym::un}},//囩 yun
{1,0,{pysm::c,pyym::ong}},//囪 cong
{1,0,{pysm::h,pyym::u}},//囫 hu
{1,0,{pysm::h,pyym::ui}},//囬 hui
{2,477,{pysm::nop,pyym::nop}},//园 yuan
{1,0,{pysm::nop,pyym::e}},//囮 e
{1,0,{pysm::g,pyym::uo}},//囯 guo
{1,0,{pysm::k,pyym::un}},//困 kun
{2,478,{pysm::nop,pyym::nop}},//囱 cong
{1,0,{pysm::t,pyym::ong}},//囲 tong
{1,0,{pysm::t,pyym::u}},//図 tu
{1,0,{pysm::w,pyym::ei}},//围 wei
{1,0,{pysm::l,pyym::un}},//囵 lun
{1,0,{pysm::g,pyym::uo}},//囶 guo
{1,0,{pysm::q,pyym::un}},//囷 qun
{1,0,{pysm::r,pyym::i}},//囸 ri
{1,0,{pysm::l,pyym::ing}},//囹 ling
{1,0,{pysm::g,pyym::u}},//固 gu
{1,0,{pysm::g,pyym::uo}},//囻 guo
{1,0,{pysm::t,pyym::ai}},//囼 tai
{1,0,{pysm::g,pyym::uo}},//国 guo
{1,0,{pysm::t,pyym::u}},//图 tu
{1,0,{pysm::y,pyym::ou}},//囿 you
{1,0,{pysm::g,pyym::uo}},//圀 guo
{1,0,{pysm::y,pyym::in}},//圁 yin
{2,479,{pysm::nop,pyym::nop}},//圂 hun
{1,0,{pysm::p,pyym::u}},//圃 pu
{1,0,{pysm::y,pyym::u}},//圄 yu
{1,0,{pysm::h,pyym::an}},//圅 han
{1,0,{pysm::y,pyym::uan}},//圆 yuan
{1,0,{pysm::l,pyym::un}},//圇 lun
{2,480,{pysm::nop,pyym::nop}},//圈 quan
{1,0,{pysm::y,pyym::u}},//圉 yu
{1,0,{pysm::q,pyym::ing}},//圊 qing
{1,0,{pysm::g,pyym::uo}},//國 guo
{2,481,{pysm::nop,pyym::nop}},//圌 chuan
{1,0,{pysm::w,pyym::ei}},//圍 wei
{1,0,{pysm::y,pyym::uan}},//圎 yuan
{1,0,{pysm::q,pyym::uan}},//圏 quan
{1,0,{pysm::k,pyym::u}},//圐 ku
{1,0,{pysm::p,pyym::u}},//圑 pu
{1,0,{pysm::y,pyym::uan}},//園 yuan
{1,0,{pysm::y,pyym::uan}},//圓 yuan
{1,0,{pysm::y,pyym::a}},//圔 ya
{1,0,{pysm::t,pyym::u}},//圕 tu
{1,0,{pysm::t,pyym::u}},//圖 tu
{1,0,{pysm::t,pyym::u}},//圗 tu
{2,482,{pysm::nop,pyym::nop}},//團 tuan
{1,0,{pysm::l,pyym::ve}},//圙 lüe
{1,0,{pysm::h,pyym::ui}},//圚 hui
{1,0,{pysm::y,pyym::i}},//圛 yi
{2,483,{pysm::nop,pyym::nop}},//圜 huan
{1,0,{pysm::l,pyym::uan}},//圝 luan
{1,0,{pysm::l,pyym::uan}},//圞 luan
{3,132,{pysm::nop,pyym::nop}},//土 tu
{1,0,{pysm::y,pyym::a}},//圠 ya
{1,0,{pysm::t,pyym::u}},//圡 tu
{1,0,{pysm::t,pyym::ing}},//圢 ting
{2,484,{pysm::nop,pyym::nop}},//圣 sheng
{1,0,{pysm::p,pyym::u}},//圤 pu
{1,0,{pysm::l,pyym::u}},//圥 lu
{1,0,{pysm::k,pyym::uai}},//圦 kuai
{1,0,{pysm::y,pyym::a}},//圧 ya
{1,0,{pysm::z,pyym::ai}},//在 zai
{3,133,{pysm::nop,pyym::nop}},//圩 wei
{2,485,{pysm::nop,pyym::nop}},//圪 ge
{3,134,{pysm::nop,pyym::nop}},//圫 yu
{1,0,{pysm::w,pyym::u}},//圬 wu
{1,0,{pysm::g,pyym::ui}},//圭 gui
{1,0,{pysm::p,pyym::i}},//圮 pi
{1,0,{pysm::y,pyym::i}},//圯 yi
{2,486,{pysm::nop,pyym::nop}},//地 di
{2,487,{pysm::nop,pyym::nop}},//圱 qian
{1,0,{pysm::q,pyym::ian}},//圲 qian
{4,32,{pysm::nop,pyym::nop}},//圳 zhen
{1,0,{pysm::zh,pyym::uo}},//圴 zhuo
{1,0,{pysm::d,pyym::ang}},//圵 dang
{1,0,{pysm::q,pyym::ia}},//圶 qia
{1,0,{pysm::x,pyym::ia}},//圷 xia
{1,0,{pysm::sh,pyym::an}},//圸 shan
{1,0,{pysm::k,pyym::uang}},//圹 kuang
{1,0,{pysm::ch,pyym::ang}},//场 chang
{2,488,{pysm::nop,pyym::nop}},//圻 qi
{1,0,{pysm::n,pyym::ie}},//圼 nie
{1,0,{pysm::m,pyym::o}},//圽 mo
{2,489,{pysm::nop,pyym::nop}},//圾 ji
{1,0,{pysm::j,pyym::ia}},//圿 jia
{1,0,{pysm::zh,pyym::i}},//址 zhi
{1,0,{pysm::zh,pyym::i}},//坁 zhi
{1,0,{pysm::b,pyym::an}},//坂 ban
{1,0,{pysm::x,pyym::un}},//坃 xun
{1,0,{pysm::y,pyym::i}},//坄 yi
{1,0,{pysm::q,pyym::in}},//坅 qin
{2,490,{pysm::nop,pyym::nop}},//坆 mei
{2,491,{pysm::nop,pyym::nop}},//均 jun
{2,492,{pysm::nop,pyym::nop}},//坈 rong
{2,493,{pysm::nop,pyym::nop}},//坉 tun
{1,0,{pysm::f,pyym::ang}},//坊 fang
{2,494,{pysm::nop,pyym::nop}},//坋 ben
{1,0,{pysm::b,pyym::en}},//坌 ben
{1,0,{pysm::t,pyym::an}},//坍 tan
{1,0,{pysm::k,pyym::an}},//坎 kan
{3,135,{pysm::nop,pyym::nop}},//坏 huai
{1,0,{pysm::z,pyym::uo}},//坐 zuo
{2,495,{pysm::nop,pyym::nop}},//坑 keng
{1,0,{pysm::b,pyym::i}},//坒 bi
{2,496,{pysm::nop,pyym::nop}},//坓 jing
{2,497,{pysm::nop,pyym::nop}},//坔 di
{1,0,{pysm::j,pyym::ing}},//坕 jing
{1,0,{pysm::j,pyym::i}},//坖 ji
{2,498,{pysm::nop,pyym::nop}},//块 kuai
{1,0,{pysm::d,pyym::i}},//坘 di
{1,0,{pysm::j,pyym::ing}},//坙 jing
{1,0,{pysm::j,pyym::ian}},//坚 jian
{1,0,{pysm::t,pyym::an}},//坛 tan
{1,0,{pysm::l,pyym::i}},//坜 li
{1,0,{pysm::b,pyym::a}},//坝 ba
{1,0,{pysm::w,pyym::u}},//坞 wu
{1,0,{pysm::f,pyym::en}},//坟 fen
{1,0,{pysm::zh,pyym::ui}},//坠 zhui
{1,0,{pysm::p,pyym::o}},//坡 po
{2,499,{pysm::nop,pyym::nop}},//坢 ban
{1,0,{pysm::t,pyym::ang}},//坣 tang
{1,0,{pysm::k,pyym::un}},//坤 kun
{2,500,{pysm::nop,pyym::nop}},//坥 qu
{1,0,{pysm::t,pyym::an}},//坦 tan
{1,0,{pysm::zh,pyym::i}},//坧 zhi
{2,501,{pysm::nop,pyym::nop}},//坨 tuo
{1,0,{pysm::g,pyym::an}},//坩 gan
{1,0,{pysm::p,pyym::ing}},//坪 ping
{2,502,{pysm::nop,pyym::nop}},//坫 dian
{2,503,{pysm::nop,pyym::nop}},//坬 gua
{1,0,{pysm::n,pyym::i}},//坭 ni
{1,0,{pysm::t,pyym::ai}},//坮 tai
{2,504,{pysm::nop,pyym::nop}},//坯 pi
{1,0,{pysm::j,pyym::iong}},//坰 jiong
{1,0,{pysm::y,pyym::ang}},//坱 yang
{1,0,{pysm::f,pyym::o}},//坲 fo
{2,505,{pysm::nop,pyym::nop}},//坳 ao
{1,0,{pysm::l,pyym::u}},//坴 lu
{1,0,{pysm::q,pyym::iu}},//坵 qiu
{2,506,{pysm::nop,pyym::nop}},//坶 mu
{2,507,{pysm::nop,pyym::nop}},//坷 ke
{1,0,{pysm::g,pyym::ou}},//坸 gou
{1,0,{pysm::x,pyym::ue}},//坹 xue
{1,0,{pysm::b,pyym::a}},//坺 ba
{2,508,{pysm::nop,pyym::nop}},//坻 chi
{1,0,{pysm::ch,pyym::e}},//坼 che
{1,0,{pysm::l,pyym::ing}},//坽 ling
{1,0,{pysm::zh,pyym::u}},//坾 zhu
{1,0,{pysm::f,pyym::u}},//坿 fu
{1,0,{pysm::h,pyym::u}},//垀 hu
{1,0,{pysm::zh,pyym::i}},//垁 zhi
{2,509,{pysm::nop,pyym::nop}},//垂 chui
{1,0,{pysm::l,pyym::a}},//垃 la
{1,0,{pysm::l,pyym::ong}},//垄 long
{1,0,{pysm::l,pyym::ong}},//垅 long
{1,0,{pysm::l,pyym::u}},//垆 lu
{1,0,{pysm::nop,pyym::ao}},//垇 ao
{1,0,{pysm::d,pyym::ai}},//垈 dai
{1,0,{pysm::p,pyym::ao}},//垉 pao
{1,0,{pysm::m,pyym::in}},//垊 min
{1,0,{pysm::x,pyym::ing}},//型 xing
{2,510,{pysm::nop,pyym::nop}},//垌 dong
{1,0,{pysm::j,pyym::i}},//垍 ji
{1,0,{pysm::h,pyym::e}},//垎 he
{1,0,{pysm::l,pyym::v}},//垏 lü
{1,0,{pysm::c,pyym::i}},//垐 ci
{1,0,{pysm::ch,pyym::i}},//垑 chi
{1,0,{pysm::l,pyym::ei}},//垒 lei
{1,0,{pysm::g,pyym::ai}},//垓 gai
{1,0,{pysm::y,pyym::in}},//垔 yin
{1,0,{pysm::h,pyym::ou}},//垕 hou
{1,0,{pysm::d,pyym::ui}},//垖 dui
{1,0,{pysm::zh,pyym::ao}},//垗 zhao
{1,0,{pysm::f,pyym::u}},//垘 fu
{1,0,{pysm::g,pyym::uang}},//垙 guang
{1,0,{pysm::y,pyym::ao}},//垚 yao
{1,0,{pysm::d,pyym::uo}},//垛 duo
{1,0,{pysm::d,pyym::uo}},//垜 duo
{1,0,{pysm::g,pyym::ui}},//垝 gui
{1,0,{pysm::ch,pyym::a}},//垞 cha
{1,0,{pysm::y,pyym::ang}},//垟 yang
{2,511,{pysm::nop,pyym::nop}},//垠 yin
{1,0,{pysm::f,pyym::a}},//垡 fa
{1,0,{pysm::g,pyym::ou}},//垢 gou
{1,0,{pysm::y,pyym::uan}},//垣 yuan
{1,0,{pysm::d,pyym::ie}},//垤 die
{1,0,{pysm::x,pyym::ie}},//垥 xie
{2,512,{pysm::nop,pyym::nop}},//垦 ken
{2,513,{pysm::nop,pyym::nop}},//垧 shang
{1,0,{pysm::sh,pyym::ou}},//垨 shou
{2,514,{pysm::nop,pyym::nop}},//垩 e
{1,0,{pysm::b,pyym::ing}},//垪 bing
{1,0,{pysm::d,pyym::ian}},//垫 dian
{1,0,{pysm::h,pyym::ong}},//垬 hong
{1,0,{pysm::y,pyym::a}},//垭 ya
{1,0,{pysm::k,pyym::ua}},//垮 kua
{1,0,{pysm::d,pyym::a}},//垯 da
{1,0,{pysm::k,pyym::a}},//垰 ka
{1,0,{pysm::d,pyym::ang}},//垱 dang
{1,0,{pysm::k,pyym::ai}},//垲 kai
{1,0,{pysm::h,pyym::ang}},//垳 hang
{1,0,{pysm::n,pyym::ao}},//垴 nao
{1,0,{pysm::nop,pyym::an}},//垵 an
{1,0,{pysm::x,pyym::ing}},//垶 xing
{1,0,{pysm::x,pyym::ian}},//垷 xian
{2,515,{pysm::nop,pyym::nop}},//垸 yuan
{1,0,{pysm::b,pyym::ang}},//垹 bang
{4,33,{pysm::nop,pyym::nop}},//垺 fu
{2,516,{pysm::nop,pyym::nop}},//垻 ba
{1,0,{pysm::y,pyym::i}},//垼 yi
{1,0,{pysm::y,pyym::in}},//垽 yin
{2,517,{pysm::nop,pyym::nop}},//垾 han
{1,0,{pysm::x,pyym::u}},//垿 xu
{1,0,{pysm::ch,pyym::ui}},//埀 chui
{1,0,{pysm::q,pyym::in}},//埁 qin
{1,0,{pysm::g,pyym::eng}},//埂 geng
{2,518,{pysm::nop,pyym::nop}},//埃 ai
{2,519,{pysm::nop,pyym::nop}},//埄 beng
{2,520,{pysm::nop,pyym::nop}},//埅 fang
{2,521,{pysm::nop,pyym::nop}},//埆 que
{1,0,{pysm::y,pyym::ong}},//埇 yong
{1,0,{pysm::j,pyym::un}},//埈 jun
{2,522,{pysm::nop,pyym::nop}},//埉 jia
{1,0,{pysm::d,pyym::i}},//埊 di
{2,523,{pysm::nop,pyym::nop}},//埋 mai
{1,0,{pysm::l,pyym::ang}},//埌 lang
{1,0,{pysm::j,pyym::uan}},//埍 juan
{1,0,{pysm::ch,pyym::eng}},//城 cheng
{2,524,{pysm::nop,pyym::nop}},//埏 shan
{2,525,{pysm::nop,pyym::nop}},//埐 jin
{1,0,{pysm::zh,pyym::e}},//埑 zhe
{1,0,{pysm::l,pyym::ie}},//埒 lie
{1,0,{pysm::l,pyym::ie}},//埓 lie
{2,526,{pysm::nop,pyym::nop}},//埔 pu
{1,0,{pysm::ch,pyym::eng}},//埕 cheng
{1,0,{pysm::h,pyym::ua}},//埖 hua
{1,0,{pysm::b,pyym::u}},//埗 bu
{1,0,{pysm::sh,pyym::i}},//埘 shi
{1,0,{pysm::x,pyym::un}},//埙 xun
{1,0,{pysm::g,pyym::uo}},//埚 guo
{1,0,{pysm::j,pyym::iong}},//埛 jiong
{1,0,{pysm::y,pyym::e}},//埜 ye
{3,136,{pysm::nop,pyym::nop}},//埝 nian
{1,0,{pysm::d,pyym::i}},//埞 di
{1,0,{pysm::y,pyym::u}},//域 yu
{1,0,{pysm::b,pyym::u}},//埠 bu
{3,137,{pysm::nop,pyym::nop}},//埡 ya
{2,527,{pysm::nop,pyym::nop}},//埢 quan
{2,528,{pysm::nop,pyym::nop}},//埣 sui
{3,138,{pysm::nop,pyym::nop}},//埤 pi
{2,529,{pysm::nop,pyym::nop}},//埥 qing
{1,0,{pysm::w,pyym::an}},//埦 wan
{1,0,{pysm::j,pyym::u}},//埧 ju
{1,0,{pysm::l,pyym::un}},//埨 lun
{2,530,{pysm::nop,pyym::nop}},//埩 zheng
{1,0,{pysm::k,pyym::ong}},//埪 kong
{3,139,{pysm::nop,pyym::nop}},//埫 chong
{1,0,{pysm::d,pyym::ong}},//埬 dong
{1,0,{pysm::d,pyym::ai}},//埭 dai
{1,0,{pysm::t,pyym::an}},//埮 tan
{2,531,{pysm::nop,pyym::nop}},//埯 an
{1,0,{pysm::c,pyym::ai}},//埰 cai
{2,532,{pysm::nop,pyym::nop}},//埱 chu
{2,533,{pysm::nop,pyym::nop}},//埲 beng
{2,534,{pysm::nop,pyym::nop}},//埳 kan
{1,0,{pysm::zh,pyym::i}},//埴 zhi
{1,0,{pysm::d,pyym::uo}},//埵 duo
{2,535,{pysm::nop,pyym::nop}},//埶 yi
{1,0,{pysm::zh,pyym::i}},//執 zhi
{1,0,{pysm::y,pyym::i}},//埸 yi
{3,140,{pysm::nop,pyym::nop}},//培 pei
{1,0,{pysm::j,pyym::i}},//基 ji
{3,141,{pysm::nop,pyym::nop}},//埻 zhun
{1,0,{pysm::q,pyym::i}},//埼 qi
{1,0,{pysm::s,pyym::ao}},//埽 sao
{1,0,{pysm::j,pyym::u}},//埾 ju
{2,536,{pysm::nop,pyym::nop}},//埿 ni
{1,0,{pysm::k,pyym::u}},//堀 ku
{1,0,{pysm::k,pyym::e}},//堁 ke
{1,0,{pysm::t,pyym::ang}},//堂 tang
{1,0,{pysm::k,pyym::un}},//堃 kun
{1,0,{pysm::n,pyym::i}},//堄 ni
{1,0,{pysm::j,pyym::ian}},//堅 jian
{2,537,{pysm::nop,pyym::nop}},//堆 dui
{2,538,{pysm::nop,pyym::nop}},//堇 jin
{1,0,{pysm::g,pyym::ang}},//堈 gang
{1,0,{pysm::y,pyym::u}},//堉 yu
{2,539,{pysm::nop,pyym::nop}},//堊 e
{3,142,{pysm::nop,pyym::nop}},//堋 peng
{1,0,{pysm::g,pyym::u}},//堌 gu
{1,0,{pysm::t,pyym::u}},//堍 tu
{1,0,{pysm::l,pyym::eng}},//堎 leng
{1,0,{pysm::f,pyym::ang}},//堏 fang
{1,0,{pysm::y,pyym::a}},//堐 ya
{1,0,{pysm::q,pyym::ian}},//堑 qian
{1,0,{pysm::k,pyym::un}},//堒 kun
{1,0,{pysm::nop,pyym::an}},//堓 an
{1,0,{pysm::sh,pyym::en}},//堔 shen
{2,540,{pysm::nop,pyym::nop}},//堕 duo
{1,0,{pysm::n,pyym::ao}},//堖 nao
{1,0,{pysm::t,pyym::u}},//堗 tu
{1,0,{pysm::ch,pyym::eng}},//堘 cheng
{1,0,{pysm::y,pyym::in}},//堙 yin
{1,0,{pysm::h,pyym::un}},//堚 hun
{1,0,{pysm::b,pyym::i}},//堛 bi
{1,0,{pysm::l,pyym::ian}},//堜 lian
{2,541,{pysm::nop,pyym::nop}},//堝 guo
{1,0,{pysm::d,pyym::ie}},//堞 die
{1,0,{pysm::zh,pyym::uan}},//堟 zhuan
{1,0,{pysm::h,pyym::ou}},//堠 hou
{3,143,{pysm::nop,pyym::nop}},//堡 bao
{1,0,{pysm::b,pyym::ao}},//堢 bao
{1,0,{pysm::y,pyym::u}},//堣 yu
{4,34,{pysm::nop,pyym::nop}},//堤 di
{3,144,{pysm::nop,pyym::nop}},//堥 mao
{1,0,{pysm::j,pyym::ie}},//堦 jie
{2,542,{pysm::nop,pyym::nop}},//堧 ruan
{3,145,{pysm::nop,pyym::nop}},//堨 ye
{1,0,{pysm::g,pyym::eng}},//堩 geng
{2,543,{pysm::nop,pyym::nop}},//堪 kan
{1,0,{pysm::z,pyym::ong}},//堫 zong
{1,0,{pysm::y,pyym::u}},//堬 yu
{1,0,{pysm::h,pyym::uang}},//堭 huang
{1,0,{pysm::nop,pyym::e}},//堮 e
{1,0,{pysm::y,pyym::ao}},//堯 yao
{1,0,{pysm::y,pyym::an}},//堰 yan
{2,544,{pysm::nop,pyym::nop}},//報 bao
{2,545,{pysm::nop,pyym::nop}},//堲 ci
{1,0,{pysm::m,pyym::ei}},//堳 mei
{3,146,{pysm::nop,pyym::nop}},//場 chang
{2,546,{pysm::nop,pyym::nop}},//堵 du
{1,0,{pysm::t,pyym::uo}},//堶 tuo
{2,547,{pysm::nop,pyym::nop}},//堷 yin
{1,0,{pysm::f,pyym::eng}},//堸 feng
{1,0,{pysm::zh,pyym::ong}},//堹 zhong
{1,0,{pysm::j,pyym::ie}},//堺 jie
{1,0,{pysm::j,pyym::in}},//堻 jin
{1,0,{pysm::h,pyym::eng}},//堼 heng
{1,0,{pysm::g,pyym::ang}},//堽 gang
{1,0,{pysm::ch,pyym::un}},//堾 chun
{3,147,{pysm::nop,pyym::nop}},//堿 jian
{1,0,{pysm::p,pyym::ing}},//塀 ping
{1,0,{pysm::l,pyym::ei}},//塁 lei
{2,548,{pysm::nop,pyym::nop}},//塂 xiang
{1,0,{pysm::h,pyym::uang}},//塃 huang
{1,0,{pysm::l,pyym::eng}},//塄 leng
{1,0,{pysm::d,pyym::uan}},//塅 duan
{1,0,{pysm::w,pyym::an}},//塆 wan
{1,0,{pysm::x,pyym::uan}},//塇 xuan
{2,549,{pysm::nop,pyym::nop}},//塈 ji
{1,0,{pysm::j,pyym::i}},//塉 ji
{1,0,{pysm::k,pyym::uai}},//塊 kuai
{1,0,{pysm::y,pyym::ing}},//塋 ying
{2,550,{pysm::nop,pyym::nop}},//塌 ta
{1,0,{pysm::ch,pyym::eng}},//塍 cheng
{1,0,{pysm::y,pyym::ong}},//塎 yong
{1,0,{pysm::k,pyym::ai}},//塏 kai
{1,0,{pysm::s,pyym::u}},//塐 su
{1,0,{pysm::s,pyym::u}},//塑 su
{1,0,{pysm::sh,pyym::i}},//塒 shi
{1,0,{pysm::m,pyym::i}},//塓 mi
{2,551,{pysm::nop,pyym::nop}},//塔 ta
{1,0,{pysm::w,pyym::eng}},//塕 weng
{1,0,{pysm::ch,pyym::eng}},//塖 cheng
{2,552,{pysm::nop,pyym::nop}},//塗 tu
{1,0,{pysm::t,pyym::ang}},//塘 tang
{2,553,{pysm::nop,pyym::nop}},//塙 que
{1,0,{pysm::zh,pyym::ong}},//塚 zhong
{1,0,{pysm::l,pyym::i}},//塛 li
{2,554,{pysm::nop,pyym::nop}},//塜 zhong
{1,0,{pysm::b,pyym::ang}},//塝 bang
{2,555,{pysm::nop,pyym::nop}},//塞 sai
{1,0,{pysm::z,pyym::ang}},//塟 zang
{1,0,{pysm::d,pyym::ui}},//塠 dui
{1,0,{pysm::t,pyym::ian}},//塡 tian
{1,0,{pysm::w,pyym::u}},//塢 wu
{1,0,{pysm::zh,pyym::eng}},//塣 zheng
{1,0,{pysm::x,pyym::un}},//塤 xun
{1,0,{pysm::g,pyym::e}},//塥 ge
{1,0,{pysm::zh,pyym::en}},//塦 zhen
{1,0,{pysm::nop,pyym::ai}},//塧 ai
{1,0,{pysm::g,pyym::ong}},//塨 gong
{1,0,{pysm::y,pyym::an}},//塩 yan
{1,0,{pysm::k,pyym::an}},//塪 kan
{3,148,{pysm::nop,pyym::nop}},//填 tian
{1,0,{pysm::y,pyym::uan}},//塬 yuan
{1,0,{pysm::w,pyym::en}},//塭 wen
{1,0,{pysm::x,pyym::ie}},//塮 xie
{1,0,{pysm::l,pyym::iu}},//塯 liu
{1,0,{pysm::h,pyym::ai}},//塰 hai
{1,0,{pysm::l,pyym::ang}},//塱 lang
{2,556,{pysm::nop,pyym::nop}},//塲 chang
{1,0,{pysm::p,pyym::eng}},//塳 peng
{1,0,{pysm::b,pyym::eng}},//塴 beng
{1,0,{pysm::ch,pyym::en}},//塵 chen
{1,0,{pysm::l,pyym::u}},//塶 lu
{1,0,{pysm::l,pyym::u}},//塷 lu
{1,0,{pysm::nop,pyym::ou}},//塸 ou
{2,557,{pysm::nop,pyym::nop}},//塹 qian
{1,0,{pysm::m,pyym::ei}},//塺 mei
{1,0,{pysm::m,pyym::o}},//塻 mo
{2,558,{pysm::nop,pyym::nop}},//塼 zhuan
{1,0,{pysm::sh,pyym::uang}},//塽 shuang
{1,0,{pysm::sh,pyym::u}},//塾 shu
{1,0,{pysm::l,pyym::ou}},//塿 lou
{1,0,{pysm::ch,pyym::i}},//墀 chi
{1,0,{pysm::m,pyym::an}},//墁 man
{1,0,{pysm::b,pyym::iao}},//墂 biao
{1,0,{pysm::j,pyym::ing}},//境 jing
{1,0,{pysm::c,pyym::e}},//墄 ce
{2,559,{pysm::nop,pyym::nop}},//墅 shu
{2,560,{pysm::nop,pyym::nop}},//墆 zhi
{1,0,{pysm::zh,pyym::ang}},//墇 zhang
{1,0,{pysm::k,pyym::an}},//墈 kan
{1,0,{pysm::y,pyym::ong}},//墉 yong
{1,0,{pysm::d,pyym::ian}},//墊 dian
{1,0,{pysm::ch,pyym::en}},//墋 chen
{2,561,{pysm::nop,pyym::nop}},//墌 zhi
{1,0,{pysm::x,pyym::i}},//墍 xi
{1,0,{pysm::g,pyym::uo}},//墎 guo
{1,0,{pysm::q,pyym::iang}},//墏 qiang
{2,562,{pysm::nop,pyym::nop}},//墐 jin
{1,0,{pysm::d,pyym::i}},//墑 di
{1,0,{pysm::sh,pyym::ang}},//墒 shang
{1,0,{pysm::m,pyym::u}},//墓 mu
{1,0,{pysm::c,pyym::ui}},//墔 cui
{1,0,{pysm::y,pyym::an}},//墕 yan
{1,0,{pysm::t,pyym::a}},//墖 ta
{1,0,{pysm::z,pyym::eng}},//増 zeng
{1,0,{pysm::q,pyym::ian}},//墘 qian
{1,0,{pysm::q,pyym::iang}},//墙 qiang
{1,0,{pysm::l,pyym::iang}},//墚 liang
{1,0,{pysm::w,pyym::ei}},//墛 wei
{1,0,{pysm::zh,pyym::ui}},//墜 zhui
{1,0,{pysm::q,pyym::iao}},//墝 qiao
{2,563,{pysm::nop,pyym::nop}},//增 zeng
{1,0,{pysm::x,pyym::u}},//墟 xu
{2,564,{pysm::nop,pyym::nop}},//墠 shan
{1,0,{pysm::sh,pyym::an}},//墡 shan
{2,565,{pysm::nop,pyym::nop}},//墢 ba
{1,0,{pysm::p,pyym::u}},//墣 pu
{2,566,{pysm::nop,pyym::nop}},//墤 kuai
{2,567,{pysm::nop,pyym::nop}},//墥 dong
{1,0,{pysm::f,pyym::an}},//墦 fan
{2,568,{pysm::nop,pyym::nop}},//墧 que
{2,569,{pysm::nop,pyym::nop}},//墨 mo
{1,0,{pysm::d,pyym::un}},//墩 dun
{1,0,{pysm::d,pyym::un}},//墪 dun
{2,570,{pysm::nop,pyym::nop}},//墫 zun
{1,0,{pysm::d,pyym::i}},//墬 di
{1,0,{pysm::sh,pyym::eng}},//墭 sheng
{2,571,{pysm::nop,pyym::nop}},//墮 duo
{1,0,{pysm::d,pyym::uo}},//墯 duo
{1,0,{pysm::t,pyym::an}},//墰 tan
{1,0,{pysm::d,pyym::eng}},//墱 deng
{2,572,{pysm::nop,pyym::nop}},//墲 mu
{1,0,{pysm::f,pyym::en}},//墳 fen
{1,0,{pysm::h,pyym::uang}},//墴 huang
{1,0,{pysm::t,pyym::an}},//墵 tan
{1,0,{pysm::d,pyym::a}},//墶 da
{1,0,{pysm::y,pyym::e}},//墷 ye
{1,0,{pysm::zh,pyym::u}},//墸 zhu
{1,0,{pysm::j,pyym::ian}},//墹 jian
{1,0,{pysm::nop,pyym::ao}},//墺 ao
{1,0,{pysm::q,pyym::iang}},//墻 qiang
{1,0,{pysm::j,pyym::i}},//墼 ji
{2,573,{pysm::nop,pyym::nop}},//墽 qiao
{1,0,{pysm::k,pyym::en}},//墾 ken
{2,574,{pysm::nop,pyym::nop}},//墿 yi
{1,0,{pysm::p,pyym::i}},//壀 pi
{1,0,{pysm::b,pyym::i}},//壁 bi
{1,0,{pysm::d,pyym::ian}},//壂 dian
{1,0,{pysm::j,pyym::iang}},//壃 jiang
{1,0,{pysm::y,pyym::e}},//壄 ye
{2,575,{pysm::nop,pyym::nop}},//壅 yong
{3,149,{pysm::nop,pyym::nop}},//壆 xue
{3,150,{pysm::nop,pyym::nop}},//壇 tan
{1,0,{pysm::l,pyym::an}},//壈 lan
{1,0,{pysm::j,pyym::u}},//壉 ju
{1,0,{pysm::h,pyym::uai}},//壊 huai
{1,0,{pysm::d,pyym::ang}},//壋 dang
{1,0,{pysm::r,pyym::ang}},//壌 rang
{1,0,{pysm::q,pyym::ian}},//壍 qian
{1,0,{pysm::x,pyym::un}},//壎 xun
{2,576,{pysm::nop,pyym::nop}},//壏 xian
{1,0,{pysm::x,pyym::i}},//壐 xi
{2,577,{pysm::nop,pyym::nop}},//壑 he
{1,0,{pysm::nop,pyym::ai}},//壒 ai
{1,0,{pysm::y,pyym::a}},//壓 ya
{1,0,{pysm::d,pyym::ao}},//壔 dao
{1,0,{pysm::h,pyym::ao}},//壕 hao
{1,0,{pysm::r,pyym::uan}},//壖 ruan
{1,0,{pysm::j,pyym::in}},//壗 jin
{2,578,{pysm::nop,pyym::nop}},//壘 lei
{1,0,{pysm::k,pyym::uang}},//壙 kuang
{1,0,{pysm::l,pyym::u}},//壚 lu
{1,0,{pysm::y,pyym::an}},//壛 yan
{1,0,{pysm::t,pyym::an}},//壜 tan
{1,0,{pysm::w,pyym::ei}},//壝 wei
{2,579,{pysm::nop,pyym::nop}},//壞 huai
{1,0,{pysm::l,pyym::ong}},//壟 long
{1,0,{pysm::l,pyym::ong}},//壠 long
{1,0,{pysm::r,pyym::ui}},//壡 rui
{1,0,{pysm::l,pyym::i}},//壢 li
{1,0,{pysm::l,pyym::in}},//壣 lin
{1,0,{pysm::r,pyym::ang}},//壤 rang
{1,0,{pysm::ch,pyym::an}},//壥 chan
{1,0,{pysm::x,pyym::un}},//壦 xun
{1,0,{pysm::y,pyym::an}},//壧 yan
{1,0,{pysm::l,pyym::ei}},//壨 lei
{1,0,{pysm::b,pyym::a}},//壩 ba
{1,0,{pysm::w,pyym::an}},//壪 wan
{1,0,{pysm::sh,pyym::i}},//士 shi
{1,0,{pysm::r,pyym::en}},//壬 ren
{1,0,{pysm::s,pyym::an}},//壭 san
{1,0,{pysm::zh,pyym::uang}},//壮 zhuang
{1,0,{pysm::zh,pyym::uang}},//壯 zhuang
{2,580,{pysm::nop,pyym::nop}},//声 sheng
{1,0,{pysm::y,pyym::i}},//壱 yi
{1,0,{pysm::m,pyym::ai}},//売 mai
{2,581,{pysm::nop,pyym::nop}},//壳 ke
{1,0,{pysm::zh,pyym::u}},//壴 zhu
{1,0,{pysm::zh,pyym::uang}},//壵 zhuang
{1,0,{pysm::h,pyym::u}},//壶 hu
{1,0,{pysm::h,pyym::u}},//壷 hu
{1,0,{pysm::k,pyym::un}},//壸 kun
{2,582,{pysm::nop,pyym::nop}},//壹 yi
{1,0,{pysm::h,pyym::u}},//壺 hu
{1,0,{pysm::x,pyym::u}},//壻 xu
{1,0,{pysm::k,pyym::un}},//壼 kun
{1,0,{pysm::sh,pyym::ou}},//壽 shou
{1,0,{pysm::m,pyym::ang}},//壾 mang
{1,0,{pysm::z,pyym::un}},//壿 zun
{1,0,{pysm::sh,pyym::ou}},//夀 shou
{1,0,{pysm::y,pyym::i}},//夁 yi
{2,583,{pysm::nop,pyym::nop}},//夂 zhi
{2,584,{pysm::nop,pyym::nop}},//夃 gu
{1,0,{pysm::ch,pyym::u}},//处 chu
{1,0,{pysm::j,pyym::iang}},//夅 jiang
{2,585,{pysm::nop,pyym::nop}},//夆 feng
{1,0,{pysm::b,pyym::ei}},//备 bei
{1,0,{pysm::zh,pyym::ai}},//夈 zhai
{1,0,{pysm::b,pyym::ian}},//変 bian
{1,0,{pysm::s,pyym::ui}},//夊 sui
{1,0,{pysm::q,pyym::un}},//夋 qun
{1,0,{pysm::l,pyym::ing}},//夌 ling
{1,0,{pysm::f,pyym::u}},//复 fu
{1,0,{pysm::c,pyym::uo}},//夎 cuo
{2,586,{pysm::nop,pyym::nop}},//夏 xia
{2,587,{pysm::nop,pyym::nop}},//夐 xiong
{1,0,{pysm::x,pyym::ie}},//夑 xie
{1,0,{pysm::n,pyym::ao}},//夒 nao
{1,0,{pysm::x,pyym::ia}},//夓 xia
{1,0,{pysm::k,pyym::ui}},//夔 kui
{2,588,{pysm::nop,pyym::nop}},//夕 xi
{1,0,{pysm::w,pyym::ai}},//外 wai
{2,589,{pysm::nop,pyym::nop}},//夗 yuan
{2,590,{pysm::nop,pyym::nop}},//夘 mao
{1,0,{pysm::s,pyym::u}},//夙 su
{1,0,{pysm::d,pyym::uo}},//多 duo
{1,0,{pysm::d,pyym::uo}},//夛 duo
{1,0,{pysm::y,pyym::e}},//夜 ye
{1,0,{pysm::q,pyym::ing}},//夝 qing
{1,0,{pysm::w,pyym::ai}},//夞 wai
{1,0,{pysm::g,pyym::ou}},//够 gou
{1,0,{pysm::g,pyym::ou}},//夠 gou
{1,0,{pysm::q,pyym::i}},//夡 qi
{1,0,{pysm::m,pyym::eng}},//夢 meng
{1,0,{pysm::m,pyym::eng}},//夣 meng
{1,0,{pysm::y,pyym::in}},//夤 yin
{1,0,{pysm::h,pyym::uo}},//夥 huo
{1,0,{pysm::ch,pyym::en}},//夦 chen
{3,151,{pysm::nop,pyym::nop}},//大 da
{1,0,{pysm::z,pyym::e}},//夨 ze
{1,0,{pysm::t,pyym::ian}},//天 tian
{2,591,{pysm::nop,pyym::nop}},//太 tai
{1,0,{pysm::f,pyym::u}},//夫 fu
{2,592,{pysm::nop,pyym::nop}},//夬 guai
{3,152,{pysm::nop,pyym::nop}},//夭 yao
{2,593,{pysm::nop,pyym::nop}},//央 yang
{2,594,{pysm::nop,pyym::nop}},//夯 hang
{1,0,{pysm::g,pyym::ao}},//夰 gao
{2,595,{pysm::nop,pyym::nop}},//失 shi
{2,596,{pysm::nop,pyym::nop}},//夲 tao
{1,0,{pysm::t,pyym::ai}},//夳 tai
{1,0,{pysm::t,pyym::ou}},//头 tou
{2,597,{pysm::nop,pyym::nop}},//夵 yan
{1,0,{pysm::b,pyym::i}},//夶 bi
{1,0,{pysm::y,pyym::i}},//夷 yi
{1,0,{pysm::k,pyym::ua}},//夸 kua
{2,598,{pysm::nop,pyym::nop}},//夹 jia
{1,0,{pysm::d,pyym::uo}},//夺 duo
{1,0,{pysm::h,pyym::ua}},//夻 hua
{1,0,{pysm::k,pyym::uang}},//夼 kuang
{1,0,{pysm::y,pyym::un}},//夽 yun
{4,35,{pysm::nop,pyym::nop}},//夾 jia
{1,0,{pysm::b,pyym::a}},//夿 ba
{1,0,{pysm::nop,pyym::en}},//奀 en
{1,0,{pysm::l,pyym::ian}},//奁 lian
{1,0,{pysm::h,pyym::uan}},//奂 huan
{2,599,{pysm::nop,pyym::nop}},//奃 di
{1,0,{pysm::y,pyym::an}},//奄 yan
{1,0,{pysm::p,pyym::ao}},//奅 pao
{1,0,{pysm::j,pyym::uan}},//奆 juan
{4,36,{pysm::nop,pyym::nop}},//奇 qi
{1,0,{pysm::n,pyym::ai}},//奈 nai
{1,0,{pysm::f,pyym::eng}},//奉 feng
{4,37,{pysm::nop,pyym::nop}},//奊 xie
{2,600,{pysm::nop,pyym::nop}},//奋 fen
{1,0,{pysm::d,pyym::ian}},//奌 dian
{1,0,{pysm::q,pyym::uan}},//奍 quan
{1,0,{pysm::k,pyym::ui}},//奎 kui
{2,601,{pysm::nop,pyym::nop}},//奏 zou
{1,0,{pysm::h,pyym::uan}},//奐 huan
{4,38,{pysm::nop,pyym::nop}},//契 qi
{1,0,{pysm::k,pyym::ai}},//奒 kai
{3,153,{pysm::nop,pyym::nop}},//奓 zha
{2,602,{pysm::nop,pyym::nop}},//奔 ben
{1,0,{pysm::y,pyym::i}},//奕 yi
{1,0,{pysm::j,pyym::iang}},//奖 jiang
{1,0,{pysm::t,pyym::ao}},//套 tao
{2,603,{pysm::nop,pyym::nop}},//奘 zang
{1,0,{pysm::b,pyym::en}},//奙 ben
{1,0,{pysm::x,pyym::i}},//奚 xi
{1,0,{pysm::h,pyym::uang}},//奛 huang
{1,0,{pysm::f,pyym::ei}},//奜 fei
{1,0,{pysm::d,pyym::iao}},//奝 diao
{1,0,{pysm::x,pyym::un}},//奞 xun
{2,604,{pysm::nop,pyym::nop}},//奟 beng
{5,14,{pysm::nop,pyym::nop}},//奠 dian
{2,605,{pysm::nop,pyym::nop}},//奡 ao
{1,0,{pysm::sh,pyym::e}},//奢 she
{1,0,{pysm::w,pyym::eng}},//奣 weng
{3,154,{pysm::nop,pyym::nop}},//奤 ha
{3,155,{pysm::nop,pyym::nop}},//奥 ao
{1,0,{pysm::w,pyym::u}},//奦 wu
{1,0,{pysm::nop,pyym::ao}},//奧 ao
{1,0,{pysm::j,pyym::iang}},//奨 jiang
{1,0,{pysm::l,pyym::ian}},//奩 lian
{2,606,{pysm::nop,pyym::nop}},//奪 duo
{1,0,{pysm::y,pyym::un}},//奫 yun
{1,0,{pysm::j,pyym::iang}},//奬 jiang
{1,0,{pysm::sh,pyym::i}},//奭 shi
{1,0,{pysm::f,pyym::en}},//奮 fen
{1,0,{pysm::h,pyym::uo}},//奯 huo
{1,0,{pysm::b,pyym::i}},//奰 bi
{1,0,{pysm::l,pyym::uan}},//奱 luan
{2,607,{pysm::nop,pyym::nop}},//奲 duo
{2,608,{pysm::nop,pyym::nop}},//女 nü
{1,0,{pysm::n,pyym::u}},//奴 nu
{2,609,{pysm::nop,pyym::nop}},//奵 ding
{1,0,{pysm::n,pyym::ai}},//奶 nai
{1,0,{pysm::q,pyym::ian}},//奷 qian
{2,610,{pysm::nop,pyym::nop}},//奸 jian
{3,156,{pysm::nop,pyym::nop}},//她 ta
{1,0,{pysm::j,pyym::iu}},//奺 jiu
{1,0,{pysm::n,pyym::uan}},//奻 nuan
{1,0,{pysm::ch,pyym::a}},//奼 cha
{1,0,{pysm::h,pyym::ao}},//好 hao
{1,0,{pysm::x,pyym::ian}},//奾 xian
{1,0,{pysm::f,pyym::an}},//奿 fan
{1,0,{pysm::j,pyym::i}},//妀 ji
{2,611,{pysm::nop,pyym::nop}},//妁 shuo
{1,0,{pysm::r,pyym::u}},//如 ru
{2,612,{pysm::nop,pyym::nop}},//妃 fei
{1,0,{pysm::w,pyym::ang}},//妄 wang
{1,0,{pysm::h,pyym::ong}},//妅 hong
{1,0,{pysm::zh,pyym::uang}},//妆 zhuang
{1,0,{pysm::f,pyym::u}},//妇 fu
{1,0,{pysm::m,pyym::a}},//妈 ma
{1,0,{pysm::d,pyym::an}},//妉 dan
{1,0,{pysm::r,pyym::en}},//妊 ren
{2,613,{pysm::nop,pyym::nop}},//妋 fu
{1,0,{pysm::j,pyym::ing}},//妌 jing
{1,0,{pysm::y,pyym::an}},//妍 yan
{2,614,{pysm::nop,pyym::nop}},//妎 hai
{1,0,{pysm::w,pyym::en}},//妏 wen
{1,0,{pysm::zh,pyym::ong}},//妐 zhong
{1,0,{pysm::p,pyym::a}},//妑 pa
{1,0,{pysm::d,pyym::u}},//妒 du
{1,0,{pysm::j,pyym::i}},//妓 ji
{2,615,{pysm::nop,pyym::nop}},//妔 keng
{1,0,{pysm::zh,pyym::ong}},//妕 zhong
{2,616,{pysm::nop,pyym::nop}},//妖 yao
{2,617,{pysm::nop,pyym::nop}},//妗 jin
{1,0,{pysm::y,pyym::un}},//妘 yun
{1,0,{pysm::m,pyym::iao}},//妙 miao
{3,157,{pysm::nop,pyym::nop}},//妚 fou
{1,0,{pysm::ch,pyym::i}},//妛 chi
{2,618,{pysm::nop,pyym::nop}},//妜 yue
{1,0,{pysm::zh,pyym::uang}},//妝 zhuang
{2,619,{pysm::nop,pyym::nop}},//妞 niu
{1,0,{pysm::y,pyym::an}},//妟 yan
{2,620,{pysm::nop,pyym::nop}},//妠 na
{1,0,{pysm::x,pyym::in}},//妡 xin
{1,0,{pysm::f,pyym::en}},//妢 fen
{1,0,{pysm::b,pyym::i}},//妣 bi
{1,0,{pysm::y,pyym::u}},//妤 yu
{1,0,{pysm::t,pyym::uo}},//妥 tuo
{1,0,{pysm::f,pyym::eng}},//妦 feng
{2,621,{pysm::nop,pyym::nop}},//妧 wan
{1,0,{pysm::f,pyym::ang}},//妨 fang
{1,0,{pysm::w,pyym::u}},//妩 wu
{1,0,{pysm::y,pyym::u}},//妪 yu
{1,0,{pysm::g,pyym::ui}},//妫 gui
{1,0,{pysm::d,pyym::u}},//妬 du
{2,622,{pysm::nop,pyym::nop}},//妭 ba
{1,0,{pysm::n,pyym::i}},//妮 ni
{2,623,{pysm::nop,pyym::nop}},//妯 zhou
{1,0,{pysm::zh,pyym::uo}},//妰 zhuo
{1,0,{pysm::zh,pyym::ao}},//妱 zhao
{1,0,{pysm::d,pyym::a}},//妲 da
{2,624,{pysm::nop,pyym::nop}},//妳 ni
{1,0,{pysm::y,pyym::uan}},//妴 yuan
{1,0,{pysm::t,pyym::ou}},//妵 tou
{3,158,{pysm::nop,pyym::nop}},//妶 xian
{2,625,{pysm::nop,pyym::nop}},//妷 zhi
{1,0,{pysm::nop,pyym::e}},//妸 e
{1,0,{pysm::m,pyym::ei}},//妹 mei
{1,0,{pysm::m,pyym::o}},//妺 mo
{1,0,{pysm::q,pyym::i}},//妻 qi
{1,0,{pysm::b,pyym::i}},//妼 bi
{1,0,{pysm::sh,pyym::en}},//妽 shen
{1,0,{pysm::q,pyym::ie}},//妾 qie
{1,0,{pysm::nop,pyym::e}},//妿 e
{1,0,{pysm::h,pyym::e}},//姀 he
{1,0,{pysm::x,pyym::u}},//姁 xu
{1,0,{pysm::f,pyym::a}},//姂 fa
{1,0,{pysm::zh,pyym::eng}},//姃 zheng
{1,0,{pysm::m,pyym::in}},//姄 min
{1,0,{pysm::b,pyym::an}},//姅 ban
{1,0,{pysm::m,pyym::u}},//姆 mu
{1,0,{pysm::f,pyym::u}},//姇 fu
{1,0,{pysm::l,pyym::ing}},//姈 ling
{1,0,{pysm::z,pyym::i}},//姉 zi
{1,0,{pysm::z,pyym::i}},//姊 zi
{1,0,{pysm::sh,pyym::i}},//始 shi
{1,0,{pysm::r,pyym::an}},//姌 ran
{3,159,{pysm::nop,pyym::nop}},//姍 shan
{1,0,{pysm::y,pyym::ang}},//姎 yang
{1,0,{pysm::m,pyym::an}},//姏 man
{4,39,{pysm::nop,pyym::nop}},//姐 jie
{1,0,{pysm::g,pyym::u}},//姑 gu
{1,0,{pysm::s,pyym::i}},//姒 si
{2,626,{pysm::nop,pyym::nop}},//姓 xing
{1,0,{pysm::w,pyym::ei}},//委 wei
{2,627,{pysm::nop,pyym::nop}},//姕 zi
{1,0,{pysm::j,pyym::u}},//姖 ju
{1,0,{pysm::sh,pyym::an}},//姗 shan
{1,0,{pysm::p,pyym::in}},//姘 pin
{1,0,{pysm::r,pyym::en}},//姙 ren
{3,160,{pysm::nop,pyym::nop}},//姚 yao
{1,0,{pysm::d,pyym::ong}},//姛 dong
{1,0,{pysm::j,pyym::iang}},//姜 jiang
{1,0,{pysm::sh,pyym::u}},//姝 shu
{1,0,{pysm::j,pyym::i}},//姞 ji
{1,0,{pysm::g,pyym::ai}},//姟 gai
{1,0,{pysm::x,pyym::iang}},//姠 xiang
{2,628,{pysm::nop,pyym::nop}},//姡 hua
{1,0,{pysm::j,pyym::uan}},//姢 juan
{2,629,{pysm::nop,pyym::nop}},//姣 jiao
{1,0,{pysm::g,pyym::ou}},//姤 gou
{2,630,{pysm::nop,pyym::nop}},//姥 lao
{1,0,{pysm::j,pyym::ian}},//姦 jian
{1,0,{pysm::j,pyym::ian}},//姧 jian
{1,0,{pysm::y,pyym::i}},//姨 yi
{1,0,{pysm::n,pyym::ian}},//姩 nian
{1,0,{pysm::zh,pyym::i}},//姪 zhi
{2,631,{pysm::nop,pyym::nop}},//姫 ji
{2,632,{pysm::nop,pyym::nop}},//姬 ji
{1,0,{pysm::x,pyym::ian}},//姭 xian
{1,0,{pysm::h,pyym::eng}},//姮 heng
{1,0,{pysm::g,pyym::uang}},//姯 guang
{4,40,{pysm::nop,pyym::nop}},//姰 jun
{2,633,{pysm::nop,pyym::nop}},//姱 kua
{1,0,{pysm::y,pyym::an}},//姲 yan
{1,0,{pysm::m,pyym::ing}},//姳 ming
{1,0,{pysm::l,pyym::ie}},//姴 lie
{1,0,{pysm::p,pyym::ei}},//姵 pei
{2,634,{pysm::nop,pyym::nop}},//姶 e
{1,0,{pysm::y,pyym::ou}},//姷 you
{1,0,{pysm::y,pyym::an}},//姸 yan
{1,0,{pysm::ch,pyym::a}},//姹 cha
{2,635,{pysm::nop,pyym::nop}},//姺 shen
{1,0,{pysm::y,pyym::in}},//姻 yin
{3,161,{pysm::nop,pyym::nop}},//姼 shi
{2,636,{pysm::nop,pyym::nop}},//姽 gui
{1,0,{pysm::q,pyym::uan}},//姾 quan
{1,0,{pysm::z,pyym::i}},//姿 zi
{1,0,{pysm::s,pyym::ong}},//娀 song
{1,0,{pysm::w,pyym::ei}},//威 wei
{1,0,{pysm::h,pyym::ong}},//娂 hong
{2,637,{pysm::nop,pyym::nop}},//娃 wa
{1,0,{pysm::l,pyym::ou}},//娄 lou
{1,0,{pysm::y,pyym::a}},//娅 ya
{1,0,{pysm::r,pyym::ao}},//娆 rao
{1,0,{pysm::j,pyym::iao}},//娇 jiao
{1,0,{pysm::l,pyym::uan}},//娈 luan
{2,638,{pysm::nop,pyym::nop}},//娉 ping
{2,639,{pysm::nop,pyym::nop}},//娊 xian
{1,0,{pysm::sh,pyym::ao}},//娋 shao
{1,0,{pysm::l,pyym::i}},//娌 li
{2,640,{pysm::nop,pyym::nop}},//娍 cheng
{1,0,{pysm::x,pyym::ie}},//娎 xie
{1,0,{pysm::m,pyym::ang}},//娏 mang
{1,0,{pysm::f,pyym::u}},//娐 fu
{1,0,{pysm::s,pyym::uo}},//娑 suo
{3,162,{pysm::nop,pyym::nop}},//娒 mei
{1,0,{pysm::w,pyym::ei}},//娓 wei
{1,0,{pysm::k,pyym::e}},//娔 ke
{3,163,{pysm::nop,pyym::nop}},//娕 chuo
{2,641,{pysm::nop,pyym::nop}},//娖 chuo
{2,642,{pysm::nop,pyym::nop}},//娗 ting
{1,0,{pysm::n,pyym::iang}},//娘 niang
{1,0,{pysm::x,pyym::ing}},//娙 xing
{1,0,{pysm::n,pyym::an}},//娚 nan
{1,0,{pysm::y,pyym::u}},//娛 yu
{2,643,{pysm::nop,pyym::nop}},//娜 na
{2,644,{pysm::nop,pyym::nop}},//娝 pou
{2,645,{pysm::nop,pyym::nop}},//娞 nei
{1,0,{pysm::j,pyym::uan}},//娟 juan
{1,0,{pysm::sh,pyym::en}},//娠 shen
{1,0,{pysm::zh,pyym::i}},//娡 zhi
{1,0,{pysm::h,pyym::an}},//娢 han
{1,0,{pysm::d,pyym::i}},//娣 di
{1,0,{pysm::zh,pyym::uang}},//娤 zhuang
{1,0,{pysm::nop,pyym::e}},//娥 e
{1,0,{pysm::p,pyym::in}},//娦 pin
{1,0,{pysm::t,pyym::ui}},//娧 tui
{1,0,{pysm::x,pyym::ian}},//娨 xian
{3,164,{pysm::nop,pyym::nop}},//娩 mian
{2,646,{pysm::nop,pyym::nop}},//娪 wu
{1,0,{pysm::y,pyym::an}},//娫 yan
{1,0,{pysm::w,pyym::u}},//娬 wu
{2,647,{pysm::nop,pyym::nop}},//娭 ai
{1,0,{pysm::y,pyym::an}},//娮 yan
{1,0,{pysm::y,pyym::u}},//娯 yu
{1,0,{pysm::s,pyym::i}},//娰 si
{1,0,{pysm::y,pyym::u}},//娱 yu
{1,0,{pysm::w,pyym::a}},//娲 wa
{1,0,{pysm::l,pyym::i}},//娳 li
{1,0,{pysm::x,pyym::ian}},//娴 xian
{1,0,{pysm::j,pyym::u}},//娵 ju
{3,165,{pysm::nop,pyym::nop}},//娶 qu
{2,648,{pysm::nop,pyym::nop}},//娷 zhui
{1,0,{pysm::q,pyym::i}},//娸 qi
{1,0,{pysm::x,pyym::ian}},//娹 xian
{1,0,{pysm::zh,pyym::uo}},//娺 zhuo
{1,0,{pysm::d,pyym::ong}},//娻 dong
{1,0,{pysm::ch,pyym::ang}},//娼 chang
{1,0,{pysm::l,pyym::u}},//娽 lu
{2,649,{pysm::nop,pyym::nop}},//娾 ai
{1,0,{pysm::nop,pyym::e}},//娿 e
{1,0,{pysm::nop,pyym::e}},//婀 e
{3,166,{pysm::nop,pyym::nop}},//婁 lou
{1,0,{pysm::m,pyym::ian}},//婂 mian
{1,0,{pysm::c,pyym::ong}},//婃 cong
{3,167,{pysm::nop,pyym::nop}},//婄 pou
{1,0,{pysm::j,pyym::u}},//婅 ju
{1,0,{pysm::p,pyym::o}},//婆 po
{1,0,{pysm::c,pyym::ai}},//婇 cai
{1,0,{pysm::l,pyym::ing}},//婈 ling
{1,0,{pysm::w,pyym::an}},//婉 wan
{1,0,{pysm::b,pyym::iao}},//婊 biao
{1,0,{pysm::x,pyym::iao}},//婋 xiao
{1,0,{pysm::sh,pyym::u}},//婌 shu
{1,0,{pysm::q,pyym::i}},//婍 qi
{1,0,{pysm::h,pyym::ui}},//婎 hui
{2,650,{pysm::nop,pyym::nop}},//婏 fan
{1,0,{pysm::w,pyym::o}},//婐 wo
{3,168,{pysm::nop,pyym::nop}},//婑 rui
{1,0,{pysm::t,pyym::an}},//婒 tan
{1,0,{pysm::f,pyym::ei}},//婓 fei
{1,0,{pysm::f,pyym::ei}},//婔 fei
{2,651,{pysm::nop,pyym::nop}},//婕 jie
{1,0,{pysm::t,pyym::ian}},//婖 tian
{1,0,{pysm::n,pyym::i}},//婗 ni
{2,652,{pysm::nop,pyym::nop}},//婘 quan
{1,0,{pysm::j,pyym::ing}},//婙 jing
{1,0,{pysm::h,pyym::un}},//婚 hun
{1,0,{pysm::j,pyym::ing}},//婛 jing
{2,653,{pysm::nop,pyym::nop}},//婜 qian
{1,0,{pysm::d,pyym::ian}},//婝 dian
{1,0,{pysm::x,pyym::ing}},//婞 xing
{1,0,{pysm::h,pyym::u}},//婟 hu
{2,654,{pysm::nop,pyym::nop}},//婠 wan
{1,0,{pysm::l,pyym::ai}},//婡 lai
{1,0,{pysm::b,pyym::i}},//婢 bi
{1,0,{pysm::y,pyym::in}},//婣 yin
{2,655,{pysm::nop,pyym::nop}},//婤 chou
{2,656,{pysm::nop,pyym::nop}},//婥 nao
{1,0,{pysm::f,pyym::u}},//婦 fu
{1,0,{pysm::j,pyym::ing}},//婧 jing
{1,0,{pysm::l,pyym::un}},//婨 lun
{2,657,{pysm::nop,pyym::nop}},//婩 an
{1,0,{pysm::l,pyym::an}},//婪 lan
{2,658,{pysm::nop,pyym::nop}},//婫 kun
{1,0,{pysm::y,pyym::in}},//婬 yin
{1,0,{pysm::y,pyym::a}},//婭 ya
{1,0,{pysm::j,pyym::u}},//婮 ju
{1,0,{pysm::l,pyym::i}},//婯 li
{1,0,{pysm::d,pyym::ian}},//婰 dian
{1,0,{pysm::x,pyym::ian}},//婱 xian
{1,0,{pysm::h,pyym::ua}},//婲 hua
{1,0,{pysm::h,pyym::ua}},//婳 hua
{1,0,{pysm::y,pyym::ing}},//婴 ying
{1,0,{pysm::ch,pyym::an}},//婵 chan
{1,0,{pysm::sh,pyym::en}},//婶 shen
{1,0,{pysm::t,pyym::ing}},//婷 ting
{2,659,{pysm::nop,pyym::nop}},//婸 dang
{1,0,{pysm::y,pyym::ao}},//婹 yao
{3,169,{pysm::nop,pyym::nop}},//婺 wu
{1,0,{pysm::n,pyym::an}},//婻 nan
{2,660,{pysm::nop,pyym::nop}},//婼 chuo
{1,0,{pysm::j,pyym::ia}},//婽 jia
{1,0,{pysm::t,pyym::ou}},//婾 tou
{1,0,{pysm::x,pyym::u}},//婿 xu
{1,0,{pysm::y,pyym::u}},//媀 yu
{1,0,{pysm::w,pyym::ei}},//媁 wei
{2,661,{pysm::nop,pyym::nop}},//媂 di
{1,0,{pysm::r,pyym::ou}},//媃 rou
{1,0,{pysm::m,pyym::ei}},//媄 mei
{1,0,{pysm::d,pyym::an}},//媅 dan
{3,170,{pysm::nop,pyym::nop}},//媆 ruan
{1,0,{pysm::q,pyym::in}},//媇 qin
{1,0,{pysm::h,pyym::ui}},//媈 hui
{1,0,{pysm::w,pyym::o}},//媉 wo
{1,0,{pysm::q,pyym::ian}},//媊 qian
{1,0,{pysm::ch,pyym::un}},//媋 chun
{1,0,{pysm::m,pyym::iao}},//媌 miao
{1,0,{pysm::f,pyym::u}},//媍 fu
{1,0,{pysm::j,pyym::ie}},//媎 jie
{1,0,{pysm::d,pyym::uan}},//媏 duan
{2,662,{pysm::nop,pyym::nop}},//媐 yi
{1,0,{pysm::zh,pyym::ong}},//媑 zhong
{1,0,{pysm::m,pyym::ei}},//媒 mei
{1,0,{pysm::h,pyym::uang}},//媓 huang
{1,0,{pysm::m,pyym::ian}},//媔 mian
{3,171,{pysm::nop,pyym::nop}},//媕 an
{1,0,{pysm::y,pyym::ing}},//媖 ying
{1,0,{pysm::x,pyym::uan}},//媗 xuan
{1,0,{pysm::j,pyym::ie}},//媘 jie
{1,0,{pysm::w,pyym::ei}},//媙 wei
{1,0,{pysm::m,pyym::ei}},//媚 mei
{1,0,{pysm::y,pyym::uan}},//媛 yuan
{1,0,{pysm::zh,pyym::eng}},//媜 zheng
{1,0,{pysm::q,pyym::iu}},//媝 qiu
{4,41,{pysm::nop,pyym::nop}},//媞 shi
{1,0,{pysm::x,pyym::ie}},//媟 xie
{3,172,{pysm::nop,pyym::nop}},//媠 tuo
{1,0,{pysm::l,pyym::ian}},//媡 lian
{1,0,{pysm::m,pyym::ao}},//媢 mao
{1,0,{pysm::r,pyym::an}},//媣 ran
{1,0,{pysm::s,pyym::i}},//媤 si
{1,0,{pysm::p,pyym::ian}},//媥 pian
{1,0,{pysm::w,pyym::ei}},//媦 wei
{1,0,{pysm::w,pyym::a}},//媧 wa
{1,0,{pysm::c,pyym::u}},//媨 cu
{1,0,{pysm::h,pyym::u}},//媩 hu
{3,173,{pysm::nop,pyym::nop}},//媪 ao
{1,0,{pysm::j,pyym::ie}},//媫 jie
{1,0,{pysm::b,pyym::ao}},//媬 bao
{1,0,{pysm::x,pyym::u}},//媭 xu
{2,663,{pysm::nop,pyym::nop}},//媮 tou
{1,0,{pysm::g,pyym::ui}},//媯 gui
{2,664,{pysm::nop,pyym::nop}},//媰 chu
{1,0,{pysm::y,pyym::ao}},//媱 yao
{2,665,{pysm::nop,pyym::nop}},//媲 pi
{1,0,{pysm::x,pyym::i}},//媳 xi
{1,0,{pysm::y,pyym::uan}},//媴 yuan
{2,666,{pysm::nop,pyym::nop}},//媵 ying
{1,0,{pysm::r,pyym::ong}},//媶 rong
{1,0,{pysm::r,pyym::u}},//媷 ru
{1,0,{pysm::ch,pyym::i}},//媸 chi
{1,0,{pysm::l,pyym::iu}},//媹 liu
{1,0,{pysm::m,pyym::ei}},//媺 mei
{1,0,{pysm::p,pyym::an}},//媻 pan
{1,0,{pysm::nop,pyym::ao}},//媼 ao
{1,0,{pysm::m,pyym::a}},//媽 ma
{1,0,{pysm::g,pyym::ou}},//媾 gou
{2,667,{pysm::nop,pyym::nop}},//媿 kui
{2,668,{pysm::nop,pyym::nop}},//嫀 qin
{1,0,{pysm::j,pyym::ia}},//嫁 jia
{1,0,{pysm::s,pyym::ao}},//嫂 sao
{1,0,{pysm::zh,pyym::en}},//嫃 zhen
{1,0,{pysm::y,pyym::uan}},//嫄 yuan
{2,669,{pysm::nop,pyym::nop}},//嫅 jie
{1,0,{pysm::r,pyym::ong}},//嫆 rong
{2,670,{pysm::nop,pyym::nop}},//嫇 ming
{2,671,{pysm::nop,pyym::nop}},//嫈 ying
{1,0,{pysm::j,pyym::i}},//嫉 ji
{1,0,{pysm::s,pyym::u}},//嫊 su
{1,0,{pysm::n,pyym::iao}},//嫋 niao
{1,0,{pysm::x,pyym::ian}},//嫌 xian
{1,0,{pysm::t,pyym::ao}},//嫍 tao
{2,672,{pysm::nop,pyym::nop}},//嫎 pang
{1,0,{pysm::l,pyym::ang}},//嫏 lang
{1,0,{pysm::n,pyym::ao}},//嫐 nao
{1,0,{pysm::b,pyym::ao}},//嫑 bao
{1,0,{pysm::nop,pyym::ai}},//嫒 ai
{1,0,{pysm::p,pyym::i}},//嫓 pi
{1,0,{pysm::p,pyym::in}},//嫔 pin
{1,0,{pysm::y,pyym::i}},//嫕 yi
{2,673,{pysm::nop,pyym::nop}},//嫖 piao
{2,674,{pysm::nop,pyym::nop}},//嫗 yu
{1,0,{pysm::l,pyym::ei}},//嫘 lei
{1,0,{pysm::x,pyym::uan}},//嫙 xuan
{2,675,{pysm::nop,pyym::nop}},//嫚 man
{1,0,{pysm::y,pyym::i}},//嫛 yi
{1,0,{pysm::zh,pyym::ang}},//嫜 zhang
{1,0,{pysm::k,pyym::ang}},//嫝 kang
{1,0,{pysm::y,pyym::ong}},//嫞 yong
{1,0,{pysm::n,pyym::i}},//嫟 ni
{1,0,{pysm::l,pyym::i}},//嫠 li
{1,0,{pysm::d,pyym::i}},//嫡 di
{2,676,{pysm::nop,pyym::nop}},//嫢 gui
{1,0,{pysm::y,pyym::an}},//嫣 yan
{1,0,{pysm::j,pyym::in}},//嫤 jin
{2,677,{pysm::nop,pyym::nop}},//嫥 zhuan
{1,0,{pysm::ch,pyym::ang}},//嫦 chang
{2,678,{pysm::nop,pyym::nop}},//嫧 ze
{2,679,{pysm::nop,pyym::nop}},//嫨 han
{1,0,{pysm::n,pyym::en}},//嫩 nen
{1,0,{pysm::l,pyym::ao}},//嫪 lao
{1,0,{pysm::m,pyym::o}},//嫫 mo
{1,0,{pysm::zh,pyym::e}},//嫬 zhe
{1,0,{pysm::h,pyym::u}},//嫭 hu
{1,0,{pysm::h,pyym::u}},//嫮 hu
{1,0,{pysm::nop,pyym::ao}},//嫯 ao
{1,0,{pysm::n,pyym::en}},//嫰 nen
{1,0,{pysm::q,pyym::iang}},//嫱 qiang
{1,0,{pysm::m,pyym::a}},//嫲 ma
{1,0,{pysm::p,pyym::ie}},//嫳 pie
{1,0,{pysm::g,pyym::u}},//嫴 gu
{1,0,{pysm::w,pyym::u}},//嫵 wu
{2,680,{pysm::nop,pyym::nop}},//嫶 qiao
{1,0,{pysm::t,pyym::uo}},//嫷 tuo
{1,0,{pysm::zh,pyym::an}},//嫸 zhan
{1,0,{pysm::m,pyym::iao}},//嫹 miao
{1,0,{pysm::x,pyym::ian}},//嫺 xian
{1,0,{pysm::x,pyym::ian}},//嫻 xian
{1,0,{pysm::m,pyym::o}},//嫼 mo
{2,681,{pysm::nop,pyym::nop}},//嫽 liao
{1,0,{pysm::l,pyym::ian}},//嫾 lian
{1,0,{pysm::h,pyym::ua}},//嫿 hua
{1,0,{pysm::g,pyym::ui}},//嬀 gui
{1,0,{pysm::d,pyym::eng}},//嬁 deng
{1,0,{pysm::zh,pyym::i}},//嬂 zhi
{1,0,{pysm::x,pyym::u}},//嬃 xu
{1,0,{pysm::y,pyym::i}},//嬄 yi
{1,0,{pysm::h,pyym::ua}},//嬅 hua
{1,0,{pysm::x,pyym::i}},//嬆 xi
{1,0,{pysm::k,pyym::ui}},//嬇 kui
{2,682,{pysm::nop,pyym::nop}},//嬈 rao
{1,0,{pysm::x,pyym::i}},//嬉 xi
{1,0,{pysm::y,pyym::an}},//嬊 yan
{1,0,{pysm::ch,pyym::an}},//嬋 chan
{1,0,{pysm::j,pyym::iao}},//嬌 jiao
{1,0,{pysm::m,pyym::ei}},//嬍 mei
{2,683,{pysm::nop,pyym::nop}},//嬎 fan
{1,0,{pysm::f,pyym::an}},//嬏 fan
{3,174,{pysm::nop,pyym::nop}},//嬐 xian
{1,0,{pysm::y,pyym::i}},//嬑 yi
{1,0,{pysm::h,pyym::ui}},//嬒 hui
{1,0,{pysm::j,pyym::iao}},//嬓 jiao
{1,0,{pysm::f,pyym::u}},//嬔 fu
{1,0,{pysm::sh,pyym::i}},//嬕 shi
{1,0,{pysm::b,pyym::i}},//嬖 bi
{2,684,{pysm::nop,pyym::nop}},//嬗 shan
{1,0,{pysm::s,pyym::ui}},//嬘 sui
{1,0,{pysm::q,pyym::iang}},//嬙 qiang
{1,0,{pysm::l,pyym::ian}},//嬚 lian
{3,175,{pysm::nop,pyym::nop}},//嬛 huan
{1,0,{pysm::x,pyym::in}},//嬜 xin
{1,0,{pysm::n,pyym::iao}},//嬝 niao
{1,0,{pysm::d,pyym::ong}},//嬞 dong
{1,0,{pysm::y,pyym::i}},//嬟 yi
{1,0,{pysm::c,pyym::an}},//嬠 can
{1,0,{pysm::nop,pyym::ai}},//嬡 ai
{1,0,{pysm::n,pyym::iang}},//嬢 niang
{1,0,{pysm::n,pyym::ing}},//嬣 ning
{1,0,{pysm::m,pyym::a}},//嬤 ma
{2,685,{pysm::nop,pyym::nop}},//嬥 tiao
{1,0,{pysm::ch,pyym::ou}},//嬦 chou
{1,0,{pysm::j,pyym::in}},//嬧 jin
{1,0,{pysm::c,pyym::i}},//嬨 ci
{1,0,{pysm::y,pyym::u}},//嬩 yu
{1,0,{pysm::p,pyym::in}},//嬪 pin
{1,0,{pysm::r,pyym::ong}},//嬫 rong
{2,686,{pysm::nop,pyym::nop}},//嬬 ru
{3,176,{pysm::nop,pyym::nop}},//嬭 nai
{1,0,{pysm::y,pyym::an}},//嬮 yan
{1,0,{pysm::t,pyym::ai}},//嬯 tai
{1,0,{pysm::y,pyym::ing}},//嬰 ying
{1,0,{pysm::q,pyym::ian}},//嬱 qian
{1,0,{pysm::n,pyym::iao}},//嬲 niao
{1,0,{pysm::y,pyym::ue}},//嬳 yue
{1,0,{pysm::y,pyym::ing}},//嬴 ying
{1,0,{pysm::m,pyym::ian}},//嬵 mian
{1,0,{pysm::b,pyym::i}},//嬶 bi
{2,687,{pysm::nop,pyym::nop}},//嬷 ma
{1,0,{pysm::sh,pyym::en}},//嬸 shen
{1,0,{pysm::x,pyym::ing}},//嬹 xing
{1,0,{pysm::n,pyym::i}},//嬺 ni
{1,0,{pysm::d,pyym::u}},//嬻 du
{1,0,{pysm::l,pyym::iu}},//嬼 liu
{1,0,{pysm::y,pyym::uan}},//嬽 yuan
{1,0,{pysm::l,pyym::an}},//嬾 lan
{1,0,{pysm::y,pyym::an}},//嬿 yan
{1,0,{pysm::sh,pyym::uang}},//孀 shuang
{1,0,{pysm::l,pyym::ing}},//孁 ling
{1,0,{pysm::j,pyym::iao}},//孂 jiao
{2,688,{pysm::nop,pyym::nop}},//孃 niang
{1,0,{pysm::l,pyym::an}},//孄 lan
{2,689,{pysm::nop,pyym::nop}},//孅 qian
{1,0,{pysm::y,pyym::ing}},//孆 ying
{1,0,{pysm::sh,pyym::uang}},//孇 shuang
{2,690,{pysm::nop,pyym::nop}},//孈 hui
{2,691,{pysm::nop,pyym::nop}},//孉 quan
{1,0,{pysm::m,pyym::i}},//孊 mi
{1,0,{pysm::l,pyym::i}},//孋 li
{2,692,{pysm::nop,pyym::nop}},//孌 luan
{1,0,{pysm::y,pyym::an}},//孍 yan
{3,177,{pysm::nop,pyym::nop}},//孎 zhu
{1,0,{pysm::l,pyym::an}},//孏 lan
{1,0,{pysm::z,pyym::i}},//子 zi
{1,0,{pysm::j,pyym::ie}},//孑 jie
{1,0,{pysm::j,pyym::ue}},//孒 jue
{1,0,{pysm::j,pyym::ue}},//孓 jue
{1,0,{pysm::k,pyym::ong}},//孔 kong
{1,0,{pysm::y,pyym::un}},//孕 yun
{2,693,{pysm::nop,pyym::nop}},//孖 ma
{1,0,{pysm::z,pyym::i}},//字 zi
{1,0,{pysm::c,pyym::un}},//存 cun
{1,0,{pysm::s,pyym::un}},//孙 sun
{1,0,{pysm::f,pyym::u}},//孚 fu
{2,694,{pysm::nop,pyym::nop}},//孛 bei
{1,0,{pysm::z,pyym::i}},//孜 zi
{1,0,{pysm::x,pyym::iao}},//孝 xiao
{1,0,{pysm::x,pyym::in}},//孞 xin
{1,0,{pysm::m,pyym::eng}},//孟 meng
{1,0,{pysm::s,pyym::i}},//孠 si
{1,0,{pysm::t,pyym::ai}},//孡 tai
{1,0,{pysm::b,pyym::ao}},//孢 bao
{1,0,{pysm::j,pyym::i}},//季 ji
{1,0,{pysm::g,pyym::u}},//孤 gu
{1,0,{pysm::n,pyym::u}},//孥 nu
{1,0,{pysm::x,pyym::ue}},//学 xue
{1,0,{pysm::y,pyym::ou}},//孧 you
{2,695,{pysm::nop,pyym::nop}},//孨 zhuan
{1,0,{pysm::h,pyym::ai}},//孩 hai
{1,0,{pysm::l,pyym::uan}},//孪 luan
{2,696,{pysm::nop,pyym::nop}},//孫 sun
{1,0,{pysm::n,pyym::ao}},//孬 nao
{1,0,{pysm::m,pyym::ie}},//孭 mie
{1,0,{pysm::c,pyym::ong}},//孮 cong
{1,0,{pysm::q,pyym::ian}},//孯 qian
{1,0,{pysm::sh,pyym::u}},//孰 shu
{4,42,{pysm::nop,pyym::nop}},//孱 can
{1,0,{pysm::y,pyym::a}},//孲 ya
{1,0,{pysm::z,pyym::i}},//孳 zi
{2,697,{pysm::nop,pyym::nop}},//孴 ni
{1,0,{pysm::f,pyym::u}},//孵 fu
{1,0,{pysm::z,pyym::i}},//孶 zi
{1,0,{pysm::l,pyym::i}},//孷 li
{3,178,{pysm::nop,pyym::nop}},//學 xue
{1,0,{pysm::b,pyym::o}},//孹 bo
{1,0,{pysm::r,pyym::u}},//孺 ru
{1,0,{pysm::n,pyym::ai}},//孻 nai
{1,0,{pysm::n,pyym::ie}},//孼 nie
{1,0,{pysm::n,pyym::ie}},//孽 nie
{1,0,{pysm::y,pyym::ing}},//孾 ying
{1,0,{pysm::l,pyym::uan}},//孿 luan
{1,0,{pysm::m,pyym::ian}},//宀 mian
{2,698,{pysm::nop,pyym::nop}},//宁 ning
{1,0,{pysm::r,pyym::ong}},//宂 rong
{3,179,{pysm::nop,pyym::nop}},//它 ta
{1,0,{pysm::g,pyym::ui}},//宄 gui
{3,180,{pysm::nop,pyym::nop}},//宅 zhai
{1,0,{pysm::q,pyym::iong}},//宆 qiong
{1,0,{pysm::y,pyym::u}},//宇 yu
{1,0,{pysm::sh,pyym::ou}},//守 shou
{1,0,{pysm::nop,pyym::an}},//安 an
{2,699,{pysm::nop,pyym::nop}},//宊 tu
{1,0,{pysm::s,pyym::ong}},//宋 song
{2,700,{pysm::nop,pyym::nop}},//完 wan
{1,0,{pysm::r,pyym::ou}},//宍 rou
{1,0,{pysm::y,pyym::ao}},//宎 yao
{1,0,{pysm::h,pyym::ong}},//宏 hong
{1,0,{pysm::y,pyym::i}},//宐 yi
{1,0,{pysm::j,pyym::ing}},//宑 jing
{1,0,{pysm::zh,pyym::un}},//宒 zhun
{2,701,{pysm::nop,pyym::nop}},//宓 mi
{1,0,{pysm::zh,pyym::u}},//宔 zhu
{1,0,{pysm::d,pyym::ang}},//宕 dang
{1,0,{pysm::h,pyym::ong}},//宖 hong
{1,0,{pysm::z,pyym::ong}},//宗 zong
{1,0,{pysm::g,pyym::uan}},//官 guan
{1,0,{pysm::zh,pyym::ou}},//宙 zhou
{1,0,{pysm::d,pyym::ing}},//定 ding
{4,43,{pysm::nop,pyym::nop}},//宛 wan
{1,0,{pysm::y,pyym::i}},//宜 yi
{1,0,{pysm::b,pyym::ao}},//宝 bao
{1,0,{pysm::sh,pyym::i}},//实 shi
{1,0,{pysm::sh,pyym::i}},//実 shi
{1,0,{pysm::ch,pyym::ong}},//宠 chong
{1,0,{pysm::sh,pyym::en}},//审 shen
{2,702,{pysm::nop,pyym::nop}},//客 ke
{1,0,{pysm::x,pyym::uan}},//宣 xuan
{1,0,{pysm::sh,pyym::i}},//室 shi
{1,0,{pysm::y,pyym::ou}},//宥 you
{1,0,{pysm::h,pyym::uan}},//宦 huan
{1,0,{pysm::y,pyym::i}},//宧 yi
{1,0,{pysm::t,pyym::iao}},//宨 tiao
{1,0,{pysm::sh,pyym::i}},//宩 shi
{2,703,{pysm::nop,pyym::nop}},//宪 xian
{1,0,{pysm::g,pyym::ong}},//宫 gong
{1,0,{pysm::ch,pyym::eng}},//宬 cheng
{1,0,{pysm::q,pyym::un}},//宭 qun
{1,0,{pysm::g,pyym::ong}},//宮 gong
{1,0,{pysm::x,pyym::iao}},//宯 xiao
{1,0,{pysm::z,pyym::ai}},//宰 zai
{1,0,{pysm::zh,pyym::a}},//宱 zha
{2,704,{pysm::nop,pyym::nop}},//宲 bao
{2,705,{pysm::nop,pyym::nop}},//害 hai
{1,0,{pysm::y,pyym::an}},//宴 yan
{1,0,{pysm::x,pyym::iao}},//宵 xiao
{3,181,{pysm::nop,pyym::nop}},//家 jia
{1,0,{pysm::sh,pyym::en}},//宷 shen
{1,0,{pysm::ch,pyym::en}},//宸 chen
{2,706,{pysm::nop,pyym::nop}},//容 rong
{1,0,{pysm::h,pyym::uang}},//宺 huang
{1,0,{pysm::m,pyym::i}},//宻 mi
{1,0,{pysm::k,pyym::ou}},//宼 kou
{1,0,{pysm::k,pyym::uan}},//宽 kuan
{1,0,{pysm::b,pyym::in}},//宾 bin
{3,182,{pysm::nop,pyym::nop}},//宿 su
{1,0,{pysm::c,pyym::ai}},//寀 cai
{1,0,{pysm::z,pyym::an}},//寁 zan
{1,0,{pysm::j,pyym::i}},//寂 ji
{1,0,{pysm::y,pyym::uan}},//寃 yuan
{1,0,{pysm::j,pyym::i}},//寄 ji
{1,0,{pysm::y,pyym::in}},//寅 yin
{1,0,{pysm::m,pyym::i}},//密 mi
{1,0,{pysm::k,pyym::ou}},//寇 kou
{1,0,{pysm::q,pyym::ing}},//寈 qing
{1,0,{pysm::h,pyym::e}},//寉 he
{1,0,{pysm::zh,pyym::en}},//寊 zhen
{1,0,{pysm::j,pyym::ian}},//寋 jian
{1,0,{pysm::f,pyym::u}},//富 fu
{1,0,{pysm::n,pyym::ing}},//寍 ning
{1,0,{pysm::b,pyym::ing}},//寎 bing
{1,0,{pysm::h,pyym::uan}},//寏 huan
{1,0,{pysm::m,pyym::ei}},//寐 mei
{1,0,{pysm::q,pyym::in}},//寑 qin
{1,0,{pysm::h,pyym::an}},//寒 han
{1,0,{pysm::y,pyym::u}},//寓 yu
{1,0,{pysm::sh,pyym::i}},//寔 shi
{1,0,{pysm::n,pyym::ing}},//寕 ning
{1,0,{pysm::j,pyym::in}},//寖 jin
{1,0,{pysm::n,pyym::ing}},//寗 ning
{2,707,{pysm::nop,pyym::nop}},//寘 zhi
{1,0,{pysm::y,pyym::u}},//寙 yu
{1,0,{pysm::b,pyym::ao}},//寚 bao
{1,0,{pysm::k,pyym::uan}},//寛 kuan
{1,0,{pysm::n,pyym::ing}},//寜 ning
{1,0,{pysm::q,pyym::in}},//寝 qin
{1,0,{pysm::m,pyym::o}},//寞 mo
{2,708,{pysm::nop,pyym::nop}},//察 cha
{3,183,{pysm::nop,pyym::nop}},//寠 ju
{1,0,{pysm::g,pyym::ua}},//寡 gua
{1,0,{pysm::q,pyym::in}},//寢 qin
{1,0,{pysm::h,pyym::u}},//寣 hu
{1,0,{pysm::w,pyym::u}},//寤 wu
{1,0,{pysm::l,pyym::iao}},//寥 liao
{2,709,{pysm::nop,pyym::nop}},//實 shi
{1,0,{pysm::n,pyym::ing}},//寧 ning
{3,184,{pysm::nop,pyym::nop}},//寨 zhai
{2,710,{pysm::nop,pyym::nop}},//審 shen
{1,0,{pysm::w,pyym::ei}},//寪 wei
{1,0,{pysm::x,pyym::ie}},//寫 xie
{1,0,{pysm::k,pyym::uan}},//寬 kuan
{1,0,{pysm::h,pyym::ui}},//寭 hui
{1,0,{pysm::l,pyym::iao}},//寮 liao
{1,0,{pysm::j,pyym::un}},//寯 jun
{2,711,{pysm::nop,pyym::nop}},//寰 huan
{1,0,{pysm::y,pyym::i}},//寱 yi
{1,0,{pysm::y,pyym::i}},//寲 yi
{1,0,{pysm::b,pyym::ao}},//寳 bao
{1,0,{pysm::q,pyym::in}},//寴 qin
{2,712,{pysm::nop,pyym::nop}},//寵 chong
{1,0,{pysm::b,pyym::ao}},//寶 bao
{1,0,{pysm::f,pyym::eng}},//寷 feng
{1,0,{pysm::c,pyym::un}},//寸 cun
{1,0,{pysm::d,pyym::ui}},//对 dui
{2,713,{pysm::nop,pyym::nop}},//寺 si
{2,714,{pysm::nop,pyym::nop}},//寻 xun
{1,0,{pysm::d,pyym::ao}},//导 dao
{2,715,{pysm::nop,pyym::nop}},//寽 lü
{1,0,{pysm::d,pyym::ui}},//対 dui
{1,0,{pysm::sh,pyym::ou}},//寿 shou
{1,0,{pysm::p,pyym::o}},//尀 po
{2,716,{pysm::nop,pyym::nop}},//封 feng
{1,0,{pysm::zh,pyym::uan}},//専 zhuan
{3,185,{pysm::nop,pyym::nop}},//尃 fu
{3,186,{pysm::nop,pyym::nop}},//射 she
{2,717,{pysm::nop,pyym::nop}},//尅 ke
{2,718,{pysm::nop,pyym::nop}},//将 jiang
{3,187,{pysm::nop,pyym::nop}},//將 jiang
{3,188,{pysm::nop,pyym::nop}},//專 zhuan
{3,189,{pysm::nop,pyym::nop}},//尉 wei
{1,0,{pysm::z,pyym::un}},//尊 zun
{2,719,{pysm::nop,pyym::nop}},//尋 xun
{2,720,{pysm::nop,pyym::nop}},//尌 shu
{1,0,{pysm::d,pyym::ui}},//對 dui
{1,0,{pysm::d,pyym::ao}},//導 dao
{1,0,{pysm::x,pyym::iao}},//小 xiao
{2,721,{pysm::nop,pyym::nop}},//尐 jie
{1,0,{pysm::sh,pyym::ao}},//少 shao
{1,0,{pysm::nop,pyym::er}},//尒 er
{1,0,{pysm::nop,pyym::er}},//尓 er
{1,0,{pysm::nop,pyym::er}},//尔 er
{1,0,{pysm::g,pyym::a}},//尕 ga
{1,0,{pysm::j,pyym::ian}},//尖 jian
{1,0,{pysm::sh,pyym::u}},//尗 shu
{1,0,{pysm::ch,pyym::en}},//尘 chen
{1,0,{pysm::sh,pyym::ang}},//尙 shang
{2,722,{pysm::nop,pyym::nop}},//尚 shang
{1,0,{pysm::m,pyym::o}},//尛 mo
{1,0,{pysm::g,pyym::a}},//尜 ga
{1,0,{pysm::ch,pyym::ang}},//尝 chang
{1,0,{pysm::l,pyym::iao}},//尞 liao
{1,0,{pysm::x,pyym::ian}},//尟 xian
{1,0,{pysm::x,pyym::ian}},//尠 xian
{1,0,{pysm::k,pyym::un}},//尡 kun
{2,723,{pysm::nop,pyym::nop}},//尢 you
{1,0,{pysm::w,pyym::ang}},//尣 wang
{1,0,{pysm::y,pyym::ou}},//尤 you
{2,724,{pysm::nop,pyym::nop}},//尥 liao
{1,0,{pysm::l,pyym::iao}},//尦 liao
{1,0,{pysm::y,pyym::ao}},//尧 yao
{3,190,{pysm::nop,pyym::nop}},//尨 mang
{1,0,{pysm::w,pyym::ang}},//尩 wang
{1,0,{pysm::w,pyym::ang}},//尪 wang
{1,0,{pysm::w,pyym::ang}},//尫 wang
{1,0,{pysm::g,pyym::a}},//尬 ga
{1,0,{pysm::y,pyym::ao}},//尭 yao
{1,0,{pysm::d,pyym::uo}},//尮 duo
{1,0,{pysm::k,pyym::ui}},//尯 kui
{1,0,{pysm::zh,pyym::ong}},//尰 zhong
{1,0,{pysm::j,pyym::iu}},//就 jiu
{1,0,{pysm::g,pyym::an}},//尲 gan
{1,0,{pysm::g,pyym::u}},//尳 gu
{1,0,{pysm::g,pyym::an}},//尴 gan
{2,725,{pysm::nop,pyym::nop}},//尵 tui
{1,0,{pysm::g,pyym::an}},//尶 gan
{1,0,{pysm::g,pyym::an}},//尷 gan
{1,0,{pysm::sh,pyym::i}},//尸 shi
{2,726,{pysm::nop,pyym::nop}},//尹 yin
{2,727,{pysm::nop,pyym::nop}},//尺 chi
{1,0,{pysm::k,pyym::ao}},//尻 kao
{1,0,{pysm::n,pyym::i}},//尼 ni
{1,0,{pysm::j,pyym::in}},//尽 jin
{2,728,{pysm::nop,pyym::nop}},//尾 wei
{2,729,{pysm::nop,pyym::nop}},//尿 niao
{1,0,{pysm::j,pyym::u}},//局 ju
{1,0,{pysm::p,pyym::i}},//屁 pi
{1,0,{pysm::c,pyym::eng}},//层 ceng
{1,0,{pysm::x,pyym::i}},//屃 xi
{1,0,{pysm::b,pyym::i}},//屄 bi
{2,730,{pysm::nop,pyym::nop}},//居 ju
{1,0,{pysm::j,pyym::ie}},//屆 jie
{1,0,{pysm::t,pyym::ian}},//屇 tian
{4,44,{pysm::nop,pyym::nop}},//屈 qu
{1,0,{pysm::t,pyym::i}},//屉 ti
{1,0,{pysm::j,pyym::ie}},//届 jie
{1,0,{pysm::w,pyym::u}},//屋 wu
{1,0,{pysm::d,pyym::iao}},//屌 diao
{1,0,{pysm::sh,pyym::i}},//屍 shi
{2,731,{pysm::nop,pyym::nop}},//屎 shi
{2,732,{pysm::nop,pyym::nop}},//屏 ping
{1,0,{pysm::j,pyym::i}},//屐 ji
{1,0,{pysm::x,pyym::ie}},//屑 xie
{1,0,{pysm::zh,pyym::en}},//屒 zhen
{1,0,{pysm::x,pyym::ie}},//屓 xie
{1,0,{pysm::n,pyym::i}},//屔 ni
{1,0,{pysm::zh,pyym::an}},//展 zhan
{1,0,{pysm::x,pyym::i}},//屖 xi
{1,0,{pysm::w,pyym::ei}},//屗 wei
{1,0,{pysm::m,pyym::an}},//屘 man
{1,0,{pysm::nop,pyym::e}},//屙 e
{1,0,{pysm::l,pyym::ou}},//屚 lou
{1,0,{pysm::p,pyym::ing}},//屛 ping
{1,0,{pysm::t,pyym::i}},//屜 ti
{1,0,{pysm::f,pyym::ei}},//屝 fei
{2,733,{pysm::nop,pyym::nop}},//属 shu
{2,734,{pysm::nop,pyym::nop}},//屟 xie
{1,0,{pysm::t,pyym::u}},//屠 tu
{1,0,{pysm::l,pyym::v}},//屡 lü
{1,0,{pysm::l,pyym::v}},//屢 lü
{1,0,{pysm::x,pyym::i}},//屣 xi
{1,0,{pysm::c,pyym::eng}},//層 ceng
{1,0,{pysm::l,pyym::v}},//履 lü
{1,0,{pysm::j,pyym::u}},//屦 ju
{1,0,{pysm::x,pyym::ie}},//屧 xie
{1,0,{pysm::j,pyym::u}},//屨 ju
{1,0,{pysm::j,pyym::ue}},//屩 jue
{1,0,{pysm::l,pyym::iao}},//屪 liao
{1,0,{pysm::j,pyym::ue}},//屫 jue
{2,735,{pysm::nop,pyym::nop}},//屬 shu
{1,0,{pysm::x,pyym::i}},//屭 xi
{2,736,{pysm::nop,pyym::nop}},//屮 che
{2,737,{pysm::nop,pyym::nop}},//屯 tun
{3,191,{pysm::nop,pyym::nop}},//屰 ni
{1,0,{pysm::sh,pyym::an}},//山 shan
{1,0,{pysm::w,pyym::a}},//屲 wa
{1,0,{pysm::x,pyym::ian}},//屳 xian
{1,0,{pysm::l,pyym::i}},//屴 li
{2,738,{pysm::nop,pyym::nop}},//屵 e
{1,0,{pysm::h,pyym::ui}},//屶 hui
{1,0,{pysm::h,pyym::ui}},//屷 hui
{2,739,{pysm::nop,pyym::nop}},//屸 long
{2,740,{pysm::nop,pyym::nop}},//屹 yi
{1,0,{pysm::q,pyym::i}},//屺 qi
{1,0,{pysm::r,pyym::en}},//屻 ren
{1,0,{pysm::w,pyym::u}},//屼 wu
{2,741,{pysm::nop,pyym::nop}},//屽 han
{1,0,{pysm::sh,pyym::en}},//屾 shen
{1,0,{pysm::y,pyym::u}},//屿 yu
{1,0,{pysm::ch,pyym::u}},//岀 chu
{1,0,{pysm::s,pyym::ui}},//岁 sui
{2,742,{pysm::nop,pyym::nop}},//岂 qi
{1,0,{pysm::r,pyym::en}},//岃 ren
{1,0,{pysm::y,pyym::ue}},//岄 yue
{1,0,{pysm::b,pyym::an}},//岅 ban
{1,0,{pysm::y,pyym::ao}},//岆 yao
{1,0,{pysm::nop,pyym::ang}},//岇 ang
{2,743,{pysm::nop,pyym::nop}},//岈 ya
{1,0,{pysm::w,pyym::u}},//岉 wu
{1,0,{pysm::j,pyym::ie}},//岊 jie
{2,744,{pysm::nop,pyym::nop}},//岋 e
{1,0,{pysm::j,pyym::i}},//岌 ji
{1,0,{pysm::q,pyym::ian}},//岍 qian
{2,745,{pysm::nop,pyym::nop}},//岎 fen
{1,0,{pysm::w,pyym::an}},//岏 wan
{1,0,{pysm::q,pyym::i}},//岐 qi
{1,0,{pysm::c,pyym::en}},//岑 cen
{1,0,{pysm::q,pyym::ian}},//岒 qian
{1,0,{pysm::q,pyym::i}},//岓 qi
{1,0,{pysm::ch,pyym::a}},//岔 cha
{1,0,{pysm::j,pyym::ie}},//岕 jie
{1,0,{pysm::q,pyym::u}},//岖 qu
{1,0,{pysm::g,pyym::ang}},//岗 gang
{1,0,{pysm::x,pyym::ian}},//岘 xian
{1,0,{pysm::nop,pyym::ao}},//岙 ao
{1,0,{pysm::l,pyym::an}},//岚 lan
{1,0,{pysm::d,pyym::ao}},//岛 dao
{1,0,{pysm::b,pyym::a}},//岜 ba
{1,0,{pysm::z,pyym::uo}},//岝 zuo
{1,0,{pysm::z,pyym::uo}},//岞 zuo
{1,0,{pysm::y,pyym::ang}},//岟 yang
{1,0,{pysm::j,pyym::u}},//岠 ju
{1,0,{pysm::g,pyym::ang}},//岡 gang
{1,0,{pysm::k,pyym::e}},//岢 ke
{1,0,{pysm::g,pyym::ou}},//岣 gou
{1,0,{pysm::x,pyym::ue}},//岤 xue
{1,0,{pysm::p,pyym::o}},//岥 po
{1,0,{pysm::l,pyym::i}},//岦 li
{1,0,{pysm::t,pyym::iao}},//岧 tiao
{3,192,{pysm::nop,pyym::nop}},//岨 qu
{1,0,{pysm::y,pyym::an}},//岩 yan
{1,0,{pysm::f,pyym::u}},//岪 fu
{1,0,{pysm::x,pyym::iu}},//岫 xiu
{1,0,{pysm::j,pyym::ia}},//岬 jia
{1,0,{pysm::l,pyym::ing}},//岭 ling
{1,0,{pysm::t,pyym::uo}},//岮 tuo
{1,0,{pysm::p,pyym::i}},//岯 pi
{1,0,{pysm::nop,pyym::ao}},//岰 ao
{1,0,{pysm::d,pyym::ai}},//岱 dai
{1,0,{pysm::k,pyym::uang}},//岲 kuang
{1,0,{pysm::y,pyym::ue}},//岳 yue
{1,0,{pysm::q,pyym::u}},//岴 qu
{1,0,{pysm::h,pyym::u}},//岵 hu
{1,0,{pysm::p,pyym::o}},//岶 po
{1,0,{pysm::m,pyym::in}},//岷 min
{1,0,{pysm::nop,pyym::an}},//岸 an
{1,0,{pysm::t,pyym::iao}},//岹 tiao
{1,0,{pysm::l,pyym::ing}},//岺 ling
{1,0,{pysm::ch,pyym::i}},//岻 chi
{1,0,{pysm::p,pyym::ing}},//岼 ping
{1,0,{pysm::d,pyym::ong}},//岽 dong
{1,0,{pysm::h,pyym::an}},//岾 han
{1,0,{pysm::k,pyym::ui}},//岿 kui
{1,0,{pysm::x,pyym::iu}},//峀 xiu
{1,0,{pysm::m,pyym::ao}},//峁 mao
{1,0,{pysm::t,pyym::ong}},//峂 tong
{1,0,{pysm::x,pyym::ue}},//峃 xue
{1,0,{pysm::y,pyym::i}},//峄 yi
{1,0,{pysm::b,pyym::ian}},//峅 bian
{1,0,{pysm::h,pyym::e}},//峆 he
{2,746,{pysm::nop,pyym::nop}},//峇 ba
{1,0,{pysm::l,pyym::uo}},//峈 luo
{1,0,{pysm::nop,pyym::e}},//峉 e
{2,747,{pysm::nop,pyym::nop}},//峊 fu
{1,0,{pysm::x,pyym::un}},//峋 xun
{1,0,{pysm::d,pyym::ie}},//峌 die
{1,0,{pysm::l,pyym::u}},//峍 lu
{1,0,{pysm::nop,pyym::en}},//峎 en
{1,0,{pysm::nop,pyym::er}},//峏 er
{1,0,{pysm::g,pyym::ai}},//峐 gai
{1,0,{pysm::q,pyym::uan}},//峑 quan
{2,748,{pysm::nop,pyym::nop}},//峒 dong
{1,0,{pysm::y,pyym::i}},//峓 yi
{1,0,{pysm::m,pyym::u}},//峔 mu
{1,0,{pysm::sh,pyym::i}},//峕 shi
{1,0,{pysm::nop,pyym::an}},//峖 an
{1,0,{pysm::w,pyym::ei}},//峗 wei
{1,0,{pysm::h,pyym::uan}},//峘 huan
{2,749,{pysm::nop,pyym::nop}},//峙 zhi
{1,0,{pysm::m,pyym::i}},//峚 mi
{2,750,{pysm::nop,pyym::nop}},//峛 li
{1,0,{pysm::j,pyym::i}},//峜 ji
{1,0,{pysm::t,pyym::ong}},//峝 tong
{1,0,{pysm::w,pyym::ei}},//峞 wei
{1,0,{pysm::y,pyym::ou}},//峟 you
{1,0,{pysm::q,pyym::ia}},//峠 qia
{1,0,{pysm::x,pyym::ia}},//峡 xia
{1,0,{pysm::l,pyym::i}},//峢 li
{1,0,{pysm::y,pyym::ao}},//峣 yao
{2,751,{pysm::nop,pyym::nop}},//峤 jiao
{1,0,{pysm::zh,pyym::eng}},//峥 zheng
{1,0,{pysm::l,pyym::uan}},//峦 luan
{1,0,{pysm::j,pyym::iao}},//峧 jiao
{1,0,{pysm::nop,pyym::e}},//峨 e
{1,0,{pysm::nop,pyym::e}},//峩 e
{1,0,{pysm::y,pyym::u}},//峪 yu
{2,752,{pysm::nop,pyym::nop}},//峫 xie
{1,0,{pysm::b,pyym::u}},//峬 bu
{1,0,{pysm::q,pyym::iao}},//峭 qiao
{1,0,{pysm::q,pyym::un}},//峮 qun
{1,0,{pysm::f,pyym::eng}},//峯 feng
{1,0,{pysm::f,pyym::eng}},//峰 feng
{1,0,{pysm::n,pyym::ao}},//峱 nao
{1,0,{pysm::l,pyym::i}},//峲 li
{1,0,{pysm::y,pyym::ou}},//峳 you
{1,0,{pysm::x,pyym::ian}},//峴 xian
{1,0,{pysm::r,pyym::ong}},//峵 rong
{1,0,{pysm::d,pyym::ao}},//島 dao
{1,0,{pysm::sh,pyym::en}},//峷 shen
{1,0,{pysm::ch,pyym::eng}},//峸 cheng
{1,0,{pysm::t,pyym::u}},//峹 tu
{1,0,{pysm::g,pyym::eng}},//峺 geng
{1,0,{pysm::j,pyym::un}},//峻 jun
{1,0,{pysm::g,pyym::ao}},//峼 gao
{1,0,{pysm::x,pyym::ia}},//峽 xia
{1,0,{pysm::y,pyym::in}},//峾 yin
{2,753,{pysm::nop,pyym::nop}},//峿 yu
{1,0,{pysm::l,pyym::ang}},//崀 lang
{1,0,{pysm::k,pyym::an}},//崁 kan
{1,0,{pysm::l,pyym::ao}},//崂 lao
{1,0,{pysm::l,pyym::ai}},//崃 lai
{1,0,{pysm::x,pyym::ian}},//崄 xian
{1,0,{pysm::q,pyym::ue}},//崅 que
{1,0,{pysm::k,pyym::ong}},//崆 kong
{1,0,{pysm::ch,pyym::ong}},//崇 chong
{1,0,{pysm::ch,pyym::ong}},//崈 chong
{1,0,{pysm::t,pyym::a}},//崉 ta
{1,0,{pysm::l,pyym::in}},//崊 lin
{1,0,{pysm::h,pyym::ua}},//崋 hua
{1,0,{pysm::j,pyym::u}},//崌 ju
{1,0,{pysm::l,pyym::ai}},//崍 lai
{2,754,{pysm::nop,pyym::nop}},//崎 qi
{1,0,{pysm::m,pyym::in}},//崏 min
{1,0,{pysm::k,pyym::un}},//崐 kun
{1,0,{pysm::k,pyym::un}},//崑 kun
{2,755,{pysm::nop,pyym::nop}},//崒 zu
{1,0,{pysm::g,pyym::u}},//崓 gu
{1,0,{pysm::c,pyym::ui}},//崔 cui
{1,0,{pysm::y,pyym::a}},//崕 ya
{1,0,{pysm::y,pyym::a}},//崖 ya
{1,0,{pysm::g,pyym::ang}},//崗 gang
{1,0,{pysm::l,pyym::un}},//崘 lun
{1,0,{pysm::l,pyym::un}},//崙 lun
{2,756,{pysm::nop,pyym::nop}},//崚 leng
{2,757,{pysm::nop,pyym::nop}},//崛 jue
{1,0,{pysm::d,pyym::uo}},//崜 duo
{1,0,{pysm::zh,pyym::eng}},//崝 zheng
{1,0,{pysm::g,pyym::uo}},//崞 guo
{1,0,{pysm::y,pyym::in}},//崟 yin
{1,0,{pysm::d,pyym::ong}},//崠 dong
{1,0,{pysm::h,pyym::an}},//崡 han
{1,0,{pysm::zh,pyym::eng}},//崢 zheng
{1,0,{pysm::w,pyym::ei}},//崣 wei
{2,758,{pysm::nop,pyym::nop}},//崤 xiao
{2,759,{pysm::nop,pyym::nop}},//崥 pi
{1,0,{pysm::y,pyym::an}},//崦 yan
{1,0,{pysm::s,pyym::ong}},//崧 song
{1,0,{pysm::j,pyym::ie}},//崨 jie
{1,0,{pysm::b,pyym::eng}},//崩 beng
{1,0,{pysm::z,pyym::u}},//崪 zu
{2,760,{pysm::nop,pyym::nop}},//崫 ku
{1,0,{pysm::d,pyym::ong}},//崬 dong
{1,0,{pysm::zh,pyym::an}},//崭 zhan
{1,0,{pysm::g,pyym::u}},//崮 gu
{1,0,{pysm::y,pyym::in}},//崯 yin
{1,0,{pysm::z,pyym::i}},//崰 zi
{1,0,{pysm::z,pyym::e}},//崱 ze
{1,0,{pysm::h,pyym::uang}},//崲 huang
{1,0,{pysm::y,pyym::u}},//崳 yu
{2,761,{pysm::nop,pyym::nop}},//崴 wai
{2,762,{pysm::nop,pyym::nop}},//崵 yang
{1,0,{pysm::f,pyym::eng}},//崶 feng
{1,0,{pysm::q,pyym::iu}},//崷 qiu
{1,0,{pysm::y,pyym::ang}},//崸 yang
{1,0,{pysm::t,pyym::i}},//崹 ti
{1,0,{pysm::y,pyym::i}},//崺 yi
{1,0,{pysm::zh,pyym::i}},//崻 zhi
{2,763,{pysm::nop,pyym::nop}},//崼 shi
{1,0,{pysm::z,pyym::ai}},//崽 zai
{1,0,{pysm::y,pyym::ao}},//崾 yao
{1,0,{pysm::nop,pyym::e}},//崿 e
{1,0,{pysm::zh,pyym::u}},//嵀 zhu
{2,764,{pysm::nop,pyym::nop}},//嵁 kan
{1,0,{pysm::l,pyym::v}},//嵂 lü
{1,0,{pysm::y,pyym::an}},//嵃 yan
{1,0,{pysm::m,pyym::ei}},//嵄 mei
{1,0,{pysm::h,pyym::an}},//嵅 han
{1,0,{pysm::j,pyym::i}},//嵆 ji
{2,765,{pysm::nop,pyym::nop}},//嵇 ji
{1,0,{pysm::h,pyym::uan}},//嵈 huan
{1,0,{pysm::t,pyym::ing}},//嵉 ting
{2,766,{pysm::nop,pyym::nop}},//嵊 sheng
{1,0,{pysm::m,pyym::ei}},//嵋 mei
{3,193,{pysm::nop,pyym::nop}},//嵌 qian
{2,767,{pysm::nop,pyym::nop}},//嵍 wu
{1,0,{pysm::y,pyym::u}},//嵎 yu
{1,0,{pysm::z,pyym::ong}},//嵏 zong
{1,0,{pysm::l,pyym::an}},//嵐 lan
{2,768,{pysm::nop,pyym::nop}},//嵑 ke
{2,769,{pysm::nop,pyym::nop}},//嵒 yan
{1,0,{pysm::y,pyym::an}},//嵓 yan
{1,0,{pysm::w,pyym::ei}},//嵔 wei
{1,0,{pysm::z,pyym::ong}},//嵕 zong
{1,0,{pysm::ch,pyym::a}},//嵖 cha
{1,0,{pysm::s,pyym::ui}},//嵗 sui
{1,0,{pysm::r,pyym::ong}},//嵘 rong
{1,0,{pysm::k,pyym::e}},//嵙 ke
{1,0,{pysm::q,pyym::in}},//嵚 qin
{1,0,{pysm::y,pyym::u}},//嵛 yu
{1,0,{pysm::q,pyym::i}},//嵜 qi
{1,0,{pysm::l,pyym::ou}},//嵝 lou
{1,0,{pysm::t,pyym::u}},//嵞 tu
{1,0,{pysm::d,pyym::ui}},//嵟 dui
{1,0,{pysm::x,pyym::i}},//嵠 xi
{1,0,{pysm::w,pyym::eng}},//嵡 weng
{1,0,{pysm::c,pyym::ang}},//嵢 cang
{2,770,{pysm::nop,pyym::nop}},//嵣 dang
{2,771,{pysm::nop,pyym::nop}},//嵤 rong
{1,0,{pysm::j,pyym::ie}},//嵥 jie
{2,772,{pysm::nop,pyym::nop}},//嵦 kai
{1,0,{pysm::l,pyym::iu}},//嵧 liu
{1,0,{pysm::w,pyym::u}},//嵨 wu
{1,0,{pysm::s,pyym::ong}},//嵩 song
{2,773,{pysm::nop,pyym::nop}},//嵪 qiao
{1,0,{pysm::z,pyym::i}},//嵫 zi
{1,0,{pysm::w,pyym::ei}},//嵬 wei
{1,0,{pysm::b,pyym::eng}},//嵭 beng
{1,0,{pysm::d,pyym::ian}},//嵮 dian
{2,774,{pysm::nop,pyym::nop}},//嵯 cuo
{1,0,{pysm::q,pyym::ian}},//嵰 qian
{1,0,{pysm::y,pyym::ong}},//嵱 yong
{1,0,{pysm::n,pyym::ie}},//嵲 nie
{1,0,{pysm::c,pyym::uo}},//嵳 cuo
{1,0,{pysm::j,pyym::i}},//嵴 ji
{1,0,{pysm::sh,pyym::i}},//嵵 shi
{1,0,{pysm::r,pyym::uo}},//嵶 ruo
{1,0,{pysm::s,pyym::ong}},//嵷 song
{1,0,{pysm::z,pyym::ong}},//嵸 zong
{1,0,{pysm::j,pyym::iang}},//嵹 jiang
{2,775,{pysm::nop,pyym::nop}},//嵺 liao
{1,0,{pysm::k,pyym::ang}},//嵻 kang
{1,0,{pysm::ch,pyym::an}},//嵼 chan
{2,776,{pysm::nop,pyym::nop}},//嵽 die
{2,777,{pysm::nop,pyym::nop}},//嵾 cen
{1,0,{pysm::d,pyym::ing}},//嵿 ding
{1,0,{pysm::t,pyym::u}},//嶀 tu
{1,0,{pysm::l,pyym::ou}},//嶁 lou
{1,0,{pysm::zh,pyym::ang}},//嶂 zhang
{1,0,{pysm::zh,pyym::an}},//嶃 zhan
{2,778,{pysm::nop,pyym::nop}},//嶄 zhan
{1,0,{pysm::nop,pyym::ao}},//嶅 ao
{1,0,{pysm::c,pyym::ao}},//嶆 cao
{1,0,{pysm::q,pyym::u}},//嶇 qu
{1,0,{pysm::q,pyym::iang}},//嶈 qiang
{2,779,{pysm::nop,pyym::nop}},//嶉 cui
{1,0,{pysm::z,pyym::ui}},//嶊 zui
{1,0,{pysm::d,pyym::ao}},//嶋 dao
{1,0,{pysm::d,pyym::ao}},//嶌 dao
{1,0,{pysm::x,pyym::i}},//嶍 xi
{1,0,{pysm::y,pyym::u}},//嶎 yu
{2,780,{pysm::nop,pyym::nop}},//嶏 pei
{1,0,{pysm::l,pyym::ong}},//嶐 long
{1,0,{pysm::x,pyym::iang}},//嶑 xiang
{2,781,{pysm::nop,pyym::nop}},//嶒 ceng
{1,0,{pysm::b,pyym::o}},//嶓 bo
{1,0,{pysm::q,pyym::in}},//嶔 qin
{1,0,{pysm::j,pyym::iao}},//嶕 jiao
{1,0,{pysm::y,pyym::an}},//嶖 yan
{1,0,{pysm::l,pyym::ao}},//嶗 lao
{1,0,{pysm::zh,pyym::an}},//嶘 zhan
{1,0,{pysm::l,pyym::in}},//嶙 lin
{1,0,{pysm::l,pyym::iao}},//嶚 liao
{1,0,{pysm::l,pyym::iao}},//嶛 liao
{2,782,{pysm::nop,pyym::nop}},//嶜 jin
{1,0,{pysm::d,pyym::eng}},//嶝 deng
{1,0,{pysm::d,pyym::uo}},//嶞 duo
{1,0,{pysm::z,pyym::un}},//嶟 zun
{2,783,{pysm::nop,pyym::nop}},//嶠 jiao
{2,784,{pysm::nop,pyym::nop}},//嶡 gui
{1,0,{pysm::y,pyym::ao}},//嶢 yao
{1,0,{pysm::j,pyym::iao}},//嶣 jiao
{1,0,{pysm::y,pyym::ao}},//嶤 yao
{1,0,{pysm::j,pyym::ue}},//嶥 jue
{2,785,{pysm::nop,pyym::nop}},//嶦 zhan
{1,0,{pysm::y,pyym::i}},//嶧 yi
{1,0,{pysm::x,pyym::ue}},//嶨 xue
{1,0,{pysm::n,pyym::ao}},//嶩 nao
{1,0,{pysm::y,pyym::e}},//嶪 ye
{1,0,{pysm::y,pyym::e}},//嶫 ye
{1,0,{pysm::y,pyym::i}},//嶬 yi
{1,0,{pysm::n,pyym::ie}},//嶭 nie
{2,786,{pysm::nop,pyym::nop}},//嶮 xian
{1,0,{pysm::j,pyym::i}},//嶯 ji
{2,787,{pysm::nop,pyym::nop}},//嶰 xie
{1,0,{pysm::k,pyym::e}},//嶱 ke
{1,0,{pysm::x,pyym::i}},//嶲 xi
{1,0,{pysm::d,pyym::i}},//嶳 di
{1,0,{pysm::nop,pyym::ao}},//嶴 ao
{1,0,{pysm::z,pyym::ui}},//嶵 zui
{1,0,{pysm::w,pyym::ei}},//嶶 wei
{2,788,{pysm::nop,pyym::nop}},//嶷 yi
{1,0,{pysm::r,pyym::ong}},//嶸 rong
{1,0,{pysm::d,pyym::ao}},//嶹 dao
{1,0,{pysm::l,pyym::ing}},//嶺 ling
{1,0,{pysm::j,pyym::ie}},//嶻 jie
{2,789,{pysm::nop,pyym::nop}},//嶼 yu
{1,0,{pysm::y,pyym::ue}},//嶽 yue
{1,0,{pysm::y,pyym::in}},//嶾 yin
{1,0,{pysm::r,pyym::u}},//嶿 ru
{1,0,{pysm::j,pyym::ie}},//巀 jie
{2,790,{pysm::nop,pyym::nop}},//巁 li
{3,194,{pysm::nop,pyym::nop}},//巂 gui
{1,0,{pysm::l,pyym::ong}},//巃 long
{1,0,{pysm::l,pyym::ong}},//巄 long
{1,0,{pysm::d,pyym::ian}},//巅 dian
{3,195,{pysm::nop,pyym::nop}},//巆 rong
{1,0,{pysm::x,pyym::i}},//巇 xi
{1,0,{pysm::j,pyym::u}},//巈 ju
{1,0,{pysm::ch,pyym::an}},//巉 chan
{1,0,{pysm::y,pyym::ing}},//巊 ying
{2,791,{pysm::nop,pyym::nop}},//巋 kui
{1,0,{pysm::y,pyym::an}},//巌 yan
{1,0,{pysm::w,pyym::ei}},//巍 wei
{1,0,{pysm::n,pyym::ao}},//巎 nao
{1,0,{pysm::q,pyym::uan}},//巏 quan
{1,0,{pysm::ch,pyym::ao}},//巐 chao
{1,0,{pysm::c,pyym::uan}},//巑 cuan
{1,0,{pysm::l,pyym::uan}},//巒 luan
{1,0,{pysm::d,pyym::ian}},//巓 dian
{1,0,{pysm::d,pyym::ian}},//巔 dian
{1,0,{pysm::n,pyym::ie}},//巕 nie
{1,0,{pysm::y,pyym::an}},//巖 yan
{1,0,{pysm::y,pyym::an}},//巗 yan
{1,0,{pysm::y,pyym::an}},//巘 yan
{2,792,{pysm::nop,pyym::nop}},//巙 kui
{1,0,{pysm::y,pyym::an}},//巚 yan
{2,793,{pysm::nop,pyym::nop}},//巛 chuan
{2,794,{pysm::nop,pyym::nop}},//巜 kuai
{1,0,{pysm::ch,pyym::uan}},//川 chuan
{1,0,{pysm::zh,pyym::ou}},//州 zhou
{1,0,{pysm::h,pyym::uang}},//巟 huang
{2,795,{pysm::nop,pyym::nop}},//巠 jing
{3,196,{pysm::nop,pyym::nop}},//巡 xun
{1,0,{pysm::ch,pyym::ao}},//巢 chao
{1,0,{pysm::ch,pyym::ao}},//巣 chao
{1,0,{pysm::l,pyym::ie}},//巤 lie
{1,0,{pysm::g,pyym::ong}},//工 gong
{1,0,{pysm::z,pyym::uo}},//左 zuo
{1,0,{pysm::q,pyym::iao}},//巧 qiao
{2,796,{pysm::nop,pyym::nop}},//巨 ju
{1,0,{pysm::g,pyym::ong}},//巩 gong
{1,0,{pysm::j,pyym::u}},//巪 ju
{1,0,{pysm::w,pyym::u}},//巫 wu
{1,0,{pysm::p,pyym::u}},//巬 pu
{1,0,{pysm::p,pyym::u}},//巭 pu
{5,15,{pysm::nop,pyym::nop}},//差 cha
{1,0,{pysm::q,pyym::iu}},//巯 qiu
{1,0,{pysm::q,pyym::iu}},//巰 qiu
{2,797,{pysm::nop,pyym::nop}},//己 ji
{2,798,{pysm::nop,pyym::nop}},//已 yi
{2,799,{pysm::nop,pyym::nop}},//巳 si
{1,0,{pysm::b,pyym::a}},//巴 ba
{1,0,{pysm::zh,pyym::i}},//巵 zhi
{1,0,{pysm::zh,pyym::ao}},//巶 zhao
{2,800,{pysm::nop,pyym::nop}},//巷 xiang
{1,0,{pysm::y,pyym::i}},//巸 yi
{1,0,{pysm::j,pyym::in}},//巹 jin
{1,0,{pysm::x,pyym::un}},//巺 xun
{1,0,{pysm::j,pyym::uan}},//巻 juan
{1,0,{pysm::b,pyym::a}},//巼 ba
{2,801,{pysm::nop,pyym::nop}},//巽 xun
{1,0,{pysm::j,pyym::in}},//巾 jin
{2,802,{pysm::nop,pyym::nop}},//巿 fu
{1,0,{pysm::z,pyym::a}},//帀 za
{2,803,{pysm::nop,pyym::nop}},//币 bi
{2,804,{pysm::nop,pyym::nop}},//市 shi
{1,0,{pysm::b,pyym::u}},//布 bu
{1,0,{pysm::d,pyym::ing}},//帄 ding
{1,0,{pysm::sh,pyym::uai}},//帅 shuai
{1,0,{pysm::f,pyym::an}},//帆 fan
{1,0,{pysm::n,pyym::ie}},//帇 nie
{1,0,{pysm::sh,pyym::i}},//师 shi
{1,0,{pysm::f,pyym::en}},//帉 fen
{1,0,{pysm::p,pyym::a}},//帊 pa
{1,0,{pysm::zh,pyym::i}},//帋 zhi
{1,0,{pysm::x,pyym::i}},//希 xi
{1,0,{pysm::h,pyym::u}},//帍 hu
{1,0,{pysm::d,pyym::an}},//帎 dan
{1,0,{pysm::w,pyym::ei}},//帏 wei
{1,0,{pysm::zh,pyym::ang}},//帐 zhang
{2,805,{pysm::nop,pyym::nop}},//帑 tang
{1,0,{pysm::d,pyym::ai}},//帒 dai
{2,806,{pysm::nop,pyym::nop}},//帓 mo
{2,807,{pysm::nop,pyym::nop}},//帔 pei
{2,808,{pysm::nop,pyym::nop}},//帕 pa
{1,0,{pysm::t,pyym::ie}},//帖 tie
{2,809,{pysm::nop,pyym::nop}},//帗 bo
{2,810,{pysm::nop,pyym::nop}},//帘 lian
{1,0,{pysm::zh,pyym::i}},//帙 zhi
{1,0,{pysm::zh,pyym::ou}},//帚 zhou
{1,0,{pysm::b,pyym::o}},//帛 bo
{1,0,{pysm::zh,pyym::i}},//帜 zhi
{1,0,{pysm::d,pyym::i}},//帝 di
{1,0,{pysm::m,pyym::o}},//帞 mo
{1,0,{pysm::y,pyym::i}},//帟 yi
{1,0,{pysm::y,pyym::i}},//帠 yi
{1,0,{pysm::p,pyym::ing}},//帡 ping
{1,0,{pysm::q,pyym::ia}},//帢 qia
{1,0,{pysm::j,pyym::uan}},//帣 juan
{1,0,{pysm::r,pyym::u}},//帤 ru
{1,0,{pysm::sh,pyym::uai}},//帥 shuai
{1,0,{pysm::d,pyym::ai}},//带 dai
{2,811,{pysm::nop,pyym::nop}},//帧 zhen
{1,0,{pysm::sh,pyym::ui}},//帨 shui
{1,0,{pysm::q,pyym::iao}},//帩 qiao
{1,0,{pysm::zh,pyym::en}},//帪 zhen
{1,0,{pysm::sh,pyym::i}},//師 shi
{1,0,{pysm::q,pyym::un}},//帬 qun
{1,0,{pysm::x,pyym::i}},//席 xi
{1,0,{pysm::b,pyym::ang}},//帮 bang
{1,0,{pysm::d,pyym::ai}},//帯 dai
{1,0,{pysm::g,pyym::ui}},//帰 gui
{2,812,{pysm::nop,pyym::nop}},//帱 chou
{1,0,{pysm::p,pyym::ing}},//帲 ping
{1,0,{pysm::zh,pyym::ang}},//帳 zhang
{2,813,{pysm::nop,pyym::nop}},//帴 san
{1,0,{pysm::w,pyym::an}},//帵 wan
{1,0,{pysm::d,pyym::ai}},//帶 dai
{1,0,{pysm::w,pyym::ei}},//帷 wei
{1,0,{pysm::ch,pyym::ang}},//常 chang
{2,814,{pysm::nop,pyym::nop}},//帹 sha
{2,815,{pysm::nop,pyym::nop}},//帺 qi
{1,0,{pysm::z,pyym::e}},//帻 ze
{1,0,{pysm::g,pyym::uo}},//帼 guo
{1,0,{pysm::m,pyym::ao}},//帽 mao
{1,0,{pysm::d,pyym::u}},//帾 du
{1,0,{pysm::h,pyym::ou}},//帿 hou
{1,0,{pysm::zh,pyym::eng}},//幀 zheng
{1,0,{pysm::x,pyym::u}},//幁 xu
{1,0,{pysm::m,pyym::i}},//幂 mi
{1,0,{pysm::w,pyym::ei}},//幃 wei
{1,0,{pysm::w,pyym::o}},//幄 wo
{2,816,{pysm::nop,pyym::nop}},//幅 fu
{2,817,{pysm::nop,pyym::nop}},//幆 yi
{1,0,{pysm::b,pyym::ang}},//幇 bang
{1,0,{pysm::p,pyym::ing}},//幈 ping
{1,0,{pysm::d,pyym::ie}},//幉 die
{1,0,{pysm::g,pyym::ong}},//幊 gong
{1,0,{pysm::p,pyym::an}},//幋 pan
{1,0,{pysm::h,pyym::uang}},//幌 huang
{1,0,{pysm::t,pyym::ao}},//幍 tao
{1,0,{pysm::m,pyym::i}},//幎 mi
{1,0,{pysm::j,pyym::ia}},//幏 jia
{1,0,{pysm::t,pyym::eng}},//幐 teng
{1,0,{pysm::h,pyym::ui}},//幑 hui
{1,0,{pysm::zh,pyym::ong}},//幒 zhong
{3,197,{pysm::nop,pyym::nop}},//幓 shan
{1,0,{pysm::m,pyym::an}},//幔 man
{2,818,{pysm::nop,pyym::nop}},//幕 mu
{1,0,{pysm::b,pyym::iao}},//幖 biao
{1,0,{pysm::g,pyym::uo}},//幗 guo
{2,819,{pysm::nop,pyym::nop}},//幘 ze
{1,0,{pysm::m,pyym::u}},//幙 mu
{1,0,{pysm::b,pyym::ang}},//幚 bang
{1,0,{pysm::zh,pyym::ang}},//幛 zhang
{1,0,{pysm::j,pyym::ing}},//幜 jing
{1,0,{pysm::ch,pyym::an}},//幝 chan
{1,0,{pysm::f,pyym::u}},//幞 fu
{1,0,{pysm::zh,pyym::i}},//幟 zhi
{2,820,{pysm::nop,pyym::nop}},//幠 hu
{1,0,{pysm::f,pyym::an}},//幡 fan
{2,821,{pysm::nop,pyym::nop}},//幢 chuang
{1,0,{pysm::b,pyym::i}},//幣 bi
{1,0,{pysm::b,pyym::i}},//幤 bi
{1,0,{pysm::zh,pyym::ang}},//幥 zhang
{1,0,{pysm::m,pyym::i}},//幦 mi
{1,0,{pysm::q,pyym::iao}},//幧 qiao
{1,0,{pysm::ch,pyym::an}},//幨 chan
{1,0,{pysm::f,pyym::en}},//幩 fen
{1,0,{pysm::m,pyym::eng}},//幪 meng
{1,0,{pysm::b,pyym::ang}},//幫 bang
{2,822,{pysm::nop,pyym::nop}},//幬 chou
{1,0,{pysm::m,pyym::ie}},//幭 mie
{1,0,{pysm::ch,pyym::u}},//幮 chu
{1,0,{pysm::j,pyym::ie}},//幯 jie
{1,0,{pysm::x,pyym::ian}},//幰 xian
{1,0,{pysm::l,pyym::an}},//幱 lan
{2,823,{pysm::nop,pyym::nop}},//干 gan
{4,45,{pysm::nop,pyym::nop}},//平 ping
{2,824,{pysm::nop,pyym::nop}},//年 nian
{2,825,{pysm::nop,pyym::nop}},//幵 jian
{1,0,{pysm::b,pyym::ing}},//并 bing
{1,0,{pysm::b,pyym::ing}},//幷 bing
{2,826,{pysm::nop,pyym::nop}},//幸 xing
{3,198,{pysm::nop,pyym::nop}},//幹 gan
{2,827,{pysm::nop,pyym::nop}},//幺 yao
{1,0,{pysm::h,pyym::uan}},//幻 huan
{2,828,{pysm::nop,pyym::nop}},//幼 you
{1,0,{pysm::y,pyym::ou}},//幽 you
{2,829,{pysm::nop,pyym::nop}},//幾 ji
{3,199,{pysm::nop,pyym::nop}},//广 guang
{1,0,{pysm::p,pyym::i}},//庀 pi
{1,0,{pysm::t,pyym::ing}},//庁 ting
{1,0,{pysm::z,pyym::e}},//庂 ze
{1,0,{pysm::g,pyym::uang}},//広 guang
{2,830,{pysm::nop,pyym::nop}},//庄 zhuang
{1,0,{pysm::m,pyym::o}},//庅 mo
{1,0,{pysm::q,pyym::ing}},//庆 qing
{2,831,{pysm::nop,pyym::nop}},//庇 bi
{1,0,{pysm::q,pyym::in}},//庈 qin
{2,832,{pysm::nop,pyym::nop}},//庉 dun
{1,0,{pysm::ch,pyym::uang}},//床 chuang
{1,0,{pysm::g,pyym::ui}},//庋 gui
{1,0,{pysm::y,pyym::a}},//庌 ya
{3,200,{pysm::nop,pyym::nop}},//庍 bai
{1,0,{pysm::j,pyym::ie}},//庎 jie
{1,0,{pysm::x,pyym::u}},//序 xu
{1,0,{pysm::l,pyym::u}},//庐 lu
{1,0,{pysm::w,pyym::u}},//庑 wu
{1,0,{pysm::zh,pyym::uang}},//庒 zhuang
{1,0,{pysm::k,pyym::u}},//库 ku
{1,0,{pysm::y,pyym::ing}},//应 ying
{2,833,{pysm::nop,pyym::nop}},//底 di
{1,0,{pysm::p,pyym::ao}},//庖 pao
{1,0,{pysm::d,pyym::ian}},//店 dian
{1,0,{pysm::y,pyym::a}},//庘 ya
{1,0,{pysm::m,pyym::iao}},//庙 miao
{1,0,{pysm::g,pyym::eng}},//庚 geng
{1,0,{pysm::c,pyym::i}},//庛 ci
{1,0,{pysm::f,pyym::u}},//府 fu
{1,0,{pysm::t,pyym::ong}},//庝 tong
{1,0,{pysm::p,pyym::ang}},//庞 pang
{1,0,{pysm::f,pyym::ei}},//废 fei
{1,0,{pysm::x,pyym::iang}},//庠 xiang
{1,0,{pysm::y,pyym::i}},//庡 yi
{1,0,{pysm::zh,pyym::i}},//庢 zhi
{1,0,{pysm::t,pyym::iao}},//庣 tiao
{1,0,{pysm::zh,pyym::i}},//庤 zhi
{1,0,{pysm::x,pyym::iu}},//庥 xiu
{3,201,{pysm::nop,pyym::nop}},//度 du
{1,0,{pysm::z,pyym::uo}},//座 zuo
{1,0,{pysm::x,pyym::iao}},//庨 xiao
{1,0,{pysm::t,pyym::u}},//庩 tu
{1,0,{pysm::g,pyym::ui}},//庪 gui
{1,0,{pysm::k,pyym::u}},//庫 ku
{2,834,{pysm::nop,pyym::nop}},//庬 mang
{1,0,{pysm::t,pyym::ing}},//庭 ting
{1,0,{pysm::y,pyym::ou}},//庮 you
{1,0,{pysm::b,pyym::u}},//庯 bu
{1,0,{pysm::b,pyym::ing}},//庰 bing
{1,0,{pysm::ch,pyym::eng}},//庱 cheng
{1,0,{pysm::l,pyym::ai}},//庲 lai
{2,835,{pysm::nop,pyym::nop}},//庳 bi
{1,0,{pysm::j,pyym::i}},//庴 ji
{3,202,{pysm::nop,pyym::nop}},//庵 an
{3,203,{pysm::nop,pyym::nop}},//庶 shu
{1,0,{pysm::k,pyym::ang}},//康 kang
{1,0,{pysm::y,pyym::ong}},//庸 yong
{1,0,{pysm::t,pyym::uo}},//庹 tuo
{1,0,{pysm::s,pyym::ong}},//庺 song
{1,0,{pysm::sh,pyym::u}},//庻 shu
{1,0,{pysm::q,pyym::ing}},//庼 qing
{1,0,{pysm::y,pyym::u}},//庽 yu
{1,0,{pysm::y,pyym::u}},//庾 yu
{1,0,{pysm::m,pyym::iao}},//庿 miao
{1,0,{pysm::s,pyym::ou}},//廀 sou
{4,46,{pysm::nop,pyym::nop}},//廁 ce
{1,0,{pysm::x,pyym::iang}},//廂 xiang
{1,0,{pysm::f,pyym::ei}},//廃 fei
{1,0,{pysm::j,pyym::iu}},//廄 jiu
{1,0,{pysm::nop,pyym::e}},//廅 e
{3,204,{pysm::nop,pyym::nop}},//廆 gui
{1,0,{pysm::l,pyym::iu}},//廇 liu
{2,836,{pysm::nop,pyym::nop}},//廈 sha
{1,0,{pysm::l,pyym::ian}},//廉 lian
{1,0,{pysm::l,pyym::ang}},//廊 lang
{1,0,{pysm::s,pyym::ou}},//廋 sou
{1,0,{pysm::zh,pyym::i}},//廌 zhi
{1,0,{pysm::b,pyym::u}},//廍 bu
{1,0,{pysm::q,pyym::ing}},//廎 qing
{1,0,{pysm::j,pyym::iu}},//廏 jiu
{1,0,{pysm::j,pyym::iu}},//廐 jiu
{2,837,{pysm::nop,pyym::nop}},//廑 jin
{1,0,{pysm::nop,pyym::ao}},//廒 ao
{1,0,{pysm::k,pyym::uo}},//廓 kuo
{1,0,{pysm::l,pyym::ou}},//廔 lou
{1,0,{pysm::y,pyym::in}},//廕 yin
{1,0,{pysm::l,pyym::iao}},//廖 liao
{1,0,{pysm::d,pyym::ai}},//廗 dai
{1,0,{pysm::l,pyym::u}},//廘 lu
{1,0,{pysm::y,pyym::i}},//廙 yi
{1,0,{pysm::ch,pyym::u}},//廚 chu
{1,0,{pysm::ch,pyym::an}},//廛 chan
{1,0,{pysm::t,pyym::u}},//廜 tu
{1,0,{pysm::s,pyym::i}},//廝 si
{2,838,{pysm::nop,pyym::nop}},//廞 xin
{1,0,{pysm::m,pyym::iao}},//廟 miao
{1,0,{pysm::ch,pyym::ang}},//廠 chang
{1,0,{pysm::w,pyym::u}},//廡 wu
{1,0,{pysm::f,pyym::ei}},//廢 fei
{2,839,{pysm::nop,pyym::nop}},//廣 guang
{1,0,{pysm::k,pyym::u}},//廤 ku
{1,0,{pysm::k,pyym::uai}},//廥 kuai
{1,0,{pysm::b,pyym::i}},//廦 bi
{2,840,{pysm::nop,pyym::nop}},//廧 qiang
{1,0,{pysm::x,pyym::ie}},//廨 xie
{2,841,{pysm::nop,pyym::nop}},//廩 lin
{1,0,{pysm::l,pyym::in}},//廪 lin
{1,0,{pysm::l,pyym::iao}},//廫 liao
{2,842,{pysm::nop,pyym::nop}},//廬 lu
{1,0,{pysm::j,pyym::i}},//廭 ji
{1,0,{pysm::y,pyym::ing}},//廮 ying
{1,0,{pysm::x,pyym::ian}},//廯 xian
{1,0,{pysm::t,pyym::ing}},//廰 ting
{1,0,{pysm::y,pyym::ong}},//廱 yong
{1,0,{pysm::l,pyym::i}},//廲 li
{1,0,{pysm::t,pyym::ing}},//廳 ting
{1,0,{pysm::y,pyym::in}},//廴 yin
{1,0,{pysm::x,pyym::un}},//廵 xun
{1,0,{pysm::y,pyym::an}},//延 yan
{1,0,{pysm::t,pyym::ing}},//廷 ting
{1,0,{pysm::d,pyym::i}},//廸 di
{2,843,{pysm::nop,pyym::nop}},//廹 pai
{1,0,{pysm::j,pyym::ian}},//建 jian
{1,0,{pysm::h,pyym::ui}},//廻 hui
{1,0,{pysm::n,pyym::ai}},//廼 nai
{1,0,{pysm::h,pyym::ui}},//廽 hui
{1,0,{pysm::g,pyym::ong}},//廾 gong
{1,0,{pysm::n,pyym::ian}},//廿 nian
{1,0,{pysm::k,pyym::ai}},//开 kai
{2,844,{pysm::nop,pyym::nop}},//弁 bian
{1,0,{pysm::y,pyym::i}},//异 yi
{1,0,{pysm::q,pyym::i}},//弃 qi
{2,845,{pysm::nop,pyym::nop}},//弄 nong
{1,0,{pysm::f,pyym::en}},//弅 fen
{2,846,{pysm::nop,pyym::nop}},//弆 ju
{2,847,{pysm::nop,pyym::nop}},//弇 yan
{1,0,{pysm::y,pyym::i}},//弈 yi
{1,0,{pysm::z,pyym::ang}},//弉 zang
{1,0,{pysm::b,pyym::i}},//弊 bi
{1,0,{pysm::y,pyym::i}},//弋 yi
{1,0,{pysm::y,pyym::i}},//弌 yi
{1,0,{pysm::nop,pyym::er}},//弍 er
{1,0,{pysm::s,pyym::an}},//弎 san
{2,848,{pysm::nop,pyym::nop}},//式 shi
{1,0,{pysm::nop,pyym::er}},//弐 er
{1,0,{pysm::sh,pyym::i}},//弑 shi
{1,0,{pysm::sh,pyym::i}},//弒 shi
{1,0,{pysm::g,pyym::ong}},//弓 gong
{2,849,{pysm::nop,pyym::nop}},//弔 diao
{1,0,{pysm::y,pyym::in}},//引 yin
{1,0,{pysm::h,pyym::u}},//弖 hu
{1,0,{pysm::f,pyym::u}},//弗 fu
{1,0,{pysm::h,pyym::ong}},//弘 hong
{1,0,{pysm::w,pyym::u}},//弙 wu
{1,0,{pysm::t,pyym::ui}},//弚 tui
{1,0,{pysm::ch,pyym::i}},//弛 chi
{1,0,{pysm::j,pyym::iang}},//弜 jiang
{1,0,{pysm::b,pyym::a}},//弝 ba
{1,0,{pysm::sh,pyym::en}},//弞 shen
{3,205,{pysm::nop,pyym::nop}},//弟 di
{1,0,{pysm::zh,pyym::ang}},//张 zhang
{2,850,{pysm::nop,pyym::nop}},//弡 jue
{1,0,{pysm::t,pyym::ao}},//弢 tao
{1,0,{pysm::f,pyym::u}},//弣 fu
{1,0,{pysm::d,pyym::i}},//弤 di
{1,0,{pysm::m,pyym::i}},//弥 mi
{1,0,{pysm::x,pyym::ian}},//弦 xian
{1,0,{pysm::h,pyym::u}},//弧 hu
{1,0,{pysm::ch,pyym::ao}},//弨 chao
{1,0,{pysm::n,pyym::u}},//弩 nu
{1,0,{pysm::j,pyym::ing}},//弪 jing
{1,0,{pysm::zh,pyym::en}},//弫 zhen
{1,0,{pysm::y,pyym::i}},//弬 yi
{1,0,{pysm::m,pyym::i}},//弭 mi
{2,851,{pysm::nop,pyym::nop}},//弮 quan
{1,0,{pysm::w,pyym::an}},//弯 wan
{1,0,{pysm::sh,pyym::ao}},//弰 shao
{1,0,{pysm::r,pyym::uo}},//弱 ruo
{2,852,{pysm::nop,pyym::nop}},//弲 xuan
{1,0,{pysm::j,pyym::ing}},//弳 jing
{1,0,{pysm::d,pyym::iao}},//弴 diao
{1,0,{pysm::zh,pyym::ang}},//張 zhang
{1,0,{pysm::j,pyym::iang}},//弶 jiang
{2,853,{pysm::nop,pyym::nop}},//強 qiang
{1,0,{pysm::p,pyym::eng}},//弸 peng
{2,854,{pysm::nop,pyym::nop}},//弹 dan
{2,855,{pysm::nop,pyym::nop}},//强 qiang
{1,0,{pysm::b,pyym::i}},//弻 bi
{1,0,{pysm::b,pyym::i}},//弼 bi
{1,0,{pysm::sh,pyym::e}},//弽 she
{1,0,{pysm::d,pyym::an}},//弾 dan
{1,0,{pysm::j,pyym::ian}},//弿 jian
{2,856,{pysm::nop,pyym::nop}},//彀 gou
{1,0,{pysm::g,pyym::e}},//彁 ge
{1,0,{pysm::f,pyym::a}},//彂 fa
{1,0,{pysm::b,pyym::i}},//彃 bi
{1,0,{pysm::k,pyym::ou}},//彄 kou
{1,0,{pysm::j,pyym::ian}},//彅 jian
{1,0,{pysm::b,pyym::ie}},//彆 bie
{1,0,{pysm::x,pyym::iao}},//彇 xiao
{2,857,{pysm::nop,pyym::nop}},//彈 dan
{1,0,{pysm::g,pyym::uo}},//彉 guo
{2,858,{pysm::nop,pyym::nop}},//彊 jiang
{1,0,{pysm::h,pyym::ong}},//彋 hong
{2,859,{pysm::nop,pyym::nop}},//彌 mi
{1,0,{pysm::g,pyym::uo}},//彍 guo
{1,0,{pysm::w,pyym::an}},//彎 wan
{1,0,{pysm::j,pyym::ue}},//彏 jue
{1,0,{pysm::j,pyym::i}},//彐 ji
{1,0,{pysm::j,pyym::i}},//彑 ji
{1,0,{pysm::g,pyym::ui}},//归 gui
{1,0,{pysm::d,pyym::ang}},//当 dang
{1,0,{pysm::l,pyym::u}},//彔 lu
{1,0,{pysm::l,pyym::u}},//录 lu
{2,860,{pysm::nop,pyym::nop}},//彖 tuan
{2,861,{pysm::nop,pyym::nop}},//彗 hui
{1,0,{pysm::zh,pyym::i}},//彘 zhi
{1,0,{pysm::h,pyym::ui}},//彙 hui
{1,0,{pysm::h,pyym::ui}},//彚 hui
{1,0,{pysm::y,pyym::i}},//彛 yi
{1,0,{pysm::y,pyym::i}},//彜 yi
{1,0,{pysm::y,pyym::i}},//彝 yi
{1,0,{pysm::y,pyym::i}},//彞 yi
{1,0,{pysm::y,pyym::ue}},//彟 yue
{1,0,{pysm::y,pyym::ue}},//彠 yue
{2,862,{pysm::nop,pyym::nop}},//彡 shan
{1,0,{pysm::x,pyym::ing}},//形 xing
{1,0,{pysm::w,pyym::en}},//彣 wen
{1,0,{pysm::t,pyym::ong}},//彤 tong
{1,0,{pysm::y,pyym::an}},//彥 yan
{2,863,{pysm::nop,pyym::nop}},//彦 yan
{1,0,{pysm::y,pyym::u}},//彧 yu
{1,0,{pysm::ch,pyym::i}},//彨 chi
{1,0,{pysm::c,pyym::ai}},//彩 cai
{1,0,{pysm::b,pyym::iao}},//彪 biao
{1,0,{pysm::d,pyym::iao}},//彫 diao
{2,864,{pysm::nop,pyym::nop}},//彬 bin
{3,206,{pysm::nop,pyym::nop}},//彭 peng
{1,0,{pysm::y,pyym::ong}},//彮 yong
{2,865,{pysm::nop,pyym::nop}},//彯 piao
{1,0,{pysm::zh,pyym::ang}},//彰 zhang
{1,0,{pysm::y,pyym::ing}},//影 ying
{1,0,{pysm::ch,pyym::i}},//彲 chi
{2,866,{pysm::nop,pyym::nop}},//彳 chi
{2,867,{pysm::nop,pyym::nop}},//彴 zhuo
{2,868,{pysm::nop,pyym::nop}},//彵 tuo
{1,0,{pysm::j,pyym::i}},//彶 ji
{2,869,{pysm::nop,pyym::nop}},//彷 pang
{1,0,{pysm::zh,pyym::ong}},//彸 zhong
{1,0,{pysm::y,pyym::i}},//役 yi
{1,0,{pysm::w,pyym::ang}},//彺 wang
{1,0,{pysm::ch,pyym::e}},//彻 che
{1,0,{pysm::b,pyym::i}},//彼 bi
{1,0,{pysm::d,pyym::i}},//彽 di
{1,0,{pysm::l,pyym::ing}},//彾 ling
{1,0,{pysm::f,pyym::u}},//彿 fu
{1,0,{pysm::w,pyym::ang}},//往 wang
{1,0,{pysm::zh,pyym::eng}},//征 zheng
{1,0,{pysm::c,pyym::u}},//徂 cu
{1,0,{pysm::w,pyym::ang}},//徃 wang
{1,0,{pysm::j,pyym::ing}},//径 jing
{1,0,{pysm::d,pyym::ai}},//待 dai
{1,0,{pysm::x,pyym::i}},//徆 xi
{1,0,{pysm::x,pyym::un}},//徇 xun
{1,0,{pysm::h,pyym::en}},//很 hen
{1,0,{pysm::y,pyym::ang}},//徉 yang
{2,870,{pysm::nop,pyym::nop}},//徊 huai
{1,0,{pysm::l,pyym::v}},//律 lü
{1,0,{pysm::h,pyym::ou}},//後 hou
{2,871,{pysm::nop,pyym::nop}},//徍 wang
{2,872,{pysm::nop,pyym::nop}},//徎 cheng
{1,0,{pysm::zh,pyym::i}},//徏 zhi
{1,0,{pysm::x,pyym::u}},//徐 xu
{1,0,{pysm::j,pyym::ing}},//徑 jing
{1,0,{pysm::t,pyym::u}},//徒 tu
{1,0,{pysm::c,pyym::ong}},//従 cong
{1,0,{pysm::zh,pyym::i}},//徔 zhi
{1,0,{pysm::l,pyym::ai}},//徕 lai
{1,0,{pysm::c,pyym::ong}},//徖 cong
{2,873,{pysm::nop,pyym::nop}},//得 de
{1,0,{pysm::p,pyym::ai}},//徘 pai
{2,874,{pysm::nop,pyym::nop}},//徙 xi
{1,0,{pysm::d,pyym::ong}},//徚 dong
{1,0,{pysm::j,pyym::i}},//徛 ji
{1,0,{pysm::ch,pyym::ang}},//徜 chang
{1,0,{pysm::zh,pyym::i}},//徝 zhi
{2,875,{pysm::nop,pyym::nop}},//從 cong
{1,0,{pysm::zh,pyym::ou}},//徟 zhou
{1,0,{pysm::l,pyym::ai}},//徠 lai
{2,876,{pysm::nop,pyym::nop}},//御 yu
{1,0,{pysm::x,pyym::ie}},//徢 xie
{1,0,{pysm::j,pyym::ie}},//徣 jie
{1,0,{pysm::j,pyym::ian}},//徤 jian
{2,877,{pysm::nop,pyym::nop}},//徥 shi
{2,878,{pysm::nop,pyym::nop}},//徦 jia
{2,879,{pysm::nop,pyym::nop}},//徧 bian
{1,0,{pysm::h,pyym::uang}},//徨 huang
{1,0,{pysm::f,pyym::u}},//復 fu
{1,0,{pysm::x,pyym::un}},//循 xun
{1,0,{pysm::w,pyym::ei}},//徫 wei
{2,880,{pysm::nop,pyym::nop}},//徬 pang
{1,0,{pysm::y,pyym::ao}},//徭 yao
{1,0,{pysm::w,pyym::ei}},//微 wei
{1,0,{pysm::x,pyym::i}},//徯 xi
{1,0,{pysm::zh,pyym::eng}},//徰 zheng
{1,0,{pysm::p,pyym::iao}},//徱 piao
{2,881,{pysm::nop,pyym::nop}},//徲 ti
{1,0,{pysm::d,pyym::e}},//徳 de
{1,0,{pysm::zh,pyym::eng}},//徴 zheng
{3,207,{pysm::nop,pyym::nop}},//徵 zheng
{1,0,{pysm::b,pyym::ie}},//徶 bie
{1,0,{pysm::d,pyym::e}},//德 de
{2,882,{pysm::nop,pyym::nop}},//徸 chong
{1,0,{pysm::ch,pyym::e}},//徹 che
{1,0,{pysm::j,pyym::iao}},//徺 jiao
{1,0,{pysm::h,pyym::ui}},//徻 hui
{2,883,{pysm::nop,pyym::nop}},//徼 jiao
{1,0,{pysm::h,pyym::ui}},//徽 hui
{1,0,{pysm::m,pyym::ei}},//徾 mei
{1,0,{pysm::l,pyym::ong}},//徿 long
{2,884,{pysm::nop,pyym::nop}},//忀 xiang
{1,0,{pysm::b,pyym::ao}},//忁 bao
{2,885,{pysm::nop,pyym::nop}},//忂 qu
{1,0,{pysm::x,pyym::in}},//心 xin
{1,0,{pysm::x,pyym::in}},//忄 xin
{1,0,{pysm::b,pyym::i}},//必 bi
{1,0,{pysm::y,pyym::i}},//忆 yi
{1,0,{pysm::l,pyym::e}},//忇 le
{1,0,{pysm::r,pyym::en}},//忈 ren
{1,0,{pysm::d,pyym::ao}},//忉 dao
{2,886,{pysm::nop,pyym::nop}},//忊 ding
{1,0,{pysm::g,pyym::ai}},//忋 gai
{1,0,{pysm::j,pyym::i}},//忌 ji
{1,0,{pysm::r,pyym::en}},//忍 ren
{1,0,{pysm::r,pyym::en}},//忎 ren
{2,887,{pysm::nop,pyym::nop}},//忏 chan
{2,888,{pysm::nop,pyym::nop}},//忐 tan
{2,889,{pysm::nop,pyym::nop}},//忑 te
{3,208,{pysm::nop,pyym::nop}},//忒 te
{2,890,{pysm::nop,pyym::nop}},//忓 gan
{2,891,{pysm::nop,pyym::nop}},//忔 qi
{2,892,{pysm::nop,pyym::nop}},//忕 shi
{1,0,{pysm::c,pyym::un}},//忖 cun
{1,0,{pysm::zh,pyym::i}},//志 zhi
{1,0,{pysm::w,pyym::ang}},//忘 wang
{1,0,{pysm::m,pyym::ang}},//忙 mang
{2,893,{pysm::nop,pyym::nop}},//忚 xi
{1,0,{pysm::f,pyym::an}},//忛 fan
{1,0,{pysm::y,pyym::ing}},//応 ying
{1,0,{pysm::t,pyym::ian}},//忝 tian
{2,894,{pysm::nop,pyym::nop}},//忞 min
{1,0,{pysm::w,pyym::en}},//忟 wen
{1,0,{pysm::zh,pyym::ong}},//忠 zhong
{1,0,{pysm::ch,pyym::ong}},//忡 chong
{1,0,{pysm::w,pyym::u}},//忢 wu
{1,0,{pysm::j,pyym::i}},//忣 ji
{1,0,{pysm::w,pyym::u}},//忤 wu
{1,0,{pysm::x,pyym::i}},//忥 xi
{1,0,{pysm::j,pyym::ia}},//忦 jia
{1,0,{pysm::y,pyym::ou}},//忧 you
{1,0,{pysm::w,pyym::an}},//忨 wan
{1,0,{pysm::c,pyym::ong}},//忩 cong
{2,895,{pysm::nop,pyym::nop}},//忪 song
{1,0,{pysm::k,pyym::uai}},//快 kuai
{2,896,{pysm::nop,pyym::nop}},//忬 yu
{1,0,{pysm::b,pyym::ian}},//忭 bian
{2,897,{pysm::nop,pyym::nop}},//忮 zhi
{2,898,{pysm::nop,pyym::nop}},//忯 qi
{1,0,{pysm::c,pyym::ui}},//忰 cui
{2,899,{pysm::nop,pyym::nop}},//忱 chen
{1,0,{pysm::t,pyym::ai}},//忲 tai
{3,209,{pysm::nop,pyym::nop}},//忳 tun
{2,900,{pysm::nop,pyym::nop}},//忴 qian
{1,0,{pysm::n,pyym::ian}},//念 nian
{1,0,{pysm::h,pyym::un}},//忶 hun
{1,0,{pysm::x,pyym::iong}},//忷 xiong
{1,0,{pysm::n,pyym::iu}},//忸 niu
{2,901,{pysm::nop,pyym::nop}},//忹 kuang
{1,0,{pysm::x,pyym::ian}},//忺 xian
{1,0,{pysm::x,pyym::in}},//忻 xin
{2,902,{pysm::nop,pyym::nop}},//忼 kang
{1,0,{pysm::h,pyym::u}},//忽 hu
{2,903,{pysm::nop,pyym::nop}},//忾 kai
{1,0,{pysm::f,pyym::en}},//忿 fen
{2,904,{pysm::nop,pyym::nop}},//怀 huai
{1,0,{pysm::t,pyym::ai}},//态 tai
{1,0,{pysm::s,pyym::ong}},//怂 song
{1,0,{pysm::w,pyym::u}},//怃 wu
{1,0,{pysm::nop,pyym::ou}},//怄 ou
{1,0,{pysm::ch,pyym::ang}},//怅 chang
{1,0,{pysm::ch,pyym::uang}},//怆 chuang
{1,0,{pysm::j,pyym::u}},//怇 ju
{1,0,{pysm::y,pyym::i}},//怈 yi
{1,0,{pysm::b,pyym::ao}},//怉 bao
{1,0,{pysm::ch,pyym::ao}},//怊 chao
{2,905,{pysm::nop,pyym::nop}},//怋 min
{1,0,{pysm::p,pyym::ei}},//怌 pei
{2,906,{pysm::nop,pyym::nop}},//怍 zuo
{1,0,{pysm::z,pyym::en}},//怎 zen
{1,0,{pysm::y,pyym::ang}},//怏 yang
{2,907,{pysm::nop,pyym::nop}},//怐 ju
{1,0,{pysm::b,pyym::an}},//怑 ban
{1,0,{pysm::n,pyym::u}},//怒 nu
{2,908,{pysm::nop,pyym::nop}},//怓 nao
{1,0,{pysm::zh,pyym::eng}},//怔 zheng
{2,909,{pysm::nop,pyym::nop}},//怕 pa
{1,0,{pysm::b,pyym::u}},//怖 bu
{2,910,{pysm::nop,pyym::nop}},//怗 tie
{2,911,{pysm::nop,pyym::nop}},//怘 hu
{2,912,{pysm::nop,pyym::nop}},//怙 hu
{4,47,{pysm::nop,pyym::nop}},//怚 ju
{2,913,{pysm::nop,pyym::nop}},//怛 da
{2,914,{pysm::nop,pyym::nop}},//怜 lian
{2,915,{pysm::nop,pyym::nop}},//思 si
{2,916,{pysm::nop,pyym::nop}},//怞 chou
{1,0,{pysm::d,pyym::i}},//怟 di
{2,917,{pysm::nop,pyym::nop}},//怠 dai
{1,0,{pysm::y,pyym::i}},//怡 yi
{3,210,{pysm::nop,pyym::nop}},//怢 tu
{1,0,{pysm::y,pyym::ou}},//怣 you
{1,0,{pysm::f,pyym::u}},//怤 fu
{1,0,{pysm::j,pyym::i}},//急 ji
{1,0,{pysm::p,pyym::eng}},//怦 peng
{1,0,{pysm::x,pyym::ing}},//性 xing
{2,918,{pysm::nop,pyym::nop}},//怨 yuan
{1,0,{pysm::n,pyym::i}},//怩 ni
{1,0,{pysm::g,pyym::uai}},//怪 guai
{3,211,{pysm::nop,pyym::nop}},//怫 fu
{1,0,{pysm::x,pyym::i}},//怬 xi
{1,0,{pysm::b,pyym::i}},//怭 bi
{2,919,{pysm::nop,pyym::nop}},//怮 you
{1,0,{pysm::q,pyym::ie}},//怯 qie
{1,0,{pysm::x,pyym::uan}},//怰 xuan
{1,0,{pysm::c,pyym::ong}},//怱 cong
{1,0,{pysm::b,pyym::ing}},//怲 bing
{1,0,{pysm::h,pyym::uang}},//怳 huang
{2,920,{pysm::nop,pyym::nop}},//怴 xu
{2,921,{pysm::nop,pyym::nop}},//怵 chu
{2,922,{pysm::nop,pyym::nop}},//怶 bi
{1,0,{pysm::sh,pyym::u}},//怷 shu
{1,0,{pysm::x,pyym::i}},//怸 xi
{1,0,{pysm::t,pyym::an}},//怹 tan
{1,0,{pysm::y,pyym::ong}},//怺 yong
{1,0,{pysm::z,pyym::ong}},//总 zong
{1,0,{pysm::d,pyym::ui}},//怼 dui
{1,0,{pysm::m,pyym::o}},//怽 mo
{1,0,{pysm::zh,pyym::i}},//怾 zhi
{1,0,{pysm::y,pyym::i}},//怿 yi
{1,0,{pysm::sh,pyym::i}},//恀 shi
{3,212,{pysm::nop,pyym::nop}},//恁 nen
{2,923,{pysm::nop,pyym::nop}},//恂 xun
{2,924,{pysm::nop,pyym::nop}},//恃 shi
{1,0,{pysm::x,pyym::i}},//恄 xi
{1,0,{pysm::l,pyym::ao}},//恅 lao
{2,925,{pysm::nop,pyym::nop}},//恆 heng
{1,0,{pysm::k,pyym::uang}},//恇 kuang
{1,0,{pysm::m,pyym::ou}},//恈 mou
{1,0,{pysm::zh,pyym::i}},//恉 zhi
{1,0,{pysm::x,pyym::ie}},//恊 xie
{1,0,{pysm::l,pyym::ian}},//恋 lian
{2,926,{pysm::nop,pyym::nop}},//恌 tiao
{2,927,{pysm::nop,pyym::nop}},//恍 huang
{1,0,{pysm::d,pyym::ie}},//恎 die
{1,0,{pysm::h,pyym::ao}},//恏 hao
{1,0,{pysm::k,pyym::ong}},//恐 kong
{2,928,{pysm::nop,pyym::nop}},//恑 gui
{1,0,{pysm::h,pyym::eng}},//恒 heng
{3,213,{pysm::nop,pyym::nop}},//恓 xi
{2,929,{pysm::nop,pyym::nop}},//恔 jiao
{1,0,{pysm::sh,pyym::u}},//恕 shu
{1,0,{pysm::s,pyym::i}},//恖 si
{2,930,{pysm::nop,pyym::nop}},//恗 hu
{1,0,{pysm::q,pyym::iu}},//恘 qiu
{1,0,{pysm::y,pyym::ang}},//恙 yang
{1,0,{pysm::h,pyym::ui}},//恚 hui
{1,0,{pysm::h,pyym::ui}},//恛 hui
{1,0,{pysm::ch,pyym::i}},//恜 chi
{2,931,{pysm::nop,pyym::nop}},//恝 jia
{1,0,{pysm::y,pyym::i}},//恞 yi
{1,0,{pysm::x,pyym::iong}},//恟 xiong
{1,0,{pysm::g,pyym::uai}},//恠 guai
{1,0,{pysm::l,pyym::in}},//恡 lin
{1,0,{pysm::h,pyym::ui}},//恢 hui
{1,0,{pysm::z,pyym::i}},//恣 zi
{1,0,{pysm::x,pyym::u}},//恤 xu
{1,0,{pysm::ch,pyym::i}},//恥 chi
{1,0,{pysm::sh,pyym::ang}},//恦 shang
{1,0,{pysm::n,pyym::v}},//恧 nü
{1,0,{pysm::h,pyym::en}},//恨 hen
{1,0,{pysm::nop,pyym::en}},//恩 en
{1,0,{pysm::k,pyym::e}},//恪 ke
{2,932,{pysm::nop,pyym::nop}},//恫 dong
{1,0,{pysm::t,pyym::ian}},//恬 tian
{1,0,{pysm::g,pyym::ong}},//恭 gong
{2,933,{pysm::nop,pyym::nop}},//恮 quan
{1,0,{pysm::x,pyym::i}},//息 xi
{1,0,{pysm::q,pyym::ia}},//恰 qia
{1,0,{pysm::y,pyym::ue}},//恱 yue
{1,0,{pysm::p,pyym::eng}},//恲 peng
{1,0,{pysm::k,pyym::en}},//恳 ken
{1,0,{pysm::d,pyym::e}},//恴 de
{1,0,{pysm::h,pyym::ui}},//恵 hui
{2,934,{pysm::nop,pyym::nop}},//恶 e
{1,0,{pysm::x,pyym::iao}},//恷 xiao
{1,0,{pysm::t,pyym::ong}},//恸 tong
{1,0,{pysm::y,pyym::an}},//恹 yan
{1,0,{pysm::k,pyym::ai}},//恺 kai
{1,0,{pysm::c,pyym::e}},//恻 ce
{1,0,{pysm::n,pyym::ao}},//恼 nao
{1,0,{pysm::y,pyym::un}},//恽 yun
{1,0,{pysm::m,pyym::ang}},//恾 mang
{2,935,{pysm::nop,pyym::nop}},//恿 yong
{1,0,{pysm::y,pyym::ong}},//悀 yong
{2,936,{pysm::nop,pyym::nop}},//悁 yuan
{2,937,{pysm::nop,pyym::nop}},//悂 pi
{1,0,{pysm::k,pyym::un}},//悃 kun
{1,0,{pysm::q,pyym::iao}},//悄 qiao
{1,0,{pysm::y,pyym::ue}},//悅 yue
{2,938,{pysm::nop,pyym::nop}},//悆 yu
{2,939,{pysm::nop,pyym::nop}},//悇 tu
{2,940,{pysm::nop,pyym::nop}},//悈 jie
{1,0,{pysm::x,pyym::i}},//悉 xi
{1,0,{pysm::zh,pyym::e}},//悊 zhe
{1,0,{pysm::l,pyym::in}},//悋 lin
{1,0,{pysm::t,pyym::i}},//悌 ti
{1,0,{pysm::h,pyym::an}},//悍 han
{2,941,{pysm::nop,pyym::nop}},//悎 hao
{1,0,{pysm::q,pyym::ie}},//悏 qie
{1,0,{pysm::t,pyym::i}},//悐 ti
{1,0,{pysm::b,pyym::u}},//悑 bu
{1,0,{pysm::y,pyym::i}},//悒 yi
{1,0,{pysm::q,pyym::ian}},//悓 qian
{1,0,{pysm::h,pyym::ui}},//悔 hui
{1,0,{pysm::x,pyym::i}},//悕 xi
{1,0,{pysm::b,pyym::ei}},//悖 bei
{2,942,{pysm::nop,pyym::nop}},//悗 man
{1,0,{pysm::y,pyym::i}},//悘 yi
{1,0,{pysm::h,pyym::eng}},//悙 heng
{1,0,{pysm::s,pyym::ong}},//悚 song
{2,943,{pysm::nop,pyym::nop}},//悛 quan
{1,0,{pysm::ch,pyym::eng}},//悜 cheng
{2,944,{pysm::nop,pyym::nop}},//悝 kui
{1,0,{pysm::w,pyym::u}},//悞 wu
{1,0,{pysm::w,pyym::u}},//悟 wu
{1,0,{pysm::y,pyym::ou}},//悠 you
{1,0,{pysm::l,pyym::i}},//悡 li
{2,945,{pysm::nop,pyym::nop}},//悢 liang
{1,0,{pysm::h,pyym::uan}},//患 huan
{1,0,{pysm::c,pyym::ong}},//悤 cong
{1,0,{pysm::y,pyym::i}},//悥 yi
{1,0,{pysm::y,pyym::ue}},//悦 yue
{1,0,{pysm::l,pyym::i}},//悧 li
{1,0,{pysm::n,pyym::in}},//您 nin
{1,0,{pysm::n,pyym::ao}},//悩 nao
{1,0,{pysm::nop,pyym::e}},//悪 e
{1,0,{pysm::q,pyym::ue}},//悫 que
{1,0,{pysm::x,pyym::uan}},//悬 xuan
{1,0,{pysm::q,pyym::ian}},//悭 qian
{1,0,{pysm::w,pyym::u}},//悮 wu
{1,0,{pysm::m,pyym::in}},//悯 min
{1,0,{pysm::c,pyym::ong}},//悰 cong
{1,0,{pysm::f,pyym::ei}},//悱 fei
{1,0,{pysm::b,pyym::ei}},//悲 bei
{1,0,{pysm::d,pyym::e}},//悳 de
{1,0,{pysm::c,pyym::ui}},//悴 cui
{1,0,{pysm::ch,pyym::ang}},//悵 chang
{1,0,{pysm::m,pyym::en}},//悶 men
{1,0,{pysm::l,pyym::i}},//悷 li
{1,0,{pysm::j,pyym::i}},//悸 ji
{1,0,{pysm::g,pyym::uan}},//悹 guan
{1,0,{pysm::g,pyym::uan}},//悺 guan
{1,0,{pysm::x,pyym::ing}},//悻 xing
{1,0,{pysm::d,pyym::ao}},//悼 dao
{1,0,{pysm::q,pyym::i}},//悽 qi
{1,0,{pysm::k,pyym::ong}},//悾 kong
{1,0,{pysm::t,pyym::ian}},//悿 tian
{1,0,{pysm::l,pyym::un}},//惀 lun
{1,0,{pysm::x,pyym::i}},//惁 xi
{1,0,{pysm::k,pyym::an}},//惂 kan
{1,0,{pysm::g,pyym::un}},//惃 gun
{1,0,{pysm::n,pyym::i}},//惄 ni
{1,0,{pysm::q,pyym::ing}},//情 qing
{3,214,{pysm::nop,pyym::nop}},//惆 chou
{1,0,{pysm::d,pyym::un}},//惇 dun
{1,0,{pysm::g,pyym::uo}},//惈 guo
{1,0,{pysm::zh,pyym::an}},//惉 zhan
{2,946,{pysm::nop,pyym::nop}},//惊 jing
{1,0,{pysm::w,pyym::an}},//惋 wan
{3,215,{pysm::nop,pyym::nop}},//惌 yuan
{1,0,{pysm::j,pyym::in}},//惍 jin
{1,0,{pysm::j,pyym::i}},//惎 ji
{2,947,{pysm::nop,pyym::nop}},//惏 lan
{2,948,{pysm::nop,pyym::nop}},//惐 yu
{1,0,{pysm::h,pyym::uo}},//惑 huo
{1,0,{pysm::h,pyym::e}},//惒 he
{2,949,{pysm::nop,pyym::nop}},//惓 quan
{2,950,{pysm::nop,pyym::nop}},//惔 tan
{1,0,{pysm::t,pyym::i}},//惕 ti
{1,0,{pysm::t,pyym::i}},//惖 ti
{1,0,{pysm::n,pyym::ie}},//惗 nie
{1,0,{pysm::w,pyym::ang}},//惘 wang
{2,951,{pysm::nop,pyym::nop}},//惙 chuo
{1,0,{pysm::h,pyym::u}},//惚 hu
{2,952,{pysm::nop,pyym::nop}},//惛 hun
{1,0,{pysm::x,pyym::i}},//惜 xi
{2,953,{pysm::nop,pyym::nop}},//惝 chang
{1,0,{pysm::x,pyym::in}},//惞 xin
{1,0,{pysm::w,pyym::ei}},//惟 wei
{1,0,{pysm::h,pyym::ui}},//惠 hui
{3,216,{pysm::nop,pyym::nop}},//惡 e
{2,954,{pysm::nop,pyym::nop}},//惢 suo
{1,0,{pysm::z,pyym::ong}},//惣 zong
{1,0,{pysm::j,pyym::ian}},//惤 jian
{1,0,{pysm::y,pyym::ong}},//惥 yong
{1,0,{pysm::d,pyym::ian}},//惦 dian
{1,0,{pysm::j,pyym::u}},//惧 ju
{1,0,{pysm::c,pyym::an}},//惨 can
{1,0,{pysm::ch,pyym::eng}},//惩 cheng
{1,0,{pysm::d,pyym::e}},//惪 de
{1,0,{pysm::b,pyym::ei}},//惫 bei
{1,0,{pysm::q,pyym::ie}},//惬 qie
{1,0,{pysm::c,pyym::an}},//惭 can
{1,0,{pysm::d,pyym::an}},//惮 dan
{1,0,{pysm::g,pyym::uan}},//惯 guan
{2,955,{pysm::nop,pyym::nop}},//惰 duo
{1,0,{pysm::n,pyym::ao}},//惱 nao
{1,0,{pysm::y,pyym::un}},//惲 yun
{1,0,{pysm::x,pyym::iang}},//想 xiang
{3,217,{pysm::nop,pyym::nop}},//惴 zhui
{2,956,{pysm::nop,pyym::nop}},//惵 die
{1,0,{pysm::h,pyym::uang}},//惶 huang
{1,0,{pysm::ch,pyym::un}},//惷 chun
{1,0,{pysm::q,pyym::iong}},//惸 qiong
{2,957,{pysm::nop,pyym::nop}},//惹 re
{1,0,{pysm::x,pyym::ing}},//惺 xing
{1,0,{pysm::c,pyym::e}},//惻 ce
{1,0,{pysm::b,pyym::ian}},//惼 bian
{2,958,{pysm::nop,pyym::nop}},//惽 min
{1,0,{pysm::z,pyym::ong}},//惾 zong
{2,959,{pysm::nop,pyym::nop}},//惿 ti
{2,960,{pysm::nop,pyym::nop}},//愀 qiao
{3,218,{pysm::nop,pyym::nop}},//愁 chou
{1,0,{pysm::b,pyym::ei}},//愂 bei
{1,0,{pysm::x,pyym::uan}},//愃 xuan
{1,0,{pysm::w,pyym::ei}},//愄 wei
{1,0,{pysm::g,pyym::e}},//愅 ge
{1,0,{pysm::q,pyym::ian}},//愆 qian
{1,0,{pysm::w,pyym::ei}},//愇 wei
{1,0,{pysm::y,pyym::u}},//愈 yu
{2,961,{pysm::nop,pyym::nop}},//愉 yu
{1,0,{pysm::b,pyym::i}},//愊 bi
{1,0,{pysm::x,pyym::uan}},//愋 xuan
{1,0,{pysm::h,pyym::uan}},//愌 huan
{2,962,{pysm::nop,pyym::nop}},//愍 min
{1,0,{pysm::b,pyym::i}},//愎 bi
{1,0,{pysm::y,pyym::i}},//意 yi
{1,0,{pysm::m,pyym::ian}},//愐 mian
{1,0,{pysm::y,pyym::ong}},//愑 yong
{3,219,{pysm::nop,pyym::nop}},//愒 kai
{4,48,{pysm::nop,pyym::nop}},//愓 dang
{1,0,{pysm::y,pyym::in}},//愔 yin
{1,0,{pysm::nop,pyym::e}},//愕 e
{3,220,{pysm::nop,pyym::nop}},//愖 chen
{1,0,{pysm::m,pyym::ao}},//愗 mao
{2,963,{pysm::nop,pyym::nop}},//愘 qia
{1,0,{pysm::k,pyym::e}},//愙 ke
{1,0,{pysm::y,pyym::u}},//愚 yu
{1,0,{pysm::nop,pyym::ai}},//愛 ai
{1,0,{pysm::q,pyym::ie}},//愜 qie
{1,0,{pysm::y,pyym::an}},//愝 yan
{1,0,{pysm::n,pyym::uo}},//愞 nuo
{2,964,{pysm::nop,pyym::nop}},//感 gan
{2,965,{pysm::nop,pyym::nop}},//愠 yun
{1,0,{pysm::z,pyym::ong}},//愡 zong
{2,966,{pysm::nop,pyym::nop}},//愢 sai
{1,0,{pysm::l,pyym::eng}},//愣 leng
{1,0,{pysm::f,pyym::en}},//愤 fen
{1,0,{pysm::y,pyym::ing}},//愥 ying
{1,0,{pysm::k,pyym::ui}},//愦 kui
{1,0,{pysm::k,pyym::ui}},//愧 kui
{1,0,{pysm::q,pyym::ue}},//愨 que
{2,967,{pysm::nop,pyym::nop}},//愩 gong
{1,0,{pysm::y,pyym::un}},//愪 yun
{1,0,{pysm::s,pyym::u}},//愫 su
{2,968,{pysm::nop,pyym::nop}},//愬 su
{1,0,{pysm::q,pyym::i}},//愭 qi
{1,0,{pysm::y,pyym::ao}},//愮 yao
{1,0,{pysm::s,pyym::ong}},//愯 song
{1,0,{pysm::h,pyym::uang}},//愰 huang
{1,0,{pysm::j,pyym::i}},//愱 ji
{1,0,{pysm::g,pyym::u}},//愲 gu
{1,0,{pysm::j,pyym::u}},//愳 ju
{1,0,{pysm::ch,pyym::uang}},//愴 chuang
{1,0,{pysm::n,pyym::i}},//愵 ni
{1,0,{pysm::x,pyym::ie}},//愶 xie
{1,0,{pysm::k,pyym::ai}},//愷 kai
{1,0,{pysm::zh,pyym::eng}},//愸 zheng
{1,0,{pysm::y,pyym::ong}},//愹 yong
{1,0,{pysm::c,pyym::ao}},//愺 cao
{1,0,{pysm::x,pyym::un}},//愻 xun
{1,0,{pysm::sh,pyym::en}},//愼 shen
{1,0,{pysm::b,pyym::o}},//愽 bo
{3,221,{pysm::nop,pyym::nop}},//愾 kai
{1,0,{pysm::y,pyym::uan}},//愿 yuan
{2,969,{pysm::nop,pyym::nop}},//慀 xi
{1,0,{pysm::h,pyym::un}},//慁 hun
{1,0,{pysm::y,pyym::ong}},//慂 yong
{1,0,{pysm::y,pyym::ang}},//慃 yang
{1,0,{pysm::l,pyym::i}},//慄 li
{2,970,{pysm::nop,pyym::nop}},//慅 sao
{1,0,{pysm::t,pyym::ao}},//慆 tao
{1,0,{pysm::y,pyym::in}},//慇 yin
{1,0,{pysm::c,pyym::i}},//慈 ci
{2,971,{pysm::nop,pyym::nop}},//慉 xu
{3,222,{pysm::nop,pyym::nop}},//慊 qian
{1,0,{pysm::t,pyym::ai}},//態 tai
{1,0,{pysm::h,pyym::uang}},//慌 huang
{1,0,{pysm::y,pyym::un}},//慍 yun
{2,972,{pysm::nop,pyym::nop}},//慎 shen
{1,0,{pysm::m,pyym::ing}},//慏 ming
{1,0,{pysm::g,pyym::ong}},//慐 gong
{1,0,{pysm::sh,pyym::e}},//慑 she
{2,973,{pysm::nop,pyym::nop}},//慒 cong
{1,0,{pysm::p,pyym::iao}},//慓 piao
{1,0,{pysm::m,pyym::u}},//慔 mu
{1,0,{pysm::m,pyym::u}},//慕 mu
{1,0,{pysm::g,pyym::uo}},//慖 guo
{1,0,{pysm::ch,pyym::i}},//慗 chi
{1,0,{pysm::c,pyym::an}},//慘 can
{1,0,{pysm::c,pyym::an}},//慙 can
{1,0,{pysm::c,pyym::an}},//慚 can
{1,0,{pysm::c,pyym::ui}},//慛 cui
{1,0,{pysm::m,pyym::in}},//慜 min
{2,974,{pysm::nop,pyym::nop}},//慝 te
{1,0,{pysm::zh,pyym::ang}},//慞 zhang
{1,0,{pysm::t,pyym::ong}},//慟 tong
{1,0,{pysm::nop,pyym::ao}},//慠 ao
{1,0,{pysm::sh,pyym::uang}},//慡 shuang
{1,0,{pysm::m,pyym::an}},//慢 man
{1,0,{pysm::g,pyym::uan}},//慣 guan
{1,0,{pysm::q,pyym::ue}},//慤 que
{2,975,{pysm::nop,pyym::nop}},//慥 zao
{1,0,{pysm::j,pyym::iu}},//慦 jiu
{1,0,{pysm::h,pyym::ui}},//慧 hui
{1,0,{pysm::k,pyym::ai}},//慨 kai
{1,0,{pysm::l,pyym::ian}},//慩 lian
{1,0,{pysm::nop,pyym::ou}},//慪 ou
{1,0,{pysm::s,pyym::ong}},//慫 song
{2,976,{pysm::nop,pyym::nop}},//慬 qin
{1,0,{pysm::y,pyym::in}},//慭 yin
{1,0,{pysm::l,pyym::v}},//慮 lü
{1,0,{pysm::sh,pyym::ang}},//慯 shang
{1,0,{pysm::w,pyym::ei}},//慰 wei
{1,0,{pysm::t,pyym::uan}},//慱 tuan
{1,0,{pysm::m,pyym::an}},//慲 man
{2,977,{pysm::nop,pyym::nop}},//慳 qian
{2,978,{pysm::nop,pyym::nop}},//慴 she
{1,0,{pysm::y,pyym::ong}},//慵 yong
{2,979,{pysm::nop,pyym::nop}},//慶 qing
{1,0,{pysm::k,pyym::ang}},//慷 kang
{2,980,{pysm::nop,pyym::nop}},//慸 di
{2,981,{pysm::nop,pyym::nop}},//慹 zhi
{2,982,{pysm::nop,pyym::nop}},//慺 lou
{1,0,{pysm::j,pyym::uan}},//慻 juan
{1,0,{pysm::q,pyym::i}},//慼 qi
{1,0,{pysm::q,pyym::i}},//慽 qi
{1,0,{pysm::y,pyym::u}},//慾 yu
{1,0,{pysm::p,pyym::ing}},//慿 ping
{1,0,{pysm::l,pyym::iao}},//憀 liao
{2,983,{pysm::nop,pyym::nop}},//憁 cong
{1,0,{pysm::y,pyym::ou}},//憂 you
{1,0,{pysm::ch,pyym::ong}},//憃 chong
{1,0,{pysm::zh,pyym::i}},//憄 zhi
{1,0,{pysm::t,pyym::ong}},//憅 tong
{1,0,{pysm::ch,pyym::eng}},//憆 cheng
{1,0,{pysm::q,pyym::i}},//憇 qi
{1,0,{pysm::q,pyym::u}},//憈 qu
{1,0,{pysm::p,pyym::eng}},//憉 peng
{1,0,{pysm::b,pyym::ei}},//憊 bei
{1,0,{pysm::b,pyym::ie}},//憋 bie
{1,0,{pysm::q,pyym::iong}},//憌 qiong
{1,0,{pysm::j,pyym::iao}},//憍 jiao
{1,0,{pysm::z,pyym::eng}},//憎 zeng
{1,0,{pysm::ch,pyym::i}},//憏 chi
{1,0,{pysm::l,pyym::ian}},//憐 lian
{1,0,{pysm::p,pyym::ing}},//憑 ping
{1,0,{pysm::k,pyym::ui}},//憒 kui
{1,0,{pysm::h,pyym::ui}},//憓 hui
{1,0,{pysm::q,pyym::iao}},//憔 qiao
{3,223,{pysm::nop,pyym::nop}},//憕 cheng
{2,984,{pysm::nop,pyym::nop}},//憖 yin
{1,0,{pysm::y,pyym::in}},//憗 yin
{1,0,{pysm::x,pyym::i}},//憘 xi
{1,0,{pysm::x,pyym::i}},//憙 xi
{3,224,{pysm::nop,pyym::nop}},//憚 dan
{1,0,{pysm::t,pyym::an}},//憛 tan
{1,0,{pysm::d,pyym::uo}},//憜 duo
{1,0,{pysm::d,pyym::ui}},//憝 dui
{3,225,{pysm::nop,pyym::nop}},//憞 dui
{1,0,{pysm::s,pyym::u}},//憟 su
{1,0,{pysm::j,pyym::ue}},//憠 jue
{1,0,{pysm::c,pyym::e}},//憡 ce
{2,985,{pysm::nop,pyym::nop}},//憢 xiao
{1,0,{pysm::f,pyym::an}},//憣 fan
{1,0,{pysm::f,pyym::en}},//憤 fen
{1,0,{pysm::l,pyym::ao}},//憥 lao
{1,0,{pysm::l,pyym::ao}},//憦 lao
{2,986,{pysm::nop,pyym::nop}},//憧 chong
{1,0,{pysm::h,pyym::an}},//憨 han
{1,0,{pysm::q,pyym::i}},//憩 qi
{1,0,{pysm::x,pyym::ian}},//憪 xian
{1,0,{pysm::m,pyym::in}},//憫 min
{1,0,{pysm::j,pyym::ing}},//憬 jing
{1,0,{pysm::l,pyym::iao}},//憭 liao
{1,0,{pysm::w,pyym::u}},//憮 wu
{1,0,{pysm::c,pyym::an}},//憯 can
{1,0,{pysm::j,pyym::ue}},//憰 jue
{1,0,{pysm::c,pyym::u}},//憱 cu
{1,0,{pysm::x,pyym::ian}},//憲 xian
{1,0,{pysm::t,pyym::an}},//憳 tan
{1,0,{pysm::sh,pyym::eng}},//憴 sheng
{1,0,{pysm::p,pyym::i}},//憵 pi
{1,0,{pysm::y,pyym::i}},//憶 yi
{1,0,{pysm::ch,pyym::u}},//憷 chu
{1,0,{pysm::x,pyym::ian}},//憸 xian
{3,226,{pysm::nop,pyym::nop}},//憹 nao
{1,0,{pysm::d,pyym::an}},//憺 dan
{1,0,{pysm::t,pyym::an}},//憻 tan
{1,0,{pysm::j,pyym::ing}},//憼 jing
{1,0,{pysm::s,pyym::ong}},//憽 song
{2,987,{pysm::nop,pyym::nop}},//憾 han
{2,988,{pysm::nop,pyym::nop}},//憿 jiao
{1,0,{pysm::w,pyym::ei}},//懀 wei
{2,989,{pysm::nop,pyym::nop}},//懁 xuan
{1,0,{pysm::d,pyym::ong}},//懂 dong
{1,0,{pysm::q,pyym::in}},//懃 qin
{1,0,{pysm::q,pyym::in}},//懄 qin
{1,0,{pysm::j,pyym::u}},//懅 ju
{2,990,{pysm::nop,pyym::nop}},//懆 cao
{1,0,{pysm::k,pyym::en}},//懇 ken
{1,0,{pysm::x,pyym::ie}},//懈 xie
{1,0,{pysm::y,pyym::ing}},//應 ying
{2,991,{pysm::nop,pyym::nop}},//懊 ao
{1,0,{pysm::m,pyym::ao}},//懋 mao
{1,0,{pysm::y,pyym::i}},//懌 yi
{1,0,{pysm::l,pyym::in}},//懍 lin
{1,0,{pysm::s,pyym::e}},//懎 se
{1,0,{pysm::j,pyym::un}},//懏 jun
{1,0,{pysm::h,pyym::uai}},//懐 huai
{1,0,{pysm::m,pyym::en}},//懑 men
{1,0,{pysm::l,pyym::an}},//懒 lan
{1,0,{pysm::nop,pyym::ai}},//懓 ai
{2,992,{pysm::nop,pyym::nop}},//懔 lin
{2,993,{pysm::nop,pyym::nop}},//懕 yan
{1,0,{pysm::k,pyym::uo}},//懖 kuo
{1,0,{pysm::x,pyym::ia}},//懗 xia
{1,0,{pysm::ch,pyym::i}},//懘 chi
{1,0,{pysm::y,pyym::u}},//懙 yu
{1,0,{pysm::y,pyym::in}},//懚 yin
{1,0,{pysm::d,pyym::ai}},//懛 dai
{1,0,{pysm::m,pyym::eng}},//懜 meng
{2,994,{pysm::nop,pyym::nop}},//懝 ai
{1,0,{pysm::m,pyym::eng}},//懞 meng
{1,0,{pysm::d,pyym::ui}},//懟 dui
{2,995,{pysm::nop,pyym::nop}},//懠 qi
{1,0,{pysm::m,pyym::o}},//懡 mo
{2,996,{pysm::nop,pyym::nop}},//懢 lan
{1,0,{pysm::m,pyym::en}},//懣 men
{1,0,{pysm::ch,pyym::ou}},//懤 chou
{1,0,{pysm::zh,pyym::i}},//懥 zhi
{1,0,{pysm::n,pyym::uo}},//懦 nuo
{1,0,{pysm::n,pyym::uo}},//懧 nuo
{1,0,{pysm::y,pyym::an}},//懨 yan
{1,0,{pysm::y,pyym::ang}},//懩 yang
{1,0,{pysm::b,pyym::o}},//懪 bo
{1,0,{pysm::zh,pyym::i}},//懫 zhi
{1,0,{pysm::k,pyym::uang}},//懬 kuang
{1,0,{pysm::k,pyym::uang}},//懭 kuang
{1,0,{pysm::y,pyym::ou}},//懮 you
{1,0,{pysm::f,pyym::u}},//懯 fu
{1,0,{pysm::l,pyym::iu}},//懰 liu
{1,0,{pysm::m,pyym::ie}},//懱 mie
{1,0,{pysm::ch,pyym::eng}},//懲 cheng
{1,0,{pysm::h,pyym::ui}},//懳 hui
{1,0,{pysm::ch,pyym::an}},//懴 chan
{1,0,{pysm::m,pyym::eng}},//懵 meng
{2,997,{pysm::nop,pyym::nop}},//懶 lan
{1,0,{pysm::h,pyym::uai}},//懷 huai
{1,0,{pysm::x,pyym::uan}},//懸 xuan
{1,0,{pysm::r,pyym::ang}},//懹 rang
{1,0,{pysm::ch,pyym::an}},//懺 chan
{1,0,{pysm::j,pyym::i}},//懻 ji
{1,0,{pysm::j,pyym::u}},//懼 ju
{2,998,{pysm::nop,pyym::nop}},//懽 huan
{1,0,{pysm::sh,pyym::e}},//懾 she
{1,0,{pysm::y,pyym::i}},//懿 yi
{1,0,{pysm::l,pyym::ian}},//戀 lian
{1,0,{pysm::n,pyym::an}},//戁 nan
{2,999,{pysm::nop,pyym::nop}},//戂 mi
{1,0,{pysm::t,pyym::ang}},//戃 tang
{1,0,{pysm::j,pyym::ue}},//戄 jue
{1,0,{pysm::g,pyym::ang}},//戅 gang
{2,1000,{pysm::nop,pyym::nop}},//戆 gang
{2,1001,{pysm::nop,pyym::nop}},//戇 zhuang
{1,0,{pysm::g,pyym::e}},//戈 ge
{1,0,{pysm::y,pyym::ue}},//戉 yue
{1,0,{pysm::w,pyym::u}},//戊 wu
{1,0,{pysm::j,pyym::ian}},//戋 jian
{2,1002,{pysm::nop,pyym::nop}},//戌 xu
{1,0,{pysm::sh,pyym::u}},//戍 shu
{2,1003,{pysm::nop,pyym::nop}},//戎 rong
{2,1004,{pysm::nop,pyym::nop}},//戏 xi
{1,0,{pysm::ch,pyym::eng}},//成 cheng
{1,0,{pysm::w,pyym::o}},//我 wo
{1,0,{pysm::j,pyym::ie}},//戒 jie
{1,0,{pysm::g,pyym::e}},//戓 ge
{2,1005,{pysm::nop,pyym::nop}},//戔 jian
{2,1006,{pysm::nop,pyym::nop}},//戕 qiang
{2,1007,{pysm::nop,pyym::nop}},//或 huo
{1,0,{pysm::q,pyym::iang}},//戗 qiang
{1,0,{pysm::zh,pyym::an}},//战 zhan
{1,0,{pysm::d,pyym::ong}},//戙 dong
{2,1008,{pysm::nop,pyym::nop}},//戚 qi
{2,1009,{pysm::nop,pyym::nop}},//戛 jia
{1,0,{pysm::d,pyym::ie}},//戜 die
{1,0,{pysm::z,pyym::ei}},//戝 zei
{1,0,{pysm::j,pyym::ia}},//戞 jia
{1,0,{pysm::j,pyym::i}},//戟 ji
{1,0,{pysm::zh,pyym::i}},//戠 zhi
{2,1010,{pysm::nop,pyym::nop}},//戡 kan
{1,0,{pysm::j,pyym::i}},//戢 ji
{1,0,{pysm::k,pyym::ui}},//戣 kui
{1,0,{pysm::g,pyym::ai}},//戤 gai
{1,0,{pysm::d,pyym::eng}},//戥 deng
{1,0,{pysm::zh,pyym::an}},//戦 zhan
{2,1011,{pysm::nop,pyym::nop}},//戧 qiang
{1,0,{pysm::g,pyym::e}},//戨 ge
{1,0,{pysm::j,pyym::ian}},//戩 jian
{1,0,{pysm::j,pyym::ie}},//截 jie
{1,0,{pysm::y,pyym::u}},//戫 yu
{1,0,{pysm::j,pyym::ian}},//戬 jian
{2,1012,{pysm::nop,pyym::nop}},//戭 yan
{1,0,{pysm::l,pyym::u}},//戮 lu
{2,1013,{pysm::nop,pyym::nop}},//戯 hu
{1,0,{pysm::zh,pyym::an}},//戰 zhan
{1,0,{pysm::x,pyym::i}},//戱 xi
{5,16,{pysm::nop,pyym::nop}},//戲 xi
{1,0,{pysm::ch,pyym::uo}},//戳 chuo
{1,0,{pysm::d,pyym::ai}},//戴 dai
{1,0,{pysm::q,pyym::u}},//戵 qu
{1,0,{pysm::h,pyym::u}},//戶 hu
{1,0,{pysm::h,pyym::u}},//户 hu
{1,0,{pysm::h,pyym::u}},//戸 hu
{1,0,{pysm::nop,pyym::e}},//戹 e
{2,1014,{pysm::nop,pyym::nop}},//戺 shi
{1,0,{pysm::t,pyym::i}},//戻 ti
{1,0,{pysm::m,pyym::ao}},//戼 mao
{1,0,{pysm::h,pyym::u}},//戽 hu
{1,0,{pysm::l,pyym::i}},//戾 li
{2,1015,{pysm::nop,pyym::nop}},//房 fang
{1,0,{pysm::s,pyym::uo}},//所 suo
{2,1016,{pysm::nop,pyym::nop}},//扁 bian
{1,0,{pysm::d,pyym::ian}},//扂 dian
{1,0,{pysm::j,pyym::iong}},//扃 jiong
{2,1017,{pysm::nop,pyym::nop}},//扄 shang
{1,0,{pysm::y,pyym::i}},//扅 yi
{1,0,{pysm::y,pyym::i}},//扆 yi
{1,0,{pysm::sh,pyym::an}},//扇 shan
{1,0,{pysm::h,pyym::u}},//扈 hu
{1,0,{pysm::f,pyym::ei}},//扉 fei
{1,0,{pysm::y,pyym::an}},//扊 yan
{1,0,{pysm::sh,pyym::ou}},//手 shou
{1,0,{pysm::sh,pyym::ou}},//扌 shou
{2,1018,{pysm::nop,pyym::nop}},//才 cai
{2,1019,{pysm::nop,pyym::nop}},//扎 zha
{1,0,{pysm::q,pyym::iu}},//扏 qiu
{3,227,{pysm::nop,pyym::nop}},//扐 le
{2,1020,{pysm::nop,pyym::nop}},//扑 pu
{4,49,{pysm::nop,pyym::nop}},//扒 ba
{1,0,{pysm::d,pyym::a}},//打 da
{1,0,{pysm::r,pyym::eng}},//扔 reng
{1,0,{pysm::f,pyym::an}},//払 fan
{1,0,{pysm::r,pyym::u}},//扖 ru
{1,0,{pysm::z,pyym::ai}},//扗 zai
{1,0,{pysm::t,pyym::uo}},//托 tuo
{1,0,{pysm::zh,pyym::ang}},//扙 zhang
{4,50,{pysm::nop,pyym::nop}},//扚 diao
{2,1021,{pysm::nop,pyym::nop}},//扛 kang
{2,1022,{pysm::nop,pyym::nop}},//扜 yu
{2,1023,{pysm::nop,pyym::nop}},//扝 ku
{2,1024,{pysm::nop,pyym::nop}},//扞 gan
{1,0,{pysm::sh,pyym::en}},//扟 shen
{3,228,{pysm::nop,pyym::nop}},//扠 cha
{3,229,{pysm::nop,pyym::nop}},//扡 tuo
{4,51,{pysm::nop,pyym::nop}},//扢 gu
{1,0,{pysm::k,pyym::ou}},//扣 kou
{1,0,{pysm::w,pyym::u}},//扤 wu
{1,0,{pysm::d,pyym::en}},//扥 den
{1,0,{pysm::q,pyym::ian}},//扦 qian
{1,0,{pysm::zh,pyym::i}},//执 zhi
{1,0,{pysm::r,pyym::en}},//扨 ren
{1,0,{pysm::k,pyym::uo}},//扩 kuo
{1,0,{pysm::m,pyym::en}},//扪 men
{1,0,{pysm::s,pyym::ao}},//扫 sao
{1,0,{pysm::y,pyym::ang}},//扬 yang
{3,230,{pysm::nop,pyym::nop}},//扭 niu
{3,231,{pysm::nop,pyym::nop}},//扮 ban
{1,0,{pysm::ch,pyym::e}},//扯 che
{2,1025,{pysm::nop,pyym::nop}},//扰 rao
{3,232,{pysm::nop,pyym::nop}},//扱 xi
{2,1026,{pysm::nop,pyym::nop}},//扲 qian
{2,1027,{pysm::nop,pyym::nop}},//扳 ban
{1,0,{pysm::j,pyym::ia}},//扴 jia
{1,0,{pysm::y,pyym::u}},//扵 yu
{2,1028,{pysm::nop,pyym::nop}},//扶 fu
{1,0,{pysm::nop,pyym::ao}},//扷 ao
{2,1029,{pysm::nop,pyym::nop}},//扸 xi
{1,0,{pysm::p,pyym::i}},//批 pi
{2,1030,{pysm::nop,pyym::nop}},//扺 zhi
{3,233,{pysm::nop,pyym::nop}},//扻 zhi
{1,0,{pysm::nop,pyym::e}},//扼 e
{1,0,{pysm::d,pyym::en}},//扽 den
{2,1031,{pysm::nop,pyym::nop}},//找 zhao
{2,1032,{pysm::nop,pyym::nop}},//承 cheng
{2,1033,{pysm::nop,pyym::nop}},//技 ji
{1,0,{pysm::y,pyym::an}},//抁 yan
{2,1034,{pysm::nop,pyym::nop}},//抂 kuang
{1,0,{pysm::b,pyym::ian}},//抃 bian
{2,1035,{pysm::nop,pyym::nop}},//抄 chao
{1,0,{pysm::j,pyym::u}},//抅 ju
{1,0,{pysm::w,pyym::en}},//抆 wen
{1,0,{pysm::h,pyym::u}},//抇 hu
{1,0,{pysm::y,pyym::ue}},//抈 yue
{1,0,{pysm::j,pyym::ue}},//抉 jue
{2,1036,{pysm::nop,pyym::nop}},//把 ba
{1,0,{pysm::q,pyym::in}},//抋 qin
{2,1037,{pysm::nop,pyym::nop}},//抌 dan
{1,0,{pysm::zh,pyym::eng}},//抍 zheng
{1,0,{pysm::y,pyym::un}},//抎 yun
{1,0,{pysm::w,pyym::an}},//抏 wan
{4,52,{pysm::nop,pyym::nop}},//抐 ne
{1,0,{pysm::y,pyym::i}},//抑 yi
{1,0,{pysm::sh,pyym::u}},//抒 shu
{1,0,{pysm::zh,pyym::ua}},//抓 zhua
{1,0,{pysm::p,pyym::ou}},//抔 pou
{2,1038,{pysm::nop,pyym::nop}},//投 tou
{1,0,{pysm::d,pyym::ou}},//抖 dou
{2,1039,{pysm::nop,pyym::nop}},//抗 kang
{3,234,{pysm::nop,pyym::nop}},//折 zhe
{1,0,{pysm::p,pyym::ou}},//抙 pou
{1,0,{pysm::f,pyym::u}},//抚 fu
{1,0,{pysm::p,pyym::ao}},//抛 pao
{1,0,{pysm::b,pyym::a}},//抜 ba
{2,1040,{pysm::nop,pyym::nop}},//抝 ao
{1,0,{pysm::z,pyym::e}},//択 ze
{1,0,{pysm::t,pyym::uan}},//抟 tuan
{1,0,{pysm::k,pyym::ou}},//抠 kou
{1,0,{pysm::l,pyym::un}},//抡 lun
{1,0,{pysm::q,pyym::iang}},//抢 qiang
{1,0,{pysm::y,pyym::un}},//抣 yun
{1,0,{pysm::h,pyym::u}},//护 hu
{1,0,{pysm::b,pyym::ao}},//报 bao
{1,0,{pysm::b,pyym::ing}},//抦 bing
{2,1041,{pysm::nop,pyym::nop}},//抧 zhi
{2,1042,{pysm::nop,pyym::nop}},//抨 peng
{1,0,{pysm::n,pyym::an}},//抩 nan
{3,235,{pysm::nop,pyym::nop}},//抪 bu
{1,0,{pysm::p,pyym::i}},//披 pi
{2,1043,{pysm::nop,pyym::nop}},//抬 tai
{2,1044,{pysm::nop,pyym::nop}},//抭 yao
{1,0,{pysm::zh,pyym::en}},//抮 zhen
{1,0,{pysm::zh,pyym::a}},//抯 zha
{1,0,{pysm::y,pyym::ang}},//抰 yang
{3,236,{pysm::nop,pyym::nop}},//抱 bao
{2,1045,{pysm::nop,pyym::nop}},//抲 he
{1,0,{pysm::n,pyym::i}},//抳 ni
{2,1046,{pysm::nop,pyym::nop}},//抴 ye
{3,237,{pysm::nop,pyym::nop}},//抵 di
{1,0,{pysm::ch,pyym::i}},//抶 chi
{2,1047,{pysm::nop,pyym::nop}},//抷 pi
{1,0,{pysm::j,pyym::ia}},//抸 jia
{2,1048,{pysm::nop,pyym::nop}},//抹 mo
{1,0,{pysm::m,pyym::ei}},//抺 mei
{2,1049,{pysm::nop,pyym::nop}},//抻 chen
{3,238,{pysm::nop,pyym::nop}},//押 ya
{1,0,{pysm::ch,pyym::ou}},//抽 chou
{1,0,{pysm::q,pyym::u}},//抾 qu
{1,0,{pysm::m,pyym::in}},//抿 min
{1,0,{pysm::ch,pyym::u}},//拀 chu
{2,1050,{pysm::nop,pyym::nop}},//拁 jia
{4,53,{pysm::nop,pyym::nop}},//拂 fu
{2,1051,{pysm::nop,pyym::nop}},//拃 zha
{1,0,{pysm::zh,pyym::u}},//拄 zhu
{2,1052,{pysm::nop,pyym::nop}},//担 dan
{4,54,{pysm::nop,pyym::nop}},//拆 chai
{1,0,{pysm::m,pyym::u}},//拇 mu
{2,1053,{pysm::nop,pyym::nop}},//拈 nian
{1,0,{pysm::l,pyym::a}},//拉 la
{2,1054,{pysm::nop,pyym::nop}},//拊 fu
{1,0,{pysm::p,pyym::ao}},//拋 pao
{2,1055,{pysm::nop,pyym::nop}},//拌 ban
{2,1056,{pysm::nop,pyym::nop}},//拍 pai
{2,1057,{pysm::nop,pyym::nop}},//拎 lin
{1,0,{pysm::n,pyym::a}},//拏 na
{1,0,{pysm::g,pyym::uai}},//拐 guai
{1,0,{pysm::q,pyym::ian}},//拑 qian
{1,0,{pysm::j,pyym::u}},//拒 ju
{3,239,{pysm::nop,pyym::nop}},//拓 tuo
{5,17,{pysm::nop,pyym::nop}},//拔 ba
{1,0,{pysm::t,pyym::uo}},//拕 tuo
{2,1058,{pysm::nop,pyym::nop}},//拖 tuo
{3,240,{pysm::nop,pyym::nop}},//拗 ao
{2,1059,{pysm::nop,pyym::nop}},//拘 ju
{1,0,{pysm::zh,pyym::uo}},//拙 zhuo
{5,18,{pysm::nop,pyym::nop}},//拚 pan
{3,241,{pysm::nop,pyym::nop}},//招 zhao
{1,0,{pysm::b,pyym::ai}},//拜 bai
{1,0,{pysm::b,pyym::ai}},//拝 bai
{1,0,{pysm::d,pyym::i}},//拞 di
{1,0,{pysm::n,pyym::i}},//拟 ni
{1,0,{pysm::j,pyym::u}},//拠 ju
{1,0,{pysm::k,pyym::uo}},//拡 kuo
{1,0,{pysm::l,pyym::ong}},//拢 long
{1,0,{pysm::j,pyym::ian}},//拣 jian
{1,0,{pysm::q,pyym::ia}},//拤 qia
{1,0,{pysm::y,pyym::ong}},//拥 yong
{1,0,{pysm::l,pyym::an}},//拦 lan
{1,0,{pysm::n,pyym::ing}},//拧 ning
{1,0,{pysm::b,pyym::o}},//拨 bo
{2,1060,{pysm::nop,pyym::nop}},//择 ze
{1,0,{pysm::q,pyym::ian}},//拪 qian
{1,0,{pysm::h,pyym::en}},//拫 hen
{2,1061,{pysm::nop,pyym::nop}},//括 kuo
{1,0,{pysm::sh,pyym::i}},//拭 shi
{2,1062,{pysm::nop,pyym::nop}},//拮 jie
{1,0,{pysm::zh,pyym::eng}},//拯 zheng
{1,0,{pysm::n,pyym::in}},//拰 nin
{2,1063,{pysm::nop,pyym::nop}},//拱 gong
{1,0,{pysm::g,pyym::ong}},//拲 gong
{1,0,{pysm::q,pyym::uan}},//拳 quan
{2,1064,{pysm::nop,pyym::nop}},//拴 shuan
{2,1065,{pysm::nop,pyym::nop}},//拵 cun
{2,1066,{pysm::nop,pyym::nop}},//拶 za
{1,0,{pysm::k,pyym::ao}},//拷 kao
{3,242,{pysm::nop,pyym::nop}},//拸 yi
{1,0,{pysm::x,pyym::ie}},//拹 xie
{3,243,{pysm::nop,pyym::nop}},//拺 ce
{1,0,{pysm::h,pyym::ui}},//拻 hui
{2,1067,{pysm::nop,pyym::nop}},//拼 pin
{2,1068,{pysm::nop,pyym::nop}},//拽 zhuai
{3,244,{pysm::nop,pyym::nop}},//拾 shi
{1,0,{pysm::n,pyym::a}},//拿 na
{1,0,{pysm::b,pyym::ai}},//挀 bai
{1,0,{pysm::ch,pyym::i}},//持 chi
{1,0,{pysm::g,pyym::ua}},//挂 gua
{2,1069,{pysm::nop,pyym::nop}},//挃 zhi
{2,1070,{pysm::nop,pyym::nop}},//挄 kuo
{1,0,{pysm::d,pyym::uo}},//挅 duo
{1,0,{pysm::d,pyym::uo}},//挆 duo
{1,0,{pysm::zh,pyym::i}},//指 zhi
{5,19,{pysm::nop,pyym::nop}},//挈 qie
{1,0,{pysm::nop,pyym::an}},//按 an
{1,0,{pysm::n,pyym::ong}},//挊 nong
{1,0,{pysm::zh,pyym::en}},//挋 zhen
{2,1071,{pysm::nop,pyym::nop}},//挌 ge
{1,0,{pysm::j,pyym::iao}},//挍 jiao
{3,245,{pysm::nop,pyym::nop}},//挎 kua
{1,0,{pysm::d,pyym::ong}},//挏 dong
{3,246,{pysm::nop,pyym::nop}},//挐 na
{3,247,{pysm::nop,pyym::nop}},//挑 tiao
{1,0,{pysm::l,pyym::ie}},//挒 lie
{1,0,{pysm::zh,pyym::a}},//挓 zha
{1,0,{pysm::l,pyym::v}},//挔 lü
{2,1072,{pysm::nop,pyym::nop}},//挕 die
{1,0,{pysm::w,pyym::a}},//挖 wa
{1,0,{pysm::j,pyym::ue}},//挗 jue
{1,0,{pysm::l,pyym::ie}},//挘 lie
{1,0,{pysm::j,pyym::u}},//挙 ju
{1,0,{pysm::zh,pyym::i}},//挚 zhi
{1,0,{pysm::l,pyym::uan}},//挛 luan
{1,0,{pysm::y,pyym::a}},//挜 ya
{2,1073,{pysm::nop,pyym::nop}},//挝 wo
{1,0,{pysm::t,pyym::a}},//挞 ta
{2,1074,{pysm::nop,pyym::nop}},//挟 xie
{1,0,{pysm::n,pyym::ao}},//挠 nao
{1,0,{pysm::d,pyym::ang}},//挡 dang
{1,0,{pysm::j,pyym::iao}},//挢 jiao
{1,0,{pysm::zh,pyym::eng}},//挣 zheng
{1,0,{pysm::j,pyym::i}},//挤 ji
{1,0,{pysm::h,pyym::ui}},//挥 hui
{1,0,{pysm::x,pyym::ian}},//挦 xian
{1,0,{pysm::y,pyym::u}},//挧 yu
{1,0,{pysm::nop,pyym::ai}},//挨 ai
{1,0,{pysm::t,pyym::uo}},//挩 tuo
{1,0,{pysm::n,pyym::uo}},//挪 nuo
{2,1075,{pysm::nop,pyym::nop}},//挫 cuo
{1,0,{pysm::b,pyym::o}},//挬 bo
{1,0,{pysm::g,pyym::eng}},//挭 geng
{1,0,{pysm::t,pyym::i}},//挮 ti
{1,0,{pysm::zh,pyym::en}},//振 zhen
{1,0,{pysm::ch,pyym::eng}},//挰 cheng
{3,248,{pysm::nop,pyym::nop}},//挱 sa
{3,249,{pysm::nop,pyym::nop}},//挲 sa
{1,0,{pysm::k,pyym::eng}},//挳 keng
{1,0,{pysm::m,pyym::ei}},//挴 mei
{1,0,{pysm::n,pyym::ong}},//挵 nong
{1,0,{pysm::j,pyym::u}},//挶 ju
{1,0,{pysm::p,pyym::eng}},//挷 peng
{1,0,{pysm::j,pyym::ian}},//挸 jian
{1,0,{pysm::y,pyym::i}},//挹 yi
{1,0,{pysm::t,pyym::ing}},//挺 ting
{2,1076,{pysm::nop,pyym::nop}},//挻 shan
{4,55,{pysm::nop,pyym::nop}},//挼 rua
{1,0,{pysm::w,pyym::an}},//挽 wan
{2,1077,{pysm::nop,pyym::nop}},//挾 xie
{1,0,{pysm::ch,pyym::a}},//挿 cha
{1,0,{pysm::f,pyym::eng}},//捀 feng
{2,1078,{pysm::nop,pyym::nop}},//捁 jiao
{1,0,{pysm::w,pyym::u}},//捂 wu
{1,0,{pysm::j,pyym::un}},//捃 jun
{3,250,{pysm::nop,pyym::nop}},//捄 jiu
{1,0,{pysm::t,pyym::ong}},//捅 tong
{2,1079,{pysm::nop,pyym::nop}},//捆 kun
{2,1080,{pysm::nop,pyym::nop}},//捇 huo
{3,251,{pysm::nop,pyym::nop}},//捈 tu
{1,0,{pysm::zh,pyym::uo}},//捉 zhuo
{2,1081,{pysm::nop,pyym::nop}},//捊 pou
{2,1082,{pysm::nop,pyym::nop}},//捋 lü
{2,1083,{pysm::nop,pyym::nop}},//捌 ba
{3,252,{pysm::nop,pyym::nop}},//捍 han
{3,253,{pysm::nop,pyym::nop}},//捎 shao
{1,0,{pysm::n,pyym::ie}},//捏 nie
{2,1084,{pysm::nop,pyym::nop}},//捐 juan
{1,0,{pysm::z,pyym::e}},//捑 ze
{3,254,{pysm::nop,pyym::nop}},//捒 shu
{2,1085,{pysm::nop,pyym::nop}},//捓 ye
{2,1086,{pysm::nop,pyym::nop}},//捔 jue
{1,0,{pysm::b,pyym::u}},//捕 bu
{2,1087,{pysm::nop,pyym::nop}},//捖 wan
{3,255,{pysm::nop,pyym::nop}},//捗 bu
{1,0,{pysm::z,pyym::un}},//捘 zun
{1,0,{pysm::y,pyym::e}},//捙 ye
{1,0,{pysm::zh,pyym::ai}},//捚 zhai
{1,0,{pysm::l,pyym::v}},//捛 lü
{1,0,{pysm::s,pyym::ou}},//捜 sou
{3,256,{pysm::nop,pyym::nop}},//捝 tuo
{1,0,{pysm::l,pyym::ao}},//捞 lao
{1,0,{pysm::s,pyym::un}},//损 sun
{1,0,{pysm::b,pyym::ang}},//捠 bang
{1,0,{pysm::j,pyym::ian}},//捡 jian
{1,0,{pysm::h,pyym::uan}},//换 huan
{1,0,{pysm::d,pyym::ao}},//捣 dao
{1,0,{pysm::w,pyym::ei}},//捤 wei
{2,1088,{pysm::nop,pyym::nop}},//捥 wan
{1,0,{pysm::q,pyym::in}},//捦 qin
{2,1089,{pysm::nop,pyym::nop}},//捧 peng
{1,0,{pysm::sh,pyym::e}},//捨 she
{2,1090,{pysm::nop,pyym::nop}},//捩 lie
{1,0,{pysm::m,pyym::in}},//捪 min
{1,0,{pysm::m,pyym::en}},//捫 men
{2,1091,{pysm::nop,pyym::nop}},//捬 fu
{3,257,{pysm::nop,pyym::nop}},//捭 bai
{1,0,{pysm::j,pyym::u}},//据 ju
{1,0,{pysm::d,pyym::ao}},//捯 dao
{2,1092,{pysm::nop,pyym::nop}},//捰 wo
{1,0,{pysm::nop,pyym::ai}},//捱 ai
{2,1093,{pysm::nop,pyym::nop}},//捲 juan
{1,0,{pysm::y,pyym::ue}},//捳 yue
{1,0,{pysm::z,pyym::ong}},//捴 zong
{3,258,{pysm::nop,pyym::nop}},//捵 chen
{2,1094,{pysm::nop,pyym::nop}},//捶 chui
{3,259,{pysm::nop,pyym::nop}},//捷 jie
{1,0,{pysm::t,pyym::u}},//捸 tu
{1,0,{pysm::b,pyym::en}},//捹 ben
{1,0,{pysm::n,pyym::a}},//捺 na
{2,1095,{pysm::nop,pyym::nop}},//捻 nian
{4,56,{pysm::nop,pyym::nop}},//捼 ruo
{4,57,{pysm::nop,pyym::nop}},//捽 zuo
{2,1096,{pysm::nop,pyym::nop}},//捾 wo
{1,0,{pysm::q,pyym::i}},//捿 qi
{2,1097,{pysm::nop,pyym::nop}},//掀 xian
{1,0,{pysm::ch,pyym::eng}},//掁 cheng
{1,0,{pysm::d,pyym::ian}},//掂 dian
{1,0,{pysm::s,pyym::ao}},//掃 sao
{1,0,{pysm::l,pyym::un}},//掄 lun
{1,0,{pysm::q,pyym::ing}},//掅 qing
{1,0,{pysm::g,pyym::ang}},//掆 gang
{2,1098,{pysm::nop,pyym::nop}},//掇 duo
{1,0,{pysm::sh,pyym::ou}},//授 shou
{2,1099,{pysm::nop,pyym::nop}},//掉 diao
{3,260,{pysm::nop,pyym::nop}},//掊 pou
{1,0,{pysm::d,pyym::i}},//掋 di
{1,0,{pysm::zh,pyym::ang}},//掌 zhang
{1,0,{pysm::h,pyym::un}},//掍 hun
{2,1100,{pysm::nop,pyym::nop}},//掎 ji
{1,0,{pysm::t,pyym::ao}},//掏 tao
{1,0,{pysm::q,pyym::ia}},//掐 qia
{1,0,{pysm::q,pyym::i}},//掑 qi
{2,1101,{pysm::nop,pyym::nop}},//排 pai
{1,0,{pysm::sh,pyym::u}},//掓 shu
{2,1102,{pysm::nop,pyym::nop}},//掔 qian
{1,0,{pysm::l,pyym::ing}},//掕 ling
{1,0,{pysm::y,pyym::e}},//掖 ye
{1,0,{pysm::y,pyym::a}},//掗 ya
{2,1103,{pysm::nop,pyym::nop}},//掘 jue
{1,0,{pysm::zh,pyym::eng}},//掙 zheng
{1,0,{pysm::l,pyym::iang}},//掚 liang
{1,0,{pysm::g,pyym::ua}},//掛 gua
{4,58,{pysm::nop,pyym::nop}},//掜 yi
{2,1104,{pysm::nop,pyym::nop}},//掝 huo
{2,1105,{pysm::nop,pyym::nop}},//掞 shan
{2,1106,{pysm::nop,pyym::nop}},//掟 zheng
{1,0,{pysm::l,pyym::ve}},//掠 lüe
{1,0,{pysm::c,pyym::ai}},//採 cai
{2,1107,{pysm::nop,pyym::nop}},//探 tan
{1,0,{pysm::ch,pyym::e}},//掣 che
{1,0,{pysm::b,pyym::ing}},//掤 bing
{4,59,{pysm::nop,pyym::nop}},//接 jie
{1,0,{pysm::t,pyym::i}},//掦 ti
{2,1108,{pysm::nop,pyym::nop}},//控 kong
{1,0,{pysm::t,pyym::ui}},//推 tui
{1,0,{pysm::y,pyym::an}},//掩 yan
{3,261,{pysm::nop,pyym::nop}},//措 cuo
{3,262,{pysm::nop,pyym::nop}},//掫 zhou
{1,0,{pysm::j,pyym::u}},//掬 ju
{1,0,{pysm::t,pyym::ian}},//掭 tian
{1,0,{pysm::q,pyym::ian}},//掮 qian
{1,0,{pysm::k,pyym::en}},//掯 ken
{1,0,{pysm::b,pyym::ai}},//掰 bai
{2,1109,{pysm::nop,pyym::nop}},//掱 pa
{1,0,{pysm::j,pyym::ie}},//掲 jie
{1,0,{pysm::l,pyym::u}},//掳 lu
{2,1110,{pysm::nop,pyym::nop}},//掴 guai
{1,0,{pysm::m,pyym::ing}},//掵 ming
{1,0,{pysm::j,pyym::ie}},//掶 jie
{1,0,{pysm::zh,pyym::i}},//掷 zhi
{2,1111,{pysm::nop,pyym::nop}},//掸 dan
{1,0,{pysm::m,pyym::eng}},//掹 meng
{3,263,{pysm::nop,pyym::nop}},//掺 can
{1,0,{pysm::s,pyym::ao}},//掻 sao
{1,0,{pysm::g,pyym::uan}},//掼 guan
{1,0,{pysm::p,pyym::eng}},//掽 peng
{2,1112,{pysm::nop,pyym::nop}},//掾 yuan
{1,0,{pysm::n,pyym::uo}},//掿 nuo
{1,0,{pysm::j,pyym::ian}},//揀 jian
{2,1113,{pysm::nop,pyym::nop}},//揁 zheng
{2,1114,{pysm::nop,pyym::nop}},//揂 jiu
{2,1115,{pysm::nop,pyym::nop}},//揃 jian
{5,20,{pysm::nop,pyym::nop}},//揄 yu
{1,0,{pysm::y,pyym::an}},//揅 yan
{1,0,{pysm::k,pyym::ui}},//揆 kui
{1,0,{pysm::n,pyym::an}},//揇 nan
{3,264,{pysm::nop,pyym::nop}},//揈 hong
{1,0,{pysm::r,pyym::ou}},//揉 rou
{2,1116,{pysm::nop,pyym::nop}},//揊 pi
{1,0,{pysm::w,pyym::ei}},//揋 wei
{2,1117,{pysm::nop,pyym::nop}},//揌 sai
{2,1118,{pysm::nop,pyym::nop}},//揍 zou
{1,0,{pysm::x,pyym::uan}},//揎 xuan
{2,1119,{pysm::nop,pyym::nop}},//描 miao
{4,60,{pysm::nop,pyym::nop}},//提 ti
{1,0,{pysm::n,pyym::ie}},//揑 nie
{2,1120,{pysm::nop,pyym::nop}},//插 cha
{1,0,{pysm::sh,pyym::i}},//揓 shi
{2,1121,{pysm::nop,pyym::nop}},//揔 zong
{1,0,{pysm::zh,pyym::en}},//揕 zhen
{2,1122,{pysm::nop,pyym::nop}},//揖 yi
{1,0,{pysm::x,pyym::un}},//揗 xun
{2,1123,{pysm::nop,pyym::nop}},//揘 yong
{1,0,{pysm::b,pyym::ian}},//揙 bian
{1,0,{pysm::y,pyym::ang}},//揚 yang
{1,0,{pysm::h,pyym::uan}},//換 huan
{1,0,{pysm::y,pyym::an}},//揜 yan
{2,1124,{pysm::nop,pyym::nop}},//揝 zan
{3,265,{pysm::nop,pyym::nop}},//揞 an
{2,1125,{pysm::nop,pyym::nop}},//揟 xu
{1,0,{pysm::y,pyym::a}},//揠 ya
{2,1126,{pysm::nop,pyym::nop}},//握 wo
{2,1127,{pysm::nop,pyym::nop}},//揢 ke
{4,61,{pysm::nop,pyym::nop}},//揣 chuai
{1,0,{pysm::j,pyym::i}},//揤 ji
{2,1128,{pysm::nop,pyym::nop}},//揥 ti
{1,0,{pysm::l,pyym::a}},//揦 la
{1,0,{pysm::l,pyym::a}},//揧 la
{1,0,{pysm::ch,pyym::en}},//揨 chen
{2,1129,{pysm::nop,pyym::nop}},//揩 kai
{1,0,{pysm::j,pyym::iu}},//揪 jiu
{1,0,{pysm::j,pyym::iu}},//揫 jiu
{1,0,{pysm::t,pyym::u}},//揬 tu
{3,266,{pysm::nop,pyym::nop}},//揭 jie
{2,1130,{pysm::nop,pyym::nop}},//揮 hui
{1,0,{pysm::g,pyym::en}},//揯 gen
{2,1131,{pysm::nop,pyym::nop}},//揰 chong
{3,267,{pysm::nop,pyym::nop}},//揱 xiao
{3,268,{pysm::nop,pyym::nop}},//揲 die
{2,1132,{pysm::nop,pyym::nop}},//揳 xie
{2,1133,{pysm::nop,pyym::nop}},//援 yuan
{2,1134,{pysm::nop,pyym::nop}},//揵 qian
{1,0,{pysm::y,pyym::e}},//揶 ye
{1,0,{pysm::ch,pyym::a}},//揷 cha
{1,0,{pysm::zh,pyym::a}},//揸 zha
{1,0,{pysm::b,pyym::ei}},//揹 bei
{1,0,{pysm::y,pyym::ao}},//揺 yao
{1,0,{pysm::w,pyym::ei}},//揻 wei
{1,0,{pysm::b,pyym::eng}},//揼 beng
{1,0,{pysm::l,pyym::an}},//揽 lan
{2,1135,{pysm::nop,pyym::nop}},//揾 wen
{1,0,{pysm::q,pyym::in}},//揿 qin
{1,0,{pysm::ch,pyym::an}},//搀 chan
{1,0,{pysm::g,pyym::e}},//搁 ge
{1,0,{pysm::l,pyym::ou}},//搂 lou
{1,0,{pysm::z,pyym::ong}},//搃 zong
{1,0,{pysm::g,pyym::en}},//搄 gen
{1,0,{pysm::j,pyym::iao}},//搅 jiao
{1,0,{pysm::g,pyym::ou}},//搆 gou
{1,0,{pysm::q,pyym::in}},//搇 qin
{1,0,{pysm::r,pyym::ong}},//搈 rong
{2,1136,{pysm::nop,pyym::nop}},//搉 que
{3,269,{pysm::nop,pyym::nop}},//搊 chou
{3,270,{pysm::nop,pyym::nop}},//搋 chuai
{1,0,{pysm::zh,pyym::an}},//搌 zhan
{1,0,{pysm::s,pyym::un}},//損 sun
{1,0,{pysm::s,pyym::un}},//搎 sun
{1,0,{pysm::b,pyym::o}},//搏 bo
{1,0,{pysm::ch,pyym::u}},//搐 chu
{2,1137,{pysm::nop,pyym::nop}},//搑 rong
{3,271,{pysm::nop,pyym::nop}},//搒 bang
{2,1138,{pysm::nop,pyym::nop}},//搓 cuo
{1,0,{pysm::s,pyym::ao}},//搔 sao
{2,1139,{pysm::nop,pyym::nop}},//搕 ke
{1,0,{pysm::y,pyym::ao}},//搖 yao
{1,0,{pysm::d,pyym::ao}},//搗 dao
{1,0,{pysm::zh,pyym::i}},//搘 zhi
{3,272,{pysm::nop,pyym::nop}},//搙 nu
{3,273,{pysm::nop,pyym::nop}},//搚 la
{2,1140,{pysm::nop,pyym::nop}},//搛 jian
{3,274,{pysm::nop,pyym::nop}},//搜 sou
{1,0,{pysm::q,pyym::iu}},//搝 qiu
{3,275,{pysm::nop,pyym::nop}},//搞 gao
{1,0,{pysm::x,pyym::ian}},//搟 xian
{1,0,{pysm::sh,pyym::uo}},//搠 shuo
{1,0,{pysm::s,pyym::ang}},//搡 sang
{1,0,{pysm::j,pyym::in}},//搢 jin
{1,0,{pysm::m,pyym::ie}},//搣 mie
{2,1141,{pysm::nop,pyym::nop}},//搤 e
{2,1142,{pysm::nop,pyym::nop}},//搥 chui
{1,0,{pysm::n,pyym::uo}},//搦 nuo
{1,0,{pysm::sh,pyym::an}},//搧 shan
{2,1143,{pysm::nop,pyym::nop}},//搨 ta
{2,1144,{pysm::nop,pyym::nop}},//搩 zha
{1,0,{pysm::t,pyym::ang}},//搪 tang
{3,276,{pysm::nop,pyym::nop}},//搫 pan
{2,1145,{pysm::nop,pyym::nop}},//搬 ban
{2,1146,{pysm::nop,pyym::nop}},//搭 da
{1,0,{pysm::l,pyym::i}},//搮 li
{1,0,{pysm::t,pyym::ao}},//搯 tao
{2,1147,{pysm::nop,pyym::nop}},//搰 hu
{2,1148,{pysm::nop,pyym::nop}},//搱 zhi
{1,0,{pysm::w,pyym::a}},//搲 wa
{3,277,{pysm::nop,pyym::nop}},//搳 hua
{1,0,{pysm::q,pyym::ian}},//搴 qian
{1,0,{pysm::w,pyym::en}},//搵 wen
{2,1149,{pysm::nop,pyym::nop}},//搶 qiang
{2,1150,{pysm::nop,pyym::nop}},//搷 tian
{1,0,{pysm::zh,pyym::en}},//搸 zhen
{1,0,{pysm::nop,pyym::e}},//搹 e
{1,0,{pysm::x,pyym::ie}},//携 xie
{1,0,{pysm::n,pyym::uo}},//搻 nuo
{1,0,{pysm::q,pyym::uan}},//搼 quan
{1,0,{pysm::ch,pyym::a}},//搽 cha
{1,0,{pysm::zh,pyym::a}},//搾 zha
{1,0,{pysm::g,pyym::e}},//搿 ge
{1,0,{pysm::w,pyym::u}},//摀 wu
{1,0,{pysm::nop,pyym::en}},//摁 en
{1,0,{pysm::sh,pyym::e}},//摂 she
{1,0,{pysm::k,pyym::ang}},//摃 kang
{1,0,{pysm::sh,pyym::e}},//摄 she
{1,0,{pysm::sh,pyym::u}},//摅 shu
{1,0,{pysm::b,pyym::ai}},//摆 bai
{1,0,{pysm::y,pyym::ao}},//摇 yao
{1,0,{pysm::b,pyym::in}},//摈 bin
{1,0,{pysm::s,pyym::ou}},//摉 sou
{1,0,{pysm::t,pyym::an}},//摊 tan
{3,278,{pysm::nop,pyym::nop}},//摋 sa
{2,1151,{pysm::nop,pyym::nop}},//摌 chan
{1,0,{pysm::s,pyym::uo}},//摍 suo
{5,21,{pysm::nop,pyym::nop}},//摎 jiu
{1,0,{pysm::ch,pyym::ong}},//摏 chong
{1,0,{pysm::ch,pyym::uang}},//摐 chuang
{2,1152,{pysm::nop,pyym::nop}},//摑 guai
{1,0,{pysm::b,pyym::ing}},//摒 bing
{2,1153,{pysm::nop,pyym::nop}},//摓 feng
{1,0,{pysm::sh,pyym::uai}},//摔 shuai
{3,279,{pysm::nop,pyym::nop}},//摕 di
{2,1154,{pysm::nop,pyym::nop}},//摖 qi
{2,1155,{pysm::nop,pyym::nop}},//摗 sou
{1,0,{pysm::zh,pyym::ai}},//摘 zhai
{1,0,{pysm::l,pyym::ian}},//摙 lian
{1,0,{pysm::ch,pyym::eng}},//摚 cheng
{1,0,{pysm::ch,pyym::i}},//摛 chi
{1,0,{pysm::g,pyym::uan}},//摜 guan
{1,0,{pysm::l,pyym::u}},//摝 lu
{1,0,{pysm::l,pyym::uo}},//摞 luo
{1,0,{pysm::l,pyym::ou}},//摟 lou
{1,0,{pysm::z,pyym::ong}},//摠 zong
{2,1156,{pysm::nop,pyym::nop}},//摡 gai
{2,1157,{pysm::nop,pyym::nop}},//摢 hu
{2,1158,{pysm::nop,pyym::nop}},//摣 zha
{1,0,{pysm::ch,pyym::uang}},//摤 chuang
{1,0,{pysm::t,pyym::ang}},//摥 tang
{1,0,{pysm::h,pyym::ua}},//摦 hua
{3,280,{pysm::nop,pyym::nop}},//摧 cui
{2,1159,{pysm::nop,pyym::nop}},//摨 nai
{3,281,{pysm::nop,pyym::nop}},//摩 mo
{2,1160,{pysm::nop,pyym::nop}},//摪 jiang
{1,0,{pysm::g,pyym::ui}},//摫 gui
{1,0,{pysm::y,pyym::ing}},//摬 ying
{1,0,{pysm::zh,pyym::i}},//摭 zhi
{2,1161,{pysm::nop,pyym::nop}},//摮 ao
{1,0,{pysm::zh,pyym::i}},//摯 zhi
{2,1162,{pysm::nop,pyym::nop}},//摰 nie
{1,0,{pysm::m,pyym::an}},//摱 man
{2,1163,{pysm::nop,pyym::nop}},//摲 chan
{2,1164,{pysm::nop,pyym::nop}},//摳 kou
{2,1165,{pysm::nop,pyym::nop}},//摴 chu
{3,282,{pysm::nop,pyym::nop}},//摵 she
{2,1166,{pysm::nop,pyym::nop}},//摶 tuan
{2,1167,{pysm::nop,pyym::nop}},//摷 jiao
{1,0,{pysm::m,pyym::o}},//摸 mo
{1,0,{pysm::m,pyym::o}},//摹 mo
{3,283,{pysm::nop,pyym::nop}},//摺 zhe
{4,62,{pysm::nop,pyym::nop}},//摻 can
{2,1168,{pysm::nop,pyym::nop}},//摼 keng
{3,284,{pysm::nop,pyym::nop}},//摽 biao
{1,0,{pysm::j,pyym::iang}},//摾 jiang
{1,0,{pysm::y,pyym::ao}},//摿 yao
{1,0,{pysm::g,pyym::ou}},//撀 gou
{1,0,{pysm::q,pyym::ian}},//撁 qian
{1,0,{pysm::l,pyym::iao}},//撂 liao
{1,0,{pysm::j,pyym::i}},//撃 ji
{1,0,{pysm::y,pyym::ing}},//撄 ying
{2,1169,{pysm::nop,pyym::nop}},//撅 jue
{1,0,{pysm::p,pyym::ie}},//撆 pie
{2,1170,{pysm::nop,pyym::nop}},//撇 pie
{1,0,{pysm::l,pyym::ao}},//撈 lao
{1,0,{pysm::d,pyym::un}},//撉 dun
{1,0,{pysm::x,pyym::ian}},//撊 xian
{5,22,{pysm::nop,pyym::nop}},//撋 ruan
{1,0,{pysm::g,pyym::ui}},//撌 gui
{3,285,{pysm::nop,pyym::nop}},//撍 zan
{1,0,{pysm::y,pyym::i}},//撎 yi
{2,1171,{pysm::nop,pyym::nop}},//撏 xian
{1,0,{pysm::ch,pyym::eng}},//撐 cheng
{1,0,{pysm::ch,pyym::eng}},//撑 cheng
{1,0,{pysm::s,pyym::a}},//撒 sa
{3,286,{pysm::nop,pyym::nop}},//撓 nao
{1,0,{pysm::h,pyym::ong}},//撔 hong
{2,1172,{pysm::nop,pyym::nop}},//撕 si
{2,1173,{pysm::nop,pyym::nop}},//撖 han
{1,0,{pysm::g,pyym::uang}},//撗 guang
{1,0,{pysm::d,pyym::a}},//撘 da
{1,0,{pysm::z,pyym::un}},//撙 zun
{1,0,{pysm::n,pyym::ian}},//撚 nian
{1,0,{pysm::l,pyym::in}},//撛 lin
{2,1174,{pysm::nop,pyym::nop}},//撜 zheng
{2,1175,{pysm::nop,pyym::nop}},//撝 hui
{1,0,{pysm::zh,pyym::uang}},//撞 zhuang
{2,1176,{pysm::nop,pyym::nop}},//撟 jiao
{1,0,{pysm::j,pyym::i}},//撠 ji
{1,0,{pysm::c,pyym::ao}},//撡 cao
{3,287,{pysm::nop,pyym::nop}},//撢 dan
{6,1,{pysm::nop,pyym::nop}},//撣 dan
{1,0,{pysm::ch,pyym::e}},//撤 che
{2,1177,{pysm::nop,pyym::nop}},//撥 bo
{1,0,{pysm::ch,pyym::e}},//撦 che
{1,0,{pysm::j,pyym::ue}},//撧 jue
{3,288,{pysm::nop,pyym::nop}},//撨 fu
{2,1178,{pysm::nop,pyym::nop}},//撩 liao
{1,0,{pysm::b,pyym::en}},//撪 ben
{2,1179,{pysm::nop,pyym::nop}},//撫 fu
{1,0,{pysm::q,pyym::iao}},//撬 qiao
{1,0,{pysm::b,pyym::o}},//播 bo
{5,23,{pysm::nop,pyym::nop}},//撮 cuo
{1,0,{pysm::zh,pyym::uo}},//撯 zhuo
{3,289,{pysm::nop,pyym::nop}},//撰 zhuan
{2,1180,{pysm::nop,pyym::nop}},//撱 wei
{2,1181,{pysm::nop,pyym::nop}},//撲 pu
{1,0,{pysm::q,pyym::in}},//撳 qin
{1,0,{pysm::d,pyym::un}},//撴 dun
{1,0,{pysm::n,pyym::ian}},//撵 nian
{1,0,{pysm::h,pyym::ua}},//撶 hua
{1,0,{pysm::x,pyym::ie}},//撷 xie
{1,0,{pysm::l,pyym::u}},//撸 lu
{1,0,{pysm::j,pyym::iao}},//撹 jiao
{1,0,{pysm::c,pyym::uan}},//撺 cuan
{1,0,{pysm::t,pyym::a}},//撻 ta
{1,0,{pysm::h,pyym::an}},//撼 han
{3,290,{pysm::nop,pyym::nop}},//撽 qiao
{2,1182,{pysm::nop,pyym::nop}},//撾 wo
{2,1183,{pysm::nop,pyym::nop}},//撿 jian
{1,0,{pysm::g,pyym::an}},//擀 gan
{1,0,{pysm::y,pyym::ong}},//擁 yong
{1,0,{pysm::l,pyym::ei}},//擂 lei
{1,0,{pysm::n,pyym::ang}},//擃 nang
{1,0,{pysm::l,pyym::u}},//擄 lu
{1,0,{pysm::sh,pyym::an}},//擅 shan
{1,0,{pysm::zh,pyym::uo}},//擆 zhuo
{3,291,{pysm::nop,pyym::nop}},//擇 ze
{1,0,{pysm::p,pyym::u}},//擈 pu
{1,0,{pysm::ch,pyym::uo}},//擉 chuo
{2,1184,{pysm::nop,pyym::nop}},//擊 ji
{1,0,{pysm::d,pyym::ang}},//擋 dang
{1,0,{pysm::s,pyym::e}},//擌 se
{1,0,{pysm::c,pyym::ao}},//操 cao
{1,0,{pysm::q,pyym::ing}},//擎 qing
{2,1185,{pysm::nop,pyym::nop}},//擏 qing
{3,292,{pysm::nop,pyym::nop}},//擐 huan
{1,0,{pysm::j,pyym::ie}},//擑 jie
{1,0,{pysm::q,pyym::in}},//擒 qin
{1,0,{pysm::k,pyym::uai}},//擓 kuai
{2,1186,{pysm::nop,pyym::nop}},//擔 dan
{1,0,{pysm::x,pyym::ie}},//擕 xie
{8,0,{pysm::nop,pyym::nop}},//擖 ka
{2,1187,{pysm::nop,pyym::nop}},//擗 pi
{2,1188,{pysm::nop,pyym::nop}},//擘 bai
{1,0,{pysm::nop,pyym::ao}},//擙 ao
{1,0,{pysm::j,pyym::u}},//據 ju
{1,0,{pysm::y,pyym::e}},//擛 ye
{1,0,{pysm::nop,pyym::e}},//擜 e
{1,0,{pysm::m,pyym::eng}},//擝 meng
{1,0,{pysm::s,pyym::ou}},//擞 sou
{1,0,{pysm::m,pyym::i}},//擟 mi
{1,0,{pysm::j,pyym::i}},//擠 ji
{1,0,{pysm::t,pyym::ai}},//擡 tai
{1,0,{pysm::zh,pyym::uo}},//擢 zhuo
{2,1189,{pysm::nop,pyym::nop}},//擣 dao
{1,0,{pysm::x,pyym::ing}},//擤 xing
{1,0,{pysm::l,pyym::an}},//擥 lan
{1,0,{pysm::c,pyym::a}},//擦 ca
{1,0,{pysm::j,pyym::u}},//擧 ju
{1,0,{pysm::y,pyym::e}},//擨 ye
{4,63,{pysm::nop,pyym::nop}},//擩 ru
{1,0,{pysm::y,pyym::e}},//擪 ye
{1,0,{pysm::y,pyym::e}},//擫 ye
{1,0,{pysm::n,pyym::i}},//擬 ni
{3,293,{pysm::nop,pyym::nop}},//擭 wo
{1,0,{pysm::j,pyym::ie}},//擮 jie
{1,0,{pysm::b,pyym::in}},//擯 bin
{1,0,{pysm::n,pyym::ing}},//擰 ning
{1,0,{pysm::g,pyym::e}},//擱 ge
{1,0,{pysm::zh,pyym::i}},//擲 zhi
{2,1190,{pysm::nop,pyym::nop}},//擳 zhi
{3,294,{pysm::nop,pyym::nop}},//擴 kuo
{1,0,{pysm::m,pyym::o}},//擵 mo
{1,0,{pysm::j,pyym::ian}},//擶 jian
{1,0,{pysm::x,pyym::ie}},//擷 xie
{2,1191,{pysm::nop,pyym::nop}},//擸 lie
{1,0,{pysm::t,pyym::an}},//擹 tan
{1,0,{pysm::b,pyym::ai}},//擺 bai
{1,0,{pysm::s,pyym::ou}},//擻 sou
{1,0,{pysm::l,pyym::u}},//擼 lu
{3,295,{pysm::nop,pyym::nop}},//擽 lüe
{1,0,{pysm::r,pyym::ao}},//擾 rao
{3,296,{pysm::nop,pyym::nop}},//擿 ti
{1,0,{pysm::p,pyym::an}},//攀 pan
{1,0,{pysm::y,pyym::ang}},//攁 yang
{1,0,{pysm::l,pyym::ei}},//攂 lei
{2,1192,{pysm::nop,pyym::nop}},//攃 ca
{2,1193,{pysm::nop,pyym::nop}},//攄 shu
{1,0,{pysm::z,pyym::an}},//攅 zan
{1,0,{pysm::n,pyym::ian}},//攆 nian
{1,0,{pysm::x,pyym::ian}},//攇 xian
{2,1194,{pysm::nop,pyym::nop}},//攈 jun
{2,1195,{pysm::nop,pyym::nop}},//攉 huo
{1,0,{pysm::l,pyym::i}},//攊 li
{2,1196,{pysm::nop,pyym::nop}},//攋 la
{1,0,{pysm::h,pyym::uan}},//攌 huan
{1,0,{pysm::y,pyym::ing}},//攍 ying
{2,1197,{pysm::nop,pyym::nop}},//攎 lu
{1,0,{pysm::l,pyym::ong}},//攏 long
{1,0,{pysm::q,pyym::ian}},//攐 qian
{1,0,{pysm::q,pyym::ian}},//攑 qian
{2,1198,{pysm::nop,pyym::nop}},//攒 zan
{1,0,{pysm::q,pyym::ian}},//攓 qian
{1,0,{pysm::l,pyym::an}},//攔 lan
{2,1199,{pysm::nop,pyym::nop}},//攕 xian
{1,0,{pysm::y,pyym::ing}},//攖 ying
{1,0,{pysm::m,pyym::ei}},//攗 mei
{3,297,{pysm::nop,pyym::nop}},//攘 rang
{2,1200,{pysm::nop,pyym::nop}},//攙 chan
{1,0,{pysm::w,pyym::eng}},//攚 weng
{1,0,{pysm::c,pyym::uan}},//攛 cuan
{1,0,{pysm::x,pyym::ie}},//攜 xie
{4,64,{pysm::nop,pyym::nop}},//攝 she
{1,0,{pysm::l,pyym::uo}},//攞 luo
{1,0,{pysm::j,pyym::un}},//攟 jun
{2,1201,{pysm::nop,pyym::nop}},//攠 mi
{1,0,{pysm::ch,pyym::i}},//攡 chi
{3,298,{pysm::nop,pyym::nop}},//攢 zan
{2,1202,{pysm::nop,pyym::nop}},//攣 luan
{2,1203,{pysm::nop,pyym::nop}},//攤 tan
{1,0,{pysm::z,pyym::uan}},//攥 zuan
{2,1204,{pysm::nop,pyym::nop}},//攦 li
{1,0,{pysm::d,pyym::ian}},//攧 dian
{1,0,{pysm::w,pyym::a}},//攨 wa
{2,1205,{pysm::nop,pyym::nop}},//攩 dang
{1,0,{pysm::j,pyym::iao}},//攪 jiao
{1,0,{pysm::j,pyym::ue}},//攫 jue
{1,0,{pysm::l,pyym::an}},//攬 lan
{2,1206,{pysm::nop,pyym::nop}},//攭 li
{1,0,{pysm::n,pyym::ang}},//攮 nang
{2,1207,{pysm::nop,pyym::nop}},//支 zhi
{1,0,{pysm::g,pyym::ui}},//攰 gui
{1,0,{pysm::g,pyym::ui}},//攱 gui
{2,1208,{pysm::nop,pyym::nop}},//攲 qi
{1,0,{pysm::x,pyym::un}},//攳 xun
{1,0,{pysm::p,pyym::u}},//攴 pu
{1,0,{pysm::p,pyym::u}},//攵 pu
{1,0,{pysm::sh,pyym::ou}},//收 shou
{1,0,{pysm::k,pyym::ao}},//攷 kao
{1,0,{pysm::y,pyym::ou}},//攸 you
{1,0,{pysm::g,pyym::ai}},//改 gai
{1,0,{pysm::y,pyym::i}},//攺 yi
{1,0,{pysm::g,pyym::ong}},//攻 gong
{2,1209,{pysm::nop,pyym::nop}},//攼 gan
{2,1210,{pysm::nop,pyym::nop}},//攽 ban
{1,0,{pysm::f,pyym::ang}},//放 fang
{1,0,{pysm::zh,pyym::eng}},//政 zheng
{1,0,{pysm::p,pyym::o}},//敀 po
{1,0,{pysm::d,pyym::ian}},//敁 dian
{1,0,{pysm::k,pyym::ou}},//敂 kou
{2,1211,{pysm::nop,pyym::nop}},//敃 min
{2,1212,{pysm::nop,pyym::nop}},//敄 wu
{1,0,{pysm::g,pyym::u}},//故 gu
{1,0,{pysm::h,pyym::e}},//敆 he
{1,0,{pysm::c,pyym::e}},//敇 ce
{1,0,{pysm::x,pyym::iao}},//效 xiao
{1,0,{pysm::m,pyym::i}},//敉 mi
{2,1213,{pysm::nop,pyym::nop}},//敊 chu
{1,0,{pysm::g,pyym::e}},//敋 ge
{2,1214,{pysm::nop,pyym::nop}},//敌 di
{1,0,{pysm::x,pyym::u}},//敍 xu
{1,0,{pysm::j,pyym::iao}},//敎 jiao
{1,0,{pysm::m,pyym::in}},//敏 min
{1,0,{pysm::ch,pyym::en}},//敐 chen
{1,0,{pysm::j,pyym::iu}},//救 jiu
{1,0,{pysm::sh,pyym::en}},//敒 shen
{1,0,{pysm::d,pyym::uo}},//敓 duo
{1,0,{pysm::y,pyym::u}},//敔 yu
{2,1215,{pysm::nop,pyym::nop}},//敕 chi
{1,0,{pysm::nop,pyym::ao}},//敖 ao
{1,0,{pysm::b,pyym::ai}},//敗 bai
{1,0,{pysm::x,pyym::u}},//敘 xu
{1,0,{pysm::j,pyym::iao}},//教 jiao
{1,0,{pysm::d,pyym::uo}},//敚 duo
{1,0,{pysm::l,pyym::ian}},//敛 lian
{1,0,{pysm::n,pyym::ie}},//敜 nie
{1,0,{pysm::b,pyym::i}},//敝 bi
{3,299,{pysm::nop,pyym::nop}},//敞 chang
{1,0,{pysm::d,pyym::ian}},//敟 dian
{2,1216,{pysm::nop,pyym::nop}},//敠 duo
{1,0,{pysm::y,pyym::i}},//敡 yi
{1,0,{pysm::g,pyym::an}},//敢 gan
{1,0,{pysm::s,pyym::an}},//散 san
{1,0,{pysm::k,pyym::e}},//敤 ke
{2,1217,{pysm::nop,pyym::nop}},//敥 yan
{7,0,{pysm::nop,pyym::nop}},//敦 dun
{2,1218,{pysm::nop,pyym::nop}},//敧 ji
{1,0,{pysm::t,pyym::ou}},//敨 tou
{2,1219,{pysm::nop,pyym::nop}},//敩 xiao
{1,0,{pysm::d,pyym::uo}},//敪 duo
{2,1220,{pysm::nop,pyym::nop}},//敫 jiao
{1,0,{pysm::j,pyym::ing}},//敬 jing
{1,0,{pysm::y,pyym::ang}},//敭 yang
{1,0,{pysm::x,pyym::ia}},//敮 xia
{1,0,{pysm::m,pyym::in}},//敯 min
{2,1221,{pysm::nop,pyym::nop}},//数 shu
{2,1222,{pysm::nop,pyym::nop}},//敱 ai
{1,0,{pysm::q,pyym::iao}},//敲 qiao
{1,0,{pysm::nop,pyym::ai}},//敳 ai
{1,0,{pysm::zh,pyym::eng}},//整 zheng
{1,0,{pysm::d,pyym::i}},//敵 di
{1,0,{pysm::zh,pyym::en}},//敶 zhen
{1,0,{pysm::f,pyym::u}},//敷 fu
{2,1223,{pysm::nop,pyym::nop}},//數 shu
{1,0,{pysm::l,pyym::iao}},//敹 liao
{2,1224,{pysm::nop,pyym::nop}},//敺 qu
{1,0,{pysm::x,pyym::iong}},//敻 xiong
{1,0,{pysm::y,pyym::i}},//敼 yi
{1,0,{pysm::j,pyym::iao}},//敽 jiao
{1,0,{pysm::sh,pyym::an}},//敾 shan
{1,0,{pysm::j,pyym::iao}},//敿 jiao
{2,1225,{pysm::nop,pyym::nop}},//斀 zhuo
{3,300,{pysm::nop,pyym::nop}},//斁 yi
{1,0,{pysm::l,pyym::ian}},//斂 lian
{1,0,{pysm::b,pyym::i}},//斃 bi
{2,1226,{pysm::nop,pyym::nop}},//斄 li
{2,1227,{pysm::nop,pyym::nop}},//斅 xiao
{1,0,{pysm::x,pyym::iao}},//斆 xiao
{1,0,{pysm::w,pyym::en}},//文 wen
{1,0,{pysm::x,pyym::ue}},//斈 xue
{1,0,{pysm::q,pyym::i}},//斉 qi
{1,0,{pysm::q,pyym::i}},//斊 qi
{1,0,{pysm::zh,pyym::ai}},//斋 zhai
{1,0,{pysm::b,pyym::in}},//斌 bin
{1,0,{pysm::j,pyym::ue}},//斍 jue
{1,0,{pysm::zh,pyym::ai}},//斎 zhai
{1,0,{pysm::l,pyym::ang}},//斏 lang
{1,0,{pysm::f,pyym::ei}},//斐 fei
{1,0,{pysm::b,pyym::an}},//斑 ban
{1,0,{pysm::b,pyym::an}},//斒 ban
{1,0,{pysm::l,pyym::an}},//斓 lan
{1,0,{pysm::y,pyym::u}},//斔 yu
{1,0,{pysm::l,pyym::an}},//斕 lan
{1,0,{pysm::w,pyym::ei}},//斖 wei
{2,1228,{pysm::nop,pyym::nop}},//斗 dou
{1,0,{pysm::sh,pyym::eng}},//斘 sheng
{1,0,{pysm::l,pyym::iao}},//料 liao
{1,0,{pysm::j,pyym::ia}},//斚 jia
{1,0,{pysm::h,pyym::u}},//斛 hu
{4,65,{pysm::nop,pyym::nop}},//斜 xie
{1,0,{pysm::j,pyym::ia}},//斝 jia
{1,0,{pysm::y,pyym::u}},//斞 yu
{1,0,{pysm::zh,pyym::en}},//斟 zhen
{1,0,{pysm::j,pyym::iao}},//斠 jiao
{2,1229,{pysm::nop,pyym::nop}},//斡 wo
{2,1230,{pysm::nop,pyym::nop}},//斢 tiao
{1,0,{pysm::d,pyym::ou}},//斣 dou
{1,0,{pysm::j,pyym::in}},//斤 jin
{3,301,{pysm::nop,pyym::nop}},//斥 chi
{2,1231,{pysm::nop,pyym::nop}},//斦 yin
{1,0,{pysm::f,pyym::u}},//斧 fu
{1,0,{pysm::q,pyym::iang}},//斨 qiang
{1,0,{pysm::zh,pyym::an}},//斩 zhan
{1,0,{pysm::q,pyym::u}},//斪 qu
{2,1232,{pysm::nop,pyym::nop}},//斫 zhuo
{1,0,{pysm::zh,pyym::an}},//斬 zhan
{1,0,{pysm::d,pyym::uan}},//断 duan
{2,1233,{pysm::nop,pyym::nop}},//斮 cuo
{2,1234,{pysm::nop,pyym::nop}},//斯 si
{1,0,{pysm::x,pyym::in}},//新 xin
{1,0,{pysm::zh,pyym::uo}},//斱 zhuo
{1,0,{pysm::zh,pyym::uo}},//斲 zhuo
{2,1235,{pysm::nop,pyym::nop}},//斳 qin
{1,0,{pysm::l,pyym::in}},//斴 lin
{1,0,{pysm::zh,pyym::uo}},//斵 zhuo
{1,0,{pysm::ch,pyym::u}},//斶 chu
{1,0,{pysm::d,pyym::uan}},//斷 duan
{1,0,{pysm::zh,pyym::u}},//斸 zhu
{4,66,{pysm::nop,pyym::nop}},//方 fang
{2,1236,{pysm::nop,pyym::nop}},//斺 chan
{1,0,{pysm::h,pyym::ang}},//斻 hang
{2,1237,{pysm::nop,pyym::nop}},//於 yu
{2,1238,{pysm::nop,pyym::nop}},//施 shi
{1,0,{pysm::p,pyym::ei}},//斾 pei
{2,1239,{pysm::nop,pyym::nop}},//斿 you
{1,0,{pysm::m,pyym::ei}},//旀 mei
{4,67,{pysm::nop,pyym::nop}},//旁 pang
{1,0,{pysm::q,pyym::i}},//旂 qi
{1,0,{pysm::zh,pyym::an}},//旃 zhan
{2,1240,{pysm::nop,pyym::nop}},//旄 mao
{1,0,{pysm::l,pyym::v}},//旅 lü
{1,0,{pysm::p,pyym::ei}},//旆 pei
{2,1241,{pysm::nop,pyym::nop}},//旇 pi
{1,0,{pysm::l,pyym::iu}},//旈 liu
{1,0,{pysm::f,pyym::u}},//旉 fu
{1,0,{pysm::f,pyym::ang}},//旊 fang
{1,0,{pysm::x,pyym::uan}},//旋 xuan
{1,0,{pysm::j,pyym::ing}},//旌 jing
{1,0,{pysm::j,pyym::ing}},//旍 jing
{1,0,{pysm::n,pyym::i}},//旎 ni
{4,68,{pysm::nop,pyym::nop}},//族 zu
{1,0,{pysm::zh,pyym::ao}},//旐 zhao
{1,0,{pysm::y,pyym::i}},//旑 yi
{1,0,{pysm::l,pyym::iu}},//旒 liu
{1,0,{pysm::sh,pyym::ao}},//旓 shao
{1,0,{pysm::j,pyym::ian}},//旔 jian
{1,0,{pysm::y,pyym::u}},//旕 yu
{1,0,{pysm::y,pyym::i}},//旖 yi
{1,0,{pysm::q,pyym::i}},//旗 qi
{1,0,{pysm::zh,pyym::i}},//旘 zhi
{1,0,{pysm::f,pyym::an}},//旙 fan
{1,0,{pysm::p,pyym::iao}},//旚 piao
{1,0,{pysm::f,pyym::an}},//旛 fan
{1,0,{pysm::zh,pyym::an}},//旜 zhan
{1,0,{pysm::k,pyym::uai}},//旝 kuai
{1,0,{pysm::s,pyym::ui}},//旞 sui
{1,0,{pysm::y,pyym::u}},//旟 yu
{2,1242,{pysm::nop,pyym::nop}},//无 wu
{1,0,{pysm::j,pyym::i}},//旡 ji
{2,1243,{pysm::nop,pyym::nop}},//既 ji
{1,0,{pysm::j,pyym::i}},//旣 ji
{1,0,{pysm::h,pyym::uo}},//旤 huo
{1,0,{pysm::r,pyym::i}},//日 ri
{1,0,{pysm::d,pyym::an}},//旦 dan
{1,0,{pysm::j,pyym::iu}},//旧 jiu
{1,0,{pysm::zh,pyym::i}},//旨 zhi
{1,0,{pysm::z,pyym::ao}},//早 zao
{1,0,{pysm::x,pyym::ie}},//旪 xie
{1,0,{pysm::t,pyym::iao}},//旫 tiao
{2,1244,{pysm::nop,pyym::nop}},//旬 xun
{1,0,{pysm::x,pyym::u}},//旭 xu
{2,1245,{pysm::nop,pyym::nop}},//旮 ga
{1,0,{pysm::l,pyym::a}},//旯 la
{2,1246,{pysm::nop,pyym::nop}},//旰 gan
{1,0,{pysm::h,pyym::an}},//旱 han
{2,1247,{pysm::nop,pyym::nop}},//旲 tai
{1,0,{pysm::d,pyym::i}},//旳 di
{1,0,{pysm::x,pyym::u}},//旴 xu
{1,0,{pysm::ch,pyym::an}},//旵 chan
{1,0,{pysm::sh,pyym::i}},//时 shi
{1,0,{pysm::k,pyym::uang}},//旷 kuang
{1,0,{pysm::y,pyym::ang}},//旸 yang
{1,0,{pysm::sh,pyym::i}},//旹 shi
{1,0,{pysm::w,pyym::ang}},//旺 wang
{1,0,{pysm::m,pyym::in}},//旻 min
{1,0,{pysm::m,pyym::in}},//旼 min
{2,1248,{pysm::nop,pyym::nop}},//旽 tun
{1,0,{pysm::ch,pyym::un}},//旾 chun
{1,0,{pysm::w,pyym::u}},//旿 wu
{1,0,{pysm::y,pyym::un}},//昀 yun
{1,0,{pysm::b,pyym::ei}},//昁 bei
{2,1249,{pysm::nop,pyym::nop}},//昂 ang
{1,0,{pysm::z,pyym::e}},//昃 ze
{1,0,{pysm::b,pyym::an}},//昄 ban
{1,0,{pysm::j,pyym::ie}},//昅 jie
{2,1250,{pysm::nop,pyym::nop}},//昆 kun
{1,0,{pysm::sh,pyym::eng}},//昇 sheng
{1,0,{pysm::h,pyym::u}},//昈 hu
{1,0,{pysm::f,pyym::ang}},//昉 fang
{1,0,{pysm::h,pyym::ao}},//昊 hao
{2,1251,{pysm::nop,pyym::nop}},//昋 gui
{1,0,{pysm::ch,pyym::ang}},//昌 chang
{1,0,{pysm::x,pyym::uan}},//昍 xuan
{2,1252,{pysm::nop,pyym::nop}},//明 ming
{1,0,{pysm::h,pyym::un}},//昏 hun
{1,0,{pysm::f,pyym::en}},//昐 fen
{1,0,{pysm::q,pyym::in}},//昑 qin
{1,0,{pysm::h,pyym::u}},//昒 hu
{1,0,{pysm::y,pyym::i}},//易 yi
{2,1253,{pysm::nop,pyym::nop}},//昔 xi
{2,1254,{pysm::nop,pyym::nop}},//昕 xin
{1,0,{pysm::y,pyym::an}},//昖 yan
{1,0,{pysm::z,pyym::e}},//昗 ze
{1,0,{pysm::f,pyym::ang}},//昘 fang
{2,1255,{pysm::nop,pyym::nop}},//昙 tan
{1,0,{pysm::sh,pyym::en}},//昚 shen
{1,0,{pysm::j,pyym::u}},//昛 ju
{1,0,{pysm::y,pyym::ang}},//昜 yang
{1,0,{pysm::z,pyym::an}},//昝 zan
{2,1256,{pysm::nop,pyym::nop}},//昞 bing
{1,0,{pysm::x,pyym::ing}},//星 xing
{2,1257,{pysm::nop,pyym::nop}},//映 ying
{1,0,{pysm::x,pyym::uan}},//昡 xuan
{2,1258,{pysm::nop,pyym::nop}},//昢 po
{1,0,{pysm::zh,pyym::en}},//昣 zhen
{1,0,{pysm::l,pyym::ing}},//昤 ling
{1,0,{pysm::ch,pyym::un}},//春 chun
{1,0,{pysm::h,pyym::ao}},//昦 hao
{3,302,{pysm::nop,pyym::nop}},//昧 mei
{1,0,{pysm::z,pyym::uo}},//昨 zuo
{1,0,{pysm::m,pyym::o}},//昩 mo
{1,0,{pysm::b,pyym::ian}},//昪 bian
{2,1259,{pysm::nop,pyym::nop}},//昫 xu
{1,0,{pysm::h,pyym::un}},//昬 hun
{1,0,{pysm::zh,pyym::ao}},//昭 zhao
{1,0,{pysm::z,pyym::ong}},//昮 zong
{2,1260,{pysm::nop,pyym::nop}},//是 shi
{2,1261,{pysm::nop,pyym::nop}},//昰 shi
{1,0,{pysm::y,pyym::u}},//昱 yu
{1,0,{pysm::f,pyym::ei}},//昲 fei
{2,1262,{pysm::nop,pyym::nop}},//昳 die
{1,0,{pysm::m,pyym::ao}},//昴 mao
{2,1263,{pysm::nop,pyym::nop}},//昵 ni
{1,0,{pysm::ch,pyym::ang}},//昶 chang
{1,0,{pysm::w,pyym::en}},//昷 wen
{1,0,{pysm::d,pyym::ong}},//昸 dong
{1,0,{pysm::nop,pyym::ai}},//昹 ai
{1,0,{pysm::b,pyym::ing}},//昺 bing
{1,0,{pysm::nop,pyym::ang}},//昻 ang
{1,0,{pysm::zh,pyym::ou}},//昼 zhou
{1,0,{pysm::l,pyym::ong}},//昽 long
{1,0,{pysm::x,pyym::ian}},//显 xian
{1,0,{pysm::k,pyym::uang}},//昿 kuang
{1,0,{pysm::t,pyym::iao}},//晀 tiao
{2,1264,{pysm::nop,pyym::nop}},//晁 chao
{1,0,{pysm::sh,pyym::i}},//時 shi
{1,0,{pysm::h,pyym::uang}},//晃 huang
{1,0,{pysm::h,pyym::uang}},//晄 huang
{1,0,{pysm::x,pyym::uan}},//晅 xuan
{1,0,{pysm::k,pyym::ui}},//晆 kui
{2,1265,{pysm::nop,pyym::nop}},//晇 xu
{1,0,{pysm::j,pyym::iao}},//晈 jiao
{1,0,{pysm::j,pyym::in}},//晉 jin
{1,0,{pysm::zh,pyym::i}},//晊 zhi
{1,0,{pysm::j,pyym::in}},//晋 jin
{1,0,{pysm::sh,pyym::ang}},//晌 shang
{1,0,{pysm::t,pyym::ong}},//晍 tong
{1,0,{pysm::h,pyym::ong}},//晎 hong
{1,0,{pysm::y,pyym::an}},//晏 yan
{1,0,{pysm::g,pyym::ai}},//晐 gai
{1,0,{pysm::x,pyym::iang}},//晑 xiang
{1,0,{pysm::sh,pyym::ai}},//晒 shai
{1,0,{pysm::x,pyym::iao}},//晓 xiao
{1,0,{pysm::y,pyym::e}},//晔 ye
{1,0,{pysm::y,pyym::un}},//晕 yun
{1,0,{pysm::h,pyym::ui}},//晖 hui
{1,0,{pysm::h,pyym::an}},//晗 han
{1,0,{pysm::h,pyym::an}},//晘 han
{1,0,{pysm::j,pyym::un}},//晙 jun
{1,0,{pysm::w,pyym::an}},//晚 wan
{1,0,{pysm::x,pyym::ian}},//晛 xian
{1,0,{pysm::k,pyym::un}},//晜 kun
{1,0,{pysm::zh,pyym::ou}},//晝 zhou
{1,0,{pysm::x,pyym::i}},//晞 xi
{3,303,{pysm::nop,pyym::nop}},//晟 cheng
{1,0,{pysm::sh,pyym::eng}},//晠 sheng
{1,0,{pysm::b,pyym::u}},//晡 bu
{2,1266,{pysm::nop,pyym::nop}},//晢 zhe
{1,0,{pysm::zh,pyym::e}},//晣 zhe
{1,0,{pysm::w,pyym::u}},//晤 wu
{1,0,{pysm::w,pyym::an}},//晥 wan
{1,0,{pysm::h,pyym::ui}},//晦 hui
{1,0,{pysm::h,pyym::ao}},//晧 hao
{1,0,{pysm::ch,pyym::en}},//晨 chen
{1,0,{pysm::w,pyym::an}},//晩 wan
{1,0,{pysm::t,pyym::ian}},//晪 tian
{1,0,{pysm::zh,pyym::uo}},//晫 zhuo
{1,0,{pysm::z,pyym::ui}},//晬 zui
{1,0,{pysm::zh,pyym::ou}},//晭 zhou
{1,0,{pysm::p,pyym::u}},//普 pu
{2,1267,{pysm::nop,pyym::nop}},//景 jing
{1,0,{pysm::x,pyym::i}},//晰 xi
{1,0,{pysm::sh,pyym::an}},//晱 shan
{1,0,{pysm::n,pyym::i}},//晲 ni
{1,0,{pysm::x,pyym::i}},//晳 xi
{1,0,{pysm::q,pyym::ing}},//晴 qing
{2,1268,{pysm::nop,pyym::nop}},//晵 qi
{1,0,{pysm::j,pyym::ing}},//晶 jing
{1,0,{pysm::g,pyym::ui}},//晷 gui
{1,0,{pysm::zh,pyym::eng}},//晸 zheng
{1,0,{pysm::y,pyym::i}},//晹 yi
{1,0,{pysm::zh,pyym::i}},//智 zhi
{2,1269,{pysm::nop,pyym::nop}},//晻 an
{1,0,{pysm::w,pyym::an}},//晼 wan
{1,0,{pysm::l,pyym::in}},//晽 lin
{1,0,{pysm::l,pyym::iang}},//晾 liang
{1,0,{pysm::ch,pyym::ang}},//晿 chang
{1,0,{pysm::w,pyym::ang}},//暀 wang
{1,0,{pysm::x,pyym::iao}},//暁 xiao
{1,0,{pysm::z,pyym::an}},//暂 zan
{1,0,{pysm::f,pyym::ei}},//暃 fei
{1,0,{pysm::x,pyym::uan}},//暄 xuan
{2,1270,{pysm::nop,pyym::nop}},//暅 geng
{1,0,{pysm::y,pyym::i}},//暆 yi
{2,1271,{pysm::nop,pyym::nop}},//暇 xia
{1,0,{pysm::y,pyym::un}},//暈 yun
{1,0,{pysm::h,pyym::ui}},//暉 hui
{1,0,{pysm::x,pyym::u}},//暊 xu
{1,0,{pysm::m,pyym::in}},//暋 min
{1,0,{pysm::k,pyym::ui}},//暌 kui
{1,0,{pysm::y,pyym::e}},//暍 ye
{1,0,{pysm::y,pyym::ing}},//暎 ying
{2,1272,{pysm::nop,pyym::nop}},//暏 shu
{1,0,{pysm::w,pyym::ei}},//暐 wei
{1,0,{pysm::sh,pyym::u}},//暑 shu
{1,0,{pysm::q,pyym::ing}},//暒 qing
{1,0,{pysm::m,pyym::ao}},//暓 mao
{1,0,{pysm::n,pyym::an}},//暔 nan
{2,1273,{pysm::nop,pyym::nop}},//暕 jian
{2,1274,{pysm::nop,pyym::nop}},//暖 nuan
{1,0,{pysm::nop,pyym::an}},//暗 an
{1,0,{pysm::y,pyym::ang}},//暘 yang
{1,0,{pysm::ch,pyym::un}},//暙 chun
{1,0,{pysm::y,pyym::ao}},//暚 yao
{1,0,{pysm::s,pyym::uo}},//暛 suo
{1,0,{pysm::p,pyym::u}},//暜 pu
{1,0,{pysm::m,pyym::ing}},//暝 ming
{1,0,{pysm::j,pyym::iao}},//暞 jiao
{1,0,{pysm::k,pyym::ai}},//暟 kai
{2,1275,{pysm::nop,pyym::nop}},//暠 gao
{1,0,{pysm::w,pyym::eng}},//暡 weng
{1,0,{pysm::ch,pyym::ang}},//暢 chang
{1,0,{pysm::q,pyym::i}},//暣 qi
{1,0,{pysm::h,pyym::ao}},//暤 hao
{1,0,{pysm::y,pyym::an}},//暥 yan
{1,0,{pysm::l,pyym::i}},//暦 li
{2,1276,{pysm::nop,pyym::nop}},//暧 ai
{2,1277,{pysm::nop,pyym::nop}},//暨 ji
{1,0,{pysm::j,pyym::i}},//暩 ji
{1,0,{pysm::m,pyym::en}},//暪 men
{1,0,{pysm::z,pyym::an}},//暫 zan
{1,0,{pysm::x,pyym::ie}},//暬 xie
{1,0,{pysm::h,pyym::ao}},//暭 hao
{1,0,{pysm::m,pyym::u}},//暮 mu
{1,0,{pysm::m,pyym::o}},//暯 mo
{1,0,{pysm::c,pyym::ong}},//暰 cong
{1,0,{pysm::n,pyym::i}},//暱 ni
{1,0,{pysm::zh,pyym::ang}},//暲 zhang
{1,0,{pysm::h,pyym::ui}},//暳 hui
{3,304,{pysm::nop,pyym::nop}},//暴 bao
{1,0,{pysm::h,pyym::an}},//暵 han
{1,0,{pysm::x,pyym::uan}},//暶 xuan
{1,0,{pysm::ch,pyym::uan}},//暷 chuan
{1,0,{pysm::l,pyym::iao}},//暸 liao
{1,0,{pysm::x,pyym::ian}},//暹 xian
{1,0,{pysm::t,pyym::an}},//暺 tan
{1,0,{pysm::j,pyym::ing}},//暻 jing
{1,0,{pysm::p,pyym::ie}},//暼 pie
{1,0,{pysm::l,pyym::in}},//暽 lin
{1,0,{pysm::t,pyym::un}},//暾 tun
{1,0,{pysm::x,pyym::i}},//暿 xi
{1,0,{pysm::y,pyym::i}},//曀 yi
{1,0,{pysm::j,pyym::i}},//曁 ji
{1,0,{pysm::h,pyym::uang}},//曂 huang
{1,0,{pysm::d,pyym::ai}},//曃 dai
{1,0,{pysm::y,pyym::e}},//曄 ye
{1,0,{pysm::y,pyym::e}},//曅 ye
{1,0,{pysm::l,pyym::i}},//曆 li
{1,0,{pysm::t,pyym::an}},//曇 tan
{1,0,{pysm::t,pyym::ong}},//曈 tong
{1,0,{pysm::x,pyym::iao}},//曉 xiao
{1,0,{pysm::f,pyym::ei}},//曊 fei
{1,0,{pysm::sh,pyym::en}},//曋 shen
{1,0,{pysm::zh,pyym::ao}},//曌 zhao
{1,0,{pysm::h,pyym::ao}},//曍 hao
{1,0,{pysm::y,pyym::i}},//曎 yi
{2,1278,{pysm::nop,pyym::nop}},//曏 xiang
{1,0,{pysm::x,pyym::ing}},//曐 xing
{1,0,{pysm::sh,pyym::en}},//曑 shen
{1,0,{pysm::j,pyym::iao}},//曒 jiao
{1,0,{pysm::b,pyym::ao}},//曓 bao
{1,0,{pysm::j,pyym::ing}},//曔 jing
{1,0,{pysm::y,pyym::an}},//曕 yan
{1,0,{pysm::nop,pyym::ai}},//曖 ai
{1,0,{pysm::y,pyym::e}},//曗 ye
{1,0,{pysm::r,pyym::u}},//曘 ru
{1,0,{pysm::sh,pyym::u}},//曙 shu
{1,0,{pysm::m,pyym::eng}},//曚 meng
{1,0,{pysm::x,pyym::un}},//曛 xun
{1,0,{pysm::y,pyym::ao}},//曜 yao
{2,1279,{pysm::nop,pyym::nop}},//曝 pu
{1,0,{pysm::l,pyym::i}},//曞 li
{1,0,{pysm::ch,pyym::en}},//曟 chen
{1,0,{pysm::k,pyym::uang}},//曠 kuang
{1,0,{pysm::d,pyym::ie}},//曡 die
{1,0,{pysm::l,pyym::iao}},//曢 liao
{1,0,{pysm::y,pyym::an}},//曣 yan
{1,0,{pysm::h,pyym::uo}},//曤 huo
{1,0,{pysm::l,pyym::u}},//曥 lu
{1,0,{pysm::x,pyym::i}},//曦 xi
{1,0,{pysm::r,pyym::ong}},//曧 rong
{1,0,{pysm::l,pyym::ong}},//曨 long
{1,0,{pysm::n,pyym::ang}},//曩 nang
{1,0,{pysm::l,pyym::uo}},//曪 luo
{1,0,{pysm::l,pyym::uan}},//曫 luan
{1,0,{pysm::sh,pyym::ai}},//曬 shai
{1,0,{pysm::t,pyym::ang}},//曭 tang
{1,0,{pysm::y,pyym::an}},//曮 yan
{1,0,{pysm::zh,pyym::u}},//曯 zhu
{1,0,{pysm::y,pyym::ue}},//曰 yue
{1,0,{pysm::y,pyym::ue}},//曱 yue
{1,0,{pysm::q,pyym::u}},//曲 qu
{1,0,{pysm::y,pyym::e}},//曳 ye
{1,0,{pysm::g,pyym::eng}},//更 geng
{1,0,{pysm::y,pyym::e}},//曵 ye
{1,0,{pysm::h,pyym::u}},//曶 hu
{2,1280,{pysm::nop,pyym::nop}},//曷 he
{1,0,{pysm::sh,pyym::u}},//書 shu
{1,0,{pysm::c,pyym::ao}},//曹 cao
{1,0,{pysm::c,pyym::ao}},//曺 cao
{1,0,{pysm::sh,pyym::eng}},//曻 sheng
{1,0,{pysm::m,pyym::an}},//曼 man
{1,0,{pysm::c,pyym::eng}},//曽 ceng
{2,1281,{pysm::nop,pyym::nop}},//曾 ceng
{1,0,{pysm::t,pyym::i}},//替 ti
{2,1282,{pysm::nop,pyym::nop}},//最 zui
{3,305,{pysm::nop,pyym::nop}},//朁 can
{1,0,{pysm::x,pyym::u}},//朂 xu
{3,306,{pysm::nop,pyym::nop}},//會 hui
{1,0,{pysm::y,pyym::in}},//朄 yin
{1,0,{pysm::q,pyym::ie}},//朅 qie
{1,0,{pysm::f,pyym::en}},//朆 fen
{1,0,{pysm::p,pyym::i}},//朇 pi
{2,1283,{pysm::nop,pyym::nop}},//月 yue
{2,1284,{pysm::nop,pyym::nop}},//有 you
{2,1285,{pysm::nop,pyym::nop}},//朊 ruan
{1,0,{pysm::p,pyym::eng}},//朋 peng
{2,1286,{pysm::nop,pyym::nop}},//朌 fen
{3,307,{pysm::nop,pyym::nop}},//服 fu
{1,0,{pysm::l,pyym::ing}},//朎 ling
{2,1287,{pysm::nop,pyym::nop}},//朏 fei
{3,308,{pysm::nop,pyym::nop}},//朐 qu
{1,0,{pysm::t,pyym::i}},//朑 ti
{1,0,{pysm::n,pyym::v}},//朒 nü
{2,1288,{pysm::nop,pyym::nop}},//朓 tiao
{1,0,{pysm::sh,pyym::uo}},//朔 shuo
{1,0,{pysm::zh,pyym::en}},//朕 zhen
{1,0,{pysm::l,pyym::ang}},//朖 lang
{1,0,{pysm::l,pyym::ang}},//朗 lang
{2,1289,{pysm::nop,pyym::nop}},//朘 zui
{1,0,{pysm::m,pyym::ing}},//朙 ming
{4,69,{pysm::nop,pyym::nop}},//朚 huang
{1,0,{pysm::w,pyym::ang}},//望 wang
{1,0,{pysm::t,pyym::un}},//朜 tun
{3,309,{pysm::nop,pyym::nop}},//朝 chao
{2,1290,{pysm::nop,pyym::nop}},//朞 ji
{2,1291,{pysm::nop,pyym::nop}},//期 qi
{1,0,{pysm::y,pyym::ing}},//朠 ying
{1,0,{pysm::z,pyym::ong}},//朡 zong
{1,0,{pysm::w,pyym::ang}},//朢 wang
{2,1292,{pysm::nop,pyym::nop}},//朣 tong
{1,0,{pysm::l,pyym::ang}},//朤 lang
{1,0,{pysm::l,pyym::ao}},//朥 lao
{2,1293,{pysm::nop,pyym::nop}},//朦 meng
{1,0,{pysm::l,pyym::ong}},//朧 long
{1,0,{pysm::m,pyym::u}},//木 mu
{1,0,{pysm::d,pyym::eng}},//朩 deng
{1,0,{pysm::w,pyym::ei}},//未 wei
{2,1294,{pysm::nop,pyym::nop}},//末 mo
{1,0,{pysm::b,pyym::en}},//本 ben
{2,1295,{pysm::nop,pyym::nop}},//札 zha
{2,1296,{pysm::nop,pyym::nop}},//朮 shu
{2,1297,{pysm::nop,pyym::nop}},//术 shu
{1,0,{pysm::m,pyym::u}},//朰 mu
{2,1298,{pysm::nop,pyym::nop}},//朱 zhu
{1,0,{pysm::r,pyym::en}},//朲 ren
{1,0,{pysm::b,pyym::a}},//朳 ba
{3,310,{pysm::nop,pyym::nop}},//朴 pu
{1,0,{pysm::d,pyym::uo}},//朵 duo
{1,0,{pysm::d,pyym::uo}},//朶 duo
{3,311,{pysm::nop,pyym::nop}},//朷 dao
{1,0,{pysm::l,pyym::i}},//朸 li
{2,1299,{pysm::nop,pyym::nop}},//朹 gui
{2,1300,{pysm::nop,pyym::nop}},//机 ji
{1,0,{pysm::j,pyym::iu}},//朻 jiu
{1,0,{pysm::b,pyym::i}},//朼 bi
{1,0,{pysm::x,pyym::iu}},//朽 xiu
{3,312,{pysm::nop,pyym::nop}},//朾 cheng
{1,0,{pysm::c,pyym::i}},//朿 ci
{1,0,{pysm::sh,pyym::a}},//杀 sha
{1,0,{pysm::r,pyym::u}},//杁 ru
{2,1301,{pysm::nop,pyym::nop}},//杂 za
{1,0,{pysm::q,pyym::uan}},//权 quan
{1,0,{pysm::q,pyym::ian}},//杄 qian
{2,1302,{pysm::nop,pyym::nop}},//杅 yu
{1,0,{pysm::g,pyym::an}},//杆 gan
{1,0,{pysm::w,pyym::u}},//杇 wu
{1,0,{pysm::ch,pyym::a}},//杈 cha
{2,1303,{pysm::nop,pyym::nop}},//杉 shan
{1,0,{pysm::x,pyym::un}},//杊 xun
{1,0,{pysm::f,pyym::an}},//杋 fan
{2,1304,{pysm::nop,pyym::nop}},//杌 wu
{1,0,{pysm::z,pyym::i}},//杍 zi
{1,0,{pysm::l,pyym::i}},//李 li
{1,0,{pysm::x,pyym::ing}},//杏 xing
{1,0,{pysm::c,pyym::ai}},//材 cai
{1,0,{pysm::c,pyym::un}},//村 cun
{2,1305,{pysm::nop,pyym::nop}},//杒 ren
{5,24,{pysm::nop,pyym::nop}},//杓 biao
{2,1306,{pysm::nop,pyym::nop}},//杔 tuo
{2,1307,{pysm::nop,pyym::nop}},//杕 di
{1,0,{pysm::zh,pyym::ang}},//杖 zhang
{1,0,{pysm::m,pyym::ang}},//杗 mang
{1,0,{pysm::ch,pyym::i}},//杘 chi
{1,0,{pysm::y,pyym::i}},//杙 yi
{2,1308,{pysm::nop,pyym::nop}},//杚 gai
{1,0,{pysm::g,pyym::ong}},//杛 gong
{2,1309,{pysm::nop,pyym::nop}},//杜 du
{5,25,{pysm::nop,pyym::nop}},//杝 li
{1,0,{pysm::q,pyym::i}},//杞 qi
{1,0,{pysm::sh,pyym::u}},//束 shu
{2,1310,{pysm::nop,pyym::nop}},//杠 gang
{1,0,{pysm::t,pyym::iao}},//条 tiao
{1,0,{pysm::j,pyym::iang}},//杢 jiang
{1,0,{pysm::m,pyym::ian}},//杣 mian
{1,0,{pysm::w,pyym::an}},//杤 wan
{1,0,{pysm::l,pyym::ai}},//来 lai
{1,0,{pysm::j,pyym::iu}},//杦 jiu
{1,0,{pysm::m,pyym::ang}},//杧 mang
{1,0,{pysm::y,pyym::ang}},//杨 yang
{1,0,{pysm::m,pyym::a}},//杩 ma
{1,0,{pysm::m,pyym::iao}},//杪 miao
{3,313,{pysm::nop,pyym::nop}},//杫 si
{1,0,{pysm::y,pyym::uan}},//杬 yuan
{2,1311,{pysm::nop,pyym::nop}},//杭 hang
{2,1312,{pysm::nop,pyym::nop}},//杮 fei
{1,0,{pysm::b,pyym::ei}},//杯 bei
{1,0,{pysm::j,pyym::ie}},//杰 jie
{1,0,{pysm::d,pyym::ong}},//東 dong
{1,0,{pysm::g,pyym::ao}},//杲 gao
{1,0,{pysm::y,pyym::ao}},//杳 yao
{2,1313,{pysm::nop,pyym::nop}},//杴 xian
{1,0,{pysm::ch,pyym::u}},//杵 chu
{1,0,{pysm::ch,pyym::un}},//杶 chun
{2,1314,{pysm::nop,pyym::nop}},//杷 pa
{2,1315,{pysm::nop,pyym::nop}},//杸 shu
{1,0,{pysm::h,pyym::ua}},//杹 hua
{1,0,{pysm::x,pyym::in}},//杺 xin
{2,1316,{pysm::nop,pyym::nop}},//杻 chou
{2,1317,{pysm::nop,pyym::nop}},//杼 zhu
{1,0,{pysm::ch,pyym::ou}},//杽 chou
{1,0,{pysm::s,pyym::ong}},//松 song
{1,0,{pysm::b,pyym::an}},//板 ban
{1,0,{pysm::s,pyym::ong}},//枀 song
{1,0,{pysm::j,pyym::i}},//极 ji
{2,1318,{pysm::nop,pyym::nop}},//枂 wo
{1,0,{pysm::j,pyym::in}},//枃 jin
{1,0,{pysm::g,pyym::ou}},//构 gou
{1,0,{pysm::j,pyym::i}},//枅 ji
{1,0,{pysm::m,pyym::ao}},//枆 mao
{2,1319,{pysm::nop,pyym::nop}},//枇 pi
{2,1320,{pysm::nop,pyym::nop}},//枈 bi
{2,1321,{pysm::nop,pyym::nop}},//枉 wang
{1,0,{pysm::nop,pyym::ang}},//枊 ang
{2,1322,{pysm::nop,pyym::nop}},//枋 fang
{1,0,{pysm::f,pyym::en}},//枌 fen
{1,0,{pysm::y,pyym::i}},//枍 yi
{1,0,{pysm::f,pyym::u}},//枎 fu
{1,0,{pysm::n,pyym::an}},//枏 nan
{2,1323,{pysm::nop,pyym::nop}},//析 xi
{1,0,{pysm::h,pyym::u}},//枑 hu
{2,1324,{pysm::nop,pyym::nop}},//枒 ya
{2,1325,{pysm::nop,pyym::nop}},//枓 dou
{1,0,{pysm::x,pyym::in}},//枔 xin
{2,1326,{pysm::nop,pyym::nop}},//枕 zhen
{1,0,{pysm::y,pyym::ao}},//枖 yao
{1,0,{pysm::l,pyym::in}},//林 lin
{2,1327,{pysm::nop,pyym::nop}},//枘 rui
{1,0,{pysm::nop,pyym::e}},//枙 e
{1,0,{pysm::m,pyym::ei}},//枚 mei
{1,0,{pysm::zh,pyym::ao}},//枛 zhao
{3,314,{pysm::nop,pyym::nop}},//果 guo
{2,1328,{pysm::nop,pyym::nop}},//枝 zhi
{2,1329,{pysm::nop,pyym::nop}},//枞 cong
{1,0,{pysm::y,pyym::un}},//枟 yun
{1,0,{pysm::z,pyym::ui}},//枠 zui
{1,0,{pysm::sh,pyym::eng}},//枡 sheng
{1,0,{pysm::sh,pyym::u}},//枢 shu
{1,0,{pysm::z,pyym::ao}},//枣 zao
{1,0,{pysm::d,pyym::i}},//枤 di
{1,0,{pysm::l,pyym::i}},//枥 li
{1,0,{pysm::l,pyym::u}},//枦 lu
{1,0,{pysm::j,pyym::ian}},//枧 jian
{1,0,{pysm::ch,pyym::eng}},//枨 cheng
{1,0,{pysm::s,pyym::ong}},//枩 song
{1,0,{pysm::q,pyym::iang}},//枪 qiang
{1,0,{pysm::f,pyym::eng}},//枫 feng
{1,0,{pysm::zh,pyym::an}},//枬 zhan
{1,0,{pysm::x,pyym::iao}},//枭 xiao
{2,1330,{pysm::nop,pyym::nop}},//枮 xian
{2,1331,{pysm::nop,pyym::nop}},//枯 ku
{1,0,{pysm::p,pyym::ing}},//枰 ping
{3,315,{pysm::nop,pyym::nop}},//枱 tai
{1,0,{pysm::x,pyym::i}},//枲 xi
{1,0,{pysm::zh,pyym::i}},//枳 zhi
{1,0,{pysm::g,pyym::uai}},//枴 guai
{1,0,{pysm::x,pyym::iao}},//枵 xiao
{1,0,{pysm::j,pyym::ia}},//架 jia
{1,0,{pysm::j,pyym::ia}},//枷 jia
{3,316,{pysm::nop,pyym::nop}},//枸 gou
{2,1332,{pysm::nop,pyym::nop}},//枹 bao
{1,0,{pysm::m,pyym::o}},//枺 mo
{2,1333,{pysm::nop,pyym::nop}},//枻 yi
{1,0,{pysm::y,pyym::e}},//枼 ye
{1,0,{pysm::y,pyym::e}},//枽 ye
{1,0,{pysm::sh,pyym::i}},//枾 shi
{1,0,{pysm::n,pyym::ie}},//枿 nie
{1,0,{pysm::b,pyym::i}},//柀 bi
{2,1334,{pysm::nop,pyym::nop}},//柁 duo
{3,317,{pysm::nop,pyym::nop}},//柂 yi
{1,0,{pysm::l,pyym::ing}},//柃 ling
{1,0,{pysm::b,pyym::ing}},//柄 bing
{2,1335,{pysm::nop,pyym::nop}},//柅 ni
{1,0,{pysm::l,pyym::a}},//柆 la
{1,0,{pysm::h,pyym::e}},//柇 he
{2,1336,{pysm::nop,pyym::nop}},//柈 ban
{1,0,{pysm::f,pyym::an}},//柉 fan
{1,0,{pysm::zh,pyym::ong}},//柊 zhong
{1,0,{pysm::d,pyym::ai}},//柋 dai
{1,0,{pysm::c,pyym::i}},//柌 ci
{2,1337,{pysm::nop,pyym::nop}},//柍 yang
{1,0,{pysm::f,pyym::u}},//柎 fu
{2,1338,{pysm::nop,pyym::nop}},//柏 bai
{2,1339,{pysm::nop,pyym::nop}},//某 mou
{2,1340,{pysm::nop,pyym::nop}},//柑 gan
{1,0,{pysm::q,pyym::i}},//柒 qi
{1,0,{pysm::r,pyym::an}},//染 ran
{1,0,{pysm::r,pyym::ou}},//柔 rou
{1,0,{pysm::m,pyym::ao}},//柕 mao
{1,0,{pysm::sh,pyym::ao}},//柖 shao
{1,0,{pysm::s,pyym::ong}},//柗 song
{1,0,{pysm::zh,pyym::e}},//柘 zhe
{2,1341,{pysm::nop,pyym::nop}},//柙 xia
{2,1342,{pysm::nop,pyym::nop}},//柚 you
{1,0,{pysm::sh,pyym::en}},//柛 shen
{2,1343,{pysm::nop,pyym::nop}},//柜 gui
{1,0,{pysm::t,pyym::uo}},//柝 tuo
{3,318,{pysm::nop,pyym::nop}},//柞 zha
{2,1344,{pysm::nop,pyym::nop}},//柟 nan
{3,319,{pysm::nop,pyym::nop}},//柠 ning
{1,0,{pysm::y,pyym::ong}},//柡 yong
{2,1345,{pysm::nop,pyym::nop}},//柢 di
{2,1346,{pysm::nop,pyym::nop}},//柣 zhi
{2,1347,{pysm::nop,pyym::nop}},//柤 zha
{3,320,{pysm::nop,pyym::nop}},//查 cha
{1,0,{pysm::d,pyym::an}},//柦 dan
{1,0,{pysm::g,pyym::u}},//柧 gu
{2,1348,{pysm::nop,pyym::nop}},//柨 bu
{1,0,{pysm::j,pyym::iu}},//柩 jiu
{1,0,{pysm::nop,pyym::ao}},//柪 ao
{1,0,{pysm::f,pyym::u}},//柫 fu
{1,0,{pysm::j,pyym::ian}},//柬 jian
{5,26,{pysm::nop,pyym::nop}},//柭 ba
{3,321,{pysm::nop,pyym::nop}},//柮 duo
{1,0,{pysm::k,pyym::e}},//柯 ke
{1,0,{pysm::n,pyym::ai}},//柰 nai
{1,0,{pysm::zh,pyym::u}},//柱 zhu
{2,1349,{pysm::nop,pyym::nop}},//柲 bi
{1,0,{pysm::l,pyym::iu}},//柳 liu
{4,70,{pysm::nop,pyym::nop}},//柴 chai
{2,1350,{pysm::nop,pyym::nop}},//柵 shan
{1,0,{pysm::s,pyym::i}},//柶 si
{2,1351,{pysm::nop,pyym::nop}},//柷 chu
{2,1352,{pysm::nop,pyym::nop}},//柸 pei
{2,1353,{pysm::nop,pyym::nop}},//柹 shi
{1,0,{pysm::g,pyym::uai}},//柺 guai
{1,0,{pysm::zh,pyym::a}},//査 zha
{1,0,{pysm::y,pyym::ao}},//柼 yao
{2,1354,{pysm::nop,pyym::nop}},//柽 cheng
{1,0,{pysm::j,pyym::iu}},//柾 jiu
{1,0,{pysm::sh,pyym::i}},//柿 shi
{1,0,{pysm::zh,pyym::i}},//栀 zhi
{1,0,{pysm::l,pyym::iu}},//栁 liu
{1,0,{pysm::m,pyym::ei}},//栂 mei
{1,0,{pysm::l,pyym::i}},//栃 li
{1,0,{pysm::r,pyym::ong}},//栄 rong
{3,322,{pysm::nop,pyym::nop}},//栅 zha
{1,0,{pysm::z,pyym::ao}},//栆 zao
{1,0,{pysm::b,pyym::iao}},//标 biao
{1,0,{pysm::zh,pyym::an}},//栈 zhan
{1,0,{pysm::zh,pyym::i}},//栉 zhi
{1,0,{pysm::l,pyym::ong}},//栊 long
{1,0,{pysm::d,pyym::ong}},//栋 dong
{1,0,{pysm::l,pyym::u}},//栌 lu
{1,0,{pysm::sh,pyym::eng}},//栍 sheng
{2,1355,{pysm::nop,pyym::nop}},//栎 li
{1,0,{pysm::l,pyym::an}},//栏 lan
{1,0,{pysm::y,pyym::ong}},//栐 yong
{1,0,{pysm::sh,pyym::u}},//树 shu
{2,1356,{pysm::nop,pyym::nop}},//栒 xun
{2,1357,{pysm::nop,pyym::nop}},//栓 shuan
{1,0,{pysm::q,pyym::i}},//栔 qi
{1,0,{pysm::zh,pyym::en}},//栕 zhen
{2,1358,{pysm::nop,pyym::nop}},//栖 qi
{2,1359,{pysm::nop,pyym::nop}},//栗 li
{1,0,{pysm::y,pyym::i}},//栘 yi
{1,0,{pysm::x,pyym::iang}},//栙 xiang
{1,0,{pysm::zh,pyym::en}},//栚 zhen
{1,0,{pysm::l,pyym::i}},//栛 li
{2,1360,{pysm::nop,pyym::nop}},//栜 se
{3,323,{pysm::nop,pyym::nop}},//栝 gua
{1,0,{pysm::k,pyym::an}},//栞 kan
{2,1361,{pysm::nop,pyym::nop}},//栟 ben
{1,0,{pysm::r,pyym::en}},//栠 ren
{3,324,{pysm::nop,pyym::nop}},//校 xiao
{1,0,{pysm::b,pyym::ai}},//栢 bai
{1,0,{pysm::r,pyym::en}},//栣 ren
{1,0,{pysm::b,pyym::ing}},//栤 bing
{1,0,{pysm::z,pyym::i}},//栥 zi
{1,0,{pysm::ch,pyym::ou}},//栦 chou
{1,0,{pysm::y,pyym::i}},//栧 yi
{1,0,{pysm::c,pyym::i}},//栨 ci
{2,1362,{pysm::nop,pyym::nop}},//栩 xu
{1,0,{pysm::zh,pyym::u}},//株 zhu
{2,1363,{pysm::nop,pyym::nop}},//栫 jian
{1,0,{pysm::z,pyym::ui}},//栬 zui
{1,0,{pysm::nop,pyym::er}},//栭 er
{1,0,{pysm::nop,pyym::er}},//栮 er
{2,1364,{pysm::nop,pyym::nop}},//栯 you
{1,0,{pysm::f,pyym::a}},//栰 fa
{1,0,{pysm::g,pyym::ong}},//栱 gong
{1,0,{pysm::k,pyym::ao}},//栲 kao
{1,0,{pysm::l,pyym::ao}},//栳 lao
{1,0,{pysm::zh,pyym::an}},//栴 zhan
{1,0,{pysm::l,pyym::ie}},//栵 lie
{1,0,{pysm::y,pyym::in}},//栶 yin
{1,0,{pysm::y,pyym::ang}},//样 yang
{4,71,{pysm::nop,pyym::nop}},//核 he
{1,0,{pysm::g,pyym::en}},//根 gen
{2,1365,{pysm::nop,pyym::nop}},//栺 yi
{1,0,{pysm::sh,pyym::i}},//栻 shi
{3,325,{pysm::nop,pyym::nop}},//格 ge
{1,0,{pysm::z,pyym::ai}},//栽 zai
{1,0,{pysm::l,pyym::uan}},//栾 luan
{1,0,{pysm::f,pyym::u}},//栿 fu
{1,0,{pysm::j,pyym::ie}},//桀 jie
{2,1366,{pysm::nop,pyym::nop}},//桁 heng
{1,0,{pysm::g,pyym::ui}},//桂 gui
{3,326,{pysm::nop,pyym::nop}},//桃 tao
{1,0,{pysm::g,pyym::uang}},//桄 guang
{2,1367,{pysm::nop,pyym::nop}},//桅 wei
{1,0,{pysm::k,pyym::uang}},//框 kuang
{1,0,{pysm::r,pyym::u}},//桇 ru
{1,0,{pysm::nop,pyym::an}},//案 an
{1,0,{pysm::nop,pyym::an}},//桉 an
{2,1368,{pysm::nop,pyym::nop}},//桊 juan
{2,1369,{pysm::nop,pyym::nop}},//桋 yi
{1,0,{pysm::zh,pyym::uo}},//桌 zhuo
{1,0,{pysm::k,pyym::u}},//桍 ku
{1,0,{pysm::zh,pyym::i}},//桎 zhi
{1,0,{pysm::q,pyym::iong}},//桏 qiong
{2,1370,{pysm::nop,pyym::nop}},//桐 tong
{1,0,{pysm::s,pyym::ang}},//桑 sang
{1,0,{pysm::s,pyym::ang}},//桒 sang
{1,0,{pysm::h,pyym::uan}},//桓 huan
{3,327,{pysm::nop,pyym::nop}},//桔 ju
{1,0,{pysm::j,pyym::iu}},//桕 jiu
{1,0,{pysm::x,pyym::ue}},//桖 xue
{1,0,{pysm::d,pyym::uo}},//桗 duo
{1,0,{pysm::zh,pyym::ui}},//桘 zhui
{2,1371,{pysm::nop,pyym::nop}},//桙 yu
{1,0,{pysm::z,pyym::an}},//桚 zan
{0,0,{pysm::nop,pyym::nop}},//桛 桛
{1,0,{pysm::y,pyym::ing}},//桜 ying
{1,0,{pysm::j,pyym::ie}},//桝 jie
{1,0,{pysm::l,pyym::iu}},//桞 liu
{1,0,{pysm::zh,pyym::an}},//桟 zhan
{1,0,{pysm::y,pyym::a}},//桠 ya
{1,0,{pysm::r,pyym::ao}},//桡 rao
{1,0,{pysm::zh,pyym::en}},//桢 zhen
{1,0,{pysm::d,pyym::ang}},//档 dang
{1,0,{pysm::q,pyym::i}},//桤 qi
{1,0,{pysm::q,pyym::iao}},//桥 qiao
{1,0,{pysm::h,pyym::ua}},//桦 hua
{2,1372,{pysm::nop,pyym::nop}},//桧 gui
{1,0,{pysm::j,pyym::iang}},//桨 jiang
{1,0,{pysm::zh,pyym::uang}},//桩 zhuang
{1,0,{pysm::x,pyym::un}},//桪 xun
{1,0,{pysm::s,pyym::uo}},//桫 suo
{1,0,{pysm::sh,pyym::a}},//桬 sha
{2,1373,{pysm::nop,pyym::nop}},//桭 zhen
{1,0,{pysm::b,pyym::ei}},//桮 bei
{2,1374,{pysm::nop,pyym::nop}},//桯 ting
{1,0,{pysm::k,pyym::uo}},//桰 kuo
{1,0,{pysm::j,pyym::ing}},//桱 jing
{2,1375,{pysm::nop,pyym::nop}},//桲 po
{1,0,{pysm::b,pyym::en}},//桳 ben
{1,0,{pysm::f,pyym::u}},//桴 fu
{1,0,{pysm::r,pyym::ui}},//桵 rui
{1,0,{pysm::t,pyym::ong}},//桶 tong
{1,0,{pysm::j,pyym::ue}},//桷 jue
{1,0,{pysm::x,pyym::i}},//桸 xi
{1,0,{pysm::l,pyym::ang}},//桹 lang
{1,0,{pysm::l,pyym::iu}},//桺 liu
{1,0,{pysm::f,pyym::eng}},//桻 feng
{1,0,{pysm::q,pyym::i}},//桼 qi
{1,0,{pysm::w,pyym::en}},//桽 wen
{1,0,{pysm::j,pyym::un}},//桾 jun
{2,1376,{pysm::nop,pyym::nop}},//桿 gan
{2,1377,{pysm::nop,pyym::nop}},//梀 su
{1,0,{pysm::l,pyym::iang}},//梁 liang
{1,0,{pysm::q,pyym::iu}},//梂 qiu
{1,0,{pysm::t,pyym::ing}},//梃 ting
{1,0,{pysm::y,pyym::ou}},//梄 you
{1,0,{pysm::m,pyym::ei}},//梅 mei
{1,0,{pysm::b,pyym::ang}},//梆 bang
{1,0,{pysm::l,pyym::ong}},//梇 long
{1,0,{pysm::p,pyym::eng}},//梈 peng
{1,0,{pysm::zh,pyym::uang}},//梉 zhuang
{1,0,{pysm::d,pyym::i}},//梊 di
{3,328,{pysm::nop,pyym::nop}},//梋 xuan
{2,1378,{pysm::nop,pyym::nop}},//梌 tu
{1,0,{pysm::z,pyym::ao}},//梍 zao
{2,1379,{pysm::nop,pyym::nop}},//梎 ao
{2,1380,{pysm::nop,pyym::nop}},//梏 gu
{1,0,{pysm::b,pyym::i}},//梐 bi
{1,0,{pysm::d,pyym::i}},//梑 di
{1,0,{pysm::h,pyym::an}},//梒 han
{1,0,{pysm::z,pyym::i}},//梓 zi
{1,0,{pysm::zh,pyym::i}},//梔 zhi
{1,0,{pysm::r,pyym::en}},//梕 ren
{1,0,{pysm::b,pyym::ei}},//梖 bei
{1,0,{pysm::g,pyym::eng}},//梗 geng
{2,1381,{pysm::nop,pyym::nop}},//梘 jian
{1,0,{pysm::h,pyym::uan}},//梙 huan
{1,0,{pysm::w,pyym::an}},//梚 wan
{1,0,{pysm::n,pyym::uo}},//梛 nuo
{1,0,{pysm::j,pyym::ia}},//梜 jia
{1,0,{pysm::t,pyym::iao}},//條 tiao
{1,0,{pysm::j,pyym::i}},//梞 ji
{1,0,{pysm::x,pyym::iao}},//梟 xiao
{1,0,{pysm::l,pyym::v}},//梠 lü
{2,1382,{pysm::nop,pyym::nop}},//梡 hun
{3,329,{pysm::nop,pyym::nop}},//梢 shao
{3,330,{pysm::nop,pyym::nop}},//梣 cen
{1,0,{pysm::f,pyym::en}},//梤 fen
{1,0,{pysm::s,pyym::ong}},//梥 song
{1,0,{pysm::m,pyym::eng}},//梦 meng
{2,1383,{pysm::nop,pyym::nop}},//梧 wu
{1,0,{pysm::l,pyym::i}},//梨 li
{3,331,{pysm::nop,pyym::nop}},//梩 li
{1,0,{pysm::d,pyym::ou}},//梪 dou
{1,0,{pysm::q,pyym::in}},//梫 qin
{1,0,{pysm::y,pyym::ing}},//梬 ying
{2,1384,{pysm::nop,pyym::nop}},//梭 suo
{1,0,{pysm::j,pyym::u}},//梮 ju
{1,0,{pysm::t,pyym::i}},//梯 ti
{1,0,{pysm::x,pyym::ie}},//械 xie
{2,1385,{pysm::nop,pyym::nop}},//梱 kun
{1,0,{pysm::zh,pyym::uo}},//梲 zhuo
{1,0,{pysm::sh,pyym::u}},//梳 shu
{1,0,{pysm::ch,pyym::an}},//梴 chan
{1,0,{pysm::f,pyym::an}},//梵 fan
{1,0,{pysm::w,pyym::ei}},//梶 wei
{1,0,{pysm::j,pyym::ing}},//梷 jing
{1,0,{pysm::l,pyym::i}},//梸 li
{2,1386,{pysm::nop,pyym::nop}},//梹 bin
{1,0,{pysm::x,pyym::ia}},//梺 xia
{1,0,{pysm::f,pyym::o}},//梻 fo
{1,0,{pysm::t,pyym::ao}},//梼 tao
{1,0,{pysm::zh,pyym::i}},//梽 zhi
{1,0,{pysm::l,pyym::ai}},//梾 lai
{1,0,{pysm::l,pyym::ian}},//梿 lian
{1,0,{pysm::j,pyym::ian}},//检 jian
{3,332,{pysm::nop,pyym::nop}},//棁 zhuo
{1,0,{pysm::l,pyym::ing}},//棂 ling
{1,0,{pysm::l,pyym::i}},//棃 li
{1,0,{pysm::q,pyym::i}},//棄 qi
{1,0,{pysm::b,pyym::ing}},//棅 bing
{1,0,{pysm::l,pyym::un}},//棆 lun
{2,1387,{pysm::nop,pyym::nop}},//棇 cong
{1,0,{pysm::q,pyym::ian}},//棈 qian
{1,0,{pysm::m,pyym::ian}},//棉 mian
{1,0,{pysm::q,pyym::i}},//棊 qi
{2,1388,{pysm::nop,pyym::nop}},//棋 qi
{1,0,{pysm::c,pyym::ai}},//棌 cai
{3,333,{pysm::nop,pyym::nop}},//棍 gun
{1,0,{pysm::ch,pyym::an}},//棎 chan
{2,1389,{pysm::nop,pyym::nop}},//棏 de
{1,0,{pysm::f,pyym::ei}},//棐 fei
{3,334,{pysm::nop,pyym::nop}},//棑 pai
{1,0,{pysm::b,pyym::ang}},//棒 bang
{4,72,{pysm::nop,pyym::nop}},//棓 bang
{1,0,{pysm::h,pyym::un}},//棔 hun
{1,0,{pysm::z,pyym::ong}},//棕 zong
{2,1390,{pysm::nop,pyym::nop}},//棖 cheng
{1,0,{pysm::z,pyym::ao}},//棗 zao
{1,0,{pysm::j,pyym::i}},//棘 ji
{2,1391,{pysm::nop,pyym::nop}},//棙 li
{1,0,{pysm::p,pyym::eng}},//棚 peng
{1,0,{pysm::y,pyym::u}},//棛 yu
{1,0,{pysm::y,pyym::u}},//棜 yu
{1,0,{pysm::g,pyym::u}},//棝 gu
{1,0,{pysm::j,pyym::un}},//棞 jun
{1,0,{pysm::d,pyym::ong}},//棟 dong
{1,0,{pysm::t,pyym::ang}},//棠 tang
{1,0,{pysm::g,pyym::ang}},//棡 gang
{1,0,{pysm::w,pyym::ang}},//棢 wang
{3,335,{pysm::nop,pyym::nop}},//棣 di
{1,0,{pysm::c,pyym::uo}},//棤 cuo
{1,0,{pysm::f,pyym::an}},//棥 fan
{1,0,{pysm::ch,pyym::eng}},//棦 cheng
{2,1392,{pysm::nop,pyym::nop}},//棧 zhan
{1,0,{pysm::q,pyym::i}},//棨 qi
{1,0,{pysm::y,pyym::uan}},//棩 yuan
{1,0,{pysm::y,pyym::an}},//棪 yan
{1,0,{pysm::y,pyym::u}},//棫 yu
{2,1393,{pysm::nop,pyym::nop}},//棬 quan
{1,0,{pysm::y,pyym::i}},//棭 yi
{1,0,{pysm::s,pyym::en}},//森 sen
{2,1394,{pysm::nop,pyym::nop}},//棯 ren
{2,1395,{pysm::nop,pyym::nop}},//棰 chui
{3,336,{pysm::nop,pyym::nop}},//棱 leng
{2,1396,{pysm::nop,pyym::nop}},//棲 qi
{1,0,{pysm::zh,pyym::uo}},//棳 zhuo
{2,1397,{pysm::nop,pyym::nop}},//棴 fu
{2,1398,{pysm::nop,pyym::nop}},//棵 ke
{1,0,{pysm::l,pyym::ai}},//棶 lai
{2,1399,{pysm::nop,pyym::nop}},//棷 zou
{1,0,{pysm::z,pyym::ou}},//棸 zou
{2,1400,{pysm::nop,pyym::nop}},//棹 zhao
{1,0,{pysm::g,pyym::uan}},//棺 guan
{1,0,{pysm::f,pyym::en}},//棻 fen
{1,0,{pysm::f,pyym::en}},//棼 fen
{2,1401,{pysm::nop,pyym::nop}},//棽 shen
{1,0,{pysm::q,pyym::ing}},//棾 qing
{2,1402,{pysm::nop,pyym::nop}},//棿 ni
{1,0,{pysm::w,pyym::an}},//椀 wan
{1,0,{pysm::g,pyym::uo}},//椁 guo
{1,0,{pysm::l,pyym::u}},//椂 lu
{1,0,{pysm::h,pyym::ao}},//椃 hao
{2,1403,{pysm::nop,pyym::nop}},//椄 jie
{1,0,{pysm::y,pyym::i}},//椅 yi
{3,337,{pysm::nop,pyym::nop}},//椆 chou
{1,0,{pysm::j,pyym::u}},//椇 ju
{1,0,{pysm::j,pyym::u}},//椈 ju
{2,1404,{pysm::nop,pyym::nop}},//椉 cheng
{2,1405,{pysm::nop,pyym::nop}},//椊 zuo
{1,0,{pysm::l,pyym::iang}},//椋 liang
{2,1406,{pysm::nop,pyym::nop}},//椌 qiang
{1,0,{pysm::zh,pyym::i}},//植 zhi
{2,1407,{pysm::nop,pyym::nop}},//椎 chui
{2,1408,{pysm::nop,pyym::nop}},//椏 ya
{1,0,{pysm::j,pyym::u}},//椐 ju
{4,73,{pysm::nop,pyym::nop}},//椑 bei
{1,0,{pysm::j,pyym::iao}},//椒 jiao
{1,0,{pysm::zh,pyym::uo}},//椓 zhuo
{1,0,{pysm::z,pyym::i}},//椔 zi
{1,0,{pysm::b,pyym::in}},//椕 bin
{1,0,{pysm::p,pyym::eng}},//椖 peng
{1,0,{pysm::d,pyym::ing}},//椗 ding
{1,0,{pysm::ch,pyym::u}},//椘 chu
{1,0,{pysm::ch,pyym::ang}},//椙 chang
{1,0,{pysm::m,pyym::en}},//椚 men
{1,0,{pysm::h,pyym::ua}},//椛 hua
{1,0,{pysm::j,pyym::ian}},//検 jian
{1,0,{pysm::g,pyym::ui}},//椝 gui
{1,0,{pysm::x,pyym::i}},//椞 xi
{1,0,{pysm::d,pyym::u}},//椟 du
{1,0,{pysm::q,pyym::ian}},//椠 qian
{1,0,{pysm::d,pyym::ao}},//椡 dao
{1,0,{pysm::g,pyym::ui}},//椢 gui
{1,0,{pysm::d,pyym::ian}},//椣 dian
{1,0,{pysm::l,pyym::uo}},//椤 luo
{1,0,{pysm::zh,pyym::i}},//椥 zhi
{1,0,{pysm::q,pyym::uan}},//椦 quan
{1,0,{pysm::m,pyym::ing}},//椧 ming
{1,0,{pysm::f,pyym::u}},//椨 fu
{1,0,{pysm::g,pyym::eng}},//椩 geng
{1,0,{pysm::p,pyym::eng}},//椪 peng
{1,0,{pysm::sh,pyym::an}},//椫 shan
{1,0,{pysm::y,pyym::i}},//椬 yi
{1,0,{pysm::t,pyym::uo}},//椭 tuo
{1,0,{pysm::s,pyym::en}},//椮 sen
{2,1409,{pysm::nop,pyym::nop}},//椯 duo
{1,0,{pysm::y,pyym::e}},//椰 ye
{1,0,{pysm::f,pyym::u}},//椱 fu
{2,1410,{pysm::nop,pyym::nop}},//椲 wei
{1,0,{pysm::w,pyym::ei}},//椳 wei
{1,0,{pysm::d,pyym::uan}},//椴 duan
{1,0,{pysm::j,pyym::ia}},//椵 jia
{1,0,{pysm::z,pyym::ong}},//椶 zong
{2,1411,{pysm::nop,pyym::nop}},//椷 jian
{1,0,{pysm::y,pyym::i}},//椸 yi
{2,1412,{pysm::nop,pyym::nop}},//椹 shen
{1,0,{pysm::x,pyym::i}},//椺 xi
{2,1413,{pysm::nop,pyym::nop}},//椻 yan
{1,0,{pysm::y,pyym::an}},//椼 yan
{1,0,{pysm::ch,pyym::uan}},//椽 chuan
{2,1414,{pysm::nop,pyym::nop}},//椾 jian
{1,0,{pysm::ch,pyym::un}},//椿 chun
{1,0,{pysm::y,pyym::u}},//楀 yu
{1,0,{pysm::h,pyym::e}},//楁 he
{2,1415,{pysm::nop,pyym::nop}},//楂 zha
{1,0,{pysm::w,pyym::o}},//楃 wo
{1,0,{pysm::p,pyym::ian}},//楄 pian
{1,0,{pysm::b,pyym::i}},//楅 bi
{1,0,{pysm::y,pyym::ao}},//楆 yao
{3,338,{pysm::nop,pyym::nop}},//楇 huo
{1,0,{pysm::x,pyym::u}},//楈 xu
{1,0,{pysm::r,pyym::uo}},//楉 ruo
{1,0,{pysm::y,pyym::ang}},//楊 yang
{1,0,{pysm::l,pyym::a}},//楋 la
{1,0,{pysm::y,pyym::an}},//楌 yan
{1,0,{pysm::b,pyym::en}},//楍 ben
{1,0,{pysm::h,pyym::ui}},//楎 hui
{1,0,{pysm::k,pyym::ui}},//楏 kui
{1,0,{pysm::j,pyym::ie}},//楐 jie
{1,0,{pysm::k,pyym::ui}},//楑 kui
{1,0,{pysm::s,pyym::i}},//楒 si
{2,1416,{pysm::nop,pyym::nop}},//楓 feng
{1,0,{pysm::x,pyym::ie}},//楔 xie
{1,0,{pysm::t,pyym::uo}},//楕 tuo
{2,1417,{pysm::nop,pyym::nop}},//楖 zhi
{1,0,{pysm::j,pyym::ian}},//楗 jian
{1,0,{pysm::m,pyym::u}},//楘 mu
{1,0,{pysm::m,pyym::ao}},//楙 mao
{1,0,{pysm::ch,pyym::u}},//楚 chu
{2,1418,{pysm::nop,pyym::nop}},//楛 hu
{1,0,{pysm::h,pyym::u}},//楜 hu
{1,0,{pysm::l,pyym::ian}},//楝 lian
{1,0,{pysm::l,pyym::eng}},//楞 leng
{1,0,{pysm::t,pyym::ing}},//楟 ting
{1,0,{pysm::n,pyym::an}},//楠 nan
{1,0,{pysm::y,pyym::u}},//楡 yu
{1,0,{pysm::y,pyym::ou}},//楢 you
{1,0,{pysm::m,pyym::ei}},//楣 mei
{2,1419,{pysm::nop,pyym::nop}},//楤 song
{2,1420,{pysm::nop,pyym::nop}},//楥 xuan
{1,0,{pysm::x,pyym::uan}},//楦 xuan
{1,0,{pysm::y,pyym::ang}},//楧 yang
{1,0,{pysm::zh,pyym::en}},//楨 zhen
{1,0,{pysm::p,pyym::ian}},//楩 pian
{2,1421,{pysm::nop,pyym::nop}},//楪 ye
{1,0,{pysm::j,pyym::i}},//楫 ji
{2,1422,{pysm::nop,pyym::nop}},//楬 jie
{1,0,{pysm::y,pyym::e}},//業 ye
{2,1423,{pysm::nop,pyym::nop}},//楮 chu
{3,339,{pysm::nop,pyym::nop}},//楯 dun
{1,0,{pysm::y,pyym::u}},//楰 yu
{2,1424,{pysm::nop,pyym::nop}},//楱 zou
{1,0,{pysm::w,pyym::ei}},//楲 wei
{1,0,{pysm::m,pyym::ei}},//楳 mei
{3,340,{pysm::nop,pyym::nop}},//楴 ti
{1,0,{pysm::j,pyym::i}},//極 ji
{1,0,{pysm::j,pyym::ie}},//楶 jie
{2,1425,{pysm::nop,pyym::nop}},//楷 kai
{1,0,{pysm::q,pyym::iu}},//楸 qiu
{1,0,{pysm::y,pyym::ing}},//楹 ying
{1,0,{pysm::r,pyym::ou}},//楺 rou
{1,0,{pysm::h,pyym::uang}},//楻 huang
{1,0,{pysm::l,pyym::ou}},//楼 lou
{1,0,{pysm::l,pyym::e}},//楽 le
{1,0,{pysm::q,pyym::uan}},//楾 quan
{1,0,{pysm::x,pyym::iang}},//楿 xiang
{1,0,{pysm::p,pyym::in}},//榀 pin
{1,0,{pysm::sh,pyym::i}},//榁 shi
{3,341,{pysm::nop,pyym::nop}},//概 gai
{1,0,{pysm::t,pyym::an}},//榃 tan
{1,0,{pysm::l,pyym::an}},//榄 lan
{2,1426,{pysm::nop,pyym::nop}},//榅 wen
{1,0,{pysm::y,pyym::u}},//榆 yu
{1,0,{pysm::ch,pyym::en}},//榇 chen
{1,0,{pysm::l,pyym::v}},//榈 lü
{1,0,{pysm::j,pyym::u}},//榉 ju
{1,0,{pysm::sh,pyym::en}},//榊 shen
{1,0,{pysm::ch,pyym::u}},//榋 chu
{1,0,{pysm::b,pyym::i}},//榌 bi
{1,0,{pysm::x,pyym::ie}},//榍 xie
{1,0,{pysm::j,pyym::ia}},//榎 jia
{1,0,{pysm::y,pyym::i}},//榏 yi
{4,74,{pysm::nop,pyym::nop}},//榐 zhan
{2,1427,{pysm::nop,pyym::nop}},//榑 fu
{1,0,{pysm::n,pyym::uo}},//榒 nuo
{1,0,{pysm::m,pyym::i}},//榓 mi
{1,0,{pysm::l,pyym::ang}},//榔 lang
{1,0,{pysm::r,pyym::ong}},//榕 rong
{1,0,{pysm::g,pyym::u}},//榖 gu
{2,1428,{pysm::nop,pyym::nop}},//榗 jian
{1,0,{pysm::j,pyym::u}},//榘 ju
{1,0,{pysm::t,pyym::a}},//榙 ta
{1,0,{pysm::y,pyym::ao}},//榚 yao
{1,0,{pysm::zh,pyym::en}},//榛 zhen
{4,75,{pysm::nop,pyym::nop}},//榜 bang
{2,1429,{pysm::nop,pyym::nop}},//榝 sha
{1,0,{pysm::y,pyym::uan}},//榞 yuan
{1,0,{pysm::z,pyym::i}},//榟 zi
{1,0,{pysm::m,pyym::ing}},//榠 ming
{1,0,{pysm::s,pyym::u}},//榡 su
{1,0,{pysm::j,pyym::ia}},//榢 jia
{1,0,{pysm::y,pyym::ao}},//榣 yao
{1,0,{pysm::j,pyym::ie}},//榤 jie
{1,0,{pysm::h,pyym::uang}},//榥 huang
{2,1430,{pysm::nop,pyym::nop}},//榦 gan
{1,0,{pysm::f,pyym::ei}},//榧 fei
{1,0,{pysm::zh,pyym::a}},//榨 zha
{1,0,{pysm::q,pyym::ian}},//榩 qian
{1,0,{pysm::m,pyym::a}},//榪 ma
{1,0,{pysm::s,pyym::un}},//榫 sun
{1,0,{pysm::y,pyym::uan}},//榬 yuan
{1,0,{pysm::x,pyym::ie}},//榭 xie
{1,0,{pysm::r,pyym::ong}},//榮 rong
{1,0,{pysm::sh,pyym::i}},//榯 shi
{1,0,{pysm::zh,pyym::i}},//榰 zhi
{1,0,{pysm::c,pyym::ui}},//榱 cui
{1,0,{pysm::w,pyym::en}},//榲 wen
{1,0,{pysm::t,pyym::ing}},//榳 ting
{1,0,{pysm::l,pyym::iu}},//榴 liu
{1,0,{pysm::r,pyym::ong}},//榵 rong
{1,0,{pysm::t,pyym::ang}},//榶 tang
{1,0,{pysm::q,pyym::ue}},//榷 que
{1,0,{pysm::zh,pyym::ai}},//榸 zhai
{1,0,{pysm::s,pyym::i}},//榹 si
{1,0,{pysm::sh,pyym::eng}},//榺 sheng
{1,0,{pysm::t,pyym::a}},//榻 ta
{1,0,{pysm::k,pyym::e}},//榼 ke
{1,0,{pysm::x,pyym::i}},//榽 xi
{1,0,{pysm::g,pyym::u}},//榾 gu
{1,0,{pysm::q,pyym::i}},//榿 qi
{2,1431,{pysm::nop,pyym::nop}},//槀 gao
{2,1432,{pysm::nop,pyym::nop}},//槁 gao
{1,0,{pysm::s,pyym::un}},//槂 sun
{1,0,{pysm::p,pyym::an}},//槃 pan
{1,0,{pysm::t,pyym::ao}},//槄 tao
{1,0,{pysm::g,pyym::e}},//槅 ge
{1,0,{pysm::ch,pyym::un}},//槆 chun
{2,1433,{pysm::nop,pyym::nop}},//槇 dian
{1,0,{pysm::n,pyym::ou}},//槈 nou
{1,0,{pysm::j,pyym::i}},//槉 ji
{1,0,{pysm::sh,pyym::uo}},//槊 shuo
{2,1434,{pysm::nop,pyym::nop}},//構 gou
{3,342,{pysm::nop,pyym::nop}},//槌 chui
{2,1435,{pysm::nop,pyym::nop}},//槍 qiang
{1,0,{pysm::ch,pyym::a}},//槎 cha
{3,343,{pysm::nop,pyym::nop}},//槏 qian
{1,0,{pysm::h,pyym::uai}},//槐 huai
{1,0,{pysm::m,pyym::ei}},//槑 mei
{1,0,{pysm::x,pyym::u}},//槒 xu
{1,0,{pysm::g,pyym::ang}},//槓 gang
{1,0,{pysm::g,pyym::ao}},//槔 gao
{1,0,{pysm::zh,pyym::uo}},//槕 zhuo
{1,0,{pysm::t,pyym::uo}},//槖 tuo
{1,0,{pysm::q,pyym::iao}},//槗 qiao
{1,0,{pysm::y,pyym::ang}},//様 yang
{1,0,{pysm::d,pyym::ian}},//槙 dian
{1,0,{pysm::j,pyym::ia}},//槚 jia
{2,1436,{pysm::nop,pyym::nop}},//槛 kan
{1,0,{pysm::z,pyym::ui}},//槜 zui
{1,0,{pysm::d,pyym::ao}},//槝 dao
{1,0,{pysm::l,pyym::ong}},//槞 long
{2,1437,{pysm::nop,pyym::nop}},//槟 bin
{1,0,{pysm::zh,pyym::u}},//槠 zhu
{1,0,{pysm::s,pyym::ang}},//槡 sang
{2,1438,{pysm::nop,pyym::nop}},//槢 xi
{2,1439,{pysm::nop,pyym::nop}},//槣 ji
{1,0,{pysm::l,pyym::ian}},//槤 lian
{1,0,{pysm::h,pyym::ui}},//槥 hui
{1,0,{pysm::y,pyym::ong}},//槦 yong
{1,0,{pysm::q,pyym::ian}},//槧 qian
{1,0,{pysm::g,pyym::uo}},//槨 guo
{1,0,{pysm::g,pyym::ai}},//槩 gai
{1,0,{pysm::g,pyym::ai}},//槪 gai
{3,344,{pysm::nop,pyym::nop}},//槫 tuan
{1,0,{pysm::h,pyym::ua}},//槬 hua
{3,345,{pysm::nop,pyym::nop}},//槭 qi
{2,1440,{pysm::nop,pyym::nop}},//槮 sen
{2,1441,{pysm::nop,pyym::nop}},//槯 cui
{1,0,{pysm::p,pyym::eng}},//槰 peng
{2,1442,{pysm::nop,pyym::nop}},//槱 you
{1,0,{pysm::h,pyym::u}},//槲 hu
{1,0,{pysm::j,pyym::iang}},//槳 jiang
{1,0,{pysm::h,pyym::u}},//槴 hu
{1,0,{pysm::h,pyym::uan}},//槵 huan
{1,0,{pysm::g,pyym::ui}},//槶 gui
{3,346,{pysm::nop,pyym::nop}},//槷 nie
{1,0,{pysm::y,pyym::i}},//槸 yi
{1,0,{pysm::g,pyym::ao}},//槹 gao
{1,0,{pysm::k,pyym::ang}},//槺 kang
{1,0,{pysm::g,pyym::ui}},//槻 gui
{1,0,{pysm::g,pyym::ui}},//槼 gui
{2,1443,{pysm::nop,pyym::nop}},//槽 cao
{2,1444,{pysm::nop,pyym::nop}},//槾 man
{2,1445,{pysm::nop,pyym::nop}},//槿 jin
{3,347,{pysm::nop,pyym::nop}},//樀 di
{2,1446,{pysm::nop,pyym::nop}},//樁 zhuang
{5,27,{pysm::nop,pyym::nop}},//樂 le
{1,0,{pysm::l,pyym::ang}},//樃 lang
{1,0,{pysm::ch,pyym::en}},//樄 chen
{2,1447,{pysm::nop,pyym::nop}},//樅 cong
{2,1448,{pysm::nop,pyym::nop}},//樆 li
{1,0,{pysm::x,pyym::iu}},//樇 xiu
{1,0,{pysm::q,pyym::ing}},//樈 qing
{1,0,{pysm::sh,pyym::uang}},//樉 shuang
{1,0,{pysm::f,pyym::an}},//樊 fan
{1,0,{pysm::t,pyym::ong}},//樋 tong
{1,0,{pysm::g,pyym::uan}},//樌 guan
{1,0,{pysm::z,pyym::e}},//樍 ze
{1,0,{pysm::s,pyym::u}},//樎 su
{1,0,{pysm::l,pyym::ei}},//樏 lei
{1,0,{pysm::l,pyym::u}},//樐 lu
{1,0,{pysm::l,pyym::iang}},//樑 liang
{1,0,{pysm::m,pyym::i}},//樒 mi
{2,1449,{pysm::nop,pyym::nop}},//樓 lou
{2,1450,{pysm::nop,pyym::nop}},//樔 chao
{1,0,{pysm::s,pyym::u}},//樕 su
{1,0,{pysm::k,pyym::e}},//樖 ke
{1,0,{pysm::ch,pyym::u}},//樗 chu
{2,1451,{pysm::nop,pyym::nop}},//樘 tang
{1,0,{pysm::b,pyym::iao}},//標 biao
{2,1452,{pysm::nop,pyym::nop}},//樚 lu
{2,1453,{pysm::nop,pyym::nop}},//樛 jiu
{1,0,{pysm::zh,pyym::e}},//樜 zhe
{1,0,{pysm::zh,pyym::a}},//樝 zha
{2,1454,{pysm::nop,pyym::nop}},//樞 shu
{1,0,{pysm::zh,pyym::ang}},//樟 zhang
{2,1455,{pysm::nop,pyym::nop}},//樠 man
{2,1456,{pysm::nop,pyym::nop}},//模 mo
{2,1457,{pysm::nop,pyym::nop}},//樢 niao
{2,1458,{pysm::nop,pyym::nop}},//樣 yang
{1,0,{pysm::t,pyym::iao}},//樤 tiao
{1,0,{pysm::p,pyym::eng}},//樥 peng
{1,0,{pysm::zh,pyym::u}},//樦 zhu
{1,0,{pysm::sh,pyym::a}},//樧 sha
{1,0,{pysm::x,pyym::i}},//樨 xi
{1,0,{pysm::q,pyym::uan}},//権 quan
{3,348,{pysm::nop,pyym::nop}},//横 heng
{1,0,{pysm::j,pyym::ian}},//樫 jian
{1,0,{pysm::c,pyym::ong}},//樬 cong
{1,0,{pysm::j,pyym::i}},//樭 ji
{1,0,{pysm::y,pyym::an}},//樮 yan
{1,0,{pysm::q,pyym::iang}},//樯 qiang
{1,0,{pysm::x,pyym::ue}},//樰 xue
{1,0,{pysm::y,pyym::ing}},//樱 ying
{2,1459,{pysm::nop,pyym::nop}},//樲 er
{1,0,{pysm::x,pyym::un}},//樳 xun
{2,1460,{pysm::nop,pyym::nop}},//樴 zhi
{1,0,{pysm::q,pyym::iao}},//樵 qiao
{1,0,{pysm::z,pyym::ui}},//樶 zui
{1,0,{pysm::c,pyym::ong}},//樷 cong
{1,0,{pysm::p,pyym::u}},//樸 pu
{1,0,{pysm::sh,pyym::u}},//樹 shu
{1,0,{pysm::h,pyym::ua}},//樺 hua
{1,0,{pysm::k,pyym::ui}},//樻 kui
{1,0,{pysm::zh,pyym::en}},//樼 zhen
{1,0,{pysm::z,pyym::un}},//樽 zun
{1,0,{pysm::y,pyym::ue}},//樾 yue
{1,0,{pysm::sh,pyym::an}},//樿 shan
{1,0,{pysm::x,pyym::i}},//橀 xi
{1,0,{pysm::ch,pyym::un}},//橁 chun
{1,0,{pysm::d,pyym::ian}},//橂 dian
{2,1461,{pysm::nop,pyym::nop}},//橃 fa
{1,0,{pysm::g,pyym::an}},//橄 gan
{1,0,{pysm::m,pyym::o}},//橅 mo
{1,0,{pysm::w,pyym::u}},//橆 wu
{1,0,{pysm::q,pyym::iao}},//橇 qiao
{2,1462,{pysm::nop,pyym::nop}},//橈 rao
{1,0,{pysm::l,pyym::in}},//橉 lin
{1,0,{pysm::l,pyym::iu}},//橊 liu
{2,1463,{pysm::nop,pyym::nop}},//橋 qiao
{1,0,{pysm::x,pyym::ian}},//橌 xian
{1,0,{pysm::r,pyym::un}},//橍 run
{1,0,{pysm::f,pyym::an}},//橎 fan
{2,1464,{pysm::nop,pyym::nop}},//橏 zhan
{3,349,{pysm::nop,pyym::nop}},//橐 tuo
{2,1465,{pysm::nop,pyym::nop}},//橑 lao
{1,0,{pysm::y,pyym::un}},//橒 yun
{1,0,{pysm::sh,pyym::un}},//橓 shun
{2,1466,{pysm::nop,pyym::nop}},//橔 dun
{1,0,{pysm::ch,pyym::eng}},//橕 cheng
{2,1467,{pysm::nop,pyym::nop}},//橖 tang
{1,0,{pysm::m,pyym::eng}},//橗 meng
{1,0,{pysm::j,pyym::u}},//橘 ju
{3,350,{pysm::nop,pyym::nop}},//橙 cheng
{3,351,{pysm::nop,pyym::nop}},//橚 su
{1,0,{pysm::j,pyym::ue}},//橛 jue
{1,0,{pysm::j,pyym::ue}},//橜 jue
{3,352,{pysm::nop,pyym::nop}},//橝 dian
{1,0,{pysm::h,pyym::ui}},//橞 hui
{1,0,{pysm::j,pyym::i}},//機 ji
{1,0,{pysm::n,pyym::uo}},//橠 nuo
{1,0,{pysm::x,pyym::iang}},//橡 xiang
{2,1468,{pysm::nop,pyym::nop}},//橢 tuo
{1,0,{pysm::n,pyym::ing}},//橣 ning
{1,0,{pysm::r,pyym::ui}},//橤 rui
{1,0,{pysm::zh,pyym::u}},//橥 zhu
{4,76,{pysm::nop,pyym::nop}},//橦 tong
{2,1469,{pysm::nop,pyym::nop}},//橧 zeng
{2,1470,{pysm::nop,pyym::nop}},//橨 fen
{1,0,{pysm::q,pyym::iong}},//橩 qiong
{2,1471,{pysm::nop,pyym::nop}},//橪 ran
{1,0,{pysm::h,pyym::eng}},//橫 heng
{2,1472,{pysm::nop,pyym::nop}},//橬 qian
{1,0,{pysm::g,pyym::u}},//橭 gu
{1,0,{pysm::l,pyym::iu}},//橮 liu
{1,0,{pysm::l,pyym::ao}},//橯 lao
{1,0,{pysm::g,pyym::ao}},//橰 gao
{1,0,{pysm::ch,pyym::u}},//橱 chu
{1,0,{pysm::x,pyym::i}},//橲 xi
{1,0,{pysm::sh,pyym::eng}},//橳 sheng
{1,0,{pysm::z,pyym::i}},//橴 zi
{1,0,{pysm::s,pyym::an}},//橵 san
{1,0,{pysm::j,pyym::i}},//橶 ji
{1,0,{pysm::d,pyym::ou}},//橷 dou
{1,0,{pysm::j,pyym::ing}},//橸 jing
{1,0,{pysm::l,pyym::u}},//橹 lu
{1,0,{pysm::j,pyym::ian}},//橺 jian
{1,0,{pysm::ch,pyym::u}},//橻 chu
{1,0,{pysm::y,pyym::uan}},//橼 yuan
{1,0,{pysm::t,pyym::a}},//橽 ta
{3,353,{pysm::nop,pyym::nop}},//橾 shu
{1,0,{pysm::j,pyym::iang}},//橿 jiang
{2,1473,{pysm::nop,pyym::nop}},//檀 tan
{1,0,{pysm::l,pyym::in}},//檁 lin
{1,0,{pysm::n,pyym::ong}},//檂 nong
{1,0,{pysm::y,pyym::in}},//檃 yin
{1,0,{pysm::x,pyym::i}},//檄 xi
{1,0,{pysm::h,pyym::ui}},//檅 hui
{1,0,{pysm::sh,pyym::an}},//檆 shan
{1,0,{pysm::z,pyym::ui}},//檇 zui
{1,0,{pysm::x,pyym::uan}},//檈 xuan
{1,0,{pysm::ch,pyym::eng}},//檉 cheng
{1,0,{pysm::g,pyym::an}},//檊 gan
{1,0,{pysm::j,pyym::u}},//檋 ju
{1,0,{pysm::z,pyym::ui}},//檌 zui
{1,0,{pysm::y,pyym::i}},//檍 yi
{1,0,{pysm::q,pyym::in}},//檎 qin
{1,0,{pysm::p,pyym::u}},//檏 pu
{2,1474,{pysm::nop,pyym::nop}},//檐 yan
{1,0,{pysm::l,pyym::ei}},//檑 lei
{1,0,{pysm::f,pyym::eng}},//檒 feng
{1,0,{pysm::h,pyym::ui}},//檓 hui
{1,0,{pysm::d,pyym::ang}},//檔 dang
{1,0,{pysm::j,pyym::i}},//檕 ji
{1,0,{pysm::s,pyym::ui}},//檖 sui
{2,1475,{pysm::nop,pyym::nop}},//檗 bo
{2,1476,{pysm::nop,pyym::nop}},//檘 ping
{1,0,{pysm::ch,pyym::eng}},//檙 cheng
{1,0,{pysm::ch,pyym::u}},//檚 chu
{1,0,{pysm::zh,pyym::ua}},//檛 zhua
{3,354,{pysm::nop,pyym::nop}},//檜 gui
{1,0,{pysm::j,pyym::i}},//檝 ji
{2,1477,{pysm::nop,pyym::nop}},//檞 jie
{1,0,{pysm::j,pyym::ia}},//檟 jia
{2,1478,{pysm::nop,pyym::nop}},//檠 qing
{3,355,{pysm::nop,pyym::nop}},//檡 zhai
{1,0,{pysm::j,pyym::ian}},//檢 jian
{1,0,{pysm::q,pyym::iang}},//檣 qiang
{1,0,{pysm::d,pyym::ao}},//檤 dao
{1,0,{pysm::y,pyym::i}},//檥 yi
{1,0,{pysm::b,pyym::iao}},//檦 biao
{1,0,{pysm::s,pyym::ong}},//檧 song
{1,0,{pysm::sh,pyym::e}},//檨 she
{1,0,{pysm::l,pyym::in}},//檩 lin
{1,0,{pysm::l,pyym::i}},//檪 li
{2,1479,{pysm::nop,pyym::nop}},//檫 cha
{1,0,{pysm::m,pyym::eng}},//檬 meng
{1,0,{pysm::y,pyym::in}},//檭 yin
{3,356,{pysm::nop,pyym::nop}},//檮 tao
{1,0,{pysm::t,pyym::ai}},//檯 tai
{1,0,{pysm::m,pyym::ian}},//檰 mian
{1,0,{pysm::q,pyym::i}},//檱 qi
{1,0,{pysm::t,pyym::uan}},//檲 tuan
{2,1480,{pysm::nop,pyym::nop}},//檳 bin
{2,1481,{pysm::nop,pyym::nop}},//檴 huo
{1,0,{pysm::j,pyym::i}},//檵 ji
{1,0,{pysm::q,pyym::ian}},//檶 qian
{2,1482,{pysm::nop,pyym::nop}},//檷 ni
{1,0,{pysm::n,pyym::ing}},//檸 ning
{1,0,{pysm::y,pyym::i}},//檹 yi
{1,0,{pysm::g,pyym::ao}},//檺 gao
{2,1483,{pysm::nop,pyym::nop}},//檻 kan
{1,0,{pysm::y,pyym::in}},//檼 yin
{3,357,{pysm::nop,pyym::nop}},//檽 nou
{1,0,{pysm::q,pyym::ing}},//檾 qing
{1,0,{pysm::y,pyym::an}},//檿 yan
{1,0,{pysm::q,pyym::i}},//櫀 qi
{1,0,{pysm::m,pyym::i}},//櫁 mi
{2,1484,{pysm::nop,pyym::nop}},//櫂 zhao
{1,0,{pysm::g,pyym::ui}},//櫃 gui
{1,0,{pysm::ch,pyym::un}},//櫄 chun
{1,0,{pysm::j,pyym::i}},//櫅 ji
{1,0,{pysm::k,pyym::ui}},//櫆 kui
{1,0,{pysm::p,pyym::o}},//櫇 po
{1,0,{pysm::d,pyym::eng}},//櫈 deng
{1,0,{pysm::ch,pyym::u}},//櫉 chu
{1,0,{pysm::g,pyym::e}},//櫊 ge
{1,0,{pysm::m,pyym::ian}},//櫋 mian
{1,0,{pysm::y,pyym::ou}},//櫌 you
{1,0,{pysm::zh,pyym::i}},//櫍 zhi
{4,77,{pysm::nop,pyym::nop}},//櫎 huang
{1,0,{pysm::q,pyym::ian}},//櫏 qian
{1,0,{pysm::l,pyym::ei}},//櫐 lei
{1,0,{pysm::l,pyym::ei}},//櫑 lei
{1,0,{pysm::s,pyym::a}},//櫒 sa
{1,0,{pysm::l,pyym::u}},//櫓 lu
{1,0,{pysm::l,pyym::i}},//櫔 li
{1,0,{pysm::c,pyym::uan}},//櫕 cuan
{2,1485,{pysm::nop,pyym::nop}},//櫖 lü
{2,1486,{pysm::nop,pyym::nop}},//櫗 mie
{1,0,{pysm::h,pyym::ui}},//櫘 hui
{1,0,{pysm::nop,pyym::ou}},//櫙 ou
{1,0,{pysm::l,pyym::v}},//櫚 lü
{1,0,{pysm::zh,pyym::i}},//櫛 zhi
{1,0,{pysm::g,pyym::ao}},//櫜 gao
{1,0,{pysm::d,pyym::u}},//櫝 du
{1,0,{pysm::y,pyym::uan}},//櫞 yuan
{3,358,{pysm::nop,pyym::nop}},//櫟 li
{1,0,{pysm::f,pyym::ei}},//櫠 fei
{2,1487,{pysm::nop,pyym::nop}},//櫡 zhuo
{1,0,{pysm::s,pyym::ou}},//櫢 sou
{1,0,{pysm::l,pyym::ian}},//櫣 lian
{1,0,{pysm::j,pyym::iang}},//櫤 jiang
{1,0,{pysm::ch,pyym::u}},//櫥 chu
{1,0,{pysm::q,pyym::ing}},//櫦 qing
{1,0,{pysm::zh,pyym::u}},//櫧 zhu
{2,1488,{pysm::nop,pyym::nop}},//櫨 lu
{1,0,{pysm::y,pyym::an}},//櫩 yan
{1,0,{pysm::l,pyym::i}},//櫪 li
{1,0,{pysm::zh,pyym::u}},//櫫 zhu
{3,359,{pysm::nop,pyym::nop}},//櫬 chen
{2,1489,{pysm::nop,pyym::nop}},//櫭 jie
{1,0,{pysm::nop,pyym::e}},//櫮 e
{1,0,{pysm::s,pyym::u}},//櫯 su
{2,1490,{pysm::nop,pyym::nop}},//櫰 huai
{1,0,{pysm::n,pyym::ie}},//櫱 nie
{1,0,{pysm::y,pyym::u}},//櫲 yu
{1,0,{pysm::l,pyym::ong}},//櫳 long
{1,0,{pysm::l,pyym::ai}},//櫴 lai
{1,0,{pysm::j,pyym::iao}},//櫵 jiao
{1,0,{pysm::x,pyym::ian}},//櫶 xian
{1,0,{pysm::g,pyym::ui}},//櫷 gui
{1,0,{pysm::j,pyym::u}},//櫸 ju
{3,360,{pysm::nop,pyym::nop}},//櫹 xiao
{1,0,{pysm::l,pyym::ing}},//櫺 ling
{1,0,{pysm::y,pyym::ing}},//櫻 ying
{2,1491,{pysm::nop,pyym::nop}},//櫼 jian
{1,0,{pysm::y,pyym::in}},//櫽 yin
{1,0,{pysm::y,pyym::ou}},//櫾 you
{1,0,{pysm::y,pyym::ing}},//櫿 ying
{2,1492,{pysm::nop,pyym::nop}},//欀 xiang
{1,0,{pysm::n,pyym::ong}},//欁 nong
{1,0,{pysm::b,pyym::o}},//欂 bo
{2,1493,{pysm::nop,pyym::nop}},//欃 chan
{2,1494,{pysm::nop,pyym::nop}},//欄 lan
{1,0,{pysm::j,pyym::u}},//欅 ju
{1,0,{pysm::sh,pyym::uang}},//欆 shuang
{1,0,{pysm::sh,pyym::e}},//欇 she
{2,1495,{pysm::nop,pyym::nop}},//欈 wei
{1,0,{pysm::c,pyym::ong}},//欉 cong
{2,1496,{pysm::nop,pyym::nop}},//權 quan
{1,0,{pysm::q,pyym::u}},//欋 qu
{1,0,{pysm::c,pyym::ang}},//欌 cang
{1,0,{pysm::j,pyym::iu}},//欍 jiu
{1,0,{pysm::y,pyym::u}},//欎 yu
{1,0,{pysm::l,pyym::uo}},//欏 luo
{1,0,{pysm::l,pyym::i}},//欐 li
{2,1497,{pysm::nop,pyym::nop}},//欑 cuan
{1,0,{pysm::l,pyym::uan}},//欒 luan
{2,1498,{pysm::nop,pyym::nop}},//欓 dang
{1,0,{pysm::j,pyym::ue}},//欔 jue
{1,0,{pysm::y,pyym::an}},//欕 yan
{1,0,{pysm::l,pyym::an}},//欖 lan
{1,0,{pysm::l,pyym::an}},//欗 lan
{1,0,{pysm::zh,pyym::u}},//欘 zhu
{2,1499,{pysm::nop,pyym::nop}},//欙 lei
{1,0,{pysm::l,pyym::i}},//欚 li
{1,0,{pysm::b,pyym::a}},//欛 ba
{1,0,{pysm::n,pyym::ang}},//欜 nang
{1,0,{pysm::y,pyym::u}},//欝 yu
{1,0,{pysm::l,pyym::ing}},//欞 ling
{1,0,{pysm::g,pyym::uang}},//欟 guang
{1,0,{pysm::q,pyym::ian}},//欠 qian
{2,1500,{pysm::nop,pyym::nop}},//次 ci
{1,0,{pysm::h,pyym::uan}},//欢 huan
{1,0,{pysm::x,pyym::in}},//欣 xin
{1,0,{pysm::y,pyym::u}},//欤 yu
{3,361,{pysm::nop,pyym::nop}},//欥 yi
{3,362,{pysm::nop,pyym::nop}},//欦 qian
{1,0,{pysm::nop,pyym::ou}},//欧 ou
{1,0,{pysm::x,pyym::u}},//欨 xu
{1,0,{pysm::ch,pyym::ao}},//欩 chao
{3,363,{pysm::nop,pyym::nop}},//欪 chu
{1,0,{pysm::q,pyym::i}},//欫 qi
{2,1501,{pysm::nop,pyym::nop}},//欬 kai
{2,1502,{pysm::nop,pyym::nop}},//欭 yi
{1,0,{pysm::j,pyym::ue}},//欮 jue
{2,1503,{pysm::nop,pyym::nop}},//欯 xi
{1,0,{pysm::x,pyym::u}},//欰 xu
{2,1504,{pysm::nop,pyym::nop}},//欱 he
{1,0,{pysm::y,pyym::u}},//欲 yu
{1,0,{pysm::k,pyym::ui}},//欳 kui
{1,0,{pysm::l,pyym::ang}},//欴 lang
{1,0,{pysm::k,pyym::uan}},//欵 kuan
{2,1505,{pysm::nop,pyym::nop}},//欶 shuo
{1,0,{pysm::x,pyym::i}},//欷 xi
{4,78,{pysm::nop,pyym::nop}},//欸 ai
{2,1506,{pysm::nop,pyym::nop}},//欹 yi
{1,0,{pysm::q,pyym::i}},//欺 qi
{2,1507,{pysm::nop,pyym::nop}},//欻 chua
{2,1508,{pysm::nop,pyym::nop}},//欼 chi
{2,1509,{pysm::nop,pyym::nop}},//欽 qin
{2,1510,{pysm::nop,pyym::nop}},//款 kuan
{3,364,{pysm::nop,pyym::nop}},//欿 kan
{1,0,{pysm::k,pyym::uan}},//歀 kuan
{3,365,{pysm::nop,pyym::nop}},//歁 kan
{1,0,{pysm::ch,pyym::uan}},//歂 chuan
{2,1511,{pysm::nop,pyym::nop}},//歃 sha
{1,0,{pysm::g,pyym::ua}},//歄 gua
{1,0,{pysm::y,pyym::in}},//歅 yin
{1,0,{pysm::x,pyym::in}},//歆 xin
{2,1512,{pysm::nop,pyym::nop}},//歇 xie
{1,0,{pysm::y,pyym::u}},//歈 yu
{1,0,{pysm::q,pyym::ian}},//歉 qian
{1,0,{pysm::x,pyym::iao}},//歊 xiao
{1,0,{pysm::y,pyym::e}},//歋 ye
{1,0,{pysm::g,pyym::e}},//歌 ge
{2,1513,{pysm::nop,pyym::nop}},//歍 wu
{1,0,{pysm::t,pyym::an}},//歎 tan
{2,1514,{pysm::nop,pyym::nop}},//歏 jin
{1,0,{pysm::nop,pyym::ou}},//歐 ou
{1,0,{pysm::h,pyym::u}},//歑 hu
{2,1515,{pysm::nop,pyym::nop}},//歒 ti
{1,0,{pysm::h,pyym::uan}},//歓 huan
{1,0,{pysm::x,pyym::u}},//歔 xu
{1,0,{pysm::p,pyym::en}},//歕 pen
{2,1516,{pysm::nop,pyym::nop}},//歖 xi
{1,0,{pysm::x,pyym::iao}},//歗 xiao
{2,1517,{pysm::nop,pyym::nop}},//歘 chua
{3,366,{pysm::nop,pyym::nop}},//歙 she
{1,0,{pysm::sh,pyym::an}},//歚 shan
{2,1518,{pysm::nop,pyym::nop}},//歛 han
{1,0,{pysm::ch,pyym::u}},//歜 chu
{1,0,{pysm::y,pyym::i}},//歝 yi
{1,0,{pysm::nop,pyym::e}},//歞 e
{1,0,{pysm::y,pyym::u}},//歟 yu
{1,0,{pysm::ch,pyym::uo}},//歠 chuo
{1,0,{pysm::h,pyym::uan}},//歡 huan
{1,0,{pysm::zh,pyym::i}},//止 zhi
{1,0,{pysm::zh,pyym::eng}},//正 zheng
{1,0,{pysm::c,pyym::i}},//此 ci
{1,0,{pysm::b,pyym::u}},//步 bu
{1,0,{pysm::w,pyym::u}},//武 wu
{1,0,{pysm::q,pyym::i}},//歧 qi
{1,0,{pysm::b,pyym::u}},//歨 bu
{1,0,{pysm::b,pyym::u}},//歩 bu
{1,0,{pysm::w,pyym::ai}},//歪 wai
{1,0,{pysm::j,pyym::u}},//歫 ju
{1,0,{pysm::q,pyym::ian}},//歬 qian
{2,1519,{pysm::nop,pyym::nop}},//歭 chi
{1,0,{pysm::s,pyym::e}},//歮 se
{1,0,{pysm::ch,pyym::i}},//歯 chi
{2,1520,{pysm::nop,pyym::nop}},//歰 se
{1,0,{pysm::zh,pyym::ong}},//歱 zhong
{2,1521,{pysm::nop,pyym::nop}},//歲 sui
{1,0,{pysm::s,pyym::ui}},//歳 sui
{1,0,{pysm::l,pyym::i}},//歴 li
{1,0,{pysm::z,pyym::e}},//歵 ze
{1,0,{pysm::y,pyym::u}},//歶 yu
{1,0,{pysm::l,pyym::i}},//歷 li
{2,1522,{pysm::nop,pyym::nop}},//歸 gui
{2,1523,{pysm::nop,pyym::nop}},//歹 dai
{1,0,{pysm::nop,pyym::e}},//歺 e
{1,0,{pysm::s,pyym::i}},//死 si
{1,0,{pysm::j,pyym::ian}},//歼 jian
{1,0,{pysm::zh,pyym::e}},//歽 zhe
{2,1524,{pysm::nop,pyym::nop}},//歾 mo
{1,0,{pysm::m,pyym::o}},//歿 mo
{1,0,{pysm::y,pyym::ao}},//殀 yao
{2,1525,{pysm::nop,pyym::nop}},//殁 mo
{1,0,{pysm::c,pyym::u}},//殂 cu
{1,0,{pysm::y,pyym::ang}},//殃 yang
{1,0,{pysm::t,pyym::ian}},//殄 tian
{1,0,{pysm::sh,pyym::eng}},//殅 sheng
{1,0,{pysm::d,pyym::ai}},//殆 dai
{1,0,{pysm::sh,pyym::ang}},//殇 shang
{1,0,{pysm::x,pyym::u}},//殈 xu
{1,0,{pysm::x,pyym::un}},//殉 xun
{1,0,{pysm::sh,pyym::u}},//殊 shu
{1,0,{pysm::c,pyym::an}},//残 can
{1,0,{pysm::j,pyym::ue}},//殌 jue
{2,1526,{pysm::nop,pyym::nop}},//殍 piao
{1,0,{pysm::q,pyym::ia}},//殎 qia
{1,0,{pysm::q,pyym::iu}},//殏 qiu
{1,0,{pysm::s,pyym::u}},//殐 su
{2,1527,{pysm::nop,pyym::nop}},//殑 qing
{1,0,{pysm::y,pyym::un}},//殒 yun
{1,0,{pysm::l,pyym::ian}},//殓 lian
{1,0,{pysm::y,pyym::i}},//殔 yi
{3,367,{pysm::nop,pyym::nop}},//殕 fou
{2,1528,{pysm::nop,pyym::nop}},//殖 zhi
{2,1529,{pysm::nop,pyym::nop}},//殗 ye
{1,0,{pysm::c,pyym::an}},//殘 can
{2,1530,{pysm::nop,pyym::nop}},//殙 hun
{1,0,{pysm::d,pyym::an}},//殚 dan
{1,0,{pysm::j,pyym::i}},//殛 ji
{1,0,{pysm::d,pyym::ie}},//殜 die
{1,0,{pysm::zh,pyym::en}},//殝 zhen
{1,0,{pysm::y,pyym::un}},//殞 yun
{1,0,{pysm::w,pyym::en}},//殟 wen
{1,0,{pysm::ch,pyym::ou}},//殠 chou
{1,0,{pysm::b,pyym::in}},//殡 bin
{1,0,{pysm::t,pyym::i}},//殢 ti
{1,0,{pysm::j,pyym::in}},//殣 jin
{1,0,{pysm::sh,pyym::ang}},//殤 shang
{1,0,{pysm::y,pyym::in}},//殥 yin
{1,0,{pysm::d,pyym::iao}},//殦 diao
{1,0,{pysm::j,pyym::iu}},//殧 jiu
{2,1531,{pysm::nop,pyym::nop}},//殨 hui
{1,0,{pysm::c,pyym::uan}},//殩 cuan
{1,0,{pysm::y,pyym::i}},//殪 yi
{1,0,{pysm::d,pyym::an}},//殫 dan
{1,0,{pysm::d,pyym::u}},//殬 du
{1,0,{pysm::j,pyym::iang}},//殭 jiang
{1,0,{pysm::l,pyym::ian}},//殮 lian
{1,0,{pysm::b,pyym::in}},//殯 bin
{1,0,{pysm::d,pyym::u}},//殰 du
{1,0,{pysm::j,pyym::ian}},//殱 jian
{1,0,{pysm::j,pyym::ian}},//殲 jian
{1,0,{pysm::sh,pyym::u}},//殳 shu
{1,0,{pysm::nop,pyym::ou}},//殴 ou
{1,0,{pysm::d,pyym::uan}},//段 duan
{1,0,{pysm::zh,pyym::u}},//殶 zhu
{2,1532,{pysm::nop,pyym::nop}},//殷 yin
{3,368,{pysm::nop,pyym::nop}},//殸 qing
{1,0,{pysm::y,pyym::i}},//殹 yi
{5,28,{pysm::nop,pyym::nop}},//殺 sha
{1,0,{pysm::q,pyym::iao}},//殻 qiao
{2,1533,{pysm::nop,pyym::nop}},//殼 ke
{2,1534,{pysm::nop,pyym::nop}},//殽 xiao
{1,0,{pysm::x,pyym::un}},//殾 xun
{1,0,{pysm::d,pyym::ian}},//殿 dian
{1,0,{pysm::h,pyym::ui}},//毀 hui
{1,0,{pysm::h,pyym::ui}},//毁 hui
{1,0,{pysm::g,pyym::u}},//毂 gu
{1,0,{pysm::q,pyym::iao}},//毃 qiao
{1,0,{pysm::j,pyym::i}},//毄 ji
{1,0,{pysm::y,pyym::i}},//毅 yi
{3,369,{pysm::nop,pyym::nop}},//毆 ou
{1,0,{pysm::h,pyym::ui}},//毇 hui
{1,0,{pysm::d,pyym::uan}},//毈 duan
{1,0,{pysm::y,pyym::i}},//毉 yi
{1,0,{pysm::x,pyym::iao}},//毊 xiao
{2,1535,{pysm::nop,pyym::nop}},//毋 wu
{1,0,{pysm::g,pyym::uan}},//毌 guan
{2,1536,{pysm::nop,pyym::nop}},//母 mu
{1,0,{pysm::m,pyym::ei}},//毎 mei
{1,0,{pysm::m,pyym::ei}},//每 mei
{1,0,{pysm::nop,pyym::ai}},//毐 ai
{1,0,{pysm::j,pyym::ie}},//毑 jie
{2,1537,{pysm::nop,pyym::nop}},//毒 du
{1,0,{pysm::y,pyym::u}},//毓 yu
{2,1538,{pysm::nop,pyym::nop}},//比 bi
{1,0,{pysm::b,pyym::i}},//毕 bi
{1,0,{pysm::b,pyym::i}},//毖 bi
{1,0,{pysm::p,pyym::i}},//毗 pi
{1,0,{pysm::p,pyym::i}},//毘 pi
{1,0,{pysm::b,pyym::i}},//毙 bi
{1,0,{pysm::ch,pyym::an}},//毚 chan
{1,0,{pysm::m,pyym::ao}},//毛 mao
{1,0,{pysm::h,pyym::ao}},//毜 hao
{1,0,{pysm::c,pyym::ai}},//毝 cai
{1,0,{pysm::p,pyym::i}},//毞 pi
{1,0,{pysm::l,pyym::ie}},//毟 lie
{1,0,{pysm::j,pyym::ia}},//毠 jia
{1,0,{pysm::zh,pyym::an}},//毡 zhan
{1,0,{pysm::s,pyym::ai}},//毢 sai
{2,1539,{pysm::nop,pyym::nop}},//毣 mu
{1,0,{pysm::t,pyym::uo}},//毤 tuo
{1,0,{pysm::x,pyym::un}},//毥 xun
{1,0,{pysm::nop,pyym::er}},//毦 er
{1,0,{pysm::r,pyym::ong}},//毧 rong
{1,0,{pysm::x,pyym::ian}},//毨 xian
{1,0,{pysm::j,pyym::u}},//毩 ju
{1,0,{pysm::m,pyym::u}},//毪 mu
{1,0,{pysm::h,pyym::ao}},//毫 hao
{1,0,{pysm::q,pyym::iu}},//毬 qiu
{2,1540,{pysm::nop,pyym::nop}},//毭 dou
{1,0,{pysm::sh,pyym::a}},//毮 sha
{1,0,{pysm::t,pyym::an}},//毯 tan
{1,0,{pysm::p,pyym::ei}},//毰 pei
{1,0,{pysm::j,pyym::u}},//毱 ju
{1,0,{pysm::d,pyym::uo}},//毲 duo
{3,370,{pysm::nop,pyym::nop}},//毳 cui
{1,0,{pysm::b,pyym::i}},//毴 bi
{1,0,{pysm::s,pyym::an}},//毵 san
{1,0,{pysm::s,pyym::an}},//毶 san
{1,0,{pysm::m,pyym::ao}},//毷 mao
{2,1541,{pysm::nop,pyym::nop}},//毸 sai
{2,1542,{pysm::nop,pyym::nop}},//毹 shu
{1,0,{pysm::sh,pyym::u}},//毺 shu
{1,0,{pysm::t,pyym::uo}},//毻 tuo
{3,371,{pysm::nop,pyym::nop}},//毼 he
{1,0,{pysm::j,pyym::ian}},//毽 jian
{1,0,{pysm::t,pyym::a}},//毾 ta
{1,0,{pysm::s,pyym::an}},//毿 san
{4,79,{pysm::nop,pyym::nop}},//氀 lü
{1,0,{pysm::m,pyym::u}},//氁 mu
{2,1543,{pysm::nop,pyym::nop}},//氂 mao
{1,0,{pysm::t,pyym::ong}},//氃 tong
{1,0,{pysm::r,pyym::ong}},//氄 rong
{1,0,{pysm::ch,pyym::ang}},//氅 chang
{1,0,{pysm::p,pyym::u}},//氆 pu
{1,0,{pysm::l,pyym::u}},//氇 lu
{1,0,{pysm::zh,pyym::an}},//氈 zhan
{1,0,{pysm::s,pyym::ao}},//氉 sao
{1,0,{pysm::zh,pyym::an}},//氊 zhan
{1,0,{pysm::m,pyym::eng}},//氋 meng
{1,0,{pysm::l,pyym::u}},//氌 lu
{1,0,{pysm::q,pyym::u}},//氍 qu
{1,0,{pysm::d,pyym::ie}},//氎 die
{3,372,{pysm::nop,pyym::nop}},//氏 shi
{2,1544,{pysm::nop,pyym::nop}},//氐 di
{1,0,{pysm::m,pyym::in}},//民 min
{1,0,{pysm::j,pyym::ue}},//氒 jue
{2,1545,{pysm::nop,pyym::nop}},//氓 mang
{1,0,{pysm::q,pyym::i}},//气 qi
{1,0,{pysm::p,pyym::ie}},//氕 pie
{1,0,{pysm::n,pyym::ai}},//氖 nai
{1,0,{pysm::q,pyym::i}},//気 qi
{1,0,{pysm::d,pyym::ao}},//氘 dao
{1,0,{pysm::x,pyym::ian}},//氙 xian
{1,0,{pysm::ch,pyym::uan}},//氚 chuan
{1,0,{pysm::f,pyym::en}},//氛 fen
{2,1546,{pysm::nop,pyym::nop}},//氜 yang
{1,0,{pysm::n,pyym::ei}},//氝 nei
{1,0,{pysm::b,pyym::in}},//氞 bin
{1,0,{pysm::f,pyym::u}},//氟 fu
{1,0,{pysm::sh,pyym::en}},//氠 shen
{1,0,{pysm::d,pyym::ong}},//氡 dong
{1,0,{pysm::q,pyym::ing}},//氢 qing
{2,1547,{pysm::nop,pyym::nop}},//氣 qi
{2,1548,{pysm::nop,pyym::nop}},//氤 yin
{1,0,{pysm::x,pyym::i}},//氥 xi
{1,0,{pysm::h,pyym::ai}},//氦 hai
{1,0,{pysm::y,pyym::ang}},//氧 yang
{1,0,{pysm::nop,pyym::an}},//氨 an
{1,0,{pysm::y,pyym::a}},//氩 ya
{1,0,{pysm::k,pyym::e}},//氪 ke
{1,0,{pysm::q,pyym::ing}},//氫 qing
{1,0,{pysm::y,pyym::a}},//氬 ya
{1,0,{pysm::d,pyym::ong}},//氭 dong
{1,0,{pysm::d,pyym::an}},//氮 dan
{1,0,{pysm::l,pyym::v}},//氯 lü
{1,0,{pysm::q,pyym::ing}},//氰 qing
{1,0,{pysm::y,pyym::ang}},//氱 yang
{1,0,{pysm::y,pyym::un}},//氲 yun
{1,0,{pysm::y,pyym::un}},//氳 yun
{1,0,{pysm::sh,pyym::ui}},//水 shui
{1,0,{pysm::sh,pyym::ui}},//氵 shui
{2,1549,{pysm::nop,pyym::nop}},//氶 zheng
{1,0,{pysm::b,pyym::ing}},//氷 bing
{1,0,{pysm::y,pyym::ong}},//永 yong
{1,0,{pysm::d,pyym::ang}},//氹 dang
{1,0,{pysm::sh,pyym::ui}},//氺 shui
{1,0,{pysm::l,pyym::e}},//氻 le
{2,1550,{pysm::nop,pyym::nop}},//氼 ni
{2,1551,{pysm::nop,pyym::nop}},//氽 tun
{1,0,{pysm::f,pyym::an}},//氾 fan
{3,373,{pysm::nop,pyym::nop}},//氿 gui
{2,1552,{pysm::nop,pyym::nop}},//汀 ting
{3,374,{pysm::nop,pyym::nop}},//汁 zhi
{1,0,{pysm::q,pyym::iu}},//求 qiu
{2,1553,{pysm::nop,pyym::nop}},//汃 bin
{1,0,{pysm::z,pyym::e}},//汄 ze
{1,0,{pysm::m,pyym::ian}},//汅 mian
{1,0,{pysm::c,pyym::uan}},//汆 cuan
{1,0,{pysm::h,pyym::ui}},//汇 hui
{1,0,{pysm::d,pyym::iao}},//汈 diao
{1,0,{pysm::h,pyym::an}},//汉 han
{1,0,{pysm::ch,pyym::a}},//汊 cha
{4,80,{pysm::nop,pyym::nop}},//汋 zhuo
{1,0,{pysm::ch,pyym::uan}},//汌 chuan
{2,1554,{pysm::nop,pyym::nop}},//汍 wan
{2,1555,{pysm::nop,pyym::nop}},//汎 fan
{2,1556,{pysm::nop,pyym::nop}},//汏 da
{1,0,{pysm::x,pyym::i}},//汐 xi
{1,0,{pysm::t,pyym::uo}},//汑 tuo
{1,0,{pysm::m,pyym::ang}},//汒 mang
{2,1557,{pysm::nop,pyym::nop}},//汓 qiu
{1,0,{pysm::q,pyym::i}},//汔 qi
{2,1558,{pysm::nop,pyym::nop}},//汕 shan
{2,1559,{pysm::nop,pyym::nop}},//汖 pin
{2,1560,{pysm::nop,pyym::nop}},//汗 han
{1,0,{pysm::q,pyym::ian}},//汘 qian
{3,375,{pysm::nop,pyym::nop}},//汙 wu
{1,0,{pysm::w,pyym::u}},//汚 wu
{1,0,{pysm::x,pyym::un}},//汛 xun
{1,0,{pysm::s,pyym::i}},//汜 si
{1,0,{pysm::r,pyym::u}},//汝 ru
{1,0,{pysm::g,pyym::ong}},//汞 gong
{1,0,{pysm::j,pyym::iang}},//江 jiang
{3,376,{pysm::nop,pyym::nop}},//池 chi
{1,0,{pysm::w,pyym::u}},//污 wu
{1,0,{pysm::t,pyym::u}},//汢 tu
{1,0,{pysm::j,pyym::iu}},//汣 jiu
{2,1561,{pysm::nop,pyym::nop}},//汤 tang
{2,1562,{pysm::nop,pyym::nop}},//汥 zhi
{1,0,{pysm::zh,pyym::i}},//汦 zhi
{2,1563,{pysm::nop,pyym::nop}},//汧 qian
{1,0,{pysm::m,pyym::i}},//汨 mi
{3,377,{pysm::nop,pyym::nop}},//汩 gu
{2,1564,{pysm::nop,pyym::nop}},//汪 wang
{1,0,{pysm::j,pyym::ing}},//汫 jing
{1,0,{pysm::j,pyym::ing}},//汬 jing
{2,1565,{pysm::nop,pyym::nop}},//汭 rui
{1,0,{pysm::j,pyym::un}},//汮 jun
{1,0,{pysm::h,pyym::ong}},//汯 hong
{1,0,{pysm::t,pyym::ai}},//汰 tai
{2,1566,{pysm::nop,pyym::nop}},//汱 quan
{1,0,{pysm::j,pyym::i}},//汲 ji
{1,0,{pysm::b,pyym::ian}},//汳 bian
{1,0,{pysm::b,pyym::ian}},//汴 bian
{3,378,{pysm::nop,pyym::nop}},//汵 gan
{3,379,{pysm::nop,pyym::nop}},//汶 wen
{1,0,{pysm::zh,pyym::ong}},//汷 zhong
{2,1567,{pysm::nop,pyym::nop}},//汸 fang
{1,0,{pysm::x,pyym::iong}},//汹 xiong
{3,380,{pysm::nop,pyym::nop}},//決 jue
{2,1568,{pysm::nop,pyym::nop}},//汻 hu
{2,1569,{pysm::nop,pyym::nop}},//汼 niu
{3,381,{pysm::nop,pyym::nop}},//汽 qi
{2,1570,{pysm::nop,pyym::nop}},//汾 fen
{1,0,{pysm::x,pyym::u}},//汿 xu
{1,0,{pysm::x,pyym::u}},//沀 xu
{1,0,{pysm::q,pyym::in}},//沁 qin
{2,1571,{pysm::nop,pyym::nop}},//沂 yi
{1,0,{pysm::w,pyym::o}},//沃 wo
{1,0,{pysm::y,pyym::un}},//沄 yun
{1,0,{pysm::y,pyym::uan}},//沅 yuan
{2,1572,{pysm::nop,pyym::nop}},//沆 hang
{2,1573,{pysm::nop,pyym::nop}},//沇 yan
{3,382,{pysm::nop,pyym::nop}},//沈 shen
{1,0,{pysm::ch,pyym::en}},//沉 chen
{1,0,{pysm::d,pyym::an}},//沊 dan
{1,0,{pysm::y,pyym::ou}},//沋 you
{4,81,{pysm::nop,pyym::nop}},//沌 dun
{1,0,{pysm::h,pyym::u}},//沍 hu
{1,0,{pysm::h,pyym::uo}},//沎 huo
{2,1574,{pysm::nop,pyym::nop}},//沏 qi
{1,0,{pysm::m,pyym::u}},//沐 mu
{2,1575,{pysm::nop,pyym::nop}},//沑 nü
{1,0,{pysm::m,pyym::ei}},//沒 mei
{2,1576,{pysm::nop,pyym::nop}},//沓 da
{1,0,{pysm::m,pyym::ian}},//沔 mian
{3,383,{pysm::nop,pyym::nop}},//沕 mi
{1,0,{pysm::ch,pyym::ong}},//沖 chong
{2,1577,{pysm::nop,pyym::nop}},//沗 pang
{1,0,{pysm::b,pyym::i}},//沘 bi
{2,1578,{pysm::nop,pyym::nop}},//沙 sha
{1,0,{pysm::zh,pyym::i}},//沚 zhi
{1,0,{pysm::p,pyym::ei}},//沛 pei
{1,0,{pysm::p,pyym::an}},//沜 pan
{2,1579,{pysm::nop,pyym::nop}},//沝 zhui
{1,0,{pysm::z,pyym::a}},//沞 za
{1,0,{pysm::g,pyym::ou}},//沟 gou
{1,0,{pysm::l,pyym::iu}},//沠 liu
{3,384,{pysm::nop,pyym::nop}},//没 mei
{1,0,{pysm::z,pyym::e}},//沢 ze
{1,0,{pysm::f,pyym::eng}},//沣 feng
{1,0,{pysm::nop,pyym::ou}},//沤 ou
{1,0,{pysm::l,pyym::i}},//沥 li
{1,0,{pysm::l,pyym::un}},//沦 lun
{1,0,{pysm::c,pyym::ang}},//沧 cang
{1,0,{pysm::f,pyym::eng}},//沨 feng
{1,0,{pysm::w,pyym::ei}},//沩 wei
{1,0,{pysm::h,pyym::u}},//沪 hu
{1,0,{pysm::m,pyym::o}},//沫 mo
{2,1580,{pysm::nop,pyym::nop}},//沬 mei
{1,0,{pysm::sh,pyym::u}},//沭 shu
{3,385,{pysm::nop,pyym::nop}},//沮 ju
{1,0,{pysm::z,pyym::a}},//沯 za
{2,1581,{pysm::nop,pyym::nop}},//沰 tuo
{3,386,{pysm::nop,pyym::nop}},//沱 tuo
{1,0,{pysm::t,pyym::uo}},//沲 tuo
{1,0,{pysm::h,pyym::e}},//河 he
{2,1582,{pysm::nop,pyym::nop}},//沴 li
{1,0,{pysm::m,pyym::i}},//沵 mi
{3,387,{pysm::nop,pyym::nop}},//沶 yi
{1,0,{pysm::f,pyym::a}},//沷 fa
{2,1583,{pysm::nop,pyym::nop}},//沸 fei
{1,0,{pysm::y,pyym::ou}},//油 you
{1,0,{pysm::t,pyym::ian}},//沺 tian
{2,1584,{pysm::nop,pyym::nop}},//治 zhi
{1,0,{pysm::zh,pyym::ao}},//沼 zhao
{1,0,{pysm::g,pyym::u}},//沽 gu
{4,82,{pysm::nop,pyym::nop}},//沾 zhan
{1,0,{pysm::y,pyym::an}},//沿 yan
{1,0,{pysm::s,pyym::i}},//泀 si
{1,0,{pysm::k,pyym::uang}},//況 kuang
{2,1585,{pysm::nop,pyym::nop}},//泂 jiong
{2,1586,{pysm::nop,pyym::nop}},//泃 ju
{2,1587,{pysm::nop,pyym::nop}},//泄 xie
{2,1588,{pysm::nop,pyym::nop}},//泅 qiu
{2,1589,{pysm::nop,pyym::nop}},//泆 yi
{1,0,{pysm::j,pyym::ia}},//泇 jia
{1,0,{pysm::zh,pyym::ong}},//泈 zhong
{1,0,{pysm::q,pyym::uan}},//泉 quan
{2,1590,{pysm::nop,pyym::nop}},//泊 po
{1,0,{pysm::h,pyym::ui}},//泋 hui
{2,1591,{pysm::nop,pyym::nop}},//泌 mi
{1,0,{pysm::b,pyym::en}},//泍 ben
{1,0,{pysm::z,pyym::e}},//泎 ze
{2,1592,{pysm::nop,pyym::nop}},//泏 zhu
{1,0,{pysm::l,pyym::e}},//泐 le
{2,1593,{pysm::nop,pyym::nop}},//泑 you
{1,0,{pysm::g,pyym::u}},//泒 gu
{1,0,{pysm::h,pyym::ong}},//泓 hong
{2,1594,{pysm::nop,pyym::nop}},//泔 gan
{1,0,{pysm::f,pyym::a}},//法 fa
{2,1595,{pysm::nop,pyym::nop}},//泖 mao
{1,0,{pysm::s,pyym::i}},//泗 si
{1,0,{pysm::h,pyym::u}},//泘 hu
{2,1596,{pysm::nop,pyym::nop}},//泙 ping
{2,1597,{pysm::nop,pyym::nop}},//泚 ci
{3,388,{pysm::nop,pyym::nop}},//泛 fan
{2,1598,{pysm::nop,pyym::nop}},//泜 zhi
{1,0,{pysm::s,pyym::u}},//泝 su
{2,1599,{pysm::nop,pyym::nop}},//泞 ning
{1,0,{pysm::ch,pyym::eng}},//泟 cheng
{1,0,{pysm::l,pyym::ing}},//泠 ling
{1,0,{pysm::p,pyym::ao}},//泡 pao
{3,389,{pysm::nop,pyym::nop}},//波 bo
{3,390,{pysm::nop,pyym::nop}},//泣 qi
{1,0,{pysm::s,pyym::i}},//泤 si
{3,391,{pysm::nop,pyym::nop}},//泥 ni
{1,0,{pysm::j,pyym::u}},//泦 ju
{2,1600,{pysm::nop,pyym::nop}},//泧 sa
{2,1601,{pysm::nop,pyym::nop}},//注 zhu
{1,0,{pysm::sh,pyym::eng}},//泩 sheng
{1,0,{pysm::l,pyym::ei}},//泪 lei
{2,1602,{pysm::nop,pyym::nop}},//泫 xuan
{2,1603,{pysm::nop,pyym::nop}},//泬 jue
{1,0,{pysm::f,pyym::u}},//泭 fu
{1,0,{pysm::p,pyym::an}},//泮 pan
{2,1604,{pysm::nop,pyym::nop}},//泯 min
{1,0,{pysm::t,pyym::ai}},//泰 tai
{1,0,{pysm::y,pyym::ang}},//泱 yang
{1,0,{pysm::j,pyym::i}},//泲 ji
{1,0,{pysm::y,pyym::ong}},//泳 yong
{1,0,{pysm::g,pyym::uan}},//泴 guan
{3,392,{pysm::nop,pyym::nop}},//泵 beng
{1,0,{pysm::x,pyym::ue}},//泶 xue
{2,1605,{pysm::nop,pyym::nop}},//泷 long
{1,0,{pysm::l,pyym::u}},//泸 lu
{1,0,{pysm::d,pyym::an}},//泹 dan
{2,1606,{pysm::nop,pyym::nop}},//泺 luo
{1,0,{pysm::x,pyym::ie}},//泻 xie
{1,0,{pysm::p,pyym::o}},//泼 po
{1,0,{pysm::z,pyym::e}},//泽 ze
{1,0,{pysm::j,pyym::ing}},//泾 jing
{1,0,{pysm::y,pyym::in}},//泿 yin
{2,1607,{pysm::nop,pyym::nop}},//洀 pan
{2,1608,{pysm::nop,pyym::nop}},//洁 jie
{1,0,{pysm::y,pyym::e}},//洂 ye
{1,0,{pysm::h,pyym::ui}},//洃 hui
{1,0,{pysm::h,pyym::ui}},//洄 hui
{1,0,{pysm::z,pyym::ai}},//洅 zai
{1,0,{pysm::ch,pyym::eng}},//洆 cheng
{3,393,{pysm::nop,pyym::nop}},//洇 yin
{1,0,{pysm::w,pyym::ei}},//洈 wei
{1,0,{pysm::h,pyym::ou}},//洉 hou
{2,1609,{pysm::nop,pyym::nop}},//洊 jian
{2,1610,{pysm::nop,pyym::nop}},//洋 yang
{1,0,{pysm::l,pyym::ie}},//洌 lie
{1,0,{pysm::s,pyym::i}},//洍 si
{1,0,{pysm::j,pyym::i}},//洎 ji
{1,0,{pysm::nop,pyym::er}},//洏 er
{1,0,{pysm::x,pyym::ing}},//洐 xing
{1,0,{pysm::f,pyym::u}},//洑 fu
{6,2,{pysm::nop,pyym::nop}},//洒 sa
{3,394,{pysm::nop,pyym::nop}},//洓 se
{1,0,{pysm::zh,pyym::i}},//洔 zhi
{1,0,{pysm::y,pyym::in}},//洕 yin
{1,0,{pysm::w,pyym::u}},//洖 wu
{2,1611,{pysm::nop,pyym::nop}},//洗 xi
{1,0,{pysm::k,pyym::ao}},//洘 kao
{1,0,{pysm::zh,pyym::u}},//洙 zhu
{2,1612,{pysm::nop,pyym::nop}},//洚 jiang
{1,0,{pysm::l,pyym::uo}},//洛 luo
{1,0,{pysm::l,pyym::uo}},//洜 luo
{3,395,{pysm::nop,pyym::nop}},//洝 an
{2,1613,{pysm::nop,pyym::nop}},//洞 dong
{1,0,{pysm::t,pyym::i}},//洟 ti
{1,0,{pysm::m,pyym::ou}},//洠 mou
{1,0,{pysm::l,pyym::ei}},//洡 lei
{1,0,{pysm::y,pyym::i}},//洢 yi
{1,0,{pysm::m,pyym::i}},//洣 mi
{1,0,{pysm::q,pyym::uan}},//洤 quan
{1,0,{pysm::j,pyym::in}},//津 jin
{1,0,{pysm::p,pyym::o}},//洦 po
{1,0,{pysm::w,pyym::ei}},//洧 wei
{1,0,{pysm::x,pyym::iao}},//洨 xiao
{2,1614,{pysm::nop,pyym::nop}},//洩 xie
{1,0,{pysm::h,pyym::ong}},//洪 hong
{2,1615,{pysm::nop,pyym::nop}},//洫 xu
{2,1616,{pysm::nop,pyym::nop}},//洬 su
{1,0,{pysm::k,pyym::uang}},//洭 kuang
{3,396,{pysm::nop,pyym::nop}},//洮 tao
{2,1617,{pysm::nop,pyym::nop}},//洯 qie
{1,0,{pysm::j,pyym::u}},//洰 ju
{1,0,{pysm::nop,pyym::er}},//洱 er
{1,0,{pysm::zh,pyym::ou}},//洲 zhou
{1,0,{pysm::r,pyym::u}},//洳 ru
{2,1618,{pysm::nop,pyym::nop}},//洴 ping
{2,1619,{pysm::nop,pyym::nop}},//洵 xun
{1,0,{pysm::x,pyym::iong}},//洶 xiong
{1,0,{pysm::zh,pyym::i}},//洷 zhi
{2,1620,{pysm::nop,pyym::nop}},//洸 guang
{1,0,{pysm::h,pyym::uan}},//洹 huan
{1,0,{pysm::m,pyym::ing}},//洺 ming
{2,1621,{pysm::nop,pyym::nop}},//活 huo
{2,1622,{pysm::nop,pyym::nop}},//洼 wa
{2,1623,{pysm::nop,pyym::nop}},//洽 qia
{4,83,{pysm::nop,pyym::nop}},//派 pai
{2,1624,{pysm::nop,pyym::nop}},//洿 wu
{1,0,{pysm::q,pyym::u}},//浀 qu
{1,0,{pysm::l,pyym::iu}},//流 liu
{1,0,{pysm::y,pyym::i}},//浂 yi
{1,0,{pysm::j,pyym::ia}},//浃 jia
{1,0,{pysm::j,pyym::ing}},//浄 jing
{2,1625,{pysm::nop,pyym::nop}},//浅 qian
{1,0,{pysm::j,pyym::iang}},//浆 jiang
{1,0,{pysm::j,pyym::iao}},//浇 jiao
{1,0,{pysm::zh,pyym::en}},//浈 zhen
{1,0,{pysm::sh,pyym::i}},//浉 shi
{1,0,{pysm::zh,pyym::uo}},//浊 zhuo
{1,0,{pysm::c,pyym::e}},//测 ce
{1,0,{pysm::f,pyym::a}},//浌 fa
{2,1626,{pysm::nop,pyym::nop}},//浍 hui
{1,0,{pysm::j,pyym::i}},//济 ji
{1,0,{pysm::l,pyym::iu}},//浏 liu
{1,0,{pysm::ch,pyym::an}},//浐 chan
{1,0,{pysm::h,pyym::un}},//浑 hun
{2,1627,{pysm::nop,pyym::nop}},//浒 hu
{1,0,{pysm::n,pyym::ong}},//浓 nong
{1,0,{pysm::x,pyym::un}},//浔 xun
{1,0,{pysm::j,pyym::in}},//浕 jin
{1,0,{pysm::l,pyym::ie}},//浖 lie
{1,0,{pysm::q,pyym::iu}},//浗 qiu
{1,0,{pysm::w,pyym::ei}},//浘 wei
{1,0,{pysm::zh,pyym::e}},//浙 zhe
{3,397,{pysm::nop,pyym::nop}},//浚 jun
{2,1628,{pysm::nop,pyym::nop}},//浛 han
{2,1629,{pysm::nop,pyym::nop}},//浜 bang
{1,0,{pysm::m,pyym::ang}},//浝 mang
{1,0,{pysm::zh,pyym::uo}},//浞 zhuo
{2,1630,{pysm::nop,pyym::nop}},//浟 you
{1,0,{pysm::x,pyym::i}},//浠 xi
{1,0,{pysm::b,pyym::o}},//浡 bo
{1,0,{pysm::d,pyym::ou}},//浢 dou
{1,0,{pysm::h,pyym::uan}},//浣 huan
{1,0,{pysm::h,pyym::ong}},//浤 hong
{2,1631,{pysm::nop,pyym::nop}},//浥 yi
{1,0,{pysm::p,pyym::u}},//浦 pu
{3,398,{pysm::nop,pyym::nop}},//浧 ying
{1,0,{pysm::l,pyym::an}},//浨 lan
{3,399,{pysm::nop,pyym::nop}},//浩 hao
{1,0,{pysm::l,pyym::ang}},//浪 lang
{1,0,{pysm::h,pyym::an}},//浫 han
{2,1632,{pysm::nop,pyym::nop}},//浬 li
{1,0,{pysm::g,pyym::eng}},//浭 geng
{1,0,{pysm::f,pyym::u}},//浮 fu
{1,0,{pysm::w,pyym::u}},//浯 wu
{2,1633,{pysm::nop,pyym::nop}},//浰 lian
{1,0,{pysm::ch,pyym::un}},//浱 chun
{2,1634,{pysm::nop,pyym::nop}},//浲 feng
{1,0,{pysm::y,pyym::i}},//浳 yi
{1,0,{pysm::y,pyym::u}},//浴 yu
{1,0,{pysm::t,pyym::ong}},//浵 tong
{1,0,{pysm::l,pyym::ao}},//浶 lao
{1,0,{pysm::h,pyym::ai}},//海 hai
{2,1635,{pysm::nop,pyym::nop}},//浸 jin
{2,1636,{pysm::nop,pyym::nop}},//浹 jia
{1,0,{pysm::ch,pyym::ong}},//浺 chong
{1,0,{pysm::j,pyym::iong}},//浻 jiong
{1,0,{pysm::m,pyym::ei}},//浼 mei
{2,1637,{pysm::nop,pyym::nop}},//浽 sui
{1,0,{pysm::ch,pyym::eng}},//浾 cheng
{1,0,{pysm::p,pyym::ei}},//浿 pei
{2,1638,{pysm::nop,pyym::nop}},//涀 xian
{1,0,{pysm::sh,pyym::en}},//涁 shen
{3,400,{pysm::nop,pyym::nop}},//涂 tu
{1,0,{pysm::k,pyym::un}},//涃 kun
{1,0,{pysm::p,pyym::ing}},//涄 ping
{1,0,{pysm::n,pyym::ie}},//涅 nie
{1,0,{pysm::h,pyym::an}},//涆 han
{2,1639,{pysm::nop,pyym::nop}},//涇 jing
{1,0,{pysm::x,pyym::iao}},//消 xiao
{2,1640,{pysm::nop,pyym::nop}},//涉 she
{2,1641,{pysm::nop,pyym::nop}},//涊 nian
{1,0,{pysm::t,pyym::u}},//涋 tu
{2,1642,{pysm::nop,pyym::nop}},//涌 yong
{1,0,{pysm::x,pyym::iao}},//涍 xiao
{3,401,{pysm::nop,pyym::nop}},//涎 xian
{1,0,{pysm::t,pyym::ing}},//涏 ting
{1,0,{pysm::nop,pyym::e}},//涐 e
{3,402,{pysm::nop,pyym::nop}},//涑 su
{2,1643,{pysm::nop,pyym::nop}},//涒 tun
{3,403,{pysm::nop,pyym::nop}},//涓 juan
{3,404,{pysm::nop,pyym::nop}},//涔 cen
{1,0,{pysm::t,pyym::i}},//涕 ti
{1,0,{pysm::l,pyym::i}},//涖 li
{1,0,{pysm::sh,pyym::ui}},//涗 shui
{1,0,{pysm::s,pyym::i}},//涘 si
{1,0,{pysm::l,pyym::ei}},//涙 lei
{1,0,{pysm::sh,pyym::ui}},//涚 shui
{1,0,{pysm::t,pyym::ao}},//涛 tao
{1,0,{pysm::d,pyym::u}},//涜 du
{1,0,{pysm::l,pyym::ao}},//涝 lao
{1,0,{pysm::l,pyym::ai}},//涞 lai
{1,0,{pysm::l,pyym::ian}},//涟 lian
{1,0,{pysm::w,pyym::ei}},//涠 wei
{2,1644,{pysm::nop,pyym::nop}},//涡 wo
{1,0,{pysm::y,pyym::un}},//涢 yun
{2,1645,{pysm::nop,pyym::nop}},//涣 huan
{1,0,{pysm::d,pyym::i}},//涤 di
{1,0,{pysm::h,pyym::eng}},//涥 heng
{1,0,{pysm::r,pyym::un}},//润 run
{1,0,{pysm::j,pyym::ian}},//涧 jian
{1,0,{pysm::zh,pyym::ang}},//涨 zhang
{1,0,{pysm::s,pyym::e}},//涩 se
{2,1646,{pysm::nop,pyym::nop}},//涪 fu
{1,0,{pysm::g,pyym::uan}},//涫 guan
{1,0,{pysm::x,pyym::ing}},//涬 xing
{2,1647,{pysm::nop,pyym::nop}},//涭 shou
{2,1648,{pysm::nop,pyym::nop}},//涮 shuan
{1,0,{pysm::y,pyym::a}},//涯 ya
{1,0,{pysm::ch,pyym::uo}},//涰 chuo
{1,0,{pysm::zh,pyym::ang}},//涱 zhang
{2,1649,{pysm::nop,pyym::nop}},//液 ye
{2,1650,{pysm::nop,pyym::nop}},//涳 kong
{3,405,{pysm::nop,pyym::nop}},//涴 wo
{1,0,{pysm::h,pyym::an}},//涵 han
{1,0,{pysm::t,pyym::uo}},//涶 tuo
{1,0,{pysm::d,pyym::ong}},//涷 dong
{1,0,{pysm::h,pyym::e}},//涸 he
{1,0,{pysm::w,pyym::o}},//涹 wo
{1,0,{pysm::j,pyym::u}},//涺 ju
{1,0,{pysm::sh,pyym::e}},//涻 she
{1,0,{pysm::l,pyym::iang}},//涼 liang
{1,0,{pysm::h,pyym::un}},//涽 hun
{1,0,{pysm::t,pyym::a}},//涾 ta
{1,0,{pysm::zh,pyym::uo}},//涿 zhuo
{1,0,{pysm::d,pyym::ian}},//淀 dian
{2,1651,{pysm::nop,pyym::nop}},//淁 qie
{1,0,{pysm::d,pyym::e}},//淂 de
{1,0,{pysm::j,pyym::uan}},//淃 juan
{1,0,{pysm::z,pyym::i}},//淄 zi
{1,0,{pysm::x,pyym::i}},//淅 xi
{1,0,{pysm::x,pyym::iao}},//淆 xiao
{1,0,{pysm::q,pyym::i}},//淇 qi
{2,1652,{pysm::nop,pyym::nop}},//淈 gu
{2,1653,{pysm::nop,pyym::nop}},//淉 guo
{2,1654,{pysm::nop,pyym::nop}},//淊 yan
{1,0,{pysm::l,pyym::in}},//淋 lin
{2,1655,{pysm::nop,pyym::nop}},//淌 tang
{2,1656,{pysm::nop,pyym::nop}},//淍 zhou
{1,0,{pysm::p,pyym::eng}},//淎 peng
{1,0,{pysm::h,pyym::ao}},//淏 hao
{1,0,{pysm::ch,pyym::ang}},//淐 chang
{2,1657,{pysm::nop,pyym::nop}},//淑 shu
{2,1658,{pysm::nop,pyym::nop}},//淒 qi
{1,0,{pysm::f,pyym::ang}},//淓 fang
{1,0,{pysm::zh,pyym::i}},//淔 zhi
{1,0,{pysm::l,pyym::u}},//淕 lu
{4,84,{pysm::nop,pyym::nop}},//淖 nao
{1,0,{pysm::j,pyym::u}},//淗 ju
{1,0,{pysm::t,pyym::ao}},//淘 tao
{2,1659,{pysm::nop,pyym::nop}},//淙 cong
{2,1660,{pysm::nop,pyym::nop}},//淚 lei
{1,0,{pysm::zh,pyym::e}},//淛 zhe
{2,1661,{pysm::nop,pyym::nop}},//淜 ping
{1,0,{pysm::f,pyym::ei}},//淝 fei
{1,0,{pysm::s,pyym::ong}},//淞 song
{1,0,{pysm::t,pyym::ian}},//淟 tian
{2,1662,{pysm::nop,pyym::nop}},//淠 pi
{3,406,{pysm::nop,pyym::nop}},//淡 dan
{2,1663,{pysm::nop,pyym::nop}},//淢 yu
{1,0,{pysm::n,pyym::i}},//淣 ni
{1,0,{pysm::y,pyym::u}},//淤 yu
{1,0,{pysm::l,pyym::u}},//淥 lu
{2,1664,{pysm::nop,pyym::nop}},//淦 gan
{1,0,{pysm::m,pyym::i}},//淧 mi
{2,1665,{pysm::nop,pyym::nop}},//淨 jing
{1,0,{pysm::l,pyym::ing}},//淩 ling
{2,1666,{pysm::nop,pyym::nop}},//淪 lun
{3,407,{pysm::nop,pyym::nop}},//淫 yin
{2,1667,{pysm::nop,pyym::nop}},//淬 cui
{1,0,{pysm::q,pyym::u}},//淭 qu
{1,0,{pysm::h,pyym::uai}},//淮 huai
{1,0,{pysm::y,pyym::u}},//淯 yu
{3,408,{pysm::nop,pyym::nop}},//淰 nian
{1,0,{pysm::sh,pyym::en}},//深 shen
{2,1668,{pysm::nop,pyym::nop}},//淲 biao
{2,1669,{pysm::nop,pyym::nop}},//淳 chun
{1,0,{pysm::h,pyym::u}},//淴 hu
{1,0,{pysm::y,pyym::uan}},//淵 yuan
{1,0,{pysm::l,pyym::ai}},//淶 lai
{3,409,{pysm::nop,pyym::nop}},//混 hun
{1,0,{pysm::q,pyym::ing}},//淸 qing
{1,0,{pysm::y,pyym::an}},//淹 yan
{4,85,{pysm::nop,pyym::nop}},//淺 qian
{1,0,{pysm::t,pyym::ian}},//添 tian
{1,0,{pysm::m,pyym::iao}},//淼 miao
{1,0,{pysm::zh,pyym::i}},//淽 zhi
{1,0,{pysm::y,pyym::in}},//淾 yin
{1,0,{pysm::b,pyym::o}},//淿 bo
{1,0,{pysm::b,pyym::en}},//渀 ben
{1,0,{pysm::y,pyym::uan}},//渁 yuan
{2,1670,{pysm::nop,pyym::nop}},//渂 wen
{2,1671,{pysm::nop,pyym::nop}},//渃 ruo
{1,0,{pysm::f,pyym::ei}},//渄 fei
{1,0,{pysm::q,pyym::ing}},//清 qing
{1,0,{pysm::y,pyym::uan}},//渆 yuan
{1,0,{pysm::k,pyym::e}},//渇 ke
{1,0,{pysm::j,pyym::i}},//済 ji
{1,0,{pysm::sh,pyym::e}},//渉 she
{1,0,{pysm::y,pyym::uan}},//渊 yuan
{1,0,{pysm::s,pyym::e}},//渋 se
{1,0,{pysm::l,pyym::u}},//渌 lu
{1,0,{pysm::z,pyym::i}},//渍 zi
{1,0,{pysm::d,pyym::u}},//渎 du
{1,0,{pysm::y,pyym::i}},//渏 yi
{1,0,{pysm::j,pyym::ian}},//渐 jian
{2,1672,{pysm::nop,pyym::nop}},//渑 mian
{1,0,{pysm::p,pyym::ai}},//渒 pai
{1,0,{pysm::x,pyym::i}},//渓 xi
{1,0,{pysm::y,pyym::u}},//渔 yu
{1,0,{pysm::y,pyym::uan}},//渕 yuan
{1,0,{pysm::sh,pyym::en}},//渖 shen
{1,0,{pysm::sh,pyym::en}},//渗 shen
{1,0,{pysm::r,pyym::ou}},//渘 rou
{1,0,{pysm::h,pyym::uan}},//渙 huan
{1,0,{pysm::zh,pyym::u}},//渚 zhu
{1,0,{pysm::j,pyym::ian}},//減 jian
{1,0,{pysm::n,pyym::uan}},//渜 nuan
{1,0,{pysm::y,pyym::u}},//渝 yu
{2,1673,{pysm::nop,pyym::nop}},//渞 qiu
{1,0,{pysm::t,pyym::ing}},//渟 ting
{2,1674,{pysm::nop,pyym::nop}},//渠 qu
{1,0,{pysm::d,pyym::u}},//渡 du
{2,1675,{pysm::nop,pyym::nop}},//渢 fan
{1,0,{pysm::zh,pyym::a}},//渣 zha
{1,0,{pysm::b,pyym::o}},//渤 bo
{3,410,{pysm::nop,pyym::nop}},//渥 wo
{2,1676,{pysm::nop,pyym::nop}},//渦 wo
{2,1677,{pysm::nop,pyym::nop}},//渧 di
{1,0,{pysm::w,pyym::ei}},//渨 wei
{2,1678,{pysm::nop,pyym::nop}},//温 wen
{1,0,{pysm::r,pyym::u}},//渪 ru
{5,29,{pysm::nop,pyym::nop}},//渫 xie
{1,0,{pysm::c,pyym::e}},//測 ce
{1,0,{pysm::w,pyym::ei}},//渭 wei
{1,0,{pysm::h,pyym::e}},//渮 he
{2,1679,{pysm::nop,pyym::nop}},//港 gang
{1,0,{pysm::y,pyym::an}},//渰 yan
{2,1680,{pysm::nop,pyym::nop}},//渱 hong
{1,0,{pysm::x,pyym::uan}},//渲 xuan
{1,0,{pysm::m,pyym::i}},//渳 mi
{4,86,{pysm::nop,pyym::nop}},//渴 ke
{1,0,{pysm::m,pyym::ao}},//渵 mao
{1,0,{pysm::y,pyym::ing}},//渶 ying
{1,0,{pysm::y,pyym::an}},//渷 yan
{2,1681,{pysm::nop,pyym::nop}},//游 you
{2,1682,{pysm::nop,pyym::nop}},//渹 hong
{1,0,{pysm::m,pyym::iao}},//渺 miao
{1,0,{pysm::sh,pyym::eng}},//渻 sheng
{1,0,{pysm::m,pyym::ei}},//渼 mei
{1,0,{pysm::z,pyym::ai}},//渽 zai
{2,1683,{pysm::nop,pyym::nop}},//渾 hun
{1,0,{pysm::n,pyym::ai}},//渿 nai
{1,0,{pysm::g,pyym::ui}},//湀 gui
{1,0,{pysm::ch,pyym::i}},//湁 chi
{1,0,{pysm::nop,pyym::e}},//湂 e
{2,1684,{pysm::nop,pyym::nop}},//湃 pai
{1,0,{pysm::m,pyym::ei}},//湄 mei
{2,1685,{pysm::nop,pyym::nop}},//湅 lian
{1,0,{pysm::q,pyym::i}},//湆 qi
{1,0,{pysm::q,pyym::i}},//湇 qi
{1,0,{pysm::m,pyym::ei}},//湈 mei
{1,0,{pysm::t,pyym::ian}},//湉 tian
{1,0,{pysm::c,pyym::ou}},//湊 cou
{1,0,{pysm::w,pyym::ei}},//湋 wei
{1,0,{pysm::c,pyym::an}},//湌 can
{2,1686,{pysm::nop,pyym::nop}},//湍 tuan
{1,0,{pysm::m,pyym::ian}},//湎 mian
{2,1687,{pysm::nop,pyym::nop}},//湏 hui
{1,0,{pysm::m,pyym::o}},//湐 mo
{1,0,{pysm::x,pyym::u}},//湑 xu
{1,0,{pysm::j,pyym::i}},//湒 ji
{1,0,{pysm::p,pyym::en}},//湓 pen
{4,87,{pysm::nop,pyym::nop}},//湔 jian
{1,0,{pysm::j,pyym::ian}},//湕 jian
{1,0,{pysm::h,pyym::u}},//湖 hu
{1,0,{pysm::f,pyym::eng}},//湗 feng
{1,0,{pysm::x,pyym::iang}},//湘 xiang
{1,0,{pysm::y,pyym::i}},//湙 yi
{1,0,{pysm::y,pyym::in}},//湚 yin
{7,1,{pysm::nop,pyym::nop}},//湛 zhan
{1,0,{pysm::sh,pyym::i}},//湜 shi
{2,1688,{pysm::nop,pyym::nop}},//湝 jie
{2,1689,{pysm::nop,pyym::nop}},//湞 zhen
{2,1690,{pysm::nop,pyym::nop}},//湟 huang
{1,0,{pysm::t,pyym::an}},//湠 tan
{1,0,{pysm::y,pyym::u}},//湡 yu
{1,0,{pysm::b,pyym::i}},//湢 bi
{3,411,{pysm::nop,pyym::nop}},//湣 min
{1,0,{pysm::sh,pyym::i}},//湤 shi
{1,0,{pysm::t,pyym::u}},//湥 tu
{1,0,{pysm::sh,pyym::eng}},//湦 sheng
{1,0,{pysm::y,pyym::ong}},//湧 yong
{1,0,{pysm::j,pyym::u}},//湨 ju
{2,1691,{pysm::nop,pyym::nop}},//湩 dong
{2,1692,{pysm::nop,pyym::nop}},//湪 tuan
{3,412,{pysm::nop,pyym::nop}},//湫 jiao
{1,0,{pysm::j,pyym::iao}},//湬 jiao
{1,0,{pysm::q,pyym::iu}},//湭 qiu
{2,1693,{pysm::nop,pyym::nop}},//湮 yan
{3,413,{pysm::nop,pyym::nop}},//湯 tang
{1,0,{pysm::l,pyym::ong}},//湰 long
{1,0,{pysm::h,pyym::uo}},//湱 huo
{1,0,{pysm::y,pyym::uan}},//湲 yuan
{1,0,{pysm::n,pyym::an}},//湳 nan
{2,1694,{pysm::nop,pyym::nop}},//湴 ban
{1,0,{pysm::y,pyym::ou}},//湵 you
{1,0,{pysm::q,pyym::uan}},//湶 quan
{2,1695,{pysm::nop,pyym::nop}},//湷 zhuang
{1,0,{pysm::l,pyym::iang}},//湸 liang
{1,0,{pysm::ch,pyym::an}},//湹 chan
{1,0,{pysm::x,pyym::ian}},//湺 xian
{1,0,{pysm::ch,pyym::un}},//湻 chun
{1,0,{pysm::n,pyym::ie}},//湼 nie
{1,0,{pysm::z,pyym::i}},//湽 zi
{1,0,{pysm::w,pyym::an}},//湾 wan
{1,0,{pysm::sh,pyym::i}},//湿 shi
{1,0,{pysm::m,pyym::an}},//満 man
{1,0,{pysm::y,pyym::ing}},//溁 ying
{1,0,{pysm::l,pyym::a}},//溂 la
{2,1696,{pysm::nop,pyym::nop}},//溃 kui
{1,0,{pysm::f,pyym::eng}},//溄 feng
{1,0,{pysm::j,pyym::ian}},//溅 jian
{1,0,{pysm::x,pyym::u}},//溆 xu
{1,0,{pysm::l,pyym::ou}},//溇 lou
{1,0,{pysm::w,pyym::ei}},//溈 wei
{2,1697,{pysm::nop,pyym::nop}},//溉 gai
{1,0,{pysm::b,pyym::o}},//溊 bo
{1,0,{pysm::y,pyym::ing}},//溋 ying
{1,0,{pysm::p,pyym::o}},//溌 po
{1,0,{pysm::j,pyym::in}},//溍 jin
{2,1698,{pysm::nop,pyym::nop}},//溎 yan
{1,0,{pysm::t,pyym::ang}},//溏 tang
{1,0,{pysm::y,pyym::uan}},//源 yuan
{1,0,{pysm::s,pyym::uo}},//溑 suo
{1,0,{pysm::y,pyym::uan}},//溒 yuan
{4,88,{pysm::nop,pyym::nop}},//溓 lian
{1,0,{pysm::y,pyym::ao}},//溔 yao
{1,0,{pysm::m,pyym::eng}},//溕 meng
{2,1699,{pysm::nop,pyym::nop}},//準 zhun
{1,0,{pysm::ch,pyym::eng}},//溗 cheng
{2,1700,{pysm::nop,pyym::nop}},//溘 ke
{1,0,{pysm::t,pyym::ai}},//溙 tai
{2,1701,{pysm::nop,pyym::nop}},//溚 ta
{1,0,{pysm::w,pyym::a}},//溛 wa
{1,0,{pysm::l,pyym::iu}},//溜 liu
{3,414,{pysm::nop,pyym::nop}},//溝 gou
{1,0,{pysm::s,pyym::ao}},//溞 sao
{2,1702,{pysm::nop,pyym::nop}},//溟 ming
{1,0,{pysm::zh,pyym::a}},//溠 zha
{1,0,{pysm::sh,pyym::i}},//溡 shi
{1,0,{pysm::y,pyym::i}},//溢 yi
{1,0,{pysm::l,pyym::un}},//溣 lun
{1,0,{pysm::m,pyym::a}},//溤 ma
{5,30,{pysm::nop,pyym::nop}},//溥 pu
{2,1703,{pysm::nop,pyym::nop}},//溦 wei
{1,0,{pysm::l,pyym::i}},//溧 li
{1,0,{pysm::z,pyym::ai}},//溨 zai
{1,0,{pysm::w,pyym::u}},//溩 wu
{2,1704,{pysm::nop,pyym::nop}},//溪 xi
{1,0,{pysm::w,pyym::en}},//溫 wen
{1,0,{pysm::q,pyym::iang}},//溬 qiang
{1,0,{pysm::z,pyym::e}},//溭 ze
{1,0,{pysm::sh,pyym::i}},//溮 shi
{2,1705,{pysm::nop,pyym::nop}},//溯 su
{1,0,{pysm::nop,pyym::ai}},//溰 ai
{2,1706,{pysm::nop,pyym::nop}},//溱 qin
{2,1707,{pysm::nop,pyym::nop}},//溲 sou
{1,0,{pysm::y,pyym::un}},//溳 yun
{2,1708,{pysm::nop,pyym::nop}},//溴 xiu
{1,0,{pysm::y,pyym::in}},//溵 yin
{1,0,{pysm::r,pyym::ong}},//溶 rong
{1,0,{pysm::h,pyym::un}},//溷 hun
{1,0,{pysm::s,pyym::u}},//溸 su
{2,1709,{pysm::nop,pyym::nop}},//溹 suo
{3,415,{pysm::nop,pyym::nop}},//溺 ni
{1,0,{pysm::t,pyym::a}},//溻 ta
{1,0,{pysm::sh,pyym::i}},//溼 shi
{1,0,{pysm::r,pyym::u}},//溽 ru
{1,0,{pysm::nop,pyym::ai}},//溾 ai
{1,0,{pysm::p,pyym::an}},//溿 pan
{2,1710,{pysm::nop,pyym::nop}},//滀 chu
{1,0,{pysm::ch,pyym::u}},//滁 chu
{2,1711,{pysm::nop,pyym::nop}},//滂 pang
{1,0,{pysm::w,pyym::eng}},//滃 weng
{1,0,{pysm::c,pyym::ang}},//滄 cang
{1,0,{pysm::m,pyym::ie}},//滅 mie
{1,0,{pysm::g,pyym::e}},//滆 ge
{3,416,{pysm::nop,pyym::nop}},//滇 dian
{2,1712,{pysm::nop,pyym::nop}},//滈 hao
{1,0,{pysm::h,pyym::uang}},//滉 huang
{3,417,{pysm::nop,pyym::nop}},//滊 xi
{3,418,{pysm::nop,pyym::nop}},//滋 zi
{1,0,{pysm::d,pyym::i}},//滌 di
{1,0,{pysm::zh,pyym::i}},//滍 zhi
{2,1713,{pysm::nop,pyym::nop}},//滎 xing
{1,0,{pysm::f,pyym::u}},//滏 fu
{1,0,{pysm::j,pyym::ie}},//滐 jie
{2,1714,{pysm::nop,pyym::nop}},//滑 hua
{1,0,{pysm::g,pyym::e}},//滒 ge
{1,0,{pysm::z,pyym::i}},//滓 zi
{1,0,{pysm::t,pyym::ao}},//滔 tao
{1,0,{pysm::t,pyym::eng}},//滕 teng
{1,0,{pysm::s,pyym::ui}},//滖 sui
{1,0,{pysm::b,pyym::i}},//滗 bi
{1,0,{pysm::j,pyym::iao}},//滘 jiao
{1,0,{pysm::h,pyym::ui}},//滙 hui
{1,0,{pysm::g,pyym::un}},//滚 gun
{1,0,{pysm::y,pyym::in}},//滛 yin
{1,0,{pysm::g,pyym::ao}},//滜 gao
{1,0,{pysm::l,pyym::ong}},//滝 long
{1,0,{pysm::zh,pyym::i}},//滞 zhi
{1,0,{pysm::y,pyym::an}},//滟 yan
{1,0,{pysm::sh,pyym::e}},//滠 she
{1,0,{pysm::m,pyym::an}},//满 man
{1,0,{pysm::y,pyym::ing}},//滢 ying
{1,0,{pysm::ch,pyym::un}},//滣 chun
{1,0,{pysm::l,pyym::v}},//滤 lü
{1,0,{pysm::l,pyym::an}},//滥 lan
{1,0,{pysm::l,pyym::uan}},//滦 luan
{2,1715,{pysm::nop,pyym::nop}},//滧 yao
{1,0,{pysm::b,pyym::in}},//滨 bin
{1,0,{pysm::t,pyym::an}},//滩 tan
{1,0,{pysm::y,pyym::u}},//滪 yu
{1,0,{pysm::x,pyym::iu}},//滫 xiu
{1,0,{pysm::h,pyym::u}},//滬 hu
{1,0,{pysm::b,pyym::i}},//滭 bi
{1,0,{pysm::b,pyym::iao}},//滮 biao
{2,1716,{pysm::nop,pyym::nop}},//滯 zhi
{1,0,{pysm::j,pyym::iang}},//滰 jiang
{1,0,{pysm::k,pyym::ou}},//滱 kou
{4,89,{pysm::nop,pyym::nop}},//滲 shen
{1,0,{pysm::sh,pyym::ang}},//滳 shang
{1,0,{pysm::d,pyym::i}},//滴 di
{1,0,{pysm::m,pyym::i}},//滵 mi
{1,0,{pysm::nop,pyym::ao}},//滶 ao
{1,0,{pysm::l,pyym::u}},//滷 lu
{2,1717,{pysm::nop,pyym::nop}},//滸 hu
{1,0,{pysm::h,pyym::u}},//滹 hu
{1,0,{pysm::y,pyym::ou}},//滺 you
{1,0,{pysm::ch,pyym::an}},//滻 chan
{1,0,{pysm::f,pyym::an}},//滼 fan
{1,0,{pysm::y,pyym::ong}},//滽 yong
{1,0,{pysm::g,pyym::un}},//滾 gun
{2,1718,{pysm::nop,pyym::nop}},//滿 man
{1,0,{pysm::q,pyym::ing}},//漀 qing
{1,0,{pysm::y,pyym::u}},//漁 yu
{2,1719,{pysm::nop,pyym::nop}},//漂 piao
{1,0,{pysm::j,pyym::i}},//漃 ji
{1,0,{pysm::y,pyym::a}},//漄 ya
{1,0,{pysm::ch,pyym::ao}},//漅 chao
{2,1720,{pysm::nop,pyym::nop}},//漆 qi
{1,0,{pysm::x,pyym::i}},//漇 xi
{1,0,{pysm::j,pyym::i}},//漈 ji
{1,0,{pysm::l,pyym::u}},//漉 lu
{2,1721,{pysm::nop,pyym::nop}},//漊 lou
{1,0,{pysm::l,pyym::ong}},//漋 long
{1,0,{pysm::j,pyym::in}},//漌 jin
{1,0,{pysm::g,pyym::uo}},//漍 guo
{2,1722,{pysm::nop,pyym::nop}},//漎 cong
{1,0,{pysm::l,pyym::ou}},//漏 lou
{1,0,{pysm::zh,pyym::i}},//漐 zhi
{1,0,{pysm::g,pyym::ai}},//漑 gai
{1,0,{pysm::q,pyym::iang}},//漒 qiang
{1,0,{pysm::l,pyym::i}},//漓 li
{1,0,{pysm::y,pyym::an}},//演 yan
{1,0,{pysm::c,pyym::ao}},//漕 cao
{1,0,{pysm::j,pyym::iao}},//漖 jiao
{1,0,{pysm::c,pyym::ong}},//漗 cong
{1,0,{pysm::ch,pyym::un}},//漘 chun
{2,1723,{pysm::nop,pyym::nop}},//漙 tuan
{1,0,{pysm::nop,pyym::ou}},//漚 ou
{1,0,{pysm::t,pyym::eng}},//漛 teng
{1,0,{pysm::y,pyym::e}},//漜 ye
{1,0,{pysm::x,pyym::i}},//漝 xi
{1,0,{pysm::m,pyym::i}},//漞 mi
{1,0,{pysm::t,pyym::ang}},//漟 tang
{1,0,{pysm::m,pyym::o}},//漠 mo
{2,1724,{pysm::nop,pyym::nop}},//漡 shang
{2,1725,{pysm::nop,pyym::nop}},//漢 han
{2,1726,{pysm::nop,pyym::nop}},//漣 lian
{1,0,{pysm::l,pyym::an}},//漤 lan
{1,0,{pysm::w,pyym::a}},//漥 wa
{2,1727,{pysm::nop,pyym::nop}},//漦 chi
{1,0,{pysm::g,pyym::an}},//漧 gan
{3,419,{pysm::nop,pyym::nop}},//漨 feng
{1,0,{pysm::x,pyym::uan}},//漩 xuan
{1,0,{pysm::y,pyym::i}},//漪 yi
{1,0,{pysm::m,pyym::an}},//漫 man
{3,420,{pysm::nop,pyym::nop}},//漬 zi
{1,0,{pysm::m,pyym::ang}},//漭 mang
{1,0,{pysm::k,pyym::ang}},//漮 kang
{3,421,{pysm::nop,pyym::nop}},//漯 luo
{1,0,{pysm::p,pyym::eng}},//漰 peng
{1,0,{pysm::sh,pyym::u}},//漱 shu
{1,0,{pysm::zh,pyym::ang}},//漲 zhang
{1,0,{pysm::zh,pyym::ang}},//漳 zhang
{4,90,{pysm::nop,pyym::nop}},//漴 zhuang
{1,0,{pysm::x,pyym::u}},//漵 xu
{1,0,{pysm::h,pyym::uan}},//漶 huan
{2,1728,{pysm::nop,pyym::nop}},//漷 huo
{3,422,{pysm::nop,pyym::nop}},//漸 jian
{1,0,{pysm::y,pyym::an}},//漹 yan
{2,1729,{pysm::nop,pyym::nop}},//漺 shuang
{3,423,{pysm::nop,pyym::nop}},//漻 liao
{1,0,{pysm::c,pyym::ui}},//漼 cui
{1,0,{pysm::t,pyym::i}},//漽 ti
{1,0,{pysm::y,pyym::ang}},//漾 yang
{1,0,{pysm::j,pyym::iang}},//漿 jiang
{1,0,{pysm::c,pyym::ong}},//潀 cong
{1,0,{pysm::y,pyym::ing}},//潁 ying
{1,0,{pysm::h,pyym::ong}},//潂 hong
{1,0,{pysm::x,pyym::iu}},//潃 xiu
{1,0,{pysm::sh,pyym::u}},//潄 shu
{1,0,{pysm::g,pyym::uan}},//潅 guan
{1,0,{pysm::y,pyym::ing}},//潆 ying
{1,0,{pysm::x,pyym::iao}},//潇 xiao
{1,0,{pysm::z,pyym::ong}},//潈 zong
{1,0,{pysm::k,pyym::un}},//潉 kun
{1,0,{pysm::x,pyym::u}},//潊 xu
{1,0,{pysm::l,pyym::ian}},//潋 lian
{1,0,{pysm::zh,pyym::i}},//潌 zhi
{1,0,{pysm::w,pyym::ei}},//潍 wei
{3,424,{pysm::nop,pyym::nop}},//潎 pi
{3,425,{pysm::nop,pyym::nop}},//潏 yu
{2,1730,{pysm::nop,pyym::nop}},//潐 jiao
{2,1731,{pysm::nop,pyym::nop}},//潑 po
{3,426,{pysm::nop,pyym::nop}},//潒 dang
{1,0,{pysm::h,pyym::ui}},//潓 hui
{1,0,{pysm::j,pyym::ie}},//潔 jie
{1,0,{pysm::w,pyym::u}},//潕 wu
{1,0,{pysm::p,pyym::a}},//潖 pa
{1,0,{pysm::j,pyym::i}},//潗 ji
{3,427,{pysm::nop,pyym::nop}},//潘 pan
{2,1732,{pysm::nop,pyym::nop}},//潙 wei
{3,428,{pysm::nop,pyym::nop}},//潚 su
{1,0,{pysm::q,pyym::ian}},//潛 qian
{1,0,{pysm::q,pyym::ian}},//潜 qian
{2,1733,{pysm::nop,pyym::nop}},//潝 xi
{1,0,{pysm::l,pyym::u}},//潞 lu
{1,0,{pysm::x,pyym::i}},//潟 xi
{2,1734,{pysm::nop,pyym::nop}},//潠 xun
{1,0,{pysm::d,pyym::un}},//潡 dun
{2,1735,{pysm::nop,pyym::nop}},//潢 huang
{1,0,{pysm::m,pyym::in}},//潣 min
{1,0,{pysm::r,pyym::un}},//潤 run
{1,0,{pysm::s,pyym::u}},//潥 su
{2,1736,{pysm::nop,pyym::nop}},//潦 lao
{1,0,{pysm::zh,pyym::en}},//潧 zhen
{2,1737,{pysm::nop,pyym::nop}},//潨 cong
{1,0,{pysm::y,pyym::i}},//潩 yi
{2,1738,{pysm::nop,pyym::nop}},//潪 zhe
{1,0,{pysm::w,pyym::an}},//潫 wan
{2,1739,{pysm::nop,pyym::nop}},//潬 shan
{4,91,{pysm::nop,pyym::nop}},//潭 tan
{1,0,{pysm::ch,pyym::ao}},//潮 chao
{2,1740,{pysm::nop,pyym::nop}},//潯 xun
{2,1741,{pysm::nop,pyym::nop}},//潰 kui
{1,0,{pysm::y,pyym::e}},//潱 ye
{1,0,{pysm::sh,pyym::ao}},//潲 shao
{2,1742,{pysm::nop,pyym::nop}},//潳 tu
{1,0,{pysm::zh,pyym::u}},//潴 zhu
{2,1743,{pysm::nop,pyym::nop}},//潵 sa
{1,0,{pysm::h,pyym::ei}},//潶 hei
{1,0,{pysm::b,pyym::i}},//潷 bi
{1,0,{pysm::sh,pyym::an}},//潸 shan
{1,0,{pysm::ch,pyym::an}},//潹 chan
{1,0,{pysm::ch,pyym::an}},//潺 chan
{1,0,{pysm::sh,pyym::u}},//潻 shu
{3,429,{pysm::nop,pyym::nop}},//潼 tong
{1,0,{pysm::p,pyym::u}},//潽 pu
{1,0,{pysm::l,pyym::in}},//潾 lin
{1,0,{pysm::w,pyym::ei}},//潿 wei
{1,0,{pysm::s,pyym::e}},//澀 se
{1,0,{pysm::s,pyym::e}},//澁 se
{1,0,{pysm::ch,pyym::eng}},//澂 cheng
{1,0,{pysm::j,pyym::iong}},//澃 jiong
{2,1744,{pysm::nop,pyym::nop}},//澄 cheng
{1,0,{pysm::h,pyym::ua}},//澅 hua
{3,430,{pysm::nop,pyym::nop}},//澆 jiao
{1,0,{pysm::l,pyym::ao}},//澇 lao
{1,0,{pysm::ch,pyym::e}},//澈 che
{2,1745,{pysm::nop,pyym::nop}},//澉 gan
{1,0,{pysm::c,pyym::un}},//澊 cun
{1,0,{pysm::h,pyym::ong}},//澋 hong
{1,0,{pysm::s,pyym::i}},//澌 si
{2,1746,{pysm::nop,pyym::nop}},//澍 shu
{1,0,{pysm::p,pyym::eng}},//澎 peng
{1,0,{pysm::h,pyym::an}},//澏 han
{1,0,{pysm::y,pyym::un}},//澐 yun
{1,0,{pysm::l,pyym::iu}},//澑 liu
{1,0,{pysm::h,pyym::ong}},//澒 hong
{1,0,{pysm::f,pyym::u}},//澓 fu
{1,0,{pysm::h,pyym::ao}},//澔 hao
{1,0,{pysm::h,pyym::e}},//澕 he
{1,0,{pysm::x,pyym::ian}},//澖 xian
{1,0,{pysm::j,pyym::ian}},//澗 jian
{1,0,{pysm::sh,pyym::an}},//澘 shan
{1,0,{pysm::x,pyym::i}},//澙 xi
{1,0,{pysm::y,pyym::u}},//澚 yu
{1,0,{pysm::l,pyym::u}},//澛 lu
{1,0,{pysm::l,pyym::an}},//澜 lan
{1,0,{pysm::n,pyym::ing}},//澝 ning
{1,0,{pysm::y,pyym::u}},//澞 yu
{1,0,{pysm::l,pyym::in}},//澟 lin
{2,1747,{pysm::nop,pyym::nop}},//澠 mian
{2,1748,{pysm::nop,pyym::nop}},//澡 zao
{1,0,{pysm::d,pyym::ang}},//澢 dang
{2,1749,{pysm::nop,pyym::nop}},//澣 huan
{4,92,{pysm::nop,pyym::nop}},//澤 ze
{1,0,{pysm::x,pyym::ie}},//澥 xie
{1,0,{pysm::y,pyym::u}},//澦 yu
{1,0,{pysm::l,pyym::i}},//澧 li
{2,1750,{pysm::nop,pyym::nop}},//澨 shi
{2,1751,{pysm::nop,pyym::nop}},//澩 xue
{1,0,{pysm::l,pyym::ing}},//澪 ling
{3,431,{pysm::nop,pyym::nop}},//澫 wan
{2,1752,{pysm::nop,pyym::nop}},//澬 zi
{1,0,{pysm::y,pyym::ong}},//澭 yong
{3,432,{pysm::nop,pyym::nop}},//澮 hui
{1,0,{pysm::c,pyym::an}},//澯 can
{1,0,{pysm::l,pyym::ian}},//澰 lian
{1,0,{pysm::d,pyym::ian}},//澱 dian
{1,0,{pysm::y,pyym::e}},//澲 ye
{2,1753,{pysm::nop,pyym::nop}},//澳 ao
{2,1754,{pysm::nop,pyym::nop}},//澴 huan
{1,0,{pysm::zh,pyym::en}},//澵 zhen
{3,433,{pysm::nop,pyym::nop}},//澶 chan
{1,0,{pysm::m,pyym::an}},//澷 man
{1,0,{pysm::d,pyym::an}},//澸 dan
{3,434,{pysm::nop,pyym::nop}},//澹 dan
{1,0,{pysm::y,pyym::i}},//澺 yi
{1,0,{pysm::s,pyym::ui}},//澻 sui
{1,0,{pysm::p,pyym::i}},//澼 pi
{1,0,{pysm::j,pyym::u}},//澽 ju
{1,0,{pysm::t,pyym::a}},//澾 ta
{1,0,{pysm::q,pyym::in}},//澿 qin
{2,1755,{pysm::nop,pyym::nop}},//激 ji
{1,0,{pysm::zh,pyym::uo}},//濁 zhuo
{2,1756,{pysm::nop,pyym::nop}},//濂 lian
{1,0,{pysm::n,pyym::ong}},//濃 nong
{2,1757,{pysm::nop,pyym::nop}},//濄 guo
{1,0,{pysm::j,pyym::in}},//濅 jin
{2,1758,{pysm::nop,pyym::nop}},//濆 fen
{1,0,{pysm::s,pyym::e}},//濇 se
{2,1759,{pysm::nop,pyym::nop}},//濈 ji
{1,0,{pysm::s,pyym::ui}},//濉 sui
{3,435,{pysm::nop,pyym::nop}},//濊 hui
{1,0,{pysm::ch,pyym::u}},//濋 chu
{1,0,{pysm::t,pyym::a}},//濌 ta
{1,0,{pysm::s,pyym::ong}},//濍 song
{2,1760,{pysm::nop,pyym::nop}},//濎 ding
{1,0,{pysm::s,pyym::e}},//濏 se
{1,0,{pysm::zh,pyym::u}},//濐 zhu
{1,0,{pysm::l,pyym::ai}},//濑 lai
{1,0,{pysm::b,pyym::in}},//濒 bin
{1,0,{pysm::l,pyym::ian}},//濓 lian
{2,1761,{pysm::nop,pyym::nop}},//濔 mi
{3,436,{pysm::nop,pyym::nop}},//濕 shi
{1,0,{pysm::sh,pyym::u}},//濖 shu
{1,0,{pysm::m,pyym::i}},//濗 mi
{2,1762,{pysm::nop,pyym::nop}},//濘 ning
{1,0,{pysm::y,pyym::ing}},//濙 ying
{1,0,{pysm::y,pyym::ing}},//濚 ying
{1,0,{pysm::m,pyym::eng}},//濛 meng
{1,0,{pysm::j,pyym::in}},//濜 jin
{1,0,{pysm::q,pyym::i}},//濝 qi
{2,1763,{pysm::nop,pyym::nop}},//濞 bi
{2,1764,{pysm::nop,pyym::nop}},//濟 ji
{1,0,{pysm::h,pyym::ao}},//濠 hao
{5,31,{pysm::nop,pyym::nop}},//濡 ru
{2,1765,{pysm::nop,pyym::nop}},//濢 cui
{1,0,{pysm::w,pyym::o}},//濣 wo
{4,93,{pysm::nop,pyym::nop}},//濤 tao
{1,0,{pysm::y,pyym::in}},//濥 yin
{1,0,{pysm::y,pyym::in}},//濦 yin
{1,0,{pysm::d,pyym::ui}},//濧 dui
{1,0,{pysm::c,pyym::i}},//濨 ci
{2,1766,{pysm::nop,pyym::nop}},//濩 huo
{1,0,{pysm::q,pyym::ing}},//濪 qing
{2,1767,{pysm::nop,pyym::nop}},//濫 lan
{2,1768,{pysm::nop,pyym::nop}},//濬 jun
{3,437,{pysm::nop,pyym::nop}},//濭 ai
{1,0,{pysm::p,pyym::u}},//濮 pu
{3,438,{pysm::nop,pyym::nop}},//濯 zhuo
{1,0,{pysm::w,pyym::ei}},//濰 wei
{1,0,{pysm::b,pyym::in}},//濱 bin
{1,0,{pysm::g,pyym::u}},//濲 gu
{1,0,{pysm::q,pyym::ian}},//濳 qian
{1,0,{pysm::y,pyym::ing}},//濴 ying
{1,0,{pysm::b,pyym::in}},//濵 bin
{1,0,{pysm::k,pyym::uo}},//濶 kuo
{1,0,{pysm::f,pyym::ei}},//濷 fei
{1,0,{pysm::c,pyym::ang}},//濸 cang
{1,0,{pysm::m,pyym::e}},//濹 me
{2,1769,{pysm::nop,pyym::nop}},//濺 jian
{1,0,{pysm::w,pyym::ei}},//濻 wei
{3,439,{pysm::nop,pyym::nop}},//濼 luo
{1,0,{pysm::z,pyym::an}},//濽 zan
{1,0,{pysm::l,pyym::v}},//濾 lü
{1,0,{pysm::l,pyym::i}},//濿 li
{1,0,{pysm::y,pyym::ou}},//瀀 you
{1,0,{pysm::y,pyym::ang}},//瀁 yang
{1,0,{pysm::l,pyym::u}},//瀂 lu
{1,0,{pysm::s,pyym::i}},//瀃 si
{1,0,{pysm::zh,pyym::i}},//瀄 zhi
{2,1770,{pysm::nop,pyym::nop}},//瀅 ying
{2,1771,{pysm::nop,pyym::nop}},//瀆 du
{1,0,{pysm::w,pyym::ang}},//瀇 wang
{1,0,{pysm::h,pyym::ui}},//瀈 hui
{1,0,{pysm::x,pyym::ie}},//瀉 xie
{1,0,{pysm::p,pyym::an}},//瀊 pan
{3,440,{pysm::nop,pyym::nop}},//瀋 shen
{1,0,{pysm::b,pyym::iao}},//瀌 biao
{1,0,{pysm::ch,pyym::an}},//瀍 chan
{2,1772,{pysm::nop,pyym::nop}},//瀎 mo
{1,0,{pysm::l,pyym::iu}},//瀏 liu
{1,0,{pysm::j,pyym::ian}},//瀐 jian
{3,441,{pysm::nop,pyym::nop}},//瀑 pu
{1,0,{pysm::s,pyym::e}},//瀒 se
{1,0,{pysm::ch,pyym::eng}},//瀓 cheng
{1,0,{pysm::g,pyym::u}},//瀔 gu
{1,0,{pysm::b,pyym::in}},//瀕 bin
{1,0,{pysm::h,pyym::uo}},//瀖 huo
{1,0,{pysm::x,pyym::ian}},//瀗 xian
{1,0,{pysm::l,pyym::u}},//瀘 lu
{1,0,{pysm::q,pyym::in}},//瀙 qin
{1,0,{pysm::h,pyym::an}},//瀚 han
{1,0,{pysm::y,pyym::ing}},//瀛 ying
{1,0,{pysm::r,pyym::ong}},//瀜 rong
{1,0,{pysm::l,pyym::i}},//瀝 li
{1,0,{pysm::j,pyym::ing}},//瀞 jing
{1,0,{pysm::x,pyym::iao}},//瀟 xiao
{1,0,{pysm::y,pyym::ing}},//瀠 ying
{1,0,{pysm::s,pyym::ui}},//瀡 sui
{2,1773,{pysm::nop,pyym::nop}},//瀢 wei
{1,0,{pysm::x,pyym::ie}},//瀣 xie
{2,1774,{pysm::nop,pyym::nop}},//瀤 huai
{1,0,{pysm::x,pyym::ue}},//瀥 xue
{1,0,{pysm::zh,pyym::u}},//瀦 zhu
{2,1775,{pysm::nop,pyym::nop}},//瀧 long
{1,0,{pysm::l,pyym::ai}},//瀨 lai
{1,0,{pysm::d,pyym::ui}},//瀩 dui
{1,0,{pysm::f,pyym::an}},//瀪 fan
{1,0,{pysm::h,pyym::u}},//瀫 hu
{1,0,{pysm::l,pyym::ai}},//瀬 lai
{1,0,{pysm::sh,pyym::u}},//瀭 shu
{1,0,{pysm::l,pyym::ing}},//瀮 ling
{1,0,{pysm::y,pyym::ing}},//瀯 ying
{2,1776,{pysm::nop,pyym::nop}},//瀰 mi
{1,0,{pysm::j,pyym::i}},//瀱 ji
{1,0,{pysm::l,pyym::ian}},//瀲 lian
{2,1777,{pysm::nop,pyym::nop}},//瀳 jian
{1,0,{pysm::y,pyym::ing}},//瀴 ying
{1,0,{pysm::f,pyym::en}},//瀵 fen
{1,0,{pysm::l,pyym::in}},//瀶 lin
{1,0,{pysm::y,pyym::i}},//瀷 yi
{1,0,{pysm::j,pyym::ian}},//瀸 jian
{2,1778,{pysm::nop,pyym::nop}},//瀹 yue
{1,0,{pysm::ch,pyym::an}},//瀺 chan
{1,0,{pysm::d,pyym::ai}},//瀻 dai
{2,1779,{pysm::nop,pyym::nop}},//瀼 rang
{1,0,{pysm::j,pyym::ian}},//瀽 jian
{1,0,{pysm::l,pyym::an}},//瀾 lan
{1,0,{pysm::f,pyym::an}},//瀿 fan
{1,0,{pysm::sh,pyym::uang}},//灀 shuang
{1,0,{pysm::y,pyym::uan}},//灁 yuan
{3,442,{pysm::nop,pyym::nop}},//灂 zhuo
{1,0,{pysm::f,pyym::eng}},//灃 feng
{2,1780,{pysm::nop,pyym::nop}},//灄 she
{1,0,{pysm::l,pyym::ei}},//灅 lei
{1,0,{pysm::l,pyym::an}},//灆 lan
{1,0,{pysm::c,pyym::ong}},//灇 cong
{1,0,{pysm::q,pyym::u}},//灈 qu
{1,0,{pysm::y,pyym::ong}},//灉 yong
{1,0,{pysm::q,pyym::ian}},//灊 qian
{1,0,{pysm::f,pyym::a}},//灋 fa
{2,1781,{pysm::nop,pyym::nop}},//灌 guan
{1,0,{pysm::j,pyym::ue}},//灍 jue
{1,0,{pysm::y,pyym::an}},//灎 yan
{1,0,{pysm::h,pyym::ao}},//灏 hao
{1,0,{pysm::y,pyym::ing}},//灐 ying
{5,32,{pysm::nop,pyym::nop}},//灑 sa
{4,94,{pysm::nop,pyym::nop}},//灒 zan
{1,0,{pysm::l,pyym::uan}},//灓 luan
{1,0,{pysm::y,pyym::an}},//灔 yan
{1,0,{pysm::l,pyym::i}},//灕 li
{1,0,{pysm::m,pyym::i}},//灖 mi
{1,0,{pysm::sh,pyym::an}},//灗 shan
{3,443,{pysm::nop,pyym::nop}},//灘 tan
{1,0,{pysm::d,pyym::ang}},//灙 dang
{1,0,{pysm::j,pyym::iao}},//灚 jiao
{1,0,{pysm::ch,pyym::an}},//灛 chan
{1,0,{pysm::y,pyym::ing}},//灜 ying
{1,0,{pysm::h,pyym::ao}},//灝 hao
{1,0,{pysm::b,pyym::a}},//灞 ba
{1,0,{pysm::zh,pyym::u}},//灟 zhu
{1,0,{pysm::l,pyym::an}},//灠 lan
{1,0,{pysm::l,pyym::an}},//灡 lan
{1,0,{pysm::n,pyym::ang}},//灢 nang
{1,0,{pysm::w,pyym::an}},//灣 wan
{1,0,{pysm::l,pyym::uan}},//灤 luan
{2,1782,{pysm::nop,pyym::nop}},//灥 xun
{1,0,{pysm::x,pyym::ian}},//灦 xian
{1,0,{pysm::y,pyym::an}},//灧 yan
{1,0,{pysm::g,pyym::an}},//灨 gan
{1,0,{pysm::y,pyym::an}},//灩 yan
{1,0,{pysm::y,pyym::u}},//灪 yu
{1,0,{pysm::h,pyym::uo}},//火 huo
{2,1783,{pysm::nop,pyym::nop}},//灬 biao
{1,0,{pysm::m,pyym::ie}},//灭 mie
{1,0,{pysm::g,pyym::uang}},//灮 guang
{2,1784,{pysm::nop,pyym::nop}},//灯 deng
{1,0,{pysm::h,pyym::ui}},//灰 hui
{1,0,{pysm::x,pyym::iao}},//灱 xiao
{1,0,{pysm::x,pyym::iao}},//灲 xiao
{1,0,{pysm::h,pyym::ui}},//灳 hui
{1,0,{pysm::h,pyym::ong}},//灴 hong
{1,0,{pysm::l,pyym::ing}},//灵 ling
{1,0,{pysm::z,pyym::ao}},//灶 zao
{1,0,{pysm::zh,pyym::uan}},//灷 zhuan
{1,0,{pysm::j,pyym::iu}},//灸 jiu
{2,1785,{pysm::nop,pyym::nop}},//灹 zha
{1,0,{pysm::x,pyym::ie}},//灺 xie
{1,0,{pysm::ch,pyym::i}},//灻 chi
{1,0,{pysm::zh,pyym::uo}},//灼 zhuo
{1,0,{pysm::z,pyym::ai}},//災 zai
{1,0,{pysm::z,pyym::ai}},//灾 zai
{1,0,{pysm::c,pyym::an}},//灿 can
{1,0,{pysm::y,pyym::ang}},//炀 yang
{1,0,{pysm::q,pyym::i}},//炁 qi
{1,0,{pysm::zh,pyym::ong}},//炂 zhong
{2,1786,{pysm::nop,pyym::nop}},//炃 fen
{1,0,{pysm::n,pyym::iu}},//炄 niu
{2,1787,{pysm::nop,pyym::nop}},//炅 jiong
{1,0,{pysm::w,pyym::en}},//炆 wen
{1,0,{pysm::p,pyym::u}},//炇 pu
{1,0,{pysm::y,pyym::i}},//炈 yi
{1,0,{pysm::l,pyym::u}},//炉 lu
{1,0,{pysm::ch,pyym::ui}},//炊 chui
{1,0,{pysm::p,pyym::i}},//炋 pi
{1,0,{pysm::k,pyym::ai}},//炌 kai
{1,0,{pysm::p,pyym::an}},//炍 pan
{2,1788,{pysm::nop,pyym::nop}},//炎 yan
{2,1789,{pysm::nop,pyym::nop}},//炏 kai
{2,1790,{pysm::nop,pyym::nop}},//炐 pang
{1,0,{pysm::m,pyym::u}},//炑 mu
{1,0,{pysm::ch,pyym::ao}},//炒 chao
{1,0,{pysm::l,pyym::iao}},//炓 liao
{3,444,{pysm::nop,pyym::nop}},//炔 gui
{2,1791,{pysm::nop,pyym::nop}},//炕 kang
{2,1792,{pysm::nop,pyym::nop}},//炖 dun
{1,0,{pysm::g,pyym::uang}},//炗 guang
{1,0,{pysm::x,pyym::in}},//炘 xin
{1,0,{pysm::zh,pyym::i}},//炙 zhi
{1,0,{pysm::g,pyym::uang}},//炚 guang
{1,0,{pysm::g,pyym::uang}},//炛 guang
{1,0,{pysm::w,pyym::ei}},//炜 wei
{1,0,{pysm::q,pyym::iang}},//炝 qiang
{1,0,{pysm::b,pyym::ian}},//炞 bian
{1,0,{pysm::d,pyym::a}},//炟 da
{1,0,{pysm::x,pyym::ia}},//炠 xia
{1,0,{pysm::zh,pyym::eng}},//炡 zheng
{1,0,{pysm::zh,pyym::u}},//炢 zhu
{1,0,{pysm::k,pyym::e}},//炣 ke
{1,0,{pysm::zh,pyym::ao}},//炤 zhao
{1,0,{pysm::f,pyym::u}},//炥 fu
{1,0,{pysm::b,pyym::a}},//炦 ba
{1,0,{pysm::x,pyym::ie}},//炧 xie
{1,0,{pysm::x,pyym::ie}},//炨 xie
{1,0,{pysm::l,pyym::ing}},//炩 ling
{2,1793,{pysm::nop,pyym::nop}},//炪 zhuo
{1,0,{pysm::x,pyym::uan}},//炫 xuan
{1,0,{pysm::j,pyym::u}},//炬 ju
{1,0,{pysm::t,pyym::an}},//炭 tan
{2,1794,{pysm::nop,pyym::nop}},//炮 pao
{1,0,{pysm::j,pyym::iong}},//炯 jiong
{2,1795,{pysm::nop,pyym::nop}},//炰 pao
{1,0,{pysm::t,pyym::ai}},//炱 tai
{1,0,{pysm::t,pyym::ai}},//炲 tai
{1,0,{pysm::b,pyym::ing}},//炳 bing
{1,0,{pysm::y,pyym::ang}},//炴 yang
{1,0,{pysm::t,pyym::ong}},//炵 tong
{1,0,{pysm::sh,pyym::an}},//炶 shan
{1,0,{pysm::zh,pyym::u}},//炷 zhu
{1,0,{pysm::zh,pyym::a}},//炸 zha
{1,0,{pysm::d,pyym::ian}},//点 dian
{1,0,{pysm::w,pyym::ei}},//為 wei
{1,0,{pysm::sh,pyym::i}},//炻 shi
{1,0,{pysm::l,pyym::ian}},//炼 lian
{1,0,{pysm::ch,pyym::i}},//炽 chi
{1,0,{pysm::h,pyym::uang}},//炾 huang
{1,0,{pysm::zh,pyym::ou}},//炿 zhou
{1,0,{pysm::h,pyym::u}},//烀 hu
{1,0,{pysm::sh,pyym::uo}},//烁 shuo
{1,0,{pysm::l,pyym::an}},//烂 lan
{1,0,{pysm::t,pyym::ing}},//烃 ting
{2,1796,{pysm::nop,pyym::nop}},//烄 jiao
{1,0,{pysm::x,pyym::u}},//烅 xu
{1,0,{pysm::h,pyym::eng}},//烆 heng
{1,0,{pysm::q,pyym::uan}},//烇 quan
{1,0,{pysm::l,pyym::ie}},//烈 lie
{1,0,{pysm::h,pyym::uan}},//烉 huan
{1,0,{pysm::y,pyym::ang}},//烊 yang
{2,1797,{pysm::nop,pyym::nop}},//烋 xiu
{1,0,{pysm::x,pyym::iu}},//烌 xiu
{1,0,{pysm::x,pyym::ian}},//烍 xian
{1,0,{pysm::y,pyym::in}},//烎 yin
{2,1798,{pysm::nop,pyym::nop}},//烏 wu
{1,0,{pysm::zh,pyym::ou}},//烐 zhou
{1,0,{pysm::y,pyym::ao}},//烑 yao
{1,0,{pysm::sh,pyym::i}},//烒 shi
{1,0,{pysm::w,pyym::ei}},//烓 wei
{2,1799,{pysm::nop,pyym::nop}},//烔 tong
{1,0,{pysm::m,pyym::ie}},//烕 mie
{1,0,{pysm::z,pyym::ai}},//烖 zai
{1,0,{pysm::k,pyym::ai}},//烗 kai
{1,0,{pysm::h,pyym::ong}},//烘 hong
{2,1800,{pysm::nop,pyym::nop}},//烙 lao
{1,0,{pysm::x,pyym::ia}},//烚 xia
{2,1801,{pysm::nop,pyym::nop}},//烛 zhu
{2,1802,{pysm::nop,pyym::nop}},//烜 xuan
{1,0,{pysm::zh,pyym::eng}},//烝 zheng
{1,0,{pysm::p,pyym::o}},//烞 po
{2,1803,{pysm::nop,pyym::nop}},//烟 yan
{2,1804,{pysm::nop,pyym::nop}},//烠 hui
{1,0,{pysm::g,pyym::uang}},//烡 guang
{1,0,{pysm::ch,pyym::e}},//烢 che
{1,0,{pysm::h,pyym::ui}},//烣 hui
{1,0,{pysm::k,pyym::ao}},//烤 kao
{1,0,{pysm::j,pyym::u}},//烥 ju
{1,0,{pysm::f,pyym::an}},//烦 fan
{1,0,{pysm::sh,pyym::ao}},//烧 shao
{1,0,{pysm::y,pyym::e}},//烨 ye
{1,0,{pysm::h,pyym::ui}},//烩 hui
{0,0,{pysm::nop,pyym::nop}},//烪 烪
{1,0,{pysm::t,pyym::ang}},//烫 tang
{1,0,{pysm::j,pyym::in}},//烬 jin
{1,0,{pysm::r,pyym::e}},//热 re
{1,0,{pysm::l,pyym::ie}},//烮 lie
{1,0,{pysm::x,pyym::i}},//烯 xi
{1,0,{pysm::f,pyym::u}},//烰 fu
{1,0,{pysm::j,pyym::iong}},//烱 jiong
{2,1805,{pysm::nop,pyym::nop}},//烲 xie
{1,0,{pysm::p,pyym::u}},//烳 pu
{2,1806,{pysm::nop,pyym::nop}},//烴 ting
{1,0,{pysm::zh,pyym::uo}},//烵 zhuo
{1,0,{pysm::t,pyym::ing}},//烶 ting
{1,0,{pysm::w,pyym::an}},//烷 wan
{1,0,{pysm::h,pyym::ai}},//烸 hai
{1,0,{pysm::p,pyym::eng}},//烹 peng
{1,0,{pysm::l,pyym::ang}},//烺 lang
{2,1807,{pysm::nop,pyym::nop}},//烻 yan
{1,0,{pysm::x,pyym::u}},//烼 xu
{1,0,{pysm::f,pyym::eng}},//烽 feng
{1,0,{pysm::ch,pyym::i}},//烾 chi
{1,0,{pysm::r,pyym::ong}},//烿 rong
{1,0,{pysm::h,pyym::u}},//焀 hu
{1,0,{pysm::x,pyym::i}},//焁 xi
{1,0,{pysm::sh,pyym::u}},//焂 shu
{2,1808,{pysm::nop,pyym::nop}},//焃 he
{2,1809,{pysm::nop,pyym::nop}},//焄 xun
{2,1810,{pysm::nop,pyym::nop}},//焅 ku
{4,95,{pysm::nop,pyym::nop}},//焆 juan
{1,0,{pysm::x,pyym::iao}},//焇 xiao
{1,0,{pysm::x,pyym::i}},//焈 xi
{2,1811,{pysm::nop,pyym::nop}},//焉 yan
{1,0,{pysm::h,pyym::an}},//焊 han
{1,0,{pysm::zh,pyym::uang}},//焋 zhuang
{2,1812,{pysm::nop,pyym::nop}},//焌 jun
{1,0,{pysm::d,pyym::i}},//焍 di
{1,0,{pysm::x,pyym::ie}},//焎 xie
{2,1813,{pysm::nop,pyym::nop}},//焏 ji
{1,0,{pysm::w,pyym::u}},//焐 wu
{1,0,{pysm::y,pyym::an}},//焑 yan
{1,0,{pysm::l,pyym::v}},//焒 lü
{1,0,{pysm::h,pyym::an}},//焓 han
{1,0,{pysm::y,pyym::an}},//焔 yan
{1,0,{pysm::h,pyym::uan}},//焕 huan
{1,0,{pysm::m,pyym::en}},//焖 men
{1,0,{pysm::j,pyym::u}},//焗 ju
{2,1814,{pysm::nop,pyym::nop}},//焘 dao
{1,0,{pysm::b,pyym::ei}},//焙 bei
{1,0,{pysm::f,pyym::en}},//焚 fen
{1,0,{pysm::l,pyym::in}},//焛 lin
{1,0,{pysm::k,pyym::un}},//焜 kun
{1,0,{pysm::h,pyym::un}},//焝 hun
{3,445,{pysm::nop,pyym::nop}},//焞 tun
{1,0,{pysm::x,pyym::i}},//焟 xi
{1,0,{pysm::c,pyym::ui}},//焠 cui
{2,1815,{pysm::nop,pyym::nop}},//無 wu
{1,0,{pysm::h,pyym::ong}},//焢 hong
{2,1816,{pysm::nop,pyym::nop}},//焣 chao
{1,0,{pysm::f,pyym::u}},//焤 fu
{2,1817,{pysm::nop,pyym::nop}},//焥 wo
{2,1818,{pysm::nop,pyym::nop}},//焦 jiao
{1,0,{pysm::c,pyym::ong}},//焧 cong
{1,0,{pysm::f,pyym::eng}},//焨 feng
{1,0,{pysm::p,pyym::ing}},//焩 ping
{1,0,{pysm::q,pyym::iong}},//焪 qiong
{2,1819,{pysm::nop,pyym::nop}},//焫 ruo
{2,1820,{pysm::nop,pyym::nop}},//焬 xi
{1,0,{pysm::q,pyym::iong}},//焭 qiong
{1,0,{pysm::x,pyym::in}},//焮 xin
{3,446,{pysm::nop,pyym::nop}},//焯 chao
{1,0,{pysm::y,pyym::an}},//焰 yan
{2,1821,{pysm::nop,pyym::nop}},//焱 yan
{1,0,{pysm::y,pyym::i}},//焲 yi
{1,0,{pysm::j,pyym::ue}},//焳 jue
{1,0,{pysm::y,pyym::u}},//焴 yu
{1,0,{pysm::g,pyym::ang}},//焵 gang
{1,0,{pysm::r,pyym::an}},//然 ran
{1,0,{pysm::p,pyym::i}},//焷 pi
{3,447,{pysm::nop,pyym::nop}},//焸 xiong
{1,0,{pysm::g,pyym::ang}},//焹 gang
{1,0,{pysm::sh,pyym::eng}},//焺 sheng
{2,1822,{pysm::nop,pyym::nop}},//焻 chang
{1,0,{pysm::sh,pyym::ao}},//焼 shao
{1,0,{pysm::x,pyym::iong}},//焽 xiong
{1,0,{pysm::n,pyym::ian}},//焾 nian
{1,0,{pysm::g,pyym::eng}},//焿 geng
{1,0,{pysm::w,pyym::ei}},//煀 wei
{1,0,{pysm::ch,pyym::en}},//煁 chen
{1,0,{pysm::h,pyym::e}},//煂 he
{1,0,{pysm::k,pyym::ui}},//煃 kui
{1,0,{pysm::zh,pyym::ong}},//煄 zhong
{1,0,{pysm::d,pyym::uan}},//煅 duan
{1,0,{pysm::x,pyym::ia}},//煆 xia
{5,33,{pysm::nop,pyym::nop}},//煇 hui
{1,0,{pysm::f,pyym::eng}},//煈 feng
{2,1823,{pysm::nop,pyym::nop}},//煉 lian
{1,0,{pysm::x,pyym::uan}},//煊 xuan
{1,0,{pysm::x,pyym::ing}},//煋 xing
{1,0,{pysm::h,pyym::uang}},//煌 huang
{1,0,{pysm::j,pyym::iao}},//煍 jiao
{1,0,{pysm::j,pyym::ian}},//煎 jian
{1,0,{pysm::b,pyym::i}},//煏 bi
{1,0,{pysm::y,pyym::ing}},//煐 ying
{1,0,{pysm::zh,pyym::u}},//煑 zhu
{2,1824,{pysm::nop,pyym::nop}},//煒 wei
{1,0,{pysm::t,pyym::uan}},//煓 tuan
{2,1825,{pysm::nop,pyym::nop}},//煔 shan
{1,0,{pysm::x,pyym::i}},//煕 xi
{2,1826,{pysm::nop,pyym::nop}},//煖 nuan
{1,0,{pysm::n,pyym::uan}},//煗 nuan
{1,0,{pysm::ch,pyym::an}},//煘 chan
{1,0,{pysm::y,pyym::an}},//煙 yan
{1,0,{pysm::j,pyym::iong}},//煚 jiong
{1,0,{pysm::j,pyym::iong}},//煛 jiong
{1,0,{pysm::y,pyym::u}},//煜 yu
{1,0,{pysm::m,pyym::ei}},//煝 mei
{1,0,{pysm::sh,pyym::a}},//煞 sha
{1,0,{pysm::w,pyym::ei}},//煟 wei
{2,1827,{pysm::nop,pyym::nop}},//煠 zha
{1,0,{pysm::j,pyym::in}},//煡 jin
{1,0,{pysm::q,pyym::iong}},//煢 qiong
{1,0,{pysm::r,pyym::ou}},//煣 rou
{1,0,{pysm::m,pyym::ei}},//煤 mei
{1,0,{pysm::h,pyym::uan}},//煥 huan
{2,1828,{pysm::nop,pyym::nop}},//煦 xu
{1,0,{pysm::zh,pyym::ao}},//照 zhao
{2,1829,{pysm::nop,pyym::nop}},//煨 wei
{1,0,{pysm::f,pyym::an}},//煩 fan
{1,0,{pysm::q,pyym::iu}},//煪 qiu
{1,0,{pysm::s,pyym::ui}},//煫 sui
{1,0,{pysm::y,pyym::ang}},//煬 yang
{1,0,{pysm::l,pyym::ie}},//煭 lie
{1,0,{pysm::zh,pyym::u}},//煮 zhu
{1,0,{pysm::j,pyym::ie}},//煯 jie
{1,0,{pysm::z,pyym::ao}},//煰 zao
{1,0,{pysm::g,pyym::ua}},//煱 gua
{1,0,{pysm::b,pyym::ao}},//煲 bao
{1,0,{pysm::h,pyym::u}},//煳 hu
{2,1830,{pysm::nop,pyym::nop}},//煴 yun
{1,0,{pysm::n,pyym::an}},//煵 nan
{1,0,{pysm::sh,pyym::i}},//煶 shi
{1,0,{pysm::l,pyym::iang}},//煷 liang
{1,0,{pysm::b,pyym::ian}},//煸 bian
{1,0,{pysm::g,pyym::ou}},//煹 gou
{1,0,{pysm::t,pyym::ui}},//煺 tui
{1,0,{pysm::t,pyym::ang}},//煻 tang
{1,0,{pysm::ch,pyym::ao}},//煼 chao
{1,0,{pysm::sh,pyym::an}},//煽 shan
{2,1831,{pysm::nop,pyym::nop}},//煾 en
{1,0,{pysm::b,pyym::o}},//煿 bo
{2,1832,{pysm::nop,pyym::nop}},//熀 huang
{1,0,{pysm::x,pyym::ie}},//熁 xie
{1,0,{pysm::x,pyym::i}},//熂 xi
{1,0,{pysm::w,pyym::u}},//熃 wu
{1,0,{pysm::x,pyym::i}},//熄 xi
{1,0,{pysm::y,pyym::un}},//熅 yun
{1,0,{pysm::h,pyym::e}},//熆 he
{3,448,{pysm::nop,pyym::nop}},//熇 he
{1,0,{pysm::x,pyym::i}},//熈 xi
{1,0,{pysm::y,pyym::un}},//熉 yun
{1,0,{pysm::x,pyym::iong}},//熊 xiong
{1,0,{pysm::n,pyym::ai}},//熋 nai
{1,0,{pysm::sh,pyym::an}},//熌 shan
{1,0,{pysm::q,pyym::iong}},//熍 qiong
{1,0,{pysm::y,pyym::ao}},//熎 yao
{1,0,{pysm::x,pyym::un}},//熏 xun
{1,0,{pysm::m,pyym::i}},//熐 mi
{2,1833,{pysm::nop,pyym::nop}},//熑 lian
{3,449,{pysm::nop,pyym::nop}},//熒 ying
{1,0,{pysm::w,pyym::u}},//熓 wu
{1,0,{pysm::r,pyym::ong}},//熔 rong
{1,0,{pysm::g,pyym::ong}},//熕 gong
{1,0,{pysm::y,pyym::an}},//熖 yan
{1,0,{pysm::q,pyym::iang}},//熗 qiang
{1,0,{pysm::l,pyym::iu}},//熘 liu
{2,1834,{pysm::nop,pyym::nop}},//熙 xi
{1,0,{pysm::b,pyym::i}},//熚 bi
{1,0,{pysm::b,pyym::iao}},//熛 biao
{2,1835,{pysm::nop,pyym::nop}},//熜 cong
{2,1836,{pysm::nop,pyym::nop}},//熝 lu
{1,0,{pysm::j,pyym::ian}},//熞 jian
{2,1837,{pysm::nop,pyym::nop}},//熟 shu
{1,0,{pysm::y,pyym::i}},//熠 yi
{1,0,{pysm::l,pyym::ou}},//熡 lou
{3,450,{pysm::nop,pyym::nop}},//熢 peng
{2,1838,{pysm::nop,pyym::nop}},//熣 sui
{1,0,{pysm::y,pyym::i}},//熤 yi
{2,1839,{pysm::nop,pyym::nop}},//熥 teng
{1,0,{pysm::j,pyym::ue}},//熦 jue
{1,0,{pysm::z,pyym::ong}},//熧 zong
{3,451,{pysm::nop,pyym::nop}},//熨 yun
{1,0,{pysm::h,pyym::u}},//熩 hu
{1,0,{pysm::y,pyym::i}},//熪 yi
{1,0,{pysm::zh,pyym::i}},//熫 zhi
{1,0,{pysm::nop,pyym::ao}},//熬 ao
{1,0,{pysm::w,pyym::ei}},//熭 wei
{1,0,{pysm::l,pyym::iu}},//熮 liu
{2,1840,{pysm::nop,pyym::nop}},//熯 han
{1,0,{pysm::nop,pyym::ou}},//熰 ou
{1,0,{pysm::r,pyym::e}},//熱 re
{1,0,{pysm::j,pyym::iong}},//熲 jiong
{1,0,{pysm::m,pyym::an}},//熳 man
{1,0,{pysm::k,pyym::un}},//熴 kun
{1,0,{pysm::sh,pyym::ang}},//熵 shang
{1,0,{pysm::c,pyym::uan}},//熶 cuan
{1,0,{pysm::z,pyym::eng}},//熷 zeng
{1,0,{pysm::j,pyym::ian}},//熸 jian
{1,0,{pysm::x,pyym::i}},//熹 xi
{1,0,{pysm::x,pyym::i}},//熺 xi
{1,0,{pysm::x,pyym::i}},//熻 xi
{1,0,{pysm::y,pyym::i}},//熼 yi
{1,0,{pysm::x,pyym::iao}},//熽 xiao
{1,0,{pysm::ch,pyym::i}},//熾 chi
{1,0,{pysm::h,pyym::uang}},//熿 huang
{2,1841,{pysm::nop,pyym::nop}},//燀 chan
{1,0,{pysm::y,pyym::e}},//燁 ye
{3,452,{pysm::nop,pyym::nop}},//燂 tan
{1,0,{pysm::r,pyym::an}},//燃 ran
{1,0,{pysm::y,pyym::an}},//燄 yan
{1,0,{pysm::x,pyym::un}},//燅 xun
{2,1842,{pysm::nop,pyym::nop}},//燆 qiao
{1,0,{pysm::j,pyym::un}},//燇 jun
{1,0,{pysm::d,pyym::eng}},//燈 deng
{2,1843,{pysm::nop,pyym::nop}},//燉 dun
{1,0,{pysm::sh,pyym::en}},//燊 shen
{4,96,{pysm::nop,pyym::nop}},//燋 jiao
{2,1844,{pysm::nop,pyym::nop}},//燌 fen
{2,1845,{pysm::nop,pyym::nop}},//燍 si
{1,0,{pysm::l,pyym::iao}},//燎 liao
{1,0,{pysm::y,pyym::u}},//燏 yu
{1,0,{pysm::l,pyym::in}},//燐 lin
{1,0,{pysm::t,pyym::ong}},//燑 tong
{1,0,{pysm::sh,pyym::ao}},//燒 shao
{1,0,{pysm::f,pyym::en}},//燓 fen
{2,1846,{pysm::nop,pyym::nop}},//燔 fan
{1,0,{pysm::y,pyym::an}},//燕 yan
{2,1847,{pysm::nop,pyym::nop}},//燖 xun
{1,0,{pysm::l,pyym::an}},//燗 lan
{1,0,{pysm::m,pyym::ei}},//燘 mei
{2,1848,{pysm::nop,pyym::nop}},//燙 tang
{1,0,{pysm::y,pyym::i}},//燚 yi
{1,0,{pysm::j,pyym::iong}},//燛 jiong
{1,0,{pysm::m,pyym::en}},//燜 men
{1,0,{pysm::j,pyym::ing}},//燝 jing
{1,0,{pysm::j,pyym::iao}},//燞 jiao
{2,1849,{pysm::nop,pyym::nop}},//營 ying
{2,1850,{pysm::nop,pyym::nop}},//燠 yu
{1,0,{pysm::y,pyym::i}},//燡 yi
{1,0,{pysm::x,pyym::ue}},//燢 xue
{1,0,{pysm::l,pyym::an}},//燣 lan
{2,1851,{pysm::nop,pyym::nop}},//燤 tai
{2,1852,{pysm::nop,pyym::nop}},//燥 zao
{1,0,{pysm::c,pyym::an}},//燦 can
{1,0,{pysm::s,pyym::ui}},//燧 sui
{1,0,{pysm::x,pyym::i}},//燨 xi
{1,0,{pysm::q,pyym::ue}},//燩 que
{1,0,{pysm::z,pyym::ong}},//燪 zong
{1,0,{pysm::l,pyym::ian}},//燫 lian
{1,0,{pysm::h,pyym::ui}},//燬 hui
{2,1853,{pysm::nop,pyym::nop}},//燭 zhu
{1,0,{pysm::x,pyym::ie}},//燮 xie
{1,0,{pysm::l,pyym::ing}},//燯 ling
{1,0,{pysm::w,pyym::ei}},//燰 wei
{1,0,{pysm::y,pyym::i}},//燱 yi
{1,0,{pysm::x,pyym::ie}},//燲 xie
{1,0,{pysm::zh,pyym::ao}},//燳 zhao
{1,0,{pysm::h,pyym::ui}},//燴 hui
{1,0,{pysm::d,pyym::a}},//燵 da
{1,0,{pysm::n,pyym::ong}},//燶 nong
{1,0,{pysm::l,pyym::an}},//燷 lan
{2,1854,{pysm::nop,pyym::nop}},//燸 ru
{2,1855,{pysm::nop,pyym::nop}},//燹 xian
{1,0,{pysm::h,pyym::e}},//燺 he
{1,0,{pysm::x,pyym::un}},//燻 xun
{1,0,{pysm::j,pyym::in}},//燼 jin
{1,0,{pysm::ch,pyym::ou}},//燽 chou
{2,1856,{pysm::nop,pyym::nop}},//燾 dao
{3,453,{pysm::nop,pyym::nop}},//燿 yao
{1,0,{pysm::h,pyym::e}},//爀 he
{1,0,{pysm::l,pyym::an}},//爁 lan
{1,0,{pysm::b,pyym::iao}},//爂 biao
{1,0,{pysm::r,pyym::ong}},//爃 rong
{2,1857,{pysm::nop,pyym::nop}},//爄 li
{1,0,{pysm::m,pyym::o}},//爅 mo
{2,1858,{pysm::nop,pyym::nop}},//爆 bao
{1,0,{pysm::r,pyym::uo}},//爇 ruo
{1,0,{pysm::l,pyym::v}},//爈 lü
{2,1859,{pysm::nop,pyym::nop}},//爉 la
{1,0,{pysm::nop,pyym::ao}},//爊 ao
{1,0,{pysm::x,pyym::un}},//爋 xun
{2,1860,{pysm::nop,pyym::nop}},//爌 kuang
{3,454,{pysm::nop,pyym::nop}},//爍 shuo
{1,0,{pysm::l,pyym::iao}},//爎 liao
{1,0,{pysm::l,pyym::i}},//爏 li
{1,0,{pysm::l,pyym::u}},//爐 lu
{1,0,{pysm::j,pyym::ue}},//爑 jue
{1,0,{pysm::l,pyym::iao}},//爒 liao
{2,1861,{pysm::nop,pyym::nop}},//爓 yan
{1,0,{pysm::x,pyym::i}},//爔 xi
{1,0,{pysm::x,pyym::ie}},//爕 xie
{1,0,{pysm::l,pyym::ong}},//爖 long
{1,0,{pysm::y,pyym::e}},//爗 ye
{1,0,{pysm::c,pyym::an}},//爘 can
{1,0,{pysm::r,pyym::ang}},//爙 rang
{1,0,{pysm::y,pyym::ue}},//爚 yue
{1,0,{pysm::l,pyym::an}},//爛 lan
{1,0,{pysm::c,pyym::ong}},//爜 cong
{2,1862,{pysm::nop,pyym::nop}},//爝 jue
{2,1863,{pysm::nop,pyym::nop}},//爞 chong
{1,0,{pysm::g,pyym::uan}},//爟 guan
{1,0,{pysm::j,pyym::u}},//爠 ju
{1,0,{pysm::ch,pyym::e}},//爡 che
{1,0,{pysm::m,pyym::i}},//爢 mi
{1,0,{pysm::t,pyym::ang}},//爣 tang
{1,0,{pysm::l,pyym::an}},//爤 lan
{1,0,{pysm::zh,pyym::u}},//爥 zhu
{1,0,{pysm::l,pyym::an}},//爦 lan
{1,0,{pysm::l,pyym::ing}},//爧 ling
{1,0,{pysm::c,pyym::uan}},//爨 cuan
{1,0,{pysm::y,pyym::u}},//爩 yu
{2,1864,{pysm::nop,pyym::nop}},//爪 zhao
{1,0,{pysm::zh,pyym::ao}},//爫 zhao
{1,0,{pysm::p,pyym::a}},//爬 pa
{1,0,{pysm::zh,pyym::eng}},//爭 zheng
{1,0,{pysm::p,pyym::ao}},//爮 pao
{1,0,{pysm::ch,pyym::eng}},//爯 cheng
{1,0,{pysm::y,pyym::uan}},//爰 yuan
{1,0,{pysm::nop,pyym::ai}},//爱 ai
{1,0,{pysm::w,pyym::ei}},//爲 wei
{1,0,{pysm::h,pyym::an}},//爳 han
{1,0,{pysm::j,pyym::ue}},//爴 jue
{1,0,{pysm::j,pyym::ue}},//爵 jue
{1,0,{pysm::f,pyym::u}},//父 fu
{1,0,{pysm::y,pyym::e}},//爷 ye
{1,0,{pysm::b,pyym::a}},//爸 ba
{1,0,{pysm::d,pyym::ie}},//爹 die
{1,0,{pysm::y,pyym::e}},//爺 ye
{2,1865,{pysm::nop,pyym::nop}},//爻 yao
{1,0,{pysm::z,pyym::u}},//爼 zu
{1,0,{pysm::sh,pyym::uang}},//爽 shuang
{3,455,{pysm::nop,pyym::nop}},//爾 er
{2,1866,{pysm::nop,pyym::nop}},//爿 pan
{1,0,{pysm::ch,pyym::uang}},//牀 chuang
{1,0,{pysm::k,pyym::e}},//牁 ke
{1,0,{pysm::z,pyym::ang}},//牂 zang
{1,0,{pysm::d,pyym::ie}},//牃 die
{1,0,{pysm::q,pyym::iang}},//牄 qiang
{1,0,{pysm::y,pyym::ong}},//牅 yong
{1,0,{pysm::q,pyym::iang}},//牆 qiang
{2,1867,{pysm::nop,pyym::nop}},//片 pian
{1,0,{pysm::b,pyym::an}},//版 ban
{1,0,{pysm::p,pyym::an}},//牉 pan
{1,0,{pysm::ch,pyym::ao}},//牊 chao
{1,0,{pysm::j,pyym::ian}},//牋 jian
{1,0,{pysm::p,pyym::ai}},//牌 pai
{1,0,{pysm::d,pyym::u}},//牍 du
{1,0,{pysm::ch,pyym::uang}},//牎 chuang
{1,0,{pysm::y,pyym::u}},//牏 yu
{1,0,{pysm::zh,pyym::a}},//牐 zha
{2,1868,{pysm::nop,pyym::nop}},//牑 bian
{1,0,{pysm::d,pyym::ie}},//牒 die
{2,1869,{pysm::nop,pyym::nop}},//牓 bang
{1,0,{pysm::b,pyym::o}},//牔 bo
{1,0,{pysm::ch,pyym::uang}},//牕 chuang
{1,0,{pysm::y,pyym::ou}},//牖 you
{1,0,{pysm::y,pyym::ou}},//牗 you
{1,0,{pysm::d,pyym::u}},//牘 du
{1,0,{pysm::y,pyym::a}},//牙 ya
{1,0,{pysm::ch,pyym::eng}},//牚 cheng
{1,0,{pysm::n,pyym::iu}},//牛 niu
{1,0,{pysm::n,pyym::iu}},//牜 niu
{1,0,{pysm::p,pyym::in}},//牝 pin
{2,1870,{pysm::nop,pyym::nop}},//牞 jiu
{3,456,{pysm::nop,pyym::nop}},//牟 mou
{2,1871,{pysm::nop,pyym::nop}},//牠 ta
{1,0,{pysm::m,pyym::u}},//牡 mu
{2,1872,{pysm::nop,pyym::nop}},//牢 lao
{1,0,{pysm::r,pyym::en}},//牣 ren
{1,0,{pysm::m,pyym::ang}},//牤 mang
{1,0,{pysm::f,pyym::ang}},//牥 fang
{1,0,{pysm::m,pyym::ao}},//牦 mao
{1,0,{pysm::m,pyym::u}},//牧 mu
{1,0,{pysm::g,pyym::ang}},//牨 gang
{1,0,{pysm::w,pyym::u}},//物 wu
{1,0,{pysm::y,pyym::an}},//牪 yan
{3,457,{pysm::nop,pyym::nop}},//牫 ge
{1,0,{pysm::b,pyym::ei}},//牬 bei
{1,0,{pysm::s,pyym::i}},//牭 si
{1,0,{pysm::j,pyym::ian}},//牮 jian
{1,0,{pysm::g,pyym::u}},//牯 gu
{2,1873,{pysm::nop,pyym::nop}},//牰 you
{1,0,{pysm::g,pyym::e}},//牱 ge
{1,0,{pysm::sh,pyym::eng}},//牲 sheng
{1,0,{pysm::m,pyym::u}},//牳 mu
{2,1874,{pysm::nop,pyym::nop}},//牴 di
{1,0,{pysm::q,pyym::ian}},//牵 qian
{1,0,{pysm::q,pyym::uan}},//牶 quan
{1,0,{pysm::q,pyym::uan}},//牷 quan
{1,0,{pysm::z,pyym::i}},//牸 zi
{1,0,{pysm::t,pyym::e}},//特 te
{1,0,{pysm::x,pyym::i}},//牺 xi
{1,0,{pysm::m,pyym::ang}},//牻 mang
{1,0,{pysm::k,pyym::eng}},//牼 keng
{1,0,{pysm::q,pyym::ian}},//牽 qian
{1,0,{pysm::w,pyym::u}},//牾 wu
{1,0,{pysm::g,pyym::u}},//牿 gu
{1,0,{pysm::x,pyym::i}},//犀 xi
{1,0,{pysm::l,pyym::i}},//犁 li
{1,0,{pysm::l,pyym::i}},//犂 li
{1,0,{pysm::p,pyym::ou}},//犃 pou
{2,1875,{pysm::nop,pyym::nop}},//犄 ji
{1,0,{pysm::g,pyym::ang}},//犅 gang
{2,1876,{pysm::nop,pyym::nop}},//犆 zhi
{1,0,{pysm::b,pyym::en}},//犇 ben
{1,0,{pysm::q,pyym::uan}},//犈 quan
{1,0,{pysm::ch,pyym::un}},//犉 chun
{1,0,{pysm::d,pyym::u}},//犊 du
{1,0,{pysm::j,pyym::u}},//犋 ju
{1,0,{pysm::j,pyym::ia}},//犌 jia
{2,1877,{pysm::nop,pyym::nop}},//犍 jian
{1,0,{pysm::f,pyym::eng}},//犎 feng
{1,0,{pysm::p,pyym::ian}},//犏 pian
{1,0,{pysm::k,pyym::e}},//犐 ke
{1,0,{pysm::j,pyym::u}},//犑 ju
{1,0,{pysm::k,pyym::ao}},//犒 kao
{1,0,{pysm::ch,pyym::u}},//犓 chu
{1,0,{pysm::x,pyym::i}},//犔 xi
{1,0,{pysm::b,pyym::ei}},//犕 bei
{1,0,{pysm::l,pyym::uo}},//犖 luo
{1,0,{pysm::j,pyym::ie}},//犗 jie
{1,0,{pysm::m,pyym::a}},//犘 ma
{1,0,{pysm::s,pyym::an}},//犙 san
{1,0,{pysm::w,pyym::ei}},//犚 wei
{2,1878,{pysm::nop,pyym::nop}},//犛 mao
{1,0,{pysm::d,pyym::un}},//犜 dun
{1,0,{pysm::t,pyym::ong}},//犝 tong
{1,0,{pysm::q,pyym::iao}},//犞 qiao
{1,0,{pysm::j,pyym::iang}},//犟 jiang
{1,0,{pysm::x,pyym::i}},//犠 xi
{1,0,{pysm::l,pyym::i}},//犡 li
{1,0,{pysm::d,pyym::u}},//犢 du
{1,0,{pysm::l,pyym::ie}},//犣 lie
{1,0,{pysm::p,pyym::ai}},//犤 pai
{2,1879,{pysm::nop,pyym::nop}},//犥 piao
{1,0,{pysm::b,pyym::o}},//犦 bo
{2,1880,{pysm::nop,pyym::nop}},//犧 xi
{1,0,{pysm::ch,pyym::ou}},//犨 chou
{1,0,{pysm::w,pyym::ei}},//犩 wei
{2,1881,{pysm::nop,pyym::nop}},//犪 kui
{1,0,{pysm::ch,pyym::ou}},//犫 chou
{1,0,{pysm::q,pyym::uan}},//犬 quan
{1,0,{pysm::q,pyym::uan}},//犭 quan
{1,0,{pysm::b,pyym::a}},//犮 ba
{1,0,{pysm::f,pyym::an}},//犯 fan
{1,0,{pysm::q,pyym::iu}},//犰 qiu
{1,0,{pysm::j,pyym::i}},//犱 ji
{1,0,{pysm::ch,pyym::ai}},//犲 chai
{1,0,{pysm::zh,pyym::uo}},//犳 zhuo
{3,458,{pysm::nop,pyym::nop}},//犴 an
{2,1882,{pysm::nop,pyym::nop}},//犵 ge
{1,0,{pysm::zh,pyym::uang}},//状 zhuang
{1,0,{pysm::g,pyym::uang}},//犷 guang
{1,0,{pysm::m,pyym::a}},//犸 ma
{1,0,{pysm::y,pyym::ou}},//犹 you
{2,1883,{pysm::nop,pyym::nop}},//犺 kang
{3,459,{pysm::nop,pyym::nop}},//犻 bo
{1,0,{pysm::h,pyym::ou}},//犼 hou
{1,0,{pysm::y,pyym::a}},//犽 ya
{1,0,{pysm::y,pyym::in}},//犾 yin
{2,1884,{pysm::nop,pyym::nop}},//犿 huan
{1,0,{pysm::zh,pyym::uang}},//狀 zhuang
{1,0,{pysm::y,pyym::un}},//狁 yun
{2,1885,{pysm::nop,pyym::nop}},//狂 kuang
{2,1886,{pysm::nop,pyym::nop}},//狃 niu
{2,1887,{pysm::nop,pyym::nop}},//狄 di
{1,0,{pysm::k,pyym::uang}},//狅 kuang
{1,0,{pysm::zh,pyym::ong}},//狆 zhong
{1,0,{pysm::m,pyym::u}},//狇 mu
{1,0,{pysm::b,pyym::ei}},//狈 bei
{1,0,{pysm::p,pyym::i}},//狉 pi
{1,0,{pysm::j,pyym::u}},//狊 ju
{3,460,{pysm::nop,pyym::nop}},//狋 yi
{2,1888,{pysm::nop,pyym::nop}},//狌 sheng
{1,0,{pysm::p,pyym::ao}},//狍 pao
{1,0,{pysm::x,pyym::ia}},//狎 xia
{2,1889,{pysm::nop,pyym::nop}},//狏 tuo
{1,0,{pysm::h,pyym::u}},//狐 hu
{1,0,{pysm::l,pyym::ing}},//狑 ling
{1,0,{pysm::f,pyym::ei}},//狒 fei
{1,0,{pysm::p,pyym::i}},//狓 pi
{1,0,{pysm::n,pyym::i}},//狔 ni
{1,0,{pysm::y,pyym::ao}},//狕 yao
{1,0,{pysm::y,pyym::ou}},//狖 you
{1,0,{pysm::g,pyym::ou}},//狗 gou
{1,0,{pysm::x,pyym::ue}},//狘 xue
{1,0,{pysm::j,pyym::u}},//狙 ju
{1,0,{pysm::d,pyym::an}},//狚 dan
{1,0,{pysm::b,pyym::o}},//狛 bo
{1,0,{pysm::k,pyym::u}},//狜 ku
{1,0,{pysm::x,pyym::ian}},//狝 xian
{1,0,{pysm::n,pyym::ing}},//狞 ning
{3,461,{pysm::nop,pyym::nop}},//狟 huan
{4,97,{pysm::nop,pyym::nop}},//狠 hen
{2,1890,{pysm::nop,pyym::nop}},//狡 jiao
{2,1891,{pysm::nop,pyym::nop}},//狢 he
{1,0,{pysm::zh,pyym::ao}},//狣 zhao
{3,462,{pysm::nop,pyym::nop}},//狤 ji
{1,0,{pysm::x,pyym::un}},//狥 xun
{1,0,{pysm::sh,pyym::an}},//狦 shan
{2,1892,{pysm::nop,pyym::nop}},//狧 ta
{1,0,{pysm::r,pyym::ong}},//狨 rong
{1,0,{pysm::sh,pyym::ou}},//狩 shou
{2,1893,{pysm::nop,pyym::nop}},//狪 tong
{1,0,{pysm::l,pyym::ao}},//狫 lao
{1,0,{pysm::d,pyym::u}},//独 du
{1,0,{pysm::x,pyym::ia}},//狭 xia
{1,0,{pysm::sh,pyym::i}},//狮 shi
{1,0,{pysm::k,pyym::uai}},//狯 kuai
{1,0,{pysm::zh,pyym::eng}},//狰 zheng
{1,0,{pysm::y,pyym::u}},//狱 yu
{1,0,{pysm::s,pyym::un}},//狲 sun
{1,0,{pysm::y,pyym::u}},//狳 yu
{1,0,{pysm::b,pyym::i}},//狴 bi
{2,1894,{pysm::nop,pyym::nop}},//狵 mang
{2,1895,{pysm::nop,pyym::nop}},//狶 xi
{1,0,{pysm::j,pyym::uan}},//狷 juan
{1,0,{pysm::l,pyym::i}},//狸 li
{1,0,{pysm::x,pyym::ia}},//狹 xia
{1,0,{pysm::y,pyym::in}},//狺 yin
{3,463,{pysm::nop,pyym::nop}},//狻 suan
{2,1896,{pysm::nop,pyym::nop}},//狼 lang
{1,0,{pysm::b,pyym::ei}},//狽 bei
{1,0,{pysm::zh,pyym::i}},//狾 zhi
{1,0,{pysm::y,pyym::an}},//狿 yan
{1,0,{pysm::sh,pyym::a}},//猀 sha
{1,0,{pysm::l,pyym::i}},//猁 li
{1,0,{pysm::h,pyym::an}},//猂 han
{1,0,{pysm::x,pyym::ian}},//猃 xian
{1,0,{pysm::j,pyym::ing}},//猄 jing
{1,0,{pysm::p,pyym::ai}},//猅 pai
{1,0,{pysm::f,pyym::ei}},//猆 fei
{1,0,{pysm::x,pyym::iao}},//猇 xiao
{2,1897,{pysm::nop,pyym::nop}},//猈 bai
{1,0,{pysm::q,pyym::i}},//猉 qi
{1,0,{pysm::n,pyym::i}},//猊 ni
{1,0,{pysm::b,pyym::iao}},//猋 biao
{1,0,{pysm::y,pyym::in}},//猌 yin
{1,0,{pysm::l,pyym::ai}},//猍 lai
{3,464,{pysm::nop,pyym::nop}},//猎 lie
{1,0,{pysm::j,pyym::ian}},//猏 jian
{1,0,{pysm::q,pyym::iang}},//猐 qiang
{1,0,{pysm::k,pyym::un}},//猑 kun
{1,0,{pysm::y,pyym::an}},//猒 yan
{2,1898,{pysm::nop,pyym::nop}},//猓 guo
{1,0,{pysm::z,pyym::ong}},//猔 zong
{1,0,{pysm::m,pyym::i}},//猕 mi
{1,0,{pysm::ch,pyym::ang}},//猖 chang
{4,98,{pysm::nop,pyym::nop}},//猗 yi
{1,0,{pysm::zh,pyym::i}},//猘 zhi
{1,0,{pysm::zh,pyym::eng}},//猙 zheng
{2,1899,{pysm::nop,pyym::nop}},//猚 ya
{1,0,{pysm::m,pyym::eng}},//猛 meng
{1,0,{pysm::c,pyym::ai}},//猜 cai
{1,0,{pysm::c,pyym::u}},//猝 cu
{1,0,{pysm::sh,pyym::e}},//猞 she
{1,0,{pysm::l,pyym::ie}},//猟 lie
{1,0,{pysm::d,pyym::ian}},//猠 dian
{1,0,{pysm::l,pyym::uo}},//猡 luo
{1,0,{pysm::h,pyym::u}},//猢 hu
{1,0,{pysm::z,pyym::ong}},//猣 zong
{1,0,{pysm::g,pyym::ui}},//猤 gui
{1,0,{pysm::w,pyym::ei}},//猥 wei
{1,0,{pysm::f,pyym::eng}},//猦 feng
{1,0,{pysm::w,pyym::o}},//猧 wo
{1,0,{pysm::y,pyym::uan}},//猨 yuan
{1,0,{pysm::x,pyym::ing}},//猩 xing
{1,0,{pysm::zh,pyym::u}},//猪 zhu
{2,1900,{pysm::nop,pyym::nop}},//猫 mao
{1,0,{pysm::w,pyym::ei}},//猬 wei
{2,1901,{pysm::nop,pyym::nop}},//猭 chuan
{1,0,{pysm::x,pyym::ian}},//献 xian
{1,0,{pysm::t,pyym::uan}},//猯 tuan
{3,465,{pysm::nop,pyym::nop}},//猰 ya
{1,0,{pysm::n,pyym::ao}},//猱 nao
{4,99,{pysm::nop,pyym::nop}},//猲 xie
{1,0,{pysm::j,pyym::ia}},//猳 jia
{1,0,{pysm::h,pyym::ou}},//猴 hou
{2,1902,{pysm::nop,pyym::nop}},//猵 bian
{2,1903,{pysm::nop,pyym::nop}},//猶 you
{1,0,{pysm::y,pyym::ou}},//猷 you
{1,0,{pysm::m,pyym::ei}},//猸 mei
{1,0,{pysm::ch,pyym::a}},//猹 cha
{1,0,{pysm::y,pyym::ao}},//猺 yao
{1,0,{pysm::s,pyym::un}},//猻 sun
{2,1904,{pysm::nop,pyym::nop}},//猼 bo
{1,0,{pysm::m,pyym::ing}},//猽 ming
{1,0,{pysm::h,pyym::ua}},//猾 hua
{1,0,{pysm::y,pyym::uan}},//猿 yuan
{1,0,{pysm::s,pyym::ou}},//獀 sou
{1,0,{pysm::m,pyym::a}},//獁 ma
{1,0,{pysm::y,pyym::uan}},//獂 yuan
{2,1905,{pysm::nop,pyym::nop}},//獃 dai
{1,0,{pysm::y,pyym::u}},//獄 yu
{1,0,{pysm::sh,pyym::i}},//獅 shi
{1,0,{pysm::h,pyym::ao}},//獆 hao
{1,0,{pysm::q,pyym::iang}},//獇 qiang
{1,0,{pysm::y,pyym::i}},//獈 yi
{1,0,{pysm::zh,pyym::en}},//獉 zhen
{1,0,{pysm::c,pyym::ang}},//獊 cang
{2,1906,{pysm::nop,pyym::nop}},//獋 hao
{1,0,{pysm::m,pyym::an}},//獌 man
{1,0,{pysm::j,pyym::ing}},//獍 jing
{1,0,{pysm::j,pyym::iang}},//獎 jiang
{2,1907,{pysm::nop,pyym::nop}},//獏 mo
{1,0,{pysm::zh,pyym::ang}},//獐 zhang
{1,0,{pysm::ch,pyym::an}},//獑 chan
{1,0,{pysm::nop,pyym::ao}},//獒 ao
{1,0,{pysm::nop,pyym::ao}},//獓 ao
{1,0,{pysm::h,pyym::ao}},//獔 hao
{1,0,{pysm::c,pyym::ui}},//獕 cui
{2,1908,{pysm::nop,pyym::nop}},//獖 ben
{1,0,{pysm::j,pyym::ue}},//獗 jue
{1,0,{pysm::b,pyym::i}},//獘 bi
{1,0,{pysm::b,pyym::i}},//獙 bi
{1,0,{pysm::h,pyym::uang}},//獚 huang
{1,0,{pysm::p,pyym::u}},//獛 pu
{1,0,{pysm::l,pyym::in}},//獜 lin
{2,1909,{pysm::nop,pyym::nop}},//獝 xu
{2,1910,{pysm::nop,pyym::nop}},//獞 tong
{2,1911,{pysm::nop,pyym::nop}},//獟 yao
{2,1912,{pysm::nop,pyym::nop}},//獠 liao
{1,0,{pysm::sh,pyym::uo}},//獡 shuo
{1,0,{pysm::x,pyym::iao}},//獢 xiao
{1,0,{pysm::sh,pyym::ou}},//獣 shou
{1,0,{pysm::d,pyym::un}},//獤 dun
{1,0,{pysm::j,pyym::iao}},//獥 jiao
{3,466,{pysm::nop,pyym::nop}},//獦 ge
{1,0,{pysm::j,pyym::uan}},//獧 juan
{1,0,{pysm::d,pyym::u}},//獨 du
{1,0,{pysm::h,pyym::ui}},//獩 hui
{2,1913,{pysm::nop,pyym::nop}},//獪 kuai
{1,0,{pysm::x,pyym::ian}},//獫 xian
{3,467,{pysm::nop,pyym::nop}},//獬 xie
{1,0,{pysm::t,pyym::a}},//獭 ta
{2,1914,{pysm::nop,pyym::nop}},//獮 xian
{1,0,{pysm::x,pyym::un}},//獯 xun
{1,0,{pysm::n,pyym::ing}},//獰 ning
{1,0,{pysm::b,pyym::ian}},//獱 bian
{1,0,{pysm::h,pyym::uo}},//獲 huo
{2,1915,{pysm::nop,pyym::nop}},//獳 nou
{1,0,{pysm::m,pyym::eng}},//獴 meng
{1,0,{pysm::l,pyym::ie}},//獵 lie
{2,1916,{pysm::nop,pyym::nop}},//獶 nao
{2,1917,{pysm::nop,pyym::nop}},//獷 guang
{1,0,{pysm::sh,pyym::ou}},//獸 shou
{1,0,{pysm::l,pyym::u}},//獹 lu
{1,0,{pysm::t,pyym::a}},//獺 ta
{3,468,{pysm::nop,pyym::nop}},//獻 xian
{1,0,{pysm::m,pyym::i}},//獼 mi
{1,0,{pysm::r,pyym::ang}},//獽 rang
{2,1918,{pysm::nop,pyym::nop}},//獾 huan
{1,0,{pysm::n,pyym::ao}},//獿 nao
{2,1919,{pysm::nop,pyym::nop}},//玀 luo
{1,0,{pysm::x,pyym::ian}},//玁 xian
{1,0,{pysm::q,pyym::i}},//玂 qi
{1,0,{pysm::j,pyym::ue}},//玃 jue
{1,0,{pysm::x,pyym::uan}},//玄 xuan
{2,1920,{pysm::nop,pyym::nop}},//玅 miao
{2,1921,{pysm::nop,pyym::nop}},//玆 zi
{3,469,{pysm::nop,pyym::nop}},//率 lü
{1,0,{pysm::l,pyym::u}},//玈 lu
{1,0,{pysm::y,pyym::u}},//玉 yu
{1,0,{pysm::s,pyym::u}},//玊 su
{2,1922,{pysm::nop,pyym::nop}},//王 wang
{1,0,{pysm::q,pyym::iu}},//玌 qiu
{1,0,{pysm::g,pyym::a}},//玍 ga
{1,0,{pysm::d,pyym::ing}},//玎 ding
{1,0,{pysm::l,pyym::e}},//玏 le
{1,0,{pysm::b,pyym::a}},//玐 ba
{1,0,{pysm::j,pyym::i}},//玑 ji
{1,0,{pysm::h,pyym::ong}},//玒 hong
{1,0,{pysm::d,pyym::i}},//玓 di
{1,0,{pysm::ch,pyym::uan}},//玔 chuan
{1,0,{pysm::g,pyym::an}},//玕 gan
{1,0,{pysm::j,pyym::iu}},//玖 jiu
{1,0,{pysm::y,pyym::u}},//玗 yu
{1,0,{pysm::q,pyym::i}},//玘 qi
{1,0,{pysm::y,pyym::u}},//玙 yu
{2,1923,{pysm::nop,pyym::nop}},//玚 chang
{1,0,{pysm::m,pyym::a}},//玛 ma
{1,0,{pysm::h,pyym::ong}},//玜 hong
{1,0,{pysm::w,pyym::u}},//玝 wu
{1,0,{pysm::f,pyym::u}},//玞 fu
{2,1924,{pysm::nop,pyym::nop}},//玟 wen
{1,0,{pysm::j,pyym::ie}},//玠 jie
{1,0,{pysm::y,pyym::a}},//玡 ya
{2,1925,{pysm::nop,pyym::nop}},//玢 bin
{1,0,{pysm::b,pyym::ian}},//玣 bian
{1,0,{pysm::b,pyym::ang}},//玤 bang
{1,0,{pysm::y,pyym::ue}},//玥 yue
{1,0,{pysm::j,pyym::ue}},//玦 jue
{2,1926,{pysm::nop,pyym::nop}},//玧 men
{1,0,{pysm::j,pyym::ue}},//玨 jue
{1,0,{pysm::w,pyym::an}},//玩 wan
{4,100,{pysm::nop,pyym::nop}},//玪 jian
{1,0,{pysm::m,pyym::ei}},//玫 mei
{1,0,{pysm::d,pyym::an}},//玬 dan
{1,0,{pysm::p,pyym::in}},//玭 pin
{1,0,{pysm::w,pyym::ei}},//玮 wei
{1,0,{pysm::h,pyym::uan}},//环 huan
{1,0,{pysm::x,pyym::ian}},//现 xian
{1,0,{pysm::q,pyym::iang}},//玱 qiang
{1,0,{pysm::l,pyym::ing}},//玲 ling
{1,0,{pysm::d,pyym::ai}},//玳 dai
{1,0,{pysm::y,pyym::i}},//玴 yi
{2,1927,{pysm::nop,pyym::nop}},//玵 an
{1,0,{pysm::p,pyym::ing}},//玶 ping
{1,0,{pysm::d,pyym::ian}},//玷 dian
{1,0,{pysm::f,pyym::u}},//玸 fu
{2,1928,{pysm::nop,pyym::nop}},//玹 xuan
{1,0,{pysm::x,pyym::i}},//玺 xi
{1,0,{pysm::b,pyym::o}},//玻 bo
{2,1929,{pysm::nop,pyym::nop}},//玼 ci
{1,0,{pysm::g,pyym::ou}},//玽 gou
{1,0,{pysm::j,pyym::ia}},//玾 jia
{1,0,{pysm::sh,pyym::ao}},//玿 shao
{1,0,{pysm::p,pyym::o}},//珀 po
{1,0,{pysm::c,pyym::i}},//珁 ci
{1,0,{pysm::k,pyym::e}},//珂 ke
{1,0,{pysm::r,pyym::an}},//珃 ran
{1,0,{pysm::sh,pyym::eng}},//珄 sheng
{1,0,{pysm::sh,pyym::en}},//珅 shen
{2,1930,{pysm::nop,pyym::nop}},//珆 yi
{2,1931,{pysm::nop,pyym::nop}},//珇 zu
{1,0,{pysm::j,pyym::ia}},//珈 jia
{1,0,{pysm::m,pyym::in}},//珉 min
{1,0,{pysm::sh,pyym::an}},//珊 shan
{1,0,{pysm::l,pyym::iu}},//珋 liu
{1,0,{pysm::b,pyym::i}},//珌 bi
{1,0,{pysm::zh,pyym::en}},//珍 zhen
{1,0,{pysm::zh,pyym::en}},//珎 zhen
{1,0,{pysm::j,pyym::ue}},//珏 jue
{1,0,{pysm::f,pyym::a}},//珐 fa
{1,0,{pysm::l,pyym::ong}},//珑 long
{1,0,{pysm::j,pyym::in}},//珒 jin
{1,0,{pysm::j,pyym::iao}},//珓 jiao
{1,0,{pysm::j,pyym::ian}},//珔 jian
{1,0,{pysm::l,pyym::i}},//珕 li
{1,0,{pysm::g,pyym::uang}},//珖 guang
{1,0,{pysm::x,pyym::ian}},//珗 xian
{1,0,{pysm::zh,pyym::ou}},//珘 zhou
{1,0,{pysm::g,pyym::ong}},//珙 gong
{1,0,{pysm::y,pyym::an}},//珚 yan
{1,0,{pysm::x,pyym::iu}},//珛 xiu
{1,0,{pysm::y,pyym::ang}},//珜 yang
{1,0,{pysm::x,pyym::u}},//珝 xu
{2,1932,{pysm::nop,pyym::nop}},//珞 luo
{1,0,{pysm::s,pyym::u}},//珟 su
{1,0,{pysm::zh,pyym::u}},//珠 zhu
{1,0,{pysm::q,pyym::in}},//珡 qin
{2,1933,{pysm::nop,pyym::nop}},//珢 yin
{1,0,{pysm::x,pyym::un}},//珣 xun
{1,0,{pysm::b,pyym::ao}},//珤 bao
{1,0,{pysm::nop,pyym::er}},//珥 er
{1,0,{pysm::x,pyym::iang}},//珦 xiang
{1,0,{pysm::y,pyym::ao}},//珧 yao
{1,0,{pysm::x,pyym::ia}},//珨 xia
{2,1934,{pysm::nop,pyym::nop}},//珩 hang
{1,0,{pysm::g,pyym::ui}},//珪 gui
{1,0,{pysm::ch,pyym::ong}},//珫 chong
{1,0,{pysm::x,pyym::u}},//珬 xu
{1,0,{pysm::b,pyym::an}},//班 ban
{1,0,{pysm::p,pyym::ei}},//珮 pei
{1,0,{pysm::l,pyym::ao}},//珯 lao
{1,0,{pysm::d,pyym::ang}},//珰 dang
{1,0,{pysm::y,pyym::ing}},//珱 ying
{2,1935,{pysm::nop,pyym::nop}},//珲 hui
{1,0,{pysm::w,pyym::en}},//珳 wen
{1,0,{pysm::nop,pyym::e}},//珴 e
{2,1936,{pysm::nop,pyym::nop}},//珵 cheng
{2,1937,{pysm::nop,pyym::nop}},//珶 di
{1,0,{pysm::w,pyym::u}},//珷 wu
{1,0,{pysm::w,pyym::u}},//珸 wu
{1,0,{pysm::ch,pyym::eng}},//珹 cheng
{1,0,{pysm::j,pyym::un}},//珺 jun
{1,0,{pysm::m,pyym::ei}},//珻 mei
{1,0,{pysm::b,pyym::ei}},//珼 bei
{1,0,{pysm::t,pyym::ing}},//珽 ting
{1,0,{pysm::x,pyym::ian}},//現 xian
{1,0,{pysm::ch,pyym::u}},//珿 chu
{1,0,{pysm::h,pyym::an}},//琀 han
{2,1938,{pysm::nop,pyym::nop}},//琁 xuan
{1,0,{pysm::y,pyym::an}},//琂 yan
{1,0,{pysm::q,pyym::iu}},//球 qiu
{1,0,{pysm::x,pyym::uan}},//琄 xuan
{1,0,{pysm::l,pyym::ang}},//琅 lang
{1,0,{pysm::l,pyym::i}},//理 li
{1,0,{pysm::x,pyym::iu}},//琇 xiu
{1,0,{pysm::f,pyym::u}},//琈 fu
{1,0,{pysm::l,pyym::iu}},//琉 liu
{1,0,{pysm::y,pyym::a}},//琊 ya
{1,0,{pysm::x,pyym::i}},//琋 xi
{1,0,{pysm::l,pyym::ing}},//琌 ling
{1,0,{pysm::l,pyym::i}},//琍 li
{1,0,{pysm::j,pyym::in}},//琎 jin
{1,0,{pysm::l,pyym::ian}},//琏 lian
{1,0,{pysm::s,pyym::uo}},//琐 suo
{1,0,{pysm::s,pyym::uo}},//琑 suo
{1,0,{pysm::f,pyym::eng}},//琒 feng
{1,0,{pysm::w,pyym::an}},//琓 wan
{1,0,{pysm::d,pyym::ian}},//琔 dian
{2,1939,{pysm::nop,pyym::nop}},//琕 pin
{1,0,{pysm::zh,pyym::an}},//琖 zhan
{2,1940,{pysm::nop,pyym::nop}},//琗 se
{1,0,{pysm::m,pyym::in}},//琘 min
{1,0,{pysm::y,pyym::u}},//琙 yu
{1,0,{pysm::j,pyym::u}},//琚 ju
{1,0,{pysm::ch,pyym::en}},//琛 chen
{1,0,{pysm::l,pyym::ai}},//琜 lai
{1,0,{pysm::m,pyym::in}},//琝 min
{2,1941,{pysm::nop,pyym::nop}},//琞 sheng
{2,1942,{pysm::nop,pyym::nop}},//琟 wei
{1,0,{pysm::t,pyym::ian}},//琠 tian
{1,0,{pysm::ch,pyym::u}},//琡 chu
{2,1943,{pysm::nop,pyym::nop}},//琢 zuo
{2,1944,{pysm::nop,pyym::nop}},//琣 beng
{1,0,{pysm::ch,pyym::eng}},//琤 cheng
{1,0,{pysm::h,pyym::u}},//琥 hu
{1,0,{pysm::q,pyym::i}},//琦 qi
{1,0,{pysm::nop,pyym::e}},//琧 e
{1,0,{pysm::k,pyym::un}},//琨 kun
{1,0,{pysm::ch,pyym::ang}},//琩 chang
{1,0,{pysm::q,pyym::i}},//琪 qi
{1,0,{pysm::b,pyym::eng}},//琫 beng
{1,0,{pysm::w,pyym::an}},//琬 wan
{1,0,{pysm::l,pyym::u}},//琭 lu
{1,0,{pysm::c,pyym::ong}},//琮 cong
{2,1945,{pysm::nop,pyym::nop}},//琯 guan
{1,0,{pysm::y,pyym::an}},//琰 yan
{1,0,{pysm::d,pyym::iao}},//琱 diao
{1,0,{pysm::b,pyym::ei}},//琲 bei
{1,0,{pysm::l,pyym::in}},//琳 lin
{1,0,{pysm::q,pyym::in}},//琴 qin
{1,0,{pysm::p,pyym::i}},//琵 pi
{1,0,{pysm::p,pyym::a}},//琶 pa
{1,0,{pysm::q,pyym::ue}},//琷 que
{1,0,{pysm::zh,pyym::uo}},//琸 zhuo
{1,0,{pysm::q,pyym::in}},//琹 qin
{1,0,{pysm::f,pyym::a}},//琺 fa
{1,0,{pysm::j,pyym::in}},//琻 jin
{1,0,{pysm::q,pyym::iong}},//琼 qiong
{1,0,{pysm::d,pyym::u}},//琽 du
{1,0,{pysm::j,pyym::ie}},//琾 jie
{2,1946,{pysm::nop,pyym::nop}},//琿 hun
{1,0,{pysm::y,pyym::u}},//瑀 yu
{1,0,{pysm::m,pyym::ao}},//瑁 mao
{1,0,{pysm::m,pyym::ei}},//瑂 mei
{1,0,{pysm::ch,pyym::un}},//瑃 chun
{1,0,{pysm::x,pyym::uan}},//瑄 xuan
{1,0,{pysm::t,pyym::i}},//瑅 ti
{1,0,{pysm::x,pyym::ing}},//瑆 xing
{1,0,{pysm::d,pyym::ai}},//瑇 dai
{1,0,{pysm::r,pyym::ou}},//瑈 rou
{1,0,{pysm::m,pyym::in}},//瑉 min
{1,0,{pysm::j,pyym::ian}},//瑊 jian
{1,0,{pysm::w,pyym::ei}},//瑋 wei
{1,0,{pysm::r,pyym::uan}},//瑌 ruan
{1,0,{pysm::h,pyym::uan}},//瑍 huan
{1,0,{pysm::x,pyym::ie}},//瑎 xie
{1,0,{pysm::ch,pyym::uan}},//瑏 chuan
{1,0,{pysm::j,pyym::ian}},//瑐 jian
{1,0,{pysm::zh,pyym::uan}},//瑑 zhuan
{3,470,{pysm::nop,pyym::nop}},//瑒 chang
{1,0,{pysm::l,pyym::ian}},//瑓 lian
{1,0,{pysm::q,pyym::uan}},//瑔 quan
{1,0,{pysm::x,pyym::ia}},//瑕 xia
{1,0,{pysm::d,pyym::uan}},//瑖 duan
{2,1947,{pysm::nop,pyym::nop}},//瑗 yuan
{1,0,{pysm::y,pyym::a}},//瑘 ya
{1,0,{pysm::n,pyym::ao}},//瑙 nao
{1,0,{pysm::h,pyym::u}},//瑚 hu
{1,0,{pysm::y,pyym::ing}},//瑛 ying
{1,0,{pysm::y,pyym::u}},//瑜 yu
{1,0,{pysm::h,pyym::uang}},//瑝 huang
{1,0,{pysm::r,pyym::ui}},//瑞 rui
{1,0,{pysm::s,pyym::e}},//瑟 se
{1,0,{pysm::l,pyym::iu}},//瑠 liu
{1,0,{pysm::sh,pyym::i}},//瑡 shi
{1,0,{pysm::r,pyym::ong}},//瑢 rong
{1,0,{pysm::s,pyym::uo}},//瑣 suo
{1,0,{pysm::y,pyym::ao}},//瑤 yao
{1,0,{pysm::w,pyym::en}},//瑥 wen
{1,0,{pysm::w,pyym::u}},//瑦 wu
{1,0,{pysm::zh,pyym::en}},//瑧 zhen
{1,0,{pysm::j,pyym::in}},//瑨 jin
{1,0,{pysm::y,pyym::ing}},//瑩 ying
{1,0,{pysm::m,pyym::a}},//瑪 ma
{1,0,{pysm::t,pyym::ao}},//瑫 tao
{1,0,{pysm::l,pyym::iu}},//瑬 liu
{1,0,{pysm::t,pyym::ang}},//瑭 tang
{1,0,{pysm::l,pyym::i}},//瑮 li
{1,0,{pysm::l,pyym::ang}},//瑯 lang
{1,0,{pysm::g,pyym::ui}},//瑰 gui
{2,1948,{pysm::nop,pyym::nop}},//瑱 zhen
{3,471,{pysm::nop,pyym::nop}},//瑲 qiang
{1,0,{pysm::c,pyym::uo}},//瑳 cuo
{1,0,{pysm::j,pyym::ue}},//瑴 jue
{1,0,{pysm::zh,pyym::ao}},//瑵 zhao
{1,0,{pysm::y,pyym::ao}},//瑶 yao
{1,0,{pysm::nop,pyym::ai}},//瑷 ai
{1,0,{pysm::b,pyym::in}},//瑸 bin
{2,1949,{pysm::nop,pyym::nop}},//瑹 shu
{1,0,{pysm::ch,pyym::ang}},//瑺 chang
{1,0,{pysm::k,pyym::un}},//瑻 kun
{1,0,{pysm::zh,pyym::uan}},//瑼 zhuan
{1,0,{pysm::c,pyym::ong}},//瑽 cong
{1,0,{pysm::j,pyym::in}},//瑾 jin
{1,0,{pysm::y,pyym::i}},//瑿 yi
{1,0,{pysm::c,pyym::ui}},//璀 cui
{1,0,{pysm::c,pyym::ong}},//璁 cong
{1,0,{pysm::q,pyym::i}},//璂 qi
{1,0,{pysm::l,pyym::i}},//璃 li
{1,0,{pysm::j,pyym::ing}},//璄 jing
{2,1950,{pysm::nop,pyym::nop}},//璅 suo
{1,0,{pysm::q,pyym::iu}},//璆 qiu
{1,0,{pysm::x,pyym::uan}},//璇 xuan
{1,0,{pysm::nop,pyym::ao}},//璈 ao
{1,0,{pysm::l,pyym::ian}},//璉 lian
{1,0,{pysm::m,pyym::en}},//璊 men
{1,0,{pysm::zh,pyym::ang}},//璋 zhang
{1,0,{pysm::y,pyym::in}},//璌 yin
{1,0,{pysm::y,pyym::e}},//璍 ye
{1,0,{pysm::y,pyym::ing}},//璎 ying
{2,1951,{pysm::nop,pyym::nop}},//璏 wei
{1,0,{pysm::l,pyym::u}},//璐 lu
{1,0,{pysm::w,pyym::u}},//璑 wu
{1,0,{pysm::d,pyym::eng}},//璒 deng
{1,0,{pysm::x,pyym::iu}},//璓 xiu
{1,0,{pysm::z,pyym::eng}},//璔 zeng
{1,0,{pysm::x,pyym::un}},//璕 xun
{1,0,{pysm::q,pyym::u}},//璖 qu
{1,0,{pysm::d,pyym::ang}},//璗 dang
{1,0,{pysm::l,pyym::in}},//璘 lin
{1,0,{pysm::l,pyym::iao}},//璙 liao
{2,1952,{pysm::nop,pyym::nop}},//璚 qiong
{1,0,{pysm::s,pyym::u}},//璛 su
{1,0,{pysm::h,pyym::uang}},//璜 huang
{1,0,{pysm::g,pyym::ui}},//璝 gui
{1,0,{pysm::p,pyym::u}},//璞 pu
{1,0,{pysm::j,pyym::ing}},//璟 jing
{1,0,{pysm::f,pyym::an}},//璠 fan
{1,0,{pysm::j,pyym::in}},//璡 jin
{1,0,{pysm::l,pyym::iu}},//璢 liu
{1,0,{pysm::j,pyym::i}},//璣 ji
{1,0,{pysm::h,pyym::ui}},//璤 hui
{1,0,{pysm::j,pyym::ing}},//璥 jing
{1,0,{pysm::nop,pyym::ai}},//璦 ai
{1,0,{pysm::b,pyym::i}},//璧 bi
{1,0,{pysm::c,pyym::an}},//璨 can
{1,0,{pysm::q,pyym::u}},//璩 qu
{1,0,{pysm::z,pyym::ao}},//璪 zao
{1,0,{pysm::d,pyym::ang}},//璫 dang
{1,0,{pysm::j,pyym::iao}},//璬 jiao
{1,0,{pysm::g,pyym::un}},//璭 gun
{1,0,{pysm::t,pyym::an}},//璮 tan
{2,1953,{pysm::nop,pyym::nop}},//璯 hui
{1,0,{pysm::h,pyym::uan}},//環 huan
{1,0,{pysm::s,pyym::e}},//璱 se
{1,0,{pysm::s,pyym::ui}},//璲 sui
{1,0,{pysm::t,pyym::ian}},//璳 tian
{1,0,{pysm::ch,pyym::u}},//璴 chu
{1,0,{pysm::y,pyym::u}},//璵 yu
{1,0,{pysm::j,pyym::in}},//璶 jin
{2,1954,{pysm::nop,pyym::nop}},//璷 lu
{2,1955,{pysm::nop,pyym::nop}},//璸 bin
{1,0,{pysm::sh,pyym::u}},//璹 shu
{1,0,{pysm::w,pyym::en}},//璺 wen
{1,0,{pysm::z,pyym::ui}},//璻 zui
{1,0,{pysm::l,pyym::an}},//璼 lan
{1,0,{pysm::x,pyym::i}},//璽 xi
{2,1956,{pysm::nop,pyym::nop}},//璾 zi
{1,0,{pysm::x,pyym::uan}},//璿 xuan
{1,0,{pysm::r,pyym::uan}},//瓀 ruan
{1,0,{pysm::w,pyym::o}},//瓁 wo
{1,0,{pysm::g,pyym::ai}},//瓂 gai
{1,0,{pysm::l,pyym::ei}},//瓃 lei
{1,0,{pysm::d,pyym::u}},//瓄 du
{1,0,{pysm::l,pyym::i}},//瓅 li
{1,0,{pysm::zh,pyym::i}},//瓆 zhi
{1,0,{pysm::r,pyym::ou}},//瓇 rou
{1,0,{pysm::l,pyym::i}},//瓈 li
{1,0,{pysm::z,pyym::an}},//瓉 zan
{2,1957,{pysm::nop,pyym::nop}},//瓊 qiong
{1,0,{pysm::t,pyym::i}},//瓋 ti
{1,0,{pysm::g,pyym::ui}},//瓌 gui
{1,0,{pysm::s,pyym::ui}},//瓍 sui
{1,0,{pysm::l,pyym::a}},//瓎 la
{1,0,{pysm::l,pyym::ong}},//瓏 long
{1,0,{pysm::l,pyym::u}},//瓐 lu
{1,0,{pysm::l,pyym::i}},//瓑 li
{1,0,{pysm::z,pyym::an}},//瓒 zan
{1,0,{pysm::l,pyym::an}},//瓓 lan
{1,0,{pysm::y,pyym::ing}},//瓔 ying
{2,1958,{pysm::nop,pyym::nop}},//瓕 mi
{1,0,{pysm::x,pyym::iang}},//瓖 xiang
{2,1959,{pysm::nop,pyym::nop}},//瓗 qiong
{1,0,{pysm::g,pyym::uan}},//瓘 guan
{1,0,{pysm::d,pyym::ao}},//瓙 dao
{1,0,{pysm::z,pyym::an}},//瓚 zan
{3,472,{pysm::nop,pyym::nop}},//瓛 huan
{1,0,{pysm::g,pyym::ua}},//瓜 gua
{1,0,{pysm::b,pyym::o}},//瓝 bo
{1,0,{pysm::d,pyym::ie}},//瓞 die
{2,1960,{pysm::nop,pyym::nop}},//瓟 bo
{3,473,{pysm::nop,pyym::nop}},//瓠 hu
{2,1961,{pysm::nop,pyym::nop}},//瓡 zhi
{1,0,{pysm::p,pyym::iao}},//瓢 piao
{1,0,{pysm::b,pyym::an}},//瓣 ban
{1,0,{pysm::r,pyym::ang}},//瓤 rang
{1,0,{pysm::l,pyym::i}},//瓥 li
{1,0,{pysm::w,pyym::a}},//瓦 wa
{0,0,{pysm::nop,pyym::nop}},//瓧 瓧
{2,1962,{pysm::nop,pyym::nop}},//瓨 xiang
{2,1963,{pysm::nop,pyym::nop}},//瓩 qian
{1,0,{pysm::b,pyym::an}},//瓪 ban
{1,0,{pysm::p,pyym::en}},//瓫 pen
{1,0,{pysm::f,pyym::ang}},//瓬 fang
{1,0,{pysm::d,pyym::an}},//瓭 dan
{1,0,{pysm::w,pyym::eng}},//瓮 weng
{1,0,{pysm::nop,pyym::ou}},//瓯 ou
{0,0,{pysm::nop,pyym::nop}},//瓰 瓰
{0,0,{pysm::nop,pyym::nop}},//瓱 瓱
{1,0,{pysm::w,pyym::a}},//瓲 wa
{1,0,{pysm::h,pyym::u}},//瓳 hu
{1,0,{pysm::l,pyym::ing}},//瓴 ling
{1,0,{pysm::y,pyym::i}},//瓵 yi
{1,0,{pysm::p,pyym::ing}},//瓶 ping
{1,0,{pysm::c,pyym::i}},//瓷 ci
{1,0,{pysm::b,pyym::ai}},//瓸 bai
{1,0,{pysm::j,pyym::uan}},//瓹 juan
{1,0,{pysm::ch,pyym::ang}},//瓺 chang
{1,0,{pysm::ch,pyym::i}},//瓻 chi
{0,0,{pysm::nop,pyym::nop}},//瓼 瓼
{1,0,{pysm::d,pyym::ang}},//瓽 dang
{1,0,{pysm::m,pyym::eng}},//瓾 meng
{2,1964,{pysm::nop,pyym::nop}},//瓿 bu
{1,0,{pysm::zh,pyym::ui}},//甀 zhui
{1,0,{pysm::p,pyym::ing}},//甁 ping
{1,0,{pysm::b,pyym::ian}},//甂 bian
{1,0,{pysm::zh,pyym::ou}},//甃 zhou
{2,1965,{pysm::nop,pyym::nop}},//甄 zhen
{0,0,{pysm::nop,pyym::nop}},//甅 甅
{1,0,{pysm::c,pyym::i}},//甆 ci
{1,0,{pysm::y,pyym::ing}},//甇 ying
{1,0,{pysm::q,pyym::i}},//甈 qi
{1,0,{pysm::x,pyym::ian}},//甉 xian
{1,0,{pysm::l,pyym::ou}},//甊 lou
{1,0,{pysm::d,pyym::i}},//甋 di
{1,0,{pysm::nop,pyym::ou}},//甌 ou
{1,0,{pysm::m,pyym::eng}},//甍 meng
{2,1966,{pysm::nop,pyym::nop}},//甎 zhuan
{1,0,{pysm::b,pyym::eng}},//甏 beng
{1,0,{pysm::l,pyym::in}},//甐 lin
{1,0,{pysm::z,pyym::eng}},//甑 zeng
{1,0,{pysm::w,pyym::u}},//甒 wu
{1,0,{pysm::p,pyym::i}},//甓 pi
{1,0,{pysm::d,pyym::an}},//甔 dan
{1,0,{pysm::w,pyym::eng}},//甕 weng
{1,0,{pysm::y,pyym::ing}},//甖 ying
{1,0,{pysm::y,pyym::an}},//甗 yan
{2,1967,{pysm::nop,pyym::nop}},//甘 gan
{1,0,{pysm::d,pyym::ai}},//甙 dai
{1,0,{pysm::sh,pyym::en}},//甚 shen
{1,0,{pysm::t,pyym::ian}},//甛 tian
{1,0,{pysm::t,pyym::ian}},//甜 tian
{1,0,{pysm::h,pyym::an}},//甝 han
{1,0,{pysm::ch,pyym::ang}},//甞 chang
{1,0,{pysm::sh,pyym::eng}},//生 sheng
{1,0,{pysm::q,pyym::ing}},//甠 qing
{1,0,{pysm::sh,pyym::en}},//甡 shen
{1,0,{pysm::ch,pyym::an}},//產 chan
{1,0,{pysm::ch,pyym::an}},//産 chan
{1,0,{pysm::r,pyym::ui}},//甤 rui
{1,0,{pysm::sh,pyym::eng}},//甥 sheng
{1,0,{pysm::s,pyym::u}},//甦 su
{1,0,{pysm::sh,pyym::en}},//甧 shen
{1,0,{pysm::y,pyym::ong}},//用 yong
{1,0,{pysm::sh,pyym::uai}},//甩 shuai
{1,0,{pysm::l,pyym::u}},//甪 lu
{2,1968,{pysm::nop,pyym::nop}},//甫 fu
{2,1969,{pysm::nop,pyym::nop}},//甬 yong
{2,1970,{pysm::nop,pyym::nop}},//甭 beng
{1,0,{pysm::f,pyym::eng}},//甮 feng
{1,0,{pysm::n,pyym::ing}},//甯 ning
{1,0,{pysm::t,pyym::ian}},//田 tian
{2,1971,{pysm::nop,pyym::nop}},//由 you
{1,0,{pysm::j,pyym::ia}},//甲 jia
{1,0,{pysm::sh,pyym::en}},//申 shen
{2,1972,{pysm::nop,pyym::nop}},//甴 zha
{1,0,{pysm::d,pyym::ian}},//电 dian
{1,0,{pysm::f,pyym::u}},//甶 fu
{1,0,{pysm::n,pyym::an}},//男 nan
{4,101,{pysm::nop,pyym::nop}},//甸 dian
{1,0,{pysm::p,pyym::ing}},//甹 ping
{4,102,{pysm::nop,pyym::nop}},//町 ting
{1,0,{pysm::h,pyym::ua}},//画 hua
{1,0,{pysm::t,pyym::ing}},//甼 ting
{3,474,{pysm::nop,pyym::nop}},//甽 zhen
{2,1973,{pysm::nop,pyym::nop}},//甾 zai
{2,1974,{pysm::nop,pyym::nop}},//甿 meng
{1,0,{pysm::b,pyym::i}},//畀 bi
{1,0,{pysm::b,pyym::i}},//畁 bi
{1,0,{pysm::l,pyym::iu}},//畂 liu
{1,0,{pysm::x,pyym::un}},//畃 xun
{1,0,{pysm::l,pyym::iu}},//畄 liu
{1,0,{pysm::ch,pyym::ang}},//畅 chang
{1,0,{pysm::m,pyym::u}},//畆 mu
{2,1975,{pysm::nop,pyym::nop}},//畇 yun
{1,0,{pysm::f,pyym::an}},//畈 fan
{1,0,{pysm::f,pyym::u}},//畉 fu
{1,0,{pysm::g,pyym::eng}},//畊 geng
{1,0,{pysm::t,pyym::ian}},//畋 tian
{1,0,{pysm::j,pyym::ie}},//界 jie
{1,0,{pysm::j,pyym::ie}},//畍 jie
{1,0,{pysm::q,pyym::uan}},//畎 quan
{1,0,{pysm::w,pyym::ei}},//畏 wei
{2,1976,{pysm::nop,pyym::nop}},//畐 fu
{1,0,{pysm::t,pyym::ian}},//畑 tian
{1,0,{pysm::m,pyym::u}},//畒 mu
{1,0,{pysm::d,pyym::uo}},//畓 duo
{1,0,{pysm::p,pyym::an}},//畔 pan
{1,0,{pysm::j,pyym::iang}},//畕 jiang
{1,0,{pysm::w,pyym::a}},//畖 wa
{2,1977,{pysm::nop,pyym::nop}},//畗 da
{1,0,{pysm::n,pyym::an}},//畘 nan
{1,0,{pysm::l,pyym::iu}},//留 liu
{1,0,{pysm::b,pyym::en}},//畚 ben
{1,0,{pysm::zh,pyym::en}},//畛 zhen
{2,1978,{pysm::nop,pyym::nop}},//畜 chu
{2,1979,{pysm::nop,pyym::nop}},//畝 mu
{1,0,{pysm::m,pyym::u}},//畞 mu
{2,1980,{pysm::nop,pyym::nop}},//畟 ce
{1,0,{pysm::t,pyym::ian}},//畠 tian
{1,0,{pysm::g,pyym::ai}},//畡 gai
{1,0,{pysm::b,pyym::i}},//畢 bi
{1,0,{pysm::d,pyym::a}},//畣 da
{3,475,{pysm::nop,pyym::nop}},//畤 zhi
{1,0,{pysm::l,pyym::ve}},//略 lüe
{1,0,{pysm::q,pyym::i}},//畦 qi
{1,0,{pysm::l,pyym::ve}},//畧 lüe
{2,1981,{pysm::nop,pyym::nop}},//畨 pan
{1,0,{pysm::y,pyym::i}},//畩 yi
{5,34,{pysm::nop,pyym::nop}},//番 fan
{1,0,{pysm::h,pyym::ua}},//畫 hua
{2,1982,{pysm::nop,pyym::nop}},//畬 she
{1,0,{pysm::y,pyym::u}},//畭 yu
{1,0,{pysm::m,pyym::u}},//畮 mu
{1,0,{pysm::j,pyym::un}},//畯 jun
{1,0,{pysm::y,pyym::i}},//異 yi
{1,0,{pysm::l,pyym::iu}},//畱 liu
{1,0,{pysm::sh,pyym::e}},//畲 she
{1,0,{pysm::d,pyym::ie}},//畳 die
{1,0,{pysm::ch,pyym::ou}},//畴 chou
{1,0,{pysm::h,pyym::ua}},//畵 hua
{1,0,{pysm::d,pyym::ang}},//當 dang
{1,0,{pysm::zh,pyym::ui}},//畷 zhui
{2,1983,{pysm::nop,pyym::nop}},//畸 ji
{2,1984,{pysm::nop,pyym::nop}},//畹 wan
{1,0,{pysm::j,pyym::iang}},//畺 jiang
{1,0,{pysm::ch,pyym::eng}},//畻 cheng
{1,0,{pysm::ch,pyym::ang}},//畼 chang
{2,1985,{pysm::nop,pyym::nop}},//畽 tun
{1,0,{pysm::l,pyym::ei}},//畾 lei
{1,0,{pysm::j,pyym::i}},//畿 ji
{1,0,{pysm::ch,pyym::a}},//疀 cha
{1,0,{pysm::l,pyym::iu}},//疁 liu
{1,0,{pysm::d,pyym::ie}},//疂 die
{1,0,{pysm::t,pyym::uan}},//疃 tuan
{1,0,{pysm::l,pyym::in}},//疄 lin
{1,0,{pysm::j,pyym::iang}},//疅 jiang
{1,0,{pysm::j,pyym::iang}},//疆 jiang
{1,0,{pysm::ch,pyym::ou}},//疇 chou
{1,0,{pysm::p,pyym::i}},//疈 pi
{1,0,{pysm::d,pyym::ie}},//疉 die
{1,0,{pysm::d,pyym::ie}},//疊 die
{3,476,{pysm::nop,pyym::nop}},//疋 pi
{2,1986,{pysm::nop,pyym::nop}},//疌 jie
{1,0,{pysm::d,pyym::an}},//疍 dan
{1,0,{pysm::sh,pyym::u}},//疎 shu
{1,0,{pysm::sh,pyym::u}},//疏 shu
{2,1987,{pysm::nop,pyym::nop}},//疐 zhi
{2,1988,{pysm::nop,pyym::nop}},//疑 yi
{1,0,{pysm::n,pyym::e}},//疒 ne
{1,0,{pysm::n,pyym::ai}},//疓 nai
{2,1989,{pysm::nop,pyym::nop}},//疔 ding
{1,0,{pysm::b,pyym::i}},//疕 bi
{1,0,{pysm::j,pyym::ie}},//疖 jie
{1,0,{pysm::l,pyym::iao}},//疗 liao
{2,1990,{pysm::nop,pyym::nop}},//疘 gang
{2,1991,{pysm::nop,pyym::nop}},//疙 ge
{1,0,{pysm::j,pyym::iu}},//疚 jiu
{1,0,{pysm::zh,pyym::ou}},//疛 zhou
{1,0,{pysm::x,pyym::ia}},//疜 xia
{1,0,{pysm::sh,pyym::an}},//疝 shan
{1,0,{pysm::x,pyym::u}},//疞 xu
{2,1992,{pysm::nop,pyym::nop}},//疟 nüe
{1,0,{pysm::l,pyym::i}},//疠 li
{1,0,{pysm::y,pyym::ang}},//疡 yang
{1,0,{pysm::ch,pyym::en}},//疢 chen
{1,0,{pysm::y,pyym::ou}},//疣 you
{1,0,{pysm::b,pyym::a}},//疤 ba
{1,0,{pysm::j,pyym::ie}},//疥 jie
{2,1993,{pysm::nop,pyym::nop}},//疦 jue
{1,0,{pysm::q,pyym::i}},//疧 qi
{2,1994,{pysm::nop,pyym::nop}},//疨 xia
{1,0,{pysm::c,pyym::ui}},//疩 cui
{1,0,{pysm::b,pyym::i}},//疪 bi
{1,0,{pysm::y,pyym::i}},//疫 yi
{1,0,{pysm::l,pyym::i}},//疬 li
{1,0,{pysm::z,pyym::ong}},//疭 zong
{1,0,{pysm::ch,pyym::uang}},//疮 chuang
{1,0,{pysm::f,pyym::eng}},//疯 feng
{1,0,{pysm::zh,pyym::u}},//疰 zhu
{1,0,{pysm::p,pyym::ao}},//疱 pao
{1,0,{pysm::p,pyym::i}},//疲 pi
{1,0,{pysm::g,pyym::an}},//疳 gan
{3,477,{pysm::nop,pyym::nop}},//疴 ke
{4,103,{pysm::nop,pyym::nop}},//疵 ci
{1,0,{pysm::x,pyym::ue}},//疶 xue
{1,0,{pysm::zh,pyym::i}},//疷 zhi
{2,1995,{pysm::nop,pyym::nop}},//疸 dan
{2,1996,{pysm::nop,pyym::nop}},//疹 zhen
{2,1997,{pysm::nop,pyym::nop}},//疺 fa
{1,0,{pysm::zh,pyym::i}},//疻 zhi
{1,0,{pysm::t,pyym::eng}},//疼 teng
{1,0,{pysm::j,pyym::u}},//疽 ju
{1,0,{pysm::j,pyym::i}},//疾 ji
{1,0,{pysm::f,pyym::ei}},//疿 fei
{2,1998,{pysm::nop,pyym::nop}},//痀 ju
{1,0,{pysm::sh,pyym::an}},//痁 shan
{1,0,{pysm::j,pyym::ia}},//痂 jia
{1,0,{pysm::x,pyym::uan}},//痃 xuan
{1,0,{pysm::zh,pyym::a}},//痄 zha
{1,0,{pysm::b,pyym::ing}},//病 bing
{3,478,{pysm::nop,pyym::nop}},//痆 nie
{1,0,{pysm::zh,pyym::eng}},//症 zheng
{1,0,{pysm::y,pyym::ong}},//痈 yong
{1,0,{pysm::j,pyym::ing}},//痉 jing
{1,0,{pysm::q,pyym::uan}},//痊 quan
{2,1999,{pysm::nop,pyym::nop}},//痋 teng
{1,0,{pysm::t,pyym::ong}},//痌 tong
{1,0,{pysm::y,pyym::i}},//痍 yi
{1,0,{pysm::j,pyym::ie}},//痎 jie
{3,479,{pysm::nop,pyym::nop}},//痏 wei
{1,0,{pysm::h,pyym::ui}},//痐 hui
{2,2000,{pysm::nop,pyym::nop}},//痑 tan
{1,0,{pysm::y,pyym::ang}},//痒 yang
{1,0,{pysm::ch,pyym::i}},//痓 chi
{1,0,{pysm::zh,pyym::i}},//痔 zhi
{2,2001,{pysm::nop,pyym::nop}},//痕 hen
{1,0,{pysm::y,pyym::a}},//痖 ya
{1,0,{pysm::m,pyym::ei}},//痗 mei
{1,0,{pysm::d,pyym::ou}},//痘 dou
{1,0,{pysm::j,pyym::ing}},//痙 jing
{1,0,{pysm::x,pyym::iao}},//痚 xiao
{1,0,{pysm::t,pyym::ong}},//痛 tong
{1,0,{pysm::t,pyym::u}},//痜 tu
{1,0,{pysm::m,pyym::ang}},//痝 mang
{1,0,{pysm::p,pyym::i}},//痞 pi
{1,0,{pysm::x,pyym::iao}},//痟 xiao
{1,0,{pysm::s,pyym::uan}},//痠 suan
{2,2002,{pysm::nop,pyym::nop}},//痡 fu
{1,0,{pysm::l,pyym::i}},//痢 li
{1,0,{pysm::zh,pyym::i}},//痣 zhi
{1,0,{pysm::c,pyym::uo}},//痤 cuo
{1,0,{pysm::d,pyym::uo}},//痥 duo
{2,2003,{pysm::nop,pyym::nop}},//痦 wu
{1,0,{pysm::sh,pyym::a}},//痧 sha
{1,0,{pysm::l,pyym::ao}},//痨 lao
{1,0,{pysm::sh,pyym::ou}},//痩 shou
{2,2004,{pysm::nop,pyym::nop}},//痪 huan
{1,0,{pysm::x,pyym::ian}},//痫 xian
{1,0,{pysm::y,pyym::i}},//痬 yi
{3,480,{pysm::nop,pyym::nop}},//痭 beng
{1,0,{pysm::zh,pyym::ang}},//痮 zhang
{1,0,{pysm::g,pyym::uan}},//痯 guan
{1,0,{pysm::t,pyym::an}},//痰 tan
{1,0,{pysm::f,pyym::ei}},//痱 fei
{1,0,{pysm::m,pyym::a}},//痲 ma
{1,0,{pysm::l,pyym::in}},//痳 lin
{1,0,{pysm::ch,pyym::i}},//痴 chi
{1,0,{pysm::j,pyym::i}},//痵 ji
{2,2005,{pysm::nop,pyym::nop}},//痶 tian
{3,481,{pysm::nop,pyym::nop}},//痷 an
{1,0,{pysm::ch,pyym::i}},//痸 chi
{1,0,{pysm::b,pyym::i}},//痹 bi
{1,0,{pysm::b,pyym::i}},//痺 bi
{1,0,{pysm::m,pyym::in}},//痻 min
{1,0,{pysm::g,pyym::u}},//痼 gu
{1,0,{pysm::d,pyym::ui}},//痽 dui
{2,2006,{pysm::nop,pyym::nop}},//痾 e
{1,0,{pysm::w,pyym::ei}},//痿 wei
{1,0,{pysm::y,pyym::u}},//瘀 yu
{1,0,{pysm::c,pyym::ui}},//瘁 cui
{1,0,{pysm::y,pyym::a}},//瘂 ya
{1,0,{pysm::zh,pyym::u}},//瘃 zhu
{1,0,{pysm::c,pyym::u}},//瘄 cu
{1,0,{pysm::d,pyym::an}},//瘅 dan
{1,0,{pysm::sh,pyym::en}},//瘆 shen
{1,0,{pysm::zh,pyym::ong}},//瘇 zhong
{2,2007,{pysm::nop,pyym::nop}},//瘈 chi
{1,0,{pysm::y,pyym::u}},//瘉 yu
{1,0,{pysm::h,pyym::ou}},//瘊 hou
{1,0,{pysm::f,pyym::eng}},//瘋 feng
{1,0,{pysm::l,pyym::a}},//瘌 la
{2,2008,{pysm::nop,pyym::nop}},//瘍 yang
{1,0,{pysm::ch,pyym::en}},//瘎 chen
{1,0,{pysm::t,pyym::u}},//瘏 tu
{1,0,{pysm::y,pyym::u}},//瘐 yu
{1,0,{pysm::g,pyym::uo}},//瘑 guo
{1,0,{pysm::w,pyym::en}},//瘒 wen
{1,0,{pysm::h,pyym::uan}},//瘓 huan
{1,0,{pysm::k,pyym::u}},//瘔 ku
{2,2009,{pysm::nop,pyym::nop}},//瘕 jia
{1,0,{pysm::y,pyym::in}},//瘖 yin
{1,0,{pysm::y,pyym::i}},//瘗 yi
{1,0,{pysm::l,pyym::ou}},//瘘 lou
{1,0,{pysm::s,pyym::ao}},//瘙 sao
{1,0,{pysm::j,pyym::ue}},//瘚 jue
{1,0,{pysm::ch,pyym::i}},//瘛 chi
{1,0,{pysm::x,pyym::i}},//瘜 xi
{1,0,{pysm::g,pyym::uan}},//瘝 guan
{1,0,{pysm::y,pyym::i}},//瘞 yi
{3,482,{pysm::nop,pyym::nop}},//瘟 wen
{1,0,{pysm::j,pyym::i}},//瘠 ji
{1,0,{pysm::ch,pyym::uang}},//瘡 chuang
{1,0,{pysm::b,pyym::an}},//瘢 ban
{2,2010,{pysm::nop,pyym::nop}},//瘣 hui
{1,0,{pysm::l,pyym::iu}},//瘤 liu
{2,2011,{pysm::nop,pyym::nop}},//瘥 chai
{1,0,{pysm::sh,pyym::ou}},//瘦 shou
{2,2012,{pysm::nop,pyym::nop}},//瘧 nüe
{2,2013,{pysm::nop,pyym::nop}},//瘨 dian
{1,0,{pysm::d,pyym::a}},//瘩 da
{1,0,{pysm::b,pyym::ie}},//瘪 bie
{1,0,{pysm::t,pyym::an}},//瘫 tan
{1,0,{pysm::zh,pyym::ang}},//瘬 zhang
{1,0,{pysm::b,pyym::iao}},//瘭 biao
{1,0,{pysm::sh,pyym::en}},//瘮 shen
{1,0,{pysm::c,pyym::u}},//瘯 cu
{1,0,{pysm::l,pyym::uo}},//瘰 luo
{1,0,{pysm::y,pyym::i}},//瘱 yi
{1,0,{pysm::z,pyym::ong}},//瘲 zong
{2,2014,{pysm::nop,pyym::nop}},//瘳 chou
{1,0,{pysm::zh,pyym::ang}},//瘴 zhang
{2,2015,{pysm::nop,pyym::nop}},//瘵 zhai
{1,0,{pysm::s,pyym::ou}},//瘶 sou
{1,0,{pysm::s,pyym::e}},//瘷 se
{1,0,{pysm::q,pyym::ue}},//瘸 que
{1,0,{pysm::d,pyym::iao}},//瘹 diao
{1,0,{pysm::l,pyym::ou}},//瘺 lou
{2,2016,{pysm::nop,pyym::nop}},//瘻 lou
{1,0,{pysm::m,pyym::o}},//瘼 mo
{1,0,{pysm::q,pyym::in}},//瘽 qin
{1,0,{pysm::y,pyym::in}},//瘾 yin
{1,0,{pysm::y,pyym::ing}},//瘿 ying
{1,0,{pysm::h,pyym::uang}},//癀 huang
{1,0,{pysm::f,pyym::u}},//癁 fu
{2,2017,{pysm::nop,pyym::nop}},//療 liao
{1,0,{pysm::l,pyym::ong}},//癃 long
{1,0,{pysm::q,pyym::iao}},//癄 qiao
{1,0,{pysm::l,pyym::iu}},//癅 liu
{1,0,{pysm::l,pyym::ao}},//癆 lao
{1,0,{pysm::x,pyym::ian}},//癇 xian
{1,0,{pysm::f,pyym::ei}},//癈 fei
{2,2018,{pysm::nop,pyym::nop}},//癉 dan
{1,0,{pysm::y,pyym::in}},//癊 yin
{1,0,{pysm::h,pyym::e}},//癋 he
{2,2019,{pysm::nop,pyym::nop}},//癌 ai
{1,0,{pysm::b,pyym::an}},//癍 ban
{1,0,{pysm::x,pyym::ian}},//癎 xian
{1,0,{pysm::g,pyym::uan}},//癏 guan
{2,2020,{pysm::nop,pyym::nop}},//癐 gui
{1,0,{pysm::n,pyym::ong}},//癑 nong
{1,0,{pysm::y,pyym::u}},//癒 yu
{1,0,{pysm::w,pyym::ei}},//癓 wei
{1,0,{pysm::y,pyym::i}},//癔 yi
{1,0,{pysm::y,pyym::ong}},//癕 yong
{1,0,{pysm::p,pyym::i}},//癖 pi
{1,0,{pysm::l,pyym::ei}},//癗 lei
{2,2021,{pysm::nop,pyym::nop}},//癘 li
{1,0,{pysm::sh,pyym::u}},//癙 shu
{1,0,{pysm::d,pyym::an}},//癚 dan
{2,2022,{pysm::nop,pyym::nop}},//癛 lin
{1,0,{pysm::d,pyym::ian}},//癜 dian
{1,0,{pysm::l,pyym::in}},//癝 lin
{1,0,{pysm::l,pyym::ai}},//癞 lai
{1,0,{pysm::b,pyym::ie}},//癟 bie
{1,0,{pysm::j,pyym::i}},//癠 ji
{1,0,{pysm::ch,pyym::i}},//癡 chi
{1,0,{pysm::y,pyym::ang}},//癢 yang
{1,0,{pysm::x,pyym::uan}},//癣 xuan
{1,0,{pysm::j,pyym::ie}},//癤 jie
{1,0,{pysm::zh,pyym::eng}},//癥 zheng
{1,0,{pysm::m,pyym::e}},//癦 me
{1,0,{pysm::l,pyym::i}},//癧 li
{1,0,{pysm::h,pyym::uo}},//癨 huo
{2,2023,{pysm::nop,pyym::nop}},//癩 lai
{1,0,{pysm::j,pyym::i}},//癪 ji
{1,0,{pysm::d,pyym::ian}},//癫 dian
{1,0,{pysm::x,pyym::uan}},//癬 xuan
{1,0,{pysm::y,pyym::ing}},//癭 ying
{1,0,{pysm::y,pyym::in}},//癮 yin
{1,0,{pysm::q,pyym::u}},//癯 qu
{1,0,{pysm::y,pyym::ong}},//癰 yong
{1,0,{pysm::t,pyym::an}},//癱 tan
{1,0,{pysm::d,pyym::ian}},//癲 dian
{1,0,{pysm::l,pyym::uo}},//癳 luo
{1,0,{pysm::l,pyym::uan}},//癴 luan
{1,0,{pysm::l,pyym::uan}},//癵 luan
{1,0,{pysm::b,pyym::o}},//癶 bo
{1,0,{pysm::b,pyym::o}},//癷 bo
{1,0,{pysm::g,pyym::ui}},//癸 gui
{1,0,{pysm::b,pyym::a}},//癹 ba
{1,0,{pysm::f,pyym::a}},//発 fa
{2,2024,{pysm::nop,pyym::nop}},//登 deng
{2,2025,{pysm::nop,pyym::nop}},//發 fa
{2,2026,{pysm::nop,pyym::nop}},//白 bai
{3,483,{pysm::nop,pyym::nop}},//百 bai
{2,2027,{pysm::nop,pyym::nop}},//癿 qie
{3,484,{pysm::nop,pyym::nop}},//皀 ji
{1,0,{pysm::z,pyym::ao}},//皁 zao
{1,0,{pysm::z,pyym::ao}},//皂 zao
{1,0,{pysm::m,pyym::ao}},//皃 mao
{2,2028,{pysm::nop,pyym::nop}},//的 de
{2,2029,{pysm::nop,pyym::nop}},//皅 pa
{1,0,{pysm::j,pyym::ie}},//皆 jie
{2,2030,{pysm::nop,pyym::nop}},//皇 huang
{1,0,{pysm::g,pyym::ui}},//皈 gui
{1,0,{pysm::c,pyym::i}},//皉 ci
{1,0,{pysm::l,pyym::ing}},//皊 ling
{3,485,{pysm::nop,pyym::nop}},//皋 gao
{1,0,{pysm::m,pyym::o}},//皌 mo
{1,0,{pysm::j,pyym::i}},//皍 ji
{1,0,{pysm::j,pyym::iao}},//皎 jiao
{1,0,{pysm::p,pyym::eng}},//皏 peng
{1,0,{pysm::g,pyym::ao}},//皐 gao
{1,0,{pysm::nop,pyym::ai}},//皑 ai
{1,0,{pysm::nop,pyym::e}},//皒 e
{2,2031,{pysm::nop,pyym::nop}},//皓 hao
{1,0,{pysm::h,pyym::an}},//皔 han
{1,0,{pysm::b,pyym::i}},//皕 bi
{2,2032,{pysm::nop,pyym::nop}},//皖 wan
{1,0,{pysm::ch,pyym::ou}},//皗 chou
{1,0,{pysm::q,pyym::ian}},//皘 qian
{1,0,{pysm::x,pyym::i}},//皙 xi
{1,0,{pysm::nop,pyym::ai}},//皚 ai
{3,486,{pysm::nop,pyym::nop}},//皛 xiao
{1,0,{pysm::h,pyym::ao}},//皜 hao
{1,0,{pysm::h,pyym::uang}},//皝 huang
{1,0,{pysm::h,pyym::ao}},//皞 hao
{1,0,{pysm::z,pyym::e}},//皟 ze
{1,0,{pysm::c,pyym::ui}},//皠 cui
{1,0,{pysm::h,pyym::ao}},//皡 hao
{1,0,{pysm::x,pyym::iao}},//皢 xiao
{1,0,{pysm::y,pyym::e}},//皣 ye
{2,2033,{pysm::nop,pyym::nop}},//皤 po
{1,0,{pysm::h,pyym::ao}},//皥 hao
{1,0,{pysm::j,pyym::iao}},//皦 jiao
{1,0,{pysm::nop,pyym::ai}},//皧 ai
{1,0,{pysm::x,pyym::ing}},//皨 xing
{1,0,{pysm::h,pyym::uang}},//皩 huang
{3,487,{pysm::nop,pyym::nop}},//皪 li
{1,0,{pysm::p,pyym::iao}},//皫 piao
{1,0,{pysm::h,pyym::e}},//皬 he
{1,0,{pysm::j,pyym::iao}},//皭 jiao
{1,0,{pysm::p,pyym::i}},//皮 pi
{1,0,{pysm::g,pyym::an}},//皯 gan
{1,0,{pysm::p,pyym::ao}},//皰 pao
{1,0,{pysm::zh,pyym::ou}},//皱 zhou
{1,0,{pysm::j,pyym::un}},//皲 jun
{1,0,{pysm::q,pyym::iu}},//皳 qiu
{1,0,{pysm::c,pyym::un}},//皴 cun
{1,0,{pysm::q,pyym::ue}},//皵 que
{1,0,{pysm::zh,pyym::a}},//皶 zha
{1,0,{pysm::g,pyym::u}},//皷 gu
{1,0,{pysm::j,pyym::un}},//皸 jun
{1,0,{pysm::j,pyym::un}},//皹 jun
{1,0,{pysm::zh,pyym::ou}},//皺 zhou
{2,2034,{pysm::nop,pyym::nop}},//皻 zha
{1,0,{pysm::g,pyym::u}},//皼 gu
{3,488,{pysm::nop,pyym::nop}},//皽 zhao
{1,0,{pysm::d,pyym::u}},//皾 du
{2,2035,{pysm::nop,pyym::nop}},//皿 min
{1,0,{pysm::q,pyym::i}},//盀 qi
{1,0,{pysm::y,pyym::ing}},//盁 ying
{1,0,{pysm::y,pyym::u}},//盂 yu
{1,0,{pysm::b,pyym::ei}},//盃 bei
{1,0,{pysm::zh,pyym::ao}},//盄 zhao
{2,2036,{pysm::nop,pyym::nop}},//盅 zhong
{1,0,{pysm::p,pyym::en}},//盆 pen
{1,0,{pysm::h,pyym::e}},//盇 he
{1,0,{pysm::y,pyym::ing}},//盈 ying
{1,0,{pysm::h,pyym::e}},//盉 he
{1,0,{pysm::y,pyym::i}},//益 yi
{1,0,{pysm::b,pyym::o}},//盋 bo
{1,0,{pysm::w,pyym::an}},//盌 wan
{2,2037,{pysm::nop,pyym::nop}},//盍 he
{1,0,{pysm::nop,pyym::ang}},//盎 ang
{1,0,{pysm::zh,pyym::an}},//盏 zhan
{1,0,{pysm::y,pyym::an}},//盐 yan
{1,0,{pysm::j,pyym::ian}},//监 jian
{2,2038,{pysm::nop,pyym::nop}},//盒 he
{2,2039,{pysm::nop,pyym::nop}},//盓 yu
{1,0,{pysm::k,pyym::ui}},//盔 kui
{1,0,{pysm::f,pyym::an}},//盕 fan
{2,2040,{pysm::nop,pyym::nop}},//盖 gai
{1,0,{pysm::d,pyym::ao}},//盗 dao
{1,0,{pysm::p,pyym::an}},//盘 pan
{1,0,{pysm::f,pyym::u}},//盙 fu
{1,0,{pysm::q,pyym::iu}},//盚 qiu
{2,2041,{pysm::nop,pyym::nop}},//盛 sheng
{1,0,{pysm::d,pyym::ao}},//盜 dao
{1,0,{pysm::l,pyym::u}},//盝 lu
{1,0,{pysm::zh,pyym::an}},//盞 zhan
{2,2042,{pysm::nop,pyym::nop}},//盟 meng
{1,0,{pysm::l,pyym::i}},//盠 li
{1,0,{pysm::j,pyym::in}},//盡 jin
{1,0,{pysm::x,pyym::u}},//盢 xu
{2,2043,{pysm::nop,pyym::nop}},//監 jian
{2,2044,{pysm::nop,pyym::nop}},//盤 pan
{1,0,{pysm::g,pyym::uan}},//盥 guan
{1,0,{pysm::nop,pyym::an}},//盦 an
{3,489,{pysm::nop,pyym::nop}},//盧 lu
{1,0,{pysm::x,pyym::u}},//盨 xu
{2,2045,{pysm::nop,pyym::nop}},//盩 zhou
{1,0,{pysm::d,pyym::ang}},//盪 dang
{1,0,{pysm::nop,pyym::an}},//盫 an
{1,0,{pysm::g,pyym::u}},//盬 gu
{1,0,{pysm::l,pyym::i}},//盭 li
{1,0,{pysm::m,pyym::u}},//目 mu
{2,2046,{pysm::nop,pyym::nop}},//盯 ding
{1,0,{pysm::g,pyym::an}},//盰 gan
{1,0,{pysm::x,pyym::u}},//盱 xu
{1,0,{pysm::m,pyym::ang}},//盲 mang
{2,2047,{pysm::nop,pyym::nop}},//盳 wang
{1,0,{pysm::zh,pyym::i}},//直 zhi
{1,0,{pysm::q,pyym::i}},//盵 qi
{1,0,{pysm::y,pyym::uan}},//盶 yuan
{3,490,{pysm::nop,pyym::nop}},//盷 tian
{1,0,{pysm::x,pyym::iang}},//相 xiang
{2,2048,{pysm::nop,pyym::nop}},//盹 dun
{1,0,{pysm::x,pyym::in}},//盺 xin
{2,2049,{pysm::nop,pyym::nop}},//盻 xi
{2,2050,{pysm::nop,pyym::nop}},//盼 pan
{1,0,{pysm::f,pyym::eng}},//盽 feng
{3,491,{pysm::nop,pyym::nop}},//盾 dun
{1,0,{pysm::m,pyym::in}},//盿 min
{1,0,{pysm::m,pyym::ing}},//眀 ming
{3,492,{pysm::nop,pyym::nop}},//省 sheng
{1,0,{pysm::sh,pyym::i}},//眂 shi
{2,2051,{pysm::nop,pyym::nop}},//眃 yun
{1,0,{pysm::m,pyym::ian}},//眄 mian
{1,0,{pysm::p,pyym::an}},//眅 pan
{1,0,{pysm::f,pyym::ang}},//眆 fang
{1,0,{pysm::m,pyym::iao}},//眇 miao
{2,2052,{pysm::nop,pyym::nop}},//眈 dan
{1,0,{pysm::m,pyym::ei}},//眉 mei
{2,2053,{pysm::nop,pyym::nop}},//眊 mao
{1,0,{pysm::k,pyym::an}},//看 kan
{1,0,{pysm::x,pyym::ian}},//県 xian
{1,0,{pysm::k,pyym::ou}},//眍 kou
{1,0,{pysm::sh,pyym::i}},//眎 shi
{2,2054,{pysm::nop,pyym::nop}},//眏 yang
{1,0,{pysm::zh,pyym::eng}},//眐 zheng
{2,2055,{pysm::nop,pyym::nop}},//眑 yao
{1,0,{pysm::sh,pyym::en}},//眒 shen
{1,0,{pysm::h,pyym::uo}},//眓 huo
{1,0,{pysm::d,pyym::a}},//眔 da
{1,0,{pysm::zh,pyym::en}},//眕 zhen
{1,0,{pysm::k,pyym::uang}},//眖 kuang
{3,493,{pysm::nop,pyym::nop}},//眗 ju
{1,0,{pysm::sh,pyym::en}},//眘 shen
{2,2056,{pysm::nop,pyym::nop}},//眙 yi
{1,0,{pysm::sh,pyym::eng}},//眚 sheng
{1,0,{pysm::m,pyym::ei}},//眛 mei
{2,2057,{pysm::nop,pyym::nop}},//眜 mo
{1,0,{pysm::zh,pyym::u}},//眝 zhu
{1,0,{pysm::zh,pyym::en}},//眞 zhen
{1,0,{pysm::zh,pyym::en}},//真 zhen
{2,2058,{pysm::nop,pyym::nop}},//眠 mian
{1,0,{pysm::sh,pyym::i}},//眡 shi
{1,0,{pysm::y,pyym::uan}},//眢 yuan
{2,2059,{pysm::nop,pyym::nop}},//眣 die
{1,0,{pysm::n,pyym::i}},//眤 ni
{1,0,{pysm::z,pyym::i}},//眥 zi
{1,0,{pysm::z,pyym::i}},//眦 zi
{1,0,{pysm::ch,pyym::ao}},//眧 chao
{1,0,{pysm::zh,pyym::a}},//眨 zha
{3,494,{pysm::nop,pyym::nop}},//眩 xuan
{2,2060,{pysm::nop,pyym::nop}},//眪 bing
{2,2061,{pysm::nop,pyym::nop}},//眫 mi
{1,0,{pysm::l,pyym::ong}},//眬 long
{4,104,{pysm::nop,pyym::nop}},//眭 sui
{1,0,{pysm::t,pyym::ong}},//眮 tong
{1,0,{pysm::m,pyym::i}},//眯 mi
{2,2062,{pysm::nop,pyym::nop}},//眰 die
{1,0,{pysm::d,pyym::i}},//眱 di
{1,0,{pysm::n,pyym::e}},//眲 ne
{1,0,{pysm::m,pyym::ing}},//眳 ming
{3,495,{pysm::nop,pyym::nop}},//眴 xuan
{1,0,{pysm::ch,pyym::i}},//眵 chi
{1,0,{pysm::k,pyym::uang}},//眶 kuang
{1,0,{pysm::j,pyym::uan}},//眷 juan
{1,0,{pysm::m,pyym::ou}},//眸 mou
{1,0,{pysm::zh,pyym::en}},//眹 zhen
{1,0,{pysm::t,pyym::iao}},//眺 tiao
{1,0,{pysm::y,pyym::ang}},//眻 yang
{2,2063,{pysm::nop,pyym::nop}},//眼 yan
{2,2064,{pysm::nop,pyym::nop}},//眽 mo
{1,0,{pysm::zh,pyym::ong}},//眾 zhong
{1,0,{pysm::m,pyym::o}},//眿 mo
{3,496,{pysm::nop,pyym::nop}},//着 zhe
{1,0,{pysm::zh,pyym::eng}},//睁 zheng
{1,0,{pysm::m,pyym::ei}},//睂 mei
{3,497,{pysm::nop,pyym::nop}},//睃 suo
{3,498,{pysm::nop,pyym::nop}},//睄 shao
{1,0,{pysm::h,pyym::an}},//睅 han
{1,0,{pysm::h,pyym::uan}},//睆 huan
{2,2065,{pysm::nop,pyym::nop}},//睇 di
{1,0,{pysm::ch,pyym::eng}},//睈 cheng
{2,2066,{pysm::nop,pyym::nop}},//睉 cuo
{1,0,{pysm::j,pyym::uan}},//睊 juan
{1,0,{pysm::nop,pyym::e}},//睋 e
{1,0,{pysm::m,pyym::an}},//睌 man
{1,0,{pysm::x,pyym::ian}},//睍 xian
{1,0,{pysm::x,pyym::i}},//睎 xi
{1,0,{pysm::k,pyym::un}},//睏 kun
{1,0,{pysm::l,pyym::ai}},//睐 lai
{1,0,{pysm::j,pyym::ian}},//睑 jian
{1,0,{pysm::sh,pyym::an}},//睒 shan
{1,0,{pysm::t,pyym::ian}},//睓 tian
{3,499,{pysm::nop,pyym::nop}},//睔 gun
{1,0,{pysm::w,pyym::an}},//睕 wan
{2,2067,{pysm::nop,pyym::nop}},//睖 leng
{1,0,{pysm::sh,pyym::i}},//睗 shi
{1,0,{pysm::q,pyym::iong}},//睘 qiong
{1,0,{pysm::l,pyym::ie}},//睙 lie
{1,0,{pysm::y,pyym::a}},//睚 ya
{1,0,{pysm::j,pyym::ing}},//睛 jing
{1,0,{pysm::zh,pyym::eng}},//睜 zheng
{1,0,{pysm::l,pyym::i}},//睝 li
{1,0,{pysm::l,pyym::ai}},//睞 lai
{2,2068,{pysm::nop,pyym::nop}},//睟 sui
{1,0,{pysm::j,pyym::uan}},//睠 juan
{1,0,{pysm::sh,pyym::ui}},//睡 shui
{3,500,{pysm::nop,pyym::nop}},//睢 sui
{1,0,{pysm::d,pyym::u}},//督 du
{1,0,{pysm::b,pyym::i}},//睤 bi
{1,0,{pysm::p,pyym::i}},//睥 pi
{1,0,{pysm::m,pyym::u}},//睦 mu
{1,0,{pysm::h,pyym::un}},//睧 hun
{1,0,{pysm::n,pyym::i}},//睨 ni
{1,0,{pysm::l,pyym::u}},//睩 lu
{4,105,{pysm::nop,pyym::nop}},//睪 yi
{2,2069,{pysm::nop,pyym::nop}},//睫 jie
{1,0,{pysm::c,pyym::ai}},//睬 cai
{1,0,{pysm::zh,pyym::ou}},//睭 zhou
{1,0,{pysm::y,pyym::u}},//睮 yu
{1,0,{pysm::h,pyym::un}},//睯 hun
{1,0,{pysm::m,pyym::a}},//睰 ma
{1,0,{pysm::x,pyym::ia}},//睱 xia
{1,0,{pysm::x,pyym::ing}},//睲 xing
{1,0,{pysm::h,pyym::ui}},//睳 hui
{1,0,{pysm::g,pyym::un}},//睴 gun
{1,0,{pysm::z,pyym::ai}},//睵 zai
{1,0,{pysm::ch,pyym::un}},//睶 chun
{1,0,{pysm::j,pyym::ian}},//睷 jian
{1,0,{pysm::m,pyym::ei}},//睸 mei
{1,0,{pysm::d,pyym::u}},//睹 du
{1,0,{pysm::h,pyym::ou}},//睺 hou
{1,0,{pysm::x,pyym::uan}},//睻 xuan
{1,0,{pysm::t,pyym::ian}},//睼 tian
{2,2070,{pysm::nop,pyym::nop}},//睽 kui
{2,2071,{pysm::nop,pyym::nop}},//睾 gao
{1,0,{pysm::r,pyym::ui}},//睿 rui
{2,2072,{pysm::nop,pyym::nop}},//瞀 mao
{1,0,{pysm::x,pyym::u}},//瞁 xu
{1,0,{pysm::f,pyym::a}},//瞂 fa
{1,0,{pysm::w,pyym::o}},//瞃 wo
{1,0,{pysm::m,pyym::iao}},//瞄 miao
{1,0,{pysm::ch,pyym::ou}},//瞅 chou
{1,0,{pysm::k,pyym::ui}},//瞆 kui
{1,0,{pysm::m,pyym::i}},//瞇 mi
{1,0,{pysm::w,pyym::eng}},//瞈 weng
{2,2073,{pysm::nop,pyym::nop}},//瞉 kou
{1,0,{pysm::d,pyym::ang}},//瞊 dang
{3,501,{pysm::nop,pyym::nop}},//瞋 chen
{1,0,{pysm::k,pyym::e}},//瞌 ke
{1,0,{pysm::s,pyym::ou}},//瞍 sou
{1,0,{pysm::x,pyym::ia}},//瞎 xia
{2,2074,{pysm::nop,pyym::nop}},//瞏 qiong
{1,0,{pysm::m,pyym::o}},//瞐 mo
{3,502,{pysm::nop,pyym::nop}},//瞑 ming
{1,0,{pysm::m,pyym::an}},//瞒 man
{1,0,{pysm::f,pyym::en}},//瞓 fen
{1,0,{pysm::z,pyym::e}},//瞔 ze
{1,0,{pysm::zh,pyym::ang}},//瞕 zhang
{1,0,{pysm::y,pyym::i}},//瞖 yi
{2,2075,{pysm::nop,pyym::nop}},//瞗 diao
{1,0,{pysm::k,pyym::ou}},//瞘 kou
{1,0,{pysm::m,pyym::o}},//瞙 mo
{1,0,{pysm::sh,pyym::un}},//瞚 shun
{1,0,{pysm::c,pyym::ong}},//瞛 cong
{2,2076,{pysm::nop,pyym::nop}},//瞜 lou
{1,0,{pysm::ch,pyym::i}},//瞝 chi
{2,2077,{pysm::nop,pyym::nop}},//瞞 man
{1,0,{pysm::p,pyym::iao}},//瞟 piao
{2,2078,{pysm::nop,pyym::nop}},//瞠 cheng
{1,0,{pysm::g,pyym::ui}},//瞡 gui
{2,2079,{pysm::nop,pyym::nop}},//瞢 meng
{1,0,{pysm::w,pyym::an}},//瞣 wan
{2,2080,{pysm::nop,pyym::nop}},//瞤 run
{2,2081,{pysm::nop,pyym::nop}},//瞥 pie
{1,0,{pysm::x,pyym::i}},//瞦 xi
{1,0,{pysm::q,pyym::iao}},//瞧 qiao
{1,0,{pysm::p,pyym::u}},//瞨 pu
{1,0,{pysm::zh,pyym::u}},//瞩 zhu
{1,0,{pysm::d,pyym::eng}},//瞪 deng
{1,0,{pysm::sh,pyym::en}},//瞫 shen
{1,0,{pysm::sh,pyym::un}},//瞬 shun
{1,0,{pysm::l,pyym::iao}},//瞭 liao
{1,0,{pysm::ch,pyym::e}},//瞮 che
{2,2082,{pysm::nop,pyym::nop}},//瞯 xian
{1,0,{pysm::k,pyym::an}},//瞰 kan
{1,0,{pysm::y,pyym::e}},//瞱 ye
{2,2083,{pysm::nop,pyym::nop}},//瞲 xu
{1,0,{pysm::t,pyym::ong}},//瞳 tong
{3,503,{pysm::nop,pyym::nop}},//瞴 mou
{2,2084,{pysm::nop,pyym::nop}},//瞵 lin
{3,504,{pysm::nop,pyym::nop}},//瞶 gui
{2,2085,{pysm::nop,pyym::nop}},//瞷 jian
{1,0,{pysm::y,pyym::e}},//瞸 ye
{1,0,{pysm::nop,pyym::ai}},//瞹 ai
{1,0,{pysm::h,pyym::ui}},//瞺 hui
{1,0,{pysm::zh,pyym::an}},//瞻 zhan
{1,0,{pysm::j,pyym::ian}},//瞼 jian
{1,0,{pysm::g,pyym::u}},//瞽 gu
{1,0,{pysm::zh,pyym::ao}},//瞾 zhao
{3,505,{pysm::nop,pyym::nop}},//瞿 qu
{1,0,{pysm::m,pyym::ei}},//矀 mei
{1,0,{pysm::ch,pyym::ou}},//矁 chou
{1,0,{pysm::s,pyym::ao}},//矂 sao
{2,2086,{pysm::nop,pyym::nop}},//矃 ning
{1,0,{pysm::x,pyym::un}},//矄 xun
{1,0,{pysm::y,pyym::ao}},//矅 yao
{4,106,{pysm::nop,pyym::nop}},//矆 huo
{1,0,{pysm::m,pyym::eng}},//矇 meng
{1,0,{pysm::m,pyym::ian}},//矈 mian
{1,0,{pysm::p,pyym::in}},//矉 pin
{1,0,{pysm::m,pyym::ian}},//矊 mian
{1,0,{pysm::l,pyym::ei}},//矋 lei
{2,2087,{pysm::nop,pyym::nop}},//矌 kuang
{1,0,{pysm::j,pyym::ue}},//矍 jue
{1,0,{pysm::x,pyym::uan}},//矎 xuan
{1,0,{pysm::m,pyym::ian}},//矏 mian
{1,0,{pysm::h,pyym::uo}},//矐 huo
{1,0,{pysm::l,pyym::u}},//矑 lu
{1,0,{pysm::m,pyym::eng}},//矒 meng
{1,0,{pysm::l,pyym::ong}},//矓 long
{2,2088,{pysm::nop,pyym::nop}},//矔 guan
{1,0,{pysm::m,pyym::an}},//矕 man
{2,2089,{pysm::nop,pyym::nop}},//矖 xi
{1,0,{pysm::ch,pyym::u}},//矗 chu
{1,0,{pysm::t,pyym::ang}},//矘 tang
{1,0,{pysm::k,pyym::an}},//矙 kan
{1,0,{pysm::zh,pyym::u}},//矚 zhu
{1,0,{pysm::m,pyym::ao}},//矛 mao
{3,506,{pysm::nop,pyym::nop}},//矜 jin
{1,0,{pysm::j,pyym::in}},//矝 jin
{3,507,{pysm::nop,pyym::nop}},//矞 yu
{1,0,{pysm::sh,pyym::uo}},//矟 shuo
{2,2090,{pysm::nop,pyym::nop}},//矠 ze
{1,0,{pysm::j,pyym::ue}},//矡 jue
{1,0,{pysm::sh,pyym::i}},//矢 shi
{2,2091,{pysm::nop,pyym::nop}},//矣 yi
{1,0,{pysm::sh,pyym::en}},//矤 shen
{1,0,{pysm::zh,pyym::i}},//知 zhi
{1,0,{pysm::h,pyym::ou}},//矦 hou
{1,0,{pysm::sh,pyym::en}},//矧 shen
{1,0,{pysm::y,pyym::ing}},//矨 ying
{1,0,{pysm::j,pyym::u}},//矩 ju
{1,0,{pysm::zh,pyym::ou}},//矪 zhou
{1,0,{pysm::j,pyym::iao}},//矫 jiao
{1,0,{pysm::c,pyym::uo}},//矬 cuo
{1,0,{pysm::d,pyym::uan}},//短 duan
{1,0,{pysm::nop,pyym::ai}},//矮 ai
{1,0,{pysm::j,pyym::iao}},//矯 jiao
{1,0,{pysm::z,pyym::eng}},//矰 zeng
{1,0,{pysm::y,pyym::ue}},//矱 yue
{1,0,{pysm::b,pyym::a}},//矲 ba
{2,2092,{pysm::nop,pyym::nop}},//石 shi
{1,0,{pysm::d,pyym::ing}},//矴 ding
{2,2093,{pysm::nop,pyym::nop}},//矵 qi
{1,0,{pysm::j,pyym::i}},//矶 ji
{1,0,{pysm::z,pyym::i}},//矷 zi
{2,2094,{pysm::nop,pyym::nop}},//矸 gan
{1,0,{pysm::w,pyym::u}},//矹 wu
{2,2095,{pysm::nop,pyym::nop}},//矺 zhe
{2,2096,{pysm::nop,pyym::nop}},//矻 ku
{3,508,{pysm::nop,pyym::nop}},//矼 gang
{1,0,{pysm::x,pyym::i}},//矽 xi
{1,0,{pysm::f,pyym::an}},//矾 fan
{1,0,{pysm::k,pyym::uang}},//矿 kuang
{1,0,{pysm::d,pyym::ang}},//砀 dang
{1,0,{pysm::m,pyym::a}},//码 ma
{1,0,{pysm::sh,pyym::a}},//砂 sha
{1,0,{pysm::d,pyym::an}},//砃 dan
{1,0,{pysm::j,pyym::ue}},//砄 jue
{1,0,{pysm::l,pyym::i}},//砅 li
{1,0,{pysm::f,pyym::u}},//砆 fu
{1,0,{pysm::m,pyym::in}},//砇 min
{1,0,{pysm::nop,pyym::e}},//砈 e
{3,509,{pysm::nop,pyym::nop}},//砉 huo
{1,0,{pysm::k,pyym::ang}},//砊 kang
{1,0,{pysm::zh,pyym::i}},//砋 zhi
{2,2097,{pysm::nop,pyym::nop}},//砌 qi
{1,0,{pysm::k,pyym::an}},//砍 kan
{1,0,{pysm::j,pyym::ie}},//砎 jie
{3,510,{pysm::nop,pyym::nop}},//砏 bin
{1,0,{pysm::nop,pyym::e}},//砐 e
{1,0,{pysm::y,pyym::a}},//砑 ya
{1,0,{pysm::p,pyym::i}},//砒 pi
{1,0,{pysm::zh,pyym::e}},//砓 zhe
{2,2098,{pysm::nop,pyym::nop}},//研 yan
{1,0,{pysm::s,pyym::ui}},//砕 sui
{1,0,{pysm::zh,pyym::uan}},//砖 zhuan
{1,0,{pysm::ch,pyym::e}},//砗 che
{1,0,{pysm::d,pyym::un}},//砘 dun
{1,0,{pysm::w,pyym::a}},//砙 wa
{1,0,{pysm::y,pyym::an}},//砚 yan
{1,0,{pysm::j,pyym::in}},//砛 jin
{1,0,{pysm::f,pyym::eng}},//砜 feng
{3,511,{pysm::nop,pyym::nop}},//砝 fa
{1,0,{pysm::m,pyym::o}},//砞 mo
{2,2099,{pysm::nop,pyym::nop}},//砟 zha
{2,2100,{pysm::nop,pyym::nop}},//砠 ju
{1,0,{pysm::y,pyym::u}},//砡 yu
{2,2101,{pysm::nop,pyym::nop}},//砢 ke
{1,0,{pysm::t,pyym::uo}},//砣 tuo
{1,0,{pysm::t,pyym::uo}},//砤 tuo
{2,2102,{pysm::nop,pyym::nop}},//砥 di
{1,0,{pysm::zh,pyym::ai}},//砦 zhai
{1,0,{pysm::zh,pyym::en}},//砧 zhen
{1,0,{pysm::nop,pyym::e}},//砨 e
{2,2103,{pysm::nop,pyym::nop}},//砩 fu
{1,0,{pysm::m,pyym::u}},//砪 mu
{1,0,{pysm::zh,pyym::u}},//砫 zhu
{2,2104,{pysm::nop,pyym::nop}},//砬 la
{1,0,{pysm::b,pyym::ian}},//砭 bian
{1,0,{pysm::n,pyym::u}},//砮 nu
{1,0,{pysm::p,pyym::ing}},//砯 ping
{2,2105,{pysm::nop,pyym::nop}},//砰 peng
{1,0,{pysm::l,pyym::ing}},//砱 ling
{3,512,{pysm::nop,pyym::nop}},//砲 pao
{1,0,{pysm::l,pyym::e}},//砳 le
{1,0,{pysm::p,pyym::o}},//破 po
{2,2106,{pysm::nop,pyym::nop}},//砵 bo
{1,0,{pysm::p,pyym::o}},//砶 po
{1,0,{pysm::sh,pyym::en}},//砷 shen
{1,0,{pysm::z,pyym::a}},//砸 za
{1,0,{pysm::nop,pyym::ai}},//砹 ai
{1,0,{pysm::l,pyym::i}},//砺 li
{1,0,{pysm::l,pyym::ong}},//砻 long
{1,0,{pysm::t,pyym::ong}},//砼 tong
{1,0,{pysm::y,pyym::ong}},//砽 yong
{1,0,{pysm::l,pyym::i}},//砾 li
{1,0,{pysm::k,pyym::uang}},//砿 kuang
{1,0,{pysm::ch,pyym::u}},//础 chu
{1,0,{pysm::k,pyym::eng}},//硁 keng
{1,0,{pysm::q,pyym::uan}},//硂 quan
{1,0,{pysm::zh,pyym::u}},//硃 zhu
{2,2107,{pysm::nop,pyym::nop}},//硄 kuang
{2,2108,{pysm::nop,pyym::nop}},//硅 gui
{1,0,{pysm::nop,pyym::e}},//硆 e
{1,0,{pysm::n,pyym::ao}},//硇 nao
{1,0,{pysm::q,pyym::ia}},//硈 qia
{1,0,{pysm::l,pyym::u}},//硉 lu
{3,513,{pysm::nop,pyym::nop}},//硊 wei
{1,0,{pysm::nop,pyym::ai}},//硋 ai
{3,514,{pysm::nop,pyym::nop}},//硌 ge
{4,107,{pysm::nop,pyym::nop}},//硍 xian
{2,2109,{pysm::nop,pyym::nop}},//硎 xing
{1,0,{pysm::y,pyym::an}},//硏 yan
{3,515,{pysm::nop,pyym::nop}},//硐 dong
{2,2110,{pysm::nop,pyym::nop}},//硑 peng
{1,0,{pysm::x,pyym::i}},//硒 xi
{1,0,{pysm::l,pyym::ao}},//硓 lao
{2,2111,{pysm::nop,pyym::nop}},//硔 hong
{1,0,{pysm::sh,pyym::uo}},//硕 shuo
{1,0,{pysm::x,pyym::ia}},//硖 xia
{1,0,{pysm::q,pyym::iao}},//硗 qiao
{1,0,{pysm::q,pyym::ing}},//硘 qing
{1,0,{pysm::w,pyym::ei}},//硙 wei
{1,0,{pysm::q,pyym::iao}},//硚 qiao
{1,0,{pysm::y,pyym::i}},//硛 yi
{2,2112,{pysm::nop,pyym::nop}},//硜 keng
{2,2113,{pysm::nop,pyym::nop}},//硝 xiao
{3,516,{pysm::nop,pyym::nop}},//硞 que
{1,0,{pysm::ch,pyym::an}},//硟 chan
{1,0,{pysm::l,pyym::ang}},//硠 lang
{1,0,{pysm::h,pyym::ong}},//硡 hong
{1,0,{pysm::y,pyym::u}},//硢 yu
{1,0,{pysm::x,pyym::iao}},//硣 xiao
{1,0,{pysm::x,pyym::ia}},//硤 xia
{2,2114,{pysm::nop,pyym::nop}},//硥 mang
{2,2115,{pysm::nop,pyym::nop}},//硦 luo
{2,2116,{pysm::nop,pyym::nop}},//硧 yong
{1,0,{pysm::ch,pyym::e}},//硨 che
{1,0,{pysm::ch,pyym::e}},//硩 che
{3,517,{pysm::nop,pyym::nop}},//硪 wo
{2,2117,{pysm::nop,pyym::nop}},//硫 liu
{2,2118,{pysm::nop,pyym::nop}},//硬 ying
{1,0,{pysm::m,pyym::ang}},//硭 mang
{1,0,{pysm::q,pyym::ue}},//确 que
{1,0,{pysm::y,pyym::an}},//硯 yan
{1,0,{pysm::sh,pyym::a}},//硰 sha
{1,0,{pysm::k,pyym::un}},//硱 kun
{1,0,{pysm::y,pyym::u}},//硲 yu
{1,0,{pysm::ch,pyym::i}},//硳 chi
{1,0,{pysm::h,pyym::ua}},//硴 hua
{1,0,{pysm::l,pyym::u}},//硵 lu
{2,2119,{pysm::nop,pyym::nop}},//硶 chen
{1,0,{pysm::j,pyym::ian}},//硷 jian
{1,0,{pysm::n,pyym::ve}},//硸 nüe
{1,0,{pysm::s,pyym::ong}},//硹 song
{1,0,{pysm::zh,pyym::uo}},//硺 zhuo
{1,0,{pysm::k,pyym::eng}},//硻 keng
{1,0,{pysm::p,pyym::eng}},//硼 peng
{1,0,{pysm::y,pyym::an}},//硽 yan
{2,2120,{pysm::nop,pyym::nop}},//硾 zhui
{1,0,{pysm::k,pyym::ong}},//硿 kong
{1,0,{pysm::ch,pyym::eng}},//碀 cheng
{1,0,{pysm::q,pyym::i}},//碁 qi
{2,2121,{pysm::nop,pyym::nop}},//碂 zong
{1,0,{pysm::q,pyym::ing}},//碃 qing
{1,0,{pysm::l,pyym::in}},//碄 lin
{1,0,{pysm::j,pyym::un}},//碅 jun
{1,0,{pysm::b,pyym::o}},//碆 bo
{1,0,{pysm::d,pyym::ing}},//碇 ding
{2,2122,{pysm::nop,pyym::nop}},//碈 min
{1,0,{pysm::d,pyym::iao}},//碉 diao
{2,2123,{pysm::nop,pyym::nop}},//碊 jian
{1,0,{pysm::h,pyym::e}},//碋 he
{3,518,{pysm::nop,pyym::nop}},//碌 lu
{1,0,{pysm::nop,pyym::ai}},//碍 ai
{1,0,{pysm::s,pyym::ui}},//碎 sui
{2,2124,{pysm::nop,pyym::nop}},//碏 que
{1,0,{pysm::l,pyym::eng}},//碐 leng
{1,0,{pysm::b,pyym::ei}},//碑 bei
{1,0,{pysm::y,pyym::in}},//碒 yin
{1,0,{pysm::d,pyym::ui}},//碓 dui
{1,0,{pysm::w,pyym::u}},//碔 wu
{1,0,{pysm::q,pyym::i}},//碕 qi
{1,0,{pysm::l,pyym::un}},//碖 lun
{1,0,{pysm::w,pyym::an}},//碗 wan
{1,0,{pysm::d,pyym::ian}},//碘 dian
{2,2125,{pysm::nop,pyym::nop}},//碙 nao
{1,0,{pysm::b,pyym::ei}},//碚 bei
{1,0,{pysm::q,pyym::i}},//碛 qi
{1,0,{pysm::ch,pyym::en}},//碜 chen
{1,0,{pysm::r,pyym::uan}},//碝 ruan
{1,0,{pysm::y,pyym::an}},//碞 yan
{2,2126,{pysm::nop,pyym::nop}},//碟 die
{1,0,{pysm::d,pyym::ing}},//碠 ding
{2,2127,{pysm::nop,pyym::nop}},//碡 du
{1,0,{pysm::t,pyym::uo}},//碢 tuo
{3,519,{pysm::nop,pyym::nop}},//碣 jie
{1,0,{pysm::y,pyym::ing}},//碤 ying
{1,0,{pysm::b,pyym::ian}},//碥 bian
{1,0,{pysm::k,pyym::e}},//碦 ke
{1,0,{pysm::b,pyym::i}},//碧 bi
{1,0,{pysm::w,pyym::ei}},//碨 wei
{1,0,{pysm::sh,pyym::uo}},//碩 shuo
{3,520,{pysm::nop,pyym::nop}},//碪 zhen
{1,0,{pysm::d,pyym::uan}},//碫 duan
{1,0,{pysm::x,pyym::ia}},//碬 xia
{1,0,{pysm::d,pyym::ang}},//碭 dang
{2,2128,{pysm::nop,pyym::nop}},//碮 ti
{1,0,{pysm::n,pyym::ao}},//碯 nao
{1,0,{pysm::p,pyym::eng}},//碰 peng
{2,2129,{pysm::nop,pyym::nop}},//碱 jian
{1,0,{pysm::d,pyym::i}},//碲 di
{1,0,{pysm::t,pyym::an}},//碳 tan
{1,0,{pysm::ch,pyym::a}},//碴 cha
{1,0,{pysm::t,pyym::ian}},//碵 tian
{1,0,{pysm::q,pyym::i}},//碶 qi
{1,0,{pysm::d,pyym::un}},//碷 dun
{1,0,{pysm::f,pyym::eng}},//碸 feng
{1,0,{pysm::x,pyym::uan}},//碹 xuan
{1,0,{pysm::q,pyym::ue}},//確 que
{2,2130,{pysm::nop,pyym::nop}},//碻 que
{1,0,{pysm::m,pyym::a}},//碼 ma
{1,0,{pysm::g,pyym::ong}},//碽 gong
{1,0,{pysm::n,pyym::ian}},//碾 nian
{2,2131,{pysm::nop,pyym::nop}},//碿 su
{1,0,{pysm::nop,pyym::e}},//磀 e
{1,0,{pysm::c,pyym::i}},//磁 ci
{1,0,{pysm::l,pyym::iu}},//磂 liu
{2,2132,{pysm::nop,pyym::nop}},//磃 si
{1,0,{pysm::t,pyym::ang}},//磄 tang
{2,2133,{pysm::nop,pyym::nop}},//磅 bang
{3,521,{pysm::nop,pyym::nop}},//磆 hua
{1,0,{pysm::p,pyym::i}},//磇 pi
{2,2134,{pysm::nop,pyym::nop}},//磈 wei
{1,0,{pysm::s,pyym::ang}},//磉 sang
{1,0,{pysm::l,pyym::ei}},//磊 lei
{1,0,{pysm::c,pyym::uo}},//磋 cuo
{1,0,{pysm::t,pyym::ian}},//磌 tian
{3,522,{pysm::nop,pyym::nop}},//磍 xia
{2,2135,{pysm::nop,pyym::nop}},//磎 xi
{2,2136,{pysm::nop,pyym::nop}},//磏 lian
{1,0,{pysm::p,pyym::an}},//磐 pan
{3,523,{pysm::nop,pyym::nop}},//磑 wei
{1,0,{pysm::y,pyym::un}},//磒 yun
{2,2137,{pysm::nop,pyym::nop}},//磓 dui
{1,0,{pysm::zh,pyym::e}},//磔 zhe
{1,0,{pysm::k,pyym::e}},//磕 ke
{1,0,{pysm::l,pyym::a}},//磖 la
{1,0,{pysm::zh,pyym::uan}},//磗 zhuan
{1,0,{pysm::y,pyym::ao}},//磘 yao
{1,0,{pysm::g,pyym::un}},//磙 gun
{3,524,{pysm::nop,pyym::nop}},//磚 zhuan
{1,0,{pysm::ch,pyym::an}},//磛 chan
{1,0,{pysm::q,pyym::i}},//磜 qi
{2,2138,{pysm::nop,pyym::nop}},//磝 ao
{1,0,{pysm::p,pyym::eng}},//磞 peng
{2,2139,{pysm::nop,pyym::nop}},//磟 liu
{1,0,{pysm::l,pyym::u}},//磠 lu
{1,0,{pysm::k,pyym::an}},//磡 kan
{1,0,{pysm::ch,pyym::uang}},//磢 chuang
{2,2140,{pysm::nop,pyym::nop}},//磣 chen
{1,0,{pysm::y,pyym::in}},//磤 yin
{1,0,{pysm::l,pyym::ei}},//磥 lei
{1,0,{pysm::b,pyym::iao}},//磦 biao
{1,0,{pysm::q,pyym::i}},//磧 qi
{1,0,{pysm::m,pyym::o}},//磨 mo
{2,2141,{pysm::nop,pyym::nop}},//磩 qi
{1,0,{pysm::c,pyym::ui}},//磪 cui
{1,0,{pysm::z,pyym::ong}},//磫 zong
{1,0,{pysm::q,pyym::ing}},//磬 qing
{1,0,{pysm::ch,pyym::uo}},//磭 chuo
{1,0,{pysm::l,pyym::un}},//磮 lun
{1,0,{pysm::j,pyym::i}},//磯 ji
{1,0,{pysm::sh,pyym::an}},//磰 shan
{1,0,{pysm::l,pyym::ao}},//磱 lao
{1,0,{pysm::q,pyym::u}},//磲 qu
{1,0,{pysm::z,pyym::eng}},//磳 zeng
{1,0,{pysm::d,pyym::eng}},//磴 deng
{1,0,{pysm::j,pyym::ian}},//磵 jian
{1,0,{pysm::x,pyym::i}},//磶 xi
{2,2142,{pysm::nop,pyym::nop}},//磷 lin
{1,0,{pysm::d,pyym::ing}},//磸 ding
{2,2143,{pysm::nop,pyym::nop}},//磹 tan
{3,525,{pysm::nop,pyym::nop}},//磺 huang
{2,2144,{pysm::nop,pyym::nop}},//磻 pan
{2,2145,{pysm::nop,pyym::nop}},//磼 za
{2,2146,{pysm::nop,pyym::nop}},//磽 qiao
{1,0,{pysm::d,pyym::i}},//磾 di
{1,0,{pysm::l,pyym::i}},//磿 li
{1,0,{pysm::j,pyym::ian}},//礀 jian
{1,0,{pysm::j,pyym::iao}},//礁 jiao
{1,0,{pysm::x,pyym::i}},//礂 xi
{1,0,{pysm::zh,pyym::ang}},//礃 zhang
{1,0,{pysm::q,pyym::iao}},//礄 qiao
{1,0,{pysm::d,pyym::un}},//礅 dun
{2,2147,{pysm::nop,pyym::nop}},//礆 jian
{1,0,{pysm::y,pyym::u}},//礇 yu
{1,0,{pysm::zh,pyym::ui}},//礈 zhui
{3,526,{pysm::nop,pyym::nop}},//礉 he
{2,2148,{pysm::nop,pyym::nop}},//礊 ke
{1,0,{pysm::z,pyym::e}},//礋 ze
{1,0,{pysm::l,pyym::ei}},//礌 lei
{1,0,{pysm::j,pyym::ie}},//礍 jie
{1,0,{pysm::ch,pyym::u}},//礎 chu
{1,0,{pysm::y,pyym::e}},//礏 ye
{2,2149,{pysm::nop,pyym::nop}},//礐 que
{1,0,{pysm::d,pyym::ang}},//礑 dang
{1,0,{pysm::y,pyym::i}},//礒 yi
{1,0,{pysm::j,pyym::iang}},//礓 jiang
{1,0,{pysm::p,pyym::i}},//礔 pi
{1,0,{pysm::p,pyym::i}},//礕 pi
{1,0,{pysm::y,pyym::u}},//礖 yu
{1,0,{pysm::p,pyym::in}},//礗 pin
{2,2150,{pysm::nop,pyym::nop}},//礘 e
{2,2151,{pysm::nop,pyym::nop}},//礙 ai
{1,0,{pysm::k,pyym::e}},//礚 ke
{1,0,{pysm::j,pyym::ian}},//礛 jian
{1,0,{pysm::y,pyym::u}},//礜 yu
{1,0,{pysm::r,pyym::uan}},//礝 ruan
{1,0,{pysm::m,pyym::eng}},//礞 meng
{1,0,{pysm::p,pyym::ao}},//礟 pao
{1,0,{pysm::c,pyym::i}},//礠 ci
{1,0,{pysm::b,pyym::o}},//礡 bo
{1,0,{pysm::y,pyym::ang}},//礢 yang
{1,0,{pysm::m,pyym::a}},//礣 ma
{1,0,{pysm::c,pyym::a}},//礤 ca
{2,2152,{pysm::nop,pyym::nop}},//礥 xian
{2,2153,{pysm::nop,pyym::nop}},//礦 kuang
{1,0,{pysm::l,pyym::ei}},//礧 lei
{1,0,{pysm::l,pyym::ei}},//礨 lei
{1,0,{pysm::zh,pyym::i}},//礩 zhi
{1,0,{pysm::l,pyym::i}},//礪 li
{2,2154,{pysm::nop,pyym::nop}},//礫 li
{1,0,{pysm::f,pyym::an}},//礬 fan
{1,0,{pysm::q,pyym::ue}},//礭 que
{1,0,{pysm::p,pyym::ao}},//礮 pao
{1,0,{pysm::y,pyym::ing}},//礯 ying
{1,0,{pysm::l,pyym::i}},//礰 li
{1,0,{pysm::l,pyym::ong}},//礱 long
{1,0,{pysm::l,pyym::ong}},//礲 long
{1,0,{pysm::m,pyym::o}},//礳 mo
{1,0,{pysm::b,pyym::o}},//礴 bo
{1,0,{pysm::sh,pyym::uang}},//礵 shuang
{1,0,{pysm::g,pyym::uan}},//礶 guan
{1,0,{pysm::l,pyym::an}},//礷 lan
{1,0,{pysm::c,pyym::a}},//礸 ca
{1,0,{pysm::y,pyym::an}},//礹 yan
{3,527,{pysm::nop,pyym::nop}},//示 shi
{1,0,{pysm::sh,pyym::i}},//礻 shi
{1,0,{pysm::l,pyym::i}},//礼 li
{1,0,{pysm::r,pyym::eng}},//礽 reng
{1,0,{pysm::sh,pyym::e}},//社 she
{1,0,{pysm::y,pyym::ue}},//礿 yue
{1,0,{pysm::s,pyym::i}},//祀 si
{2,2155,{pysm::nop,pyym::nop}},//祁 qi
{1,0,{pysm::t,pyym::a}},//祂 ta
{1,0,{pysm::m,pyym::a}},//祃 ma
{1,0,{pysm::x,pyym::ie}},//祄 xie
{1,0,{pysm::y,pyym::ao}},//祅 yao
{1,0,{pysm::x,pyym::ian}},//祆 xian
{3,528,{pysm::nop,pyym::nop}},//祇 qi
{2,2156,{pysm::nop,pyym::nop}},//祈 qi
{1,0,{pysm::zh,pyym::i}},//祉 zhi
{2,2157,{pysm::nop,pyym::nop}},//祊 beng
{1,0,{pysm::d,pyym::ui}},//祋 dui
{2,2158,{pysm::nop,pyym::nop}},//祌 zhong
{1,0,{pysm::r,pyym::en}},//祍 ren
{1,0,{pysm::y,pyym::i}},//祎 yi
{1,0,{pysm::sh,pyym::i}},//祏 shi
{1,0,{pysm::y,pyym::ou}},//祐 you
{1,0,{pysm::zh,pyym::i}},//祑 zhi
{1,0,{pysm::t,pyym::iao}},//祒 tiao
{2,2159,{pysm::nop,pyym::nop}},//祓 fu
{1,0,{pysm::f,pyym::u}},//祔 fu
{2,2160,{pysm::nop,pyym::nop}},//祕 mi
{2,2161,{pysm::nop,pyym::nop}},//祖 zu
{1,0,{pysm::zh,pyym::i}},//祗 zhi
{1,0,{pysm::s,pyym::uan}},//祘 suan
{1,0,{pysm::m,pyym::ei}},//祙 mei
{1,0,{pysm::z,pyym::uo}},//祚 zuo
{1,0,{pysm::q,pyym::u}},//祛 qu
{1,0,{pysm::h,pyym::u}},//祜 hu
{3,529,{pysm::nop,pyym::nop}},//祝 zhu
{1,0,{pysm::sh,pyym::en}},//神 shen
{1,0,{pysm::s,pyym::ui}},//祟 sui
{2,2162,{pysm::nop,pyym::nop}},//祠 ci
{1,0,{pysm::ch,pyym::ai}},//祡 chai
{2,2163,{pysm::nop,pyym::nop}},//祢 mi
{1,0,{pysm::l,pyym::v}},//祣 lü
{1,0,{pysm::y,pyym::u}},//祤 yu
{1,0,{pysm::x,pyym::iang}},//祥 xiang
{1,0,{pysm::w,pyym::u}},//祦 wu
{1,0,{pysm::t,pyym::iao}},//祧 tiao
{1,0,{pysm::p,pyym::iao}},//票 piao
{1,0,{pysm::zh,pyym::u}},//祩 zhu
{1,0,{pysm::g,pyym::ui}},//祪 gui
{1,0,{pysm::x,pyym::ia}},//祫 xia
{1,0,{pysm::zh,pyym::i}},//祬 zhi
{2,2164,{pysm::nop,pyym::nop}},//祭 ji
{1,0,{pysm::g,pyym::ao}},//祮 gao
{1,0,{pysm::zh,pyym::en}},//祯 zhen
{1,0,{pysm::g,pyym::ao}},//祰 gao
{2,2165,{pysm::nop,pyym::nop}},//祱 shui
{1,0,{pysm::j,pyym::in}},//祲 jin
{1,0,{pysm::sh,pyym::en}},//祳 shen
{1,0,{pysm::g,pyym::ai}},//祴 gai
{1,0,{pysm::k,pyym::un}},//祵 kun
{1,0,{pysm::d,pyym::i}},//祶 di
{1,0,{pysm::d,pyym::ao}},//祷 dao
{1,0,{pysm::h,pyym::uo}},//祸 huo
{1,0,{pysm::t,pyym::ao}},//祹 tao
{1,0,{pysm::q,pyym::i}},//祺 qi
{1,0,{pysm::g,pyym::u}},//祻 gu
{1,0,{pysm::g,pyym::uan}},//祼 guan
{1,0,{pysm::z,pyym::ui}},//祽 zui
{1,0,{pysm::l,pyym::ing}},//祾 ling
{1,0,{pysm::l,pyym::u}},//祿 lu
{1,0,{pysm::b,pyym::ing}},//禀 bing
{1,0,{pysm::j,pyym::in}},//禁 jin
{1,0,{pysm::d,pyym::ao}},//禂 dao
{1,0,{pysm::zh,pyym::i}},//禃 zhi
{1,0,{pysm::l,pyym::u}},//禄 lu
{2,2166,{pysm::nop,pyym::nop}},//禅 chan
{1,0,{pysm::b,pyym::i}},//禆 bi
{1,0,{pysm::zh,pyym::e}},//禇 zhe
{1,0,{pysm::h,pyym::ui}},//禈 hui
{1,0,{pysm::y,pyym::ou}},//禉 you
{1,0,{pysm::x,pyym::i}},//禊 xi
{1,0,{pysm::y,pyym::in}},//禋 yin
{1,0,{pysm::z,pyym::i}},//禌 zi
{1,0,{pysm::h,pyym::uo}},//禍 huo
{2,2167,{pysm::nop,pyym::nop}},//禎 zhen
{1,0,{pysm::f,pyym::u}},//福 fu
{1,0,{pysm::y,pyym::uan}},//禐 yuan
{1,0,{pysm::w,pyym::u}},//禑 wu
{1,0,{pysm::x,pyym::ian}},//禒 xian
{2,2168,{pysm::nop,pyym::nop}},//禓 yang
{1,0,{pysm::zh,pyym::i}},//禔 zhi
{1,0,{pysm::y,pyym::i}},//禕 yi
{1,0,{pysm::m,pyym::ei}},//禖 mei
{1,0,{pysm::s,pyym::i}},//禗 si
{1,0,{pysm::d,pyym::i}},//禘 di
{1,0,{pysm::b,pyym::ei}},//禙 bei
{1,0,{pysm::zh,pyym::uo}},//禚 zhuo
{1,0,{pysm::zh,pyym::en}},//禛 zhen
{2,2169,{pysm::nop,pyym::nop}},//禜 yong
{1,0,{pysm::j,pyym::i}},//禝 ji
{1,0,{pysm::g,pyym::ao}},//禞 gao
{1,0,{pysm::t,pyym::ang}},//禟 tang
{1,0,{pysm::s,pyym::i}},//禠 si
{1,0,{pysm::m,pyym::a}},//禡 ma
{1,0,{pysm::t,pyym::a}},//禢 ta
{1,0,{pysm::f,pyym::u}},//禣 fu
{1,0,{pysm::x,pyym::uan}},//禤 xuan
{1,0,{pysm::q,pyym::i}},//禥 qi
{1,0,{pysm::y,pyym::u}},//禦 yu
{1,0,{pysm::x,pyym::i}},//禧 xi
{2,2170,{pysm::nop,pyym::nop}},//禨 ji
{1,0,{pysm::s,pyym::i}},//禩 si
{3,530,{pysm::nop,pyym::nop}},//禪 chan
{1,0,{pysm::d,pyym::an}},//禫 dan
{1,0,{pysm::g,pyym::ui}},//禬 gui
{1,0,{pysm::s,pyym::ui}},//禭 sui
{1,0,{pysm::l,pyym::i}},//禮 li
{1,0,{pysm::n,pyym::ong}},//禯 nong
{3,531,{pysm::nop,pyym::nop}},//禰 mi
{1,0,{pysm::d,pyym::ao}},//禱 dao
{1,0,{pysm::l,pyym::i}},//禲 li
{1,0,{pysm::r,pyym::ang}},//禳 rang
{1,0,{pysm::y,pyym::ue}},//禴 yue
{1,0,{pysm::t,pyym::i}},//禵 ti
{1,0,{pysm::z,pyym::an}},//禶 zan
{1,0,{pysm::l,pyym::ei}},//禷 lei
{1,0,{pysm::r,pyym::ou}},//禸 rou
{1,0,{pysm::y,pyym::u}},//禹 yu
{1,0,{pysm::y,pyym::u}},//禺 yu
{2,2171,{pysm::nop,pyym::nop}},//离 li
{1,0,{pysm::x,pyym::ie}},//禼 xie
{1,0,{pysm::q,pyym::in}},//禽 qin
{1,0,{pysm::h,pyym::e}},//禾 he
{1,0,{pysm::t,pyym::u}},//禿 tu
{1,0,{pysm::x,pyym::iu}},//秀 xiu
{1,0,{pysm::s,pyym::i}},//私 si
{1,0,{pysm::r,pyym::en}},//秂 ren
{1,0,{pysm::t,pyym::u}},//秃 tu
{1,0,{pysm::z,pyym::i}},//秄 zi
{2,2172,{pysm::nop,pyym::nop}},//秅 cha
{1,0,{pysm::g,pyym::an}},//秆 gan
{2,2173,{pysm::nop,pyym::nop}},//秇 yi
{1,0,{pysm::x,pyym::ian}},//秈 xian
{1,0,{pysm::b,pyym::ing}},//秉 bing
{1,0,{pysm::n,pyym::ian}},//秊 nian
{1,0,{pysm::q,pyym::iu}},//秋 qiu
{1,0,{pysm::q,pyym::iu}},//秌 qiu
{2,2174,{pysm::nop,pyym::nop}},//种 zhong
{1,0,{pysm::f,pyym::en}},//秎 fen
{2,2175,{pysm::nop,pyym::nop}},//秏 hao
{1,0,{pysm::y,pyym::un}},//秐 yun
{1,0,{pysm::k,pyym::e}},//科 ke
{1,0,{pysm::m,pyym::iao}},//秒 miao
{1,0,{pysm::zh,pyym::i}},//秓 zhi
{1,0,{pysm::j,pyym::ing}},//秔 jing
{1,0,{pysm::b,pyym::i}},//秕 bi
{1,0,{pysm::zh,pyym::i}},//秖 zhi
{1,0,{pysm::y,pyym::u}},//秗 yu
{3,532,{pysm::nop,pyym::nop}},//秘 mi
{1,0,{pysm::k,pyym::u}},//秙 ku
{1,0,{pysm::b,pyym::an}},//秚 ban
{1,0,{pysm::p,pyym::i}},//秛 pi
{1,0,{pysm::n,pyym::i}},//秜 ni
{1,0,{pysm::l,pyym::i}},//秝 li
{1,0,{pysm::y,pyym::ou}},//秞 you
{2,2176,{pysm::nop,pyym::nop}},//租 zu
{1,0,{pysm::p,pyym::i}},//秠 pi
{1,0,{pysm::b,pyym::o}},//秡 bo
{1,0,{pysm::l,pyym::ing}},//秢 ling
{1,0,{pysm::m,pyym::o}},//秣 mo
{2,2177,{pysm::nop,pyym::nop}},//秤 cheng
{1,0,{pysm::n,pyym::ian}},//秥 nian
{1,0,{pysm::q,pyym::in}},//秦 qin
{1,0,{pysm::y,pyym::ang}},//秧 yang
{1,0,{pysm::z,pyym::uo}},//秨 zuo
{1,0,{pysm::zh,pyym::i}},//秩 zhi
{1,0,{pysm::zh,pyym::i}},//秪 zhi
{1,0,{pysm::sh,pyym::u}},//秫 shu
{1,0,{pysm::j,pyym::u}},//秬 ju
{1,0,{pysm::z,pyym::i}},//秭 zi
{1,0,{pysm::h,pyym::uo}},//秮 huo
{2,2178,{pysm::nop,pyym::nop}},//积 ji
{2,2179,{pysm::nop,pyym::nop}},//称 cheng
{1,0,{pysm::t,pyym::ong}},//秱 tong
{2,2180,{pysm::nop,pyym::nop}},//秲 zhi
{2,2181,{pysm::nop,pyym::nop}},//秳 huo
{2,2182,{pysm::nop,pyym::nop}},//秴 he
{1,0,{pysm::y,pyym::in}},//秵 yin
{1,0,{pysm::z,pyym::i}},//秶 zi
{1,0,{pysm::zh,pyym::i}},//秷 zhi
{2,2183,{pysm::nop,pyym::nop}},//秸 jie
{1,0,{pysm::r,pyym::en}},//秹 ren
{1,0,{pysm::d,pyym::u}},//秺 du
{2,2184,{pysm::nop,pyym::nop}},//移 yi
{1,0,{pysm::zh,pyym::u}},//秼 zhu
{1,0,{pysm::h,pyym::ui}},//秽 hui
{1,0,{pysm::n,pyym::ong}},//秾 nong
{3,533,{pysm::nop,pyym::nop}},//秿 fu
{1,0,{pysm::x,pyym::i}},//稀 xi
{1,0,{pysm::g,pyym::ao}},//稁 gao
{1,0,{pysm::l,pyym::ang}},//稂 lang
{1,0,{pysm::f,pyym::u}},//稃 fu
{2,2185,{pysm::nop,pyym::nop}},//稄 xun
{1,0,{pysm::sh,pyym::ui}},//稅 shui
{1,0,{pysm::l,pyym::v}},//稆 lü
{1,0,{pysm::k,pyym::un}},//稇 kun
{1,0,{pysm::g,pyym::an}},//稈 gan
{1,0,{pysm::j,pyym::ing}},//稉 jing
{1,0,{pysm::t,pyym::i}},//稊 ti
{1,0,{pysm::ch,pyym::eng}},//程 cheng
{2,2186,{pysm::nop,pyym::nop}},//稌 tu
{1,0,{pysm::sh,pyym::ao}},//稍 shao
{4,108,{pysm::nop,pyym::nop}},//税 shui
{1,0,{pysm::y,pyym::a}},//稏 ya
{1,0,{pysm::l,pyym::un}},//稐 lun
{1,0,{pysm::l,pyym::u}},//稑 lu
{1,0,{pysm::g,pyym::u}},//稒 gu
{1,0,{pysm::z,pyym::uo}},//稓 zuo
{1,0,{pysm::r,pyym::en}},//稔 ren
{1,0,{pysm::zh,pyym::un}},//稕 zhun
{1,0,{pysm::b,pyym::ang}},//稖 bang
{1,0,{pysm::b,pyym::ai}},//稗 bai
{2,2187,{pysm::nop,pyym::nop}},//稘 ji
{1,0,{pysm::zh,pyym::i}},//稙 zhi
{1,0,{pysm::zh,pyym::i}},//稚 zhi
{1,0,{pysm::k,pyym::un}},//稛 kun
{2,2188,{pysm::nop,pyym::nop}},//稜 leng
{1,0,{pysm::p,pyym::eng}},//稝 peng
{2,2189,{pysm::nop,pyym::nop}},//稞 ke
{2,2190,{pysm::nop,pyym::nop}},//稟 bing
{3,534,{pysm::nop,pyym::nop}},//稠 chou
{3,535,{pysm::nop,pyym::nop}},//稡 zui
{1,0,{pysm::y,pyym::u}},//稢 yu
{1,0,{pysm::s,pyym::u}},//稣 su
{1,0,{pysm::l,pyym::ve}},//稤 lüe
{1,0,{pysm::x,pyym::iang}},//稥 xiang
{1,0,{pysm::y,pyym::i}},//稦 yi
{2,2191,{pysm::nop,pyym::nop}},//稧 xi
{1,0,{pysm::b,pyym::ian}},//稨 bian
{1,0,{pysm::j,pyym::i}},//稩 ji
{1,0,{pysm::f,pyym::u}},//稪 fu
{2,2192,{pysm::nop,pyym::nop}},//稫 pi
{1,0,{pysm::n,pyym::uo}},//稬 nuo
{1,0,{pysm::j,pyym::ie}},//稭 jie
{2,2193,{pysm::nop,pyym::nop}},//種 zhong
{1,0,{pysm::z,pyym::ong}},//稯 zong
{1,0,{pysm::x,pyym::u}},//稰 xu
{2,2194,{pysm::nop,pyym::nop}},//稱 cheng
{1,0,{pysm::d,pyym::ao}},//稲 dao
{1,0,{pysm::w,pyym::en}},//稳 wen
{3,536,{pysm::nop,pyym::nop}},//稴 xian
{2,2195,{pysm::nop,pyym::nop}},//稵 zi
{1,0,{pysm::y,pyym::u}},//稶 yu
{2,2196,{pysm::nop,pyym::nop}},//稷 ji
{1,0,{pysm::x,pyym::u}},//稸 xu
{2,2197,{pysm::nop,pyym::nop}},//稹 zhen
{1,0,{pysm::zh,pyym::i}},//稺 zhi
{1,0,{pysm::d,pyym::ao}},//稻 dao
{1,0,{pysm::j,pyym::ia}},//稼 jia
{2,2198,{pysm::nop,pyym::nop}},//稽 ji
{3,537,{pysm::nop,pyym::nop}},//稾 gao
{1,0,{pysm::g,pyym::ao}},//稿 gao
{1,0,{pysm::g,pyym::u}},//穀 gu
{1,0,{pysm::r,pyym::ong}},//穁 rong
{1,0,{pysm::s,pyym::ui}},//穂 sui
{1,0,{pysm::r,pyym::ong}},//穃 rong
{1,0,{pysm::j,pyym::i}},//穄 ji
{1,0,{pysm::k,pyym::ang}},//穅 kang
{1,0,{pysm::m,pyym::u}},//穆 mu
{3,538,{pysm::nop,pyym::nop}},//穇 can
{3,539,{pysm::nop,pyym::nop}},//穈 mei
{3,540,{pysm::nop,pyym::nop}},//穉 zhi
{1,0,{pysm::j,pyym::i}},//穊 ji
{2,2199,{pysm::nop,pyym::nop}},//穋 lu
{1,0,{pysm::s,pyym::u}},//穌 su
{1,0,{pysm::j,pyym::i}},//積 ji
{1,0,{pysm::y,pyym::ing}},//穎 ying
{1,0,{pysm::w,pyym::en}},//穏 wen
{1,0,{pysm::q,pyym::iu}},//穐 qiu
{1,0,{pysm::s,pyym::e}},//穑 se
{1,0,{pysm::h,pyym::e}},//穒 he
{1,0,{pysm::y,pyym::i}},//穓 yi
{1,0,{pysm::h,pyym::uang}},//穔 huang
{1,0,{pysm::q,pyym::ie}},//穕 qie
{1,0,{pysm::j,pyym::i}},//穖 ji
{1,0,{pysm::s,pyym::ui}},//穗 sui
{2,2200,{pysm::nop,pyym::nop}},//穘 xiao
{1,0,{pysm::p,pyym::u}},//穙 pu
{1,0,{pysm::j,pyym::iao}},//穚 jiao
{2,2201,{pysm::nop,pyym::nop}},//穛 zhuo
{2,2202,{pysm::nop,pyym::nop}},//穜 zhong
{1,0,{pysm::z,pyym::ui}},//穝 zui
{1,0,{pysm::l,pyym::v}},//穞 lü
{1,0,{pysm::s,pyym::ui}},//穟 sui
{1,0,{pysm::n,pyym::ong}},//穠 nong
{1,0,{pysm::s,pyym::e}},//穡 se
{1,0,{pysm::h,pyym::ui}},//穢 hui
{1,0,{pysm::r,pyym::ang}},//穣 rang
{1,0,{pysm::n,pyym::uo}},//穤 nuo
{1,0,{pysm::y,pyym::u}},//穥 yu
{1,0,{pysm::p,pyym::in}},//穦 pin
{2,2203,{pysm::nop,pyym::nop}},//穧 ji
{1,0,{pysm::t,pyym::ui}},//穨 tui
{1,0,{pysm::w,pyym::en}},//穩 wen
{2,2204,{pysm::nop,pyym::nop}},//穪 cheng
{2,2205,{pysm::nop,pyym::nop}},//穫 huo
{1,0,{pysm::k,pyym::uang}},//穬 kuang
{1,0,{pysm::l,pyym::v}},//穭 lü
{2,2206,{pysm::nop,pyym::nop}},//穮 biao
{1,0,{pysm::s,pyym::e}},//穯 se
{2,2207,{pysm::nop,pyym::nop}},//穰 rang
{2,2208,{pysm::nop,pyym::nop}},//穱 zhuo
{1,0,{pysm::l,pyym::i}},//穲 li
{2,2209,{pysm::nop,pyym::nop}},//穳 cuan
{2,2210,{pysm::nop,pyym::nop}},//穴 xue
{2,2211,{pysm::nop,pyym::nop}},//穵 wa
{1,0,{pysm::j,pyym::iu}},//究 jiu
{1,0,{pysm::q,pyym::iong}},//穷 qiong
{1,0,{pysm::x,pyym::i}},//穸 xi
{2,2212,{pysm::nop,pyym::nop}},//穹 qiong
{1,0,{pysm::k,pyym::ong}},//空 kong
{1,0,{pysm::y,pyym::u}},//穻 yu
{1,0,{pysm::sh,pyym::en}},//穼 shen
{1,0,{pysm::j,pyym::ing}},//穽 jing
{1,0,{pysm::y,pyym::ao}},//穾 yao
{2,2213,{pysm::nop,pyym::nop}},//穿 chuan
{2,2214,{pysm::nop,pyym::nop}},//窀 zhun
{1,0,{pysm::t,pyym::u}},//突 tu
{1,0,{pysm::l,pyym::ao}},//窂 lao
{1,0,{pysm::q,pyym::ie}},//窃 qie
{1,0,{pysm::zh,pyym::ai}},//窄 zhai
{1,0,{pysm::y,pyym::ao}},//窅 yao
{1,0,{pysm::b,pyym::ian}},//窆 bian
{1,0,{pysm::b,pyym::ao}},//窇 bao
{1,0,{pysm::y,pyym::ao}},//窈 yao
{1,0,{pysm::b,pyym::ing}},//窉 bing
{1,0,{pysm::w,pyym::a}},//窊 wa
{2,2215,{pysm::nop,pyym::nop}},//窋 zhu
{4,109,{pysm::nop,pyym::nop}},//窌 jiao
{1,0,{pysm::q,pyym::iao}},//窍 qiao
{1,0,{pysm::d,pyym::iao}},//窎 diao
{1,0,{pysm::w,pyym::u}},//窏 wu
{2,2216,{pysm::nop,pyym::nop}},//窐 gui
{1,0,{pysm::y,pyym::ao}},//窑 yao
{2,2217,{pysm::nop,pyym::nop}},//窒 zhi
{1,0,{pysm::ch,pyym::uang}},//窓 chuang
{1,0,{pysm::y,pyym::ao}},//窔 yao
{1,0,{pysm::t,pyym::iao}},//窕 tiao
{2,2218,{pysm::nop,pyym::nop}},//窖 jiao
{2,2219,{pysm::nop,pyym::nop}},//窗 chuang
{1,0,{pysm::j,pyym::iong}},//窘 jiong
{1,0,{pysm::x,pyym::iao}},//窙 xiao
{1,0,{pysm::ch,pyym::eng}},//窚 cheng
{1,0,{pysm::k,pyym::ou}},//窛 kou
{1,0,{pysm::c,pyym::uan}},//窜 cuan
{1,0,{pysm::w,pyym::o}},//窝 wo
{1,0,{pysm::d,pyym::an}},//窞 dan
{1,0,{pysm::k,pyym::u}},//窟 ku
{1,0,{pysm::k,pyym::e}},//窠 ke
{1,0,{pysm::zh,pyym::uo}},//窡 zhuo
{1,0,{pysm::x,pyym::u}},//窢 xu
{1,0,{pysm::s,pyym::u}},//窣 su
{1,0,{pysm::g,pyym::uan}},//窤 guan
{1,0,{pysm::k,pyym::ui}},//窥 kui
{1,0,{pysm::d,pyym::ou}},//窦 dou
{1,0,{pysm::zh,pyym::uo}},//窧 zhuo
{2,2220,{pysm::nop,pyym::nop}},//窨 xun
{1,0,{pysm::w,pyym::o}},//窩 wo
{1,0,{pysm::w,pyym::a}},//窪 wa
{2,2221,{pysm::nop,pyym::nop}},//窫 ya
{2,2222,{pysm::nop,pyym::nop}},//窬 yu
{1,0,{pysm::j,pyym::u}},//窭 ju
{1,0,{pysm::q,pyym::iong}},//窮 qiong
{2,2223,{pysm::nop,pyym::nop}},//窯 yao
{1,0,{pysm::y,pyym::ao}},//窰 yao
{1,0,{pysm::t,pyym::iao}},//窱 tiao
{1,0,{pysm::ch,pyym::ao}},//窲 chao
{1,0,{pysm::y,pyym::u}},//窳 yu
{1,0,{pysm::t,pyym::ian}},//窴 tian
{1,0,{pysm::d,pyym::iao}},//窵 diao
{2,2224,{pysm::nop,pyym::nop}},//窶 ju
{1,0,{pysm::l,pyym::iao}},//窷 liao
{1,0,{pysm::x,pyym::i}},//窸 xi
{1,0,{pysm::w,pyym::u}},//窹 wu
{1,0,{pysm::k,pyym::ui}},//窺 kui
{1,0,{pysm::ch,pyym::uang}},//窻 chuang
{2,2225,{pysm::nop,pyym::nop}},//窼 zhao
{1,0,{pysm::k,pyym::uan}},//窽 kuan
{2,2226,{pysm::nop,pyym::nop}},//窾 kuan
{1,0,{pysm::l,pyym::ong}},//窿 long
{1,0,{pysm::ch,pyym::eng}},//竀 cheng
{1,0,{pysm::c,pyym::ui}},//竁 cui
{1,0,{pysm::l,pyym::iao}},//竂 liao
{1,0,{pysm::z,pyym::ao}},//竃 zao
{1,0,{pysm::c,pyym::uan}},//竄 cuan
{1,0,{pysm::q,pyym::iao}},//竅 qiao
{1,0,{pysm::q,pyym::iong}},//竆 qiong
{2,2227,{pysm::nop,pyym::nop}},//竇 dou
{1,0,{pysm::z,pyym::ao}},//竈 zao
{1,0,{pysm::l,pyym::ong}},//竉 long
{1,0,{pysm::q,pyym::ie}},//竊 qie
{2,2228,{pysm::nop,pyym::nop}},//立 li
{1,0,{pysm::ch,pyym::u}},//竌 chu
{1,0,{pysm::sh,pyym::i}},//竍 shi
{1,0,{pysm::f,pyym::u}},//竎 fu
{1,0,{pysm::q,pyym::ian}},//竏 qian
{1,0,{pysm::ch,pyym::u}},//竐 chu
{1,0,{pysm::h,pyym::ong}},//竑 hong
{1,0,{pysm::q,pyym::i}},//竒 qi
{1,0,{pysm::h,pyym::ao}},//竓 hao
{1,0,{pysm::sh,pyym::eng}},//竔 sheng
{1,0,{pysm::f,pyym::en}},//竕 fen
{1,0,{pysm::sh,pyym::u}},//竖 shu
{1,0,{pysm::m,pyym::iao}},//竗 miao
{2,2229,{pysm::nop,pyym::nop}},//竘 qu
{1,0,{pysm::zh,pyym::an}},//站 zhan
{1,0,{pysm::zh,pyym::u}},//竚 zhu
{1,0,{pysm::l,pyym::ing}},//竛 ling
{2,2230,{pysm::nop,pyym::nop}},//竜 long
{1,0,{pysm::b,pyym::ing}},//竝 bing
{1,0,{pysm::j,pyym::ing}},//竞 jing
{1,0,{pysm::j,pyym::ing}},//竟 jing
{1,0,{pysm::zh,pyym::ang}},//章 zhang
{1,0,{pysm::b,pyym::ai}},//竡 bai
{1,0,{pysm::s,pyym::i}},//竢 si
{1,0,{pysm::j,pyym::un}},//竣 jun
{1,0,{pysm::h,pyym::ong}},//竤 hong
{2,2231,{pysm::nop,pyym::nop}},//童 tong
{1,0,{pysm::s,pyym::ong}},//竦 song
{2,2232,{pysm::nop,pyym::nop}},//竧 jing
{1,0,{pysm::d,pyym::iao}},//竨 diao
{1,0,{pysm::y,pyym::i}},//竩 yi
{1,0,{pysm::sh,pyym::u}},//竪 shu
{1,0,{pysm::j,pyym::ing}},//竫 jing
{1,0,{pysm::q,pyym::u}},//竬 qu
{1,0,{pysm::j,pyym::ie}},//竭 jie
{1,0,{pysm::p,pyym::ing}},//竮 ping
{1,0,{pysm::d,pyym::uan}},//端 duan
{1,0,{pysm::l,pyym::i}},//竰 li
{1,0,{pysm::zh,pyym::uan}},//竱 zhuan
{1,0,{pysm::c,pyym::eng}},//竲 ceng
{1,0,{pysm::d,pyym::eng}},//竳 deng
{1,0,{pysm::c,pyym::un}},//竴 cun
{2,2233,{pysm::nop,pyym::nop}},//竵 wai
{1,0,{pysm::j,pyym::ing}},//競 jing
{1,0,{pysm::k,pyym::an}},//竷 kan
{1,0,{pysm::j,pyym::ing}},//竸 jing
{1,0,{pysm::zh,pyym::u}},//竹 zhu
{2,2234,{pysm::nop,pyym::nop}},//竺 zhu
{2,2235,{pysm::nop,pyym::nop}},//竻 le
{1,0,{pysm::p,pyym::eng}},//竼 peng
{1,0,{pysm::y,pyym::u}},//竽 yu
{1,0,{pysm::ch,pyym::i}},//竾 chi
{1,0,{pysm::g,pyym::an}},//竿 gan
{1,0,{pysm::m,pyym::ang}},//笀 mang
{1,0,{pysm::zh,pyym::u}},//笁 zhu
{1,0,{pysm::w,pyym::an}},//笂 wan
{1,0,{pysm::d,pyym::u}},//笃 du
{1,0,{pysm::j,pyym::i}},//笄 ji
{1,0,{pysm::j,pyym::iao}},//笅 jiao
{1,0,{pysm::b,pyym::a}},//笆 ba
{1,0,{pysm::s,pyym::uan}},//笇 suan
{1,0,{pysm::j,pyym::i}},//笈 ji
{1,0,{pysm::q,pyym::in}},//笉 qin
{1,0,{pysm::zh,pyym::ao}},//笊 zhao
{1,0,{pysm::s,pyym::un}},//笋 sun
{1,0,{pysm::y,pyym::a}},//笌 ya
{2,2236,{pysm::nop,pyym::nop}},//笍 zhui
{1,0,{pysm::y,pyym::uan}},//笎 yuan
{3,541,{pysm::nop,pyym::nop}},//笏 hu
{1,0,{pysm::h,pyym::ang}},//笐 hang
{1,0,{pysm::x,pyym::iao}},//笑 xiao
{3,542,{pysm::nop,pyym::nop}},//笒 cen
{2,2237,{pysm::nop,pyym::nop}},//笓 bi
{1,0,{pysm::b,pyym::i}},//笔 bi
{1,0,{pysm::j,pyym::ian}},//笕 jian
{1,0,{pysm::y,pyym::i}},//笖 yi
{1,0,{pysm::d,pyym::ong}},//笗 dong
{1,0,{pysm::sh,pyym::an}},//笘 shan
{1,0,{pysm::sh,pyym::eng}},//笙 sheng
{3,543,{pysm::nop,pyym::nop}},//笚 da
{1,0,{pysm::d,pyym::i}},//笛 di
{1,0,{pysm::zh,pyym::u}},//笜 zhu
{1,0,{pysm::n,pyym::a}},//笝 na
{1,0,{pysm::ch,pyym::i}},//笞 chi
{1,0,{pysm::g,pyym::u}},//笟 gu
{1,0,{pysm::l,pyym::i}},//笠 li
{1,0,{pysm::q,pyym::ie}},//笡 qie
{1,0,{pysm::m,pyym::in}},//笢 min
{1,0,{pysm::b,pyym::ao}},//笣 bao
{2,2238,{pysm::nop,pyym::nop}},//笤 tiao
{1,0,{pysm::s,pyym::i}},//笥 si
{1,0,{pysm::f,pyym::u}},//符 fu
{2,2239,{pysm::nop,pyym::nop}},//笧 ce
{1,0,{pysm::b,pyym::en}},//笨 ben
{1,0,{pysm::f,pyym::a}},//笩 fa
{1,0,{pysm::d,pyym::a}},//笪 da
{1,0,{pysm::z,pyym::i}},//笫 zi
{1,0,{pysm::d,pyym::i}},//第 di
{1,0,{pysm::l,pyym::ing}},//笭 ling
{3,544,{pysm::nop,pyym::nop}},//笮 ze
{1,0,{pysm::n,pyym::u}},//笯 nu
{2,2240,{pysm::nop,pyym::nop}},//笰 fu
{1,0,{pysm::g,pyym::ou}},//笱 gou
{1,0,{pysm::f,pyym::an}},//笲 fan
{1,0,{pysm::j,pyym::ia}},//笳 jia
{1,0,{pysm::g,pyym::an}},//笴 gan
{1,0,{pysm::f,pyym::an}},//笵 fan
{1,0,{pysm::sh,pyym::i}},//笶 shi
{1,0,{pysm::m,pyym::ao}},//笷 mao
{1,0,{pysm::p,pyym::o}},//笸 po
{1,0,{pysm::t,pyym::i}},//笹 ti
{1,0,{pysm::j,pyym::ian}},//笺 jian
{1,0,{pysm::q,pyym::iong}},//笻 qiong
{1,0,{pysm::l,pyym::ong}},//笼 long
{1,0,{pysm::m,pyym::in}},//笽 min
{1,0,{pysm::b,pyym::ian}},//笾 bian
{1,0,{pysm::l,pyym::uo}},//笿 luo
{1,0,{pysm::g,pyym::ui}},//筀 gui
{1,0,{pysm::q,pyym::u}},//筁 qu
{1,0,{pysm::ch,pyym::i}},//筂 chi
{1,0,{pysm::y,pyym::in}},//筃 yin
{1,0,{pysm::y,pyym::ao}},//筄 yao
{1,0,{pysm::x,pyym::ian}},//筅 xian
{1,0,{pysm::b,pyym::i}},//筆 bi
{1,0,{pysm::q,pyym::iong}},//筇 qiong
{1,0,{pysm::k,pyym::uo}},//筈 kuo
{1,0,{pysm::d,pyym::eng}},//等 deng
{2,2241,{pysm::nop,pyym::nop}},//筊 xiao
{2,2242,{pysm::nop,pyym::nop}},//筋 jin
{1,0,{pysm::q,pyym::uan}},//筌 quan
{3,545,{pysm::nop,pyym::nop}},//筍 sun
{1,0,{pysm::r,pyym::u}},//筎 ru
{1,0,{pysm::f,pyym::a}},//筏 fa
{1,0,{pysm::k,pyym::uang}},//筐 kuang
{1,0,{pysm::zh,pyym::u}},//筑 zhu
{2,2243,{pysm::nop,pyym::nop}},//筒 tong
{1,0,{pysm::j,pyym::i}},//筓 ji
{1,0,{pysm::d,pyym::a}},//答 da
{1,0,{pysm::h,pyym::ang}},//筕 hang
{1,0,{pysm::c,pyym::e}},//策 ce
{1,0,{pysm::zh,pyym::ong}},//筗 zhong
{1,0,{pysm::k,pyym::ou}},//筘 kou
{1,0,{pysm::l,pyym::ai}},//筙 lai
{1,0,{pysm::b,pyym::i}},//筚 bi
{1,0,{pysm::sh,pyym::ai}},//筛 shai
{1,0,{pysm::d,pyym::ang}},//筜 dang
{1,0,{pysm::zh,pyym::eng}},//筝 zheng
{1,0,{pysm::c,pyym::e}},//筞 ce
{1,0,{pysm::f,pyym::u}},//筟 fu
{2,2244,{pysm::nop,pyym::nop}},//筠 yun
{1,0,{pysm::t,pyym::u}},//筡 tu
{1,0,{pysm::p,pyym::a}},//筢 pa
{1,0,{pysm::l,pyym::i}},//筣 li
{1,0,{pysm::l,pyym::ang}},//筤 lang
{1,0,{pysm::j,pyym::u}},//筥 ju
{1,0,{pysm::g,pyym::uan}},//筦 guan
{2,2245,{pysm::nop,pyym::nop}},//筧 jian
{1,0,{pysm::h,pyym::an}},//筨 han
{3,546,{pysm::nop,pyym::nop}},//筩 tong
{1,0,{pysm::x,pyym::ia}},//筪 xia
{1,0,{pysm::zh,pyym::i}},//筫 zhi
{1,0,{pysm::ch,pyym::eng}},//筬 cheng
{1,0,{pysm::s,pyym::uan}},//筭 suan
{1,0,{pysm::sh,pyym::i}},//筮 shi
{1,0,{pysm::zh,pyym::u}},//筯 zhu
{1,0,{pysm::z,pyym::uo}},//筰 zuo
{1,0,{pysm::x,pyym::iao}},//筱 xiao
{1,0,{pysm::sh,pyym::ao}},//筲 shao
{1,0,{pysm::t,pyym::ing}},//筳 ting
{2,2246,{pysm::nop,pyym::nop}},//筴 ce
{1,0,{pysm::y,pyym::an}},//筵 yan
{1,0,{pysm::g,pyym::ao}},//筶 gao
{1,0,{pysm::k,pyym::uai}},//筷 kuai
{1,0,{pysm::g,pyym::an}},//筸 gan
{1,0,{pysm::ch,pyym::ou}},//筹 chou
{1,0,{pysm::k,pyym::uang}},//筺 kuang
{1,0,{pysm::g,pyym::ang}},//筻 gang
{1,0,{pysm::y,pyym::un}},//筼 yun
{2,2247,{pysm::nop,pyym::nop}},//筽 ou
{1,0,{pysm::q,pyym::ian}},//签 qian
{1,0,{pysm::x,pyym::iao}},//筿 xiao
{1,0,{pysm::j,pyym::ian}},//简 jian
{4,110,{pysm::nop,pyym::nop}},//箁 pou
{1,0,{pysm::l,pyym::ai}},//箂 lai
{1,0,{pysm::z,pyym::ou}},//箃 zou
{3,547,{pysm::nop,pyym::nop}},//箄 bi
{1,0,{pysm::b,pyym::i}},//箅 bi
{1,0,{pysm::b,pyym::i}},//箆 bi
{1,0,{pysm::g,pyym::e}},//箇 ge
{2,2248,{pysm::nop,pyym::nop}},//箈 tai
{2,2249,{pysm::nop,pyym::nop}},//箉 guai
{1,0,{pysm::y,pyym::u}},//箊 yu
{1,0,{pysm::j,pyym::ian}},//箋 jian
{2,2250,{pysm::nop,pyym::nop}},//箌 dao
{1,0,{pysm::g,pyym::u}},//箍 gu
{2,2251,{pysm::nop,pyym::nop}},//箎 chi
{1,0,{pysm::zh,pyym::eng}},//箏 zheng
{3,548,{pysm::nop,pyym::nop}},//箐 qing
{2,2252,{pysm::nop,pyym::nop}},//箑 sha
{1,0,{pysm::zh,pyym::ou}},//箒 zhou
{1,0,{pysm::l,pyym::u}},//箓 lu
{1,0,{pysm::b,pyym::o}},//箔 bo
{1,0,{pysm::j,pyym::i}},//箕 ji
{1,0,{pysm::l,pyym::in}},//箖 lin
{1,0,{pysm::s,pyym::uan}},//算 suan
{2,2253,{pysm::nop,pyym::nop}},//箘 jun
{1,0,{pysm::f,pyym::u}},//箙 fu
{1,0,{pysm::zh,pyym::a}},//箚 zha
{1,0,{pysm::g,pyym::u}},//箛 gu
{1,0,{pysm::k,pyym::ong}},//箜 kong
{1,0,{pysm::q,pyym::ian}},//箝 qian
{1,0,{pysm::q,pyym::ian}},//箞 qian
{1,0,{pysm::j,pyym::un}},//箟 jun
{2,2254,{pysm::nop,pyym::nop}},//箠 chui
{1,0,{pysm::g,pyym::uan}},//管 guan
{2,2255,{pysm::nop,pyym::nop}},//箢 yuan
{1,0,{pysm::c,pyym::e}},//箣 ce
{1,0,{pysm::z,pyym::u}},//箤 zu
{1,0,{pysm::b,pyym::o}},//箥 bo
{1,0,{pysm::z,pyym::e}},//箦 ze
{1,0,{pysm::q,pyym::ie}},//箧 qie
{1,0,{pysm::t,pyym::uo}},//箨 tuo
{1,0,{pysm::l,pyym::uo}},//箩 luo
{1,0,{pysm::d,pyym::an}},//箪 dan
{1,0,{pysm::x,pyym::iao}},//箫 xiao
{2,2256,{pysm::nop,pyym::nop}},//箬 ruo
{1,0,{pysm::j,pyym::ian}},//箭 jian
{1,0,{pysm::x,pyym::uan}},//箮 xuan
{1,0,{pysm::b,pyym::ian}},//箯 bian
{1,0,{pysm::s,pyym::un}},//箰 sun
{1,0,{pysm::x,pyym::iang}},//箱 xiang
{1,0,{pysm::x,pyym::ian}},//箲 xian
{1,0,{pysm::p,pyym::ing}},//箳 ping
{2,2257,{pysm::nop,pyym::nop}},//箴 zhen
{2,2258,{pysm::nop,pyym::nop}},//箵 xing
{1,0,{pysm::h,pyym::u}},//箶 hu
{2,2259,{pysm::nop,pyym::nop}},//箷 yi
{2,2260,{pysm::nop,pyym::nop}},//箸 zhu
{3,549,{pysm::nop,pyym::nop}},//箹 yue
{1,0,{pysm::ch,pyym::un}},//箺 chun
{1,0,{pysm::l,pyym::v}},//箻 lü
{1,0,{pysm::w,pyym::u}},//箼 wu
{1,0,{pysm::d,pyym::ong}},//箽 dong
{3,550,{pysm::nop,pyym::nop}},//箾 shuo
{1,0,{pysm::j,pyym::i}},//箿 ji
{1,0,{pysm::j,pyym::ie}},//節 jie
{1,0,{pysm::h,pyym::uang}},//篁 huang
{1,0,{pysm::x,pyym::ing}},//篂 xing
{1,0,{pysm::m,pyym::ei}},//篃 mei
{1,0,{pysm::f,pyym::an}},//範 fan
{2,2261,{pysm::nop,pyym::nop}},//篅 chuan
{1,0,{pysm::zh,pyym::uan}},//篆 zhuan
{1,0,{pysm::p,pyym::ian}},//篇 pian
{1,0,{pysm::f,pyym::eng}},//篈 feng
{1,0,{pysm::zh,pyym::u}},//築 zhu
{2,2262,{pysm::nop,pyym::nop}},//篊 huang
{1,0,{pysm::q,pyym::ie}},//篋 qie
{1,0,{pysm::h,pyym::ou}},//篌 hou
{1,0,{pysm::q,pyym::iu}},//篍 qiu
{1,0,{pysm::m,pyym::iao}},//篎 miao
{1,0,{pysm::q,pyym::ian}},//篏 qian
{1,0,{pysm::g,pyym::u}},//篐 gu
{1,0,{pysm::k,pyym::ui}},//篑 kui
{1,0,{pysm::sh,pyym::i}},//篒 shi
{1,0,{pysm::l,pyym::ou}},//篓 lou
{2,2263,{pysm::nop,pyym::nop}},//篔 yun
{1,0,{pysm::h,pyym::e}},//篕 he
{1,0,{pysm::t,pyym::ang}},//篖 tang
{1,0,{pysm::y,pyym::ue}},//篗 yue
{1,0,{pysm::ch,pyym::ou}},//篘 chou
{1,0,{pysm::g,pyym::ao}},//篙 gao
{1,0,{pysm::f,pyym::ei}},//篚 fei
{1,0,{pysm::r,pyym::uo}},//篛 ruo
{1,0,{pysm::zh,pyym::eng}},//篜 zheng
{1,0,{pysm::g,pyym::ou}},//篝 gou
{1,0,{pysm::n,pyym::ie}},//篞 nie
{1,0,{pysm::q,pyym::ian}},//篟 qian
{1,0,{pysm::x,pyym::iao}},//篠 xiao
{1,0,{pysm::c,pyym::uan}},//篡 cuan
{3,551,{pysm::nop,pyym::nop}},//篢 long
{2,2264,{pysm::nop,pyym::nop}},//篣 peng
{1,0,{pysm::d,pyym::u}},//篤 du
{1,0,{pysm::l,pyym::i}},//篥 li
{2,2265,{pysm::nop,pyym::nop}},//篦 bi
{2,2266,{pysm::nop,pyym::nop}},//篧 zhuo
{1,0,{pysm::ch,pyym::u}},//篨 chu
{2,2267,{pysm::nop,pyym::nop}},//篩 shai
{1,0,{pysm::ch,pyym::i}},//篪 chi
{1,0,{pysm::zh,pyym::u}},//篫 zhu
{2,2268,{pysm::nop,pyym::nop}},//篬 qiang
{1,0,{pysm::l,pyym::ong}},//篭 long
{1,0,{pysm::l,pyym::an}},//篮 lan
{1,0,{pysm::j,pyym::ian}},//篯 jian
{1,0,{pysm::b,pyym::u}},//篰 bu
{1,0,{pysm::l,pyym::i}},//篱 li
{2,2269,{pysm::nop,pyym::nop}},//篲 hui
{1,0,{pysm::b,pyym::i}},//篳 bi
{2,2270,{pysm::nop,pyym::nop}},//篴 di
{1,0,{pysm::c,pyym::ong}},//篵 cong
{1,0,{pysm::y,pyym::an}},//篶 yan
{1,0,{pysm::p,pyym::eng}},//篷 peng
{3,552,{pysm::nop,pyym::nop}},//篸 can
{3,553,{pysm::nop,pyym::nop}},//篹 zhuan
{1,0,{pysm::p,pyym::i}},//篺 pi
{2,2271,{pysm::nop,pyym::nop}},//篻 piao
{1,0,{pysm::d,pyym::ou}},//篼 dou
{1,0,{pysm::y,pyym::u}},//篽 yu
{1,0,{pysm::m,pyym::ie}},//篾 mie
{2,2272,{pysm::nop,pyym::nop}},//篿 tuan
{2,2273,{pysm::nop,pyym::nop}},//簀 ze
{1,0,{pysm::sh,pyym::ai}},//簁 shai
{2,2274,{pysm::nop,pyym::nop}},//簂 gui
{1,0,{pysm::y,pyym::i}},//簃 yi
{1,0,{pysm::h,pyym::u}},//簄 hu
{1,0,{pysm::ch,pyym::an}},//簅 chan
{1,0,{pysm::k,pyym::ou}},//簆 kou
{3,554,{pysm::nop,pyym::nop}},//簇 cu
{1,0,{pysm::p,pyym::ing}},//簈 ping
{2,2275,{pysm::nop,pyym::nop}},//簉 zao
{1,0,{pysm::j,pyym::i}},//簊 ji
{1,0,{pysm::g,pyym::ui}},//簋 gui
{1,0,{pysm::s,pyym::u}},//簌 su
{3,555,{pysm::nop,pyym::nop}},//簍 lou
{2,2276,{pysm::nop,pyym::nop}},//簎 ce
{1,0,{pysm::l,pyym::u}},//簏 lu
{1,0,{pysm::n,pyym::ian}},//簐 nian
{1,0,{pysm::s,pyym::uo}},//簑 suo
{1,0,{pysm::c,pyym::uan}},//簒 cuan
{1,0,{pysm::d,pyym::iao}},//簓 diao
{1,0,{pysm::s,pyym::uo}},//簔 suo
{1,0,{pysm::l,pyym::e}},//簕 le
{1,0,{pysm::d,pyym::uan}},//簖 duan
{1,0,{pysm::zh,pyym::u}},//簗 zhu
{1,0,{pysm::x,pyym::iao}},//簘 xiao
{1,0,{pysm::b,pyym::o}},//簙 bo
{1,0,{pysm::m,pyym::i}},//簚 mi
{2,2277,{pysm::nop,pyym::nop}},//簛 shai
{2,2278,{pysm::nop,pyym::nop}},//簜 dang
{1,0,{pysm::l,pyym::iao}},//簝 liao
{1,0,{pysm::d,pyym::an}},//簞 dan
{1,0,{pysm::d,pyym::ian}},//簟 dian
{1,0,{pysm::f,pyym::u}},//簠 fu
{1,0,{pysm::j,pyym::ian}},//簡 jian
{1,0,{pysm::m,pyym::in}},//簢 min
{1,0,{pysm::k,pyym::ui}},//簣 kui
{1,0,{pysm::d,pyym::ai}},//簤 dai
{1,0,{pysm::j,pyym::iao}},//簥 jiao
{1,0,{pysm::d,pyym::eng}},//簦 deng
{1,0,{pysm::h,pyym::uang}},//簧 huang
{2,2279,{pysm::nop,pyym::nop}},//簨 sun
{1,0,{pysm::l,pyym::ao}},//簩 lao
{1,0,{pysm::z,pyym::an}},//簪 zan
{1,0,{pysm::x,pyym::iao}},//簫 xiao
{1,0,{pysm::l,pyym::u}},//簬 lu
{1,0,{pysm::sh,pyym::i}},//簭 shi
{1,0,{pysm::z,pyym::an}},//簮 zan
{1,0,{pysm::q,pyym::i}},//簯 qi
{1,0,{pysm::p,pyym::ai}},//簰 pai
{1,0,{pysm::q,pyym::i}},//簱 qi
{1,0,{pysm::p,pyym::ai}},//簲 pai
{1,0,{pysm::g,pyym::an}},//簳 gan
{1,0,{pysm::j,pyym::u}},//簴 ju
{1,0,{pysm::l,pyym::u}},//簵 lu
{1,0,{pysm::l,pyym::u}},//簶 lu
{1,0,{pysm::y,pyym::an}},//簷 yan
{1,0,{pysm::b,pyym::o}},//簸 bo
{1,0,{pysm::d,pyym::ang}},//簹 dang
{1,0,{pysm::s,pyym::ai}},//簺 sai
{2,2280,{pysm::nop,pyym::nop}},//簻 zhua
{1,0,{pysm::g,pyym::ou}},//簼 gou
{1,0,{pysm::q,pyym::ian}},//簽 qian
{1,0,{pysm::l,pyym::ian}},//簾 lian
{2,2281,{pysm::nop,pyym::nop}},//簿 bu
{1,0,{pysm::zh,pyym::ou}},//籀 zhou
{1,0,{pysm::l,pyym::ai}},//籁 lai
{1,0,{pysm::sh,pyym::i}},//籂 shi
{1,0,{pysm::l,pyym::an}},//籃 lan
{1,0,{pysm::k,pyym::ui}},//籄 kui
{1,0,{pysm::y,pyym::u}},//籅 yu
{1,0,{pysm::y,pyym::ue}},//籆 yue
{1,0,{pysm::h,pyym::ao}},//籇 hao
{2,2282,{pysm::nop,pyym::nop}},//籈 zhen
{1,0,{pysm::t,pyym::ai}},//籉 tai
{1,0,{pysm::t,pyym::i}},//籊 ti
{2,2283,{pysm::nop,pyym::nop}},//籋 nie
{2,2284,{pysm::nop,pyym::nop}},//籌 chou
{2,2285,{pysm::nop,pyym::nop}},//籍 ji
{1,0,{pysm::y,pyym::i}},//籎 yi
{1,0,{pysm::q,pyym::i}},//籏 qi
{1,0,{pysm::t,pyym::eng}},//籐 teng
{2,2286,{pysm::nop,pyym::nop}},//籑 zhuan
{1,0,{pysm::zh,pyym::ou}},//籒 zhou
{3,556,{pysm::nop,pyym::nop}},//籓 fan
{2,2287,{pysm::nop,pyym::nop}},//籔 sou
{1,0,{pysm::zh,pyym::ou}},//籕 zhou
{1,0,{pysm::q,pyym::ian}},//籖 qian
{1,0,{pysm::zh,pyym::uo}},//籗 zhuo
{1,0,{pysm::t,pyym::eng}},//籘 teng
{1,0,{pysm::l,pyym::u}},//籙 lu
{1,0,{pysm::l,pyym::u}},//籚 lu
{1,0,{pysm::j,pyym::ian}},//籛 jian
{1,0,{pysm::t,pyym::uo}},//籜 tuo
{1,0,{pysm::y,pyym::ing}},//籝 ying
{1,0,{pysm::y,pyym::u}},//籞 yu
{1,0,{pysm::l,pyym::ai}},//籟 lai
{1,0,{pysm::l,pyym::ong}},//籠 long
{1,0,{pysm::q,pyym::ie}},//籡 qie
{1,0,{pysm::l,pyym::ian}},//籢 lian
{1,0,{pysm::l,pyym::an}},//籣 lan
{1,0,{pysm::q,pyym::ian}},//籤 qian
{1,0,{pysm::y,pyym::ue}},//籥 yue
{1,0,{pysm::zh,pyym::ong}},//籦 zhong
{2,2288,{pysm::nop,pyym::nop}},//籧 qu
{1,0,{pysm::l,pyym::ian}},//籨 lian
{1,0,{pysm::b,pyym::ian}},//籩 bian
{1,0,{pysm::d,pyym::uan}},//籪 duan
{1,0,{pysm::z,pyym::uan}},//籫 zuan
{1,0,{pysm::l,pyym::i}},//籬 li
{1,0,{pysm::s,pyym::i}},//籭 si
{1,0,{pysm::l,pyym::uo}},//籮 luo
{1,0,{pysm::y,pyym::ing}},//籯 ying
{1,0,{pysm::y,pyym::ue}},//籰 yue
{1,0,{pysm::zh,pyym::uo}},//籱 zhuo
{1,0,{pysm::y,pyym::u}},//籲 yu
{1,0,{pysm::m,pyym::i}},//米 mi
{2,2289,{pysm::nop,pyym::nop}},//籴 di
{1,0,{pysm::f,pyym::an}},//籵 fan
{1,0,{pysm::sh,pyym::en}},//籶 shen
{1,0,{pysm::zh,pyym::e}},//籷 zhe
{1,0,{pysm::sh,pyym::en}},//籸 shen
{1,0,{pysm::n,pyym::v}},//籹 nü
{1,0,{pysm::h,pyym::e}},//籺 he
{1,0,{pysm::l,pyym::ei}},//类 lei
{1,0,{pysm::x,pyym::ian}},//籼 xian
{1,0,{pysm::z,pyym::i}},//籽 zi
{1,0,{pysm::n,pyym::i}},//籾 ni
{1,0,{pysm::c,pyym::un}},//籿 cun
{1,0,{pysm::zh,pyym::ang}},//粀 zhang
{1,0,{pysm::q,pyym::ian}},//粁 qian
{1,0,{pysm::zh,pyym::ai}},//粂 zhai
{2,2290,{pysm::nop,pyym::nop}},//粃 bi
{1,0,{pysm::b,pyym::an}},//粄 ban
{1,0,{pysm::w,pyym::u}},//粅 wu
{2,2291,{pysm::nop,pyym::nop}},//粆 sha
{2,2292,{pysm::nop,pyym::nop}},//粇 kang
{1,0,{pysm::r,pyym::ou}},//粈 rou
{1,0,{pysm::f,pyym::en}},//粉 fen
{1,0,{pysm::b,pyym::i}},//粊 bi
{1,0,{pysm::c,pyym::ui}},//粋 cui
{1,0,{pysm::y,pyym::in}},//粌 yin
{1,0,{pysm::zh,pyym::e}},//粍 zhe
{1,0,{pysm::m,pyym::i}},//粎 mi
{1,0,{pysm::t,pyym::ai}},//粏 tai
{1,0,{pysm::h,pyym::u}},//粐 hu
{1,0,{pysm::b,pyym::a}},//粑 ba
{1,0,{pysm::l,pyym::i}},//粒 li
{1,0,{pysm::g,pyym::an}},//粓 gan
{1,0,{pysm::j,pyym::u}},//粔 ju
{1,0,{pysm::p,pyym::o}},//粕 po
{1,0,{pysm::m,pyym::o}},//粖 mo
{1,0,{pysm::c,pyym::u}},//粗 cu
{2,2293,{pysm::nop,pyym::nop}},//粘 zhan
{1,0,{pysm::zh,pyym::ou}},//粙 zhou
{1,0,{pysm::ch,pyym::i}},//粚 chi
{1,0,{pysm::s,pyym::u}},//粛 su
{1,0,{pysm::t,pyym::iao}},//粜 tiao
{1,0,{pysm::l,pyym::i}},//粝 li
{1,0,{pysm::x,pyym::i}},//粞 xi
{1,0,{pysm::s,pyym::u}},//粟 su
{1,0,{pysm::h,pyym::ong}},//粠 hong
{1,0,{pysm::t,pyym::ong}},//粡 tong
{3,557,{pysm::nop,pyym::nop}},//粢 zi
{2,2294,{pysm::nop,pyym::nop}},//粣 ce
{1,0,{pysm::y,pyym::ue}},//粤 yue
{2,2295,{pysm::nop,pyym::nop}},//粥 zhou
{1,0,{pysm::l,pyym::in}},//粦 lin
{1,0,{pysm::zh,pyym::uang}},//粧 zhuang
{1,0,{pysm::b,pyym::ai}},//粨 bai
{1,0,{pysm::l,pyym::ao}},//粩 lao
{1,0,{pysm::f,pyym::en}},//粪 fen
{1,0,{pysm::nop,pyym::er}},//粫 er
{1,0,{pysm::q,pyym::u}},//粬 qu
{1,0,{pysm::h,pyym::e}},//粭 he
{1,0,{pysm::l,pyym::iang}},//粮 liang
{1,0,{pysm::x,pyym::ian}},//粯 xian
{1,0,{pysm::f,pyym::u}},//粰 fu
{1,0,{pysm::l,pyym::iang}},//粱 liang
{1,0,{pysm::c,pyym::an}},//粲 can
{1,0,{pysm::j,pyym::ing}},//粳 jing
{1,0,{pysm::l,pyym::i}},//粴 li
{1,0,{pysm::y,pyym::ue}},//粵 yue
{1,0,{pysm::l,pyym::u}},//粶 lu
{1,0,{pysm::j,pyym::u}},//粷 ju
{1,0,{pysm::q,pyym::i}},//粸 qi
{2,2296,{pysm::nop,pyym::nop}},//粹 cui
{1,0,{pysm::b,pyym::ai}},//粺 bai
{1,0,{pysm::zh,pyym::ang}},//粻 zhang
{1,0,{pysm::l,pyym::in}},//粼 lin
{1,0,{pysm::z,pyym::ong}},//粽 zong
{2,2297,{pysm::nop,pyym::nop}},//精 jing
{2,2298,{pysm::nop,pyym::nop}},//粿 guo
{1,0,{pysm::h,pyym::ua}},//糀 hua
{2,2299,{pysm::nop,pyym::nop}},//糁 san
{1,0,{pysm::s,pyym::an}},//糂 san
{1,0,{pysm::t,pyym::ang}},//糃 tang
{1,0,{pysm::b,pyym::ian}},//糄 bian
{1,0,{pysm::r,pyym::ou}},//糅 rou
{1,0,{pysm::m,pyym::ian}},//糆 mian
{1,0,{pysm::h,pyym::ou}},//糇 hou
{1,0,{pysm::x,pyym::u}},//糈 xu
{1,0,{pysm::z,pyym::ong}},//糉 zong
{1,0,{pysm::h,pyym::u}},//糊 hu
{1,0,{pysm::j,pyym::ian}},//糋 jian
{1,0,{pysm::z,pyym::an}},//糌 zan
{1,0,{pysm::c,pyym::i}},//糍 ci
{1,0,{pysm::l,pyym::i}},//糎 li
{1,0,{pysm::x,pyym::ie}},//糏 xie
{1,0,{pysm::f,pyym::u}},//糐 fu
{1,0,{pysm::n,pyym::uo}},//糑 nuo
{1,0,{pysm::b,pyym::ei}},//糒 bei
{1,0,{pysm::g,pyym::u}},//糓 gu
{1,0,{pysm::x,pyym::iu}},//糔 xiu
{1,0,{pysm::g,pyym::ao}},//糕 gao
{1,0,{pysm::t,pyym::ang}},//糖 tang
{1,0,{pysm::q,pyym::iu}},//糗 qiu
{1,0,{pysm::j,pyym::ia}},//糘 jia
{1,0,{pysm::c,pyym::ao}},//糙 cao
{1,0,{pysm::zh,pyym::uang}},//糚 zhuang
{1,0,{pysm::t,pyym::ang}},//糛 tang
{2,2300,{pysm::nop,pyym::nop}},//糜 mi
{2,2301,{pysm::nop,pyym::nop}},//糝 san
{1,0,{pysm::f,pyym::en}},//糞 fen
{1,0,{pysm::z,pyym::ao}},//糟 zao
{1,0,{pysm::k,pyym::ang}},//糠 kang
{1,0,{pysm::j,pyym::iang}},//糡 jiang
{1,0,{pysm::m,pyym::o}},//糢 mo
{1,0,{pysm::s,pyym::an}},//糣 san
{1,0,{pysm::s,pyym::an}},//糤 san
{1,0,{pysm::n,pyym::uo}},//糥 nuo
{1,0,{pysm::x,pyym::i}},//糦 xi
{1,0,{pysm::l,pyym::iang}},//糧 liang
{1,0,{pysm::j,pyym::iang}},//糨 jiang
{1,0,{pysm::k,pyym::uai}},//糩 kuai
{1,0,{pysm::b,pyym::o}},//糪 bo
{1,0,{pysm::h,pyym::uan}},//糫 huan
{1,0,{pysm::sh,pyym::u}},//糬 shu
{1,0,{pysm::z,pyym::ong}},//糭 zong
{1,0,{pysm::x,pyym::ian}},//糮 xian
{1,0,{pysm::n,pyym::uo}},//糯 nuo
{1,0,{pysm::t,pyym::uan}},//糰 tuan
{1,0,{pysm::n,pyym::ie}},//糱 nie
{1,0,{pysm::l,pyym::i}},//糲 li
{1,0,{pysm::z,pyym::uo}},//糳 zuo
{1,0,{pysm::d,pyym::i}},//糴 di
{1,0,{pysm::n,pyym::ie}},//糵 nie
{2,2302,{pysm::nop,pyym::nop}},//糶 tiao
{1,0,{pysm::l,pyym::an}},//糷 lan
{2,2303,{pysm::nop,pyym::nop}},//糸 mi
{1,0,{pysm::s,pyym::i}},//糹 si
{1,0,{pysm::j,pyym::iu}},//糺 jiu
{2,2304,{pysm::nop,pyym::nop}},//系 xi
{1,0,{pysm::g,pyym::ong}},//糼 gong
{1,0,{pysm::zh,pyym::eng}},//糽 zheng
{2,2305,{pysm::nop,pyym::nop}},//糾 jiu
{1,0,{pysm::y,pyym::ou}},//糿 you
{1,0,{pysm::j,pyym::i}},//紀 ji
{1,0,{pysm::ch,pyym::a}},//紁 cha
{1,0,{pysm::zh,pyym::ou}},//紂 zhou
{1,0,{pysm::x,pyym::un}},//紃 xun
{3,558,{pysm::nop,pyym::nop}},//約 yue
{3,559,{pysm::nop,pyym::nop}},//紅 hong
{2,2306,{pysm::nop,pyym::nop}},//紆 yu
{3,560,{pysm::nop,pyym::nop}},//紇 he
{1,0,{pysm::w,pyym::an}},//紈 wan
{1,0,{pysm::r,pyym::en}},//紉 ren
{1,0,{pysm::w,pyym::en}},//紊 wen
{1,0,{pysm::w,pyym::en}},//紋 wen
{1,0,{pysm::q,pyym::iu}},//紌 qiu
{1,0,{pysm::n,pyym::a}},//納 na
{1,0,{pysm::z,pyym::i}},//紎 zi
{1,0,{pysm::t,pyym::ou}},//紏 tou
{1,0,{pysm::n,pyym::iu}},//紐 niu
{1,0,{pysm::f,pyym::ou}},//紑 fou
{2,2307,{pysm::nop,pyym::nop}},//紒 ji
{1,0,{pysm::sh,pyym::u}},//紓 shu
{5,35,{pysm::nop,pyym::nop}},//純 chun
{3,561,{pysm::nop,pyym::nop}},//紕 pi
{1,0,{pysm::zh,pyym::en}},//紖 zhen
{2,2308,{pysm::nop,pyym::nop}},//紗 sha
{1,0,{pysm::h,pyym::ong}},//紘 hong
{1,0,{pysm::zh,pyym::i}},//紙 zhi
{1,0,{pysm::j,pyym::i}},//級 ji
{1,0,{pysm::f,pyym::en}},//紛 fen
{1,0,{pysm::y,pyym::un}},//紜 yun
{1,0,{pysm::r,pyym::en}},//紝 ren
{1,0,{pysm::d,pyym::an}},//紞 dan
{1,0,{pysm::j,pyym::in}},//紟 jin
{1,0,{pysm::s,pyym::u}},//素 su
{2,2309,{pysm::nop,pyym::nop}},//紡 fang
{1,0,{pysm::s,pyym::uo}},//索 suo
{1,0,{pysm::c,pyym::ui}},//紣 cui
{1,0,{pysm::j,pyym::iu}},//紤 jiu
{2,2310,{pysm::nop,pyym::nop}},//紥 za
{1,0,{pysm::b,pyym::a}},//紦 ba
{1,0,{pysm::j,pyym::in}},//紧 jin
{1,0,{pysm::f,pyym::u}},//紨 fu
{1,0,{pysm::zh,pyym::i}},//紩 zhi
{1,0,{pysm::q,pyym::i}},//紪 qi
{1,0,{pysm::z,pyym::i}},//紫 zi
{2,2311,{pysm::nop,pyym::nop}},//紬 chou
{1,0,{pysm::h,pyym::ong}},//紭 hong
{2,2312,{pysm::nop,pyym::nop}},//紮 za
{3,562,{pysm::nop,pyym::nop}},//累 lei
{1,0,{pysm::x,pyym::i}},//細 xi
{1,0,{pysm::f,pyym::u}},//紱 fu
{2,2313,{pysm::nop,pyym::nop}},//紲 xie
{1,0,{pysm::sh,pyym::en}},//紳 shen
{2,2314,{pysm::nop,pyym::nop}},//紴 bo
{2,2315,{pysm::nop,pyym::nop}},//紵 zhu
{1,0,{pysm::q,pyym::u}},//紶 qu
{1,0,{pysm::l,pyym::ing}},//紷 ling
{1,0,{pysm::zh,pyym::u}},//紸 zhu
{2,2316,{pysm::nop,pyym::nop}},//紹 shao
{1,0,{pysm::g,pyym::an}},//紺 gan
{1,0,{pysm::y,pyym::ang}},//紻 yang
{2,2317,{pysm::nop,pyym::nop}},//紼 fu
{1,0,{pysm::t,pyym::uo}},//紽 tuo
{3,563,{pysm::nop,pyym::nop}},//紾 zhen
{1,0,{pysm::d,pyym::ai}},//紿 dai
{1,0,{pysm::ch,pyym::u}},//絀 chu
{1,0,{pysm::sh,pyym::i}},//絁 shi
{1,0,{pysm::zh,pyym::ong}},//終 zhong
{2,2318,{pysm::nop,pyym::nop}},//絃 xian
{2,2319,{pysm::nop,pyym::nop}},//組 zu
{1,0,{pysm::j,pyym::iong}},//絅 jiong
{1,0,{pysm::b,pyym::an}},//絆 ban
{1,0,{pysm::q,pyym::u}},//絇 qu
{1,0,{pysm::m,pyym::o}},//絈 mo
{1,0,{pysm::sh,pyym::u}},//絉 shu
{1,0,{pysm::z,pyym::ui}},//絊 zui
{1,0,{pysm::k,pyym::uang}},//絋 kuang
{1,0,{pysm::j,pyym::ing}},//経 jing
{1,0,{pysm::r,pyym::en}},//絍 ren
{1,0,{pysm::h,pyym::ang}},//絎 hang
{2,2320,{pysm::nop,pyym::nop}},//絏 xie
{2,2321,{pysm::nop,pyym::nop}},//結 jie
{1,0,{pysm::zh,pyym::u}},//絑 zhu
{1,0,{pysm::ch,pyym::ou}},//絒 chou
{2,2322,{pysm::nop,pyym::nop}},//絓 gua
{2,2323,{pysm::nop,pyym::nop}},//絔 bai
{1,0,{pysm::j,pyym::ue}},//絕 jue
{1,0,{pysm::k,pyym::uang}},//絖 kuang
{1,0,{pysm::h,pyym::u}},//絗 hu
{1,0,{pysm::c,pyym::i}},//絘 ci
{2,2324,{pysm::nop,pyym::nop}},//絙 huan
{1,0,{pysm::g,pyym::eng}},//絚 geng
{1,0,{pysm::t,pyym::ao}},//絛 tao
{5,36,{pysm::nop,pyym::nop}},//絜 jie
{1,0,{pysm::k,pyym::u}},//絝 ku
{2,2325,{pysm::nop,pyym::nop}},//絞 jiao
{1,0,{pysm::q,pyym::uan}},//絟 quan
{2,2326,{pysm::nop,pyym::nop}},//絠 gai
{2,2327,{pysm::nop,pyym::nop}},//絡 luo
{2,2328,{pysm::nop,pyym::nop}},//絢 xuan
{3,564,{pysm::nop,pyym::nop}},//絣 beng
{1,0,{pysm::x,pyym::ian}},//絤 xian
{1,0,{pysm::f,pyym::u}},//絥 fu
{3,565,{pysm::nop,pyym::nop}},//給 gei
{2,2329,{pysm::nop,pyym::nop}},//絧 dong
{1,0,{pysm::r,pyym::ong}},//絨 rong
{3,566,{pysm::nop,pyym::nop}},//絩 tiao
{1,0,{pysm::y,pyym::in}},//絪 yin
{1,0,{pysm::l,pyym::ei}},//絫 lei
{1,0,{pysm::x,pyym::ie}},//絬 xie
{1,0,{pysm::j,pyym::uan}},//絭 juan
{4,111,{pysm::nop,pyym::nop}},//絮 xu
{2,2330,{pysm::nop,pyym::nop}},//絯 gai
{1,0,{pysm::d,pyym::ie}},//絰 die
{1,0,{pysm::t,pyym::ong}},//統 tong
{1,0,{pysm::s,pyym::i}},//絲 si
{1,0,{pysm::j,pyym::iang}},//絳 jiang
{1,0,{pysm::x,pyym::iang}},//絴 xiang
{1,0,{pysm::h,pyym::ui}},//絵 hui
{1,0,{pysm::j,pyym::ue}},//絶 jue
{1,0,{pysm::zh,pyym::i}},//絷 zhi
{1,0,{pysm::j,pyym::ian}},//絸 jian
{2,2331,{pysm::nop,pyym::nop}},//絹 juan
{2,2332,{pysm::nop,pyym::nop}},//絺 chi
{4,112,{pysm::nop,pyym::nop}},//絻 mian
{1,0,{pysm::zh,pyym::en}},//絼 zhen
{1,0,{pysm::l,pyym::v}},//絽 lü
{1,0,{pysm::ch,pyym::eng}},//絾 cheng
{1,0,{pysm::q,pyym::iu}},//絿 qiu
{1,0,{pysm::sh,pyym::u}},//綀 shu
{1,0,{pysm::b,pyym::ang}},//綁 bang
{1,0,{pysm::t,pyym::ong}},//綂 tong
{2,2333,{pysm::nop,pyym::nop}},//綃 xiao
{2,2334,{pysm::nop,pyym::nop}},//綄 huan
{2,2335,{pysm::nop,pyym::nop}},//綅 qin
{2,2336,{pysm::nop,pyym::nop}},//綆 geng
{1,0,{pysm::x,pyym::iu}},//綇 xiu
{1,0,{pysm::t,pyym::i}},//綈 ti
{2,2337,{pysm::nop,pyym::nop}},//綉 tou
{1,0,{pysm::x,pyym::ie}},//綊 xie
{1,0,{pysm::h,pyym::ong}},//綋 hong
{1,0,{pysm::x,pyym::i}},//綌 xi
{1,0,{pysm::f,pyym::u}},//綍 fu
{1,0,{pysm::t,pyym::ing}},//綎 ting
{4,113,{pysm::nop,pyym::nop}},//綏 sui
{1,0,{pysm::d,pyym::ui}},//綐 dui
{1,0,{pysm::k,pyym::un}},//綑 kun
{1,0,{pysm::f,pyym::u}},//綒 fu
{1,0,{pysm::j,pyym::ing}},//經 jing
{1,0,{pysm::h,pyym::u}},//綔 hu
{1,0,{pysm::zh,pyym::i}},//綕 zhi
{2,2338,{pysm::nop,pyym::nop}},//綖 yan
{1,0,{pysm::j,pyym::iong}},//綗 jiong
{1,0,{pysm::f,pyym::eng}},//綘 feng
{1,0,{pysm::j,pyym::i}},//継 ji
{1,0,{pysm::x,pyym::u}},//続 xu
{1,0,{pysm::r,pyym::en}},//綛 ren
{2,2339,{pysm::nop,pyym::nop}},//綜 zong
{3,567,{pysm::nop,pyym::nop}},//綝 chen
{1,0,{pysm::d,pyym::uo}},//綞 duo
{2,2340,{pysm::nop,pyym::nop}},//綟 li
{1,0,{pysm::l,pyym::v}},//綠 lü
{1,0,{pysm::l,pyym::iang}},//綡 liang
{3,568,{pysm::nop,pyym::nop}},//綢 chou
{1,0,{pysm::q,pyym::uan}},//綣 quan
{1,0,{pysm::sh,pyym::ao}},//綤 shao
{1,0,{pysm::q,pyym::i}},//綥 qi
{1,0,{pysm::q,pyym::i}},//綦 qi
{1,0,{pysm::zh,pyym::un}},//綧 zhun
{1,0,{pysm::q,pyym::i}},//綨 qi
{1,0,{pysm::w,pyym::an}},//綩 wan
{3,569,{pysm::nop,pyym::nop}},//綪 qian
{1,0,{pysm::x,pyym::ian}},//綫 xian
{1,0,{pysm::sh,pyym::ou}},//綬 shou
{2,2341,{pysm::nop,pyym::nop}},//維 wei
{2,2342,{pysm::nop,pyym::nop}},//綮 qi
{1,0,{pysm::t,pyym::ao}},//綯 tao
{1,0,{pysm::w,pyym::an}},//綰 wan
{1,0,{pysm::g,pyym::ang}},//綱 gang
{1,0,{pysm::w,pyym::ang}},//網 wang
{1,0,{pysm::b,pyym::eng}},//綳 beng
{2,2343,{pysm::nop,pyym::nop}},//綴 zhui
{1,0,{pysm::c,pyym::ai}},//綵 cai
{1,0,{pysm::g,pyym::uo}},//綶 guo
{2,2344,{pysm::nop,pyym::nop}},//綷 cui
{2,2345,{pysm::nop,pyym::nop}},//綸 lun
{1,0,{pysm::l,pyym::iu}},//綹 liu
{2,2346,{pysm::nop,pyym::nop}},//綺 qi
{1,0,{pysm::zh,pyym::an}},//綻 zhan
{1,0,{pysm::b,pyym::i}},//綼 bi
{2,2347,{pysm::nop,pyym::nop}},//綽 chuo
{1,0,{pysm::l,pyym::ing}},//綾 ling
{1,0,{pysm::m,pyym::ian}},//綿 mian
{1,0,{pysm::q,pyym::i}},//緀 qi
{1,0,{pysm::q,pyym::ie}},//緁 qie
{3,570,{pysm::nop,pyym::nop}},//緂 tian
{1,0,{pysm::z,pyym::ong}},//緃 zong
{2,2348,{pysm::nop,pyym::nop}},//緄 gun
{1,0,{pysm::z,pyym::ou}},//緅 zou
{1,0,{pysm::x,pyym::i}},//緆 xi
{1,0,{pysm::z,pyym::i}},//緇 zi
{1,0,{pysm::x,pyym::ing}},//緈 xing
{1,0,{pysm::l,pyym::iang}},//緉 liang
{1,0,{pysm::j,pyym::in}},//緊 jin
{1,0,{pysm::f,pyym::ei}},//緋 fei
{1,0,{pysm::r,pyym::ui}},//緌 rui
{1,0,{pysm::m,pyym::in}},//緍 min
{1,0,{pysm::y,pyym::u}},//緎 yu
{2,2349,{pysm::nop,pyym::nop}},//総 zong
{1,0,{pysm::f,pyym::an}},//緐 fan
{2,2350,{pysm::nop,pyym::nop}},//緑 lü
{1,0,{pysm::x,pyym::u}},//緒 xu
{1,0,{pysm::y,pyym::ing}},//緓 ying
{1,0,{pysm::sh,pyym::ang}},//緔 shang
{1,0,{pysm::q,pyym::i}},//緕 qi
{1,0,{pysm::x,pyym::u}},//緖 xu
{1,0,{pysm::x,pyym::iang}},//緗 xiang
{1,0,{pysm::j,pyym::ian}},//緘 jian
{1,0,{pysm::k,pyym::e}},//緙 ke
{1,0,{pysm::x,pyym::ian}},//線 xian
{1,0,{pysm::r,pyym::uan}},//緛 ruan
{1,0,{pysm::m,pyym::ian}},//緜 mian
{2,2351,{pysm::nop,pyym::nop}},//緝 ji
{1,0,{pysm::d,pyym::uan}},//緞 duan
{2,2352,{pysm::nop,pyym::nop}},//緟 chong
{1,0,{pysm::d,pyym::i}},//締 di
{3,571,{pysm::nop,pyym::nop}},//緡 min
{2,2353,{pysm::nop,pyym::nop}},//緢 miao
{1,0,{pysm::y,pyym::uan}},//緣 yuan
{2,2354,{pysm::nop,pyym::nop}},//緤 xie
{1,0,{pysm::b,pyym::ao}},//緥 bao
{1,0,{pysm::s,pyym::i}},//緦 si
{1,0,{pysm::q,pyym::iu}},//緧 qiu
{1,0,{pysm::b,pyym::ian}},//編 bian
{1,0,{pysm::h,pyym::uan}},//緩 huan
{1,0,{pysm::g,pyym::eng}},//緪 geng
{1,0,{pysm::c,pyym::ong}},//緫 cong
{1,0,{pysm::m,pyym::ian}},//緬 mian
{1,0,{pysm::w,pyym::ei}},//緭 wei
{1,0,{pysm::f,pyym::u}},//緮 fu
{1,0,{pysm::w,pyym::ei}},//緯 wei
{3,572,{pysm::nop,pyym::nop}},//緰 tou
{1,0,{pysm::g,pyym::ou}},//緱 gou
{1,0,{pysm::m,pyym::iao}},//緲 miao
{1,0,{pysm::x,pyym::ie}},//緳 xie
{1,0,{pysm::l,pyym::ian}},//練 lian
{1,0,{pysm::z,pyym::ong}},//緵 zong
{2,2355,{pysm::nop,pyym::nop}},//緶 bian
{2,2356,{pysm::nop,pyym::nop}},//緷 yun
{1,0,{pysm::y,pyym::in}},//緸 yin
{1,0,{pysm::t,pyym::i}},//緹 ti
{1,0,{pysm::g,pyym::ua}},//緺 gua
{1,0,{pysm::zh,pyym::i}},//緻 zhi
{2,2357,{pysm::nop,pyym::nop}},//緼 yun
{1,0,{pysm::ch,pyym::eng}},//緽 cheng
{1,0,{pysm::ch,pyym::an}},//緾 chan
{1,0,{pysm::d,pyym::ai}},//緿 dai
{1,0,{pysm::x,pyym::ia}},//縀 xia
{1,0,{pysm::y,pyym::uan}},//縁 yuan
{1,0,{pysm::z,pyym::ong}},//縂 zong
{1,0,{pysm::x,pyym::u}},//縃 xu
{1,0,{pysm::sh,pyym::eng}},//縄 sheng
{1,0,{pysm::w,pyym::ei}},//縅 wei
{1,0,{pysm::g,pyym::eng}},//縆 geng
{1,0,{pysm::x,pyym::uan}},//縇 xuan
{1,0,{pysm::y,pyym::ing}},//縈 ying
{1,0,{pysm::j,pyym::in}},//縉 jin
{1,0,{pysm::y,pyym::i}},//縊 yi
{1,0,{pysm::zh,pyym::ui}},//縋 zhui
{1,0,{pysm::n,pyym::i}},//縌 ni
{1,0,{pysm::b,pyym::ang}},//縍 bang
{2,2358,{pysm::nop,pyym::nop}},//縎 gu
{1,0,{pysm::p,pyym::an}},//縏 pan
{3,573,{pysm::nop,pyym::nop}},//縐 zhou
{1,0,{pysm::j,pyym::ian}},//縑 jian
{3,574,{pysm::nop,pyym::nop}},//縒 ci
{1,0,{pysm::q,pyym::uan}},//縓 quan
{1,0,{pysm::sh,pyym::uang}},//縔 shuang
{1,0,{pysm::y,pyym::un}},//縕 yun
{1,0,{pysm::x,pyym::ia}},//縖 xia
{3,575,{pysm::nop,pyym::nop}},//縗 cui
{1,0,{pysm::x,pyym::i}},//縘 xi
{1,0,{pysm::r,pyym::ong}},//縙 rong
{1,0,{pysm::t,pyym::ao}},//縚 tao
{1,0,{pysm::f,pyym::u}},//縛 fu
{1,0,{pysm::y,pyym::un}},//縜 yun
{2,2359,{pysm::nop,pyym::nop}},//縝 chen
{1,0,{pysm::g,pyym::ao}},//縞 gao
{2,2360,{pysm::nop,pyym::nop}},//縟 ru
{1,0,{pysm::h,pyym::u}},//縠 hu
{2,2361,{pysm::nop,pyym::nop}},//縡 zai
{1,0,{pysm::t,pyym::eng}},//縢 teng
{2,2362,{pysm::nop,pyym::nop}},//縣 xian
{1,0,{pysm::s,pyym::u}},//縤 su
{1,0,{pysm::zh,pyym::en}},//縥 zhen
{1,0,{pysm::z,pyym::ong}},//縦 zong
{1,0,{pysm::t,pyym::ao}},//縧 tao
{1,0,{pysm::h,pyym::uang}},//縨 huang
{1,0,{pysm::c,pyym::ai}},//縩 cai
{1,0,{pysm::b,pyym::i}},//縪 bi
{1,0,{pysm::f,pyym::eng}},//縫 feng
{1,0,{pysm::c,pyym::u}},//縬 cu
{1,0,{pysm::l,pyym::i}},//縭 li
{2,2363,{pysm::nop,pyym::nop}},//縮 suo
{2,2364,{pysm::nop,pyym::nop}},//縯 yan
{1,0,{pysm::x,pyym::i}},//縰 xi
{2,2365,{pysm::nop,pyym::nop}},//縱 zong
{1,0,{pysm::l,pyym::ei}},//縲 lei
{2,2366,{pysm::nop,pyym::nop}},//縳 juan
{1,0,{pysm::q,pyym::ian}},//縴 qian
{1,0,{pysm::m,pyym::an}},//縵 man
{1,0,{pysm::zh,pyym::i}},//縶 zhi
{1,0,{pysm::l,pyym::v}},//縷 lü
{2,2367,{pysm::nop,pyym::nop}},//縸 mu
{1,0,{pysm::p,pyym::iao}},//縹 piao
{1,0,{pysm::l,pyym::ian}},//縺 lian
{1,0,{pysm::m,pyym::i}},//縻 mi
{1,0,{pysm::x,pyym::uan}},//縼 xuan
{2,2368,{pysm::nop,pyym::nop}},//總 zong
{1,0,{pysm::j,pyym::i}},//績 ji
{5,37,{pysm::nop,pyym::nop}},//縿 shan
{2,2369,{pysm::nop,pyym::nop}},//繀 sui
{3,576,{pysm::nop,pyym::nop}},//繁 fan
{1,0,{pysm::l,pyym::v}},//繂 lü
{1,0,{pysm::b,pyym::eng}},//繃 beng
{1,0,{pysm::y,pyym::i}},//繄 yi
{2,2370,{pysm::nop,pyym::nop}},//繅 sao
{7,2,{pysm::nop,pyym::nop}},//繆 mou
{3,577,{pysm::nop,pyym::nop}},//繇 yao
{1,0,{pysm::q,pyym::iang}},//繈 qiang
{1,0,{pysm::h,pyym::un}},//繉 hun
{1,0,{pysm::x,pyym::ian}},//繊 xian
{1,0,{pysm::j,pyym::i}},//繋 ji
{1,0,{pysm::sh,pyym::a}},//繌 sha
{1,0,{pysm::x,pyym::iu}},//繍 xiu
{1,0,{pysm::r,pyym::an}},//繎 ran
{1,0,{pysm::x,pyym::uan}},//繏 xuan
{1,0,{pysm::s,pyym::ui}},//繐 sui
{2,2371,{pysm::nop,pyym::nop}},//繑 qiao
{2,2372,{pysm::nop,pyym::nop}},//繒 zeng
{1,0,{pysm::z,pyym::uo}},//繓 zuo
{1,0,{pysm::zh,pyym::i}},//織 zhi
{1,0,{pysm::sh,pyym::an}},//繕 shan
{1,0,{pysm::s,pyym::an}},//繖 san
{1,0,{pysm::l,pyym::in}},//繗 lin
{2,2373,{pysm::nop,pyym::nop}},//繘 yu
{1,0,{pysm::f,pyym::an}},//繙 fan
{2,2374,{pysm::nop,pyym::nop}},//繚 liao
{1,0,{pysm::ch,pyym::uo}},//繛 chuo
{1,0,{pysm::z,pyym::un}},//繜 zun
{1,0,{pysm::j,pyym::ian}},//繝 jian
{1,0,{pysm::r,pyym::ao}},//繞 rao
{1,0,{pysm::ch,pyym::an}},//繟 chan
{1,0,{pysm::r,pyym::ui}},//繠 rui
{1,0,{pysm::x,pyym::iu}},//繡 xiu
{1,0,{pysm::h,pyym::ui}},//繢 hui
{1,0,{pysm::h,pyym::ua}},//繣 hua
{1,0,{pysm::z,pyym::uan}},//繤 zuan
{1,0,{pysm::x,pyym::i}},//繥 xi
{1,0,{pysm::q,pyym::iang}},//繦 qiang
{1,0,{pysm::y,pyym::un}},//繧 yun
{1,0,{pysm::d,pyym::a}},//繨 da
{3,578,{pysm::nop,pyym::nop}},//繩 sheng
{2,2375,{pysm::nop,pyym::nop}},//繪 hui
{2,2376,{pysm::nop,pyym::nop}},//繫 xi
{1,0,{pysm::s,pyym::e}},//繬 se
{1,0,{pysm::j,pyym::ian}},//繭 jian
{1,0,{pysm::j,pyym::iang}},//繮 jiang
{1,0,{pysm::h,pyym::uan}},//繯 huan
{3,579,{pysm::nop,pyym::nop}},//繰 zao
{1,0,{pysm::c,pyym::ong}},//繱 cong
{1,0,{pysm::x,pyym::ie}},//繲 xie
{3,580,{pysm::nop,pyym::nop}},//繳 jiao
{1,0,{pysm::b,pyym::i}},//繴 bi
{3,581,{pysm::nop,pyym::nop}},//繵 dan
{1,0,{pysm::y,pyym::i}},//繶 yi
{1,0,{pysm::n,pyym::ong}},//繷 nong
{1,0,{pysm::s,pyym::ui}},//繸 sui
{2,2377,{pysm::nop,pyym::nop}},//繹 yi
{1,0,{pysm::sh,pyym::ai}},//繺 shai
{2,2378,{pysm::nop,pyym::nop}},//繻 xu
{1,0,{pysm::j,pyym::i}},//繼 ji
{1,0,{pysm::b,pyym::in}},//繽 bin
{1,0,{pysm::q,pyym::ian}},//繾 qian
{1,0,{pysm::l,pyym::an}},//繿 lan
{2,2379,{pysm::nop,pyym::nop}},//纀 pu
{1,0,{pysm::x,pyym::un}},//纁 xun
{1,0,{pysm::z,pyym::uan}},//纂 zuan
{1,0,{pysm::q,pyym::i}},//纃 qi
{1,0,{pysm::p,pyym::eng}},//纄 peng
{2,2380,{pysm::nop,pyym::nop}},//纅 yao
{1,0,{pysm::m,pyym::o}},//纆 mo
{1,0,{pysm::l,pyym::ei}},//纇 lei
{1,0,{pysm::x,pyym::ie}},//纈 xie
{1,0,{pysm::z,pyym::uan}},//纉 zuan
{1,0,{pysm::k,pyym::uang}},//纊 kuang
{1,0,{pysm::y,pyym::ou}},//纋 you
{1,0,{pysm::x,pyym::u}},//續 xu
{1,0,{pysm::l,pyym::ei}},//纍 lei
{1,0,{pysm::x,pyym::ian}},//纎 xian
{1,0,{pysm::ch,pyym::an}},//纏 chan
{1,0,{pysm::j,pyym::iao}},//纐 jiao
{1,0,{pysm::l,pyym::u}},//纑 lu
{1,0,{pysm::ch,pyym::an}},//纒 chan
{1,0,{pysm::y,pyym::ing}},//纓 ying
{2,2381,{pysm::nop,pyym::nop}},//纔 cai
{3,582,{pysm::nop,pyym::nop}},//纕 rang
{2,2382,{pysm::nop,pyym::nop}},//纖 xian
{1,0,{pysm::z,pyym::ui}},//纗 zui
{1,0,{pysm::z,pyym::uan}},//纘 zuan
{1,0,{pysm::l,pyym::uo}},//纙 luo
{3,583,{pysm::nop,pyym::nop}},//纚 li
{2,2383,{pysm::nop,pyym::nop}},//纛 dao
{1,0,{pysm::l,pyym::an}},//纜 lan
{1,0,{pysm::l,pyym::ei}},//纝 lei
{1,0,{pysm::l,pyym::ian}},//纞 lian
{1,0,{pysm::s,pyym::i}},//纟 si
{1,0,{pysm::j,pyym::iu}},//纠 jiu
{1,0,{pysm::y,pyym::u}},//纡 yu
{2,2384,{pysm::nop,pyym::nop}},//红 hong
{1,0,{pysm::zh,pyym::ou}},//纣 zhou
{2,2385,{pysm::nop,pyym::nop}},//纤 xian
{2,2386,{pysm::nop,pyym::nop}},//纥 ge
{2,2387,{pysm::nop,pyym::nop}},//约 yue
{1,0,{pysm::j,pyym::i}},//级 ji
{1,0,{pysm::w,pyym::an}},//纨 wan
{1,0,{pysm::k,pyym::uang}},//纩 kuang
{1,0,{pysm::j,pyym::i}},//纪 ji
{1,0,{pysm::r,pyym::en}},//纫 ren
{1,0,{pysm::w,pyym::ei}},//纬 wei
{1,0,{pysm::y,pyym::un}},//纭 yun
{1,0,{pysm::h,pyym::ong}},//纮 hong
{1,0,{pysm::ch,pyym::un}},//纯 chun
{1,0,{pysm::p,pyym::i}},//纰 pi
{1,0,{pysm::sh,pyym::a}},//纱 sha
{1,0,{pysm::g,pyym::ang}},//纲 gang
{1,0,{pysm::n,pyym::a}},//纳 na
{1,0,{pysm::r,pyym::en}},//纴 ren
{1,0,{pysm::z,pyym::ong}},//纵 zong
{2,2388,{pysm::nop,pyym::nop}},//纶 lun
{1,0,{pysm::f,pyym::en}},//纷 fen
{1,0,{pysm::zh,pyym::i}},//纸 zhi
{1,0,{pysm::w,pyym::en}},//纹 wen
{1,0,{pysm::f,pyym::ang}},//纺 fang
{1,0,{pysm::zh,pyym::u}},//纻 zhu
{1,0,{pysm::zh,pyym::en}},//纼 zhen
{1,0,{pysm::n,pyym::iu}},//纽 niu
{1,0,{pysm::sh,pyym::u}},//纾 shu
{1,0,{pysm::x,pyym::ian}},//线 xian
{1,0,{pysm::g,pyym::an}},//绀 gan
{1,0,{pysm::x,pyym::ie}},//绁 xie
{1,0,{pysm::f,pyym::u}},//绂 fu
{1,0,{pysm::l,pyym::ian}},//练 lian
{1,0,{pysm::z,pyym::u}},//组 zu
{1,0,{pysm::sh,pyym::en}},//绅 shen
{1,0,{pysm::x,pyym::i}},//细 xi
{1,0,{pysm::zh,pyym::i}},//织 zhi
{1,0,{pysm::zh,pyym::ong}},//终 zhong
{1,0,{pysm::zh,pyym::ou}},//绉 zhou
{1,0,{pysm::b,pyym::an}},//绊 ban
{1,0,{pysm::f,pyym::u}},//绋 fu
{1,0,{pysm::ch,pyym::u}},//绌 chu
{1,0,{pysm::sh,pyym::ao}},//绍 shao
{1,0,{pysm::y,pyym::i}},//绎 yi
{1,0,{pysm::j,pyym::ing}},//经 jing
{1,0,{pysm::d,pyym::ai}},//绐 dai
{1,0,{pysm::b,pyym::ang}},//绑 bang
{1,0,{pysm::r,pyym::ong}},//绒 rong
{1,0,{pysm::j,pyym::ie}},//结 jie
{1,0,{pysm::k,pyym::u}},//绔 ku
{1,0,{pysm::r,pyym::ao}},//绕 rao
{1,0,{pysm::d,pyym::ie}},//绖 die
{1,0,{pysm::h,pyym::ang}},//绗 hang
{1,0,{pysm::h,pyym::ui}},//绘 hui
{2,2389,{pysm::nop,pyym::nop}},//给 gei
{1,0,{pysm::x,pyym::uan}},//绚 xuan
{1,0,{pysm::j,pyym::iang}},//绛 jiang
{2,2390,{pysm::nop,pyym::nop}},//络 luo
{1,0,{pysm::j,pyym::ue}},//绝 jue
{1,0,{pysm::j,pyym::iao}},//绞 jiao
{1,0,{pysm::t,pyym::ong}},//统 tong
{1,0,{pysm::g,pyym::eng}},//绠 geng
{1,0,{pysm::x,pyym::iao}},//绡 xiao
{1,0,{pysm::j,pyym::uan}},//绢 juan
{1,0,{pysm::x,pyym::iu}},//绣 xiu
{1,0,{pysm::x,pyym::i}},//绤 xi
{1,0,{pysm::s,pyym::ui}},//绥 sui
{1,0,{pysm::t,pyym::ao}},//绦 tao
{1,0,{pysm::j,pyym::i}},//继 ji
{1,0,{pysm::t,pyym::i}},//绨 ti
{1,0,{pysm::j,pyym::i}},//绩 ji
{1,0,{pysm::x,pyym::u}},//绪 xu
{1,0,{pysm::l,pyym::ing}},//绫 ling
{1,0,{pysm::y,pyym::ing}},//绬 ying
{1,0,{pysm::x,pyym::u}},//续 xu
{1,0,{pysm::q,pyym::i}},//绮 qi
{1,0,{pysm::f,pyym::ei}},//绯 fei
{2,2391,{pysm::nop,pyym::nop}},//绰 chuo
{1,0,{pysm::sh,pyym::ang}},//绱 shang
{1,0,{pysm::g,pyym::un}},//绲 gun
{1,0,{pysm::sh,pyym::eng}},//绳 sheng
{1,0,{pysm::w,pyym::ei}},//维 wei
{1,0,{pysm::m,pyym::ian}},//绵 mian
{1,0,{pysm::sh,pyym::ou}},//绶 shou
{1,0,{pysm::b,pyym::eng}},//绷 beng
{1,0,{pysm::ch,pyym::ou}},//绸 chou
{1,0,{pysm::t,pyym::ao}},//绹 tao
{1,0,{pysm::l,pyym::iu}},//绺 liu
{1,0,{pysm::q,pyym::uan}},//绻 quan
{2,2392,{pysm::nop,pyym::nop}},//综 zong
{1,0,{pysm::zh,pyym::an}},//绽 zhan
{1,0,{pysm::w,pyym::an}},//绾 wan
{2,2393,{pysm::nop,pyym::nop}},//绿 lü
{1,0,{pysm::zh,pyym::ui}},//缀 zhui
{1,0,{pysm::z,pyym::i}},//缁 zi
{1,0,{pysm::k,pyym::e}},//缂 ke
{1,0,{pysm::x,pyym::iang}},//缃 xiang
{1,0,{pysm::j,pyym::ian}},//缄 jian
{1,0,{pysm::m,pyym::ian}},//缅 mian
{1,0,{pysm::l,pyym::an}},//缆 lan
{1,0,{pysm::t,pyym::i}},//缇 ti
{1,0,{pysm::m,pyym::iao}},//缈 miao
{2,2394,{pysm::nop,pyym::nop}},//缉 ji
{1,0,{pysm::y,pyym::un}},//缊 yun
{1,0,{pysm::h,pyym::ui}},//缋 hui
{1,0,{pysm::s,pyym::i}},//缌 si
{1,0,{pysm::d,pyym::uo}},//缍 duo
{1,0,{pysm::d,pyym::uan}},//缎 duan
{2,2395,{pysm::nop,pyym::nop}},//缏 bian
{1,0,{pysm::x,pyym::ian}},//缐 xian
{1,0,{pysm::g,pyym::ou}},//缑 gou
{1,0,{pysm::zh,pyym::ui}},//缒 zhui
{1,0,{pysm::h,pyym::uan}},//缓 huan
{1,0,{pysm::d,pyym::i}},//缔 di
{1,0,{pysm::l,pyym::v}},//缕 lü
{1,0,{pysm::b,pyym::ian}},//编 bian
{1,0,{pysm::m,pyym::in}},//缗 min
{1,0,{pysm::y,pyym::uan}},//缘 yuan
{1,0,{pysm::j,pyym::in}},//缙 jin
{1,0,{pysm::f,pyym::u}},//缚 fu
{1,0,{pysm::r,pyym::u}},//缛 ru
{1,0,{pysm::zh,pyym::en}},//缜 zhen
{1,0,{pysm::f,pyym::eng}},//缝 feng
{1,0,{pysm::c,pyym::ui}},//缞 cui
{1,0,{pysm::g,pyym::ao}},//缟 gao
{1,0,{pysm::ch,pyym::an}},//缠 chan
{1,0,{pysm::l,pyym::i}},//缡 li
{1,0,{pysm::y,pyym::i}},//缢 yi
{1,0,{pysm::j,pyym::ian}},//缣 jian
{1,0,{pysm::b,pyym::in}},//缤 bin
{1,0,{pysm::p,pyym::iao}},//缥 piao
{1,0,{pysm::m,pyym::an}},//缦 man
{1,0,{pysm::l,pyym::ei}},//缧 lei
{1,0,{pysm::y,pyym::ing}},//缨 ying
{2,2396,{pysm::nop,pyym::nop}},//缩 suo
{3,584,{pysm::nop,pyym::nop}},//缪 mou
{1,0,{pysm::s,pyym::ao}},//缫 sao
{1,0,{pysm::x,pyym::ie}},//缬 xie
{1,0,{pysm::l,pyym::iao}},//缭 liao
{1,0,{pysm::sh,pyym::an}},//缮 shan
{1,0,{pysm::z,pyym::eng}},//缯 zeng
{1,0,{pysm::j,pyym::iang}},//缰 jiang
{1,0,{pysm::q,pyym::ian}},//缱 qian
{2,2397,{pysm::nop,pyym::nop}},//缲 qiao
{1,0,{pysm::h,pyym::uan}},//缳 huan
{2,2398,{pysm::nop,pyym::nop}},//缴 jiao
{1,0,{pysm::z,pyym::uan}},//缵 zuan
{1,0,{pysm::f,pyym::ou}},//缶 fou
{1,0,{pysm::x,pyym::ie}},//缷 xie
{1,0,{pysm::g,pyym::ang}},//缸 gang
{1,0,{pysm::f,pyym::ou}},//缹 fou
{2,2399,{pysm::nop,pyym::nop}},//缺 que
{1,0,{pysm::f,pyym::ou}},//缻 fou
{1,0,{pysm::q,pyym::i}},//缼 qi
{1,0,{pysm::b,pyym::o}},//缽 bo
{1,0,{pysm::p,pyym::ing}},//缾 ping
{1,0,{pysm::x,pyym::iang}},//缿 xiang
{1,0,{pysm::zh,pyym::ao}},//罀 zhao
{1,0,{pysm::g,pyym::ang}},//罁 gang
{1,0,{pysm::y,pyym::ing}},//罂 ying
{1,0,{pysm::y,pyym::ing}},//罃 ying
{1,0,{pysm::q,pyym::ing}},//罄 qing
{1,0,{pysm::x,pyym::ia}},//罅 xia
{1,0,{pysm::g,pyym::uan}},//罆 guan
{1,0,{pysm::z,pyym::un}},//罇 zun
{1,0,{pysm::t,pyym::an}},//罈 tan
{1,0,{pysm::ch,pyym::eng}},//罉 cheng
{1,0,{pysm::q,pyym::i}},//罊 qi
{1,0,{pysm::w,pyym::eng}},//罋 weng
{1,0,{pysm::y,pyym::ing}},//罌 ying
{1,0,{pysm::l,pyym::ei}},//罍 lei
{1,0,{pysm::t,pyym::an}},//罎 tan
{1,0,{pysm::l,pyym::u}},//罏 lu
{1,0,{pysm::g,pyym::uan}},//罐 guan
{1,0,{pysm::w,pyym::ang}},//网 wang
{1,0,{pysm::w,pyym::ang}},//罒 wang
{1,0,{pysm::g,pyym::ang}},//罓 gang
{1,0,{pysm::w,pyym::ang}},//罔 wang
{1,0,{pysm::h,pyym::an}},//罕 han
{1,0,{pysm::l,pyym::uo}},//罖 luo
{1,0,{pysm::l,pyym::uo}},//罗 luo
{1,0,{pysm::f,pyym::u}},//罘 fu
{1,0,{pysm::sh,pyym::en}},//罙 shen
{1,0,{pysm::f,pyym::a}},//罚 fa
{1,0,{pysm::g,pyym::u}},//罛 gu
{2,2400,{pysm::nop,pyym::nop}},//罜 zhu
{2,2401,{pysm::nop,pyym::nop}},//罝 ju
{1,0,{pysm::m,pyym::ao}},//罞 mao
{1,0,{pysm::g,pyym::u}},//罟 gu
{1,0,{pysm::m,pyym::in}},//罠 min
{1,0,{pysm::g,pyym::ang}},//罡 gang
{1,0,{pysm::b,pyym::a}},//罢 ba
{1,0,{pysm::g,pyym::ua}},//罣 gua
{2,2402,{pysm::nop,pyym::nop}},//罤 ti
{1,0,{pysm::j,pyym::uan}},//罥 juan
{1,0,{pysm::f,pyym::u}},//罦 fu
{1,0,{pysm::sh,pyym::en}},//罧 shen
{1,0,{pysm::y,pyym::an}},//罨 yan
{1,0,{pysm::zh,pyym::ao}},//罩 zhao
{1,0,{pysm::z,pyym::ui}},//罪 zui
{3,585,{pysm::nop,pyym::nop}},//罫 gua
{1,0,{pysm::zh,pyym::uo}},//罬 zhuo
{1,0,{pysm::y,pyym::u}},//罭 yu
{1,0,{pysm::zh,pyym::i}},//置 zhi
{1,0,{pysm::nop,pyym::an}},//罯 an
{1,0,{pysm::f,pyym::a}},//罰 fa
{2,2403,{pysm::nop,pyym::nop}},//罱 lan
{1,0,{pysm::sh,pyym::u}},//署 shu
{1,0,{pysm::s,pyym::i}},//罳 si
{1,0,{pysm::p,pyym::i}},//罴 pi
{1,0,{pysm::m,pyym::a}},//罵 ma
{1,0,{pysm::l,pyym::iu}},//罶 liu
{4,114,{pysm::nop,pyym::nop}},//罷 ba
{1,0,{pysm::f,pyym::a}},//罸 fa
{1,0,{pysm::l,pyym::i}},//罹 li
{1,0,{pysm::ch,pyym::ao}},//罺 chao
{1,0,{pysm::w,pyym::ei}},//罻 wei
{1,0,{pysm::b,pyym::i}},//罼 bi
{1,0,{pysm::j,pyym::i}},//罽 ji
{1,0,{pysm::z,pyym::eng}},//罾 zeng
{1,0,{pysm::ch,pyym::ong}},//罿 chong
{1,0,{pysm::l,pyym::iu}},//羀 liu
{1,0,{pysm::j,pyym::i}},//羁 ji
{1,0,{pysm::j,pyym::uan}},//羂 juan
{1,0,{pysm::m,pyym::i}},//羃 mi
{1,0,{pysm::zh,pyym::ao}},//羄 zhao
{1,0,{pysm::l,pyym::uo}},//羅 luo
{1,0,{pysm::p,pyym::i}},//羆 pi
{1,0,{pysm::j,pyym::i}},//羇 ji
{1,0,{pysm::j,pyym::i}},//羈 ji
{1,0,{pysm::l,pyym::uan}},//羉 luan
{1,0,{pysm::y,pyym::ang}},//羊 yang
{2,2404,{pysm::nop,pyym::nop}},//羋 mi
{1,0,{pysm::q,pyym::iang}},//羌 qiang
{1,0,{pysm::d,pyym::a}},//羍 da
{1,0,{pysm::m,pyym::ei}},//美 mei
{2,2405,{pysm::nop,pyym::nop}},//羏 yang
{1,0,{pysm::y,pyym::ou}},//羐 you
{1,0,{pysm::y,pyym::ou}},//羑 you
{1,0,{pysm::f,pyym::en}},//羒 fen
{1,0,{pysm::b,pyym::a}},//羓 ba
{1,0,{pysm::g,pyym::ao}},//羔 gao
{1,0,{pysm::y,pyym::ang}},//羕 yang
{1,0,{pysm::g,pyym::u}},//羖 gu
{2,2406,{pysm::nop,pyym::nop}},//羗 qiang
{1,0,{pysm::z,pyym::ang}},//羘 zang
{2,2407,{pysm::nop,pyym::nop}},//羙 gao
{1,0,{pysm::l,pyym::ing}},//羚 ling
{2,2408,{pysm::nop,pyym::nop}},//羛 yi
{1,0,{pysm::zh,pyym::u}},//羜 zhu
{1,0,{pysm::d,pyym::i}},//羝 di
{1,0,{pysm::x,pyym::iu}},//羞 xiu
{1,0,{pysm::q,pyym::iang}},//羟 qiang
{1,0,{pysm::y,pyym::i}},//羠 yi
{3,586,{pysm::nop,pyym::nop}},//羡 xian
{1,0,{pysm::r,pyym::ong}},//羢 rong
{1,0,{pysm::q,pyym::un}},//羣 qun
{1,0,{pysm::q,pyym::un}},//群 qun
{2,2409,{pysm::nop,pyym::nop}},//羥 qiang
{1,0,{pysm::h,pyym::uan}},//羦 huan
{2,2410,{pysm::nop,pyym::nop}},//羧 suo
{1,0,{pysm::x,pyym::ian}},//羨 xian
{2,2411,{pysm::nop,pyym::nop}},//義 yi
{1,0,{pysm::y,pyym::ang}},//羪 yang
{2,2412,{pysm::nop,pyym::nop}},//羫 qiang
{3,587,{pysm::nop,pyym::nop}},//羬 qian
{1,0,{pysm::y,pyym::u}},//羭 yu
{1,0,{pysm::g,pyym::eng}},//羮 geng
{1,0,{pysm::j,pyym::ie}},//羯 jie
{1,0,{pysm::t,pyym::ang}},//羰 tang
{1,0,{pysm::y,pyym::uan}},//羱 yuan
{1,0,{pysm::x,pyym::i}},//羲 xi
{1,0,{pysm::f,pyym::an}},//羳 fan
{1,0,{pysm::sh,pyym::an}},//羴 shan
{1,0,{pysm::f,pyym::en}},//羵 fen
{1,0,{pysm::sh,pyym::an}},//羶 shan
{1,0,{pysm::l,pyym::ian}},//羷 lian
{2,2413,{pysm::nop,pyym::nop}},//羸 lei
{2,2414,{pysm::nop,pyym::nop}},//羹 geng
{1,0,{pysm::n,pyym::ou}},//羺 nou
{1,0,{pysm::q,pyym::iang}},//羻 qiang
{1,0,{pysm::ch,pyym::an}},//羼 chan
{2,2415,{pysm::nop,pyym::nop}},//羽 yu
{1,0,{pysm::g,pyym::ong}},//羾 gong
{1,0,{pysm::y,pyym::i}},//羿 yi
{1,0,{pysm::ch,pyym::ong}},//翀 chong
{1,0,{pysm::w,pyym::eng}},//翁 weng
{1,0,{pysm::f,pyym::en}},//翂 fen
{1,0,{pysm::h,pyym::ong}},//翃 hong
{1,0,{pysm::ch,pyym::i}},//翄 chi
{1,0,{pysm::ch,pyym::i}},//翅 chi
{1,0,{pysm::c,pyym::ui}},//翆 cui
{1,0,{pysm::f,pyym::u}},//翇 fu
{1,0,{pysm::x,pyym::ia}},//翈 xia
{1,0,{pysm::b,pyym::en}},//翉 ben
{1,0,{pysm::y,pyym::i}},//翊 yi
{1,0,{pysm::l,pyym::a}},//翋 la
{1,0,{pysm::y,pyym::i}},//翌 yi
{3,588,{pysm::nop,pyym::nop}},//翍 pi
{1,0,{pysm::l,pyym::ing}},//翎 ling
{2,2416,{pysm::nop,pyym::nop}},//翏 liu
{1,0,{pysm::zh,pyym::i}},//翐 zhi
{1,0,{pysm::q,pyym::u}},//翑 qu
{1,0,{pysm::x,pyym::i}},//習 xi
{1,0,{pysm::x,pyym::ie}},//翓 xie
{1,0,{pysm::x,pyym::iang}},//翔 xiang
{1,0,{pysm::x,pyym::i}},//翕 xi
{1,0,{pysm::x,pyym::i}},//翖 xi
{1,0,{pysm::k,pyym::e}},//翗 ke
{1,0,{pysm::q,pyym::iao}},//翘 qiao
{1,0,{pysm::h,pyym::ui}},//翙 hui
{1,0,{pysm::h,pyym::ui}},//翚 hui
{2,2417,{pysm::nop,pyym::nop}},//翛 xiao
{1,0,{pysm::sh,pyym::a}},//翜 sha
{1,0,{pysm::h,pyym::ong}},//翝 hong
{1,0,{pysm::j,pyym::iang}},//翞 jiang
{2,2418,{pysm::nop,pyym::nop}},//翟 di
{1,0,{pysm::c,pyym::ui}},//翠 cui
{1,0,{pysm::f,pyym::ei}},//翡 fei
{2,2419,{pysm::nop,pyym::nop}},//翢 dao
{1,0,{pysm::sh,pyym::a}},//翣 sha
{1,0,{pysm::ch,pyym::i}},//翤 chi
{1,0,{pysm::zh,pyym::u}},//翥 zhu
{1,0,{pysm::j,pyym::ian}},//翦 jian
{1,0,{pysm::x,pyym::uan}},//翧 xuan
{1,0,{pysm::ch,pyym::i}},//翨 chi
{1,0,{pysm::p,pyym::ian}},//翩 pian
{1,0,{pysm::z,pyym::ong}},//翪 zong
{1,0,{pysm::w,pyym::an}},//翫 wan
{1,0,{pysm::h,pyym::ui}},//翬 hui
{1,0,{pysm::h,pyym::ou}},//翭 hou
{2,2420,{pysm::nop,pyym::nop}},//翮 he
{2,2421,{pysm::nop,pyym::nop}},//翯 he
{1,0,{pysm::h,pyym::an}},//翰 han
{1,0,{pysm::nop,pyym::ao}},//翱 ao
{1,0,{pysm::p,pyym::iao}},//翲 piao
{1,0,{pysm::y,pyym::i}},//翳 yi
{1,0,{pysm::l,pyym::ian}},//翴 lian
{2,2422,{pysm::nop,pyym::nop}},//翵 hou
{1,0,{pysm::nop,pyym::ao}},//翶 ao
{1,0,{pysm::l,pyym::in}},//翷 lin
{1,0,{pysm::p,pyym::en}},//翸 pen
{1,0,{pysm::q,pyym::iao}},//翹 qiao
{1,0,{pysm::nop,pyym::ao}},//翺 ao
{1,0,{pysm::f,pyym::an}},//翻 fan
{1,0,{pysm::y,pyym::i}},//翼 yi
{1,0,{pysm::h,pyym::ui}},//翽 hui
{1,0,{pysm::x,pyym::uan}},//翾 xuan
{1,0,{pysm::d,pyym::ao}},//翿 dao
{1,0,{pysm::y,pyym::ao}},//耀 yao
{1,0,{pysm::l,pyym::ao}},//老 lao
{1,0,{pysm::l,pyym::ao}},//耂 lao
{1,0,{pysm::k,pyym::ao}},//考 kao
{1,0,{pysm::m,pyym::ao}},//耄 mao
{1,0,{pysm::zh,pyym::e}},//者 zhe
{3,589,{pysm::nop,pyym::nop}},//耆 qi
{1,0,{pysm::g,pyym::ou}},//耇 gou
{1,0,{pysm::g,pyym::ou}},//耈 gou
{1,0,{pysm::g,pyym::ou}},//耉 gou
{1,0,{pysm::d,pyym::ie}},//耊 die
{1,0,{pysm::d,pyym::ie}},//耋 die
{2,2423,{pysm::nop,pyym::nop}},//而 er
{1,0,{pysm::sh,pyym::ua}},//耍 shua
{2,2424,{pysm::nop,pyym::nop}},//耎 ruan
{2,2425,{pysm::nop,pyym::nop}},//耏 nai
{2,2426,{pysm::nop,pyym::nop}},//耐 nai
{2,2427,{pysm::nop,pyym::nop}},//耑 duan
{1,0,{pysm::l,pyym::ei}},//耒 lei
{1,0,{pysm::t,pyym::ing}},//耓 ting
{1,0,{pysm::z,pyym::i}},//耔 zi
{1,0,{pysm::g,pyym::eng}},//耕 geng
{1,0,{pysm::ch,pyym::ao}},//耖 chao
{2,2428,{pysm::nop,pyym::nop}},//耗 hao
{1,0,{pysm::y,pyym::un}},//耘 yun
{2,2429,{pysm::nop,pyym::nop}},//耙 ba
{1,0,{pysm::p,pyym::i}},//耚 pi
{2,2430,{pysm::nop,pyym::nop}},//耛 yi
{1,0,{pysm::s,pyym::i}},//耜 si
{2,2431,{pysm::nop,pyym::nop}},//耝 qu
{1,0,{pysm::j,pyym::ia}},//耞 jia
{1,0,{pysm::j,pyym::u}},//耟 ju
{1,0,{pysm::h,pyym::uo}},//耠 huo
{1,0,{pysm::ch,pyym::u}},//耡 chu
{1,0,{pysm::l,pyym::ao}},//耢 lao
{1,0,{pysm::l,pyym::un}},//耣 lun
{2,2432,{pysm::nop,pyym::nop}},//耤 ji
{1,0,{pysm::t,pyym::ang}},//耥 tang
{1,0,{pysm::nop,pyym::ou}},//耦 ou
{1,0,{pysm::l,pyym::ou}},//耧 lou
{1,0,{pysm::n,pyym::ou}},//耨 nou
{1,0,{pysm::j,pyym::iang}},//耩 jiang
{1,0,{pysm::p,pyym::ang}},//耪 pang
{2,2433,{pysm::nop,pyym::nop}},//耫 zha
{1,0,{pysm::l,pyym::ou}},//耬 lou
{1,0,{pysm::j,pyym::i}},//耭 ji
{1,0,{pysm::l,pyym::ao}},//耮 lao
{1,0,{pysm::h,pyym::uo}},//耯 huo
{1,0,{pysm::y,pyym::ou}},//耰 you
{1,0,{pysm::m,pyym::o}},//耱 mo
{1,0,{pysm::h,pyym::uai}},//耲 huai
{2,2434,{pysm::nop,pyym::nop}},//耳 er
{1,0,{pysm::y,pyym::i}},//耴 yi
{1,0,{pysm::d,pyym::ing}},//耵 ding
{2,2435,{pysm::nop,pyym::nop}},//耶 ye
{2,2436,{pysm::nop,pyym::nop}},//耷 da
{1,0,{pysm::s,pyym::ong}},//耸 song
{1,0,{pysm::q,pyym::in}},//耹 qin
{2,2437,{pysm::nop,pyym::nop}},//耺 yun
{1,0,{pysm::ch,pyym::i}},//耻 chi
{1,0,{pysm::d,pyym::an}},//耼 dan
{1,0,{pysm::d,pyym::an}},//耽 dan
{1,0,{pysm::h,pyym::ong}},//耾 hong
{1,0,{pysm::g,pyym::eng}},//耿 geng
{1,0,{pysm::zh,pyym::i}},//聀 zhi
{1,0,{pysm::p,pyym::an}},//聁 pan
{1,0,{pysm::n,pyym::ie}},//聂 nie
{1,0,{pysm::d,pyym::an}},//聃 dan
{1,0,{pysm::zh,pyym::en}},//聄 zhen
{1,0,{pysm::ch,pyym::e}},//聅 che
{1,0,{pysm::l,pyym::ing}},//聆 ling
{1,0,{pysm::zh,pyym::eng}},//聇 zheng
{1,0,{pysm::y,pyym::ou}},//聈 you
{3,590,{pysm::nop,pyym::nop}},//聉 wa
{2,2438,{pysm::nop,pyym::nop}},//聊 liao
{1,0,{pysm::l,pyym::ong}},//聋 long
{1,0,{pysm::zh,pyym::i}},//职 zhi
{1,0,{pysm::n,pyym::ing}},//聍 ning
{1,0,{pysm::t,pyym::iao}},//聎 tiao
{2,2439,{pysm::nop,pyym::nop}},//聏 er
{1,0,{pysm::y,pyym::a}},//聐 ya
{2,2440,{pysm::nop,pyym::nop}},//聑 tie
{2,2441,{pysm::nop,pyym::nop}},//聒 gua
{1,0,{pysm::x,pyym::u}},//聓 xu
{1,0,{pysm::l,pyym::ian}},//联 lian
{1,0,{pysm::h,pyym::ao}},//聕 hao
{1,0,{pysm::sh,pyym::eng}},//聖 sheng
{1,0,{pysm::l,pyym::ie}},//聗 lie
{2,2442,{pysm::nop,pyym::nop}},//聘 pin
{1,0,{pysm::j,pyym::ing}},//聙 jing
{1,0,{pysm::j,pyym::u}},//聚 ju
{1,0,{pysm::b,pyym::i}},//聛 bi
{1,0,{pysm::d,pyym::i}},//聜 di
{1,0,{pysm::g,pyym::uo}},//聝 guo
{1,0,{pysm::w,pyym::en}},//聞 wen
{1,0,{pysm::x,pyym::u}},//聟 xu
{1,0,{pysm::p,pyym::ing}},//聠 ping
{1,0,{pysm::c,pyym::ong}},//聡 cong
{1,0,{pysm::d,pyym::ing}},//聢 ding
{1,0,{pysm::n,pyym::i}},//聣 ni
{1,0,{pysm::t,pyym::ing}},//聤 ting
{1,0,{pysm::j,pyym::u}},//聥 ju
{1,0,{pysm::c,pyym::ong}},//聦 cong
{1,0,{pysm::k,pyym::ui}},//聧 kui
{1,0,{pysm::l,pyym::ian}},//聨 lian
{1,0,{pysm::k,pyym::ui}},//聩 kui
{1,0,{pysm::c,pyym::ong}},//聪 cong
{1,0,{pysm::l,pyym::ian}},//聫 lian
{1,0,{pysm::w,pyym::eng}},//聬 weng
{1,0,{pysm::k,pyym::ui}},//聭 kui
{1,0,{pysm::l,pyym::ian}},//聮 lian
{1,0,{pysm::l,pyym::ian}},//聯 lian
{1,0,{pysm::c,pyym::ong}},//聰 cong
{2,2443,{pysm::nop,pyym::nop}},//聱 ao
{1,0,{pysm::sh,pyym::eng}},//聲 sheng
{1,0,{pysm::s,pyym::ong}},//聳 song
{1,0,{pysm::t,pyym::ing}},//聴 ting
{1,0,{pysm::k,pyym::ui}},//聵 kui
{4,115,{pysm::nop,pyym::nop}},//聶 nie
{2,2444,{pysm::nop,pyym::nop}},//職 zhi
{1,0,{pysm::d,pyym::an}},//聸 dan
{1,0,{pysm::n,pyym::ing}},//聹 ning
{1,0,{pysm::q,pyym::ie}},//聺 qie
{2,2445,{pysm::nop,pyym::nop}},//聻 ni
{1,0,{pysm::t,pyym::ing}},//聼 ting
{1,0,{pysm::t,pyym::ing}},//聽 ting
{1,0,{pysm::l,pyym::ong}},//聾 long
{1,0,{pysm::y,pyym::u}},//聿 yu
{1,0,{pysm::y,pyym::u}},//肀 yu
{1,0,{pysm::zh,pyym::ao}},//肁 zhao
{1,0,{pysm::s,pyym::i}},//肂 si
{1,0,{pysm::s,pyym::u}},//肃 su
{2,2446,{pysm::nop,pyym::nop}},//肄 yi
{1,0,{pysm::s,pyym::u}},//肅 su
{2,2447,{pysm::nop,pyym::nop}},//肆 si
{1,0,{pysm::zh,pyym::ao}},//肇 zhao
{1,0,{pysm::zh,pyym::ao}},//肈 zhao
{2,2448,{pysm::nop,pyym::nop}},//肉 rou
{1,0,{pysm::y,pyym::i}},//肊 yi
{3,591,{pysm::nop,pyym::nop}},//肋 le
{1,0,{pysm::j,pyym::i}},//肌 ji
{1,0,{pysm::q,pyym::iu}},//肍 qiu
{1,0,{pysm::k,pyym::en}},//肎 ken
{1,0,{pysm::c,pyym::ao}},//肏 cao
{2,2449,{pysm::nop,pyym::nop}},//肐 ge
{2,2450,{pysm::nop,pyym::nop}},//肑 bo
{1,0,{pysm::h,pyym::uan}},//肒 huan
{1,0,{pysm::h,pyym::uang}},//肓 huang
{1,0,{pysm::ch,pyym::i}},//肔 chi
{1,0,{pysm::r,pyym::en}},//肕 ren
{1,0,{pysm::x,pyym::iao}},//肖 xiao
{1,0,{pysm::r,pyym::u}},//肗 ru
{1,0,{pysm::zh,pyym::ou}},//肘 zhou
{1,0,{pysm::y,pyym::uan}},//肙 yuan
{1,0,{pysm::d,pyym::u}},//肚 du
{1,0,{pysm::g,pyym::ang}},//肛 gang
{2,2451,{pysm::nop,pyym::nop}},//肜 rong
{1,0,{pysm::g,pyym::an}},//肝 gan
{1,0,{pysm::ch,pyym::a}},//肞 cha
{1,0,{pysm::w,pyym::o}},//肟 wo
{1,0,{pysm::ch,pyym::ang}},//肠 chang
{1,0,{pysm::g,pyym::u}},//股 gu
{2,2452,{pysm::nop,pyym::nop}},//肢 zhi
{2,2453,{pysm::nop,pyym::nop}},//肣 han
{1,0,{pysm::f,pyym::u}},//肤 fu
{2,2454,{pysm::nop,pyym::nop}},//肥 fei
{1,0,{pysm::f,pyym::en}},//肦 fen
{1,0,{pysm::p,pyym::ei}},//肧 pei
{2,2455,{pysm::nop,pyym::nop}},//肨 pang
{2,2456,{pysm::nop,pyym::nop}},//肩 jian
{1,0,{pysm::f,pyym::ang}},//肪 fang
{4,116,{pysm::nop,pyym::nop}},//肫 zhun
{1,0,{pysm::y,pyym::ou}},//肬 you
{2,2457,{pysm::nop,pyym::nop}},//肭 na
{3,592,{pysm::nop,pyym::nop}},//肮 ang
{1,0,{pysm::k,pyym::en}},//肯 ken
{1,0,{pysm::r,pyym::an}},//肰 ran
{1,0,{pysm::g,pyym::ong}},//肱 gong
{3,593,{pysm::nop,pyym::nop}},//育 yu
{1,0,{pysm::w,pyym::en}},//肳 wen
{1,0,{pysm::y,pyym::ao}},//肴 yao
{1,0,{pysm::q,pyym::i}},//肵 qi
{2,2458,{pysm::nop,pyym::nop}},//肶 pi
{2,2459,{pysm::nop,pyym::nop}},//肷 qian
{2,2460,{pysm::nop,pyym::nop}},//肸 xi
{1,0,{pysm::x,pyym::i}},//肹 xi
{2,2461,{pysm::nop,pyym::nop}},//肺 fei
{1,0,{pysm::k,pyym::en}},//肻 ken
{1,0,{pysm::j,pyym::ing}},//肼 jing
{1,0,{pysm::t,pyym::ai}},//肽 tai
{1,0,{pysm::sh,pyym::en}},//肾 shen
{1,0,{pysm::zh,pyym::ong}},//肿 zhong
{1,0,{pysm::zh,pyym::ang}},//胀 zhang
{1,0,{pysm::x,pyym::ie}},//胁 xie
{2,2462,{pysm::nop,pyym::nop}},//胂 shen
{1,0,{pysm::w,pyym::ei}},//胃 wei
{1,0,{pysm::zh,pyym::ou}},//胄 zhou
{1,0,{pysm::d,pyym::ie}},//胅 die
{3,594,{pysm::nop,pyym::nop}},//胆 dan
{2,2463,{pysm::nop,pyym::nop}},//胇 fei
{1,0,{pysm::b,pyym::a}},//胈 ba
{1,0,{pysm::b,pyym::o}},//胉 bo
{1,0,{pysm::q,pyym::u}},//胊 qu
{1,0,{pysm::t,pyym::ian}},//胋 tian
{1,0,{pysm::b,pyym::ei}},//背 bei
{3,595,{pysm::nop,pyym::nop}},//胍 gua
{1,0,{pysm::t,pyym::ai}},//胎 tai
{2,2464,{pysm::nop,pyym::nop}},//胏 zi
{1,0,{pysm::f,pyym::ei}},//胐 fei
{1,0,{pysm::zh,pyym::i}},//胑 zhi
{1,0,{pysm::n,pyym::i}},//胒 ni
{2,2465,{pysm::nop,pyym::nop}},//胓 ping
{3,596,{pysm::nop,pyym::nop}},//胔 zi
{2,2466,{pysm::nop,pyym::nop}},//胕 fu
{2,2467,{pysm::nop,pyym::nop}},//胖 pang
{2,2468,{pysm::nop,pyym::nop}},//胗 zhen
{1,0,{pysm::x,pyym::ian}},//胘 xian
{1,0,{pysm::z,pyym::uo}},//胙 zuo
{1,0,{pysm::p,pyym::ei}},//胚 pei
{1,0,{pysm::j,pyym::ia}},//胛 jia
{3,597,{pysm::nop,pyym::nop}},//胜 sheng
{3,598,{pysm::nop,pyym::nop}},//胝 zhi
{2,2469,{pysm::nop,pyym::nop}},//胞 bao
{1,0,{pysm::m,pyym::u}},//胟 mu
{1,0,{pysm::q,pyym::u}},//胠 qu
{1,0,{pysm::h,pyym::u}},//胡 hu
{1,0,{pysm::k,pyym::e}},//胢 ke
{1,0,{pysm::ch,pyym::i}},//胣 chi
{1,0,{pysm::y,pyym::in}},//胤 yin
{1,0,{pysm::x,pyym::u}},//胥 xu
{1,0,{pysm::y,pyym::ang}},//胦 yang
{1,0,{pysm::l,pyym::ong}},//胧 long
{1,0,{pysm::d,pyym::ong}},//胨 dong
{1,0,{pysm::k,pyym::a}},//胩 ka
{1,0,{pysm::l,pyym::u}},//胪 lu
{1,0,{pysm::j,pyym::ing}},//胫 jing
{2,2470,{pysm::nop,pyym::nop}},//胬 nu
{1,0,{pysm::y,pyym::an}},//胭 yan
{1,0,{pysm::p,pyym::ang}},//胮 pang
{1,0,{pysm::k,pyym::ua}},//胯 kua
{1,0,{pysm::y,pyym::i}},//胰 yi
{1,0,{pysm::g,pyym::uang}},//胱 guang
{2,2471,{pysm::nop,pyym::nop}},//胲 hai
{2,2472,{pysm::nop,pyym::nop}},//胳 ge
{1,0,{pysm::d,pyym::ong}},//胴 dong
{2,2473,{pysm::nop,pyym::nop}},//胵 chi
{2,2474,{pysm::nop,pyym::nop}},//胶 jiao
{1,0,{pysm::x,pyym::iong}},//胷 xiong
{1,0,{pysm::x,pyym::iong}},//胸 xiong
{1,0,{pysm::nop,pyym::er}},//胹 er
{2,2475,{pysm::nop,pyym::nop}},//胺 an
{1,0,{pysm::h,pyym::eng}},//胻 heng
{1,0,{pysm::p,pyym::ian}},//胼 pian
{4,117,{pysm::nop,pyym::nop}},//能 neng
{1,0,{pysm::z,pyym::i}},//胾 zi
{2,2476,{pysm::nop,pyym::nop}},//胿 gui
{2,2477,{pysm::nop,pyym::nop}},//脀 cheng
{1,0,{pysm::t,pyym::iao}},//脁 tiao
{1,0,{pysm::zh,pyym::i}},//脂 zhi
{1,0,{pysm::c,pyym::ui}},//脃 cui
{1,0,{pysm::m,pyym::ei}},//脄 mei
{3,599,{pysm::nop,pyym::nop}},//脅 xie
{1,0,{pysm::c,pyym::ui}},//脆 cui
{1,0,{pysm::x,pyym::ie}},//脇 xie
{2,2478,{pysm::nop,pyym::nop}},//脈 mai
{2,2479,{pysm::nop,pyym::nop}},//脉 mai
{1,0,{pysm::j,pyym::i}},//脊 ji
{1,0,{pysm::x,pyym::ie}},//脋 xie
{1,0,{pysm::n,pyym::in}},//脌 nin
{1,0,{pysm::k,pyym::uai}},//脍 kuai
{1,0,{pysm::s,pyym::a}},//脎 sa
{1,0,{pysm::z,pyym::ang}},//脏 zang
{1,0,{pysm::q,pyym::i}},//脐 qi
{1,0,{pysm::n,pyym::ao}},//脑 nao
{1,0,{pysm::m,pyym::i}},//脒 mi
{1,0,{pysm::n,pyym::ong}},//脓 nong
{2,2480,{pysm::nop,pyym::nop}},//脔 luan
{2,2481,{pysm::nop,pyym::nop}},//脕 wan
{1,0,{pysm::b,pyym::o}},//脖 bo
{1,0,{pysm::w,pyym::en}},//脗 wen
{2,2482,{pysm::nop,pyym::nop}},//脘 wan
{1,0,{pysm::x,pyym::iu}},//脙 xiu
{2,2483,{pysm::nop,pyym::nop}},//脚 jiao
{2,2484,{pysm::nop,pyym::nop}},//脛 jing
{1,0,{pysm::y,pyym::ou}},//脜 you
{1,0,{pysm::h,pyym::eng}},//脝 heng
{2,2485,{pysm::nop,pyym::nop}},//脞 cuo
{3,600,{pysm::nop,pyym::nop}},//脟 lie
{2,2486,{pysm::nop,pyym::nop}},//脠 shan
{1,0,{pysm::t,pyym::ing}},//脡 ting
{1,0,{pysm::m,pyym::ei}},//脢 mei
{1,0,{pysm::ch,pyym::un}},//脣 chun
{1,0,{pysm::sh,pyym::en}},//脤 shen
{3,601,{pysm::nop,pyym::nop}},//脥 qian
{2,2487,{pysm::nop,pyym::nop}},//脦 de
{2,2488,{pysm::nop,pyym::nop}},//脧 juan
{2,2489,{pysm::nop,pyym::nop}},//脨 cu
{4,118,{pysm::nop,pyym::nop}},//脩 xiu
{2,2490,{pysm::nop,pyym::nop}},//脪 xin
{1,0,{pysm::t,pyym::uo}},//脫 tuo
{1,0,{pysm::p,pyym::ao}},//脬 pao
{1,0,{pysm::ch,pyym::eng}},//脭 cheng
{2,2491,{pysm::nop,pyym::nop}},//脮 nei
{2,2492,{pysm::nop,pyym::nop}},//脯 pu
{1,0,{pysm::d,pyym::ou}},//脰 dou
{2,2493,{pysm::nop,pyym::nop}},//脱 tuo
{1,0,{pysm::n,pyym::iao}},//脲 niao
{1,0,{pysm::n,pyym::ao}},//脳 nao
{1,0,{pysm::p,pyym::i}},//脴 pi
{1,0,{pysm::g,pyym::u}},//脵 gu
{1,0,{pysm::l,pyym::uo}},//脶 luo
{1,0,{pysm::l,pyym::i}},//脷 li
{1,0,{pysm::l,pyym::ian}},//脸 lian
{2,2494,{pysm::nop,pyym::nop}},//脹 zhang
{2,2495,{pysm::nop,pyym::nop}},//脺 cui
{1,0,{pysm::j,pyym::ie}},//脻 jie
{2,2496,{pysm::nop,pyym::nop}},//脼 liang
{1,0,{pysm::sh,pyym::ui}},//脽 shui
{3,602,{pysm::nop,pyym::nop}},//脾 pi
{1,0,{pysm::b,pyym::iao}},//脿 biao
{1,0,{pysm::l,pyym::un}},//腀 lun
{1,0,{pysm::p,pyym::ian}},//腁 pian
{3,603,{pysm::nop,pyym::nop}},//腂 lei
{3,604,{pysm::nop,pyym::nop}},//腃 kui
{3,605,{pysm::nop,pyym::nop}},//腄 chui
{1,0,{pysm::d,pyym::an}},//腅 dan
{1,0,{pysm::t,pyym::ian}},//腆 tian
{1,0,{pysm::n,pyym::ei}},//腇 nei
{1,0,{pysm::j,pyym::ing}},//腈 jing
{1,0,{pysm::n,pyym::ai}},//腉 nai
{2,2497,{pysm::nop,pyym::nop}},//腊 la
{1,0,{pysm::y,pyym::e}},//腋 ye
{3,606,{pysm::nop,pyym::nop}},//腌 yan
{2,2498,{pysm::nop,pyym::nop}},//腍 ren
{1,0,{pysm::sh,pyym::en}},//腎 shen
{2,2499,{pysm::nop,pyym::nop}},//腏 chuo
{1,0,{pysm::f,pyym::u}},//腐 fu
{1,0,{pysm::f,pyym::u}},//腑 fu
{1,0,{pysm::j,pyym::u}},//腒 ju
{1,0,{pysm::f,pyym::ei}},//腓 fei
{2,2500,{pysm::nop,pyym::nop}},//腔 qiang
{1,0,{pysm::w,pyym::an}},//腕 wan
{1,0,{pysm::d,pyym::ong}},//腖 dong
{1,0,{pysm::p,pyym::i}},//腗 pi
{1,0,{pysm::g,pyym::uo}},//腘 guo
{1,0,{pysm::z,pyym::ong}},//腙 zong
{1,0,{pysm::d,pyym::ing}},//腚 ding
{1,0,{pysm::w,pyym::o}},//腛 wo
{1,0,{pysm::m,pyym::ei}},//腜 mei
{5,38,{pysm::nop,pyym::nop}},//腝 ni
{3,607,{pysm::nop,pyym::nop}},//腞 zhuan
{1,0,{pysm::ch,pyym::i}},//腟 chi
{1,0,{pysm::c,pyym::ou}},//腠 cou
{1,0,{pysm::l,pyym::uo}},//腡 luo
{1,0,{pysm::nop,pyym::ou}},//腢 ou
{1,0,{pysm::d,pyym::i}},//腣 di
{1,0,{pysm::nop,pyym::an}},//腤 an
{1,0,{pysm::x,pyym::ing}},//腥 xing
{1,0,{pysm::n,pyym::ao}},//腦 nao
{2,2501,{pysm::nop,pyym::nop}},//腧 shu
{1,0,{pysm::sh,pyym::uan}},//腨 shuan
{1,0,{pysm::n,pyym::an}},//腩 nan
{1,0,{pysm::y,pyym::un}},//腪 yun
{1,0,{pysm::zh,pyym::ong}},//腫 zhong
{1,0,{pysm::r,pyym::ou}},//腬 rou
{1,0,{pysm::nop,pyym::e}},//腭 e
{1,0,{pysm::s,pyym::ai}},//腮 sai
{2,2502,{pysm::nop,pyym::nop}},//腯 tu
{1,0,{pysm::y,pyym::ao}},//腰 yao
{2,2503,{pysm::nop,pyym::nop}},//腱 jian
{1,0,{pysm::w,pyym::ei}},//腲 wei
{2,2504,{pysm::nop,pyym::nop}},//腳 jiao
{1,0,{pysm::y,pyym::u}},//腴 yu
{1,0,{pysm::j,pyym::ia}},//腵 jia
{1,0,{pysm::d,pyym::uan}},//腶 duan
{1,0,{pysm::b,pyym::i}},//腷 bi
{1,0,{pysm::ch,pyym::ang}},//腸 chang
{1,0,{pysm::f,pyym::u}},//腹 fu
{1,0,{pysm::x,pyym::ian}},//腺 xian
{1,0,{pysm::n,pyym::i}},//腻 ni
{1,0,{pysm::m,pyym::ian}},//腼 mian
{1,0,{pysm::w,pyym::a}},//腽 wa
{1,0,{pysm::t,pyym::eng}},//腾 teng
{1,0,{pysm::t,pyym::ui}},//腿 tui
{2,2505,{pysm::nop,pyym::nop}},//膀 bang
{3,608,{pysm::nop,pyym::nop}},//膁 qian
{1,0,{pysm::l,pyym::v}},//膂 lü
{1,0,{pysm::w,pyym::a}},//膃 wa
{1,0,{pysm::sh,pyym::ou}},//膄 shou
{1,0,{pysm::t,pyym::ang}},//膅 tang
{1,0,{pysm::s,pyym::u}},//膆 su
{1,0,{pysm::zh,pyym::ui}},//膇 zhui
{1,0,{pysm::g,pyym::e}},//膈 ge
{1,0,{pysm::y,pyym::i}},//膉 yi
{3,609,{pysm::nop,pyym::nop}},//膊 bo
{1,0,{pysm::l,pyym::iao}},//膋 liao
{1,0,{pysm::j,pyym::i}},//膌 ji
{1,0,{pysm::p,pyym::i}},//膍 pi
{1,0,{pysm::x,pyym::ie}},//膎 xie
{1,0,{pysm::g,pyym::ao}},//膏 gao
{1,0,{pysm::l,pyym::v}},//膐 lü
{1,0,{pysm::b,pyym::in}},//膑 bin
{1,0,{pysm::nop,pyym::ou}},//膒 ou
{1,0,{pysm::ch,pyym::ang}},//膓 chang
{2,2506,{pysm::nop,pyym::nop}},//膔 lu
{2,2507,{pysm::nop,pyym::nop}},//膕 guo
{1,0,{pysm::p,pyym::ang}},//膖 pang
{1,0,{pysm::ch,pyym::uai}},//膗 chuai
{2,2508,{pysm::nop,pyym::nop}},//膘 biao
{1,0,{pysm::j,pyym::iang}},//膙 jiang
{2,2509,{pysm::nop,pyym::nop}},//膚 fu
{1,0,{pysm::t,pyym::ang}},//膛 tang
{1,0,{pysm::m,pyym::o}},//膜 mo
{1,0,{pysm::x,pyym::i}},//膝 xi
{3,610,{pysm::nop,pyym::nop}},//膞 zhuan
{1,0,{pysm::l,pyym::v}},//膟 lü
{3,611,{pysm::nop,pyym::nop}},//膠 jiao
{1,0,{pysm::y,pyym::ing}},//膡 ying
{1,0,{pysm::l,pyym::v}},//膢 lü
{1,0,{pysm::zh,pyym::i}},//膣 zhi
{1,0,{pysm::x,pyym::ue}},//膤 xue
{1,0,{pysm::c,pyym::un}},//膥 cun
{2,2510,{pysm::nop,pyym::nop}},//膦 lin
{1,0,{pysm::t,pyym::ong}},//膧 tong
{1,0,{pysm::p,pyym::eng}},//膨 peng
{1,0,{pysm::n,pyym::i}},//膩 ni
{3,612,{pysm::nop,pyym::nop}},//膪 chuai
{1,0,{pysm::l,pyym::iao}},//膫 liao
{1,0,{pysm::c,pyym::ui}},//膬 cui
{3,613,{pysm::nop,pyym::nop}},//膭 gui
{1,0,{pysm::x,pyym::iao}},//膮 xiao
{2,2511,{pysm::nop,pyym::nop}},//膯 teng
{2,2512,{pysm::nop,pyym::nop}},//膰 fan
{1,0,{pysm::zh,pyym::i}},//膱 zhi
{1,0,{pysm::j,pyym::iao}},//膲 jiao
{1,0,{pysm::sh,pyym::an}},//膳 shan
{3,614,{pysm::nop,pyym::nop}},//膴 hu
{1,0,{pysm::c,pyym::ui}},//膵 cui
{1,0,{pysm::r,pyym::un}},//膶 run
{1,0,{pysm::x,pyym::iang}},//膷 xiang
{2,2513,{pysm::nop,pyym::nop}},//膸 sui
{1,0,{pysm::f,pyym::en}},//膹 fen
{1,0,{pysm::y,pyym::ing}},//膺 ying
{2,2514,{pysm::nop,pyym::nop}},//膻 shan
{1,0,{pysm::zh,pyym::ua}},//膼 zhua
{1,0,{pysm::d,pyym::an}},//膽 dan
{1,0,{pysm::k,pyym::uai}},//膾 kuai
{1,0,{pysm::n,pyym::ong}},//膿 nong
{1,0,{pysm::t,pyym::un}},//臀 tun
{1,0,{pysm::l,pyym::ian}},//臁 lian
{2,2515,{pysm::nop,pyym::nop}},//臂 bi
{1,0,{pysm::y,pyym::ong}},//臃 yong
{2,2516,{pysm::nop,pyym::nop}},//臄 jue
{1,0,{pysm::ch,pyym::u}},//臅 chu
{1,0,{pysm::y,pyym::i}},//臆 yi
{1,0,{pysm::j,pyym::uan}},//臇 juan
{2,2517,{pysm::nop,pyym::nop}},//臈 la
{1,0,{pysm::l,pyym::ian}},//臉 lian
{1,0,{pysm::s,pyym::ao}},//臊 sao
{1,0,{pysm::t,pyym::un}},//臋 tun
{1,0,{pysm::g,pyym::u}},//臌 gu
{1,0,{pysm::q,pyym::i}},//臍 qi
{1,0,{pysm::c,pyym::ui}},//臎 cui
{1,0,{pysm::b,pyym::in}},//臏 bin
{1,0,{pysm::x,pyym::un}},//臐 xun
{5,39,{pysm::nop,pyym::nop}},//臑 nao
{2,2518,{pysm::nop,pyym::nop}},//臒 wo
{1,0,{pysm::z,pyym::ang}},//臓 zang
{1,0,{pysm::x,pyym::ian}},//臔 xian
{1,0,{pysm::b,pyym::iao}},//臕 biao
{1,0,{pysm::x,pyym::ing}},//臖 xing
{1,0,{pysm::k,pyym::uan}},//臗 kuan
{2,2519,{pysm::nop,pyym::nop}},//臘 la
{1,0,{pysm::y,pyym::an}},//臙 yan
{2,2520,{pysm::nop,pyym::nop}},//臚 lu
{1,0,{pysm::h,pyym::uo}},//臛 huo
{1,0,{pysm::z,pyym::a}},//臜 za
{1,0,{pysm::l,pyym::uo}},//臝 luo
{1,0,{pysm::q,pyym::u}},//臞 qu
{1,0,{pysm::z,pyym::ang}},//臟 zang
{1,0,{pysm::l,pyym::uan}},//臠 luan
{2,2521,{pysm::nop,pyym::nop}},//臡 ni
{2,2522,{pysm::nop,pyym::nop}},//臢 za
{1,0,{pysm::ch,pyym::en}},//臣 chen
{3,615,{pysm::nop,pyym::nop}},//臤 qian
{1,0,{pysm::w,pyym::o}},//臥 wo
{2,2523,{pysm::nop,pyym::nop}},//臦 guang
{2,2524,{pysm::nop,pyym::nop}},//臧 zang
{1,0,{pysm::l,pyym::in}},//臨 lin
{2,2525,{pysm::nop,pyym::nop}},//臩 guang
{1,0,{pysm::z,pyym::i}},//自 zi
{1,0,{pysm::j,pyym::iao}},//臫 jiao
{1,0,{pysm::n,pyym::ie}},//臬 nie
{2,2526,{pysm::nop,pyym::nop}},//臭 chou
{1,0,{pysm::j,pyym::i}},//臮 ji
{1,0,{pysm::g,pyym::ao}},//臯 gao
{1,0,{pysm::ch,pyym::ou}},//臰 chou
{2,2527,{pysm::nop,pyym::nop}},//臱 mian
{1,0,{pysm::n,pyym::ie}},//臲 nie
{2,2528,{pysm::nop,pyym::nop}},//至 zhi
{2,2529,{pysm::nop,pyym::nop}},//致 zhi
{1,0,{pysm::g,pyym::e}},//臵 ge
{1,0,{pysm::j,pyym::ian}},//臶 jian
{2,2530,{pysm::nop,pyym::nop}},//臷 die
{2,2531,{pysm::nop,pyym::nop}},//臸 zhi
{1,0,{pysm::x,pyym::iu}},//臹 xiu
{1,0,{pysm::t,pyym::ai}},//臺 tai
{1,0,{pysm::zh,pyym::en}},//臻 zhen
{1,0,{pysm::j,pyym::iu}},//臼 jiu
{1,0,{pysm::x,pyym::ian}},//臽 xian
{3,616,{pysm::nop,pyym::nop}},//臾 yu
{1,0,{pysm::ch,pyym::a}},//臿 cha
{1,0,{pysm::y,pyym::ao}},//舀 yao
{1,0,{pysm::y,pyym::u}},//舁 yu
{3,617,{pysm::nop,pyym::nop}},//舂 chong
{1,0,{pysm::x,pyym::i}},//舃 xi
{3,618,{pysm::nop,pyym::nop}},//舄 xi
{1,0,{pysm::j,pyym::iu}},//舅 jiu
{1,0,{pysm::y,pyym::u}},//舆 yu
{1,0,{pysm::y,pyym::u}},//與 yu
{2,2532,{pysm::nop,pyym::nop}},//興 xing
{1,0,{pysm::j,pyym::u}},//舉 ju
{1,0,{pysm::j,pyym::iu}},//舊 jiu
{1,0,{pysm::x,pyym::in}},//舋 xin
{2,2533,{pysm::nop,pyym::nop}},//舌 she
{2,2534,{pysm::nop,pyym::nop}},//舍 she
{1,0,{pysm::sh,pyym::e}},//舎 she
{1,0,{pysm::j,pyym::iu}},//舏 jiu
{1,0,{pysm::sh,pyym::i}},//舐 shi
{1,0,{pysm::t,pyym::an}},//舑 tan
{2,2535,{pysm::nop,pyym::nop}},//舒 shu
{1,0,{pysm::sh,pyym::i}},//舓 shi
{2,2536,{pysm::nop,pyym::nop}},//舔 tian
{1,0,{pysm::t,pyym::an}},//舕 tan
{1,0,{pysm::p,pyym::u}},//舖 pu
{1,0,{pysm::p,pyym::u}},//舗 pu
{1,0,{pysm::g,pyym::uan}},//舘 guan
{2,2537,{pysm::nop,pyym::nop}},//舙 hua
{1,0,{pysm::t,pyym::ian}},//舚 tian
{1,0,{pysm::ch,pyym::uan}},//舛 chuan
{1,0,{pysm::sh,pyym::un}},//舜 shun
{1,0,{pysm::x,pyym::ia}},//舝 xia
{1,0,{pysm::w,pyym::u}},//舞 wu
{1,0,{pysm::zh,pyym::ou}},//舟 zhou
{1,0,{pysm::d,pyym::ao}},//舠 dao
{2,2538,{pysm::nop,pyym::nop}},//舡 chuan
{1,0,{pysm::sh,pyym::an}},//舢 shan
{1,0,{pysm::y,pyym::i}},//舣 yi
{1,0,{pysm::f,pyym::an}},//舤 fan
{1,0,{pysm::p,pyym::a}},//舥 pa
{1,0,{pysm::t,pyym::ai}},//舦 tai
{1,0,{pysm::f,pyym::an}},//舧 fan
{1,0,{pysm::b,pyym::an}},//舨 ban
{2,2539,{pysm::nop,pyym::nop}},//舩 chuan
{1,0,{pysm::h,pyym::ang}},//航 hang
{1,0,{pysm::f,pyym::ang}},//舫 fang
{3,619,{pysm::nop,pyym::nop}},//般 ban
{1,0,{pysm::b,pyym::i}},//舭 bi
{1,0,{pysm::l,pyym::u}},//舮 lu
{1,0,{pysm::zh,pyym::ong}},//舯 zhong
{1,0,{pysm::j,pyym::ian}},//舰 jian
{1,0,{pysm::c,pyym::ang}},//舱 cang
{1,0,{pysm::l,pyym::ing}},//舲 ling
{2,2540,{pysm::nop,pyym::nop}},//舳 zhu
{1,0,{pysm::z,pyym::e}},//舴 ze
{1,0,{pysm::d,pyym::uo}},//舵 duo
{1,0,{pysm::b,pyym::o}},//舶 bo
{1,0,{pysm::x,pyym::ian}},//舷 xian
{1,0,{pysm::g,pyym::e}},//舸 ge
{1,0,{pysm::ch,pyym::uan}},//船 chuan
{1,0,{pysm::x,pyym::ia}},//舺 xia
{1,0,{pysm::l,pyym::u}},//舻 lu
{2,2541,{pysm::nop,pyym::nop}},//舼 qiong
{2,2542,{pysm::nop,pyym::nop}},//舽 pang
{1,0,{pysm::x,pyym::i}},//舾 xi
{1,0,{pysm::k,pyym::ua}},//舿 kua
{1,0,{pysm::f,pyym::u}},//艀 fu
{1,0,{pysm::z,pyym::ao}},//艁 zao
{1,0,{pysm::f,pyym::eng}},//艂 feng
{1,0,{pysm::l,pyym::i}},//艃 li
{1,0,{pysm::sh,pyym::ao}},//艄 shao
{1,0,{pysm::y,pyym::u}},//艅 yu
{1,0,{pysm::l,pyym::ang}},//艆 lang
{1,0,{pysm::t,pyym::ing}},//艇 ting
{1,0,{pysm::y,pyym::u}},//艈 yu
{1,0,{pysm::w,pyym::ei}},//艉 wei
{1,0,{pysm::b,pyym::o}},//艊 bo
{1,0,{pysm::m,pyym::eng}},//艋 meng
{2,2543,{pysm::nop,pyym::nop}},//艌 nian
{1,0,{pysm::j,pyym::u}},//艍 ju
{1,0,{pysm::h,pyym::uang}},//艎 huang
{1,0,{pysm::sh,pyym::ou}},//艏 shou
{3,620,{pysm::nop,pyym::nop}},//艐 ke
{1,0,{pysm::b,pyym::ian}},//艑 bian
{2,2544,{pysm::nop,pyym::nop}},//艒 mu
{1,0,{pysm::d,pyym::ie}},//艓 die
{1,0,{pysm::d,pyym::ao}},//艔 dao
{1,0,{pysm::b,pyym::ang}},//艕 bang
{1,0,{pysm::ch,pyym::a}},//艖 cha
{1,0,{pysm::y,pyym::i}},//艗 yi
{1,0,{pysm::s,pyym::ou}},//艘 sou
{1,0,{pysm::c,pyym::ang}},//艙 cang
{1,0,{pysm::c,pyym::ao}},//艚 cao
{1,0,{pysm::l,pyym::ou}},//艛 lou
{1,0,{pysm::d,pyym::ai}},//艜 dai
{1,0,{pysm::x,pyym::ue}},//艝 xue
{2,2545,{pysm::nop,pyym::nop}},//艞 yao
{3,621,{pysm::nop,pyym::nop}},//艟 chong
{1,0,{pysm::d,pyym::eng}},//艠 deng
{1,0,{pysm::d,pyym::ang}},//艡 dang
{1,0,{pysm::q,pyym::iang}},//艢 qiang
{1,0,{pysm::l,pyym::u}},//艣 lu
{1,0,{pysm::y,pyym::i}},//艤 yi
{1,0,{pysm::j,pyym::i}},//艥 ji
{1,0,{pysm::j,pyym::ian}},//艦 jian
{2,2546,{pysm::nop,pyym::nop}},//艧 huo
{1,0,{pysm::m,pyym::eng}},//艨 meng
{1,0,{pysm::q,pyym::i}},//艩 qi
{1,0,{pysm::l,pyym::u}},//艪 lu
{1,0,{pysm::l,pyym::u}},//艫 lu
{1,0,{pysm::ch,pyym::an}},//艬 chan
{1,0,{pysm::sh,pyym::uang}},//艭 shuang
{2,2547,{pysm::nop,pyym::nop}},//艮 gen
{1,0,{pysm::l,pyym::iang}},//良 liang
{1,0,{pysm::j,pyym::ian}},//艰 jian
{1,0,{pysm::j,pyym::ian}},//艱 jian
{2,2548,{pysm::nop,pyym::nop}},//色 se
{1,0,{pysm::y,pyym::an}},//艳 yan
{3,622,{pysm::nop,pyym::nop}},//艴 fu
{1,0,{pysm::p,pyym::ing}},//艵 ping
{1,0,{pysm::y,pyym::an}},//艶 yan
{1,0,{pysm::y,pyym::an}},//艷 yan
{1,0,{pysm::c,pyym::ao}},//艸 cao
{1,0,{pysm::c,pyym::ao}},//艹 cao
{1,0,{pysm::y,pyym::i}},//艺 yi
{2,2549,{pysm::nop,pyym::nop}},//艻 le
{2,2550,{pysm::nop,pyym::nop}},//艼 ting
{2,2551,{pysm::nop,pyym::nop}},//艽 jiao
{2,2552,{pysm::nop,pyym::nop}},//艾 ai
{2,2553,{pysm::nop,pyym::nop}},//艿 nai
{1,0,{pysm::t,pyym::iao}},//芀 tiao
{1,0,{pysm::j,pyym::iao}},//芁 jiao
{1,0,{pysm::j,pyym::ie}},//节 jie
{1,0,{pysm::p,pyym::eng}},//芃 peng
{1,0,{pysm::w,pyym::an}},//芄 wan
{1,0,{pysm::y,pyym::i}},//芅 yi
{2,2554,{pysm::nop,pyym::nop}},//芆 chai
{1,0,{pysm::m,pyym::ian}},//芇 mian
{1,0,{pysm::m,pyym::i}},//芈 mi
{1,0,{pysm::g,pyym::an}},//芉 gan
{1,0,{pysm::q,pyym::ian}},//芊 qian
{2,2555,{pysm::nop,pyym::nop}},//芋 yu
{1,0,{pysm::y,pyym::u}},//芌 yu
{4,119,{pysm::nop,pyym::nop}},//芍 shao
{2,2556,{pysm::nop,pyym::nop}},//芎 qiong
{1,0,{pysm::d,pyym::u}},//芏 du
{2,2557,{pysm::nop,pyym::nop}},//芐 hu
{1,0,{pysm::q,pyym::i}},//芑 qi
{3,623,{pysm::nop,pyym::nop}},//芒 mang
{1,0,{pysm::z,pyym::i}},//芓 zi
{2,2558,{pysm::nop,pyym::nop}},//芔 hui
{1,0,{pysm::s,pyym::ui}},//芕 sui
{1,0,{pysm::zh,pyym::i}},//芖 zhi
{1,0,{pysm::x,pyym::iang}},//芗 xiang
{2,2559,{pysm::nop,pyym::nop}},//芘 pi
{1,0,{pysm::f,pyym::u}},//芙 fu
{2,2560,{pysm::nop,pyym::nop}},//芚 tun
{1,0,{pysm::w,pyym::ei}},//芛 wei
{1,0,{pysm::w,pyym::u}},//芜 wu
{1,0,{pysm::zh,pyym::i}},//芝 zhi
{1,0,{pysm::q,pyym::i}},//芞 qi
{2,2561,{pysm::nop,pyym::nop}},//芟 shan
{1,0,{pysm::w,pyym::en}},//芠 wen
{1,0,{pysm::q,pyym::ian}},//芡 qian
{1,0,{pysm::r,pyym::en}},//芢 ren
{2,2562,{pysm::nop,pyym::nop}},//芣 fu
{1,0,{pysm::k,pyym::ou}},//芤 kou
{2,2563,{pysm::nop,pyym::nop}},//芥 jie
{2,2564,{pysm::nop,pyym::nop}},//芦 lu
{2,2565,{pysm::nop,pyym::nop}},//芧 xu
{1,0,{pysm::j,pyym::i}},//芨 ji
{2,2566,{pysm::nop,pyym::nop}},//芩 qin
{2,2567,{pysm::nop,pyym::nop}},//芪 qi
{2,2568,{pysm::nop,pyym::nop}},//芫 yan
{1,0,{pysm::f,pyym::en}},//芬 fen
{2,2569,{pysm::nop,pyym::nop}},//芭 ba
{2,2570,{pysm::nop,pyym::nop}},//芮 rui
{1,0,{pysm::x,pyym::in}},//芯 xin
{1,0,{pysm::j,pyym::i}},//芰 ji
{1,0,{pysm::h,pyym::ua}},//花 hua
{1,0,{pysm::h,pyym::ua}},//芲 hua
{1,0,{pysm::f,pyym::ang}},//芳 fang
{2,2571,{pysm::nop,pyym::nop}},//芴 wu
{1,0,{pysm::j,pyym::ue}},//芵 jue
{1,0,{pysm::g,pyym::ou}},//芶 gou
{1,0,{pysm::zh,pyym::i}},//芷 zhi
{1,0,{pysm::y,pyym::un}},//芸 yun
{1,0,{pysm::q,pyym::in}},//芹 qin
{1,0,{pysm::nop,pyym::ao}},//芺 ao
{2,2572,{pysm::nop,pyym::nop}},//芻 chu
{1,0,{pysm::m,pyym::ao}},//芼 mao
{1,0,{pysm::y,pyym::a}},//芽 ya
{2,2573,{pysm::nop,pyym::nop}},//芾 fei
{1,0,{pysm::r,pyym::eng}},//芿 reng
{1,0,{pysm::h,pyym::ang}},//苀 hang
{1,0,{pysm::c,pyym::ong}},//苁 cong
{1,0,{pysm::y,pyym::in}},//苂 yin
{1,0,{pysm::y,pyym::ou}},//苃 you
{1,0,{pysm::b,pyym::ian}},//苄 bian
{1,0,{pysm::y,pyym::i}},//苅 yi
{1,0,{pysm::q,pyym::ie}},//苆 qie
{1,0,{pysm::w,pyym::ei}},//苇 wei
{1,0,{pysm::l,pyym::i}},//苈 li
{1,0,{pysm::p,pyym::i}},//苉 pi
{1,0,{pysm::nop,pyym::e}},//苊 e
{1,0,{pysm::x,pyym::ian}},//苋 xian
{1,0,{pysm::ch,pyym::ang}},//苌 chang
{1,0,{pysm::c,pyym::ang}},//苍 cang
{1,0,{pysm::zh,pyym::u}},//苎 zhu
{1,0,{pysm::s,pyym::u}},//苏 su
{2,2574,{pysm::nop,pyym::nop}},//苐 ti
{3,624,{pysm::nop,pyym::nop}},//苑 yuan
{1,0,{pysm::r,pyym::an}},//苒 ran
{2,2575,{pysm::nop,pyym::nop}},//苓 ling
{1,0,{pysm::t,pyym::ai}},//苔 tai
{2,2576,{pysm::nop,pyym::nop}},//苕 shao
{1,0,{pysm::d,pyym::i}},//苖 di
{1,0,{pysm::m,pyym::iao}},//苗 miao
{1,0,{pysm::q,pyym::ing}},//苘 qing
{2,2577,{pysm::nop,pyym::nop}},//苙 li
{1,0,{pysm::y,pyym::ong}},//苚 yong
{2,2578,{pysm::nop,pyym::nop}},//苛 ke
{1,0,{pysm::m,pyym::u}},//苜 mu
{1,0,{pysm::b,pyym::ei}},//苝 bei
{3,625,{pysm::nop,pyym::nop}},//苞 bao
{1,0,{pysm::g,pyym::ou}},//苟 gou
{1,0,{pysm::m,pyym::in}},//苠 min
{1,0,{pysm::y,pyym::i}},//苡 yi
{1,0,{pysm::y,pyym::i}},//苢 yi
{2,2579,{pysm::nop,pyym::nop}},//苣 ju
{2,2580,{pysm::nop,pyym::nop}},//苤 pie
{2,2581,{pysm::nop,pyym::nop}},//若 ruo
{3,626,{pysm::nop,pyym::nop}},//苦 ku
{2,2582,{pysm::nop,pyym::nop}},//苧 ning
{1,0,{pysm::n,pyym::i}},//苨 ni
{2,2583,{pysm::nop,pyym::nop}},//苩 bo
{1,0,{pysm::b,pyym::ing}},//苪 bing
{3,627,{pysm::nop,pyym::nop}},//苫 shan
{1,0,{pysm::x,pyym::iu}},//苬 xiu
{1,0,{pysm::y,pyym::ao}},//苭 yao
{1,0,{pysm::x,pyym::ian}},//苮 xian
{1,0,{pysm::b,pyym::en}},//苯 ben
{1,0,{pysm::h,pyym::ong}},//苰 hong
{2,2584,{pysm::nop,pyym::nop}},//英 ying
{2,2585,{pysm::nop,pyym::nop}},//苲 zha
{1,0,{pysm::d,pyym::ong}},//苳 dong
{7,3,{pysm::nop,pyym::nop}},//苴 ju
{1,0,{pysm::d,pyym::ie}},//苵 die
{1,0,{pysm::n,pyym::ie}},//苶 nie
{1,0,{pysm::g,pyym::an}},//苷 gan
{1,0,{pysm::h,pyym::u}},//苸 hu
{2,2586,{pysm::nop,pyym::nop}},//苹 ping
{1,0,{pysm::m,pyym::ei}},//苺 mei
{2,2587,{pysm::nop,pyym::nop}},//苻 fu
{2,2588,{pysm::nop,pyym::nop}},//苼 sheng
{2,2589,{pysm::nop,pyym::nop}},//苽 gu
{3,628,{pysm::nop,pyym::nop}},//苾 bi
{1,0,{pysm::w,pyym::ei}},//苿 wei
{5,40,{pysm::nop,pyym::nop}},//茀 fu
{2,2590,{pysm::nop,pyym::nop}},//茁 zhuo
{1,0,{pysm::m,pyym::ao}},//茂 mao
{1,0,{pysm::f,pyym::an}},//范 fan
{2,2591,{pysm::nop,pyym::nop}},//茄 jia
{1,0,{pysm::m,pyym::ao}},//茅 mao
{1,0,{pysm::m,pyym::ao}},//茆 mao
{3,629,{pysm::nop,pyym::nop}},//茇 ba
{3,630,{pysm::nop,pyym::nop}},//茈 ci
{1,0,{pysm::m,pyym::o}},//茉 mo
{1,0,{pysm::z,pyym::i}},//茊 zi
{2,2592,{pysm::nop,pyym::nop}},//茋 zhi
{1,0,{pysm::ch,pyym::i}},//茌 chi
{1,0,{pysm::j,pyym::i}},//茍 ji
{1,0,{pysm::j,pyym::ing}},//茎 jing
{1,0,{pysm::l,pyym::ong}},//茏 long
{1,0,{pysm::c,pyym::ong}},//茐 cong
{1,0,{pysm::n,pyym::iao}},//茑 niao
{1,0,{pysm::y,pyym::uan}},//茒 yuan
{1,0,{pysm::x,pyym::ue}},//茓 xue
{1,0,{pysm::y,pyym::ing}},//茔 ying
{1,0,{pysm::q,pyym::iong}},//茕 qiong
{2,2593,{pysm::nop,pyym::nop}},//茖 ge
{1,0,{pysm::m,pyym::ing}},//茗 ming
{1,0,{pysm::l,pyym::i}},//茘 li
{1,0,{pysm::r,pyym::ong}},//茙 rong
{1,0,{pysm::y,pyym::in}},//茚 yin
{2,2594,{pysm::nop,pyym::nop}},//茛 gen
{2,2595,{pysm::nop,pyym::nop}},//茜 qian
{2,2596,{pysm::nop,pyym::nop}},//茝 chai
{1,0,{pysm::ch,pyym::en}},//茞 chen
{2,2597,{pysm::nop,pyym::nop}},//茟 yu
{3,631,{pysm::nop,pyym::nop}},//茠 hao
{1,0,{pysm::z,pyym::i}},//茡 zi
{1,0,{pysm::l,pyym::ie}},//茢 lie
{1,0,{pysm::w,pyym::u}},//茣 wu
{2,2598,{pysm::nop,pyym::nop}},//茤 ji
{1,0,{pysm::g,pyym::ui}},//茥 gui
{1,0,{pysm::c,pyym::i}},//茦 ci
{2,2599,{pysm::nop,pyym::nop}},//茧 jian
{1,0,{pysm::c,pyym::i}},//茨 ci
{1,0,{pysm::g,pyym::ou}},//茩 gou
{1,0,{pysm::g,pyym::uang}},//茪 guang
{2,2600,{pysm::nop,pyym::nop}},//茫 mang
{2,2601,{pysm::nop,pyym::nop}},//茬 cha
{3,632,{pysm::nop,pyym::nop}},//茭 jiao
{2,2602,{pysm::nop,pyym::nop}},//茮 jiao
{1,0,{pysm::f,pyym::u}},//茯 fu
{1,0,{pysm::y,pyym::u}},//茰 yu
{1,0,{pysm::zh,pyym::u}},//茱 zhu
{2,2603,{pysm::nop,pyym::nop}},//茲 zi
{1,0,{pysm::j,pyym::iang}},//茳 jiang
{1,0,{pysm::h,pyym::ui}},//茴 hui
{1,0,{pysm::y,pyym::in}},//茵 yin
{1,0,{pysm::ch,pyym::a}},//茶 cha
{4,120,{pysm::nop,pyym::nop}},//茷 fa
{1,0,{pysm::r,pyym::ong}},//茸 rong
{1,0,{pysm::r,pyym::u}},//茹 ru
{1,0,{pysm::ch,pyym::ong}},//茺 chong
{2,2604,{pysm::nop,pyym::nop}},//茻 mang
{1,0,{pysm::t,pyym::ong}},//茼 tong
{1,0,{pysm::zh,pyym::ong}},//茽 zhong
{1,0,{pysm::q,pyym::ian}},//茾 qian
{1,0,{pysm::zh,pyym::u}},//茿 zhu
{1,0,{pysm::x,pyym::un}},//荀 xun
{1,0,{pysm::h,pyym::uan}},//荁 huan
{1,0,{pysm::f,pyym::u}},//荂 fu
{2,2605,{pysm::nop,pyym::nop}},//荃 quan
{1,0,{pysm::g,pyym::ai}},//荄 gai
{2,2606,{pysm::nop,pyym::nop}},//荅 da
{1,0,{pysm::j,pyym::ing}},//荆 jing
{1,0,{pysm::x,pyym::ing}},//荇 xing
{1,0,{pysm::ch,pyym::uan}},//荈 chuan
{2,2607,{pysm::nop,pyym::nop}},//草 cao
{1,0,{pysm::j,pyym::ing}},//荊 jing
{1,0,{pysm::nop,pyym::er}},//荋 er
{1,0,{pysm::nop,pyym::an}},//荌 an
{1,0,{pysm::q,pyym::iao}},//荍 qiao
{1,0,{pysm::ch,pyym::i}},//荎 chi
{1,0,{pysm::r,pyym::en}},//荏 ren
{1,0,{pysm::j,pyym::ian}},//荐 jian
{2,2608,{pysm::nop,pyym::nop}},//荑 ti
{2,2609,{pysm::nop,pyym::nop}},//荒 huang
{2,2610,{pysm::nop,pyym::nop}},//荓 ping
{1,0,{pysm::l,pyym::i}},//荔 li
{1,0,{pysm::j,pyym::in}},//荕 jin
{2,2611,{pysm::nop,pyym::nop}},//荖 lao
{1,0,{pysm::sh,pyym::u}},//荗 shu
{1,0,{pysm::zh,pyym::uang}},//荘 zhuang
{1,0,{pysm::d,pyym::a}},//荙 da
{1,0,{pysm::j,pyym::ia}},//荚 jia
{1,0,{pysm::r,pyym::ao}},//荛 rao
{1,0,{pysm::b,pyym::i}},//荜 bi
{1,0,{pysm::c,pyym::e}},//荝 ce
{1,0,{pysm::q,pyym::iao}},//荞 qiao
{1,0,{pysm::h,pyym::ui}},//荟 hui
{2,2612,{pysm::nop,pyym::nop}},//荠 ji
{1,0,{pysm::d,pyym::ang}},//荡 dang
{1,0,{pysm::z,pyym::i}},//荢 zi
{1,0,{pysm::r,pyym::ong}},//荣 rong
{2,2613,{pysm::nop,pyym::nop}},//荤 hun
{2,2614,{pysm::nop,pyym::nop}},//荥 xing
{1,0,{pysm::l,pyym::uo}},//荦 luo
{1,0,{pysm::y,pyym::ing}},//荧 ying
{2,2615,{pysm::nop,pyym::nop}},//荨 xun
{1,0,{pysm::j,pyym::in}},//荩 jin
{1,0,{pysm::s,pyym::un}},//荪 sun
{1,0,{pysm::y,pyym::in}},//荫 yin
{1,0,{pysm::m,pyym::ai}},//荬 mai
{1,0,{pysm::h,pyym::ong}},//荭 hong
{1,0,{pysm::zh,pyym::ou}},//荮 zhou
{1,0,{pysm::y,pyym::ao}},//药 yao
{1,0,{pysm::d,pyym::u}},//荰 du
{1,0,{pysm::w,pyym::ei}},//荱 wei
{1,0,{pysm::l,pyym::i}},//荲 li
{1,0,{pysm::d,pyym::ou}},//荳 dou
{1,0,{pysm::f,pyym::u}},//荴 fu
{1,0,{pysm::r,pyym::en}},//荵 ren
{1,0,{pysm::y,pyym::in}},//荶 yin
{1,0,{pysm::h,pyym::e}},//荷 he
{1,0,{pysm::b,pyym::i}},//荸 bi
{2,2616,{pysm::nop,pyym::nop}},//荹 bu
{1,0,{pysm::y,pyym::un}},//荺 yun
{1,0,{pysm::d,pyym::i}},//荻 di
{4,121,{pysm::nop,pyym::nop}},//荼 tu
{2,2617,{pysm::nop,pyym::nop}},//荽 sui
{1,0,{pysm::s,pyym::ui}},//荾 sui
{1,0,{pysm::ch,pyym::eng}},//荿 cheng
{2,2618,{pysm::nop,pyym::nop}},//莀 chen
{1,0,{pysm::w,pyym::u}},//莁 wu
{1,0,{pysm::b,pyym::ie}},//莂 bie
{1,0,{pysm::x,pyym::i}},//莃 xi
{1,0,{pysm::g,pyym::eng}},//莄 geng
{1,0,{pysm::l,pyym::i}},//莅 li
{2,2619,{pysm::nop,pyym::nop}},//莆 pu
{1,0,{pysm::zh,pyym::u}},//莇 zhu
{1,0,{pysm::m,pyym::o}},//莈 mo
{2,2620,{pysm::nop,pyym::nop}},//莉 li
{1,0,{pysm::zh,pyym::uang}},//莊 zhuang
{2,2621,{pysm::nop,pyym::nop}},//莋 zuo
{1,0,{pysm::t,pyym::uo}},//莌 tuo
{1,0,{pysm::q,pyym::iu}},//莍 qiu
{3,633,{pysm::nop,pyym::nop}},//莎 sha
{1,0,{pysm::s,pyym::uo}},//莏 suo
{1,0,{pysm::ch,pyym::en}},//莐 chen
{2,2622,{pysm::nop,pyym::nop}},//莑 peng
{1,0,{pysm::j,pyym::u}},//莒 ju
{1,0,{pysm::m,pyym::ei}},//莓 mei
{3,634,{pysm::nop,pyym::nop}},//莔 meng
{1,0,{pysm::x,pyym::ing}},//莕 xing
{2,2623,{pysm::nop,pyym::nop}},//莖 jing
{1,0,{pysm::ch,pyym::e}},//莗 che
{2,2624,{pysm::nop,pyym::nop}},//莘 shen
{1,0,{pysm::j,pyym::un}},//莙 jun
{1,0,{pysm::y,pyym::an}},//莚 yan
{1,0,{pysm::t,pyym::ing}},//莛 ting
{3,635,{pysm::nop,pyym::nop}},//莜 you
{1,0,{pysm::c,pyym::uo}},//莝 cuo
{2,2625,{pysm::nop,pyym::nop}},//莞 guan
{1,0,{pysm::h,pyym::an}},//莟 han
{2,2626,{pysm::nop,pyym::nop}},//莠 you
{1,0,{pysm::c,pyym::uo}},//莡 cuo
{1,0,{pysm::j,pyym::ia}},//莢 jia
{1,0,{pysm::w,pyym::ang}},//莣 wang
{2,2627,{pysm::nop,pyym::nop}},//莤 su
{2,2628,{pysm::nop,pyym::nop}},//莥 niu
{2,2629,{pysm::nop,pyym::nop}},//莦 shao
{2,2630,{pysm::nop,pyym::nop}},//莧 xian
{2,2631,{pysm::nop,pyym::nop}},//莨 lang
{2,2632,{pysm::nop,pyym::nop}},//莩 fu
{1,0,{pysm::nop,pyym::e}},//莪 e
{2,2633,{pysm::nop,pyym::nop}},//莫 mo
{3,636,{pysm::nop,pyym::nop}},//莬 wen
{1,0,{pysm::j,pyym::ie}},//莭 jie
{1,0,{pysm::n,pyym::an}},//莮 nan
{1,0,{pysm::m,pyym::u}},//莯 mu
{1,0,{pysm::k,pyym::an}},//莰 kan
{1,0,{pysm::l,pyym::ai}},//莱 lai
{1,0,{pysm::l,pyym::ian}},//莲 lian
{1,0,{pysm::sh,pyym::i}},//莳 shi
{1,0,{pysm::w,pyym::o}},//莴 wo
{1,0,{pysm::t,pyym::u}},//莵 tu
{1,0,{pysm::x,pyym::ian}},//莶 xian
{1,0,{pysm::h,pyym::uo}},//获 huo
{1,0,{pysm::y,pyym::ou}},//莸 you
{1,0,{pysm::y,pyym::ing}},//莹 ying
{1,0,{pysm::y,pyym::ing}},//莺 ying
{1,0,{pysm::g,pyym::ong}},//莻 gong
{1,0,{pysm::ch,pyym::un}},//莼 chun
{1,0,{pysm::m,pyym::ang}},//莽 mang
{1,0,{pysm::m,pyym::ang}},//莾 mang
{1,0,{pysm::c,pyym::i}},//莿 ci
{3,637,{pysm::nop,pyym::nop}},//菀 wan
{1,0,{pysm::j,pyym::ing}},//菁 jing
{1,0,{pysm::d,pyym::i}},//菂 di
{1,0,{pysm::q,pyym::u}},//菃 qu
{1,0,{pysm::d,pyym::ong}},//菄 dong
{2,2634,{pysm::nop,pyym::nop}},//菅 jian
{4,122,{pysm::nop,pyym::nop}},//菆 zou
{1,0,{pysm::g,pyym::u}},//菇 gu
{1,0,{pysm::l,pyym::a}},//菈 la
{2,2635,{pysm::nop,pyym::nop}},//菉 lu
{1,0,{pysm::j,pyym::u}},//菊 ju
{1,0,{pysm::w,pyym::ei}},//菋 wei
{1,0,{pysm::j,pyym::un}},//菌 jun
{2,2636,{pysm::nop,pyym::nop}},//菍 nie
{1,0,{pysm::k,pyym::un}},//菎 kun
{2,2637,{pysm::nop,pyym::nop}},//菏 he
{1,0,{pysm::p,pyym::u}},//菐 pu
{2,2638,{pysm::nop,pyym::nop}},//菑 zai
{1,0,{pysm::g,pyym::ao}},//菒 gao
{1,0,{pysm::g,pyym::uo}},//菓 guo
{1,0,{pysm::f,pyym::u}},//菔 fu
{1,0,{pysm::l,pyym::un}},//菕 lun
{1,0,{pysm::ch,pyym::ang}},//菖 chang
{1,0,{pysm::ch,pyym::ou}},//菗 chou
{1,0,{pysm::s,pyym::ong}},//菘 song
{1,0,{pysm::ch,pyym::ui}},//菙 chui
{1,0,{pysm::zh,pyym::an}},//菚 zhan
{1,0,{pysm::m,pyym::en}},//菛 men
{1,0,{pysm::c,pyym::ai}},//菜 cai
{1,0,{pysm::b,pyym::a}},//菝 ba
{1,0,{pysm::l,pyym::i}},//菞 li
{1,0,{pysm::t,pyym::u}},//菟 tu
{1,0,{pysm::b,pyym::o}},//菠 bo
{1,0,{pysm::h,pyym::an}},//菡 han
{1,0,{pysm::b,pyym::ao}},//菢 bao
{1,0,{pysm::q,pyym::in}},//菣 qin
{1,0,{pysm::j,pyym::uan}},//菤 juan
{2,2639,{pysm::nop,pyym::nop}},//菥 xi
{1,0,{pysm::q,pyym::in}},//菦 qin
{1,0,{pysm::d,pyym::i}},//菧 di
{2,2640,{pysm::nop,pyym::nop}},//菨 jie
{3,638,{pysm::nop,pyym::nop}},//菩 pu
{1,0,{pysm::d,pyym::ang}},//菪 dang
{1,0,{pysm::j,pyym::in}},//菫 jin
{2,2641,{pysm::nop,pyym::nop}},//菬 qiao
{3,639,{pysm::nop,pyym::nop}},//菭 tai
{1,0,{pysm::g,pyym::eng}},//菮 geng
{2,2642,{pysm::nop,pyym::nop}},//華 hua
{1,0,{pysm::g,pyym::u}},//菰 gu
{1,0,{pysm::l,pyym::ing}},//菱 ling
{1,0,{pysm::f,pyym::ei}},//菲 fei
{2,2643,{pysm::nop,pyym::nop}},//菳 qin
{2,2644,{pysm::nop,pyym::nop}},//菴 an
{1,0,{pysm::w,pyym::ang}},//菵 wang
{1,0,{pysm::b,pyym::eng}},//菶 beng
{1,0,{pysm::zh,pyym::ou}},//菷 zhou
{2,2645,{pysm::nop,pyym::nop}},//菸 yan
{2,2646,{pysm::nop,pyym::nop}},//菹 ju
{1,0,{pysm::j,pyym::ian}},//菺 jian
{1,0,{pysm::l,pyym::in}},//菻 lin
{1,0,{pysm::t,pyym::an}},//菼 tan
{2,2647,{pysm::nop,pyym::nop}},//菽 shu
{1,0,{pysm::t,pyym::ian}},//菾 tian
{1,0,{pysm::d,pyym::ao}},//菿 dao
{1,0,{pysm::h,pyym::u}},//萀 hu
{2,2648,{pysm::nop,pyym::nop}},//萁 qi
{1,0,{pysm::h,pyym::e}},//萂 he
{1,0,{pysm::c,pyym::ui}},//萃 cui
{1,0,{pysm::t,pyym::ao}},//萄 tao
{1,0,{pysm::ch,pyym::un}},//萅 chun
{4,123,{pysm::nop,pyym::nop}},//萆 bi
{1,0,{pysm::ch,pyym::ang}},//萇 chang
{1,0,{pysm::h,pyym::uan}},//萈 huan
{2,2649,{pysm::nop,pyym::nop}},//萉 fei
{1,0,{pysm::l,pyym::ai}},//萊 lai
{1,0,{pysm::q,pyym::i}},//萋 qi
{2,2650,{pysm::nop,pyym::nop}},//萌 meng
{1,0,{pysm::p,pyym::ing}},//萍 ping
{1,0,{pysm::w,pyym::ei}},//萎 wei
{1,0,{pysm::d,pyym::an}},//萏 dan
{1,0,{pysm::sh,pyym::a}},//萐 sha
{2,2651,{pysm::nop,pyym::nop}},//萑 huan
{2,2652,{pysm::nop,pyym::nop}},//萒 yan
{1,0,{pysm::y,pyym::i}},//萓 yi
{1,0,{pysm::t,pyym::iao}},//萔 tiao
{1,0,{pysm::q,pyym::i}},//萕 qi
{1,0,{pysm::w,pyym::an}},//萖 wan
{1,0,{pysm::c,pyym::e}},//萗 ce
{1,0,{pysm::n,pyym::ai}},//萘 nai
{1,0,{pysm::zh,pyym::en}},//萙 zhen
{1,0,{pysm::t,pyym::uo}},//萚 tuo
{1,0,{pysm::j,pyym::iu}},//萛 jiu
{1,0,{pysm::t,pyym::ie}},//萜 tie
{1,0,{pysm::l,pyym::uo}},//萝 luo
{1,0,{pysm::b,pyym::i}},//萞 bi
{1,0,{pysm::y,pyym::i}},//萟 yi
{1,0,{pysm::p,pyym::an}},//萠 pan
{1,0,{pysm::b,pyym::o}},//萡 bo
{1,0,{pysm::p,pyym::ao}},//萢 pao
{1,0,{pysm::d,pyym::ing}},//萣 ding
{1,0,{pysm::y,pyym::ing}},//萤 ying
{1,0,{pysm::y,pyym::ing}},//营 ying
{1,0,{pysm::y,pyym::ing}},//萦 ying
{1,0,{pysm::x,pyym::iao}},//萧 xiao
{1,0,{pysm::s,pyym::a}},//萨 sa
{2,2653,{pysm::nop,pyym::nop}},//萩 qiu
{1,0,{pysm::k,pyym::e}},//萪 ke
{1,0,{pysm::x,pyym::iang}},//萫 xiang
{1,0,{pysm::w,pyym::an}},//萬 wan
{2,2654,{pysm::nop,pyym::nop}},//萭 yu
{1,0,{pysm::y,pyym::u}},//萮 yu
{2,2655,{pysm::nop,pyym::nop}},//萯 fu
{1,0,{pysm::l,pyym::ian}},//萰 lian
{1,0,{pysm::x,pyym::uan}},//萱 xuan
{1,0,{pysm::x,pyym::uan}},//萲 xuan
{1,0,{pysm::n,pyym::an}},//萳 nan
{1,0,{pysm::c,pyym::e}},//萴 ce
{1,0,{pysm::w,pyym::o}},//萵 wo
{1,0,{pysm::ch,pyym::un}},//萶 chun
{3,640,{pysm::nop,pyym::nop}},//萷 xiao
{1,0,{pysm::y,pyym::u}},//萸 yu
{2,2656,{pysm::nop,pyym::nop}},//萹 bian
{2,2657,{pysm::nop,pyym::nop}},//萺 mao
{1,0,{pysm::nop,pyym::an}},//萻 an
{1,0,{pysm::nop,pyym::e}},//萼 e
{3,641,{pysm::nop,pyym::nop}},//落 luo
{1,0,{pysm::y,pyym::ing}},//萾 ying
{2,2658,{pysm::nop,pyym::nop}},//萿 kuo
{1,0,{pysm::k,pyym::uo}},//葀 kuo
{1,0,{pysm::j,pyym::iang}},//葁 jiang
{1,0,{pysm::m,pyym::ian}},//葂 mian
{2,2659,{pysm::nop,pyym::nop}},//葃 zuo
{1,0,{pysm::z,pyym::uo}},//葄 zuo
{1,0,{pysm::z,pyym::u}},//葅 zu
{1,0,{pysm::b,pyym::ao}},//葆 bao
{1,0,{pysm::r,pyym::ou}},//葇 rou
{1,0,{pysm::x,pyym::i}},//葈 xi
{2,2660,{pysm::nop,pyym::nop}},//葉 ye
{1,0,{pysm::nop,pyym::an}},//葊 an
{1,0,{pysm::q,pyym::u}},//葋 qu
{1,0,{pysm::j,pyym::ian}},//葌 jian
{1,0,{pysm::f,pyym::u}},//葍 fu
{1,0,{pysm::l,pyym::v}},//葎 lü
{1,0,{pysm::j,pyym::ing}},//葏 jing
{2,2661,{pysm::nop,pyym::nop}},//葐 pen
{1,0,{pysm::f,pyym::eng}},//葑 feng
{1,0,{pysm::h,pyym::ong}},//葒 hong
{1,0,{pysm::h,pyym::ong}},//葓 hong
{1,0,{pysm::h,pyym::ou}},//葔 hou
{1,0,{pysm::y,pyym::an}},//葕 yan
{1,0,{pysm::t,pyym::u}},//葖 tu
{5,41,{pysm::nop,pyym::nop}},//著 zhu
{1,0,{pysm::z,pyym::i}},//葘 zi
{1,0,{pysm::x,pyym::iang}},//葙 xiang
{2,2662,{pysm::nop,pyym::nop}},//葚 ren
{1,0,{pysm::g,pyym::e}},//葛 ge
{1,0,{pysm::q,pyym::ia}},//葜 qia
{2,2663,{pysm::nop,pyym::nop}},//葝 qing
{1,0,{pysm::m,pyym::i}},//葞 mi
{1,0,{pysm::h,pyym::uang}},//葟 huang
{2,2664,{pysm::nop,pyym::nop}},//葠 shen
{2,2665,{pysm::nop,pyym::nop}},//葡 pu
{1,0,{pysm::g,pyym::ai}},//葢 gai
{2,2666,{pysm::nop,pyym::nop}},//董 dong
{1,0,{pysm::zh,pyym::ou}},//葤 zhou
{2,2667,{pysm::nop,pyym::nop}},//葥 jian
{1,0,{pysm::w,pyym::ei}},//葦 wei
{1,0,{pysm::b,pyym::o}},//葧 bo
{1,0,{pysm::w,pyym::ei}},//葨 wei
{1,0,{pysm::p,pyym::a}},//葩 pa
{1,0,{pysm::j,pyym::i}},//葪 ji
{1,0,{pysm::h,pyym::u}},//葫 hu
{1,0,{pysm::z,pyym::ang}},//葬 zang
{2,2668,{pysm::nop,pyym::nop}},//葭 jia
{1,0,{pysm::d,pyym::uan}},//葮 duan
{1,0,{pysm::y,pyym::ao}},//葯 yao
{3,642,{pysm::nop,pyym::nop}},//葰 sui
{2,2669,{pysm::nop,pyym::nop}},//葱 cong
{1,0,{pysm::q,pyym::uan}},//葲 quan
{1,0,{pysm::w,pyym::ei}},//葳 wei
{2,2670,{pysm::nop,pyym::nop}},//葴 zhen
{1,0,{pysm::k,pyym::ui}},//葵 kui
{2,2671,{pysm::nop,pyym::nop}},//葶 ting
{2,2672,{pysm::nop,pyym::nop}},//葷 hun
{1,0,{pysm::x,pyym::i}},//葸 xi
{1,0,{pysm::sh,pyym::i}},//葹 shi
{1,0,{pysm::q,pyym::i}},//葺 qi
{1,0,{pysm::l,pyym::an}},//葻 lan
{1,0,{pysm::z,pyym::ong}},//葼 zong
{1,0,{pysm::y,pyym::ao}},//葽 yao
{1,0,{pysm::y,pyym::uan}},//葾 yuan
{1,0,{pysm::m,pyym::ei}},//葿 mei
{1,0,{pysm::y,pyym::un}},//蒀 yun
{1,0,{pysm::sh,pyym::u}},//蒁 shu
{1,0,{pysm::d,pyym::i}},//蒂 di
{1,0,{pysm::zh,pyym::uan}},//蒃 zhuan
{1,0,{pysm::g,pyym::uan}},//蒄 guan
{1,0,{pysm::r,pyym::an}},//蒅 ran
{1,0,{pysm::x,pyym::ue}},//蒆 xue
{1,0,{pysm::ch,pyym::an}},//蒇 chan
{1,0,{pysm::k,pyym::ai}},//蒈 kai
{1,0,{pysm::k,pyym::ui}},//蒉 kui
{1,0,{pysm::h,pyym::ua}},//蒊 hua
{1,0,{pysm::j,pyym::iang}},//蒋 jiang
{1,0,{pysm::l,pyym::ou}},//蒌 lou
{4,124,{pysm::nop,pyym::nop}},//蒍 wei
{1,0,{pysm::p,pyym::ai}},//蒎 pai
{1,0,{pysm::y,pyym::ou}},//蒏 you
{2,2673,{pysm::nop,pyym::nop}},//蒐 sou
{1,0,{pysm::y,pyym::in}},//蒑 yin
{1,0,{pysm::sh,pyym::i}},//蒒 shi
{1,0,{pysm::ch,pyym::un}},//蒓 chun
{1,0,{pysm::sh,pyym::i}},//蒔 shi
{1,0,{pysm::y,pyym::un}},//蒕 yun
{1,0,{pysm::zh,pyym::en}},//蒖 zhen
{1,0,{pysm::l,pyym::ang}},//蒗 lang
{2,2674,{pysm::nop,pyym::nop}},//蒘 ru
{1,0,{pysm::m,pyym::eng}},//蒙 meng
{1,0,{pysm::l,pyym::i}},//蒚 li
{1,0,{pysm::q,pyym::ue}},//蒛 que
{1,0,{pysm::s,pyym::uan}},//蒜 suan
{2,2675,{pysm::nop,pyym::nop}},//蒝 yuan
{1,0,{pysm::l,pyym::i}},//蒞 li
{1,0,{pysm::j,pyym::u}},//蒟 ju
{1,0,{pysm::x,pyym::i}},//蒠 xi
{2,2676,{pysm::nop,pyym::nop}},//蒡 bang
{1,0,{pysm::ch,pyym::u}},//蒢 chu
{2,2677,{pysm::nop,pyym::nop}},//蒣 xu
{1,0,{pysm::t,pyym::u}},//蒤 tu
{1,0,{pysm::l,pyym::iu}},//蒥 liu
{2,2678,{pysm::nop,pyym::nop}},//蒦 huo
{1,0,{pysm::d,pyym::ian}},//蒧 dian
{1,0,{pysm::q,pyym::ian}},//蒨 qian
{3,643,{pysm::nop,pyym::nop}},//蒩 zu
{1,0,{pysm::p,pyym::o}},//蒪 po
{1,0,{pysm::c,pyym::uo}},//蒫 cuo
{1,0,{pysm::y,pyym::uan}},//蒬 yuan
{1,0,{pysm::ch,pyym::u}},//蒭 chu
{1,0,{pysm::y,pyym::u}},//蒮 yu
{1,0,{pysm::k,pyym::uai}},//蒯 kuai
{1,0,{pysm::p,pyym::an}},//蒰 pan
{1,0,{pysm::p,pyym::u}},//蒱 pu
{2,2679,{pysm::nop,pyym::nop}},//蒲 pu
{1,0,{pysm::n,pyym::a}},//蒳 na
{1,0,{pysm::sh,pyym::uo}},//蒴 shuo
{1,0,{pysm::x,pyym::i}},//蒵 xi
{1,0,{pysm::f,pyym::en}},//蒶 fen
{1,0,{pysm::y,pyym::un}},//蒷 yun
{1,0,{pysm::zh,pyym::eng}},//蒸 zheng
{1,0,{pysm::j,pyym::ian}},//蒹 jian
{1,0,{pysm::j,pyym::i}},//蒺 ji
{1,0,{pysm::r,pyym::uo}},//蒻 ruo
{1,0,{pysm::c,pyym::ang}},//蒼 cang
{1,0,{pysm::nop,pyym::en}},//蒽 en
{1,0,{pysm::m,pyym::i}},//蒾 mi
{2,2680,{pysm::nop,pyym::nop}},//蒿 hao
{1,0,{pysm::s,pyym::un}},//蓀 sun
{2,2681,{pysm::nop,pyym::nop}},//蓁 zhen
{2,2682,{pysm::nop,pyym::nop}},//蓂 ming
{1,0,{pysm::s,pyym::ou}},//蓃 sou
{1,0,{pysm::x,pyym::u}},//蓄 xu
{1,0,{pysm::l,pyym::iu}},//蓅 liu
{1,0,{pysm::x,pyym::i}},//蓆 xi
{1,0,{pysm::g,pyym::u}},//蓇 gu
{1,0,{pysm::l,pyym::ang}},//蓈 lang
{1,0,{pysm::r,pyym::ong}},//蓉 rong
{1,0,{pysm::w,pyym::eng}},//蓊 weng
{2,2683,{pysm::nop,pyym::nop}},//蓋 gai
{1,0,{pysm::c,pyym::uo}},//蓌 cuo
{1,0,{pysm::sh,pyym::i}},//蓍 shi
{1,0,{pysm::t,pyym::ang}},//蓎 tang
{1,0,{pysm::l,pyym::uo}},//蓏 luo
{1,0,{pysm::r,pyym::u}},//蓐 ru
{2,2684,{pysm::nop,pyym::nop}},//蓑 suo
{1,0,{pysm::x,pyym::uan}},//蓒 xuan
{1,0,{pysm::b,pyym::ei}},//蓓 bei
{2,2685,{pysm::nop,pyym::nop}},//蓔 yao
{1,0,{pysm::g,pyym::ui}},//蓕 gui
{1,0,{pysm::b,pyym::i}},//蓖 bi
{1,0,{pysm::z,pyym::ong}},//蓗 zong
{1,0,{pysm::g,pyym::un}},//蓘 gun
{1,0,{pysm::z,pyym::uo}},//蓙 zuo
{1,0,{pysm::t,pyym::iao}},//蓚 tiao
{1,0,{pysm::c,pyym::e}},//蓛 ce
{1,0,{pysm::p,pyym::ei}},//蓜 pei
{2,2686,{pysm::nop,pyym::nop}},//蓝 lan
{1,0,{pysm::d,pyym::an}},//蓞 dan
{1,0,{pysm::j,pyym::i}},//蓟 ji
{1,0,{pysm::l,pyym::i}},//蓠 li
{1,0,{pysm::sh,pyym::en}},//蓡 shen
{1,0,{pysm::l,pyym::ang}},//蓢 lang
{1,0,{pysm::y,pyym::u}},//蓣 yu
{1,0,{pysm::l,pyym::ing}},//蓤 ling
{1,0,{pysm::y,pyym::ing}},//蓥 ying
{1,0,{pysm::m,pyym::o}},//蓦 mo
{3,644,{pysm::nop,pyym::nop}},//蓧 diao
{2,2687,{pysm::nop,pyym::nop}},//蓨 tiao
{1,0,{pysm::m,pyym::ao}},//蓩 mao
{1,0,{pysm::t,pyym::ong}},//蓪 tong
{2,2688,{pysm::nop,pyym::nop}},//蓫 chu
{1,0,{pysm::p,pyym::eng}},//蓬 peng
{1,0,{pysm::nop,pyym::an}},//蓭 an
{1,0,{pysm::l,pyym::ian}},//蓮 lian
{3,645,{pysm::nop,pyym::nop}},//蓯 cong
{1,0,{pysm::x,pyym::i}},//蓰 xi
{1,0,{pysm::p,pyym::ing}},//蓱 ping
{4,125,{pysm::nop,pyym::nop}},//蓲 qiu
{1,0,{pysm::j,pyym::in}},//蓳 jin
{2,2689,{pysm::nop,pyym::nop}},//蓴 chun
{1,0,{pysm::j,pyym::ie}},//蓵 jie
{1,0,{pysm::w,pyym::ei}},//蓶 wei
{1,0,{pysm::t,pyym::ui}},//蓷 tui
{1,0,{pysm::c,pyym::ao}},//蓸 cao
{1,0,{pysm::y,pyym::u}},//蓹 yu
{1,0,{pysm::y,pyym::i}},//蓺 yi
{2,2690,{pysm::nop,pyym::nop}},//蓻 zi
{4,126,{pysm::nop,pyym::nop}},//蓼 liao
{1,0,{pysm::b,pyym::i}},//蓽 bi
{1,0,{pysm::l,pyym::u}},//蓾 lu
{2,2691,{pysm::nop,pyym::nop}},//蓿 xu
{1,0,{pysm::b,pyym::u}},//蔀 bu
{1,0,{pysm::zh,pyym::ang}},//蔁 zhang
{1,0,{pysm::l,pyym::ei}},//蔂 lei
{2,2692,{pysm::nop,pyym::nop}},//蔃 qiang
{1,0,{pysm::m,pyym::an}},//蔄 man
{1,0,{pysm::y,pyym::an}},//蔅 yan
{1,0,{pysm::l,pyym::ing}},//蔆 ling
{2,2693,{pysm::nop,pyym::nop}},//蔇 ji
{2,2694,{pysm::nop,pyym::nop}},//蔈 biao
{1,0,{pysm::g,pyym::un}},//蔉 gun
{1,0,{pysm::h,pyym::an}},//蔊 han
{1,0,{pysm::d,pyym::i}},//蔋 di
{1,0,{pysm::s,pyym::u}},//蔌 su
{2,2695,{pysm::nop,pyym::nop}},//蔍 lu
{1,0,{pysm::sh,pyym::e}},//蔎 she
{1,0,{pysm::sh,pyym::ang}},//蔏 shang
{1,0,{pysm::d,pyym::i}},//蔐 di
{1,0,{pysm::m,pyym::ie}},//蔑 mie
{1,0,{pysm::x,pyym::un}},//蔒 xun
{2,2696,{pysm::nop,pyym::nop}},//蔓 man
{1,0,{pysm::b,pyym::o}},//蔔 bo
{3,646,{pysm::nop,pyym::nop}},//蔕 di
{3,647,{pysm::nop,pyym::nop}},//蔖 cuo
{1,0,{pysm::zh,pyym::e}},//蔗 zhe
{2,2697,{pysm::nop,pyym::nop}},//蔘 shen
{1,0,{pysm::x,pyym::uan}},//蔙 xuan
{2,2698,{pysm::nop,pyym::nop}},//蔚 wei
{1,0,{pysm::h,pyym::u}},//蔛 hu
{1,0,{pysm::nop,pyym::ao}},//蔜 ao
{1,0,{pysm::m,pyym::i}},//蔝 mi
{4,127,{pysm::nop,pyym::nop}},//蔞 lou
{3,648,{pysm::nop,pyym::nop}},//蔟 cu
{1,0,{pysm::zh,pyym::ong}},//蔠 zhong
{3,649,{pysm::nop,pyym::nop}},//蔡 cai
{2,2699,{pysm::nop,pyym::nop}},//蔢 po
{1,0,{pysm::j,pyym::iang}},//蔣 jiang
{1,0,{pysm::m,pyym::i}},//蔤 mi
{1,0,{pysm::c,pyym::ong}},//蔥 cong
{1,0,{pysm::n,pyym::iao}},//蔦 niao
{1,0,{pysm::h,pyym::ui}},//蔧 hui
{2,2700,{pysm::nop,pyym::nop}},//蔨 juan
{1,0,{pysm::y,pyym::in}},//蔩 yin
{2,2701,{pysm::nop,pyym::nop}},//蔪 jian
{2,2702,{pysm::nop,pyym::nop}},//蔫 nian
{1,0,{pysm::sh,pyym::u}},//蔬 shu
{1,0,{pysm::y,pyym::in}},//蔭 yin
{1,0,{pysm::g,pyym::uo}},//蔮 guo
{1,0,{pysm::ch,pyym::en}},//蔯 chen
{1,0,{pysm::h,pyym::u}},//蔰 hu
{1,0,{pysm::sh,pyym::a}},//蔱 sha
{1,0,{pysm::k,pyym::ou}},//蔲 kou
{1,0,{pysm::q,pyym::ian}},//蔳 qian
{1,0,{pysm::m,pyym::a}},//蔴 ma
{2,2703,{pysm::nop,pyym::nop}},//蔵 zang
{1,0,{pysm::z,pyym::e}},//蔶 ze
{1,0,{pysm::q,pyym::iang}},//蔷 qiang
{1,0,{pysm::d,pyym::ou}},//蔸 dou
{1,0,{pysm::l,pyym::ian}},//蔹 lian
{1,0,{pysm::l,pyym::in}},//蔺 lin
{1,0,{pysm::k,pyym::ou}},//蔻 kou
{1,0,{pysm::nop,pyym::ai}},//蔼 ai
{3,650,{pysm::nop,pyym::nop}},//蔽 bi
{1,0,{pysm::l,pyym::i}},//蔾 li
{1,0,{pysm::w,pyym::ei}},//蔿 wei
{1,0,{pysm::j,pyym::i}},//蕀 ji
{3,651,{pysm::nop,pyym::nop}},//蕁 qian
{1,0,{pysm::sh,pyym::eng}},//蕂 sheng
{3,652,{pysm::nop,pyym::nop}},//蕃 fan
{1,0,{pysm::m,pyym::eng}},//蕄 meng
{1,0,{pysm::nop,pyym::ou}},//蕅 ou
{1,0,{pysm::ch,pyym::an}},//蕆 chan
{1,0,{pysm::d,pyym::ian}},//蕇 dian
{2,2704,{pysm::nop,pyym::nop}},//蕈 xun
{2,2705,{pysm::nop,pyym::nop}},//蕉 jiao
{2,2706,{pysm::nop,pyym::nop}},//蕊 rui
{1,0,{pysm::r,pyym::ui}},//蕋 rui
{1,0,{pysm::l,pyym::ei}},//蕌 lei
{1,0,{pysm::y,pyym::u}},//蕍 yu
{2,2707,{pysm::nop,pyym::nop}},//蕎 qiao
{1,0,{pysm::ch,pyym::u}},//蕏 chu
{1,0,{pysm::h,pyym::ua}},//蕐 hua
{1,0,{pysm::j,pyym::ian}},//蕑 jian
{1,0,{pysm::m,pyym::ai}},//蕒 mai
{1,0,{pysm::y,pyym::un}},//蕓 yun
{1,0,{pysm::b,pyym::ao}},//蕔 bao
{1,0,{pysm::y,pyym::ou}},//蕕 you
{1,0,{pysm::q,pyym::u}},//蕖 qu
{1,0,{pysm::l,pyym::u}},//蕗 lu
{2,2708,{pysm::nop,pyym::nop}},//蕘 rao
{1,0,{pysm::h,pyym::ui}},//蕙 hui
{1,0,{pysm::nop,pyym::e}},//蕚 e
{1,0,{pysm::t,pyym::i}},//蕛 ti
{1,0,{pysm::f,pyym::ei}},//蕜 fei
{2,2709,{pysm::nop,pyym::nop}},//蕝 jue
{3,653,{pysm::nop,pyym::nop}},//蕞 zui
{2,2710,{pysm::nop,pyym::nop}},//蕟 fa
{1,0,{pysm::r,pyym::u}},//蕠 ru
{2,2711,{pysm::nop,pyym::nop}},//蕡 fen
{2,2712,{pysm::nop,pyym::nop}},//蕢 kui
{1,0,{pysm::sh,pyym::un}},//蕣 shun
{1,0,{pysm::r,pyym::ui}},//蕤 rui
{1,0,{pysm::y,pyym::a}},//蕥 ya
{1,0,{pysm::x,pyym::u}},//蕦 xu
{1,0,{pysm::f,pyym::u}},//蕧 fu
{1,0,{pysm::j,pyym::ue}},//蕨 jue
{2,2713,{pysm::nop,pyym::nop}},//蕩 dang
{1,0,{pysm::w,pyym::u}},//蕪 wu
{1,0,{pysm::d,pyym::ong}},//蕫 dong
{1,0,{pysm::s,pyym::i}},//蕬 si
{1,0,{pysm::x,pyym::iao}},//蕭 xiao
{1,0,{pysm::x,pyym::i}},//蕮 xi
{1,0,{pysm::l,pyym::ong}},//蕯 long
{2,2714,{pysm::nop,pyym::nop}},//蕰 wen
{1,0,{pysm::sh,pyym::ao}},//蕱 shao
{1,0,{pysm::q,pyym::i}},//蕲 qi
{1,0,{pysm::j,pyym::ian}},//蕳 jian
{1,0,{pysm::y,pyym::un}},//蕴 yun
{1,0,{pysm::s,pyym::un}},//蕵 sun
{1,0,{pysm::l,pyym::ing}},//蕶 ling
{1,0,{pysm::y,pyym::u}},//蕷 yu
{1,0,{pysm::x,pyym::ia}},//蕸 xia
{2,2715,{pysm::nop,pyym::nop}},//蕹 weng
{2,2716,{pysm::nop,pyym::nop}},//蕺 ji
{1,0,{pysm::h,pyym::ong}},//蕻 hong
{1,0,{pysm::s,pyym::i}},//蕼 si
{1,0,{pysm::n,pyym::ong}},//蕽 nong
{1,0,{pysm::l,pyym::ei}},//蕾 lei
{1,0,{pysm::x,pyym::uan}},//蕿 xuan
{1,0,{pysm::y,pyym::un}},//薀 yun
{2,2717,{pysm::nop,pyym::nop}},//薁 yu
{2,2718,{pysm::nop,pyym::nop}},//薂 xi
{1,0,{pysm::h,pyym::ao}},//薃 hao
{3,654,{pysm::nop,pyym::nop}},//薄 bao
{1,0,{pysm::h,pyym::ao}},//薅 hao
{1,0,{pysm::nop,pyym::ai}},//薆 ai
{1,0,{pysm::w,pyym::ei}},//薇 wei
{1,0,{pysm::h,pyym::ui}},//薈 hui
{1,0,{pysm::h,pyym::ui}},//薉 hui
{1,0,{pysm::j,pyym::i}},//薊 ji
{2,2719,{pysm::nop,pyym::nop}},//薋 ci
{1,0,{pysm::x,pyym::iang}},//薌 xiang
{2,2720,{pysm::nop,pyym::nop}},//薍 wan
{1,0,{pysm::m,pyym::ie}},//薎 mie
{1,0,{pysm::y,pyym::i}},//薏 yi
{1,0,{pysm::l,pyym::eng}},//薐 leng
{1,0,{pysm::j,pyym::iang}},//薑 jiang
{1,0,{pysm::c,pyym::an}},//薒 can
{1,0,{pysm::sh,pyym::en}},//薓 shen
{2,2721,{pysm::nop,pyym::nop}},//薔 qiang
{1,0,{pysm::l,pyym::ian}},//薕 lian
{1,0,{pysm::k,pyym::e}},//薖 ke
{1,0,{pysm::y,pyym::uan}},//薗 yuan
{1,0,{pysm::d,pyym::a}},//薘 da
{2,2722,{pysm::nop,pyym::nop}},//薙 ti
{1,0,{pysm::t,pyym::ang}},//薚 tang
{1,0,{pysm::x,pyym::ue}},//薛 xue
{4,128,{pysm::nop,pyym::nop}},//薜 bi
{1,0,{pysm::zh,pyym::an}},//薝 zhan
{1,0,{pysm::s,pyym::un}},//薞 sun
{4,129,{pysm::nop,pyym::nop}},//薟 xian
{1,0,{pysm::f,pyym::an}},//薠 fan
{1,0,{pysm::d,pyym::ing}},//薡 ding
{1,0,{pysm::x,pyym::ie}},//薢 xie
{1,0,{pysm::g,pyym::u}},//薣 gu
{1,0,{pysm::x,pyym::ie}},//薤 xie
{2,2723,{pysm::nop,pyym::nop}},//薥 shu
{1,0,{pysm::j,pyym::ian}},//薦 jian
{2,2724,{pysm::nop,pyym::nop}},//薧 hao
{1,0,{pysm::h,pyym::ong}},//薨 hong
{1,0,{pysm::s,pyym::a}},//薩 sa
{1,0,{pysm::x,pyym::in}},//薪 xin
{1,0,{pysm::x,pyym::un}},//薫 xun
{1,0,{pysm::y,pyym::ao}},//薬 yao
{1,0,{pysm::b,pyym::ai}},//薭 bai
{1,0,{pysm::s,pyym::ou}},//薮 sou
{1,0,{pysm::sh,pyym::u}},//薯 shu
{1,0,{pysm::x,pyym::un}},//薰 xun
{1,0,{pysm::d,pyym::ui}},//薱 dui
{1,0,{pysm::p,pyym::in}},//薲 pin
{2,2725,{pysm::nop,pyym::nop}},//薳 wei
{1,0,{pysm::n,pyym::ing}},//薴 ning
{3,655,{pysm::nop,pyym::nop}},//薵 chou
{2,2726,{pysm::nop,pyym::nop}},//薶 mai
{1,0,{pysm::r,pyym::u}},//薷 ru
{1,0,{pysm::p,pyym::iao}},//薸 piao
{1,0,{pysm::t,pyym::ai}},//薹 tai
{3,656,{pysm::nop,pyym::nop}},//薺 ji
{1,0,{pysm::z,pyym::ao}},//薻 zao
{1,0,{pysm::ch,pyym::en}},//薼 chen
{1,0,{pysm::zh,pyym::en}},//薽 zhen
{1,0,{pysm::nop,pyym::er}},//薾 er
{1,0,{pysm::n,pyym::i}},//薿 ni
{1,0,{pysm::y,pyym::ing}},//藀 ying
{1,0,{pysm::g,pyym::ao}},//藁 gao
{1,0,{pysm::c,pyym::ong}},//藂 cong
{3,657,{pysm::nop,pyym::nop}},//藃 xiao
{1,0,{pysm::q,pyym::i}},//藄 qi
{1,0,{pysm::f,pyym::a}},//藅 fa
{1,0,{pysm::j,pyym::ian}},//藆 jian
{2,2727,{pysm::nop,pyym::nop}},//藇 xu
{1,0,{pysm::k,pyym::ui}},//藈 kui
{2,2728,{pysm::nop,pyym::nop}},//藉 ji
{1,0,{pysm::b,pyym::ian}},//藊 bian
{3,658,{pysm::nop,pyym::nop}},//藋 diao
{1,0,{pysm::m,pyym::i}},//藌 mi
{2,2729,{pysm::nop,pyym::nop}},//藍 lan
{1,0,{pysm::j,pyym::in}},//藎 jin
{2,2730,{pysm::nop,pyym::nop}},//藏 cang
{2,2731,{pysm::nop,pyym::nop}},//藐 miao
{1,0,{pysm::q,pyym::iong}},//藑 qiong
{1,0,{pysm::q,pyym::ie}},//藒 qie
{1,0,{pysm::x,pyym::ian}},//藓 xian
{1,0,{pysm::l,pyym::iao}},//藔 liao
{1,0,{pysm::nop,pyym::ou}},//藕 ou
{2,2732,{pysm::nop,pyym::nop}},//藖 xian
{1,0,{pysm::s,pyym::u}},//藗 su
{1,0,{pysm::l,pyym::v}},//藘 lü
{1,0,{pysm::y,pyym::i}},//藙 yi
{1,0,{pysm::x,pyym::u}},//藚 xu
{1,0,{pysm::x,pyym::ie}},//藛 xie
{1,0,{pysm::l,pyym::i}},//藜 li
{1,0,{pysm::y,pyym::i}},//藝 yi
{1,0,{pysm::l,pyym::a}},//藞 la
{1,0,{pysm::l,pyym::ei}},//藟 lei
{1,0,{pysm::j,pyym::iao}},//藠 jiao
{1,0,{pysm::d,pyym::i}},//藡 di
{1,0,{pysm::zh,pyym::i}},//藢 zhi
{1,0,{pysm::b,pyym::ei}},//藣 bei
{1,0,{pysm::t,pyym::eng}},//藤 teng
{3,659,{pysm::nop,pyym::nop}},//藥 yao
{1,0,{pysm::m,pyym::o}},//藦 mo
{1,0,{pysm::h,pyym::uan}},//藧 huan
{2,2733,{pysm::nop,pyym::nop}},//藨 biao
{1,0,{pysm::f,pyym::an}},//藩 fan
{3,660,{pysm::nop,pyym::nop}},//藪 sou
{1,0,{pysm::t,pyym::an}},//藫 tan
{1,0,{pysm::t,pyym::ui}},//藬 tui
{1,0,{pysm::q,pyym::iong}},//藭 qiong
{1,0,{pysm::q,pyym::iao}},//藮 qiao
{1,0,{pysm::w,pyym::ei}},//藯 wei
{1,0,{pysm::l,pyym::iu}},//藰 liu
{1,0,{pysm::h,pyym::ui}},//藱 hui
{1,0,{pysm::nop,pyym::ou}},//藲 ou
{1,0,{pysm::g,pyym::ao}},//藳 gao
{2,2734,{pysm::nop,pyym::nop}},//藴 yun
{1,0,{pysm::b,pyym::ao}},//藵 bao
{1,0,{pysm::l,pyym::i}},//藶 li
{2,2735,{pysm::nop,pyym::nop}},//藷 shu
{3,661,{pysm::nop,pyym::nop}},//藸 chu
{1,0,{pysm::nop,pyym::ai}},//藹 ai
{1,0,{pysm::l,pyym::in}},//藺 lin
{1,0,{pysm::z,pyym::ao}},//藻 zao
{1,0,{pysm::x,pyym::uan}},//藼 xuan
{1,0,{pysm::q,pyym::in}},//藽 qin
{1,0,{pysm::l,pyym::ai}},//藾 lai
{2,2736,{pysm::nop,pyym::nop}},//藿 huo
{2,2737,{pysm::nop,pyym::nop}},//蘀 tuo
{2,2738,{pysm::nop,pyym::nop}},//蘁 wu
{1,0,{pysm::r,pyym::ui}},//蘂 rui
{1,0,{pysm::r,pyym::ui}},//蘃 rui
{3,662,{pysm::nop,pyym::nop}},//蘄 qi
{1,0,{pysm::h,pyym::eng}},//蘅 heng
{1,0,{pysm::l,pyym::u}},//蘆 lu
{1,0,{pysm::s,pyym::u}},//蘇 su
{1,0,{pysm::t,pyym::ui}},//蘈 tui
{2,2739,{pysm::nop,pyym::nop}},//蘉 meng
{1,0,{pysm::y,pyym::un}},//蘊 yun
{2,2740,{pysm::nop,pyym::nop}},//蘋 ping
{1,0,{pysm::y,pyym::u}},//蘌 yu
{1,0,{pysm::x,pyym::un}},//蘍 xun
{1,0,{pysm::j,pyym::i}},//蘎 ji
{1,0,{pysm::j,pyym::iong}},//蘏 jiong
{1,0,{pysm::x,pyym::uan}},//蘐 xuan
{1,0,{pysm::m,pyym::o}},//蘑 mo
{1,0,{pysm::q,pyym::iu}},//蘒 qiu
{1,0,{pysm::s,pyym::u}},//蘓 su
{1,0,{pysm::j,pyym::iong}},//蘔 jiong
{1,0,{pysm::p,pyym::eng}},//蘕 peng
{2,2741,{pysm::nop,pyym::nop}},//蘖 nie
{2,2742,{pysm::nop,pyym::nop}},//蘗 bo
{3,663,{pysm::nop,pyym::nop}},//蘘 rang
{1,0,{pysm::y,pyym::i}},//蘙 yi
{1,0,{pysm::x,pyym::ian}},//蘚 xian
{1,0,{pysm::y,pyym::u}},//蘛 yu
{1,0,{pysm::j,pyym::u}},//蘜 ju
{1,0,{pysm::l,pyym::ian}},//蘝 lian
{2,2743,{pysm::nop,pyym::nop}},//蘞 lian
{1,0,{pysm::y,pyym::in}},//蘟 yin
{1,0,{pysm::q,pyym::iang}},//蘠 qiang
{1,0,{pysm::y,pyym::ing}},//蘡 ying
{1,0,{pysm::l,pyym::ong}},//蘢 long
{1,0,{pysm::t,pyym::ou}},//蘣 tou
{1,0,{pysm::h,pyym::ua}},//蘤 hua
{1,0,{pysm::y,pyym::ue}},//蘥 yue
{1,0,{pysm::l,pyym::ing}},//蘦 ling
{2,2744,{pysm::nop,pyym::nop}},//蘧 qu
{1,0,{pysm::y,pyym::ao}},//蘨 yao
{1,0,{pysm::f,pyym::an}},//蘩 fan
{1,0,{pysm::m,pyym::ei}},//蘪 mei
{2,2745,{pysm::nop,pyym::nop}},//蘫 han
{3,664,{pysm::nop,pyym::nop}},//蘬 kui
{1,0,{pysm::l,pyym::an}},//蘭 lan
{1,0,{pysm::j,pyym::i}},//蘮 ji
{1,0,{pysm::d,pyym::ang}},//蘯 dang
{1,0,{pysm::m,pyym::an}},//蘰 man
{1,0,{pysm::l,pyym::ei}},//蘱 lei
{1,0,{pysm::l,pyym::ei}},//蘲 lei
{1,0,{pysm::h,pyym::ui}},//蘳 hui
{2,2746,{pysm::nop,pyym::nop}},//蘴 feng
{1,0,{pysm::zh,pyym::i}},//蘵 zhi
{1,0,{pysm::w,pyym::ei}},//蘶 wei
{1,0,{pysm::k,pyym::ui}},//蘷 kui
{1,0,{pysm::zh,pyym::an}},//蘸 zhan
{1,0,{pysm::h,pyym::uai}},//蘹 huai
{1,0,{pysm::l,pyym::i}},//蘺 li
{1,0,{pysm::j,pyym::i}},//蘻 ji
{1,0,{pysm::m,pyym::i}},//蘼 mi
{1,0,{pysm::l,pyym::ei}},//蘽 lei
{1,0,{pysm::h,pyym::uai}},//蘾 huai
{1,0,{pysm::l,pyym::uo}},//蘿 luo
{1,0,{pysm::j,pyym::i}},//虀 ji
{1,0,{pysm::k,pyym::ui}},//虁 kui
{1,0,{pysm::l,pyym::u}},//虂 lu
{1,0,{pysm::j,pyym::ian}},//虃 jian
{1,0,{pysm::s,pyym::a}},//虄 sa
{1,0,{pysm::t,pyym::eng}},//虅 teng
{1,0,{pysm::l,pyym::ei}},//虆 lei
{1,0,{pysm::q,pyym::uan}},//虇 quan
{1,0,{pysm::x,pyym::iao}},//虈 xiao
{1,0,{pysm::y,pyym::i}},//虉 yi
{1,0,{pysm::l,pyym::uan}},//虊 luan
{1,0,{pysm::m,pyym::en}},//虋 men
{1,0,{pysm::b,pyym::ie}},//虌 bie
{1,0,{pysm::h,pyym::u}},//虍 hu
{1,0,{pysm::h,pyym::u}},//虎 hu
{1,0,{pysm::l,pyym::u}},//虏 lu
{1,0,{pysm::n,pyym::ve}},//虐 nüe
{2,2747,{pysm::nop,pyym::nop}},//虑 lü
{4,130,{pysm::nop,pyym::nop}},//虒 si
{1,0,{pysm::x,pyym::iao}},//虓 xiao
{1,0,{pysm::q,pyym::ian}},//虔 qian
{2,2748,{pysm::nop,pyym::nop}},//處 chu
{1,0,{pysm::h,pyym::u}},//虖 hu
{1,0,{pysm::x,pyym::u}},//虗 xu
{1,0,{pysm::c,pyym::uo}},//虘 cuo
{1,0,{pysm::f,pyym::u}},//虙 fu
{1,0,{pysm::x,pyym::u}},//虚 xu
{1,0,{pysm::x,pyym::u}},//虛 xu
{1,0,{pysm::l,pyym::u}},//虜 lu
{1,0,{pysm::h,pyym::u}},//虝 hu
{1,0,{pysm::y,pyym::u}},//虞 yu
{1,0,{pysm::h,pyym::ao}},//號 hao
{2,2749,{pysm::nop,pyym::nop}},//虠 jiao
{1,0,{pysm::j,pyym::u}},//虡 ju
{1,0,{pysm::g,pyym::uo}},//虢 guo
{1,0,{pysm::b,pyym::ao}},//虣 bao
{1,0,{pysm::y,pyym::an}},//虤 yan
{1,0,{pysm::zh,pyym::an}},//虥 zhan
{1,0,{pysm::zh,pyym::an}},//虦 zhan
{1,0,{pysm::k,pyym::ui}},//虧 kui
{1,0,{pysm::b,pyym::in}},//虨 bin
{2,2750,{pysm::nop,pyym::nop}},//虩 xi
{1,0,{pysm::sh,pyym::u}},//虪 shu
{2,2751,{pysm::nop,pyym::nop}},//虫 chong
{1,0,{pysm::q,pyym::iu}},//虬 qiu
{2,2752,{pysm::nop,pyym::nop}},//虭 diao
{1,0,{pysm::j,pyym::i}},//虮 ji
{1,0,{pysm::q,pyym::iu}},//虯 qiu
{2,2753,{pysm::nop,pyym::nop}},//虰 ding
{1,0,{pysm::sh,pyym::i}},//虱 shi
{1,0,{pysm::x,pyym::ia}},//虲 xia
{1,0,{pysm::j,pyym::ue}},//虳 jue
{1,0,{pysm::zh,pyym::e}},//虴 zhe
{2,2754,{pysm::nop,pyym::nop}},//虵 she
{1,0,{pysm::y,pyym::u}},//虶 yu
{2,2755,{pysm::nop,pyym::nop}},//虷 han
{1,0,{pysm::z,pyym::i}},//虸 zi
{3,665,{pysm::nop,pyym::nop}},//虹 hong
{1,0,{pysm::h,pyym::ui}},//虺 hui
{1,0,{pysm::m,pyym::eng}},//虻 meng
{1,0,{pysm::g,pyym::e}},//虼 ge
{1,0,{pysm::s,pyym::ui}},//虽 sui
{2,2756,{pysm::nop,pyym::nop}},//虾 xia
{1,0,{pysm::ch,pyym::ai}},//虿 chai
{1,0,{pysm::sh,pyym::i}},//蚀 shi
{1,0,{pysm::y,pyym::i}},//蚁 yi
{1,0,{pysm::m,pyym::a}},//蚂 ma
{1,0,{pysm::x,pyym::iang}},//蚃 xiang
{2,2757,{pysm::nop,pyym::nop}},//蚄 fang
{1,0,{pysm::nop,pyym::e}},//蚅 e
{1,0,{pysm::b,pyym::a}},//蚆 ba
{1,0,{pysm::ch,pyym::i}},//蚇 chi
{1,0,{pysm::q,pyym::ian}},//蚈 qian
{1,0,{pysm::w,pyym::en}},//蚉 wen
{1,0,{pysm::w,pyym::en}},//蚊 wen
{1,0,{pysm::r,pyym::ui}},//蚋 rui
{4,131,{pysm::nop,pyym::nop}},//蚌 bang
{1,0,{pysm::p,pyym::i}},//蚍 pi
{1,0,{pysm::y,pyym::ue}},//蚎 yue
{1,0,{pysm::y,pyym::ue}},//蚏 yue
{1,0,{pysm::j,pyym::un}},//蚐 jun
{1,0,{pysm::q,pyym::i}},//蚑 qi
{1,0,{pysm::t,pyym::ong}},//蚒 tong
{1,0,{pysm::y,pyym::in}},//蚓 yin
{2,2758,{pysm::nop,pyym::nop}},//蚔 qi
{2,2759,{pysm::nop,pyym::nop}},//蚕 can
{2,2760,{pysm::nop,pyym::nop}},//蚖 yuan
{2,2761,{pysm::nop,pyym::nop}},//蚗 jue
{2,2762,{pysm::nop,pyym::nop}},//蚘 hui
{2,2763,{pysm::nop,pyym::nop}},//蚙 qin
{1,0,{pysm::q,pyym::i}},//蚚 qi
{1,0,{pysm::zh,pyym::ong}},//蚛 zhong
{1,0,{pysm::y,pyym::a}},//蚜 ya
{2,2764,{pysm::nop,pyym::nop}},//蚝 hao
{1,0,{pysm::m,pyym::u}},//蚞 mu
{1,0,{pysm::w,pyym::ang}},//蚟 wang
{1,0,{pysm::f,pyym::en}},//蚠 fen
{1,0,{pysm::f,pyym::en}},//蚡 fen
{1,0,{pysm::h,pyym::ang}},//蚢 hang
{2,2765,{pysm::nop,pyym::nop}},//蚣 gong
{2,2766,{pysm::nop,pyym::nop}},//蚤 zao
{1,0,{pysm::f,pyym::u}},//蚥 fu
{1,0,{pysm::r,pyym::an}},//蚦 ran
{1,0,{pysm::j,pyym::ie}},//蚧 jie
{1,0,{pysm::f,pyym::u}},//蚨 fu
{1,0,{pysm::ch,pyym::i}},//蚩 chi
{1,0,{pysm::d,pyym::ou}},//蚪 dou
{2,2767,{pysm::nop,pyym::nop}},//蚫 bao
{1,0,{pysm::x,pyym::ian}},//蚬 xian
{1,0,{pysm::n,pyym::i}},//蚭 ni
{1,0,{pysm::d,pyym::ai}},//蚮 dai
{1,0,{pysm::q,pyym::iu}},//蚯 qiu
{2,2768,{pysm::nop,pyym::nop}},//蚰 you
{1,0,{pysm::zh,pyym::a}},//蚱 zha
{1,0,{pysm::p,pyym::ing}},//蚲 ping
{2,2769,{pysm::nop,pyym::nop}},//蚳 chi
{2,2770,{pysm::nop,pyym::nop}},//蚴 you
{2,2771,{pysm::nop,pyym::nop}},//蚵 he
{1,0,{pysm::h,pyym::an}},//蚶 han
{1,0,{pysm::j,pyym::u}},//蚷 ju
{1,0,{pysm::l,pyym::i}},//蚸 li
{1,0,{pysm::f,pyym::u}},//蚹 fu
{2,2772,{pysm::nop,pyym::nop}},//蚺 ran
{1,0,{pysm::zh,pyym::a}},//蚻 zha
{3,666,{pysm::nop,pyym::nop}},//蚼 gou
{1,0,{pysm::p,pyym::i}},//蚽 pi
{2,2773,{pysm::nop,pyym::nop}},//蚾 pi
{1,0,{pysm::x,pyym::ian}},//蚿 xian
{1,0,{pysm::zh,pyym::u}},//蛀 zhu
{1,0,{pysm::d,pyym::iao}},//蛁 diao
{1,0,{pysm::b,pyym::ie}},//蛂 bie
{1,0,{pysm::b,pyym::ing}},//蛃 bing
{1,0,{pysm::g,pyym::u}},//蛄 gu
{1,0,{pysm::zh,pyym::an}},//蛅 zhan
{2,2774,{pysm::nop,pyym::nop}},//蛆 qu
{4,132,{pysm::nop,pyym::nop}},//蛇 she
{1,0,{pysm::t,pyym::ie}},//蛈 tie
{1,0,{pysm::l,pyym::ing}},//蛉 ling
{1,0,{pysm::g,pyym::u}},//蛊 gu
{1,0,{pysm::d,pyym::an}},//蛋 dan
{1,0,{pysm::g,pyym::u}},//蛌 gu
{1,0,{pysm::y,pyym::ing}},//蛍 ying
{1,0,{pysm::l,pyym::i}},//蛎 li
{1,0,{pysm::ch,pyym::eng}},//蛏 cheng
{1,0,{pysm::q,pyym::u}},//蛐 qu
{2,2775,{pysm::nop,pyym::nop}},//蛑 mou
{2,2776,{pysm::nop,pyym::nop}},//蛒 ge
{1,0,{pysm::c,pyym::i}},//蛓 ci
{1,0,{pysm::h,pyym::ui}},//蛔 hui
{1,0,{pysm::h,pyym::ui}},//蛕 hui
{2,2777,{pysm::nop,pyym::nop}},//蛖 mang
{1,0,{pysm::f,pyym::u}},//蛗 fu
{1,0,{pysm::y,pyym::ang}},//蛘 yang
{2,2778,{pysm::nop,pyym::nop}},//蛙 wa
{1,0,{pysm::l,pyym::ie}},//蛚 lie
{1,0,{pysm::zh,pyym::u}},//蛛 zhu
{1,0,{pysm::y,pyym::i}},//蛜 yi
{1,0,{pysm::x,pyym::ian}},//蛝 xian
{2,2779,{pysm::nop,pyym::nop}},//蛞 kuo
{1,0,{pysm::j,pyym::iao}},//蛟 jiao
{1,0,{pysm::l,pyym::i}},//蛠 li
{2,2780,{pysm::nop,pyym::nop}},//蛡 yi
{1,0,{pysm::p,pyym::ing}},//蛢 ping
{3,667,{pysm::nop,pyym::nop}},//蛣 qi
{3,668,{pysm::nop,pyym::nop}},//蛤 ha
{1,0,{pysm::sh,pyym::e}},//蛥 she
{1,0,{pysm::y,pyym::i}},//蛦 yi
{1,0,{pysm::w,pyym::ang}},//蛧 wang
{1,0,{pysm::m,pyym::o}},//蛨 mo
{2,2781,{pysm::nop,pyym::nop}},//蛩 qiong
{2,2782,{pysm::nop,pyym::nop}},//蛪 qie
{1,0,{pysm::g,pyym::ui}},//蛫 gui
{1,0,{pysm::q,pyym::iong}},//蛬 qiong
{1,0,{pysm::zh,pyym::i}},//蛭 zhi
{1,0,{pysm::m,pyym::an}},//蛮 man
{1,0,{pysm::l,pyym::ao}},//蛯 lao
{1,0,{pysm::zh,pyym::e}},//蛰 zhe
{1,0,{pysm::j,pyym::ia}},//蛱 jia
{1,0,{pysm::n,pyym::ao}},//蛲 nao
{1,0,{pysm::s,pyym::i}},//蛳 si
{1,0,{pysm::q,pyym::i}},//蛴 qi
{1,0,{pysm::x,pyym::ing}},//蛵 xing
{1,0,{pysm::j,pyym::ie}},//蛶 jie
{1,0,{pysm::q,pyym::iu}},//蛷 qiu
{2,2783,{pysm::nop,pyym::nop}},//蛸 shao
{1,0,{pysm::y,pyym::ong}},//蛹 yong
{1,0,{pysm::j,pyym::ia}},//蛺 jia
{1,0,{pysm::t,pyym::ui}},//蛻 tui
{1,0,{pysm::ch,pyym::e}},//蛼 che
{1,0,{pysm::b,pyym::ei}},//蛽 bei
{2,2784,{pysm::nop,pyym::nop}},//蛾 e
{1,0,{pysm::h,pyym::an}},//蛿 han
{1,0,{pysm::sh,pyym::u}},//蜀 shu
{1,0,{pysm::x,pyym::uan}},//蜁 xuan
{1,0,{pysm::f,pyym::eng}},//蜂 feng
{1,0,{pysm::sh,pyym::en}},//蜃 shen
{2,2785,{pysm::nop,pyym::nop}},//蜄 shen
{2,2786,{pysm::nop,pyym::nop}},//蜅 fu
{1,0,{pysm::x,pyym::ian}},//蜆 xian
{1,0,{pysm::zh,pyym::e}},//蜇 zhe
{1,0,{pysm::w,pyym::u}},//蜈 wu
{1,0,{pysm::f,pyym::u}},//蜉 fu
{1,0,{pysm::l,pyym::i}},//蜊 li
{2,2787,{pysm::nop,pyym::nop}},//蜋 lang
{1,0,{pysm::b,pyym::i}},//蜌 bi
{2,2788,{pysm::nop,pyym::nop}},//蜍 chu
{2,2789,{pysm::nop,pyym::nop}},//蜎 yuan
{1,0,{pysm::y,pyym::ou}},//蜏 you
{1,0,{pysm::j,pyym::ie}},//蜐 jie
{1,0,{pysm::d,pyym::an}},//蜑 dan
{2,2790,{pysm::nop,pyym::nop}},//蜒 yan
{2,2791,{pysm::nop,pyym::nop}},//蜓 ting
{1,0,{pysm::d,pyym::ian}},//蜔 dian
{2,2792,{pysm::nop,pyym::nop}},//蜕 tui
{1,0,{pysm::h,pyym::ui}},//蜖 hui
{1,0,{pysm::w,pyym::o}},//蜗 wo
{1,0,{pysm::zh,pyym::i}},//蜘 zhi
{1,0,{pysm::s,pyym::ong}},//蜙 song
{3,669,{pysm::nop,pyym::nop}},//蜚 fei
{1,0,{pysm::j,pyym::u}},//蜛 ju
{1,0,{pysm::m,pyym::i}},//蜜 mi
{1,0,{pysm::q,pyym::i}},//蜝 qi
{1,0,{pysm::q,pyym::i}},//蜞 qi
{1,0,{pysm::y,pyym::u}},//蜟 yu
{1,0,{pysm::j,pyym::un}},//蜠 jun
{4,133,{pysm::nop,pyym::nop}},//蜡 la
{1,0,{pysm::m,pyym::eng}},//蜢 meng
{1,0,{pysm::q,pyym::iang}},//蜣 qiang
{2,2793,{pysm::nop,pyym::nop}},//蜤 si
{1,0,{pysm::x,pyym::i}},//蜥 xi
{1,0,{pysm::l,pyym::un}},//蜦 lun
{1,0,{pysm::l,pyym::i}},//蜧 li
{1,0,{pysm::d,pyym::ie}},//蜨 die
{2,2794,{pysm::nop,pyym::nop}},//蜩 tiao
{1,0,{pysm::t,pyym::ao}},//蜪 tao
{1,0,{pysm::k,pyym::un}},//蜫 kun
{1,0,{pysm::h,pyym::an}},//蜬 han
{1,0,{pysm::h,pyym::an}},//蜭 han
{2,2795,{pysm::nop,pyym::nop}},//蜮 yu
{1,0,{pysm::b,pyym::ang}},//蜯 bang
{1,0,{pysm::f,pyym::ei}},//蜰 fei
{2,2796,{pysm::nop,pyym::nop}},//蜱 pi
{1,0,{pysm::w,pyym::ei}},//蜲 wei
{2,2797,{pysm::nop,pyym::nop}},//蜳 dun
{2,2798,{pysm::nop,pyym::nop}},//蜴 yi
{2,2799,{pysm::nop,pyym::nop}},//蜵 yuan
{1,0,{pysm::s,pyym::uo}},//蜶 suo
{2,2800,{pysm::nop,pyym::nop}},//蜷 quan
{1,0,{pysm::q,pyym::ian}},//蜸 qian
{2,2801,{pysm::nop,pyym::nop}},//蜹 rui
{1,0,{pysm::n,pyym::i}},//蜺 ni
{2,2802,{pysm::nop,pyym::nop}},//蜻 qing
{2,2803,{pysm::nop,pyym::nop}},//蜼 wei
{1,0,{pysm::l,pyym::iang}},//蜽 liang
{2,2804,{pysm::nop,pyym::nop}},//蜾 guo
{1,0,{pysm::w,pyym::an}},//蜿 wan
{1,0,{pysm::d,pyym::ong}},//蝀 dong
{1,0,{pysm::nop,pyym::e}},//蝁 e
{1,0,{pysm::b,pyym::an}},//蝂 ban
{2,2805,{pysm::nop,pyym::nop}},//蝃 di
{1,0,{pysm::w,pyym::ang}},//蝄 wang
{1,0,{pysm::c,pyym::an}},//蝅 can
{1,0,{pysm::y,pyym::ang}},//蝆 yang
{1,0,{pysm::y,pyym::ing}},//蝇 ying
{1,0,{pysm::g,pyym::uo}},//蝈 guo
{1,0,{pysm::ch,pyym::an}},//蝉 chan
{1,0,{pysm::d,pyym::ing}},//蝊 ding
{1,0,{pysm::l,pyym::a}},//蝋 la
{1,0,{pysm::k,pyym::e}},//蝌 ke
{2,2806,{pysm::nop,pyym::nop}},//蝍 jie
{2,2807,{pysm::nop,pyym::nop}},//蝎 xie
{1,0,{pysm::t,pyym::ing}},//蝏 ting
{1,0,{pysm::m,pyym::ao}},//蝐 mao
{2,2808,{pysm::nop,pyym::nop}},//蝑 xu
{1,0,{pysm::m,pyym::ian}},//蝒 mian
{1,0,{pysm::y,pyym::u}},//蝓 yu
{1,0,{pysm::j,pyym::ie}},//蝔 jie
{3,670,{pysm::nop,pyym::nop}},//蝕 shi
{1,0,{pysm::x,pyym::uan}},//蝖 xuan
{1,0,{pysm::h,pyym::uang}},//蝗 huang
{1,0,{pysm::y,pyym::an}},//蝘 yan
{2,2809,{pysm::nop,pyym::nop}},//蝙 bian
{2,2810,{pysm::nop,pyym::nop}},//蝚 rou
{1,0,{pysm::w,pyym::ei}},//蝛 wei
{1,0,{pysm::f,pyym::u}},//蝜 fu
{1,0,{pysm::y,pyym::uan}},//蝝 yuan
{1,0,{pysm::m,pyym::ei}},//蝞 mei
{1,0,{pysm::w,pyym::ei}},//蝟 wei
{1,0,{pysm::f,pyym::u}},//蝠 fu
{2,2811,{pysm::nop,pyym::nop}},//蝡 ru
{1,0,{pysm::x,pyym::ie}},//蝢 xie
{1,0,{pysm::y,pyym::ou}},//蝣 you
{3,671,{pysm::nop,pyym::nop}},//蝤 qiu
{2,2812,{pysm::nop,pyym::nop}},//蝥 mao
{3,672,{pysm::nop,pyym::nop}},//蝦 xia
{1,0,{pysm::y,pyym::ing}},//蝧 ying
{1,0,{pysm::sh,pyym::i}},//蝨 shi
{2,2813,{pysm::nop,pyym::nop}},//蝩 chong
{1,0,{pysm::t,pyym::ang}},//蝪 tang
{1,0,{pysm::zh,pyym::u}},//蝫 zhu
{1,0,{pysm::z,pyym::ong}},//蝬 zong
{2,2814,{pysm::nop,pyym::nop}},//蝭 ti
{1,0,{pysm::f,pyym::u}},//蝮 fu
{1,0,{pysm::y,pyym::uan}},//蝯 yuan
{1,0,{pysm::k,pyym::ui}},//蝰 kui
{1,0,{pysm::m,pyym::eng}},//蝱 meng
{1,0,{pysm::l,pyym::a}},//蝲 la
{2,2815,{pysm::nop,pyym::nop}},//蝳 du
{1,0,{pysm::h,pyym::u}},//蝴 hu
{1,0,{pysm::q,pyym::iu}},//蝵 qiu
{2,2816,{pysm::nop,pyym::nop}},//蝶 die
{2,2817,{pysm::nop,pyym::nop}},//蝷 li
{3,673,{pysm::nop,pyym::nop}},//蝸 wo
{2,2818,{pysm::nop,pyym::nop}},//蝹 yun
{2,2819,{pysm::nop,pyym::nop}},//蝺 qu
{1,0,{pysm::n,pyym::an}},//蝻 nan
{1,0,{pysm::l,pyym::ou}},//蝼 lou
{1,0,{pysm::ch,pyym::un}},//蝽 chun
{1,0,{pysm::r,pyym::ong}},//蝾 rong
{1,0,{pysm::y,pyym::ing}},//蝿 ying
{1,0,{pysm::j,pyym::iang}},//螀 jiang
{1,0,{pysm::b,pyym::an}},//螁 ban
{1,0,{pysm::l,pyym::ang}},//螂 lang
{2,2820,{pysm::nop,pyym::nop}},//螃 pang
{1,0,{pysm::s,pyym::i}},//螄 si
{2,2821,{pysm::nop,pyym::nop}},//螅 xi
{1,0,{pysm::c,pyym::i}},//螆 ci
{2,2822,{pysm::nop,pyym::nop}},//螇 xi
{1,0,{pysm::y,pyym::uan}},//螈 yuan
{1,0,{pysm::w,pyym::eng}},//螉 weng
{1,0,{pysm::l,pyym::ian}},//螊 lian
{1,0,{pysm::s,pyym::ou}},//螋 sou
{3,674,{pysm::nop,pyym::nop}},//螌 ban
{1,0,{pysm::r,pyym::ong}},//融 rong
{1,0,{pysm::r,pyym::ong}},//螎 rong
{1,0,{pysm::j,pyym::i}},//螏 ji
{1,0,{pysm::w,pyym::u}},//螐 wu
{1,0,{pysm::x,pyym::iu}},//螑 xiu
{1,0,{pysm::h,pyym::an}},//螒 han
{1,0,{pysm::q,pyym::in}},//螓 qin
{2,2823,{pysm::nop,pyym::nop}},//螔 yi
{2,2824,{pysm::nop,pyym::nop}},//螕 bi
{1,0,{pysm::h,pyym::ua}},//螖 hua
{1,0,{pysm::t,pyym::ang}},//螗 tang
{1,0,{pysm::y,pyym::i}},//螘 yi
{1,0,{pysm::d,pyym::u}},//螙 du
{2,2825,{pysm::nop,pyym::nop}},//螚 nai
{2,2826,{pysm::nop,pyym::nop}},//螛 he
{1,0,{pysm::h,pyym::u}},//螜 hu
{2,2827,{pysm::nop,pyym::nop}},//螝 gui
{1,0,{pysm::m,pyym::a}},//螞 ma
{1,0,{pysm::m,pyym::ing}},//螟 ming
{1,0,{pysm::y,pyym::i}},//螠 yi
{1,0,{pysm::w,pyym::en}},//螡 wen
{1,0,{pysm::y,pyym::ing}},//螢 ying
{2,2828,{pysm::nop,pyym::nop}},//螣 te
{1,0,{pysm::zh,pyym::ong}},//螤 zhong
{1,0,{pysm::c,pyym::ang}},//螥 cang
{1,0,{pysm::s,pyym::ao}},//螦 sao
{1,0,{pysm::q,pyym::i}},//螧 qi
{1,0,{pysm::m,pyym::an}},//螨 man
{1,0,{pysm::t,pyym::iao}},//螩 tiao
{1,0,{pysm::sh,pyym::ang}},//螪 shang
{2,2829,{pysm::nop,pyym::nop}},//螫 shi
{1,0,{pysm::c,pyym::ao}},//螬 cao
{1,0,{pysm::ch,pyym::i}},//螭 chi
{2,2830,{pysm::nop,pyym::nop}},//螮 di
{1,0,{pysm::nop,pyym::ao}},//螯 ao
{1,0,{pysm::l,pyym::u}},//螰 lu
{1,0,{pysm::w,pyym::ei}},//螱 wei
{2,2831,{pysm::nop,pyym::nop}},//螲 zhi
{1,0,{pysm::t,pyym::ang}},//螳 tang
{1,0,{pysm::ch,pyym::en}},//螴 chen
{1,0,{pysm::p,pyym::iao}},//螵 piao
{2,2832,{pysm::nop,pyym::nop}},//螶 qu
{1,0,{pysm::p,pyym::i}},//螷 pi
{1,0,{pysm::y,pyym::u}},//螸 yu
{2,2833,{pysm::nop,pyym::nop}},//螹 jian
{1,0,{pysm::l,pyym::uo}},//螺 luo
{1,0,{pysm::l,pyym::ou}},//螻 lou
{1,0,{pysm::q,pyym::in}},//螼 qin
{1,0,{pysm::zh,pyym::ong}},//螽 zhong
{1,0,{pysm::y,pyym::in}},//螾 yin
{1,0,{pysm::j,pyym::iang}},//螿 jiang
{1,0,{pysm::sh,pyym::uai}},//蟀 shuai
{1,0,{pysm::w,pyym::en}},//蟁 wen
{1,0,{pysm::x,pyym::iao}},//蟂 xiao
{1,0,{pysm::w,pyym::an}},//蟃 wan
{1,0,{pysm::zh,pyym::e}},//蟄 zhe
{1,0,{pysm::zh,pyym::e}},//蟅 zhe
{2,2834,{pysm::nop,pyym::nop}},//蟆 ma
{1,0,{pysm::m,pyym::a}},//蟇 ma
{2,2835,{pysm::nop,pyym::nop}},//蟈 guo
{2,2836,{pysm::nop,pyym::nop}},//蟉 liu
{2,2837,{pysm::nop,pyym::nop}},//蟊 mao
{1,0,{pysm::x,pyym::i}},//蟋 xi
{1,0,{pysm::c,pyym::ong}},//蟌 cong
{1,0,{pysm::l,pyym::i}},//蟍 li
{1,0,{pysm::m,pyym::an}},//蟎 man
{1,0,{pysm::x,pyym::iao}},//蟏 xiao
{1,0,{pysm::ch,pyym::ang}},//蟐 chang
{1,0,{pysm::zh,pyym::ang}},//蟑 zhang
{2,2838,{pysm::nop,pyym::nop}},//蟒 mang
{1,0,{pysm::x,pyym::iang}},//蟓 xiang
{1,0,{pysm::m,pyym::o}},//蟔 mo
{1,0,{pysm::z,pyym::ui}},//蟕 zui
{1,0,{pysm::s,pyym::i}},//蟖 si
{1,0,{pysm::q,pyym::iu}},//蟗 qiu
{1,0,{pysm::t,pyym::e}},//蟘 te
{1,0,{pysm::zh,pyym::i}},//蟙 zhi
{1,0,{pysm::p,pyym::eng}},//蟚 peng
{1,0,{pysm::p,pyym::eng}},//蟛 peng
{2,2839,{pysm::nop,pyym::nop}},//蟜 jiao
{1,0,{pysm::q,pyym::u}},//蟝 qu
{1,0,{pysm::b,pyym::ie}},//蟞 bie
{1,0,{pysm::l,pyym::iao}},//蟟 liao
{2,2840,{pysm::nop,pyym::nop}},//蟠 pan
{1,0,{pysm::g,pyym::ui}},//蟡 gui
{1,0,{pysm::x,pyym::i}},//蟢 xi
{2,2841,{pysm::nop,pyym::nop}},//蟣 ji
{1,0,{pysm::zh,pyym::uan}},//蟤 zhuan
{1,0,{pysm::h,pyym::uang}},//蟥 huang
{2,2842,{pysm::nop,pyym::nop}},//蟦 fei
{2,2843,{pysm::nop,pyym::nop}},//蟧 lao
{1,0,{pysm::j,pyym::ue}},//蟨 jue
{1,0,{pysm::j,pyym::ue}},//蟩 jue
{1,0,{pysm::h,pyym::ui}},//蟪 hui
{2,2844,{pysm::nop,pyym::nop}},//蟫 yin
{3,675,{pysm::nop,pyym::nop}},//蟬 chan
{1,0,{pysm::j,pyym::iao}},//蟭 jiao
{1,0,{pysm::sh,pyym::an}},//蟮 shan
{2,2845,{pysm::nop,pyym::nop}},//蟯 nao
{1,0,{pysm::x,pyym::iao}},//蟰 xiao
{2,2846,{pysm::nop,pyym::nop}},//蟱 wu
{3,676,{pysm::nop,pyym::nop}},//蟲 chong
{1,0,{pysm::x,pyym::un}},//蟳 xun
{1,0,{pysm::s,pyym::i}},//蟴 si
{1,0,{pysm::ch,pyym::u}},//蟵 chu
{1,0,{pysm::ch,pyym::eng}},//蟶 cheng
{1,0,{pysm::d,pyym::ang}},//蟷 dang
{1,0,{pysm::l,pyym::i}},//蟸 li
{1,0,{pysm::x,pyym::ie}},//蟹 xie
{4,134,{pysm::nop,pyym::nop}},//蟺 shan
{2,2847,{pysm::nop,pyym::nop}},//蟻 yi
{1,0,{pysm::j,pyym::ing}},//蟼 jing
{1,0,{pysm::d,pyym::a}},//蟽 da
{1,0,{pysm::ch,pyym::an}},//蟾 chan
{2,2848,{pysm::nop,pyym::nop}},//蟿 qi
{2,2849,{pysm::nop,pyym::nop}},//蠀 ci
{1,0,{pysm::x,pyym::iang}},//蠁 xiang
{1,0,{pysm::sh,pyym::e}},//蠂 she
{2,2850,{pysm::nop,pyym::nop}},//蠃 luo
{1,0,{pysm::q,pyym::in}},//蠄 qin
{1,0,{pysm::y,pyym::ing}},//蠅 ying
{1,0,{pysm::ch,pyym::ai}},//蠆 chai
{1,0,{pysm::l,pyym::i}},//蠇 li
{1,0,{pysm::z,pyym::ei}},//蠈 zei
{1,0,{pysm::x,pyym::uan}},//蠉 xuan
{1,0,{pysm::l,pyym::ian}},//蠊 lian
{1,0,{pysm::zh,pyym::u}},//蠋 zhu
{1,0,{pysm::z,pyym::e}},//蠌 ze
{1,0,{pysm::x,pyym::ie}},//蠍 xie
{1,0,{pysm::m,pyym::ang}},//蠎 mang
{1,0,{pysm::x,pyym::ie}},//蠏 xie
{1,0,{pysm::q,pyym::i}},//蠐 qi
{1,0,{pysm::r,pyym::ong}},//蠑 rong
{1,0,{pysm::j,pyym::ian}},//蠒 jian
{1,0,{pysm::m,pyym::eng}},//蠓 meng
{1,0,{pysm::h,pyym::ao}},//蠔 hao
{1,0,{pysm::r,pyym::u}},//蠕 ru
{2,2851,{pysm::nop,pyym::nop}},//蠖 huo
{1,0,{pysm::zh,pyym::uo}},//蠗 zhuo
{1,0,{pysm::j,pyym::ie}},//蠘 jie
{1,0,{pysm::p,pyym::in}},//蠙 pin
{1,0,{pysm::h,pyym::e}},//蠚 he
{1,0,{pysm::m,pyym::ie}},//蠛 mie
{1,0,{pysm::f,pyym::an}},//蠜 fan
{1,0,{pysm::l,pyym::ei}},//蠝 lei
{1,0,{pysm::j,pyym::ie}},//蠞 jie
{1,0,{pysm::l,pyym::a}},//蠟 la
{2,2852,{pysm::nop,pyym::nop}},//蠠 min
{2,2853,{pysm::nop,pyym::nop}},//蠡 li
{1,0,{pysm::ch,pyym::un}},//蠢 chun
{1,0,{pysm::l,pyym::i}},//蠣 li
{1,0,{pysm::q,pyym::iu}},//蠤 qiu
{1,0,{pysm::n,pyym::ie}},//蠥 nie
{1,0,{pysm::l,pyym::u}},//蠦 lu
{1,0,{pysm::d,pyym::u}},//蠧 du
{1,0,{pysm::x,pyym::iao}},//蠨 xiao
{2,2854,{pysm::nop,pyym::nop}},//蠩 zhu
{1,0,{pysm::l,pyym::ong}},//蠪 long
{1,0,{pysm::l,pyym::i}},//蠫 li
{1,0,{pysm::l,pyym::ong}},//蠬 long
{2,2855,{pysm::nop,pyym::nop}},//蠭 feng
{1,0,{pysm::y,pyym::e}},//蠮 ye
{1,0,{pysm::p,pyym::i}},//蠯 pi
{3,677,{pysm::nop,pyym::nop}},//蠰 nang
{2,2856,{pysm::nop,pyym::nop}},//蠱 gu
{1,0,{pysm::j,pyym::uan}},//蠲 juan
{1,0,{pysm::y,pyym::ing}},//蠳 ying
{1,0,{pysm::sh,pyym::u}},//蠴 shu
{1,0,{pysm::x,pyym::i}},//蠵 xi
{1,0,{pysm::c,pyym::an}},//蠶 can
{1,0,{pysm::q,pyym::u}},//蠷 qu
{2,2857,{pysm::nop,pyym::nop}},//蠸 quan
{1,0,{pysm::d,pyym::u}},//蠹 du
{1,0,{pysm::c,pyym::an}},//蠺 can
{1,0,{pysm::m,pyym::an}},//蠻 man
{2,2858,{pysm::nop,pyym::nop}},//蠼 qu
{1,0,{pysm::j,pyym::ie}},//蠽 jie
{2,2859,{pysm::nop,pyym::nop}},//蠾 zhu
{1,0,{pysm::zh,pyym::uo}},//蠿 zhuo
{2,2860,{pysm::nop,pyym::nop}},//血 xue
{1,0,{pysm::h,pyym::uang}},//衁 huang
{1,0,{pysm::n,pyym::v}},//衂 nü
{2,2861,{pysm::nop,pyym::nop}},//衃 pei
{1,0,{pysm::n,pyym::v}},//衄 nü
{1,0,{pysm::x,pyym::in}},//衅 xin
{1,0,{pysm::zh,pyym::ong}},//衆 zhong
{1,0,{pysm::m,pyym::ai}},//衇 mai
{1,0,{pysm::nop,pyym::er}},//衈 er
{1,0,{pysm::k,pyym::a}},//衉 ka
{1,0,{pysm::m,pyym::ie}},//衊 mie
{1,0,{pysm::x,pyym::i}},//衋 xi
{3,678,{pysm::nop,pyym::nop}},//行 xing
{1,0,{pysm::y,pyym::an}},//衍 yan
{1,0,{pysm::k,pyym::an}},//衎 kan
{1,0,{pysm::y,pyym::uan}},//衏 yuan
{1,0,{pysm::q,pyym::u}},//衐 qu
{1,0,{pysm::l,pyym::ing}},//衑 ling
{1,0,{pysm::x,pyym::uan}},//衒 xuan
{1,0,{pysm::sh,pyym::u}},//術 shu
{1,0,{pysm::x,pyym::ian}},//衔 xian
{2,2862,{pysm::nop,pyym::nop}},//衕 tong
{2,2863,{pysm::nop,pyym::nop}},//衖 xiang
{1,0,{pysm::j,pyym::ie}},//街 jie
{2,2864,{pysm::nop,pyym::nop}},//衘 xian
{2,2865,{pysm::nop,pyym::nop}},//衙 ya
{1,0,{pysm::h,pyym::u}},//衚 hu
{1,0,{pysm::w,pyym::ei}},//衛 wei
{1,0,{pysm::d,pyym::ao}},//衜 dao
{1,0,{pysm::ch,pyym::ong}},//衝 chong
{1,0,{pysm::w,pyym::ei}},//衞 wei
{1,0,{pysm::d,pyym::ao}},//衟 dao
{1,0,{pysm::zh,pyym::un}},//衠 zhun
{1,0,{pysm::h,pyym::eng}},//衡 heng
{1,0,{pysm::q,pyym::u}},//衢 qu
{1,0,{pysm::y,pyym::i}},//衣 yi
{1,0,{pysm::y,pyym::i}},//衤 yi
{1,0,{pysm::b,pyym::u}},//补 bu
{1,0,{pysm::g,pyym::an}},//衦 gan
{1,0,{pysm::y,pyym::u}},//衧 yu
{1,0,{pysm::b,pyym::iao}},//表 biao
{1,0,{pysm::ch,pyym::a}},//衩 cha
{1,0,{pysm::y,pyym::i}},//衪 yi
{1,0,{pysm::sh,pyym::an}},//衫 shan
{1,0,{pysm::ch,pyym::en}},//衬 chen
{1,0,{pysm::f,pyym::u}},//衭 fu
{1,0,{pysm::g,pyym::un}},//衮 gun
{2,2866,{pysm::nop,pyym::nop}},//衯 fen
{3,679,{pysm::nop,pyym::nop}},//衰 shuai
{1,0,{pysm::j,pyym::ie}},//衱 jie
{1,0,{pysm::n,pyym::a}},//衲 na
{1,0,{pysm::zh,pyym::ong}},//衳 zhong
{1,0,{pysm::d,pyym::an}},//衴 dan
{1,0,{pysm::y,pyym::i}},//衵 yi
{1,0,{pysm::zh,pyym::ong}},//衶 zhong
{1,0,{pysm::zh,pyym::ong}},//衷 zhong
{1,0,{pysm::j,pyym::ie}},//衸 jie
{3,680,{pysm::nop,pyym::nop}},//衹 zhi
{1,0,{pysm::x,pyym::ie}},//衺 xie
{1,0,{pysm::r,pyym::an}},//衻 ran
{1,0,{pysm::zh,pyym::i}},//衼 zhi
{1,0,{pysm::r,pyym::en}},//衽 ren
{1,0,{pysm::q,pyym::in}},//衾 qin
{2,2867,{pysm::nop,pyym::nop}},//衿 jin
{1,0,{pysm::j,pyym::un}},//袀 jun
{1,0,{pysm::y,pyym::uan}},//袁 yuan
{2,2868,{pysm::nop,pyym::nop}},//袂 mei
{1,0,{pysm::ch,pyym::ai}},//袃 chai
{1,0,{pysm::nop,pyym::ao}},//袄 ao
{1,0,{pysm::n,pyym::iao}},//袅 niao
{1,0,{pysm::h,pyym::ui}},//袆 hui
{1,0,{pysm::r,pyym::an}},//袇 ran
{1,0,{pysm::j,pyym::ia}},//袈 jia
{1,0,{pysm::t,pyym::uo}},//袉 tuo
{1,0,{pysm::l,pyym::ing}},//袊 ling
{1,0,{pysm::d,pyym::ai}},//袋 dai
{2,2869,{pysm::nop,pyym::nop}},//袌 bao
{2,2870,{pysm::nop,pyym::nop}},//袍 pao
{1,0,{pysm::y,pyym::ao}},//袎 yao
{1,0,{pysm::z,pyym::uo}},//袏 zuo
{1,0,{pysm::b,pyym::i}},//袐 bi
{1,0,{pysm::sh,pyym::ao}},//袑 shao
{2,2871,{pysm::nop,pyym::nop}},//袒 tan
{2,2872,{pysm::nop,pyym::nop}},//袓 ju
{3,681,{pysm::nop,pyym::nop}},//袔 he
{1,0,{pysm::x,pyym::ue}},//袕 xue
{1,0,{pysm::x,pyym::iu}},//袖 xiu
{1,0,{pysm::zh,pyym::en}},//袗 zhen
{2,2873,{pysm::nop,pyym::nop}},//袘 yi
{1,0,{pysm::p,pyym::a}},//袙 pa
{2,2874,{pysm::nop,pyym::nop}},//袚 bo
{1,0,{pysm::d,pyym::i}},//袛 di
{2,2875,{pysm::nop,pyym::nop}},//袜 wa
{1,0,{pysm::f,pyym::u}},//袝 fu
{1,0,{pysm::g,pyym::un}},//袞 gun
{1,0,{pysm::zh,pyym::i}},//袟 zhi
{1,0,{pysm::zh,pyym::i}},//袠 zhi
{1,0,{pysm::r,pyym::an}},//袡 ran
{2,2876,{pysm::nop,pyym::nop}},//袢 pan
{1,0,{pysm::y,pyym::i}},//袣 yi
{2,2877,{pysm::nop,pyym::nop}},//袤 mao
{1,0,{pysm::t,pyym::uo}},//袥 tuo
{2,2878,{pysm::nop,pyym::nop}},//袦 na
{1,0,{pysm::g,pyym::ou}},//袧 gou
{1,0,{pysm::x,pyym::uan}},//袨 xuan
{2,2879,{pysm::nop,pyym::nop}},//袩 zhe
{1,0,{pysm::q,pyym::u}},//袪 qu
{3,682,{pysm::nop,pyym::nop}},//被 bei
{1,0,{pysm::y,pyym::u}},//袬 yu
{1,0,{pysm::x,pyym::i}},//袭 xi
{1,0,{pysm::m,pyym::i}},//袮 mi
{1,0,{pysm::b,pyym::o}},//袯 bo
{1,0,{pysm::b,pyym::o}},//袰 bo
{1,0,{pysm::f,pyym::u}},//袱 fu
{2,2880,{pysm::nop,pyym::nop}},//袲 chi
{4,135,{pysm::nop,pyym::nop}},//袳 chi
{1,0,{pysm::k,pyym::u}},//袴 ku
{1,0,{pysm::r,pyym::en}},//袵 ren
{1,0,{pysm::j,pyym::iang}},//袶 jiang
{3,683,{pysm::nop,pyym::nop}},//袷 jia
{2,2881,{pysm::nop,pyym::nop}},//袸 jian
{2,2882,{pysm::nop,pyym::nop}},//袹 bo
{1,0,{pysm::j,pyym::ie}},//袺 jie
{1,0,{pysm::nop,pyym::er}},//袻 er
{2,2883,{pysm::nop,pyym::nop}},//袼 ge
{1,0,{pysm::r,pyym::u}},//袽 ru
{1,0,{pysm::zh,pyym::u}},//袾 zhu
{2,2884,{pysm::nop,pyym::nop}},//袿 gui
{1,0,{pysm::y,pyym::in}},//裀 yin
{1,0,{pysm::c,pyym::ai}},//裁 cai
{1,0,{pysm::l,pyym::ie}},//裂 lie
{1,0,{pysm::k,pyym::a}},//裃 ka
{1,0,{pysm::x,pyym::ing}},//裄 xing
{1,0,{pysm::zh,pyym::uang}},//装 zhuang
{1,0,{pysm::d,pyym::ang}},//裆 dang
{1,0,{pysm::x,pyym::u}},//裇 xu
{1,0,{pysm::k,pyym::un}},//裈 kun
{1,0,{pysm::k,pyym::en}},//裉 ken
{1,0,{pysm::n,pyym::iao}},//裊 niao
{1,0,{pysm::sh,pyym::u}},//裋 shu
{2,2885,{pysm::nop,pyym::nop}},//裌 jia
{1,0,{pysm::k,pyym::un}},//裍 kun
{1,0,{pysm::ch,pyym::eng}},//裎 cheng
{1,0,{pysm::l,pyym::i}},//裏 li
{1,0,{pysm::j,pyym::uan}},//裐 juan
{1,0,{pysm::sh,pyym::en}},//裑 shen
{2,2886,{pysm::nop,pyym::nop}},//裒 pou
{2,2887,{pysm::nop,pyym::nop}},//裓 ge
{1,0,{pysm::y,pyym::i}},//裔 yi
{1,0,{pysm::y,pyym::u}},//裕 yu
{1,0,{pysm::zh,pyym::en}},//裖 zhen
{1,0,{pysm::l,pyym::iu}},//裗 liu
{1,0,{pysm::q,pyym::iu}},//裘 qiu
{1,0,{pysm::q,pyym::un}},//裙 qun
{1,0,{pysm::j,pyym::i}},//裚 ji
{1,0,{pysm::y,pyym::i}},//裛 yi
{1,0,{pysm::b,pyym::u}},//補 bu
{1,0,{pysm::zh,pyym::uang}},//裝 zhuang
{1,0,{pysm::sh,pyym::ui}},//裞 shui
{1,0,{pysm::sh,pyym::a}},//裟 sha
{1,0,{pysm::q,pyym::un}},//裠 qun
{1,0,{pysm::l,pyym::i}},//裡 li
{2,2888,{pysm::nop,pyym::nop}},//裢 lian
{1,0,{pysm::l,pyym::ian}},//裣 lian
{1,0,{pysm::k,pyym::u}},//裤 ku
{1,0,{pysm::j,pyym::ian}},//裥 jian
{1,0,{pysm::f,pyym::ou}},//裦 fou
{2,2889,{pysm::nop,pyym::nop}},//裧 chan
{2,2890,{pysm::nop,pyym::nop}},//裨 bi
{1,0,{pysm::k,pyym::un}},//裩 kun
{1,0,{pysm::t,pyym::ao}},//裪 tao
{1,0,{pysm::y,pyym::uan}},//裫 yuan
{1,0,{pysm::l,pyym::ing}},//裬 ling
{1,0,{pysm::ch,pyym::i}},//裭 chi
{1,0,{pysm::ch,pyym::ang}},//裮 chang
{2,2891,{pysm::nop,pyym::nop}},//裯 chou
{1,0,{pysm::d,pyym::uo}},//裰 duo
{1,0,{pysm::b,pyym::iao}},//裱 biao
{1,0,{pysm::l,pyym::iang}},//裲 liang
{2,2892,{pysm::nop,pyym::nop}},//裳 shang
{2,2893,{pysm::nop,pyym::nop}},//裴 pei
{1,0,{pysm::p,pyym::ei}},//裵 pei
{1,0,{pysm::f,pyym::ei}},//裶 fei
{2,2894,{pysm::nop,pyym::nop}},//裷 yuan
{1,0,{pysm::l,pyym::uo}},//裸 luo
{1,0,{pysm::g,pyym::uo}},//裹 guo
{2,2895,{pysm::nop,pyym::nop}},//裺 yan
{1,0,{pysm::d,pyym::u}},//裻 du
{2,2896,{pysm::nop,pyym::nop}},//裼 ti
{1,0,{pysm::zh,pyym::i}},//製 zhi
{1,0,{pysm::j,pyym::u}},//裾 ju
{2,2897,{pysm::nop,pyym::nop}},//裿 yi
{1,0,{pysm::q,pyym::i}},//褀 qi
{1,0,{pysm::g,pyym::uo}},//褁 guo
{1,0,{pysm::g,pyym::ua}},//褂 gua
{1,0,{pysm::k,pyym::en}},//褃 ken
{1,0,{pysm::q,pyym::i}},//褄 qi
{1,0,{pysm::t,pyym::i}},//褅 ti
{2,2898,{pysm::nop,pyym::nop}},//褆 ti
{1,0,{pysm::f,pyym::u}},//複 fu
{2,2899,{pysm::nop,pyym::nop}},//褈 chong
{1,0,{pysm::x,pyym::ie}},//褉 xie
{2,2900,{pysm::nop,pyym::nop}},//褊 bian
{1,0,{pysm::d,pyym::ie}},//褋 die
{1,0,{pysm::k,pyym::un}},//褌 kun
{2,2901,{pysm::nop,pyym::nop}},//褍 duan
{2,2902,{pysm::nop,pyym::nop}},//褎 xiu
{1,0,{pysm::x,pyym::iu}},//褏 xiu
{1,0,{pysm::h,pyym::e}},//褐 he
{1,0,{pysm::y,pyym::uan}},//褑 yuan
{1,0,{pysm::b,pyym::ao}},//褒 bao
{1,0,{pysm::b,pyym::ao}},//褓 bao
{1,0,{pysm::f,pyym::u}},//褔 fu
{2,2903,{pysm::nop,pyym::nop}},//褕 yu
{1,0,{pysm::t,pyym::uan}},//褖 tuan
{1,0,{pysm::y,pyym::an}},//褗 yan
{2,2904,{pysm::nop,pyym::nop}},//褘 hui
{1,0,{pysm::b,pyym::ei}},//褙 bei
{3,684,{pysm::nop,pyym::nop}},//褚 chu
{1,0,{pysm::l,pyym::v}},//褛 lü
{1,0,{pysm::p,pyym::ao}},//褜 pao
{1,0,{pysm::d,pyym::an}},//褝 dan
{2,2905,{pysm::nop,pyym::nop}},//褞 yun
{1,0,{pysm::t,pyym::a}},//褟 ta
{1,0,{pysm::g,pyym::ou}},//褠 gou
{1,0,{pysm::d,pyym::a}},//褡 da
{1,0,{pysm::h,pyym::uai}},//褢 huai
{1,0,{pysm::r,pyym::ong}},//褣 rong
{1,0,{pysm::y,pyym::uan}},//褤 yuan
{2,2906,{pysm::nop,pyym::nop}},//褥 ru
{1,0,{pysm::n,pyym::ai}},//褦 nai
{1,0,{pysm::j,pyym::iong}},//褧 jiong
{2,2907,{pysm::nop,pyym::nop}},//褨 suo
{2,2908,{pysm::nop,pyym::nop}},//褩 ban
{2,2909,{pysm::nop,pyym::nop}},//褪 tui
{1,0,{pysm::ch,pyym::i}},//褫 chi
{1,0,{pysm::s,pyym::ang}},//褬 sang
{1,0,{pysm::n,pyym::iao}},//褭 niao
{1,0,{pysm::y,pyym::ing}},//褮 ying
{1,0,{pysm::j,pyym::ie}},//褯 jie
{1,0,{pysm::q,pyym::ian}},//褰 qian
{1,0,{pysm::h,pyym::uai}},//褱 huai
{1,0,{pysm::k,pyym::u}},//褲 ku
{1,0,{pysm::l,pyym::ian}},//褳 lian
{1,0,{pysm::l,pyym::an}},//褴 lan
{1,0,{pysm::l,pyym::i}},//褵 li
{3,685,{pysm::nop,pyym::nop}},//褶 zhe
{1,0,{pysm::sh,pyym::i}},//褷 shi
{1,0,{pysm::l,pyym::v}},//褸 lü
{2,2910,{pysm::nop,pyym::nop}},//褹 yi
{1,0,{pysm::d,pyym::ie}},//褺 die
{1,0,{pysm::x,pyym::ie}},//褻 xie
{1,0,{pysm::x,pyym::ian}},//褼 xian
{1,0,{pysm::w,pyym::ei}},//褽 wei
{1,0,{pysm::b,pyym::iao}},//褾 biao
{1,0,{pysm::c,pyym::ao}},//褿 cao
{1,0,{pysm::j,pyym::i}},//襀 ji
{1,0,{pysm::q,pyym::iang}},//襁 qiang
{2,2911,{pysm::nop,pyym::nop}},//襂 sen
{2,2912,{pysm::nop,pyym::nop}},//襃 bao
{1,0,{pysm::x,pyym::iang}},//襄 xiang
{1,0,{pysm::b,pyym::i}},//襅 bi
{2,2913,{pysm::nop,pyym::nop}},//襆 fu
{1,0,{pysm::j,pyym::ian}},//襇 jian
{2,2914,{pysm::nop,pyym::nop}},//襈 zhuan
{1,0,{pysm::j,pyym::ian}},//襉 jian
{2,2915,{pysm::nop,pyym::nop}},//襊 cui
{1,0,{pysm::j,pyym::i}},//襋 ji
{1,0,{pysm::d,pyym::an}},//襌 dan
{1,0,{pysm::z,pyym::a}},//襍 za
{2,2916,{pysm::nop,pyym::nop}},//襎 fan
{2,2917,{pysm::nop,pyym::nop}},//襏 bo
{1,0,{pysm::x,pyym::iang}},//襐 xiang
{1,0,{pysm::x,pyym::in}},//襑 xin
{1,0,{pysm::b,pyym::ie}},//襒 bie
{1,0,{pysm::r,pyym::ao}},//襓 rao
{1,0,{pysm::m,pyym::an}},//襔 man
{1,0,{pysm::l,pyym::an}},//襕 lan
{1,0,{pysm::nop,pyym::ao}},//襖 ao
{3,686,{pysm::nop,pyym::nop}},//襗 ze
{2,2918,{pysm::nop,pyym::nop}},//襘 gui
{1,0,{pysm::c,pyym::ao}},//襙 cao
{1,0,{pysm::s,pyym::ui}},//襚 sui
{1,0,{pysm::n,pyym::ong}},//襛 nong
{2,2919,{pysm::nop,pyym::nop}},//襜 chan
{2,2920,{pysm::nop,pyym::nop}},//襝 lian
{1,0,{pysm::b,pyym::i}},//襞 bi
{1,0,{pysm::j,pyym::in}},//襟 jin
{1,0,{pysm::d,pyym::ang}},//襠 dang
{2,2921,{pysm::nop,pyym::nop}},//襡 shu
{3,687,{pysm::nop,pyym::nop}},//襢 tan
{1,0,{pysm::b,pyym::i}},//襣 bi
{1,0,{pysm::l,pyym::an}},//襤 lan
{1,0,{pysm::f,pyym::u}},//襥 fu
{1,0,{pysm::r,pyym::u}},//襦 ru
{1,0,{pysm::zh,pyym::i}},//襧 zhi
{1,0,{pysm::d,pyym::ui}},//襨 dui
{1,0,{pysm::sh,pyym::u}},//襩 shu
{1,0,{pysm::w,pyym::a}},//襪 wa
{1,0,{pysm::sh,pyym::i}},//襫 shi
{2,2922,{pysm::nop,pyym::nop}},//襬 bai
{1,0,{pysm::x,pyym::ie}},//襭 xie
{1,0,{pysm::b,pyym::o}},//襮 bo
{1,0,{pysm::ch,pyym::en}},//襯 chen
{1,0,{pysm::l,pyym::ai}},//襰 lai
{1,0,{pysm::l,pyym::ong}},//襱 long
{1,0,{pysm::x,pyym::i}},//襲 xi
{2,2923,{pysm::nop,pyym::nop}},//襳 xian
{1,0,{pysm::l,pyym::an}},//襴 lan
{1,0,{pysm::zh,pyym::e}},//襵 zhe
{1,0,{pysm::d,pyym::ai}},//襶 dai
{1,0,{pysm::j,pyym::u}},//襷 ju
{2,2924,{pysm::nop,pyym::nop}},//襸 zan
{1,0,{pysm::sh,pyym::i}},//襹 shi
{1,0,{pysm::j,pyym::ian}},//襺 jian
{1,0,{pysm::p,pyym::an}},//襻 pan
{1,0,{pysm::y,pyym::i}},//襼 yi
{1,0,{pysm::l,pyym::an}},//襽 lan
{1,0,{pysm::y,pyym::a}},//襾 ya
{1,0,{pysm::x,pyym::i}},//西 xi
{1,0,{pysm::x,pyym::i}},//覀 xi
{1,0,{pysm::y,pyym::ao}},//要 yao
{2,2925,{pysm::nop,pyym::nop}},//覂 feng
{3,688,{pysm::nop,pyym::nop}},//覃 tan
{1,0,{pysm::f,pyym::u}},//覄 fu
{1,0,{pysm::f,pyym::iao}},//覅 fiao
{1,0,{pysm::f,pyym::u}},//覆 fu
{1,0,{pysm::b,pyym::a}},//覇 ba
{1,0,{pysm::h,pyym::e}},//覈 he
{1,0,{pysm::j,pyym::i}},//覉 ji
{1,0,{pysm::j,pyym::i}},//覊 ji
{2,2926,{pysm::nop,pyym::nop}},//見 jian
{1,0,{pysm::g,pyym::uan}},//覌 guan
{1,0,{pysm::b,pyym::ian}},//覍 bian
{1,0,{pysm::y,pyym::an}},//覎 yan
{2,2927,{pysm::nop,pyym::nop}},//規 gui
{1,0,{pysm::j,pyym::ue}},//覐 jue
{1,0,{pysm::p,pyym::ian}},//覑 pian
{1,0,{pysm::m,pyym::ao}},//覒 mao
{1,0,{pysm::m,pyym::i}},//覓 mi
{1,0,{pysm::m,pyym::i}},//覔 mi
{2,2928,{pysm::nop,pyym::nop}},//覕 mie
{1,0,{pysm::sh,pyym::i}},//視 shi
{1,0,{pysm::s,pyym::i}},//覗 si
{3,689,{pysm::nop,pyym::nop}},//覘 chan
{1,0,{pysm::l,pyym::uo}},//覙 luo
{1,0,{pysm::j,pyym::ue}},//覚 jue
{1,0,{pysm::m,pyym::i}},//覛 mi
{1,0,{pysm::t,pyym::iao}},//覜 tiao
{1,0,{pysm::l,pyym::ian}},//覝 lian
{1,0,{pysm::y,pyym::ao}},//覞 yao
{1,0,{pysm::zh,pyym::i}},//覟 zhi
{1,0,{pysm::j,pyym::un}},//覠 jun
{1,0,{pysm::x,pyym::i}},//覡 xi
{1,0,{pysm::sh,pyym::an}},//覢 shan
{1,0,{pysm::w,pyym::ei}},//覣 wei
{1,0,{pysm::x,pyym::i}},//覤 xi
{1,0,{pysm::t,pyym::ian}},//覥 tian
{1,0,{pysm::y,pyym::u}},//覦 yu
{1,0,{pysm::l,pyym::an}},//覧 lan
{1,0,{pysm::nop,pyym::e}},//覨 e
{1,0,{pysm::d,pyym::u}},//覩 du
{2,2929,{pysm::nop,pyym::nop}},//親 qin
{1,0,{pysm::p,pyym::ang}},//覫 pang
{1,0,{pysm::j,pyym::i}},//覬 ji
{1,0,{pysm::m,pyym::ing}},//覭 ming
{1,0,{pysm::y,pyym::ing}},//覮 ying
{1,0,{pysm::g,pyym::ou}},//覯 gou
{1,0,{pysm::q,pyym::u}},//覰 qu
{1,0,{pysm::zh,pyym::an}},//覱 zhan
{1,0,{pysm::j,pyym::in}},//覲 jin
{1,0,{pysm::g,pyym::uan}},//観 guan
{1,0,{pysm::d,pyym::eng}},//覴 deng
{2,2930,{pysm::nop,pyym::nop}},//覵 jian
{2,2931,{pysm::nop,pyym::nop}},//覶 luo
{1,0,{pysm::q,pyym::u}},//覷 qu
{1,0,{pysm::j,pyym::ian}},//覸 jian
{1,0,{pysm::w,pyym::ei}},//覹 wei
{2,2932,{pysm::nop,pyym::nop}},//覺 jue
{1,0,{pysm::q,pyym::u}},//覻 qu
{1,0,{pysm::l,pyym::uo}},//覼 luo
{1,0,{pysm::l,pyym::an}},//覽 lan
{1,0,{pysm::sh,pyym::en}},//覾 shen
{2,2933,{pysm::nop,pyym::nop}},//覿 di
{1,0,{pysm::g,pyym::uan}},//觀 guan
{2,2934,{pysm::nop,pyym::nop}},//见 jian
{1,0,{pysm::g,pyym::uan}},//观 guan
{1,0,{pysm::y,pyym::an}},//觃 yan
{1,0,{pysm::g,pyym::ui}},//规 gui
{1,0,{pysm::m,pyym::i}},//觅 mi
{1,0,{pysm::sh,pyym::i}},//视 shi
{1,0,{pysm::ch,pyym::an}},//觇 chan
{1,0,{pysm::l,pyym::an}},//览 lan
{2,2935,{pysm::nop,pyym::nop}},//觉 jue
{1,0,{pysm::j,pyym::i}},//觊 ji
{1,0,{pysm::x,pyym::i}},//觋 xi
{1,0,{pysm::d,pyym::i}},//觌 di
{1,0,{pysm::t,pyym::ian}},//觍 tian
{1,0,{pysm::y,pyym::u}},//觎 yu
{1,0,{pysm::g,pyym::ou}},//觏 gou
{1,0,{pysm::j,pyym::in}},//觐 jin
{1,0,{pysm::q,pyym::u}},//觑 qu
{4,136,{pysm::nop,pyym::nop}},//角 jiao
{1,0,{pysm::q,pyym::iu}},//觓 qiu
{1,0,{pysm::j,pyym::in}},//觔 jin
{3,690,{pysm::nop,pyym::nop}},//觕 cu
{3,691,{pysm::nop,pyym::nop}},//觖 jue
{1,0,{pysm::zh,pyym::i}},//觗 zhi
{1,0,{pysm::ch,pyym::ao}},//觘 chao
{1,0,{pysm::j,pyym::i}},//觙 ji
{1,0,{pysm::g,pyym::u}},//觚 gu
{1,0,{pysm::d,pyym::an}},//觛 dan
{2,2936,{pysm::nop,pyym::nop}},//觜 zi
{2,2937,{pysm::nop,pyym::nop}},//觝 di
{1,0,{pysm::sh,pyym::ang}},//觞 shang
{2,2938,{pysm::nop,pyym::nop}},//觟 hua
{1,0,{pysm::q,pyym::uan}},//觠 quan
{1,0,{pysm::g,pyym::e}},//觡 ge
{1,0,{pysm::sh,pyym::i}},//觢 shi
{2,2939,{pysm::nop,pyym::nop}},//解 jie
{1,0,{pysm::g,pyym::ui}},//觤 gui
{1,0,{pysm::g,pyym::ong}},//觥 gong
{1,0,{pysm::ch,pyym::u}},//触 chu
{1,0,{pysm::j,pyym::ie}},//觧 jie
{1,0,{pysm::h,pyym::un}},//觨 hun
{1,0,{pysm::q,pyym::iu}},//觩 qiu
{1,0,{pysm::x,pyym::ing}},//觪 xing
{1,0,{pysm::s,pyym::u}},//觫 su
{1,0,{pysm::n,pyym::i}},//觬 ni
{2,2940,{pysm::nop,pyym::nop}},//觭 ji
{1,0,{pysm::l,pyym::u}},//觮 lu
{1,0,{pysm::zh,pyym::i}},//觯 zhi
{2,2941,{pysm::nop,pyym::nop}},//觰 zha
{1,0,{pysm::b,pyym::i}},//觱 bi
{1,0,{pysm::x,pyym::ing}},//觲 xing
{3,692,{pysm::nop,pyym::nop}},//觳 hu
{1,0,{pysm::sh,pyym::ang}},//觴 shang
{1,0,{pysm::g,pyym::ong}},//觵 gong
{1,0,{pysm::zh,pyym::i}},//觶 zhi
{2,2942,{pysm::nop,pyym::nop}},//觷 xue
{1,0,{pysm::ch,pyym::u}},//觸 chu
{1,0,{pysm::x,pyym::i}},//觹 xi
{1,0,{pysm::y,pyym::i}},//觺 yi
{2,2943,{pysm::nop,pyym::nop}},//觻 li
{1,0,{pysm::j,pyym::ue}},//觼 jue
{1,0,{pysm::x,pyym::i}},//觽 xi
{1,0,{pysm::y,pyym::an}},//觾 yan
{2,2944,{pysm::nop,pyym::nop}},//觿 xi
{2,2945,{pysm::nop,pyym::nop}},//言 yan
{1,0,{pysm::y,pyym::an}},//訁 yan
{1,0,{pysm::d,pyym::ing}},//訂 ding
{1,0,{pysm::f,pyym::u}},//訃 fu
{2,2946,{pysm::nop,pyym::nop}},//訄 qiu
{1,0,{pysm::q,pyym::iu}},//訅 qiu
{1,0,{pysm::j,pyym::iao}},//訆 jiao
{3,693,{pysm::nop,pyym::nop}},//訇 hong
{1,0,{pysm::j,pyym::i}},//計 ji
{1,0,{pysm::f,pyym::an}},//訉 fan
{1,0,{pysm::x,pyym::un}},//訊 xun
{1,0,{pysm::d,pyym::iao}},//訋 diao
{1,0,{pysm::h,pyym::ong}},//訌 hong
{2,2947,{pysm::nop,pyym::nop}},//訍 chai
{1,0,{pysm::t,pyym::ao}},//討 tao
{1,0,{pysm::x,pyym::u}},//訏 xu
{2,2948,{pysm::nop,pyym::nop}},//訐 jie
{4,137,{pysm::nop,pyym::nop}},//訑 yi
{1,0,{pysm::r,pyym::en}},//訒 ren
{1,0,{pysm::x,pyym::un}},//訓 xun
{1,0,{pysm::y,pyym::in}},//訔 yin
{1,0,{pysm::sh,pyym::an}},//訕 shan
{1,0,{pysm::q,pyym::i}},//訖 qi
{1,0,{pysm::t,pyym::uo}},//託 tuo
{1,0,{pysm::j,pyym::i}},//記 ji
{1,0,{pysm::x,pyym::un}},//訙 xun
{1,0,{pysm::y,pyym::in}},//訚 yin
{1,0,{pysm::nop,pyym::e}},//訛 e
{2,2949,{pysm::nop,pyym::nop}},//訜 fen
{1,0,{pysm::y,pyym::a}},//訝 ya
{1,0,{pysm::y,pyym::ao}},//訞 yao
{1,0,{pysm::s,pyym::ong}},//訟 song
{1,0,{pysm::sh,pyym::en}},//訠 shen
{1,0,{pysm::y,pyym::in}},//訡 yin
{3,694,{pysm::nop,pyym::nop}},//訢 xin
{1,0,{pysm::j,pyym::ue}},//訣 jue
{2,2950,{pysm::nop,pyym::nop}},//訤 xiao
{1,0,{pysm::n,pyym::e}},//訥 ne
{1,0,{pysm::ch,pyym::en}},//訦 chen
{1,0,{pysm::y,pyym::ou}},//訧 you
{1,0,{pysm::zh,pyym::i}},//訨 zhi
{1,0,{pysm::x,pyym::iong}},//訩 xiong
{1,0,{pysm::f,pyym::ang}},//訪 fang
{1,0,{pysm::x,pyym::in}},//訫 xin
{2,2951,{pysm::nop,pyym::nop}},//訬 chao
{1,0,{pysm::sh,pyym::e}},//設 she
{1,0,{pysm::y,pyym::an}},//訮 yan
{1,0,{pysm::s,pyym::a}},//訯 sa
{1,0,{pysm::zh,pyym::un}},//訰 zhun
{2,2952,{pysm::nop,pyym::nop}},//許 xu
{1,0,{pysm::y,pyym::i}},//訲 yi
{1,0,{pysm::y,pyym::i}},//訳 yi
{1,0,{pysm::s,pyym::u}},//訴 su
{1,0,{pysm::ch,pyym::i}},//訵 chi
{1,0,{pysm::h,pyym::e}},//訶 he
{1,0,{pysm::sh,pyym::en}},//訷 shen
{1,0,{pysm::h,pyym::e}},//訸 he
{1,0,{pysm::x,pyym::u}},//訹 xu
{1,0,{pysm::zh,pyym::en}},//診 zhen
{1,0,{pysm::zh,pyym::u}},//註 zhu
{1,0,{pysm::zh,pyym::eng}},//証 zheng
{1,0,{pysm::g,pyym::ou}},//訽 gou
{1,0,{pysm::z,pyym::i}},//訾 zi
{1,0,{pysm::z,pyym::i}},//訿 zi
{4,138,{pysm::nop,pyym::nop}},//詀 zhan
{1,0,{pysm::g,pyym::u}},//詁 gu
{1,0,{pysm::f,pyym::u}},//詂 fu
{1,0,{pysm::j,pyym::ian}},//詃 jian
{1,0,{pysm::d,pyym::ie}},//詄 die
{1,0,{pysm::l,pyym::ing}},//詅 ling
{2,2953,{pysm::nop,pyym::nop}},//詆 di
{1,0,{pysm::y,pyym::ang}},//詇 yang
{1,0,{pysm::l,pyym::i}},//詈 li
{3,695,{pysm::nop,pyym::nop}},//詉 nao
{1,0,{pysm::p,pyym::an}},//詊 pan
{1,0,{pysm::zh,pyym::ou}},//詋 zhou
{1,0,{pysm::g,pyym::an}},//詌 gan
{1,0,{pysm::y,pyym::i}},//詍 yi
{1,0,{pysm::j,pyym::u}},//詎 ju
{1,0,{pysm::y,pyym::ao}},//詏 yao
{1,0,{pysm::zh,pyym::a}},//詐 zha
{4,139,{pysm::nop,pyym::nop}},//詑 yi
{3,696,{pysm::nop,pyym::nop}},//詒 yi
{1,0,{pysm::q,pyym::u}},//詓 qu
{1,0,{pysm::zh,pyym::ao}},//詔 zhao
{1,0,{pysm::p,pyym::ing}},//評 ping
{1,0,{pysm::b,pyym::i}},//詖 bi
{1,0,{pysm::x,pyym::iong}},//詗 xiong
{2,2954,{pysm::nop,pyym::nop}},//詘 qu
{2,2955,{pysm::nop,pyym::nop}},//詙 ba
{1,0,{pysm::d,pyym::a}},//詚 da
{1,0,{pysm::z,pyym::u}},//詛 zu
{1,0,{pysm::t,pyym::ao}},//詜 tao
{1,0,{pysm::zh,pyym::u}},//詝 zhu
{1,0,{pysm::c,pyym::i}},//詞 ci
{1,0,{pysm::zh,pyym::e}},//詟 zhe
{1,0,{pysm::y,pyym::ong}},//詠 yong
{1,0,{pysm::x,pyym::u}},//詡 xu
{1,0,{pysm::x,pyym::un}},//詢 xun
{1,0,{pysm::y,pyym::i}},//詣 yi
{1,0,{pysm::h,pyym::uang}},//詤 huang
{2,2956,{pysm::nop,pyym::nop}},//詥 he
{1,0,{pysm::sh,pyym::i}},//試 shi
{2,2957,{pysm::nop,pyym::nop}},//詧 cha
{1,0,{pysm::x,pyym::iao}},//詨 xiao
{1,0,{pysm::sh,pyym::i}},//詩 shi
{1,0,{pysm::h,pyym::en}},//詪 hen
{2,2958,{pysm::nop,pyym::nop}},//詫 cha
{2,2959,{pysm::nop,pyym::nop}},//詬 gou
{1,0,{pysm::g,pyym::ui}},//詭 gui
{1,0,{pysm::q,pyym::uan}},//詮 quan
{1,0,{pysm::h,pyym::ui}},//詯 hui
{1,0,{pysm::j,pyym::ie}},//詰 jie
{1,0,{pysm::h,pyym::ua}},//話 hua
{1,0,{pysm::g,pyym::ai}},//該 gai
{2,2960,{pysm::nop,pyym::nop}},//詳 xiang
{1,0,{pysm::w,pyym::ei}},//詴 wei
{1,0,{pysm::sh,pyym::en}},//詵 shen
{2,2961,{pysm::nop,pyym::nop}},//詶 zhou
{2,2962,{pysm::nop,pyym::nop}},//詷 tong
{1,0,{pysm::m,pyym::i}},//詸 mi
{2,2963,{pysm::nop,pyym::nop}},//詹 zhan
{1,0,{pysm::m,pyym::ing}},//詺 ming
{3,697,{pysm::nop,pyym::nop}},//詻 e
{1,0,{pysm::h,pyym::ui}},//詼 hui
{1,0,{pysm::y,pyym::an}},//詽 yan
{1,0,{pysm::x,pyym::iong}},//詾 xiong
{1,0,{pysm::g,pyym::ua}},//詿 gua
{2,2964,{pysm::nop,pyym::nop}},//誀 er
{1,0,{pysm::b,pyym::ing}},//誁 bing
{2,2965,{pysm::nop,pyym::nop}},//誂 tiao
{3,698,{pysm::nop,pyym::nop}},//誃 yi
{1,0,{pysm::l,pyym::ei}},//誄 lei
{1,0,{pysm::zh,pyym::u}},//誅 zhu
{1,0,{pysm::k,pyym::uang}},//誆 kuang
{2,2966,{pysm::nop,pyym::nop}},//誇 kua
{1,0,{pysm::w,pyym::u}},//誈 wu
{1,0,{pysm::y,pyym::u}},//誉 yu
{1,0,{pysm::t,pyym::eng}},//誊 teng
{1,0,{pysm::j,pyym::i}},//誋 ji
{1,0,{pysm::zh,pyym::i}},//誌 zhi
{1,0,{pysm::r,pyym::en}},//認 ren
{1,0,{pysm::c,pyym::u}},//誎 cu
{1,0,{pysm::l,pyym::ang}},//誏 lang
{1,0,{pysm::nop,pyym::e}},//誐 e
{1,0,{pysm::k,pyym::uang}},//誑 kuang
{4,140,{pysm::nop,pyym::nop}},//誒 ei
{1,0,{pysm::sh,pyym::i}},//誓 shi
{1,0,{pysm::t,pyym::ing}},//誔 ting
{1,0,{pysm::d,pyym::an}},//誕 dan
{1,0,{pysm::b,pyym::ei}},//誖 bei
{1,0,{pysm::ch,pyym::an}},//誗 chan
{1,0,{pysm::y,pyym::ou}},//誘 you
{1,0,{pysm::k,pyym::eng}},//誙 keng
{1,0,{pysm::q,pyym::iao}},//誚 qiao
{1,0,{pysm::q,pyym::in}},//誛 qin
{1,0,{pysm::sh,pyym::ua}},//誜 shua
{1,0,{pysm::nop,pyym::an}},//誝 an
{1,0,{pysm::y,pyym::u}},//語 yu
{1,0,{pysm::x,pyym::iao}},//誟 xiao
{1,0,{pysm::ch,pyym::eng}},//誠 cheng
{1,0,{pysm::j,pyym::ie}},//誡 jie
{1,0,{pysm::x,pyym::ian}},//誢 xian
{1,0,{pysm::w,pyym::u}},//誣 wu
{1,0,{pysm::w,pyym::u}},//誤 wu
{1,0,{pysm::g,pyym::ao}},//誥 gao
{1,0,{pysm::s,pyym::ong}},//誦 song
{1,0,{pysm::b,pyym::u}},//誧 bu
{1,0,{pysm::h,pyym::ui}},//誨 hui
{1,0,{pysm::j,pyym::ing}},//誩 jing
{1,0,{pysm::sh,pyym::uo}},//說 shuo
{1,0,{pysm::zh,pyym::en}},//誫 zhen
{4,141,{pysm::nop,pyym::nop}},//説 shuo
{1,0,{pysm::d,pyym::u}},//読 du
{1,0,{pysm::h,pyym::ua}},//誮 hua
{1,0,{pysm::ch,pyym::ang}},//誯 chang
{2,2967,{pysm::nop,pyym::nop}},//誰 shui
{1,0,{pysm::j,pyym::ie}},//誱 jie
{1,0,{pysm::k,pyym::e}},//課 ke
{2,2968,{pysm::nop,pyym::nop}},//誳 qu
{1,0,{pysm::c,pyym::ong}},//誴 cong
{1,0,{pysm::x,pyym::iao}},//誵 xiao
{1,0,{pysm::s,pyym::ui}},//誶 sui
{1,0,{pysm::w,pyym::ang}},//誷 wang
{1,0,{pysm::x,pyym::ian}},//誸 xian
{1,0,{pysm::f,pyym::ei}},//誹 fei
{2,2969,{pysm::nop,pyym::nop}},//誺 chi
{1,0,{pysm::t,pyym::a}},//誻 ta
{1,0,{pysm::y,pyym::i}},//誼 yi
{2,2970,{pysm::nop,pyym::nop}},//誽 ni
{1,0,{pysm::y,pyym::in}},//誾 yin
{3,699,{pysm::nop,pyym::nop}},//調 diao
{2,2971,{pysm::nop,pyym::nop}},//諀 pi
{1,0,{pysm::zh,pyym::uo}},//諁 zhuo
{1,0,{pysm::ch,pyym::an}},//諂 chan
{1,0,{pysm::ch,pyym::en}},//諃 chen
{1,0,{pysm::zh,pyym::un}},//諄 zhun
{1,0,{pysm::j,pyym::i}},//諅 ji
{1,0,{pysm::q,pyym::i}},//諆 qi
{1,0,{pysm::t,pyym::an}},//談 tan
{1,0,{pysm::zh,pyym::ui}},//諈 zhui
{1,0,{pysm::w,pyym::ei}},//諉 wei
{1,0,{pysm::j,pyym::u}},//諊 ju
{1,0,{pysm::q,pyym::ing}},//請 qing
{1,0,{pysm::d,pyym::ong}},//諌 dong
{1,0,{pysm::zh,pyym::eng}},//諍 zheng
{5,42,{pysm::nop,pyym::nop}},//諎 ze
{2,2972,{pysm::nop,pyym::nop}},//諏 zou
{1,0,{pysm::q,pyym::ian}},//諐 qian
{1,0,{pysm::zh,pyym::uo}},//諑 zhuo
{1,0,{pysm::l,pyym::iang}},//諒 liang
{1,0,{pysm::j,pyym::ian}},//諓 jian
{2,2973,{pysm::nop,pyym::nop}},//諔 chu
{3,700,{pysm::nop,pyym::nop}},//諕 hao
{1,0,{pysm::l,pyym::un}},//論 lun
{2,2974,{pysm::nop,pyym::nop}},//諗 shen
{1,0,{pysm::b,pyym::iao}},//諘 biao
{1,0,{pysm::h,pyym::ua}},//諙 hua
{1,0,{pysm::p,pyym::ian}},//諚 pian
{1,0,{pysm::y,pyym::u}},//諛 yu
{2,2975,{pysm::nop,pyym::nop}},//諜 die
{1,0,{pysm::x,pyym::u}},//諝 xu
{1,0,{pysm::p,pyym::ian}},//諞 pian
{2,2976,{pysm::nop,pyym::nop}},//諟 shi
{1,0,{pysm::x,pyym::uan}},//諠 xuan
{1,0,{pysm::sh,pyym::i}},//諡 shi
{1,0,{pysm::h,pyym::un}},//諢 hun
{2,2977,{pysm::nop,pyym::nop}},//諣 hua
{1,0,{pysm::nop,pyym::e}},//諤 e
{1,0,{pysm::zh,pyym::ong}},//諥 zhong
{2,2978,{pysm::nop,pyym::nop}},//諦 di
{1,0,{pysm::x,pyym::ie}},//諧 xie
{1,0,{pysm::f,pyym::u}},//諨 fu
{1,0,{pysm::p,pyym::u}},//諩 pu
{1,0,{pysm::t,pyym::ing}},//諪 ting
{2,2979,{pysm::nop,pyym::nop}},//諫 jian
{1,0,{pysm::q,pyym::i}},//諬 qi
{2,2980,{pysm::nop,pyym::nop}},//諭 yu
{1,0,{pysm::z,pyym::i}},//諮 zi
{1,0,{pysm::zh,pyym::uan}},//諯 zhuan
{3,701,{pysm::nop,pyym::nop}},//諰 xi
{1,0,{pysm::h,pyym::ui}},//諱 hui
{1,0,{pysm::y,pyym::in}},//諲 yin
{2,2981,{pysm::nop,pyym::nop}},//諳 an
{2,2982,{pysm::nop,pyym::nop}},//諴 xian
{1,0,{pysm::n,pyym::an}},//諵 nan
{1,0,{pysm::ch,pyym::en}},//諶 chen
{1,0,{pysm::f,pyym::eng}},//諷 feng
{2,2983,{pysm::nop,pyym::nop}},//諸 zhu
{1,0,{pysm::y,pyym::ang}},//諹 yang
{1,0,{pysm::y,pyym::an}},//諺 yan
{1,0,{pysm::h,pyym::uang}},//諻 huang
{1,0,{pysm::x,pyym::uan}},//諼 xuan
{1,0,{pysm::g,pyym::e}},//諽 ge
{1,0,{pysm::n,pyym::uo}},//諾 nuo
{2,2984,{pysm::nop,pyym::nop}},//諿 qi
{1,0,{pysm::m,pyym::ou}},//謀 mou
{2,2985,{pysm::nop,pyym::nop}},//謁 ye
{1,0,{pysm::w,pyym::ei}},//謂 wei
{1,0,{pysm::x,pyym::ing}},//謃 xing
{1,0,{pysm::t,pyym::eng}},//謄 teng
{3,702,{pysm::nop,pyym::nop}},//謅 zhou
{1,0,{pysm::sh,pyym::an}},//謆 shan
{1,0,{pysm::j,pyym::ian}},//謇 jian
{2,2986,{pysm::nop,pyym::nop}},//謈 po
{4,142,{pysm::nop,pyym::nop}},//謉 kui
{1,0,{pysm::h,pyym::uang}},//謊 huang
{1,0,{pysm::h,pyym::uo}},//謋 huo
{1,0,{pysm::g,pyym::e}},//謌 ge
{2,2987,{pysm::nop,pyym::nop}},//謍 ying
{1,0,{pysm::m,pyym::i}},//謎 mi
{2,2988,{pysm::nop,pyym::nop}},//謏 xiao
{1,0,{pysm::m,pyym::i}},//謐 mi
{2,2989,{pysm::nop,pyym::nop}},//謑 xi
{1,0,{pysm::q,pyym::iang}},//謒 qiang
{2,2990,{pysm::nop,pyym::nop}},//謓 chen
{1,0,{pysm::x,pyym::ue}},//謔 xue
{2,2991,{pysm::nop,pyym::nop}},//謕 ti
{1,0,{pysm::s,pyym::u}},//謖 su
{1,0,{pysm::b,pyym::ang}},//謗 bang
{1,0,{pysm::ch,pyym::i}},//謘 chi
{2,2992,{pysm::nop,pyym::nop}},//謙 qian
{3,703,{pysm::nop,pyym::nop}},//謚 shi
{1,0,{pysm::j,pyym::iang}},//講 jiang
{2,2993,{pysm::nop,pyym::nop}},//謜 yuan
{1,0,{pysm::x,pyym::ie}},//謝 xie
{2,2994,{pysm::nop,pyym::nop}},//謞 he
{1,0,{pysm::t,pyym::ao}},//謟 tao
{1,0,{pysm::y,pyym::ao}},//謠 yao
{1,0,{pysm::y,pyym::ao}},//謡 yao
{1,0,{pysm::l,pyym::u}},//謢 lu
{2,2995,{pysm::nop,pyym::nop}},//謣 yu
{2,2996,{pysm::nop,pyym::nop}},//謤 biao
{1,0,{pysm::c,pyym::ong}},//謥 cong
{1,0,{pysm::q,pyym::ing}},//謦 qing
{1,0,{pysm::l,pyym::i}},//謧 li
{1,0,{pysm::m,pyym::o}},//謨 mo
{1,0,{pysm::m,pyym::o}},//謩 mo
{1,0,{pysm::sh,pyym::ang}},//謪 shang
{2,2997,{pysm::nop,pyym::nop}},//謫 zhe
{1,0,{pysm::m,pyym::iu}},//謬 miu
{1,0,{pysm::j,pyym::ian}},//謭 jian
{1,0,{pysm::z,pyym::e}},//謮 ze
{3,704,{pysm::nop,pyym::nop}},//謯 jie
{1,0,{pysm::l,pyym::ian}},//謰 lian
{2,2998,{pysm::nop,pyym::nop}},//謱 lou
{4,143,{pysm::nop,pyym::nop}},//謲 can
{2,2999,{pysm::nop,pyym::nop}},//謳 ou
{1,0,{pysm::g,pyym::un}},//謴 gun
{2,3000,{pysm::nop,pyym::nop}},//謵 xi
{3,705,{pysm::nop,pyym::nop}},//謶 zhuo
{1,0,{pysm::nop,pyym::ao}},//謷 ao
{1,0,{pysm::nop,pyym::ao}},//謸 ao
{1,0,{pysm::j,pyym::in}},//謹 jin
{1,0,{pysm::zh,pyym::e}},//謺 zhe
{2,3001,{pysm::nop,pyym::nop}},//謻 yi
{2,3002,{pysm::nop,pyym::nop}},//謼 hu
{1,0,{pysm::j,pyym::iang}},//謽 jiang
{1,0,{pysm::m,pyym::an}},//謾 man
{1,0,{pysm::ch,pyym::ao}},//謿 chao
{2,3003,{pysm::nop,pyym::nop}},//譀 han
{2,3004,{pysm::nop,pyym::nop}},//譁 hua
{2,3005,{pysm::nop,pyym::nop}},//譂 chan
{1,0,{pysm::x,pyym::u}},//譃 xu
{1,0,{pysm::z,pyym::eng}},//譄 zeng
{1,0,{pysm::s,pyym::e}},//譅 se
{1,0,{pysm::x,pyym::i}},//譆 xi
{1,0,{pysm::zh,pyym::a}},//譇 zha
{1,0,{pysm::d,pyym::ui}},//譈 dui
{1,0,{pysm::zh,pyym::eng}},//證 zheng
{2,3006,{pysm::nop,pyym::nop}},//譊 nao
{1,0,{pysm::l,pyym::an}},//譋 lan
{3,706,{pysm::nop,pyym::nop}},//譌 e
{1,0,{pysm::y,pyym::ing}},//譍 ying
{1,0,{pysm::j,pyym::ue}},//譎 jue
{1,0,{pysm::j,pyym::i}},//譏 ji
{1,0,{pysm::z,pyym::un}},//譐 zun
{2,3007,{pysm::nop,pyym::nop}},//譑 jiao
{1,0,{pysm::b,pyym::o}},//譒 bo
{1,0,{pysm::h,pyym::ui}},//譓 hui
{2,3008,{pysm::nop,pyym::nop}},//譔 zhuan
{2,3009,{pysm::nop,pyym::nop}},//譕 wu
{2,3010,{pysm::nop,pyym::nop}},//譖 zen
{1,0,{pysm::zh,pyym::a}},//譗 zha
{2,3011,{pysm::nop,pyym::nop}},//識 shi
{1,0,{pysm::q,pyym::iao}},//譙 qiao
{1,0,{pysm::t,pyym::an}},//譚 tan
{1,0,{pysm::z,pyym::en}},//譛 zen
{1,0,{pysm::p,pyym::u}},//譜 pu
{1,0,{pysm::sh,pyym::eng}},//譝 sheng
{1,0,{pysm::x,pyym::uan}},//譞 xuan
{1,0,{pysm::z,pyym::ao}},//譟 zao
{1,0,{pysm::t,pyym::an}},//譠 tan
{1,0,{pysm::d,pyym::ang}},//譡 dang
{1,0,{pysm::s,pyym::ui}},//譢 sui
{1,0,{pysm::x,pyym::ian}},//譣 xian
{1,0,{pysm::j,pyym::i}},//譤 ji
{1,0,{pysm::j,pyym::iao}},//譥 jiao
{1,0,{pysm::j,pyym::ing}},//警 jing
{2,3012,{pysm::nop,pyym::nop}},//譧 zhan
{2,3013,{pysm::nop,pyym::nop}},//譨 nang
{1,0,{pysm::y,pyym::i}},//譩 yi
{1,0,{pysm::nop,pyym::ai}},//譪 ai
{1,0,{pysm::zh,pyym::an}},//譫 zhan
{1,0,{pysm::p,pyym::i}},//譬 pi
{1,0,{pysm::h,pyym::ui}},//譭 hui
{3,707,{pysm::nop,pyym::nop}},//譮 hua
{1,0,{pysm::y,pyym::i}},//譯 yi
{1,0,{pysm::y,pyym::i}},//議 yi
{1,0,{pysm::sh,pyym::an}},//譱 shan
{1,0,{pysm::r,pyym::ang}},//譲 rang
{1,0,{pysm::n,pyym::ou}},//譳 nou
{1,0,{pysm::q,pyym::ian}},//譴 qian
{1,0,{pysm::d,pyym::ui}},//譵 dui
{1,0,{pysm::t,pyym::a}},//譶 ta
{1,0,{pysm::h,pyym::u}},//護 hu
{2,3014,{pysm::nop,pyym::nop}},//譸 zhou
{1,0,{pysm::h,pyym::ao}},//譹 hao
{3,708,{pysm::nop,pyym::nop}},//譺 ai
{1,0,{pysm::y,pyym::ing}},//譻 ying
{1,0,{pysm::j,pyym::ian}},//譼 jian
{1,0,{pysm::y,pyym::u}},//譽 yu
{1,0,{pysm::j,pyym::ian}},//譾 jian
{1,0,{pysm::h,pyym::ui}},//譿 hui
{2,3015,{pysm::nop,pyym::nop}},//讀 du
{1,0,{pysm::zh,pyym::e}},//讁 zhe
{1,0,{pysm::x,pyym::uan}},//讂 xuan
{1,0,{pysm::z,pyym::an}},//讃 zan
{1,0,{pysm::l,pyym::ei}},//讄 lei
{1,0,{pysm::sh,pyym::en}},//讅 shen
{1,0,{pysm::w,pyym::ei}},//讆 wei
{1,0,{pysm::ch,pyym::an}},//讇 chan
{1,0,{pysm::l,pyym::i}},//讈 li
{2,3016,{pysm::nop,pyym::nop}},//讉 yi
{1,0,{pysm::b,pyym::ian}},//變 bian
{1,0,{pysm::zh,pyym::e}},//讋 zhe
{1,0,{pysm::y,pyym::an}},//讌 yan
{1,0,{pysm::nop,pyym::e}},//讍 e
{1,0,{pysm::ch,pyym::ou}},//讎 chou
{1,0,{pysm::w,pyym::ei}},//讏 wei
{1,0,{pysm::ch,pyym::ou}},//讐 chou
{1,0,{pysm::y,pyym::ao}},//讑 yao
{1,0,{pysm::ch,pyym::an}},//讒 chan
{1,0,{pysm::r,pyym::ang}},//讓 rang
{1,0,{pysm::y,pyym::in}},//讔 yin
{1,0,{pysm::l,pyym::an}},//讕 lan
{2,3017,{pysm::nop,pyym::nop}},//讖 chen
{1,0,{pysm::x,pyym::ie}},//讗 xie
{1,0,{pysm::n,pyym::ie}},//讘 nie
{1,0,{pysm::h,pyym::uan}},//讙 huan
{1,0,{pysm::z,pyym::an}},//讚 zan
{1,0,{pysm::y,pyym::i}},//讛 yi
{1,0,{pysm::d,pyym::ang}},//讜 dang
{1,0,{pysm::zh,pyym::an}},//讝 zhan
{1,0,{pysm::y,pyym::an}},//讞 yan
{1,0,{pysm::d,pyym::u}},//讟 du
{1,0,{pysm::y,pyym::an}},//讠 yan
{1,0,{pysm::j,pyym::i}},//计 ji
{1,0,{pysm::d,pyym::ing}},//订 ding
{1,0,{pysm::f,pyym::u}},//讣 fu
{1,0,{pysm::r,pyym::en}},//认 ren
{1,0,{pysm::j,pyym::i}},//讥 ji
{1,0,{pysm::j,pyym::ie}},//讦 jie
{1,0,{pysm::h,pyym::ong}},//讧 hong
{1,0,{pysm::t,pyym::ao}},//讨 tao
{1,0,{pysm::r,pyym::ang}},//让 rang
{1,0,{pysm::sh,pyym::an}},//讪 shan
{1,0,{pysm::q,pyym::i}},//讫 qi
{1,0,{pysm::t,pyym::uo}},//讬 tuo
{1,0,{pysm::x,pyym::un}},//训 xun
{1,0,{pysm::y,pyym::i}},//议 yi
{1,0,{pysm::x,pyym::un}},//讯 xun
{1,0,{pysm::j,pyym::i}},//记 ji
{1,0,{pysm::r,pyym::en}},//讱 ren
{1,0,{pysm::j,pyym::iang}},//讲 jiang
{1,0,{pysm::h,pyym::ui}},//讳 hui
{1,0,{pysm::nop,pyym::ou}},//讴 ou
{1,0,{pysm::j,pyym::u}},//讵 ju
{1,0,{pysm::y,pyym::a}},//讶 ya
{1,0,{pysm::n,pyym::e}},//讷 ne
{2,3018,{pysm::nop,pyym::nop}},//许 xu
{1,0,{pysm::nop,pyym::e}},//讹 e
{1,0,{pysm::l,pyym::un}},//论 lun
{1,0,{pysm::x,pyym::iong}},//讻 xiong
{1,0,{pysm::s,pyym::ong}},//讼 song
{1,0,{pysm::f,pyym::eng}},//讽 feng
{1,0,{pysm::sh,pyym::e}},//设 she
{1,0,{pysm::f,pyym::ang}},//访 fang
{1,0,{pysm::j,pyym::ue}},//诀 jue
{1,0,{pysm::zh,pyym::eng}},//证 zheng
{1,0,{pysm::g,pyym::u}},//诂 gu
{1,0,{pysm::h,pyym::e}},//诃 he
{1,0,{pysm::p,pyym::ing}},//评 ping
{1,0,{pysm::z,pyym::u}},//诅 zu
{2,3019,{pysm::nop,pyym::nop}},//识 shi
{1,0,{pysm::x,pyym::iong}},//诇 xiong
{1,0,{pysm::zh,pyym::a}},//诈 zha
{1,0,{pysm::s,pyym::u}},//诉 su
{1,0,{pysm::zh,pyym::en}},//诊 zhen
{1,0,{pysm::d,pyym::i}},//诋 di
{1,0,{pysm::zh,pyym::ou}},//诌 zhou
{1,0,{pysm::c,pyym::i}},//词 ci
{1,0,{pysm::q,pyym::u}},//诎 qu
{1,0,{pysm::zh,pyym::ao}},//诏 zhao
{1,0,{pysm::b,pyym::i}},//诐 bi
{1,0,{pysm::y,pyym::i}},//译 yi
{1,0,{pysm::y,pyym::i}},//诒 yi
{1,0,{pysm::k,pyym::uang}},//诓 kuang
{1,0,{pysm::l,pyym::ei}},//诔 lei
{1,0,{pysm::sh,pyym::i}},//试 shi
{1,0,{pysm::g,pyym::ua}},//诖 gua
{1,0,{pysm::sh,pyym::i}},//诗 shi
{2,3020,{pysm::nop,pyym::nop}},//诘 ji
{1,0,{pysm::h,pyym::ui}},//诙 hui
{1,0,{pysm::ch,pyym::eng}},//诚 cheng
{1,0,{pysm::zh,pyym::u}},//诛 zhu
{1,0,{pysm::sh,pyym::en}},//诜 shen
{1,0,{pysm::h,pyym::ua}},//话 hua
{1,0,{pysm::d,pyym::an}},//诞 dan
{1,0,{pysm::g,pyym::ou}},//诟 gou
{1,0,{pysm::q,pyym::uan}},//诠 quan
{1,0,{pysm::g,pyym::ui}},//诡 gui
{1,0,{pysm::x,pyym::un}},//询 xun
{1,0,{pysm::y,pyym::i}},//诣 yi
{1,0,{pysm::zh,pyym::eng}},//诤 zheng
{1,0,{pysm::g,pyym::ai}},//该 gai
{1,0,{pysm::x,pyym::iang}},//详 xiang
{1,0,{pysm::ch,pyym::a}},//诧 cha
{1,0,{pysm::h,pyym::un}},//诨 hun
{1,0,{pysm::x,pyym::u}},//诩 xu
{1,0,{pysm::zh,pyym::ou}},//诪 zhou
{1,0,{pysm::j,pyym::ie}},//诫 jie
{1,0,{pysm::w,pyym::u}},//诬 wu
{1,0,{pysm::y,pyym::u}},//语 yu
{1,0,{pysm::q,pyym::iao}},//诮 qiao
{1,0,{pysm::w,pyym::u}},//误 wu
{1,0,{pysm::g,pyym::ao}},//诰 gao
{1,0,{pysm::y,pyym::ou}},//诱 you
{1,0,{pysm::h,pyym::ui}},//诲 hui
{1,0,{pysm::k,pyym::uang}},//诳 kuang
{3,709,{pysm::nop,pyym::nop}},//说 shuo
{1,0,{pysm::s,pyym::ong}},//诵 song
{1,0,{pysm::nop,pyym::ei}},//诶 ei
{1,0,{pysm::q,pyym::ing}},//请 qing
{1,0,{pysm::zh,pyym::u}},//诸 zhu
{1,0,{pysm::z,pyym::ou}},//诹 zou
{1,0,{pysm::n,pyym::uo}},//诺 nuo
{2,3021,{pysm::nop,pyym::nop}},//读 du
{1,0,{pysm::zh,pyym::uo}},//诼 zhuo
{1,0,{pysm::f,pyym::ei}},//诽 fei
{1,0,{pysm::k,pyym::e}},//课 ke
{1,0,{pysm::w,pyym::ei}},//诿 wei
{1,0,{pysm::y,pyym::u}},//谀 yu
{2,3022,{pysm::nop,pyym::nop}},//谁 shui
{1,0,{pysm::sh,pyym::en}},//谂 shen
{2,3023,{pysm::nop,pyym::nop}},//调 diao
{1,0,{pysm::ch,pyym::an}},//谄 chan
{1,0,{pysm::l,pyym::iang}},//谅 liang
{1,0,{pysm::zh,pyym::un}},//谆 zhun
{1,0,{pysm::s,pyym::ui}},//谇 sui
{1,0,{pysm::t,pyym::an}},//谈 tan
{1,0,{pysm::sh,pyym::en}},//谉 shen
{1,0,{pysm::y,pyym::i}},//谊 yi
{1,0,{pysm::m,pyym::ou}},//谋 mou
{1,0,{pysm::ch,pyym::en}},//谌 chen
{1,0,{pysm::d,pyym::ie}},//谍 die
{1,0,{pysm::h,pyym::uang}},//谎 huang
{1,0,{pysm::j,pyym::ian}},//谏 jian
{1,0,{pysm::x,pyym::ie}},//谐 xie
{1,0,{pysm::x,pyym::ue}},//谑 xue
{1,0,{pysm::y,pyym::e}},//谒 ye
{1,0,{pysm::w,pyym::ei}},//谓 wei
{1,0,{pysm::nop,pyym::e}},//谔 e
{1,0,{pysm::y,pyym::u}},//谕 yu
{1,0,{pysm::x,pyym::uan}},//谖 xuan
{1,0,{pysm::ch,pyym::an}},//谗 chan
{1,0,{pysm::z,pyym::i}},//谘 zi
{1,0,{pysm::nop,pyym::an}},//谙 an
{1,0,{pysm::y,pyym::an}},//谚 yan
{1,0,{pysm::d,pyym::i}},//谛 di
{2,3024,{pysm::nop,pyym::nop}},//谜 mi
{1,0,{pysm::p,pyym::ian}},//谝 pian
{1,0,{pysm::x,pyym::u}},//谞 xu
{1,0,{pysm::m,pyym::o}},//谟 mo
{1,0,{pysm::d,pyym::ang}},//谠 dang
{1,0,{pysm::s,pyym::u}},//谡 su
{1,0,{pysm::x,pyym::ie}},//谢 xie
{1,0,{pysm::y,pyym::ao}},//谣 yao
{1,0,{pysm::b,pyym::ang}},//谤 bang
{1,0,{pysm::sh,pyym::i}},//谥 shi
{1,0,{pysm::q,pyym::ian}},//谦 qian
{1,0,{pysm::m,pyym::i}},//谧 mi
{1,0,{pysm::j,pyym::in}},//谨 jin
{1,0,{pysm::m,pyym::an}},//谩 man
{1,0,{pysm::zh,pyym::e}},//谪 zhe
{1,0,{pysm::j,pyym::ian}},//谫 jian
{1,0,{pysm::m,pyym::iu}},//谬 miu
{1,0,{pysm::t,pyym::an}},//谭 tan
{1,0,{pysm::z,pyym::en}},//谮 zen
{1,0,{pysm::q,pyym::iao}},//谯 qiao
{1,0,{pysm::l,pyym::an}},//谰 lan
{1,0,{pysm::p,pyym::u}},//谱 pu
{1,0,{pysm::j,pyym::ue}},//谲 jue
{1,0,{pysm::y,pyym::an}},//谳 yan
{1,0,{pysm::q,pyym::ian}},//谴 qian
{1,0,{pysm::zh,pyym::an}},//谵 zhan
{1,0,{pysm::ch,pyym::en}},//谶 chen
{3,710,{pysm::nop,pyym::nop}},//谷 gu
{1,0,{pysm::q,pyym::ian}},//谸 qian
{1,0,{pysm::h,pyym::ong}},//谹 hong
{1,0,{pysm::x,pyym::ia}},//谺 xia
{1,0,{pysm::j,pyym::i}},//谻 ji
{1,0,{pysm::h,pyym::ong}},//谼 hong
{1,0,{pysm::h,pyym::an}},//谽 han
{2,3025,{pysm::nop,pyym::nop}},//谾 hong
{2,3026,{pysm::nop,pyym::nop}},//谿 xi
{1,0,{pysm::x,pyym::i}},//豀 xi
{2,3027,{pysm::nop,pyym::nop}},//豁 huo
{1,0,{pysm::l,pyym::iao}},//豂 liao
{2,3028,{pysm::nop,pyym::nop}},//豃 han
{1,0,{pysm::d,pyym::u}},//豄 du
{1,0,{pysm::l,pyym::ong}},//豅 long
{1,0,{pysm::d,pyym::ou}},//豆 dou
{1,0,{pysm::j,pyym::iang}},//豇 jiang
{2,3029,{pysm::nop,pyym::nop}},//豈 qi
{2,3030,{pysm::nop,pyym::nop}},//豉 shi
{2,3031,{pysm::nop,pyym::nop}},//豊 li
{1,0,{pysm::d,pyym::eng}},//豋 deng
{1,0,{pysm::w,pyym::an}},//豌 wan
{2,3032,{pysm::nop,pyym::nop}},//豍 bi
{1,0,{pysm::sh,pyym::u}},//豎 shu
{1,0,{pysm::x,pyym::ian}},//豏 xian
{1,0,{pysm::f,pyym::eng}},//豐 feng
{1,0,{pysm::zh,pyym::i}},//豑 zhi
{1,0,{pysm::zh,pyym::i}},//豒 zhi
{1,0,{pysm::y,pyym::an}},//豓 yan
{1,0,{pysm::y,pyym::an}},//豔 yan
{1,0,{pysm::sh,pyym::i}},//豕 shi
{1,0,{pysm::ch,pyym::u}},//豖 chu
{1,0,{pysm::h,pyym::ui}},//豗 hui
{1,0,{pysm::t,pyym::un}},//豘 tun
{1,0,{pysm::y,pyym::i}},//豙 yi
{2,3033,{pysm::nop,pyym::nop}},//豚 tun
{1,0,{pysm::y,pyym::i}},//豛 yi
{1,0,{pysm::j,pyym::ian}},//豜 jian
{1,0,{pysm::b,pyym::a}},//豝 ba
{1,0,{pysm::h,pyym::ou}},//豞 hou
{1,0,{pysm::nop,pyym::e}},//豟 e
{1,0,{pysm::ch,pyym::u}},//豠 chu
{1,0,{pysm::x,pyym::iang}},//象 xiang
{1,0,{pysm::h,pyym::uan}},//豢 huan
{2,3034,{pysm::nop,pyym::nop}},//豣 jian
{2,3035,{pysm::nop,pyym::nop}},//豤 ken
{1,0,{pysm::g,pyym::ai}},//豥 gai
{1,0,{pysm::j,pyym::u}},//豦 ju
{2,3036,{pysm::nop,pyym::nop}},//豧 fu
{1,0,{pysm::x,pyym::i}},//豨 xi
{2,3037,{pysm::nop,pyym::nop}},//豩 bin
{1,0,{pysm::h,pyym::ao}},//豪 hao
{3,711,{pysm::nop,pyym::nop}},//豫 yu
{1,0,{pysm::zh,pyym::u}},//豬 zhu
{1,0,{pysm::j,pyym::ia}},//豭 jia
{1,0,{pysm::f,pyym::en}},//豮 fen
{1,0,{pysm::x,pyym::i}},//豯 xi
{4,144,{pysm::nop,pyym::nop}},//豰 bo
{1,0,{pysm::w,pyym::en}},//豱 wen
{1,0,{pysm::h,pyym::uan}},//豲 huan
{2,3038,{pysm::nop,pyym::nop}},//豳 bin
{1,0,{pysm::d,pyym::i}},//豴 di
{1,0,{pysm::z,pyym::ong}},//豵 zong
{1,0,{pysm::f,pyym::en}},//豶 fen
{1,0,{pysm::y,pyym::i}},//豷 yi
{2,3039,{pysm::nop,pyym::nop}},//豸 zhi
{1,0,{pysm::b,pyym::ao}},//豹 bao
{1,0,{pysm::ch,pyym::ai}},//豺 chai
{1,0,{pysm::nop,pyym::an}},//豻 an
{1,0,{pysm::p,pyym::i}},//豼 pi
{1,0,{pysm::n,pyym::a}},//豽 na
{1,0,{pysm::p,pyym::i}},//豾 pi
{1,0,{pysm::g,pyym::ou}},//豿 gou
{2,3040,{pysm::nop,pyym::nop}},//貀 na
{1,0,{pysm::y,pyym::ou}},//貁 you
{1,0,{pysm::d,pyym::iao}},//貂 diao
{1,0,{pysm::m,pyym::o}},//貃 mo
{1,0,{pysm::s,pyym::i}},//貄 si
{1,0,{pysm::x,pyym::iu}},//貅 xiu
{1,0,{pysm::h,pyym::uan}},//貆 huan
{3,712,{pysm::nop,pyym::nop}},//貇 kun
{2,3041,{pysm::nop,pyym::nop}},//貈 he
{4,145,{pysm::nop,pyym::nop}},//貉 hao
{2,3042,{pysm::nop,pyym::nop}},//貊 mo
{1,0,{pysm::nop,pyym::an}},//貋 an
{2,3043,{pysm::nop,pyym::nop}},//貌 mao
{3,713,{pysm::nop,pyym::nop}},//貍 li
{1,0,{pysm::n,pyym::i}},//貎 ni
{1,0,{pysm::b,pyym::i}},//貏 bi
{1,0,{pysm::y,pyym::u}},//貐 yu
{1,0,{pysm::j,pyym::ia}},//貑 jia
{1,0,{pysm::t,pyym::uan}},//貒 tuan
{1,0,{pysm::m,pyym::ao}},//貓 mao
{1,0,{pysm::p,pyym::i}},//貔 pi
{1,0,{pysm::x,pyym::i}},//貕 xi
{1,0,{pysm::y,pyym::i}},//貖 yi
{2,3044,{pysm::nop,pyym::nop}},//貗 ju
{1,0,{pysm::m,pyym::o}},//貘 mo
{1,0,{pysm::ch,pyym::u}},//貙 chu
{1,0,{pysm::t,pyym::an}},//貚 tan
{1,0,{pysm::h,pyym::uan}},//貛 huan
{1,0,{pysm::j,pyym::ue}},//貜 jue
{1,0,{pysm::b,pyym::ei}},//貝 bei
{2,3045,{pysm::nop,pyym::nop}},//貞 zhen
{1,0,{pysm::y,pyym::uan}},//貟 yuan
{1,0,{pysm::f,pyym::u}},//負 fu
{1,0,{pysm::c,pyym::ai}},//財 cai
{1,0,{pysm::g,pyym::ong}},//貢 gong
{1,0,{pysm::t,pyym::e}},//貣 te
{1,0,{pysm::y,pyym::i}},//貤 yi
{1,0,{pysm::h,pyym::ang}},//貥 hang
{1,0,{pysm::w,pyym::an}},//貦 wan
{1,0,{pysm::p,pyym::in}},//貧 pin
{1,0,{pysm::h,pyym::uo}},//貨 huo
{1,0,{pysm::f,pyym::an}},//販 fan
{1,0,{pysm::t,pyym::an}},//貪 tan
{2,3046,{pysm::nop,pyym::nop}},//貫 guan
{2,3047,{pysm::nop,pyym::nop}},//責 ze
{1,0,{pysm::zh,pyym::i}},//貭 zhi
{1,0,{pysm::nop,pyym::er}},//貮 er
{1,0,{pysm::zh,pyym::u}},//貯 zhu
{1,0,{pysm::sh,pyym::i}},//貰 shi
{1,0,{pysm::b,pyym::i}},//貱 bi
{1,0,{pysm::z,pyym::i}},//貲 zi
{1,0,{pysm::nop,pyym::er}},//貳 er
{1,0,{pysm::g,pyym::ui}},//貴 gui
{1,0,{pysm::p,pyym::ian}},//貵 pian
{2,3048,{pysm::nop,pyym::nop}},//貶 bian
{1,0,{pysm::m,pyym::ai}},//買 mai
{2,3049,{pysm::nop,pyym::nop}},//貸 dai
{1,0,{pysm::sh,pyym::eng}},//貹 sheng
{1,0,{pysm::k,pyym::uang}},//貺 kuang
{3,714,{pysm::nop,pyym::nop}},//費 fei
{1,0,{pysm::t,pyym::ie}},//貼 tie
{1,0,{pysm::y,pyym::i}},//貽 yi
{1,0,{pysm::ch,pyym::i}},//貾 chi
{1,0,{pysm::m,pyym::ao}},//貿 mao
{1,0,{pysm::h,pyym::e}},//賀 he
{7,4,{pysm::nop,pyym::nop}},//賁 bi
{1,0,{pysm::l,pyym::u}},//賂 lu
{1,0,{pysm::l,pyym::in}},//賃 lin
{1,0,{pysm::h,pyym::ui}},//賄 hui
{1,0,{pysm::g,pyym::ai}},//賅 gai
{1,0,{pysm::p,pyym::ian}},//賆 pian
{1,0,{pysm::z,pyym::i}},//資 zi
{2,3050,{pysm::nop,pyym::nop}},//賈 jia
{1,0,{pysm::x,pyym::u}},//賉 xu
{1,0,{pysm::z,pyym::ei}},//賊 zei
{1,0,{pysm::j,pyym::iao}},//賋 jiao
{1,0,{pysm::g,pyym::ai}},//賌 gai
{1,0,{pysm::z,pyym::ang}},//賍 zang
{1,0,{pysm::j,pyym::ian}},//賎 jian
{1,0,{pysm::y,pyym::ing}},//賏 ying
{1,0,{pysm::x,pyym::un}},//賐 xun
{1,0,{pysm::zh,pyym::en}},//賑 zhen
{2,3051,{pysm::nop,pyym::nop}},//賒 she
{1,0,{pysm::b,pyym::in}},//賓 bin
{1,0,{pysm::b,pyym::in}},//賔 bin
{1,0,{pysm::q,pyym::iu}},//賕 qiu
{1,0,{pysm::sh,pyym::e}},//賖 she
{1,0,{pysm::ch,pyym::uan}},//賗 chuan
{1,0,{pysm::z,pyym::ang}},//賘 zang
{1,0,{pysm::zh,pyym::ou}},//賙 zhou
{1,0,{pysm::l,pyym::ai}},//賚 lai
{1,0,{pysm::z,pyym::an}},//賛 zan
{1,0,{pysm::c,pyym::i}},//賜 ci
{1,0,{pysm::ch,pyym::en}},//賝 chen
{1,0,{pysm::sh,pyym::ang}},//賞 shang
{1,0,{pysm::t,pyym::ian}},//賟 tian
{1,0,{pysm::p,pyym::ei}},//賠 pei
{1,0,{pysm::g,pyym::eng}},//賡 geng
{1,0,{pysm::x,pyym::ian}},//賢 xian
{1,0,{pysm::m,pyym::ai}},//賣 mai
{1,0,{pysm::j,pyym::ian}},//賤 jian
{1,0,{pysm::s,pyym::ui}},//賥 sui
{1,0,{pysm::f,pyym::u}},//賦 fu
{1,0,{pysm::t,pyym::an}},//賧 tan
{1,0,{pysm::c,pyym::ong}},//賨 cong
{1,0,{pysm::c,pyym::ong}},//賩 cong
{1,0,{pysm::zh,pyym::i}},//質 zhi
{1,0,{pysm::j,pyym::i}},//賫 ji
{1,0,{pysm::zh,pyym::ang}},//賬 zhang
{1,0,{pysm::d,pyym::u}},//賭 du
{1,0,{pysm::j,pyym::in}},//賮 jin
{1,0,{pysm::x,pyym::iong}},//賯 xiong
{1,0,{pysm::ch,pyym::un}},//賰 chun
{1,0,{pysm::y,pyym::un}},//賱 yun
{1,0,{pysm::b,pyym::ao}},//賲 bao
{1,0,{pysm::z,pyym::ai}},//賳 zai
{1,0,{pysm::l,pyym::ai}},//賴 lai
{1,0,{pysm::f,pyym::eng}},//賵 feng
{1,0,{pysm::c,pyym::ang}},//賶 cang
{1,0,{pysm::j,pyym::i}},//賷 ji
{1,0,{pysm::sh,pyym::eng}},//賸 sheng
{2,3052,{pysm::nop,pyym::nop}},//賹 yi
{2,3053,{pysm::nop,pyym::nop}},//賺 zhuan
{1,0,{pysm::f,pyym::u}},//賻 fu
{1,0,{pysm::g,pyym::ou}},//購 gou
{1,0,{pysm::s,pyym::ai}},//賽 sai
{1,0,{pysm::z,pyym::e}},//賾 ze
{1,0,{pysm::l,pyym::iao}},//賿 liao
{1,0,{pysm::y,pyym::i}},//贀 yi
{1,0,{pysm::b,pyym::ai}},//贁 bai
{1,0,{pysm::ch,pyym::en}},//贂 chen
{1,0,{pysm::w,pyym::an}},//贃 wan
{1,0,{pysm::zh,pyym::i}},//贄 zhi
{1,0,{pysm::zh,pyym::ui}},//贅 zhui
{1,0,{pysm::b,pyym::iao}},//贆 biao
{2,3054,{pysm::nop,pyym::nop}},//贇 yun
{1,0,{pysm::z,pyym::eng}},//贈 zeng
{1,0,{pysm::d,pyym::an}},//贉 dan
{1,0,{pysm::z,pyym::an}},//贊 zan
{1,0,{pysm::y,pyym::an}},//贋 yan
{1,0,{pysm::p,pyym::u}},//贌 pu
{2,3055,{pysm::nop,pyym::nop}},//贍 shan
{1,0,{pysm::w,pyym::an}},//贎 wan
{1,0,{pysm::y,pyym::ing}},//贏 ying
{1,0,{pysm::j,pyym::in}},//贐 jin
{1,0,{pysm::g,pyym::an}},//贑 gan
{1,0,{pysm::x,pyym::ian}},//贒 xian
{1,0,{pysm::z,pyym::ang}},//贓 zang
{1,0,{pysm::b,pyym::i}},//贔 bi
{1,0,{pysm::d,pyym::u}},//贕 du
{1,0,{pysm::sh,pyym::u}},//贖 shu
{1,0,{pysm::y,pyym::an}},//贗 yan
{1,0,{pysm::sh,pyym::ang}},//贘 shang
{1,0,{pysm::x,pyym::uan}},//贙 xuan
{1,0,{pysm::l,pyym::ong}},//贚 long
{3,715,{pysm::nop,pyym::nop}},//贛 gan
{1,0,{pysm::z,pyym::ang}},//贜 zang
{1,0,{pysm::b,pyym::ei}},//贝 bei
{1,0,{pysm::zh,pyym::en}},//贞 zhen
{1,0,{pysm::f,pyym::u}},//负 fu
{1,0,{pysm::y,pyym::uan}},//贠 yuan
{1,0,{pysm::g,pyym::ong}},//贡 gong
{1,0,{pysm::c,pyym::ai}},//财 cai
{1,0,{pysm::z,pyym::e}},//责 ze
{1,0,{pysm::x,pyym::ian}},//贤 xian
{1,0,{pysm::b,pyym::ai}},//败 bai
{1,0,{pysm::zh,pyym::ang}},//账 zhang
{1,0,{pysm::h,pyym::uo}},//货 huo
{1,0,{pysm::zh,pyym::i}},//质 zhi
{1,0,{pysm::f,pyym::an}},//贩 fan
{1,0,{pysm::t,pyym::an}},//贪 tan
{1,0,{pysm::p,pyym::in}},//贫 pin
{1,0,{pysm::b,pyym::ian}},//贬 bian
{1,0,{pysm::g,pyym::ou}},//购 gou
{1,0,{pysm::zh,pyym::u}},//贮 zhu
{1,0,{pysm::g,pyym::uan}},//贯 guan
{1,0,{pysm::nop,pyym::er}},//贰 er
{1,0,{pysm::j,pyym::ian}},//贱 jian
{2,3056,{pysm::nop,pyym::nop}},//贲 ben
{1,0,{pysm::sh,pyym::i}},//贳 shi
{1,0,{pysm::t,pyym::ie}},//贴 tie
{1,0,{pysm::g,pyym::ui}},//贵 gui
{1,0,{pysm::k,pyym::uang}},//贶 kuang
{1,0,{pysm::d,pyym::ai}},//贷 dai
{1,0,{pysm::m,pyym::ao}},//贸 mao
{1,0,{pysm::f,pyym::ei}},//费 fei
{1,0,{pysm::h,pyym::e}},//贺 he
{1,0,{pysm::y,pyym::i}},//贻 yi
{1,0,{pysm::z,pyym::ei}},//贼 zei
{1,0,{pysm::zh,pyym::i}},//贽 zhi
{2,3057,{pysm::nop,pyym::nop}},//贾 jia
{1,0,{pysm::h,pyym::ui}},//贿 hui
{1,0,{pysm::z,pyym::i}},//赀 zi
{1,0,{pysm::l,pyym::in}},//赁 lin
{1,0,{pysm::l,pyym::u}},//赂 lu
{1,0,{pysm::z,pyym::ang}},//赃 zang
{1,0,{pysm::z,pyym::i}},//资 zi
{1,0,{pysm::g,pyym::ai}},//赅 gai
{1,0,{pysm::j,pyym::in}},//赆 jin
{1,0,{pysm::q,pyym::iu}},//赇 qiu
{1,0,{pysm::zh,pyym::en}},//赈 zhen
{1,0,{pysm::l,pyym::ai}},//赉 lai
{1,0,{pysm::sh,pyym::e}},//赊 she
{1,0,{pysm::f,pyym::u}},//赋 fu
{1,0,{pysm::d,pyym::u}},//赌 du
{1,0,{pysm::j,pyym::i}},//赍 ji
{1,0,{pysm::sh,pyym::u}},//赎 shu
{1,0,{pysm::sh,pyym::ang}},//赏 shang
{1,0,{pysm::c,pyym::i}},//赐 ci
{1,0,{pysm::b,pyym::i}},//赑 bi
{1,0,{pysm::zh,pyym::ou}},//赒 zhou
{1,0,{pysm::g,pyym::eng}},//赓 geng
{1,0,{pysm::p,pyym::ei}},//赔 pei
{1,0,{pysm::d,pyym::an}},//赕 dan
{1,0,{pysm::l,pyym::ai}},//赖 lai
{1,0,{pysm::f,pyym::eng}},//赗 feng
{1,0,{pysm::zh,pyym::ui}},//赘 zhui
{1,0,{pysm::f,pyym::u}},//赙 fu
{2,3058,{pysm::nop,pyym::nop}},//赚 zhuan
{1,0,{pysm::s,pyym::ai}},//赛 sai
{1,0,{pysm::z,pyym::e}},//赜 ze
{1,0,{pysm::y,pyym::an}},//赝 yan
{1,0,{pysm::z,pyym::an}},//赞 zan
{1,0,{pysm::y,pyym::un}},//赟 yun
{1,0,{pysm::z,pyym::eng}},//赠 zeng
{1,0,{pysm::sh,pyym::an}},//赡 shan
{1,0,{pysm::y,pyym::ing}},//赢 ying
{1,0,{pysm::g,pyym::an}},//赣 gan
{1,0,{pysm::ch,pyym::i}},//赤 chi
{1,0,{pysm::x,pyym::i}},//赥 xi
{2,3059,{pysm::nop,pyym::nop}},//赦 she
{1,0,{pysm::n,pyym::an}},//赧 nan
{2,3060,{pysm::nop,pyym::nop}},//赨 tong
{1,0,{pysm::x,pyym::i}},//赩 xi
{1,0,{pysm::ch,pyym::eng}},//赪 cheng
{2,3061,{pysm::nop,pyym::nop}},//赫 he
{1,0,{pysm::ch,pyym::eng}},//赬 cheng
{1,0,{pysm::zh,pyym::e}},//赭 zhe
{1,0,{pysm::x,pyym::ia}},//赮 xia
{1,0,{pysm::t,pyym::ang}},//赯 tang
{1,0,{pysm::z,pyym::ou}},//走 zou
{1,0,{pysm::z,pyym::ou}},//赱 zou
{1,0,{pysm::l,pyym::i}},//赲 li
{1,0,{pysm::j,pyym::iu}},//赳 jiu
{1,0,{pysm::f,pyym::u}},//赴 fu
{1,0,{pysm::zh,pyym::ao}},//赵 zhao
{2,3062,{pysm::nop,pyym::nop}},//赶 gan
{1,0,{pysm::q,pyym::i}},//起 qi
{1,0,{pysm::sh,pyym::an}},//赸 shan
{1,0,{pysm::q,pyym::iong}},//赹 qiong
{2,3063,{pysm::nop,pyym::nop}},//赺 yin
{1,0,{pysm::x,pyym::ian}},//赻 xian
{1,0,{pysm::z,pyym::i}},//赼 zi
{2,3064,{pysm::nop,pyym::nop}},//赽 jue
{1,0,{pysm::q,pyym::in}},//赾 qin
{2,3065,{pysm::nop,pyym::nop}},//赿 chi
{1,0,{pysm::c,pyym::i}},//趀 ci
{3,716,{pysm::nop,pyym::nop}},//趁 chen
{1,0,{pysm::ch,pyym::en}},//趂 chen
{2,3066,{pysm::nop,pyym::nop}},//趃 die
{2,3067,{pysm::nop,pyym::nop}},//趄 ju
{2,3068,{pysm::nop,pyym::nop}},//超 chao
{1,0,{pysm::d,pyym::i}},//趆 di
{1,0,{pysm::x,pyym::i}},//趇 xi
{1,0,{pysm::zh,pyym::an}},//趈 zhan
{2,3069,{pysm::nop,pyym::nop}},//趉 jue
{2,3070,{pysm::nop,pyym::nop}},//越 yue
{1,0,{pysm::q,pyym::u}},//趋 qu
{2,3071,{pysm::nop,pyym::nop}},//趌 ji
{2,3072,{pysm::nop,pyym::nop}},//趍 chi
{1,0,{pysm::ch,pyym::u}},//趎 chu
{2,3073,{pysm::nop,pyym::nop}},//趏 gua
{2,3074,{pysm::nop,pyym::nop}},//趐 xue
{2,3075,{pysm::nop,pyym::nop}},//趑 zi
{1,0,{pysm::t,pyym::iao}},//趒 tiao
{1,0,{pysm::d,pyym::uo}},//趓 duo
{1,0,{pysm::l,pyym::ie}},//趔 lie
{1,0,{pysm::g,pyym::an}},//趕 gan
{1,0,{pysm::s,pyym::uo}},//趖 suo
{1,0,{pysm::c,pyym::u}},//趗 cu
{1,0,{pysm::x,pyym::i}},//趘 xi
{2,3076,{pysm::nop,pyym::nop}},//趙 zhao
{1,0,{pysm::s,pyym::u}},//趚 su
{1,0,{pysm::y,pyym::in}},//趛 yin
{3,717,{pysm::nop,pyym::nop}},//趜 ju
{1,0,{pysm::j,pyym::ian}},//趝 jian
{3,718,{pysm::nop,pyym::nop}},//趞 que
{3,719,{pysm::nop,pyym::nop}},//趟 tang
{4,146,{pysm::nop,pyym::nop}},//趠 chuo
{3,720,{pysm::nop,pyym::nop}},//趡 cui
{1,0,{pysm::l,pyym::u}},//趢 lu
{4,147,{pysm::nop,pyym::nop}},//趣 qu
{1,0,{pysm::d,pyym::ang}},//趤 dang
{2,3077,{pysm::nop,pyym::nop}},//趥 qiu
{1,0,{pysm::z,pyym::i}},//趦 zi
{1,0,{pysm::t,pyym::i}},//趧 ti
{3,721,{pysm::nop,pyym::nop}},//趨 qu
{1,0,{pysm::ch,pyym::i}},//趩 chi
{2,3078,{pysm::nop,pyym::nop}},//趪 huang
{3,722,{pysm::nop,pyym::nop}},//趫 qiao
{1,0,{pysm::q,pyym::iao}},//趬 qiao
{1,0,{pysm::j,pyym::iao}},//趭 jiao
{1,0,{pysm::z,pyym::ao}},//趮 zao
{3,723,{pysm::nop,pyym::nop}},//趯 ti
{1,0,{pysm::nop,pyym::er}},//趰 er
{1,0,{pysm::z,pyym::an}},//趱 zan
{2,3079,{pysm::nop,pyym::nop}},//趲 zan
{2,3080,{pysm::nop,pyym::nop}},//足 zu
{1,0,{pysm::p,pyym::a}},//趴 pa
{5,43,{pysm::nop,pyym::nop}},//趵 bao
{2,3081,{pysm::nop,pyym::nop}},//趶 ku
{1,0,{pysm::k,pyym::e}},//趷 ke
{1,0,{pysm::d,pyym::un}},//趸 dun
{2,3082,{pysm::nop,pyym::nop}},//趹 jue
{1,0,{pysm::f,pyym::u}},//趺 fu
{1,0,{pysm::ch,pyym::en}},//趻 chen
{2,3083,{pysm::nop,pyym::nop}},//趼 jian
{2,3084,{pysm::nop,pyym::nop}},//趽 fang
{1,0,{pysm::zh,pyym::i}},//趾 zhi
{3,724,{pysm::nop,pyym::nop}},//趿 ta
{1,0,{pysm::y,pyym::ue}},//跀 yue
{2,3085,{pysm::nop,pyym::nop}},//跁 ba
{3,725,{pysm::nop,pyym::nop}},//跂 qi
{1,0,{pysm::y,pyym::ue}},//跃 yue
{1,0,{pysm::q,pyym::iang}},//跄 qiang
{2,3086,{pysm::nop,pyym::nop}},//跅 tuo
{1,0,{pysm::t,pyym::ai}},//跆 tai
{1,0,{pysm::y,pyym::i}},//跇 yi
{4,148,{pysm::nop,pyym::nop}},//跈 nian
{1,0,{pysm::l,pyym::ing}},//跉 ling
{1,0,{pysm::m,pyym::ei}},//跊 mei
{2,3087,{pysm::nop,pyym::nop}},//跋 ba
{2,3088,{pysm::nop,pyym::nop}},//跌 die
{1,0,{pysm::k,pyym::u}},//跍 ku
{1,0,{pysm::t,pyym::uo}},//跎 tuo
{1,0,{pysm::j,pyym::ia}},//跏 jia
{2,3089,{pysm::nop,pyym::nop}},//跐 ci
{2,3090,{pysm::nop,pyym::nop}},//跑 pao
{1,0,{pysm::q,pyym::ia}},//跒 qia
{1,0,{pysm::zh,pyym::u}},//跓 zhu
{2,3091,{pysm::nop,pyym::nop}},//跔 ju
{4,149,{pysm::nop,pyym::nop}},//跕 dian
{1,0,{pysm::zh,pyym::i}},//跖 zhi
{1,0,{pysm::f,pyym::u}},//跗 fu
{2,3092,{pysm::nop,pyym::nop}},//跘 pan
{4,150,{pysm::nop,pyym::nop}},//跙 ju
{1,0,{pysm::sh,pyym::an}},//跚 shan
{3,726,{pysm::nop,pyym::nop}},//跛 bo
{1,0,{pysm::n,pyym::i}},//跜 ni
{1,0,{pysm::j,pyym::u}},//距 ju
{2,3093,{pysm::nop,pyym::nop}},//跞 li
{1,0,{pysm::g,pyym::en}},//跟 gen
{1,0,{pysm::y,pyym::i}},//跠 yi
{1,0,{pysm::j,pyym::i}},//跡 ji
{3,727,{pysm::nop,pyym::nop}},//跢 duo
{2,3094,{pysm::nop,pyym::nop}},//跣 xian
{2,3095,{pysm::nop,pyym::nop}},//跤 jiao
{1,0,{pysm::d,pyym::uo}},//跥 duo
{2,3096,{pysm::nop,pyym::nop}},//跦 zhu
{2,3097,{pysm::nop,pyym::nop}},//跧 quan
{2,3098,{pysm::nop,pyym::nop}},//跨 kua
{2,3099,{pysm::nop,pyym::nop}},//跩 zhuai
{1,0,{pysm::g,pyym::ui}},//跪 gui
{2,3100,{pysm::nop,pyym::nop}},//跫 qiong
{2,3101,{pysm::nop,pyym::nop}},//跬 kui
{1,0,{pysm::x,pyym::iang}},//跭 xiang
{2,3102,{pysm::nop,pyym::nop}},//跮 chi
{2,3103,{pysm::nop,pyym::nop}},//路 lu
{3,728,{pysm::nop,pyym::nop}},//跰 pian
{1,0,{pysm::zh,pyym::i}},//跱 zhi
{2,3104,{pysm::nop,pyym::nop}},//跲 jia
{3,729,{pysm::nop,pyym::nop}},//跳 tiao
{1,0,{pysm::c,pyym::ai}},//跴 cai
{1,0,{pysm::j,pyym::ian}},//践 jian
{1,0,{pysm::d,pyym::a}},//跶 da
{1,0,{pysm::q,pyym::iao}},//跷 qiao
{1,0,{pysm::b,pyym::i}},//跸 bi
{1,0,{pysm::x,pyym::ian}},//跹 xian
{1,0,{pysm::d,pyym::uo}},//跺 duo
{1,0,{pysm::j,pyym::i}},//跻 ji
{2,3105,{pysm::nop,pyym::nop}},//跼 ju
{1,0,{pysm::j,pyym::i}},//跽 ji
{2,3106,{pysm::nop,pyym::nop}},//跾 shu
{3,730,{pysm::nop,pyym::nop}},//跿 tu
{2,3107,{pysm::nop,pyym::nop}},//踀 chu
{2,3108,{pysm::nop,pyym::nop}},//踁 jing
{1,0,{pysm::n,pyym::ie}},//踂 nie
{2,3109,{pysm::nop,pyym::nop}},//踃 xiao
{1,0,{pysm::b,pyym::u}},//踄 bu
{2,3110,{pysm::nop,pyym::nop}},//踅 xue
{5,44,{pysm::nop,pyym::nop}},//踆 cun
{1,0,{pysm::m,pyym::u}},//踇 mu
{1,0,{pysm::sh,pyym::u}},//踈 shu
{2,3111,{pysm::nop,pyym::nop}},//踉 liang
{1,0,{pysm::y,pyym::ong}},//踊 yong
{1,0,{pysm::j,pyym::iao}},//踋 jiao
{1,0,{pysm::ch,pyym::ou}},//踌 chou
{1,0,{pysm::q,pyym::iao}},//踍 qiao
{1,0,{pysm::m,pyym::ou}},//踎 mou
{1,0,{pysm::t,pyym::a}},//踏 ta
{1,0,{pysm::j,pyym::ian}},//踐 jian
{2,3112,{pysm::nop,pyym::nop}},//踑 qi
{3,731,{pysm::nop,pyym::nop}},//踒 wo
{2,3113,{pysm::nop,pyym::nop}},//踓 wei
{4,151,{pysm::nop,pyym::nop}},//踔 chuo
{1,0,{pysm::j,pyym::ie}},//踕 jie
{3,732,{pysm::nop,pyym::nop}},//踖 ji
{1,0,{pysm::n,pyym::ie}},//踗 nie
{1,0,{pysm::j,pyym::u}},//踘 ju
{1,0,{pysm::n,pyym::ie}},//踙 nie
{1,0,{pysm::l,pyym::un}},//踚 lun
{1,0,{pysm::l,pyym::u}},//踛 lu
{2,3114,{pysm::nop,pyym::nop}},//踜 leng
{1,0,{pysm::h,pyym::uai}},//踝 huai
{1,0,{pysm::j,pyym::u}},//踞 ju
{1,0,{pysm::ch,pyym::i}},//踟 chi
{2,3115,{pysm::nop,pyym::nop}},//踠 wan
{2,3116,{pysm::nop,pyym::nop}},//踡 quan
{2,3117,{pysm::nop,pyym::nop}},//踢 ti
{2,3118,{pysm::nop,pyym::nop}},//踣 bo
{3,733,{pysm::nop,pyym::nop}},//踤 zu
{1,0,{pysm::q,pyym::ie}},//踥 qie
{3,734,{pysm::nop,pyym::nop}},//踦 yi
{2,3119,{pysm::nop,pyym::nop}},//踧 cu
{1,0,{pysm::z,pyym::ong}},//踨 zong
{2,3120,{pysm::nop,pyym::nop}},//踩 cai
{1,0,{pysm::z,pyym::ong}},//踪 zong
{2,3121,{pysm::nop,pyym::nop}},//踫 peng
{1,0,{pysm::zh,pyym::i}},//踬 zhi
{1,0,{pysm::zh,pyym::eng}},//踭 zheng
{1,0,{pysm::d,pyym::ian}},//踮 dian
{1,0,{pysm::zh,pyym::i}},//踯 zhi
{3,735,{pysm::nop,pyym::nop}},//踰 yu
{2,3122,{pysm::nop,pyym::nop}},//踱 duo
{1,0,{pysm::d,pyym::un}},//踲 dun
{2,3123,{pysm::nop,pyym::nop}},//踳 chuan
{1,0,{pysm::y,pyym::ong}},//踴 yong
{1,0,{pysm::zh,pyym::ong}},//踵 zhong
{5,45,{pysm::nop,pyym::nop}},//踶 di
{1,0,{pysm::zh,pyym::a}},//踷 zha
{1,0,{pysm::ch,pyym::en}},//踸 chen
{4,152,{pysm::nop,pyym::nop}},//踹 chuai
{1,0,{pysm::j,pyym::ian}},//踺 jian
{2,3124,{pysm::nop,pyym::nop}},//踻 gua
{2,3125,{pysm::nop,pyym::nop}},//踼 tang
{1,0,{pysm::j,pyym::u}},//踽 ju
{2,3126,{pysm::nop,pyym::nop}},//踾 fu
{1,0,{pysm::z,pyym::u}},//踿 zu
{1,0,{pysm::d,pyym::ie}},//蹀 die
{1,0,{pysm::p,pyym::ian}},//蹁 pian
{1,0,{pysm::r,pyym::ou}},//蹂 rou
{3,736,{pysm::nop,pyym::nop}},//蹃 nuo
{2,3127,{pysm::nop,pyym::nop}},//蹄 ti
{2,3128,{pysm::nop,pyym::nop}},//蹅 cha
{1,0,{pysm::t,pyym::ui}},//蹆 tui
{1,0,{pysm::j,pyym::ian}},//蹇 jian
{1,0,{pysm::d,pyym::ao}},//蹈 dao
{1,0,{pysm::c,pyym::uo}},//蹉 cuo
{2,3129,{pysm::nop,pyym::nop}},//蹊 qi
{1,0,{pysm::t,pyym::a}},//蹋 ta
{1,0,{pysm::q,pyym::iang}},//蹌 qiang
{3,737,{pysm::nop,pyym::nop}},//蹍 nian
{1,0,{pysm::d,pyym::ian}},//蹎 dian
{1,0,{pysm::t,pyym::i}},//蹏 ti
{1,0,{pysm::j,pyym::i}},//蹐 ji
{1,0,{pysm::n,pyym::ie}},//蹑 nie
{2,3130,{pysm::nop,pyym::nop}},//蹒 pan
{1,0,{pysm::l,pyym::iu}},//蹓 liu
{2,3131,{pysm::nop,pyym::nop}},//蹔 zan
{1,0,{pysm::b,pyym::i}},//蹕 bi
{1,0,{pysm::ch,pyym::ong}},//蹖 chong
{1,0,{pysm::l,pyym::u}},//蹗 lu
{1,0,{pysm::l,pyym::iao}},//蹘 liao
{1,0,{pysm::c,pyym::u}},//蹙 cu
{2,3132,{pysm::nop,pyym::nop}},//蹚 tang
{4,153,{pysm::nop,pyym::nop}},//蹛 dai
{1,0,{pysm::s,pyym::u}},//蹜 su
{1,0,{pysm::x,pyym::i}},//蹝 xi
{1,0,{pysm::k,pyym::ui}},//蹞 kui
{1,0,{pysm::j,pyym::i}},//蹟 ji
{2,3133,{pysm::nop,pyym::nop}},//蹠 zhi
{1,0,{pysm::q,pyym::iang}},//蹡 qiang
{2,3134,{pysm::nop,pyym::nop}},//蹢 di
{3,738,{pysm::nop,pyym::nop}},//蹣 pan
{1,0,{pysm::z,pyym::ong}},//蹤 zong
{1,0,{pysm::l,pyym::ian}},//蹥 lian
{1,0,{pysm::b,pyym::eng}},//蹦 beng
{1,0,{pysm::z,pyym::ao}},//蹧 zao
{2,3135,{pysm::nop,pyym::nop}},//蹨 nian
{1,0,{pysm::b,pyym::ie}},//蹩 bie
{1,0,{pysm::t,pyym::ui}},//蹪 tui
{1,0,{pysm::j,pyym::u}},//蹫 ju
{1,0,{pysm::d,pyym::eng}},//蹬 deng
{1,0,{pysm::c,pyym::eng}},//蹭 ceng
{1,0,{pysm::x,pyym::ian}},//蹮 xian
{1,0,{pysm::f,pyym::an}},//蹯 fan
{1,0,{pysm::ch,pyym::u}},//蹰 chu
{2,3136,{pysm::nop,pyym::nop}},//蹱 zhong
{5,46,{pysm::nop,pyym::nop}},//蹲 dun
{1,0,{pysm::b,pyym::o}},//蹳 bo
{3,739,{pysm::nop,pyym::nop}},//蹴 cu
{1,0,{pysm::c,pyym::u}},//蹵 cu
{2,3137,{pysm::nop,pyym::nop}},//蹶 jue
{1,0,{pysm::j,pyym::ue}},//蹷 jue
{1,0,{pysm::l,pyym::in}},//蹸 lin
{1,0,{pysm::t,pyym::a}},//蹹 ta
{1,0,{pysm::q,pyym::iao}},//蹺 qiao
{5,47,{pysm::nop,pyym::nop}},//蹻 jue
{1,0,{pysm::p,pyym::u}},//蹼 pu
{1,0,{pysm::l,pyym::iao}},//蹽 liao
{1,0,{pysm::d,pyym::un}},//蹾 dun
{1,0,{pysm::c,pyym::uan}},//蹿 cuan
{1,0,{pysm::g,pyym::uan}},//躀 guan
{1,0,{pysm::z,pyym::ao}},//躁 zao
{1,0,{pysm::d,pyym::a}},//躂 da
{1,0,{pysm::b,pyym::i}},//躃 bi
{1,0,{pysm::b,pyym::i}},//躄 bi
{2,3138,{pysm::nop,pyym::nop}},//躅 zhu
{1,0,{pysm::j,pyym::u}},//躆 ju
{2,3139,{pysm::nop,pyym::nop}},//躇 chu
{1,0,{pysm::q,pyym::iao}},//躈 qiao
{1,0,{pysm::d,pyym::un}},//躉 dun
{1,0,{pysm::ch,pyym::ou}},//躊 chou
{1,0,{pysm::j,pyym::i}},//躋 ji
{1,0,{pysm::w,pyym::u}},//躌 wu
{2,3140,{pysm::nop,pyym::nop}},//躍 yue
{1,0,{pysm::n,pyym::ian}},//躎 nian
{1,0,{pysm::l,pyym::in}},//躏 lin
{1,0,{pysm::l,pyym::ie}},//躐 lie
{1,0,{pysm::zh,pyym::i}},//躑 zhi
{3,740,{pysm::nop,pyym::nop}},//躒 li
{1,0,{pysm::zh,pyym::i}},//躓 zhi
{2,3141,{pysm::nop,pyym::nop}},//躔 chan
{1,0,{pysm::ch,pyym::u}},//躕 chu
{1,0,{pysm::d,pyym::uan}},//躖 duan
{1,0,{pysm::w,pyym::ei}},//躗 wei
{1,0,{pysm::l,pyym::ong}},//躘 long
{1,0,{pysm::l,pyym::in}},//躙 lin
{1,0,{pysm::x,pyym::ian}},//躚 xian
{1,0,{pysm::w,pyym::ei}},//躛 wei
{1,0,{pysm::z,pyym::uan}},//躜 zuan
{1,0,{pysm::l,pyym::an}},//躝 lan
{1,0,{pysm::x,pyym::ie}},//躞 xie
{1,0,{pysm::r,pyym::ang}},//躟 rang
{2,3142,{pysm::nop,pyym::nop}},//躠 sa
{1,0,{pysm::n,pyym::ie}},//躡 nie
{1,0,{pysm::t,pyym::a}},//躢 ta
{1,0,{pysm::q,pyym::u}},//躣 qu
{1,0,{pysm::j,pyym::i}},//躤 ji
{1,0,{pysm::c,pyym::uan}},//躥 cuan
{2,3143,{pysm::nop,pyym::nop}},//躦 cuo
{1,0,{pysm::x,pyym::i}},//躧 xi
{1,0,{pysm::k,pyym::ui}},//躨 kui
{2,3144,{pysm::nop,pyym::nop}},//躩 jue
{1,0,{pysm::l,pyym::in}},//躪 lin
{2,3145,{pysm::nop,pyym::nop}},//身 shen
{1,0,{pysm::g,pyym::ong}},//躬 gong
{1,0,{pysm::d,pyym::an}},//躭 dan
{1,0,{pysm::f,pyym::en}},//躮 fen
{1,0,{pysm::q,pyym::u}},//躯 qu
{1,0,{pysm::t,pyym::i}},//躰 ti
{1,0,{pysm::d,pyym::uo}},//躱 duo
{1,0,{pysm::d,pyym::uo}},//躲 duo
{1,0,{pysm::g,pyym::ong}},//躳 gong
{1,0,{pysm::l,pyym::ang}},//躴 lang
{1,0,{pysm::r,pyym::en}},//躵 ren
{1,0,{pysm::l,pyym::uo}},//躶 luo
{1,0,{pysm::nop,pyym::ai}},//躷 ai
{1,0,{pysm::j,pyym::i}},//躸 ji
{1,0,{pysm::j,pyym::u}},//躹 ju
{1,0,{pysm::t,pyym::ang}},//躺 tang
{1,0,{pysm::k,pyym::ong}},//躻 kong
{1,0,{pysm::l,pyym::ao}},//躼 lao
{1,0,{pysm::y,pyym::an}},//躽 yan
{1,0,{pysm::m,pyym::ei}},//躾 mei
{1,0,{pysm::k,pyym::ang}},//躿 kang
{1,0,{pysm::q,pyym::u}},//軀 qu
{2,3146,{pysm::nop,pyym::nop}},//軁 lou
{1,0,{pysm::l,pyym::ao}},//軂 lao
{2,3147,{pysm::nop,pyym::nop}},//軃 duo
{1,0,{pysm::zh,pyym::i}},//軄 zhi
{1,0,{pysm::y,pyym::an}},//軅 yan
{1,0,{pysm::t,pyym::i}},//軆 ti
{1,0,{pysm::d,pyym::ao}},//軇 dao
{1,0,{pysm::y,pyym::ing}},//軈 ying
{1,0,{pysm::y,pyym::u}},//軉 yu
{2,3148,{pysm::nop,pyym::nop}},//車 che
{3,741,{pysm::nop,pyym::nop}},//軋 ya
{1,0,{pysm::g,pyym::ui}},//軌 gui
{1,0,{pysm::j,pyym::un}},//軍 jun
{1,0,{pysm::w,pyym::ei}},//軎 wei
{1,0,{pysm::y,pyym::ue}},//軏 yue
{2,3149,{pysm::nop,pyym::nop}},//軐 xin
{1,0,{pysm::d,pyym::ai}},//軑 dai
{4,154,{pysm::nop,pyym::nop}},//軒 xuan
{1,0,{pysm::f,pyym::an}},//軓 fan
{1,0,{pysm::r,pyym::en}},//軔 ren
{1,0,{pysm::sh,pyym::an}},//軕 shan
{1,0,{pysm::k,pyym::uang}},//軖 kuang
{1,0,{pysm::sh,pyym::u}},//軗 shu
{1,0,{pysm::t,pyym::un}},//軘 tun
{2,3150,{pysm::nop,pyym::nop}},//軙 chen
{1,0,{pysm::d,pyym::ai}},//軚 dai
{1,0,{pysm::nop,pyym::e}},//軛 e
{1,0,{pysm::n,pyym::a}},//軜 na
{1,0,{pysm::q,pyym::i}},//軝 qi
{1,0,{pysm::m,pyym::ao}},//軞 mao
{1,0,{pysm::r,pyym::uan}},//軟 ruan
{1,0,{pysm::k,pyym::uang}},//軠 kuang
{1,0,{pysm::q,pyym::ian}},//軡 qian
{1,0,{pysm::zh,pyym::uan}},//転 zhuan
{1,0,{pysm::h,pyym::ong}},//軣 hong
{1,0,{pysm::h,pyym::u}},//軤 hu
{3,742,{pysm::nop,pyym::nop}},//軥 qu
{1,0,{pysm::k,pyym::uang}},//軦 kuang
{2,3151,{pysm::nop,pyym::nop}},//軧 di
{1,0,{pysm::l,pyym::ing}},//軨 ling
{1,0,{pysm::d,pyym::ai}},//軩 dai
{1,0,{pysm::nop,pyym::ao}},//軪 ao
{1,0,{pysm::zh,pyym::en}},//軫 zhen
{2,3152,{pysm::nop,pyym::nop}},//軬 fan
{1,0,{pysm::k,pyym::uang}},//軭 kuang
{1,0,{pysm::y,pyym::ang}},//軮 yang
{1,0,{pysm::p,pyym::eng}},//軯 peng
{1,0,{pysm::b,pyym::ei}},//軰 bei
{1,0,{pysm::g,pyym::u}},//軱 gu
{1,0,{pysm::g,pyym::u}},//軲 gu
{1,0,{pysm::p,pyym::ao}},//軳 pao
{1,0,{pysm::zh,pyym::u}},//軴 zhu
{2,3153,{pysm::nop,pyym::nop}},//軵 rong
{1,0,{pysm::nop,pyym::e}},//軶 e
{1,0,{pysm::b,pyym::a}},//軷 ba
{2,3154,{pysm::nop,pyym::nop}},//軸 zhou
{1,0,{pysm::zh,pyym::i}},//軹 zhi
{2,3155,{pysm::nop,pyym::nop}},//軺 yao
{1,0,{pysm::k,pyym::e}},//軻 ke
{3,743,{pysm::nop,pyym::nop}},//軼 yi
{2,3156,{pysm::nop,pyym::nop}},//軽 zhi
{1,0,{pysm::sh,pyym::i}},//軾 shi
{1,0,{pysm::p,pyym::ing}},//軿 ping
{1,0,{pysm::nop,pyym::er}},//輀 er
{1,0,{pysm::g,pyym::ong}},//輁 gong
{1,0,{pysm::j,pyym::u}},//輂 ju
{3,744,{pysm::nop,pyym::nop}},//較 jiao
{1,0,{pysm::g,pyym::uang}},//輄 guang
{3,745,{pysm::nop,pyym::nop}},//輅 he
{1,0,{pysm::k,pyym::ai}},//輆 kai
{2,3157,{pysm::nop,pyym::nop}},//輇 quan
{1,0,{pysm::zh,pyym::ou}},//輈 zhou
{3,746,{pysm::nop,pyym::nop}},//載 zai
{1,0,{pysm::zh,pyym::i}},//輊 zhi
{1,0,{pysm::sh,pyym::e}},//輋 she
{1,0,{pysm::l,pyym::iang}},//輌 liang
{1,0,{pysm::y,pyym::u}},//輍 yu
{1,0,{pysm::sh,pyym::ao}},//輎 shao
{1,0,{pysm::y,pyym::ou}},//輏 you
{2,3158,{pysm::nop,pyym::nop}},//輐 wan
{2,3159,{pysm::nop,pyym::nop}},//輑 yin
{1,0,{pysm::zh,pyym::e}},//輒 zhe
{1,0,{pysm::w,pyym::an}},//輓 wan
{1,0,{pysm::f,pyym::u}},//輔 fu
{1,0,{pysm::q,pyym::ing}},//輕 qing
{1,0,{pysm::zh,pyym::ou}},//輖 zhou
{2,3160,{pysm::nop,pyym::nop}},//輗 ni
{2,3161,{pysm::nop,pyym::nop}},//輘 leng
{1,0,{pysm::zh,pyym::e}},//輙 zhe
{1,0,{pysm::zh,pyym::an}},//輚 zhan
{1,0,{pysm::l,pyym::iang}},//輛 liang
{1,0,{pysm::z,pyym::i}},//輜 zi
{1,0,{pysm::h,pyym::ui}},//輝 hui
{1,0,{pysm::w,pyym::ang}},//輞 wang
{1,0,{pysm::ch,pyym::uo}},//輟 chuo
{3,747,{pysm::nop,pyym::nop}},//輠 guo
{1,0,{pysm::k,pyym::an}},//輡 kan
{1,0,{pysm::y,pyym::i}},//輢 yi
{1,0,{pysm::p,pyym::eng}},//輣 peng
{1,0,{pysm::q,pyym::ian}},//輤 qian
{1,0,{pysm::g,pyym::un}},//輥 gun
{2,3162,{pysm::nop,pyym::nop}},//輦 nian
{2,3163,{pysm::nop,pyym::nop}},//輧 ping
{1,0,{pysm::g,pyym::uan}},//輨 guan
{1,0,{pysm::b,pyym::ei}},//輩 bei
{1,0,{pysm::l,pyym::un}},//輪 lun
{1,0,{pysm::p,pyym::ai}},//輫 pai
{1,0,{pysm::l,pyym::iang}},//輬 liang
{2,3164,{pysm::nop,pyym::nop}},//輭 ruan
{1,0,{pysm::r,pyym::ou}},//輮 rou
{1,0,{pysm::j,pyym::i}},//輯 ji
{1,0,{pysm::y,pyym::ang}},//輰 yang
{2,3165,{pysm::nop,pyym::nop}},//輱 xian
{1,0,{pysm::ch,pyym::uan}},//輲 chuan
{1,0,{pysm::c,pyym::ou}},//輳 cou
{2,3166,{pysm::nop,pyym::nop}},//輴 chun
{4,155,{pysm::nop,pyym::nop}},//輵 ge
{1,0,{pysm::y,pyym::ou}},//輶 you
{1,0,{pysm::h,pyym::ong}},//輷 hong
{1,0,{pysm::sh,pyym::u}},//輸 shu
{2,3167,{pysm::nop,pyym::nop}},//輹 fu
{1,0,{pysm::z,pyym::i}},//輺 zi
{1,0,{pysm::f,pyym::u}},//輻 fu
{2,3168,{pysm::nop,pyym::nop}},//輼 wen
{1,0,{pysm::b,pyym::en}},//輽 ben
{2,3169,{pysm::nop,pyym::nop}},//輾 zhan
{1,0,{pysm::y,pyym::u}},//輿 yu
{1,0,{pysm::w,pyym::en}},//轀 wen
{2,3170,{pysm::nop,pyym::nop}},//轁 tao
{1,0,{pysm::g,pyym::u}},//轂 gu
{1,0,{pysm::zh,pyym::en}},//轃 zhen
{2,3171,{pysm::nop,pyym::nop}},//轄 xia
{1,0,{pysm::y,pyym::uan}},//轅 yuan
{1,0,{pysm::l,pyym::u}},//轆 lu
{2,3172,{pysm::nop,pyym::nop}},//轇 jiao
{1,0,{pysm::ch,pyym::ao}},//轈 chao
{2,3173,{pysm::nop,pyym::nop}},//轉 zhuan
{1,0,{pysm::w,pyym::ei}},//轊 wei
{1,0,{pysm::h,pyym::un}},//轋 hun
{1,0,{pysm::x,pyym::ue}},//轌 xue
{1,0,{pysm::zh,pyym::e}},//轍 zhe
{1,0,{pysm::j,pyym::iao}},//轎 jiao
{1,0,{pysm::zh,pyym::an}},//轏 zhan
{1,0,{pysm::b,pyym::u}},//轐 bu
{2,3174,{pysm::nop,pyym::nop}},//轑 lao
{1,0,{pysm::f,pyym::en}},//轒 fen
{1,0,{pysm::f,pyym::an}},//轓 fan
{1,0,{pysm::l,pyym::in}},//轔 lin
{1,0,{pysm::g,pyym::e}},//轕 ge
{1,0,{pysm::s,pyym::e}},//轖 se
{1,0,{pysm::k,pyym::an}},//轗 kan
{1,0,{pysm::h,pyym::uan}},//轘 huan
{1,0,{pysm::y,pyym::i}},//轙 yi
{1,0,{pysm::j,pyym::i}},//轚 ji
{1,0,{pysm::zh,pyym::ui}},//轛 zhui
{1,0,{pysm::nop,pyym::er}},//轜 er
{1,0,{pysm::y,pyym::u}},//轝 yu
{1,0,{pysm::j,pyym::ian}},//轞 jian
{1,0,{pysm::h,pyym::ong}},//轟 hong
{1,0,{pysm::l,pyym::ei}},//轠 lei
{1,0,{pysm::p,pyym::ei}},//轡 pei
{1,0,{pysm::l,pyym::i}},//轢 li
{1,0,{pysm::l,pyym::i}},//轣 li
{1,0,{pysm::l,pyym::u}},//轤 lu
{1,0,{pysm::l,pyym::in}},//轥 lin
{2,3175,{pysm::nop,pyym::nop}},//车 che
{3,748,{pysm::nop,pyym::nop}},//轧 ya
{1,0,{pysm::g,pyym::ui}},//轨 gui
{1,0,{pysm::x,pyym::uan}},//轩 xuan
{1,0,{pysm::d,pyym::ai}},//轪 dai
{1,0,{pysm::r,pyym::en}},//轫 ren
{2,3176,{pysm::nop,pyym::nop}},//转 zhuan
{1,0,{pysm::nop,pyym::e}},//轭 e
{1,0,{pysm::l,pyym::un}},//轮 lun
{1,0,{pysm::r,pyym::uan}},//软 ruan
{1,0,{pysm::h,pyym::ong}},//轰 hong
{1,0,{pysm::g,pyym::u}},//轱 gu
{1,0,{pysm::k,pyym::e}},//轲 ke
{1,0,{pysm::l,pyym::u}},//轳 lu
{1,0,{pysm::zh,pyym::ou}},//轴 zhou
{1,0,{pysm::zh,pyym::i}},//轵 zhi
{1,0,{pysm::y,pyym::i}},//轶 yi
{1,0,{pysm::h,pyym::u}},//轷 hu
{1,0,{pysm::zh,pyym::en}},//轸 zhen
{1,0,{pysm::l,pyym::i}},//轹 li
{1,0,{pysm::y,pyym::ao}},//轺 yao
{1,0,{pysm::q,pyym::ing}},//轻 qing
{1,0,{pysm::sh,pyym::i}},//轼 shi
{1,0,{pysm::z,pyym::ai}},//载 zai
{1,0,{pysm::zh,pyym::i}},//轾 zhi
{1,0,{pysm::j,pyym::iao}},//轿 jiao
{1,0,{pysm::zh,pyym::ou}},//辀 zhou
{1,0,{pysm::q,pyym::uan}},//辁 quan
{1,0,{pysm::l,pyym::u}},//辂 lu
{1,0,{pysm::j,pyym::iao}},//较 jiao
{1,0,{pysm::zh,pyym::e}},//辄 zhe
{1,0,{pysm::f,pyym::u}},//辅 fu
{1,0,{pysm::l,pyym::iang}},//辆 liang
{1,0,{pysm::n,pyym::ian}},//辇 nian
{1,0,{pysm::b,pyym::ei}},//辈 bei
{1,0,{pysm::h,pyym::ui}},//辉 hui
{1,0,{pysm::g,pyym::un}},//辊 gun
{1,0,{pysm::w,pyym::ang}},//辋 wang
{1,0,{pysm::l,pyym::iang}},//辌 liang
{1,0,{pysm::ch,pyym::uo}},//辍 chuo
{1,0,{pysm::z,pyym::i}},//辎 zi
{1,0,{pysm::c,pyym::ou}},//辏 cou
{1,0,{pysm::f,pyym::u}},//辐 fu
{1,0,{pysm::j,pyym::i}},//辑 ji
{1,0,{pysm::w,pyym::en}},//辒 wen
{1,0,{pysm::sh,pyym::u}},//输 shu
{1,0,{pysm::p,pyym::ei}},//辔 pei
{1,0,{pysm::y,pyym::uan}},//辕 yuan
{1,0,{pysm::x,pyym::ia}},//辖 xia
{2,3177,{pysm::nop,pyym::nop}},//辗 nian
{1,0,{pysm::l,pyym::u}},//辘 lu
{1,0,{pysm::zh,pyym::e}},//辙 zhe
{1,0,{pysm::l,pyym::in}},//辚 lin
{1,0,{pysm::x,pyym::in}},//辛 xin
{1,0,{pysm::g,pyym::u}},//辜 gu
{1,0,{pysm::c,pyym::i}},//辝 ci
{1,0,{pysm::c,pyym::i}},//辞 ci
{3,749,{pysm::nop,pyym::nop}},//辟 pi
{1,0,{pysm::z,pyym::ui}},//辠 zui
{1,0,{pysm::b,pyym::ian}},//辡 bian
{1,0,{pysm::l,pyym::a}},//辢 la
{1,0,{pysm::l,pyym::a}},//辣 la
{1,0,{pysm::c,pyym::i}},//辤 ci
{2,3178,{pysm::nop,pyym::nop}},//辥 xue
{1,0,{pysm::b,pyym::an}},//辦 ban
{1,0,{pysm::b,pyym::ian}},//辧 bian
{3,750,{pysm::nop,pyym::nop}},//辨 bian
{1,0,{pysm::b,pyym::ian}},//辩 bian
{1,0,{pysm::x,pyym::ue}},//辪 xue
{1,0,{pysm::b,pyym::ian}},//辫 bian
{1,0,{pysm::b,pyym::an}},//辬 ban
{1,0,{pysm::c,pyym::i}},//辭 ci
{1,0,{pysm::b,pyym::ian}},//辮 bian
{3,751,{pysm::nop,pyym::nop}},//辯 bian
{1,0,{pysm::ch,pyym::en}},//辰 chen
{1,0,{pysm::r,pyym::u}},//辱 ru
{1,0,{pysm::n,pyym::ong}},//農 nong
{1,0,{pysm::n,pyym::ong}},//辳 nong
{2,3179,{pysm::nop,pyym::nop}},//辴 chan
{1,0,{pysm::ch,pyym::uo}},//辵 chuo
{1,0,{pysm::ch,pyym::uo}},//辶 chuo
{1,0,{pysm::y,pyym::i}},//辷 yi
{1,0,{pysm::r,pyym::eng}},//辸 reng
{1,0,{pysm::b,pyym::ian}},//边 bian
{1,0,{pysm::b,pyym::ian}},//辺 bian
{1,0,{pysm::sh,pyym::i}},//辻 shi
{1,0,{pysm::y,pyym::u}},//込 yu
{1,0,{pysm::l,pyym::iao}},//辽 liao
{3,752,{pysm::nop,pyym::nop}},//达 da
{1,0,{pysm::ch,pyym::an}},//辿 chan
{1,0,{pysm::g,pyym::an}},//迀 gan
{1,0,{pysm::q,pyym::ian}},//迁 qian
{1,0,{pysm::y,pyym::u}},//迂 yu
{1,0,{pysm::y,pyym::u}},//迃 yu
{1,0,{pysm::q,pyym::i}},//迄 qi
{1,0,{pysm::x,pyym::un}},//迅 xun
{2,3180,{pysm::nop,pyym::nop}},//迆 yi
{1,0,{pysm::g,pyym::uo}},//过 guo
{1,0,{pysm::m,pyym::ai}},//迈 mai
{1,0,{pysm::q,pyym::i}},//迉 qi
{1,0,{pysm::z,pyym::a}},//迊 za
{3,753,{pysm::nop,pyym::nop}},//迋 wang
{1,0,{pysm::t,pyym::u}},//迌 tu
{1,0,{pysm::zh,pyym::un}},//迍 zhun
{1,0,{pysm::y,pyym::ing}},//迎 ying
{1,0,{pysm::d,pyym::a}},//迏 da
{1,0,{pysm::y,pyym::un}},//运 yun
{1,0,{pysm::j,pyym::in}},//近 jin
{2,3181,{pysm::nop,pyym::nop}},//迒 hang
{1,0,{pysm::y,pyym::a}},//迓 ya
{1,0,{pysm::f,pyym::an}},//返 fan
{1,0,{pysm::w,pyym::u}},//迕 wu
{1,0,{pysm::d,pyym::a}},//迖 da
{1,0,{pysm::nop,pyym::e}},//迗 e
{3,754,{pysm::nop,pyym::nop}},//还 hai
{2,3182,{pysm::nop,pyym::nop}},//这 zhe
{1,0,{pysm::d,pyym::a}},//迚 da
{1,0,{pysm::j,pyym::in}},//进 jin
{1,0,{pysm::y,pyym::uan}},//远 yuan
{1,0,{pysm::w,pyym::ei}},//违 wei
{1,0,{pysm::l,pyym::ian}},//连 lian
{1,0,{pysm::ch,pyym::i}},//迟 chi
{1,0,{pysm::ch,pyym::e}},//迠 che
{2,3183,{pysm::nop,pyym::nop}},//迡 ni
{1,0,{pysm::t,pyym::iao}},//迢 tiao
{2,3184,{pysm::nop,pyym::nop}},//迣 zhi
{2,3185,{pysm::nop,pyym::nop}},//迤 yi
{1,0,{pysm::j,pyym::iong}},//迥 jiong
{2,3186,{pysm::nop,pyym::nop}},//迦 jia
{1,0,{pysm::ch,pyym::en}},//迧 chen
{1,0,{pysm::d,pyym::ai}},//迨 dai
{1,0,{pysm::nop,pyym::er}},//迩 er
{1,0,{pysm::d,pyym::i}},//迪 di
{2,3187,{pysm::nop,pyym::nop}},//迫 po
{2,3188,{pysm::nop,pyym::nop}},//迬 zhu
{3,755,{pysm::nop,pyym::nop}},//迭 die
{2,3189,{pysm::nop,pyym::nop}},//迮 ze
{1,0,{pysm::t,pyym::ao}},//迯 tao
{1,0,{pysm::sh,pyym::u}},//述 shu
{2,3190,{pysm::nop,pyym::nop}},//迱 tuo
{1,0,{pysm::q,pyym::u}},//迲 qu
{1,0,{pysm::j,pyym::ing}},//迳 jing
{1,0,{pysm::h,pyym::ui}},//迴 hui
{1,0,{pysm::d,pyym::ong}},//迵 dong
{1,0,{pysm::y,pyym::ou}},//迶 you
{1,0,{pysm::m,pyym::i}},//迷 mi
{1,0,{pysm::b,pyym::eng}},//迸 beng
{1,0,{pysm::j,pyym::i}},//迹 ji
{1,0,{pysm::n,pyym::ai}},//迺 nai
{1,0,{pysm::y,pyym::i}},//迻 yi
{1,0,{pysm::j,pyym::ie}},//迼 jie
{3,756,{pysm::nop,pyym::nop}},//追 zhui
{1,0,{pysm::l,pyym::ie}},//迾 lie
{1,0,{pysm::x,pyym::un}},//迿 xun
{1,0,{pysm::t,pyym::ui}},//退 tui
{1,0,{pysm::s,pyym::ong}},//送 song
{2,3191,{pysm::nop,pyym::nop}},//适 shi
{1,0,{pysm::t,pyym::ao}},//逃 tao
{2,3192,{pysm::nop,pyym::nop}},//逄 pang
{1,0,{pysm::h,pyym::ou}},//逅 hou
{1,0,{pysm::n,pyym::i}},//逆 ni
{1,0,{pysm::d,pyym::un}},//逇 dun
{1,0,{pysm::j,pyym::iong}},//逈 jiong
{1,0,{pysm::x,pyym::uan}},//选 xuan
{1,0,{pysm::x,pyym::un}},//逊 xun
{1,0,{pysm::b,pyym::u}},//逋 bu
{1,0,{pysm::y,pyym::ou}},//逌 you
{1,0,{pysm::x,pyym::iao}},//逍 xiao
{1,0,{pysm::q,pyym::iu}},//逎 qiu
{2,3193,{pysm::nop,pyym::nop}},//透 tou
{4,156,{pysm::nop,pyym::nop}},//逐 zhu
{1,0,{pysm::q,pyym::iu}},//逑 qiu
{1,0,{pysm::d,pyym::i}},//递 di
{1,0,{pysm::d,pyym::i}},//逓 di
{1,0,{pysm::t,pyym::u}},//途 tu
{1,0,{pysm::j,pyym::ing}},//逕 jing
{1,0,{pysm::t,pyym::i}},//逖 ti
{4,157,{pysm::nop,pyym::nop}},//逗 dou
{2,3194,{pysm::nop,pyym::nop}},//逘 yi
{3,757,{pysm::nop,pyym::nop}},//這 zhe
{1,0,{pysm::t,pyym::ong}},//通 tong
{2,3195,{pysm::nop,pyym::nop}},//逛 guang
{1,0,{pysm::w,pyym::u}},//逜 wu
{1,0,{pysm::sh,pyym::i}},//逝 shi
{2,3196,{pysm::nop,pyym::nop}},//逞 cheng
{1,0,{pysm::s,pyym::u}},//速 su
{2,3197,{pysm::nop,pyym::nop}},//造 zao
{3,758,{pysm::nop,pyym::nop}},//逡 qun
{3,759,{pysm::nop,pyym::nop}},//逢 feng
{2,3198,{pysm::nop,pyym::nop}},//連 lian
{1,0,{pysm::s,pyym::uo}},//逤 suo
{1,0,{pysm::h,pyym::ui}},//逥 hui
{1,0,{pysm::l,pyym::i}},//逦 li
{1,0,{pysm::g,pyym::u}},//逧 gu
{1,0,{pysm::l,pyym::ai}},//逨 lai
{1,0,{pysm::b,pyym::en}},//逩 ben
{1,0,{pysm::c,pyym::uo}},//逪 cuo
{2,3199,{pysm::nop,pyym::nop}},//逫 jue
{2,3200,{pysm::nop,pyym::nop}},//逬 beng
{1,0,{pysm::h,pyym::uan}},//逭 huan
{2,3201,{pysm::nop,pyym::nop}},//逮 dai
{2,3202,{pysm::nop,pyym::nop}},//逯 lu
{1,0,{pysm::y,pyym::ou}},//逰 you
{1,0,{pysm::zh,pyym::ou}},//週 zhou
{1,0,{pysm::j,pyym::in}},//進 jin
{1,0,{pysm::y,pyym::u}},//逳 yu
{1,0,{pysm::ch,pyym::uo}},//逴 chuo
{1,0,{pysm::k,pyym::ui}},//逵 kui
{1,0,{pysm::w,pyym::ei}},//逶 wei
{1,0,{pysm::t,pyym::i}},//逷 ti
{1,0,{pysm::y,pyym::i}},//逸 yi
{1,0,{pysm::d,pyym::a}},//逹 da
{1,0,{pysm::y,pyym::uan}},//逺 yuan
{1,0,{pysm::l,pyym::uo}},//逻 luo
{1,0,{pysm::b,pyym::i}},//逼 bi
{1,0,{pysm::n,pyym::uo}},//逽 nuo
{2,3203,{pysm::nop,pyym::nop}},//逾 yu
{2,3204,{pysm::nop,pyym::nop}},//逿 dang
{1,0,{pysm::s,pyym::ui}},//遀 sui
{3,760,{pysm::nop,pyym::nop}},//遁 dun
{1,0,{pysm::s,pyym::ui}},//遂 sui
{2,3205,{pysm::nop,pyym::nop}},//遃 yan
{1,0,{pysm::ch,pyym::uan}},//遄 chuan
{1,0,{pysm::ch,pyym::i}},//遅 chi
{1,0,{pysm::t,pyym::i}},//遆 ti
{3,761,{pysm::nop,pyym::nop}},//遇 yu
{1,0,{pysm::sh,pyym::i}},//遈 shi
{1,0,{pysm::zh,pyym::en}},//遉 zhen
{1,0,{pysm::y,pyym::ou}},//遊 you
{1,0,{pysm::y,pyym::un}},//運 yun
{1,0,{pysm::nop,pyym::e}},//遌 e
{1,0,{pysm::b,pyym::ian}},//遍 bian
{2,3206,{pysm::nop,pyym::nop}},//過 guo
{1,0,{pysm::nop,pyym::e}},//遏 e
{1,0,{pysm::x,pyym::ia}},//遐 xia
{1,0,{pysm::h,pyym::uang}},//遑 huang
{1,0,{pysm::q,pyym::iu}},//遒 qiu
{1,0,{pysm::d,pyym::ao}},//道 dao
{2,3207,{pysm::nop,pyym::nop}},//達 da
{2,3208,{pysm::nop,pyym::nop}},//違 wei
{1,0,{pysm::n,pyym::an}},//遖 nan
{2,3209,{pysm::nop,pyym::nop}},//遗 yi
{1,0,{pysm::g,pyym::ou}},//遘 gou
{1,0,{pysm::y,pyym::ao}},//遙 yao
{1,0,{pysm::ch,pyym::ou}},//遚 chou
{1,0,{pysm::l,pyym::iu}},//遛 liu
{1,0,{pysm::x,pyym::un}},//遜 xun
{1,0,{pysm::t,pyym::a}},//遝 ta
{3,762,{pysm::nop,pyym::nop}},//遞 di
{3,763,{pysm::nop,pyym::nop}},//遟 chi
{1,0,{pysm::y,pyym::uan}},//遠 yuan
{1,0,{pysm::s,pyym::u}},//遡 su
{1,0,{pysm::t,pyym::a}},//遢 ta
{1,0,{pysm::q,pyym::ian}},//遣 qian
{1,0,{pysm::m,pyym::a}},//遤 ma
{1,0,{pysm::y,pyym::ao}},//遥 yao
{1,0,{pysm::g,pyym::uan}},//遦 guan
{1,0,{pysm::zh,pyym::ang}},//遧 zhang
{1,0,{pysm::nop,pyym::ao}},//遨 ao
{4,158,{pysm::nop,pyym::nop}},//適 shi
{1,0,{pysm::c,pyym::a}},//遪 ca
{1,0,{pysm::ch,pyym::i}},//遫 chi
{1,0,{pysm::s,pyym::u}},//遬 su
{1,0,{pysm::z,pyym::ao}},//遭 zao
{1,0,{pysm::zh,pyym::e}},//遮 zhe
{1,0,{pysm::d,pyym::un}},//遯 dun
{3,764,{pysm::nop,pyym::nop}},//遰 di
{1,0,{pysm::l,pyym::ou}},//遱 lou
{2,3210,{pysm::nop,pyym::nop}},//遲 chi
{1,0,{pysm::c,pyym::uo}},//遳 cuo
{1,0,{pysm::l,pyym::in}},//遴 lin
{1,0,{pysm::z,pyym::un}},//遵 zun
{1,0,{pysm::r,pyym::ao}},//遶 rao
{1,0,{pysm::q,pyym::ian}},//遷 qian
{3,765,{pysm::nop,pyym::nop}},//選 xuan
{1,0,{pysm::y,pyym::u}},//遹 yu
{3,766,{pysm::nop,pyym::nop}},//遺 yi
{1,0,{pysm::nop,pyym::e}},//遻 e
{1,0,{pysm::l,pyym::iao}},//遼 liao
{2,3211,{pysm::nop,pyym::nop}},//遽 ju
{1,0,{pysm::sh,pyym::i}},//遾 shi
{1,0,{pysm::b,pyym::i}},//避 bi
{1,0,{pysm::y,pyym::ao}},//邀 yao
{1,0,{pysm::m,pyym::ai}},//邁 mai
{1,0,{pysm::x,pyym::ie}},//邂 xie
{1,0,{pysm::s,pyym::ui}},//邃 sui
{3,767,{pysm::nop,pyym::nop}},//還 hai
{1,0,{pysm::zh,pyym::an}},//邅 zhan
{1,0,{pysm::t,pyym::eng}},//邆 teng
{1,0,{pysm::nop,pyym::er}},//邇 er
{1,0,{pysm::m,pyym::iao}},//邈 miao
{1,0,{pysm::b,pyym::ian}},//邉 bian
{1,0,{pysm::b,pyym::ian}},//邊 bian
{2,3212,{pysm::nop,pyym::nop}},//邋 la
{2,3213,{pysm::nop,pyym::nop}},//邌 li
{1,0,{pysm::y,pyym::uan}},//邍 yuan
{1,0,{pysm::y,pyym::ao}},//邎 yao
{1,0,{pysm::l,pyym::uo}},//邏 luo
{1,0,{pysm::l,pyym::i}},//邐 li
{2,3214,{pysm::nop,pyym::nop}},//邑 yi
{1,0,{pysm::t,pyym::ing}},//邒 ting
{2,3215,{pysm::nop,pyym::nop}},//邓 deng
{1,0,{pysm::q,pyym::i}},//邔 qi
{1,0,{pysm::y,pyym::ong}},//邕 yong
{1,0,{pysm::sh,pyym::an}},//邖 shan
{1,0,{pysm::h,pyym::an}},//邗 han
{1,0,{pysm::y,pyym::u}},//邘 yu
{1,0,{pysm::m,pyym::ang}},//邙 mang
{2,3216,{pysm::nop,pyym::nop}},//邚 ru
{1,0,{pysm::q,pyym::iong}},//邛 qiong
{1,0,{pysm::x,pyym::i}},//邜 xi
{1,0,{pysm::k,pyym::uang}},//邝 kuang
{1,0,{pysm::f,pyym::u}},//邞 fu
{2,3217,{pysm::nop,pyym::nop}},//邟 kang
{1,0,{pysm::b,pyym::in}},//邠 bin
{1,0,{pysm::f,pyym::ang}},//邡 fang
{2,3218,{pysm::nop,pyym::nop}},//邢 xing
{5,48,{pysm::nop,pyym::nop}},//那 na
{1,0,{pysm::x,pyym::in}},//邤 xin
{1,0,{pysm::sh,pyym::en}},//邥 shen
{1,0,{pysm::b,pyym::ang}},//邦 bang
{1,0,{pysm::y,pyym::uan}},//邧 yuan
{1,0,{pysm::c,pyym::un}},//邨 cun
{1,0,{pysm::h,pyym::uo}},//邩 huo
{5,49,{pysm::nop,pyym::nop}},//邪 xie
{1,0,{pysm::b,pyym::ang}},//邫 bang
{1,0,{pysm::w,pyym::u}},//邬 wu
{1,0,{pysm::j,pyym::u}},//邭 ju
{1,0,{pysm::y,pyym::ou}},//邮 you
{1,0,{pysm::h,pyym::an}},//邯 han
{1,0,{pysm::t,pyym::ai}},//邰 tai
{1,0,{pysm::q,pyym::iu}},//邱 qiu
{2,3219,{pysm::nop,pyym::nop}},//邲 bi
{1,0,{pysm::p,pyym::i}},//邳 pi
{1,0,{pysm::b,pyym::ing}},//邴 bing
{1,0,{pysm::sh,pyym::ao}},//邵 shao
{1,0,{pysm::b,pyym::ei}},//邶 bei
{1,0,{pysm::w,pyym::a}},//邷 wa
{1,0,{pysm::d,pyym::i}},//邸 di
{1,0,{pysm::z,pyym::ou}},//邹 zou
{2,3220,{pysm::nop,pyym::nop}},//邺 ye
{1,0,{pysm::l,pyym::in}},//邻 lin
{1,0,{pysm::k,pyym::uang}},//邼 kuang
{1,0,{pysm::g,pyym::ui}},//邽 gui
{1,0,{pysm::zh,pyym::u}},//邾 zhu
{1,0,{pysm::sh,pyym::i}},//邿 shi
{1,0,{pysm::k,pyym::u}},//郀 ku
{1,0,{pysm::y,pyym::u}},//郁 yu
{2,3221,{pysm::nop,pyym::nop}},//郂 gai
{2,3222,{pysm::nop,pyym::nop}},//郃 he
{2,3223,{pysm::nop,pyym::nop}},//郄 qie
{2,3224,{pysm::nop,pyym::nop}},//郅 zhi
{1,0,{pysm::j,pyym::i}},//郆 ji
{2,3225,{pysm::nop,pyym::nop}},//郇 huan
{1,0,{pysm::h,pyym::ou}},//郈 hou
{1,0,{pysm::x,pyym::ing}},//郉 xing
{1,0,{pysm::j,pyym::iao}},//郊 jiao
{1,0,{pysm::x,pyym::i}},//郋 xi
{1,0,{pysm::g,pyym::ui}},//郌 gui
{3,768,{pysm::nop,pyym::nop}},//郍 nuo
{1,0,{pysm::l,pyym::ang}},//郎 lang
{1,0,{pysm::j,pyym::ia}},//郏 jia
{1,0,{pysm::k,pyym::uai}},//郐 kuai
{1,0,{pysm::zh,pyym::eng}},//郑 zheng
{1,0,{pysm::l,pyym::ang}},//郒 lang
{1,0,{pysm::y,pyym::un}},//郓 yun
{1,0,{pysm::y,pyym::an}},//郔 yan
{1,0,{pysm::ch,pyym::eng}},//郕 cheng
{1,0,{pysm::d,pyym::ou}},//郖 dou
{2,3226,{pysm::nop,pyym::nop}},//郗 xi
{1,0,{pysm::l,pyym::v}},//郘 lü
{1,0,{pysm::f,pyym::u}},//郙 fu
{2,3227,{pysm::nop,pyym::nop}},//郚 wu
{1,0,{pysm::f,pyym::u}},//郛 fu
{1,0,{pysm::g,pyym::ao}},//郜 gao
{2,3228,{pysm::nop,pyym::nop}},//郝 hao
{1,0,{pysm::l,pyym::ang}},//郞 lang
{1,0,{pysm::j,pyym::ia}},//郟 jia
{1,0,{pysm::g,pyym::eng}},//郠 geng
{1,0,{pysm::j,pyym::un}},//郡 jun
{2,3229,{pysm::nop,pyym::nop}},//郢 ying
{1,0,{pysm::b,pyym::o}},//郣 bo
{1,0,{pysm::x,pyym::i}},//郤 xi
{1,0,{pysm::b,pyym::ei}},//郥 bei
{1,0,{pysm::l,pyym::i}},//郦 li
{1,0,{pysm::y,pyym::un}},//郧 yun
{2,3230,{pysm::nop,pyym::nop}},//部 bu
{2,3231,{pysm::nop,pyym::nop}},//郩 xiao
{1,0,{pysm::q,pyym::i}},//郪 qi
{1,0,{pysm::p,pyym::i}},//郫 pi
{1,0,{pysm::q,pyym::ing}},//郬 qing
{1,0,{pysm::g,pyym::uo}},//郭 guo
{1,0,{pysm::zh,pyym::ou}},//郮 zhou
{1,0,{pysm::t,pyym::an}},//郯 tan
{2,3232,{pysm::nop,pyym::nop}},//郰 zou
{1,0,{pysm::p,pyym::ing}},//郱 ping
{2,3233,{pysm::nop,pyym::nop}},//郲 lai
{1,0,{pysm::n,pyym::i}},//郳 ni
{2,3234,{pysm::nop,pyym::nop}},//郴 chen
{2,3235,{pysm::nop,pyym::nop}},//郵 you
{1,0,{pysm::b,pyym::u}},//郶 bu
{1,0,{pysm::x,pyym::iang}},//郷 xiang
{1,0,{pysm::d,pyym::an}},//郸 dan
{1,0,{pysm::j,pyym::u}},//郹 ju
{1,0,{pysm::y,pyym::ong}},//郺 yong
{1,0,{pysm::q,pyym::iao}},//郻 qiao
{1,0,{pysm::y,pyym::i}},//郼 yi
{2,3236,{pysm::nop,pyym::nop}},//都 dou
{1,0,{pysm::y,pyym::an}},//郾 yan
{1,0,{pysm::m,pyym::ei}},//郿 mei
{1,0,{pysm::r,pyym::uo}},//鄀 ruo
{1,0,{pysm::b,pyym::ei}},//鄁 bei
{1,0,{pysm::nop,pyym::e}},//鄂 e
{1,0,{pysm::sh,pyym::u}},//鄃 shu
{1,0,{pysm::j,pyym::uan}},//鄄 juan
{1,0,{pysm::y,pyym::u}},//鄅 yu
{1,0,{pysm::y,pyym::un}},//鄆 yun
{1,0,{pysm::h,pyym::ou}},//鄇 hou
{1,0,{pysm::k,pyym::ui}},//鄈 kui
{1,0,{pysm::x,pyym::iang}},//鄉 xiang
{1,0,{pysm::x,pyym::iang}},//鄊 xiang
{1,0,{pysm::s,pyym::ou}},//鄋 sou
{1,0,{pysm::t,pyym::ang}},//鄌 tang
{1,0,{pysm::m,pyym::ing}},//鄍 ming
{1,0,{pysm::x,pyym::i}},//鄎 xi
{1,0,{pysm::r,pyym::u}},//鄏 ru
{1,0,{pysm::ch,pyym::u}},//鄐 chu
{1,0,{pysm::z,pyym::i}},//鄑 zi
{2,3237,{pysm::nop,pyym::nop}},//鄒 zou
{1,0,{pysm::y,pyym::e}},//鄓 ye
{1,0,{pysm::w,pyym::u}},//鄔 wu
{1,0,{pysm::x,pyym::iang}},//鄕 xiang
{1,0,{pysm::y,pyym::un}},//鄖 yun
{3,769,{pysm::nop,pyym::nop}},//鄗 hao
{1,0,{pysm::y,pyym::ong}},//鄘 yong
{1,0,{pysm::b,pyym::i}},//鄙 bi
{2,3238,{pysm::nop,pyym::nop}},//鄚 mao
{1,0,{pysm::ch,pyym::ao}},//鄛 chao
{2,3239,{pysm::nop,pyym::nop}},//鄜 fu
{1,0,{pysm::l,pyym::iao}},//鄝 liao
{1,0,{pysm::y,pyym::in}},//鄞 yin
{1,0,{pysm::zh,pyym::uan}},//鄟 zhuan
{1,0,{pysm::h,pyym::u}},//鄠 hu
{1,0,{pysm::q,pyym::iao}},//鄡 qiao
{1,0,{pysm::y,pyym::an}},//鄢 yan
{1,0,{pysm::zh,pyym::ang}},//鄣 zhang
{2,3240,{pysm::nop,pyym::nop}},//鄤 man
{1,0,{pysm::q,pyym::iao}},//鄥 qiao
{1,0,{pysm::x,pyym::u}},//鄦 xu
{1,0,{pysm::d,pyym::eng}},//鄧 deng
{1,0,{pysm::b,pyym::i}},//鄨 bi
{1,0,{pysm::x,pyym::un}},//鄩 xun
{1,0,{pysm::b,pyym::i}},//鄪 bi
{2,3241,{pysm::nop,pyym::nop}},//鄫 zeng
{1,0,{pysm::w,pyym::ei}},//鄬 wei
{1,0,{pysm::zh,pyym::eng}},//鄭 zheng
{1,0,{pysm::m,pyym::ao}},//鄮 mao
{1,0,{pysm::sh,pyym::an}},//鄯 shan
{1,0,{pysm::l,pyym::in}},//鄰 lin
{3,770,{pysm::nop,pyym::nop}},//鄱 po
{2,3242,{pysm::nop,pyym::nop}},//鄲 dan
{1,0,{pysm::m,pyym::eng}},//鄳 meng
{1,0,{pysm::y,pyym::e}},//鄴 ye
{2,3243,{pysm::nop,pyym::nop}},//鄵 cao
{1,0,{pysm::k,pyym::uai}},//鄶 kuai
{1,0,{pysm::f,pyym::eng}},//鄷 feng
{1,0,{pysm::m,pyym::eng}},//鄸 meng
{2,3244,{pysm::nop,pyym::nop}},//鄹 zou
{2,3245,{pysm::nop,pyym::nop}},//鄺 kuang
{1,0,{pysm::l,pyym::ian}},//鄻 lian
{1,0,{pysm::z,pyym::an}},//鄼 zan
{1,0,{pysm::ch,pyym::an}},//鄽 chan
{1,0,{pysm::y,pyym::ou}},//鄾 you
{2,3246,{pysm::nop,pyym::nop}},//鄿 ji
{1,0,{pysm::y,pyym::an}},//酀 yan
{1,0,{pysm::ch,pyym::an}},//酁 chan
{2,3247,{pysm::nop,pyym::nop}},//酂 cuo
{1,0,{pysm::l,pyym::ing}},//酃 ling
{2,3248,{pysm::nop,pyym::nop}},//酄 huan
{1,0,{pysm::x,pyym::i}},//酅 xi
{1,0,{pysm::f,pyym::eng}},//酆 feng
{2,3249,{pysm::nop,pyym::nop}},//酇 zan
{2,3250,{pysm::nop,pyym::nop}},//酈 li
{1,0,{pysm::y,pyym::ou}},//酉 you
{1,0,{pysm::d,pyym::ing}},//酊 ding
{1,0,{pysm::q,pyym::iu}},//酋 qiu
{1,0,{pysm::zh,pyym::uo}},//酌 zhuo
{1,0,{pysm::p,pyym::ei}},//配 pei
{1,0,{pysm::zh,pyym::ou}},//酎 zhou
{1,0,{pysm::y,pyym::i}},//酏 yi
{2,3251,{pysm::nop,pyym::nop}},//酐 gan
{1,0,{pysm::y,pyym::u}},//酑 yu
{1,0,{pysm::j,pyym::iu}},//酒 jiu
{2,3252,{pysm::nop,pyym::nop}},//酓 yan
{1,0,{pysm::z,pyym::ui}},//酔 zui
{1,0,{pysm::m,pyym::ao}},//酕 mao
{2,3253,{pysm::nop,pyym::nop}},//酖 zhen
{1,0,{pysm::x,pyym::u}},//酗 xu
{1,0,{pysm::d,pyym::ou}},//酘 dou
{1,0,{pysm::zh,pyym::en}},//酙 zhen
{1,0,{pysm::f,pyym::en}},//酚 fen
{1,0,{pysm::y,pyym::uan}},//酛 yuan
{1,0,{pysm::f,pyym::u}},//酜 fu
{1,0,{pysm::y,pyym::un}},//酝 yun
{1,0,{pysm::t,pyym::ai}},//酞 tai
{1,0,{pysm::t,pyym::ian}},//酟 tian
{1,0,{pysm::q,pyym::ia}},//酠 qia
{2,3254,{pysm::nop,pyym::nop}},//酡 tuo
{2,3255,{pysm::nop,pyym::nop}},//酢 cu
{1,0,{pysm::h,pyym::an}},//酣 han
{1,0,{pysm::g,pyym::u}},//酤 gu
{1,0,{pysm::s,pyym::u}},//酥 su
{2,3256,{pysm::nop,pyym::nop}},//酦 po
{1,0,{pysm::ch,pyym::ou}},//酧 chou
{2,3257,{pysm::nop,pyym::nop}},//酨 zai
{1,0,{pysm::m,pyym::ing}},//酩 ming
{3,771,{pysm::nop,pyym::nop}},//酪 lao
{1,0,{pysm::ch,pyym::uo}},//酫 chuo
{1,0,{pysm::ch,pyym::ou}},//酬 chou
{1,0,{pysm::y,pyym::ou}},//酭 you
{3,772,{pysm::nop,pyym::nop}},//酮 tong
{1,0,{pysm::zh,pyym::i}},//酯 zhi
{1,0,{pysm::x,pyym::ian}},//酰 xian
{1,0,{pysm::j,pyym::iang}},//酱 jiang
{1,0,{pysm::ch,pyym::eng}},//酲 cheng
{1,0,{pysm::y,pyym::in}},//酳 yin
{1,0,{pysm::t,pyym::u}},//酴 tu
{1,0,{pysm::j,pyym::iao}},//酵 jiao
{1,0,{pysm::m,pyym::ei}},//酶 mei
{1,0,{pysm::k,pyym::u}},//酷 ku
{1,0,{pysm::s,pyym::uan}},//酸 suan
{1,0,{pysm::l,pyym::ei}},//酹 lei
{1,0,{pysm::p,pyym::u}},//酺 pu
{2,3258,{pysm::nop,pyym::nop}},//酻 zui
{1,0,{pysm::h,pyym::ai}},//酼 hai
{1,0,{pysm::y,pyym::an}},//酽 yan
{2,3259,{pysm::nop,pyym::nop}},//酾 shai
{1,0,{pysm::n,pyym::iang}},//酿 niang
{2,3260,{pysm::nop,pyym::nop}},//醀 wei
{1,0,{pysm::l,pyym::u}},//醁 lu
{1,0,{pysm::l,pyym::an}},//醂 lan
{2,3261,{pysm::nop,pyym::nop}},//醃 yan
{1,0,{pysm::t,pyym::ao}},//醄 tao
{1,0,{pysm::p,pyym::ei}},//醅 pei
{1,0,{pysm::zh,pyym::an}},//醆 zhan
{1,0,{pysm::ch,pyym::un}},//醇 chun
{2,3262,{pysm::nop,pyym::nop}},//醈 tan
{1,0,{pysm::z,pyym::ui}},//醉 zui
{1,0,{pysm::zh,pyym::ui}},//醊 zhui
{2,3263,{pysm::nop,pyym::nop}},//醋 cu
{1,0,{pysm::k,pyym::un}},//醌 kun
{1,0,{pysm::t,pyym::i}},//醍 ti
{2,3264,{pysm::nop,pyym::nop}},//醎 xian
{1,0,{pysm::d,pyym::u}},//醏 du
{1,0,{pysm::h,pyym::u}},//醐 hu
{1,0,{pysm::x,pyym::u}},//醑 xu
{3,773,{pysm::nop,pyym::nop}},//醒 xing
{1,0,{pysm::t,pyym::an}},//醓 tan
{2,3265,{pysm::nop,pyym::nop}},//醔 qiu
{1,0,{pysm::ch,pyym::un}},//醕 chun
{1,0,{pysm::y,pyym::un}},//醖 yun
{1,0,{pysm::p,pyym::o}},//醗 po
{1,0,{pysm::k,pyym::e}},//醘 ke
{1,0,{pysm::s,pyym::ou}},//醙 sou
{1,0,{pysm::m,pyym::i}},//醚 mi
{2,3266,{pysm::nop,pyym::nop}},//醛 quan
{1,0,{pysm::ch,pyym::ou}},//醜 chou
{1,0,{pysm::c,pyym::uo}},//醝 cuo
{1,0,{pysm::y,pyym::un}},//醞 yun
{1,0,{pysm::y,pyym::ong}},//醟 yong
{1,0,{pysm::nop,pyym::ang}},//醠 ang
{1,0,{pysm::zh,pyym::a}},//醡 zha
{1,0,{pysm::h,pyym::ai}},//醢 hai
{1,0,{pysm::t,pyym::ang}},//醣 tang
{1,0,{pysm::j,pyym::iang}},//醤 jiang
{1,0,{pysm::p,pyym::iao}},//醥 piao
{2,3267,{pysm::nop,pyym::nop}},//醦 chen
{2,3268,{pysm::nop,pyym::nop}},//醧 yu
{1,0,{pysm::l,pyym::i}},//醨 li
{1,0,{pysm::z,pyym::ao}},//醩 zao
{1,0,{pysm::l,pyym::ao}},//醪 lao
{1,0,{pysm::y,pyym::i}},//醫 yi
{1,0,{pysm::j,pyym::iang}},//醬 jiang
{1,0,{pysm::b,pyym::u}},//醭 bu
{3,774,{pysm::nop,pyym::nop}},//醮 jiao
{1,0,{pysm::x,pyym::i}},//醯 xi
{1,0,{pysm::t,pyym::an}},//醰 tan
{2,3269,{pysm::nop,pyym::nop}},//醱 fa
{1,0,{pysm::n,pyym::ong}},//醲 nong
{2,3270,{pysm::nop,pyym::nop}},//醳 yi
{1,0,{pysm::l,pyym::i}},//醴 li
{1,0,{pysm::j,pyym::u}},//醵 ju
{4,159,{pysm::nop,pyym::nop}},//醶 yan
{2,3271,{pysm::nop,pyym::nop}},//醷 yi
{1,0,{pysm::n,pyym::iang}},//醸 niang
{1,0,{pysm::r,pyym::u}},//醹 ru
{1,0,{pysm::x,pyym::un}},//醺 xun
{3,775,{pysm::nop,pyym::nop}},//醻 chou
{1,0,{pysm::y,pyym::an}},//醼 yan
{1,0,{pysm::l,pyym::ing}},//醽 ling
{1,0,{pysm::m,pyym::i}},//醾 mi
{1,0,{pysm::m,pyym::i}},//醿 mi
{1,0,{pysm::n,pyym::iang}},//釀 niang
{1,0,{pysm::x,pyym::in}},//釁 xin
{1,0,{pysm::j,pyym::iao}},//釂 jiao
{3,776,{pysm::nop,pyym::nop}},//釃 shai
{1,0,{pysm::m,pyym::i}},//釄 mi
{1,0,{pysm::y,pyym::an}},//釅 yan
{1,0,{pysm::b,pyym::ian}},//釆 bian
{1,0,{pysm::c,pyym::ai}},//采 cai
{1,0,{pysm::sh,pyym::i}},//釈 shi
{1,0,{pysm::y,pyym::ou}},//釉 you
{1,0,{pysm::sh,pyym::i}},//释 shi
{2,3272,{pysm::nop,pyym::nop}},//釋 shi
{1,0,{pysm::l,pyym::i}},//里 li
{3,777,{pysm::nop,pyym::nop}},//重 zhong
{2,3273,{pysm::nop,pyym::nop}},//野 ye
{1,0,{pysm::l,pyym::iang}},//量 liang
{4,160,{pysm::nop,pyym::nop}},//釐 li
{1,0,{pysm::j,pyym::in}},//金 jin
{1,0,{pysm::j,pyym::in}},//釒 jin
{2,3274,{pysm::nop,pyym::nop}},//釓 qiu
{1,0,{pysm::y,pyym::i}},//釔 yi
{1,0,{pysm::l,pyym::iao}},//釕 liao
{1,0,{pysm::d,pyym::ao}},//釖 dao
{1,0,{pysm::zh,pyym::ao}},//釗 zhao
{2,3275,{pysm::nop,pyym::nop}},//釘 ding
{1,0,{pysm::p,pyym::o}},//釙 po
{1,0,{pysm::q,pyym::iu}},//釚 qiu
{1,0,{pysm::b,pyym::a}},//釛 ba
{1,0,{pysm::f,pyym::u}},//釜 fu
{1,0,{pysm::zh,pyym::en}},//針 zhen
{1,0,{pysm::zh,pyym::i}},//釞 zhi
{1,0,{pysm::b,pyym::a}},//釟 ba
{1,0,{pysm::l,pyym::uan}},//釠 luan
{1,0,{pysm::f,pyym::u}},//釡 fu
{1,0,{pysm::n,pyym::ai}},//釢 nai
{1,0,{pysm::d,pyym::iao}},//釣 diao
{2,3276,{pysm::nop,pyym::nop}},//釤 shan
{2,3277,{pysm::nop,pyym::nop}},//釥 qiao
{1,0,{pysm::k,pyym::ou}},//釦 kou
{1,0,{pysm::ch,pyym::uan}},//釧 chuan
{1,0,{pysm::z,pyym::i}},//釨 zi
{1,0,{pysm::f,pyym::an}},//釩 fan
{2,3278,{pysm::nop,pyym::nop}},//釪 hua
{2,3279,{pysm::nop,pyym::nop}},//釫 hua
{2,3280,{pysm::nop,pyym::nop}},//釬 han
{2,3281,{pysm::nop,pyym::nop}},//釭 gang
{1,0,{pysm::q,pyym::i}},//釮 qi
{1,0,{pysm::m,pyym::ang}},//釯 mang
{3,778,{pysm::nop,pyym::nop}},//釰 ri
{1,0,{pysm::d,pyym::i}},//釱 di
{1,0,{pysm::s,pyym::i}},//釲 si
{1,0,{pysm::x,pyym::i}},//釳 xi
{1,0,{pysm::y,pyym::i}},//釴 yi
{2,3282,{pysm::nop,pyym::nop}},//釵 chai
{3,779,{pysm::nop,pyym::nop}},//釶 shi
{1,0,{pysm::t,pyym::u}},//釷 tu
{1,0,{pysm::x,pyym::i}},//釸 xi
{1,0,{pysm::n,pyym::v}},//釹 nü
{1,0,{pysm::q,pyym::ian}},//釺 qian
{1,0,{pysm::q,pyym::iu}},//釻 qiu
{1,0,{pysm::j,pyym::ian}},//釼 jian
{2,3283,{pysm::nop,pyym::nop}},//釽 pi
{2,3284,{pysm::nop,pyym::nop}},//釾 ye
{2,3285,{pysm::nop,pyym::nop}},//釿 jin
{2,3286,{pysm::nop,pyym::nop}},//鈀 ba
{1,0,{pysm::f,pyym::ang}},//鈁 fang
{3,780,{pysm::nop,pyym::nop}},//鈂 chen
{1,0,{pysm::x,pyym::ing}},//鈃 xing
{1,0,{pysm::d,pyym::ou}},//鈄 dou
{1,0,{pysm::y,pyym::ue}},//鈅 yue
{2,3287,{pysm::nop,pyym::nop}},//鈆 qian
{1,0,{pysm::f,pyym::u}},//鈇 fu
{2,3288,{pysm::nop,pyym::nop}},//鈈 pi
{2,3289,{pysm::nop,pyym::nop}},//鈉 na
{2,3290,{pysm::nop,pyym::nop}},//鈊 xin
{1,0,{pysm::nop,pyym::e}},//鈋 e
{1,0,{pysm::j,pyym::ue}},//鈌 jue
{1,0,{pysm::d,pyym::un}},//鈍 dun
{1,0,{pysm::g,pyym::ou}},//鈎 gou
{1,0,{pysm::y,pyym::in}},//鈏 yin
{2,3291,{pysm::nop,pyym::nop}},//鈐 qian
{1,0,{pysm::b,pyym::an}},//鈑 ban
{2,3292,{pysm::nop,pyym::nop}},//鈒 sa
{1,0,{pysm::r,pyym::en}},//鈓 ren
{1,0,{pysm::ch,pyym::ao}},//鈔 chao
{2,3293,{pysm::nop,pyym::nop}},//鈕 niu
{1,0,{pysm::f,pyym::en}},//鈖 fen
{2,3294,{pysm::nop,pyym::nop}},//鈗 yun
{1,0,{pysm::y,pyym::i}},//鈘 yi
{1,0,{pysm::q,pyym::in}},//鈙 qin
{2,3295,{pysm::nop,pyym::nop}},//鈚 pi
{1,0,{pysm::g,pyym::uo}},//鈛 guo
{1,0,{pysm::h,pyym::ong}},//鈜 hong
{1,0,{pysm::y,pyym::in}},//鈝 yin
{1,0,{pysm::j,pyym::un}},//鈞 jun
{1,0,{pysm::d,pyym::iao}},//鈟 diao
{1,0,{pysm::y,pyym::i}},//鈠 yi
{1,0,{pysm::zh,pyym::ong}},//鈡 zhong
{1,0,{pysm::x,pyym::i}},//鈢 xi
{1,0,{pysm::g,pyym::ai}},//鈣 gai
{1,0,{pysm::r,pyym::i}},//鈤 ri
{1,0,{pysm::h,pyym::uo}},//鈥 huo
{1,0,{pysm::t,pyym::ai}},//鈦 tai
{1,0,{pysm::k,pyym::ang}},//鈧 kang
{1,0,{pysm::y,pyym::uan}},//鈨 yuan
{1,0,{pysm::l,pyym::u}},//鈩 lu
{1,0,{pysm::nop,pyym::e}},//鈪 e
{1,0,{pysm::q,pyym::in}},//鈫 qin
{1,0,{pysm::d,pyym::uo}},//鈬 duo
{1,0,{pysm::z,pyym::i}},//鈭 zi
{1,0,{pysm::n,pyym::i}},//鈮 ni
{1,0,{pysm::t,pyym::u}},//鈯 tu
{1,0,{pysm::sh,pyym::i}},//鈰 shi
{1,0,{pysm::m,pyym::in}},//鈱 min
{2,3296,{pysm::nop,pyym::nop}},//鈲 gu
{1,0,{pysm::k,pyym::e}},//鈳 ke
{1,0,{pysm::l,pyym::ing}},//鈴 ling
{1,0,{pysm::b,pyym::ing}},//鈵 bing
{3,781,{pysm::nop,pyym::nop}},//鈶 si
{2,3297,{pysm::nop,pyym::nop}},//鈷 gu
{1,0,{pysm::b,pyym::o}},//鈸 bo
{1,0,{pysm::p,pyym::i}},//鈹 pi
{1,0,{pysm::y,pyym::u}},//鈺 yu
{1,0,{pysm::s,pyym::i}},//鈻 si
{1,0,{pysm::z,pyym::uo}},//鈼 zuo
{1,0,{pysm::b,pyym::u}},//鈽 bu
{2,3298,{pysm::nop,pyym::nop}},//鈾 you
{2,3299,{pysm::nop,pyym::nop}},//鈿 tian
{2,3300,{pysm::nop,pyym::nop}},//鉀 jia
{1,0,{pysm::zh,pyym::en}},//鉁 zhen
{1,0,{pysm::sh,pyym::i}},//鉂 shi
{2,3301,{pysm::nop,pyym::nop}},//鉃 shi
{2,3302,{pysm::nop,pyym::nop}},//鉄 zhi
{1,0,{pysm::j,pyym::u}},//鉅 ju
{3,782,{pysm::nop,pyym::nop}},//鉆 chan
{2,3303,{pysm::nop,pyym::nop}},//鉇 shi
{5,50,{pysm::nop,pyym::nop}},//鉈 shi
{1,0,{pysm::x,pyym::uan}},//鉉 xuan
{1,0,{pysm::zh,pyym::ao}},//鉊 zhao
{2,3304,{pysm::nop,pyym::nop}},//鉋 bao
{1,0,{pysm::h,pyym::e}},//鉌 he
{2,3305,{pysm::nop,pyym::nop}},//鉍 bi
{1,0,{pysm::sh,pyym::eng}},//鉎 sheng
{6,3,{pysm::nop,pyym::nop}},//鉏 chu
{2,3306,{pysm::nop,pyym::nop}},//鉐 shi
{1,0,{pysm::b,pyym::o}},//鉑 bo
{1,0,{pysm::zh,pyym::u}},//鉒 zhu
{1,0,{pysm::ch,pyym::i}},//鉓 chi
{1,0,{pysm::z,pyym::a}},//鉔 za
{1,0,{pysm::p,pyym::o}},//鉕 po
{1,0,{pysm::t,pyym::ong}},//鉖 tong
{2,3307,{pysm::nop,pyym::nop}},//鉗 qian
{1,0,{pysm::f,pyym::u}},//鉘 fu
{1,0,{pysm::zh,pyym::ai}},//鉙 zhai
{2,3308,{pysm::nop,pyym::nop}},//鉚 liu
{2,3309,{pysm::nop,pyym::nop}},//鉛 qian
{1,0,{pysm::f,pyym::u}},//鉜 fu
{1,0,{pysm::l,pyym::i}},//鉝 li
{1,0,{pysm::y,pyym::ue}},//鉞 yue
{1,0,{pysm::p,pyym::i}},//鉟 pi
{1,0,{pysm::y,pyym::ang}},//鉠 yang
{1,0,{pysm::b,pyym::an}},//鉡 ban
{1,0,{pysm::b,pyym::o}},//鉢 bo
{1,0,{pysm::j,pyym::ie}},//鉣 jie
{2,3310,{pysm::nop,pyym::nop}},//鉤 gou
{2,3311,{pysm::nop,pyym::nop}},//鉥 shu
{1,0,{pysm::zh,pyym::eng}},//鉦 zheng
{1,0,{pysm::m,pyym::u}},//鉧 mu
{3,783,{pysm::nop,pyym::nop}},//鉨 xi
{2,3312,{pysm::nop,pyym::nop}},//鉩 xi
{1,0,{pysm::d,pyym::i}},//鉪 di
{1,0,{pysm::j,pyym::ia}},//鉫 jia
{1,0,{pysm::m,pyym::u}},//鉬 mu
{1,0,{pysm::t,pyym::an}},//鉭 tan
{2,3313,{pysm::nop,pyym::nop}},//鉮 huan
{1,0,{pysm::y,pyym::i}},//鉯 yi
{1,0,{pysm::s,pyym::i}},//鉰 si
{1,0,{pysm::k,pyym::uang}},//鉱 kuang
{1,0,{pysm::k,pyym::a}},//鉲 ka
{1,0,{pysm::b,pyym::ei}},//鉳 bei
{1,0,{pysm::j,pyym::ian}},//鉴 jian
{2,3314,{pysm::nop,pyym::nop}},//鉵 tong
{1,0,{pysm::x,pyym::ing}},//鉶 xing
{1,0,{pysm::h,pyym::ong}},//鉷 hong
{1,0,{pysm::j,pyym::iao}},//鉸 jiao
{1,0,{pysm::ch,pyym::i}},//鉹 chi
{2,3315,{pysm::nop,pyym::nop}},//鉺 er
{2,3316,{pysm::nop,pyym::nop}},//鉻 luo
{2,3317,{pysm::nop,pyym::nop}},//鉼 bing
{1,0,{pysm::sh,pyym::i}},//鉽 shi
{2,3318,{pysm::nop,pyym::nop}},//鉾 mou
{4,161,{pysm::nop,pyym::nop}},//鉿 jia
{1,0,{pysm::y,pyym::in}},//銀 yin
{1,0,{pysm::j,pyym::un}},//銁 jun
{1,0,{pysm::zh,pyym::ou}},//銂 zhou
{1,0,{pysm::ch,pyym::ong}},//銃 chong
{2,3319,{pysm::nop,pyym::nop}},//銄 xiang
{1,0,{pysm::t,pyym::ong}},//銅 tong
{1,0,{pysm::m,pyym::o}},//銆 mo
{1,0,{pysm::l,pyym::ei}},//銇 lei
{1,0,{pysm::j,pyym::i}},//銈 ji
{2,3320,{pysm::nop,pyym::nop}},//銉 yu
{2,3321,{pysm::nop,pyym::nop}},//銊 xu
{1,0,{pysm::r,pyym::en}},//銋 ren
{1,0,{pysm::z,pyym::un}},//銌 zun
{1,0,{pysm::zh,pyym::i}},//銍 zhi
{1,0,{pysm::q,pyym::iong}},//銎 qiong
{2,3322,{pysm::nop,pyym::nop}},//銏 shan
{2,3323,{pysm::nop,pyym::nop}},//銐 chi
{2,3324,{pysm::nop,pyym::nop}},//銑 xian
{2,3325,{pysm::nop,pyym::nop}},//銒 xing
{1,0,{pysm::q,pyym::uan}},//銓 quan
{1,0,{pysm::p,pyym::i}},//銔 pi
{2,3326,{pysm::nop,pyym::nop}},//銕 tie
{1,0,{pysm::zh,pyym::u}},//銖 zhu
{2,3327,{pysm::nop,pyym::nop}},//銗 xiang
{1,0,{pysm::m,pyym::ing}},//銘 ming
{1,0,{pysm::k,pyym::ua}},//銙 kua
{4,162,{pysm::nop,pyym::nop}},//銚 yao
{3,784,{pysm::nop,pyym::nop}},//銛 xian
{1,0,{pysm::x,pyym::ian}},//銜 xian
{1,0,{pysm::x,pyym::iu}},//銝 xiu
{1,0,{pysm::j,pyym::un}},//銞 jun
{1,0,{pysm::ch,pyym::a}},//銟 cha
{1,0,{pysm::l,pyym::ao}},//銠 lao
{1,0,{pysm::j,pyym::i}},//銡 ji
{1,0,{pysm::p,pyym::i}},//銢 pi
{1,0,{pysm::r,pyym::u}},//銣 ru
{1,0,{pysm::m,pyym::i}},//銤 mi
{1,0,{pysm::y,pyym::i}},//銥 yi
{1,0,{pysm::y,pyym::in}},//銦 yin
{1,0,{pysm::g,pyym::uang}},//銧 guang
{1,0,{pysm::nop,pyym::an}},//銨 an
{1,0,{pysm::d,pyym::iu}},//銩 diu
{1,0,{pysm::y,pyym::ou}},//銪 you
{1,0,{pysm::s,pyym::e}},//銫 se
{1,0,{pysm::k,pyym::ao}},//銬 kao
{1,0,{pysm::q,pyym::ian}},//銭 qian
{1,0,{pysm::l,pyym::uan}},//銮 luan
{1,0,{pysm::s,pyym::i}},//銯 si
{1,0,{pysm::nop,pyym::ai}},//銰 ai
{1,0,{pysm::d,pyym::iao}},//銱 diao
{1,0,{pysm::h,pyym::an}},//銲 han
{1,0,{pysm::r,pyym::ui}},//銳 rui
{2,3328,{pysm::nop,pyym::nop}},//銴 shi
{1,0,{pysm::k,pyym::eng}},//銵 keng
{1,0,{pysm::q,pyym::iu}},//銶 qiu
{1,0,{pysm::x,pyym::iao}},//銷 xiao
{2,3329,{pysm::nop,pyym::nop}},//銸 zhe
{2,3330,{pysm::nop,pyym::nop}},//銹 xiu
{1,0,{pysm::z,pyym::ang}},//銺 zang
{1,0,{pysm::t,pyym::i}},//銻 ti
{1,0,{pysm::c,pyym::uo}},//銼 cuo
{1,0,{pysm::g,pyym::ua}},//銽 gua
{2,3331,{pysm::nop,pyym::nop}},//銾 hong
{2,3332,{pysm::nop,pyym::nop}},//銿 zhong
{3,785,{pysm::nop,pyym::nop}},//鋀 tou
{1,0,{pysm::l,pyym::v}},//鋁 lü
{2,3333,{pysm::nop,pyym::nop}},//鋂 mei
{1,0,{pysm::l,pyym::ang}},//鋃 lang
{1,0,{pysm::w,pyym::an}},//鋄 wan
{2,3334,{pysm::nop,pyym::nop}},//鋅 xin
{2,3335,{pysm::nop,pyym::nop}},//鋆 yun
{1,0,{pysm::b,pyym::ei}},//鋇 bei
{1,0,{pysm::w,pyym::u}},//鋈 wu
{1,0,{pysm::s,pyym::u}},//鋉 su
{1,0,{pysm::y,pyym::u}},//鋊 yu
{2,3336,{pysm::nop,pyym::nop}},//鋋 chan
{2,3337,{pysm::nop,pyym::nop}},//鋌 ding
{1,0,{pysm::b,pyym::o}},//鋍 bo
{1,0,{pysm::h,pyym::an}},//鋎 han
{1,0,{pysm::j,pyym::ia}},//鋏 jia
{1,0,{pysm::h,pyym::ong}},//鋐 hong
{3,786,{pysm::nop,pyym::nop}},//鋑 cuan
{1,0,{pysm::f,pyym::eng}},//鋒 feng
{1,0,{pysm::ch,pyym::an}},//鋓 chan
{1,0,{pysm::w,pyym::an}},//鋔 wan
{1,0,{pysm::zh,pyym::i}},//鋕 zhi
{2,3338,{pysm::nop,pyym::nop}},//鋖 si
{2,3339,{pysm::nop,pyym::nop}},//鋗 xuan
{3,787,{pysm::nop,pyym::nop}},//鋘 hua
{2,3340,{pysm::nop,pyym::nop}},//鋙 yu
{1,0,{pysm::t,pyym::iao}},//鋚 tiao
{1,0,{pysm::k,pyym::uang}},//鋛 kuang
{2,3341,{pysm::nop,pyym::nop}},//鋜 zhuo
{1,0,{pysm::l,pyym::ve}},//鋝 lüe
{2,3342,{pysm::nop,pyym::nop}},//鋞 xing
{3,788,{pysm::nop,pyym::nop}},//鋟 qin
{1,0,{pysm::sh,pyym::en}},//鋠 shen
{1,0,{pysm::h,pyym::an}},//鋡 han
{1,0,{pysm::l,pyym::ve}},//鋢 lüe
{1,0,{pysm::y,pyym::e}},//鋣 ye
{2,3343,{pysm::nop,pyym::nop}},//鋤 chu
{1,0,{pysm::z,pyym::eng}},//鋥 zeng
{1,0,{pysm::j,pyym::u}},//鋦 ju
{1,0,{pysm::x,pyym::ian}},//鋧 xian
{2,3344,{pysm::nop,pyym::nop}},//鋨 tie
{1,0,{pysm::m,pyym::ang}},//鋩 mang
{1,0,{pysm::p,pyym::u}},//鋪 pu
{1,0,{pysm::l,pyym::i}},//鋫 li
{1,0,{pysm::p,pyym::an}},//鋬 pan
{3,789,{pysm::nop,pyym::nop}},//鋭 rui
{1,0,{pysm::ch,pyym::eng}},//鋮 cheng
{1,0,{pysm::g,pyym::ao}},//鋯 gao
{1,0,{pysm::l,pyym::i}},//鋰 li
{1,0,{pysm::t,pyym::e}},//鋱 te
{1,0,{pysm::b,pyym::ing}},//鋲 bing
{1,0,{pysm::zh,pyym::u}},//鋳 zhu
{1,0,{pysm::zh,pyym::en}},//鋴 zhen
{1,0,{pysm::t,pyym::u}},//鋵 tu
{1,0,{pysm::l,pyym::iu}},//鋶 liu
{2,3345,{pysm::nop,pyym::nop}},//鋷 zui
{1,0,{pysm::j,pyym::u}},//鋸 ju
{1,0,{pysm::ch,pyym::ang}},//鋹 chang
{2,3346,{pysm::nop,pyym::nop}},//鋺 yuan
{1,0,{pysm::j,pyym::ian}},//鋻 jian
{1,0,{pysm::g,pyym::ang}},//鋼 gang
{1,0,{pysm::d,pyym::iao}},//鋽 diao
{1,0,{pysm::t,pyym::ao}},//鋾 tao
{1,0,{pysm::ch,pyym::ang}},//鋿 chang
{2,3347,{pysm::nop,pyym::nop}},//錀 lun
{3,790,{pysm::nop,pyym::nop}},//錁 guo
{1,0,{pysm::l,pyym::ing}},//錂 ling
{1,0,{pysm::p,pyym::i}},//錃 pi
{1,0,{pysm::l,pyym::u}},//錄 lu
{1,0,{pysm::l,pyym::i}},//錅 li
{1,0,{pysm::q,pyym::iang}},//錆 qiang
{3,791,{pysm::nop,pyym::nop}},//錇 pou
{1,0,{pysm::j,pyym::uan}},//錈 juan
{1,0,{pysm::m,pyym::in}},//錉 min
{2,3348,{pysm::nop,pyym::nop}},//錊 zui
{2,3349,{pysm::nop,pyym::nop}},//錋 peng
{1,0,{pysm::nop,pyym::an}},//錌 an
{3,792,{pysm::nop,pyym::nop}},//錍 pi
{3,793,{pysm::nop,pyym::nop}},//錎 xian
{1,0,{pysm::y,pyym::a}},//錏 ya
{1,0,{pysm::zh,pyym::ui}},//錐 zhui
{2,3350,{pysm::nop,pyym::nop}},//錑 lei
{2,3351,{pysm::nop,pyym::nop}},//錒 ke
{1,0,{pysm::k,pyym::ong}},//錓 kong
{1,0,{pysm::t,pyym::a}},//錔 ta
{2,3352,{pysm::nop,pyym::nop}},//錕 kun
{1,0,{pysm::d,pyym::u}},//錖 du
{3,794,{pysm::nop,pyym::nop}},//錗 nei
{1,0,{pysm::ch,pyym::ui}},//錘 chui
{1,0,{pysm::z,pyym::i}},//錙 zi
{1,0,{pysm::zh,pyym::eng}},//錚 zheng
{1,0,{pysm::b,pyym::en}},//錛 ben
{1,0,{pysm::n,pyym::ie}},//錜 nie
{1,0,{pysm::z,pyym::ong}},//錝 zong
{3,795,{pysm::nop,pyym::nop}},//錞 chun
{3,796,{pysm::nop,pyym::nop}},//錟 tan
{1,0,{pysm::d,pyym::ing}},//錠 ding
{2,3353,{pysm::nop,pyym::nop}},//錡 qi
{2,3354,{pysm::nop,pyym::nop}},//錢 qian
{2,3355,{pysm::nop,pyym::nop}},//錣 zhui
{1,0,{pysm::j,pyym::i}},//錤 ji
{1,0,{pysm::y,pyym::u}},//錥 yu
{1,0,{pysm::j,pyym::in}},//錦 jin
{1,0,{pysm::g,pyym::uan}},//錧 guan
{1,0,{pysm::m,pyym::ao}},//錨 mao
{1,0,{pysm::ch,pyym::ang}},//錩 chang
{2,3356,{pysm::nop,pyym::nop}},//錪 tian
{2,3357,{pysm::nop,pyym::nop}},//錫 xi
{1,0,{pysm::l,pyym::ian}},//錬 lian
{2,3358,{pysm::nop,pyym::nop}},//錭 tao
{1,0,{pysm::g,pyym::u}},//錮 gu
{3,797,{pysm::nop,pyym::nop}},//錯 cuo
{1,0,{pysm::sh,pyym::u}},//錰 shu
{1,0,{pysm::zh,pyym::en}},//錱 zhen
{2,3359,{pysm::nop,pyym::nop}},//録 lu
{1,0,{pysm::m,pyym::eng}},//錳 meng
{1,0,{pysm::l,pyym::u}},//錴 lu
{1,0,{pysm::h,pyym::ua}},//錵 hua
{1,0,{pysm::b,pyym::iao}},//錶 biao
{1,0,{pysm::g,pyym::a}},//錷 ga
{1,0,{pysm::l,pyym::ai}},//錸 lai
{1,0,{pysm::k,pyym::en}},//錹 ken
{1,0,{pysm::f,pyym::ang}},//錺 fang
{1,0,{pysm::w,pyym::u}},//錻 wu
{1,0,{pysm::n,pyym::ai}},//錼 nai
{2,3360,{pysm::nop,pyym::nop}},//錽 wan
{1,0,{pysm::z,pyym::an}},//錾 zan
{1,0,{pysm::h,pyym::u}},//錿 hu
{1,0,{pysm::d,pyym::e}},//鍀 de
{1,0,{pysm::x,pyym::ian}},//鍁 xian
{1,0,{pysm::p,pyym::ian}},//鍂 pian
{1,0,{pysm::h,pyym::uo}},//鍃 huo
{1,0,{pysm::l,pyym::iang}},//鍄 liang
{1,0,{pysm::f,pyym::a}},//鍅 fa
{1,0,{pysm::m,pyym::en}},//鍆 men
{2,3361,{pysm::nop,pyym::nop}},//鍇 kai
{1,0,{pysm::y,pyym::ing}},//鍈 ying
{3,798,{pysm::nop,pyym::nop}},//鍉 di
{2,3362,{pysm::nop,pyym::nop}},//鍊 lian
{1,0,{pysm::g,pyym::uo}},//鍋 guo
{1,0,{pysm::x,pyym::ian}},//鍌 xian
{1,0,{pysm::d,pyym::u}},//鍍 du
{1,0,{pysm::t,pyym::u}},//鍎 tu
{1,0,{pysm::w,pyym::ei}},//鍏 wei
{1,0,{pysm::z,pyym::ong}},//鍐 zong
{1,0,{pysm::f,pyym::u}},//鍑 fu
{1,0,{pysm::r,pyym::ou}},//鍒 rou
{1,0,{pysm::j,pyym::i}},//鍓 ji
{1,0,{pysm::nop,pyym::e}},//鍔 e
{1,0,{pysm::j,pyym::un}},//鍕 jun
{2,3363,{pysm::nop,pyym::nop}},//鍖 chen
{1,0,{pysm::t,pyym::i}},//鍗 ti
{1,0,{pysm::zh,pyym::a}},//鍘 zha
{1,0,{pysm::h,pyym::u}},//鍙 hu
{1,0,{pysm::y,pyym::ang}},//鍚 yang
{1,0,{pysm::d,pyym::uan}},//鍛 duan
{1,0,{pysm::x,pyym::ia}},//鍜 xia
{1,0,{pysm::y,pyym::u}},//鍝 yu
{1,0,{pysm::k,pyym::eng}},//鍞 keng
{1,0,{pysm::sh,pyym::eng}},//鍟 sheng
{1,0,{pysm::h,pyym::uang}},//鍠 huang
{1,0,{pysm::w,pyym::ei}},//鍡 wei
{1,0,{pysm::f,pyym::u}},//鍢 fu
{1,0,{pysm::zh,pyym::ao}},//鍣 zhao
{1,0,{pysm::ch,pyym::a}},//鍤 cha
{1,0,{pysm::q,pyym::ie}},//鍥 qie
{2,3364,{pysm::nop,pyym::nop}},//鍦 shi
{1,0,{pysm::h,pyym::ong}},//鍧 hong
{1,0,{pysm::k,pyym::ui}},//鍨 kui
{2,3365,{pysm::nop,pyym::nop}},//鍩 tian
{1,0,{pysm::m,pyym::ou}},//鍪 mou
{1,0,{pysm::q,pyym::iao}},//鍫 qiao
{1,0,{pysm::q,pyym::iao}},//鍬 qiao
{1,0,{pysm::h,pyym::ou}},//鍭 hou
{1,0,{pysm::t,pyym::ou}},//鍮 tou
{1,0,{pysm::c,pyym::ong}},//鍯 cong
{1,0,{pysm::h,pyym::uan}},//鍰 huan
{2,3366,{pysm::nop,pyym::nop}},//鍱 ye
{1,0,{pysm::m,pyym::in}},//鍲 min
{1,0,{pysm::j,pyym::ian}},//鍳 jian
{1,0,{pysm::d,pyym::uan}},//鍴 duan
{1,0,{pysm::j,pyym::ian}},//鍵 jian
{2,3367,{pysm::nop,pyym::nop}},//鍶 song
{1,0,{pysm::k,pyym::ui}},//鍷 kui
{1,0,{pysm::h,pyym::u}},//鍸 hu
{1,0,{pysm::x,pyym::uan}},//鍹 xuan
{3,799,{pysm::nop,pyym::nop}},//鍺 duo
{1,0,{pysm::j,pyym::ie}},//鍻 jie
{2,3368,{pysm::nop,pyym::nop}},//鍼 zhen
{1,0,{pysm::b,pyym::ian}},//鍽 bian
{1,0,{pysm::zh,pyym::ong}},//鍾 zhong
{1,0,{pysm::z,pyym::i}},//鍿 zi
{1,0,{pysm::x,pyym::iu}},//鎀 xiu
{1,0,{pysm::y,pyym::e}},//鎁 ye
{1,0,{pysm::m,pyym::ei}},//鎂 mei
{1,0,{pysm::p,pyym::ai}},//鎃 pai
{1,0,{pysm::nop,pyym::ai}},//鎄 ai
{1,0,{pysm::j,pyym::ie}},//鎅 jie
{1,0,{pysm::q,pyym::ian}},//鎆 qian
{1,0,{pysm::m,pyym::ei}},//鎇 mei
{2,3369,{pysm::nop,pyym::nop}},//鎈 suo
{2,3370,{pysm::nop,pyym::nop}},//鎉 da
{2,3371,{pysm::nop,pyym::nop}},//鎊 bang
{1,0,{pysm::x,pyym::ia}},//鎋 xia
{1,0,{pysm::l,pyym::ian}},//鎌 lian
{2,3372,{pysm::nop,pyym::nop}},//鎍 suo
{1,0,{pysm::k,pyym::ai}},//鎎 kai
{1,0,{pysm::l,pyym::iu}},//鎏 liu
{2,3373,{pysm::nop,pyym::nop}},//鎐 yao
{3,800,{pysm::nop,pyym::nop}},//鎑 ye
{2,3374,{pysm::nop,pyym::nop}},//鎒 nou
{1,0,{pysm::w,pyym::eng}},//鎓 weng
{1,0,{pysm::r,pyym::ong}},//鎔 rong
{1,0,{pysm::t,pyym::ang}},//鎕 tang
{1,0,{pysm::s,pyym::uo}},//鎖 suo
{2,3375,{pysm::nop,pyym::nop}},//鎗 qiang
{2,3376,{pysm::nop,pyym::nop}},//鎘 li
{1,0,{pysm::sh,pyym::uo}},//鎙 shuo
{3,801,{pysm::nop,pyym::nop}},//鎚 chui
{1,0,{pysm::b,pyym::o}},//鎛 bo
{1,0,{pysm::p,pyym::an}},//鎜 pan
{2,3377,{pysm::nop,pyym::nop}},//鎝 da
{2,3378,{pysm::nop,pyym::nop}},//鎞 bi
{1,0,{pysm::s,pyym::ang}},//鎟 sang
{1,0,{pysm::g,pyym::ang}},//鎠 gang
{1,0,{pysm::z,pyym::i}},//鎡 zi
{1,0,{pysm::w,pyym::u}},//鎢 wu
{2,3379,{pysm::nop,pyym::nop}},//鎣 ying
{1,0,{pysm::h,pyym::uang}},//鎤 huang
{1,0,{pysm::t,pyym::iao}},//鎥 tiao
{1,0,{pysm::l,pyym::iu}},//鎦 liu
{1,0,{pysm::k,pyym::ai}},//鎧 kai
{1,0,{pysm::s,pyym::un}},//鎨 sun
{3,802,{pysm::nop,pyym::nop}},//鎩 sha
{1,0,{pysm::s,pyym::ou}},//鎪 sou
{1,0,{pysm::w,pyym::an}},//鎫 wan
{2,3380,{pysm::nop,pyym::nop}},//鎬 hao
{1,0,{pysm::zh,pyym::en}},//鎭 zhen
{2,3381,{pysm::nop,pyym::nop}},//鎮 zhen
{2,3382,{pysm::nop,pyym::nop}},//鎯 lang
{1,0,{pysm::y,pyym::i}},//鎰 yi
{1,0,{pysm::y,pyym::uan}},//鎱 yuan
{1,0,{pysm::t,pyym::ang}},//鎲 tang
{1,0,{pysm::n,pyym::ie}},//鎳 nie
{1,0,{pysm::x,pyym::i}},//鎴 xi
{1,0,{pysm::j,pyym::ia}},//鎵 jia
{1,0,{pysm::g,pyym::e}},//鎶 ge
{1,0,{pysm::m,pyym::a}},//鎷 ma
{1,0,{pysm::j,pyym::uan}},//鎸 juan
{1,0,{pysm::s,pyym::ong}},//鎹 song
{1,0,{pysm::z,pyym::u}},//鎺 zu
{1,0,{pysm::s,pyym::uo}},//鎻 suo
{1,0,{pysm::x,pyym::ia}},//鎼 xia
{1,0,{pysm::f,pyym::eng}},//鎽 feng
{1,0,{pysm::w,pyym::en}},//鎾 wen
{1,0,{pysm::n,pyym::a}},//鎿 na
{1,0,{pysm::l,pyym::u}},//鏀 lu
{1,0,{pysm::s,pyym::uo}},//鏁 suo
{2,3383,{pysm::nop,pyym::nop}},//鏂 ou
{2,3384,{pysm::nop,pyym::nop}},//鏃 zu
{1,0,{pysm::t,pyym::uan}},//鏄 tuan
{1,0,{pysm::x,pyym::iu}},//鏅 xiu
{1,0,{pysm::g,pyym::uan}},//鏆 guan
{1,0,{pysm::x,pyym::uan}},//鏇 xuan
{1,0,{pysm::l,pyym::ian}},//鏈 lian
{2,3385,{pysm::nop,pyym::nop}},//鏉 shou
{1,0,{pysm::nop,pyym::ao}},//鏊 ao
{1,0,{pysm::m,pyym::an}},//鏋 man
{1,0,{pysm::m,pyym::o}},//鏌 mo
{1,0,{pysm::l,pyym::uo}},//鏍 luo
{1,0,{pysm::b,pyym::i}},//鏎 bi
{1,0,{pysm::w,pyym::ei}},//鏏 wei
{2,3386,{pysm::nop,pyym::nop}},//鏐 liu
{1,0,{pysm::d,pyym::i}},//鏑 di
{3,803,{pysm::nop,pyym::nop}},//鏒 san
{2,3387,{pysm::nop,pyym::nop}},//鏓 zong
{1,0,{pysm::y,pyym::i}},//鏔 yi
{2,3388,{pysm::nop,pyym::nop}},//鏕 lu
{2,3389,{pysm::nop,pyym::nop}},//鏖 ao
{1,0,{pysm::k,pyym::eng}},//鏗 keng
{1,0,{pysm::q,pyym::iang}},//鏘 qiang
{1,0,{pysm::c,pyym::ui}},//鏙 cui
{1,0,{pysm::q,pyym::i}},//鏚 qi
{1,0,{pysm::ch,pyym::ang}},//鏛 chang
{1,0,{pysm::t,pyym::ang}},//鏜 tang
{1,0,{pysm::m,pyym::an}},//鏝 man
{1,0,{pysm::y,pyym::ong}},//鏞 yong
{1,0,{pysm::ch,pyym::an}},//鏟 chan
{1,0,{pysm::f,pyym::eng}},//鏠 feng
{1,0,{pysm::j,pyym::ing}},//鏡 jing
{1,0,{pysm::b,pyym::iao}},//鏢 biao
{1,0,{pysm::sh,pyym::u}},//鏣 shu
{2,3390,{pysm::nop,pyym::nop}},//鏤 lou
{1,0,{pysm::x,pyym::iu}},//鏥 xiu
{1,0,{pysm::c,pyym::ong}},//鏦 cong
{1,0,{pysm::l,pyym::ong}},//鏧 long
{1,0,{pysm::z,pyym::an}},//鏨 zan
{2,3391,{pysm::nop,pyym::nop}},//鏩 jian
{1,0,{pysm::c,pyym::ao}},//鏪 cao
{1,0,{pysm::l,pyym::i}},//鏫 li
{1,0,{pysm::x,pyym::ia}},//鏬 xia
{1,0,{pysm::x,pyym::i}},//鏭 xi
{1,0,{pysm::k,pyym::ang}},//鏮 kang
{1,0,{pysm::sh,pyym::uang}},//鏯 shuang
{1,0,{pysm::b,pyym::eng}},//鏰 beng
{1,0,{pysm::zh,pyym::ang}},//鏱 zhang
{1,0,{pysm::q,pyym::ian}},//鏲 qian
{1,0,{pysm::ch,pyym::eng}},//鏳 cheng
{1,0,{pysm::l,pyym::u}},//鏴 lu
{1,0,{pysm::h,pyym::ua}},//鏵 hua
{1,0,{pysm::j,pyym::i}},//鏶 ji
{1,0,{pysm::p,pyym::u}},//鏷 pu
{3,804,{pysm::nop,pyym::nop}},//鏸 hui
{1,0,{pysm::q,pyym::iang}},//鏹 qiang
{1,0,{pysm::p,pyym::o}},//鏺 po
{1,0,{pysm::l,pyym::in}},//鏻 lin
{1,0,{pysm::s,pyym::e}},//鏼 se
{1,0,{pysm::x,pyym::iu}},//鏽 xiu
{3,805,{pysm::nop,pyym::nop}},//鏾 san
{1,0,{pysm::ch,pyym::eng}},//鏿 cheng
{2,3392,{pysm::nop,pyym::nop}},//鐀 kui
{1,0,{pysm::s,pyym::i}},//鐁 si
{1,0,{pysm::l,pyym::iu}},//鐂 liu
{1,0,{pysm::n,pyym::ao}},//鐃 nao
{1,0,{pysm::h,pyym::uang}},//鐄 huang
{1,0,{pysm::p,pyym::ie}},//鐅 pie
{1,0,{pysm::s,pyym::ui}},//鐆 sui
{1,0,{pysm::f,pyym::an}},//鐇 fan
{1,0,{pysm::q,pyym::iao}},//鐈 qiao
{1,0,{pysm::q,pyym::uan}},//鐉 quan
{1,0,{pysm::y,pyym::ang}},//鐊 yang
{1,0,{pysm::t,pyym::ang}},//鐋 tang
{1,0,{pysm::x,pyym::iang}},//鐌 xiang
{2,3393,{pysm::nop,pyym::nop}},//鐍 jue
{1,0,{pysm::j,pyym::iao}},//鐎 jiao
{1,0,{pysm::z,pyym::un}},//鐏 zun
{1,0,{pysm::l,pyym::iao}},//鐐 liao
{1,0,{pysm::q,pyym::ie}},//鐑 qie
{1,0,{pysm::l,pyym::ao}},//鐒 lao
{2,3394,{pysm::nop,pyym::nop}},//鐓 dui
{1,0,{pysm::x,pyym::in}},//鐔 xin
{1,0,{pysm::z,pyym::an}},//鐕 zan
{2,3395,{pysm::nop,pyym::nop}},//鐖 ji
{1,0,{pysm::j,pyym::ian}},//鐗 jian
{1,0,{pysm::zh,pyym::ong}},//鐘 zhong
{1,0,{pysm::d,pyym::eng}},//鐙 deng
{1,0,{pysm::y,pyym::a}},//鐚 ya
{1,0,{pysm::y,pyym::ing}},//鐛 ying
{2,3396,{pysm::nop,pyym::nop}},//鐜 dui
{1,0,{pysm::j,pyym::ue}},//鐝 jue
{1,0,{pysm::n,pyym::ou}},//鐞 nou
{2,3397,{pysm::nop,pyym::nop}},//鐟 zan
{1,0,{pysm::p,pyym::u}},//鐠 pu
{1,0,{pysm::t,pyym::ie}},//鐡 tie
{1,0,{pysm::f,pyym::an}},//鐢 fan
{1,0,{pysm::ch,pyym::eng}},//鐣 cheng
{1,0,{pysm::d,pyym::ing}},//鐤 ding
{1,0,{pysm::sh,pyym::an}},//鐥 shan
{1,0,{pysm::k,pyym::ai}},//鐦 kai
{1,0,{pysm::j,pyym::ian}},//鐧 jian
{1,0,{pysm::f,pyym::ei}},//鐨 fei
{1,0,{pysm::s,pyym::ui}},//鐩 sui
{1,0,{pysm::l,pyym::u}},//鐪 lu
{1,0,{pysm::j,pyym::uan}},//鐫 juan
{1,0,{pysm::h,pyym::ui}},//鐬 hui
{1,0,{pysm::y,pyym::u}},//鐭 yu
{1,0,{pysm::l,pyym::ian}},//鐮 lian
{1,0,{pysm::zh,pyym::uo}},//鐯 zhuo
{3,806,{pysm::nop,pyym::nop}},//鐰 qiao
{2,3398,{pysm::nop,pyym::nop}},//鐱 jian
{2,3399,{pysm::nop,pyym::nop}},//鐲 zhuo
{1,0,{pysm::l,pyym::ei}},//鐳 lei
{2,3400,{pysm::nop,pyym::nop}},//鐴 bi
{2,3401,{pysm::nop,pyym::nop}},//鐵 tie
{2,3402,{pysm::nop,pyym::nop}},//鐶 huan
{1,0,{pysm::y,pyym::e}},//鐷 ye
{1,0,{pysm::d,pyym::uo}},//鐸 duo
{1,0,{pysm::g,pyym::uo}},//鐹 guo
{3,807,{pysm::nop,pyym::nop}},//鐺 dang
{2,3403,{pysm::nop,pyym::nop}},//鐻 ju
{2,3404,{pysm::nop,pyym::nop}},//鐼 fen
{1,0,{pysm::d,pyym::a}},//鐽 da
{1,0,{pysm::b,pyym::ei}},//鐾 bei
{1,0,{pysm::y,pyym::i}},//鐿 yi
{1,0,{pysm::nop,pyym::ai}},//鑀 ai
{1,0,{pysm::z,pyym::ong}},//鑁 zong
{1,0,{pysm::x,pyym::un}},//鑂 xun
{1,0,{pysm::d,pyym::iao}},//鑃 diao
{1,0,{pysm::zh,pyym::u}},//鑄 zhu
{1,0,{pysm::h,pyym::eng}},//鑅 heng
{1,0,{pysm::zh,pyym::ui}},//鑆 zhui
{1,0,{pysm::j,pyym::i}},//鑇 ji
{2,3405,{pysm::nop,pyym::nop}},//鑈 nie
{1,0,{pysm::h,pyym::e}},//鑉 he
{1,0,{pysm::h,pyym::uo}},//鑊 huo
{1,0,{pysm::q,pyym::ing}},//鑋 qing
{1,0,{pysm::b,pyym::in}},//鑌 bin
{1,0,{pysm::y,pyym::ing}},//鑍 ying
{1,0,{pysm::k,pyym::ui}},//鑎 kui
{1,0,{pysm::n,pyym::ing}},//鑏 ning
{3,808,{pysm::nop,pyym::nop}},//鑐 xu
{1,0,{pysm::j,pyym::ian}},//鑑 jian
{1,0,{pysm::j,pyym::ian}},//鑒 jian
{1,0,{pysm::q,pyym::ian}},//鑓 qian
{1,0,{pysm::ch,pyym::a}},//鑔 cha
{1,0,{pysm::zh,pyym::i}},//鑕 zhi
{2,3406,{pysm::nop,pyym::nop}},//鑖 mie
{1,0,{pysm::l,pyym::i}},//鑗 li
{1,0,{pysm::l,pyym::ei}},//鑘 lei
{1,0,{pysm::j,pyym::i}},//鑙 ji
{1,0,{pysm::z,pyym::uan}},//鑚 zuan
{2,3407,{pysm::nop,pyym::nop}},//鑛 kuang
{1,0,{pysm::sh,pyym::ang}},//鑜 shang
{1,0,{pysm::p,pyym::eng}},//鑝 peng
{1,0,{pysm::l,pyym::a}},//鑞 la
{1,0,{pysm::d,pyym::u}},//鑟 du
{3,809,{pysm::nop,pyym::nop}},//鑠 shuo
{1,0,{pysm::ch,pyym::uo}},//鑡 chuo
{1,0,{pysm::l,pyym::v}},//鑢 lü
{1,0,{pysm::b,pyym::iao}},//鑣 biao
{1,0,{pysm::b,pyym::ao}},//鑤 bao
{1,0,{pysm::l,pyym::u}},//鑥 lu
{1,0,{pysm::x,pyym::ian}},//鑦 xian
{1,0,{pysm::k,pyym::uan}},//鑧 kuan
{1,0,{pysm::l,pyym::ong}},//鑨 long
{1,0,{pysm::nop,pyym::e}},//鑩 e
{1,0,{pysm::l,pyym::u}},//鑪 lu
{2,3408,{pysm::nop,pyym::nop}},//鑫 xin
{1,0,{pysm::j,pyym::ian}},//鑬 jian
{1,0,{pysm::l,pyym::an}},//鑭 lan
{1,0,{pysm::b,pyym::o}},//鑮 bo
{2,3409,{pysm::nop,pyym::nop}},//鑯 jian
{2,3410,{pysm::nop,pyym::nop}},//鑰 yao
{1,0,{pysm::ch,pyym::an}},//鑱 chan
{2,3411,{pysm::nop,pyym::nop}},//鑲 xiang
{1,0,{pysm::j,pyym::ian}},//鑳 jian
{2,3412,{pysm::nop,pyym::nop}},//鑴 xi
{1,0,{pysm::g,pyym::uan}},//鑵 guan
{1,0,{pysm::c,pyym::ang}},//鑶 cang
{1,0,{pysm::n,pyym::ie}},//鑷 nie
{1,0,{pysm::l,pyym::ei}},//鑸 lei
{1,0,{pysm::c,pyym::uan}},//鑹 cuan
{1,0,{pysm::q,pyym::u}},//鑺 qu
{1,0,{pysm::p,pyym::an}},//鑻 pan
{1,0,{pysm::l,pyym::uo}},//鑼 luo
{1,0,{pysm::z,pyym::uan}},//鑽 zuan
{1,0,{pysm::l,pyym::uan}},//鑾 luan
{3,810,{pysm::nop,pyym::nop}},//鑿 zao
{2,3413,{pysm::nop,pyym::nop}},//钀 nie
{1,0,{pysm::j,pyym::ue}},//钁 jue
{1,0,{pysm::t,pyym::ang}},//钂 tang
{1,0,{pysm::zh,pyym::u}},//钃 zhu
{1,0,{pysm::l,pyym::an}},//钄 lan
{1,0,{pysm::j,pyym::in}},//钅 jin
{1,0,{pysm::g,pyym::a}},//钆 ga
{1,0,{pysm::y,pyym::i}},//钇 yi
{1,0,{pysm::zh,pyym::en}},//针 zhen
{1,0,{pysm::d,pyym::ing}},//钉 ding
{1,0,{pysm::zh,pyym::ao}},//钊 zhao
{1,0,{pysm::p,pyym::o}},//钋 po
{1,0,{pysm::l,pyym::iao}},//钌 liao
{1,0,{pysm::t,pyym::u}},//钍 tu
{1,0,{pysm::q,pyym::ian}},//钎 qian
{1,0,{pysm::ch,pyym::uan}},//钏 chuan
{1,0,{pysm::sh,pyym::an}},//钐 shan
{1,0,{pysm::s,pyym::a}},//钑 sa
{1,0,{pysm::f,pyym::an}},//钒 fan
{1,0,{pysm::d,pyym::iao}},//钓 diao
{1,0,{pysm::m,pyym::en}},//钔 men
{1,0,{pysm::n,pyym::v}},//钕 nü
{1,0,{pysm::y,pyym::ang}},//钖 yang
{1,0,{pysm::ch,pyym::ai}},//钗 chai
{1,0,{pysm::x,pyym::ing}},//钘 xing
{1,0,{pysm::g,pyym::ai}},//钙 gai
{1,0,{pysm::b,pyym::u}},//钚 bu
{1,0,{pysm::t,pyym::ai}},//钛 tai
{1,0,{pysm::j,pyym::u}},//钜 ju
{1,0,{pysm::d,pyym::un}},//钝 dun
{1,0,{pysm::ch,pyym::ao}},//钞 chao
{1,0,{pysm::zh,pyym::ong}},//钟 zhong
{1,0,{pysm::n,pyym::a}},//钠 na
{1,0,{pysm::b,pyym::ei}},//钡 bei
{1,0,{pysm::g,pyym::ang}},//钢 gang
{1,0,{pysm::b,pyym::an}},//钣 ban
{1,0,{pysm::q,pyym::ian}},//钤 qian
{2,3414,{pysm::nop,pyym::nop}},//钥 yao
{1,0,{pysm::q,pyym::in}},//钦 qin
{1,0,{pysm::j,pyym::un}},//钧 jun
{1,0,{pysm::w,pyym::u}},//钨 wu
{1,0,{pysm::g,pyym::ou}},//钩 gou
{1,0,{pysm::k,pyym::ang}},//钪 kang
{1,0,{pysm::f,pyym::ang}},//钫 fang
{1,0,{pysm::h,pyym::uo}},//钬 huo
{2,3415,{pysm::nop,pyym::nop}},//钭 tou
{1,0,{pysm::n,pyym::iu}},//钮 niu
{2,3416,{pysm::nop,pyym::nop}},//钯 ba
{1,0,{pysm::y,pyym::u}},//钰 yu
{1,0,{pysm::q,pyym::ian}},//钱 qian
{1,0,{pysm::zh,pyym::eng}},//钲 zheng
{1,0,{pysm::q,pyym::ian}},//钳 qian
{1,0,{pysm::g,pyym::u}},//钴 gu
{1,0,{pysm::b,pyym::o}},//钵 bo
{1,0,{pysm::k,pyym::e}},//钶 ke
{1,0,{pysm::p,pyym::o}},//钷 po
{1,0,{pysm::b,pyym::u}},//钸 bu
{1,0,{pysm::b,pyym::o}},//钹 bo
{1,0,{pysm::y,pyym::ue}},//钺 yue
{1,0,{pysm::z,pyym::uan}},//钻 zuan
{1,0,{pysm::m,pyym::u}},//钼 mu
{1,0,{pysm::t,pyym::an}},//钽 tan
{1,0,{pysm::j,pyym::ia}},//钾 jia
{2,3417,{pysm::nop,pyym::nop}},//钿 dian
{1,0,{pysm::y,pyym::ou}},//铀 you
{1,0,{pysm::t,pyym::ie}},//铁 tie
{1,0,{pysm::b,pyym::o}},//铂 bo
{1,0,{pysm::l,pyym::ing}},//铃 ling
{1,0,{pysm::sh,pyym::uo}},//铄 shuo
{2,3418,{pysm::nop,pyym::nop}},//铅 qian
{1,0,{pysm::m,pyym::ao}},//铆 mao
{1,0,{pysm::b,pyym::ao}},//铇 bao
{1,0,{pysm::sh,pyym::i}},//铈 shi
{1,0,{pysm::x,pyym::uan}},//铉 xuan
{2,3419,{pysm::nop,pyym::nop}},//铊 ta
{1,0,{pysm::b,pyym::i}},//铋 bi
{1,0,{pysm::n,pyym::i}},//铌 ni
{1,0,{pysm::p,pyym::i}},//铍 pi
{1,0,{pysm::d,pyym::uo}},//铎 duo
{1,0,{pysm::x,pyym::ing}},//铏 xing
{1,0,{pysm::k,pyym::ao}},//铐 kao
{1,0,{pysm::l,pyym::ao}},//铑 lao
{1,0,{pysm::nop,pyym::er}},//铒 er
{1,0,{pysm::m,pyym::ang}},//铓 mang
{1,0,{pysm::y,pyym::a}},//铔 ya
{1,0,{pysm::y,pyym::ou}},//铕 you
{1,0,{pysm::ch,pyym::eng}},//铖 cheng
{1,0,{pysm::j,pyym::ia}},//铗 jia
{1,0,{pysm::y,pyym::e}},//铘 ye
{1,0,{pysm::n,pyym::ao}},//铙 nao
{1,0,{pysm::zh,pyym::i}},//铚 zhi
{2,3420,{pysm::nop,pyym::nop}},//铛 dang
{1,0,{pysm::t,pyym::ong}},//铜 tong
{1,0,{pysm::l,pyym::v}},//铝 lü
{1,0,{pysm::d,pyym::iao}},//铞 diao
{1,0,{pysm::y,pyym::in}},//铟 yin
{1,0,{pysm::k,pyym::ai}},//铠 kai
{1,0,{pysm::zh,pyym::a}},//铡 zha
{1,0,{pysm::zh,pyym::u}},//铢 zhu
{2,3421,{pysm::nop,pyym::nop}},//铣 xi
{2,3422,{pysm::nop,pyym::nop}},//铤 ding
{1,0,{pysm::d,pyym::iu}},//铥 diu
{1,0,{pysm::x,pyym::ian}},//铦 xian
{1,0,{pysm::h,pyym::ua}},//铧 hua
{1,0,{pysm::q,pyym::uan}},//铨 quan
{1,0,{pysm::sh,pyym::a}},//铩 sha
{1,0,{pysm::h,pyym::a}},//铪 ha
{2,3423,{pysm::nop,pyym::nop}},//铫 diao
{1,0,{pysm::g,pyym::e}},//铬 ge
{1,0,{pysm::m,pyym::ing}},//铭 ming
{1,0,{pysm::zh,pyym::eng}},//铮 zheng
{1,0,{pysm::s,pyym::e}},//铯 se
{1,0,{pysm::j,pyym::iao}},//铰 jiao
{1,0,{pysm::y,pyym::i}},//铱 yi
{1,0,{pysm::ch,pyym::an}},//铲 chan
{1,0,{pysm::ch,pyym::ong}},//铳 chong
{1,0,{pysm::t,pyym::ang}},//铴 tang
{1,0,{pysm::nop,pyym::an}},//铵 an
{1,0,{pysm::y,pyym::in}},//银 yin
{1,0,{pysm::r,pyym::u}},//铷 ru
{1,0,{pysm::zh,pyym::u}},//铸 zhu
{1,0,{pysm::l,pyym::ao}},//铹 lao
{1,0,{pysm::p,pyym::u}},//铺 pu
{2,3424,{pysm::nop,pyym::nop}},//铻 wu
{1,0,{pysm::l,pyym::ai}},//铼 lai
{1,0,{pysm::t,pyym::e}},//铽 te
{1,0,{pysm::l,pyym::ian}},//链 lian
{1,0,{pysm::k,pyym::eng}},//铿 keng
{1,0,{pysm::x,pyym::iao}},//销 xiao
{1,0,{pysm::s,pyym::uo}},//锁 suo
{1,0,{pysm::l,pyym::i}},//锂 li
{1,0,{pysm::z,pyym::eng}},//锃 zeng
{1,0,{pysm::ch,pyym::u}},//锄 chu
{1,0,{pysm::g,pyym::uo}},//锅 guo
{1,0,{pysm::g,pyym::ao}},//锆 gao
{1,0,{pysm::nop,pyym::e}},//锇 e
{1,0,{pysm::x,pyym::iu}},//锈 xiu
{1,0,{pysm::c,pyym::uo}},//锉 cuo
{1,0,{pysm::l,pyym::ve}},//锊 lüe
{1,0,{pysm::f,pyym::eng}},//锋 feng
{1,0,{pysm::x,pyym::in}},//锌 xin
{1,0,{pysm::l,pyym::iu}},//锍 liu
{1,0,{pysm::k,pyym::ai}},//锎 kai
{1,0,{pysm::j,pyym::ian}},//锏 jian
{1,0,{pysm::r,pyym::ui}},//锐 rui
{1,0,{pysm::t,pyym::i}},//锑 ti
{1,0,{pysm::l,pyym::ang}},//锒 lang
{1,0,{pysm::q,pyym::in}},//锓 qin
{1,0,{pysm::j,pyym::u}},//锔 ju
{1,0,{pysm::nop,pyym::a}},//锕 a
{1,0,{pysm::q,pyym::iang}},//锖 qiang
{1,0,{pysm::zh,pyym::e}},//锗 zhe
{1,0,{pysm::n,pyym::uo}},//锘 nuo
{1,0,{pysm::c,pyym::uo}},//错 cuo
{1,0,{pysm::m,pyym::ao}},//锚 mao
{1,0,{pysm::b,pyym::en}},//锛 ben
{1,0,{pysm::q,pyym::i}},//锜 qi
{1,0,{pysm::d,pyym::e}},//锝 de
{1,0,{pysm::k,pyym::e}},//锞 ke
{1,0,{pysm::k,pyym::un}},//锟 kun
{1,0,{pysm::ch,pyym::ang}},//锠 chang
{1,0,{pysm::x,pyym::i}},//锡 xi
{1,0,{pysm::g,pyym::u}},//锢 gu
{1,0,{pysm::l,pyym::uo}},//锣 luo
{1,0,{pysm::ch,pyym::ui}},//锤 chui
{1,0,{pysm::zh,pyym::ui}},//锥 zhui
{1,0,{pysm::j,pyym::in}},//锦 jin
{1,0,{pysm::zh,pyym::i}},//锧 zhi
{1,0,{pysm::x,pyym::ian}},//锨 xian
{1,0,{pysm::j,pyym::uan}},//锩 juan
{1,0,{pysm::h,pyym::uo}},//锪 huo
{1,0,{pysm::p,pyym::ei}},//锫 pei
{2,3425,{pysm::nop,pyym::nop}},//锬 tan
{1,0,{pysm::d,pyym::ing}},//锭 ding
{1,0,{pysm::j,pyym::ian}},//键 jian
{1,0,{pysm::j,pyym::u}},//锯 ju
{1,0,{pysm::m,pyym::eng}},//锰 meng
{1,0,{pysm::z,pyym::i}},//锱 zi
{1,0,{pysm::q,pyym::ie}},//锲 qie
{1,0,{pysm::y,pyym::ing}},//锳 ying
{1,0,{pysm::k,pyym::ai}},//锴 kai
{1,0,{pysm::q,pyym::iang}},//锵 qiang
{1,0,{pysm::s,pyym::i}},//锶 si
{1,0,{pysm::nop,pyym::e}},//锷 e
{1,0,{pysm::ch,pyym::a}},//锸 cha
{1,0,{pysm::q,pyym::iao}},//锹 qiao
{1,0,{pysm::zh,pyym::ong}},//锺 zhong
{1,0,{pysm::d,pyym::uan}},//锻 duan
{1,0,{pysm::s,pyym::ou}},//锼 sou
{1,0,{pysm::h,pyym::uang}},//锽 huang
{1,0,{pysm::h,pyym::uan}},//锾 huan
{1,0,{pysm::nop,pyym::ai}},//锿 ai
{1,0,{pysm::d,pyym::u}},//镀 du
{1,0,{pysm::m,pyym::ei}},//镁 mei
{1,0,{pysm::l,pyym::ou}},//镂 lou
{1,0,{pysm::z,pyym::i}},//镃 zi
{1,0,{pysm::f,pyym::ei}},//镄 fei
{1,0,{pysm::m,pyym::ei}},//镅 mei
{1,0,{pysm::m,pyym::o}},//镆 mo
{1,0,{pysm::zh,pyym::en}},//镇 zhen
{1,0,{pysm::b,pyym::o}},//镈 bo
{1,0,{pysm::g,pyym::e}},//镉 ge
{1,0,{pysm::n,pyym::ie}},//镊 nie
{1,0,{pysm::t,pyym::ang}},//镋 tang
{1,0,{pysm::j,pyym::uan}},//镌 juan
{1,0,{pysm::n,pyym::ie}},//镍 nie
{1,0,{pysm::n,pyym::a}},//镎 na
{1,0,{pysm::l,pyym::iu}},//镏 liu
{2,3426,{pysm::nop,pyym::nop}},//镐 gao
{1,0,{pysm::b,pyym::ang}},//镑 bang
{1,0,{pysm::y,pyym::i}},//镒 yi
{1,0,{pysm::j,pyym::ia}},//镓 jia
{1,0,{pysm::b,pyym::in}},//镔 bin
{1,0,{pysm::r,pyym::ong}},//镕 rong
{1,0,{pysm::b,pyym::iao}},//镖 biao
{1,0,{pysm::t,pyym::ang}},//镗 tang
{1,0,{pysm::m,pyym::an}},//镘 man
{1,0,{pysm::l,pyym::uo}},//镙 luo
{1,0,{pysm::b,pyym::eng}},//镚 beng
{1,0,{pysm::y,pyym::ong}},//镛 yong
{1,0,{pysm::j,pyym::ing}},//镜 jing
{1,0,{pysm::d,pyym::i}},//镝 di
{1,0,{pysm::z,pyym::u}},//镞 zu
{1,0,{pysm::x,pyym::uan}},//镟 xuan
{1,0,{pysm::l,pyym::iu}},//镠 liu
{3,811,{pysm::nop,pyym::nop}},//镡 chan
{1,0,{pysm::j,pyym::ue}},//镢 jue
{1,0,{pysm::l,pyym::iao}},//镣 liao
{1,0,{pysm::p,pyym::u}},//镤 pu
{1,0,{pysm::l,pyym::u}},//镥 lu
{2,3427,{pysm::nop,pyym::nop}},//镦 dui
{1,0,{pysm::l,pyym::an}},//镧 lan
{1,0,{pysm::p,pyym::u}},//镨 pu
{1,0,{pysm::c,pyym::uan}},//镩 cuan
{1,0,{pysm::q,pyym::iang}},//镪 qiang
{1,0,{pysm::d,pyym::eng}},//镫 deng
{1,0,{pysm::h,pyym::uo}},//镬 huo
{1,0,{pysm::l,pyym::ei}},//镭 lei
{1,0,{pysm::h,pyym::uan}},//镮 huan
{1,0,{pysm::zh,pyym::uo}},//镯 zhuo
{1,0,{pysm::l,pyym::ian}},//镰 lian
{1,0,{pysm::y,pyym::i}},//镱 yi
{1,0,{pysm::ch,pyym::a}},//镲 cha
{1,0,{pysm::b,pyym::iao}},//镳 biao
{1,0,{pysm::l,pyym::a}},//镴 la
{1,0,{pysm::ch,pyym::an}},//镵 chan
{1,0,{pysm::x,pyym::iang}},//镶 xiang
{2,3428,{pysm::nop,pyym::nop}},//長 zhang
{1,0,{pysm::ch,pyym::ang}},//镸 chang
{1,0,{pysm::j,pyym::iu}},//镹 jiu
{1,0,{pysm::nop,pyym::ao}},//镺 ao
{1,0,{pysm::d,pyym::ie}},//镻 die
{1,0,{pysm::q,pyym::u}},//镼 qu
{1,0,{pysm::l,pyym::iao}},//镽 liao
{1,0,{pysm::m,pyym::i}},//镾 mi
{2,3429,{pysm::nop,pyym::nop}},//长 zhang
{1,0,{pysm::m,pyym::en}},//門 men
{1,0,{pysm::m,pyym::a}},//閁 ma
{1,0,{pysm::sh,pyym::uan}},//閂 shuan
{1,0,{pysm::sh,pyym::an}},//閃 shan
{2,3430,{pysm::nop,pyym::nop}},//閄 huo
{1,0,{pysm::m,pyym::en}},//閅 men
{1,0,{pysm::y,pyym::an}},//閆 yan
{1,0,{pysm::b,pyym::i}},//閇 bi
{2,3431,{pysm::nop,pyym::nop}},//閈 han
{1,0,{pysm::b,pyym::i}},//閉 bi
{1,0,{pysm::sh,pyym::an}},//閊 shan
{2,3432,{pysm::nop,pyym::nop}},//開 kai
{1,0,{pysm::k,pyym::ang}},//閌 kang
{1,0,{pysm::b,pyym::eng}},//閍 beng
{1,0,{pysm::h,pyym::ong}},//閎 hong
{1,0,{pysm::r,pyym::un}},//閏 run
{1,0,{pysm::s,pyym::an}},//閐 san
{1,0,{pysm::x,pyym::ian}},//閑 xian
{2,3433,{pysm::nop,pyym::nop}},//閒 xian
{1,0,{pysm::j,pyym::ian}},//間 jian
{1,0,{pysm::m,pyym::in}},//閔 min
{1,0,{pysm::x,pyym::ia}},//閕 xia
{1,0,{pysm::sh,pyym::ui}},//閖 shui
{1,0,{pysm::d,pyym::ou}},//閗 dou
{3,812,{pysm::nop,pyym::nop}},//閘 zha
{1,0,{pysm::n,pyym::ao}},//閙 nao
{1,0,{pysm::zh,pyym::an}},//閚 zhan
{1,0,{pysm::p,pyym::eng}},//閛 peng
{2,3434,{pysm::nop,pyym::nop}},//閜 xia
{1,0,{pysm::l,pyym::ing}},//閝 ling
{2,3435,{pysm::nop,pyym::nop}},//閞 bian
{1,0,{pysm::b,pyym::i}},//閟 bi
{1,0,{pysm::r,pyym::un}},//閠 run
{5,51,{pysm::nop,pyym::nop}},//閡 ai
{1,0,{pysm::g,pyym::uan}},//関 guan
{1,0,{pysm::g,pyym::e}},//閣 ge
{2,3436,{pysm::nop,pyym::nop}},//閤 ge
{1,0,{pysm::f,pyym::a}},//閥 fa
{1,0,{pysm::ch,pyym::u}},//閦 chu
{2,3437,{pysm::nop,pyym::nop}},//閧 hong
{1,0,{pysm::g,pyym::ui}},//閨 gui
{1,0,{pysm::m,pyym::in}},//閩 min
{1,0,{pysm::s,pyym::e}},//閪 se
{1,0,{pysm::k,pyym::un}},//閫 kun
{2,3438,{pysm::nop,pyym::nop}},//閬 lang
{1,0,{pysm::l,pyym::v}},//閭 lü
{1,0,{pysm::t,pyym::ing}},//閮 ting
{1,0,{pysm::sh,pyym::a}},//閯 sha
{1,0,{pysm::j,pyym::u}},//閰 ju
{1,0,{pysm::y,pyym::ue}},//閱 yue
{1,0,{pysm::y,pyym::ue}},//閲 yue
{1,0,{pysm::ch,pyym::an}},//閳 chan
{1,0,{pysm::q,pyym::u}},//閴 qu
{1,0,{pysm::l,pyym::in}},//閵 lin
{2,3439,{pysm::nop,pyym::nop}},//閶 chang
{2,3440,{pysm::nop,pyym::nop}},//閷 shai
{1,0,{pysm::k,pyym::un}},//閸 kun
{1,0,{pysm::y,pyym::an}},//閹 yan
{1,0,{pysm::w,pyym::en}},//閺 wen
{1,0,{pysm::y,pyym::an}},//閻 yan
{3,813,{pysm::nop,pyym::nop}},//閼 e
{1,0,{pysm::h,pyym::un}},//閽 hun
{1,0,{pysm::y,pyym::u}},//閾 yu
{1,0,{pysm::w,pyym::en}},//閿 wen
{1,0,{pysm::h,pyym::ong}},//闀 hong
{1,0,{pysm::b,pyym::ao}},//闁 bao
{3,814,{pysm::nop,pyym::nop}},//闂 hong
{1,0,{pysm::q,pyym::u}},//闃 qu
{1,0,{pysm::y,pyym::ao}},//闄 yao
{1,0,{pysm::w,pyym::en}},//闅 wen
{2,3441,{pysm::nop,pyym::nop}},//闆 ban
{2,3442,{pysm::nop,pyym::nop}},//闇 an
{1,0,{pysm::w,pyym::ei}},//闈 wei
{1,0,{pysm::y,pyym::in}},//闉 yin
{1,0,{pysm::k,pyym::uo}},//闊 kuo
{3,815,{pysm::nop,pyym::nop}},//闋 que
{1,0,{pysm::l,pyym::an}},//闌 lan
{2,3443,{pysm::nop,pyym::nop}},//闍 du
{1,0,{pysm::q,pyym::uan}},//闎 quan
{1,0,{pysm::f,pyym::eng}},//闏 feng
{1,0,{pysm::t,pyym::ian}},//闐 tian
{1,0,{pysm::n,pyym::ie}},//闑 nie
{1,0,{pysm::t,pyym::a}},//闒 ta
{1,0,{pysm::k,pyym::ai}},//闓 kai
{1,0,{pysm::h,pyym::e}},//闔 he
{2,3444,{pysm::nop,pyym::nop}},//闕 que
{2,3445,{pysm::nop,pyym::nop}},//闖 chuang
{1,0,{pysm::g,pyym::uan}},//闗 guan
{1,0,{pysm::d,pyym::ou}},//闘 dou
{1,0,{pysm::q,pyym::i}},//闙 qi
{1,0,{pysm::k,pyym::ui}},//闚 kui
{2,3446,{pysm::nop,pyym::nop}},//闛 tang
{2,3447,{pysm::nop,pyym::nop}},//關 guan
{1,0,{pysm::p,pyym::iao}},//闝 piao
{3,816,{pysm::nop,pyym::nop}},//闞 kan
{3,817,{pysm::nop,pyym::nop}},//闟 xi
{1,0,{pysm::h,pyym::ui}},//闠 hui
{1,0,{pysm::ch,pyym::an}},//闡 chan
{1,0,{pysm::p,pyym::i}},//闢 pi
{2,3448,{pysm::nop,pyym::nop}},//闣 dang
{1,0,{pysm::h,pyym::uan}},//闤 huan
{1,0,{pysm::t,pyym::a}},//闥 ta
{1,0,{pysm::w,pyym::en}},//闦 wen
{1,0,{pysm::t,pyym::a}},//闧 ta
{1,0,{pysm::m,pyym::en}},//门 men
{1,0,{pysm::sh,pyym::uan}},//闩 shuan
{1,0,{pysm::sh,pyym::an}},//闪 shan
{1,0,{pysm::y,pyym::an}},//闫 yan
{1,0,{pysm::h,pyym::an}},//闬 han
{1,0,{pysm::b,pyym::i}},//闭 bi
{1,0,{pysm::w,pyym::en}},//问 wen
{1,0,{pysm::ch,pyym::uang}},//闯 chuang
{1,0,{pysm::r,pyym::un}},//闰 run
{1,0,{pysm::w,pyym::ei}},//闱 wei
{1,0,{pysm::x,pyym::ian}},//闲 xian
{1,0,{pysm::h,pyym::ong}},//闳 hong
{1,0,{pysm::j,pyym::ian}},//间 jian
{1,0,{pysm::m,pyym::in}},//闵 min
{1,0,{pysm::k,pyym::ang}},//闶 kang
{1,0,{pysm::m,pyym::en}},//闷 men
{1,0,{pysm::zh,pyym::a}},//闸 zha
{1,0,{pysm::n,pyym::ao}},//闹 nao
{1,0,{pysm::g,pyym::ui}},//闺 gui
{1,0,{pysm::w,pyym::en}},//闻 wen
{1,0,{pysm::t,pyym::a}},//闼 ta
{1,0,{pysm::m,pyym::in}},//闽 min
{1,0,{pysm::l,pyym::v}},//闾 lü
{1,0,{pysm::k,pyym::ai}},//闿 kai
{1,0,{pysm::f,pyym::a}},//阀 fa
{1,0,{pysm::g,pyym::e}},//阁 ge
{1,0,{pysm::h,pyym::e}},//阂 he
{1,0,{pysm::k,pyym::un}},//阃 kun
{1,0,{pysm::j,pyym::iu}},//阄 jiu
{1,0,{pysm::y,pyym::ue}},//阅 yue
{1,0,{pysm::l,pyym::ang}},//阆 lang
{2,3449,{pysm::nop,pyym::nop}},//阇 du
{1,0,{pysm::y,pyym::u}},//阈 yu
{1,0,{pysm::y,pyym::an}},//阉 yan
{1,0,{pysm::ch,pyym::ang}},//阊 chang
{1,0,{pysm::x,pyym::i}},//阋 xi
{1,0,{pysm::w,pyym::en}},//阌 wen
{1,0,{pysm::h,pyym::un}},//阍 hun
{1,0,{pysm::y,pyym::an}},//阎 yan
{2,3450,{pysm::nop,pyym::nop}},//阏 e
{1,0,{pysm::ch,pyym::an}},//阐 chan
{1,0,{pysm::l,pyym::an}},//阑 lan
{1,0,{pysm::q,pyym::u}},//阒 qu
{1,0,{pysm::h,pyym::ui}},//阓 hui
{1,0,{pysm::k,pyym::uo}},//阔 kuo
{1,0,{pysm::q,pyym::ue}},//阕 que
{1,0,{pysm::h,pyym::e}},//阖 he
{1,0,{pysm::t,pyym::ian}},//阗 tian
{2,3451,{pysm::nop,pyym::nop}},//阘 da
{1,0,{pysm::q,pyym::ue}},//阙 que
{2,3452,{pysm::nop,pyym::nop}},//阚 han
{1,0,{pysm::h,pyym::uan}},//阛 huan
{1,0,{pysm::f,pyym::u}},//阜 fu
{1,0,{pysm::f,pyym::u}},//阝 fu
{1,0,{pysm::l,pyym::e}},//阞 le
{1,0,{pysm::d,pyym::ui}},//队 dui
{1,0,{pysm::x,pyym::in}},//阠 xin
{1,0,{pysm::q,pyym::ian}},//阡 qian
{2,3453,{pysm::nop,pyym::nop}},//阢 wu
{2,3454,{pysm::nop,pyym::nop}},//阣 gai
{3,818,{pysm::nop,pyym::nop}},//阤 zhi
{1,0,{pysm::y,pyym::in}},//阥 yin
{1,0,{pysm::y,pyym::ang}},//阦 yang
{1,0,{pysm::d,pyym::ou}},//阧 dou
{2,3455,{pysm::nop,pyym::nop}},//阨 e
{1,0,{pysm::sh,pyym::eng}},//阩 sheng
{1,0,{pysm::b,pyym::an}},//阪 ban
{1,0,{pysm::p,pyym::ei}},//阫 pei
{3,819,{pysm::nop,pyym::nop}},//阬 keng
{2,3456,{pysm::nop,pyym::nop}},//阭 yun
{2,3457,{pysm::nop,pyym::nop}},//阮 ruan
{1,0,{pysm::zh,pyym::i}},//阯 zhi
{1,0,{pysm::p,pyym::i}},//阰 pi
{1,0,{pysm::j,pyym::ing}},//阱 jing
{1,0,{pysm::f,pyym::ang}},//防 fang
{1,0,{pysm::y,pyym::ang}},//阳 yang
{1,0,{pysm::y,pyym::in}},//阴 yin
{1,0,{pysm::zh,pyym::en}},//阵 zhen
{1,0,{pysm::j,pyym::ie}},//阶 jie
{1,0,{pysm::ch,pyym::eng}},//阷 cheng
{2,3458,{pysm::nop,pyym::nop}},//阸 e
{1,0,{pysm::q,pyym::u}},//阹 qu
{1,0,{pysm::d,pyym::i}},//阺 di
{2,3459,{pysm::nop,pyym::nop}},//阻 zu
{1,0,{pysm::z,pyym::uo}},//阼 zuo
{2,3460,{pysm::nop,pyym::nop}},//阽 dian
{1,0,{pysm::l,pyym::ing}},//阾 ling
{2,3461,{pysm::nop,pyym::nop}},//阿 a
{2,3462,{pysm::nop,pyym::nop}},//陀 tuo
{3,820,{pysm::nop,pyym::nop}},//陁 tuo
{4,163,{pysm::nop,pyym::nop}},//陂 bei
{1,0,{pysm::b,pyym::ing}},//陃 bing
{2,3463,{pysm::nop,pyym::nop}},//附 fu
{1,0,{pysm::j,pyym::i}},//际 ji
{2,3464,{pysm::nop,pyym::nop}},//陆 lu
{1,0,{pysm::l,pyym::ong}},//陇 long
{1,0,{pysm::ch,pyym::en}},//陈 chen
{1,0,{pysm::x,pyym::ing}},//陉 xing
{1,0,{pysm::d,pyym::uo}},//陊 duo
{1,0,{pysm::l,pyym::ou}},//陋 lou
{1,0,{pysm::m,pyym::o}},//陌 mo
{2,3465,{pysm::nop,pyym::nop}},//降 jiang
{1,0,{pysm::sh,pyym::u}},//陎 shu
{2,3466,{pysm::nop,pyym::nop}},//陏 duo
{2,3467,{pysm::nop,pyym::nop}},//限 xian
{1,0,{pysm::nop,pyym::er}},//陑 er
{1,0,{pysm::g,pyym::ui}},//陒 gui
{1,0,{pysm::y,pyym::u}},//陓 yu
{1,0,{pysm::g,pyym::ai}},//陔 gai
{1,0,{pysm::sh,pyym::an}},//陕 shan
{1,0,{pysm::j,pyym::un}},//陖 jun
{1,0,{pysm::q,pyym::iao}},//陗 qiao
{2,3468,{pysm::nop,pyym::nop}},//陘 xing
{1,0,{pysm::ch,pyym::un}},//陙 chun
{2,3469,{pysm::nop,pyym::nop}},//陚 fu
{1,0,{pysm::b,pyym::i}},//陛 bi
{1,0,{pysm::x,pyym::ia}},//陜 xia
{1,0,{pysm::sh,pyym::an}},//陝 shan
{1,0,{pysm::sh,pyym::eng}},//陞 sheng
{2,3470,{pysm::nop,pyym::nop}},//陟 zhi
{2,3471,{pysm::nop,pyym::nop}},//陠 pu
{1,0,{pysm::d,pyym::ou}},//陡 dou
{1,0,{pysm::y,pyym::uan}},//院 yuan
{1,0,{pysm::zh,pyym::en}},//陣 zhen
{3,821,{pysm::nop,pyym::nop}},//除 chu
{1,0,{pysm::x,pyym::ian}},//陥 xian
{1,0,{pysm::d,pyym::ao}},//陦 dao
{1,0,{pysm::n,pyym::ie}},//陧 nie
{1,0,{pysm::y,pyym::un}},//陨 yun
{1,0,{pysm::x,pyym::ian}},//险 xian
{1,0,{pysm::p,pyym::ei}},//陪 pei
{2,3472,{pysm::nop,pyym::nop}},//陫 fei
{2,3473,{pysm::nop,pyym::nop}},//陬 zou
{1,0,{pysm::y,pyym::i}},//陭 yi
{1,0,{pysm::d,pyym::ui}},//陮 dui
{1,0,{pysm::l,pyym::un}},//陯 lun
{2,3474,{pysm::nop,pyym::nop}},//陰 yin
{1,0,{pysm::j,pyym::u}},//陱 ju
{1,0,{pysm::ch,pyym::ui}},//陲 chui
{2,3475,{pysm::nop,pyym::nop}},//陳 chen
{2,3476,{pysm::nop,pyym::nop}},//陴 pi
{1,0,{pysm::l,pyym::ing}},//陵 ling
{3,822,{pysm::nop,pyym::nop}},//陶 tao
{1,0,{pysm::x,pyym::ian}},//陷 xian
{2,3477,{pysm::nop,pyym::nop}},//陸 lu
{1,0,{pysm::sh,pyym::eng}},//陹 sheng
{1,0,{pysm::x,pyym::ian}},//険 xian
{1,0,{pysm::y,pyym::in}},//陻 yin
{2,3478,{pysm::nop,pyym::nop}},//陼 zhu
{1,0,{pysm::y,pyym::ang}},//陽 yang
{2,3479,{pysm::nop,pyym::nop}},//陾 reng
{1,0,{pysm::x,pyym::ia}},//陿 xia
{1,0,{pysm::ch,pyym::ong}},//隀 chong
{1,0,{pysm::y,pyym::an}},//隁 yan
{1,0,{pysm::y,pyym::in}},//隂 yin
{3,823,{pysm::nop,pyym::nop}},//隃 shu
{2,3480,{pysm::nop,pyym::nop}},//隄 di
{1,0,{pysm::y,pyym::u}},//隅 yu
{1,0,{pysm::l,pyym::ong}},//隆 long
{1,0,{pysm::w,pyym::ei}},//隇 wei
{1,0,{pysm::w,pyym::ei}},//隈 wei
{1,0,{pysm::n,pyym::ie}},//隉 nie
{3,824,{pysm::nop,pyym::nop}},//隊 dui
{3,825,{pysm::nop,pyym::nop}},//隋 sui
{1,0,{pysm::nop,pyym::an}},//隌 an
{1,0,{pysm::h,pyym::uang}},//隍 huang
{1,0,{pysm::j,pyym::ie}},//階 jie
{1,0,{pysm::s,pyym::ui}},//随 sui
{1,0,{pysm::y,pyym::in}},//隐 yin
{3,826,{pysm::nop,pyym::nop}},//隑 gai
{1,0,{pysm::y,pyym::an}},//隒 yan
{2,3481,{pysm::nop,pyym::nop}},//隓 hui
{3,827,{pysm::nop,pyym::nop}},//隔 ge
{2,3482,{pysm::nop,pyym::nop}},//隕 yun
{1,0,{pysm::w,pyym::u}},//隖 wu
{3,828,{pysm::nop,pyym::nop}},//隗 kui
{2,3483,{pysm::nop,pyym::nop}},//隘 ai
{1,0,{pysm::x,pyym::i}},//隙 xi
{1,0,{pysm::t,pyym::ang}},//隚 tang
{1,0,{pysm::j,pyym::i}},//際 ji
{1,0,{pysm::zh,pyym::ang}},//障 zhang
{1,0,{pysm::d,pyym::ao}},//隝 dao
{1,0,{pysm::nop,pyym::ao}},//隞 ao
{1,0,{pysm::x,pyym::i}},//隟 xi
{1,0,{pysm::y,pyym::in}},//隠 yin
{1,0,{pysm::s,pyym::a}},//隡 sa
{1,0,{pysm::r,pyym::ao}},//隢 rao
{1,0,{pysm::l,pyym::in}},//隣 lin
{1,0,{pysm::t,pyym::ui}},//隤 tui
{1,0,{pysm::d,pyym::eng}},//隥 deng
{2,3484,{pysm::nop,pyym::nop}},//隦 jiao
{2,3485,{pysm::nop,pyym::nop}},//隧 sui
{1,0,{pysm::s,pyym::ui}},//隨 sui
{2,3486,{pysm::nop,pyym::nop}},//隩 ao
{3,829,{pysm::nop,pyym::nop}},//險 xian
{1,0,{pysm::f,pyym::en}},//隫 fen
{1,0,{pysm::n,pyym::i}},//隬 ni
{1,0,{pysm::nop,pyym::er}},//隭 er
{1,0,{pysm::j,pyym::i}},//隮 ji
{1,0,{pysm::d,pyym::ao}},//隯 dao
{2,3487,{pysm::nop,pyym::nop}},//隰 xi
{1,0,{pysm::y,pyym::in}},//隱 yin
{1,0,{pysm::zh,pyym::i}},//隲 zhi
{1,0,{pysm::h,pyym::ui}},//隳 hui
{1,0,{pysm::l,pyym::ong}},//隴 long
{1,0,{pysm::x,pyym::i}},//隵 xi
{4,164,{pysm::nop,pyym::nop}},//隶 li
{1,0,{pysm::l,pyym::i}},//隷 li
{1,0,{pysm::l,pyym::i}},//隸 li
{3,830,{pysm::nop,pyym::nop}},//隹 zhui
{3,831,{pysm::nop,pyym::nop}},//隺 hu
{2,3488,{pysm::nop,pyym::nop}},//隻 zhi
{1,0,{pysm::s,pyym::un}},//隼 sun
{2,3489,{pysm::nop,pyym::nop}},//隽 juan
{1,0,{pysm::n,pyym::an}},//难 nan
{1,0,{pysm::y,pyym::i}},//隿 yi
{2,3490,{pysm::nop,pyym::nop}},//雀 que
{1,0,{pysm::y,pyym::an}},//雁 yan
{1,0,{pysm::q,pyym::in}},//雂 qin
{2,3491,{pysm::nop,pyym::nop}},//雃 qian
{1,0,{pysm::x,pyym::iong}},//雄 xiong
{1,0,{pysm::y,pyym::a}},//雅 ya
{1,0,{pysm::j,pyym::i}},//集 ji
{2,3492,{pysm::nop,pyym::nop}},//雇 gu
{1,0,{pysm::h,pyym::uan}},//雈 huan
{4,165,{pysm::nop,pyym::nop}},//雉 zhi
{1,0,{pysm::g,pyym::ou}},//雊 gou
{3,832,{pysm::nop,pyym::nop}},//雋 juan
{1,0,{pysm::c,pyym::i}},//雌 ci
{1,0,{pysm::y,pyym::ong}},//雍 yong
{1,0,{pysm::j,pyym::u}},//雎 ju
{1,0,{pysm::ch,pyym::u}},//雏 chu
{1,0,{pysm::h,pyym::u}},//雐 hu
{1,0,{pysm::z,pyym::a}},//雑 za
{1,0,{pysm::l,pyym::uo}},//雒 luo
{1,0,{pysm::y,pyym::u}},//雓 yu
{1,0,{pysm::ch,pyym::ou}},//雔 chou
{1,0,{pysm::d,pyym::iao}},//雕 diao
{1,0,{pysm::s,pyym::ui}},//雖 sui
{1,0,{pysm::h,pyym::an}},//雗 han
{1,0,{pysm::w,pyym::o}},//雘 wo
{1,0,{pysm::sh,pyym::uang}},//雙 shuang
{2,3493,{pysm::nop,pyym::nop}},//雚 guan
{2,3494,{pysm::nop,pyym::nop}},//雛 chu
{1,0,{pysm::z,pyym::a}},//雜 za
{1,0,{pysm::y,pyym::ong}},//雝 yong
{1,0,{pysm::j,pyym::i}},//雞 ji
{1,0,{pysm::x,pyym::i}},//雟 xi
{1,0,{pysm::ch,pyym::ou}},//雠 chou
{1,0,{pysm::l,pyym::iu}},//雡 liu
{3,833,{pysm::nop,pyym::nop}},//離 li
{2,3495,{pysm::nop,pyym::nop}},//難 nan
{1,0,{pysm::x,pyym::ue}},//雤 xue
{1,0,{pysm::z,pyym::a}},//雥 za
{1,0,{pysm::j,pyym::i}},//雦 ji
{1,0,{pysm::j,pyym::i}},//雧 ji
{1,0,{pysm::y,pyym::u}},//雨 yu
{2,3496,{pysm::nop,pyym::nop}},//雩 yu
{1,0,{pysm::x,pyym::ue}},//雪 xue
{1,0,{pysm::n,pyym::a}},//雫 na
{1,0,{pysm::f,pyym::ou}},//雬 fou
{2,3497,{pysm::nop,pyym::nop}},//雭 se
{1,0,{pysm::m,pyym::u}},//雮 mu
{1,0,{pysm::w,pyym::en}},//雯 wen
{1,0,{pysm::f,pyym::en}},//雰 fen
{2,3498,{pysm::nop,pyym::nop}},//雱 pang
{1,0,{pysm::y,pyym::un}},//雲 yun
{1,0,{pysm::l,pyym::i}},//雳 li
{1,0,{pysm::ch,pyym::i}},//雴 chi
{1,0,{pysm::y,pyym::ang}},//雵 yang
{2,3499,{pysm::nop,pyym::nop}},//零 ling
{1,0,{pysm::l,pyym::ei}},//雷 lei
{1,0,{pysm::nop,pyym::an}},//雸 an
{1,0,{pysm::b,pyym::ao}},//雹 bao
{2,3500,{pysm::nop,pyym::nop}},//雺 wu
{1,0,{pysm::d,pyym::ian}},//電 dian
{1,0,{pysm::d,pyym::ang}},//雼 dang
{1,0,{pysm::h,pyym::u}},//雽 hu
{1,0,{pysm::w,pyym::u}},//雾 wu
{1,0,{pysm::d,pyym::iao}},//雿 diao
{4,166,{pysm::nop,pyym::nop}},//需 xu
{1,0,{pysm::j,pyym::i}},//霁 ji
{1,0,{pysm::m,pyym::u}},//霂 mu
{1,0,{pysm::ch,pyym::en}},//霃 chen
{1,0,{pysm::x,pyym::iao}},//霄 xiao
{4,167,{pysm::nop,pyym::nop}},//霅 zha
{1,0,{pysm::t,pyym::ing}},//霆 ting
{2,3501,{pysm::nop,pyym::nop}},//震 zhen
{1,0,{pysm::p,pyym::ei}},//霈 pei
{1,0,{pysm::m,pyym::ei}},//霉 mei
{1,0,{pysm::l,pyym::ing}},//霊 ling
{1,0,{pysm::q,pyym::i}},//霋 qi
{1,0,{pysm::zh,pyym::ou}},//霌 zhou
{3,834,{pysm::nop,pyym::nop}},//霍 huo
{1,0,{pysm::sh,pyym::a}},//霎 sha
{1,0,{pysm::f,pyym::ei}},//霏 fei
{1,0,{pysm::h,pyym::ong}},//霐 hong
{1,0,{pysm::zh,pyym::an}},//霑 zhan
{1,0,{pysm::y,pyym::in}},//霒 yin
{1,0,{pysm::n,pyym::i}},//霓 ni
{1,0,{pysm::zh,pyym::u}},//霔 zhu
{1,0,{pysm::t,pyym::un}},//霕 tun
{1,0,{pysm::l,pyym::in}},//霖 lin
{1,0,{pysm::l,pyym::ing}},//霗 ling
{1,0,{pysm::d,pyym::ong}},//霘 dong
{2,3502,{pysm::nop,pyym::nop}},//霙 ying
{1,0,{pysm::w,pyym::u}},//霚 wu
{1,0,{pysm::l,pyym::ing}},//霛 ling
{1,0,{pysm::sh,pyym::uang}},//霜 shuang
{1,0,{pysm::l,pyym::ing}},//霝 ling
{1,0,{pysm::x,pyym::ia}},//霞 xia
{1,0,{pysm::h,pyym::ong}},//霟 hong
{1,0,{pysm::y,pyym::in}},//霠 yin
{1,0,{pysm::m,pyym::ai}},//霡 mai
{1,0,{pysm::m,pyym::ai}},//霢 mai
{1,0,{pysm::y,pyym::un}},//霣 yun
{1,0,{pysm::l,pyym::iu}},//霤 liu
{1,0,{pysm::m,pyym::eng}},//霥 meng
{1,0,{pysm::b,pyym::in}},//霦 bin
{2,3503,{pysm::nop,pyym::nop}},//霧 wu
{1,0,{pysm::w,pyym::ei}},//霨 wei
{1,0,{pysm::k,pyym::uo}},//霩 kuo
{1,0,{pysm::y,pyym::in}},//霪 yin
{1,0,{pysm::x,pyym::i}},//霫 xi
{1,0,{pysm::y,pyym::i}},//霬 yi
{1,0,{pysm::nop,pyym::ai}},//霭 ai
{1,0,{pysm::d,pyym::an}},//霮 dan
{1,0,{pysm::t,pyym::eng}},//霯 teng
{2,3504,{pysm::nop,pyym::nop}},//霰 xian
{1,0,{pysm::y,pyym::u}},//霱 yu
{2,3505,{pysm::nop,pyym::nop}},//露 lu
{1,0,{pysm::l,pyym::ong}},//霳 long
{1,0,{pysm::d,pyym::ai}},//霴 dai
{1,0,{pysm::j,pyym::i}},//霵 ji
{1,0,{pysm::p,pyym::ang}},//霶 pang
{1,0,{pysm::y,pyym::ang}},//霷 yang
{2,3506,{pysm::nop,pyym::nop}},//霸 ba
{1,0,{pysm::p,pyym::i}},//霹 pi
{1,0,{pysm::w,pyym::ei}},//霺 wei
{1,0,{pysm::f,pyym::eng}},//霻 feng
{1,0,{pysm::x,pyym::i}},//霼 xi
{1,0,{pysm::j,pyym::i}},//霽 ji
{2,3507,{pysm::nop,pyym::nop}},//霾 mai
{3,835,{pysm::nop,pyym::nop}},//霿 meng
{1,0,{pysm::m,pyym::eng}},//靀 meng
{1,0,{pysm::l,pyym::ei}},//靁 lei
{1,0,{pysm::l,pyym::i}},//靂 li
{3,836,{pysm::nop,pyym::nop}},//靃 huo
{1,0,{pysm::nop,pyym::ai}},//靄 ai
{1,0,{pysm::f,pyym::ei}},//靅 fei
{1,0,{pysm::d,pyym::ai}},//靆 dai
{2,3508,{pysm::nop,pyym::nop}},//靇 long
{1,0,{pysm::l,pyym::ing}},//靈 ling
{2,3509,{pysm::nop,pyym::nop}},//靉 ai
{1,0,{pysm::f,pyym::eng}},//靊 feng
{1,0,{pysm::l,pyym::i}},//靋 li
{1,0,{pysm::b,pyym::ao}},//靌 bao
{1,0,{pysm::h,pyym::e}},//靍 he
{1,0,{pysm::h,pyym::e}},//靎 he
{1,0,{pysm::h,pyym::e}},//靏 he
{1,0,{pysm::b,pyym::ing}},//靐 bing
{1,0,{pysm::q,pyym::ing}},//靑 qing
{2,3510,{pysm::nop,pyym::nop}},//青 qing
{2,3511,{pysm::nop,pyym::nop}},//靓 jing
{1,0,{pysm::t,pyym::ian}},//靔 tian
{1,0,{pysm::zh,pyym::en}},//靕 zhen
{1,0,{pysm::j,pyym::ing}},//靖 jing
{1,0,{pysm::ch,pyym::eng}},//靗 cheng
{2,3512,{pysm::nop,pyym::nop}},//靘 qing
{1,0,{pysm::j,pyym::ing}},//静 jing
{2,3513,{pysm::nop,pyym::nop}},//靚 jing
{1,0,{pysm::d,pyym::ian}},//靛 dian
{1,0,{pysm::j,pyym::ing}},//靜 jing
{1,0,{pysm::t,pyym::ian}},//靝 tian
{1,0,{pysm::f,pyym::ei}},//非 fei
{1,0,{pysm::f,pyym::ei}},//靟 fei
{1,0,{pysm::k,pyym::ao}},//靠 kao
{2,3514,{pysm::nop,pyym::nop}},//靡 mi
{1,0,{pysm::m,pyym::ian}},//面 mian
{1,0,{pysm::m,pyym::ian}},//靣 mian
{1,0,{pysm::b,pyym::ao}},//靤 bao
{1,0,{pysm::y,pyym::e}},//靥 ye
{2,3515,{pysm::nop,pyym::nop}},//靦 tian
{1,0,{pysm::h,pyym::ui}},//靧 hui
{2,3516,{pysm::nop,pyym::nop}},//靨 ye
{2,3517,{pysm::nop,pyym::nop}},//革 ge
{1,0,{pysm::d,pyym::ing}},//靪 ding
{1,0,{pysm::ch,pyym::a}},//靫 cha
{4,168,{pysm::nop,pyym::nop}},//靬 qian
{1,0,{pysm::r,pyym::en}},//靭 ren
{1,0,{pysm::d,pyym::i}},//靮 di
{1,0,{pysm::d,pyym::u}},//靯 du
{1,0,{pysm::w,pyym::u}},//靰 wu
{1,0,{pysm::r,pyym::en}},//靱 ren
{1,0,{pysm::q,pyym::in}},//靲 qin
{1,0,{pysm::j,pyym::in}},//靳 jin
{1,0,{pysm::x,pyym::ue}},//靴 xue
{1,0,{pysm::n,pyym::iu}},//靵 niu
{1,0,{pysm::b,pyym::a}},//靶 ba
{1,0,{pysm::y,pyym::in}},//靷 yin
{2,3518,{pysm::nop,pyym::nop}},//靸 sa
{1,0,{pysm::n,pyym::a}},//靹 na
{2,3519,{pysm::nop,pyym::nop}},//靺 mo
{1,0,{pysm::z,pyym::u}},//靻 zu
{1,0,{pysm::d,pyym::a}},//靼 da
{1,0,{pysm::b,pyym::an}},//靽 ban
{1,0,{pysm::y,pyym::i}},//靾 yi
{1,0,{pysm::y,pyym::ao}},//靿 yao
{1,0,{pysm::t,pyym::ao}},//鞀 tao
{3,837,{pysm::nop,pyym::nop}},//鞁 bei
{1,0,{pysm::j,pyym::ie}},//鞂 jie
{1,0,{pysm::h,pyym::ong}},//鞃 hong
{1,0,{pysm::p,pyym::ao}},//鞄 pao
{1,0,{pysm::y,pyym::ang}},//鞅 yang
{1,0,{pysm::b,pyym::ing}},//鞆 bing
{1,0,{pysm::y,pyym::in}},//鞇 yin
{3,838,{pysm::nop,pyym::nop}},//鞈 ge
{1,0,{pysm::t,pyym::ao}},//鞉 tao
{2,3520,{pysm::nop,pyym::nop}},//鞊 jie
{2,3521,{pysm::nop,pyym::nop}},//鞋 xie
{1,0,{pysm::nop,pyym::an}},//鞌 an
{1,0,{pysm::nop,pyym::an}},//鞍 an
{1,0,{pysm::h,pyym::en}},//鞎 hen
{1,0,{pysm::g,pyym::ong}},//鞏 gong
{1,0,{pysm::q,pyym::ia}},//鞐 qia
{1,0,{pysm::d,pyym::a}},//鞑 da
{1,0,{pysm::q,pyym::iao}},//鞒 qiao
{1,0,{pysm::t,pyym::ing}},//鞓 ting
{2,3522,{pysm::nop,pyym::nop}},//鞔 man
{2,3523,{pysm::nop,pyym::nop}},//鞕 ying
{1,0,{pysm::s,pyym::ui}},//鞖 sui
{1,0,{pysm::t,pyym::iao}},//鞗 tiao
{2,3524,{pysm::nop,pyym::nop}},//鞘 qiao
{2,3525,{pysm::nop,pyym::nop}},//鞙 xuan
{1,0,{pysm::k,pyym::ong}},//鞚 kong
{1,0,{pysm::b,pyym::eng}},//鞛 beng
{1,0,{pysm::t,pyym::a}},//鞜 ta
{2,3526,{pysm::nop,pyym::nop}},//鞝 shang
{4,169,{pysm::nop,pyym::nop}},//鞞 bing
{1,0,{pysm::k,pyym::uo}},//鞟 kuo
{3,839,{pysm::nop,pyym::nop}},//鞠 ju
{1,0,{pysm::l,pyym::a}},//鞡 la
{3,840,{pysm::nop,pyym::nop}},//鞢 xie
{1,0,{pysm::r,pyym::ou}},//鞣 rou
{1,0,{pysm::b,pyym::ang}},//鞤 bang
{1,0,{pysm::nop,pyym::eng}},//鞥 eng
{1,0,{pysm::q,pyym::iu}},//鞦 qiu
{1,0,{pysm::q,pyym::iu}},//鞧 qiu
{3,841,{pysm::nop,pyym::nop}},//鞨 he
{1,0,{pysm::q,pyym::iao}},//鞩 qiao
{2,3527,{pysm::nop,pyym::nop}},//鞪 mu
{2,3528,{pysm::nop,pyym::nop}},//鞫 ju
{1,0,{pysm::j,pyym::ian}},//鞬 jian
{1,0,{pysm::b,pyym::ian}},//鞭 bian
{1,0,{pysm::d,pyym::i}},//鞮 di
{1,0,{pysm::j,pyym::ian}},//鞯 jian
{1,0,{pysm::w,pyym::en}},//鞰 wen
{1,0,{pysm::t,pyym::ao}},//鞱 tao
{1,0,{pysm::g,pyym::ou}},//鞲 gou
{1,0,{pysm::t,pyym::a}},//鞳 ta
{4,170,{pysm::nop,pyym::nop}},//鞴 bei
{1,0,{pysm::x,pyym::ie}},//鞵 xie
{1,0,{pysm::p,pyym::an}},//鞶 pan
{1,0,{pysm::g,pyym::e}},//鞷 ge
{2,3529,{pysm::nop,pyym::nop}},//鞸 bi
{1,0,{pysm::k,pyym::uo}},//鞹 kuo
{1,0,{pysm::t,pyym::ang}},//鞺 tang
{1,0,{pysm::l,pyym::ou}},//鞻 lou
{2,3530,{pysm::nop,pyym::nop}},//鞼 gui
{2,3531,{pysm::nop,pyym::nop}},//鞽 qiao
{1,0,{pysm::x,pyym::ue}},//鞾 xue
{1,0,{pysm::j,pyym::i}},//鞿 ji
{1,0,{pysm::j,pyym::ian}},//韀 jian
{1,0,{pysm::j,pyym::iang}},//韁 jiang
{1,0,{pysm::ch,pyym::an}},//韂 chan
{2,3532,{pysm::nop,pyym::nop}},//韃 da
{1,0,{pysm::h,pyym::u}},//韄 hu
{1,0,{pysm::x,pyym::ian}},//韅 xian
{1,0,{pysm::q,pyym::ian}},//韆 qian
{1,0,{pysm::d,pyym::u}},//韇 du
{1,0,{pysm::w,pyym::a}},//韈 wa
{1,0,{pysm::j,pyym::ian}},//韉 jian
{1,0,{pysm::l,pyym::an}},//韊 lan
{2,3533,{pysm::nop,pyym::nop}},//韋 wei
{1,0,{pysm::r,pyym::en}},//韌 ren
{1,0,{pysm::f,pyym::u}},//韍 fu
{1,0,{pysm::m,pyym::ei}},//韎 mei
{2,3534,{pysm::nop,pyym::nop}},//韏 quan
{1,0,{pysm::g,pyym::e}},//韐 ge
{1,0,{pysm::w,pyym::ei}},//韑 wei
{2,3535,{pysm::nop,pyym::nop}},//韒 qiao
{1,0,{pysm::h,pyym::an}},//韓 han
{1,0,{pysm::ch,pyym::ang}},//韔 chang
{1,0,{pysm::k,pyym::uo}},//韕 kuo
{1,0,{pysm::r,pyym::ou}},//韖 rou
{1,0,{pysm::y,pyym::un}},//韗 yun
{1,0,{pysm::sh,pyym::e}},//韘 she
{1,0,{pysm::w,pyym::ei}},//韙 wei
{1,0,{pysm::g,pyym::e}},//韚 ge
{2,3536,{pysm::nop,pyym::nop}},//韛 bai
{1,0,{pysm::t,pyym::ao}},//韜 tao
{1,0,{pysm::g,pyym::ou}},//韝 gou
{2,3537,{pysm::nop,pyym::nop}},//韞 yun
{1,0,{pysm::g,pyym::ao}},//韟 gao
{1,0,{pysm::b,pyym::i}},//韠 bi
{2,3538,{pysm::nop,pyym::nop}},//韡 wei
{2,3539,{pysm::nop,pyym::nop}},//韢 sui
{1,0,{pysm::d,pyym::u}},//韣 du
{1,0,{pysm::w,pyym::a}},//韤 wa
{1,0,{pysm::d,pyym::u}},//韥 du
{1,0,{pysm::w,pyym::ei}},//韦 wei
{1,0,{pysm::r,pyym::en}},//韧 ren
{1,0,{pysm::f,pyym::u}},//韨 fu
{1,0,{pysm::h,pyym::an}},//韩 han
{1,0,{pysm::w,pyym::ei}},//韪 wei
{1,0,{pysm::y,pyym::un}},//韫 yun
{1,0,{pysm::t,pyym::ao}},//韬 tao
{1,0,{pysm::j,pyym::iu}},//韭 jiu
{1,0,{pysm::j,pyym::iu}},//韮 jiu
{1,0,{pysm::x,pyym::ian}},//韯 xian
{1,0,{pysm::x,pyym::ie}},//韰 xie
{1,0,{pysm::x,pyym::ian}},//韱 xian
{1,0,{pysm::j,pyym::i}},//韲 ji
{1,0,{pysm::y,pyym::in}},//音 yin
{1,0,{pysm::z,pyym::a}},//韴 za
{1,0,{pysm::y,pyym::un}},//韵 yun
{1,0,{pysm::sh,pyym::ao}},//韶 shao
{1,0,{pysm::l,pyym::e}},//韷 le
{1,0,{pysm::p,pyym::eng}},//韸 peng
{2,3540,{pysm::nop,pyym::nop}},//韹 huang
{1,0,{pysm::y,pyym::ing}},//韺 ying
{1,0,{pysm::y,pyym::un}},//韻 yun
{1,0,{pysm::p,pyym::eng}},//韼 peng
{1,0,{pysm::nop,pyym::an}},//韽 an
{1,0,{pysm::y,pyym::in}},//韾 yin
{1,0,{pysm::x,pyym::iang}},//響 xiang
{1,0,{pysm::h,pyym::u}},//頀 hu
{2,3541,{pysm::nop,pyym::nop}},//頁 ye
{1,0,{pysm::d,pyym::ing}},//頂 ding
{2,3542,{pysm::nop,pyym::nop}},//頃 qing
{1,0,{pysm::k,pyym::ui}},//頄 kui
{1,0,{pysm::x,pyym::iang}},//項 xiang
{1,0,{pysm::sh,pyym::un}},//順 shun
{2,3543,{pysm::nop,pyym::nop}},//頇 han
{1,0,{pysm::x,pyym::u}},//須 xu
{1,0,{pysm::y,pyym::i}},//頉 yi
{1,0,{pysm::x,pyym::u}},//頊 xu
{1,0,{pysm::nop,pyym::e}},//頋 e
{2,3544,{pysm::nop,pyym::nop}},//頌 song
{1,0,{pysm::k,pyym::ui}},//頍 kui
{2,3545,{pysm::nop,pyym::nop}},//頎 qi
{2,3546,{pysm::nop,pyym::nop}},//頏 hang
{1,0,{pysm::y,pyym::u}},//預 yu
{2,3547,{pysm::nop,pyym::nop}},//頑 wan
{2,3548,{pysm::nop,pyym::nop}},//頒 ban
{2,3549,{pysm::nop,pyym::nop}},//頓 dun
{1,0,{pysm::d,pyym::i}},//頔 di
{2,3550,{pysm::nop,pyym::nop}},//頕 dan
{1,0,{pysm::p,pyym::an}},//頖 pan
{2,3551,{pysm::nop,pyym::nop}},//頗 po
{1,0,{pysm::l,pyym::ing}},//領 ling
{1,0,{pysm::ch,pyym::e}},//頙 che
{1,0,{pysm::j,pyym::ing}},//頚 jing
{1,0,{pysm::l,pyym::ei}},//頛 lei
{4,171,{pysm::nop,pyym::nop}},//頜 he
{1,0,{pysm::q,pyym::iao}},//頝 qiao
{2,3552,{pysm::nop,pyym::nop}},//頞 e
{1,0,{pysm::nop,pyym::e}},//頟 e
{1,0,{pysm::w,pyym::ei}},//頠 wei
{3,842,{pysm::nop,pyym::nop}},//頡 xie
{1,0,{pysm::k,pyym::uo}},//頢 kuo
{1,0,{pysm::sh,pyym::en}},//頣 shen
{1,0,{pysm::y,pyym::i}},//頤 yi
{1,0,{pysm::y,pyym::i}},//頥 yi
{2,3553,{pysm::nop,pyym::nop}},//頦 hai
{1,0,{pysm::d,pyym::ui}},//頧 dui
{2,3554,{pysm::nop,pyym::nop}},//頨 yu
{1,0,{pysm::p,pyym::ing}},//頩 ping
{1,0,{pysm::l,pyym::ei}},//頪 lei
{3,843,{pysm::nop,pyym::nop}},//頫 fu
{1,0,{pysm::j,pyym::ia}},//頬 jia
{1,0,{pysm::t,pyym::ou}},//頭 tou
{1,0,{pysm::h,pyym::ui}},//頮 hui
{1,0,{pysm::k,pyym::ui}},//頯 kui
{1,0,{pysm::j,pyym::ia}},//頰 jia
{1,0,{pysm::l,pyym::uo}},//頱 luo
{1,0,{pysm::t,pyym::ing}},//頲 ting
{1,0,{pysm::ch,pyym::eng}},//頳 cheng
{2,3555,{pysm::nop,pyym::nop}},//頴 ying
{1,0,{pysm::y,pyym::un}},//頵 yun
{1,0,{pysm::h,pyym::u}},//頶 hu
{1,0,{pysm::h,pyym::an}},//頷 han
{2,3556,{pysm::nop,pyym::nop}},//頸 jing
{1,0,{pysm::t,pyym::ui}},//頹 tui
{1,0,{pysm::t,pyym::ui}},//頺 tui
{2,3557,{pysm::nop,pyym::nop}},//頻 pin
{1,0,{pysm::l,pyym::ai}},//頼 lai
{1,0,{pysm::t,pyym::ui}},//頽 tui
{1,0,{pysm::z,pyym::i}},//頾 zi
{1,0,{pysm::z,pyym::i}},//頿 zi
{1,0,{pysm::ch,pyym::ui}},//顀 chui
{1,0,{pysm::d,pyym::ing}},//顁 ding
{1,0,{pysm::l,pyym::ai}},//顂 lai
{2,3558,{pysm::nop,pyym::nop}},//顃 tan
{1,0,{pysm::h,pyym::an}},//顄 han
{1,0,{pysm::q,pyym::ian}},//顅 qian
{2,3559,{pysm::nop,pyym::nop}},//顆 ke
{2,3560,{pysm::nop,pyym::nop}},//顇 cui
{3,844,{pysm::nop,pyym::nop}},//顈 xuan
{1,0,{pysm::q,pyym::in}},//顉 qin
{1,0,{pysm::y,pyym::i}},//顊 yi
{1,0,{pysm::s,pyym::ai}},//顋 sai
{2,3561,{pysm::nop,pyym::nop}},//題 ti
{1,0,{pysm::nop,pyym::e}},//額 e
{1,0,{pysm::nop,pyym::e}},//顎 e
{1,0,{pysm::y,pyym::an}},//顏 yan
{2,3562,{pysm::nop,pyym::nop}},//顐 wen
{2,3563,{pysm::nop,pyym::nop}},//顑 kan
{2,3564,{pysm::nop,pyym::nop}},//顒 yong
{1,0,{pysm::zh,pyym::uan}},//顓 zhuan
{2,3565,{pysm::nop,pyym::nop}},//顔 yan
{1,0,{pysm::x,pyym::ian}},//顕 xian
{1,0,{pysm::x,pyym::in}},//顖 xin
{1,0,{pysm::y,pyym::i}},//顗 yi
{1,0,{pysm::y,pyym::uan}},//願 yuan
{1,0,{pysm::s,pyym::ang}},//顙 sang
{2,3566,{pysm::nop,pyym::nop}},//顚 dian
{1,0,{pysm::d,pyym::ian}},//顛 dian
{1,0,{pysm::j,pyym::iang}},//顜 jiang
{2,3567,{pysm::nop,pyym::nop}},//顝 kui
{1,0,{pysm::l,pyym::ei}},//類 lei
{1,0,{pysm::l,pyym::ao}},//顟 lao
{1,0,{pysm::p,pyym::iao}},//顠 piao
{2,3568,{pysm::nop,pyym::nop}},//顡 wai
{1,0,{pysm::m,pyym::an}},//顢 man
{1,0,{pysm::c,pyym::u}},//顣 cu
{2,3569,{pysm::nop,pyym::nop}},//顤 yao
{1,0,{pysm::h,pyym::ao}},//顥 hao
{1,0,{pysm::q,pyym::iao}},//顦 qiao
{1,0,{pysm::g,pyym::u}},//顧 gu
{1,0,{pysm::x,pyym::un}},//顨 xun
{4,172,{pysm::nop,pyym::nop}},//顩 yan
{1,0,{pysm::h,pyym::ui}},//顪 hui
{3,845,{pysm::nop,pyym::nop}},//顫 chan
{1,0,{pysm::r,pyym::u}},//顬 ru
{1,0,{pysm::m,pyym::eng}},//顭 meng
{1,0,{pysm::b,pyym::in}},//顮 bin
{1,0,{pysm::x,pyym::ian}},//顯 xian
{1,0,{pysm::p,pyym::in}},//顰 pin
{1,0,{pysm::l,pyym::u}},//顱 lu
{2,3570,{pysm::nop,pyym::nop}},//顲 lan
{1,0,{pysm::n,pyym::ie}},//顳 nie
{1,0,{pysm::q,pyym::uan}},//顴 quan
{1,0,{pysm::y,pyym::e}},//页 ye
{1,0,{pysm::d,pyym::ing}},//顶 ding
{1,0,{pysm::q,pyym::ing}},//顷 qing
{1,0,{pysm::h,pyym::an}},//顸 han
{1,0,{pysm::x,pyym::iang}},//项 xiang
{1,0,{pysm::sh,pyym::un}},//顺 shun
{1,0,{pysm::x,pyym::u}},//须 xu
{1,0,{pysm::x,pyym::u}},//顼 xu
{1,0,{pysm::w,pyym::an}},//顽 wan
{1,0,{pysm::g,pyym::u}},//顾 gu
{2,3571,{pysm::nop,pyym::nop}},//顿 dun
{1,0,{pysm::q,pyym::i}},//颀 qi
{1,0,{pysm::b,pyym::an}},//颁 ban
{1,0,{pysm::s,pyym::ong}},//颂 song
{1,0,{pysm::h,pyym::ang}},//颃 hang
{1,0,{pysm::y,pyym::u}},//预 yu
{1,0,{pysm::l,pyym::u}},//颅 lu
{1,0,{pysm::l,pyym::ing}},//领 ling
{1,0,{pysm::p,pyym::o}},//颇 po
{2,3572,{pysm::nop,pyym::nop}},//颈 jing
{2,3573,{pysm::nop,pyym::nop}},//颉 jie
{1,0,{pysm::j,pyym::ia}},//颊 jia
{1,0,{pysm::t,pyym::ing}},//颋 ting
{2,3574,{pysm::nop,pyym::nop}},//颌 he
{1,0,{pysm::y,pyym::ing}},//颍 ying
{1,0,{pysm::j,pyym::iong}},//颎 jiong
{1,0,{pysm::k,pyym::e}},//颏 ke
{1,0,{pysm::y,pyym::i}},//颐 yi
{1,0,{pysm::p,pyym::in}},//频 pin
{1,0,{pysm::h,pyym::ui}},//颒 hui
{1,0,{pysm::t,pyym::ui}},//颓 tui
{1,0,{pysm::h,pyym::an}},//颔 han
{1,0,{pysm::y,pyym::ing}},//颕 ying
{1,0,{pysm::y,pyym::ing}},//颖 ying
{1,0,{pysm::k,pyym::e}},//颗 ke
{1,0,{pysm::t,pyym::i}},//题 ti
{1,0,{pysm::y,pyym::ong}},//颙 yong
{1,0,{pysm::nop,pyym::e}},//颚 e
{1,0,{pysm::zh,pyym::uan}},//颛 zhuan
{1,0,{pysm::y,pyym::an}},//颜 yan
{1,0,{pysm::nop,pyym::e}},//额 e
{1,0,{pysm::n,pyym::ie}},//颞 nie
{1,0,{pysm::m,pyym::an}},//颟 man
{1,0,{pysm::d,pyym::ian}},//颠 dian
{1,0,{pysm::s,pyym::ang}},//颡 sang
{1,0,{pysm::h,pyym::ao}},//颢 hao
{1,0,{pysm::l,pyym::ei}},//颣 lei
{2,3575,{pysm::nop,pyym::nop}},//颤 chan
{1,0,{pysm::r,pyym::u}},//颥 ru
{1,0,{pysm::p,pyym::in}},//颦 pin
{1,0,{pysm::q,pyym::uan}},//颧 quan
{1,0,{pysm::f,pyym::eng}},//風 feng
{2,3576,{pysm::nop,pyym::nop}},//颩 biao
{1,0,{pysm::g,pyym::ua}},//颪 gua
{1,0,{pysm::f,pyym::u}},//颫 fu
{1,0,{pysm::x,pyym::ia}},//颬 xia
{1,0,{pysm::zh,pyym::an}},//颭 zhan
{2,3577,{pysm::nop,pyym::nop}},//颮 biao
{2,3578,{pysm::nop,pyym::nop}},//颯 sa
{2,3579,{pysm::nop,pyym::nop}},//颰 ba
{1,0,{pysm::t,pyym::ai}},//颱 tai
{1,0,{pysm::l,pyym::ie}},//颲 lie
{2,3580,{pysm::nop,pyym::nop}},//颳 gua
{1,0,{pysm::x,pyym::uan}},//颴 xuan
{2,3581,{pysm::nop,pyym::nop}},//颵 shao
{1,0,{pysm::j,pyym::u}},//颶 ju
{1,0,{pysm::b,pyym::iao}},//颷 biao
{1,0,{pysm::s,pyym::i}},//颸 si
{1,0,{pysm::w,pyym::ei}},//颹 wei
{1,0,{pysm::y,pyym::ang}},//颺 yang
{1,0,{pysm::y,pyym::ao}},//颻 yao
{1,0,{pysm::s,pyym::ou}},//颼 sou
{1,0,{pysm::k,pyym::ai}},//颽 kai
{2,3582,{pysm::nop,pyym::nop}},//颾 sou
{1,0,{pysm::f,pyym::an}},//颿 fan
{1,0,{pysm::l,pyym::iu}},//飀 liu
{1,0,{pysm::x,pyym::i}},//飁 xi
{2,3583,{pysm::nop,pyym::nop}},//飂 liu
{1,0,{pysm::p,pyym::iao}},//飃 piao
{1,0,{pysm::p,pyym::iao}},//飄 piao
{1,0,{pysm::l,pyym::iu}},//飅 liu
{1,0,{pysm::b,pyym::iao}},//飆 biao
{1,0,{pysm::b,pyym::iao}},//飇 biao
{1,0,{pysm::b,pyym::iao}},//飈 biao
{1,0,{pysm::l,pyym::iao}},//飉 liao
{1,0,{pysm::b,pyym::iao}},//飊 biao
{1,0,{pysm::s,pyym::e}},//飋 se
{1,0,{pysm::f,pyym::eng}},//飌 feng
{1,0,{pysm::x,pyym::iu}},//飍 xiu
{1,0,{pysm::f,pyym::eng}},//风 feng
{1,0,{pysm::y,pyym::ang}},//飏 yang
{1,0,{pysm::zh,pyym::an}},//飐 zhan
{1,0,{pysm::b,pyym::iao}},//飑 biao
{1,0,{pysm::s,pyym::a}},//飒 sa
{1,0,{pysm::j,pyym::u}},//飓 ju
{1,0,{pysm::s,pyym::i}},//飔 si
{1,0,{pysm::s,pyym::ou}},//飕 sou
{1,0,{pysm::y,pyym::ao}},//飖 yao
{1,0,{pysm::l,pyym::iu}},//飗 liu
{1,0,{pysm::p,pyym::iao}},//飘 piao
{1,0,{pysm::b,pyym::iao}},//飙 biao
{1,0,{pysm::b,pyym::iao}},//飚 biao
{1,0,{pysm::f,pyym::ei}},//飛 fei
{1,0,{pysm::f,pyym::an}},//飜 fan
{1,0,{pysm::f,pyym::ei}},//飝 fei
{1,0,{pysm::f,pyym::ei}},//飞 fei
{3,846,{pysm::nop,pyym::nop}},//食 shi
{1,0,{pysm::sh,pyym::i}},//飠 shi
{1,0,{pysm::c,pyym::an}},//飡 can
{1,0,{pysm::j,pyym::i}},//飢 ji
{1,0,{pysm::d,pyym::ing}},//飣 ding
{1,0,{pysm::s,pyym::i}},//飤 si
{1,0,{pysm::t,pyym::uo}},//飥 tuo
{2,3584,{pysm::nop,pyym::nop}},//飦 zhan
{1,0,{pysm::s,pyym::un}},//飧 sun
{1,0,{pysm::x,pyym::iang}},//飨 xiang
{2,3585,{pysm::nop,pyym::nop}},//飩 tun
{1,0,{pysm::r,pyym::en}},//飪 ren
{1,0,{pysm::y,pyym::u}},//飫 yu
{2,3586,{pysm::nop,pyym::nop}},//飬 juan
{2,3587,{pysm::nop,pyym::nop}},//飭 chi
{1,0,{pysm::y,pyym::in}},//飮 yin
{1,0,{pysm::f,pyym::an}},//飯 fan
{1,0,{pysm::f,pyym::an}},//飰 fan
{2,3588,{pysm::nop,pyym::nop}},//飱 sun
{1,0,{pysm::y,pyym::in}},//飲 yin
{2,3589,{pysm::nop,pyym::nop}},//飳 tou
{2,3590,{pysm::nop,pyym::nop}},//飴 yi
{2,3591,{pysm::nop,pyym::nop}},//飵 zuo
{1,0,{pysm::b,pyym::i}},//飶 bi
{1,0,{pysm::j,pyym::ie}},//飷 jie
{1,0,{pysm::t,pyym::ao}},//飸 tao
{1,0,{pysm::b,pyym::ao}},//飹 bao
{1,0,{pysm::c,pyym::i}},//飺 ci
{1,0,{pysm::t,pyym::ie}},//飻 tie
{1,0,{pysm::s,pyym::i}},//飼 si
{1,0,{pysm::b,pyym::ao}},//飽 bao
{2,3592,{pysm::nop,pyym::nop}},//飾 shi
{1,0,{pysm::d,pyym::uo}},//飿 duo
{1,0,{pysm::h,pyym::ai}},//餀 hai
{1,0,{pysm::r,pyym::en}},//餁 ren
{1,0,{pysm::t,pyym::ian}},//餂 tian
{1,0,{pysm::j,pyym::iao}},//餃 jiao
{2,3593,{pysm::nop,pyym::nop}},//餄 jia
{1,0,{pysm::b,pyym::ing}},//餅 bing
{1,0,{pysm::y,pyym::ao}},//餆 yao
{1,0,{pysm::t,pyym::ong}},//餇 tong
{1,0,{pysm::c,pyym::i}},//餈 ci
{1,0,{pysm::x,pyym::iang}},//餉 xiang
{1,0,{pysm::y,pyym::ang}},//養 yang
{1,0,{pysm::j,pyym::uan}},//餋 juan
{1,0,{pysm::nop,pyym::er}},//餌 er
{1,0,{pysm::y,pyym::an}},//餍 yan
{1,0,{pysm::l,pyym::e}},//餎 le
{1,0,{pysm::x,pyym::i}},//餏 xi
{2,3594,{pysm::nop,pyym::nop}},//餐 can
{1,0,{pysm::b,pyym::o}},//餑 bo
{1,0,{pysm::n,pyym::ei}},//餒 nei
{1,0,{pysm::nop,pyym::e}},//餓 e
{1,0,{pysm::b,pyym::u}},//餔 bu
{1,0,{pysm::j,pyym::un}},//餕 jun
{1,0,{pysm::d,pyym::ou}},//餖 dou
{1,0,{pysm::s,pyym::u}},//餗 su
{2,3595,{pysm::nop,pyym::nop}},//餘 yu
{2,3596,{pysm::nop,pyym::nop}},//餙 shi
{1,0,{pysm::y,pyym::ao}},//餚 yao
{2,3597,{pysm::nop,pyym::nop}},//餛 hun
{1,0,{pysm::g,pyym::uo}},//餜 guo
{1,0,{pysm::sh,pyym::i}},//餝 shi
{1,0,{pysm::j,pyym::ian}},//餞 jian
{1,0,{pysm::zh,pyym::ui}},//餟 zhui
{1,0,{pysm::b,pyym::ing}},//餠 bing
{2,3598,{pysm::nop,pyym::nop}},//餡 xian
{1,0,{pysm::b,pyym::u}},//餢 bu
{1,0,{pysm::y,pyym::e}},//餣 ye
{2,3599,{pysm::nop,pyym::nop}},//餤 tan
{1,0,{pysm::f,pyym::ei}},//餥 fei
{1,0,{pysm::zh,pyym::ang}},//餦 zhang
{2,3600,{pysm::nop,pyym::nop}},//餧 wei
{1,0,{pysm::g,pyym::uan}},//館 guan
{1,0,{pysm::nop,pyym::e}},//餩 e
{1,0,{pysm::n,pyym::uan}},//餪 nuan
{2,3601,{pysm::nop,pyym::nop}},//餫 yun
{1,0,{pysm::h,pyym::u}},//餬 hu
{1,0,{pysm::h,pyym::uang}},//餭 huang
{1,0,{pysm::t,pyym::ie}},//餮 tie
{1,0,{pysm::h,pyym::ui}},//餯 hui
{2,3602,{pysm::nop,pyym::nop}},//餰 jian
{1,0,{pysm::h,pyym::ou}},//餱 hou
{2,3603,{pysm::nop,pyym::nop}},//餲 ai
{2,3604,{pysm::nop,pyym::nop}},//餳 tang
{1,0,{pysm::f,pyym::en}},//餴 fen
{1,0,{pysm::w,pyym::ei}},//餵 wei
{1,0,{pysm::g,pyym::u}},//餶 gu
{1,0,{pysm::ch,pyym::a}},//餷 cha
{1,0,{pysm::s,pyym::ong}},//餸 song
{1,0,{pysm::t,pyym::ang}},//餹 tang
{1,0,{pysm::b,pyym::o}},//餺 bo
{1,0,{pysm::g,pyym::ao}},//餻 gao
{1,0,{pysm::x,pyym::i}},//餼 xi
{1,0,{pysm::k,pyym::ui}},//餽 kui
{1,0,{pysm::l,pyym::iu}},//餾 liu
{1,0,{pysm::s,pyym::ou}},//餿 sou
{2,3605,{pysm::nop,pyym::nop}},//饀 tao
{1,0,{pysm::y,pyym::e}},//饁 ye
{1,0,{pysm::w,pyym::en}},//饂 wen
{1,0,{pysm::m,pyym::o}},//饃 mo
{1,0,{pysm::t,pyym::ang}},//饄 tang
{1,0,{pysm::m,pyym::an}},//饅 man
{1,0,{pysm::b,pyym::i}},//饆 bi
{1,0,{pysm::y,pyym::u}},//饇 yu
{1,0,{pysm::x,pyym::iu}},//饈 xiu
{1,0,{pysm::j,pyym::in}},//饉 jin
{1,0,{pysm::s,pyym::an}},//饊 san
{2,3606,{pysm::nop,pyym::nop}},//饋 kui
{2,3607,{pysm::nop,pyym::nop}},//饌 zhuan
{1,0,{pysm::sh,pyym::an}},//饍 shan
{1,0,{pysm::ch,pyym::i}},//饎 chi
{1,0,{pysm::d,pyym::an}},//饏 dan
{3,847,{pysm::nop,pyym::nop}},//饐 yi
{2,3608,{pysm::nop,pyym::nop}},//饑 ji
{1,0,{pysm::r,pyym::ao}},//饒 rao
{1,0,{pysm::ch,pyym::eng}},//饓 cheng
{1,0,{pysm::y,pyym::ong}},//饔 yong
{1,0,{pysm::t,pyym::ao}},//饕 tao
{1,0,{pysm::w,pyym::ei}},//饖 wei
{1,0,{pysm::x,pyym::iang}},//饗 xiang
{1,0,{pysm::zh,pyym::an}},//饘 zhan
{1,0,{pysm::f,pyym::en}},//饙 fen
{1,0,{pysm::h,pyym::ai}},//饚 hai
{1,0,{pysm::m,pyym::eng}},//饛 meng
{1,0,{pysm::y,pyym::an}},//饜 yan
{1,0,{pysm::m,pyym::o}},//饝 mo
{1,0,{pysm::ch,pyym::an}},//饞 chan
{1,0,{pysm::x,pyym::iang}},//饟 xiang
{1,0,{pysm::l,pyym::uo}},//饠 luo
{1,0,{pysm::z,pyym::an}},//饡 zan
{1,0,{pysm::n,pyym::ang}},//饢 nang
{1,0,{pysm::sh,pyym::i}},//饣 shi
{1,0,{pysm::d,pyym::ing}},//饤 ding
{1,0,{pysm::j,pyym::i}},//饥 ji
{1,0,{pysm::t,pyym::uo}},//饦 tuo
{2,3609,{pysm::nop,pyym::nop}},//饧 tang
{1,0,{pysm::t,pyym::un}},//饨 tun
{1,0,{pysm::x,pyym::i}},//饩 xi
{1,0,{pysm::r,pyym::en}},//饪 ren
{1,0,{pysm::y,pyym::u}},//饫 yu
{1,0,{pysm::ch,pyym::i}},//饬 chi
{1,0,{pysm::f,pyym::an}},//饭 fan
{1,0,{pysm::y,pyym::in}},//饮 yin
{1,0,{pysm::j,pyym::ian}},//饯 jian
{1,0,{pysm::sh,pyym::i}},//饰 shi
{1,0,{pysm::b,pyym::ao}},//饱 bao
{1,0,{pysm::s,pyym::i}},//饲 si
{1,0,{pysm::d,pyym::uo}},//饳 duo
{1,0,{pysm::y,pyym::i}},//饴 yi
{1,0,{pysm::nop,pyym::er}},//饵 er
{1,0,{pysm::r,pyym::ao}},//饶 rao
{1,0,{pysm::x,pyym::iang}},//饷 xiang
{1,0,{pysm::h,pyym::e}},//饸 he
{2,3610,{pysm::nop,pyym::nop}},//饹 le
{1,0,{pysm::j,pyym::iao}},//饺 jiao
{1,0,{pysm::x,pyym::i}},//饻 xi
{1,0,{pysm::b,pyym::ing}},//饼 bing
{1,0,{pysm::b,pyym::o}},//饽 bo
{1,0,{pysm::d,pyym::ou}},//饾 dou
{1,0,{pysm::nop,pyym::e}},//饿 e
{1,0,{pysm::y,pyym::u}},//馀 yu
{1,0,{pysm::n,pyym::ei}},//馁 nei
{1,0,{pysm::j,pyym::un}},//馂 jun
{1,0,{pysm::g,pyym::uo}},//馃 guo
{1,0,{pysm::h,pyym::un}},//馄 hun
{1,0,{pysm::x,pyym::ian}},//馅 xian
{1,0,{pysm::g,pyym::uan}},//馆 guan
{2,3611,{pysm::nop,pyym::nop}},//馇 cha
{1,0,{pysm::k,pyym::ui}},//馈 kui
{1,0,{pysm::g,pyym::u}},//馉 gu
{1,0,{pysm::s,pyym::ou}},//馊 sou
{1,0,{pysm::ch,pyym::an}},//馋 chan
{1,0,{pysm::y,pyym::e}},//馌 ye
{1,0,{pysm::m,pyym::o}},//馍 mo
{1,0,{pysm::b,pyym::o}},//馎 bo
{1,0,{pysm::l,pyym::iu}},//馏 liu
{1,0,{pysm::x,pyym::iu}},//馐 xiu
{1,0,{pysm::j,pyym::in}},//馑 jin
{1,0,{pysm::m,pyym::an}},//馒 man
{1,0,{pysm::s,pyym::an}},//馓 san
{1,0,{pysm::zh,pyym::uan}},//馔 zhuan
{1,0,{pysm::n,pyym::ang}},//馕 nang
{1,0,{pysm::sh,pyym::ou}},//首 shou
{2,3612,{pysm::nop,pyym::nop}},//馗 kui
{2,3613,{pysm::nop,pyym::nop}},//馘 guo
{1,0,{pysm::x,pyym::iang}},//香 xiang
{1,0,{pysm::f,pyym::en}},//馚 fen
{1,0,{pysm::b,pyym::o}},//馛 bo
{1,0,{pysm::n,pyym::i}},//馜 ni
{1,0,{pysm::b,pyym::i}},//馝 bi
{2,3614,{pysm::nop,pyym::nop}},//馞 bo
{1,0,{pysm::t,pyym::u}},//馟 tu
{1,0,{pysm::h,pyym::an}},//馠 han
{1,0,{pysm::f,pyym::ei}},//馡 fei
{1,0,{pysm::j,pyym::ian}},//馢 jian
{1,0,{pysm::nop,pyym::an}},//馣 an
{1,0,{pysm::nop,pyym::ai}},//馤 ai
{2,3615,{pysm::nop,pyym::nop}},//馥 fu
{1,0,{pysm::x,pyym::ian}},//馦 xian
{2,3616,{pysm::nop,pyym::nop}},//馧 yun
{1,0,{pysm::x,pyym::in}},//馨 xin
{1,0,{pysm::f,pyym::en}},//馩 fen
{1,0,{pysm::p,pyym::in}},//馪 pin
{1,0,{pysm::x,pyym::in}},//馫 xin
{1,0,{pysm::m,pyym::a}},//馬 ma
{1,0,{pysm::y,pyym::u}},//馭 yu
{2,3617,{pysm::nop,pyym::nop}},//馮 feng
{2,3618,{pysm::nop,pyym::nop}},//馯 han
{1,0,{pysm::d,pyym::i}},//馰 di
{3,848,{pysm::nop,pyym::nop}},//馱 tuo
{2,3619,{pysm::nop,pyym::nop}},//馲 zhe
{1,0,{pysm::ch,pyym::i}},//馳 chi
{1,0,{pysm::x,pyym::un}},//馴 xun
{1,0,{pysm::zh,pyym::u}},//馵 zhu
{2,3620,{pysm::nop,pyym::nop}},//馶 zhi
{1,0,{pysm::p,pyym::ei}},//馷 pei
{2,3621,{pysm::nop,pyym::nop}},//馸 xin
{1,0,{pysm::r,pyym::i}},//馹 ri
{1,0,{pysm::s,pyym::a}},//馺 sa
{1,0,{pysm::y,pyym::un}},//馻 yun
{1,0,{pysm::w,pyym::en}},//馼 wen
{1,0,{pysm::zh,pyym::i}},//馽 zhi
{1,0,{pysm::d,pyym::an}},//馾 dan
{1,0,{pysm::l,pyym::v}},//馿 lü
{1,0,{pysm::y,pyym::ou}},//駀 you
{1,0,{pysm::b,pyym::o}},//駁 bo
{1,0,{pysm::b,pyym::ao}},//駂 bao
{2,3622,{pysm::nop,pyym::nop}},//駃 jue
{1,0,{pysm::t,pyym::uo}},//駄 tuo
{1,0,{pysm::y,pyym::i}},//駅 yi
{1,0,{pysm::q,pyym::u}},//駆 qu
{1,0,{pysm::w,pyym::en}},//駇 wen
{1,0,{pysm::q,pyym::u}},//駈 qu
{1,0,{pysm::j,pyym::iong}},//駉 jiong
{1,0,{pysm::p,pyym::o}},//駊 po
{1,0,{pysm::zh,pyym::ao}},//駋 zhao
{1,0,{pysm::y,pyym::uan}},//駌 yuan
{2,3623,{pysm::nop,pyym::nop}},//駍 pei
{1,0,{pysm::zh,pyym::ou}},//駎 zhou
{1,0,{pysm::j,pyym::u}},//駏 ju
{1,0,{pysm::zh,pyym::u}},//駐 zhu
{1,0,{pysm::n,pyym::u}},//駑 nu
{1,0,{pysm::j,pyym::u}},//駒 ju
{1,0,{pysm::p,pyym::i}},//駓 pi
{2,3624,{pysm::nop,pyym::nop}},//駔 zang
{1,0,{pysm::j,pyym::ia}},//駕 jia
{1,0,{pysm::l,pyym::ing}},//駖 ling
{1,0,{pysm::zh,pyym::en}},//駗 zhen
{3,849,{pysm::nop,pyym::nop}},//駘 tai
{1,0,{pysm::f,pyym::u}},//駙 fu
{1,0,{pysm::y,pyym::ang}},//駚 yang
{1,0,{pysm::sh,pyym::i}},//駛 shi
{1,0,{pysm::b,pyym::i}},//駜 bi
{1,0,{pysm::t,pyym::uo}},//駝 tuo
{1,0,{pysm::t,pyym::uo}},//駞 tuo
{1,0,{pysm::s,pyym::i}},//駟 si
{1,0,{pysm::l,pyym::iu}},//駠 liu
{1,0,{pysm::m,pyym::a}},//駡 ma
{1,0,{pysm::p,pyym::ian}},//駢 pian
{1,0,{pysm::t,pyym::ao}},//駣 tao
{1,0,{pysm::zh,pyym::i}},//駤 zhi
{1,0,{pysm::r,pyym::ong}},//駥 rong
{1,0,{pysm::t,pyym::eng}},//駦 teng
{1,0,{pysm::d,pyym::ong}},//駧 dong
{2,3625,{pysm::nop,pyym::nop}},//駨 xun
{1,0,{pysm::q,pyym::uan}},//駩 quan
{1,0,{pysm::sh,pyym::en}},//駪 shen
{1,0,{pysm::j,pyym::iong}},//駫 jiong
{1,0,{pysm::nop,pyym::er}},//駬 er
{1,0,{pysm::h,pyym::ai}},//駭 hai
{1,0,{pysm::b,pyym::o}},//駮 bo
{1,0,{pysm::zh,pyym::u}},//駯 zhu
{1,0,{pysm::y,pyym::in}},//駰 yin
{2,3626,{pysm::nop,pyym::nop}},//駱 luo
{1,0,{pysm::zh,pyym::ou}},//駲 zhou
{1,0,{pysm::d,pyym::an}},//駳 dan
{1,0,{pysm::h,pyym::ai}},//駴 hai
{1,0,{pysm::l,pyym::iu}},//駵 liu
{1,0,{pysm::j,pyym::u}},//駶 ju
{1,0,{pysm::s,pyym::ong}},//駷 song
{1,0,{pysm::q,pyym::in}},//駸 qin
{1,0,{pysm::m,pyym::ang}},//駹 mang
{2,3627,{pysm::nop,pyym::nop}},//駺 lang
{1,0,{pysm::h,pyym::an}},//駻 han
{1,0,{pysm::t,pyym::u}},//駼 tu
{1,0,{pysm::x,pyym::uan}},//駽 xuan
{1,0,{pysm::t,pyym::ui}},//駾 tui
{1,0,{pysm::j,pyym::un}},//駿 jun
{1,0,{pysm::nop,pyym::e}},//騀 e
{1,0,{pysm::ch,pyym::eng}},//騁 cheng
{1,0,{pysm::x,pyym::ing}},//騂 xing
{3,850,{pysm::nop,pyym::nop}},//騃 ai
{1,0,{pysm::l,pyym::u}},//騄 lu
{1,0,{pysm::zh,pyym::ui}},//騅 zhui
{2,3628,{pysm::nop,pyym::nop}},//騆 zhou
{1,0,{pysm::sh,pyym::e}},//騇 she
{1,0,{pysm::p,pyym::ian}},//騈 pian
{1,0,{pysm::k,pyym::un}},//騉 kun
{1,0,{pysm::t,pyym::ao}},//騊 tao
{1,0,{pysm::l,pyym::ai}},//騋 lai
{1,0,{pysm::z,pyym::ong}},//騌 zong
{1,0,{pysm::k,pyym::e}},//騍 ke
{2,3629,{pysm::nop,pyym::nop}},//騎 qi
{1,0,{pysm::q,pyym::i}},//騏 qi
{1,0,{pysm::y,pyym::an}},//騐 yan
{1,0,{pysm::f,pyym::ei}},//騑 fei
{1,0,{pysm::s,pyym::ao}},//騒 sao
{1,0,{pysm::y,pyym::an}},//験 yan
{1,0,{pysm::g,pyym::e}},//騔 ge
{1,0,{pysm::y,pyym::ao}},//騕 yao
{1,0,{pysm::w,pyym::u}},//騖 wu
{1,0,{pysm::p,pyym::ian}},//騗 pian
{1,0,{pysm::c,pyym::ong}},//騘 cong
{1,0,{pysm::p,pyym::ian}},//騙 pian
{1,0,{pysm::q,pyym::ian}},//騚 qian
{1,0,{pysm::f,pyym::ei}},//騛 fei
{1,0,{pysm::h,pyym::uang}},//騜 huang
{1,0,{pysm::q,pyym::ian}},//騝 qian
{1,0,{pysm::h,pyym::uo}},//騞 huo
{1,0,{pysm::y,pyym::u}},//騟 yu
{1,0,{pysm::t,pyym::i}},//騠 ti
{1,0,{pysm::q,pyym::uan}},//騡 quan
{1,0,{pysm::x,pyym::ia}},//騢 xia
{1,0,{pysm::z,pyym::ong}},//騣 zong
{2,3630,{pysm::nop,pyym::nop}},//騤 kui
{1,0,{pysm::r,pyym::ou}},//騥 rou
{1,0,{pysm::s,pyym::i}},//騦 si
{1,0,{pysm::g,pyym::ua}},//騧 gua
{1,0,{pysm::t,pyym::uo}},//騨 tuo
{2,3631,{pysm::nop,pyym::nop}},//騩 gui
{1,0,{pysm::s,pyym::ou}},//騪 sou
{2,3632,{pysm::nop,pyym::nop}},//騫 qian
{1,0,{pysm::ch,pyym::eng}},//騬 cheng
{1,0,{pysm::zh,pyym::i}},//騭 zhi
{1,0,{pysm::l,pyym::iu}},//騮 liu
{2,3633,{pysm::nop,pyym::nop}},//騯 peng
{1,0,{pysm::t,pyym::eng}},//騰 teng
{1,0,{pysm::x,pyym::i}},//騱 xi
{1,0,{pysm::c,pyym::ao}},//騲 cao
{1,0,{pysm::d,pyym::u}},//騳 du
{1,0,{pysm::y,pyym::an}},//騴 yan
{1,0,{pysm::y,pyym::uan}},//騵 yuan
{4,173,{pysm::nop,pyym::nop}},//騶 zou
{2,3634,{pysm::nop,pyym::nop}},//騷 sao
{1,0,{pysm::sh,pyym::an}},//騸 shan
{1,0,{pysm::q,pyym::i}},//騹 qi
{2,3635,{pysm::nop,pyym::nop}},//騺 zhi
{1,0,{pysm::sh,pyym::uang}},//騻 shuang
{1,0,{pysm::l,pyym::u}},//騼 lu
{1,0,{pysm::x,pyym::i}},//騽 xi
{1,0,{pysm::l,pyym::uo}},//騾 luo
{1,0,{pysm::zh,pyym::ang}},//騿 zhang
{2,3636,{pysm::nop,pyym::nop}},//驀 mo
{2,3637,{pysm::nop,pyym::nop}},//驁 ao
{1,0,{pysm::c,pyym::an}},//驂 can
{2,3638,{pysm::nop,pyym::nop}},//驃 biao
{1,0,{pysm::c,pyym::ong}},//驄 cong
{1,0,{pysm::q,pyym::u}},//驅 qu
{1,0,{pysm::b,pyym::i}},//驆 bi
{1,0,{pysm::zh,pyym::i}},//驇 zhi
{1,0,{pysm::y,pyym::u}},//驈 yu
{1,0,{pysm::x,pyym::u}},//驉 xu
{1,0,{pysm::h,pyym::ua}},//驊 hua
{1,0,{pysm::b,pyym::o}},//驋 bo
{1,0,{pysm::s,pyym::u}},//驌 su
{1,0,{pysm::x,pyym::iao}},//驍 xiao
{1,0,{pysm::l,pyym::in}},//驎 lin
{1,0,{pysm::zh,pyym::an}},//驏 zhan
{1,0,{pysm::d,pyym::un}},//驐 dun
{1,0,{pysm::l,pyym::iu}},//驑 liu
{1,0,{pysm::t,pyym::uo}},//驒 tuo
{1,0,{pysm::c,pyym::eng}},//驓 ceng
{1,0,{pysm::d,pyym::ian}},//驔 dian
{4,174,{pysm::nop,pyym::nop}},//驕 jiao
{1,0,{pysm::t,pyym::ie}},//驖 tie
{1,0,{pysm::y,pyym::an}},//驗 yan
{1,0,{pysm::l,pyym::uo}},//驘 luo
{1,0,{pysm::zh,pyym::an}},//驙 zhan
{1,0,{pysm::j,pyym::ing}},//驚 jing
{1,0,{pysm::y,pyym::i}},//驛 yi
{1,0,{pysm::y,pyym::e}},//驜 ye
{1,0,{pysm::t,pyym::uo}},//驝 tuo
{1,0,{pysm::p,pyym::in}},//驞 pin
{1,0,{pysm::zh,pyym::ou}},//驟 zhou
{1,0,{pysm::y,pyym::an}},//驠 yan
{2,3639,{pysm::nop,pyym::nop}},//驡 long
{1,0,{pysm::l,pyym::v}},//驢 lü
{1,0,{pysm::t,pyym::eng}},//驣 teng
{1,0,{pysm::x,pyym::iang}},//驤 xiang
{1,0,{pysm::j,pyym::i}},//驥 ji
{1,0,{pysm::sh,pyym::uang}},//驦 shuang
{1,0,{pysm::j,pyym::u}},//驧 ju
{1,0,{pysm::x,pyym::i}},//驨 xi
{1,0,{pysm::h,pyym::uan}},//驩 huan
{2,3640,{pysm::nop,pyym::nop}},//驪 li
{2,3641,{pysm::nop,pyym::nop}},//驫 biao
{1,0,{pysm::m,pyym::a}},//马 ma
{1,0,{pysm::y,pyym::u}},//驭 yu
{2,3642,{pysm::nop,pyym::nop}},//驮 tuo
{1,0,{pysm::x,pyym::un}},//驯 xun
{1,0,{pysm::ch,pyym::i}},//驰 chi
{1,0,{pysm::q,pyym::u}},//驱 qu
{1,0,{pysm::r,pyym::i}},//驲 ri
{1,0,{pysm::b,pyym::o}},//驳 bo
{1,0,{pysm::l,pyym::v}},//驴 lü
{1,0,{pysm::z,pyym::ang}},//驵 zang
{1,0,{pysm::sh,pyym::i}},//驶 shi
{1,0,{pysm::s,pyym::i}},//驷 si
{1,0,{pysm::f,pyym::u}},//驸 fu
{1,0,{pysm::j,pyym::u}},//驹 ju
{1,0,{pysm::z,pyym::ou}},//驺 zou
{1,0,{pysm::zh,pyym::u}},//驻 zhu
{1,0,{pysm::t,pyym::uo}},//驼 tuo
{1,0,{pysm::n,pyym::u}},//驽 nu
{1,0,{pysm::j,pyym::ia}},//驾 jia
{1,0,{pysm::y,pyym::i}},//驿 yi
{2,3643,{pysm::nop,pyym::nop}},//骀 dai
{1,0,{pysm::x,pyym::iao}},//骁 xiao
{1,0,{pysm::m,pyym::a}},//骂 ma
{1,0,{pysm::y,pyym::in}},//骃 yin
{1,0,{pysm::j,pyym::iao}},//骄 jiao
{1,0,{pysm::h,pyym::ua}},//骅 hua
{1,0,{pysm::l,pyym::uo}},//骆 luo
{1,0,{pysm::h,pyym::ai}},//骇 hai
{1,0,{pysm::p,pyym::ian}},//骈 pian
{1,0,{pysm::b,pyym::iao}},//骉 biao
{1,0,{pysm::l,pyym::i}},//骊 li
{1,0,{pysm::ch,pyym::eng}},//骋 cheng
{1,0,{pysm::y,pyym::an}},//验 yan
{1,0,{pysm::x,pyym::ing}},//骍 xing
{1,0,{pysm::q,pyym::in}},//骎 qin
{1,0,{pysm::j,pyym::un}},//骏 jun
{1,0,{pysm::q,pyym::i}},//骐 qi
{1,0,{pysm::q,pyym::i}},//骑 qi
{1,0,{pysm::k,pyym::e}},//骒 ke
{1,0,{pysm::zh,pyym::ui}},//骓 zhui
{1,0,{pysm::z,pyym::ong}},//骔 zong
{1,0,{pysm::s,pyym::u}},//骕 su
{1,0,{pysm::c,pyym::an}},//骖 can
{1,0,{pysm::p,pyym::ian}},//骗 pian
{1,0,{pysm::zh,pyym::i}},//骘 zhi
{1,0,{pysm::k,pyym::ui}},//骙 kui
{1,0,{pysm::s,pyym::ao}},//骚 sao
{1,0,{pysm::w,pyym::u}},//骛 wu
{1,0,{pysm::nop,pyym::ao}},//骜 ao
{1,0,{pysm::l,pyym::iu}},//骝 liu
{1,0,{pysm::q,pyym::ian}},//骞 qian
{1,0,{pysm::sh,pyym::an}},//骟 shan
{2,3644,{pysm::nop,pyym::nop}},//骠 biao
{1,0,{pysm::l,pyym::uo}},//骡 luo
{1,0,{pysm::c,pyym::ong}},//骢 cong
{1,0,{pysm::ch,pyym::an}},//骣 chan
{1,0,{pysm::zh,pyym::ou}},//骤 zhou
{1,0,{pysm::j,pyym::i}},//骥 ji
{1,0,{pysm::sh,pyym::uang}},//骦 shuang
{1,0,{pysm::x,pyym::iang}},//骧 xiang
{1,0,{pysm::g,pyym::u}},//骨 gu
{1,0,{pysm::w,pyym::ei}},//骩 wei
{1,0,{pysm::w,pyym::ei}},//骪 wei
{2,3645,{pysm::nop,pyym::nop}},//骫 wei
{1,0,{pysm::y,pyym::u}},//骬 yu
{1,0,{pysm::g,pyym::an}},//骭 gan
{1,0,{pysm::y,pyym::i}},//骮 yi
{2,3646,{pysm::nop,pyym::nop}},//骯 ang
{2,3647,{pysm::nop,pyym::nop}},//骰 tou
{3,851,{pysm::nop,pyym::nop}},//骱 jie
{1,0,{pysm::b,pyym::ao}},//骲 bao
{1,0,{pysm::b,pyym::ei}},//骳 bei
{2,3648,{pysm::nop,pyym::nop}},//骴 ci
{1,0,{pysm::t,pyym::i}},//骵 ti
{1,0,{pysm::d,pyym::i}},//骶 di
{1,0,{pysm::k,pyym::u}},//骷 ku
{2,3649,{pysm::nop,pyym::nop}},//骸 hai
{3,852,{pysm::nop,pyym::nop}},//骹 qiao
{1,0,{pysm::h,pyym::ou}},//骺 hou
{1,0,{pysm::k,pyym::ua}},//骻 kua
{1,0,{pysm::g,pyym::e}},//骼 ge
{1,0,{pysm::t,pyym::ui}},//骽 tui
{1,0,{pysm::g,pyym::eng}},//骾 geng
{1,0,{pysm::p,pyym::ian}},//骿 pian
{1,0,{pysm::b,pyym::i}},//髀 bi
{2,3650,{pysm::nop,pyym::nop}},//髁 ke
{2,3651,{pysm::nop,pyym::nop}},//髂 qia
{1,0,{pysm::y,pyym::u}},//髃 yu
{1,0,{pysm::s,pyym::ui}},//髄 sui
{1,0,{pysm::l,pyym::ou}},//髅 lou
{2,3652,{pysm::nop,pyym::nop}},//髆 bo
{1,0,{pysm::x,pyym::iao}},//髇 xiao
{2,3653,{pysm::nop,pyym::nop}},//髈 bang
{2,3654,{pysm::nop,pyym::nop}},//髉 bo
{2,3655,{pysm::nop,pyym::nop}},//髊 ci
{1,0,{pysm::k,pyym::uan}},//髋 kuan
{1,0,{pysm::b,pyym::in}},//髌 bin
{1,0,{pysm::m,pyym::o}},//髍 mo
{1,0,{pysm::l,pyym::iao}},//髎 liao
{1,0,{pysm::l,pyym::ou}},//髏 lou
{1,0,{pysm::x,pyym::iao}},//髐 xiao
{1,0,{pysm::d,pyym::u}},//髑 du
{1,0,{pysm::z,pyym::ang}},//髒 zang
{1,0,{pysm::s,pyym::ui}},//髓 sui
{1,0,{pysm::t,pyym::i}},//體 ti
{1,0,{pysm::b,pyym::in}},//髕 bin
{1,0,{pysm::k,pyym::uan}},//髖 kuan
{1,0,{pysm::l,pyym::u}},//髗 lu
{1,0,{pysm::g,pyym::ao}},//高 gao
{1,0,{pysm::g,pyym::ao}},//髙 gao
{1,0,{pysm::q,pyym::iao}},//髚 qiao
{1,0,{pysm::k,pyym::ao}},//髛 kao
{1,0,{pysm::q,pyym::iao}},//髜 qiao
{1,0,{pysm::l,pyym::ao}},//髝 lao
{1,0,{pysm::s,pyym::ao}},//髞 sao
{3,853,{pysm::nop,pyym::nop}},//髟 biao
{1,0,{pysm::k,pyym::un}},//髠 kun
{1,0,{pysm::k,pyym::un}},//髡 kun
{1,0,{pysm::d,pyym::i}},//髢 di
{1,0,{pysm::f,pyym::ang}},//髣 fang
{1,0,{pysm::x,pyym::iu}},//髤 xiu
{1,0,{pysm::r,pyym::an}},//髥 ran
{1,0,{pysm::m,pyym::ao}},//髦 mao
{1,0,{pysm::d,pyym::an}},//髧 dan
{1,0,{pysm::k,pyym::un}},//髨 kun
{1,0,{pysm::b,pyym::in}},//髩 bin
{1,0,{pysm::f,pyym::a}},//髪 fa
{1,0,{pysm::t,pyym::iao}},//髫 tiao
{1,0,{pysm::p,pyym::i}},//髬 pi
{1,0,{pysm::z,pyym::i}},//髭 zi
{1,0,{pysm::f,pyym::a}},//髮 fa
{1,0,{pysm::r,pyym::an}},//髯 ran
{1,0,{pysm::t,pyym::i}},//髰 ti
{1,0,{pysm::b,pyym::ao}},//髱 bao
{1,0,{pysm::b,pyym::i}},//髲 bi
{3,854,{pysm::nop,pyym::nop}},//髳 mao
{2,3656,{pysm::nop,pyym::nop}},//髴 fu
{1,0,{pysm::nop,pyym::er}},//髵 er
{2,3657,{pysm::nop,pyym::nop}},//髶 rong
{1,0,{pysm::q,pyym::u}},//髷 qu
{1,0,{pysm::g,pyym::ong}},//髸 gong
{1,0,{pysm::x,pyym::iu}},//髹 xiu
{2,3658,{pysm::nop,pyym::nop}},//髺 kuo
{2,3659,{pysm::nop,pyym::nop}},//髻 ji
{1,0,{pysm::p,pyym::eng}},//髼 peng
{1,0,{pysm::zh,pyym::ua}},//髽 zhua
{1,0,{pysm::sh,pyym::ao}},//髾 shao
{1,0,{pysm::s,pyym::uo}},//髿 suo
{1,0,{pysm::t,pyym::i}},//鬀 ti
{1,0,{pysm::l,pyym::i}},//鬁 li
{1,0,{pysm::b,pyym::in}},//鬂 bin
{1,0,{pysm::z,pyym::ong}},//鬃 zong
{2,3660,{pysm::nop,pyym::nop}},//鬄 di
{1,0,{pysm::p,pyym::eng}},//鬅 peng
{1,0,{pysm::s,pyym::ong}},//鬆 song
{1,0,{pysm::zh,pyym::eng}},//鬇 zheng
{1,0,{pysm::q,pyym::uan}},//鬈 quan
{1,0,{pysm::z,pyym::ong}},//鬉 zong
{1,0,{pysm::sh,pyym::un}},//鬊 shun
{1,0,{pysm::j,pyym::ian}},//鬋 jian
{3,855,{pysm::nop,pyym::nop}},//鬌 tuo
{1,0,{pysm::h,pyym::u}},//鬍 hu
{1,0,{pysm::l,pyym::a}},//鬎 la
{1,0,{pysm::j,pyym::iu}},//鬏 jiu
{1,0,{pysm::q,pyym::i}},//鬐 qi
{1,0,{pysm::l,pyym::ian}},//鬑 lian
{1,0,{pysm::zh,pyym::en}},//鬒 zhen
{1,0,{pysm::b,pyym::in}},//鬓 bin
{1,0,{pysm::p,pyym::eng}},//鬔 peng
{1,0,{pysm::m,pyym::a}},//鬕 ma
{1,0,{pysm::s,pyym::an}},//鬖 san
{1,0,{pysm::m,pyym::an}},//鬗 man
{1,0,{pysm::m,pyym::an}},//鬘 man
{1,0,{pysm::s,pyym::eng}},//鬙 seng
{1,0,{pysm::x,pyym::u}},//鬚 xu
{1,0,{pysm::l,pyym::ie}},//鬛 lie
{1,0,{pysm::q,pyym::ian}},//鬜 qian
{1,0,{pysm::q,pyym::ian}},//鬝 qian
{1,0,{pysm::n,pyym::ang}},//鬞 nang
{1,0,{pysm::h,pyym::uan}},//鬟 huan
{2,3661,{pysm::nop,pyym::nop}},//鬠 kuo
{1,0,{pysm::n,pyym::ing}},//鬡 ning
{1,0,{pysm::b,pyym::in}},//鬢 bin
{1,0,{pysm::l,pyym::ie}},//鬣 lie
{2,3662,{pysm::nop,pyym::nop}},//鬤 rang
{1,0,{pysm::d,pyym::ou}},//鬥 dou
{1,0,{pysm::d,pyym::ou}},//鬦 dou
{1,0,{pysm::n,pyym::ao}},//鬧 nao
{2,3663,{pysm::nop,pyym::nop}},//鬨 hong
{2,3664,{pysm::nop,pyym::nop}},//鬩 xi
{1,0,{pysm::d,pyym::ou}},//鬪 dou
{1,0,{pysm::h,pyym::an}},//鬫 han
{1,0,{pysm::d,pyym::ou}},//鬬 dou
{1,0,{pysm::d,pyym::ou}},//鬭 dou
{1,0,{pysm::j,pyym::iu}},//鬮 jiu
{1,0,{pysm::ch,pyym::ang}},//鬯 chang
{1,0,{pysm::y,pyym::u}},//鬰 yu
{1,0,{pysm::y,pyym::u}},//鬱 yu
{3,856,{pysm::nop,pyym::nop}},//鬲 ge
{1,0,{pysm::y,pyym::an}},//鬳 yan
{2,3665,{pysm::nop,pyym::nop}},//鬴 fu
{2,3666,{pysm::nop,pyym::nop}},//鬵 qin
{1,0,{pysm::g,pyym::ui}},//鬶 gui
{2,3667,{pysm::nop,pyym::nop}},//鬷 zong
{1,0,{pysm::l,pyym::iu}},//鬸 liu
{2,3668,{pysm::nop,pyym::nop}},//鬹 gui
{1,0,{pysm::sh,pyym::ang}},//鬺 shang
{3,857,{pysm::nop,pyym::nop}},//鬻 yu
{1,0,{pysm::g,pyym::ui}},//鬼 gui
{1,0,{pysm::m,pyym::ei}},//鬽 mei
{2,3669,{pysm::nop,pyym::nop}},//鬾 ji
{1,0,{pysm::q,pyym::i}},//鬿 qi
{1,0,{pysm::g,pyym::a}},//魀 ga
{2,3670,{pysm::nop,pyym::nop}},//魁 kui
{1,0,{pysm::h,pyym::un}},//魂 hun
{1,0,{pysm::b,pyym::a}},//魃 ba
{3,858,{pysm::nop,pyym::nop}},//魄 po
{1,0,{pysm::m,pyym::ei}},//魅 mei
{1,0,{pysm::x,pyym::u}},//魆 xu
{1,0,{pysm::y,pyym::an}},//魇 yan
{1,0,{pysm::x,pyym::iao}},//魈 xiao
{1,0,{pysm::l,pyym::iang}},//魉 liang
{1,0,{pysm::y,pyym::u}},//魊 yu
{2,3671,{pysm::nop,pyym::nop}},//魋 tui
{1,0,{pysm::q,pyym::i}},//魌 qi
{1,0,{pysm::w,pyym::ang}},//魍 wang
{1,0,{pysm::l,pyym::iang}},//魎 liang
{1,0,{pysm::w,pyym::ei}},//魏 wei
{1,0,{pysm::g,pyym::an}},//魐 gan
{1,0,{pysm::ch,pyym::i}},//魑 chi
{1,0,{pysm::p,pyym::iao}},//魒 piao
{1,0,{pysm::b,pyym::i}},//魓 bi
{1,0,{pysm::m,pyym::o}},//魔 mo
{1,0,{pysm::j,pyym::i}},//魕 ji
{1,0,{pysm::x,pyym::u}},//魖 xu
{1,0,{pysm::ch,pyym::ou}},//魗 chou
{1,0,{pysm::y,pyym::an}},//魘 yan
{1,0,{pysm::zh,pyym::an}},//魙 zhan
{1,0,{pysm::y,pyym::u}},//魚 yu
{1,0,{pysm::d,pyym::ao}},//魛 dao
{1,0,{pysm::r,pyym::en}},//魜 ren
{2,3672,{pysm::nop,pyym::nop}},//魝 jie
{1,0,{pysm::b,pyym::a}},//魞 ba
{2,3673,{pysm::nop,pyym::nop}},//魟 hong
{1,0,{pysm::t,pyym::uo}},//魠 tuo
{2,3674,{pysm::nop,pyym::nop}},//魡 diao
{1,0,{pysm::j,pyym::i}},//魢 ji
{2,3675,{pysm::nop,pyym::nop}},//魣 xu
{2,3676,{pysm::nop,pyym::nop}},//魤 e
{3,859,{pysm::nop,pyym::nop}},//魥 e
{2,3677,{pysm::nop,pyym::nop}},//魦 sha
{1,0,{pysm::h,pyym::ang}},//魧 hang
{1,0,{pysm::t,pyym::un}},//魨 tun
{1,0,{pysm::m,pyym::o}},//魩 mo
{1,0,{pysm::j,pyym::ie}},//魪 jie
{1,0,{pysm::sh,pyym::en}},//魫 shen
{1,0,{pysm::b,pyym::an}},//魬 ban
{2,3678,{pysm::nop,pyym::nop}},//魭 yuan
{2,3679,{pysm::nop,pyym::nop}},//魮 pi
{2,3680,{pysm::nop,pyym::nop}},//魯 lu
{1,0,{pysm::w,pyym::en}},//魰 wen
{1,0,{pysm::h,pyym::u}},//魱 hu
{1,0,{pysm::l,pyym::u}},//魲 lu
{2,3681,{pysm::nop,pyym::nop}},//魳 za
{1,0,{pysm::f,pyym::ang}},//魴 fang
{1,0,{pysm::f,pyym::en}},//魵 fen
{1,0,{pysm::n,pyym::a}},//魶 na
{1,0,{pysm::y,pyym::ou}},//魷 you
{1,0,{pysm::p,pyym::ian}},//魸 pian
{1,0,{pysm::m,pyym::o}},//魹 mo
{2,3682,{pysm::nop,pyym::nop}},//魺 he
{1,0,{pysm::x,pyym::ia}},//魻 xia
{2,3683,{pysm::nop,pyym::nop}},//魼 qu
{1,0,{pysm::h,pyym::an}},//魽 han
{1,0,{pysm::p,pyym::i}},//魾 pi
{2,3684,{pysm::nop,pyym::nop}},//魿 ling
{1,0,{pysm::t,pyym::uo}},//鮀 tuo
{2,3685,{pysm::nop,pyym::nop}},//鮁 bo
{1,0,{pysm::q,pyym::iu}},//鮂 qiu
{1,0,{pysm::p,pyym::ing}},//鮃 ping
{1,0,{pysm::f,pyym::u}},//鮄 fu
{1,0,{pysm::b,pyym::i}},//鮅 bi
{2,3686,{pysm::nop,pyym::nop}},//鮆 ci
{1,0,{pysm::w,pyym::ei}},//鮇 wei
{3,860,{pysm::nop,pyym::nop}},//鮈 ju
{1,0,{pysm::d,pyym::iao}},//鮉 diao
{2,3687,{pysm::nop,pyym::nop}},//鮊 ba
{2,3688,{pysm::nop,pyym::nop}},//鮋 you
{1,0,{pysm::g,pyym::un}},//鮌 gun
{2,3689,{pysm::nop,pyym::nop}},//鮍 pi
{1,0,{pysm::n,pyym::ian}},//鮎 nian
{2,3690,{pysm::nop,pyym::nop}},//鮏 xing
{1,0,{pysm::t,pyym::ai}},//鮐 tai
{2,3691,{pysm::nop,pyym::nop}},//鮑 bao
{1,0,{pysm::f,pyym::u}},//鮒 fu
{1,0,{pysm::zh,pyym::a}},//鮓 zha
{1,0,{pysm::j,pyym::u}},//鮔 ju
{1,0,{pysm::g,pyym::u}},//鮕 gu
{1,0,{pysm::sh,pyym::i}},//鮖 shi
{1,0,{pysm::d,pyym::ong}},//鮗 dong
{1,0,{pysm::d,pyym::ai}},//鮘 dai
{1,0,{pysm::t,pyym::a}},//鮙 ta
{2,3692,{pysm::nop,pyym::nop}},//鮚 jie
{1,0,{pysm::sh,pyym::u}},//鮛 shu
{1,0,{pysm::h,pyym::ou}},//鮜 hou
{2,3693,{pysm::nop,pyym::nop}},//鮝 xiang
{1,0,{pysm::nop,pyym::er}},//鮞 er
{1,0,{pysm::nop,pyym::an}},//鮟 an
{1,0,{pysm::w,pyym::ei}},//鮠 wei
{1,0,{pysm::zh,pyym::ao}},//鮡 zhao
{1,0,{pysm::zh,pyym::u}},//鮢 zhu
{1,0,{pysm::y,pyym::in}},//鮣 yin
{1,0,{pysm::l,pyym::ie}},//鮤 lie
{2,3694,{pysm::nop,pyym::nop}},//鮥 luo
{1,0,{pysm::t,pyym::ong}},//鮦 tong
{2,3695,{pysm::nop,pyym::nop}},//鮧 ti
{2,3696,{pysm::nop,pyym::nop}},//鮨 yi
{2,3697,{pysm::nop,pyym::nop}},//鮩 bing
{1,0,{pysm::w,pyym::ei}},//鮪 wei
{1,0,{pysm::j,pyym::iao}},//鮫 jiao
{1,0,{pysm::k,pyym::u}},//鮬 ku
{5,52,{pysm::nop,pyym::nop}},//鮭 gui
{1,0,{pysm::x,pyym::ian}},//鮮 xian
{1,0,{pysm::g,pyym::e}},//鮯 ge
{1,0,{pysm::h,pyym::ui}},//鮰 hui
{1,0,{pysm::l,pyym::ao}},//鮱 lao
{1,0,{pysm::f,pyym::u}},//鮲 fu
{1,0,{pysm::k,pyym::ao}},//鮳 kao
{1,0,{pysm::x,pyym::iu}},//鮴 xiu
{1,0,{pysm::d,pyym::uo}},//鮵 duo
{1,0,{pysm::j,pyym::un}},//鮶 jun
{1,0,{pysm::t,pyym::i}},//鮷 ti
{1,0,{pysm::m,pyym::ian}},//鮸 mian
{1,0,{pysm::sh,pyym::ao}},//鮹 shao
{1,0,{pysm::zh,pyym::a}},//鮺 zha
{1,0,{pysm::s,pyym::uo}},//鮻 suo
{1,0,{pysm::q,pyym::in}},//鮼 qin
{1,0,{pysm::y,pyym::u}},//鮽 yu
{1,0,{pysm::n,pyym::ei}},//鮾 nei
{1,0,{pysm::zh,pyym::e}},//鮿 zhe
{1,0,{pysm::g,pyym::un}},//鯀 gun
{1,0,{pysm::g,pyym::eng}},//鯁 geng
{1,0,{pysm::s,pyym::u}},//鯂 su
{1,0,{pysm::w,pyym::u}},//鯃 wu
{1,0,{pysm::q,pyym::iu}},//鯄 qiu
{2,3698,{pysm::nop,pyym::nop}},//鯅 shan
{2,3699,{pysm::nop,pyym::nop}},//鯆 pu
{1,0,{pysm::h,pyym::uan}},//鯇 huan
{3,861,{pysm::nop,pyym::nop}},//鯈 tiao
{1,0,{pysm::l,pyym::i}},//鯉 li
{1,0,{pysm::sh,pyym::a}},//鯊 sha
{1,0,{pysm::sh,pyym::a}},//鯋 sha
{1,0,{pysm::k,pyym::ao}},//鯌 kao
{1,0,{pysm::m,pyym::eng}},//鯍 meng
{1,0,{pysm::ch,pyym::eng}},//鯎 cheng
{1,0,{pysm::l,pyym::i}},//鯏 li
{1,0,{pysm::z,pyym::ou}},//鯐 zou
{1,0,{pysm::x,pyym::i}},//鯑 xi
{1,0,{pysm::y,pyym::ong}},//鯒 yong
{1,0,{pysm::sh,pyym::en}},//鯓 shen
{1,0,{pysm::z,pyym::i}},//鯔 zi
{1,0,{pysm::q,pyym::i}},//鯕 qi
{2,3700,{pysm::nop,pyym::nop}},//鯖 zheng
{1,0,{pysm::x,pyym::iang}},//鯗 xiang
{1,0,{pysm::n,pyym::ei}},//鯘 nei
{1,0,{pysm::ch,pyym::un}},//鯙 chun
{1,0,{pysm::j,pyym::i}},//鯚 ji
{1,0,{pysm::d,pyym::iao}},//鯛 diao
{1,0,{pysm::q,pyym::ie}},//鯜 qie
{1,0,{pysm::g,pyym::u}},//鯝 gu
{1,0,{pysm::zh,pyym::ou}},//鯞 zhou
{1,0,{pysm::d,pyym::ong}},//鯟 dong
{1,0,{pysm::l,pyym::ai}},//鯠 lai
{1,0,{pysm::f,pyym::ei}},//鯡 fei
{1,0,{pysm::n,pyym::i}},//鯢 ni
{1,0,{pysm::y,pyym::i}},//鯣 yi
{1,0,{pysm::k,pyym::un}},//鯤 kun
{1,0,{pysm::l,pyym::u}},//鯥 lu
{2,3701,{pysm::nop,pyym::nop}},//鯦 jiu
{1,0,{pysm::ch,pyym::ang}},//鯧 chang
{2,3702,{pysm::nop,pyym::nop}},//鯨 jing
{1,0,{pysm::l,pyym::un}},//鯩 lun
{1,0,{pysm::l,pyym::ing}},//鯪 ling
{1,0,{pysm::z,pyym::ou}},//鯫 zou
{1,0,{pysm::l,pyym::i}},//鯬 li
{1,0,{pysm::m,pyym::eng}},//鯭 meng
{1,0,{pysm::z,pyym::ong}},//鯮 zong
{1,0,{pysm::zh,pyym::i}},//鯯 zhi
{1,0,{pysm::n,pyym::ian}},//鯰 nian
{1,0,{pysm::h,pyym::u}},//鯱 hu
{1,0,{pysm::y,pyym::u}},//鯲 yu
{1,0,{pysm::d,pyym::i}},//鯳 di
{1,0,{pysm::sh,pyym::i}},//鯴 shi
{1,0,{pysm::sh,pyym::en}},//鯵 shen
{1,0,{pysm::h,pyym::uan}},//鯶 huan
{1,0,{pysm::t,pyym::i}},//鯷 ti
{1,0,{pysm::h,pyym::ou}},//鯸 hou
{1,0,{pysm::x,pyym::ing}},//鯹 xing
{1,0,{pysm::zh,pyym::u}},//鯺 zhu
{1,0,{pysm::l,pyym::a}},//鯻 la
{1,0,{pysm::z,pyym::ong}},//鯼 zong
{2,3703,{pysm::nop,pyym::nop}},//鯽 zei
{1,0,{pysm::b,pyym::ian}},//鯾 bian
{1,0,{pysm::b,pyym::ian}},//鯿 bian
{1,0,{pysm::h,pyym::uan}},//鰀 huan
{1,0,{pysm::q,pyym::uan}},//鰁 quan
{2,3704,{pysm::nop,pyym::nop}},//鰂 zei
{1,0,{pysm::w,pyym::ei}},//鰃 wei
{1,0,{pysm::w,pyym::ei}},//鰄 wei
{1,0,{pysm::y,pyym::u}},//鰅 yu
{1,0,{pysm::ch,pyym::un}},//鰆 chun
{1,0,{pysm::r,pyym::ou}},//鰇 rou
{3,862,{pysm::nop,pyym::nop}},//鰈 die
{1,0,{pysm::h,pyym::uang}},//鰉 huang
{1,0,{pysm::l,pyym::ian}},//鰊 lian
{1,0,{pysm::y,pyym::an}},//鰋 yan
{1,0,{pysm::q,pyym::iu}},//鰌 qiu
{1,0,{pysm::q,pyym::iu}},//鰍 qiu
{1,0,{pysm::j,pyym::ian}},//鰎 jian
{1,0,{pysm::b,pyym::i}},//鰏 bi
{1,0,{pysm::nop,pyym::e}},//鰐 e
{1,0,{pysm::y,pyym::ang}},//鰑 yang
{1,0,{pysm::f,pyym::u}},//鰒 fu
{2,3705,{pysm::nop,pyym::nop}},//鰓 sai
{3,863,{pysm::nop,pyym::nop}},//鰔 gan
{1,0,{pysm::x,pyym::ia}},//鰕 xia
{2,3706,{pysm::nop,pyym::nop}},//鰖 tuo
{1,0,{pysm::h,pyym::u}},//鰗 hu
{1,0,{pysm::sh,pyym::i}},//鰘 shi
{1,0,{pysm::r,pyym::uo}},//鰙 ruo
{1,0,{pysm::x,pyym::uan}},//鰚 xuan
{1,0,{pysm::w,pyym::en}},//鰛 wen
{2,3707,{pysm::nop,pyym::nop}},//鰜 qian
{1,0,{pysm::h,pyym::ao}},//鰝 hao
{1,0,{pysm::w,pyym::u}},//鰞 wu
{2,3708,{pysm::nop,pyym::nop}},//鰟 fang
{1,0,{pysm::s,pyym::ao}},//鰠 sao
{1,0,{pysm::l,pyym::iu}},//鰡 liu
{1,0,{pysm::m,pyym::a}},//鰢 ma
{1,0,{pysm::sh,pyym::i}},//鰣 shi
{1,0,{pysm::sh,pyym::i}},//鰤 shi
{3,864,{pysm::nop,pyym::nop}},//鰥 guan
{1,0,{pysm::z,pyym::i}},//鰦 zi
{1,0,{pysm::t,pyym::eng}},//鰧 teng
{2,3709,{pysm::nop,pyym::nop}},//鰨 ta
{1,0,{pysm::y,pyym::ao}},//鰩 yao
{2,3710,{pysm::nop,pyym::nop}},//鰪 e
{1,0,{pysm::y,pyym::ong}},//鰫 yong
{1,0,{pysm::q,pyym::ian}},//鰬 qian
{1,0,{pysm::q,pyym::i}},//鰭 qi
{1,0,{pysm::w,pyym::en}},//鰮 wen
{1,0,{pysm::r,pyym::uo}},//鰯 ruo
{1,0,{pysm::sh,pyym::en}},//鰰 shen
{1,0,{pysm::l,pyym::ian}},//鰱 lian
{1,0,{pysm::nop,pyym::ao}},//鰲 ao
{1,0,{pysm::l,pyym::e}},//鰳 le
{1,0,{pysm::h,pyym::ui}},//鰴 hui
{1,0,{pysm::m,pyym::in}},//鰵 min
{1,0,{pysm::j,pyym::i}},//鰶 ji
{1,0,{pysm::t,pyym::iao}},//鰷 tiao
{1,0,{pysm::q,pyym::u}},//鰸 qu
{1,0,{pysm::j,pyym::ian}},//鰹 jian
{3,865,{pysm::nop,pyym::nop}},//鰺 shen
{1,0,{pysm::m,pyym::an}},//鰻 man
{1,0,{pysm::x,pyym::i}},//鰼 xi
{1,0,{pysm::q,pyym::iu}},//鰽 qiu
{1,0,{pysm::b,pyym::iao}},//鰾 biao
{1,0,{pysm::j,pyym::i}},//鰿 ji
{1,0,{pysm::j,pyym::i}},//鱀 ji
{1,0,{pysm::zh,pyym::u}},//鱁 zhu
{1,0,{pysm::j,pyym::iang}},//鱂 jiang
{2,3711,{pysm::nop,pyym::nop}},//鱃 xiu
{3,866,{pysm::nop,pyym::nop}},//鱄 zhuan
{1,0,{pysm::y,pyym::ong}},//鱅 yong
{1,0,{pysm::zh,pyym::ang}},//鱆 zhang
{1,0,{pysm::k,pyym::ang}},//鱇 kang
{1,0,{pysm::x,pyym::ue}},//鱈 xue
{1,0,{pysm::b,pyym::ie}},//鱉 bie
{1,0,{pysm::y,pyym::u}},//鱊 yu
{1,0,{pysm::q,pyym::u}},//鱋 qu
{1,0,{pysm::x,pyym::iang}},//鱌 xiang
{1,0,{pysm::b,pyym::o}},//鱍 bo
{1,0,{pysm::j,pyym::iao}},//鱎 jiao
{1,0,{pysm::x,pyym::un}},//鱏 xun
{1,0,{pysm::s,pyym::u}},//鱐 su
{1,0,{pysm::h,pyym::uang}},//鱑 huang
{1,0,{pysm::z,pyym::un}},//鱒 zun
{2,3712,{pysm::nop,pyym::nop}},//鱓 shan
{1,0,{pysm::sh,pyym::an}},//鱔 shan
{1,0,{pysm::f,pyym::an}},//鱕 fan
{2,3713,{pysm::nop,pyym::nop}},//鱖 gui
{1,0,{pysm::l,pyym::in}},//鱗 lin
{1,0,{pysm::x,pyym::un}},//鱘 xun
{1,0,{pysm::m,pyym::iao}},//鱙 miao
{1,0,{pysm::x,pyym::i}},//鱚 xi
{1,0,{pysm::z,pyym::eng}},//鱛 zeng
{1,0,{pysm::x,pyym::iang}},//鱜 xiang
{1,0,{pysm::f,pyym::en}},//鱝 fen
{1,0,{pysm::g,pyym::uan}},//鱞 guan
{1,0,{pysm::h,pyym::ou}},//鱟 hou
{1,0,{pysm::k,pyym::uai}},//鱠 kuai
{1,0,{pysm::z,pyym::ei}},//鱡 zei
{1,0,{pysm::s,pyym::ao}},//鱢 sao
{2,3714,{pysm::nop,pyym::nop}},//鱣 zhan
{1,0,{pysm::g,pyym::an}},//鱤 gan
{1,0,{pysm::g,pyym::ui}},//鱥 gui
{3,867,{pysm::nop,pyym::nop}},//鱦 ying
{1,0,{pysm::l,pyym::i}},//鱧 li
{1,0,{pysm::ch,pyym::ang}},//鱨 chang
{1,0,{pysm::l,pyym::ei}},//鱩 lei
{1,0,{pysm::sh,pyym::u}},//鱪 shu
{1,0,{pysm::nop,pyym::ai}},//鱫 ai
{1,0,{pysm::r,pyym::u}},//鱬 ru
{1,0,{pysm::j,pyym::i}},//鱭 ji
{2,3715,{pysm::nop,pyym::nop}},//鱮 xu
{1,0,{pysm::h,pyym::u}},//鱯 hu
{1,0,{pysm::sh,pyym::u}},//鱰 shu
{1,0,{pysm::l,pyym::i}},//鱱 li
{2,3716,{pysm::nop,pyym::nop}},//鱲 lie
{3,868,{pysm::nop,pyym::nop}},//鱳 li
{1,0,{pysm::m,pyym::ie}},//鱴 mie
{1,0,{pysm::zh,pyym::en}},//鱵 zhen
{1,0,{pysm::x,pyym::iang}},//鱶 xiang
{1,0,{pysm::nop,pyym::e}},//鱷 e
{1,0,{pysm::l,pyym::u}},//鱸 lu
{1,0,{pysm::g,pyym::uan}},//鱹 guan
{1,0,{pysm::l,pyym::i}},//鱺 li
{1,0,{pysm::x,pyym::ian}},//鱻 xian
{1,0,{pysm::y,pyym::u}},//鱼 yu
{1,0,{pysm::d,pyym::ao}},//鱽 dao
{1,0,{pysm::j,pyym::i}},//鱾 ji
{1,0,{pysm::y,pyym::ou}},//鱿 you
{1,0,{pysm::t,pyym::un}},//鲀 tun
{1,0,{pysm::l,pyym::u}},//鲁 lu
{1,0,{pysm::f,pyym::ang}},//鲂 fang
{1,0,{pysm::b,pyym::a}},//鲃 ba
{1,0,{pysm::h,pyym::e}},//鲄 he
{2,3717,{pysm::nop,pyym::nop}},//鲅 ba
{1,0,{pysm::p,pyym::ing}},//鲆 ping
{1,0,{pysm::n,pyym::ian}},//鲇 nian
{1,0,{pysm::l,pyym::u}},//鲈 lu
{1,0,{pysm::y,pyym::ou}},//鲉 you
{1,0,{pysm::zh,pyym::a}},//鲊 zha
{1,0,{pysm::f,pyym::u}},//鲋 fu
{2,3718,{pysm::nop,pyym::nop}},//鲌 ba
{1,0,{pysm::b,pyym::ao}},//鲍 bao
{1,0,{pysm::h,pyym::ou}},//鲎 hou
{1,0,{pysm::p,pyym::i}},//鲏 pi
{1,0,{pysm::t,pyym::ai}},//鲐 tai
{2,3719,{pysm::nop,pyym::nop}},//鲑 gui
{1,0,{pysm::j,pyym::ie}},//鲒 jie
{1,0,{pysm::k,pyym::ao}},//鲓 kao
{1,0,{pysm::w,pyym::ei}},//鲔 wei
{1,0,{pysm::nop,pyym::er}},//鲕 er
{1,0,{pysm::t,pyym::ong}},//鲖 tong
{1,0,{pysm::z,pyym::ei}},//鲗 zei
{1,0,{pysm::h,pyym::ou}},//鲘 hou
{1,0,{pysm::k,pyym::uai}},//鲙 kuai
{1,0,{pysm::j,pyym::i}},//鲚 ji
{1,0,{pysm::j,pyym::iao}},//鲛 jiao
{1,0,{pysm::x,pyym::ian}},//鲜 xian
{1,0,{pysm::zh,pyym::a}},//鲝 zha
{1,0,{pysm::x,pyym::iang}},//鲞 xiang
{1,0,{pysm::x,pyym::un}},//鲟 xun
{1,0,{pysm::g,pyym::eng}},//鲠 geng
{1,0,{pysm::l,pyym::i}},//鲡 li
{1,0,{pysm::l,pyym::ian}},//鲢 lian
{1,0,{pysm::j,pyym::ian}},//鲣 jian
{1,0,{pysm::l,pyym::i}},//鲤 li
{1,0,{pysm::sh,pyym::i}},//鲥 shi
{1,0,{pysm::t,pyym::iao}},//鲦 tiao
{1,0,{pysm::g,pyym::un}},//鲧 gun
{1,0,{pysm::sh,pyym::a}},//鲨 sha
{1,0,{pysm::h,pyym::uan}},//鲩 huan
{1,0,{pysm::j,pyym::un}},//鲪 jun
{1,0,{pysm::j,pyym::i}},//鲫 ji
{1,0,{pysm::y,pyym::ong}},//鲬 yong
{2,3720,{pysm::nop,pyym::nop}},//鲭 qing
{1,0,{pysm::l,pyym::ing}},//鲮 ling
{1,0,{pysm::q,pyym::i}},//鲯 qi
{1,0,{pysm::z,pyym::ou}},//鲰 zou
{1,0,{pysm::f,pyym::ei}},//鲱 fei
{1,0,{pysm::k,pyym::un}},//鲲 kun
{1,0,{pysm::ch,pyym::ang}},//鲳 chang
{1,0,{pysm::g,pyym::u}},//鲴 gu
{1,0,{pysm::n,pyym::i}},//鲵 ni
{1,0,{pysm::n,pyym::ian}},//鲶 nian
{1,0,{pysm::d,pyym::iao}},//鲷 diao
{1,0,{pysm::j,pyym::ing}},//鲸 jing
{1,0,{pysm::sh,pyym::en}},//鲹 shen
{1,0,{pysm::sh,pyym::i}},//鲺 shi
{1,0,{pysm::z,pyym::i}},//鲻 zi
{1,0,{pysm::f,pyym::en}},//鲼 fen
{1,0,{pysm::d,pyym::ie}},//鲽 die
{1,0,{pysm::b,pyym::i}},//鲾 bi
{1,0,{pysm::ch,pyym::ang}},//鲿 chang
{1,0,{pysm::t,pyym::i}},//鳀 ti
{1,0,{pysm::w,pyym::en}},//鳁 wen
{1,0,{pysm::w,pyym::ei}},//鳂 wei
{1,0,{pysm::s,pyym::ai}},//鳃 sai
{1,0,{pysm::nop,pyym::e}},//鳄 e
{1,0,{pysm::q,pyym::iu}},//鳅 qiu
{1,0,{pysm::f,pyym::u}},//鳆 fu
{1,0,{pysm::h,pyym::uang}},//鳇 huang
{1,0,{pysm::q,pyym::uan}},//鳈 quan
{1,0,{pysm::j,pyym::iang}},//鳉 jiang
{1,0,{pysm::b,pyym::ian}},//鳊 bian
{1,0,{pysm::s,pyym::ao}},//鳋 sao
{1,0,{pysm::nop,pyym::ao}},//鳌 ao
{1,0,{pysm::q,pyym::i}},//鳍 qi
{1,0,{pysm::t,pyym::a}},//鳎 ta
{1,0,{pysm::g,pyym::uan}},//鳏 guan
{1,0,{pysm::y,pyym::ao}},//鳐 yao
{1,0,{pysm::p,pyym::ang}},//鳑 pang
{1,0,{pysm::j,pyym::ian}},//鳒 jian
{1,0,{pysm::l,pyym::e}},//鳓 le
{1,0,{pysm::b,pyym::iao}},//鳔 biao
{1,0,{pysm::x,pyym::ue}},//鳕 xue
{1,0,{pysm::b,pyym::ie}},//鳖 bie
{1,0,{pysm::m,pyym::an}},//鳗 man
{1,0,{pysm::m,pyym::in}},//鳘 min
{1,0,{pysm::y,pyym::ong}},//鳙 yong
{1,0,{pysm::w,pyym::ei}},//鳚 wei
{1,0,{pysm::x,pyym::i}},//鳛 xi
{1,0,{pysm::g,pyym::ui}},//鳜 gui
{1,0,{pysm::sh,pyym::an}},//鳝 shan
{1,0,{pysm::l,pyym::in}},//鳞 lin
{1,0,{pysm::z,pyym::un}},//鳟 zun
{1,0,{pysm::h,pyym::u}},//鳠 hu
{1,0,{pysm::g,pyym::an}},//鳡 gan
{1,0,{pysm::l,pyym::i}},//鳢 li
{1,0,{pysm::zh,pyym::an}},//鳣 zhan
{1,0,{pysm::g,pyym::uan}},//鳤 guan
{4,175,{pysm::nop,pyym::nop}},//鳥 niao
{1,0,{pysm::y,pyym::i}},//鳦 yi
{1,0,{pysm::f,pyym::u}},//鳧 fu
{1,0,{pysm::l,pyym::i}},//鳨 li
{3,869,{pysm::nop,pyym::nop}},//鳩 jiu
{1,0,{pysm::b,pyym::u}},//鳪 bu
{1,0,{pysm::y,pyym::an}},//鳫 yan
{1,0,{pysm::f,pyym::u}},//鳬 fu
{2,3721,{pysm::nop,pyym::nop}},//鳭 diao
{1,0,{pysm::j,pyym::i}},//鳮 ji
{1,0,{pysm::f,pyym::eng}},//鳯 feng
{1,0,{pysm::r,pyym::u}},//鳰 ru
{3,870,{pysm::nop,pyym::nop}},//鳱 gan
{1,0,{pysm::sh,pyym::i}},//鳲 shi
{1,0,{pysm::f,pyym::eng}},//鳳 feng
{1,0,{pysm::m,pyym::ing}},//鳴 ming
{1,0,{pysm::b,pyym::ao}},//鳵 bao
{1,0,{pysm::y,pyym::uan}},//鳶 yuan
{2,3722,{pysm::nop,pyym::nop}},//鳷 zhi
{1,0,{pysm::h,pyym::u}},//鳸 hu
{1,0,{pysm::q,pyym::in}},//鳹 qin
{2,3723,{pysm::nop,pyym::nop}},//鳺 fu
{2,3724,{pysm::nop,pyym::nop}},//鳻 ban
{1,0,{pysm::w,pyym::en}},//鳼 wen
{3,871,{pysm::nop,pyym::nop}},//鳽 jian
{1,0,{pysm::sh,pyym::i}},//鳾 shi
{1,0,{pysm::y,pyym::u}},//鳿 yu
{1,0,{pysm::f,pyym::ou}},//鴀 fou
{2,3725,{pysm::nop,pyym::nop}},//鴁 yao
{2,3726,{pysm::nop,pyym::nop}},//鴂 jue
{1,0,{pysm::j,pyym::ue}},//鴃 jue
{1,0,{pysm::p,pyym::i}},//鴄 pi
{1,0,{pysm::h,pyym::uan}},//鴅 huan
{1,0,{pysm::zh,pyym::en}},//鴆 zhen
{1,0,{pysm::b,pyym::ao}},//鴇 bao
{1,0,{pysm::y,pyym::an}},//鴈 yan
{1,0,{pysm::y,pyym::a}},//鴉 ya
{1,0,{pysm::zh,pyym::eng}},//鴊 zheng
{1,0,{pysm::f,pyym::ang}},//鴋 fang
{1,0,{pysm::f,pyym::eng}},//鴌 feng
{1,0,{pysm::w,pyym::en}},//鴍 wen
{1,0,{pysm::nop,pyym::ou}},//鴎 ou
{1,0,{pysm::d,pyym::ai}},//鴏 dai
{1,0,{pysm::g,pyym::e}},//鴐 ge
{1,0,{pysm::r,pyym::u}},//鴑 ru
{1,0,{pysm::l,pyym::ing}},//鴒 ling
{2,3727,{pysm::nop,pyym::nop}},//鴓 mie
{1,0,{pysm::f,pyym::u}},//鴔 fu
{1,0,{pysm::t,pyym::uo}},//鴕 tuo
{2,3728,{pysm::nop,pyym::nop}},//鴖 min
{1,0,{pysm::l,pyym::i}},//鴗 li
{1,0,{pysm::b,pyym::ian}},//鴘 bian
{1,0,{pysm::zh,pyym::i}},//鴙 zhi
{1,0,{pysm::g,pyym::e}},//鴚 ge
{1,0,{pysm::y,pyym::uan}},//鴛 yuan
{1,0,{pysm::c,pyym::i}},//鴜 ci
{2,3729,{pysm::nop,pyym::nop}},//鴝 qu
{1,0,{pysm::x,pyym::iao}},//鴞 xiao
{1,0,{pysm::ch,pyym::i}},//鴟 chi
{1,0,{pysm::d,pyym::an}},//鴠 dan
{1,0,{pysm::j,pyym::u}},//鴡 ju
{2,3730,{pysm::nop,pyym::nop}},//鴢 yao
{1,0,{pysm::g,pyym::u}},//鴣 gu
{1,0,{pysm::zh,pyym::ong}},//鴤 zhong
{1,0,{pysm::y,pyym::u}},//鴥 yu
{1,0,{pysm::y,pyym::ang}},//鴦 yang
{1,0,{pysm::y,pyym::u}},//鴧 yu
{1,0,{pysm::y,pyym::a}},//鴨 ya
{2,3731,{pysm::nop,pyym::nop}},//鴩 tie
{1,0,{pysm::y,pyym::u}},//鴪 yu
{1,0,{pysm::t,pyym::ian}},//鴫 tian
{1,0,{pysm::y,pyym::ing}},//鴬 ying
{1,0,{pysm::d,pyym::ui}},//鴭 dui
{1,0,{pysm::w,pyym::u}},//鴮 wu
{1,0,{pysm::nop,pyym::er}},//鴯 er
{1,0,{pysm::g,pyym::ua}},//鴰 gua
{1,0,{pysm::nop,pyym::ai}},//鴱 ai
{1,0,{pysm::zh,pyym::i}},//鴲 zhi
{3,872,{pysm::nop,pyym::nop}},//鴳 yan
{1,0,{pysm::h,pyym::eng}},//鴴 heng
{1,0,{pysm::x,pyym::iao}},//鴵 xiao
{1,0,{pysm::j,pyym::ia}},//鴶 jia
{1,0,{pysm::l,pyym::ie}},//鴷 lie
{1,0,{pysm::zh,pyym::u}},//鴸 zhu
{2,3732,{pysm::nop,pyym::nop}},//鴹 yang
{2,3733,{pysm::nop,pyym::nop}},//鴺 ti
{1,0,{pysm::h,pyym::ong}},//鴻 hong
{1,0,{pysm::l,pyym::uo}},//鴼 luo
{1,0,{pysm::r,pyym::u}},//鴽 ru
{1,0,{pysm::m,pyym::ou}},//鴾 mou
{1,0,{pysm::g,pyym::e}},//鴿 ge
{1,0,{pysm::r,pyym::en}},//鵀 ren
{2,3734,{pysm::nop,pyym::nop}},//鵁 jiao
{1,0,{pysm::x,pyym::iu}},//鵂 xiu
{2,3735,{pysm::nop,pyym::nop}},//鵃 zhou
{1,0,{pysm::ch,pyym::i}},//鵄 chi
{2,3736,{pysm::nop,pyym::nop}},//鵅 luo
{1,0,{pysm::h,pyym::eng}},//鵆 heng
{1,0,{pysm::n,pyym::ian}},//鵇 nian
{1,0,{pysm::nop,pyym::e}},//鵈 e
{1,0,{pysm::l,pyym::uan}},//鵉 luan
{1,0,{pysm::j,pyym::ia}},//鵊 jia
{1,0,{pysm::j,pyym::i}},//鵋 ji
{1,0,{pysm::t,pyym::u}},//鵌 tu
{3,873,{pysm::nop,pyym::nop}},//鵍 huan
{1,0,{pysm::t,pyym::uo}},//鵎 tuo
{2,3737,{pysm::nop,pyym::nop}},//鵏 bu
{1,0,{pysm::w,pyym::u}},//鵐 wu
{1,0,{pysm::j,pyym::uan}},//鵑 juan
{1,0,{pysm::y,pyym::u}},//鵒 yu
{1,0,{pysm::b,pyym::o}},//鵓 bo
{1,0,{pysm::j,pyym::un}},//鵔 jun
{1,0,{pysm::j,pyym::un}},//鵕 jun
{1,0,{pysm::b,pyym::i}},//鵖 bi
{1,0,{pysm::x,pyym::i}},//鵗 xi
{1,0,{pysm::j,pyym::un}},//鵘 jun
{1,0,{pysm::j,pyym::u}},//鵙 ju
{1,0,{pysm::t,pyym::u}},//鵚 tu
{1,0,{pysm::j,pyym::ing}},//鵛 jing
{1,0,{pysm::t,pyym::i}},//鵜 ti
{1,0,{pysm::nop,pyym::e}},//鵝 e
{1,0,{pysm::nop,pyym::e}},//鵞 e
{1,0,{pysm::k,pyym::uang}},//鵟 kuang
{3,874,{pysm::nop,pyym::nop}},//鵠 hu
{1,0,{pysm::w,pyym::u}},//鵡 wu
{1,0,{pysm::sh,pyym::en}},//鵢 shen
{2,3738,{pysm::nop,pyym::nop}},//鵣 lai
{1,0,{pysm::j,pyym::iao}},//鵤 jiao
{1,0,{pysm::p,pyym::an}},//鵥 pan
{1,0,{pysm::l,pyym::u}},//鵦 lu
{1,0,{pysm::p,pyym::i}},//鵧 pi
{1,0,{pysm::sh,pyym::u}},//鵨 shu
{1,0,{pysm::f,pyym::u}},//鵩 fu
{2,3739,{pysm::nop,pyym::nop}},//鵪 an
{1,0,{pysm::zh,pyym::uo}},//鵫 zhuo
{2,3740,{pysm::nop,pyym::nop}},//鵬 peng
{1,0,{pysm::q,pyym::in}},//鵭 qin
{1,0,{pysm::q,pyym::ian}},//鵮 qian
{1,0,{pysm::b,pyym::ei}},//鵯 bei
{1,0,{pysm::d,pyym::iao}},//鵰 diao
{1,0,{pysm::l,pyym::u}},//鵱 lu
{1,0,{pysm::q,pyym::ue}},//鵲 que
{1,0,{pysm::j,pyym::ian}},//鵳 jian
{1,0,{pysm::j,pyym::u}},//鵴 ju
{1,0,{pysm::t,pyym::u}},//鵵 tu
{1,0,{pysm::y,pyym::a}},//鵶 ya
{1,0,{pysm::y,pyym::uan}},//鵷 yuan
{1,0,{pysm::q,pyym::i}},//鵸 qi
{1,0,{pysm::l,pyym::i}},//鵹 li
{1,0,{pysm::y,pyym::e}},//鵺 ye
{1,0,{pysm::zh,pyym::ui}},//鵻 zhui
{1,0,{pysm::k,pyym::ong}},//鵼 kong
{1,0,{pysm::d,pyym::uo}},//鵽 duo
{1,0,{pysm::k,pyym::un}},//鵾 kun
{1,0,{pysm::sh,pyym::eng}},//鵿 sheng
{1,0,{pysm::q,pyym::i}},//鶀 qi
{1,0,{pysm::j,pyym::ing}},//鶁 jing
{1,0,{pysm::y,pyym::i}},//鶂 yi
{1,0,{pysm::y,pyym::i}},//鶃 yi
{2,3741,{pysm::nop,pyym::nop}},//鶄 jing
{1,0,{pysm::z,pyym::i}},//鶅 zi
{1,0,{pysm::l,pyym::ai}},//鶆 lai
{1,0,{pysm::d,pyym::ong}},//鶇 dong
{1,0,{pysm::q,pyym::i}},//鶈 qi
{2,3742,{pysm::nop,pyym::nop}},//鶉 chun
{1,0,{pysm::g,pyym::eng}},//鶊 geng
{1,0,{pysm::j,pyym::u}},//鶋 ju
{2,3743,{pysm::nop,pyym::nop}},//鶌 jue
{1,0,{pysm::y,pyym::i}},//鶍 yi
{1,0,{pysm::z,pyym::un}},//鶎 zun
{1,0,{pysm::j,pyym::i}},//鶏 ji
{1,0,{pysm::sh,pyym::u}},//鶐 shu
{1,0,{pysm::y,pyym::ing}},//鶑 ying
{1,0,{pysm::ch,pyym::i}},//鶒 chi
{1,0,{pysm::m,pyym::iao}},//鶓 miao
{1,0,{pysm::r,pyym::ou}},//鶔 rou
{1,0,{pysm::nop,pyym::an}},//鶕 an
{1,0,{pysm::q,pyym::iu}},//鶖 qiu
{2,3744,{pysm::nop,pyym::nop}},//鶗 ti
{1,0,{pysm::h,pyym::u}},//鶘 hu
{1,0,{pysm::t,pyym::i}},//鶙 ti
{1,0,{pysm::nop,pyym::e}},//鶚 e
{1,0,{pysm::j,pyym::ie}},//鶛 jie
{1,0,{pysm::m,pyym::ao}},//鶜 mao
{2,3745,{pysm::nop,pyym::nop}},//鶝 fu
{1,0,{pysm::ch,pyym::un}},//鶞 chun
{1,0,{pysm::t,pyym::u}},//鶟 tu
{1,0,{pysm::y,pyym::an}},//鶠 yan
{1,0,{pysm::h,pyym::e}},//鶡 he
{1,0,{pysm::y,pyym::uan}},//鶢 yuan
{2,3746,{pysm::nop,pyym::nop}},//鶣 pian
{1,0,{pysm::k,pyym::un}},//鶤 kun
{1,0,{pysm::m,pyym::ei}},//鶥 mei
{1,0,{pysm::h,pyym::u}},//鶦 hu
{1,0,{pysm::y,pyym::ing}},//鶧 ying
{2,3747,{pysm::nop,pyym::nop}},//鶨 chuan
{2,3748,{pysm::nop,pyym::nop}},//鶩 wu
{1,0,{pysm::j,pyym::u}},//鶪 ju
{1,0,{pysm::d,pyym::ong}},//鶫 dong
{2,3749,{pysm::nop,pyym::nop}},//鶬 cang
{1,0,{pysm::f,pyym::ang}},//鶭 fang
{2,3750,{pysm::nop,pyym::nop}},//鶮 he
{1,0,{pysm::y,pyym::ing}},//鶯 ying
{1,0,{pysm::y,pyym::uan}},//鶰 yuan
{1,0,{pysm::x,pyym::ian}},//鶱 xian
{1,0,{pysm::w,pyym::eng}},//鶲 weng
{1,0,{pysm::sh,pyym::i}},//鶳 shi
{1,0,{pysm::h,pyym::e}},//鶴 he
{1,0,{pysm::ch,pyym::u}},//鶵 chu
{1,0,{pysm::t,pyym::ang}},//鶶 tang
{1,0,{pysm::x,pyym::ia}},//鶷 xia
{1,0,{pysm::r,pyym::uo}},//鶸 ruo
{1,0,{pysm::l,pyym::iu}},//鶹 liu
{1,0,{pysm::j,pyym::i}},//鶺 ji
{2,3751,{pysm::nop,pyym::nop}},//鶻 gu
{2,3752,{pysm::nop,pyym::nop}},//鶼 jian
{2,3753,{pysm::nop,pyym::nop}},//鶽 sun
{1,0,{pysm::h,pyym::an}},//鶾 han
{1,0,{pysm::c,pyym::i}},//鶿 ci
{1,0,{pysm::c,pyym::i}},//鷀 ci
{1,0,{pysm::y,pyym::i}},//鷁 yi
{1,0,{pysm::y,pyym::ao}},//鷂 yao
{1,0,{pysm::y,pyym::an}},//鷃 yan
{1,0,{pysm::j,pyym::i}},//鷄 ji
{1,0,{pysm::l,pyym::i}},//鷅 li
{1,0,{pysm::t,pyym::ian}},//鷆 tian
{1,0,{pysm::k,pyym::ou}},//鷇 kou
{1,0,{pysm::t,pyym::i}},//鷈 ti
{2,3754,{pysm::nop,pyym::nop}},//鷉 ti
{1,0,{pysm::y,pyym::i}},//鷊 yi
{1,0,{pysm::t,pyym::u}},//鷋 tu
{1,0,{pysm::m,pyym::a}},//鷌 ma
{1,0,{pysm::x,pyym::iao}},//鷍 xiao
{1,0,{pysm::g,pyym::ao}},//鷎 gao
{1,0,{pysm::t,pyym::ian}},//鷏 tian
{1,0,{pysm::ch,pyym::en}},//鷐 chen
{1,0,{pysm::j,pyym::i}},//鷑 ji
{1,0,{pysm::t,pyym::uan}},//鷒 tuan
{1,0,{pysm::zh,pyym::e}},//鷓 zhe
{1,0,{pysm::nop,pyym::ao}},//鷔 ao
{2,3755,{pysm::nop,pyym::nop}},//鷕 yao
{1,0,{pysm::y,pyym::i}},//鷖 yi
{1,0,{pysm::nop,pyym::ou}},//鷗 ou
{1,0,{pysm::ch,pyym::i}},//鷘 chi
{2,3756,{pysm::nop,pyym::nop}},//鷙 zhi
{1,0,{pysm::l,pyym::iu}},//鷚 liu
{1,0,{pysm::y,pyym::ong}},//鷛 yong
{1,0,{pysm::l,pyym::v}},//鷜 lü
{1,0,{pysm::b,pyym::i}},//鷝 bi
{1,0,{pysm::sh,pyym::uang}},//鷞 shuang
{1,0,{pysm::zh,pyym::uo}},//鷟 zhuo
{1,0,{pysm::y,pyym::u}},//鷠 yu
{1,0,{pysm::w,pyym::u}},//鷡 wu
{1,0,{pysm::j,pyym::ue}},//鷢 jue
{1,0,{pysm::y,pyym::in}},//鷣 yin
{2,3757,{pysm::nop,pyym::nop}},//鷤 ti
{1,0,{pysm::s,pyym::i}},//鷥 si
{1,0,{pysm::j,pyym::iao}},//鷦 jiao
{1,0,{pysm::y,pyym::i}},//鷧 yi
{1,0,{pysm::h,pyym::ua}},//鷨 hua
{1,0,{pysm::b,pyym::i}},//鷩 bi
{1,0,{pysm::y,pyym::ing}},//鷪 ying
{1,0,{pysm::s,pyym::u}},//鷫 su
{1,0,{pysm::h,pyym::uang}},//鷬 huang
{1,0,{pysm::f,pyym::an}},//鷭 fan
{1,0,{pysm::j,pyym::iao}},//鷮 jiao
{1,0,{pysm::l,pyym::iao}},//鷯 liao
{1,0,{pysm::y,pyym::an}},//鷰 yan
{1,0,{pysm::g,pyym::ao}},//鷱 gao
{1,0,{pysm::j,pyym::iu}},//鷲 jiu
{1,0,{pysm::x,pyym::ian}},//鷳 xian
{1,0,{pysm::x,pyym::ian}},//鷴 xian
{1,0,{pysm::t,pyym::u}},//鷵 tu
{1,0,{pysm::m,pyym::ai}},//鷶 mai
{1,0,{pysm::z,pyym::un}},//鷷 zun
{2,3758,{pysm::nop,pyym::nop}},//鷸 yu
{1,0,{pysm::y,pyym::ing}},//鷹 ying
{1,0,{pysm::l,pyym::u}},//鷺 lu
{1,0,{pysm::t,pyym::uan}},//鷻 tuan
{1,0,{pysm::x,pyym::ian}},//鷼 xian
{1,0,{pysm::x,pyym::ue}},//鷽 xue
{1,0,{pysm::y,pyym::i}},//鷾 yi
{1,0,{pysm::p,pyym::i}},//鷿 pi
{2,3759,{pysm::nop,pyym::nop}},//鸀 chu
{1,0,{pysm::l,pyym::uo}},//鸁 luo
{2,3760,{pysm::nop,pyym::nop}},//鸂 xi
{1,0,{pysm::y,pyym::i}},//鸃 yi
{1,0,{pysm::j,pyym::i}},//鸄 ji
{1,0,{pysm::z,pyym::e}},//鸅 ze
{1,0,{pysm::y,pyym::u}},//鸆 yu
{1,0,{pysm::zh,pyym::an}},//鸇 zhan
{1,0,{pysm::y,pyym::e}},//鸈 ye
{1,0,{pysm::y,pyym::ang}},//鸉 yang
{2,3761,{pysm::nop,pyym::nop}},//鸊 pi
{1,0,{pysm::n,pyym::ing}},//鸋 ning
{1,0,{pysm::h,pyym::u}},//鸌 hu
{1,0,{pysm::m,pyym::i}},//鸍 mi
{1,0,{pysm::y,pyym::ing}},//鸎 ying
{2,3762,{pysm::nop,pyym::nop}},//鸏 meng
{1,0,{pysm::d,pyym::i}},//鸐 di
{1,0,{pysm::y,pyym::ue}},//鸑 yue
{1,0,{pysm::y,pyym::u}},//鸒 yu
{1,0,{pysm::l,pyym::ei}},//鸓 lei
{1,0,{pysm::b,pyym::u}},//鸔 bu
{1,0,{pysm::l,pyym::u}},//鸕 lu
{1,0,{pysm::h,pyym::e}},//鸖 he
{1,0,{pysm::l,pyym::ong}},//鸗 long
{1,0,{pysm::sh,pyym::uang}},//鸘 shuang
{1,0,{pysm::y,pyym::ue}},//鸙 yue
{1,0,{pysm::y,pyym::ing}},//鸚 ying
{3,875,{pysm::nop,pyym::nop}},//鸛 guan
{1,0,{pysm::q,pyym::u}},//鸜 qu
{1,0,{pysm::l,pyym::i}},//鸝 li
{1,0,{pysm::l,pyym::uan}},//鸞 luan
{2,3763,{pysm::nop,pyym::nop}},//鸟 niao
{1,0,{pysm::j,pyym::iu}},//鸠 jiu
{1,0,{pysm::j,pyym::i}},//鸡 ji
{1,0,{pysm::y,pyym::uan}},//鸢 yuan
{1,0,{pysm::m,pyym::ing}},//鸣 ming
{1,0,{pysm::sh,pyym::i}},//鸤 shi
{1,0,{pysm::nop,pyym::ou}},//鸥 ou
{1,0,{pysm::y,pyym::a}},//鸦 ya
{1,0,{pysm::c,pyym::ang}},//鸧 cang
{1,0,{pysm::b,pyym::ao}},//鸨 bao
{1,0,{pysm::zh,pyym::en}},//鸩 zhen
{1,0,{pysm::g,pyym::u}},//鸪 gu
{1,0,{pysm::d,pyym::ong}},//鸫 dong
{1,0,{pysm::l,pyym::u}},//鸬 lu
{1,0,{pysm::y,pyym::a}},//鸭 ya
{1,0,{pysm::x,pyym::iao}},//鸮 xiao
{1,0,{pysm::y,pyym::ang}},//鸯 yang
{1,0,{pysm::l,pyym::ing}},//鸰 ling
{1,0,{pysm::ch,pyym::i}},//鸱 chi
{1,0,{pysm::q,pyym::u}},//鸲 qu
{1,0,{pysm::y,pyym::uan}},//鸳 yuan
{1,0,{pysm::x,pyym::ue}},//鸴 xue
{1,0,{pysm::t,pyym::uo}},//鸵 tuo
{1,0,{pysm::s,pyym::i}},//鸶 si
{1,0,{pysm::zh,pyym::i}},//鸷 zhi
{1,0,{pysm::nop,pyym::er}},//鸸 er
{1,0,{pysm::g,pyym::ua}},//鸹 gua
{1,0,{pysm::x,pyym::iu}},//鸺 xiu
{1,0,{pysm::h,pyym::eng}},//鸻 heng
{1,0,{pysm::zh,pyym::ou}},//鸼 zhou
{1,0,{pysm::g,pyym::e}},//鸽 ge
{1,0,{pysm::l,pyym::uan}},//鸾 luan
{1,0,{pysm::h,pyym::ong}},//鸿 hong
{1,0,{pysm::w,pyym::u}},//鹀 wu
{1,0,{pysm::b,pyym::o}},//鹁 bo
{1,0,{pysm::l,pyym::i}},//鹂 li
{1,0,{pysm::j,pyym::uan}},//鹃 juan
{2,3764,{pysm::nop,pyym::nop}},//鹄 gu
{1,0,{pysm::nop,pyym::e}},//鹅 e
{1,0,{pysm::y,pyym::u}},//鹆 yu
{1,0,{pysm::x,pyym::ian}},//鹇 xian
{1,0,{pysm::t,pyym::i}},//鹈 ti
{1,0,{pysm::w,pyym::u}},//鹉 wu
{1,0,{pysm::q,pyym::ue}},//鹊 que
{1,0,{pysm::m,pyym::iao}},//鹋 miao
{1,0,{pysm::nop,pyym::an}},//鹌 an
{1,0,{pysm::k,pyym::un}},//鹍 kun
{1,0,{pysm::b,pyym::ei}},//鹎 bei
{1,0,{pysm::p,pyym::eng}},//鹏 peng
{1,0,{pysm::q,pyym::ian}},//鹐 qian
{1,0,{pysm::ch,pyym::un}},//鹑 chun
{1,0,{pysm::g,pyym::eng}},//鹒 geng
{1,0,{pysm::y,pyym::uan}},//鹓 yuan
{1,0,{pysm::s,pyym::u}},//鹔 su
{1,0,{pysm::h,pyym::u}},//鹕 hu
{1,0,{pysm::h,pyym::e}},//鹖 he
{1,0,{pysm::nop,pyym::e}},//鹗 e
{2,3765,{pysm::nop,pyym::nop}},//鹘 gu
{1,0,{pysm::q,pyym::iu}},//鹙 qiu
{1,0,{pysm::c,pyym::i}},//鹚 ci
{1,0,{pysm::m,pyym::ei}},//鹛 mei
{1,0,{pysm::w,pyym::u}},//鹜 wu
{1,0,{pysm::y,pyym::i}},//鹝 yi
{1,0,{pysm::y,pyym::ao}},//鹞 yao
{1,0,{pysm::w,pyym::eng}},//鹟 weng
{1,0,{pysm::l,pyym::iu}},//鹠 liu
{1,0,{pysm::j,pyym::i}},//鹡 ji
{1,0,{pysm::y,pyym::i}},//鹢 yi
{1,0,{pysm::j,pyym::ian}},//鹣 jian
{1,0,{pysm::h,pyym::e}},//鹤 he
{1,0,{pysm::y,pyym::i}},//鹥 yi
{1,0,{pysm::y,pyym::ing}},//鹦 ying
{1,0,{pysm::zh,pyym::e}},//鹧 zhe
{1,0,{pysm::l,pyym::iu}},//鹨 liu
{1,0,{pysm::l,pyym::iao}},//鹩 liao
{1,0,{pysm::j,pyym::iao}},//鹪 jiao
{1,0,{pysm::j,pyym::iu}},//鹫 jiu
{1,0,{pysm::y,pyym::u}},//鹬 yu
{1,0,{pysm::l,pyym::u}},//鹭 lu
{1,0,{pysm::h,pyym::uan}},//鹮 huan
{1,0,{pysm::zh,pyym::an}},//鹯 zhan
{1,0,{pysm::y,pyym::ing}},//鹰 ying
{1,0,{pysm::h,pyym::u}},//鹱 hu
{1,0,{pysm::m,pyym::eng}},//鹲 meng
{1,0,{pysm::g,pyym::uan}},//鹳 guan
{1,0,{pysm::sh,pyym::uang}},//鹴 shuang
{1,0,{pysm::l,pyym::u}},//鹵 lu
{1,0,{pysm::j,pyym::in}},//鹶 jin
{1,0,{pysm::l,pyym::ing}},//鹷 ling
{1,0,{pysm::j,pyym::ian}},//鹸 jian
{2,3766,{pysm::nop,pyym::nop}},//鹹 xian
{1,0,{pysm::c,pyym::uo}},//鹺 cuo
{1,0,{pysm::j,pyym::ian}},//鹻 jian
{1,0,{pysm::j,pyym::ian}},//鹼 jian
{1,0,{pysm::y,pyym::an}},//鹽 yan
{1,0,{pysm::c,pyym::uo}},//鹾 cuo
{2,3767,{pysm::nop,pyym::nop}},//鹿 lu
{1,0,{pysm::y,pyym::ou}},//麀 you
{1,0,{pysm::c,pyym::u}},//麁 cu
{1,0,{pysm::j,pyym::i}},//麂 ji
{3,876,{pysm::nop,pyym::nop}},//麃 pao
{1,0,{pysm::c,pyym::u}},//麄 cu
{1,0,{pysm::p,pyym::ao}},//麅 pao
{2,3768,{pysm::nop,pyym::nop}},//麆 zhu
{2,3769,{pysm::nop,pyym::nop}},//麇 jun
{1,0,{pysm::zh,pyym::u}},//麈 zhu
{1,0,{pysm::j,pyym::ian}},//麉 jian
{1,0,{pysm::m,pyym::i}},//麊 mi
{1,0,{pysm::m,pyym::i}},//麋 mi
{1,0,{pysm::y,pyym::u}},//麌 yu
{1,0,{pysm::l,pyym::iu}},//麍 liu
{1,0,{pysm::ch,pyym::en}},//麎 chen
{1,0,{pysm::j,pyym::un}},//麏 jun
{1,0,{pysm::l,pyym::in}},//麐 lin
{1,0,{pysm::n,pyym::i}},//麑 ni
{1,0,{pysm::q,pyym::i}},//麒 qi
{1,0,{pysm::l,pyym::u}},//麓 lu
{1,0,{pysm::j,pyym::iu}},//麔 jiu
{2,3770,{pysm::nop,pyym::nop}},//麕 jun
{1,0,{pysm::j,pyym::ing}},//麖 jing
{2,3771,{pysm::nop,pyym::nop}},//麗 li
{1,0,{pysm::x,pyym::iang}},//麘 xiang
{2,3772,{pysm::nop,pyym::nop}},//麙 xian
{1,0,{pysm::j,pyym::ia}},//麚 jia
{1,0,{pysm::m,pyym::i}},//麛 mi
{1,0,{pysm::l,pyym::i}},//麜 li
{1,0,{pysm::sh,pyym::e}},//麝 she
{1,0,{pysm::zh,pyym::ang}},//麞 zhang
{1,0,{pysm::l,pyym::in}},//麟 lin
{1,0,{pysm::j,pyym::ing}},//麠 jing
{1,0,{pysm::q,pyym::i}},//麡 qi
{1,0,{pysm::l,pyym::ing}},//麢 ling
{1,0,{pysm::y,pyym::an}},//麣 yan
{1,0,{pysm::c,pyym::u}},//麤 cu
{1,0,{pysm::m,pyym::ai}},//麥 mai
{1,0,{pysm::m,pyym::ai}},//麦 mai
{1,0,{pysm::h,pyym::e}},//麧 he
{1,0,{pysm::ch,pyym::ao}},//麨 chao
{1,0,{pysm::f,pyym::u}},//麩 fu
{1,0,{pysm::m,pyym::ian}},//麪 mian
{1,0,{pysm::m,pyym::ian}},//麫 mian
{1,0,{pysm::f,pyym::u}},//麬 fu
{1,0,{pysm::p,pyym::ao}},//麭 pao
{1,0,{pysm::q,pyym::u}},//麮 qu
{1,0,{pysm::q,pyym::u}},//麯 qu
{1,0,{pysm::m,pyym::ou}},//麰 mou
{1,0,{pysm::f,pyym::u}},//麱 fu
{2,3773,{pysm::nop,pyym::nop}},//麲 xian
{1,0,{pysm::l,pyym::ai}},//麳 lai
{1,0,{pysm::q,pyym::u}},//麴 qu
{1,0,{pysm::m,pyym::ian}},//麵 mian
{1,0,{pysm::ch,pyym::i}},//麶 chi
{1,0,{pysm::f,pyym::eng}},//麷 feng
{1,0,{pysm::f,pyym::u}},//麸 fu
{1,0,{pysm::q,pyym::u}},//麹 qu
{1,0,{pysm::m,pyym::ian}},//麺 mian
{1,0,{pysm::m,pyym::a}},//麻 ma
{1,0,{pysm::m,pyym::e}},//麼 me
{3,877,{pysm::nop,pyym::nop}},//麽 mo
{1,0,{pysm::h,pyym::ui}},//麾 hui
{1,0,{pysm::m,pyym::i}},//麿 mi
{1,0,{pysm::z,pyym::ou}},//黀 zou
{1,0,{pysm::n,pyym::un}},//黁 nun
{1,0,{pysm::f,pyym::en}},//黂 fen
{1,0,{pysm::h,pyym::uang}},//黃 huang
{1,0,{pysm::h,pyym::uang}},//黄 huang
{1,0,{pysm::j,pyym::in}},//黅 jin
{1,0,{pysm::g,pyym::uang}},//黆 guang
{1,0,{pysm::t,pyym::ian}},//黇 tian
{1,0,{pysm::t,pyym::ou}},//黈 tou
{1,0,{pysm::h,pyym::ong}},//黉 hong
{1,0,{pysm::h,pyym::ua}},//黊 hua
{1,0,{pysm::k,pyym::uang}},//黋 kuang
{1,0,{pysm::h,pyym::ong}},//黌 hong
{1,0,{pysm::sh,pyym::u}},//黍 shu
{1,0,{pysm::l,pyym::i}},//黎 li
{1,0,{pysm::n,pyym::ian}},//黏 nian
{2,3774,{pysm::nop,pyym::nop}},//黐 chi
{1,0,{pysm::h,pyym::ei}},//黑 hei
{1,0,{pysm::h,pyym::ei}},//黒 hei
{1,0,{pysm::y,pyym::i}},//黓 yi
{1,0,{pysm::q,pyym::ian}},//黔 qian
{1,0,{pysm::d,pyym::an}},//黕 dan
{1,0,{pysm::x,pyym::i}},//黖 xi
{1,0,{pysm::t,pyym::un}},//黗 tun
{1,0,{pysm::m,pyym::o}},//默 mo
{1,0,{pysm::m,pyym::o}},//黙 mo
{2,3775,{pysm::nop,pyym::nop}},//黚 qian
{1,0,{pysm::d,pyym::ai}},//黛 dai
{1,0,{pysm::ch,pyym::u}},//黜 chu
{2,3776,{pysm::nop,pyym::nop}},//黝 you
{3,878,{pysm::nop,pyym::nop}},//點 dian
{1,0,{pysm::y,pyym::i}},//黟 yi
{1,0,{pysm::x,pyym::ia}},//黠 xia
{1,0,{pysm::y,pyym::an}},//黡 yan
{1,0,{pysm::q,pyym::u}},//黢 qu
{1,0,{pysm::m,pyym::ei}},//黣 mei
{1,0,{pysm::y,pyym::an}},//黤 yan
{1,0,{pysm::q,pyym::ing}},//黥 qing
{2,3777,{pysm::nop,pyym::nop}},//黦 yue
{2,3778,{pysm::nop,pyym::nop}},//黧 li
{3,879,{pysm::nop,pyym::nop}},//黨 dang
{1,0,{pysm::d,pyym::u}},//黩 du
{1,0,{pysm::c,pyym::an}},//黪 can
{1,0,{pysm::y,pyym::an}},//黫 yan
{2,3779,{pysm::nop,pyym::nop}},//黬 yan
{1,0,{pysm::y,pyym::an}},//黭 yan
{4,176,{pysm::nop,pyym::nop}},//黮 dan
{1,0,{pysm::nop,pyym::an}},//黯 an
{2,3780,{pysm::nop,pyym::nop}},//黰 zhen
{2,3781,{pysm::nop,pyym::nop}},//黱 dai
{1,0,{pysm::c,pyym::an}},//黲 can
{2,3782,{pysm::nop,pyym::nop}},//黳 yi
{1,0,{pysm::m,pyym::ei}},//黴 mei
{2,3783,{pysm::nop,pyym::nop}},//黵 zhan
{1,0,{pysm::y,pyym::an}},//黶 yan
{1,0,{pysm::d,pyym::u}},//黷 du
{1,0,{pysm::l,pyym::u}},//黸 lu
{2,3784,{pysm::nop,pyym::nop}},//黹 zhi
{1,0,{pysm::f,pyym::en}},//黺 fen
{1,0,{pysm::f,pyym::u}},//黻 fu
{1,0,{pysm::f,pyym::u}},//黼 fu
{3,880,{pysm::nop,pyym::nop}},//黽 mian
{3,881,{pysm::nop,pyym::nop}},//黾 min
{1,0,{pysm::y,pyym::uan}},//黿 yuan
{1,0,{pysm::c,pyym::u}},//鼀 cu
{1,0,{pysm::q,pyym::u}},//鼁 qu
{2,3785,{pysm::nop,pyym::nop}},//鼂 chao
{1,0,{pysm::w,pyym::a}},//鼃 wa
{1,0,{pysm::zh,pyym::u}},//鼄 zhu
{1,0,{pysm::zh,pyym::i}},//鼅 zhi
{1,0,{pysm::m,pyym::eng}},//鼆 meng
{1,0,{pysm::nop,pyym::ao}},//鼇 ao
{1,0,{pysm::b,pyym::ie}},//鼈 bie
{1,0,{pysm::t,pyym::uo}},//鼉 tuo
{1,0,{pysm::b,pyym::i}},//鼊 bi
{1,0,{pysm::y,pyym::uan}},//鼋 yuan
{1,0,{pysm::ch,pyym::ao}},//鼌 chao
{1,0,{pysm::t,pyym::uo}},//鼍 tuo
{2,3786,{pysm::nop,pyym::nop}},//鼎 ding
{1,0,{pysm::m,pyym::i}},//鼏 mi
{1,0,{pysm::n,pyym::ai}},//鼐 nai
{1,0,{pysm::d,pyym::ing}},//鼑 ding
{1,0,{pysm::z,pyym::i}},//鼒 zi
{1,0,{pysm::g,pyym::u}},//鼓 gu
{1,0,{pysm::g,pyym::u}},//鼔 gu
{2,3787,{pysm::nop,pyym::nop}},//鼕 dong
{1,0,{pysm::f,pyym::en}},//鼖 fen
{1,0,{pysm::t,pyym::ao}},//鼗 tao
{1,0,{pysm::y,pyym::uan}},//鼘 yuan
{1,0,{pysm::p,pyym::i}},//鼙 pi
{1,0,{pysm::ch,pyym::ang}},//鼚 chang
{1,0,{pysm::g,pyym::ao}},//鼛 gao
{2,3788,{pysm::nop,pyym::nop}},//鼜 qi
{1,0,{pysm::y,pyym::uan}},//鼝 yuan
{1,0,{pysm::t,pyym::ang}},//鼞 tang
{1,0,{pysm::t,pyym::eng}},//鼟 teng
{1,0,{pysm::sh,pyym::u}},//鼠 shu
{1,0,{pysm::sh,pyym::u}},//鼡 shu
{1,0,{pysm::f,pyym::en}},//鼢 fen
{1,0,{pysm::f,pyym::ei}},//鼣 fei
{1,0,{pysm::w,pyym::en}},//鼤 wen
{2,3789,{pysm::nop,pyym::nop}},//鼥 ba
{1,0,{pysm::d,pyym::iao}},//鼦 diao
{1,0,{pysm::t,pyym::uo}},//鼧 tuo
{1,0,{pysm::zh,pyym::ong}},//鼨 zhong
{1,0,{pysm::q,pyym::u}},//鼩 qu
{1,0,{pysm::sh,pyym::eng}},//鼪 sheng
{1,0,{pysm::sh,pyym::i}},//鼫 shi
{1,0,{pysm::y,pyym::ou}},//鼬 you
{1,0,{pysm::sh,pyym::i}},//鼭 shi
{1,0,{pysm::t,pyym::ing}},//鼮 ting
{1,0,{pysm::w,pyym::u}},//鼯 wu
{1,0,{pysm::j,pyym::u}},//鼰 ju
{1,0,{pysm::j,pyym::ing}},//鼱 jing
{1,0,{pysm::h,pyym::un}},//鼲 hun
{2,3790,{pysm::nop,pyym::nop}},//鼳 ju
{1,0,{pysm::y,pyym::an}},//鼴 yan
{1,0,{pysm::t,pyym::u}},//鼵 tu
{1,0,{pysm::s,pyym::i}},//鼶 si
{1,0,{pysm::x,pyym::i}},//鼷 xi
{1,0,{pysm::x,pyym::ian}},//鼸 xian
{1,0,{pysm::y,pyym::an}},//鼹 yan
{1,0,{pysm::l,pyym::ei}},//鼺 lei
{1,0,{pysm::b,pyym::i}},//鼻 bi
{1,0,{pysm::y,pyym::ao}},//鼼 yao
{1,0,{pysm::q,pyym::iu}},//鼽 qiu
{1,0,{pysm::h,pyym::an}},//鼾 han
{2,3791,{pysm::nop,pyym::nop}},//鼿 wu
{1,0,{pysm::w,pyym::u}},//齀 wu
{2,3792,{pysm::nop,pyym::nop}},//齁 hou
{1,0,{pysm::x,pyym::ie}},//齂 xie
{2,3793,{pysm::nop,pyym::nop}},//齃 e
{1,0,{pysm::zh,pyym::a}},//齄 zha
{1,0,{pysm::x,pyym::iu}},//齅 xiu
{1,0,{pysm::w,pyym::eng}},//齆 weng
{1,0,{pysm::zh,pyym::a}},//齇 zha
{1,0,{pysm::n,pyym::ong}},//齈 nong
{1,0,{pysm::n,pyym::ang}},//齉 nang
{5,53,{pysm::nop,pyym::nop}},//齊 qi
{1,0,{pysm::zh,pyym::ai}},//齋 zhai
{1,0,{pysm::j,pyym::i}},//齌 ji
{2,3794,{pysm::nop,pyym::nop}},//齍 zi
{1,0,{pysm::j,pyym::i}},//齎 ji
{1,0,{pysm::j,pyym::i}},//齏 ji
{2,3795,{pysm::nop,pyym::nop}},//齐 qi
{1,0,{pysm::j,pyym::i}},//齑 ji
{1,0,{pysm::ch,pyym::i}},//齒 chi
{1,0,{pysm::ch,pyym::en}},//齓 chen
{1,0,{pysm::ch,pyym::en}},//齔 chen
{1,0,{pysm::h,pyym::e}},//齕 he
{1,0,{pysm::y,pyym::a}},//齖 ya
{2,3796,{pysm::nop,pyym::nop}},//齗 yin
{1,0,{pysm::x,pyym::ie}},//齘 xie
{1,0,{pysm::b,pyym::ao}},//齙 bao
{1,0,{pysm::z,pyym::e}},//齚 ze
{2,3797,{pysm::nop,pyym::nop}},//齛 xie
{2,3798,{pysm::nop,pyym::nop}},//齜 chai
{1,0,{pysm::ch,pyym::i}},//齝 chi
{1,0,{pysm::y,pyym::an}},//齞 yan
{2,3799,{pysm::nop,pyym::nop}},//齟 ju
{1,0,{pysm::t,pyym::iao}},//齠 tiao
{1,0,{pysm::l,pyym::ing}},//齡 ling
{1,0,{pysm::l,pyym::ing}},//齢 ling
{2,3800,{pysm::nop,pyym::nop}},//齣 chu
{1,0,{pysm::q,pyym::uan}},//齤 quan
{1,0,{pysm::x,pyym::ie}},//齥 xie
{4,177,{pysm::nop,pyym::nop}},//齦 ken
{1,0,{pysm::n,pyym::ie}},//齧 nie
{1,0,{pysm::j,pyym::iu}},//齨 jiu
{1,0,{pysm::y,pyym::ao}},//齩 yao
{1,0,{pysm::ch,pyym::uo}},//齪 chuo
{1,0,{pysm::y,pyym::un}},//齫 yun
{2,3801,{pysm::nop,pyym::nop}},//齬 yu
{1,0,{pysm::ch,pyym::u}},//齭 chu
{2,3802,{pysm::nop,pyym::nop}},//齮 yi
{1,0,{pysm::n,pyym::i}},//齯 ni
{3,882,{pysm::nop,pyym::nop}},//齰 ze
{2,3803,{pysm::nop,pyym::nop}},//齱 zou
{1,0,{pysm::q,pyym::u}},//齲 qu
{1,0,{pysm::y,pyym::un}},//齳 yun
{1,0,{pysm::y,pyym::an}},//齴 yan
{2,3804,{pysm::nop,pyym::nop}},//齵 ou
{1,0,{pysm::nop,pyym::e}},//齶 e
{1,0,{pysm::w,pyym::o}},//齷 wo
{1,0,{pysm::y,pyym::i}},//齸 yi
{2,3805,{pysm::nop,pyym::nop}},//齹 ci
{1,0,{pysm::z,pyym::ou}},//齺 zou
{1,0,{pysm::d,pyym::ian}},//齻 dian
{1,0,{pysm::ch,pyym::u}},//齼 chu
{1,0,{pysm::j,pyym::in}},//齽 jin
{2,3806,{pysm::nop,pyym::nop}},//齾 ya
{1,0,{pysm::ch,pyym::i}},//齿 chi
{1,0,{pysm::ch,pyym::en}},//龀 chen
{1,0,{pysm::h,pyym::e}},//龁 he
{1,0,{pysm::y,pyym::in}},//龂 yin
{1,0,{pysm::j,pyym::u}},//龃 ju
{1,0,{pysm::l,pyym::ing}},//龄 ling
{1,0,{pysm::b,pyym::ao}},//龅 bao
{1,0,{pysm::t,pyym::iao}},//龆 tiao
{1,0,{pysm::z,pyym::i}},//龇 zi
{2,3807,{pysm::nop,pyym::nop}},//龈 ken
{1,0,{pysm::y,pyym::u}},//龉 yu
{1,0,{pysm::ch,pyym::uo}},//龊 chuo
{1,0,{pysm::q,pyym::u}},//龋 qu
{1,0,{pysm::w,pyym::o}},//龌 wo
{2,3808,{pysm::nop,pyym::nop}},//龍 long
{1,0,{pysm::p,pyym::ang}},//龎 pang
{2,3809,{pysm::nop,pyym::nop}},//龏 gong
{2,3810,{pysm::nop,pyym::nop}},//龐 pang
{1,0,{pysm::y,pyym::an}},//龑 yan
{1,0,{pysm::l,pyym::ong}},//龒 long
{1,0,{pysm::l,pyym::ong}},//龓 long
{1,0,{pysm::g,pyym::ong}},//龔 gong
{2,3811,{pysm::nop,pyym::nop}},//龕 kan
{1,0,{pysm::d,pyym::a}},//龖 da
{1,0,{pysm::l,pyym::ing}},//龗 ling
{1,0,{pysm::d,pyym::a}},//龘 da
{1,0,{pysm::l,pyym::ong}},//龙 long
{1,0,{pysm::g,pyym::ong}},//龚 gong
{1,0,{pysm::k,pyym::an}},//龛 kan
{3,883,{pysm::nop,pyym::nop}},//龜 gui
{1,0,{pysm::q,pyym::iu}},//龝 qiu
{1,0,{pysm::b,pyym::ie}},//龞 bie
{3,884,{pysm::nop,pyym::nop}},//龟 gui
{1,0,{pysm::y,pyym::ue}},//龠 yue
{1,0,{pysm::ch,pyym::ui}},//龡 chui
{1,0,{pysm::h,pyym::e}},//龢 he
{1,0,{pysm::j,pyym::ue}},//龣 jue
{1,0,{pysm::x,pyym::ie}},//龤 xie
{1,0,{pysm::y,pyym::u}},//龥 yu
};
constexpr static PinYin2 s_pinyin2[] = {
{{pysm::d,pyym::ing},{pysm::zh,pyym::eng}},//丁
{{pysm::w,pyym::an},{pysm::m,pyym::o}},//万
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//丌
{{pysm::g,pyym::e},{pysm::g,pyym::an}},//个
{{pysm::g,pyym::uan},{pysm::k,pyym::uang}},//丱
{{pysm::ch,pyym::an},{pysm::ch,pyym::uan}},//丳
{{pysm::j,pyym::ing},{pysm::d,pyym::an}},//丼
{{pysm::p,pyym::ie},{pysm::y,pyym::i}},//丿
{{pysm::y,pyym::i},{pysm::j,pyym::i}},//乁
{{pysm::y,pyym::i},{pysm::nop,pyym::ai}},//乂
{{pysm::n,pyym::ai},{pysm::nop,pyym::ai}},//乃
{{pysm::t,pyym::uo},{pysm::zh,pyym::e}},//乇
{{pysm::zh,pyym::i},{pysm::zh,pyym::u}},//之
{{pysm::zh,pyym::a},{pysm::z,pyym::uo}},//乍
{{pysm::l,pyym::e},{pysm::y,pyym::ue}},//乐
{{pysm::ch,pyym::eng},{pysm::sh,pyym::eng}},//乘
{{pysm::y,pyym::i},{pysm::j,pyym::ue}},//乙
{{pysm::m,pyym::ie},{pysm::n,pyym::ie}},//乜
{{pysm::y,pyym::e},{pysm::y,pyym::i}},//也
{{pysm::q,pyym::ian},{pysm::g,pyym::an}},//乾
{{pysm::zh,pyym::i},{pysm::l,pyym::uan}},//乿
{{pysm::l,pyym::e},{pysm::l,pyym::iao}},//了
{{pysm::y,pyym::u},{pysm::zh,pyym::u}},//予
{{pysm::sh,pyym::i},{pysm::z,pyym::i}},//事
{{pysm::k,pyym::ui},{pysm::y,pyym::u}},//亏
{{pysm::g,pyym::en},{pysm::g,pyym::eng}},//亙
{{pysm::x,pyym::ie},{pysm::s,pyym::uo}},//些
{{pysm::q,pyym::i},{pysm::zh,pyym::ai}},//亝
{{pysm::y,pyym::a},{pysm::nop,pyym::e}},//亞
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//亟
{{pysm::w,pyym::ang},{pysm::w,pyym::u}},//亡
{{pysm::h,pyym::ai},{pysm::j,pyym::ie}},//亥
{{pysm::q,pyym::in},{pysm::q,pyym::ing}},//亲
{{pysm::w,pyym::ei},{pysm::m,pyym::en}},//亹
{{pysm::sh,pyym::en},{pysm::sh,pyym::i}},//什
{{pysm::l,pyym::e},{pysm::l,pyym::i}},//仂
{{pysm::j,pyym::ie},{pysm::g,pyym::e}},//介
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//从
{{pysm::z,pyym::ai},{pysm::z,pyym::i}},//仔
{{pysm::t,pyym::a},{pysm::t,pyym::uo}},//他
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//仠
{{pysm::l,pyym::ing},{pysm::l,pyym::ian}},//令
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//以
{{pysm::ch,pyym::ao},{pysm::m,pyym::iao}},//仯
{{pysm::y,pyym::ang},{pysm::nop,pyym::ang}},//仰
{{pysm::q,pyym::ian},{pysm::j,pyym::ing}},//仱
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//仳
{{pysm::j,pyym::ian},{pysm::m,pyym::ou}},//件
{{pysm::j,pyym::ia},{pysm::j,pyym::ie}},//价
{{pysm::y,pyym::ao},{pysm::f,pyym::o}},//仸
{{pysm::r,pyym::en},{pysm::l,pyym::in}},//任
{{pysm::f,pyym::en},{pysm::b,pyym::in}},//份
{{pysm::f,pyym::ang},{pysm::p,pyym::ang}},//仿
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//伃
{{pysm::x,pyym::in},{pysm::l,pyym::in}},//伈
{{pysm::k,pyym::ang},{pysm::g,pyym::ang}},//伉
{{pysm::j,pyym::i},{pysm::f,pyym::an}},//伋
{{pysm::x,pyym::iu},{pysm::x,pyym::u}},//休
{{pysm::j,pyym::in},{pysm::y,pyym::in}},//伒
{{pysm::zh,pyym::ong},{pysm::y,pyym::in}},//众
{{pysm::h,pyym::ui},{pysm::k,pyym::uai}},//会
{{pysm::ch,pyym::uan},{pysm::zh,pyym::uan}},//传
{{pysm::q,pyym::ian},{pysm::x,pyym::ian}},//伣
{{pysm::c,pyym::ang},{pysm::ch,pyym::en}},//伧
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//伴
{{pysm::q,pyym::u},{pysm::z,pyym::u}},//伹
{{pysm::c,pyym::i},{pysm::s,pyym::i}},//伺
{{pysm::sh,pyym::i},{pysm::s,pyym::i}},//似
{{pysm::d,pyym::ian},{pysm::t,pyym::ian}},//佃
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//佄
{{pysm::q,pyym::u},{pysm::q,pyym::ia}},//佉
{{pysm::zh,pyym::ao},{pysm::sh,pyym::ao}},//佋
{{pysm::w,pyym::ei},{pysm::l,pyym::i}},//位
{{pysm::t,pyym::uo},{pysm::y,pyym::i}},//佗
{{pysm::y,pyym::i},{pysm::d,pyym::ie}},//佚
{{pysm::h,pyym::ui},{pysm::h,pyym::uai}},//佪
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//佫
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//佬
{{pysm::g,pyym::e},{pysm::nop,pyym::e}},//佮
{{pysm::b,pyym::ai},{pysm::m,pyym::o}},//佰
{{pysm::nop,pyym::er},{pysm::n,pyym::ai}},//佴
{{pysm::h,pyym::en},{pysm::h,pyym::eng}},//佷
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//佼
{{pysm::g,pyym::ai},{pysm::h,pyym::ai}},//侅
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//例
{{pysm::zh,pyym::u},{pysm::zh,pyym::ou}},//侏
{{pysm::m,pyym::ou},{pysm::m,pyym::ao}},//侔
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//侗
{{pysm::c,pyym::un},{pysm::j,pyym::ian}},//侟
{{pysm::j,pyym::iao},{pysm::y,pyym::ao}},//侥
{{pysm::ch,pyym::eng},{pysm::t,pyym::ing}},//侱
{{pysm::zh,pyym::en},{pysm::ch,pyym::en}},//侲
{{pysm::sh,pyym::u},{pysm::d,pyym::ou}},//侸
{{pysm::t,pyym::ui},{pysm::t,pyym::uo}},//侻
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//便
{{pysm::c,pyym::u},{pysm::ch,pyym::uo}},//促
{{pysm::x,pyym::u},{pysm::sh,pyym::u}},//俆
{{pysm::l,pyym::iang},{pysm::l,pyym::ang}},//俍
{{pysm::q,pyym::iao},{pysm::x,pyym::iao}},//俏
{{pysm::j,pyym::ing},{pysm::y,pyym::ing}},//俓
{{pysm::q,pyym::ian},{pysm::x,pyym::ian}},//俔
{{pysm::f,pyym::u},{pysm::m,pyym::ian}},//俛
{{pysm::y,pyym::u},{pysm::sh,pyym::u}},//俞
{{pysm::q,pyym::i},{pysm::s,pyym::i}},//俟
{{pysm::x,pyym::in},{pysm::sh,pyym::en}},//信
{{pysm::ch,pyym::e},{pysm::j,pyym::u}},//俥
{{pysm::l,pyym::ia},{pysm::l,pyym::iang}},//俩
{{pysm::f,pyym::eng},{pysm::b,pyym::eng}},//俸
{{pysm::nop,pyym::an},{pysm::y,pyym::an}},//俺
{{pysm::h,pyym::u},{pysm::ch,pyym::i}},//俿
{{pysm::c,pyym::ui},{pysm::z,pyym::u}},//倅
{{pysm::l,pyym::ia},{pysm::l,pyym::iang}},//倆
{{pysm::l,pyym::ai},{pysm::l,pyym::ie}},//倈
{{pysm::c,pyym::ang},{pysm::ch,pyym::uang}},//倉
{{pysm::b,pyym::ei},{pysm::p,pyym::ei}},//倍
{{pysm::t,pyym::an},{pysm::d,pyym::an}},//倓
{{pysm::ch,pyym::ui},{pysm::zh,pyym::ui}},//倕
{{pysm::p,pyym::eng},{pysm::p,pyym::ing}},//倗
{{pysm::t,pyym::ang},{pysm::ch,pyym::ang}},//倘
{{pysm::y,pyym::i},{pysm::j,pyym::i}},//倚
{{pysm::j,pyym::ing},{pysm::l,pyym::iang}},//倞
{{pysm::j,pyym::ie},{pysm::q,pyym::ie}},//倢
{{pysm::q,pyym::ian},{pysm::q,pyym::ing}},//倩
{{pysm::n,pyym::i},{pysm::n,pyym::ie}},//倪
{{pysm::w,pyym::o},{pysm::w,pyym::ei}},//倭
{{pysm::l,pyym::eng},{pysm::l,pyym::ing}},//倰
{{pysm::r,pyym::uan},{pysm::r,pyym::u}},//偄
{{pysm::r,pyym::uo},{pysm::r,pyym::e}},//偌
{{pysm::t,pyym::ang},{pysm::d,pyym::ang}},//偒
{{pysm::x,pyym::ie},{pysm::j,pyym::ie}},//偕
{{pysm::b,pyym::i},{pysm::f,pyym::u}},//偪
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//偬
{{pysm::c,pyym::ai},{pysm::s,pyym::i}},//偲
{{pysm::zh,pyym::en},{pysm::zh,pyym::eng}},//偵
{{pysm::z,pyym::a},{pysm::z,pyym::an}},//偺
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//偻
{{pysm::zh,pyym::i},{pysm::s,pyym::i}},//傂
{{pysm::j,pyym::iang},{pysm::g,pyym::ou}},//傋
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//傔
{{pysm::j,pyym::ue},{pysm::q,pyym::ue}},//傕
{{pysm::y,pyym::ong},{pysm::r,pyym::ong}},//傛
{{pysm::t,pyym::an},{pysm::t,pyym::a}},//傝
{{pysm::j,pyym::ia},{pysm::x,pyym::iang}},//傢
{{pysm::y,pyym::ong},{pysm::ch,pyym::ong}},//傭
{{pysm::z,pyym::ao},{pysm::c,pyym::ao}},//傮
{{pysm::b,pyym::eng},{pysm::p,pyym::eng}},//傰
{{pysm::s,pyym::ong},{pysm::sh,pyym::uang}},//傱
{{pysm::ch,pyym::uan},{pysm::zh,pyym::uan}},//傳
{{pysm::z,pyym::u},{pysm::q,pyym::i}},//傶
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//傿
{{pysm::x,pyym::ie},{pysm::s,pyym::u}},//僁
{{pysm::p,pyym::iao},{pysm::b,pyym::iao}},//僄
{{pysm::l,pyym::u},{pysm::l,pyym::iao}},//僇
{{pysm::t,pyym::an},{pysm::l,pyym::an}},//僋
{{pysm::zh,pyym::uan},{pysm::z,pyym::un}},//僎
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//僑
{{pysm::z,pyym::un},{pysm::c,pyym::uan}},//僔
{{pysm::p,pyym::u},{pysm::b,pyym::u}},//僕
{{pysm::l,pyym::iao},{pysm::l,pyym::ao}},//僚
{{pysm::ch,pyym::an},{pysm::zh,pyym::uan}},//僝
{{pysm::ch,pyym::uan},{pysm::ch,pyym::un}},//僢
{{pysm::t,pyym::ie},{pysm::j,pyym::ian}},//僣
{{pysm::j,pyym::iao},{pysm::y,pyym::ao}},//僥
{{pysm::s,pyym::eng},{pysm::c,pyym::eng}},//僧
{{pysm::j,pyym::u},{pysm::y,pyym::u}},//僪
{{pysm::j,pyym::ian},{pysm::z,pyym::en}},//僭
{{pysm::d,pyym::an},{pysm::sh,pyym::an}},//儋
{{pysm::ch,pyym::ou},{pysm::d,pyym::ao}},//儔
{{pysm::l,pyym::ie},{pysm::l,pyym::a}},//儠
{{pysm::ch,pyym::en},{pysm::q,pyym::in}},//儭
{{pysm::r,pyym::ang},{pysm::x,pyym::iang}},//儴
{{pysm::sh,pyym::u},{pysm::t,pyym::iao}},//儵
{{pysm::h,pyym::ui},{pysm::x,pyym::ie}},//儶
{{pysm::t,pyym::ang},{pysm::ch,pyym::ang}},//儻
{{pysm::l,pyym::ei},{pysm::l,pyym::uo}},//儽
{{pysm::nop,pyym::er},{pysm::r,pyym::en}},//儿
{{pysm::y,pyym::un},{pysm::y,pyym::uan}},//允
{{pysm::x,pyym::iong},{pysm::k,pyym::uang}},//兄
{{pysm::nop,pyym::er},{pysm::n,pyym::i}},//兒
{{pysm::j,pyym::in},{pysm::z,pyym::an}},//兓
{{pysm::t,pyym::u},{pysm::ch,pyym::an}},//兔
{{pysm::l,pyym::iu},{pysm::l,pyym::u}},//六
{{pysm::g,pyym::ong},{pysm::h,pyym::ong}},//共
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//其
{{pysm::d,pyym::ian},{pysm::t,pyym::ian}},//典
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//兹
{{pysm::c,pyym::e},{pysm::zh,pyym::a}},//册
{{pysm::m,pyym::ao},{pysm::m,pyym::o}},//冒
{{pysm::y,pyym::in},{pysm::y,pyym::ou}},//冘
{{pysm::m,pyym::ing},{pysm::m,pyym::ian}},//冥
{{pysm::f,pyym::eng},{pysm::p,pyym::ing}},//冯
{{pysm::b,pyym::ing},{pysm::n,pyym::ing}},//冰
{{pysm::l,pyym::eng},{pysm::l,pyym::ing}},//冷
{{pysm::x,pyym::ian},{pysm::sh,pyym::eng}},//冼
{{pysm::j,pyym::ing},{pysm::ch,pyym::eng}},//净
{{pysm::ch,pyym::uang},{pysm::c,pyym::ang}},//凔
{{pysm::q,pyym::ian},{pysm::k,pyym::an}},//凵
{{pysm::nop,pyym::ao},{pysm::w,pyym::a}},//凹
{{pysm::z,pyym::ao},{pysm::z,pyym::uo}},//凿
{{pysm::d,pyym::ao},{pysm::d,pyym::iao}},//刀
{{pysm::q,pyym::ie},{pysm::q,pyym::i}},//切
{{pysm::l,pyym::ie},{pysm::l,pyym::i}},//列
{{pysm::p,pyym::ao},{pysm::b,pyym::ao}},//刨
{{pysm::k,pyym::u},{pysm::k,pyym::ou}},//刳
{{pysm::q,pyym::uan},{pysm::x,pyym::uan}},//券
{{pysm::sh,pyym::a},{pysm::ch,pyym::a}},//刹
{{pysm::c,pyym::i},{pysm::q,pyym::i}},//刺
{{pysm::k,pyym::e},{pysm::k,pyym::ei}},//刻
{{pysm::l,pyym::ou},{pysm::d,pyym::ou}},//剅
{{pysm::k,pyym::e},{pysm::k,pyym::ei}},//剋
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//前
{{pysm::p,pyym::ou},{pysm::p,pyym::o}},//剖
{{pysm::d,pyym::uo},{pysm::ch,pyym::i}},//剟
{{pysm::q,pyym::ing},{pysm::l,pyym::ve}},//剠
{{pysm::sh,pyym::an},{pysm::y,pyym::an}},//剡
{{pysm::d,pyym::u},{pysm::zh,pyym::uo}},//剢
{{pysm::d,pyym::uo},{pysm::d,pyym::u}},//剫
{{pysm::f,pyym::u},{pysm::p,pyym::i}},//副
{{pysm::d,pyym::a},{pysm::zh,pyym::a}},//剳
{{pysm::k,pyym::ai},{pysm::nop,pyym::ai}},//剴
{{pysm::ch,pyym::uang},{pysm::q,pyym::iang}},//創
{{pysm::t,pyym::uan},{pysm::zh,pyym::uan}},//剸
{{pysm::l,pyym::u},{pysm::j,pyym::iu}},//剹
{{pysm::p,pyym::iao},{pysm::b,pyym::iao}},//剽
{{pysm::j,pyym::iao},{pysm::ch,pyym::ao}},//剿
{{pysm::h,pyym::ua},{pysm::h,pyym::uai}},//劃
{{pysm::j,pyym::iao},{pysm::ch,pyym::ao}},//劋
{{pysm::h,pyym::uo},{pysm::h,pyym::ua}},//劐
{{pysm::j,pyym::ian},{pysm::z,pyym::uan}},//劗
{{pysm::m,pyym::o},{pysm::m,pyym::i}},//劘
{{pysm::x,pyym::ie},{pysm::l,pyym::ie}},//劦
{{pysm::zh,pyym::u},{pysm::ch,pyym::u}},//助
{{pysm::j,pyym::in},{pysm::j,pyym::ing}},//劲
{{pysm::h,pyym::e},{pysm::k,pyym::ai}},//劾
{{pysm::j,pyym::in},{pysm::j,pyym::ing}},//勁
{{pysm::ch,pyym::i},{pysm::l,pyym::ai}},//勑
{{pysm::l,pyym::ei},{pysm::l,pyym::e}},//勒
{{pysm::x,pyym::u},{pysm::m,pyym::ao}},//勖
{{pysm::w,pyym::u},{pysm::m,pyym::ao}},//務
{{pysm::w,pyym::eng},{pysm::y,pyym::ang}},//勜
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//勞
{{pysm::m,pyym::u},{pysm::b,pyym::o}},//募
{{pysm::q,pyym::in},{pysm::q,pyym::i}},//勤
{{pysm::j,pyym::iang},{pysm::q,pyym::iang}},//勥
{{pysm::ch,pyym::ao},{pysm::j,pyym::iao}},//勦
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//勭
{{pysm::r,pyym::ang},{pysm::x,pyym::iang}},//勷
{{pysm::w,pyym::u},{pysm::m,pyym::o}},//勿
{{pysm::y,pyym::un},{pysm::j,pyym::un}},//匀
{{pysm::t,pyym::ao},{pysm::y,pyym::ao}},//匋
{{pysm::b,pyym::i},{pysm::p,pyym::in}},//匕
{{pysm::h,pyym::ua},{pysm::h,pyym::uo}},//化
{{pysm::sh,pyym::i},{pysm::ch,pyym::i}},//匙
{{pysm::k,pyym::uang},{pysm::w,pyym::ang}},//匡
{{pysm::z,pyym::ang},{pysm::c,pyym::ang}},//匨
{{pysm::f,pyym::ei},{pysm::f,pyym::en}},//匪
{{pysm::k,pyym::ui},{pysm::g,pyym::ui}},//匮
{{pysm::g,pyym::ui},{pysm::k,pyym::ui}},//匱
{{pysm::q,pyym::u},{pysm::nop,pyym::ou}},//区
{{pysm::n,pyym::i},{pysm::t,pyym::e}},//匿
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//半
{{pysm::n,pyym::an},{pysm::n,pyym::a}},//南
{{pysm::j,pyym::i},{pysm::ch,pyym::i}},//卙
{{pysm::k,pyym::uang},{pysm::g,pyym::uan}},//卝
{{pysm::b,pyym::ian},{pysm::p,pyym::an}},//卞
{{pysm::b,pyym::u},{pysm::j,pyym::i}},//卟
{{pysm::zh,pyym::an},{pysm::t,pyym::ie}},//占
{{pysm::k,pyym::a},{pysm::q,pyym::ia}},//卡
{{pysm::l,pyym::u},{pysm::x,pyym::i}},//卤
{{pysm::nop,pyym::ang},{pysm::y,pyym::ang}},//卬
{{pysm::y,pyym::in},{pysm::y,pyym::i}},//印
{{pysm::l,pyym::uan},{pysm::k,pyym::un}},//卵
{{pysm::x,pyym::u},{pysm::s,pyym::u}},//卹
{{pysm::w,pyym::ei},{pysm::y,pyym::an}},//厃
{{pysm::zh,pyym::e},{pysm::zh,pyym::ai}},//厇
{{pysm::h,pyym::an},{pysm::nop,pyym::an}},//厈
{{pysm::d,pyym::i},{pysm::zh,pyym::i}},//厎
{{pysm::zh,pyym::a},{pysm::zh,pyym::ai}},//厏
{{pysm::y,pyym::a},{pysm::nop,pyym::ai}},//厓
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//厔
{{pysm::c,pyym::e},{pysm::s,pyym::i}},//厕
{{pysm::p,pyym::ang},{pysm::m,pyym::ang}},//厖
{{pysm::l,pyym::i},{pysm::ch,pyym::an}},//厘
{{pysm::c,pyym::uo},{pysm::j,pyym::i}},//厝
{{pysm::sh,pyym::a},{pysm::x,pyym::ia}},//厦
{{pysm::l,pyym::an},{pysm::q,pyym::ian}},//厱
{{pysm::l,pyym::i},{pysm::l,pyym::ai}},//厲
{{pysm::s,pyym::i},{pysm::m,pyym::ou}},//厶
{{pysm::g,pyym::ong},{pysm::h,pyym::ong}},//厷
{{pysm::l,pyym::in},{pysm::m,pyym::in}},//厸
{{pysm::r,pyym::ou},{pysm::q,pyym::iu}},//厹
{{pysm::zh,pyym::uan},{pysm::h,pyym::ui}},//叀
{{pysm::sh,pyym::i},{pysm::l,pyym::i}},//叓
{{pysm::sh,pyym::ou},{pysm::d,pyym::ao}},//受
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//叚
{{pysm::s,pyym::ou},{pysm::x,pyym::iao}},//叟
{{pysm::g,pyym::u},{pysm::k,pyym::u}},//古
{{pysm::d,pyym::ao},{pysm::t,pyym::ao}},//叨
{{pysm::zh,pyym::ao},{pysm::sh,pyym::ao}},//召
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//叭
{{pysm::k,pyym::e},{pysm::g,pyym::e}},//可
{{pysm::y,pyym::e},{pysm::x,pyym::ie}},//叶
{{pysm::h,pyym::ao},{pysm::x,pyym::iao}},//号
{{pysm::s,pyym::i},{pysm::c,pyym::i}},//司
{{pysm::l,pyym::e},{pysm::l,pyym::i}},//叻
{{pysm::j,pyym::i},{pysm::j,pyym::iao}},//叽
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//吁
{{pysm::ch,pyym::i},{pysm::q,pyym::i}},//吃
{{pysm::x,pyym::uan},{pysm::s,pyym::ong}},//吅
{{pysm::z,pyym::i},{pysm::j,pyym::i}},//吇
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//合
{{pysm::y,pyym::a},{pysm::nop,pyym::a}},//吖
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//吚
{{pysm::t,pyym::un},{pysm::t,pyym::ian}},//吞
{{pysm::y,pyym::in},{pysm::j,pyym::in}},//吟
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//吡
{{pysm::b,pyym::u},{pysm::p,pyym::ou}},//吥
{{pysm::f,pyym::ou},{pysm::p,pyym::i}},//否
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//吧
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//吨
{{pysm::f,pyym::en},{pysm::p,pyym::en}},//吩
{{pysm::nop,pyym::e},{pysm::h,pyym::ua}},//吪
{{pysm::k,pyym::eng},{pysm::h,pyym::ang}},//吭
{{pysm::y,pyym::in},{pysm::sh,pyym::en}},//吲
{{pysm::w,pyym::u},{pysm::y,pyym::u}},//吳
{{pysm::w,pyym::u},{pysm::t,pyym::un}},//吴
{{pysm::ch,pyym::ao},{pysm::m,pyym::iao}},//吵
{{pysm::d,pyym::ou},{pysm::r,pyym::u}},//吺
{{pysm::y,pyym::a},{pysm::x,pyym::ia}},//呀
{{pysm::nop,pyym::e},{pysm::nop,pyym::ai}},//呃
{{pysm::m,pyym::ei},{pysm::w,pyym::en}},//呅
{{pysm::q,pyym::i},{pysm::m,pyym::en}},//呇
{{pysm::ch,pyym::eng},{pysm::k,pyym::uang}},//呈
{{pysm::ch,pyym::i},{pysm::y,pyym::ing}},//呎
{{pysm::w,pyym::u},{pysm::m,pyym::m}},//呒
{{pysm::d,pyym::ai},{pysm::t,pyym::ai}},//呔
{{pysm::b,pyym::ei},{pysm::b,pyym::ai}},//呗
{{pysm::y,pyym::uan},{pysm::y,pyym::un}},//员
{{pysm::w,pyym::en},{pysm::m,pyym::in}},//呡
{{pysm::n,pyym::e},{pysm::n,pyym::i}},//呢
{{pysm::m,pyym::m},{pysm::m,pyym::ou}},//呣
{{pysm::t,pyym::ie},{pysm::ch,pyym::e}},//呫
{{pysm::x,pyym::i},{pysm::ch,pyym::i}},//呬
{{pysm::q,pyym::i},{pysm::zh,pyym::i}},//呮
{{pysm::g,pyym::u},{pysm::g,pyym::ua}},//呱
{{pysm::c,pyym::i},{pysm::z,pyym::i}},//呲
{{pysm::w,pyym::ei},{pysm::m,pyym::ei}},//味
{{pysm::y,pyym::i},{pysm::ch,pyym::i}},//呹
{{pysm::x,pyym::iao},{pysm::h,pyym::ao}},//呺
{{pysm::q,pyym::u},{pysm::k,pyym::a}},//呿
{{pysm::j,pyym::u},{pysm::z,pyym::ui}},//咀
{{pysm::b,pyym::ie},{pysm::b,pyym::i}},//咇
{{pysm::h,pyym::ai},{pysm::t,pyym::ai}},//咍
{{pysm::j,pyym::iu},{pysm::g,pyym::ao}},//咎
{{pysm::k,pyym::a},{pysm::n,pyym::ong}},//咔
{{pysm::g,pyym::uang},{pysm::g,pyym::ong}},//咣
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//咦
{{pysm::y,pyym::ao},{pysm::j,pyym::iao}},//咬
{{pysm::sh,pyym::u},{pysm::x,pyym::un}},//咰
{{pysm::z,pyym::an},{pysm::z,pyym::a}},//咱
{{pysm::h,pyym::ui},{pysm::h,pyym::ai}},//咴
{{pysm::t,pyym::ao},{pysm::t,pyym::iao}},//咷
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//咸
{{pysm::x,pyym::iong},{pysm::h,pyym::ong}},//哅
{{pysm::d,pyym::ie},{pysm::d,pyym::i}},//哋
{{pysm::p,pyym::ai},{pysm::g,pyym::u}},//哌
{{pysm::k,pyym::uang},{pysm::q,pyym::iang}},//哐
{{pysm::h,pyym::ui},{pysm::y,pyym::ue}},//哕
{{pysm::y,pyym::uan},{pysm::y,pyym::un}},//員
{{pysm::nop,pyym::o},{pysm::nop,pyym::e}},//哦
{{pysm::x,pyym::iao},{pysm::x,pyym::ue}},//哮
{{pysm::l,pyym::iang},{pysm::l,pyym::ang}},//哴
{{pysm::l,pyym::ie},{pysm::l,pyym::v}},//哷
{{pysm::b,pyym::u},{pysm::f,pyym::u}},//哺
{{pysm::h,pyym::eng},{pysm::h,pyym::ng}},//哼
{{pysm::sh,pyym::uo},{pysm::y,pyym::ue}},//哾
{{pysm::b,pyym::ei},{pysm::b,pyym::ai}},//唄
{{pysm::s,pyym::uo},{pysm::sh,pyym::ua}},//唆
{{pysm::ch,pyym::un},{pysm::zh,pyym::en}},//唇
{{pysm::j,pyym::ia},{pysm::q,pyym::ian}},//唊
{{pysm::x,pyym::i},{pysm::x,pyym::ie}},//唏
{{pysm::z,pyym::uo},{pysm::sh,pyym::i}},//唑
{{pysm::m,pyym::a},{pysm::m,pyym::ai}},//唛
{{pysm::g,pyym::ong},{pysm::h,pyym::ong}},//唝
{{pysm::l,pyym::iang},{pysm::y,pyym::ing}},//唡
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//唧
{{pysm::w,pyym::o},{pysm::w,pyym::ei}},//唩
{{pysm::f,pyym::eng},{pysm::b,pyym::eng}},//唪
{{pysm::j,pyym::in},{pysm::y,pyym::in}},//唫
{{pysm::sh,pyym::ou},{pysm::sh,pyym::u}},//售
{{pysm::nop,pyym::er},{pysm::w,pyym::a}},//唲
{{pysm::z,pyym::e},{pysm::j,pyym::ie}},//唶
{{pysm::y,pyym::o},{pysm::y,pyym::u}},//唷
{{pysm::n,pyym::ian},{pysm::d,pyym::ian}},//唸
{{pysm::sh,pyym::a},{pysm::q,pyym::ie}},//唼
{{pysm::zh,pyym::uo},{pysm::zh,pyym::ou}},//啄
{{pysm::zh,pyym::uo},{pysm::zh,pyym::ao}},//啅
{{pysm::nop,pyym::a},{pysm::nop,pyym::e}},//啊
{{pysm::c,pyym::ai},{pysm::x,pyym::iao}},//啋
{{pysm::x,pyym::iang},{pysm::q,pyym::iang}},//啌
{{pysm::y,pyym::e},{pysm::w,pyym::a}},//啘
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//啙
{{pysm::b,pyym::i},{pysm::t,pyym::u}},//啚
{{pysm::y,pyym::a},{pysm::nop,pyym::e}},//啞
{{pysm::l,pyym::iang},{pysm::y,pyym::ing}},//啢
{{pysm::y,pyym::ing},{pysm::q,pyym::ing}},//啨
{{pysm::q,pyym::uan},{pysm::j,pyym::ue}},//啳
{{pysm::ch,pyym::an},{pysm::t,pyym::an}},//啴
{{pysm::ch,pyym::i},{pysm::d,pyym::i}},//啻
{{pysm::k,pyym::a},{pysm::k,pyym::e}},//喀
{{pysm::y,pyym::ong},{pysm::y,pyym::u}},//喁
{{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//喈
{{pysm::n,pyym::uo},{pysm::r,pyym::e}},//喏
{{pysm::z,pyym::a},{pysm::z,pyym::an}},//喒
{{pysm::h,pyym::ui},{pysm::zh,pyym::ou}},//喙
{{pysm::x,pyym::i},{pysm::ch,pyym::i}},//喜
{{pysm::k,pyym::ui},{pysm::h,pyym::uai}},//喟
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//喠
{{pysm::sh,pyym::a},{pysm::ch,pyym::e}},//喢
{{pysm::d,pyym::uo},{pysm::zh,pyym::a}},//喥
{{pysm::n,pyym::ie},{pysm::y,pyym::i}},//喦
{{pysm::ch,pyym::i},{pysm::k,pyym::ai}},//喫
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//喬
{{pysm::p,pyym::en},{pysm::b,pyym::en}},//喯
{{pysm::zh,pyym::a},{pysm::ch,pyym::a}},//喳
{{pysm::z,pyym::ao},{pysm::q,pyym::iao}},//喿
{{pysm::q,pyym::iang},{pysm::ch,pyym::eng}},//嗆
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//嗊
{{pysm::s,pyym::uo},{pysm::sh,pyym::uo}},//嗍
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//嗒
{{pysm::ch,pyym::en},{pysm::t,pyym::ian}},//嗔
{{pysm::s,pyym::ou},{pysm::s,pyym::u}},//嗖
{{pysm::w,pyym::a},{pysm::g,pyym::u}},//嗗
{{pysm::j,pyym::ie},{pysm::j,pyym::ue}},//嗟
{{pysm::h,pyym::ai},{pysm::h,pyym::ei}},//嗨
{{pysm::nop,pyym::en},{pysm::n,pyym::g}},//嗯
{{pysm::d,pyym::ie},{pysm::d,pyym::ia}},//嗲
{{pysm::z,pyym::ui},{pysm::s,pyym::ui}},//嗺
{{pysm::zh,pyym::e},{pysm::zh,pyym::u}},//嗻
{{pysm::d,pyym::i},{pysm::zh,pyym::e}},//嘀
{{pysm::j,pyym::iao},{pysm::d,pyym::ao}},//嘄
{{pysm::k,pyym::ai},{pysm::g,pyym::e}},//嘅
{{pysm::g,pyym::u},{pysm::j,pyym::ia}},//嘏
{{pysm::x,pyym::u},{pysm::sh,pyym::i}},//嘘
{{pysm::l,pyym::ei},{pysm::l,pyym::e}},//嘞
{{pysm::ch,pyym::uai},{pysm::z,pyym::uo}},//嘬
{{pysm::x,pyym::iao},{pysm::ch,pyym::i}},//嘯
{{pysm::ch,pyym::ao},{pysm::zh,pyym::ao}},//嘲
{{pysm::d,pyym::an},{pysm::t,pyym::an}},//嘾
{{pysm::f,pyym::an},{pysm::b,pyym::o}},//噃
{{pysm::z,pyym::an},{pysm::c,pyym::an}},//噆
{{pysm::t,pyym::un},{pysm::k,pyym::uo}},//噋
{{pysm::c,pyym::eng},{pysm::ch,pyym::eng}},//噌
{{pysm::j,pyym::iao},{pysm::j,pyym::iu}},//噍
{{pysm::zh,pyym::an},{pysm::d,pyym::an}},//噡
{{pysm::n,pyym::ong},{pysm::n,pyym::ang}},//噥
{{pysm::y,pyym::ue},{pysm::h,pyym::ui}},//噦
{{pysm::y,pyym::i},{pysm::nop,pyym::ai}},//噫
{{pysm::j,pyym::ue},{pysm::x,pyym::ue}},//噱
{{pysm::p,pyym::en},{pysm::f,pyym::en}},//噴
{{pysm::g,pyym::a},{pysm::g,pyym::e}},//噶
{{pysm::l,pyym::an},{pysm::h,pyym::an}},//嚂
{{pysm::x,pyym::ia},{pysm::h,pyym::e}},//嚇
{{pysm::ch,pyym::ou},{pysm::zh,pyym::ou}},//嚋
{{pysm::c,pyym::a},{pysm::ch,pyym::a}},//嚓
{{pysm::t,pyym::i},{pysm::zh,pyym::i}},//嚔
{{pysm::n,pyym::ie},{pysm::y,pyym::ao}},//嚙
{{pysm::h,pyym::u},{pysm::y,pyym::o}},//嚛
{{pysm::x,pyym::iao},{pysm::nop,pyym::ao}},//嚣
{{pysm::h,pyym::uo},{pysm::x,pyym::ue}},//嚯
{{pysm::j,pyym::ue},{pysm::j,pyym::iao}},//嚼
{{pysm::n,pyym::ie},{pysm::zh,pyym::e}},//囁
{{pysm::x,pyym::iao},{pysm::nop,pyym::ao}},//囂
{{pysm::w,pyym::ei},{pysm::g,pyym::uo}},//囗
{{pysm::n,pyym::an},{pysm::n,pyym::ie}},//囡
{{pysm::t,pyym::uan},{pysm::q,pyym::iu}},//团
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//囤
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//园
{{pysm::c,pyym::ong},{pysm::ch,pyym::uang}},//囱
{{pysm::h,pyym::un},{pysm::h,pyym::uan}},//圂
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//圈
{{pysm::ch,pyym::uan},{pysm::ch,pyym::ui}},//圌
{{pysm::t,pyym::uan},{pysm::ch,pyym::uan}},//團
{{pysm::h,pyym::uan},{pysm::y,pyym::uan}},//圜
{{pysm::sh,pyym::eng},{pysm::k,pyym::u}},//圣
{{pysm::g,pyym::e},{pysm::y,pyym::i}},//圪
{{pysm::d,pyym::i},{pysm::d,pyym::e}},//地
{{pysm::q,pyym::ian},{pysm::s,pyym::u}},//圱
{{pysm::q,pyym::i},{pysm::y,pyym::in}},//圻
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//圾
{{pysm::m,pyym::ei},{pysm::f,pyym::en}},//坆
{{pysm::j,pyym::un},{pysm::y,pyym::un}},//均
{{pysm::r,pyym::ong},{pysm::k,pyym::eng}},//坈
{{pysm::t,pyym::un},{pysm::d,pyym::un}},//坉
{{pysm::b,pyym::en},{pysm::f,pyym::en}},//坋
{{pysm::k,pyym::eng},{pysm::k,pyym::ang}},//坑
{{pysm::j,pyym::ing},{pysm::x,pyym::ing}},//坓
{{pysm::d,pyym::i},{pysm::l,pyym::an}},//坔
{{pysm::k,pyym::uai},{pysm::y,pyym::ue}},//块
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//坢
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//坥
{{pysm::t,pyym::uo},{pysm::y,pyym::i}},//坨
{{pysm::d,pyym::ian},{pysm::zh,pyym::en}},//坫
{{pysm::g,pyym::ua},{pysm::w,pyym::a}},//坬
{{pysm::p,pyym::i},{pysm::h,pyym::uai}},//坯
{{pysm::nop,pyym::ao},{pysm::y,pyym::ou}},//坳
{{pysm::m,pyym::u},{pysm::m,pyym::ei}},//坶
{{pysm::k,pyym::e},{pysm::j,pyym::iong}},//坷
{{pysm::ch,pyym::i},{pysm::d,pyym::i}},//坻
{{pysm::ch,pyym::ui},{pysm::zh,pyym::ui}},//垂
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//垌
{{pysm::y,pyym::in},{pysm::k,pyym::en}},//垠
{{pysm::k,pyym::en},{pysm::y,pyym::in}},//垦
{{pysm::sh,pyym::ang},{pysm::j,pyym::iong}},//垧
{{pysm::nop,pyym::e},{pysm::sh,pyym::eng}},//垩
{{pysm::y,pyym::uan},{pysm::h,pyym::uan}},//垸
{{pysm::b,pyym::a},{pysm::b,pyym::ei}},//垻
{{pysm::h,pyym::an},{pysm::nop,pyym::an}},//垾
{{pysm::nop,pyym::ai},{pysm::zh,pyym::i}},//埃
{{pysm::b,pyym::eng},{pysm::f,pyym::eng}},//埄
{{pysm::f,pyym::ang},{pysm::d,pyym::i}},//埅
{{pysm::q,pyym::ue},{pysm::j,pyym::ue}},//埆
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//埉
{{pysm::m,pyym::ai},{pysm::m,pyym::an}},//埋
{{pysm::sh,pyym::an},{pysm::y,pyym::an}},//埏
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//埐
{{pysm::p,pyym::u},{pysm::b,pyym::u}},//埔
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//埢
{{pysm::s,pyym::ui},{pysm::s,pyym::u}},//埣
{{pysm::q,pyym::ing},{pysm::zh,pyym::eng}},//埥
{{pysm::zh,pyym::eng},{pysm::ch,pyym::eng}},//埩
{{pysm::nop,pyym::an},{pysm::y,pyym::an}},//埯
{{pysm::ch,pyym::u},{pysm::t,pyym::ou}},//埱
{{pysm::b,pyym::eng},{pysm::b,pyym::ang}},//埲
{{pysm::k,pyym::an},{pysm::x,pyym::ian}},//埳
{{pysm::y,pyym::i},{pysm::sh,pyym::i}},//埶
{{pysm::n,pyym::i},{pysm::b,pyym::an}},//埿
{{pysm::d,pyym::ui},{pysm::z,pyym::ui}},//堆
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//堇
{{pysm::nop,pyym::e},{pysm::y,pyym::a}},//堊
{{pysm::d,pyym::uo},{pysm::h,pyym::ui}},//堕
{{pysm::g,pyym::uo},{pysm::w,pyym::o}},//堝
{{pysm::r,pyym::uan},{pysm::n,pyym::uo}},//堧
{{pysm::k,pyym::an},{pysm::ch,pyym::en}},//堪
{{pysm::b,pyym::ao},{pysm::f,pyym::u}},//報
{{pysm::c,pyym::i},{pysm::j,pyym::i}},//堲
{{pysm::d,pyym::u},{pysm::zh,pyym::e}},//堵
{{pysm::y,pyym::in},{pysm::p,pyym::ou}},//堷
{{pysm::x,pyym::iang},{pysm::j,pyym::iang}},//塂
{{pysm::j,pyym::i},{pysm::x,pyym::i}},//塈
{{pysm::t,pyym::a},{pysm::d,pyym::a}},//塌
{{pysm::t,pyym::a},{pysm::d,pyym::a}},//塔
{{pysm::t,pyym::u},{pysm::d,pyym::u}},//塗
{{pysm::q,pyym::ue},{pysm::q,pyym::iao}},//塙
{{pysm::zh,pyym::ong},{pysm::p,pyym::eng}},//塜
{{pysm::s,pyym::ai},{pysm::s,pyym::e}},//塞
{{pysm::ch,pyym::ang},{pysm::sh,pyym::ang}},//塲
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//塹
{{pysm::zh,pyym::uan},{pysm::t,pyym::uan}},//塼
{{pysm::sh,pyym::u},{pysm::y,pyym::e}},//墅
{{pysm::zh,pyym::i},{pysm::d,pyym::i}},//墆
{{pysm::zh,pyym::i},{pysm::zh,pyym::uo}},//墌
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//墐
{{pysm::z,pyym::eng},{pysm::c,pyym::eng}},//增
{{pysm::sh,pyym::an},{pysm::ch,pyym::an}},//墠
{{pysm::b,pyym::a},{pysm::f,pyym::ei}},//墢
{{pysm::k,pyym::uai},{pysm::t,pyym::ui}},//墤
{{pysm::d,pyym::ong},{pysm::t,pyym::uan}},//墥
{{pysm::q,pyym::ue},{pysm::q,pyym::iao}},//墧
{{pysm::m,pyym::o},{pysm::m,pyym::ei}},//墨
{{pysm::z,pyym::un},{pysm::c,pyym::un}},//墫
{{pysm::d,pyym::uo},{pysm::h,pyym::ui}},//墮
{{pysm::m,pyym::u},{pysm::w,pyym::u}},//墲
{{pysm::q,pyym::iao},{pysm::nop,pyym::ao}},//墽
{{pysm::y,pyym::i},{pysm::t,pyym::u}},//墿
{{pysm::y,pyym::ong},{pysm::w,pyym::eng}},//壅
{{pysm::x,pyym::ian},{pysm::l,pyym::an}},//壏
{{pysm::h,pyym::e},{pysm::h,pyym::uo}},//壑
{{pysm::l,pyym::ei},{pysm::l,pyym::v}},//壘
{{pysm::h,pyym::uai},{pysm::h,pyym::ui}},//壞
{{pysm::sh,pyym::eng},{pysm::q,pyym::ing}},//声
{{pysm::k,pyym::e},{pysm::q,pyym::iao}},//壳
{{pysm::y,pyym::i},{pysm::y,pyym::in}},//壹
{{pysm::zh,pyym::i},{pysm::zh,pyym::ong}},//夂
{{pysm::g,pyym::u},{pysm::y,pyym::ing}},//夃
{{pysm::f,pyym::eng},{pysm::p,pyym::ang}},//夆
{{pysm::x,pyym::ia},{pysm::j,pyym::ia}},//夏
{{pysm::x,pyym::iong},{pysm::x,pyym::uan}},//夐
{{pysm::x,pyym::i},{pysm::y,pyym::i}},//夕
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//夗
{{pysm::m,pyym::ao},{pysm::w,pyym::an}},//夘
{{pysm::t,pyym::ai},{pysm::t,pyym::a}},//太
{{pysm::g,pyym::uai},{pysm::j,pyym::ue}},//夬
{{pysm::y,pyym::ang},{pysm::y,pyym::ing}},//央
{{pysm::h,pyym::ang},{pysm::b,pyym::en}},//夯
{{pysm::sh,pyym::i},{pysm::y,pyym::i}},//失
{{pysm::t,pyym::ao},{pysm::b,pyym::en}},//夲
{{pysm::y,pyym::an},{pysm::t,pyym::ao}},//夵
{{pysm::j,pyym::ia},{pysm::g,pyym::a}},//夹
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//奃
{{pysm::f,pyym::en},{pysm::k,pyym::ang}},//奋
{{pysm::z,pyym::ou},{pysm::c,pyym::ou}},//奏
{{pysm::b,pyym::en},{pysm::f,pyym::en}},//奔
{{pysm::z,pyym::ang},{pysm::zh,pyym::uang}},//奘
{{pysm::b,pyym::eng},{pysm::k,pyym::eng}},//奟
{{pysm::nop,pyym::ao},{pysm::x,pyym::iao}},//奡
{{pysm::d,pyym::uo},{pysm::d,pyym::ui}},//奪
{{pysm::d,pyym::uo},{pysm::ch,pyym::e}},//奲
{{pysm::n,pyym::v},{pysm::r,pyym::u}},//女
{{pysm::d,pyym::ing},{pysm::t,pyym::ian}},//奵
{{pysm::j,pyym::ian},{pysm::g,pyym::an}},//奸
{{pysm::sh,pyym::uo},{pysm::y,pyym::ue}},//妁
{{pysm::f,pyym::ei},{pysm::p,pyym::ei}},//妃
{{pysm::f,pyym::u},{pysm::y,pyym::ou}},//妋
{{pysm::h,pyym::ai},{pysm::j,pyym::ie}},//妎
{{pysm::k,pyym::eng},{pysm::h,pyym::ang}},//妔
{{pysm::y,pyym::ao},{pysm::j,pyym::iao}},//妖
{{pysm::j,pyym::in},{pysm::x,pyym::ian}},//妗
{{pysm::y,pyym::ue},{pysm::j,pyym::ue}},//妜
{{pysm::n,pyym::iu},{pysm::h,pyym::ao}},//妞
{{pysm::n,pyym::a},{pysm::n,pyym::an}},//妠
{{pysm::w,pyym::an},{pysm::y,pyym::uan}},//妧
{{pysm::b,pyym::a},{pysm::b,pyym::o}},//妭
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ou}},//妯
{{pysm::n,pyym::i},{pysm::n,pyym::ai}},//妳
{{pysm::zh,pyym::i},{pysm::y,pyym::i}},//妷
{{pysm::x,pyym::ing},{pysm::sh,pyym::eng}},//姓
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//姕
{{pysm::h,pyym::ua},{pysm::h,pyym::uo}},//姡
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//姣
{{pysm::l,pyym::ao},{pysm::m,pyym::u}},//姥
{{pysm::j,pyym::i},{pysm::zh,pyym::en}},//姫
{{pysm::j,pyym::i},{pysm::y,pyym::i}},//姬
{{pysm::k,pyym::ua},{pysm::h,pyym::u}},//姱
{{pysm::nop,pyym::e},{pysm::y,pyym::a}},//姶
{{pysm::sh,pyym::en},{pysm::x,pyym::ian}},//姺
{{pysm::g,pyym::ui},{pysm::w,pyym::a}},//姽
{{pysm::w,pyym::a},{pysm::g,pyym::ui}},//娃
{{pysm::p,pyym::ing},{pysm::p,pyym::in}},//娉
{{pysm::x,pyym::ian},{pysm::d,pyym::an}},//娊
{{pysm::ch,pyym::eng},{pysm::sh,pyym::eng}},//娍
{{pysm::ch,pyym::uo},{pysm::c,pyym::u}},//娖
{{pysm::t,pyym::ing},{pysm::t,pyym::ian}},//娗
{{pysm::n,pyym::a},{pysm::n,pyym::uo}},//娜
{{pysm::p,pyym::ou},{pysm::b,pyym::i}},//娝
{{pysm::n,pyym::ei},{pysm::s,pyym::ui}},//娞
{{pysm::w,pyym::u},{pysm::y,pyym::u}},//娪
{{pysm::nop,pyym::ai},{pysm::x,pyym::i}},//娭
{{pysm::zh,pyym::ui},{pysm::sh,pyym::ui}},//娷
{{pysm::nop,pyym::ai},{pysm::nop,pyym::e}},//娾
{{pysm::f,pyym::an},{pysm::f,pyym::u}},//婏
{{pysm::j,pyym::ie},{pysm::q,pyym::ie}},//婕
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//婘
{{pysm::q,pyym::ian},{pysm::j,pyym::in}},//婜
{{pysm::w,pyym::an},{pysm::g,pyym::uan}},//婠
{{pysm::ch,pyym::ou},{pysm::zh,pyym::ou}},//婤
{{pysm::n,pyym::ao},{pysm::ch,pyym::uo}},//婥
{{pysm::nop,pyym::an},{pysm::n,pyym::ve}},//婩
{{pysm::k,pyym::un},{pysm::h,pyym::un}},//婫
{{pysm::d,pyym::ang},{pysm::y,pyym::ang}},//婸
{{pysm::ch,pyym::uo},{pysm::r,pyym::uo}},//婼
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//媂
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//媐
{{pysm::t,pyym::ou},{pysm::y,pyym::u}},//媮
{{pysm::ch,pyym::u},{pysm::z,pyym::ou}},//媰
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//媲
{{pysm::y,pyym::ing},{pysm::sh,pyym::eng}},//媵
{{pysm::k,pyym::ui},{pysm::ch,pyym::ou}},//媿
{{pysm::q,pyym::in},{pysm::sh,pyym::en}},//嫀
{{pysm::j,pyym::ie},{pysm::s,pyym::uo}},//嫅
{{pysm::m,pyym::ing},{pysm::m,pyym::eng}},//嫇
{{pysm::y,pyym::ing},{pysm::x,pyym::ing}},//嫈
{{pysm::p,pyym::ang},{pysm::b,pyym::ang}},//嫎
{{pysm::p,pyym::iao},{pysm::b,pyym::iao}},//嫖
{{pysm::y,pyym::u},{pysm::k,pyym::ou}},//嫗
{{pysm::m,pyym::an},{pysm::y,pyym::uan}},//嫚
{{pysm::g,pyym::ui},{pysm::z,pyym::ui}},//嫢
{{pysm::zh,pyym::uan},{pysm::t,pyym::uan}},//嫥
{{pysm::z,pyym::e},{pysm::c,pyym::e}},//嫧
{{pysm::h,pyym::an},{pysm::n,pyym::an}},//嫨
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//嫶
{{pysm::l,pyym::iao},{pysm::l,pyym::ao}},//嫽
{{pysm::r,pyym::ao},{pysm::y,pyym::ao}},//嬈
{{pysm::f,pyym::an},{pysm::f,pyym::u}},//嬎
{{pysm::sh,pyym::an},{pysm::ch,pyym::an}},//嬗
{{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//嬥
{{pysm::r,pyym::u},{pysm::n,pyym::ou}},//嬬
{{pysm::m,pyym::a},{pysm::m,pyym::o}},//嬷
{{pysm::n,pyym::iang},{pysm::r,pyym::ang}},//孃
{{pysm::q,pyym::ian},{pysm::x,pyym::ian}},//孅
{{pysm::h,pyym::ui},{pysm::x,pyym::ie}},//孈
{{pysm::q,pyym::uan},{pysm::h,pyym::uan}},//孉
{{pysm::l,pyym::uan},{pysm::l,pyym::ian}},//孌
{{pysm::m,pyym::a},{pysm::z,pyym::i}},//孖
{{pysm::b,pyym::ei},{pysm::b,pyym::o}},//孛
{{pysm::zh,pyym::uan},{pysm::n,pyym::i}},//孨
{{pysm::s,pyym::un},{pysm::x,pyym::un}},//孫
{{pysm::n,pyym::i},{pysm::y,pyym::i}},//孴
{{pysm::n,pyym::ing},{pysm::zh,pyym::u}},//宁
{{pysm::t,pyym::u},{pysm::j,pyym::ia}},//宊
{{pysm::w,pyym::an},{pysm::k,pyym::uan}},//完
{{pysm::m,pyym::i},{pysm::f,pyym::u}},//宓
{{pysm::k,pyym::e},{pysm::q,pyym::ia}},//客
{{pysm::x,pyym::ian},{pysm::x,pyym::iong}},//宪
{{pysm::b,pyym::ao},{pysm::sh,pyym::i}},//宲
{{pysm::h,pyym::ai},{pysm::h,pyym::e}},//害
{{pysm::r,pyym::ong},{pysm::y,pyym::ong}},//容
{{pysm::zh,pyym::i},{pysm::t,pyym::ian}},//寘
{{pysm::ch,pyym::a},{pysm::c,pyym::ui}},//察
{{pysm::sh,pyym::i},{pysm::zh,pyym::i}},//實
{{pysm::sh,pyym::en},{pysm::p,pyym::an}},//審
{{pysm::h,pyym::uan},{pysm::x,pyym::ian}},//寰
{{pysm::ch,pyym::ong},{pysm::l,pyym::ong}},//寵
{{pysm::s,pyym::i},{pysm::sh,pyym::i}},//寺
{{pysm::x,pyym::un},{pysm::x,pyym::in}},//寻
{{pysm::l,pyym::v},{pysm::l,pyym::ve}},//寽
{{pysm::f,pyym::eng},{pysm::b,pyym::ian}},//封
{{pysm::k,pyym::e},{pysm::k,pyym::ei}},//尅
{{pysm::j,pyym::iang},{pysm::q,pyym::iang}},//将
{{pysm::x,pyym::un},{pysm::x,pyym::in}},//尋
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//尌
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//尐
{{pysm::sh,pyym::ang},{pysm::ch,pyym::ang}},//尚
{{pysm::y,pyym::ou},{pysm::w,pyym::ang}},//尢
{{pysm::l,pyym::iao},{pysm::n,pyym::iao}},//尥
{{pysm::t,pyym::ui},{pysm::zh,pyym::uai}},//尵
{{pysm::y,pyym::in},{pysm::y,pyym::un}},//尹
{{pysm::ch,pyym::i},{pysm::ch,pyym::e}},//尺
{{pysm::w,pyym::ei},{pysm::y,pyym::i}},//尾
{{pysm::n,pyym::iao},{pysm::s,pyym::ui}},//尿
{{pysm::j,pyym::u},{pysm::j,pyym::i}},//居
{{pysm::sh,pyym::i},{pysm::x,pyym::i}},//屎
{{pysm::p,pyym::ing},{pysm::b,pyym::ing}},//屏
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//属
{{pysm::x,pyym::ie},{pysm::t,pyym::i}},//屟
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//屬
{{pysm::ch,pyym::e},{pysm::c,pyym::ao}},//屮
{{pysm::t,pyym::un},{pysm::zh,pyym::un}},//屯
{{pysm::nop,pyym::e},{pysm::y,pyym::an}},//屵
{{pysm::l,pyym::ong},{pysm::h,pyym::ong}},//屸
{{pysm::y,pyym::i},{pysm::g,pyym::e}},//屹
{{pysm::h,pyym::an},{pysm::nop,pyym::an}},//屽
{{pysm::q,pyym::i},{pysm::k,pyym::ai}},//岂
{{pysm::y,pyym::a},{pysm::x,pyym::ia}},//岈
{{pysm::nop,pyym::e},{pysm::j,pyym::i}},//岋
{{pysm::f,pyym::en},{pysm::ch,pyym::a}},//岎
{{pysm::b,pyym::a},{pysm::k,pyym::e}},//峇
{{pysm::f,pyym::u},{pysm::n,pyym::ie}},//峊
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//峒
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//峙
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//峛
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//峤
{{pysm::x,pyym::ie},{pysm::y,pyym::e}},//峫
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//峿
{{pysm::q,pyym::i},{pysm::y,pyym::i}},//崎
{{pysm::z,pyym::u},{pysm::c,pyym::ui}},//崒
{{pysm::l,pyym::eng},{pysm::l,pyym::ing}},//崚
{{pysm::j,pyym::ue},{pysm::y,pyym::u}},//崛
{{pysm::x,pyym::iao},{pysm::y,pyym::ao}},//崤
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//崥
{{pysm::k,pyym::u},{pysm::j,pyym::ue}},//崫
{{pysm::w,pyym::ai},{pysm::w,pyym::ei}},//崴
{{pysm::y,pyym::ang},{pysm::d,pyym::ang}},//崵
{{pysm::sh,pyym::i},{pysm::d,pyym::ie}},//崼
{{pysm::k,pyym::an},{pysm::zh,pyym::an}},//嵁
{{pysm::j,pyym::i},{pysm::x,pyym::i}},//嵇
{{pysm::sh,pyym::eng},{pysm::ch,pyym::eng}},//嵊
{{pysm::w,pyym::u},{pysm::m,pyym::ao}},//嵍
{{pysm::k,pyym::e},{pysm::j,pyym::ie}},//嵑
{{pysm::y,pyym::an},{pysm::n,pyym::ie}},//嵒
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//嵣
{{pysm::r,pyym::ong},{pysm::y,pyym::ing}},//嵤
{{pysm::k,pyym::ai},{pysm::nop,pyym::ai}},//嵦
{{pysm::q,pyym::iao},{pysm::k,pyym::ao}},//嵪
{{pysm::c,pyym::uo},{pysm::c,pyym::i}},//嵯
{{pysm::l,pyym::iao},{pysm::j,pyym::iao}},//嵺
{{pysm::d,pyym::ie},{pysm::d,pyym::i}},//嵽
{{pysm::c,pyym::en},{pysm::c,pyym::an}},//嵾
{{pysm::zh,pyym::an},{pysm::ch,pyym::an}},//嶄
{{pysm::c,pyym::ui},{pysm::z,pyym::ui}},//嶉
{{pysm::p,pyym::ei},{pysm::p,pyym::i}},//嶏
{{pysm::c,pyym::eng},{pysm::zh,pyym::eng}},//嶒
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//嶜
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//嶠
{{pysm::g,pyym::ui},{pysm::j,pyym::ue}},//嶡
{{pysm::zh,pyym::an},{pysm::sh,pyym::an}},//嶦
{{pysm::x,pyym::ian},{pysm::y,pyym::an}},//嶮
{{pysm::x,pyym::ie},{pysm::j,pyym::ie}},//嶰
{{pysm::y,pyym::i},{pysm::n,pyym::i}},//嶷
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//嶼
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//巁
{{pysm::k,pyym::ui},{pysm::w,pyym::ei}},//巋
{{pysm::k,pyym::ui},{pysm::n,pyym::ao}},//巙
{{pysm::ch,pyym::uan},{pysm::sh,pyym::un}},//巛
{{pysm::k,pyym::uai},{pysm::h,pyym::uan}},//巜
{{pysm::j,pyym::ing},{pysm::x,pyym::ing}},//巠
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//巨
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//己
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//已
{{pysm::s,pyym::i},{pysm::y,pyym::i}},//巳
{{pysm::x,pyym::iang},{pysm::h,pyym::ang}},//巷
{{pysm::x,pyym::un},{pysm::zh,pyym::uan}},//巽
{{pysm::f,pyym::u},{pysm::p,pyym::o}},//巿
{{pysm::b,pyym::i},{pysm::y,pyym::in}},//币
{{pysm::sh,pyym::i},{pysm::f,pyym::u}},//市
{{pysm::t,pyym::ang},{pysm::n,pyym::u}},//帑
{{pysm::m,pyym::o},{pysm::w,pyym::a}},//帓
{{pysm::p,pyym::ei},{pysm::p,pyym::i}},//帔
{{pysm::p,pyym::a},{pysm::m,pyym::o}},//帕
{{pysm::b,pyym::o},{pysm::f,pyym::u}},//帗
{{pysm::l,pyym::ian},{pysm::ch,pyym::en}},//帘
{{pysm::zh,pyym::en},{pysm::zh,pyym::eng}},//帧
{{pysm::ch,pyym::ou},{pysm::d,pyym::ao}},//帱
{{pysm::s,pyym::an},{pysm::j,pyym::ian}},//帴
{{pysm::sh,pyym::a},{pysm::q,pyym::ie}},//帹
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//帺
{{pysm::f,pyym::u},{pysm::b,pyym::i}},//幅
{{pysm::y,pyym::i},{pysm::k,pyym::ai}},//幆
{{pysm::m,pyym::u},{pysm::m,pyym::an}},//幕
{{pysm::z,pyym::e},{pysm::c,pyym::e}},//幘
{{pysm::h,pyym::u},{pysm::w,pyym::u}},//幠
{{pysm::ch,pyym::uang},{pysm::zh,pyym::uang}},//幢
{{pysm::ch,pyym::ou},{pysm::d,pyym::ao}},//幬
{{pysm::g,pyym::an},{pysm::nop,pyym::an}},//干
{{pysm::n,pyym::ian},{pysm::n,pyym::ing}},//年
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//幵
{{pysm::x,pyym::ing},{pysm::n,pyym::ie}},//幸
{{pysm::y,pyym::ao},{pysm::m,pyym::i}},//幺
{{pysm::y,pyym::ou},{pysm::y,pyym::ao}},//幼
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//幾
{{pysm::zh,pyym::uang},{pysm::p,pyym::eng}},//庄
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//庇
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//庉
{{pysm::d,pyym::i},{pysm::d,pyym::e}},//底
{{pysm::m,pyym::ang},{pysm::m,pyym::eng}},//庬
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//庳
{{pysm::sh,pyym::a},{pysm::x,pyym::ia}},//廈
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//廑
{{pysm::x,pyym::in},{pysm::q,pyym::ian}},//廞
{{pysm::g,pyym::uang},{pysm::k,pyym::uang}},//廣
{{pysm::q,pyym::iang},{pysm::s,pyym::e}},//廧
{{pysm::l,pyym::in},{pysm::l,pyym::an}},//廩
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//廬
{{pysm::p,pyym::ai},{pysm::p,pyym::o}},//廹
{{pysm::b,pyym::ian},{pysm::p,pyym::an}},//弁
{{pysm::n,pyym::ong},{pysm::l,pyym::ong}},//弄
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//弆
{{pysm::y,pyym::an},{pysm::n,pyym::an}},//弇
{{pysm::sh,pyym::i},{pysm::t,pyym::e}},//式
{{pysm::d,pyym::iao},{pysm::d,pyym::i}},//弔
{{pysm::j,pyym::ue},{pysm::zh,pyym::ang}},//弡
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//弮
{{pysm::x,pyym::uan},{pysm::y,pyym::uan}},//弲
{{pysm::q,pyym::iang},{pysm::j,pyym::iang}},//強
{{pysm::d,pyym::an},{pysm::t,pyym::an}},//弹
{{pysm::q,pyym::iang},{pysm::j,pyym::iang}},//强
{{pysm::g,pyym::ou},{pysm::k,pyym::ou}},//彀
{{pysm::d,pyym::an},{pysm::t,pyym::an}},//彈
{{pysm::j,pyym::iang},{pysm::q,pyym::iang}},//彊
{{pysm::m,pyym::i},{pysm::n,pyym::i}},//彌
{{pysm::t,pyym::uan},{pysm::sh,pyym::i}},//彖
{{pysm::h,pyym::ui},{pysm::s,pyym::ui}},//彗
{{pysm::sh,pyym::an},{pysm::x,pyym::ian}},//彡
{{pysm::y,pyym::an},{pysm::p,pyym::an}},//彦
{{pysm::b,pyym::in},{pysm::b,pyym::an}},//彬
{{pysm::p,pyym::iao},{pysm::m,pyym::iao}},//彯
{{pysm::ch,pyym::i},{pysm::f,pyym::u}},//彳
{{pysm::zh,pyym::uo},{pysm::b,pyym::o}},//彴
{{pysm::t,pyym::uo},{pysm::y,pyym::i}},//彵
{{pysm::p,pyym::ang},{pysm::f,pyym::ang}},//彷
{{pysm::h,pyym::uai},{pysm::h,pyym::ui}},//徊
{{pysm::w,pyym::ang},{pysm::w,pyym::a}},//徍
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//徎
{{pysm::d,pyym::e},{pysm::d,pyym::ei}},//得
{{pysm::x,pyym::i},{pysm::s,pyym::i}},//徙
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//從
{{pysm::y,pyym::u},{pysm::y,pyym::a}},//御
{{pysm::sh,pyym::i},{pysm::t,pyym::i}},//徥
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//徦
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//徧
{{pysm::p,pyym::ang},{pysm::b,pyym::ang}},//徬
{{pysm::t,pyym::i},{pysm::ch,pyym::i}},//徲
{{pysm::ch,pyym::ong},{pysm::zh,pyym::ong}},//徸
{{pysm::j,pyym::iao},{pysm::y,pyym::ao}},//徼
{{pysm::x,pyym::iang},{pysm::r,pyym::ang}},//忀
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//忂
{{pysm::d,pyym::ing},{pysm::t,pyym::ing}},//忊
{{pysm::ch,pyym::an},{pysm::q,pyym::ian}},//忏
{{pysm::t,pyym::an},{pysm::k,pyym::eng}},//忐
{{pysm::t,pyym::e},{pysm::d,pyym::ao}},//忑
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//忓
{{pysm::q,pyym::i},{pysm::y,pyym::i}},//忔
{{pysm::sh,pyym::i},{pysm::t,pyym::ai}},//忕
{{pysm::x,pyym::i},{pysm::l,pyym::ie}},//忚
{{pysm::m,pyym::in},{pysm::w,pyym::en}},//忞
{{pysm::s,pyym::ong},{pysm::zh,pyym::ong}},//忪
{{pysm::y,pyym::u},{pysm::sh,pyym::u}},//忬
{{pysm::zh,pyym::i},{pysm::q,pyym::i}},//忮
{{pysm::q,pyym::i},{pysm::sh,pyym::i}},//忯
{{pysm::ch,pyym::en},{pysm::d,pyym::an}},//忱
{{pysm::q,pyym::ian},{pysm::q,pyym::in}},//忴
{{pysm::k,pyym::uang},{pysm::w,pyym::ang}},//忹
{{pysm::k,pyym::ang},{pysm::h,pyym::ang}},//忼
{{pysm::k,pyym::ai},{pysm::q,pyym::i}},//忾
{{pysm::h,pyym::uai},{pysm::f,pyym::u}},//怀
{{pysm::m,pyym::in},{pysm::m,pyym::en}},//怋
{{pysm::z,pyym::uo},{pysm::zh,pyym::a}},//怍
{{pysm::j,pyym::u},{pysm::k,pyym::ou}},//怐
{{pysm::n,pyym::ao},{pysm::n,pyym::iu}},//怓
{{pysm::p,pyym::a},{pysm::b,pyym::o}},//怕
{{pysm::t,pyym::ie},{pysm::zh,pyym::an}},//怗
{{pysm::h,pyym::u},{pysm::g,pyym::u}},//怘
{{pysm::h,pyym::u},{pysm::t,pyym::ie}},//怙
{{pysm::d,pyym::a},{pysm::d,pyym::an}},//怛
{{pysm::l,pyym::ian},{pysm::l,pyym::ing}},//怜
{{pysm::s,pyym::i},{pysm::s,pyym::ai}},//思
{{pysm::ch,pyym::ou},{pysm::y,pyym::ou}},//怞
{{pysm::d,pyym::ai},{pysm::y,pyym::i}},//怠
{{pysm::y,pyym::uan},{pysm::y,pyym::un}},//怨
{{pysm::y,pyym::ou},{pysm::y,pyym::ao}},//怮
{{pysm::x,pyym::u},{pysm::x,pyym::ue}},//怴
{{pysm::ch,pyym::u},{pysm::x,pyym::u}},//怵
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//怶
{{pysm::x,pyym::un},{pysm::sh,pyym::un}},//恂
{{pysm::sh,pyym::i},{pysm::zh,pyym::i}},//恃
{{pysm::h,pyym::eng},{pysm::g,pyym::eng}},//恆
{{pysm::t,pyym::iao},{pysm::y,pyym::ao}},//恌
{{pysm::h,pyym::uang},{pysm::g,pyym::uang}},//恍
{{pysm::g,pyym::ui},{pysm::w,pyym::ei}},//恑
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//恔
{{pysm::h,pyym::u},{pysm::k,pyym::ua}},//恗
{{pysm::j,pyym::ia},{pysm::q,pyym::i}},//恝
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//恫
{{pysm::q,pyym::uan},{pysm::zh,pyym::uan}},//恮
{{pysm::nop,pyym::e},{pysm::w,pyym::u}},//恶
{{pysm::y,pyym::ong},{pysm::t,pyym::ong}},//恿
{{pysm::y,pyym::uan},{pysm::j,pyym::uan}},//悁
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//悂
{{pysm::y,pyym::u},{pysm::sh,pyym::u}},//悆
{{pysm::t,pyym::u},{pysm::y,pyym::u}},//悇
{{pysm::j,pyym::ie},{pysm::k,pyym::e}},//悈
{{pysm::h,pyym::ao},{pysm::j,pyym::iao}},//悎
{{pysm::m,pyym::an},{pysm::m,pyym::en}},//悗
{{pysm::q,pyym::uan},{pysm::x,pyym::un}},//悛
{{pysm::k,pyym::ui},{pysm::l,pyym::i}},//悝
{{pysm::l,pyym::iang},{pysm::l,pyym::ang}},//悢
{{pysm::j,pyym::ing},{pysm::l,pyym::iang}},//惊
{{pysm::l,pyym::an},{pysm::l,pyym::in}},//惏
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//惐
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//惓
{{pysm::t,pyym::an},{pysm::d,pyym::an}},//惔
{{pysm::ch,pyym::uo},{pysm::ch,pyym::ui}},//惙
{{pysm::h,pyym::un},{pysm::m,pyym::en}},//惛
{{pysm::ch,pyym::ang},{pysm::t,pyym::ang}},//惝
{{pysm::s,pyym::uo},{pysm::r,pyym::ui}},//惢
{{pysm::d,pyym::uo},{pysm::t,pyym::uo}},//惰
{{pysm::d,pyym::ie},{pysm::t,pyym::ie}},//惵
{{pysm::r,pyym::e},{pysm::r,pyym::uo}},//惹
{{pysm::m,pyym::in},{pysm::h,pyym::un}},//惽
{{pysm::t,pyym::i},{pysm::sh,pyym::i}},//惿
{{pysm::q,pyym::iao},{pysm::q,pyym::iu}},//愀
{{pysm::y,pyym::u},{pysm::t,pyym::ou}},//愉
{{pysm::m,pyym::in},{pysm::f,pyym::en}},//愍
{{pysm::q,pyym::ia},{pysm::k,pyym::e}},//愘
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//感
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//愠
{{pysm::s,pyym::ai},{pysm::s,pyym::i}},//愢
{{pysm::g,pyym::ong},{pysm::h,pyym::ong}},//愩
{{pysm::s,pyym::u},{pysm::s,pyym::e}},//愬
{{pysm::x,pyym::i},{pysm::x,pyym::ie}},//慀
{{pysm::s,pyym::ao},{pysm::c,pyym::ao}},//慅
{{pysm::x,pyym::u},{pysm::ch,pyym::u}},//慉
{{pysm::sh,pyym::en},{pysm::zh,pyym::en}},//慎
{{pysm::c,pyym::ong},{pysm::c,pyym::ao}},//慒
{{pysm::t,pyym::e},{pysm::n,pyym::i}},//慝
{{pysm::z,pyym::ao},{pysm::c,pyym::ao}},//慥
{{pysm::q,pyym::in},{pysm::j,pyym::in}},//慬
{{pysm::q,pyym::ian},{pysm::x,pyym::ian}},//慳
{{pysm::sh,pyym::e},{pysm::zh,pyym::e}},//慴
{{pysm::q,pyym::ing},{pysm::q,pyym::iang}},//慶
{{pysm::d,pyym::i},{pysm::ch,pyym::i}},//慸
{{pysm::zh,pyym::i},{pysm::zh,pyym::e}},//慹
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//慺
{{pysm::c,pyym::ong},{pysm::s,pyym::ong}},//憁
{{pysm::y,pyym::in},{pysm::x,pyym::in}},//憖
{{pysm::x,pyym::iao},{pysm::j,pyym::iao}},//憢
{{pysm::ch,pyym::ong},{pysm::zh,pyym::uang}},//憧
{{pysm::h,pyym::an},{pysm::d,pyym::an}},//憾
{{pysm::j,pyym::iao},{pysm::j,pyym::i}},//憿
{{pysm::x,pyym::uan},{pysm::h,pyym::uan}},//懁
{{pysm::c,pyym::ao},{pysm::s,pyym::ao}},//懆
{{pysm::nop,pyym::ao},{pysm::y,pyym::u}},//懊
{{pysm::l,pyym::in},{pysm::l,pyym::an}},//懔
{{pysm::y,pyym::an},{pysm::y,pyym::e}},//懕
{{pysm::nop,pyym::ai},{pysm::n,pyym::i}},//懝
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//懠
{{pysm::l,pyym::an},{pysm::x,pyym::ian}},//懢
{{pysm::l,pyym::an},{pysm::l,pyym::ai}},//懶
{{pysm::h,pyym::uan},{pysm::g,pyym::uan}},//懽
{{pysm::m,pyym::i},{pysm::m,pyym::o}},//戂
{{pysm::g,pyym::ang},{pysm::zh,pyym::uang}},//戆
{{pysm::zh,pyym::uang},{pysm::g,pyym::ang}},//戇
{{pysm::x,pyym::u},{pysm::q,pyym::u}},//戌
{{pysm::r,pyym::ong},{pysm::r,pyym::eng}},//戎
{{pysm::x,pyym::i},{pysm::h,pyym::u}},//戏
{{pysm::j,pyym::ian},{pysm::c,pyym::an}},//戔
{{pysm::q,pyym::iang},{pysm::z,pyym::ang}},//戕
{{pysm::h,pyym::uo},{pysm::y,pyym::u}},//或
{{pysm::q,pyym::i},{pysm::c,pyym::u}},//戚
{{pysm::j,pyym::ia},{pysm::g,pyym::a}},//戛
{{pysm::k,pyym::an},{pysm::zh,pyym::en}},//戡
{{pysm::q,pyym::iang},{pysm::ch,pyym::uang}},//戧
{{pysm::y,pyym::an},{pysm::y,pyym::ou}},//戭
{{pysm::h,pyym::u},{pysm::x,pyym::i}},//戯
{{pysm::sh,pyym::i},{pysm::y,pyym::i}},//戺
{{pysm::f,pyym::ang},{pysm::p,pyym::ang}},//房
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//扁
{{pysm::sh,pyym::ang},{pysm::j,pyym::iong}},//扄
{{pysm::c,pyym::ai},{pysm::z,pyym::ai}},//才
{{pysm::zh,pyym::a},{pysm::z,pyym::a}},//扎
{{pysm::p,pyym::u},{pysm::p,pyym::i}},//扑
{{pysm::k,pyym::ang},{pysm::g,pyym::ang}},//扛
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//扜
{{pysm::k,pyym::u},{pysm::w,pyym::u}},//扝
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//扞
{{pysm::r,pyym::ao},{pysm::y,pyym::ou}},//扰
{{pysm::q,pyym::ian},{pysm::q,pyym::in}},//扲
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//扳
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//扶
{{pysm::x,pyym::i},{pysm::zh,pyym::e}},//扸
{{pysm::zh,pyym::i},{pysm::q,pyym::i}},//扺
{{pysm::zh,pyym::ao},{pysm::h,pyym::ua}},//找
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//承
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//技
{{pysm::k,pyym::uang},{pysm::w,pyym::ang}},//抂
{{pysm::ch,pyym::ao},{pysm::s,pyym::uo}},//抄
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//把
{{pysm::d,pyym::an},{pysm::sh,pyym::en}},//抌
{{pysm::t,pyym::ou},{pysm::d,pyym::ou}},//投
{{pysm::k,pyym::ang},{pysm::g,pyym::ang}},//抗
{{pysm::nop,pyym::ao},{pysm::n,pyym::iu}},//抝
{{pysm::zh,pyym::i},{pysm::zh,pyym::ai}},//抧
{{pysm::p,pyym::eng},{pysm::b,pyym::eng}},//抨
{{pysm::t,pyym::ai},{pysm::ch,pyym::i}},//抬
{{pysm::y,pyym::ao},{pysm::t,pyym::ao}},//抭
{{pysm::h,pyym::e},{pysm::q,pyym::ia}},//抲
{{pysm::y,pyym::e},{pysm::sh,pyym::e}},//抴
{{pysm::p,pyym::i},{pysm::p,pyym::ei}},//抷
{{pysm::m,pyym::o},{pysm::m,pyym::a}},//抹
{{pysm::ch,pyym::en},{pysm::sh,pyym::en}},//抻
{{pysm::j,pyym::ia},{pysm::y,pyym::a}},//拁
{{pysm::zh,pyym::a},{pysm::zh,pyym::an}},//拃
{{pysm::d,pyym::an},{pysm::j,pyym::ie}},//担
{{pysm::n,pyym::ian},{pysm::d,pyym::ian}},//拈
{{pysm::f,pyym::u},{pysm::b,pyym::u}},//拊
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//拌
{{pysm::p,pyym::ai},{pysm::b,pyym::o}},//拍
{{pysm::l,pyym::in},{pysm::l,pyym::ing}},//拎
{{pysm::t,pyym::uo},{pysm::ch,pyym::i}},//拖
{{pysm::j,pyym::u},{pysm::g,pyym::ou}},//拘
{{pysm::z,pyym::e},{pysm::zh,pyym::ai}},//择
{{pysm::k,pyym::uo},{pysm::g,pyym::ua}},//括
{{pysm::j,pyym::ie},{pysm::j,pyym::ia}},//拮
{{pysm::g,pyym::ong},{pysm::j,pyym::u}},//拱
{{pysm::sh,pyym::uan},{pysm::q,pyym::uan}},//拴
{{pysm::c,pyym::un},{pysm::z,pyym::un}},//拵
{{pysm::z,pyym::a},{pysm::z,pyym::an}},//拶
{{pysm::p,pyym::in},{pysm::b,pyym::ing}},//拼
{{pysm::zh,pyym::uai},{pysm::y,pyym::e}},//拽
{{pysm::zh,pyym::i},{pysm::d,pyym::ie}},//挃
{{pysm::k,pyym::uo},{pysm::g,pyym::uang}},//挄
{{pysm::g,pyym::e},{pysm::h,pyym::e}},//挌
{{pysm::d,pyym::ie},{pysm::sh,pyym::e}},//挕
{{pysm::w,pyym::o},{pysm::zh,pyym::ua}},//挝
{{pysm::x,pyym::ie},{pysm::j,pyym::ia}},//挟
{{pysm::c,pyym::uo},{pysm::z,pyym::uo}},//挫
{{pysm::sh,pyym::an},{pysm::y,pyym::an}},//挻
{{pysm::x,pyym::ie},{pysm::j,pyym::ia}},//挾
{{pysm::j,pyym::iao},{pysm::k,pyym::u}},//捁
{{pysm::k,pyym::un},{pysm::h,pyym::un}},//捆
{{pysm::h,pyym::uo},{pysm::ch,pyym::i}},//捇
{{pysm::p,pyym::ou},{pysm::f,pyym::u}},//捊
{{pysm::l,pyym::v},{pysm::l,pyym::uo}},//捋
{{pysm::b,pyym::a},{pysm::b,pyym::ie}},//捌
{{pysm::j,pyym::uan},{pysm::y,pyym::uan}},//捐
{{pysm::y,pyym::e},{pysm::y,pyym::u}},//捓
{{pysm::j,pyym::ue},{pysm::zh,pyym::uo}},//捔
{{pysm::w,pyym::an},{pysm::g,pyym::ua}},//捖
{{pysm::w,pyym::an},{pysm::y,pyym::u}},//捥
{{pysm::p,pyym::eng},{pysm::f,pyym::eng}},//捧
{{pysm::l,pyym::ie},{pysm::l,pyym::i}},//捩
{{pysm::f,pyym::u},{pysm::b,pyym::u}},//捬
{{pysm::w,pyym::o},{pysm::l,pyym::uo}},//捰
{{pysm::j,pyym::uan},{pysm::q,pyym::uan}},//捲
{{pysm::ch,pyym::ui},{pysm::d,pyym::uo}},//捶
{{pysm::n,pyym::ian},{pysm::n,pyym::ie}},//捻
{{pysm::w,pyym::o},{pysm::x,pyym::ia}},//捾
{{pysm::x,pyym::ian},{pysm::h,pyym::en}},//掀
{{pysm::d,pyym::uo},{pysm::zh,pyym::uo}},//掇
{{pysm::d,pyym::iao},{pysm::n,pyym::uo}},//掉
{{pysm::j,pyym::i},{pysm::y,pyym::i}},//掎
{{pysm::p,pyym::ai},{pysm::b,pyym::ai}},//排
{{pysm::q,pyym::ian},{pysm::w,pyym::an}},//掔
{{pysm::j,pyym::ue},{pysm::k,pyym::u}},//掘
{{pysm::h,pyym::uo},{pysm::x,pyym::u}},//掝
{{pysm::sh,pyym::an},{pysm::y,pyym::an}},//掞
{{pysm::zh,pyym::eng},{pysm::d,pyym::ing}},//掟
{{pysm::t,pyym::an},{pysm::x,pyym::ian}},//探
{{pysm::k,pyym::ong},{pysm::q,pyym::iang}},//控
{{pysm::p,pyym::a},{pysm::sh,pyym::ou}},//掱
{{pysm::g,pyym::uai},{pysm::g,pyym::uo}},//掴
{{pysm::d,pyym::an},{pysm::sh,pyym::an}},//掸
{{pysm::y,pyym::uan},{pysm::ch,pyym::uan}},//掾
{{pysm::zh,pyym::eng},{pysm::k,pyym::eng}},//揁
{{pysm::j,pyym::iu},{pysm::y,pyym::ou}},//揂
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//揃
{{pysm::p,pyym::i},{pysm::ch,pyym::e}},//揊
{{pysm::s,pyym::ai},{pysm::c,pyym::ai}},//揌
{{pysm::z,pyym::ou},{pysm::c,pyym::ou}},//揍
{{pysm::m,pyym::iao},{pysm::m,pyym::ao}},//描
{{pysm::ch,pyym::a},{pysm::zh,pyym::a}},//插
{{pysm::z,pyym::ong},{pysm::s,pyym::ong}},//揔
{{pysm::y,pyym::i},{pysm::j,pyym::i}},//揖
{{pysm::y,pyym::ong},{pysm::h,pyym::uang}},//揘
{{pysm::z,pyym::an},{pysm::z,pyym::uan}},//揝
{{pysm::x,pyym::u},{pysm::j,pyym::u}},//揟
{{pysm::w,pyym::o},{pysm::nop,pyym::ou}},//握
{{pysm::k,pyym::e},{pysm::q,pyym::ia}},//揢
{{pysm::t,pyym::i},{pysm::d,pyym::i}},//揥
{{pysm::k,pyym::ai},{pysm::j,pyym::ia}},//揩
{{pysm::h,pyym::ui},{pysm::h,pyym::un}},//揮
{{pysm::ch,pyym::ong},{pysm::d,pyym::ong}},//揰
{{pysm::x,pyym::ie},{pysm::j,pyym::ia}},//揳
{{pysm::y,pyym::uan},{pysm::h,pyym::uan}},//援
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//揵
{{pysm::w,pyym::en},{pysm::w,pyym::u}},//揾
{{pysm::q,pyym::ue},{pysm::h,pyym::uo}},//搉
{{pysm::r,pyym::ong},{pysm::n,pyym::ang}},//搑
{{pysm::c,pyym::uo},{pysm::ch,pyym::ai}},//搓
{{pysm::k,pyym::e},{pysm::nop,pyym::e}},//搕
{{pysm::j,pyym::ian},{pysm::l,pyym::ian}},//搛
{{pysm::nop,pyym::e},{pysm::y,pyym::i}},//搤
{{pysm::ch,pyym::ui},{pysm::d,pyym::ui}},//搥
{{pysm::t,pyym::a},{pysm::d,pyym::a}},//搨
{{pysm::zh,pyym::a},{pysm::j,pyym::ie}},//搩
{{pysm::b,pyym::an},{pysm::s,pyym::u}},//搬
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//搭
{{pysm::h,pyym::u},{pysm::k,pyym::u}},//搰
{{pysm::zh,pyym::i},{pysm::n,pyym::ai}},//搱
{{pysm::q,pyym::iang},{pysm::ch,pyym::eng}},//搶
{{pysm::t,pyym::ian},{pysm::sh,pyym::en}},//搷
{{pysm::ch,pyym::an},{pysm::s,pyym::un}},//摌
{{pysm::g,pyym::uai},{pysm::g,pyym::uo}},//摑
{{pysm::f,pyym::eng},{pysm::p,pyym::eng}},//摓
{{pysm::q,pyym::i},{pysm::ch,pyym::a}},//摖
{{pysm::s,pyym::ou},{pysm::s,pyym::ong}},//摗
{{pysm::g,pyym::ai},{pysm::x,pyym::i}},//摡
{{pysm::h,pyym::u},{pysm::ch,pyym::u}},//摢
{{pysm::zh,pyym::a},{pysm::zh,pyym::ua}},//摣
{{pysm::n,pyym::ai},{pysm::zh,pyym::i}},//摨
{{pysm::j,pyym::iang},{pysm::q,pyym::iang}},//摪
{{pysm::nop,pyym::ao},{pysm::q,pyym::iao}},//摮
{{pysm::n,pyym::ie},{pysm::ch,pyym::e}},//摰
{{pysm::ch,pyym::an},{pysm::c,pyym::an}},//摲
{{pysm::k,pyym::ou},{pysm::nop,pyym::ou}},//摳
{{pysm::ch,pyym::u},{pysm::ch,pyym::i}},//摴
{{pysm::t,pyym::uan},{pysm::zh,pyym::uan}},//摶
{{pysm::j,pyym::iao},{pysm::ch,pyym::ao}},//摷
{{pysm::k,pyym::eng},{pysm::q,pyym::ian}},//摼
{{pysm::j,pyym::ue},{pysm::g,pyym::ui}},//撅
{{pysm::p,pyym::ie},{pysm::b,pyym::ie}},//撇
{{pysm::x,pyym::ian},{pysm::x,pyym::un}},//撏
{{pysm::s,pyym::i},{pysm::x,pyym::i}},//撕
{{pysm::h,pyym::an},{pysm::q,pyym::ian}},//撖
{{pysm::zh,pyym::eng},{pysm::ch,pyym::eng}},//撜
{{pysm::h,pyym::ui},{pysm::w,pyym::ei}},//撝
{{pysm::j,pyym::iao},{pysm::k,pyym::ao}},//撟
{{pysm::b,pyym::o},{pysm::f,pyym::a}},//撥
{{pysm::l,pyym::iao},{pysm::l,pyym::ao}},//撩
{{pysm::f,pyym::u},{pysm::m,pyym::o}},//撫
{{pysm::w,pyym::ei},{pysm::t,pyym::uo}},//撱
{{pysm::p,pyym::u},{pysm::b,pyym::u}},//撲
{{pysm::w,pyym::o},{pysm::zh,pyym::ua}},//撾
{{pysm::j,pyym::ian},{pysm::l,pyym::ian}},//撿
{{pysm::j,pyym::i},{pysm::x,pyym::i}},//擊
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//擏
{{pysm::d,pyym::an},{pysm::sh,pyym::an}},//擔
{{pysm::p,pyym::i},{pysm::b,pyym::o}},//擗
{{pysm::b,pyym::ai},{pysm::b,pyym::o}},//擘
{{pysm::d,pyym::ao},{pysm::ch,pyym::ou}},//擣
{{pysm::zh,pyym::i},{pysm::j,pyym::ie}},//擳
{{pysm::l,pyym::ie},{pysm::l,pyym::a}},//擸
{{pysm::c,pyym::a},{pysm::s,pyym::a}},//攃
{{pysm::sh,pyym::u},{pysm::l,pyym::u}},//攄
{{pysm::j,pyym::un},{pysm::p,pyym::ei}},//攈
{{pysm::h,pyym::uo},{pysm::q,pyym::ue}},//攉
{{pysm::l,pyym::a},{pysm::l,pyym::ai}},//攋
{{pysm::l,pyym::u},{pysm::l,pyym::uo}},//攎
{{pysm::z,pyym::an},{pysm::c,pyym::uan}},//攒
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//攕
{{pysm::ch,pyym::an},{pysm::sh,pyym::an}},//攙
{{pysm::m,pyym::i},{pysm::m,pyym::o}},//攠
{{pysm::l,pyym::uan},{pysm::l,pyym::ian}},//攣
{{pysm::t,pyym::an},{pysm::n,pyym::an}},//攤
{{pysm::l,pyym::i},{pysm::sh,pyym::ai}},//攦
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//攩
{{pysm::l,pyym::i},{pysm::l,pyym::uo}},//攭
{{pysm::zh,pyym::i},{pysm::q,pyym::i}},//支
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//攲
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//攼
{{pysm::b,pyym::an},{pysm::b,pyym::in}},//攽
{{pysm::m,pyym::in},{pysm::f,pyym::en}},//敃
{{pysm::w,pyym::u},{pysm::m,pyym::ou}},//敄
{{pysm::ch,pyym::u},{pysm::sh,pyym::ou}},//敊
{{pysm::d,pyym::i},{pysm::h,pyym::ua}},//敌
{{pysm::ch,pyym::i},{pysm::s,pyym::ou}},//敕
{{pysm::d,pyym::uo},{pysm::q,pyym::ue}},//敠
{{pysm::y,pyym::an},{pysm::j,pyym::iao}},//敥
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//敧
{{pysm::x,pyym::iao},{pysm::x,pyym::ue}},//敩
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//敫
{{pysm::sh,pyym::u},{pysm::sh,pyym::uo}},//数
{{pysm::nop,pyym::ai},{pysm::zh,pyym::u}},//敱
{{pysm::sh,pyym::u},{pysm::sh,pyym::uo}},//數
{{pysm::q,pyym::u},{pysm::nop,pyym::ou}},//敺
{{pysm::zh,pyym::uo},{pysm::zh,pyym::u}},//斀
{{pysm::l,pyym::i},{pysm::t,pyym::ai}},//斄
{{pysm::x,pyym::iao},{pysm::x,pyym::ue}},//斅
{{pysm::d,pyym::ou},{pysm::zh,pyym::u}},//斗
{{pysm::w,pyym::o},{pysm::g,pyym::uan}},//斡
{{pysm::t,pyym::iao},{pysm::t,pyym::ou}},//斢
{{pysm::y,pyym::in},{pysm::zh,pyym::i}},//斦
{{pysm::zh,pyym::uo},{pysm::ch,pyym::uo}},//斫
{{pysm::c,pyym::uo},{pysm::zh,pyym::uo}},//斮
{{pysm::s,pyym::i},{pysm::sh,pyym::i}},//斯
{{pysm::q,pyym::in},{pysm::j,pyym::in}},//斳
{{pysm::ch,pyym::an},{pysm::j,pyym::ie}},//斺
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//於
{{pysm::sh,pyym::i},{pysm::y,pyym::i}},//施
{{pysm::y,pyym::ou},{pysm::l,pyym::iu}},//斿
{{pysm::m,pyym::ao},{pysm::w,pyym::u}},//旄
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//旇
{{pysm::w,pyym::u},{pysm::m,pyym::o}},//无
{{pysm::j,pyym::i},{pysm::x,pyym::i}},//既
{{pysm::x,pyym::un},{pysm::j,pyym::un}},//旬
{{pysm::g,pyym::a},{pysm::x,pyym::u}},//旮
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//旰
{{pysm::t,pyym::ai},{pysm::y,pyym::ing}},//旲
{{pysm::t,pyym::un},{pysm::zh,pyym::un}},//旽
{{pysm::nop,pyym::ang},{pysm::y,pyym::ang}},//昂
{{pysm::k,pyym::un},{pysm::h,pyym::un}},//昆
{{pysm::g,pyym::ui},{pysm::j,pyym::iong}},//昋
{{pysm::m,pyym::ing},{pysm::m,pyym::eng}},//明
{{pysm::x,pyym::i},{pysm::c,pyym::uo}},//昔
{{pysm::x,pyym::in},{pysm::x,pyym::uan}},//昕
{{pysm::t,pyym::an},{pysm::y,pyym::u}},//昙
{{pysm::b,pyym::ing},{pysm::f,pyym::ang}},//昞
{{pysm::y,pyym::ing},{pysm::y,pyym::ang}},//映
{{pysm::p,pyym::o},{pysm::p,pyym::ei}},//昢
{{pysm::x,pyym::u},{pysm::x,pyym::iong}},//昫
{{pysm::sh,pyym::i},{pysm::t,pyym::i}},//是
{{pysm::sh,pyym::i},{pysm::x,pyym::ia}},//昰
{{pysm::d,pyym::ie},{pysm::y,pyym::i}},//昳
{{pysm::n,pyym::i},{pysm::zh,pyym::i}},//昵
{{pysm::ch,pyym::ao},{pysm::zh,pyym::ao}},//晁
{{pysm::x,pyym::u},{pysm::k,pyym::ua}},//晇
{{pysm::zh,pyym::e},{pysm::zh,pyym::i}},//晢
{{pysm::j,pyym::ing},{pysm::y,pyym::ing}},//景
{{pysm::q,pyym::i},{pysm::d,pyym::u}},//晵
{{pysm::nop,pyym::an},{pysm::y,pyym::an}},//晻
{{pysm::g,pyym::eng},{pysm::x,pyym::uan}},//暅
{{pysm::x,pyym::ia},{pysm::j,pyym::ia}},//暇
{{pysm::sh,pyym::u},{pysm::d,pyym::u}},//暏
{{pysm::j,pyym::ian},{pysm::l,pyym::an}},//暕
{{pysm::n,pyym::uan},{pysm::x,pyym::uan}},//暖
{{pysm::g,pyym::ao},{pysm::h,pyym::ao}},//暠
{{pysm::nop,pyym::ai},{pysm::n,pyym::uan}},//暧
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//暨
{{pysm::x,pyym::iang},{pysm::sh,pyym::ang}},//曏
{{pysm::p,pyym::u},{pysm::b,pyym::ao}},//曝
{{pysm::h,pyym::e},{pysm::nop,pyym::e}},//曷
{{pysm::c,pyym::eng},{pysm::z,pyym::eng}},//曾
{{pysm::z,pyym::ui},{pysm::c,pyym::uo}},//最
{{pysm::y,pyym::ue},{pysm::r,pyym::u}},//月
{{pysm::y,pyym::ou},{pysm::w,pyym::ei}},//有
{{pysm::r,pyym::uan},{pysm::w,pyym::an}},//朊
{{pysm::f,pyym::en},{pysm::b,pyym::an}},//朌
{{pysm::f,pyym::ei},{pysm::k,pyym::u}},//朏
{{pysm::t,pyym::iao},{pysm::y,pyym::ou}},//朓
{{pysm::z,pyym::ui},{pysm::j,pyym::uan}},//朘
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//朞
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//期
{{pysm::t,pyym::ong},{pysm::ch,pyym::uang}},//朣
{{pysm::m,pyym::eng},{pysm::m,pyym::ang}},//朦
{{pysm::m,pyym::o},{pysm::m,pyym::e}},//末
{{pysm::zh,pyym::a},{pysm::y,pyym::a}},//札
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//朮
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//术
{{pysm::zh,pyym::u},{pysm::sh,pyym::u}},//朱
{{pysm::g,pyym::ui},{pysm::q,pyym::iu}},//朹
{{pysm::j,pyym::i},{pysm::w,pyym::ei}},//机
{{pysm::z,pyym::a},{pysm::d,pyym::uo}},//杂
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//杅
{{pysm::sh,pyym::an},{pysm::sh,pyym::a}},//杉
{{pysm::w,pyym::u},{pysm::w,pyym::o}},//杌
{{pysm::r,pyym::en},{pysm::nop,pyym::er}},//杒
{{pysm::t,pyym::uo},{pysm::zh,pyym::e}},//杔
{{pysm::d,pyym::i},{pysm::d,pyym::uo}},//杕
{{pysm::g,pyym::ai},{pysm::g,pyym::e}},//杚
{{pysm::d,pyym::u},{pysm::t,pyym::u}},//杜
{{pysm::g,pyym::ang},{pysm::g,pyym::ong}},//杠
{{pysm::h,pyym::ang},{pysm::k,pyym::ang}},//杭
{{pysm::f,pyym::ei},{pysm::b,pyym::ei}},//杮
{{pysm::x,pyym::ian},{pysm::q,pyym::ian}},//杴
{{pysm::p,pyym::a},{pysm::b,pyym::a}},//杷
{{pysm::sh,pyym::u},{pysm::d,pyym::ui}},//杸
{{pysm::ch,pyym::ou},{pysm::n,pyym::iu}},//杻
{{pysm::zh,pyym::u},{pysm::sh,pyym::u}},//杼
{{pysm::w,pyym::o},{pysm::y,pyym::ue}},//枂
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//枇
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//枈
{{pysm::w,pyym::ang},{pysm::k,pyym::uang}},//枉
{{pysm::f,pyym::ang},{pysm::b,pyym::ing}},//枋
{{pysm::x,pyym::i},{pysm::s,pyym::i}},//析
{{pysm::y,pyym::a},{pysm::y,pyym::e}},//枒
{{pysm::d,pyym::ou},{pysm::zh,pyym::u}},//枓
{{pysm::zh,pyym::en},{pysm::ch,pyym::en}},//枕
{{pysm::r,pyym::ui},{pysm::n,pyym::en}},//枘
{{pysm::zh,pyym::i},{pysm::q,pyym::i}},//枝
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//枞
{{pysm::x,pyym::ian},{pysm::zh,pyym::en}},//枮
{{pysm::k,pyym::u},{pysm::g,pyym::u}},//枯
{{pysm::b,pyym::ao},{pysm::f,pyym::u}},//枹
{{pysm::y,pyym::i},{pysm::x,pyym::ie}},//枻
{{pysm::d,pyym::uo},{pysm::t,pyym::uo}},//柁
{{pysm::n,pyym::i},{pysm::ch,pyym::i}},//柅
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//柈
{{pysm::y,pyym::ang},{pysm::y,pyym::ing}},//柍
{{pysm::b,pyym::ai},{pysm::b,pyym::o}},//柏
{{pysm::m,pyym::ou},{pysm::m,pyym::ei}},//某
{{pysm::g,pyym::an},{pysm::q,pyym::ian}},//柑
{{pysm::x,pyym::ia},{pysm::j,pyym::ia}},//柙
{{pysm::y,pyym::ou},{pysm::zh,pyym::ou}},//柚
{{pysm::g,pyym::ui},{pysm::j,pyym::u}},//柜
{{pysm::n,pyym::an},{pysm::r,pyym::an}},//柟
{{pysm::d,pyym::i},{pysm::ch,pyym::i}},//柢
{{pysm::zh,pyym::i},{pysm::d,pyym::ie}},//柣
{{pysm::zh,pyym::a},{pysm::z,pyym::u}},//柤
{{pysm::b,pyym::u},{pysm::p,pyym::u}},//柨
{{pysm::b,pyym::i},{pysm::b,pyym::ie}},//柲
{{pysm::sh,pyym::an},{pysm::zh,pyym::a}},//柵
{{pysm::ch,pyym::u},{pysm::zh,pyym::u}},//柷
{{pysm::p,pyym::ei},{pysm::b,pyym::ei}},//柸
{{pysm::sh,pyym::i},{pysm::f,pyym::ei}},//柹
{{pysm::ch,pyym::eng},{pysm::j,pyym::ue}},//柽
{{pysm::l,pyym::i},{pysm::y,pyym::ue}},//栎
{{pysm::x,pyym::un},{pysm::s,pyym::un}},//栒
{{pysm::sh,pyym::uan},{pysm::q,pyym::uan}},//栓
{{pysm::q,pyym::i},{pysm::x,pyym::i}},//栖
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//栗
{{pysm::s,pyym::e},{pysm::c,pyym::i}},//栜
{{pysm::b,pyym::en},{pysm::b,pyym::ing}},//栟
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//栩
{{pysm::j,pyym::ian},{pysm::z,pyym::un}},//栫
{{pysm::y,pyym::ou},{pysm::y,pyym::u}},//栯
{{pysm::y,pyym::i},{pysm::zh,pyym::i}},//栺
{{pysm::h,pyym::eng},{pysm::h,pyym::ang}},//桁
{{pysm::w,pyym::ei},{pysm::g,pyym::ui}},//桅
{{pysm::j,pyym::uan},{pysm::q,pyym::uan}},//桊
{{pysm::y,pyym::i},{pysm::t,pyym::i}},//桋
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//桐
{{pysm::y,pyym::u},{pysm::m,pyym::ou}},//桙
{{pysm::g,pyym::ui},{pysm::h,pyym::ui}},//桧
{{pysm::zh,pyym::en},{pysm::ch,pyym::en}},//桭
{{pysm::t,pyym::ing},{pysm::y,pyym::ing}},//桯
{{pysm::p,pyym::o},{pysm::b,pyym::o}},//桲
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//桿
{{pysm::s,pyym::u},{pysm::y,pyym::in}},//梀
{{pysm::t,pyym::u},{pysm::ch,pyym::a}},//梌
{{pysm::nop,pyym::ao},{pysm::y,pyym::ou}},//梎
{{pysm::g,pyym::u},{pysm::j,pyym::ue}},//梏
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//梘
{{pysm::h,pyym::un},{pysm::k,pyym::uan}},//梡
{{pysm::w,pyym::u},{pysm::y,pyym::u}},//梧
{{pysm::s,pyym::uo},{pysm::x,pyym::un}},//梭
{{pysm::k,pyym::un},{pysm::h,pyym::un}},//梱
{{pysm::b,pyym::in},{pysm::b,pyym::ing}},//梹
{{pysm::c,pyym::ong},{pysm::s,pyym::ong}},//棇
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//棋
{{pysm::d,pyym::e},{pysm::zh,pyym::e}},//棏
{{pysm::ch,pyym::eng},{pysm::ch,pyym::ang}},//棖
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//棙
{{pysm::zh,pyym::an},{pysm::ch,pyym::en}},//棧
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//棬
{{pysm::r,pyym::en},{pysm::sh,pyym::en}},//棯
{{pysm::ch,pyym::ui},{pysm::d,pyym::uo}},//棰
{{pysm::q,pyym::i},{pysm::x,pyym::i}},//棲
{{pysm::f,pyym::u},{pysm::s,pyym::u}},//棴
{{pysm::k,pyym::e},{pysm::k,pyym::uan}},//棵
{{pysm::z,pyym::ou},{pysm::s,pyym::ou}},//棷
{{pysm::zh,pyym::ao},{pysm::zh,pyym::uo}},//棹
{{pysm::sh,pyym::en},{pysm::ch,pyym::en}},//棽
{{pysm::n,pyym::i},{pysm::n,pyym::ie}},//棿
{{pysm::j,pyym::ie},{pysm::q,pyym::ie}},//椄
{{pysm::ch,pyym::eng},{pysm::sh,pyym::eng}},//椉
{{pysm::z,pyym::uo},{pysm::c,pyym::ui}},//椊
{{pysm::q,pyym::iang},{pysm::k,pyym::ong}},//椌
{{pysm::ch,pyym::ui},{pysm::zh,pyym::ui}},//椎
{{pysm::y,pyym::a},{pysm::nop,pyym::e}},//椏
{{pysm::d,pyym::uo},{pysm::ch,pyym::uan}},//椯
{{pysm::w,pyym::ei},{pysm::h,pyym::ui}},//椲
{{pysm::j,pyym::ian},{pysm::h,pyym::an}},//椷
{{pysm::sh,pyym::en},{pysm::zh,pyym::en}},//椹
{{pysm::y,pyym::an},{pysm::y,pyym::a}},//椻
{{pysm::j,pyym::ian},{pysm::zh,pyym::an}},//椾
{{pysm::zh,pyym::a},{pysm::ch,pyym::a}},//楂
{{pysm::f,pyym::eng},{pysm::f,pyym::an}},//楓
{{pysm::zh,pyym::i},{pysm::j,pyym::i}},//楖
{{pysm::h,pyym::u},{pysm::k,pyym::u}},//楛
{{pysm::s,pyym::ong},{pysm::c,pyym::ong}},//楤
{{pysm::x,pyym::uan},{pysm::y,pyym::uan}},//楥
{{pysm::y,pyym::e},{pysm::d,pyym::ie}},//楪
{{pysm::j,pyym::ie},{pysm::q,pyym::ia}},//楬
{{pysm::ch,pyym::u},{pysm::zh,pyym::u}},//楮
{{pysm::z,pyym::ou},{pysm::c,pyym::ou}},//楱
{{pysm::k,pyym::ai},{pysm::j,pyym::ie}},//楷
{{pysm::w,pyym::en},{pysm::y,pyym::un}},//榅
{{pysm::f,pyym::u},{pysm::b,pyym::o}},//榑
{{pysm::j,pyym::ian},{pysm::j,pyym::in}},//榗
{{pysm::sh,pyym::a},{pysm::x,pyym::ie}},//榝
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//榦
{{pysm::g,pyym::ao},{pysm::k,pyym::ao}},//槀
{{pysm::g,pyym::ao},{pysm::k,pyym::ao}},//槁
{{pysm::d,pyym::ian},{pysm::zh,pyym::en}},//槇
{{pysm::g,pyym::ou},{pysm::j,pyym::ue}},//構
{{pysm::q,pyym::iang},{pysm::ch,pyym::eng}},//槍
{{pysm::k,pyym::an},{pysm::j,pyym::ian}},//槛
{{pysm::b,pyym::in},{pysm::b,pyym::ing}},//槟
{{pysm::x,pyym::i},{pysm::d,pyym::ie}},//槢
{{pysm::j,pyym::i},{pysm::g,pyym::ui}},//槣
{{pysm::s,pyym::en},{pysm::sh,pyym::en}},//槮
{{pysm::c,pyym::ui},{pysm::z,pyym::ui}},//槯
{{pysm::y,pyym::ou},{pysm::ch,pyym::ao}},//槱
{{pysm::c,pyym::ao},{pysm::z,pyym::ao}},//槽
{{pysm::m,pyym::an},{pysm::w,pyym::an}},//槾
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//槿
{{pysm::zh,pyym::uang},{pysm::ch,pyym::ong}},//樁
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//樅
{{pysm::l,pyym::i},{pysm::ch,pyym::i}},//樆
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//樓
{{pysm::ch,pyym::ao},{pysm::j,pyym::iao}},//樔
{{pysm::t,pyym::ang},{pysm::ch,pyym::eng}},//樘
{{pysm::l,pyym::u},{pysm::d,pyym::u}},//樚
{{pysm::j,pyym::iu},{pysm::l,pyym::iao}},//樛
{{pysm::sh,pyym::u},{pysm::nop,pyym::ou}},//樞
{{pysm::m,pyym::an},{pysm::l,pyym::ang}},//樠
{{pysm::m,pyym::o},{pysm::m,pyym::u}},//模
{{pysm::n,pyym::iao},{pysm::m,pyym::u}},//樢
{{pysm::y,pyym::ang},{pysm::x,pyym::iang}},//樣
{{pysm::nop,pyym::er},{pysm::zh,pyym::i}},//樲
{{pysm::zh,pyym::i},{pysm::y,pyym::i}},//樴
{{pysm::f,pyym::a},{pysm::f,pyym::ei}},//橃
{{pysm::r,pyym::ao},{pysm::n,pyym::ao}},//橈
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//橋
{{pysm::zh,pyym::an},{pysm::j,pyym::ian}},//橏
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//橑
{{pysm::d,pyym::un},{pysm::t,pyym::ui}},//橔
{{pysm::t,pyym::ang},{pysm::ch,pyym::eng}},//橖
{{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//橢
{{pysm::z,pyym::eng},{pysm::c,pyym::eng}},//橧
{{pysm::f,pyym::en},{pysm::f,pyym::ei}},//橨
{{pysm::r,pyym::an},{pysm::y,pyym::an}},//橪
{{pysm::q,pyym::ian},{pysm::q,pyym::in}},//橬
{{pysm::t,pyym::an},{pysm::sh,pyym::an}},//檀
{{pysm::y,pyym::an},{pysm::d,pyym::an}},//檐
{{pysm::b,pyym::o},{pysm::b,pyym::i}},//檗
{{pysm::p,pyym::ing},{pysm::b,pyym::o}},//檘
{{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//檞
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//檠
{{pysm::ch,pyym::a},{pysm::s,pyym::a}},//檫
{{pysm::b,pyym::in},{pysm::b,pyym::ing}},//檳
{{pysm::h,pyym::uo},{pysm::h,pyym::ua}},//檴
{{pysm::n,pyym::i},{pysm::m,pyym::i}},//檷
{{pysm::k,pyym::an},{pysm::j,pyym::ian}},//檻
{{pysm::zh,pyym::ao},{pysm::d,pyym::i}},//櫂
{{pysm::l,pyym::v},{pysm::ch,pyym::u}},//櫖
{{pysm::m,pyym::ie},{pysm::m,pyym::ei}},//櫗
{{pysm::zh,pyym::uo},{pysm::zh,pyym::u}},//櫡
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//櫨
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//櫭
{{pysm::h,pyym::uai},{pysm::g,pyym::ui}},//櫰
{{pysm::j,pyym::ian},{pysm::sh,pyym::an}},//櫼
{{pysm::x,pyym::iang},{pysm::r,pyym::ang}},//欀
{{pysm::ch,pyym::an},{pysm::zh,pyym::an}},//欃
{{pysm::l,pyym::an},{pysm::l,pyym::ian}},//欄
{{pysm::w,pyym::ei},{pysm::z,pyym::ui}},//欈
{{pysm::q,pyym::uan},{pysm::g,pyym::uan}},//權
{{pysm::c,pyym::uan},{pysm::z,pyym::uan}},//欑
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//欓
{{pysm::l,pyym::ei},{pysm::l,pyym::uo}},//欙
{{pysm::c,pyym::i},{pysm::z,pyym::i}},//次
{{pysm::k,pyym::ai},{pysm::nop,pyym::ai}},//欬
{{pysm::y,pyym::i},{pysm::y,pyym::in}},//欭
{{pysm::x,pyym::i},{pysm::k,pyym::ai}},//欯
{{pysm::h,pyym::e},{pysm::x,pyym::ia}},//欱
{{pysm::sh,pyym::uo},{pysm::s,pyym::ou}},//欶
{{pysm::y,pyym::i},{pysm::q,pyym::i}},//欹
{{pysm::ch,pyym::ua},{pysm::x,pyym::u}},//欻
{{pysm::ch,pyym::i},{pysm::ch,pyym::uai}},//欼
{{pysm::q,pyym::in},{pysm::y,pyym::in}},//欽
{{pysm::k,pyym::uan},{pysm::x,pyym::in}},//款
{{pysm::sh,pyym::a},{pysm::x,pyym::ia}},//歃
{{pysm::x,pyym::ie},{pysm::y,pyym::a}},//歇
{{pysm::w,pyym::u},{pysm::y,pyym::ang}},//歍
{{pysm::j,pyym::in},{pysm::q,pyym::un}},//歏
{{pysm::t,pyym::i},{pysm::x,pyym::iao}},//歒
{{pysm::x,pyym::i},{pysm::y,pyym::i}},//歖
{{pysm::ch,pyym::ua},{pysm::x,pyym::u}},//歘
{{pysm::h,pyym::an},{pysm::l,pyym::ian}},//歛
{{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//歭
{{pysm::s,pyym::e},{pysm::sh,pyym::a}},//歰
{{pysm::s,pyym::ui},{pysm::s,pyym::uo}},//歲
{{pysm::g,pyym::ui},{pysm::k,pyym::ui}},//歸
{{pysm::d,pyym::ai},{pysm::nop,pyym::e}},//歹
{{pysm::m,pyym::o},{pysm::w,pyym::en}},//歾
{{pysm::m,pyym::o},{pysm::w,pyym::en}},//殁
{{pysm::p,pyym::iao},{pysm::b,pyym::i}},//殍
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//殑
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//殖
{{pysm::y,pyym::e},{pysm::y,pyym::an}},//殗
{{pysm::h,pyym::un},{pysm::m,pyym::en}},//殙
{{pysm::h,pyym::ui},{pysm::k,pyym::ui}},//殨
{{pysm::y,pyym::in},{pysm::y,pyym::an}},//殷
{{pysm::k,pyym::e},{pysm::q,pyym::iao}},//殼
{{pysm::x,pyym::iao},{pysm::y,pyym::ao}},//殽
{{pysm::w,pyym::u},{pysm::m,pyym::ou}},//毋
{{pysm::m,pyym::u},{pysm::w,pyym::u}},//母
{{pysm::d,pyym::u},{pysm::d,pyym::ai}},//毒
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//比
{{pysm::m,pyym::u},{pysm::m,pyym::ao}},//毣
{{pysm::d,pyym::ou},{pysm::n,pyym::uo}},//毭
{{pysm::s,pyym::ai},{pysm::s,pyym::ui}},//毸
{{pysm::sh,pyym::u},{pysm::y,pyym::u}},//毹
{{pysm::m,pyym::ao},{pysm::l,pyym::i}},//氂
{{pysm::d,pyym::i},{pysm::zh,pyym::i}},//氐
{{pysm::m,pyym::ang},{pysm::m,pyym::eng}},//氓
{{pysm::y,pyym::ang},{pysm::r,pyym::i}},//氜
{{pysm::q,pyym::i},{pysm::x,pyym::i}},//氣
{{pysm::y,pyym::in},{pysm::y,pyym::an}},//氤
{{pysm::zh,pyym::eng},{pysm::ch,pyym::eng}},//氶
{{pysm::n,pyym::i},{pysm::m,pyym::ei}},//氼
{{pysm::t,pyym::un},{pysm::q,pyym::iu}},//氽
{{pysm::t,pyym::ing},{pysm::d,pyym::ing}},//汀
{{pysm::b,pyym::in},{pysm::p,pyym::a}},//汃
{{pysm::w,pyym::an},{pysm::h,pyym::uan}},//汍
{{pysm::f,pyym::an},{pysm::f,pyym::a}},//汎
{{pysm::d,pyym::a},{pysm::t,pyym::ai}},//汏
{{pysm::q,pyym::iu},{pysm::y,pyym::ou}},//汓
{{pysm::sh,pyym::an},{pysm::sh,pyym::uan}},//汕
{{pysm::p,pyym::in},{pysm::ch,pyym::i}},//汖
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//汗
{{pysm::t,pyym::ang},{pysm::sh,pyym::ang}},//汤
{{pysm::zh,pyym::i},{pysm::j,pyym::i}},//汥
{{pysm::q,pyym::ian},{pysm::y,pyym::an}},//汧
{{pysm::w,pyym::ang},{pysm::h,pyym::ong}},//汪
{{pysm::r,pyym::ui},{pysm::t,pyym::un}},//汭
{{pysm::q,pyym::uan},{pysm::f,pyym::u}},//汱
{{pysm::f,pyym::ang},{pysm::p,pyym::ang}},//汸
{{pysm::h,pyym::u},{pysm::h,pyym::uang}},//汻
{{pysm::n,pyym::iu},{pysm::y,pyym::ou}},//汼
{{pysm::f,pyym::en},{pysm::p,pyym::en}},//汾
{{pysm::y,pyym::i},{pysm::y,pyym::in}},//沂
{{pysm::h,pyym::ang},{pysm::k,pyym::ang}},//沆
{{pysm::y,pyym::an},{pysm::w,pyym::ei}},//沇
{{pysm::q,pyym::i},{pysm::q,pyym::ie}},//沏
{{pysm::n,pyym::v},{pysm::n,pyym::iu}},//沑
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//沓
{{pysm::p,pyym::ang},{pysm::t,pyym::ian}},//沗
{{pysm::sh,pyym::a},{pysm::s,pyym::uo}},//沙
{{pysm::zh,pyym::ui},{pysm::z,pyym::i}},//沝
{{pysm::m,pyym::ei},{pysm::h,pyym::ui}},//沬
{{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//沰
{{pysm::l,pyym::i},{pysm::zh,pyym::en}},//沴
{{pysm::f,pyym::ei},{pysm::f,pyym::u}},//沸
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//治
{{pysm::j,pyym::iong},{pysm::y,pyym::ing}},//泂
{{pysm::j,pyym::u},{pysm::g,pyym::ou}},//泃
{{pysm::x,pyym::ie},{pysm::y,pyym::i}},//泄
{{pysm::q,pyym::iu},{pysm::y,pyym::ou}},//泅
{{pysm::y,pyym::i},{pysm::d,pyym::ie}},//泆
{{pysm::p,pyym::o},{pysm::b,pyym::o}},//泊
{{pysm::m,pyym::i},{pysm::b,pyym::i}},//泌
{{pysm::zh,pyym::u},{pysm::k,pyym::u}},//泏
{{pysm::y,pyym::ou},{pysm::nop,pyym::ao}},//泑
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//泔
{{pysm::m,pyym::ao},{pysm::l,pyym::iu}},//泖
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//泙
{{pysm::c,pyym::i},{pysm::z,pyym::i}},//泚
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//泜
{{pysm::n,pyym::ing},{pysm::zh,pyym::u}},//泞
{{pysm::s,pyym::a},{pysm::x,pyym::ue}},//泧
{{pysm::zh,pyym::u},{pysm::zh,pyym::ou}},//注
{{pysm::x,pyym::uan},{pysm::j,pyym::uan}},//泫
{{pysm::j,pyym::ue},{pysm::x,pyym::ue}},//泬
{{pysm::m,pyym::in},{pysm::m,pyym::ian}},//泯
{{pysm::l,pyym::ong},{pysm::sh,pyym::uang}},//泷
{{pysm::l,pyym::uo},{pysm::p,pyym::o}},//泺
{{pysm::p,pyym::an},{pysm::zh,pyym::ou}},//洀
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//洁
{{pysm::j,pyym::ian},{pysm::c,pyym::un}},//洊
{{pysm::y,pyym::ang},{pysm::x,pyym::iang}},//洋
{{pysm::x,pyym::i},{pysm::x,pyym::ian}},//洗
{{pysm::j,pyym::iang},{pysm::h,pyym::ong}},//洚
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//洞
{{pysm::x,pyym::ie},{pysm::y,pyym::i}},//洩
{{pysm::x,pyym::u},{pysm::y,pyym::i}},//洫
{{pysm::s,pyym::u},{pysm::sh,pyym::uo}},//洬
{{pysm::q,pyym::ie},{pysm::j,pyym::ie}},//洯
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//洴
{{pysm::x,pyym::un},{pysm::x,pyym::uan}},//洵
{{pysm::g,pyym::uang},{pysm::h,pyym::uang}},//洸
{{pysm::h,pyym::uo},{pysm::g,pyym::uo}},//活
{{pysm::w,pyym::a},{pysm::g,pyym::ui}},//洼
{{pysm::q,pyym::ia},{pysm::h,pyym::e}},//洽
{{pysm::w,pyym::u},{pysm::h,pyym::u}},//洿
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//浅
{{pysm::h,pyym::ui},{pysm::k,pyym::uai}},//浍
{{pysm::h,pyym::u},{pysm::x,pyym::u}},//浒
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//浛
{{pysm::b,pyym::ang},{pysm::b,pyym::in}},//浜
{{pysm::y,pyym::ou},{pysm::d,pyym::i}},//浟
{{pysm::y,pyym::i},{pysm::y,pyym::a}},//浥
{{pysm::l,pyym::i},{pysm::h,pyym::ai}},//浬
{{pysm::l,pyym::ian},{pysm::l,pyym::i}},//浰
{{pysm::f,pyym::eng},{pysm::h,pyym::ong}},//浲
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//浸
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//浹
{{pysm::s,pyym::ui},{pysm::n,pyym::ei}},//浽
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//涀
{{pysm::j,pyym::ing},{pysm::q,pyym::ing}},//涇
{{pysm::sh,pyym::e},{pysm::d,pyym::ie}},//涉
{{pysm::n,pyym::ian},{pysm::r,pyym::en}},//涊
{{pysm::y,pyym::ong},{pysm::ch,pyym::ong}},//涌
{{pysm::t,pyym::un},{pysm::y,pyym::un}},//涒
{{pysm::w,pyym::o},{pysm::g,pyym::uo}},//涡
{{pysm::h,pyym::uan},{pysm::h,pyym::ui}},//涣
{{pysm::f,pyym::u},{pysm::p,pyym::ou}},//涪
{{pysm::sh,pyym::ou},{pysm::t,pyym::ao}},//涭
{{pysm::sh,pyym::uan},{pysm::sh,pyym::ua}},//涮
{{pysm::y,pyym::e},{pysm::sh,pyym::i}},//液
{{pysm::k,pyym::ong},{pysm::n,pyym::ang}},//涳
{{pysm::q,pyym::ie},{pysm::j,pyym::i}},//淁
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//淈
{{pysm::g,pyym::uo},{pysm::g,pyym::uan}},//淉
{{pysm::y,pyym::an},{pysm::h,pyym::an}},//淊
{{pysm::t,pyym::ang},{pysm::ch,pyym::ang}},//淌
{{pysm::zh,pyym::ou},{pysm::d,pyym::iao}},//淍
{{pysm::sh,pyym::u},{pysm::ch,pyym::u}},//淑
{{pysm::q,pyym::i},{pysm::q,pyym::ian}},//淒
{{pysm::c,pyym::ong},{pysm::sh,pyym::uang}},//淙
{{pysm::l,pyym::ei},{pysm::l,pyym::i}},//淚
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//淜
{{pysm::p,pyym::i},{pysm::p,pyym::ei}},//淠
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//淢
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//淦
{{pysm::j,pyym::ing},{pysm::ch,pyym::eng}},//淨
{{pysm::l,pyym::un},{pysm::g,pyym::uan}},//淪
{{pysm::c,pyym::ui},{pysm::z,pyym::u}},//淬
{{pysm::b,pyym::iao},{pysm::h,pyym::u}},//淲
{{pysm::ch,pyym::un},{pysm::zh,pyym::un}},//淳
{{pysm::w,pyym::en},{pysm::m,pyym::in}},//渂
{{pysm::r,pyym::uo},{pysm::r,pyym::e}},//渃
{{pysm::m,pyym::ian},{pysm::sh,pyym::eng}},//渑
{{pysm::q,pyym::iu},{pysm::w,pyym::u}},//渞
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//渠
{{pysm::f,pyym::an},{pysm::f,pyym::eng}},//渢
{{pysm::w,pyym::o},{pysm::g,pyym::uo}},//渦
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//渧
{{pysm::w,pyym::en},{pysm::y,pyym::un}},//温
{{pysm::g,pyym::ang},{pysm::h,pyym::ong}},//港
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//渱
{{pysm::y,pyym::ou},{pysm::l,pyym::iu}},//游
{{pysm::h,pyym::ong},{pysm::q,pyym::ing}},//渹
{{pysm::h,pyym::un},{pysm::g,pyym::un}},//渾
{{pysm::p,pyym::ai},{pysm::b,pyym::a}},//湃
{{pysm::l,pyym::ian},{pysm::l,pyym::an}},//湅
{{pysm::t,pyym::uan},{pysm::zh,pyym::uan}},//湍
{{pysm::h,pyym::ui},{pysm::m,pyym::in}},//湏
{{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//湝
{{pysm::zh,pyym::en},{pysm::ch,pyym::eng}},//湞
{{pysm::h,pyym::uang},{pysm::k,pyym::uang}},//湟
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//湩
{{pysm::t,pyym::uan},{pysm::n,pyym::uan}},//湪
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//湮
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//湴
{{pysm::zh,pyym::uang},{pysm::h,pyym::un}},//湷
{{pysm::k,pyym::ui},{pysm::h,pyym::ui}},//溃
{{pysm::g,pyym::ai},{pysm::x,pyym::ie}},//溉
{{pysm::y,pyym::an},{pysm::g,pyym::ui}},//溎
{{pysm::zh,pyym::un},{pysm::zh,pyym::uo}},//準
{{pysm::k,pyym::e},{pysm::k,pyym::ai}},//溘
{{pysm::t,pyym::a},{pysm::d,pyym::a}},//溚
{{pysm::m,pyym::ing},{pysm::m,pyym::i}},//溟
{{pysm::w,pyym::ei},{pysm::m,pyym::ei}},//溦
{{pysm::x,pyym::i},{pysm::q,pyym::i}},//溪
{{pysm::s,pyym::u},{pysm::sh,pyym::uo}},//溯
{{pysm::q,pyym::in},{pysm::zh,pyym::en}},//溱
{{pysm::s,pyym::ou},{pysm::sh,pyym::ao}},//溲
{{pysm::x,pyym::iu},{pysm::ch,pyym::ou}},//溴
{{pysm::s,pyym::uo},{pysm::s,pyym::e}},//溹
{{pysm::ch,pyym::u},{pysm::x,pyym::u}},//滀
{{pysm::p,pyym::ang},{pysm::p,pyym::eng}},//滂
{{pysm::h,pyym::ao},{pysm::x,pyym::ue}},//滈
{{pysm::x,pyym::ing},{pysm::y,pyym::ing}},//滎
{{pysm::h,pyym::ua},{pysm::g,pyym::u}},//滑
{{pysm::y,pyym::ao},{pysm::x,pyym::iao}},//滧
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//滯
{{pysm::h,pyym::u},{pysm::x,pyym::u}},//滸
{{pysm::m,pyym::an},{pysm::m,pyym::en}},//滿
{{pysm::p,pyym::iao},{pysm::b,pyym::iao}},//漂
{{pysm::q,pyym::i},{pysm::q,pyym::ie}},//漆
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//漊
{{pysm::c,pyym::ong},{pysm::s,pyym::ong}},//漎
{{pysm::t,pyym::uan},{pysm::zh,pyym::uan}},//漙
{{pysm::sh,pyym::ang},{pysm::t,pyym::ang}},//漡
{{pysm::h,pyym::an},{pysm::t,pyym::an}},//漢
{{pysm::l,pyym::ian},{pysm::l,pyym::an}},//漣
{{pysm::ch,pyym::i},{pysm::t,pyym::ai}},//漦
{{pysm::h,pyym::uo},{pysm::k,pyym::uo}},//漷
{{pysm::sh,pyym::uang},{pysm::ch,pyym::uang}},//漺
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//潐
{{pysm::p,pyym::o},{pysm::b,pyym::o}},//潑
{{pysm::w,pyym::ei},{pysm::g,pyym::ui}},//潙
{{pysm::x,pyym::i},{pysm::y,pyym::a}},//潝
{{pysm::x,pyym::un},{pysm::s,pyym::un}},//潠
{{pysm::h,pyym::uang},{pysm::g,pyym::uang}},//潢
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//潦
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//潨
{{pysm::zh,pyym::e},{pysm::zh,pyym::i}},//潪
{{pysm::sh,pyym::an},{pysm::t,pyym::an}},//潬
{{pysm::x,pyym::un},{pysm::y,pyym::in}},//潯
{{pysm::k,pyym::ui},{pysm::x,pyym::ie}},//潰
{{pysm::t,pyym::u},{pysm::zh,pyym::a}},//潳
{{pysm::s,pyym::a},{pysm::s,pyym::an}},//潵
{{pysm::ch,pyym::eng},{pysm::d,pyym::eng}},//澄
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//澉
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//澍
{{pysm::m,pyym::ian},{pysm::sh,pyym::eng}},//澠
{{pysm::z,pyym::ao},{pysm::c,pyym::ao}},//澡
{{pysm::h,pyym::uan},{pysm::h,pyym::an}},//澣
{{pysm::sh,pyym::i},{pysm::c,pyym::uo}},//澨
{{pysm::x,pyym::ue},{pysm::x,pyym::iao}},//澩
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//澬
{{pysm::nop,pyym::ao},{pysm::y,pyym::u}},//澳
{{pysm::h,pyym::uan},{pysm::x,pyym::uan}},//澴
{{pysm::j,pyym::i},{pysm::j,pyym::iao}},//激
{{pysm::l,pyym::ian},{pysm::x,pyym::ian}},//濂
{{pysm::g,pyym::uo},{pysm::w,pyym::o}},//濄
{{pysm::f,pyym::en},{pysm::p,pyym::en}},//濆
{{pysm::j,pyym::i},{pysm::sh,pyym::a}},//濈
{{pysm::d,pyym::ing},{pysm::t,pyym::ing}},//濎
{{pysm::m,pyym::i},{pysm::n,pyym::i}},//濔
{{pysm::n,pyym::ing},{pysm::n,pyym::i}},//濘
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//濞
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//濟
{{pysm::c,pyym::ui},{pysm::z,pyym::ui}},//濢
{{pysm::h,pyym::uo},{pysm::h,pyym::u}},//濩
{{pysm::l,pyym::an},{pysm::j,pyym::ian}},//濫
{{pysm::j,pyym::un},{pysm::x,pyym::un}},//濬
{{pysm::j,pyym::ian},{pysm::z,pyym::an}},//濺
{{pysm::y,pyym::ing},{pysm::j,pyym::iong}},//瀅
{{pysm::d,pyym::u},{pysm::d,pyym::ou}},//瀆
{{pysm::m,pyym::o},{pysm::m,pyym::ie}},//瀎
{{pysm::w,pyym::ei},{pysm::d,pyym::ui}},//瀢
{{pysm::h,pyym::uai},{pysm::w,pyym::ai}},//瀤
{{pysm::l,pyym::ong},{pysm::sh,pyym::uang}},//瀧
{{pysm::m,pyym::i},{pysm::n,pyym::i}},//瀰
{{pysm::j,pyym::ian},{pysm::z,pyym::un}},//瀳
{{pysm::y,pyym::ue},{pysm::y,pyym::ao}},//瀹
{{pysm::r,pyym::ang},{pysm::n,pyym::ang}},//瀼
{{pysm::sh,pyym::e},{pysm::n,pyym::i}},//灄
{{pysm::g,pyym::uan},{pysm::h,pyym::uan}},//灌
{{pysm::x,pyym::un},{pysm::q,pyym::uan}},//灥
{{pysm::b,pyym::iao},{pysm::h,pyym::uo}},//灬
{{pysm::d,pyym::eng},{pysm::d,pyym::ing}},//灯
{{pysm::zh,pyym::a},{pysm::y,pyym::u}},//灹
{{pysm::f,pyym::en},{pysm::b,pyym::en}},//炃
{{pysm::j,pyym::iong},{pysm::g,pyym::ui}},//炅
{{pysm::y,pyym::an},{pysm::t,pyym::an}},//炎
{{pysm::k,pyym::ai},{pysm::y,pyym::an}},//炏
{{pysm::p,pyym::ang},{pysm::f,pyym::eng}},//炐
{{pysm::k,pyym::ang},{pysm::h,pyym::ang}},//炕
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//炖
{{pysm::zh,pyym::uo},{pysm::ch,pyym::u}},//炪
{{pysm::p,pyym::ao},{pysm::b,pyym::ao}},//炮
{{pysm::p,pyym::ao},{pysm::f,pyym::ou}},//炰
{{pysm::j,pyym::iao},{pysm::y,pyym::ao}},//烄
{{pysm::x,pyym::iu},{pysm::x,pyym::iao}},//烋
{{pysm::w,pyym::u},{pysm::y,pyym::a}},//烏
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//烔
{{pysm::l,pyym::ao},{pysm::l,pyym::uo}},//烙
{{pysm::zh,pyym::u},{pysm::ch,pyym::ong}},//烛
{{pysm::x,pyym::uan},{pysm::h,pyym::ui}},//烜
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//烟
{{pysm::h,pyym::ui},{pysm::nop,pyym::ai}},//烠
{{pysm::x,pyym::ie},{pysm::ch,pyym::e}},//烲
{{pysm::t,pyym::ing},{pysm::j,pyym::ing}},//烴
{{pysm::y,pyym::an},{pysm::sh,pyym::an}},//烻
{{pysm::h,pyym::e},{pysm::h,pyym::uo}},//焃
{{pysm::x,pyym::un},{pysm::h,pyym::un}},//焄
{{pysm::k,pyym::u},{pysm::k,pyym::ao}},//焅
{{pysm::y,pyym::an},{pysm::y,pyym::i}},//焉
{{pysm::j,pyym::un},{pysm::q,pyym::u}},//焌
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//焏
{{pysm::d,pyym::ao},{pysm::t,pyym::ao}},//焘
{{pysm::w,pyym::u},{pysm::m,pyym::o}},//無
{{pysm::ch,pyym::ao},{pysm::j,pyym::u}},//焣
{{pysm::w,pyym::o},{pysm::nop,pyym::ai}},//焥
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//焦
{{pysm::r,pyym::uo},{pysm::r,pyym::e}},//焫
{{pysm::x,pyym::i},{pysm::y,pyym::i}},//焬
{{pysm::y,pyym::an},{pysm::y,pyym::i}},//焱
{{pysm::ch,pyym::ang},{pysm::g,pyym::ua}},//焻
{{pysm::l,pyym::ian},{pysm::l,pyym::an}},//煉
{{pysm::w,pyym::ei},{pysm::h,pyym::ui}},//煒
{{pysm::sh,pyym::an},{pysm::q,pyym::ian}},//煔
{{pysm::n,pyym::uan},{pysm::x,pyym::uan}},//煖
{{pysm::zh,pyym::a},{pysm::y,pyym::e}},//煠
{{pysm::x,pyym::u},{pysm::x,pyym::iu}},//煦
{{pysm::w,pyym::ei},{pysm::y,pyym::u}},//煨
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//煴
{{pysm::nop,pyym::en},{pysm::y,pyym::un}},//煾
{{pysm::h,pyym::uang},{pysm::y,pyym::e}},//熀
{{pysm::l,pyym::ian},{pysm::q,pyym::ian}},//熑
{{pysm::x,pyym::i},{pysm::y,pyym::i}},//熙
{{pysm::c,pyym::ong},{pysm::z,pyym::ong}},//熜
{{pysm::l,pyym::u},{pysm::nop,pyym::ao}},//熝
{{pysm::sh,pyym::u},{pysm::sh,pyym::ou}},//熟
{{pysm::s,pyym::ui},{pysm::c,pyym::ui}},//熣
{{pysm::t,pyym::eng},{pysm::t,pyym::ong}},//熥
{{pysm::h,pyym::an},{pysm::r,pyym::an}},//熯
{{pysm::ch,pyym::an},{pysm::d,pyym::an}},//燀
{{pysm::q,pyym::iao},{pysm::x,pyym::iao}},//燆
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//燉
{{pysm::f,pyym::en},{pysm::b,pyym::en}},//燌
{{pysm::s,pyym::i},{pysm::x,pyym::i}},//燍
{{pysm::f,pyym::an},{pysm::f,pyym::en}},//燔
{{pysm::x,pyym::un},{pysm::q,pyym::ian}},//燖
{{pysm::t,pyym::ang},{pysm::d,pyym::ang}},//燙
{{pysm::y,pyym::ing},{pysm::c,pyym::uo}},//營
{{pysm::y,pyym::u},{pysm::nop,pyym::ao}},//燠
{{pysm::t,pyym::ai},{pysm::l,pyym::ie}},//燤
{{pysm::z,pyym::ao},{pysm::s,pyym::ao}},//燥
{{pysm::zh,pyym::u},{pysm::k,pyym::uo}},//燭
{{pysm::r,pyym::u},{pysm::r,pyym::uan}},//燸
{{pysm::x,pyym::ian},{pysm::b,pyym::ing}},//燹
{{pysm::d,pyym::ao},{pysm::t,pyym::ao}},//燾
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//爄
{{pysm::b,pyym::ao},{pysm::b,pyym::o}},//爆
{{pysm::l,pyym::a},{pysm::l,pyym::ie}},//爉
{{pysm::k,pyym::uang},{pysm::h,pyym::uang}},//爌
{{pysm::y,pyym::an},{pysm::x,pyym::un}},//爓
{{pysm::j,pyym::ue},{pysm::j,pyym::iao}},//爝
{{pysm::ch,pyym::ong},{pysm::t,pyym::ong}},//爞
{{pysm::zh,pyym::ao},{pysm::zh,pyym::ua}},//爪
{{pysm::y,pyym::ao},{pysm::x,pyym::iao}},//爻
{{pysm::p,pyym::an},{pysm::q,pyym::iang}},//爿
{{pysm::p,pyym::ian},{pysm::p,pyym::an}},//片
{{pysm::b,pyym::ian},{pysm::m,pyym::ian}},//牑
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//牓
{{pysm::j,pyym::iu},{pysm::l,pyym::e}},//牞
{{pysm::t,pyym::a},{pysm::t,pyym::uo}},//牠
{{pysm::l,pyym::ao},{pysm::l,pyym::ou}},//牢
{{pysm::y,pyym::ou},{pysm::ch,pyym::ou}},//牰
{{pysm::d,pyym::i},{pysm::zh,pyym::ai}},//牴
{{pysm::j,pyym::i},{pysm::y,pyym::i}},//犄
{{pysm::zh,pyym::i},{pysm::t,pyym::e}},//犆
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//犍
{{pysm::m,pyym::ao},{pysm::l,pyym::i}},//犛
{{pysm::p,pyym::iao},{pysm::p,pyym::ao}},//犥
{{pysm::x,pyym::i},{pysm::s,pyym::uo}},//犧
{{pysm::k,pyym::ui},{pysm::r,pyym::ao}},//犪
{{pysm::g,pyym::e},{pysm::h,pyym::e}},//犵
{{pysm::k,pyym::ang},{pysm::g,pyym::ang}},//犺
{{pysm::h,pyym::uan},{pysm::f,pyym::an}},//犿
{{pysm::k,pyym::uang},{pysm::j,pyym::ue}},//狂
{{pysm::n,pyym::iu},{pysm::n,pyym::v}},//狃
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//狄
{{pysm::sh,pyym::eng},{pysm::x,pyym::ing}},//狌
{{pysm::t,pyym::uo},{pysm::y,pyym::i}},//狏
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//狡
{{pysm::h,pyym::e},{pysm::m,pyym::o}},//狢
{{pysm::t,pyym::a},{pysm::sh,pyym::i}},//狧
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//狪
{{pysm::m,pyym::ang},{pysm::zh,pyym::uo}},//狵
{{pysm::x,pyym::i},{pysm::sh,pyym::i}},//狶
{{pysm::l,pyym::ang},{pysm::h,pyym::ang}},//狼
{{pysm::b,pyym::ai},{pysm::p,pyym::i}},//猈
{{pysm::g,pyym::uo},{pysm::l,pyym::uo}},//猓
{{pysm::y,pyym::a},{pysm::w,pyym::ei}},//猚
{{pysm::m,pyym::ao},{pysm::m,pyym::iao}},//猫
{{pysm::ch,pyym::uan},{pysm::sh,pyym::an}},//猭
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//猵
{{pysm::y,pyym::ou},{pysm::y,pyym::ao}},//猶
{{pysm::b,pyym::o},{pysm::p,pyym::o}},//猼
{{pysm::d,pyym::ai},{pysm::nop,pyym::ai}},//獃
{{pysm::h,pyym::ao},{pysm::g,pyym::ao}},//獋
{{pysm::m,pyym::o},{pysm::m,pyym::u}},//獏
{{pysm::b,pyym::en},{pysm::f,pyym::en}},//獖
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//獝
{{pysm::t,pyym::ong},{pysm::zh,pyym::uang}},//獞
{{pysm::y,pyym::ao},{pysm::x,pyym::iao}},//獟
{{pysm::l,pyym::iao},{pysm::l,pyym::ao}},//獠
{{pysm::k,pyym::uai},{pysm::h,pyym::ua}},//獪
{{pysm::x,pyym::ian},{pysm::m,pyym::i}},//獮
{{pysm::n,pyym::ou},{pysm::r,pyym::u}},//獳
{{pysm::n,pyym::ao},{pysm::y,pyym::ou}},//獶
{{pysm::g,pyym::uang},{pysm::j,pyym::ing}},//獷
{{pysm::h,pyym::uan},{pysm::q,pyym::uan}},//獾
{{pysm::l,pyym::uo},{pysm::nop,pyym::e}},//玀
{{pysm::m,pyym::iao},{pysm::y,pyym::ao}},//玅
{{pysm::z,pyym::i},{pysm::x,pyym::uan}},//玆
{{pysm::w,pyym::ang},{pysm::y,pyym::u}},//王
{{pysm::ch,pyym::ang},{pysm::y,pyym::ang}},//玚
{{pysm::w,pyym::en},{pysm::m,pyym::in}},//玟
{{pysm::b,pyym::in},{pysm::f,pyym::en}},//玢
{{pysm::m,pyym::en},{pysm::y,pyym::un}},//玧
{{pysm::nop,pyym::an},{pysm::g,pyym::an}},//玵
{{pysm::x,pyym::uan},{pysm::x,pyym::ian}},//玹
{{pysm::c,pyym::i},{pysm::c,pyym::uo}},//玼
{{pysm::y,pyym::i},{pysm::t,pyym::ai}},//珆
{{pysm::z,pyym::u},{pysm::j,pyym::u}},//珇
{{pysm::l,pyym::uo},{pysm::l,pyym::i}},//珞
{{pysm::y,pyym::in},{pysm::k,pyym::en}},//珢
{{pysm::h,pyym::ang},{pysm::h,pyym::eng}},//珩
{{pysm::h,pyym::ui},{pysm::h,pyym::un}},//珲
{{pysm::ch,pyym::eng},{pysm::t,pyym::ing}},//珵
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//珶
{{pysm::x,pyym::uan},{pysm::q,pyym::iong}},//琁
{{pysm::p,pyym::in},{pysm::b,pyym::ing}},//琕
{{pysm::s,pyym::e},{pysm::c,pyym::ui}},//琗
{{pysm::sh,pyym::eng},{pysm::w,pyym::ang}},//琞
{{pysm::w,pyym::ei},{pysm::y,pyym::u}},//琟
{{pysm::z,pyym::uo},{pysm::zh,pyym::uo}},//琢
{{pysm::b,pyym::eng},{pysm::p,pyym::ei}},//琣
{{pysm::g,pyym::uan},{pysm::g,pyym::un}},//琯
{{pysm::h,pyym::un},{pysm::h,pyym::ui}},//琿
{{pysm::y,pyym::uan},{pysm::h,pyym::uan}},//瑗
{{pysm::zh,pyym::en},{pysm::t,pyym::ian}},//瑱
{{pysm::sh,pyym::u},{pysm::t,pyym::u}},//瑹
{{pysm::s,pyym::uo},{pysm::z,pyym::ao}},//璅
{{pysm::w,pyym::ei},{pysm::zh,pyym::i}},//璏
{{pysm::q,pyym::iong},{pysm::j,pyym::ue}},//璚
{{pysm::h,pyym::ui},{pysm::k,pyym::uai}},//璯
{{pysm::l,pyym::u},{pysm::f,pyym::u}},//璷
{{pysm::b,pyym::in},{pysm::p,pyym::ian}},//璸
{{pysm::z,pyym::i},{pysm::j,pyym::i}},//璾
{{pysm::q,pyym::iong},{pysm::x,pyym::uan}},//瓊
{{pysm::m,pyym::i},{pysm::x,pyym::i}},//瓕
{{pysm::q,pyym::iong},{pysm::w,pyym::ei}},//瓗
{{pysm::b,pyym::o},{pysm::p,pyym::ao}},//瓟
{{pysm::zh,pyym::i},{pysm::h,pyym::u}},//瓡
{{pysm::x,pyym::iang},{pysm::h,pyym::ong}},//瓨
{{pysm::q,pyym::ian},{pysm::w,pyym::a}},//瓩
{{pysm::b,pyym::u},{pysm::p,pyym::ou}},//瓿
{{pysm::zh,pyym::en},{pysm::j,pyym::uan}},//甄
{{pysm::zh,pyym::uan},{pysm::ch,pyym::uan}},//甎
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//甘
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//甫
{{pysm::y,pyym::ong},{pysm::d,pyym::ong}},//甬
{{pysm::b,pyym::eng},{pysm::q,pyym::i}},//甭
{{pysm::y,pyym::ou},{pysm::y,pyym::ao}},//由
{{pysm::zh,pyym::a},{pysm::y,pyym::ou}},//甴
{{pysm::z,pyym::ai},{pysm::z,pyym::i}},//甾
{{pysm::m,pyym::eng},{pysm::m,pyym::ang}},//甿
{{pysm::y,pyym::un},{pysm::t,pyym::ian}},//畇
{{pysm::f,pyym::u},{pysm::b,pyym::i}},//畐
{{pysm::d,pyym::a},{pysm::f,pyym::u}},//畗
{{pysm::ch,pyym::u},{pysm::x,pyym::u}},//畜
{{pysm::m,pyym::u},{pysm::m,pyym::ou}},//畝
{{pysm::c,pyym::e},{pysm::j,pyym::i}},//畟
{{pysm::p,pyym::an},{pysm::f,pyym::an}},//畨
{{pysm::sh,pyym::e},{pysm::y,pyym::u}},//畬
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//畸
{{pysm::w,pyym::an},{pysm::y,pyym::uan}},//畹
{{pysm::t,pyym::un},{pysm::t,pyym::uan}},//畽
{{pysm::j,pyym::ie},{pysm::q,pyym::ie}},//疌
{{pysm::zh,pyym::i},{pysm::d,pyym::i}},//疐
{{pysm::y,pyym::i},{pysm::n,pyym::ing}},//疑
{{pysm::d,pyym::ing},{pysm::n,pyym::e}},//疔
{{pysm::g,pyym::ang},{pysm::g,pyym::ong}},//疘
{{pysm::g,pyym::e},{pysm::y,pyym::i}},//疙
{{pysm::n,pyym::ve},{pysm::y,pyym::ao}},//疟
{{pysm::j,pyym::ue},{pysm::x,pyym::ue}},//疦
{{pysm::x,pyym::ia},{pysm::y,pyym::a}},//疨
{{pysm::d,pyym::an},{pysm::d,pyym::a}},//疸
{{pysm::zh,pyym::en},{pysm::ch,pyym::en}},//疹
{{pysm::f,pyym::a},{pysm::b,pyym::ian}},//疺
{{pysm::j,pyym::u},{pysm::g,pyym::ou}},//痀
{{pysm::t,pyym::eng},{pysm::ch,pyym::ong}},//痋
{{pysm::t,pyym::an},{pysm::sh,pyym::i}},//痑
{{pysm::h,pyym::en},{pysm::g,pyym::en}},//痕
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//痡
{{pysm::w,pyym::u},{pysm::p,pyym::i}},//痦
{{pysm::h,pyym::uan},{pysm::t,pyym::uan}},//痪
{{pysm::t,pyym::ian},{pysm::d,pyym::ian}},//痶
{{pysm::nop,pyym::e},{pysm::k,pyym::e}},//痾
{{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//瘈
{{pysm::y,pyym::ang},{pysm::d,pyym::ang}},//瘍
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//瘕
{{pysm::h,pyym::ui},{pysm::l,pyym::ei}},//瘣
{{pysm::ch,pyym::ai},{pysm::c,pyym::uo}},//瘥
{{pysm::n,pyym::ve},{pysm::y,pyym::ao}},//瘧
{{pysm::d,pyym::ian},{pysm::ch,pyym::en}},//瘨
{{pysm::ch,pyym::ou},{pysm::l,pyym::u}},//瘳
{{pysm::zh,pyym::ai},{pysm::j,pyym::i}},//瘵
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//瘻
{{pysm::l,pyym::iao},{pysm::sh,pyym::uo}},//療
{{pysm::d,pyym::an},{pysm::t,pyym::an}},//癉
{{pysm::nop,pyym::ai},{pysm::y,pyym::an}},//癌
{{pysm::g,pyym::ui},{pysm::w,pyym::ei}},//癐
{{pysm::l,pyym::i},{pysm::l,pyym::ai}},//癘
{{pysm::l,pyym::in},{pysm::b,pyym::ing}},//癛
{{pysm::l,pyym::ai},{pysm::l,pyym::a}},//癩
{{pysm::d,pyym::eng},{pysm::d,pyym::e}},//登
{{pysm::f,pyym::a},{pysm::b,pyym::o}},//發
{{pysm::b,pyym::ai},{pysm::b,pyym::o}},//白
{{pysm::q,pyym::ie},{pysm::b,pyym::ie}},//癿
{{pysm::d,pyym::e},{pysm::d,pyym::i}},//的
{{pysm::p,pyym::a},{pysm::b,pyym::a}},//皅
{{pysm::h,pyym::uang},{pysm::w,pyym::ang}},//皇
{{pysm::h,pyym::ao},{pysm::h,pyym::ui}},//皓
{{pysm::w,pyym::an},{pysm::h,pyym::uan}},//皖
{{pysm::p,pyym::o},{pysm::p,pyym::an}},//皤
{{pysm::zh,pyym::a},{pysm::c,pyym::u}},//皻
{{pysm::m,pyym::in},{pysm::m,pyym::ing}},//皿
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//盅
{{pysm::h,pyym::e},{pysm::k,pyym::e}},//盍
{{pysm::h,pyym::e},{pysm::nop,pyym::an}},//盒
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//盓
{{pysm::g,pyym::ai},{pysm::g,pyym::e}},//盖
{{pysm::sh,pyym::eng},{pysm::ch,pyym::eng}},//盛
{{pysm::m,pyym::eng},{pysm::m,pyym::ing}},//盟
{{pysm::j,pyym::ian},{pysm::k,pyym::an}},//監
{{pysm::p,pyym::an},{pysm::x,pyym::uan}},//盤
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ou}},//盩
{{pysm::d,pyym::ing},{pysm::ch,pyym::eng}},//盯
{{pysm::w,pyym::ang},{pysm::m,pyym::ang}},//盳
{{pysm::d,pyym::un},{pysm::zh,pyym::un}},//盹
{{pysm::x,pyym::i},{pysm::p,pyym::an}},//盻
{{pysm::p,pyym::an},{pysm::f,pyym::en}},//盼
{{pysm::y,pyym::un},{pysm::h,pyym::un}},//眃
{{pysm::d,pyym::an},{pysm::ch,pyym::en}},//眈
{{pysm::m,pyym::ao},{pysm::m,pyym::ei}},//眊
{{pysm::y,pyym::ang},{pysm::y,pyym::ing}},//眏
{{pysm::y,pyym::ao},{pysm::nop,pyym::ao}},//眑
{{pysm::y,pyym::i},{pysm::ch,pyym::i}},//眙
{{pysm::m,pyym::o},{pysm::m,pyym::ie}},//眜
{{pysm::m,pyym::ian},{pysm::m,pyym::in}},//眠
{{pysm::d,pyym::ie},{pysm::ch,pyym::ou}},//眣
{{pysm::b,pyym::ing},{pysm::f,pyym::ang}},//眪
{{pysm::m,pyym::i},{pysm::p,pyym::an}},//眫
{{pysm::d,pyym::ie},{pysm::zh,pyym::i}},//眰
{{pysm::y,pyym::an},{pysm::w,pyym::en}},//眼
{{pysm::m,pyym::o},{pysm::m,pyym::i}},//眽
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//睇
{{pysm::c,pyym::uo},{pysm::zh,pyym::uai}},//睉
{{pysm::l,pyym::eng},{pysm::ch,pyym::eng}},//睖
{{pysm::s,pyym::ui},{pysm::z,pyym::ui}},//睟
{{pysm::j,pyym::ie},{pysm::sh,pyym::e}},//睫
{{pysm::k,pyym::ui},{pysm::j,pyym::i}},//睽
{{pysm::g,pyym::ao},{pysm::h,pyym::ao}},//睾
{{pysm::m,pyym::ao},{pysm::w,pyym::u}},//瞀
{{pysm::k,pyym::ou},{pysm::j,pyym::i}},//瞉
{{pysm::q,pyym::iong},{pysm::h,pyym::uan}},//瞏
{{pysm::d,pyym::iao},{pysm::d,pyym::ou}},//瞗
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//瞜
{{pysm::m,pyym::an},{pysm::m,pyym::en}},//瞞
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//瞠
{{pysm::m,pyym::eng},{pysm::m,pyym::ang}},//瞢
{{pysm::r,pyym::un},{pysm::sh,pyym::un}},//瞤
{{pysm::p,pyym::ie},{pysm::b,pyym::i}},//瞥
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//瞯
{{pysm::x,pyym::u},{pysm::x,pyym::ue}},//瞲
{{pysm::l,pyym::in},{pysm::l,pyym::ian}},//瞵
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//瞷
{{pysm::n,pyym::ing},{pysm::ch,pyym::eng}},//矃
{{pysm::k,pyym::uang},{pysm::g,pyym::uo}},//矌
{{pysm::g,pyym::uan},{pysm::q,pyym::uan}},//矔
{{pysm::x,pyym::i},{pysm::l,pyym::i}},//矖
{{pysm::z,pyym::e},{pysm::zh,pyym::uo}},//矠
{{pysm::y,pyym::i},{pysm::x,pyym::ian}},//矣
{{pysm::sh,pyym::i},{pysm::d,pyym::an}},//石
{{pysm::q,pyym::i},{pysm::d,pyym::iao}},//矵
{{pysm::g,pyym::an},{pysm::h,pyym::an}},//矸
{{pysm::zh,pyym::e},{pysm::d,pyym::a}},//矺
{{pysm::k,pyym::u},{pysm::q,pyym::ia}},//矻
{{pysm::q,pyym::i},{pysm::q,pyym::ie}},//砌
{{pysm::y,pyym::an},{pysm::x,pyym::ing}},//研
{{pysm::zh,pyym::a},{pysm::z,pyym::uo}},//砟
{{pysm::j,pyym::u},{pysm::z,pyym::u}},//砠
{{pysm::k,pyym::e},{pysm::l,pyym::uo}},//砢
{{pysm::d,pyym::i},{pysm::zh,pyym::i}},//砥
{{pysm::f,pyym::u},{pysm::f,pyym::ei}},//砩
{{pysm::l,pyym::a},{pysm::l,pyym::i}},//砬
{{pysm::p,pyym::eng},{pysm::p,pyym::ing}},//砰
{{pysm::b,pyym::o},{pysm::nop,pyym::e}},//砵
{{pysm::k,pyym::uang},{pysm::g,pyym::uang}},//硄
{{pysm::g,pyym::ui},{pysm::h,pyym::e}},//硅
{{pysm::x,pyym::ing},{pysm::k,pyym::eng}},//硎
{{pysm::p,pyym::eng},{pysm::p,pyym::ing}},//硑
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//硔
{{pysm::k,pyym::eng},{pysm::q,pyym::ing}},//硜
{{pysm::x,pyym::iao},{pysm::q,pyym::iao}},//硝
{{pysm::m,pyym::ang},{pysm::b,pyym::ang}},//硥
{{pysm::l,pyym::uo},{pysm::l,pyym::ong}},//硦
{{pysm::y,pyym::ong},{pysm::t,pyym::ong}},//硧
{{pysm::l,pyym::iu},{pysm::ch,pyym::u}},//硫
{{pysm::y,pyym::ing},{pysm::g,pyym::eng}},//硬
{{pysm::ch,pyym::en},{pysm::c,pyym::en}},//硶
{{pysm::zh,pyym::ui},{pysm::d,pyym::uo}},//硾
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//碂
{{pysm::m,pyym::in},{pysm::h,pyym::un}},//碈
{{pysm::j,pyym::ian},{pysm::zh,pyym::an}},//碊
{{pysm::q,pyym::ue},{pysm::x,pyym::i}},//碏
{{pysm::n,pyym::ao},{pysm::g,pyym::ang}},//碙
{{pysm::d,pyym::ie},{pysm::sh,pyym::e}},//碟
{{pysm::d,pyym::u},{pysm::zh,pyym::ou}},//碡
{{pysm::t,pyym::i},{pysm::d,pyym::i}},//碮
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//碱
{{pysm::q,pyym::ue},{pysm::q,pyym::iao}},//碻
{{pysm::s,pyym::u},{pysm::x,pyym::ie}},//碿
{{pysm::s,pyym::i},{pysm::t,pyym::i}},//磃
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//磅
{{pysm::w,pyym::ei},{pysm::k,pyym::ui}},//磈
{{pysm::x,pyym::i},{pysm::q,pyym::i}},//磎
{{pysm::l,pyym::ian},{pysm::q,pyym::ian}},//磏
{{pysm::d,pyym::ui},{pysm::zh,pyym::ui}},//磓
{{pysm::nop,pyym::ao},{pysm::q,pyym::iao}},//磝
{{pysm::l,pyym::iu},{pysm::l,pyym::u}},//磟
{{pysm::ch,pyym::en},{pysm::c,pyym::a}},//磣
{{pysm::q,pyym::i},{pysm::zh,pyym::u}},//磩
{{pysm::l,pyym::in},{pysm::l,pyym::ing}},//磷
{{pysm::t,pyym::an},{pysm::d,pyym::ian}},//磹
{{pysm::p,pyym::an},{pysm::b,pyym::o}},//磻
{{pysm::z,pyym::a},{pysm::sh,pyym::e}},//磼
{{pysm::q,pyym::iao},{pysm::nop,pyym::ao}},//磽
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//礆
{{pysm::k,pyym::e},{pysm::h,pyym::uo}},//礊
{{pysm::q,pyym::ue},{pysm::h,pyym::u}},//礐
{{pysm::nop,pyym::e},{pysm::q,pyym::i}},//礘
{{pysm::nop,pyym::ai},{pysm::y,pyym::i}},//礙
{{pysm::x,pyym::ian},{pysm::x,pyym::in}},//礥
{{pysm::k,pyym::uang},{pysm::g,pyym::ong}},//礦
{{pysm::l,pyym::i},{pysm::l,pyym::uo}},//礫
{{pysm::q,pyym::i},{pysm::zh,pyym::i}},//祁
{{pysm::q,pyym::i},{pysm::g,pyym::ui}},//祈
{{pysm::b,pyym::eng},{pysm::f,pyym::ang}},//祊
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//祌
{{pysm::f,pyym::u},{pysm::f,pyym::ei}},//祓
{{pysm::m,pyym::i},{pysm::b,pyym::i}},//祕
{{pysm::z,pyym::u},{pysm::j,pyym::ie}},//祖
{{pysm::c,pyym::i},{pysm::s,pyym::i}},//祠
{{pysm::m,pyym::i},{pysm::n,pyym::i}},//祢
{{pysm::j,pyym::i},{pysm::zh,pyym::ai}},//祭
{{pysm::sh,pyym::ui},{pysm::l,pyym::ei}},//祱
{{pysm::ch,pyym::an},{pysm::sh,pyym::an}},//禅
{{pysm::zh,pyym::en},{pysm::zh,pyym::eng}},//禎
{{pysm::y,pyym::ang},{pysm::sh,pyym::ang}},//禓
{{pysm::y,pyym::ong},{pysm::y,pyym::ing}},//禜
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//禨
{{pysm::l,pyym::i},{pysm::ch,pyym::i}},//离
{{pysm::ch,pyym::a},{pysm::n,pyym::a}},//秅
{{pysm::y,pyym::i},{pysm::zh,pyym::i}},//秇
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//种
{{pysm::h,pyym::ao},{pysm::m,pyym::ao}},//秏
{{pysm::z,pyym::u},{pysm::j,pyym::u}},//租
{{pysm::ch,pyym::eng},{pysm::p,pyym::ing}},//秤
{{pysm::j,pyym::i},{pysm::zh,pyym::i}},//积
{{pysm::ch,pyym::eng},{pysm::ch,pyym::en}},//称
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//秲
{{pysm::h,pyym::uo},{pysm::k,pyym::uo}},//秳
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//秴
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//秸
{{pysm::y,pyym::i},{pysm::ch,pyym::i}},//移
{{pysm::x,pyym::un},{pysm::z,pyym::e}},//稄
{{pysm::t,pyym::u},{pysm::sh,pyym::u}},//稌
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//稘
{{pysm::l,pyym::eng},{pysm::l,pyym::ing}},//稜
{{pysm::k,pyym::e},{pysm::h,pyym::ua}},//稞
{{pysm::b,pyym::ing},{pysm::l,pyym::in}},//稟
{{pysm::x,pyym::i},{pysm::q,pyym::ie}},//稧
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//稫
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//種
{{pysm::ch,pyym::eng},{pysm::ch,pyym::en}},//稱
{{pysm::z,pyym::i},{pysm::j,pyym::iu}},//稵
{{pysm::j,pyym::i},{pysm::z,pyym::e}},//稷
{{pysm::zh,pyym::en},{pysm::b,pyym::ian}},//稹
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//稽
{{pysm::l,pyym::u},{pysm::j,pyym::iu}},//穋
{{pysm::x,pyym::iao},{pysm::r,pyym::ao}},//穘
{{pysm::zh,pyym::uo},{pysm::b,pyym::o}},//穛
{{pysm::zh,pyym::ong},{pysm::t,pyym::ong}},//穜
{{pysm::j,pyym::i},{pysm::z,pyym::i}},//穧
{{pysm::ch,pyym::eng},{pysm::b,pyym::ie}},//穪
{{pysm::h,pyym::uo},{pysm::h,pyym::u}},//穫
{{pysm::b,pyym::iao},{pysm::p,pyym::ao}},//穮
{{pysm::r,pyym::ang},{pysm::r,pyym::eng}},//穰
{{pysm::zh,pyym::uo},{pysm::j,pyym::ue}},//穱
{{pysm::c,pyym::uan},{pysm::z,pyym::an}},//穳
{{pysm::x,pyym::ue},{pysm::j,pyym::ue}},//穴
{{pysm::w,pyym::a},{pysm::y,pyym::a}},//穵
{{pysm::q,pyym::iong},{pysm::k,pyym::ong}},//穹
{{pysm::ch,pyym::uan},{pysm::y,pyym::uan}},//穿
{{pysm::zh,pyym::un},{pysm::t,pyym::un}},//窀
{{pysm::zh,pyym::u},{pysm::k,pyym::u}},//窋
{{pysm::g,pyym::ui},{pysm::w,pyym::a}},//窐
{{pysm::zh,pyym::i},{pysm::d,pyym::ie}},//窒
{{pysm::j,pyym::iao},{pysm::z,pyym::ao}},//窖
{{pysm::ch,pyym::uang},{pysm::c,pyym::ong}},//窗
{{pysm::x,pyym::un},{pysm::y,pyym::in}},//窨
{{pysm::y,pyym::a},{pysm::y,pyym::e}},//窫
{{pysm::y,pyym::u},{pysm::d,pyym::ou}},//窬
{{pysm::y,pyym::ao},{pysm::q,pyym::iao}},//窯
{{pysm::j,pyym::u},{pysm::l,pyym::ou}},//窶
{{pysm::zh,pyym::ao},{pysm::k,pyym::e}},//窼
{{pysm::k,pyym::uan},{pysm::c,pyym::uan}},//窾
{{pysm::d,pyym::ou},{pysm::d,pyym::u}},//竇
{{pysm::l,pyym::i},{pysm::w,pyym::ei}},//立
{{pysm::q,pyym::u},{pysm::k,pyym::ou}},//竘
{{pysm::l,pyym::ong},{pysm::n,pyym::eng}},//竜
{{pysm::t,pyym::ong},{pysm::zh,pyym::ong}},//童
{{pysm::j,pyym::ing},{pysm::zh,pyym::en}},//竧
{{pysm::w,pyym::ai},{pysm::h,pyym::ua}},//竵
{{pysm::zh,pyym::u},{pysm::d,pyym::u}},//竺
{{pysm::l,pyym::e},{pysm::j,pyym::in}},//竻
{{pysm::zh,pyym::ui},{pysm::r,pyym::ui}},//笍
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//笓
{{pysm::t,pyym::iao},{pysm::sh,pyym::ao}},//笤
{{pysm::c,pyym::e},{pysm::sh,pyym::an}},//笧
{{pysm::f,pyym::u},{pysm::f,pyym::ei}},//笰
{{pysm::x,pyym::iao},{pysm::j,pyym::iao}},//筊
{{pysm::j,pyym::in},{pysm::q,pyym::ian}},//筋
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//筒
{{pysm::y,pyym::un},{pysm::j,pyym::un}},//筠
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//筧
{{pysm::c,pyym::e},{pysm::j,pyym::ia}},//筴
{{pysm::nop,pyym::ou},{pysm::w,pyym::u}},//筽
{{pysm::t,pyym::ai},{pysm::ch,pyym::i}},//箈
{{pysm::g,pyym::uai},{pysm::d,pyym::ai}},//箉
{{pysm::d,pyym::ao},{pysm::zh,pyym::ao}},//箌
{{pysm::ch,pyym::i},{pysm::h,pyym::u}},//箎
{{pysm::sh,pyym::a},{pysm::zh,pyym::a}},//箑
{{pysm::j,pyym::un},{pysm::q,pyym::un}},//箘
{{pysm::ch,pyym::ui},{pysm::zh,pyym::ui}},//箠
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//箢
{{pysm::r,pyym::uo},{pysm::n,pyym::a}},//箬
{{pysm::zh,pyym::en},{pysm::j,pyym::ian}},//箴
{{pysm::x,pyym::ing},{pysm::sh,pyym::eng}},//箵
{{pysm::y,pyym::i},{pysm::sh,pyym::i}},//箷
{{pysm::zh,pyym::u},{pysm::zh,pyym::uo}},//箸
{{pysm::ch,pyym::uan},{pysm::d,pyym::uan}},//篅
{{pysm::h,pyym::uang},{pysm::h,pyym::ong}},//篊
{{pysm::y,pyym::un},{pysm::x,pyym::un}},//篔
{{pysm::p,pyym::eng},{pysm::p,pyym::ang}},//篣
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//篦
{{pysm::zh,pyym::uo},{pysm::h,pyym::uo}},//篧
{{pysm::sh,pyym::ai},{pysm::sh,pyym::i}},//篩
{{pysm::q,pyym::iang},{pysm::c,pyym::ang}},//篬
{{pysm::h,pyym::ui},{pysm::s,pyym::ui}},//篲
{{pysm::d,pyym::i},{pysm::zh,pyym::u}},//篴
{{pysm::p,pyym::iao},{pysm::b,pyym::iao}},//篻
{{pysm::t,pyym::uan},{pysm::zh,pyym::uan}},//篿
{{pysm::z,pyym::e},{pysm::zh,pyym::ai}},//簀
{{pysm::g,pyym::ui},{pysm::g,pyym::uo}},//簂
{{pysm::z,pyym::ao},{pysm::ch,pyym::ou}},//簉
{{pysm::c,pyym::e},{pysm::j,pyym::i}},//簎
{{pysm::sh,pyym::ai},{pysm::s,pyym::i}},//簛
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//簜
{{pysm::s,pyym::un},{pysm::zh,pyym::uan}},//簨
{{pysm::zh,pyym::ua},{pysm::k,pyym::e}},//簻
{{pysm::b,pyym::u},{pysm::b,pyym::o}},//簿
{{pysm::zh,pyym::en},{pysm::j,pyym::ian}},//籈
{{pysm::n,pyym::ie},{pysm::m,pyym::i}},//籋
{{pysm::ch,pyym::ou},{pysm::t,pyym::ao}},//籌
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//籍
{{pysm::zh,pyym::uan},{pysm::z,pyym::uan}},//籑
{{pysm::s,pyym::ou},{pysm::sh,pyym::u}},//籔
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//籧
{{pysm::d,pyym::i},{pysm::z,pyym::a}},//籴
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//粃
{{pysm::sh,pyym::a},{pysm::ch,pyym::ao}},//粆
{{pysm::k,pyym::ang},{pysm::j,pyym::ing}},//粇
{{pysm::zh,pyym::an},{pysm::n,pyym::ian}},//粘
{{pysm::c,pyym::e},{pysm::s,pyym::e}},//粣
{{pysm::zh,pyym::ou},{pysm::y,pyym::u}},//粥
{{pysm::c,pyym::ui},{pysm::s,pyym::ui}},//粹
{{pysm::j,pyym::ing},{pysm::q,pyym::ing}},//精
{{pysm::g,pyym::uo},{pysm::h,pyym::ua}},//粿
{{pysm::s,pyym::an},{pysm::sh,pyym::en}},//糁
{{pysm::m,pyym::i},{pysm::m,pyym::ei}},//糜
{{pysm::s,pyym::an},{pysm::sh,pyym::en}},//糝
{{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//糶
{{pysm::m,pyym::i},{pysm::s,pyym::i}},//糸
{{pysm::x,pyym::i},{pysm::j,pyym::i}},//系
{{pysm::j,pyym::iu},{pysm::j,pyym::iao}},//糾
{{pysm::y,pyym::u},{pysm::nop,pyym::ou}},//紆
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//紒
{{pysm::sh,pyym::a},{pysm::m,pyym::iao}},//紗
{{pysm::f,pyym::ang},{pysm::b,pyym::ang}},//紡
{{pysm::z,pyym::a},{pysm::zh,pyym::a}},//紥
{{pysm::ch,pyym::ou},{pysm::zh,pyym::ou}},//紬
{{pysm::z,pyym::a},{pysm::zh,pyym::a}},//紮
{{pysm::x,pyym::ie},{pysm::y,pyym::i}},//紲
{{pysm::b,pyym::o},{pysm::b,pyym::i}},//紴
{{pysm::zh,pyym::u},{pysm::sh,pyym::u}},//紵
{{pysm::sh,pyym::ao},{pysm::ch,pyym::ao}},//紹
{{pysm::f,pyym::u},{pysm::f,pyym::ei}},//紼
{{pysm::x,pyym::ian},{pysm::x,pyym::uan}},//絃
{{pysm::z,pyym::u},{pysm::q,pyym::u}},//組
{{pysm::x,pyym::ie},{pysm::y,pyym::i}},//絏
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//結
{{pysm::g,pyym::ua},{pysm::k,pyym::ua}},//絓
{{pysm::b,pyym::ai},{pysm::m,pyym::o}},//絔
{{pysm::h,pyym::uan},{pysm::g,pyym::eng}},//絙
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//絞
{{pysm::g,pyym::ai},{pysm::nop,pyym::ai}},//絠
{{pysm::l,pyym::uo},{pysm::l,pyym::ao}},//絡
{{pysm::x,pyym::uan},{pysm::x,pyym::un}},//絢
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//絧
{{pysm::g,pyym::ai},{pysm::h,pyym::ai}},//絯
{{pysm::j,pyym::uan},{pysm::x,pyym::uan}},//絹
{{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//絺
{{pysm::x,pyym::iao},{pysm::sh,pyym::ao}},//綃
{{pysm::h,pyym::uan},{pysm::w,pyym::an}},//綄
{{pysm::q,pyym::in},{pysm::x,pyym::ian}},//綅
{{pysm::g,pyym::eng},{pysm::b,pyym::ing}},//綆
{{pysm::t,pyym::ou},{pysm::x,pyym::iu}},//綉
{{pysm::y,pyym::an},{pysm::x,pyym::ian}},//綖
{{pysm::z,pyym::ong},{pysm::z,pyym::eng}},//綜
{{pysm::l,pyym::i},{pysm::l,pyym::ie}},//綟
{{pysm::w,pyym::ei},{pysm::y,pyym::i}},//維
{{pysm::q,pyym::i},{pysm::q,pyym::ing}},//綮
{{pysm::zh,pyym::ui},{pysm::ch,pyym::uo}},//綴
{{pysm::c,pyym::ui},{pysm::z,pyym::u}},//綷
{{pysm::l,pyym::un},{pysm::g,pyym::uan}},//綸
{{pysm::q,pyym::i},{pysm::y,pyym::i}},//綺
{{pysm::ch,pyym::uo},{pysm::ch,pyym::ao}},//綽
{{pysm::g,pyym::un},{pysm::h,pyym::un}},//緄
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//総
{{pysm::l,pyym::v},{pysm::l,pyym::u}},//緑
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//緝
{{pysm::ch,pyym::ong},{pysm::zh,pyym::ong}},//緟
{{pysm::m,pyym::iao},{pysm::m,pyym::ao}},//緢
{{pysm::x,pyym::ie},{pysm::y,pyym::e}},//緤
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//緶
{{pysm::y,pyym::un},{pysm::g,pyym::un}},//緷
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//緼
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//縎
{{pysm::ch,pyym::en},{pysm::zh,pyym::en}},//縝
{{pysm::r,pyym::u},{pysm::r,pyym::ong}},//縟
{{pysm::z,pyym::ai},{pysm::z,pyym::eng}},//縡
{{pysm::x,pyym::ian},{pysm::x,pyym::uan}},//縣
{{pysm::s,pyym::uo},{pysm::s,pyym::u}},//縮
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//縯
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//縱
{{pysm::j,pyym::uan},{pysm::zh,pyym::uan}},//縳
{{pysm::m,pyym::u},{pysm::m,pyym::o}},//縸
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//總
{{pysm::s,pyym::ui},{pysm::c,pyym::ui}},//繀
{{pysm::s,pyym::ao},{pysm::z,pyym::ao}},//繅
{{pysm::q,pyym::iao},{pysm::j,pyym::ue}},//繑
{{pysm::z,pyym::eng},{pysm::c,pyym::eng}},//繒
{{pysm::y,pyym::u},{pysm::j,pyym::ue}},//繘
{{pysm::l,pyym::iao},{pysm::r,pyym::ao}},//繚
{{pysm::h,pyym::ui},{pysm::g,pyym::ui}},//繪
{{pysm::x,pyym::i},{pysm::j,pyym::i}},//繫
{{pysm::y,pyym::i},{pysm::sh,pyym::i}},//繹
{{pysm::x,pyym::u},{pysm::r,pyym::u}},//繻
{{pysm::p,pyym::u},{pysm::f,pyym::u}},//纀
{{pysm::y,pyym::ao},{pysm::l,pyym::i}},//纅
{{pysm::c,pyym::ai},{pysm::sh,pyym::an}},//纔
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//纖
{{pysm::d,pyym::ao},{pysm::d,pyym::u}},//纛
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//红
{{pysm::x,pyym::ian},{pysm::q,pyym::ian}},//纤
{{pysm::g,pyym::e},{pysm::h,pyym::e}},//纥
{{pysm::y,pyym::ue},{pysm::y,pyym::ao}},//约
{{pysm::l,pyym::un},{pysm::g,pyym::uan}},//纶
{{pysm::g,pyym::ei},{pysm::j,pyym::i}},//给
{{pysm::l,pyym::uo},{pysm::l,pyym::ao}},//络
{{pysm::ch,pyym::uo},{pysm::ch,pyym::ao}},//绰
{{pysm::z,pyym::ong},{pysm::z,pyym::eng}},//综
{{pysm::l,pyym::v},{pysm::l,pyym::u}},//绿
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//缉
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//缏
{{pysm::s,pyym::uo},{pysm::s,pyym::u}},//缩
{{pysm::q,pyym::iao},{pysm::s,pyym::ao}},//缲
{{pysm::j,pyym::iao},{pysm::zh,pyym::uo}},//缴
{{pysm::q,pyym::ue},{pysm::k,pyym::ui}},//缺
{{pysm::zh,pyym::u},{pysm::d,pyym::u}},//罜
{{pysm::j,pyym::u},{pysm::j,pyym::ie}},//罝
{{pysm::t,pyym::i},{pysm::k,pyym::un}},//罤
{{pysm::l,pyym::an},{pysm::n,pyym::an}},//罱
{{pysm::m,pyym::i},{pysm::m,pyym::ie}},//羋
{{pysm::y,pyym::ang},{pysm::x,pyym::iang}},//羏
{{pysm::q,pyym::iang},{pysm::y,pyym::ou}},//羗
{{pysm::g,pyym::ao},{pysm::m,pyym::ei}},//羙
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//羛
{{pysm::q,pyym::iang},{pysm::q,pyym::ian}},//羥
{{pysm::s,pyym::uo},{pysm::z,pyym::ui}},//羧
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//義
{{pysm::q,pyym::iang},{pysm::k,pyym::ang}},//羫
{{pysm::l,pyym::ei},{pysm::l,pyym::ian}},//羸
{{pysm::g,pyym::eng},{pysm::l,pyym::ang}},//羹
{{pysm::y,pyym::u},{pysm::h,pyym::u}},//羽
{{pysm::l,pyym::iu},{pysm::l,pyym::u}},//翏
{{pysm::x,pyym::iao},{pysm::sh,pyym::u}},//翛
{{pysm::d,pyym::i},{pysm::zh,pyym::ai}},//翟
{{pysm::d,pyym::ao},{pysm::zh,pyym::ou}},//翢
{{pysm::h,pyym::e},{pysm::l,pyym::i}},//翮
{{pysm::h,pyym::e},{pysm::h,pyym::ao}},//翯
{{pysm::h,pyym::ou},{pysm::q,pyym::u}},//翵
{{pysm::nop,pyym::er},{pysm::n,pyym::eng}},//而
{{pysm::r,pyym::uan},{pysm::n,pyym::uo}},//耎
{{pysm::n,pyym::ai},{pysm::nop,pyym::er}},//耏
{{pysm::n,pyym::ai},{pysm::n,pyym::eng}},//耐
{{pysm::d,pyym::uan},{pysm::zh,pyym::uan}},//耑
{{pysm::h,pyym::ao},{pysm::m,pyym::ao}},//耗
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//耙
{{pysm::y,pyym::i},{pysm::ch,pyym::i}},//耛
{{pysm::q,pyym::u},{pysm::ch,pyym::u}},//耝
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//耤
{{pysm::zh,pyym::a},{pysm::z,pyym::e}},//耫
{{pysm::nop,pyym::er},{pysm::r,pyym::eng}},//耳
{{pysm::y,pyym::e},{pysm::x,pyym::ie}},//耶
{{pysm::d,pyym::a},{pysm::zh,pyym::e}},//耷
{{pysm::y,pyym::un},{pysm::y,pyym::ing}},//耺
{{pysm::l,pyym::iao},{pysm::l,pyym::iu}},//聊
{{pysm::nop,pyym::er},{pysm::n,pyym::v}},//聏
{{pysm::t,pyym::ie},{pysm::zh,pyym::e}},//聑
{{pysm::g,pyym::ua},{pysm::g,pyym::uo}},//聒
{{pysm::p,pyym::in},{pysm::p,pyym::ing}},//聘
{{pysm::nop,pyym::ao},{pysm::y,pyym::ou}},//聱
{{pysm::zh,pyym::i},{pysm::t,pyym::e}},//職
{{pysm::n,pyym::i},{pysm::j,pyym::ian}},//聻
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//肄
{{pysm::s,pyym::i},{pysm::t,pyym::i}},//肆
{{pysm::r,pyym::ou},{pysm::r,pyym::u}},//肉
{{pysm::g,pyym::e},{pysm::q,pyym::i}},//肐
{{pysm::b,pyym::o},{pysm::d,pyym::i}},//肑
{{pysm::r,pyym::ong},{pysm::ch,pyym::en}},//肜
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//肢
{{pysm::h,pyym::an},{pysm::q,pyym::in}},//肣
{{pysm::f,pyym::ei},{pysm::b,pyym::i}},//肥
{{pysm::p,pyym::ang},{pysm::f,pyym::eng}},//肨
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//肩
{{pysm::n,pyym::a},{pysm::n,pyym::u}},//肭
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//肶
{{pysm::q,pyym::ian},{pysm::x,pyym::u}},//肷
{{pysm::x,pyym::i},{pysm::b,pyym::i}},//肸
{{pysm::f,pyym::ei},{pysm::p,pyym::ei}},//肺
{{pysm::sh,pyym::en},{pysm::ch,pyym::en}},//胂
{{pysm::f,pyym::ei},{pysm::b,pyym::i}},//胇
{{pysm::z,pyym::i},{pysm::f,pyym::ei}},//胏
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//胓
{{pysm::f,pyym::u},{pysm::zh,pyym::ou}},//胕
{{pysm::p,pyym::ang},{pysm::p,pyym::an}},//胖
{{pysm::zh,pyym::en},{pysm::zh,pyym::un}},//胗
{{pysm::b,pyym::ao},{pysm::p,pyym::ao}},//胞
{{pysm::n,pyym::u},{pysm::n,pyym::v}},//胬
{{pysm::h,pyym::ai},{pysm::g,pyym::ai}},//胲
{{pysm::g,pyym::e},{pysm::g,pyym::a}},//胳
{{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//胵
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//胶
{{pysm::nop,pyym::an},{pysm::nop,pyym::e}},//胺
{{pysm::g,pyym::ui},{pysm::k,pyym::ui}},//胿
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//脀
{{pysm::m,pyym::ai},{pysm::m,pyym::o}},//脈
{{pysm::m,pyym::ai},{pysm::m,pyym::o}},//脉
{{pysm::l,pyym::uan},{pysm::j,pyym::i}},//脔
{{pysm::w,pyym::an},{pysm::w,pyym::en}},//脕
{{pysm::w,pyym::an},{pysm::h,pyym::uan}},//脘
{{pysm::j,pyym::iao},{pysm::j,pyym::ue}},//脚
{{pysm::j,pyym::ing},{pysm::k,pyym::eng}},//脛
{{pysm::c,pyym::uo},{pysm::q,pyym::ie}},//脞
{{pysm::sh,pyym::an},{pysm::ch,pyym::an}},//脠
{{pysm::d,pyym::e},{pysm::t,pyym::e}},//脦
{{pysm::j,pyym::uan},{pysm::z,pyym::ui}},//脧
{{pysm::c,pyym::u},{pysm::j,pyym::i}},//脨
{{pysm::x,pyym::in},{pysm::ch,pyym::i}},//脪
{{pysm::n,pyym::ei},{pysm::t,pyym::ui}},//脮
{{pysm::p,pyym::u},{pysm::f,pyym::u}},//脯
{{pysm::t,pyym::uo},{pysm::t,pyym::ui}},//脱
{{pysm::zh,pyym::ang},{pysm::ch,pyym::ang}},//脹
{{pysm::c,pyym::ui},{pysm::s,pyym::ui}},//脺
{{pysm::l,pyym::iang},{pysm::l,pyym::ang}},//脼
{{pysm::l,pyym::a},{pysm::x,pyym::i}},//腊
{{pysm::r,pyym::en},{pysm::d,pyym::ian}},//腍
{{pysm::ch,pyym::uo},{pysm::zh,pyym::ui}},//腏
{{pysm::q,pyym::iang},{pysm::k,pyym::ong}},//腔
{{pysm::sh,pyym::u},{pysm::y,pyym::u}},//腧
{{pysm::t,pyym::u},{pysm::d,pyym::un}},//腯
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//腱
{{pysm::j,pyym::iao},{pysm::j,pyym::ue}},//腳
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//膀
{{pysm::l,pyym::u},{pysm::b,pyym::iao}},//膔
{{pysm::g,pyym::uo},{pysm::h,pyym::uo}},//膕
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//膘
{{pysm::f,pyym::u},{pysm::l,pyym::u}},//膚
{{pysm::l,pyym::in},{pysm::l,pyym::ian}},//膦
{{pysm::t,pyym::eng},{pysm::t,pyym::un}},//膯
{{pysm::f,pyym::an},{pysm::p,pyym::an}},//膰
{{pysm::s,pyym::ui},{pysm::w,pyym::ei}},//膸
{{pysm::sh,pyym::an},{pysm::d,pyym::an}},//膻
{{pysm::b,pyym::i},{pysm::b,pyym::ei}},//臂
{{pysm::j,pyym::ue},{pysm::j,pyym::u}},//臄
{{pysm::l,pyym::a},{pysm::g,pyym::e}},//臈
{{pysm::w,pyym::o},{pysm::y,pyym::ue}},//臒
{{pysm::l,pyym::a},{pysm::l,pyym::ie}},//臘
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//臚
{{pysm::n,pyym::i},{pysm::l,pyym::uan}},//臡
{{pysm::z,pyym::a},{pysm::z,pyym::an}},//臢
{{pysm::g,pyym::uang},{pysm::j,pyym::iong}},//臦
{{pysm::z,pyym::ang},{pysm::c,pyym::ang}},//臧
{{pysm::g,pyym::uang},{pysm::j,pyym::iong}},//臩
{{pysm::ch,pyym::ou},{pysm::x,pyym::iu}},//臭
{{pysm::m,pyym::ian},{pysm::b,pyym::ian}},//臱
{{pysm::zh,pyym::i},{pysm::d,pyym::ie}},//至
{{pysm::zh,pyym::i},{pysm::zh,pyym::ui}},//致
{{pysm::d,pyym::ie},{pysm::zh,pyym::i}},//臷
{{pysm::zh,pyym::i},{pysm::j,pyym::in}},//臸
{{pysm::x,pyym::ing},{pysm::x,pyym::in}},//興
{{pysm::sh,pyym::e},{pysm::g,pyym::ua}},//舌
{{pysm::sh,pyym::e},{pysm::sh,pyym::i}},//舍
{{pysm::sh,pyym::u},{pysm::y,pyym::u}},//舒
{{pysm::t,pyym::ian},{pysm::t,pyym::an}},//舔
{{pysm::h,pyym::ua},{pysm::q,pyym::i}},//舙
{{pysm::ch,pyym::uan},{pysm::x,pyym::iang}},//舡
{{pysm::ch,pyym::uan},{pysm::f,pyym::an}},//舩
{{pysm::zh,pyym::u},{pysm::zh,pyym::ou}},//舳
{{pysm::q,pyym::iong},{pysm::h,pyym::ong}},//舼
{{pysm::p,pyym::ang},{pysm::f,pyym::eng}},//舽
{{pysm::n,pyym::ian},{pysm::q,pyym::ian}},//艌
{{pysm::m,pyym::u},{pysm::m,pyym::o}},//艒
{{pysm::y,pyym::ao},{pysm::t,pyym::iao}},//艞
{{pysm::h,pyym::uo},{pysm::w,pyym::o}},//艧
{{pysm::g,pyym::en},{pysm::h,pyym::en}},//艮
{{pysm::s,pyym::e},{pysm::sh,pyym::ai}},//色
{{pysm::l,pyym::e},{pysm::j,pyym::i}},//艻
{{pysm::t,pyym::ing},{pysm::d,pyym::ing}},//艼
{{pysm::j,pyym::iao},{pysm::q,pyym::iu}},//艽
{{pysm::nop,pyym::ai},{pysm::y,pyym::i}},//艾
{{pysm::n,pyym::ai},{pysm::r,pyym::eng}},//艿
{{pysm::ch,pyym::ai},{pysm::ch,pyym::a}},//芆
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//芋
{{pysm::q,pyym::iong},{pysm::x,pyym::iong}},//芎
{{pysm::h,pyym::u},{pysm::x,pyym::ia}},//芐
{{pysm::h,pyym::ui},{pysm::h,pyym::u}},//芔
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//芘
{{pysm::t,pyym::un},{pysm::ch,pyym::un}},//芚
{{pysm::sh,pyym::an},{pysm::w,pyym::ei}},//芟
{{pysm::f,pyym::u},{pysm::f,pyym::ou}},//芣
{{pysm::j,pyym::ie},{pysm::g,pyym::ai}},//芥
{{pysm::l,pyym::u},{pysm::h,pyym::u}},//芦
{{pysm::x,pyym::u},{pysm::zh,pyym::u}},//芧
{{pysm::q,pyym::in},{pysm::y,pyym::in}},//芩
{{pysm::q,pyym::i},{pysm::ch,pyym::i}},//芪
{{pysm::y,pyym::an},{pysm::y,pyym::uan}},//芫
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//芭
{{pysm::r,pyym::ui},{pysm::r,pyym::uo}},//芮
{{pysm::w,pyym::u},{pysm::h,pyym::u}},//芴
{{pysm::ch,pyym::u},{pysm::z,pyym::ou}},//芻
{{pysm::f,pyym::ei},{pysm::f,pyym::u}},//芾
{{pysm::t,pyym::i},{pysm::d,pyym::i}},//苐
{{pysm::l,pyym::ing},{pysm::l,pyym::ian}},//苓
{{pysm::sh,pyym::ao},{pysm::t,pyym::iao}},//苕
{{pysm::l,pyym::i},{pysm::j,pyym::i}},//苙
{{pysm::k,pyym::e},{pysm::h,pyym::e}},//苛
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//苣
{{pysm::p,pyym::ie},{pysm::p,pyym::i}},//苤
{{pysm::r,pyym::uo},{pysm::r,pyym::e}},//若
{{pysm::n,pyym::ing},{pysm::zh,pyym::u}},//苧
{{pysm::b,pyym::o},{pysm::p,pyym::a}},//苩
{{pysm::y,pyym::ing},{pysm::y,pyym::ang}},//英
{{pysm::zh,pyym::a},{pysm::z,pyym::uo}},//苲
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//苹
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//苻
{{pysm::sh,pyym::eng},{pysm::r,pyym::ui}},//苼
{{pysm::g,pyym::u},{pysm::g,pyym::ua}},//苽
{{pysm::zh,pyym::uo},{pysm::zh,pyym::u}},//茁
{{pysm::j,pyym::ia},{pysm::q,pyym::ie}},//茄
{{pysm::zh,pyym::i},{pysm::d,pyym::i}},//茋
{{pysm::g,pyym::e},{pysm::l,pyym::uo}},//茖
{{pysm::g,pyym::en},{pysm::j,pyym::ian}},//茛
{{pysm::q,pyym::ian},{pysm::x,pyym::i}},//茜
{{pysm::ch,pyym::ai},{pysm::zh,pyym::i}},//茝
{{pysm::y,pyym::u},{pysm::w,pyym::ei}},//茟
{{pysm::j,pyym::i},{pysm::d,pyym::uo}},//茤
{{pysm::j,pyym::ian},{pysm::ch,pyym::ong}},//茧
{{pysm::m,pyym::ang},{pysm::h,pyym::uang}},//茫
{{pysm::ch,pyym::a},{pysm::ch,pyym::i}},//茬
{{pysm::j,pyym::iao},{pysm::n,pyym::iao}},//茮
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//茲
{{pysm::m,pyym::ang},{pysm::m,pyym::u}},//茻
{{pysm::q,pyym::uan},{pysm::ch,pyym::uo}},//荃
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//荅
{{pysm::c,pyym::ao},{pysm::z,pyym::ao}},//草
{{pysm::t,pyym::i},{pysm::y,pyym::i}},//荑
{{pysm::h,pyym::uang},{pysm::k,pyym::ang}},//荒
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//荓
{{pysm::l,pyym::ao},{pysm::ch,pyym::a}},//荖
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//荠
{{pysm::h,pyym::un},{pysm::x,pyym::un}},//荤
{{pysm::x,pyym::ing},{pysm::y,pyym::ing}},//荥
{{pysm::x,pyym::un},{pysm::q,pyym::ian}},//荨
{{pysm::b,pyym::u},{pysm::p,pyym::u}},//荹
{{pysm::s,pyym::ui},{pysm::w,pyym::ei}},//荽
{{pysm::ch,pyym::en},{pysm::n,pyym::ong}},//莀
{{pysm::p,pyym::u},{pysm::f,pyym::u}},//莆
{{pysm::l,pyym::i},{pysm::ch,pyym::i}},//莉
{{pysm::z,pyym::uo},{pysm::j,pyym::i}},//莋
{{pysm::p,pyym::eng},{pysm::f,pyym::eng}},//莑
{{pysm::j,pyym::ing},{pysm::y,pyym::ing}},//莖
{{pysm::sh,pyym::en},{pysm::x,pyym::in}},//莘
{{pysm::g,pyym::uan},{pysm::w,pyym::an}},//莞
{{pysm::y,pyym::ou},{pysm::x,pyym::iu}},//莠
{{pysm::s,pyym::u},{pysm::y,pyym::ou}},//莤
{{pysm::n,pyym::iu},{pysm::r,pyym::ou}},//莥
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao}},//莦
{{pysm::x,pyym::ian},{pysm::w,pyym::an}},//莧
{{pysm::l,pyym::ang},{pysm::l,pyym::iang}},//莨
{{pysm::f,pyym::u},{pysm::p,pyym::iao}},//莩
{{pysm::m,pyym::o},{pysm::m,pyym::u}},//莫
{{pysm::j,pyym::ian},{pysm::g,pyym::uan}},//菅
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//菉
{{pysm::n,pyym::ie},{pysm::r,pyym::en}},//菍
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//菏
{{pysm::z,pyym::ai},{pysm::z,pyym::i}},//菑
{{pysm::x,pyym::i},{pysm::s,pyym::i}},//菥
{{pysm::j,pyym::ie},{pysm::sh,pyym::a}},//菨
{{pysm::q,pyym::iao},{pysm::zh,pyym::ao}},//菬
{{pysm::h,pyym::ua},{pysm::k,pyym::ua}},//華
{{pysm::q,pyym::in},{pysm::j,pyym::in}},//菳
{{pysm::nop,pyym::an},{pysm::y,pyym::an}},//菴
{{pysm::y,pyym::an},{pysm::y,pyym::u}},//菸
{{pysm::j,pyym::u},{pysm::z,pyym::u}},//菹
{{pysm::sh,pyym::u},{pysm::j,pyym::iao}},//菽
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//萁
{{pysm::f,pyym::ei},{pysm::f,pyym::u}},//萉
{{pysm::m,pyym::eng},{pysm::m,pyym::ing}},//萌
{{pysm::h,pyym::uan},{pysm::zh,pyym::ui}},//萑
{{pysm::y,pyym::an},{pysm::j,pyym::uan}},//萒
{{pysm::q,pyym::iu},{pysm::j,pyym::iao}},//萩
{{pysm::y,pyym::u},{pysm::j,pyym::u}},//萭
{{pysm::f,pyym::u},{pysm::b,pyym::ei}},//萯
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//萹
{{pysm::m,pyym::ao},{pysm::m,pyym::u}},//萺
{{pysm::k,pyym::uo},{pysm::h,pyym::uo}},//萿
{{pysm::z,pyym::uo},{pysm::z,pyym::e}},//葃
{{pysm::y,pyym::e},{pysm::sh,pyym::e}},//葉
{{pysm::p,pyym::en},{pysm::f,pyym::en}},//葐
{{pysm::r,pyym::en},{pysm::sh,pyym::en}},//葚
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//葝
{{pysm::sh,pyym::en},{pysm::sh,pyym::an}},//葠
{{pysm::p,pyym::u},{pysm::b,pyym::ei}},//葡
{{pysm::d,pyym::ong},{pysm::zh,pyym::ong}},//董
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//葥
{{pysm::j,pyym::ia},{pysm::x,pyym::ia}},//葭
{{pysm::c,pyym::ong},{pysm::ch,pyym::uang}},//葱
{{pysm::zh,pyym::en},{pysm::q,pyym::ian}},//葴
{{pysm::t,pyym::ing},{pysm::d,pyym::ing}},//葶
{{pysm::h,pyym::un},{pysm::x,pyym::un}},//葷
{{pysm::s,pyym::ou},{pysm::h,pyym::ui}},//蒐
{{pysm::r,pyym::u},{pysm::n,pyym::a}},//蒘
{{pysm::y,pyym::uan},{pysm::h,pyym::uan}},//蒝
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//蒡
{{pysm::x,pyym::u},{pysm::sh,pyym::u}},//蒣
{{pysm::h,pyym::uo},{pysm::w,pyym::o}},//蒦
{{pysm::p,pyym::u},{pysm::b,pyym::o}},//蒲
{{pysm::h,pyym::ao},{pysm::g,pyym::ao}},//蒿
{{pysm::zh,pyym::en},{pysm::q,pyym::in}},//蓁
{{pysm::m,pyym::ing},{pysm::m,pyym::i}},//蓂
{{pysm::g,pyym::ai},{pysm::g,pyym::e}},//蓋
{{pysm::s,pyym::uo},{pysm::s,pyym::ui}},//蓑
{{pysm::y,pyym::ao},{pysm::zh,pyym::uo}},//蓔
{{pysm::l,pyym::an},{pysm::l,pyym::a}},//蓝
{{pysm::t,pyym::iao},{pysm::x,pyym::iu}},//蓨
{{pysm::ch,pyym::u},{pysm::zh,pyym::u}},//蓫
{{pysm::ch,pyym::un},{pysm::t,pyym::uan}},//蓴
{{pysm::z,pyym::i},{pysm::j,pyym::u}},//蓻
{{pysm::x,pyym::u},{pysm::s,pyym::u}},//蓿
{{pysm::q,pyym::iang},{pysm::j,pyym::iang}},//蔃
{{pysm::j,pyym::i},{pysm::x,pyym::i}},//蔇
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//蔈
{{pysm::l,pyym::u},{pysm::c,pyym::u}},//蔍
{{pysm::m,pyym::an},{pysm::w,pyym::an}},//蔓
{{pysm::sh,pyym::en},{pysm::s,pyym::an}},//蔘
{{pysm::w,pyym::ei},{pysm::y,pyym::u}},//蔚
{{pysm::p,pyym::o},{pysm::b,pyym::o}},//蔢
{{pysm::j,pyym::uan},{pysm::j,pyym::un}},//蔨
{{pysm::j,pyym::ian},{pysm::sh,pyym::an}},//蔪
{{pysm::n,pyym::ian},{pysm::y,pyym::an}},//蔫
{{pysm::z,pyym::ang},{pysm::c,pyym::ang}},//蔵
{{pysm::x,pyym::un},{pysm::t,pyym::an}},//蕈
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//蕉
{{pysm::r,pyym::ui},{pysm::j,pyym::uan}},//蕊
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//蕎
{{pysm::r,pyym::ao},{pysm::y,pyym::ao}},//蕘
{{pysm::j,pyym::ue},{pysm::z,pyym::ui}},//蕝
{{pysm::f,pyym::a},{pysm::f,pyym::ei}},//蕟
{{pysm::f,pyym::en},{pysm::f,pyym::ei}},//蕡
{{pysm::k,pyym::ui},{pysm::k,pyym::uai}},//蕢
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//蕩
{{pysm::w,pyym::en},{pysm::y,pyym::un}},//蕰
{{pysm::w,pyym::eng},{pysm::y,pyym::ong}},//蕹
{{pysm::j,pyym::i},{pysm::q,pyym::ie}},//蕺
{{pysm::y,pyym::u},{pysm::nop,pyym::ao}},//薁
{{pysm::x,pyym::i},{pysm::x,pyym::iao}},//薂
{{pysm::c,pyym::i},{pysm::z,pyym::i}},//薋
{{pysm::w,pyym::an},{pysm::l,pyym::uan}},//薍
{{pysm::q,pyym::iang},{pysm::s,pyym::e}},//薔
{{pysm::t,pyym::i},{pysm::zh,pyym::i}},//薙
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//薥
{{pysm::h,pyym::ao},{pysm::k,pyym::ao}},//薧
{{pysm::w,pyym::ei},{pysm::y,pyym::uan}},//薳
{{pysm::m,pyym::ai},{pysm::w,pyym::o}},//薶
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//藇
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//藉
{{pysm::l,pyym::an},{pysm::l,pyym::a}},//藍
{{pysm::c,pyym::ang},{pysm::z,pyym::ang}},//藏
{{pysm::m,pyym::iao},{pysm::m,pyym::o}},//藐
{{pysm::x,pyym::ian},{pysm::q,pyym::ian}},//藖
{{pysm::b,pyym::iao},{pysm::p,pyym::ao}},//藨
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//藴
{{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//藷
{{pysm::h,pyym::uo},{pysm::h,pyym::e}},//藿
{{pysm::t,pyym::uo},{pysm::z,pyym::e}},//蘀
{{pysm::w,pyym::u},{pysm::nop,pyym::e}},//蘁
{{pysm::m,pyym::eng},{pysm::m,pyym::ang}},//蘉
{{pysm::p,pyym::ing},{pysm::p,pyym::in}},//蘋
{{pysm::n,pyym::ie},{pysm::b,pyym::o}},//蘖
{{pysm::b,pyym::o},{pysm::b,pyym::i}},//蘗
{{pysm::l,pyym::ian},{pysm::x,pyym::ian}},//蘞
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//蘧
{{pysm::h,pyym::an},{pysm::l,pyym::an}},//蘫
{{pysm::f,pyym::eng},{pysm::s,pyym::ong}},//蘴
{{pysm::l,pyym::v},{pysm::b,pyym::i}},//虑
{{pysm::ch,pyym::u},{pysm::j,pyym::u}},//處
{{pysm::j,pyym::iao},{pysm::h,pyym::ao}},//虠
{{pysm::x,pyym::i},{pysm::s,pyym::e}},//虩
{{pysm::ch,pyym::ong},{pysm::h,pyym::ui}},//虫
{{pysm::d,pyym::iao},{pysm::d,pyym::ao}},//虭
{{pysm::d,pyym::ing},{pysm::ch,pyym::eng}},//虰
{{pysm::sh,pyym::e},{pysm::y,pyym::e}},//虵
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//虷
{{pysm::x,pyym::ia},{pysm::h,pyym::a}},//虾
{{pysm::f,pyym::ang},{pysm::b,pyym::ang}},//蚄
{{pysm::q,pyym::i},{pysm::zh,pyym::i}},//蚔
{{pysm::c,pyym::an},{pysm::t,pyym::ian}},//蚕
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//蚖
{{pysm::j,pyym::ue},{pysm::q,pyym::ue}},//蚗
{{pysm::h,pyym::ui},{pysm::y,pyym::ou}},//蚘
{{pysm::q,pyym::in},{pysm::q,pyym::ian}},//蚙
{{pysm::h,pyym::ao},{pysm::c,pyym::i}},//蚝
{{pysm::g,pyym::ong},{pysm::zh,pyym::ong}},//蚣
{{pysm::z,pyym::ao},{pysm::zh,pyym::ao}},//蚤
{{pysm::b,pyym::ao},{pysm::p,pyym::ao}},//蚫
{{pysm::y,pyym::ou},{pysm::zh,pyym::u}},//蚰
{{pysm::ch,pyym::i},{pysm::d,pyym::i}},//蚳
{{pysm::y,pyym::ou},{pysm::n,pyym::iu}},//蚴
{{pysm::h,pyym::e},{pysm::k,pyym::e}},//蚵
{{pysm::r,pyym::an},{pysm::t,pyym::ian}},//蚺
{{pysm::p,pyym::i},{pysm::b,pyym::o}},//蚾
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//蛆
{{pysm::m,pyym::ou},{pysm::m,pyym::ao}},//蛑
{{pysm::g,pyym::e},{pysm::l,pyym::uo}},//蛒
{{pysm::m,pyym::ang},{pysm::b,pyym::ang}},//蛖
{{pysm::w,pyym::a},{pysm::j,pyym::ue}},//蛙
{{pysm::k,pyym::uo},{pysm::sh,pyym::e}},//蛞
{{pysm::y,pyym::i},{pysm::x,pyym::u}},//蛡
{{pysm::q,pyym::iong},{pysm::g,pyym::ong}},//蛩
{{pysm::q,pyym::ie},{pysm::n,pyym::i}},//蛪
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao}},//蛸
{{pysm::nop,pyym::e},{pysm::y,pyym::i}},//蛾
{{pysm::sh,pyym::en},{pysm::zh,pyym::en}},//蜄
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//蜅
{{pysm::l,pyym::ang},{pysm::l,pyym::iang}},//蜋
{{pysm::ch,pyym::u},{pysm::y,pyym::u}},//蜍
{{pysm::y,pyym::uan},{pysm::x,pyym::uan}},//蜎
{{pysm::y,pyym::an},{pysm::d,pyym::an}},//蜒
{{pysm::t,pyym::ing},{pysm::d,pyym::ian}},//蜓
{{pysm::t,pyym::ui},{pysm::y,pyym::ue}},//蜕
{{pysm::s,pyym::i},{pysm::x,pyym::i}},//蜤
{{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//蜩
{{pysm::y,pyym::u},{pysm::g,pyym::uo}},//蜮
{{pysm::p,pyym::i},{pysm::m,pyym::iao}},//蜱
{{pysm::d,pyym::un},{pysm::t,pyym::un}},//蜳
{{pysm::y,pyym::i},{pysm::x,pyym::i}},//蜴
{{pysm::y,pyym::uan},{pysm::y,pyym::un}},//蜵
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//蜷
{{pysm::r,pyym::ui},{pysm::w,pyym::ei}},//蜹
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//蜻
{{pysm::w,pyym::ei},{pysm::t,pyym::ong}},//蜼
{{pysm::g,pyym::uo},{pysm::l,pyym::uo}},//蜾
{{pysm::d,pyym::i},{pysm::zh,pyym::uo}},//蝃
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//蝍
{{pysm::x,pyym::ie},{pysm::h,pyym::e}},//蝎
{{pysm::x,pyym::u},{pysm::x,pyym::ie}},//蝑
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//蝙
{{pysm::r,pyym::ou},{pysm::n,pyym::ao}},//蝚
{{pysm::r,pyym::u},{pysm::r,pyym::uan}},//蝡
{{pysm::m,pyym::ao},{pysm::w,pyym::u}},//蝥
{{pysm::ch,pyym::ong},{pysm::zh,pyym::ong}},//蝩
{{pysm::t,pyym::i},{pysm::ch,pyym::i}},//蝭
{{pysm::d,pyym::u},{pysm::d,pyym::ai}},//蝳
{{pysm::d,pyym::ie},{pysm::t,pyym::ie}},//蝶
{{pysm::l,pyym::i},{pysm::x,pyym::i}},//蝷
{{pysm::y,pyym::un},{pysm::nop,pyym::ao}},//蝹
{{pysm::q,pyym::u},{pysm::y,pyym::u}},//蝺
{{pysm::p,pyym::ang},{pysm::b,pyym::ang}},//螃
{{pysm::x,pyym::i},{pysm::c,pyym::i}},//螅
{{pysm::x,pyym::i},{pysm::q,pyym::i}},//螇
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//螔
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//螕
{{pysm::n,pyym::ai},{pysm::n,pyym::eng}},//螚
{{pysm::h,pyym::e},{pysm::x,pyym::ia}},//螛
{{pysm::g,pyym::ui},{pysm::h,pyym::ui}},//螝
{{pysm::t,pyym::e},{pysm::t,pyym::eng}},//螣
{{pysm::sh,pyym::i},{pysm::zh,pyym::e}},//螫
{{pysm::d,pyym::i},{pysm::d,pyym::ai}},//螮
{{pysm::zh,pyym::i},{pysm::d,pyym::ie}},//螲
{{pysm::q,pyym::u},{pysm::j,pyym::u}},//螶
{{pysm::j,pyym::ian},{pysm::ch,pyym::an}},//螹
{{pysm::m,pyym::a},{pysm::m,pyym::o}},//蟆
{{pysm::g,pyym::uo},{pysm::y,pyym::u}},//蟈
{{pysm::l,pyym::iu},{pysm::l,pyym::iao}},//蟉
{{pysm::m,pyym::ao},{pysm::m,pyym::eng}},//蟊
{{pysm::m,pyym::ang},{pysm::m,pyym::eng}},//蟒
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//蟜
{{pysm::p,pyym::an},{pysm::f,pyym::an}},//蟠
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//蟣
{{pysm::f,pyym::ei},{pysm::b,pyym::en}},//蟦
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//蟧
{{pysm::y,pyym::in},{pysm::x,pyym::un}},//蟫
{{pysm::n,pyym::ao},{pysm::r,pyym::ao}},//蟯
{{pysm::w,pyym::u},{pysm::m,pyym::ou}},//蟱
{{pysm::y,pyym::i},{pysm::j,pyym::i}},//蟻
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//蟿
{{pysm::c,pyym::i},{pysm::j,pyym::i}},//蠀
{{pysm::l,pyym::uo},{pysm::g,pyym::uo}},//蠃
{{pysm::h,pyym::uo},{pysm::y,pyym::ue}},//蠖
{{pysm::m,pyym::in},{pysm::m,pyym::ian}},//蠠
{{pysm::l,pyym::i},{pysm::l,pyym::uo}},//蠡
{{pysm::zh,pyym::u},{pysm::ch,pyym::u}},//蠩
{{pysm::f,pyym::eng},{pysm::p,pyym::ang}},//蠭
{{pysm::g,pyym::u},{pysm::y,pyym::e}},//蠱
{{pysm::q,pyym::uan},{pysm::h,pyym::uan}},//蠸
{{pysm::q,pyym::u},{pysm::j,pyym::ue}},//蠼
{{pysm::zh,pyym::u},{pysm::sh,pyym::u}},//蠾
{{pysm::x,pyym::ue},{pysm::x,pyym::ie}},//血
{{pysm::p,pyym::ei},{pysm::f,pyym::ou}},//衃
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//衕
{{pysm::x,pyym::iang},{pysm::l,pyym::ong}},//衖
{{pysm::x,pyym::ian},{pysm::y,pyym::u}},//衘
{{pysm::y,pyym::a},{pysm::y,pyym::u}},//衙
{{pysm::f,pyym::en},{pysm::p,pyym::en}},//衯
{{pysm::j,pyym::in},{pysm::q,pyym::in}},//衿
{{pysm::m,pyym::ei},{pysm::y,pyym::i}},//袂
{{pysm::b,pyym::ao},{pysm::p,pyym::ao}},//袌
{{pysm::p,pyym::ao},{pysm::b,pyym::ao}},//袍
{{pysm::t,pyym::an},{pysm::zh,pyym::an}},//袒
{{pysm::j,pyym::u},{pysm::j,pyym::ie}},//袓
{{pysm::y,pyym::i},{pysm::t,pyym::uo}},//袘
{{pysm::b,pyym::o},{pysm::f,pyym::u}},//袚
{{pysm::w,pyym::a},{pysm::m,pyym::o}},//袜
{{pysm::p,pyym::an},{pysm::f,pyym::an}},//袢
{{pysm::m,pyym::ao},{pysm::m,pyym::ou}},//袤
{{pysm::n,pyym::a},{pysm::j,pyym::ue}},//袦
{{pysm::zh,pyym::e},{pysm::ch,pyym::an}},//袩
{{pysm::ch,pyym::i},{pysm::n,pyym::uo}},//袲
{{pysm::j,pyym::ian},{pysm::z,pyym::un}},//袸
{{pysm::b,pyym::o},{pysm::m,pyym::o}},//袹
{{pysm::g,pyym::e},{pysm::l,pyym::uo}},//袼
{{pysm::g,pyym::ui},{pysm::g,pyym::ua}},//袿
{{pysm::j,pyym::ia},{pysm::x,pyym::ie}},//裌
{{pysm::p,pyym::ou},{pysm::b,pyym::ao}},//裒
{{pysm::g,pyym::e},{pysm::j,pyym::ie}},//裓
{{pysm::l,pyym::ian},{pysm::sh,pyym::ao}},//裢
{{pysm::ch,pyym::an},{pysm::t,pyym::an}},//裧
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//裨
{{pysm::ch,pyym::ou},{pysm::d,pyym::ao}},//裯
{{pysm::sh,pyym::ang},{pysm::ch,pyym::ang}},//裳
{{pysm::p,pyym::ei},{pysm::f,pyym::ei}},//裴
{{pysm::y,pyym::uan},{pysm::g,pyym::un}},//裷
{{pysm::y,pyym::an},{pysm::nop,pyym::an}},//裺
{{pysm::t,pyym::i},{pysm::x,pyym::i}},//裼
{{pysm::y,pyym::i},{pysm::q,pyym::i}},//裿
{{pysm::t,pyym::i},{pysm::sh,pyym::i}},//褆
{{pysm::ch,pyym::ong},{pysm::zh,pyym::ong}},//褈
{{pysm::b,pyym::ian},{pysm::p,pyym::ian}},//褊
{{pysm::d,pyym::uan},{pysm::t,pyym::uan}},//褍
{{pysm::x,pyym::iu},{pysm::y,pyym::ou}},//褎
{{pysm::y,pyym::u},{pysm::t,pyym::ou}},//褕
{{pysm::h,pyym::ui},{pysm::y,pyym::i}},//褘
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//褞
{{pysm::r,pyym::u},{pysm::n,pyym::u}},//褥
{{pysm::s,pyym::uo},{pysm::ch,pyym::a}},//褨
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//褩
{{pysm::t,pyym::ui},{pysm::t,pyym::un}},//褪
{{pysm::y,pyym::i},{pysm::n,pyym::ie}},//褹
{{pysm::s,pyym::en},{pysm::sh,pyym::an}},//襂
{{pysm::b,pyym::ao},{pysm::p,pyym::ou}},//襃
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//襆
{{pysm::zh,pyym::uan},{pysm::j,pyym::uan}},//襈
{{pysm::c,pyym::ui},{pysm::c,pyym::uo}},//襊
{{pysm::f,pyym::an},{pysm::b,pyym::o}},//襎
{{pysm::b,pyym::o},{pysm::f,pyym::ei}},//襏
{{pysm::g,pyym::ui},{pysm::h,pyym::ui}},//襘
{{pysm::ch,pyym::an},{pysm::d,pyym::an}},//襜
{{pysm::l,pyym::ian},{pysm::ch,pyym::an}},//襝
{{pysm::sh,pyym::u},{pysm::d,pyym::u}},//襡
{{pysm::b,pyym::ai},{pysm::b,pyym::ei}},//襬
{{pysm::x,pyym::ian},{pysm::sh,pyym::an}},//襳
{{pysm::z,pyym::an},{pysm::c,pyym::uan}},//襸
{{pysm::f,pyym::eng},{pysm::b,pyym::an}},//覂
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//見
{{pysm::g,pyym::ui},{pysm::x,pyym::u}},//規
{{pysm::m,pyym::ie},{pysm::p,pyym::ie}},//覕
{{pysm::q,pyym::in},{pysm::q,pyym::ing}},//親
{{pysm::j,pyym::ian},{pysm::b,pyym::ian}},//覵
{{pysm::l,pyym::uo},{pysm::l,pyym::uan}},//覶
{{pysm::j,pyym::ue},{pysm::j,pyym::iao}},//覺
{{pysm::d,pyym::i},{pysm::j,pyym::i}},//覿
{{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//见
{{pysm::j,pyym::ue},{pysm::j,pyym::iao}},//觉
{{pysm::z,pyym::i},{pysm::z,pyym::ui}},//觜
{{pysm::d,pyym::i},{pysm::zh,pyym::i}},//觝
{{pysm::h,pyym::ua},{pysm::x,pyym::ie}},//觟
{{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//解
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//觭
{{pysm::zh,pyym::a},{pysm::d,pyym::a}},//觰
{{pysm::x,pyym::ue},{pysm::h,pyym::u}},//觷
{{pysm::l,pyym::i},{pysm::l,pyym::u}},//觻
{{pysm::x,pyym::i},{pysm::w,pyym::ei}},//觿
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//言
{{pysm::q,pyym::iu},{pysm::k,pyym::ao}},//訄
{{pysm::ch,pyym::ai},{pysm::ch,pyym::a}},//訍
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//訐
{{pysm::f,pyym::en},{pysm::b,pyym::in}},//訜
{{pysm::x,pyym::iao},{pysm::n,pyym::a}},//訤
{{pysm::ch,pyym::ao},{pysm::m,pyym::iao}},//訬
{{pysm::x,pyym::u},{pysm::h,pyym::u}},//許
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//詆
{{pysm::q,pyym::u},{pysm::ch,pyym::u}},//詘
{{pysm::b,pyym::a},{pysm::b,pyym::o}},//詙
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//詥
{{pysm::ch,pyym::a},{pysm::q,pyym::ie}},//詧
{{pysm::ch,pyym::a},{pysm::d,pyym::u}},//詫
{{pysm::g,pyym::ou},{pysm::h,pyym::ou}},//詬
{{pysm::x,pyym::iang},{pysm::y,pyym::ang}},//詳
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ou}},//詶
{{pysm::t,pyym::ong},{pysm::d,pyym::ong}},//詷
{{pysm::zh,pyym::an},{pysm::d,pyym::an}},//詹
{{pysm::nop,pyym::er},{pysm::ch,pyym::i}},//誀
{{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//誂
{{pysm::k,pyym::ua},{pysm::q,pyym::u}},//誇
{{pysm::sh,pyym::ui},{pysm::sh,pyym::ei}},//誰
{{pysm::q,pyym::u},{pysm::j,pyym::ue}},//誳
{{pysm::ch,pyym::i},{pysm::l,pyym::ai}},//誺
{{pysm::n,pyym::i},{pysm::n,pyym::a}},//誽
{{pysm::p,pyym::i},{pysm::b,pyym::ei}},//諀
{{pysm::z,pyym::ou},{pysm::zh,pyym::ou}},//諏
{{pysm::ch,pyym::u},{pysm::j,pyym::i}},//諔
{{pysm::sh,pyym::en},{pysm::n,pyym::ie}},//諗
{{pysm::d,pyym::ie},{pysm::x,pyym::ie}},//諜
{{pysm::sh,pyym::i},{pysm::d,pyym::i}},//諟
{{pysm::h,pyym::ua},{pysm::g,pyym::ua}},//諣
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//諦
{{pysm::j,pyym::ian},{pysm::l,pyym::an}},//諫
{{pysm::y,pyym::u},{pysm::t,pyym::ou}},//諭
{{pysm::nop,pyym::an},{pysm::t,pyym::ou}},//諳
{{pysm::x,pyym::ian},{pysm::g,pyym::an}},//諴
{{pysm::zh,pyym::u},{pysm::ch,pyym::u}},//諸
{{pysm::q,pyym::i},{pysm::x,pyym::u}},//諿
{{pysm::y,pyym::e},{pysm::nop,pyym::ai}},//謁
{{pysm::p,pyym::o},{pysm::p,pyym::ao}},//謈
{{pysm::y,pyym::ing},{pysm::h,pyym::ong}},//謍
{{pysm::x,pyym::iao},{pysm::s,pyym::ou}},//謏
{{pysm::x,pyym::i},{pysm::x,pyym::ia}},//謑
{{pysm::ch,pyym::en},{pysm::zh,pyym::en}},//謓
{{pysm::t,pyym::i},{pysm::s,pyym::i}},//謕
{{pysm::q,pyym::ian},{pysm::zh,pyym::an}},//謙
{{pysm::y,pyym::uan},{pysm::q,pyym::uan}},//謜
{{pysm::h,pyym::e},{pysm::x,pyym::iao}},//謞
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//謣
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//謤
{{pysm::zh,pyym::e},{pysm::z,pyym::e}},//謫
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//謱
{{pysm::nop,pyym::ou},{pysm::x,pyym::u}},//謳
{{pysm::x,pyym::i},{pysm::ch,pyym::e}},//謵
{{pysm::y,pyym::i},{pysm::ch,pyym::i}},//謻
{{pysm::h,pyym::u},{pysm::x,pyym::iao}},//謼
{{pysm::h,pyym::an},{pysm::x,pyym::ian}},//譀
{{pysm::h,pyym::ua},{pysm::w,pyym::a}},//譁
{{pysm::ch,pyym::an},{pysm::d,pyym::an}},//譂
{{pysm::n,pyym::ao},{pysm::x,pyym::iao}},//譊
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//譑
{{pysm::zh,pyym::uan},{pysm::q,pyym::uan}},//譔
{{pysm::w,pyym::u},{pysm::m,pyym::o}},//譕
{{pysm::z,pyym::en},{pysm::j,pyym::ian}},//譖
{{pysm::sh,pyym::i},{pysm::zh,pyym::i}},//識
{{pysm::zh,pyym::an},{pysm::l,pyym::ian}},//譧
{{pysm::n,pyym::ang},{pysm::n,pyym::ou}},//譨
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ou}},//譸
{{pysm::d,pyym::u},{pysm::d,pyym::ou}},//讀
{{pysm::y,pyym::i},{pysm::t,pyym::ui}},//讉
{{pysm::ch,pyym::en},{pysm::ch,pyym::an}},//讖
{{pysm::x,pyym::u},{pysm::h,pyym::u}},//许
{{pysm::sh,pyym::i},{pysm::zh,pyym::i}},//识
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//诘
{{pysm::d,pyym::u},{pysm::d,pyym::ou}},//读
{{pysm::sh,pyym::ui},{pysm::sh,pyym::ei}},//谁
{{pysm::d,pyym::iao},{pysm::t,pyym::iao}},//调
{{pysm::m,pyym::i},{pysm::m,pyym::ei}},//谜
{{pysm::h,pyym::ong},{pysm::l,pyym::ong}},//谾
{{pysm::x,pyym::i},{pysm::j,pyym::i}},//谿
{{pysm::h,pyym::uo},{pysm::h,pyym::ua}},//豁
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//豃
{{pysm::q,pyym::i},{pysm::k,pyym::ai}},//豈
{{pysm::sh,pyym::i},{pysm::ch,pyym::i}},//豉
{{pysm::l,pyym::i},{pysm::f,pyym::eng}},//豊
{{pysm::b,pyym::i},{pysm::b,pyym::ian}},//豍
{{pysm::t,pyym::un},{pysm::d,pyym::un}},//豚
{{pysm::j,pyym::ian},{pysm::y,pyym::an}},//豣
{{pysm::k,pyym::en},{pysm::k,pyym::un}},//豤
{{pysm::f,pyym::u},{pysm::p,pyym::u}},//豧
{{pysm::b,pyym::in},{pysm::h,pyym::uan}},//豩
{{pysm::b,pyym::in},{pysm::b,pyym::an}},//豳
{{pysm::zh,pyym::i},{pysm::zh,pyym::ai}},//豸
{{pysm::n,pyym::a},{pysm::d,pyym::uo}},//貀
{{pysm::h,pyym::e},{pysm::m,pyym::o}},//貈
{{pysm::m,pyym::o},{pysm::m,pyym::a}},//貊
{{pysm::m,pyym::ao},{pysm::m,pyym::o}},//貌
{{pysm::j,pyym::u},{pysm::y,pyym::u}},//貗
{{pysm::zh,pyym::en},{pysm::zh,pyym::eng}},//貞
{{pysm::g,pyym::uan},{pysm::w,pyym::an}},//貫
{{pysm::z,pyym::e},{pysm::zh,pyym::ai}},//責
{{pysm::b,pyym::ian},{pysm::f,pyym::a}},//貶
{{pysm::d,pyym::ai},{pysm::t,pyym::e}},//貸
{{pysm::j,pyym::ia},{pysm::g,pyym::u}},//賈
{{pysm::sh,pyym::e},{pysm::sh,pyym::a}},//賒
{{pysm::y,pyym::i},{pysm::nop,pyym::ai}},//賹
{{pysm::zh,pyym::uan},{pysm::z,pyym::uan}},//賺
{{pysm::y,pyym::un},{pysm::b,pyym::in}},//贇
{{pysm::sh,pyym::an},{pysm::d,pyym::an}},//贍
{{pysm::b,pyym::en},{pysm::b,pyym::i}},//贲
{{pysm::j,pyym::ia},{pysm::g,pyym::u}},//贾
{{pysm::zh,pyym::uan},{pysm::z,pyym::uan}},//赚
{{pysm::sh,pyym::e},{pysm::c,pyym::e}},//赦
{{pysm::t,pyym::ong},{pysm::x,pyym::iong}},//赨
{{pysm::h,pyym::e},{pysm::sh,pyym::i}},//赫
{{pysm::g,pyym::an},{pysm::q,pyym::ian}},//赶
{{pysm::y,pyym::in},{pysm::q,pyym::in}},//赺
{{pysm::j,pyym::ue},{pysm::g,pyym::ui}},//赽
{{pysm::ch,pyym::i},{pysm::d,pyym::i}},//赿
{{pysm::d,pyym::ie},{pysm::t,pyym::u}},//趃
{{pysm::j,pyym::u},{pysm::q,pyym::ie}},//趄
{{pysm::ch,pyym::ao},{pysm::t,pyym::iao}},//超
{{pysm::j,pyym::ue},{pysm::j,pyym::u}},//趉
{{pysm::y,pyym::ue},{pysm::h,pyym::uo}},//越
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//趌
{{pysm::ch,pyym::i},{pysm::q,pyym::u}},//趍
{{pysm::g,pyym::ua},{pysm::h,pyym::uo}},//趏
{{pysm::x,pyym::ue},{pysm::ch,pyym::i}},//趐
{{pysm::z,pyym::i},{pysm::c,pyym::i}},//趑
{{pysm::zh,pyym::ao},{pysm::d,pyym::iao}},//趙
{{pysm::q,pyym::iu},{pysm::c,pyym::u}},//趥
{{pysm::h,pyym::uang},{pysm::g,pyym::uang}},//趪
{{pysm::z,pyym::an},{pysm::z,pyym::u}},//趲
{{pysm::z,pyym::u},{pysm::j,pyym::u}},//足
{{pysm::k,pyym::u},{pysm::w,pyym::u}},//趶
{{pysm::j,pyym::ue},{pysm::g,pyym::ui}},//趹
{{pysm::j,pyym::ian},{pysm::y,pyym::an}},//趼
{{pysm::f,pyym::ang},{pysm::p,pyym::ang}},//趽
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//跁
{{pysm::t,pyym::uo},{pysm::ch,pyym::i}},//跅
{{pysm::b,pyym::a},{pysm::b,pyym::ei}},//跋
{{pysm::d,pyym::ie},{pysm::t,pyym::u}},//跌
{{pysm::c,pyym::i},{pysm::z,pyym::i}},//跐
{{pysm::p,pyym::ao},{pysm::b,pyym::o}},//跑
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//跔
{{pysm::p,pyym::an},{pysm::b,pyym::an}},//跘
{{pysm::l,pyym::i},{pysm::l,pyym::uo}},//跞
{{pysm::x,pyym::ian},{pysm::s,pyym::un}},//跣
{{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//跤
{{pysm::zh,pyym::u},{pysm::ch,pyym::u}},//跦
{{pysm::q,pyym::uan},{pysm::z,pyym::un}},//跧
{{pysm::k,pyym::ua},{pysm::k,pyym::u}},//跨
{{pysm::zh,pyym::uai},{pysm::sh,pyym::i}},//跩
{{pysm::q,pyym::iong},{pysm::q,pyym::iang}},//跫
{{pysm::k,pyym::ui},{pysm::x,pyym::ie}},//跬
{{pysm::ch,pyym::i},{pysm::d,pyym::ie}},//跮
{{pysm::l,pyym::u},{pysm::l,pyym::uo}},//路
{{pysm::j,pyym::ia},{pysm::j,pyym::ie}},//跲
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//跼
{{pysm::sh,pyym::u},{pysm::ch,pyym::ou}},//跾
{{pysm::ch,pyym::u},{pysm::c,pyym::u}},//踀
{{pysm::j,pyym::ing},{pysm::k,pyym::eng}},//踁
{{pysm::x,pyym::iao},{pysm::q,pyym::iao}},//踃
{{pysm::x,pyym::ue},{pysm::ch,pyym::i}},//踅
{{pysm::l,pyym::iang},{pysm::l,pyym::ang}},//踉
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//踑
{{pysm::w,pyym::ei},{pysm::c,pyym::u}},//踓
{{pysm::l,pyym::eng},{pysm::ch,pyym::eng}},//踜
{{pysm::w,pyym::an},{pysm::w,pyym::o}},//踠
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//踡
{{pysm::t,pyym::i},{pysm::d,pyym::ie}},//踢
{{pysm::b,pyym::o},{pysm::p,pyym::ou}},//踣
{{pysm::c,pyym::u},{pysm::d,pyym::i}},//踧
{{pysm::c,pyym::ai},{pysm::k,pyym::ui}},//踩
{{pysm::p,pyym::eng},{pysm::p,pyym::an}},//踫
{{pysm::d,pyym::uo},{pysm::ch,pyym::uo}},//踱
{{pysm::ch,pyym::uan},{pysm::ch,pyym::un}},//踳
{{pysm::g,pyym::ua},{pysm::t,pyym::uo}},//踻
{{pysm::t,pyym::ang},{pysm::sh,pyym::ang}},//踼
{{pysm::f,pyym::u},{pysm::b,pyym::i}},//踾
{{pysm::t,pyym::i},{pysm::d,pyym::i}},//蹄
{{pysm::ch,pyym::a},{pysm::zh,pyym::a}},//蹅
{{pysm::q,pyym::i},{pysm::x,pyym::i}},//蹊
{{pysm::p,pyym::an},{pysm::m,pyym::an}},//蹒
{{pysm::z,pyym::an},{pysm::c,pyym::an}},//蹔
{{pysm::t,pyym::ang},{pysm::ch,pyym::eng}},//蹚
{{pysm::zh,pyym::i},{pysm::zh,pyym::uo}},//蹠
{{pysm::d,pyym::i},{pysm::zh,pyym::i}},//蹢
{{pysm::n,pyym::ian},{pysm::r,pyym::an}},//蹨
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//蹱
{{pysm::j,pyym::ue},{pysm::g,pyym::ui}},//蹶
{{pysm::zh,pyym::u},{pysm::zh,pyym::uo}},//躅
{{pysm::ch,pyym::u},{pysm::ch,pyym::uo}},//躇
{{pysm::y,pyym::ue},{pysm::t,pyym::i}},//躍
{{pysm::ch,pyym::an},{pysm::zh,pyym::an}},//躔
{{pysm::s,pyym::a},{pysm::x,pyym::ie}},//躠
{{pysm::c,pyym::uo},{pysm::z,pyym::uan}},//躦
{{pysm::j,pyym::ue},{pysm::q,pyym::i}},//躩
{{pysm::sh,pyym::en},{pysm::j,pyym::uan}},//身
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//軁
{{pysm::d,pyym::uo},{pysm::t,pyym::uo}},//軃
{{pysm::ch,pyym::e},{pysm::j,pyym::u}},//車
{{pysm::x,pyym::in},{pysm::x,pyym::ian}},//軐
{{pysm::ch,pyym::en},{pysm::q,pyym::i}},//軙
{{pysm::d,pyym::i},{pysm::ch,pyym::i}},//軧
{{pysm::f,pyym::an},{pysm::b,pyym::en}},//軬
{{pysm::r,pyym::ong},{pysm::f,pyym::u}},//軵
{{pysm::zh,pyym::ou},{pysm::zh,pyym::u}},//軸
{{pysm::y,pyym::ao},{pysm::d,pyym::iao}},//軺
{{pysm::zh,pyym::i},{pysm::q,pyym::ing}},//軽
{{pysm::q,pyym::uan},{pysm::ch,pyym::un}},//輇
{{pysm::w,pyym::an},{pysm::y,pyym::uan}},//輐
{{pysm::y,pyym::in},{pysm::q,pyym::un}},//輑
{{pysm::n,pyym::i},{pysm::y,pyym::i}},//輗
{{pysm::l,pyym::eng},{pysm::l,pyym::ing}},//輘
{{pysm::n,pyym::ian},{pysm::l,pyym::ian}},//輦
{{pysm::p,pyym::ing},{pysm::p,pyym::eng}},//輧
{{pysm::r,pyym::uan},{pysm::nop,pyym::er}},//輭
{{pysm::x,pyym::ian},{pysm::k,pyym::an}},//輱
{{pysm::ch,pyym::un},{pysm::sh,pyym::un}},//輴
{{pysm::f,pyym::u},{pysm::b,pyym::u}},//輹
{{pysm::w,pyym::en},{pysm::y,pyym::un}},//輼
{{pysm::zh,pyym::an},{pysm::n,pyym::ian}},//輾
{{pysm::t,pyym::ao},{pysm::k,pyym::an}},//轁
{{pysm::x,pyym::ia},{pysm::h,pyym::e}},//轄
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//轇
{{pysm::zh,pyym::uan},{pysm::zh,pyym::uai}},//轉
{{pysm::l,pyym::ao},{pysm::l,pyym::iao}},//轑
{{pysm::ch,pyym::e},{pysm::j,pyym::u}},//车
{{pysm::zh,pyym::uan},{pysm::zh,pyym::uai}},//转
{{pysm::n,pyym::ian},{pysm::zh,pyym::an}},//辗
{{pysm::x,pyym::ue},{pysm::y,pyym::i}},//辥
{{pysm::ch,pyym::an},{pysm::zh,pyym::en}},//辴
{{pysm::y,pyym::i},{pysm::t,pyym::uo}},//迆
{{pysm::h,pyym::ang},{pysm::x,pyym::iang}},//迒
{{pysm::zh,pyym::e},{pysm::zh,pyym::ei}},//这
{{pysm::n,pyym::i},{pysm::ch,pyym::i}},//迡
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//迣
{{pysm::y,pyym::i},{pysm::t,pyym::uo}},//迤
{{pysm::j,pyym::ia},{pysm::x,pyym::ie}},//迦
{{pysm::p,pyym::o},{pysm::p,pyym::ai}},//迫
{{pysm::zh,pyym::u},{pysm::w,pyym::ang}},//迬
{{pysm::z,pyym::e},{pysm::z,pyym::uo}},//迮
{{pysm::t,pyym::uo},{pysm::y,pyym::i}},//迱
{{pysm::sh,pyym::i},{pysm::k,pyym::uo}},//适
{{pysm::p,pyym::ang},{pysm::f,pyym::eng}},//逄
{{pysm::t,pyym::ou},{pysm::sh,pyym::u}},//透
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//逘
{{pysm::g,pyym::uang},{pysm::k,pyym::uang}},//逛
{{pysm::ch,pyym::eng},{pysm::y,pyym::ing}},//逞
{{pysm::z,pyym::ao},{pysm::c,pyym::ao}},//造
{{pysm::l,pyym::ian},{pysm::l,pyym::an}},//連
{{pysm::j,pyym::ue},{pysm::zh,pyym::u}},//逫
{{pysm::b,pyym::eng},{pysm::p,pyym::eng}},//逬
{{pysm::d,pyym::ai},{pysm::d,pyym::i}},//逮
{{pysm::l,pyym::u},{pysm::d,pyym::ai}},//逯
{{pysm::y,pyym::u},{pysm::d,pyym::ou}},//逾
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//逿
{{pysm::y,pyym::an},{pysm::nop,pyym::an}},//遃
{{pysm::g,pyym::uo},{pysm::h,pyym::uo}},//過
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//達
{{pysm::w,pyym::ei},{pysm::h,pyym::ui}},//違
{{pysm::y,pyym::i},{pysm::w,pyym::ei}},//遗
{{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//遲
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//遽
{{pysm::l,pyym::a},{pysm::l,pyym::ie}},//邋
{{pysm::l,pyym::i},{pysm::ch,pyym::i}},//邌
{{pysm::y,pyym::i},{pysm::nop,pyym::e}},//邑
{{pysm::d,pyym::eng},{pysm::sh,pyym::an}},//邓
{{pysm::r,pyym::u},{pysm::f,pyym::u}},//邚
{{pysm::k,pyym::ang},{pysm::h,pyym::ang}},//邟
{{pysm::x,pyym::ing},{pysm::g,pyym::eng}},//邢
{{pysm::b,pyym::i},{pysm::b,pyym::ian}},//邲
{{pysm::y,pyym::e},{pysm::q,pyym::iu}},//邺
{{pysm::g,pyym::ai},{pysm::h,pyym::ai}},//郂
{{pysm::h,pyym::e},{pysm::x,pyym::ia}},//郃
{{pysm::q,pyym::ie},{pysm::x,pyym::i}},//郄
{{pysm::zh,pyym::i},{pysm::j,pyym::i}},//郅
{{pysm::h,pyym::uan},{pysm::x,pyym::un}},//郇
{{pysm::x,pyym::i},{pysm::ch,pyym::i}},//郗
{{pysm::w,pyym::u},{pysm::y,pyym::u}},//郚
{{pysm::h,pyym::ao},{pysm::sh,pyym::i}},//郝
{{pysm::y,pyym::ing},{pysm::ch,pyym::eng}},//郢
{{pysm::b,pyym::u},{pysm::p,pyym::ou}},//部
{{pysm::x,pyym::iao},{pysm::nop,pyym::ao}},//郩
{{pysm::z,pyym::ou},{pysm::j,pyym::u}},//郰
{{pysm::l,pyym::ai},{pysm::l,pyym::ei}},//郲
{{pysm::ch,pyym::en},{pysm::l,pyym::an}},//郴
{{pysm::y,pyym::ou},{pysm::ch,pyym::ui}},//郵
{{pysm::d,pyym::ou},{pysm::d,pyym::u}},//都
{{pysm::z,pyym::ou},{pysm::j,pyym::u}},//鄒
{{pysm::m,pyym::ao},{pysm::m,pyym::o}},//鄚
{{pysm::f,pyym::u},{pysm::l,pyym::u}},//鄜
{{pysm::m,pyym::an},{pysm::w,pyym::an}},//鄤
{{pysm::z,pyym::eng},{pysm::c,pyym::eng}},//鄫
{{pysm::d,pyym::an},{pysm::d,pyym::uo}},//鄲
{{pysm::c,pyym::ao},{pysm::s,pyym::ao}},//鄵
{{pysm::z,pyym::ou},{pysm::j,pyym::u}},//鄹
{{pysm::k,pyym::uang},{pysm::k,pyym::uo}},//鄺
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//鄿
{{pysm::c,pyym::uo},{pysm::z,pyym::an}},//酂
{{pysm::h,pyym::uan},{pysm::q,pyym::uan}},//酄
{{pysm::z,pyym::an},{pysm::c,pyym::uo}},//酇
{{pysm::l,pyym::i},{pysm::zh,pyym::i}},//酈
{{pysm::g,pyym::an},{pysm::h,pyym::ang}},//酐
{{pysm::y,pyym::an},{pysm::y,pyym::in}},//酓
{{pysm::zh,pyym::en},{pysm::d,pyym::an}},//酖
{{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//酡
{{pysm::c,pyym::u},{pysm::z,pyym::uo}},//酢
{{pysm::p,pyym::o},{pysm::f,pyym::a}},//酦
{{pysm::z,pyym::ai},{pysm::z,pyym::ui}},//酨
{{pysm::z,pyym::ui},{pysm::f,pyym::u}},//酻
{{pysm::sh,pyym::ai},{pysm::sh,pyym::i}},//酾
{{pysm::w,pyym::ei},{pysm::zh,pyym::ui}},//醀
{{pysm::y,pyym::an},{pysm::nop,pyym::ang}},//醃
{{pysm::t,pyym::an},{pysm::d,pyym::an}},//醈
{{pysm::c,pyym::u},{pysm::z,pyym::uo}},//醋
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//醎
{{pysm::q,pyym::iu},{pysm::ch,pyym::ou}},//醔
{{pysm::q,pyym::uan},{pysm::ch,pyym::uo}},//醛
{{pysm::ch,pyym::en},{pysm::ch,pyym::an}},//醦
{{pysm::y,pyym::u},{pysm::nop,pyym::ou}},//醧
{{pysm::f,pyym::a},{pysm::p,pyym::o}},//醱
{{pysm::y,pyym::i},{pysm::sh,pyym::i}},//醳
{{pysm::y,pyym::i},{pysm::nop,pyym::ai}},//醷
{{pysm::sh,pyym::i},{pysm::y,pyym::i}},//釋
{{pysm::y,pyym::e},{pysm::sh,pyym::u}},//野
{{pysm::q,pyym::iu},{pysm::g,pyym::a}},//釓
{{pysm::d,pyym::ing},{pysm::l,pyym::ing}},//釘
{{pysm::sh,pyym::an},{pysm::x,pyym::ian}},//釤
{{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//釥
{{pysm::h,pyym::ua},{pysm::y,pyym::u}},//釪
{{pysm::h,pyym::ua},{pysm::w,pyym::u}},//釫
{{pysm::h,pyym::an},{pysm::g,pyym::an}},//釬
{{pysm::g,pyym::ang},{pysm::g,pyym::ong}},//釭
{{pysm::ch,pyym::ai},{pysm::ch,pyym::a}},//釵
{{pysm::p,pyym::i},{pysm::zh,pyym::ao}},//釽
{{pysm::y,pyym::e},{pysm::y,pyym::a}},//釾
{{pysm::j,pyym::in},{pysm::y,pyym::in}},//釿
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//鈀
{{pysm::q,pyym::ian},{pysm::zh,pyym::ong}},//鈆
{{pysm::p,pyym::i},{pysm::b,pyym::u}},//鈈
{{pysm::n,pyym::a},{pysm::r,pyym::ui}},//鈉
{{pysm::x,pyym::in},{pysm::q,pyym::in}},//鈊
{{pysm::q,pyym::ian},{pysm::h,pyym::an}},//鈐
{{pysm::s,pyym::a},{pysm::x,pyym::i}},//鈒
{{pysm::n,pyym::iu},{pysm::ch,pyym::ou}},//鈕
{{pysm::y,pyym::un},{pysm::d,pyym::ui}},//鈗
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//鈚
{{pysm::g,pyym::u},{pysm::p,pyym::i}},//鈲
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//鈷
{{pysm::y,pyym::ou},{pysm::zh,pyym::ou}},//鈾
{{pysm::t,pyym::ian},{pysm::d,pyym::ian}},//鈿
{{pysm::j,pyym::ia},{pysm::g,pyym::e}},//鉀
{{pysm::sh,pyym::i},{pysm::z,pyym::u}},//鉃
{{pysm::zh,pyym::i},{pysm::t,pyym::ie}},//鉄
{{pysm::sh,pyym::i},{pysm::y,pyym::i}},//鉇
{{pysm::b,pyym::ao},{pysm::p,pyym::ao}},//鉋
{{pysm::b,pyym::i},{pysm::s,pyym::e}},//鉍
{{pysm::sh,pyym::i},{pysm::z,pyym::u}},//鉐
{{pysm::q,pyym::ian},{pysm::nop,pyym::an}},//鉗
{{pysm::l,pyym::iu},{pysm::m,pyym::ao}},//鉚
{{pysm::q,pyym::ian},{pysm::y,pyym::an}},//鉛
{{pysm::g,pyym::ou},{pysm::q,pyym::u}},//鉤
{{pysm::sh,pyym::u},{pysm::x,pyym::u}},//鉥
{{pysm::x,pyym::i},{pysm::n,pyym::ie}},//鉩
{{pysm::h,pyym::uan},{pysm::sh,pyym::en}},//鉮
{{pysm::t,pyym::ong},{pysm::zh,pyym::uo}},//鉵
{{pysm::nop,pyym::er},{pysm::k,pyym::eng}},//鉺
{{pysm::l,pyym::uo},{pysm::g,pyym::e}},//鉻
{{pysm::b,pyym::ing},{pysm::p,pyym::ing}},//鉼
{{pysm::m,pyym::ou},{pysm::m,pyym::ao}},//鉾
{{pysm::x,pyym::iang},{pysm::j,pyym::iong}},//銄
{{pysm::y,pyym::u},{pysm::s,pyym::i}},//銉
{{pysm::x,pyym::u},{pysm::h,pyym::ui}},//銊
{{pysm::sh,pyym::an},{pysm::sh,pyym::uo}},//銏
{{pysm::ch,pyym::i},{pysm::l,pyym::i}},//銐
{{pysm::x,pyym::ian},{pysm::x,pyym::i}},//銑
{{pysm::x,pyym::ing},{pysm::j,pyym::ian}},//銒
{{pysm::t,pyym::ie},{pysm::y,pyym::i}},//銕
{{pysm::x,pyym::iang},{pysm::h,pyym::ou}},//銗
{{pysm::sh,pyym::i},{pysm::zh,pyym::i}},//銴
{{pysm::zh,pyym::e},{pysm::n,pyym::ie}},//銸
{{pysm::x,pyym::iu},{pysm::y,pyym::ou}},//銹
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//銾
{{pysm::zh,pyym::ong},{pysm::y,pyym::ong}},//銿
{{pysm::m,pyym::ei},{pysm::m,pyym::eng}},//鋂
{{pysm::x,pyym::in},{pysm::z,pyym::i}},//鋅
{{pysm::y,pyym::un},{pysm::j,pyym::un}},//鋆
{{pysm::ch,pyym::an},{pysm::y,pyym::an}},//鋋
{{pysm::d,pyym::ing},{pysm::t,pyym::ing}},//鋌
{{pysm::s,pyym::i},{pysm::t,pyym::uo}},//鋖
{{pysm::x,pyym::uan},{pysm::j,pyym::uan}},//鋗
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//鋙
{{pysm::zh,pyym::uo},{pysm::ch,pyym::uo}},//鋜
{{pysm::x,pyym::ing},{pysm::j,pyym::ing}},//鋞
{{pysm::ch,pyym::u},{pysm::j,pyym::u}},//鋤
{{pysm::t,pyym::ie},{pysm::nop,pyym::e}},//鋨
{{pysm::z,pyym::ui},{pysm::n,pyym::ie}},//鋷
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//鋺
{{pysm::l,pyym::un},{pysm::f,pyym::en}},//錀
{{pysm::z,pyym::ui},{pysm::z,pyym::u}},//錊
{{pysm::p,pyym::eng},{pysm::b,pyym::eng}},//錋
{{pysm::l,pyym::ei},{pysm::l,pyym::i}},//錑
{{pysm::k,pyym::e},{pysm::nop,pyym::a}},//錒
{{pysm::k,pyym::un},{pysm::g,pyym::un}},//錕
{{pysm::q,pyym::i},{pysm::y,pyym::i}},//錡
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//錢
{{pysm::zh,pyym::ui},{pysm::ch,pyym::uo}},//錣
{{pysm::t,pyym::ian},{pysm::t,pyym::un}},//錪
{{pysm::x,pyym::i},{pysm::t,pyym::i}},//錫
{{pysm::t,pyym::ao},{pysm::d,pyym::iao}},//錭
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//録
{{pysm::w,pyym::an},{pysm::j,pyym::ian}},//錽
{{pysm::k,pyym::ai},{pysm::j,pyym::ie}},//鍇
{{pysm::l,pyym::ian},{pysm::j,pyym::ian}},//鍊
{{pysm::ch,pyym::en},{pysm::zh,pyym::en}},//鍖
{{pysm::sh,pyym::i},{pysm::sh,pyym::e}},//鍦
{{pysm::t,pyym::ian},{pysm::n,pyym::uo}},//鍩
{{pysm::y,pyym::e},{pysm::x,pyym::ie}},//鍱
{{pysm::s,pyym::ong},{pysm::s,pyym::i}},//鍶
{{pysm::zh,pyym::en},{pysm::q,pyym::ian}},//鍼
{{pysm::s,pyym::uo},{pysm::ch,pyym::a}},//鎈
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//鎉
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//鎊
{{pysm::s,pyym::uo},{pysm::s,pyym::e}},//鎍
{{pysm::y,pyym::ao},{pysm::z,pyym::u}},//鎐
{{pysm::n,pyym::ou},{pysm::h,pyym::ao}},//鎒
{{pysm::q,pyym::iang},{pysm::ch,pyym::eng}},//鎗
{{pysm::l,pyym::i},{pysm::g,pyym::e}},//鎘
{{pysm::d,pyym::a},{pysm::s,pyym::a}},//鎝
{{pysm::b,pyym::i},{pysm::p,pyym::i}},//鎞
{{pysm::y,pyym::ing},{pysm::j,pyym::iong}},//鎣
{{pysm::h,pyym::ao},{pysm::g,pyym::ao}},//鎬
{{pysm::zh,pyym::en},{pysm::t,pyym::ian}},//鎮
{{pysm::l,pyym::ang},{pysm::l,pyym::uo}},//鎯
{{pysm::nop,pyym::ou},{pysm::k,pyym::ou}},//鏂
{{pysm::z,pyym::u},{pysm::ch,pyym::uo}},//鏃
{{pysm::sh,pyym::ou},{pysm::s,pyym::ou}},//鏉
{{pysm::l,pyym::iu},{pysm::l,pyym::iao}},//鏐
{{pysm::z,pyym::ong},{pysm::c,pyym::ong}},//鏓
{{pysm::l,pyym::u},{pysm::nop,pyym::ao}},//鏕
{{pysm::nop,pyym::ao},{pysm::b,pyym::iao}},//鏖
{{pysm::l,pyym::ou},{pysm::l,pyym::v}},//鏤
{{pysm::j,pyym::ian},{pysm::z,pyym::an}},//鏩
{{pysm::k,pyym::ui},{pysm::g,pyym::ui}},//鐀
{{pysm::j,pyym::ue},{pysm::y,pyym::u}},//鐍
{{pysm::d,pyym::ui},{pysm::d,pyym::un}},//鐓
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//鐖
{{pysm::d,pyym::ui},{pysm::d,pyym::un}},//鐜
{{pysm::z,pyym::an},{pysm::t,pyym::i}},//鐟
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//鐱
{{pysm::zh,pyym::uo},{pysm::sh,pyym::u}},//鐲
{{pysm::b,pyym::i},{pysm::b,pyym::ei}},//鐴
{{pysm::t,pyym::ie},{pysm::d,pyym::ie}},//鐵
{{pysm::h,pyym::uan},{pysm::x,pyym::uan}},//鐶
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//鐻
{{pysm::f,pyym::en},{pysm::b,pyym::en}},//鐼
{{pysm::n,pyym::ie},{pysm::n,pyym::i}},//鑈
{{pysm::m,pyym::ie},{pysm::m,pyym::i}},//鑖
{{pysm::k,pyym::uang},{pysm::g,pyym::ong}},//鑛
{{pysm::x,pyym::in},{pysm::x,pyym::un}},//鑫
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//鑯
{{pysm::y,pyym::ao},{pysm::y,pyym::ue}},//鑰
{{pysm::x,pyym::iang},{pysm::r,pyym::ang}},//鑲
{{pysm::x,pyym::i},{pysm::h,pyym::ui}},//鑴
{{pysm::n,pyym::ie},{pysm::y,pyym::i}},//钀
{{pysm::y,pyym::ao},{pysm::y,pyym::ue}},//钥
{{pysm::t,pyym::ou},{pysm::d,pyym::ou}},//钭
{{pysm::b,pyym::a},{pysm::p,pyym::a}},//钯
{{pysm::d,pyym::ian},{pysm::t,pyym::ian}},//钿
{{pysm::q,pyym::ian},{pysm::y,pyym::an}},//铅
{{pysm::t,pyym::a},{pysm::t,pyym::uo}},//铊
{{pysm::d,pyym::ang},{pysm::ch,pyym::eng}},//铛
{{pysm::x,pyym::i},{pysm::x,pyym::ian}},//铣
{{pysm::d,pyym::ing},{pysm::t,pyym::ing}},//铤
{{pysm::d,pyym::iao},{pysm::y,pyym::ao}},//铫
{{pysm::w,pyym::u},{pysm::y,pyym::u}},//铻
{{pysm::t,pyym::an},{pysm::x,pyym::ian}},//锬
{{pysm::g,pyym::ao},{pysm::h,pyym::ao}},//镐
{{pysm::d,pyym::ui},{pysm::d,pyym::un}},//镦
{{pysm::zh,pyym::ang},{pysm::ch,pyym::ang}},//長
{{pysm::zh,pyym::ang},{pysm::ch,pyym::ang}},//长
{{pysm::h,pyym::uo},{pysm::sh,pyym::an}},//閄
{{pysm::h,pyym::an},{pysm::b,pyym::i}},//閈
{{pysm::k,pyym::ai},{pysm::q,pyym::ian}},//開
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//閒
{{pysm::x,pyym::ia},{pysm::nop,pyym::e}},//閜
{{pysm::b,pyym::ian},{pysm::g,pyym::uan}},//閞
{{pysm::g,pyym::e},{pysm::h,pyym::e}},//閤
{{pysm::h,pyym::ong},{pysm::x,pyym::iang}},//閧
{{pysm::l,pyym::ang},{pysm::l,pyym::iang}},//閬
{{pysm::ch,pyym::ang},{pysm::t,pyym::ang}},//閶
{{pysm::sh,pyym::ai},{pysm::sh,pyym::a}},//閷
{{pysm::b,pyym::an},{pysm::p,pyym::an}},//闆
{{pysm::nop,pyym::an},{pysm::y,pyym::in}},//闇
{{pysm::d,pyym::u},{pysm::sh,pyym::e}},//闍
{{pysm::q,pyym::ue},{pysm::j,pyym::ue}},//闕
{{pysm::ch,pyym::uang},{pysm::ch,pyym::en}},//闖
{{pysm::t,pyym::ang},{pysm::ch,pyym::ang}},//闛
{{pysm::g,pyym::uan},{pysm::w,pyym::an}},//關
{{pysm::d,pyym::ang},{pysm::t,pyym::ang}},//闣
{{pysm::d,pyym::u},{pysm::sh,pyym::e}},//阇
{{pysm::nop,pyym::e},{pysm::y,pyym::an}},//阏
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//阘
{{pysm::h,pyym::an},{pysm::k,pyym::an}},//阚
{{pysm::w,pyym::u},{pysm::w,pyym::ei}},//阢
{{pysm::g,pyym::ai},{pysm::y,pyym::i}},//阣
{{pysm::nop,pyym::e},{pysm::nop,pyym::ai}},//阨
{{pysm::y,pyym::un},{pysm::y,pyym::an}},//阭
{{pysm::r,pyym::uan},{pysm::y,pyym::uan}},//阮
{{pysm::nop,pyym::e},{pysm::nop,pyym::ai}},//阸
{{pysm::z,pyym::u},{pysm::zh,pyym::u}},//阻
{{pysm::d,pyym::ian},{pysm::y,pyym::an}},//阽
{{pysm::nop,pyym::a},{pysm::nop,pyym::e}},//阿
{{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//陀
{{pysm::f,pyym::u},{pysm::b,pyym::u}},//附
{{pysm::l,pyym::u},{pysm::l,pyym::iu}},//陆
{{pysm::j,pyym::iang},{pysm::x,pyym::iang}},//降
{{pysm::d,pyym::uo},{pysm::s,pyym::ui}},//陏
{{pysm::x,pyym::ian},{pysm::w,pyym::en}},//限
{{pysm::x,pyym::ing},{pysm::j,pyym::ing}},//陘
{{pysm::f,pyym::u},{pysm::w,pyym::u}},//陚
{{pysm::zh,pyym::i},{pysm::d,pyym::e}},//陟
{{pysm::p,pyym::u},{pysm::b,pyym::u}},//陠
{{pysm::f,pyym::ei},{pysm::p,pyym::ei}},//陫
{{pysm::z,pyym::ou},{pysm::zh,pyym::e}},//陬
{{pysm::y,pyym::in},{pysm::nop,pyym::an}},//陰
{{pysm::ch,pyym::en},{pysm::zh,pyym::en}},//陳
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//陴
{{pysm::l,pyym::u},{pysm::l,pyym::iu}},//陸
{{pysm::zh,pyym::u},{pysm::d,pyym::u}},//陼
{{pysm::r,pyym::eng},{pysm::nop,pyym::er}},//陾
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//隄
{{pysm::h,pyym::ui},{pysm::d,pyym::uo}},//隓
{{pysm::y,pyym::un},{pysm::y,pyym::uan}},//隕
{{pysm::nop,pyym::ai},{pysm::nop,pyym::e}},//隘
{{pysm::j,pyym::iao},{pysm::p,pyym::i}},//隦
{{pysm::s,pyym::ui},{pysm::zh,pyym::ui}},//隧
{{pysm::nop,pyym::ao},{pysm::y,pyym::u}},//隩
{{pysm::x,pyym::i},{pysm::x,pyym::ie}},//隰
{{pysm::zh,pyym::i},{pysm::h,pyym::uo}},//隻
{{pysm::j,pyym::uan},{pysm::j,pyym::un}},//隽
{{pysm::q,pyym::ue},{pysm::q,pyym::iao}},//雀
{{pysm::q,pyym::ian},{pysm::j,pyym::ie}},//雃
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//雇
{{pysm::g,pyym::uan},{pysm::h,pyym::uan}},//雚
{{pysm::ch,pyym::u},{pysm::j,pyym::u}},//雛
{{pysm::n,pyym::an},{pysm::n,pyym::uo}},//難
{{pysm::y,pyym::u},{pysm::x,pyym::u}},//雩
{{pysm::s,pyym::e},{pysm::x,pyym::i}},//雭
{{pysm::p,pyym::ang},{pysm::f,pyym::ang}},//雱
{{pysm::l,pyym::ing},{pysm::l,pyym::ian}},//零
{{pysm::w,pyym::u},{pysm::m,pyym::eng}},//雺
{{pysm::zh,pyym::en},{pysm::sh,pyym::en}},//震
{{pysm::y,pyym::ing},{pysm::y,pyym::ang}},//霙
{{pysm::w,pyym::u},{pysm::m,pyym::eng}},//霧
{{pysm::x,pyym::ian},{pysm::s,pyym::an}},//霰
{{pysm::l,pyym::u},{pysm::l,pyym::ou}},//露
{{pysm::b,pyym::a},{pysm::p,pyym::o}},//霸
{{pysm::m,pyym::ai},{pysm::l,pyym::i}},//霾
{{pysm::l,pyym::ong},{pysm::l,pyym::ing}},//靇
{{pysm::nop,pyym::ai},{pysm::y,pyym::i}},//靉
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//青
{{pysm::j,pyym::ing},{pysm::l,pyym::iang}},//靓
{{pysm::q,pyym::ing},{pysm::j,pyym::ing}},//靘
{{pysm::j,pyym::ing},{pysm::l,pyym::iang}},//靚
{{pysm::m,pyym::i},{pysm::m,pyym::a}},//靡
{{pysm::t,pyym::ian},{pysm::m,pyym::ian}},//靦
{{pysm::y,pyym::e},{pysm::y,pyym::an}},//靨
{{pysm::g,pyym::e},{pysm::j,pyym::i}},//革
{{pysm::s,pyym::a},{pysm::t,pyym::a}},//靸
{{pysm::m,pyym::o},{pysm::w,pyym::a}},//靺
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//鞊
{{pysm::x,pyym::ie},{pysm::w,pyym::a}},//鞋
{{pysm::m,pyym::an},{pysm::m,pyym::en}},//鞔
{{pysm::y,pyym::ing},{pysm::b,pyym::ian}},//鞕
{{pysm::q,pyym::iao},{pysm::sh,pyym::ao}},//鞘
{{pysm::x,pyym::uan},{pysm::j,pyym::uan}},//鞙
{{pysm::sh,pyym::ang},{pysm::zh,pyym::ang}},//鞝
{{pysm::m,pyym::u},{pysm::m,pyym::ou}},//鞪
{{pysm::j,pyym::u},{pysm::q,pyym::u}},//鞫
{{pysm::b,pyym::i},{pysm::b,pyym::ing}},//鞸
{{pysm::g,pyym::ui},{pysm::h,pyym::ui}},//鞼
{{pysm::q,pyym::iao},{pysm::j,pyym::ue}},//鞽
{{pysm::d,pyym::a},{pysm::t,pyym::a}},//韃
{{pysm::w,pyym::ei},{pysm::h,pyym::ui}},//韋
{{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//韏
{{pysm::q,pyym::iao},{pysm::sh,pyym::ao}},//韒
{{pysm::b,pyym::ai},{pysm::f,pyym::u}},//韛
{{pysm::y,pyym::un},{pysm::w,pyym::en}},//韞
{{pysm::w,pyym::ei},{pysm::x,pyym::ue}},//韡
{{pysm::s,pyym::ui},{pysm::h,pyym::ui}},//韢
{{pysm::h,pyym::uang},{pysm::y,pyym::ing}},//韹
{{pysm::y,pyym::e},{pysm::x,pyym::ie}},//頁
{{pysm::q,pyym::ing},{pysm::k,pyym::ui}},//頃
{{pysm::h,pyym::an},{pysm::nop,pyym::an}},//頇
{{pysm::s,pyym::ong},{pysm::r,pyym::ong}},//頌
{{pysm::q,pyym::i},{pysm::k,pyym::en}},//頎
{{pysm::h,pyym::ang},{pysm::g,pyym::ang}},//頏
{{pysm::w,pyym::an},{pysm::k,pyym::un}},//頑
{{pysm::b,pyym::an},{pysm::f,pyym::en}},//頒
{{pysm::d,pyym::un},{pysm::d,pyym::u}},//頓
{{pysm::d,pyym::an},{pysm::d,pyym::ian}},//頕
{{pysm::p,pyym::o},{pysm::p,pyym::i}},//頗
{{pysm::nop,pyym::e},{pysm::nop,pyym::an}},//頞
{{pysm::h,pyym::ai},{pysm::k,pyym::e}},//頦
{{pysm::y,pyym::u},{pysm::b,pyym::ian}},//頨
{{pysm::y,pyym::ing},{pysm::j,pyym::ing}},//頴
{{pysm::j,pyym::ing},{pysm::g,pyym::eng}},//頸
{{pysm::p,pyym::in},{pysm::b,pyym::in}},//頻
{{pysm::t,pyym::an},{pysm::sh,pyym::an}},//顃
{{pysm::k,pyym::e},{pysm::k,pyym::uan}},//顆
{{pysm::c,pyym::ui},{pysm::z,pyym::u}},//顇
{{pysm::t,pyym::i},{pysm::d,pyym::i}},//題
{{pysm::w,pyym::en},{pysm::h,pyym::un}},//顐
{{pysm::k,pyym::an},{pysm::y,pyym::an}},//顑
{{pysm::y,pyym::ong},{pysm::y,pyym::u}},//顒
{{pysm::y,pyym::an},{pysm::y,pyym::a}},//顔
{{pysm::d,pyym::ian},{pysm::t,pyym::ian}},//顚
{{pysm::k,pyym::ui},{pysm::k,pyym::ua}},//顝
{{pysm::w,pyym::ai},{pysm::zh,pyym::uai}},//顡
{{pysm::y,pyym::ao},{pysm::q,pyym::iao}},//顤
{{pysm::l,pyym::an},{pysm::l,pyym::in}},//顲
{{pysm::d,pyym::un},{pysm::d,pyym::u}},//顿
{{pysm::j,pyym::ing},{pysm::g,pyym::eng}},//颈
{{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//颉
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//颌
{{pysm::ch,pyym::an},{pysm::zh,pyym::an}},//颤
{{pysm::b,pyym::iao},{pysm::d,pyym::iu}},//颩
{{pysm::b,pyym::iao},{pysm::p,pyym::ao}},//颮
{{pysm::s,pyym::a},{pysm::l,pyym::i}},//颯
{{pysm::b,pyym::a},{pysm::f,pyym::u}},//颰
{{pysm::g,pyym::ua},{pysm::j,pyym::i}},//颳
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao}},//颵
{{pysm::s,pyym::ou},{pysm::s,pyym::ao}},//颾
{{pysm::l,pyym::iu},{pysm::l,pyym::iao}},//飂
{{pysm::zh,pyym::an},{pysm::g,pyym::an}},//飦
{{pysm::t,pyym::un},{pysm::zh,pyym::un}},//飩
{{pysm::j,pyym::uan},{pysm::y,pyym::ong}},//飬
{{pysm::ch,pyym::i},{pysm::sh,pyym::i}},//飭
{{pysm::s,pyym::un},{pysm::c,pyym::an}},//飱
{{pysm::t,pyym::ou},{pysm::zh,pyym::u}},//飳
{{pysm::y,pyym::i},{pysm::s,pyym::i}},//飴
{{pysm::z,pyym::uo},{pysm::z,pyym::e}},//飵
{{pysm::sh,pyym::i},{pysm::ch,pyym::i}},//飾
{{pysm::j,pyym::ia},{pysm::h,pyym::e}},//餄
{{pysm::c,pyym::an},{pysm::s,pyym::un}},//餐
{{pysm::y,pyym::u},{pysm::y,pyym::e}},//餘
{{pysm::sh,pyym::i},{pysm::x,pyym::i}},//餙
{{pysm::h,pyym::un},{pysm::k,pyym::un}},//餛
{{pysm::x,pyym::ian},{pysm::k,pyym::an}},//餡
{{pysm::t,pyym::an},{pysm::d,pyym::an}},//餤
{{pysm::w,pyym::ei},{pysm::n,pyym::ei}},//餧
{{pysm::y,pyym::un},{pysm::h,pyym::un}},//餫
{{pysm::j,pyym::ian},{pysm::zh,pyym::an}},//餰
{{pysm::nop,pyym::ai},{pysm::h,pyym::e}},//餲
{{pysm::t,pyym::ang},{pysm::x,pyym::ing}},//餳
{{pysm::t,pyym::ao},{pysm::x,pyym::ian}},//饀
{{pysm::k,pyym::ui},{pysm::t,pyym::ui}},//饋
{{pysm::zh,pyym::uan},{pysm::x,pyym::uan}},//饌
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//饑
{{pysm::t,pyym::ang},{pysm::x,pyym::ing}},//饧
{{pysm::l,pyym::e},{pysm::g,pyym::e}},//饹
{{pysm::ch,pyym::a},{pysm::zh,pyym::a}},//馇
{{pysm::k,pyym::ui},{pysm::q,pyym::iu}},//馗
{{pysm::g,pyym::uo},{pysm::x,pyym::u}},//馘
{{pysm::b,pyym::o},{pysm::p,pyym::o}},//馞
{{pysm::f,pyym::u},{pysm::b,pyym::i}},//馥
{{pysm::y,pyym::un},{pysm::w,pyym::o}},//馧
{{pysm::f,pyym::eng},{pysm::p,pyym::ing}},//馮
{{pysm::h,pyym::an},{pysm::q,pyym::ian}},//馯
{{pysm::zh,pyym::e},{pysm::t,pyym::uo}},//馲
{{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//馶
{{pysm::x,pyym::in},{pysm::j,pyym::in}},//馸
{{pysm::j,pyym::ue},{pysm::k,pyym::uai}},//駃
{{pysm::p,pyym::ei},{pysm::p,pyym::eng}},//駍
{{pysm::z,pyym::ang},{pysm::z,pyym::u}},//駔
{{pysm::x,pyym::un},{pysm::x,pyym::uan}},//駨
{{pysm::l,pyym::uo},{pysm::j,pyym::ia}},//駱
{{pysm::l,pyym::ang},{pysm::l,pyym::iang}},//駺
{{pysm::zh,pyym::ou},{pysm::d,pyym::ong}},//騆
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//騎
{{pysm::k,pyym::ui},{pysm::j,pyym::ue}},//騤
{{pysm::g,pyym::ui},{pysm::t,pyym::ui}},//騩
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//騫
{{pysm::p,pyym::eng},{pysm::b,pyym::ang}},//騯
{{pysm::s,pyym::ao},{pysm::x,pyym::iao}},//騷
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//騺
{{pysm::m,pyym::o},{pysm::m,pyym::a}},//驀
{{pysm::nop,pyym::ao},{pysm::y,pyym::ao}},//驁
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//驃
{{pysm::l,pyym::ong},{pysm::z,pyym::ang}},//驡
{{pysm::l,pyym::i},{pysm::ch,pyym::i}},//驪
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//驫
{{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//驮
{{pysm::d,pyym::ai},{pysm::t,pyym::ai}},//骀
{{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//骠
{{pysm::w,pyym::ei},{pysm::w,pyym::an}},//骫
{{pysm::nop,pyym::ang},{pysm::k,pyym::ang}},//骯
{{pysm::t,pyym::ou},{pysm::g,pyym::u}},//骰
{{pysm::c,pyym::i},{pysm::zh,pyym::ai}},//骴
{{pysm::h,pyym::ai},{pysm::g,pyym::ai}},//骸
{{pysm::k,pyym::e},{pysm::k,pyym::ua}},//髁
{{pysm::q,pyym::ia},{pysm::g,pyym::e}},//髂
{{pysm::b,pyym::o},{pysm::p,pyym::o}},//髆
{{pysm::b,pyym::ang},{pysm::p,pyym::ang}},//髈
{{pysm::b,pyym::o},{pysm::j,pyym::ue}},//髉
{{pysm::c,pyym::i},{pysm::c,pyym::uo}},//髊
{{pysm::f,pyym::u},{pysm::f,pyym::ei}},//髴
{{pysm::r,pyym::ong},{pysm::nop,pyym::er}},//髶
{{pysm::k,pyym::uo},{pysm::y,pyym::ue}},//髺
{{pysm::j,pyym::i},{pysm::j,pyym::ie}},//髻
{{pysm::d,pyym::i},{pysm::t,pyym::i}},//鬄
{{pysm::k,pyym::uo},{pysm::k,pyym::uai}},//鬠
{{pysm::r,pyym::ang},{pysm::n,pyym::ing}},//鬤
{{pysm::h,pyym::ong},{pysm::x,pyym::iang}},//鬨
{{pysm::x,pyym::i},{pysm::h,pyym::e}},//鬩
{{pysm::f,pyym::u},{pysm::l,pyym::i}},//鬴
{{pysm::q,pyym::in},{pysm::x,pyym::in}},//鬵
{{pysm::z,pyym::ong},{pysm::z,pyym::eng}},//鬷
{{pysm::g,pyym::ui},{pysm::x,pyym::ie}},//鬹
{{pysm::j,pyym::i},{pysm::q,pyym::i}},//鬾
{{pysm::k,pyym::ui},{pysm::k,pyym::uai}},//魁
{{pysm::t,pyym::ui},{pysm::ch,pyym::ui}},//魋
{{pysm::j,pyym::ie},{pysm::j,pyym::i}},//魝
{{pysm::h,pyym::ong},{pysm::g,pyym::ong}},//魟
{{pysm::d,pyym::iao},{pysm::d,pyym::i}},//魡
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//魣
{{pysm::nop,pyym::e},{pysm::h,pyym::ua}},//魤
{{pysm::sh,pyym::a},{pysm::s,pyym::uo}},//魦
{{pysm::y,pyym::uan},{pysm::w,pyym::an}},//魭
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//魮
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//魯
{{pysm::z,pyym::a},{pysm::sh,pyym::i}},//魳
{{pysm::h,pyym::e},{pysm::g,pyym::e}},//魺
{{pysm::q,pyym::u},{pysm::x,pyym::ie}},//魼
{{pysm::l,pyym::ing},{pysm::l,pyym::in}},//魿
{{pysm::b,pyym::o},{pysm::b,pyym::a}},//鮁
{{pysm::c,pyym::i},{pysm::j,pyym::i}},//鮆
{{pysm::b,pyym::a},{pysm::b,pyym::o}},//鮊
{{pysm::y,pyym::ou},{pysm::ch,pyym::ou}},//鮋
{{pysm::p,pyym::i},{pysm::j,pyym::u}},//鮍
{{pysm::x,pyym::ing},{pysm::zh,pyym::eng}},//鮏
{{pysm::b,pyym::ao},{pysm::p,pyym::ao}},//鮑
{{pysm::j,pyym::ie},{pysm::q,pyym::ia}},//鮚
{{pysm::x,pyym::iang},{pysm::zh,pyym::en}},//鮝
{{pysm::l,pyym::uo},{pysm::g,pyym::e}},//鮥
{{pysm::t,pyym::i},{pysm::y,pyym::i}},//鮧
{{pysm::y,pyym::i},{pysm::q,pyym::i}},//鮨
{{pysm::b,pyym::ing},{pysm::b,pyym::i}},//鮩
{{pysm::sh,pyym::an},{pysm::sh,pyym::en}},//鯅
{{pysm::p,pyym::u},{pysm::b,pyym::u}},//鯆
{{pysm::zh,pyym::eng},{pysm::q,pyym::ing}},//鯖
{{pysm::j,pyym::iu},{pysm::nop,pyym::ai}},//鯦
{{pysm::j,pyym::ing},{pysm::q,pyym::ing}},//鯨
{{pysm::z,pyym::ei},{pysm::j,pyym::i}},//鯽
{{pysm::z,pyym::ei},{pysm::z,pyym::e}},//鰂
{{pysm::s,pyym::ai},{pysm::x,pyym::i}},//鰓
{{pysm::t,pyym::uo},{pysm::w,pyym::ei}},//鰖
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//鰜
{{pysm::f,pyym::ang},{pysm::p,pyym::ang}},//鰟
{{pysm::t,pyym::a},{pysm::d,pyym::ie}},//鰨
{{pysm::nop,pyym::e},{pysm::g,pyym::e}},//鰪
{{pysm::x,pyym::iu},{pysm::q,pyym::iu}},//鱃
{{pysm::sh,pyym::an},{pysm::t,pyym::uo}},//鱓
{{pysm::g,pyym::ui},{pysm::j,pyym::ue}},//鱖
{{pysm::zh,pyym::an},{pysm::sh,pyym::an}},//鱣
{{pysm::x,pyym::u},{pysm::y,pyym::u}},//鱮
{{pysm::l,pyym::ie},{pysm::l,pyym::a}},//鱲
{{pysm::b,pyym::a},{pysm::b,pyym::o}},//鲅
{{pysm::b,pyym::a},{pysm::b,pyym::o}},//鲌
{{pysm::g,pyym::ui},{pysm::x,pyym::ie}},//鲑
{{pysm::q,pyym::ing},{pysm::zh,pyym::eng}},//鲭
{{pysm::d,pyym::iao},{pysm::zh,pyym::ao}},//鳭
{{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//鳷
{{pysm::f,pyym::u},{pysm::g,pyym::ui}},//鳺
{{pysm::b,pyym::an},{pysm::f,pyym::en}},//鳻
{{pysm::y,pyym::ao},{pysm::nop,pyym::ao}},//鴁
{{pysm::j,pyym::ue},{pysm::g,pyym::ui}},//鴂
{{pysm::m,pyym::ie},{pysm::b,pyym::i}},//鴓
{{pysm::m,pyym::in},{pysm::w,pyym::en}},//鴖
{{pysm::q,pyym::u},{pysm::g,pyym::ou}},//鴝
{{pysm::y,pyym::ao},{pysm::nop,pyym::ao}},//鴢
{{pysm::t,pyym::ie},{pysm::h,pyym::u}},//鴩
{{pysm::y,pyym::ang},{pysm::x,pyym::iang}},//鴹
{{pysm::t,pyym::i},{pysm::y,pyym::i}},//鴺
{{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//鵁
{{pysm::zh,pyym::ou},{pysm::d,pyym::iao}},//鵃
{{pysm::l,pyym::uo},{pysm::g,pyym::e}},//鵅
{{pysm::b,pyym::u},{pysm::p,pyym::u}},//鵏
{{pysm::l,pyym::ai},{pysm::ch,pyym::i}},//鵣
{{pysm::nop,pyym::an},{pysm::y,pyym::a}},//鵪
{{pysm::p,pyym::eng},{pysm::f,pyym::eng}},//鵬
{{pysm::j,pyym::ing},{pysm::q,pyym::ing}},//鶄
{{pysm::ch,pyym::un},{pysm::t,pyym::uan}},//鶉
{{pysm::j,pyym::ue},{pysm::q,pyym::u}},//鶌
{{pysm::t,pyym::i},{pysm::ch,pyym::i}},//鶗
{{pysm::f,pyym::u},{pysm::b,pyym::i}},//鶝
{{pysm::p,pyym::ian},{pysm::b,pyym::ian}},//鶣
{{pysm::ch,pyym::uan},{pysm::zh,pyym::i}},//鶨
{{pysm::w,pyym::u},{pysm::m,pyym::u}},//鶩
{{pysm::c,pyym::ang},{pysm::q,pyym::iang}},//鶬
{{pysm::h,pyym::e},{pysm::h,pyym::u}},//鶮
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//鶻
{{pysm::j,pyym::ian},{pysm::q,pyym::ian}},//鶼
{{pysm::s,pyym::un},{pysm::x,pyym::un}},//鶽
{{pysm::t,pyym::i},{pysm::s,pyym::i}},//鷉
{{pysm::y,pyym::ao},{pysm::x,pyym::iao}},//鷕
{{pysm::zh,pyym::i},{pysm::zh,pyym::e}},//鷙
{{pysm::t,pyym::i},{pysm::t,pyym::an}},//鷤
{{pysm::y,pyym::u},{pysm::sh,pyym::u}},//鷸
{{pysm::ch,pyym::u},{pysm::zh,pyym::u}},//鸀
{{pysm::x,pyym::i},{pysm::q,pyym::i}},//鸂
{{pysm::p,pyym::i},{pysm::b,pyym::i}},//鸊
{{pysm::m,pyym::eng},{pysm::m,pyym::ang}},//鸏
{{pysm::n,pyym::iao},{pysm::d,pyym::iao}},//鸟
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//鹄
{{pysm::g,pyym::u},{pysm::h,pyym::u}},//鹘
{{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//鹹
{{pysm::l,pyym::u},{pysm::l,pyym::v}},//鹿
{{pysm::zh,pyym::u},{pysm::c,pyym::u}},//麆
{{pysm::j,pyym::un},{pysm::q,pyym::un}},//麇
{{pysm::j,pyym::un},{pysm::q,pyym::un}},//麕
{{pysm::l,pyym::i},{pysm::s,pyym::i}},//麗
{{pysm::x,pyym::ian},{pysm::y,pyym::an}},//麙
{{pysm::x,pyym::ian},{pysm::y,pyym::an}},//麲
{{pysm::ch,pyym::i},{pysm::l,pyym::i}},//黐
{{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//黚
{{pysm::y,pyym::ou},{pysm::y,pyym::i}},//黝
{{pysm::y,pyym::ue},{pysm::y,pyym::e}},//黦
{{pysm::l,pyym::i},{pysm::l,pyym::ai}},//黧
{{pysm::y,pyym::an},{pysm::j,pyym::ian}},//黬
{{pysm::zh,pyym::en},{pysm::y,pyym::an}},//黰
{{pysm::d,pyym::ai},{pysm::zh,pyym::en}},//黱
{{pysm::y,pyym::i},{pysm::w,pyym::a}},//黳
{{pysm::zh,pyym::an},{pysm::d,pyym::an}},//黵
{{pysm::zh,pyym::i},{pysm::x,pyym::ian}},//黹
{{pysm::ch,pyym::ao},{pysm::zh,pyym::ao}},//鼂
{{pysm::d,pyym::ing},{pysm::zh,pyym::en}},//鼎
{{pysm::d,pyym::ong},{pysm::t,pyym::ong}},//鼕
{{pysm::q,pyym::i},{pysm::c,pyym::ao}},//鼜
{{pysm::b,pyym::a},{pysm::f,pyym::ei}},//鼥
{{pysm::j,pyym::u},{pysm::x,pyym::i}},//鼳
{{pysm::w,pyym::u},{pysm::h,pyym::ui}},//鼿
{{pysm::h,pyym::ou},{pysm::k,pyym::u}},//齁
{{pysm::nop,pyym::e},{pysm::h,pyym::e}},//齃
{{pysm::z,pyym::i},{pysm::j,pyym::i}},//齍
{{pysm::q,pyym::i},{pysm::j,pyym::i}},//齐
{{pysm::y,pyym::in},{pysm::y,pyym::an}},//齗
{{pysm::x,pyym::ie},{pysm::sh,pyym::i}},//齛
{{pysm::ch,pyym::ai},{pysm::z,pyym::i}},//齜
{{pysm::j,pyym::u},{pysm::zh,pyym::a}},//齟
{{pysm::ch,pyym::u},{pysm::ch,pyym::i}},//齣
{{pysm::y,pyym::u},{pysm::w,pyym::u}},//齬
{{pysm::y,pyym::i},{pysm::q,pyym::i}},//齮
{{pysm::z,pyym::ou},{pysm::ch,pyym::uo}},//齱
{{pysm::nop,pyym::ou},{pysm::y,pyym::u}},//齵
{{pysm::c,pyym::i},{pysm::c,pyym::uo}},//齹
{{pysm::y,pyym::a},{pysm::nop,pyym::e}},//齾
{{pysm::k,pyym::en},{pysm::y,pyym::in}},//龈
{{pysm::l,pyym::ong},{pysm::m,pyym::ang}},//龍
{{pysm::g,pyym::ong},{pysm::w,pyym::o}},//龏
{{pysm::p,pyym::ang},{pysm::l,pyym::ong}},//龐
{{pysm::k,pyym::an},{pysm::k,pyym::e}},//龕
};
constexpr static PinYin3 s_pinyin3[] = { {{pysm::k,pyym::ao},{pysm::q,pyym::iao},{pysm::y,pyym::u}},//丂
{{pysm::b,pyym::u},{pysm::f,pyym::ou},{pysm::f,pyym::u}},//不
{{pysm::q,pyym::ie},{pysm::j,pyym::u},{pysm::c,pyym::u}},//且
{{pysm::ch,pyym::eng},{pysm::sh,pyym::eng},{pysm::zh,pyym::eng}},//丞
{{pysm::b,pyym::ing},{pysm::b,pyym::an},{pysm::b,pyym::ang}},//並
{{pysm::ch,pyym::uan},{pysm::g,pyym::uan},{pysm::q,pyym::uan}},//串
{{pysm::y,pyym::in},{pysm::p,pyym::an},{pysm::zh,pyym::ong}},//乑
{{pysm::y,pyym::u},{pysm::w,pyym::ei},{pysm::x,pyym::u}},//于
{{pysm::g,pyym::en},{pysm::x,pyym::uan},{pysm::g,pyym::eng}},//亘
{{pysm::k,pyym::ang},{pysm::g,pyym::ang},{pysm::g,pyym::eng}},//亢
{{pysm::h,pyym::eng},{pysm::x,pyym::iang},{pysm::p,pyym::eng}},//亨
{{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::zh,pyym::an}},//亶
{{pysm::j,pyym::in},{pysm::f,pyym::u},{pysm::n,pyym::u}},//仅
{{pysm::ch,pyym::ou},{pysm::q,pyym::iu},{pysm::j,pyym::u}},//仇
{{pysm::g,pyym::e},{pysm::y,pyym::i},{pysm::w,pyym::u}},//仡
{{pysm::j,pyym::i},{pysm::zh,pyym::i},{pysm::q,pyym::i}},//伎
{{pysm::g,pyym::a},{pysm::j,pyym::ia},{pysm::q,pyym::ie}},//伽
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::y,pyym::an}},//但
{{pysm::t,pyym::i},{pysm::b,pyym::en},{pysm::c,pyym::ui}},//体
{{pysm::zh,pyym::an},{pysm::ch,pyym::an},{pysm::d,pyym::ian}},//佔
{{pysm::y,pyym::u},{pysm::t,pyym::u},{pysm::x,pyym::u}},//余
{{pysm::g,pyym::ou},{pysm::k,pyym::ou},{pysm::j,pyym::u}},//佝
{{pysm::c,pyym::e},{pysm::z,pyym::e},{pysm::zh,pyym::ai}},//侧
{{pysm::j,pyym::un},{pysm::sh,pyym::un},{pysm::d,pyym::un}},//俊
{{pysm::ch,pyym::u},{pysm::sh,pyym::u},{pysm::t,pyym::i}},//俶
{{pysm::b,pyym::i},{pysm::b,pyym::ei},{pysm::p,pyym::i}},//俾
{{pysm::ch,pyym::ang},{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//倀
{{pysm::t,pyym::i},{pysm::d,pyym::iao},{pysm::zh,pyym::ou}},//倜
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong},{pysm::t,pyym::ong}},//偅
{{pysm::j,pyym::i},{pysm::j,pyym::ie},{pysm::q,pyym::i}},//偈
{{pysm::x,pyym::ie},{pysm::y,pyym::e},{pysm::zh,pyym::a}},//偞
{{pysm::ch,pyym::ou},{pysm::q,pyym::iao},{pysm::z,pyym::ou}},//偢
{{pysm::c,pyym::e},{pysm::z,pyym::e},{pysm::zh,pyym::ai}},//側
{{pysm::w,pyym::ei},{pysm::nop,pyym::e},{pysm::g,pyym::ui}},//偽
{{pysm::g,pyym::ui},{pysm::k,pyym::ui},{pysm::k,pyym::uai}},//傀
{{pysm::c,pyym::ang},{pysm::ch,pyym::eng},{pysm::ch,pyym::en}},//傖
{{pysm::l,pyym::ou},{pysm::l,pyym::iu},{pysm::l,pyym::v}},//僂
{{pysm::ch,pyym::eng},{pysm::d,pyym::eng},{pysm::t,pyym::eng}},//僜
{{pysm::t,pyym::ong},{pysm::zh,pyym::uang},{pysm::ch,pyym::ong}},//僮
{{pysm::j,pyym::ia},{pysm::q,pyym::ia},{pysm::j,pyym::ie}},//價
{{pysm::n,pyym::i},{pysm::y,pyym::i},{pysm::nop,pyym::ai}},//儗
{{pysm::y,pyym::u},{pysm::d,pyym::i},{pysm::d,pyym::u}},//儥
{{pysm::m,pyym::ian},{pysm::w,pyym::en},{pysm::w,pyym::an}},//免
{{pysm::d,pyym::ui},{pysm::r,pyym::ui},{pysm::d,pyym::uo}},//兑
{{pysm::y,pyym::u},{pysm::sh,pyym::u},{pysm::zh,pyym::u}},//兪
{{pysm::n,pyym::ei},{pysm::n,pyym::a},{pysm::r,pyym::ui}},//内
{{pysm::r,pyym::an},{pysm::n,pyym::an},{pysm::d,pyym::an}},//冉
{{pysm::h,pyym::ua},{pysm::g,pyym::uo},{pysm::h,pyym::uai}},//划
{{pysm::b,pyym::o},{pysm::b,pyym::ao},{pysm::p,pyym::u}},//剥
{{pysm::d,pyym::uan},{pysm::t,pyym::uan},{pysm::zh,pyym::i}},//剬
{{pysm::b,pyym::ao},{pysm::p,pyym::ao},{pysm::f,pyym::u}},//包
{{pysm::k,pyym::e},{pysm::nop,pyym::e},{pysm::nop,pyym::an}},//匼
{{pysm::z,pyym::u},{pysm::c,pyym::u},{pysm::c,pyym::ui}},//卒
{{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::sh,pyym::an}},//单
{{pysm::b,pyym::o},{pysm::b,pyym::u},{pysm::p,pyym::u}},//卜
{{pysm::q,pyym::ue},{pysm::j,pyym::iao},{pysm::x,pyym::i}},//卻
{{pysm::y,pyym::an},{pysm::y,pyym::a},{pysm::y,pyym::i}},//厭
{{pysm::c,pyym::an},{pysm::c,pyym::en},{pysm::sh,pyym::en}},//参
{{pysm::j,pyym::u},{pysm::g,pyym::ou},{pysm::q,pyym::u}},//句
{{pysm::t,pyym::ai},{pysm::y,pyym::i},{pysm::s,pyym::i}},//台
{{pysm::ch,pyym::i},{pysm::h,pyym::ua},{pysm::nop,pyym::e}},//叱
{{pysm::t,pyym::an},{pysm::y,pyym::i},{pysm::y,pyym::ou}},//叹
{{pysm::c,pyym::un},{pysm::d,pyym::ou},{pysm::y,pyym::ing}},//吋
{{pysm::x,pyym::ia},{pysm::h,pyym::e},{pysm::h,pyym::a}},//吓
{{pysm::j,pyym::ie},{pysm::g,pyym::e},{pysm::x,pyym::ie}},//吤
{{pysm::t,pyym::ing},{pysm::y,pyym::in},{pysm::y,pyym::i}},//听
{{pysm::zh,pyym::i},{pysm::z,pyym::i},{pysm::q,pyym::i}},//吱
{{pysm::x,pyym::ue},{pysm::ch,pyym::uo},{pysm::j,pyym::ue}},//吷
{{pysm::h,pyym::ong},{pysm::nop,pyym::ou},{pysm::h,pyym::ou}},//吽
{{pysm::w,pyym::u},{pysm::y,pyym::u},{pysm::y,pyym::a}},//吾
{{pysm::d,pyym::ai},{pysm::b,pyym::ao},{pysm::nop,pyym::ai}},//呆
{{pysm::g,pyym::ao},{pysm::j,pyym::u},{pysm::g,pyym::u}},//告
{{pysm::n,pyym::a},{pysm::n,pyym::e},{pysm::n,pyym::uo}},//呐
{{pysm::n,pyym::ao},{pysm::n,pyym::a},{pysm::n,pyym::u}},//呶
{{pysm::g,pyym::a},{pysm::x,pyym::ia},{pysm::j,pyym::ia}},//呷
{{pysm::g,pyym::an},{pysm::h,pyym::an},{pysm::x,pyym::ian}},//咁
{{pysm::z,pyym::a},{pysm::z,pyym::e},{pysm::zh,pyym::a}},//咋
{{pysm::h,pyym::e},{pysm::h,pyym::u},{pysm::h,pyym::uo}},//和
{{pysm::k,pyym::a},{pysm::g,pyym::a},{pysm::j,pyym::ia}},//咖
{{pysm::x,pyym::i},{pysm::d,pyym::ie},{pysm::zh,pyym::i}},//咥
{{pysm::m,pyym::i},{pysm::m,pyym::ie},{pysm::m,pyym::ai}},//咪
{{pysm::j,pyym::i},{pysm::x,pyym::i},{pysm::q,pyym::ia}},//咭
{{pysm::zh,pyym::ou},{pysm::zh,pyym::u},{pysm::r,pyym::u}},//咮
{{pysm::k,pyym::e},{pysm::h,pyym::ai},{pysm::g,pyym::ai}},//咳
{{pysm::nop,pyym::e},{pysm::nop,pyym::an},{pysm::n,pyym::n}},//咹
{{pysm::x,pyym::iu},{pysm::x,pyym::u},{pysm::x,pyym::iao}},//咻
{{pysm::y,pyym::an},{pysm::y,pyym::e},{pysm::y,pyym::uan}},//咽
{{pysm::w,pyym::a},{pysm::g,pyym::ui},{pysm::h,pyym::ua}},//哇
{{pysm::g,pyym::en},{pysm::h,pyym::en},{pysm::n,pyym::n}},//哏
{{pysm::ch,pyym::i},{pysm::x,pyym::ia},{pysm::h,pyym::e}},//哧
{{pysm::sh,pyym::ao},{pysm::s,pyym::ao},{pysm::x,pyym::iao}},//哨
{{pysm::l,pyym::i},{pysm::m,pyym::ai},{pysm::y,pyym::ing}},//哩
{{pysm::x,pyym::ian},{pysm::y,pyym::an},{pysm::d,pyym::an}},//唌
{{pysm::nop,pyym::an},{pysm::n,pyym::g},{pysm::n,pyym::n}},//唵
{{pysm::d,pyym::i},{pysm::sh,pyym::i},{pysm::zh,pyym::ai}},//啇
{{pysm::h,pyym::eng},{pysm::nop,pyym::e},{pysm::z,pyym::a}},//啈
{{pysm::l,pyym::in},{pysm::l,pyym::an},{pysm::l,pyym::en}},//啉
{{pysm::ch,pyym::uai},{pysm::ch,pyym::uo},{pysm::zh,pyym::uo}},//啜
{{pysm::h,pyym::an},{pysm::k,pyym::an},{pysm::j,pyym::ian}},//喊
{{pysm::d,pyym::ie},{pysm::zh,pyym::a},{pysm::q,pyym::ie}},//喋
{{pysm::nop,pyym::o},{pysm::w,pyym::o},{pysm::w,pyym::u}},//喔
{{pysm::h,pyym::e},{pysm::y,pyym::e},{pysm::k,pyym::ai}},//喝
{{pysm::c,pyym::an},{pysm::s,pyym::un},{pysm::q,pyym::i}},//喰
{{pysm::h,pyym::e},{pysm::x,pyym::iao},{pysm::h,pyym::u}},//嗃
{{pysm::nop,pyym::a},{pysm::sh,pyym::a},{pysm::x,pyym::ia}},//嗄
{{pysm::nop,pyym::ai},{pysm::y,pyym::i},{pysm::w,pyym::o}},//嗌
{{pysm::k,pyym::e},{pysm::h,pyym::e},{pysm::x,pyym::ia}},//嗑
{{pysm::p,pyym::ang},{pysm::b,pyym::eng},{pysm::b,pyym::ang}},//嗙
{{pysm::q,pyym::ian},{pysm::x,pyym::ian},{pysm::q,pyym::ie}},//嗛
{{pysm::s,pyym::ou},{pysm::sh,pyym::uo},{pysm::sh,pyym::u}},//嗽
{{pysm::q,pyym::i},{pysm::z,pyym::u},{pysm::z,pyym::a}},//嘁
{{pysm::sh,pyym::an},{pysm::c,pyym::an},{pysm::sh,pyym::en}},//嘇
{{pysm::nop,pyym::ou},{pysm::x,pyym::u},{pysm::ch,pyym::u}},//嘔
{{pysm::d,pyym::e},{pysm::d,pyym::ei},{pysm::d,pyym::ai}},//嘚
{{pysm::l,pyym::ao},{pysm::ch,pyym::ao},{pysm::x,pyym::iao}},//嘮
{{pysm::f,pyym::u},{pysm::w,pyym::u},{pysm::m,pyym::m}},//嘸
{{pysm::ch,pyym::u},{pysm::x,pyym::u},{pysm::sh,pyym::ou}},//嘼
{{pysm::h,pyym::ei},{pysm::m,pyym::o},{pysm::m,pyym::u}},//嘿
{{pysm::nop,pyym::e},{pysm::w,pyym::u},{pysm::w,pyym::o}},//噁
{{pysm::c,pyym::u},{pysm::z,pyym::a},{pysm::h,pyym::e}},//噈
{{pysm::y,pyym::e},{pysm::y,pyym::i},{pysm::sh,pyym::a}},//噎
{{pysm::nop,pyym::o},{pysm::y,pyym::u},{pysm::nop,pyym::ao}},//噢
{{pysm::j,pyym::iao},{pysm::q,pyym::iao},{pysm::ch,pyym::i}},//噭
{{pysm::h,pyym::m},{pysm::x,pyym::in},{pysm::h,pyym::en}},//噷
{{pysm::h,pyym::uo},{pysm::w,pyym::o},{pysm::nop,pyym::o}},//嚄
{{pysm::p,pyym::i},{pysm::x,pyym::i},{pysm::x,pyym::iu}},//嚊
{{pysm::j,pyym::i},{pysm::j,pyym::ie},{pysm::zh,pyym::ai}},//嚌
{{pysm::b,pyym::o},{pysm::p,pyym::ao},{pysm::b,pyym::ao}},//嚗
{{pysm::m,pyym::e},{pysm::m,pyym::ei},{pysm::m,pyym::a}},//嚜
{{pysm::c,pyym::a},{pysm::zh,pyym::a},{pysm::z,pyym::a}},//囃
{{pysm::z,pyym::a},{pysm::z,pyym::an},{pysm::c,pyym::an}},//囋
{{pysm::j,pyym::ian},{pysm::n,pyym::an},{pysm::y,pyym::ue}},//囝
{{pysm::t,pyym::u},{pysm::d,pyym::u},{pysm::ch,pyym::a}},//土
{{pysm::w,pyym::ei},{pysm::x,pyym::u},{pysm::y,pyym::u}},//圩
{{pysm::y,pyym::u},{pysm::t,pyym::uo},{pysm::zh,pyym::un}},//圫
{{pysm::h,pyym::uai},{pysm::p,pyym::i},{pysm::p,pyym::ei}},//坏
{{pysm::n,pyym::ian},{pysm::d,pyym::ian},{pysm::n,pyym::ie}},//埝
{{pysm::y,pyym::a},{pysm::nop,pyym::e},{pysm::w,pyym::u}},//埡
{{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::b,pyym::ei}},//埤
{{pysm::ch,pyym::ong},{pysm::t,pyym::ang},{pysm::sh,pyym::ang}},//埫
{{pysm::p,pyym::ei},{pysm::p,pyym::ou},{pysm::p,pyym::i}},//培
{{pysm::zh,pyym::un},{pysm::d,pyym::ui},{pysm::g,pyym::uo}},//埻
{{pysm::p,pyym::eng},{pysm::b,pyym::eng},{pysm::p,pyym::ing}},//堋
{{pysm::b,pyym::ao},{pysm::b,pyym::u},{pysm::p,pyym::u}},//堡
{{pysm::m,pyym::ao},{pysm::m,pyym::ou},{pysm::w,pyym::u}},//堥
{{pysm::y,pyym::e},{pysm::nop,pyym::e},{pysm::nop,pyym::ai}},//堨
{{pysm::ch,pyym::ang},{pysm::sh,pyym::ang},{pysm::d,pyym::ang}},//場
{{pysm::j,pyym::ian},{pysm::k,pyym::an},{pysm::x,pyym::ian}},//堿
{{pysm::t,pyym::ian},{pysm::ch,pyym::en},{pysm::zh,pyym::en}},//填
{{pysm::x,pyym::ue},{pysm::j,pyym::ue},{pysm::b,pyym::o}},//壆
{{pysm::t,pyym::an},{pysm::sh,pyym::an},{pysm::d,pyym::an}},//壇
{{pysm::d,pyym::a},{pysm::d,pyym::ai},{pysm::t,pyym::ai}},//大
{{pysm::y,pyym::ao},{pysm::w,pyym::o},{pysm::w,pyym::ai}},//夭
{{pysm::zh,pyym::a},{pysm::sh,pyym::e},{pysm::ch,pyym::i}},//奓
{{pysm::h,pyym::a},{pysm::p,pyym::o},{pysm::t,pyym::ai}},//奤
{{pysm::nop,pyym::ao},{pysm::y,pyym::u},{pysm::y,pyym::ou}},//奥
{{pysm::t,pyym::a},{pysm::j,pyym::ie},{pysm::ch,pyym::i}},//她
{{pysm::f,pyym::ou},{pysm::p,pyym::ei},{pysm::p,pyym::i}},//妚
{{pysm::x,pyym::ian},{pysm::x,pyym::uan},{pysm::x,pyym::u}},//妶
{{pysm::sh,pyym::an},{pysm::x,pyym::ian},{pysm::p,pyym::an}},//姍
{{pysm::y,pyym::ao},{pysm::t,pyym::iao},{pysm::t,pyym::ao}},//姚
{{pysm::sh,pyym::i},{pysm::t,pyym::i},{pysm::j,pyym::i}},//姼
{{pysm::m,pyym::ei},{pysm::m,pyym::u},{pysm::w,pyym::u}},//娒
{{pysm::ch,pyym::uo},{pysm::c,pyym::u},{pysm::l,pyym::ai}},//娕
{{pysm::m,pyym::ian},{pysm::w,pyym::an},{pysm::w,pyym::en}},//娩
{{pysm::q,pyym::u},{pysm::j,pyym::u},{pysm::sh,pyym::u}},//娶
{{pysm::l,pyym::ou},{pysm::l,pyym::v},{pysm::l,pyym::ei}},//婁
{{pysm::p,pyym::ou},{pysm::p,pyym::ei},{pysm::b,pyym::u}},//婄
{{pysm::r,pyym::ui},{pysm::w,pyym::o},{pysm::n,pyym::ei}},//婑
{{pysm::w,pyym::u},{pysm::m,pyym::ou},{pysm::m,pyym::u}},//婺
{{pysm::r,pyym::uan},{pysm::n,pyym::en},{pysm::n,pyym::un}},//媆
{{pysm::nop,pyym::an},{pysm::y,pyym::an},{pysm::nop,pyym::e}},//媕
{{pysm::t,pyym::uo},{pysm::d,pyym::uo},{pysm::n,pyym::uo}},//媠
{{pysm::nop,pyym::ao},{pysm::y,pyym::un},{pysm::w,pyym::o}},//媪
{{pysm::x,pyym::ian},{pysm::y,pyym::an},{pysm::j,pyym::in}},//嬐
{{pysm::h,pyym::uan},{pysm::x,pyym::uan},{pysm::q,pyym::iong}},//嬛
{{pysm::n,pyym::ai},{pysm::nop,pyym::er},{pysm::n,pyym::i}},//嬭
{{pysm::zh,pyym::u},{pysm::sh,pyym::u},{pysm::ch,pyym::uo}},//孎
{{pysm::x,pyym::ue},{pysm::h,pyym::ua},{pysm::j,pyym::iao}},//學
{{pysm::t,pyym::a},{pysm::t,pyym::uo},{pysm::y,pyym::i}},//它
{{pysm::zh,pyym::ai},{pysm::ch,pyym::e},{pysm::d,pyym::u}},//宅
{{pysm::j,pyym::ia},{pysm::j,pyym::ie},{pysm::g,pyym::u}},//家
{{pysm::s,pyym::u},{pysm::x,pyym::iu},{pysm::q,pyym::i}},//宿
{{pysm::j,pyym::u},{pysm::l,pyym::v},{pysm::l,pyym::ou}},//寠
{{pysm::zh,pyym::ai},{pysm::s,pyym::e},{pysm::q,pyym::ian}},//寨
{{pysm::f,pyym::u},{pysm::b,pyym::u},{pysm::p,pyym::o}},//尃
{{pysm::sh,pyym::e},{pysm::y,pyym::e},{pysm::y,pyym::i}},//射
{{pysm::j,pyym::iang},{pysm::q,pyym::iang},{pysm::y,pyym::ang}},//將
{{pysm::zh,pyym::uan},{pysm::t,pyym::uan},{pysm::sh,pyym::uan}},//專
{{pysm::w,pyym::ei},{pysm::y,pyym::u},{pysm::y,pyym::un}},//尉
{{pysm::m,pyym::ang},{pysm::m,pyym::eng},{pysm::p,pyym::ang}},//尨
{{pysm::n,pyym::i},{pysm::p,pyym::o},{pysm::j,pyym::i}},//屰
{{pysm::q,pyym::u},{pysm::j,pyym::u},{pysm::z,pyym::u}},//岨
{{pysm::q,pyym::ian},{pysm::h,pyym::an},{pysm::k,pyym::an}},//嵌
{{pysm::g,pyym::ui},{pysm::x,pyym::i},{pysm::j,pyym::uan}},//巂
{{pysm::r,pyym::ong},{pysm::h,pyym::ong},{pysm::y,pyym::ing}},//巆
{{pysm::x,pyym::un},{pysm::y,pyym::an},{pysm::sh,pyym::un}},//巡
{{pysm::sh,pyym::an},{pysm::sh,pyym::en},{pysm::q,pyym::iao}},//幓
{{pysm::g,pyym::an},{pysm::h,pyym::an},{pysm::g,pyym::uan}},//幹
{{pysm::g,pyym::uang},{pysm::y,pyym::an},{pysm::nop,pyym::an}},//广
{{pysm::b,pyym::ai},{pysm::x,pyym::in},{pysm::t,pyym::ing}},//庍
{{pysm::d,pyym::u},{pysm::d,pyym::uo},{pysm::zh,pyym::ai}},//度
{{pysm::nop,pyym::an},{pysm::y,pyym::an},{pysm::nop,pyym::e}},//庵
{{pysm::sh,pyym::u},{pysm::zh,pyym::u},{pysm::zh,pyym::e}},//庶
{{pysm::g,pyym::ui},{pysm::w,pyym::ei},{pysm::h,pyym::ui}},//廆
{{pysm::d,pyym::i},{pysm::t,pyym::i},{pysm::t,pyym::ui}},//弟
{{pysm::p,pyym::eng},{pysm::p,pyym::ang},{pysm::b,pyym::ang}},//彭
{{pysm::zh,pyym::eng},{pysm::zh,pyym::i},{pysm::ch,pyym::eng}},//徵
{{pysm::t,pyym::e},{pysm::t,pyym::ui},{pysm::t,pyym::ei}},//忒
{{pysm::t,pyym::un},{pysm::zh,pyym::un},{pysm::d,pyym::un}},//忳
{{pysm::t,pyym::u},{pysm::d,pyym::ie},{pysm::t,pyym::ui}},//怢
{{pysm::f,pyym::u},{pysm::f,pyym::ei},{pysm::b,pyym::ei}},//怫
{{pysm::n,pyym::en},{pysm::r,pyym::en},{pysm::n,pyym::in}},//恁
{{pysm::x,pyym::i},{pysm::q,pyym::i},{pysm::x,pyym::u}},//恓
{{pysm::ch,pyym::ou},{pysm::q,pyym::iu},{pysm::d,pyym::ao}},//惆
{{pysm::y,pyym::uan},{pysm::w,pyym::an},{pysm::y,pyym::u}},//惌
{{pysm::nop,pyym::e},{pysm::w,pyym::u},{pysm::h,pyym::u}},//惡
{{pysm::zh,pyym::ui},{pysm::ch,pyym::uan},{pysm::g,pyym::ua}},//惴
{{pysm::ch,pyym::ou},{pysm::q,pyym::iao},{pysm::j,pyym::iu}},//愁
{{pysm::k,pyym::ai},{pysm::q,pyym::i},{pysm::h,pyym::e}},//愒
{{pysm::ch,pyym::en},{pysm::d,pyym::an},{pysm::x,pyym::in}},//愖
{{pysm::k,pyym::ai},{pysm::x,pyym::i},{pysm::q,pyym::i}},//愾
{{pysm::q,pyym::ian},{pysm::q,pyym::ie},{pysm::x,pyym::ian}},//慊
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng},{pysm::d,pyym::eng}},//憕
{{pysm::d,pyym::an},{pysm::d,pyym::a},{pysm::ch,pyym::an}},//憚
{{pysm::d,pyym::ui},{pysm::d,pyym::un},{pysm::t,pyym::un}},//憞
{{pysm::n,pyym::ao},{pysm::n,pyym::ong},{pysm::n,pyym::ang}},//憹
{{pysm::l,pyym::e},{pysm::l,pyym::i},{pysm::c,pyym::ai}},//扐
{{pysm::ch,pyym::a},{pysm::ch,pyym::ai},{pysm::zh,pyym::a}},//扠
{{pysm::t,pyym::uo},{pysm::y,pyym::i},{pysm::ch,pyym::i}},//扡
{{pysm::n,pyym::iu},{pysm::ch,pyym::ou},{pysm::zh,pyym::ou}},//扭
{{pysm::b,pyym::an},{pysm::f,pyym::en},{pysm::h,pyym::uo}},//扮
{{pysm::x,pyym::i},{pysm::ch,pyym::a},{pysm::q,pyym::i}},//扱
{{pysm::zh,pyym::i},{pysm::s,pyym::un},{pysm::k,pyym::an}},//扻
{{pysm::zh,pyym::e},{pysm::sh,pyym::e},{pysm::t,pyym::i}},//折
{{pysm::b,pyym::u},{pysm::p,pyym::u},{pysm::b,pyym::a}},//抪
{{pysm::b,pyym::ao},{pysm::p,pyym::ao},{pysm::p,pyym::ou}},//抱
{{pysm::d,pyym::i},{pysm::zh,pyym::i},{pysm::q,pyym::i}},//抵
{{pysm::y,pyym::a},{pysm::x,pyym::ia},{pysm::j,pyym::ia}},//押
{{pysm::t,pyym::uo},{pysm::t,pyym::a},{pysm::zh,pyym::i}},//拓
{{pysm::nop,pyym::ao},{pysm::n,pyym::iu},{pysm::y,pyym::u}},//拗
{{pysm::zh,pyym::ao},{pysm::q,pyym::iao},{pysm::sh,pyym::ao}},//招
{{pysm::y,pyym::i},{pysm::ch,pyym::i},{pysm::h,pyym::ai}},//拸
{{pysm::c,pyym::e},{pysm::s,pyym::e},{pysm::ch,pyym::uo}},//拺
{{pysm::sh,pyym::i},{pysm::sh,pyym::e},{pysm::j,pyym::ie}},//拾
{{pysm::k,pyym::ua},{pysm::k,pyym::u},{pysm::k,pyym::ou}},//挎
{{pysm::n,pyym::a},{pysm::r,pyym::u},{pysm::n,pyym::u}},//挐
{{pysm::t,pyym::iao},{pysm::t,pyym::ao},{pysm::d,pyym::iao}},//挑
{{pysm::s,pyym::a},{pysm::sh,pyym::a},{pysm::s,pyym::uo}},//挱
{{pysm::s,pyym::a},{pysm::s,pyym::uo},{pysm::sh,pyym::a}},//挲
{{pysm::j,pyym::iu},{pysm::j,pyym::u},{pysm::q,pyym::iu}},//捄
{{pysm::t,pyym::u},{pysm::sh,pyym::u},{pysm::ch,pyym::a}},//捈
{{pysm::h,pyym::an},{pysm::x,pyym::ian},{pysm::g,pyym::an}},//捍
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao},{pysm::q,pyym::iao}},//捎
{{pysm::sh,pyym::u},{pysm::s,pyym::ou},{pysm::s,pyym::ong}},//捒
{{pysm::b,pyym::u},{pysm::p,pyym::u},{pysm::zh,pyym::i}},//捗
{{pysm::t,pyym::uo},{pysm::sh,pyym::ui},{pysm::y,pyym::an}},//捝
{{pysm::b,pyym::ai},{pysm::b,pyym::a},{pysm::b,pyym::i}},//捭
{{pysm::ch,pyym::en},{pysm::t,pyym::ian},{pysm::n,pyym::ian}},//捵
{{pysm::j,pyym::ie},{pysm::q,pyym::ie},{pysm::ch,pyym::a}},//捷
{{pysm::p,pyym::ou},{pysm::f,pyym::u},{pysm::p,pyym::ei}},//掊
{{pysm::c,pyym::uo},{pysm::z,pyym::e},{pysm::c,pyym::i}},//措
{{pysm::zh,pyym::ou},{pysm::z,pyym::ou},{pysm::ch,pyym::ou}},//掫
{{pysm::c,pyym::an},{pysm::ch,pyym::an},{pysm::sh,pyym::an}},//掺
{{pysm::h,pyym::ong},{pysm::x,pyym::uan},{pysm::j,pyym::u}},//揈
{{pysm::nop,pyym::an},{pysm::y,pyym::an},{pysm::y,pyym::e}},//揞
{{pysm::j,pyym::ie},{pysm::q,pyym::i},{pysm::h,pyym::e}},//揭
{{pysm::x,pyym::iao},{pysm::sh,pyym::uo},{pysm::x,pyym::ian}},//揱
{{pysm::d,pyym::ie},{pysm::sh,pyym::e},{pysm::y,pyym::e}},//揲
{{pysm::ch,pyym::ou},{pysm::z,pyym::ou},{pysm::zh,pyym::u}},//搊
{{pysm::ch,pyym::uai},{pysm::ch,pyym::i},{pysm::y,pyym::i}},//搋
{{pysm::b,pyym::ang},{pysm::p,pyym::eng},{pysm::b,pyym::eng}},//搒
{{pysm::n,pyym::u},{pysm::n,pyym::uo},{pysm::n,pyym::ou}},//搙
{{pysm::l,pyym::a},{pysm::x,pyym::ie},{pysm::x,pyym::ian}},//搚
{{pysm::s,pyym::ou},{pysm::x,pyym::iao},{pysm::sh,pyym::ao}},//搜
{{pysm::g,pyym::ao},{pysm::q,pyym::iao},{pysm::k,pyym::ao}},//搞
{{pysm::p,pyym::an},{pysm::b,pyym::an},{pysm::p,pyym::o}},//搫
{{pysm::h,pyym::ua},{pysm::x,pyym::ia},{pysm::q,pyym::ia}},//搳
{{pysm::s,pyym::a},{pysm::sh,pyym::ai},{pysm::sh,pyym::a}},//摋
{{pysm::d,pyym::i},{pysm::t,pyym::u},{pysm::zh,pyym::i}},//摕
{{pysm::c,pyym::ui},{pysm::z,pyym::ui},{pysm::c,pyym::uo}},//摧
{{pysm::m,pyym::o},{pysm::m,pyym::a},{pysm::m,pyym::i}},//摩
{{pysm::sh,pyym::e},{pysm::s,pyym::u},{pysm::m,pyym::i}},//摵
{{pysm::zh,pyym::e},{pysm::l,pyym::a},{pysm::x,pyym::ie}},//摺
{{pysm::b,pyym::iao},{pysm::p,pyym::iao},{pysm::p,pyym::ao}},//摽
{{pysm::z,pyym::an},{pysm::z,pyym::en},{pysm::q,pyym::ian}},//撍
{{pysm::n,pyym::ao},{pysm::x,pyym::iao},{pysm::r,pyym::ao}},//撓
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::x,pyym::in}},//撢
{{pysm::f,pyym::u},{pysm::x,pyym::iao},{pysm::s,pyym::ou}},//撨
{{pysm::zh,pyym::uan},{pysm::x,pyym::uan},{pysm::s,pyym::uan}},//撰
{{pysm::q,pyym::iao},{pysm::y,pyym::ao},{pysm::j,pyym::i}},//撽
{{pysm::z,pyym::e},{pysm::zh,pyym::ai},{pysm::y,pyym::i}},//擇
{{pysm::h,pyym::uan},{pysm::j,pyym::uan},{pysm::x,pyym::uan}},//擐
{{pysm::w,pyym::o},{pysm::h,pyym::uo},{pysm::h,pyym::u}},//擭
{{pysm::k,pyym::uo},{pysm::t,pyym::ang},{pysm::g,pyym::uang}},//擴
{{pysm::l,pyym::ve},{pysm::l,pyym::i},{pysm::y,pyym::ue}},//擽
{{pysm::t,pyym::i},{pysm::zh,pyym::i},{pysm::zh,pyym::ai}},//擿
{{pysm::r,pyym::ang},{pysm::n,pyym::ing},{pysm::x,pyym::iang}},//攘
{{pysm::z,pyym::an},{pysm::c,pyym::uan},{pysm::z,pyym::uan}},//攢
{{pysm::ch,pyym::ang},{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//敞
{{pysm::y,pyym::i},{pysm::d,pyym::u},{pysm::t,pyym::u}},//斁
{{pysm::ch,pyym::i},{pysm::ch,pyym::e},{pysm::zh,pyym::e}},//斥
{{pysm::m,pyym::ei},{pysm::w,pyym::en},{pysm::m,pyym::o}},//昧
{{pysm::ch,pyym::eng},{pysm::sh,pyym::eng},{pysm::j,pyym::ing}},//晟
{{pysm::b,pyym::ao},{pysm::p,pyym::u},{pysm::b,pyym::o}},//暴
{{pysm::c,pyym::an},{pysm::q,pyym::ian},{pysm::j,pyym::ian}},//朁
{{pysm::h,pyym::ui},{pysm::k,pyym::uai},{pysm::k,pyym::uo}},//會
{{pysm::f,pyym::u},{pysm::b,pyym::i},{pysm::b,pyym::o}},//服
{{pysm::q,pyym::u},{pysm::x,pyym::u},{pysm::ch,pyym::un}},//朐
{{pysm::ch,pyym::ao},{pysm::zh,pyym::ao},{pysm::zh,pyym::u}},//朝
{{pysm::p,pyym::u},{pysm::p,pyym::iao},{pysm::p,pyym::o}},//朴
{{pysm::d,pyym::ao},{pysm::m,pyym::u},{pysm::t,pyym::iao}},//朷
{{pysm::ch,pyym::eng},{pysm::zh,pyym::eng},{pysm::t,pyym::ing}},//朾
{{pysm::s,pyym::i},{pysm::zh,pyym::i},{pysm::x,pyym::i}},//杫
{{pysm::g,pyym::uo},{pysm::l,pyym::uo},{pysm::g,pyym::uan}},//果
{{pysm::t,pyym::ai},{pysm::s,pyym::i},{pysm::c,pyym::i}},//枱
{{pysm::g,pyym::ou},{pysm::j,pyym::u},{pysm::q,pyym::u}},//枸
{{pysm::y,pyym::i},{pysm::d,pyym::uo},{pysm::l,pyym::i}},//柂
{{pysm::zh,pyym::a},{pysm::z,pyym::uo},{pysm::z,pyym::e}},//柞
{{pysm::n,pyym::ing},{pysm::ch,pyym::u},{pysm::zh,pyym::u}},//柠
{{pysm::ch,pyym::a},{pysm::zh,pyym::a},{pysm::ch,pyym::ai}},//查
{{pysm::d,pyym::uo},{pysm::z,pyym::uo},{pysm::w,pyym::u}},//柮
{{pysm::zh,pyym::a},{pysm::sh,pyym::an},{pysm::c,pyym::e}},//栅
{{pysm::g,pyym::ua},{pysm::t,pyym::ian},{pysm::k,pyym::uo}},//栝
{{pysm::x,pyym::iao},{pysm::j,pyym::iao},{pysm::q,pyym::iao}},//校
{{pysm::g,pyym::e},{pysm::l,pyym::uo},{pysm::h,pyym::e}},//格
{{pysm::t,pyym::ao},{pysm::t,pyym::iao},{pysm::zh,pyym::ao}},//桃
{{pysm::j,pyym::u},{pysm::j,pyym::ie},{pysm::x,pyym::ie}},//桔
{{pysm::x,pyym::uan},{pysm::j,pyym::uan},{pysm::x,pyym::ie}},//梋
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao},{pysm::s,pyym::ao}},//梢
{{pysm::c,pyym::en},{pysm::ch,pyym::en},{pysm::q,pyym::in}},//梣
{{pysm::l,pyym::i},{pysm::s,pyym::i},{pysm::q,pyym::i}},//梩
{{pysm::zh,pyym::uo},{pysm::t,pyym::uo},{pysm::r,pyym::ui}},//棁
{{pysm::g,pyym::un},{pysm::h,pyym::un},{pysm::nop,pyym::ao}},//棍
{{pysm::p,pyym::ai},{pysm::b,pyym::ei},{pysm::p,pyym::ei}},//棑
{{pysm::d,pyym::i},{pysm::t,pyym::i},{pysm::d,pyym::ai}},//棣
{{pysm::l,pyym::eng},{pysm::l,pyym::ing},{pysm::ch,pyym::eng}},//棱
{{pysm::ch,pyym::ou},{pysm::zh,pyym::ou},{pysm::d,pyym::iao}},//椆
{{pysm::h,pyym::uo},{pysm::g,pyym::uo},{pysm::k,pyym::ua}},//楇
{{pysm::d,pyym::un},{pysm::sh,pyym::un},{pysm::ch,pyym::un}},//楯
{{pysm::t,pyym::i},{pysm::d,pyym::i},{pysm::sh,pyym::i}},//楴
{{pysm::g,pyym::ai},{pysm::g,pyym::ui},{pysm::j,pyym::ie}},//概
{{pysm::ch,pyym::ui},{pysm::zh,pyym::ui},{pysm::d,pyym::ui}},//槌
{{pysm::q,pyym::ian},{pysm::x,pyym::ian},{pysm::l,pyym::ian}},//槏
{{pysm::t,pyym::uan},{pysm::sh,pyym::uan},{pysm::q,pyym::uan}},//槫
{{pysm::q,pyym::i},{pysm::z,pyym::u},{pysm::s,pyym::e}},//槭
{{pysm::n,pyym::ie},{pysm::x,pyym::ie},{pysm::y,pyym::i}},//槷
{{pysm::d,pyym::i},{pysm::zh,pyym::i},{pysm::zh,pyym::e}},//樀
{{pysm::h,pyym::eng},{pysm::g,pyym::uang},{pysm::h,pyym::uang}},//横
{{pysm::t,pyym::uo},{pysm::d,pyym::u},{pysm::l,pyym::uo}},//橐
{{pysm::ch,pyym::eng},{pysm::d,pyym::eng},{pysm::ch,pyym::en}},//橙
{{pysm::s,pyym::u},{pysm::x,pyym::iao},{pysm::q,pyym::iu}},//橚
{{pysm::d,pyym::ian},{pysm::t,pyym::an},{pysm::x,pyym::in}},//橝
{{pysm::sh,pyym::u},{pysm::q,pyym::iao},{pysm::s,pyym::ao}},//橾
{{pysm::g,pyym::ui},{pysm::k,pyym::uai},{pysm::h,pyym::ui}},//檜
{{pysm::zh,pyym::ai},{pysm::sh,pyym::i},{pysm::t,pyym::u}},//檡
{{pysm::t,pyym::ao},{pysm::ch,pyym::ou},{pysm::d,pyym::ao}},//檮
{{pysm::n,pyym::ou},{pysm::r,pyym::uan},{pysm::r,pyym::u}},//檽
{{pysm::l,pyym::i},{pysm::l,pyym::uo},{pysm::y,pyym::ue}},//櫟
{{pysm::ch,pyym::en},{pysm::q,pyym::in},{pysm::g,pyym::uan}},//櫬
{{pysm::x,pyym::iao},{pysm::q,pyym::iu},{pysm::x,pyym::iu}},//櫹
{{pysm::y,pyym::i},{pysm::h,pyym::uan},{pysm::y,pyym::u}},//欥
{{pysm::q,pyym::ian},{pysm::h,pyym::an},{pysm::x,pyym::ian}},//欦
{{pysm::ch,pyym::u},{pysm::x,pyym::i},{pysm::q,pyym::u}},//欪
{{pysm::k,pyym::an},{pysm::q,pyym::ian},{pysm::d,pyym::an}},//欿
{{pysm::k,pyym::an},{pysm::k,pyym::e},{pysm::q,pyym::ian}},//歁
{{pysm::sh,pyym::e},{pysm::x,pyym::i},{pysm::x,pyym::ie}},//歙
{{pysm::f,pyym::ou},{pysm::y,pyym::e},{pysm::b,pyym::o}},//殕
{{pysm::q,pyym::ing},{pysm::k,pyym::eng},{pysm::sh,pyym::eng}},//殸
{{pysm::nop,pyym::ou},{pysm::k,pyym::ou},{pysm::q,pyym::u}},//毆
{{pysm::c,pyym::ui},{pysm::q,pyym::iao},{pysm::x,pyym::ia}},//毳
{{pysm::h,pyym::e},{pysm::k,pyym::e},{pysm::d,pyym::a}},//毼
{{pysm::sh,pyym::i},{pysm::zh,pyym::i},{pysm::j,pyym::ing}},//氏
{{pysm::g,pyym::ui},{pysm::j,pyym::iu},{pysm::q,pyym::iu}},//氿
{{pysm::zh,pyym::i},{pysm::x,pyym::ie},{pysm::sh,pyym::i}},//汁
{{pysm::w,pyym::u},{pysm::y,pyym::u},{pysm::w,pyym::a}},//汙
{{pysm::ch,pyym::i},{pysm::t,pyym::uo},{pysm::ch,pyym::e}},//池
{{pysm::g,pyym::u},{pysm::y,pyym::u},{pysm::h,pyym::u}},//汩
{{pysm::g,pyym::an},{pysm::h,pyym::an},{pysm::c,pyym::en}},//汵
{{pysm::w,pyym::en},{pysm::m,pyym::in},{pysm::m,pyym::en}},//汶
{{pysm::j,pyym::ue},{pysm::q,pyym::ue},{pysm::x,pyym::ue}},//決
{{pysm::q,pyym::i},{pysm::g,pyym::ai},{pysm::y,pyym::i}},//汽
{{pysm::sh,pyym::en},{pysm::ch,pyym::en},{pysm::t,pyym::an}},//沈
{{pysm::m,pyym::i},{pysm::w,pyym::u},{pysm::f,pyym::u}},//沕
{{pysm::m,pyym::ei},{pysm::m,pyym::o},{pysm::m,pyym::e}},//没
{{pysm::j,pyym::u},{pysm::j,pyym::ian},{pysm::z,pyym::u}},//沮
{{pysm::t,pyym::uo},{pysm::d,pyym::uo},{pysm::ch,pyym::i}},//沱
{{pysm::y,pyym::i},{pysm::ch,pyym::i},{pysm::sh,pyym::i}},//沶
{{pysm::f,pyym::an},{pysm::f,pyym::eng},{pysm::f,pyym::a}},//泛
{{pysm::b,pyym::o},{pysm::b,pyym::ei},{pysm::b,pyym::i}},//波
{{pysm::q,pyym::i},{pysm::l,pyym::i},{pysm::s,pyym::e}},//泣
{{pysm::n,pyym::i},{pysm::n,pyym::ie},{pysm::n,pyym::ing}},//泥
{{pysm::b,pyym::eng},{pysm::p,pyym::in},{pysm::l,pyym::iu}},//泵
{{pysm::y,pyym::in},{pysm::y,pyym::an},{pysm::y,pyym::e}},//洇
{{pysm::s,pyym::e},{pysm::q,pyym::i},{pysm::z,pyym::i}},//洓
{{pysm::nop,pyym::an},{pysm::y,pyym::an},{pysm::nop,pyym::e}},//洝
{{pysm::t,pyym::ao},{pysm::y,pyym::ao},{pysm::d,pyym::ao}},//洮
{{pysm::j,pyym::un},{pysm::x,pyym::un},{pysm::c,pyym::un}},//浚
{{pysm::y,pyym::ing},{pysm::ch,pyym::eng},{pysm::zh,pyym::eng}},//浧
{{pysm::h,pyym::ao},{pysm::g,pyym::ao},{pysm::g,pyym::e}},//浩
{{pysm::t,pyym::u},{pysm::ch,pyym::u},{pysm::y,pyym::e}},//涂
{{pysm::x,pyym::ian},{pysm::y,pyym::an},{pysm::d,pyym::ian}},//涎
{{pysm::s,pyym::u},{pysm::s,pyym::ou},{pysm::sh,pyym::u}},//涑
{{pysm::j,pyym::uan},{pysm::y,pyym::uan},{pysm::x,pyym::uan}},//涓
{{pysm::c,pyym::en},{pysm::q,pyym::ian},{pysm::z,pyym::an}},//涔
{{pysm::w,pyym::o},{pysm::y,pyym::uan},{pysm::w,pyym::an}},//涴
{{pysm::d,pyym::an},{pysm::y,pyym::an},{pysm::t,pyym::an}},//淡
{{pysm::y,pyym::in},{pysm::y,pyym::an},{pysm::y,pyym::ao}},//淫
{{pysm::n,pyym::ian},{pysm::sh,pyym::en},{pysm::n,pyym::a}},//淰
{{pysm::h,pyym::un},{pysm::g,pyym::un},{pysm::k,pyym::un}},//混
{{pysm::w,pyym::o},{pysm::nop,pyym::ou},{pysm::w,pyym::u}},//渥
{{pysm::m,pyym::in},{pysm::h,pyym::un},{pysm::m,pyym::ian}},//湣
{{pysm::j,pyym::iao},{pysm::q,pyym::iu},{pysm::j,pyym::iu}},//湫
{{pysm::t,pyym::ang},{pysm::sh,pyym::ang},{pysm::y,pyym::ang}},//湯
{{pysm::g,pyym::ou},{pysm::g,pyym::ang},{pysm::k,pyym::ou}},//溝
{{pysm::n,pyym::i},{pysm::r,pyym::uo},{pysm::n,pyym::iao}},//溺
{{pysm::d,pyym::ian},{pysm::t,pyym::ian},{pysm::zh,pyym::en}},//滇
{{pysm::x,pyym::i},{pysm::x,pyym::ie},{pysm::q,pyym::i}},//滊
{{pysm::z,pyym::i},{pysm::c,pyym::i},{pysm::x,pyym::uan}},//滋
{{pysm::f,pyym::eng},{pysm::p,pyym::eng},{pysm::b,pyym::eng}},//漨
{{pysm::z,pyym::i},{pysm::s,pyym::e},{pysm::q,pyym::i}},//漬
{{pysm::l,pyym::uo},{pysm::t,pyym::a},{pysm::l,pyym::ei}},//漯
{{pysm::j,pyym::ian},{pysm::q,pyym::ian},{pysm::ch,pyym::an}},//漸
{{pysm::l,pyym::iao},{pysm::x,pyym::iao},{pysm::l,pyym::iu}},//漻
{{pysm::p,pyym::i},{pysm::p,pyym::ie},{pysm::p,pyym::iao}},//潎
{{pysm::y,pyym::u},{pysm::j,pyym::ue},{pysm::sh,pyym::u}},//潏
{{pysm::d,pyym::ang},{pysm::x,pyym::iang},{pysm::y,pyym::ang}},//潒
{{pysm::p,pyym::an},{pysm::b,pyym::o},{pysm::f,pyym::an}},//潘
{{pysm::s,pyym::u},{pysm::x,pyym::iao},{pysm::s,pyym::ou}},//潚
{{pysm::t,pyym::ong},{pysm::ch,pyym::ong},{pysm::zh,pyym::ong}},//潼
{{pysm::j,pyym::iao},{pysm::nop,pyym::ao},{pysm::n,pyym::ao}},//澆
{{pysm::w,pyym::an},{pysm::m,pyym::an},{pysm::nop,pyym::ou}},//澫
{{pysm::h,pyym::ui},{pysm::k,pyym::uai},{pysm::h,pyym::ua}},//澮
{{pysm::ch,pyym::an},{pysm::d,pyym::an},{pysm::zh,pyym::an}},//澶
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::sh,pyym::an}},//澹
{{pysm::h,pyym::ui},{pysm::w,pyym::ei},{pysm::h,pyym::uo}},//濊
{{pysm::sh,pyym::i},{pysm::t,pyym::a},{pysm::x,pyym::i}},//濕
{{pysm::nop,pyym::ai},{pysm::k,pyym::ai},{pysm::k,pyym::e}},//濭
{{pysm::zh,pyym::uo},{pysm::sh,pyym::uo},{pysm::zh,pyym::ao}},//濯
{{pysm::l,pyym::uo},{pysm::p,pyym::o},{pysm::l,pyym::i}},//濼
{{pysm::sh,pyym::en},{pysm::ch,pyym::en},{pysm::p,pyym::an}},//瀋
{{pysm::p,pyym::u},{pysm::b,pyym::ao},{pysm::b,pyym::o}},//瀑
{{pysm::zh,pyym::uo},{pysm::z,pyym::e},{pysm::j,pyym::iao}},//灂
{{pysm::t,pyym::an},{pysm::h,pyym::an},{pysm::n,pyym::an}},//灘
{{pysm::g,pyym::ui},{pysm::q,pyym::ue},{pysm::x,pyym::ue}},//炔
{{pysm::t,pyym::un},{pysm::t,pyym::ui},{pysm::j,pyym::un}},//焞
{{pysm::ch,pyym::ao},{pysm::zh,pyym::uo},{pysm::ch,pyym::uo}},//焯
{{pysm::x,pyym::iong},{pysm::y,pyym::ing},{pysm::g,pyym::u}},//焸
{{pysm::h,pyym::e},{pysm::x,pyym::iao},{pysm::k,pyym::ao}},//熇
{{pysm::y,pyym::ing},{pysm::x,pyym::ing},{pysm::j,pyym::iong}},//熒
{{pysm::p,pyym::eng},{pysm::b,pyym::eng},{pysm::f,pyym::eng}},//熢
{{pysm::y,pyym::un},{pysm::y,pyym::u},{pysm::w,pyym::ei}},//熨
{{pysm::t,pyym::an},{pysm::x,pyym::un},{pysm::q,pyym::ian}},//燂
{{pysm::y,pyym::ao},{pysm::sh,pyym::uo},{pysm::sh,pyym::ao}},//燿
{{pysm::sh,pyym::uo},{pysm::l,pyym::uo},{pysm::y,pyym::ue}},//爍
{{pysm::nop,pyym::er},{pysm::m,pyym::i},{pysm::n,pyym::i}},//爾
{{pysm::m,pyym::ou},{pysm::m,pyym::u},{pysm::m,pyym::ao}},//牟
{{pysm::g,pyym::e},{pysm::q,pyym::iu},{pysm::z,pyym::ang}},//牫
{{pysm::nop,pyym::an},{pysm::h,pyym::an},{pysm::j,pyym::ian}},//犴
{{pysm::b,pyym::o},{pysm::p,pyym::ei},{pysm::f,pyym::ei}},//犻
{{pysm::y,pyym::i},{pysm::q,pyym::uan},{pysm::ch,pyym::i}},//狋
{{pysm::h,pyym::uan},{pysm::x,pyym::uan},{pysm::h,pyym::eng}},//狟
{{pysm::j,pyym::i},{pysm::j,pyym::ie},{pysm::k,pyym::uai}},//狤
{{pysm::s,pyym::uan},{pysm::x,pyym::un},{pysm::j,pyym::un}},//狻
{{pysm::l,pyym::ie},{pysm::x,pyym::i},{pysm::q,pyym::ue}},//猎
{{pysm::y,pyym::a},{pysm::j,pyym::ia},{pysm::q,pyym::ie}},//猰
{{pysm::g,pyym::e},{pysm::x,pyym::ie},{pysm::l,pyym::ie}},//獦
{{pysm::x,pyym::ie},{pysm::h,pyym::a},{pysm::j,pyym::ie}},//獬
{{pysm::x,pyym::ian},{pysm::s,pyym::uo},{pysm::x,pyym::i}},//獻
{{pysm::l,pyym::v},{pysm::sh,pyym::uai},{pysm::l,pyym::ve}},//率
{{pysm::ch,pyym::ang},{pysm::y,pyym::ang},{pysm::d,pyym::ang}},//瑒
{{pysm::q,pyym::iang},{pysm::ch,pyym::eng},{pysm::c,pyym::ang}},//瑲
{{pysm::h,pyym::uan},{pysm::y,pyym::e},{pysm::y,pyym::an}},//瓛
{{pysm::h,pyym::u},{pysm::h,pyym::uo},{pysm::g,pyym::u}},//瓠
{{pysm::zh,pyym::en},{pysm::q,pyym::uan},{pysm::zh,pyym::un}},//甽
{{pysm::zh,pyym::i},{pysm::ch,pyym::ou},{pysm::sh,pyym::i}},//畤
{{pysm::p,pyym::i},{pysm::sh,pyym::u},{pysm::y,pyym::a}},//疋
{{pysm::k,pyym::e},{pysm::nop,pyym::e},{pysm::q,pyym::ia}},//疴
{{pysm::n,pyym::ie},{pysm::n,pyym::i},{pysm::n,pyym::ian}},//痆
{{pysm::w,pyym::ei},{pysm::y,pyym::ou},{pysm::y,pyym::u}},//痏
{{pysm::b,pyym::eng},{pysm::p,pyym::eng},{pysm::b,pyym::ing}},//痭
{{pysm::nop,pyym::an},{pysm::y,pyym::e},{pysm::nop,pyym::e}},//痷
{{pysm::w,pyym::en},{pysm::w,pyym::o},{pysm::y,pyym::un}},//瘟
{{pysm::b,pyym::ai},{pysm::b,pyym::o},{pysm::m,pyym::o}},//百
{{pysm::j,pyym::i},{pysm::x,pyym::iang},{pysm::b,pyym::i}},//皀
{{pysm::g,pyym::ao},{pysm::h,pyym::ao},{pysm::g,pyym::u}},//皋
{{pysm::x,pyym::iao},{pysm::j,pyym::iao},{pysm::p,pyym::o}},//皛
{{pysm::l,pyym::i},{pysm::l,pyym::uo},{pysm::b,pyym::o}},//皪
{{pysm::zh,pyym::ao},{pysm::zh,pyym::an},{pysm::d,pyym::an}},//皽
{{pysm::l,pyym::u},{pysm::l,pyym::v},{pysm::l,pyym::ei}},//盧
{{pysm::t,pyym::ian},{pysm::x,pyym::ian},{pysm::m,pyym::in}},//盷
{{pysm::d,pyym::un},{pysm::sh,pyym::un},{pysm::y,pyym::un}},//盾
{{pysm::sh,pyym::eng},{pysm::x,pyym::ing},{pysm::x,pyym::ian}},//省
{{pysm::j,pyym::u},{pysm::x,pyym::u},{pysm::k,pyym::ou}},//眗
{{pysm::x,pyym::uan},{pysm::h,pyym::uan},{pysm::j,pyym::uan}},//眩
{{pysm::x,pyym::uan},{pysm::sh,pyym::un},{pysm::x,pyym::un}},//眴
{{pysm::zh,pyym::e},{pysm::zh,pyym::ao},{pysm::zh,pyym::uo}},//着
{{pysm::s,pyym::uo},{pysm::j,pyym::un},{pysm::j,pyym::uan}},//睃
{{pysm::sh,pyym::ao},{pysm::q,pyym::iao},{pysm::x,pyym::iao}},//睄
{{pysm::g,pyym::un},{pysm::h,pyym::uan},{pysm::l,pyym::un}},//睔
{{pysm::s,pyym::ui},{pysm::h,pyym::ui},{pysm::w,pyym::ei}},//睢
{{pysm::ch,pyym::en},{pysm::t,pyym::ian},{pysm::sh,pyym::en}},//瞋
{{pysm::m,pyym::ing},{pysm::m,pyym::eng},{pysm::m,pyym::ian}},//瞑
{{pysm::m,pyym::ou},{pysm::w,pyym::u},{pysm::m,pyym::i}},//瞴
{{pysm::g,pyym::ui},{pysm::w,pyym::ei},{pysm::k,pyym::ui}},//瞶
{{pysm::q,pyym::u},{pysm::j,pyym::u},{pysm::j,pyym::i}},//瞿
{{pysm::j,pyym::in},{pysm::q,pyym::in},{pysm::g,pyym::uan}},//矜
{{pysm::y,pyym::u},{pysm::j,pyym::ue},{pysm::x,pyym::u}},//矞
{{pysm::g,pyym::ang},{pysm::k,pyym::ong},{pysm::q,pyym::iang}},//矼
{{pysm::h,pyym::uo},{pysm::h,pyym::ua},{pysm::x,pyym::u}},//砉
{{pysm::b,pyym::in},{pysm::f,pyym::en},{pysm::p,pyym::in}},//砏
{{pysm::f,pyym::a},{pysm::j,pyym::ie},{pysm::g,pyym::e}},//砝
{{pysm::p,pyym::ao},{pysm::b,pyym::ao},{pysm::p,pyym::u}},//砲
{{pysm::w,pyym::ei},{pysm::h,pyym::ui},{pysm::g,pyym::ui}},//硊
{{pysm::g,pyym::e},{pysm::l,pyym::uo},{pysm::l,pyym::i}},//硌
{{pysm::d,pyym::ong},{pysm::t,pyym::ong},{pysm::l,pyym::iu}},//硐
{{pysm::q,pyym::ue},{pysm::k,pyym::e},{pysm::k,pyym::u}},//硞
{{pysm::w,pyym::o},{pysm::nop,pyym::e},{pysm::y,pyym::i}},//硪
{{pysm::l,pyym::u},{pysm::l,pyym::iu},{pysm::l,pyym::uo}},//碌
{{pysm::j,pyym::ie},{pysm::k,pyym::e},{pysm::y,pyym::a}},//碣
{{pysm::zh,pyym::en},{pysm::nop,pyym::an},{pysm::k,pyym::an}},//碪
{{pysm::h,pyym::ua},{pysm::k,pyym::e},{pysm::g,pyym::u}},//磆
{{pysm::x,pyym::ia},{pysm::q,pyym::ia},{pysm::y,pyym::a}},//磍
{{pysm::w,pyym::ei},{pysm::nop,pyym::ai},{pysm::g,pyym::ai}},//磑
{{pysm::zh,pyym::uan},{pysm::t,pyym::uan},{pysm::t,pyym::uo}},//磚
{{pysm::h,pyym::uang},{pysm::k,pyym::uang},{pysm::g,pyym::ong}},//磺
{{pysm::h,pyym::e},{pysm::q,pyym::iao},{pysm::nop,pyym::ao}},//礉
{{pysm::sh,pyym::i},{pysm::q,pyym::i},{pysm::zh,pyym::i}},//示
{{pysm::q,pyym::i},{pysm::ch,pyym::i},{pysm::zh,pyym::i}},//祇
{{pysm::zh,pyym::u},{pysm::zh,pyym::ou},{pysm::ch,pyym::u}},//祝
{{pysm::ch,pyym::an},{pysm::sh,pyym::an},{pysm::t,pyym::an}},//禪
{{pysm::m,pyym::i},{pysm::n,pyym::i},{pysm::x,pyym::ian}},//禰
{{pysm::m,pyym::i},{pysm::b,pyym::i},{pysm::b,pyym::ie}},//秘
{{pysm::f,pyym::u},{pysm::b,pyym::u},{pysm::p,pyym::u}},//秿
{{pysm::ch,pyym::ou},{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//稠
{{pysm::z,pyym::ui},{pysm::z,pyym::u},{pysm::s,pyym::u}},//稡
{{pysm::x,pyym::ian},{pysm::j,pyym::ian},{pysm::l,pyym::ian}},//稴
{{pysm::g,pyym::ao},{pysm::k,pyym::ao},{pysm::j,pyym::iao}},//稾
{{pysm::c,pyym::an},{pysm::sh,pyym::an},{pysm::c,pyym::en}},//穇
{{pysm::m,pyym::ei},{pysm::m,pyym::en},{pysm::m,pyym::i}},//穈
{{pysm::zh,pyym::i},{pysm::ch,pyym::i},{pysm::t,pyym::i}},//穉
{{pysm::h,pyym::u},{pysm::w,pyym::en},{pysm::w,pyym::u}},//笏
{{pysm::c,pyym::en},{pysm::j,pyym::in},{pysm::h,pyym::an}},//笒
{{pysm::d,pyym::a},{pysm::x,pyym::ia},{pysm::n,pyym::a}},//笚
{{pysm::z,pyym::e},{pysm::z,pyym::uo},{pysm::zh,pyym::a}},//笮
{{pysm::s,pyym::un},{pysm::y,pyym::un},{pysm::x,pyym::un}},//筍
{{pysm::t,pyym::ong},{pysm::y,pyym::ong},{pysm::d,pyym::ong}},//筩
{{pysm::b,pyym::i},{pysm::b,pyym::ei},{pysm::p,pyym::ai}},//箄
{{pysm::q,pyym::ing},{pysm::j,pyym::ing},{pysm::q,pyym::iang}},//箐
{{pysm::y,pyym::ue},{pysm::y,pyym::ao},{pysm::ch,pyym::uo}},//箹
{{pysm::sh,pyym::uo},{pysm::x,pyym::iao},{pysm::q,pyym::iao}},//箾
{{pysm::l,pyym::ong},{pysm::g,pyym::ong},{pysm::g,pyym::an}},//篢
{{pysm::c,pyym::an},{pysm::c,pyym::en},{pysm::z,pyym::an}},//篸
{{pysm::zh,pyym::uan},{pysm::s,pyym::uan},{pysm::z,pyym::uan}},//篹
{{pysm::c,pyym::u},{pysm::ch,pyym::uo},{pysm::c,pyym::ou}},//簇
{{pysm::l,pyym::ou},{pysm::l,pyym::v},{pysm::j,pyym::u}},//簍
{{pysm::f,pyym::an},{pysm::b,pyym::an},{pysm::p,pyym::an}},//籓
{{pysm::z,pyym::i},{pysm::c,pyym::i},{pysm::j,pyym::i}},//粢
{{pysm::y,pyym::ue},{pysm::y,pyym::ao},{pysm::d,pyym::i}},//約
{{pysm::h,pyym::ong},{pysm::g,pyym::ong},{pysm::j,pyym::iang}},//紅
{{pysm::h,pyym::e},{pysm::g,pyym::e},{pysm::j,pyym::ie}},//紇
{{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::ch,pyym::i}},//紕
{{pysm::l,pyym::ei},{pysm::l,pyym::v},{pysm::l,pyym::ie}},//累
{{pysm::zh,pyym::en},{pysm::t,pyym::ian},{pysm::j,pyym::in}},//紾
{{pysm::b,pyym::eng},{pysm::b,pyym::ing},{pysm::p,pyym::eng}},//絣
{{pysm::g,pyym::ei},{pysm::j,pyym::i},{pysm::x,pyym::ia}},//給
{{pysm::t,pyym::iao},{pysm::d,pyym::iao},{pysm::d,pyym::ao}},//絩
{{pysm::ch,pyym::en},{pysm::sh,pyym::en},{pysm::l,pyym::in}},//綝
{{pysm::ch,pyym::ou},{pysm::t,pyym::ao},{pysm::d,pyym::iao}},//綢
{{pysm::q,pyym::ian},{pysm::q,pyym::ing},{pysm::zh,pyym::eng}},//綪
{{pysm::t,pyym::ian},{pysm::t,pyym::an},{pysm::ch,pyym::an}},//緂
{{pysm::m,pyym::in},{pysm::m,pyym::ian},{pysm::h,pyym::un}},//緡
{{pysm::t,pyym::ou},{pysm::x,pyym::u},{pysm::y,pyym::u}},//緰
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ao},{pysm::c,pyym::u}},//縐
{{pysm::c,pyym::i},{pysm::c,pyym::uo},{pysm::s,pyym::uo}},//縒
{{pysm::c,pyym::ui},{pysm::s,pyym::ui},{pysm::sh,pyym::uai}},//縗
{{pysm::f,pyym::an},{pysm::p,pyym::o},{pysm::p,pyym::an}},//繁
{{pysm::y,pyym::ao},{pysm::y,pyym::ou},{pysm::zh,pyym::ou}},//繇
{{pysm::sh,pyym::eng},{pysm::y,pyym::ing},{pysm::m,pyym::in}},//繩
{{pysm::z,pyym::ao},{pysm::s,pyym::ao},{pysm::q,pyym::iao}},//繰
{{pysm::j,pyym::iao},{pysm::zh,pyym::uo},{pysm::h,pyym::e}},//繳
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::ch,pyym::an}},//繵
{{pysm::r,pyym::ang},{pysm::x,pyym::iang},{pysm::s,pyym::ang}},//纕
{{pysm::l,pyym::i},{pysm::x,pyym::i},{pysm::s,pyym::a}},//纚
{{pysm::m,pyym::ou},{pysm::m,pyym::iao},{pysm::m,pyym::iu}},//缪
{{pysm::g,pyym::ua},{pysm::h,pyym::ua},{pysm::g,pyym::uai}},//罫
{{pysm::x,pyym::ian},{pysm::y,pyym::an},{pysm::y,pyym::i}},//羡
{{pysm::q,pyym::ian},{pysm::x,pyym::ian},{pysm::y,pyym::an}},//羬
{{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::p,pyym::o}},//翍
{{pysm::q,pyym::i},{pysm::zh,pyym::i},{pysm::sh,pyym::i}},//耆
{{pysm::w,pyym::a},{pysm::t,pyym::ui},{pysm::zh,pyym::uo}},//聉
{{pysm::l,pyym::e},{pysm::l,pyym::ei},{pysm::j,pyym::in}},//肋
{{pysm::nop,pyym::ang},{pysm::h,pyym::ang},{pysm::g,pyym::ang}},//肮
{{pysm::y,pyym::u},{pysm::zh,pyym::ou},{pysm::y,pyym::o}},//育
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::d,pyym::a}},//胆
{{pysm::g,pyym::ua},{pysm::g,pyym::u},{pysm::h,pyym::u}},//胍
{{pysm::z,pyym::i},{pysm::c,pyym::i},{pysm::j,pyym::i}},//胔
{{pysm::sh,pyym::eng},{pysm::x,pyym::ing},{pysm::q,pyym::ing}},//胜
{{pysm::zh,pyym::i},{pysm::ch,pyym::i},{pysm::d,pyym::i}},//胝
{{pysm::x,pyym::ie},{pysm::x,pyym::ian},{pysm::x,pyym::i}},//脅
{{pysm::l,pyym::ie},{pysm::l,pyym::uan},{pysm::p,pyym::ao}},//脟
{{pysm::q,pyym::ian},{pysm::q,pyym::u},{pysm::j,pyym::ie}},//脥
{{pysm::p,pyym::i},{pysm::p,pyym::ai},{pysm::b,pyym::i}},//脾
{{pysm::l,pyym::ei},{pysm::g,pyym::uo},{pysm::h,pyym::ua}},//腂
{{pysm::k,pyym::ui},{pysm::q,pyym::uan},{pysm::j,pyym::uan}},//腃
{{pysm::ch,pyym::ui},{pysm::h,pyym::ou},{pysm::ch,pyym::uai}},//腄
{{pysm::y,pyym::an},{pysm::nop,pyym::a},{pysm::nop,pyym::ang}},//腌
{{pysm::zh,pyym::uan},{pysm::d,pyym::un},{pysm::t,pyym::u}},//腞
{{pysm::q,pyym::ian},{pysm::x,pyym::ian},{pysm::y,pyym::an}},//膁
{{pysm::b,pyym::o},{pysm::p,pyym::o},{pysm::l,pyym::ie}},//膊
{{pysm::zh,pyym::uan},{pysm::ch,pyym::uan},{pysm::ch,pyym::un}},//膞
{{pysm::j,pyym::iao},{pysm::h,pyym::ao},{pysm::n,pyym::ao}},//膠
{{pysm::ch,pyym::uai},{pysm::zh,pyym::a},{pysm::zh,pyym::ai}},//膪
{{pysm::g,pyym::ui},{pysm::k,pyym::ui},{pysm::d,pyym::ui}},//膭
{{pysm::h,pyym::u},{pysm::w,pyym::u},{pysm::m,pyym::ei}},//膴
{{pysm::q,pyym::ian},{pysm::x,pyym::ian},{pysm::q,pyym::in}},//臤
{{pysm::y,pyym::u},{pysm::y,pyym::ong},{pysm::k,pyym::ui}},//臾
{{pysm::ch,pyym::ong},{pysm::ch,pyym::uang},{pysm::zh,pyym::ong}},//舂
{{pysm::x,pyym::i},{pysm::q,pyym::ue},{pysm::t,pyym::uo}},//舄
{{pysm::b,pyym::an},{pysm::p,pyym::an},{pysm::b,pyym::o}},//般
{{pysm::k,pyym::e},{pysm::j,pyym::ie},{pysm::z,pyym::ong}},//艐
{{pysm::ch,pyym::ong},{pysm::zh,pyym::uang},{pysm::t,pyym::ong}},//艟
{{pysm::f,pyym::u},{pysm::b,pyym::o},{pysm::p,pyym::ei}},//艴
{{pysm::m,pyym::ang},{pysm::h,pyym::uang},{pysm::w,pyym::ang}},//芒
{{pysm::y,pyym::uan},{pysm::y,pyym::u},{pysm::y,pyym::un}},//苑
{{pysm::b,pyym::ao},{pysm::p,pyym::ao},{pysm::b,pyym::iao}},//苞
{{pysm::k,pyym::u},{pysm::g,pyym::u},{pysm::h,pyym::u}},//苦
{{pysm::sh,pyym::an},{pysm::t,pyym::ian},{pysm::ch,pyym::an}},//苫
{{pysm::b,pyym::i},{pysm::b,pyym::ie},{pysm::m,pyym::i}},//苾
{{pysm::b,pyym::a},{pysm::p,pyym::ei},{pysm::f,pyym::ei}},//茇
{{pysm::c,pyym::i},{pysm::z,pyym::i},{pysm::ch,pyym::ai}},//茈
{{pysm::h,pyym::ao},{pysm::x,pyym::iu},{pysm::k,pyym::ou}},//茠
{{pysm::j,pyym::iao},{pysm::x,pyym::iao},{pysm::q,pyym::iao}},//茭
{{pysm::sh,pyym::a},{pysm::s,pyym::uo},{pysm::s,pyym::ui}},//莎
{{pysm::m,pyym::eng},{pysm::x,pyym::i},{pysm::q,pyym::ing}},//莔
{{pysm::y,pyym::ou},{pysm::d,pyym::iao},{pysm::d,pyym::i}},//莜
{{pysm::w,pyym::en},{pysm::w,pyym::an},{pysm::m,pyym::ian}},//莬
{{pysm::w,pyym::an},{pysm::y,pyym::u},{pysm::y,pyym::un}},//菀
{{pysm::p,pyym::u},{pysm::b,pyym::ei},{pysm::b,pyym::o}},//菩
{{pysm::t,pyym::ai},{pysm::zh,pyym::i},{pysm::ch,pyym::i}},//菭
{{pysm::x,pyym::iao},{pysm::sh,pyym::ao},{pysm::sh,pyym::uo}},//萷
{{pysm::l,pyym::uo},{pysm::l,pyym::a},{pysm::l,pyym::ao}},//落
{{pysm::s,pyym::ui},{pysm::j,pyym::un},{pysm::s,pyym::uo}},//葰
{{pysm::z,pyym::u},{pysm::j,pyym::u},{pysm::j,pyym::i}},//蒩
{{pysm::d,pyym::iao},{pysm::t,pyym::iao},{pysm::d,pyym::i}},//蓧
{{pysm::c,pyym::ong},{pysm::z,pyym::ong},{pysm::s,pyym::ong}},//蓯
{{pysm::d,pyym::i},{pysm::d,pyym::ai},{pysm::ch,pyym::ai}},//蔕
{{pysm::c,pyym::uo},{pysm::c,pyym::u},{pysm::zh,pyym::a}},//蔖
{{pysm::c,pyym::u},{pysm::c,pyym::ou},{pysm::ch,pyym::uo}},//蔟
{{pysm::c,pyym::ai},{pysm::s,pyym::a},{pysm::c,pyym::a}},//蔡
{{pysm::b,pyym::i},{pysm::b,pyym::ie},{pysm::p,pyym::ie}},//蔽
{{pysm::q,pyym::ian},{pysm::t,pyym::an},{pysm::x,pyym::un}},//蕁
{{pysm::f,pyym::an},{pysm::b,pyym::o},{pysm::p,pyym::i}},//蕃
{{pysm::z,pyym::ui},{pysm::j,pyym::ue},{pysm::zh,pyym::uo}},//蕞
{{pysm::b,pyym::ao},{pysm::b,pyym::o},{pysm::b,pyym::u}},//薄
{{pysm::ch,pyym::ou},{pysm::zh,pyym::ou},{pysm::d,pyym::ao}},//薵
{{pysm::j,pyym::i},{pysm::c,pyym::i},{pysm::q,pyym::i}},//薺
{{pysm::x,pyym::iao},{pysm::h,pyym::ao},{pysm::h,pyym::e}},//藃
{{pysm::d,pyym::iao},{pysm::d,pyym::i},{pysm::zh,pyym::uo}},//藋
{{pysm::y,pyym::ao},{pysm::sh,pyym::uo},{pysm::l,pyym::ve}},//藥
{{pysm::s,pyym::ou},{pysm::sh,pyym::u},{pysm::c,pyym::ou}},//藪
{{pysm::ch,pyym::u},{pysm::zh,pyym::u},{pysm::zh,pyym::a}},//藸
{{pysm::q,pyym::i},{pysm::j,pyym::i},{pysm::q,pyym::in}},//蘄
{{pysm::r,pyym::ang},{pysm::x,pyym::iang},{pysm::n,pyym::ang}},//蘘
{{pysm::k,pyym::ui},{pysm::h,pyym::ui},{pysm::g,pyym::ui}},//蘬
{{pysm::h,pyym::ong},{pysm::j,pyym::iang},{pysm::g,pyym::ong}},//虹
{{pysm::g,pyym::ou},{pysm::q,pyym::u},{pysm::x,pyym::u}},//蚼
{{pysm::q,pyym::i},{pysm::j,pyym::ie},{pysm::q,pyym::ie}},//蛣
{{pysm::h,pyym::a},{pysm::g,pyym::e},{pysm::nop,pyym::e}},//蛤
{{pysm::f,pyym::ei},{pysm::p,pyym::ei},{pysm::b,pyym::ei}},//蜚
{{pysm::sh,pyym::i},{pysm::l,pyym::i},{pysm::l,pyym::ong}},//蝕
{{pysm::q,pyym::iu},{pysm::y,pyym::ou},{pysm::j,pyym::iu}},//蝤
{{pysm::x,pyym::ia},{pysm::h,pyym::a},{pysm::j,pyym::ia}},//蝦
{{pysm::w,pyym::o},{pysm::l,pyym::uo},{pysm::g,pyym::uo}},//蝸
{{pysm::b,pyym::an},{pysm::p,pyym::an},{pysm::h,pyym::uan}},//螌
{{pysm::ch,pyym::an},{pysm::t,pyym::i},{pysm::sh,pyym::an}},//蟬
{{pysm::ch,pyym::ong},{pysm::zh,pyym::ong},{pysm::t,pyym::ong}},//蟲
{{pysm::n,pyym::ang},{pysm::sh,pyym::ang},{pysm::r,pyym::ang}},//蠰
{{pysm::x,pyym::ing},{pysm::h,pyym::ang},{pysm::h,pyym::eng}},//行
{{pysm::sh,pyym::uai},{pysm::s,pyym::uo},{pysm::c,pyym::ui}},//衰
{{pysm::zh,pyym::i},{pysm::t,pyym::i},{pysm::q,pyym::i}},//衹
{{pysm::h,pyym::e},{pysm::k,pyym::e},{pysm::k,pyym::ua}},//袔
{{pysm::b,pyym::ei},{pysm::b,pyym::i},{pysm::p,pyym::i}},//被
{{pysm::j,pyym::ia},{pysm::q,pyym::ia},{pysm::j,pyym::ie}},//袷
{{pysm::ch,pyym::u},{pysm::zh,pyym::e},{pysm::zh,pyym::u}},//褚
{{pysm::zh,pyym::e},{pysm::d,pyym::ie},{pysm::x,pyym::i}},//褶
{{pysm::z,pyym::e},{pysm::d,pyym::uo},{pysm::y,pyym::i}},//襗
{{pysm::t,pyym::an},{pysm::zh,pyym::an},{pysm::ch,pyym::an}},//襢
{{pysm::t,pyym::an},{pysm::q,pyym::in},{pysm::y,pyym::an}},//覃
{{pysm::ch,pyym::an},{pysm::d,pyym::an},{pysm::j,pyym::i}},//覘
{{pysm::c,pyym::u},{pysm::ch,pyym::u},{pysm::ch,pyym::eng}},//觕
{{pysm::j,pyym::ue},{pysm::k,pyym::ui},{pysm::g,pyym::ui}},//觖
{{pysm::h,pyym::u},{pysm::q,pyym::ue},{pysm::j,pyym::ue}},//觳
{{pysm::h,pyym::ong},{pysm::j,pyym::un},{pysm::h,pyym::eng}},//訇
{{pysm::x,pyym::in},{pysm::x,pyym::i},{pysm::y,pyym::in}},//訢
{{pysm::n,pyym::ao},{pysm::n,pyym::a},{pysm::n,pyym::u}},//詉
{{pysm::y,pyym::i},{pysm::d,pyym::ai},{pysm::t,pyym::ai}},//詒
{{pysm::nop,pyym::e},{pysm::l,pyym::ve},{pysm::l,pyym::uo}},//詻
{{pysm::y,pyym::i},{pysm::ch,pyym::i},{pysm::d,pyym::uo}},//誃
{{pysm::d,pyym::iao},{pysm::t,pyym::iao},{pysm::zh,pyym::ou}},//調
{{pysm::h,pyym::ao},{pysm::x,pyym::ia},{pysm::h,pyym::uo}},//諕
{{pysm::x,pyym::i},{pysm::sh,pyym::ai},{pysm::nop,pyym::ai}},//諰
{{pysm::zh,pyym::ou},{pysm::ch,pyym::ou},{pysm::ch,pyym::ao}},//謅
{{pysm::sh,pyym::i},{pysm::y,pyym::i},{pysm::x,pyym::i}},//謚
{{pysm::j,pyym::ie},{pysm::zh,pyym::a},{pysm::z,pyym::u}},//謯
{{pysm::zh,pyym::uo},{pysm::sh,pyym::u},{pysm::zh,pyym::e}},//謶
{{pysm::nop,pyym::e},{pysm::w,pyym::a},{pysm::g,pyym::ui}},//譌
{{pysm::h,pyym::ua},{pysm::x,pyym::ie},{pysm::h,pyym::ui}},//譮
{{pysm::nop,pyym::ai},{pysm::y,pyym::i},{pysm::n,pyym::i}},//譺
{{pysm::sh,pyym::uo},{pysm::sh,pyym::ui},{pysm::y,pyym::ue}},//说
{{pysm::g,pyym::u},{pysm::l,pyym::u},{pysm::y,pyym::u}},//谷
{{pysm::y,pyym::u},{pysm::x,pyym::ie},{pysm::sh,pyym::u}},//豫
{{pysm::k,pyym::un},{pysm::m,pyym::ao},{pysm::k,pyym::en}},//貇
{{pysm::l,pyym::i},{pysm::m,pyym::ai},{pysm::y,pyym::u}},//貍
{{pysm::f,pyym::ei},{pysm::f,pyym::u},{pysm::b,pyym::i}},//費
{{pysm::g,pyym::an},{pysm::g,pyym::ong},{pysm::zh,pyym::uang}},//贛
{{pysm::ch,pyym::en},{pysm::zh,pyym::en},{pysm::n,pyym::ian}},//趁
{{pysm::j,pyym::u},{pysm::q,pyym::u},{pysm::q,pyym::iu}},//趜
{{pysm::q,pyym::ue},{pysm::q,pyym::i},{pysm::j,pyym::i}},//趞
{{pysm::t,pyym::ang},{pysm::zh,pyym::eng},{pysm::ch,pyym::eng}},//趟
{{pysm::c,pyym::ui},{pysm::w,pyym::ei},{pysm::j,pyym::u}},//趡
{{pysm::q,pyym::u},{pysm::c,pyym::u},{pysm::c,pyym::ou}},//趨
{{pysm::q,pyym::iao},{pysm::j,pyym::iao},{pysm::ch,pyym::ao}},//趫
{{pysm::t,pyym::i},{pysm::y,pyym::ue},{pysm::y,pyym::ao}},//趯
{{pysm::t,pyym::a},{pysm::s,pyym::a},{pysm::q,pyym::i}},//趿
{{pysm::q,pyym::i},{pysm::j,pyym::i},{pysm::zh,pyym::i}},//跂
{{pysm::b,pyym::o},{pysm::b,pyym::i},{pysm::p,pyym::o}},//跛
{{pysm::d,pyym::uo},{pysm::d,pyym::ai},{pysm::ch,pyym::i}},//跢
{{pysm::p,pyym::ian},{pysm::b,pyym::eng},{pysm::b,pyym::ing}},//跰
{{pysm::t,pyym::iao},{pysm::d,pyym::iao},{pysm::t,pyym::ao}},//跳
{{pysm::t,pyym::u},{pysm::d,pyym::uo},{pysm::ch,pyym::uo}},//跿
{{pysm::w,pyym::o},{pysm::w,pyym::ei},{pysm::r,pyym::ui}},//踒
{{pysm::j,pyym::i},{pysm::q,pyym::i},{pysm::q,pyym::ue}},//踖
{{pysm::z,pyym::u},{pysm::c,pyym::u},{pysm::c,pyym::ui}},//踤
{{pysm::y,pyym::i},{pysm::q,pyym::i},{pysm::j,pyym::i}},//踦
{{pysm::y,pyym::u},{pysm::y,pyym::ao},{pysm::ch,pyym::u}},//踰
{{pysm::n,pyym::uo},{pysm::r,pyym::e},{pysm::n,pyym::a}},//蹃
{{pysm::n,pyym::ian},{pysm::zh,pyym::an},{pysm::ch,pyym::an}},//蹍
{{pysm::p,pyym::an},{pysm::m,pyym::an},{pysm::l,pyym::iang}},//蹣
{{pysm::c,pyym::u},{pysm::z,pyym::u},{pysm::j,pyym::iu}},//蹴
{{pysm::l,pyym::i},{pysm::y,pyym::ue},{pysm::l,pyym::uo}},//躒
{{pysm::y,pyym::a},{pysm::zh,pyym::a},{pysm::g,pyym::a}},//軋
{{pysm::q,pyym::u},{pysm::g,pyym::ou},{pysm::j,pyym::u}},//軥
{{pysm::y,pyym::i},{pysm::d,pyym::ie},{pysm::zh,pyym::e}},//軼
{{pysm::j,pyym::iao},{pysm::j,pyym::ue},{pysm::x,pyym::iao}},//較
{{pysm::h,pyym::e},{pysm::l,pyym::u},{pysm::y,pyym::a}},//輅
{{pysm::z,pyym::ai},{pysm::d,pyym::ai},{pysm::z,pyym::i}},//載
{{pysm::g,pyym::uo},{pysm::h,pyym::ua},{pysm::h,pyym::ui}},//輠
{{pysm::y,pyym::a},{pysm::zh,pyym::a},{pysm::g,pyym::a}},//轧
{{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::m,pyym::i}},//辟
{{pysm::b,pyym::ian},{pysm::b,pyym::an},{pysm::p,pyym::ian}},//辨
{{pysm::b,pyym::ian},{pysm::p,pyym::ian},{pysm::b,pyym::an}},//辯
{{pysm::d,pyym::a},{pysm::t,pyym::i},{pysm::t,pyym::a}},//达
{{pysm::w,pyym::ang},{pysm::g,pyym::uang},{pysm::k,pyym::uang}},//迋
{{pysm::h,pyym::ai},{pysm::h,pyym::uan},{pysm::f,pyym::u}},//还
{{pysm::d,pyym::ie},{pysm::y,pyym::i},{pysm::d,pyym::a}},//迭
{{pysm::zh,pyym::ui},{pysm::d,pyym::ui},{pysm::t,pyym::ui}},//追
{{pysm::zh,pyym::e},{pysm::y,pyym::an},{pysm::zh,pyym::ei}},//這
{{pysm::q,pyym::un},{pysm::x,pyym::un},{pysm::s,pyym::uo}},//逡
{{pysm::f,pyym::eng},{pysm::p,pyym::eng},{pysm::p,pyym::ang}},//逢
{{pysm::d,pyym::un},{pysm::q,pyym::un},{pysm::x,pyym::un}},//遁
{{pysm::y,pyym::u},{pysm::y,pyym::ong},{pysm::nop,pyym::ou}},//遇
{{pysm::d,pyym::i},{pysm::sh,pyym::i},{pysm::d,pyym::ai}},//遞
{{pysm::ch,pyym::i},{pysm::zh,pyym::i},{pysm::x,pyym::i}},//遟
{{pysm::d,pyym::i},{pysm::sh,pyym::i},{pysm::d,pyym::ai}},//遰
{{pysm::x,pyym::uan},{pysm::s,pyym::uan},{pysm::sh,pyym::ua}},//選
{{pysm::y,pyym::i},{pysm::w,pyym::ei},{pysm::s,pyym::ui}},//遺
{{pysm::h,pyym::ai},{pysm::h,pyym::uan},{pysm::x,pyym::uan}},//還
{{pysm::n,pyym::uo},{pysm::n,pyym::a},{pysm::f,pyym::u}},//郍
{{pysm::h,pyym::ao},{pysm::q,pyym::iao},{pysm::j,pyym::iao}},//鄗
{{pysm::p,pyym::o},{pysm::p,pyym::i},{pysm::p,pyym::an}},//鄱
{{pysm::l,pyym::ao},{pysm::l,pyym::uo},{pysm::l,pyym::u}},//酪
{{pysm::t,pyym::ong},{pysm::d,pyym::ong},{pysm::ch,pyym::ong}},//酮
{{pysm::x,pyym::ing},{pysm::ch,pyym::eng},{pysm::j,pyym::ing}},//醒
{{pysm::j,pyym::iao},{pysm::q,pyym::iao},{pysm::zh,pyym::an}},//醮
{{pysm::ch,pyym::ou},{pysm::sh,pyym::ou},{pysm::d,pyym::ao}},//醻
{{pysm::sh,pyym::ai},{pysm::sh,pyym::i},{pysm::l,pyym::i}},//釃
{{pysm::zh,pyym::ong},{pysm::ch,pyym::ong},{pysm::t,pyym::ong}},//重
{{pysm::r,pyym::i},{pysm::r,pyym::en},{pysm::j,pyym::ian}},//釰
{{pysm::sh,pyym::i},{pysm::y,pyym::i},{pysm::y,pyym::e}},//釶
{{pysm::ch,pyym::en},{pysm::q,pyym::in},{pysm::zh,pyym::en}},//鈂
{{pysm::s,pyym::i},{pysm::c,pyym::i},{pysm::t,pyym::ai}},//鈶
{{pysm::ch,pyym::an},{pysm::q,pyym::ian},{pysm::t,pyym::ie}},//鉆
{{pysm::x,pyym::i},{pysm::n,pyym::i},{pysm::n,pyym::ie}},//鉨
{{pysm::x,pyym::ian},{pysm::t,pyym::ian},{pysm::g,pyym::ua}},//銛
{{pysm::t,pyym::ou},{pysm::d,pyym::ou},{pysm::t,pyym::u}},//鋀
{{pysm::c,pyym::uan},{pysm::j,pyym::ian},{pysm::j,pyym::uan}},//鋑
{{pysm::h,pyym::ua},{pysm::w,pyym::u},{pysm::h,pyym::u}},//鋘
{{pysm::q,pyym::in},{pysm::q,pyym::ian},{pysm::j,pyym::in}},//鋟
{{pysm::r,pyym::ui},{pysm::d,pyym::ui},{pysm::y,pyym::ue}},//鋭
{{pysm::g,pyym::uo},{pysm::k,pyym::ua},{pysm::k,pyym::e}},//錁
{{pysm::p,pyym::ou},{pysm::f,pyym::u},{pysm::p,pyym::ei}},//錇
{{pysm::p,pyym::i},{pysm::b,pyym::ei},{pysm::b,pyym::i}},//錍
{{pysm::x,pyym::ian},{pysm::g,pyym::an},{pysm::q,pyym::ian}},//錎
{{pysm::n,pyym::ei},{pysm::zh,pyym::ui},{pysm::w,pyym::ei}},//錗
{{pysm::ch,pyym::un},{pysm::d,pyym::ui},{pysm::d,pyym::uo}},//錞
{{pysm::t,pyym::an},{pysm::x,pyym::ian},{pysm::y,pyym::an}},//錟
{{pysm::c,pyym::uo},{pysm::c,pyym::u},{pysm::x,pyym::i}},//錯
{{pysm::d,pyym::i},{pysm::ch,pyym::i},{pysm::sh,pyym::i}},//鍉
{{pysm::d,pyym::uo},{pysm::d,pyym::u},{pysm::zh,pyym::e}},//鍺
{{pysm::y,pyym::e},{pysm::t,pyym::a},{pysm::g,pyym::e}},//鎑
{{pysm::ch,pyym::ui},{pysm::d,pyym::ui},{pysm::zh,pyym::ui}},//鎚
{{pysm::sh,pyym::a},{pysm::sh,pyym::i},{pysm::s,pyym::e}},//鎩
{{pysm::s,pyym::an},{pysm::q,pyym::iao},{pysm::c,pyym::an}},//鏒
{{pysm::h,pyym::ui},{pysm::s,pyym::ui},{pysm::r,pyym::ui}},//鏸
{{pysm::s,pyym::an},{pysm::x,pyym::ian},{pysm::s,pyym::a}},//鏾
{{pysm::q,pyym::iao},{pysm::s,pyym::ao},{pysm::c,pyym::ao}},//鐰
{{pysm::d,pyym::ang},{pysm::ch,pyym::eng},{pysm::t,pyym::ang}},//鐺
{{pysm::x,pyym::u},{pysm::r,pyym::u},{pysm::r,pyym::ou}},//鑐
{{pysm::sh,pyym::uo},{pysm::y,pyym::ue},{pysm::l,pyym::i}},//鑠
{{pysm::z,pyym::ao},{pysm::z,pyym::uo},{pysm::z,pyym::u}},//鑿
{{pysm::ch,pyym::an},{pysm::t,pyym::an},{pysm::x,pyym::in}},//镡
{{pysm::zh,pyym::a},{pysm::y,pyym::a},{pysm::g,pyym::e}},//閘
{{pysm::nop,pyym::e},{pysm::y,pyym::u},{pysm::y,pyym::an}},//閼
{{pysm::h,pyym::ong},{pysm::x,pyym::iang},{pysm::j,pyym::uan}},//闂
{{pysm::q,pyym::ue},{pysm::j,pyym::ue},{pysm::k,pyym::ui}},//闋
{{pysm::k,pyym::an},{pysm::h,pyym::an},{pysm::x,pyym::ian}},//闞
{{pysm::x,pyym::i},{pysm::s,pyym::e},{pysm::t,pyym::a}},//闟
{{pysm::zh,pyym::i},{pysm::y,pyym::i},{pysm::t,pyym::uo}},//阤
{{pysm::k,pyym::eng},{pysm::k,pyym::ang},{pysm::g,pyym::ang}},//阬
{{pysm::t,pyym::uo},{pysm::zh,pyym::i},{pysm::y,pyym::i}},//陁
{{pysm::ch,pyym::u},{pysm::zh,pyym::u},{pysm::sh,pyym::u}},//除
{{pysm::t,pyym::ao},{pysm::y,pyym::ao},{pysm::d,pyym::ao}},//陶
{{pysm::sh,pyym::u},{pysm::y,pyym::u},{pysm::y,pyym::ao}},//隃
{{pysm::d,pyym::ui},{pysm::zh,pyym::ui},{pysm::s,pyym::ui}},//隊
{{pysm::s,pyym::ui},{pysm::d,pyym::uo},{pysm::t,pyym::uo}},//隋
{{pysm::g,pyym::ai},{pysm::nop,pyym::ai},{pysm::q,pyym::i}},//隑
{{pysm::g,pyym::e},{pysm::r,pyym::ong},{pysm::j,pyym::i}},//隔
{{pysm::k,pyym::ui},{pysm::w,pyym::ei},{pysm::g,pyym::ui}},//隗
{{pysm::x,pyym::ian},{pysm::j,pyym::ian},{pysm::y,pyym::an}},//險
{{pysm::zh,pyym::ui},{pysm::c,pyym::ui},{pysm::w,pyym::ei}},//隹
{{pysm::h,pyym::u},{pysm::h,pyym::e},{pysm::q,pyym::ue}},//隺
{{pysm::j,pyym::uan},{pysm::j,pyym::un},{pysm::z,pyym::ui}},//雋
{{pysm::l,pyym::i},{pysm::ch,pyym::i},{pysm::g,pyym::u}},//離
{{pysm::h,pyym::uo},{pysm::h,pyym::e},{pysm::s,pyym::uo}},//霍
{{pysm::m,pyym::eng},{pysm::m,pyym::ao},{pysm::w,pyym::u}},//霿
{{pysm::h,pyym::uo},{pysm::s,pyym::ui},{pysm::s,pyym::uo}},//靃
{{pysm::b,pyym::ei},{pysm::b,pyym::ai},{pysm::b,pyym::i}},//鞁
{{pysm::g,pyym::e},{pysm::s,pyym::a},{pysm::t,pyym::a}},//鞈
{{pysm::j,pyym::u},{pysm::q,pyym::u},{pysm::q,pyym::iong}},//鞠
{{pysm::x,pyym::ie},{pysm::zh,pyym::a},{pysm::d,pyym::ie}},//鞢
{{pysm::h,pyym::e},{pysm::sh,pyym::e},{pysm::m,pyym::o}},//鞨
{{pysm::x,pyym::ie},{pysm::j,pyym::ia},{pysm::j,pyym::ie}},//頡
{{pysm::f,pyym::u},{pysm::t,pyym::ao},{pysm::t,pyym::iao}},//頫
{{pysm::x,pyym::uan},{pysm::j,pyym::iong},{pysm::x,pyym::ian}},//顈
{{pysm::ch,pyym::an},{pysm::zh,pyym::an},{pysm::sh,pyym::an}},//顫
{{pysm::sh,pyym::i},{pysm::s,pyym::i},{pysm::y,pyym::i}},//食
{{pysm::y,pyym::i},{pysm::y,pyym::e},{pysm::nop,pyym::en}},//饐
{{pysm::t,pyym::uo},{pysm::d,pyym::uo},{pysm::d,pyym::ai}},//馱
{{pysm::t,pyym::ai},{pysm::d,pyym::ai},{pysm::zh,pyym::ai}},//駘
{{pysm::nop,pyym::ai},{pysm::s,pyym::i},{pysm::t,pyym::ai}},//騃
{{pysm::j,pyym::ie},{pysm::j,pyym::ia},{pysm::x,pyym::ie}},//骱
{{pysm::q,pyym::iao},{pysm::j,pyym::iao},{pysm::x,pyym::iao}},//骹
{{pysm::b,pyym::iao},{pysm::p,pyym::iao},{pysm::sh,pyym::an}},//髟
{{pysm::m,pyym::ao},{pysm::r,pyym::ou},{pysm::m,pyym::eng}},//髳
{{pysm::t,pyym::uo},{pysm::ch,pyym::ui},{pysm::d,pyym::uo}},//鬌
{{pysm::g,pyym::e},{pysm::l,pyym::i},{pysm::nop,pyym::e}},//鬲
{{pysm::y,pyym::u},{pysm::zh,pyym::ou},{pysm::j,pyym::u}},//鬻
{{pysm::p,pyym::o},{pysm::b,pyym::o},{pysm::t,pyym::uo}},//魄
{{pysm::nop,pyym::e},{pysm::q,pyym::ie},{pysm::j,pyym::i}},//魥
{{pysm::j,pyym::u},{pysm::q,pyym::u},{pysm::g,pyym::ou}},//鮈
{{pysm::t,pyym::iao},{pysm::y,pyym::ou},{pysm::ch,pyym::ou}},//鯈
{{pysm::d,pyym::ie},{pysm::q,pyym::ie},{pysm::zh,pyym::a}},//鰈
{{pysm::g,pyym::an},{pysm::j,pyym::ian},{pysm::x,pyym::ian}},//鰔
{{pysm::g,pyym::uan},{pysm::k,pyym::un},{pysm::g,pyym::un}},//鰥
{{pysm::sh,pyym::en},{pysm::s,pyym::ao},{pysm::c,pyym::an}},//鰺
{{pysm::zh,pyym::uan},{pysm::t,pyym::uan},{pysm::l,pyym::ian}},//鱄
{{pysm::y,pyym::ing},{pysm::sh,pyym::eng},{pysm::m,pyym::eng}},//鱦
{{pysm::l,pyym::i},{pysm::l,pyym::u},{pysm::l,pyym::uo}},//鱳
{{pysm::j,pyym::iu},{pysm::q,pyym::iu},{pysm::zh,pyym::i}},//鳩
{{pysm::g,pyym::an},{pysm::h,pyym::an},{pysm::y,pyym::an}},//鳱
{{pysm::j,pyym::ian},{pysm::q,pyym::ian},{pysm::zh,pyym::an}},//鳽
{{pysm::y,pyym::an},{pysm::nop,pyym::an},{pysm::nop,pyym::e}},//鴳
{{pysm::h,pyym::uan},{pysm::j,pyym::uan},{pysm::g,pyym::uan}},//鵍
{{pysm::h,pyym::u},{pysm::g,pyym::u},{pysm::h,pyym::e}},//鵠
{{pysm::g,pyym::uan},{pysm::h,pyym::uan},{pysm::q,pyym::uan}},//鸛
{{pysm::p,pyym::ao},{pysm::b,pyym::iao},{pysm::p,pyym::iao}},//麃
{{pysm::m,pyym::o},{pysm::m,pyym::a},{pysm::m,pyym::e}},//麽
{{pysm::d,pyym::ian},{pysm::zh,pyym::an},{pysm::d,pyym::uo}},//點
{{pysm::d,pyym::ang},{pysm::t,pyym::ang},{pysm::ch,pyym::eng}},//黨
{{pysm::m,pyym::ian},{pysm::m,pyym::eng},{pysm::m,pyym::in}},//黽
{{pysm::m,pyym::in},{pysm::m,pyym::ian},{pysm::m,pyym::eng}},//黾
{{pysm::z,pyym::e},{pysm::c,pyym::e},{pysm::zh,pyym::a}},//齰
{{pysm::g,pyym::ui},{pysm::q,pyym::iu},{pysm::j,pyym::un}},//龜
{{pysm::g,pyym::ui},{pysm::j,pyym::un},{pysm::q,pyym::iu}},//龟
};
constexpr static PinYin4 s_pinyin4[] = { {{pysm::m,pyym::e},{pysm::y,pyym::ao},{pysm::m,pyym::o},{pysm::m,pyym::a}},//么
{{pysm::t,pyym::uo},{pysm::d,pyym::uo},{pysm::ch,pyym::a},{pysm::zh,pyym::e}},//仛
{{pysm::b,pyym::o},{pysm::b,pyym::ai},{pysm::m,pyym::o},{pysm::b,pyym::a}},//伯
{{pysm::y,pyym::i},{pysm::nop,pyym::ai},{pysm::s,pyym::i},{pysm::ch,pyym::i}},//佁
{{pysm::f,pyym::u},{pysm::f,pyym::o},{pysm::b,pyym::o},{pysm::b,pyym::i}},//佛
{{pysm::k,pyym::ua},{pysm::h,pyym::ua},{pysm::nop,pyym::e},{pysm::w,pyym::u}},//侉
{{pysm::j,pyym::ia},{pysm::j,pyym::ie},{pysm::x,pyym::ia},{pysm::g,pyym::e}},//假
{{pysm::b,pyym::ang},{pysm::p,pyym::ang},{pysm::b,pyym::eng},{pysm::p,pyym::eng}},//傍
{{pysm::c,pyym::an},{pysm::s,pyym::an},{pysm::c,pyym::a},{pysm::s,pyym::en}},//傪
{{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::sh,pyym::an},{pysm::d,pyym::a}},//僤
{{pysm::x,pyym::ue},{pysm::x,pyym::iao},{pysm::q,pyym::iao},{pysm::sh,pyym::ao}},//削
{{pysm::sh,pyym::ao},{pysm::sh,pyym::uo},{pysm::zh,pyym::uo},{pysm::d,pyym::i}},//勺
{{pysm::b,pyym::ei},{pysm::b,pyym::i},{pysm::p,pyym::i},{pysm::b,pyym::an}},//卑
{{pysm::j,pyym::uan},{pysm::q,pyym::uan},{pysm::g,pyym::un},{pysm::j,pyym::un}},//卷
{{pysm::ch,pyym::ang},{pysm::h,pyym::an},{pysm::y,pyym::an},{pysm::nop,pyym::an}},//厂
{{pysm::c,pyym::an},{pysm::sh,pyym::en},{pysm::s,pyym::an},{pysm::c,pyym::en}},//參
{{pysm::zh,pyym::uo},{pysm::y,pyym::i},{pysm::l,pyym::i},{pysm::j,pyym::ue}},//叕
{{pysm::z,pyym::i},{pysm::c,pyym::i},{pysm::j,pyym::i},{pysm::x,pyym::i}},//呰
{{pysm::x,pyym::u},{pysm::h,pyym::ou},{pysm::g,pyym::ou},{pysm::g,pyym::u}},//呴
{{pysm::d,pyym::a},{pysm::y,pyym::a},{pysm::t,pyym::a},{pysm::d,pyym::an}},//呾
{{pysm::g,pyym::e},{pysm::k,pyym::a},{pysm::l,pyym::o},{pysm::l,pyym::uo}},//咯
{{pysm::d,pyym::uo},{pysm::ch,pyym::i},{pysm::zh,pyym::a},{pysm::d,pyym::ie}},//哆
{{pysm::h,pyym::a},{pysm::h,pyym::e},{pysm::t,pyym::a},{pysm::sh,pyym::a}},//哈
{{pysm::b,pyym::o},{pysm::p,pyym::o},{pysm::b,pyym::ei},{pysm::b,pyym::a}},//哱
{{pysm::g,pyym::eng},{pysm::y,pyym::ing},{pysm::n,pyym::g},{pysm::n,pyym::n}},//哽
{{pysm::w,pyym::u},{pysm::n,pyym::g},{pysm::m,pyym::m},{pysm::n,pyym::n}},//唔
{{pysm::f,pyym::ei},{pysm::p,pyym::ei},{pysm::p,pyym::ai},{pysm::b,pyym::ai}},//啡
{{pysm::h,pyym::uan},{pysm::y,pyym::uan},{pysm::x,pyym::uan},{pysm::h,pyym::e}},//喛
{{pysm::ch,pyym::an},{pysm::t,pyym::an},{pysm::t,pyym::uo},{pysm::d,pyym::an}},//嘽
{{pysm::zh,pyym::ou},{pysm::zh,pyym::uo},{pysm::zh,pyym::u},{pysm::d,pyym::u}},//噣
{{pysm::k,pyym::uai},{pysm::g,pyym::uai},{pysm::k,pyym::uo},{pysm::w,pyym::ei}},//噲
{{pysm::z,pyym::a},{pysm::n,pyym::ie},{pysm::y,pyym::an},{pysm::nop,pyym::e}},//囐
{{pysm::zh,pyym::en},{pysm::q,pyym::uan},{pysm::ch,pyym::ou},{pysm::h,pyym::uai}},//圳
{{pysm::f,pyym::u},{pysm::f,pyym::ou},{pysm::p,pyym::ei},{pysm::p,pyym::ou}},//垺
{{pysm::d,pyym::i},{pysm::t,pyym::i},{pysm::sh,pyym::i},{pysm::w,pyym::ei}},//堤
{{pysm::j,pyym::ia},{pysm::x,pyym::ie},{pysm::x,pyym::ia},{pysm::g,pyym::a}},//夾
{{pysm::q,pyym::i},{pysm::j,pyym::i},{pysm::nop,pyym::ai},{pysm::y,pyym::i}},//奇
{{pysm::x,pyym::ie},{pysm::l,pyym::ie},{pysm::x,pyym::i},{pysm::p,pyym::i}},//奊
{{pysm::q,pyym::i},{pysm::x,pyym::ie},{pysm::q,pyym::ie},{pysm::j,pyym::ie}},//契
{{pysm::j,pyym::ie},{pysm::j,pyym::u},{pysm::x,pyym::u},{pysm::z,pyym::u}},//姐
{{pysm::j,pyym::un},{pysm::x,pyym::un},{pysm::x,pyym::uan},{pysm::x,pyym::in}},//姰
{{pysm::sh,pyym::i},{pysm::t,pyym::i},{pysm::zh,pyym::i},{pysm::d,pyym::ai}},//媞
{{pysm::c,pyym::an},{pysm::ch,pyym::an},{pysm::j,pyym::ian},{pysm::zh,pyym::an}},//孱
{{pysm::w,pyym::an},{pysm::y,pyym::uan},{pysm::y,pyym::un},{pysm::y,pyym::u}},//宛
{{pysm::q,pyym::u},{pysm::j,pyym::ue},{pysm::q,pyym::ue},{pysm::j,pyym::u}},//屈
{{pysm::p,pyym::ing},{pysm::p,pyym::ian},{pysm::b,pyym::ing},{pysm::b,pyym::eng}},//平
{{pysm::c,pyym::e},{pysm::c,pyym::i},{pysm::z,pyym::e},{pysm::s,pyym::i}},//廁
{{pysm::j,pyym::u},{pysm::q,pyym::u},{pysm::c,pyym::u},{pysm::z,pyym::u}},//怚
{{pysm::d,pyym::ang},{pysm::sh,pyym::ang},{pysm::t,pyym::ang},{pysm::y,pyym::ang}},//愓
{{pysm::b,pyym::a},{pysm::p,pyym::a},{pysm::b,pyym::ai},{pysm::b,pyym::ie}},//扒
{{pysm::d,pyym::iao},{pysm::d,pyym::i},{pysm::y,pyym::ue},{pysm::l,pyym::i}},//扚
{{pysm::g,pyym::u},{pysm::q,pyym::i},{pysm::j,pyym::ie},{pysm::g,pyym::e}},//扢
{{pysm::n,pyym::e},{pysm::n,pyym::i},{pysm::n,pyym::a},{pysm::r,pyym::ui}},//抐
{{pysm::f,pyym::u},{pysm::b,pyym::i},{pysm::p,pyym::i},{pysm::f,pyym::ei}},//拂
{{pysm::ch,pyym::ai},{pysm::ch,pyym::e},{pysm::ch,pyym::i},{pysm::c,pyym::a}},//拆
{{pysm::r,pyym::ua},{pysm::r,pyym::uo},{pysm::s,pyym::ui},{pysm::l,pyym::uo}},//挼
{{pysm::r,pyym::uo},{pysm::w,pyym::o},{pysm::w,pyym::ei},{pysm::r,pyym::e}},//捼
{{pysm::z,pyym::uo},{pysm::c,pyym::u},{pysm::s,pyym::u},{pysm::z,pyym::un}},//捽
{{pysm::y,pyym::i},{pysm::n,pyym::i},{pysm::n,pyym::ai},{pysm::n,pyym::ie}},//掜
{{pysm::j,pyym::ie},{pysm::x,pyym::ie},{pysm::sh,pyym::a},{pysm::ch,pyym::a}},//接
{{pysm::t,pyym::i},{pysm::d,pyym::i},{pysm::ch,pyym::i},{pysm::sh,pyym::i}},//提
{{pysm::ch,pyym::uai},{pysm::d,pyym::uo},{pysm::zh,pyym::ui},{pysm::t,pyym::uan}},//揣
{{pysm::c,pyym::an},{pysm::sh,pyym::an},{pysm::ch,pyym::an},{pysm::s,pyym::en}},//摻
{{pysm::r,pyym::u},{pysm::n,pyym::u},{pysm::n,pyym::ou},{pysm::r,pyym::uan}},//擩
{{pysm::sh,pyym::e},{pysm::zh,pyym::e},{pysm::n,pyym::ie},{pysm::sh,pyym::a}},//攝
{{pysm::x,pyym::ie},{pysm::x,pyym::ia},{pysm::ch,pyym::a},{pysm::y,pyym::e}},//斜
{{pysm::f,pyym::ang},{pysm::p,pyym::ang},{pysm::w,pyym::ang},{pysm::f,pyym::eng}},//方
{{pysm::p,pyym::ang},{pysm::p,pyym::eng},{pysm::b,pyym::eng},{pysm::b,pyym::ang}},//旁
{{pysm::z,pyym::u},{pysm::s,pyym::ou},{pysm::c,pyym::ou},{pysm::z,pyym::ou}},//族
{{pysm::h,pyym::uang},{pysm::m,pyym::ang},{pysm::w,pyym::ang},{pysm::m,pyym::eng}},//朚
{{pysm::ch,pyym::ai},{pysm::c,pyym::i},{pysm::zh,pyym::ai},{pysm::z,pyym::i}},//柴
{{pysm::h,pyym::e},{pysm::h,pyym::u},{pysm::g,pyym::ai},{pysm::k,pyym::ai}},//核
{{pysm::b,pyym::ang},{pysm::b,pyym::ei},{pysm::p,pyym::ou},{pysm::p,pyym::ei}},//棓
{{pysm::b,pyym::ei},{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::p,pyym::ai}},//椑
{{pysm::zh,pyym::an},{pysm::ch,pyym::an},{pysm::n,pyym::ian},{pysm::zh,pyym::en}},//榐
{{pysm::b,pyym::ang},{pysm::b,pyym::eng},{pysm::p,pyym::ang},{pysm::p,pyym::eng}},//榜
{{pysm::t,pyym::ong},{pysm::ch,pyym::uang},{pysm::zh,pyym::ong},{pysm::ch,pyym::ong}},//橦
{{pysm::h,pyym::uang},{pysm::g,pyym::uang},{pysm::g,pyym::uo},{pysm::g,pyym::u}},//櫎
{{pysm::nop,pyym::ai},{pysm::nop,pyym::ê},{pysm::x,pyym::ie},{pysm::nop,pyym::ei}},//欸
{{pysm::l,pyym::v},{pysm::sh,pyym::u},{pysm::y,pyym::u},{pysm::d,pyym::ou}},//氀
{{pysm::zh,pyym::uo},{pysm::y,pyym::ue},{pysm::q,pyym::ue},{pysm::sh,pyym::uo}},//汋
{{pysm::d,pyym::un},{pysm::zh,pyym::uan},{pysm::t,pyym::un},{pysm::ch,pyym::un}},//沌
{{pysm::zh,pyym::an},{pysm::t,pyym::ian},{pysm::d,pyym::ian},{pysm::ch,pyym::an}},//沾
{{pysm::p,pyym::ai},{pysm::m,pyym::ai},{pysm::b,pyym::ai},{pysm::p,pyym::a}},//派
{{pysm::n,pyym::ao},{pysm::zh,pyym::ao},{pysm::zh,pyym::uo},{pysm::ch,pyym::uo}},//淖
{{pysm::q,pyym::ian},{pysm::j,pyym::ian},{pysm::c,pyym::an},{pysm::z,pyym::an}},//淺
{{pysm::k,pyym::e},{pysm::j,pyym::ie},{pysm::k,pyym::ai},{pysm::h,pyym::e}},//渴
{{pysm::j,pyym::ian},{pysm::z,pyym::an},{pysm::zh,pyym::an},{pysm::q,pyym::ian}},//湔
{{pysm::l,pyym::ian},{pysm::x,pyym::ian},{pysm::n,pyym::ian},{pysm::l,pyym::in}},//溓
{{pysm::sh,pyym::en},{pysm::s,pyym::en},{pysm::q,pyym::in},{pysm::l,pyym::in}},//滲
{{pysm::zh,pyym::uang},{pysm::ch,pyym::ong},{pysm::sh,pyym::uang},{pysm::ch,pyym::uang}},//漴
{{pysm::t,pyym::an},{pysm::x,pyym::un},{pysm::y,pyym::in},{pysm::d,pyym::an}},//潭
{{pysm::z,pyym::e},{pysm::sh,pyym::i},{pysm::y,pyym::i},{pysm::d,pyym::uo}},//澤
{{pysm::t,pyym::ao},{pysm::ch,pyym::ao},{pysm::sh,pyym::ou},{pysm::d,pyym::ao}},//濤
{{pysm::z,pyym::an},{pysm::c,pyym::uan},{pysm::q,pyym::ian},{pysm::z,pyym::a}},//灒
{{pysm::j,pyym::uan},{pysm::y,pyym::e},{pysm::y,pyym::ue},{pysm::y,pyym::uan}},//焆
{{pysm::j,pyym::iao},{pysm::q,pyym::iao},{pysm::j,pyym::ue},{pysm::zh,pyym::uo}},//燋
{{pysm::h,pyym::en},{pysm::y,pyym::an},{pysm::k,pyym::en},{pysm::h,pyym::ang}},//狠
{{pysm::y,pyym::i},{pysm::j,pyym::i},{pysm::nop,pyym::e},{pysm::w,pyym::ei}},//猗
{{pysm::x,pyym::ie},{pysm::h,pyym::e},{pysm::g,pyym::e},{pysm::h,pyym::ai}},//猲
{{pysm::j,pyym::ian},{pysm::y,pyym::in},{pysm::q,pyym::ian},{pysm::l,pyym::in}},//玪
{{pysm::d,pyym::ian},{pysm::t,pyym::ian},{pysm::sh,pyym::eng},{pysm::y,pyym::ing}},//甸
{{pysm::t,pyym::ing},{pysm::d,pyym::ing},{pysm::zh,pyym::eng},{pysm::t,pyym::ian}},//町
{{pysm::c,pyym::i},{pysm::z,pyym::i},{pysm::zh,pyym::ai},{pysm::j,pyym::i}},//疵
{{pysm::s,pyym::ui},{pysm::h,pyym::ui},{pysm::x,pyym::ie},{pysm::w,pyym::ei}},//眭
{{pysm::y,pyym::i},{pysm::z,pyym::e},{pysm::d,pyym::u},{pysm::g,pyym::ao}},//睪
{{pysm::h,pyym::uo},{pysm::x,pyym::ue},{pysm::y,pyym::ue},{pysm::w,pyym::o}},//矆
{{pysm::x,pyym::ian},{pysm::y,pyym::in},{pysm::k,pyym::en},{pysm::k,pyym::eng}},//硍
{{pysm::sh,pyym::ui},{pysm::t,pyym::uo},{pysm::t,pyym::ui},{pysm::t,pyym::uan}},//税
{{pysm::j,pyym::iao},{pysm::p,pyym::ao},{pysm::l,pyym::iao},{pysm::l,pyym::iu}},//窌
{{pysm::p,pyym::ou},{pysm::b,pyym::u},{pysm::f,pyym::u},{pysm::p,pyym::u}},//箁
{{pysm::x,pyym::u},{pysm::ch,pyym::u},{pysm::n,pyym::v},{pysm::n,pyym::a}},//絮
{{pysm::m,pyym::ian},{pysm::w,pyym::en},{pysm::m,pyym::an},{pysm::w,pyym::an}},//絻
{{pysm::s,pyym::ui},{pysm::sh,pyym::uai},{pysm::r,pyym::ui},{pysm::t,pyym::uo}},//綏
{{pysm::b,pyym::a},{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::b,pyym::ai}},//罷
{{pysm::n,pyym::ie},{pysm::zh,pyym::e},{pysm::sh,pyym::e},{pysm::y,pyym::e}},//聶
{{pysm::zh,pyym::un},{pysm::ch,pyym::un},{pysm::t,pyym::un},{pysm::zh,pyym::uo}},//肫
{{pysm::n,pyym::eng},{pysm::t,pyym::ai},{pysm::n,pyym::ai},{pysm::x,pyym::iong}},//能
{{pysm::x,pyym::iu},{pysm::y,pyym::ou},{pysm::t,pyym::iao},{pysm::x,pyym::iao}},//脩
{{pysm::sh,pyym::ao},{pysm::x,pyym::iao},{pysm::q,pyym::ue},{pysm::d,pyym::i}},//芍
{{pysm::f,pyym::a},{pysm::p,pyym::ei},{pysm::b,pyym::o},{pysm::b,pyym::a}},//茷
{{pysm::t,pyym::u},{pysm::ch,pyym::a},{pysm::y,pyym::e},{pysm::sh,pyym::u}},//荼
{{pysm::z,pyym::ou},{pysm::c,pyym::uan},{pysm::ch,pyym::u},{pysm::c,pyym::ong}},//菆
{{pysm::b,pyym::i},{pysm::p,pyym::i},{pysm::b,pyym::ei},{pysm::b,pyym::a}},//萆
{{pysm::w,pyym::ei},{pysm::h,pyym::ua},{pysm::k,pyym::ui},{pysm::nop,pyym::e}},//蒍
{{pysm::q,pyym::iu},{pysm::nop,pyym::ou},{pysm::x,pyym::u},{pysm::f,pyym::u}},//蓲
{{pysm::l,pyym::iao},{pysm::l,pyym::u},{pysm::l,pyym::ao},{pysm::l,pyym::iu}},//蓼
{{pysm::l,pyym::ou},{pysm::l,pyym::v},{pysm::j,pyym::u},{pysm::l,pyym::iu}},//蔞
{{pysm::b,pyym::i},{pysm::b,pyym::o},{pysm::b,pyym::ai},{pysm::p,pyym::i}},//薜
{{pysm::x,pyym::ian},{pysm::l,pyym::ian},{pysm::y,pyym::an},{pysm::k,pyym::an}},//薟
{{pysm::s,pyym::i},{pysm::x,pyym::i},{pysm::t,pyym::i},{pysm::zh,pyym::i}},//虒
{{pysm::b,pyym::ang},{pysm::b,pyym::eng},{pysm::p,pyym::i},{pysm::f,pyym::eng}},//蚌
{{pysm::sh,pyym::e},{pysm::y,pyym::i},{pysm::t,pyym::uo},{pysm::ch,pyym::i}},//蛇
{{pysm::l,pyym::a},{pysm::q,pyym::u},{pysm::zh,pyym::a},{pysm::j,pyym::i}},//蜡
{{pysm::sh,pyym::an},{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::t,pyym::uo}},//蟺
{{pysm::ch,pyym::i},{pysm::q,pyym::i},{pysm::d,pyym::uo},{pysm::n,pyym::uo}},//袳
{{pysm::j,pyym::iao},{pysm::j,pyym::ue},{pysm::l,pyym::u},{pysm::g,pyym::u}},//角
{{pysm::y,pyym::i},{pysm::d,pyym::an},{pysm::sh,pyym::i},{pysm::t,pyym::uo}},//訑
{{pysm::zh,pyym::an},{pysm::ch,pyym::e},{pysm::d,pyym::ian},{pysm::t,pyym::ie}},//詀
{{pysm::y,pyym::i},{pysm::t,pyym::uo},{pysm::d,pyym::uo},{pysm::x,pyym::i}},//詑
{{pysm::nop,pyym::ei},{pysm::x,pyym::i},{pysm::y,pyym::i},{pysm::nop,pyym::ê}},//誒
{{pysm::sh,pyym::uo},{pysm::sh,pyym::ui},{pysm::y,pyym::ue},{pysm::t,pyym::uo}},//説
{{pysm::k,pyym::ui},{pysm::d,pyym::ui},{pysm::t,pyym::ui},{pysm::g,pyym::ui}},//謉
{{pysm::c,pyym::an},{pysm::z,pyym::ao},{pysm::s,pyym::an},{pysm::ch,pyym::en}},//謲
{{pysm::b,pyym::o},{pysm::h,pyym::u},{pysm::h,pyym::uo},{pysm::g,pyym::ou}},//豰
{{pysm::h,pyym::ao},{pysm::h,pyym::e},{pysm::m,pyym::o},{pysm::m,pyym::a}},//貉
{{pysm::ch,pyym::uo},{pysm::ch,pyym::ao},{pysm::t,pyym::iao},{pysm::zh,pyym::uo}},//趠
{{pysm::q,pyym::u},{pysm::c,pyym::u},{pysm::c,pyym::ou},{pysm::z,pyym::ou}},//趣
{{pysm::n,pyym::ian},{pysm::j,pyym::ian},{pysm::ch,pyym::en},{pysm::t,pyym::ian}},//跈
{{pysm::d,pyym::ian},{pysm::t,pyym::ie},{pysm::d,pyym::ie},{pysm::zh,pyym::an}},//跕
{{pysm::j,pyym::u},{pysm::q,pyym::u},{pysm::q,pyym::ie},{pysm::zh,pyym::u}},//跙
{{pysm::ch,pyym::uo},{pysm::d,pyym::iao},{pysm::zh,pyym::uo},{pysm::t,pyym::iao}},//踔
{{pysm::ch,pyym::uai},{pysm::sh,pyym::uan},{pysm::d,pyym::uan},{pysm::ch,pyym::uan}},//踹
{{pysm::d,pyym::ai},{pysm::d,pyym::ie},{pysm::d,pyym::an},{pysm::zh,pyym::i}},//蹛
{{pysm::x,pyym::uan},{pysm::x,pyym::ian},{pysm::h,pyym::an},{pysm::j,pyym::ian}},//軒
{{pysm::g,pyym::e},{pysm::y,pyym::a},{pysm::nop,pyym::e},{pysm::q,pyym::ie}},//輵
{{pysm::zh,pyym::u},{pysm::d,pyym::i},{pysm::zh,pyym::ou},{pysm::t,pyym::un}},//逐
{{pysm::d,pyym::ou},{pysm::zh,pyym::u},{pysm::t,pyym::ou},{pysm::q,pyym::i}},//逗
{{pysm::sh,pyym::i},{pysm::d,pyym::i},{pysm::t,pyym::i},{pysm::zh,pyym::e}},//適
{{pysm::y,pyym::an},{pysm::l,pyym::ian},{pysm::x,pyym::ian},{pysm::j,pyym::ian}},//醶
{{pysm::l,pyym::i},{pysm::x,pyym::i},{pysm::l,pyym::ai},{pysm::t,pyym::ai}},//釐
{{pysm::j,pyym::ia},{pysm::g,pyym::e},{pysm::k,pyym::e},{pysm::h,pyym::a}},//鉿
{{pysm::y,pyym::ao},{pysm::d,pyym::iao},{pysm::t,pyym::iao},{pysm::q,pyym::iao}},//銚
{{pysm::b,pyym::ei},{pysm::p,pyym::i},{pysm::b,pyym::i},{pysm::p,pyym::o}},//陂
{{pysm::l,pyym::i},{pysm::d,pyym::ai},{pysm::y,pyym::i},{pysm::d,pyym::i}},//隶
{{pysm::zh,pyym::i},{pysm::k,pyym::ai},{pysm::y,pyym::i},{pysm::s,pyym::i}},//雉
{{pysm::x,pyym::u},{pysm::n,pyym::uo},{pysm::r,pyym::u},{pysm::r,pyym::uan}},//需
{{pysm::zh,pyym::a},{pysm::sh,pyym::a},{pysm::s,pyym::a},{pysm::y,pyym::i}},//霅
{{pysm::q,pyym::ian},{pysm::j,pyym::ian},{pysm::k,pyym::an},{pysm::h,pyym::an}},//靬
{{pysm::b,pyym::ing},{pysm::b,pyym::i},{pysm::p,pyym::i},{pysm::b,pyym::ei}},//鞞
{{pysm::b,pyym::ei},{pysm::f,pyym::u},{pysm::b,pyym::u},{pysm::b,pyym::ai}},//鞴
{{pysm::h,pyym::e},{pysm::h,pyym::an},{pysm::q,pyym::in},{pysm::g,pyym::e}},//頜
{{pysm::y,pyym::an},{pysm::q,pyym::in},{pysm::h,pyym::an},{pysm::q,pyym::ian}},//顩
{{pysm::z,pyym::ou},{pysm::zh,pyym::u},{pysm::zh,pyym::ou},{pysm::q,pyym::u}},//騶
{{pysm::j,pyym::iao},{pysm::x,pyym::iao},{pysm::j,pyym::u},{pysm::q,pyym::iao}},//驕
{{pysm::n,pyym::iao},{pysm::d,pyym::iao},{pysm::d,pyym::ao},{pysm::q,pyym::ue}},//鳥
{{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::zh,pyym::en},{pysm::sh,pyym::en}},//黮
{{pysm::k,pyym::en},{pysm::q,pyym::ian},{pysm::y,pyym::in},{pysm::k,pyym::un}},//齦
};
constexpr static PinYin5 s_pinyin5[] = { {{pysm::t,pyym::iao},{pysm::d,pyym::iao},{pysm::y,pyym::ao},{pysm::d,pyym::ao},{pysm::zh,pyym::ao}},//佻
{{pysm::ch,pyym::an},{pysm::sh,pyym::an},{pysm::t,pyym::an},{pysm::d,pyym::an},{pysm::zh,pyym::an}},//儃
{{pysm::q,pyym::u},{pysm::nop,pyym::ou},{pysm::g,pyym::ou},{pysm::q,pyym::iu},{pysm::k,pyym::ou}},//區
{{pysm::h,pyym::e},{pysm::h,pyym::a},{pysm::nop,pyym::a},{pysm::k,pyym::e},{pysm::h,pyym::uo}},//呵
{{pysm::h,pyym::u},{pysm::x,pyym::iao},{pysm::x,pyym::u},{pysm::h,pyym::e},{pysm::x,pyym::ia}},//呼
{{pysm::h,pyym::uai},{pysm::sh,pyym::i},{pysm::g,pyym::uo},{pysm::g,pyym::ua},{pysm::h,pyym::ua}},//咶
{{pysm::g,pyym::uo},{pysm::w,pyym::ai},{pysm::h,pyym::e},{pysm::w,pyym::o},{pysm::g,pyym::ua}},//咼
{{pysm::h,pyym::u},{pysm::x,pyym::iao},{pysm::g,pyym::uo},{pysm::x,pyym::ia},{pysm::h,pyym::ao}},//唬
{{pysm::zh,pyym::ao},{pysm::zh,pyym::ou},{pysm::d,pyym::ao},{pysm::t,pyym::iao},{pysm::d,pyym::iao}},//啁
{{pysm::t,pyym::un},{pysm::zh,pyym::un},{pysm::x,pyym::iang},{pysm::t,pyym::ui},{pysm::d,pyym::ui}},//啍
{{pysm::c,pyym::ui},{pysm::z,pyym::u},{pysm::z,pyym::a},{pysm::nop,pyym::e},{pysm::ch,pyym::uai}},//啐
{{pysm::sh,pyym::a},{pysm::z,pyym::a},{pysm::j,pyym::ie},{pysm::d,pyym::ie},{pysm::t,pyym::i}},//啑
{{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::sh,pyym::an},{pysm::zh,pyym::an},{pysm::t,pyym::an}},//單
{{pysm::x,pyym::iao},{pysm::j,pyym::iao},{pysm::l,pyym::ao},{pysm::b,pyym::ao},{pysm::m,pyym::iu}},//嘐
{{pysm::d,pyym::ian},{pysm::t,pyym::ing},{pysm::d,pyym::ing},{pysm::zh,pyym::eng},{pysm::z,pyym::un}},//奠
{{pysm::ch,pyym::a},{pysm::ch,pyym::ai},{pysm::c,pyym::i},{pysm::c,pyym::uo},{pysm::j,pyym::ie}},//差
{{pysm::x,pyym::i},{pysm::h,pyym::u},{pysm::h,pyym::ui},{pysm::s,pyym::uo},{pysm::y,pyym::i}},//戲
{{pysm::b,pyym::a},{pysm::b,pyym::o},{pysm::b,pyym::ie},{pysm::f,pyym::a},{pysm::b,pyym::ei}},//拔
{{pysm::p,pyym::an},{pysm::b,pyym::ian},{pysm::f,pyym::en},{pysm::f,pyym::an},{pysm::p,pyym::in}},//拚
{{pysm::q,pyym::ie},{pysm::q,pyym::i},{pysm::j,pyym::ia},{pysm::q,pyym::ia},{pysm::sh,pyym::i}},//挈
{{pysm::y,pyym::u},{pysm::ch,pyym::ou},{pysm::y,pyym::ou},{pysm::sh,pyym::u},{pysm::y,pyym::ao}},//揄
{{pysm::j,pyym::iu},{pysm::l,pyym::iu},{pysm::l,pyym::iao},{pysm::j,pyym::iao},{pysm::n,pyym::ao}},//摎
{{pysm::r,pyym::uan},{pysm::r,pyym::ui},{pysm::r,pyym::un},{pysm::r,pyym::uo},{pysm::s,pyym::ui}},//撋
{{pysm::c,pyym::uo},{pysm::z,pyym::uo},{pysm::z,pyym::ui},{pysm::z,pyym::uan},{pysm::ch,pyym::ua}},//撮
{{pysm::b,pyym::iao},{pysm::sh,pyym::ao},{pysm::sh,pyym::uo},{pysm::d,pyym::i},{pysm::zh,pyym::uo}},//杓
{{pysm::l,pyym::i},{pysm::zh,pyym::i},{pysm::y,pyym::i},{pysm::t,pyym::uo},{pysm::d,pyym::uo}},//杝
{{pysm::b,pyym::a},{pysm::f,pyym::u},{pysm::b,pyym::o},{pysm::b,pyym::ie},{pysm::p,pyym::ei}},//柭
{{pysm::l,pyym::e},{pysm::y,pyym::ue},{pysm::y,pyym::ao},{pysm::l,pyym::uo},{pysm::l,pyym::iao}},//樂
{{pysm::sh,pyym::a},{pysm::sh,pyym::ai},{pysm::s,pyym::a},{pysm::x,pyym::ie},{pysm::sh,pyym::i}},//殺
{{pysm::x,pyym::ie},{pysm::d,pyym::ie},{pysm::zh,pyym::a},{pysm::y,pyym::i},{pysm::q,pyym::ie}},//渫
{{pysm::p,pyym::u},{pysm::f,pyym::u},{pysm::b,pyym::u},{pysm::b,pyym::o},{pysm::p,pyym::o}},//溥
{{pysm::r,pyym::u},{pysm::r,pyym::uan},{pysm::nop,pyym::er},{pysm::n,pyym::uan},{pysm::n,pyym::uo}},//濡
{{pysm::s,pyym::a},{pysm::x,pyym::ian},{pysm::x,pyym::i},{pysm::l,pyym::i},{pysm::sh,pyym::i}},//灑
{{pysm::h,pyym::ui},{pysm::h,pyym::un},{pysm::y,pyym::un},{pysm::x,pyym::un},{pysm::x,pyym::uan}},//煇
{{pysm::f,pyym::an},{pysm::p,pyym::an},{pysm::b,pyym::o},{pysm::p,pyym::o},{pysm::p,pyym::i}},//番
{{pysm::ch,pyym::un},{pysm::zh,pyym::un},{pysm::t,pyym::un},{pysm::q,pyym::uan},{pysm::z,pyym::i}},//純
{{pysm::j,pyym::ie},{pysm::x,pyym::ie},{pysm::q,pyym::ia},{pysm::j,pyym::ia},{pysm::q,pyym::i}},//絜
{{pysm::sh,pyym::an},{pysm::x,pyym::ian},{pysm::x,pyym::iao},{pysm::s,pyym::ao},{pysm::c,pyym::an}},//縿
{{pysm::n,pyym::i},{pysm::r,pyym::uan},{pysm::n,pyym::ao},{pysm::n,pyym::en},{pysm::nop,pyym::er}},//腝
{{pysm::n,pyym::ao},{pysm::r,pyym::u},{pysm::nop,pyym::er},{pysm::n,pyym::en},{pysm::n,pyym::uan}},//臑
{{pysm::f,pyym::u},{pysm::b,pyym::o},{pysm::f,pyym::ei},{pysm::b,pyym::ei},{pysm::b,pyym::i}},//茀
{{pysm::zh,pyym::u},{pysm::zh,pyym::e},{pysm::zh,pyym::uo},{pysm::ch,pyym::u},{pysm::zh,pyym::ao}},//著
{{pysm::z,pyym::e},{pysm::c,pyym::uo},{pysm::z,pyym::uo},{pysm::zh,pyym::a},{pysm::j,pyym::ie}},//諎
{{pysm::b,pyym::ao},{pysm::b,pyym::o},{pysm::zh,pyym::uo},{pysm::ch,pyym::uo},{pysm::p,pyym::ao}},//趵
{{pysm::c,pyym::un},{pysm::q,pyym::un},{pysm::z,pyym::un},{pysm::q,pyym::iu},{pysm::zh,pyym::un}},//踆
{{pysm::d,pyym::i},{pysm::zh,pyym::i},{pysm::t,pyym::i},{pysm::ch,pyym::i},{pysm::sh,pyym::i}},//踶
{{pysm::d,pyym::un},{pysm::z,pyym::un},{pysm::c,pyym::un},{pysm::c,pyym::uan},{pysm::q,pyym::un}},//蹲
{{pysm::j,pyym::ue},{pysm::q,pyym::iao},{pysm::j,pyym::iao},{pysm::j,pyym::u},{pysm::x,pyym::ue}},//蹻
{{pysm::n,pyym::a},{pysm::n,pyym::uo},{pysm::n,pyym::ei},{pysm::n,pyym::e},{pysm::n,pyym::ai}},//那
{{pysm::x,pyym::ie},{pysm::y,pyym::a},{pysm::y,pyym::e},{pysm::x,pyym::u},{pysm::sh,pyym::e}},//邪
{{pysm::sh,pyym::i},{pysm::sh,pyym::e},{pysm::y,pyym::i},{pysm::t,pyym::uo},{pysm::t,pyym::a}},//鉈
{{pysm::nop,pyym::ai},{pysm::h,pyym::e},{pysm::h,pyym::ai},{pysm::g,pyym::ai},{pysm::k,pyym::ai}},//閡
{{pysm::g,pyym::ui},{pysm::x,pyym::ie},{pysm::h,pyym::ua},{pysm::w,pyym::a},{pysm::k,pyym::ui}},//鮭
{{pysm::q,pyym::i},{pysm::j,pyym::i},{pysm::z,pyym::i},{pysm::zh,pyym::ai},{pysm::j,pyym::ian}},//齊
};
constexpr static PinYin6 s_pinyin6[] = { {{pysm::n,pyym::a},{pysm::n,pyym::e},{pysm::n,pyym::uo},{pysm::n,pyym::ai},{pysm::n,pyym::ie},{pysm::n,pyym::ei}},//哪
{{pysm::d,pyym::an},{pysm::ch,pyym::an},{pysm::t,pyym::an},{pysm::zh,pyym::an},{pysm::sh,pyym::an},{pysm::t,pyym::ian}},//撣
{{pysm::s,pyym::a},{pysm::x,pyym::i},{pysm::x,pyym::ian},{pysm::s,pyym::en},{pysm::c,pyym::ui},{pysm::x,pyym::un}},//洒
{{pysm::ch,pyym::u},{pysm::z,pyym::u},{pysm::zh,pyym::u},{pysm::j,pyym::u},{pysm::ch,pyym::a},{pysm::x,pyym::u}},//鉏
};
constexpr static PinYin7 s_pinyin7[] = { {{pysm::d,pyym::un},{pysm::d,pyym::ui},{pysm::t,pyym::uan},{pysm::d,pyym::iao},{pysm::d,pyym::ao},{pysm::zh,pyym::un},{pysm::t,pyym::un}},//敦
{{pysm::zh,pyym::an},{pysm::ch,pyym::en},{pysm::d,pyym::an},{pysm::t,pyym::an},{pysm::j,pyym::in},{pysm::y,pyym::in},{pysm::sh,pyym::en}},//湛
{{pysm::m,pyym::ou},{pysm::j,pyym::iu},{pysm::m,pyym::iu},{pysm::m,pyym::u},{pysm::m,pyym::iao},{pysm::l,pyym::iao},{pysm::l,pyym::u}},//繆
{{pysm::j,pyym::u},{pysm::ch,pyym::a},{pysm::zh,pyym::a},{pysm::z,pyym::u},{pysm::j,pyym::ie},{pysm::b,pyym::ao},{pysm::x,pyym::ie}},//苴
{{pysm::b,pyym::i},{pysm::f,pyym::en},{pysm::b,pyym::en},{pysm::f,pyym::ei},{pysm::b,pyym::an},{pysm::l,pyym::u},{pysm::p,pyym::an}},//賁
};
constexpr static PinYin8 s_pinyin8[] = { 
	{{pysm::k,pyym::a},{pysm::q,pyym::ia},{pysm::j,pyym::ia},{pysm::zh,pyym::a},{pysm::g,pyym::ua},{pysm::y,pyym::e},{pysm::g,pyym::e},{pysm::l,pyym::ie}},//擖
};


constexpr  auto s_pinyin2_cout = sizeof(s_pinyin2) / sizeof(PinYin2);
constexpr  auto s_pinyin3_cout = sizeof(s_pinyin3) / sizeof(PinYin3);
constexpr  auto s_pinyin4_cout = sizeof(s_pinyin4) / sizeof(PinYin4);
constexpr  auto s_pinyin5_cout = sizeof(s_pinyin5) / sizeof(PinYin5);
constexpr  auto s_pinyin6_cout = sizeof(s_pinyin6) / sizeof(PinYin6);
constexpr  auto s_pinyin7_cout = sizeof(s_pinyin7) / sizeof(PinYin7);
constexpr  auto s_pinyin8_cout = sizeof(s_pinyin8) / sizeof(PinYin8);

/*为了兼容C++17没使用span,迭代器也好使*/
inline const PinYin* GetMultiPinyinPtr(std::uint8_t& count, const std::uint16_t index) {
	if (index < 0) {
		count = 0;
		return nullptr;  // 处理无效索引
	}

	switch (count) {
	case 2:
		if (index < s_pinyin2_cout) {
			return s_pinyin2[index];
		}
		break;
	case 3:
		if (index < s_pinyin3_cout) {
			return s_pinyin3[index];
		}
		break;
	case 4:
		if (index < s_pinyin4_cout) {
			return s_pinyin4[index];
		}
		break;
	case 5:
		if (index < s_pinyin5_cout) {
			return s_pinyin5[index];
		}
		break;
	case 6:
		if (index < s_pinyin6_cout) {
			return s_pinyin6[index];
		}
		break;
	case 7:
		if (index < s_pinyin7_cout) {
			return s_pinyin7[index];
		}
		break;
	case 8:
		if (index < s_pinyin8_cout) {
			return s_pinyin8[index];
		}
		break;
	default:
		break;
	}
	count = 0;
	return nullptr;  // 返回空指针或者处理错误
}
inline auto GetPinyinStruct(const wchar_t ch, std::uint8_t& count) -> const PinYin* {
	count = 0;
	/*非中文*/
	if (ch< MIN_CN_CHAR_UNICODE_VALUE || ch>MAX_CN_CHAR_UNICODE_VALUE)
		return nullptr;
	const auto& info = all_pinyin + ch - MIN_CN_CHAR_UNICODE_VALUE;
	count = info->MultiCount;
	if (count == 0)
		return nullptr;
	if (count > 1)
		return GetMultiPinyinPtr(count, info->MultiIndex);
	return &info->MultiTone;
}
/*因为是码表,所以返回的直接就是静态变量*/
inline auto GetSm(const wchar_t ch, int index)->const wchar_t* {
	if (index <= 0)return nullptr;
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || index > count)
		return nullptr;
	return GetPinyinSm(pinyin[index - 1].sm);
}
inline auto GetYm(const wchar_t ch, int index) -> const wchar_t* {
	if (index <= 0)return nullptr;
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || index > count)
		return nullptr;
	return GetPinyinYm(pinyin[index - 1].ym);
}
inline auto GetPinyin(const wchar_t ch, int index) -> std::wstring {
	if (index <= 0)return {};
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || index > count)
		return {};
	std::wstring ret{ GetPinyinSm(pinyin[index - 1].sm) };
	return ret + GetPinyinYm(pinyin[index - 1].ym);
}

inline auto GetPinyinW(const wchar_t ch, int index) -> LPBYTE {
	if (index <= 0)return {};
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || index > count)
		return {};

	auto sm = GetPinyinSm(pinyin[index - 1].sm), ym = GetPinyinYm(pinyin[index - 1].ym);
	auto sizesm = wcslen(sm) * sizeof(wchar_t), sizeym= wcslen(ym) * sizeof(wchar_t);
	auto nDataSize = sizesm + sizeym + sizeof(L'\0');
	LPBYTE pd = static_cast<LPBYTE>(elibstl::ealloc(sizeof(std::uint32_t) * 2 + nDataSize));
	if (sizesm != 0)
		std::copy(sm, sm + sizesm, pd + sizeof(std::uint32_t) * 2);
	if (sizeym)
		std::copy(ym, ym + sizeym, pd + sizeof(std::uint32_t) * 2 + sizesm);
	*reinterpret_cast<std::uint32_t*>(pd) = 1;
	*reinterpret_cast<std::uint32_t*>(pd + sizeof(std::uint32_t)) = nDataSize;
	return pd;
}

inline auto GetAllPinyin(const wchar_t ch) -> std::vector<std::wstring> {
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || count == 0)
		return {};
	std::vector<std::wstring> ret;
	for (std::uint8_t i = 0; i < count;  i++)
	{
		std::wstring str{ GetPinyinSm(pinyin[i].sm) };
		str += GetPinyinYm(pinyin[i].ym);
		ret.push_back(str);
	}
	return  ret;
}

inline auto GetAllPinyinW(const wchar_t ch) -> void* {
	std::uint8_t count = 0;
	const auto pinyin = GetPinyinStruct(ch, count);
	if (pinyin == nullptr || count == 0)
		return empty_array();

	const auto p = reinterpret_cast<void**>(malloc_array<LPBYTE>(count));
	const auto arr = p + 2;
	for (std::uint8_t index = 0; index < count; index++)
	{
		auto sm = GetPinyinSm(pinyin[index].sm), ym = GetPinyinYm(pinyin[index].ym);
		auto sizesm = wcslen(sm) * sizeof(wchar_t), sizeym = wcslen(ym) * sizeof(wchar_t);
		auto nDataSize = sizesm + sizeym + sizeof(L'\0');
		LPBYTE pd = static_cast<LPBYTE>(elibstl::ealloc(sizeof(std::uint32_t) * 2 + nDataSize));
		if (sizesm != 0)
			std::copy(sm, sm + sizesm, pd + sizeof(std::uint32_t) * 2);
		if (sizeym)
			std::copy(ym, ym + sizeym, pd + sizeof(std::uint32_t) * 2 + sizesm);
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(std::uint32_t)) = nDataSize;
		arr[index] = pd;
	}
	return p;
}

/*获取整个字符串的拼音
* @ 字符串
* @ 是否保留无拼音字符
*/
inline auto GetStrPinyin(const std::wstring_view& text, bool preserveNonChinese = true) {
	std::wstring str;
	for (const auto& ch : text)
	{
		auto py = GetPinyin(ch, 1);
		if (py.empty() && preserveNonChinese)
			str.push_back(ch);
		else
			str += py;

		if (!py.empty()) {
			str.push_back(L' ');
		}
	}

	// 移除最后一个多余的空格
	if (!str.empty()) {
		str.pop_back();
	}

	return str;
}

/*获取整个字符串的拼音,无空格*/
inline auto GetStrPinyinNoNop(const std::wstring_view& text, bool preserveNonChinese = true) {
	std::wstring str;
	for (const auto& ch : text)
	{
		auto py = GetPinyin(ch, 1);
		if (py.empty() && preserveNonChinese) 
			str.push_back(ch);
		else
			str += py;
	}
	return str;
}

/*获取文本拼音的开头一个字符*/
inline auto GetStrPinyinFirst(const std::wstring_view& text) {
	std::wstring str;
	for (const auto& ch : text)
	{
		auto py = GetPinyin(ch, 1);
		if (py.empty())
			str.push_back(ch);
		else
			str.push_back(py[0]);
	}
	return str;
}
//检查整个字符串是否包含声母和韵母的组合
inline bool IsAllSpelled(const std::wstring_view& text) {
	constexpr static const wchar_t* PinYinSmNoNop[] = {
		L"b",L"c",L"d",L"f",L"g",L"h",L"j",L"k",L"l",L"m",L"n",L"p",L"q",L"r",L"s",L"t",L"w",L"x",L"y",L"z",L"ch",L"sh",L"zh"
	};

	/*韵母表对照*/
	constexpr static const wchar_t* PinYinYmNoNop[] = {
		L"a",	L"ai",	L"an",	L"ang",	L"ao",	L"e",	L"ei",	L"en",	L"eng",	L"er",	L"g",	L"i",	L"ia",	L"ian",	L"iang",	L"iao",	L"ie",	L"in",	L"ing",	L"iong",	L"iu",L"m",L"n",	L"ng",	L"o",	L"ong",	L"ou",	L"u",	L"ua",	L"uai",	L"uan",	L"uang",	L"ue",	L"ui",	L"un",	L"uo",	L"v",	L"ve",	L"ê"
	};
	size_t i = 0;
	while (i < text.length()) {
		bool found_sm = false;
		for (const wchar_t* sm : PinYinSmNoNop) {
			if (text.substr(i).find(sm) == 0) {
				i += wcslen(sm);
				found_sm = true;
				break;
			}
		}
		if (found_sm) {/*如果找到声母,那么继续判断其后是否为韵母*/
			bool found_ym = false;
			for (const wchar_t* ym : PinYinYmNoNop) {
				const auto size = wcslen(ym);
				if (i + size <= text.length() && text.substr(i, size) == ym) {
					i += size;
					return true;
				}
			}
		}
		i++;
	}
	return false;  // 所有声母和韵母都被找到，返回true
}


}

#endif