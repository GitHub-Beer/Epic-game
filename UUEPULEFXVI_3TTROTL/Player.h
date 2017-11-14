#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "constants.h"

using namespace Constants;

class player : public Entity
{
public:
	bool thrustU, thrustD, thrustL, thrustR;
	player()
	{
		name = "player";
		//angle = 0;
	}

	void update()
	{
		if (thrustU)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			dy -= 0.099;
			//angle = 0;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
			//angle = 0;
		}

		if (thrustD)
		{
			//dx -= cos(angle*DEGTORAD)*0.2;
			//dy -= sin(angle*DEGTORAD)*0.2;
			dy += 0.099;
			//angle = 180;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
			//angle = 0;
		}

		if (thrustL)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx -= 0.099;
			//angle = -90;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
			//angle = 0;
		}

		if (thrustR)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx += 0.099;
			//angle = 90;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
			//angle = 0;
		}

		int maxSpeed = 15;
		float speed = sqrt(dx*dx + dy*dy);
		if (speed>maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		x += dx;
		y += dy;

		if (x>W) x = 0; if (x<0) x = W;
		if (y>H) y = 0; if (y<0) y = H;
	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif