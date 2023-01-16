#pragma once
//字符串拼接重载运算符，也可使使用字符串拼接函数
std::vector<unsigned char> operator+(const std::vector<unsigned char>& 字节集1, const std::vector<unsigned char>& 字节集2);

#pragma region 到字节集
vector<unsigned char> 到字节集(const string& 欲转换为字节集的数据);
vector<unsigned char> 到字节集(const wstring& 欲转换为字节集的数据);
vector<unsigned char> 到字节集(unsigned char 欲转换为字节集的数据);
vector<unsigned char> 到字节集(short 欲转换为字节集的数据);
vector<unsigned char> 到字节集(long long 欲转换为字节集的数据);
vector<unsigned char> 到字节集(float 欲转换为字节集的数据);
vector<unsigned char> 到字节集(double 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<unsigned char> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<int> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<short> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<long long> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<double> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(vector<float> 欲转换为字节集的数据);
vector<unsigned char> 到字节集(char* 欲转换为字节集的数据);
vector<unsigned char> 到字节集(const char* 欲转换为字节集的数据);
vector<unsigned char> 到字节集(const wchar_t* 欲转换为字节集的数据);
vector<unsigned char> 到字节集(wchar_t* 欲转换为字节集的数据);

/*****************万物皆可机器码 *************/
template<typename Type>
vector<unsigned char> 到字节集(const std::vector<Type>& 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		return {};
	}
	return	vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)欲转换为字节集的数据.data() + 欲转换为字节集的数据.size() * sizeof(Type)));
};
template<typename Type>
vector<unsigned char> 到字节集(const Type& 欲转换为字节集的数据) {//大型结构体防止拷贝，保证数据结构的执行效率
	return  vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据 + sizeof(Type)));
};
/*****************万物皆可机器码 *************/
#pragma endregion
/*C中作用很小的几个宏*/
#define 指针到整数(内存数据指针)  *(int*)内存数据指针
#define 指针到双精度小数(内存数据指针)  *(double*)内存数据指针
#define 指针到小数(内存数据指针)  *(float*)内存数据指针
#define 取字节集数据(字节集数据,起始位置,数据类型)  (*((数据类型*)(字节集数据.data() + 起始位置)))


size_t 取字节集长度(const vector<unsigned char>& 字节集数据);
/*调用格式： 〈字节集〉 取字节集左边 （字节集 欲取其部分的字节集，整数型 欲取出字节的数目） - 系统核心支持库->字节集操作
   英文名称：BinLeft
   返回一个字节集，其中包含指定字节集中从左边算起指定数量的字节。本命令为初级命令。
   参数<1>的名称为“欲取其部分的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲取出字节的数目”，类型为“整数型（int）”。

   操作系统需求： Windows、Linux
*/
vector<unsigned char> 取字节集左边(const vector<unsigned char>& 欲取其部分的字节集, size_t 欲取出字节的数目);
/* 调用格式： 〈字节集〉 取字节集右边 （字节集 欲取其部分的字节集，整数型 欲取出字节的数目） - 系统核心支持库->字节集操作
   英文名称：BinRight
   返回一个字节集，其中包含指定字节集中从右边算起指定数量的字节。本命令为初级命令。
   参数<1>的名称为“欲取其部分的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲取出字节的数目”，类型为“整数型（int）”。

   操作系统需求： Windows、Linux*/
vector<unsigned char> 取字节集右边(const vector<unsigned char>& 欲取其部分的字节集, size_t 欲取出字节的数目);
/*    调用格式： 〈字节集〉 取字节集中间 （字节集 欲取其部分的字节集，整数型 起始取出位置，整数型 欲取出字节的数目） - 系统核心支持库->字节集操作
   英文名称：BinMid
   返回一个字节集，其中包含指定字节集中从指定位置算起指定数量的字节。本命令为初级命令。
   参数<1>的名称为“欲取其部分的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“起始取出位置”，类型为“整数型（int）”。1为首位置，2为第2个位置，如此类推。
   参数<3>的名称为“欲取出字节的数目”，类型为“整数型（int）”。

   操作系统需求： Windows、Linux
*/
vector<unsigned char> 取字节集中间(const vector<unsigned char>& 欲取其部分的字节集, size_t 起始取出位置, size_t 欲取出字节的数目);
/*  调用格式： 〈字节集〉 字节集替换 （字节集 欲替换其部分的字节集，整数型 起始替换位置，整数型 替换长度，［字节集 用作替换的字节集］） - 系统核心支持库->字节集操作
   英文名称：RpBin
   将指定字节集的某一部分用其它的字节集替换，然后返回替换后的结果。本命令为初级命令。
   参数<1>的名称为“欲替换其部分的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“起始替换位置”，类型为“整数型（int）”。替换的起始位置，1为首位置，2为第2个位置，如此类推。
   参数<3>的名称为“替换长度”，类型为“整数型（int）”。
   参数<4>的名称为“用作替换的字节集”，类型为“字节集（bin）”，可以被省略。如果本参数被省略，则删除字节集中的指定部分。

   操作系统需求： Windows、Linux*/
vector<unsigned char> 字节集替换(const vector<unsigned char>& 欲替换其部分的字节集, size_t 起始替换位置, size_t 替换长度, const vector<unsigned char>& 用作替换的字节集);
/*
   调用格式： 〈字节集〉 子字节集替换 （字节集 欲被替换的字节集，字节集 欲被替换的子字节集，［字节集 用作替换的子字节集］，［整数型 进行替换的起始位置］，［整数型 替换进行的次数］） - 系统核心支持库->字节集操作
   英文名称：RpSubBin
   返回一个字节集，该字节集中指定的子字节集已被替换成另一子字节集，并且替换发生的次数也是被指定的。本命令为初级命令。
   参数<1>的名称为“欲被替换的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲被替换的子字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“用作替换的子字节集”，类型为“字节集（bin）”，可以被省略。如果省略本参数，则默认为空字节集。
   参数<4>的名称为“进行替换的起始位置”，类型为“整数型（intptr_t）”，可以被省略。被替换子字节集的起始搜索位置。如果省略，默认从1开始。
   参数<5>的名称为“替换进行的次数”，类型为“整数型（intptr_t）”，可以被省略。对子字节集进行替换的次数。如果省略，默认进行所有可能的替换。
*/
vector<unsigned char> 子字节集替换(const vector<unsigned char>& 欲被替换的字节集, const vector<unsigned char>& 欲被替换的子字节集, const vector<unsigned char>& 用作替换的子字节集 = vector<unsigned char>(), size_t 进行替换的起始位置 = 1);
/*
   调用格式： 〈字节集〉 子字节集替换 （字节集 欲被替换的字节集，字节集 欲被替换的子字节集，［字节集 用作替换的子字节集］，［整数型 进行替换的起始位置］，［整数型 替换进行的次数］） - 系统核心支持库->字节集操作
   英文名称：RpSubBin
   返回一个字节集，该字节集中指定的子字节集已被替换成另一子字节集，并且替换发生的次数也是被指定的。本命令为初级命令。
   参数<1>的名称为“欲被替换的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲被替换的子字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“用作替换的子字节集”，类型为“字节集（bin）”，可以被省略。如果省略本参数，则默认为空字节集。
   参数<4>的名称为“进行替换的起始位置”，类型为“整数型（intptr_t）”，可以被省略。被替换子字节集的起始搜索位置。如果省略，默认从1开始。
   参数<5>的名称为“替换进行的次数”，类型为“整数型（intptr_t）”，可以被省略。对子字节集进行替换的次数。如果省略，默认进行所有可能的替换。
*/
vector<unsigned char> 子字节集替换(vector<unsigned char> 欲被替换的字节集, vector<unsigned char> 欲被替换的子字节集, vector<unsigned char> 用作替换的子字节集, size_t 进行替换的起始位置, size_t 替换进行的次数);
std::vector<unsigned char> 取重复字节集(size_t 重复次数, const std::vector<unsigned char>& 待重复的字节集);
/*    调用格式： 〈字节集数组〉 分割字节集 （字节集 待分割字节集，［字节集 用作分割的字节集］，［整数型 要返回的子字节集数目］） - 系统核心支持库->字节集操作
   英文名称：SplitBin
   将指定字节集进行分割，返回分割后的一维字节集数组。本命令为初级命令。
   参数<1>的名称为“待分割字节集”，类型为“字节集（bin）”。如果参数值是一个长度为零的字节集，则返回一个空数组，即没有任何成员的数组。
   参数<2>的名称为“用作分割的字节集”，类型为“字节集（bin）”，可以被省略。用于标识子字节集边界。本参数如果被省略，则默认使用字节 0 作为分隔符。
   参数<3>的名称为“要返回的子字节集数目”，类型为“整数型（int）”，可以被省略。如果被省略，则默认返回所有的子字节集。

   操作系统需求： Windows、Linux*/
std::vector<std::vector<unsigned char>> 分割字节集(const std::vector<unsigned char>& 待分割字节集, const  std::vector<unsigned char>& 用作分割的字节集);
/*    调用格式： 〈字节集数组〉 分割字节集 （字节集 待分割字节集，［字节集 用作分割的字节集］，［整数型 要返回的子字节集数目］） - 系统核心支持库->字节集操作
   英文名称：SplitBin
   将指定字节集进行分割，返回分割后的一维字节集数组。本命令为初级命令。
   参数<1>的名称为“待分割字节集”，类型为“字节集（bin）”。如果参数值是一个长度为零的字节集，则返回一个空数组，即没有任何成员的数组。
   参数<2>的名称为“用作分割的字节集”，类型为“字节集（bin）”，可以被省略。用于标识子字节集边界。本参数如果被省略，则默认使用字节 0 作为分隔符。
   参数<3>的名称为“要返回的子字节集数目”，类型为“整数型（int）”，可以被省略。如果被省略，则默认返回所有的子字节集。

   操作系统需求： Windows、Linux*/
std::vector<std::vector<unsigned char>> 分割字节集(const std::vector<unsigned char>& 待分割字节集, const  std::vector<unsigned char>& 用作分割的字节集, intptr_t  要返回的子字节集数目);
vector<unsigned char> 指针到字节集(void* 内存数据指针, size_t 内存数据长度);


int 取字节集内整数(const std::vector<unsigned char>& 待处理的字节集, size_t 欲获取整数所处偏移, bool 是否反转字节序 = false);
void 置字节集内整数(vector<unsigned char> 待处理的字节集, size_t 欲设置整数所处偏移, int 欲设置的整数值, bool 是否反转字节序);
vector<unsigned char>  取空白字节集(size_t  零字节数目);

#pragma region 字节集搜索
/*    调用格式： 〈整数型〉 寻找字节集 （字节集 被搜寻的字节集，字节集 欲寻找的字节集，［整数型 起始搜寻位置］） - 系统核心支持库->字节集操作
   英文名称：InBin
   返回一字节集在另一字节集中最先出现的位置，位置值从 1 开始。如果未找到，返回 -1。本命令为初级命令。
   参数<1>的名称为“被搜寻的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲寻找的字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“起始搜寻位置”，类型为“整数型（int）”，可以被省略。1为首位置，2为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。
   操作系统需求： Windows、Linux
*/
size_t 寻找字节集(const vector<unsigned char>& 被搜寻的字节集, const vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置 = 1);

/*    调用格式： 〈整数型〉 寻找字节集 （字节集 被搜寻的字节集，字节集 欲寻找的字节集，［整数型 起始搜寻位置］） - 系统核心支持库->字节集操作
   英文名称：InBin
   返回一字节集在另一字节集中最先出现的位置下标，下标值 0 开始。如果未找到，返回 -1。本命令为初级命令。
   参数<1>的名称为“被搜寻的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲寻找的字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“起始搜寻位置”，类型为“整数型（int）”，可以被省略。1为首位置，2为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。
   操作系统需求： Windows、Linux
*/
size_t 寻找字节集下标(const vector<unsigned char>& 被搜寻的字节集, const vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置 = -1);
/*    调用格式： 〈整数型〉 倒找字节集 （字节集 被搜寻的字节集，字节集 欲寻找的字节集，［整数型 起始搜寻位置］） - 系统核心支持库->字节集操作
   英文名称：InBinRev
   也就是下标加1
   返回一字节集在另一字节集中最后出现的位置，位置值从 1 开始。如果未找到，返回 -1。本命令为初级命令。
   参数<1>的名称为“被搜寻的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲寻找的字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“起始搜寻位置”，类型为“整数型（int）”，可以被省略。1为首位置，2为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。

   操作系统需求： Windows、Linux*/
intptr_t 倒找字节集(const std::vector<unsigned char>& 被搜寻的字节集, const std::vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置);

/*    调用格式： 〈整数型〉 倒找字节集 （字节集 被搜寻的字节集，字节集 欲寻找的字节集，［整数型 起始搜寻位置］） - 系统核心支持库->字节集操作
   英文名称：InBinRev
   返回一字节集在另一字节集中最后出现的位置，位置值从 1 开始。如果未找到，返回 -1。本命令为初级命令。
	  也就是下标加1
   参数<1>的名称为“被搜寻的字节集”，类型为“字节集（bin）”。
   参数<2>的名称为“欲寻找的字节集”，类型为“字节集（bin）”。
   参数<3>的名称为“起始搜寻位置”，类型为“整数型（int）”，可以被省略。1为首位置，2为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。

   操作系统需求： Windows、Linux*/
intptr_t 倒找字节集(const std::vector<unsigned char>& 被搜寻的字节集, const std::vector<unsigned char>& 欲寻找的字节集 = std::vector<unsigned char>());

std::vector<unsigned char> 字节集拼接(std::vector<unsigned char> 字节集1, const std::vector<unsigned char>& 字节集2);
#pragma region 