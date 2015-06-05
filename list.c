#include <stdlib.h>
#include <string.h>
#include "list.h"

/*Initialize the list*/
void list_init(List *list,void (*destroy)(void *data))
{
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

/*destroy the list*/
void list_destroy(List *list)
{
	void *data;
	while (list_size(list)>0)
	{
		if (list->destroy != NULL&&list_rem_next(list,NULL,(void **)&data)==0)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
	
}

/*remove the next of element*/
int list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt *oldelement;
	if (list==NULL||list_size(list)==0||data==NULL)
	{
		return -1;
	}


	/*if element ==NULL ,remove the head*/
	if (element==NULL)
	{
		*data = list->head->data;
		oldelement = list->head;
		list->head = oldelement->next;

	}
	else
	{
		if (element->next==NULL)
		{
			return -1;
		}

		oldelement = element->next;
		element->next = oldelement->next;
		if (element->next==NULL)
		{
			list->tail = element;
		}
	}

	free(oldelement);

	list->size--;
	return 0;
}
/*insert a new element next to the param element*/
int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *newelement;
	if (list == NULL)
	{
		return -1;
	}
	if ((newelement = (ListElmt*)malloc(sizeof(ListElmt))) == NULL)
	{
		return -1;
	}

	newelement->data = data;

	if (element == NULL)
	{
		newelement->next = list->head;
		list->head = newelement;
		if (list->size == 0)
		{
			list->tail = newelement;
		}

	}

	else
	{
		newelement->next = element->next;
		element->next = newelement;
		if (newelement->next == NULL)
		{
			list->tail = newelement;
		}
	}
	list->size++;
	return 0;

} 