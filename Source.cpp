#include <iostream>
#include <SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* render = NULL;

int win_width = 800, win_height = 600;
int Frames[3] = { 0, 0, 0 };

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

struct Firework
{
	float x, y;
	float vx, vy;
	int frames_to_reapear;
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

void DrawSmallWindows(HouseWindow window, int upx, int upy)
{
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor(render, window.color.r, window.color.g, window.color.b, window.color.a);
		SDL_Rect win_points = { window.x+upx, window.y + upy, 40, 30 };
		SDL_RenderFillRect(render, &win_points);
}

void DrawBigWindows(HouseWindow window, int upx, int upy)
{
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(render, window.color.r, window.color.g, window.color.b, window.color.a);
	SDL_Rect win_points = { window.x + upx, window.y + upy, 30, 40 };
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


void DrawFirework(Firework firework[3][4])
{
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	for (int i = 0; i < 3; i++)
	{
		float firerectside = 15;
		for (int j = 0; j < 4; j++)
		{ 
			SDL_SetRenderDrawColor(render, firework[i][j].color.r , firework[i][j].color.g, firework[i][j].color.b, firework[i][j].color.a);
			SDL_Rect Firework = {firework[i][j].x, firework[i][j].y, firerectside, firerectside };
			SDL_RenderFillRect(render, &Firework);
		}
	}
}

void UpdateFirework(Firework firework[3][4], int c)
{
	if (Frames[c] > 0)
	{
		Frames[c]-=1;
		return;
	}
		float onex = (float)random(0, 800);
		float oney = (float)random(0, 350);
		float onevx = (float)random(1, 4);
		float onevy = (float)random(2, 6);
		
		unsigned char r = random(0, 255);
		unsigned char g = random(0, 255);
		unsigned char b = random(0, 255);
		
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				firework[c][j].x += firework[c][j].vx;
				firework[c][j].y += firework[c][j].vy;
				firework[c][j].vy += 0.2;
			}
			if (j == 1)
			{
				firework[c][j].x -= firework[c][j].vx;
				firework[c][j].y += firework[c][j].vy;
				firework[c][j].vy += 0.2;
			}
			if (j == 2)
			{
				firework[c][j].x += firework[c][j].vx;
				firework[c][j].y += firework[c][j].vy;
				firework[c][j].vy += 0.2;
			}
			if (j == 3)
			{
				firework[c][j].x -= firework[c][j].vx;
				firework[c][j].y += firework[c][j].vy;
				firework[c][j].vy += 0.2;
			}
		}
		if (((firework[c][0].y > win_height + 30) || (firework[c][0].x > win_width + 30)) && ((firework[c][1].y > win_height + 30) || (firework[c][1].x > win_width + 30)) && ((firework[c][2].y > win_height + 30) || (firework[c][2].x > win_width + 30)) && ((firework[c][3].y > win_height + 30) || (firework[c][3].x > win_width + 30)))
		{
			Frames[c] = random(0,10);
			firework[c][0] = {onex, oney, onevx, -onevy, random(0,200), r, g, b, 255};
			firework[c][1] = { onex, oney, onevx, -onevy, random(0,200), r, g, b, 255};
			firework[c][2] = { onex, oney, onevx, onevy, random(0,200), r, g, b, 255};
			firework[c][3] = { onex, oney, onevx, onevy, random(0,200), r, g, b, 255};
		}
	
}

int main(int arcg, char* argv[])
{
	srand(time(NULL));
	system("chcp 1251");
	Init();
	
	bool isRunning = true;
	
	HouseWindow bigwindow[16];
	HouseWindow smallwindow[16];
	Firework firework[3][4];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			firework[i][j].frames_to_reapear = 0;
			firework[i][j].x = win_width + 100;
			firework[i][j].y = win_height + 100;
			firework[i][j].vx = 10;
			firework[i][j].vy = 0;
		}

	}
	

	for (int i = 0; i < 16; i++)
	{
		bigwindow[i].x = 275;
		bigwindow[i].y = 480;
		bigwindow[i].color.r = 255;
		bigwindow[i].color.g = 240;
		bigwindow[i].color.b = 0;
		bigwindow[i].color.a = random(0, 255);
	}

	for (int i = 0; i < 16; i++)
	{
		smallwindow[i].x = 10;
		smallwindow[i].y = 520;
		smallwindow[i].color.r = 255;
		smallwindow[i].color.g = 240;
		smallwindow[i].color.b = 0;
		smallwindow[i].color.a = random(0,255);
	}

	bool isLightUp = false;
	while (isRunning)
	{
		
		UpdateWindow(isLightUp, smallwindow);
		UpdateWindow(isLightUp, bigwindow);
		for (int i = 0; i < 3; i++)
		{
			UpdateFirework(firework, i);
		}

		SDL_SetRenderDrawColor(render, 10, 5, 65, 255);
		SDL_RenderClear(render);
		
		DrawBackground();
		
		int upx = 0;
		int upy = 0;
		for (int i = 0; i < 8; i++)
		{
			
			if (upx > 180 && upx <250 ) upx += 215;
			DrawSmallWindows(smallwindow[i],upx,upy);
			upx += 60;
		}
		upx = 0;
		upy = 0;
		for (int i = 8; i < 16; i++)
		{
			upy = 50;
			if (upx > 180 && upx < 250) upx += 215;
			DrawSmallWindows(smallwindow[i], upx, upy);
			upx += 60;
			
		}
		
		upx = 0;
		upy = 0;
		for (int i = 0; i < 8; i++)
		{

			if (upx > 160 && upx < 250) upx += 275;
			DrawBigWindows(bigwindow[i], upx, upy);
			upx += 60;
		}
		upx = 0;
		upy = 0;
		for (int i = 8; i < 16; i++)
		{
			upy = 70;
			if (upx > 160 && upx < 250) upx += 275;
			DrawBigWindows(bigwindow[i], upx, upy);
			upx += 60;

		}
		
		DrawFirework(firework);

		
		SDL_RenderPresent(render);

		SDL_Delay(30);
	}

	DeInit(0);
	return 0;
}