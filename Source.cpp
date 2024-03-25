#include <iostream>
#include <SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* render = NULL;

int win_width = 800, win_height = 600;

int x = 0;
int y = 0;

bool isRightPressed = false;
bool isLeftPressed = false;
bool isUpPressed = false;
bool isDownPressed = false;

struct HouseWindow
{
	int x, y;
	SDL_Color color;
};

void DeInit(int error)
{
	if (render != NULL) SDL_DestroyRenderer(render);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Init Error! - %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow(
		"win", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		win_width,
		win_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (win == NULL)
	{
		printf("Window Error! - %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (render == NULL)
	{
		printf("Renderer Error! - %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}

SDL_Rect win_points = {10, 450, 50, 30};

void DrawBackground()
{ 
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	for (int i = 0; i <= win_width; i += 450)
	{
		SDL_Rect house = { 0 + i, 500, 250, 110 };
		SDL_RenderFillRect(render, &house);
	}

	for (int i = 250; i <= win_width; i += 450)
	{
		SDL_Rect house = { 0 + i, 450, 200, 170 };
		SDL_RenderFillRect(render, &house);
	}
}

int random(int a, int b)
{
	return rand()%(b-a+1)+a;
}

void DrawWindows(HouseWindow window, int upx, int upy)
{
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(render, window.color.r, window.color.g, window.color.b, window.color.a);
		SDL_Rect win_points = { window.x+upx, window.y + upy, 40, 30 };
		SDL_RenderFillRect(render, &win_points);
}

void UpdateWindow(bool isLightUp, HouseWindow smallwindow[])
{
	for (int i = 0; i < 16; i++)
	{
			if (isLightUp == true)
			{
				smallwindow[i].color.a += 1;
			}

			if (isLightUp == false)
			{
				smallwindow[i].color.a -= 1;
			}
		
			if (smallwindow[i].color.a <= 0) isLightUp = true;
			if (smallwindow[i].color.a >= 255) isLightUp = false;

	}
}
int main(int arcg, char* argv[])
{
	srand(time(NULL));
	system("chcp 1251");
	Init();
	
	bool isRunning = true;
	
	HouseWindow smallwindow[16];

	for (int i = 0; i < 16; i++)
	{
		smallwindow[i].x = 10;
		smallwindow[i].y = 510;
		smallwindow[i].color.r = 255;
		smallwindow[i].color.g = 240;
		smallwindow[i].color.b = 0;
		smallwindow[i].color.a = random(0,255);
	}

	bool isLightUp = false;
	while (isRunning)
	{
		

		SDL_SetRenderDrawColor(render, 10, 5, 65, 255);
		SDL_RenderClear(render);
		
		DrawBackground();
		
		int upx = 0;
		int upy = 0;
		for (int i = 0; i < 8; i++)
		{
			
			if (upx > 180 && upx <250 ) upx += 215;
			DrawWindows(smallwindow[i],upx,upy);
			upx += 60;
		}
		upx = 0;
		upy = 0;
		for (int i = 8; i < 16; i++)
		{
			upy = 55;
			if (upx > 180 && upx < 250) upx += 215;
			DrawWindows(smallwindow[i], upx, upy);
			upx += 60;
			
		}
		UpdateWindow(isLightUp, smallwindow);
		SDL_RenderPresent(render);
		

		SDL_Delay(20);
	}

	DeInit(0);
	return 0;
}