#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int divide(int dividend, int divisor) {
        int quotient = 0;

        if ((dividend == 0) || (divisor == 0)) {
            return quotient;
        }

        long absDividend = labs(dividend);
        long absDivisor = labs(divisor);
        if (absDividend < absDivisor) {
            return quotient;
        }

        int i;
        for (i = 31; i >= 0; --i) {
            if ((absDivisor << i) > absDividend) {
                continue;
            }
            absDividend -= (absDivisor << i);
            quotient += ((long)1 << i);
        }

        int negative = (((dividend < 0) ^ (divisor < 0)) == 1) ? (-1) : 1;
        if ((quotient == numeric_limits<int>::min()) && (negative == 1)) {
            quotient = numeric_limits<int>::max();
        } else if ((quotient == numeric_limits<int>::min()) && (negative == -1)) {
            negative = 1;
        }
        quotient = negative * quotient;

        return quotient;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int dividend;
        int divisor;
    };
    vector<subject> testData{
        {10, 3}, {7, -3}, {-1, -1}, {1, 2}, {2, 2}, {numeric_limits<int>::min(), -1}, {numeric_limits<int>::min(), 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: dividend = 10, divisor = 3
     *  Output: 3
     *
     *  Input: dividend = 7, divisor = -3
     *  Output: -2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: dividend = " << testData[i].dividend << ", divisor = " << testData[i].divisor << "\n";

        answer = cSolution.divide(testData[i].dividend, testData[i].divisor);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
