#include "BoardManager.h"


BoardManager::BoardManager() {

}

void BoardManager::start_new_game() {
	start_new_game_FEN(new_game_FEN);
}

void BoardManager::start_new_game_FEN(std::string FEN) {
	current_board = Board(FEN);
}