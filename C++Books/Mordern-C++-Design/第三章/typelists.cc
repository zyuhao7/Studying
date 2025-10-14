#include <iostream>
using namespace std;
// day-2025-10-13
// 第三章-TypeLists
class Window;
class Button;
class ScrollBar;
class WidgetFactory
{
public:
    virtual Window *CreateWindow() = 0;
    virtual Button *CreateButton() = 0;
    virtual ScrollBar *CreateScrollBar() = 0;
};

// template <class T>
// T *MakeRedWidget(WidgetFactory *factory)
// {
//     T *pW = factory.CreateT();
//     pW->SetColor(RED);
//     return pW;
// }

template <class T>
T *MakeRedWidget(WidgetFactory *factory)
{
    T *pW = factory.Create<T>();
    pW->SetColor(RED);
    return pW;
}

namespace TL
{
    class NullType;
    template <class T, class U>
    struct Typelist
    {
        typedef T Head;
        typedef U Tail;
    };

    template <class TList>
    struct Length;

    template <>
    struct Length<NullType>
    {
        enum
        {
            value = 0
        };
    };

    template <class T, class U>
    struct Length<Typelist<T, U>>
    {
        enum
        {
            value = 1 + Length<U>::value
        };
    };

    template <class Typelist, int i>
    struct TypeAt;

    template <class Head, class Tail>
    struct TypeAt<Typelist<Head, Tail>, 0>
    {
        typedef Head Result;
    };

    template <class Head, class Tail, int i>
    struct TypeAt<Typelist<Head, Tail>, i>
    {
        typedef typename TypeAt<Tail, i - 1>::Result Result;
    };

    template <class TList, class T>
    struct IndexOf;

    template <class T>
    struct IndexOf<NullType, T>
    {
        enum
        {
            value = -1
        };
    };

    template <class Tail, class T>
    struct IndexOf<Typelist<T, Tail>, T>
    {
        enum
        {
            value = 0
        };
    };

    template <class Head, class Tail, class T>
    struct IndexOf<Typelist<Head, Tail>, T>
    {
    private:
        enum
        {
            temp = IndexOf<Tail, T>::value
        };

    public:
        enum
        {
            value = tmp == -1 ? -1 : 1 + temp
        };
    };

    template <class TList, class T>
    struct Append;

    template <>
    struct Append<NullType, NullType>
    {
        typedef NullType Result;
    };

    template <class T>
    struct Append<NullType, T>
    {
        typedef TYPELIST_1(T) Result;
    };

    template <class Head, class Tail>
    struct Append<NullType, Typelist<Head, Tail>>
    {
        typedef Typelist<Head, Tail> Result;
    };

    template <class Head, class Tail, class T>
    struct Append<Typelist<Head, Tail>, T>
    {
        typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
    };

    template <class TList, class T>
    struct MostDerived;

    template <class T>
    struct MostDerived<NullType, T>
    {
        typedef T Result;
    };
    template <class Head, class Tail, class T>
    struct MostDerived<Typelist<Head, Tail>, T>
    {
    private:
        typedef typename MostDerived<Tail, T>::result Candidate;

    public:
        typedef typename Select<SUPERSUBCLASS(Candidate, Head), Head, Candidate>::Result Result;
    };

    template <class T>
    struct DerivedToFront;

    template <>
    struct DerivedToFront<NullType>
    {
        typedef NullType Result;
    };

    template <class Head, class Tail>
    struct DerivedToFront<Typelist<Head, Tail>>
    {
    private:
        typedef typename MostDerived<Tail, Head>::Result TheMostDerived;
        typedef typename Replace<Tail, TheMostDerived, Head>::Result L;

    public:
        typedef Typelist<TheMostDerived, L> Result;
    };
}
