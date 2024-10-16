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
	
	return 1;
}

void Mountain::ScrapeEvent(Player& p) {
    // Define options and their enabled state
    vector<Option> options = {
        {"Apply Bandage", false},
        {"Do Nothing", true},
    };

    // Build the prompt string
	if (p.hasToolX("container")) {
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
