
#include "micromouseserver.h"

//north 0, east 1, south, 2, west 3


void myTurnLeft(int *dir)
{

   if (*dir ==0)
  {

       *dir=3;
   }
   else
   {
       *dir-=1;
   }

}

void myTurnRight(int *dir)
{
    if (*dir==3)
    {
        *dir=0;
    }
    else
    {
        *dir+=1;
    }
}

void myMoveForward(int *dir, int *x,int *y )
{
    if (*dir == 0)
    {
        *y++;

    }
    else if (*dir==1)
    {
        *x++;
    }
    else if (*dir==2)
    {
        *y--;
    }
    else // dir ==3
    {
        *x--;
    }
}

int numberOfTimesLeft(int dir, int x, int y, int (&map)[20][20])
{
    myTurnLeft(&dir);
    myMoveForward(&dir, &x, &y);
    if (x<0)
    {
        x= 0;
    }
    else if (x>19)
    {
        x= 19;
    }
    else if (y<0)
    {
        y= 0;
    }
    else if (y>19)
    {
        y= 19;
    }


    return map[x][y];

}

int numberOfTimesRight(int dir, int x, int y, int (&map)[20][20])
{
    myTurnRight(&dir);
    myMoveForward(&dir, &x, &y);
    if (x<0)
    {
        x= 0;
    }
    else if (x>19)
    {
        x= 19;
    }
    else if (y<0)
    {
        y= 0;
    }
    else if (y>19)
    {
        y= 19;
    }

    return map[x][y];
}

int numberOfTimesForward(int dir, int x, int y, int (&map)[20][20])
{
    myMoveForward(&dir, &x, &y);
    if (x<0)
    {
        x= 0;
    }
    else if (x>19)
    {
        x= 19;
    }
    else if (y<0)
    {
        y= 0;
    }
    else if (y>19)
    {
        y= 19;
    }

    return map[x][y];
}


void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/
static int counterR, counterL; //for ending, counts how many times mouse turnsRight and moveForward
static int map[20][20] = {0};
static int x=0, y=0, dir =0;

/*if (map[x][y] < map[x][y+1])
{
    //foo
}
else if (map[x][y] < map[x][y-1])
{}
*/


if (!isWallLeft() )
    {turnLeft();
    myTurnLeft(&dir);
    counterR = 0;
    counterL++;
    }

else
    {
        if(!isWallForward() )
           {
            counterR = 0;
            counterL = 0;
           }

        else if (!isWallRight())
            {
            turnRight();
            myTurnRight(&dir);
            counterR++;
            counterL=0;
            }
        else if (isWallForward() && isWallLeft() && isWallRight())
            {
            turnLeft();
            myTurnLeft(&dir);
            turnLeft();
            myTurnLeft(&dir);
            counterR = 0;
            counterL= 0;
            }
    }

moveForward();
myMoveForward(&x,&y,&dir);



if (counterR == 3 || counterL == 3)
{
    foundFinish();


}

}
