#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPowerOfTwo(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

#if (0)
        if ((n & (n - 1)) == 0) {
            retVal = true;
        }
#else
        /* n = 2 ^ x
         * = > log(n) = x * log(2)
         * = > x = log(n) / log(2)
         */
        double x = log10(n) / log10(2);
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
    vector<subject> testData{{1}, {16}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: true
     *
     *  Input: n = 16
     *  Output: true
     *
     *  Input: n = 3
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].n << "\n";

        answer = cSolution.isPowerOfTwo(testData[i].n);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
