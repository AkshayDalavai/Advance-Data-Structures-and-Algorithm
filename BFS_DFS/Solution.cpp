//Akshay Dalavai


#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<stack>
#include<queue>
#include<list>

using namespace std;

class cell { public:
int id;
int wall;
bool visited;
bool in_structure;
int from;
//design your constructor
cell()
{
   id = -1;
   wall = -1;
   visited = false;
   in_structure = false;
   from = -1;
}
int move(int d, int w, int p)
{
   int new_id =-1;
   switch(d)
   {
       case 1: if((w&d) == d)
       {
           new_id = -2;
       }
       else
       {
           new_id = id +p;
       }
       break;

       case 2: if((w&d) == d)
       {
           new_id = -2;
       }
       else
       {
           new_id = id + 1;
       }
       break;

       case 4: if((w&d) ==d)
       {
           new_id = -2;
       }
       else
       {
            new_id = id - p;
       }
       break;

       case 8: if((w&d)==d)
       {
           new_id = -2;
       }
       else
       {
           new_id = id - 1;
       }
       break;
       default : new_id =-2;
       break;    

   }
   if (new_id < 0 || new_id > ((p*p)-1))
       {
           return -2;
       }
       else
       {
           return new_id;
       }


}
};

void DFS(vector<cell> &maze, int n, int start, int end);
void BFS(vector<cell> &maze, int n, int start, int end);
void maze(int &StartingCell, int &EndingCell);
void print(vector<cell> &maze, int s,int e,int n);
void resetmaze(vector<cell> &maze,int n);

int main()
{
   ifstream in("maze.txt");
   int NumberOfCell;
   in>>NumberOfCell;
   vector<cell> maze(NumberOfCell);
   int StartingCell, EndingCell;  
   in>>StartingCell>>EndingCell;
   int value;

   for(int i = 0; i<NumberOfCell; i++)
   {
       in>>value;
       maze[i].id = i;  
       maze[i].wall = value;
       maze[i].visited = false;
       maze[i].in_structure = false;
       maze[i].from = -1;
   }
   in.close();
   DFS(maze,NumberOfCell,StartingCell,EndingCell);
   resetmaze(maze,NumberOfCell);
   BFS(maze, NumberOfCell,StartingCell, EndingCell);
   return 0;
}

void resetmaze(vector<cell> &maze,int n)
{
   for(int i = 0; i<n; i++)
   {
       maze[i].id = i;
       maze[i].visited = false;
       maze[i].in_structure = false;
       maze[i].from = -1;
   }
}
void DFS(vector<cell> &maze, int n, int start, int end)
{
   stack<int> DFS_stack;
   int wallvalue;
   int pos = sqrt(n);
   bool sol_found = false;
   DFS_stack.push(start);
   maze[start].in_structure = true;
   while(DFS_stack.empty() == false)
   {
       cell obj;
       obj.id = DFS_stack.top();
       if(obj.id == end)
       {
           break;
       }
       DFS_stack.pop();
       obj.visited = true;
       wallvalue = maze[obj.id].wall;
       obj.wall = wallvalue;


       for(int i=1; i<=8; i=i*2)
       {
           int new_id = obj.move(i,wallvalue,pos);
           if(new_id != -2 && maze[new_id].visited == false && maze[new_id].in_structure == false)
           {
               DFS_stack.push(new_id);
               maze[new_id].from = obj.id;
               maze[new_id].visited = true;
           }
           if(new_id == end)
           {
               sol_found = true;
               break;
           }

       }
   }
   if(sol_found == true)
   {
       cout <<"Target is reached!" << endl;
       cout << "The output path of the DFS is as below :" << endl;
       print(maze,start,end,n);
   }
   else
   {
       cout << "No solution is possible" << endl;
   }

}

void BFS(vector<cell> &maze, int n, int start, int end)
{
   queue<int> BFS_Queue;
   int wallvalue;
   int pos = sqrt(n);
   bool sol_found = false;
   BFS_Queue.push(start);
   maze[start].in_structure = true;
   while(BFS_Queue.empty() == false)
   {
       cell objQ;
       objQ.id = BFS_Queue.front();
       if(objQ.id == end)
       {
           break;
       }
       BFS_Queue.pop();
       objQ.visited = true;
       wallvalue = maze[objQ.id].wall;
       objQ.wall = wallvalue;

       for(int i=1; i<=8; i=i*2) //Four directions to move 8421
       {
           int new_id = objQ.move(i,wallvalue,pos);
           if(new_id != -2 && maze[new_id].visited == false && maze[new_id].in_structure == false)
           {
               BFS_Queue.push(new_id);
               maze[new_id].from = objQ.id;
               maze[new_id].visited = true;
           }
           if(new_id == end)
           {
               sol_found = true;
               break;
           }

       }
   }
   if(sol_found == true)
   {
       cout <<"Target is reached!" << endl;
       cout << "The output path of the BFS is as below :" << endl;
       print(maze,start,end,n);
   }
   else
   {
       cout << "No solution is possible" << endl;
   }
}

void print(vector<cell> &maze, int s, int e,int n)
{
  int value;
  list<int> path;
  path.push_front(e);
  while(maze[e].from != -1)
  {

      value = maze[e].from;
      path.push_front(value);
      e = value;
  }

  int count = 0;

     list <int> :: iterator it; 
   for(it = path.begin(); it != path.end(); ++it) 
   {
       if(std::distance( it, path.end() ) != 1 )
        cout << *it<< "-->" ; 
       else
       cout << *it;
   }

   cout << '\n'; 
  for(int i = 0;i<sqrt(n);i++){
   for (int j =0;j<sqrt(n);j++){
       if (std::find(path.begin(), path.end(),count)!=path.end()){

           cout<<"*";

       }
       else{
           cout<<"-";

       }
       count ++;
   }
   cout<<endl;
  }






} 

/* Generated one meaningful 20 by 20 maze as below:
400
0
399
8 6 12 6 12 6 14 14 14 13 5 4 5 6 14 13 4 5 5 6 10 9 3 15 2 10 10 10 9 4 6 8 6 9 0 4 2 
12 6 11 8 5 4 3 9 11 10 9 5 3 10 8 0 5 2 8 1 0 0 7 10 13 0 5 7 12 1 4 5 5 2 10 8 6 8 0 
4 2 10 12 10 12 3 13 6 10 12 10 12 5 3 0 3 13 2 9 3 8 3 11 10 9 5 5 1 2 10 11 8 5 4 11 1
2 4 10 9 6 11 12 14 9 4 5 5 7 11 8 7 8 6 8 4 0 3 9 4 0 5 1 2 14 10 12 4 5 4 2 13 2 10 8 2 
8 5 4 0 2 12 7 10 10 10 8 2 12 9 1 5 11 10 8 2 8 6 10 9 3 10 12 3 10 10 9 3 9 5 5 5 5 2 9 
1 0 1 0 4 5 1 0 2 10 8 5 6 12 6 12 5 5 3 12 6 8 5 2 10 12 5 0 2 11 10 12 10 8 2 9 5 5 5 1 
2 9 5 1 0 9 6 9 2 13 3 10 11 10 8 4 5 4 5 6 9 5 5 6 8 6 9 6 11 13 4 1 5 3 8 2 12 0 4 2 15 
15 15 10 9 2 14 8 6 14 10 13 4 6 9 8 2 8 2 10 13 5 4 1 7 11 10 10 10 8 0 4 1 3 12 10 9 2 
8 8 12 6 9 4 5 7 10 8 3 10 10 8 4 4 2 9 7 11 9 5 1 1 7 10 12 4 10 9 7 8 1 2 9 1 0 7 12 5 
5 5 5 5 5 3 8 2 8 5 6 8 4 0 4 6 10 12 2 13 5 5 5 5 5 5 1 3 10 14 10 11 11 1 1 3 11 11 9 5 
5 5 5 5 5 5 5 5 3 11 10
*/
