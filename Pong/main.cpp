#include "graphics.h"
#include "game.h"
#include "config.h"

void update(float ms)
{
	Game* game = reinterpret_cast<Game*>(graphics::getUserData());
	game->update();
}


void draw()
{
	Game* game = reinterpret_cast<Game*>(graphics::getUserData());
	game->draw();
}


void init()
{

}


int main()
{

	Game game;

	//create window
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Modern Pong");
	//graphics::setFullScreen(true);

	graphics::setUserData(&game);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);

	game.init();
	graphics::startMessageLoop();
	graphics::destroyWindow();




	return 0;
}