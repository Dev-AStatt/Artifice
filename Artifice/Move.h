#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "cEnums.h"
#include "BoardPos.h"

class Move {
private:
	PieceName name;
	std::string const standard_notation;
	BoardPos starting;
	BoardPos ending;
	//Method will take in a string and make sure the input is
	//sanitized before constructing the class with it. 
	bool move_sanitization(std::string standard_notation) const;

	void non_event_move(std::string standard_notation);

	void event_move(std::string standard_notation);

	

public:
	Move(std::string move_string);

	std::string get_standard_notation() const { return standard_notation; }
	PieceName get_piece_name() const { return name; }
	BoardPos get_starting() const { return starting; }
	BoardPos get_ending() const { return ending; }




};

