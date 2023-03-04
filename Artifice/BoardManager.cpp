#include "BoardManager.h"


BoardManager::BoardManager() {

}

void BoardManager::start_new_game() {
	start_new_game_FEN(new_game_FEN);
}

void BoardManager::start_new_game_FEN(std::string FEN) {
	current_board = Board(FEN);
}

bool BoardManager::test_legal_move(Board test_board, std::string move) const
{
	/*
	* Order of Opperations
	* 01 - Test if start of move matches who's turn it is
	* 02 - Get Legal Moves for Piece
	* 03 - Check if ending location is in returned legal moves 
	*/

	Move test_move = Move(move);
	// Step 01
	if (!test_legal_move_player_turn(test_board, test_move)) { return false; }

	// Step 02
	PieceName piece_name = test_board.get_piece_at(test_move.get_starting_board_ID());
	std::vector<Move> legal_moves = get_legal_moves(test_board, piece_name, test_move.get_starting_board_ID());

	return true;
}


bool BoardManager::test_legal_move_player_turn(Board test_board, Move move_to_test) const {

	//get who's turn it is 
	PieceColor whos_turn = current_board.get_side_to_move();
	Bitboard color_side = current_board.get_copy_side_bitboard(whos_turn);
	return color_side.bb.test(move_to_test.get_starting_board_ID());

}

std::vector<Move> BoardManager::get_legal_moves(Board test_board, PieceName piece_name, int starting_ID) const
{
	std::vector<Move> legal_moves;





	return legal_moves;
}





