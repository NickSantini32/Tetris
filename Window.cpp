#include "Window.h"
#include "Shape.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>

Window::Window(std::string title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	init();
}
Window::~Window()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
void Window::draw(SDL_Rect rect, int r, int g, int b)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, 200);
	SDL_RenderFillRect(_renderer, &rect);
}
void Window::drawText(std::string text)
{	
	TTF_Init();

	_color = { 0, 0, 0 };
	_font = TTF_OpenFont("arial.ttf", 25);
	SDL_Surface* _surface = TTF_RenderText_Solid(_font,
		text.c_str(), _color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, _surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect rect = { 0, 0, texW, texH };
	SDL_RenderCopy(_renderer, texture, NULL, &rect);

	TTF_CloseFont(_font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(_surface);

	TTF_Quit();
}
void Window::drawGrid(int grid[][10][4])
{
	int DIM = Shape::getDim();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j][0] == 1)
			{
				SDL_Rect rect;
				rect.x = j * DIM;
				rect.y = i * DIM;
				rect.w = DIM;
				rect.h = DIM;

				draw(rect, grid[i][j][1], grid[i][j][2], grid[i][j][3]);
			}
		}
	}
}
void Window::drawShape(Shape shape, int grid[][10][4])
{
	int* X = shape.getX();
	int* Y = shape.getY();
	int* color = shape.getColor();
	int DIM = Shape::getDim();

	
	
	SDL_Rect rect[4];
	for (int i = 0; i < 4; i++)
	{
		rect[i].x = X[i];
		rect[i].y = Y[i];
		rect[i].w = DIM;
		rect[i].h = DIM;

		SDL_SetRenderDrawColor(_renderer, color[0], color[1], color[2], 200);
		SDL_RenderFillRect(_renderer, &rect[i]);
	}

	float distance[4], finalDist;
	int tempY;
	for (int i = 0; i < 4; i++)
	{
		for (int j = Y[i] / DIM; j < 20; j++)
		{
			if (grid[j][X[i] / DIM][0] == 1)
			{
				distance[i] = j * DIM - Y[i];
				break;
			}
			else if (j == 19)
			{
				distance[i] = 800 - Y[i];
			}
		}
	}
	finalDist = distance[0];
	for (int i = 0; i < 4; i++)
	{
		if (distance[i] < finalDist)
		{
			finalDist = distance[i];
		}
	}
	SDL_Rect ghost[4];
	for (int i = 0; i < 4; i++)
	{
		if ((int)(Y[i] + finalDist - DIM + 1) % DIM < 10)
		{
			tempY = (int)(Y[i] + finalDist - DIM + 1) - (int)(Y[i] + finalDist - DIM + 1) % DIM;
		}
		else
		{
			tempY = (int)(Y[i] + finalDist - DIM + 1);
		}
		ghost[i].x = X[i];
		ghost[i].y = tempY;
		ghost[i].w = DIM;
		ghost[i].h = DIM;
		SDL_SetRenderDrawColor(_renderer, color[0], color[1], color[2], 150);
		SDL_RenderDrawRect(_renderer, &ghost[i]);
	}
}
void Window::drawShape(Shape shape)
{
	int* X = shape.getX();
	int* Y = shape.getY();
	int* color = shape.getColor();
	int DIM = Shape::getDim();

	SDL_Rect rect[4];
	for (int i = 0; i < 4; i++)
	{
		rect[i].x = X[i];
		rect[i].y = Y[i];
		rect[i].w = DIM;
		rect[i].h = DIM;

		SDL_SetRenderDrawColor(_renderer, color[0], color[1], color[2], 200);
		SDL_RenderFillRect(_renderer, &rect[i]);
	}
}
void Window::setPos(int x, int y)
{
	SDL_SetWindowPosition(_window, x, y);
}
void Window::getPos(int* x, int* y)
{
	SDL_GetWindowPosition(_window, x, y);
}
bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Could not init";
	}


	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width,
		_height,
		SDL_WINDOW_SHOWN);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	return true;
}
void Window::clear()
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}
void Window::present()
{
	SDL_RenderPresent(_renderer);
}
