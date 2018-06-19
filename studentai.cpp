#include "micromouseserver.h"


#include <iostream>
using namespace std;

//DIR: forward 0, right 1, down 2, left 3

/*   0
  3 -|- 1
     2
*/

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

void myMoveForward(int *x, int *y, int *dir, int (&mazeMap)[20][20]) //changes x or y coodinates when moving forward
{
     mazeMap[*x][*y]+=1;//increments value in that position, counts how many times been to coodinate
    if (*dir == 0)
    {
        *y+=1;

    }
    else if (*dir==1)
    {
        *x+=1;
    }
    else if (*dir==2)
    {
        *y-=1;
    }
    else // dir ==3
    {
        *x-=1;
    }
}

int numberOfTimesLeft(int dir, int x, int y, int (&mazeMap)[20][20] )
{
    myTurnLeft(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y];
}

int numberOfTimesRight(int dir, int x, int y, int (&mazeMap)[20][20] )
{
    myTurnRight(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y];
}

int numberOfTimesForward(int dir, int x, int y, int (&mazeMap)[20][20] )
{
    myMoveForward(&x, &y, &dir, mazeMap);
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
   static int x=0;
   static int y=0;
   static int dir = 0;
   static int mazeMap[20][20]= {0};


    // ORIGINAL left hand rule algorithm ...........................................................

    if (!isWallLeft()  && (!isWallForward() && ((numberOfTimesLeft(dir, x, y, mazeMap) < numberOfTimesForward(dir, x, y, mazeMap))) ) )
    {
        turnLeft();
        myTurnLeft(&dir);
        counterR = 0;
        counterL++;
    }

    else if (!isWallLeft() && (!isWallForward() && ((numberOfTimesForward(dir, x, y, mazeMap) < numberOfTimesLeft(dir, x, y, mazeMap))) ) )
    {

        counterR = 0;
        counterL =0;
    }

    else
        {
            if(!isWallForward()   && (!isWallRight() && (numberOfTimesForward(dir, x, y, mazeMap) < numberOfTimesRight(dir, x, y, mazeMap))))
               {
                counterR = 0;
                counterL = 0;
               }

            else if (!isWallRight()  && (numberOfTimesRight(dir, x, y, mazeMap) < numberOfTimesForward(dir, x, y, mazeMap)))
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
    myMoveForward(&x, &y, &dir, mazeMap);



    if (counterR == 3 || counterL == 3)
    {
        foundFinish();
    }

//----------see value in array ------------------------- (issue: doesnt update like expected)
    cout<<endl;
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            cout<<mazeMap[j][i];
        }
        cout<<endl;
    }
    cout<<endl;

}
