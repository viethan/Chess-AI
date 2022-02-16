#include "GameState.h"

int** init_main(bool colour);

GameState::GameState() {
    this->status = CONTINUE;
    this->userColour = selectPlayer();

    // in case the user quits at the menu
    if (this->status == CONTINUE) {    
        if (this->userColour == WHITE) this->usersTurn = true;
        else this->usersTurn = false;
        this->history = vector<string>();
        this->board = init_main(this->userColour); // colour to rotate board or not
        if (this->board == NULL) this->status = QUIT;
    }
}

GameState::~GameState() {
    // only if a game was played to begin with
    if (this->board != NULL) {
        std::cout << "Game Over!" << std::endl;
        free_board(this->board);
    }
}

int GameState::selectPlayer() {
    bool player;
    string input;
    
    while(true) {
        cout << "Enter 0 for White, 1 for Black, 2 for Random" << endl;
        cout << "Type quit in order to exit" << endl;
        cin >> input;
        
        if (input.compare("quit") == 0) { 
            this->status = QUIT;
            return -1;
        }

        if (input.size() == 1) {
            // player wants to play white/black        
            if (input[0] == '0' || input[0] == '1') {
                player = input[0] - '0';
                break; 
            }

            // player chose to play a random colour
            if (input[0] == '2') {
                srand(static_cast<unsigned int>(time(nullptr))); 
                player = rand() % 2;
                break;        
            }
        }  
    }

    if (player == WHITE) cout << "You are white" << endl;
    else cout << "You are black" << endl;
    return player;
}

void GameState::visualise() {
    visBoard(this->board, this->userColour);
}

void GameState::userMoves() {
    string input;
    Move userMove;
    
    while (true) {
        cout << "Your next move: " << endl;
        cin >> input;

        if (input.compare("quit") == 0) { 
            this->status = QUIT;
            return;
        }

        if (string2move(input, &userMove) && 
            check_move(userMove, this->board, this->userColour)) {
                if (this->userColour == WHITE) this->history.push_back("White " + input);    
                else this->history.push_back("Black " + input);

                int** newBoard;
                newBoard = make_move(userMove, this->board);
                free_board(this->board);
                this->board = newBoard;
                break;
        }

        cout << "bad input" << endl;
    }

    this->usersTurn = false;
    status_check(!this->userColour);
}

void GameState::AIMoves() {
    Move AIMove = getOptimalMove(this->board, !this->userColour);
    string srcCol(1, 'a' + AIMove.srcCol), destCol(1, 'a' + AIMove.destCol);
    string srcRow(1, '1' + (7-AIMove.srcRow)), destRow(1, '1' + (7-AIMove.destRow));
    
    if (!(this->userColour) == WHITE)
        this->history.push_back("White " + srcCol + srcRow + destCol + destRow);    
    else
        this->history.push_back("Black " + srcCol + srcRow + destCol + destRow);

    int** newBoard;
    newBoard = make_move(AIMove, board);
    free_board(board);
    this->board = newBoard;

    this->usersTurn = true;
    status_check(this->userColour);
}

void GameState::printHistory() {
    cout << "\033[2J\033[1;1H"; // clears the screen
    for (vector<string>::iterator it = history.begin(); it != history.end(); it++) {
        cout << *it << endl;
    }
}

void GameState::status_check(bool colour) {
    int newStatus = gameOver(this->board, colour);    
    
    if (newStatus != CONTINUE) {
        if (newStatus == LOSE) {
            if (colour == WHITE) history.push_back("Black wins");
            else this->history.push_back("White wins");
        } else if (newStatus == STALEMATE) {
            this->history.push_back("Stalemate");
        }
    }

    this->status = newStatus;
} 

// closes the previous game's window
// initialises SDL
// loads the media into memory
// returns a new board with default setup
int** init_main(bool colour) { 
    if (SDL_WasInit(SDL_INIT_EVERYTHING)) close_visualise();
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