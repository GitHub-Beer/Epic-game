#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "constants.h"

using namespace Constants;

class player : public Entity
{
public:
	bool thrustU, thrustD, thrustL, thrustR;
	float acc, maxSpeed, stopspeed;
	float sf;
	
	player()
	{
		name = "player";
		acc = 2;
		maxSpeed = 10;
		stopspeed = 0.8;
		sf = 0.00001;
		//angle = 0;
	}
	float getAcc() {
		return acc;
	}
	float getmaxSpeed() {
		return maxSpeed;
	
	}
	void update(float time)
	{
		if (thrustU&thrustR)
		{
			
			if (dy > 0 || dx < 0) {
				if (dy > 0 && dx < 0) {
					dy *= stopspeed*time;
					dx *= stopspeed*time;
					dx += sf;
					dy -= sf;
				}
				else if (dy > 0&&dx>0) {
					dy *= stopspeed*time;
					dy -= sf;
					dx += acc*time;
				}
				else {
					dx *= stopspeed*time;
					dx += sf;
					dy -= acc*time;
				}
			
			}
			else {
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
				dy -= acc*time;
				dx += acc*time;
				//angle = 0;
			}
		}
		else if (thrustU&thrustL)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			if (dy>0||dx>0) {
				if (dy > 0 && dx > 0) {
					dy *= stopspeed*time;
					dx *= stopspeed*time;
					dx -= sf;
					dy -= sf;
				
				}
				else if (dy > 0&&dx<0) {
					dy *= stopspeed*time;
					dy -= sf;
					dx -= acc*time;
				}
				else
				{
					dx *= stopspeed*time;
					dx -= sf;
					dy -= acc*time;
				}

			}
			else {
				dy -= acc*time;
				dx -= acc*time;
				//angle = 0;
			}
		}
		else if (thrustD&thrustL)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			if (dy<0||dx>0) {
				if (dy < 0&&dx>0) {
					dy *= stopspeed*time;
					dx *= stopspeed*time;
					dy += sf;
					dx -= sf;
				}
				else if (dy<0 && dx>0)
				{
					dy *= stopspeed*time;
					dy += sf;
					dx -= acc*time;
				}
				else
				{
					dx *= stopspeed*time;
					dx -= sf;
					dy += acc*time;

				}

			}

		else {
			dy += acc*time;
			dx -= acc*time;
			//angle = 0;
		}
		}
		else if (thrustD&thrustR)
		{
			if (dx<0||dy<0)
			{
				if (dx<0 && dy<0)
				{
					dx *= stopspeed*time;
					dy *= stopspeed*time;
					dx += sf;
					dy += sf;
				}
				else if (dx<0 && dy>0)
				{
					dx *= stopspeed*time;
					dx += sf;
					dy += acc*time;
				}
				else
				{
					dy *= stopspeed*time;
					dy += sf;
					dx += acc*time;
				}
			}
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
		else {
			dy += acc*time;
			dx += acc*time;
		}
			//angle = 0;
		}
		else if (thrustU)
		{
			if (dy > 0) {
				dy *= stopspeed*time;
				dy -=sf;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dy -= acc*time;
			}
			dx *= stopspeed*time;
			//angle = 0;
		}
		//else
		//{
		//	dx *= 0.time*time;
		//	dy *= 0.time*time;
		//	//angle = 0;
		//}

		else if (thrustD)
		{
			//dx -= cos(angle*DEGTORAD)*0.2;
			//dy -= sin(angle*DEGTORAD)*0.2;
			if (dy < 0) {
				dy *= stopspeed*time;
				dy += sf;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dy += acc*time;
			}
			dx *= stopspeed*time;
			//angle = 0;
			//angle = time80;
		}
		//else
		//{
		//	dx *= 0.99*time;
		//	dy *= 0.99*time;
		//	//angle = 0;
		//}

	    else if (thrustL)
		{
			//dy -= sin(angle*DEGTORAD)*0.2;
			if (dx > 0) {
				dx *= stopspeed*time;
				dx -= 0.05;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dx -= acc*time;
			}
			dy *= stopspeed*time;//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			
			//angle = -90;
		}
		//else
		//{
		//	dx *= 0.time*time;
		//	dy *= 0.time*time;
		//	//angle = 0;
		//}

		else if (thrustR)
		{
			if (dx < 0) {
				dx *= stopspeed*time;
				dx += 0.05;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dx += acc*time;
			}
			dy *= stopspeed*time;//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			
			//angle = 90;
		}
		
		else
		{
			dx *= stopspeed*time;
			dy *= stopspeed*time;
			if (dx > 0) {
				dx -= sf;
			}
			if (dy > 0) {
				dy -= sf;
			}
			if (dx<0)
			{
				dx += sf;
			}
			if (dy<0)
			{
				dy += sf;
			}
			//angle = 0;
		}

		
		float speed = sqrt(dx*dx + dy*dy);
		if (speed>maxSpeed)
		{
			dx*= maxSpeed/speed;
			dy*= maxSpeed/speed;
		}

		x += dx;
		y += dy;


		if(x>maxW) x = maxW; if (x<0) x = 0;
		if (y>maxH) y = maxH; if (y<0) y = 0;
		//if (isOutsideMap(dx*time, dy*time)) {
			//offsetEntities(dx*time, dy*time);
		//}
	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif