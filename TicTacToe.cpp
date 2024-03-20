#include <iostream>
#include <SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* render = NULL;
int win_width = 800, win_height = 600;


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
		"Just window", 
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

int TicTacToe()
{
	Init();

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderClear(render);

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	
	int bordersize = 50;
	int cellsize = 200;

	//вертикальные линии
	SDL_Rect r = {cellsize, bordersize, 5, win_height - 2*bordersize};
	SDL_RenderFillRect(render, &r);

	r = {2*cellsize, bordersize, 5, win_height - 2*bordersize};
	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	
	//горизонтальные линии
	r = {bordersize, cellsize, win_width - cellsize, 5};
	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	
	r = {bordersize, 2* cellsize, win_width - cellsize, 5};
	SDL_RenderFillRect(render, &r);
	SDL_RenderPresent(render);


	//крестики
	SDL_SetRenderDrawColor(render, 155, 100, 200, 255);
	SDL_RenderDrawLine(render, bordersize, bordersize, cellsize, cellsize);
	SDL_RenderDrawLine(render, cellsize, bordersize, bordersize, cellsize);
	


	SDL_RenderDrawLine(render, 2 * cellsize, bordersize, 3 * cellsize - bordersize, cellsize);
	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, bordersize, 2 * cellsize, cellsize);
	
	SDL_RenderDrawLine(render, 2 * cellsize, cellsize, 3 * cellsize - bordersize, 2 * cellsize);
	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, cellsize, 2 * cellsize, 2 * cellsize);

	SDL_RenderDrawLine(render, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize, 3 * cellsize - bordersize);
	SDL_RenderDrawLine(render, 3 * cellsize - bordersize, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize);
	
	
	SDL_RenderDrawLine(render, cellsize, 2 * cellsize, 2 * cellsize , 3 * cellsize - bordersize);
	SDL_RenderDrawLine(render, 2 * cellsize, 2 * cellsize, cellsize, 3 * cellsize - bordersize);

	#pragma region T_T восьмиугольники (не бейте) :( 
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + bordersize + 30,cellsize + 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize +30, cellsize + 2 * bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + 30, cellsize + 2* bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + 2 * bordersize + 30, cellsize + bordersize + 30, cellsize + 3*bordersize+ 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize + 3 * bordersize+ 30, cellsize + 2 * bordersize + 30, cellsize + 3*bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + 30 + 3*bordersize , cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, cellsize + 3*bordersize + 30, cellsize+bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30, cellsize + bordersize + 30, cellsize + 2 * bordersize + 30, cellsize + 30);

	SDL_RenderDrawLine(render, cellsize + 30, bordersize + 30, cellsize + bordersize + 30, 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30, 30);
	SDL_RenderDrawLine(render, cellsize + 30,  bordersize + 30, cellsize + 30,  2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, 2 * bordersize + 30, cellsize + bordersize + 30, 3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 3 * bordersize + 30, cellsize + 2 * bordersize + 30,  3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30,  3 * bordersize + 30, cellsize + 30 + 3 * bordersize,  2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize,  2 * bordersize + 30, cellsize + 3 * bordersize + 30,  bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30,  bordersize + 30, cellsize + 2 * bordersize + 30, 30);

	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 30, 2 * bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30, cellsize + 2 * bordersize + 30, bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 3 * bordersize + 30, 2 * bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, 2 * bordersize + 30, cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, 3 * bordersize + 30, cellsize + bordersize + 30);
	SDL_RenderDrawLine(render, 3 * bordersize + 30, cellsize + bordersize + 30, 2 * bordersize + 30, cellsize + 30);

	SDL_RenderDrawLine(render, 30, 2*cellsize + bordersize + 30, bordersize + 30, 2*cellsize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, 2*cellsize + 30, 2 * bordersize + 30, 2*cellsize + 30);
	SDL_RenderDrawLine(render, 30, 2*cellsize + bordersize + 30, 30, 2*cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30, 2*cellsize + 2 * bordersize + 30, bordersize + 30, 2*cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, 2*cellsize + 3 * bordersize + 30, 2 * bordersize + 30, 2*cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, 2 * bordersize + 30, 2*cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, 2*cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30 + 3 * bordersize, 2*cellsize + 2 * bordersize + 30, 3 * bordersize + 30, 2*cellsize + bordersize + 30);
	SDL_RenderDrawLine(render, 3 * bordersize + 30, 2*cellsize + bordersize + 30, 2 * bordersize + 30, 2*cellsize + 30);
	#pragma endregion

	SDL_RenderDrawLine(render, 2 * cellsize + 2* bordersize, bordersize, 2 * cellsize + bordersize, 3 * cellsize - bordersize  );

	SDL_RenderPresent(render);

	SDL_Delay(2000000);

	DeInit(0);
	return 0;
}