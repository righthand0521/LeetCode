#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/design-movie-rental-system/solutions/1943123/she-ji-dian-ying-zu-jie-by-heng-deng-shi-gw1e/
#if (1)
#define MOST_RESULTS (5)
#define MOST_MOVIES (10001)
#define SINGLE_SHIFT (20)
#define SINGLE_MASK (0xFFFFF)
#define DOUBLE_SHIFT (40)
#define INVALID_INDEX (-1)
#define FATHER_NODE(x) ((0 == (x)) ? INVALID_INDEX : (((x) - 1) >> 1))
#define LEFT_NODE(x) (((x) << 1) + 1)
#define RIGHT_NODE(x) (((x) << 1) + 2)

typedef struct {
    long int *buffer;
    int *searchResult;
    int *reportBuffer;
    int **reportResult;
    int *reportColResult;
} ReturnArrays;
typedef struct {
    int shop;
    int price;
    bool sent;
    bool inMovieHeap;
    bool inSentHeap;
    UT_hash_handle hh;
} HashMapNode;
typedef struct {
    int bufferSize;
    long int *buffer;
} HeapNode;

void heapPush(HeapNode *heap, long int value) {
    int son = heap->bufferSize;
    int father = FATHER_NODE(son);

    heap->bufferSize++;
    while ((INVALID_INDEX != father) && (heap->buffer[father] > value)) {
        heap->buffer[son] = heap->buffer[father];
        son = father;
        father = FATHER_NODE(son);
    }
    heap->buffer[son] = value;
}
void heapPop(HeapNode *heap) {
    int father = 0;
    int son = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);

    long int value = heap->buffer[heap->bufferSize - 1];

    heap->bufferSize--;
    while (((heap->bufferSize > left) && (heap->buffer[left] < value)) ||
           ((heap->bufferSize > right) && (heap->buffer[right] < value))) {
        son = ((heap->bufferSize > right) && (heap->buffer[right] < heap->buffer[left])) ? (right) : (left);
        heap->buffer[father] = heap->buffer[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    heap->buffer[father] = value;
}
#endif
typedef struct {
    ReturnArrays arrays;
    HeapNode sentHeap;
    HeapNode *movieHeap;
    HashMapNode **hashTable;
} MovieRentingSystem;
MovieRentingSystem *movieRentingSystemCreate(int n, int **entries, int entriesSize, int *entriesColSize) {
    MovieRentingSystem *obj = (MovieRentingSystem *)malloc(sizeof(MovieRentingSystem));

    obj->arrays.buffer = (long int *)malloc(sizeof(long int) * MOST_RESULTS);
    obj->arrays.searchResult = (int *)malloc(sizeof(int) * MOST_RESULTS);
    obj->arrays.reportBuffer = (int *)malloc(sizeof(int) * MOST_RESULTS * 2);
    obj->arrays.reportResult = (int **)malloc(sizeof(int *) * MOST_RESULTS);
    obj->arrays.reportColResult = (int *)malloc(sizeof(int) * MOST_RESULTS);

    int x = 0;
    while (MOST_RESULTS > x) {
        obj->arrays.reportResult[x] = &obj->arrays.reportBuffer[x * 2];
        obj->arrays.reportColResult[x] = 2;
        x++;
    }

    obj->sentHeap.bufferSize = 0;
    obj->sentHeap.buffer = (long int *)malloc(sizeof(long int) * entriesSize);

    obj->movieHeap = (HeapNode *)calloc(MOST_MOVIES, sizeof(HeapNode));
    obj->hashTable = (HashMapNode **)calloc(MOST_MOVIES, sizeof(HashMapNode *));

    HashMapNode *node = NULL;
    int shop = 0;
    x = 0;
    while (entriesSize > x) {
        shop = entries[x][0];

        node = (HashMapNode *)malloc(sizeof(HashMapNode));
        node->shop = shop;
        node->price = entries[x][2];
        node->sent = false;
        node->inMovieHeap = true;
        node->inSentHeap = false;
        HASH_ADD_INT(obj->hashTable[entries[x][1]], shop, node);

        obj->movieHeap[entries[x][1]].bufferSize++;

        x++;
    }

    long int value = 0;
    x = 0;
    while (entriesSize > x) {
        if ((0 < obj->movieHeap[entries[x][1]].bufferSize) && (NULL == obj->movieHeap[entries[x][1]].buffer)) {
            obj->movieHeap[entries[x][1]].buffer =
                (long int *)malloc(sizeof(long int) * obj->movieHeap[entries[x][1]].bufferSize);
            obj->movieHeap[entries[x][1]].bufferSize = 0;
        }

        value = ((long int)entries[x][2] << DOUBLE_SHIFT) | ((long int)entries[x][0] << SINGLE_SHIFT) |
                ((long int)entries[x][1]);
        heapPush(&obj->movieHeap[entries[x][1]], value);

        x++;
    }

    return obj;
}
int *movieRentingSystemSearch(MovieRentingSystem *obj, int movie, int *retSize) {
    int *pRetVal = NULL;

    (*retSize) = 0;

    HashMapNode *node = NULL;
    int x = 0;
    int shop = 0;
    long int value = 0;
    while ((MOST_RESULTS > (*retSize)) && (0 < obj->movieHeap[movie].bufferSize)) {
        value = obj->movieHeap[movie].buffer[0];
        shop = value >> SINGLE_SHIFT & SINGLE_MASK;
        HASH_FIND_INT(obj->hashTable[movie], &shop, node);
        if (NULL != node) {
            if (false == node->sent) {
                obj->arrays.searchResult[(*retSize)] = shop;
                obj->arrays.buffer[(*retSize)] = value;
                (*retSize)++;
            } else {
                node->inMovieHeap = false;
            }
        }
        heapPop(&obj->movieHeap[movie]);
    }

    if (0 < (*retSize)) {
        while ((*retSize) > x) {
            heapPush(&obj->movieHeap[movie], obj->arrays.buffer[x]);
            x++;
        }
        pRetVal = obj->arrays.searchResult;
    }

    return pRetVal;
}
void movieRentingSystemRent(MovieRentingSystem *obj, int shop, int movie) {
    HashMapNode *node = NULL;
    HASH_FIND_INT(obj->hashTable[movie], &shop, node);
    if (node == NULL) {
        return;
    } else if (node->sent == true) {
        return;
    }
    node->sent = true;

    long int value = ((long int)node->price << DOUBLE_SHIFT) | ((long int)shop << SINGLE_SHIFT) | ((long int)movie);
    if ((0 < obj->movieHeap[movie].bufferSize) && (value == obj->movieHeap[movie].buffer[0])) {
        node->inMovieHeap = false;
        heapPop(&obj->movieHeap[movie]);
    }

    if (false == node->inSentHeap) {
        node->inSentHeap = true;
        heapPush(&obj->sentHeap, value);
    }
}
void movieRentingSystemDrop(MovieRentingSystem *obj, int shop, int movie) {
    HashMapNode *node = NULL;
    HASH_FIND_INT(obj->hashTable[movie], &shop, node);
    if (node == NULL) {
        return;
    } else if (node->sent == false) {
        return;
    }
    node->sent = false;

    long int value = ((long int)node->price << DOUBLE_SHIFT) | ((long int)shop << SINGLE_SHIFT) | ((long int)movie);
    if ((0 < obj->sentHeap.bufferSize) && (value == obj->sentHeap.buffer[0])) {
        node->inSentHeap = false;
        heapPop(&obj->sentHeap);
    }

    if (false == node->inMovieHeap) {
        node->inMovieHeap = true;
        heapPush(&obj->movieHeap[movie], value);
    }
}
int **movieRentingSystemReport(MovieRentingSystem *obj, int *retSize, int **retColSize) {
    int **pRetVal = NULL;

    (*retSize) = 0;
    (*retColSize) = NULL;

    HashMapNode *node = NULL;
    int x = 0;
    int shop = 0;
    int movie = 0;
    long int value = 0;
    while ((MOST_RESULTS > (*retSize)) && (0 < obj->sentHeap.bufferSize)) {
        value = obj->sentHeap.buffer[0];
        shop = value >> SINGLE_SHIFT & SINGLE_MASK;
        movie = value & SINGLE_MASK;

        HASH_FIND_INT(obj->hashTable[movie], &shop, node);
        if (NULL != node) {
            if (true == node->sent) {
                obj->arrays.reportResult[(*retSize)][0] = shop;
                obj->arrays.reportResult[(*retSize)][1] = movie;
                obj->arrays.buffer[(*retSize)] = value;
                (*retSize)++;
            } else {
                node->inSentHeap = false;
            }
        }
        heapPop(&obj->sentHeap);
    }

    if (0 < (*retSize)) {
        while (*retSize > x) {
            heapPush(&obj->sentHeap, obj->arrays.buffer[x]);
            x++;
        }
        (*retColSize) = obj->arrays.reportColResult;
        pRetVal = obj->arrays.reportResult;
    }

    return pRetVal;
}
void movieRentingSystemFree(MovieRentingSystem *obj) {
    free(obj->arrays.buffer);
    free(obj->arrays.searchResult);
    free(obj->arrays.reportBuffer);
    free(obj->arrays.reportResult);
    free(obj->arrays.reportColResult);

    if (NULL != obj->sentHeap.buffer) {
        free(obj->sentHeap.buffer);
    }

    HashMapNode *node = NULL;
    HashMapNode *t = NULL;
    int x = 0;
    while (MOST_MOVIES > x) {
        if (NULL != obj->hashTable[x]) {
            HASH_ITER(hh, obj->hashTable[x], node, t) {
                HASH_DEL(obj->hashTable[x], node);
                free(node);
            }
        }

        if (NULL != obj->movieHeap[x].buffer) {
            free(obj->movieHeap[x].buffer);
        }

        x++;
    }
    free(obj->hashTable);
    free(obj->movieHeap);

    free(obj);

    return;
}
/**
 * Your MovieRentingSystem struct will be instantiated and called as such:
 * MovieRentingSystem* obj = movieRentingSystemCreate(n, entries, entriesSize, entriesColSize);
 * int* param_1 = movieRentingSystemSearch(obj, movie, retSize);
 * movieRentingSystemRent(obj, shop, movie);
 * movieRentingSystemDrop(obj, shop, movie);
 * int** param_4 = movieRentingSystemReport(obj, retSize, retColSize);
 * movieRentingSystemFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int n[MAX_SIZE];
        int entries[MAX_SIZE][MAX_SIZE][MAX_SIZE];
        int entriesSize[MAX_SIZE];
        int entriesColSize[MAX_SIZE][MAX_SIZE];
        int shop[MAX_SIZE];
        int movie[MAX_SIZE];
        int retSize[MAX_SIZE];
        int *retColSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"},
                     {3, 0, 0, 0, 0, 0, 0},
                     {{{0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}}, {}, {}, {}, {}, {}, {}},
                     {6, 0, 0, 0, 0, 0, 0},
                     {{3, 3, 3, 3, 3, 3}, {}, {}, {}, {}, {}, {}},
                     {0, 0, 0, 1, 0, 1, 0},
                     {0, 1, 1, 2, 0, 2, 2},
                     {0, 0, 0, 0, 0, 0, 0},
                     {NULL, NULL, NULL, NULL, NULL, NULL, NULL},
                     7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"]
     *  [[3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2, 7], [2, 1, 5]]], [1], [0, 1], [1, 2], [], [1, 2], [2]]
     *  Output
     *  [null, [1, 0, 2], null, null, [[0, 1], [1, 2]], null, [0, 1]]
     */

    MovieRentingSystem *obj = NULL;
    int **pEntries = NULL;
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            if (strcmp(testCase[i].methods[j], "MovieRentingSystem") == 0) {
                printf("%d, ", testCase[i].n[j]);
                printf("[");
                for (int k = 0; k < testCase[i].entriesSize[j]; ++k) {
                    printf("%s[", (k == 0) ? "" : ", ");
                    for (int l = 0; l < testCase[i].entriesColSize[j][k]; ++l) {
                        printf("%s%d", (l == 0) ? "" : ",", testCase[i].entries[j][k][l]);
                    }
                    printf("]");
                }
                printf("]");
            } else if (strcmp(testCase[i].methods[j], "search") == 0) {
                printf("%d", testCase[i].movie[j]);
            } else if (strcmp(testCase[i].methods[j], "rent") == 0) {
                printf("%d, %d", testCase[i].shop[j], testCase[i].movie[j]);
            } else if (strcmp(testCase[i].methods[j], "report") == 0) {
            } else if (strcmp(testCase[i].methods[j], "drop") == 0) {
                printf("%d, %d", testCase[i].shop[j], testCase[i].movie[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (int j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ", ");
            if (strcmp(testCase[i].methods[j], "MovieRentingSystem") == 0) {
                pEntries = (int **)malloc(sizeof(int *) * testCase[i].entriesSize[j]);
                for (int k = 0; k < testCase[i].entriesSize[j]; ++k) {
                    pEntries[k] = (int *)malloc(sizeof(int) * testCase[i].entriesColSize[j][k]);
                    memcpy(pEntries[k], testCase[i].entries[j][k], sizeof(int) * testCase[i].entriesColSize[j][k]);
                }
                obj = movieRentingSystemCreate(testCase[i].n[j], pEntries, testCase[i].entriesSize[j],
                                               testCase[i].entriesColSize[j]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "search") == 0) {
                int *retVal = movieRentingSystemSearch(obj, testCase[i].movie[j], &testCase[i].retSize[j]);
                printf("[");
                for (int k = 0; k < testCase[i].retSize[j]; ++k) {
                    printf("%s%d", (k == 0) ? "" : ",", retVal[k]);
                }
                printf("]");
            } else if (strcmp(testCase[i].methods[j], "rent") == 0) {
                movieRentingSystemRent(obj, testCase[i].shop[j], testCase[i].movie[j]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "report") == 0) {
                int **retVal = movieRentingSystemReport(obj, &testCase[i].retSize[j], &testCase[i].retColSize[j]);
                printf("[");
                for (int k = 0; k < testCase[i].retSize[j]; ++k) {
                    printf("%s", (k == 0) ? "" : ",");
                    printf("[");
                    for (int l = 0; l < testCase[i].retColSize[j][k]; ++l) {
                        printf("%s%d", (l == 0) ? "" : ",", retVal[k][l]);
                    }
                    printf("]");
                }
                printf("]");
            } else if (strcmp(testCase[i].methods[j], "drop") == 0) {
                movieRentingSystemDrop(obj, testCase[i].shop[j], testCase[i].movie[j]);
                printf("null");
            }
        }
        printf("]\n");

        for (int j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MovieRentingSystem") == 0) {
                for (int k = 0; k < testCase[i].entriesSize[j]; ++k) {
                    free(pEntries[k]);
                    pEntries[k] = NULL;
                }
                free(pEntries);
                pEntries = NULL;
            }
        }
        movieRentingSystemFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
