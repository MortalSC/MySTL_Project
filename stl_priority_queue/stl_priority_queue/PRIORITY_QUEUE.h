#pragma warning (disable : 4996)


#include <vector>
#include <iostream>

using std::cout;
using std::endl;

namespace STL {

	// �Ż���֧�ִ���ѵ����ȼ����У�ʹ�÷º���ʵ�֣�����ģ���������ָ�������ͣ�
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

	// ���ȼ��߼���ע��Ĭ�ϴ���ѣ�less<T>����С���ѣ�greater<T>�� 
	template<class T, class Container = std::vector<T>, class Compare = less<T>>	
	class priority_queue {
	private:
		Container _container;

	public:
		void push(const T& data){
			_container.push_back(data);			// β�巨�������ݲ��뵽����β��������
			adjust_up(_container.size() - 1);	// �ѵ����ϵ����㷨���ҵ��ող�������ݣ�
		}
		void pop(){
			// �������ݵ�ɾ����ֻ���ڶѶ�ɾ����
			// �����ǻ�������ʵ�֣��ʣ�idx=0�����Ѷ���idx=size()-1����βԪ�أ�
			// ɾ�����ԣ�ͷβ������ɾ��β����ִ�жѵ��������µ����㷨��
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
		// ���ϵ����㷨��child parent ��Ϊ����
		void adjust_up(int child) {
			Compare _compare;
			int parent = (child - 1) / 2;
			// ���Ϊ��
			while (child > 0) {
				//if (_container[parent] < _container[child]) 
				if(_compare(_container[parent], _container[child]))
				// if (Compare()(_container[parent], _container[child]))	// ���������÷�
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
		// ���µ������Դ����Ϊ����
		void adjust_down(int parent) {
			Compare _compare;
			int child = parent * 2 + 1;			// �������
			while(child<_container.size()){
				//if (child + 1 < _container.size() && _container[child + 1] > _container[child]) 
				if(child + 1 < _container.size() && _compare(_container[child],_container[child + 1]))
				//if (child + 1 < _container.size() && Compare()(_container[child], _container[child + 1]))	// ���������÷�
				{
					++child;	// �ж��Ƿ�����Һ��ӣ�������Һ��ӵ�ֵ�������ӣ����ƶ���ǣ����ڽ�������
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



	// �������ܲ��ԣ�Ĭ��Ϊ����ѣ������롢ɾ������С���յȣ����ϵ��������µ����㷨��
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

	// ��������º����󣬿��Զ���ȽϷ�����ʾ��
	void test2() {
		std::cout << "Ĭ�ϣ�����ѣ�: " << std::endl;
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


		std::cout << "ָ����С���ѣ�: " << std::endl;
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


	// �Զ�����������
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

	// �����Զ������ͣ�������
	void TestPriorityQueue()
	{
		// ��ѣ���Ҫ�û����Զ����������ṩ<������
		priority_queue<Date> q1;
		q1.push(Date(2018, 10, 29));
		q1.push(Date(2018, 10, 28));
		q1.push(Date(2018, 10, 30));
		cout << q1.top() << endl;
		// ���Ҫ����С�ѣ���Ҫ�û��ṩ>������
		priority_queue<Date, std::vector<Date>, greater<Date>> q2;
		q2.push(Date(2018, 10, 29));
		q2.push(Date(2018, 10, 28));
		q2.push(Date(2018, 10, 30));
		cout << q2.top() << endl;
	}

}