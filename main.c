#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>



void main()
{
	void displayBinTree(AVLTree T);
	void menu();
	void insert(AVLTree *T);
	void delete(AVLTree T);
	void visit(DataType *data);
	void Traverse(AVLTree *T);
	void addRadom(AVLTree *T);
	void find(AVLTree *T);
	void TraverseTest(AVLTree T, Status(*visit)(AVLTree e));
	void testBf(AVLTree T);

	//int Test();
	//Test();
	//return;
	int n;
	n = 100055489;

	AVLTree T;
	int i = 0;
	DataType *data;
	srand((unsigned)time(NULL));
	T = NULL;

	//int state = 0;
	//int datas[16] = { 665, 177, 389, 90, 536, 879, 886, 740, 460, 16, 604, 885, 476, 632, 601, 470 };
	int datas[8] = { 644,205,901,159,337,896,944,57 };

	int state = 0;
	for (i = 0; i < 8; i++)
	{
		data = (DataType*)malloc(sizeof(DataType));
	
		data->key = datas[i];//rand() % 100;
		printf("%d  ", data->key);
		AVLTree_insert(&T, data, &state);
	}
	menu();
	char ch;

	while (1)
	{
		printf("\n请输入相应的操作命令:");
		ch = -1;
		scanf("%c", &ch);
		if (getchar() != '\n')
		{
			printf("操作失败，请重新输入:\n");
			while (getchar() != '\n');
			continue;
		}
		switch (ch)
		{
		case 'e':return;
		case 's':displayBinTree(T); TraverseTest(T, testBf); break;
		case 'c':system("cls"); break;
		case 'm':menu(); break;
		case 'a':insert(&T); displayBinTree(T); TraverseTest(T, testBf); break;
		case 'd':delete(&T); displayBinTree(T); TraverseTest(T, testBf); break;
		case 'b':Traverse(&T); break;
		case 'x':AVLTree_destroy(T); T = NULL; printf("销毁成功\n"); break;
		case 'r':addRadom(&T); TraverseTest(T, testBf); break;
		case 'f': find(T); break;
		//case 't':TraverseTest(T, testBf); break;
		default:
			printf("操作失败\n");
		}
	}

}
//查找测试
void find(AVLTree T)
{
	int input(const int max);
	int transform(char *str);

	int num = 0;
	int taller = 0;
	printf("请输入要查找的关键字（9位数以内）：\n");

	
	num = input(9);

	AVLTreeNode *node = NULL;
	
	node = AVLTree_search(T, num);
	if (node)
	{
		printf("查找成功，当前结点为%d \n", node->data->key);
		printf("左孩子:");
		if (node->lchild != NULL)
			printf("%d    ", node->lchild->data->key);
		else
			printf("不存在   ");
		printf("右孩子:");
		if (node->rchild != NULL)
			printf("%d    \n", node->rchild->data->key);
		else
			printf("不存在   \n");
	}
	else
		printf("找不到结点");


}
//随机插入测试
void addRadom(AVLTree *T)
{
	int i,taller=0,num;
	DataType* data;
	srand((unsigned)time(NULL));
	printf("请输入加入的随机的个数(二位数以内):\n");
	
	num = input(2);

	for (i = 0; i < num; i++)
	{
		data = (DataType*)malloc(sizeof(DataType));

		data->key = rand() % 1000;
		printf("%d  ", data->key);
		AVLTree_insert(T, data, &taller);
	}
	printf("加入成功\n");
}
//删除操作测试
void delete(AVLTree *T)
{
	DataType* data = NULL;
	int num = 0;
	int taller = 0;
	data = (DataType*)malloc(sizeof(DataType));
	printf("请输入要删除的数（9位数以内）：\n");

	num = input(9);

	data->key = num;
	deleteAVL(T, num, &taller);

	/*if (OK == AVLTree_delete(T, num, &taller))
		printf("删除成功 \n");
	else
		printf("删除失败! \n");*/
}
//插入操作测试
void insert(AVLTree *T)
{
	DataType* data = NULL;
	int num = 0;
	int taller = 0;
	data = (DataType*)malloc(sizeof(DataType));
	while (1)
	{
		printf("请输入要插入的数（9位数以内）：\n");

		num = input(9);
		data->key = num;
		if (OK == AVLTree_insert(T, data, &taller))
		{
			printf("插入成功!\n");
			break;
		}
		else
		{
			printf("插入失败!\n");
			break;
		}
	}
}
//遍历操作测试
void Traverse(AVLTree *T)
{
	void testBf(AVLTree T);
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
//遍历时的访问函数
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
	printf("   树的深度为%d                       平衡因子\n", dep);
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
				level[top] = n + 5;
			}
			if (p->lchild != NULL)
			{
				top++;
				stack[top] = p->lchild;
				level[top] = n + 5;
			}
		}
	}
}

//请求输入函数，只能输入数字
//max 能输入最大位数
//返回用户输入的数
int input(const int max)
{
	char c;           //存放临时接收的字符
	char *s;          //存放输入字符串
	int n = 0;        //字符串数组下标

	s = malloc(max*sizeof(max + 1));
	rewind(stdin);
	while (1)
	{
		c = getchar();
		if (c == '\n')
			break;
		if (c!='-'&&(c<48||c>57)) //如果用户输入不为负号且不为数字
		{
			printf("请输入有效的数字\n");
			n = 0;
			rewind(stdin);
			continue;
		}
		if (n>max)
		{
			printf("请保持数字位数在%d位数以内\n",max);
			rewind(stdin);
			n = 0;
			continue;
		}
		
		s[n] = c;
		n++;
	}
	s[n] = '\0';

	//将字符转为int型
	int num = 0, k = 1;
	int len = 0;
	while (s[len++] != '\0');
	len = len - 2;
	while (len >= 0)
	{
		num += (s[len--] - 48)*k;
		k = k * 10;
	}
	return num;
}
//检测结点平衡因子是否有错
void testBf(AVLTree T)
{
	int l, r;
	l = AVLTree_level(T->lchild);
	r = AVLTree_level(T->rchild);
	if (T->bf!=l-r)
	{
		printf("\n结点%d有错！！！！！！\n ", T->data->key);
	}
}
//递归遍历所有结点检测平衡因子是否有错
void TraverseTest(AVLTree T, Status(*visit1)(AVLTree e))
{
	if (!T)
	{
		return ERROR;
	}
	visit1(T);
	if (T->lchild != NULL)
	{
		TraverseTest(T->lchild, visit1);
	}
	if (T->rchild != NULL)
	{
		TraverseTest(T->rchild, visit1);
	}
	return OK;
}