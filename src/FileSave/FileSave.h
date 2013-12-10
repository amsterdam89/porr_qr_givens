/*
 * FileSave.h
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#ifndef FILESAVE_H_
#define FILESAVE_H_

#include <stdio.h>
#include "../bool.h"

extern int NUM_PROCS;
extern int SIZE;

bool saveData(char *path, double timeA, double timeB);

#endif /* FILESAVE_H_ */
