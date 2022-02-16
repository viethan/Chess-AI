// game.h
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "moves.h"
#include "minimax.h"
#include "visualise.h"
using namespace std;

extern bool QUIT;
extern vector<string> history;

int selectPlayer();
int** userMoves(int** board, bool colour);
int** AIMoves(int** board, bool colour);
int** init_main(bool colour);
int status_check(int** board, bool colour);



#endif