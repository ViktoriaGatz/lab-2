#ifndef BSTREE_H
#define BSTREE_H
#define M 20

typedef struct bstree {
    char* key;
    int value;

    struct bstree* left;
    struct bstree* right;
} bstree;



typedef struct {
    char* words;
} UNIT;

bstree* bstree_create(char* key, int value);
int bstree_add(struct bstree* tree, char* key, int value);
bstree* bstree_lookup(struct bstree* tree, char* key);
bstree* bstree_min(struct bstree* tree);
bstree* bstree_max(struct bstree* tree);
void bstree_free(struct bstree** tree);
int sortsort(char* s1, char* s2);
int minimum(char* s1, char* s2);
int str_sort(char c1, char c2);

#endif
