#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long coloredCells(int n) {
        long long retVal = 0;

        /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
         *  = 1 + 4 x (1 + 2 + ... + (n-1))
         *  = 1 + 4 x (n x (n-1) / 2)
         *  = 1 + 2 x n x (n-1)
         */
        retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 2
     *  Output: 5
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.coloredCells(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
