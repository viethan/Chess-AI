#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "moves.h"
#include "minimax.h"
#include "visualise.h"
using namespace std;

bool QUIT = false;

static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (QUIT == false) { 
        while (SDL_PollEvent(&e)) {}
    }

    return 1;
}

int selectPlayer() {
    int n;
    string input;
    bool validInput = false;
    
    while(!validInput) {
        cout << "Enter 0 for White, 1 for Black, 2 for Random" << endl;
        cin >> input;
        if (input.size() == 1 && 
            (input[0] == '0' || input[0] == '1' || input[0] == '2')) {
            validInput = true;
            n = input[0] - '0';
        }
    }

    if (n == 2) {
        srand(static_cast<unsigned int>(time(nullptr))); 
        return rand() % 2;
    }

    return n;
}

int** userMoves(int** board, bool colour) {
    string input;
    Move userMove;
    bool validInput = false;
    while (!validInput) {
        cin >> input;

        if (input.compare("quit") == 0) { 
            QUIT = true;
            free_board(board);
            return NULL;
        }

        if (string2move(input, &userMove) && 
            check_move(userMove, board, colour)) 
            validInput = true; 
        else cout << "bad input" << endl;
    }

    int** temp;
    temp = make_move(userMove, board);
    free_board(board);
    return temp;
}

int** AIMoves(int** board, bool colour) {
    Move AIMove = getOptimalMove(board, !colour);

    int** temp;
    temp = make_move(AIMove, board);
    free_board(board);
    SDL_Delay(3000);
    return temp;
}

int** init_main(bool colour) { 
    if (!init_SDL()) {
        cout << "Failed to initialize SDL" << endl;
        return NULL;
    }

    if (!loadMedia(colour)) {
        cout << "Failed to load media" << endl;
        return NULL;
    }

    return init_board();
}

int main(int argc,char *argv[]){
    // These will prevent our game window to be deemed unresponsive
    SDL_Thread *thread;
    int         threadReturnValue;
    thread = SDL_CreateThread(PollEvents, "Events", (void *)NULL);

    bool playerMoves;
    bool colour = selectPlayer();
    if (colour == WHITE) {
        cout << "You are white" << endl;
        playerMoves = true;
    } else { 
        cout << "You are black" << endl;
        playerMoves = false;
    }

    int** board = init_main(colour);
    if (board == NULL) return -1;

    while (!QUIT) {
        if (!visualise(board, colour)) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}

        if (playerMoves) {
            board = userMoves(board, colour);
            playerMoves = false;
        } else {
            board = AIMoves(board, colour);
            playerMoves = true;
        }
    }

    if (board != NULL) free_board(board); // technically optional
    SDL_WaitThread(thread, &threadReturnValue);
    close_visualise();
    return 0;
}