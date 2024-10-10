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
};
#endif
