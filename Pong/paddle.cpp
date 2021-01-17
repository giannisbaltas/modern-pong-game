#include "paddle.h"
#include "graphics.h"
#include "game.h"

void Paddle::update()
{
	//Fix the movement of paddles

	// W for going up
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos_y_leftpaddle -= speed * graphics::getDeltaTime() / 10.0f;
	}
	// S for going down
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_y_leftpaddle += speed * graphics::getDeltaTime() / 10.0f;
		 
	}
	// O for going up
	if (graphics::getKeyState(graphics::SCANCODE_O))
	{
		pos_y_rightpaddle -= speed * graphics::getDeltaTime() / 10.0f;
	}
	// L for going down
	if (graphics::getKeyState(graphics::SCANCODE_L))
	{
		pos_y_rightpaddle += speed * graphics::getDeltaTime() / 10.0f;

	}

	//fix the borders for both paddles
	if (pos_y_leftpaddle < 40 ) pos_y_leftpaddle = 40;
	if (pos_y_leftpaddle > CANVAS_HEIGHT-5) pos_y_leftpaddle = CANVAS_HEIGHT-5;
	
	if (pos_y_rightpaddle < 40) pos_y_rightpaddle = 40;
	if (pos_y_rightpaddle > CANVAS_HEIGHT-5) pos_y_rightpaddle = CANVAS_HEIGHT-5;


}

void Paddle::draw()
{ 
	//Draw the puddles
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "frpaddle.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x_rightpaddle, pos_y_rightpaddle , paddleWidth, paddleHeight, br);

	br.texture = std::string(ASSET_PATH) + "flpaddle.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x_leftpaddle, pos_y_leftpaddle, paddleWidth, paddleHeight, br);
	
	graphics::resetPose();
	br.texture = "";
}

void Paddle::init()
{
}

void Paddle::increaseScoreR()
{
	++scoreR;
}

void Paddle::increaseScoreL()
{
	++scoreL;
}

int Paddle::getScoreR()
{
	return scoreR;
}

int Paddle::getScoreL()
{
	return scoreL;
}

void Paddle::resetScore()
{
	scoreR = 0;
	scoreL = 0;
}
