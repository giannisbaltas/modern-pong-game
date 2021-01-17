#include "graphics.h"
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "config.h"

void Game::prodBall() 
{
	if (!ball)
		ball = new Ball();
}

void Game::checkBall()
{
	if (ball && !ball->isActive())
	{
		delete ball;
		ball = nullptr;
	}
}

void Game::gameLogic()
{
	//Check if the ball hits the left or the right paddle and apply the bounce
	if (ball && leftpaddle && rightpaddle)
	{
		ball->checkHitLeftPaddle(leftpaddle->getPosXLeftPaddle(), leftpaddle->getPosYLeftPaddle());
		ball->checkHitRightPaddle(rightpaddle->getPosXRightPaddle(), rightpaddle->getPosYRightPaddle());

		if (leftpaddle->getScoreL() == 15 || rightpaddle->getScoreR() == 15)
		{
			_gamestatus = GameStatus::EndGame;
		}
	}
}

void Game::update()
{
	if (_gamestatus == GameStatus::Menu)
	{
		updateMenu();
	}
	else if (_gamestatus == GameStatus::Playing)
	{
		updateGame();
	}
	else
	{
		updateEndOfGame();
	}
	
}

void Game::updateMenu()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		_gamestatus = GameStatus::Playing;
	}
}

void Game::updateEndOfGame()
{
	graphics::stopMusic(3000);
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		if (leftpaddle && rightpaddle)
		{
			leftpaddle->resetScore();
			rightpaddle->resetScore();
		}
		_gamestatus = GameStatus::Playing;
	}
}

void Game::updateGame()
{
	if (!leftpaddle_init)
	{
		leftpaddle = new Paddle;
		leftpaddle_init = true;
	}
	if (!rightpaddle_init)
	{
		rightpaddle = new Paddle;
		rightpaddle_init = true;
	}

	if (leftpaddle && rightpaddle)
	{
		leftpaddle->update();
		rightpaddle->update();
	}

	checkBall();
	prodBall();
	gameLogic();

	if (ball)
		ball->update();
}

void Game::draw()
{
	if (_gamestatus == GameStatus::Menu)
	{
		drawMenu();
	}
	else if (_gamestatus == GameStatus::Playing)
	{
		drawGame();
	}
	else
	{
		drawEndOfGame();
	}	
}

void Game::drawMenu()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "level2.png";
	br.outline_opacity = 0.f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.1f;
	graphics::drawText(365, CANVAS_HEIGHT / 2, 90, "PONG", br);
	graphics::drawText(330, CANVAS_HEIGHT - 30 , 30, "Press SPACE to play", br);
	graphics::drawText(35, CANVAS_HEIGHT - 30 , 15, "Player 1-> ", br);
	graphics::drawText(150, CANVAS_HEIGHT - 40 ,15, "W: UP", br);
	graphics::drawText(150, CANVAS_HEIGHT - 20, 15, "S: DOWN", br);
	graphics::drawText(CANVAS_WIDTH - 130, CANVAS_HEIGHT - 30 , 15, " <-Player 2", br);
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 40 , 15, "O: UP", br);
	graphics::drawText(CANVAS_WIDTH - 220, CANVAS_HEIGHT - 20 , 15, "L: DOWN", br);
	br.texture = "";
	graphics::resetPose();
}

void Game::drawGame()
{
	//Draw the background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "level4.png";
	br.outline_opacity = 0.f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::resetPose();

	//Draw the ball and the paddles
	if (ball)
	{
		ball->draw();
	}

	if (leftpaddle && rightpaddle)
	{
		leftpaddle->draw();
		rightpaddle->draw();
	}
	
	//Draw the score
	drawScore();
	if (ball)
	{
		if (ball->isOutsideLeft())
		{
			rightpaddle->increaseScoreR();
		}
		if (ball->isOutsideRight())
		{
			leftpaddle->increaseScoreL();
		}
	}
}

void Game::drawScore()
{
	if (leftpaddle && rightpaddle)
	{
		graphics::Brush br;
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.1f;
		char scoreStr[4];
		sprintf_s(scoreStr, "%d", rightpaddle->getScoreR());
		graphics::drawText(CANVAS_WIDTH - 90, CANVAS_HEIGHT - 450, 40, scoreStr, br);
		sprintf_s(scoreStr, "%d", leftpaddle->getScoreL());
		graphics::drawText(60, 50, 40, scoreStr, br);
	}
}


void Game::drawEndOfGame()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "level2.png";
	br.outline_opacity = 0.f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.1f;
	if (leftpaddle && rightpaddle)
	{
		if (leftpaddle->getScoreL() > rightpaddle->getScoreR())
			graphics::drawText(300, CANVAS_HEIGHT / 2, 50, "WINNER Player1", br);
		else 
			graphics::drawText(300, CANVAS_HEIGHT / 2, 50, "WINNER Player2", br);
	}
	graphics::drawText(300, CANVAS_HEIGHT - 30, 30, "Press SPACE to play again", br);
	br.texture = "";
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "cempaka1.otf");
	graphics::playMusic(std::string(ASSET_PATH) + "house.mp3", 0.4, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
	if (leftpaddle && rightpaddle)
	{
		delete leftpaddle;
		delete rightpaddle;
	}
	if (ball)
		delete ball;
}
