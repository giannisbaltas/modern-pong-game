#pragma once

#include "gameobjects.h"
#include "config.h"
#include <random>

class Paddle;

class Ball : public GameObject
{
    float posx = 150 , posy = (float)rand() / (RAND_MAX + 1)*CANVAS_HEIGHT;
    float speedx, speedy;
    bool active = true;
public:
    float getPosX() { return posx; }
    float getPosY() { return posy; }
	void update() override;
	void draw() override;
	void init() override;
    bool isActive() { return active; }
    bool isOutsideLeft();
    bool isOutsideRight();
    void checkHitLeftPaddle(float paddley, float paddlex);
    void checkHitRightPaddle(float paddlex, float paddley);
    Ball();
	~Ball();
};
