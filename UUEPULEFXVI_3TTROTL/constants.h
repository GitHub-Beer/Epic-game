#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <list>
#include "Entity.h"
#include <SFML/Graphics.hpp>


namespace Constants
{
	// actual global variables
	extern double mouseXpos, mouseYpos, mouseAngle;//mouse location
	extern const int mapH = 50;
	extern const int mapW = 50;
	extern int gameMode = 0;//{ 0,1,2,3,4,5,6,7,8,9 }; //This game will feature 10 game modes, 0= default
	extern const int maxW = 1600; //max Screen resolution - Width
	extern const int maxH = 1600; //max Screen resolution - Height

	extern const int W = 1280; //Screen resolution - Width
	extern const int H = 720; ////Screen Height
	extern const float PI = 3.14159265;
	extern float DEGTORAD = 0.017453f;//This commend was modified in the new branch again 2
	extern int offset_x = 0, offset_y = 0;



}
#endif