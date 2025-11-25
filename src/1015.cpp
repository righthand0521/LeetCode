#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestRepunitDivByK(int k) {
        int retVal = -1;

        int remainder = 0;
        for (int nSize = 1; nSize <= k; ++nSize) {
            remainder = (remainder * 10 + 1) % k;
            if (remainder == 0) {
                retVal = nSize;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
    };
    vector<subject> testData{{1}, {2}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 1
     *  Output: 1
     *
     *  Input: k = 2
     *  Output: -1
     *
     *  Input: k = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << "\n";

        answer = cSolution.smallestRepunitDivByK(testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
