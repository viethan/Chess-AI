#include <iostream>
#include "visualise.h"
using namespace std;

bool gColour;

//g++ board.cpp -w -lSDL2 -lSDL2_image -o board
int main(int argc,char *argv[]){
    gColour = 1;


    if (!init_SDL()) {
    	cout << "Failed to initialize SDL" << endl;
    	return -1;
    }

    if (!loadMedia()) {
    	cout << "Failed to load media" << endl;
    	return -1;
    }

    init_board();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
    	while (SDL_PollEvent(&e)) {
    		if (e.type == SDL_QUIT) quit = true;
    	}

    	if (!visualise()) {
    		cout << "Failed to visualise" << endl;
    		return -1;
    	}
    }    

    close();
    return 0;
}