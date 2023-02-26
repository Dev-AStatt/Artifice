#include "Board.h"

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
}


bool Board::load_FEN(std::string FEN)
{
	int rank = 0;
	int file = 0;
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
	//
	// First Section: for string switch case for what piece it is and tracking
	//
	s = fenSections[0];
	for (int i = 0; i < s.size(); i++) {
		c = s[i];

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
	//
	// Second Section: Tracking who's turn is next
	//
	c = fenSections[1][0];
	switch (c) {
	case 'w':
		side_to_move = nWhite;
		break;
	case 'b':
		side_to_move = nBlack;
		break;
	default:
		//std::cout << "Error in Side to move";
		break;
	}
	//
	// Third Section: Castle
	//
	s = fenSections[2];
	for (int i = 0; i < s.size(); i++) {
		c = s[i];
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
			//std::cout << "Error on Castle" << std::endl;
			break;
		}
	}

	//
	// Forth Section: En Passant
	//

	return true;
}


int Board::return_piece_at(int loc) {

	for (int bitboard = 0; bitboard <= 11; bitboard++) {
		if (all_bitboards[bitboard]->test(loc)) {
			return bitboard;
		}
	}
	return enumPiece::nEmpty;
}




