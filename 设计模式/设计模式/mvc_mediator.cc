#include <iostream>
#include <string>
#include <vector>

/*
MVC架构中中介者模式的应用详解
    一、MVC与中介者模式的内在联系
        MVC架构中的 Controller（控制器）本质上就是中介者模式的实现 ，它承担了Model（模型）与View（视图）之间的协调工作，
        避免两者直接通信。这种设计完全符合中介者模式"通过第三方对象封装对象间交互"的核心思想。

    二、角色对应关系
    MVC组件             中介者模式角色          核心职责
    Model               同事类                  处理业务逻辑、数据存储和管理
    View                同事类                  负责展示界面、接收用户输入
    Controller          中介者                  协调Model和View之间的交互，处理用户请求
    用户输入/事件       交互触发源              启动整个交互流程的外部事件

    三、详细协作流程
┌─────────┐     通知事件   ┌────────────┐     调用业务逻辑    ┌─────────┐
│  View            │ -------------> │ Controller             │ ----------------->  │ Model            │
│（登录页）        │                │（中介者）              │                     │（用户数据）      │
└─────────┘                └────────────┘                     └─────────┘
        ▲                           │                          │
        │                           │                          │
        │       更新视图            │         返回结果         │
        │ <-----------------------  │<--------------------------
        │                           │                          │

    四、中介者模式在MVC中的核心价值
        - 1.
        解耦Model与View ：
            - Model不知道View的存在，只需关注业务逻辑
            - View不直接操作Model，通过Controller间接通信
            - 修改View时无需改动Model，反之亦然
        - 2.
        集中控制交互流程 ：
            - 所有用户操作都由Controller统一处理
            - 避免出现Model←→View的直接依赖和复杂网状关系
            - 符合"单一职责原则"：Controller只负责协调，不处理业务逻辑
        -3.
        支持多视图协作 ：当中介者需要协调多个View时优势更明显，例如：
        ┌────────────┐
        │ Controller             │ ← 中介者协调多个视图
        ├────────────┤
        │ ┌─────────┐ │┌─────────┐│ ┌─────────┐
        │ │ View A           │ ││ View B           ││ │ View C           │
        │ └─────────┘ │└─────────┘│ └─────────┘
        └────────────┘
*/
// 预先声明类，避免循环依赖
class UserModel;
class LoginView;

// 具体中介者：Controller
class Controller
{
private:
    UserModel *model; // 持有同事对象引用
    LoginView *view;

public:
    Controller()
        : model(nullptr), view(nullptr) {}
    void setModel(UserModel *m) { model = m; }
    void setView(LoginView *v) { view = v; }

    // 处理登录请求（核心中介逻辑）
    void handleLoginRequest(const std::string &user, const std::string &pwd);
    // 响应模型变化
    void onModelChanged(UserModel *model);
};

// 抽象同事类（MVC组件基类）
class MVCComponent
{
protected:
    Controller *mediator;

public:
    MVCComponent(Controller *med)
        : mediator(med) {}
    virtual ~MVCComponent() = default;
};

// 具体同事类：Model
class UserModel : public MVCComponent
{
private:
    std::string username;
    bool isLoggedIn;

public:
    UserModel(Controller *med)
        : MVCComponent(med),
          username(""),
          isLoggedIn(false) {}

    // 业务逻辑：登录验证
    bool login(const std::string &user, const std::string &pwd)
    {
        if (pwd == "password")
        { // 简化验证
            username = user;
            isLoggedIn = true;
            mediator->onModelChanged(this); // 通知中介者状态变化
            return true;
        }
        return false;
    }

    std::string getUsername() const { return username; }
    bool getLoginStatus() const { return isLoggedIn; }
};

// 具体同事类：View
class LoginView : public MVCComponent
{
public:
    LoginView(Controller *med)
        : MVCComponent(med) {}

    // 展示界面
    void render()
    {
        std::cout << "=== 登录界面 ===\n";
        std::cout << "用户名: ________\n";
        std::cout << "密码: ________\n";
        std::cout << "[登录按钮]\n";
    }

    // 接收用户输入并通知中介者
    void onLoginButtonClicked(const std::string &user, const std::string &pwd)
    {
        mediator->handleLoginRequest(user, pwd);
    }

    // 显示登录结果
    void showMessage(const std::string &msg)
    {
        std::cout << "【提示】" << msg << std::endl;
    }
};

void Controller::handleLoginRequest(const std::string &user, const std::string &pwd)
{
    bool success = model->login(user, pwd);
    if (success)
    {
        view->showMessage("登录成功！欢迎您，" + model->getUsername());
    }
    else
    {
        view->showMessage("登录失败：密码错误");
    }
}

void Controller::onModelChanged(UserModel *model)
{
    std::cout << "中介者收到模型更新通知: 用户" << model->getUsername() << "已登录\n";
}

// 客户端代码
int main()
{
    Controller *controller = new Controller();

    UserModel *model = new UserModel(controller);
    LoginView *view = new LoginView(controller);

    controller->setModel(model);
    controller->setView(view);

    // 运行流程
    view->render();
    view->onLoginButtonClicked("admin", "password"); // 模拟用户输入
    /*
        === 登录界面 ===
        用户名: ________
        密码: ________
        [登录按钮]
        中介者收到模型更新通知: 用户admin已登录
        【提示】登录成功！欢迎您，admin
    */
    // 释放资源
    delete model;
    delete view;
    delete controller;
    return 0;
}