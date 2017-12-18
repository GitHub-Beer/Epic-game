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
	float counter_reload=0;
	float counter_spm;
	float dist;//radius of bullet life
	Sound snd;
	std::string type;
	weapon()
	{
		name = "weapon";
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	void weaponcopy(weapon *w) {
		if (type == w->type) {
			spm *= 1.2;
			ammo *= 1.2;
			rtime *= 0.9;
			damage*=1.2;
			dist *= 1.2;

		}
		else
		{
			snd.setBuffer(w->buffer);
			spm = w->spm;
			ammo = w->ammo;
			rtime = w->rtime;
			damage =  w->damage;
			dist = w->dist;
			spt = w->spt;
			type = w->type;
			currammo = ammo;
		}
	
	}
	void weaponSetup(SoundBuffer &Buf, int _spm, int _ammo, int _rtime, float _damage, int _spt, float distance ,std::string _type) {
		spm = 600/_spm;
		ammo = _ammo;
		currammo = _ammo;
		rtime = _rtime*10;//seconds to miliseconds
		damage = _damage;
		spt = _spt;
		buffer = Buf;
		snd.setBuffer(Buf);
		dist = distance;
		counter_spm = spm + 1;
		type = _type;
		
	
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
	float wreloadpercentage() {
		return (counter_reload/rtime)*100;
	}
	bool needReload() {
		if (currammo == 0) return true;
		else return false;

	}
	void shoot_sound() {
	
		snd.play();
	
	
	}
     	void reload(float time) {

		if (counter_reload > rtime) {
			currammo = ammo;
			
			counter_reload = 0;
			
		}
		
		else {
			counter_reload += time;
			
		}
	}
	void  update(float time)
	{
		counter_spm += time;
		if (currammo == 0) {
			reload(time);
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