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
	void WildAnimalAttackEvent(Player& p);
	void PoisonousPlantEvent(Player& p);
	void FollowMonkeyEvent(Player& p);
};
#endif

