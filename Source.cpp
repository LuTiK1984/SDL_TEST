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

//void DrawSix()
//{
//	for (int j = 0; j <= 600; j += 100)
//	{
//		for (int i = 0; i <= 800; i += sixSize*2)
//		{
//		SDL_RenderDrawLine(render, 35+i, 0+j, sixSize+i, 0+j);
//		SDL_RenderDrawLine(render, 35+i, 0+j, 0+i, 50+j);
//		SDL_RenderDrawLine(render, sixSize+i, 0+ j, sixSize + i + 35, 50+j);
//		SDL_RenderDrawLine(render, sixSize + 35+i, 50+j, sixSize + i, 100+j);
//		SDL_RenderDrawLine(render, sixSize+i, 100+j, 35 + i, 100+j);
//		SDL_RenderDrawLine(render, 35+i, 100+j, 0+ i, 50+j);
//		}
//	}
//	
//	for (int j = 0; j <= 600; j += 100)
//	{
//		for (int i = 0; i <= 800; i += sixSize * 2)
//		{
//			SDL_RenderDrawLine(render, sixSize + 35+i, 50+j, sixSize + i + sixSize, 50+j);
//		}
//	}
//
//
//}
//
//void Circles()
//{
//	int RadiusCount = 0;
//	printf("¬ведите количество окружостей: "); scanf_s("%i", &RadiusCount);
//
//	int sum = 0;
//	do
//	{
//	printf("¬ведите радиусы этих окружностей");
//	
//	for (int i = 0; i < RadiusCount; i++)
//	{
//		scanf_s("%i", &radius[i]);
//	}
//
//	for (int i = 0; i < RadiusCount; i++)
//	{
//		sum += radius[i];
//	}
//
//	if (2*sum > win_width)
//		printf("¬ведены некорректные радиусы, введите их снова!");
//	} while (2*sum > win_width);
//
//	int x1, y1;
//
//	int scale = 0;
//	for (int j = 0; j < RadiusCount; j++)
//	{
//		for (double alpha = 0; alpha < 360; alpha += 0.5)
//		{
//			x1 = radius[j] * cos(alpha * M_PI / 180.0) + scale*2+radius[j];
//			y1 = radius[j] * sin(alpha * M_PI / 180.0) + win_height/2;
//			SDL_RenderDrawPoint(render,x1,y1);
//		}
//		scale += radius[j];
//	}
//
//
//}
//
////int TicTacToe()
//{
//	Init();
//
//	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
//	SDL_RenderClear(render);
//
//	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
//
//	int bordersize = 50;
//	int cellsize = 200;
//
//	//вертикальные линии
//	SDL_Rect r = { cellsize, bordersize, 5, win_height - 2 * bordersize };
//	SDL_RenderFillRect(render, &r);
//
//	r = { 2 * cellsize, bordersize, 5, win_height - 2 * bordersize };
//	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
//
//	//горизонтальные линии
//	r = { bordersize, cellsize, win_width - cellsize, 5 };
//	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
//
//	r = { bordersize, 2 * cellsize, win_width - cellsize, 5 };
//	SDL_RenderFillRect(render, &r);
//	SDL_RenderPresent(render);
//
//
//	//крестики
//	SDL_SetRenderDrawColor(render, 155, 100, 200, 255);
//	SDL_RenderDrawLine(render, bordersize, bordersize, cellsize, cellsize);
//	SDL_RenderDrawLine(render, cellsize, bordersize, bordersize, cellsize);
//
//
//
//	SDL_RenderDrawLine(render, 2 * cellsize, bordersize, 3 * cellsize - bordersize, cellsize);
//	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, bordersize, 2 * cellsize, cellsize);
//
//	SDL_RenderDrawLine(render, 2 * cellsize, cellsize, 3 * cellsize - bordersize, 2 * cellsize);
//	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, cellsize, 2 * cellsize, 2 * cellsize);
//
//	SDL_RenderDrawLine(render, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize, 3 * cellsize - bordersize);
//	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize);
//
//
//	SDL_RenderDrawLine(render, cellsize, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize);
//	SDL_RenderDrawLine(render, 2 * cellsize, 2 * cellsize, cellsize, 3 * cellsize - bordersize);
//
//#pragma region T_T восьмиугольники (не бейте) :( 
//	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + bordersize + 30, cellsize + 30);
//	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize + 30, cellsize + 2 * bordersize + 30, cellsize + 30);
//	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + 30, cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 30, cellsize + 2 * bordersize + 30, cellsize + bordersize + 30, cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + 30 + 3 * bordersize, cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30, cellsize + bordersize + 30, cellsize + 2 * bordersize + 30, cellsize + 30);
//
//	SDL_RenderDrawLine(render, cellsize + 30, bordersize + 30, cellsize + bordersize + 30, 30);
//	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30, 30);
//	SDL_RenderDrawLine(render, cellsize + 30, bordersize + 30, cellsize + 30, 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 30, 2 * bordersize + 30, cellsize + bordersize + 30, 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 3 * bordersize + 30, cellsize + 2 * bordersize + 30, 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30, 3 * bordersize + 30, cellsize + 30 + 3 * bordersize, 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize, 2 * bordersize + 30, cellsize + 3 * bordersize + 30, bordersize + 30);
//	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30, bordersize + 30, cellsize + 2 * bordersize + 30, 30);
//
//	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, bordersize + 30, cellsize + 30);
//	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 30, 2 * bordersize + 30, cellsize + 30);
//	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, 30, cellsize + 2 * bordersize + 30, bordersize + 30, cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 3 * bordersize + 30, 2 * bordersize + 30, cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, 2 * bordersize + 30, cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, 3 * bordersize + 30, cellsize + bordersize + 30);
//	SDL_RenderDrawLine(render, 3 * bordersize + 30, cellsize + bordersize + 30, 2 * bordersize + 30, cellsize + 30);
//
//	SDL_RenderDrawLine(render, 30, 2 * cellsize + bordersize + 30, bordersize + 30, 2 * cellsize + 30);
//	SDL_RenderDrawLine(render, bordersize + 30, 2 * cellsize + 30, 2 * bordersize + 30, 2 * cellsize + 30);
//	SDL_RenderDrawLine(render, 30, 2 * cellsize + bordersize + 30, 30, 2 * cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, 30, 2 * cellsize + 2 * bordersize + 30, bordersize + 30, 2 * cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, bordersize + 30, 2 * cellsize + 3 * bordersize + 30, 2 * bordersize + 30, 2 * cellsize + 3 * bordersize + 30);
//	SDL_RenderDrawLine(render, 2 * bordersize + 30, 2 * cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, 2 * cellsize + 2 * bordersize + 30);
//	SDL_RenderDrawLine(render, 30 + 3 * bordersize, 2 * cellsize + 2 * bordersize + 30, 3 * bordersize + 30, 2 * cellsize + bordersize + 30);
//	SDL_RenderDrawLine(render, 3 * bordersize + 30, 2 * cellsize + bordersize + 30, 2 * bordersize + 30, 2 * cellsize + 30);
//#pragma endregion
//
//	SDL_RenderDrawLine(render, 2 * cellsize + 2 * bordersize, bordersize, 2 * cellsize + bordersize, 3 * cellsize - bordersize);
//
//	SDL_RenderPresent(render);
//
//	SDL_Delay(2000000);
//
//	DeInit(0);
//	return 0;
//}

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

int main(int arcg, char* argv[])
{
	system("chcp 1251");
	Init();
	

	bool isRunning = true;
		
	while (isRunning)
	{
		
	

		SDL_SetRenderDrawColor(render, 10, 5, 65, 255);
		SDL_RenderClear(render);
		
		DrawBackground();

		SDL_RenderPresent(render);
		


		SDL_Delay(10);
	}

	DeInit(0);
	return 0;
}