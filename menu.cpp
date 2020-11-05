#include "menu.h"

Menu::Menu(SDL_Renderer* r)
{
    renderer = r;
    stage = 1;

    stageInfo.resize(10);
    stageInfo[0].unlocked = true;
    for(int i=1; i<10; i++)
    {
        stageInfo[i].unlocked = false;
    }

    for(int i=0; i<10; i++)
    {
        stageInfo[i].stars = 0;
    }

}

Menu::~Menu()
{
    free();
}

bool Menu::Show()
{
    bool quit = false;
    bool showLock = false;
    SDL_Event e;
    while(!quit)
    {

        while( SDL_PollEvent( &e ) != 0 )
        {
            if(showLock)
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    showLock = false;
                }
            }
            else
            {
                for(int i=0; i<10; i++)
                {
                    if(stageInfo[i].stars>0)
                    {
                        if(i!=10){
                            stageInfo[i+1].unlocked = true;
                        }
                    }
                    if(ok_button[i].handleEvent(&e))
                    {
                        if(!stageInfo[i].unlocked)
                        {
                            showLock = true;
                        }
                        else if(stageInfo[i].unlocked)
                        {
                            setStage(i+1);
                            quit = true;
                            return false;
                        }

                    }
                }
            }

            if(e.type == SDL_QUIT)
            {
                quit = true;
                return true;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );


        background.render(0,0);
        for(int i=0; i<10; i++)
        {
            ok_button[i].render();
        }

        for(int i=0; i<10; i++)
        {
            switch(stageInfo[i].stars)
            {
            case 0:
                zero_star.render(87+(i%5)*246,172+(i/5)*333);
                break;

            case 1:
                one_star.render(87+(i%5)*246,172+(i/5)*333);
                break;
            case 2:
                two_star.render(87+(i%5)*246,172+(i/5)*333);
                break;
            case 3:
                three_star.render(87+(i%5)*246,172+(i/5)*333);
                break;
            }
        }

        if(showLock)
        {
            unlock.render(345,250);
        }
        //Update screen
        SDL_RenderPresent( renderer );

    }
    return false;
}

void Menu::loadMedia()
{
    background.renderer=renderer;
    //Load media
    if( !background.loadFromFile("Resources/menu.png") )
    {
        printf( "Failed to load menu!\n" );
    }

    unlock.renderer = renderer;
    if( !unlock.loadFromFile("Resources/unlock.png") )
    {
        printf( "Failed to load unlock!\n" );
    }

    zero_star.renderer = renderer;
    if( !zero_star.loadFromFile("Resources/zero_star.png") )
    {
        printf( "Failed to load unlock!\n" );
    }

    one_star.renderer = renderer;
    if( !one_star.loadFromFile("Resources/one_star.png") )
    {
        printf( "Failed to load unlock!\n" );
    }

    two_star.renderer = renderer;
    if( !two_star.loadFromFile("Resources/two_star.png") )
    {
        printf( "Failed to load unlock!\n" );
    }

    three_star.renderer = renderer;
    if( !three_star.loadFromFile("Resources/three_star.png") )
    {
        printf( "Failed to load unlock!\n" );
    }

    for(int i=0; i<10; i++ )
    {
        ok_button[i].loadMedia("Resources/button/button_ok.png", renderer);
        ok_button[i].setPosition(110+(i%5)*246,227+(i/5)*330);
    }
}

void Menu::free()
{
    background.free();
    unlock.free();
    for(int i=0; i<10; i++)
    {
        ok_button[i].free();
    }
}

void Menu::setStage(int i)
{
    stage = i;
}

int Menu::getStage()
{
    return stage;
}

void Menu::setStars(int i)
{
    stageInfo[stage-1].stars = i;
}

int Menu::getStars()
{
    return stageInfo[stage-1].stars;
}
