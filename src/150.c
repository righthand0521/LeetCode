#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK
#define STACK (1)

typedef struct Node {
    long long data;
    struct Node* next;
} Node;
void stack_show(struct Node* pTop) {
    Node* pHead = pTop;
    while (pHead != NULL) {
        printf("%3lld -> ", pHead->data);
        pHead = pHead->next;
    }
    printf("NULL\n");
}
void stack_push(struct Node** pTop, int value) {
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = (*pTop);
    *(pTop) = pNew;
}
int stack_pop(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);
    pHead = NULL;

    return retVal;
}
void stack_free(struct Node** pTop) {
    Node* pFree = (*pTop);
    while ((*pTop) != NULL) {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
    pFree = NULL;
}
#endif
int evalRPN(char** tokens, int tokensSize) {
    int retVal = 0;

    Node* pTop = NULL;
    long long push, pop1, pop2;
    int i;
    for (i = 0; i < tokensSize; ++i) {
        push = 0;

        // tokens[i] is either an operator: "+", "-", "*", or "/"
        if ((strcmp(tokens[i], "+") == 0) || (strcmp(tokens[i], "-") == 0) || (strcmp(tokens[i], "*") == 0) ||
            (strcmp(tokens[i], "/") == 0)) {
            pop1 = stack_pop(&pTop);
            pop2 = stack_pop(&pTop);
            if (strcmp(tokens[i], "+") == 0) {
                push = pop2 + pop1;
            } else if (strcmp(tokens[i], "-") == 0) {
                push = pop2 - pop1;
            } else if (strcmp(tokens[i], "*") == 0) {
                push = pop2 * pop1;
            } else if (strcmp(tokens[i], "/") == 0) {
                push = pop2 / pop1;
            }
        } else {
            push = atoi(tokens[i]);
        }

        stack_push(&pTop, push);
    }
    retVal = stack_pop(&pTop);

    //
    stack_free(&pTop);
    pTop = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* tokens[MAX_SIZE];
        int tokensSize;
    } testCase[] = {{{"2", "1", "+", "3", "*"}, 5},
                    {{"4", "13", "5", "/", "+"}, 5},
                    {{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}, 13}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tokens = ["2","1","+","3","*"]
     *  Output: 9
     *
     *  Input: tokens = ["4","13","5","/","+"]
     *  Output: 6
     *
     *  Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
     *  Output: 22
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tokens = [");
        for (j = 0; j < testCase[i].tokensSize; ++j) {
            printf("\"%s\"%s", testCase[i].tokens[j], (j == (testCase[i].tokensSize - 1) ? "" : ","));
        }
        printf("]\n");

        answer = evalRPN(testCase[i].tokens, testCase[i].tokensSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
