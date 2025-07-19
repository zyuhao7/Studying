#include <iostream>
#include <string>

// day-2025-7-19
/*
代理模式（Proxy Pattern）详解
========================================
    一、核心概念
    代理模式是一种结构型设计模式，它通过创建一个代理对象来控制对真实对象的访问。
    代理对象作为客户端与真实对象之间的中介，可以实现请求的预处理、访问控制、延迟加载等功能。

    二、核心角色（详见 proxy_pattern_diagram.svg 关系图）
    1. Subject（抽象主题）：定义代理和真实主题的共同接口
    2. RealSubject（真实主题）：实现具体业务逻辑，是被代理的对象
    3. Proxy（代理）：维护指向RealSubject的引用，控制对其访问

    三、与其他模式的对比分析
    | 模式       | 核心意图                  | 与代理模式的区别                     | 典型应用场景               |
    |------------|---------------------------|--------------------------------------|----------------------------|
    | 代理模式   | 控制对象访问              | 维持与RealSubject的相同接口          | 延迟加载、权限控制         |
    | 装饰器模式 | 动态添加对象功能          | 关注功能增强，通常会嵌套多个装饰器   | GUI组件扩展、日志增强      |
    | 适配器模式 | 转换接口适配不同客户端    | 改变接口，使不兼容的类可以一起工作   | 第三方库集成、接口兼容     |
    | 外观模式   | 简化复杂系统的访问接口    | 为多个对象提供统一入口，不控制访问   | 子系统封装、API网关        |

    四、独特优势
    1. 实现延迟初始化（Lazy Initialization）
    - 如示例中仅在首次display()时才创建RealImage对象
    2. 增强安全性与访问控制
    - 可在调用真实对象前进行权限验证
    3. 优化性能与资源占用
    - 避免创建开销大的对象直到真正需要
    4. 实现远程代理
    - 可作为网络对象的本地代表（如RPC调用）
    5. 实现日志记录与监控
    - 在不修改真实对象的情况下添加横切关注点

    五、典型应用场景
    • 数据库连接池管理
    • 大型文件的延迟加载
    • 权限控制系统
    • 远程服务调用代理
    • 缓存代理（如Redis缓存）
    • 智能引用（如C++的shared_ptr）

    六、关系图说明
    详见配套文件 proxy_pattern_diagram.svg，包含：
    1. 代理模式核心结构（Subject-RealSubject-Proxy关系）
    2. 与装饰器/适配器/外观模式的关系对比
    3. 类之间的关联与实现关系
*/

// 1. 抽象主题（Subject）
class Image
{
public:
    virtual ~Image() = default;
    virtual void display() const = 0;
};

// 2. 真实主题（RealSubject）
class RealImage : public Image
{
private:
    std::string filename;

    // 模拟加载图片的耗时操作
    void loadFromDisk() const
    {
        std::cout << "Loading image: " << filename << std::endl;
    }

public:
    explicit RealImage(std::string name)
        : filename(std::move(name))
    {
        loadFromDisk(); // 构造时加载图片
    }

    void display() const override
    {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

// 3. 代理类（Proxy）
class ImageProxy : public Image
{
private:
    mutable RealImage *realImage; // 延迟初始化的真实对象
    std::string filename;

public:
    explicit ImageProxy(std::string name)
        : realImage(nullptr),
          filename(std::move(name)) {}

    ~ImageProxy() override
    {
        delete realImage; // 负责释放真实对象
    }

    // 延迟加载：只有在需要时才创建真实对象
    void display() const override
    {
        if (!realImage)
        {
            realImage = new RealImage(filename);
        }
        realImage->display(); // 调用真实对象的方法
    }
};

// 客户端代码
int main()
{
    // 使用代理模式创建图片（初始不会加载图片）
    Image *image = new ImageProxy("design_patterns.png");
    std::cout << "Image created, but not loaded yet.\n";

    // 第一次显示时才会真正加载图片
    std::cout << "First display:\n";
    image->display();

    // 第二次显示时直接使用已加载的图片
    std::cout << "Second display:\n";
    image->display();

    delete image;
    return 0;
}
