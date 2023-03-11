#include "BoardManager.h"



BoardManager::BoardManager() {

}

void BoardManager::start_new_game() {
	start_new_game_FEN(new_game_FEN);
}

void BoardManager::start_new_game_FEN(std::string FEN) {
	current_board = Board(FEN);
}

bool BoardManager::test_legal_move(Board test_board, std::string move) const
{
	return legal_move_gen.test_legal_move(test_board, move);
}

void BoardManager::run_perft_tests(int depth) const
{
	PerftTesting perft_tester = PerftTesting(1,TestType::Nodes, depth);
	



}





