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
	double previous_x, previous_y, present_x, present_y, t;
	std::string function;

	std::cout << "f(z)=";
	std::cin >> function;
	FunctionParser fp;
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	fp.Parse(function, "z");

	for (t = 0; t < 8 * atan(1) - 0.005; t = t + 0.005) {
		double cost = cos(t), sint = sin(t), costa = cos(t + 0.005), sinta = sin(t + 0.005);
		previous_x = fp.Eval(&cost);
		previous_y = fp.Eval(&sint);
		present_x = fp.Eval(&costa);
		present_y = fp.Eval(&sinta);
		DrawLine(imageReference->image, previous_x, previous_y, present_x, present_y, 2, GetGray(0.3));
	}
	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "main.png");
	DeleteImage(imageReference->image);
	return 0;
}