#include <iostream>
#include "Window.h"
#include "SDL.h"
#include "Shape.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool updateGrid(Shape *obj, int grid[][10][4], int* score);
struct highScore {
	int score;
	string name;
	highScore(string n = "", int sc = 0) {
		name = n;
		score = sc;
	}
};
void sort(vector<highScore>& v);
int main(int argc, char** argv)
{
	
	bool gameRunning = true;
	bool playAgain = true;

	int grid[20][10][4], score = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			grid[j][i][0] = 0;
		}		
	}
	const string HSfile = "scores.dat";
	ifstream inFS;
	ofstream oFS;
	inFS.open(HSfile);
	if (!inFS.is_open()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			(HSfile + " was not found, please create the file in the root directory or reinstall the program").c_str(),
			NULL);
		return 1;
	}
	inFS.close();

	Window window1("Tetris", 400, 800);
	Window window2("Next Shape", 250, 250);
	Window window3("Save", 250, 250);
	Window endScreen("GG", 400, 400);
	Window textInputScreen("High Score!", 300, 100);
	textInputScreen.show(false);
	endScreen.show(false);

	int tempx, tempy;
	window1.getPos(&tempx, &tempy);
	window2.setPos(tempx + 400, tempy);
	window3.setPos(tempx + 400, tempy + 250);

	Shape obj;
	window2.clear();
	window2.drawShape(obj.getNext());
	window2.present();

	window3.clear();

	while (true)
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
				case SDLK_q:
				{
					obj.save(grid);
					window3.clear();	
					window3.drawShape(obj.getSaved());
					window3.present();
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
					return 0;
				}	
				}
			}
			}
		}		
		window1.present();
		if (!gameRunning)
		{
			bool endLoop = true;
			vector<highScore> highscores;
			highScore HS;
			SDL_Rect selectionBox{115, 70 + 27 * 9, 50, 30};
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Game Over",
				"U lose nerd",
				NULL);
			inFS.open(HSfile);		
			while (inFS >> HS.name) { //Load in High Scores
				inFS >> HS.score;
				highscores.push_back(HS);
			}
			inFS.close();

			cout << "Vector after load: ";
			for (int j = 0; j < highscores.size(); j++) {
				cout << highscores.at(j).name << " ";
			}
			cout << endl;

			endScreen.show(true);
			for (int i = 0; i < highscores.size() && i < 5 || highscores.size() == 0; i++) {
				if (highscores.size() == 0 || score > highscores.at(i).score || highscores.size() < 5) { // checks if user score is greater than any of the top 5 or if there are less than 5
					textInputScreen.show(true);
					string name = "";
					int charLimit = 15;
					bool switcher = false;
					while (endLoop) {	//handles text input for high score name entry
						textInputScreen.clear();
						SDL_StartTextInput();
						if (SDL_PollEvent(&event) == 1)
						{
							switch (event.type)
							{
							case SDL_KEYDOWN:
							{
								switch (event.key.keysym.sym)
								{
								case SDLK_BACKSPACE: {
									if (name.size() > 0)
										name.pop_back();
									continue;
								}
								case SDLK_RETURN: {
									if (name.size() > 0)
										endLoop = false;
									continue;
								}
								case SDLK_LSHIFT:{
									continue;
								}
								}
							}
							case SDL_TEXTINPUT: {
								if (name.size() <= charLimit) {
									if (switcher) {
										name += event.text.text;
									}
								}
								switcher = !switcher;
								continue;
							}
							case SDL_WINDOWEVENT:
							{
								switch (event.window.event)
								{
								case SDL_WINDOWEVENT_CLOSE:
								{
									return 0;
								}
								}
							}
							}
						}

						textInputScreen.drawText("Enter Your Name (15 char max)", 10, 10, 20);
						textInputScreen.drawText(name.c_str(), 20, 40, 18);
						textInputScreen.present();
					}
					textInputScreen.show(false);
					SDL_StopTextInput();

					HS.name = name;
					HS.score = score;
					highscores.push_back(HS);
					sort(highscores);
					oFS.open(HSfile);
					if (!oFS.is_open()) {
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
							"Error",
							(HSfile + " was not found, please create the file in the root directory or reinstall the program").c_str(),
							NULL);
						return 1;
					}
					for (int j = 0; j < 5 && j < highscores.size(); j++) {
						oFS << highscores.at(j).name + " " + to_string(highscores.at(j).score) << endl;
					}
					oFS.close();
					break;
				}
			}

			endLoop = true;
			while (endLoop) {
				endScreen.drawText("High Scores", 110, 20, 35);
				for (int i = 0; i < 5 && i < highscores.size(); i++) {
					endScreen.drawText(highscores.at(i).name + ": " + to_string(highscores.at(i).score), 120, 60 + 27 * i, 25);
				}
				endScreen.draw(selectionBox, 255, 0, 0);
				endScreen.drawText("Play Again?", 110, 60 + 27 * 8, 30);
				endScreen.drawText("Yes", 120, 70 + 27 * 9, 25);
				endScreen.drawText("No", 210, 70 + 27 * 9, 25);

				if (SDL_PollEvent(&event) == 1)
				{
					switch (event.type)
					{
					case SDL_KEYDOWN:
					{
						switch (event.key.keysym.sym)
						{
						case SDLK_LEFT:
						{
							selectionBox.x = 115;
							playAgain = true;
							continue;
						}
						case SDLK_RIGHT:
						{
							selectionBox.x = 202;
							playAgain = false;
							continue;
						}
						case SDLK_RETURN:
						{
							endLoop = false;
							continue;
						}
						case SDLK_SPACE:
						{
							endLoop = false;
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
							return 0;
						}
						}
					}
					}					
				}
				endScreen.present();
				endScreen.clear();
			}
			if (playAgain) {
				gameRunning = true;
				score = 0;
				obj.reset();

				endScreen.show(false);
				window2.clear();
				window2.drawShape(obj.getNext());
				window2.present();
				window3.clear();

				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						for (int k = 0; k < 4; k++) {
							grid[j][i][k] = 0;
						}
					}
				}
			}
			else {
				return 0;
			}						
		}
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
void sort(vector<highScore>& v) {
	int index;
	highScore temp;
	for (int i = 0; i + 1 < v.size(); i++) {
		index = i;
		for (int j = i + 1; j < v.size(); j++) {
			if (v.at(index).score < v.at(j).score) {
				index = j;
			}
		}
		temp = v.at(i);
		v.at(i) = v.at(index);
		v.at(index) = temp;
	}
}