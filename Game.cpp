#include "game.h"
#include "graphics.h"
#include <SDL_image.h>
Game::Game(const char *title, int w, int h, bool fullscreen)
{
    Graphics graphics;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        printf("SDL init success\n");
    }
    else
    {
        printf("SDL init failed\n");
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, fullscreen ? 1 : 0);
    if(window)
    {
        printf("Window init succes\n");
    }
    else
    {
        printf("Window init failed\n");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer)
    {
        printf("Renderer init success\n");
    }
    else
    {
        printf("Renderer init failed\n");
        return;
    }
    if(TTF_Init() == 0)
    {
        printf("TTF init success\n");
    }
    else
    {
        printf("TTF init failed\n");
        return;
    }
    board = new Bang();
    running = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    // background 2048
    SDL_Texture *background = IMG_LoadTexture(renderer,"assets\\2048.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);
    //load music
    Mix_Music *musicGame = graphics.loadMusic("assets\\music.mp3");
    graphics.play(musicGame);

}
Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void Game::handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }
        board -> handleEvents(window, event);
    }
}



void Game::update()
{
    board -> update();
}
void Game::render()
{
    board -> render(renderer);
    SDL_RenderPresent(renderer);
}
