#pragma once
#include<string>
#include <iostream>
#include <vector>
#include "Board.h"
#include "cEnums.h"

class GameDebug
{

private:
	
	Board game_board;

public:
	std::string line; //string caught from the cli
	PieceName side_to_move = PieceName::White;
	bool white_king_castle = false;
	bool white_queen_castle = false;
	bool black_king_castle = false;
	bool black_queen_castle = false;

	//Constructor
	GameDebug();
	//Loop the debugger will run through to play a game via CLI
	void game_debug_loop();
	//Does what it says on the tin, prints current board state
	void print_board() const;
	//will take in a intager representing the piece
	//will return the string representation of the piece or ' ' for none. 
	std::string piece_to_string(PieceName p) const;


};

