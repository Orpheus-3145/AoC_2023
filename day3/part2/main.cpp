#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

typedef std::vector< std::vector<char> > mtx;

mtx get_matrix(std::ifstream& fd)
{
    mtx matrix;
    std::string line;

    while (std::getline(fd, line))
        matrix.push_back(std::vector(line.begin(), line.end()));
    return(matrix);
}

int build_number(std::vector<char> str, size_t n_pos, int& n)
{
	int exp=0, count=0;
    n = 0;
	while (isdigit(str[n_pos]))
    {
		n += (str[n_pos] - '0') * pow(10, exp++);
        count++;
        if (n_pos > 0)
            n_pos--;
        else
            break;
    }
	return (count - 1);
}

int    find_prod(mtx& matrix, size_t i, size_t j)
{
    int n=0, cnt=0;
    if (((i > 0) and (j > 0) and isdigit(matrix[i - 1][j - 1])) or 
        ((i > 0) and isdigit(matrix[i - 1][j])) or 
        ((i > 0) and (j < matrix[i - 1].size() - 1) and isdigit(matrix[i - 1][j + 1])))
    {
        if (!isdigit(matrix[i - 1][j]))
        {
            if ((j > 0) and isdigit(matrix[i - 1][j - 1]))
            {
                cnt += build_number(matrix[i - 1], j - 1, n);
                while (cnt >= 0)
                    matrix[i - 1][j - cnt--] = '.';
                return (n);
            }
            else
            {
                j++;
                while ((j < matrix[i - 1].size() - 1) and (isdigit(matrix[i - 1][j + 1])))
                    j++;
                cnt += build_number(matrix[i - 1], j, n);
                while (cnt >= 0)
                    matrix[i - 1][j - cnt--] = '.';
                return (n);
            }
        }
        else
        {
            while ((j < matrix[i - 1].size() - 1) and (isdigit(matrix[i - 1][j + 1])))
                j++;
            cnt += build_number(matrix[i - 1], j, n);
            while (cnt >= 0)
                matrix[i - 1][j - cnt--] = '.';
            return (n);
        }
    }
    else if ((j > 0) and isdigit(matrix[i][j - 1]))
    {
        j--;
        cnt += build_number(matrix[i], j, n);
        while (cnt >= 0)
            matrix[i][j - cnt--] = '.';
        return (n);
    }
    else if ((j < matrix[i - 1].size() - 1) and isdigit(matrix[i][j + 1]))
    {
        j++;
        while ((j < matrix[i].size() - 1) and (isdigit(matrix[i][j + 1])))
            j++;
        cnt += build_number(matrix[i], j, n);
        while (cnt >= 0)
            matrix[i][j - cnt--] = '.';
        return (n);
    }
    else if (((i < matrix.size() - 1) and (j > 0) and isdigit(matrix[i + 1][j - 1])) or 
        ((i < matrix.size() - 1) and isdigit(matrix[i + 1][j])) or 
        ((i < matrix.size() - 1) and (j < matrix[i + 1].size() - 1) and isdigit(matrix[i + 1][j + 1])))
    {
        if (!isdigit(matrix[i + 1][j]))
        {
            if ((j > 0) and isdigit(matrix[i + 1][j - 1]))
            {
                cnt += build_number(matrix[i + 1], j - 1, n);
                while (cnt >= 0)
                    matrix[i + 1][j - cnt--] = '.';
                return (n);
            }
            else
            {
                j++;
                while ((j < matrix[i + 1].size() - 1) and (isdigit(matrix[i + 1][j + 1])))
                    j++;
                cnt += build_number(matrix[i + 1], j, n);
                while (cnt >= 0)
                    matrix[i + 1][j - cnt--] = '.';
                return (n);
            }
        }
        else
        {
            while ((j < matrix[i + 1].size() - 1) and (isdigit(matrix[i + 1][j + 1])))
                j++;
            cnt += build_number(matrix[i + 1], j, n);
            while (cnt >= 0)
                matrix[i + 1][j - cnt--] = '.';
            return (n);
        }
    }
    return (0);
}

size_t  part2(char *file_name)
{
    size_t          tot = 0;
    mtx             matrix;
    // int n1, n2;
    std::ifstream	inFile(file_name);

    if (!inFile.is_open())
		return (0);
    matrix = get_matrix(inFile);
    for (size_t i=0; i<matrix.size(); i++)
    {
        for (size_t j=0; j<matrix[i].size(); j++)
        {
            if (matrix[i][j] == '*')
            {
                // std::cout << i << " " << j << '\n';
                // n1 = find_prod(matrix, i, j);
                // std::cout <<n1<<'\n';
                // n2 = find_prod(matrix, i, j);
                // std::cout <<n2<<'\n';
                tot += find_prod(matrix, i, j) * find_prod(matrix, i, j);
            }
        }
    }
    return (tot);
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}
