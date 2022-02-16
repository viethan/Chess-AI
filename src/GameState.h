// GameState.h
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "moves.h"
#include "minimax.h"
#include "visualise.h"
#include "forall.h"

class GameState {
	public:
		int status;
		bool usersTurn, userColour;

		GameState();
		~GameState();
		void userMoves();
		void AIMoves();
		void visualise();
		void printHistory();
	private:
		int** board;
		std::vector<string> history;

		void status_check(bool colour);
		int selectPlayer();
};

// Note: the destructor doesn't free the SDL surfaces
// associated with the current game
// This is so that the window doesn't close immediately
// after the game is over
// If called the constructor for new game, it will close it then

#endif