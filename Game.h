#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Location.h"
#include "Player.h"
#include "Utilities.h"
#include "Beach.h"
#include "Mountain.h"
#include "Jungle.h"
#include "Cave.h"
#include "Lake.h"
#include <windows.h>

using namespace std;

class Game
{

private:
    Location*** world;
    Player p;
    size_t rows, cols;
    size_t playerRow, playerCol;
    bool gameStatus;
    int numDaysToSurvive, numAnimalsToKill, numToolsToCollect;

public:
    Game();
    ~Game();

    void SetUpGame(int rows, int cols, int playerRow, int playerCol);
    void ReadDataFile(vector<vector<string>>& data);
    void SetUpGame(vector<vector<string>>& data);
    void DrawGame();
    void PlayGame();
    void GameOver();
    void WinGame();
    void calculateWinConditions(vector <vector<string>>& data);
    Location* GetLocation(string className);

};

#endif
