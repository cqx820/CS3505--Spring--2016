/*
Author: Qixiang Chao
*/

#include <iostream>
using namespace std;

class Spiral
{
    double centerX, centerY, start_angle, start_radius;
public:
	Spiral();
    Spiral(double _centerX, double _centerY, double _start_angle, double _start_radius);
    Spiral& operator++();
    Spiral operator++(int);
    double get_text_x();
    double get_text_y();
    double get_spiral_angle();
    double get_text_angle();
	double get_CenterX();
	double get_CenterY();
    friend ostream& operator<<(ostream& output, Spiral sp);
};
