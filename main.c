
#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void main()

{
	void display(AVLTree T);
	void ShowTree(AVLTree t);
	AVLTreeNode* FindNode(AVLTree t, KeyType key);
	AVLTree T;
	//AVLTree *tp;
	int i = 0;
	DataType *data;
	srand((unsigned)time(NULL));
	T = NULL;

	int state = 0;
	int datas[5] = { 64, 50, 86, 78, 82 };

	for (i = 0; i < 10; i++)
	{
		data = (DataType*)malloc(sizeof(DataType));
		//data->key = datas[i];
		data->key = rand() % 100;
		printf("%d  ", data->key);
		AVLTree_insert(&T, data, &state);
	}

	printf("\n");
	display(T);
	ShowTree(T);
	printf("\n");
	int ch;
	while (1)
	{
		scanf("%d", &ch);
		getchar();
		AVLTreeNode* p = FindNode(T, ch);
		if (p != NULL)
			printf("p: %d  ×óº¢×Ó£º%d  ÓÒº¢×Ó£º%d\n", p->data->key, p->lchild == NULL ? -1 : p->lchild->data->key, p->rchild == NULL ? -1 : p->rchild->data->key);
		else
			printf("error");
	}

	getchar();

}

AVLTreeNode* FindNode(AVLTree t, KeyType key)
{

	if (t == NULL)
		return NULL;

	while (t != NULL)
	{
		if (t->data->key==key)
		{
			return t;
		}
		else if (t->data->key<key)
		{
			t = t->rchild;
		}
		else
		{
			t = t->lchild;
		}
	}
	return NULL;
		

}


void ShowTree(AVLTree t)
{

	if (NULL == t){
		printf("#");
		return 0;
	}
	else
		printf("%d", t->data->key);
	printf("(");
	ShowTree(t->lchild);
	printf(",");
	ShowTree(t->rchild);
	printf(")");

	return 0;
}
void display(AVLTree T)
{
	if (T->lchild != NULL)
		display(T->lchild);
	printf("%d  bf: %d  \n", T->data->key,T->bf);
	if (T->rchild != NULL)
		display(T->rchild);
}


struct NodeInfo
{
	int level;
	AVLTreeNode *node;
	int pos;
};




