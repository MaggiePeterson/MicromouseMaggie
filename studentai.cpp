#include "micromouseserver.h"
#include <iostream>
using namespace std;

//DIR: forward 0, right 1, down 2, left 3

/*   0
  3 -|- 1
     2
*/
struct node {

    int timesVisited;
    bool finished = false;

    node* previousNode = NULL;
    node* north = NULL;
    node* east = NULL;
    node* south = NULL;
    node* west = NULL;

};


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

void myMoveForward(int *x, int *y, int *dir, node (mazeMap)[20][20]) //changes x or y coodinates when moving forward
{
     mazeMap[*x][*y].timesVisited+=1; //increments value in that position, counts how many times been to coodinate

    if (*dir == 0)
        *y-=1;

    else if (*dir==1)     
        *x+=1;

    else if (*dir==2)    
        *y+=1;

    else // dir ==3     
        *x-=1;

}

int numberOfTimesLeft(int dir, int x, int y, node (&mazeMap)[20][20] )
{
    myTurnLeft(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y].timesVisited;
}

int numberOfTimesRight(int dir, int x, int y, node (mazeMap)[20][20] )
{
    myTurnRight(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y].timesVisited;
}

int numberOfTimesForward(int dir, int x, int y, node (&mazeMap)[20][20] )
{
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y].timesVisited;
}


void microMouseServer::studentAI()
{
   static int counterR; //for ending, counts how many times mouse turnsRight and moveForward
   static int counterL;
   static int x=0;
   static int y=19; //shows in bottom left corner of array
   static int dir = 0;
   static node mazeMap[20][20];

   switch (dir){
    case 0: //forward
      { if(!isWallForward())
          {
           mazeMap[x][y].north = & (mazeMap[x][y-1]);
           mazeMap[x][y-1].south = &(mazeMap[x][y] );
           }
       else if (!isWallRight())
       {
           mazeMap[x][y].east = & (mazeMap[x-1][y]);
           mazeMap[x-1][y].west = &(mazeMap[x][y] );
        }
       else if(!isWallLeft())
       {
           mazeMap[x][y].west = &(mazeMap[x-1][y]);
           mazeMap[x-1][y].east = &(mazeMap[x][y]);
        }

       break;
       }
    case 1: //right
       {
       if(!isWallForward())
       {
          mazeMap[x][y].east = &mazeMap[x+1][y];
          mazeMap[x+1][y].west = &mazeMap[x][y];
       }
       else if(!isWallRight())
        {
           mazeMap[x][y].south = &mazeMap[x][y+1];
           mazeMap[x][y+1].north = &mazeMap[x][y];
        }
       else if(!isWallLeft())
       {
           mazeMap[x][y].north = &mazeMap[x][y-1];
           mazeMap[x][y-1].south = &mazeMap[x][y];
       }
       break;
        }
     case 2: //down
     {
       if(!isWallForward())
       {
           mazeMap[x][y].south = &mazeMap[x][y+1];
           mazeMap[x][y+1].north = &mazeMap[x][y];
       }
       else if(!isWallRight())
       {
           mazeMap[x][y].west = &mazeMap[x-1][y];
           mazeMap[x-1][y].east = &mazeMap[x][y];
       }
       else if(!isWallLeft())
       {
           mazeMap[x][y].east = &mazeMap[x+1][y];
           mazeMap[x+1][y].west = &mazeMap[x][y];
        }
       break;
      }
     case 3: //left
      {
        if(!isWallForward())
        {
            mazeMap[x][y].west = &mazeMap[x-1][y];
            mazeMap[x-1][y].east = &mazeMap[x][y];
         }
         else if(!isWallRight())
        {
            mazeMap[x][y].north = &mazeMap[x][y-1];
            mazeMap[x][y-1].south = &mazeMap[x][y];
         }
        else if(!isWallLeft())
        {
            mazeMap[x][y].south = &mazeMap[x][y+1];
            mazeMap[x][y+1].north = &mazeMap[x][y];
        }
        break;
        }
  }
  // static square mapSq[20][20];

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

   //links nodes together if no walls



   //finish-----------------------------------
    if (counterR > 2 || counterL > 2 )
       {
        foundFinish();
        mazeMap[x][y].finished = true;
       }

    cout<<endl;
        for(int i=0; i<20; i++){
            for(int j=0; j<20; j++){
                cout<<mazeMap[j][i].timesVisited<<" ";
            }
            cout<<endl;
       }
        cout<<endl;
}

