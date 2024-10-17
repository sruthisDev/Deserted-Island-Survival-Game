#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "Location.h"
class Mountain : public Location
{
private:
	bool taken;
public:
	Mountain();
	void setTaken(bool taken);
	int getTaken();
	virtual void draw();
	virtual int visit(Player& p);
	void ScrapeEvent(Player& p);
	void WildAnimalAttackEvent(Player& p);
};
#endif
