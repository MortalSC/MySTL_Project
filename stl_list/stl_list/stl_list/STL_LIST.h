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
	* ������������ʵ�֣�
	*	1. ����������ԭ��ָ�룡
	*	2. �����������Զ������Ͷ�ԭ��ָ��ķ�װ��ģ��ָ�����Ϊ��
	*/

	// ��װ������
	/*
	* �Ƿ���Ҫ����������
	* ����Ҫ��������ֻ���õ��˽��ķ���Ȩ�������ǹ���Ȩ�����ռ���ͷ��� list ���£��͵������޹ء�
	*/
	//template <class T>
	template <class T, class Ref, class Ptr>	// ��չʵ�� const ��������ʹ�õڶ���ģ������������ֵ����
	struct __list_iterator {
		typedef list_node<T> node;	// ȡ����
		node* _node;				// ���ָ��
		// ���캯��
		__list_iterator(node* ptr_node):_node(ptr_node){}
		// ������
		//T& operator * () { return _node->_data; }
		Ref operator * () { return _node->_data; }
		
		// ǰ��++
		__list_iterator<T, Ref, Ptr>& operator++() {
			_node = _node->_next;
			return *this;
		}
		// ����++
		__list_iterator<T, Ref, Ptr> operator ++ (int) {
			__list_iterator<T, Ref, Ptr>& temp(*this);
			_node = _node->_next;
			return temp;
		}
		// ǰ��--
		__list_iterator<T, Ref, Ptr>& operator--() {
			_node = _node->_next;
			return *this;
		}
		// ����--
		__list_iterator<T, Ref, Ptr> operator -- (int) {
			__list_iterator<T, Ref, Ptr>& temp(*this);
			_node = _node->prev;
			return temp;
		}

		// ����
		bool operator != (const __list_iterator<T, Ref, Ptr>& pnode) {
			return _node != pnode._node;
		}
		// ���
		bool operator == (const __list_iterator<T, Ref, Ptr>& pnode) {
			return _node == pnode._node;
		}

		// ֧�� -> ����
		//T* operator -> () { return &(_node->_data); }
		
		// �Ż���� const ���������ơ����������ģ�������Ptr��
		Ptr operator -> () { return &(_node->_data); }

	};




	template<class T>
	class list {

		typedef list_node<T> node;
	public:
		//typedef __list_iterator<T> iterator;		// ��������ע�ⲻҪʹ�����ã�������
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
		*	����������ls2(ls1.begin(), ls1.end())
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
		*	�������죺ls1(ls2)
		*/
		list(const list<T>& ls) {
			_head = new list_node<T>;
			_head->_next = _head;
			_head->_prev = _head;
			list<T> temp(ls.cbegin(), ls.cend());
			swap(temp);
		}

		/*
		*	��ֵ���������
		*		ע���������ʹ�� ���ã�����
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
		*	�����������ݣ���ɾͷ���
		*/
		void clear() {
			iterator iter = begin();
			while (iter != end()) {
				iter = erase(iter);		// д��һ
				//erase(iter++);			// д������������ ���� ++
			}
		}

		/*
		*	β�巨����Ԫ��
		*/
		//void push_back(const T& data) {
		//	node* tail = _head->_prev;				// ָ��ǰ�����β��
		//	node* add_node = new node(data);		// �����½��
		//	//����
		//	tail->_next = add_node;
		//	add_node->_prev = tail;
		//	add_node->_next = _head;
		//	_head->_prev = add_node;
		//}
		// β�����һ��д�������ã�
		void push_back(const T& data) { insert(end(), data); }

		bool empty() { return _head == _head->_next; }

		/*
		*	ָ��λ��֮ǰ�����½��
		*		idx��ָ��λ���ϵĽ�㣬������ǰ����һ�����
		*/
		void insert(iterator idx, const T& data){
			node* cur = idx._node;					// ��ǲ���λ��
			node* prev = cur->_prev;			// �ҵ�����λ�õ�ǰһ�����
			// �����½��
			node* new_node = new node(data);
			prev->_next = new_node;
			new_node->_prev = prev;
			new_node->_next = cur;
			cur->_prev = new_node;
		}

		/* ɾ��ָ��λ���ϵĽ�� */
		iterator erase(iterator idx){
			assert(idx != end());
			node* prev = idx._node->_prev;				// ���ɾ�����ǰһ�����
			node* next = idx._node->_next;				// ���ɾ����ĺ�һ�����
			// ��ɾ�����ǰ�����ӣ�ʵ��ɾ��
			prev->_next = next;
			next->_prev = prev;
			delete idx._node;		// ������ʧЧ�㣡����
			return iterator(next);
		}

		/* βɾ��� */
		void pop_back() { erase(_head->_prev); }

		/* ͷɾ */
		void pop_front() { erase(begin()); }

		/* ͷ�� */
		void push_front(const T& data) { insert(begin(), data); }
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

	// �����Զ��������������
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


	// ����ָ��λ�ò���
	void test5() {
		list<int> ls;
		ls.push_back(1);
		ls.push_back(2);
		ls.push_back(3);

		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// �� 2 ֮ǰ���� 666 
		list<int>::iterator iter = ls.begin();
		iter++;
		ls.insert(iter, 666);

		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// β������ 777
		iter = ls.end();
		ls.insert(iter, 777);
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}

	// ����ָ��λ��ɾ����ͷɾ��β�塢ͷ�塢β��
	void test6() {
		list<int> ls;
		for (int i = 1; i < 7; i++) {
			ls.push_back(i);
		}
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// ɾ���ڶ������
		list<int>::iterator iter = ls.begin();
		iter++;
		ls.erase(iter);
		std::cout << "ɾ���ڶ������" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// ͷ�� 666
		ls.push_front(666);
		std::cout << "ͷ�� 666" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// β�� 777
		ls.push_back(777);
		std::cout << "β�� 777" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// ͷɾ
		ls.pop_front();
		std::cout << "ͷɾ" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		// βɾ
		ls.pop_back();
		std::cout << "βɾ" << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}


	// ���� clear ���������
	void test7() {
		list<int> ls;
		for (int i = 1; i < 7; i++) {
			ls.push_back(i);
		}
		std::cout << "�Ƿ�Ϊ�գ�" << ls.empty() << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;

		ls.clear();
		std::cout << "�Ƿ�Ϊ�գ�" << ls.empty() << std::endl;

		for (int i = 1; i < 7; i++) {
			ls.push_back(i*20);
		}
		std::cout << "�Ƿ�Ϊ�գ�" << ls.empty() << std::endl;
		for (auto e : ls) std::cout << e << " ";
		std::cout << std::endl;
	}

	// ���� ���������� �� ��������
	void test8() {
		list<int> ls1;
		for (int i = 1; i < 7; i++) {
			ls1.push_back(i);
		}
		for (auto e : ls1) std::cout << e << " ";
		std::cout << std::endl;

		// ����������
		list<int> ls2(ls1.begin(), ls1.end());
		for (auto e : ls2) std::cout << e << " ";
		std::cout << std::endl;

		// ��������
		list<int> ls3(ls1);
		for (auto e : ls3) std::cout << e << " ";
		std::cout << std::endl;

		// ��ֵ���������
		list<int> ls4 = ls1;
		for (auto e : ls3) std::cout << e << " ";
		std::cout << std::endl;
	}
}
