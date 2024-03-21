#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Window* win = NULL;
SDL_Renderer* render = NULL;

int win_width = 800, win_height = 600;
double sx;
double sy;

int sixSize = 100;
int radius[1000] = { 0 };

int x = 0;
int y = 0;


bool isRightPressed = false;
bool isLeftPressed = false;
bool isUpPressed = false;
bool isDownPressed = false;

double angle = 0;

void DeInit(int error)
{
	if (render != NULL) SDL_DestroyRenderer(render);
	if (win != NULL) SDL_DestroyWindow(win);
	IMG_Quit();
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

	int res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if (res == 0)
	{
		printf("Init Error! - %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	if (res & IMG_INIT_PNG) printf("Inintialized PNG library.\n"); else printf("Inintialize failed PNG library.\n");
	if (res & IMG_INIT_JPG) printf("Inintialized JPG library.\n"); else printf("Inintialize failed JPG library.\n");

	win = SDL_CreateWindow(
		"KVAJABLYABUSHKA", 
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

void DrawSix()
{
	for (int j = 0; j <= 600; j += 100)
	{
		for (int i = 0; i <= 800; i += sixSize*2)
		{
		SDL_RenderDrawLine(render, 35+i, 0+j, sixSize+i, 0+j);
		SDL_RenderDrawLine(render, 35+i, 0+j, 0+i, 50+j);
		SDL_RenderDrawLine(render, sixSize+i, 0+ j, sixSize + i + 35, 50+j);
		SDL_RenderDrawLine(render, sixSize + 35+i, 50+j, sixSize + i, 100+j);
		SDL_RenderDrawLine(render, sixSize+i, 100+j, 35 + i, 100+j);
		SDL_RenderDrawLine(render, 35+i, 100+j, 0+ i, 50+j);
		}
	}
	
	for (int j = 0; j <= 600; j += 100)
	{
		for (int i = 0; i <= 800; i += sixSize * 2)
		{
			SDL_RenderDrawLine(render, sixSize + 35+i, 50+j, sixSize + i + sixSize, 50+j);
		}
	}


}

void Circles()
{
	int RadiusCount = 0;
	printf("Введите количество окружостей: "); scanf_s("%i", &RadiusCount);

	int sum = 0;
	do
	{
	printf("Введите радиусы этих окружностей");
	
	for (int i = 0; i < RadiusCount; i++)
	{
		scanf_s("%i", &radius[i]);
	}

	for (int i = 0; i < RadiusCount; i++)
	{
		sum += radius[i];
	}

	if (2*sum > win_width)
		printf("Введены некорректные радиусы, введите их снова!");
	} while (2*sum > win_width);

	int x1, y1;

	int scale = 0;
	for (int j = 0; j < RadiusCount; j++)
	{
		for (double alpha = 0; alpha < 360; alpha += 0.5)
		{
			x1 = radius[j] * cos(alpha * M_PI / 180.0) + scale*2+radius[j];
			y1 = radius[j] * sin(alpha * M_PI / 180.0) + win_height/2;
			SDL_RenderDrawPoint(render,x1,y1);
		}
		scale += radius[j];
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
	SDL_Rect r = { cellsize, bordersize, 5, win_height - 2 * bordersize };
	SDL_RenderFillRect(render, &r);

	r = { 2 * cellsize, bordersize, 5, win_height - 2 * bordersize };
	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

	//горизонтальные линии
	r = { bordersize, cellsize, win_width - cellsize, 5 };
	SDL_RenderFillRect(render, &r); SDL_SetRenderDrawColor(render, 0, 255, 0, 255);

	r = { bordersize, 2 * cellsize, win_width - cellsize, 5 };
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


	SDL_RenderDrawLine(render, cellsize, 2 * cellsize, 2 * cellsize, 3 * cellsize - bordersize);
	SDL_RenderDrawLine(render, 2 * cellsize, 2 * cellsize, cellsize, 3 * cellsize - bordersize);

#pragma region T_T восьмиугольники (не бейте) :( 
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize + 30, cellsize + 2 * bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + bordersize + 30, cellsize + 30, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, cellsize + 2 * bordersize + 30, cellsize + bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + 30 + 3 * bordersize, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, cellsize + 3 * bordersize + 30, cellsize + bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30, cellsize + bordersize + 30, cellsize + 2 * bordersize + 30, cellsize + 30);

	SDL_RenderDrawLine(render, cellsize + 30, bordersize + 30, cellsize + bordersize + 30, 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30, 30);
	SDL_RenderDrawLine(render, cellsize + 30, bordersize + 30, cellsize + 30, 2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30, 2 * bordersize + 30, cellsize + bordersize + 30, 3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + bordersize + 30, 3 * bordersize + 30, cellsize + 2 * bordersize + 30, 3 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 2 * bordersize + 30, 3 * bordersize + 30, cellsize + 30 + 3 * bordersize, 2 * bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 30 + 3 * bordersize, 2 * bordersize + 30, cellsize + 3 * bordersize + 30, bordersize + 30);
	SDL_RenderDrawLine(render, cellsize + 3 * bordersize + 30, bordersize + 30, cellsize + 2 * bordersize + 30, 30);

	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 30, 2 * bordersize + 30, cellsize + 30);
	SDL_RenderDrawLine(render, 30, cellsize + bordersize + 30, 30, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30, cellsize + 2 * bordersize + 30, bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, cellsize + 3 * bordersize + 30, 2 * bordersize + 30, cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, 2 * bordersize + 30, cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30 + 3 * bordersize, cellsize + 2 * bordersize + 30, 3 * bordersize + 30, cellsize + bordersize + 30);
	SDL_RenderDrawLine(render, 3 * bordersize + 30, cellsize + bordersize + 30, 2 * bordersize + 30, cellsize + 30);

	SDL_RenderDrawLine(render, 30, 2 * cellsize + bordersize + 30, bordersize + 30, 2 * cellsize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, 2 * cellsize + 30, 2 * bordersize + 30, 2 * cellsize + 30);
	SDL_RenderDrawLine(render, 30, 2 * cellsize + bordersize + 30, 30, 2 * cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30, 2 * cellsize + 2 * bordersize + 30, bordersize + 30, 2 * cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, bordersize + 30, 2 * cellsize + 3 * bordersize + 30, 2 * bordersize + 30, 2 * cellsize + 3 * bordersize + 30);
	SDL_RenderDrawLine(render, 2 * bordersize + 30, 2 * cellsize + 3 * bordersize + 30, 30 + 3 * bordersize, 2 * cellsize + 2 * bordersize + 30);
	SDL_RenderDrawLine(render, 30 + 3 * bordersize, 2 * cellsize + 2 * bordersize + 30, 3 * bordersize + 30, 2 * cellsize + bordersize + 30);
	SDL_RenderDrawLine(render, 3 * bordersize + 30, 2 * cellsize + bordersize + 30, 2 * bordersize + 30, 2 * cellsize + 30);
#pragma endregion

	SDL_RenderDrawLine(render, 2 * cellsize + 2 * bordersize, bordersize, 2 * cellsize + bordersize, 3 * cellsize - bordersize);

	SDL_RenderPresent(render);

	SDL_Delay(2000000);

	DeInit(0);
	return 0;
}

void Work1()
{
	int choice;
	do {
		printf("Выберете задание: \n1 - Крестики - нолики\n2 - Шестиугольники\n3 - Окружности\n\n");
		scanf_s("%i",&choice);

		if (choice < 1 || choice>3) printf("\nВведено некорректное значение!\n");
	} while (choice<1 || choice>3);
	
	switch (choice)
	{
	case 1:
		TicTacToe();
		break;
	case 2:
		DrawSix();
		break;
	case 3:
		Circles();
		break;
	}
}

void WorkWithKeys()
{
		//Действия с зажатыми клавишами
		if (isUpPressed && !isDownPressed) y+=5; 
		if (!isUpPressed && isDownPressed) y-=5;
		if (isRightPressed && !isLeftPressed) x+=5;
		if (!isRightPressed && isLeftPressed) x-=5;
}


int main(int arcg, char* argv[])
{
	system("chcp 1251");
	Init();
	
	SDL_Surface* surface = IMG_Load("jaba.jpg");
	if (surface == NULL)
	{
		printf("Couldn`t load Jaba! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	SDL_Surface* win_surf = SDL_GetWindowSurface(win);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_Rect img_rect = { 0, 0, surface->w, surface->h };
	SDL_FreeSurface(surface);

	SDL_Event ev;
	bool isRunning = true;
		
	
	SDL_Rect dst_rect = { 0, 0, 0, 0 };

	while (isRunning)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT: //Выход из приложения (закрытие окна)
				isRunning = false;
				break;

			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED) //Изменения размеров окна
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
				break;

			case SDL_MOUSEBUTTONDOWN: //Обработка зажатия ЛКМ
				if (ev.button.button == SDL_BUTTON_LEFT)
				{
					x = ev.button.x;
					y = ev.button.y;
				}
				break;

			case SDL_KEYDOWN: //Обработка зажатия клавиш клавиатуры
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE: //Клавиша ESC
					isRunning = false;
					break;
				case SDL_SCANCODE_RIGHT: //Клавиша стрелка вправо
					x += 10;
					//isRightPressed = true;
					break;
				case SDL_SCANCODE_LEFT: //Клавиша стрелка влево
					x -= 10;
					//isLeftPressed = true;
					break;
				case SDL_SCANCODE_UP: //Клавиша стрелка вверх
					y -= 10;
					//isUpPressed = true;
					break;
				case SDL_SCANCODE_DOWN: //Клавиша стрелка вниз
					y += 10;
					//isDownPressed = true;
					break;
				case SDL_SCANCODE_PAGEUP:
					angle += 15;
					break;
				case SDL_SCANCODE_PAGEDOWN:
					angle -= 15;
					break;
				}

			case SDL_KEYUP: //Обработка отпускания клавиш клавиатуры
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_RIGHT: //Клавиша стрелка вправо
					isRightPressed = false;
					break;
				case SDL_SCANCODE_LEFT: //Клавиша стрелка влево
					isLeftPressed = false;
					break;
				case SDL_SCANCODE_UP: //Клавиша стрелка вверх
					isUpPressed = false;
					break;
				case SDL_SCANCODE_DOWN: //Клавиша стрелка вниз
					isDownPressed = false;
					break;
				}
				break;
			}
		}
		
		dst_rect = { x, y, img_rect.w, img_rect.h };

		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);
		
		//SDL_RenderCopy(render, texture, NULL, &dst_rect);
		SDL_RenderCopyEx(render, texture, NULL, &dst_rect, angle, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(render);
		


		SDL_Delay(10);
	}



	SDL_DestroyTexture(texture);
	DeInit(0);
	return 0;
}