#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.h"
#include <time.h>
#include "constants.h"

using namespace Constants;

class zombie : public Entity
{
public:
	float maxSpeed, acc;


	zombie()
	{
		dx = 0.1;
		dy = 0.1;
		acc = 1;
		maxSpeed = 5;
		name = "zombie"; \
			//angle = atan2(getXlocation() - x, y - getYlocation()) * 180 / 3.14 + 180;
	}

	void  update(float time)
	{
		//Get player location
		//i = entities.end();
		//playerTemp = *entitiesIterator;

		switch (gameMode)
		{
		case 0: {x += dx; y += dy; };// Orignal
		case 1:
		{
			if (x<getPlayerX())
			{
				dx += acc*time;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			else
			{
				dx -= acc*time;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			if (y<getPlayerY())
			{
				dy += acc*time;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			else
			{
				dy -= acc*time;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
		};//Enemies follow you
		case 2:
		{
			if (x<getPlayerX())
			{
				dx += 1;
			}
			else
			{
				dx -= 1;
			}
			if (y<getPlayerY())
			{
				dy += 1;
			}
			else
			{
				dy -= 1;
			}
		};//Enemies follow you but not facing you
		case 3: {};
		case 4: {};
		case 5: {};
		case 6: {};
		case 7: {};
		case 8: {};
		case 9: {};
		default:
		{
			//x += dx;
			//y += dy;
		}
		}
		
		float speed = sqrt(dx*dx + dy*dy);
		if (speed>maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}
	x += dx*time*.5;
		y += dy*time*.5 ;

		if (x>maxW) x = maxW;  if (x<0) x = 0;
		if (y>maxH) y = maxH;  if (y<0) y = 0;
	}

};
#endif