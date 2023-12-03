#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>

int build_number(std::string::iterator n_pos)
{
	int n = 0, exp=0;
	while (isdigit(*n_pos))
		n += (*n_pos-- - '0') * pow(10, exp++);
	return (n);
}

int    get_index(std::string line)
{
	size_t pos_color = 0;
	std::map<int, std::string> limits = {{12, "red"}, {13, "green"}, {14, "blue"}};

	for(auto limit : limits)
	{
		pos_color = line.find(limit.second, 0);
		while (pos_color != std::string::npos)
		{
			if (build_number(line.begin() + pos_color - 2) > limit.first)
				return (0);
			pos_color = line.find(limit.second, pos_color + 1);
		}
	}
	return (build_number(line.begin() + line.find(":") - 1));
}

size_t  part1(char *file_name)
{
	size_t tot = 0;
	std::string line;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
		tot += get_index(line);
	return (tot);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
	return (0);
}
