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

	void update(float time)
	{
		if (thrustU)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			dy -= 1*time;
			//angle = 0;
		}
		//else
		//{
		//	dx *= 0.1*time;
		//	dy *= 0.1*time;
		//	//angle = 0;
		//}

		else if (thrustD)
		{
			//dx -= cos(angle*DEGTORAD)*0.2;
			//dy -= sin(angle*DEGTORAD)*0.2;
			dy += 1*time;
			//angle = 180;
		}
		//else
		//{
		//	dx *= 0.99*time;
		//	dy *= 0.99*time;
		//	//angle = 0;
		//}

		else if (thrustL)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx -= 1*time;
			//angle = -90;
		}
		//else
		//{
		//	dx *= 0.1*time;
		//	dy *= 0.1*time;
		//	//angle = 0;
		//}

		else if (thrustR)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx += 1*time;
			//angle = 90;
		}
		else
		{
			dx *=dx- 0.1*time;
			dy *= dx- 0.1*time;
			//angle = 0;
		}

		int maxSpeed = 5;
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