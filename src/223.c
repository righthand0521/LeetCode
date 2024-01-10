#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int retVal = 0;

    int aSpace = (ax2 - ax1) * (ay2 - ay1);
    int bSpace = (bx2 - bx1) * (by2 - by1);

    int xOverlap = MIN(ax2, bx2) - MAX(ax1, bx1);
    int yOverlap = MIN(ay2, by2) - MAX(ay1, by1);
    int overlapSpace = 0;
    if ((xOverlap > 0) && (yOverlap > 0)) {
        overlapSpace = xOverlap * yOverlap;
    }
    retVal = aSpace + bSpace - overlapSpace;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int ax1;
        int ay1;
        int ax2;
        int ay2;
        int bx1;
        int by1;
        int bx2;
        int by2;
    } testCase[] = {{-3, 0, 3, 4, 0, -1, 9, 2},
                    {-2, -2, 2, 2, -2, -2, 2, 2},
                    {0, 0, 0, 0, -1, -1, 1, 1},
                    {-2, -2, 2, 2, -4, 3, -3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ax1 = %d, ay1 = %d, ax2 = %d, ay2 = %d, bx1 = %d, by1 = %d, bx2 =%d, by2 = %d\n",
               testCase[i].ax1, testCase[i].ay1, testCase[i].ax2, testCase[i].ay2, testCase[i].bx1, testCase[i].by1,
               testCase[i].bx2, testCase[i].by2);

        answer = computeArea(testCase[i].ax1, testCase[i].ay1, testCase[i].ax2, testCase[i].ay2, testCase[i].bx1,
                             testCase[i].by1, testCase[i].bx2, testCase[i].by2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
