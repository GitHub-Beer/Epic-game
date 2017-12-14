#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"


class bullet : public Entity
{
public:

	bullet()
	{
		name = "bullet";
		xpos = x;
		ypos = y;
	}

	void  update(float time)
	{
		dx = cos(angle*DEGTORAD) * 60 * time;
		dy = sin(angle*DEGTORAD) * 60 * time;
		// angle+=rand()%6-3;
		x += dx;
		y += dy;

		//if (x>W || x<0 || y>H || y<0) life = 0;
	}

};

#endif