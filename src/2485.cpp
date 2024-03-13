#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int pivotInteger(int n) {
        int retVal = -1;

        /* 1 + 2 + ... + x = x + ... + n
         * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
         * => 2 * x^2 = n^2 + n
         * => x = ((n^2 + n) / 2)^(1/2)
         * => x = ((n * (n+1) / 2))^(1/2)
         */
        int sum = n * (n + 1) / 2;
        int x = sqrt(sum);
        if (x * x == sum) {
            retVal = x;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{8}, {1}, {4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 8
     *  Output: 6
     *
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 4
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.pivotInteger(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
