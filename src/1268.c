#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareString(const void *str1, const void *str2) {
    // ascending order
    return strcmp(*(char **)str1, *(char **)str2);
}
void findProducts(char **ret, char **products, int productsSize, char *searchWord, int *size) {
    char *s = NULL;
    int i;
    for (i = 0; i < productsSize; ++i) {
        s = strstr(products[i], searchWord);
        if (s == products[i]) {
            ret[*size] = (char *)malloc((strlen(products[i]) + 1) * sizeof(char));
            strcpy(ret[(*size)++], products[i]);
        }
        if (*size == 3) {
            break;
        }
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***suggestedProducts(char **products, int productsSize, char *searchWord, int *returnSize,
                          int **returnColumnSizes) {
    char ***pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    int searchWordSize = strlen(searchWord);
    pRetVal = (char ***)malloc(searchWordSize * sizeof(char **));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(searchWordSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    qsort(products, productsSize, sizeof(char *), compareString);

    char tmp;
    int i, j;
    for (i = 0; i < searchWordSize; ++i) {
        pRetVal[i] = (char **)malloc(3 * sizeof(char *));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }

        tmp = 0;
        if (i + 1 < searchWordSize) {
            tmp = searchWord[i + 1];
            searchWord[i + 1] = 0;
        }

        (*returnColumnSizes)[i] = 0;
        findProducts(pRetVal[i], products, productsSize, searchWord, &(*returnColumnSizes)[i]);

        if (i + 1 < searchWordSize) {
            searchWord[i + 1] = tmp;
        }
    }
    (*returnSize) = searchWordSize;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *products[MAX_SIZE];
        int productsSize;
        char searchWord[MAX_SIZE];
        int returnSize;
        int *returnColumnSizes;
    } testCase[] = {{{"mobile", "mouse", "moneypot", "monitor", "mousepad"}, 5, "mouse", 0, NULL},
                    {{"havana"}, 1, "havana", 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
     *  Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],
     *  ["mouse","mousepad"],["mouse","mousepad"]]
     *
     *  Input: products = ["havana"], searchWord = "havana"
     *  Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
     */

    char **pProducts = NULL;
    char ***pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: products =  [");
        for (j = 0; j < testCase[i].productsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].products[j]);
        }
        printf("], searchWord = \"%s\"\n", testCase[i].searchWord);

        pProducts = (char **)malloc(testCase[i].productsSize * sizeof(char *));
        if (pProducts == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].productsSize; ++j) {
            pProducts[j] = (char *)malloc((strlen(testCase[i].products[j]) + 1) * sizeof(char));
            if (pProducts[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pProducts[k]) {
                        free(pProducts[k]);
                        pProducts[k] = NULL;
                    }
                }
                free(pProducts);
                pProducts = NULL;
                return EXIT_FAILURE;
            }
            memset(pProducts[j], 0, (strlen(testCase[i].products[j]) + 1) * sizeof(char));
            memcpy(pProducts[j], testCase[i].products[j], (strlen(testCase[i].products[j]) + 1) * sizeof(char));
        }
        pAnswer = suggestedProducts(pProducts, testCase[i].productsSize, testCase[i].searchWord,
                                    &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                free(pAnswer[j][k]);
                pAnswer[j][k] = NULL;
            }
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].productsSize; ++j) {
            if (pProducts[j]) {
                free(pProducts[j]);
                pProducts[j] = NULL;
            }
        }
        free(pProducts);
        pProducts = NULL;
    }

    return EXIT_SUCCESS;
}
