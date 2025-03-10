#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

// day-2025-3-10
// C++是万能的，我们可以用C++实现一个类似于go的channel，采用csp模式解耦合，实现类似的生产者和消费者问题
template <typename T>
class Channel
{
private:
    std::queue<T> queue_;
    std::mutex mtx_;
    std::condition_variable cv_producer_;
    std::condition_variable cv_consumer_;
    size_t capacity_;
    bool close_ = false;

public:
    Channel(size_t capacity = 0)
        : capacity_(capacity)
    {
    }

    bool send(T val)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        //   // 对于无缓冲的channel，我们应该等待直到有消费者准备好
        cv_producer_.wait(lock, [this]()
                          { return (capacity_ == 0 && queue_.empty()) || close_ || queue_.size() < capacity_; });
        if (close_)
            return false;

        queue_.emplace(val);
        cv_consumer_.notify_one();
        return true;
    }

    bool receive(T &val)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_consumer_.wait(lock, [this]()
                          { return !queue_.empty() || close_; });
        // 如果 channel 关闭, 队列为空, 返回 false.
        if (close_ && queue_.empty())
            return false;

        val = queue_.front();
        queue_.pop();
        cv_producer_.notify_one();
        return true;
    }

    void close()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        close_ = true;
        cv_producer_.notify_all();
        cv_consumer_.notify_all();
    }
};
// 示例使用
int main()
{
    Channel<int> ch(10);

    std::thread producer([&]()
                         {
		for (int i = 0; i < 50; ++i) {
			ch.send(i);
			std::cout << "Sent: " << i << std::endl;
		}
		ch.close(); });

    std::thread consumer([&]()
                         {
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 故意延迟消费者开始消费
		int val;
		while (ch.receive(val)) {
			std::cout << "Received: " << val << std::endl;
		} });

    producer.join();
    consumer.join();
    return 0;
}