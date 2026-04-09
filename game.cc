#include "game.h"
#include <iostream>

Game::Game() {
    //Make board

};

bool Game::onTheBoard(const int & row, const int & col) const {
    if( row < 0 || col < 0 || row > 7 || col > 7) {
        return false;
    }
    return true;
}

bool Game::spaceCheck(const int & row, const int & col, const bool & white) const {
    //Checks if off board or if an ally piece already occupies the space
    if(!onTheBoard(row, col) || board_[row][col].white == white) {
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

