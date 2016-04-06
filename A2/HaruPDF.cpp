/*
Author: Qixiang Chao
*/

#include "hpdf.h"
#include "HaruPDF.h"
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;

HaruPDF::HaruPDF()
{
    pdf = HPDF_New(NULL, NULL);
    page = HPDF_AddPage(pdf);
	HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
    font = HPDF_GetFont(pdf, "Helvetica", NULL); 
    HPDF_Page_SetTextLeading(page, 20);
    HPDF_Page_SetGrayStroke(page, 0);
    HPDF_Page_BeginText(page);
    font = HPDF_GetFont(pdf, "Courier-Bold", NULL);
    HPDF_Page_SetFontAndSize(page, font, 30);
}

HaruPDF::~HaruPDF()
{
	HPDF_Page_EndText(page);
	HPDF_SaveToFile(pdf, fname);
	HPDF_Free(pdf);
}

void HaruPDF::setFileName(char* _fname)
{
    strcpy(fname, _fname);
    strcat(fname, ".pdf");
}

void HaruPDF::HPDF_Page_SetTextMatrix(HPDF_REAL a, HPDF_REAL b, HPDF_REAL c, HPDF_REAL d, HPDF_REAL x, HPDF_REAL y)
{
    ::HPDF_Page_SetTextMatrix(page, a, b, c, d, x, y);
}

void HaruPDF::HPDF_Page_ShowText(const char* text)
{
    ::HPDF_Page_ShowText(page, text);
}

