#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define MAX 255
int Q[MAX],first=0,last=0;

void qInsert(int x)
{
    if(first==MAX-1)
        printf("The Queue is full!");
    else
    {
        Q[first++]=x;
    }
}

int qDelete()
{
    int x;
    if(last==first)
        printf("The Queue is Empty");
    else
    {
        x=Q[last++];
    }
    return x;
}

#endif // QUEUE_H_INCLUDED
