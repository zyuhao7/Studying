#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// day-2025-7-27
/*
    观察者设计模式（Observer Pattern）:
    核心角色
    1. 抽象主题（Subject） ：定义注册、移除和通知观察者的接口
    2  具体主题（ConcreteSubject） ：维护状态并通知观察者
    3. 抽象观察者（Observer）：定义接收通知的更新接口
    4. 具体观察者（ConcreteObserver） ：实现更新接口，处理主题通知
*/
// 抽象观察者
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

// 抽象主题
class Subject
{
public:
    virtual ~Subject() = default;
    virtual void registerObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
};

// 具体主题：气象站
class WeatherData : public Subject
{
private:
    std::vector<Observer *> observers;
    float temperature; // 温度
    float humidity;    // 湿度
    float pressure;    // 气压

public:
    void registerObserver(Observer *observer) override
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer) override
    {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }

    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update(temperature, humidity, pressure);
        }
    }

    // 当气象数据更新时调用
    void measurementsChanged()
    {
        notifyObservers();
    }

    // 设置气象数据
    void setMeasurements(float temp, float humi, float press)
    {
        temperature = temp;
        humidity = humi;
        pressure = press;
        measurementsChanged();
    }
};

// 具体观察者：当前条件显示器
class CurrentConditionsDisplay : public Observer
{
private:
    float temperature;
    float humidity;
    Subject *weatherData; // 持有主题引用，方便取消订阅

public:
    explicit CurrentConditionsDisplay(Subject *subject) : weatherData(subject)
    {
        weatherData->registerObserver(this);
    }

    ~CurrentConditionsDisplay() override
    {
        weatherData->removeObserver(this);
    }

    void update(float temp, float humi, float press) override
    {
        temperature = temp;
        humidity = humi;
        display();
    }

    void display()
    {
        std::cout << "当前天气状况：" << std::endl;
        std::cout << "温度：" << temperature << "°C" << std::endl;
        std::cout << "湿度：" << humidity << "%" << std::endl;
        std::cout << "------------------------" << std::endl;
    }
};

// 具体观察者：统计数据显示器
class StatisticsDisplay : public Observer
{
private:
    float maxTemp = 0;
    float minTemp = 1000;
    float tempSum = 0;
    int numReadings = 0;

public:
    void update(float temp, float humi, float press) override
    {
        tempSum += temp;
        numReadings++;

        if (temp > maxTemp)
            maxTemp = temp;
        if (temp < minTemp)
            minTemp = temp;

        display();
    }

    void display()
    {
        std::cout << "温度统计数据：" << std::endl;
        std::cout << "平均温度：" << (tempSum / numReadings) << "°C" << std::endl;
        std::cout << "最高温度：" << maxTemp << "°C" << std::endl;
        std::cout << "最低温度：" << minTemp << "°C" << std::endl;
        std::cout << "------------------------" << std::endl;
    }
};

// int main()
// {
//     // 创建主题（气象站）
//     WeatherData weatherStation;

//     // 创建观察者并注册到主题
//     CurrentConditionsDisplay currentDisplay(&weatherStation);
//     StatisticsDisplay statsDisplay;
//     weatherStation.registerObserver(&statsDisplay);

//     // 模拟气象数据更新
//     weatherStation.setMeasurements(25.6f, 65.0f, 1013.2f);
//     weatherStation.setMeasurements(28.3f, 70.0f, 1012.8f);
//     weatherStation.setMeasurements(22.1f, 55.0f, 1014.1f);

//     return 0;
// }