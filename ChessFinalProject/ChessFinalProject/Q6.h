#ifndef _Q6_H
#define _Q6_H

#include "GeneralFunctions.h"
#include "Q1.h"
#include "Q2.h"
#include "Q5.h"
#include "Q3.h"

#define POS_BITS 6
#define INVALID_PATH 1
#define PATH_COVERING_ALL_BOARD 2
#define PATH_NOT_COVERING_ALL_BOARD 3
#define NOT_FOUND -1

/* This function gets a name of binary file containing a number of positions, then the positions themselves binarily.
 * This function creates a positions list and returns a number:
 * if the list represents invalid path the function returns 1
 * Otherwise, the function removes reocurring positions from the list and displays it.
 * It returns 2 if that path covers all the board, if not - 3. */
int checkAndDisplayFileFromFile(char *file_name);

/* This function determines whether a path is valid */
bool isValidPath (chessPosList* lst);

#endif /* _Q6_h */ 