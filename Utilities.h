#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <random>

using namespace std;

#define SET_COLOR(code) std::cout << "\033[" << (code) << "m"
#define RESET_COLOR() std::cout << "\033[0m"

struct Option {
	string text;     // Option text
	bool enabled;    // Is the option enabled or disabled
};

bool checkInVector(vector<char>& options, char input);			

char checkAndGetInput(vector<char> options, string text);			//Helper function to check if input is in the given options vector

void printOptions(vector<Option>& options);

char checkAndGetInput(vector<Option>& options); //Specific to handle events and its options

int generateRandomNumber(int first, int last);							//Helper function to generate random number based on uniform distribution

void deleteFromVector(vector<string>& vec, string value);

#endif
