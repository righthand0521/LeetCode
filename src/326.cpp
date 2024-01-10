#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPowerOfThree(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

        if (n % 2 == 0) {
            return retVal;
        }

        /*  n = 3^x
         *  => log(n) = x * log(3)
         *  => x = log(n) / log(3)
         */
        double x = log10(n) / log10(3);
        if (x - (int)x == 0) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{27}, {0}, {-1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 27
     *  Output: true
     *
     *  Input: n = 0
     *  Output: false
     *
     *  Input: n = -1
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.isPowerOfThree(testData[i].n);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
