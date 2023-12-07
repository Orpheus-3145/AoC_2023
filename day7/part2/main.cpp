#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>

typedef std::pair<std::string,size_t> item_t;

int count_occ(std::string hand, char check)
{
	size_t	pos = hand.find(check);
	int 	count = 0;

	while (pos != std::string::npos)
	{
		count++;
		pos = hand.find(check, pos + 1);
	}
	return (count);
}

int mapt( int count)
{
	if (count == 2)			// couple
		return(2);
	else if (count == 3)	// triple
		return(5);
	else if (count == 4)	// quadruple
		return(8);
	else if (count == 5)	// quintuple
		return(9);
	else
		return (0);
}

std::string get_filter(std::string hand, char check)
{
	std::string filter;

	for (char l : hand)
	{
		if (l != check)
			filter += l;
	}
	return (filter);
}

int find_order(std::string hand)
{
	std::multiset<int>	maxs;
	std::multiset<int>::const_iterator last;
	std::string 	filter = get_filter(hand, 'J');
	int				tot=0, max=0, jcount=0;

	do
	{
		maxs.insert(count_occ(filter, filter[0]));
		filter = get_filter(filter, filter[0]);
	}
	while (filter.empty() == false);
	jcount = count_occ(hand, 'J');
	if (jcount > 0)
	{
		last = maxs.end();
		max = *(--last);
		maxs.erase(last);
		maxs.insert(max + jcount);
	}
	for (auto item : maxs)
		tot += mapt(item);
	return (tot);
}

bool	custom_sort(item_t i1, item_t i2)
{
	int i = 0;
	size_t ord1 = find_order(i1.first);
	size_t ord2 = find_order(i2.first);
	while ((ord1 == ord2) and (i < 5))
	{
		ord1 = std::string("J23456789TQKA").find(i1.first[i]);
		ord2 = std::string("J23456789TQKA").find(i2.first[i]);
		i++;
	}
	return (ord1 < ord2);
}

std::vector<item_t> fill_hands(std::ifstream&	inFile)
{
	std::string line;
	int exp=0, i=0;
	size_t n = 0;
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

size_t  part2(char *file_name)
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
	std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
	return (0);
}
