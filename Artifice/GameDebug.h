#pragma once
#include<string>
#include <iostream>
#include <vector>
#include "BoardManager.h"


class GameDebug
{

private:
	
	BoardManager board_manager;

	//Call during class construction or debug startup, print directions
	void print_opening_text() const;

	void print_help() const;

public:
	std::string line; //string caught from the cli
	PieceColor side_to_move = PieceColor::White;
	bool white_king_castle = false;
	bool white_queen_castle = false;
	bool black_king_castle = false;
	bool black_queen_castle = false;

	//Constructor
	GameDebug();
	//Loop the debugger will run through to play a game via CLI
	void game_debug_loop();
	//Does what it says on the tin, prints current board state
	void print_board(Board board_to_print) const;
	//will take in a intager representing the piece
	//will return the string representation of the piece or ' ' for none. 
	std::string piece_to_string(PieceName p) const;


	int get_board_ID(int r, int f) const {
		return r * 8 + f;
	}

};

