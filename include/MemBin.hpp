#ifndef  _MEMBIN_HPP_
#define  _MEMBIN_HPP_
#include <array>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>
namespace epldatatype {
    class MemBin
    {
    public:
        using byte_type = unsigned char;
        using byte_poiter = byte_type*;
        using const_byte_poiter = const byte_type*;
        using reference = byte_type&;
        using const_reference = const byte_type&;
        using size_type = size_t;

        ////内部常量迭代器
        //class const_iterator
        //{
        //    using __traits_type = std::iterator_traits<const_byte_poiter>;
        //public:
        //    typedef typename __traits_type::iterator_category iterator_category;
        //    typedef typename __traits_type::value_type  	value_type;
        //    typedef typename __traits_type::difference_type 	difference_type;
        //    typedef typename __traits_type::reference 	reference;
        //    typedef typename __traits_type::pointer   	pointer;

        //    constexpr const_iterator() noexcept
        //        : _M_current(const_byte_poiter()) { }

        //    constexpr
        //        const_iterator(const const_byte_poiter& __i) noexcept
        //        : _M_current(__i) { }

        //    /*    constexpr
        //            const_iterator(const void*& __i) noexcept
        //            : _M_current(static_cast<const const_byte_poiter>(__i)) { }*/
        //            // 输入迭代器
        //    constexpr
        //        reference
        //        operator*() const noexcept
        //    {
        //        return *_M_current;
        //    }

        //    constexpr
        //        pointer
        //        operator->() const noexcept
        //    {
        //        return _M_current;
        //    }

        //    constexpr
        //        const_iterator&
        //        operator++()  noexcept
        //    {
        //        ++_M_current;
        //        return *this;
        //    }

        //    constexpr
        //        const_iterator
        //        operator++(int)  noexcept
        //    {
        //        return const_iterator(_M_current++);
        //    }

        //    // 双向迭代器
        //    constexpr
        //        const_iterator&
        //        operator--() noexcept
        //    {
        //        --_M_current;
        //        return *this;
        //    }

        //    constexpr
        //        const_iterator
        //        operator--(int) noexcept
        //    {
        //        return const_iterator(_M_current--);
        //    }

        //    // 随机访问迭代器
        //    constexpr
        //        reference
        //        operator[](difference_type __n) const noexcept
        //    {
        //        return _M_current[__n];
        //    }

        //    constexpr
        //        const_iterator&
        //        operator+=(difference_type __n) noexcept
        //    {
        //        _M_current += __n; return *this;
        //    }

        //    constexpr
        //        const_iterator
        //        operator+(difference_type __n) const noexcept
        //    {
        //        return const_iterator(_M_current + __n);
        //    }

        //    constexpr
        //        const_iterator&
        //        operator-=(difference_type __n) noexcept
        //    {
        //        _M_current -= __n; return *this;
        //    }

        //    constexpr
        //        const_iterator
        //        operator-(difference_type __n) const noexcept
        //    {
        //        return const_iterator(_M_current - __n);
        //    }

        //    constexpr
        //        const const_byte_poiter&
        //        base() const noexcept
        //    {
        //        return _M_current;
        //    }
        //    constexpr
        //        operator const_byte_poiter() const noexcept {
        //        return _M_current;
        //    }
        //    constexpr
        //        difference_type
        //        operator-(const const_iterator& _X) const noexcept
        //    {
        //        return std::distance(_X._M_current, _M_current);
        //    }

        //    constexpr
        //        bool
        //        operator==(const const_iterator& __x) const noexcept
        //    {
        //        return _M_current == __x._M_current;
        //    }

        //    constexpr
        //        bool
        //        operator!=(const const_iterator& __x) const noexcept
        //    {
        //        return _M_current != __x._M_current;
        //    }

        //    constexpr
        //        std::strong_ordering
        //        operator<=>(const const_iterator& __x) const noexcept
        //    {
        //        return _M_current <=> __x._M_current;
        //    }
        //private:
        //    const_byte_poiter _M_current{ nullptr };
        //};
        ////内部迭代器
        //class iterator
        //{
        //    using __traits_type = std::iterator_traits<byte_poiter>;
        //public:
        //    typedef typename __traits_type::iterator_category iterator_category;
        //    typedef typename __traits_type::value_type  	value_type;
        //    typedef typename __traits_type::difference_type 	difference_type;
        //    typedef typename __traits_type::reference 	reference;
        //    typedef typename __traits_type::pointer   	pointer;

        //    constexpr iterator() noexcept
        //        : _M_current(nullptr) { }

        //    constexpr
        //        iterator(const byte_poiter& __i) noexcept
        //        : _M_current(__i) { }
        //    /*  constexpr
        //          iterator(void*& __i) noexcept
        //          : _M_current(static_cast<byte_poiter>(__i)) { }*/

        //          // 输入迭代器
        //    constexpr
        //        reference
        //        operator*() const noexcept
        //    {
        //        return *_M_current;
        //    }

        //    constexpr
        //        pointer
        //        operator->() const noexcept
        //    {
        //        return _M_current;
        //    }
        //    //指针重载
        //    constexpr
        //        operator pointer() const noexcept
        //    {
        //        return _M_current;
        //    }

        //    constexpr
        //        iterator&
        //        operator++()  noexcept
        //    {
        //        ++_M_current;
        //        return *this;
        //    }

        //    constexpr
        //        iterator
        //        operator++(int)  noexcept
        //    {
        //        return iterator(_M_current++);
        //    }

        //    // 双向迭代器
        //    constexpr
        //        iterator&
        //        operator--() noexcept
        //    {
        //        --_M_current;
        //        return *this;
        //    }

        //    constexpr
        //        iterator
        //        operator--(int) noexcept
        //    {
        //        return iterator(_M_current--);
        //    }

        //    // 随机访问迭代器
        //    constexpr
        //        reference
        //        operator[](difference_type __n) const noexcept
        //    {
        //        return _M_current[__n];
        //    }

        //    constexpr
        //        iterator&
        //        operator+=(difference_type __n) noexcept
        //    {
        //        _M_current += __n; return *this;
        //    }

        //    constexpr
        //        iterator
        //        operator+(difference_type __n) const noexcept
        //    {
        //        return iterator(_M_current + __n);
        //    }

        //    constexpr
        //        iterator&
        //        operator-=(difference_type __n) noexcept
        //    {
        //        _M_current -= __n; return *this;
        //    }

        //    constexpr
        //        iterator
        //        operator-(difference_type __n) const noexcept
        //    {
        //        return iterator(_M_current - __n);
        //    }

        //    constexpr
        //        const byte_poiter&
        //        base() const noexcept
        //    {
        //        return _M_current;
        //    }

        //    constexpr
        //        difference_type
        //        operator-(const iterator& _X) const noexcept
        //    {
        //        return std::distance(_X._M_current, _M_current);
        //    }

        //    constexpr
        //        bool
        //        operator==(const iterator& __x) const noexcept
        //    {
        //        return _M_current == __x._M_current;
        //    }

        //    constexpr
        //        bool
        //        operator!=(const iterator& __x) const noexcept
        //    {
        //        return _M_current != __x._M_current;
        //    }

        //    constexpr
        //        std::strong_ordering
        //        operator<=>(const iterator& __x) const noexcept
        //    {
        //        return _M_current <=> __x._M_current;
        //    }
        //private:
        //    byte_poiter _M_current{ nullptr };
        //};
        ////反向迭代器类型
        //using reverse_iterator = std::reverse_iterator<iterator>;
        ////常量反向迭代器类型
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    public:
        MemBin() = default;
        ~MemBin();


        /*explicit
            MemBin(size_type __n)
        {
            this->m_pData = new byte_type[__n]{};
            this->m_nSize = this->m_nMaxSize = __n;
        }*/
        MemBin(std::initializer_list<byte_type> __l)
        {
            const size_type __n = __l.size();
            this->m_pData = new byte_type[__n];
            this->m_nSize = this->m_nMaxSize = __n;
            std::copy(__l.begin(), __l.end(), this->m_pData);
        }

        //template <typename T>
        //MemBin(std::initializer_list<T> __l)
        //{
        //    const size_type __n = __l.size();
        //    this->m_pData = new byte_type[__n];
        //    this->m_nSize = this->m_nMaxSize = __n;

        //    std::unique_ptr<T[]> p = std::make_unique<T[]>(__n);
        //    std::copy(__l.begin(), __l.end(), p.get());
        //    for (size_t i = 0; i < __n; i++)
        //        this->m_pData[i] = static_cast<byte_type>(p[i]);
        //}


        MemBin(const void* _p, size_type _size)
        {
            if (_p != nullptr && _size != 0)
            {
                this->m_pData = new byte_type[_size];
                this->m_nSize = this->m_nMaxSize = _size;
                memcpy(this->m_pData, _p, _size);
            }

        }

        template <typename T>
        explicit  MemBin(T&& val) :MemBin(&val, sizeof(T)) {};


        explicit MemBin(const char* val) :MemBin(val, strlen(val)) {};
        explicit MemBin(const wchar_t* val) :MemBin(val, wcslen(val) * sizeof(char)) {};
        template <typename CharType>
        explicit MemBin(std::basic_string<CharType>&& val) :MemBin(val.data(), val.size() * sizeof(CharType)) {};


        MemBin(const MemBin& __x)
        {
            const size_type __n = __x.size();
            this->m_pData = new byte_type[__n];
            this->m_nSize = this->m_nMaxSize = __n;
            std::copy(__x.m_pData, __x.m_pData+ __x.m_nSize, this->m_pData);
        }
    public://迭代器部分


        ////读写迭代器-返回指向第一个字节的迭代器
        //iterator
        //    begin()  noexcept
        //{
        //    return iterator(this->m_pData);
        //}

        ////只读迭代器-返回指向第一个字节的迭代器
        //const_iterator
        //    begin() const noexcept
        //{
        //    return const_iterator(this->m_pData);
        //}
        ////读写迭代器-返回指向最后一个字节的迭代器
        //iterator
        //    end() noexcept
        //{
        //    return iterator(this->m_pData + this->m_nSize);
        //}
        ////只读迭代器-返回指向最后一个字节的迭代器
        //const_iterator
        //    end() const noexcept
        //{
        //    return const_iterator(this->m_pData + this->m_nSize);
        //}
        ////读写反向迭代器-返回指向最后一个字节的迭代器
        //reverse_iterator
        //    rbegin() noexcept
        //{
        //    return reverse_iterator(end());
        //}

        ////只读反向迭代器-返回指向最后一个字节的迭代器
        //const_reverse_iterator
        //    rbegin() const noexcept
        //{
        //    return const_reverse_iterator(end());
        //}

        ////读写反向迭代器-返回指向第一个字节的迭代器
        //reverse_iterator
        //    rend() noexcept
        //{
        //    return reverse_iterator(begin());
        //}

        ////只读反向迭代器-返回指向第一个字节的迭代器
        //const_reverse_iterator
        //    rend() const noexcept
        //{
        //    return const_reverse_iterator(begin());
        //}

        ////只读迭代器-返回指向第一个字节的迭代器
        //const_iterator
        //    cbegin() const noexcept
        //{
        //    return const_iterator(this->m_pData);
        //}

        ////只读迭代器-返回指向最后一个字节的迭代器
        //const_iterator
        //    cend() const noexcept
        //{
        //    return const_iterator(this->m_pData + this->m_nSize);
        //}

        ////只读反向迭代器-返回指向最后一个字节的迭代器
        //const_reverse_iterator
        //    crbegin() const noexcept
        //{
        //    return const_reverse_iterator(end());
        //}

        ////只读反向迭代器-返回指向第一个字节的迭代器
        //const_reverse_iterator
        //    crend() const noexcept
        //{
        //    return const_reverse_iterator(begin());
        //}
       /* reference front()
        {
            return *begin();
        }
        const_reference front() const
        {
            return *begin();
        }
        reference back()
        {
            return *(end() - 1);
        }
        const_reference back() const
        {
            return *(end() - 1);
        }*/
        void pop_back()
        {
            if (m_nSize > 0)
                m_nSize--;
        }
    public:

        void reserve(size_type _N);
        void resize(size_type nNewSize);
        byte_poiter data() {
            return m_pData;
        }
        const_byte_poiter data() const {
            return m_pData;
        }
        void remove(const size_t npOffset, const size_t npSize)
        {

            if (npSize <= 0)
                return;

            if (npOffset <= -1)  // 从尾部开始向前删除?
            {
                const auto npNewSize = m_nSize - npSize;

                if (npNewSize <= 0)  // 全部删除?
                    clean();
                else
                    resize(npNewSize);  // 去除尾部所指定尺寸的数据
            }
            else
            {
               size_t npRemoveSize;

                if (npSize < m_nSize - npOffset)  // 在中间删除?
                {
                    BYTE* pRemoveAt = m_pData + npOffset;
                    npRemoveSize = npSize;
                    memmove(pRemoveAt, pRemoveAt + npRemoveSize, m_nSize - npOffset - npRemoveSize);
                }
                else
                {
                    // 从npOffset一直删除到尾部
                    npRemoveSize = m_nSize - npOffset;
                }

                if (m_nSize == npRemoveSize)
                    clean();
                else
                   resize(m_nSize - npRemoveSize);
            }
        }

        size_type size() const
        {
            return m_pData == nullptr ? 0 : m_nSize;
        }
        bool empty() const
        {
            return (size() == 0);
        }
        size_type capacity() const
        {
            return m_pData == nullptr ? 0 : m_nMaxSize;
        }

    private://辅助算法

        static void make_delta1(size_t* delta1, unsigned char* pat, size_t patlen) noexcept {
            for (size_t i = 0; i < 256; i++) {
                delta1[i] = patlen;
            }
            for (size_t i = 0; i < patlen - 1; i++) {
                delta1[pat[i]] = patlen - 1 - i;
            }
        }
        static bool is_prefix(unsigned char* word, size_t wordlen, size_t pos) noexcept {
            if (wordlen < pos)
                return true;
            auto suffixlen = wordlen - pos;
            for (size_t i = 0; i < suffixlen; i++) {
                if (word[i] != word[pos + i]) {
                    return false;
                }
            }
            return true;
        }
        static size_t suffix_length(unsigned char* word, size_t wordlen, size_t pos) noexcept {
            size_t length = 0;
            if (pos >= wordlen) return 0;
            for (size_t i = 0; i < pos; i++) {
                if (word[pos - i] != word[wordlen - 1 - i]) {
                    break;
                }
                length++;
            }

            return length;
        }
        static void make_delta2(size_t* delta2, unsigned char* pat, size_t patlen) noexcept {
            size_t last_prefix_index = 1;
            for (size_t p = patlen; p != 0; p--) {
                if (is_prefix(pat, patlen, p)) {
                    last_prefix_index = p;
                }
                delta2[p - 1] = patlen - p + last_prefix_index;
            }
            for (size_t p = 0; p < patlen - 1; p++) {
                const auto slen = suffix_length(pat, patlen, p);
                if (pat[p - slen] != pat[patlen - 1 - slen]) {
                    delta2[patlen - 1 - slen] = patlen - 1 - p + slen;
                }
            }
        }
        size_t boyer_moore(unsigned char* string, size_t stringlen, unsigned char* pat, size_t patlen) const noexcept {

            size_t delta1[256];
            std::unique_ptr<size_t[]> delta2 = std::make_unique<size_t[]>(patlen);
            if (!delta2)
                return -1;
            make_delta1(delta1, pat, patlen);
            make_delta2(delta2.get(), pat, patlen);
            size_t n_shifts = 0;
            for (size_t i = patlen - 1; i < stringlen;) {
                ptrdiff_t j = patlen - 1;
                while (j >= 0 && (string[i] == pat[j])) {
                    --i;
                    --j;
                }
                if (j < 0)
                    return i + 1;

                i += delta1[string[i]] > delta2[j] ? delta1[string[i]] : delta2[j];
            }
            return -1;
        }



    public:
        //不改变容量
        void clean() {
           m_nSize = 0;
        }

        template<typename Val>
        Val to_value(size_type off = 0) const {
            std::unique_ptr<Val> p = std::make_unique<Val>();
            *p = 0;
            auto nSize = size() - off < sizeof(Val) ? size() - off : sizeof(Val);
            memcpy(p.get(), data() + off, nSize);
            return *reinterpret_cast<Val*>(p.get());
        }

        template<typename charType>
        std::basic_string<charType> to_string(size_type off = 0) const {
            if (empty() || off > size())
                return {};
            const auto pData = this->m_pData + off;
            const size_type nSize = this->m_pData + this->m_nSize - pData;
            const auto needSize = nSize + sizeof(charType) * 2;//最少两个结束符,防止小众语言的变成收尾碰撞问题;
            std::unique_ptr<unsigned char[]> p = std::make_unique<unsigned char[]>(needSize);
            std::fill_n(p.get(), needSize, 0);
            memcpy(p.get(), pData, nSize);
            return reinterpret_cast<charType*>(p.get());
        }
        MemBin& append(const MemBin& src)
        {
            const auto nOldSize = m_nSize;
            resize(m_nSize + src.m_nSize);
            memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize);
            return *this;
        }
        template <typename T>
        MemBin& append(T&& src)
        {
            const auto nOldSize = m_nSize;
            resize(m_nSize + sizeof(T));
            memcpy(m_pData + nOldSize, &src, sizeof(T));
            return *this;
        }
        template <typename T>
        void append_str(const std::basic_string_view<T>& pws)
        {
            if (!pws.empty())
                append(pws.data(), pws.size() * sizeof(T));
        }
        MemBin& append(const void* p,const size_t size)
        {
            const auto nOldSize = m_nSize;
            resize(m_nSize + size);
            memcpy(m_pData + nOldSize, p, size);
            return *this;
        }
        template <typename T>
        MemBin& append(std::initializer_list<T> src) {
            auto size = src.size();
            if (size == 0)
            {
                return *this;
            }
            const auto nOldSize = m_nSize;
            resize(m_nSize + size);
            auto begin = m_pData + nOldSize;
            std::unique_ptr<T[]> p = std::make_unique<T[]>(size);
            std::copy(src.begin(), src.end(), p.get());
            for (size_t i = 0; i < size; i++)
                begin[i] = static_cast<byte_type>(p[i]);
            return *this;
        };

        void insert(size_type nIndex, const void* newElement, size_type nCount) {
            if (newElement == nullptr || nCount == 0)
            {
                return;
            }
            if (nIndex >= m_nSize)
            {
                resize(nIndex + nCount);
            }
            else
            {
                const auto nOldSize = m_nSize;
                resize(m_nSize + nCount);
                memmove(m_pData + nIndex + nCount, m_pData + nIndex,
                    nOldSize - nIndex);
            }
            std::copy_n(static_cast<const_byte_poiter>(newElement), nCount, m_pData + nIndex);
        };
        void insert(size_type nStartIndex, const MemBin& pNewArray) {
            if (pNewArray.size() > 0)
            {
                insert(nStartIndex, pNewArray.data(), pNewArray.size());
            }
        };
        void swap(MemBin& _X)
        {
            std::swap(m_pData, _X.m_pData);
            std::swap(m_nMaxSize, _X.m_nMaxSize);
            std::swap(m_nSize, _X.m_nSize);
        }

    public:
        static const size_type nops = size_type(-1);
        [[nodiscard]]
        size_type find(const MemBin& sub, size_type off = 0)  const noexcept {
            auto nLen = size(), nSubLen = sub.size();
            auto pSrc = m_pData + off;

            if (nLen <= off || nSubLen == 0)
                return nops;
            //实际需求长度
            nLen -= off;
            if (nSubLen > nLen)
                return nops;
            auto  pDes = sub.m_pData;


            switch (nSubLen) {
            case 1: {
                auto lpsz = static_cast<const unsigned char*>(std::memchr(pSrc, *pDes, nLen));
                return (lpsz == nullptr) ? nops : (lpsz - pSrc);
            }
            case 2: {
                for (size_t i = 0; i < nLen - 1; i++) {
                    if (*reinterpret_cast<const short*>(pSrc + i) == *reinterpret_cast<const short*>(pDes))
                        return i + off;
                }
                return nops;
            }
            case 3: {
                for (size_t i = 0; i < nLen - 2; i++) {
                    if (*reinterpret_cast<const short*>(pSrc + i) == *reinterpret_cast<const short*>(pDes)) {
                        if (pSrc[i + 2] == pDes[2]) {
                            return i + off;
                        }
                    }
                }
                return nops;
            }
            case 4: {
                for (size_t i = 0; i < nLen - 3; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes))
                        return i + off;
                }
                return nops;
            }
            case 5: {
                for (size_t i = 0; i < nLen - 4; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes)) {
                        if (pSrc[i + 4] == pDes[4])
                            return i + off;
                    }
                }
                return nops;
            }
            case 6: {
                for (size_t i = 0; i < nLen - 5; i++) {
                    if (*reinterpret_cast<const int*>(pSrc + i) == *reinterpret_cast<const int*>(pDes)) {
                        if (*reinterpret_cast<const short*>(pSrc + i + 4) == *reinterpret_cast<const short*>(pDes + 4))
                            return i + off;
                    }
                }
                return nops;
            }
            default: {
                size_t naddr = boyer_moore(pSrc, nLen, pDes, nSubLen);
                if (naddr != nops)
                    return naddr + off;
                return nops;
            }
            }
        }
        //[[nodiscard]]
        //size_type rfind(const MemBin& sub)const noexcept {
        //    auto nLen = size(), nSubLen = sub.size();
        //    if (nLen < nSubLen)
        //        return nops;
        //    size_type off = nLen - nSubLen;

        //    const auto pSrc = data();
        //    const auto pDes = sub.data();


        //    //起始迭代器
        //    auto it = const_reverse_iterator(this->begin() + off);


        //    if (nSubLen == 1)
        //    {
        //        const auto c = *pDes;
        //        for (; it != this->rend(); ++it) {
        //            if (*it == c)
        //                return std::distance(begin(), it.base());
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 2) {
        //        const auto need = sub.to_value<short>();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need)
        //                return std::distance(begin(), it.base());

        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 3) {
        //        const auto need = sub.to_value<short>();
        //        const auto c = sub.back();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 2).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 4) {
        //        const auto need = sub.to_value<int>();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base())) == need) {
        //                return std::distance(begin(), it.base());
        //            }

        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 5) {
        //        const auto need = sub.to_value<int>();
        //        const auto c = sub.back();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 4).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 6) {
        //        const auto need = sub.to_value<int>();
        //        const auto c = sub.to_value<short>(3);
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 4).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }

        //    std::array<size_type, 256> next;
        //    for (auto& c : next)
        //        c = nSubLen;
        //    for (size_t i = nSubLen; i > 0; i--)
        //        next[pDes[i - 1]] = i;


        //    const unsigned char* naddr = pSrc + off;
        //    for (; naddr >= pSrc; naddr -= next[naddr[-1]])
        //        if (memcmp(naddr, pDes, nSubLen) == 0)
        //            return naddr - pSrc;
        //    return nops;
        //}
        //[[nodiscard]]
        //size_type rfind(const MemBin& sub, size_type off) const noexcept {
        //    auto nLen = size(), nSubLen = sub.size();
        //    if (nLen < nSubLen)
        //        return nops;


        //    if (off < nLen)
        //        nLen = off + 1;

        //    if (nLen < nSubLen)
        //        return nops;
        //    off = nLen - nSubLen;

        //    const auto pSrc = data();
        //    const auto pDes = sub.data();


        //    //起始迭代器
        //    auto it = const_reverse_iterator(this->begin() + off);


        //    if (nSubLen == 1)
        //    {
        //        const auto c = *pDes;
        //        for (; it != this->rend(); ++it) {
        //            if (*it == c)
        //                return std::distance(begin(), it.base());
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 2) {
        //        const auto need = sub.to_value<short>();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need)
        //                return std::distance(begin(), it.base());

        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 3) {
        //        const auto need = sub.to_value<short>();
        //        const auto c = sub.back();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const short*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 2).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 4) {
        //        const auto need = sub.to_value<int>();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                return std::distance(begin(), it.base());
        //            }

        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 5) {
        //        const auto need = sub.to_value<int>();
        //        const auto c = sub.back();
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 4).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }
        //    else if (nSubLen == 6) {
        //        const auto need = sub.to_value<int>();
        //        const auto c = sub.to_value<short>(3);
        //        // 迭代器指向容器末尾的前两个元素
        //        for (; it != this->rend(); ++it) {
        //            // 比较连续的两个元素是否与子序列相匹配
        //            if (*reinterpret_cast<const int*>(static_cast<const unsigned char*>(it.base().base())) == need) {
        //                if (c == *std::next(it, 4).base())
        //                    return std::distance(begin(), it.base());
        //            }
        //        }
        //        return nops;
        //    }

        //    std::array<size_type, 256> next;
        //    for (auto& c : next)
        //        c = nSubLen;
        //    for (size_t i = nSubLen; i > 0; i--)
        //        next[pDes[i - 1]] = i;


        //    const unsigned char* naddr = pSrc + off;
        //    for (; naddr >= pSrc; naddr -= next[naddr[-1]])
        //        if (memcmp(naddr, pDes, nSubLen) == 0)
        //            return naddr - pSrc;
        //    return nops;
        //}
        //[[nodiscard]]
        MemBin replace(size_type nStart, size_type  nRpLen, const MemBin& sub = {}) const noexcept {
            if (empty())
                return {};
            auto pBin = data(), pSubBin = sub.data();;
            auto nSubLen = sub.size(), nLen = this->size();;


            if (nStart > nLen)
                nStart = nLen - 1;

            if (nStart + nRpLen > nLen) nRpLen = nLen - nStart;
            auto nNewLen = nLen - nRpLen + nSubLen;
            if (nNewLen <= 0) return {};


            if (nStart == 0)
            {
                if (nSubLen == 0)
                    return { pBin + nRpLen, nNewLen };
                MemBin pTemp;
                pTemp.resize(nNewLen);
                memcpy(pTemp.data(), pSubBin, nSubLen);
                memcpy(pTemp.data() + nSubLen, pBin + nRpLen, nLen - nRpLen);
                return pTemp;
            }
            else if (nStart >= nLen)
            {
                if (nSubLen == 0)
                    return { pBin, nNewLen };

                MemBin pTemp;
                pTemp.resize(nNewLen);
                memcpy(pTemp.data(), pBin, nLen);
                memcpy(pTemp.data() + nLen, pSubBin, nSubLen);
                return pTemp;
            }

            MemBin pTemp;
            pTemp.resize(nNewLen);

            memcpy(pTemp.data(), pBin, nStart);
            auto p = pTemp.data() + nStart;
            if (nSubLen > 0)
            {
                memcpy(p, pSubBin, nSubLen);
                p += nSubLen;
            }
            if (nStart + nSubLen < nNewLen)
                memcpy(p, pBin + nStart + nRpLen, nLen - nStart - nRpLen);
            return pTemp;

        }
    public:
        MemBin& operator=(const MemBin& src) {
            resize(src.m_nSize);
            memcpy(m_pData, src.m_pData, src.m_nSize);
            return *this;
        }


        MemBin& operator=(std::initializer_list<unsigned char> src) {
            resize(src.size());
            memcpy(m_pData, src.begin(), src.size());
            return *this;
        }
        bool operator==(const MemBin& src) const {
            if (src.empty() && empty())
                return true;
            if (src.size() != size())
                return false;
            return memcmp(m_pData, src.m_pData, size()) == 0;
        }

        MemBin& operator+=(
            const MemBin& other) {
            append(other);
            return *this;
        }
        [[nodiscard]]
        const_reference operator[](const size_type _P) const noexcept
        {
            return *(m_pData + _P);
        }
        [[nodiscard]]
        reference operator[](const size_type _P) noexcept {
            return	*(m_pData + _P);
        };
    public:
        //到十进制文本
        template <typename T>
        std::basic_string<T> to_byte_str() const {
            if (empty()) {
                return std::basic_string<T>();
            }

            const size_t length = size();
            //std::basic_string <T> buffer(length * 4 + sizeof("{}"));
            std::unique_ptr<T[]>buffer = std::make_unique<T[]>(length * 4 + sizeof("{}"));
            size_t buffer_index = 0;
            buffer[buffer_index++] = T('{');

            for (const auto byte : *this) {
                auto hundreds = byte / 100;
                auto tens = byte % 100 / 10;
                auto ones = byte % 10;

                if (hundreds > 0) {
                    buffer[buffer_index++] = hundreds + T('0');
                    buffer[buffer_index++] = tens + T('0');
                }
                else if (tens > 0) {
                    buffer[buffer_index++] = tens + T('0');
                }
                buffer[buffer_index++] = ones + T('0');
                buffer[buffer_index++] = ',';
            }
            buffer[buffer_index - 1] = '}';

            return std::basic_string<T>(buffer.get(), buffer_index);
        }
        MemBin left(size_t nDataSize) {
            if (empty() || nDataSize == 0)
                return {};
            if (nDataSize > size())
                nDataSize = size();
            return { m_pData,nDataSize };
        }
        MemBin mid(size_type nStart, size_t nObjLen) {
            if (empty() || nObjLen == 0)
                return {};
            auto nDataSize = size();
            if (nStart > nDataSize)
                return {};

            if (nStart + nObjLen >= nDataSize)
                nObjLen = nDataSize - nStart;
            nDataSize = nObjLen;
            return { m_pData + nStart,nDataSize };
        }
        MemBin right(size_t nCount) {
            if (empty() || nCount <= 0)
                return {};
            if (nCount >= size())
                return *this;
            auto nOffset = size() - nCount;

            return { m_pData + nOffset ,nCount };
        }

    private:
        byte_poiter m_pData{ nullptr }; //起始指针  
        size_t m_nSize{ 0 };     //长度
        size_t m_nMaxSize{ 0 };  //容量
        //因为字节集类对于迭代器要求非常低,所以对于迭代要求比较小

    };

    inline MemBin operator+(const MemBin& left,
        const MemBin& other) {
        MemBin temp{ left };
        return temp.append(other);
    }
    template <typename T>
    inline MemBin operator+(const MemBin& left,
        std::initializer_list<T> other) {
        MemBin temp{ left };
        return temp.append(other);
    }

    namespace __in_core {

        //标准库沟通函数
        template <class _Elem, class _Traits>
        std::basic_ostream<_Elem, _Traits>& MemBinput_str(std::basic_ostream<_Elem, _Traits>& ostr, const _Elem* const data, const size_t size) {
            using OStreamType = std::basic_ostream<_Elem, _Traits>;
            typename OStreamType::iostate state = OStreamType::goodbit; // 初始化状态

            size_t pad_count;
            // 计算需要填充的数量
            if (ostr.width() <= 0 || static_cast<size_t>(ostr.width()) <= size) {
                pad_count = 0; // 不需要填充
            }
            else {
                pad_count = static_cast<size_t>(ostr.width()) - size; // 计算填充的数量
            }

            const typename OStreamType::sentry ok(ostr); // sentry 用于检查流的状态是否正常

            if (!ok) {
                state |= OStreamType::badbit; // 如果流的状态不正常，设置坏位并返回
            }
            else { // 如果流的状态正常，进行字符插入和填充
                if ((ostr.flags() & OStreamType::adjustfield) != OStreamType::left) {
                    // 如果不是左对齐，则在左边进行填充
                    for (; pad_count > 0; --pad_count) {
                        if (OStreamType::traits_type::eq_int_type(OStreamType::traits_type::eof(), ostr.rdbuf()->sputc(ostr.fill()))) {
                            state |= OStreamType::badbit; // 插入失败，设置坏位并退出
                            break;
                        }
                    }
                }

                // 插入字符序列
                if (state == OStreamType::goodbit &&
                    ostr.rdbuf()->sputn(data, static_cast<std::streamsize>(size)) != static_cast<std::streamsize>(size)) {
                    state |= OStreamType::badbit; // 如果插入失败，设置坏位
                }
                else {
                    // 如果插入成功且仍有剩余填充，则在右边进行填充
                    for (; pad_count > 0; --pad_count) {
                        if (OStreamType::traits_type::eq_int_type(OStreamType::traits_type::eof(), ostr.rdbuf()->sputc(ostr.fill()))) {
                            state |= OStreamType::badbit; // 插入失败，设置坏位并退出
                            break;
                        }
                    }
                }

                ostr.width(0); // 重置填充宽度为0，避免影响后续插入操作
            }

            ostr.setstate(state); // 设置流的状态
            return ostr; // 返回修改后的输出流对象
        }

    }

    template <class _Elem, class _Traits>
    std::basic_ostream<_Elem, _Traits>& operator<<(
        std::basic_ostream<_Elem, _Traits>& _Ostr, const MemBin& mem) {

        std::basic_string<_Elem> _Str{ mem.to_byte_str<_Elem>() };
        return __in_core::MemBinput_str(_Ostr, _Str.data(), _Str.size());
    }







    inline MemBin::~MemBin()
    {
        if (m_pData)
            delete[] m_pData;
    }
    inline  void MemBin::reserve(size_type nNewSize)
    {
        if (capacity() < nNewSize)
        {
            if (m_pData == nullptr)
            {
                m_pData = new byte_type[nNewSize]{};
                m_nMaxSize = nNewSize;
            }
            else {
                auto p{ new byte_type[nNewSize]{} };
                std::copy_n(m_pData, m_nSize, p);
                delete[] m_pData;
                m_pData = p;
                m_nMaxSize = nNewSize;
            }

        }
    }
    inline void MemBin::resize(size_type nNewSize)
    {

        if (nNewSize == 0)
        {
            if (m_pData)
                delete[] m_pData;
            m_pData = nullptr;
            m_nSize = m_nMaxSize = 0;
        }
        else if (m_pData == nullptr)
        {

            m_pData = new byte_type[nNewSize]{};
            m_nSize = m_nMaxSize = nNewSize;
        }
        else if (nNewSize <= m_nMaxSize)
        {
            if (nNewSize > m_nSize)
                std::fill_n(m_pData + m_nSize, nNewSize - m_nSize, 0);
            m_nSize = nNewSize;
        }
        else
        {
            //最小两倍当前长度的扩容,因为容量肯定会预设特别大
            size_type nNewMax = nNewSize < m_nSize * 2 ? m_nSize * 2 : nNewSize;
            byte_poiter pNewData = new byte_type[nNewMax];
            std::copy_n(m_pData, m_nSize, pNewData);
            std::fill_n(pNewData + m_nSize, nNewSize - m_nSize, 0);
            delete[]m_pData;
            m_pData = pNewData;
            m_nSize = nNewSize;
            m_nMaxSize = nNewMax;

        }
    }


    inline const WCHAR* GetWideText(const CHAR* szText, MemBin& memBuf, size_t* pnpResultTextLength)
    {

        if (pnpResultTextLength != NULL)
        {
            *pnpResultTextLength = 0;
        }

        if (szText != nullptr && *szText != '\0')
        {
            const auto npLenIncludeEndZero = strlen(szText) + 1;  // 获得包括结束零字符的待转换文本长度
            auto npBufLen = ::MultiByteToWideChar(CP_ACP, 0, szText, (INT)npLenIncludeEndZero, NULL, 0);
            memBuf.resize(npBufLen * sizeof(WCHAR));
            WCHAR* pwsBuf = (WCHAR*)memBuf.data();
            npBufLen = ::MultiByteToWideChar(CP_ACP, 0, szText, (INT)npLenIncludeEndZero, pwsBuf, (INT)npBufLen);

            if (npBufLen > 0)  // 转换成功?
            {
                if (pnpResultTextLength != NULL)
                {
                    *pnpResultTextLength = npBufLen - 1;
                }
                return pwsBuf;
            }
        }
        return L"";
    }
    inline   const CHAR* GetMbsText(const WCHAR* szText, MemBin& memBuf, size_t* pnpResultTextLength)
    {
        if (pnpResultTextLength != NULL)
        {
            *pnpResultTextLength = 0;
        }

        if (szText != nullptr && *szText != '\0')
        {
            const auto npLenIncludeEndZero = wcslen(szText) + 1;  // 获得包括结束零字符的待转换文本长度
            auto npBufLen = ::WideCharToMultiByte(CP_ACP, 0, szText, (INT)npLenIncludeEndZero, NULL, 0, NULL, NULL);
            memBuf.resize(npBufLen * sizeof(CHAR));
            CHAR* psBuf = (char*)memBuf.data();
            npBufLen = ::WideCharToMultiByte(CP_ACP, 0, szText, (INT)npLenIncludeEndZero, psBuf, (INT)npBufLen, NULL, NULL);

            if (npBufLen > 0)  // 转换成功?
            {
                if (pnpResultTextLength != NULL)
                {
                    *pnpResultTextLength = npBufLen - 1;
                }
                return psBuf;
            }
        }
        return "";
    }
}
#endif //  _MEMBIN_HPP_