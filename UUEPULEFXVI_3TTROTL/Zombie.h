#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.h"
#include <time.h>
#include "constants.h"

using namespace Constants;

class zombie : public Entity
{
public:

	zombie()
	{
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
		name = "zombie"; \
			//angle = atan2(getXlocation() - x, y - getYlocation()) * 180 / 3.14 + 180;
	}

	void  update()
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
				x += 1;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			else
			{
				x -= 1;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			if (y<getPlayerY())
			{
				y += 1;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
			else
			{
				y -= 1;
				angle = atan2(getPlayerX() - x, y - getPlayerY()) * 180 / 3.14 + 180;
			}
		};//Enemies follow you
		case 2:
		{
			if (x<getPlayerX())
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
			if (y<getPlayerY())
			{
				y += 1;
			}
			else
			{
				y -= 1;
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
		//x += dx;
		//y += dy;

		if (x>W) x = 0;  if (x<0) x = W;
		if (y>H) y = 0;  if (y<0) y = H;
	}

};
#endif