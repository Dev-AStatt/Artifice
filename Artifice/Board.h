#pragma once

#include <sstream>
#include <vector>
#include <bitset>
#include "cEnums.h"

//Global Variables Because I need to. 
static const std::string new_game_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Board
{
private:
    //Vector that holds all Bitboards
    std::vector<std::bitset<64>*> all_bitboards;
    std::vector<PieceName> all_piece_names;
 //BitBoards
    //--White Pieces
    std::bitset<64> whitePawns;
    std::bitset<64> whiteKnights;
    std::bitset<64> whiteBishops;
    std::bitset<64> whiteRooks;
    std::bitset<64> whiteQueens;
    std::bitset<64> whiteKings;
    //--Black Pieces
    std::bitset<64> blackPawns;
    std::bitset<64> blackKnights;
    std::bitset<64> blackBishops;
    std::bitset<64> blackRooks;
    std::bitset<64> blackQueens;
    std::bitset<64> blackKings;

    //Bit board for all white or all black pieces
    std::bitset<64> allWhite;
    std::bitset<64> allBlack;
    //Bitset has a .test and a .set() and can be called like blackPawns[i]

    //Function will take in the first part of a fen string to be loaded
    //into a new board state. This is all of the charicters of the string up
    //to the first space charicter ' '. It will return false if it failed to 
    //load the string
    bool sort_fen_pieces_into_bitboards(std::string pieces_fen_string);
    //This is a sub function of load from fen string, where the input is 
    //the second string set of the fen string ' '
    //[Return] False if fails
    bool set_next_turn_from_fen(std::string fen_sec_2);
    //[Use]: For fen string loading
    //[Input]: third string from fen string ' '
    //[Return]: False if fails
    bool set_castle_rites_from_fen(std::string fen_sec_3);

public:
    PieceName side_to_move = PieceName::White;
    bool K_Castle = false;
    bool Q_Castle = false;
    bool k_Castle = false;
    bool q_Castle = false;

    Board();

    // getAllBB will capture and return the current states of all bit boards
    std::vector<std::bitset<64>*>& get_all_bitboards() const;

    void start_with_FEN(std::string FEN = new_game_FEN) {
        load_FEN(FEN);
    }

    bool load_FEN(std::string FEN);

    

    

    PieceName return_piece_at(int loc) const;

    int get_board_ID(int r, int f) const {
        return r * 8 + f;
    }


};

