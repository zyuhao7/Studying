#include <iostream>
#include <string>
#include "scienum.h"

enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
};

int main()
{
    std::cout << scienum::details::get_enum_name(YELLOW) << std::endl;
    std::cout << scienum::details::enum_from_name<Color>("YELLOW") << std::endl;
}
