#ifndef PICKUP_H
#define PICKUP_H

#include "Entity.h"


class pickup : public Entity
{
public:
	
	
	pickup()
	{
		name = "pickup";
		
	}
	
	void  update(float time)
	{
		counter += time;
		if (counter > 100) {
			life = false;
		}
		//if (x>W || x<0 || y>H || y<0) life = 0;
	}

};

#endif
