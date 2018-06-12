
#include "micromouseserver.h"

//north 0, east 1, south, 2, west 3


void myTurnLeft(int *dir) //changes direction of mouse everytime turns left
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

void myTurnRight(int *dir) //sets direction of mouse everytime turns right
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

void myMoveForward(int *dir, int *x,int *y ) //changes x or y coodinates when moving forward
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
    mazeMap[x][y]++;
}

int numberOfTimesLeft(int dir, int x, int y, int (&mazeMap)[20][20]) //returns current position ?
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


    return mazeMap[x][y];

}

int numberOfTimesRight(int dir, int x, int y, int (&mazeMap)[20][20]) //returns current position after turning right
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

    return mazeMap[x][y];
}

int numberOfTimesForward(int dir, int x, int y, int (&mazeMap)[20][20]) //returns position of forward coodinate...
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

    return mazeMap[x][y];
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
static int mazeMap[20][20] = {0};
static int x=0, y=0, dir =0;

//add while loop to continue
int minT = mazeMap[x][y+1]; //minT = min amount of times visited coordinate
int minDir = 0; //north 0, east 1, south, 2, west 3 ... Sets direction of minimum coodinate

// finds coodinate least visited relative to current position x,y
if (mazeMap[x][y-1]< minT)
{
    minT = mazeMap[x][y-1];
    minDir = 2;
}
else if (mazeMap[x+1][y]< minT)
{
    minT = mazeMap[x+1][y];
    minDir = 1;
}
else // (mazeMap[x-1][y]< minT)
{
    minT = mazeMap[x-1][y];
    minDir = 3;
}

//compares Current Direction to Direction/ placement of cood least visited, then decides how to turn

if (&dir == minDir )
{
    moveForward();
    myMoveForward(&x,&y,&dir);
}

else if (&dir - minDir == 3 || &dir - minDir == -1) //current direction 3 minus minDirection 0, = 3, turn right
{
    turnRight();
    myTurnRight(&dir);
}
else if (&dir - minDir == 1 || &dir - minDir == -3) //ex. CurrentDir = 2(south), minDir = 1(east), turn left
{
    turnLeft();
    myTurnLeft(&dir);
}


// left hand rule algorithm ...

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
