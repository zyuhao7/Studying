#include <iostream>
#include <string>

/*房东要把⼀个房⼦通过中介租出去理解代理模式*/
class RentHouse
{
public:
    virtual void rentHouse() = 0;
};

/*房东类：将房⼦租出去*/

class Landlord : public RentHouse
{
public:
    void rentHouse()
    {
        std::cout << "将房⼦租出去\n";
    }
};

/*中介代理类：对租房⼦进⾏功能加强，实现租房以外的其他功能*/

class Intermediary : public RentHouse
{
public:
    void rentHouse()
    {
        std::cout << "发布招租启⽰\n";
        std::cout << "带⼈看房\n";
        _landlord.rentHouse();
        std::cout << "负责租后维修\n";
    }

private:
    Landlord _landlord;
};

int main()
{
    Intermediary intermediary;
    intermediary.rentHouse();
    return 0;
}
