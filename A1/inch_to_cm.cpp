
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

double convertInchToCm(double inches);
void niceOutput(double cm);
/*
  Author: Qixiang Chao
  Brife Description: This program I used four library classes and a namespace.
  I followed the requirement of the assignment, so I created two helper methods
  and made the forward declaration. I have tested this code by passing a data
  file and generate a result file after the test. The command lines have been
  included in the written assignment.
 */
int main()
{
	string input;
	double inches, cm;
	while (std::getline(std::cin, input))
	{
		//if (input == " ")
		//{
		//	continue;
		//}
		istringstream integer(input);
	    while ((integer >> inches))
		{
			cm = convertInchToCm(inches);
			niceOutput(cm);
		}
	}
	return 0;
}

double convertInchToCm(double inches)
{
	return inches * 2.54;
}

void niceOutput(double cm)
{
	cout << fixed << setprecision(2) << cm << endl;
}

