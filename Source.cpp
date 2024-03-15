#include <iostream>
#include <SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* render = NULL;
int win_width = 800; int win_height = 600;


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

int main(int arcg, char* argv[])
{
	Init();

	SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
	SDL_RenderClear(render);

	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderDrawLine(render, 100, 100, 40, 300);
	SDL_RenderDrawLine(render, 100, 100, 160, 300);
	SDL_RenderDrawLine(render, 50, 150, 160, 150);
	SDL_RenderDrawLine(render, win_width - 1, 0, win_width - 1, win_height);

	int bordersize = 50;

	SDL_Rect r = {0, 0, win_width, win_height};
	SDL_RenderDrawRect(render, &r);
	SDL_RenderFillRect(render, &r);

	SDL_RenderPresent(render);

	SDL_Delay(2000);

	DeInit(0);
	return 0;
}