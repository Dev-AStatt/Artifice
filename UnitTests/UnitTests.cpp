#include "pch.h"
#include "CppUnitTest.h"

#include "../Artifice/Move.cpp"
#include "../Artifice/cEnums.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArtificeUnitTests
{
	TEST_CLASS(MoveClass) {
	public:
		
		TEST_METHOD(TestThatTestsWork) {Assert::AreEqual(1, 1);}


		TEST_METHOD(String_To_Board_ID) {
			Move m_1 = Move("a1a1");
			Move m_2 = Move("h8h8");
			
			Assert::AreEqual(56, m_1.get_starting_board_ID());
			Assert::AreEqual(56, m_1.get_ending_board_ID());
			Assert::AreEqual(7, m_2.get_starting_board_ID());
			Assert::AreEqual(7, m_2.get_ending_board_ID());
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
}


