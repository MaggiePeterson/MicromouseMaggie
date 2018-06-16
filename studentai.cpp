#include "micromouseserver.h"


#include <iostream>
using namespace std;

//DIR: forward 0, right 1, down, 2, left 3

/*  0
  3-|- 1
    2
*/

int dir;
int y =0;
int x=0;

void myTurnLeft() //changes direction of mouse everytime turns left
{

   if (dir ==0)
  {
       dir=3;
   }
   else
   {
       dir-=1;
   }

}

void myTurnRight() //sets direction of mouse everytime turns right
{
    if (dir==3)
    {
        dir=0;
    }
    else
    {
        dir+=1;
    }
}

void myMoveForward(int mazeMap[20][20]) //changes x or y coodinates when moving forward
{
     mazeMap[x][y]+=1;//increments value in that position, counts how many times been to coodinate
    if (dir == 0)
    {
        y+=1;

    }
    else if (dir==1)
    {
        x+=1;
    }
    else if (dir==2)
    {
        y-=1;
    }
    else // dir ==3
    {
        x-=1;
    }
}

/*
int numberOfTimesLeft(int dir, int x, int y, int (&mazeMap)[20][20]) //returns current position ?
{
    //myTurnLeft(&dir);
   //myMoveForward(&dir, &x, &y, mazeMap );
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
    //myTurnRight(&dir);
    //myMoveForward(&dir, &x, &y,mazeMap );
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
    myMoveForward(&dir, &x, &y, mazeMap );
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
*/

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
   // static int x=0;
    //static int y=0;
   // static int dir = 0;
    //static int mazeMap[20][20]= {0};
   static int minT =  mazeMap[x-1][y]; //minT = min amount of times visited coordinate
   static int minDir = 1; //north 0, east 1, south, 2, west 3 ... Sets direction of minimum coodinate

    switch (dir) //finds min direction relative to current orientation of mouse, without a wall
    {
        case 0:{ //mouse facing forward

                if (!isWallForward() && mazeMap[x][y+1] < minT) //no wall forward and forward has least value, forward is min and minDir is forward
                {
                    minT = mazeMap[x][y+1];
                    minDir = 0;
                }
                if (!isWallRight() && mazeMap[x+1][y] < minT)
                {
                    minT = mazeMap[x+1][y];
                    minDir = 1;
                }
                if (!isWallLeft() && mazeMap[x-1][y] < minT) // finds coodinate least visited relative to current position x,y
                {
                    minT = mazeMap[x-1][y];
                    minDir = 3;
               }
            break;
        }

    case 1:{ //mouse facing right

            if (!isWallLeft() && mazeMap[x][y+1] < minT) //no wall left to mouse, no wall in position on graph that is left of mouse
            {
                minT = mazeMap[x][y+1];
                minDir = 0;
            }
            if (!isWallForward() && mazeMap[x+1][y]< minT)
            {
                minT = mazeMap[x+1][y];
                minDir = 1;
            }
            if (!isWallRight() && mazeMap[x][y-1]< minT) // finds coodinate least visited relative to current position x,y
            {
                minT = mazeMap[x][y-1];
                minDir = 2;
           }
        break;
    }
    case 2:{ //mouse facing down

            if (!isWallForward() && mazeMap[x][y-1] < minT)
            {
                minT = mazeMap[x][y-1];
                minDir = 2;
            }
            if (!isWallRight() && mazeMap[x-1][y]< minT)
            {
                minT = mazeMap[x-1][y];
                minDir = 3;
            }
            if (!isWallLeft() && mazeMap[x+1][y]< minT) // finds coodinate least visited relative to current position x,y
            {
                minT = mazeMap[x+1][y];
                minDir = 1;
           }
        break;
    }

    case 3:{ //mouse facing left

            if (!isWallRight() && mazeMap[x][y+1] < minT)
            {
                minT = mazeMap[x][y+1];
                minDir = 0;
            }
            if (!isWallLeft() && mazeMap[x][y-1]< minT)
            {
                minT = mazeMap[x][y-1];
                minDir = 2;
            }
            if (!isWallForward() && mazeMap[x-1][y]< minT) // finds coodinate least visited relative to current position x,y
            {
                minT = mazeMap[x-1][y];
                minDir = 3;
           }
        break;
    }

      default:
        break;
    }

    //compares Current Direction to Direction/placement of cood least visited, then decides how to turn.........
    if (dir == minDir)
    {
      //stay in place
    }

    else if ( dir - minDir == 3 || dir - minDir == -1) //current direction 3 minus minDirection 0, = 3, turn right
    {
        turnRight();
        myTurnRight();
    }
    else if (dir - minDir == 1 || dir - minDir == -3) //ex. CurrentDir = 2(south), minDir = 1(east), turn left
    {
        turnLeft();
        myTurnLeft();
    }

    // ORIGINAL left hand rule algorithm ...........................................................

    if (!isWallLeft())
        {turnLeft();
        myTurnLeft();
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

            else if (!isWallRight() )
                {
                turnRight();
                myTurnRight();
                counterR++;
                counterL=0;
                }
           else if (isWallForward() && isWallLeft() && isWallRight())
                {
                turnLeft();
                myTurnLeft();
                turnLeft();
                myTurnLeft();
                counterR = 0;
                counterL= 0;
                }
        }

    moveForward();
    myMoveForward(mazeMap);



    if (counterR == 3 || counterL == 3)
    {
        foundFinish();
    }


    //---------see value in array ------------------------- (issue: doesnt update like expected)
    cout<<endl;
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            cout<<mazeMap[j][i];
        }
        cout<<endl;
    }
    cout<<endl;

}
