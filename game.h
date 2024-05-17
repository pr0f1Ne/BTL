#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<SDL.h>
#include "bang.h"

class Game{
    private:
        bool running = false;
        bool createBG = false;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Event event;
        Bang *board = nullptr;
    public:
        Game(const char *title, int w, int h, bool fullscreen);
        ~Game();
        // check game loop
        bool isRunning() {return running;}
        void handleEvents();
        void update();
        void render();
};

#endif // GAME_H
