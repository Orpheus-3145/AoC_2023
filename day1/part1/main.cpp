#include "part1.hpp"
#include <iostream>

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) << '\n';
    return (0);
}