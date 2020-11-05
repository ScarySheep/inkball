#include "Ball.h"
const int SCREEN_HEIGHT=680;
const int SCREEN_WIDTH=840;
const int DOT_WIDTH=20;
const int DOT_HEIGHT=20;
#define PI 3.14159265


using namespace std;
Ball::Ball(SDL_Renderer* r)
{
	state = 0;
	playstate=0;
	bump=0;
	enter=0;
	setup=0;
	//ball position
	mPosX=0;
	mPosY=0;
	ballcenterx=mPosX+48;
	ballcentery=mPosY+48;
	//ball velocity
	mVelX = 0;
    mVelY = 0;
    oldcenterx=mPosX+48;
    oldcentery=mPosX+48;
    rv=10;
    velocity=10;
    decreaserate=0.1;
    edgedecrease=0.15;
    increaserate=0.07;

    mCollider.r = 10;
    lastTime=0;
    renderer=r;
    Apx=ballcenterx-50;
    Apy=ballcentery-200;


    arrowcenter.x=50;
    arrowcenter.y=200;


    aniballstop.setFramerate(100);
    aniballmove.setFramerate(100);
    aniballbump.setFramerate(50);
    aniarrow.setFramerate(100);

    aniballstop.setMaxFrame(4);
    aniballmove.setMaxFrame(2);
    aniballbump.setMaxFrame(4);
    aniarrow.setMaxFrame(3);

    aniballstop.loadTexture("Resources/animation/ball/normal_ani.png",renderer);
    aniballmove.loadTexture("Resources/animation/ball/move_ani.png",renderer);
    aniballbump.loadTexture("Resources/animation/ball/hitting_wall_ani.png",renderer);
    aniarrow.loadTexture("Resources/animation/array/array_ani.png",renderer);
    //gBallTexture.renderer=renderer;
    //gBallTexture.loadFromFile("Resource/1.png");
}

void Ball::move( int n1,vector<WallA>& square,int n2,vector<WallB>& square2 )
{
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1)
    {
        mPosX += mVelX;
        mCollider.x=mPosX;
        if ( mPosX+4 < 0 )
        {
            //Move back
            oldcenterx=mPosX+48;
            oldcentery=mPosY+48;
            mPosX -= mVelX;
            mCollider.x = mPosX;
            directionx=-directionx;
            bump=1;
            velocity=velocity-edgedecrease*rv;
            //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
            //cout<<atan2(directiony,directionx)*180/PI<<endl;

        }
        else if( mPosX +52 > SCREEN_WIDTH )
        {
            //Move back
            oldcenterx=mPosX+48;
            oldcentery=mPosY+48;
            mPosX -= mVelX;
            mCollider.x = mPosX;
            directionx=-directionx;
            bump=2;
            velocity=velocity-edgedecrease*rv;
            //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
            //cout<<atan2(directiony,directionx)*180/PI<<endl;

        }
        else
        {
            for(int i=0;i<n1;i++)
            {
                if(checkCollision( mCollider, square[i] )&&((mCollider.x+48)<(square[i].wx+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosX -= mVelX;
                    mCollider.x = mPosX;
                    directionx=-directionx;
                    bump=2;
                    velocity=velocity-decreaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
                else if(checkCollision( mCollider, square[i] )&&((mCollider.x+48)>(square[i].wx+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosX -= mVelX;
                    mCollider.x = mPosX;
                    directionx=-directionx;
                    bump=1;
                    velocity=velocity-decreaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
            }
            for(int i=0;i<n2;i++)
            {

                if(checkCollision( mCollider, square2[i] )&&((mCollider.x+48)<(square2[i].wx+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosX -= mVelX;
                    mCollider.x = mPosX;
                    directionx=-directionx;
                    bump=2;
                    velocity=velocity+increaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
                else if(checkCollision( mCollider, square2[i] )&&((mCollider.x+48)>(square2[i].wx+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosX -= mVelX;
                    mCollider.x = mPosX;
                    directionx=-directionx;
                    bump=1;
                    velocity=velocity+increaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
            }
        }





        mPosY += mVelY;
        mCollider.y=mPosY;
        if( mPosY+4< 0 )
        {
            //Move back
            oldcenterx=mPosX+48;
            oldcentery=mPosY+48;
            mPosY -= mVelY;
            mCollider.y = mPosY;
            directiony=-directiony;
            bump=3;
            velocity=velocity-edgedecrease*rv;
            //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
            //cout<<atan2(directiony,directionx)*180/PI<<endl;
        }
        else if( mPosY + 52 > SCREEN_HEIGHT )
        {
            //Move back
            oldcenterx=mPosX+48;
            oldcentery=mPosY+48;
            mPosY -= mVelY;
            mCollider.y = mPosY;
            directiony=-directiony;
            bump=4;
            velocity=velocity-edgedecrease*rv;
            //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
            //cout<<atan2(directiony,directionx)*180/PI<<endl;

        }
        else
        {
            for(int i=0;i<n1;i++)
            {
                if(checkCollision( mCollider, square[i] )&&((mCollider.y+48)<(square[i].wy+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosY -= mVelY;
                    mCollider.y = mPosY;
                    directiony=-directiony;
                    bump=4;
                    velocity=velocity-decreaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
                else if(checkCollision( mCollider, square[i] )&&((mCollider.y+48)>(square[i].wy+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosY -= mVelY;
                    mCollider.y = mPosY;
                    directiony=-directiony;
                    bump=3;
                    velocity=velocity-decreaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
            }
            for(int i=0;i<n2;i++)
            {
                if(checkCollision( mCollider, square2[i] )&&((mCollider.y+48)<(square2[i].wy+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosY -= mVelY;
                    mCollider.y = mPosY;
                    directiony=-directiony;
                    bump=4;
                    velocity=velocity+increaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
                    //cout<<"error"<<endl;
                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
                else if(checkCollision( mCollider, square2[i] )&&((mCollider.y+48)>(square2[i].wy+24)))
                {
                    //Move back
                    oldcenterx=mPosX+48;
                    oldcentery=mPosY+48;
                    mPosY -= mVelY;
                    mCollider.y = mPosY;
                    directiony=-directiony;
                    bump=3;
                    velocity=velocity+increaserate*rv;
                    //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;

                    //cout<<atan2(directiony,directionx)*180/PI<<endl;
                }
            }
        }


        if(velocity<1) velocity=0;
        mVelX=velocity*directionx;
        mVelY=velocity*directiony;
        ballcenterx=mPosX+48;
        ballcentery=mPosY+48;

        //cout<<"velocity="<<velocity<<"VX="<<mVelX<<" VY="<<mVelY<<endl;
        lastTime = currentTime;
    }
}

int Ball::startvelocity( SDL_Event* e )
{
    int finalpointx,finalpointy;


        //if(e->type == SDLK_s)   return false;

        if(e->type == SDL_MOUSEBUTTONDOWN) state=5;
        if(e->type == SDL_MOUSEBUTTONUP&&state==5)
        {
            SDL_GetMouseState( &finalpointx, &finalpointy );
            //cout<<"finalpointx "<<finalpointx<<" finalpointx "<<finalpointy<<endl;
            directionx =((finalpointx-ballcenterx)/sqrt((finalpointx-ballcenterx)*(finalpointx-ballcenterx)+(finalpointy-ballcentery)*(finalpointy-ballcentery)));
            directiony =((finalpointy-ballcentery)/sqrt((finalpointx-ballcenterx)*(finalpointx-ballcenterx)+(finalpointy-ballcentery)*(finalpointy-ballcentery)));
            //cout<<sqrt(finalpointx*finalpointx+finalpointy*finalpointy)<<endl;
            //cout<<"directionx "<<directionx<<" directiony "<<directionx<<endl;
            mVelX=velocity*directionx;
            mVelY=velocity*directiony;
            //cout<<"mVelX= "<<mVelX<<" mVelY= "<<mVelY<<endl;
            setup=1;state=1;playstate=1;
            arrowangle=atan2(directiony,directionx)*180/PI;
            angle=atan2(directiony,directionx)*180/PI;
            if(angle>360) angle=angle-360;
            else if(angle<0) angle=angle+360;
            //cout<<"a="<<angle<<endl;
        }
        else
        {
            SDL_GetMouseState( &finalpointx, &finalpointy );
            directionx =((finalpointx-ballcenterx)/sqrt((finalpointx-ballcenterx)*(finalpointx-ballcenterx)+(finalpointy-ballcentery)*(finalpointy-ballcentery)));
            directiony =((finalpointy-ballcentery)/sqrt((finalpointx-ballcenterx)*(finalpointx-ballcenterx)+(finalpointy-ballcentery)*(finalpointy-ballcentery)));
            angle=atan2(directiony,directionx)*180/PI;
            arrowangle=atan2(directiony,directionx)*180/PI;
            if(angle>360) angle=angle-360;
            else if(angle<0) angle=angle+360;
            setup=0;
        }
        return setup;
}

void Ball::arrowrender()
{

    /*if(state==0)
    {
        aniarrow.animate();
        aniarrow.render(ballcenterx-50,ballcentery-200,135,&arrowcenter,SDL_FLIP_NONE);
    }
    if(state==4)
    {
        aniarrow.animate();
        aniarrow.render(ballcenterx-50,ballcentery-200,0,&arrowcenter,SDL_FLIP_NONE);
    }*/
    if(state==5)
    {
        aniarrow.animate();
        aniarrow.render(ballcenterx-50,ballcentery-200,90+arrowangle,&arrowcenter,SDL_FLIP_NONE);
    }

}

void Ball::ballrender()
{
    if(bump==0)
   {
      if (state==0||state==5||state==4)
        {
        aniballstop.animate();
        aniballstop.render(mPosX,mPosY,0,NULL,SDL_FLIP_NONE);

        }
        else if (state==1)
        {
        //double angle=atan2(directiony,directionx)*180/PI;
        aniballmove.animate();
        aniballmove.render(mPosX,mPosY, angle,NULL,SDL_FLIP_NONE);
        }
   }
   else if(bump!=0||state==2)
   {
        if(bump==1)
        {
            if(enter==0) {stopTime=SDL_GetTicks();enter=1;v=velocity;aniballbump.start=true;}
            if(aniballbump.getCurrentFrame()!= 0||stopTime+100>SDL_GetTicks())
            {
                aniballbump.animate();
                if(angle>360) angle=angle-360;
                else if(angle<0) angle=angle+360;

                if((angle<90&&angle>0)||(angle>270)||(angle<0))
                aniballbump.render(mPosX,mPosY,0,NULL,SDL_FLIP_HORIZONTAL);
                else
                aniballbump.render(mPosX,mPosY,180,NULL,SDL_FLIP_NONE);
                //cout<<"in";
                velocity=0;
            }
           else
            {
                bump=0;
                state=1;
                enter=0;
                velocity=v;
                angle=-angle;
                while(angle>360) angle=angle-360;
                while(angle<0) angle=angle+360;
                //cout<<angle<<endl;
            }
        }

        else if(bump==2)
        {
            if(enter==0) {stopTime=SDL_GetTicks();enter=1;v=velocity;aniballbump.start=true;}
            if(aniballbump.getCurrentFrame()!= 0||stopTime+100>SDL_GetTicks())
            {
                aniballbump.animate();
                if(angle>360) angle=angle-360;
                else if(angle<0) angle=angle+360;

                if((angle<90&&angle>0)||(angle>270)||(angle<0))
                aniballbump.render(mPosX,mPosY,0,NULL,SDL_FLIP_NONE);
                else
                aniballbump.render(mPosX,mPosY,180,NULL,SDL_FLIP_HORIZONTAL);
                //cout<<"in";
                velocity=0;
            }
            else
            {
                bump=0;
                state=1;
                enter=0;
                velocity=v;
                angle=-angle;
                while(angle>360) angle=angle-360;
                while(angle<0) angle=angle+360;
                //cout<<angle<<endl;
            }

        }

        else if(bump==3)
        {
            if(enter==0) {stopTime=SDL_GetTicks();enter=1;v=velocity;aniballbump.start=true;}
            if(aniballbump.getCurrentFrame()!= 0||stopTime+100>SDL_GetTicks())
            {
                aniballbump.animate();
                if(angle>360) angle=angle-360;
                else if(angle<0) angle=angle+360;

                if(angle>180||angle<0)
                aniballbump.render(mPosX,mPosY,270,NULL,SDL_FLIP_NONE);
                else
                aniballbump.render(mPosX,mPosY,90,NULL,SDL_FLIP_HORIZONTAL);

                //cout<<"in";
                velocity=0;
            }
            else
            {
                bump=0;
                state=1;
                enter=0;
                velocity=v;
                angle=180-angle;
                while(angle>360) angle=angle-360;
                while(angle<0) angle=angle+360;
                //cout<<angle<<endl;
            }
        }
        else if(bump==4)
        {
            if(enter==0) {stopTime=SDL_GetTicks();enter=1;v=velocity;aniballbump.start=true;}
            if(aniballbump.getCurrentFrame()!= 0||stopTime+100>SDL_GetTicks())
            {
                aniballbump.animate();
                if(angle>360) angle=angle-360;
                else if(angle<0) angle=angle+360;

                if(angle>180||angle<0)
                aniballbump.render(mPosX,mPosY,270,NULL,SDL_FLIP_HORIZONTAL);
                else
                aniballbump.render(mPosX,mPosY,90,NULL,SDL_FLIP_NONE);
                //cout<<"in";
                velocity=0;

            }
            else
            {
                bump=0;
                state=1;
                enter=0;
                velocity=v;
                angle=180-angle;
                while(angle>360) angle=angle-360;
                while(angle<0) angle=angle+360;
                //cout<<angle<<endl;
            }
        }
        if(v==0) {playstate=0;state=4;setup=0;velocity=rv;}
   }


   else cout<<"error";
}
bool checkCollision( Circle& a, WallA& b )
{//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x+24;
    rightA = a.x+72;
    topA = a.y+24;
    bottomA = a.y+72;

    //Calculate the sides of rect B
    leftB = b.wx;
    rightB = b.wx+48;
    topB = b.wy;
    bottomB = b.wy+48;

    //If any of the sides from A are outside of B
    if( bottomA < topB || topA > bottomB||rightA < leftB||leftA > rightB)
    {
        return false;
    }
    else
    {
        return true;
        cout<<"collision";
    }
    //If none of the sides from A are outside B

}

bool checkCollision( Circle& a, WallB& b )
{//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x+24;
    rightA = a.x+72;
    topA = a.y+24;
    bottomA = a.y+72;

    //Calculate the sides of rect B
    leftB = b.wx;
    rightB = b.wx+48;
    topB = b.wy;
    bottomB = b.wy+48;

    //If any of the sides from A are outside of B
    if( bottomA < topB || topA > bottomB||rightA < leftB||leftA > rightB)
    {
        return false;
    }
    else
    {
        return true;
        cout<<"collision";
    }
    //If none of the sides from A are outside B

}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

float Ball::getcenterx()
{
    float x;
    x=ballcenterx;
    return x;
}

float Ball::getcentery()
{
    float y;
    y=ballcentery;
    return y;
}

float Ball::getoldcenterx()
{
    float x;
    x=oldcenterx;
    return x;
}

float Ball::getoldcentery()
{
    float y;
    y=oldcentery;
    return y;
}

int Ball::getplaystate()
{
    int x;
    x=playstate;
    return x;
}
/*bool checkCollision( Circle& a, SDL_Rect& b )
{
    //Closest point on collision box
    int cX, cY;
    a.x+=a.r;
    a.y+=a.r;
    //Find closest x offset
    if( a.x< b.x )
    {
        cX = b.x;
    }
    else if( a.x > b.x + b.w )
    {
        cX = b.x + b.w;
    }
    else
    {
        cX = a.x;
    }
    //Find closest y offset
    if( a.y < b.y )
    {
        cY = b.y;
    }
    else if( a.y > b.y + b.h )
    {
        cY = b.y + b.h;
    }
    else
    {
        cY = a.y;
    }

    //If the closest point is inside the circle
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
    {
        //This box and the circle have collided
        return true;
    }
    else return false;
    //If the shapes have not collided

}*/
