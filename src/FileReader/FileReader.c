/*
 * FileReader.c
 *
 *  Created on: Nov 22, 2013
 *      Author: amsterdam
 */
#include "FileReader.h"


bool loadArguments(int argc, char *argv[], char *path, char *name){

	if(argc == 1) {
		printf("wywolanie algorytmu z niepoprawnymi flagami.\n");
		printf("przyklady wywolania:\n porr.exe data.dat\n porr.exe data.dat wyniki.dat\n");
		return false;
	}
	else if(argc >=2) {
		if(argc == 2) {
			path = argv[1];
			name = "wynik.dat";
			return true;
		}
		else {
			path = argv[1];
			name = argv[2];
			return true;
		}
	}
	else {
			printf("blad, zle argumenty.\n");
			return false;
	}

}

bool loadData(char *path, double ***A) {

	FILE *f;

	f = fopen(path, "r");

	if(f == NULL ) {
		fprintf(stderr,"Error:Unable to open %s\n", (char *) f);
		return false;
	}

	fscanf(f, "%d", &M);
	fscanf(f, " %d\n", &N);

	mallocMatrix(A);
	setMatrix(f,A);

    fclose(f);

    return true;
}

void setMatrix(FILE *f, double ***A) {
	int i , j;

	for(i=0; i<M; i++)
		for(j=0; j<N; j++) {
			fscanf(f, " %lf", &(*A)[i][j]);
			//printf("wartosc macierzy = %f\n", (*A)[i][j]);
		}

}


