#ifndef WALL_H
#define WALL_H
#include "Entity.h"
#include "constants.h"

using namespace Constants;

class wall : public Entity
{
public:
	wall()
	{
		name = "wall";
	}

	void update()
	{

	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif