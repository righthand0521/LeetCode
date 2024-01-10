#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumOneBitOperations(int n) {
        int retVal = 0;

        int k = 0;
        int mask = 1;
        while (mask <= n) {
            if ((n & mask) != 0) {
                retVal = (1 << (k + 1)) - 1 - retVal;
            }
            mask <<= 1;
            k++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: 2
     *
     *  Input: n = 6
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.minimumOneBitOperations(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
