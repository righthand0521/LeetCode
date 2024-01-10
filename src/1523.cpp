#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countOdds(int low, int high) {
        int retVal = 0;

        int range = high - low + 1;
        retVal = range / 2;
        if ((range % 2) == 1) {
            retVal = (((low % 2) == 1) || ((high % 2) == 1)) ? retVal + 1 : retVal;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int low;
        int high;
    };
    vector<subject> testData{{3, 7}, {8, 10}, {1, 1}, {1, 2}, {2, 2}, {2, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: low = 3, high = 7
     *  Output: 3
     *
     *  Input: low = 8, high = 10
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: low = " << testData[i].low << ", high = " << testData[i].high << "\n";

        answer = cSolution.countOdds(testData[i].low, testData[i].high);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
