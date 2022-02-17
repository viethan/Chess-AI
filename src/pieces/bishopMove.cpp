#include "bishopMove.h"

std::vector<pieceMove> bishopMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::unordered_set<int> myTeam, enemyTeam;

	if (colour == WHITE) {
		myTeam = WhiteTeam;
		enemyTeam = BlackTeam;
	} else {
		myTeam = BlackTeam;
		enemyTeam = WhiteTeam;
	}

	int ro, col;

	// top-right diagonal
	ro = row - 1;
	col = column + 1;

	while (ro >= 0 && col < BOARD_WIDTH) {
		if (board[ro][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, col));
		} else if (myTeam.count(board[ro][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, col));
			break;
		}

		ro--; col++;
	}

	// bottom-left diagonal
	ro = row + 1;
	col = column - 1;

	while (ro < BOARD_HEIGHT && col >= 0) {
		if (board[ro][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, col));
		} else if (myTeam.count(board[ro][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, col));
			break;
		}
		
		ro++; col--;
	}

	// top-left diagonal
	ro = row - 1;
	col = column - 1;

	while (ro >= 0 && col >= 0) {
		if (board[ro][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, col));
		} else if (myTeam.count(board[ro][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, col));
			break;
		}
		
		ro--; col--;
	}

	// bottom-right diagonal
	ro = row + 1;
	col = column + 1;

	while (ro < BOARD_HEIGHT && col < BOARD_WIDTH) {
		if (board[ro][col] == EMPTY) { // empty square
			moves.push_back(pieceMove(row, column, ro, col));
		} else if (myTeam.count(board[ro][col])) { // same colour
			break;
		} else { // first enemy encountered on the path
			moves.push_back(pieceMove(row, column, ro, col));
			break;
		}
		
		ro++; col++;
	}

	return moves;
}