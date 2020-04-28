#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define Prostokat Czworokat

class Punkt2D
{
public:
	Punkt2D(double ix, double iy)
	{
		x = ix;
		y = iy;
	};
public:
	double x;
	double y;
};

class Punkt
{
public:
	Punkt() {};
	Punkt(double ix, double iy, double iz)
	{
		x = ix;
		y = iy;
		z = iz;
	};
public:
	double x;
	double y;
	double z;
};

class Czworokat
{
public:
	Czworokat(Punkt x1, Punkt x2, Punkt x3, Punkt x4)
		: w1(x1)
		, w2(x2)
		, w3(x3)
		, w4(x4)
	{
	};
public:
	Punkt w1, w2, w3, w4;
};

class Kamera
{
public:
	Punkt2D ObliczPozycjePunktu(Punkt p);

public:
	int szer = 1800;
	int wys = 1000;

	double x = 0;
	double y = 0;
	double z = 0;

	double ox = 0;
	double oy = 0;
	double oz = M_PI;

	double zoom = 1.01;

public:
	void RuchX(double krok);
	void RuchY(double krok);
	void RuchZ(double krok);

	void ObrotOX(double krok);
	void ObrotOY(double krok);
	void ObrotOZ(double krok);

	void Zoom(double ktok);
};
