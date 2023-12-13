#pragma warning ( disable : 4996 )
#pragma once

namespace STL {
	template <class T>
	struct list_node {
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;
		list_node(const T& data = T()) :_next(nullptr),_prev(nullptr),_data(data){}
	};

	// 封装迭代器
	/*
	* 是否需要析构函数？
	* 不需要！迭代器只是拿到了结点的访问权，而不是归属权，结点空间的释放是 list 的事，和迭代器无关。
	*/
	//template <class T>
	template <class T, class Ref>	// 扩展实现 const 迭代器，使用第二个模板参数解决返回值问题
	struct __list_iterator {
		typedef list_node<T> node;	// 取别名
		node* _node;				// 结点指针
		// 构造函数
		__list_iterator(node* ptr_node):_node(ptr_node){}
		// 解引用
		//T& operator * () { return _node->_data; }
		Ref operator * () { return _node->_data; }
		
		// 前置++
		__list_iterator<T, Ref>& operator++() {
			_node = _node->_next;
			return *this;
		}
		// 后置++
		__list_iterator<T, Ref> operator ++ (int) {
			__list_iterator<T, Ref>& temp(*this);
			_node = _node->_next;
			return temp;
		}
		// 前置--
		__list_iterator<T, Ref>& operator--() {
			_node = _node->_next;
			return *this;
		}
		// 后置--
		__list_iterator<T, Ref> operator -- (int) {
			__list_iterator<T, Ref>& temp(*this);
			_node = _node->prev;
			return temp;
		}

		// 不等
		bool operator != (const __list_iterator<T, Ref>& pnode) {
			return _node != pnode._node;
		}
		// 相等
		bool operator == (const __list_iterator<T, Ref>& pnode) {
			return _node == pnode._node;
		}
	};



	template<class T>
	class list {

		typedef list_node<T> node;
	public:
		//typedef __list_iterator<T> iterator;		// 迭代器【注意不要使用引用！！！】
		typedef __list_iterator<T, T&> iterator;
		typedef __list_iterator<T, const T&> const_iterator;
		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); }
		const_iterator cbegin() { return const_iterator(_head->_next); }
		const_iterator cend() { return const_iterator(_head); }
	private:
		list_node<T>* _head;
	public:
		list() {
			_head = new list_node<T>;
			_head->_next = _head;
			_head->_prev = _head;
		}
		void push_back(const T& data) {
			node* tail = _head->_prev;				// 指向当前链表的尾部
			node* add_node = new node(data);		// 构造新结点
			//链接
			tail->_next = add_node;
			add_node->_prev = tail;
			add_node->_next = _head;
			_head->_prev = add_node;
		}

		bool empty() { return _head == _head->_next; }
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
}
