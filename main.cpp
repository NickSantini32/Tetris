#include <iostream>
#include "Window.h"
#include "SDL.h"
#include "Shape.h"
#include <ctime>
#include <cstdlib>

bool updateGrid(Shape *obj, int grid[][10][4], int* score);

int main(int argc, char** argv)
{
	using namespace std;

	bool gameRunning = true;
	bool lose = false;	

	int grid[20][10][4], score = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			grid[j][i][0] = 0;
		}		
	}

	Window window1("Tetris", 400, 800);
	Window window2("Next Shape", 250, 250);

	int tempx, tempy;
	window1.getPos(&tempx, &tempy);
	window2.setPos(tempx + 400, tempy);

	Shape obj;
	window2.clear();
	window2.drawShape(obj.getNext());
	window2.present();

	while (gameRunning)
	{				
		window1.clear();		
		if (!obj.moveDown(grid))
		{	
			window2.clear();
			window2.drawShape(obj.getNext());
			window2.present();
			if (!updateGrid(&obj, grid, &score))
			{
				gameRunning = false;
				lose = true;
			}
		}
		window1.drawShape(obj, grid);
		window1.drawGrid(grid);		
		window1.drawText("Score: " + to_string(score));

		SDL_Event event;
		
		if (SDL_PollEvent(&event) == 1)
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
			{		
				switch (event.key.keysym.sym)
				{
				case SDLK_a:
				{
					obj.moveLeft(grid);
					continue;
				}
				case SDLK_d:
				{
					obj.moveRight(grid);
					continue;
				}
				case SDLK_w:
				{
					obj.rotate(grid);
					continue;
				}
				case SDLK_s:
				{
					obj.rotate(grid);
					continue;
				}
				case SDLK_LEFT:
				{
					obj.moveLeft(grid);
					continue;
				}
				case SDLK_RIGHT:
				{
					obj.moveRight(grid);
					continue;
				}
				case SDLK_UP:
				{
					obj.rotate(grid);
					continue;
				}
				case SDLK_DOWN:
				{
					obj.rotate(grid);
					continue;
				}
				case SDLK_SPACE:
				{
					obj.down(grid);
					continue;
				}
				default:
				{
					continue;
				}

				}
			}
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event) 
				{
				case SDL_WINDOWEVENT_CLOSE:
				{
					gameRunning = false;
					break;
				}	
				}
			}
			}
		}		
		window1.present();
	}

	if (!gameRunning && lose)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Game Over",
			"U lose nerd",
			NULL);
	}
	
	return 0;
}
bool updateGrid(Shape *obj, int grid[][10][4], int *score)
{
	bool full = true;
	int rows = 0;
	for (int i = 0; i < 10; i++)
	{
		if (grid[0][i][0] == 1)
		{			
			return false;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		full = true;
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j][0] != 1)
			{
				full = false;
				break;
			}
		}
		if (full)
		{
			for (int k = i; k > 0; k--)
			{
				for (int l = 0; l < 10; l++)
				{
					for (int p = 0; p < 4; p++)
					{
						grid[k][l][p] = grid[k - 1][l][p];
					}
				}
			}
			for (int k = 0; k < 10; k++)
			{
				grid[0][k][0] = 0; 
			}
			obj->addSpeed();
			rows += 1;
		}
	}

	full = false;
	for (int k = 0; k < 20; k++)
	{
		for (int l = 0; l < 10; l++)
		{
			if (grid[k][l][0] == 1)
			{
				full = true;
				break;
			}
		}
	}
	if (!full)
	{
		switch (rows)
		{
		case 1:
		{
			*score += 2000;
			break;
		}
		case 2:
		{
			*score += 8000;
			break;
		}
		case 3:
		{
			*score += 18000;
			break;
		}
		case 4:
		{
			*score += 40000;
			break;
		}
		}
	}
	else 
	{
		switch (rows)
		{
		case 1:
		{
			*score += 100;
			break;
		}
		case 2:
		{
			*score += 400;
			break;
		}
		case 3:
		{
			*score += 900;
			break;
		}
		case 4:
		{
			*score += 2000;
			break;
		}
		}
	}	
	return true;
}