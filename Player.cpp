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
	if (userHealth > 100) {
		this->health = 100;
	}
	else {
		this->health = userHealth;
	}
}

// get`s the player`s health 
int Player::GetPlayerHealth() {
	return health;
}

// set`s player`s water
void Player::SetWater(int userWater) {
	if (userWater > 100) {
		this->water = 100;
	}
	else if(userWater < 0){
		this->water = 0;
	}
	else {
		this->water = userWater;
	}
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
//Use resources to craft various tools
void Player::useResources(const vector<string>& required) {
	for (size_t i = 0; i < required.size(); ++i) {
		this->rawMaterial[required[i]] -= 1; // Decrement one unit of each required resource
	}
}

//Build a vector for the items that can be crafted based on the available resources in inventory
vector<string> Player::showCraftableItems() {
	vector<string> craftableItems;
	int maxWidth = 30; // Maximum width for the first column

	// Build the output in a string stream
	string output;
	int index = 1;

	// Check for craftable items and build output
	for (map<string, vector<string>>::iterator it = this->recipes.begin(); it != this->recipes.end(); ++it) {
		// Check if the item is already in the tools vector
		if (std::find(tools.begin(), tools.end(), it->first) == tools.end()) {
			if (this->hasResources(it->second)) {
				// Format the line with padding
				string itemLine = to_string(index) + ". " + it->first;
				itemLine += string(maxWidth - itemLine.length(), ' '); // Pad to the max width

				// Add to output
				output += "| " + itemLine + " |\n";
				craftableItems.push_back(it->first);
				index++;
			}
		}
	}

	// Only print if there are craftable items
	if (!craftableItems.empty()) {
		cout << endl << "You can craft the following tools based on your current materials:" << endl;
		cout << "+" << string(maxWidth, '-') << "+" << endl; // Top border line
		cout << output; // Print the craftable items
		cout << "+" << string(maxWidth, '-') << "+" << endl; // Bottom border line
	}

	return craftableItems;
}


//Crux of the tools crafting. Tools are crafted based on input of the Player from console
void Player::CraftTools() {
	char response = 'y';
	while (response != 'n') {
		
		vector<string> craftable = this->showCraftableItems();
		if (craftable.empty()) {
			cout << endl << "No tools can be crafted with available resources now." << endl;
			return;
		}

		response = checkAndGetInput({'y','n'},"Do you wish to craft an item?(y/n):");

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
	}
}

void Player::AddTools(string userToolName) {
	this->tools.push_back(userToolName);
}
size_t Player::GetNumOfTools() {
	return this->tools.size();
}

void Player::CollectRawMaterial(vector<string>  items) {
	
	SET_COLOR(33);
	for (int i = 0; i < items.size(); i++) {
		cout << "[" << items.at(i) << "]";
	}
	RESET_COLOR();
	cout << endl;

	for(size_t i=0; i< items.size(); i++){
				
		if (isFoodItem(items[i])) {
			if (!this->GetEnoughFood()) {
				cout << items[i] << " is a food resource. But you have enough food for today. Cannot store food for future" << endl;
			}
			else {
				cout << items[i] << " is a food item. Consuming it for today's quota of food" << endl;
				this->SetEnoughFood(true);
			}
			items.erase(items.begin() + i);
			continue;
		}
		else if (isWaterItem(items[i])) {
			string prompt = items[i] + " is a water source. It will restore water level by x. Drint it(y/n):";
			char in = checkAndGetInput({ 'y','n' }, prompt);
			if (in == 'y') {
				this->SetWater(this->GetWater() + 30);
				items.erase(items.begin() + i);
			}			
			continue;
		}
		
		if (this->rawMaterial.count(items[i]) > 0) {
			this->rawMaterial[items[i]]++;	//Add number of resources
		}
		else {
			this->rawMaterial[items[i]] = 1; //First time resource
		}
	}
}

void Player::PrintStatus() {

	SET_COLOR(36);
	cout << endl << "GAME STATUS: " << endl;
	RESET_COLOR();
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

void Player::foundMysteryPlace() {
	this->HasfoundMysteryPlace = true;
}

bool Player::HasVisitedMysteryPlace()  {
	return this->HasfoundMysteryPlace;
}

void Player::SetEnoughFood(bool enoughFood) {
	this->enoughFood = enoughFood;
}
bool Player::GetEnoughFood() {
	return this->enoughFood;
}

bool Player::hasToolX(string toolName){
	auto it = std::find(this->tools.begin(), this->tools.end(), toolName);
	if (it != this->tools.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::isFoodItem(string resourceName) {
	if (resourceName == "fruits" || resourceName == "fish" || resourceName == "crabs") {
		return true;
	}
	return false;
}

bool Player::isWaterItem(string resourceName) {
	if (resourceName == "fruits" || resourceName == "fish" || resourceName == "crabs") {
		return true;
	}
	return false;
}