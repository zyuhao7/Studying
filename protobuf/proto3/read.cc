#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace contacts;

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