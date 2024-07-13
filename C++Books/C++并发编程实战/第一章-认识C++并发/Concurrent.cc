#include <iostream>
#include <thread>
using namespace std;
void hello()
{
    cout << "hello concurrent world!\n";
}




int main()
{
    thread t(hello);
    t.join();
}