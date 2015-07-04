#ifndef HASHTABLE
#define HASHTABLE

#define result int
#define SUCCESS 1
#define UNSUCCESS 0
#define ERROR -1
#define KeyType long
#define TRUE 1
#define FALSE 0
#define bool int

typedef struct RcdType
{
	KeyType key;
	int tag;    //0表示为空，1表示占用，-1表示已删除
}RcdType;


typedef struct HashTable
{
	int Size; 
	int Count;
	int(*hash)(const KeyType key);
	bool(*match)(const KeyType key1, const KeyType key2);
	RcdType *base;
}HashTable;

//创建哈希表
HashTable * HT_Create();

//初始化哈希表
result  HT_init(HashTable *table, int MaxSize, int(*hash)(const KeyType key), int(*match)(const KeyType key1, const KeyType key2));

//销毁哈希表
result HT_destroy(HashTable *table);


//查找数据
result HT_search(HashTable *table, KeyType key, int* position,int* c);

//插入数据
result HT_insert(HashTable *table, const RcdType data,int *c);

//删除数据
result HT_remove(HashTable *table, KeyType key, RcdType *data);

int HashSquare(KeyType key);

int Hash(KeyType key);

bool match(KeyType key1, KeyType key2);











#endif
