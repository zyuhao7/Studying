#include<iostream>
#include<ctime>
#include "ThreadPool.h"
using namespace std;
/**
* 
*/

using ULL = unsigned long long;

class MyTask : public Task
{
public:
	MyTask(int begin, int end)
		:begin_(begin)
		,end_(end)
	{}

	// 如何设计 run 函数的返回值, 可以表示任意的类型？
	// c++ 17 any 
	Any run()
	{
		std::cout << "tid:" << std::this_thread::get_id() << " begin!" << std::endl;

		//std::this_thread::sleep_for(std::chrono::seconds(2));

		ULL  s = 0;
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
	// 线程池退出, 如何将线程资源回收?
	{
		ThreadPool pool;
		pool.setMode(PoolMode::MODE_CACHED);
		pool.start(4);

		clock_t begin = clock();
		Result res1 = pool.submitTask(std::make_shared<MyTask>(1,100000000));
		Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		Result res3 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));

		ULL  sum1 = res1.get().cast_<ULL>();
		ULL  sum2 = res2.get().cast_<ULL>();
		ULL  sum3 = res3.get().cast_<ULL>();
		clock_t end = clock();

		cout << sum1 + sum2 + sum3 << endl;

		cout << end - begin <<" ms " << endl;



		clock_t begin2 = clock();
		ULL  s = 0;
		for (int i = 1; i <= 300000000;++i) s += i;
		cout << s << endl;
		clock_t end2 = clock();
		cout << end2 - begin2 << " ms " << endl;
	}

	getchar();

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