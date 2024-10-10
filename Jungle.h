#ifndef JUNGLE_H
#define JUNGLE_H
#include "Location.h"
class Jungle :  public Location
{
private:
	bool taken;
public:
	Jungle();
	void setTaken(bool taken);
	int getTaken();
	virtual void draw();
	virtual int visit(Player& p);
	void attack(Player& p);
	void escape(Player& p);
};
#endif

