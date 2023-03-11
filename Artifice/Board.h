#pragma once

#include <sstream>
#include <vector>
#include <bitset>
#include "cEnums.h"

#include "Move.h"

//Global Variables Because I need to. 

struct Bitboard {
    PieceName name;
    std::bitset<64> bb;
    //Bitset has a .test and a .set() and can be called like blackPawns[i]
};

struct EnPassant {
    bool able;
    BoardPos target_square;
};

class Board
{
private:
    
    //Vector that holds bitboards of single pieces
    std::vector<Bitboard> piece_bitboards;
    std::vector<Bitboard> side_bitboards;
    
    PieceColor side_to_move = PieceColor::White;
    bool K_Castle = false;
    bool Q_Castle = false;
    bool k_Castle = false;
    bool q_Castle = false;
    EnPassant board_en_passant;

    

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
    bool set_en_passant_from_fen(std::string fen_sec_4);
    void overwrite_board_from_FEN(std::string FEN) {
        load_FEN(FEN);
    }
    bool load_FEN(std::string FEN);
    //Fill the board vectors during class construction
    void create_bitboards();
    //call this after every change to a bitboard, to update the bitboards
    //that are combinations of other bitboards like sides.
    bool insert_piece_into_side_bb(PieceName p_name, int board_id);

    bool update_mesh_boards();
    

    //Simple multiplication function for repeted 2d to 1d conversion
    int get_board_ID(int rank, int file) const {return rank * 8 + file;}
public:
    //Will Create an empty board class
    Board();
    //Will Create a board from a given fen string
    Board(std::string FEN);

    //will return a copy of all the bitboards in Board
    std::vector<Bitboard> get_copy_all_bitbords() const {return piece_bitboards;};
    PieceColor get_side_to_move() const { return side_to_move; }
    bool can_white_castle_kingside() const { return K_Castle; }
    bool can_white_castle_queenside() const { return Q_Castle; }
    bool can_black_castle_kingside() const { return k_Castle; }
    bool can_black_castle_queenside() const { return q_Castle; }
    EnPassant can_enpassant() const{ return board_en_passant; }
    void flip_side_to_move();

    PieceName get_piece_at(int loc) const;
    PieceName get_piece_at(BoardPos pos) const;

    //This will only return one or the other black or white bitboards, so dont pass
    //in anything weird, or your just going to get hte black bitboard back. 
    Bitboard get_copy_side_bitboard(PieceColor color) const;
    //will return false if cannot make move
    bool make_move(Move move);
    

};

