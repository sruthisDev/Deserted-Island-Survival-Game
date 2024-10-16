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
	int health; // reperesents player`s health.
	int water; // represents players` water level.
	bool enoughFood; // tells whether player has enough foor or not.
	int survivalDays; // tells how many days player survived.
	int numAnimalsKilled; // tells how many animals player killed.
	vector<string> tools;// it shows what tools player has.
	map<string,int> rawMaterial; //
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

