#include "WallA.h"
using namespace std;
WallA::WallA()
{
    wx=0;
    wy=0;

}
WallA::WallA(SDL_Renderer* renderer, int x,int y)
{
    wx=x;
    wy=y;
    gWallATexture.renderer=renderer;
    gWallATexture.loadFromFile("Resources/wall.png");
}

void WallA::setrenderer(SDL_Renderer* renderer)
{
    gWallATexture.renderer=renderer;
    gWallATexture.loadFromFile("Resources/wall.png");
}
void WallA::setposition(int x,int y)
{
    wx=x;
    wy=y;
}


void WallA::render()
{
    gWallATexture.render( wx, wy );
    //cout<<"renderwall"<<mPosX<<"  "<<mPosY<<endl;
}


WallB::WallB()
{
    wx=0;
    wy=0;

}
WallB::WallB(SDL_Renderer* renderer, int x,int y)
{
    wx=x;
    wy=y;
    gWallBTexture.renderer=renderer;
    gWallBTexture.loadFromFile("Resources/fast_wall.png");
}

void WallB::setrenderer(SDL_Renderer* renderer)
{
    gWallBTexture.renderer=renderer;
    gWallBTexture.loadFromFile("Resources/fast_wall.png");
}
void WallB::setposition(int x,int y)
{
    wx=x;
    wy=y;
}


void WallB::render()
{
    gWallBTexture.render( wx, wy );
    //cout<<"renderwall"<<mPosX<<"  "<<mPosY<<endl;
}

