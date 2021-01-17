#pragma once

#include "ball.h"
#include "paddle.h"


class Game 
{
	enum class GameStatus {Menu, Playing, EndGame} ;
	Ball* ball = nullptr;
	Paddle* leftpaddle = nullptr;
	Paddle* rightpaddle = nullptr;
	bool leftpaddle_init = false;
	bool rightpaddle_init = false;
	void checkBall();
	void prodBall();
	void gameLogic();
	void drawMenu();
	void drawEndOfGame();
	void drawGame();
	void updateMenu();
	void updateEndOfGame();
	void updateGame();
	GameStatus _gamestatus = GameStatus::Menu;
public:
	void update();
	void draw();
	void drawScore(); 
	void init();
	Game();
	~Game();
};