#pragma once
#include <string>

#include "SDL.h"
#include "Helpers.hpp"
#include "Colors.hpp"

using namespace std;

class Player
{
private:
	SDL_Rect _originalPos;

public:
	SDL_Rect rect;

	Player(int Xcord, int Ycord, int height, int width)
	{
		rect.x = Xcord;
		rect.y	= Ycord;
		rect.h = height;
		rect.w = width;

		_originalPos = rect;
	}

	void Present(SDL_Renderer* ren, Color color)
	{
		setDrawColor(ren, color);
		SDL_RenderFillRect(ren, &rect);
	}

	void Restart()
	{
		rect = _originalPos;
	}
};