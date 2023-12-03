#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <cmath>

int build_number(std::string::iterator n_pos)
{
	int n = 0, exp=0;
	while (isdigit(*n_pos))
		n += (*n_pos-- - '0') * pow(10, exp++);
	return (n);
}

int    get_min_prod(std::string line)
{
	size_t pos_color = 0;
    int count = 0, prod = 1, max = 0;
    std::set< std::string>  colors = {"red", "green", "blue"};
	for(auto color : colors)
	{
        max = 0;
		pos_color = line.find(color, 0);
		while (pos_color != std::string::npos)
		{
            count = build_number(line.begin() + pos_color - 2);
			if ( count > max)
				max = count;
			pos_color = line.find(color, pos_color + 1);
		}
        prod *= max;
	}
	return (prod);

}
size_t  part2(char *file_name)
{
	size_t tot = 0;
	std::string line;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
        tot += get_min_prod(line);
	return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
