#pragma once
#include <string>
#include "pch.h"
#include "CppUnitTest.h"

#include "../Artifice/Move.cpp"
#include "../Artifice/Board.cpp"
#include "../Artifice/LegalMovesGenerator.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArtificeUnitTests
{
	TEST_CLASS(BoardClass) {
	public:
		TEST_METHOD(Update_Mesh) {
			Board test_board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			Bitboard white_bitboard = test_board.get_copy_side_bitboard(PieceColor::White);

			Assert::AreEqual(16, int(white_bitboard.bb.count()));

			Move m = Move("d2e3");
			test_board.make_move(m);
			white_bitboard = test_board.get_copy_side_bitboard(PieceColor::White);
			Assert::AreEqual(16, int(white_bitboard.bb.count()));

		}

	};

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
		TEST_METHOD(String_From_BoardPos) {
			BoardPos bp = BoardPos(57); //b1
			std::string standard_notation = "b1";
			Assert::AreEqual(standard_notation, bp.get_string());
		}
		

	};

	TEST_CLASS(MoveLawyer) {
	private:
		std::string test_position_1 = "rnbqkbnr/ppp1pppp/8/8/3N4/8/B1p1R2P/1NBQK1NR w Kkq - 0 1";
		std::string perft_position_2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";

		LegalMovesGenerator lgm;
	public:
		TEST_METHOD(LM_Rook) {
			Board b = Board(test_position_1);
			std::vector<Move> test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteRook, BoardPos("e2"));
			/*Logger::WriteMessage("Move for White Rook on e2");
			for (Move i : test_moves) {
				Logger::WriteMessage(i.get_standard_notation().c_str());
			}*/

			Assert::AreEqual(9, int(test_moves.size()));
			test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteRook, BoardPos("h1"));
			Assert::AreEqual(0, int(test_moves.size()));
		}
		TEST_METHOD(LM_Bishop) {
			
			Board b = Board(test_position_1);
			std::vector<Move> test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteBishop, BoardPos("c1"));
			Assert::AreEqual(7, int(test_moves.size()));

			test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteBishop, BoardPos("a2"));
			Assert::AreEqual(5, int(test_moves.size()));


			test_moves = lgm.get_legal_moves_for_piece(b, PieceName::BlackBishop, BoardPos("f8"));
			Assert::AreEqual(0, int(test_moves.size()));
		}
		TEST_METHOD(LM_Pawn) {
			Board b = Board(perft_position_2);
			std::vector<Move> test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhitePawn, BoardPos("d5")); 
			Assert::AreEqual(2, int(test_moves.size()));
			test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhitePawn, BoardPos("e4"));
			Assert::AreEqual(0, int(test_moves.size()));
			test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhitePawn, BoardPos("g2"));
			Assert::AreEqual(3, int(test_moves.size()));
		}
		TEST_METHOD(LM_Knight) {
			Board b = Board(perft_position_2);
			std::vector<Move> test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteKnight, BoardPos("e5"));
					
			Assert::AreEqual(7, int(test_moves.size()));
		}
		TEST_METHOD(LM_King) {
			Board b = Board(perft_position_2);
			std::vector<Move> test_moves = lgm.get_legal_moves_for_piece(b, PieceName::WhiteKing, BoardPos("e1"));

			Assert::AreEqual(4, int(test_moves.size()));
		}
	};
	
}


