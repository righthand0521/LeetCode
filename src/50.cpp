#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    double myPow(double x, int n) {
        double retVal = 1;

        /* https://en.wikipedia.org/wiki/Exponentiation_by_squaring
         *
         * func binaryExp(x, n):
         *  if n == 0: return 1.0
         *  if n < 0: return 1.0 / binaryExp(x, -n)
         *  // Binary exponentiation steps.
         *  if n is odd: return x * binaryExp(x * x, (n - 1) / 2)
         *  otherwise: return binaryExp(x * x, n / 2)
         */

        if ((x == (double)0) || (x == (double)1)) {
            retVal = x;
            return retVal;
        } else if (x == (double)(-1)) {
            retVal = (n % 2 == 0) ? 1 : -1;
            return retVal;
        }

        x = (n > 0) ? x : 1 / x;
        if (n == numeric_limits<int>::min()) {
            n += 1;
        }

        int times = abs(n);
        while (times > 0) {
            if (times % 2 == 1) {
                retVal *= x;
                --times;
            }
            if (retVal == (double)0) {
                break;
            }

            x *= x;
            times >>= 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        double x;
        int n;
    };
    vector<subject> testData{{2.000000, 10}, {2.100000, 3}, {2.000000, -2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: x = 2.00000, n = 10
     *  Output: 1024.00000
     *
     *  Input: x = 2.10000, n = 3
     *  Output: 9.26100
     *
     *  Input: x = 2.00000, n = -2
     *  Output: 0.25000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Input: x = " << testData[i].x << ", n = " << testData[i].n << "\n";

        answer = cSolution.myPow(testData[i].x, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
