#include "LegalMovesGenerator.h"



LegalMovesGenerator::LegalMovesGenerator() {
	
	//get the starting squares for the pawns, this is a good reference
	//for if they can move 2 squares or not
	white_pawns_starting_pos = {
		BoardPos("a2"),
		BoardPos("b2"),
		BoardPos("c2"),
		BoardPos("d2"),
		BoardPos("e2"),
		BoardPos("f2"),
		BoardPos("g2"),
		BoardPos("h2"),
	};
	black_pawns_starting_pos = {
		BoardPos("a7"),
		BoardPos("b7"),
		BoardPos("c7"),
		BoardPos("d7"),
		BoardPos("e7"),
		BoardPos("f7"),
		BoardPos("g7"),
		BoardPos("h7"),
	};
}


bool LegalMovesGenerator::test_legal_move(Board test_board, std::string move) const
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
	PieceName piece_name = test_board.get_piece_at(test_move.get_starting());
	std::vector<Move> legal_moves = get_legal_moves(test_board, piece_name, test_move.get_starting());

	return true;
}


bool LegalMovesGenerator::test_legal_move_player_turn(Board test_board, Move move_to_test) const {

	//get who's turn it is 
	PieceColor whos_turn = test_board.get_side_to_move();
	Bitboard color_side = test_board.get_copy_side_bitboard(whos_turn);
	return color_side.bb.test(move_to_test.get_starting().get_board_ID());

}

std::vector<Move> LegalMovesGenerator::get_legal_moves(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	PieceType piece_type = enum_utils.get_type_from_name(piece_name);


	if (piece_type == PieceType::Rook) {
		legal_moves = get_legal_moves_rook(test_board, piece_name, pos);
	}


	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_legal_moves_rook(Board test_board, PieceName piece_name, BoardPos pos) const
{
	//Rooks can move + or - rank, or + or - file until a piece can be captured. No jumping

	std::vector<Move> legal_moves;







	return legal_moves;

}


std::vector<Move> LegalMovesGenerator::get_legal_moves_across_file(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;

	//to the left



	//to the right



	return legal_moves;
}


/*

std::vector<Move> BoardManager::get_legal_moves_queen(Board test_board, PieceName piece_name, int starting_ID) const
{
	std::vector<Move> legal_moves = get_legal_moves_bishop(test_board, piece_name, starting_ID);
	std::vector<Move> legal_moves_1 = get_legal_moves_rook(test_board, piece_name, starting_ID);
	legal_moves.insert(legal_moves.end(), legal_moves_1.begin(), legal_moves_1.end());
	return legal_moves;
}

*/