#ifndef TRAIL_H_INCLUDED
#define TRAIL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include <vector>
#include <time.h>

using namespace std;

class Trail
{

public:
    Trail();
    void activeLine(double x1, double y1, double x2, double y2);
    void finishLine(double x1, double y1, double x2, double y2);
    void draw();
    void free();
    void loadMedia(SDL_Renderer*);

    static const int IMAGEWIDTH = 1470;
    static const int IMAGEHEIGHT = 96;

private:


    struct Line
    {
        SDL_Rect clip;
        double a;
        double x;
        double y;
    };

    LTexture texture;
    LTexture addon;
    void addLine();
    vector<struct Line> image;


    SDL_RendererFlip flipType;
    SDL_Point center;

    static const int PI = 3.1415926;


};

#endif // TRAIL_H_INCLUDED
