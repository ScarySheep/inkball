#ifndef SPLASHSCREEN_H_INCLUDED
#define SPLASHSCREEN_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Animation.h"

class SplashScreen
{
public:
    SplashScreen(SDL_Renderer*);
    ~SplashScreen();
    bool Show();
    void loadMedia();
    void free();

private:
    SDL_Renderer* renderer;
    LTexture image;
    Animation start;
};


#endif // SPLASHSCREEN_H_INCLUDED
