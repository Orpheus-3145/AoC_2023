#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstddef>
#include <algorithm>

typedef std::vector<std::vector<<size_t[3] > > maps_t;
typedef std::vector<size_t[3] > map_t;

size_t build_number(std::string::reverse_iterator& n_pos, std::string::reverse_iterator end)
{
	size_t n = 0, exp=0;
	while ((n_pos != end) and isdigit(*n_pos))
		n += (*n_pos++ - '0') * powl(10, exp++);
	return (n);
}

template<size_t N>
size_t[N]    get_numbers_line(std::string line)
{
	size_t[N] seeds;

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
	size_t[3] newInput;
	
	while (std::getline(fd, line))
	{
		if (isdigit(line[0]))
			map.push_back(get_numbers_line<3>(line));     
		else if (map.empty() == false)
		{
            std::sort(map.begin(), map.end(), [] <size_t[3] x,<size_t[3] y) -> bool {return(x[0] < y[0]);});
			maps.push_back(map);
			map.clear();
		}
	}
	if (map.empty() == false)
	{
        std::sort(map.begin(), map.end(), [] <size_t[3] x,<size_t[3] y) -> bool {return(x[0] < y[0]);});
		maps.push_back(map);
		map.clear();
	}
	return (maps);
}

// size_t    next_hop_value(map_t map, size_t seed)
// {
// 	size_t  next_hop = SIZE_MAX;
// 	long    diff = -1;

//     // std::cout << " --> " << seed;
// 	for (auto triple : map)      // the order is reversed! D=2, S=1, RANGE=0
// 	{
// 		if ((seed >= triple[1]) and (seed < triple[1] + triple[2]))
// 		{
// 			diff = triple[0] - triple[1];
// 			next_hop = seed + diff;
//             // std::cout << " --> " << next_hop;
// 			break;
// 		}
// 	}
// 	if (next_hop == SIZE_MAX)
// 		next_hop = seed;
// 	return (next_hop);
// }

// size_t  part2(char *file_name)
// {
// 	size_t 				min=SIZE_MAX, next_hop=SIZE_MAX, range=SIZE_MAX;
// 	std::string			line;
// 	size_t[3]	seeds;
// 	maps_t				maps;
// 	std::ifstream		inFile(file_name);
// 	if (!inFile.is_open())
// 		return (0);
// 	std::getline(inFile, line);
// 	seeds = get_numbers_line(line);
// 	std::reverse(seeds.begin(), seeds.end());
// 	maps = fill_maps(inFile);
// 	inFile.close();
// 	for (auto start=seeds.begin();start!=seeds.end();start++)
// 	{
//         range = *(++start);
//         for (size_t i=0; i<range; i++)
//         {
//             next_hop = *(start - 1) + i;
//             // std::cout << " start: " << next_hop << ' ';
//             for (map_t map: maps)
//                 next_hop = next_hop_value(map, next_hop);
//             if (min > next_hop)
//                 min = next_hop;
//             // std::cout << "\n";
//         }
// 	}
// 	return (min);
// }

size_t    next_hop_value(map_t map, size_t seed, size_t range)
{
	size_t  next_hop = SIZE_MAX;
	size_t[3] best = {0, 0, 0};
	for (auto item : map)
	{
		if ((seed + range < item[1]) or (seed > item[1] + item[2]))
			continue;
			
	}	
}

bool test(map_t map)
{
    size_t count = 0;
    for (auto item=map.begin(); item!=map.end();item++)
    {
        count += (*item)[2];
        if (((item + 1) != map.end()) and (count != (*(item + 1))[1]))
        {
            std::cout << count << ' ' << (*(item + 1))[1] << '\n';
            return (false);
        }
    }
    return (true);
}

size_t  part2(char *file_name)
{
	size_t 			min=SIZE_MAX;//, next_hop=SIZE_MAX;//, range=SIZE_MAX;
	std::string		line;
	size_t[3]		seeds;
	maps_t			maps;
	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	std::getline(inFile, line);
	seeds = get_numbers_line<20>(line);
	maps = fill_maps(inFile);
    for(auto a:maps)
    {
        for (auto b:a)
        {
            for(auto c:b)
                std::cout << c << ' ';
            std::cout << '\n';
        }
        std::cout << '\n';
    }
	inFile.close();
	// for (auto start=seeds.begin(); start!=seeds.end();)
	// {
        for (map_t map: maps)
        {
            if (test(map) == false)
            {
                std::cout << maps.size() <<" nop!\n";
                // return (1);
            }
        }
            // next_hop = next_hop_value(map, *start, *(start + 1));
    //     if (min > next_hop)
    //         min = next_hop;
    //     start += 2;
	// }
	return (min);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
