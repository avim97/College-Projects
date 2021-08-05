
#include "Q3.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    pathTree path;

    PreviousSteps prevSteps = { false };

    chessPosArray*** possibleMoves=validKnightMoves();

    path.root = findAllPossibleKnightPathsRec(startingPosition, possibleMoves, prevSteps);

    freePosArrays(possibleMoves);

    return path;

}

treeNode* findAllPossibleKnightPathsRec(chessPos* startingPosition, chessPosArray*** possibleMoves, PreviousSteps prevSteps)
{
    int currRow, currCol,currSize,i,tempRow,tempCol,count;
    chessPos* tempPos;
    bool isThereNoPrevStep = true; /* this argument represents whether there have left any possible moves from now on or not.*/
    treeNodeListCell* newCell;
    treeNode* nextRoot;
    treeNode* currRoot = createNewTreeNode(startingPosition, NULL);

    currRow = charToInt((*startingPosition)[0]);
    currCol = charToInt((*startingPosition)[1]);
    currSize= possibleMoves[currRow][currCol]->size;
    count = currSize;

    tempPos = possibleMoves[currRow][currCol]->positions;
    prevSteps[currRow][currCol] = true; /*marking that this position have already been visited*/

    for (i = 0;i < currSize;i++)
    {
        tempRow = charToInt(tempPos[i][0]);
        tempCol = charToInt(tempPos[i][1]);

        if (prevSteps[tempRow][tempCol] == false)
        {
            isThereNoPrevStep = false; /*meaning we have at least one cell to go to = at least one cell in the list*/
            nextRoot = findAllPossibleKnightPathsRec(&tempPos[i], possibleMoves, prevSteps);

            if (currRoot->next_possible_position == NULL)
            {
                newCell = createNewListCell(nextRoot, NULL);
                currRoot->next_possible_position = newCell;
            }
            else
            {
                newCell = createNewListCell(nextRoot, currRoot->next_possible_position);
                currRoot->next_possible_position = newCell;
            }
        }
        else
            count--;
    }

    prevSteps[currRow][currCol] = false; /*unmarking the position we have marked as visited for future use of the newCell's "siblings"*/

    if (isThereNoPrevStep)
    {
        if (count == 0)
            return currRoot;
        else /*meaning we have nowhere to go*/
            return NULL;
    }
    else
        return currRoot;
}

treeNode* createNewTreeNode(chessPos* startingPosition, treeNodeListCell* nextMoves)
{
    treeNode* newNode= (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(newNode);

    /*filling the root's position*/
    newNode->position[0] = (*startingPosition)[0];
    newNode->position[1] = (*startingPosition)[1];

    newNode->next_possible_position = nextMoves;

    return newNode;
}

treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* prevListCell)
{
    treeNodeListCell* newCell= (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkAllocation(newCell);

    newCell->node = node;
    newCell->next = prevListCell;

    return newCell;
}

void freeTree(pathTree* tr)
{
    freeTreeRec(tr->root);
}

void freeTreeRec(treeNode* root)
{

    if (root == NULL)
    {
        return;
    }
    else
    {
        if (root->next_possible_position == NULL) /* if the root doesn't have any sons*/
            free(root);

        else  /* meaning the root has at least one son*/
        {
            if (root->next_possible_position->node != NULL)
            {
                freeTreeRec(root->next_possible_position->node);
            }

            if (root->next_possible_position->next != NULL) /* if the root has a brother*/
            {
                if (root->next_possible_position->next->node)
                {
                    freeTreeRec(root->next_possible_position->next->node); /* free brother */
                }
            }
        }
    }
}









