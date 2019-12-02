#ifndef SHAPE_H
#define SHAPE_H
#pragma once
#include "SDL.h"
#include <chrono>

class Shape
{
private:	
	static const int DIM = 40;

	int speedNum = 2;
	int speedDenom = 8;
	float speedCounter = 0;
	int simplNum = 1;
	int simplDenom = 4;
	int type;
	int orientation;
	int X[4];
	int Y[4];
	int color[3];
	int nextShape;
	int savedShape;
	bool swappable;
	std::chrono::time_point<std::chrono::steady_clock> timeDown;
	bool isDown;

	void randomizeShape();
	void buildShape(bool, int, int, int grid[][10][4]);
	void buildDisplayShape();
	bool checkPos(int tempOrientation, int tempX[], int tempY[], int grid[][10][4]);
	void replaceShape(int t);
	Shape(int t);

public:
	Shape();
	static inline int getDim() { return DIM; };
	inline int* getY() { return Y; };
	inline int* getX() { return X; };
	inline int* getColor() { return color; };
	inline int getType() { return type; };
	void addSpeed();
	void reset();

	bool moveDown(int grid[][10][4]);
	void save(int grid[][10][4]);
	void moveRight(int grid[][10][4]);
	void moveLeft(int grid[][10][4]);
	void rotate(int grid[][10][4]);
	void down(int grid[][10][4]);
	Shape getNext();
	Shape getSaved();
};
#endif
