#include "Player.h"
#include <iomanip> 

Player::Player() {
	this->health = 100;
	this->water = 100;
	this->food = 100;
	this->survivalDays = 0;
	this->numAnimalsKilled= 0;
	this->visitedCave = false;
	this->tools;
}

void Player::SetPlayerHealth(int userHealth) {
	this->health = userHealth;
}
int Player::GetPlayerHealth() {
	return health;
}

void Player::SetWater(int userWater) {
	this->water = userWater;
}
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
	this->numAnimalsKilled = userNumAnimalsKilled;
}
int Player::GetNumAnimalsKilled() {
	return this->numAnimalsKilled;
}

void Player::CraftTools() {

	auto woodIter = std::find(rawMaterial.begin(), rawMaterial.end(), "wood");
	auto stoneIter = std::find(rawMaterial.begin(), rawMaterial.end(), "stones");

	if (woodIter != rawMaterial.end() && stoneIter != rawMaterial.end()) {
		tools.push_back("hammer");
		rawMaterial.erase(woodIter);  
		stoneIter = std::find(rawMaterial.begin(), rawMaterial.end(), "stones");
		rawMaterial.erase(stoneIter);  

		std::cout << "Crafted a hammer using wood and stone.\n";
	}
}

void Player::AddTools(string userToolName) {
	this->tools.push_back(userToolName);
}
int Player::GetNumOfTools() {
	return this->tools.size();
}

void Player::CollectRawMaterial(vector<string>  items) {
	
	for(size_t i=0; i< items.size(); i++){
		rawMaterial.push_back(items[i]);
	}
}

void Player::PrintStatus() {


	cout << "GAME STATUS: " << endl;
	int metricWidth = 20;  // Width for the "Metric" column
	int valueWidth = 10;   // Width for the "Current" column

	cout << "+----------------------+------------------+\n";
	cout << "| " << left << setw(metricWidth - 2) << "Metric" << "| " << setw(valueWidth - 2) << "Current" << "|\n";
	cout << "+----------------------+------------------+\n";

	cout << "| " << left << setw(metricWidth - 2) << "Tools Collected" << "| " << setw(valueWidth - 2) << GetNumOfTools() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Animals Killed" << "| " << setw(valueWidth - 2) << GetNumAnimalsKilled() << "|\n";
	cout << "| " << left << setw(metricWidth - 2) << "Days Survived" << "| " << setw(valueWidth - 2) << GetSurvivalDays() << "|\n";

	cout << "+----------------------+------------------+\n";
}

bool Player::CheckWinConditions() {

	//if (GetNumOfTools() >= 5 && GetSurvivalDays() >= 30 && GetNumAnimalsKilled() >= 10 && HasVisitedCave())
	if (GetNumOfTools() >= 2 && GetSurvivalDays() >= 4 && HasVisitedCave()) {
		cout << "Win Condition Met: Enough tools were collected, ";
		cout << "Enough animals were killed and ";
		cout << "Survived total 30 days. ";
		cout << "Visited the caves secret place" << endl;
		return true;
	}
	return false;
}

void Player::VisitCave() {
	visitedCave = true;
}

bool Player::HasVisitedCave()  {
	return visitedCave;
}
