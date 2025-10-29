#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestNumber(int n) {
        int retVal = 0;

        retVal = (1 << (32 - __builtin_clz(n))) - 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {10}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: 7
     *
     *  Input: n = 10
     *  Output: 15
     *
     *  Input: n = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.smallestNumber(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
