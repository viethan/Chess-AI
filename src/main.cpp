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
    // a bittt bad because no sync read/write
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
        std::srand(static_cast<unsigned int>(std::time(nullptr))); 
        return std::rand() % 2;
    }

    return n;
}

int main(int argc,char *argv[]){
   gColour = selectPlayer();
    cout << "You are ";
    if (gColour) cout << "black" << endl;
    else cout << "white" << endl;

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
    while (true) {
        SDL_Thread *thread;
        int         threadReturnValue;

    	if (!visualise()) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}

        string input;
        Move userMove;
        bool validInput = false;
        while (!validInput) {
            cin >> input;

            if (input.compare("quit") == 0) { break; }
            if (string2move(input, &userMove) && check_move(userMove, gBoardCoords, gColour)) { 
                cout << "Good move" << endl; 
                validInput = true; } 
            else {
                cout << "bad input" << endl;
            }
        }

        if (input.compare("quit") == 0) { break; }

        int** temp;
        temp = make_move(userMove, gBoardCoords);
        free_board(gBoardCoords);
        gBoardCoords = temp;

        // Let the AI choose its move

        // Perform AI's chosen move
    }

    shutEvents = true;
    SDL_WaitThread(thread, &threadReturnValue);


    close_visualise();
    close_moves();
    return 0;
}