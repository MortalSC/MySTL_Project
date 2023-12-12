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
		*	无参构造
		*/
		vector()
			:_start(nullptr),			// 指向起始位置
			_finish(nullptr),			// 指向最后一个有效元素的下一个位置
			_end_of_storage(nullptr)	// 始终指向容器结束的下一个位置
		{}

		/*
		*	指定大小构造
		*		注：匿名对象的生命周期旨在使用行，但是 const 引用 可以延长其生命周期，即延长到const引用变量的生命结束！
		*/
		vector(size_t n, const T& data = T())
			:_start(nullptr),			// 指向起始位置
			_finish(nullptr),			// 指向最后一个有效元素的下一个位置
			_end_of_storage(nullptr)	// 始终指向容器结束的下一个位置
		{
			reserve(n);
			for (size_t i = 0; i < n; i++) {
				push_back(data);
			}
		}
		vector(int n, const T& data = T())
			:_start(nullptr),			// 指向起始位置
			_finish(nullptr),			// 指向最后一个有效元素的下一个位置
			_end_of_storage(nullptr)	// 始终指向容器结束的下一个位置
		{
			reserve(n);
			for (size_t i = 0; i < n; i++) {
				push_back(data);
			}
		}


		/*
		*	迭代器构造
		*/
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) {
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		/*
		*	拷贝构造
		*/
		vector(const vector<T>& v) {
			reserve(v.capacity());
			//for (size_t i = 0; i < n; i++) {
			//	push_back(v[i]);
			//}
			//memcpy(_start, v._start, sizeof(T) * v.size());	// 只能解决内置类型！不安全！
			//_start = new T[v.capcity()];
			for (size_t i = 0; i < v.size(); i++) {
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}

		/*
		*	析构函数
		*/
		~vector() {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		/*
		*	扩容：防止缩容问题
		*/
		void reserve(size_t n_size) {
			if (n_size > capacity()) {
				T* temp = new T[n_size];
				size_t sz = size();

				if (_start) {
					// memcpy(temp, _start, sizeof(T) * size());	// 导致深层次的浅拷贝问题
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

		size_t capacity() const { return _end_of_storage - _start; }	// 获取容器大小
		size_t size() const { return _finish - _start; }				// 获取元素个数

		/*
		*	重新定容：resize
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
		*	判断容器是否为空
		*/
		bool empty() { return _start == _finish; }

		/*
		*	尾插元素
		*/
		void push_back(const T& data) {
			if (_finish == _end_of_storage) {							// 扩容判断！
				reserve((capacity() == 0) ? 4 : capacity() * 2);		// 设计为两倍扩容
			}
			*_finish = data;
			++_finish;
		}


		/*
		*	尾部删除
		*/
		void pop_back() {
			assert(!empty());
			--_finish;
		}

		/*
		*	设计 [] 访问重载支持
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
		*	指定位置插入
		*/
		//void insert(iterator idx, const T& data) {
		// 迭代器失效的情形二
		/*
		*
		*/
		iterator insert(iterator idx, const T& data) {
			assert(idx >= _start);
			assert(idx <= _finish);
			if (_finish == _end_of_storage) {							// 扩容判断！
				//reserve((capacity() == 0) ? 4 : capacity() * 2);		// 设计为两倍扩容

				// 修正：防止迭代器失效：（情形一）
				/*
				* 情形一：
				* 在插入过程中！发生了迭代器失效：
				* 原因：扩容方式是开辟新的空间，再将数据拷贝到新空间，然后释放旧空间！
				* 关键点：\_start、\_finish、\_end_of_storage 都会随之更新，
				* 但是作为标记插入位置的 idx 不会随即更新，会因为旧空间的释放而随之丢失！
				*/
				size_t offset = idx - _start;	// 解决方式，扩容前记录！
				reserve((capacity() == 0) ? 4 : capacity() * 2);		// 设计为两倍扩容
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
		iterator erase(iterator idx) {	// 应对迭代器失效
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
		*	迭代器
		*/
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }
	};

	// 测试无参构造、尾插法及其涉及的相关函数，如：扩容、获取容量、[]遍历 等
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


	// 测试迭代器遍历，及元素尾删
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


	// 指定位置插入测试
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
		auto pter = v.insert(idx, 2222);	// 迭代器失效的情形二的应用补充，后续修改数据！
		iter = v.begin();
		while (iter != v.end()) {
			std::cout << *iter << " ";
			iter++;
		}
		std::cout << std::endl;

		(*pter)++;
		testprint(v);
	}

	// 测试指定位置删除
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

	// 测试其他构造函数
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