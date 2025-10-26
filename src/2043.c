#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long* balance;
    int balanceSize;
} Bank;
Bank* bankCreate(long long* balance, int balanceSize) {
    Bank* pObj = NULL;

    pObj = (Bank*)malloc(sizeof(Bank));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->balance = (long long*)malloc(balanceSize * sizeof(long long));
    if (pObj->balance == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    memcpy(pObj->balance, balance, (balanceSize * sizeof(long long)));
    pObj->balanceSize = balanceSize;

    return pObj;
}
bool bankTransfer(Bank* obj, int account1, int account2, long long money) {
    bool retVal = false;

    if ((obj->balanceSize < account1) || (obj->balanceSize < account2)) {
        return retVal;
    } else if (obj->balance[account1 - 1] < money) {
        return retVal;
    }

    obj->balance[account1 - 1] -= money;
    obj->balance[account2 - 1] += money;
    retVal = true;

    return retVal;
}
bool bankDeposit(Bank* obj, int account, long long money) {
    bool retVal = false;

    if (obj->balanceSize < account) {
        return retVal;
    }

    obj->balance[account - 1] += money;
    retVal = true;

    return retVal;
}
bool bankWithdraw(Bank* obj, int account, long long money) {
    bool retVal = false;

    if (obj->balanceSize < account) {
        return retVal;
    } else if (obj->balance[account - 1] < money) {
        return retVal;
    }

    obj->balance[account - 1] -= money;
    retVal = true;

    return retVal;
}
void bankFree(Bank* obj) {
    free(obj->balance);
    obj->balance = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 * bool param_2 = bankDeposit(obj, account, money);
 * bool param_3 = bankWithdraw(obj, account, money);
 * bankFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        long long balance[MAX_SIZE][100];
        int balanceSize[MAX_SIZE];
        int account1[MAX_SIZE];
        int account2[MAX_SIZE];
        long long money[MAX_SIZE];
        int account[MAX_SIZE];
        int calls;
    } testCase[] = {{{"Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"},
                     {{10, 100, 20, 50, 30}, {}, {}, {}, {}, {}},
                     {5, 0, 0, 0, 0, 0},
                     {0, 0, 5, 0, 3, 0},
                     {0, 0, 1, 0, 4, 0},
                     {0, 10, 20, 20, 15, 50},
                     {0, 3, 0, 5, 0, 10},
                     6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["Bank", "withdraw", "transfer", "deposit", "transfer", "withdraw"]
     *  [[[10, 100, 20, 50, 30]], [3, 10], [5, 1, 20], [5, 20], [3, 4, 15], [10, 50]]
     *  Output
     *  [null, true, true, true, false, false]
     */

    Bank* obj = NULL;
    bool retBool;
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
            if (strcmp(testCase[i].methods[j], "Bank") == 0) {
                printf("%s[", (j == 0) ? "" : ", ");
                for (k = 0; k < testCase[i].balanceSize[j]; ++k) {
                    printf("%s%lld", (k == 0) ? "" : ", ", testCase[i].balance[j][k]);
                }
                printf("]");
            } else if (strcmp(testCase[i].methods[j], "transfer") == 0) {
                printf("%d, %d, %lld", testCase[i].account1[j], testCase[i].account2[j], testCase[i].money[j]);
            } else if (strcmp(testCase[i].methods[j], "deposit") == 0) {
                printf("%d, %lld", testCase[i].account[j], testCase[i].money[j]);
            } else if (strcmp(testCase[i].methods[j], "withdraw") == 0) {
                printf("%d, %lld", testCase[i].account[j], testCase[i].money[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "Bank") == 0) {
                obj = bankCreate(testCase[i].balance[j], testCase[i].balanceSize[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "transfer") == 0) {
                retBool = bankTransfer(obj, testCase[i].account1[j], testCase[i].account2[j], testCase[i].money[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "deposit") == 0) {
                retBool = bankDeposit(obj, testCase[i].account[j], testCase[i].money[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "withdraw") == 0) {
                retBool = bankWithdraw(obj, testCase[i].account[j], testCase[i].money[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        bankFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
