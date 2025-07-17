#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    day-2025-7-17
    Flyweight 模式（享元模式） 是结构型设计模式之一，通过共享对象的方式来减少内存占用和提高性能。
        ┌────────────┐
        │        Client          │  ←←←←  客户端类，包含外部状态
        └────┬───────┘
                  │
                  ▼
        ┌────────────┐
        │         Flyweight      │  ←←←←  享元类，包含共享的不可变部分
        └────┬───────┘
        ┌────┴──────────────┐
        ▼                                      ▼
    ┌────────────┐      ┌────────────┐
    │ SubsystemA             │      │ SubsystemB             │  ←←←←  子系统（可多个）
    └────────────┘      └────────────┘
     优势:
     减少内存占用：共享相同属性的对象只占用一份内存
     提高性能：避免重复创建相同对象

     缺点:
     增加复杂性：引入新的类和工厂
     不支持外部状态：享元模式不支持外部状态，每个对象只能有自己的内部状态
    */
// Flyweight类 - 包含共享的不可变部分
class TreeType
{
private:
    std::string name_;
    std::string color_;
    std::string texture_;

public:
    TreeType(const std::string &name, const std::string &color, const std::string &texture)
        : name_(name), color_(color), texture_(texture) {}

    void draw(int x, int y) const
    {
        std::cout << "Drawing tree type " << name_
                  << " with color " << color_
                  << " and texture " << texture_
                  << " at position (" << x << ", " << y << ")" << std::endl;
    }
};

// Flyweight工厂 - 创建和管理Flyweight对象
class TreeFactory
{
private:
    static std::unordered_map<std::string, TreeType *> treeTypes_;

public:
    static TreeType *getTreeType(const std::string &name, const std::string &color, const std::string &texture)
    {
        std::string key = name + color + texture;
        if (treeTypes_.find(key) == treeTypes_.end())
        {
            treeTypes_[key] = new TreeType(name, color, texture);
        }
        return treeTypes_[key];
    }

    static void printTreeTypes()
    {
        std::cout << "Total tree types created: " << treeTypes_.size() << std::endl;
    }
};

std::unordered_map<std::string, TreeType *> TreeFactory::treeTypes_;

// 客户端类 - 包含外部状态
class Tree
{
private:
    int x_;
    int y_;
    TreeType *type_;

public:
    Tree(int x, int y, TreeType *type)
        : x_(x), y_(y), type_(type) {}

    void draw() const
    {
        type_->draw(x_, y_);
    }
};

// 森林类 - 创建和管理大量Tree对象
class Forest
{
private:
    vector<Tree *> trees_;

public:
    void plantTree(int x, int y, const std::string &name, const std::string &color, const std::string &texture)
    {
        TreeType *type = TreeFactory::getTreeType(name, color, texture);
        trees_.push_back(new Tree(x, y, type));
    }

    void draw() const
    {
        for (const auto &tree : trees_)
        {
            tree->draw();
        }
    }

    ~Forest()
    {
        for (auto tree : trees_)
        {
            delete tree;
        }
    }
};

int main()
{
    Forest forest;

    // 种植1000棵树，但只创建了2种TreeType对象
    for (int i = 0; i < 500; ++i)
    {
        forest.plantTree(i, i, "Oak", "Green", "Rough");
        forest.plantTree(i + 1, i, "Pine", "Dark Green", "Smooth");
    }

    TreeFactory::printTreeTypes();
    forest.draw();

    return 0;
}