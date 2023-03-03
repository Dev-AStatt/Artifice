#pragma once

#include <sstream>
#include <vector>
#include <bitset>
#include "cEnums.h"

//Global Variables Because I need to. 

struct Bitboard {
    PieceName name;
    std::bitset<64> bb;
    //Bitset has a .test and a .set() and can be called like blackPawns[i]
};

class Board
{
private:
    //Vector that holds all Bitboards
    std::vector<Bitboard> all_bitboards;
    
    PieceName side_to_move = PieceName::White;
    bool K_Castle = false;
    bool Q_Castle = false;
    bool k_Castle = false;
    bool q_Castle = false;

    //Function will take in the first part of a fen string to be loaded
    //into a new board state. This is all of the charicters of the string up
    //to the first space charicter ' '. It will return false if it failed to 
    //load the string
    bool sort_fen_pieces_into_bitboards(std::string pieces_fen_string);
    //This is a sub function of load from fen string, where the input is 
    //the second string set of the fen string ' '
    //[Return] False if fails
    bool set_next_turn_from_fen(std::string fen_sec_2);
    void insert_piece_into_bb(PieceName p_name, int id);
    //[Use]: For fen string loading
    //[Input]: third string from fen string ' '
    //[Return]: False if fails
    bool set_castle_rites_from_fen(std::string fen_sec_3);
    //this will take whatever fen string is entered and reset the board to
    //that fen string
    void overwrite_board_from_FEN(std::string FEN) {
        load_FEN(FEN);
    }
    bool load_FEN(std::string FEN);
    //Fill the board vectors during class construction
    void create_bitboards();
    //Simple multiplication function for repeted 2d to 1d conversion
    int get_board_ID(int rank, int file) const {return rank * 8 + file;}
public:
    //Will Create an empty board class
    Board();
    //Will Create a board from a given fen string
    Board(std::string FEN);

    //will return a copy of all the bitboards in Board
    std::vector<Bitboard> get_copy_all_bitbords() const {return all_bitboards;};

    PieceName return_piece_at(int loc) const;




};

