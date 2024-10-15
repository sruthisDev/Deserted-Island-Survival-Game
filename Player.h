#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<string>
#include<iostream>
#include<map>

using namespace std;

class Player
{
private:
	int health;
	int water; // remove if not req
	bool enoughFood;
	int survivalDays;
	int numAnimalsKilled;
	vector<string> tools;
	map<string,int> rawMaterial;
	bool HasfoundMysteryPlace;

public:

	Player();
	
	void CraftTools();
	void AddTools(string toolName); // remove it if rew bcz in craft tools u can add it to the tool vector
	size_t GetNumOfTools();

	void CollectRawMaterial(vector<string>  rawMaterial);
	void PrintStatus();
	bool CheckWinConditions();


	//Setters and Getters
	void SetPlayerHealth(int health);
	int  GetPlayerHealth();

	void SetWater(int water);
	int  GetWater();

	void SetSurvivalDays(int survivalDays);
	int  GetSurvivalDays();

	void SetNumAnimalsKilled(int numAnimalsKilled);
	int  GetNumAnimalsKilled();

	void SetEnoughFood(bool enoughFood);
	bool GetEnoughFood();

	void foundMysteryPlace();
	bool HasVisitedMysteryPlace();


};

#endif

