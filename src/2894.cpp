#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int differenceOfSums(int n, int m) {
        int retVal = 0;

        for (int i = 1; i <= n; ++i) {
            if (i % m == 0) {
                retVal -= i;
            } else {
                retVal += i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
    };
    vector<subject> testData{{10, 3}, {5, 6}, {5, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10, m = 3
     *  Output: 19
     *
     *  Input: n = 5, m = 6
     *  Output: 15
     *
     *  Input: n = 5, m = 1
     *  Output: -15
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << "\n";

        answer = cSolution.differenceOfSums(testData[i].n, testData[i].m);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
