#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REFERENCE_1 \
    (1)  // 適用於帶括號的加減乘除運算: 遇到左括號, 將括號內的元素遞歸處理; 遞歸結束後, 再繼續與外層運算計算.
#define REFERENCE_2 (1)  // 適用於帶括號的加減運算: 考慮加減運算, 使用stack, 遇到括號時, 將括號外的運算符保留和結果保留.
#if (REFERENCE_1)
int recursive(char** s) {
    int retVal = 0;

    char* pStr = *s;
    int len = strlen(pStr);

    int top = 0;
    int* stack = (int*)malloc(sizeof(int) * len);
    if (stack == NULL) {
        perror("malloc");
        return retVal;
    }

    char sign = '+';
    int num = 0;
    char ch;
    while (*pStr) {
        ch = *pStr;
        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        }

        // 遇到左括號, 將括號內的元素遞歸處理
        if (ch == '(') {
            pStr++;
            num = recursive(&pStr);
        }

        if (((!isdigit(ch)) && (ch != ' ')) || (*(pStr + 1) == '\0')) {
            if (sign == '+') {
                stack[top++] = num;
            } else if (sign == '-') {
                stack[top++] = -num;
            }
            sign = ch;
            num = 0;

            // 遇到右括號, 退出本次處理, 更新字符串起始.
            if (ch == ')') {
                *s = pStr;
                break;
            }
        }
        pStr++;
    }

    while (top > 0) {
        retVal += stack[--top];
    }
    free(stack);
    stack = NULL;

    return retVal;
}

int calculate(char* s) {
    printf("REFERENCE_1\n");

    int retVal = recursive(&s);

    return retVal;
}
#elif (REFERENCE_2)
int calculate(char* s) {
    printf("REFERENCE_2\n");

    int retVal = 0;

    int len = strlen(s);

    int stack[len];
    int top = 0;

    int sign = 1;
    int num = 0;
    char ch;
    int i = 0;
    for (i = 0; i < len; ++i) {
        ch = s[i];

        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if ((ch == '+') || (ch == '-')) {
            retVal += (sign * num);
            num = 0;
            sign = (ch == '+') ? 1 : -1;
        } else if (ch == '(') {  // 左括號, 保留當前結果和符號位.
            stack[top++] = retVal;
            stack[top++] = sign;
            retVal = 0;
            sign = 1;
        } else if (ch == ')') {  // 右符號, 計算完括號內的結果, 並與Stack結果相加減.
            retVal += (sign * num);
            num = 0;
            retVal *= stack[--top];
            retVal += stack[--top];
        }
    }
    retVal += (sign * num);

    return retVal;
}
#endif

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"1 + 1"}, {" 2-1 + 2 "}, {"(1+(4+5+2)-3)+(6+8)"}, {"1-(     -2)"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = calculate(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
