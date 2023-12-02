#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

size_t  findNumber(std::string line)
{
	auto start = line.begin();
	auto end = line.end();
	end--;
	while (start != end)
	{
		if (isdigit(*start) and isdigit(*end))
		   return ((*start - '0') * 10 + *end - '0');
		if (! isdigit(*start))
		    start++;
		if (! isdigit(*end))
		    end--;
	}
	return (0);
}

size_t  part1(char *file_name)
{
    size_t tot = 0;
    std::string line;

	std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    while (std::getline(inFile, line))
        tot += findNumber(line);
    inFile.close();
    return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) << '\n';
    return (0);
}
