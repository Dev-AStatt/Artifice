#include "Move.h"

/*
Move format:
------------

The move format is in long algebraic notation.
A nullmove from the Engine to the GUI should be sent as 0000.
Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)

*/

Move::Move(std::string standard_notation) : standard_notation(standard_notation) {
	//make sure the move is valid before trying to construct everything
	if (!move_sanitization(standard_notation)) { throw std::invalid_argument("Tried to create a move form invalid string"); }

	if (standard_notation.length() == 4) {
		non_event_move(standard_notation);
	}
	if (standard_notation.length() == 5) {
		event_move(standard_notation);
	}



}

bool Move::move_sanitization(std::string standard_notation) const {
	if (standard_notation.length() > 5) { return false; }
	if (standard_notation.length() < 4) { return false; }
	return true;
}

void Move::non_event_move(std::string standard_notation) {
	starting = BoardPos(standard_notation.substr(0, 2));
	ending = BoardPos(standard_notation.substr(2, 4));
}

void Move::event_move(std::string standard_notation) {
	starting = BoardPos(standard_notation.substr(0, 2));
	ending = BoardPos(standard_notation.substr(3, 5));
}







