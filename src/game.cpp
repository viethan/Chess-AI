#include "game.h"

int selectPlayer() {
    int n;
    string input;
    bool validInput = false;
    
    while(!validInput) {
        cout << "Enter 0 for White, 1 for Black, 2 for Random" << endl;
        cout << "Type quit in order to exit" << endl;
        cin >> input;
        if (input.size() == 1 && 
            (input[0] == '0' || input[0] == '1' || input[0] == '2')) {
            validInput = true;
            n = input[0] - '0';
        } else if (input.compare("quit") == 0) { 
            QUIT = true;
            return -1;
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
        cout << "Your next move: " << endl;
        cin >> input;

        if (input.compare("quit") == 0) { 
            QUIT = true;
            return board;
        }

        if (string2move(input, &userMove) && 
            check_move(userMove, board, colour)) 
            validInput = true; 
        else cout << "bad input" << endl;
    }

    if (colour == WHITE) {
        history.push_back("White " + input);    
    } else {
        history.push_back("Black " + input);
    }
    

    int** temp;
    temp = make_move(userMove, board);
    free_board(board);
    return temp;
}

int** AIMoves(int** board, bool colour) {
    Move AIMove = getOptimalMove(board, colour);
    string srcCol(1, 'a' + AIMove.srcCol), destCol(1, 'a' + AIMove.destCol);
    string srcRow(1, '1' + (7-AIMove.srcRow)), destRow(1, '1' + (7-AIMove.destRow));
    
    if (colour == WHITE) {
        history.push_back("White " + srcCol + srcRow + destCol + destRow);    
    } else {
        history.push_back("Black " + srcCol + srcRow + destCol + destRow);
    }

    int** temp;
    temp = make_move(AIMove, board);
    free_board(board);
    //SDL_Delay(3000);
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

int status_check(int** board, bool colour) {
    int status = gameOver(board, colour);    
    if (status != CONTINUE) {
        if (status == LOSE) {
            if (colour == WHITE) history.push_back("Black wins");
            else history.push_back("White wins");
        } else if (status == STALEMATE) {
            history.push_back("Stalemate");
        }
    }

    return status;
} 