#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>

Status AVLTree_init()
{
	return OK;
}

Status AVLTree_search(AVLTree T, const KeyType key, DataType **e)
{
	if (T == NULL)
		return ERROR;
	while (T)
	{
		if (T->data->key == key)
			break;
		else if (T->data->key > key)
			T = T->lchild;
		else
			T = T->rchild;

	}
	if (T != NULL)
	{
		*e = T->data;
		return OK;
	}
	return ERROR;
}


void R_Rotate(AVLTree *T)
{
	AVLTreeNode *lc;
	lc = (*T)->lchild;
	(*T)->lchild = lc->rchild;
	lc->rchild = (*T);
	(*T) = lc;
}

void L_Rotate(AVLTree *T)
{
	AVLTreeNode *rc;
	rc = (*T)->rchild;
	(*T)->rchild = rc->lchild;
	rc->lchild = (*T);
	(*T) = rc;
}

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



Status AVLTree_insert(AVLTree *T, DataType *e, Status *taller)
{

	if (*T == NULL)
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
	else if ((*T)->data->key == e->key)
	{
		*taller = FALSE;
		return ERROR;
	}
	else if (e->key < (*T)->data->key)
	{
		if (ERROR == AVLTree_insert(&(*T)->lchild, e, taller))
			return ERROR;
		if (*taller == TRUE)
			switch ((*T)->bf)
		{
			case LH:LeftBalance(T); *taller = FALSE; break;
			case RH:(*T)->bf = EH; *taller = FALSE; break;
			case EH:(*T)->bf = LH; *taller = TRUE; break;
		}
	}
	else
	{
		if (ERROR == AVLTree_insert(&(*T)->rchild, e, taller))
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