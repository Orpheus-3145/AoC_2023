#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

typedef std::vector<std::string> input_t;

typedef struct point
{
    size_t y;
    size_t x;
} point_t;

size_t count_empty_gal(input_t const& input, point_t origin)
{
    size_t rows=0, cols=0;
    size_t i=0, j=0;
    point_t end;
    if (origin.x == input[origin[y]].size() - 1)
    {
        end.y = origin.y + 1;
        end.x = origin.x;
    }
    else
    {
        end.y = origin.y;
        end.x = origin.x + 1;
    }
    for (i=origin.y; i<end.y; i++)
    {
        j = 0;
        while ((j < input[i].size()) and (input[i][j] != '#'))
            j++;
        if (j == input[i].size())
            cols++;
    }
    for (j=origin.x; i<end.x; j++)
    {
        i = 0;
        while ((i < input.size()) and (input[i][j] != '#'))
            i++;
        if (i == input.size())
            rows++;
    }
    std::cout << "(" << origin.x << "; " << origin.y << ") - (" << end.x << "; " << end.y << ") " << rows << ' ' << cols << '\n';
    return (rows + cols);
}

size_t  find_dist_next(input_t const& input, point_t origin)
{
    size_t dist = 0;
    point_t start;
    start.x = origin.x;
    start.y = origin.y;
    for(; start.y<input.size(); start.y++)
    {
        for(; start.x<input[start.y].size(); start.x++)
        {
            if (input[start.y][start.x] == '#')
                dist += abs(start.y - origin.y) + abs(int(start.x) - int(origin.x)) + count_empty_gal(input, origin);
        }
        start.x=0;
    }
    return (dist);
}

size_t  count_dist(input_t const& input)
{
    size_t dist = 0;

    for(size_t i=0; i<input.size(); i++)
    {
        for(size_t j=0; j<input[i].size(); j++)
        {
            if (input[i][j] == '#')
                dist += find_dist_next(input, point_t{i, j});
        }
    }
    return (dist);
}

size_t  part1(char *file_name)
{
	std::string line;
    input_t input;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
		input.push_back(line);
    inFile.close();
    return (count_dist(input));
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
    return (0);
}
