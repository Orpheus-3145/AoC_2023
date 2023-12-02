SHELL := /bin/bash

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

GREEN = \x1b[32;01m
RED = \x1b[31;01m
RESET = \x1b[0m

all: $(PART1) $(PART2)

$(PART1): $(MAIN_P1)
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(MAIN_P1) -o $(PART1)
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\n"

$(PART2): $(MAIN_P2)
	@$(PP) $(PP_FLAGS) $(DEBUG_FLAGS) $(MAIN_P2) -o $(PART2)
	@printf "(Advent of Code) $(GREEN)Created program $@$(RESET)\n"

part1: $(PART1)
	@clear
	@./$(PART1) $(SRC_P1)/$(INPUT)

part2: $(PART2)
	@clear
	@./$(PART2) $(SRC_P2)/$(INPUT)

run: all
	@clear
	@./$(PART1) $(SRC_P1)/$(INPUT)
	@./$(PART2) $(SRC_P2)/$(INPUT)

clean:
	@rm -f $(PART1)
	@printf "(Advent of Code) $(RED)Removed program $(PART1)$(RESET)\n"
	@rm -f $(PART2)
	@printf "(Advent of Code) $(RED)Removed program $(PART2)$(RESET)\n"

re: clean all

.PHONY: re clean all part1 part2 run