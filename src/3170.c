#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // s consists only of lowercase English letters and '*'.
typedef struct {
    int* data;
    int size;
    int capacity;
} Stack;
Stack* createStack(int capacity) {
    Stack* pObj = NULL;

    pObj = (Stack*)malloc(sizeof(Stack));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data = (int*)malloc(capacity * sizeof(int));
    if (pObj->data == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 0;
    pObj->capacity = capacity;

    return pObj;
}
void push(Stack* stack, int value) {
    if (stack->size < stack->capacity) {
        stack->data[stack->size++] = value;
    }
}
int pop(Stack* stack) {
    int retVal = -1;

    if (stack->size > 0) {
        retVal = stack->data[--stack->size];
    }

    return retVal;
}
int isEmpty(Stack* stack) {
    int retVal = (stack->size == 0);

    return retVal;
}
void freeStack(Stack* stack) {
    free(stack->data);
    stack->data = NULL;
    free(stack);
    stack = NULL;
}
char* clearStars(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    Stack* lettersStack[MAX_LETTERS];
    for (int i = 0; i < MAX_LETTERS; i++) {
        lettersStack[i] = createStack(sSize);
        if (lettersStack[i] == NULL) {
            perror("createStack");
            for (int j = 0; j < i; j++) {
                freeStack(lettersStack[j]);
            }
            return pRetVal;
        }
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '*') {
            push(lettersStack[s[i] - 'a'], i);
            continue;
        }
        for (int j = 0; j < MAX_LETTERS; j++) {
            if (isEmpty(lettersStack[j]) == 0) {
                s[pop(lettersStack[j])] = '*';
                break;
            }
        }
    }

    int returnSize = 0;
    pRetVal = calloc(sSize + 1, sizeof(char));
    if (pRetVal != NULL) {
        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                pRetVal[returnSize++] = s[i];
            }
        }
    } else {
        perror("calloc");
    }

    // Free the stacks
    for (int i = 0; i < MAX_LETTERS; i++) {
        freeStack(lettersStack[i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aaba*"}, {"abc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaba*"
     *  Output: "aab"
     *
     *  Input: s = "abc"
     *  Output: "abc"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = clearStars(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
