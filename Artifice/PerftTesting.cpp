#include "PerftTesting.h"

PerftTesting::PerftTesting(int test_number, TestType test_type, int depth)
{
	build_test_1();
	if (depth > max_depth_for_test) { depth = max_depth_for_test; }
	run_test(test_type, depth);

}



void PerftTesting::build_test_1() {
	test_board_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";
	/*
	Depth 	Nodes 				Captures 			E.p. 			Castles 		Promotions 	Checks 		Disc Checks Double Checks 	Checkmates
	0	 	1 					0 					0 				0 				0		 	0				0			0		 	0
	1		20 					0 					0				0				0		 	0			 	0			0			0
	2		400 				0 					0 				0 				0		 	0				0			0			0
	3		8,902 				34 					0 				0 				0		 	12				0			0			0
	4		197,281 			1576 				0 				0 				0			469 			0		 	0			8
	5		4,865,609 			82,719 				258				0 				0 			27,351			6		 	0			347
	6		119,060,324 		2,812,008 			5248 			0 				0			809,099		 	329 		46 			10,828
	7		3,195,901,860 		108,329,926 		319,617 		883,453 		0 			33,103,848 		18,026 		1628 		435,767
	8		84,998,978,956		3,523,740,106 		7,187,977		23,605,205		0 			968,981,593 	847,039 	147,215 	9,852,036
	9		2,439,530,234,167 	125,208,536,153		319,496,827 	1,784,356,000 	17,334,376 	36,095,901,903 	37,101,713 	5,547,231 	400,191,963
	
	*/

	max_depth_for_test = 6;
	
	results_nodes = {
		1,
		20,
		400,
		8902,
		197281,
		4865609,
		119060324
	};

	results_captures = {
		0,
		0,
		0,
		34,
		1576,
		82719
	};

	
}

void PerftTesting::build_test_2() {
	std::string perft_2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";

}

std::string PerftTesting::test_type_to_string(TestType type) const
{
	std::string type_string;
	if (type == TestType::Nodes) { type_string = "Nodes"; }
	if (type == TestType::Captures) { type_string = "Captures"; }
	if (type == TestType::EnPassant) { type_string = "EnPassant"; }
	if (type == TestType::Castles) { type_string = "Castles"; }
	if (type == TestType::Promotions) { type_string = "Promoations"; }
	if (type == TestType::Checks) { type_string = "Checks"; }
	if (type == TestType::DiscoveryChecks) { type_string = "Discovery Checks"; }
	if (type == TestType::DoubleChecks) { type_string = "Double Checks"; }
	if (type == TestType::Checkmates) { type_string = "Checkmates"; }

	return type_string;
}

std::vector<Move> add_moves_together(std::vector<Move> m1, std::vector<Move> m2) {
	std::vector<Move> ret_vect = m1;
	std::copy(m2.begin(), m2.end(), std::back_inserter(ret_vect));
	return ret_vect;
}

bool PerftTesting::run_test(TestType test_type, int depth) const
{
	std::vector<PerftResults> results;

	Board starting_board = Board(test_board_string);
	
	
	for (int i = 0; i <= depth; i++) {
		PerftResults r = {
			i,
			count_nodes(i, starting_board),
			results_nodes[i]
		};

		results.emplace_back(r);

	}
	print_results(results, test_type);
	

	return false;
}

int PerftTesting::count_nodes(int depth, Board starting_board) const {
	if (depth == 0) { return 1; }


	std::vector<Move> new_moves = lgm.get_legal_moves_for_side(starting_board, starting_board.get_side_to_move());
	int number_positions = 0;

	for (Move m : new_moves) {
		Board new_board = starting_board;
		new_board.make_move(m);
		number_positions += count_nodes(depth - 1, new_board);
	}
	return number_positions;
}

//PerftResults PerftTesting::get_next_depth(Board starting_board, std::vector<Move> last_perft_moves,int current_depth, bool print) const {
//	
//	std::vector<Move> total_moves;
//	Board test_board;
//
//	for (Move m : last_perft_moves) {
//		test_board = starting_board;
//		test_board.make_move(m);
//
//		std::vector<Move> new_moves = lgm.get_legal_moves_for_side(test_board, test_board.get_side_to_move());
//		if (print) {
//			std::cout << "Printing Moves After: " << m.get_standard_notation() << std::endl;
//			for (Move nm : new_moves) {
//				std::cout << nm.get_standard_notation() << std::endl;
//			}
//		}
//		
//		total_moves = add_moves_together(
//			total_moves,
//			new_moves
//		);
//	}
//
//	PerftResults output = {current_depth, total_moves, results_nodes[current_depth]};
//	return output;
//
//}

void PerftTesting::print_results(std::vector<PerftResults> results, TestType type) const
{
	std::string type_str = test_type_to_string(type);
	std::cout << "Test Results for Test " << "1" << std::endl;
	std::cout << "Depth |  " << type_str <<" Expected |  " << type_str << " Results" << std::endl;
	for (PerftResults r : results) {
		std::cout << r.depth << "     |  " << r.test_result << "		|  " << r.calculated << std::endl;

	}


}

