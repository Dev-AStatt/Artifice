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
	Board get_current_board() const { return current_board; }

};

