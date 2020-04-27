#include "pch.h"
#include "Kamera.h"


/////////////////////////////////////////////////////////////////////////////
// Translacja o wektor
void Kamera::RuchX(double krok)
{
	double cosy = cos(-this->oy);
	double siny = sin(-this->oy);

	double nx = (-siny * krok);
	double nz = (cosy * krok);

	x += nx;
	z += nz;
}

void Kamera::RuchZ(double krok)
{
	double cosy = cos(-this->oy);
	double siny = sin(-this->oy);

	double nx = (cosy * krok);
	double nz = (siny * krok);

	x += nx;
	z += nz;
}

void Kamera::RuchY(double krok)
{
	y += krok;
}

/////////////////////////////////////////////////////////////////////////////
// Obroty
void Kamera::ObrotOX(double krok)
{
	this->ox += krok;
}

void Kamera::ObrotOY(double krok)
{
	this->oy += krok;
}

void Kamera::ObrotOZ(double krok)
{
	this->oz += krok;
}

/////////////////////////////////////////////////////////////////////////////
// Obliczenia pomocnicze
Punkt2D Kamera::ObliczPozycjePunktu(Punkt p)
{
	double dx = p.x - x;
	double dy = p.y - y;
	double dz = p.z - z;

	double sinx = sin(ox);
	double siny = sin(oy);
	double sinz = sin(oz);

	double cosx = cos(ox);
	double cosy = cos(oy);
	double cosz = cos(oz);

	double tempx = (cosy * (sinz * (dy)+cosz * (dx)) - siny * (dz));
	double tempy = (sinx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) + cosx * (cosz * (dy)-sinz * (dx)));
	double tempz = (cosx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) - sinx * (cosz * (dy)-sinz * (dx)));

	double resx = (((tempx) * (zoom / tempz)) * (wys / 2)) + (szer / 2);
	double resy = (((tempy) * (zoom / tempz)) * (wys / 2)) + (wys / 2);

	return Punkt2D(resx, resy);
}
