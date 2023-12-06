#include <fstream>
#include <iostream>
#include <cmath>

double    get_number(std::string line)
{
	double number = 0;
	int exp = 0;

	for (auto it=line.rbegin(); it!=line.rend();)
	{
		if (isdigit(*it))
            number += (*it++ - '0') * powl(10, exp++);
        else if (*it == ':')
            break;
		else
			it++;
	}
	return (number);
}

// the requirement is to find which n satisfies: (t - n) * n < r [t=timing, r=record];
// solving the second degree inequality in n we have that the valid n are the ones inside
// the open interval (x1, x2):
// x1 = (t - sqrt(t^2 - 4r)) / 2
// x2 = (t + sqrt(t^2 - 4r)) / 2
int	get_range(double time, double record)
{
	double min_r, max_r;

	min_r = (time - sqrt(pow(time, 2.) - 4. * record)) / 2.;
	max_r = (time + sqrt(pow(time, 2.) - 4. * record)) / 2.;
	return (ceil(max_r) - floor(min_r) - 1);
}

int  part2(char *file_name)
{
	std::string line;
	double timing, record;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	std::getline(inFile, line);
	timing = get_number(line);
	std::getline(inFile, line);
	record = get_number(line);
	inFile.close();
	return (get_range(timing, record));
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
