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

	knight_move_table = {
		//rank ,file
	  std::make_pair(2,1),
	  std::make_pair(1,2),
	  std::make_pair(-1,2),
	  std::make_pair(-2,1),
	  std::make_pair(-2,-1),
	  std::make_pair(-1,-2),
	  std::make_pair(1,-2),
	  std::make_pair(2,-1),
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
	if (piece_type == PieceType::Bishop) {
		legal_moves = get_moves_bishop(test_board, piece_name, pos);
	}
	if (piece_type == PieceType::Queen) {
		legal_moves = get_moves_queen(test_board, piece_name, pos);
	}
	if (piece_type == PieceType::Pawn) {
		legal_moves = get_moves_pawn(test_board, piece_name, pos);
	}
	if (piece_type == PieceType::Knight) {
		legal_moves = get_moves_knight(test_board, piece_name, pos);
	}


	return legal_moves;
}

// 0----------------------------------------------------------------0
// |						MOVES BY PIECE							|
// 0----------------------------------------------------------------0

std::vector<Move> LegalMovesGenerator::get_moves_rook(Board test_board, PieceName piece_name, BoardPos pos) const
{
	//Rooks can move + or - rank, or + or - file until a piece can be captured. No jumping
	std::vector<Move> legal_moves = get_moves_across_file(test_board, piece_name, pos);
	std::vector<Move> legal_moves_1 = get_moves_across_rank(test_board, piece_name, pos);
	return add_moves_together(legal_moves, legal_moves_1);
}

std::vector<Move> LegalMovesGenerator::get_moves_bishop(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves = get_moves_across_rising_diag(test_board, piece_name, pos);
	std::vector<Move> legal_moves_1 = get_moves_across_decend_diag(test_board, piece_name, pos);
	return add_moves_together(legal_moves, legal_moves_1);
}

std::vector<Move> LegalMovesGenerator::get_moves_queen(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves_r = get_moves_rook(test_board, piece_name, pos);
	std::vector<Move> legal_moves_b = get_moves_bishop(test_board, piece_name, pos);
	return add_moves_together(legal_moves_b, legal_moves_r);
}

std::vector<Move> LegalMovesGenerator::get_moves_pawn(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	std::vector<BoardPos> to_test;
	std::vector<bool> usable = { false, false , false, false };
	int direction_offset;
	PieceColor pawn_color = enum_utils.get_color_from_name(piece_name);

	if (pawn_color == PieceColor::White) { direction_offset = -1; }
	else { direction_offset = 1; }

	/*RULES FOR PAWNS
	* a. The pawn may move forward to the unoccupied square immediately in front of it on
		 the same file, or
	  b. on its first move the pawn may move it may advance two squares along the
	     same file provided both squares are unoccupied, or
	  c. the pawn may move to a square occupied by an opponent’s piece, which is
		 diagonally in front of it on an adjacent file, capturing that piece.
	*/

	//Get list of possible positions
	// [0] - Normal pawn push
	to_test.push_back(BoardPos(pos.get_rank() + direction_offset, pos.get_file()));
	// [1] - Double panw push
	to_test.push_back(BoardPos(pos.get_rank() + (2 * direction_offset), pos.get_file()));
	// [2] - Capture 1
	to_test.push_back(BoardPos(pos.get_rank() + direction_offset, pos.get_file() + 1));
	// [3] - Capture 2
	to_test.push_back(BoardPos(pos.get_rank() + direction_offset, pos.get_file() - 1));

	
	//Check if forward is empty
	if (test_board.get_piece_at(to_test[0]) == PieceName::Empty) { 
		usable[0] = true;
	}
	//check if we can double pawn push
	if (usable[0] &&
		is_pawn_starting_position(pawn_color,pos) &&
		test_board.get_piece_at(to_test[1]) == PieceName::Empty
		) {
		usable[1] = true;
	}
	// check if diagonal moves work
	PieceName target_piece = test_board.get_piece_at(to_test[2]);
	if (
		target_piece != PieceName::Empty &&
		enum_utils.get_color_from_name(target_piece) != pawn_color
		) {
		usable[2] = true;
	}
	target_piece = test_board.get_piece_at(to_test[3]);
	if (
		target_piece != PieceName::Empty &&
		enum_utils.get_color_from_name(target_piece) != pawn_color
		) {
		usable[3] = true;
	}
	//Check if on board
	for (int i = 0; i < to_test.size(); i++) {
		if (!to_test[i].is_on_board()) { usable[i] = false; }
	}
	//check if any move will end up with the king in check
	for (int i = 0; i < to_test.size(); i++) {
		if (usable[i]) {
			usable[i] = !will_king_be_in_check(test_board, Move(pos, to_test[i], MoveType::Normal));
		}
	}

	if (usable[0]) {

		legal_moves.emplace_back(Move(pos, to_test[0], MoveType::Normal));				//NOTE HERE PAWNS CANT GEN CHECK MOVES ATM
	}
	if (usable[1]) {
		legal_moves.emplace_back(Move(pos, to_test[1], MoveType::DoublePawnPush));
	}
	if (usable[2]) {
		legal_moves.emplace_back(Move(pos, to_test[2], MoveType::Capture));
	}
	if (usable[3]) {
		legal_moves.emplace_back(Move(pos, to_test[3], MoveType::Capture));
	}

	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_knight(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	for (int i; i < knight_move_table.size(); i++) {
		BoardPos test_pos = BoardPos(
			pos.get_rank() + knight_move_table[i].first,
			pos.get_file() + knight_move_table[i].second);

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
	}




	return legal_moves;
}





// 0----------------------------------------------------------------0
// |						MOVES BY DIRECTION						|
// 0----------------------------------------------------------------0

std::vector<Move> LegalMovesGenerator::get_moves_across_file(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	
	//to the left
	int file = pos.get_file();
	//Loop from file to edge of the board to the left
	for (file += 1; file <= 7; file++) {
		BoardPos test_pos = BoardPos(pos.get_rank(), file);
		
		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos,test_pos,piece_name);
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

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
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

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
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

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
	}
	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_across_rising_diag(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;

	int rank = pos.get_rank() - 1;
	int file = pos.get_file() + 1;
	while (rank >= 0 && file <= 7) {
		BoardPos test_pos = BoardPos(rank, file);

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
		rank -= 1;
		file += 1;
	}

	rank = pos.get_rank() + 1;
	file = pos.get_file() - 1;
	while (rank <= 7 && file >= 0) {
		BoardPos test_pos = BoardPos(rank, file);

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
		rank += 1;
		file -= 1;
	}


	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_across_decend_diag(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;

	int rank = pos.get_rank() + 1;
	int file = pos.get_file() + 1;
	while (rank <= 7 && file <= 7) {
		BoardPos test_pos = BoardPos(rank, file);

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
		rank += 1;
		file += 1;
	}

	rank = pos.get_rank() - 1;
	file = pos.get_file() - 1;
	while (rank >= 0 && file >= 0) {
		BoardPos test_pos = BoardPos(rank, file);

		//for each loop, check if the next position is a move or not
		Return_For_Move_Validation ret_val = if_endpoint_legal_get_move(test_board, pos, test_pos, piece_name);
		if (ret_val.usable_move) {
			//test the out paramaters of ret_val
			legal_moves.emplace_back(ret_val.returned_move);
			if (!ret_val.continue_searching) { break; }
		}
		else { break; } //if move unusable - break from the loop
		rank -= 1;
		file -= 1;
	}


	return legal_moves;
}

Return_For_Move_Validation LegalMovesGenerator::if_endpoint_legal_get_move(
	Board test_board,
	BoardPos source_pos, 
	BoardPos test_pos, 
	PieceName source_name
) const {
	
	PieceName test_name = test_board.get_piece_at(test_pos);

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
			type = MoveType::Capture;
			useable_data = true;
			continue_searching_after = false;
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

bool LegalMovesGenerator::is_in_board_pos_vec(BoardPos pos, std::vector<BoardPos> vect) const {

	auto is_equal = [pos](const BoardPos& bp) {return bp.get_board_ID() == pos.get_board_ID(); };

	auto it = std::find_if(vect.begin(), vect.end(), is_equal);
	if (it != std::end(vect)) {	return true;}
	else { return false; }

}

bool LegalMovesGenerator::is_pawn_starting_position(PieceColor color, BoardPos pos) const
{
	if (color == PieceColor::White) {
		return is_in_board_pos_vec(pos, white_pawns_starting_pos);
	}
	else if (color == PieceColor::Black) {
		return is_in_board_pos_vec(pos, black_pawns_starting_pos);
	}
	else { return false; }
}

