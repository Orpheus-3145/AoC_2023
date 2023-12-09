#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

bool    check_line(std::vector<long> line)
{
	for (long n : line)
	{
		if (n != 0)
			return (false);
	}
	return (true);
}

long extrapolate(std::string line)
{
    std::istringstream  iss(line);
	long  		        count=0, n=0;
	std::vector<long>   increments, row;

	while(iss >> n)
        row.push_back(n);
	count += n;
	while (true)
	{
		for (size_t i=0; i<row.size() - 1; i++)
			increments.push_back(row[i + 1] - row[i]);
		if (check_line(increments) == true)
			break ;
		count += increments.back();
		row = increments;
		increments.clear();
	}
	return (count);
}

long  part1(char *file_name)
{
	long                tot = 0;
	std::ifstream	    inFile(file_name);
    std::string         line;

	if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
		tot += extrapolate(line);
	inFile.close();
	return (tot);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
	return (0);
}
