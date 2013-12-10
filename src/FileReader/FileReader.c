/*
 * FileReader.c
 *
 *  Created on: Nov 22, 2013
 *      Author: amsterdam
 */
#include "FileReader.h"


bool loadArguments(int argc, char *argv[], char **path, char **name){

	if(argc <= 2) {
		printf("wywolanie algorytmu z niepoprawnymi flagami.\n");
		printf("przyklady wywolania:\n porr.exe 8 data.dat\n porr.exe 8 data.dat wyniki.dat\n");
		printf("pierwszy argument to: liczba rdzenie procesora\ndrugi argument to: plik z testowa macierza\ntrzeci argument( opcjonalny, w przypadku nie podania wyniki zostana zapisane do wyniki.dat) to: plik do zapisu wyników\n");
		return false;
	}
	else if(argc >=3) {
		if(argc == 3) {
			NUM_PROCS = atoi(argv[1]);
			*path = argv[2];
			*name = "wynik.dat";
			return true;
		}
		else {
			NUM_PROCS = atoi(argv[1]);
			*path = argv[2];
			*name = argv[3];
			return true;
		}
	}
	else {
			printf("blad, zle argumenty.\n");
			return false;
	}

}

bool loadData(char *path, double ***A) {
	/*
	 * plik przykladowy
	 *
	 * 4
	 * 11 12 13 14
	 * 21 22 23 24
	 * 31 32 33 34
	 * 41 42 43 44
	 */

	FILE *f;

	f = fopen(path, "r");

	if(f == NULL ) {
		fprintf(stderr,"Error:Unable to open %s\n", (char *) f);
		return false;
	}

	fscanf(f, "%d", &SIZE);

	mallocMatrix(A);
	setMatrix(f,A);
    fclose(f);

    return true;
}

void setMatrix(FILE *f, double ***A) {
	int i , j;

	for(i=0; i<SIZE; i++) //wiersze
		for(j=0; j<SIZE; j++) //kolumny
			fscanf(f, " %lf", &(*A)[i][j]);


}


