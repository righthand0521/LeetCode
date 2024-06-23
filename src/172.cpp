#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int trailingZeroes(int n) {
        int retVal = 0;

        while (n >= 5) {
            retVal += (n / 5);
            n /= 5;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {5}, {0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: 0
     *
     *  Input: n = 5
     *  Output: 1
     *
     *  Input: n = 0
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.trailingZeroes(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
