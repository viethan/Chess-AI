#include "knightMove.h"

std::vector<pieceMove> knightMove::findMoves(int** board, int row, int column, bool colour) {
	std::vector<pieceMove> moves = std::vector<pieceMove>();
	std::unordered_set<int> myTeam, enemyTeam;

	if (colour == WHITE) {
		myTeam = WhiteTeam;
		enemyTeam = BlackTeam;
	} else {
		myTeam = BlackTeam;
		enemyTeam = WhiteTeam;
	}

	// Can physically do the move, and it's not in our team
	int ro, col;

	// upper-left1
	ro = row - 2;
	col = column - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// upper-left2
	ro = row - 1;
	col = column - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// upper-right1
	ro = row - 2;
	col = column + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// upper-right2
	ro = row - 1;
	col = column + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// bottom-left1
	ro = row + 2;
	col = column - 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// bottom-left2
	ro = row + 1;
	col = column - 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// bottom-right1
	ro = row + 2;
	col = column + 1;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	// bottom-right2
	ro = row + 1;
	col = column + 2;
	if (0 <= ro && ro < BOARD_HEIGHT && 0 <= col && col < BOARD_WIDTH && // physically can move
		myTeam.count(board[ro][col]) == 0) { // must not be on the same team
			moves.push_back(pieceMove(row, column, ro, col));
	}

	return moves;
}