#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define Prostokat Czworokat

class Punkt2D
{
public:
	Punkt2D(double ix, double iy, double iz)
	{
		x = ix;
		y = iy;
		odl = iz;
	};
public:
	double x;
	double y;
	double odl;
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
	int wys = 1200;

	double x = 0;
	double y = 0;
	double z = -100;

	double ox = 0;
	double oy = 0;
	double oz = 0;//M_PI;

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

class Poligon
{
public:
	Poligon(const POINT* p, double o)
		: punkty(p)
		, odl(o)
	{
	};

public:
	const POINT* punkty;
	double odl;
};