#include "hashtab.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// rol - циклический сдвиг влево
int XOR(char const* input)
{
    int result = 0x55555555;
    while (*input) {
        result ^= *input++;
        result = rol(result, 5);
        if (result < 0) {
            return (result * (-1)) % N;
        } else {
            return result % N;
        }
    }
}

unsigned int KRHash(char* key)
{
    unsigned int h = 0;
    unsigned int hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % N;
}
//Все узлы указывают в некуда
//Есть только указатель на начало хеш таблицы
void hashtab_init(listnode** hashtab)
{
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++) {
        hashtab[i] = NULL;
    }
}
//Создаётся узел
//Для полученного ключа создаётся хеш код - index
//Под указатель на узел выделяется память
void hashtab_add(listnode** hashtab, char* key, int value, collision* hash_)
{
    listnode* node = (listnode*)malloc(sizeof(listnode));
    assert(node);
    int index = KRHash(key);
    // int index = XOR((const char*)key);
    if (node != NULL) {
        strcpy(node->key, key);
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
        hash_->array[index]++;
        /*fprintf(stderr,
                "Add [ind: %d | key: %s | %p->%p]\n",
                index,
                hashtab[index]->key,
                hashtab[index],
                hashtab[index]->next);*/
    } else {
        printf("Error no add, no action taken\nindex: %d key: %s value: %d\n",
               index,
               key,
               value);
    }
}

listnode* hashtab_lookup(listnode** hashtab, char* key)
{
    listnode* node;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            //  printf("lookup done\n");
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(listnode** hashtab, char* key)
{
    listnode *node, *prev = NULL;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}

void work(collision* hash_)
{
    int i;
    unsigned int max = 0;
    max = hash_->array[0];
    for (i = 1; i < HASHTAB_SIZE; i++) {
        if (hash_->array[i] > max) {
            max = hash_->array[i];
        }
    }
    hash_->max = max - 1;
    hash_->zero_elements = 0;
    hash_->one_elements = 0;
    hash_->collisi = 0;
    for (i = 0; i < HASHTAB_SIZE; i++) {
        if (hash_->array[i] == 0) {
            hash_->zero_elements++;
        } else if (hash_->array[i] == 1) {
            hash_->one_elements++;
        }
        if (hash_->array[i] > 1) {
            hash_->collisi += (hash_->array[i] - 1);
        }
    }
}

void print_stats_HT(listnode** hashtab)
{
    listnode* cursor = NULL;
    for (int i = 0; i < HASHTAB_SIZE; i++) {
        if (hashtab[i] != NULL) {
            printf("[ind: %d | key: %s | ptr: %p]\n",
                   i,
                   hashtab[i]->key,
                   hashtab[i]->next);
            cursor = hashtab[i]->next;
            while (cursor != NULL) {
                printf("\t[ind: %d | key: %s | ptr: %p]\n",
                       i,
                       cursor->key,
                       cursor->next);
                cursor = cursor->next;
            }
        } else {
            printf("[ind: %d | key: %s]\n", i, "NONE");
        }
    }
}

int rol(int a, int n)
{
    int t1, t2;
    n = n % (sizeof(a) * 8); // нормализуем n
    t1 = a << n; // двигаем а вправо на n бит, теряя старшие биты
    t2 = a >> (sizeof(a) * 8 - n); // перегоняем старшие биты в младшие
    return t1 | t2; // объединяем старшие и младшие биты
}
