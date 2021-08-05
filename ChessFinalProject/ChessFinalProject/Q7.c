#include "Q7.h"


void gamePlay()
{
    int userChoice=0;
    chessPos pos;
    pathTree path;
    path.root = NULL;
    chessPosList* lst=NULL ;
    char* file_name;


    pos[0] = EMPTY, pos[1] = EMPTY;

    printf("\n");
    printLogo();
    printf("\n\n");
    printf("%22cWelcome to Chess !\n\n", SPACE);

    while (userChoice != 6)
    {

        printMenu(&userChoice);

        switch (userChoice)
        {
            case 1:

                emptyListAndTree(lst, &path);
                getPosition(&pos);
                break;

            case 2:

                if (pos[0] != EMPTY && pos[1] != EMPTY)
                {
                    path = findAllPossibleKnightPaths(&pos);
                    printf("\n%7cAll possible knight's paths were found!\n\n", SPACE);
                }

                else
                    printf("%7cNo starting position was entered!\n", SPACE);

                break;

            case 3:
                if (pos[0] != EMPTY && pos[1] != EMPTY)
                {
                    if (path.root == NULL)
                    {
                        path = findAllPossibleKnightPaths(&pos);
                        lst = findKnightPathCoveringAllBoard(&path);
                    }
                    else
                    {
                        lst = findKnightPathCoveringAllBoard(&path);
                    }

                    if (lst == NULL)
                    {
                        printf("%7cThere is no such path. \n\n", SPACE);
                        emptyListAndTree(lst, &path);
                    }

                    else
                        printf("%7cA path covering all board was found successfully!\n\n", SPACE);
                }
                else
                    printf("%7cNo starting position was entered!\n\n", SPACE);
                break;

            case 4:
                if (pos[0] != EMPTY && pos[1] != EMPTY)
                {
                    if (path.root == NULL)
                    {
                        path = findAllPossibleKnightPaths(&pos);
                        lst = findKnightPathCoveringAllBoard(&path);
                    }

                    else
                    {
                        lst = findKnightPathCoveringAllBoard(&path);
                    }

                    if (lst == NULL)
                    {
                        printf("%7cThere is no such path. \n\n", SPACE);
                        emptyListAndTree(lst, &path);
                    }



                    else
                    {
                        file_name = getFileName();
                        saveListToBinFile(file_name, lst);
                        printf("%7cA path covering all board was written to the file successfully!\n\n", SPACE);
                        free(file_name);
                    }
                }
                else
                    printf("%7cNo starting position was entered\n", SPACE);
                break;

            case 5:
                if (lst != NULL)
                {
                    file_name = getFileName();
                    userAnnouncement(checkAndDisplayFileFromFile(file_name));
                    free(file_name);
                    emptyListAndTree(lst, &path);
                }

                else
                {
                    printf("%7cThere is no such path. \n", SPACE);
                    emptyListAndTree(lst, &path);
                }

                break;

            case 6:

                emptyListAndTree(lst, &path);
                printf("%7cGoodBye!\n", SPACE);
                exit(1);

        }
    }



}

void printLogo()
{
    printf("                                                      _:_\n"
           "                                                     '-.-'\n"
           "                                            ()      __.'.__\n"
           "                                         .-:--:-.  |_______|\n"
           "                                  ()      \\____/    \\=====/\n"
           "                                  /\\      {====}     )___(\n"
           "                       (\\=,      //\\\\      )__(     /_____\\\n"
           "       __    |'-'-'|  //  .\\    (    )    /____\\     |   |\n"
           "      /  \\   |_____| (( \\_  \\    )__(      |  |      |   |\n"
           "      \\__/    |===|   ))  `\\_)  /____\\     |  |      |   |\n"
           "     /____\\   |   |  (/     \\    |  |      |  |      |   |\n"
           "      |  |    |   |   | _.-'|    |  |      |  |      |   |\n"
           "      |__|    )___(    )___(    /____\\    /____\\    /_____\\\n"
           "     (====)  (=====)  (=====)  (======)  (======)  (=======)\n"
           "     }===={  }====={  }====={  }======{  }======{  }======={\n"
           "    (______)(_______)(_______)(________)(________)(_________)");
}

void printMenu(int* userChoice)
{
    int choice;


    printf("%7c-------------------------------------------------- \n", SPACE);
    printf("%7c|    Please choose your option:                  | \n", SPACE);
    printf("%7c-------------------------------------------------- \n", SPACE);
    printf("%7c| 1. Enter a knight's starting position.         | \n", SPACE);
    printf("%7c| 2. Create all possible knight paths            | \n", SPACE);
    printf("%7c| 3. Find a knight path covering all board       | \n", SPACE);
    printf("%7c| 4. Save knight path covering all board to file | \n", SPACE);
    printf("%7c| 5. Load and display path from file             | \n", SPACE);
    printf("%7c| 6. Exit                                        | \n", SPACE);
    printf("%7c-------------------------------------------------- \n", SPACE);


    scanf("%d", &choice);

    while (choice > 6 || choice < 1)
    {
        printf("%7cInvalid choice, please choose again! \n\n ", SPACE);
        scanf("%d", &choice);
    }

    *userChoice = choice;
}

bool isValidCell(chessPos cell)
{
    bool res = true;

    if ((cell[0] < 'A' || cell[0] > 'H') || (cell[1] < '1' || cell[1] > '8'))
        res = false;

    return res;
}

void getPosition (chessPos *pos)
{
    chessPos temp;

    printf("\n%7cPlease enter a knight's starting position: \n", SPACE);
    getchar();
    scanf("%c %c", &temp[0], &temp[1]);

    if (!isValidCell(temp))
    {
        printf("\n%7c You chose an invalid cell.\n", SPACE);
    }
    else
    {
        (*pos)[0] = temp[0];
        (*pos)[1] = temp[1];
        printf("\n%6c Cell was saved successfully.\n", SPACE);

    }

    printf("\n");

}

char* getFileName()
{
    int logicSize = 0, physicalSize = 1;
    char currChar = EMPTY;
    char* res;

    res = (char*)malloc(physicalSize * sizeof(char));
    checkAllocation(res);

    printf("\n%7cPlease enter file's name:\n%7c", SPACE, SPACE);



    getchar();
    while (currChar != '\n')
    {
        if (logicSize == physicalSize)
        {
            physicalSize = physicalSize * 2 + 1;	 /* double the physical size + one more place for '\0' */
            res = (char*)realloc(res, sizeof(char) * physicalSize);
            checkAllocation(res);
        }

        res[logicSize] = currChar; /* inserting the char */
        logicSize++;
        currChar = getchar(); /* gets next char */
    }

    /*  adjusting the string's size to be its logical size + one more for '\0' */
    res = (char*)realloc(res, sizeof(char)* (logicSize + 1));
    checkAllocation(res);

    res[logicSize] = '\0';		/* '\0' ending the string */

    return res;
}

void emptyListAndTree (chessPosList *lst, pathTree* path)
{
    if (path -> root != NULL)
    {
        freeTree(path);
        path -> root = NULL;
    }

    if (lst != NULL)
    {
        freeChessPosList(lst);
        makeEmptyList(lst);
    }

}

void userAnnouncement (int value)
{
    switch (value)
    {
        case NOT_FOUND :
            printf("\n %7cThere is no such file!\n", SPACE);
            break;

        case INVALID_PATH:
            printf("\n %7cThe path is invalid! \n", SPACE);
            break;

        case PATH_COVERING_ALL_BOARD:
            printf("\n %7cThe path covering all board is displayed above\n", SPACE);
            break;

        case PATH_NOT_COVERING_ALL_BOARD:
            printf("\n %7cThe path does not cover all of the board!\n", SPACE);
            break;

    }
}
