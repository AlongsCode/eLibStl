#pragma once
enum class 内存文件操作命令 {
	读入缓冲区,
	写入缓冲区,
	提交缓冲区,
	检查缓冲区
};
enum  class 读写位置移动方向
{
	前 = 0,
	后 = 1,
};
enum class 文件读写位置
{
	文件首 = 1,
	文件尾,
	现行位置
};




class 内存文件
{
private:
	std::vector<unsigned char> 数据; // 储存文件数据
	size_t 当前位置; // 当前读写位置
	size_t 文件大小; // 文件长度
	// 改变缓冲区长度
	void 改变缓冲区长度(size_t 新长度);

public:
	// 初始化内存文件，可以指定 vector 的初始容量
	内存文件(size_t grow_bytes = 1024);

	~内存文件();
	//
	void 关闭();
	// 读取数据
	std::vector<unsigned char> 读(size_t 读入长度);
	//写入数据
	void 写();
	void 写(const std::vector<unsigned char>& data);
	void 写(const std::string& data);
	void 写(const std::wstring& data);
	void 写(char* data);
	void 写(wchar_t* data);
	void 写(const char* data);
	void 写(const wchar_t* data);
	template<typename T, typename ... Args>
	void 写(const T& data) {
		写(vector<unsigned char>((unsigned char*)&data, ((unsigned char*)&data + sizeof(T))));
	}
	template<typename T, typename ... Args>
	void 写(const T& data, const Args&...args) {
		写(data);
		写(args...);
	}

	//插入数据
	bool 插入(std::vector<unsigned char> data);

	// 移动读写位置
	bool 移动读写位置(long offset, 文件读写位置 origin = 文件读写位置::现行位置);

	// 移动到文件开头
	void 移到文件首();

	// 移动到文件末尾
	void 移到文件尾();

	// 设置文件长度
	void 置文件大小(size_t 新长度);
	// 获取文件长度
	size_t 获取长度() const;

	// 获取当前读写位置
	size_t 获取位置() const;


};