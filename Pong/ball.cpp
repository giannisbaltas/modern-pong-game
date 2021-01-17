#include "ball.h"
#include "graphics.h"
#include "config.h"
#include <random>

void Ball::update()
{
	//Movement of the ball
	posx += speedx * graphics::getDeltaTime();
	posy += speedy * graphics::getDeltaTime();

	//If the ball go outside from the sides isn't active anymore
	if (posx < 0 || posx > CANVAS_WIDTH)
	{
		active = false;
	}
	//If the ball hits the upper or lower wall it bounces back
	if (posy > CANVAS_HEIGHT - 5)
		speedy = -abs(speedy);
	if (posy < 5)
		speedy = abs(speedy);
}

void Ball::draw()
{
	//Draw the ball
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "fball.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(posx, posy,25, 25, br);
	graphics::resetPose();
}


void Ball::init()
{
	speedx = 0.8f;
	speedy = 0.5f;
}

void Ball::checkHitLeftPaddle(float paddlex, float paddley)
{
	if (posx < 20 && speedx < 0)
	{
		if (posy > paddley - 100 / 2 && posy < paddley + 100 / 2)
		{
			//The ball's speedx and speedy will be changed according to the point that will be bounced on the paddle
			float posHitPaddle = (posy - paddley) / (paddleWidth / 2);
			speedx = abs(speedx + speedx * (1 - abs(posHitPaddle)) * 0.1 - abs(speedx * posHitPaddle * (-0.2)));
			speedy = speedy + abs(speedy) * posHitPaddle * 0.5;
		}
	}
}

void Ball::checkHitRightPaddle(float paddlex, float paddley)
{
	if (posx > CANVAS_WIDTH - 20 && speedx > 0)
	{
		if (posy > paddley - paddleWidth / 2 && posy < paddley + paddleWidth / 2)
		{
			//The ball's speedx and speedy will be changed according to the point that will be bounced on the paddle
			float posHitPaddle = (posy - paddley) / (paddleWidth / 2); 
			speedx = -abs(speedx + speedx * (1 - abs(posHitPaddle)) * 0.1 - abs(speedx * posHitPaddle * (-0.2)));
			speedy = speedy + abs(speedy) * posHitPaddle * 0.5;
		}
	}
}

bool Ball::isOutsideLeft()
{
	// returns true if the ball is outside of the left side
	return (posx < 0);
}

bool Ball::isOutsideRight()
{
	// returns true if the ball is outside of the right side
	return (posx > CANVAS_WIDTH );
}

Ball::Ball()
{
	init();
}

Ball::~Ball()
{

}


