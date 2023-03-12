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
		{2,1},
		{1,2},
		{-1,2},
		{-2,1},
		{-2,-1},
		{-1,-2},
		{1,-2},
		{2,-1},
	};
	king_move_table = {
		{1,1},
		{1,0},
		{1,-1},
		{-1, 1},
		{-1,0},
		{-1,-1},
		{0, 1},
		{0, -1}
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
	std::vector<Move> legal_moves = get_legal_moves_for_piece(test_board, piece_name, test_move.get_starting());

	return true;
}


bool LegalMovesGenerator::is_move_right_player(Board test_board, Move move_to_test) const {

	//get who's turn it is 
	PieceColor whos_turn = test_board.get_side_to_move();
	Bitboard color_side = test_board.get_copy_side_bitboard(whos_turn);
	return color_side.bb.test(move_to_test.get_starting().get_board_ID());

}

std::vector<Move> LegalMovesGenerator::get_legal_moves_for_piece(Board test_board, PieceName piece_name, BoardPos pos) const
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
		legal_moves = get_moves_pawn2(test_board, piece_name, pos);
	}
	if (piece_type == PieceType::Knight) {
		legal_moves = get_moves_knight(test_board, piece_name, pos);
	}
	if (piece_type == PieceType::King) {
		legal_moves = get_moves_king(test_board, piece_name, pos);
	}


	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_legal_moves_for_side(Board test_board, PieceColor side) const
{

	std::vector<Move> all_legal_moves;
	PieceColor side_to_move = test_board.get_side_to_move();
	Bitboard side_bb = test_board.get_copy_side_bitboard(side_to_move);
	for (int i = 0; i < side_bb.bb.size(); i++) {
		if (!side_bb.bb.test(i)) { continue; }

		PieceName piece = test_board.get_piece_at(i);
		BoardPos pos = BoardPos(i);

		all_legal_moves = add_moves_together(
			all_legal_moves,
			get_legal_moves_for_piece(test_board, piece, pos)
			);

	}
	return all_legal_moves;

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


std::vector<Move> LegalMovesGenerator::get_moves_pawn2(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	BoardPos test_pos;
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


	//Forward 1 Square
	test_pos = BoardPos(pos.get_rank() + direction_offset, pos.get_file());
	if(!test_pos.is_on_board() || 
		will_king_be_in_check(test_board,Move(pos,test_pos, MoveType::Normal))
		) {}
	else if (test_board.get_piece_at(test_pos) == PieceName::Empty) {
		legal_moves.emplace_back(Move(pos, test_pos, MoveType::Normal));
	}
	//Forward 2 Square
	test_pos = BoardPos(pos.get_rank() + (2* direction_offset), pos.get_file());
	if (!test_pos.is_on_board() ||
		will_king_be_in_check(test_board, Move(pos, test_pos, MoveType::Normal)) ||
		legal_moves.size() == 0
		) {}
	else if (test_board.get_piece_at(test_pos) == PieceName::Empty &&
			is_pawn_starting_position(pawn_color,pos)
		) {
		legal_moves.emplace_back(Move(pos, test_pos, MoveType::DoublePawnPush));
	}

	// - Capture Left
	test_pos = BoardPos(pos.get_rank() + direction_offset, pos.get_file() + 1);
	if (!test_pos.is_on_board() ||
		will_king_be_in_check(test_board, Move(pos, test_pos, MoveType::Normal)) ||
		test_board.get_piece_at(test_pos) == PieceName::Empty
		) {}
	else if (enum_utils.get_color_from_name(test_board.get_piece_at(test_pos)) != pawn_color) {
		legal_moves.emplace_back(Move(pos, test_pos, MoveType::Capture));
	}
	// - Capture Right
	test_pos = BoardPos(pos.get_rank() + direction_offset, pos.get_file() - 1);
	if (!test_pos.is_on_board() ||
		will_king_be_in_check(test_board, Move(pos, test_pos, MoveType::Normal)) ||
		test_board.get_piece_at(test_pos) == PieceName::Empty
		) {
	}
	else if (enum_utils.get_color_from_name(test_board.get_piece_at(test_pos)) != pawn_color) {
		legal_moves.emplace_back(Move(pos, test_pos, MoveType::Capture));
	}
	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_knight(Board test_board, PieceName piece_name, BoardPos pos) const
{
	
	std::vector<Move> legal_moves;
	PieceName target_piece;
	PieceColor knight_color = enum_utils.get_color_from_name(piece_name);
	for (int i = 0; i < knight_move_table.size(); i++) {
		BoardPos test_pos = BoardPos(
			pos.get_rank() + knight_move_table[i].rank,
			pos.get_file() + knight_move_table[i].file);
		

		if (!test_pos.is_on_board()) { continue; }

		target_piece = test_board.get_piece_at(test_pos);

		if (will_king_be_in_check(test_board, Move(pos, test_pos, MoveType::Normal))) { continue; }
			
		if (target_piece == PieceName::Empty) {
			legal_moves.push_back(Move(pos, test_pos, MoveType::Normal));
		}

		else if (enum_utils.get_color_from_name(target_piece) != knight_color) {
			legal_moves.push_back(Move(pos, test_pos, MoveType::Capture));
		}
			
	}

	return legal_moves;
}

std::vector<Move> LegalMovesGenerator::get_moves_king(Board test_board, PieceName piece_name, BoardPos pos) const
{
	std::vector<Move> legal_moves;
	PieceName target_piece;
	PieceColor king_color = enum_utils.get_color_from_name(piece_name);
	for (int i = 0; i < king_move_table.size(); i++) {
		BoardPos test_pos = BoardPos(
			pos.get_rank() + king_move_table[i].rank,
			pos.get_file() + king_move_table[i].file);
		//std::cout << "Board Position: " + test_pos.get_string() << std::endl;

		if (!test_pos.is_on_board()) { continue; }

		target_piece = test_board.get_piece_at(test_pos);

		if (will_king_be_in_check(test_board, Move(pos, test_pos, MoveType::Normal))) {continue;}

		if (target_piece == PieceName::Empty) {
			legal_moves.push_back(Move(pos, test_pos, MoveType::Normal));
		}

		else if (enum_utils.get_color_from_name(target_piece) != king_color) {
			legal_moves.push_back(Move(pos, test_pos, MoveType::Capture));
		}
		
	}

	//Here is where we impliment Casteling
	if (king_color == PieceColor::White) {
		if (test_board.can_white_castle_kingside() &&
			test_board.get_piece_at(63 /*h1*/) == PieceName::WhiteRook &&
			test_board.get_piece_at(62 /*g1*/) == PieceName::Empty &&
			test_board.get_piece_at(61 /*f1*/) == PieceName::Empty
			) {
			legal_moves.push_back(Move(pos, BoardPos("g1"), MoveType::Castle));
		}
		if (test_board.can_white_castle_queenside() &&
			test_board.get_piece_at(56 /*a1*/) == PieceName::WhiteRook &&
			test_board.get_piece_at(57 /*b1*/) == PieceName::Empty &&
			test_board.get_piece_at(58 /*c1*/) == PieceName::Empty &&
			test_board.get_piece_at(59 /*d1*/) == PieceName::Empty
			) {
			legal_moves.push_back(Move(pos, BoardPos("c1"), MoveType::Castle));
		}
	}

	if (king_color == PieceColor::Black &&
		(test_board.can_black_castle_kingside() || test_board.can_black_castle_queenside())
		) {

		if (test_board.can_black_castle_kingside() &&
			test_board.get_piece_at(7 /*h8*/) == PieceName::BlackRook &&
			test_board.get_piece_at(6 /*g8*/) == PieceName::Empty &&
			test_board.get_piece_at(5 /*f8*/) == PieceName::Empty
			) {
			legal_moves.push_back(Move(pos, BoardPos("g8"), MoveType::Castle));
		}
		if (test_board.can_black_castle_queenside() &&
			test_board.get_piece_at(0 /*a8*/) == PieceName::BlackRook &&
			test_board.get_piece_at(1 /*b8*/) == PieceName::Empty &&
			test_board.get_piece_at(2 /*c8*/) == PieceName::Empty &&
			test_board.get_piece_at(3 /*d8*/) == PieceName::Empty
			) {
			legal_moves.push_back(Move(pos, BoardPos("c8"), MoveType::Castle));
		}
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

	//check if the king will be in check
	if (useable_data) {
		useable_data = !will_king_be_in_check(test_board, m);
	}
	
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

