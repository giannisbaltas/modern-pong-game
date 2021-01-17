#pragma once
#include "gameobjects.h"
#include "config.h"

class Paddle : public GameObject
{
	float speed = 8.0f;
	float pos_x_rightpaddle = CANVAS_WIDTH  - 20 , pos_y_rightpaddle = CANVAS_HEIGHT/2;
	float pos_x_leftpaddle = 20 , pos_y_leftpaddle = CANVAS_HEIGHT/2;
	int scoreR = 0;
	int scoreL = 0;
public:
	float getPosYLeftPaddle() { return pos_y_leftpaddle;}
	float getPosXLeftPaddle() { return pos_x_leftpaddle;}
	float getPosYRightPaddle() { return pos_y_rightpaddle;}
	float getPosXRightPaddle() { return pos_x_rightpaddle;}
	void update() override;
	void draw() override;
	void init() override;
	void increaseScoreR();
	void increaseScoreL();
	int getScoreR();
	int getScoreL();
	void resetScore();
};
