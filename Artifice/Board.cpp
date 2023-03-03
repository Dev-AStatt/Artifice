#include "Board.h"
#include <iostream>



Board::Board() {
	create_bitboards();
}

Board::Board(std::string FEN) {
	create_bitboards();
	overwrite_board_from_FEN(FEN);
}

void Board::create_bitboards() {

	all_bitboards = {
		{ PieceName::WhitePawn	, 0},
		{ PieceName::WhiteKnight, 0 },
		{ PieceName::WhiteBishop, 0 },
		{ PieceName::WhiteRook	, 0 },
		{ PieceName::WhiteQueen	, 0 },
		{ PieceName::WhiteKing	, 0 },
		{ PieceName::BlackPawn	, 0 },
		{ PieceName::BlackKnight, 0 },
		{ PieceName::BlackBishop, 0 },
		{ PieceName::BlackRook	, 0 },
		{ PieceName::BlackQueen	, 0 },
		{ PieceName::BlackKing	, 0 },
	};
}

bool Board::load_FEN(std::string FEN)
{
	std::string s;
	std::stringstream ss(FEN);
	std::vector<std::string> fenSections;

	//
	// Sepperate the FEN string into its seperate components. First Section is pieces
	// Second section is who goes next, Third is who can castle, Fourth is En Passant
	// Fith is Halfmove clock, and 6th is Fullmove Counter
	//
	while (std::getline(ss, s, ' ')) {
		fenSections.push_back(s);
	}
	// First Section: for string switch case for what piece it is and tracking
	sort_fen_pieces_into_bitboards(fenSections[0]);
	
	// Second Section: Tracking who's turn is next
	set_next_turn_from_fen(fenSections[1]);
	//
	// Third Section: Castle
	//
	set_castle_rites_from_fen(fenSections[2]);

	//
	// Forth Section: En Passant
	//

	return true;
}

bool Board::set_castle_rites_from_fen(std::string fen_sec_3) {
	for (int i = 0; i < fen_sec_3.size(); i++) {
		char c = fen_sec_3[i];
		switch (c) {
		case 'K':
			K_Castle = true;
			break;
		case 'Q':
			Q_Castle = true;
			break;
		case 'k':
			k_Castle = true;
			break;
		case 'q':
			q_Castle = true;
			break;
		case '-':
			K_Castle = false;
			Q_Castle = false;
			k_Castle = false;
			q_Castle = false;
			break;
		default:
			std::cout << "Error on Castle" << std::endl;
			return false;
			break;
		}
	}
}

bool Board::set_next_turn_from_fen(std::string fen_sec_2) {
	
	char c = fen_sec_2[0]; //get the first charicter from the string at id: 1
	switch (c) {
	case 'w':
		side_to_move = PieceName::White;
		break;
	case 'b':
		side_to_move = PieceName::Black;
		break;
	default:
		std::cout << "Error in Side to move";
		return false;
		break;
	}
}

void Board::insert_piece_into_bb(PieceName p_name, int id) {
	//This is a lamda function that can be used as a comparison for the find_if below
	//it takes in the current bitboard that find is looking for. in the brackets is what you
	//can pass in from the sorounding function. 
	auto is_name = [p_name](Bitboard& b) { return b.name == p_name; };
	auto it = std::find_if(all_bitboards.begin(), all_bitboards.end(), is_name);
	it->bb.set(id);
}

PieceName Board::return_piece_at(int board_id) const {
	//This produces a weird error if the bitboard function is not const, so just keep
	//an eye on that. 
	auto is_set = [board_id](const Bitboard& b) {return b.bb.test(board_id); };
	//Find the bitboard that has the test position set at board_id
	auto it = std::find_if(all_bitboards.begin(), all_bitboards.end(), is_set);
	
	if (it != std::end(all_bitboards)) {
		return it->name;
	} 
	else {
		return PieceName::Empty;
	}	
}


bool Board::sort_fen_pieces_into_bitboards(std::string fen_sec_1) {
	int rank = 0;
	int file = 0;

	for (int i = 0; i < fen_sec_1.size(); i++) {
		char c = fen_sec_1[i];

		int board_id = get_board_ID(file, rank);

		//Dont Look at this Cancer
		switch (c) {
		case ' ':
			break;
		case '/':
			file = ++file;
			rank = 0;
			if (file > 7) { return false; }
			break;
		case 'r':
			insert_piece_into_bb(PieceName::BlackRook, board_id);
			rank = ++rank;
			break;
		case 'n':
			insert_piece_into_bb(PieceName::BlackKnight, board_id);
			rank = ++rank;
			break;
		case 'b':
			insert_piece_into_bb(PieceName::BlackBishop, board_id);
			rank = ++rank;
			break;
		case 'q':
			insert_piece_into_bb(PieceName::BlackQueen, board_id);
			rank = ++rank;
			break;
		case 'k':
			insert_piece_into_bb(PieceName::BlackKnight, board_id);
			rank = ++rank;
			break;
		case 'p':
			insert_piece_into_bb(PieceName::BlackPawn, board_id);
			rank = ++rank;
			break;
			//WHITE_P PIECES
		case 'R':
			insert_piece_into_bb(PieceName::WhiteRook, board_id);
			rank = ++rank;
			break;
		case 'N':
			insert_piece_into_bb(PieceName::WhiteKnight, board_id);
			rank = ++rank;
			break;
		case 'B':
			insert_piece_into_bb(PieceName::WhiteBishop, board_id);
			rank = ++rank;
			break;
		case 'Q':
			insert_piece_into_bb(PieceName::WhiteQueen, board_id);
			rank = ++rank;
			break;
		case 'K':
			insert_piece_into_bb(PieceName::WhiteKing, board_id);
			rank = ++rank;
			break;
		case 'P':
			insert_piece_into_bb(PieceName::WhitePawn, board_id);
			rank = ++rank;
			break;

		default:
			int cint = c - '0';

			rank = rank + cint;

			break;
		}
	}
}






