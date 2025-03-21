#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/find-all-possible-recipes-from-given-supplies/solutions/1202692/cyu-yan-tuo-bu-pai-xu-by-charfield-4wg3/
#define RECIPE_NAME (12)
#define INGRE_NUM (100)
typedef struct {
    int idx;
    char* reciName;
    int ingreCnt;
} Recipe;
typedef struct {
    char* ingre;
    int dishIdx[INGRE_NUM];
    int top;
    UT_hash_handle hh;
} IngreHash;
void freeAll(IngreHash* pFree) {
    IngreHash* current;
    IngreHash* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllRecipes(char** recipes, int recipesSize, char*** ingredients, int ingredientsSize,
                      int* ingredientsColSize, char** supplies, int suppliesSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    Recipe* recipeStr = (Recipe*)malloc(recipesSize * sizeof(Recipe));
    if (recipeStr == NULL) {
        perror("malloc");
        return pRetVal;
    }

    IngreHash* ingHash = NULL;
    for (int i = 0; i < recipesSize; i++) {
        recipeStr[i].reciName = recipes[i];
        recipeStr[i].ingreCnt = ingredientsColSize[i];
        recipeStr[i].idx = i;

        for (int j = 0; j < ingredientsColSize[i]; j++) {
            IngreHash* tmp;
            HASH_FIND_STR(ingHash, ingredients[i][j], tmp);
            if (tmp == NULL) {
                tmp = (IngreHash*)malloc(sizeof(IngreHash));
                if (tmp == NULL) {
                    perror("malloc");
                    freeAll(ingHash);
                    free(recipeStr);
                    return pRetVal;
                }
                tmp->ingre = ingredients[i][j];
                tmp->top = 1;
                tmp->dishIdx[tmp->top - 1] = i;
                HASH_ADD_STR(ingHash, ingre, tmp);
            } else {
                tmp->top++;
                tmp->dishIdx[tmp->top - 1] = i;
            }
        }
    }

    char** que = (char**)malloc(INGRE_NUM * 2 * sizeof(char*));
    if (que == NULL) {
        perror("malloc");
        freeAll(ingHash);
        free(recipeStr);
        return pRetVal;
    }
    int r = 0;
    for (int i = 0; i < suppliesSize; i++) {
        que[r++] = supplies[i];
    }

    pRetVal = (char**)malloc(recipesSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        free(que);
        freeAll(ingHash);
        free(recipeStr);
        return pRetVal;
    }
    int idx = 0;
    int l = 0;
    while (l < r) {
        char* cur = que[l++];
        IngreHash* tmp;
        HASH_FIND_STR(ingHash, cur, tmp);
        if (tmp == NULL) {
            continue;
        } else if (tmp->top == 0) {
            continue;
        }

        for (int j = 0; j < tmp->top; j++) {
            recipeStr[tmp->dishIdx[j]].ingreCnt--;
            if (recipeStr[tmp->dishIdx[j]].ingreCnt == 0) {
                pRetVal[idx] = (char*)calloc(RECIPE_NAME, sizeof(char));
                strcpy(pRetVal[idx++], recipeStr[tmp->dishIdx[j]].reciName);
                que[r++] = recipeStr[tmp->dishIdx[j]].reciName;
            }
        }
    }
    (*returnSize) = idx;

    //
    free(que);
    freeAll(ingHash);
    free(recipeStr);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* recipes[MAX_SIZE];
        int recipesSize;
        char* ingredients[MAX_SIZE][MAX_SIZE];
        int ingredientsSize;
        int ingredientsColSize[MAX_SIZE];
        char* supplies[MAX_SIZE];
        int suppliesSize;
        int returnSize;
    } testCase[] = {{{"bread"}, 1, {{"yeast", "flour"}}, 1, {2}, {"yeast", "flour", "corn"}, 3, 0},
                    {{"bread", "sandwich"},
                     2,
                     {{"yeast", "flour"}, {"bread", "meat"}},
                     2,
                     {2, 2},
                     {"yeast", "flour", "meat"},
                     3,
                     0},
                    {{"bread", "sandwich", "burger"},
                     3,
                     {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}},
                     3,
                     {2, 2, 3},
                     {"yeast", "flour", "meat"},
                     3,
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
     *  Output: ["bread"]
     *
     *  Input: recipes = ["bread","sandwich"],
     *  ingredients = [["yeast","flour"],["bread","meat"]],
     *  supplies = ["yeast","flour","meat"]
     *  Output:["bread","sandwich"]
     *
     *  Input: recipes = ["bread","sandwich","burger"],
     *  ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]],
     *  supplies = ["yeast","flour","meat"]
     *  Output: ["bread","sandwich","burger"]
     */

    char*** pIngredients = NULL;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: recipes = [");
        for (j = 0; j < testCase[i].recipesSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].recipes[j]);
        }
        printf("], ingredients = [");
        for (j = 0; j < testCase[i].ingredientsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].ingredientsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].ingredients[j][k]);
            }
            printf("]");
        }
        printf("], supplies = [");
        for (j = 0; j < testCase[i].suppliesSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].supplies[j]);
        }
        printf("]\n");

        pIngredients = (char***)malloc(testCase[i].ingredientsSize * sizeof(char**));
        if (pIngredients == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].ingredientsSize; ++j) {
            pIngredients[j] = (char**)malloc(testCase[i].ingredientsColSize[j] * sizeof(char*));
            if (pIngredients[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pIngredients[k]);
                    pIngredients[k] = NULL;
                }
                free(pIngredients);
                pIngredients = NULL;
                return EXIT_FAILURE;
            }
            for (k = 0; k < testCase[i].ingredientsColSize[j]; ++k) {
                pIngredients[j][k] = (char*)malloc(strlen(testCase[i].ingredients[j][k]) + 1);
                if (pIngredients[j][k] == NULL) {
                    perror("malloc");
                    for (k = 0; k < j; ++k) {
                        free(pIngredients[k]);
                        pIngredients[k] = NULL;
                    }
                    free(pIngredients);
                    pIngredients = NULL;
                    return EXIT_FAILURE;
                }
                strcpy(pIngredients[j][k], testCase[i].ingredients[j][k]);
            }
        }

        pAnswer = findAllRecipes(testCase[i].recipes, testCase[i].recipesSize, pIngredients,
                                 testCase[i].ingredientsSize, testCase[i].ingredientsColSize, testCase[i].supplies,
                                 testCase[i].suppliesSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

        for (j = 0; j < testCase[i].ingredientsSize; ++j) {
            for (k = 0; k < testCase[i].ingredientsColSize[j]; ++k) {
                free(pIngredients[j][k]);
                pIngredients[j][k] = NULL;
            }
            free(pIngredients[j]);
            pIngredients[j] = NULL;
        }
        free(pIngredients);
    }

    return EXIT_SUCCESS;
}
