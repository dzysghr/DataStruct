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


//用户数据类型，为方便测试只有一个成员并作为关键字
typedef struct Data{
	KeyType key;   //关键字
	
}DataType;



typedef struct AVLTreeNode{
	DataType *data;
	int bf;
	struct AVLTreeNode *lchild, *rchild;

} *AVLTree, AVLTreeNode;



//销毁平衡二叉树
void AVLTree_destroy(AVLTree T);

//搜索关键字为key的树节点
AVLTreeNode* AVLTree_search(AVLTree T, const KeyType key);

//插入数据
Status AVLTree_insert(AVLTree *T, DataType *e,Status *taller);
//删除关键字为key的数据
Status AVLTree_delete(AVLTree *T,KeyType key,int taller);
//返回树的深度
int AVLTree_level(AVLTree T);

//关键字比较函数
//key1>key2 return 1
//key1<key2 return -1
//key==key2 return 0
int Compare(const KeyType key1,const KeyType key2);


Status InOrderTraverse(AVLTree T, Status(*visit)(DataType *e));
Status PreOrderTraverse(AVLTree T, Status(*visit)(DataType *e));
Status PostOrderTraverse(AVLTree T, Status(*visit)(DataType *e));

void R_Rotate(AVLTree *T);
void L_Rotate(AVLTree *T);
void LeftBalance(AVLTree *T);
void RightBalance(AVLTree *T);

#endif