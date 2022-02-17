#include "rookMove.h"

std::vector<pieceMove> rookMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::unordered_set<int> myTeam, enemyTeam;

	if (colour == WHITE) {
		myTeam = WhiteTeam;
		enemyTeam = BlackTeam;
	} else {
		myTeam = BlackTeam;
		enemyTeam = WhiteTeam;
	}

	// right of rook
	for (int col = column+1; col < BOARD_WIDTH; col++) {
		if (board[row][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, row, col));
		} else if (myTeam.count(board[row][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, row, col));
			break;
		}
	}

	// left of rook
	for (int col = column-1; col >= 0; col--) {
		if (board[row][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, row, col));
		} else if (myTeam.count(board[row][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, row, col));
			break;
		}
	}		

	// bottom of rook
	for (int ro = row+1; ro < BOARD_HEIGHT; ro++) {
		if (board[ro][column] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, column));
		} else if (myTeam.count(board[ro][column])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, column));
			break;
		}
	}

	// top of rook
	for (int ro = row-1; ro >= 0; ro--) {
		if (board[ro][column] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, column));
		} else if (myTeam.count(board[ro][column])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, column));
			break;
		}
	}

	return moves;
}