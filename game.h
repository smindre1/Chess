#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <vector>


struct Piece {
    bool empty;
    bool white;
    std::string name;
    int row;
    int col;
};

class Game {
    private:

        //wTeaam and bTeam, vectors of Pieces, (pos, white bool, name)

        // Initializes Game Board
        Piece board_[8][8] = {
            {{false, false, "Rook", 0, 0}, {false, false, "Knight", 0, 1}, {false, false, "Bishop", 0, 2}, {false, false, "Queen", 0, 3}, {false, false, "King", 0, 4}, {false, false, "Bishop", 0, 5}, {false, false, "Knight", 0, 6}, {false, false, "Rook", 0, 7}},

            {{false, false, "Pawn", 1, 0}, {false, false, "Pawn", 1, 1}, {false, false, "Pawn", 1, 2}, {false, false, "Pawn", 1, 3}, {false, false, "Pawn", 1, 4}, {false, false, "Pawn", 1, 5}, {false, false, "Pawn", 1, 6}, {false, false, "Pawn", 1, 7}},

            {{true, false, "", 2, 0}, {true, false, "", 2, 1}, {true, false, "", 2, 2}, {true, false, "", 2, 3}, {true, false, "", 2, 4}, {true, false, "", 2, 5}, {true, false, "", 2, 6}, {true, false, "", 2, 7}},

            {{true, false, "", 3, 0}, {true, false, "", 3, 1}, {true, false, "", 3, 2}, {true, false, "", 3, 3}, {true, false, "", 3, 4}, {true, false, "", 3, 5}, {true, false, "", 3, 6}, {true, false, "", 3, 7}},

            {{true, false, "", 4, 0}, {true, false, "", 4, 1}, {true, false, "", 4, 2}, {true, false, "", 4, 3}, {true, false, "", 4, 4}, {true, false, "", 4, 5}, {true, false, "", 4, 6}, {true, false, "", 4, 7}},

            {{true, false, "", 5, 0}, {true, false, "", 5, 1}, {true, false, "", 5, 2}, {true, false, "", 5, 3}, {true, false, "", 5, 4}, {true, false, "", 5, 5}, {true, false, "", 5, 6}, {true, false, "", 5, 7}},

            {{false, true, "Pawn", 6, 0}, {false, true, "Pawn", 6, 1}, {false, true, "Pawn", 6, 2}, {false, true, "Pawn", 6, 3}, {false, true, "Pawn", 6, 4}, {false, true, "Pawn", 6, 5}, {false, true, "Pawn", 6, 6}, {false, true, "Pawn", 6, 7}, },

            {{false, true, "Rook", 7, 0}, {false, true, "Knight", 7, 1}, {false, true, "Bishop", 7, 2}, {false, true, "Queen", 7, 3}, {false, true, "King", 7, 4}, {false, true, "Bishop", 7, 5}, {false, true, "Knight", 7, 6}, {false, true, "Rook", 7, 7}}
        };

        bool wCovers_[8][8] = {
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {true, true, true, true, true, true, true, true},
            {true, true, true, true, true, true, true, true},
            {false, false, true, true, true, true, false, false}
        };
        bool bCovers_[8][8];
        //create the array
        bool wCheck_ = false;
        bool bCheck_ = false;
        bool wCheckmate_ = false;
        bool bCheckmate_ = false;
    public:

        Game();

        //Updates the 'covers' 2D array for the specific color team
        // if moveList is true then an array of possible moves for the Piece given in the parameter is returned
        // else and empty array is returned

        std::vector<Piece> checkPawn(const Piece & x, bool moveList);
        std::vector<Piece> rookMoveList(const Piece & x);
        void rookDefends(const Piece & x);
        std::vector<Piece> checkBishop(const Piece & x, bool moveList);
        std::vector<Piece> checkQueen(const Piece & x, bool moveList);
        std::vector<Piece> checkKing(const Piece & x, bool moveList);

        //If the pawn makes it to the end of the board, then promote it
        void promotePawn(Piece & x);

        //Checks if a move is on the board or goes off the board
        bool onTheBoard(const int & row, const int & col) const;

        //Checks if a move is on the board or goes off the board, and if it is already occupied by an ally piece
        bool spaceCheck(const int & row, const int & col, const bool & white) const;

        //Covers a space for bCovers_ or wCovers_ 2D arrays
        void coverSpace(const int & row, const int & col, const bool & white);

        //Checks if the king is checked and updates private member
        bool checked(const Piece & x);

        //Checks if the king is checked and cannot move
        //If so it ends the game
        bool checkmate(const Piece & x);

        // Moves the selected piece based on piece move list
        void move(const Piece & x);

        void printMap();
};
