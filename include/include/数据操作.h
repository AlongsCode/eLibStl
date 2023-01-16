/*获取指定数据的MD5,可用网络传输中简单的的数据验证，但是不建议出于安全目的使用MD5，因为它被认为容易受到冲突攻击。还有更安全的替代方案，如SHA-2和SHA-3。对于高度安全数据更简易使用更专业openssl库，或者自己实现算法*/
std::string 取数据摘要A(std::vector<unsigned char> 字节集数据);
/*获取指定数据的MD5,可用网络传输中简单的的数据验证，但是不建议出于安全目的使用MD5，因为它被认为容易受到冲突攻击。还有更安全的替代方案，如SHA-2和SHA-3。对于高度安全数据更简易使用更专业openssl库，或者自己实现算法*/
std::wstring 取数据摘要W(std::vector<unsigned char> 字节集数据);
#ifdef _UNICODE
#define 取数据摘要(X) 取数据摘要W(X)
#else
#define 取数据摘要(X) 取数据摘要A(X)
#endif // _UNICODE
std::vector<unsigned char> 加密数据(std::vector<unsigned char> 字节集数据, const std::string& 密码文本, const int 加密算法 = 1);
std::vector<unsigned char> 加密数据(std::vector<unsigned char> 字节集数据, const std::wstring& 密码文本, const int 加密算法 = 1);
std::vector<unsigned char> 解密数据(std::vector<unsigned char> 字节集数据, const std::wstring& 密码文本, const int 加密算法 = 1);
std::vector<unsigned char> 解密数据(std::vector<unsigned char> 字节集数据, const std::string& 密码文本, const int 加密算法 = 1);