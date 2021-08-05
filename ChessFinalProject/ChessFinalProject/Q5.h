#ifndef _Q5_H
#define _Q5_H

#include "Q2.h"
#include "GeneralFunctions.h"

/* This function gets a name of binary file and a positions list and saves the length
 * of the list and the positions themselves binarily */
void saveListToBinFile (char *file_name, chessPosList *pos_list);

/* This function returns the length of the list */
short int countPositions (chessPosList *pos_list);


#endif /* _Q5_H */