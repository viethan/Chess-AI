#include "kingMove.h"

std::vector<pieceMove> kingMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	int colourLower, colourUpper;
	
	if (colour == WHITE) {
		colourLower = 1;
		colourUpper = 6;
	} else {
		colourLower = 7;
		colourUpper = 12;
	}

	if (row+1 < BOARD_HEIGHT) {
		// bottom
		if (!(colourLower <= board[row+1][column] && board[row+1][column] <= colourUpper)) {
			moves.push_back(pieceMove(row, column, row+1, column));
		}
		// bottom-left
		if (column-1 >= 0 && (!(colourLower <= board[row+1][column-1] && board[row+1][column-1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row+1, column-1));
		}
		// bottom-right
		if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row+1][column+1] && board[row+1][column+1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row+1, column+1));
		}
	}

	if (row-1 >= 0) {
		// upper
		if (!(colourLower <= board[row-1][column] && board[row-1][column] <= colourUpper)) {
			moves.push_back(pieceMove(row, column, row-1, column));
		}
		// upper-left
		if (column-1 >= 0 && (!(colourLower <= board[row-1][column-1] && board[row-1][column-1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row-1, column-1));
		}
		// upper-right
		if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row-1][column+1] && board[row-1][column+1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row-1, column+1));
		}
	}

	// left
	if (column-1 >= 0 && (!(colourLower <= board[row][column-1] && board[row][column-1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row, column-1));
	}
	// right
	if (column+1 < BOARD_WIDTH && (!(colourLower <= board[row][column+1] && board[row][column+1] <= colourUpper))) {
			moves.push_back(pieceMove(row, column, row, column+1));
	}

	return moves;
}



