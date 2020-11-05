#include "GamePlay.h"
#include "Animation.h"
#include <sstream>
#include "Ball.h"
#include "AreaCoverage.h"
#include <iostream>

GamePlay::GamePlay(SDL_Renderer* r)
{
    background.renderer = r;
    scoreTexture.renderer = r;
    stageTextTexture.renderer = r;
    stageBackTextTexture.renderer = r;
    remainTextTexture.renderer = r;
    remainBackTextTexture.renderer = r;
    percentTextTexture.renderer = r;
    percentBackTextTexture.renderer = r;
    scoreStar.renderer = r;
    renderer = r;
    trail.loadMedia(r);
    frame.renderer = r;

    for(int i=0; i<10; i++)
    {
        star[i] = 0;
    }
}

void GamePlay::init(int i)
{


    remainTry = 3;
    areaPercent = 0;

    stageCount = i;

    stringstream ss;
    ss << "Stage " << stageCount;
    stage = ss.str();

    ss.str("");
    ss<< "Remain : "<<remainTry<<" try";
    remain = ss.str();
    ss.str("");
    ss<<"Completed area : "<<areaPercent<<"%";
    percent = ss.str();

    state = GamePlay::Playing;
    finished = false;
    setFinished = true;
    finishedTranslation = false;
    delayed = false;

    oldTime = 0;
    score_x = 100;
    score_y = 720;
    scoreStar_x = 244;
    scoreStar_y = 491;
    star_count=0;

    start=0;
    wall_num1=0;
    wall_num2=0;
    playing_times=3;

    startBounce = true;
    oldcenterX = 45;
    oldcenterY = 45;
}

void GamePlay::loadMedia()
{
    if( !background.loadFromFile("Resources/ingame_bg.png") )
    {
        printf( "Failed to load background!\n" );
    }

    if( !scoreTexture.loadFromFile("Resources/show_score.png") )
    {
        printf( "Failed to load background!\n" );
    }

    if( !scoreStar.loadFromFile("Resources/score_star.png") )
    {
        printf( "Failed to load background!\n" );
    }

    if( !frame.loadFromFile("Resources/bg_frame.png") )
    {
        printf( "Failed to load frame!\n" );
    }

    scoreStarClip.h = scoreStar.getHeight();
    scoreStarClip.w = scoreStar.getWidth();
    scoreStarClip.x = 0;
    scoreStarClip.y = 0;

    //Open the font
    stageFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 64 );
    if( stageFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 0, 0, 0 };
        if( !stageTextTexture.loadFromRenderedText( stage, textColor, stageFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    stageBackFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 64 );
    if( stageBackFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 255, 255, 255 };
        TTF_SetFontOutline(stageBackFont,10);
        if( !stageBackTextTexture.loadFromRenderedText( stage, textColor, stageBackFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    remainFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 48 );
    if( remainFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 0, 0, 0 };
        if( !remainTextTexture.loadFromRenderedText( remain, textColor, remainFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    remainBackFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 48 );
    if( remainBackFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 255, 255, 255 };
        TTF_SetFontOutline(remainBackFont,5);
        if( !remainBackTextTexture.loadFromRenderedText( remain, textColor, remainBackFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    percentFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 36 );
    if( percentFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 0, 0, 0 };
        if( !percentTextTexture.loadFromRenderedText( percent, textColor, percentFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    percentBackFont = TTF_OpenFont( "Resources/BAUHS93.ttf", 36 );
    if( percentBackFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Render text
        textColor = { 255, 255, 255 };
        TTF_SetFontOutline(percentBackFont,3);
        if( !percentBackTextTexture.loadFromRenderedText( percent, textColor, percentBackFont ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    }

    button_menu.loadMedia("Resources/button/button_menu.png", renderer);
    button_menu.setPosition(993,530);

    button_restart.loadMedia("Resources/button/button_restart.png",renderer);
    button_restart.setPosition(980,430);
}

void GamePlay::show()
{
    Ball b(renderer);
    loadWall();
    AREA a;

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        switch(state)
        {
        case GamePlay::Playing:
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    state = GamePlay::Exiting;
                }
                else if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(finishedTranslation)
                    {
                        //printf("return to menu");
                        quit = true;
                        trail.free();
                        state = GamePlay::Menu;
                    }
                }

                if(button_menu.handleEvent(&e))
                {
                    state = GamePlay::Menu;
                }

                if(button_restart.handleEvent(&e))
                {
                    init(stageCount);
                    trail.free();
                    show();
                }
            }

            if (start==0&&playing_times>0)
            {
                //b.startvelocity( &e );
                start=b.startvelocity( &e );
            }
            else if(start==1)
            {
                b.move(wall_num1,wall1,wall_num2,wall2);

                if(b.getplaystate()==0)
                {
                    start=0;
                    playing_times=playing_times-1;
                }
                else start=1;
                //cout<<"in";
            }

            if(playing_times==0)
            {
                if(areaPercent>70)
                {
                    //printf("3 %d\n",areaPercent);
                    star[stageCount-1] = 3;
                }
                else if(areaPercent>60)
                {
                    // printf("2 %d\n",areaPercent);
                    star[stageCount-1] = 2;
                }
                else if(areaPercent>50)
                {
                    //  printf("1 %d\n",areaPercent);
                    star[stageCount-1] = 1;
                }
                else
                {
                    // printf("0 %d\n",areaPercent);
                    star[stageCount-1] = 0;
                }
                finished = true;
            }


            if(startBounce)
            {
                startBounce = false;
            }
            else if(oldcenterX!=b.getoldcenterx()||oldcenterY!=b.getoldcentery())
            {

                trail.finishLine(oldcenterX,oldcenterY,b.getoldcenterx(),b.getoldcentery());
                oldcenterX = b.getoldcenterx();
                oldcenterY = b.getoldcentery();
            }

            trail.activeLine(b.getoldcenterx(),b.getoldcentery(),b.getcenterx(),b.getcentery());


            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
            SDL_RenderClear( renderer );

            setRemainTry();

            if(!finished)
            {
                a.setNewPosition(b.getcenterx(),b.getcentery());
                areaPercent = a.GetArea()*100/(571200-(wall_num1+wall_num2)*48*48);
                setPercent();
            }

            background.render(0,0);

            button_menu.render();
            button_restart.render();

            stageBackTextTexture.render(965,100);
            stageTextTexture.render(975,110);
            remainBackTextTexture.render(917,230);
            remainTextTexture.render(922,235);
            percentBackTextTexture.render(887,340);
            percentTextTexture.render(890,343);

            trail.draw();

            frame.render(0,0);

            for(int i=0; i<wall_num1; i++)
                wall1[i].render();
            for(int i=0; i<wall_num2; i++)
                wall2[i].render();

            if(!finished)
            {
                if (playing_times>0) b.arrowrender();
                b.ballrender();
            }

            playEndAni();

            SDL_RenderPresent( renderer );
            break;

        }
        case GamePlay::NextStage:
        {
            break;
        }

        case GamePlay::Menu:
        {
            quit = true;
            trail.free();
            break;
        }
        case GamePlay::Exiting:
        {
            printf("exit");
            quit = true;
            break;
        }

        }
    }
}

void GamePlay::free()
{
    background.free();
}

int GamePlay::getState()
{
    return state;
}

int GamePlay::getStar(int i)
{
    return star[i];
}

void GamePlay::setRemainTry()
{
    stringstream ss;
    ss<< "Remain : "<<playing_times<<" try";
    remain = ss.str();
    ss.str("");

    textColor = { 255, 255, 255 };
    TTF_SetFontOutline(remainBackFont,5);
    if( !remainBackTextTexture.loadFromRenderedText( remain, textColor, remainBackFont ) )
    {
        printf( "Failed to render text texture!\n" );
    }

    textColor = { 0, 0, 0 };
    if( !remainTextTexture.loadFromRenderedText( remain, textColor, remainFont ) )
    {
        printf( "Failed to render text texture!\n" );
    }


}

void GamePlay::setPercent()
{
    stringstream ss;
    ss<<"Completed area : "<<areaPercent<<"%";
    percent = ss.str();
    ss.str("");

    textColor = { 255, 255, 255 };
    TTF_SetFontOutline(percentBackFont,3);
    if( !percentBackTextTexture.loadFromRenderedText( percent, textColor, percentBackFont ) )
    {
        printf( "Failed to render text texture!\n" );
    }

    textColor = { 0, 0, 0 };
    if( !percentTextTexture.loadFromRenderedText( percent, textColor, percentFont ) )
    {
        printf( "Failed to render text texture!\n" );
    }


}

void GamePlay::playEndAni()
{
    if(finished)
    {
        if(setFinished)
        {
            oldTime = SDL_GetTicks();
            setFinished = false;
        }
        if(score_y>0)
        {
            if(oldTime+60>SDL_GetTicks())
            {
                oldTime = SDL_GetTicks();
                score_y-=3;
            }
        }
        else if(score_y<=0)
        {
            finishedTranslation = true;
        }
        scoreTexture.render(score_x,score_y);

        if(finishedTranslation)
        {
            if(!delayed)
            {
                oldTime = SDL_GetTicks();
                delayed = true;
            }
            if(SDL_GetTicks()>(oldTime+500))
            {
                oldTime = SDL_GetTicks();
                if(star_count<star[stageCount-1])
                    star_count++;
            }
        }
        for(int i=0; i<star_count; i++)
        {
            scoreStar.renderEx(scoreStar_x+i*138,scoreStar_y-i*50,&scoreStarClip,-20,NULL,SDL_FLIP_NONE);
        }


    }

}



void GamePlay::loadWall()
{
    if(stageCount==1)
    {

        wall_num1=4;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(500,500);
        wall1[1].setposition(548,500);
        wall1[2].setposition(500,548);
        wall1[3].setposition(548,548);

        wall_num2=6;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(200,200);
        wall2[1].setposition(248,200);
        wall2[2].setposition(200,248);
        wall2[3].setposition(248,248);
        wall2[4].setposition(296,248);
        wall2[5].setposition(296,200);

    }

    else if(stageCount==2)
    {
        wall_num1=6;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(150,150);
        wall1[1].setposition(150,198);
        wall1[2].setposition(150,246);
        wall1[3].setposition(198,150);
        wall1[4].setposition(198,198);
        wall1[5].setposition(198,246);

        wall_num2=4;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(500,500);
        wall2[1].setposition(548,500);
        wall2[2].setposition(500,548);
        wall2[3].setposition(548,548);


    }

    else if(stageCount==3)
    {
        wall_num1=5;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(200,100);
        wall1[1].setposition(200,148);
        wall1[2].setposition(200,196);
        wall1[3].setposition(200,244);
        wall1[4].setposition(200,292);



        wall_num2=1;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(300,200);


    }


    else if(stageCount==4)
    {
        wall_num1=12;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(200,0);
        wall1[1].setposition(200,48);
        wall1[2].setposition(200,96);
        wall1[3].setposition(200,144);
        wall1[4].setposition(200,192);
        wall1[5].setposition(248,0);
        wall1[6].setposition(248,48);
        wall1[7].setposition(248,96);
        wall1[8].setposition(248,144);
        wall1[9].setposition(248,192);
        wall1[10].setposition(248,192+48);
        wall1[11].setposition(200,192+48);

        wall_num2=6;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(200,288);
        wall2[1].setposition(500,0);
        wall2[2].setposition(248,288);
        wall2[3].setposition(500,48);
        wall2[4].setposition(548,48);
        wall2[5].setposition(548,0);


    }

    else if(stageCount==5)
    {
        wall_num1=3;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(400,400);
        wall1[1].setposition(448,400);
        wall1[2].setposition(496,400);

        wall_num2=3;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(200,200);
        wall2[1].setposition(580,580);
        wall2[2].setposition(580,628);

    }

    else if(stageCount==6)
    {
        wall_num1=10;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(200,496);
        wall1[1].setposition(200,542);
        wall1[2].setposition(200,590);
        wall1[3].setposition(550,680-48);
        wall1[4].setposition(550,680-48*2);
        wall1[5].setposition(550,680-48*3);
        wall1[6].setposition(550,680-48*4);
        wall1[7].setposition(300,0);
        wall1[8].setposition(300,48);
        wall1[9].setposition(300,96);

        wall_num2=1;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(300,540);

    }

    else if(stageCount==7)
    {
        wall_num1=10;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(150,0);
        wall1[1].setposition(150,48);
        wall1[2].setposition(150,144);
        wall1[3].setposition(700,680-96);
        wall1[4].setposition(700,680-144);
        wall1[5].setposition(198,0);
        wall1[6].setposition(198,48);
        wall1[7].setposition(198,144);
        wall1[8].setposition(198,192);
        wall1[9].setposition(150,192);

        wall_num2=3;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(700,680-48);
        wall2[1].setposition(150,96);
        wall2[2].setposition(198,96);



    }

    else if(stageCount==8)
    {
        wall_num1=12;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(100,100);
        wall1[1].setposition(148,100);
        wall1[2].setposition(500,300);
        wall1[3].setposition(500,348);
        wall1[4].setposition(500,396);
        wall1[5].setposition(100,148);
        wall1[6].setposition(148,148);
        wall1[7].setposition(548,300);
        wall1[8].setposition(548,348);
        wall1[9].setposition(548,396);
        wall1[10].setposition(548,444);
        wall1[11].setposition(500,444);


        wall_num2=2;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(196,100);
        wall2[1].setposition(196,148);


    }

    else if(stageCount==9)
    {
        wall_num1=12;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(220,100);
        wall1[1].setposition(268,100);
        wall1[2].setposition(316,100);
        wall1[3].setposition(250,300);
        wall1[4].setposition(220,500);
        wall1[5].setposition(268,500);
        wall1[6].setposition(316,500);
        wall1[7].setposition(364,500);
        wall1[8].setposition(364,100);
        wall1[9].setposition(412,100);
        wall1[10].setposition(412,500);
        wall1[11].setposition(460,500);

        wall_num2=1;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(370,300);


    }

    else if(stageCount==10)
    {
        wall_num1=18;
        wall1.resize(wall_num1);

        for(int i=0; i<wall_num1; i++)
            wall1[i].setrenderer(renderer);

        wall1[0].setposition(300,680-48);
        wall1[1].setposition(300,680-48*1);
        wall1[2].setposition(300,680-48*2);
        wall1[3].setposition(300,680-48*3);
        wall1[4].setposition(300,680-48*4);
        wall1[5].setposition(300,680-48*5);
        wall1[6].setposition(300,680-48*6);
        wall1[7].setposition(300,680-48*7);
        wall1[8].setposition(300,680-48*8);
        wall1[9].setposition(300,680-48*9);
        wall1[10].setposition(300,680-48*10);
        wall1[11].setposition(300,680-48*11);
        wall1[12].setposition(300,680-48*12);
        wall1[13].setposition(150,200);
        wall1[14].setposition(150,248);
        wall1[15].setposition(150,296);
        wall1[16].setposition(150,344);
        wall1[17].setposition(150,392);

        wall_num2=2;
        wall2.resize(wall_num2);

        for(int i=0; i<wall_num2; i++)
            wall2[i].setrenderer(renderer);

        wall2[0].setposition(500,400);
        wall2[1].setposition(500,352);


    }
}

