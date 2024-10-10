
#include "Game.h"
#include "Location.h"
#include"Beach.h"
#include"Mountain.h"
#include"Jungle.h"
#include"Cave.h"
#include"Lake.h"

Game::Game() {
    world = nullptr;
    rows = 0;
    cols = 0;
    playerRow = 0;
    playerCol = 0;
    gameStatus = true;
}
Game::~Game() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete world[i][j];
        }
        delete[] world[i];
    }
    delete[] world;
}

void Game::ReadDataFile(string fileName) {

}
void Game::SetUpGame(int userRows, int userCols, int userPlayerRow, int userPlayerCol) {
    rows = userRows;
    cols = userCols;
    playerRow = userPlayerRow;
    playerCol = userPlayerCol;
    world = new Location * *[rows];
    for (int i = 0; i < rows; ++i) {
        world[i] = new Location * [cols];
        for (int j = 0; j < cols; ++j) {

            world[i][j] = new Location();

            if (i == 0 ||  i == 5) {
                world[i][j] = new Beach();
            }
            
            if (i == 1 || i == 3) {
                world[i][j] = new Mountain();
            }

            if (i == 2) {
                world[i][j] = new Cave();
            }

            

        }
    }
    /*
    if (i == 2) {
                world[i][j] = new Jungle();
            }
            if (i == 4) {
                world[i][j] = new Cave();
            }
            if (i == 5) {
                world[i][j] = new Lake();
            }
    world[1][2] = new Beach();
    world[2][2] = new Jungle();
    world[3][3] = new Mountain();
    world[3][4] = new Cave();
    world[4][5] = new Lake();*/
}

void Game::DrawGame() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == playerRow && j == playerCol) {
                cout << "P";
            }
            else {
                world[i][j]->draw();
            }
        }
        cout << endl;
    }    
}
void Game::PlayGame() {
    SetUpGame(10, 10, 4, 5);

    char move;
    bool keepPlaying = true;
    do {
        DrawGame();

        std::cout << "Move (WASD): ";
        std::cin >> move;


        switch (move) {
        case 'w':
            if (playerRow > 0) --playerRow;
            break;
        case 's':
            if (playerRow < rows - 1) ++playerRow;
            break;
        case 'a':
            if (playerCol > 0) --playerCol;
            break;
        case 'd':
            if (playerCol < cols - 1) ++playerCol;
            break;
        }

        world[playerRow][playerCol]->visit(p);
        p.PrintStatus();
        p.SetSurvivalDays(1);
        if (p.CheckWinConditions()) {
            std::cout << "Game Over: You won!\n";
            break;
        }
        char continuePlaying;
        std::cout << "Continue exploring? (y/n): ";
        std::cin >> continuePlaying;
        if (continuePlaying == 'n') {
            keepPlaying = false;
        }

    } while (keepPlaying);


}