#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_SIZE (int)(4 * 10000)
// Stores cumulative product of the stream
typedef struct {
    int prefixProduct[MAX_PRODUCT_SIZE];
    int index;
    int size;
} ProductOfNumbers;
ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* pRetVal = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->prefixProduct, 0, (MAX_PRODUCT_SIZE * sizeof(int)));
    pRetVal->index = 0;
    pRetVal->size = 0;

    // Initialize the product list with 1 to handle multiplication logic
    pRetVal->prefixProduct[pRetVal->index] = 1;
    pRetVal->size += 1;

    return pRetVal;
}
void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        // If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
        obj->index = 0;
        obj->prefixProduct[obj->index] = 1;
        obj->size = 1;
    } else {
        // Append the cumulative product of the current number with the last product
        obj->prefixProduct[obj->size] = obj->prefixProduct[obj->index] * num;
        obj->index += 1;
        obj->size += 1;
    }
}
int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    int retVal = 0;

    // Check if the requested product length exceeds the size of the valid product list
    if (k > obj->index) {
        return retVal;
    }
    // Compute the product of the last k elements using division
    retVal = obj->prefixProduct[obj->index] / obj->prefixProduct[obj->index - k];

    return retVal;
}
void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your ProductOfNumbers struct will be instantiated and called as such:
 * ProductOfNumbers* obj = productOfNumbersCreate();
 * productOfNumbersAdd(obj, num);
 * int param_2 = productOfNumbersGetProduct(obj, k);
 * productOfNumbersFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][4];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"ProductOfNumbers", "add", "add", "add", "add", "add", "getProduct", "getProduct", "getProduct",
                      "add", "getProduct"},
                     {{}, {3}, {0}, {2}, {5}, {4}, {2}, {3}, {4}, {8}, {2}},
                     {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
     *  [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
     *  Output
     *  [null,null,null,null,null,null,20,40,0,null,32]
     */

    ProductOfNumbers* obj = NULL;
    int retInt;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "ProductOfNumbers") == 0) {
                obj = productOfNumbersCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "add") == 0) {
                productOfNumbersAdd(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "getProduct") == 0) {
                retInt = productOfNumbersGetProduct(obj, testCase[i].val[j][0]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        productOfNumbersFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
