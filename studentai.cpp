#include "micromouseserver.h"
#include <iostream>
using namespace std;

//DIR: forward 0, right 1, down 2, left 3

/*   0
  3 -|- 1
     2
*/

class square { //SHORTEST PATH: make square class in array, detects where walls are

    bool isWallNorth;
    bool isWallEast;
    bool isWallSouth;
    bool isWallWest;

public:
    void setWallNorth(bool wallN);
    void setWallEast(bool wallE);
    void setWallSouth(bool wallS);
    void setWallWest(bool wallW);

};

void square::setWallNorth(bool wallN) //wall is north if value gets is true/ false
{
    this->isWallNorth = wallN;
}

void square::setWallEast(bool wallE)
{
    this->isWallEast = wallE;
}

void square::setWallSouth(bool wallS)
{
    this->isWallSouth = wallS;
}

void square::setWallWest(bool wallW)
{
    this->isWallWest = wallW;
}

square mapSq[20][20];

//---------------------------

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

void myMoveForward(int *x, int *y, int *dir, int (&mazeMap)[20][20]) //changes x or y coodinates when moving forward
{
     mazeMap[*x][*y]+=1; //increments value in that position, counts how many times been to coodinate

    if (*dir == 0)
        *y-=1;

    else if (*dir==1)     
        *x+=1;

    else if (*dir==2)    
        *y+=1;

    else // dir ==3     
        *x-=1;

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
   static int counterR; //for ending, counts how many times mouse turnsRight and moveForward
   static int counterL;
   static int x=0;
   static int y=19; //shows in bottom left corner of array
   static int dir = 0;
   static int mazeMap[20][20]= {0}; //20 spaces, walls have space in array

    //use enum, find state to get exploring vs. shortest path
   //find finish (first time) ------------------------------------

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

   //find where walls are------------------------

   switch (dir){
    case 0: //forward
      {
       mapSq[x][y].setWallNorth(isWallForward());
       mapSq[x][y].setWallEast(isWallRight());
       mapSq[x][y].setWallWest(isWallLeft());
       break;
      }
   case 1: //right
     {
      mapSq[x][y].setWallEast(isWallForward()); //forward if mouse is facing right, square has wall East
      mapSq[x][y].setWallSouth(isWallRight());
      mapSq[x][y].setWallNorth(isWallLeft());
      break;
     }
   case 2: //down
     {
      mapSq[x][y].setWallSouth(isWallForward()); //is facing down, wall is forward, wall is objectively south
      mapSq[x][y].setWallWest(isWallRight());
      mapSq[x][y].setWallEast(isWallLeft());
      break;
     }
   case 3: //left
     {
      mapSq[x][y].setWallWest(isWallForward());
      mapSq[x][y].setWallNorth(isWallRight());
      mapSq[x][y].setWallSouth(isWallLeft());
      break;
     }
   }

   //finish-----------------------------------
    if (counterR > 2 || counterL > 2 )
       {
        foundFinish();
       }

    cout<<endl;
        for(int i=0; i<20; i++){
            for(int j=0; j<20; j++){
                cout<<mazeMap[j][i]<<" ";
            }
            cout<<endl;
       }
        cout<<endl;
}

