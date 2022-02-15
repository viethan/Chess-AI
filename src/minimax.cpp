#include "minimax.h"

int eval(int **board) {
	int score = 0;
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int col = 0; col < BOARD_WIDTH; col++) {
			if (board[row][col] != EMPTY) {
				switch (board[row][col]) {
					case wPawn:
						score += pawnTable[row][col] + pawnVal;
						break;
					case bPawn:
						score += (pawnTable[7-row][7-col] + pawnVal) * (-1);
						break;
					case wKnight:
						score += knightTable[row][col] + knightVal;
						break;
					case bKnight:
						score += (knightTable[7-row][7-col] + knightVal) * (-1);
						break;
					case wBishop:
						score += bishopTable[row][col] + bishopVal;
						break;
					case bBishop:
						score += (bishopTable[7-row][7-col] + bishopVal) * (-1);
						break;
					case wRook:
						score += rookTable[row][col] + rookVal;
						break;
					case bRook:
						score += (rookTable[7-row][7-col] + rookVal) * (-1);
						break;
					case wQueen:
						score += queenTable[row][col] + queenVal;
						break;
					case bQueen:
						score += (queenTable[7-row][7-col] + queenVal) * (-1);
						break;
					case wKing:
						score += kingTable[row][col] + kingVal;
						break;
					case bKing:
						score += (kingTable[7-row][7-col] + kingVal) * (-1);
						break;
					}
			}
		}
	}

	return score;
}

Move getOptimalMove(int **board, bool colour) {
	MoveEval best = minimax(board, MAX_DEPTH, numeric_limits<int>::min(), numeric_limits<int>::max(), colour);
	cout << "Best Move for AI: " << best.move.srcRow << best.move.srcCol << " " << best.move.destRow << best.move.destCol << endl;
	return best.move;
}

MoveEval minimax(int **board, int depth, int alpha, int beta, bool colour) {
	if (depth == 0) return MoveEval{ Move{}, eval(board) };
	// || gameOver(board)

	MoveEval eval, compareEval = MoveEval{}; 
	if (colour == WHITE) compareEval.score = numeric_limits<int>::min(); // maximizing
	else if (colour == BLACK) compareEval.score = numeric_limits<int>::max(); // minimizing

	vector<Move> nextMoves = get_moves(board, colour);
	for (vector<Move>::iterator it = nextMoves.begin(); it != nextMoves.end(); it++) {
			int** nextBoard = make_move(*it, board);
			eval = minimax(nextBoard, depth-1, alpha, beta, !colour);
			if ((colour == WHITE && eval.score > compareEval.score) || 
				(colour == BLACK && eval.score < compareEval.score)) 
				compareEval = MoveEval{*it, eval.score};

			free_board(nextBoard);
			if (colour == WHITE) alpha = max(alpha, eval.score);
			else beta = min(beta, eval.score);
			if (beta <= alpha) break;
	}

	return compareEval;
}