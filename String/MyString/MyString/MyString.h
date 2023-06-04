#pragma
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using std::swap;
using std::cout;
using std::endl;
using std::cin;
using std::istream;
using std::ostream;

namespace MySTL {

	class String {
	public:
		/* 迭代器的实现：string 的迭代器实现原理就是指针 */
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() {
			return _str;
		}

		iterator end() {
			return _str + _size;							// 注意返回的是字符串尾部的下一个位置，且 + 的是 _size
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}


		/* 构造函数 */
		//String() 											// 默认构造
		//	:_str(new char[1])								// 此处不能给 nullptr：因为后续函数实现过程中存在返回对象，若返回的是 nullptr（空对象） 会出问题
		//	,_size(0)
		//	,_capacity(0)
		//{
		//	_str[0] = '\0';									
		//}

#if 0
		// String(const char* str = '\0')
		String(const char* str = "")						// 注意：对于常量字符串默认会含 '\0'
			:_str(new char[strlen(str)+1])					// strlen 效率：O(N)
			,_size(strlen(str))
			,_capacity(strlen(str))							// 注意此处：容量不包含 '\0'
			/* 注意：以上顺序不能随意摆放！原因在于参数列表的初始化顺序是与声明顺序相关的！ */
		{
			strcpy(_str, str);
		}
#endif
		/* 以上函数的修改建议：由于多次使用了 strlen 函数效率不高，所以可以选择不适用初始化列表写法实现 */
		String(const char* str = "") {
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];					// 空间申请
			strcpy(_str, str);
		}

		// 拷贝构造：深拷贝！
		//String(const String& str) 
		//	:_str(new char[str._capacity + 1])
		//	,_size(str._size)
		//	,_capacity(str._capacity)
		//{
		//	strcpy(_str, str._str);
		//}




		/* 访问系列函数 */
		// []：访问方式
		char& operator [] (size_t pos) {
			assert(pos>=0);
			return _str[pos];
		}

		const char& operator [] (size_t pos) const
		{
			assert(pos>=0);
			return _str[pos];
		}

		
		// 返回 char* 对象
		const char* c_str() const
		{
			return _str;
		}

		/* 赋值运算符重载 */
//		String& operator = (const String& str) {
//			if (this != &str) {								// 防止出现自己给自己赋值
//#if 0
//				delete[] _str;
//				_str = new char[str._capacity + 1];
//				strcpy(_str, str._str);
//				_size = str._size;
//				_capacity = str._capacity;
//
//#endif
//				char* tmp  = new char[str._capacity + 1];
//				strcpy(tmp, str._str);
//
//				delete[] _str;
//
//				_str = tmp;
//				_size = str._size;
//				_capacity = str._capacity;
//
//
//			}
//			return *this;
//		}
		/* 新写法 */
		//String& operator = (const String& str) {
		//	if (this != &str) {
		//		String temp(str);
		//		swap(temp);
		//	}
		//	return *this;
		//}

		String& operator = (String str) {		// 注意参数列表：直接使用传值传参，str 直接就顶替了上面写法中的 temp
			swap(str);
			return *this;
		}


		void swap(String& temp) {
			::swap(_str, temp._str);
			::swap(_size, temp._size);
			::swap(_capacity, temp._capacity);
		}

		/* 拷贝构造：新式写法 */
		String(const String& str) 
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{
			String temp(str._str);
			swap(temp);
		}

		void reserve(size_t n)
		{
			if (n > _capacity) {
				char* temp = new char[n+1];
				strcpy(temp, _str);
				delete[] _str;
				_str = temp;
				_capacity = n;
			}
		}

		void reszie(size_t n, char ch = '\0') {
			if (n > _size) {
				// 插入数据
				reserve(n);
				for (size_t i = _size; i < n ; i++) {
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else {
				// 删除数据
				_str[n] = '\0';
				_size = n;
			}
		}

		void push_back(char ch)
		{
			// 满就扩容
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			// 如果满就扩容
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			strcpy(_str + len, str);		// 可以使用strcat可以用，但是效率低，拼接的时候每次需要找 '\0'
			//strcat(_str + len, str);
			//strcat(_str, str);
			_size += len;
		}

		String& operator += (char ch) {
			push_back(ch);
			return *this;
		}

		String& operator += (const char* str) {
			append(str);
			return *this;
		}

		String& insert(size_t pos, char ch) {
			assert(pos <= _size);
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			//size_t end = _size;
			//while (end >= pos) {
			//	_str[end + 1] = _str[end];
			//	--end;
			//}

			size_t end = _size+1;
			while (end > pos) {
				_str[end] = _str[end-1];
				--end;
			}


			_str[pos] = ch;
			++_size;
			return *this;
		}

		String& insert(size_t pos, const char* str) {
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			size_t end = _size + len;
			while (end >= pos + len) {
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, str , len);
			_size += len;
			return *this;
		}

		void earse(size_t pos, size_t len = npos) {
			assert(pos < _size);

			if (len == npos || pos + len >= _size) {
				_str[pos] = '\0';
				_size = pos;
			}
			else {
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}

		size_t find(char ch, size_t pos = 0) const
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++) {
				if (ch == _str[i])
					return i;
			}
			return npos;
		}

		size_t find(const char* sub, size_t pos = 0) const 
		{
			assert(sub);
			assert(pos < _size);
			/* 暴力匹配 */
			const char* p = strstr(_str + pos, sub);
			if (p == nullptr) {
				return npos;
			}
			else {
				return p - _str;
			}
		}

		String substr(size_t pos = 0, size_t len = npos) const
		{
			assert(pos < _size);
			size_t realLength = len;
			if (len == npos || pos + len > _size) {
				realLength = _size - pos;
			}
			String sub;
			for (size_t i = 0; i < realLength; i++) {
				sub += _str[pos + i];
			}
			return sub;
		}

		bool operator > (const String& str) const
		{
			return strcmp(_str, str.c_str()) == 1;
		}
		bool operator == (const String& str) const
		{
			return strcmp(_str, str.c_str()) == 0;
		}
		bool operator >= (const String& str) const
		{
			return *this > str || *this == str;
		}
		bool operator <= (const String& str) const
		{
			return !(*this > str);
		}
		bool operator < (const String& str) const
		{
			return !(*this >= str);
		}
		bool operator != (const String& str) const
		{
			return !(*this == str);
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}



		// 析构函数
		~String() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		/* 容量系列函数 */
		// 获取当前字符数
		size_t size() const
		{
			return _size;
		}

	private:
		char* _str;
		size_t _size;										// 记录当前 串 内字符数
		size_t _capacity;									// 记录当前 串 可存储的最大有效字符数（不含 '\0'）
	public:
		const static size_t npos = -1;						// 即：整形最大值
	};

	ostream& operator << (ostream& out, const String& str) {
		for (size_t i = 0; i < str.size(); ++i) {
			out << str[i];
		}
		return out;
	}
	// 流插入与流提取
	istream& operator >> (istream& in, String& str) {
		//char ch;
		//ch = in.get();
		//while (ch != ' ' && ch != '\n') {
		//	str += ch;
		//	ch = in.get();
		//}
		/* 优化！ */
		char ch;
		ch = in.get();
		str.clear();
		const size_t N = 32;
		char buff[N];								// 模拟缓冲区

		size_t i = 0;

		while (ch != ' ' && ch != '\n') {
			buff[i++] = ch;
			if (i == N - 1) {
				buff[i] = '\0';
				str += buff;
				i = 0;
			}
			ch = in.get();
		}
		buff[i] = '\0';
		str += buff;
		return in;
	}



	void test_s1() {
		String s1("123456");
		String s2("");


		for (auto iter = s1.begin(); iter != s1.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
		for (int i = 0; i < s1.size(); i++) {
			cout << s1[i] << " ";
		}
		cout << endl;
		for (auto v : s1) {
			cout << v << " ";
		}
		cout << endl;

		cout << s1.c_str() << endl;
	}

	void test_s2() {
		String s1("123456");
		String s2(s1);
		cout << &s1 << endl;
		cout << &s2 << endl;


		String s3("abcdefghijklmn");
		s3 = s1;

		s3.push_back('c');
		for (int i = 0; i < s3.size(); i++) {
			cout << s3[i] << " ";
		}

		s3 += "1asdfadsf";
		for (int i = 0; i < s3.size(); i++) {
			cout << s3[i] << " ";
		}
	}

	void test_s3() {
		String s1("hello world");
		s1.insert(6, '#');
		for (int i = 0; i < s1.size(); i++) {
			cout << s1[i];
		}
		cout << endl;
		s1.insert(5, "123456789");
		for (int i = 0; i < s1.size(); i++) {
			cout << s1[i];
		}
		cout << endl;
		String s2,s3;
		cin >> s2 >> s3;
		cout << s2 << endl;
		cout << s3 << endl;
	}
}