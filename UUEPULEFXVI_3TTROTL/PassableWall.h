#ifndef PASSABLEWALL_H
#define PASSABLEWALL_H
#include "Entity.h"
#include "constants.h"

using namespace Constants;

class p_wall : public Entity
{
public:
	p_wall()
	{
		name = "p_wall";
	}

	void update()
	{
		x -= offset_x;
	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif#pragma once
