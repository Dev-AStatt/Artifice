#include "pch.h"
#include "CppUnitTest.h"

#include "../Artifice/Move.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MoveClass) {
	public:
		
		TEST_METHOD(TestThatTestsWork) {Assert::AreEqual(1, 1);}

		TEST_METHOD(String_to_BoardID_FirstLetter_Minimum) {
			Move m = Move("a1a2");
			Assert::AreEqual(0, m.get_starting_board_ID());
		}
		TEST_METHOD(String_to_BoardID_FirstLetter_Maximum) {
			Move m = Move("h8a2");
			Assert::AreEqual(63, m.get_starting_board_ID());
		}
		TEST_METHOD(String_to_BoardID_LastLetter_Minimum) {
			Move m = Move("a1a1");
			Assert::AreEqual(0, m.get_ending_board_ID());
		}
		TEST_METHOD(String_to_BoardID_LastLetter_Maximum) {
			Move m = Move("h8h8");
			Assert::AreEqual(63, m.get_ending_board_ID());
		}
	};
}
