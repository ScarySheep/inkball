#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>



//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path);

    //Deallocates texture
    void free();

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y );

    void renderEx( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font*);

    //Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Renderer* renderer;

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // LTEXTURE_H_INCLUDED
