#pragma once 

namespace STL {


	// 反向迭代器			// 标记返回值	// 标记返回指针
	template<class Iterator, class Ref, class Ptr>	// 使用两个模板参数，替代官方的 “萃取” 实现方式
	struct ReverseIterator {
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;		// 别名简化类型
		Iterator _current;										// 标记一个当前点（基于复用正向迭代器逻辑）
		// _current ：就是逆向开始的起点！
		// 它的下一个位置，在链表中是：_current => node->_prev

		ReverseIterator(Iterator iter)
			:_current(iter)
		{}

		// 重载解引用！
		// 正向迭代器：begin() => _head->_next;	/ end() => _head;
		// 反向迭代器：rbegin() => _head; / rend() => _head->_next;
		// 两者刚好对称（相反指向）
		Ref operator * () {
			Iterator temp = _current;		// 临时标记当前点
			--temp;							// 实现反向移动
			return *(temp);
		}

		Ptr operator -> () {
			return &(operator*());
		}

		// 重载 前置++
		// 区别于正向迭代器：反向迭代器 ++ 就是 （正向）-- ，依托于双向链表，可以轻易实现向前移动
		Self& operator ++ () {
			--_current;						// 复用正向迭代器的 --，实现指向前移（基于正向逻辑）！！！
			return *this;					// 返回指向对象
		}
		// 重载后置 ++
		Self operator ++ (int) {
			Self temp(*this);
			--_current;
			return temp;
		}

		// 重载后置 --
		// 区别于正向迭代器：反向迭代器 -- 就是 （正向）++ ，依托于双向链表，可以轻易实现向前移动
		Self& operator -- () {
			++_current;						// 复用正向迭代器的 ++，实现指向后移（基于正向逻辑）！！！
			return *this;
		}
		// 重载后置 --
		Self operator -- (int) {
			Self temp(*this);
			++_current;
			return temp;
		}

		bool operator != (const Self& iter) {
			return _current != iter._current;
		}
	};
}