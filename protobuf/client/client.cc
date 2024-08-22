#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace c_contacts;

// 打印联系人列表
void PrintContacts(const Contacts &contacts)
{
    for (int i = 0; i < contacts.contacts_size(); ++i)
    {
        const PeopleInfo &people = contacts.contacts(i);

        cout << "--------联系人" << i + 1 << "--------" << endl;
        cout << "姓名: " << people.name() << endl;
        cout << "年龄: " << people.age() << endl;

        int j = 1;
        for (const PeopleInfo_Phone &phone : people.phone())
        {
            cout << "电话 " << j++ << phone.number() << endl;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << "CONTACTS_FILE" << endl;
        return -1;
    }
    // 以二进制方式读取 contacts
    Contacts contacts;
    fstream input(argv[1], ios::in | ios::binary);
    if (!contacts.ParseFromIstream(&input))
    {
        cerr << "Failed to parse contacts. " << endl;
        input.close();
        return -1;
    }

    // 打印 contacts
    PrintContacts(contacts);

    input.close();
    return 0;
}

/*
    --------联系人1--------
    姓名: 王红
    年龄: 17
    电话 11234567890

    --------联系人2--------
    姓名: 李岚
    年龄: 16
    电话 11254632146

    --------联系人3--------
    姓名: 秀娥
    年龄: 1020
    电话 1145

    --------联系人4--------
    姓名: 王五
    年龄: 0
    电话 11123



*/