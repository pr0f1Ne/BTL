#ifndef bang_hpp
#define bang_hpp
#include "Tile.h"
#include "graphics.h"
#include <ctime>
#include <string>
#define FORD(i,a,b) for(int i = a; i >= b; i--)
class Bang
{
private:
    int value[4][4] = {0};
    Tile tiles[4][4] = {Tile()};
    int score = 0;
public:
    Bang()
    {
        generateTile();
        generateTile();
    }
    bool generateTile()
    {
        int unusedTiles = 0;
        FOR(i,0,3)
        FOR(j,0,3)
        {
            if(!value[i][j]) unusedTiles++;
        }
        if(!unusedTiles)
        {
            printf("No more tiles left\n");
            return false;
        }

        srand(time(NULL));
        bool four_spawn = false;
        int x = rand() % 4;
        int y = rand() % 4;
        while(value[x][y])
        {
            four_spawn = true;
            x = rand() % 4;
            y = rand() % 4;
        }
        if(!four_spawn) value[x][y] = 2;
        else value[x][y] = (rand() % 2 + 1) * 2;
        return true;
    }
    void makeCopy(int baseValue[4][4], int NewValue[4][4])
    {
        FOR(i,0,3)
        FOR(j,0,3) NewValue[i][j] = baseValue[i][j];
    }

    bool compareCopy(int oldValue[4][4], int newValue[4][4])
    {
        FOR(i,0,3)
        FOR(j,0,3)
        {
            if(oldValue[i][j] != newValue[i][j]) return false;
        }
        return true;
    }

    bool Up()
    {

        int oldValue[4][4];
        makeCopy(value, oldValue);

        FOR(i,0,3)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FOR(k,i+1,3)
            {
                if(value[k][j])
                {
                    value[i][j] = value[k][j];
                    value[k][j] = 0;
                    break;
                }
            }
        }
        FOR(i,0,2)
        FOR(j,0,3)
        {
            if(value[i][j] && value[i][j] == value[i+1][j])
            {
                value[i][j] *= 2;
                value[i+1][j] = 0;
                score += value[i][j];
            }
        }
        FOR(i,0,3)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FOR(k,i+1,3)
            {
                if(value[k][j])
                {
                    value[i][j] = value[k][j];
                    value[k][j] = 0;
                    break;
                }
            }
        }
        return !compareCopy(oldValue, value);
    }
    bool Down()
    {
        int oldValue[4][4];
        makeCopy(value, oldValue);

        FORD(i,3,0)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FORD(k,i-1,0)
            {
                if(value[k][j])
                {
                    value[i][j] = value[k][j];
                    value[k][j] = 0;
                    break;
                }
            }
        }

        FORD(i,3,0)
        FOR(j,0,3)
        {
            if(value[i][j] && value[i][j] == value[i-1][j])
            {
                value[i][j] *= 2;
                value[i-1][j] = 0;
                score += value[i][j];
            }
        }

        FORD(i,3,0)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FORD(k,i-1,0)
            {
                if(value[k][j])
                {
                    value[i][j] = value[k][j];
                    value[k][j] = 0;
                    break;
                }
            }
        }

        return !compareCopy(oldValue, value);
    }
    bool Left()
    {

        int oldValue[4][4];
        makeCopy(value, oldValue);


        FOR(i,0,3)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FOR(k,j+1,3)
            {
                if(value[i][k])
                {
                    value[i][j] = value[i][k];
                    value[i][k] = 0;
                    break;
                }
            }
        }

        FOR(i,0,3)
        FOR(j,0,2)
        {
            if(value[i][j] && value[i][j] == value[i][j+1])
            {
                value[i][j] *= 2;
                value[i][j+1] = 0;
                score += value[i][j];
            }
        }

        FOR(i,0,3)
        FOR(j,0,3)
        if(!value[i][j])
        {
            FOR(k,j+1,3)
            {
                if(value[i][k])
                {
                    value[i][j] = value[i][k];
                    value[i][k] = 0;
                    break;
                }
            }
        }

        return !compareCopy(oldValue, value);
    }
    bool Right()
    {

        int oldValue[4][4];
        makeCopy(value, oldValue);


        FOR(i,0,3)
        FORD(j,3,0)
        if(!value[i][j])
        {
            FORD(k,j-1,0)
            {
                if(value[i][k])
                {
                    value[i][j] = value[i][k];
                    value[i][k] = 0;
                    break;
                }
            }
        }

        FOR(i,0,3)
        FORD(j,3,1)
        {
            if(value[i][j] && value[i][j] == value[i][j-1])
            {
                value[i][j] *= 2;
                value[i][j-1] = 0;
                score += value[i][j];
            }
        }

        FOR(i,0,3)
        FORD(j,3,0)
        if(!value[i][j])
        {
            FORD(k,j-1,0)
            {
                if(value[i][k])
                {
                    value[i][j] = value[i][k];
                    value[i][k] = 0;
                    break;
                }
            }
        }

        return !compareCopy(oldValue, value);
    }

    bool availableMove()
    {
        int oldValue[4][4];
        makeCopy(value, oldValue);

        bool available = (Up()||Down()||Left()||Right());

        FOR(i,0,3)
        FOR(j,0,3)
        {
            value[i][j] = oldValue[i][j];
        }

        return (available||generateTile());
    }
    bool checkwin()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (value[i][j] == 2048)
                {
                    return true;
                    break;
                }
            }
        }
        return false;
    }
    void handleEvents(SDL_Window *window, SDL_Event event)
    {
        if(event.type == SDL_KEYDOWN)
        {
            if(checkwin())
            {
                std::string title = "You Win! Final score: " + std::to_string(score);
                SDL_SetWindowTitle(window, title.c_str());
            }
            else
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if(Up())
                    {
                        generateTile();
                        if(!availableMove())
                        {
                            std::string title = "Game Over! Final score: " + std::to_string(score);
                            SDL_SetWindowTitle(window, title.c_str());
                        }
                        else
                        {
                            SDL_SetWindowTitle(window, std::to_string(score).c_str());
                        }
                        break;
                    }
                case SDLK_DOWN:
                    if(Down())
                    {
                        generateTile();
                        if(!availableMove())
                        {
                            std::string title = "Game Over! Final score: " + std::to_string(score);
                            SDL_SetWindowTitle(window, title.c_str());
                        }
                        else
                        {
                            SDL_SetWindowTitle(window, std::to_string(score).c_str());
                        }
                        break;
                    }
                case SDLK_LEFT:
                    if(Left())
                    {
                        generateTile();
                        if(!availableMove())
                        {
                            std::string title = "Game Over! Final score: " + std::to_string(score);
                            SDL_SetWindowTitle(window, title.c_str());
                        }
                        else
                        {
                            SDL_SetWindowTitle(window, std::to_string(score).c_str());
                        }
                        break;
                    }
                case SDLK_RIGHT:
                    if(Right())
                    {
                        generateTile();
                        if(!availableMove())
                        {
                            std::string title = "Game Over! Final score: " + std::to_string(score);
                            SDL_SetWindowTitle(window, title.c_str());
                        }
                        else
                        {
                            SDL_SetWindowTitle(window, std::to_string(score).c_str());
                        }
                        break;
                    }
                }

            }
        }
    }

    void update()
    {
        FOR(i,0,3)
        FOR(j,0,3) tiles[i][j] = Tile(132 + (97* j), 198 + (97 * i), 82, value[i][j]);
    }
    void render(SDL_Renderer *renderer)
    {
        FOR(i,0,3)
        FOR(j,0,3) tiles[i][j].render(renderer);
    }

};
#endif // bang_hpp
