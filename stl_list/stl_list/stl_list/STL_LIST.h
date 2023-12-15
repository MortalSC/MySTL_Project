#pragma warning ( disable : 4996 )
#pragma once
#include <cassert>

namespace STL {
	template <class T>
	struct list_node {
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;
		list_node(const T& data = T()) :_next(nullptr),_prev(nullptr),_data(data){}
	};

	/*
	* 迭代器的两种实现：
	*	1. 迭代器就是原生指针！
	*	2. 迭代器就是自定义类型对原生指针的封装，模拟指针的行为！
	*/

	// 封装迭代器
	/*
	* 是否需要析构函数？
	* 不需要！迭代器只是拿到了结点的访问权，而不是归属权，结点空间的释放是 list 的事，和迭代器无关。
	*/
	//template <class T>
	template <class T, class Ref, class Ptr>	// 扩展实现 const 迭代器，使用第二个模板参数解决返回值问题
	struct __list_iterator {
		typedef list_node<T> node;	// 取别名
		node* _node;				// 结点指针
		// 构造函数
		__list_iterator(node* ptr_node):_node(ptr_node){}
		// 解引用
		//T& operator * () { return _node->_data; }
		Ref operator * () { return _node->_data; }
		
		// 前置++
		__list_iterator<T, Ref, Ptr>& operator++() {
			_node = _node->_next;
			return *this;
		}
		// 后置++
		__list_iterator<T, Ref, Ptr> operator ++ (int) {
			__list_iterator<T, Ref, Ptr>& temp(*this);
			_node = _node->_next;
			return temp;
		}
		// 前置--
		__list_iterator<T, Ref, Ptr>& operator--() {
			_node = _node->_next;
			return *this;
		}
		// 后置--
		__list_iterator<T, Ref, Ptr> operator -- (int) {
			__list_iterator<T, Ref, Ptr>& temp(*this);
			_node = _node->prev;
			return temp;
		}

		// 不等
		bool operator != (const __list_iterator<T, Ref, Ptr>& pnode) {
			return _node != pnode._node;
		}
		// 相等
		bool operator == (const __list_iterator<T, Ref, Ptr>& pnode) {
			return _node == pnode._node;
		}

		// 支持 -> 访问
		//T* operator -> () { return &(_node->_data); }
		
		// 优化解决 const 迭代器限制【引入第三个模板参数：Ptr】
		Ptr operator -> () { return &(_node->_data); }

	};




	template<class T>
	class list {

		typedef list_node<T> node;
	public:
		//typedef __list_iterator<T> iterator;		// 迭代器【注意不要使用引用！！！】
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); }
		const_iterator cbegin() const { return const_iterator(_head->_next); }
		const_iterator cend() const { return const_iterator(_head); }
	private:
		list_node<T>* _head;
	public:
		list() {
			_head = new list_node<T>;
			_head->_next = _head;
			_head->_prev = _head;
		}
		/*
		*	迭代器构造ls2(ls1.begin(), ls1.end())
		*/
		template<class InputIterator>
		list(InputIterator first, InputIterator last){
			_head = new list_node<T>;
			_head->_next = _head;
			_head->_prev = _head;
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		void swap(list<T>& ls) {
			std::swap(_head, ls._head);
		}

		/*
		*	拷贝构造：ls1(ls2)
		*/
		list(const list<T>& ls) {
			_head = new list_node<T>;
			_head->_next = _head;
			_head->_prev = _head;
			list<T> temp(ls.cbegin(), ls.cend());
			swap(temp);
		}

		/*
		*	赋值运算符重载
		*		注意参数：不使用 引用！！！
		*/
		list<T>& operator = (list<T> ls) {
			swap(ls);
			return *this;
		}

		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}

		/*
		*	清理链表数据：不删头结点
		*/
		void clear() {
			iterator iter = begin();
			while (iter != end()) {
				iter = erase(iter);		// 写法一
				//erase(iter++);			// 写法二：必须是 后置 ++
			}
		}

		/*
		*	尾插法插入元素
		*/
		//void push_back(const T& data) {
		//	node* tail = _head->_prev;				// 指向当前链表的尾部
		//	node* add_node = new node(data);		// 构造新结点
		//	//链接
		//	tail->_next = add_node;
		//	add_node->_prev = tail;
		//	add_node->_next = _head;
		//	_head->_prev = add_node;
		//}
		// 尾插的另一种写法（复用）
		void push_back(const T& data) { insert(end(), data); }

		bool empty() { return _head == _head->_next; }

		/*
		*	指定位置之前插入新结点
		*		idx：指定位置上的结点，即在其前插入一个结点
		*/
		void insert(iterator idx, const T& data){
			node* cur = idx._node;					// 标记插入位置
			node* prev = cur->_prev;			// 找到插入位置的前一个结点
			// 构造新结点
			node* new_node = new node(data);
			prev->_next = new_node;
			new_node->_prev = prev;
			new_node->_next = cur;
			cur->_prev = new_node;
		}

		/* 删除指定位置上的结点 */
		iterator erase(iterator idx){
			assert(idx != end());
			node* prev = idx._node->_prev;				// 标记删除点的前一个结点
			node* next = idx._node->_next;				// 标记删除点的后一个结点
			// 被删除点的前后链接：实现删除
			prev->_next = next;
			next->_prev = prev;
			delete idx._node;		// 迭代器失效点！！！
			return iterator(next);
		}

		/* 尾删结点 */
		void pop_back() { erase(_head->_prev); }

		/* 头删 */
		void pop_front() { erase(begin()); }

		/* 头插 */
		void push_front(const T& data) { insert(begin(), data); }
	};



	// 测试简单构造和尾插法
	void test1() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);

	}

	// 测试迭代器的封装，以及遍历
	void test2() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);
		std::cout << ls.empty() << std::endl;

		list<int>::iterator iter = ls.begin();// 提问目前的拷贝是深/浅？
		// => 浅：此处迭代器的就是相当于指针存储地址，值传递，
		// 尽管地址拷贝给新的变量，但是指向的位置不变！故不需要深拷贝！
		while (iter != ls.end()) {
			std::cout << *iter << ' ';
			++iter;
		}
		std::cout << std::endl;

		std::cout << ls.empty() << std::endl;
		for (auto e : ls) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}

	// 测试 const 迭代器
	void test3() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);

		list<int>::const_iterator iter = ls.cbegin();
		while (iter != ls.cend()) {
			std::cout << *iter << ' ';
			++iter;
		}
		std::cout << std::endl;
	}

	// 测试自定义类型与迭代器
	struct A {
		int _a;
		int _b;
		A(int a = 0, int b = 0):_a(a),_b(b){}
	};
	void test4() {
		list<A> ls;
		ls.push_back(A(1, 1));
		ls.push_back(A(1, 2));
		ls.push_back(A(1, 3));

		list<A>::iterator iter = ls.begin();
		while (iter != ls.end()) {
			std::cout << iter.operator->()->_a << " : " << iter.operator->()->_b << std::endl;
			std::cout << iter->_a << " : " << iter->_b << std::endl;

			++iter;
		}
	}


	// 测试指定位置插入
	void test5() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);

		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 在 2 之前插入 666 
		list<int>::iterator iter = ls.begin();
		iter++;
		ls.insert(iter, 666);

		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 尾部插入 777
		iter = ls.end();
		ls.insert(iter, 777);
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}

	// 测试指定位置删除、头删、尾插、头插、尾插
	void test6() {
		list<int> ls;
		for (int i = 1; i < 7; i++) {
			ls.push_back(i);
		}
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 删除第二个结点
		list<int>::iterator iter = ls.begin();
		iter++;
		ls.erase(iter);
		std::cout << "删除第二个结点" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 头插 666
		ls.push_front(666);
		std::cout << "头插 666" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 尾插 777
		ls.push_back(777);
		std::cout << "尾插 777" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 头删
		ls.pop_front();
		std::cout << "头删" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// 尾删
		ls.pop_back();
		std::cout << "尾删" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}


	// 测试 clear 清除链表结点
	void test7() {
		list<int> ls;
		for (int i = 1; i < 7; i++) {
			ls.push_back(i);
		}
		std::cout << "是否为空：" << ls.empty() << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		ls.clear();
		std::cout << "是否为空：" << ls.empty() << std::endl;

		for (int i = 1; i < 7; i++) {
			ls.push_back(i*20);
		}
		std::cout << "是否为空：" << ls.empty() << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}

	// 测试 迭代器构造 和 拷贝构造
	void test8() {
		list<int> ls1;
		for (int i = 1; i < 7; i++) {
			ls1.push_back(i);
		}
		for (auto e : ls1) std::cout << e << " ";
		std::cout << std::endl;

		// 迭代器构造
		list<int> ls2(ls1.begin(), ls1.end());
		for (auto e : ls2) std::cout << e << " ";
		std::cout << std::endl;

		// 拷贝构造
		list<int> ls3(ls1);
		for (auto e : ls3) std::cout << e << " ";
		std::cout << std::endl;

		// 赋值运算符重载
		list<int> ls4 = ls1;
		for (auto e : ls3) std::cout << e << " ";
		std::cout << std::endl;
	}
}
