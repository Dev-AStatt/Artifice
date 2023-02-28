#include "GameDebug.h"

GameDebug::GameDebug()
{
	std::cout.setf(std::ios::unitbuf);// Make sure that the outputs are sent straight away to the GUI
	std::cout << "Welcome to the Debug mode." << std::endl;
	std::cout << "01 - 'new'  - Start new game" << std::endl;
	std::cout << "02 - 'fen'  - start game from FEN string" << std::endl;
	std::cout << "03 - 'quit' - quit the debugger" << std::endl;
}

void GameDebug::game_debug_loop() {
	while (std::getline(std::cin, line)) {
		if (line == "new") {
			game_board.start_with_FEN();
		}
		else if (line == "quit") {
			std::cout << "Bye Bye" << std::endl;
			break;
		}
		print_board();
	}
	
}

//Function will print the current board state to the console for debug mode
void GameDebug::print_board() const
{
	//Board Print stuff
	std::string rank_separation = "    +---+---+---+---+---+---+---+---+";
	std::string board_spacing = " | ";
	std::string board_rank_labels = "      a   b   c   d   e   f   g   h  ";
	
	//Loop through each rank and file
	for (int rank = 0; rank < 8; rank++) {
		std::cout << rank_separation << std::endl;
		//print the rank number before printing the rest of the file
		std::cout << "  " << 8 - rank << " ";

		for (int file = 0; file < 8; file++) {
			std::cout << "| ";

			//get the piece number at this rank and file
			PieceName p = game_board.return_piece_at(game_board.get_board_ID(rank, file));
			//convert that piece number to a string to be displayed
			std::cout << piece_to_string(p);
			std::cout << " ";
		}
		//put a "|" at the end of the line
		std::cout << "|" << std::endl;
	}
	std::cout << rank_separation << std::endl;
	std::cout << board_rank_labels << std::endl << std::endl;

	//Print game information
	std::cout << "Turn: ";
	if (side_to_move == PieceName::Black) { std::cout << "Black     "; }
	else { std::cout << "White     "; }
	std::cout << "Castle: ";
	if (white_king_castle ) { std::cout << 'K'; }
	if (white_queen_castle) { std::cout << 'Q'; }
	if (black_king_castle ) { std::cout << 'k'; }
	if (black_queen_castle) { std::cout << 'q'; }
	std::cout << std::endl;

}

std::string GameDebug::piece_to_string(PieceName p) const
{
	switch (p) {
	case PieceName::WhitePawn:
		return "P";
		break;
	case PieceName::WhiteKnight:
		return "N";
		break;
	case PieceName::WhiteBishop:
		return "B";
		break;
	case PieceName::WhiteRook:
		return "R";
		break;
	case PieceName::WhiteQueen:
		return "Q";
		break;
	case PieceName::WhiteKing:
		return "K";
		break;
	case PieceName::BlackPawn:
		return "p";
		break;
	case PieceName::BlackKnight:
		return "n";
		break;
	case PieceName::BlackBishop:
		return "b";
		break;
	case PieceName::BlackRook:
		return "r";
		break;
	case PieceName::BlackQueen:
		return "q";
		break;
	case PieceName::BlackKing:
		return "k";
		break;
	default:
		return " ";

	}
}

