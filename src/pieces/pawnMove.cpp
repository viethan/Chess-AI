#include "pawnMove.h"

std::vector<pieceMove> pawnMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();

	int colourLower, colourUpper;
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
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
		if (row-1 >= 0 && column-1 >= 0 && \
			! (board[row-1][column-1] == EMPTY || (colourLower <= board[row-1][column-1] && board[row-1][column-1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row-1, column-1));		
		}

		if (row-1 >= 0 && column+1 < BOARD_WIDTH && \
			! (board[row-1][column+1] == EMPTY || (colourLower <= board[row-1][column+1] && board[row-1][column+1] <= colourUpper))) {
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
		if (row+1 < BOARD_HEIGHT && column-1 >= 0 && \
			! (board[row+1][column-1] == EMPTY || (colourLower <= board[row+1][column-1] && board[row+1][column-1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row+1, column-1));		
		}

		if (row+1 < BOARD_HEIGHT && column+1 < BOARD_WIDTH && \
			! (board[row+1][column+1] == EMPTY || (colourLower <= board[row+1][column+1] && board[row+1][column+1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row+1, column+1));		
		}
	}

	return moves;
}