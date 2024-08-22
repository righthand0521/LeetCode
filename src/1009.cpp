#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int bitwiseComplement(int n) {
        int retVal = n;

        // 0 <= n < 10^9
        if (n == 0) {
            retVal = 1;
            return retVal;
        }

        int i = 31;
        while ((retVal & ((uint32_t)1 << i)) == 0) {
            i--;
        }

        while (i >= 0) {
            retVal ^= (1 << i--);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {7}, {10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: 2
     *
     *  Input: n = 7
     *  Output: 0
     *
     *  Input: n = 10
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.bitwiseComplement(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
