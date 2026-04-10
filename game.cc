#include "game.h"
#include <iostream>

Game::Game() {};

bool Game::onTheBoard(const int & row, const int & col) const {
    if( row < 0 || col < 0 || row > 7 || col > 7) {
        return false;
    }
    return true;
}

bool Game::spaceCheck(const int & row, const int & col, const bool & white) const {
    //Checks if off board or if an ally piece already occupies the space
    if(!onTheBoard(row, col) || board_[row][col].empty == false && board_[row][col].white == white) {
        return false;
    }

    return true;
}

void Game::coverSpace(const int & row, const int & col, const bool & white) {
    if(white) {
        wCovers_[row][col] = true;
    } else {
        bCovers_[row][col] = true;
    }
}


std::vector<Piece> Game::checkPawn(const Piece & pawn, bool moveList){
    std::vector<Piece> list;
    bool doubJump = false;
    int dir = pawn.white ? -1 : 1;
    int bgRow = pawn.white ? 6 : 1;

    //Pawn forward
    if(moveList && spaceCheck(pawn.row + dir, pawn.col, pawn.white)) {
        //Forward 1 space
        list.push_back(board_[pawn.row + dir][pawn.col]);
        
        //Forward 2 spaces (Pawn starting move)
        if(pawn.row == bgRow && spaceCheck(pawn.row + (2 * dir), pawn.col, pawn.white)) {
            list.push_back(board_[pawn.row + (2 * dir)][pawn.col]);
        }
    }
    
    if(moveList) {
        //Left diagonal attack
        if(spaceCheck(pawn.row + dir, pawn.col - 1, pawn.white) && board_[pawn.row + dir][pawn.col - 1].name != "") {
            list.push_back(board_[pawn.row + dir][pawn.col - 1]);
        }
    
        //Right diagonal attack
        if(spaceCheck(pawn.row + dir, pawn.col + 1, pawn.white) && board_[pawn.row + dir][pawn.col + 1].name != "") {
            list.push_back(board_[pawn.row + dir][pawn.col + 1]);
        }
    } else {
        //Pawn protects (covers) left diagonal space
        if(onTheBoard(pawn.row + dir, pawn.col - 1)){
            coverSpace(pawn.row + dir, pawn.col - 1, pawn.white);
        }
        //Pawn protects (covers) right diagonal space
        if(onTheBoard(pawn.row + dir, pawn.col + 1)){
            coverSpace(pawn.row + dir, pawn.col + 1, pawn.white);
        }
    }

    return list;
}

std::vector<Piece> Game::rookMoveList(const Piece & rook) {
    std::vector<Piece> list;
    bool left, up, right, down = true;
    int i = 1;
    while(left) {
        //Not off board and no ally piece occupies space
        if(spaceCheck(rook.row, rook.col - i, rook.white)) {
            list.push_back(board_[rook.row][rook.col - i]);
            i++;
        } else {
            i = 1;
            left = false;
        }
        //If not empty and enemy piece occupies space
        if(board_[rook.row][rook.col - i].empty == false && board_[rook.row][rook.col - i].white != rook.white) {
            list.push_back(board_[rook.row][rook.col - i]);
            i = 1;
            left = false;
        }
    }

    while(right) {
        if(spaceCheck(rook.row, rook.col + i, rook.white)) {
            list.push_back(board_[rook.row][rook.col + i]);
            i++;
        } else {
            i = 1;
            right = false;
        }

        if(board_[rook.row][rook.col + i].empty == false && board_[rook.row][rook.col + i].white != rook.white) {
            list.push_back(board_[rook.row][rook.col + i]);
            i = 1;
            right = false;
        }
    }

    while(down) {
        if(spaceCheck(rook.row - i, rook.col, rook.white)) {
            list.push_back(board_[rook.row - i][rook.col]);
            i++;
        } else {
            i = 1;
            down = false;
        }

        if(board_[rook.row - i][rook.col].empty == false && board_[rook.row - i][rook.col].white != rook.white) {
            list.push_back(board_[rook.row - i][rook.col]);
            i = 1;
            down = false;
        }
    }

    while(up) {
        if(spaceCheck(rook.row + i, rook.col, rook.white)) {
            list.push_back(board_[rook.row + i][rook.col]);
            i++;
        } else {
            i = 1;
            down = false;
        }

        if(board_[rook.row + i][rook.col].empty == false && board_[rook.row + i][rook.col].white != rook.white) {
            list.push_back(board_[rook.row + i][rook.col]);
            i = 1;
            down = false;
        }
    }

    return list;
}

void Game::rookDefends(const Piece & rook) {
    bool left, up, right, down = true;
    int i = 1;

    while(left) {
        if(onTheBoard(rook.row, rook.col - i)) {
            coverSpace(rook.row, rook.col - i, rook.white);
            i++;
        } else {
            i = 1;
            left = false;
        }

        if(board_[rook.row][rook.col - i].empty == false) {
            coverSpace(rook.row, rook.col - i, rook.white);
            i = 1;
            left = false;
        }
    }

    while(right) {
        if(onTheBoard(rook.row, rook.col + i)) {
            coverSpace(rook.row, rook.col + i, rook.white);
            i++;
        } else {
            i = 1;
            right = false;
        }

        if(board_[rook.row][rook.col + i].empty == false) {
            coverSpace(rook.row, rook.col + i, rook.white);
            i = 1;
            right = false;
        }
    }

    while(down) {
        if(onTheBoard(rook.row - i, rook.col)) {
            coverSpace(rook.row - i, rook.col, rook.white);
            i++;
        } else {
            i = 1;
            down = false;
        }

        if(board_[rook.row - i][rook.col].empty == false) {
            coverSpace(rook.row - i, rook.col, rook.white);
            i = 1;
            down = false;
        }
    }

    while(up) {
        if(onTheBoard(rook.row + i, rook.col)) {
            coverSpace(rook.row + i, rook.col, rook.white);
            i++;
        } else {
            i = 1;
            down = false;
        }

        if(board_[rook.row + i][rook.col].empty == false) {
            coverSpace(rook.row + i, rook.col, rook.white);
            i = 1;
            down = false;
        }
    }
}







void Game::printMap() {
    for(size_t i = 0; i < sizeof(board_[0]); i++){
        std::cout << "Chess Gameboard:" << std::endl;
        std::cout << "| ";
        for(size_t q = 0; q < sizeof(board_[0]); q++){
            std::cout << board_[i][q].name[0] << board_[i][q].name[1] << " |";
        }
        std::cout << "\n";

    }
}

