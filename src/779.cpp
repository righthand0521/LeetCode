#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int kthGrammar(int n, int k) {
        int retVal = 0;

#if (0)  // Recursion
        /*
         *  0
         *  0 1
         *  0 1 1 0
         *  0 1 1 0 1 0 0 1
         *  0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
         */
        if (k == 1) {
            return retVal;
        }
        if (k > (1 << (n - 2))) {
            retVal = 1 ^ (kthGrammar(n - 1, k - (1 << (n - 2))));
            return retVal;
        }
        retVal = kthGrammar(n - 1, k);
#else  // Bit Manipulation: 0->01, 1-> 10.
        /*
         *  +-------------------------------+
         *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
         *  +-------------------------------+
         *  | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
         *  +-------------------------------+
         *  | 0 | 1 |   |   |   |   |   |   |
         *  |   | 1 | 1 | 0 |   |   |   |   |
         *  |   |   | 1 |   | 1 | 0 |   |   |
         *  |   |   |   | 0 |   |   | 0 | 1 |
         *  +-------------------------------+
         */
        // retVal = __builtin_popcount(k - 1) & 1;
        k--;
        while (k > 0) {
            k &= (k - 1);
            retVal ^= 1;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{1, 1}, {2, 1}, {2, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1, k = 1
     *  Output: 0
     *
     *  Input: n = 2, k = 1
     *  Output: 0
     *
     *  Input: n = 2, k = 2
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.kthGrammar(testData[i].n, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
