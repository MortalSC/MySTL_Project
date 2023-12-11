#pragma warning( disable : 4996)
#pragma once
#include <iostream>
#include<cstring>
#include <cstdio>
#include <cassert>


namespace stl {


	class string {
	private:
		char* _str;				// ��
		size_t _size;			// ʵ�ʴ���
		size_t _capacity;		// ������󳤶ȣ�������
		// static size_t npos;		
		// �﷨�㣺��̬��Ա�������ܸ���ȱʡֵ�����������ĸ�ֵ��ʼ���Ǹ���ʼ���б��õģ�
		// ���ǣ���̬��Ա���������ڳ�ʼ����Ա�б��ʼ���ģ������������ࡣ
		static const size_t npos;		// ע�� static const type value���� type ������ʱ�����Ը�����ʼֵ������

	public:
		// ģ�������
		typedef char* iterator;
		typedef const char* const_iterator;
		


		iterator begin() { return _str; }
		iterator end() { return _str + _size; }
		const_iterator cbegin() { return _str; }
		const_iterator cend() { return _str + _size; }
		/*
		*	�޲ι���
		*/
		//string() 
		//	// :_str(nullptr),		// ����֣� nullptr.c_str
		//	: _str(new char[1]),	// new char <=> new char[1]��ʹ�ú�����Ϊ�˱�������������ͳһ��������
		//	_size(0), 
		//	_capacity(0)
		//{
		//	_str[0] = '\0';
		//}

		/*
		*	ȫȱʡ���캯����
		*	ע���ֹ�� str = '\0' / nullptr ����������ģ�
		*/
		string(const char* str = "")
			// :_str(str), _size(strlen(str)), capacity(strlen(str))	
			// strlen �� O(N) �ģ���ʼ���б��о����ܲ����֣���Ա��ʼ��������˳��ҹ�������
			:_size(strlen(str))
		{
			_capacity = (_size == 0) ? 4 : _size;	// �մ�����ʱ����ֹ�մ��� push_back ��������Խ�����⣡
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		/*
		*	��������
		*/
		string(const string& str) 
			:_size(str._size),
			_capacity(str._capacity)
		{
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
		}

		/*
		*	��ֵ���죺
		*		ע���Ѵ��ڵ���������Ĵ�С��
		*		ע�⣺�Լ����Լ���ֵ��
		*/
		string& operator = (const string& str) {
			// Ϊ�˽�����ܳ��ֵ� �������� �Ĵ�С��࣬����˵ С����ֱ�Ӹ�ֵ������� ��ɴ����Ŀռ��˷� ������
			// ֱ��������ɾ������ֵ���󣡣�ע�⣺�Լ����Լ���ֵ���⡾��ֱ��ɾ����ֵ����Ͳ������ˣ���������
			
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


		// ���� [] 
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

		// �����ַ�����С
		size_t size() const{
			return _size;
		}

		// �����ַ�������
		size_t capacity() const { return _capacity; }

		const char* c_str() {
			return _str;
		}

		/*
		*	ʵ���ַ����Ƚϵ����������
		*		���޸ĳ�Ա���ݵ�����£��������� const ������
		*/
		bool operator > (const string& str) const { return strcmp(_str, str._str) > 0; }
		bool operator == (const string& str) const { return strcmp(_str, str._str) == 0; }

		bool operator >= (const string & str) const { return (*this > str._str) || (*this == str._str); }
		bool operator < (const string& str) const { return !(*this >= str._str); }
		bool operator != (const string& str) const { return !(*this == str._str); }
		bool operator <= (const string& str) const { return !(*this < str._str); }

		/*
		*	���� + ��ָ������ʼ��
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
		*	ָ�����ݣ��������ݣ�
		*/
		void reserve(size_t n) {
			if (n > _capacity) {				// ��ֹ���������Խ������
				char* temp = new char[n + 1];	// +1��\0
				strcpy(temp, _str);				// ��ֹ���� new ʧ�ܣ��� new ʧ�ܣ�������һ�������� try
				delete[] _str;
				_str = temp;
				_capacity = n;
			}
		}

		/*
		*	β�����ַ�
		*/
		void push_back(char ch) {
			//if (_size+1 > _capacity) {
			//	reserve(_capacity * 2);
			//}
			//_str[_size++] = ch;
			//_str[_size] = '\0';
			// ���ô���
			insert(_size, ch);
		}

		/*
		*	β��һ����
		*		Ϊʲô������ strcat ��
		*/
		void append(const char* str) {
			//size_t len = strlen(str);		// ��¼����Ĵ����������ж�
			//if (_size + len > _capacity) {
			//	reserve(_size + len);
			//}
			//strcpy(_str + _size, _str);
			//_size += len;
			// ���ô���
			insert(_size, str);
		}

		/*
		*	+= ��������أ�ʵ�ֱ�������ƴ���ַ���
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
		*	ָ��λ�ò��� �ַ�/�ַ���
		*/
		string& insert(size_t idx, char ch) {
			assert(idx <= _size);
			if (_size + 1 > _capacity) {
				reserve(_capacity * 2);
			}
			//size_t end = _size;				// end ָ�����һ����Ч�ַ�
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
			// Ų������
			if (_size + len > _capacity) {			// ��ֹ���ݲ����Խ��
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
		*	����ַ�������
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
		*	�ַ�������Ľ���
		*/
		void swap(string& str) {
			std::swap(_str, str._str);
			std::swap(_capacity, str._capacity);
			std::swap(_size, str._size);
		}

		/*
		*	ָ���ַ�����
		*/
		size_t find(char ch, size_t idx = 0) {
			assert(idx <= _size);
			for (size_t i = idx; i < _size; i++) {
				if (_str[i] == ch) return i;
			}
			return npos;
		}

		/*
		*	ָ���ַ�������
		*/
		size_t find(const char* str, size_t idx = 0) {
			assert(idx <= _size);
			char* ptr = strstr(_str + idx, str);	// ����ƥ��
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
	*	������������ȡ������
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

		// Ӧ�Դ�����һ�����룬���µ�Ƶ������
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

	// ���Թ��캯��
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

	// ����ʹ�� [] ���������޸�
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

	// ģ���������������
	void test3() {
		string s2 = "hello world";
		string::iterator iter = s2.begin();
		while (iter != s2.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;
	}

	// ���ݲ��ԣ�resize + reserve
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

	// ���Բ����ַ� / �ַ���
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


	// ����ɾ��
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

	// ����������������ȡ
	void test8() {
		string s1 = "123456789";
		std::cout << s1 << std::endl;

	}

}