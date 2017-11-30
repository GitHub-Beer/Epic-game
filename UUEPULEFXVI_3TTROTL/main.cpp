#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <random>
#include <list>
#include<math.h>
#include "constants.h"

using namespace Constants;




//Global stuff
using namespace sf;
/*tring Map[W*H] = {
"AAAAAAAAAAAA",
"BBBBBBBBBBBB",
"CCCCCCCCCCCC",
"AAAAAAAAAAAA",
"AAAAAAAAAAAA",

};*/




//Global functions
bool isTooClose(float, float); //For finiding if another entitiy is close or not
void updateMouseAngle(sf::Vector2i); // This is for making Player point towards Mouse
void generateMap(int mapType); //Map generator
float getPlayerX();
float getPlayerY();
bool isCollide(Entity *a, Entity *b);
void offsetEntities(int howMuchX, int howMuchY);



//Include all other parts of the game
#include "Animation.h""
#include "Entity.h"
#include "Bullet.h"
#include "Map.h"
#include "Pickup.h"
#include "Player.h"
#include "Walls.h"
#include "Zombie.h"
#include "PassableWall.h"


//global variable
float playerX;
float playerY;
//sf::String Map[50][50];
int gameState[maxW][maxH]; //Stores the information of entities in map at location W and H , buffer is outside area
												   /*
												   0 = nothing
												   1 = Pickup
												   2 = Zombie
												   3 = Bullet
												   4 = Player
												   5 = Wall
												   6 = Passable wall or grass
												   7 = Breakable wall
												   */

//extern int getXlocation(), getYlocation();//player location
std::list<Entity*> entities; //Entities

//std::list<Entity*> entities;


//main
int main()

{

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator


	double mouseXpos, mouseYpos, mouseAngle;
	sf::Vector2f curPos;

	srand(time(0));
	// Load the font from a file
	sf::Font font;
	if (!font.loadFromFile("fonts/BRADHITC.ttf"))
	{
		// error...
	}
	sf::Text text;

	// select the font
	text.setFont(font); 				
	text.setCharacterSize(28); 
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	RenderWindow app(VideoMode(W, H), "The third return of the legend!");
	//app.setFramerateLimit(120);


	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9,t11,t12,t13;
	t1.loadFromFile("images/Player_top.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/explosions/enemy_die.png");
	t4.loadFromFile("images/enemy_move.png");
	t5.loadFromFile("images/fire_red.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/LEG_ANIM1.png");
	///
	t9.loadFromFile("images/background/bcg.png");
	t11.loadFromFile("images/background/grass.png");
	t12.loadFromFile("images/background/stone.png");
	t13.loadFromFile("images/background/bushes.png");


	Sprite BCG(t9);
	Sprite UPD(t9);



	//RectangleShape rect(Ve;
	t1.setSmooth(true);
	t2.setSmooth(true);
	


	RectangleShape rectangle(Vector2f(4, 4));
	RectangleShape rectangle1(Vector2f(200, 200));
	int mMapX = 1000;
	int mMapY = 500;

	//Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 120.5, 73, 6, 0.1);
	Animation sRock(t4, 0, 0, 120.5, 53, 6, 0.1);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);

	Animation sPlayer(t1, 0, 0, 57, 99, 1, 0);
	//Animation sPlayer(t1, 0, 0, 57, 99, 1, 0);
	Animation sPlayer_go(t1, 0, 0, 57, 99, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
	Animation sLeg(t1, 0, 0, 57, 99, 1, 0);

	//Background entities
	Animation bGrass(t11, 0, 0, 32, 32, 1, 0);
	Animation bStone(t12, 0, 0, 32, 32, 1, 0);
	Animation bBushes(t13, 0, 0, 32, 32, 1, 0);

	SoundBuffer buffer;
	buffer.loadFromFile("weap_deserteagle_slmn_2.wav");
	Sound sound(buffer);
	SoundBuffer buf;
	buf.loadFromFile("Jump.ogg");
	Sound sou(buf);
	Music music;
    music.openFromFile("Mario_Theme.ogg");
    music.play();





	int randW, randH;

	//Generate Map
	generateMap(0);
	//generateMap(0);

	Sprite background(t2);

	//Make map entities
	for (int i = 0; i < maxW; i++)
	{
		for (int j = 0; j < maxW; j++)
		{
			if (i % 32 == 0 && j % 32 == 0) {
				if (gameState[i][j] == '0') { //TODO: account for sprite image size
											  //grass *g = new grass();
											  ////a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);//Zombie 

											  //g->settings(bGrass, i, j, 1, 25);
											  ///*	a->settings(sRock, 0, rand() % H, rand() % 360, 25);*/
											  //entities.push_back(g);
				}
				if (gameState[i][j] == '5') {
					wall *w = new wall();
					w->settings(bStone, i, j, 0, 25);//wall
					entities.push_back(w);

				}
				else if (gameState[i][j] == '6') {
					p_wall *pw = new p_wall();
					pw->settings(bBushes, i, j, 0, 25);//wall 
					entities.push_back(pw);
				}
			}
		}
	}



	for (int i = 0; i<15; i++)
	{
		zombie *a = new zombie();
		//a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);//Zombie 

		if (rand() % 2 == 0)//Randomize location 1 Branch : Top/Bot or Left/Right , 2nd Branch , Top, Bot, Left, Right
		{
			if (rand() % 2 == 0)
			{
				std::uniform_int_distribution<> distr(-200, 0); // define the range
				randW = distr(eng);
				randH = rand() % maxH;
			}
			else
			{
				std::uniform_int_distribution<> distr(maxW, maxW + 200); // define the range
				randW = distr(eng);
				randH = rand() % maxH;
			}
		}
		else
		{
			if (rand() % 2 == 0)
			{
				std::uniform_int_distribution<> distr(-200, 0); // define the range
				randH = distr(eng);
				randW = rand() % maxW;
			}
			else
			{
				std::uniform_int_distribution<> distr(H, H + 200); // define the range
				randH = distr(eng);
				randW = rand() % maxW;
			}
		}

		a->settings(sRock, randW, randH, a->angle, 25);
		/*	a->settings(sRock, 0, rand() % H, rand() % 360, 25);*/
		entities.push_back(a);

	}

	player *p = new player();
	p->settings(sPlayer, W/2, H/2, 0, 20);
	entities.push_back(p);

	////////////////////////////
	//generateMap(1);
	/////main loop/////
	Clock clock;
	float time = 0;

	while (app.isOpen())
	{
		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 100;
		if (time > 50) time = 50;

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					bullet *b = new bullet();
					sound.play();
					b->settings(sBullet, p->x, p->y, p->angle, 10);
					entities.push_back(b);
				}
		}

		//Angle Update
		// This is for making Player point towards Mouse
		//	double dX =  Mouse::getPosition().x; // x and y are global Varibales declared outside
		//	double dY =  Mouse::getPosition().y;
		////	double magnitude = sqrt((dX*dX) - (dY*dY));
		//	double normalizedX = dX / magnitude;
		//	double normalizedY = dY / magnitude;
		//	Updating the angle
		//	double mouseAngle = (atan2(dY, dX)) * 180 / 3.14;
		//updateMouseAngle(Mouse::getPosition());
		curPos.x = p->x;//player.getShape().getGlobalBounds().left;
		curPos.y = p->y;//player.getShape().getGlobalBounds().top;
		sf::Vector2i position = sf::Mouse::getPosition(app);
		position = sf::Vector2i(app.mapPixelToCoords(position));
		float dx = curPos.x - position.x;
		float dy = curPos.y - position.y;
		float rotation = (atan2(dy, dx)) * 180 / PI;
		p->angle = rotation + 180;


		//p->angle = -mouseAngle;
		//if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle = 30;
		//if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle = 90;

		//Location Update
		if (Keyboard::isKeyPressed(Keyboard::W)) p->thrustU = true;
		else p->thrustU = false;
		if (Keyboard::isKeyPressed(Keyboard::S)) p->thrustD = true;
		else p->thrustD = false;
		if (Keyboard::isKeyPressed(Keyboard::A)) p->thrustL = true;
		else p->thrustL = false;
		if (Keyboard::isKeyPressed(Keyboard::D)) p->thrustR = true;
		else p->thrustR = false;
		if (Keyboard::isKeyPressed(Keyboard::Num0)) gameMode = 0;
		if (Keyboard::isKeyPressed(Keyboard::Num1)) gameMode = 1;
		if (Keyboard::isKeyPressed(Keyboard::Num2)) gameMode = 2;
		if (Keyboard::isKeyPressed(Keyboard::Num3)) gameMode = 3;
		if (Keyboard::isKeyPressed(Keyboard::Num4)) gameMode = 4;
		if (Keyboard::isKeyPressed(Keyboard::Num5)) gameMode = 5;
		if (Keyboard::isKeyPressed(Keyboard::Num6)) gameMode = 6;
		if (Keyboard::isKeyPressed(Keyboard::Num7)) gameMode = 7;
		if (Keyboard::isKeyPressed(Keyboard::Num8)) gameMode = 8;
		if (Keyboard::isKeyPressed(Keyboard::Num9)) gameMode = 9;





		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "zombie" && b->name == "bullet")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity();

						e->settings(sExplosion, a->x, a->y, a->angle, 1);

						e->name = "explosion";
						sou.play();
						entities.push_back(e);

						/*for (int i = 0; i<2; i++)
						{
						if (a->R == 15) continue;
						Entity *e = new zombie();
						e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
						entities.push_back(e);
						}*/

					}

				if (a->name == "player" && b->name == "zombie")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, 0, 1);
						e->name = "explosion";
						entities.push_back(e);

						p->settings(sPlayer, W / 2, H / 2, 0, 20);
						p->dx = 0; p->dy = 0;
					}

				if (a->name == "zombie" && b->name == "zombie")
					if (isCollide(a, b))
					{

						if (rand() % 2 == 0)
						{
							if (rand() % 2 == 0)//It goes bot left or top right,
							{
								a->y -= 1;
								a->x += 1;
								a->angle = atan2(playerX - a->x, a->y - playerY) * 180 / 3.14 + 180;

								b->y -= 1;
								b->x += 1;
								b->angle = atan2(playerX - b->x, b->y - playerY) * 180 / 3.14 + 180;
							}
							else
							{
								a->y += 1;
								a->x -= 1;
								a->angle = atan2(playerX - a->x, a->y - playerY) * 180 / 3.14 + 180;

								b->y += 1;
								b->x -= 1;
								b->angle = atan2(playerX - b->x, b->y - playerY) * 180 / 3.14 + 180;
							}
						} // a zombie
						else
						{
							if (rand() % 2 == 0)//It goes top left or bot right,
							{
								a->dy += 1 * time;
								a->dx += 1 * time;
								a->angle = atan2(playerX - a->x, a->y - playerY) * 180 / 3.14 + 180;

								b->dy += 1 * time;
								b->dx += 1 * time;
								b->angle = atan2(playerX - b->x, b->y - playerY) * 180 / 3.14 + 180;
							}
							else
							{
								a->dy -= 1 * time;
								a->dx -= 1 * time;
								a->angle = atan2(playerX - a->x, a->y - playerY) * 180 / 3.14 + 180;

								b->dy -= 1 * time;
								b->dx -= 1 * time;
								b->angle = atan2(playerX - b->x, b->y - playerY) * 180 / 3.14 + 180;
							}
						}

					}
			}



		if (p->thrustU)  p->anim = sPlayer;

		else   p->anim = sPlayer;


		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

		if (rand() % 150 == 0)
		{
			if (rand() % 2 == 0)//Randomize location 1 Branch : Top/Bot or Left/Right , 2nd Branch , Top, Bot, Left, Right
			{
				if (rand() % 2 == 0)
				{
					std::uniform_int_distribution<> distr(-200, 0); // define the range
					randW = distr(eng);
					randH = rand() % H;
				}
				else
				{
					std::uniform_int_distribution<> distr(W, W + 200); // define the range
					randW = distr(eng);
					randH = rand() % H;
				}
			}
			else
			{
				if (rand() % 2 == 0)
				{
					std::uniform_int_distribution<> distr(-200, 0); // define the range
					randH = distr(eng);
					randW = rand() % W;
				}
				else
				{
					std::uniform_int_distribution<> distr(H, H + 200); // define the range
					randH = distr(eng);
					randW = rand() % W;
				}
			}
			zombie *a = new zombie();
			a->settings(sRock, randW, randH, rand() % 360, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update(time);

			e->anim.update(time);

			//Update player x and y location global variable
			if (e->name == "player")
			{
				playerX = e->x;
				playerY = e->y;
				if ((e->x <= (maxW - (W / 2)) && e->x > (W / 2)))
				{
					offset_x = e->x - (W / 2);
				}
				if ((e->y <= (maxH - (H / 2)) && e->y > (H / 2)))
				{
					offset_y = e->y - (H / 2);
				}

			}
			if (e->name != "player" && e->name != "zombie")
			{
				//e->x -= offset_x;
				//e->y -= offset_y;	

			}
			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		app.draw(background);

		//Change location based on offset
		//for (auto i = entities.begin(); i != entities.end();)
		//{
		//	Entity *e = *i;
		//	if (e->name != "player")
		//
		//}

		//////draw//////

		//Grass Background//
//
//		for (int i = 0; i< mapW; i++)
//		{
//			for (int j = 0; j < mapH; j++)
//			{
//
//				BCG.setTextureRect(IntRect(0, 0, 32, 32));
//
//				BCG.setPosition(i * 32, j * 32);
//				app.draw(BCG);
//			}
//		}
////upd back
//		for (int i = 0; i < mapW; i++)
//		{
//			for (int j = 0; j < mapH; j++)
//			{
//
//				if (Map[i][j] == 'A') {
//
//					UPD.setTextureRect(IntRect(32, 0, 32, 32));
//
//
//				}
//				else if (Map[i][j] == 'B') {
//
//
//					UPD.setTextureRect(IntRect(64, 0, 32, 32));
//
//
//				}
//				else if (Map[i][j] == ' ') continue;
//
//				UPD.setPosition(i * 32, j * 32);
//				app.draw(UPD);
//
//			}
//		}
//		//app.draw(background);

		for (auto i : entities)
			i->draw(app);


		rectangle1.setFillColor(Color::Color(0,0,0,128));
		rectangle1.setPosition(mMapX, mMapY);
		app.draw(rectangle1);

		for (auto i : entities) {

			/*if (playerXpos/32== i&&playerYpos/32 == j) {
				rectangle.setFillColor(Color::Color(255, 0, 0, 128));*/

			if (i->name == "p_wall") {

				rectangle.setFillColor(Color::Color(0, 255, 0, 128));

			}
			else if (i->name == "zombie") {

				rectangle.setFillColor(Color::Cyan);

			}
			else if (i->name == "bullet") {

				rectangle.setFillColor(Color::Blue);

			}
			else if (i->name == "player") {

				rectangle.setFillColor(Color::Red);

			}
			else if (i->name == "wall") 	rectangle.setFillColor(Color::Color(0, 0, 0, 128));
			rectangle.setPosition((i->x / 32 ) * 4 + mMapX,( i->y / 32)* 4 + mMapY);
			app.draw(rectangle);
		}
	
		//}
		//	


		//}		
		text.setString("Offset X: " + std::to_string(offset_x) + " Offset Y: " + std::to_string(offset_y) + " Player X: " + std::to_string(playerX) + " Player Y: " + std::to_string(playerY));
		app .draw(text);
		app.display();
	}

	return 0;
}


//Map Generator
/////////////////////////////////////////////
//MAP GENERATOR///////////////////////////////
//void generateMap(int mapType) {
//	int h = 0;
//	int w = 0;
//	
//	switch (mapType)
//		{
//	case 1: {
//		for (h; h < mapH; h++) {
//			for (w; w < mapW; w++) {
//				
//				int x = rand() % 50;
//				if (x == 1)Map[h][w] =='B';
//				if (x == 23)Map[h][w] =='A';
//				else Map[h][w] =='C';
//				;
//				
//			}
//		}
//		}
//	default:
//		break;
//	}
//
//void generateMap(int mapType) {
//	int x;
//	for (int i = 0; i < mapW; i++)
//	{
//		x = rand() % 70;
//
//		for (int j = 0; j < mapH; j++)
//		{
//			x = rand() % 70;
//
//			if (x == 60) {
//				Map[i][j] = 'A';
//
//			}
//
//			/*else*/ if (x == 26) {
//				Map[i][j] = 'B';
//			}
//			else if (x != 26 && x != 60)
//			{
//				Map[i][j] = ' ';
//			}
//		}
//	}
//}

void offsetEntities(int howMuchX,int howMuchY) 
{
	for (auto i : entities) {
		if (i->name != "player")
		{
			i->x -= howMuchX;
			i->y -= howMuchY;

		}

	}
}

void generateMap(int mapType) {
	int x;
	for (int i = 0; i < maxW; i++)
	{
		x = rand() % 70;

		for (int j = 0; j < maxH; j++)
		{
			x = rand() % 70;

			if (x == 60) {
				gameState[i][j] = '5';

			}

			/*else*/ if (x == 26) {
				gameState[i][j] = '6';

			}
			else if (x != 26 && x != 60)
			{
				gameState[i][j] = '0';
			}
		}
	}
}

bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}


bool isTooClose(float xPos, float yPos)
{
	std::list<Entity*> ::iterator i;
	Entity* temp;
	float distX;
	float distY;

	float threshold = 1;

	for (i = entities.begin(); i != entities.end(); i++)
	{
		temp = *i;
		distX = abs(xPos - temp->x);
		distY = abs(xPos - temp->y);

		if (distX < W && distY < H)
		{
			if (distX <= threshold || distY <= threshold)
			{
				return true;
			}
		}
		else { return false; }
	}

	return false;

}

float getPlayerX() { return playerX; }
float getPlayerY() { return playerY; }

