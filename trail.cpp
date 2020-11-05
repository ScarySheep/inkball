#include "trail.h"
#include <iostream>
#include <cmath>

static int objectCount = 0;

Trail::Trail()
{

    addLine();

    flipType = SDL_FLIP_NONE;

    center.x = 0;
    center.y = IMAGEHEIGHT/2;



}

void Trail::activeLine(double x1, double y1, double x2, double y2)
{
    image[objectCount-1].x = x1;
    image[objectCount-1].y = y1;
    image[objectCount-1].clip.w = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    image[objectCount-1].a = atan2((y2-y1),(x2-x1)) * 180 / 3.1415;
    //printf("%d",length);
}

void Trail::finishLine(double x1, double y1, double x2, double y2)
{
    /*finished = clock();
    duration = (double)(finished - start) / CLOCKS_PER_SEC;
    printf("%f second\n",duration);*/
    image[objectCount-1].clip.w = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    image[objectCount-1].a = atan2((y2-y1),(x2-x1)) * 180 / 3.1415;
    image[objectCount-1].x = x1;
    image[objectCount-1].y = y1;
    addLine();

}
void Trail::draw()
{
    for(int i=0; i<objectCount; i++)
    {
        addon.render(image[i].x-IMAGEHEIGHT/2,image[i].y-IMAGEHEIGHT/2);
        texture.renderEx(image[i].x,image[i].y-IMAGEHEIGHT/2,&(image[i].clip),image[i].a,&center,flipType);
        //printf("%f\n",image[i].l);
    }
}


void Trail::addLine()
{
    //start = clock();
    objectCount++;
    image.resize(objectCount);
    image[objectCount-1].clip.x = 0;
    image[objectCount-1].clip.y = 0;
    image[objectCount-1].clip.h = IMAGEHEIGHT;
    //printf("%d ",objectCount);
}

void Trail::free(){
    //texture.free();
    image.clear();
    objectCount = 0;
    addLine();
}

void Trail::loadMedia(SDL_Renderer* r){
    texture.renderer = r;
    if(!texture.loadFromFile("Resources/trail.png"))
    {
        printf("Failed to load trail texture!\n");
    }
    addon.renderer = r;
    if(!addon.loadFromFile("Resources/trail_addon.png"))
    {
        printf("Failed to load addon texture!\n");
    }

}
