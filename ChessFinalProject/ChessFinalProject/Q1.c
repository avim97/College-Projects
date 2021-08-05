#include "Q1.h"


chessPosArray*** validKnightMoves()
{
    int i, j, currSize;
    chessPosArray*** knightMoves;

    /*allocation of the two-dims array and the pointers:*/

    knightMoves = (chessPosArray***)malloc(SIZE * sizeof(chessPosArray**));
    checkAllocation(knightMoves);

    for (i = 0; i < SIZE; i++)
    {
        knightMoves[i] = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
        checkAllocation(knightMoves[i]);
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            knightMoves[i][j] = (chessPosArray*)malloc(SIZE * sizeof(chessPosArray));
            checkAllocation(knightMoves[i][j]);
        }
    }
    /* going through the array, inserting the valid positions to the certain square's array*/
    for (i = 0; i < SIZE; i++)
    {
        for (currSize = 0, j = 0; j < SIZE; currSize = 0, j++)
        {
            knightMoves[i][j]->positions = insertPositions(&currSize, i, j);
            knightMoves[i][j]->size = currSize; /* updating its array's size accordingly */
        }
    }
    return knightMoves;
}

chessPos* insertPositions(int* currSize, int row, int col)
{
    chessPos* pos_array;
    pos_array = (chessPos*)malloc(MAX_POS * sizeof(chessPos));
    checkAllocation(pos_array);

    if (row - 2 >= 0)  /* checking for a possible position above the current square */
    {
        if (col + 1 <= SIZE - 1) /* above & right */
        {
            pos_array[*currSize][0] = intToChar(row - 2);
            pos_array[*currSize][1] = (char)(col + 1 + '1');
            (*currSize)++;
        }

        if (col - 1 >= 0) /* above & left */
        {
            pos_array[*currSize][0] = intToChar(row - 2);
            pos_array[*currSize][1] = (char)(col - 1 + '1');
            (*currSize)++;
        }
    }

    if (row + 2 <= SIZE - 1) /* checking for a possible position beneath the current square */
    {
        if (col + 1 <= SIZE - 1) /* below & right */
        {
            pos_array[*currSize][0] = intToChar(row + 2);
            pos_array[*currSize][1] = (char)(col + 1 + '1');
            (*currSize)++;
        }

        if (col - 1 >= 0) /* below & left */
        {
            pos_array[*currSize][0] = intToChar(row + 2);
            pos_array[*currSize][1] = (char)(col - 1 + '1');
            (*currSize)++;
        }
    }

    if (col - 2 >= 0) /* checking for a possible position on the left side of the current square */
    {
        if (row + 1 <= SIZE - 1) /* left & below */
        {
            pos_array[*currSize][0] = intToChar(row + 1);
            pos_array[*currSize][1] = (char)(col - 2 + '1');
            (*currSize)++;
        }

        if (row - 1 >= 0) /* left & above */
        {
            pos_array[*currSize][0] = intToChar(row - 1);
            pos_array[*currSize][1] = (char)(col - 2 + '1');
            (*currSize)++;
        }
    }

    if (col + 2 <= SIZE - 1) /* checking for a possible position on the right side of the current square */
    {
        if (row + 1 <= SIZE - 1) /* right & below */
        {
            pos_array[*currSize][0] = intToChar(row + 1);
            pos_array[*currSize][1] = (char)(col + 2 + '1');
            (*currSize)++;
        }

        if (row - 1 >= 0) /* right & above */
        {
            pos_array[*currSize][0] = intToChar(row - 1);
            pos_array[*currSize][1] = (char)(col + 2 + '1');
            (*currSize)++;
        }
    }

    pos_array = (chessPos*)realloc(pos_array, ((*currSize) * sizeof(chessPos)));
    checkAllocation(pos_array);

    return pos_array;
}

void freePosArrays(chessPosArray*** knightMoves)
{
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            free(knightMoves[i][j]->positions);
        }
        free(knightMoves[i]);
    }
    free(knightMoves);
}

void printValidKnightMoves(chessPosArray*** knightMoves)
{
    int i, j, t, si;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("current square: (%c:%d) \nIts possible knight moves:\n", intToChar(i), (j + 1));
            si = knightMoves[i][j]->size;
            for (t = 0; t < si;t++)
                printf("(%c,%c)   ", knightMoves[i][j]->positions[t][0], knightMoves[i][j]->positions[t][1]);
            printf("\n\n");
        }
    }
}

