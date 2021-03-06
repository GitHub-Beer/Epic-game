#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	float Frame, speed, size;
	Sprite sprite;

	std::vector<IntRect> frames;
	
	Animation() {}

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
	{
		Frame = 0;
		speed = Speed;
		size = 1;
		for (int i = 0; i<count; i++)
			frames.push_back(IntRect(x + i*w, y, w, h));

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);
	}


	void update(float time)
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
#endif
