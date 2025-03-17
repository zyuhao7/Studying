#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <random>

using namespace std;
int main()
{
    std::mutex _mtx;
    std::queue<int> _que;
    int que_max = 1024;
    std::condition_variable _cv_consumer;
    std::condition_variable _cv_producer;
    bool _b_stop = false;

    auto consumer = std::thread([&]() {
        for (;;)
        {
            // 1. 先上锁
            std::unique_lock<std::mutex> lock(_mtx);

            // 2.判断队列是否有数据消费
            // 2.1 如果队列为空并且服务没关闭
            while (_que.empty() && !_b_stop)
            {
                _cv_consumer.wait(lock);
            }
            // 2.2 如果服务关闭则返回
            if (_b_stop)
                return;

            //2.3 如果队列有数据则消费
            auto t = _que.front();
            cout << "Consumer consume " << t << endl;
            _que.pop();

            
            // 3. 通知生产者线程
            bool b_notify = (_que.size() == que_max - 1) ? true : false;
            lock.unlock();
            if (b_notify)
            {
                _cv_producer.notify_one();
            }

            // 4. 睡眠一段时间

            std::random_device rd;
            std::mt19937 gen(rd());

            //  // 创建分布器，这里以生成范围在[0, 100]的整数为例
            std::uniform_int_distribution<>  dis(1, 3);

            int randomVal = dis(gen);
            std::this_thread::sleep_for(std::chrono::milliseconds(randomVal));

        }
        });

    auto producer = std::thread([&]() {
        for (int i = 0;;++i)
        {
            std::unique_lock<std::mutex> lock(_mtx);
            while (_que.size() == que_max && !_b_stop)
            {
                _cv_producer.wait(lock);
            }

            if (_b_stop)
                return ;

            _que.push(i);
            cout << "Producer produce " << i << endl;
            bool b_notify = (_que.size() == 1) ? true : false;
            lock.unlock();
            if (b_notify)
            {
                _cv_consumer.notify_one();
            }
            // 创建随机数引擎
            std::random_device rd;
            std::mt19937 gen(rd());

            // 创建分布器，这里以生成范围在[0, 100]的整数为例
            std::uniform_int_distribution<> dis(1, 3);

            // 生成随机数
            int randomValue = dis(gen);

            // 睡眠一毫秒
            std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));

        }
        });

    // 全局 io_context 对象
    boost::asio::io_context ioContext;
    // 创建一个信号集对象
    boost::asio::signal_set signals(ioContext, SIGINT);

    // 异步等待信号
    signals.async_wait([&](const boost::system::error_code& error,
        int signalNumber) {
            std::cout << "Received signal: " << signalNumber << std::endl;
            _b_stop = true;
            _cv_consumer.notify_one();
            _cv_producer.notify_one();
            // 停止 io_context
            ioContext.stop();
        });

    // 运行 io_context
    ioContext.run();
    //等待线程退出
    consumer.join();
    producer.join();

    std::cout << "Exiting..." << std::endl;

}

