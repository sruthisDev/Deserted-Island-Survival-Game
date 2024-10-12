#ifndef LAKE_H
#define LAKE_H
#include "Location.h"
class Lake :  public Location
{
private:
	bool taken;
public:
	Lake();
	void setTaken(bool taken);
	int getTaken();
	virtual void draw();
	virtual int visit(Player& p);
};
#endif

