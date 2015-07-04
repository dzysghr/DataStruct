#include "hashtable.h"
#include <stdlib.h>

HashTable * HT_Create()
{
	return (HashTable*)malloc(sizeof(HashTable));
}


//初始化
result  HT_init(HashTable *table, int MaxSize, int(*hash)(const KeyType key), int(*match)(const KeyType key1, const KeyType key2))
{
	int i;

	
	if (table == NULL || hash == NULL || match == NULL)
	{
		return UNSUCCESS;
	}
	table->Size = MaxSize;
	table->Count = 0;
	table->match = match;
	table->hash = hash;
	table->base = (RcdType*)malloc(MaxSize*sizeof(RcdType));
	if (table->base == NULL)
	{
	
		return UNSUCCESS;
	}

	for ( i = 0; i < MaxSize; i++)
	{
		table->base[i].tag = 0;
	}

	return SUCCESS;
}

//销毁
result HT_destroy(HashTable *table)
{
	
	free(table->base);
	free(table);
	return SUCCESS;
}


//搜索
result HT_search(HashTable *table, KeyType key, int* position,int* c)
{
	int p, i=0;
	int m = table->Size;
	p = table->hash(key);

	for ( i = 0; i < table->Size; i++)
	{
		*c = i;
		if (table->base[(p + i)%m].tag == 0)
		{
			*position = p + i;
			return	UNSUCCESS;
		}
		if (table->match(table->base[(p + i) % m].key, key) && table->base[(p + i) % m].tag != -1)
		{
			*position = p + i;
			return SUCCESS;
		}
	}
	return UNSUCCESS;
		
}

//插入
result HT_insert(HashTable *table, const RcdType data,int *c)
{
	int p=0;
	if (table->Count == table->Size || HT_search(table, data.key, &p,c) == SUCCESS)
	{
		return UNSUCCESS;
	}
	else
	{
		table->base[p] = data;
		table->base[p].tag = 1;
		table->Count++;
		return SUCCESS;
	}
}

//删除
result HT_remove(HashTable *table,KeyType key, RcdType *data)
{
	int p, c;
	if (UNSUCCESS == HT_search(table,key,&p,&c))
	{
		return UNSUCCESS;
	}
	else
	{
		*data = table->base[p];
		table->base[p].tag = -1;
		table->Count--;
		return SUCCESS;
	}
}

bool match(KeyType key1, KeyType key2)
{
	return key1 == key2 ? TRUE : FALSE;
}

//除留余数法
int Hash(KeyType key)
{
	return key % 997;
}


//平方取中法
int HashSquare(KeyType key)
{
	long temp;
	temp = key*key / 100;
	if (temp > 1000)
		temp = temp % 1000;
	return temp;
}
