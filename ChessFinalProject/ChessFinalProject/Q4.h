#ifndef _Q4_H
#define _Q4_H
#include "GeneralFunctions.h"
#include "Q3.h"
#include "Q2.h"


/* This function finds the path covering all of the board and returns a list of that path */
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);

/* This function rucursively helps the former one to find the path covering all of the board */
void findKnightPathCoveringAllBoardRec(chessPosList* res, treeNode* parent, int level, bool* insertNode);

#endif /* _Q4_H */
