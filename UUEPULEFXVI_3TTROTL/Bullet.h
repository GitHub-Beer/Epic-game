#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"


class bullet : public Entity
{
public:
	bullet()
	{
		name = "bullet";
	}

	void  update()
	{
		dx = cos(angle*DEGTORAD) * 6;
		dy = sin(angle*DEGTORAD) * 6;
		// angle+=rand()%6-3;
		x += dx;
		y += dy;

		if (x>W || x<0 || y>H || y<0) life = 0;
	}

};

#endif