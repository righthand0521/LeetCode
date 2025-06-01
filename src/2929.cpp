#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long distributeCandies(int n, int limit) {
        long long retVal = 0;

        int minLimit = min(limit, n);
        for (int i = 0; i <= minLimit; i++) {
            if ((n - i) > (2 * limit)) {
                continue;
            }
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int limit;
    };
    vector<subject> testData{{5, 2}, {3, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, limit = 2
     *  Output: 3
     *
     *  Input: n = 3, limit = 3
     *  Output: 10
     */

    Solution cSolution;
    long long answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", limit = " << testData[i].limit << "\n";

        answer = cSolution.distributeCandies(testData[i].n, testData[i].limit);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
