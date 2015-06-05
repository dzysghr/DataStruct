
#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>





void main()
{
	void display(AVLTree T);
	AVLTree T;
	//AVLTree *tp;
	int i = 0;
	DataType *data;
	srand((unsigned)time(NULL));
	T = NULL;
	/*tp = &T;
	printf("%d  %d  ", *tp,&T);
	getchar();*/
	//return 0;
	int state = 0;
	int datas[5] = { 65, 79, 45, 52, 49 };

	for (i = 0; i < 5; i++)
	{
		//AVLTree_init();
		data = (DataType*)malloc(sizeof(DataType));
		data->key = datas[i]; //rand() % 100;

		printf("%d  ", data->key);
		AVLTree_insert(&T, data, &state);
	}


	printf("\n");

	display(T);

	getchar();
	//getchar();
}
void display(AVLTree T)
{
	if (T->lchild != NULL)
		display(T->lchild);
	printf("%d  bf: %d  \n", T->data->key,T->bf);
	if (T->rchild != NULL)
		display(T->rchild);

}