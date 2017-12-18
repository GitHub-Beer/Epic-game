#ifndef WEAPON_H
#define Weapon_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"


class weapon : public Entity
{
public:
	
	int spm;//shots per minute
	int ammo;
	int rtime;//reload time
	SoundBuffer buffer;
	float damage;//damage from one shot
	int spt;//shots per one turn uses for shotgun
	int currammo;
	float counter_reload;
	float counter_spm;
	float dist;//radius of bullet life
	Sound snd();

	weapon()
	{
		name = "weapon";
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	void weaponSetup(std::string _LOAD, int _spm, int _ammo, int _rtime, float _damage, int _spt, float distance ) {
		spm =600/_spm;
		ammo = _ammo;
		currammo = _ammo;
		rtime = 600/_rtime;//seconds to miliseconds
		damage = _damage;
		spt = _spt;
		buffer.loadFromFile(_LOAD);
		dist = distance;
		counter_spm = spm + 1;
		float counter_reload=0;
		
	
	}
	
	//calculate spm returns result in miliseconds, result means wait time between shots 
	bool canshoot(float time){
		if (counter_spm > spm) {
			counter_spm = 0;
			return true;
		}
		else {
			counter_spm += time;
				return false;
		}


	}
	/*void shoot(float time) {
		if (currammo > 0&&canshoot) {
			currammo--;
			Sound sound(buffer);
			sound.play();
			
			
		}
		if(currammo==0) {
			reload(time);
			
		}
		
		
	}*/
	bool needReload() {
		if (currammo == 0) return true;
		else return false;

	}
	void play() {
		Sound sound(buffer);
		sound.play();
	
	
	}
     	void reload(float time) {

		if (counter_reload > rtime) {
			currammo = ammo;
			
			counter_reload = 0;
			//return false;
		}
		
		else {
			counter_reload += time;
			//return true;
		}
	}
	void  update(float time)
	{
		counter_spm += time;
		//if (currammo == 0) {
			
		//}
		if (currammo == 0) {
			reload(time);
			counter_reload += time;

		}
		//dx = cos(angle*DEGTORAD) * 6;
		//dy = sin(angle*DEGTORAD) * 6;
		//// angle+=rand()%6-3;
		//x += dx;
		//y += dy;

		//if (x>W || x<0 || y>H || y<0) life = 0;
	}
	
};


#endif