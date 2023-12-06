#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

int build_number(std::string::reverse_iterator& n_pos, std::string::reverse_iterator end)
{
	int n = 0, exp=0;
	while ((n_pos != end) and isdigit(*n_pos))
		n += (*n_pos++ - '0') * powl(10, exp++);
	return (n);
}

std::vector<int>    get_numbers(std::string line)
{
	std::vector<int> numbers;

	for (auto it=line.rbegin(); it!=line.rend();)
	{
		if (isdigit(*it))
			numbers.push_back(build_number(it, line.rend()));
		else
			it++;
	}
	std::reverse(numbers.begin(), numbers.end());
	return (numbers);
}

// the requirement is to find which n satisfies: (t - n) * n < r [t=timing, r=record];
// solving the second degree inequality in n we have that the valid n are the ones inside
// the open interval (x1, x2):
// x1 = (t - sqrt(t^2 - 4r)) / 2
// x2 = (t + sqrt(t^2 - 4r)) / 2
int	get_range(double time, double record)
{
	double min_r, max_r;
	int count = 0;

	min_r = (time - sqrt(pow(time, 2.) - 4. * record)) / 2. + 0.00001;	// + and - 0.00001 to have the open interval
	max_r = (time + sqrt(pow(time, 2.) - 4. * record)) / 2. - 0.00001;
	for (count=0; count < max_r - ceil(min_r);count++);
	return (count);
}

int  part1(char *file_name)
{
	int prod = 1;
	std::string line;
	std::vector<int> timings, records;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	std::getline(inFile, line);
	timings = get_numbers(line);
	std::getline(inFile, line);
	records = get_numbers(line);
	inFile.close();
	for (size_t i=0; i< timings.size(); i++)
		prod *= get_range(timings[i], records[i]);
	return (prod);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
	return (0);
}
