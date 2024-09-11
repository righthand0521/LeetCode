#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minBitFlips(int start, int goal) {
        int retVal = 0;

        for (int i = 0; i < 32; ++i) {
            retVal += (start & 1) ^ (goal & 1);
            start >>= 1;
            goal >>= 1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int start;
        int goal;
    };
    vector<subject> testData{{10, 7}, {3, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: start = 10, goal = 7
     *  Output: 3
     *
     *  Input: start = 3, goal = 4
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: start = " << testData[i].start << ", goal = " << testData[i].goal << "\n";

        answer = cSolution.minBitFlips(testData[i].start, testData[i].goal);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
