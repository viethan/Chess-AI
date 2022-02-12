#include "minimax.h"

int eval(int **board) {
	return 0;
}

Move getOptimalMove(int **board, bool colour) {
	std::vector<Move> availableMoves;
    availableMoves = get_moves(board, colour);

    return availableMoves[availableMoves.size() / 2];
}