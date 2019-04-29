#ifndef HASHTAB_H
#define HASHTAB_H
#define HASHTAB_SIZE 75011
#define N 50000
// 75000
typedef struct {
    unsigned int array[HASHTAB_SIZE];
    unsigned int max;
    unsigned int zero_elements;
    unsigned int one_elements;
    unsigned int collisi;
} collision;

typedef struct _listnode {
    int value;
    struct _listnode* next;
    char key[100];
} listnode;
/*
struct stack {
struct listnode *top; // Вершина стека
int size;
};
*/

//Функция переводящая значение ключа в хеш "Керниган & Ритчи"
unsigned int KRHash(char* key);
//Инициализация пустой хеш таблицы
void hashtab_init(listnode** hashtab);
//Добавить элемент в таблицу (адрес указателя на начало таблицы;
//адрес, по которому лежит ключ; значение)
void hashtab_add(listnode** hashtab, char* key, int value, collision* hash_);
listnode* hashtab_lookup(listnode** hashtab, char* key);
void hashtab_delete(listnode** hashtab, char* key);
void work(collision* hash_);
void print_stats_HT(listnode** hashtab);
int rol(int a, int n);

#endif
