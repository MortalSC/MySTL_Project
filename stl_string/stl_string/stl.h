#pragma warning( disable : 4996)
#pragma once
#include <iostream>
#include<cstring>
#include <cstdio>
#include <cassert>


namespace stl {


	class string {
	private:
		char* _str;				// 串
		size_t _size;			// 实际串长
		size_t _capacity;		// 串的最大长度（容量）
		// static size_t npos;		
		// 语法点：静态成员变量不能给定缺省值，其他变量的赋值初始化是给初始化列表用的！
		// 但是，静态成员变量不是在初始化成员列表初始化的！它属于整个类。
		static const size_t npos;		// 注： static const type value；当 type 是整型时，可以给定初始值！！！

	public:
		// 模拟迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		


		iterator begin() { return _str; }
		iterator end() { return _str + _size; }
		const_iterator cbegin() { return _str; }
		const_iterator cend() { return _str + _size; }
		/*
		*	无参构造
		*/
		//string() 
		//	// :_str(nullptr),		// 会出现： nullptr.c_str
		//	: _str(new char[1]),	// new char <=> new char[1]，使用后者是为了便于析构函数的统一处理！！！
		//	_size(0), 
		//	_capacity(0)
		//{
		//	_str[0] = '\0';
		//}

		/*
		*	全缺省构造函数！
		*	注意防止空 str = '\0' / nullptr 都是有问题的！
		*/
		string(const char* str = "")
			// :_str(str), _size(strlen(str)), capacity(strlen(str))	
			// strlen 是 O(N) 的，初始化列表中尽可能不出现，成员初始化与声明顺序挂钩！！！
			:_size(strlen(str))
		{
			_capacity = (_size == 0) ? 4 : _size;	// 空串构造时，防止空串的 push_back 操作导致越界问题！
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		/*
		*	拷贝构造
		*/
		string(const string& str) 
			:_size(str._size),
			_capacity(str._capacity)
		{
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
		}

		/*
		*	赋值构造：
		*		注意已存在的两个对象的大小！
		*		注意：自己给自己赋值！
		*/
		string& operator = (const string& str) {
			// 为了解决可能出现的 两个对象 的大小差距，或者说 小对象直接赋值给大对象 造成大量的空间浪费 等问题
			// 直接上来就删除被赋值对象！（注意：自己给自己赋值问题【若直接删除赋值对象就不存在了！！！】）
			
			//delete[] _str;
			//_str = new char[str._capacity + 1];
			//strcpy(_str, str._str);
			//_size = str._size;
			//_capacity = str._capacity;
			if (this != &str) {

				char* tmp = new char[str._capacity + 1];
				strcpy(_str, str._str);
				delete[] _str;
				_str = tmp;
				_size = str._size;
				_capacity = str._capacity;
			}

			return *this;
		}

		~string() {
			delete[] _str;
		}


		// 重载 [] 
		const char& operator [] (size_t idx) const
		{
			assert(idx < _size);
			return _str[idx];
		}

		char& operator [] (size_t idx)
		{
			assert(idx < _size);
			return _str[idx];
		}

		// 返回字符串大小
		size_t size() const{
			return _size;
		}

		// 返回字符串容量
		size_t capacity() const { return _capacity; }

		const char* c_str() {
			return _str;
		}

		/*
		*	实现字符串比较的运算符重载
		*		不修改成员数据的情况下，尽量带上 const ！！！
		*/
		bool operator > (const string& str) const { return strcmp(_str, str._str) > 0; }
		bool operator == (const string& str) const { return strcmp(_str, str._str) == 0; }

		bool operator >= (const string & str) const { return (*this > str._str) || (*this == str._str); }
		bool operator < (const string& str) const { return !(*this >= str._str); }
		bool operator != (const string& str) const { return !(*this == str._str); }
		bool operator <= (const string& str) const { return !(*this < str._str); }

		/*
		*	扩容 + （指定）初始化
		*/
		void resize(size_t n, char ch = '\0') {
			if (n <= _size) {
				_size = n;
				_str[_size] = '\0';
			}
			else {
				if (n > _capacity) {
					reserve(n);
				}

				size_t i = _size;
				while (i < n) {
					_str[i++] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		/*
		*	指定扩容（不能缩容）
		*/
		void reserve(size_t n) {
			if (n > _capacity) {				// 防止：缩容造成越界问题
				char* temp = new char[n + 1];	// +1：\0
				strcpy(temp, _str);				// 防止出现 new 失败，若 new 失败，就在上一行跳出到 try
				delete[] _str;
				_str = temp;
				_capacity = n;
			}
		}

		/*
		*	尾插新字符
		*/
		void push_back(char ch) {
			//if (_size+1 > _capacity) {
			//	reserve(_capacity * 2);
			//}
			//_str[_size++] = ch;
			//_str[_size] = '\0';
			// 复用代码
			insert(_size, ch);
		}

		/*
		*	尾插一个串
		*		为什么：不用 strcat ？
		*/
		void append(const char* str) {
			//size_t len = strlen(str);		// 记录插入的串长，便于判断
			//if (_size + len > _capacity) {
			//	reserve(_size + len);
			//}
			//strcpy(_str + _size, _str);
			//_size += len;
			// 复用代码
			insert(_size, str);
		}

		/*
		*	+= 运算符重载：实现遍历操作拼接字符串
		*/
		string& operator += (char ch) {
			push_back(ch);
			return *this;
		}

		string& operator += (const char* chs) {
			append(chs);
			return *this;
		}




		/*
		*	指定位置插入 字符/字符串
		*/
		string& insert(size_t idx, char ch) {
			assert(idx <= _size);
			if (_size + 1 > _capacity) {
				reserve(_capacity * 2);
			}
			//size_t end = _size;				// end 指向最后一个有效字符
			//while (end >= idx) {
			//	_str[end + 1] = _str[end];
			//	--end;
			//}
			size_t end = _size + 1;
			while (end > idx) {
				_str[end] = _str[end - 1];
				--end;
			}
			_str[idx] = ch;
			++_size;
			return *this;
		}

		string& insert(size_t idx, const char* str) {
			assert(idx <= _size);
			size_t len = strlen(str);
			// 挪动数据
			if (_size + len > _capacity) {			// 防止数据插入的越界
				reserve(_capacity + len);
			}
			size_t end = _size + len;
			while (end > idx+len-1) {
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + idx, str, len);
			_size += len;
			return *this;
		}

		/*
		*	清除字符串内容
		*/
		void erase(size_t idx, size_t len = npos) {
			if (len == npos || idx + len >= _size) {
				_str[idx] = '\0';
				_size = idx;
			}
			else {
				strcpy(_str + idx, _str + idx + len);
				_size -= len;
			}
		}

		/*
		*	字符串对象的交换
		*/
		void swap(string& str) {
			std::swap(_str, str._str);
			std::swap(_capacity, str._capacity);
			std::swap(_size, str._size);
		}

		/*
		*	指定字符查找
		*/
		size_t find(char ch, size_t idx = 0) {
			assert(idx <= _size);
			for (size_t i = idx; i < _size; i++) {
				if (_str[i] == ch) return i;
			}
			return npos;
		}

		/*
		*	指定字符串查找
		*/
		size_t find(const char* str, size_t idx = 0) {
			assert(idx <= _size);
			char* ptr = strstr(_str + idx, str);	// 暴力匹配
			if (ptr == nullptr) return npos;
			else return ptr - _str;
		}

		void clear() {
			_str[0] = '\0';
			_size = 0;
		}

	};

	const size_t string::npos = -1;

	/*
	*	流插入与流提取的重载
	*/
	std::ostream& operator << (std::ostream& out, const string& str) {
		for (size_t i = 0; i < str.size(); i++) {
			out << str[i];
		}
		return out;
	}
	std::istream& operator >> (std::istream& in, string& str) {
		str.clear();
		char ch = in.get();
		//while (ch != ' ' && ch != '\n') {
		//	str += ch;
		//	ch = in.get();
		//}

		// 应对大量的一次输入，导致的频繁扩容
		char buff[128];
		size_t i = 0;
		while (ch != ' ' && ch != '\n') {
			buff[i++] = ch;
			if (i == 127) {
				buff[127] = '\0';
				str += buff;
				i = 0;
			}
			ch = in.get();
		}

		if (i != 0) {
			buff[i] = '\0';
			str += buff;
		}

		return in;
	}

	// 测试构造函数
	void test1() {
		string s1;
		string s2 = "hello world";
		string s3;

		s2 = s2;
		s3 = s2;

		std::cout << s1.c_str() << std::endl;
		std::cout << s2.c_str() << std::endl;
		std::cout << s3.c_str() << std::endl;
	}

	// 测试使用 [] 遍历，及修改
	void print(const string & str) {
		for (int i = 0; i < str.size(); i++) {
			std::cout << str[i] << ' ';
		}
		std::cout << std::endl;
	}

	void test2() {
		string s2 = "hello world";
		print(s2);

		s2[0]++;
		print(s2);
	}

	// 模拟迭代器遍历测试
	void test3() {
		string s2 = "hello world";
		string::iterator iter = s2.begin();
		while (iter != s2.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;
	}

	// 扩容测试：resize + reserve
	void test4() {
		string s1 = "123456789";
		std::cout << s1.capacity() << std::endl;
		s1.resize(20, 'x');
		std::cout << s1.c_str() << std::endl;
		std::cout << s1.capacity() << std::endl;
		s1.reserve(30);
		std::cout << s1.capacity() << std::endl;
		s1.reserve(10);
		std::cout << s1.capacity() << std::endl;
	}

	// 测试插入字符 / 字符串
	void test5() {
		string s1 = "123456789";
		std::cout << s1.c_str() << std::endl;
		s1.insert(0, 'x');
		std::cout << s1.c_str() << std::endl;
		s1.insert(s1.size() - 2, 'y');
		std::cout << s1.c_str() << std::endl;


		s1.insert(0, "aaa");
		std::cout << s1.c_str() << std::endl;
		std::cout << s1.capacity() << std::endl;
		s1.insert(5, "qwertyuiopasdfghjklzxcvbnm");
		std::cout << s1.c_str() << std::endl;
		std::cout << s1.capacity() << std::endl;
	}


	// 测试删除
	void test6() {
		string s1 = "123456789";
		string s2 = "123456789";
		string s3 = "123456789";
		s1.erase(5, 3);
		s2.erase(5, 8);
		s3.erase(5);
		std::cout << s1.c_str() << std::endl;
		std::cout << s2.c_str() << std::endl;
		std::cout << s3.c_str() << std::endl;

	}

	// 测试流插入与流提取
	void test8() {
		string s1 = "123456789";
		std::cout << s1 << std::endl;

	}

}