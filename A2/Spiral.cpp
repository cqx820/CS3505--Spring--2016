/*
Author: Qixiang Chao
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "Spiral.h"
using namespace std;

Spiral::Spiral()
{
	centerX = 0;
	centerY = 0;
	start_angle = 0;
	start_radius = 0;
}

Spiral::Spiral(double _centerX, double _centerY, double _start_angle, double _start_radius)
{
    centerX = _centerX;
    centerY = _centerY;
    start_angle = _start_angle;
    start_radius = _start_radius;
}

Spiral& Spiral::operator++()
{	
	double rad = start_angle / 180 * M_PI;
	centerX = 210 + cos(rad) * start_radius;
	centerY = 300 + sin(rad) * start_radius;
	start_angle -= 10;
	start_radius += 8;
    return *this;
}

Spiral Spiral::operator++(int)
{
    Spiral temp = *this;
    ++*this;
    return temp;
}

ostream& operator<<(ostream& output, Spiral sp)
{
    output << "Center location is (" << sp.centerX << ", " << sp.centerY << ")" << ". The start agle is " << sp.start_angle << " and start radius is " << sp.start_radius << ".";
    return output;
}

double Spiral::get_text_x()
{
    return this->centerX;
}

double Spiral::get_text_y()
{
    return this->centerY;
}

double Spiral::get_spiral_angle()
{
    return this->start_angle;//start ang
}

double Spiral::get_text_angle()
{
	return this->start_angle;
}

double Spiral::get_CenterX()
{
	return this->centerX;
}

double Spiral::get_CenterY()
{
	return this->centerY;
}


