#pragma once
#include "Move.h"
#include "Board.h"


struct Return_For_Move_Validation {
	bool usable_move;
	bool continue_searching;
	Move returned_move;

};

class LegalMovesGenerator
{

private:
	Enum_Utils enum_utils;
	std::vector<BoardPos> white_pawns_starting_pos;
	std::vector<BoardPos> black_pawns_starting_pos;

	bool test_legal_move_player_turn(Board test_board, Move move) const;
	
	std::vector<Move> get_legal_moves_rook(Board test_board, PieceName piece_name, BoardPos pos) const;


	std::vector<Move> get_legal_moves_across_file(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_legal_moves_across_rank(Board test_board, PieceName piece_name, BoardPos pos) const;
	//returns true if the answer is usable
	Return_For_Move_Validation if_legal_move_get_move(
		BoardPos source_pos, 
		BoardPos test_pos, 
		PieceName source_name, 
		PieceName test_name
	) const;

	std::vector<Move> add_moves_together(std::vector<Move> m1, std::vector<Move> m2) const;

public:
	LegalMovesGenerator();
	std::vector<Move> get_legal_moves(Board test_board, PieceName piece_name, BoardPos pos) const;
	//will test a move on a current board is a legal move
	//input must be just the move. ie e2e4
	bool test_legal_move(Board test_board, std::string move) const;

};

