#pragma once
#include "pch.h"
#include "CppUnitTest.h"

#include "../Artifice/Move.cpp"
#include "../Artifice/Board.cpp"
#include "../Artifice/LegalMovesGenerator.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArtificeUnitTests
{
	TEST_CLASS(MoveClass) {
	public:
		TEST_METHOD(TestThatTestsWork) {Assert::AreEqual(1, 1);}
		TEST_METHOD(String_To_Board_ID) {
			Move m_1 = Move("a1a1");
			Move m_2 = Move("h8h8");
			
			Assert::AreEqual(56, m_1.get_starting().get_board_ID());
			Assert::AreEqual(56, m_1.get_ending().get_board_ID());
			Assert::AreEqual(7, m_2.get_starting().get_board_ID());
			Assert::AreEqual(7, m_2.get_ending().get_board_ID());
		}
		TEST_METHOD(CopyVectors) {
			std::vector<Move> m_1 = {
				Move("a1a2"),
				Move("a3a4")
			};
			std::vector<Move> m_2 = {
				Move("b1b2"),
				Move("b3b4")
			};
			Assert::AreEqual(4, int(m_1.size() + m_2.size()));
			
			std::copy(m_2.begin(), m_2.end(), std::back_inserter(m_1));

			Assert::AreEqual(4, int(m_1.size()));
		}

	};

	TEST_CLASS(Enums_Class) {
	public:
		TEST_METHOD(ColorConversion_1) {
			Enum_Utils enum_utils;
			PieceColor pc_1 = enum_utils.get_color_from_name(PieceName::WhitePawn);
			PieceColor pc_2 = enum_utils.get_color_from_name(PieceName::AllWhite);
			PieceColor pc_3 = enum_utils.get_color_from_name(PieceName::BlackPawn);
			PieceColor pc_4 = enum_utils.get_color_from_name(PieceName::AllBlack);

			Assert::IsTrue(pc_1 == PieceColor::White);
			Assert::IsTrue(pc_2 == PieceColor::White);
			Assert::IsTrue(pc_3 == PieceColor::Black);
			Assert::IsTrue(pc_4 == PieceColor::Black);
			
		}
	};
	TEST_CLASS(Board_Pos_Class) {
	public:
		TEST_METHOD(Constructor_Baord_ID) {
			BoardPos bp_1 = BoardPos(33); //b4 - file: 1 rank: 3
			BoardPos bp_2 = BoardPos(7); //b4 - file: 1 rank: 3
			
			Assert::AreEqual(1, bp_1.get_file());
			Assert::AreEqual(4, bp_1.get_rank());
			Assert::AreEqual(33, bp_1.get_board_ID(4, 1));

			Assert::AreEqual(7, bp_2.get_file());
			Assert::AreEqual(0, bp_2.get_rank());
			Assert::AreEqual(7, bp_2.get_board_ID(0, 7));
		}
		TEST_METHOD(Constructor_String_Correct_Input) {
			//Test Correct Input
			BoardPos bp_1 = BoardPos("a1");
			Assert::AreEqual(56, bp_1.get_board_ID());
			Assert::AreEqual(7, bp_1.get_rank());
			Assert::AreEqual(0, bp_1.get_file());
		}
		TEST_METHOD(Constructor_String_Invalid_Input) {
			auto func = [] { BoardPos("ww"); };
			Assert::ExpectException<std::invalid_argument>(func);
		}
		

	};
	TEST_CLASS(MoveLawer) {
	public:
		TEST_METHOD(LM_across_file) {
			std::string loaded_fen = "rnbqkbnr/ppp1pppp/8/8/3N4/8/B1p1R2P/1NBQK1NR w Kkq - 0 1";
			Board b = Board(loaded_fen);
			LegalMovesGenerator lgm;
			std::vector<Move> test_moves = lgm.get_legal_moves(b, PieceName::WhiteRook, BoardPos("e2"));

			Assert::AreEqual(9, int(test_moves.size()));
			test_moves = lgm.get_legal_moves(b, PieceName::WhiteRook, BoardPos("h1"));
			Assert::AreEqual(0, int(test_moves.size()));
		}
	};
	
}


