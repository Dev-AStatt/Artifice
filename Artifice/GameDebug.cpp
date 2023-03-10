#include "GameDebug.h"

GameDebug::GameDebug() {

	BoardManager board_manager = BoardManager();
	print_opening_text();
}

void GameDebug::print_opening_text() const {
	std::cout.setf(std::ios::unitbuf);// Make sure that the outputs are sent straight away to the GUI
	std::cout << "Welcome to the Debug mode." << std::endl;
	std::cout << "01 - 'new'  - Start new game" << std::endl;
	std::cout << "02 - 'fen'  - start game from FEN string" << std::endl;
	std::cout << "03 - 'quit' - quit the debugger" << std::endl;
	std::cout << "04 - 'perft test <test>' - will run perft testing" << std::endl;
}

void GameDebug::print_help() const {
	std::cout << "Options During Debug Mode:" << std::endl;
	std::cout << "01 - 'test ' <move> - Will test if a move is legal" << std::endl;
	std::cout << "02 - 'flip turn' - will flip who's turn it is" << std::endl;
	
}


void GameDebug::game_debug_loop() {
	while (std::getline(std::cin, line)) {
		bool draw_board = false;
		if (line == "new") {
			board_manager.start_new_game();
			draw_board = true;
		}
		if (line == "fen") {
			board_manager.start_new_game_FEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
			draw_board = true;
		}
		else if (line == "quit") {
			std::cout << "Bye Bye" << std::endl;
			break;
		}
		else if (line == "help") {
			print_help();
		}
		else if (line == "flip turn") {
			board_manager.flip_turn_current_board();
			draw_board = true;
		}

		else if (line.substr(0, 5) == "test ") {
			std::cout << "Testing Move " + line.substr(5, 10) << std::endl;
			if (board_manager.test_legal_move(board_manager.copy_current_board(), line.substr(5, 10))) {
				std::cout << "Move: " + line.substr(5, 10) + " Is an Legal Move" << std::endl;
			}
			else {
				std::cout << "Move: " + line.substr(5, 10) + " Is an Illegal Move" << std::endl;
			}
		}

		else if (line.substr(0, 11) == "perft test ") {
			std::cout << "Running Perft Test " + line.substr(11, 12) << std::endl;

			int depth = std::stoi(line.substr(11));

			board_manager.run_perft_tests(depth);
		}

		if (draw_board) {
			Board cb = board_manager.copy_current_board();
			print_board(cb);
		}
	}
}

//There is a bug in here somewhere with the board getting copied into the printboard function

//Function will print the current board state to the console for debug mode
void GameDebug::print_board(Board board_to_print) const
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
			PieceName p = board_to_print.get_piece_at(get_board_ID(rank, file));
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
	if (board_to_print.get_side_to_move() == PieceColor::Black) { std::cout << "Black     "; }
	else { std::cout << "White     "; }
	std::cout << "Castle: ";
	if (board_to_print.can_white_castle_kingside() ) { std::cout << 'K'; }
	if (board_to_print.can_white_castle_queenside() ) { std::cout << 'Q'; }
	if (board_to_print.can_black_castle_kingside() ) { std::cout << 'k'; }
	if (board_to_print.can_black_castle_queenside()) { std::cout << 'q'; }
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

