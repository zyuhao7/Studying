#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <memory>
using namespace std;

// day-2025-3-10
class TestCopy
{
public:
    TestCopy() {}
    TestCopy(const TestCopy &tp)
    {
        std::cout << "TestCopy Copy" << endl;
    }
    TestCopy(TestCopy &&tp)
    {
        cout << "TestCopy Move" << endl;
    }
};

TestCopy TestCp()
{
    // return std::move(TestCopy());
    // TestCopy tp;
    // return tp;
    return TestCopy();
}
std::unique_ptr<int> ReturnUniquePtr()
{
    std::unique_ptr<int> uq_ptr = std::make_unique<int>(100);
    return uq_ptr;
}

std::thread ReturnThread()
{
    std::thread t([]()
                  {
		int i = 0;
		while (true) {
			std::cout << "i is " << i << std::endl;
			i++;
			if (i == 5) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		} });

    return t;
}

void ChangeValue()
{
    int m = 100;
    std::thread t1{[](int &rm)
                   {
                       rm++;
                   },
                   std::ref(m)};

    t1.join();
}

void ThreadOp()
{

    std::thread t1([]()
                   {
		int i = 0;
		while (i < 5) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			i++;
			} });

    std::thread t2([]()
                   {
		int i = 0;
		while (i < 10) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			i++;
		} });

    // 不能将一个线程归属权绑定给一个已经绑定线程的变量，否则会触发terminate导致崩溃
    t1 = std::move(t2);
    t1.join();
    t2.join();
}

int asyncFunc()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "this is asyncFunc" << std::endl;
    return 0;
}

void func1(std::future<int> &future_ref)
{
    std::cout << "this is func1" << std::endl;
    future_ref = std::async(std::launch::async, asyncFunc);
}

void func2(std::future<int> &future_ref)
{
    std::cout << "this is func2" << std::endl;
    auto future_res = future_ref.get();
    if (future_res == 0)
    {
        std::cout << "get asyncFunc result success !" << std::endl;
    }
    else
    {
        std::cout << "get asyncFunc result failed !" << std::endl;
        return;
    }
}

void first_method()
{
    std::future<int> future_tmp;
    func1(future_tmp);
    func2(future_tmp);
}

int main()
{
    // TestCp();
    // auto rt_ptr = ReturnUniquePtr();
    // std::cout << "rt_ptr value is " << *rt_ptr << std::endl;

    // std::thread rt_thread = ReturnThread();
    // rt_thread.join();

    // ThreadOp();
    // BlockAsync();

    // ChangeValue();
    // DeadLock();
    // first_method();
    // TestParallen1();
    // std::this_thread::sleep_for(std::chrono::seconds(4));
    // TestParallen2();
    std::cout << "Main Exited!\n";
    return 0;
}