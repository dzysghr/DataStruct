#ifndef CQUEUE_H
#define CQUEUE_H
//À≥–Ú—≠ª∑∂”¡–

#define MAXQSIZE 5

typedef struct
{
	int data;
}ElemType;

typedef struct
{
	ElemType *base;
	int front;
	int rear;
	int tag;
	int maxSize;
}SqQueue;

int InitQueue(SqQueue *Q);

int ClearQueue(SqQueue *Q);

int QueueEmpty(SqQueue *Q);

int QueueLength(SqQueue *Q);

int EnQueue(SqQueue *Q, ElemType e);

int DeQueue(SqQueue *Q, ElemType *e);

int GetHead(SqQueue *Q, ElemType *e);


















#endif