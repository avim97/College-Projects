#include "Q2.h"

void display(chessPosList* lst)
{
    chessBoard board = { 0 };

    removeAllReoccurringCells(lst);

    fillBoard(board, lst); /*filling the board according to lst*/

    printBoard(board);
}

void fillBoard(chessBoard board, chessPosList* lst)
{
    chessPosCell* curr = lst->head;
    int row, col, ind = 1;

    while (curr != NULL)
    {
        row = charToInt(curr->position[0]);
        col = charToInt(curr->position[1]);
        board[row][col] = ind;
        ind++;
        curr = curr->next;
    }
}

void printBoard(chessBoard board)
{
    int i, j, k;
    printf("\n");

    for (i = -1; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (i == -1)
            {
                if (j == 0)
                    printf("   ");
                printf(" %2d |",  j + 1);
            }
            else if (j == 0 && i == 0)
            {
                if (board[i][j] != 0)
                    printf("%c | %2d | ",  'A' + i, board[i][j]);
                else
                    printf("%c |   | ", 'A' + i);
            }
            else if (j == 0)
            {
                if (board[i][j] != 0)
                    printf("%c | %2d | ", 'A' + i, board[i][j]);
                else
                    printf("%c |   | ", 'A' + i);
            }
            else
            {
                if (board[i][j] != 0)
                    printf("%2d | ", board[i][j]);
                else
                    printf("  | ");

            }
        }

        printf("\n");
        printf("%3c", SPACE);
        for ( k = 0 ; k < SIZE; k++)
            printf("-----");

        printf("\n");

    }
    printf("\n\n");
}

/* The function below is for monitoring only ! */
void printList(chessPosList* lst)
{
    chessPosCell* curr = lst->head;
    int count = 1;

    while (curr != NULL)
    {
        printf("%d. (%c : %c) \n ",count, curr->position[0], curr->position[1]);
        curr = curr->next;
        count++;
    }
}


void removeAllReoccurringCells(chessPosList* lst)
{
    chessPosCell* curr = lst->head;
    while (curr != NULL)
    {
        lst->tail = removeReoccurringCells(curr);
        curr = curr->next;
    }
}

chessPosCell* removeReoccurringCells(chessPosCell* currentPos)
{
    chessPosCell* curr, * prev, * toDelete;
    chessPos pos;

    /* saving the positions of the cell we would like to compare */
    pos[0] = currentPos->position[0];
    pos[1] = currentPos->position[1];

    prev = currentPos;
    curr = currentPos->next; /* we start checking by the first's following chessPosCell */

    while (curr != NULL)
    {
        if (curr->position[0] == pos[0] && curr->position[1] == pos[1])
        {
            toDelete = curr;
            prev->next = curr->next;

            free(toDelete);
        }

        prev = prev->next;
        curr = prev->next;
    }

    return prev; /* this is the last cell since we've reached the end of the list with curr. */
}

bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;

    return false;
}

void insertCellToEndList(chessPosList* lst, chessPosCell* newTail)
{
    if (isEmptyList(lst))
    {
        lst->head = newTail;
        lst->tail = newTail;
    }
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void insertCellToStartList(chessPosList* lst, chessPosCell* newHead)
{
    if (isEmptyList(lst))
    {
        lst->head = newHead;
        lst->tail = newHead;
    }
    else
    {
        newHead->next = lst->head;
        lst->head = newHead;
    }
}

void freeChessPosList(chessPosList* lst)
{
    chessPosCell* curr = lst->head;
    chessPosCell* next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void insertPosDataToEndList(chessPosList* lst, chessPos pos)
{
    chessPosCell* newTail;
    newTail = createNewListNode(pos, NULL);
    insertCellToEndList(lst, newTail);
}

void insertPosDataToStartList(chessPosList* lst, chessPos pos)
{
    chessPosCell* newHead;
    newHead = createNewListNode(pos, NULL);
    insertCellToStartList(lst, newHead);
}

void makeEmptyList(chessPosList* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

chessPosCell* createNewListNode(chessPos pos, chessPosCell* next)
{
    chessPosCell* newCell;

    newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
    checkAllocation(newCell);

    newCell->position[0] = pos[0];
    newCell->position[1] = pos[1];

    newCell->next = next;
    return newCell;
}



