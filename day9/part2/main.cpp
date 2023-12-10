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
	long  		    count=0, n=0;
	std::vector<long>   increments, new_row, firsts;

    while(iss >> n)
        new_row.push_back(n);
    firsts.push_back(new_row.front());
	while (true)
	{
		for (size_t i=0; i<new_row.size() - 1; i++)
			increments.push_back(new_row[i + 1] - new_row[i]);
		if (check_line(increments) == true)
			break ;
		firsts.push_back(increments.front());
		new_row = increments;
		increments.clear();
	}
        for (auto it=firsts.rbegin(); it!=firsts.rend(); it++)
        	count = *it - count;
	return (count);
}

long  part2(char *file_name)
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
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
