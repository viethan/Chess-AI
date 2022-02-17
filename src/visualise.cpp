#include "visualise.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBoardSurface = NULL;
SDL_Surface** gPieceSurfaces = NULL;

bool init_SDL()
{
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
		std::cout << "SDL could not initialize" << std::endl;
		std::cout << "Reason: " << SDL_GetError() << std::endl;
		return 0;
	}
	
	gWindow = SDL_CreateWindow( "chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(gWindow == NULL) {
		std::cout << "Window could not be created" << std::endl; 
		std::cout << "Reason: " << SDL_GetError() << std::endl;
		return 0;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if( initted & flags != flags) {
        std::cout << "Could not init SDL_Image" << std::endl;
        std::cout << "Reason: " << IMG_GetError() << std::endl;
        return 0;
    }

	//Get window surface
	gScreenSurface = SDL_GetWindowSurface( gWindow );
	return 1;
}

bool loadMedia(bool colour)
{
	if (colour == WHITE) {
		gBoardSurface = IMG_Load("../img/wBoard.png");
	} else {
		gBoardSurface = IMG_Load("../img/bBoard.png");
	}

    if (gBoardSurface == NULL) {
        std::cout << "Could not load board img" << std::endl;
        return 0;
    }

    gPieceSurfaces = new SDL_Surface*[13];

    gPieceSurfaces[wPawn] = IMG_Load("../img/wPawn.png");
    if (gPieceSurfaces[wPawn] == NULL) {
        std::cout << "Could not load white pawn img" << std::endl;
        return 0;
    }

    gPieceSurfaces[wKnight] = IMG_Load("../img/wKnight.png");
    if (gPieceSurfaces[wKnight] == NULL) {
        std::cout << "Could not load white knight img" << std::endl;
        return 0;
    }

	gPieceSurfaces[wBishop] = IMG_Load("../img/wBishop.png");
    if (gPieceSurfaces[wBishop] == NULL) {
        std::cout << "Could not load white bishop img" << std::endl;
        return 0;
    }

    gPieceSurfaces[wRook] = IMG_Load("../img/wRook.png");
    if (gPieceSurfaces[wRook] == NULL) {
        std::cout << "Could not load white rook img" << std::endl;
        return 0;
    }

    gPieceSurfaces[wQueen] = IMG_Load("../img/wQueen.png");
    if (gPieceSurfaces[wQueen] == NULL) {
        std::cout << "Could not load white queen img" << std::endl;
        return 0;
    }

    gPieceSurfaces[wKing] = IMG_Load("../img/wKing.png");
    if (gPieceSurfaces[wKing] == NULL) {
        std::cout << "Could not load white king img" << std::endl;
        return 0;
    }


    gPieceSurfaces[bPawn] = IMG_Load("../img/bPawn.png");
    if (gPieceSurfaces[bPawn] == NULL) {
        std::cout << "Could not load black pawn img" << std::endl;
        return 0;
    }

    gPieceSurfaces[bKnight] = IMG_Load("../img/bKnight.png");
    if (gPieceSurfaces[bKnight] == NULL) {
        std::cout << "Could not load black knight img" << std::endl;
        return 0;
    }

	gPieceSurfaces[bBishop] = IMG_Load("../img/bBishop.png");
    if (gPieceSurfaces[bBishop] == NULL) {
        std::cout << "Could not load black bishop img" << std::endl;
        return 0;
    }

    gPieceSurfaces[bRook] = IMG_Load("../img/bRook.png");
    if (gPieceSurfaces[bRook] == NULL) {
        std::cout << "Could not load black rook img" << std::endl;
        return 0;
    }

    gPieceSurfaces[bQueen] = IMG_Load("../img/bQueen.png");
    if (gPieceSurfaces[bQueen] == NULL) {
        std::cout << "Could not load black queen img" << std::endl;
        return 0;
    }

    gPieceSurfaces[bKing] = IMG_Load("../img/bKing.png");
    if (gPieceSurfaces[bKing] == NULL) {
        std::cout << "Could not load black king img" << std::endl;
        return 0;
    }

	return 1;
}

void close_visualise()
{
	SDL_FreeSurface( gBoardSurface );
	gBoardSurface = NULL;

	for (int i = 1; i < 13; i++) {
		if (gPieceSurfaces[i] != NULL) 
			SDL_FreeSurface(gPieceSurfaces[i]);
	}

	delete gPieceSurfaces;
	gPieceSurfaces = NULL;
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	IMG_Quit();
	//SDL_Quit(); // gives memory leak?
}

bool visBoard(int **board, bool colour) {
	if (SDL_BlitSurface(gBoardSurface, NULL, gScreenSurface, NULL) == -1) {
        std::cout << "Error while blitting the board" << std::endl;
        return 0;
    }

    SDL_Rect dstrect;
    if (colour == WHITE) {
        for (int row = 0; row < BOARD_HEIGHT; row++) {
        	for (int column = 0; column < BOARD_WIDTH; column++) {
    			if (board[row][column] != EMPTY) {
    				dstrect.x = BORDER_OFFSET + BOARD_OFFSET * column;
    				dstrect.y = BORDER_OFFSET + BOARD_OFFSET * row;
    				dstrect.w = 75;
    				dstrect.h = 75;
        			
        			if (SDL_BlitSurface(gPieceSurfaces[board[row][column]], NULL, gScreenSurface, &dstrect) == -1 ){
            			std::cout << "Error while blitting piece" << std::endl;
            			return 0;
        			}		
        		}
        	}
        }
    } else {
    	for (int row = 7; row >= 0; row--) {
        	for (int column = 7; column >= 0; column--) {
    			if (board[row][column] != EMPTY) {
    				dstrect.x = BORDER_OFFSET + BOARD_OFFSET * (7 - column);
    				dstrect.y = BORDER_OFFSET + BOARD_OFFSET * (7 - row);
    				dstrect.w = 75;
    				dstrect.h = 75;
        			
        			if (SDL_BlitSurface(gPieceSurfaces[board[row][column]], NULL, gScreenSurface, &dstrect) == -1 ){
            			std::cout << "Error while blitting piece" << std::endl;
            			return 0;
        			}		
        		}
        	}
        }
    }

    SDL_UpdateWindowSurface(gWindow);
    return 1;
}