#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>



void main()
{
	void displayBinTree(AVLTree T);
	void print(AVLTree t, int n);
	void display(AVLTree T);
	void ShowTree(AVLTree t);
	void menu();
	void insert(AVLTree *T);
	void delete(AVLTree T);
	void visit(DataType *data);
	void Traverse(AVLTree *T);
	void addRadom(AVLTree *T);

	AVLTree T;
	int i = 0;
	DataType *data;
	srand((unsigned)time(NULL));
	T = NULL;

	int state = 0;

	for (i = 0; i < 10; i++)
	{
		data = (DataType*)malloc(sizeof(DataType));
	
		data->key = rand() % 100;
		printf("%d  ", data->key);
		AVLTree_insert(&T, data, &state);
	}
	menu();
	char ch;
	
	while (1)
	{
  	
		ch = -1;
		scanf("%c", &ch);
		if (getchar() != '\n')
		{
			printf("Erro!!!please enter again:\n");
			while (getchar() != '\n');
			continue;
		}
		switch (ch)
		{
		case 'e':return;
		case 's':displayBinTree(T); break;
		case 'c':system("cls"); break;
		case 'm':menu(T); break;
		case 'a':insert(&T); break;
		case 'd':delete(&T); break;
		case 'b':Traverse(&T); break;
		case 'x':AVLTree_destroy(T); T = NULL; break;
		case 'r':addRadom(T); break;
		}
	}
	

}

void addRadom(AVLTree *T)
{
	int i,taller=0,n;
	DataType* data;
	srand((unsigned)time(NULL));
	printf("请输入加入的随机的个数:\n");
	scanf("%d", &n);
	getchar();
	for (i = 0; i < n; i++)
	{
		data = (DataType*)malloc(sizeof(DataType));

		data->key = rand() % 100;
		printf("%d  ", data->key);
		AVLTree_insert(&T, data, &taller);
	}
	printf("加入成功\n");
}
void delete(AVLTree *T)
{
	DataType* data = NULL;
	int num = 0;
	int taller = 0;
	data = (DataType*)malloc(sizeof(DataType));
	while (1)
	{
		printf("please enter the number you want to delete：\n");
		scanf("%d", &num);
		getchar();
		data->key = num;
		if (OK == AVLTree_delete(T, num, &taller))
		{
			printf("delete susseed!\n");
			break;
		}
		else
		{
			printf("delete fail! \n");
			break;
		}
	}
}
void insert(AVLTree *T)
{
	DataType* data = NULL;
	int num = 0;
	int taller = 0;
	data = (DataType*)malloc(sizeof(DataType));
	while (1)
	{
		printf("please enter the number you want to insert：\n");
		scanf("%d", &num);
		getchar();
		data->key = num;
		if (OK == AVLTree_insert(T, data, &taller))
		{
			printf("insert susseed!\n");
			break;
		}
		else
		{
			printf("insert fail !");
			break;
		}
	}
}
void Traverse(AVLTree *T)
{
	printf("先序遍历：");
	PreOrderTraverse(*T, visit);
	printf("\n");
	printf("中序遍历：");
	InOrderTraverse(*T, visit);
	printf("\n");
	printf("后序遍历：");
	PostOrderTraverse(*T, visit);
	printf("\n");

}
void visit(DataType *data)
{
	printf("%d  ", data->key);
}


//菜单显示
void menu()
{
	
	printf("\n************************************************\n");
	printf("*         平衡二叉树测试程序                   *\n");
	printf("*     可以使用以下命令来执行相关操作           *\n");
	printf("*                                              *\n");
	printf("*     插入数据： a          删除数据： d       *\n");
	printf("*                                              *\n");
	printf("*     查找数据： f          显示所有结点：s    *\n");
	printf("*                                              *\n");
	printf("*     随机加入n个结点：r    显示菜单 :m        *\n");
	printf("*                                              *\n");
	printf("*     遍历所有节点  b       销毁二叉树 x       *\n");
	printf("*                                              *\n");
	printf("*     清除屏幕内容：c                          *\n");
	printf("*                                              *\n");
	printf("*     退出程序：e                              *\n");
	printf("************************************************\n");

}
//凹入表显示
void displayBinTree(AVLTree T)
{
	AVLTree stack[100], p;
	int level[100], top=0, n, i;
	int dep;
	if (!T)
	{
		printf("当前二叉树为空树\n");
	}
	dep = AVLTree_level(T);
	printf("树的深度为%d\n", dep);
	if (T != NULL)
	{
		top = 1;
		stack[top] = T;
		level[top] = 3;
		while (top>0)
		{
			p = stack[top];
			n = level[top];
			for (i = 1; i <= n; i++)
				printf(" ");
			printf("%d", p->data->key);
			for (i = n + 1; i<70 - n; i += 2)
				printf("-");
			printf(" ( %d )", p->bf);
			printf("\n");
			top--;

			if (p->rchild != NULL)
			{
				top++;
				stack[top] = p->rchild;
				level[top] = n + 4;
			}
			if (p->lchild != NULL)
			{
				top++;
				stack[top] = p->lchild;
				level[top] = n + 4;
			}
		}
	}
}





