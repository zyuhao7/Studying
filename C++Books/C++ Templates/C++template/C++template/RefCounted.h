#pragma once
#include <iostream>
// 侵入式基类（引用计数内置）
class RefCounted {
private:
    size_t ref_count = 0;

public:
    void add_ref() { ++ref_count; }
    void release() { if (--ref_count == 0) delete this; }
protected:
    virtual ~RefCounted() = default;
};

// 对象必须继承 RefCounted
class MyObject : public RefCounted {
public:
    MyObject(int v) : value(v) {}
    void print() const { std::cout << value << "\n"; }
private:
    int value;
};

// 智能指针（直接操作对象内部的计数）
template <typename T>
class IntrusivePtr {
    T* ptr;
public:
    IntrusivePtr(T* p) : ptr(p) { if (ptr) ptr->add_ref(); }
    ~IntrusivePtr() { if (ptr) ptr->release(); }
    // 拷贝/移动构造、赋值运算符等...
};


// 非侵入式引用计数
// 计数块（外部存储引用计数）
struct RefCountBlock {
    size_t count = 1;
    void add_ref() { ++count; }
    void release() { if (--count == 0) delete this; }
};

// 智能指针（外部管理计数）
template <typename T>
class NonIntrusivePtr {
    T* ptr;
    RefCountBlock* block;
public:
    NonIntrusivePtr(T* p) : ptr(p), block(new RefCountBlock) {}
    ~NonIntrusivePtr() {
        if (block->release()) {
            delete ptr;  // 先释放对象
            delete block; // 再释放计数块
        }
    }
    // 拷贝/移动构造、赋值运算符等...
};

// 对象无需继承任何基类
class MyObject {
public:
    MyObject(int v) : value(v) {}
    void print() const { std::cout << value << "\n"; }
private:
    int value;
};