#ifndef _Q3_H
#define _Q3_H

#include "GeneralFunctions.h"
#include "Q1.h"

typedef bool PreviousSteps[SIZE][SIZE];

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
    chessPos position;
    treeNodeListCell* next_possible_position;
}treeNode;

typedef struct _treeNodeListCell {
    treeNode* node;
    struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
    treeNode* root;
} pathTree;


/* This function finds all of the possible knight moves of a certain position and returns the tree containing all
 * possible paths */
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);

/* The following function recursively helps the former function achieving all possible paths */
treeNode* findAllPossibleKnightPathsRec(chessPos* startingPosition, chessPosArray*** possibleMoves, PreviousSteps prevSteps);

/* The following function creates a new tree node */
treeNode* createNewTreeNode(chessPos* startingPosition, treeNodeListCell* nextMoves);

/* The following function creates a new treeNodeListCell */
treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* prevListCell);

/* The following function is a wrapper function to the recursive function which frees the tree. */
void freeTree(pathTree* tr);

/* The following function recursively frees the tree. */
void freeTreeRec(treeNode* root);



#endif /* _Q3_H */
