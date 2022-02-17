#include "pawnMove.h"

std::vector<pieceMove> pawnMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::unordered_set<int> myTeam, enemyTeam;
	int colourLower, colourUpper;
	if (colour == WHITE) {
		myTeam = WhiteTeam;
		enemyTeam = BlackTeam;
	} else {
		myTeam = BlackTeam;
		enemyTeam = WhiteTeam;
	}

	if (colour == WHITE) {
		// move one square forward
		if (row-1 >= 0 && board[row-1][column] == EMPTY) {
			moves.push_back(pieceMove(row, column, row-1, column));
			// move two squares forward
			if (row == 6 && board[4][column] == EMPTY) {
				moves.push_back(pieceMove(row, column, 4, column));
			} 
		}

		// attack diagonally
		if (row-1 >= 0 && column-1 >= 0 && 
			enemyTeam.count(board[row-1][column-1])) {
			moves.push_back(pieceMove(row, column, row-1, column-1));		
		}

		if (row-1 >= 0 && column+1 < BOARD_WIDTH && 
			enemyTeam.count(board[row-1][column+1])) {
			moves.push_back(pieceMove(row, column, row-1, column+1));		
		}
	} else {
		// move one square forward
		if (row+1 < BOARD_HEIGHT && board[row+1][column] == EMPTY) {
			moves.push_back(pieceMove(row, column, row+1, column));
			// move two squares forward
			if (row == 1 && board[3][column] == EMPTY) {
				moves.push_back(pieceMove(row, column, 3, column));
			}
		}

		// attack diagonally
		if (row+1 < BOARD_HEIGHT && column-1 >= 0 && 
			enemyTeam.count(board[row+1][column-1])) {
			moves.push_back(pieceMove(row, column, row+1, column-1));		
		}

		if (row+1 < BOARD_HEIGHT && column+1 < BOARD_WIDTH && 
			enemyTeam.count(board[row+1][column+1])) {
			moves.push_back(pieceMove(row, column, row+1, column+1));		
		}
	}

	return moves;
}