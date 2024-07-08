#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findTheWinner(int n, int k) {
        int retVal = 1;

        if (n == 1) {
            return retVal;
        }
        retVal = (k + findTheWinner(n - 1, k) - 1) % n + 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{5, 2}, {6, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, k = 2
     *  Output: 3
     *
     *  Input: n = 6, k = 5
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.findTheWinner(testData[i].n, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
