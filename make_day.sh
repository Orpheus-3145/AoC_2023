#! /bin/bash

newFolder=day$1

MakefileContent='SHELL := /bin/bash\n\n
SRC_P1 := part1\n
SRC_P2 := part2\n
SOURCES_P1 := $(wildcard $(SRC_P1)/*.cpp)\n
HEADERS_P1 := $(wildcard $(SRC_P1)/*.hpp)\n
SOURCES_P2 := $(wildcard $(SRC_P2)/*.cpp)\n
HEADERS_P2 := $(wildcard $(SRC_P2)/*.hpp)\n
PART1 := $(SRC_P1)/exe_part1\n
PART2 := $(SRC_P2)/exe_part2\n
INPUT := input_file\n\n
PP := c++\n
PP_FLAGS := -Wall -Wextra -Werror -Wshadow -Wpedantic -g3 -fsanitize=address\n
\n
GREEN = \x1b[32;01m\n
RED = \x1b[31;01m\n
RESET = \x1b[0m\n
\n
all: $(PART1) $(PART2)\n
\n
$(PART1): $(SOURCES_P1) $(HEADERS_P1)\n
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(SOURCES_P1) -o $(PART1)\n
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\n"\n
\n
$(PART2): $(SOURCES_P2) $(HEADERS_P2)\n
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(SOURCES_P2) -o $(PART2)\n
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\n"\n
\n
part2: $(PART2)\n
	@clear\n
	@./$(PART2) input_file\n
\n
part1: $(PART1)\n
	@clear\n
	@./$(PART1) input_file\n
\n
run: all\n
	@clear\n
	@./$(PART1) input_file\n
	@./$(PART2) input_file\n
\n
clean:\n
	@rm -f $(PART1)\n
	@printf "(Advent of Code) $(RED)Removed program $(PART1)$(RESET)\n"\n
	@rm -f $(PART2)\n
	@printf "(Advent of Code) $(RED)Removed program $(PART2)$(RESET)\n"\n
\n
re: clean all'

mainContent="#include \"part$PART.hpp\"
#include <iostream>

int main( int argc, char **argv)
{
    if (argc != 2)
        return (1);
    std::cout << \"tot $PART: \" << $PART(argv[1]) << '\n';
    return (0);
}"

headerContent="#pragma once
#include <cstddef>

size_t  $PART(char *file_name);"

implContent="#include \"$PART.hpp\"

size_t  $PART(char *file_name)
{
    
}"
mkdir $newFolder
cd $newFolder
touch $newFolder.txt Makefile input_file
echo $MakefileContent > Makefile

mkdir part1
cd part1
touch main.cpp part1.cpp part1.hpp
PART=1
# filling header
echo $MakefileContent >main.cpp

# filling implementation
echo $mainContent >part1.cpp

# filling main
echo $implContent >part1.hpp

cd ..
mkdir part2
cd part2
touch main.cpp part2.cpp part2.hpp
PART=2
# filling header
echo $MakefileContent >main.cpp

# filling implementation
echo $mainContent >part1.cpp

# filling main
echo $implContent >part1.hpp