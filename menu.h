#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Button.h"
#include <vector>

class Menu
{
public:
    Menu(SDL_Renderer*);
    ~Menu();
    bool Show();
    void loadMedia();
    void free();
    void setStage(int);
    int getStage();
    void setStars(int);
    int getStars();

private:
    SDL_Renderer* renderer;
    LTexture background;
    LTexture unlock;

    LTexture zero_star;
    LTexture one_star;
    LTexture two_star;
    LTexture three_star;

    Button ok_button[10];
    int stage;

    struct Info
    {
        bool unlocked;
        int stars;
    };

    std::vector<struct Info> stageInfo;

};


#endif // MENU_H_INCLUDED
