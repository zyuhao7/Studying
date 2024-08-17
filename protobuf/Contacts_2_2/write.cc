#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace contacts;

// 新增联系人

void AddPeopleInfo(PeopleInfo *people_info_ptr)
{
    cout << "------------新增联系人------------" << endl;

    cout << "请输入联系人姓名:> ";
    string name;
    getline(cin, name);
    people_info_ptr->set_name(name);

    cout << "请输入联系人年龄:> ";
    int age;
    cin >> age;
    people_info_ptr->set_age(age);
    cin.ignore(256, '\n');

    for (int i = 1;; i++)
    {
        cout << "请输入联系人电话 " << i << " (只输入回车完成电话新增): ";
        string number;
        getline(cin, number);
        if (number.empty())
            break;

        PeopleInfo_Phone *phone = people_info_ptr->add_phone();
        phone->set_number(number);

        cout << "请输入该电话类型(1、移动电话   2、固定电话): ";
        int type;
        cin >> type;
        cin.ignore(256, '\n');
        switch (type)
        {
        case 1:
            phone->set_type(PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
            break;
        case 2:
            phone->set_type(PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_F_TEL);
            break;
        default:
            cout << "选择有误！" << endl;
            break;
        }
    }

    Address addr;
    cout << "请输入联系人家庭地址: ";

    string home_addr;
    getline(cin, home_addr);
    addr.set_home_address(home_addr);

    cout << "请输入联系人单位地址: ";
    string unit_addr;
    getline(cin, unit_addr);
    addr.set_unit_address(unit_addr);

    google::protobuf::Any *data = people_info_ptr->mutable_data();
    data->PackFrom(addr);
    cout << "------------添加联系人成功------------" << endl;
}

int main(int argc, char *argv[])
{

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " CONTACTS_FILE" << endl;
        return -1;
    }

    Contacts contacts;

    // 先读取已存在的 contacts.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input)
    {
        cout << argv[1] << ": File not found. Create a new file." << endl;
    }
    else if (!contacts.ParseFromIstream(&input))
    {
        cerr << "Failed to parse contacts." << endl;
        input.close();
        return -1;
    }

    // 新增一个联系人.
    AddPeopleInfo(contacts.add_contacts());

    // 向磁盘文件写入新的 contacts
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!contacts.SerializeToOstream(&output))
    {
        cerr << "Failed to write contacts. " << endl;
        input.close();
        output.close();
        return -1;
    }

    input.close();
    output.close();

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}