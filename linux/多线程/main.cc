#include "threadpool.h"
#include <iostream>
#include <time.h>

using namespace std;

bool handler(int data)
{
    srand(time(0));
    int n = rand() % 5;
    printf("Thread: %p Run Task: %d -- sleep %d sec \n", pthread_self(), data, n);
    sleep(n);
    return true;
}
int main()
{
    int i;
    ThreadPool pool;
    pool.PoolInit();
    for (int i = 0; i < 10; ++i)
    {
        ThreadTask *tt = new ThreadTask(i, handler);
        pool.PushTask(tt);
    }
    pool.PoolQuit();
    return 0;
}
