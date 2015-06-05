#include "set.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void set_init(Set *set, int(*match)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	list_init(set, destroy);
	set->match = match;
	return;

}

int set_insert(Set *set, const void *data)
{
	if (set_is_member(set,data))
	{
		return -1;
	}
	return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set* set,void **data)
{
	ListElmt *member, *priv;
	priv = NULL;
	for (member = list_head(set);member!=NULL;member = list_next(member))
	{
		if (set->match(*data,member->data))
		{
			break;
		}
		priv = member;
	}

	if (member == NULL)
		return -1;

	return list_rem_next(set, priv, data);
}

int set_union(Set *setu, const Set* set1, const Set *set2)
{
	ListElmt *elmt;
	void *data;
	set_init(setu, set1->match, set1->destroy);
	/*copy the member from set1 to setu*/
	for (elmt = list_head(set1); elmt != NULL; elmt = list_next(elmt))
	{
		data = list_data(elmt);
		if (list_ins_next(setu,list_tail(setu),data)!=0)
		{
			set_destroy(setu);
			return -1;
		}
	}

	for (elmt = list_head(set2); elmt != NULL; elmt = list_next(elmt))
	{
		if (set_is_member(set1,elmt->data))
		{
			continue;
		}
		else
		{
			if (list_ins_next(setu,list_tail(setu),elmt->data)!=0)
			{
				set_destroy(setu);
				return -1;
			}
		}
	}

	return 0;
}

int set_intersection(Set *seti, const Set* set1, const Set* set2)
{
	ListElmt *elmt;
	set_init(seti, set1->match, set1->destroy);

	for ( elmt = list_head(set1); elmt!=NULL; elmt = list_next(elmt))
	{
		if (set_is_member(set2,elmt->data))
		{
			if (list_ins_next(seti,list_tail(seti),elmt->data)!=0)
			{
				set_destroy(seti);
				return -1;
			}

		}
	}
	return 0;
}

int set_defference(Set *setd, const Set* set1, const Set* set2)
{
	ListElmt *elmt;
	set_init(setd, set1->match, set2->destroy);

	for (elmt = list_head(set1); elmt != NULL; elmt = list_next(elmt))
	{
		if (set_is_member(set2,elmt->data))
		{
			continue;
		}
		else
		{
			if (set_insert(setd,elmt->data)!=0)
			{
				set_destroy(setd);
				return -1;
			}
		}
	}

	return 0;
}

int set_is_member(Set *set, const void* data)
{
	ListElmt *elmt;
	if (data==NULL)
	{
		return -1;
	}
	for (elmt=list_head(set); elmt!=NULL;elmt = list_next(elmt))
	{
		if (set->match(list_data(elmt),data))
		{
			return 1;
		}
		
	}
	return 0;
}

int set_is_subset(const Set* set1, const Set* set2)
{
	ListElmt *elmt;
	if (set_size(set1)>set_size(set2))
	{
		return 0;
	}
	for (elmt = list_head(set1); elmt != NULL; elmt = list_next(elmt))
	{
		if (!set_is_member(set2, elmt->data))
			return 0;
	}

	return 1;
}

int set_is_equal(const Set* set1, const Set* set2)
{
	if (set_size(set1)!=set_size(set2))
	{
		return 0;
	}
	return set_is_subset(set1, set2);
}