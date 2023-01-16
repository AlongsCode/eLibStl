#pragma once
#ifndef E_BIT_VECTOR//模板类防止复用
#define E_BIT_VECTOR
#include"vector"
#include <algorithm>
template <class T>
using 数组 = std::vector<T>;
template<typename Type>
void 重定义数组(std::vector<Type>& 欲重定义的数组变量, bool 是否保留以前的内容, intptr_t 数组对应维的上限值)
{
	if (是否保留以前的内容) {
		欲重定义的数组变量.resize(数组对应维的上限值);
	}
	else {

		欲重定义的数组变量.clear();
		欲重定义的数组变量.resize(数组对应维的上限值);
	}
}
template<typename Type>
size_t 取数组成员数(std::vector<Type>& 欲重定义的数组变量) {
	return 欲重定义的数组变量.size();
}
template<typename Type>
int 取数组下标(const std::vector<Type>& 欲取某维最大下标的数组变量) {

	return 欲取某维最大下标的数组变量.capacity();

}
template<typename Type>
void 复制数组(std::vector<Type>& 复制到的数组变量, const std::vector<Type>& 待复制的数组数据) {
	复制到的数组变量.assign(待复制的数组数据.begin(), 待复制的数组数据.end());
}
template<typename Type, typename Type2>
void 加入成员(std::vector<Type>& 欲加入成员的数组变量, const Type2& 欲加入的成员数据) {
	欲加入成员的数组变量.push_back(欲加入的成员数据);
}
template<typename Type, typename Type2>
void 插入成员(std::vector<Type>& 欲插入成员的数组变量, intptr_t 欲插入的位置, const Type2& 欲插入的成员数据)
{
	欲插入成员的数组变量.insert(欲插入成员的数组变量.begin() + 欲插入的位置, 欲插入的成员数据);

}
//索引和易有些区别，从0开始
template<typename Type>
intptr_t  删除成员(std::vector<Type>& 欲删除成员的数组变量, intptr_t 欲删除的位置, intptr_t 欲删除的成员数目 = 1) {
	if (欲删除的位置 <  0 || 欲删除的成员数目 > 欲删除成员的数组变量.size()) {
		return 0;
	}
	intptr_t 数目 = 0;
	for (intptr_t i = 1; i <= 欲删除的成员数目; i++)
	{
		欲删除成员的数组变量.erase(欲删除成员的数组变量.begin() + 欲删除的位置);
		if (欲删除成员的数组变量.size() < 欲删除的位置 - 1) {
			break;
		}
		数目 = i;
	}

	return 数目;
};
template<typename Type>
void 清除数组(std::vector<Type>& 欲删除成员的数组变量) {
	std::vector<Type> ret;
	欲删除成员的数组变量.swap(ret);
};
template<typename Type>
void 数组排序(std::vector<Type>& 数值数组变量, bool 排序方向是否为从小到大 = true) {
	if (std::is_same<Type, int>::value) {
		if (排序方向是否为从小到大) {
			std::sort(数值数组变量.begin(), 数值数组变量.end());
		}
		else {
			std::sort(数值数组变量.rbegin(), 数值数组变量.rend());
		}


	}

};
//循环赋值效率没测试，应该不会很快，直接memsetvector数据的地址和长度也许会快一些，而且兼容非数值类数据类型,注意自定义结构体的对齐，别搞大了访问越界
//其次注意容器和对象，尽量指针操作
template<typename Type>
void 数组清零(std::vector<Type>& 数值数组变量) {
	memset(&数值数组变量[0], 0, sizeof(Type) * 数值数组变量.size());
};

//字符串拼接重载运算符，也可使使用字符串拼接函数
template<typename Type>
std::vector<Type> operator+(const std::vector<Type>& 数组1, const std::vector<Type>& 数组2) {
	std::vector<Type> result;
	result.reserve(数组1.size() + 数组2.size());
	result.insert(result.end(), 数组1.begin(), 数组1.end());
	result.insert(result.end(), 数组2.begin(), 数组2.end());
	return result;
}
//二分查找一定要确保数值类以及升序类型，返回数组下标，与易的下标不同注意区分
template<typename Type>
intptr_t 二分查找(std::vector<Type>& 有序数组变量, Type 要查找的值) {
	intptr_t left = 0;
	intptr_t right = 有序数组变量.size() - 1;
	while (left <= right) {
		intptr_t mid = left + (right - left) / 2;
		if (有序数组变量[mid] == 要查找的值) {
			return mid;
		}
		else if (有序数组变量[mid] < 要查找的值) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}
//用于非数值类的数组寻找,返回数组下标，与易的下标不同注意区分
template<typename Type>
intptr_t 数组查找(const std::vector<Type>& 数组, Type 要查找的值) {
	auto it = std::find(数组.begin(), 数组.end(), 要查找的值);
	if (it != 数组.end()) {
		return std::distance(数组.begin(), it);
	}
	else {
		return -1;
	}
}
#endif 