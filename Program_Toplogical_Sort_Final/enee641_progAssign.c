#include <stdio.h>
#include <string.h>
#include "myFunctions.h"
#include "queue.h"


int A[100],G[255][255],inDegree[255];//topSort[100],//count=0;

int main()
{
  struct vertex V[100];
  struct edge E[10000];
  struct vertex tempV;
  struct edge tempE;
  //struct vertex graph[100];
  //root=graph;
  int i=0,j=0;
  //initGraph(G);
  initInDegree(inDegree);
  i=0,j=0;
  readFile("in1.txt",G,V,E); // Read file and create a graph
  printf("\nPrinting the G Matrix:\n");
  //printGraph(G);
  findInDegree(V,inDegree);
  //creatGraph(V,E,G);
  printf("\nPrinting the Graph:\n");
  for(i=0;i<noVer;i++)
   // printVertex(V[i]);
  //check the inDegree
  for(i=0;i<noVer;i++)
  {
      if(inDegree[i]==0)
      {
          qInsert(i+1);
      }
  }
  int verX;
  while(last!=first)
  {
      topSort[count] = qDelete();
      verX = topSort[count]-1;
      if(V[verX].next!=NULL)
      {
          tempE=*V[verX].next;
          inDegree[tempE.v-1]--;
          if(inDegree[tempE.v-1]==0)
                qInsert(tempE.v);
           while(tempE.next!=NULL)
           {
                tempE=*tempE.next;
                inDegree[tempE.v-1]--;
                if(inDegree[tempE.v-1]==0)
                    qInsert(tempE.v);
           }
      }
      count++;
  }
  printf("\nTopological Sorted List:\n");
  if(count == noVer)
    for(i=0;i<noVer;i++)
        printf("%d ",topSort[i]);
  else
        printf("\nWe have a cycle in the Graph!");
  writeFile("output.txt");
  return 0;
}
