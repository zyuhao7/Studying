#include <iostream>
#include "contacts.pb.h"

int main()
{
    std::string people_str;

    {
        // 对⼀个联系⼈的信息使⽤ PB 进⾏序列化，并将结果打印出来。
        contacts::People people;
        people.set_name("小徐");
        people.set_age(11);
        if (!people.SerializeToString(&people_str))
        {
            std::cerr << "序列化联系⼈失败！" << std::endl;
            return -1;
        }
        std::cout << "序列化成功，结果：" << people_str << std::endl;
    }

    {
        // 对序列化后的内容使⽤ PB 进⾏反序列, 解析出联系⼈信息并打印出来.
        contacts::People people;
        if (!people.ParseFromString(people_str))
        {
            std::cerr << "反序列化联系⼈失败！" << std::endl;
            return -1;
        }

        std::cout << "反序列化成功！" << std::endl
                  << "姓名： " << people.name() << std::endl
                  << "年龄： " << people.age() << std::endl;
    }

    return 0;
}
