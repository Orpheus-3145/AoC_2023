#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

typedef struct node
{
    int n_inst;
    std::vector<int> winners;
    std::vector<int> potentials;
} node_t;

int build_number(std::string str, int pos, int& n)
{
    int cnt=0, exp=0;

    while (isdigit(str[pos]))
    {
        cnt++;
        n += (str[pos--] - '0') * pow(10,exp++);
    }
    return (cnt);
}

std::vector<int>    get_numbers(std::string line)
{
    std::vector<int> numbers;
    int n;
    for(int it=line.size() - 1; it>=0;)
    {
        if (isdigit(line[it]))
        {
            n=0;
            it -= build_number(line, it, n);
            numbers.push_back(n);
        }
        else
            it--;
    }
    return (numbers);
}

int find_winners(std::vector<int>& winners, std::vector<int>& potentials)
{
    int count=0;

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
    return (count);
}

void build_struct(std::ifstream& fd,std::vector<node_t>& nodes)
{
    node_t              node;
    int semi_c_pos=0, pipe_pos=0;
    std::string line;

    while (std::getline(fd, line))
    {
        semi_c_pos = line.find(':') - 1;
        pipe_pos = line.find('|');
        node.n_inst = 1;
        node.winners = get_numbers(line.substr(semi_c_pos + 1, pipe_pos - semi_c_pos - 2));
        node.potentials = get_numbers(line.substr(pipe_pos + 1));
        nodes.push_back(node);
    }
}

int  part2(char *file_name)
{
    int tot = 0, wins=0;
    std::vector<node_t> nodes;
    std::ifstream	inFile(file_name);
    std::vector<node_t>::iterator tmp;
    if (!inFile.is_open())
		return (0);
    build_struct(inFile, nodes);
    inFile.close();
    for(auto node=nodes.begin(); node!=nodes.end();)
    {
        wins = find_winners((*node).winners, (*node).potentials);
        tot += (*node).n_inst;
        tmp = node + 1;
        while ((wins-- > 0) and (tmp != nodes.end()))
            (*tmp++).n_inst += (*node).n_inst;
        node++;
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
