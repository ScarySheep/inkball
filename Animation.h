#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <string>
#include "LTexture.h"
#include <vector>

using namespace std;


class Animation{
public:
    Animation();
    void animate();
    void setFramerate(int);
    int getCurrentFrame();
    void setMaxFrame(int);
    bool loadTexture(string, SDL_Renderer*);
    void render(int, int, double, SDL_Point*, SDL_RendererFlip);
    void free();
    bool start;

private:
    int currentFrame;
    int direction;
    long oldTime;
    int framerate;
    int maxFrames;

    vector<SDL_Rect> frames;
    LTexture texture;
};


#endif // ANIMATION_H_INCLUDED
