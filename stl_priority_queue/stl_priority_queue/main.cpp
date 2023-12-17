#include <iostream>

#include "PRIORITY_QUEUE.h"

int main() {
	try
	{
		//STL::test1();		// 基本功能测试（默认为大根堆）：插入、删除、大小、空等（向上调整、向下调整算法）
		//STL::test2();		// 测试引入仿函数后，可自定义比较方案的示例
		STL::TestPriorityQueue();	// 测试自定义类型：日期类
	}
	catch (const std::exception&)
	{

	}
	return 0;
}