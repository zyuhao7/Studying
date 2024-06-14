#include<iostream>
#include "ThreadPool.h"

/**
* 
*/


class MyTask : public Task
{
public:
	//MyTask(int begin, int end)
	//	:begin_(begin)
	//	,end_(end)
	//{}

	// 如何设计 run 函数的返回值, 可以表示任意的类型？
	// c++ 17 any 
	Any run()
	{
		std::cout << "tid:" << std::this_thread::get_id() << " begin!" << std::endl;

		//std::this_thread::sleep_for(std::chrono::seconds(2));

		int s = 0;
		for (int i = begin_; i <= end_;++i) s += i;

		std::cout << "tid:" << std::this_thread::get_id() << " end!" << std::endl;
		return s;
	}

private:
	int begin_;
	int end_;
};

int main()
{
	ThreadPool pool;
	pool.start(4);

	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());

	//std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}