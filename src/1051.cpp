#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int heightChecker(vector<int>& heights) {
        int retVal = 0;

        vector<int> expected(heights);
        sort(expected.begin(), expected.end());

        int heightsSize = heights.size();
        for (int i = 0; i < heightsSize; ++i) {
            if (heights[i] != expected[i]) {
                ++retVal;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> heights;
    };
    vector<subject> testData{{{1, 1, 4, 2, 1, 3}}, {{5, 1, 2, 3, 4}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [1,1,4,2,1,3]
     *  Output: 3
     *
     *  Input: heights = [5,1,2,3,4]
     *  Output: 5
     *
     *  Input: heights = [1,2,3,4,5]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].heights[j];
        }
        cout << "]\n";

        answer = cSolution.heightChecker(testData[i].heights);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
