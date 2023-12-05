#! /bin/bash

MakefileContent=$'SHELL := /bin/bash

MAIN := main.cpp
SRC_P1 := part1
SRC_P2 := part2
MAIN_P1 := $(SRC_P1)/$(MAIN)
MAIN_P2 := $(SRC_P2)/$(MAIN)
PART1 := $(SRC_P1)/exe_part1
PART2 := $(SRC_P2)/exe_part2
INPUT := input_file

PP := c++
PP_FLAGS := -Wall -Wextra -Werror -Wshadow -Wpedantic -g3 -fsanitize=address
''
GREEN = \\''x1b[32;01m
RED = \\''x1b[31;01m
RESET = \\''x1b[0m

all: $(PART1) $(PART2)

$(PART1): $(MAIN_P1)
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(MAIN_P1) -o $(PART1)
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\\''n"

$(PART2): $(MAIN_P2)
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(MAIN_P2) -o $(PART2)
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\\''n"

part1: $(PART1)
	@clear
	@./$(PART1) $(INPUT)

part2: $(PART2)
	@clear
	@./$(PART2) $(INPUT)

run: all
	@clear
	@./$(PART1) $(INPUT)
	@./$(PART2) $(INPUT)

clean:
	@rm -f $(PART1)
	@printf "(Advent of Code) $(RED)Removed program $(PART1)$(RESET)\\n"
	@rm -f $(PART2)
	@printf "(Advent of Code) $(RED)Removed program $(PART2)$(RESET)\\n"

re: clean all

.PHONY: re clean all part1 part2 run'

mainContent1=$'#include <fstream>
#include <iostream>
#include <string>

size_t  part1(char *file_name)
{
    size_t tot = 0;
    std::string line;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    while (std::getline(inFile, line))
    {
        // ...
    }
    inFile.close();
    return (tot);
}
''
int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part1: " << part1(argv[1]) <<  "\n" ;
    return (0);
}'

mainContent2=$'#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

size_t  part2(char *file_name)
{
    size_t tot = 0;
    std::string line;

    std::ifstream	inFile(file_name);
    if (!inFile.is_open())
		return (0);
    while (std::getline(inFile, line))
    {
        // ...
    }
    return (tot);
}
''
int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << "tot part2: " << part2(argv[1]) <<  "\n" ;
    return (0);
}'

newFolder=day$1

mkdir $newFolder
cd $newFolder
touch $newFolder.txt Makefile input_file
echo "$MakefileContent" > Makefile

PART=1
mkdir part$PART
cd part$PART
touch main.cpp
echo "$mainContent1" >main.cpp 

PART=2
cd ..
mkdir part$PART
cd part$PART
touch main.cpp 
echo "$mainContent2" >main.cpp 