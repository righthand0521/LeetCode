#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestEvenMultiple(int n) {
        int retVal = 0;

#if (1)
        retVal = n << (n & 1);
#else
        retVal = n;
        if (n % 2 == 1) {
            retVal = n * 2;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{5}, {6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5
     *  Output: 10
     *
     *  Input: n = 6
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: num = " << testData[i].n << "\n";

        answer = cSolution.smallestEvenMultiple(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
