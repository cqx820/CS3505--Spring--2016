CC = g++
CFLAGS = -Wall -std=c++11

HARULIBDIR = libharu-RELEASE_2_3_0/src
HARULIBINCLUDE = libharu-RELEASE_2_3_0/include

pdfTest : $(HARULIBDIR)/libhpdfs.a spiralPDF.o Spiral.o HaruPDF.o
	$(CC) $(CFLAGS) -o pdfTest spiralPDF.o Spiral.o HaruPDF.o -L$(HARULIBDIR) -lhpdfs -lz


HaruPDF.o : $(HARULIBINCLUDE)/hpdf.h HaruPDF.h HaruPDF.cpp
	$(CC) $(CFLAGS) -c -I$(HARULIBINCLUDE) HaruPDF.cpp


spiralPDF.o : spiralPDF.cpp HaruPDF.h Spiral.h
	$(CC) $(CFLAGS) -c -I$(HARULIBINCLUDE) spiralPDF.cpp


Spiral.o : Spiral.h Spiral.cpp
	$(CC) $(CFLAGS) -c -I$(HARULIBINCLUDE) Spiral.cpp

clean:
	rm pdfTest *.o

test:
	./pdfTest "This is my sample text"
