#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long getSum(int index, int value, int n) {
        long retVal = 0;

        // On index's left:
        // If value > index, there are index + 1 numbers in the arithmetic sequence:
        // [value - index, ..., value - 1, value].
        // Otherwise, there are value numbers in the arithmetic sequence:
        // [1, 2, ..., value - 1, value], plus a sequence of length (index - value + 1) of 1s.
        if (value > index) {
            retVal += (long)(value + value - index) * (index + 1) / 2;
        } else {
            retVal += (long)(value + 1) * value / 2 + index - value + 1;
        }

        // On index's right:
        // If value >= n - index, there are n - index numbers in the arithmetic sequence:
        // [value, value - 1, ..., value - n + 1 + index].
        // Otherwise, there are value numbers in the arithmetic sequence:
        // [value, value - 1, ..., 1], plus a sequence of length (n - index - value) of 1s.
        if (value >= n - index) {
            retVal += (long)(value + value - n + 1 + index) * (n - index) / 2;
        } else {
            retVal += (long)(value + 1) * value / 2 + n - index - value;
        }

        retVal -= value;

        return retVal;
    }
    int maxValue(int n, int index, int maxSum) {
        int retVal = 0;

        int middle;
        int left = 1;
        int right = maxSum;
        while (left < right) {
            middle = (left + right + 1) / 2;
            // 1 <= n <= maxSum <= 10^9, 0 <= index < n
            if (getSum(index, middle, n) <= maxSum) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int index;
        int maxSum;
    };
    vector<subject> testData{{4, 2, 6}, {6, 1, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, index = 2,  maxSum = 6
     *  Output: 2
     *
     *  Input: n = 6, index = 1,  maxSum = 10
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", index = " << testData[i].index
             << ", maxSum = " << testData[i].maxSum << "\n";

        answer = cSolution.maxValue(testData[i].n, testData[i].index, testData[i].maxSum);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
