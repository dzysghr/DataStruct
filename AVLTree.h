#ifndef AVLTREE
#define AVLTREE
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define EH 0
#define LH 1
#define RH -1

#define TRUE 1
#define FALSE 0

#define KeyType int


typedef struct Data{
	KeyType key;
	int num;
}DataType;



typedef struct AVLTreeNode{
	DataType *data;
	int bf;
	struct AVLTreeNode *lchild, *rchild;

} *AVLTree, AVLTreeNode;

Status AVLTree_init();
Status AVLTree_destroy(AVLTree T);
Status AVLTree_search(AVLTree T,const KeyType key,DataType **e);
Status AVLTree_insert(AVLTree *T, DataType *e,Status *taller);
Status AVLTree_delete(AVLTree *T,KeyType key,DataType *e);

Status InOrderTraverse(AVLTree T, Status(*visit)(DataType e));
Status PreOrderTraverse(AVLTree T, Status(*visit)(DataType e));


void R_Rotate(AVLTree *T);
void L_Rotate(AVLTree *T);
void LeftBalance(AVLTree *T);
void RightBalance(AVLTree *T);

#endif