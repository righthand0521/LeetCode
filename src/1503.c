#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLastMoment(int n, int* left, int leftSize, int* right, int rightSize) {
    int retVal = 0;

    /* Brainteaser
     *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
     *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
     *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
     *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
     *  假設一隻螞蟻在位置 p。
     *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
     *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
     */
    int i;
    for (i = 0; i < leftSize; ++i) {
        retVal = fmax(retVal, left[i]);
    }
    for (i = 0; i < rightSize; ++i) {
        retVal = fmax(retVal, n - right[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000 + 4)
    struct testCaseType {
        int n;
        int left[MAX_SIZE];
        int leftSize;
        int right[MAX_SIZE];
        int rightSize;
    } testCase[] = {
        {4, {4, 3}, 2, {0, 1}, 2}, {7, {}, 0, {0, 1, 2, 3, 4, 5, 6, 7}, 8}, {7, {0, 1, 2, 3, 4, 5, 6, 7}, 8, {}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, left = [4,3], right = [0,1]
     *  Output: 4
     *
     *  Input: n = 7, left = [], right = [0,1,2,3,4,5,6,7]
     *  Output: 7
     *
     *  Input: n = 7, left = [0,1,2,3,4,5,6,7], right = []
     *  Output: 7
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, left = [", testCase[i].n);
        for (j = 0; j < testCase[i].leftSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].left[j]);
        }
        printf("], right = [");
        for (j = 0; j < testCase[i].rightSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].right[j]);
        }
        printf("]\n");

        answer = getLastMoment(testCase[i].n, testCase[i].left, testCase[i].leftSize, testCase[i].right,
                               testCase[i].rightSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
