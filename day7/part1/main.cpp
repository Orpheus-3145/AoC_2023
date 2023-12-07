#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

typedef std::pair<std::string,int> item_t;

int count_occ(std::string hand)
{
	size_t	start = 0;
	int 	count = -1;
	char	check = hand[0];
	do
	{
		count++;
		start = hand.find(check, start + 1);
	} while (start != std::string::npos);
	if (count == 1)			// couple
		count = 2;
	else if (count == 2)	// triple
		count = 5;
	else if (count == 3)	// quadruple
		count = 8;
	else if (count == 4)	// quintuple
		count = 9;
	return (count);
}

std::string get_filter(std::string hand)
{
	std::string filter;
	char check = hand[0];
	for (char l : hand)
	{
		if (l != check)
			filter += l;
	}
	return (filter);
}

int find_order(std::string hand)
{
	if (hand.empty() == true)
		return (0);
	else
		return (count_occ(hand) + find_order(get_filter(hand)));
}

bool	custom_sort(item_t i1, item_t i2)
{
	size_t	ord1 = find_order(i1.first);
	size_t	ord2 = find_order(i2.first);
	int i = 0;

	while ((ord1 == ord2) and (i < 5))
	{
		ord1 = std::string("23456789TJQKA").find(i1.first[i]);
		ord2 = std::string("23456789TJQKA").find(i2.first[i]);
		i++;
	}
	return (ord1 < ord2);
}

std::vector<item_t> fill_hands(std::ifstream&	inFile)
{
	std::string line;
	int n = 0, exp=0, i=0;
	std::vector<item_t> hands;
	char hand[6];
	while (std::getline(inFile, line))
	{
		i=line.size() - 1;
		n = 0;
		exp = 0;
		memset(hand, 0, 6);
		while (isdigit(line[i]))
			n += (line[i--] - '0') * powl(10, exp++);
		while (i-- > 0)
			hand[i] = line[i];
		hands.push_back(std::make_pair(std::string(hand), n));
	}
	return (hands);
}


size_t  part1(char *file_name)
{
	size_t      tot = 0;
	std::vector<item_t> hands;

	std::ifstream	inFile(file_name);
	if (!inFile.is_open())
		return (0);
	hands = fill_hands(inFile);
	inFile.close();
	std::sort(hands.begin(), hands.end(), custom_sort);
	for (size_t i=0; i<hands.size(); i++)
		tot += hands[i].second * (i + 1);
	return (tot);
}

int main( int argc, char **argv)
{
	if (argc != 2)
		return (1);
	std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
	return (0);
}
