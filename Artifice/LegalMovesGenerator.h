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
	std::vector<std::pair<int, int>> knight_move_table; //rank, file

	bool is_move_right_player(Board test_board, Move move) const;
	
	std::vector<Move> get_moves_rook(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_bishop(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_queen(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_pawn(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_knight(Board test_board, PieceName piece_name, BoardPos pos) const;
	


	std::vector<Move> get_moves_across_file(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_across_rank(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_across_rising_diag(Board test_board, PieceName piece_name, BoardPos pos) const;
	std::vector<Move> get_moves_across_decend_diag(Board test_board, PieceName piece_name, BoardPos pos) const;

	//you can pass a source and a test and method will check
	// 01 - Is test point on the same team as source?
	// 02 - Is test point empty?
	// 03 - Is test point a capture? what kind?
	//[Return] a struct containing metidata on result, like is the move returned
	//usable or not, and if you can continue your search after adding move to vector of legal moves. 
	Return_For_Move_Validation if_endpoint_legal_get_move(
		Board test_board,
		BoardPos source_pos, 
		BoardPos test_pos, 
		PieceName source_name 
		
	) const;

	std::vector<Move> add_moves_together(std::vector<Move> m1, std::vector<Move> m2) const;

	bool is_in_board_pos_vec(BoardPos pos, std::vector<BoardPos> vect) const;

	bool is_pawn_starting_position(PieceColor color, BoardPos pos) const;

	bool will_king_be_in_check(Board test_board, Move test_move) const {

		return false;
	}


public:
	LegalMovesGenerator();
	std::vector<Move> get_legal_moves(Board test_board, PieceName piece_name, BoardPos pos) const;
	//will test a move on a current board is a legal move
	//input must be just the move. ie e2e4
	bool test_legal_move(Board test_board, std::string move) const;

};

