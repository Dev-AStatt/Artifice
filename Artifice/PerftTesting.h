#pragma once
#include "Board.h"
#include "LegalMovesGenerator.h"

enum class TestType {
	Nodes,
	Captures,
	EnPassant,
	Castles,
	Promotions,
	Checks,
	DiscoveryChecks,
	DoubleChecks,
	Checkmates
};

struct PerftResults {
	int depth;
	int calculated;
	int test_result;
};




class PerftTesting
{
private:
	std::string test_board_string;
	std::vector<int> results_nodes = {};
	std::vector<int> results_captures = {};
	std::vector<int> results_enpassant = {};
	std::vector<int> results_castles = {};
	std::vector<int> results_promotions = {};
	std::vector<int> results_checks = {};
	std::vector<int> results_discovery_checks = {};
	std::vector<int> results_double_checks = {};
	std::vector<int> results_checkmates = {};
	
	int max_depth_for_test;

	std::vector<Move> white_opening_moves;
	void build_opening_moves();

	LegalMovesGenerator lgm;
	

	void build_test_1();
	void build_test_2();
	//will return true if passed
	bool run_perft_test(TestType test_type, int depth) const;
	bool run_test_after_move(Board starting_board, int depth) const;
	void print_perft_results(std::vector<PerftResults> results, TestType type) const;
	void print_init_pos_summary(Move starting, std::vector<PerftResults> results) const;
	std::string test_type_to_string(TestType type) const;

	
//	PerftResults get_next_depth(Board starting_board, std::vector<Move> last_perft_moves, int current_depth, bool print) const;

	int count_nodes(int depth, Board starting_board, bool print) const;



public:

	PerftTesting(int test_number, TestType test_type, int depth);
	

};

