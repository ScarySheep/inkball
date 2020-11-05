#include "Animation.h"

Animation::Animation(){
    currentFrame = 0;
    framerate = 100;
    oldTime = 0;
    maxFrames = 0;
    direction = 1;
    start = true;
}

void Animation::animate(){
    if(start){
        oldTime = SDL_GetTicks();
        start = false;
    }

    if(oldTime + framerate > SDL_GetTicks()){
        return;
    }

    oldTime = SDL_GetTicks();

    currentFrame += direction;

    if(currentFrame >= maxFrames-1||currentFrame <= 0){
        direction = -direction;
    }
}

void Animation::setFramerate(int rate){
    framerate = rate;
}

int Animation::getCurrentFrame(){
    return currentFrame;
}

void Animation::setMaxFrame(int i){
    maxFrames = i;
    frames.resize(maxFrames);
}

bool Animation::loadTexture(string str, SDL_Renderer* renderer){
    texture.renderer = renderer;

    if( !texture.loadFromFile(str) )
    {
        cout<<"Failed to load media!\n";
        return false;
    }else{
        if(maxFrames == 0){
            cout<<"Maxframes not set!\n";
            return false;
        }

        int width = (texture.getWidth())/maxFrames;
        int height = texture.getHeight();

        for(int i = 0; i<maxFrames; i++){
            frames[i].x = width*i;
            frames[i].y = 0;
            frames[i].w = width;
            frames[i].h = height;
        }

        return true;
    }
}

void Animation::render(int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip){
    texture.renderEx(x, y, &frames[currentFrame], angle, center, flip );
}

void Animation::free(){
    texture.free();
}
