#include "Button.h"


Button::Button()
{
    BUTTON_WIDTH = 0;
    BUTTON_HEIGHT = 0;

	position.x = 0;
	position.y = 0;

	currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition( int x, int y )
{
	position.x = x;
	position.y = y;
}

bool Button::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			currentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

				case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                return true;
                break;

			}
		}
	}
	return false;
}

void Button::render()
{
	//Show current button sprite
	buttonTexture.renderEx( position.x, position.y, &spriteClips[ currentSprite ],0,NULL,SDL_FLIP_NONE);
}

void Button::loadMedia(std::string str, SDL_Renderer* r){
    buttonTexture.renderer = r;

	//Load sprites
	if( !buttonTexture.loadFromFile( str ) )
	{
		printf( "Failed to load button sprite texture!\n" );
	}
	else
	{

	    BUTTON_WIDTH = buttonTexture.getWidth()/BUTTON_SPRITE_TOTAL;
	    BUTTON_HEIGHT = buttonTexture.getHeight();
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; i++ )
		{
			spriteClips[ i ].x = i * BUTTON_WIDTH;
			spriteClips[ i ].y = 0;
			spriteClips[ i ].w = BUTTON_WIDTH;
			spriteClips[ i ].h = BUTTON_HEIGHT;
		}

	}
}

void Button::free()
{
    buttonTexture.free();
}

