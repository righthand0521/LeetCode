#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATH (1)
#define BRUTE_FORCE (1)
int countEven(int num) {
    int retVal = 0;

#if (MATH)
    printf("MATH\n");

    /* Math
     *  nums = xyz, sum of digits = x + y + z.
     *  if x + y + z is even, the even digit sums is nums / 2.
     *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
     */
    int sum = 0;
    int tmp = num;
    while (tmp > 0) {
        sum += (tmp % 10);
        tmp /= 10;
    }

    if (sum % 2 == 0) {
        retVal = num / 2;
    } else {
        retVal = (num - 1) / 2;
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    int tmp;
    int sum;
    int i;
    for (i = 2; i <= num; ++i) {
        sum = 0;
        tmp = i;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }
        if (sum % 2 == 0) {
            ++retVal;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{4}, {30}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = countEven(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
