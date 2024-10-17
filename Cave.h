#ifndef CAVE_H
#define CAVE_H
#include <iostream>
#include <random>
#include "Location.h"
class Cave : public Location
{
private:
	bool taken;
public:
	Cave();
	void setTaken(bool taken);
	int getTaken();
	virtual void draw();
	virtual int visit(Player& p);
	void StagnantWaterEvent(Player& p);
	void BatsEvent(Player& p);

};
#endif
