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
	PieceType piece_type = enum_utils.get_type_from_name(piece_name);
	if (piece_type == PieceType::Pawn) {
		legal_moves = get_legal_moves_pawn(test_board, piece_name, starting_ID);
	}
	if (piece_type == PieceType::Knight) {
		legal_moves = get_legal_moves_knight(test_board, piece_name, starting_ID);
	}
	if (piece_type == PieceType::Bishop) {
		legal_moves = get_legal_moves_bishop(test_board, piece_name, starting_ID);
	}
	if (piece_type == PieceType::Rook) {
		legal_moves = get_legal_moves_rook(test_board, piece_name, starting_ID);
	}
	if (piece_type == PieceType::Queen) {
		legal_moves = get_legal_moves_queen(test_board, piece_name, starting_ID);
	}
	if (piece_type == PieceType::King) {
		legal_moves = get_legal_moves_king(test_board, piece_name, starting_ID);
	}
	
	return legal_moves;
}

std::vector<Move> BoardManager::get_legal_moves_bishop(Board test_board, PieceName piece_name, int starting_ID) const
{
	return std::vector<Move>();
}

std::vector<Move> BoardManager::get_legal_moves_rook(Board test_board, PieceName piece_name, int starting_ID) const
{
	return std::vector<Move>();
}

std::vector<Move> BoardManager::get_legal_moves_knight(Board test_board, PieceName piece_name, int starting_ID) const
{
	return std::vector<Move>();
}

std::vector<Move> BoardManager::get_legal_moves_pawn(Board test_board, PieceName piece_name, int starting_ID) const
{
	return std::vector<Move>();
}

std::vector<Move> BoardManager::get_legal_moves_queen(Board test_board, PieceName piece_name, int starting_ID) const
{
	std::vector<Move> legal_moves = get_legal_moves_bishop(test_board, piece_name, starting_ID);
	std::vector<Move> legal_moves_1 = get_legal_moves_rook(test_board, piece_name, starting_ID);
	legal_moves.insert(legal_moves.end(), legal_moves_1.begin(), legal_moves_1.end());
	return legal_moves;
}

std::vector<Move> BoardManager::get_legal_moves_king(Board test_board, PieceName piece_name, int starting_ID) const
{
	return std::vector<Move>();
}





