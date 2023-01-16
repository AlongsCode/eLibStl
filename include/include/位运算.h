#ifndef E_BIT_OPERTAIN//模板类防止复用
#define E_BIT_OPERTAIN
/*此库尽量少用，微软有很多现成的宏可以使用，甚至强制转换都可以，位运算远远不止库中的几个,如果不是特别需要，或者对位运算完全不懂的小白可以使用，其他不建议使用，自己手撸比套一层代码强多了*/

int 位取反(int 欲取反的数值);
int 左移(int 欲移动的整数, int 欲移动的位数);
int 右移(int 欲移动的整数, int 欲移动的位数);
int 合并整数(int 低位, int 高位);
short 合并短整数(int 低位, int 高位);
short  合并短整数(char 低位, char 高位);
void 取长整数高低位(long long 预取长整数, int* 高位, int* 低位);
//取整数型某一位的值，为1返回真，为0返回假 32位bit 位号下标为0-31
bool 取整数型某位(int 整数, char 位号);



template <typename T>
long long 位与(const T& t) {
	return t;
};
template <typename T, typename ... Args>
int 位与(const T& num, const Args... args) {
	return num & 位与<long long>(args...);
};
template <typename T>
long long 位或(const T& t) {
	return t;
};
template <typename T, typename ... Args>
long long 位或(const T& num, const Args... args) {
	return num | 位或<long long>(args...);
};

template <typename T>
long long 位异或(const T& t) {
	return t;
};
template <typename T, typename ... Args>
long long 位异或(const T& num, const Args... args) {
	return num ^ 位异或<long long>(args...);
};


#endif 