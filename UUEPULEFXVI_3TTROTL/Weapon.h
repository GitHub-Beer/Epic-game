#ifndef WEAPON_H
#define Weapon_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class weapon : public Entity
{
public:
	
	int spm;//shots per minute
	int ammo;
	int rtime;//reload time
	SoundBuffer buffer;
	float damage;//damage from one shot
	int spt;//shots per one turn uses for shotgun

	weapon()
	{
		name = "weapon";
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	void weaponSetup(SoundBuffer _buf, int _spm, int _ammo, int _rtime, float _damage, int _spt ) {
		spm = calculateSPM(_spm);
		ammo = _ammo;
		rtime = _rtime*1000;//seconds to miliseconds
		damage = _damage;
		spt = _spt;
		buffer = _buf;
	
	}

	//calculate spm returns result in miliseconds, result means wait time between shots 
	int calculateSPM(int _spm) {
			return 60000 / _spm; //60*10^3 miliseconds/ shoots per minute
	}
	void shoot(float time) {
		float itime;
	}

	void  update(float time)
	{
		//dx = cos(angle*DEGTORAD) * 6;
		//dy = sin(angle*DEGTORAD) * 6;
		//// angle+=rand()%6-3;
		//x += dx;
		//y += dy;

		//if (x>W || x<0 || y>H || y<0) life = 0;
	}

};

#endif