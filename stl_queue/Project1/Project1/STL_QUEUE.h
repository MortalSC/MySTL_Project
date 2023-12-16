#pragma warning(disable : 4996)
#pragma once

#include <deque>
namespace STL {
	template<class T, class Container = std::deque<T>>
	class queue {
	private:
		Container _container;
	public:
		void push(const T& data) { _container.push_front(data); }
		void pop() { _container.pop_back(); }
		bool empty() { return _container.empty(); }
		T& front() { return _container.back(); }
		T& back() { return _container.front(); }
		const T& front()const { return _container.back(); }
		const T& back() const{ return _container.front(); }
		size_t size() { return _container.size(); }
	};

	void test1() {
		queue<int> qu;
		qu.push(1);
		qu.push(2);
		qu.push(3);
		qu.push(4);
		std::cout << qu.size() << std::endl;
		std::cout << qu.front() << std::endl;
		std::cout << qu.back() << std::endl;
		std::cout << qu.front() << std::endl;
		std::cout << qu.back() << std::endl;
		std::cout << qu.size() << std::endl;
		qu.pop();
		std::cout << qu.front() << std::endl;
		std::cout << qu.back() << std::endl;
		std::cout << qu.size() << std::endl;
	}
}