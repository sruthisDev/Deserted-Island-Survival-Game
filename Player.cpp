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
	this->recipes = {
	   {"axe", {"wood", "stone"}},
	   {"bandage", {"cloth", "medical_herbs"}},
	   {"spear", {"wood", "stone", "rope"}},
	   {"torch", {"wood", "animal_fat"}},
	   {"sleeping bag", {"cloth", "reeds"}},
	   {"rope", {"coconuts"}},
	   {"clothing", {"coconuts", "reeds"}},
	   {"container", {"wood", "rope"}},
	   {"mud pack", {"mud", "medical_herbs"}},
	   {"whistle", {"animal_bone", "wood"}}
	};
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

bool Player::hasResources(const vector<string>& required) {
	for (size_t i = 0; i < required.size(); ++i) {
		if (this->rawMaterial[required[i]] <= 0) {
			return false;  // Not enough of this resource
		}
	}
	return true;  // Enough resources
}

void Player::useResources(const vector<string>& required) {
	for (size_t i = 0; i < required.size(); ++i) {
		this->rawMaterial[required[i]] -= 1; // Decrement one unit of each required resource
	}
}

vector<string> Player::showCraftableItems() {
	/*vector<string> craftableItems;
	cout << "You can craft the following tools based on your current materials:" << endl;
	for (map<string, vector<string>>::iterator it = this->recipes.begin(); it != this->recipes.end(); ++it) {
		if (this->hasResources(it->second)) {
			cout << "- " << it->first << endl;
			craftableItems.push_back(it->first);
		}
	}
	return craftableItems;*/

	vector<string> craftableItems;
	cout << "You can craft the following tools based on your current materials:" << endl;
	int index = 1;
	for (map<string, vector<string>>::iterator it = this->recipes.begin(); it != this->recipes.end(); ++it) {
	//for (auto it = this->recipes.begin(); it != this->recipes.end(); ++it) {
		if (this->hasResources(it->second)) {
			cout << index << ". " << it->first << endl;
			craftableItems.push_back(it->first);
			index++;
		}
	}
	return craftableItems;
}

void Player::CraftTools() {
	vector<string> craftable = this->showCraftableItems();
	if (craftable.empty()) {
		cout << "No tools can be crafted with available resources." << endl;
		return;
	}
	cout << "Do you wish to craft an item? (y/n): ";
	char response;
	cin >> response;
	if (response == 'n') {
		cout << "Crafting canceled." << endl;
		return;
	}

	if (response == 'y') {
		cout << "Enter the number of the tool you want to craft: ";
		int toolChoice;
		cin >> toolChoice;

		if (toolChoice > 0 && toolChoice <= craftable.size()) {
			string selectedTool = craftable[toolChoice - 1];
			this->useResources(this->recipes[selectedTool]);
			this->tools.push_back(selectedTool);
			cout << "Successfully crafted a " << selectedTool << "." << endl;
		}
		else {
			cout << "Invalid tool choice. Please select a valid number from the list." << endl;
		}
	}
	else {
		cout << "Invalid response. Please enter 'y' for yes or 'n' for no." << endl;
	}

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