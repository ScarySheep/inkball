#include "SplashScreen.h"

SplashScreen::SplashScreen(SDL_Renderer* r)
{
    renderer = r;
}

SplashScreen::~SplashScreen()
{

}

bool SplashScreen::Show()
{
    bool quit = false;
    while(!quit){
    //Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
    image.render(0,0);
    start.animate();
    start.render(550,500,0,NULL,SDL_FLIP_NONE);
    //Update screen
    SDL_RenderPresent( renderer );
    //Event handler
    SDL_Event e;
    //Handle events on queue

        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN )
            {
                quit = true;
                return false;
            }
            else if(e.type == SDL_QUIT)
            {
                quit = true;
                return true;
            }

        }
    }
    return false;
}

void SplashScreen::loadMedia()
{
    image.renderer=renderer;
    //Load media
    if( !image.loadFromFile("Resources/startscreen3.png") )
    {
        printf( "Failed to load startscreen!\n" );
    }

    start.setFramerate(80);
    start.setMaxFrame(8);
    start.loadTexture("Resources/animation/start_ani.png",renderer);
}

void SplashScreen::free()
{
    image.free();
    start.free();
}

