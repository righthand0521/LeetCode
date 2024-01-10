#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPowerOfFour(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

#if (0)
        if ((n & (n - 1)) != 0) {
            return retVal;
        }

        if ((n & 0x55555555) != 0) {
            retVal = true;
        }
#else
        /* n = 4 ^ x
         * = > log(n) = x * log(4)
         * = > x = log(n) / log(4)
         */
        double x = log10(n) / log10(4);
        if (x - (int)x == 0) {
            retVal = true;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{16}, {5}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 16
     *  Output: true
     *
     *  Input: n = 5
     *  Output: false
     *
     *  Input: n = 1
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.isPowerOfFour(testData[i].n);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
