#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>




//查找操作
AVLTreeNode* AVLTree_search(AVLTree T, const KeyType key)
{
	if (T == NULL)
		return T;
	while (T)
	{
		if (Compare(T->data->key,key)==0)
			break;
		else if (T->data->key > key)
			T = T->lchild;
		else
			T = T->rchild;

	}
	return T;
}

//比较操作
int Compare(const KeyType key1, const KeyType key2)
{
	if (key1 > key2)
	{
		return 1;
	}
	if (key1<key2)
	{
		return -1;
	}
	return 0;
}

//右旋
void R_Rotate(AVLTree *T)
{
	AVLTreeNode *lc;
	lc = (*T)->lchild;
	(*T)->lchild = lc->rchild;
	lc->rchild = (*T);
	(*T) = lc;
}

//左旋
void L_Rotate(AVLTree *T)
{
	AVLTreeNode *rc;
	rc = (*T)->rchild;
	(*T)->rchild = rc->lchild;
	rc->lchild = (*T);
	(*T) = rc;
}
//左平衡处理
void LeftBalance(AVLTree *T)
{
	AVLTreeNode *lc, *rc;
	lc = (*T)->lchild;
	 switch (lc->bf)
	 {
	 case LH:
		 (*T)->bf = lc->bf = EH;
		 R_Rotate(T); break;
	 case RH:
		 rc = lc->rchild;
		 switch (rc->bf)
		 {
		 case LH:(*T)->bf = RH; lc->bf = EH; break;
		 case RH:(*T)->bf = EH; lc->bf = LH; break;
		 case EH:(*T)->bf = lc->bf = EH; break;
		 }
		 rc->bf = EH;
		 L_Rotate(&(*T)->lchild);
		 R_Rotate(T);
		 break;
	 }
}
//右平衡处理
void RightBalance(AVLTree *T)
{
	AVLTreeNode *lc, *rc;
	rc = (*T)->rchild;
	switch (rc->bf)
	{
	case RH:
		(*T)->bf = rc->bf = EH;
		L_Rotate(T); break;
	
	case LH:
		lc = rc->lchild;
		switch (lc->bf)
		{
		case LH:(*T)->bf = EH; rc->bf = LH; break;
		case RH:(*T)->bf = LH; rc->bf = EH; break;
		case EH:(*T)->bf = rc->bf = EH; break;
		}

		lc->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
		break;
	}
}
//删除操作
int AVLTree_delete(AVLTree *T, KeyType key, int *lower)
{
	AVLTree p; // 删除结点
	
	
	int targ = 0; // 标志位，即删除左结点或右结点
	int return_tag = 0;
	if (!*T)
	{// 可能出现删除叶子为空的情况不？
		return 0;
	}
	if (Compare(key, (*T)->data->key)==0)
	{// 如果为要删除结点
		*lower = TRUE; // 即找到所要删除结点，致标识为TRUE~
		if (NULL == (*T)->rchild)
		{ // 如果没有右节点
			p = *T;
			*T = (*T)->lchild;
			free(p->data);
			free(p);
			return 1; //删除成功，原tree左子树平衡，无需调整~ 
		}
		else
		{
			p = (*T)->rchild;
			while (p->lchild != NULL)
			{ // 找到当前结点的右子树的最左结点
				p = p->lchild;
			}

			(*T)->data->key = p->data->key;  //这里应该根据data的实际类型而实现赋值操作
			

			return_tag = AVLTree_delete(&(*T)->rchild, p->data->key, lower);
			targ = RH;
		}
	}
	else if (Compare(key,(*T)->data->key)<0)
	{
		return_tag = AVLTree_delete(&(*T)->lchild, key, lower);
		targ = LH;
	}
	else
	{
		return_tag = AVLTree_delete(&(*T)->rchild, key, lower);
		targ = RH;
	}

	// 保证存在过为key的结点~
	if (TRUE == *lower)
	{
		if (targ == LH)
		{// 删除的是左子树结点
			switch ((*T)->bf)
			{
		     // 原来结点左倾，现又删除左子树结点，左子树高度一定减少1，删除后变平衡，*T高度减少1，需继续平衡
			case LH: 
				(*T)->bf = EH; *lower = TRUE; break;
			case EH:
				(*T)->bf = RH; *lower = FALSE; break;
			case RH: // 如果原右子树已比左子树高1~，现在又删左子树，将导致不平衡~
				RightBalance(T); *lower = TRUE; break;
			} // switch(tree->bf)
		}
		else
		{// 删除的是右子树
			switch ((*T)->bf)
			{
			case LH:
				LeftBalance(T); *lower = TRUE; break;
			case EH:
				(*T)->bf = LH; *lower = FALSE; break;
			case RH:
				(*T)->bf = EH; *lower = TRUE; break;
			} // switch(tree->bf)
		}
	}// if(TRUE == lower)

	return return_tag;
}
//要树的深度
int AVLTree_level(AVLTree T)
{
	int lc, rc;
	if (!T)
	{
		return 0;
	}
	lc = AVLTree_level(T->lchild);
	rc = AVLTree_level(T->rchild);

	return lc > rc ? lc + 1 : rc + 1;

}
//销毁二叉树
void AVLTree_destroy(AVLTree T)
{
	if (!T)
	{
		return ;
	}

	if (T->lchild != NULL)
	{
		AVLTree_destroy(T->lchild);
	}
	if (T->rchild != NULL)
	{
		AVLTree_destroy(T->rchild);
	}
	free(T->data);
	free(T);
	
	

}


Status AVLTree_insert(AVLTree *T, DataType *e, Status *taller)
{
	
	if (*T == NULL)//如果*T为空，即找到插入的位置
	{
		*T = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));
		if (T == NULL)
			return ERROR;
		(*T)->data = e;
		(*T)->bf = EH;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
		*taller = TRUE; 
		
	}
	else if (Compare((*T)->data->key,e->key)==0) //元素已经存在，不再插入
	{
		*taller = FALSE;
		return ERROR;
	}
	else if (Compare(e->key,(*T)->data->key)<0)//如果元素小于当前结点
	{
		if (ERROR == AVLTree_insert(&(*T)->lchild, e, taller))//则向左子树插入
			return ERROR;
		if (*taller == TRUE)//taller为True，表明需要处理平衡
			switch ((*T)->bf)
		{
			case LH:LeftBalance(T); *taller = FALSE; break;//当前结点左倾，向左子树插入入后导致不平衡，执行左平衡处理
			case RH:(*T)->bf = EH; *taller = FALSE; break;
			case EH:(*T)->bf = LH; *taller = TRUE; break;
		}
	}
	else//如果元素小于当前结点
	{
		if (ERROR == AVLTree_insert(&(*T)->rchild, e, taller))//则向右子树插入
			return ERROR;
		if (*taller == TRUE)
			switch ((*T)->bf)
		{
			case RH:RightBalance(T); *taller = FALSE; break;
			case LH:(*T)->bf = EH; *taller = FALSE; break;
			case EH:(*T)->bf = RH; *taller = TRUE; break;
		}
	}
	return OK;
}

Status InOrderTraverse(AVLTree T, Status(*visit)(DataType *e))
{
	if (!T)
	{
		return ERROR;
	}
	
	if (T->lchild!=NULL)
	{
		InOrderTraverse(T->lchild, visit);
	}
	if (ERROR == visit(T->data))
		return ERROR;
	if (T->rchild != NULL)
	{
		InOrderTraverse(T->rchild, visit);
	}
	return OK;
}
Status PreOrderTraverse(AVLTree T, Status(*visit)(DataType *e))
{
	if (!T)
	{
		return ERROR;
	}
	if (ERROR == visit(T->data))
		return ERROR;
	if (T->lchild != NULL)
	{
		InOrderTraverse(T->lchild, visit);
	}
	if (T->rchild != NULL)
	{
		InOrderTraverse(T->rchild, visit);
	}
	return OK;
}

Status PostOrderTraverse(AVLTree T, Status(*visit)(DataType *e))
{
	if (!T)
	{
		return ERROR;
	}
	
	if (T->lchild != NULL)
	{
		InOrderTraverse(T->lchild, visit);
	}
	if (T->rchild != NULL)
	{
		InOrderTraverse(T->rchild, visit);
	}
	if (ERROR == visit(T->data))
		return ERROR;
	return OK;
}
