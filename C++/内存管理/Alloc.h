#include <stdlib.h> //for malloc(),realloc()
#include <stddef.h> //for size_t
#include <memory.h> //for memcpy()

// #define __THROW_BAD_ALLOC   cerr << "out of memory" << endl; exit(1)
#define __THROW_BAD_ALLOC exit(1)

//----------------------------------------------
// 第1級配置器。
//----------------------------------------------

void (*oom_handler)() = 0; // 初始化函数指针为空.
void *oom_malloc(size_t n)
{
    void (*my_malloc_handler)();
    void *result;
    for (;;) // 不断尝试释放、配置、在释放、再配置
    {
        my_malloc_handler = oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)(); // 呼叫处理常式, 企图释放内存.
        result = malloc(n);     // 再次尝试配置内存.
        if (result)
            return result;
    }
}

void *oom_realloc(void *p, size_t n)
{
    void (*my_malloc_handler)();
    void *result;
    for (;;)
    {
        my_malloc_handler = oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        result = realloc(p, n);
        if (result)
            return result;
    }
}

void *malloc_allocate(size_t n)
{
    void *result = malloc(n);
    if (0 == result)
        result = oom_malloc(n);
    return result;
}

void malloc_deallocate(void *p, size_t n)
{
    free(p);
}

void *malloc_reallocate(void *p, size_t old_sz, size_t new_sz)
{
    void *result = realloc(p, new_sz);
    if (0 == result)
        result = oom_realloc(p, new_sz);
    return result;
}

void (*set_malloc_handler(void (*f)()))()
{
    void (*old)() = oom_handler;
    oom_handler = f;
    return old;
}