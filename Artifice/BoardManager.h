#pragma once
#include "Board.h"




class BoardManager {
private:
	const std::string new_game_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Board current_board;

public:
	BoardManager();


	void start_new_game();
	//this will change current board to input fen string
	void start_new_game_FEN(std::string FEN);
	//Returns a copy of the current board
	Board copy_current_board() const { return current_board; }
	//will test a move on a current board is a legal move
	//input must be just the move. ie e2e4
	bool test_legal_move(Board& current_board, std::string move) const;

};

