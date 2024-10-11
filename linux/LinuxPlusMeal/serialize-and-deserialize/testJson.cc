#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <jsoncpp/json/json.h>

int main()
{
    // 序列化
    // Json::Value root;
    // root["name"] = "茶颜悦色";
    // root["sex"] = "女";
    // std::string s = root.toStyledString();
    // std::cout << s << std::endl;

    // Json::Value root;
    // root["name"] = "烟花茶仙";
    // root["sex"] = "男";
    // Json::StreamWriterBuilder wbuilder; // StreamWriter 的工厂
    // std::unique_ptr<Json::StreamWriter> writer(wbuilder.newStreamWriter());
    // std::stringstream ss;
    // writer->write(root, &ss);
    // std::cout << ss.str() << std::endl;

    // Json::Value root;
    // root["name"] = "荷塘月色";
    // root["sex"] = "女";
    // Json::FastWriter writer;
    // std::string s = writer.write(root);
    // std::cout << s << std::endl;

    // Json::Value root;
    // root["name"] = "残垣断壑";
    // root["sex"] = "男";
    // // Json::FastWriter writer;
    // Json::StyledWriter writer;
    // std::string s = writer.write(root);
    // std::cout << s << std::endl;

    // 反序列化 JSON 字符串

    // std::string json_string = "{\"name\":\"张三\",\"age\":30, \"city\":\"北京\"}";
    // // 解析 JSON 字符串
    // Json::Reader reader;
    // Json::Value root;
    // // 从字符串中读取 JSON 数据
    // bool parsingSuccessful = reader.parse(json_string,
    //                                       root);
    // if (!parsingSuccessful)
    // {
    //     // 解析失败，输出错误信息
    //     std::cout << "Failed to parse JSON: " << reader.getFormattedErrorMessages() << std::endl;
    //     return 1;
    // }

    // // 访问 JSON 数据
    // std::string name = root["name"].asString();
    // int age = root["age"].asInt();
    // std::string city = root["city"].asString();
    // // 输出结果
    // std::cout << "Name: " << name << std::endl;
    // std::cout << "Age: " << age << std::endl;
    // std::cout << "City: " << city << std::endl;

    return 0;
}
