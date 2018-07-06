
#include "micromouseserver.h"
#include <iostream>
using namespace std;
#include <QQueue>

//DIR: forward 0, right 1, down 2, left 3

/*   0
  3 -|- 1
     2
*/

struct node {

    int timesVisited;
    int xN =0,yN=19;
    bool finished = false;
    bool flag = false;      //visited Node
    int level = 0;

    node* previousNode = NULL;
    node* north = NULL;
    node* east = NULL;
    node* south = NULL;
    node* west = NULL;

};

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

void myMoveForward(int *x, int *y, int *dir, node (&mazeMap)[20][20]) //changes x or y coodinates when moving forward
{
     mazeMap[*x][*y].timesVisited+=1; //increments value in that position, counts how many times been to coodinate

    if (*dir == 0)

        *y-=1;

    else if (*dir==1)
        *x+=1;

    else if (*dir==2)
        *y+=1;

    else // 3
        *x-=1;
}

int numberOfTimesLeft(int dir, int x, int y, node (&mazeMap)[20][20] )
{
    myTurnLeft(&dir);
    myMoveForward(&x, &y, &dir, mazeMap);
    return mazeMap[x][y].timesVisited;
}

int numberOfTimesRight(int dir, int x, int y, node (&mazeMap)[20][20] )
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

void findShortestPath(node (&mazeMap)[20][20] ) //BFR algorithm
{
     QQueue <node*> q;
     q.enqueue(& (mazeMap[0][19])); //adds starting position to queue


     while(!q.head()->finished)     // adds queue but doesnt delete it, until found finish
      {
         node* currNode = q.dequeue();//currNode points to removed value, empties q

        if (currNode->north != NULL && !currNode->north->flag) //finds adjacent nodes, doesnt count node if already counted
         {
            currNode->north->previousNode = currNode;       //currNode is previous node of node North
            q.enqueue(currNode->north);                     //adds north node to queue
            currNode->flag = true;
         }
       if(currNode->east != NULL && !currNode->east->flag) //opening right && if node has not been checked/ visited
         {
            currNode->east->previousNode = currNode;
            q.enqueue(currNode->east);
            currNode->flag = true; //node has been visited/ checked
         }
       if(currNode->west != NULL && !currNode->west->flag) //opening left...
            {
            currNode->west->previousNode = currNode;
            q.enqueue(currNode->west);
            currNode->flag = true;
         }
      if(currNode->south != NULL && !currNode->south->flag) //opening down...
           {
            currNode->south->previousNode = currNode;
            q.enqueue(currNode->south);
            currNode->flag = true;
           }

      }

     node* pathNode = q.head(); //sets pathNode pointer to position of finish

     //until x,y of pathnode are 0,19 (at beginnning), backtrack from finish to start

     while(!(pathNode->xN == 0 && pathNode->yN == 19))
     {
            pathNode->timesVisited = -99; //mark path from finish to start with -99 (least visited)
            pathNode = pathNode->previousNode; //pathnode points to previous node, goes back in path, continues

      }
     pathNode->timesVisited = -99;

}
void microMouseServer::studentAI()
{
   static int counterR = 0, counterL = 0; //for ending, counts how many times mouse turnsRight and moveForward
   static int x=0, y=19;    //shows in bottom left corner of array
   static int dir = 0;
   static node mazeMap[20][20]; //map of nodes
   static int timesRun = 0;

   //creates links between nodes when no wall separates
   switch (dir){
    case 0: //forward
      {
       if(!isWallForward())
          {
           mazeMap[x][y].north = &(mazeMap[x][y-1]); //north of node becomes upper node
           mazeMap[x][y-1].south = &(mazeMap[x][y]); //south of upper node becomes lower node
           }
        if (!isWallRight())
       {
           mazeMap[x][y].east = & (mazeMap[x+1][y]);
           mazeMap[x+1][y].west = &(mazeMap[x][y]);
        }
        if(!isWallLeft())
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
          mazeMap[x][y].east = &(mazeMap[x+1][y]);
          mazeMap[x+1][y].west = &(mazeMap[x][y]);
       }
       if(!isWallRight())
        {
           mazeMap[x][y].south = &(mazeMap[x][y+1]);
           mazeMap[x][y+1].north = &(mazeMap[x][y]);
        }
       if(!isWallLeft())
       {
           mazeMap[x][y].north = &(mazeMap[x][y-1]);
           mazeMap[x][y-1].south = &(mazeMap[x][y]);
       }
       break;
      }
     case 2: //down
     {
       if(!isWallForward())
       {
           mazeMap[x][y].south = &(mazeMap[x][y+1]);
           mazeMap[x][y+1].north = &(mazeMap[x][y]);
       }
       if(!isWallRight())
       {
           mazeMap[x][y].west = &(mazeMap[x-1][y]);
           mazeMap[x-1][y].east = &(mazeMap[x][y]);
       }
      if(!isWallLeft())
       {
           mazeMap[x][y].east = &(mazeMap[x+1][y]);
           mazeMap[x+1][y].west = &(mazeMap[x][y]);
        }
       break;
      }
     case 3: //left
      {
        if(!isWallForward())
        {
            mazeMap[x][y].west = &(mazeMap[x-1][y]);
            mazeMap[x-1][y].east = &(mazeMap[x][y]);
         }
        if(!isWallRight())
        {
            mazeMap[x][y].north = &(mazeMap[x][y-1]);
            mazeMap[x][y-1].south = &(mazeMap[x][y]);
         }
        if(!isWallLeft())
        {
            mazeMap[x][y].south = &(mazeMap[x][y+1]);
            mazeMap[x][y+1].north = &(mazeMap[x][y]);
        }
        break;
     }
  }

   //ISLANDED ALGORITHM ------------------------------------

   if (!isWallLeft() && !(!isWallForward() && (numberOfTimesForward(dir, x, y,mazeMap) < numberOfTimesLeft(dir,x,y,mazeMap))) &&
                         !(!isWallRight() && (numberOfTimesRight(dir, x, y,mazeMap) < numberOfTimesLeft(dir,x,y,mazeMap)) ))
    {
       turnLeft();
       myTurnLeft(&dir);
       counterR = 0;
       counterL++;
     }

     else if (!isWallForward() && !(!isWallRight() && (numberOfTimesForward(dir, x, y,mazeMap) > numberOfTimesRight(dir, x, y,mazeMap)) ))
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

       else //dead end
       {
           turnLeft();
           myTurnLeft(&dir);
           turnLeft();
           myTurnLeft(&dir);
           counterR = 0;
           counterL= 0;
       }

   mazeMap[x][y].xN = x; //sets x,y of node to x,y of array
   mazeMap[x][y].yN = y;
   moveForward();
   myMoveForward(&x, &y, &dir, mazeMap);


   //finish
    if (counterR > 2 || counterL > 2 )
       {
         mazeMap[x][y].finished = true;

         if (timesRun == 0)
         {
            findShortestPath(mazeMap);
         }

        foundFinish();
        timesRun++;

        x = 0;
        y = 19;
        dir = 0;
        counterR = 0;
        counterL = 0;
       }

}
