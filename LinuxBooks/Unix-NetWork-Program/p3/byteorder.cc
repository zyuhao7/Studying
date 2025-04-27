#include <iostream>


int main() {
    union {
        uint32_t i;
        char c[4];
    } u;

    u.i = 0x01020304;

    if (u.c[0] == 0x01) {
        std::cout << "大端字节序(Big Endian)" << std::endl;
    } else if (u.c[0] == 0x04) {
        std::cout << "小端字节序(Little Endian)" << std::endl;
    } else {
        std::cout << "未知字节序" << std::endl;
    }

    return 0;
}
