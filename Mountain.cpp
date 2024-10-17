#include "Mountain.h"

Mountain::Mountain() :Location('M') {
	resourcesAvailable = { "stone", "leaves", "wood", "animal_hide", "animal_bone"};
	taken = false;
}
void Mountain::setTaken(bool userTaken) {
	taken = userTaken;
}
int Mountain::getTaken() {
	return  taken;
}
void Mountain::draw() {
	if (taken) {
		cout << " ";
	}
	else {
		Location::draw();
	}

}
int Mountain::visit(Player& p) {
	size_t numResources = 0;
	if (!visited) {
		visited = true;
		numResources = getResources().size();
		cout << "Climbing the mountain" << endl;
	}
	else {
		numResources = 1;
		cout << "You are again at the Mountain. You find fewer resources." << endl;
	}
	CollectResources(p, numResources);
	int eventProb = generateRandomNumber(0, 100);
	if (eventProb < 20) {
		ScrapeEvent(p);
	}
	else if (eventProb < 40) {
		cout << "No Event";
	}
	WildAnimalAttackEvent(p);
	
	return 1;
}

void Mountain::ScrapeEvent(Player& p) {
    // Define options and their enabled state
    vector<Option> options = {
        {"Apply Bandage", false},
        {"Do Nothing", true},
    };

    // Build the prompt string
	if (p.hasToolX("bandage")) {
		options[0].enabled = true;
	}
    cout << endl <<"While navigating the mountains, you scrape yourselves." << endl;
    printOptions(options);
    cout << "Select an option (1-" << options.size() << "): ";

    // Get valid input from the player
    char in = checkAndGetInput(options);

    switch (in) {
    case '1':
        cout << "You applied a bandage successfully. No impact to health." << endl;
        break;
    case '2':
        cout << "You chose to do nothing. The scrape worsens, impacting your health." << endl;
        p.SetPlayerHealth(p.GetPlayerHealth() - 10);
        cout << "You lost 10 health." << endl;
        break;
    }
}


void Mountain::WildAnimalAttackEvent(Player& p) {
	// Define options and their enabled state
	vector<Option> options = {
		{"Attack with a tool", p.hasToolX("axe") || p.hasToolX("spear") || p.hasToolX("knife")},
		{"Attack directly (50% chance to succeed)", true},
		{"Escape", true}
	};

	cout << endl << "A wild bear suddenly appears in the dense jungle!" << endl;
	cout << "You need to act quickly. What will you do?" << endl;
	printOptions(options);
	cout << "Select an option (1-" << options.size() << "): ";

	// Get valid input from the player
	char in = checkAndGetInput(options);

	switch (in) {
	case '1':
		cout << "You use your tool to attack the wild animal." << endl;
		cout << "You successfully kill the animal and obtain an animal hide!" << endl;
		p.CollectRawMaterial({ "animal_hide" });
		cout << "You eat the animal to satisfy food quota for the day" << endl;
		p.SetEnoughFood(true);
		p.SetNumAnimalsKilled(1);
		break;
	case '2':
		cout << "You decide to attack the animal directly." << endl;
		if (generateRandomNumber(0, 100) < 50) { // 50% chance of success
			cout << "You managed to kill the animal with your bare hands! You obtain an animal hide." << endl;
			p.CollectRawMaterial({ "animal_hide" });
			cout << "You eat the animal to satisfy food quota for the day" << endl;
			p.SetEnoughFood(true);
			p.SetNumAnimalsKilled(1);
			break;
		}
		else {
			cout << "The animal overpowered you. You lost 15 health." << endl;
			p.SetPlayerHealth(p.GetPlayerHealth() - 15);
		}
		break;
	case '3':
		cout << "You chose to escape from the animal." << endl;
		cout << "You run away safely but gain no rewards." << endl;
		break;
	}
}
