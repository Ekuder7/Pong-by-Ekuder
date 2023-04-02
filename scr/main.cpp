#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>

#include <SDL.h>

#include "Player.hpp"
#include "Helpers.hpp"
#include "Colors.hpp"

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 720;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Event windowEvent;

int BallspeedX = 3;
int BallspeedY = 3;

int goalplayer = 0;
int goalenemy = 0;

bool Running;

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	// initialize SDL											   
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{					   
		win = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
		if (win != 0)
		{
			ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}
	}
	else
		return false;

	return true;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	if (init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) Running = true;
	else
	{
		std::cout << "initialize error" << std::endl;
		_getch();
		return 1;
	}

	// player(int Xcord, int Ycord, int Height, int Width)
	Player player(50, 200, 100, 13);
	Player ball(500, 300, 20, 20);
	Player enemy(1230, 200, 100, 13);

	BallspeedX = 3;
	BallspeedY = 3;

	int lastposX = 0;
	int timecounter = 0;
	int timecounter2 = 0;

	while (Running)
	{
		setDrawColor(ren, BgBlue);

		SDL_RenderClear(ren);

		ball.rect.x += BallspeedX;
		ball.rect.y += BallspeedY;

		// do not fly away from the screen
		if (ball.rect.y > 700)
		{
			BallspeedY = -BallspeedY;
		}
		if (ball.rect.y < 0)
		{
			BallspeedY = -BallspeedY;
		}

		// goal check
		if (ball.rect.x > 1260)
		{
			goalplayer++;

			ball.Restart();
			BallspeedX = 3;
			BallspeedY = 3;

			cout << "goal" << endl;
		}
		if (ball.rect.x < 0)
		{
			goalenemy++;

			ball.Restart();
			BallspeedX = 3;
			BallspeedY = 3;

			cout << "loose" << endl;
		}

		// collision
		if (check_collision(player.rect, ball.rect))
		{
			BallspeedX = -BallspeedX;
		}
		if (check_collision(enemy.rect, ball.rect))
		{
			BallspeedX = -BallspeedX;
		}

		// AI
		if (ball.rect.x > 800)
		{
			timecounter2++;
			if (timecounter2 > 2)
			{
				lastposX = ball.rect.x;
				timecounter2 = 0;
			}

			if (lastposX < ball.rect.x)
			{
				if (ball.rect.y > enemy.rect.y + 49)
				{
					enemy.rect.y += ball.rect.x / 500 + abs(BallspeedX);
				}
				else if (ball.rect.y < enemy.rect.y + 49)
				{
					enemy.rect.y -= ball.rect.x / 500 + abs(BallspeedX);
				}
			}
		}

		// ball acceleration
		timecounter++;
		if (timecounter > 500)
		{
			if (BallspeedX > 0)
			{
				BallspeedX++;
			}
			else
			{
				BallspeedX--;
			}
			if (BallspeedY > 0)
			{
				BallspeedY++;
			}
			else
			{
				BallspeedY--;
			}

			timecounter = 0;
		}

		// events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				Running = false;
			}

			/*
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{ 
					case SDLK_UP: player.rect.y > 0 ? player.rect.y -= 8 : player.rect.y -= 0; break;
					case SDLK_DOWN: player.rect.y < 620 ? player.rect.y += 8 : player.rect.y += 0; break;
				}
			}
			*/
		}

		// only for windows, used for better game control
		if (GetAsyncKeyState(VK_UP))
		{
			player.rect.y > 0 ? player.rect.y -= 3 + abs(BallspeedX) : player.rect.y -= 0;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			player.rect.y < 620 ? player.rect.y += 3 + abs(BallspeedX) : player.rect.y += 0;
		}

		player.Present(ren, SaladGreen);
		ball.Present(ren, Black);
		enemy.Present(ren, Red);
		SDL_RenderPresent(ren);
	}

	quit(win);
	return EXIT_SUCCESS;
}