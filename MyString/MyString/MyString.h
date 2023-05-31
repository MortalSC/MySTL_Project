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
		String() 											// Ĭ�Ϲ���
			:_str(new char[1])								// �˴����ܸ� nullptr����Ϊ��������ʵ�ֹ����д��ڷ��ض��������ص��� nullptr���ն��� �������
			,_size(0)
			,_capacity(0)
		{
			_str[0] = '\0';									
		}

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
		String(const String& str) 
			:_str(new char[str._capacity + 1])
			,_size(str._size)
			,_capacity(str._capacity)
		{
			strcpy(_str, str._str);
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


		/* ����ϵ�к��� */
		// []�����ʷ�ʽ
		char& operator [] (size_t pos) {
			assert(pos>=0);
			return _str[pos];
		}

		const char& operator [] (size_t pos) const
		{
			assert(pos);
			return _str[pos];
		}

		
		// ���� char* ����
		const char* c_str() const
		{
			return _str;
		}

		/* ��ֵ��������� */
		String& operator = (const String& str) {
			if (this != &str) {								// ���� s1
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

		/* ��ֵ��������أ���ʽд�� */
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
		size_t _size;										// ��¼��ǰ �� ���ַ���
		size_t _capacity;									// ��¼��ǰ �� �ɴ洢������ַ��������� '\0'��
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