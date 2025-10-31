#include <iostream>
#include <map>
using namespace std;

// 第八章 对象工厂
// day-2025-10-31
template <class AbstractProduct,
          typename IdentifierType,
          typename ProductCreator>
class Factory
{
public:
    bool Register(const IdentifierType &id, ProductCreator creator)
    {
        return associations_.insert(AssocMap::value_type(id, creator)).second;
    }

    bool Unregister(const IdentifierType &id)
    {
        return associations_.erase(id) == 1;
    }

    AbstractProduct *CreateObject(const IdentifierType &id)
    {
        typename AssocMap::const_iterator i = associations_.find(id);
        if (i != associations_.end())
        {
            return (i->second)();
        }
        // handle error
    }

private:
    typedef std::map<IdentifierType, AbstractProduct> AssocMap;
    AssocMap associations_;
};

template <class IdentifierType, class ProductType>
class DefaultFactoryError
{
public:
    class Exception : public std::exception
    {
    public:
        Exception(const IdentifierType &unKnownId)
            : unknowId_(unKnownId)
        {
        }

                virtual const char* what9)
                {
                    return "Unknown object type passed to Factory.";
                }
                const IdentifierType GetId()
                {
                    return unknowId_;
                }

            private:
                IdentifierType unknowId_;
    };
};
