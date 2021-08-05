#define _CRT_SECURE_NO_WARNINGS

#ifndef _Q7_H
#define _Q7_H

#include "GeneralFunctions.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"
#include "Q7.h"

#define EMPTY 'T'

/* This function is the gameplay function */
void gamePlay();

/* This function prints chess logo */
void printLogo();

/* This function prints the menu and returns the choice of the user*/
void printMenu(int* userChoice);

/* This function checks is the cell chosen by the user is valid and returns a boolean value */
bool isValidCell(chessPos cell);

/* this functions receives a position from the user and checks if the position is valid */
void getPosition (chessPos *pos);

/* This function receives a file name from the user */
char* getFileName ();

/* This function check if the list and path are not null and if they aren't, it frees them */
void emptyListAndTree (chessPosList *lst, pathTree* path);

/* This function prints an announcement to the user according to the value received by the function checkAndDisplayFileFromFile in Q6 */
void userAnnouncement (int value);


#endif /* _Q7_H */