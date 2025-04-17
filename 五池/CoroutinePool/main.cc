#include "coroutine_pool.h"
#include <unistd.h>
#include <iostream>

int main()
{
    CoroutinePool pool(4, 10);

    pool.setHighWatermarkCallback([](size_t size)
                                  { printf(" 高水位警告，当前任务数量: %zu\n", size); });

    // 模拟添加任务
    for (int i = 0; i < 20; ++i)
    {
        pool.addTask([i]
                     {
                         printf("执行任务 %d\n", i);
                         usleep(100000); // 模拟耗时任务
                     });
    }
    pool.start();

    sleep(2); // 等协程运行一会儿
    return 0;
}