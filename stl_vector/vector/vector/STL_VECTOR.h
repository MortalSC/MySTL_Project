#pragma warning( disable :4996 )
#pragma once
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <string>
namespace STL {

	template <class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	public:
		/*
		*	�޲ι���
		*/
		vector()
			:_start(nullptr),			// ָ����ʼλ��
			_finish(nullptr),			// ָ�����һ����ЧԪ�ص���һ��λ��
			_end_of_storage(nullptr)	// ʼ��ָ��������������һ��λ��
		{}

		/*
		*	ָ����С����
		*		ע�������������������ּ��ʹ���У����� const ���� �����ӳ����������ڣ����ӳ���const���ñ���������������
		*/
		vector(size_t n, const T& data = T())
			:_start(nullptr),			// ָ����ʼλ��
			_finish(nullptr),			// ָ�����һ����ЧԪ�ص���һ��λ��
			_end_of_storage(nullptr)	// ʼ��ָ��������������һ��λ��
		{
			reserve(n);
			for (size_t i = 0; i < n; i++) {
				push_back(data);
			}
		}
		vector(int n, const T& data = T())
			:_start(nullptr),			// ָ����ʼλ��
			_finish(nullptr),			// ָ�����һ����ЧԪ�ص���һ��λ��
			_end_of_storage(nullptr)	// ʼ��ָ��������������һ��λ��
		{
			reserve(n);
			for (size_t i = 0; i < n; i++) {
				push_back(data);
			}
		}


		/*
		*	����������
		*/
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) {
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		/*
		*	��������
		*/
		vector(const vector<T>& v) {
			reserve(v.capacity());
			//for (size_t i = 0; i < n; i++) {
			//	push_back(v[i]);
			//}
			//memcpy(_start, v._start, sizeof(T) * v.size());	// ֻ�ܽ���������ͣ�����ȫ��
			//_start = new T[v.capcity()];
			for (size_t i = 0; i < v.size(); i++) {
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}

		/*
		*	��������
		*/
		~vector() {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		/*
		*	���ݣ���ֹ��������
		*/
		void reserve(size_t n_size) {
			if (n_size > capacity()) {
				T* temp = new T[n_size];
				size_t sz = size();

				if (_start) {
					// memcpy(temp, _start, sizeof(T) * size());	// �������ε�ǳ��������
					for (size_t i = 0; i < sz; i++) {
						temp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = temp;
				//_finish = temp + size();		// size() = _finish - _start
				_finish = _start + sz;
				_end_of_storage = temp + n_size;
			}
		}

		size_t capacity() const { return _end_of_storage - _start; }	// ��ȡ������С
		size_t size() const { return _finish - _start; }				// ��ȡԪ�ظ���

		/*
		*	���¶��ݣ�resize
		*/
		void resize(size_t n, T data = T()) {
			if (n < size()) {
				_finish = _start + n;
			}
			else {
				if (n > capacity())
				{
					reserve(n);
				}
				while (_start + n != _finish) {
					*_finish = data;
					++_finish;
				}
			}
		}

		/*
		*	�ж������Ƿ�Ϊ��
		*/
		bool empty() { return _start == _finish; }

		/*
		*	β��Ԫ��
		*/
		void push_back(const T& data) {
			if (_finish == _end_of_storage) {							// �����жϣ�
				reserve((capacity() == 0) ? 4 : capacity() * 2);		// ���Ϊ��������
			}
			*_finish = data;
			++_finish;
		}


		/*
		*	β��ɾ��
		*/
		void pop_back() {
			assert(!empty());
			--_finish;
		}

		/*
		*	��� [] ��������֧��
		*/
		T& operator [] (size_t idx) {
			assert(idx <= size());
			return _start[idx];
		}

		const T& operator [] (size_t idx) const {
			assert(idx <= size());
			return _start[idx];
		}

		/*
		*	ָ��λ�ò���
		*/
		//void insert(iterator idx, const T& data) {
		// ������ʧЧ�����ζ�
		/*
		*
		*/
		iterator insert(iterator idx, const T& data) {
			assert(idx >= _start);
			assert(idx <= _finish);
			if (_finish == _end_of_storage) {							// �����жϣ�
				//reserve((capacity() == 0) ? 4 : capacity() * 2);		// ���Ϊ��������

				// ��������ֹ������ʧЧ��������һ��
				/*
				* ����һ��
				* �ڲ�������У������˵�����ʧЧ��
				* ԭ�����ݷ�ʽ�ǿ����µĿռ䣬�ٽ����ݿ������¿ռ䣬Ȼ���ͷžɿռ䣡
				* �ؼ��㣺\_start��\_finish��\_end_of_storage ������֮���£�
				* ������Ϊ��ǲ���λ�õ� idx �����漴���£�����Ϊ�ɿռ���ͷŶ���֮��ʧ��
				*/
				size_t offset = idx - _start;	// �����ʽ������ǰ��¼��
				reserve((capacity() == 0) ? 4 : capacity() * 2);		// ���Ϊ��������
				idx = _start + offset;
			}
			iterator end = _finish - 1;
			while (end >= idx) {
				*(end + 1) = *end;
				--end;
			}
			*idx = data;
			++_finish;
			return idx;
		}

		//void erase(iterator idx) {
		iterator erase(iterator idx) {	// Ӧ�Ե�����ʧЧ
			assert(idx >= _start);
			assert(idx <= _finish);
			iterator ptr = idx + 1;
			while (ptr != _finish) {
				*(ptr - 1) = *ptr;
				++ptr;
			}
			--_finish;
			return idx;
		}

		/*
		*	������
		*/
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }
	};

	// �����޲ι��졢β�巨�����漰����غ������磺���ݡ���ȡ������[]���� ��
	void test1() {
		vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);

		for (int i = 3; i < 10; i++) {
			vec.push_back(i);
		}

		std::cout << vec.capacity() << std::endl;
		std::cout << vec.size() << std::endl;

		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << " ";
		}
		std::cout << std::endl;
	}


	// ���Ե�������������Ԫ��βɾ
	void testprint(const vector<int>& v) {
		vector<int>::const_iterator iter = v.cbegin();
		while (iter != v.cend()) {
			std::cout << *iter << " ";
			++iter;
		}
		std::cout << std::endl;
	}
	void test2() {
		vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);

		for (int i = 3; i < 10; i++) {
			vec.push_back(i);
		}

		for (auto e : vec) {
			std::cout << e << " ";
		}
		std::cout << std::endl;

		vector<int>::iterator iter = vec.begin();
		while (iter != vec.end()) {
			std::cout << *iter << " ";
			++iter;
		}
		std::cout << std::endl;


		vec.pop_back();
		vec.pop_back();
		testprint(vec);


	}


	// ָ��λ�ò������
	void test3() {
		vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i * 2 + 1);
		}

		auto iter = v.begin();
		while (iter != v.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;

		v.insert(v.begin(), 1000);
		iter = v.begin();
		while (iter != v.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;


		auto idx = std::find(v.begin(), v.end(), 15);
		auto pter = v.insert(idx, 2222);	// ������ʧЧ�����ζ���Ӧ�ò��䣬�����޸����ݣ�
		iter = v.begin();
		while (iter != v.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;

		(*pter)++;
		testprint(v);
	}

	// ����ָ��λ��ɾ��
	void test4() {
		vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i * 2 + 1);
		}
		testprint(v);

		auto idx = std::find(v.begin(), v.end(), 15);
		if (idx != v.end()) v.erase(idx);
		testprint(v);

		(*idx)++;
		testprint(v);

	}

	// �����������캯��
	void test5()
	{
		vector<int> v(10, 123);
		testprint(v);

		vector<int> vv(v);
		testprint(vv);

		vector < std::string > v1(3, "123456789");
		for (auto e : v1) {
			std::cout << e << "\t";
		}
		std::cout << std::endl;

		
	}

	
}