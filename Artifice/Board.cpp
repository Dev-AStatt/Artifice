#include "Board.h"
#include <iostream>



Board::Board() {
    all_bitboards.emplace_back(&whitePawns);
    all_bitboards.emplace_back(&whiteKnights);
    all_bitboards.emplace_back(&whiteBishops);
    all_bitboards.emplace_back(&whiteRooks);
    all_bitboards.emplace_back(&whiteQueens);
    all_bitboards.emplace_back(&whiteKings);
    all_bitboards.emplace_back(&blackPawns);
    all_bitboards.emplace_back(&blackKnights);
    all_bitboards.emplace_back(&blackBishops);
    all_bitboards.emplace_back(&blackRooks);
    all_bitboards.emplace_back(&blackQueens);
    all_bitboards.emplace_back(&blackKings);

	all_piece_names.emplace_back(PieceName::WhitePawn);
	all_piece_names.emplace_back(PieceName::WhiteKnight);
	all_piece_names.emplace_back(PieceName::WhiteBishop);
	all_piece_names.emplace_back(PieceName::WhiteRook);
	all_piece_names.emplace_back(PieceName::WhiteQueen);
	all_piece_names.emplace_back(PieceName::WhiteKing);
	all_piece_names.emplace_back(PieceName::BlackPawn);
	all_piece_names.emplace_back(PieceName::BlackKnight);
	all_piece_names.emplace_back(PieceName::BlackBishop);
	all_piece_names.emplace_back(PieceName::BlackRook);
	all_piece_names.emplace_back(PieceName::BlackQueen);
	all_piece_names.emplace_back(PieceName::BlackKing);
}


bool Board::load_FEN(std::string FEN)
{
	char c;
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

bool Board::sort_fen_pieces_into_bitboards(std::string fen_sec_1) {
	int rank = 0;
	int file = 0;

	for (int i = 0; i < fen_sec_1.size(); i++) {
		char c = fen_sec_1[i];

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
			//// bset.set(pos) makes bset[pos] = 1
			blackRooks.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'n':
			blackKnights.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'b':
			blackBishops.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'q':
			blackQueens.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'k':
			blackKings.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'p':
			blackPawns.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
			//WHITE_P PIECES
		case 'R':
			whiteRooks.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'N':
			whiteKnights.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'B':
			whiteBishops.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'Q':
			whiteQueens.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'K':
			whiteKings.set(get_board_ID(file, rank));
			rank = ++rank;
			break;
		case 'P':
			whitePawns.set(get_board_ID(file, rank));
			rank = ++rank;
			break;

		default:
			int cint = c - '0';

			rank = rank + cint;

			break;
		}
	}
}

PieceName Board::return_piece_at(int loc) const {

	for (int bitboard = 0; bitboard <= 11; bitboard++) {
		if (all_bitboards[bitboard]->test(loc)) {
			return all_piece_names[bitboard];
		}
	}
	return PieceName::Empty;
}




