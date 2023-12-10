#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


typedef std::vector<std::string> input_t;
typedef struct point
{
	size_t x;
	size_t y;
} point_t;

bool operator==(point_t const& a, point_t const& b)
{
	return ((a.x == b.x) and (a.y == b.y));
}

bool operator!=(point_t const& a, point_t const& b)
{
	return (! operator==(a, b));
}

bool is_valid(const char *str, char check)
{
	return (std::string(str).find(check) != std::string::npos);
}

void move_to(input_t input, point_t& curr, point_t& prev)
{
	point_t next = curr;

	if (input[curr.y][curr.x] == '-')
	{
		if (curr.x > prev.x)
			next.x += 1;
		else
			next.x -= 1;
	}
	else if (input[curr.y][curr.x] == '|')
	{
		if (curr.y > prev.y)
			next.y += 1;
		else
			next.y -= 1;
	}
	else if (input[curr.y][curr.x] == 'L')
	{
		if (curr.y > prev.y)
			next.x += 1;
		else
			next.y -= 1;
	}
	else if (input[curr.y][curr.x] == 'J')
	{
		if (curr.y > prev.y)
			next.x -= 1;
		else
			next.y -= 1;
	}
	else if (input[curr.y][curr.x] == 'F')
	{
		if (curr.y < prev.y)
			next.x += 1;
		else
			next.y += 1;
	}
	else if (input[curr.y][curr.x] == '7')
	{
		if (curr.y < prev.y)
			next.x -= 1;
		else
			next.y += 1;
	}
	prev = curr;
	curr = next;
}

point_t find_next(input_t input, point_t start, point_t ignore)
{
	point_t check = start;

	if ((start.x > 0) and (point_t{start.x - 1, start.y} != ignore) and is_valid("-LF", input[start.y][start.x - 1]))
		check.x -= 1;
	else if ((start.y > 0) and (point_t{start.x, start.y - 1} != ignore) and is_valid("|7F", input[start.y - 1][start.x]))
		check.y -= 1;
	else if ((start.x < input[start.y].size() - 1) and (point_t{start.x + 1, start.y} != ignore) and is_valid("-7J", input[start.y][start.x + 1]))
		check.x += 1;
	else if ((start.y < input.size() - 1) and (point_t{start.x, start.y + 1} != ignore) and is_valid("|JL", input[start.y + 1][start.x]))
		check.y += 1;
	return (check);
}

void setup_start( input_t input, point_t& start, point_t& front, point_t& reverse )
{
	for (start.y=0; start.y<input.size(); start.y++)
	{
		for (start.x=0; start.x<input[start.y].size(); start.x++)
		{
			if (input[start.y][start.x] == 'S')
			{
				// std::cout << "start: (" << start.y << ", " <<start.x << ")\n";
				front = find_next(input, start, point_t{0, 0});
				reverse = find_next(input, start, front);
				return;
			}
		}
	}
}

size_t  count_half_way(input_t input)
{
	size_t count = 1;
	point_t start, curr_f, curr_r, next_f, next_r;

	setup_start(input, start, next_f, next_r);
	curr_f = start;
	curr_r = start;
	// std::cout << "start: (" << start.y << ", " <<start.x << ")\n";
	while ((next_f != next_r) or ((curr_f == next_r) and (curr_r == next_f)))
	{
		std::cout << "front: (" << curr_f.y << ", " <<curr_f.x << ")\t rev: (" << curr_r.y << ", " << curr_r.x << ")\n";
		move_to(input, next_f, curr_f);
		move_to(input, next_r, curr_r);
		count++;
	}
	return (count);
}

size_t  part2(char *file_name)
{
	size_t tot = 0;
	std::string line;
	input_t input;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	while (std::getline(inFile, line))
		input.push_back(line);
	inFile.close();
	tot = count_half_way(input);
	return (tot);
}


int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
