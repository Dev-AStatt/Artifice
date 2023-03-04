#pragma once
#include <vector>
#include <stdexcept>

enum class PieceName
{
    WhitePawn,
    WhiteKnight,
    WhiteBishop,
    WhiteRook,
    WhiteQueen,
    WhiteKing,
    BlackPawn,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackQueen,
    BlackKing,
    AllWhite,
    AllBlack,
    Empty,
};

enum class PieceColor
{
    White,
    Black
};

enum class PieceType
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    None,
};


class Enum_Utils {
private:
    const std::vector<PieceName> list_of_white_pieces  = {
        PieceName::WhitePawn,
        PieceName::WhiteKnight,
        PieceName::WhiteBishop,
        PieceName::WhiteRook,
        PieceName::WhiteQueen,
        PieceName::WhiteKing,
    };
    const std::vector<PieceName> list_of_black_pieces = {
        PieceName::BlackPawn,
        PieceName::BlackKnight,
        PieceName::BlackBishop,
        PieceName::BlackRook,
        PieceName::BlackQueen,
        PieceName::BlackKing,
    };

public:
    Enum_Utils() {}

    PieceColor get_color_from_name(PieceName name) const {
        if (name == PieceName::Empty   ) { throw std::invalid_argument("Recieved PieceName::Empty in get_color_from_name()"); }
        if (name == PieceName::AllWhite) { return PieceColor::White; }
        if (name == PieceName::AllBlack) { return PieceColor::Black; }

        auto result = std::find(begin(list_of_white_pieces), end(list_of_white_pieces), name);
        if (result != std::end(list_of_white_pieces)) {
            return PieceColor::White;
        }
        else { return PieceColor::Black; }
    }

    PieceType get_type_from_name(PieceName name) const {
        if (name == PieceName::WhitePawn   || name == PieceName::BlackPawn  ) { return PieceType::Pawn;   }
        if (name == PieceName::WhiteKnight || name == PieceName::BlackKnight) { return PieceType::Knight; }
        if (name == PieceName::WhiteBishop || name == PieceName::BlackBishop) { return PieceType::Bishop; }
        if (name == PieceName::WhiteRook   || name == PieceName::BlackRook  ) { return PieceType::Rook;   }
        if (name == PieceName::WhiteQueen  || name == PieceName::BlackQueen ) { return PieceType::Queen;  }
        if (name == PieceName::WhiteKing   || name == PieceName::BlackKing  ) { return PieceType::King;   }
        else { return PieceType::None; }
    }

};



