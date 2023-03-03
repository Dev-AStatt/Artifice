#include "BoardManager.h"


BoardManager::BoardManager() {

}

void BoardManager::start_new_game() {
	start_new_game_FEN(new_game_FEN);
}

void BoardManager::start_new_game_FEN(std::string FEN) {
	current_board = Board(FEN);
}

bool BoardManager::test_legal_move(Board& current_board, std::string move) const
{

	return false;
}
