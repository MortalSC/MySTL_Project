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

	// ��װ������
	/*
	* �Ƿ���Ҫ����������
	* ����Ҫ��������ֻ���õ��˽��ķ���Ȩ�������ǹ���Ȩ�����ռ���ͷ��� list ���£��͵������޹ء�
	*/
	//template <class T>
	template <class T, class Ref>	// ��չʵ�� const ��������ʹ�õڶ���ģ������������ֵ����
	struct __list_iterator {
		typedef list_node<T> node;	// ȡ����
		node* _node;				// ���ָ��
		// ���캯��
		__list_iterator(node* ptr_node):_node(ptr_node){}
		// ������
		//T& operator * () { return _node->_data; }
		Ref operator * () { return _node->_data; }
		
		// ǰ��++
		__list_iterator<T, Ref>& operator++() {
			_node = _node->_next;
			return *this;
		}
		// ����++
		__list_iterator<T, Ref> operator ++ (int) {
			__list_iterator<T, Ref>& temp(*this);
			_node = _node->_next;
			return temp;
		}
		// ǰ��--
		__list_iterator<T, Ref>& operator--() {
			_node = _node->_next;
			return *this;
		}
		// ����--
		__list_iterator<T, Ref> operator -- (int) {
			__list_iterator<T, Ref>& temp(*this);
			_node = _node->prev;
			return temp;
		}

		// ����
		bool operator != (const __list_iterator<T, Ref>& pnode) {
			return _node != pnode._node;
		}
		// ���
		bool operator == (const __list_iterator<T, Ref>& pnode) {
			return _node == pnode._node;
		}
	};



	template<class T>
	class list {

		typedef list_node<T> node;
	public:
		//typedef __list_iterator<T> iterator;		// ��������ע�ⲻҪʹ�����ã�������
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
			node* tail = _head->_prev;				// ָ��ǰ�����β��
			node* add_node = new node(data);		// �����½��
			//����
			tail->_next = add_node;
			add_node->_prev = tail;
			add_node->_next = _head;
			_head->_prev = add_node;
		}

		bool empty() { return _head == _head->_next; }
	};



	// ���Լ򵥹����β�巨
	void test1() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);

	}

	// ���Ե������ķ�װ���Լ�����
	void test2() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);
		std::cout << ls.empty() << std::endl;

		list<int>::iterator iter = ls.begin();// ����Ŀǰ�Ŀ�������/ǳ��
		// => ǳ���˴��������ľ����൱��ָ��洢��ַ��ֵ���ݣ�
		// ���ܵ�ַ�������µı���������ָ���λ�ò��䣡�ʲ���Ҫ�����
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

	// ���� const ������
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
