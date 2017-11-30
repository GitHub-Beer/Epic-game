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
			dx = 0;
			dy = 0;
			//angle = 0;
		}

		int maxSpeed = 5;
		float speed = sqrt(dx*dx + dy*dy);
		if (speed>maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		//if (x == 0 || x <= (W / 2))
		//{
		//	if (offset_x == 0)
		//	{
		//		//x changes
		//		x += dx;
		//		if (x >= (W / 2)) { x = (W / 2); }
		//	}
		//	if (x <= 0) { x = 0; }

		//}

		//if (x == (W/2))
		//{
		//	//Offset always changes
		//	offset_x += dx;

		//	//Limit offset
		//	if (offset_x >= maxW - (W))
		//	{
		//		offset_x = maxW - (W);
		//	}
		//	if (offset_x <= 0)
		//	{
		//		offset_x = 0;
		//	}
		//}
		//if (x > (W / 2) || offset_x == (maxW - (W))) //set offset to limit
		//{
		//	offset_x = (maxW - (W));
		//	//x changes
		//	x += dx;
		//	if (x >= (W)) { x = (W); } // limit x
		//	if (x < ((W/2))) { x = ((W / 2)); }
		//	if (x > (W / 2)) { offset_x = (maxW - W); }
		//}


		//if (x == (W / 2) && offset_x == (maxW - (W / 2)))
		//{
		//		//x changes
		//		x += dx;
		//		if (x >= (maxW)) { x = (maxW); } //limit x
		//	//if (x <= 0) { x = 0; }
		//}

		//Update player position
		//if (offset_x == 0 && dx <= 0)
		//{
		//	x += dx;
		//}

		//Update Offset
		//X
		//if (x >= 0 && x < (W / 2))
		//{
		//	//dont update offset but update player position
		//	offset_x = 0;
		//	x += dx;
		//	if (x >= (W / 2)) { x = (W / 2); } //make sure x stays W/2 maximum
		//}
		//else if (offset_x >= (maxW -(W/2)))
		//{
		//	//update offset to  max value and change x
		//	offset_x = maxW - (W / 2);
		//	if (x <= maxW) 
		//	{
		//		x += dx;
		//	}
		//}
		//Y

		//Update player position on screen

		//if ((x <= (maxW - (W / 2)) && x >= (W / 2))) //Increase offset 
		//{
		//	//offset_x = x - (W / 2);
		//	offset_x += dx;
		//}
		//

		//else
		//{
		//	x += dx;
		//}
	//	if ((y <= (maxH - (H / 2)) && y > (H / 2)))
	//	{
	//		offset_y = y - (H / 2);
	//	}
	//	else 
	//	{ 
			y += dy;
	//	}

	//	if (x>maxW) x = 0; if (x<0) x = maxW;
	//	if (y>maxH) y = 0; if (y<0) y = maxH;

			if (x>maxW) x = maxW;  if (x<0) x = 0;
			if (y>maxH) y = maxH;  if (y<0) y = 0;

			y += dy;
			x += dx;

			offsetEntities(dx, dy);
	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif