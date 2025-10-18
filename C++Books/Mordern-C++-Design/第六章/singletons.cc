#include <iostream>
using namespace std;

// day-2025-10-17
//  第七章 Singletons 实作技术

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if (!pInstance_)
            pInstance_ = new Singleton;
        return pInstance_;
    }

private:
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    ~Singleton();
    static Singleton *pInstance_;
};

Singleton *Singleton::pInstance_ = nullptr;

#include <cstdlib>
void bar()
{
    cout << "void bar()" << endl;
}

void foo()
{
    std::atexit(bar);
}

namespace Private
{
    class LifetimeTracker
    {
    public:
        LifetimeTracker(unsigned int x)
            : longevity_(x)
        {
        }
        virtual ~LifetimeTracker() = 0;
        friend inline bool Compare(unsigned int longevity, const LifetimeTracker *p)
        {
            return p->longevity_ < longevity;
        }

    private:
        unsigned int longevity_;
    };

    inline LifetimeTracker::~LifetimeTracker() {}

    namespace
    {
        template <typename T, typename Destroyer>
        class ConcreteLifetimeTracker : public LifetimeTracker
        {
        public:
            ConcreteLifetimeTracker(T *pDynObject, unsigned int longevity, Destroyer destroyer)
                : LifetimeTracker(longevity), pTracked_(pDynObject), destroyer_(destroyer)
            {
            }

        private:
            T *pTracked_;
            Destroyer destroyer_;
        };
        void AtExitFn();
    }

    template <typename T, typename Destroyer>
    void SetLongevity(T *pDynObject, unsigned int longevity, Destroyer d = Private::Deleter<T>::Delete)
    {
        // .....
    }

}

template <typename T>
void Delete(T *pObj)
{
    delete pObj;
}

int main()
{

    std::atexit(foo); // void bar()
    return 0;
}