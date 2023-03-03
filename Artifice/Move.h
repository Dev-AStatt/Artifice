#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "cEnums.h"

class Move {
private:
	PieceName name;
	std::string const standard_notation;
	int starting_board_ID;
	int ending_board_ID;
	//Method will take in a string and make sure the input is
	//sanitized before constructing the class with it. 
	bool move_sanitization(std::string standard_notation) const;

	void non_event_move(std::string standard_notation);

	void event_move(std::string standard_notation);

	int string_coordinate_to_board_ID(std::string single_coord) const;

public:
	Move(std::string move_string);

	std::string get_standard_notation() const { return standard_notation; }
	PieceName get_piece_name() const { return name; }
	int get_starting_board_ID() const { return starting_board_ID; }
	int get_ending_board_ID() const { return ending_board_ID; }




};

