#include "kingMove.h"

std::vector<pieceMove> kingMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::unordered_set<int> myTeam, enemyTeam;

	if (colour == WHITE) {
		myTeam = WhiteTeam;
		enemyTeam = BlackTeam;
	} else {
		myTeam = BlackTeam;
		enemyTeam = WhiteTeam;
	}

	if (row+1 < BOARD_HEIGHT) {
		// bottom
		if (myTeam.count(board[row+1][column]) == 0) {
			moves.push_back(pieceMove(row, column, row+1, column));
		}
		// bottom-left
		if (column-1 >= 0 && myTeam.count(board[row+1][column-1]) == 0) {
			moves.push_back(pieceMove(row, column, row+1, column-1));
		}
		// bottom-right
		if (column+1 < BOARD_WIDTH && myTeam.count(board[row+1][column+1]) == 0) {
			moves.push_back(pieceMove(row, column, row+1, column+1));
		}
	}

	if (row-1 >= 0) {
		// upper
		if (myTeam.count(board[row-1][column]) == 0) {
			moves.push_back(pieceMove(row, column, row-1, column));
		}
		// upper-left
		if (column-1 >= 0 && myTeam.count(board[row-1][column-1]) == 0) {
			moves.push_back(pieceMove(row, column, row-1, column-1));
		}
		// upper-right
		if (column+1 < BOARD_WIDTH && myTeam.count(board[row-1][column+1]) == 0) {
			moves.push_back(pieceMove(row, column, row-1, column+1));
		}
	}

	// left
	if (column-1 >= 0 && myTeam.count(board[row][column-1]) == 0) {
			moves.push_back(pieceMove(row, column, row, column-1));
	}
	// right
	if (column+1 < BOARD_WIDTH && myTeam.count(board[row][column+1]) == 0) {
			moves.push_back(pieceMove(row, column, row, column+1));
	}

	return moves;
}



