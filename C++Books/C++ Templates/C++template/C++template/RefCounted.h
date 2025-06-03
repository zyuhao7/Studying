#pragma once
#include <iostream>
// ����ʽ���ࣨ���ü������ã�
class RefCounted {
private:
    size_t ref_count = 0;

public:
    void add_ref() { ++ref_count; }
    void release() { if (--ref_count == 0) delete this; }
protected:
    virtual ~RefCounted() = default;
};

// �������̳� RefCounted
class MyObject : public RefCounted {
public:
    MyObject(int v) : value(v) {}
    void print() const { std::cout << value << "\n"; }
private:
    int value;
};

// ����ָ�루ֱ�Ӳ��������ڲ��ļ�����
template <typename T>
class IntrusivePtr {
    T* ptr;
public:
    IntrusivePtr(T* p) : ptr(p) { if (ptr) ptr->add_ref(); }
    ~IntrusivePtr() { if (ptr) ptr->release(); }
    // ����/�ƶ����졢��ֵ�������...
};


// ������ʽ���ü���
// �����飨�ⲿ�洢���ü�����
struct RefCountBlock {
    size_t count = 1;
    void add_ref() { ++count; }
    void release() { if (--count == 0) delete this; }
};

// ����ָ�루�ⲿ���������
template <typename T>
class NonIntrusivePtr {
    T* ptr;
    RefCountBlock* block;
public:
    NonIntrusivePtr(T* p) : ptr(p), block(new RefCountBlock) {}
    ~NonIntrusivePtr() {
        if (block->release()) {
            delete ptr;  // ���ͷŶ���
            delete block; // ���ͷż�����
        }
    }
    // ����/�ƶ����졢��ֵ�������...
};

// ��������̳��κλ���
class MyObject {
public:
    MyObject(int v) : value(v) {}
    void print() const { std::cout << value << "\n"; }
private:
    int value;
};