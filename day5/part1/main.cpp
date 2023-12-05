#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstddef>
#include <algorithm>

typedef std::vector<std::vector< std::vector<size_t > > > maps_t;
typedef std::vector<std::vector<size_t > > map_t;

size_t build_number(std::string::reverse_iterator& n_pos, std::string::reverse_iterator end)
{
	size_t n = 0, exp=0;
	while ((n_pos != end) and isdigit(*n_pos))
		n += (*n_pos++ - '0') * powl(10, exp++);
	return (n);
}

std::vector<size_t>    get_numbers_line(std::string line)
{
	std::vector<size_t> seeds;

	for (auto it=line.rbegin(); it!=line.rend();)
	{
		if (isdigit(*it))
			seeds.push_back(build_number(it, line.rend()));
		else
			it++;
	}
	std::reverse(seeds.begin(), seeds.end());
	return (seeds);
}

maps_t fill_maps(std::ifstream& fd)
{
	maps_t maps;
	map_t map;
	std::string line;
	
	while (std::getline(fd, line))
	{
		if (isdigit(line[0]))
			map.push_back(get_numbers_line(line));     
		else if (map.empty() == false)
		{
			maps.push_back(map);
			map.clear();
		}
	}
	if (map.empty() == false)
	{
		maps.push_back(map);
		map.clear();
	}
	return (maps);
}

size_t    next_hop_value(map_t map, size_t seed)
{
	size_t  next_hop = SIZE_MAX;
	long    diff = -1;

	for (auto triple : map)
	{
		if ((seed >= triple[1]) and (seed < triple[1] + triple[2]))
		{
			diff = triple[0] - triple[1];
			next_hop = seed + diff;
			break;
		}
	}
	if (next_hop == SIZE_MAX)
		next_hop = seed;
	return (next_hop);
}

size_t  part1(char *file_name)
{
	size_t 				min=SIZE_MAX, next_hop=SIZE_MAX;
	std::string			line;
	std::vector<size_t>	seeds;
	maps_t				maps;
	std::ifstream		inFile(file_name);
	if (!inFile.is_open())
		return (0);
	std::getline(inFile, line);
	seeds = get_numbers_line(line);
	maps = fill_maps(inFile);
	inFile.close();
	for (size_t seed : seeds)
	{
		next_hop = seed;
		for (map_t map: maps)
			next_hop = next_hop_value(map, next_hop);
		if (min > next_hop)
			min = next_hop;
	}
	return (min);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
	return (0);
}
