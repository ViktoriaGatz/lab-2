#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bstree* bstree_create(char* key, int value)
{
    bstree* node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = (char*)malloc(128 * sizeof(char));
        if (!node->key) {
            fprintf(stderr, "Out of memory\n");
            return NULL;
        }
        strcpy(node->key, key);
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_free(struct bstree** tree)
{
    if (*tree == NULL)
        return;
    bstree_free(&(*tree)->left);
    bstree_free(&(*tree)->right);
    free(*tree);
}

int bstree_add(struct bstree* tree, char* key, int value)
{
    if (tree == NULL) {
        if (!(tree = bstree_create(key, value)))
            return -1;
    }

    bstree *parent, *node;
    while (tree != NULL) {
        parent = tree;
        if (sortsort(key, tree->key) == 1)
            tree = tree->left;
        else if (sortsort(key, tree->key) == -1)
            tree = tree->right;
        else
            return -1;
    }
    node = bstree_create(key, value);

    if (sortsort(key, parent->key) == 1)
        parent->left = node;
    else
        parent->right = node;
    return 0;
}

// O(logn + m) ?? O(logn * m)
bstree* bstree_lookup(struct bstree* tree, char* key)
{
    while (tree != NULL) {
        if (!(strcmp(key, tree->key)))
            return tree;
        else if (sortsort(key, tree->key) == 1)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

bstree* bstree_min(struct bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

bstree* bstree_max(struct bstree* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}
// Срвнивание слов в алфавитном порядке
// возвращает 1 если s1 стоит до s2
// возвращает -1 если s1 стоит после s2
// возвращает 0 если слова одинаковые
int sortsort(char* s1, char* s2)
{
    int min = minimum(s1, s2);
    for (int i = 0; i < min; i++) {
        if (str_sort(s1[i], s2[i]) == 1)
            return 1;
        if (str_sort(s1[i], s2[i]) == -1)
            return -1;
    }
    return 0;
}

int minimum(char* s1, char* s2)
{
    int min = 0;
    if (strlen(s1) < strlen(s2))
        min = strlen(s1);
    else
        min = strlen(s2);
    return min;
}

int str_sort(char c1, char c2)
{
    if (c1 < c2)
        return 1;
    else if (c2 < c1)
        return -1;
    else
        return 0;
}
