#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef struct node
{
    std::string name;
    std::string left;
    std::string right;
} node_t;

typedef std::unordered_map<std::string, node_t> umap_t;

void fill_nodes_seq(std::ifstream& fd, umap_t& nodes, std::string seq )
{
    std::string line;
    node_t new_node;

    std::getline(fd, line);
    for (char l : line)
    {
        if (std::string("LR").find(l) != std::string::npos)
            seq += l;
    }
    while (std::getline(fd, line))
    {
        new_node.name = line.substr(0, 3);
        new_node.left = line.substr(7, 3);
        new_node.right = line.substr(12, 3);
        nodes.insert(make_pair(new_node.name, new_node));
    }
}

size_t find_end(umap_t& nodes, std::string seq)
{
    size_t count=0, i=0, max_size=seq.size();
    node_t current = nodes["AAA"];

    while (current.name != "ZZZ")
    {
        if (seq[i] == 'L')
            current = nodes[current.left];
        else if (seq[i] == 'R')
            current = nodes[current.right];
        count++;
        i = (i + 1) % max_size;
    }
    return (count);
}

size_t  part1(char *file_name)
{
    std::string seq;
    umap_t nodes;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    std::getline(inFile, seq);
    fill_nodes_seq(inFile, nodes, seq);
    inFile.close();
    return (find_end(nodes, seq));
}

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
    return (0);
}
