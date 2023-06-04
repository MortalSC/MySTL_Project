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
		/* ��������ʵ�֣�string �ĵ�����ʵ��ԭ�����ָ�� */
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() {
			return _str;
		}

		iterator end() {
			return _str + _size;							// ע�ⷵ�ص����ַ���β������һ��λ�ã��� + ���� _size
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}


		/* ���캯�� */
		//String() 											// Ĭ�Ϲ���
		//	:_str(new char[1])								// �˴����ܸ� nullptr����Ϊ��������ʵ�ֹ����д��ڷ��ض��������ص��� nullptr���ն��� �������
		//	,_size(0)
		//	,_capacity(0)
		//{
		//	_str[0] = '\0';									
		//}

#if 0
		// String(const char* str = '\0')
		String(const char* str = "")						// ע�⣺���ڳ����ַ���Ĭ�ϻẬ '\0'
			:_str(new char[strlen(str)+1])					// strlen Ч�ʣ�O(N)
			,_size(strlen(str))
			,_capacity(strlen(str))							// ע��˴������������� '\0'
			/* ע�⣺����˳��������ڷţ�ԭ�����ڲ����б�ĳ�ʼ��˳����������˳����صģ� */
		{
			strcpy(_str, str);
		}
#endif
		/* ���Ϻ������޸Ľ��飺���ڶ��ʹ���� strlen ����Ч�ʲ��ߣ����Կ���ѡ�����ó�ʼ���б�д��ʵ�� */
		String(const char* str = "") {
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];					// �ռ�����
			strcpy(_str, str);
		}

		// �������죺�����
		//String(const String& str) 
		//	:_str(new char[str._capacity + 1])
		//	,_size(str._size)
		//	,_capacity(str._capacity)
		//{
		//	strcpy(_str, str._str);
		//}




		/* ����ϵ�к��� */
		// []�����ʷ�ʽ
		char& operator [] (size_t pos) {
			assert(pos>=0);
			return _str[pos];
		}

		const char& operator [] (size_t pos) const
		{
			assert(pos>=0);
			return _str[pos];
		}

		
		// ���� char* ����
		const char* c_str() const
		{
			return _str;
		}

		/* ��ֵ��������� */
//		String& operator = (const String& str) {
//			if (this != &str) {								// ��ֹ�����Լ����Լ���ֵ
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
		/* ��д�� */
		//String& operator = (const String& str) {
		//	if (this != &str) {
		//		String temp(str);
		//		swap(temp);
		//	}
		//	return *this;
		//}

		String& operator = (String str) {		// ע������б�ֱ��ʹ�ô�ֵ���Σ�str ֱ�ӾͶ���������д���е� temp
			swap(str);
			return *this;
		}


		void swap(String& temp) {
			::swap(_str, temp._str);
			::swap(_size, temp._size);
			::swap(_capacity, temp._capacity);
		}

		/* �������죺��ʽд�� */
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
				// ��������
				reserve(n);
				for (size_t i = _size; i < n ; i++) {
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else {
				// ɾ������
				_str[n] = '\0';
				_size = n;
			}
		}

		void push_back(char ch)
		{
			// ��������
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			// �����������
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			strcpy(_str + len, str);		// ����ʹ��strcat�����ã�����Ч�ʵͣ�ƴ�ӵ�ʱ��ÿ����Ҫ�� '\0'
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
			/* ����ƥ�� */
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



		// ��������
		~String() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		/* ����ϵ�к��� */
		// ��ȡ��ǰ�ַ���
		size_t size() const
		{
			return _size;
		}

	private:
		char* _str;
		size_t _size;										// ��¼��ǰ �� ���ַ���
		size_t _capacity;									// ��¼��ǰ �� �ɴ洢�������Ч�ַ��������� '\0'��
	public:
		const static size_t npos = -1;						// �����������ֵ
	};

	ostream& operator << (ostream& out, const String& str) {
		for (size_t i = 0; i < str.size(); ++i) {
			out << str[i];
		}
		return out;
	}
	// ������������ȡ
	istream& operator >> (istream& in, String& str) {
		//char ch;
		//ch = in.get();
		//while (ch != ' ' && ch != '\n') {
		//	str += ch;
		//	ch = in.get();
		//}
		/* �Ż��� */
		char ch;
		ch = in.get();
		str.clear();
		const size_t N = 32;
		char buff[N];								// ģ�⻺����

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