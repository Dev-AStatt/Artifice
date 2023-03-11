#pragma once
class BoardPos
{
private:
	int rank;
	int file;
	int board_ID;
	std::string as_string;
public:
	BoardPos() : rank(0), file(0), board_ID(0), as_string("a8") {}
	BoardPos(int rank, int file) : rank(rank), file(file) {
		board_ID = get_board_ID(rank, file);
	}

	BoardPos(int board_ID) : board_ID(board_ID) {
		file = board_ID % 8;
		rank = int(board_ID / 8);
	}
	BoardPos(std::string single_coord) : as_string(single_coord) {
		char c = single_coord[0];
		if (0 <= int(c) - 97 <= 7) {
			file = int(c) - 97;
		} //int(char) will get us the intager value of the letter, then subtract 97 to get the number
		else { 
			file = 0;
			throw std::invalid_argument("Tried to create a BoardPos form invalid string: " + single_coord);
		}

		c = single_coord[1];
		if (c >= 49 && c <= 56) {
			rank = 8 - std::atoi(&c);
		}
		else { 
			rank = 0;
			throw std::invalid_argument("Tried to create a BoardPos form invalid string: " + single_coord);
		}
		board_ID = get_board_ID(rank, file);
		
	}
	
	//Simple multiplication function for repeted 2d to 1d conversion
	int get_board_ID(int rank, int file) const { return rank * 8 + file; }
	int get_board_ID() const { return board_ID; }
	int get_rank() const { return rank; }
	int get_file() const { return file; }
	std::string get_string() { 
		char letter = char(file + 97); 
		as_string = std::string() + letter + std::to_string(8 - rank);
		return as_string;
	}
	bool is_on_board() const {
		if (0 <= rank && rank <= 7) {
			if (0 <= file && file <= 7) {
				return true;
			}
			else { return false;}
		}
		else { return false; }
	}



};

