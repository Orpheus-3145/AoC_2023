#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


void fill_matrix(std::ifstream& fd, std::vector<std::vector<size_t> >& input)
{
	std::string line;
	std::vector<size_t> new_row;
	size_t n;

	while (std::getline(fd, line))
	{
		std::istringstream iss(line);
		while( iss >> n)
			new_row.push_back(n);
		input.push_back(new_row);
		new_row.clear();
	}
}
size_t  part2(char *file_name)
{
    size_t tot = 0;
    std::vector<std::vector<size_t> > input;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    fill_matrix(inFile, input);
    inFile.close();

    // ...

    return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
