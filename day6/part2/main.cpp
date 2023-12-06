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


int	get_range(double time, double record)
{
	double min_r, max_r;
	int count = 0;

	min_r = (time - sqrt(pow(time, 2.) - 4. * record)) / 2. + 0.001;
	max_r = (time + sqrt(pow(time, 2.) - 4. * record)) / 2. - 0.001;
	for (count=0; count < max_r - ceil(min_r);count++);
	return (count);
}

int  part2(char *file_name)
{
	int prod = 1;
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
    prod *= get_range(timing, record);
	return (prod);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
