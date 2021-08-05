/*
  Full name: Avi Maya
  Project description: this program is the snake game.
  the user chooses between 3 levels: basic, intermediate and advanced.
  using the arrows on the keyboard, the user moves the snake in order for it to catch the food (the symbol '$').
  Everytime the snake eats its body grows bigger. If the snake eats its tail or hits the wall the game is over.
  There are 10 food symbols ('$') in total, if the snake eats all of them without hitting itself or the walls, the
  user wins.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 20
#define UP 72  
#define DOWN 80 
#define LEFT 75  
#define RIGHT 77  
#define ESC 27  
#define ROW_SIZE 25
#define COL_SIZE 75
#define INVALID_CHOICE -1
#define WIN 2
#define LOSE 1
#define EXIT 0

typedef struct {
    int x;
    int y;

}Snake;
typedef struct {
    int x;
    int y;
}Point;

// a function for printing the game's menu
int  printMenu();

// a function for printing the boards borders
void printBorder();

// a function for moving the cursor to a specific point on the screen regardless of the sequnce of action
void gotoXY(int x, int y);

// the gameplay function for playing the game
int gamePlay();

// the getKey function returns a code for every key pressed on the keyboard
int getKey();

// a function for moving the snake, prints @ in each move and deletes the first @ (the tail)
void moveSnake(Snake snake[], int size, int x, int y);

// a boolean function that ends the game if the snake hits one of the borders of the board or its body
bool badIntersection(Snake snake[], int head);

// a function that scatters  food randomly across the board (one at a time).
void printFood(Point* food);



void main() {
    int userChoice, res;
    bool gameOn = true;
    

    printf("\n\n");
    printf("                                 88                   \n"
        "                                 88                   \n"
        "                                 88                   \n"
        ",adPPYba, 8b,dPPYba,  ,adPPYYba, 88   ,d8  ,adPPYba,  \n"
        "I8[    \"\" 88P'   `\"8a \"\"     `Y8 88 ,a8\"  a8P_____88  \n"
        " `\"Y8ba,  88       88 ,adPPPPP88 8888[    8PP\"\"\"\"\"\"\"  \n"
        "aa    ]8I 88       88 88,    ,88 88`\"Yba, \"8b,   ,aa  \n"
        "`\"YbbdP\"' 88       88 `\"8bbdP\"Y8 88   `Y8a `\"Ybbd8\"' ");


    while (gameOn)
    {
        userChoice = printMenu();

        while (userChoice == INVALID_CHOICE)
        {
            userChoice = printMenu();
        }

        if (userChoice != EXIT)
        {
            printBorder();

            while (gameOn)
            {
                res = gamePlay();

                if (res == LOSE)
                {
                    system("cls");
                    printf("\n\nGame Over!\n\n");
                    break;

                }
                else if (res == WIN)
                {
                    system("cls");
                    printf("\n\nYou Won! Congrats!\n\n");
                    break;
                }

                else
                    system("cls");
                    break;
            }

        }

        else
        {
            printf("\n\nGood bye.\n");
            gameOn = false;
        }


        }
    }

int printMenu()

{
    int userChoice;


    printf("\n\n\n****************************************************\n");
    printf("* Please choose your level (or press 0 to exit):   *\n");
    printf("* 0. Exit                                          *\n");
    printf("* 1. Basic                                         *\n");
    printf("* 2. Intermediate                                  *\n");
    printf("* 3. Advanced                                      *\n");
    printf("****************************************************\n");

    scanf("%d", &userChoice);

    // For part A of this project only! defining option 1 as the default game level, will change the conditions in part B
    if (userChoice != 0 && userChoice != 1)
        userChoice = INVALID_CHOICE;

    return userChoice;


}
void printBorder()   
{
    int row, col;
    system("cls");
    for (row = 0, col = 0; row < ROW_SIZE ; row++)
    {
        gotoXY(col, row);
        printf("#");
    }

    for (row = 0, col = COL_SIZE - 1; row < ROW_SIZE ; row++)
    {
        gotoXY(col, row);
        printf("#");
    }

    for (row = ROW_SIZE - 1, col = 1; col < COL_SIZE; col++)
    {
        gotoXY(col, row);
        printf("#");                  
    }

    for (row = 0, col = 1; col < COL_SIZE; col++)
    {
        gotoXY(col, row);;
        printf("#");
    }


}

void gotoXY(int y, int x) {
    printf("\x1b[%d;%df", x + 1, y + 1);

}

int gamePlay()
{
   Snake snake[SIZE];
   Point food = {0,0};
   bool eatenFood = false;
   char userAction, currentAction;
   int x0, y0, x = 40, y = 12, count = 0, ind =0, remainingFood = 10;
   gotoXY(x, y); 


   printFood(&food);
   userAction = getKey();
   
   
    while (userAction != ESC)
    {
        Sleep(1000);

        currentAction = userAction;

        if (_kbhit())
        {
            userAction = getKey();
        }
        
        

        if (userAction != LEFT && userAction != RIGHT && userAction != UP && userAction != DOWN && userAction != ESC)
        {
            userAction = currentAction;
        }


        switch (userAction)
        {
             case RIGHT:
                x++;
                break;

             case LEFT:
                 x--;
                 break;

             case DOWN:
                 y++;
                 break;
                 
             case UP:
                 y--;
                 break;

           
         }

        if (eatenFood == true)
        {
            printFood(&food);
            eatenFood = false;
        }

        if (count > 9)
        {
            x0 = snake[0].x;
            y0 = snake[0].y;
            snake[count].x = x;
            snake[count].y = y;
            
            

            if (badIntersection(snake, count))
            {
                return LOSE;
            }
             
            else if (x == food.x && y == food.y)
            {
                eatenFood = true;
                remainingFood--;
                count ++;
            }
            else
            {
                moveSnake(snake, count, x0, y0);
            }


            if (remainingFood == 0)
            {
                return WIN;
            }


        }
        else 
        {
            snake[count].x = x;
            snake[count].y = y;
            count++;
        }

        
        gotoXY(x, y);
        printf("@");
        gotoXY(26, 81);

    }

    return EXIT;


}

int getKey() 
{
    char KeyStroke = _getch();
    if (KeyStroke == 0 || KeyStroke == -32)
        KeyStroke = _getch();
    return (KeyStroke);
}
void moveSnake(Snake snake[], int size,  int x, int y)
{  
    int i;

    for (i = 0 ; i < size ; i++ )
    {
        snake[i].x = snake[i+1].x;
        snake[i].y = snake[i+1].y;
    }

    gotoXY(x, y);
    printf(" ");



}

bool badIntersection(Snake snake[], int head)
{
    int i;

    if (snake[head].x == COL_SIZE - 1 || snake[head].x == 0 || snake[head].y == ROW_SIZE -1 || snake[head].y == 0)
        return true;

    for (i = 0; i < head; i++)
    {
        if (snake[head].x == snake[i].x && snake[head].y == snake[i].y)
            return true;
    }

    return false;
}
void printFood(Point* food)
{

    srand(time(NULL));
    (*food).x = 1 + rand() % (COL_SIZE - 2) ;
    (*food).y = 1 + rand() % (ROW_SIZE - 2) ;
    gotoXY(food -> x, food -> y);
    printf("$");

}
