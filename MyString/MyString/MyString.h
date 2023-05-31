#pragma
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using std::swap;
using std::cout;
using std::endl;
using std::cin;

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
		String() 											// 默认构造
			:_str(new char[1])								// 此处不能给 nullptr：因为后续函数实现过程中存在返回对象，若返回的是 nullptr（空对象） 会出问题
			,_size(0)
			,_capacity(0)
		{
			_str[0] = '\0';									
		}

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
		String(const String& str) 
			:_str(new char[str._capacity + 1])
			,_size(str._size)
			,_capacity(str._capacity)
		{
			strcpy(_str, str._str);
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


		/* 访问系列函数 */
		// []：访问方式
		char& operator [] (size_t pos) {
			assert(pos>=0);
			return _str[pos];
		}

		const char& operator [] (size_t pos) const
		{
			assert(pos);
			return _str[pos];
		}

		
		// 返回 char* 对象
		const char* c_str() const
		{
			return _str;
		}

		/* 赋值运算符重载 */
		String& operator = (const String& str) {
			if (this != &str) {								// 避免 s1
#if 0
				delete[] _str;
				_str = new char[str._capacity + 1];
				_size = str._size;
				_capacity = str._capacity;

#endif
				char* tmp  = new char[str._capacity + 1];
				strcpy(tmp, str._str);

				delete[] _str;

				_str = tmp;
				_size = str._size;
				_capacity = str._capacity;
			}
			return *this;
		}

		void swap(String& temp) {
			::swap(_str, temp._str);
			::swap(_size, temp._size);
			::swap(_capacity, temp._capacity);
		}

		/* 赋值运算符重载：新式写法 */
		String(const String& str) 
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{
			String temp(str._str);
			swap(temp);
		}

	private:
		char* _str;
		size_t _size;										// 记录当前 串 内字符数
		size_t _capacity;									// 记录当前 串 可存储的最大字符数（不含 '\0'）
	};


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
	}
}