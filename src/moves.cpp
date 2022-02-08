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

int** copy_board(int **board) {
	int** copy = new int*[8];
	for (int i = 0; i < 8; i++) {
		copy[i] = new int[8];
	}

	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			copy[row][column] = board[row][column];
		}
	}

	return copy;
}


int** make_move(int srcRow, int srcCol, int destRow, int destCol, int** board) {
	srcRow = 7 - srcRow;
	destRow = 7 - destRow;

	int **newBoard = copy_board(board);
	newBoard[destRow][destCol] = newBoard[srcRow][srcCol]; 
	newBoard[srcRow][srcCol] = 0;

	return newBoard;
}

void free_board(int** board) {
	for (int i = 0; i < 8; i++) {
		delete board[i];
	}
	delete board;
}