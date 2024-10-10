#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<string>
#include "Location.h"
#include "Player.h"

using namespace std;

class Game
{

private:
    Location*** world;
    Player p;
    int rows, cols;
    int playerRow, playerCol;
    bool gameStatus;

public:
    Game();
    ~Game();

    void ReadDataFile(string fileName);
    void SetUpGame(int rows, int cols, int playerRow, int playerCol);
    void DrawGame();
    void PlayGame();


};

#endif
