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

using namespace std;

class Game
{

private:
    Location*** world; // 2D loctions pointer 
    Player p; //player`s object
    size_t rows, cols; // grid size
    size_t playerRow, playerCol; // player`s position
    bool gameStatus, regularWinCondition; // status of the game
    int numDaysToSurvive, numAnimalsToKill, numToolsToCollect;
    int waterPerMove, dmgWhenHungryPerMove , dmgWhenThirstyPerMove;

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
    bool CheckWinConditions(Player& p);
    Location* GetLocation(string className);

};

#endif
