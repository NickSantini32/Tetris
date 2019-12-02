#include "Shape.h"
#include "SDL.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "Window.h"
#include <math.h> 

using namespace std;

Shape::Shape()
{
	nextShape = rand() % 7;
	isDown = false;
	randomizeShape();
	savedShape = -1;
	swappable = true;
}
Shape::Shape(int t){
	nextShape = rand() % 7;
	type = t;
	isDown = false;
	buildDisplayShape();
	savedShape = -1;
	swappable = true;
}
bool Shape::moveDown(int grid[][10][4])
{
	if (!isDown)
	{
		for (int i = 0; i < 4; i++)
		{
			int height;
			for (int j = Y[i] / DIM; j < 20; j++)
			{
				if (grid[j][X[i] / DIM][0] == 1)
				{
					height = j;
					break;
				}
				if (j == 19)
				{
					height = j + 1;
				}
			}
			if (800 - (Y[i] + DIM) <= 800 - height * DIM)
			{				
				timeDown = std::chrono::high_resolution_clock::now();
				isDown = true;
				return true;
			}
		}	
		speedCounter += (float)simplNum/simplDenom;
		if (speedCounter >= 1)
		{
			int temp = 0;
			while (speedCounter >= 1)
			{
				speedCounter -=1;
				temp++;
			}
			for (int i = 0; i < 4; i++)
			{
				Y[i] += temp;
			}
			//std::cout << temp << std::endl;
		}	
	}
	else
	{		
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeDown).count() << std::endl;
		if	 (1000 < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeDown).count())
		{
			for (int j = 0; j < 4; j++)
			{
				int xGrid, yGrid;
				xGrid = X[j] / DIM;
				yGrid = ((int)Y[j]) / DIM;
				grid[yGrid][xGrid][0] = 1;
				for (int k = 0; k < 3; k++)
				{
					grid[yGrid][xGrid][k + 1] = color[k];
				}
			}
			randomizeShape();
			swappable = true;
			isDown = false;
			return false;
		}
		else
		{			
			for (int i = 0; i < 4; i++)
			{				
				if ((int)Y[i] / DIM + 1 == 20 || grid[(int)Y[i] / DIM + 1][X[i] / DIM][0] == 1)
				{
					return true;
				}
			}	
			isDown = false;
		}
	}
	return true;
}
void Shape::replaceShape(int t) {

}
void Shape::save(int grid[][10][4]){
	if (swappable) {
		if (savedShape == -1) {
			savedShape = type;
			randomizeShape();
		}
		else {
			int tempType = type;
			type = savedShape;
			savedShape = tempType;
			buildShape(false, X[0], Y[0], grid);
		}
	}	
//	std::cout << "saved: " << savedShape << std::endl;
//	std::cout << "current: " << type << std::endl;
}
Shape Shape::getSaved() {
	Shape shape(savedShape);
	return shape;
}
void Shape::buildDisplayShape() {
	int base;
	orientation = 0;
	switch (type)
	{
	case 0: // Square
	{
		base = 250/2 - DIM;
		color[0] = 240;
		color[1] = 240;
		color[2] = 0;

		X[0] = base;
		Y[0] = 220 / 2 - DIM/2;

		X[1] = base + DIM;
		Y[1] = 220 / 2 - DIM/2;

		X[2] = base;
		Y[2] = 220 / 2 + DIM/2;

		X[3] = base + DIM;
		Y[3] = 220 / 2 + DIM/2;
		break;
	}
	case 1: // T block
	{
		base = 250 / 2 - DIM * 1.5;
		color[0] = 160;
		color[1] = 0;
		color[2] = 240;

		X[0] = base;
		Y[0] = 220 / 2 - DIM / 2;

		X[1] = base + DIM;
		Y[1] = 220 / 2 - DIM / 2;

		X[2] = base + DIM * 2;
		Y[2] = 220 / 2 - DIM / 2;

		X[3] = base + DIM;
		Y[3] = 220 / 2 + DIM / 2;
		break;
	}
	case 2: // Line
	{
		base = 250 / 2 - DIM * 0.5;
		color[0] = 0;
		color[1] = 240;
		color[2] = 240;

		X[0] = base;
		Y[0] = 220 / 2 - DIM * 1.5;

		X[1] = base;
		Y[1] = 220 / 2 - DIM / 2;

		X[2] = base;
		Y[2] = 220 / 2 + DIM / 2;

		X[3] = base;
		Y[3] = 220 / 2 + DIM * 1.5;
		break;
	}
	case 3: // Z
	{
		base = 250 / 2 - DIM * 1.5;
		color[0] = 240;
		color[1] = 0;
		color[2] = 0;

		X[0] = base;
		Y[0] = 220 / 2 - DIM / 2;

		X[1] = base + DIM;
		Y[1] = 220 / 2 - DIM / 2;

		X[2] = base + DIM;
		Y[2] = 220 / 2 + DIM / 2;

		X[3] = base + DIM * 2;
		Y[3] = 220 / 2 + DIM / 2;
		break;
	}
	case 4: // Backwards Z
	{
		base = 250 / 2 - DIM * 0.5;
		color[0] = 0;
		color[1] = 240;
		color[2] = 0;

		X[0] = base;
		Y[0] = 220 / 2 + DIM / 2;

		X[1] = base + DIM;
		Y[1] = 220 / 2 + DIM / 2;

		X[2] = base + DIM;
		Y[2] = 220 / 2 - DIM / 2;

		X[3] = base + DIM * 2;
		Y[3] = 220 / 2 - DIM / 2;
		break;
	}
	case 5: // L
	{
		base = 250 / 2 - DIM;
		color[0] = 240;
		color[1] = 160;
		color[2] = 0;

		X[0] = base;
		Y[0] = 220 / 2 - DIM * 1.5;

		X[1] = base;
		Y[1] = 220 / 2 - DIM / 2;

		X[2] = base;
		Y[2] = 220 / 2 + DIM / 2;

		X[3] = base + DIM;
		Y[3] = 220 / 2 + DIM / 2;
		break;
	}
	case 6: // Backwards L
	{
		base = 250 / 2 - DIM;
		color[0] = 0;
		color[1] = 0;
		color[2] = 240;

		X[0] = base + DIM;
		Y[0] = 220 / 2 - DIM *1.5;

		X[1] = base + DIM;
		Y[1] = 220 / 2 - DIM / 2;

		X[2] = base + DIM;
		Y[2] = 220 / 2 + DIM /2;

		X[3] = base;
		Y[3] = 220 / 2 + DIM /2;
		break;
	}
	}
}
void Shape::addSpeed()
{
	speedNum++;
	simplNum = speedNum;
	simplDenom = speedDenom;
	if (speedNum % 8 == 0)
	{
	simplNum /= 8;
	simplDenom /= 8;
	}
	else if (speedNum % 4 == 0)
	{			
		simplNum /= 4;
		simplDenom /= 4;
	}
	else if (speedNum % 2 == 0)
	{
		simplNum /= 2;
		simplDenom /= 2;
	}
	//std::cout << speedNum << "/" << speedDenom << std::endl;
	//std::cout << simplNum << "/" << simplDenom << std::endl;
}
void Shape::moveRight(int grid[][10][4])
{
	for (int i = 0; i < 4; i++)
	{
		if (X[i] >= DIM * 9 || grid[(int)Y[i]/DIM][(X[i] / DIM) + 1][0] == 1)
		{
			return;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		X[i] += DIM;		
	}
}
void Shape::moveLeft(int grid[][10][4])
{
	for (int i = 0; i < 4; i++)
	{
		if (X[i] <= 0 || grid[(int)Y[i] / DIM][(X[i] / DIM) - 1][0] == 1)
		{
			return;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		X[i] -= DIM;
	}
}
void Shape::down(int grid[][10][4])
{
	if (isDown)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> x = std::chrono::time_point<std::chrono::high_resolution_clock>();
		timeDown = x;
	}
	else 
	{
		float distance[4];
		float finalDist;
		for (int i = 0; i < 4; i++)
		{
			for (int j = Y[i] / DIM; j < 20; j++)
			{
				if (grid[j][X[i] / DIM][0] == 1)
				{				
					distance[i] = j * DIM - Y[i];
					break;
				}
				else if(j == 19)
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
		for (int i = 0; i < 4; i++)
		{
			Y[i] += (int)finalDist - DIM;
		}
	}
}
void Shape::rotate(int grid[][10][4])
{
	int tempX[4];
	int tempY[4];
	int tempOrientation = orientation;

	for (int i = 0; i < 4; i++)
	{
		tempX[i] = X[i];
		tempY[i] = Y[i];
	}
	switch (type)
	{
		case 0: // Square
		{			
			break;
		}
		case 1: // T
		{					
			X[2] = X[3];
			Y[2] = Y[3];

			X[3] = X[0];
			Y[3] = Y[0];

			switch (orientation)
			{
				case 0:
				{
					X[0] = X[1];
					Y[0] = Y[1] - DIM;
					orientation = 1;
					break;
				}
				case 1:
				{
					X[0] = X[1] + DIM;
					Y[0] = Y[1];
					orientation = 2;
					break;
				}
				case 2:
				{
					X[0] = X[1];
					Y[0] = Y[1] + DIM;
					orientation = 3;
					break;
				}
				case 3:
				{
					X[0] = X[1] - DIM;
					Y[0] = Y[1];
					orientation = 0;
					break;
				}							
			}		
			break;
		}
		case 2: // Line
		{
			switch (orientation)
			{
				case 0:
				{
					Y[0] = Y[2];
					Y[1] = Y[2];
					Y[3] = Y[2];

					X[0] = X[2] - DIM;
					X[1] = X[2] + DIM;
					X[3] = X[2] + 2 * DIM;
					orientation = 1;
					break;
				}
				case 1:
				{
					X[0] = X[2];
					X[1] = X[2];
					X[3] = X[2];

					Y[0] = Y[2] - 2 * DIM;
					Y[1] = Y[2] - DIM;
					Y[3] = Y[2] + DIM;
					orientation = 0;
					break;
				}
			}
			break;
		}
		case 3: // Z
		{
			switch (orientation)
			{
				case 0:
				{
					X[0] += 2 * DIM;
					X[1] += DIM;
					X[3] -= DIM;

					Y[2] -= DIM;
					Y[0] -= DIM;
					orientation += 1;
					break;
				}
				case 1:
				{
					X[0] -= DIM;
					X[2] += DIM;
					X[3] += 2 * DIM;

					Y[2] += DIM;
					Y[0] += DIM;
					orientation -= 1;
					break;
				}				
			}		
			break;
		}
		case 4: // Backwards Z
		{
			switch (orientation)
			{
				case 0:
				{
					X[0] += 2 * DIM;
					X[1] += DIM;
					X[3] -= DIM;

					Y[2] -= DIM;
					Y[0] -= DIM;
					orientation += 1;
					break;
				}
				case 1:
				{
					X[0] -= DIM;
					X[2] += DIM;
					X[3] += 2 * DIM;

					Y[2] += DIM;
					Y[0] += DIM;
					orientation -= 1;
					break;
				}
			}
			break;
		}
		case 5: // L
		{
			switch (orientation)
			{
				case 0:
				{
					X[0] += DIM;
					X[2] -= DIM;
					X[3] -= 2 * DIM;

					Y[0] += DIM;
					Y[2] -= DIM;
					orientation += 1;
					break;
				}
				case 1:
				{
					X[0] -= DIM;
					X[2] += DIM;

					Y[0] += DIM;
					Y[2] -= DIM;
					Y[3] -= 2 * DIM;
					orientation += 1;
					break;
				}
				case 2:
				{
					X[0] -= DIM;
					X[2] += DIM;
					X[3] += 2 * DIM;

					Y[0] -= DIM;
					Y[2] += DIM;					
					orientation += 1;					
					break;
				}
				case 3:
				{
					X[0] += DIM;
					X[2] -= DIM;					

					Y[0] -= DIM;
					Y[2] += DIM;
					Y[3] += 2 * DIM;
					orientation = 0;
					break;
				}
			}
			
			break;
		}
		case 6: // Backwards L
		{
			switch (orientation)
			{
				case 0:
				{
					X[0] += DIM;
					X[2] -= DIM;					

					Y[0] += DIM;
					Y[2] -= DIM;
					Y[3] -= 2 * DIM;
					orientation += 1;
					break;
				}
				case 1:
				{
					X[0] -= DIM;
					X[2] += DIM;
					X[3] += 2 * DIM;

					Y[0] += DIM;
					Y[2] -= DIM;					
					orientation += 1;
					break;
				}
				case 2:
				{
					X[0] -= DIM;
					X[2] += DIM;					

					Y[0] -= DIM;
					Y[2] += DIM;
					Y[3] += 2 * DIM;
					orientation += 1;
					break;
				}
				case 3:
				{
					X[0] += DIM;
					X[2] -= DIM;

					Y[0] -= DIM;
					Y[2] += DIM;
					X[3] -= 2 * DIM;
					orientation = 0;
					break;
				}
			}
			break;
		}		
	}
	checkPos(tempOrientation, tempX, tempY, grid);
}
Shape Shape::getNext()
{
	Shape shape(nextShape);
	return shape;
}
void Shape::randomizeShape()
{
	srand(time(NULL));
	type = nextShape;
	nextShape = rand() % 7;
	buildShape(true, 0, 0, nullptr);	
}
void Shape::buildShape(bool isNew, int x, int y, int grid[][10][4])
{
	int baseX, baseY = 0;
	int tempX[4], tempY[4], tempColor[3];
	orientation = 0;
	if (!isNew) {
		for (int i = 0; i < 4; i++) {
			tempX[i] = X[i];
			tempY[i] = Y[i];
			if (i < 3) {
				tempColor[i] = color[i];
			}
		}
	}
	switch (type)
	{
		case 0: // Square
		{
			if (isNew)
				baseX = (rand() % 9) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
						
			color[0] = 240;
			color[1] = 240;
			color[2] = 0;

			X[0] = baseX;
			Y[0] = baseY;

			X[1] = baseX + DIM;
			Y[1] = baseY;

			X[2] = baseX;
			Y[2] = baseY + DIM;

			X[3] = baseX + DIM;
			Y[3] = baseY + DIM;
			break;
		}
		case 1: // T block
		{
			if (isNew)
				baseX = (rand() % 8) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			color[0] = 160;
			color[1] = 0;
			color[2] = 240;

			X[0] = baseX;
			Y[0] = baseY;

			X[1] = baseX + DIM;
			Y[1] = baseY;

			X[2] = baseX + DIM * 2;
			Y[2] = baseY;

			X[3] = baseX + DIM;
			Y[3] = baseY + DIM;
			break;
		}
		case 2: // Line
		{
			if (isNew)
				baseX = (rand() % 10) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			
			color[0] = 0;
			color[1] = 240;
			color[2] = 240;

			X[0] = baseX;
			Y[0] = baseY;

			X[1] = baseX;
			Y[1] = baseY + DIM;

			X[2] = baseX;
			Y[2] = baseY + 2 * DIM;

			X[3] = baseX;
			Y[3] = baseY + 3 * DIM;
			break;
		}
		case 3: // Z
		{
			if (isNew)
				baseX = (rand() % 8) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			color[0] = 240;
			color[1] = 0;
			color[2] = 0;

			X[0] = baseX;
			Y[0] = baseY;

			X[1] = baseX + DIM;
			Y[1] = baseY;

			X[2] = baseX + DIM;
			Y[2] = baseY + DIM;

			X[3] = baseX + DIM * 2;
			Y[3] = baseY + DIM;
			break;
		}
		case 4: // Backwards Z
		{
			if (isNew)
				baseX = (rand() % 8) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			color[0] = 0;
			color[1] = 240;
			color[2] = 0;

			X[0] = baseX;
			Y[0] = baseY +DIM;

			X[1] = baseX + DIM;
			Y[1] = baseY + DIM;

			X[2] = baseX + DIM;
			Y[2] = baseY;

			X[3] = baseX + DIM * 2;
			Y[3] = baseY;
			break;
		}
		case 5: // L
		{
			if (isNew)
				baseX = (rand() % 9) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			color[0] = 240;
			color[1] = 160;
			color[2] = 0;

			X[0] = baseX;
			Y[0] = baseY;

			X[1] = baseX;
			Y[1] = baseY + DIM;

			X[2] = baseX;
			Y[2] = baseY + 2 * DIM;

			X[3] = baseX + DIM;
			Y[3] = baseY + 2 * DIM;
			break;
		}
		case 6: // Backwards L
		{
			if (isNew)
				baseX = (rand() % 9) * DIM;
			else {
				baseX = x;
				baseY = y;
			}
			color[0] = 0;
			color[1] = 0;
			color[2] = 240;

			X[0] = baseX + DIM;
			Y[0] = baseY;

			X[1] = baseX + DIM;
			Y[1] = baseY + DIM;

			X[2] = baseX + DIM;
			Y[2] = baseY + 2 * DIM;

			X[3] = baseX;
			Y[3] = baseY + 2 * DIM;
			break;
		}
	}
	if (!isNew) {
		if (type == 6 || savedShape == 6) {
			for (int i = 0; i < 4; i++) {
				X[i] -= DIM;
			}
		}
		if (checkPos(orientation, tempX, tempY, grid)) {
			swappable = false;

		}
		else {
			swappable = true;
			for (int i = 0; i < 3; i++) {
				color[i] = tempColor[i];
			}
			int tempType = type;
			type = savedShape;
			savedShape = tempType;

		}
		/*for (int l = 0; l < 4; l++) //RESET
		{
			X[l] = tempX[l];
			Y[l] = tempY[l];
		}*/
	}
}
bool Shape::checkPos(int tempOrientation, int tempX[], int tempY[], int grid[][10][4]) {
	for (int i = 0; i < 4; i++) //(X[i] < 0 || grid[(int)Y[i] / DIM][(X[i] / DIM)] == 1 || X[i] > DIM * 9)
	{
		if (X[i] < 0) //IF TOO FAR LEFT
		{
			for (int j = 0; j < 4; j++) //MOVE 1 RIGHT
			{
				X[j] += DIM;
			}
			for (int j = 0; j < 4; j++)
			{
				if (grid[(int)Y[j] / DIM][(X[j] / DIM)][0] == 1) //IF INTERSECTS WITH GRID
				{
					for (int l = 0; l < 4; l++) //RESET
					{
						X[l] = tempX[l];
						Y[l] = tempY[l];
					}
					orientation = tempOrientation;
					std::cout << "could not rotate" << std::endl;
					return false;
				}
			}
		}
		else if (X[i] > DIM * 9) //IF TOO FAR RIGHT
		{
			for (int j = 0; j < 4; j++) //MOVE 1 LEFT
			{
				X[j] -= DIM;
			}
			for (int j = 0; j < 4; j++)
			{
				if (grid[(int)Y[j] / DIM][(X[j] / DIM)][0] == 1) //IF INTERSECTS WITH GRID
				{
					for (int l = 0; l < 4; l++) //RESET
					{
						X[l] = tempX[l];
						Y[l] = tempY[l];
					}
					orientation = tempOrientation;
					std::cout << "could not rotate" << std::endl;
					return false;
				}
			}
		}
		if (grid[(int)Y[i] / DIM][(X[i] / DIM)][0] == 1) //IF INTERSECTS WITH GRID LEFT/RIGHT
		{
			for (int j = 0; j < 4; j++) //MOVE 1 LEFT
			{
				X[j] -= DIM;
			}
			for (int j = 0; j < 4; j++)
			{
				if (X[j] < 0 || grid[(int)Y[j] / DIM][(X[j] / DIM)][0] == 1) //IF INTERSECTS WITH GRID OR TOO FAR LEFT
				{
					for (int l = 0; l < 4; l++) //RESET
					{
						X[l] = tempX[l];
						Y[l] = tempY[l];
					}
					for (int k = 0; k < 4; k++) //MOVE 1 RIGHT
					{
						X[k] += DIM;
					}
					for (int k = 0; k < 4; k++) 
					{
						if (X[k] > DIM * 9 || grid[(int)Y[k] / DIM][(X[k] / DIM)][0] == 1) //IF INTERSECTS WITH GRID OR TOO FAR RIGHT
						{
							for (int l = 0; l < 4; l++) //RESET
							{
								X[l] = tempX[l];
								Y[l] = tempY[l];
							}
							orientation = tempOrientation;
							std::cout << "could not rotate" << std::endl;
							return false;
						}
					}
				}
			}
		}
		if (Y[i] / DIM >= 20) //IF TOO FAR DOWN
		{
			for (int j = 0; j < 4; j++) //MOVE 1 UP
			{
				Y[j] -= DIM;
			}
			for (int j = 0; j < 4; j++)
			{
				if (grid[(int)Y[j] / DIM][(X[j] / DIM)][0] == 1) //IF INTERSECTS WITH GRID
				{
					for (int l = 0; l < 4; l++) //RESET
					{
						X[l] = tempX[l];
						Y[l] = tempY[l];
					}
					orientation = tempOrientation;
					std::cout << "could not rotate" << std::endl;
					return false;
				}
			}
		}
	}
	return true;
}
void Shape::reset() {
	nextShape = rand() % 7;
	isDown = false;
	randomizeShape();
	savedShape = -1;
	swappable = true;
}
