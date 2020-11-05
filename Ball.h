#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <iostream>
#include <cmath>
#include "LTexture.h"
#include "WallA.h"
#include "Animation.h"
#include <SDL.h>
#include "trail.h"
//#include "GameObject.h"
extern SDL_Renderer* gRenderer;
struct Circle
{
	float x, y;
	float r;
};
class Ball //: public GameObject
{
public:
    Ball(SDL_Renderer*);
    void move(int,vector<WallA>&,int,vector<WallB>&);
    //void move( int  ,SDL_Rect& ,SDL_Rect&  , SDL_Rect& , SDL_Rect&  , SDL_Rect&  , SDL_Rect&  , SDL_Rect&  , SDL_Rect&  , SDL_Rect&  , SDL_Rect& );
    void ballrender();
    void arrowrender();
    float getcenterx();
    float getcentery();
    float getoldcenterx();
    float getoldcentery();
    int getplaystate();


    Circle mCollider;
    int startvelocity( SDL_Event* e );
private:
    float velocity, v;
    float ballcenterx, ballcentery;
    //LTexture gBallTexture;
    float mPosX, mPosY,Apx,Apy;
    //The velocity of the dot
    float mVelX, mVelY;
    //LTexture image;
    std::string filename;
    bool isLoaded;
    float directionx,directiony;
    float oldcenterx,oldcentery;
    int state , bump ,enter,playstate,setup;
    int lastTime, currentTime, stopTime;
    double arrowangle,angle;
    float decreaserate,increaserate,edgedecrease,rv;


    SDL_Renderer* renderer;
    SDL_Point arrowcenter;

    Animation aniballstop;
    Animation aniballmove;
    Animation aniballbump;
    Animation aniarrow;

};
//Circle/Box collision detector

bool checkCollision( Circle& , WallA& );
bool checkCollision( Circle& , WallB& );
double distanceSquared( int x1, int y1, int x2, int y2 );


#endif // BALL_H_INCLUDED
