#ifndef LOCATION_H
#define LOCATION_H
#include<iostream>
#include<vector>
#include "Player.h"
#include "Utilities.h"
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
	virtual vector<string>& getResources();
	virtual void CollectResources(Player& p, size_t numResources);

};

#endif

