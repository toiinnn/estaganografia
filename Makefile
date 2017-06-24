all:
	gcc lerImagemPPM.c -c
	gcc lerImagemBMP.c -c
	gcc main.c lerImagemPPM.o lerImagemBMP.o -o steg
