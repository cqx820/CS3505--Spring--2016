/*
Author: Qixiang Chao
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Spiral.h"
#include "HaruPDF.h"
//#include "hpdf.h"
#include <cstdio>
#include <sstream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
    if(argc < 1)
    {
        cout << "No input found, please enter valid input" << endl;
        return EXIT_FAILURE;
    }
    float rad1;
	unsigned int i;
    HaruPDF haru = HaruPDF();
    haru.setFileName("spiralPDF");
    Spiral sp = Spiral(200, 200, 180, 30);
    for (i = 0; i < strlen(argv[1]); i++) {
        char buf[2];
		rad1 = (sp.get_text_angle() - 90) / 180 * M_PI;	
		sp++;				
        haru.HPDF_Page_SetTextMatrix(cos(rad1), sin(rad1), -sin(rad1), cos(rad1), sp.get_text_x(), sp.get_text_y());		
        buf[0] = argv[1][i];
        buf[1] = 0;
        haru.HPDF_Page_ShowText(buf); 
    }
    return 0;
}
