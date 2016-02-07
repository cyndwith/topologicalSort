#ifndef MYFUNCTIONS_H_INCLUDED
#define MYFUNCTIONS_H_INCLUDED
#include "queue.h"
int noVer,E,noValidEdges,topSort[100],count=0,inDegree[255];

struct vertex{
    int value;
    int inDegree;
    int opr;
    struct edge *next;
};

struct edge{
    int value;
    int u;
    int v;
    int opr;
    struct edge *next;
};

struct edge setEdge(struct edge e,int u,int v)
{
    e.u = u;
    e.v = v;
    e.opr = 0;
    e.next = NULL;
    return e;
}
struct vertex setVertex(struct vertex v,int value,int inDegree)
{
    v.value = value;
    v.inDegree = inDegree;
    v.opr = 0;
    v.next = NULL;
    return v;
}

void printVertex(struct vertex root)
{
    int i=0;
    struct vertex v;
    struct edge e;
    v=root;
    printf("\n Vertex: %d",v.value);
    if(v.next!=NULL)
    {
        e=*v.next;
        printf(" %d",e.v);
        while(e.next!=NULL)
        {
            e = *e.next;
            printf(" %d",e.v);
            //e = *e.next;
        }
    }
    else
        printf(" No Edges!");
}


void initInDegree(int inDegree[])
{
    int i=0;
    for(i=0;i<255;i++)
        inDegree[i]=0;
}

void findInDegree(struct vertex *V,int* inDegree)
{
   struct vertex newVer;
   struct edge newEdge;
   int i=0,j=0;
   newVer = V[0];
   for(i=0;i<noVer;i++)
   {
       //inDegree[V[i].value]++;
       V[i].opr++;
       if(V[i].next!=NULL)
       {
            newEdge = *V[i].next;
            inDegree[newEdge.v-1]++; newEdge.opr++;
            while(newEdge.next!=NULL)
            {
                newEdge = *newEdge.next;
                inDegree[newEdge.v-1]++; newEdge.opr++;
            }
       }
   }
   /*
   int sum=0;
   for(i=0;i<noVer;i++)
   {
      printf("inDegree[%d]:%d \n",i,inDegree[i]);
      sum+=inDegree[i];
   }
   printf("Total Edges inDegree! : %d\n",sum);
   */
}


void readFile(char fileName[],struct vertex *V, struct edge *E)
{
  char str[255];
  struct vertex newVer;
  struct edge newEdge;
  FILE *fp = fopen(fileName,"r");
  FILE *fp2 = fopen(fileName,"r+");
  FILE *fp3 = fopen("temp.txt","r+");
  int temp = getc(fp2),noEdges;
  int i=0,j=0;
  while(fgets(str,255,fp)!=NULL)
  {
    fp3 = fopen("temp.txt","r+");//puts(str);
    fprintf(fp3,"%s",str);
    fprintf(fp3,"%d\n",-1);
    fclose(fp3);
    fp3 = fopen("temp.txt","r");
    fscanf (fp3, "%d", &temp);
    i=0;
    while (temp != -1)
    {
      if(i==0)
      {
                V[j]=setVertex(newVer,j+1,-1);
      }
      else
      {
          if(i==1)
          {
                E[noEdges+1]=setEdge(newEdge,i+1,temp);//G[j][i]);
                V[j].next = &E[noEdges+1];
          }
          else
          {
                E[noEdges+1]=setEdge(newEdge,i+1,temp);//G[j][i]);
                E[noEdges].next = &E[noEdges+1];
          }
          noEdges++;
      }
      i++;
      fscanf (fp3, "%d", &temp);
    }
    j++;
    fclose(fp3);
  }
  noVer=j;
  noValidEdges = noEdges;
}


void writeFile(char fileName[])
{
    FILE *output = fopen(fileName,"w");
    int i=0;
    if(noVer == count)
        for(i=0;i<noVer;i++)
            fprintf(output,"%d ",topSort[i]);
    else
            fprintf(output,"%s","This Graph has Cycle!");
    fclose(output);
}


void topologicalSort(struct vertex *V,struct edge *E)
{
      /* Insert into the Queue - values with with zero inDegree  */
      //struct vertex tempV;
      struct edge *tempE;
      int i;
      for(i=0;i<noVer;i++)
      {
          V[i].opr++;
          if(inDegree[i]==0)
          {
              V[i].opr++;
              qInsert(i+1);
          }
      }
      /* Check the graph using inDegree for zero Degree peeling */
      int verX;
      while(last!=first)
      {
          topSort[count] = qDelete();//verX = topSort[count]-1;
          V[topSort[count]-1].opr++;
          if(V[topSort[count]-1].next!=NULL)
          {
              //tempE=*V[topSort[count]-1].next;
              tempE=V[topSort[count]-1].next;
              //inDegree[tempE.v-1]--;  tempE.opr++; V[tempE.v-1].opr++;
              inDegree[tempE->v-1]--;  tempE->opr++; V[tempE->v-1].opr++;
              if(inDegree[tempE->v-1]==0){
                    //qInsert(tempE.v); tempE.opr++;  V[tempE.v-1].opr++;
                    qInsert(tempE->v); tempE->opr++;  V[tempE->v-1].opr++;
              }
               while(tempE.next!=NULL)
               {
                    tempE=tempE.next;
                    inDegree[tempE->v-1]--; tempE->opr++; V[tempE->v-1].opr++;
                    if(inDegree[tempE->v-1]==0){
                        qInsert(tempE->v);  tempE->opr++; V[tempE->v-1].opr++;
                    }

               }
          }
          count++;
      }
      /* Print the topological Sorted list of Vertices */
      printf("\nTopological Sorted List:\n");
      if(count == noVer)
      {
        int verOPR=0,edgeOPR=0;
        for(i=0;i<noVer;i++)
            printf("%d ",topSort[i]);
        for(i=0;i<noVer;i++)
        {
            verOPR +=V[i].opr;
            printf("\nVertex %d : %d",i+1,V[i].opr);
        }
        printf("\nTotal Vertex operations : %d\n",verOPR);
        printf("\nTotal Edges: %d\n",noValidEdges);
        for(i=0;i<noValidEdges;i++)
            printf("\nEdge from %d to %d: %d",E[i].u,E[i].v,E[i].opr);
      }
      else
            printf("\nThis Graph has Cycle!");
}

#endif // MYFUNCTIONS_H_INCLUDED
