#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>


class Game
{

public:
    Game();
    ~Game();
    void Start();
    void close();

private:
    //Screen dimension constants
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 720;

    //The window we'll be rendering to
    SDL_Window* gWindow;

    //renderer
    SDL_Renderer* gRenderer;

    enum Gamestate { Uninitialized, Paused, ShowingSplashScreen, ShowingMenu,
                     Playing, Exiting
                   };
    Gamestate gamestate;

    bool init();
    bool IsExiting();
    void Gameloop();


};

#endif // GAME_H_INCLUDED
