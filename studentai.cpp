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
       *dir=3;

   else
       *dir-=1;
}

void myTurnRight(int *dir) //sets direction of mouse everytime turns right
{
    if (*dir==3)    
        *dir=0;

    else    
        *dir+=1;
}

void myMoveForward(int *x, int *y, int *dir, int (&mazeMap)[41][41]) //changes x or y coodinates when moving forward
{
     mazeMap[*x][*y]+=1; //increments value in that position, counts how many times been to coodinate

    if (*dir == 0) //+2 because space in middle is space for wall
        *y+=2;

    else if (*dir==1)     
        *x+=2;

    else if (*dir==2)    
        *y-=2;

    else // dir ==3     
        *x-=2;

}

int numberOfTimesLeft(int dir, int x, int y, int (&mazeMap)[41][41] )
{
    myTurnLeft(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y];
}

int numberOfTimesRight(int dir, int x, int y, int (&mazeMap)[41][41] )
{
    myTurnRight(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y];
}

int numberOfTimesForward(int dir, int x, int y, int (&mazeMap)[41][41] )
{
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y];
}

void microMouseServer::studentAI()
{
   static int counterR; //for ending, counts how many times mouse turnsRight and moveForward
   static int counterL;
   static int x=0;
   static int y=0;
   static int dir = 0;
   static int mazeMap[41][41]= {0}; //41 spaces, walls have space in array

   //find finish (first time) ----------------------------------

   if (!isWallLeft())
    {

       if (!isWallForward() && (numberOfTimesForward(dir, x, y,mazeMap) < numberOfTimesLeft(dir,x,y,mazeMap)))
        {
           counterR = 0;
           counterL = 0;
        }
      else if (!isWallRight() && (numberOfTimesRight(dir, x, y,mazeMap) < numberOfTimesLeft(dir,x,y,mazeMap)) )
       {
           turnRight();
           myTurnRight(&dir);
           counterR++;
           counterL=0;
       }
      else
        {
           turnLeft();
           myTurnLeft(&dir);
           counterR = 0;
           counterL++;
         }
    }
   else
   {
       if (!isWallForward() && !isWallRight() && (numberOfTimesForward(dir, x, y,mazeMap) < numberOfTimesRight(dir, x, y,mazeMap)) || (isWallRight() && !isWallForward()) )
       {
           counterR = 0;
           counterL = 0;
       }
     else  if(!isWallRight() )
       {
           turnRight();
           myTurnRight(&dir);
           counterR++;
           counterL=0;
       }

       else if (isWallForward() && isWallRight()) //dead end
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

   //find where walls are

   switch (dir){
       case 0: //mouse is forward
       {
            if(isWallForward())
                mazeMap[x][y+1] = 99;
            if(isWallRight())
                mazeMap[x+1][y] = 99;
            if(isWallLeft())
                mazeMap[x-1][y] = 99;
       }
       case 1: //mouse is right
       {
            if(isWallForward())
                mazeMap[x+1][y] = 99;
            if(isWallRight())
                mazeMap[x][y-1] = 99;
            if(isWallLeft())
                mazeMap[x][y+1] = 99;
       }
       case 2: //mouse is down
       {
            if(isWallForward())
                mazeMap[x][y-1] = 99;
            if(isWallRight())
                mazeMap[x-1][y] = 99;
            if(isWallLeft())
                mazeMap[x+1][y] = 99;
       }
       case 3: //mouse is left
       {
            if(isWallForward())
                mazeMap[x-1][y] = 99;
            if(isWallRight() )
                mazeMap[x][y+1] = 99;
            if(isWallLeft() )
                mazeMap[x][y-1] = 99;
       }
   }




    if (counterR == 3 || counterL == 3)
       {
        foundFinish();
       }


    cout<<endl;
        for(int i=0; i<41; i++){
            for(int j=0; j<41; j++){
                cout<<mazeMap[i][j]<<" ";
            }
            cout<<endl;
       }
        cout<<endl;
}
