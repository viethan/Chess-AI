#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include "forall.h"
#include "visualise.h"
#include "moves.h"
using namespace std;

bool gColour;
bool shutEvents = false;

static int PollEvents(void *ptr)
{
    SDL_Event e;
    while (shutEvents == false) { 
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

void userMoves() {
    string input;
    Move userMove;
    bool validInput = false;
    while (!validInput) {
        cin >> input;

        if (input.compare("quit") == 0) { 
            shutEvents = true;
            return;
        }

        if (string2move(input, &userMove) && 
            check_move(userMove, gBoardCoords, gColour)) 
            validInput = true; 
        else cout << "bad input" << endl;
    }

    int** temp;
    temp = make_move(userMove, gBoardCoords);
    free_board(gBoardCoords);
    gBoardCoords = temp;
}

void AIMoves() {
    // Let the AI choose its move
    // Perform AI's chosen move
}

int main(int argc,char *argv[]){
    bool playerMoves;
    gColour = selectPlayer();
    if (gColour == WHITE) {
        cout << "You are white" << endl;
        playerMoves = true;
    } else { 
        cout << "You are black" << endl;
        playerMoves = false;
    }

    if (!init_SDL()) {
    	cout << "Failed to initialize SDL" << endl;
    	return -1;
    }

    if (!loadMedia()) {
    	cout << "Failed to load media" << endl;
    	return -1;
    }

    SDL_Thread *thread;
    int         threadReturnValue;
    thread = SDL_CreateThread(PollEvents, "Events", (void *)NULL);
    
    init_board();
    while (!shutEvents) {
        if (!visualise()) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}

        if (playerMoves) {
            userMoves();
            playerMoves = false;
        } else {
            AIMoves();
            playerMoves = true;
        }
    }

    shutEvents = true;
    SDL_WaitThread(thread, &threadReturnValue);

    close_visualise();
    close_moves();
    return 0;
}