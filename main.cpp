#include <iostream>
#include <cmath>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <../fparser.hh>
#include <vector>
#include <complex>
#include <math.h>
#define _USE_MATH_DEFINES

int main()
{
	const int x0 = 0, y0 = 0, r = 1;
	const double pi = 4 * atan(1), dt = 0.005;
	bool success;
	std::string function;
	std::vector<double>xs;
	std::vector<double>ys;

	std::cout << "f(z)=";
	std::cin >> function;
	FunctionParser_cd fp;
	fp.Parse(function, "z");

	for (double t = 0; t < 2 * pi; t += dt){
		std::complex<double>z=(x0 + r * cos(t), y0 + r * sin(t));
		std::complex<double>f = fp.Eval(&z);
		xs.push_back(f.real());
		ys.push_back(f.imag());
	}

	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	DrawScatterPlot(imageReference, 1000, 1000, &xs, &ys, errorMessage);
	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "main.png");
	DeleteImage(imageReference->image);

	return 0;
}	