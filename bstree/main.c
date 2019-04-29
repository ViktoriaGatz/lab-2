#include "bstree.h"
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

int main(int argc, char** argv)
{
    srand(time(NULL));
    unsigned int N;
    for (N = 75000; N <= 75000; N += 5000) {
        FILE* myfile = fopen("./words.txt", "r");
        if (myfile == NULL)
            fprintf(stderr, "No file. %s:[%d]\n", __FILE__, __LINE__);
        UNIT* WORDS = (UNIT*)malloc(N * sizeof(char));
        int c = 0;
        bstree* root = bstree_create("bstree", 0);
        // printf("root\t%p\n", (bstree*)root);
        char* key = (char*)malloc(128 * sizeof(char));
        int count = N;
        int value = 0;
        if (!key) {
            fprintf(stderr,
                    "Fatal error in malloc. %s:[%d]\n",
                    __FILE__,
                    __LINE__);
            return 1;
        }
        if (myfile == NULL) {
            printf("No file\n");
            return 1;
        }
        // fprintf(stderr, "find\t%p\n", root);
        char buf[256];
        unsigned int j;
        j = rand() % N;
        unsigned int i = 0;

        while (1) {
            if (c >= count)
                break;
            if (fscanf(myfile, "%s", key) > 0) {
                if (c == j) {
                    strcpy(buf, key);
                    // printf("%s\n", buf);
                }
                c++;
                bstree_add(root, key, c - 1);
                i++;
            } else {
                fprintf(stderr, "End of file\n");
                break;
            }
        }
        /* Если слова в тексте выстроенны в алфавитном порядке,
        то они все попадут в правое крыло
        bstree* cursor = root;
        while (cursor != NULL) {
            printf("%s\n", cursor->key);
            cursor = cursor->right;
        } */
        // fseek(myfile, 0, SEEK_SET);

        double t = wtime();
        bstree_lookup(root, buf);
        t = wtime() - t;
        printf("%d\t%f\n", N, t);
        //        printf("%s\n", WORDS[j].words);
        fclose(myfile);
        bstree_free(&root);
        free(key);
        free(WORDS);
        // printf("Done\n");
    }
    return 0;
}
