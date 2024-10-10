#ifndef LOCATION_H
#define LOCATION_H
#include<iostream>
#include "Player.h"
#include<vector>
using namespace std;

class Location
{
protected:
	bool visited;
	char symbol;
	vector <string> resourcesAvailable;

public:
	Location(char s = 'L');

	void setSymbol(char symbol);
	void setVisited(bool visited);	
	bool getVisited();
	char getSymbol();
	virtual void draw();
	virtual int visit(Player& p);
	virtual int visit(Player& p, bool init);

};

#endif

