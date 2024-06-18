// ThreadPool-NewCharacteristic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<thread>
#include<future>
#include<mutex>
#include <chrono>
#include "ThreadPool.h"
using namespace std;

/*
*	让线程池提交任务更加方便.
* 1.pool.submitTask(sum1, 10, 20);
*	pool.submitTask(sum2, 10, 20,30);
*			可变参模板编程.
* 
*  2. Result 类以及相关类型, 代码冗余.
*	 c++ 11 线程库 thread packaged_task(function函数对象) async.
*/

int sum1(int a, int b)
{
	this_thread::sleep_for(chrono::seconds(5));
	return  a + b;
}

int sum2(int a, int b, int c)
{
	this_thread::sleep_for(chrono::seconds(5));
	return  a + b + c;
}

int main()
{
	ThreadPool pool;
	pool.start(2);

	future<int>  r1 = pool.submitTask(sum1, 1, 2);
	future<int>  r2 = pool.submitTask(sum2, 1, 2,10);
	future<int>  r3 = pool.submitTask([](int begin, int end)-> int {
		int sum = 0;
		for (int i = begin;i <= end;++i) sum += i;
		return sum;
		}, 1, 100);

	future<int>  r4 = pool.submitTask([](int begin, int end)-> int {
		int sum = 0;
		for (int i = begin;i <= end;++i) sum += i;
		return sum;
		}, 1, 100);

	future<int>  r5 = pool.submitTask([](int begin, int end)-> int {
		int sum = 0;
		for (int i = begin;i <= end;++i) sum += i;
		return sum;
		}, 1, 100);

	cout << r1.get() << endl;
	cout << r2.get() << endl;
	cout << r3.get() << endl;
	cout << r4.get() << endl;
	cout << r5.get() << endl;

	getchar();

	//packaged_task<int(int, int)> task(sum1);

	//// future <=> Result
	//future<int> res = task.get_future(); 

	////task(10, 20); 
	//thread t(std::move(task), 10, 50);
	//t.detach();
	//cout << res.get() << endl;

	//thread t1(sum1, 10, 20);
	//thread t2(sum1, 10, 20);

	//t1.join();
	//t2.join();

	return  0;
}
