#include <iostream>
#include <vector>
#include <string>
#include <memory>

// 2025-7-23 迭代器模式
/*
    迭代器模式（Iterator Pattern）介绍
    迭代器模式是一种行为型设计模式，它提供了一种方法来顺序访问聚合对象中的元素，而无需暴露聚合对象的内部表示。
    迭代器模式将遍历逻辑封装在迭代器对象中，使得同一聚合对象可以有多种遍历方式，同时简化了聚合类的设计。
 核心角色
    1.
     抽象迭代器（Iterator） ：定义访问和遍历元素的接口（如 hasNext() 、 next() ）。
    2.
   具体迭代器（Concrete Iterator） ：实现抽象迭代器接口，完成对聚合对象的遍历，记录当前位置。
    3.
   抽象聚合（Aggregate） ：定义创建迭代器对象的接口（如 createIterator() ）。
    4.
   具体聚合（Concrete Aggregate） ：实现抽象聚合接口，返回具体迭代器实例。

    迭代器模式的优点
    - 单一职责原则 ：遍历逻辑封装在迭代器中，聚合类只需关注元素存储。
    - 开闭原则 ：新增迭代器或聚合类无需修改现有代码。
    - 解耦 ：客户端通过迭代器接口访问聚合对象，无需依赖具体聚合类型
*/
// 抽象迭代器
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual std::string next() = 0;
    virtual ~Iterator() = default;
};

// 抽象聚合
class Aggregate
{
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;
    virtual ~Aggregate() = default;
};

// 具体聚合：书架
class BookShelf : public Aggregate
{
private:
    std::vector<std::string> books; // 存储元素的容器

public:
    std::string getBook(int index) const
    {
        return books[index];
    }

    void addBook(const std::string &book)
    {
        books.push_back(book);
    }

    int getCount()
    {
        return books.size();
    }
    // 具体迭代器：遍历书架
    class BookShelfIterator : public Iterator
    {
    private:
        std::shared_ptr<BookShelf> bookShelf; // 具体聚合对象
        int index;                            // 当前遍历位置

    public:
        BookShelfIterator(std::shared_ptr<BookShelf> bs)
            : bookShelf(bs), index(0) {}

        bool hasNext() override
        {
            return index < bookShelf->getCount();
        }

        std::string next() override
        {
            std::string book = bookShelf->getBook(index);
            index++;
            return book;
        }
    };
    std::shared_ptr<Iterator> createIterator() override
    {
        return std::make_shared<BookShelfIterator>(this); // 创建迭代器
    }
};

// 客户端代码
int main()
{
    std::shared_ptr<BookShelf> bookShelf = std::make_shared<BookShelf>();
    bookShelf->addBook("设计模式: 可复用面向对象软件的基础");
    bookShelf->addBook("C++ Primer");
    bookShelf->addBook("Effective C++");
    bookShelf->addBook("STL源码剖析");

    std::shared_ptr<Iterator> iterator = bookShelf->createIterator();

    // 使用迭代器遍历书架
    while (iterator->hasNext())
    {
        std::cout << iterator->next() << std::endl;
    }

    return 0;
}