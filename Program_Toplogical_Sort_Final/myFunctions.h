#ifndef MYFUNCTIONS_H_INCLUDED
#define MYFUNCTIONS_H_INCLUDED
int noVer,E,noValidEdges,topSort[100],count=0;;

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
    struct edge *next;
};

struct edge setEdge(struct edge e,int u,int v)
{
    e.u = u;
    e.v = v;
    e.next = NULL;
    return e;
}
struct vertex setVertex(struct vertex v,int value,int inDegree)
{
    v.value = value;
    v.inDegree = inDegree;
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

/*
void creatGraph(struct vertex *V,struct edge *E, int G[255][255])
{
   int i=0,j=0;
   int noEdges=-1;
   struct vertex newVer;
   struct edge newEdge;
   //newVer = V[i];
   for(i=0;G[i][j]!=-1;)
   {
        V[i]=setVertex(newVer,i+1,-1);
        for(j=1;G[i][j]!=-1;j++)
        {
            //V[i]=setValues(newVer,i,-1);
            if(j==1)
            {
                    E[noEdges+1]=setEdge(newEdge,i+1,G[i][j]);
                    V[i].next = &E[noEdges+1];
                    //noEdges++;
            }
            else
            {
                    E[noEdges+1]=setEdge(newEdge,i+1,G[i][j]);
                    E[noEdges].next = &E[noEdges+1];
                    //noEdges++;
            }
            noEdges++;
            if(G[i][j]==-1) break;
        }
        j=0;
        i++;
        if(G[i][j]==-1) break;
   }
   noValidEdges = noEdges;
   return ;
}
*/

void initInDegree(int inDegree[])
{
    int i=0;
    for(i=0;i<255;i++)
        inDegree[i]=0;
}
/*
void findInDegree(int G[255][255],int inDegree[])
{
   int i=0,j=0;

   for(i=0;G[i][j]!=-1;)
   {
    for(j=0;G[i][j]!=-1;j++)
    {
        inDegree[G[i][j]-1]++;
        if(G[i][j]==-1) break;
    }
    j=0;
    i++;
    if(G[i][j]==-1) break;
  }
  int sum=0;
  for(i=0;inDegree[i]!=-1;i++)
  {

    printf("inDegree[%d]:%d \n",i,inDegree[i]);
    sum+=inDegree[i];
  }
  printf("Total Edges inDegree! : %d\n",sum);
}*/

void findInDegree(struct vertex *V,int* inDegree)
{
   struct vertex newVer;
   struct edge newEdge;
   int i=0,j=0;
   newVer = V[0];
   for(i=0;i<noVer;i++)
   {
       //inDegree[V[i].value]++;
       if(V[i].next!=NULL)
       {
            newEdge = *V[i].next;
            inDegree[newEdge.v-1]++;
            while(newEdge.next!=NULL)
            {
                newEdge = *newEdge.next;
                inDegree[newEdge.v-1]++;
            }
       }
   }
   //int sum=0;
   //for(i=0;i<noVer;i++)
   //{
    // printf("inDegree[%d]:%d \n",i,inDegree[i]);
     //sum+=inDegree[i];
   //}
  // printf("Total Edges inDegree! : %d\n",sum);
}

/*
void initGraph(int G[255][255])
{
    int i=0,j=0;
    for(i=0;i<255;i++)
    for(j=0;j<255;j++)
        G[i][j]=-1;
}*/
/*
void printGraph(int G[255][255])
{
   int i=0,j=0;
   for(i=0;G[i][j]!=-1;)
   {
    for(j=0;G[i][j]!=-1;j++)
    {
        printf("%d  ",G[i][j]);
        if(G[i][j]==-1) break;
    }
    printf("\n");
    E+=(j-1);
    j=0;
    i++;
    if(G[i][j]==-1) break;
  }
  printf("\nNumber of Vertices: %d",(noVer=i));
  printf("\nNumber of  Edges: %d \n",E);
}
*/
void readFile(char fileName[],int G[255][255],struct vertex *V, struct edge *E)
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
    fp3 = fopen("temp.txt","r+");
    //puts(str);
    fprintf(fp3,"%s",str);
    fprintf(fp3,"%d\n",-1);
    fclose(fp3);
    fp3 = fopen("temp.txt","r");
    fscanf (fp3, "%d", &temp);
    i=0;
    while (temp != -1)
    {
      //G[j][i++]=temp;
      G[j][i]=temp;
      if(i==0)
      {
                V[j]=setVertex(newVer,j+1,-1);
      }
      else
      {
          if(i==1)
          {
                E[noEdges+1]=setEdge(newEdge,i+1,G[j][i]);
                V[j].next = &E[noEdges+1];
          }
          else
          {
                E[noEdges+1]=setEdge(newEdge,i+1,G[j][i]);
                E[noEdges].next = &E[noEdges+1];
          }
          noEdges++;
      }
      i++;
      //printf ("G[%d][%d] = %d ",j,i,G[j][i-1]);
      fscanf (fp3, "%d", &temp);
    }
    G[j][i++]=temp;
    //printf ("G[%d][%d] = %d ",j,i,temp);
    j++;
    fclose(fp3);
    //printf("\n");
  }
  noVer=j;
  G[j][i++]=-1;
  //printf ("G[%d][%d] = %d ",j,i,-1);
}


void writeFile(char fileName[])
{
    FILE *output = fopen(fileName,"w");
    int i=0;
    if(noVer == count)
        for(i=0;i<noVer;i++)
            fprintf(output,"%d ",topSort[i]);
    else
            fprintf(output,"%s","We have a cycle in the graph!");
    fclose(output);
}

#endif // MYFUNCTIONS_H_INCLUDED
