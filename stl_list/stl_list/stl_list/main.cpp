#include <iostream>
#include "STL_LIST.h"
using namespace std;

int main() {

	try
	{
		//STL::test1();		// 测试简单构造和尾插法
		//STL::test2();		// 测试迭代器的封装，以及遍历
		//STL::test3();		// 测试 const 迭代器
		//STL::test4();		// 测试自定义类型与迭代器
		//STL::test5();		// 测试指定位置插入
		//STL::test6();		// 测试指定位置删除、头删、尾插、头插、尾插
		//STL::test7();		// 测试 clear 清除链表结点
		//STL::test8();		// 测试 迭代器构造 和 拷贝构造
		STL::test9();		// 测试反向迭代器的设计
	}
	catch (const std::exception&)
	{

	}
	return 0;
}