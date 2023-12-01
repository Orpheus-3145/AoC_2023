#include "part1.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>

size_t  findNumber(std::string line)
{
    auto start = line.begin();
    auto end = line.end();
    end--;
    while (start != end)
    {
        if (! isdigit(*start))
            start++;
        if (! isdigit(*end))
            end--;
    }
    
}

size_t  part1(char *file_name)
{
    size_t tot = 0, nl = 0, last_nl = 0;

	std::ifstream	inFile(file_name);
    if (!inFile.is_open())  //check if infile exists and has permissions
		return (0);
    std::stringstream buffer;
    buffer << inFile.rdbuf(); // read entire contents of file into buffer

    std::string line, content = buffer.str();
    do
    {
        nl = content.find("\n", last_nl);
        line = content.substr(last_nl, nl - last_nl);
        tot += findNumber(line);
        last_nl = nl + 1;
    } while (nl != std::string::npos);
    inFile.close();
    return (tot);
}



