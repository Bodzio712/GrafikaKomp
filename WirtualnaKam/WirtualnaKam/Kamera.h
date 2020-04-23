#pragma once

const int szer = 220;
const int wys = 150;

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

class Prostokat
{
public:
	Prostokat(Punkt x1, Punkt x2, Punkt x3, Punkt x4)
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
	double x = 0;
	double y = 0;
	double z = 0;

	double ox = 0;
	double oy = 0;
	double oz = 0;

	double zoom = 1;
};

