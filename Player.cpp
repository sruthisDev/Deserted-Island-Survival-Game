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

void Player::CraftTools(vector<string> userRawMaterial) {
	//cout<<"Vector Size: " << userRawMaterial.size() << endl;
}

void Player::AddTools(string userToolName) {
	this->tools.push_back(userToolName);
}
int Player::GetNumOfTools() {
	return 0;
	//return this->tools.size();
}

void Player::PrintStatus() {

	cout << "GAME STATUS: " << endl;
	cout << GetNumOfTools() << " tools are collected ";
	if (GetNumOfTools() < 5) {
		//cout << 5 - GetNumOfTools() << " more tools should be collected to win";
	}
	//cout<< endl;

	cout << GetNumAnimalsKilled()<<" animals are killed ";
	if (GetNumAnimalsKilled() < 10) {
		//cout << 10 - GetNumAnimalsKilled() << " more animals should be killed to win";
	}
	//cout << endl;

	cout << "Survived "<< GetSurvivalDays() <<" days";
	if (GetSurvivalDays() < 30) {
		//cout << 30 - GetSurvivalDays() << " days are left to win";
	}
	cout << endl << endl;
}

bool Player::CheckWinConditions() {
	if (GetNumOfTools() >= 5 && GetSurvivalDays() >= 30 && GetNumAnimalsKilled() >= 10) {
		cout << "Win Condition Met: Enough tools were collected, ";
		cout << "Enough animals were killed and ";
		cout << "Survived total 30 days."<<endl;
		return true;
	}
	return false;
}
