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
	int tag;    //0��ʾΪ�գ�1��ʾռ�ã�-1��ʾ��ɾ��
}RcdType;


typedef struct HashTable
{
	int Size; 
	int Count;
	int(*hash)(const KeyType key);
	bool(*match)(const KeyType key1, const KeyType key2);
	RcdType *base;
}HashTable;

//������ϣ��
HashTable * HT_Create();

//��ʼ����ϣ��
result  HT_init(HashTable *table, int MaxSize, int(*hash)(const KeyType key), int(*match)(const KeyType key1, const KeyType key2));

//���ٹ�ϣ��
result HT_destroy(HashTable *table);


//��������
result HT_search(HashTable *table, KeyType key, int* position,int* c);

//��������
result HT_insert(HashTable *table, const RcdType data,int *c);

//ɾ������
result HT_remove(HashTable *table, KeyType key, RcdType *data);

int HashSquare(KeyType key);

int Hash(KeyType key);

bool match(KeyType key1, KeyType key2);











#endif
