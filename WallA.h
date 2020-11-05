#ifndef WALLA_H_INCLUDED
#define WALLA_H_INCLUDED

#include <iostream>
#include "LTexture.h"


class WallA
{
public:
    WallA();
    WallA(SDL_Renderer*,int ,int);
    void setposition (int,int);
    //void DrawWallA();
    void render();
    void setrenderer(SDL_Renderer*);
    float wx,wy;
private:
    LTexture gWallATexture;
};

class WallB
{
public:
    WallB();
    WallB(SDL_Renderer*,int ,int);
    void setposition (int,int);
    //void DrawWallA();
    void render();
    void setrenderer(SDL_Renderer*);
    float wx,wy;
private:
    LTexture gWallATexture;
    LTexture gWallBTexture;
};



#endif // WALLA_H_INCLUDED
