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
	std::vector<Move> moves;
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
	
	LegalMovesGenerator lgm;


	void build_test_1();
	void build_test_2();
	//will return true if passed
	bool run_test(TestType test_type, int depth) const;
	void print_results(std::vector<PerftResults> results, TestType type) const;
	std::string test_type_to_string(TestType type) const;



public:

	PerftTesting(int test_number, TestType test_type, int depth);
	

};

