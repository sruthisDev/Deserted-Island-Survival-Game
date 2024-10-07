#include "Game.h"
#include "Location.h"

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

        }
    }
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
    SetUpGame(8, 8, 4, 4);

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

        char continuePlaying;
        std::cout << "Continue exploring? (y/n): ";
        std::cin >> continuePlaying;
        if (continuePlaying == 'n') {
            keepPlaying = false;
        }

    } while (keepPlaying);


}