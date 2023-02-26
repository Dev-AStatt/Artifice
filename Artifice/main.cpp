/*
* Artifice.cpp : This file contains the 'main' function.Program execution begins and ends there.
* 
* Artifice is a chess engine that will use the the UCI (Universal Chess Interface) to interact with other
* chess engines. The documentation for the communication protocol can be found here: https://www.shredderchess.com/download.html
* 
*/
//


#include <iostream>
#include <string>


void introduction() {
	std::cout << "Welcome to the Artifice chess engine. type 'help' for list of commands" << std::endl;
}

void list_help_commands() {
	std::cout << "01: 'uci'   - Tell the engine to communicate via UCI" << std::endl;
	std::cout << "02: 'debug' - Enter Debug Mode" << std::endl;
}


int main()
{
	std::string gui_line; //to read the command given by the GUI
	int flag = 1; //to change the value of chess squares from 'a' to 'h'

	std::cout.setf(std::ios::unitbuf);// Make sure that the outputs are sent straight away to the GUI
	introduction();

	/*
	* This is the communication between the chess engine and the program
	*/


	while (std::getline(std::cin, gui_line)) {
		
		if (gui_line == "uci") {
			//We will recieve "uci" as the first line sent to our engine telling us to use UCI mode.
			// Step 01 - Engine Idenfity
			std::cout << "id name Project Artemis" << std::endl;
			std::cout << "id author Aaron Statt" << std::endl;

			// Step 02 - Set beguinning parameters

			// Step 03 - If engine has set all paramaters and is ready respond with "uciok"
			std::cout << "uciok" << std::endl;

		}
		//This will be sent to the engine to wait of the engine is finished initializing, both
		//command and answer is required. 
		else if (gui_line == "isready") {
			std::cout << "readyok" << std::endl;
		}
		else if (gui_line == "quit") {
			std::cout << "Bye Bye" << std::endl;
			break;
		}
		// if the GUI is supporting it, tell the engine that is is
		// searching on a game that it hasn't searched on before
		else if (gui_line == "ucinewgame") {
			// nothing to do
		}

		if (gui_line.substr(0, 24) == "position startpos moves ") {

			//moves = stringsplit(Line.substr(24));
			//gm.consrtuctBoardStateFromMoves(moves);
			//std::cout << moves.size() << std::endl;
		}
		
		else if (gui_line.substr(0, 3) == "go ") {
			// Received a command like: "go wtime 300000 btime 300000 winc 0 binc 0"
			//						or: "go infinite" - infinate search
			//Expected Responce: "bestmove h7h5"
			std::cout << "bestmove e7e5" << std::endl;
			
		}
		// the engine starts sending infos about the search to the GUI
		// (only some examples are given)

		/*
		info depth 1 seldepth 0
			info score cp 13  depth 1 nodes 13 time 15 pv f1b5
			info depth 2 seldepth 2
			info nps 15937
			info score cp 14  depth 2 nodes 255 time 15 pv f1c4 f8c5
			info depth 2 seldepth 7 nodes 255
			info depth 3 seldepth 7
			info nps 26437
			info score cp 20  depth 3 nodes 423 time 15 pv f1c4 g8f6 b1c3
			info nps 41562
			...
			// here the user has seen enough and asks to stop the searching
			stop
		*/
		else if (gui_line == "stop") {
			// nothing to do
		}

		//-------------------------------------//
		//These are user commands for using the engine via CLI

		else if (gui_line == "debug") {
			//GameDebug db;
			//db.startGameDebug();
		}
		else if (gui_line == "help") {
			list_help_commands();
		}
	}



	return 0;
}


/*
<Artifice(0): id name Project Artemis
<Artifice(0): id author Aaron Statt
<Artifice(0): uciok
>Artifice(0): isready
<Artifice(0): readyok
>Artifice(0): ucinewgame
>Artifice(0): position startpos
>Artifice(0): position startpos moves d2d4
>Artifice(0): isready
<Artifice(0): readyok
>Artifice(0): go wtime 300000 btime 300000 movestogo 40
<Artifice(0): bestmove e7e5
*/

/*
* 
*/



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
