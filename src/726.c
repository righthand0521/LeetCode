#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/number-of-atoms/solutions/95872/c-jian-dan-de-cong-you-xiang-zuo-bian-li-fen-qing-/
char* countOfAtoms(char* formula) {
    char* pRetVal = NULL;

    int returnSize = 1001;  // 1 <= formula.length <= 1000
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int formulaSize = strlen(formula);
    int i, j;

#define LETTERS_SIZE (26)  // formula consists of English letters, digits, '(', and')'.
    int store[LETTERS_SIZE][LETTERS_SIZE + 1];
    memset(store, 0, sizeof(store));

    int stack[formulaSize + 1];
    memset(stack, 0, sizeof(stack));

    int digit = 1;
    int top = 0;
    int numTemp = 0;
    int coefficient = 1;
    for (i = formulaSize - 1; i >= 0;) {
        if (isdigit(formula[i])) {
            digit = 1;
            numTemp += ((formula[i] - '0') * digit);
            while (isdigit(formula[--i])) {
                digit *= 10;
                numTemp += ((formula[i] - '0') * digit);
            }
            coefficient *= numTemp;
            stack[top++] = numTemp;
        }

        if (formula[i] == ')') {
            numTemp = 0;
        } else if (formula[i] == '(') {
            if (top > 0) {
                coefficient /= stack[--top];
            }
        } else if (isupper(formula[i])) {
            store[formula[i] - 'A'][0] += 1 * coefficient;
            if (numTemp != 0) {
                coefficient /= stack[--top];
                numTemp = 0;
            }
        } else if (islower(formula[i])) {
            store[formula[i - 1] - 'A'][formula[i] - 'a' + 1] += (1 * coefficient);
            if (numTemp != 0) {
                coefficient /= stack[--top];
                numTemp = 0;
            }
            i--;
        }

        i--;
    }

    int tail = 0;
    for (i = 0; i < LETTERS_SIZE; i++) {
        if (store[i][0] == 1) {
            tail += sprintf(pRetVal + tail, "%c", i + 'A');
        } else if (store[i][0] > 1) {
            tail += sprintf(pRetVal + tail, "%c%d", i + 'A', store[i][0]);
        }

        for (j = 1; j <= LETTERS_SIZE; j++) {
            if (store[i][j] == 1) {
                tail += sprintf(pRetVal + tail, "%c%c", i + 'A', j - 1 + 'a');
            } else if (store[i][j] > 1) {
                tail += sprintf(pRetVal + tail, "%c%c%d", i + 'A', j - 1 + 'a', store[i][j]);
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char formula[MAX_SIZE];
    } testCase[] = {{"H2O"}, {"Mg(OH)2"}, {"K4(ON(SO3)2)2"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: formula = "H2O"
     *  Output: "H2O"
     *
     *  Input: formula = "Mg(OH)2"
     *  Output: "H2MgO2"
     *
     *  Input: formula = "K4(ON(SO3)2)2"
     *  Output: "K4N2O14S4"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: formula = \"%s\"\n", testCase[i].formula);

        pAnswer = countOfAtoms(testCase[i].formula);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
