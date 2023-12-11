#include <iostream>
#include <vector>
#include "stl.h"

using namespace std;




void TestVectorExpand()
{
	size_t sz;
	vector<int> v;
	sz = v.capacity();
	cout << "making v grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

int main() {

	////stl::test1();
	//// ���� [] ��ʽ�������޸�
	//stl::test2();
	//// ����ģ�����������
	//stl::test3();

	//try
	//{
	//	stl::test8();
	//}
	//catch (const std::exception&)
	//{
	//	throw;
	//}

	//cout << "��ʽһ���±� + []" << endl;
	//vector<int> arr1(10, 1);
	//for (int i = 1; i < 10; i++) {
	//	arr1[i] = arr1[i-1] * 2 + 1;
	//	cout << arr1[i] << ' ';
	//}
	//cout << endl;

	//vector<int>::reverse_iterator iter = arr1.rbegin();
	//while (iter != arr1.rend()) {
	//	cout << *iter << " ";
	//	iter++;
	//}
	//cout << endl;

	TestVectorExpand();


	return 0;
}