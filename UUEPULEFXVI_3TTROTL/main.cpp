#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <random>
#include <list>
#include<math.h>
#include "constants.h"
#include<SFML\Network.hpp>

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

int main();
//int gameWon = false;
void offsetEntities(int howMuchX, int howMuchY);
bool isOutsideMap(int howMuchX, int howMuchY);

int mapZoomVal = 1; //On the minimap this number defines the zoom level of the map , 1x ,2x zoom etc
int updZombieLife(float time);

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
#include "Weapon.h"
bool calculateDistance(Entity *b, weapon *c);
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
std::list < RectangleShape* >   bgRects; //background rectangls

							 //std::list<Entity*> entities;


							 //main
int main()

{
	int scene = 2;
	int gameWonScore = 100;
	bool mousePress = false;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator

	//Statistics
	int livesRemaining = 3, zombiesKilled = 0, bulletsShot = 0; //Bullet shot records each click, for eg. shotgun will be 1 even though you shoot 16 bullets

	double mouseXpos, mouseYpos, mouseAngle;
	sf::Vector2f curPos;
	int zlcoef = 1;
	srand(time(0));
	// Load the font from a file
	sf::Font font;
	if (!font.loadFromFile("fonts/baksheeshregular.ttf"))
	{
		// error...
	}
	sf::Text text,reload;
	View VieW;
	// select the font
	text.setFont(font);
	text.setCharacterSize(28);
	text.setColor(sf::Color::Red);
	//text.setStyle(sf::Text::Bold);
	
	reload.setFont(font);
	reload.setCharacterSize(20);
	reload.setColor(Color::Color(255, 0, 0, 128));
	//reload.setStyle(sf::Text::Bold);
	sf::Text debug, gameover;

	// select the font for debug
	debug.setFont(font);
	debug.setCharacterSize(28);
	debug.setColor(sf::Color::Red);
	debug.setStyle(sf::Text::Bold);

	// select the font for gameover
	gameover.setFont(font);
	gameover.setCharacterSize(64);
	gameover.setOutlineThickness(5);
	gameover.setColor(sf::Color::Red);
	//gameover.setStyle(sf::Text::Bold);
	gameover.setPosition(sf::Vector2f(100, H / 2));
	gameover.setString("GAME OVER!      press enter to restart");

	RenderWindow app(VideoMode(W, H), "The third return of the legend!");
	//app.setFramerateLimit(120);


	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t11, t12, t13, t14,t15,t21,t22,t23,t24;
	t1.loadFromFile("images/Player_top.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/explosions/enemy_die.png");
	t4.loadFromFile("images/enemy_move.png");
	t5.loadFromFile("images/Bullet.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/LEG_ANIM1.png");
	///

	if (scene == 1) {
		//t9.loadFromFile("images/background/bcg.png");
		t11.loadFromFile("images/background/grass.png");
		t12.loadFromFile("images/background/stone.png");
		t13.loadFromFile("images/background/Bush.png");
		//t14.loadFromFile("images/background/grass_14.png");
	}
	if (scene = 2) {
		t11.loadFromFile("images/scene2/bg.png"); //BG
		t12.loadFromFile("images/scene2/skull.png");
		t13.loadFromFile("images/scene2/cactus.png");
		t21.loadFromFile("images/scene2/stone1.png");
		t22.loadFromFile("images/scene2/stone2.png");
		t23.loadFromFile("images/scene2/stone3.png");
		t24.loadFromFile("images/scene2/tree.png");
	}

	t14.loadFromFile("images/UI/lives.png");



	//Weapons texture
	Texture w1, w2, w3, w4, w5,w6;
	w1.loadFromFile("images/weapons/rpg.png");
	w2.loadFromFile("images/weapons/machine.png");
	w3.loadFromFile("images/weapons/pistol.png");
	w4.loadFromFile("images/weapons/rifle.png");
	w5.loadFromFile("images/weapons/shotgun.png");
	w6.loadFromFile("images/weapons/blackbox.png");
	Animation arpg(w1, 0, 0, 300, 200, 1, 0);
	Animation amachine(w2, 0, 0, 300, 200, 1, 0);
	Animation apistol(w3, 0, 0, 300, 200, 1, 0);
	Animation arifle(w4, 0, 0, 300, 200, 1, 0);
	Animation ashotgun(w5, 0, 0, 300, 200, 1, 0);
	//pickable texture
	Texture p1, p2, p3, p4, p5, p6;
	p1.loadFromFile("images/weapons/pickable/rpg_pick.png");
	p2.loadFromFile("images/weapons/pickable/machine_pick.png");
	p3.loadFromFile("images/weapons/pickable/pistol_pick.png");
	p4.loadFromFile("images/weapons/pickable/rifle_pick.png");
	p5.loadFromFile("images/weapons/pickable/shotgun_pick.png");
	Animation p_rpg(p1, 0, 0, 90, 20, 1, 0);
	Animation p_machine(p2, 0, 0, 91, 29, 1, 0);
	Animation p_pistol(p3, 0, 0, 55, 31, 1, 0);
	Animation p_rifle(p4, 0, 0, 89, 18, 1, 0);
	Animation p_shotgun(p5, 0, 0, 85, 29, 1, 0);

	/*Animation Ww1(w1, 0, 0, 300, 100, 1, 0);
	Animation Ww2(w2, 0, 0, 300, 100, 1, 0);
	Animation Ww3(w3, 0, 0, 300, 100, 1, 0);
	Animation Ww4(w4, 0, 0, 300, 100, 1, 0);
	Animation Ww5(w5, 0, 0, 300, 100, 1, 0);*/
	RectangleShape weapons_ui(Vector2f(300/1.5, 100/1.5));

	Sprite BCG(t9);
	Sprite UPD(t9);



	//RectangleShape rect(Ve;
	t1.setSmooth(true);
	t2.setSmooth(true);
	t14.setSmooth(true);




	RectangleShape rectangle(Vector2f(4, 4));
	//sf::CircleShape octagon(4, 8);
	RectangleShape rectangle1(Vector2f(200, 200));
	RectangleShape blackbox(Vector2f(300 / 1.5, 130 / 1.25));
	RectangleShape livesbox(Vector2f(300 / 1.5, 130 / 1.25));

	int mMapX = W/2-10-4*mapH;
	int mMapY =H/2-10-4*mapW;

	//Sprite background(t14);

	Animation sExplosion(t3, 0, 0, 120.5, 73, 6, 0.1);
	Animation sRock(t4, 0, 0, 120.5, 53, 6, 0.1);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(t5, 0, 0, 18, 38, 1, 0);

	Animation sPlayer(t1, 0, 0, 57, 99, 1, 0);
	//Animation sPlayer(t1, 0, 0, 57, 99, 1, 0);
	Animation sPlayer_go(t1, 0, 0, 57, 99, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
	Animation sLeg(t1, 0, 0, 57, 99, 1, 0);

	//Background entities
	if (scene == 1) {	

		Animation bGrass(t11, 0, 0, 32, 32, 1, 0);
		Animation bStone(t12, 0, 0, 32, 32, 1, 0); // skul;
		Animation bBushes(t13, 0, 0, 32, 32, 1, 0);//cactus
	}
	if (scene == 2) {
		Animation bGrass(t11, 0, 0, 32, 32, 1, 0);
		Animation bStone(t12, 0, 0, 34, 42, 1, 0); // skul;
		Animation bBushes(t13, 0, 0, 40, 61, 1, 0);//cactus
	}
	Animation bGrass(t11, 0, 0, 32, 32, 1, 0);
	Animation bStone(t12, 0, 0, 34, 42, 1, 0); // skul;
	Animation bBushes(t13, 0, 0, 40, 61, 1, 0);//cactus
	Animation bStone1(t21, 0, 0, 48, 46, 1, 0);
	Animation bStone2(t22, 0, 0, 65, 60, 1, 0);
	Animation bStone3(t23, 0, 0, 50, 49, 1, 0);
	Animation bTree(t24, 0, 0, 69, 104, 1, 0);

//	Animation bBackground(t14, 0, 0, 1600, 1600, 1, 0);


	SoundBuffer psound,ssound,msound,rsound,rpsound;
	psound.loadFromFile("sound/weapon/pistol.wav");
	ssound.loadFromFile("sound/weapon/shotgun.wav");
	rsound.loadFromFile("sound/weapon/rifle.wav");
	rpsound.loadFromFile("sound/weapon/RPG.wav");
	msound.loadFromFile("sound/weapon/machinegun.wav");
	
	SoundBuffer kill;
	//kill.loadFromFile("sound/kill/Jump.ogg");
	kill.loadFromFile("sound/kill/hitmarker.wav");
	Sound zkill(kill);
	Music music;
	music.openFromFile("sound/Theme.wav");
	music.setLoop(true);
	music.play();

	
	
	
	weapon *pistol=new weapon();
	weapon *rifle=new weapon();
	weapon *shotgun=new weapon();
	weapon *rpg=new weapon();
	weapon *machinegun=new weapon();
	pistol->weaponSetup(psound, 60, 10, 5, 20, 1, 320,"pistol");
	rifle->weaponSetup(rsound, 120, 30, 3, 50, 1, 720,"rifle");
	shotgun->weaponSetup(ssound, 60, 8, 5, 30, 35, 320,"shotgun");
	machinegun->weaponSetup(msound, 300, 240, 10, 20, 1, 500,"machine");
	rpg->weaponSetup(rpsound, 40, 5, 10, 400, 1, 900,"rpg");

	int randW, randH;

	//Generate Map
	generateMap(0);
	//generateMap(0);

	//Sprite background(t11);aaaaaa

	//Make map entities
	
	//background entity
	//Entity *bg = new Entity();
	//bg->settings(bBushes, 0, 0, 0, 0);//bg 
	//entities.push_back(bg);

	//Weapon entity
	float gTime = 0;//time of the game
	weapon *w = new weapon();
	w->weaponSetup(psound, 60, 2, 3, 20, 50, 500,"test");
	w->weaponcopy(pistol,msound);
	entities.push_back(w);

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
					//p_wall *pw = new p_wall();
					//pw->settings(bGrass, i, j, 0, 25);//wall 
					//entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);

		
				}
				if (gameState[i][j] == '5') {
					wall *w = new wall();
					w->settings(bStone, i, j, -90, 25);//wall
					entities.push_back(w);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);

				}
				else if (gameState[i][j] == '6') {
					p_wall *pw = new p_wall();
					pw->settings(bBushes, i, j, -90, 25);//wall 
					entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);
				}
				else if (gameState[i][j] == '7') {
					p_wall *pw = new p_wall();
					pw->settings(bStone1, i, j, -90, 25);//wall 
					entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);
				}
				else if (gameState[i][j] == '8') {
					p_wall *pw = new p_wall();
					pw->settings(bStone2, i, j, -90, 25);//wall 
					entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);
				}
				else if (gameState[i][j] == '9') {
					p_wall *pw = new p_wall();
					pw->settings(bStone3, i, j, -90, 25);//wall 
					entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);
				}
				else if (gameState[i][j] == '10') {
					p_wall *pw = new p_wall();
					pw->settings(bTree, i, j, -90, 25);//wall 
					entities.push_back(pw);
					//Draw background rectangles
					RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					bgRectangle->setTexture(&t11);
					bgRectangle->setPosition(Vector2f(i, j));
					bgRects.push_back(bgRectangle);
				}
				//else if (gameState[i][j] == '11') {
				//	wall *w = new wall();
					//w->settings(bStone, i, j, 0, 25);//wall 
				//	entities.push_back(w);
					//Draw background rectangles
					//RectangleShape *bgRectangle = new RectangleShape(Vector2f(32, 32));
					//bgRectangle->setTexture(&t11);
					//bgRectangle->setPosition(Vector2f(i, j));
					//bgRects.push_back(bgRectangle);
				//}
				
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
	p->settings(sPlayer, (maxW / 2) / mapZoomVal , (maxH / 2) / mapZoomVal, 0, 20);
	entities.push_back(p);

	////////////////////////////
	//generateMap(1);
	/////main loop/////
	Clock clock;
	float time = 0;


	//for (auto i : entities) {
	//	//if (i->name != "player")
	//	//{
	//		i->x -= -160;
	//		i->y -= -440;
	//	//	offset_x += howMuchX;
	//	//	offset_y += howMuchY;
	//	//}
	//}

	//offsetEntities(-(maxW/2 - W/2), (maxH/2 - H/2));

	while (app.isOpen())
	{

		if (livesRemaining >= 0 && zombiesKilled < gameWonScore)
		{
		//
	
		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 100;
		//if (time > 20) time = 20;

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			
			//if (event.type == Event::KeyPressed)
			//app.setKeyRepeatEnabled(true);
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
			//	if (event.mouseButton.button == sf::Mouse::Left)
					//mousePress = true;
					
						//if (event.key.code == Keyboard::Space)
						//while (event.type == Event::MouseButtonReleased)
					{

						//bullet *b = new bullet();
						//	sound.play();
						//	b->settings(sBullet, p->x, p->y, p->angle, 10);
						//	entities.push_back(b);

						if (w->canshoot(time) && w->currammo > 0) {

							bulletsShot++;
							if (w->spt > 1) {
								for (int i = 0; i < ((rand() % w->spt - w->spt / 10) + w->spt / 10); i++) {
									//and() % (max_number + 1 - minimum_number) + minimum_number
									bullet *b = new bullet();
									
									b->settings(sBullet, p->x, p->y, p->angle - 45 + rand() % 90, 10);
									b->anim.sprite.setScale(0.3, 0.3);
									b->xpos = p->x;
									b->ypos = p->y;
									entities.push_back(b);
								}
							}
							else {
								bullet *b = new bullet();
								b->settings(sBullet, p->x, p->y, p->angle, 10);
								b->anim.sprite.setScale(0.3, 0.3);
								b->xpos = p->x;
								b->ypos = p->y;
								entities.push_back(b);
							}
							w->shoot_sound();

							w->currammo--;
							w->counter_spm = 0;
						}


					}

	
			}
			//mousePress = false;
			//if (sf::Event::KeyReleased)
			//{
			////	if (event.mouseButton.button == sf::Mouse::Left)
			//		//mousePress = false;
			//		zombiesKilled == 0;
			//}
			//if (event.mouseButton.button == sf::Mouse::Left)
			
		}
		if (gTime>60000) {
			zlcoef = updZombieLife(gTime);
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
		if (Keyboard::isKeyPressed(Keyboard::Dash)) gameMode = 9;
				if (Keyboard::isKeyPressed(Keyboard::Dash)) mapZoomVal = 1;
				if (Keyboard::isKeyPressed(Keyboard::Equal)) mapZoomVal =  2; // Only for testing, has bugs

				if (Keyboard::isKeyPressed(Keyboard::P)) scene = 0;
				if (Keyboard::isKeyPressed(Keyboard::O)) scene = 0;






		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "zombie" && b->name == "bullet")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;
						if (b->life == false) zombiesKilled++;
						Entity *e = new Entity();

						e->settings(sExplosion, a->x, a->y, a->angle, 1);

						e->name = "explosion";
						zkill.play();
						entities.push_back(e);
						//create pickable items
						if (rand() % 10 == 0) {
							pickup *pik = new pickup();
							pik->settings(bStone, a->x, a->y, a->angle, 25);
							//int x = rand() % 3;
							//if (x == 0) {
								//buff
							
							//else if (x == 1) {
								//debuff

							
							
								//weapon
								int y = rand() % 4;
								if (y == 0) {
									//pik->anim///
									pik->type = "pistol";
									pik->settings(p_pistol, a->x, a->y, a->angle, 25);

								}
								if (y == 1) {
									//pik->anim///
									pik->type = "shotgun";
									pik->settings(p_shotgun, a->x, a->y, a->angle, 25);

								}
								if (y == 2) {
									//pik->anim///
									pik->type = "rifle";
									pik->settings(p_rifle, a->x, a->y, a->angle, 25);

								}
								if (y == 3) {
									//pik->anim///
									pik->type = "machinegun";
									pik->settings(p_machine, a->x, a->y, a->angle, 25);

								}
								//if (y == 4) {
									//pik->anim///
									//->type = "rpg";
									//pik->settings(p_rpg, a->x, a->y, a->angle, 25);

								//}

							
							
						
						
								entities.push_back(pik);

						}
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

						p->settings(sPlayer, (maxW / 2) / mapZoomVal, (maxH / 2) / mapZoomVal, 0, 20);
						p->dx = 0; p->dy = 0;
						livesRemaining--;
					}
				if (a->name == "player"&& b->name == "pickup") {
				//weapons 
					if (isCollide(a, b))
					{
						if (b->type == "pistol") {
							w->weaponcopy(pistol, psound);
						}
						if (b->type == "rifle") {
							w->weaponcopy(rifle, rsound);
						}
						if (b->type == "shotgun") {
							w->weaponcopy(shotgun, psound);
						}
						if (b->type == "machinegun") {
							w->weaponcopy(machinegun, msound);
						}
						//if (b->type == "rpg") {
							//w->weaponcopy(rpg, rpsound);
						//}
						b->life = false;
						//buff
						//debuff
					}
				
				
				
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


		for (auto e : entities) {
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;
			if (e->name == "bullet") {
				if (calculateDistance(e,w))
					e->life = false;
			}
			
			
		}
		if (rand() % 50 == 0)
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
				//if ((e->x <= (maxW - (W / 2)) && e->x > (W / 2)))
				//{
				//	offset_x = e->x - (W / 2);
				//}
				//if ((e->y <= (maxH - (H / 2)) && e->y > (H / 2)))
				//{
				//	offset_y = e->y - (H / 2);
				//}

			}
			if (e->name != "player" && e->name != "zombie")
			{
				//e->x -= offset_x;
				//e->y -= offset_y;	

			}
			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}


			//		app.draw(background);

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

			for (auto i : bgRects)
				app.draw(*i);

			for (auto i : entities)
				i->draw(app);



			

			//SET VIEW
			float viewX = 0;
			float viewY = 0;
			if (p->x < W / 2)viewX = W / 2; if (p->y < H / 2)viewY = H / 2;
			if (p->x > (maxW - W / 2))viewX = maxW - W / 2; if (p->y > (maxH - H / 2))viewY = maxH - H / 2;
			if (p->x > W / 2 & p->x < (maxW - W / 2))viewX = p->x; if (p->y > H / 2 & p->y < (maxH - H / 2))viewY = p->y;
			/*if (p->y < H / 2 || p->x < W / 2) {
				if (p->y < H / 2 && p->x < W / 2) {
					VieW.setCenter(W / 2, H / 2);
				}
				else if (p->y < H / 2) {
					VieW.setCenter(p->x, H / 2);
				}
				else if (p->x <W / 2) {
					VieW.setCenter(W / 2, p->y);
				}

			}
			else if (p->x >(maxW-W/2) || p->y >(maxH-H/2)) {
				if (p->x >  (maxW - W / 2) && p->y > (maxH - H / 2)) {
					VieW.setCenter((maxW - W / 2), (maxH - H / 2));
				}
				else if (p->x >(maxW - W / 2)) {
					VieW.setCenter(maxW - W / 2, p->y);
				}
				
				else if (p->y >(maxH - H / 2)) {
					VieW.setCenter(p->x, (maxH - H / 2));
				}
			}*/
		/*	else if (p->x<W / 2 && p->y>(maxH - H / 2)) {
				VieW.setCenter(W / 2, maxH - H / 2);
			}*/
			/*else {
				VieW.setCenter(p->x, p->y);
			}*/
			VieW.setCenter(viewX, viewY);
			VieW.setSize(W, H);
			app.setView(VieW);

			////////////////////////////////////////////////////////////////////////////
			//DRAW MAP//
			//Minimap background
			rectangle1.setFillColor(Color::Color(0, 0, 0, 128));
			rectangle1.setPosition(viewX+mMapX, viewY+mMapY);
			app.draw(rectangle1);
			//Minimap entities
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
				else if (i->name == "wall") 	rectangle.setFillColor(Color::White);

				rectangle.setPosition((i->x / 32 * mapZoomVal) * 4 +viewX+mMapX, (i->y / 32 * mapZoomVal) * 4 +viewY+mMapY);
				if (i->x >= 0 && i->y >= 0 &&
					i->x < maxW / mapZoomVal && i->y < maxH / mapZoomVal)
				{
					if (i->name == "zombie")
					{
						rectangle.setSize((Vector2f(5 * mapZoomVal, 5 * mapZoomVal)));
						app.draw(rectangle);

					}
					else
					{
						rectangle.setSize((Vector2f(3 * mapZoomVal, 3 * mapZoomVal)));
						app.draw(rectangle);

					}

				}
			}
			//}		
			//text.setString("Offset X: " + std::to_string(offset_x) + " Offset Y: " + std::to_string(offset_y) + " Player X: " + std::to_string(playerX) + " Player Y: " + std::to_string(playerY));
			//text.setString("Lives Remaining: " + std::to_string(livesRemaining) +
			//	"                                                                                                            Score: " + std::to_string(zombiesKilled));//+ "Bullets Shot" + std::to_string(bulletsShot));
			//text.setPosition(viewX-W/2,viewY-H/2);
			//app.draw(text);
			text.setColor(sf::Color::White);
			text.setString("   " + std::to_string(w->currammo));// +"         Current weapon:" + w->type )
			text.setPosition(viewX - W / 2+25, viewY + H / 2-48);
			app.draw(text);
			text.setColor(sf::Color::Red);

			if (w->currammo == 0) {
				reload.setString("Reloading... " + std::to_string(int(w->wreloadpercentage())) + "%");
				reload.setPosition(p->x+30, p->y - 40);
				app.draw(reload);
			}
			app.draw(debug);

			//Lives UI
			//text.setString("Lives Remaining: " + std::to_string(livesRemaining) +
			//	"                                                                                                            Score: " + std::to_string(zombiesKilled));//+ "Bullets Shot" + std::to_string(bulletsShot));
			//text.setPosition(viewX - W / 2, viewY - H / 2);
			//app.draw(text);
			//text.setColor(sf::Color::White);

			//lives box
			livesbox.setScale(0.5, 1);
			livesbox.setFillColor(Color::Color(0, 0, 0, 150));
			livesbox.setTexture(&t14);
			livesbox.setPosition(viewX - (W / 2) + 10, viewY - (H / 2)+5);
			app.draw(livesbox);

			//score box
			livesbox.setScale(1.15, 1);
			livesbox.setFillColor(Color::Color(0, 0, 0, 150));
			livesbox.setTexture(&t14);
			livesbox.setPosition(viewX + (W / 2) - 10 - 230, viewY - (H / 2) + 5);
			app.draw(livesbox);

			//Lives UI text
			text.setColor(sf::Color::White);
			text.setCharacterSize(32);
			text.setString("Lives:");//  Score: " + std::to_string(zombiesKilled));//+ "Bullets Shot" + std::to_string(bulletsShot));
			text.setPosition(viewX - W / 2 + 25, viewY - H / 2+ 15);
			app.draw(text);
			//
			text.setCharacterSize(40);
			text.setPosition(viewX - W / 2 + 55, viewY - H / 2+50);
			text.setString(std::to_string(livesRemaining));
			app.draw(text);
			text.setCharacterSize(28);
			//Score UI
			text.setColor(sf::Color::White);
			text.setCharacterSize(32);
			text.setString("Zombies Killed");//  Score: " + std::to_string(zombiesKilled));//+ "Bullets Shot" + std::to_string(bulletsShot));
			text.setPosition(viewX + W / 2 - 25 -200, viewY - H / 2 + 5 +5);
			app.draw(text);
			//
			text.setCharacterSize(40);
			text.setPosition(viewX + W / 2 - 60 -75 -30, viewY - H / 2 + 40 + 5);
			text.setString(std::to_string(zombiesKilled) + "/" + std::to_string(gameWonScore));
			app.draw(text);
			text.setCharacterSize(28);


			//Weapon UIs
			//black box
			blackbox.setFillColor(Color::Color(0, 0, 0, 25));
			blackbox.setPosition(viewX - (W / 2) + 5, viewY + (H / 2) - 116);
			app.draw(blackbox);

			//weapon
			weapons_ui.setPosition(viewX - (W / 2) + 5, viewY + (H / 2) - 100);
			//shadow
			weapons_ui.setScale(Vector2f(1, 1.125));
			weapons_ui.setFillColor(sf::Color::Color(0, 0, 0, 50));
			//weapons_ui.setTexture(&w6);
			app.draw(weapons_ui);

			//gun
			weapons_ui.setScale(Vector2f(1, 1));
			weapons_ui.setFillColor(sf::Color::White);
			app.draw(weapons_ui);
			if (w->type == "rpg")
			{
				weapons_ui.setTexture(&w1);
			}
			if (w->type == "machine")
			{
				weapons_ui.setTexture(&w2);
			}
			if (w->type == "pistol")
			{
				weapons_ui.setTexture(&w3);
			}
			if (w->type == "rifle")
			{
				weapons_ui.setTexture(&w4);
			}
			if (w->type == "shotgun")
			{
				weapons_ui.setTexture(&w5);
			}
			app.draw(weapons_ui);

			app.display();
		}
		else
		{
			for (auto i : bgRects)
				app.draw(*i);

			for (auto i : entities)
				i->draw(app);



			rectangle1.setFillColor(Color::Color(0, 0, 0, 128));
			rectangle1.setPosition(mMapX, mMapY);
			//app.draw(rectangle1);


			//Draw the map
			//for (auto i : entities) {

			//	/*if (playerXpos/32== i&&playerYpos/32 == j) {
			//	rectangle.setFillColor(Color::Color(255, 0, 0, 128));*/

			//	if (i->name == "p_wall") {

			//		rectangle.setFillColor(Color::Color(0, 255, 0, 128));

			//	}
			//	else if (i->name == "zombie") {

			//		rectangle.setFillColor(Color::Cyan);

			//	}
			//	else if (i->name == "bullet") {

			//		rectangle.setFillColor(Color::Blue);

			//	}
			//	else if (i->name == "player") {

			//		rectangle.setFillColor(Color::Red);

			//	}
			//	else if (i->name == "wall") 	rectangle.setFillColor(Color::White);
			//	
			//	rectangle.setPosition((i->x / 32 * mapZoomVal) * 4 + mMapX, (i->y / 32 * mapZoomVal) * 4 + mMapY);
			//	if (i->x >= 0 && i->y >= 0 &&
			//		i->x < maxW / mapZoomVal && i->y < maxH / mapZoomVal)
			//	{
			//		if (i->name == "zombie")
			//		{
			//			rectangle.setSize((Vector2f(5 * mapZoomVal, 5 * mapZoomVal)));
			//			app.draw(rectangle);

			//		}
			//		else
			//		{
			//			rectangle.setSize((Vector2f(3 * mapZoomVal, 3 * mapZoomVal)));
			//			app.draw(rectangle);

			//		}

			//	}
			//}

			//}
			//	


			//}		
			//text.setString("Offset X: " + std::to_string(offset_x) + " Offset Y: " + std::to_string(offset_y) + " Player X: " + std::to_string(playerX) + " Player Y: " + std::to_string(playerY));
			//text.setString("Lives Remaining: " + std::to_string(livesRemaining) +
			//	"                                                                                                    Score: " + std::to_string(zombiesKilled));//+ "Bullets Shot" + std::to_string(bulletsShot));
			


			app.draw(text);
			gameover.setColor(Color::Green);

			gameover.setPosition(sf::Vector2f(p->x, p->y));
			gameover.setString("\GAME WON!!!");

			if (livesRemaining < 0)
			{
				gameover.setColor(sf::Color::Red);
				//gameover.setStyle(sf::Text::Bold);
				gameover.setPosition(sf::Vector2f(p->x, p->y));
				gameover.setString("GAME OVER!");
				//w->weaponcopy(pistol, psound);

			}
			app.draw(gameover);

			app.draw(debug);

			app.display();
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				livesRemaining = 3;
				zombiesKilled = 0;
				bulletsShot = 0;
				//gameWon = false;
		
			}
			for (auto i : entities)
			{
				if (i->name == "zombie") i->life = 0;
			}
		}
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

void offsetEntities(int howMuchX, int howMuchY)
{
	//if ((offset_x + howMuchX <= 5452 && offset_x + howMuchX > 20334) &&
	//	(offset_y + howMuchY <= 8685 && offset_y + howMuchY > 74849))//limit boundaries
	//{

		//offset map rectangles
		for (auto i : bgRects) {
			i->setPosition(Vector2f(i->getPosition().x - howMuchX, i->getPosition().y - howMuchY));
			//-= howMuchX i->y -= howMuchY;
		}
		for (auto i : entities) {
			if (i->name != "player")
			{
				i->x -= howMuchX;
				i->y -= howMuchY;

			}
			offset_x += howMuchX;
			offset_y += howMuchY;
		}
	//}
}

bool isOutsideMap(int howMuchX, int howMuchY)
{
	//for (auto i : entities)
	//{
	//	if ((i->x + howMuchX) < 0 || i->x + howMuchX > maxW
	//		|| i->y + howMuchY < 0 || i->y + howMuchY > maxH)
	//	{
			return true;
	//	}
	//	else return false;
	//}
}

void generateMap(int mapType) {
	int x;
	for (int i = 0; i < maxW; i++)
	{
		x = rand() % 100;

		for (int j = 0; j < maxH; j++)
		{
			//make boundary
			//if (i%maxW == 0 || j%maxH == 0)
			///{
			//	gameState[i][j] = '11';
			//}
			//else
			//{

				x = rand() % 200;

				if (x == 10) {
					gameState[i][j] = '5';

				}

				if (x == 20) {
					gameState[i][j] = '6';

				}				
				if (x == 30) {
					gameState[i][j] = '7';

				}

				if (x == 40) {
					gameState[i][j] = '8';

				}				
				if (x == 50) {
					gameState[i][j] = '9';

				}

				if (x == 60) {
					gameState[i][j] = '10';

				}
				else if (x != 10 && x != 20 && x != 30 && x != 40 && x != 50 && x != 60)
				{
					gameState[i][j] = '0';
				}
			//}

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



bool calculateDistance(Entity *b, weapon *c) {
	return abs(sqrt((b->x - b->xpos)*(b->x - b->xpos) +
		(b->y - b->ypos)*(b->y - b->ypos)))>c->dist;
}

void NewMapGenerator(int Breakable, int Unbreakable, Entity e) {


}
int updZombieLife(float time) {
	return  int(time / 60000);
}

