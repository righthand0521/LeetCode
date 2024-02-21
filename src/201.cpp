#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int rangeBitwiseAnd(int left, int right) {
        int retVal = 0;

        int shift = 0;
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift += 1;
        }
        retVal = left << shift;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int left;
        int right;
    };
    vector<subject> testData{{5, 7}, {0, 0}, {1, 2147483647}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: left = 5, right = 7
     *  Output: 4
     *
     *  Input: left = 0, right = 0
     *  Output: 0
     *
     *  Input: left = 1, right = 2147483647
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: left = " << testData[i].left << ", right = " << testData[i].right << "\n";

        answer = cSolution.rangeBitwiseAnd(testData[i].left, testData[i].right);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
