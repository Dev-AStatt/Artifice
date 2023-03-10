#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "cEnums.h"
#include "BoardPos.h"


enum class MoveType {
	Capture,
	Castle,
	EnPassant,
	Promotion,
	Check,
	Normal,
	DoublePawnPush,
};

class Move {
private:
	std::string standard_notation;
	BoardPos starting;
	BoardPos ending;
	MoveType type;
	//Method will take in a string and make sure the input is
	//sanitized before constructing the class with it. 
	bool move_sanitization(std::string standard_notation) const;

	void non_event_move(std::string standard_notation);

	void event_move(std::string standard_notation);

	void build_standard_notation();

public:
	Move(std::string move_string);
	Move(BoardPos starting, BoardPos ending, MoveType type);

	std::string get_standard_notation() const { return standard_notation; }
	MoveType get_move_type() const { return type; }
	BoardPos get_starting() const { return starting; }
	BoardPos get_ending() const { return ending; }




};

