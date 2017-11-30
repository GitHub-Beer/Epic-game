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
		acc = 15;
		maxSpeed = 40;
		stopspeed = 0.8;
		sf = 0.00000001;
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
					dy *= stopspeed*1;
					dx *= stopspeed*1;
					dx += sf;
					dy -= sf;
				}
				else if (dy > 0&&dx>0) {
					dy *= stopspeed*1;
					dy -= sf;
					dx += acc*1;
				}
				else {
					dx *= stopspeed*1;
					dx += sf;
					dy -= acc*1;
				}
			
			}
			else {
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
				dy -= acc*1;
				dx += acc*1;
				//angle = 0;
			}
		}
		else if (thrustU&thrustL)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			if (dy>0||dx>0) {
				if (dy > 0 && dx > 0) {
					dy *= stopspeed*1;
					dx *= stopspeed*1;
					dx -= sf;
					dy -= sf;
				
				}
				else if (dy > 0&&dx<0) {
					dy *= stopspeed*1;
					dy -= sf;
					dx -= acc*1;
				}
				else
				{
					dx *= stopspeed*1;
					dx -= sf;
					dy -= acc*1;
				}

			}
			else {
				dy -= acc*1;
				dx -= acc*1;
				//angle = 0;
			}
		}
		else if (thrustD&thrustL)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			if (dy<0||dx>0) {
				if (dy < 0&&dx>0) {
					dy *= stopspeed*1;
					dx *= stopspeed*1;
					dy += sf;
					dx -= sf;
				}
				else if (dy<0 && dx>0)
				{
					dy *= stopspeed*1;
					dy += sf;
					dx -= acc*1;
				}
				else
				{
					dx *= stopspeed*1;
					dx -= sf;
					dy += acc*1;

				}

			}

		else {
			dy += acc*1;
			dx -= acc*1;
			//angle = 0;
		}
		}
		else if (thrustD&thrustR)
		{
			if (dx<0||dy<0)
			{
				if (dx<0 && dy<0)
				{
					dx *= stopspeed*1;
					dy *= stopspeed*1;
					dx += sf;
					dy += sf;
				}
				else if (dx<0 && dy>0)
				{
					dx *= stopspeed*1;
					dx += sf;
					dy += acc*1;
				}
				else
				{
					dy *= stopspeed*1;
					dy += sf;
					dx += acc*1;
				}
			}
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
		else {
			dy += acc*1;
			dx += acc*1;
		}
			//angle = 0;
		}
		else if (thrustU)
		{
			if (dy > 0) {
				dy *= stopspeed*1;
				dy -=sf;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dy -= acc*1;
			}
			dx *= stopspeed*1;
			//angle = 0;
		}
		//else
		//{
		//	dx *= 0.1*1;
		//	dy *= 0.1*1;
		//	//angle = 0;
		//}

		else if (thrustD)
		{
			//dx -= cos(angle*DEGTORAD)*0.2;
			//dy -= sin(angle*DEGTORAD)*0.2;
			if (dy < 0) {
				dy *= stopspeed*1;
				dy += sf;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dy += acc*1;
			}
			dx *= stopspeed*1;
			//angle = 0;
			//angle = 180;
		}
		//else
		//{
		//	dx *= 0.99*1;
		//	dy *= 0.99*1;
		//	//angle = 0;
		//}

	    else if (thrustL)
		{
			//dy -= sin(angle*DEGTORAD)*0.2;
			if (dx > 0) {
				dx *= stopspeed*1;
				dx -= 0.05;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dx -= acc*1;
			}
			dy *= stopspeed*1;//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			
			//angle = -90;
		}
		//else
		//{
		//	dx *= 0.1*1;
		//	dy *= 0.1*1;
		//	//angle = 0;
		//}

		else if (thrustR)
		{
			if (dx < 0) {
				dx *= stopspeed*1;
				dx += 0.05;
				//dx += cos(angle*DEGTORAD)*0.2;
				//dy += sin(angle*DEGTORAD)*0.2;
			}
			else {
				dx += acc*1;
			}
			dy *= stopspeed*1;//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			
			//angle = 90;
		}
		
		else
		{
			dx *= stopspeed*1;
			dy *= stopspeed*1;
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

		x += dx*time;
		y += dy*time;


		if (x>W) x = 0; if (x<0) x = W;
		if (y>H) y = 0; if (y<0) y = H;
	}

	int getXlocation() { return x; };
	int getYLocation() { return y; };

};
#endif