## 观察者模式
* 定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都要得到通知并自动更新.

```c++
/*观察者模式从根本上讲必须包含两个角色：观察者和被观察对象

被观察对象自身应该包含一个容器来存放观察者对象，当被观察者自身发生改变时通知容器内所有的观察者对象自动更新.

观察者对象可以注册到被观察者中，完成注册后可以检测被观察者的变化，接收被观察者的通知。当然观察者也可以被注销掉，停止对被观察者的监控.


code1: 博客园版.

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

/**
 *  关键代码: 在目标类中增加一个 ArrayList 来存放观察者们.
 */

class View;

// 被观察者抽象类 - 数据模型.
class DataModel
{
public:
    virtual ~DataModel(){};
    virtual void addView(View *v) = 0;
    virtual void removeView(View *v) = 0;
    virtual void notify() = 0; // 通知函数.
};

// 观察者抽象类 - 视图
class View
{
public:
    virtual ~View() { cout << "~View()" << endl; }
    virtual void update() = 0;
    virtual void setViewName(const string &name) = 0;
    virtual const string &name() = 0;
};

// 具体的被观察者 - 整数模型
class IntDataModel : public DataModel
{
public:
    ~IntDataModel()
    {
        m_pViewList.clear();
    }

    void addView(View *v) override
    {
        shared_ptr<View> temp(v);
        auto it = find(m_pViewList.begin(), m_pViewList.end(), temp);
        if (it == m_pViewList.end())
        {
            m_pViewList.push_front(temp);
        }
        else
        {
            cout << "View Already exists!" << endl;
        }
    }

    void removeView(View *v) override
    {
        auto it = m_pViewList.begin();
        for (; it != m_pViewList.end(); it++)
        {
            if ((*it).get() == v)
            {
                m_pViewList.erase(it);
                cout << "Remove view success!" << endl;
                return;
            }
        }
    }

    void notify() override
    {
        auto it = m_pViewList.begin();
        for (; it != m_pViewList.end(); ++it)
        {
            (*it).get()->update();
        }
    }

private:
    list<shared_ptr<View>> m_pViewList;
};

// 具体的观察者类 - 表视图
class TableView : public View
{
public:
    TableView()
        : m_name("unKnown!")
    {
    }

    TableView(const string &name)
        : m_name(name)
    {
    }

    ~TableView() { cout << "~TableView():" << m_name.data() << endl; }

    void setViewName(const string &name)
    {
        m_name = name;
    }

    const string &name()
    {
        return m_name;
    }

    void update() override
    {
        cout << m_name.data() << "updata. " << endl;
    }

private:
    string m_name;
};

int main()
{

    /*
     * 这里需要补充说明的是在此示例代码中,View一旦被注册到DataModel类之后,DataModel解析时会自动解析掉内部容器中存储的View对象
     * 因此注册后的View对象不需要在手动去delete，再去delete View对象会出错.
     */

    View *v1 = new TableView("TableView1");
    View *v2 = new TableView("TableView2");
    View *v3 = new TableView("TableView3");
    View *v4 = new TableView("TableView4");

    IntDataModel *model = new IntDataModel;
    model->addView(v1);
    model->addView(v2);
    model->addView(v3);
    model->addView(v4);

    model->notify();

    cout << "=========================" << endl;

    model->removeView(v1);

    model->notify();

    delete model;

    model = nullptr;

    return 0;
}

*/

```