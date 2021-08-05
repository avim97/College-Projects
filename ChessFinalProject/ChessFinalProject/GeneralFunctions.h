#ifndef __GeneralFunctions_h
#define __GeneralFunctions_h

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8
#define SPACE 32
#define MAX_LST_SIZE SIZE*SIZE

typedef char chessPos[2];

typedef unsigned char BYTE;

typedef struct _chessPosArray {
    unsigned int size;
    chessPos* positions;
}chessPosArray;

typedef int chessBoard[SIZE][SIZE];

/* This function checks memory allocation */
void checkAllocation(void* ptr);

/* This function checks whether the file opened successfully*/
void checkFileOpening(FILE* file);


/* The following function receives a number and converts it to char. */
char intToChar(int num);

/* The following function receives a character and converts it to an integer. */
int charToInt(char ch);

#endif /* __GeneralFunctions_h */




 
