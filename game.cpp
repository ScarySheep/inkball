#include "game.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "GamePlay.h"
#include <SDL_ttf.h>



Game::Game(){
    gamestate=Game::Uninitialized;

    gWindow = NULL;

    gRenderer = NULL;

    Start();
}

Game::~Game(){
    close();
}

bool Game::init()
{
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		if(!SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1"))
        {
            printf( "Warning:Highdpi can't be disabled" );
        }


		//Create window
		gWindow = SDL_CreateWindow( "Inkball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::close()
{
    //free menu texture


    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::Start()
{
    if(gamestate != Uninitialized)
        return;

    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        gamestate=Game::ShowingSplashScreen;
    }
    while(!IsExiting())
    {
        Gameloop();
    }

    close();
}

bool Game::IsExiting()
{
    if(gamestate == Game::Exiting)
        return true;
    else
        return false;
}

void Game::Gameloop()
{
    printf("SplashScreen\n");
    SplashScreen splashScreen(gRenderer);
    splashScreen.loadMedia();

    Menu menu(gRenderer);
    menu.loadMedia();

    GamePlay gameplay(gRenderer);

    //Main loop flag
    bool quit = false;

    //While application is running
    while( !quit )
    {
        switch(gamestate)
        {
        case Game::ShowingSplashScreen:
        {

            quit = splashScreen.Show();

            if(quit)
            {
                splashScreen.free();
                gamestate = Game::Exiting;
            }
            else
            {
                splashScreen.free();
                gamestate = Game::ShowingMenu;
            }
            break;
        }

        case Game::ShowingMenu:
        {
            printf("Menu\n");

            for(int i=0; i<10;i++){
                menu.setStage(i+1);
                if(gameplay.getStar(i)>menu.getStars()){
                    menu.setStars(gameplay.getStar(i));
                }
            }
            quit = menu.Show();

            if(quit)
            {
                gamestate = Game::Exiting;
            }
            else
            {
                gamestate = Game::Playing;
            }
            break;
        }
        case Game::Playing:
        {

            gameplay.init(menu.getStage());
            gameplay.loadMedia();
            gameplay.show();
            switch(gameplay.getState()){
            //nextstage
            case 1:
                break;
            //menu
            case 2:
                gamestate = Game::ShowingMenu;
                break;
            //exit
            case 3:
                printf("quit");
                gamestate = Exiting;
                quit = true;
                break;
            }

            break;
        }

        case Game::Paused:
        {
                break;
        }

        case Game::Exiting:
        {
            menu.free();
            close();
            break;
        }
        }
    }
}

