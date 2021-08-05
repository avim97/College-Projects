#include "GeneralFunctions.h"

void checkAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation has failed! \n Terminating the program. \n");
        exit(1);
    }
}

void checkFileOpening(FILE* file)
{
    if (file == NULL)
    {
        printf("File opening has failed! \n Terminating the program. \n");
        exit(1);
    }
}

char intToChar(int num)
{
    char res;

    switch (num)
    {
        case 0:
            res = 'A';
            break;
        case 1:
            res = 'B';
            break;
        case 2:
            res = 'C';
            break;
        case 3:
            res = 'D';
            break;
        case 4:
            res = 'E';
            break;
        case 5:
            res = 'F';
            break;
        case 6:
            res = 'G';
            break;
        case 7:
            res = 'H';
            break;
    }

    return res;
}

int charToInt(char ch)
{
    int num = -1;

    if (ch >= '1' && ch <= '9')
        num = ch - '1';
    else
    {
        if (ch >= 'A' && ch <= 'Z')
            num = ch - 'A';
    }

    return num;
}