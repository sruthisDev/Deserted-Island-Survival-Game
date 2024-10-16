#include "Player.h"
#include <iomanip> 

Player::Player() {
	this->health = 100;
	this->water = 100;
	this->enoughFood = true;
	this->survivalDays = 0;
	this->numAnimalsKilled= 0;
	this->HasfoundMysteryPlace = false;
	this->tools;
}

//sets the player`s health
void Player::SetPlayerHealth(int userHealth) {
	this->health = userHealth;
}

// get`s the player`s health 
int Player::GetPlayerHealth() {
	return health;
}

// set`s player`s water
void Player::SetWater(int userWater) {
	this->water = userWater;
}

//get`s player`s water
int Player::GetWater() {
	return this->water;
}


void Player::SetSurvivalDays(int userSurvivalDays) {
	this->survivalDays += userSurvivalDays;
}


int Player::GetSurvivalDays() {
	return this->survivalDays;
}

void Player::SetNumAnimalsKilled(int userNumAnimalsKilled) {
	this->numAnimalsKilled += userNumAnimalsKilled;
}
int Player::GetNumAnimalsKilled() {
	return this->numAnimalsKilled;
}

void Player::CraftTools() {

	//auto woodIter = std::find(rawMaterial.begin(), rawMaterial.end(), "wood");
	//auto stoneIter = std::find(rawMaterial.begin(), rawMaterial.end(), "stones");

	//if (woodIter != rawMaterial.end() && stoneIter != rawMaterial.end()) {
	//	tools.push_back("hammer");
	//	rawMaterial.erase(woodIter);  
	//	stoneIter = std::find(rawMaterial.begin(), rawMaterial.end(), "stones");
	//	rawMaterial.erase(stoneIter);  

	//	std::cout << "Crafted a hammer using wood and stone.\n";
	//}
}

void Player::AddTools(string userToolName) {
	this->tools.push_back(userToolName);
}
size_t Player::GetNumOfTools() {
	return this->tools.size();
}

void Player::CollectRawMaterial(vector<string>  items) {
	
	for(size_t i=0; i< items.size(); i++){
		if (this->rawMaterial.count(items[i]) > 0) {
			this->rawMaterial[items[i]]++;	//Add number of resources
		}
		else {
			this->rawMaterial[items[i]] = 1; //First time resource
		}
	}
}

void Player::PrintStatus() {


	cout << "GAME STATUS: " << endl;
	int metricWidth = 20;  
	int valueWidth = 10;  

	cout << "+-------------------+---------+\n";
	cout << "| " << left << setw(metricWidth - 2) << "Metric" << "| " << setw(valueWidth - 2) << "Current" << "|\n";
	cout << "+-------------------+---------+\n";

	cout << "| " << left << setw(metricWidth - 2) << "Player Health" << "| " << setw(valueWidth - 2) << GetPlayerHealth() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Player Water" << "| " << setw(valueWidth - 2) << GetWater() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Has Food for Today" << "| " << setw(valueWidth - 2) << GetEnoughFood() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Tools Collected" << "| " << setw(valueWidth - 2) << GetNumOfTools() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Animals Killed" << "| " << setw(valueWidth - 2) << GetNumAnimalsKilled() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Days Survived" << "| " << setw(valueWidth - 2) << GetSurvivalDays() << "|\n";

	cout << "+-------------------+---------+\n";
}

bool Player::CheckWinConditions() {

	//if (GetNumOfTools() >= 5 && GetSurvivalDays() >= 30 && GetNumAnimalsKilled() >= 10 && HasVisitedMysteryPlace())
	if (GetNumOfTools() >= 2 && GetSurvivalDays() >= 4 && HasVisitedMysteryPlace() && GetNumAnimalsKilled() >= 1) {
		cout << "\n \nWin Conditions Met: "<< endl; 
		cout << "Required number of tools were crafted ("<< GetNumOfTools () << ")" << endl;
		cout << "Required number of animals were killed ("<< GetNumAnimalsKilled ()<<") " << endl;
		cout << "Survived for total (" << GetSurvivalDays() << ") days. " << endl;;
		cout << "Found the caves secret place" << endl;
		return true;
	}
	return false;
}

void Player::foundMysteryPlace() {
	this->HasfoundMysteryPlace = true;
}

bool Player::HasVisitedMysteryPlace()  {
	return this->HasfoundMysteryPlace;
}

void Player::SetEnoughFood(bool enoughFood) {
	this->enoughFood = true;
}

bool Player::GetEnoughFood() {
	return this->enoughFood;
}