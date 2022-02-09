// visualise.h
#ifndef VISUALISE_H
#define VISUALISE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "forall.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

const int BORDER_OFFSET = 18;
const int BOARD_OFFSET = 75;

extern bool gColour;

//The window we'll be rendering to
extern SDL_Window* gWindow;
//The surface contained by the window
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gBoardSurface;
extern SDL_Surface** gPieceSurfaces;

// Starts up SDL and creates window
bool init_SDL();
// Loads board and chess images
bool loadMedia();
// Frees media and shuts down SDL
void close_visualise();
// Make the current board appear in the window
bool visualise();

#endif