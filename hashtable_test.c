﻿#include <stdio.h>
#include "list.h"

#include "hashtable.h"

#define MAXSIZE 1000



int Test()
{
	void ShowAll(HashTable *h);
	HashTable *h;

	int i, n, c;
	float sum = 0;
	char sign;
	
	char * string;
	//string = "dfasdfsadf";
	//puts(string);

	getchar();

	h = HT_Create();

	if (UNSUCCESS == HT_init(h, MAXSIZE, HashSquare, match))
		return 0;

	srand((unsigned)time(NULL));
	
	for (i = 0; i < 10; i++)
	{
		RcdType new;
		new.key = rand();
		//HT_insert(h, new, &c);

		if (SUCCESS == HT_insert(h, new, &c))
			printf("插入成功，冲突次数：%d \n", c);
		sum += c;
	}
	printf("平均每次插入冲突：%f 次\n", sum / 800);
	//ShowAll(h);

	while (1)
	{
		scanf("%c%d", &sign, &n);
		getchar();
		if (sign == '+')
		{
			RcdType new;
			new.key = n;
			if (SUCCESS == HT_insert(h, new, &c))
				printf("插入成功，冲突次数：%d\n", c);
			ShowAll(h);
		}
		else if (sign == '-')
		{
			RcdType new;
			if (SUCCESS == HT_remove(h, n, &new))
			{
				printf("删除和元素为 key:%d\n", new.key);
			}
			else
			{
				printf("key=%d 的元素不存在\n", n);
			}
			ShowAll(h);
		}
		else
		{
			return 0;
		}

	}


	return 0;

}

void ShowAll(HashTable *h)
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
	{
		if (h->base[i].tag == 1)
		{
			printf("%d ", h->base[i].key);
		}
	}
	printf("\n");
}