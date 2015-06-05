#include <stdio.h>
#include "list.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "cqueue.h"
#include "hashtable.h"

#define MAXSIZE 1000

bool match(KeyType key1, KeyType key2)
{
	return key1 == key2 ? TRUE : FALSE;
}

//����������
int Hash(KeyType key)
{
	return key % 997;
}


//ƽ��ȡ�з�
int HashSquare(KeyType key)
{
	long temp;
	temp = key*key / 100;
	if (temp > 1000)
		temp = temp % 1000;
	return temp;
}



int Test()
{
	void ShowAll(HashTable *h);
	HashTable *h;

	int i, n, c;
	float sum = 0;
	char sign;

	char * string;
	string = "dfasdfsadf";
	puts(string);

	getchar();

	h = HT_Create();

	if (UNSUCCESS == HT_init(h, MAXSIZE, HashSquare, match))
		return 0;

	srand((unsigned)time(NULL));
	
	for (i = 0; i < 800; i++)
	{
		RcdType new;
		new.key = rand();
		//HT_insert(h, new, &c);

		if (SUCCESS == HT_insert(h, new, &c))
			printf("����ɹ�����ͻ������%d \n", c);
		sum += c;
	}
	printf("ƽ��ÿ�β����ͻ��%f ��\n", sum / 800);
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
				printf("����ɹ�����ͻ������%d\n", c);
			ShowAll(h);
		}
		else if (sign == '-')
		{
			RcdType new;
			if (SUCCESS == HT_remove(h, n, &new))
			{
				printf("ɾ����Ԫ��Ϊ key:%d\n", new.key);
			}
			else
			{
				printf("key=%d ��Ԫ�ز�����\n", n);
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