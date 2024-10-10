#ifndef BEACH_H
#define BEACH_H
#include "Location.h"

class Beach : public Location
{
private:
	bool taken;
public:
	Beach();
	void setTaken(bool taken);
	int getTaken();
	virtual void draw();
	virtual int visit(Player& p);
};
#endif

