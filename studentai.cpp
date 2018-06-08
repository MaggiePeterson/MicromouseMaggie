
#include "micromouseserver.h"



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


if (!isWallLeft() )
    {turnLeft();
    counterR = 0;
    counterL++;
    }

else if (isWallLeft())
    {
        if(!isWallForward() )
           {
            counterR = 0;
            counterL = 0;
           }

        else if (isWallForward())
            {
            turnRight();
            counterR++;
            counterL=0;
            }
        else if (isWallForward() && isWallLeft() && isWallRight())
            {
            turnLeft();
            turnLeft();
            counterR = 0;
            counterL= 0;
            }
    }

moveForward();

if (counterR == 3 || counterL == 3)
{
    foundFinish();


}

}
