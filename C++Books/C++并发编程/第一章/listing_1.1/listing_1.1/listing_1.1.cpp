#include <iostream>
#include <thread>
using namespace std;

void hello()
{
    std::cout << "Hello Concurrent World\n";
}

int main()
{
    cout << _MSVC_LANG << endl;
    std::thread t(hello);
    t.join();
}
