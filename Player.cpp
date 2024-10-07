#include "Player.h"
Player::Player() {
	this->health = 100;
	this->water = 100;
	this->food = 100;
	this->survivalDays = 0;
	this->numAnimalsKilled= 0;
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
	this->survivalDays = userSurvivalDays;
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

void Player::CraftTools(vector<string> userRawMaterial) {
	cout<<"Vector Size: " << userRawMaterial.size() << endl;
}

void Player::AddTools(string userToolName) {
	this->tools.push_back(userToolName);
}
int Player::GetNumOfTools() {
	return 0;
	//return this->tools.size();
}