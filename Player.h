#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<string>
#include<iostream>

using namespace std;

class Player
{
private:
	int health;
	int water; // remove if not req
	int food;
	int survivalDays;
	int numAnimalsKilled;
	vector<string> tools;
	vector<string> rawMaterial;
	bool HasfoundMysteryPlace;

public:

	Player();
	
	void SetPlayerHealth(int health);
	int GetPlayerHealth();
	
	void SetWater(int water);
	int GetWater();

	void SetSurvivalDays(int survivalDays);
	int GetSurvivalDays();
	
	void SetNumAnimalsKilled(int numAnimalsKilled);
	int GetNumAnimalsKilled();
	
	void CraftTools();
	void AddTools(string toolName); // remove it if rew bcz in craft tools u can add it to the tool vector
	int GetNumOfTools();

	void CollectRawMaterial(vector<string>  rawMaterial);
	void PrintStatus();
	bool CheckWinConditions();

	void foundMysteryPlace();
	bool HasVisitedMysteryPlace();


};

#endif

