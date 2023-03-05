#pragma once
#include "Board.h"
#include "Move.h"




class BoardManager {
private:
	const std::string new_game_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Board current_board;
	Enum_Utils enum_utils;
	
	// 0----------------------------0
	// |	Legal Move Generation	|
	// 0----------------------------0
	bool test_legal_move_player_turn(Board test_board, Move move) const;
	std::vector<Move> get_legal_moves       (Board test_board, PieceName piece_name, int starting_ID) const;
	/*std::vector<Move> get_legal_moves_bishop(Board test_board, PieceName piece_name, int starting_ID) const;
	std::vector<Move> get_legal_moves_rook  (Board test_board, PieceName piece_name, int starting_ID) const;
	std::vector<Move> get_legal_moves_knight(Board test_board, PieceName piece_name, int starting_ID) const;
	std::vector<Move> get_legal_moves_pawn  (Board test_board, PieceName piece_name, int starting_ID) const;
	std::vector<Move> get_legal_moves_queen (Board test_board, PieceName piece_name, int starting_ID) const;
	std::vector<Move> get_legal_moves_king  (Board test_board, PieceName piece_name, int starting_ID) const;
*/




public:
	BoardManager();
	void start_new_game();
	//this will change current board to input fen string
	void start_new_game_FEN(std::string FEN);
	//Returns a copy of the current board
	Board copy_current_board() const { return current_board; }
	void flip_turn_current_board() { current_board.flip_side_to_move();	}

	//will test a move on a current board is a legal move
	//input must be just the move. ie e2e4
	bool test_legal_move(Board test_board, std::string move) const;
};

