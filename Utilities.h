#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <random>

using namespace std;

bool checkInVector(std::vector<char>& options, char& input);

char checkAndGetInput(std::vector<char> options, string text);

int generateRandomNumber();

#endif
