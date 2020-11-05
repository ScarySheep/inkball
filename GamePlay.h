#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include <string>
#include <SDL_ttf.h>
#include "Button.h"
#include "trail.h"
#include "WallA.h"

class GamePlay
{
public:
    GamePlay(SDL_Renderer*);
    void init(int);
    void loadMedia();
    void show();
    void free();
    int getState();
    enum State {Playing, NextStage, Menu, Exiting};
    State state;
    Trail trail;

    void setRemainTry();
    void setPercent();
    int getStar(int i);

    void playEndAni();

    void loadWall();

    int star[10];

private:
    LTexture background;
    LTexture scoreTexture;
    LTexture scoreStar;
    SDL_Rect scoreStarClip;
    LTexture frame;

    LTexture stageTextTexture;
    LTexture stageBackTextTexture;

    LTexture remainTextTexture;
    LTexture remainBackTextTexture;

    LTexture percentTextTexture;
    LTexture percentBackTextTexture;



    Button button_menu;
    Button button_restart;
    SDL_Renderer* renderer;

    TTF_Font* stageFont;
    TTF_Font* stageBackFont;

    TTF_Font* remainFont;
    TTF_Font* remainBackFont;

    TTF_Font* percentFont;
    TTF_Font* percentBackFont;

    SDL_Color textColor;

    std::string stage;
    std::string remain;
    std::string percent;

    int remainTry;
    int areaPercent;
    int stageCount;

    bool finished;
    bool setFinished;
    bool finishedTranslation;
    bool delayed;

    long oldTime;
    int star_count;

    int score_x;
    int score_y;
    int scoreStar_x;
    int scoreStar_y;



    int start;
    int wall_num1,wall_num2,Level,playing_times;
    vector<WallA> wall1;
    vector<WallB> wall2;

    bool startBounce;
    float oldcenterX;
    float oldcenterY;
};


#endif // PLAYING_H_INCLUDED
