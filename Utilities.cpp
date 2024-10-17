#include "Utilities.h"

bool checkInVector(vector<char>& options, char input) {
	for (size_t i = 0; i < options.size(); i++) {
		if (input == options[i]) {
			return true;
		}
	}
	return false;
}

//Check if text is in options char vector or not
char checkAndGetInput(vector<char> options, string text) {
	string input = "";
	while (true) {
		cout << text ;
		cin >> input;

		if(input.length() == 1 && checkInVector(options, tolower(input[0])))
			return tolower(input[0]);
		else 
			cout << "Invalid Input " << endl;
	}
}

// Function to print the options
void printOptions(vector<Option>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        // Print the option text
        if (options[i].enabled) {
            cout << i + 1 << ") " << options[i].text << endl; // Normal color
        }
        else {
            // Print disabled options in grey
            SET_COLOR(31); // Set to grey
            cout << i + 1 << ") " << options[i].text << " (disabled)" << endl;
            RESET_COLOR(); // Reset color to default
        }
    }
}

// Function to check and get input
char checkAndGetInput(vector<Option>& options) {
    string input;
    while (true) {
        cin >> input;

        // Validate input and check for the enabled state
        if (input.length() == 1 && isdigit(input[0])) {
            int choice = input[0] - '0'; // Convert char to int
            if (choice > 0 && choice <= options.size()) {
                // Return valid input only if it's enabled
                if (options[choice - 1].enabled) {
                    return input[0]; // Return the valid input
                }
                else {
                    cout << "Option " << choice << " is disabled." << endl;
                }
            }
        }
        cout << "Invalid Input. Please enter a valid option." << endl;
    }
}

//Generate random number between start and end (ex 100 if you want %)
int generateRandomNumber(int start, int end) {
	static std::mt19937 generator(42); 
	std::uniform_int_distribution<int> distribution(start, end);
	return distribution(generator);
}

void deleteFromVector(vector<string>& vec, string value) {
    auto it = find(vec.begin(), vec.end(), value);

    if (it != vec.end()) {
        vec.erase(it);
    }
}