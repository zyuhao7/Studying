#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <iostream>
#include <queue>
#include <vector>
#include <semaphore.h>

using namespace std;
// day-2024-9-4
// BIT 8 _LINUX 多线程


// POSIX 信号量
// 环形队列
// #define NUM 16
// class RingQueue
// {
// private:
//     vector<int> q;
//     int capacity;
//     sem_t data_sem;
//     sem_t space_sem;
//     int consume_step;
//     int product_step;

// public:
//     RingQueue(int _cap = NUM)
//         : q(_cap), capacity(_cap)
//     {
//         sem_init(&data_sem, 0, 0);
//         sem_init(&space_sem, 0, capacity);
//         consume_step = 0;
//         product_step = 0;
//     }

//     void PutData(const int &data)
//     {
//         sem_wait(&space_sem); // P -1
//         q[product_step] = data;
//         product_step++;
//         product_step %= capacity;
//         sem_post(&data_sem); // V +1
//     }

//     void GetData(int &data)
//     {
//         sem_wait(&data_sem);
//         data = q[consume_step];
//         consume_step++;
//         consume_step %= capacity;
//         sem_post(&space_sem);
//     }
//     ~RingQueue()
//     {
//         sem_destroy(&data_sem);
//         sem_destroy(&space_sem);
//     }
// };

// void *consumer(void *arg)
// {
//     RingQueue *rqp = (RingQueue *)arg;
//     int data;
//     for (;;)
//     {
//         rqp->GetData(data);
//         cout << "Consume data done : " << data << endl;
//         sleep(1);
//     }
// }

// void *producter(void *arg)
// {
//     RingQueue *rqp = (RingQueue *)arg;
//     srand(time(0));

//     for (;;)
//     {
//         int data = rand() % 1024;
//         rqp->PutData(data);
//         cout << "Product data done : " << data << endl;
//         sleep(1);
//     }
// }

// int main()
// {
//     RingQueue rq;
//     pthread_t c, p;
//     pthread_create(&c, NULL, consumer, (void *)&rq);
//     pthread_create(&p, NULL, producter, (void *)&rq);

//     pthread_join(c, NULL);
//     pthread_join(p, NULL);

//     return 0;
// }

// 生产者-消费者模型
// BlockingQueue(阻塞队列)
// C++ queue模拟阻塞队列的生产消费模型
// #define NUM 8
// class BlockQueue
// {
// private:
//     std::queue<int> q;
//     int capacity;
//     pthread_mutex_t lock;
//     pthread_cond_t full;
//     pthread_cond_t empty;

// private:
//     void LockQueue()
//     {
//         pthread_mutex_lock(&lock);
//     }

//     void UnLockQueue()
//     {
//         pthread_mutex_unlock(&lock);
//     }

//     void ProductWait()
//     {
//         pthread_cond_wait(&full, &lock);
//     }

//     void ConsumeWait()
//     {
//         pthread_cond_wait(&empty, &lock);
//     }

//     void NotifyProduct()
//     {
//         pthread_cond_signal(&full);
//     }

//     void NotifyConsume()
//     {
//         pthread_cond_signal(&empty);
//     }

//     bool IsEmpty()
//     {
//         return q.size() == 0 ? true : false;
//     }

//     bool IsFull()
//     {
//         return q.size() == capacity ? true : false;
//     }

// public:
//     BlockQueue(int _cap = NUM)
//         : capacity(_cap)
//     {
//         pthread_mutex_init(&lock, NULL);
//         pthread_cond_init(&full, NULL);
//         pthread_cond_init(&empty, NULL);
//     }

//     void PushData(const int &data)
//     {
//         LockQueue();
//         while (IsFull())
//         {
//             NotifyConsume();
//             cout << "Queue Full, Notify consume data, product stop.. !" << endl;
//             ProductWait();
//         }
//         q.push(data);
//         NotifyConsume();
//         UnLockQueue();
//     }

//     void PopData(int &data)
//     {
//         LockQueue();
//         while (IsEmpty())
//         {
//             NotifyProduct();
//             cout << "Queue Empty, Notify product data, consume stop..! " << endl;
//             ConsumeWait();
//         }
//         data = q.front();
//         q.pop();
//         NotifyProduct();
//         UnLockQueue();
//     }
//     ~BlockQueue()
//     {
//         pthread_mutex_destroy(&lock);
//         pthread_cond_destroy(&full);
//         pthread_cond_destroy(&empty);
//     }
// };

// void *consumer(void *arg)
// {
//     BlockQueue *bpq = (BlockQueue *)arg;
//     int data;
//     for (;;)
//     {
//         sleep(1);
//         bpq->PopData(data);
//         cout << "Consume data done : " << data << endl;
//     }
// }

// void *producter(void *arg)
// {
//     BlockQueue *bpq = (BlockQueue *)arg;
//     srand(unsigned(time(0)));
//     for (;;)
//     {
//         int data = rand() % 1024;
//         bpq->PushData(data);
//         cout << "Product data done : " << data << endl;
//     }
// }

// int main()
// {
//     BlockQueue bq;
//     pthread_t c, p;
//     pthread_create(&c, NULL, consumer, (void *)&bq);
//     pthread_create(&p, NULL, producter, (void *)&bq);

//     pthread_join(c, NULL);
//     pthread_join(p, NULL);
// }

// 条件变量
// pthread_cond_t cond;
// pthread_mutex_t mutex;

// void *r1(void *arg)
// {
//     while (1)
//     {
//         pthread_cond_wait(&cond, &mutex);
//         printf("活动\n");
//     }
// }

// void *r2(void *arg)
// {
//     while (1)
//     {
//         pthread_cond_signal(&cond);
//         sleep(1);
//     }
// }

// int main(void)
// {
//     pthread_t t1, t2;

//     pthread_cond_init(&cond, NULL);
//     pthread_mutex_init(&mutex, NULL);

//     pthread_create(&t1, NULL, r1, NULL);
//     pthread_create(&t2, NULL, r2, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     pthread_mutex_destroy(&mutex);
//     pthread_cond_destroy(&cond);
// }

// 改进下面的售票系统 正常卖票了!
// int ticket = 100;
// pthread_mutex_t mutex;

// void *route(void *arg)
// {
//     char *id = (char *)arg;
//     while (1)
//     {
//         pthread_mutex_lock(&mutex);
//         if (ticket > 0)
//         {
//             usleep(1000);
//             printf("%s sells ticket:%d\n", id, ticket);
//             ticket--;
//             pthread_mutex_unlock(&mutex);
//             // sched_yield(); 放弃CPU
//         }
//         else
//         {
//             pthread_mutex_unlock(&mutex);
//             break;
//         }
//     }
// }

// int main(void)
// {
//     pthread_t t1, t2, t3, t4;

//     pthread_mutex_init(&mutex, NULL);

//     pthread_create(&t1, NULL, route, (void *)"thread 1");
//     pthread_create(&t2, NULL, route, (void *)"thread 2");
//     pthread_create(&t3, NULL, route, (void *)"thread 3");
//     pthread_create(&t4, NULL, route, (void *)"thread 4");

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     pthread_join(t3, NULL);
//     pthread_join(t4, NULL);
//     pthread_mutex_destroy(&mutex);
// }

// 操作共享变量会有问题的售票系统代码
// int ticket = 100;
// void *route(void *arg)
// {
//     char *id = (char *)arg;
//     while (1)
//     {
//         if (ticket > 0)
//         {
//             usleep(1000);
//             printf("%s sells ticket: %d\n", id, ticket);
//             ticket--;
//         }
//         else
//             break;
//     }
// }

// int main()
// {
//     pthread_t t1, t2, t3, t4;
//     pthread_create(&t1, NULL, route, (void *)"thread 1");
//     pthread_create(&t2, NULL, route, (void *)"thread 2");
//     pthread_create(&t3, NULL, route, (void *)"thread 3");
//     pthread_create(&t4, NULL, route, (void *)"thread 4");

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     pthread_join(t3, NULL);
//     pthread_join(t4, NULL);

//     // ....
//     // thread 1 sells ticket: 1
//     // thread 3 sells ticket: 0
//     // thread 4 sells ticket: -1
//     // thread 2 sells ticket: -2
// }

// void *thread_run(void *arg)
// {
//     pthread_detach(pthread_self());
//     printf("%s \n", (char *)arg);
//     return NULL;
// }

// int main()
// {
//     pthread_t tid;
//     if (pthread_create(&tid, NULL, thread_run, NULL) != 0)
//     {
//         printf("Create thread error !\n");
//         return 1;
//     }

//     int ret = 0;
//     sleep(1); // import 先让线程分离, 再等待.

//     if (pthread_join(tid, NULL) == 0)
//     {
//         printf("pthread wait success! \n");
//         ret = 0;
//     }
//     else
//     {
//         printf("pthread wait failed\n");
//         ret = 1;
//     }
//     return ret;
// }

/*
// 线程不同退出方式
void *thread1(void *arg)
{
    printf("Thread 1 returning ... \n");
    int *p = (int *)malloc(sizeof(int));
    *p = 1;
    return (void *)p;
}

void *thread2(void *arg)
{
    printf("Thread 2 exiting... \n");
    int *p = (int *)malloc(sizeof(int));
    *p = 2;
    return (void *)p;
}

void *thread3(void *arg)
{
    while (1)
    {
        printf("Thread 3 is Runnning.. \n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    void *ret;

    // thread 1 return
    pthread_create(&tid, NULL, thread1, NULL);
    pthread_join(tid, &ret);
    printf("thread return, thread id : %x, return code: %d \n", tid, *(int *)ret);
    free(ret);

    // thread 2 exit
    pthread_create(&tid, NULL, thread2, NULL);
    pthread_join(tid, &ret);
    printf("thread return, thread id : %x, return code: %d \n", tid, *(int *)ret);
    free(ret);

    // thread 3 cancel by other
    pthread_create(&tid, NULL, thread3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &ret);
    if (ret == PTHREAD_CANCELED)
        printf("thread return, thread id : %x, return code : PTHREAD_CANCELED \n", tid);
    else
        printf("thread return, thread id : %x, return code : NULL\n", tid);
}

*/

// void *rout(void *arg)
// {
//     int i;
//     for (;;)
//     {
//         printf("I am Thread 1! \n");
//         sleep(1);
//     }
// }

// int main()
// {
//     pthread_t tid;
//     int ret;
//     if ((ret = pthread_create(&tid, NULL, rout, NULL)) != 0)
//     {
//         fprintf(stderr, "pthread_create: %s \n", strerror(ret));
//         exit(EXIT_FAILURE);
//     }

//     int i;
//     for (;;)
//     {
//         printf("I am main thread! \n");
//         sleep(1);
//     }
// }