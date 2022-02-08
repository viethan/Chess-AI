#include "moves.h"

int** gBoardCoords = NULL;

void init_board() {
	gBoardCoords = new int*[8];

	for (int i = 0; i < 8; i++) {
		switch (i) {
			case 0:
				gBoardCoords[i] = new int[8]{bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook};
				break;
			case 1:
				gBoardCoords[i] = new int[8]{bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn};
				break;
			case 6:
				gBoardCoords[i] = new int[8]{wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn};
				break;
			case 7:
				gBoardCoords[i] = new int[8]{wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook};
				break;
			default:
				gBoardCoords[i] = new int[8]{0, 0, 0, 0, 0, 0, 0, 0}; 	 	
		}		
	}
}

void close_moves() {
	for (int i = 0; i < 8; i++) {
		delete gBoardCoords[i];
	}
	delete gBoardCoords;
}