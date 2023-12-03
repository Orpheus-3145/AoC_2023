#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string symbols = "*+=$%#@&/-";
typedef std::vector< std::vector<char> > mtx;

mtx get_matrix(std::ifstream& fd)
{
    mtx matrix;
    std::string line;

    while (std::getline(fd, line))
        matrix.push_back(std::vector(line.begin(), line.end()));
    return(matrix);
}

bool    check_surround(mtx matrix, size_t i, size_t j)
{
    if ((i > 0) and (symbols.find(matrix[i - 1][j]) != std::string::npos))
        return (true);
    else if ((i < matrix.size() - 1) and (symbols.find(matrix[i + 1][j]) != std::string::npos))
        return (true);
    else if ((j < matrix[i].size() - 1) and (symbols.find(matrix[i][j + 1]) != std::string::npos))
        return (true);
    else if ((j > 0) and (symbols.find(matrix[i][j - 1]) != std::string::npos))
        return (true);
    else if ((i < matrix.size() - 1) and (j < matrix[i].size() - 1) and (symbols.find(matrix[i + 1][j + 1]) != std::string::npos))
        return (true);
    else if ((i > 0) and (j > 0) and (symbols.find(matrix[i - 1][j - 1]) != std::string::npos))
        return (true);
    else if ((i > 0) and (j < matrix[i].size() - 1) and (symbols.find(matrix[i - 1][j + 1]) != std::string::npos))
        return (true);
    else if ((i < matrix.size() - 1) and (j > 0) and (symbols.find(matrix[i + 1][j - 1]) != std::string::npos))
        return (true);
    else
        return (false);
}

size_t  part1(char *file_name)
{
    size_t tot = 0;
    std::string number;
    bool isOk = false;
    mtx matrix;
    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    matrix = get_matrix(inFile);
    for (size_t i=0; i<matrix.size(); i++)
    {
        for (size_t j=0; j<matrix[i].size(); j++)
        {
            number.clear();
            isOk = false;
            while ((j<matrix[i].size()) and isdigit(matrix[i][j]))
            {
                if ((isOk == false) and (check_surround(matrix, i, j) == true))
                    isOk = true;
                number += matrix[i][j];
                j++;
            }
            if (isOk)
            {
                // std::cout << number << '\n';
                tot += std::stol(number.c_str());
            }
        }
    }
    return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
    return (0);
}
