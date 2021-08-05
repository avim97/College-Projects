#ifndef _Q2_H
#define _Q2_H

#include "GeneralFunctions.h"

typedef struct _chessPosCell {
    chessPos position;
    struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList {
    chessPosCell* head;
    chessPosCell* tail;
}chessPosList;

void display(chessPosList* lst);

/* The following function fills the board according to the attached list */
void fillBoard(chessBoard board, chessPosList* lst);

/* The following function prints a characters' list (for monitoring) */
void printList(chessPosList* lst);

/* The following function prints the chess board */
void printBoard(chessBoard board);

/* The following function gets a position list and removes any reocurring cells */
void removeAllReoccurringCells(chessPosList* lst);

/* The following function gets a position and erases any other position with the same data.
 * The function returns the last Cell (to update the list's tail in case we erased it). */
chessPosCell* removeReoccurringCells(chessPosCell* currentPos);

/* The following function checks if the list is empty. if so it returns true, if not- false */
bool isEmptyList(chessPosList* lst);

/* The following function inserts a new node to the end of the list. */
void insertCellToEndList(chessPosList* lst, chessPosCell* newTail);

/* The following function inserts a new node to the start of the list. */
void insertCellToStartList(chessPosList* lst, chessPosCell* newHead);

/* The following function creates a new node which is going to be a tail. */
void insertPosDataToEndList(chessPosList* lst, chessPos pos);

/* The following function creates a new node which is going to be a head. */
void insertPosDataToStartList(chessPosList* lst, chessPos pos);

/* The following function frees the list and its data. */
void freeChessPosList(chessPosList* lst);

/* The following function sets an empty list. */
void makeEmptyList(chessPosList* lst);

/*Description: The following function creates a new list node. */
chessPosCell* createNewListNode(chessPos pos, chessPosCell* next);

#endif /* _Q2_H */
