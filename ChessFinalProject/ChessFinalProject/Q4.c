#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
    bool insertNode = true;
    chessPosList* res;
    res = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocation(res);
    makeEmptyList(res);

    findKnightPathCoveringAllBoardRec(res, path_tree->root, 1,&insertNode);

    if (res->head != NULL)
    {
        insertPosDataToStartList(res, path_tree->root->position);
        return res;
    }
    else
    {
        free(res);
        return NULL;
    }
}

void findKnightPathCoveringAllBoardRec(chessPosList* res, treeNode* parent, int level, bool* insertNode)
{
    treeNodeListCell* sons;

    if (parent->next_possible_position == NULL) /* if the parent doesn't have sons*/
    {
        if (level == MAX_LST_SIZE) /*we have reached a path covering the entire board*/
            *insertNode = true;
        else
            *insertNode = false;
        /*if we've reached the end of one path and its not covering the entire board we wouldn't want the former
         *positions to be entered to the list*/
    }
    else /*if parent has sons*/
    {
        sons = parent->next_possible_position; /*the first son*/

        while (sons != NULL) /* We'll run through the brother's list*/
        {
            findKnightPathCoveringAllBoardRec(res, sons->node, level+1,insertNode);

            if (*insertNode) /*meaning we've reached a full path and this node is a part of it*/
            {
                insertPosDataToStartList(res, sons->node->position);
                break; /*we have a full path so we'll exit the while loop- we don't need to check other paths of son's brothers*/
            }
            else
                sons = sons->next;
        }
    }
}