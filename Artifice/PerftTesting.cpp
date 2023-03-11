#include "PerftTesting.h"

PerftTesting::PerftTesting(int test_number, TestType test_type, int depth)
{
	build_test_1();
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

bool PerftTesting::run_test(TestType test_type, int depth)
{





	return false;
}

