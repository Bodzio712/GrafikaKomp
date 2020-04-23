#include "pch.h"
#include "Kamera.h"

Punkt2D Kamera::ObliczPozycjePunktu(Punkt p)
{
	double dx = p.x - x;
	double dy = p.y - y;
	double dz = p.z - z;

	double sinx = sin(x);
	double siny = sin(y);
	double sinz = sin(z);

	double cosx = cos(x);
	double cosy = cos(y);
	double cosz = cos(z);

	double tempx = (cosy * (sinz * (dy)+cosz * (dx)) - siny * (dz));
	double tempy = (sinx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) + cosx * (cosz * (dy)-sinz * (dx)));
	double tempz = (cosx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) - sinx * (cosz * (dy)-sinz * (dx)));

	double resx = (((tempx) * (zoom / tempz)) * (wys / 2)) + (szer / 2);
	double resy = (((tempy) * (zoom / tempz)) * (wys / 2)) + (wys / 2);

	return Punkt2D(resx, resy);
}

////Obliczanie dystansu kamera-punkt
//var dx = this.position.x - c.position.x;
//var dy = this.position.y - c.position.y;
//var dz = this.position.z - c.position.z;

//Obliczanie wart. funkcji trygonometrycznych do dalszych obliczeñ
//var cosx = Math.cos(c.rotation.x);
//var cosy = Math.cos(c.rotation.y);
//var cosz = Math.cos(c.rotation.z);
//var sinx = Math.sin(c.rotation.x);
//var siny = Math.sin(c.rotation.y);
//var sinz = Math.sin(c.rotation.z);

//Obliczanie pozycji punktów przed uwzglednieniem zoomu
//var nx = (cosy * (sinz * (dy)+cosz * (dx)) - siny * (dz));
//var ny = (sinx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) + cosx * (cosz * (dy)-sinz * (dx)));
//var nz = (cosx * (cosy * (dz)+siny * (sinz * (dy)+cosz * (dx))) - sinx * (cosz * (dy)-sinz * (dx)));
//


//Zwracanie pozycji punktu
//return {
//	x: (((nx) * (c.zoom / nz)) * (screen.height / 2)) + (screen.width / 2),
//	y : (((ny) * (c.zoom / nz)) * (screen.height / 2)) + (screen.height / 2),
//	distance : nz