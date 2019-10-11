#pragma once
#include "SDL.h"
#include "Shape.h"
#include "SDL_ttf.h"
#include <string>

class Window
{
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	int _width, _height;
	std::string _title;
	SDL_Color _color;
	TTF_Font* _font;

	bool init();

public:
	Window(std::string title, int width, int height);
	~Window();
	void clear();
	void setPos(int x, int y);
	void getPos(int* x, int* y);
	void draw(SDL_Rect rect, int r, int g, int b);
	void drawShape(Shape shape, int grid[][10][4]);
	void drawShape(Shape shape);
	void drawText(std::string text);
	void drawGrid(int grid[][10][4]);
	void present();
};

