#include "cqueue.h"
#include <stdlib.h>
#include <stdio.h>


int InitQueue(SqQueue *Q)
{
	if((Q->base = (ElemType *)malloc(MAXQSIZE))==NULL)
	{
		return -1;
	}
	Q->front = 0;
	Q->maxSize = MAXQSIZE;
	Q->rear = 0;
	Q->tag = 0;
	return 0;

}


int ClearQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	Q->tag = 0;
	return 0;
}

int QueueEmpty(SqQueue *Q)
{
	if (Q->base==NULL)
	{
		return -1;
	}
	if (Q->front==Q->rear&&Q->tag==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int QueueLength(SqQueue *Q)
{
	if (Q->base==NULL)
	{
		return -1;
	}
	if (Q->tag==1)
	{
		return Q->maxSize;
	}

	return (Q->rear - Q->front + Q->maxSize) % Q->maxSize;
}


int EnQueue(SqQueue *Q, ElemType e)
{
	if (Q->base==NULL||Q->tag==1)
	{
		return -1;
	}

	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % Q->maxSize;
	if (Q->rear == Q->front)
	{
		Q->tag = 1;
	}
	return 0;
}

int DeQueue(SqQueue *Q, ElemType *e)
{
	if (QueueEmpty(Q))
	{
		return -1;
	}
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % Q->maxSize;
	if (Q->tag==1)
	{
		Q->tag = 0;
	}
	return 0;
}


int GetHead(SqQueue *Q, ElemType *e)
{
	if (QueueEmpty(Q)==1)
	{
		return -1;
	}

	*e = Q->base[Q->front];
	
	return 0;
}