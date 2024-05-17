#include "game.h"
int main(int argc, char *argv[])
{
    Game *game = new Game("GAME 2048", 640, 640, false);
    while(game->isRunning())
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    delete game;
    return 0;
}
