// forall.h
#ifndef FORALL_H
#define FORALL_H

enum Pieces { wPawn = 1, wKnight, wBishop, wRook, wQueen, wKing, bPawn, bKnight, bBishop, bRook, bQueen, bKing };
extern bool gColour; // 0 for white, 1 for black
extern int** gBoardCoords;

#endif