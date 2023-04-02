#pragma once
#include "SDL.h"

#include <conio.h>

struct Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

void setDrawColor(SDL_Renderer* ren, Color color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
}

void quit(SDL_Window* win)
{
	SDL_DestroyWindow(win);
	SDL_Quit();
}

// thx, stack overflow "https://stackoverflow.com/questions/9487793/collisions-in-sdl-c"
bool check_collision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}