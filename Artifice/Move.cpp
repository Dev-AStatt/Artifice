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
	starting_board_ID = string_coordinate_to_board_ID(standard_notation.substr(0, 2));
	ending_board_ID = string_coordinate_to_board_ID(standard_notation.substr(2, 4));
}

void Move::event_move(std::string standard_notation) {

}

//Simple multiplication function for repeted 2d to 1d conversion
int get_board_ID(int rank, int file) { return rank * 8 + file; }

int Move::string_coordinate_to_board_ID(std::string single_coord) const {
	int file = 0; // Letters a, b, c, d, e, f, g, h
	int rank = 0; // Numbers 1, 2, 3, 4, 5, 6, 7, 8
	
	char c = single_coord[0];
	if (0 <= int(c) - 97 <= 7) {
		file = int(c) - 97; 
	} //int(char) will get us the intager value of the letter, then subtract 97 to get the number
	else { std::cout << "First char from string read incorrectly" + c << std::endl; }

	c = single_coord[1];
	if (c >= 49 && c <= 56) {
		rank = 8 - std::atoi(&c); 
	}
	else { std::cout << "Second char from string read incorrectly" + c << std::endl; }

	return get_board_ID(rank, file);

}


