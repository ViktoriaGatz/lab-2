#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    collision hash_;
    srand(time(NULL));
    listnode* hashtab[HASHTAB_SIZE];
    // printf("%ld\n", sizeof(listnode) * N);
    hashtab_init(hashtab);
    memset(&hash_, 0, sizeof(collision));
    FILE* myfile;
    myfile = fopen("words.txt", "r");
    if (myfile == NULL) {
        printf("No file\n");
        return 1;
    }

    char key[100];
    int k = 0;

    // выбираем рандомный элемент
    char buf[256];
    int j = rand() % N;
    //  printf("%d\n", j);
    while (k < N) {
        fscanf(myfile, "%s", key);
        if (k == j)
            strcpy(buf, key);
        hashtab_add(hashtab, key, k++, &hash_);
    }

    double t;
    t = wtime();
    hashtab_lookup(hashtab, buf);
    t = wtime() - t;
    work(&hash_);
    // print_stats_HT(hashtab);
    /*printf("Число коллизий:\t\t\t\t\t\t%d\nЧисло незадействованных "
           "ячеек:\t\t\t\t%d\nЧисло "
           "ячеек, в которых лежит только один элемент:\t%d\nМаксимальное "
           "число коллизий на одну ячейку:\t\t%d\n",
           hash_.collisi,
           hash_.zero_elements,
           hash_.one_elements,
           hash_.max);*/
    printf("%d\t%f\t%d\n", N, t, hash_.collisi);
    fclose(myfile);
    return 0;
}
