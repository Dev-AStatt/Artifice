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
	if (!is_move_right_player(test_board, test_move)) { return false; }

	// Step 02
	PieceName piece_name = test_board.get_piece_at(test_move.get_starting());
	std::vector<Move> legal_moves = get_legal_moves(test_board, piece_name, test_move.get_starting());

	return true;
}


bool LegalMovesGenerator::is_move_right_player(Board test_board, Move move_to_test) const {

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
		legal_moves = get_moves_rook(test_board, piece_name, pos);
	}


	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_rook(Board test_board, PieceName piece_name, BoardPos pos) const
{
	//Rooks can move + or - rank, or + or - file until a piece can be captured. No jumping
	std::vector<Move> legal_moves = get_moves_across_file(test_board, piece_name, pos);
	std::vector<Move> legal_moves_1 = get_moves_across_rank(test_board, piece_name, pos);
	return add_moves_together(legal_moves, legal_moves_1);
}

std::vector<Move> LegalMovesGenerator::get_moves_across_file(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	
	//to the left
	int file = pos.get_file();
	//Loop from file to edge of the board to the left
	for (file += 1; file <= 7; file++) {
		BoardPos test_pos = BoardPos(pos.get_rank(), file);
		PieceName test_name = test_board.get_piece_at(test_pos);
		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(pos,test_pos,piece_name,test_name);
		if (ret_val.usable_move) { 
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		} 
		else { break; } //if move unusable - break from the loop
	}
	file = pos.get_file();
	//Loop from file to edge of the board to the right
	for (file -= 1; file >= 0; file--) {
		BoardPos test_pos = BoardPos(pos.get_rank(), file);
		PieceName test_name = test_board.get_piece_at(test_pos);
		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(pos, test_pos, piece_name, test_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
	}
	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_across_rank(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;

	//Searching Down
	int rank = pos.get_rank();
	
	for (rank += 1; rank <= 7; rank++) {
		BoardPos test_pos = BoardPos(rank, pos.get_file());
		PieceName test_name = test_board.get_piece_at(test_pos);
		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(pos, test_pos, piece_name, test_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
	}
	//Searching Up
	rank = pos.get_rank();

	for (rank -= 1; rank >= 0; rank--) {
		BoardPos test_pos = BoardPos(rank, pos.get_file());
		PieceName test_name = test_board.get_piece_at(test_pos);
		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(pos, test_pos, piece_name, test_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
	}
	return legal_moves;
}

Return_For_Move_Validation LegalMovesGenerator::if_endpoint_legal_get_move(
	BoardPos source_pos, 
	BoardPos test_pos, 
	PieceName source_name, 
	PieceName test_name
) const {
	
	//here are all the default flags to be made into a move later
	MoveType type = MoveType::Normal;
	bool useable_data = false;
	bool continue_searching_after = true;


	if (test_name == PieceName::Empty) {
		//if location is empty add it to the list of legal moves
		useable_data = true;
		continue_searching_after = true;
	}

	else if (enum_utils.is_piece_same_team(source_name, test_name)) {
		//if on the same team, break
		useable_data = false;
		continue_searching_after = false;
	}

	else if (!enum_utils.is_piece_same_team(source_name, test_name)) {
		//if not on the same team
		//check for special cases, like if the opponent piece is a king, or an Enpassant
		if (enum_utils.is_king(test_name)) {
			type = MoveType::Check;
			useable_data = true;
			continue_searching_after = false;
		}
		else if (enum_utils.is_pawn(test_name)) {
			//This is where you would check for EnPasant
			type = MoveType::Capture;
			useable_data = true;
			continue_searching_after = false;
		}
		else {
			type = MoveType::Capture;
			useable_data = true;
			continue_searching_after = true;
		}
	}
	else {
		throw std::invalid_argument("we fell out of a if else that we shouldn't have");
		useable_data = false;
	}

	//Create a move of type that may have been changed in the if checks
	Move m = Move(source_pos, test_pos, type);
	return Return_For_Move_Validation{ useable_data, continue_searching_after, m };
}


std::vector<Move> LegalMovesGenerator::add_moves_together(std::vector<Move> m1, std::vector<Move> m2) const {
	std::vector<Move> ret_vect = m1;
	std::copy(m2.begin(), m2.end(), std::back_inserter(ret_vect));
	return ret_vect;
}


