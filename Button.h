#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include <string>

//The mouse button
class Button
{
public:
    //Initializes internal variables
    Button();

    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    bool handleEvent( SDL_Event* e );

    //Shows button sprite
    void render();

    void loadMedia(std::string, SDL_Renderer*);

    void free();

    enum ButtonSprite
    {
        BUTTON_SPRITE_MOUSE_OUT = 0,
        BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
        BUTTON_SPRITE_MOUSE_DOWN = 2,
        BUTTON_SPRITE_MOUSE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };

private:
    //Top left position
    SDL_Point position;

    //Currently used global sprite
    ButtonSprite currentSprite;

    LTexture buttonTexture;

    //Mouse button sprites
    SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];

    //Button constants
    int BUTTON_WIDTH;
    int BUTTON_HEIGHT;
};

#endif // BUTTON_H_INCLUDED
