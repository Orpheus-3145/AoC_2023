#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

std::vector<int>    get_numbers(std::string line)
{
    int n=0, exp=0;
    std::vector<int> numbers;
    for(int i=line.size()-1; i>=0;)
    {
        if (isdigit(line[i]))
        {
            n = 0;
            exp = 0;
            while (isdigit(line[i]))
                n += (line[i--] - '0') * pow(10,exp++);
            numbers.push_back(n);
        }
        else
            i--;
    }
    return (numbers);
}

int find_winners(std::string line)
{
    int count=0;
    size_t semi_c_pos = line.find(':'), pipe_pos = line.find('|');
    std::vector<int> winners = get_numbers(line.substr(semi_c_pos + 1, pipe_pos - semi_c_pos - 2));
    std::vector<int> potentials = get_numbers(line.substr(pipe_pos + 1));

    for (auto win : winners)
    {
        for (auto pot : potentials)
        {
            if (win == pot)
            {
                count++;
                break ;
            }
        }
    }
    if (count < 2)
        return (count);
    else
        return (pow(2, count - 1));
}

size_t  part1(char *file_name)
{
    size_t tot = 0;
    std::string line;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    while (std::getline(inFile, line))
        tot += find_winners(line);
    return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
    return (0);
}
