#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>

using namespace sf;
int playerXpos, playerYpos;//player location
double mouseXpos, mouseYpos, mouseAngle;//mouse location

int gameMode = 1;//{ 0,1,2,3,4,5,6,7,8,9 }; //This game will feature 10 game modes, 0= default
const int W = 1200;
const int H = 800;
const float PI = 3.14159265;
float DEGTORAD = 0.017453f;//This commend was modified in the new branch again 2
void updateMouseAngle(sf::Vector2i); // This is for making Player point towards Mouse


class Animation
{
public:
	float Frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;

	Animation() {}

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
	{
		Frame = 0;
		speed = Speed;

		for (int i = 0; i<count; i++)
			frames.push_back(IntRect(x + i*w, y, w, h));

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);
	}


	void update()
	{
		Frame += speed;
		int n = frames.size();
		if (Frame >= n) Frame -= n;
		if (n>0) sprite.setTextureRect(frames[int(Frame)]);
	}

	bool isEnd()
	{
		return Frame + speed >= frames.size();
	}

};


class Entity
{
public:
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;

	Entity()
	{
		life = 1;
	}



	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1)
	{
		anim = a;
		x = X; y = Y;
		angle = Angle;
		R = radius;
	}

	virtual void update() {};

	void draw(RenderWindow &app)
	{
		anim.sprite.setPosition(x, y);
		anim.sprite.setRotation(angle + 90);
		app.draw(anim.sprite);

		CircleShape circle(R);
		circle.setFillColor(Color(255, 0, 0, 170));
		circle.setPosition(x, y);
		circle.setOrigin(R, R);
		//app.draw(circle);
	}

	virtual ~Entity() {};
};


class asteroid : public Entity
{
public:
	asteroid()
	{
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
		name = "asteroid";
	}

	void  update()
	{
		switch (gameMode)
		{
			case 0: {x += dx; y += dy; };// Orignal
			case 1: 
			{
				if (x<playerXpos)
				{
					x += 1;
				}
				else
				{
					x -= 1;
				}
				if (y<playerYpos)
				{
					y += 1;
				}
				else
				{
					y -= 1;
				}
			};//Enemies follow you
			case 2: {};
			case 3: {};
			case 4: {};
			case 5: {};
			case 6: {};
			case 7: {};
			case 8: {};
			case 9: {};
			default:
			{
				//x += dx;
				//y += dy;
			}
		}
		//x += dx;
		//y += dy;

		if (x>W) x = 0;  if (x<0) x = W;
		if (y>H) y = 0;  if (y<0) y = H;
	}

};



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


class player : public Entity
{
public:
	bool thrustU,thrustD,thrustL,thrustR;
	player()
	{
		name = "player";
	}

	void update()
	{
		if (thrustU)
		{
			//dx += cos(angle*DEGTORAD)*0.2;
			//dy += sin(angle*DEGTORAD)*0.2;
			dy -= 0.099;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		if (thrustD)
		{
			//dx -= cos(angle*DEGTORAD)*0.2;
			//dy -= sin(angle*DEGTORAD)*0.2;
			dy += 0.099;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		if (thrustL)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx -= 0.099;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		if (thrustR)
		{
			//dx += sin(angle*DEGTORAD)*0.2;
			//dy += cos(angle*DEGTORAD)*0.2;
			dx += 0.099;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		int maxSpeed = 15;
		float speed = sqrt(dx*dx + dy*dy);
		if (speed>maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		x += dx;
		y += dy;

		if (x>W) x = 0; if (x<0) x = W;
		if (y>H) y = 0; if (y<0) y = H;
		playerXpos = x;
		playerYpos = y;
	}

};


bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}


int main()
{


	sf::Vector2f curPos;

	srand(time(0));
	// Load the font from a file
	sf::Font MyFont;
	if (!MyFont.loadFromFile("/fonts/verdana.ttf"))
	{
		// Error...
	}
	//sf::String Log;
	//Log = "Hello";
	//Log
	//Log.setSize(50);

	RenderWindow app(VideoMode(W, H), "The third return of the legend!");
	app.setFramerateLimit(60);


	Texture t1, t2, t3, t4, t5, t6, t7;
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(t1, 0, 0, 40, 40, 1, 0);
	Animation sPlayer_go(t1, 0, 40, 40, 40, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

   
	std::list<Entity*> entities;

	for (int i = 0; i<15; i++)
	{
		asteroid *a = new asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
	}

	player *p = new player();
	p->settings(sPlayer, 200, 200, 0, 20);
	entities.push_back(p);

	/////main loop/////
	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					bullet *b = new bullet();
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



		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "asteroid" && b->name == "bullet")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);


						for (int i = 0; i<2; i++)
						{
							if (a->R == 15) continue;
							Entity *e = new asteroid();
							e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
							entities.push_back(e);
						}

					}

				if (a->name == "player" && b->name == "asteroid")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);

						p->settings(sPlayer, W / 2, H / 2, 0, 20);
						p->dx = 0; p->dy = 0;
					}
			}


		if (p->thrustU)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;


		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

		if (rand() % 150 == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sRock, 0, rand() % H, rand() % 360, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}



		//////draw//////
		app.draw(background);

		for (auto i : entities)
			i->draw(app);

		app.display();
	}

	return 0;
}
