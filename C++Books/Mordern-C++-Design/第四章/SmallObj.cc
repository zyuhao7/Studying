#include <iostream>
#include <assert.h>
using namespace std;

// day-2025-10-15
// 第三章 小型对象分配技术

class Chunk
{
public:
    void Init(std::size_t blockSize, unsigned char blocks);
    void Release();
    void *Allocate(std::size_t blockSize);
    void Deallocate(void *p, std::size_t blockSize);
    unsigned char *pData_;
    unsigned char firstAvailableBlock_, // chunk 内第一个可用区块的索引号
        blockAvailable_;                // chunk 内可用区块总数
};

void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    pData_ = new unsigned char[blockSize * blocks];
    firstAvailableBlock_ = 0;
    blockAvailable_ = blocks;
    unsigned char *p = pData_;
    for (unsigned char i = 0; i != blocks; ++i, p += blockSize)
    {
        *p = i + 1;
    }
}

void *Chunk::Allocate(std::size_t blockSize)
{
    if (!blockAvailable_)
        return nullptr;
    unsigned char *pResult = pData_ + firstAvailableBlock_ * blockSize;
    firstAvailableBlock_ = *pResult;
    --blockAvailable_;
    return pResult;
}

void Chunk::Deallocate(void *p, std::size_t blockSize)
{
    assert(p >= pData_);
    unsigned char *toRelease = static_cast<unsigned char *>(p);
    *toRelease = firstAvailableBlock_;
    firstAvailableBlock_ = static_cast<unsigned char>(toRelease - pData_) / blockSize;
    assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
    ++blockAvailable_;
}
#include <vector>

// 大小一致的分配器
class FixedAllocator
{
private:
    std::size_t blockSize_;
    unsigned char numBlocks_;
    typedef vector<Chunk> Chunks;
    Chunks chunks_;

    Chunk *allocChunk_;
    Chunk *deallocChunk_;

    void *Allocate();
};

void *FixedAllocator::Allocate()
{
    if (allocChunk_ == 0 || allocChunk_->blockAvailable_ == 0)
    {
        Chunks::iterator it = chunks_.begin();
        for (;; ++it)
        {
            if (it == chunks_.end())
            {
                chunks_.push_back(Chunk());
                Chunk &newChunk = chunks_.back();
                newChunk.Init(blockSize_, numBlocks_);
                allocChunk_ = &newChunk;
                deallocChunk_ = &newChunk;
                break;
            }
            if (it->blockAvailable_ > 0)
            {
                allocChunk_ = &(*it);
                break;
            }
        }
    }
    assert(allocChunk_ != 0);
    assert(allocChunk_->blockAvailable_ > 0);
    return allocChunk_->Allocate(blockSize_);
}

class SmallObjectAllocator
{
public:
    SmallObjectAllocator(std::size_t chunkSize, std::size_t maxObjSize);
    void *Allocate(std::size_t numBytes);
    void Deallocate(void *p, std::size_t size);

private:
    vector<FixedAllocator> pool_;
    FixedAllocator *pLastAlloc_;
    FixedAllocator *pLastDealloc_;
};

class SmallObject
{
public:
    static void *operator new(std::size_t size);
    static void operator delete(void *p, size_t size);
    virtual ~SmallObject() {}
};

class Base
{
    int a_[100];

public:
    virtual ~Base()
    {
        std::cout << "~Base()" << endl;
    }
};

class Derived : public Base
{
    int b_[200];

public:
    virtual ~Derived()
    {
        std::cout << "~Derived()" << endl;
    }
};

int main()
{
    Base *p = new Derived;
    delete p;
}