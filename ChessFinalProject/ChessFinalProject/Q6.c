#include "Q6.h"

int checkAndDisplayFileFromFile(char* file_name)
{
    chessPosList* lst;
    int count = 0, bitsRemainder = 0, iterations;
    short int len;
    BYTE buffer = 0, rowMask, colMask, nextMask;
    chessPos temp;

    lst = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocation(lst);
    makeEmptyList(lst);

    FILE* file = fopen(file_name, "rb");
    if (file == NULL)
        return NOT_FOUND;

    fread(&len, sizeof(short int), 1, file);

    if ((len * POS_BITS) % 8 == 0)
        iterations = (len * POS_BITS) / 8;
    else
        iterations = ((len * POS_BITS) / 8) + 1;

    while (count < iterations)
    {
        count++;
        fread(&buffer, sizeof(BYTE), 1, file);

        if (bitsRemainder % 3 == 0)
        {
            rowMask = 0xE0;
            rowMask = buffer & rowMask;
            rowMask = rowMask >> 5;
            temp[0] = (char)(rowMask) + 'A';

            colMask = 0x1C;
            colMask = buffer & colMask;
            colMask = colMask >> 2;
            temp[1] = (char)(colMask) + '1';
            insertPosDataToEndList(lst, temp);

            nextMask = 0x03;
            nextMask = buffer & nextMask;
            nextMask = nextMask << 1;
        }

        else if (bitsRemainder % 3 == 1)
        {
            rowMask = 0x80;
            rowMask = buffer & rowMask;
            rowMask = rowMask >> 7;
            rowMask = nextMask | rowMask;
            temp[0] = (rowMask) + 'A';

            colMask = 0x70;
            colMask = buffer & colMask;
            colMask = colMask >> 4;
            temp[1] = (colMask) + '1';
            insertPosDataToEndList(lst, temp);

            rowMask = 0x0E;
            rowMask = buffer & rowMask;
            rowMask = rowMask >> 1;
            nextMask = 0x01;
            nextMask = nextMask & buffer;
            nextMask = nextMask << 2;
        }
        else
        {
            temp[0] = (rowMask) + 'A';

            colMask = 0xC0;
            colMask = buffer & colMask;
            colMask = colMask >> 6;
            colMask = colMask | nextMask;
            temp[1] = (colMask) + '1';

            insertPosDataToEndList(lst,temp);

            if(len - count > 0)
            {
                rowMask = 0x38;
                rowMask = rowMask & buffer;
                rowMask = rowMask >> 3;
                temp[0]= (rowMask) + 'A';

                colMask = 0x7;
                colMask = buffer & colMask;
                temp[1] = (colMask) + '1';

                insertPosDataToEndList(lst, temp);
            }
        }
        bitsRemainder++;
    }

    fclose(file);

    if (!isValidPath(lst))
    {
        freeChessPosList(lst);
        return INVALID_PATH;
    }

    display(lst); /*the display function removes reoccurring positions*/

    len = countPositions(lst);
    freeChessPosList(lst);

    if (len < MAX_LST_SIZE) /*that way we know for sure this path is not covering all of the board*/
    {
        return PATH_NOT_COVERING_ALL_BOARD;
    }
    else /* in this scenario we know for sure that the list covers all board because len == MAX_LST_SIZE*/
        return PATH_COVERING_ALL_BOARD;

}

bool isValidPath (chessPosList* lst)
{
    bool res = true;

    if (lst == NULL)
        return res;
    else
    if (lst->head -> next == NULL)
        return res;

    chessPosArray*** possibleMoves = validKnightMoves();
    chessPosCell *pos = lst->head;
    unsigned int tempSize, i;

    while (pos->next != NULL && res == true)
    {
        res = false;
        tempSize = possibleMoves[charToInt(pos->position[0])][charToInt(pos->position[1])]->size;

        for(i = 0 ; i < tempSize ; i++)
        {
            if(possibleMoves[charToInt(pos->position[0])][charToInt(pos->position[1])] -> positions[i][0] == pos->next->position[0])
                if (possibleMoves[charToInt(pos->position[0])][charToInt(pos->position[1])] -> positions[i][1] == pos->next->position[1])
                {
                    res = true;
                    break;
                }
        }
        pos = pos->next;
    }

    freePosArrays(possibleMoves);

    return res;
}

