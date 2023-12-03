#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <map>

std::map<const char*, int> numbers({{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}});

int cast_front(const char *line, int pos)
{
	int i = 0;
	
	if (isdigit(line[pos]))
		return (line[pos] - '0');
	for (std::pair<const char*, int> number : numbers)
	{
		i = 0;
		while (line[pos + i] and number.first[i])
		{
			if (line[pos + i] != number.first[i])
				break;
			i++;
		}
		if (number.first[i] == '\0')
			return (number.second);
	}
	return (-1);
}

int cast_back(const char *line, int pos)
{ 
	int len_needle = -1, i = 0;;

	if (isdigit(line[pos]))
		return (line[pos] - '0');
	for (std::pair<const char*, int> number : numbers)
	{
		len_needle = strlen(number.first);
		if ((pos - len_needle + 1) < 0)
			continue;
		i = 0;
		while (i < len_needle)
		{
			if (number.first[len_needle - 1 - i] != line[pos - i])
				break;
			i++;
		}
		if (i == len_needle)
			return (number.second);
	}
	return (-1);
}

size_t  findNumber(const char* line)
{
	int start = 0, end = strlen(line) - 1;
	int cast_start = cast_front(line, start), cast_end = cast_back(line, end);
	while (start < end)
	{
		if ((cast_start != -1) and (cast_end != -1))
			return (cast_start * 10 + cast_end);
		if (cast_start == -1)
			cast_start = cast_front(line, ++start);
		if (cast_end == -1)
			cast_end = cast_back(line, --end);
	}
	return (0);
}

size_t  part2(char *file_name)
{
	size_t tot = 0;
	std::string line;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
		tot += findNumber(line.c_str());
	inFile.close();
	return (tot);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part2: " << part2(argv[1]) << '\n';
	return (0);
}
