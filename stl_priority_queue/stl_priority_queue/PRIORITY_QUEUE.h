#pragma warning (disable : 4996)


#include <vector>
#include <iostream>

using std::cout;
using std::endl;

namespace STL {

	// 优化仅支持大根堆的优先级队列（使用仿函数实现，第三模板参数调整指定堆类型）
	template<class T>
	struct less {
		bool operator () (const T& a, const T& b) {
			return a < b;
		}
	};
	
	template <class T>
	struct greater {
		bool operator () (const T& a, const T& b) {
			return a > b;
		}
	};

	// 优先级逻辑！注：默认大根堆（less<T>）；小根堆（greater<T>） 
	template<class T, class Container = std::vector<T>, class Compare = less<T>>	
	class priority_queue {
	private:
		Container _container;

	public:
		void push(const T& data){
			_container.push_back(data);			// 尾插法：新数据插入到数组尾部！！！
			adjust_up(_container.size() - 1);	// 堆的向上调整算法：找到刚刚插入的数据！
		}
		void pop(){
			// 堆中数据的删除：只能在堆顶删除！
			// 由于是基于数组实现！故：idx=0，即堆顶！idx=size()-1，即尾元素！
			// 删除策略：头尾交换，删除尾部，执行堆调整（向下调整算法）
			std::swap(_container[0], _container[_container.size() - 1]);
			_container.pop_back();
			adjust_down(0);
		}
		bool empty(){
			return _container.empty();
		}
		const T& top(){
			return _container[0];
		}
		size_t size(){
			return _container.size();
		}

	private:
		// 向上调整算法：child parent 均为索引
		void adjust_up(int child) {
			Compare _compare;
			int parent = (child - 1) / 2;
			// 大堆为例
			while (child > 0) {
				//if (_container[parent] < _container[child]) 
				if(_compare(_container[parent], _container[child]))
				// if (Compare()(_container[parent], _container[child]))	// 匿名对象用法
				{
					std::swap(_container[parent], _container[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else {
					break;
				}
			}
		}
		// 向下调整（以大根堆为例）
		void adjust_down(int parent) {
			Compare _compare;
			int child = parent * 2 + 1;			// 标记左孩子
			while(child<_container.size()){
				//if (child + 1 < _container.size() && _container[child + 1] > _container[child]) 
				if(child + 1 < _container.size() && _compare(_container[child],_container[child + 1]))
				//if (child + 1 < _container.size() && Compare()(_container[child], _container[child + 1]))	// 匿名对象用法
				{
					++child;	// 判断是否存在右孩子！且如果右孩子的值大于左孩子，就移动标记（用于交换）！
				}
				if (_compare(_container[parent],_container[child] )) {
					std::swap(_container[child], _container[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else break;
			}
		}
	};



	// 基本功能测试（默认为大根堆）：插入、删除、大小、空等（向上调整、向下调整算法）
	void test1() {
		priority_queue<int> pq;
		pq.push(1);
		pq.push(2);
		pq.push(3);
		pq.push(4);
		pq.push(5);
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		pq.push(100);
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		pq.push(-5);
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		std::cout << "data set : ";
		while (!pq.empty()) {
			std::cout << pq.top() << " ";
			pq.pop();
		}
		std::cout << std::endl;
	}

	// 测试引入仿函数后，可自定义比较方案的示例
	void test2() {
		std::cout << "默认（大根堆）: " << std::endl;
		priority_queue<int> pq1;
		pq1.push(1);
		pq1.push(2);
		pq1.push(3);
		pq1.push(4);
		pq1.push(5);
		std::cout << "size : " << pq1.size() << std::endl;
		std::cout << "top : " << pq1.top() << std::endl;

		pq1.push(100);
		std::cout << "insert : 100" << std::endl;
		std::cout << "size : " << pq1.size() << std::endl;
		std::cout << "top : " << pq1.top() << std::endl;

		std::cout << "insert : -5" << std::endl;
		pq1.push(-5);
		std::cout << "size : " << pq1.size() << std::endl;
		std::cout << "top : " << pq1.top() << std::endl;

		std::cout << "data set : ";
		while (!pq1.empty()) {
			std::cout << pq1.top() << " ";
			pq1.pop();
		}
		std::cout << std::endl;
		std::cout << std::endl;


		std::cout << "指定（小根堆）: " << std::endl;
		priority_queue<int,std::vector<int>, greater<int>> pq;
		pq.push(1);
		pq.push(2);
		pq.push(3);
		pq.push(4);
		pq.push(5);
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		pq.push(100);
		std::cout << "insert : 100" << std::endl;
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		pq.push(-5);
		std::cout << "insert : -5" << std::endl;
		std::cout << "size : " << pq.size() << std::endl;
		std::cout << "top : " << pq.top() << std::endl;

		std::cout << "data set : ";
		while (!pq.empty()) {
			std::cout << pq.top() << " ";
			pq.pop();
		}
		std::cout << std::endl;
	}


	// 自定义数据类型
	class Date
	{
	public:
		Date(int year = 1900, int month = 1, int day = 1)
			: _year(year)
			, _month(month)
			, _day(day)
		{}
		bool operator<(const Date& d)const
		{
			return (_year < d._year) ||
				(_year == d._year && _month < d._month) ||
				(_year == d._year && _month == d._month && _day < d._day);
		}
		bool operator>(const Date& d)const
		{
			return (_year > d._year) ||
				(_year == d._year && _month > d._month) ||
				(_year == d._year && _month == d._month && _day > d._day);
		}
		friend std::ostream& operator<<(std::ostream& _cout, const Date& d)
		{
			_cout << d._year << "-" << d._month << "-" << d._day;
			return _cout;
		}
	private:
		int _year;
		int _month;
		int _day;
	};

	// 测试自定义类型：日期类
	void TestPriorityQueue()
	{
		// 大堆，需要用户在自定义类型中提供<的重载
		priority_queue<Date> q1;
		q1.push(Date(2018, 10, 29));
		q1.push(Date(2018, 10, 28));
		q1.push(Date(2018, 10, 30));
		cout << q1.top() << endl;
		// 如果要创建小堆，需要用户提供>的重载
		priority_queue<Date, std::vector<Date>, greater<Date>> q2;
		q2.push(Date(2018, 10, 29));
		q2.push(Date(2018, 10, 28));
		q2.push(Date(2018, 10, 30));
		cout << q2.top() << endl;
	}

}