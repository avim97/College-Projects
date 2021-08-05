#include "Q5.h"


void saveListToBinFile (char *file_name, chessPosList *pos_list)
{
    int bitsRemainder = 0;
    short int len = countPositions(pos_list);
    BYTE buffer = 0, rowMask, colMask, nextMask, reminder1Mask;
    chessPosCell *curr = pos_list->head;

    FILE *file = fopen(file_name, "wb");
    checkFileOpening(file);

    fwrite(&len, sizeof(short int), 1, file);
    fflush(file);

    while (curr != NULL)
    {
        if (bitsRemainder % 3 == 0)
        {
            rowMask = (BYTE)(curr->position[0] - 'A');
            rowMask  = rowMask << 5;
            colMask = (BYTE)(curr->position [1] - '1');
            colMask = colMask << 2;

            buffer = buffer | rowMask;
            buffer = buffer | colMask;

            if (curr->next != NULL)
            {
                nextMask = (BYTE)(curr->next->position[0] - 'A');
                nextMask = nextMask >> 1;
                buffer = buffer | nextMask;
            }

            fwrite(&buffer, sizeof(BYTE), 1, file);
            bitsRemainder++;
            fflush(file);
            buffer = 0;
        }

        else if (bitsRemainder % 3 == 1)
        {
            rowMask = (BYTE)(curr->position[0] - 'A');
            rowMask = rowMask << 7;
            colMask = (BYTE)(curr->position [1] - '1');
            colMask = colMask << 4;

            buffer = buffer | rowMask;
            buffer = buffer | colMask;

            if (curr->next != NULL)
            {
                nextMask = (BYTE)(curr->next->position[0] - 'A'); /* row*/
                nextMask = nextMask << 1;
                buffer = buffer | nextMask;
                nextMask = (BYTE)(curr->next->position[1] - '1'); /* col*/
                nextMask = nextMask >> 2;
                buffer = buffer | nextMask;

                fwrite(&buffer, sizeof(BYTE), 1, file);
                bitsRemainder++;
                fflush(file);
                buffer = 0;
            }
        }
        else /* when (bitsRemainder % 3) == 2 */
        {
            colMask =(BYTE)(curr->position [1] - '1');
            colMask = colMask << 6;

            buffer = buffer | colMask;

            if (curr->next != NULL)
            {
                nextMask = (BYTE)(curr->next->position[0] - 'A'); /* row */
                nextMask = nextMask << 3;
                buffer = buffer | nextMask;
                nextMask = (BYTE)(curr->next->position[1] - '1'); /* col */
                buffer = buffer | nextMask;
                curr = curr->next;
            }
            fwrite(&buffer, sizeof(BYTE), 1, file);
            bitsRemainder++;
            fflush(file);
            buffer = 0;
        }

        curr = curr->next;
    }

    fclose(file);
}

short int countPositions (chessPosList *pos_list)
{
    short int res = 0;
    chessPosCell *curr = pos_list->head;

    while (curr != NULL)
    {
        res++;
        curr = curr->next;
    }

    return res;

}
