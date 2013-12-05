/*
 * FileReader.h
 *
 *  Created on: Nov 22, 2013
 *      Author: amsterdam
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <stdio.h>
#include "../MatrixOperation/matrixOperation.h"
#include "../bool.h"

extern int SIZE;

bool loadArguments(int argc, char *argv[], char *path, char *name);
bool loadData(char *path, double ***A);
void setMatrix(FILE *f, double ***A);


#endif /* FILEREADER_H_ */
