#pragma warning( disable : 4996 )
#pragma once 
#include <iostream>
#include <vector>
#include <list>
#include <deque>
namespace STL {

	// 适配器模式 / 配接器
	template<class T, class Container = std::deque<T>>
	class stack {
	private:
		Container _container;
	public:
		void push(const T& data) { _container.push_back(data); }
		void pop() { _container.pop_back(); }
		const T& top() { return _container.back(); }
		bool empty() { return _container.empty(); }
		size_t size() { return _container.size(); }
	};

	// 测试简单设计的栈
	void test1() {
		stack<int, std::vector<int>> stk;
		stk.push(1);
		stk.push(2);
		stk.push(3);
		stk.push(4);
		while (!stk.empty()) {
			std::cout << stk.top() << " ";
			stk.pop();
		}
	}
}