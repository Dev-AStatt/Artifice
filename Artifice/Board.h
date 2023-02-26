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

    //Starting FEN string for new games
    
public:
    int side_to_move = enumPiece::nWhite;
    bool K_Castle = false;
    bool Q_Castle = false;
    bool k_Castle = false;
    bool q_Castle = false;

    Board();


    // getAllBB will capture and return the current states of all bit boards
    std::vector<std::bitset<64>*>& get_all_bitboards();

    void start_with_FEN(std::string FEN = new_game_FEN) {
        load_FEN(FEN);
    }

    bool load_FEN(std::string FEN);

    int return_piece_at(int loc);

    int get_board_ID(int r, int f) {
        return r * 8 + f;
    }


};

