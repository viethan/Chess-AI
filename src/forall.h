// forall.h
#ifndef FORALL_H
#define FORALL_H

#include <unordered_set>

enum Pieces { EMPTY, wPawn, wKnight, wBishop, wRook, wQueen, wKing, bPawn, bKnight, bBishop, bRook, bQueen, bKing };
enum Colour { WHITE = 0, BLACK = 1 };
enum GAME { CONTINUE, WIN, LOSE, STALEMATE, QUIT };
const std::unordered_set<int> WhiteTeam = {wPawn, wKnight, wBishop, wRook, wQueen, wKing};
const std::unordered_set<int> BlackTeam = {bPawn, bKnight, bBishop, bRook, bQueen, bKing};  
const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

#endif