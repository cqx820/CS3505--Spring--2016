/*
Author: Qixiang Chao
*/

#include "hpdf.h"
#include <iostream>
using namespace std;
class HaruPDF
{
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    char fname[256]; // char *fname;

public:
    HaruPDF();
	~HaruPDF();
    void setFileName(char *_fname);
    void HPDF_Page_SetTextMatrix(HPDF_REAL a, HPDF_REAL b, HPDF_REAL c, HPDF_REAL d, HPDF_REAL x, HPDF_REAL y);
    void HPDF_Page_ShowText(const char *text);
};
