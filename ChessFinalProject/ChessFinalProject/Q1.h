#ifndef _Q1_H
#define _Q1_H
#include "GeneralFunctions.h"

#define MAX_POS 8

/* The following function calculates and returns the possible knight's moves from the knight's current position. */
chessPosArray*** validKnightMoves();

/* The following function inserts the possible knight positions of a specific square to its array.  */
chessPos* insertPositions(int* currSize, int row, int col);

/* The following function frees the chessPosArrays which were allocated. */
void freePosArrays(chessPosArray*** knightMoves);

/* This function is for monitoring for printing the valid knight moves */
void printValidKnightMoves(chessPosArray*** knightMoves);


#endif /* _Q1_H */